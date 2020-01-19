#include <iostream>
#include <sstream>
#include <string>

using std::cout; using std::endl;

int main() {
std::stringstream str;
std::string s1 = "5f0066";
str << s1;
int value;
str >> std::hex >> value;


value = 56;
char* s = reinterpret_cast <char *>(&value);
cout << "*s: " << *s << endl;
cout << "s: " << s << endl;
cout << "value: " << value << endl;
return 0;
}
