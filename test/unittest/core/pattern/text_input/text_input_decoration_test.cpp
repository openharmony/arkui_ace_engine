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

class TextInputDecorationUXTest : public TextInputBases {};

/**
 * @tc.name: TextInputToJsonValue004
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecorationUXTest, TextInputToJsonValue004, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::NONE);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::SOLID);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextInput JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto decorationJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(decorationJson, nullptr);
    /**
     * @tc.expected: check decoration in TextInput JSON is NONE, BLACK, SOLID
     */
    EXPECT_TRUE(decorationJson->Contains("type"));
    EXPECT_TRUE(decorationJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::NONE));
    EXPECT_TRUE(decorationJson->Contains("color"));
    EXPECT_TRUE(decorationJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(decorationJson->Contains("style"));
    EXPECT_TRUE(decorationJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::SOLID));
}

/**
 * @tc.name: TextInputToJsonValue005
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecorationUXTest, TextInputToJsonValue005, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::UNDERLINE);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::SOLID);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextInput JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto decorationJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(decorationJson, nullptr);
    /**
     * @tc.expected: check decoration in TextInput JSON is UNDERLINE, BLACK, SOLID
     */
    EXPECT_TRUE(decorationJson->Contains("type"));
    EXPECT_TRUE(decorationJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::UNDERLINE));
    EXPECT_TRUE(decorationJson->Contains("color"));
    EXPECT_TRUE(decorationJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(decorationJson->Contains("style"));
    EXPECT_TRUE(decorationJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::SOLID));
}

/**
 * @tc.name: TextInputToJsonValue006
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecorationUXTest, TextInputToJsonValue006, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::UNDERLINE);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::DOUBLE);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextInput JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto decorationJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(decorationJson, nullptr);
    /**
     * @tc.expected: check decoration in TextInput JSON is UNDERLINE, BLACK, DOUBLE
     */
    EXPECT_TRUE(decorationJson->Contains("type"));
    EXPECT_TRUE(decorationJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::UNDERLINE));
    EXPECT_TRUE(decorationJson->Contains("color"));
    EXPECT_TRUE(decorationJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(decorationJson->Contains("style"));
    EXPECT_TRUE(decorationJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::DOUBLE));
}

/**
 * @tc.name: TextInputToJsonValue007
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecorationUXTest, TextInputToJsonValue007, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::UNDERLINE);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::DOTTED);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextInput JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto decorationJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(decorationJson, nullptr);
    /**
     * @tc.expected: check decoration in TextInput JSON is UNDERLINE, BLACK, DOTTED
     */
    EXPECT_TRUE(decorationJson->Contains("type"));
    EXPECT_TRUE(decorationJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::UNDERLINE));
    EXPECT_TRUE(decorationJson->Contains("color"));
    EXPECT_TRUE(decorationJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(decorationJson->Contains("style"));
    EXPECT_TRUE(decorationJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::DOTTED));
}

/**
 * @tc.name: TextInputToJsonValue008
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecorationUXTest, TextInputToJsonValue008, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::UNDERLINE);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::DASHED);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextInput JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto decorationJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(decorationJson, nullptr);
    /**
     * @tc.expected: check decoration in TextInput JSON is UNDERLINE, BLACK, DASHED
     */
    EXPECT_TRUE(decorationJson->Contains("type"));
    EXPECT_TRUE(decorationJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::UNDERLINE));
    EXPECT_TRUE(decorationJson->Contains("color"));
    EXPECT_TRUE(decorationJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(decorationJson->Contains("style"));
    EXPECT_TRUE(decorationJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::DASHED));
}

/**
 * @tc.name: TextInputToJsonValue009
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecorationUXTest, TextInputToJsonValue009, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::UNDERLINE);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::WAVY);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextInput JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto decorationJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(decorationJson, nullptr);
    /**
     * @tc.expected: check decoration in TextInput JSON is UNDERLINE, BLACK, WAVY
     */
    EXPECT_TRUE(decorationJson->Contains("type"));
    EXPECT_TRUE(decorationJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::UNDERLINE));
    EXPECT_TRUE(decorationJson->Contains("color"));
    EXPECT_TRUE(decorationJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(decorationJson->Contains("style"));
    EXPECT_TRUE(decorationJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::WAVY));
}

