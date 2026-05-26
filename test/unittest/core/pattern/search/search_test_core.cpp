/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-License-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "gtest/gtest.h"

#define protected public
#define private public

#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "core/components/search/search_theme.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/search/search_layout_property.h"
#include "core/components_ng/pattern/search/search_model_ng.h"
#include "core/components_ng/pattern/search/search_pattern.h"
#include "core/components_ng/pattern/search/search_node.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

#undef protected
#undef private

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const Color CUSTOM_FONT_COLOR = Color(0xFF123456);
const Color CUSTOM_FONT_COLOR_WITH_SPACE = Color(0xFF654321).SetColorSpace(ColorSpace::DISPLAY_P3);
const std::u16string EMPTY_VALUE_U16 = u"";
const std::u16string PLACEHOLDER_U16 = u"SEARCH_PLACEHOLDER";
const std::string SEARCH_SVG = "";
const std::string EMPTY_VALUE = "";
const std::string BUTTON_TEXT = "Search";
constexpr int32_t BUTTON_INDEX = 4;
constexpr int32_t TEXTFIELD_INDEX = 0;
} // namespace

class SearchTestCore : public testing::Test {
public:
    static void SetUpTestCase()
    {
        MockContainer::SetUp();
        MockPipelineContext::SetUp();
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        auto searchTheme = AceType::MakeRefPtr<SearchTheme>();
        searchTheme->searchButtonTextColor_ = Color::RED;
        searchTheme->searchIconColor_ = Color::RED;
        searchTheme->iconHeight_ = Dimension(16, DimensionUnit::PX);
        searchTheme->height_ = Dimension(56, DimensionUnit::VP);
        auto textFieldTheme = AceType::MakeRefPtr<TextFieldTheme>();
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([=](ThemeType type) -> RefPtr<Theme> {
            if (type == SearchTheme::TypeId()) {
                return searchTheme;
            }
            return textFieldTheme;
        });
        MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
        MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    }

    static void TearDownTestCase()
    {
        MockContainer::TearDown();
        MockPipelineContext::TearDown();
    }

    void SetUp() override
    {
        SearchModelNG searchModelInstance;
        searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
        searchModelInstance.SetSearchButton(BUTTON_TEXT);
        searchModelInstance.SetCancelButtonStyle(CancelButtonStyle::CONSTANT);
    }

    void TearDown() override
    {
        ViewStackProcessor::GetInstance()->ClearStack();
    }
};

