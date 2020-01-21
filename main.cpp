#include <iostream>
#include <string>
#include "md5.h"
#include <sstream>
#include <iostream>
#include <bitset>
#include <thread>

using std::string;using std::cout; using std::endl;
using std::stringstream;


// input 32-character string representing 16-bytes in hex
string base64_crypt(string md5_str) {
	char crypt_base64_set[] = {'.','/','0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};	

	string md5_rearranged_1 = "";
	string md5_rearranged_2 = "";
	string md5_rearranged_3 = "";
	string md5_rearranged_4 = "";
	string md5_rearranged_5 = "";
	

	md5_rearranged_1.push_back(md5_str.at(0));
	md5_rearranged_1.push_back(md5_str.at(1));
	md5_rearranged_1.push_back(md5_str.at(12));
	md5_rearranged_1.push_back(md5_str.at(13));
	md5_rearranged_1.push_back(md5_str.at(24));
	md5_rearranged_1.push_back(md5_str.at(25));	


	md5_rearranged_2.push_back(md5_str.at(2));
	md5_rearranged_2.push_back(md5_str.at(3));
	md5_rearranged_2.push_back(md5_str.at(14));
	md5_rearranged_2.push_back(md5_str.at(15));
	md5_rearranged_2.push_back(md5_str.at(26));
	md5_rearranged_2.push_back(md5_str.at(27));	


	md5_rearranged_3.push_back(md5_str.at(4));
	md5_rearranged_3.push_back(md5_str.at(5));
	md5_rearranged_3.push_back(md5_str.at(16));
	md5_rearranged_3.push_back(md5_str.at(17));
	md5_rearranged_3.push_back(md5_str.at(28));
	md5_rearranged_3.push_back(md5_str.at(29));	


	md5_rearranged_4.push_back(md5_str.at(6));
	md5_rearranged_4.push_back(md5_str.at(7));
	md5_rearranged_4.push_back(md5_str.at(18));
	md5_rearranged_4.push_back(md5_str.at(19));
	md5_rearranged_4.push_back(md5_str.at(30));
	md5_rearranged_4.push_back(md5_str.at(31));

	md5_rearranged_5.push_back(md5_str.at(8));
	md5_rearranged_5.push_back(md5_str.at(9));
	md5_rearranged_5.push_back(md5_str.at(20));
	md5_rearranged_5.push_back(md5_str.at(21));
	md5_rearranged_5.push_back(md5_str.at(10));
	md5_rearranged_5.push_back(md5_str.at(11));


	// rearrange the bytes
	unsigned int last_6_bits_mask = 0x00003F; 
	unsigned int group_1;
	unsigned int group_2;
	unsigned int group_3;
	unsigned int group_4;
	unsigned int group_5;
	//cout << "Test 1 after push back: " << md5_rearranged_1 << endl;	
	stringstream cstream;
	cstream.clear();
	cstream.str(string());
	cstream << md5_rearranged_1;
	cstream >> std::hex >> group_1; 

	cstream.clear();
	cstream.str(string());
	cstream << md5_rearranged_2;
	cstream >> std::hex >> group_2;

	cstream.clear();
	cstream.str(string());
	cstream << md5_rearranged_3;
	cstream >> std::hex >> group_3;

	cstream.clear();
	cstream.str(string());
	cstream << md5_rearranged_4;
	cstream >> std::hex >> group_4;

	cstream.clear();
	cstream.str(string());
	cstream << md5_rearranged_5;
	cstream >> std::hex >> group_5;
	
	string answer = "";
	
	// 3*8 = 24
	// 24 / 6 = 4
	int res = 0;
	for (int i = 0; i < 4; ++i) {
		res = last_6_bits_mask & group_1;
		answer.push_back(crypt_base64_set[res]);
		group_1 = group_1 >> 6;
	}
		
	for (int i = 0; i < 4; ++i) {
		res = last_6_bits_mask & group_2;
		answer.push_back(crypt_base64_set[res]);
		group_2 = group_2 >> 6;
	}


	for (int i = 0; i < 4; ++i) {
		res = last_6_bits_mask & group_3;
		answer.push_back(crypt_base64_set[res]);
		group_3 = group_3 >> 6;
	}

	for (int i = 0; i < 4; ++i) {
		res = last_6_bits_mask & group_4;
		answer.push_back(crypt_base64_set[res]);
		group_4 = group_4 >> 6;
	}

	for (int i = 0; i < 4; ++i) {
		res = last_6_bits_mask & group_5;
		answer.push_back(crypt_base64_set[res]);
		group_5 = group_5 >> 6;
	}

	// handle the last byte seperately
	// 8 bits, mask six, move over six

	string byte_11 = "";
	int byte_11_int = 0;
	byte_11.push_back(md5_str.at(22));
	byte_11.push_back(md5_str.at(23));
	//cout << "byte 11: " << byte_11 << endl;	
	cstream.clear();
	cstream.str(string());
	cstream << byte_11;
	cstream >> std::hex >> byte_11_int;
	
	res = (0x3F) & byte_11_int;
	answer.push_back(crypt_base64_set[res]);
	byte_11_int = byte_11_int >> 6;
	
	res = 0x03 & byte_11_int;
	answer.push_back(crypt_base64_set[res]);

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
		//cout << "s is " << s << endl;
		cstream << s;
		cstream >> std::hex >> value;
		// now turn value into a char and append to md5_str
		//cout << "pushing int " << value << " which is char " << static_cast<char> (value) << endl;
		md5_str.push_back(static_cast<char> (value));
	}

	return md5_str;
}


