#ifndef OS_LABS_UTILS_H
#define OS_LABS_UTILS_H

template <typename Container>
inline int Isize(const Container& cont) {
    return static_cast<int>(cont.size());
}

#endif //OS_LABS_UTILS_H