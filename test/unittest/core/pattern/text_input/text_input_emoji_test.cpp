/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "text_input_base.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class TextFieldUXTest : public TextInputBases {
protected:
    static int32_t GetEmojiStringLength(std::string emojiString);
    static std::string CreateEmojiStringWithLength(std::string emoji, int32_t length);
    static void InitICU();
};

// get emoji string length in UTF-16 format
int32_t TextFieldUXTest::GetEmojiStringLength(std::string emojiString)
{
    std::u16string u16EmojiString = StringUtils::Str8ToStr16(emojiString);
    return static_cast<int32_t>(u16EmojiString.length());
}

// create emoji string with number of emoji characters
std::string TextFieldUXTest::CreateEmojiStringWithLength(std::string emoji, int32_t length)
{
    std::string emojiString = "";
    for (int32_t i = 0; i < length; i++) {
        emojiString += emoji;
    }
    return emojiString;
}

void TextFieldUXTest::InitICU()
{
#if defined(__HuaweiLite__) || defined(__OHOS__)
    // use system icudt .dat file
    std::string dataPath = "/system/usr/ohos_icu";
#else
    // use project icudt .dat file
#ifdef WINDOWS_PLATFORM
    char buffer[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, buffer);
    std::string currentPath = std::string(buffer);
#else
    char buffer[PATH_MAX];
    getcwd(buffer, sizeof(buffer));
    std::string currentPath = std::string(buffer);
#endif
    std::string dataPath = currentPath + "/../../../../../../third_party/icu/ohos_icu4j/data";
#endif
    u_setDataDirectory(dataPath.c_str());
    UErrorCode code;
    u_init(&code);
}

/**
 * @tc.name: HandleOnDeleteAction001
 * @tc.desc: test testInput deleteAction for normal emoji.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleOnDeleteAction001, TestSize.Level1)
{
    // init icu library.
    // we only need to init icu once.
    // please make sure that the icu library is initialized before using it.
    // zero means success.
    InitICU();
    
    /**
     * @tc.steps: Create Text field node
     */
    std::string txt = "😄😌😎😭😄😌😎😭😄😌😎😭";
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();
    /**
     * @tc.step: step2. Set caretPosition and call Delete
     */
    pattern_->SetCaretPosition(24);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    std::string result = "😄😌😎😭😄😌😎😭😄😌";
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " << pattern_->GetTextValue();

    pattern_->SetCaretPosition(10);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    result = "😄😌😎😌😎😭😄😌";
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " << pattern_->GetTextValue();

    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = "😎😌😎😭😄😌";
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    pattern_->SetCaretPosition(6);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = "😎😌😎😌";
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();
}

/**
 * @tc.name: HandleOnDeleteAction002
 * @tc.desc: test testInput deleteAction for ZWJ emoji.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleOnDeleteAction002, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    std::string caseEmoji = "👨‍👩‍👦‍👦";
    int32_t totalNumberOfEmoji = 12;
    int32_t bytesOfOneEmoji = GetEmojiStringLength(caseEmoji);
    const std::string txt = CreateEmojiStringWithLength(caseEmoji, totalNumberOfEmoji);
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    /**
     * @tc.step: step1. Set caretPosition and call DeleteBackward in end of text
     * @tc.expected: Text is 10 x caseEmoji
     */
    pattern_->SetCaretPosition(totalNumberOfEmoji * bytesOfOneEmoji);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    std::string result = CreateEmojiStringWithLength(caseEmoji, 10);

    /**
     * @tc.step: step2. Set caretPosition and call DeleteBackward in middle of text
     * @tc.expected: Text is 8 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 8);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 8);

    /**
     * @tc.step: step3. Set caretPosition and call DeleteForward in start of text
     * @tc.expected: Text is 6 x caseEmoji
     */
    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 6);

    /**
     * @tc.step: step4. Set caretPosition and call DeleteForward in middle of text
     * @tc.expected: Text is 4 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 4);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 4);
}

/**
 * @tc.name: HandleOnDeleteAction003
 * @tc.desc: test testInput deleteAction for VS emoji.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleOnDeleteAction003, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    std::string caseEmoji = "👨‍👩‍👦‍👦";
    int32_t totalNumberOfEmoji = 12;
    int32_t bytesOfOneEmoji = GetEmojiStringLength(caseEmoji);
    const std::string txt = CreateEmojiStringWithLength(caseEmoji, totalNumberOfEmoji);
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    /**
     * @tc.step: step1. Set caretPosition and call DeleteBackward in end of text
     * @tc.expected: Text is 10 x caseEmoji
     */
    pattern_->SetCaretPosition(totalNumberOfEmoji * bytesOfOneEmoji);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    std::string result = CreateEmojiStringWithLength(caseEmoji, 10);

    /**
     * @tc.step: step2. Set caretPosition and call DeleteBackward in middle of text
     * @tc.expected: Text is 8 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 8);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 8);

    /**
     * @tc.step: step3. Set caretPosition and call DeleteForward in start of text
     * @tc.expected: Text is 6 x caseEmoji
     */
    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 6);

    /**
     * @tc.step: step4. Set caretPosition and call DeleteForward in middle of text
     * @tc.expected: Text is 4 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 4);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 4);
}

/**
 * @tc.name: HandleOnDeleteAction004
 * @tc.desc: test testInput deleteAction for RIS.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleOnDeleteAction004, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    std::string caseEmoji = "🇨🇳";
    int32_t totalNumberOfEmoji = 12;
    int32_t bytesOfOneEmoji = GetEmojiStringLength(caseEmoji);
    const std::string txt = CreateEmojiStringWithLength(caseEmoji, totalNumberOfEmoji);
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    /**
     * @tc.step: step1. Set caretPosition and call DeleteBackward in end of text
     * @tc.expected: Text is 10 x caseEmoji
     */
    pattern_->SetCaretPosition(totalNumberOfEmoji * bytesOfOneEmoji);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    std::string result = CreateEmojiStringWithLength(caseEmoji, 10);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step2. Set caretPosition and call DeleteBackward in middle of text
     * @tc.expected: Text is 8 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 8);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 8);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step3. Set caretPosition and call DeleteForward in start of text
     * @tc.expected: Text is 6 x caseEmoji
     */
    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 6);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step4. Set caretPosition and call DeleteForward in middle of text
     * @tc.expected: Text is 4 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 4);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 4);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();
}

