/*
 * Copyright (c) 2023 iSoftStone Information Technology (Group) Co.,Ltd.
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
#define protected public
#define private public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components/common/properties/decoration.h"
#include "core/components/popup/popup_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/base/view_stack_model_ng.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigator/navigator_model_ng.h"
#include "core/components_ng/pattern/navrouter/navrouter_model_ng.h"
#include "core/components_ng/pattern/picker/datepicker_model_ng.h"
#include "core/components_ng/pattern/stepper/stepper_item_model_ng.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components_ng/property/property.h"
#include "core/interfaces/native/node/node_api.h"
#include "core/pipeline/base/element_register.h"
#include "frameworks/core/components/common/layout/position_param.h"
#include "frameworks/core/components_ng/pattern/panel/sliding_panel_model_ng.h"
#include "frameworks/core/pipeline/base/element.h"

#undef private
#undef protected
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const Dimension WIDTH { 50.0, DimensionUnit::PX };
const Dimension HEIGHT { 100.0, DimensionUnit::PX };
const Dimension MIN_WIDTH { 10.0, DimensionUnit::PX };
const Dimension MIN_HEIGHT { 20.0, DimensionUnit::PX };
const Dimension RADIUS { 10.0, DimensionUnit::PX };
const Dimension LEFT { 10.0, DimensionUnit::PX };
const Dimension TOP { 20.0, DimensionUnit::PX };
const Dimension RIGHT { 10.0, DimensionUnit::PX };
const Dimension BOTTOM { 20.0, DimensionUnit::PX };
const Dimension VALUE { -50.0, DimensionUnit::PX };
const Dimension ZERO { 0.0, DimensionUnit::PX };
const BiasPair biasPair(0.5f, 0.5f);
const InvertVariant invert = 0.0f;
const OffsetF OFFSETF { 1.0, 1.0 };
const Offset OFFSET { 2.0, 2.0 };
const float RATIO = 1.0f;
const double OPACITYS = 10;
const int32_t TEN = 10;
const int32_t FOUF = 4;
const int32_t INDEX = 1;
const Color BLUE = Color(0xff0000ff);
const SafeAreaExpandOpts safeAreaExpandOpts = SafeAreaExpandOpts();
const std::vector<ObscuredReasons> reasonsVector = { ObscuredReasons::PLACEHOLDER };

const BackgroundImageSize BACKGROUNDSIZE { BackgroundImageSizeType::AUTO, 1.0 };
const BackgroundImagePosition BACKGROUNDPOSITION { BackgroundImagePositionType::PERCENT, -1.0,
    BackgroundImagePositionType::PERCENT, 0.0 };

constexpr char TAG_ROOT[] = "root";
constexpr char TAG_CHILD[] = "child";
const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
const uint32_t REGISTER_ID = 1 << 20;
const auto FRAME_NODE_REGISTER = FrameNode::CreateFrameNode(TAG_ROOT, REGISTER_ID, MOCK_PATTERN_ROOT, false);

std::string srcimages = "common/images/mmm.jpg";
const std::string VALUE_EMPTY = "";
const std::string VALUE_X = "X";
const std::string VALUE_CX = "CX";
const std::string VALUE_TAB = "TAB";
const std::string VALUE_DPAD_UP = "DPAD_UP";
ViewAbstractModelNG viewAbstractModelNG;
auto callback = []() { srcimages = "test"; };
int32_t flag = 0;
const ImageSourceInfo imageSourceInfo = ImageSourceInfo("common/images/mmm.jpg", "abstract", "abstract");
}; // namespace
class ViewAbstractTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
        MockContainer::SetUp();
        MockContainer::Current()->pipelineContext_ = PipelineBase::GetCurrentContext();
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        PipelineBase::GetCurrentContext()->SetThemeManager(themeManager);
        PipelineBase::GetCurrentContext()->SetEventManager(AceType::MakeRefPtr<EventManager>());
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<PopupTheme>()));
    }
    static void TearDownTestSuite()
    {
        MockContainer::Current()->pipelineContext_ = nullptr;
        MockPipelineContext::TearDown();
    }

    void SetUp() override
    {
        auto* stack = ViewStackProcessor::GetInstance();
        auto nodeId = stack->ClaimNodeId();
        auto frameNode =
            FrameNode::GetOrCreateFrameNode("components", nodeId, []() { return AceType::MakeRefPtr<Pattern>(); });
        stack->Push(frameNode);
    }
    void TearDown() override {}
};

/**
 * @tc.name: ViewAbstractTest001
 * @tc.desc: SetWidth、SetHeight、SetMinWidth、SetMinHeight、SetMaxWidth、SetMaxHeight、ClearWidthOrHeight
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Using static methods to set component properties
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    ViewAbstract::SetWidth(NG::CalcLength(WIDTH));
    ViewAbstract::SetHeight(NG::CalcLength(HEIGHT));
    ViewAbstract::SetMinWidth(NG::CalcLength(MIN_WIDTH));
    ViewAbstract::SetMinHeight(NG::CalcLength(MIN_HEIGHT));
    ViewAbstract::SetMaxWidth(NG::CalcLength(MIN_WIDTH));
    ViewAbstract::SetMaxHeight(NG::CalcLength(MIN_HEIGHT));
    ViewAbstract::ResetAspectRatio();
    ViewAbstract::SetDrawModifier(nullptr);

    /**
     * @tc.expected: Successfully set various properties of the top node on the stack
     */
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->selfIdealSize->Width(), NG::CalcLength(WIDTH));
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->selfIdealSize->Height(), NG::CalcLength(HEIGHT));
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->minSize->Width(), NG::CalcLength(MIN_WIDTH));
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->minSize->Height(), NG::CalcLength(MIN_HEIGHT));
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->maxSize->Width(), NG::CalcLength(MIN_WIDTH));
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->maxSize->Height(), NG::CalcLength(MIN_HEIGHT));

    /**
     * @tc.steps: step2.Static methods set properties for other nodes
     */
    auto newNode = FrameNode::GetOrCreateFrameNode("newframenode", 10, []() { return AceType::MakeRefPtr<Pattern>(); });
    ViewAbstract::SetWidth(AceType::RawPtr(newNode), NG::CalcLength(WIDTH));
    ViewAbstract::SetHeight(AceType::RawPtr(newNode), NG::CalcLength(HEIGHT));
    ViewAbstract::SetMinWidth(AceType::RawPtr(newNode), NG::CalcLength(MIN_WIDTH));
    ViewAbstract::SetMinHeight(AceType::RawPtr(newNode), NG::CalcLength(MIN_HEIGHT));
    ViewAbstract::SetMaxWidth(AceType::RawPtr(newNode), NG::CalcLength(MIN_WIDTH));
    ViewAbstract::SetMaxHeight(AceType::RawPtr(newNode), NG::CalcLength(MIN_HEIGHT));
    auto newProperty = frameNode->GetLayoutProperty();

    /**
     * @tc.expected: Successfully set various attributes of the new node
     */
    EXPECT_EQ(newProperty->calcLayoutConstraint_->selfIdealSize->Width(), NG::CalcLength(WIDTH));
    EXPECT_EQ(newProperty->calcLayoutConstraint_->selfIdealSize->Height(), NG::CalcLength(HEIGHT));
    EXPECT_EQ(newProperty->calcLayoutConstraint_->minSize->Width(), NG::CalcLength(MIN_WIDTH));
    EXPECT_EQ(newProperty->calcLayoutConstraint_->minSize->Height(), NG::CalcLength(MIN_HEIGHT));
    EXPECT_EQ(newProperty->calcLayoutConstraint_->maxSize->Width(), NG::CalcLength(MIN_WIDTH));
    EXPECT_EQ(newProperty->calcLayoutConstraint_->maxSize->Height(), NG::CalcLength(MIN_HEIGHT));

    ViewAbstract::ClearWidthOrHeight(true);
    ViewAbstract::ClearWidthOrHeight(AceType::RawPtr(newNode), true);
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->selfIdealSize->Width(), std::nullopt);
    EXPECT_EQ(newProperty->calcLayoutConstraint_->selfIdealSize->Width(), std::nullopt);
}

