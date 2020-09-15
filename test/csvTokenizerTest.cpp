#include "gtest/gtest.h"
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <exception>
#include <stdexcept>
#include "parser/parseErrors.h"
#include "parser/csvTokenizer.h"

using namespace echeck::parser;
using namespace std;

// helper objects

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

vector<string> testGetRow(string str)
{
  csvTokenizerFromString ctfs(str);
  return ctfs.izer->getRow();
}

string testGetField(string str)
{
  csvTokenizerFromString ctfs(str);
  return ctfs.izer->getField();
}

// general tests

TEST(csvTokenizer, Assumptions) {
  ASSERT_EQ(0x0d, '\r');
  ASSERT_EQ(0x0a, '\n');
}

TEST(csvTokenizer, advanceInput) {
  istringstream iss("ab");
  ASSERT_EQ(iss.peek(), 'a');
  csvTokenizer ct(&iss);
  ASSERT_EQ(iss.peek(), 'a');
  ct.advanceInput();
  ASSERT_EQ(iss.peek(), 'b');
}

// tests for csvTokenizer::getRow()

TEST(csvTokenizer_getRow, Empty) {
  string input = "";
  ASSERT_THROW(testGetRow(input), token_error);
}

TEST(csvTokenizer_getRow, NormalUsage) {
  string input = "148,\" Hello, there,\"\" said the old man\",it was a while before he returned.,,";
  vector<string> expected = {"148", " Hello, there,\" said the old man", "it was a while before he returned.", "", ""};
  vector<string> output = testGetRow(input);
  if (expected.size() != output.size()) {
    FAIL();
  }
  EXPECT_TRUE(std::equal(output.begin(), output.end(), expected.begin()));
}

TEST(csvTokenizer_getRow, BlankFields) {
  string input = ",,";
  vector<string> expected = {"", "", ""};
  vector<string> output = testGetRow(input);
  if (expected.size() != output.size()) {
    FAIL();
  }
  EXPECT_TRUE(std::equal(output.begin(), output.end(), expected.begin()));
}

TEST(csvTokenizer_getRow, BlankFields2) {
  string input = ",,\n,,";
  vector<string> expected = {"", "", ""};
  vector<string> output = testGetRow(input);
  if (expected.size() != output.size()) {
    FAIL();
  }
  EXPECT_TRUE(std::equal(output.begin(), output.end(), expected.begin()));
}

TEST(csvTokenizer_getRow, MultipleRows) {
  string input = "148,149,150,151\n1,2,3,4\n5,6,7,8";
  vector<string> expected = {"148", "149", "150", "151"};
  vector<string> output = testGetRow(input);
  if (expected.size() != output.size()) {
    cout << expected.size() << "!=" << output.size() << endl;
    FAIL();
  }
  EXPECT_TRUE(std::equal(output.begin(), output.end(), expected.begin()));
}

// tests for csvTokenizer::getField()
TEST(csvTokenizer_getField, EmptyInput) {
  EXPECT_EQ(testGetField(""),"");
}

TEST(csvTokenizer_EscapedToken, NormalUsage) {
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
  }; int i = sizeof(in_out_pairs) / sizeof(*in_out_pairs);
  for (i -= 1; i >= 0; i--) { // backwards iterator
    EXPECT_EQ(testGetField(in_out_pairs[i][0]), in_out_pairs[i][1]);
  }
}

TEST(csvTokenizer_EscapedToken, UnfinishedField) {
  string shouldThrow[] = {
    "\"This doesn't fini",
    "\"\"\"Opens with escaped double quote",
    "\"Ends with escaped double quote \"\"",
    "\"\"\"Surrounded by escaped quotes\"\"",
    "\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"" // has odd number of escaped quotes
  };
  int i = sizeof(shouldThrow)/sizeof(*shouldThrow);
  for (i -= 1; i >= 0; i--) { // backwards iterator
    EXPECT_THROW(testGetField(shouldThrow[i]), token_error);
  }
  // Just make sure it doesn't just throw all the time
  EXPECT_NO_THROW(testGetField("\"This does finish\""));
}

TEST(csvTokenizer_EscapedToken, IllegalCharacters) {
  EXPECT_THROW(testGetField("\"Hello\rThat should break\""), token_error);
}

TEST(csvTokenizer_UnescapedToken, NormalUsage) {
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
    EXPECT_EQ(testGetField(in_out_pairs[i][0]), in_out_pairs[i][1]);
  }
}

TEST(csvTokenizer_UnescapedToken, IllegalCharacters) {
  EXPECT_THROW(testGetField("Hello\rThat should break"), token_error);
  EXPECT_THROW(testGetField("Hello\"That should break"), token_error);
}

