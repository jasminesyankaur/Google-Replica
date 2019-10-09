#ifndef _STEMMING_H_
#define _STEMMING_H_

#include <vector>
#include <string>

namespace Stemming //group all stemming functions
{
	void stem(std::string& word); //performs porter stemming on a word
	
	namespace Builder //group functions that build into porter stemmer
	{
		bool validWord(std::string& word, size_t length); //checks if the word satisfies all constraints and if not, returns false, exiting the stemmer
		bool isVowel(char c); //checks if a letter is a vowel (a e i o u) may not be needed
		bool isVowelY(char c); //checks if a letter is a vowel (a e i o u y)
		bool isDouble(char c1, char c2); //checks if two characters are a double consonant
		bool isLIEnding(char c); //checks if the -li ending would be valid
		bool doesEndShort(std::string& word); //checks if a word ends with a short syllable
		bool isShort(std::string& word, size_t R1); //checks if a word itself is short (in R1 and ends with short syllable)
		void convertytoY(std::string& word); //converts all consonant y's to uppercase Y (to distinguish from vowel y's)
		size_t initialR1(std::string& word); //return the initial position of the R1 region
		size_t initialR2(std::string& word, size_t R1); //return the initial position of the R2 region
		size_t firstConsanantAfterVowel(std::string&word, size_t first); //return the first consonant after a vowel (for R1 and R2)
		bool searchReplace(std::string& word, std::string toSearch, std::string toReplace, size_t pos);
		bool suffixExists(std::string& word, std::string suffix); //check if a given suffix exists in a word
		bool containsVowel(std::string& word, size_t first, size_t last); //checks if a given word contains a vowel from given start to given finish
		void convertYtoy(std::string& word); //converts all consonant Y's to lowercase y (to reset word to original form)
	}
	namespace Steps //group step functions in porter algorithm (porter2)
	{
		void step0(std::string& word); //remove longest among suffixes (', 's, 's')
		bool step1A(std::string& word); //perform action on longest among suffixes (sses -> ss, ied/ies -> i*/ie, delete s*, leave us/ss)
		void step1B(std::string& word, size_t R1); //perform action on longest among suffixes (eed/eedly -> ee*, remove ed/edly/ing/ingly and add e or remove last letter*)
		void step1C(std::string& word); //replace suffix y/Y with i if preceded by a non vowel which is not the first letter in the word
		void step2(std::string& word, size_t R1); //perform more replacement (tional -> tion, enci -> ...)
		void step3(std::string& word, size_t R1, size_t R2); //perform more replacement if found in R1 (tional -> tion, ational -> ate, alize -> al, icate/iciti/ical -> ic, remove ful/ness, remove ative)
		void step4(std::string& word, size_t R2); //remove if found in R2 (al/ance/ence/er/ic/able/ible/ant/ement/ment/ent/ism/ate/iti/ous/ive/ize, ion if preceded by s or t)
		void step5(std::string& word, size_t R1, size_t R2); //delete e if in R2, or R1 and not preceded by short syllable, delete l if in R2 and preceded by l
	}
}

#endif