/**
 * @tc.name: ViewAbstractTest002
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1.push FrameNode is not null, related function is called.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    ViewAbstract::SetWidth(NG::CalcLength(WIDTH));
    ViewAbstract::SetHeight(NG::CalcLength(HEIGHT));
    ViewAbstract::SetMinWidth(NG::CalcLength(MIN_WIDTH));
    ViewAbstract::SetMinHeight(NG::CalcLength(MIN_HEIGHT));
    ViewAbstract::SetMaxWidth(NG::CalcLength(MIN_WIDTH));
    ViewAbstract::SetMaxHeight(NG::CalcLength(MIN_HEIGHT));
    ViewAbstract::ResetAspectRatio();
    ViewAbstract::ClearWidthOrHeight(true);

    /**
     * @tc.expected: Return expected results..
     */
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest003
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1.The FrameNode is null, related function is called.
     */
    ViewAbstract::SetAspectRatio(RATIO);
    ViewAbstract::SetBackgroundColor(BLUE);
    ViewAbstract::SetBackgroundColor(nullptr, BLUE);
    ViewAbstract::SetBackgroundImage(imageSourceInfo);
    ViewAbstract::SetBackgroundImage(nullptr, imageSourceInfo);
    ViewAbstract::SetBackgroundImageSize(BACKGROUNDSIZE);
    ViewAbstract::SetBackgroundImageSize(nullptr, BACKGROUNDSIZE);
    ViewAbstract::SetBackgroundImagePosition(BACKGROUNDPOSITION);
    ViewAbstract::SetBackgroundImagePosition(nullptr, BACKGROUNDPOSITION);
    ViewAbstract::SetPixelRound(0);
    ChainInfo chainInfo;
    chainInfo.direction = LineDirection::HORIZONTAL;
    chainInfo.style = ChainStyle::SPREAD;
    ViewAbstract::SetChainStyle(chainInfo);
    ViewAbstract::SetChainStyle(AceType::RawPtr(FRAME_NODE_REGISTER), chainInfo);
    ViewAbstract::SetLayoutWeight(TEN);
    ViewAbstract::SetLayoutWeight(AceType::RawPtr(FRAME_NODE_REGISTER), TEN);
    ViewAbstract::SetBias(biasPair);
    ViewAbstract::SetOuterBorderRadius(ZERO);
    ViewAbstract::SetOuterBorderRadius(nullptr, ZERO);
    NG::BorderRadiusProperty borderRadius;
    ViewAbstract::SetOuterBorderRadius(borderRadius);
    ViewAbstract::SetOuterBorderRadius(nullptr, borderRadius);
    ViewAbstract::SetOuterBorderColor(BLUE);
    ViewAbstract::SetOuterBorderColor(nullptr, BLUE);
    NG::BorderColorProperty borderColor;
    ViewAbstract::SetOuterBorderColor(borderColor);
    ViewAbstract::SetOuterBorderColor(nullptr, borderColor);
    ViewAbstract::SetOuterBorderWidth(ZERO);
    ViewAbstract::SetOuterBorderWidth(nullptr, ZERO);
    NG::BorderWidthProperty borderWidth;
    ViewAbstract::SetOuterBorderWidth(borderWidth);
    ViewAbstract::SetOuterBorderWidth(nullptr, borderWidth);
    auto borderStyle = static_cast<BorderStyle>(INDEX);
    ViewAbstract::SetOuterBorderStyle(borderStyle);
    ViewAbstract::SetOuterBorderStyle(nullptr, borderStyle);
    NG::BorderStyleProperty borderStyleProperty;
    ViewAbstract::SetOuterBorderStyle(borderStyleProperty);
    ViewAbstract::SetOuterBorderStyle(nullptr, borderStyleProperty);
    BlendMode blendMode = BlendMode::NONE;
    ViewAbstract::SetBlendMode(blendMode);
    ViewAbstract::SetBlendMode(AceType::RawPtr(FRAME_NODE_REGISTER), blendMode);
    BlendApplyType blendApplyType = BlendApplyType::FAST;
    ViewAbstract::SetBlendApplyType(blendApplyType);
    ViewAbstract::SetBlendApplyType(AceType::RawPtr(FRAME_NODE_REGISTER), blendApplyType);

    BlurStyleOption blurStyleOption;
    blurStyleOption.blurStyle = BlurStyle::NO_MATERIAL;
    blurStyleOption.colorMode = ThemeColorMode::SYSTEM;
    blurStyleOption.adaptiveColor = AdaptiveColor::DEFAULT;
    ViewAbstract::SetBackgroundBlurStyle(blurStyleOption);
    ViewAbstract::SetBackgroundBlurStyle(AceType::RawPtr(FRAME_NODE_REGISTER), blurStyleOption);
    CalcDimension dimensionRadius(0.0);
    ViewAbstract::SetLightPosition(dimensionRadius, dimensionRadius, dimensionRadius);
    ViewAbstract::SetLightIntensity(RATIO);
    ViewAbstract::SetIlluminatedBorderWidth(ZERO);
    ViewAbstract::SetBloom(RATIO);
    std::map<AlignDirection, AlignRule> alignRules;
    ViewAbstract::SetAlignRules(alignRules);
    ViewAbstract::SetAlignRules(AceType::RawPtr(FRAME_NODE_REGISTER), alignRules);
    auto repeat = static_cast<ImageRepeat>(INDEX);
    ViewAbstract::SetBackgroundImageRepeat(repeat);
    ViewAbstract::SetBackgroundImageRepeat(nullptr, repeat);
    auto direction = static_cast<TextDirection>(INDEX);
    ViewAbstract::SetLayoutDirection(direction);
    ViewAbstract::SetLayoutDirection(AceType::RawPtr(FRAME_NODE_REGISTER), direction);
    ViewAbstract::GetAlignRules(AceType::RawPtr(FRAME_NODE_REGISTER));

    /**
     * @tc.expected: Return expected results..
     */
    EXPECT_NE(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractTest004
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1.push FrameNode is not null, related function is called.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    ViewAbstract::SetAspectRatio(RATIO);
    ViewAbstract::SetBackgroundColor(BLUE);
    ViewAbstract::SetBackgroundColor(nullptr, BLUE);
    ViewAbstract::SetBackgroundImage(imageSourceInfo);
    ViewAbstract::SetBackgroundImage(nullptr, imageSourceInfo);
    ViewAbstract::SetBackgroundImageSize(BACKGROUNDSIZE);
    ViewAbstract::SetBackgroundImageSize(nullptr, BACKGROUNDSIZE);
    ViewAbstract::SetBackgroundImagePosition(BACKGROUNDPOSITION);
    ViewAbstract::SetBackgroundImagePosition(nullptr, BACKGROUNDPOSITION);
    ViewAbstract::SetPixelRound(0);

    ChainInfo chainInfo;
    chainInfo.direction = LineDirection::HORIZONTAL;
    chainInfo.style = ChainStyle::SPREAD;
    ViewAbstract::SetChainStyle(chainInfo);
    ViewAbstract::SetChainStyle(AceType::RawPtr(FRAME_NODE_REGISTER), chainInfo);
    ViewAbstract::SetBias(biasPair);
    ViewAbstract::SetOuterBorderRadius(ZERO);
    ViewAbstract::SetOuterBorderRadius(nullptr, ZERO);
    NG::BorderRadiusProperty borderRadius;
    ViewAbstract::SetOuterBorderRadius(borderRadius);
    ViewAbstract::SetOuterBorderRadius(nullptr, borderRadius);
    ViewAbstract::SetOuterBorderColor(BLUE);
    ViewAbstract::SetOuterBorderColor(nullptr, BLUE);
    NG::BorderColorProperty borderColor;
    ViewAbstract::SetOuterBorderColor(borderColor);
    ViewAbstract::SetOuterBorderColor(nullptr, borderColor);
    ViewAbstract::SetOuterBorderWidth(ZERO);
    ViewAbstract::SetOuterBorderWidth(nullptr, ZERO);
    NG::BorderWidthProperty borderWidth;
    ViewAbstract::SetOuterBorderWidth(borderWidth);
    ViewAbstract::SetOuterBorderWidth(nullptr, borderWidth);
    auto borderStyle = static_cast<BorderStyle>(INDEX);
    ViewAbstract::SetOuterBorderStyle(borderStyle);
    ViewAbstract::SetOuterBorderStyle(nullptr, borderStyle);
    NG::BorderStyleProperty borderStyleProperty;
    ViewAbstract::SetOuterBorderStyle(borderStyleProperty);
    ViewAbstract::SetOuterBorderStyle(nullptr, borderStyleProperty);
    ViewAbstract::SetLayoutWeight(TEN);
    BlendMode blendMode = BlendMode::NONE;
    ViewAbstract::SetBlendMode(blendMode);
    BlendApplyType blendApplyType = BlendApplyType::FAST;
    ViewAbstract::SetBlendApplyType(blendApplyType);

    BlurStyleOption blurStyleOption;
    blurStyleOption.blurStyle = BlurStyle::NO_MATERIAL;
    blurStyleOption.colorMode = ThemeColorMode::SYSTEM;
    blurStyleOption.adaptiveColor = AdaptiveColor::DEFAULT;
    ViewAbstract::SetBackgroundBlurStyle(blurStyleOption);

    std::map<AlignDirection, AlignRule> alignRules;
    ViewAbstract::SetAlignRules(alignRules);
    auto repeat = static_cast<ImageRepeat>(INDEX);
    ViewAbstract::SetBackgroundImageRepeat(repeat);
    ViewAbstract::SetBackgroundImageRepeat(nullptr, repeat);
    auto direction = static_cast<TextDirection>(INDEX);
    ViewAbstract::SetLayoutDirection(direction);
    CalcDimension dimensionRadius(0.0);
    ViewAbstract::SetLightPosition(dimensionRadius, dimensionRadius, dimensionRadius);
    ViewAbstract::SetLightIntensity(RATIO);
    ViewAbstract::SetIlluminatedBorderWidth(ZERO);
    ViewAbstract::SetBloom(RATIO);

    /**
     * @tc.expected: Return expected results.
     */
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest005
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1.The FrameNode is null, related function is called.
     */
    auto alignSelf = static_cast<FlexAlign>(INDEX);
    ViewAbstract::SetAlignSelf(alignSelf);
    ViewAbstract::SetFlexShrink(RATIO);
    ViewAbstract::SetFlexGrow(RATIO);
    ViewAbstract::SetFlexBasis(WIDTH);
    ViewAbstract::SetDisplayIndex(INDEX);

    ViewAbstract::SetPadding(NG::CalcLength(WIDTH));
    ViewAbstract::SetMargin(NG::CalcLength(WIDTH));
    ViewAbstract::SetBorderRadius(WIDTH);
    ViewAbstract::SetBorderColor(BLUE);
    ViewAbstract::SetBorderWidth(WIDTH);
    auto borderStyle = static_cast<BorderStyle>(INDEX);
    ViewAbstract::SetBorderStyle(borderStyle);
    ViewAbstract::SetBorderStyle(nullptr, borderStyle);
    ViewAbstract::SetAutoEventParam(VALUE_X);

    /**
     * @tc.expected: Return expected results..
     */
    EXPECT_NE(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractTest006
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1.push FrameNode is not null, related function is called.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    auto alignSelf = static_cast<FlexAlign>(INDEX);
    ViewAbstract::SetAlignSelf(alignSelf);
    ViewAbstract::SetFlexShrink(RATIO);
    ViewAbstract::SetFlexShrink(AceType::RawPtr(FRAME_NODE_REGISTER), RATIO);
    ViewAbstract::SetFlexGrow(RATIO);
    ViewAbstract::SetFlexGrow(AceType::RawPtr(FRAME_NODE_REGISTER), RATIO);
    ViewAbstract::SetFlexBasis(WIDTH);
    ViewAbstract::SetDisplayIndex(INDEX);

    ViewAbstract::SetPadding(NG::CalcLength(WIDTH));
    ViewAbstract::SetMargin(NG::CalcLength(WIDTH));
    ViewAbstract::SetBorderRadius(WIDTH);
    ViewAbstract::SetBorderColor(BLUE);
    ViewAbstract::SetBorderWidth(WIDTH);
    auto borderStyle = static_cast<BorderStyle>(INDEX);
    ViewAbstract::SetBorderStyle(borderStyle);
    ViewAbstract::SetBorderStyle(nullptr, borderStyle);

    /**
     * @tc.expected: Return expected results.
     */
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest007
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1.The FrameNode is null, related function is called.
     */
    NG::PaddingProperty paddings;
    ViewAbstract::SetPadding(paddings);

    NG::MarginProperty margins;
    ViewAbstract::SetMargin(margins);

    NG::BorderRadiusProperty borderRadius;
    ViewAbstract::SetBorderRadius(borderRadius);
    ViewAbstract::SetBorderRadius(nullptr, borderRadius);

    NG::BorderColorProperty borderColors;
    ViewAbstract::SetBorderColor(borderColors);

    NG::BorderWidthProperty borderWidth;
    ViewAbstract::SetBorderWidth(borderWidth);
    ViewAbstract::SetBorderWidth(nullptr, borderWidth);

    NG::BorderStyleProperty borderStyles;
    ViewAbstract::SetBorderStyle(borderStyles);
    ViewAbstract::SetBorderStyle(nullptr, borderStyles);

    /**
     * @tc.expected: Return expected results..
     */
    EXPECT_NE(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractTest008
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1.push FrameNode is not null, related function is called.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    NG::PaddingProperty paddings;
    ViewAbstract::SetPadding(paddings);

    NG::MarginProperty margins;
    ViewAbstract::SetMargin(margins);

    NG::BorderRadiusProperty borderRadius;
    ViewAbstract::SetBorderRadius(borderRadius);

    NG::BorderColorProperty borderColors;
    ViewAbstract::SetBorderColor(borderColors);
    ViewAbstract::SetBorderColor(nullptr, borderColors);

    NG::BorderWidthProperty borderWidth;
    ViewAbstract::SetBorderWidth(borderWidth);

    NG::BorderStyleProperty borderStyles;
    ViewAbstract::SetBorderStyle(borderStyles);
    ViewAbstract::SetBorderStyle(nullptr, borderStyles);

    /**
     * @tc.expected: Return expected results.
     */
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest009
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1.The FrameNode is null, related function is called.
     */
    GestureEventFunc tapEventFunc;
    ViewAbstract::SetOnClick(std::move(tapEventFunc));
    ViewAbstract::SetOnClick(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(tapEventFunc));
    TouchEventFunc touchEventFunc;
    ViewAbstract::SetOnTouch(std::move(touchEventFunc));
    ViewAbstract::SetOnTouch(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(touchEventFunc));
    OnMouseEventFunc onMouseEventFunc;
    ViewAbstract::SetOnMouse(std::move(onMouseEventFunc));
    OnHoverFunc onHoverEventFunc;
    ViewAbstract::SetOnHover(std::move(onHoverEventFunc));
    ViewAbstract::SetJSFrameNodeOnHover(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(onHoverEventFunc));
    ViewAbstract::ClearJSFrameNodeOnHover(AceType::RawPtr(FRAME_NODE_REGISTER));
    OnKeyCallbackFunc onKeyCallback;
    ViewAbstract::SetOnKeyEvent(std::move(onKeyCallback));
    DragPreviewOption dragPreviewOption;
    ViewAbstract::SetDragPreviewOptions(dragPreviewOption);
    ViewAbstract::SetDragPreviewOptions(AceType::RawPtr(FRAME_NODE_REGISTER), dragPreviewOption);
    NG::DragDropInfo info;
    ViewAbstract::SetDragPreview(info);

    auto hoverEffect = static_cast<HoverEffectType>(INDEX);
    ViewAbstract::SetHoverEffect(hoverEffect);
    ViewAbstract::SetHoverEffect(AceType::RawPtr(FRAME_NODE_REGISTER), hoverEffect);

    ViewAbstract::SetFocusable(false);
    ViewAbstract::SetFocusable(AceType::RawPtr(FRAME_NODE_REGISTER), false);
    ViewAbstract::SetEnabled(false);
    ViewAbstract::SetEnabled(AceType::RawPtr(FRAME_NODE_REGISTER), false);
    ViewAbstract::SetOnFocus(callback);
    ViewAbstract::SetOnBlur(callback);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_NE(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractTest010
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1.push FrameNode is not null, related function is called.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    GestureEventFunc tapEventFunc;
    ViewAbstract::SetOnClick(std::move(tapEventFunc));
    TouchEventFunc touchEventFunc;
    ViewAbstract::SetOnTouch(std::move(touchEventFunc));
    OnMouseEventFunc onMouseEventFunc;
    ViewAbstract::SetOnMouse(std::move(onMouseEventFunc));
    OnHoverFunc onHoverEventFunc;
    ViewAbstract::SetOnHover(std::move(onHoverEventFunc));
    OnKeyCallbackFunc onKeyCallback;
    ViewAbstract::SetOnKeyEvent(std::move(onKeyCallback));

    auto hoverEffect = static_cast<HoverEffectType>(INDEX);
    ViewAbstract::SetHoverEffect(hoverEffect);

    ViewAbstract::SetFocusable(true);
    ViewAbstract::SetOnFocus(callback);
    ViewAbstract::SetOnBlur(callback);
    ViewAbstract::SetFlexBasis(VALUE);

    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    focusHub->focusable_ = true;
    focusHub->parentFocusable_ = true;
    ViewAbstract::SetVisibility(VisibleType::VISIBLE);
    ViewAbstract::SetEnabled(true);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_FALSE(focusHub->IsFocusableScope());
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest011
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1.The FrameNode is null, related function is called.
     */
    ViewAbstract::SetTabIndex(INDEX);
    ViewAbstract::SetTabIndex(AceType::RawPtr(FRAME_NODE_REGISTER), INDEX);
    ViewAbstract::SetFocusOnTouch(false);
    ViewAbstract::SetFocusOnTouch(AceType::RawPtr(FRAME_NODE_REGISTER), false);
    ViewAbstract::SetDefaultFocus(false);
    ViewAbstract::SetGroupDefaultFocus(false);
    ViewAbstract::SetGroupDefaultFocus(AceType::RawPtr(FRAME_NODE_REGISTER), false);
    ViewAbstract::SetTouchable(false);
    ViewAbstract::SetTouchable(AceType::RawPtr(FRAME_NODE_REGISTER), false);
    ViewAbstract::SetOnAppear(callback);
    ViewAbstract::SetOnAppear(AceType::RawPtr(FRAME_NODE_REGISTER), callback);
    ViewAbstract::SetOnDisappear(callback);
    ViewAbstract::SetOnDisappear(AceType::RawPtr(FRAME_NODE_REGISTER), callback);
    ViewAbstract::GetFocusable(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetDefaultFocus(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetResponseRegion(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetOverlay(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::SetNeedFocus(AceType::RawPtr(FRAME_NODE_REGISTER), false);
    ViewAbstract::GetNeedFocus(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetOpacity(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetBorderWidth(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetLayoutBorderWidth(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetBorderRadius(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetBorderColor(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetBorderStyle(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetZIndex(AceType::RawPtr(FRAME_NODE_REGISTER));

    auto hitTestMode = static_cast<HitTestMode>(INDEX);
    ViewAbstract::SetHitTestMode(hitTestMode);
    ViewAbstract::SetHitTestMode(AceType::RawPtr(FRAME_NODE_REGISTER), hitTestMode);

    std::vector<DimensionRect> responseRegion;
    ViewAbstract::SetResponseRegion(std::move(responseRegion));
    ViewAbstract::SetResponseRegion(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(responseRegion));
    std::function<DragDropInfo(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)> onDragStart;
    ViewAbstract::SetOnDragStart(std::move(onDragStart));
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)> onDragEnter;
    ViewAbstract::SetOnDragEnter(std::move(onDragEnter));
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)> onDragLeave;
    ViewAbstract::SetOnDragLeave(std::move(onDragLeave));
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)> onDragMove;
    ViewAbstract::SetOnDragMove(std::move(onDragMove));
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)> onDrop;
    ViewAbstract::SetOnDrop(std::move(onDrop));
    Alignment alignment;
    ViewAbstract::SetAlign(std::move(alignment));
    ViewAbstract::SetAlign(nullptr, std::move(alignment));

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_NE(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractTest012
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1.push FrameNode is not null, related function is called.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    ViewAbstract::SetTabIndex(INDEX);
    ViewAbstract::SetFocusOnTouch(false);
    ViewAbstract::SetDefaultFocus(false);
    ViewAbstract::SetDefaultFocus(AceType::RawPtr(FRAME_NODE_REGISTER), false);
    ViewAbstract::SetGroupDefaultFocus(false);
    ViewAbstract::SetTouchable(false);
    ViewAbstract::SetOnAppear(callback);
    ViewAbstract::SetOnDisappear(callback);
    auto hitTestMode = static_cast<HitTestMode>(INDEX);
    ViewAbstract::SetHitTestMode(hitTestMode);

    std::vector<DimensionRect> responseRegion;
    ViewAbstract::SetResponseRegion(std::move(responseRegion));
    std::function<DragDropInfo(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)> onDragStart;
    ViewAbstract::SetOnDragStart(std::move(onDragStart));
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)> onDragEnter;
    ViewAbstract::SetOnDragEnter(std::move(onDragEnter));
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)> onDragLeave;
    ViewAbstract::SetOnDragLeave(std::move(onDragLeave));
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)> onDragMove;
    ViewAbstract::SetOnDragMove(std::move(onDragMove));
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)> onDrop;
    ViewAbstract::SetOnDrop(std::move(onDrop));
    Alignment alignment;
    ViewAbstract::SetAlign(std::move(alignment));

    /**
     * @tc.expected: Return expected results.
     */
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest013
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1.The FrameNode is null, related function is called.
     */
    auto visible = static_cast<VisibleType>(INDEX);
    ViewAbstract::SetVisibility(std::move(visible));
    ViewAbstract::SetVisibility(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(visible));
    ViewAbstract::SetGeometryTransition(srcimages);
    ViewAbstract::SetGeometryTransition(AceType::RawPtr(FRAME_NODE_REGISTER), srcimages, false);
    ViewAbstract::SetOpacity(OPACITYS);
    ViewAbstract::SetOpacity(AceType::RawPtr(FRAME_NODE_REGISTER), OPACITYS);
    ViewAbstract::SetZIndex(FOUF);

    OffsetT<Dimension> value = { WIDTH, HEIGHT };
    ViewAbstract::SetPosition(value);
    ViewAbstract::SetPosition(AceType::RawPtr(FRAME_NODE_REGISTER), value);
    ViewAbstract::SetOffset(value);
    ViewAbstract::SetOffset(AceType::RawPtr(FRAME_NODE_REGISTER), value);
    ViewAbstract::MarkAnchor(value);
    ViewAbstract::MarkAnchor(AceType::RawPtr(FRAME_NODE_REGISTER), value);
    VectorF scale(1.0f, 1.0f);
    ViewAbstract::SetScale(scale);
    ViewAbstract::SetScale(AceType::RawPtr(FRAME_NODE_REGISTER), scale);
    DimensionOffset valueOffset = { WIDTH, HEIGHT };
    ViewAbstract::SetPivot(AceType::RawPtr(FRAME_NODE_REGISTER), valueOffset);
    ViewAbstract::GetVisibility(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetClip(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetClipShape(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetTransform(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetHitTestBehavior(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetPosition(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetShadow(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetSweepGradient(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetRadialGradient(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetMask(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetMaskProgress(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetBlendMode(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetDirection(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetAlignSelf(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetFlexGrow(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetFlexShrink(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetFlexBasis(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetMinWidth(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetMaxWidth(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetMinHeight(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetMaxHeight(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetGrayScale(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetInvert(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetSepia(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetContrast(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetForegroundColor(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetScale(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetRotate(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetBrightness(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetSaturate(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetBackgroundImagePosition(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetLinearGradient(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetAlign(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetWidth(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetHeight(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetBackgroundColor(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetBackgroundImageSrc(AceType::RawPtr(FRAME_NODE_REGISTER));
    auto repeat = static_cast<ImageRepeat>(INDEX);
    ViewAbstract::SetBackgroundImageRepeat(AceType::RawPtr(FRAME_NODE_REGISTER), repeat);
    ViewAbstract::GetBackgroundImageRepeat(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetPadding(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetConfigSize(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetEnabled(AceType::RawPtr(FRAME_NODE_REGISTER));

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_NE(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractTest014
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1.push FrameNode is not null, related function is called.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    auto visible = static_cast<VisibleType>(INDEX);
    ViewAbstract::SetVisibility(std::move(visible));
    ViewAbstract::SetGeometryTransition(srcimages);
    ViewAbstract::SetOpacity(OPACITYS);
    ViewAbstract::SetZIndex(FOUF);
    ViewAbstract::SetZIndex(nullptr, FOUF);

    OffsetT<Dimension> value = { WIDTH, HEIGHT };
    ViewAbstract::SetPosition(value);
    ViewAbstract::SetOffset(value);
    ViewAbstract::MarkAnchor(value);
    viewAbstractModelNG.SetScale(-1.0f, -1.0f, 0.0f);
    ViewAbstract::GetMargin(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetTranslate(AceType::RawPtr(FRAME_NODE_REGISTER));
    GestureEventFunc tapEventFunc;
    ViewAbstract::SetJSFrameNodeOnClick(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(tapEventFunc));
    ViewAbstract::ClearJSFrameNodeOnClick(AceType::RawPtr(FRAME_NODE_REGISTER));
    TouchEventFunc touchEventFunc;
    ViewAbstract::SetJSFrameNodeOnTouch(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(touchEventFunc));
    ViewAbstract::ClearJSFrameNodeOnTouch(AceType::RawPtr(FRAME_NODE_REGISTER));
    std::function<void()> buildFunc;
    ViewAbstract::SetJSFrameNodeOnAppear(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(buildFunc));
    ViewAbstract::ClearJSFrameNodeOnAppear(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::SetJSFrameNodeOnDisappear(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(buildFunc));
    ViewAbstract::ClearJSFrameNodeOnDisappear(AceType::RawPtr(FRAME_NODE_REGISTER));
    OnKeyCallbackFunc onKeyCallback = [](KeyEventInfo& info) {};
    ViewAbstract::SetJSFrameNodeOnKeyCallback(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(onKeyCallback));
    ViewAbstract::ClearJSFrameNodeOnKeyCallback(AceType::RawPtr(FRAME_NODE_REGISTER));

    /**
     * @tc.expected: Return expected results.
     */
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest015
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1.The FrameNode is null, related function is called.
     */
    viewAbstractModelNG.SetPivot(WIDTH, HEIGHT, WIDTH);
    NG::TranslateOptions pttions;
    BlurOption blurOption;
    ViewAbstract::SetTranslate(std::move(pttions));
    ViewAbstract::SetTranslate(nullptr, std::move(pttions));
    Matrix4 matrix;
    ViewAbstract::SetTransformMatrix(std::move(matrix));
    ViewAbstract::SetTransformMatrix(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(matrix));
    ViewAbstract::SetBackdropBlur(RADIUS, blurOption);
    ViewAbstract::SetBackdropBlur(nullptr, RADIUS, blurOption);
    ViewAbstract::SetFrontBlur(RADIUS, blurOption);
    ViewAbstract::SetFrontBlur(AceType::RawPtr(FRAME_NODE_REGISTER), RADIUS, blurOption);
    ViewAbstract::SetInspectorId(srcimages);
    ViewAbstract::SetInspectorId(AceType::RawPtr(FRAME_NODE_REGISTER), srcimages);

    Vector5F scale(1.0f, 1.0f, 2.0f, 2.0f, 0.0f);
    ViewAbstract::SetRotate(scale);
    ViewAbstract::SetRotate(nullptr, scale);
    ShadowStyle style { 1 };
    Shadow shadow { RATIO, OFFSET, BLUE, style };
    ViewAbstract::SetBackShadow(shadow);
    ViewAbstract::SetBackShadow(nullptr, shadow);

    NG::Gradient gradient;
    ViewAbstract::SetLinearGradient(std::move(gradient));
    ViewAbstract::SetLinearGradient(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(gradient));
    ViewAbstract::SetSweepGradient(std::move(gradient));
    ViewAbstract::SetSweepGradient(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(gradient));
    ViewAbstract::SetRadialGradient(std::move(gradient));
    ViewAbstract::SetRadialGradient(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(gradient));
    ViewAbstract::SetSystemBarEffect(false);
    ViewAbstract::SetFreeze(false);
    ViewAbstract::SetUseShadowBatching(false);
    ViewAbstract::SetUseShadowBatching(AceType::RawPtr(FRAME_NODE_REGISTER), false);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_NE(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractTest016
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1.push FrameNode is not null, related function is called.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    viewAbstractModelNG.SetPivot(WIDTH, HEIGHT, ZERO);
    NG::TranslateOptions pttions;
    ViewAbstract::SetTranslate(std::move(pttions));
    Matrix4 matrix;
    BlurOption blurOption;
    ViewAbstract::SetTransformMatrix(std::move(matrix));
    ViewAbstract::SetBackdropBlur(RADIUS, blurOption);
    ViewAbstract::SetFrontBlur(RADIUS, blurOption);
    ViewAbstract::SetInspectorId(srcimages);
    ViewAbstract::SetDebugLine(srcimages);

    Vector5F scale(1.0f, 1.0f, 2.0f, 2.0f, 0.0f);
    ViewAbstract::SetRotate(scale);
    ShadowStyle style { 1 };
    Shadow shadow { RATIO, OFFSET, BLUE, style };
    ViewAbstract::SetBackShadow(shadow);
    NG::Gradient gradient;
    ViewAbstract::SetLinearGradient(std::move(gradient));
    ViewAbstract::SetSweepGradient(std::move(gradient));
    ViewAbstract::SetRadialGradient(std::move(gradient));
    ViewAbstract::SetSystemBarEffect(false);
    ViewAbstract::SetFreeze(false);
    ViewAbstract::SetUseShadowBatching(false);
    /**
     * @tc.expected: Return expected results.
     */
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest017
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1.The FrameNode is null, related function is called.
     */
    auto visible = static_cast<GridSizeType>(INDEX);
    ViewAbstract::SetGrid(FOUF, FOUF, std::move(visible));
    ViewAbstract::SetGrid(AceType::RawPtr(FRAME_NODE_REGISTER), FOUF, FOUF, std::move(visible));
    TransitionOptions options;
    ViewAbstract::SetTransition(std::move(options));
    RefPtr<BasicShape> basicShape;
    ViewAbstract::SetClipShape(std::move(basicShape));
    ViewAbstract::SetClipShape(nullptr, std::move(basicShape));
    ViewAbstract::SetMask(std::move(basicShape));
    ViewAbstract::SetClipEdge(false);
    ViewAbstract::SetGrayScale(RADIUS);
    ViewAbstract::SetContrast(RADIUS);
    ViewAbstract::SetSaturate(RADIUS);
    ViewAbstract::SetSaturate(nullptr, RADIUS);
    ViewAbstract::SetSepia(RADIUS);
    ViewAbstract::SetSepia(nullptr, RADIUS);
    ViewAbstract::SetInvert(invert);
    ViewAbstract::SetInvert(nullptr, invert);
    ViewAbstract::SetHueRotate(RATIO);
    ViewAbstract::SetHueRotate(nullptr, RATIO);
    ViewAbstract::SetBrightness(RADIUS);
    ViewAbstract::SetColorBlend(BLUE);
    ViewAbstract::SetBorderImageSource(srcimages);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_NE(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractTest018
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1.push FrameNode is not null, related function is called.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    auto visible = static_cast<GridSizeType>(INDEX);
    ViewAbstract::SetGrid(FOUF, FOUF, std::move(visible));
    TransitionOptions options;
    ViewAbstract::SetTransition(std::move(options));
    RefPtr<BasicShape> basicShape;
    ViewAbstract::SetClipShape(std::move(basicShape));
    ViewAbstract::SetMask(std::move(basicShape));
    ViewAbstract::SetClipEdge(false);
    ViewAbstract::SetClipEdge(nullptr, false);
    ViewAbstract::SetGrayScale(RADIUS);
    ViewAbstract::SetContrast(RADIUS);
    ViewAbstract::SetSaturate(RADIUS);
    ViewAbstract::SetSepia(RADIUS);
    ViewAbstract::SetInvert(invert);
    ViewAbstract::SetHueRotate(RATIO);
    ViewAbstract::SetBrightness(RADIUS);
    ViewAbstract::SetBrightness(nullptr, RADIUS);
    ViewAbstract::SetColorBlend(BLUE);
    ViewAbstract::SetColorBlend(nullptr, BLUE);
    ViewAbstract::SetBorderImageSource(srcimages);

    /**
     * @tc.expected: Return expected results.
     */
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest019
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1.The FrameNode is null, related function is called.
     */
    RefPtr<BorderImage> borderImage;
    ViewAbstract::SetBorderImage(std::move(borderImage));
    ViewAbstract::SetHasBorderImageSlice(true);
    ViewAbstract::SetHasBorderImageWidth(true);
    ViewAbstract::SetHasBorderImageOutset(true);
    ViewAbstract::SetHasBorderImageRepeat(true);
    ViewAbstract::SetHasBorderImageRepeat(nullptr, true);
    Gradient gradient;
    ViewAbstract::SetBorderImageGradient(std::move(gradient));
    ViewAbstract::SetBorderImageGradient(nullptr, std::move(gradient));
    OverlayOptions overlay;
    ViewAbstract::SetOverlay(std::move(overlay));
    ViewAbstract::SetOverlay(nullptr, std::move(overlay));
    MotionPathOption motionPath;
    ViewAbstract::SetMotionPath(std::move(motionPath));
    ViewAbstract::SetMotionPath(nullptr, std::move(motionPath));
    ViewAbstract::SetSharedTransition("", nullptr);
    ViewAbstract::SetSharedTransition(AceType::RawPtr(FRAME_NODE_REGISTER), "", nullptr);
    ViewAbstract::SetSphericalEffect(RATIO);
    ViewAbstract::SetLightUpEffect(RATIO);
    ViewAbstract::SetUseEffect(false);
    ViewAbstract::SetRenderGroup(false);
    ViewAbstract::SetRenderFit(RenderFit::BOTTOM);
    ViewAbstract::UpdateSafeAreaExpandOpts(safeAreaExpandOpts);
    ViewAbstract::UpdateSafeAreaExpandOpts(AceType::RawPtr(FRAME_NODE_REGISTER), safeAreaExpandOpts);
    ViewAbstract::SetObscured(reasonsVector);
    ViewAbstract::SetObscured(AceType::RawPtr(FRAME_NODE_REGISTER), reasonsVector);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_NE(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractTest020
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1.push FrameNode is not null, related function is called.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    RefPtr<BorderImage> borderImage;
    ViewAbstract::SetBorderImage(std::move(borderImage));
    ViewAbstract::SetBorderImage(nullptr, std::move(borderImage));
    ViewAbstract::SetHasBorderImageSlice(true);
    ViewAbstract::SetHasBorderImageWidth(true);
    ViewAbstract::SetHasBorderImageOutset(true);
    ViewAbstract::SetHasBorderImageRepeat(true);
    Gradient gradient;
    ViewAbstract::SetBorderImageGradient(std::move(gradient));
    OverlayOptions overlay;
    ViewAbstract::SetOverlay(std::move(overlay));
    MotionPathOption motionPath;
    ViewAbstract::SetMotionPath(std::move(motionPath));
    std::shared_ptr<SharedTransitionOption> option;
    ViewAbstract::SetSharedTransition(srcimages, std::move(option));
    ViewAbstract::SetSphericalEffect(RATIO);
    ViewAbstract::SetLightUpEffect(RATIO);
    ViewAbstract::SetDraggable(false);
    ViewAbstract::SetDraggable(AceType::RawPtr(FRAME_NODE_REGISTER), false);
    ViewAbstract::SetUseEffect(false);
    ViewAbstract::SetRenderGroup(false);
    ViewAbstract::SetRenderFit(RenderFit::BOTTOM);
    ViewAbstract::UpdateSafeAreaExpandOpts(safeAreaExpandOpts);
    ViewAbstract::SetObscured(reasonsVector);

    /**
     * @tc.expected: Return expected results.
     */
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest021
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1.The FrameNode is null, related function is called.
     */
    PixStretchEffectOption option;
    option.bottom = BOTTOM;
    option.left = LEFT;
    option.right = RIGHT;
    option.top = TOP;
    ViewAbstract::SetPixelStretchEffect(option);
    ViewAbstract::SetPixelStretchEffect(nullptr, option);
    RefPtr<NG::ChainedTransitionEffect> effect;
    ViewAbstract::SetChainedTransition(std::move(effect));
    RefPtr<ProgressMaskProperty> progress;
    ViewAbstract::SetProgressMask(std::move(progress));

    ViewAbstract::SetForegroundColor(BLUE);
    auto strategy = static_cast<ForegroundColorStrategy>(INDEX);
    ViewAbstract::SetForegroundColorStrategy(std::move(strategy));
    auto hoverEffect = static_cast<HoverEffectType>(INDEX);
    ViewAbstract::SetHoverEffectAuto(hoverEffect);
    ViewAbstract::SetDraggable(true);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_NE(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractTest022
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1.push FrameNode is not null, related function is called.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    PixStretchEffectOption option;
    option.bottom = BOTTOM;
    option.left = LEFT;
    option.right = RIGHT;
    option.top = TOP;
    ViewAbstract::SetPixelStretchEffect(option);
    RefPtr<NG::ChainedTransitionEffect> effect;
    ViewAbstract::SetChainedTransition(std::move(effect));
    RefPtr<ProgressMaskProperty> progress;
    ViewAbstract::SetProgressMask(std::move(progress));
    ViewAbstract::SetForegroundColor(BLUE);
    auto strategy = static_cast<ForegroundColorStrategy>(INDEX);
    ViewAbstract::SetForegroundColorStrategy(std::move(strategy));
    ViewAbstract::SetBorderWidth(VALUE);
    ViewAbstract::SetHeight(NG::CalcLength(HEIGHT));
    ViewAbstract::SetWidth(NG::CalcLength(WIDTH));
    auto hoverEffect = static_cast<HoverEffectType>(INDEX);
    ViewAbstract::SetHoverEffectAuto(hoverEffect);
    ViewAbstract::SetDraggable(true);

    /**
     * @tc.expected: Return expected results.
     */
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest023
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1.The FrameNode is null, related function is called.
     */
    std::function<void(const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin)>
        onAreaChanged;
    ViewAbstract::SetOnAreaChanged(std::move(onAreaChanged));
    ViewAbstract::SetOnAreaChanged(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(onAreaChanged));

    std::function<void(const RectF& oldRect, const RectF& rect)> onSizeChanged;
    ViewAbstract::SetOnSizeChanged(std::move(onSizeChanged));
    std::function<void(bool, double)> onVisibleChange;
    const std::vector<double> ratios;
    ViewAbstract::SetOnVisibleChange(std::move(onVisibleChange), ratios);

    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&)> onDragEnd;
    ViewAbstract::SetOnDragEnd(std::move(onDragEnd));
    std::set<std::string> allowDrop;
    ViewAbstract::SetAllowDrop(std::move(allowDrop));
    ViewAbstract::SetAllowDrop(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(allowDrop));
    ViewAbstract::CreateAnimatablePropertyFloat(srcimages, RATIO, nullptr);
    ViewAbstract::UpdateAnimatablePropertyFloat(srcimages, RATIO);
    ViewAbstract::SetRestoreId(TEN);
    ViewAbstract::SetRestoreId(AceType::RawPtr(FRAME_NODE_REGISTER), TEN);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_NE(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractTest024
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step1.push FrameNode is not null, related function is called.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    std::function<void(const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin)>
        onAreaChanged;
    ViewAbstract::SetOnAreaChanged(std::move(onAreaChanged));
    std::function<void(bool, double)> onVisibleChange;
    const std::vector<double> ratios;
    ViewAbstract::SetOnVisibleChange(std::move(onVisibleChange), ratios);
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&)> onDragEnd;
    ViewAbstract::SetOnDragEnd(std::move(onDragEnd));
    std::set<std::string> allowDrop;
    ViewAbstract::SetAllowDrop(std::move(allowDrop));
    ViewAbstract::CreateAnimatablePropertyFloat(srcimages, RATIO, nullptr);
    ViewAbstract::UpdateAnimatablePropertyFloat(srcimages, RATIO);
    ViewAbstract::SetRestoreId(TEN);

    /**
     * @tc.expected: Return expected results.
     */
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest025
 * @tc.desc: Test the BindPopup of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create some FrameNode and params.
     */
    const RefPtr<FrameNode> customNode = FrameNode::CreateFrameNode("one", 1, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("two", 2, AceType::MakeRefPtr<Pattern>());
    const RefPtr<FrameNode> targetNode2 = FrameNode::CreateFrameNode("three", 3, AceType::MakeRefPtr<Pattern>());
    auto param = AceType::MakeRefPtr<PopupParam>();
    auto param2 = AceType::MakeRefPtr<PopupParam>();

    /**
     * @tc.steps: step2. get popupInfo and change some params.
     */
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto nodeId = targetNode->GetId();
    PopupInfo info = overlayManager->GetPopupInfo(nodeId);
    info.isCurrentOnShow = true;
    info.popupId = 1;
    auto popupNode1 = FrameNode::CreateFrameNode(
        V2::POPUP_ETS_TAG, info.popupId, AceType::MakeRefPtr<BubblePattern>(targetNode->GetId(), targetNode->GetTag()));
    info.popupNode = popupNode1;
    info.target = targetNode2;
    overlayManager->ShowPopup(targetNode->GetId(), info);

    /**
     * @tc.steps: step3. Call BindPopup many times.
     * @tc.expected: popupNode in overlayManager of targetNode not null
     */
    ViewAbstract::BindPopup(param, targetNode, customNode);
    ViewAbstract::BindPopup(param, targetNode, customNode);
    overlayManager->HidePopup(targetNode->GetId(), info);
    auto popupInfo = overlayManager->GetPopupInfo(targetNode->GetId());
    auto popupNode = popupInfo.popupNode;
    ASSERT_NE(popupNode, nullptr);
    popupNode->GetPattern<BubblePattern>()->transitionStatus_ = TransitionStatus::ENTERING;
    ViewAbstract::BindPopup(param, targetNode, customNode);
    param->SetIsShow(false);
    ViewAbstract::BindPopup(param, targetNode, customNode);
    param->SetShowInSubWindow(true);
    ViewAbstract::BindPopup(param, targetNode, customNode);
    EXPECT_NE(overlayManager->GetPopupInfo(targetNode->GetId()).popupNode, nullptr);

    /**
     * @tc.steps: step4. Call BindPopup with param use custom.
     * @tc.expected: popupNode in overlayManager of targetNode not null
     */
    param2->SetUseCustomComponent(true);
    ViewAbstract::BindPopup(param2, targetNode2, customNode);
    ViewAbstract::BindPopup(param2, targetNode2, customNode);
    param2->SetShowInSubWindow(true);
    ViewAbstract::BindPopup(param2, targetNode2, customNode);
    param2->SetIsShow(false);
    ViewAbstract::BindPopup(param2, targetNode2, customNode);
    EXPECT_NE(overlayManager->GetPopupInfo(targetNode->GetId()).popupNode, nullptr);
}

/**
 * @tc.name: ViewAbstractTest026
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    /**
     * @tc.steps: step2. call SetKeyboardShortcut with ctrl + x.
     * @tc.expected: add fail
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_X, std::move(keys), callback);
    ViewAbstract::SetKeyboardShortcut(AceType::RawPtr(FRAME_NODE_REGISTER), VALUE_X, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 0);
    keys.clear();
    /**
     * @tc.steps: step3. call SetKeyboardShortcut with other wrong type.
     * @tc.expected: add fail
     */
    ViewAbstract::SetKeyboardShortcut(VALUE_EMPTY, std::move(keys), callback);
    ViewAbstract::SetKeyboardShortcut(VALUE_CX, std::move(keys), callback);
    ViewAbstract::SetKeyboardShortcut(VALUE_X, std::move(keys), callback);
    ViewAbstract::SetKeyboardShortcut(AceType::RawPtr(FRAME_NODE_REGISTER), VALUE_EMPTY, std::move(keys), callback);
    ViewAbstract::SetKeyboardShortcut(AceType::RawPtr(FRAME_NODE_REGISTER), VALUE_CX, std::move(keys), callback);
    ViewAbstract::SetKeyboardShortcut(AceType::RawPtr(FRAME_NODE_REGISTER), VALUE_X, std::move(keys), callback);

    /**
     * @tc.steps: step4. and shift in keys and recall SetKeyboardShortcut .
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::ALT);
    ViewAbstract::SetKeyboardShortcut(VALUE_CX, std::move(keys), callback);
    ViewAbstract::SetKeyboardShortcut(AceType::RawPtr(FRAME_NODE_REGISTER), VALUE_CX, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step5. make other key and recall SetKeyboardShortcut .
     * @tc.expected: add fail
     */
    keys.push_back(ModifierKey::SHIFT);
    ViewAbstract::SetKeyboardShortcut(VALUE_CX, std::move(keys), callback);
    ViewAbstract::SetKeyboardShortcut(AceType::RawPtr(FRAME_NODE_REGISTER), VALUE_CX, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.push_back(ModifierKey::ALT);
    ViewAbstract::SetKeyboardShortcut(VALUE_CX, std::move(keys), callback);
    ViewAbstract::SetKeyboardShortcut(AceType::RawPtr(FRAME_NODE_REGISTER), VALUE_CX, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
}

/**
 * @tc.name: ViewAbstractTest027
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest027, TestSize.Level1)
{
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    /**
     * @tc.steps: step1. callback ShowMenu with two condition.
     */
    ContainerScope sontainerScope(1);
    /**
     * @tc.steps: step2. callback SetForegroundBlurStyle and ResetFlexShrink.
     */
    BlurStyleOption bgBlurStyle;
    ViewAbstract::SetForegroundBlurStyle(bgBlurStyle);
    ViewAbstract::SetForegroundBlurStyle(AceType::RawPtr(FRAME_NODE_REGISTER), bgBlurStyle);
    ViewAbstract::ResetFlexShrink();
    ViewAbstract::ResetFlexShrink(AceType::RawPtr(FRAME_NODE_REGISTER));
    /**
     * @tc.steps: step3. SetVisualState in ViewStackProcessor and recall the two function.
     * @tc.expected: the blur radius in render context meet expectations.
     */
    ViewStackProcessor::GetInstance()->SetVisualState(VisualState::FOCUSED);
    ViewAbstract::SetForegroundBlurStyle(bgBlurStyle);
    ViewAbstract::SetForegroundBlurStyle(AceType::RawPtr(FRAME_NODE_REGISTER), bgBlurStyle);
    ViewAbstract::ResetFlexShrink();
    ASSERT_NE(FRAME_NODE_ROOT->GetRenderContext(), nullptr);
    EXPECT_FALSE(FRAME_NODE_ROOT->GetRenderContext()->GetFrontBlurRadius().has_value());
}

/**
 * @tc.name: ViewAbstractTest028
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest028, TestSize.Level1)
{
    /**
     * @tc.steps: step1.push FrameNode is not null, callback Pop function.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    ViewAbstract::Pop();

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_FALSE(ViewStackProcessor::GetInstance()->elementsStack_.empty());
    EXPECT_EQ(ViewStackProcessor::GetInstance()->elementsStack_.size(), INDEX);
}

/**
 * @tc.name: ViewAbstractTest029
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest029, TestSize.Level1)
{
    /**
     * @tc.steps: step1.ClearStack.
     */
    auto state = static_cast<VisualState>(INDEX);
    ViewStackProcessor::GetInstance()->SetVisualState(state);
    ViewStackProcessor::GetInstance()->ClearStack();

    /**
     * @tc.steps: step2. related function is called.
     */
    ViewAbstract::SetWidth(NG::CalcLength(WIDTH));
    ViewAbstract::SetHeight(NG::CalcLength(HEIGHT));
    ViewAbstract::SetMinWidth(NG::CalcLength(MIN_WIDTH));
    ViewAbstract::SetMinHeight(NG::CalcLength(MIN_HEIGHT));
    ViewAbstract::SetMaxWidth(NG::CalcLength(MIN_WIDTH));
    ViewAbstract::SetMaxHeight(NG::CalcLength(MIN_HEIGHT));
    ViewAbstract::SetAspectRatio(RATIO);
    ViewAbstract::SetAspectRatio(AceType::RawPtr(FRAME_NODE_REGISTER), RATIO);
    ViewAbstract::SetBackgroundColor(BLUE);
    ViewAbstract::SetBackgroundColor(nullptr, BLUE);
    ViewAbstract::SetBackgroundImage(imageSourceInfo);
    ViewAbstract::SetBackgroundImage(nullptr, imageSourceInfo);
    ViewAbstract::SetBackgroundImageSize(BACKGROUNDSIZE);
    ViewAbstract::SetBackgroundImageSize(nullptr, BACKGROUNDSIZE);
    ViewAbstract::SetBackgroundImagePosition(BACKGROUNDPOSITION);
    ViewAbstract::SetBackgroundImagePosition(nullptr, BACKGROUNDPOSITION);
    ViewAbstract::SetPixelRound(0);
    ChainInfo chainInfo;
    chainInfo.direction = LineDirection::HORIZONTAL;
    chainInfo.style = ChainStyle::SPREAD;
    ViewAbstract::SetChainStyle(chainInfo);
    ViewAbstract::SetChainStyle(AceType::RawPtr(FRAME_NODE_REGISTER), chainInfo);
    ViewAbstract::SetBias(biasPair);
    ViewAbstract::SetOuterBorderRadius(ZERO);
    ViewAbstract::SetOuterBorderRadius(nullptr, ZERO);
    NG::BorderRadiusProperty borderRadius;
    ViewAbstract::SetOuterBorderRadius(borderRadius);
    ViewAbstract::SetOuterBorderRadius(nullptr, borderRadius);
    ViewAbstract::SetOuterBorderColor(BLUE);
    ViewAbstract::SetOuterBorderColor(nullptr, BLUE);
    NG::BorderColorProperty borderColor;
    ViewAbstract::SetOuterBorderColor(borderColor);
    ViewAbstract::SetOuterBorderColor(nullptr, borderColor);
    ViewAbstract::SetOuterBorderWidth(ZERO);
    ViewAbstract::SetOuterBorderWidth(nullptr, ZERO);
    NG::BorderWidthProperty borderWidth;
    ViewAbstract::SetOuterBorderWidth(borderWidth);
    ViewAbstract::SetOuterBorderWidth(nullptr, borderWidth);
    auto borderStyle = static_cast<BorderStyle>(INDEX);
    ViewAbstract::SetOuterBorderStyle(borderStyle);
    ViewAbstract::SetOuterBorderStyle(nullptr, borderStyle);
    NG::BorderStyleProperty borderStyleProperty;
    ViewAbstract::SetOuterBorderStyle(borderStyleProperty);
    ViewAbstract::SetOuterBorderStyle(nullptr, borderStyleProperty);
    ViewAbstract::ResetAspectRatio();
    ViewAbstract::ResetAspectRatio(AceType::RawPtr(FRAME_NODE_REGISTER));

    /**
     * @tc.expected: Return expected results.
     */
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest030
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest030, TestSize.Level1)
{
    /**
     * @tc.steps: step1.ClearStack.
     */
    auto state = static_cast<VisualState>(INDEX);
    ViewStackProcessor::GetInstance()->SetVisualState(state);
    ViewStackProcessor::GetInstance()->ClearStack();

    /**
     * @tc.steps: step2. related function is called.
     */
    MotionPathOption motionPath;
    ViewAbstract::SetMotionPath(std::move(motionPath));
    auto repeat = static_cast<ImageRepeat>(INDEX);
    ViewAbstract::SetBackgroundImageRepeat(repeat);
    GestureJudgeFunc tapEventFunc;
    ViewAbstract::SetOnGestureJudgeBegin(std::move(tapEventFunc));

    BlurStyleOption blurStyleOption;
    blurStyleOption.blurStyle = BlurStyle::NO_MATERIAL;
    blurStyleOption.colorMode = ThemeColorMode::SYSTEM;
    blurStyleOption.adaptiveColor = AdaptiveColor::DEFAULT;
    ViewAbstract::SetBackgroundBlurStyle(blurStyleOption);

    auto direction = static_cast<TextDirection>(INDEX);
    ViewAbstract::SetLayoutDirection(direction);
    std::map<AlignDirection, AlignRule> alignRules;
    ViewAbstract::SetAlignRules(alignRules);
    auto alignSelf = static_cast<FlexAlign>(INDEX);
    ViewAbstract::SetAlignSelf(alignSelf);
    ViewAbstract::SetAlignSelf(AceType::RawPtr(FRAME_NODE_REGISTER), alignSelf);

    /**
     * @tc.expected: Return expected results.
     */
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest031
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest031, TestSize.Level1)
{
    /**
     * @tc.steps: step1.ClearStack.
     */
    auto state = static_cast<VisualState>(INDEX);
    ViewStackProcessor::GetInstance()->SetVisualState(state);
    ViewStackProcessor::GetInstance()->ClearStack();

    /**
     * @tc.steps: step2. related function is called.
     */
    ViewAbstract::SetFlexShrink(RATIO);
    ViewAbstract::SetFlexGrow(RATIO);
    ViewAbstract::SetFlexBasis(WIDTH);
    ViewAbstract::SetFlexBasis(AceType::RawPtr(FRAME_NODE_REGISTER), WIDTH);
    ViewAbstract::SetDisplayIndex(TEN);
    ViewAbstract::SetZIndex(FOUF);

    Alignment alignment;
    ViewAbstract::SetAlign(std::move(alignment));
    auto visible = static_cast<VisibleType>(INDEX);
    ViewAbstract::SetVisibility(std::move(visible));
    ViewAbstract::SetOpacity(OPACITYS);

    /**
     * @tc.expected: Return expected results.
     */
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest032
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest032, TestSize.Level1)
{
    /**
     * @tc.steps: step1.ClearStack.
     */
    auto state = static_cast<VisualState>(INDEX);
    ViewStackProcessor::GetInstance()->SetVisualState(state);
    ViewStackProcessor::GetInstance()->ClearStack();

    /**
     * @tc.steps: step2. related function is called.
     */
    OffsetT<Dimension> values = { WIDTH, HEIGHT };
    ViewAbstract::SetPosition(values);
    ViewAbstract::SetOffset(values);
    ViewAbstract::MarkAnchor(values);

    ViewAbstract::SetPadding(NG::CalcLength(WIDTH));
    ViewAbstract::SetPadding(AceType::RawPtr(FRAME_NODE_REGISTER), NG::CalcLength(WIDTH));
    ViewAbstract::SetMargin(NG::CalcLength(WIDTH));
    ViewAbstract::SetMargin(AceType::RawPtr(FRAME_NODE_REGISTER), NG::CalcLength(WIDTH));
    ViewAbstract::SetBorderRadius(WIDTH);
    ViewAbstract::SetBorderRadius(nullptr, WIDTH);
    ViewAbstract::SetBorderColor(BLUE);
    ViewAbstract::SetBorderColor(nullptr, BLUE);
    ViewAbstract::SetBorderWidth(WIDTH);
    ViewAbstract::SetBorderWidth(nullptr, WIDTH);

    auto borderStyle = static_cast<BorderStyle>(INDEX);
    ViewAbstract::SetBorderStyle(borderStyle);
    ViewAbstract::SetBorderStyle(nullptr, borderStyle);

    /**
     * @tc.expected: Return expected results.
     */
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest033
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest033, TestSize.Level1)
{
    /**
     * @tc.steps: step1.ClearStack.
     */
    auto state = static_cast<VisualState>(INDEX);
    ViewStackProcessor::GetInstance()->SetVisualState(state);
    ViewStackProcessor::GetInstance()->ClearStack();

    /**
     * @tc.steps: step2. related function is called.
     */
    OffsetT<Dimension> values = { WIDTH, HEIGHT };
    ViewAbstract::SetPosition(values);
    ViewAbstract::SetOffset(values);
    ViewAbstract::MarkAnchor(values);

    NG::PaddingProperty paddings;
    ViewAbstract::SetPadding(paddings);
    ViewAbstract::SetPadding(AceType::RawPtr(FRAME_NODE_REGISTER), paddings);

    NG::MarginProperty margins;
    ViewAbstract::SetMargin(margins);
    ViewAbstract::SetMargin(AceType::RawPtr(FRAME_NODE_REGISTER), margins);

    NG::BorderRadiusProperty borderRadius;
    ViewAbstract::SetBorderRadius(borderRadius);

    NG::BorderColorProperty borderColors;
    ViewAbstract::SetBorderColor(borderColors);

    NG::BorderWidthProperty borderWidth;
    ViewAbstract::SetBorderWidth(borderWidth);

    NG::BorderStyleProperty borderStyles;
    ViewAbstract::SetBorderStyle(borderStyles);
    ViewAbstract::SetBorderStyle(nullptr, borderStyles);

    /**
     * @tc.expected: Return expected results.
     */
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest034
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest034, TestSize.Level1)
{
    /**
     * @tc.steps: step1.ClearStack.
     */
    auto state = static_cast<VisualState>(INDEX);
    ViewStackProcessor::GetInstance()->SetVisualState(state);
    ViewStackProcessor::GetInstance()->ClearStack();

    /**
     * @tc.steps: step2. related function is called.
     */
    BlurOption blurOption;
    ViewAbstract::SetBrightness(RADIUS);
    ViewAbstract::SetGrayScale(RADIUS);
    ViewAbstract::SetContrast(RADIUS);
    ViewAbstract::SetContrast(nullptr, RADIUS);
    ViewAbstract::SetSaturate(RADIUS);
    ViewAbstract::SetSepia(RADIUS);
    ViewAbstract::SetInvert(invert);
    ViewAbstract::SetHueRotate(RATIO);
    ViewAbstract::SetColorBlend(BLUE);
    ViewAbstract::SetBackdropBlur(RADIUS, blurOption);
    ViewAbstract::SetFrontBlur(RADIUS, blurOption);
    ViewAbstract::SetClipEdge(false);

    /**
     * @tc.expected: Return expected results.
     */
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest035
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest035, TestSize.Level1)
{
    /**
     * @tc.steps: step1.ClearStack.
     */
    auto state = static_cast<VisualState>(INDEX);
    ViewStackProcessor::GetInstance()->SetVisualState(state);
    ViewStackProcessor::GetInstance()->ClearStack();

    /**
     * @tc.steps: step2. related function is called.
     */
    viewAbstractModelNG.SetScale(1.0f, 1.0f, 0.0f);
    DimensionOffset value = { WIDTH, HEIGHT };
    viewAbstractModelNG.SetPivot(WIDTH, HEIGHT, ZERO);
    NG::TranslateOptions values;
    ViewAbstract::SetTranslate(std::move(values));
    Vector5F scales(1.0f, 1.0f, 2.0f, 2.0f, 0.0f);
    ViewAbstract::SetRotate(scales);
    Matrix4 matrix;
    ViewAbstract::SetTransformMatrix(std::move(matrix));

    ShadowStyle style { 1 };
    Shadow shadow { RATIO, OFFSET, BLUE, style };
    ViewAbstract::SetBackShadow(shadow);
    NG::Gradient gradient;
    ViewAbstract::SetLinearGradient(std::move(gradient));
    ViewAbstract::SetSweepGradient(std::move(gradient));
    ViewAbstract::SetRadialGradient(std::move(gradient));
    TransitionOptions options;
    ViewAbstract::SetTransition(std::move(options));
    ViewAbstract::SetTransition(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(options));
    RefPtr<BasicShape> basicShape;
    ViewAbstract::SetClipShape(std::move(basicShape));
    ViewAbstract::SetMask(std::move(basicShape));
    ViewAbstract::SetMask(nullptr, std::move(basicShape));

    /**
     * @tc.expected: Return expected results.
     */
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest036
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest036, TestSize.Level1)
{
    /**
     * @tc.steps: step1.ClearStack.
     */
    auto state = static_cast<VisualState>(INDEX);
    ViewStackProcessor::GetInstance()->SetVisualState(state);
    ViewStackProcessor::GetInstance()->ClearStack();

    /**
     * @tc.steps: step2. related function is called.
     */
    ViewAbstract::SetBorderImageSource(srcimages);
    ViewAbstract::SetBorderImageSource(nullptr, srcimages);
    ViewAbstract::SetHasBorderImageSlice(false);
    ViewAbstract::SetHasBorderImageSlice(nullptr, false);
    ViewAbstract::SetHasBorderImageWidth(false);
    ViewAbstract::SetHasBorderImageWidth(nullptr, false);
    ViewAbstract::SetHasBorderImageOutset(false);
    ViewAbstract::SetHasBorderImageOutset(nullptr, false);
    ViewAbstract::SetHasBorderImageRepeat(false);
    ViewAbstract::SetSphericalEffect(RATIO);
    ViewAbstract::SetSphericalEffect(nullptr, RATIO);
    ViewAbstract::SetLightUpEffect(RATIO);
    ViewAbstract::SetLightUpEffect(nullptr, RATIO);
    ViewAbstract::SetForegroundColor(BLUE);
    ViewAbstract::SetForegroundColor(AceType::RawPtr(FRAME_NODE_REGISTER), BLUE);
    ViewAbstract::ClearWidthOrHeight(true);
    ViewAbstract::SetUseEffect(false);
    ViewAbstract::SetUseEffect(nullptr, false);
    ViewAbstract::SetRenderGroup(false);
    ViewAbstract::SetRenderGroup(nullptr, false);
    ViewAbstract::SetRenderFit(RenderFit::BOTTOM);
    ViewAbstract::SetRenderFit(nullptr, RenderFit::BOTTOM);
    ViewAbstract::UpdateSafeAreaExpandOpts(safeAreaExpandOpts);
    ViewAbstract::SetObscured(reasonsVector);

    PixStretchEffectOption option;
    option.bottom = BOTTOM;
    option.left = LEFT;
    option.right = RIGHT;
    option.top = TOP;
    ViewAbstract::SetPixelStretchEffect(option);

    /**
     * @tc.expected: Return expected results.
     */
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest037
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest037, TestSize.Level1)
{
    /**
     * @tc.steps: step1.ClearStack.
     */
    auto state = static_cast<VisualState>(INDEX);
    ViewStackProcessor::GetInstance()->SetVisualState(state);
    ViewStackProcessor::GetInstance()->ClearStack();

    /**
     * @tc.steps: step2. related function is called.
     */
    RefPtr<BorderImage> borderImage;
    ViewAbstract::SetBorderImage(std::move(borderImage));
    Gradient gradient;
    ViewAbstract::SetBorderImageGradient(std::move(gradient));
    RefPtr<NG::ChainedTransitionEffect> effect;
    ViewAbstract::SetChainedTransition(std::move(effect));
    ViewAbstract::SetChainedTransition(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(effect));
    RefPtr<ProgressMaskProperty> progress;
    ViewAbstract::SetProgressMask(std::move(progress));
    ViewAbstract::SetProgressMask(nullptr, std::move(progress));
    auto strategy = static_cast<ForegroundColorStrategy>(INDEX);
    ViewAbstract::SetForegroundColorStrategy(std::move(strategy));
    ViewAbstract::SetForegroundColorStrategy(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(strategy));
    OverlayOptions overlay;
    ViewAbstract::SetOverlay(std::move(overlay));

    /**
     * @tc.expected: Return expected results.
     */
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest038
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest038, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    /**
     * @tc.steps: step2. callback SetClickEffectLevel.push FrameNode is not null.
     */
    viewAbstract.SetClickEffectLevel(ClickEffectLevel::LIGHT, 1.0f);
    viewAbstract.SetClickEffectLevel(AceType::RawPtr(FRAME_NODE_REGISTER), ClickEffectLevel::LIGHT, 1.0f);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.expected: step3. Return expected results..
     */
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest039
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest039, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    /**
     * @tc.steps: step2.ClearStack and callback SetScale.
     */
    viewStackProcessor.GetInstance()->ClearStack();
    /**
     * @tc.expected: step2. Return expected results..
     */
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetClickEffectLevel(ClickEffectLevel::LIGHT, 1.0f);
    ViewAbstract::ResetMinSize(true);
    EXPECT_FALSE(result);
    /**
     * @tc.steps: step3. visualState_ is null.
     * @tc.expected: result is true.
     */
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetClickEffectLevel(ClickEffectLevel::LIGHT, 1.0f);
    ViewAbstract::ResetMinSize(true);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ViewAbstractTest040
 * @tc.desc: Test the BindMenu and BindContextMenu of ViewAbstractModelNG
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest040, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and put mainNode, then build some necessary params.
     */
    const RefPtr<FrameNode> mainNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(mainNode);

    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);

    ASSERT_NE(SubwindowManager::GetInstance(), nullptr);
    std::function<void()> flagFunc = []() { flag++; };
    std::vector<NG::OptionParam> params = {};
    std::function<void()> buildFunc;
    MenuParam menuParam;
    std::function<void()> previewBuildFunc = nullptr;
    /**
     * @tc.steps: step2. call Bind and BindContextMenu multiple times with unless parameters
     * @tc.expected: The show or hide method will not call flagFunc.
     */
    viewAbstractModelNG.BindMenu(std::move(params), std::move(buildFunc), menuParam);
    buildFunc = []() {};
    viewAbstractModelNG.BindMenu(std::move(params), std::move(buildFunc), menuParam);
    params.push_back(OptionParam());
    viewAbstractModelNG.BindMenu(std::move(params), std::move(buildFunc), menuParam);
    menuParam.type = MenuType::CONTEXT_MENU;
    viewAbstractModelNG.BindContextMenu(ResponseType::LONG_PRESS, buildFunc, menuParam, previewBuildFunc);
    EXPECT_EQ(flag, 0);
    /**
     * @tc.steps: step3. set appear and disappear and recall BindMenu and BindContextMenu;
     * @tc.expected: The flagFunc call times meet expectations.
     */
    menuParam.onAppear = flagFunc;
    menuParam.onDisappear = flagFunc;
    menuParam.type = MenuType::MENU;
    viewAbstractModelNG.BindMenu(std::move(params), std::move(buildFunc), menuParam);
    menuParam.type = MenuType::CONTEXT_MENU;
    viewAbstractModelNG.BindContextMenu(ResponseType::RIGHT_CLICK, buildFunc, menuParam, previewBuildFunc);
    menuParam.contextMenuRegisterType = ContextMenuRegisterType::CUSTOM_TYPE;
    menuParam.isShow = true;
    viewAbstractModelNG.BindContextMenu(ResponseType::LONG_PRESS, buildFunc, menuParam, previewBuildFunc);
    EXPECT_EQ(flag, 0);
    auto subwindow = SubwindowManager::GetInstance()->GetSubwindow(container);
    EXPECT_EQ(subwindow, nullptr);

    /**
     * @tc.steps: step4. create mouseInfo, set some useless params and call onMouseCallback_;
     * @tc.expected: StopPropagation in mouseInfo is false.
     */
    auto inputHub = mainNode->GetOrCreateInputEventHub();
    ASSERT_NE(inputHub, nullptr);
    MouseInfo mouseInfo;
    mouseInfo.SetButton(MouseButton::LEFT_BUTTON);
    mouseInfo.SetAction(MouseAction::NONE);
    inputHub->showMenu_->onMouseCallback_(mouseInfo);
    mouseInfo.SetButton(MouseButton::RIGHT_BUTTON);
    mouseInfo.SetAction(MouseAction::NONE);
    inputHub->showMenu_->onMouseCallback_(mouseInfo);
    EXPECT_FALSE(mouseInfo.IsStopPropagation());
    /**
     * @tc.steps: step4. create mouseInfo, set right param and call onMouseCallback_;
     * @tc.expected: StopPropagation in mouseInfo is false.
     */
    mouseInfo.SetButton(MouseButton::RIGHT_BUTTON);
    mouseInfo.SetAction(MouseAction::RELEASE);
    inputHub->showMenu_->onMouseCallback_(mouseInfo);
    EXPECT_FALSE(mouseInfo.IsStopPropagation());

    /**
     * @tc.steps: step5. create mouseInfo, set right param and call BindMenuWithCustomNode;
     * @tc.expected: StopPropagation in mouseInfo is true.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    PipelineBase::GetCurrentContext()->SetThemeManager(themeManager);
    PipelineBase::GetCurrentContext()->SetEventManager(AceType::MakeRefPtr<EventManager>());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    const RefPtr<FrameNode> targetNode =
        FrameNode::CreateFrameNode("targetNode", nodeId, AceType::MakeRefPtr<Pattern>(), true);
    std::vector<OptionParam> param;
    ViewAbstract::BindMenuWithItems(std::move(param), targetNode, OFFSETF, menuParam);
    menuParam.type = MenuType::MULTI_MENU;
    ViewAbstract::BindMenuWithCustomNode(mainNode, targetNode, OFFSETF, menuParam);
    EXPECT_FALSE(mouseInfo.IsStopPropagation());
    param.push_back(OptionParam());
    ViewAbstract::BindMenuWithItems(std::move(param), targetNode, OFFSETF, menuParam);
    menuParam.type = MenuType::CONTEXT_MENU;
    ViewAbstract::BindMenuWithCustomNode(mainNode, targetNode, OFFSETF, menuParam);
    EXPECT_FALSE(mouseInfo.IsStopPropagation());
}

/**
 * @tc.name: ViewAbstractTest041
 * @tc.desc: Test the BindMenu and BindContextMenu of ViewAbstractModelNG
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest041, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat frameNode and other creat.
     */
    int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    const RefPtr<FrameNode> frameNode =
        FrameNode::CreateFrameNode("frameNode", nodeId, AceType::MakeRefPtr<Pattern>(), true);

    auto layoutProperty = frameNode->GetLayoutProperty();
    CalcSize idealSize = { CalcLength(ZERO), CalcLength(ZERO) };
    layoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    layoutProperty->calcLayoutConstraint_->minSize = idealSize;
    layoutProperty->calcLayoutConstraint_->maxSize = idealSize;
    EffectOption option;
    Color color = Color::TRANSPARENT;
    option.color = color;

    std::vector<std::pair<float, float>> fractionStops;
    fractionStops.push_back(std::pair<float, float>(0.0f, 1.0f));
    CalcDimension dimensionRadius(0.0);
    LinearGradientBlurPara blurPara(dimensionRadius, fractionStops, GradientDirection::LEFT);
    /**
     * @tc.steps: step2. ResetMinSize test, IsCurrentVisualStateProcess() == false
     * @tc.expected:call ResetMinSize(),calcLayoutConstraint_ not change
     */
    ViewStackProcessor::GetInstance()->SetVisualState(VisualState::DISABLED);
    ViewAbstract::ResetMinSize(true);
    ViewAbstract::ResetMinSize(AceType::RawPtr(FRAME_NODE_REGISTER), true);
    ViewAbstract::ResetMaxSize(true);
    ViewAbstract::ResetMaxSize(AceType::RawPtr(FRAME_NODE_REGISTER), true);
    ViewAbstract::SetBackgroundAlign(Alignment::TOP_LEFT);
    ViewAbstract::SetBackgroundEffect(option);
    ViewAbstract::SetBackgroundEffect(AceType::RawPtr(FRAME_NODE_REGISTER), option);
    ViewAbstract::SetDynamicLightUp(0, 0);
    ViewAbstract::SetDynamicLightUp(AceType::RawPtr(FRAME_NODE_REGISTER), 0, 0);
    ViewAbstract::SetLinearGradientBlur(blurPara);
    ViewAbstract::SetLinearGradientBlur(nullptr, blurPara);
    EXPECT_TRUE(layoutProperty->calcLayoutConstraint_->minSize.has_value());
    EXPECT_TRUE(layoutProperty->calcLayoutConstraint_->maxSize.has_value());

    /**
     * @tc.steps: step3. ResetMinSize test, IsCurrentVisualStateProcess() == true
     * @tc.expected:call ResetMinSize(),calcLayoutConstraint_->minSize.Width not change
     */
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    ViewAbstract::ResetMinSize(true);
    ViewAbstract::ResetMaxSize(true);
    ViewAbstract::SetBackgroundAlign(Alignment::BOTTOM_RIGHT);
    ViewAbstract::SetBackgroundEffect(option);
    ViewAbstract::SetDynamicLightUp(0, 0);
    ViewAbstract::SetLinearGradientBlur(blurPara);
    ViewAbstract::DisableOnAppear();
    ViewAbstract::DisableOnAreaChange();
    ViewAbstract::DisableOnDisAppear();
    std::vector<DimensionRect> responseRegion;
    DimensionRect responseRect(Dimension(0), Dimension(0), DimensionOffset(OFFSETF));
    responseRegion.emplace_back(responseRect);
    ViewAbstract::SetMouseResponseRegion(responseRegion);
    ViewAbstract::SetMouseResponseRegion(AceType::RawPtr(FRAME_NODE_REGISTER), responseRegion);
    EXPECT_TRUE(layoutProperty->calcLayoutConstraint_->minSize.value().Width().has_value());
    EXPECT_TRUE(layoutProperty->calcLayoutConstraint_->maxSize.value().Width().has_value());
}

/**
 * @tc.name: ViewAbstractTest042
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for tab/Up arrow/Down arrow/Left arrow/Right arrow key.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest042, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    /**
     * @tc.steps: step2. call SetKeyboardShortcut with tab and ModifierKey.
     * @tc.expected: add fail
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::SHIFT);
    ViewAbstract::SetKeyboardShortcut(VALUE_TAB, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();

    /**
     * @tc.steps: step3. call SetKeyboardShortcut with up arrow.
     * @tc.expected: add success
     */
    ViewAbstract::SetKeyboardShortcut(VALUE_DPAD_UP, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();

    /**
     * @tc.steps: step4. call SetKeyboardShortcut with up arrow and ModifierKey.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::ALT);
    ViewAbstract::SetKeyboardShortcut(VALUE_DPAD_UP, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();

    /**
     * @tc.steps: step5. call SetKeyboardShortcut with tab.
     * @tc.expected: add success
     */

    ViewAbstract::SetKeyboardShortcut(VALUE_TAB, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
}

/**
 * @tc.name: ViewAbstractOffsetEdges001
 * @tc.desc: test offset attribute, use Edges type.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and put mainNode, then build some necessary params.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);

    /**
     * @tc.steps: step2. get node in ViewStackProcessor.
     * @tc.expected: node is not null.
     */
    auto rootFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(rootFrameNode, nullptr);

    /**
     * @tc.steps: step3. use ViewAbstract::SetOffsetEdges.
     * @tc.expected: success set render property offsetEdges value.
     */
    EdgesParam edges;
    CalcDimension top(30, DimensionUnit::VP);
    CalcDimension left(20, DimensionUnit::VP);
    edges.SetTop(top);
    edges.SetLeft(left);
    ViewAbstract::SetOffsetEdges(edges);

    EXPECT_NE(FRAME_NODE_ROOT->GetRenderContext(), nullptr);
    EXPECT_EQ(FRAME_NODE_ROOT->GetRenderContext()
                  ->GetOffsetEdgesValue(EdgesParam {}).top.value_or(Dimension {}).ConvertToVp(), 30.0f);
    EXPECT_EQ(FRAME_NODE_ROOT->GetRenderContext()
                  ->GetOffsetEdgesValue(EdgesParam {}).left.value_or(Dimension {}).ConvertToVp(), 20.0f);

    /**
     * @tc.steps: step5. finish view stack.
     */
    ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: ViewAbstractPositionEdges001
 * @tc.desc: test position attribute, use Edges type.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractPositionEdges001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and put mainNode, then build some necessary params.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);

    /**
     * @tc.steps: step2. get node in ViewStackProcessor.
     * @tc.expected: node is not null.
     */
    auto rootFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(rootFrameNode, nullptr);

    /**
     * @tc.steps: step3. use ViewAbstract::SetPositionEdges.
     * @tc.expected: success set render property PositionEdges value.
     */
    EdgesParam edges;
    CalcDimension bottom(30, DimensionUnit::VP);
    CalcDimension right(20, DimensionUnit::VP);
    edges.SetBottom(bottom);
    edges.SetRight(right);
    ViewAbstract::SetPositionEdges(edges);

    EXPECT_NE(FRAME_NODE_ROOT->GetRenderContext(), nullptr);
    EXPECT_EQ(FRAME_NODE_ROOT->GetRenderContext()
                  ->GetPositionEdgesValue(EdgesParam {}).bottom.value_or(Dimension {}).ConvertToVp(), 30.0f);
    EXPECT_EQ(FRAME_NODE_ROOT->GetRenderContext()
                  ->GetPositionEdgesValue(EdgesParam {}).right.value_or(Dimension {}).ConvertToVp(), 20.0f);

    /**
     * @tc.steps: step5. finish view stack.
     */
    ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: ViewAbstractDisableClickTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableClickTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    GestureEventFunc tapEventFunc;
    ViewAbstract::SetOnClick(std::move(tapEventFunc));

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    auto gestureHub = node->GetOrCreateGestureEventHub();
    auto& callback = gestureHub->clickEventActuator_->userCallback_;
    EXPECT_NE(callback, nullptr);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnClick();
    EXPECT_EQ(callback, nullptr);

    /**
     * @tc.steps: step3. Add callback again.
     * @tc.expected: callback is not null.
     */
    GestureEventFunc tapEventFunc2;
    ViewAbstract::SetOnClick(std::move(tapEventFunc2));
    EXPECT_NE(callback, nullptr);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: ViewAbstractDisableTouchTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableTouchTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    TouchEventFunc touchEventFunc;
    ViewAbstract::SetOnTouch(std::move(touchEventFunc));

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    auto gestureHub = node->GetOrCreateGestureEventHub();
    auto& callback = gestureHub->touchEventActuator_->userCallback_;
    EXPECT_NE(callback, nullptr);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnTouch();
    EXPECT_EQ(callback, nullptr);

    /**
     * @tc.steps: step3. Add callback again.
     * @tc.expected: callback is not null.
     */
    TouchEventFunc touchEventFunc2;
    ViewAbstract::SetOnTouch(std::move(touchEventFunc2));
    EXPECT_NE(callback, nullptr);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: ViewAbstractDisableMouseTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableMouseTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    OnMouseEventFunc onMouseEventFunc;
    ViewAbstract::SetOnMouse(std::move(onMouseEventFunc));

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    auto eventHub = node->GetOrCreateInputEventHub();
    auto& callback = eventHub->mouseEventActuator_->userCallback_;
    EXPECT_NE(callback, nullptr);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnMouse();
    EXPECT_EQ(callback, nullptr);

    /**
     * @tc.steps: step3. Add callback again.
     * @tc.expected: callback is not null.
     */
    OnMouseEventFunc onMouseEventFunc2;
    ViewAbstract::SetOnMouse(std::move(onMouseEventFunc2));
    ViewAbstract::SetJSFrameNodeOnMouse(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(onMouseEventFunc2));
    ViewAbstract::ClearJSFrameNodeOnMouse(AceType::RawPtr(FRAME_NODE_REGISTER));
    EXPECT_NE(callback, nullptr);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: ViewAbstractDisableHoverTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableHoverTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    OnHoverFunc onHoverEventFunc;
    ViewAbstract::SetOnHover(std::move(onHoverEventFunc));

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    auto eventHub = node->GetOrCreateInputEventHub();
    auto& callback = eventHub->hoverEventActuator_->userCallback_;
    EXPECT_NE(callback, nullptr);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnHover();
    EXPECT_EQ(callback, nullptr);

    /**
     * @tc.steps: step3. Add callback again.
     * @tc.expected: callback is not null.
     */
    OnHoverFunc onHoverEventFunc2;
    ViewAbstract::SetOnHover(std::move(onHoverEventFunc2));
    EXPECT_NE(callback, nullptr);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: ViewAbstractDisableKeyTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableKeyTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    OnKeyCallbackFunc onKeyCallback = [](KeyEventInfo& info) {};
    ViewAbstract::SetOnKeyEvent(std::move(onKeyCallback));

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    auto focusHub = node->GetOrCreateFocusHub();
    auto& callback = focusHub->focusCallbackEvents_->onKeyEventCallback_;
    EXPECT_TRUE(callback);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnKeyEvent();
    EXPECT_FALSE(callback);

    /**
     * @tc.steps: step3. Add callback again.
     * @tc.expected: callback is not null.
     */
    OnKeyCallbackFunc onKeyCallback2 = [](KeyEventInfo& info) {};
    ViewAbstract::SetOnKeyEvent(std::move(onKeyCallback2));
    EXPECT_TRUE(callback);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: ViewAbstractDisableFocusTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableFocusTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    OnFocusFunc onFocusCallback = []() {};
    ViewAbstract::SetOnFocus(std::move(onFocusCallback));
    ViewAbstract::SetOnFocus(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(onFocusCallback));
    ViewAbstract::SetJSFrameNodeOnFocusCallback(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(onFocusCallback));
    ViewAbstract::ClearJSFrameNodeOnFocusCallback(AceType::RawPtr(FRAME_NODE_REGISTER));

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    auto focusHub = node->GetOrCreateFocusHub();
    auto& callback = focusHub->focusCallbackEvents_->onFocusCallback_;
    EXPECT_NE(callback, nullptr);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnFocus();
    EXPECT_EQ(callback, nullptr);

    /**
     * @tc.steps: step3. Add callback again.
     * @tc.expected: callback is not null.
     */
    OnFocusFunc onFocusCallback2 = []() {};
    ViewAbstract::SetOnFocus(std::move(onFocusCallback2));
    EXPECT_NE(callback, nullptr);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: ViewAbstractDisableBlurTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableBlurTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    OnBlurFunc onBlurCallback = []() {};
    ViewAbstract::SetOnFocus(std::move(onBlurCallback));
    ViewAbstract::SetJSFrameNodeOnBlurCallback(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(onBlurCallback));
    ViewAbstract::ClearJSFrameNodeOnBlurCallback(AceType::RawPtr(FRAME_NODE_REGISTER));

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNodeOne = static_cast<FrameNode*>(ViewAbstract::GetFrameNode());
    EXPECT_EQ(strcmp(frameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    auto focusHub = node->GetOrCreateFocusHub();
    auto& callback = focusHub->focusCallbackEvents_->onBlurCallback_;
    EXPECT_TRUE(callback);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnBlur();
    EXPECT_FALSE(callback);

    /**
     * @tc.steps: step3. Add callback again.
     * @tc.expected: callback is not null.
     */
    OnBlurFunc onBlurCallback2 = []() {};
    ViewAbstract::SetOnBlur(std::move(onBlurCallback2));
    ViewAbstract::SetOnBlur(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(onBlurCallback2));
    EXPECT_TRUE(callback);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: ViewAbstractMonopolizeEvent001
 * @tc.desc: View_Abstract set MonopolizeEvent true test
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractMonopolizeEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and put mainNode, then build some necessary params.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);

    /**
     * @tc.steps: step2. set monopolize
     */
    ViewAbstract::SetMonopolizeEvents(true);
    ViewAbstract::SetMonopolizeEvents(AceType::RawPtr(FRAME_NODE_REGISTER), true);

    /**
     * @tc.steps: step3. get node in ViewStackProcessor.
     * @tc.expected: node is not null.
     */
    auto rootFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(rootFrameNode, nullptr);

    /**
     * @tc.steps: step4. get monopolizeEvents value of the node.
     * @tc.expected: value is equal to true.
     */
    EXPECT_EQ(rootFrameNode->GetMonopolizeEvents(), true);

    /**
     * @tc.steps: step5. finish view stack.
     */
    ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: ViewAbstractMonopolizeEvent002
 * @tc.desc: View_Abstract set MonopolizeEvent false test
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractMonopolizeEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and put mainNode, then build some necessary params.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);

    /**
     * @tc.steps: step2. set monopolize
     */
    ViewAbstract::SetMonopolizeEvents(false);

    /**
     * @tc.steps: step3. get node in ViewStackProcessor.
     * @tc.expected: node is not null.
     */
    auto rootFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(rootFrameNode, nullptr);

    /**
     * @tc.steps: step4. get monopolizeEvents value of the node.
     * @tc.expected: value is equal to true.
     */
    EXPECT_EQ(rootFrameNode->GetMonopolizeEvents(), false);

    /**
     * @tc.steps: step5. finish view stack.
     */
    ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: ViewAbstractMonopolizeEvent003
 * @tc.desc: View_Abstract not set MonopolizeEvent test (use default)
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractMonopolizeEvent003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and put mainNode, then build some necessary params.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);

    /**
     * @tc.steps: step2. get node in ViewStackProcessor.
     * @tc.expected: node is not null.
     */
    auto rootFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(rootFrameNode, nullptr);

    /**
     * @tc.steps: step3. get monopolizeEvents value of the node.
     * @tc.expected: value is equal to true.
     */
    EXPECT_EQ(rootFrameNode->GetMonopolizeEvents(), false);

    /**
     * @tc.steps: step5. finish view stack.
     */
    ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: ViewAbstractMenuTransition001
 * @tc.desc: Test the BindMenu and BindContextMenu of ViewAbstractModelNG (use dafault)
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractMenuTransition001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    PipelineBase::GetCurrentContext()->SetThemeManager(themeManager);
    PipelineBase::GetCurrentContext()->SetEventManager(AceType::MakeRefPtr<EventManager>());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    const RefPtr<FrameNode> mainNode =
        FrameNode::CreateFrameNode("targetNode", nodeId, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(mainNode);
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);

    ASSERT_NE(SubwindowManager::GetInstance(), nullptr);
    std::function<void()> flagFunc = []() { flag++; };
    std::vector<NG::OptionParam> params = {};
    std::function<void()> buildFunc;
    MenuParam menuParam;
    std::function<void()> previewBuildFunc = nullptr;

    menuParam.type = MenuType::MENU;
    menuParam.isShow = true;

    auto targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(targetNode, nullptr);
    std::function<void()> action = [] {};
    params.emplace_back("MenuItem1", "", action);
    params.emplace_back("MenuItem2", "", action);
    viewAbstractModelNG.BindMenu(std::move(params), std::move(buildFunc), menuParam);
    auto targetId = targetNode->GetId();

    auto menuNode = overlayManager->GetMenuNode(targetId);
    ASSERT_NE(menuNode, nullptr);
    auto wrapperPattern = menuNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);
    EXPECT_EQ(wrapperPattern->HasTransitionEffect(), false);
    EXPECT_EQ(wrapperPattern->HasPreviewTransitionEffect(), false);
}

/**
 * @tc.name: ViewAbstractMenuTransition002
 * @tc.desc: Test the BindMenu and BindContextMenu of ViewAbstractModelNG (use true)
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractMenuTransition002, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    PipelineBase::GetCurrentContext()->SetThemeManager(themeManager);
    PipelineBase::GetCurrentContext()->SetEventManager(AceType::MakeRefPtr<EventManager>());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    const RefPtr<FrameNode> mainNode =
        FrameNode::CreateFrameNode("targetNode", nodeId, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(mainNode);
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);

    ASSERT_NE(SubwindowManager::GetInstance(), nullptr);
    std::function<void()> flagFunc = []() { flag++; };
    std::vector<NG::OptionParam> params = {};
    std::function<void()> buildFunc;
    MenuParam menuParam;
    std::function<void()> previewBuildFunc = nullptr;

    NG::RotateOptions rotate(0.0f, 0.0f, 0.0f, 0.0f, 0.5_pct, 0.5_pct);

    menuParam.hasTransitionEffect = true;
    menuParam.hasPreviewTransitionEffect = true;
    menuParam.transition = AceType::MakeRefPtr<NG::ChainedRotateEffect>(rotate);
    menuParam.previewTransition = AceType::MakeRefPtr<NG::ChainedRotateEffect>(rotate);
    menuParam.type = MenuType::MENU;
    menuParam.isShow = true;

    auto targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(targetNode, nullptr);
    std::function<void()> action = [] {};
    params.emplace_back("MenuItem1", "", action);
    params.emplace_back("MenuItem2", "", action);
    viewAbstractModelNG.BindMenu(std::move(params), std::move(buildFunc), menuParam);
    auto targetId = targetNode->GetId();

    auto menuNode = overlayManager->GetMenuNode(targetId);
    ASSERT_NE(menuNode, nullptr);
    auto wrapperPattern = menuNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);
    EXPECT_EQ(wrapperPattern->HasTransitionEffect(), true);
    EXPECT_EQ(wrapperPattern->HasPreviewTransitionEffect(), true);
}

/**
 * @tc.name: ViewAbstractMenuBorderRadius001
 * @tc.desc: Test the BindMenu and BindContextMenu of ViewAbstractModelNG (use true)
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractMenuBorderRadius001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    PipelineBase::GetCurrentContext()->SetThemeManager(themeManager);
    PipelineBase::GetCurrentContext()->SetEventManager(AceType::MakeRefPtr<EventManager>());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    const RefPtr<FrameNode> mainNode =
        FrameNode::CreateFrameNode("targetNode", nodeId, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(mainNode);
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    ASSERT_NE(SubwindowManager::GetInstance(), nullptr);
    std::vector<NG::OptionParam> params = {};
    std::function<void()> buildFunc;
    MenuParam menuParam;

    menuParam.type = MenuType::MENU;
    menuParam.isShow = true;
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(Dimension(16));
    menuParam.borderRadius = borderRadius;

    auto targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(targetNode, nullptr);
    std::function<void()> action = [] {};
    params.emplace_back("MenuItem1", "", action);
    params.emplace_back("MenuItem2", "", action);
    viewAbstractModelNG.BindMenu(std::move(params), std::move(buildFunc), menuParam);
    auto targetId = targetNode->GetId();

    auto menuNode = overlayManager->GetMenuNode(targetId);
    ASSERT_NE(menuNode, nullptr);
    auto wrapperPattern = menuNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);
    EXPECT_EQ(wrapperPattern->GetHasCustomRadius(), true);
}

/**
 * @tc.name: ViewAbstractDisableClickByFrameNodeTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableClickByFrameNodeTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    GestureEventFunc tapEventFunc;
    ViewAbstract::SetOnClick(AceType::RawPtr(node), std::move(tapEventFunc));
    auto gestureHub = node->GetOrCreateGestureEventHub();
    auto& callback = gestureHub->clickEventActuator_->userCallback_;
    EXPECT_NE(callback, nullptr);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnClick(AceType::RawPtr(node));
    EXPECT_EQ(callback, nullptr);
}

/**
 * @tc.name: ViewAbstractDisableTouchByFrameNodeTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableTouchByFrameNodeTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    TouchEventFunc touchEventFunc;
    ViewAbstract::SetOnTouch(AceType::RawPtr(node), std::move(touchEventFunc));
    auto gestureHub = node->GetOrCreateGestureEventHub();
    auto& callback = gestureHub->touchEventActuator_->userCallback_;
    EXPECT_NE(callback, nullptr);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnTouch(AceType::RawPtr(node));
    EXPECT_EQ(callback, nullptr);
}

/**
 * @tc.name: ViewAbstractDisableMouseByFrameNodeTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableMouseByFrameNodeTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    OnMouseEventFunc onMouseEventFunc;
    ViewAbstract::SetOnMouse(AceType::RawPtr(node), std::move(onMouseEventFunc));
    auto eventHub = node->GetOrCreateInputEventHub();
    auto& callback = eventHub->mouseEventActuator_->userCallback_;
    EXPECT_NE(callback, nullptr);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnMouse(AceType::RawPtr(node));
    EXPECT_EQ(callback, nullptr);
}

/**
 * @tc.name: ViewAbstractDisableHoverByFrameNodeTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableHoverByFrameNodeTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    OnHoverFunc onHoverEventFunc;
    ViewAbstract::SetOnHover(AceType::RawPtr(node), std::move(onHoverEventFunc));
    auto eventHub = node->GetOrCreateInputEventHub();
    auto& callback = eventHub->hoverEventActuator_->userCallback_;
    EXPECT_NE(callback, nullptr);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnHover(AceType::RawPtr(node));
    EXPECT_EQ(callback, nullptr);
}

/**
 * @tc.name: ViewAbstractDisableKeyByFrameNodeTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableKeyByFrameNodeTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    OnKeyCallbackFunc onKeyCallback = [](KeyEventInfo& info) {};
    ViewAbstract::SetOnKeyEvent(AceType::RawPtr(node), std::move(onKeyCallback));
    auto focusHub = node->GetOrCreateFocusHub();
    auto& callback = focusHub->focusCallbackEvents_->onKeyEventCallback_;
    EXPECT_TRUE(callback);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnKeyEvent(AceType::RawPtr(node));
    EXPECT_FALSE(callback);
}

/**
 * @tc.name: ViewAbstractDisableFocusByFrameNodeTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableFocusByFrameNodeTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    OnFocusFunc onFocusCallback = []() {};
    ViewAbstract::SetOnFocus(AceType::RawPtr(node), std::move(onFocusCallback));
    auto focusHub = node->GetOrCreateFocusHub();
    auto& callback = focusHub->focusCallbackEvents_->onFocusCallback_;
    EXPECT_NE(callback, nullptr);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnFocus(AceType::RawPtr(node));
    EXPECT_EQ(callback, nullptr);
}

/**
 * @tc.name: ViewAbstractDisableBlurByFrameNodeTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableBlurByFrameNodeTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    OnBlurFunc onBlurCallback = []() {};
    ViewAbstract::SetOnBlur(AceType::RawPtr(node), std::move(onBlurCallback));
    auto focusHub = node->GetOrCreateFocusHub();
    auto& callback = focusHub->focusCallbackEvents_->onBlurCallback_;
    EXPECT_TRUE(callback);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnBlur(AceType::RawPtr(node));
    EXPECT_FALSE(callback);
}

/**
 * @tc.name: ViewAbstractDisableOnAppearByFrameNodeTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableOnAppearByFrameNodeTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    std::function<void()> onAppearCallback = []() {};
    ViewAbstract::SetOnAppear(AceType::RawPtr(node), std::move(onAppearCallback));
    auto eventHub = node->GetEventHub<EventHub>();
    auto& callback = eventHub->onAppear_;
    EXPECT_NE(callback, nullptr);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnAppear(AceType::RawPtr(node));
    EXPECT_EQ(callback, nullptr);
}

/**
 * @tc.name: ViewAbstractDisableOnDisAppearByFrameNodeTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableOnDisAppearByFrameNodeTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    std::function<void()> onDiaAppearCallback = []() {};
    ViewAbstract::SetOnDisappear(AceType::RawPtr(node), std::move(onDiaAppearCallback));
    auto eventHub = node->GetEventHub<EventHub>();
    auto& callback = eventHub->onDisappear_;
    EXPECT_NE(callback, nullptr);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnDisappear(AceType::RawPtr(node));
    EXPECT_EQ(callback, nullptr);
}

/**
 * @tc.name: ViewAbstractDisableOnAreaChangeByFrameNodeTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableOnAreaChangeByFrameNodeTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    std::function<void(const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin)>
        onAreaChangeCallback =
            [](const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin) {};
    ViewAbstract::SetOnAreaChanged(AceType::RawPtr(node), std::move(onAreaChangeCallback));
    auto eventHub = node->GetEventHub<EventHub>();
    auto& callback = eventHub->onAreaChanged_;
    EXPECT_NE(callback, nullptr);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnAreaChange(AceType::RawPtr(node));
    EXPECT_EQ(callback, nullptr);
}

/**
 * @tc.name: ViewAbstractSetOnGestureJudgeBeiginByFrameNodeTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractSetOnGestureJudgeBeiginByFrameNodeTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    GestureJudgeFunc onGestureJudgeCallback = [](const RefPtr<GestureInfo>& gestureInfo,
                                                  const std::shared_ptr<BaseGestureEvent>& info) {
        return GestureJudgeResult::REJECT;
    };
    ViewAbstract::SetOnGestureJudgeBegin(AceType::RawPtr(node), std::move(onGestureJudgeCallback));
    auto gestureHub = node->GetOrCreateGestureEventHub();
    auto& callback = gestureHub->gestureJudgeFunc_;
    EXPECT_NE(callback, nullptr);
}

/**
 * @tc.name: ViewAbstractSetOnSizeChangeByFrameNodeTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractSetOnSizeChangeByFrameNodeTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    std::function<void(const RectF& oldRect, const RectF& rect)> onSizeChangeCallback = [](const RectF& oldRect,
                                                                                            const RectF& rect) {};
    ViewAbstract::SetOnSizeChanged(AceType::RawPtr(node), std::move(onSizeChangeCallback));
    auto eventHub = node->GetEventHub<EventHub>();
    auto& callback = eventHub->onSizeChanged_;
    EXPECT_NE(callback, nullptr);
}

/**
 * @tc.name: MotionBlur001
 * @tc.desc: SetMotionBlur.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, MotionBlur001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and put mainNode, then build some necessary params.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);

    /**
     * @tc.steps: step2. get node in ViewStackProcessor.
     * @tc.expected: node is not null.
     */
    auto rootFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(rootFrameNode, nullptr);

    /**
     * @tc.steps: step3. use ViewAbstract::SetMotionBlur.
     * @tc.expected: success set render property motionBlur value.
     */
    MotionBlurOption motionBlurOption;
    motionBlurOption.radius = 5;
    motionBlurOption.anchor.x = 0.5;
    motionBlurOption.anchor.y = 0.5;
    ViewAbstract::SetMotionBlur(motionBlurOption);
    /**
     * @tc.steps: step4. get propMotionBlur value of the node.
     * @tc.expected: anchor.x = 0.5, anchor.y = 0.5, radius = 5.
     */
    EXPECT_NE(FRAME_NODE_ROOT->GetRenderContext(), nullptr);
    EXPECT_EQ(FRAME_NODE_ROOT->GetRenderContext()
                  ->GetOrCreateForeground()->propMotionBlur->anchor.x, 0.5);
    EXPECT_EQ(FRAME_NODE_ROOT->GetRenderContext()
                  ->GetOrCreateForeground()->propMotionBlur->anchor.y, 0.5);
    EXPECT_EQ(FRAME_NODE_ROOT->GetRenderContext()
                  ->GetOrCreateForeground()->propMotionBlur->radius, 5);

    /**
     * @tc.steps: step5. finish view stack.
     */
    ViewStackProcessor::GetInstance()->Finish();
}
} // namespace OHOS::Ace::NG