/**
 * @tc.name: HandleOnDeleteAction005
 * @tc.desc: test testInput deleteAction for keycap.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleOnDeleteAction005, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    std::string caseEmoji = "3️⃣";
    int32_t totalNumberOfEmoji = 12;
    int32_t bytesOfOneEmoji = GetEmojiStringLength(caseEmoji);
    const std::string txt = CreateEmojiStringWithLength(caseEmoji, totalNumberOfEmoji);
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    /**
     * @tc.step: step1. Set caretPosition and call DeleteBackward in end of text
     * @tc.expected: Text is 10 x caseEmoji
     */
    pattern_->SetCaretPosition(totalNumberOfEmoji * bytesOfOneEmoji);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    std::string result = CreateEmojiStringWithLength(caseEmoji, 10);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step2. Set caretPosition and call DeleteBackward in middle of text
     * @tc.expected: Text is 8 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 8);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 8);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step3. Set caretPosition and call DeleteForward in start of text
     * @tc.expected: Text is 6 x caseEmoji
     */
    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 6);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step4. Set caretPosition and call DeleteForward in middle of text
     * @tc.expected: Text is 4 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 4);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 4);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();
}

/**
 * @tc.name: HandleOnDeleteAction006
 * @tc.desc: test testInput deleteAction for ZWJ&VS emoji.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleOnDeleteAction006, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    std::string caseEmoji = "👁️‍🗨️";
    int32_t totalNumberOfEmoji = 12;
    int32_t bytesOfOneEmoji = GetEmojiStringLength(caseEmoji);
    const std::string txt = CreateEmojiStringWithLength(caseEmoji, totalNumberOfEmoji);
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    /**
     * @tc.step: step1. Set caretPosition and call DeleteBackward in end of text
     * @tc.expected: Text is 10 x caseEmoji
     */
    pattern_->SetCaretPosition(totalNumberOfEmoji * bytesOfOneEmoji);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    std::string result = CreateEmojiStringWithLength(caseEmoji, 10);

    /**
     * @tc.step: step2. Set caretPosition and call DeleteBackward in middle of text
     * @tc.expected: Text is 8 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 8);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 8);

    /**
     * @tc.step: step3. Set caretPosition and call DeleteForward in start of text
     * @tc.expected: Text is 6 x caseEmoji
     */
    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 6);

    /**
     * @tc.step: step4. Set caretPosition and call DeleteForward in middle of text
     * @tc.expected: Text is 4 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 4);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 4);
}

/**
 * @tc.name: HandleOnDeleteAction007
 * @tc.desc: test testInput deleteAction for line break.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleOnDeleteAction007, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    const std::string txt = "1\n23\n45\r\n6\n78\n9";
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    /**
     * @tc.step: step2. Set caretPosition and call Delete
     */
    pattern_->SetCaretPosition(15);
    pattern_->DeleteBackward(4);
    FlushLayoutTask(frameNode_);
    std::string result = "1\n23\n45\r\n6\n";
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    pattern_->SetCaretPosition(9);
    pattern_->DeleteBackward(3);
    FlushLayoutTask(frameNode_);
    result = "1\n23\n6\n";
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(3);
    FlushLayoutTask(frameNode_);
    result = "3\n6\n";
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    pattern_->SetCaretPosition(2);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = "3\n";
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();
}