/**
 * @tc.name: TextInputToJsonValue010
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecorationUXTest, TextInputToJsonValue010, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::UNDERLINE);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::INITIAL);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextInput JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto decorationJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(decorationJson, nullptr);
    /**
     * @tc.expected: check decoration in TextInput JSON is UNDERLINE, BLACK, INITIAL
     */
    EXPECT_TRUE(decorationJson->Contains("type"));
    EXPECT_TRUE(decorationJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::UNDERLINE));
    EXPECT_TRUE(decorationJson->Contains("color"));
    EXPECT_TRUE(decorationJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(decorationJson->Contains("style"));
    EXPECT_TRUE(decorationJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::INITIAL));
}

/**
 * @tc.name: TextInputToJsonValue011
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecorationUXTest, TextInputToJsonValue011, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::UNDERLINE);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::INHERIT);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextInput JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto decorationJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(decorationJson, nullptr);
    /**
     * @tc.expected: check decoration in TextInput JSON is UNDERLINE, BLACK, INHERIT
     */
    EXPECT_TRUE(decorationJson->Contains("type"));
    EXPECT_TRUE(decorationJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::UNDERLINE));
    EXPECT_TRUE(decorationJson->Contains("color"));
    EXPECT_TRUE(decorationJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(decorationJson->Contains("style"));
    EXPECT_TRUE(decorationJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::INHERIT));
}

/**
 * @tc.name: TextInputToJsonValue012
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecorationUXTest, TextInputToJsonValue012, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::OVERLINE);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::SOLID);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextInput JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto decorationJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(decorationJson, nullptr);
    /**
     * @tc.expected: check decoration in TextInput JSON is OVERLINE, BLACK, SOLID
     */
    EXPECT_TRUE(decorationJson->Contains("type"));
    EXPECT_TRUE(decorationJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::OVERLINE));
    EXPECT_TRUE(decorationJson->Contains("color"));
    EXPECT_TRUE(decorationJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(decorationJson->Contains("style"));
    EXPECT_TRUE(decorationJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::SOLID));
}


/**
 * @tc.name: TextInputToJsonValue012
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecorationUXTest, TextInputToJsonValue013, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::OVERLINE);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::DOUBLE);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextInput JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto decorationJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(decorationJson, nullptr);
    /**
     * @tc.expected: check decoration in TextInput JSON is OVERLINE, BLACK, DOUBLE
     */
    EXPECT_TRUE(decorationJson->Contains("type"));
    EXPECT_TRUE(decorationJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::OVERLINE));
    EXPECT_TRUE(decorationJson->Contains("color"));
    EXPECT_TRUE(decorationJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(decorationJson->Contains("style"));
    EXPECT_TRUE(decorationJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::DOUBLE));
}

/**
 * @tc.name: TextInputToJsonValue014
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecorationUXTest, TextInputToJsonValue014, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::OVERLINE);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::DOTTED);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextInput JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto decorationJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(decorationJson, nullptr);
    /**
     * @tc.expected: check decoration in TextInput JSON is OVERLINE, BLACK, DOTTED
     */
    EXPECT_TRUE(decorationJson->Contains("type"));
    EXPECT_TRUE(decorationJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::OVERLINE));
    EXPECT_TRUE(decorationJson->Contains("color"));
    EXPECT_TRUE(decorationJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(decorationJson->Contains("style"));
    EXPECT_TRUE(decorationJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::DOTTED));
}

/**
 * @tc.name: TextInputToJsonValue015
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecorationUXTest, TextInputToJsonValue015, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::OVERLINE);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::DASHED);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextInput JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto decorationJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(decorationJson, nullptr);
    /**
     * @tc.expected: check decoration in TextInput JSON is OVERLINE, BLACK, DASHED
     */
    EXPECT_TRUE(decorationJson->Contains("type"));
    EXPECT_TRUE(decorationJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::OVERLINE));
    EXPECT_TRUE(decorationJson->Contains("color"));
    EXPECT_TRUE(decorationJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(decorationJson->Contains("style"));
    EXPECT_TRUE(decorationJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::DASHED));
}

