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

#include "core/common/ime/text_editing_value.h"
#include "core/common/ime/text_input_action.h"
#include "core/common/ime/text_input_configuration.h"
#include "core/common/ime/text_input_formatter.h"
#include "core/common/ime/text_input_proxy.h"
#include "core/common/ime/text_input_type.h"
#include "frameworks/bridge/common/utils/utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
std::string TYPE_TEST = "type";
std::string OBSCURE_TEXT_TEST = "obscureText";
std::string ACTION_TEST = "action";
std::string AUTO_CORRECT_TEST = "autoCorrect";
std::string ACTION_LABEL_TEST = "actionLabel";
std::string CAPITALIZATION_TEST = "capitalization";
std::string KEYBOARD_APPEARANCE_TEST = "keyboardAppearance";
std::string STR_ACTION_LABEL_TEST = "test_actionLabel";
std::string STR_CAPITALIZATION_TEST = "test_capitalization";
std::string STR_KEYBOARD_APPEARANCE_TEST = "test_keyboardAppearance";
} // namespace

class ImeTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
    void SetUp() {}
    void TearDown() {}
};

/**
 * @tc.name: CastToTextInputType001
 * @tc.desc: Test cast to text input type.
 * @tc.type: FUNC
 */
HWTEST_F(ImeTest, CastToTextInputType001, TestSize.Level1)
{
    EXPECT_EQ(CastToTextInputType(1), TextInputType::MULTILINE);
    EXPECT_EQ(CastToTextInputType(-2), TextInputType::TEXT);
    EXPECT_EQ(CastToTextInputType(10), TextInputType::TEXT);
    EXPECT_EQ(CastToTextInputType(0), TextInputType::TEXT);
}

/**
 * @tc.name: CastToTextInputAction001
 * @tc.desc: Test convert to Text Input Operation.
 * @tc.type: FUNC
 */
HWTEST_F(ImeTest, CastToTextInputAction001, TestSize.Level1)
{
    EXPECT_EQ(CastToTextInputAction(1), TextInputAction::NONE);
    EXPECT_EQ(CastToTextInputAction(-2), TextInputAction::UNSPECIFIED);
    EXPECT_EQ(CastToTextInputAction(10), TextInputAction::UNSPECIFIED);
    EXPECT_EQ(CastToTextInputAction(0), TextInputAction::BEGIN);
}

/**
 * @tc.name: ToJsonString001
 * @tc.desc: Test to json string.
 * @tc.type: FUNC
 */
HWTEST_F(ImeTest, ToJsonString001, TestSize.Level1)
{
    TextInputConfiguration textInputConfiguration;

    auto jsonString = textInputConfiguration.ToJsonString();
    auto json = JsonUtil::ParseJsonString(jsonString);
    EXPECT_EQ(json->GetValue(TYPE_TEST)->GetInt(), static_cast<int32_t>(TextInputType::TEXT));
    EXPECT_EQ(json->GetValue(OBSCURE_TEXT_TEST)->GetBool(), false);
    EXPECT_EQ(json->GetValue(ACTION_TEST)->GetInt(), static_cast<int32_t>(TextInputAction::UNSPECIFIED));
    EXPECT_EQ(json->GetValue(AUTO_CORRECT_TEST)->GetBool(), false);
}

/**
 * @tc.name: ToJsonString002
 * @tc.desc: Test actionLabel,capitalization and keyboardAppearance not empty.
 * @tc.type: FUNC
 */
HWTEST_F(ImeTest, ToJsonString002, TestSize.Level1)
{
    TextInputConfiguration textInputConfiguration;
    textInputConfiguration.actionLabel = STR_ACTION_LABEL_TEST;
    textInputConfiguration.capitalization = STR_CAPITALIZATION_TEST;
    textInputConfiguration.keyboardAppearance = STR_KEYBOARD_APPEARANCE_TEST;

    auto jsonString = textInputConfiguration.ToJsonString();
    auto json = JsonUtil::ParseJsonString(jsonString);
    EXPECT_EQ(json->GetValue(ACTION_LABEL_TEST)->GetString(), STR_ACTION_LABEL_TEST);
    EXPECT_EQ(json->GetValue(CAPITALIZATION_TEST)->GetString(), STR_CAPITALIZATION_TEST);
    EXPECT_EQ(json->GetValue(KEYBOARD_APPEARANCE_TEST)->GetString(), STR_KEYBOARD_APPEARANCE_TEST);
}
} // namespace OHOS::Ace
