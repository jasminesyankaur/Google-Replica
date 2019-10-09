#include "stemming.h"

//Stemmer
void Stemming::stem(std::string& word)
{
	size_t length = word.length();
	
	if(!Stemming::Builder::validWord(word, length))
		return;
	
	if(word[0] == '\'')
		word.erase(0, 1);
	
	Stemming::Builder::convertytoY(word);
	
	size_t R1 = Stemming::Builder::initialR1(word);
	size_t R2 = Stemming::Builder::initialR2(word, R1);
	
	Stemming::Steps::step0(word);
	if(!Stemming::Steps::step1A(word))
		return;
	Stemming::Steps::step1B(word, R1);
	Stemming::Steps::step1C(word);
	Stemming::Steps::step2(word, R1);
	Stemming::Steps::step3(word, R1, R2);
	Stemming::Steps::step4(word, R2);
	Stemming::Steps::step5(word, R1, R2);
	
	Stemming::Builder::convertYtoy(word);
}

//Stem steps
void Stemming::Steps::step0(std::string& word)
{
	Stemming::Builder::searchReplace(word, "'", "", 0);
	Stemming::Builder::searchReplace(word, "'s", "", 0);
	Stemming::Builder::searchReplace(word, "'s'", "", 0);
	
	return;
}
bool Stemming::Steps::step1A(std::string& word)
{
	size_t length = word.length();
	
	Stemming::Builder::searchReplace(word, "sses", "ss", 0);
	
	if(Stemming::Builder::suffixExists(word, "ied") && length > 4)
		Stemming::Builder::searchReplace(word, "ied", "i", 0);
	else if(Stemming::Builder::suffixExists(word, "ied") && length < 5)
		Stemming::Builder::searchReplace(word, "ied", "ie", 0);
	if(Stemming::Builder::suffixExists(word, "ies") && length > 4)
		Stemming::Builder::searchReplace(word, "ies", "i", 0);
	else if(Stemming::Builder::suffixExists(word, "ies") && length < 5)
		Stemming::Builder::searchReplace(word, "ies", "ie", 0);
	
	if(Stemming::Builder::suffixExists(word, "s") && !Stemming::Builder::suffixExists(word, "us") &&
		!Stemming::Builder::suffixExists(word, "ss") && Stemming::Builder::containsVowel(word, 0, length - 2))
		Stemming::Builder::searchReplace(word, "s", "", length - 1);
	
	//Special case
	std::vector<std::string> invariants = {	"inning", "outing", "canning", "herring", "earring", "proceed", "excced", "succeed"	};
	
	for(size_t i = 0; i < invariants.size(); ++i)
	{
		if(word == invariants[i])
			return false;

	}
	
	return true;
}
void Stemming::Steps::step1B(std::string& word, size_t R1)
{
	size_t length = word.length();

	if(Stemming::Builder::suffixExists(word, "eed"))
		Stemming::Builder::searchReplace(word, "eed", "ee", R1);
			
	if(Stemming::Builder::suffixExists(word, "eedly"))
		Stemming::Builder::searchReplace(word, "eedly", "ee", R1);
	
	if(Stemming::Builder::suffixExists(word, "ed") && Stemming::Builder::containsVowel(word, 0, length - 3))
	{
		Stemming::Builder::searchReplace(word, "ed", "", 0);
		if(Stemming::Builder::suffixExists(word, "at") || Stemming::Builder::suffixExists(word, "bl") ||
			Stemming::Builder::suffixExists(word, "iz") || Stemming::Builder::isShort(word, R1))
			word.push_back('e');
		else if(Stemming::Builder::isDouble(word[length - 2], word[length - 1]))
			word.pop_back();
	}
	if(Stemming::Builder::suffixExists(word, "edly") && Stemming::Builder::containsVowel(word, 0, length - 3))
	{
		Stemming::Builder::searchReplace(word, "edly", "", 0);
		if(Stemming::Builder::suffixExists(word, "at") || Stemming::Builder::suffixExists(word, "bl") ||
			Stemming::Builder::suffixExists(word, "iz") || Stemming::Builder::isShort(word, R1))
			word.push_back('e');
		else if(Stemming::Builder::isDouble(word[length - 2], word[length - 1]))
			word.pop_back();
	}
	if(Stemming::Builder::suffixExists(word, "ing") && Stemming::Builder::containsVowel(word, 0, length - 3))
	{
		Stemming::Builder::searchReplace(word, "ing", "", 0);
		if(Stemming::Builder::suffixExists(word, "at") || Stemming::Builder::suffixExists(word, "bl") ||
			Stemming::Builder::suffixExists(word, "iz") || Stemming::Builder::isShort(word, R1))
			word.push_back('e');
		else if(Stemming::Builder::isDouble(word[length - 2], word[length - 1]))
			word.pop_back();
	}
	if(Stemming::Builder::suffixExists(word, "ingly") && Stemming::Builder::containsVowel(word, 0, length - 3))
	{
		Stemming::Builder::searchReplace(word, "ingly", "", 0);
		if(Stemming::Builder::suffixExists(word, "at") || Stemming::Builder::suffixExists(word, "bl") ||
			Stemming::Builder::suffixExists(word, "iz") || Stemming::Builder::isShort(word, R1))
			word.push_back('e');
		else if(Stemming::Builder::isDouble(word[length - 2], word[length - 1]))
			word.pop_back();
	}
	
	return;
}
void Stemming::Steps::step1C(std::string& word)
{
	size_t length = word.length();
	
	if(length > 2 && word[length - 1] == 'y' && !Stemming::Builder::isVowel(word[length - 2]))
	{
		word.pop_back();
		word.push_back('i');
	}
	else if(length > 2 && word[length - 1] == 'Y' && !Stemming::Builder::isVowel(word[length - 2]))
	{
		word.pop_back();
		word.push_back('i');
	}
	
	return;
}
void Stemming::Steps::step2(std::string& word, size_t R1)
{
	size_t length = word.length();
	std::vector<std::vector<std::string> > suffixes = { { "tional", "tion" },
														{ "enci", "ence" },
														{ "anci", "ance" },
														{ "abli", "able" },
														{ "entli", "ent" },
														{ "izer", "ize" },
														{ "ization", "ize" },
														{ "ational", "ate" },
														{ "ation", "ate" },
														{ "ator", "ate" },
														{ "alism", "al" },
														{ "aliti", "al" },
														{ "alli", "al" },
														{ "filness", "ful" },
														{ "ousli", "ous" },
														{ "ousness", "ous" },
														{ "iveness", "ive" },
														{ "iviti", "ive" },
														{ "biliti", "ble" },
														{ "bli", "ble" },
														{ "fulli", "ful" },
														{ "lessli", "less" } };
	
	for(size_t i = 0; i < suffixes.size(); ++i)
	{
		if(Stemming::Builder::searchReplace(word, suffixes[i][0], suffixes[i][1], R1))
			return;
	}

	if(Stemming::Builder::suffixExists(word, "ogi") && word[length - 4] == 'l')
		Stemming::Builder::searchReplace(word, "ogi", "og", R1);
	
	if(Stemming::Builder::suffixExists(word, "li") && Stemming::Builder::isLIEnding(word[length - 3]))
		Stemming::Builder::searchReplace(word, "li", "", R1);
		
	return;
}
void Stemming::Steps::step3(std::string& word, size_t R1, size_t R2)
{
	std::vector<std::vector<std::string> > suffixes = { { "tional", "tion" },
														{ "ational", "ate" },
														{ "alize", "al"	   },
														{ "icate", "ic"    },
														{ "iciti", "ic"    },
														{ "ical", "ic"     },
														{ "ful", ""        },
														{ "ness", ""       } };
	
	for(size_t i = 0; i < suffixes.size(); ++i)
	{
		if(Stemming::Builder::searchReplace(word, suffixes[i][0], suffixes[i][1], R1))
			return;
	}
	Stemming::Builder::searchReplace(word, "ative", "", R2);
	
	return;
}
void Stemming::Steps::step4(std::string& word, size_t R2)
{
	std::vector<std::vector<std::string> > suffixes = { { "al", "" },
														{ "ance", "" },
														{ "ence", "" },
														{ "er", "" },
														{ "ic", "" },
														{ "able", "" },
														{ "ible", "" },
														{ "ant", "" },
														{ "ement", "" },
														{ "ment", "" },
														{ "ent", "" },
														{ "ism", "" },
														{ "ate", "" },
														{ "iti", "" },
														{ "ous", "" },
														{ "ive", "" },
														{ "ize", "" } };
														
	for(size_t i = 0; i < suffixes.size(); ++i)
	{
		if(Stemming::Builder::searchReplace(word, suffixes[i][0], suffixes[i][1], R2))
			return;
	}
	
	Stemming::Builder::searchReplace(word, "sion", "s", R2 - 1);
	Stemming::Builder::searchReplace(word, "tion", "t", R2 - 1);
	
	return;
}
void Stemming::Steps::step5(std::string& word, size_t R1, size_t R2)
{
	size_t length = word.length();
	std::string temp = word.substr(0, length - 1);
	
	if(word[length - 1] == 'e')
		Stemming::Builder::searchReplace(word, "e", "", R2);
	if(word[length - 1] == 'e' && !Stemming::Builder::doesEndShort(temp))
		Stemming::Builder::searchReplace(word, "e", "", R1);
	if(word[length - 1] == 'l' && word[length - 2] == 'l')
		Stemming::Builder::searchReplace(word, "l", "", R2);
	
	return;
}