/**
 * @tc.name: HandleOnDeleteAction008
 * @tc.desc: test testInput deleteAction for all case.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleOnDeleteAction008, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    const std::string txt = "12345📡👨‍👩‍👧‍👦👁️\n🇨🇳3️⃣👁️‍🗨️\n67890";
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    /**
     * @tc.step: step2. Set caretPosition and call Delete
     */
    pattern_->SetCaretPosition(42);
    pattern_->DeleteBackward(6);
    FlushLayoutTask(frameNode_);
    std::string result = "12345📡👨‍👩‍👧‍👦👁️\n🇨🇳3️⃣👁️‍🗨️";
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    pattern_->SetCaretPosition(29);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    result = "12345📡👨‍👩‍👧‍👦👁️\n👁️‍🗨️";
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(6);
    FlushLayoutTask(frameNode_);
    result = "👨‍👩‍👧‍👦👁️\n👁️‍🗨️";
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    pattern_->SetCaretPosition(14);
    pattern_->DeleteForward(1);
    FlushLayoutTask(frameNode_);
    result = "👨‍👩‍👧‍👦👁️👁️‍🗨️";
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();
}

/**
 * @tc.name: HandleOnDeleteAction009
 * @tc.desc: test testInput deleteAction.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleOnDeleteAction009, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    std::string caseEmoji = "😄";
    int32_t totalNumberOfEmoji = 12;
    int32_t bytesOfOneEmoji = GetEmojiStringLength(caseEmoji);
    const std::string txt = CreateEmojiStringWithLength(caseEmoji, totalNumberOfEmoji);
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    /**
     * @tc.step: step1. Set caretPosition and call DeleteBackward in end of text
     * @tc.expected: Text is 10 x caseEmoji
     */
    pattern_->SetCaretPosition(totalNumberOfEmoji * bytesOfOneEmoji);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    std::string result = CreateEmojiStringWithLength(caseEmoji, 10);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step2. Set caretPosition and call DeleteBackward in middle of text
     * @tc.expected: Text is 8 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 8);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 8);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step3. Set caretPosition and call DeleteForward in start of text
     * @tc.expected: Text is 6 x caseEmoji
     */
    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 6);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step4. Set caretPosition and call DeleteForward in middle of text
     * @tc.expected: Text is 4 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 4);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 4);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();
}

/**
 * @tc.name: HandleOnDeleteAction010
 * @tc.desc: test testInput deleteAction.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleOnDeleteAction010, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    std::string caseEmoji = "😌";
    int32_t totalNumberOfEmoji = 12;
    int32_t bytesOfOneEmoji = GetEmojiStringLength(caseEmoji);
    const std::string txt = CreateEmojiStringWithLength(caseEmoji, totalNumberOfEmoji);
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    /**
     * @tc.step: step1. Set caretPosition and call DeleteBackward in end of text
     * @tc.expected: Text is 10 x caseEmoji
     */
    pattern_->SetCaretPosition(totalNumberOfEmoji * bytesOfOneEmoji);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    std::string result = CreateEmojiStringWithLength(caseEmoji, 10);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step2. Set caretPosition and call DeleteBackward in middle of text
     * @tc.expected: Text is 8 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 8);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 8);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step3. Set caretPosition and call DeleteForward in start of text
     * @tc.expected: Text is 6 x caseEmoji
     */
    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 6);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step4. Set caretPosition and call DeleteForward in middle of text
     * @tc.expected: Text is 4 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 4);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 4);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();
}

/**
 * @tc.name: HandleOnDeleteAction011
 * @tc.desc: test testInput deleteAction.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleOnDeleteAction011, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    std::string caseEmoji = "😎";
    int32_t totalNumberOfEmoji = 12;
    int32_t bytesOfOneEmoji = GetEmojiStringLength(caseEmoji);
    const std::string txt = CreateEmojiStringWithLength(caseEmoji, totalNumberOfEmoji);
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    /**
     * @tc.step: step1. Set caretPosition and call DeleteBackward in end of text
     * @tc.expected: Text is 10 x caseEmoji
     */
    pattern_->SetCaretPosition(totalNumberOfEmoji * bytesOfOneEmoji);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    std::string result = CreateEmojiStringWithLength(caseEmoji, 10);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step2. Set caretPosition and call DeleteBackward in middle of text
     * @tc.expected: Text is 8 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 8);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 8);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step3. Set caretPosition and call DeleteForward in start of text
     * @tc.expected: Text is 6 x caseEmoji
     */
    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 6);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step4. Set caretPosition and call DeleteForward in middle of text
     * @tc.expected: Text is 4 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 4);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 4);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();
}

