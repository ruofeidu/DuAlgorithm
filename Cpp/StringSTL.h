#pragma once
#include "common.h"

namespace StringSTL {
	// O(N + M)
	void find() {
		string str("There are two needles in this haystack with needles.");
		string key("needle");

		size_t found = str.find(key);
		if (found != string::npos)
			cout << "first 'needle' found at: " << found << '\n';

		string str2("The sixth sick sheik's sixth sheep's sick.");
		string key2("sixth");

		found = str2.rfind(key2);
		if (found != std::string::npos)
			str2.replace(found, key2.length(), "seventh");

		cout << str << '\n';
	}

	void replace() {
		std::string base = "this is a test string.";
		std::string str2 = "n example";
		std::string str3 = "sample phrase";
		std::string str4 = "useful.";
		string str = base;				// "this is a test string."
		str.replace(9, 5, str2);          // "this is an example string." (1)
		str.replace(19, 6, str3, 7, 6);     // "this is an example phrase." (2)
		str.replace(8, 10, "just a");     // "this is just a phrase."     (3)
		str.replace(8, 6, "a shorty", 7);  // "this is a short phrase."    (4)
		str.replace(22, 1, 3, '!');        // "this is a short phrase!!!"  (5)
	}

	void erase() {
		std::string str("This is an example sentence.");
		std::cout << str << '\n';
		                                         // "This is an example sentence."
		str.erase(10, 8);                        //            ^^^^^^^^
		std::cout << str << '\n';
		                                          // "This is an sentence."
		str.erase(str.begin() + 9);               //           ^
		std::cout << str << '\n';
		                                            // "This is a sentence."
		str.erase(str.begin() + 5, str.end() - 9);  //       ^^^^^
		std::cout << str << '\n';

		// "This sentence."
	}
}