//Stem internal functions
bool Stemming::Builder::validWord(std::string& word, size_t length)
{
	if(length < 3)
		return false;
	
	std::vector<std::vector<std::string> > specialStem = {	{	"skis", "ski"		},
															{	"skies", "sky"		},
															{	"dying", "die"		},
															{	"lying", "lie"		},
															{	"tying", "tie"		},
															{	"idly", "idl"		},
															{	"gently", "gentl"	},
															{	"ugly", "ugli"		},
															{	"early", "earli"	},
															{	"only", "onli"		},
															{	"singly", "singl"	}	};
															
	for(size_t i = 0; i < specialStem.size(); ++i)
	{
		if(word == specialStem[i][0])
		{
			word = specialStem[i][1];
			return false;
		}
	}
	
	std::vector<std::string> invariants = {	"sky", "news", "howe", "atlas", "cosmos", "bias", "andes"	};
	
	for(size_t i = 0; i < invariants.size(); ++i)
	{
		if(word == invariants[i])
			return false;

	}
	
	return true;
}
bool Stemming::Builder::isVowel(char c)
{
	return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}
bool Stemming::Builder::isVowelY(char c)
{
	return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y';
}
bool Stemming::Builder::isDouble(char c1, char c2)
{
	if(c1 == c2)
		return !isVowel(c1);
	else
		return false;
}
bool Stemming::Builder::isLIEnding(char c)
{
	return c == 'c' || c == 'd' || c == 'e' || c == 'g' || c == 'h' || c == 'k' || c == 'm' || c == 'n' || c == 'r' ||
		c == 't';
}
bool Stemming::Builder::doesEndShort(std::string& word)
{
	size_t length = word.length();
	
	if(length > 2)
	{
		return isVowelY(word[length - 2]) && !isVowelY(word[length - 1]) &&word[length - 1] != 'w' 
			&& word[length - 1] != 'x' && word[length - 1] != 'Y' && !isVowel(word[length - 3]);
	}
	
	return length == 2 && isVowelY(word[0]) && !isVowelY(word[1]);
}
bool Stemming::Builder::isShort(std::string& word, size_t R1)
{
	return doesEndShort(word) && R1 == word.length();
}
void Stemming::Builder::convertytoY(std::string& word)
{
	if(word[0] == 'y')
		word[0] = 'Y';
	
	for(size_t i = 1; i < word.length(); ++i)
	{
		if(word[i] == 'y')
		{
			if(isVowel(word[i - 1]))
				word[i] = 'Y';
		}
	}
	return;
}
size_t Stemming::Builder::initialR1 (std::string& word)
{
	firstConsanantAfterVowel(word, 1);
}
size_t Stemming::Builder::initialR2 (std::string& word, size_t R1)
{
	firstConsanantAfterVowel(word, R1);
}
size_t Stemming::Builder::firstConsanantAfterVowel(std::string&word, size_t first)
{
	for(size_t i = first; i < word.length(); ++i)
	{
		if(!isVowelY(word[i]) && isVowelY(word[i - 1]))
			return i + 1;
	}
	return word.length();
}
bool Stemming::Builder::searchReplace(std::string& word, std::string toSearch, std::string toReplace, size_t first)
{
	size_t pos = word.find(toSearch, first);
	if(pos != std::string::npos)
	{
		word.replace(pos, toSearch.length(), toReplace);
		return true;
	}
	else
		return false;
}
bool Stemming::Builder::suffixExists(std::string& word, std::string suffix)
{
	size_t suffixLength = suffix.length();
	size_t wordLength = word.length();
	
	if(suffixLength > wordLength)
		return false;
	
	std::string check = word.substr(wordLength - suffixLength);
	
	return check == suffix;
}
bool Stemming::Builder::containsVowel(std::string& word, size_t first, size_t last)
{
	for(size_t i = first; i < last; ++i)
	{
		if(isVowelY(word[i]))
			return true;
	}
	
	return false;
}
void Stemming::Builder::convertYtoy(std::string& word)
{
	for(size_t i = 0; i < word.length(); ++i)
	{
		if(word[i] == 'Y')
			word[i] = 'y';
	}
	return;
}
