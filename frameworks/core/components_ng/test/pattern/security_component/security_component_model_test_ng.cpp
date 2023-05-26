/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include <algorithm>
#include <cstddef>
#include <optional>
#include <utility>

#include "gtest/gtest.h"

#define protected public
#define private public
#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/system_properties.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/security_component/location_button/location_button_common.h"
#include "core/components_ng/pattern/security_component/location_button/location_button_model_ng.h"
#include "core/components_ng/pattern/security_component/security_component_pattern.h"
#include "core/components_ng/pattern/security_component/security_component_theme.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"
#include "core/pipeline_ng/ui_task_scheduler.h"
#undef protected
#undef private

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    constexpr float DEFAULT_ICON_SIZE = 16.0f;
    constexpr float DEFAULT_FONT_SIZE = 16.0f;
    constexpr float DEFAULT_ICON_MIN_SIZE = 12.0f;
    constexpr float DEFAULT_FONT_MIN_SIZE = 12.0f;
    constexpr float DEFAULT_PADDING = 10.0f;
    constexpr float DEFAULT_BORDER_RADIUS = 1.0f;
    constexpr float DEFAULT_BORDER_WIDTH = 1.0f;
    constexpr float DEFAULT_PADDING_WITHOUT_BG = 4.0f;
    constexpr float DEFAULT_BUTTON_SIZE = 20.0f;
    const std::string DEFAULT_TEXT = "Add Location";
    constexpr int INDEX_ZERO = 0;
    constexpr int INDEX_ONE = 1;
    constexpr int INDEX_TWO = 2;
    constexpr int INDEX_SIZE = 3;
}

class SecurityComponentModelTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
protected:
    static RefPtr<FrameNode> CreateSecurityComponent(int32_t text, int32_t icon,
        SecurityComponentBackgroundType backgroundType);
    static void CreateSecurityComponentNotFinish(int32_t text, int32_t icon,
        SecurityComponentBackgroundType backgroundType);
    static RefPtr<LayoutWrapper> CreateLayoutWrapper(RefPtr<FrameNode>& node);
    static RefPtr<LayoutWrapper> CreateSecurityComponentLayoutWrapper(RefPtr<FrameNode>& node);
    static void CheckSecurityComponentDefaultProp(RefPtr<FrameNode>& node);
    static void InitDefaultTheme(RefPtr<SecurityComponentTheme>& theme);
    static void SetUserDefinedPropty();
};

class MockSecurityModelNG : public SecurityComponentModelNG {
public:
    void Create(int32_t text, int32_t icon,
        SecurityComponentBackgroundType backgroundType) override
    {
        CreateCommon(V2::SEC_LOCATION_BUTTON_ETS_TAG,
            text, icon, backgroundType, []() { return AceType::MakeRefPtr<SecurityComponentPattern>();});
    }

    bool GetIconResource(int32_t iconStyle, InternalResource::ResourceId& id) override
    {
        id = InternalResource::ResourceId::LOCATION_BUTTON_FILLED_SVG;
        return true;
    }

    bool GetTextResource(int32_t textStyle, std::string& text) override
    {
        text = DEFAULT_TEXT;
        return true;
    }
};

class MockSecurityComponentButtonLayoutAlgorithm : public BoxLayoutAlgorithm {
public:
    MockSecurityComponentButtonLayoutAlgorithm() = default;

    ~MockSecurityComponentButtonLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override
    {
        SizeF frameSize(DEFAULT_BUTTON_SIZE, DEFAULT_BUTTON_SIZE);
        layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize);
    }
};

