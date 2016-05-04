#include <gmock/gmock.h>

#include "SoundEx.h"

class SoundExEncoding : public testing::Test 
{
public:
	SoundEx soundex;
};

TEST_F(SoundExEncoding, RetainsSoleLetterOfOneLetterWord)
{
	auto encoded = soundex.Encode("A");
	ASSERT_THAT(encoded, testing::Eq("A000"));
}

TEST_F(SoundExEncoding, PadsWithZerosToEnsure3Digits)
{
	auto encoded = soundex.Encode("I");
	ASSERT_THAT(encoded, testing::Eq("I000"));
}

TEST_F(SoundExEncoding, ReplacesConsonantWithCorrectDigits)
{
	EXPECT_THAT(soundex.Encode("Ib"), testing::Eq("I100"));
	EXPECT_THAT(soundex.Encode("Ic"), testing::Eq("I200"));
	EXPECT_THAT(soundex.Encode("Id"), testing::Eq("I300"));
}

TEST_F(SoundExEncoding, ReplacesMultipleConsonantsWithCorrectDigits)
{
	EXPECT_THAT(soundex.Encode("Ibcd"), testing::Eq("I123"));
}

TEST_F(SoundExEncoding, StopsEncodingAfter3Digits)
{
	EXPECT_THAT(soundex.Encode("Ibcdbcd"), testing::Eq("I123"));
}

TEST_F(SoundExEncoding, MapsCorrectDigitsToConsonants)
{
	EXPECT_THAT(soundex.Encode("Ifgt"), testing::Eq("I123"));
	EXPECT_THAT(soundex.Encode("Ipjl"), testing::Eq("I124"));
	EXPECT_THAT(soundex.Encode("Ivkm"), testing::Eq("I125"));
	EXPECT_THAT(soundex.Encode("Iqnr"), testing::Eq("I256"));
	EXPECT_THAT(soundex.Encode("Is"), testing::Eq("I200"));
	EXPECT_THAT(soundex.Encode("Ix"), testing::Eq("I200"));
	EXPECT_THAT(soundex.Encode("Iz"), testing::Eq("I200"));
}

TEST_F(SoundExEncoding, DoNotEncodeRepeatedLetters)
{
	EXPECT_THAT(soundex.Encode("Ibbb"), testing::Eq("I100"));
}

TEST_F(SoundExEncoding, DoubleEncodesDigitsSeparatedByAVowel)
{
	EXPECT_THAT(soundex.Encode("Ibeb"), testing::Eq("I110"));
}

TEST_F(SoundExEncoding, DoNotEncodeRepeatedLettersSeparatedByReservedConsonants)
{
	EXPECT_THAT(soundex.Encode("Ibhb"), testing::Eq("I100"));
	EXPECT_THAT(soundex.Encode("Ibwb"), testing::Eq("I100"));
}

TEST_F(SoundExEncoding, ConvertsUppercaseCharacters)
{
	EXPECT_THAT(soundex.Encode("ABCD"), testing::Eq("A123"));
}

TEST_F(SoundExEncoding, CombinesDuplicateCodesWhen2ndLetterDuplicates1st)
{
	EXPECT_THAT(soundex.Encode("Bbcd"), testing::Eq("B230"));
}

TEST_F(SoundExEncoding, SanityTests)
{
	EXPECT_THAT(soundex.Encode("Hotel"), testing::Eq("H340"));
	EXPECT_THAT(soundex.Encode("california"), testing::Eq("C416"));
}

