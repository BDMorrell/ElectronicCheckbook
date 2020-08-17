#include "gtest/gtest.h"
#include <string>
#include <sstream>
#include <vector>
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
    {"\"Hello\",\"How are you?\"", "Hello"},
    {"\"Hello\"\n\"How are you?\"", "Hello"}
  };
  int i = sizeof(in_out_pairs) / sizeof(*in_out_pairs);
  for (i -= 1; i >= 0; i--) { // backwards iterator
    EXPECT_EQ(testCSVTokenizerFromString(in_out_pairs[i][0]), in_out_pairs[i][1]);
  }
}

TEST(EscapedToken, UnfinishedField) {
  string shouldThrow[] = {
    "\"This doesn't fini",
    "\"\"\"Opens with escaped double quote",
    "\"Ends with escaped double quote \"\"",
    "\"\"\"Surrounded by escaped quotes\"\"",
    "\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"" // has odd number of escaped quotes
  };
  // I'm looking for either parser_error or token_error
  int i = sizeof(shouldThrow)/sizeof(*shouldThrow);
  for (i -= 1; i >= 0; i--) { // backwards iterator
    EXPECT_THROW(testCSVTokenizerFromString(shouldThrow[i]), parser_error);
  }
  // Just make sure it doesn't just throw all the time
  EXPECT_NO_THROW(testCSVTokenizerFromString("\"This does finish\""));
}

TEST(EscapedToken, IllegalCharacters) {
  EXPECT_THROW(testCSVTokenizerFromString("\"Hello\rThat should break\""), token_error);
}

TEST(EscapedToken, Assumptions) {
  ASSERT_EQ(0x0d, '\r');
  ASSERT_EQ(0x0a, '\n');
}

TEST(UnescapedToken, NormalUsage) {
  string in_out_pairs[][2] = {
    // can it handle the basics?
    {"This is intended", "This is intended"},
    // empty
    {"\n", ""},
    {",", ""},
    {"\r\n", ""},
    // A single token extraction?
    {"Hello,How are you?", "Hello"},
    {"Hello\nHow are you?", "Hello"}
  };
  int i = sizeof(in_out_pairs) / sizeof(*in_out_pairs);
  for (i -= 1; i >= 0; i--) { // backwards iterator
    EXPECT_EQ(testCSVTokenizerFromString(in_out_pairs[i][0]), in_out_pairs[i][1]);
  }
}

TEST(UnescapedToken, IllegalCharacters) {
  EXPECT_THROW(testCSVTokenizerFromString("Hello\rThat should break"), token_error);
  EXPECT_THROW(testCSVTokenizerFromString("Hello\"That should break"), token_error);
}