void SecurityComponentModelTestNg::InitDefaultTheme(RefPtr<SecurityComponentTheme>& theme)
{
    theme->iconSize_ = Dimension(DEFAULT_ICON_SIZE);
    theme->fontSize_ = Dimension(DEFAULT_FONT_SIZE);
    theme->minIconSize_ = Dimension(DEFAULT_ICON_MIN_SIZE);
    theme->minFontSize_ = Dimension(DEFAULT_FONT_MIN_SIZE);
    theme->backgroundTopPadding_ = Dimension(DEFAULT_PADDING);
    theme->backgroundRightPadding_ = Dimension(DEFAULT_PADDING);
    theme->backgroundBottomPadding_ = Dimension(DEFAULT_PADDING);
    theme->backgroundLeftPadding_ = Dimension(DEFAULT_PADDING);
    theme->textIconPadding_ = Dimension(DEFAULT_PADDING);
    theme->borderRadius_ = Dimension(DEFAULT_BORDER_RADIUS);
    theme->borderWidth_ = Dimension(DEFAULT_BORDER_WIDTH);
    theme->paddingWithoutBg_ = Dimension(DEFAULT_PADDING_WITHOUT_BG);
    theme->iconColor_ = Color::WHITE;
    theme->fontColor_ = Color::WHITE;
    theme->backgroundColor_ = Color::BLUE;
    theme->iconColorNoBg_ = Color::BLUE;
    theme->fontColorNoBg_ = Color::BLACK;
    theme->borderColor_ = Color::RED;
}

void SecurityComponentModelTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto scTheme = AceType::MakeRefPtr<SecurityComponentTheme>();
    InitDefaultTheme(scTheme);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(scTheme));
}

void SecurityComponentModelTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

RefPtr<FrameNode> SecurityComponentModelTestNg::CreateSecurityComponent(int32_t text, int32_t icon,
    SecurityComponentBackgroundType backgroundType)
{
    MockSecurityModelNG sc;
    sc.Create(text, icon, backgroundType);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    return AceType::DynamicCast<FrameNode>(element);
}

void SecurityComponentModelTestNg::CreateSecurityComponentNotFinish(int32_t text, int32_t icon,
    SecurityComponentBackgroundType backgroundType)
{
    MockSecurityModelNG sc;
    sc.Create(text, icon, backgroundType);
}

void SecurityComponentModelTestNg::SetUserDefinedPropty()
{
    MockSecurityModelNG sc;
    sc.SetFontSize(Dimension(15.0)); // 15.0 vp
    sc.SetIconSize(Dimension(15.0)); // 15.0 vp
    sc.SetIconColor(Color::RED);
    sc.SetFontStyle(Ace::FontStyle::ITALIC);
    sc.SetFontWeight(FontWeight::BOLDER);
    std::vector<std::string> fontFamilies = { "testFont" };
    sc.SetFontFamily(fontFamilies);
    sc.SetFontColor(Color::GREEN);
    sc.SetBackgroundColor(Color::GRAY);
    sc.SetBackgroundBorderWidth(Dimension(15.0)); // 15.0 vp
    sc.SetBackgroundBorderColor(Color::GREEN);
    sc.SetBackgroundBorderStyle(BorderStyle::DOTTED);
    sc.SetBackgroundBorderRadius(Dimension(15.0)); // 15.0 vp
    sc.SetBackgroundPadding(Dimension(25.0)); // 25.0 vp
    sc.SetTextIconPadding(Dimension(25.0)); // 25.0 vp
    sc.SetTextIconLayoutDirection(SecurityComponentLayoutDirection::VERTICAL);
    sc.SetlayoutOrder(SecSecurityComponentLayoutOrder::TEXT_FIRST);
}

RefPtr<LayoutWrapper> SecurityComponentModelTestNg::CreateLayoutWrapper(RefPtr<FrameNode>& node)
{
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    if (geometryNode == nullptr) {
        return nullptr;
    }
    return AceType::MakeRefPtr<LayoutWrapper>(node, geometryNode, node->GetLayoutProperty());
}

