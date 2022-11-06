#include "tools.h"

using namespace std;


string Tools::decorate_text(string text, int length, int padside) {
  return text.length() >= length ? text : padside == LEFT ? string(length - text.length(), ' ') + text : text + string(length - text.length(), ' ');
}

string Tools::itos(int number) {
  ostringstream oss;
  oss << number;
  return oss.str();
}

int Tools::mystoi(string number) {
  int n;
  stringstream ss;
  ss << number;
  ss >> n;
  return n;
}

vector<string> Tools::split(string statement, char delimeter) {
	vector<string> result;
	string token;
	for(int i=0; i<statement.length(); i++)
		if(statement[i] != delimeter)
			token += statement[i];
		else if(token.length()) {
			result.push_back(token);
			token = "";
		}
	if(token.length())
		result.push_back(token);
	return result;
}
