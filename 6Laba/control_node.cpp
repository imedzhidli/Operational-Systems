#include <unistd.h>
#include <vector>
#include <zmq.hpp>

#include "my_zmq.h"
#include "topology.h"

using namespace std;

using node_id_type = long long;

void delete_control_node(node_id_type id, topology_t<node_id_type> &control_node, vector<pair<void *, void *>> children) {
  int ind = control_node.find(id);
  int rc;
  bool ok;
  if (ind != -1) {
	auto *token = new node_token_t({destroy, id, id});
	node_token_t reply({fail, id, id});
	ok = my_zmq::send_receive_wait(token, reply, children[ind].second);
	if (reply.action == destroy and reply.parent_id == id) {
	  rc = zmq_close(children[ind].second);
	  assert(rc == 0);
	  rc = zmq_ctx_destroy(children[ind].first);
	  assert(rc == 0);
	  auto it = children.begin();
	  while (ind--) {
		++it;
	  }
	  children.erase(it);
	} else if (reply.action == bind and reply.parent_id == id) {
	  rc = zmq_close(children[ind].second);
	  assert(rc == 0);
	  rc = zmq_ctx_term(children[ind].first);
	  assert(rc == 0);
	  my_zmq::init_pair_socket(children[ind].first, children[ind].second);
	  rc = zmq_bind(children[ind].second, ("tcp://*:" + to_string(PORT_BASE + id)).c_str());
	  assert(rc == 0);
	}
	if (ok) {
	  control_node.erase(id);
	  cout << "OK: " << id << endl;
	} else {
	  cout << "Error: Node " << id << " is unavailable" << endl;
	}
  } else {
	cout << "Error: Not found" << endl;
  }
}

int main() {
  int rc;
  bool ok;
  topology_t<node_id_type> control_node;
  vector<pair<void *, void *>> children;// [context, socket]
  string s;
  node_id_type id;

  while (cin >> s >> id) {
	if (s == "create") {
	  node_id_type parent_id;
	  cin >> parent_id;
	  int ind;
	  if (parent_id == -1) {
		void *new_context = nullptr;
		void *new_socket = nullptr;
		my_zmq::init_pair_socket(new_context, new_socket);
		rc = zmq_bind(new_socket, ("tcp://*:" + to_string(PORT_BASE + id)).c_str());
		assert(rc == 0);

		int fork_id = fork();
		if (fork_id == 0) {
		  rc = execl(NODE_EXECUTABLE_NAME, NODE_EXECUTABLE_NAME, to_string(id).c_str(), nullptr);
		  assert(rc != -1);
		  return 0;
		} else {
		  auto *token = new node_token_t({ping, id, id});
		  node_token_t reply({fail, id, id});
		  if (my_zmq::send_receive_wait(token, reply, new_socket) and reply.action == success) {
			children.emplace_back(make_pair(new_context, new_socket));
			control_node.insert(id);
		  } else {
			rc = zmq_close(new_socket);
			assert(rc == 0);
			rc = zmq_ctx_destroy(new_context);
			assert(rc == 0);
		  }
		}
	  } else if ((ind = control_node.find(parent_id)) == -1) {
		cout << "Error: Not found" << endl;
		continue;
	  } else {
		if (control_node.find(id) != -1) {
		  cout << "Error: Already exists" << endl;
		  continue;
		}
		auto *token = new node_token_t({create, parent_id, id});
		node_token_t reply({fail, id, id});
		if (my_zmq::send_receive_wait(token, reply, children[ind].second) and reply.action == success) {
		  control_node.insert(parent_id, id);
		} else {
		  cout << "Error: Parent is unavailable" << endl;
		}
	  }
	} else if (s == "remove") {
	  delete_control_node(id, control_node, children);
	} else if (s == "ping") {
	  int ind = control_node.find(id);
	  if (ind == -1) {
		cout << "Error: Not found" << endl;
		continue;
	  }
	  auto *token = new node_token_t({ping, id, id});
	  node_token_t reply({fail, id, id});
	  if (my_zmq::send_receive_wait(token, reply, children[ind].second) and reply.action == success) {
		cout << "OK: 1" << endl;
	  } else {
		cout << "OK: 0" << endl;
	  }
	} else if (s == "exec") {
	  ok = true;
	  string key;
	  char c;
	  int val = -1;
	  bool add = false;
	  cin >> key;
	  if ((c = getchar()) == ' ') {
		add = true;
		cin >> val;
	  }
	  int ind = control_node.find(id);
	  if (ind == -1) {
		cout << "Error: Not found" << endl;
		continue;
	  }
	  key += SENTINEL;
	  if (add) {
		for (auto i: key) {
		  auto *token = new node_token_t({exec_add, i, id});
		  node_token_t reply({fail, id, id});
		  if (!my_zmq::send_receive_wait(token, reply, children[ind].second) or reply.action != success) {
			cout << "Fail: " << i << endl;
			ok = false;
			break;
		  }
		}
		auto *token = new node_token_t({exec_add, val, id});
		node_token_t reply({fail, id, id});
		if (!my_zmq::send_receive_wait(token, reply, children[ind].second) or reply.action != success) {
		  cout << "Fail: " << val << endl;
		  ok = false;
		}
	  } else {
		for (auto i: key) {
		  auto *token = new node_token_t({exec_check, i, id});
		  node_token_t reply({fail, i, id});
		  if (!my_zmq::send_receive_wait(token, reply, children[ind].second) or reply.action != success) {
			ok = false;
			cout << "Fail: " << i << endl;
			break;
		  }
		}
	  }
	  if (!ok) {
		cout << "Error: Node is unavailable" << endl;
	  }
	} else if (s == "print") {
	  cout << control_node;
	}
  }
  cout << control_node;
  for (auto i: control_node.container) {
	for (size_t size = i.size(); size > 1; --size) {
	  node_id_type last = i.back();
	  delete_control_node(last, control_node, children);
	  i.pop_back();
	}
  }

  vector<node_id_type> after_root;
  for (auto i: control_node.container) {
	after_root.push_back(i.back());
  }

  for (auto i: after_root) {
	delete_control_node(i, control_node, children);
  }
  return 0;
}