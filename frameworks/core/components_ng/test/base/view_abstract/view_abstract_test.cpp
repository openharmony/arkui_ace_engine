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
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_model_ng.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/layout/layout_property.h"
#undef private
#undef protected
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const Dimension WIDTH {50.0, DimensionUnit::PX};
const Dimension HEIGHT {100.0, DimensionUnit::PX};
const Dimension MIN_WIDTH {10.0, DimensionUnit::PX};
const Dimension MIN_HEIGHT {20.0, DimensionUnit::PX};
const Dimension RADIUS {10.0, DimensionUnit::PX};
const Dimension LEFT {10.0, DimensionUnit::PX};
const Dimension TOP {20.0, DimensionUnit::PX};
const Dimension RIGHT {10.0, DimensionUnit::PX};
const Dimension BOTTOM {20.0, DimensionUnit::PX};
const Dimension VALUE {-50.0, DimensionUnit::PX};

const OffsetF OFFSETF {1.0, 1.0};
const Offset OFFSET {2.0, 2.0};
const float RATIO = 1.0f;
const double OPACITYS = 10;
const int32_t TEN = 10;
const int32_t FOUF = 4;
const int32_t INDEX = 1;
const Color BLUE = Color(0xff0000ff);

const BackgroundImageSize BACKGROUNDSIZE {BackgroundImageSizeType::AUTO, 1.0};
const BackgroundImagePosition BACKGROUNDPOSITION {BackgroundImagePositionType::PERCENT, -1.0,
    BackgroundImagePositionType::PERCENT, 0.0};

constexpr char TAG_ROOT[] = "root";
constexpr char TAG_CHILD[] = "child";
const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);

std::string srcimages = "common/images/mmm.jpg";

auto callback = []() {
    srcimages = "test";
};
}; // namespace
class ViewAbstractTest : public testing::Test {};

