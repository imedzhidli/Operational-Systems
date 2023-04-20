#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <gtest/gtest.h>
#include <string>

#include "parent.h"
#include "string_to_vector.h"

using namespace std;


TEST(Lab4Test, StringToVectorTest) {
    vector <vector <int>> expectedVectors = {
            {1, 2, 3, 4, 5},
            {200, 4, 5},
            {10, 0}
    };
    vector <string> inputStrings = {
            "1 2 3 4 5",
            "200 4 5",
            "10 0"
    };

    long unsigned int countTests = 3;
    for (long unsigned int i = 0; i < countTests; i++) {
        vector <int> outputVector = StringToVector(inputStrings[i]);
        ASSERT_EQ(expectedVectors[i].size(), outputVector.size());
        for (long unsigned int j = 0; j < expectedVectors[i].size(); j++) {
            EXPECT_EQ(expectedVectors[i][j], outputVector[j]);
            EXPECT_EQ(1, 1);
        }
    }
}

TEST(Lab4Test, ParentTest) {
    vector <string> namesOutputFile = {
            "checker.txt",
            "output.txt",
            "jambo.tea"
    };
    vector <string> stringsNumbers = {
            "200 4 5\n800 8\n1\n90 2"
            ""
    };
    vector <string> expectedStrings = {
            "10 100 1 45 "
    };

    long unsigned int countTests = 1;
    for (long unsigned int i = 0; i < countTests; i++) {
        {
            ofstream fOut("input.txt");
            fOut << namesOutputFile[i] << "\n";
            fOut << stringsNumbers[i] << "\n";
        }

        {
            ifstream fIn("input.txt");
            ParentRoutine(fIn, getenv("PATH_TO_CHILD4"));
        }
        remove("input.txt");
    
        {
            ifstream fInCheckOutput = ifstream(namesOutputFile[i]);

            ASSERT_TRUE(fInCheckOutput.good());
        
            string outputString;
            getline(fInCheckOutput, outputString);
            
            EXPECT_EQ(outputString, expectedStrings[i]);
            fInCheckOutput.clear();
        }

        remove(namesOutputFile[i].data());
    }
}
