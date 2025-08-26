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
#include "ui/base/utils/utils.h"

#define protected public
#define private public
#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/system_properties.h"
#include "core/common/ace_engine.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/security_component/location_button/location_button_common.h"
#include "core/components_ng/pattern/security_component/location_button/location_button_model_ng.h"
#include "core/components_ng/pattern/security_component/paste_button/paste_button_common.h"
#include "core/components_ng/pattern/security_component/paste_button/paste_button_model_ng.h"
#include "core/components_ng/pattern/security_component/save_button/save_button_common.h"
#include "core/components_ng/pattern/security_component/save_button/save_button_model_ng.h"
#include "core/components_ng/pattern/security_component/security_component_handler.h"
#include "core/components_ng/pattern/security_component/security_component_pattern.h"
#include "core/components_ng/pattern/security_component/security_component_theme.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "core/pipeline_ng/ui_task_scheduler.h"
#include "test/mock/base/mock_task_executor.h"
#include "security_component_test_ng.h"
#undef protected
#undef private

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
const InspectorFilter filter;
constexpr float DEFAULT_ICON_SIZE = 16.0f;
constexpr float DEFAULT_SYMBOL_FONT_SIZE = 24.0f;
constexpr uint32_t DEFAULT_SYMBOL_ICON_COLOR = 0xFF000000;
constexpr float DEFAULT_FONT_SIZE = 16.0f;
constexpr float DEFAULT_ICON_MIN_SIZE = 12.0f;
constexpr float DEFAULT_FONT_MIN_SIZE = 12.0f;
constexpr float DEFAULT_PADDING = 10.0f;
constexpr float DEFAULT_BORDER_RADIUS = 1.0f;
constexpr float DEFAULT_BORDER_WIDTH = 1.0f;
constexpr float DEFAULT_PADDING_WITHOUT_BG = 4.0f;
constexpr float MIN_SIZE = 1.0f;
constexpr float ENLARGE_SIZE = 50.0f;
constexpr int INDEX_ZERO = 0;
constexpr int INDEX_ONE = 1;
constexpr int INDEX_TWO = 2;
constexpr int INDEX_SIZE = 3;
constexpr int ICON_RESOURCE_TABLE = 2;
const std::string CUSTOMIZE_TEXT = "customize";
}

namespace {
class TestNode : public UINode {
    DECLARE_ACE_TYPE(TestNode, UINode);

    public:
        static RefPtr<TestNode> CreateTestNode(int32_t nodeId)
        {
            auto node = MakeRefPtr<TestNode>(nodeId);
            return node;
        }

        bool IsAtomicNode() const override
        {
            return true;
        }

        explicit TestNode(int32_t nodeId) : UINode("TestNode", nodeId) {}
        ~TestNode() override = default;
    };
}

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
    theme->textIconSpace_ = Dimension(DEFAULT_PADDING);
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
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->pipelineContext_ = PipelineBase::GetCurrentContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto scTheme = AceType::MakeRefPtr<SecurityComponentTheme>();
    InitDefaultTheme(scTheme);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(scTheme));
}

void SecurityComponentModelTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

RefPtr<FrameNode> SecurityComponentModelTestNg::CreateSecurityComponent(int32_t text, int32_t icon,
    int32_t backgroundType, std::string type)
{
    if (type == V2::LOCATION_BUTTON_ETS_TAG) {
        LocationButtonModelNG locationSc;
        locationSc.Create(text, icon, backgroundType, false);
    } else if (type == V2::PASTE_BUTTON_ETS_TAG) {
        PasteButtonModelNG pasteSc;
        pasteSc.Create(text, icon, backgroundType, false);
    } else if (type == V2::SAVE_BUTTON_ETS_TAG) {
        SaveButtonModelNG saveSc;
        saveSc.Create(text, icon, backgroundType, false);
    }
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    return AceType::DynamicCast<FrameNode>(element);
}

void SecurityComponentModelTestNg::CreateSecurityComponentNotFinish(int32_t text, int32_t icon,
    int32_t backgroundType, std::string type)
{
    if (type == V2::LOCATION_BUTTON_ETS_TAG) {
        LocationButtonModelNG locationSc;
        locationSc.Create(text, icon, backgroundType, false);
    } else if (type == V2::PASTE_BUTTON_ETS_TAG) {
        PasteButtonModelNG pasteSc;
        pasteSc.Create(text, icon, backgroundType, false);
    } else if (type == V2::SAVE_BUTTON_ETS_TAG) {
        SaveButtonModelNG saveSc;
        saveSc.Create(text, icon, backgroundType, false);
    }
}

void SecurityComponentModelTestNg::SetLocationUserDefinedPropty()
{
    LocationButtonModelNG sc;
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
    sc.SetTextIconSpace(Dimension(25.0)); // 25.0 vp
    sc.SetTextIconLayoutDirection(SecurityComponentLayoutDirection::VERTICAL);
}

void SecurityComponentModelTestNg::SetPasteUserDefinedPropty()
{
    PasteButtonModelNG sc;
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
    sc.SetTextIconSpace(Dimension(25.0)); // 25.0 vp
    sc.SetTextIconLayoutDirection(SecurityComponentLayoutDirection::VERTICAL);
}

void SecurityComponentModelTestNg::SetSaveUserDefinedPropty()
{
    SaveButtonModelNG sc;
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
    sc.SetTextIconSpace(Dimension(25.0)); // 25.0 vp
    sc.SetTextIconLayoutDirection(SecurityComponentLayoutDirection::VERTICAL);
}

RefPtr<LayoutWrapperNode> SecurityComponentModelTestNg::CreateLayoutWrapper(RefPtr<FrameNode>& node)
{
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    if (geometryNode == nullptr) {
        return nullptr;
    }
    return AceType::MakeRefPtr<LayoutWrapperNode>(node, geometryNode, node->GetLayoutProperty());
}

RefPtr<LayoutWrapperNode> SecurityComponentModelTestNg::CreateSecurityComponentLayoutWrapper(RefPtr<FrameNode>& node)
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
    layoutWrapper->cachedList_.emplace_back(&*buttonWrapper);
    layoutWrapper->cachedList_.emplace_back(&*iconWrapper);
    layoutWrapper->cachedList_.emplace_back(&*textWrapper);
    return layoutWrapper;
}

void SecurityComponentModelTestNg::CheckSecurityComponentDefaultProp(RefPtr<FrameNode>& node)
{
    auto property = node->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetSecurityComponentDescription().value_or(1), 0);
    EXPECT_EQ(property->GetIconStyle().value_or(1), 0);
    EXPECT_EQ(property->GetBackgroundType().value_or(static_cast<int32_t>(ButtonType::NORMAL)),
        static_cast<int32_t>(ButtonType::CAPSULE));
    EXPECT_EQ(property->GetTextIconLayoutDirection().value_or(SecurityComponentLayoutDirection::VERTICAL),
        SecurityComponentLayoutDirection::HORIZONTAL);
}