/**
 * @tc.name: TextInputToJsonValue016
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecorationUXTest, TextInputToJsonValue016, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::OVERLINE);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::WAVY);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextInput JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto decorationJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(decorationJson, nullptr);
    /**
     * @tc.expected: check decoration in TextInput JSON is OVERLINE, BLACK, WAVY
     */
    EXPECT_TRUE(decorationJson->Contains("type"));
    EXPECT_TRUE(decorationJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::OVERLINE));
    EXPECT_TRUE(decorationJson->Contains("color"));
    EXPECT_TRUE(decorationJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(decorationJson->Contains("style"));
    EXPECT_TRUE(decorationJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::WAVY));
}

/**
 * @tc.name: TextInputToJsonValue017
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecorationUXTest, TextInputToJsonValue017, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::OVERLINE);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::INITIAL);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextInput JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto decorationJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(decorationJson, nullptr);
    /**
     * @tc.expected: check decoration in TextInput JSON is OVERLINE, BLACK, INITIAL
     */
    EXPECT_TRUE(decorationJson->Contains("type"));
    EXPECT_TRUE(decorationJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::OVERLINE));
    EXPECT_TRUE(decorationJson->Contains("color"));
    EXPECT_TRUE(decorationJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(decorationJson->Contains("style"));
    EXPECT_TRUE(decorationJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::INITIAL));
}

/**
 * @tc.name: TextInputToJsonValue018
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecorationUXTest, TextInputToJsonValue018, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::OVERLINE);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::INHERIT);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextInput JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto decorationJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(decorationJson, nullptr);
    /**
     * @tc.expected: check decoration in TextInput JSON is OVERLINE, BLACK, INHERIT
     */
    EXPECT_TRUE(decorationJson->Contains("type"));
    EXPECT_TRUE(decorationJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::OVERLINE));
    EXPECT_TRUE(decorationJson->Contains("color"));
    EXPECT_TRUE(decorationJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(decorationJson->Contains("style"));
    EXPECT_TRUE(decorationJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::INHERIT));
}

/**
 * @tc.name: TextInputToJsonValue019
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecorationUXTest, TextInputToJsonValue019, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::LINE_THROUGH);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::SOLID);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextInput JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto decorationJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(decorationJson, nullptr);
    /**
     * @tc.expected: check decoration in TextInput JSON is LINE_THROUGH, BLACK, SOLID
     */
    EXPECT_TRUE(decorationJson->Contains("type"));
    EXPECT_TRUE(decorationJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::LINE_THROUGH));
    EXPECT_TRUE(decorationJson->Contains("color"));
    EXPECT_TRUE(decorationJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(decorationJson->Contains("style"));
    EXPECT_TRUE(decorationJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::SOLID));
}

/**
 * @tc.name: TextInputToJsonValue020
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecorationUXTest, TextInputToJsonValue020, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::LINE_THROUGH);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::DOUBLE);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextInput JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto decorationJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(decorationJson, nullptr);
    /**
     * @tc.expected: check decoration in TextInput JSON is LINE_THROUGH, BLACK, DOUBLE
     */
    EXPECT_TRUE(decorationJson->Contains("type"));
    EXPECT_TRUE(decorationJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::LINE_THROUGH));
    EXPECT_TRUE(decorationJson->Contains("color"));
    EXPECT_TRUE(decorationJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(decorationJson->Contains("style"));
    EXPECT_TRUE(decorationJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::DOUBLE));
}

/**
 * @tc.name: TextInputToJsonValue021
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecorationUXTest, TextInputToJsonValue021, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::LINE_THROUGH);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::DOTTED);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextInput JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto decorationJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(decorationJson, nullptr);
    /**
     * @tc.expected: check decoration in TextInput JSON is LINE_THROUGH, BLACK, DOTTED
     */
    EXPECT_TRUE(decorationJson->Contains("type"));
    EXPECT_TRUE(decorationJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::LINE_THROUGH));
    EXPECT_TRUE(decorationJson->Contains("color"));
    EXPECT_TRUE(decorationJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(decorationJson->Contains("style"));
    EXPECT_TRUE(decorationJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::DOTTED));
}