/**
 * @tc.name: HandleOnDeleteAction012
 * @tc.desc: test testInput deleteAction.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleOnDeleteAction012, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    std::string caseEmoji = "😭";
    int32_t totalNumberOfEmoji = 12;
    int32_t bytesOfOneEmoji = GetEmojiStringLength(caseEmoji);
    const std::string txt = CreateEmojiStringWithLength(caseEmoji, totalNumberOfEmoji);
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    /**
     * @tc.step: step1. Set caretPosition and call DeleteBackward in end of text
     * @tc.expected: Text is 10 x caseEmoji
     */
    pattern_->SetCaretPosition(totalNumberOfEmoji * bytesOfOneEmoji);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    std::string result = CreateEmojiStringWithLength(caseEmoji, 10);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step2. Set caretPosition and call DeleteBackward in middle of text
     * @tc.expected: Text is 8 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 8);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 8);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step3. Set caretPosition and call DeleteForward in start of text
     * @tc.expected: Text is 6 x caseEmoji
     */
    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 6);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step4. Set caretPosition and call DeleteForward in middle of text
     * @tc.expected: Text is 4 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 4);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 4);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();
}

/**
 * @tc.name: HandleOnDeleteAction013
 * @tc.desc: test testInput deleteAction.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleOnDeleteAction013, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    std::string caseEmoji = "😄";
    int32_t totalNumberOfEmoji = 12;
    int32_t bytesOfOneEmoji = GetEmojiStringLength(caseEmoji);
    const std::string txt = CreateEmojiStringWithLength(caseEmoji, totalNumberOfEmoji);
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    /**
     * @tc.step: step1. Set caretPosition and call DeleteBackward in end of text
     * @tc.expected: Text is 10 x caseEmoji
     */
    pattern_->SetCaretPosition(totalNumberOfEmoji * bytesOfOneEmoji);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    std::string result = CreateEmojiStringWithLength(caseEmoji, 10);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step2. Set caretPosition and call DeleteBackward in middle of text
     * @tc.expected: Text is 8 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 8);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 8);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step3. Set caretPosition and call DeleteForward in start of text
     * @tc.expected: Text is 6 x caseEmoji
     */
    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 6);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step4. Set caretPosition and call DeleteForward in middle of text
     * @tc.expected: Text is 4 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 4);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 4);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();
}

/**
 * @tc.name: HandleOnDeleteAction014
 * @tc.desc: test testInput deleteAction.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleOnDeleteAction014, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    std::string caseEmoji = "😌";
    int32_t totalNumberOfEmoji = 12;
    int32_t bytesOfOneEmoji = GetEmojiStringLength(caseEmoji);
    const std::string txt = CreateEmojiStringWithLength(caseEmoji, totalNumberOfEmoji);
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    /**
     * @tc.step: step1. Set caretPosition and call DeleteBackward in end of text
     * @tc.expected: Text is 10 x caseEmoji
     */
    pattern_->SetCaretPosition(totalNumberOfEmoji * bytesOfOneEmoji);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    std::string result = CreateEmojiStringWithLength(caseEmoji, 10);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step2. Set caretPosition and call DeleteBackward in middle of text
     * @tc.expected: Text is 8 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 8);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 8);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step3. Set caretPosition and call DeleteForward in start of text
     * @tc.expected: Text is 6 x caseEmoji
     */
    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 6);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step4. Set caretPosition and call DeleteForward in middle of text
     * @tc.expected: Text is 4 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 4);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 4);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();
}

/**
 * @tc.name: HandleOnDeleteAction015
 * @tc.desc: test testInput deleteAction.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleOnDeleteAction015, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    std::string caseEmoji = "😎";
    int32_t totalNumberOfEmoji = 12;
    int32_t bytesOfOneEmoji = GetEmojiStringLength(caseEmoji);
    const std::string txt = CreateEmojiStringWithLength(caseEmoji, totalNumberOfEmoji);
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    /**
     * @tc.step: step1. Set caretPosition and call DeleteBackward in end of text
     * @tc.expected: Text is 10 x caseEmoji
     */
    pattern_->SetCaretPosition(totalNumberOfEmoji * bytesOfOneEmoji);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    std::string result = CreateEmojiStringWithLength(caseEmoji, 10);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step2. Set caretPosition and call DeleteBackward in middle of text
     * @tc.expected: Text is 8 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 8);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 8);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step3. Set caretPosition and call DeleteForward in start of text
     * @tc.expected: Text is 6 x caseEmoji
     */
    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 6);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step4. Set caretPosition and call DeleteForward in middle of text
     * @tc.expected: Text is 4 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 4);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 4);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();
}

