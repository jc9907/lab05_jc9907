#include "tddFuncs.h"
#include "WordCount.h"
#include <sstream>

using namespace std;

int main(){
    cout<< "Testing WordCount..."<<endl;
    WordCount w;
    string a = "sentence is a sentence";
    string b = "sentence is      a              sentence";
    string c = "sentence \n is  a\n\n\n\n sentence  \n crazy\n test  test  test";
    w.addAllWords(c);
    ostringstream oss;
    w.dumpWordsSortedByOccurence(oss);
    ASSERT_EQUALS("TEST,3\nSENTENCE,2\nA,1\nCRAZY,1\nIS,1\n", oss.str());
    oss.str("");
    w.dumpWordsSortedByWord(oss);
    ASSERT_EQUALS("A,1\nCRAZY,1\nIS,1\nSENTENCE,2\nTEST,3\n", oss.str());
    return 0;
    }
    
 