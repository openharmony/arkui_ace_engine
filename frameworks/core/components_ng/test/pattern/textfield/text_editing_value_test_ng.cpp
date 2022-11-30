/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/text_field/text_editing_value_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string EMPTY_TEXT_VALUE;
const std::string TEXT_EDITING_VALUE("textEditingValue");
constexpr int32_t ONECE_MOVE_POS = 1;
} // namespace
class TextEditingValueTestNG : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
    void SetUp() override;
    void TearDown() override;
};

void TextEditingValueTestNG::SetUp() {}

void TextEditingValueTestNG::TearDown() {}

/**
 * @tc.name: GetWideText001
 * @tc.desc: test GetWideText
 * @tc.type: FUNC
 */
HWTEST_F(TextEditingValueTestNG, GetWideText001, TestSize.Level1)
{
    struct TextEditingValueNG textEditingStructure;
    EXPECT_EQ(StringUtils::ToString(textEditingStructure.GetWideText()), EMPTY_TEXT_VALUE);
    textEditingStructure.text = TEXT_EDITING_VALUE;
    EXPECT_EQ(StringUtils::ToString(textEditingStructure.GetWideText()), TEXT_EDITING_VALUE);
}

/**
 * @tc.name: CursorMoveLeft001
 * @tc.desc: test CursorMoveLeft
 * @tc.type: FUNC
 */
HWTEST_F(TextEditingValueTestNG, CursorMoveLeft001, TestSize.Level1)
{
    struct TextEditingValueNG textEditingStructure;
    textEditingStructure.text = TEXT_EDITING_VALUE;
    auto textLength = static_cast<int32_t>(textEditingStructure.text.size());
    textEditingStructure.CursorMoveLeft();
    EXPECT_EQ(textEditingStructure.caretPosition, 0);
    textEditingStructure.caretPosition = textLength;
    textEditingStructure.CursorMoveLeft();
    EXPECT_EQ(textEditingStructure.caretPosition, textLength - ONECE_MOVE_POS);
}

/**
 * @tc.name: CursorMoveRight001
 * @tc.desc: test CursorMoveRight
 * @tc.type: FUNC
 */
HWTEST_F(TextEditingValueTestNG, CursorMoveRight001, TestSize.Level1)
{
    struct TextEditingValueNG textEditingStructure;
    textEditingStructure.text = TEXT_EDITING_VALUE;
    auto textLength = static_cast<int32_t>(textEditingStructure.text.size());
    textEditingStructure.CursorMoveRight();
    EXPECT_EQ(textEditingStructure.caretPosition, ONECE_MOVE_POS);
    textEditingStructure.caretPosition = textLength;
    textEditingStructure.CursorMoveRight();
    EXPECT_EQ(textEditingStructure.caretPosition, textLength);
}

/**
 * @tc.name: CursorMoveToPosition001
 * @tc.desc: test CursorMoveToPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextEditingValueTestNG, CursorMoveToPosition001, TestSize.Level1)
{
    struct TextEditingValueNG textEditingStructure;
    textEditingStructure.text = TEXT_EDITING_VALUE;
    auto textLength = static_cast<int32_t>(textEditingStructure.text.size());
    textEditingStructure.CursorMoveToPosition(-1);
    EXPECT_EQ(textEditingStructure.caretPosition, 0);
    textEditingStructure.CursorMoveToPosition(textLength + ONECE_MOVE_POS);
    EXPECT_EQ(textEditingStructure.caretPosition, textLength);
    textEditingStructure.CursorMoveToPosition(textLength - ONECE_MOVE_POS);
    EXPECT_EQ(textEditingStructure.caretPosition, textLength - ONECE_MOVE_POS);
}

/**
 * @tc.name: GetValueBeforeCursor_GetValueAfterCursor001
 * @tc.desc: test GetValueBeforeCursor and GetValueAfterCursor
 * @tc.type: FUNC
 */
