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

#include "core/components_ng/pattern/text_field/text_field_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "textfield_test_ng_utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class TextFieldLayoutPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
    void SetUp() override;
    void TearDown() override;
    RefPtr<TextFieldLayoutProperty> GetTextFieldLayoutProperty();
    RefPtr<FrameNode> host_;
};

void TextFieldLayoutPropertyTestNg::SetUp() {}

void TextFieldLayoutPropertyTestNg::TearDown()
{
    host_ = nullptr;
}

RefPtr<TextFieldLayoutProperty> TextFieldLayoutPropertyTestNg::GetTextFieldLayoutProperty()
{
    host_ = TextFieldTestNgUtils::CreatTextFieldNode();
    return host_ ? host_->GetLayoutProperty<TextFieldLayoutProperty>() : nullptr;
}

/**
 * @tc.name: TextInputType001
 * @tc.desc: Update TextInputType layout property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutPropertyTestNg, TextInputType001, TestSize.Level1)
{
    auto textFieldLayoutProperty = GetTextFieldLayoutProperty();
    EXPECT_TRUE(textFieldLayoutProperty);
    if (!textFieldLayoutProperty) {
        return;
    }
    EXPECT_FALSE(textFieldLayoutProperty->HasTextInputType());
    textFieldLayoutProperty->UpdateTextInputType(TextInputType::MULTILINE);
    EXPECT_TRUE(textFieldLayoutProperty->HasTextInputType());
    EXPECT_EQ(textFieldLayoutProperty->GetTextInputTypeValue(), TextInputType::MULTILINE);

    textFieldLayoutProperty->UpdateTextInputType(TextInputType::EMAIL_ADDRESS);
    EXPECT_TRUE(textFieldLayoutProperty->HasTextInputType());
    EXPECT_EQ(textFieldLayoutProperty->GetTextInputTypeValue(), TextInputType::EMAIL_ADDRESS);
}

/**
 * @tc.name: TypeChanged001
 * @tc.desc: Update TypeChanged layout property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutPropertyTestNg, TypeChanged001, TestSize.Level1)
{
    auto textFieldLayoutProperty = GetTextFieldLayoutProperty();
    EXPECT_TRUE(textFieldLayoutProperty);
    if (!textFieldLayoutProperty) {
        return;
    }
    EXPECT_FALSE(textFieldLayoutProperty->HasTypeChanged());
    textFieldLayoutProperty->UpdateTypeChanged(true);
    EXPECT_TRUE(textFieldLayoutProperty->HasTypeChanged());
    EXPECT_TRUE(textFieldLayoutProperty->GetTypeChangedValue());

    textFieldLayoutProperty->UpdateTypeChanged(false);
    EXPECT_TRUE(textFieldLayoutProperty->HasTypeChanged());
    EXPECT_FALSE(textFieldLayoutProperty->GetTypeChangedValue());
}

/**
 * @tc.name: PlaceholderTextColor001
 * @tc.desc: Update PlaceholderTextColor layout property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutPropertyTestNg, PlaceholderTextColor001, TestSize.Level1)
{
    auto textFieldLayoutProperty = GetTextFieldLayoutProperty();
    EXPECT_TRUE(textFieldLayoutProperty);
    if (!textFieldLayoutProperty) {
        return;
    }
    EXPECT_FALSE(textFieldLayoutProperty->HasPlaceholderTextColor());
    textFieldLayoutProperty->UpdatePlaceholderTextColor(Color::RED);
    EXPECT_TRUE(textFieldLayoutProperty->HasPlaceholderTextColor());
}

/**
 * @tc.name: Font001
 * @tc.desc: Update Font structure layout property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutPropertyTestNg, Font001, TestSize.Level1)
{
    std::vector<std::string> fontFamilies;
    Font font { .fontWeight = Ace::FontWeight::W200,
                .fontSize = Dimension(10.0),
                .fontStyle = Ace::FontStyle::NORMAL,
                .fontFamilies = fontFamilies };
    auto textFieldLayoutProperty = GetTextFieldLayoutProperty();
    EXPECT_TRUE(textFieldLayoutProperty);
    if (!textFieldLayoutProperty) {
        return;
    }
    EXPECT_FALSE(textFieldLayoutProperty->HasPlaceholderFontSize());
    EXPECT_FALSE(textFieldLayoutProperty->HasPlaceholderItalicFontStyle());
    EXPECT_FALSE(textFieldLayoutProperty->HasPlaceholderFontWeight());
    EXPECT_FALSE(textFieldLayoutProperty->HasPlaceholderFontFamily());

    textFieldLayoutProperty->UpdatePlaceholderFontSize(font.fontSize.value());
    if (textFieldLayoutProperty->HasPlaceholderFontSize()) {
        EXPECT_EQ(textFieldLayoutProperty->GetPlaceholderFontSize().value().Value(), 10.0);
    }

    textFieldLayoutProperty->UpdatePlaceholderItalicFontStyle(font.fontStyle.value());
    if (textFieldLayoutProperty->HasPlaceholderItalicFontStyle()) {
        EXPECT_EQ(textFieldLayoutProperty->GetPlaceholderItalicFontStyle().value(), Ace::FontStyle::NORMAL);
    }

    textFieldLayoutProperty->UpdatePlaceholderFontWeight(font.fontWeight.value());
    if (textFieldLayoutProperty->HasPlaceholderFontWeight()) {
        EXPECT_EQ(textFieldLayoutProperty->GetPlaceholderFontWeight().value(), Ace::FontWeight::W200);
    }

    textFieldLayoutProperty->UpdatePlaceholderFontFamily(font.fontFamilies);
    if (textFieldLayoutProperty->HasPlaceholderFontFamily()) {
        EXPECT_EQ(textFieldLayoutProperty->GetPlaceholderFontFamily().value().size(), fontFamilies.size());
    }
}

/**
 * @tc.name: TextAlign001
 * @tc.desc: Update TextAlign layout property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutPropertyTestNg, TextAlign001, TestSize.Level1)
{
    auto textFieldLayoutProperty = GetTextFieldLayoutProperty();
    EXPECT_TRUE(textFieldLayoutProperty);
    if (!textFieldLayoutProperty) {
        return;
    }
    
    EXPECT_FALSE(textFieldLayoutProperty->HasTextAlign());
    textFieldLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
    if (textFieldLayoutProperty->HasTextAlign()) {
        EXPECT_EQ(textFieldLayoutProperty->GetTextAlign().value(), TextAlign::CENTER);
    }
}

/**
 * @tc.name: MaxLength001
 * @tc.desc: Update MaxLength layout property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutPropertyTestNg, MaxLength001, TestSize.Level1)
{
    auto textFieldLayoutProperty = GetTextFieldLayoutProperty();
    EXPECT_TRUE(textFieldLayoutProperty);
    if (!textFieldLayoutProperty) {
        return;
    }
    uint32_t length = 32;
    EXPECT_FALSE(textFieldLayoutProperty->HasMaxLength());
    textFieldLayoutProperty->UpdateMaxLength(length);
    if (textFieldLayoutProperty->HasMaxLength()) {
        EXPECT_EQ(textFieldLayoutProperty->GetMaxLength().value(), length);
    }
}

/**
 * @tc.name: MaxLines001
 * @tc.desc: Update MaxLines layout property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutPropertyTestNg, MaxLines001, TestSize.Level1)
{
    auto textFieldLayoutProperty = GetTextFieldLayoutProperty();
    EXPECT_TRUE(textFieldLayoutProperty);
    if (!textFieldLayoutProperty) {
        return;
    }
    uint32_t lines = 32;
    textFieldLayoutProperty->UpdateMaxLines(lines);
    if (textFieldLayoutProperty->HasMaxLines()) {
        EXPECT_EQ(textFieldLayoutProperty->GetMaxLines().value(), lines);
    }
}

/**
 * @tc.name: FontSize001
 * @tc.desc: Update FontSize layout property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutPropertyTestNg, FontSize001, TestSize.Level1)
{
    auto textFieldLayoutProperty = GetTextFieldLayoutProperty();
    EXPECT_TRUE(textFieldLayoutProperty);
    if (!textFieldLayoutProperty) {
        return;
    }
    EXPECT_FALSE(textFieldLayoutProperty->HasFontSize());
    textFieldLayoutProperty->UpdateFontSize(Dimension(10.0));
    if (textFieldLayoutProperty->HasFontSize()) {
        EXPECT_EQ(textFieldLayoutProperty->GetFontSize().value().Value(), 10.0);
    }
}

/**
 * @tc.name: PreferredTextLineHeightNeedToUpdate001
 * @tc.desc: Update PreferredTextLineHeightNeedToUpdate layout property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutPropertyTestNg, PreferredTextLineHeightNeedToUpdate001, TestSize.Level1)
{
    auto textFieldLayoutProperty = GetTextFieldLayoutProperty();
    EXPECT_TRUE(textFieldLayoutProperty);
    if (!textFieldLayoutProperty) {
        return;
    }
    EXPECT_FALSE(textFieldLayoutProperty->HasPreferredTextLineHeightNeedToUpdate());
    textFieldLayoutProperty->UpdatePreferredTextLineHeightNeedToUpdate(true);
    if (textFieldLayoutProperty->HasPreferredTextLineHeightNeedToUpdate()) {
        EXPECT_TRUE(textFieldLayoutProperty->GetPreferredTextLineHeightNeedToUpdate().value());
    }
}

/**
 * @tc.name: TextColor001
 * @tc.desc: Update TextColor layout property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutPropertyTestNg, TextColor001, TestSize.Level1)
{
    auto textFieldLayoutProperty = GetTextFieldLayoutProperty();
    EXPECT_TRUE(textFieldLayoutProperty);
    if (!textFieldLayoutProperty) {
        return;
    }
    EXPECT_FALSE(textFieldLayoutProperty->HasTextColor());
    textFieldLayoutProperty->UpdateTextColor(Color::RED);
    if (textFieldLayoutProperty->HasTextColor()) {
        EXPECT_EQ(textFieldLayoutProperty->GetTextColor().value(), Color::RED);
    }
}

/**
 * @tc.name: ItalicFontStyle001
 * @tc.desc: Update ItalicFontStyle layout property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutPropertyTestNg, ItalicFontStyle001, TestSize.Level1)
{
    auto textFieldLayoutProperty = GetTextFieldLayoutProperty();
    EXPECT_TRUE(textFieldLayoutProperty);
    if (!textFieldLayoutProperty) {
        return;
    }
    EXPECT_FALSE(textFieldLayoutProperty->HasItalicFontStyle());
    textFieldLayoutProperty->UpdateItalicFontStyle(Ace::FontStyle::NORMAL);
    if (textFieldLayoutProperty->HasItalicFontStyle()) {
        EXPECT_EQ(textFieldLayoutProperty->GetItalicFontStyle().value(), Ace::FontStyle::NORMAL);
    }
}

/**
 * @tc.name: FontFamily001
 * @tc.desc: Update FontFamily layout property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutPropertyTestNg, FontFamily001, TestSize.Level1)
{
    auto textFieldLayoutProperty = GetTextFieldLayoutProperty();
    EXPECT_TRUE(textFieldLayoutProperty);
    if (!textFieldLayoutProperty) {
        return;
    }
    std::vector<std::string> fontFamilies;
    EXPECT_FALSE(textFieldLayoutProperty->HasFontFamily());
    textFieldLayoutProperty->UpdateFontFamily(fontFamilies);
    if (textFieldLayoutProperty->HasFontFamily()) {
        EXPECT_EQ(textFieldLayoutProperty->GetFontFamily().value().size(), fontFamilies.size());
    }
}

/**
 * @tc.name: InputFilter001
 * @tc.desc: Update InputFilter layout property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutPropertyTestNg, InputFilter001, TestSize.Level1)
{
    auto textFieldLayoutProperty = GetTextFieldLayoutProperty();
    EXPECT_TRUE(textFieldLayoutProperty);
    if (!textFieldLayoutProperty) {
        return;
    }
    std::string filterTest = "filterTest";
    EXPECT_FALSE(textFieldLayoutProperty->HasInputFilter());
    textFieldLayoutProperty->UpdateInputFilter(filterTest);
    if (textFieldLayoutProperty->HasInputFilter()) {
        EXPECT_EQ(textFieldLayoutProperty->GetInputFilterValue(), filterTest);
    }
}

/**
 * @tc.name: ShowPasswordIcon001
 * @tc.desc: Update ShowPasswordIcon layout property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutPropertyTestNg, ShowPasswordIcon001, TestSize.Level1)
{
    auto textFieldLayoutProperty = GetTextFieldLayoutProperty();
    EXPECT_TRUE(textFieldLayoutProperty);
    if (!textFieldLayoutProperty) {
        return;
    }
    EXPECT_FALSE(textFieldLayoutProperty->HasShowPasswordIcon());
    textFieldLayoutProperty->UpdateShowPasswordIcon(true);
    if (textFieldLayoutProperty->HasShowPasswordIcon()) {
        EXPECT_TRUE(textFieldLayoutProperty->GetShowPasswordIcon().value());
    }
}

/**
 * @tc.name: CopyOptions001
 * @tc.desc: Update CopyOptions layout property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutPropertyTestNg, CopyOptions001, TestSize.Level1)
{
    auto textFieldLayoutProperty = GetTextFieldLayoutProperty();
    EXPECT_TRUE(textFieldLayoutProperty);
    if (!textFieldLayoutProperty) {
        return;
    }
    EXPECT_FALSE(textFieldLayoutProperty->HasCopyOptions());
    textFieldLayoutProperty->UpdateCopyOptions(CopyOptions::Local);
    if (textFieldLayoutProperty->HasCopyOptions()) {
        EXPECT_EQ(textFieldLayoutProperty->GetCopyOptions().value(), CopyOptions::Local);
    }
}
} // namespace OHOS::Ace::NG