/**
 * @tc.name: SecurityComponentPasteButtonSymbolTest001
 * @tc.desc: Test symbol of paste component.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentPasteButtonSymbolTest001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = PasteButtonModelNG::GetInstance()->CreateNode(
        0, -1, static_cast<int32_t>(ButtonType::CAPSULE), true, 1);
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    auto textIconSpace = property->GetTextIconSpace();
    ASSERT_EQ(textIconSpace.has_value(), false);

    frameNode = PasteButtonModelNG::GetInstance()->CreateNode(
        0, 0, static_cast<int32_t>(ButtonType::CAPSULE), true, -1);
    ASSERT_NE(frameNode, nullptr);
    property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    textIconSpace = property->GetTextIconSpace();
    ASSERT_EQ(textIconSpace.has_value(), false);

    frameNode = PasteButtonModelNG::GetInstance()->CreateNode(
        0, 0, static_cast<int32_t>(ButtonType::CAPSULE), true, 1);
    ASSERT_EQ(frameNode, nullptr);

    frameNode = PasteButtonModelNG::GetInstance()->CreateNode(
        0, -1, static_cast<int32_t>(ButtonType::CAPSULE), true, -1);
    ASSERT_NE(frameNode, nullptr);
    property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    textIconSpace = property->GetTextIconSpace();
    ASSERT_EQ(textIconSpace.has_value(), false);

    frameNode = PasteButtonModelNG::GetInstance()->CreateNode(
        -1, 0, static_cast<int32_t>(ButtonType::CAPSULE), true, -1);
    ASSERT_NE(frameNode, nullptr);
    property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    textIconSpace = property->GetTextIconSpace();
    ASSERT_EQ(textIconSpace.has_value(), false);

    frameNode = PasteButtonModelNG::GetInstance()->CreateNode(
        -1, -1, static_cast<int32_t>(ButtonType::CAPSULE), true, 1);
    ASSERT_NE(frameNode, nullptr);
    property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    textIconSpace = property->GetTextIconSpace();
    ASSERT_EQ(textIconSpace.has_value(), false);
}

/**
 * @tc.name: SecurityComponentPasteButtonSymbolTest002
 * @tc.desc: Test symbol of paste component.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentPasteButtonSymbolTest002, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = PasteButtonModelNG::GetInstance()->CreateNode(
        0, -1, static_cast<int32_t>(ButtonType::CAPSULE), true, 1);
    ASSERT_NE(frameNode, nullptr);

    OHOS::Security::SecurityComponent::SecCompBase buttonInfo;
    std::string message;
    SecurityComponentHandler::InitChildInfo(buttonInfo, frameNode);
    ASSERT_EQ(NearEqual(buttonInfo.iconSize_, DEFAULT_SYMBOL_FONT_SIZE), true);
    ASSERT_EQ(buttonInfo.iconColor_.value, DEFAULT_SYMBOL_ICON_COLOR);
}

/**
 * @tc.name: SecurityComponentLocationPropertyTest001
 * @tc.desc: Test default properties of security component.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLocationPropertyTest001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0, static_cast<int32_t>(ButtonType::CAPSULE),
        V2::LOCATION_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetTag(), V2::LOCATION_BUTTON_ETS_TAG);

    CheckSecurityComponentDefaultProp(frameNode);

    // text node property
    auto textNode = GetSecCompChildNode(frameNode, V2::TEXT_ETS_TAG);
    ASSERT_NE(textNode, nullptr);
    auto textProp = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textProp, nullptr);
    EXPECT_EQ(textProp->GetMaxLines().value_or(0), static_cast<uint32_t>(1000000));
    EXPECT_EQ(textProp->GetFontSize().value_or(Dimension(0.0)).ConvertToVp(), DEFAULT_FONT_SIZE);
    EXPECT_EQ(textProp->GetItalicFontStyle().value_or(Ace::FontStyle::ITALIC), Ace::FontStyle::NORMAL);
    EXPECT_EQ(textProp->GetFontWeight().value_or(FontWeight::NORMAL), FontWeight::MEDIUM);
    std::vector<std::string> emptyVec;
    auto fontFamily = textProp->GetFontFamily().value_or(emptyVec);
    EXPECT_TRUE(fontFamily.empty());
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

    EXPECT_EQ(buttonRender->GetBackgroundColor().value_or(Color()), Color::BLUE);
    EXPECT_EQ(buttonProp->GetType().value_or(ButtonType::NORMAL), ButtonType::CAPSULE);
}

/**
 * @tc.name: SecurityComponentLocationPropertyTest002
 * @tc.desc: Test default properties of security component without background
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLocationPropertyTest002, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        BUTTON_TYPE_NULL, V2::LOCATION_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetTag(), V2::LOCATION_BUTTON_ETS_TAG);

    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetBackgroundType().value_or(static_cast<int32_t>(ButtonType::NORMAL)),
        BUTTON_TYPE_NULL);
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
 * @tc.name: SecurityComponentLocationPropertyTest003
 * @tc.desc: Test default properties of security component without icon
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLocationPropertyTest003, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(1, -1,
        BUTTON_TYPE_NULL, V2::LOCATION_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetTag(), V2::LOCATION_BUTTON_ETS_TAG);

    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetIconStyle().value_or(1), -1);
    EXPECT_EQ(property->GetTextIconSpace().value_or(Dimension(0.0)).ConvertToVp(), 0.0);

    auto iconNode = GetSecCompChildNode(frameNode, V2::IMAGE_ETS_TAG);
    ASSERT_EQ(iconNode, nullptr);
}

/**
 * @tc.name: SecurityComponentLocationPropertyTest004
 * @tc.desc: Test set security component property
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLocationPropertyTest004, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, static_cast<int32_t>(ButtonType::CAPSULE), V2::LOCATION_BUTTON_ETS_TAG);
    SetLocationUserDefinedPropty();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetTextIconSpace().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetBackgroundLeftPadding().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetBackgroundRightPadding().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetBackgroundTopPadding().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetBackgroundBottomPadding().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetTextIconLayoutDirection().value_or(SecurityComponentLayoutDirection::HORIZONTAL),
        SecurityComponentLayoutDirection::VERTICAL);

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
    EXPECT_EQ(buttonRender->GetBackgroundColor().value_or(Color()), Color::GRAY);
}

/**
 * @tc.name: SecurityComponentLocationPropertyTest005
 * @tc.desc: Test set security component property
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLocationPropertyTest005, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, static_cast<int32_t>(ButtonType::CAPSULE), V2::LOCATION_BUTTON_ETS_TAG);
    SetLocationUserDefinedPropty();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetTextIconSpace().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetBackgroundLeftPadding().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetBackgroundRightPadding().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetBackgroundTopPadding().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetBackgroundBottomPadding().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetTextIconLayoutDirection().value_or(SecurityComponentLayoutDirection::HORIZONTAL),
        SecurityComponentLayoutDirection::VERTICAL);

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
    EXPECT_EQ(buttonRender->GetBackgroundColor().value_or(Color()), Color::GRAY);
}

/**
 * @tc.name: SecurityComponentLocationPropertyTest006
 * @tc.desc: Test set security component property without background
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLocationPropertyTest006, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, BUTTON_TYPE_NULL, V2::LOCATION_BUTTON_ETS_TAG);
    LocationButtonModelNG locationSc;
    locationSc.SetBackgroundColor(Color::GRAY);
    locationSc.SetBackgroundBorderWidth(Dimension(15.0)); // 15.0 vp
    locationSc.SetBackgroundBorderColor(Color::GREEN);
    locationSc.SetBackgroundBorderStyle(BorderStyle::DOTTED);
    locationSc.SetBackgroundBorderRadius(Dimension(15.0)); // 15.0 vp
    locationSc.SetBackgroundPadding(Dimension(25.0)); // 25.0 vp

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
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
 * @tc.name: SecurityComponentLocationPropertyTest007
 * @tc.desc: Test set security component property without icon
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLocationPropertyTest007, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(1, -1, static_cast<int32_t>(ButtonType::CAPSULE),
        V2::LOCATION_BUTTON_ETS_TAG);
    LocationButtonModelNG locationSc;
    locationSc.SetTextIconSpace(Dimension(15.0)); // 15.0vp

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetTextIconSpace().value_or(Dimension(0.0)).ConvertToVp(), 0.0);
}

/**
 * @tc.name: SecurityComponentLocationPatternTest001
 * @tc.desc: Test default security component modifyDone
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLocationPatternTest001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::LOCATION_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetTag(), V2::LOCATION_BUTTON_ETS_TAG);

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
 * @tc.name: SecurityComponentLocationPatternTest002
 * @tc.desc: Test event callback
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLocationPatternTest002, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::LOCATION_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetTag(), V2::LOCATION_BUTTON_ETS_TAG);

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
 * @tc.name: SecurityComponentLocationLayoutAlgoTest001
 * @tc.desc: Test default layout algo
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLocationLayoutAlgoTest001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::LOCATION_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetTag(), V2::LOCATION_BUTTON_ETS_TAG);
    auto pattern = frameNode->GetPattern<SecurityComponentPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnModifyDone();

    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    property->UpdateMarginSelfIdealSize(SizeF(MIN_SIZE, MIN_SIZE));
    property->UpdateContentConstraint();

    auto layoutAlgo = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgo, nullptr);

    auto layoutWrapper = CreateSecurityComponentLayoutWrapper(frameNode);
    ASSERT_NE(layoutWrapper, nullptr);
    layoutAlgo->Measure(layoutWrapper.rawPtr_);
    layoutAlgo->Layout(layoutWrapper.rawPtr_);
    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameSize().Height(), DEFAULT_ICON_MIN_SIZE);
    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameSize().Width(), DEFAULT_ICON_MIN_SIZE);

    property->UpdateBackgroundType(static_cast<int32_t>(ButtonType::CAPSULE));
    property->UpdateTextIconLayoutDirection(SecurityComponentLayoutDirection::VERTICAL);
    property->UpdateAlignment(Alignment::CENTER_LEFT);
    pattern->OnModifyDone();

    layoutAlgo->Measure(layoutWrapper.rawPtr_);
    layoutAlgo->Layout(layoutWrapper.rawPtr_);
    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameSize().Height(), DEFAULT_ICON_MIN_SIZE);
    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameSize().Width(), DEFAULT_ICON_MIN_SIZE);

    property->UpdateBackgroundType(static_cast<int32_t>(ButtonType::CIRCLE));
    property->UpdateTextIconLayoutDirection(SecurityComponentLayoutDirection::VERTICAL);
    pattern->OnModifyDone();

    layoutAlgo->Measure(layoutWrapper.rawPtr_);
    layoutAlgo->Layout(layoutWrapper.rawPtr_);
    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameSize().Height(), DEFAULT_ICON_MIN_SIZE);
    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameSize().Width(), DEFAULT_ICON_MIN_SIZE);

    property->UpdateBackgroundType(static_cast<int32_t>(ButtonType::CAPSULE));
    property->UpdateTextIconLayoutDirection(SecurityComponentLayoutDirection::VERTICAL);
    pattern->OnModifyDone();

    property->UpdateMarginSelfIdealSize(SizeF(ENLARGE_SIZE, ENLARGE_SIZE));
    property->UpdateContentConstraint();
    layoutAlgo->Measure(layoutWrapper.rawPtr_);
    layoutAlgo->Layout(layoutWrapper.rawPtr_);
    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameSize().Height(), ENLARGE_SIZE);
    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameSize().Width(), ENLARGE_SIZE);
}

/**
 * @tc.name: SecurityComponentLocationAccessibilityPropertyTest001
 * @tc.desc: Test security component accessibility property
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLocationAccessibilityPropertyTest001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::LOCATION_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetTag(), V2::LOCATION_BUTTON_ETS_TAG);
    auto pattern = frameNode->GetPattern<SecurityComponentPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnModifyDone();

    auto accessibility = pattern->CreateAccessibilityProperty();
    ASSERT_NE(accessibility, nullptr);
    accessibility->SetHost(frameNode);
}

/**
 * @tc.name: SecurityComponentSavePropertyTest001
 * @tc.desc: Test default properties of security component.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentSavePropertyTest001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0, static_cast<int32_t>(ButtonType::CAPSULE),
        V2::SAVE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetTag(), V2::SAVE_BUTTON_ETS_TAG);

    CheckSecurityComponentDefaultProp(frameNode);

    // text node property
    auto textNode = GetSecCompChildNode(frameNode, V2::TEXT_ETS_TAG);
    ASSERT_NE(textNode, nullptr);
    auto textProp = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textProp, nullptr);
    EXPECT_EQ(textProp->GetMaxLines().value_or(0), 1000000);
    EXPECT_EQ(textProp->GetFontSize().value_or(Dimension(0.0)).ConvertToVp(), DEFAULT_FONT_SIZE);
    EXPECT_EQ(textProp->GetItalicFontStyle().value_or(Ace::FontStyle::ITALIC), Ace::FontStyle::NORMAL);
    EXPECT_EQ(textProp->GetFontWeight().value_or(FontWeight::NORMAL), FontWeight::MEDIUM);
    std::vector<std::string> emptyVec;
    auto fontFamily = textProp->GetFontFamily().value_or(emptyVec);
    EXPECT_TRUE(fontFamily.empty());
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

    EXPECT_EQ(buttonRender->GetBackgroundColor().value_or(Color()), Color::BLUE);
    EXPECT_EQ(buttonProp->GetType().value_or(ButtonType::NORMAL), ButtonType::CAPSULE);
}

/**
 * @tc.name: SecurityComponentSavePropertyTest002
 * @tc.desc: Test default properties of security component without background
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentSavePropertyTest002, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        BUTTON_TYPE_NULL, V2::SAVE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetTag(), V2::SAVE_BUTTON_ETS_TAG);
    frameNode->MarkModifyDone();

    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetBackgroundType().value_or(static_cast<int32_t>(ButtonType::NORMAL)),
        BUTTON_TYPE_NULL);
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
 * @tc.name: SecurityComponentSavePropertyTest003
 * @tc.desc: Test default properties of security component without icon
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentSavePropertyTest003, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(1, -1,
        BUTTON_TYPE_NULL, V2::SAVE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetTag(), V2::SAVE_BUTTON_ETS_TAG);

    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetIconStyle().value_or(1), -1);
    EXPECT_EQ(property->GetTextIconSpace().value_or(Dimension(0.0)).ConvertToVp(), 0.0);

    auto iconNode = GetSecCompChildNode(frameNode, V2::IMAGE_ETS_TAG);
    ASSERT_EQ(iconNode, nullptr);
}

/**
 * @tc.name: SecurityComponentSavePropertyTest004
 * @tc.desc: Test set security component property
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentSavePropertyTest004, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, static_cast<int32_t>(ButtonType::CAPSULE), V2::SAVE_BUTTON_ETS_TAG);
    SetSaveUserDefinedPropty();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetTextIconSpace().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetBackgroundLeftPadding().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetBackgroundRightPadding().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetBackgroundTopPadding().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetBackgroundBottomPadding().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetTextIconLayoutDirection().value_or(SecurityComponentLayoutDirection::HORIZONTAL),
        SecurityComponentLayoutDirection::VERTICAL);
    frameNode->MarkModifyDone();

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
    EXPECT_EQ(buttonRender->GetBackgroundColor().value_or(Color()), Color::GRAY);
}

/**
 * @tc.name: SecurityComponentSavePropertyTest005
 * @tc.desc: Test set security component property
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentSavePropertyTest005, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, static_cast<int32_t>(ButtonType::CAPSULE), V2::SAVE_BUTTON_ETS_TAG);
    SetSaveUserDefinedPropty();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetTextIconSpace().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetBackgroundLeftPadding().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetBackgroundRightPadding().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetBackgroundTopPadding().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetBackgroundBottomPadding().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetTextIconLayoutDirection().value_or(SecurityComponentLayoutDirection::HORIZONTAL),
        SecurityComponentLayoutDirection::VERTICAL);

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
    EXPECT_EQ(buttonRender->GetBackgroundColor().value_or(Color()), Color::GRAY);
}

/**
 * @tc.name: SecurityComponentSavePropertyTest006
 * @tc.desc: Test set security component property without background
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentSavePropertyTest006, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, BUTTON_TYPE_NULL, V2::SAVE_BUTTON_ETS_TAG);
    SaveButtonModelNG saveSc;
    saveSc.SetBackgroundColor(Color::GRAY);
    saveSc.SetBackgroundBorderWidth(Dimension(15.0)); // 15.0 vp
    saveSc.SetBackgroundBorderColor(Color::GREEN);
    saveSc.SetBackgroundBorderStyle(BorderStyle::DOTTED);
    saveSc.SetBackgroundBorderRadius(Dimension(15.0)); // 15.0 vp
    saveSc.SetBackgroundPadding(Dimension(25.0)); // 25.0 vp

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
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
 * @tc.name: SecurityComponentSavePropertyTest007
 * @tc.desc: Test set security component property without icon
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentSavePropertyTest007, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(1, -1, static_cast<int32_t>(ButtonType::CAPSULE),
        V2::SAVE_BUTTON_ETS_TAG);
    SaveButtonModelNG saveSc;
    saveSc.SetTextIconSpace(Dimension(15.0)); // 15.0vp

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetTextIconSpace().value_or(Dimension(0.0)).ConvertToVp(), 15.0);
}

/**
 * @tc.name: SecurityComponentSavePropertyTest008
 * @tc.desc: Test set security component property with customize permission
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentSavePropertyTest008, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, static_cast<int32_t>(ButtonType::CAPSULE),
        V2::SAVE_BUTTON_ETS_TAG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    property->UpdateHasCustomPermissionForSecComp(true);
    SaveButtonModelNG sc;
    std::optional<NG::CalcLength> width(Dimension(15.0));
    std::optional<NG::CalcLength> height(Dimension(15.0));
    sc.SetIconSize(CalcSize(width, height));
    sc.SetIconBorderRadius(Dimension(3.0));
    sc.SetText(CUSTOMIZE_TEXT);
    sc.SetStateEffect(false);
    sc.SetTipPosition(TipPosition::BELOW_TOP);

    NG::BorderRadiusProperty borderRadiusEmpty;
    NG::BorderRadiusProperty borderRadiusSetted;
    borderRadiusSetted.radiusTopLeft = Dimension(3.0);
    borderRadiusSetted.radiusTopRight = Dimension(3.0);
    borderRadiusSetted.radiusBottomLeft = Dimension(3.0);
    borderRadiusSetted.radiusBottomRight = Dimension(3.0);
    std::optional<NG::CalcLength> widthDefault(Dimension(16.0));
    std::optional<NG::CalcLength> heightDefault(Dimension(16.0));
    EXPECT_EQ(property->GetIconCalcSize().value_or(CalcSize(widthDefault, heightDefault)), CalcSize(width, height));
    EXPECT_EQ(property->GetIconBorderRadius().value_or(borderRadiusEmpty), borderRadiusSetted);
    EXPECT_EQ(property->GetTextContent().value_or(""), CUSTOMIZE_TEXT);
    EXPECT_EQ(property->GetStateEffect().value_or(true), false);
    EXPECT_EQ(property->GetTipPosition().value_or(TipPosition::ABOVE_BOTTOM), TipPosition::BELOW_TOP);

    std::optional<Dimension> topLeft(Dimension(3.0));
    std::optional<Dimension> topRight(Dimension(3.0));
    std::optional<Dimension> bottomLeft(Dimension(3.0));
    std::optional<Dimension> bottomRight(Dimension(3.0));
    sc.SetIconBorderRadius(topLeft, topRight, bottomLeft, bottomRight);
    EXPECT_EQ(property->GetIconBorderRadius().value_or(borderRadiusEmpty), borderRadiusSetted);
}

/**
 * @tc.name: SecurityComponentSavePropertyTest009
 * @tc.desc: Test set security component property without customize permission
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentSavePropertyTest009, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, static_cast<int32_t>(ButtonType::CAPSULE),
        V2::SAVE_BUTTON_ETS_TAG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    property->UpdateHasCustomPermissionForSecComp(false);
    SaveButtonModelNG sc;
    std::optional<NG::CalcLength> width(Dimension(15.0));
    std::optional<NG::CalcLength> height(Dimension(15.0));
    sc.SetIconSize(CalcSize(width, height));
    sc.SetIconBorderRadius(Dimension(3.0));
    sc.SetText(CUSTOMIZE_TEXT);
    sc.SetStateEffect(false);
    sc.SetTipPosition(TipPosition::BELOW_TOP);

    NG::BorderRadiusProperty borderRadiusEmpty;
    NG::BorderRadiusProperty borderRadiusSetted;
    borderRadiusSetted.radiusTopLeft = Dimension(3.0);
    borderRadiusSetted.radiusTopRight = Dimension(3.0);
    borderRadiusSetted.radiusBottomLeft = Dimension(3.0);
    borderRadiusSetted.radiusBottomRight = Dimension(3.0);
    std::optional<NG::CalcLength> widthDefault(Dimension(16.0));
    std::optional<NG::CalcLength> heightDefault(Dimension(16.0));
    EXPECT_EQ(property->GetIconCalcSize().value_or(CalcSize(widthDefault, heightDefault)),
        CalcSize(width, height));
    EXPECT_EQ(property->GetIconBorderRadius().value_or(borderRadiusEmpty), borderRadiusEmpty);
    EXPECT_EQ(property->GetTextContent().value_or(""), "");
    EXPECT_EQ(property->GetStateEffect().value_or(true), true);
    EXPECT_EQ(property->GetTipPosition().value_or(TipPosition::ABOVE_BOTTOM), TipPosition::ABOVE_BOTTOM);

    std::optional<Dimension> topLeft(Dimension(3.0));
    std::optional<Dimension> topRight(Dimension(3.0));
    std::optional<Dimension> bottomLeft(Dimension(3.0));
    std::optional<Dimension> bottomRight(Dimension(3.0));
    sc.SetIconBorderRadius(topLeft, topRight, bottomLeft, bottomRight);
    EXPECT_EQ(property->GetIconBorderRadius().value_or(borderRadiusEmpty), borderRadiusEmpty);
}

/**
 * @tc.name: SecurityComponentSavePropertyTest010
 * @tc.desc: Test set security component text without init text
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentSavePropertyTest010, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(-1, 1, static_cast<int32_t>(ButtonType::CAPSULE),
        V2::SAVE_BUTTON_ETS_TAG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    property->UpdateHasCustomPermissionForSecComp(true);
    SaveButtonModelNG sc;
    sc.SetText(CUSTOMIZE_TEXT);

    EXPECT_EQ(property->GetTextContent().value_or(""), CUSTOMIZE_TEXT);
}

/**
 * @tc.name: SecurityComponentSavePatternTest001
 * @tc.desc: Test default security component modifyDone
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentSavePatternTest001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::SAVE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetTag(), V2::SAVE_BUTTON_ETS_TAG);

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
 * @tc.name: SecurityComponentSavePatternTest002
 * @tc.desc: Test event callback
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentSavePatternTest002, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::SAVE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetTag(), V2::SAVE_BUTTON_ETS_TAG);

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
 * @tc.name: SecurityComponentSaveLayoutAlgoTest001
 * @tc.desc: Test default layout algo
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentSaveLayoutAlgoTest001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::SAVE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetTag(), V2::SAVE_BUTTON_ETS_TAG);
    auto pattern = frameNode->GetPattern<SecurityComponentPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnModifyDone();

    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    property->UpdateMarginSelfIdealSize(SizeF(MIN_SIZE, MIN_SIZE));
    property->UpdateContentConstraint();

    auto layoutAlgo = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgo, nullptr);

    auto layoutWrapper = CreateSecurityComponentLayoutWrapper(frameNode);
    ASSERT_NE(layoutWrapper, nullptr);
    layoutAlgo->Measure(layoutWrapper.rawPtr_);
    layoutAlgo->Layout(layoutWrapper.rawPtr_);
    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameSize().Height(), DEFAULT_ICON_MIN_SIZE);
    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameSize().Width(), DEFAULT_ICON_MIN_SIZE);

    property->UpdateBackgroundType(static_cast<int32_t>(ButtonType::CAPSULE));
    property->UpdateTextIconLayoutDirection(SecurityComponentLayoutDirection::VERTICAL);
    pattern->OnModifyDone();

    layoutAlgo->Measure(layoutWrapper.rawPtr_);
    layoutAlgo->Layout(layoutWrapper.rawPtr_);
    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameSize().Height(), DEFAULT_ICON_MIN_SIZE);
    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameSize().Width(), DEFAULT_ICON_MIN_SIZE);
}

/**
 * @tc.name: SecurityComponentSaveAccessibilityPropertyTest001
 * @tc.desc: Test security component accessibility property
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentSaveAccessibilityPropertyTest001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::SAVE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetTag(), V2::SAVE_BUTTON_ETS_TAG);
    auto pattern = frameNode->GetPattern<SecurityComponentPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnModifyDone();

    auto accessibility = pattern->CreateAccessibilityProperty();
    ASSERT_NE(accessibility, nullptr);
    accessibility->SetHost(frameNode);
}

/**
 * @tc.name: SecurityComponentPastePropertyTest001
 * @tc.desc: Test default properties of security component.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentPastePropertyTest001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0, static_cast<int32_t>(ButtonType::CAPSULE),
        V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetTag(), V2::PASTE_BUTTON_ETS_TAG);

    CheckSecurityComponentDefaultProp(frameNode);

    // text node property
    auto textNode = GetSecCompChildNode(frameNode, V2::TEXT_ETS_TAG);
    ASSERT_NE(textNode, nullptr);
    auto textProp = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textProp, nullptr);
    EXPECT_EQ(textProp->GetMaxLines().value_or(0), 1000000);
    EXPECT_EQ(textProp->GetFontSize().value_or(Dimension(0.0)).ConvertToVp(), DEFAULT_FONT_SIZE);
    EXPECT_EQ(textProp->GetItalicFontStyle().value_or(Ace::FontStyle::ITALIC), Ace::FontStyle::NORMAL);
    EXPECT_EQ(textProp->GetFontWeight().value_or(FontWeight::NORMAL), FontWeight::MEDIUM);
    std::vector<std::string> emptyVec;
    auto fontFamily = textProp->GetFontFamily().value_or(emptyVec);
    EXPECT_TRUE(fontFamily.empty());
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

    EXPECT_EQ(buttonRender->GetBackgroundColor().value_or(Color()), Color::BLUE);
    EXPECT_EQ(buttonProp->GetType().value_or(ButtonType::NORMAL), ButtonType::CAPSULE);
}

/**
 * @tc.name: SecurityComponentPastePropertyTest002
 * @tc.desc: Test default properties of security component without background
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentPastePropertyTest002, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        BUTTON_TYPE_NULL, V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetTag(), V2::PASTE_BUTTON_ETS_TAG);

    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetBackgroundType().value_or(static_cast<int32_t>(ButtonType::NORMAL)),
        BUTTON_TYPE_NULL);
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
 * @tc.name: SecurityComponentPastePropertyTest003
 * @tc.desc: Test default properties of security component without icon
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentPastePropertyTest003, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(1, -1,
        BUTTON_TYPE_NULL, V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetTag(), V2::PASTE_BUTTON_ETS_TAG);

    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetIconStyle().value_or(1), -1);
    EXPECT_EQ(property->GetTextIconSpace().value_or(Dimension(0.0)).ConvertToVp(), 0.0);

    auto iconNode = GetSecCompChildNode(frameNode, V2::IMAGE_ETS_TAG);
    ASSERT_EQ(iconNode, nullptr);
}

/**
 * @tc.name: SecurityComponentPastePropertyTest004
 * @tc.desc: Test set security component property
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentPastePropertyTest004, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    SetPasteUserDefinedPropty();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetTextIconSpace().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetBackgroundLeftPadding().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetBackgroundRightPadding().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetBackgroundTopPadding().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetBackgroundBottomPadding().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetTextIconLayoutDirection().value_or(SecurityComponentLayoutDirection::HORIZONTAL),
        SecurityComponentLayoutDirection::VERTICAL);

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
    EXPECT_EQ(buttonRender->GetBackgroundColor().value_or(Color()), Color::GRAY);
}

/**
 * @tc.name: SecurityComponentPastePropertyTest005
 * @tc.desc: Test set security component property
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentPastePropertyTest005, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    SetPasteUserDefinedPropty();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetTextIconSpace().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetBackgroundLeftPadding().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetBackgroundRightPadding().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetBackgroundTopPadding().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetBackgroundBottomPadding().value_or(Dimension(0.0)).ConvertToVp(), 25.0); // 25.0 vp
    EXPECT_EQ(property->GetTextIconLayoutDirection().value_or(SecurityComponentLayoutDirection::HORIZONTAL),
        SecurityComponentLayoutDirection::VERTICAL);

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
    EXPECT_EQ(buttonRender->GetBackgroundColor().value_or(Color()), Color::GRAY);
}

/**
 * @tc.name: SecurityComponentPastePropertyTest006
 * @tc.desc: Test set security component property without background
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentPastePropertyTest006, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(0, 0, BUTTON_TYPE_NULL, V2::PASTE_BUTTON_ETS_TAG);
    PasteButtonModelNG pasteSc;
    pasteSc.SetBackgroundColor(Color::GRAY);
    pasteSc.SetBackgroundBorderWidth(Dimension(15.0)); // 15.0 vp
    pasteSc.SetBackgroundBorderColor(Color::GREEN);
    pasteSc.SetBackgroundBorderStyle(BorderStyle::DOTTED);
    pasteSc.SetBackgroundBorderRadius(Dimension(15.0)); // 15.0 vp
    pasteSc.SetBackgroundPadding(Dimension(25.0)); // 25.0 vp

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
 * @tc.name: SecurityComponentPastePropertyTest007
 * @tc.desc: Test set security component property without icon
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentPastePropertyTest007, TestSize.Level0)
{
    CreateSecurityComponentNotFinish(1, -1, static_cast<int32_t>(ButtonType::CAPSULE),
        V2::PASTE_BUTTON_ETS_TAG);
    PasteButtonModelNG pasteSc;
    pasteSc.SetTextIconSpace(Dimension(15.0)); // 15.0vp

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetTextIconSpace().value_or(Dimension(0.0)).ConvertToVp(), 15.0);
}

/**
 * @tc.name: SecurityComponentPastePatternTest001
 * @tc.desc: Test default security component modifyDone
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentPastePatternTest001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetTag(), V2::PASTE_BUTTON_ETS_TAG);

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
 * @tc.name: SecurityComponentPastePatternTest002
 * @tc.desc: Test event callback
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentPastePatternTest002, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetTag(), V2::PASTE_BUTTON_ETS_TAG);

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
 * @tc.name: SecurityComponentPasteLayoutAlgoTest001
 * @tc.desc: Test default layout algo
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentPasteLayoutAlgoTest001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetTag(), V2::PASTE_BUTTON_ETS_TAG);
    auto pattern = frameNode->GetPattern<SecurityComponentPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnModifyDone();
    auto property = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    ASSERT_NE(property, nullptr);
    property->UpdateMarginSelfIdealSize(SizeF(MIN_SIZE, MIN_SIZE));
    property->UpdateContentConstraint();

    auto layoutAlgo = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgo, nullptr);

    auto layoutWrapper = CreateSecurityComponentLayoutWrapper(frameNode);
    ASSERT_NE(layoutWrapper, nullptr);
    layoutAlgo->Measure(layoutWrapper.rawPtr_);
    layoutAlgo->Layout(layoutWrapper.rawPtr_);
    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameSize().Height(), DEFAULT_ICON_MIN_SIZE);
    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameSize().Width(), DEFAULT_ICON_MIN_SIZE);
    property->UpdateBackgroundType(static_cast<int32_t>(ButtonType::CAPSULE));
    property->UpdateTextIconLayoutDirection(SecurityComponentLayoutDirection::VERTICAL);
    pattern->OnModifyDone();

    layoutAlgo->Measure(layoutWrapper.rawPtr_);
    layoutAlgo->Layout(layoutWrapper.rawPtr_);
    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameSize().Height(), DEFAULT_ICON_MIN_SIZE);
    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameSize().Width(), DEFAULT_ICON_MIN_SIZE);
}

/**
 * @tc.name: SecurityComponentPasteAccessibilityPropertyTest001
 * @tc.desc: Test security component accessibility property
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentPasteAccessibilityPropertyTest001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetTag(), V2::PASTE_BUTTON_ETS_TAG);
    auto pattern = frameNode->GetPattern<SecurityComponentPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnModifyDone();

    auto accessibility = pattern->CreateAccessibilityProperty();
    ASSERT_NE(accessibility, nullptr);
    accessibility->SetHost(frameNode);
}

/**
 * @tc.name: SecurityComponentGetIconResourceTest001
 * @tc.desc: Test set security component property with invalid icon
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentGetIconResourceTest001, TestSize.Level0)
{
    InternalResource::ResourceId id;
    EXPECT_FALSE(LocationButtonModelNG::GetInstance()->GetIconResource(-1, id));
    EXPECT_FALSE(LocationButtonModelNG::GetInstance()->GetIconResource(ICON_RESOURCE_TABLE + 1, id));
    EXPECT_FALSE(PasteButtonModelNG::GetInstance()->GetIconResource(-1, id));
    EXPECT_FALSE(PasteButtonModelNG::GetInstance()->GetIconResource(ICON_RESOURCE_TABLE + 1, id));
    EXPECT_FALSE(SaveButtonModelNG::GetInstance()->GetIconResource(-1, id));
    EXPECT_FALSE(SaveButtonModelNG::GetInstance()->GetIconResource(ICON_RESOURCE_TABLE + 1, id));
}

/**
 * @tc.name: SecurityComponentHandlerTest001
 * @tc.desc: Test security component handler
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentHandlerTest001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    RefPtr<FrameNode> invalidFrameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), "test");
    int32_t scId;
    GestureEvent info;

    int32_t invalidId = -1;
    int32_t noExistId = 0;
    std::string message;
    EXPECT_EQ(SecurityComponentHandler::RegisterSecurityComponent(invalidFrameNode, scId), -1);
    EXPECT_EQ(SecurityComponentHandler::UpdateSecurityComponent(invalidFrameNode, noExistId), -1);
    EXPECT_EQ(SecurityComponentHandler::UnregisterSecurityComponent(invalidId), -1);
    EXPECT_EQ(SecurityComponentHandler::ReportSecurityComponentClickEvent(
        invalidId, frameNode, info, [](int32_t) {}, message), -1);
    EXPECT_EQ(SecurityComponentHandler::ReportSecurityComponentClickEvent(
        noExistId, invalidFrameNode, info, [] (int32_t) {}, message), -1);

    KeyEvent key;
    EXPECT_EQ(SecurityComponentHandler::ReportSecurityComponentClickEvent(
        noExistId, invalidFrameNode, key, [] (int32_t) {}), -1);
    key.enhanceData = { 0 };
    EXPECT_EQ(SecurityComponentHandler::ReportSecurityComponentClickEvent(
        noExistId, invalidFrameNode, key, [] (int32_t) {}), -1);
}

/**
 * @tc.name: SecurityComponentHandlerTest002
 * @tc.desc: Test security component handler
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentHandlerTest002, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::SAVE_BUTTON_ETS_TAG);
    int32_t scId;
    GestureEvent info;

    int32_t noExistId = 0;
    std::string message;
    ASSERT_EQ(SecurityComponentHandler::RegisterSecurityComponent(frameNode, scId), -1);
    ASSERT_EQ(SecurityComponentHandler::UpdateSecurityComponent(frameNode, noExistId), -1);
    ASSERT_EQ(SecurityComponentHandler::UnregisterSecurityComponent(noExistId), 0);
    ASSERT_EQ(SecurityComponentHandler::ReportSecurityComponentClickEvent(
        noExistId, frameNode, info, [] (int32_t) {}, message), -1);
}

/**
 * @tc.name: SecurityComponentHandlerTest003
 * @tc.desc: Test security component handler
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentHandlerTest003, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::LOCATION_BUTTON_ETS_TAG);
    int32_t scId;
    GestureEvent info;

    int32_t noExistId = 0;
    std::string message;
    ASSERT_EQ(SecurityComponentHandler::RegisterSecurityComponent(frameNode, scId), -1);
    ASSERT_EQ(SecurityComponentHandler::UpdateSecurityComponent(frameNode, noExistId), -1);
    ASSERT_EQ(SecurityComponentHandler::UnregisterSecurityComponent(noExistId), 0);
    ASSERT_EQ(SecurityComponentHandler::ReportSecurityComponentClickEvent(
        noExistId, frameNode, info, [] (int32_t) {}, message), -1);
}

/**
 * @tc.name: SecurityComponentHandlerTest004
 * @tc.desc: Test security component handler
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentHandlerTest004, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    int32_t scId;
    GestureEvent info;

    int32_t noExistId = 0;
    std::string message;
    ASSERT_EQ(SecurityComponentHandler::RegisterSecurityComponent(frameNode, scId), -1);
    ASSERT_EQ(SecurityComponentHandler::UpdateSecurityComponent(frameNode, noExistId), -1);
    ASSERT_EQ(SecurityComponentHandler::UnregisterSecurityComponent(noExistId), 0);
    ASSERT_EQ(SecurityComponentHandler::ReportSecurityComponentClickEvent(
        noExistId, frameNode, info, [] (int32_t) {}, message), -1);
}

/**
 * @tc.name: SecurityComponentHandlerTest005
 * @tc.desc: Test security component handler
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentHandlerTest005, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    std::string message;
    ASSERT_EQ(SecurityComponentHandler::CheckComponentCoveredStatus(frameNode->GetId(), message), false);
}

/**
 * @tc.name: SecurityComponentCheckParentNodesEffectTest001
 * @tc.desc: Test security component CheckParentNodesEffect
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentCheckParentNodesEffectTest001, TestSize.Level0)
{
    RefPtr<FrameNode> parentFrameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(parentFrameNode, nullptr);
    RefPtr<FrameNode> childFrameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(childFrameNode, nullptr);
    parentFrameNode->AddChild(childFrameNode);

    // security component is not completely displayed
    OHOS::Security::SecurityComponent::SecCompBase buttonInfo;
    std::string message;
    ASSERT_FALSE(SecurityComponentHandler::CheckParentNodesEffect(childFrameNode, buttonInfo, message));
    RefPtr<RenderContext> parentRenderContext = parentFrameNode->GetRenderContext();
    auto parentFrameRect = parentRenderContext->GetPaintRectWithTransform();
    RefPtr<RenderContext> childRenderContext = childFrameNode->GetRenderContext();
    auto childFrameRect = childRenderContext->GetPaintRectWithTransform();
    ASSERT_EQ(parentFrameRect.Width(), childFrameRect.Width());
    ASSERT_EQ(parentFrameRect.Height(), childFrameRect.Height());

    PixStretchEffectOption pixelStretchEffectOption;
    auto renderContext = parentFrameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdatePixelStretchEffect(pixelStretchEffectOption);
    ASSERT_TRUE(SecurityComponentHandler::CheckParentNodesEffect(childFrameNode, buttonInfo, message));
}

/**
 * @tc.name: SecurityComponentCheckParentNodesEffectTest002
 * @tc.desc: Test security component CheckParentNodesEffect
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentCheckParentNodesEffectTest002, TestSize.Level0)
{
    RefPtr<FrameNode> parentFrameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(parentFrameNode, nullptr);
    RefPtr<FrameNode> childFrameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(childFrameNode, nullptr);
    parentFrameNode->AddChild(childFrameNode);

    auto renderContext = parentFrameNode->GetRenderContext();
    OHOS::Security::SecurityComponent::SecCompBase buttonInfo;
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateLightUpEffect(1);
    std::string message;
    ASSERT_TRUE(SecurityComponentHandler::CheckParentNodesEffect(childFrameNode, buttonInfo, message));
}

/**
 * @tc.name: SecurityComponentCheckParentNodesEffectTest003
 * @tc.desc: Test security component CheckParentNodesEffect
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentCheckParentNodesEffectTest003, TestSize.Level0)
{
    RefPtr<FrameNode> parentFrameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(parentFrameNode, nullptr);
    RefPtr<FrameNode> childFrameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(childFrameNode, nullptr);
    parentFrameNode->AddChild(childFrameNode);

    auto renderContext = parentFrameNode->GetRenderContext();
    OHOS::Security::SecurityComponent::SecCompBase buttonInfo;
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateSphericalEffect(0);
    std::string message;
    ASSERT_FALSE(SecurityComponentHandler::CheckParentNodesEffect(childFrameNode, buttonInfo, message));
    ASSERT_EQ(renderContext->GetSphericalEffect().value(), 0.0f);
    renderContext->UpdateSphericalEffect(1);
    ASSERT_TRUE(SecurityComponentHandler::CheckParentNodesEffect(childFrameNode, buttonInfo, message));
}

/**
 * @tc.name: LocationGetIconResourceStaticTest001
 * @tc.desc: Test security component GetIconResourceStatic
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, LocationGetIconResourceStaticTest001, TestSize.Level0)
{
    int32_t iconStyle = -1;
    InternalResource::ResourceId id;
    ASSERT_FALSE(LocationButtonModelNG::GetIconResourceStatic(iconStyle, id));

    iconStyle = 2;
    ASSERT_FALSE(LocationButtonModelNG::GetIconResourceStatic(iconStyle, id));

    iconStyle = 0;
    ASSERT_TRUE(LocationButtonModelNG::GetIconResourceStatic(iconStyle, id));
}

/**
 * @tc.name: LocationGetTextResourceStatic001
 * @tc.desc: Test security component GetTextResourceStatic
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, LocationGetTextResourceStatic001, TestSize.Level0)
{
    int32_t textStyle = 0;
    std::string text;

    ASSERT_TRUE(LocationButtonModelNG::GetTextResourceStatic(textStyle, text));
}

/**
 * @tc.name: LocationInitLocationButton001
 * @tc.desc: Test security component InitLocationButton001
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, LocationInitLocationButton001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    bool isArkuiComponent = false;
    LocationButtonStyle style;
    style.text = LocationButtonLocationDescription::TEXT_NULL;
    style.icon = LocationButtonIconStyle::ICON_NULL;
    ASSERT_TRUE(LocationButtonModelNG::InitLocationButton(frameNode.rawPtr_, style, isArkuiComponent));

    style.text = LocationButtonStyle::DEFAULT_TEXT;
    style.icon = LocationButtonIconStyle::ICON_NULL;
    ASSERT_TRUE(LocationButtonModelNG::InitLocationButton(frameNode.rawPtr_, style, isArkuiComponent));

    style.text = LocationButtonLocationDescription::TEXT_NULL;
    style.icon = LocationButtonStyle::DEFAULT_ICON;
    ASSERT_TRUE(LocationButtonModelNG::InitLocationButton(frameNode.rawPtr_, style, isArkuiComponent));

    style.text = LocationButtonStyle::DEFAULT_TEXT;
    style.icon = LocationButtonStyle::DEFAULT_ICON;
    ASSERT_TRUE(LocationButtonModelNG::InitLocationButton(frameNode.rawPtr_, style, isArkuiComponent));
}

/**
 * @tc.name: PasteButtonGetIconResourceStaticTest001
 * @tc.desc: Test security component GetIconResourceStatic
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, PasteButtonGetIconResourceStaticTest001, TestSize.Level0)
{
    int32_t iconStyle = -1;
    InternalResource::ResourceId id;
    ASSERT_FALSE(PasteButtonModelNG::GetIconResourceStatic(iconStyle, id));

    iconStyle = 2;
    ASSERT_FALSE(PasteButtonModelNG::GetIconResourceStatic(iconStyle, id));

    iconStyle = 0;
    ASSERT_TRUE(PasteButtonModelNG::GetIconResourceStatic(iconStyle, id));
}

/**
 * @tc.name: PasteGetTextResourceStatic001
 * @tc.desc: Test security component GetTextResourceStatic
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, PasteGetTextResourceStatic001, TestSize.Level0)
{
    int32_t textStyle = 0;
    std::string text;

    ASSERT_TRUE(PasteButtonModelNG::GetTextResourceStatic(textStyle, text));
}

/**
 * @tc.name: InitPasteButton001
 * @tc.desc: Test security component InitPasteButton
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, InitPasteButton001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    bool isArkuiComponent = false;
    PasteButtonStyle style;
    style.text = PasteButtonPasteDescription::TEXT_NULL;
    style.icon = PasteButtonIconStyle::ICON_NULL;
    ASSERT_TRUE(PasteButtonModelNG::InitPasteButton(frameNode.rawPtr_, style, isArkuiComponent));

    style.text = PasteButtonStyle::DEFAULT_TEXT;
    style.icon = PasteButtonIconStyle::ICON_NULL;
    ASSERT_TRUE(PasteButtonModelNG::InitPasteButton(frameNode.rawPtr_, style, isArkuiComponent));

    style.text = PasteButtonPasteDescription::TEXT_NULL;
    style.icon = PasteButtonStyle::DEFAULT_ICON;
    ASSERT_TRUE(PasteButtonModelNG::InitPasteButton(frameNode.rawPtr_, style, isArkuiComponent));

    style.text = PasteButtonStyle::DEFAULT_TEXT;
    style.icon = PasteButtonStyle::DEFAULT_ICON;
    ASSERT_TRUE(PasteButtonModelNG::InitPasteButton(frameNode.rawPtr_, style, isArkuiComponent));
}

/**
 * @tc.name: SaveButtonGetIconResourceStaticTest001
 * @tc.desc: Test security component GetIconResourceStatic
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SaveButtonGetIconResourceStaticTest001, TestSize.Level0)
{
    int32_t iconStyle = -1;
    InternalResource::ResourceId id;
    ASSERT_FALSE(SaveButtonModelNG::GetIconResourceStatic(iconStyle, id));

    iconStyle = 3;
    ASSERT_FALSE(SaveButtonModelNG::GetIconResourceStatic(iconStyle, id));

    iconStyle = 0;
    ASSERT_TRUE(SaveButtonModelNG::GetIconResourceStatic(iconStyle, id));
}

/**
 * @tc.name: SaveGetTextResourceStatic001
 * @tc.desc: Test security component GetTextResourceStatic
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SaveGetTextResourceStatic001, TestSize.Level0)
{
    int32_t textStyle = 0;
    std::string text;

    ASSERT_TRUE(SaveButtonModelNG::GetTextResourceStatic(textStyle, text));
}

/**
 * @tc.name: SaveLocationButton001
 * @tc.desc: Test security component InitSaveButton
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SaveLocationButton001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    bool isArkuiComponent = false;
    SaveButtonStyle style;
    style.text = SaveButtonSaveDescription::TEXT_NULL;
    style.icon = SaveButtonIconStyle::ICON_NULL;
    ASSERT_TRUE(SaveButtonModelNG::InitSaveButton(frameNode.rawPtr_, style, isArkuiComponent));

    style.text = SaveButtonSaveDescription::TEXT_NULL;
    style.icon = SaveButtonStyle::DEFAULT_ICON;
    ASSERT_TRUE(SaveButtonModelNG::InitSaveButton(frameNode.rawPtr_, style, isArkuiComponent));

    style.text = SaveButtonStyle::DEFAULT_TEXT;
    style.icon = SaveButtonIconStyle::ICON_NULL;
    ASSERT_TRUE(SaveButtonModelNG::InitSaveButton(frameNode.rawPtr_, style, isArkuiComponent));

    style.text = SaveButtonStyle::DEFAULT_TEXT;
    style.icon = SaveButtonStyle::DEFAULT_ICON;
    ASSERT_TRUE(SaveButtonModelNG::InitSaveButton(frameNode.rawPtr_, style, isArkuiComponent));
}

/**
 * @tc.name: InitChildNode001
 * @tc.desc: Test security component InitChildNode
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, InitChildNode001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
    static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    SecurityComponentElementStyle secCompStyle = {
        .text = static_cast<int32_t>(SecurityComponentDescription::TEXT_NULL),
        .icon = static_cast<int32_t>(SecurityComponentIconStyle::ICON_NULL),
        .backgroundType = BUTTON_TYPE_NULL,
        .symbolIcon = false
    };
    LocationButtonModelNG::GetIconResourceFuncType getIconResource = SaveButtonModelNG::GetIconResourceStatic;
    LocationButtonModelNG::GetTextResourceFuncType getTextResource = SaveButtonModelNG::GetTextResourceStatic;

    // style.backgroundType == BUTTON_TYPE_NULL, symbolIcon = false
    SecurityComponentModelNG::InitChildNode(frameNode.rawPtr_, secCompStyle, getIconResource, getTextResource);
    ASSERT_FALSE(secCompStyle.symbolIcon);
    ASSERT_TRUE(secCompStyle.symbolIcon != static_cast<uint32_t>(SecurityComponentIconStyle::ICON_NULL));
    ASSERT_FALSE(secCompStyle.icon != static_cast<int32_t>(SecurityComponentIconStyle::ICON_NULL));
    ASSERT_FALSE(secCompStyle.text != static_cast<int32_t>(SecurityComponentDescription::TEXT_NULL));

    // style.backgroundType != BUTTON_TYPE_NULL, symbolIcon = ICON_NULL
    secCompStyle.backgroundType = static_cast<int32_t>(SaveButtonStyle::DEFAULT_BACKGROUND_TYPE);
    secCompStyle.symbolIcon = static_cast<uint32_t>(SecurityComponentIconStyle::ICON_NULL);
    secCompStyle.icon = static_cast<int32_t>(SaveButtonStyle::DEFAULT_ICON);
    secCompStyle.text = static_cast<int32_t>(SaveButtonStyle::DEFAULT_TEXT);
    SecurityComponentModelNG::InitChildNode(frameNode.rawPtr_, secCompStyle, getIconResource, getTextResource);
    ASSERT_TRUE(secCompStyle.symbolIcon);
    ASSERT_FALSE(secCompStyle.symbolIcon != static_cast<uint32_t>(SecurityComponentIconStyle::ICON_NULL));
    ASSERT_TRUE(secCompStyle.icon != static_cast<int32_t>(SecurityComponentIconStyle::ICON_NULL));
    ASSERT_TRUE(secCompStyle.text != static_cast<int32_t>(SecurityComponentDescription::TEXT_NULL));

    // style.symbolIcon != -1
    secCompStyle.symbolIcon = 1;
    SecurityComponentModelNG::InitChildNode(frameNode.rawPtr_, secCompStyle, getIconResource, getTextResource);
    ASSERT_TRUE(secCompStyle.symbolIcon);
    ASSERT_TRUE(secCompStyle.symbolIcon != static_cast<uint32_t>(SecurityComponentIconStyle::ICON_NULL));
}

/**
 * @tc.name: InitSecurityComponent001
 * @tc.desc: Test security component InitSecurityComponent
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, InitSecurityComponent001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
    static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);

    SecurityComponentElementStyle secCompStyle = {
        .text = static_cast<int32_t>(SaveButtonStyle::DEFAULT_TEXT),
        .icon = static_cast<int32_t>(SaveButtonStyle::DEFAULT_ICON),
        .backgroundType = static_cast<int32_t>(SaveButtonStyle::DEFAULT_BACKGROUND_TYPE)
    };
    bool isArkuiComponent = false;
    LocationButtonModelNG::GetIconResourceFuncType getIconResource = SaveButtonModelNG::GetIconResourceStatic;
    LocationButtonModelNG::GetTextResourceFuncType getTextResource = SaveButtonModelNG::GetTextResourceStatic;

    ASSERT_TRUE(SecurityComponentModelNG::InitSecurityComponent(
        frameNode.rawPtr_, secCompStyle, isArkuiComponent, getIconResource, getTextResource));
}

/**
 * @tc.name: IsBackgroundVisible001
 * @tc.desc: Test security component IsBackgroundVisible
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, IsBackgroundVisible001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
    static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_TRUE(SecurityComponentModelNG::IsBackgroundVisible(frameNode.rawPtr_));
}

/**
 * @tc.name: IsArkuiComponent001
 * @tc.desc: Test security component IsArkuiComponent
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, IsArkuiComponent001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
    static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);

    auto prop = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    prop->UpdateIsArkuiComponent(true);
    ASSERT_TRUE(SecurityComponentModelNG::IsArkuiComponent(frameNode.rawPtr_));
}

/**
 * @tc.name: SetIconSize001
 * @tc.desc: Test security component SetIconSize
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SetIconSize001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
    static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);

    std::optional<Dimension> value = std::nullopt;
    SecurityComponentModelNG::SetIconSize(frameNode.rawPtr_, value);
    ASSERT_FALSE(value);

    value = Dimension(15.0);
    SecurityComponentModelNG::SetIconSize(frameNode.rawPtr_, value);
    ASSERT_TRUE(value);
}

/**
 * @tc.name: SetIconColor001
 * @tc.desc: Test security component SetIconColor
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SetIconColor001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
    static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);

    std::optional<Color> value = std::nullopt;
    SecurityComponentModelNG::SetIconColor(frameNode.rawPtr_, value);
    ASSERT_FALSE(value);

    value = Color::RED;
    SecurityComponentModelNG::SetIconColor(frameNode.rawPtr_, value);
    ASSERT_TRUE(value);
}

/**
 * @tc.name: SetFontSize001
 * @tc.desc: Test security component SetFontSize
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SetFontSize001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
    static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);

    std::optional<Dimension> value = std::nullopt;
    SecurityComponentModelNG::SetFontSize(frameNode.rawPtr_, value);
    ASSERT_FALSE(value);

    value = Dimension(15.0);
    SecurityComponentModelNG::SetFontSize(frameNode.rawPtr_, value);
    ASSERT_TRUE(value);
}

/**
 * @tc.name: SetFontStyle001
 * @tc.desc: Test security component SetFontStyle
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SetFontStyle001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
    static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);

    std::optional<Ace::FontStyle> value = std::nullopt;
    SecurityComponentModelNG::SetFontStyle(frameNode.rawPtr_, value);
    ASSERT_FALSE(value);

    value = Ace::FontStyle::ITALIC;
    SecurityComponentModelNG::SetFontStyle(frameNode.rawPtr_, value);
    ASSERT_TRUE(value);
}

/**
 * @tc.name: SetFontWeight001
 * @tc.desc: Test security component SetFontWeight
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SetFontWeight001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
    static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);

    std::optional<FontWeight> value = std::nullopt;
    SecurityComponentModelNG::SetFontWeight(frameNode.rawPtr_, value);
    ASSERT_FALSE(value);

    value = FontWeight::W200;
    SecurityComponentModelNG::SetFontWeight(frameNode.rawPtr_, value);
    ASSERT_TRUE(value);
}

/**
 * @tc.name: SetFontFamily001
 * @tc.desc: Test security component SetFontFamily
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SetFontFamily001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
    static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);

    std::optional<std::vector<std::string>> fontFamilies = std::nullopt;
    SecurityComponentModelNG::SetFontFamily(frameNode.rawPtr_, fontFamilies);
    ASSERT_FALSE(fontFamilies);

    fontFamilies = { "testFont" };
    SecurityComponentModelNG::SetFontFamily(frameNode.rawPtr_, fontFamilies);
    ASSERT_TRUE(fontFamilies);
}

/**
 * @tc.name: SetFontColor001
 * @tc.desc: Test security component SetFontColor
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SetFontColor001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
    static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);

    std::optional<Color> value = std::nullopt;
    SecurityComponentModelNG::SetFontColor(frameNode.rawPtr_, value);
    ASSERT_FALSE(value);

    value = Color::BLUE;
    SecurityComponentModelNG::SetFontColor(frameNode.rawPtr_, value);
    ASSERT_TRUE(value);
}

/**
 * @tc.name: SetBackgroundColor001
 * @tc.desc: Test security component SetBackgroundColor
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SetBackgroundColor001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
    static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);

    // IsBackgroundVisible = false
    auto prop = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    prop->UpdateBackgroundType(-1);
    std::optional<Color> valueOpt = std::nullopt;
    SecurityComponentModelNG::SetBackgroundColor(frameNode.rawPtr_, valueOpt);

    // valueOpt.has_value() = false
    prop->UpdateBackgroundType(static_cast<int32_t>(ButtonType::CAPSULE));
    SecurityComponentModelNG::SetBackgroundColor(frameNode.rawPtr_, valueOpt);

    // IsInReleaseList = false, IsArkuiComponent = false, IsBelowThreshold = true
    valueOpt = Color::FOREGROUND;
    prop->UpdateIsArkuiComponent(false);
    SecurityComponentModelNG::SetBackgroundColor(frameNode.rawPtr_, valueOpt);
    ASSERT_FALSE(SecurityComponentModelNG::IsArkuiComponent(frameNode.rawPtr_));
    ASSERT_TRUE(SecurityComponentModelNG::IsBelowThreshold(valueOpt.value()));

    // IsInReleaseList = false, IsArkuiComponent = false, IsBelowThreshold = false
    valueOpt = Color::BLACK;
    SecurityComponentModelNG::SetBackgroundColor(frameNode.rawPtr_, valueOpt);
    ASSERT_FALSE(SecurityComponentModelNG::IsArkuiComponent(frameNode.rawPtr_));
    ASSERT_FALSE(SecurityComponentModelNG::IsBelowThreshold(valueOpt.value()));

    // IsInReleaseList = false, IsArkuiComponent = true, IsBelowThreshold = false
    prop->UpdateIsArkuiComponent(true);
    SecurityComponentModelNG::SetBackgroundColor(frameNode.rawPtr_, valueOpt);
    ASSERT_TRUE(SecurityComponentModelNG::IsArkuiComponent(frameNode.rawPtr_));
    ASSERT_FALSE(SecurityComponentModelNG::IsBelowThreshold(valueOpt.value()));

    // IsInReleaseList = true, IsArkuiComponent = true, IsBelowThreshold = true
    valueOpt = Color(0x0C000000);
    SecurityComponentModelNG::SetBackgroundColor(frameNode.rawPtr_, valueOpt);
    ASSERT_TRUE(SecurityComponentModelNG::IsArkuiComponent(frameNode.rawPtr_));
    ASSERT_TRUE(SecurityComponentModelNG::IsBelowThreshold(valueOpt.value()));
}

/**
 * @tc.name: SetBackgroundBorderWidth001
 * @tc.desc: Test security component SetBackgroundBorderWidth
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SetBackgroundBorderWidth001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
    static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);

    // IsBackgroundVisible = false
    auto prop = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    prop->UpdateBackgroundType(-1);
    std::optional<Dimension> value = std::nullopt;
    SecurityComponentModelNG::SetBackgroundBorderWidth(frameNode.rawPtr_, value);

    // IsBackgroundVisible = true
    prop->UpdateBackgroundType(static_cast<int32_t>(ButtonType::CAPSULE));
    SecurityComponentModelNG::SetBackgroundBorderWidth(frameNode.rawPtr_, value);
    ASSERT_FALSE(value);

    value = Dimension(15.0);
    SecurityComponentModelNG::SetBackgroundBorderWidth(frameNode.rawPtr_, value);
    ASSERT_TRUE(value);
}

/**
 * @tc.name: SetBackgroundBorderColor001
 * @tc.desc: Test security component SetBackgroundBorderColor
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SetBackgroundBorderColor001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
    static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);

    // IsBackgroundVisible = false
    auto prop = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    prop->UpdateBackgroundType(-1);
    std::optional<Color> value = std::nullopt;
    SecurityComponentModelNG::SetBackgroundBorderColor(frameNode.rawPtr_, value);

    // IsBackgroundVisible = true
    prop->UpdateBackgroundType(static_cast<int32_t>(ButtonType::CAPSULE));
    SecurityComponentModelNG::SetBackgroundBorderColor(frameNode.rawPtr_, value);
    ASSERT_FALSE(value);

    value = Color::BLUE;
    SecurityComponentModelNG::SetBackgroundBorderColor(frameNode.rawPtr_, value);
    ASSERT_TRUE(value);
}

/**
 * @tc.name: SetBackgroundBorderStyle001
 * @tc.desc: Test security component SetBackgroundBorderStyle
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SetBackgroundBorderStyle001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
    static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);

    // IsBackgroundVisible = false
    auto prop = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    prop->UpdateBackgroundType(-1);
    std::optional<BorderStyle> value = BorderStyle::DOTTED;
    SecurityComponentModelNG::SetBackgroundBorderStyle(frameNode.rawPtr_, value);

    // IsBackgroundVisible = true
    prop->UpdateBackgroundType(static_cast<int32_t>(ButtonType::CAPSULE));
    SecurityComponentModelNG::SetBackgroundBorderStyle(frameNode.rawPtr_, value);
    ASSERT_TRUE(value);
}

/**
 * @tc.name: SetBackgroundBorderRadius001
 * @tc.desc: Test security component SetBackgroundBorderRadius
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SetBackgroundBorderRadius001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
    static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);

    // IsBackgroundVisible = false
    auto prop = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    prop->UpdateBackgroundType(-1);
    std::optional<Dimension> value = std::nullopt;
    SecurityComponentModelNG::SetBackgroundBorderRadius(frameNode.rawPtr_, value);

    // IsBackgroundVisible = true
    prop->UpdateBackgroundType(static_cast<int32_t>(ButtonType::CAPSULE));
    SecurityComponentModelNG::SetBackgroundBorderRadius(frameNode.rawPtr_, value);
    ASSERT_FALSE(value);

    value = Dimension(15.0);
    SecurityComponentModelNG::SetBackgroundBorderRadius(frameNode.rawPtr_, value);
    ASSERT_TRUE(value);
}

/**
 * @tc.name: SetBackgroundPadding001
 * @tc.desc: Test security component SetBackgroundPadding
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SetBackgroundPadding001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
    static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);

    std::optional<Dimension> left = std::nullopt;
    std::optional<Dimension> right = std::nullopt;
    std::optional<Dimension> top = std::nullopt;
    std::optional<Dimension> bottom = std::nullopt;

    // IsBackgroundVisible = false
    auto prop = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    prop->UpdateBackgroundType(-1);
    SecurityComponentModelNG::SetBackgroundPadding(frameNode.rawPtr_, left, right, top, bottom);

    // IsBackgroundVisible = true
    prop->UpdateBackgroundType(static_cast<int32_t>(ButtonType::CAPSULE));
    SecurityComponentModelNG::SetBackgroundPadding(frameNode.rawPtr_, left, right, top, bottom);

    left = Dimension(15.0);
    SecurityComponentModelNG::SetBackgroundPadding(frameNode.rawPtr_, left, right, top, bottom);
    ASSERT_TRUE(left.has_value());

    right = Dimension(16.0);
    SecurityComponentModelNG::SetBackgroundPadding(frameNode.rawPtr_, left, right, top, bottom);
    ASSERT_TRUE(right.has_value());

    top = Dimension(15.1);
    SecurityComponentModelNG::SetBackgroundPadding(frameNode.rawPtr_, left, right, top, bottom);
    ASSERT_TRUE(top.has_value());

    bottom = Dimension(15.2);
    SecurityComponentModelNG::SetBackgroundPadding(frameNode.rawPtr_, left, right, top, bottom);
    ASSERT_TRUE(bottom.has_value());
}

/**
 * @tc.name: SetTextIconSpace001
 * @tc.desc: Test security component SetTextIconSpace
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SetTextIconSpace001, TestSize.Level0)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
    static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);

    std::optional<Dimension> value = std::nullopt;
    SecurityComponentModelNG::SetTextIconSpace(frameNode.rawPtr_, value);
    ASSERT_FALSE(value);

    value = Dimension(15.2);
    SecurityComponentModelNG::SetTextIconSpace(frameNode.rawPtr_, value);
    ASSERT_TRUE(value);
}

/**
 * @tc.name: SetTextIconSpace002
 * @tc.desc: Test security component SetTextIconSpace
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SetTextIconSpace002, TestSize.Level0)
{
    auto frameNode = FrameNode::CreateFrameNode(
    V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());

    std::optional<Dimension> value = std::nullopt;
    SecurityComponentModelNG::SetTextIconSpace(frameNode.rawPtr_, value);
    ASSERT_FALSE(value);
}
} // namespace OHOS::Ace::NG
