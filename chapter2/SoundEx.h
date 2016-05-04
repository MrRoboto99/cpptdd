#pragma once

#include <xstring>

// std::string SoundEx::Encode(const std::string& toEncode)
// 1.	Retain the first letter. Drop all other occurrences of a,e,i,o,u
// 2.	Replace consonants with digits (after the first letter):
//			b,f,p,v -> 1
//			c,g,j,k,q,s,x,z -> 2
//			d,t -> 3
//			l -> 4
//			m,n -> 5
//			r -> 6
// 3.	If two adjacent letters encode to the same number, encode them instead
//		as a single number. Also, do so if two letters with the same number are
//		separated by h or w (but code them twice separated by a vowel). This rule
//		also applies to the first letter.
// 4.	Stop when you have a letter and three digits. Zero-pad if needed.



class SoundEx
{
public:
	std::string Encode(const std::string& toEncode);

private:
	const size_t kMaxEncodingLength = 3;

	std::string EncodeCharacter(char character);
	bool IsLetterIgnored(char letter);

	std::string EncodeSignature(const std::string& toEncode);

	std::string PadZeros(const std::string& base);
};

