/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "gtest/gtest.h"

#include "core/common/ime/text_input_filter.h"
#include "core/common/ime/text_input_obscure_utils.h"
#include "core/common/ime/text_input_type.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

class TextInputFilterTest : public testing::Test {};

// =================== FilterWithDecimal ===================

/**
 * @tc.name: FilterWithDecimal001
 * @tc.desc: Test FilterWithDecimal with multiple dots — only the first dot is kept.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, FilterWithDecimal001, TestSize.Level1)
{
    std::u16string text = u"3.1.4.";
    EXPECT_TRUE(TextInputFilter::FilterWithDecimal(text));
    EXPECT_EQ(text, u"3.14");
}

/**
 * @tc.name: FilterWithDecimal002
 * @tc.desc: Test FilterWithDecimal with a single dot — no change, returns false.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, FilterWithDecimal002, TestSize.Level1)
{
    std::u16string text = u"3.14";
    EXPECT_FALSE(TextInputFilter::FilterWithDecimal(text));
    EXPECT_EQ(text, u"3.14");
}

/**
 * @tc.name: FilterWithDecimal003
 * @tc.desc: Test FilterWithDecimal with no dots — no change, returns false.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, FilterWithDecimal003, TestSize.Level1)
{
    std::u16string text = u"123";
    EXPECT_FALSE(TextInputFilter::FilterWithDecimal(text));
    EXPECT_EQ(text, u"123");
}

/**
 * @tc.name: FilterWithDecimal004
 * @tc.desc: Test FilterWithDecimal with empty string — no change, returns false.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, FilterWithDecimal004, TestSize.Level1)
{
    std::u16string text = u"";
    EXPECT_FALSE(TextInputFilter::FilterWithDecimal(text));
    EXPECT_EQ(text, u"");
}

// =================== FilterWithEmail ===================

/**
 * @tc.name: FilterWithEmail001
 * @tc.desc: Test FilterWithEmail with multiple @ — only the first @ is kept.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, FilterWithEmail001, TestSize.Level1)
{
    std::u16string text = u"a@b@c";
    EXPECT_TRUE(TextInputFilter::FilterWithEmail(text));
    EXPECT_EQ(text, u"a@bc");
}

/**
 * @tc.name: FilterWithEmail002
 * @tc.desc: Test FilterWithEmail with a single @ — no change, returns false.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, FilterWithEmail002, TestSize.Level1)
{
    std::u16string text = u"a@b";
    EXPECT_FALSE(TextInputFilter::FilterWithEmail(text));
    EXPECT_EQ(text, u"a@b");
}

/**
 * @tc.name: FilterWithEmail003
 * @tc.desc: Test FilterWithEmail with no @ — no change, returns false.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, FilterWithEmail003, TestSize.Level1)
{
    std::u16string text = u"abc";
    EXPECT_FALSE(TextInputFilter::FilterWithEmail(text));
    EXPECT_EQ(text, u"abc");
}

// =================== FilterWithAscii ===================

/**
 * @tc.name: FilterWithAscii001
 * @tc.desc: Test FilterWithAscii with empty string — returns false.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, FilterWithAscii001, TestSize.Level1)
{
    std::u16string str = u"";
    EXPECT_FALSE(TextInputFilter::FilterWithAscii(str));
    EXPECT_EQ(str, u"");
}

/**
 * @tc.name: FilterWithAscii002
 * @tc.desc: Test FilterWithAscii with all ASCII — no change, returns false.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, FilterWithAscii002, TestSize.Level1)
{
    std::u16string str = u"hello123";
    EXPECT_FALSE(TextInputFilter::FilterWithAscii(str));
    EXPECT_EQ(str, u"hello123");
}

/**
 * @tc.name: FilterWithAscii003
 * @tc.desc: Test FilterWithAscii with mixed ASCII and non-ASCII — non-ASCII removed.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, FilterWithAscii003, TestSize.Level1)
{
    // \u6d4c = 测, \u8bd5 = 试
    std::u16string str = u"abc\u6d4c\u8bd5";
    EXPECT_TRUE(TextInputFilter::FilterWithAscii(str));
    EXPECT_EQ(str, u"abc");
}

/**
 * @tc.name: FilterWithAscii004
 * @tc.desc: Test FilterWithAscii with all non-ASCII — all removed, returns true.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, FilterWithAscii004, TestSize.Level1)
{
    std::u16string str = u"\u6d4c\u8bd5";
    EXPECT_TRUE(TextInputFilter::FilterWithAscii(str));
    EXPECT_EQ(str, u"");
}

// =================== RemoveErrorTextFromValue ===================

/**
 * @tc.name: RemoveErrorTextFromValue001
 * @tc.desc: Test RemoveErrorTextFromValue when error text is not in value.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, RemoveErrorTextFromValue001, TestSize.Level1)
{
    auto result = TextInputFilter::RemoveErrorTextFromValue(u"b", u"a");
    EXPECT_EQ(result, u"b");
}

/**
 * @tc.name: RemoveErrorTextFromValue002
 * @tc.desc: Test RemoveErrorTextFromValue with single char error in value.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, RemoveErrorTextFromValue002, TestSize.Level1)
{
    auto result = TextInputFilter::RemoveErrorTextFromValue(u"abc", u"b");
    EXPECT_EQ(result, u"ac");
}

/**
 * @tc.name: RemoveErrorTextFromValue003
 * @tc.desc: Test RemoveErrorTextFromValue with multiple error chars interleaved.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, RemoveErrorTextFromValue003, TestSize.Level1)
{
    auto result = TextInputFilter::RemoveErrorTextFromValue(u"a1b2c3", u"123");
    EXPECT_EQ(result, u"abc");
}

/**
 * @tc.name: RemoveErrorTextFromValue004
 * @tc.desc: Test RemoveErrorTextFromValue with empty error text.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, RemoveErrorTextFromValue004, TestSize.Level1)
{
    auto result = TextInputFilter::RemoveErrorTextFromValue(u"abc", u"");
    EXPECT_EQ(result, u"abc");
}

// =================== FilterWithRegex ===================

/**
 * @tc.name: FilterWithRegex001
 * @tc.desc: Test FilterWithRegex with digit whitelist — non-digits removed.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, FilterWithRegex001, TestSize.Level1)
{
    std::u16string result = u"1a2b3";
    auto errorText = TextInputFilter::FilterWithRegex(TextInputFilter::DIGIT_WHITE_LIST, result);
    EXPECT_EQ(result, u"123");
    EXPECT_EQ(errorText, u"ab");
}

/**
 * @tc.name: FilterWithRegex002
 * @tc.desc: Test FilterWithRegex with no errors — empty error text, no change.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, FilterWithRegex002, TestSize.Level1)
{
    std::u16string result = u"123";
    auto errorText = TextInputFilter::FilterWithRegex(TextInputFilter::DIGIT_WHITE_LIST, result);
    EXPECT_EQ(result, u"123");
    EXPECT_TRUE(errorText.empty());
}

// =================== FilterWithEvent ===================

/**
 * @tc.name: FilterWithEvent001
 * @tc.desc: Test FilterWithEvent with no error callback — returns true if filtered.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, FilterWithEvent001, TestSize.Level1)
{
    std::u16string result = u"1a2";
    std::function<bool(const std::u16string&)> onError;
    EXPECT_TRUE(TextInputFilter::FilterWithEvent(TextInputFilter::DIGIT_WHITE_LIST, result, onError));
    EXPECT_EQ(result, u"12");
}

/**
 * @tc.name: FilterWithEvent002
 * @tc.desc: Test FilterWithEvent with no errors — returns false.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, FilterWithEvent002, TestSize.Level1)
{
    std::u16string result = u"123";
    std::function<bool(const std::u16string&)> onError;
    EXPECT_FALSE(TextInputFilter::FilterWithEvent(TextInputFilter::DIGIT_WHITE_LIST, result, onError));
    EXPECT_EQ(result, u"123");
}

/**
 * @tc.name: FilterWithEvent003
 * @tc.desc: Test FilterWithEvent with error callback returning true — returns true.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, FilterWithEvent003, TestSize.Level1)
{
    std::u16string result = u"1a2";
    bool callbackCalled = false;
    auto onError = [&callbackCalled](const std::u16string& error) -> bool {
        callbackCalled = true;
        return true;
    };
    EXPECT_TRUE(TextInputFilter::FilterWithEvent(TextInputFilter::DIGIT_WHITE_LIST, result, onError));
    EXPECT_TRUE(callbackCalled);
    EXPECT_EQ(result, u"12");
}

/**
 * @tc.name: FilterWithEvent004
 * @tc.desc: Test FilterWithEvent with error callback returning false — returns false.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, FilterWithEvent004, TestSize.Level1)
{
    std::u16string result = u"1a2";
    auto onError = [](const std::u16string& error) -> bool { return false; };
    EXPECT_FALSE(TextInputFilter::FilterWithEvent(TextInputFilter::DIGIT_WHITE_LIST, result, onError));
}

// =================== FilterByInputType ===================

/**
 * @tc.name: FilterByInputType001
 * @tc.desc: Test FilterByInputType with NUMBER — non-digits removed.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, FilterByInputType001, TestSize.Level1)
{
    std::u16string result = u"1a2b3";
    EXPECT_TRUE(TextInputFilter::FilterByInputType(TextInputType::NUMBER, result));
    EXPECT_EQ(result, u"123");
}

/**
 * @tc.name: FilterByInputType002
 * @tc.desc: Test FilterByInputType with PHONE — non-phone chars removed.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, FilterByInputType002, TestSize.Level1)
{
    std::u16string result = u"1a2b3";
    EXPECT_TRUE(TextInputFilter::FilterByInputType(TextInputType::PHONE, result));
    EXPECT_EQ(result, u"123");
}

/**
 * @tc.name: FilterByInputType003
 * @tc.desc: Test FilterByInputType with EMAIL_ADDRESS — duplicate @ removed.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, FilterByInputType003, TestSize.Level1)
{
    std::u16string result = u"a@b@c";
    EXPECT_TRUE(TextInputFilter::FilterByInputType(TextInputType::EMAIL_ADDRESS, result));
    EXPECT_EQ(result, u"a@bc");
}

/**
 * @tc.name: FilterByInputType004
 * @tc.desc: Test FilterByInputType with NUMBER_DECIMAL — duplicate dots removed.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, FilterByInputType004, TestSize.Level1)
{
    std::u16string result = u"3.1.4.";
    EXPECT_TRUE(TextInputFilter::FilterByInputType(TextInputType::NUMBER_DECIMAL, result));
    EXPECT_EQ(result, u"3.14");
}

/**
 * @tc.name: FilterByInputType005
 * @tc.desc: Test FilterByInputType with TEXT — no filtering, returns false.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, FilterByInputType005, TestSize.Level1)
{
    std::u16string result = u"abc123";
    EXPECT_FALSE(TextInputFilter::FilterByInputType(TextInputType::TEXT, result));
    EXPECT_EQ(result, u"abc123");
}

/**
 * @tc.name: FilterByInputType006
 * @tc.desc: Test FilterByInputType with NUMBER and no errors — returns false.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, FilterByInputType006, TestSize.Level1)
{
    std::u16string result = u"123";
    EXPECT_FALSE(TextInputFilter::FilterByInputType(TextInputType::NUMBER, result));
    EXPECT_EQ(result, u"123");
}

// =================== PreprocessValue ===================

/**
 * @tc.name: PreprocessValue001
 * @tc.desc: Test PreprocessValue with NUMBER_DECIMAL — removes dot from insert when existing has dot.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, PreprocessValue001, TestSize.Level1)
{
    auto result = TextInputFilter::PreprocessValue(
        TextInputType::NUMBER_DECIMAL, u"1.2", u"3.", u"");
    EXPECT_EQ(result, u"3");
}

/**
 * @tc.name: PreprocessValue002
 * @tc.desc: Test PreprocessValue with NUMBER_DECIMAL — no dedup when existing has no dot.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, PreprocessValue002, TestSize.Level1)
{
    auto result = TextInputFilter::PreprocessValue(
        TextInputType::NUMBER_DECIMAL, u"12", u"3.", u"");
    EXPECT_EQ(result, u"3.");
}

/**
 * @tc.name: PreprocessValue003
 * @tc.desc: Test PreprocessValue with EMAIL_ADDRESS — removes @ from insert when existing has @.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, PreprocessValue003, TestSize.Level1)
{
    auto result = TextInputFilter::PreprocessValue(
        TextInputType::EMAIL_ADDRESS, u"a@b", u"c@", u"");
    EXPECT_EQ(result, u"c");
}

/**
 * @tc.name: PreprocessValue004
 * @tc.desc: Test PreprocessValue — no dedup when selected text contains the special char.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, PreprocessValue004, TestSize.Level1)
{
    auto result = TextInputFilter::PreprocessValue(
        TextInputType::NUMBER_DECIMAL, u"1.2", u"3.", u".");
    EXPECT_EQ(result, u"3.");
}

/**
 * @tc.name: PreprocessValue005
 * @tc.desc: Test PreprocessValue with TEXT — no preprocessing.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, PreprocessValue005, TestSize.Level1)
{
    auto result = TextInputFilter::PreprocessValue(
        TextInputType::TEXT, u"abc", u"def", u"");
    EXPECT_EQ(result, u"def");
}

// =================== IsVerificationCodePlaceholder ===================

/**
 * @tc.name: IsVerificationCodePlaceholder001
 * @tc.desc: Test IsVerificationCodePlaceholder with Chinese keyword.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, IsVerificationCodePlaceholder001, TestSize.Level1)
{
    EXPECT_TRUE(TextInputFilter::IsVerificationCodePlaceholder(u"\u8bf7\u8f93\u5165\u9a8c\u8bc1\u7801"));
}

/**
 * @tc.name: IsVerificationCodePlaceholder002
 * @tc.desc: Test IsVerificationCodePlaceholder with English keyword (lowercase).
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, IsVerificationCodePlaceholder002, TestSize.Level1)
{
    EXPECT_TRUE(TextInputFilter::IsVerificationCodePlaceholder(u"Enter verification code"));
}

/**
 * @tc.name: IsVerificationCodePlaceholder003
 * @tc.desc: Test IsVerificationCodePlaceholder with English keyword (mixed case).
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, IsVerificationCodePlaceholder003, TestSize.Level1)
{
    EXPECT_TRUE(TextInputFilter::IsVerificationCodePlaceholder(u"Verification Code"));
}

/**
 * @tc.name: IsVerificationCodePlaceholder004
 * @tc.desc: Test IsVerificationCodePlaceholder with non-OTP placeholder.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, IsVerificationCodePlaceholder004, TestSize.Level1)
{
    EXPECT_FALSE(TextInputFilter::IsVerificationCodePlaceholder(u"Enter password"));
}

/**
 * @tc.name: IsVerificationCodePlaceholder005
 * @tc.desc: Test IsVerificationCodePlaceholder with empty string.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, IsVerificationCodePlaceholder005, TestSize.Level1)
{
    EXPECT_FALSE(TextInputFilter::IsVerificationCodePlaceholder(u""));
}

// =================== text_input_type.h predicates ===================

/**
 * @tc.name: IsPasswordInputType001
 * @tc.desc: Test IsPasswordInputType with all password types.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, IsPasswordInputType001, TestSize.Level1)
{
    EXPECT_TRUE(IsPasswordInputType(TextInputType::VISIBLE_PASSWORD));
    EXPECT_TRUE(IsPasswordInputType(TextInputType::NUMBER_PASSWORD));
    EXPECT_TRUE(IsPasswordInputType(TextInputType::SCREEN_LOCK_PASSWORD));
    EXPECT_TRUE(IsPasswordInputType(TextInputType::NEW_PASSWORD));
}

/**
 * @tc.name: IsPasswordInputType002
 * @tc.desc: Test IsPasswordInputType with non-password types.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, IsPasswordInputType002, TestSize.Level1)
{
    EXPECT_FALSE(IsPasswordInputType(TextInputType::TEXT));
    EXPECT_FALSE(IsPasswordInputType(TextInputType::NUMBER));
    EXPECT_FALSE(IsPasswordInputType(TextInputType::EMAIL_ADDRESS));
    EXPECT_FALSE(IsPasswordInputType(TextInputType::UNSPECIFIED));
}

/**
 * @tc.name: IsOneTimeCodeInputType001
 * @tc.desc: Test IsOneTimeCodeInputType with OTP types.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, IsOneTimeCodeInputType001, TestSize.Level1)
{
    EXPECT_TRUE(IsOneTimeCodeInputType(TextInputType::ONE_TIME_CODE));
    EXPECT_TRUE(IsOneTimeCodeInputType(TextInputType::ONE_TIME_CODE_NUMBER));
}

/**
 * @tc.name: IsOneTimeCodeInputType002
 * @tc.desc: Test IsOneTimeCodeInputType with non-OTP types.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, IsOneTimeCodeInputType002, TestSize.Level1)
{
    EXPECT_FALSE(IsOneTimeCodeInputType(TextInputType::TEXT));
    EXPECT_FALSE(IsOneTimeCodeInputType(TextInputType::NUMBER));
    EXPECT_FALSE(IsOneTimeCodeInputType(TextInputType::UNSPECIFIED));
}

/**
 * @tc.name: ShouldShowAIWriteForInputType001
 * @tc.desc: Test ShouldShowAIWriteForInputType with types that show AI Write.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, ShouldShowAIWriteForInputType001, TestSize.Level1)
{
    EXPECT_TRUE(ShouldShowAIWriteForInputType(TextInputType::UNSPECIFIED));
    EXPECT_TRUE(ShouldShowAIWriteForInputType(TextInputType::TEXT));
}

/**
 * @tc.name: ShouldShowAIWriteForInputType002
 * @tc.desc: Test ShouldShowAIWriteForInputType with types that do not show AI Write.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, ShouldShowAIWriteForInputType002, TestSize.Level1)
{
    EXPECT_FALSE(ShouldShowAIWriteForInputType(TextInputType::NUMBER));
    EXPECT_FALSE(ShouldShowAIWriteForInputType(TextInputType::EMAIL_ADDRESS));
    EXPECT_FALSE(ShouldShowAIWriteForInputType(TextInputType::PHONE));
    EXPECT_FALSE(ShouldShowAIWriteForInputType(TextInputType::VISIBLE_PASSWORD));
}

// =================== TextInputObscureUtils (pure functions) ===================

/**
 * @tc.name: ShouldRevealNakedChar001
 * @tc.desc: Test ShouldRevealNakedChar with all conditions true.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, ShouldRevealNakedChar001, TestSize.Level1)
{
    EXPECT_TRUE(TextInputObscureUtils::ShouldRevealNakedChar(true, true, true, 1));
}

/**
 * @tc.name: ShouldRevealNakedChar002
 * @tc.desc: Test ShouldRevealNakedChar with some conditions false.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, ShouldRevealNakedChar002, TestSize.Level1)
{
    EXPECT_FALSE(TextInputObscureUtils::ShouldRevealNakedChar(false, true, true, 1));
    EXPECT_FALSE(TextInputObscureUtils::ShouldRevealNakedChar(true, false, true, 1));
    EXPECT_FALSE(TextInputObscureUtils::ShouldRevealNakedChar(true, true, false, 1));
    EXPECT_FALSE(TextInputObscureUtils::ShouldRevealNakedChar(true, true, true, 0));
}

/**
 * @tc.name: UpdateObscureState001
 * @tc.desc: Test UpdateObscureState with single char insert matching content.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, UpdateObscureState001, TestSize.Level1)
{
    // Inserted 'x' after 'a' -> content "ax", caret at 2 (after the inserted char);
    // content[caret-1]='x' == insertValue -> reveal.
    auto result = TextInputObscureUtils::UpdateObscureState(
        TextInputType::VISIBLE_PASSWORD, u"x", true, u"ax", 2);
    EXPECT_EQ(result.tickCountDown, static_cast<int32_t>(TextInputObscureUtils::OBSCURE_SHOW_TICKS));
    EXPECT_EQ(result.nakedCharPosition, 1);
}

/**
 * @tc.name: UpdateObscureState002
 * @tc.desc: Test UpdateObscureState with non-matching insert.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, UpdateObscureState002, TestSize.Level1)
{
    // Inserted 'x' after 'a' -> content "ay", caret at 2;
    // content[caret-1]='y' != insertValue -> no match.
    auto result = TextInputObscureUtils::UpdateObscureState(
        TextInputType::VISIBLE_PASSWORD, u"x", true, u"ay", 2);
    EXPECT_EQ(result.tickCountDown, 0);
    EXPECT_EQ(result.nakedCharPosition, -1);
}

/**
 * @tc.name: UpdateObscureState003
 * @tc.desc: Test UpdateObscureState with multi-char insert — no reveal.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, UpdateObscureState003, TestSize.Level1)
{
    auto result = TextInputObscureUtils::UpdateObscureState(
        TextInputType::VISIBLE_PASSWORD, u"xy", true, u"axy", 2);
    EXPECT_EQ(result.tickCountDown, 0);
    EXPECT_EQ(result.nakedCharPosition, -1);
}

/**
 * @tc.name: UpdateObscureState004
 * @tc.desc: Test UpdateObscureState with hasInsert=false — no reveal.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, UpdateObscureState004, TestSize.Level1)
{
    auto result = TextInputObscureUtils::UpdateObscureState(
        TextInputType::VISIBLE_PASSWORD, u"x", false, u"ax", 1);
    EXPECT_EQ(result.tickCountDown, 0);
    EXPECT_EQ(result.nakedCharPosition, -1);
}

/**
 * @tc.name: UpdateObscureState005
 * @tc.desc: Test UpdateObscureState with NUMBER_PASSWORD and non-digit insert — no reveal.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, UpdateObscureState005, TestSize.Level1)
{
    // NUMBER_PASSWORD only reveals digits
    auto result = TextInputObscureUtils::UpdateObscureState(
        TextInputType::NUMBER_PASSWORD, u"x", true, u"ax", 1);
    EXPECT_EQ(result.tickCountDown, 0);
    EXPECT_EQ(result.nakedCharPosition, -1);
}

/**
 * @tc.name: UpdateObscureState006
 * @tc.desc: Test UpdateObscureState with NUMBER_PASSWORD and digit insert — reveal.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputFilterTest, UpdateObscureState006, TestSize.Level1)
{
    // NUMBER_PASSWORD reveals digits: inserted '5' after 'a' -> content "a5",
    // caret at 2; content[caret-1]='5' == insertValue -> reveal.
    auto result = TextInputObscureUtils::UpdateObscureState(
        TextInputType::NUMBER_PASSWORD, u"5", true, u"a5", 2);
    EXPECT_EQ(result.tickCountDown, static_cast<int32_t>(TextInputObscureUtils::OBSCURE_SHOW_TICKS));
    EXPECT_EQ(result.nakedCharPosition, 1);
}

} // namespace OHOS::Ace