/**
 * @tc.name: HandleOnDeleteAction016
 * @tc.desc: test testInput deleteAction.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleOnDeleteAction016, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    std::string caseEmoji = "😭";
    int32_t totalNumberOfEmoji = 12;
    int32_t bytesOfOneEmoji = GetEmojiStringLength(caseEmoji);
    const std::string txt = CreateEmojiStringWithLength(caseEmoji, totalNumberOfEmoji);
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    /**
     * @tc.step: step1. Set caretPosition and call DeleteBackward in end of text
     * @tc.expected: Text is 10 x caseEmoji
     */
    pattern_->SetCaretPosition(totalNumberOfEmoji * bytesOfOneEmoji);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    std::string result = CreateEmojiStringWithLength(caseEmoji, 10);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step2. Set caretPosition and call DeleteBackward in middle of text
     * @tc.expected: Text is 8 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 8);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 8);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step3. Set caretPosition and call DeleteForward in start of text
     * @tc.expected: Text is 6 x caseEmoji
     */
    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 6);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step4. Set caretPosition and call DeleteForward in middle of text
     * @tc.expected: Text is 4 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 4);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 4);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();
}

/**
 * @tc.name: HandleOnDeleteAction017
 * @tc.desc: test testInput deleteAction.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleOnDeleteAction017, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    std::string caseEmoji = "😄";
    int32_t totalNumberOfEmoji = 12;
    int32_t bytesOfOneEmoji = GetEmojiStringLength(caseEmoji);
    const std::string txt = CreateEmojiStringWithLength(caseEmoji, totalNumberOfEmoji);
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    /**
     * @tc.step: step1. Set caretPosition and call DeleteBackward in end of text
     * @tc.expected: Text is 10 x caseEmoji
     */
    pattern_->SetCaretPosition(totalNumberOfEmoji * bytesOfOneEmoji);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    std::string result = CreateEmojiStringWithLength(caseEmoji, 10);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step2. Set caretPosition and call DeleteBackward in middle of text
     * @tc.expected: Text is 8 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 8);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 8);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step3. Set caretPosition and call DeleteForward in start of text
     * @tc.expected: Text is 6 x caseEmoji
     */
    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 6);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step4. Set caretPosition and call DeleteForward in middle of text
     * @tc.expected: Text is 4 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 4);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 4);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();
}

/**
 * @tc.name: HandleOnDeleteAction018
 * @tc.desc: test testInput deleteAction.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleOnDeleteAction018, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    std::string caseEmoji = "😌";
    int32_t totalNumberOfEmoji = 12;
    int32_t bytesOfOneEmoji = GetEmojiStringLength(caseEmoji);
    const std::string txt = CreateEmojiStringWithLength(caseEmoji, totalNumberOfEmoji);
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    /**
     * @tc.step: step1. Set caretPosition and call DeleteBackward in end of text
     * @tc.expected: Text is 10 x caseEmoji
     */
    pattern_->SetCaretPosition(totalNumberOfEmoji * bytesOfOneEmoji);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    std::string result = CreateEmojiStringWithLength(caseEmoji, 10);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step2. Set caretPosition and call DeleteBackward in middle of text
     * @tc.expected: Text is 8 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 8);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 8);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step3. Set caretPosition and call DeleteForward in start of text
     * @tc.expected: Text is 6 x caseEmoji
     */
    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 6);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step4. Set caretPosition and call DeleteForward in middle of text
     * @tc.expected: Text is 4 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 4);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 4);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();
}

/**
 * @tc.name: HandleOnDeleteAction019
 * @tc.desc: test testInput deleteAction.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleOnDeleteAction019, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    std::string caseEmoji = "😎";
    int32_t totalNumberOfEmoji = 12;
    int32_t bytesOfOneEmoji = GetEmojiStringLength(caseEmoji);
    const std::string txt = CreateEmojiStringWithLength(caseEmoji, totalNumberOfEmoji);
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    /**
     * @tc.step: step1. Set caretPosition and call DeleteBackward in end of text
     * @tc.expected: Text is 10 x caseEmoji
     */
    pattern_->SetCaretPosition(totalNumberOfEmoji * bytesOfOneEmoji);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    std::string result = CreateEmojiStringWithLength(caseEmoji, 10);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step2. Set caretPosition and call DeleteBackward in middle of text
     * @tc.expected: Text is 8 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 8);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 8);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step3. Set caretPosition and call DeleteForward in start of text
     * @tc.expected: Text is 6 x caseEmoji
     */
    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 6);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step4. Set caretPosition and call DeleteForward in middle of text
     * @tc.expected: Text is 4 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 4);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 4);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();
}

/**
 * @tc.name: HandleOnDeleteAction020
 * @tc.desc: test testInput deleteAction.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleOnDeleteAction020, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    std::string caseEmoji = "😭";
    int32_t totalNumberOfEmoji = 12;
    int32_t bytesOfOneEmoji = GetEmojiStringLength(caseEmoji);
    const std::string txt = CreateEmojiStringWithLength(caseEmoji, totalNumberOfEmoji);
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    /**
     * @tc.step: step1. Set caretPosition and call DeleteBackward in end of text
     * @tc.expected: Text is 10 x caseEmoji
     */
    pattern_->SetCaretPosition(totalNumberOfEmoji * bytesOfOneEmoji);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    std::string result = CreateEmojiStringWithLength(caseEmoji, 10);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step2. Set caretPosition and call DeleteBackward in middle of text
     * @tc.expected: Text is 8 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 8);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 8);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step3. Set caretPosition and call DeleteForward in start of text
     * @tc.expected: Text is 6 x caseEmoji
     */
    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 6);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step4. Set caretPosition and call DeleteForward in middle of text
     * @tc.expected: Text is 4 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 4);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 4);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();
}

