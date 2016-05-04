#include "SoundEx.h"

#include <cctype>
#include <map>
#include <set>
#include <algorithm>

std::string SoundEx::Encode(const std::string& toEncode)
{
	auto firstLetter = toEncode.front();
	auto uppercaseFirstLetter = static_cast<char>(std::toupper(firstLetter));

	auto encoded = EncodeSignature(toEncode);
	return uppercaseFirstLetter + PadZeros(encoded);
}

std::string SoundEx::EncodeCharacter(char character)
{
	const std::map<char, std::string> encodingMap =
	{
		{ 'b', "1" },{ 'f', "1" },{ 'p', "1" },{ 'v', "1" },
		{ 'c', "2" },{ 'g', "2" },{ 'j', "2" },{ 'k', "2" },{ 'q', "2" },{ 's', "2" },{ 'x', "2" },{ 'z', "2" },
		{ 'd', "3" },{ 't', "3" },
		{ 'l', "4" },
		{ 'm', "5" },{ 'n', "5" },
		{ 'r', "6" },
	};

	auto lowerCaseChar = static_cast<char>(std::tolower(character));

	auto encodingMatch = encodingMap.find(lowerCaseChar);
	if (encodingMatch != encodingMap.end())
	{
		return encodingMatch->second;
	}
	else
	{
		return "";
	}
}

bool SoundEx::IsLetterIgnored(char letter)
{
	const std::set<char> skippedLetters =
	{
		'h', 'w',
	};

	auto lowerCaseChar = static_cast<char>(std::tolower(letter));
	return skippedLetters.find(lowerCaseChar) != skippedLetters.end();
}

std::string SoundEx::EncodeSignature(const std::string& toEncode)
{
	std::string encoded = "";

	if (toEncode.length() > 1)
	{
		char firstCharacter = toEncode[0];
		auto remainingString = toEncode.substr(1, toEncode.length() - 1);

		auto lastDigit = EncodeCharacter(firstCharacter);
		for (auto character : remainingString)
		{
			if (!IsLetterIgnored(character))
			{
				auto newDigit = EncodeCharacter(character);
				if (newDigit != lastDigit)
				{
					encoded += newDigit;
				}
				lastDigit = newDigit;

				if (encoded.length() >= kMaxEncodingLength)
				{
					break;
				}
			}
		}
	}

	return encoded;
}

std::string SoundEx::PadZeros(const std::string& base)
{
	auto paddingSize = kMaxEncodingLength - std::min(kMaxEncodingLength, base.length());
	return base + std::string(paddingSize, '0');
}