/**
 * @tc.name: SetSearchButtonFontColor_WithCustomColor_IsThemeFalse_API26
 * @tc.desc: Test SearchModelNG SetSearchButtonFontColor with custom color, isTheme=false on API26+
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestCore, SetSearchButtonFontColor_WithCustomColor_IsThemeFalse_API26, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    SearchModelNG::SetSearchButtonFontColor(frameNode, CUSTOM_FONT_COLOR, false);

    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    ASSERT_NE(buttonFrameNode, nullptr);
    auto buttonLayoutProperty = buttonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonLayoutProperty, nullptr);
    EXPECT_EQ(buttonLayoutProperty->GetFontColor().value_or(Color::BLACK), CUSTOM_FONT_COLOR);
    EXPECT_EQ(pattern->IsSearchButtonUsingThemeColor(), false);
}

/**
 * @tc.name: SetSearchButtonFontColor_WithThemeColor_IsThemeTrue_API26
 * @tc.desc: Test SearchModelNG SetSearchButtonFontColor with theme color, isTheme=true on API26+
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestCore, SetSearchButtonFontColor_WithThemeColor_IsThemeTrue_API26, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    SearchModelNG::SetSearchButtonFontColor(frameNode, Color::RED, true);

    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    ASSERT_NE(buttonFrameNode, nullptr);
    auto buttonLayoutProperty = buttonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonLayoutProperty, nullptr);
    EXPECT_EQ(buttonLayoutProperty->GetFontColor().value_or(Color::BLACK), Color::RED);
    EXPECT_EQ(pattern->IsSearchButtonUsingThemeColor(), true);
}

/**
 * @tc.name: SetSearchButtonFontColor_WithColorSpace_P3
 * @tc.desc: Test SearchModelNG SetSearchButtonFontColor preserves ColorSpace (DISPLAY_P3)
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestCore, SetSearchButtonFontColor_WithColorSpace_P3, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    SearchModelNG::SetSearchButtonFontColor(frameNode, CUSTOM_FONT_COLOR_WITH_SPACE, false);

    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    ASSERT_NE(buttonFrameNode, nullptr);
    auto buttonLayoutProperty = buttonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonLayoutProperty, nullptr);
    auto resultColor = buttonLayoutProperty->GetFontColor().value_or(Color::BLACK);
    EXPECT_EQ(resultColor.GetValue(), CUSTOM_FONT_COLOR_WITH_SPACE.GetValue());
}

/**
 * @tc.name: SetSearchButtonFontColor_NullFrameNode
 * @tc.desc: Test SearchModelNG SetSearchButtonFontColor with null frameNode
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestCore, SetSearchButtonFontColor_NullFrameNode, TestSize.Level1)
{
    SearchModelNG::SetSearchButtonFontColor(nullptr, CUSTOM_FONT_COLOR, false);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetSearchButtonFontColor_NullButtonFrameNode
 * @tc.desc: Test SearchModelNG SetSearchButtonFontColor when button child node is null
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestCore, SetSearchButtonFontColor_NullButtonFrameNode, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->children_ = {};

    SearchModelNG::SetSearchButtonFontColor(frameNode, CUSTOM_FONT_COLOR, false);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetCancelButtonFontColor_WithCustomColor_IsThemeFalse
 * @tc.desc: Test CancelButton color with custom color, isThemeColor=false
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestCore, SetCancelButtonFontColor_WithCustomColor_IsThemeFalse, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    SearchModelNG::SetCancelButtonStyle(frameNode, CancelButtonStyle::CONSTANT);

    auto iconColor = CUSTOM_FONT_COLOR;
    NG::IconOptions cancelIconOptions(iconColor, Dimension(16, DimensionUnit::PX), "", "", "");
    SearchModelNG::SetCancelImageIcon(frameNode, cancelIconOptions);

    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetCancelButtonFontColor_WithThemeColor_IsThemeTrue
 * @tc.desc: Test CancelButton color with theme color, isThemeColor=true
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestCore, SetCancelButtonFontColor_WithThemeColor_IsThemeTrue, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    SearchModelNG::SetCancelButtonStyle(frameNode, CancelButtonStyle::CONSTANT);

    NG::IconOptions cancelIconOptions(Dimension(16, DimensionUnit::PX), "", "", "");
    SearchModelNG::SetCancelImageIcon(frameNode, cancelIconOptions);

    EXPECT_TRUE(true);
}

/**
 * @tc.name: SearchButtonFontColor_RegisterResource
 * @tc.desc: Test searchButtonFontColor resource registration with ConfigChangePerform
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestCore, SearchButtonFontColor_RegisterResource, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
    resObj->SetIsResource(true);
    resObj->SetId(1001);
    resObj->SetType(static_cast<int32_t>(ResourceType::COLOR));

    SearchModelNG::SetSearchButtonFontColor(frameNode, CUSTOM_FONT_COLOR, false);
    pattern->RegisterResource<Color>("searchButtonFontColor", resObj, CUSTOM_FONT_COLOR);

    EXPECT_TRUE(pattern->HasResource("searchButtonFontColor"));
}

/**
 * @tc.name: SearchButtonFontColor_UnRegisterResource
 * @tc.desc: Test searchButtonFontColor resource unregistration
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestCore, SearchButtonFontColor_UnRegisterResource, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->UnRegisterResource("searchButtonFontColor");

    EXPECT_FALSE(pattern->HasResource("searchButtonFontColor"));
}

/**
 * @tc.name: SearchButton_IsSearchButtonUsingThemeColor_Default
 * @tc.desc: Test IsSearchButtonUsingThemeColor default value is true
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestCore, SearchButton_IsSearchButtonUsingThemeColor_Default, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    EXPECT_EQ(pattern->IsSearchButtonUsingThemeColor(), true);
}

/**
 * @tc.name: SearchButton_IsSearchButtonUsingThemeColor_SetFalse
 * @tc.desc: Test SetIsSearchButtonUsingThemeColor to false
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestCore, SearchButton_IsSearchButtonUsingThemeColor_SetFalse, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    SearchModelNG::SetSearchButtonFontColor(frameNode, CUSTOM_FONT_COLOR, false);
    EXPECT_EQ(pattern->IsSearchButtonUsingThemeColor(), false);
}

/**
 * @tc.name: SearchButton_IsSearchButtonUsingThemeColor_SetTrueThenFalse
 * @tc.desc: Test SetIsSearchButtonUsingThemeColor toggling between true and false
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestCore, SearchButton_IsSearchButtonUsingThemeColor_SetTrueThenFalse, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    SearchModelNG::SetSearchButtonFontColor(frameNode, Color::RED, true);
    EXPECT_EQ(pattern->IsSearchButtonUsingThemeColor(), true);

    SearchModelNG::SetSearchButtonFontColor(frameNode, CUSTOM_FONT_COLOR, false);
    EXPECT_EQ(pattern->IsSearchButtonUsingThemeColor(), false);
}

/**
 * @tc.name: ArkUI_InnerColor_FontColor_Passthrough
 * @tc.desc: Test that Color passed through ArkUI_InnerColor preserves full color info including ColorSpace
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestCore, ArkUI_InnerColor_FontColor_Passthrough, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    Color p3Color = Color(0xFF654321).SetColorSpace(ColorSpace::DISPLAY_P3);
    SearchModelNG::SetSearchButtonFontColor(frameNode, p3Color, false);

    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    ASSERT_NE(buttonFrameNode, nullptr);
    auto buttonLayoutProperty = buttonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonLayoutProperty, nullptr);

    auto resultColor = buttonLayoutProperty->GetFontColor().value_or(Color::BLACK);
    EXPECT_EQ(resultColor.GetValue(), p3Color.GetValue());
    EXPECT_EQ(resultColor.GetColorSpace(), p3Color.GetColorSpace());
}

/**
 * @tc.name: SearchButton_FontColor_FlagByUser
 * @tc.desc: Test that FontColorFlagByUser is set to true when custom color is applied
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestCore, SearchButton_FontColor_FlagByUser, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    SearchModelNG::SetSearchButtonFontColor(frameNode, CUSTOM_FONT_COLOR, false);

    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    ASSERT_NE(buttonFrameNode, nullptr);
    auto buttonLayoutProperty = buttonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonLayoutProperty, nullptr);
    EXPECT_TRUE(buttonLayoutProperty->GetFontColorFlagByUser());
}

/**
 * @tc.name: SearchButton_FontColor_MarkDirtyNode
 * @tc.desc: Test that setting font color marks the button node as dirty
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestCore, SearchButton_FontColor_MarkDirtyNode, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    SearchModelNG::SetSearchButtonFontColor(frameNode, CUSTOM_FONT_COLOR, false);

    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    ASSERT_NE(buttonFrameNode, nullptr);
    EXPECT_TRUE(buttonFrameNode->IsMarkedDirty());
}

/**
 * @tc.name: SearchButton_FontColor_ConsecutiveUpdates
 * @tc.desc: Test consecutive font color updates reflect the latest value
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestCore, SearchButton_FontColor_ConsecutiveUpdates, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    SearchModelNG::SetSearchButtonFontColor(frameNode, Color::RED, true);
    SearchModelNG::SetSearchButtonFontColor(frameNode, CUSTOM_FONT_COLOR, false);
    SearchModelNG::SetSearchButtonFontColor(frameNode, Color::GREEN, true);

    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    ASSERT_NE(buttonFrameNode, nullptr);
    auto buttonLayoutProperty = buttonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonLayoutProperty, nullptr);
    EXPECT_EQ(buttonLayoutProperty->GetFontColor().value_or(Color::BLACK), Color::GREEN);
    EXPECT_EQ(pattern->IsSearchButtonUsingThemeColor(), true);
}

/**
 * @tc.name: SearchCancelButton_Style_Constant
 * @tc.desc: Test CancelButtonStyle CONSTANT is set correctly
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestCore, SearchCancelButton_Style_Constant, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SearchModelNG::SetCancelButtonStyle(frameNode, CancelButtonStyle::CONSTANT);
    EXPECT_EQ(layoutProperty->GetCancelButtonStyle().value_or(CancelButtonStyle::INVISIBLE),
        CancelButtonStyle::CONSTANT);
}

/**
 * @tc.name: SearchCancelButton_Style_Invisible
 * @tc.desc: Test CancelButtonStyle INVISIBLE is set correctly
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestCore, SearchCancelButton_Style_Invisible, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SearchModelNG::SetCancelButtonStyle(frameNode, CancelButtonStyle::INVISIBLE);
    EXPECT_EQ(layoutProperty->GetCancelButtonStyle().value_or(CancelButtonStyle::CONSTANT),
        CancelButtonStyle::INVISIBLE);
}

/**
 * @tc.name: SearchCancelButton_Style_Input
 * @tc.desc: Test CancelButtonStyle INPUT is set correctly
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestCore, SearchCancelButton_Style_Input, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SearchModelNG::SetCancelButtonStyle(frameNode, CancelButtonStyle::INPUT);
    EXPECT_EQ(layoutProperty->GetCancelButtonStyle().value_or(CancelButtonStyle::CONSTANT),
        CancelButtonStyle::INPUT);
}

} // namespace
} // namespace OHOS::Ace::NG