/**
 * @tc.name: HandleOnDeleteAction021
 * @tc.desc: test testInput deleteAction.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleOnDeleteAction021, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    std::string caseEmoji = "🩷";
    int32_t totalNumberOfEmoji = 12;
    int32_t bytesOfOneEmoji = GetEmojiStringLength(caseEmoji);
    const std::string txt = CreateEmojiStringWithLength(caseEmoji, totalNumberOfEmoji);
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    /**
     * @tc.step: step1. Set caretPosition and call DeleteBackward in end of text
     * @tc.expected: Text is 10 x caseEmoji
     */
    pattern_->SetCaretPosition(totalNumberOfEmoji * bytesOfOneEmoji);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    std::string result = CreateEmojiStringWithLength(caseEmoji, 10);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step2. Set caretPosition and call DeleteBackward in middle of text
     * @tc.expected: Text is 8 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 8);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 8);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step3. Set caretPosition and call DeleteForward in start of text
     * @tc.expected: Text is 6 x caseEmoji
     */
    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 6);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step4. Set caretPosition and call DeleteForward in middle of text
     * @tc.expected: Text is 4 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 4);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 4);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();
}

/**
 * @tc.name: HandleOnDeleteAction022
 * @tc.desc: test testInput deleteAction.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleOnDeleteAction022, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    std::string caseEmoji = "🤌";
    int32_t totalNumberOfEmoji = 12;
    int32_t bytesOfOneEmoji = GetEmojiStringLength(caseEmoji);
    const std::string txt = CreateEmojiStringWithLength(caseEmoji, totalNumberOfEmoji);
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    /**
     * @tc.step: step1. Set caretPosition and call DeleteBackward in end of text
     * @tc.expected: Text is 10 x caseEmoji
     */
    pattern_->SetCaretPosition(totalNumberOfEmoji * bytesOfOneEmoji);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    std::string result = CreateEmojiStringWithLength(caseEmoji, 10);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step2. Set caretPosition and call DeleteBackward in middle of text
     * @tc.expected: Text is 8 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 8);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 8);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step3. Set caretPosition and call DeleteForward in start of text
     * @tc.expected: Text is 6 x caseEmoji
     */
    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 6);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step4. Set caretPosition and call DeleteForward in middle of text
     * @tc.expected: Text is 4 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 4);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 4);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();
}

/**
 * @tc.name: HandleOnDeleteAction023
 * @tc.desc: test testInput deleteAction.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleOnDeleteAction023, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    std::string caseEmoji = "🤲";
    int32_t totalNumberOfEmoji = 12;
    int32_t bytesOfOneEmoji = GetEmojiStringLength(caseEmoji);
    const std::string txt = CreateEmojiStringWithLength(caseEmoji, totalNumberOfEmoji);
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    /**
     * @tc.step: step1. Set caretPosition and call DeleteBackward in end of text
     * @tc.expected: Text is 10 x caseEmoji
     */
    pattern_->SetCaretPosition(totalNumberOfEmoji * bytesOfOneEmoji);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    std::string result = CreateEmojiStringWithLength(caseEmoji, 10);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step2. Set caretPosition and call DeleteBackward in middle of text
     * @tc.expected: Text is 8 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 8);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 8);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step3. Set caretPosition and call DeleteForward in start of text
     * @tc.expected: Text is 6 x caseEmoji
     */
    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 6);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step4. Set caretPosition and call DeleteForward in middle of text
     * @tc.expected: Text is 4 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 4);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 4);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();
}

/**
 * @tc.name: HandleOnDeleteAction024
 * @tc.desc: test testInput deleteAction.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleOnDeleteAction024, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    std::string caseEmoji = "🫰";
    int32_t totalNumberOfEmoji = 12;
    int32_t bytesOfOneEmoji = GetEmojiStringLength(caseEmoji);
    const std::string txt = CreateEmojiStringWithLength(caseEmoji, totalNumberOfEmoji);
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    /**
     * @tc.step: step1. Set caretPosition and call DeleteBackward in end of text
     * @tc.expected: Text is 10 x caseEmoji
     */
    pattern_->SetCaretPosition(totalNumberOfEmoji * bytesOfOneEmoji);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    std::string result = CreateEmojiStringWithLength(caseEmoji, 10);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step2. Set caretPosition and call DeleteBackward in middle of text
     * @tc.expected: Text is 8 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 8);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 8);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step3. Set caretPosition and call DeleteForward in start of text
     * @tc.expected: Text is 6 x caseEmoji
     */
    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 6);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step4. Set caretPosition and call DeleteForward in middle of text
     * @tc.expected: Text is 4 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 4);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 4);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();
}