RefPtr<LayoutWrapper> SecurityComponentModelTestNg::CreateSecurityComponentLayoutWrapper(RefPtr<FrameNode>& node)
{
    auto layoutWrapper = CreateLayoutWrapper(node);
    auto buttonNode = GetSecCompChildNode(node, V2::BUTTON_ETS_TAG);
    CHECK_NULL_RETURN(buttonNode, nullptr);
    auto buttonWrapper = CreateLayoutWrapper(buttonNode);
    auto buttonAlgorithm = AceType::MakeRefPtr<MockSecurityComponentButtonLayoutAlgorithm>();
    CHECK_NULL_RETURN(buttonAlgorithm, nullptr);
    buttonWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(buttonAlgorithm));

    auto iconNode = GetSecCompChildNode(node, V2::IMAGE_ETS_TAG);
    CHECK_NULL_RETURN(iconNode, nullptr);
    auto iconWrapper = CreateLayoutWrapper(iconNode);
    auto iconPattern = iconNode->GetPattern<ImagePattern>();
    CHECK_NULL_RETURN(iconPattern, nullptr);
    auto iconAlgorithm = iconPattern->CreateLayoutAlgorithm();
    CHECK_NULL_RETURN(iconAlgorithm, nullptr);
    iconWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(iconAlgorithm));

    auto textNode = GetSecCompChildNode(node, V2::TEXT_ETS_TAG);
    CHECK_NULL_RETURN(textNode, nullptr);
    auto textWrapper = CreateLayoutWrapper(textNode);
    auto textPattern = textNode->GetPattern<TextPattern>();
    CHECK_NULL_RETURN(textPattern, nullptr);
    auto textAlgorithm = textPattern->CreateLayoutAlgorithm();
    CHECK_NULL_RETURN(textAlgorithm, nullptr);
    textWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(textAlgorithm));

    layoutWrapper->childrenMap_[INDEX_ZERO] = buttonWrapper;
    layoutWrapper->childrenMap_[INDEX_ONE] = iconWrapper;
    layoutWrapper->childrenMap_[INDEX_TWO] = textWrapper;
    layoutWrapper->currentChildCount_ = INDEX_SIZE;
    return layoutWrapper;
}

void SecurityComponentModelTestNg::CheckSecurityComponentDefaultProp(RefPtr<FrameNode>& node)
{
    auto property = node->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetSecurityComponentDescription().value_or(0), 1);
    EXPECT_EQ(property->GetIconStyle().value_or(1), 1);
    EXPECT_EQ(property->GetBackgroundType().value_or(SecurityComponentBackgroundType::NORMAL),
        SecurityComponentBackgroundType::CAPSULE);
    EXPECT_EQ(property->GetTextIconPadding().value_or(Dimension(0.0)).ConvertToVp(), DEFAULT_PADDING);
    EXPECT_EQ(property->GetBackgroundLeftPadding().value_or(Dimension(0.0)).ConvertToVp(), DEFAULT_PADDING);
    EXPECT_EQ(property->GetTextIconLayoutDirection().value_or(SecurityComponentLayoutDirection::VERTICAL),
        SecurityComponentLayoutDirection::HORIZONTAL);
    EXPECT_EQ(property->GetLayoutOrder().value_or(SecSecurityComponentLayoutOrder::TEXT_FIRST),
        SecSecurityComponentLayoutOrder::ICON_FIRST);
}

