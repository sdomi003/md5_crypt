#include <iostream>
#include <string>
#include "md5.h"
#include <sstream>
#include <iostream>
#include <bitset>


using std::string;using std::cout; using std::endl;
using std::stringstream;

string base64_cypt(string md5_str) {
	string md5_rearranged = "";
	// rearrange the bytes
	int mask_1 = 
	int mask_2 = 
	int mask_3 = 
	int mask_4 = 	
	return answer;
}

string md5_to_string(string md5) {
	string md5_str = "";
	stringstream cstream;
	int value;
	for (int i = 0; i < md5.length(); i += 2) {
		cstream.clear();
		cstream.str(string());
		string s = "";
		s.push_back(md5.at(i));	
		s.push_back(md5.at(i+1));
		cout << "s is " << s << endl;
		cstream << s;
		cstream >> std::hex >> value;
		// now turn value into a char and append to md5_str
		cout << "pushing int " << value << " which is char " << static_cast<char> (value) << endl;
		md5_str.push_back(static_cast<char> (value));
	}

	return md5_str;
}




int main() {
	string password = "zhgnnd";
	string salt = "hfT7jp2q";
	string magic = "$1$";
	string intermediate = "";
	string next_intermediate = "next_intermediate";	
	string alternate_sum = md5(password + salt + password);
	cout << "altermate sum hex: " << alternate_sum << endl;
	alternate_sum = md5_to_string(alternate_sum);
	cout << "alternate sum string: " << alternate_sum << endl;	
	
	intermediate += password;
	intermediate += magic;
	intermediate += salt;
	
	int len_password = password.length();
	
	int bytes_left = len_password;
	
	
	while (bytes_left >= 16) {
		intermediate += alternate_sum;
		bytes_left -= 16;
	}	

	for (int i = 0; i < bytes_left; ++i) {
		intermediate.push_back(alternate_sum.at(i));
	}

	std::bitset <16> len_pass_bits(len_password);
	int start = 15;
	while (!len_pass_bits.test(start)) {
		start -= 1;
	}

	for (std::size_t i = 0; i <= start; ++i) {
		if (len_pass_bits.test(i)) {
			intermediate.push_back('\0');
		} else {
			intermediate.push_back(password.at(0));
		}
	}
	
	intermediate = md5(intermediate);	
	cout << "intermediate_0: " << intermediate << endl;
	next_intermediate = md5_to_string(intermediate);

	for (int i = 0; i < 999; ++i) {
		intermediate = next_intermediate;
		next_intermediate = "";
		if (i % 2 == 0) {
			next_intermediate += intermediate;	
		} else {
			next_intermediate += password;
		}
		if (i % 3 != 0) {
			next_intermediate += salt;
		}
		if (i % 7 != 0) {
			next_intermediate += password;
		}
		if (i % 2 == 0) {
			next_intermediate += password;
		} else {
			next_intermediate += intermediate;
		}
		next_intermediate = md5_to_string(md5(next_intermediate));
	}
	int i = 999;
	intermediate = next_intermediate;
	next_intermediate = "";
	if (i % 2 == 0) {
		next_intermediate += intermediate;	
	} else {
		next_intermediate += password;
	}
	if (i % 3 != 0) {
		next_intermediate += salt;
	}
	if (i % 7 != 0) {
		next_intermediate += password;
	}
	if (i % 2 == 0) {
		next_intermediate += password;
	} else {
		next_intermediate += intermediate;
	}
	next_intermediate = md5(next_intermediate);

	// next_intermediate will be the last thing calculated
	string final_intermediate = next_intermediate;
	cout << "final intermediate " << final_intermediate << endl;
	final_intermediate = md5_to_string(final_intermediate);
	cout << base64_crypt(final_intermediate) << endl;	
	return 0;
}

// turn into bits then for every 6 bits left to right do base64[i] 
// last char will be either a . or / or 0