/**
 * @tc.name: HandleOnDeleteAction025
 * @tc.desc: test testInput deleteAction.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleOnDeleteAction025, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    std::string caseEmoji = "😹";
    int32_t totalNumberOfEmoji = 12;
    int32_t bytesOfOneEmoji = GetEmojiStringLength(caseEmoji);
    const std::string txt = CreateEmojiStringWithLength(caseEmoji, totalNumberOfEmoji);
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    /**
     * @tc.step: step1. Set caretPosition and call DeleteBackward in end of text
     * @tc.expected: Text is 10 x caseEmoji
     */
    pattern_->SetCaretPosition(totalNumberOfEmoji * bytesOfOneEmoji);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    std::string result = CreateEmojiStringWithLength(caseEmoji, 10);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step2. Set caretPosition and call DeleteBackward in middle of text
     * @tc.expected: Text is 8 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 8);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 8);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step3. Set caretPosition and call DeleteForward in start of text
     * @tc.expected: Text is 6 x caseEmoji
     */
    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 6);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step4. Set caretPosition and call DeleteForward in middle of text
     * @tc.expected: Text is 4 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 4);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 4);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();
}

/**
 * @tc.name: HandleOnDeleteAction026
 * @tc.desc: test testInput deleteAction.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleOnDeleteAction026, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    std::string caseEmoji = "😾";
    int32_t totalNumberOfEmoji = 12;
    int32_t bytesOfOneEmoji = GetEmojiStringLength(caseEmoji);
    const std::string txt = CreateEmojiStringWithLength(caseEmoji, totalNumberOfEmoji);
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    /**
     * @tc.step: step1. Set caretPosition and call DeleteBackward in end of text
     * @tc.expected: Text is 10 x caseEmoji
     */
    pattern_->SetCaretPosition(totalNumberOfEmoji * bytesOfOneEmoji);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    std::string result = CreateEmojiStringWithLength(caseEmoji, 10);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step2. Set caretPosition and call DeleteBackward in middle of text
     * @tc.expected: Text is 8 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 8);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 8);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step3. Set caretPosition and call DeleteForward in start of text
     * @tc.expected: Text is 6 x caseEmoji
     */
    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 6);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step4. Set caretPosition and call DeleteForward in middle of text
     * @tc.expected: Text is 4 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 4);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 4);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();
}

/**
 * @tc.name: HandleOnDeleteAction027
 * @tc.desc: test testInput deleteAction.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleOnDeleteAction027, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    std::string caseEmoji = "🤖";
    int32_t totalNumberOfEmoji = 12;
    int32_t bytesOfOneEmoji = GetEmojiStringLength(caseEmoji);
    const std::string txt = CreateEmojiStringWithLength(caseEmoji, totalNumberOfEmoji);
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    /**
     * @tc.step: step1. Set caretPosition and call DeleteBackward in end of text
     * @tc.expected: Text is 10 x caseEmoji
     */
    pattern_->SetCaretPosition(totalNumberOfEmoji * bytesOfOneEmoji);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    std::string result = CreateEmojiStringWithLength(caseEmoji, 10);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step2. Set caretPosition and call DeleteBackward in middle of text
     * @tc.expected: Text is 8 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 8);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 8);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step3. Set caretPosition and call DeleteForward in start of text
     * @tc.expected: Text is 6 x caseEmoji
     */
    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 6);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step4. Set caretPosition and call DeleteForward in middle of text
     * @tc.expected: Text is 4 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 4);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 4);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();
}

/**
 * @tc.name: HandleOnDeleteAction028
 * @tc.desc: test testInput deleteAction.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleOnDeleteAction028, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    std::string caseEmoji = "👾";
    int32_t totalNumberOfEmoji = 12;
    int32_t bytesOfOneEmoji = GetEmojiStringLength(caseEmoji);
    const std::string txt = CreateEmojiStringWithLength(caseEmoji, totalNumberOfEmoji);
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    /**
     * @tc.step: step1. Set caretPosition and call DeleteBackward in end of text
     * @tc.expected: Text is 10 x caseEmoji
     */
    pattern_->SetCaretPosition(totalNumberOfEmoji * bytesOfOneEmoji);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    std::string result = CreateEmojiStringWithLength(caseEmoji, 10);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step2. Set caretPosition and call DeleteBackward in middle of text
     * @tc.expected: Text is 8 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 8);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 8);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step3. Set caretPosition and call DeleteForward in start of text
     * @tc.expected: Text is 6 x caseEmoji
     */
    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 6);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step4. Set caretPosition and call DeleteForward in middle of text
     * @tc.expected: Text is 4 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 4);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 4);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();
}