/**
 * @tc.name: TextInputToJsonValue022
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecorationUXTest, TextInputToJsonValue022, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::LINE_THROUGH);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::DASHED);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextInput JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto decorationJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(decorationJson, nullptr);
    /**
     * @tc.expected: check decoration in TextInput JSON is LINE_THROUGH, BLACK, DASHED
     */
    EXPECT_TRUE(decorationJson->Contains("type"));
    EXPECT_TRUE(decorationJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::LINE_THROUGH));
    EXPECT_TRUE(decorationJson->Contains("color"));
    EXPECT_TRUE(decorationJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(decorationJson->Contains("style"));
    EXPECT_TRUE(decorationJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::DASHED));
}

/**
 * @tc.name: TextInputToJsonValue023
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecorationUXTest, TextInputToJsonValue023, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::LINE_THROUGH);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::WAVY);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextInput JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto decorationJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(decorationJson, nullptr);
    /**
     * @tc.expected: check decoration in TextInput JSON is LINE_THROUGH, BLACK, WAVY
     */
    EXPECT_TRUE(decorationJson->Contains("type"));
    EXPECT_TRUE(decorationJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::LINE_THROUGH));
    EXPECT_TRUE(decorationJson->Contains("color"));
    EXPECT_TRUE(decorationJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(decorationJson->Contains("style"));
    EXPECT_TRUE(decorationJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::WAVY));
}

/**
 * @tc.name: TextInputToJsonValue024
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecorationUXTest, TextInputToJsonValue024, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::LINE_THROUGH);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::INITIAL);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextInput JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto decorationJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(decorationJson, nullptr);
    /**
     * @tc.expected: check decoration in TextInput JSON is LINE_THROUGH, BLACK, INITIAL
     */
    EXPECT_TRUE(decorationJson->Contains("type"));
    EXPECT_TRUE(decorationJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::LINE_THROUGH));
    EXPECT_TRUE(decorationJson->Contains("color"));
    EXPECT_TRUE(decorationJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(decorationJson->Contains("style"));
    EXPECT_TRUE(decorationJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::INITIAL));
}

/**
 * @tc.name: TextInputToJsonValue025
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecorationUXTest, TextInputToJsonValue025, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::LINE_THROUGH);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::INHERIT);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextInput JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto decorationJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(decorationJson, nullptr);
    /**
     * @tc.expected: check decoration in TextInput JSON is LINE_THROUGH, BLACK, INHERIT
     */
    EXPECT_TRUE(decorationJson->Contains("type"));
    EXPECT_TRUE(decorationJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::LINE_THROUGH));
    EXPECT_TRUE(decorationJson->Contains("color"));
    EXPECT_TRUE(decorationJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(decorationJson->Contains("style"));
    EXPECT_TRUE(decorationJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::INHERIT));
}

/**
 * @tc.name: TextInputToJsonValue026
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecorationUXTest, TextInputToJsonValue026, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::INHERIT);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::SOLID);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextInput JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto decorationJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(decorationJson, nullptr);
    /**
     * @tc.expected: check decoration in TextInput JSON is INHERIT, BLACK, SOLID
     */
    EXPECT_TRUE(decorationJson->Contains("type"));
    EXPECT_TRUE(decorationJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::INHERIT));
    EXPECT_TRUE(decorationJson->Contains("color"));
    EXPECT_TRUE(decorationJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(decorationJson->Contains("style"));
    EXPECT_TRUE(decorationJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::SOLID));
}

/**
 * @tc.name: TextInputToJsonValue027
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecorationUXTest, TextInputToJsonValue027, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::INHERIT);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::DOUBLE);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextInput JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto decorationJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(decorationJson, nullptr);
    /**
     * @tc.expected: check decoration in TextInput JSON is INHERIT, BLACK, DOUBLE
     */
    EXPECT_TRUE(decorationJson->Contains("type"));
    EXPECT_TRUE(decorationJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::INHERIT));
    EXPECT_TRUE(decorationJson->Contains("color"));
    EXPECT_TRUE(decorationJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(decorationJson->Contains("style"));
    EXPECT_TRUE(decorationJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::DOUBLE));
}

