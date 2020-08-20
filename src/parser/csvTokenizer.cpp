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

vector<string> csvTokenizer::getRow()
{
  // thought: support an expected initial size hint
  vector<string> fields;
  while (input->peek() == ',') {
    fields.push_back(getField());
  }
  if (input->peek() == '\r') {
    input->putback(handleCRLF());
  }
  if (input->peek() == '\n') {
    advanceInput();
  }
  return fields;
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

void csvTokenizer::advanceInput()
{
  input->get();
}

string csvTokenizer::getEscapedField()
{
  int c = input->get(); // remove first DQUOTE
  string builder;
  while ((c = input->get()) != EOF) {
    if (c == '"') {
      if (input->peek() == '"') {
        advanceInput();
        builder.push_back('"');
      } else {
        break; // end of field
      }
    } else if (c == '\r') { // CR
      builder.push_back(handleCRLF());
    } else { // note: \n (LF) can pass right through.
      builder.push_back((char) c);
    }
  }
  if (c == EOF) {
    throw token_error("unexpected EOF when parsing an escaped");
  }
  return builder;
}

string csvTokenizer::getUnescapedField()
{
  int c;
  string builder;
  while ((c = input->get()) != EOF) {
    if (c == '\r') { // CR
      c = handleCRLF();
    }
    if (c == ',' || c == '\n') {
      input->putback(c);
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
  throw token_error("end of file");
}

char csvTokenizer::handleCRLF()
{
  if (input->peek() == '\n') {
    advanceInput();
    return '\n';
  } else {
    throw token_error("CR may not exist without a LF");
  }
}