/**
 * @tc.name: HandleOnDeleteAction029
 * @tc.desc: test testInput deleteAction.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleOnDeleteAction029, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    std::string caseEmoji = "🤒";
    int32_t totalNumberOfEmoji = 12;
    int32_t bytesOfOneEmoji = GetEmojiStringLength(caseEmoji);
    const std::string txt = CreateEmojiStringWithLength(caseEmoji, totalNumberOfEmoji);
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    /**
     * @tc.step: step1. Set caretPosition and call DeleteBackward in end of text
     * @tc.expected: Text is 10 x caseEmoji
     */
    pattern_->SetCaretPosition(totalNumberOfEmoji * bytesOfOneEmoji);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    std::string result = CreateEmojiStringWithLength(caseEmoji, 10);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step2. Set caretPosition and call DeleteBackward in middle of text
     * @tc.expected: Text is 8 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 8);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 8);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step3. Set caretPosition and call DeleteForward in start of text
     * @tc.expected: Text is 6 x caseEmoji
     */
    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 6);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step4. Set caretPosition and call DeleteForward in middle of text
     * @tc.expected: Text is 4 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 4);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 4);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();
}

/**
 * @tc.name: HandleOnDeleteAction030
 * @tc.desc: test testInput deleteAction.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleOnDeleteAction030, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    std::string caseEmoji = "👺";
    int32_t totalNumberOfEmoji = 12;
    int32_t bytesOfOneEmoji = GetEmojiStringLength(caseEmoji);
    const std::string txt = CreateEmojiStringWithLength(caseEmoji, totalNumberOfEmoji);
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    /**
     * @tc.step: step1. Set caretPosition and call DeleteBackward in end of text
     * @tc.expected: Text is 10 x caseEmoji
     */
    pattern_->SetCaretPosition(totalNumberOfEmoji * bytesOfOneEmoji);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    std::string result = CreateEmojiStringWithLength(caseEmoji, 10);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step2. Set caretPosition and call DeleteBackward in middle of text
     * @tc.expected: Text is 8 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 8);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 8);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step3. Set caretPosition and call DeleteForward in start of text
     * @tc.expected: Text is 6 x caseEmoji
     */
    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 6);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step4. Set caretPosition and call DeleteForward in middle of text
     * @tc.expected: Text is 4 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 4);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 4);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();
}

/**
 * @tc.name: HandleOnDeleteAction031
 * @tc.desc: test testInput deleteAction.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleOnDeleteAction031, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    std::string caseEmoji = "😺";
    int32_t totalNumberOfEmoji = 12;
    int32_t bytesOfOneEmoji = GetEmojiStringLength(caseEmoji);
    const std::string txt = CreateEmojiStringWithLength(caseEmoji, totalNumberOfEmoji);
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    /**
     * @tc.step: step1. Set caretPosition and call DeleteBackward in end of text
     * @tc.expected: Text is 10 x caseEmoji
     */
    pattern_->SetCaretPosition(totalNumberOfEmoji * bytesOfOneEmoji);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    std::string result = CreateEmojiStringWithLength(caseEmoji, 10);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step2. Set caretPosition and call DeleteBackward in middle of text
     * @tc.expected: Text is 8 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 8);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 8);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step3. Set caretPosition and call DeleteForward in start of text
     * @tc.expected: Text is 6 x caseEmoji
     */
    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 6);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step4. Set caretPosition and call DeleteForward in middle of text
     * @tc.expected: Text is 4 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 4);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 4);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();
}

/**
 * @tc.name: HandleOnDeleteAction032
 * @tc.desc: test testInput deleteAction.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleOnDeleteAction032, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    std::string caseEmoji = "👃";
    int32_t totalNumberOfEmoji = 12;
    int32_t bytesOfOneEmoji = GetEmojiStringLength(caseEmoji);
    const std::string txt = CreateEmojiStringWithLength(caseEmoji, totalNumberOfEmoji);
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    /**
     * @tc.step: step1. Set caretPosition and call DeleteBackward in end of text
     * @tc.expected: Text is 10 x caseEmoji
     */
    pattern_->SetCaretPosition(totalNumberOfEmoji * bytesOfOneEmoji);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    std::string result = CreateEmojiStringWithLength(caseEmoji, 10);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step2. Set caretPosition and call DeleteBackward in middle of text
     * @tc.expected: Text is 8 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 8);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 8);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step3. Set caretPosition and call DeleteForward in start of text
     * @tc.expected: Text is 6 x caseEmoji
     */
    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 6);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    /**
     * @tc.step: step4. Set caretPosition and call DeleteForward in middle of text
     * @tc.expected: Text is 4 x caseEmoji
     */
    pattern_->SetCaretPosition(bytesOfOneEmoji * 4);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = CreateEmojiStringWithLength(caseEmoji, 4);
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();
}
} // namespace OHOS::Ace::NG
