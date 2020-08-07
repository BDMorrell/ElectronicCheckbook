#include "csvTokenizer.h"

using namespace echeck::parser;
using namespace std;

csvTokenizer::csvTokenizer(istream *input)
{
  this->input = input;
}

csvTokenizer::~csvTokenizer()
{
  ;
}

string csvTokenizer::getField()
{
  int c = input->peek();
  if (c == EOF) {
    unexpectedEOF();
  } else if (c == '"') {
    return getEscapedField();
  } else {
    return getUnescapedField();
  }
}

string csvTokenizer::getEscapedField()
{
  int c = input->get(); // remove first DQUOTE
  string builder;
  while ((c = input->get()) != EOF) {
    if (c == '"') {
      if (input->peek() == '"') {
        input->get(); // advance input
        builder.push_back('"');
      } else {
        break; // end of field
      }
    } else if (c == '\x0d') { // CR
      if (input->peek() == '\x0a') {
        input->get(); // advance input
        builder.push_back('\n');
      } else {
        throw token_error("CR may not exist without a LF");
      }
    } else { // note: \x0a (LF) can pass right through. I'm assuming \x0a == \n
      builder.push_back((char) c);
    }
  }
  if (c == EOF) {
    throw parser_error("unexpected EOF when parsing an escaped");
  }
  return builder;
}

string csvTokenizer::getUnescapedField()
{
  int c;
  string builder;
  while ((c = input->get()) != EOF) {
    if (c == ',' || c == '\n') {
      break;
    } else if (c == '"') {
      throw token_error("a DQUOTE may not exist in a non-escaped");
    } else {
      builder.push_back((char) c);
    }
  }
  return builder;
}

void csvTokenizer::unexpectedEOF()
{
  throw parser_error("end of file");
}

