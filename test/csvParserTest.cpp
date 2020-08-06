#include "gtest/gtest.h"
#include <string>
#include <sstream>
#include "parser/parseErrors.h"
#include "parser/csvTokenizer.h"

using namespace echeck::parser;
using namespace std;

class csvTokenizerFromString {
  public:
    csvTokenizer *izer;
    istringstream *ss;

    csvTokenizerFromString(const string &str)
    {
      ss = new istringstream(str);
      izer = new csvTokenizer(ss);
    }

    ~csvTokenizerFromString()
    {
      delete izer;
      delete ss;
    }
};

string testCSVTokenizerFromString(string str)
{
  csvTokenizerFromString ctfs(str);
  return ctfs.izer->getField();
}

TEST(EscapedToken, UnfinishedField) {
  // I'm looking for either parser_error or token_error
  EXPECT_THROW(testCSVTokenizerFromString("\"This doesn't fini"), parser_error);
  EXPECT_THROW(testCSVTokenizerFromString("\"\"\"Opens with escaped double quote"), parser_error);
  EXPECT_THROW(testCSVTokenizerFromString("\"Ends with escaped double quote \"\""), parser_error);
  EXPECT_THROW(testCSVTokenizerFromString("\"\"\"Surrounded by escaped quotes\"\""), parser_error);
  EXPECT_THROW(testCSVTokenizerFromString("\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\""), parser_error); // has odd number of escaped quotes
  // Just make sure it doesn't just throw
  EXPECT_NO_THROW(testCSVTokenizerFromString("\"This does finish\""));
}

TEST(EscapedToken, NormalUsage) {
  string in_out_pairs[][2] = {
    // can it handle the basics?
    {"\"This is intended\"", "This is intended"},
    // empty
    {"\"\"", ""},
    // escaped quotes?
    {"\"\"\"\"", "\""},
    {"\"\"\"\"\"\"", "\"\""},
    // do special characters make it through?
    {"\"Special characters like\ta tab,\nnewline,\"\"and escaped quote\"", "Special characters like\ta tab,\nnewline,\"and escaped quote"},
    // Are CRLF and LF characters okay?
    {"\"CRLF:\x0d\x0a,Simpler:\n\"", "CRLF:\n,Simpler:\n"},
    // A single token extraction?
    {"\"Hello\",\"How are you?\"", "Hello"}
  };
  int i = sizeof(in_out_pairs) / sizeof(in_out_pairs[0]);
  for (i -= 1; i >= 0; i--) { // backwards iterator
    EXPECT_EQ(testCSVTokenizerFromString(in_out_pairs[i][0]), in_out_pairs[i][1]);
  }
}

TEST(EscapedToken, IllegalCharacters) {
  EXPECT_THROW(testCSVTokenizerFromString("\"Hello\rThat should break\""), token_error);
}

TEST(EscapedToken, Assumptions) {
  ASSERT_EQ('\x0d', '\r');
  ASSERT_EQ('\x0a', '\n');
}

// TODO: add tests for unescaped fields