/**
 * @tc.name: SecurityComponentPropertyTest001
 * @tc.desc: Test default properties of security component.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentPropertyTest001, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(1, 1, SecurityComponentBackgroundType::CAPSULE);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetTag(), V2::SEC_LOCATION_BUTTON_ETS_TAG);

    CheckSecurityComponentDefaultProp(frameNode);

    // text node property
    auto textNode = GetSecCompChildNode(frameNode, V2::TEXT_ETS_TAG);
    ASSERT_NE(textNode, nullptr);
    auto textProp = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textProp, nullptr);
    EXPECT_EQ(textProp->GetContent().value_or(""), DEFAULT_TEXT);
    EXPECT_EQ(textProp->GetMaxLines().value_or(0), 1);
    EXPECT_EQ(textProp->GetFontSize().value_or(Dimension(0.0)).ConvertToVp(), DEFAULT_FONT_SIZE);
    EXPECT_EQ(textProp->GetItalicFontStyle().value_or(Ace::FontStyle::ITALIC), Ace::FontStyle::NORMAL);
    EXPECT_EQ(textProp->GetFontWeight().value_or(FontWeight::MEDIUM), FontWeight::NORMAL);
    std::vector<std::string> emptyVec;
    auto fontFamily = textProp->GetFontFamily().value_or(emptyVec);
    EXPECT_FALSE(fontFamily.empty());
    EXPECT_EQ(textProp->GetTextColor().value_or(Color()), Color::WHITE);

    // icon node property
    auto iconNode = GetSecCompChildNode(frameNode, V2::IMAGE_ETS_TAG);
    ASSERT_NE(iconNode, nullptr);
    auto iconProp = iconNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(iconProp, nullptr);
    ImageSourceInfo iconSrc = iconProp->GetImageSourceInfo().value_or(ImageSourceInfo());
    EXPECT_EQ(iconSrc.GetFillColor().value_or(Color()), Color::WHITE);

    // button node property
    auto buttonNode = GetSecCompChildNode(frameNode, V2::BUTTON_ETS_TAG);
    ASSERT_NE(buttonNode, nullptr);
    auto buttonProp = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonProp, nullptr);
    auto buttonRender = buttonNode->GetRenderContext();
    ASSERT_NE(buttonRender, nullptr);
    auto borderColor = buttonRender->GetBorderColor().value_or(BorderColorProperty());
    EXPECT_EQ(borderColor.leftColor.value_or(Color()), Color::RED);
    auto& widthProp = buttonProp->GetBorderWidthProperty();
    ASSERT_NE(widthProp, nullptr);
    EXPECT_EQ(widthProp->leftDimen.value_or(Dimension(0.0)).ConvertToVp(), DEFAULT_BORDER_WIDTH);
    auto borderStyle = buttonRender->GetBorderStyle().value_or(BorderStyleProperty());
    EXPECT_EQ(borderStyle.styleLeft.value_or(BorderStyle::SOLID), BorderStyle::NONE);

    EXPECT_EQ(buttonProp->GetBorderRadius().value_or(Dimension(0.0)).ConvertToVp(), DEFAULT_BORDER_RADIUS);
    EXPECT_EQ(buttonRender->GetBackgroundColor().value_or(Color()), Color::BLUE);
    EXPECT_EQ(buttonProp->GetType().value_or(ButtonType::NORMAL), ButtonType::CAPSULE);
}

/**
 * @tc.name: SecurityComponentPropertyTest002
 * @tc.desc: Test default properties of security component without background
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentPropertyTest002, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(1, 1,
        SecurityComponentBackgroundType::BACKGROUND_NULL);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetTag(), V2::SEC_LOCATION_BUTTON_ETS_TAG);

    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetBackgroundType().value_or(SecurityComponentBackgroundType::NORMAL),
        SecurityComponentBackgroundType::BACKGROUND_NULL);
    EXPECT_EQ(property->GetBackgroundLeftPadding().value_or(Dimension(0.0)).ConvertToVp(), DEFAULT_PADDING_WITHOUT_BG);
    EXPECT_EQ(property->GetBackgroundRightPadding().value_or(Dimension(0.0)).ConvertToVp(),
        DEFAULT_PADDING_WITHOUT_BG);
    EXPECT_EQ(property->GetBackgroundTopPadding().value_or(Dimension(0.0)).ConvertToVp(), DEFAULT_PADDING_WITHOUT_BG);
    EXPECT_EQ(property->GetBackgroundBottomPadding().value_or(Dimension(0.0)).ConvertToVp(),
        DEFAULT_PADDING_WITHOUT_BG);

    auto textNode = GetSecCompChildNode(frameNode, V2::TEXT_ETS_TAG);
    ASSERT_NE(textNode, nullptr);
    auto textProp = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textProp, nullptr);
    EXPECT_EQ(textProp->GetTextColor().value_or(Color()), Color::BLACK);

    auto iconNode = GetSecCompChildNode(frameNode, V2::IMAGE_ETS_TAG);
    ASSERT_NE(iconNode, nullptr);
    auto iconProp = iconNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(iconProp, nullptr);
    ImageSourceInfo iconSrc = iconProp->GetImageSourceInfo().value_or(ImageSourceInfo());
    EXPECT_EQ(iconSrc.GetFillColor().value_or(Color()), Color::BLUE);

    auto buttonNode = GetSecCompChildNode(frameNode, V2::BUTTON_ETS_TAG);
    ASSERT_NE(buttonNode, nullptr);
    auto buttonProp = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonProp, nullptr);
    auto buttonRender = buttonNode->GetRenderContext();
    ASSERT_NE(buttonRender, nullptr);
    EXPECT_EQ(buttonRender->GetBackgroundColor().value_or(Color()), Color::TRANSPARENT);
    EXPECT_EQ(buttonProp->GetType().value_or(ButtonType::CAPSULE), ButtonType::NORMAL);
}

/**
 * @tc.name: SecurityComponentPropertyTest003
 * @tc.desc: Test default properties of security component without icon
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentPropertyTest003, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(1, -1,
        SecurityComponentBackgroundType::BACKGROUND_NULL);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetTag(), V2::SEC_LOCATION_BUTTON_ETS_TAG);

    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetIconStyle().value_or(1), -1);
    EXPECT_EQ(property->GetTextIconPadding().value_or(Dimension(0.0)).ConvertToVp(), 0.0);

    auto iconNode = GetSecCompChildNode(frameNode, V2::IMAGE_ETS_TAG);
    ASSERT_EQ(iconNode, nullptr);
}

/**
 * @tc.name: SecurityComponentPropertyTest004
 * @tc.desc: Test set security component property
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentPropertyTest004, TestSize.Level1)
{
    CreateSecurityComponentNotFinish(1, 1, SecurityComponentBackgroundType::CAPSULE);
    SetUserDefinedPropty();

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetTextIconPadding().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetBackgroundLeftPadding().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetBackgroundRightPadding().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetBackgroundTopPadding().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetBackgroundBottomPadding().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetTextIconLayoutDirection().value_or(SecurityComponentLayoutDirection::HORIZONTAL),
        SecurityComponentLayoutDirection::VERTICAL);
    EXPECT_EQ(property->GetLayoutOrder().value_or(SecSecurityComponentLayoutOrder::ICON_FIRST),
        SecSecurityComponentLayoutOrder::TEXT_FIRST);

    auto iconNode = GetCurSecCompChildNode(V2::IMAGE_ETS_TAG);
    ASSERT_NE(iconNode, nullptr);
    auto iconProp = iconNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(iconProp, nullptr);
    ImageSourceInfo iconSrc = iconProp->GetImageSourceInfo().value_or(ImageSourceInfo());
    EXPECT_EQ(iconSrc.GetFillColor().value_or(Color()), Color::RED);

    auto textNode = GetCurSecCompChildNode(V2::TEXT_ETS_TAG);
    ASSERT_NE(textNode, nullptr);
    auto textProp = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textProp, nullptr);
    EXPECT_EQ(textProp->GetFontSize().value_or(Dimension(0.0)).ConvertToVp(), 15.0); // 15.0 vp
    EXPECT_EQ(textProp->GetItalicFontStyle().value_or(Ace::FontStyle::NORMAL), Ace::FontStyle::ITALIC);
    EXPECT_EQ(textProp->GetFontWeight().value_or(FontWeight::MEDIUM), FontWeight::BOLDER);
    std::vector<std::string> emptyVec;
    auto fontFamily = textProp->GetFontFamily().value_or(emptyVec);
    ASSERT_FALSE(fontFamily.empty());
    EXPECT_EQ(fontFamily[0], "testFont");
    EXPECT_EQ(textProp->GetTextColor().value_or(Color()), Color::GREEN);

    auto buttonNode = GetCurSecCompChildNode(V2::BUTTON_ETS_TAG);
    ASSERT_NE(buttonNode, nullptr);
    auto buttonProp = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonProp, nullptr);
    auto buttonRender = buttonNode->GetRenderContext();
    ASSERT_NE(buttonRender, nullptr);
    auto borderColor = buttonRender->GetBorderColor().value_or(BorderColorProperty());
    EXPECT_EQ(borderColor.leftColor.value_or(Color()), Color::GREEN);
    auto& widthProp = buttonProp->GetBorderWidthProperty();
    ASSERT_NE(widthProp, nullptr);
    EXPECT_EQ(widthProp->leftDimen.value_or(Dimension(0.0)).ConvertToVp(), 15.0); // 15.0 vp
    auto borderStyle = buttonRender->GetBorderStyle().value_or(BorderStyleProperty());
    EXPECT_EQ(borderStyle.styleLeft.value_or(BorderStyle::SOLID), BorderStyle::DOTTED);
    EXPECT_EQ(buttonProp->GetBorderRadius().value_or(Dimension(0.0)).ConvertToVp(), 15.0); // 15.0 vp
    EXPECT_EQ(buttonRender->GetBackgroundColor().value_or(Color()), Color::GRAY);
}

/**
 * @tc.name: SecurityComponentPropertyTest005
 * @tc.desc: Test set security component property
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentPropertyTest005, TestSize.Level1)
{
    CreateSecurityComponentNotFinish(1, 1, SecurityComponentBackgroundType::CAPSULE);
    SetUserDefinedPropty();

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetTextIconPadding().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetBackgroundLeftPadding().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetBackgroundRightPadding().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetBackgroundTopPadding().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetBackgroundBottomPadding().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetTextIconLayoutDirection().value_or(SecurityComponentLayoutDirection::HORIZONTAL),
        SecurityComponentLayoutDirection::VERTICAL);
    EXPECT_EQ(property->GetLayoutOrder().value_or(SecSecurityComponentLayoutOrder::ICON_FIRST),
        SecSecurityComponentLayoutOrder::TEXT_FIRST);

    auto iconNode = GetCurSecCompChildNode(V2::IMAGE_ETS_TAG);
    ASSERT_NE(iconNode, nullptr);
    auto iconProp = iconNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(iconProp, nullptr);
    ImageSourceInfo iconSrc = iconProp->GetImageSourceInfo().value_or(ImageSourceInfo());
    EXPECT_EQ(iconSrc.GetFillColor().value_or(Color()), Color::RED);

    auto textNode = GetCurSecCompChildNode(V2::TEXT_ETS_TAG);
    ASSERT_NE(textNode, nullptr);
    auto textProp = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textProp, nullptr);
    EXPECT_EQ(textProp->GetFontSize().value_or(Dimension(0.0)).ConvertToVp(), 15.0); // 15.0 vp
    EXPECT_EQ(textProp->GetItalicFontStyle().value_or(Ace::FontStyle::NORMAL), Ace::FontStyle::ITALIC);
    EXPECT_EQ(textProp->GetFontWeight().value_or(FontWeight::MEDIUM), FontWeight::BOLDER);
    std::vector<std::string> emptyVec;
    auto fontFamily = textProp->GetFontFamily().value_or(emptyVec);
    ASSERT_FALSE(fontFamily.empty());
    EXPECT_EQ(fontFamily[0], "testFont");
    EXPECT_EQ(textProp->GetTextColor().value_or(Color()), Color::GREEN);

    auto buttonNode = GetCurSecCompChildNode(V2::BUTTON_ETS_TAG);
    ASSERT_NE(buttonNode, nullptr);
    auto buttonProp = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonProp, nullptr);
    auto buttonRender = buttonNode->GetRenderContext();
    ASSERT_NE(buttonRender, nullptr);
    auto borderColor = buttonRender->GetBorderColor().value_or(BorderColorProperty());
    EXPECT_EQ(borderColor.leftColor.value_or(Color()), Color::GREEN);
    auto& widthProp = buttonProp->GetBorderWidthProperty();
    ASSERT_NE(widthProp, nullptr);
    EXPECT_EQ(widthProp->leftDimen.value_or(Dimension(0.0)).ConvertToVp(), 15.0); // 15.0 vp
    auto borderStyle = buttonRender->GetBorderStyle().value_or(BorderStyleProperty());
    EXPECT_EQ(borderStyle.styleLeft.value_or(BorderStyle::SOLID), BorderStyle::DOTTED);

    EXPECT_EQ(buttonProp->GetBorderRadius().value_or(Dimension(0.0)).ConvertToVp(), 15.0); // 15.0 vp
    EXPECT_EQ(buttonRender->GetBackgroundColor().value_or(Color()), Color::GRAY);
}

/**
 * @tc.name: SecurityComponentPropertyTest006
 * @tc.desc: Test set security component property without background
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentPropertyTest006, TestSize.Level1)
{
    CreateSecurityComponentNotFinish(1, 1, SecurityComponentBackgroundType::BACKGROUND_NULL);
    MockSecurityModelNG sc;
    sc.SetBackgroundColor(Color::GRAY);
    sc.SetBackgroundBorderWidth(Dimension(15.0)); // 15.0 vp
    sc.SetBackgroundBorderColor(Color::GREEN);
    sc.SetBackgroundBorderStyle(BorderStyle::DOTTED);
    sc.SetBackgroundBorderRadius(Dimension(15.0)); // 15.0 vp
    sc.SetBackgroundPadding(Dimension(25.0)); // 25.0 vp

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_NE(property->GetBackgroundLeftPadding().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_NE(property->GetBackgroundRightPadding().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_NE(property->GetBackgroundTopPadding().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_NE(property->GetBackgroundBottomPadding().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp

    auto buttonNode = GetCurSecCompChildNode(V2::BUTTON_ETS_TAG);
    ASSERT_NE(buttonNode, nullptr);
    auto buttonProp = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonProp, nullptr);
    auto buttonRender = buttonNode->GetRenderContext();
    ASSERT_NE(buttonRender, nullptr);
    auto borderColor = buttonRender->GetBorderColor().value_or(BorderColorProperty());
    EXPECT_NE(borderColor.leftColor.value_or(Color()), Color::GREEN);
    auto& widthProp = buttonProp->GetBorderWidthProperty();
    ASSERT_EQ(widthProp, nullptr);
    auto borderStyle = buttonRender->GetBorderStyle().value_or(BorderStyleProperty());
    EXPECT_NE(borderStyle.styleLeft.value_or(BorderStyle::SOLID), BorderStyle::DOTTED);
}

/**
 * @tc.name: SecurityComponentPropertyTest007
 * @tc.desc: Test set security component property without icon
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentPropertyTest007, TestSize.Level1)
{
    CreateSecurityComponentNotFinish(1, -1, SecurityComponentBackgroundType::CAPSULE);
    MockSecurityModelNG sc;
    sc.SetTextIconPadding(Dimension(15.0)); // 15.0vp

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetTextIconPadding().value_or(Dimension(0.0)).ConvertToVp(), 0.0);
}

/**
 * @tc.name: SecurityComponentPatternTest001
 * @tc.desc: Test default security component modifyDone
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentPatternTest001, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(1, 1,
        SecurityComponentBackgroundType::CAPSULE);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetTag(), V2::SEC_LOCATION_BUTTON_ETS_TAG);

    auto pattern = frameNode->GetPattern<SecurityComponentPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnModifyDone();
    EXPECT_TRUE(pattern->isAppearCallback_);
    EXPECT_NE(pattern->clickListener_, nullptr);

    auto secCompGesture = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(secCompGesture, nullptr);
    EXPECT_EQ(secCompGesture->GetHitTestMode(), HitTestMode::HTMDEFAULT);

    // modifydone again
    pattern->OnModifyDone();
    EXPECT_TRUE(pattern->isAppearCallback_);
    EXPECT_NE(pattern->clickListener_, nullptr);
}

/**
 * @tc.name: SecurityComponentPatternTest002
 * @tc.desc: Test event callback
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentPatternTest002, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(1, 1,
        SecurityComponentBackgroundType::CAPSULE);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetTag(), V2::SEC_LOCATION_BUTTON_ETS_TAG);

    auto pattern = frameNode->GetPattern<SecurityComponentPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnModifyDone();

    auto secCompGesture = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(secCompGesture, nullptr);
    auto clickListener = secCompGesture->clickEventActuator_->clickEvents_.back();
    ASSERT_NE(clickListener, nullptr);
    ASSERT_NE(clickListener->callback_, nullptr);
    GestureEvent info;
    clickListener->callback_(info);

    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    ASSERT_NE(eventHub->onAppear_, nullptr);
    ASSERT_NE(eventHub->onDisappear_, nullptr);
    eventHub->onAppear_();
    eventHub->onDisappear_();
    ASSERT_EQ(pattern->scId_, -1);
}

/**
 * @tc.name: SecurityComponentLayoutAlgoTest001
 * @tc.desc: Test default layout algo
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLayoutAlgoTest001, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(1, 1,
        SecurityComponentBackgroundType::CAPSULE);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetTag(), V2::SEC_LOCATION_BUTTON_ETS_TAG);
    auto pattern = frameNode->GetPattern<SecurityComponentPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnModifyDone();

    auto layoutAlgo = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgo, nullptr);

    auto layoutWrapper = CreateSecurityComponentLayoutWrapper(frameNode);
    ASSERT_NE(layoutWrapper, nullptr);
    layoutAlgo->Measure(layoutWrapper.rawPtr_);
    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameSize().Height(), DEFAULT_BUTTON_SIZE);
    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameSize().Width(), DEFAULT_BUTTON_SIZE);

    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    property->UpdateBackgroundType(SecurityComponentBackgroundType::CIRCLE);
    property->UpdateTextIconLayoutDirection(SecurityComponentLayoutDirection::VERTICAL);
    property->UpdateLayoutOrder(SecSecurityComponentLayoutOrder::ICON_FIRST);
    pattern->OnModifyDone();

    layoutAlgo->Measure(layoutWrapper.rawPtr_);
    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameSize().Height(), DEFAULT_BUTTON_SIZE);
    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameSize().Width(), DEFAULT_BUTTON_SIZE);
}

/**
 * @tc.name: SecurityComponentLayoutAlgoTest001
 * @tc.desc: Test security component accessibility property
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentAccessibilityPropertyTest001, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(1, 1,
        SecurityComponentBackgroundType::CAPSULE);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetTag(), V2::SEC_LOCATION_BUTTON_ETS_TAG);
    auto pattern = frameNode->GetPattern<SecurityComponentPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnModifyDone();

    auto accessibility = pattern->CreateAccessibilityProperty();
    ASSERT_NE(accessibility, nullptr);
    accessibility->SetHost(frameNode);
    ASSERT_EQ(accessibility->GetText(), DEFAULT_TEXT);
}
} // namespace OHOS::Ace::NG