HWTEST_F(TextEditingValueTestNG, GetValueBeforeCursor_GetValueAfterCursor001, TestSize.Level1)
{
    struct TextEditingValueNG textEditingStructure;
    EXPECT_EQ(textEditingStructure.GetValueBeforeCursor(), EMPTY_TEXT_VALUE);
    EXPECT_EQ(textEditingStructure.GetValueAfterCursor(), EMPTY_TEXT_VALUE);
    textEditingStructure.text = TEXT_EDITING_VALUE;
    textEditingStructure.CursorMoveRight();
    EXPECT_EQ(textEditingStructure.GetValueBeforeCursor(), "t");
    EXPECT_EQ(textEditingStructure.GetValueAfterCursor(), "extEditingValue");
}

/**
 * @tc.name: GetValueBeforePosition_GetValueAfterPosition001
 * @tc.desc: test GetValueBeforePosition and GetValueAfterPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextEditingValueTestNG, GetValueBeforePosition_GetValueAfterPosition001, TestSize.Level1)
{
    struct TextEditingValueNG textEditingStructure;
    EXPECT_EQ(textEditingStructure.GetValueBeforePosition(ONECE_MOVE_POS), EMPTY_TEXT_VALUE);
    EXPECT_EQ(textEditingStructure.GetValueAfterPosition(ONECE_MOVE_POS), EMPTY_TEXT_VALUE);
    textEditingStructure.text = TEXT_EDITING_VALUE;
    EXPECT_EQ(textEditingStructure.GetValueBeforePosition(ONECE_MOVE_POS), "t");
    EXPECT_EQ(textEditingStructure.GetValueAfterPosition(ONECE_MOVE_POS), "extEditingValue");
}

/**
 * @tc.name: GetSelectedText001
 * @tc.desc: test GetSelectedText
 * @tc.type: FUNC
 */
HWTEST_F(TextEditingValueTestNG, GetSelectedText001, TestSize.Level1)
{
    struct TextEditingValueNG textEditingStructure;
    EXPECT_EQ(textEditingStructure.GetSelectedText(ONECE_MOVE_POS, ONECE_MOVE_POS * 2), EMPTY_TEXT_VALUE);
    textEditingStructure.text = TEXT_EDITING_VALUE;
    auto textLength = static_cast<int32_t>(textEditingStructure.text.size());
    EXPECT_GT(textLength, 0);
    EXPECT_EQ(textEditingStructure.GetSelectedText(textLength, 0), EMPTY_TEXT_VALUE);
    EXPECT_EQ(textEditingStructure.GetSelectedText(0, textLength), "textEditingValue");
}

/**
 * @tc.name: ToString001
 * @tc.desc: test ToString
 * @tc.type: FUNC
 */
HWTEST_F(TextEditingValueTestNG, ToString001, TestSize.Level1)
{
    struct TextEditingValueNG textEditingStructure;
    textEditingStructure.text = TEXT_EDITING_VALUE;
    textEditingStructure.CursorMoveRight();
    EXPECT_EQ(textEditingStructure.ToString(), "t|extEditingValue");
}

/**
 * @tc.name: Reset001
 * @tc.desc: test Reset
 * @tc.type: FUNC
 */
HWTEST_F(TextEditingValueTestNG, Reset001, TestSize.Level1)
{
    struct TextEditingValueNG textEditingStructure;
    textEditingStructure.text = TEXT_EDITING_VALUE;
    textEditingStructure.CursorMoveRight();
    textEditingStructure.Reset();
    EXPECT_EQ(textEditingStructure.text, EMPTY_TEXT_VALUE);
    EXPECT_EQ(textEditingStructure.caretPosition, 0);
}

/**
 * @tc.name: operator001
 * @tc.desc: test operator
 * @tc.type: FUNC
 */
HWTEST_F(TextEditingValueTestNG, operator001, TestSize.Level1)
{
    struct TextEditingValueNG textEditingStructure1;
    struct TextEditingValueNG textEditingStructure2;
    textEditingStructure1.text = TEXT_EDITING_VALUE;
    textEditingStructure1.caretPosition = 1;
    textEditingStructure2.text = TEXT_EDITING_VALUE;
    textEditingStructure2.caretPosition = 2;
    EXPECT_EQ(textEditingStructure1, textEditingStructure2);
}
} // namespace OHOS::Ace::NG