/**
 * @tc.name: ViewAbstractTest001
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.The FrameNode is null, related function is called.
     */
    ViewAbstract::SetWidth(NG::CalcLength(WIDTH));
    ViewAbstract::SetHeight(NG::CalcLength(HEIGHT));
    ViewAbstract::SetMinWidth(NG::CalcLength(MIN_WIDTH));
    ViewAbstract::SetMinHeight(NG::CalcLength(MIN_HEIGHT));
    ViewAbstract::SetMaxWidth(NG::CalcLength(MIN_WIDTH));
    ViewAbstract::SetMaxHeight(NG::CalcLength(MIN_HEIGHT));
    ViewAbstract::ClearWidthOrHeight(true);

    /**
     * @tc.expected: Return expected results..
     */
    EXPECT_EQ(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractTest002
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest002, TestSize.Level1)
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
HWTEST_F(ViewAbstractTest, ViewAbstractTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1.The FrameNode is null, related function is called.
     */
    ViewAbstract::SetAspectRatio(RATIO);
    ViewAbstract::SetBackgroundColor(BLUE);
    ViewAbstract::SetBackgroundImage(srcimages);
    ViewAbstract::SetBackgroundImageSize(BACKGROUNDSIZE);
    ViewAbstract::SetBackgroundImagePosition(BACKGROUNDPOSITION);
    ViewAbstract::SetLayoutWeight(TEN);

    BlurStyleOption blurStyleOption;
    blurStyleOption.blurStyle = BlurStyle::NO_MATERIAL;
    blurStyleOption.colorMode = ThemeColorMode::SYSTEM;
    blurStyleOption.adaptiveColor = AdaptiveColor::DEFAULT;
    ViewAbstract::SetBackgroundBlurStyle(blurStyleOption);

    std::map<AlignDirection, AlignRule> alignRules;
    ViewAbstract::SetAlignRules(alignRules);
    auto repeat = static_cast<ImageRepeat>(INDEX);
    ViewAbstract::SetBackgroundImageRepeat(repeat);
    auto direction = static_cast<TextDirection>(INDEX);
    ViewAbstract::SetLayoutDirection(direction);

    /**
     * @tc.expected: Return expected results..
     */
    EXPECT_EQ(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractTest004
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1.push FrameNode is not null, related function is called.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    ViewAbstract::SetAspectRatio(RATIO);
    ViewAbstract::SetBackgroundColor(BLUE);
    ViewAbstract::SetBackgroundImage(srcimages);
    ViewAbstract::SetBackgroundImageSize(BACKGROUNDSIZE);
    ViewAbstract::SetBackgroundImagePosition(BACKGROUNDPOSITION);
    ViewAbstract::SetLayoutWeight(TEN);

    BlurStyleOption blurStyleOption;
    blurStyleOption.blurStyle = BlurStyle::NO_MATERIAL;
    blurStyleOption.colorMode = ThemeColorMode::SYSTEM;
    blurStyleOption.adaptiveColor = AdaptiveColor::DEFAULT;
    ViewAbstract::SetBackgroundBlurStyle(blurStyleOption);

    std::map<AlignDirection, AlignRule> alignRules;
    ViewAbstract::SetAlignRules(alignRules);
    auto repeat = static_cast<ImageRepeat>(INDEX);
    ViewAbstract::SetBackgroundImageRepeat(repeat);
    auto direction = static_cast<TextDirection>(INDEX);
    ViewAbstract::SetLayoutDirection(direction);

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
HWTEST_F(ViewAbstractTest, ViewAbstractTest005, TestSize.Level1)
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

    /**
     * @tc.expected: Return expected results..
     */
    EXPECT_EQ(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractTest006
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1.push FrameNode is not null, related function is called.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

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
HWTEST_F(ViewAbstractTest, ViewAbstractTest007, TestSize.Level1)
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

    NG::BorderColorProperty borderColors;
    ViewAbstract::SetBorderColor(borderColors);

    NG::BorderWidthProperty borderWidth;
    ViewAbstract::SetBorderWidth(borderWidth);

    NG::BorderStyleProperty borderStyles;
    ViewAbstract::SetBorderStyle(borderStyles);

    /**
     * @tc.expected: Return expected results..
     */
    EXPECT_EQ(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractTest008
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest008, TestSize.Level1)
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

    NG::BorderWidthProperty borderWidth;
    ViewAbstract::SetBorderWidth(borderWidth);

    NG::BorderStyleProperty borderStyles;
    ViewAbstract::SetBorderStyle(borderStyles);

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
HWTEST_F(ViewAbstractTest, ViewAbstractTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1.The FrameNode is null, related function is called.
     */
    GestureEventFunc tapEventFunc;
    ViewAbstract::SetOnClick(std::move(tapEventFunc));
    TouchEventFunc touchEventFunc;
    ViewAbstract::SetOnTouch(std::move(touchEventFunc));
    OnMouseEventFunc onMouseEventFunc;
    ViewAbstract::SetOnMouse(std::move(onMouseEventFunc));
    OnHoverEventFunc onHoverEventFunc;
    ViewAbstract::SetOnHover(std::move(onHoverEventFunc));
    OnKeyCallbackFunc onKeyCallback;
    ViewAbstract::SetOnKeyEvent(std::move(onKeyCallback));

    auto hoverEffect = static_cast<HoverEffectType>(INDEX);
    ViewAbstract::SetHoverEffect(hoverEffect);

    ViewAbstract::SetFocusable(false);
    ViewAbstract::SetEnabled(false);
    ViewAbstract::SetOnFocus(callback);
    ViewAbstract::SetOnBlur(callback);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractTest010
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest010, TestSize.Level1)
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
    OnHoverEventFunc onHoverEventFunc;
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
HWTEST_F(ViewAbstractTest, ViewAbstractTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1.The FrameNode is null, related function is called.
     */
    ViewAbstract::SetTabIndex(INDEX);
    ViewAbstract::SetFocusOnTouch(false);
    ViewAbstract::SetDefaultFocus(false);
    ViewAbstract::SetGroupDefaultFocus(false);
    ViewAbstract::SetTouchable(false);
    ViewAbstract::SetOnAppear(callback);
    ViewAbstract::SetOnDisappear(callback);

    auto hitTestMode = static_cast<HitTestMode>(INDEX);
    ViewAbstract::SetHitTestMode(hitTestMode);

    std::vector<DimensionRect> responseRegion;
    ViewAbstract::SetResponseRegion(std::move(responseRegion));
    std::function<DragDropInfo(const RefPtr<OHOS::Ace::DragEvent>&,
        const std::string&)> onDragStart;
    ViewAbstract::SetOnDragStart(std::move(onDragStart));
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&,
        const std::string&)> onDragEnter;
    ViewAbstract::SetOnDragEnter(std::move(onDragEnter));
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&,
        const std::string&)> onDragLeave;
    ViewAbstract::SetOnDragLeave(std::move(onDragLeave));
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&,
        const std::string&)> onDragMove;
    ViewAbstract::SetOnDragMove(std::move(onDragMove));
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&,
        const std::string&)> onDrop;
    ViewAbstract::SetOnDrop(std::move(onDrop));
    Alignment alignment;
    ViewAbstract::SetAlign(std::move(alignment));

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractTest012
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1.push FrameNode is not null, related function is called.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    ViewAbstract::SetTabIndex(INDEX);
    ViewAbstract::SetFocusOnTouch(false);
    ViewAbstract::SetDefaultFocus(false);
    ViewAbstract::SetGroupDefaultFocus(false);
    ViewAbstract::SetTouchable(false);
    ViewAbstract::SetOnAppear(callback);
    ViewAbstract::SetOnDisappear(callback);
    auto hitTestMode = static_cast<HitTestMode>(INDEX);
    ViewAbstract::SetHitTestMode(hitTestMode);

    std::vector<DimensionRect> responseRegion;
    ViewAbstract::SetResponseRegion(std::move(responseRegion));
    std::function<DragDropInfo(const RefPtr<OHOS::Ace::DragEvent>&,
        const std::string&)> onDragStart;
    ViewAbstract::SetOnDragStart(std::move(onDragStart));
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&,
        const std::string&)> onDragEnter;
    ViewAbstract::SetOnDragEnter(std::move(onDragEnter));
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&,
        const std::string&)> onDragLeave;
    ViewAbstract::SetOnDragLeave(std::move(onDragLeave));
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&,
        const std::string&)> onDragMove;
    ViewAbstract::SetOnDragMove(std::move(onDragMove));
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&,
        const std::string&)> onDrop;
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
HWTEST_F(ViewAbstractTest, ViewAbstractTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1.The FrameNode is null, related function is called.
     */
    auto visible = static_cast<VisibleType>(INDEX);
    ViewAbstract::SetVisibility(std::move(visible));
    ViewAbstract::SetGeometryTransition(srcimages);
    ViewAbstract::SetOpacity(OPACITYS);
    ViewAbstract::SetZIndex(FOUF);

    OffsetT<Dimension> value = {WIDTH, HEIGHT};
    ViewAbstract::SetPosition(value);
    ViewAbstract::SetOffset(value);
    ViewAbstract::MarkAnchor(value);
    VectorF scale(1.0f, 1.0f);
    ViewAbstract::SetScale(scale);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractTest014
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest014, TestSize.Level1)
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

    OffsetT<Dimension> value = {WIDTH, HEIGHT};
    ViewAbstract::SetPosition(value);
    ViewAbstract::SetOffset(value);
    ViewAbstract::MarkAnchor(value);
    VectorF scale(1.0f, 1.0f);
    ViewAbstract::SetScale(scale);

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
HWTEST_F(ViewAbstractTest, ViewAbstractTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1.The FrameNode is null, related function is called.
     */
    DimensionOffset value = {WIDTH, HEIGHT};
    ViewAbstract::SetPivot(value);
    NG::TranslateOptions pttions;
    ViewAbstract::SetTranslate(std::move(pttions));
    Matrix4 matrix;
    ViewAbstract::SetTransformMatrix(std::move(matrix));
    ViewAbstract::SetBackdropBlur(RADIUS);
    ViewAbstract::SetFrontBlur(RADIUS);
    ViewAbstract::SetInspectorId(srcimages);

    Vector4F scale(1.0f, 1.0f, 2.0f, 2.0f);
    ViewAbstract::SetRotate(scale);
    ShadowStyle style {1};
    Shadow shadow {RATIO, OFFSET, BLUE, style};
    ViewAbstract::SetBackShadow(shadow);

    NG::Gradient gradient;
    ViewAbstract::SetLinearGradient(std::move(gradient));
    ViewAbstract::SetSweepGradient(std::move(gradient));
    ViewAbstract::SetRadialGradient(std::move(gradient));

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractTest016
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1.push FrameNode is not null, related function is called.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    DimensionOffset value = {WIDTH, HEIGHT};
    ViewAbstract::SetPivot(value);
    NG::TranslateOptions pttions;
    ViewAbstract::SetTranslate(std::move(pttions));
    Matrix4 matrix;
    ViewAbstract::SetTransformMatrix(std::move(matrix));
    ViewAbstract::SetBackdropBlur(RADIUS);
    ViewAbstract::SetFrontBlur(RADIUS);
    ViewAbstract::SetInspectorId(srcimages);
    ViewAbstract::SetDebugLine(srcimages);

    Vector4F scale(1.0f, 1.0f, 2.0f, 2.0f);
    ViewAbstract::SetRotate(scale);
    ShadowStyle style {1};
    Shadow shadow {RATIO, OFFSET, BLUE, style};
    ViewAbstract::SetBackShadow(shadow);
    NG::Gradient gradient;
    ViewAbstract::SetLinearGradient(std::move(gradient));
    ViewAbstract::SetSweepGradient(std::move(gradient));
    ViewAbstract::SetRadialGradient(std::move(gradient));

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
HWTEST_F(ViewAbstractTest, ViewAbstractTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1.The FrameNode is null, related function is called.
     */
    auto visible = static_cast<GridSizeType>(INDEX);
    ViewAbstract::SetGrid(FOUF, FOUF, std::move(visible));
    TransitionOptions options;
    ViewAbstract::SetTransition(std::move(options));
    RefPtr<BasicShape> basicShape;
    ViewAbstract::SetClipShape(std::move(basicShape));
    ViewAbstract::SetMask(std::move(basicShape));
    ViewAbstract::SetClipEdge(false);
    ViewAbstract::SetGrayScale(RADIUS);
    ViewAbstract::SetContrast(RADIUS);
    ViewAbstract::SetSaturate(RADIUS);
    ViewAbstract::SetSepia(RADIUS);
    ViewAbstract::SetInvert(RADIUS);
    ViewAbstract::SetHueRotate(RATIO);
    ViewAbstract::SetBrightness(RADIUS);
    ViewAbstract::SetColorBlend(BLUE);
    ViewAbstract::SetBorderImageSource(srcimages);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractTest018
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest018, TestSize.Level1)
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
    ViewAbstract::SetGrayScale(RADIUS);
    ViewAbstract::SetContrast(RADIUS);
    ViewAbstract::SetSaturate(RADIUS);
    ViewAbstract::SetSepia(RADIUS);
    ViewAbstract::SetInvert(RADIUS);
    ViewAbstract::SetHueRotate(RATIO);
    ViewAbstract::SetBrightness(RADIUS);
    ViewAbstract::SetColorBlend(BLUE);
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
HWTEST_F(ViewAbstractTest, ViewAbstractTest019, TestSize.Level1)
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
    Gradient gradient;
    ViewAbstract::SetBorderImageGradient(std::move(gradient));
    OverlayOptions overlay;
    ViewAbstract::SetOverlay(std::move(overlay));
    MotionPathOption motionPath;
    ViewAbstract::SetMotionPath(std::move(motionPath));
    ViewAbstract::SetSharedTransition("", nullptr);
    ViewAbstract::SetSphericalEffect(RATIO);
    ViewAbstract::SetLightUpEffect(RATIO);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractTest020
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1.push FrameNode is not null, related function is called.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    RefPtr<BorderImage> borderImage;
    ViewAbstract::SetBorderImage(std::move(borderImage));
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
HWTEST_F(ViewAbstractTest, ViewAbstractTest021, TestSize.Level1)
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
    RefPtr<NG::ChainedTransitionEffect> effect;
    ViewAbstract::SetChainedTransition(std::move(effect));
    RefPtr<ProgressMaskProperty> progress;
    ViewAbstract::SetProgressMask(std::move(progress));
    
    ViewAbstract::SetForegroundColor(BLUE);
    auto strategy = static_cast<ForegroundColorStrategy>(INDEX);
    ViewAbstract::SetForegroundColorStrategy(std::move(strategy));
    std::vector<ModifierKey> keys;
    ViewAbstract::SetKeyboardShortcut(srcimages, std::move(keys), callback);
    auto hoverEffect = static_cast<HoverEffectType>(INDEX);
    ViewAbstract::SetHoverEffectAuto(hoverEffect);
    ViewAbstract::SetDraggable(true);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractTest022
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest022, TestSize.Level1)
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
    std::vector<ModifierKey> keys;
    ViewAbstract::SetKeyboardShortcut(srcimages, std::move(keys), callback);
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
HWTEST_F(ViewAbstractTest, ViewAbstractTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1.The FrameNode is null, related function is called.
     */
    std::function<void(const RectF& oldRect, const OffsetF& oldOrigin,
        const RectF& rect, const OffsetF& origin)> onAreaChanged;
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
    EXPECT_EQ(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractTest024
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step1.push FrameNode is not null, related function is called.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    std::function<void(const RectF& oldRect, const OffsetF& oldOrigin,
        const RectF& rect, const OffsetF& origin)> onAreaChanged;
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
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode.
     */
    const RefPtr<FrameNode> customNode = FrameNode::CreateFrameNode("one", 1, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<PopupParam> param;

    /**
     * @tc.steps: step2. callback BindPopup.push targetNode is null.
     * @tc.expected: Return expected results..
     */
    ViewAbstract::BindPopup(std::move(param), nullptr, customNode);
    EXPECT_EQ(Container::Current(), nullptr);
}

/**
 * @tc.name: ViewAbstractTest026
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode.
     */
    const RefPtr<FrameNode> customNode = FrameNode::CreateFrameNode("one", 1, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("two", 2, AceType::MakeRefPtr<Pattern>());
    const RefPtr<PopupParam> param;

    /**
     * @tc.steps: step2. callback SetEnabled.push targetNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewAbstract::BindPopup(std::move(param), targetNode, customNode);
    EXPECT_EQ(Container::Current(), nullptr);
}

/**
 * @tc.name: ViewAbstractTest027
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback ShowMenu function.push isContextMenu is false.
     */
    std::shared_ptr<SubwindowManager> subwindow = SubwindowManager::GetInstance();
    ContainerScope sontainerScope(1);

    ViewAbstract::ShowMenu(INDEX, OFFSETF, false);

    /**
     * @tc.expected: Return expected results..
     */
    EXPECT_EQ(Container::Current(), nullptr);
    EXPECT_EQ(sontainerScope.currentId_, INDEX);
}

/**
 * @tc.name: ViewAbstractTest028
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest028, TestSize.Level1)
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
HWTEST_F(ViewAbstractTest, ViewAbstractTest029, TestSize.Level1)
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
    ViewAbstract::SetBackgroundColor(BLUE);
    ViewAbstract::SetBackgroundImage(srcimages);
    ViewAbstract::SetBackgroundImageSize(BACKGROUNDSIZE);
    ViewAbstract::SetBackgroundImagePosition(BACKGROUNDPOSITION);

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
HWTEST_F(ViewAbstractTest, ViewAbstractTest030, TestSize.Level1)
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
HWTEST_F(ViewAbstractTest, ViewAbstractTest031, TestSize.Level1)
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
HWTEST_F(ViewAbstractTest, ViewAbstractTest032, TestSize.Level1)
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
    OffsetT<Dimension> values = {WIDTH, HEIGHT};
    ViewAbstract::SetPosition(values);
    ViewAbstract::SetOffset(values);
    ViewAbstract::MarkAnchor(values);

    ViewAbstract::SetPadding(NG::CalcLength(WIDTH));
    ViewAbstract::SetMargin(NG::CalcLength(WIDTH));
    ViewAbstract::SetBorderRadius(WIDTH);
    ViewAbstract::SetBorderColor(BLUE);
    ViewAbstract::SetBorderWidth(WIDTH);

    auto borderStyle = static_cast<BorderStyle>(INDEX);
    ViewAbstract::SetBorderStyle(borderStyle);

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
HWTEST_F(ViewAbstractTest, ViewAbstractTest033, TestSize.Level1)
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
    OffsetT<Dimension> values = {WIDTH, HEIGHT};
    ViewAbstract::SetPosition(values);
    ViewAbstract::SetOffset(values);
    ViewAbstract::MarkAnchor(values);

    NG::PaddingProperty paddings;
    ViewAbstract::SetPadding(paddings);

    NG::MarginProperty margins;
    ViewAbstract::SetMargin(margins);

    NG::BorderRadiusProperty borderRadius;
    ViewAbstract::SetBorderRadius(borderRadius);

    NG::BorderColorProperty borderColors;
    ViewAbstract::SetBorderColor(borderColors);

    NG::BorderWidthProperty borderWidth;
    ViewAbstract::SetBorderWidth(borderWidth);

    NG::BorderStyleProperty borderStyles;
    ViewAbstract::SetBorderStyle(borderStyles);

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
HWTEST_F(ViewAbstractTest, ViewAbstractTest034, TestSize.Level1)
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
    ViewAbstract::SetBrightness(RADIUS);
    ViewAbstract::SetGrayScale(RADIUS);
    ViewAbstract::SetContrast(RADIUS);
    ViewAbstract::SetSaturate(RADIUS);
    ViewAbstract::SetSepia(RADIUS);
    ViewAbstract::SetInvert(RADIUS);
    ViewAbstract::SetHueRotate(RATIO);
    ViewAbstract::SetColorBlend(BLUE);
    ViewAbstract::SetBackdropBlur(RADIUS);
    ViewAbstract::SetFrontBlur(RADIUS);
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
HWTEST_F(ViewAbstractTest, ViewAbstractTest035, TestSize.Level1)
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
    VectorF scale(1.0f, 1.0f);
    ViewAbstract::SetScale(scale);
    DimensionOffset value = {WIDTH, HEIGHT};
    ViewAbstract::SetPivot(value);
    NG::TranslateOptions values;
    ViewAbstract::SetTranslate(std::move(values));
    Vector4F scales(1.0f, 1.0f, 2.0f, 2.0f);
    ViewAbstract::SetRotate(scales);
    Matrix4 matrix;
    ViewAbstract::SetTransformMatrix(std::move(matrix));

    ShadowStyle style {1};
    Shadow shadow {RATIO, OFFSET, BLUE, style};
    ViewAbstract::SetBackShadow(shadow);
    NG::Gradient gradient;
    ViewAbstract::SetLinearGradient(std::move(gradient));
    ViewAbstract::SetSweepGradient(std::move(gradient));
    ViewAbstract::SetRadialGradient(std::move(gradient));
    TransitionOptions options;
    ViewAbstract::SetTransition(std::move(options));
    RefPtr<BasicShape> basicShape;
    ViewAbstract::SetClipShape(std::move(basicShape));
    ViewAbstract::SetMask(std::move(basicShape));

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
HWTEST_F(ViewAbstractTest, ViewAbstractTest036, TestSize.Level1)
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
    ViewAbstract::SetHasBorderImageSlice(false);
    ViewAbstract::SetHasBorderImageWidth(false);
    ViewAbstract::SetHasBorderImageOutset(false);
    ViewAbstract::SetHasBorderImageRepeat(false);
    ViewAbstract::SetSphericalEffect(RATIO);
    ViewAbstract::SetLightUpEffect(RATIO);
    ViewAbstract::SetForegroundColor(BLUE);
    ViewAbstract::ClearWidthOrHeight(true);

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
HWTEST_F(ViewAbstractTest, ViewAbstractTest037, TestSize.Level1)
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
    RefPtr<ProgressMaskProperty> progress;
    ViewAbstract::SetProgressMask(std::move(progress));
    auto strategy = static_cast<ForegroundColorStrategy>(INDEX);
    ViewAbstract::SetForegroundColorStrategy(std::move(strategy));
    std::vector<ModifierKey> keys;
    ViewAbstract::SetKeyboardShortcut(srcimages, std::move(keys), callback);
    OverlayOptions overlay;
    ViewAbstract::SetOverlay(std::move(overlay));

    /**
     * @tc.expected: Return expected results.
     */
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_FALSE(result);
}
} // namespace OHOS::Ace::NG