string md5_crypt(string password, string salt, string magic) {
	string intermediate = "";
	string next_intermediate = "next_intermediate";	
	string alternate_sum = md5(password + salt + password);
	//cout << "altermate sum hex: " << alternate_sum << endl;
	alternate_sum = md5_to_string(alternate_sum);
	//cout << "alternate sum string: " << alternate_sum << endl;	
	
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
	//cout << "intermediate_0: " << intermediate << endl;
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
	//cout << "final intermediate " << final_intermediate << endl;
	//final_intermediate = md5_to_string(final_intermediate);
	//cout << base64_crypt(final_intermediate) << endl;	

	return base64_crypt(final_intermediate);
}

void six_1 () {	
	string hashed_password = "jXUpzhJaegsl6uwrGhMBW0";	
	string password = "";
	string salt = "4fTgjp6q";
	string magic = "$1$";
	//cout << md5_crypt(password, salt, magic) << endl;
	char alphabet[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	string guess_6 = "aaaaaa";

	int i = 0;
	int j = 0;
	int k = 0;
	int x = 0;
	int v = 0;
	int l = 0;
	// guess_6
	for (l = 0; l < 4; ++l) {
		guess_6[0] = alphabet[l];
		for (v = 0; v < 26; ++v) {
			guess_6[1] = alphabet[v];
			for (x = 0; x < 26; ++x) {
				guess_6[2] = alphabet[x];
				for (i = 0; i< 26; ++i) {
					guess_6[3] = alphabet[i];
					for (j = 0; j < 26; ++j) {
						guess_6[4] = alphabet[j];
						for (k = 0; k < 26; ++k) {
							guess_6[5] = alphabet[k];
							if (md5_crypt( guess_6,  salt,  magic) == hashed_password) {
								cout << "FOUND: " << guess_6 << endl;
							}
							//cout << guess_6 << endl;
						}	
					}
				}
			}
		}
	}
}

void six_2 () {	
	string hashed_password = "jXUpzhJaegsl6uwrGhMBW0";	
	string password = "";
	string salt = "4fTgjp6q";
	string magic = "$1$";
	//cout << md5_crypt(password, salt, magic) << endl;
	char alphabet[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	string guess_6 = "aaaaaa";

	int i = 0;
	int j = 0;
	int k = 0;
	int x = 0;
	int v = 0;
	int l = 0;
	// guess_6
	for (l = 4; l < 8; ++l) {
		guess_6[0] = alphabet[l];
		for (v = 0; v < 26; ++v) {
			guess_6[1] = alphabet[v];
			for (x = 0; x < 26; ++x) {
				guess_6[2] = alphabet[x];
				for (i = 0; i< 26; ++i) {
					guess_6[3] = alphabet[i];
					for (j = 0; j < 26; ++j) {
						guess_6[4] = alphabet[j];
						for (k = 0; k < 26; ++k) {
							guess_6[5] = alphabet[k];
							if (md5_crypt( guess_6,  salt,  magic) == hashed_password) {
								cout << "FOUND: " << guess_6 << endl;
							}
							//cout << guess_6 << endl;
						}	
					}
				}
			}
		}
	}
}
void six_3 () {	
	string hashed_password = "jXUpzhJaegsl6uwrGhMBW0";	
	string password = "";
	string salt = "4fTgjp6q";
	string magic = "$1$";
	//cout << md5_crypt(password, salt, magic) << endl;
	char alphabet[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	string guess_6 = "aaaaaa";

	int i = 0;
	int j = 0;
	int k = 0;
	int x = 0;
	int v = 0;
	int l = 0;
	// guess_6
	for (l = 8; l < 12; ++l) {
		guess_6[0] = alphabet[l];
		for (v = 0; v < 26; ++v) {
			guess_6[1] = alphabet[v];
			for (x = 0; x < 26; ++x) {
				guess_6[2] = alphabet[x];
				for (i = 0; i< 26; ++i) {
					guess_6[3] = alphabet[i];
					for (j = 0; j < 26; ++j) {
						guess_6[4] = alphabet[j];
						for (k = 0; k < 26; ++k) {
							guess_6[5] = alphabet[k];
							if (md5_crypt( guess_6,  salt,  magic) == hashed_password) {
								cout << "FOUND: " << guess_6 << endl;
							}
							//cout << guess_6 << endl;
						}	
					}
				}
			}
		}
	}
}
void six_4 () {	
	string hashed_password = "jXUpzhJaegsl6uwrGhMBW0";	
	string password = "";
	string salt = "4fTgjp6q";
	string magic = "$1$";
	//cout << md5_crypt(password, salt, magic) << endl;
	char alphabet[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	string guess_6 = "aaaaaa";

	int i = 0;
	int j = 0;
	int k = 0;
	int x = 0;
	int v = 0;
	int l = 0;
	// guess_6
	for (l = 12; l < 16; ++l) {
		guess_6[0] = alphabet[l];
		for (v = 0; v < 26; ++v) {
			guess_6[1] = alphabet[v];
			for (x = 0; x < 26; ++x) {
				guess_6[2] = alphabet[x];
				for (i = 0; i< 26; ++i) {
					guess_6[3] = alphabet[i];
					for (j = 0; j < 26; ++j) {
						guess_6[4] = alphabet[j];
						for (k = 0; k < 26; ++k) {
							guess_6[5] = alphabet[k];
							if (md5_crypt( guess_6,  salt,  magic) == hashed_password) {
								cout << "FOUND: " << guess_6 << endl;
							}
							//cout << guess_6 << endl;
						}	
					}
				}
			}
		}
	}
}
void six_5 () {	
	string hashed_password = "jXUpzhJaegsl6uwrGhMBW0";	
	string password = "";
	string salt = "4fTgjp6q";
	string magic = "$1$";
	//cout << md5_crypt(password, salt, magic) << endl;
	char alphabet[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	string guess_6 = "aaaaaa";

	int i = 0;
	int j = 0;
	int k = 0;
	int x = 0;
	int v = 0;
	int l = 0;
	// guess_6
	for (l = 16; l < 20; ++l) {
		guess_6[0] = alphabet[l];
		for (v = 0; v < 26; ++v) {
			guess_6[1] = alphabet[v];
			for (x = 0; x < 26; ++x) {
				guess_6[2] = alphabet[x];
				for (i = 0; i< 26; ++i) {
					guess_6[3] = alphabet[i];
					for (j = 0; j < 26; ++j) {
						guess_6[4] = alphabet[j];
						for (k = 0; k < 26; ++k) {
							guess_6[5] = alphabet[k];
							if (md5_crypt( guess_6,  salt,  magic) == hashed_password) {
								cout << "FOUND: " << guess_6 << endl;
							}
							//cout << guess_6 << endl;
						}	
					}
				}
			}
		}
	}
}


void six_6 () {	
	string hashed_password = "jXUpzhJaegsl6uwrGhMBW0";	
	string password = "";
	string salt = "4fTgjp6q";
	string magic = "$1$";
	//cout << md5_crypt(password, salt, magic) << endl;
	char alphabet[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	string guess_6 = "aaaaaa";

	int i = 0;
	int j = 0;
	int k = 0;
	int x = 0;
	int v = 0;
	int l = 0;
	// guess_6
	for (l = 20; l < 24; ++l) {
		guess_6[0] = alphabet[l];
		for (v = 0; v < 26; ++v) {
			guess_6[1] = alphabet[v];
			for (x = 0; x < 26; ++x) {
				guess_6[2] = alphabet[x];
				for (i = 0; i< 26; ++i) {
					guess_6[3] = alphabet[i];
					for (j = 0; j < 26; ++j) {
						guess_6[4] = alphabet[j];
						for (k = 0; k < 26; ++k) {
							guess_6[5] = alphabet[k];
							if (md5_crypt( guess_6,  salt,  magic) == hashed_password) {
								cout << "FOUND: " << guess_6 << endl;
							}
							//cout << guess_6 << endl;
						}	
					}
				}
			}
		}
	}
}

void six_7 () {	
	string hashed_password = "jXUpzhJaegsl6uwrGhMBW0";	
	string password = "";
	string salt = "4fTgjp6q";
	string magic = "$1$";
	//cout << md5_crypt(password, salt, magic) << endl;
	char alphabet[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	string guess_6 = "aaaaaa";

	int i = 0;
	int j = 0;
	int k = 0;
	int x = 0;
	int v = 0;
	int l = 0;
	// guess_6
	for (l = 24; l < 26; ++l) {
		guess_6[0] = alphabet[l];
		for (v = 0; v < 26; ++v) {
			guess_6[1] = alphabet[v];
			for (x = 0; x < 26; ++x) {
				guess_6[2] = alphabet[x];
				for (i = 0; i< 26; ++i) {
					guess_6[3] = alphabet[i];
					for (j = 0; j < 26; ++j) {
						guess_6[4] = alphabet[j];
						for (k = 0; k < 26; ++k) {
							guess_6[5] = alphabet[k];
							if (md5_crypt( guess_6,  salt,  magic) == hashed_password) {
								cout << "FOUND: " << guess_6 << endl;
							}
							//cout << guess_6 << endl;
						}	
					}
				}
			}
		}
	}
}



void guesses_one_to_three() {

	string hashed_password = "jXUpzhJaegsl6uwrGhMBW0";	
	string password = "";
	string salt = "4fTgjp6q";
	string magic = "$1$";
	//cout << md5_crypt(password, salt, magic) << endl;
	char alphabet[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	string guess_1 = "a";
	string guess_2 = "aa";
	string guess_3 = "aaa";
	string guess_4 = "aaaa";


	int i = 0;
	int j = 0;
	int k = 0;
	int x = 0;
	int v = 0;
	int l = 0;

	// guess_1
	for (k = 0; k < 26; ++k) {
		guess_1[0] = alphabet[k];
		if (md5_crypt( guess_1,  salt,  magic) == hashed_password) {
			cout << "FOUND: " << guess_1 << endl;
		}
	}
	
	// guess_2
	for (j = 0; j < 26; ++j) {
		guess_2[0] = alphabet[j];
		for (k = 0; k < 26; ++k) {
			guess_2[1] = alphabet[k];
			//cout << guess_2 << endl;
			if (md5_crypt( guess_2,  salt,  magic) == hashed_password) {
				cout << "FOUND: " << guess_2 << endl;
			}
		}	
	}

	// guess_3
	for (i = 0; i< 26; ++i) {
		guess_3[0] = alphabet[i];
		for (j = 0; j < 26; ++j) {
			guess_3[1] = alphabet[j];
			for (k = 0; k < 26; ++k) {
				guess_3[2] = alphabet[k];
				if (md5_crypt( guess_3,  salt,  magic) == hashed_password) {
					cout << "FOUND: " << guess_3 << endl;
				}	
				//cout << guess_3 << endl;
			}	
		}
		
	}


}


void guess_4(){
	string hashed_password = "jXUpzhJaegsl6uwrGhMBW0";	
	string password = "";
	string salt = "4fTgjp6q";
	string magic = "$1$";
	//cout << md5_crypt(password, salt, magic) << endl;
	char alphabet[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	string guess_4 = "aaaa";
	int i = 0;
	int j = 0;
	int k = 0;
	int x = 0;
	int v = 0;
	int l = 0;
	// guess_4
	for (x = 0; x < 26; ++x) {
		guess_4[0] = alphabet[x];
		for (i = 0; i< 26; ++i) {
			guess_4[1] = alphabet[i];
			for (j = 0; j < 26; ++j) {
				guess_4[2] = alphabet[j];
				for (k = 0; k < 26; ++k) {
					guess_4[3] = alphabet[k];	
					if (md5_crypt( guess_4,  salt,  magic) == hashed_password) {
						cout << "FOUND: " << guess_4 << endl;
					}
					//cout << guess_4 << endl;
				}	
			}
		}
	}
}


void guess_5_1() {
	string hashed_password = "jXUpzhJaegsl6uwrGhMBW0";	
	string password = "";
	string salt = "4fTgjp6q";
	string magic = "$1$";
	//cout << md5_crypt(password, salt, magic) << endl;
	char alphabet[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	string guess_5 = "aaaaa";
	int i = 0;
	int j = 0;
	int k = 0;
	int x = 0;
	int v = 0;
	int l = 0;	
	// guess_5
	for (v = 0; v < 15; ++v) {
		guess_5[0] = alphabet[v];
		for (x = 0; x < 26; ++x) {
			guess_5[1] = alphabet[x];
			for (i = 0; i< 26; ++i) {
				guess_5[2] = alphabet[i];
				for (j = 0; j < 26; ++j) {
					guess_5[3] = alphabet[j];
					for (k = 0; k < 26; ++k) {
						guess_5[4] = alphabet[k];
						if (md5_crypt(guess_5, salt, magic) == hashed_password) {
							cout << "FOUND: " << guess_5 << endl;
						}
						//cout << guess_5 << endl;
					}	
				}
			}
		}
	}

}



void guess_5_2() {
	string hashed_password = "jXUpzhJaegsl6uwrGhMBW0";	
	string password = "";
	string salt = "4fTgjp6q";
	string magic = "$1$";
	//cout << md5_crypt(password, salt, magic) << endl;
	char alphabet[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};	
	string guess_5 = "aaaaa";
	int i = 0;
	int j = 0;
	int k = 0;
	int x = 0;
	int v = 0;
	int l = 0;	
	// guess_5
	for (v = 15; v < 26; ++v) {
		guess_5[0] = alphabet[v];
		for (x = 0; x < 26; ++x) {
			guess_5[1] = alphabet[x];
			for (i = 0; i< 26; ++i) {
				guess_5[2] = alphabet[i];
				for (j = 0; j < 26; ++j) {
					guess_5[3] = alphabet[j];
					for (k = 0; k < 26; ++k) {
						guess_5[4] = alphabet[k];
						if (md5_crypt(guess_5, salt, magic) == hashed_password) {
							cout << "FOUND: " << guess_5 << endl;
						}
						//cout << guess_5 << endl;
					}	
				}
			}
		}
	}

}

int main() {
	
	std::thread thread_1(guesses_one_to_three);
	std::thread thread_2(guess_4);
	std::thread thread_3(guess_5_1);
	std::thread thread_4(guess_5_2);	
	
	thread_1.join();
	thread_2.join();
	thread_3.join();
	thread_4.join();

	std::thread thread_6(six_1);
	std::thread thread_7(six_2);
	std::thread thread_8(six_3);
	std::thread thread_9(six_4);
	std::thread thread_10(six_5);
	std::thread thread_11(six_6);
	std::thread thread_12(six_7);

	thread_6.join();
	thread_7.join();
	thread_8.join();
	thread_9.join();
	thread_10.join();
	thread_11.join();
	thread_12.join();

	return 0;
}