/**
 * @tc.name: TextInputToJsonValue028
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecorationUXTest, TextInputToJsonValue028, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::INHERIT);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::DOTTED);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextInput JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto decorationJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(decorationJson, nullptr);
    /**
     * @tc.expected: check decoration in TextInput JSON is INHERIT, BLACK, DOTTED
     */
    EXPECT_TRUE(decorationJson->Contains("type"));
    EXPECT_TRUE(decorationJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::INHERIT));
    EXPECT_TRUE(decorationJson->Contains("color"));
    EXPECT_TRUE(decorationJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(decorationJson->Contains("style"));
    EXPECT_TRUE(decorationJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::DOTTED));
}

/**
 * @tc.name: TextInputToJsonValue029
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecorationUXTest, TextInputToJsonValue029, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::INHERIT);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::DASHED);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextInput JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto decorationJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(decorationJson, nullptr);
    /**
     * @tc.expected: check decoration in TextInput JSON is INHERIT, BLACK, DASHED
     */
    EXPECT_TRUE(decorationJson->Contains("type"));
    EXPECT_TRUE(decorationJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::INHERIT));
    EXPECT_TRUE(decorationJson->Contains("color"));
    EXPECT_TRUE(decorationJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(decorationJson->Contains("style"));
    EXPECT_TRUE(decorationJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::DASHED));
}

/**
 * @tc.name: TextInputToJsonValue030
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecorationUXTest, TextInputToJsonValue030, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::INHERIT);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::WAVY);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextInput JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto decorationJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(decorationJson, nullptr);
    /**
     * @tc.expected: check decoration in TextInput JSON is INHERIT, BLACK, WAVY
     */
    EXPECT_TRUE(decorationJson->Contains("type"));
    EXPECT_TRUE(decorationJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::INHERIT));
    EXPECT_TRUE(decorationJson->Contains("color"));
    EXPECT_TRUE(decorationJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(decorationJson->Contains("style"));
    EXPECT_TRUE(decorationJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::WAVY));
}

/**
 * @tc.name: TextInputToJsonValue031
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecorationUXTest, TextInputToJsonValue031, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::INHERIT);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::INITIAL);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextInput JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto decorationJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(decorationJson, nullptr);
    /**
     * @tc.expected: check decoration in TextInput JSON is INHERIT, BLACK, INITIAL
     */
    EXPECT_TRUE(decorationJson->Contains("type"));
    EXPECT_TRUE(decorationJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::INHERIT));
    EXPECT_TRUE(decorationJson->Contains("color"));
    EXPECT_TRUE(decorationJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(decorationJson->Contains("style"));
    EXPECT_TRUE(decorationJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::INITIAL));
}

/**
 * @tc.name: TextInputToJsonValue032
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecorationUXTest, TextInputToJsonValue032, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::INHERIT);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::INHERIT);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextInput JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto decorationJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(decorationJson, nullptr);
    /**
     * @tc.expected: check decoration in TextInput JSON is INHERIT, BLACK, INHERIT
     */
    EXPECT_TRUE(decorationJson->Contains("type"));
    EXPECT_TRUE(decorationJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::INHERIT));
    EXPECT_TRUE(decorationJson->Contains("color"));
    EXPECT_TRUE(decorationJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(decorationJson->Contains("style"));
    EXPECT_TRUE(decorationJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::INHERIT));
}

/**
 * @tc.name: TextInputToJsonValue033
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecorationUXTest, TextInputToJsonValue033, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetLetterSpacing(0.0_px);
        model.SetLineHeight(0.0_px);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextInput JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    /**
     * @tc.expected: check letterSpacing in TextInput JSON is 0.00px
     */
    EXPECT_EQ(json->GetString("letterSpacing"), "0.00px");
    /**
     * @tc.expected: check lineHeight in TextInput JSON is 0.00px
     */
    EXPECT_EQ(json->GetString("lineHeight"), "0.00px");
}

/**
 * @tc.name: TextInputToJsonValue034
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecorationUXTest, TextInputToJsonValue034, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetLetterSpacing(2.0_px);
        model.SetLineHeight(3.0_px);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextInput JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    /**
     * @tc.expected: check letterSpacing in TextInput JSON is 2.00px
     */
    EXPECT_EQ(json->GetString("letterSpacing"), "2.00px");
    /**
     * @tc.expected: check lineHeight in TextInput JSON is 3.00px
     */
    EXPECT_EQ(json->GetString("lineHeight"), "3.00px");
}
} // namespace OHOS::Ace::NG
