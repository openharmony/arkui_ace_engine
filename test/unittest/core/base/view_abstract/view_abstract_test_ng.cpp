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
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"
#include "core/components/popup/popup_theme.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
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

const OffsetF OFFSETF { 1.0, 1.0 };
const Offset OFFSET { 2.0, 2.0 };
const float RATIO = 1.0f;
const double OPACITYS = 10;
const int32_t TEN = 10;
const int32_t FOUF = 4;
const int32_t INDEX = 1;
const Color BLUE = Color(0xff0000ff);

const BackgroundImageSize BACKGROUNDSIZE { BackgroundImageSizeType::AUTO, 1.0 };
const BackgroundImagePosition BACKGROUNDPOSITION { BackgroundImagePositionType::PERCENT, -1.0,
    BackgroundImagePositionType::PERCENT, 0.0 };

constexpr char TAG_ROOT[] = "root";
constexpr char TAG_CHILD[] = "child";
const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);

std::string srcimages = "common/images/mmm.jpg";
const std::string VALUE_EMPTY = "";
const std::string VALUE_X = "X";
const std::string VALUE_CX = "CX";
ViewAbstractModelNG viewAbstractModelNG;
auto callback = []() { srcimages = "test"; };
int32_t flag = 0;

void CallShowHideFunc()
{
    MockPipelineBase::GetCurrent()->GetOverlayManager()->CallOnShowMenuCallback();
    MockPipelineBase::GetCurrent()->GetOverlayManager()->CallOnHideMenuCallback();
    SubwindowManager::GetInstance()->onShowMenuCallback_();
    SubwindowManager::GetInstance()->onHideMenuCallback_();
}
}; // namespace
class ViewAbstractTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineBase::SetUp();
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
        MockPipelineBase::TearDown();
    }
};

/**
 * @tc.name: ViewAbstractTest001
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest001, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest004, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest009, TestSize.Level1)
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
    OnHoverFunc onHoverEventFunc;
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
    EXPECT_EQ(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
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
    ViewAbstract::SetGeometryTransition(srcimages);
    ViewAbstract::SetOpacity(OPACITYS);
    ViewAbstract::SetZIndex(FOUF);

    OffsetT<Dimension> value = { WIDTH, HEIGHT };
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

    OffsetT<Dimension> value = { WIDTH, HEIGHT };
    ViewAbstract::SetPosition(value);
    ViewAbstract::SetOffset(value);
    ViewAbstract::MarkAnchor(value);
    viewAbstractModelNG.SetScale(-1.0f, -1.0f, 0.0f);

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
    ViewAbstract::SetTranslate(std::move(pttions));
    Matrix4 matrix;
    ViewAbstract::SetTransformMatrix(std::move(matrix));
    ViewAbstract::SetBackdropBlur(RADIUS);
    ViewAbstract::SetFrontBlur(RADIUS);
    ViewAbstract::SetInspectorId(srcimages);

    Vector5F scale(1.0f, 1.0f, 2.0f, 2.0f, 0.0f);
    ViewAbstract::SetRotate(scale);
    ShadowStyle style { 1 };
    Shadow shadow { RATIO, OFFSET, BLUE, style };
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
    ViewAbstract::SetTransformMatrix(std::move(matrix));
    ViewAbstract::SetBackdropBlur(RADIUS);
    ViewAbstract::SetFrontBlur(RADIUS);
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest020, TestSize.Level1)
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
    EXPECT_EQ(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
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
    auto overlayManager = MockPipelineBase::GetCurrent()->GetOverlayManager();
    PopupInfo info = overlayManager->GetPopupInfo(targetNode->GetId());
    info.isCurrentOnShow = true;
    info.popupId = 1;
    overlayManager->ShowPopup(targetNode->GetId(), info);

    /**
     * @tc.steps: step3. Call BindPopup many times.
     * @tc.expected: popupNode in overlayManager of targetNode not null
     */
    ViewAbstract::BindPopup(param, targetNode, customNode);
    ViewAbstract::BindPopup(param, targetNode, customNode);
    auto popupNode = overlayManager->GetPopupInfo(targetNode->GetId()).popupNode;
    ASSERT_NE(popupNode, nullptr);
    popupNode->GetPattern<BubblePattern>()->transitionStatus_ = BubblePattern::TransitionStatus::ENTERING;
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
    param2->SetUseCustomComponent(false);
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
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 0);
    keys.clear();
    /**
     * @tc.steps: step3. call SetKeyboardShortcut with other wrong type.
     * @tc.expected: add fail
     */
    ViewAbstract::SetKeyboardShortcut(VALUE_EMPTY, std::move(keys), callback);
    ViewAbstract::SetKeyboardShortcut(VALUE_CX, std::move(keys), callback);
    ViewAbstract::SetKeyboardShortcut(VALUE_X, std::move(keys), callback);

    /**
     * @tc.steps: step4. and shift in keys and recall SetKeyboardShortcut .
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::ALT);
    ViewAbstract::SetKeyboardShortcut(VALUE_CX, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step5. make other key and recall SetKeyboardShortcut .
     * @tc.expected: add fail
     */
    keys.push_back(ModifierKey::SHIFT);
    ViewAbstract::SetKeyboardShortcut(VALUE_CX, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.push_back(ModifierKey::ALT);
    ViewAbstract::SetKeyboardShortcut(VALUE_CX, std::move(keys), callback);
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
    ViewAbstract::ShowMenu(INDEX, OFFSETF, false);
    ViewAbstract::ShowMenu(INDEX, OFFSETF, true);
    /**
     * @tc.steps: step2. callback SetForegroundBlurStyle and ResetFlexShrink.
     */
    BlurStyleOption bgBlurStyle;
    ViewAbstract::SetForegroundBlurStyle(bgBlurStyle);
    ViewAbstract::ResetFlexShrink();
    /**
     * @tc.steps: step3. SetVisualState in ViewStackProcessor and recall the two function.
     * @tc.expected: the blur radius in render context meet expectations.
     */
    ViewStackProcessor::GetInstance()->SetVisualState(VisualState::FOCUSED);
    ViewAbstract::SetForegroundBlurStyle(bgBlurStyle);
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
    RefPtr<ProgressMaskProperty> progress;
    ViewAbstract::SetProgressMask(std::move(progress));
    auto strategy = static_cast<ForegroundColorStrategy>(INDEX);
    ViewAbstract::SetForegroundColorStrategy(std::move(strategy));
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
    EXPECT_FALSE(result);
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
    ASSERT_NE(MockPipelineBase::GetCurrent()->GetOverlayManager(), nullptr);
    ASSERT_NE(SubwindowManager::GetInstance(), nullptr);
    std::function<void()> flagFunc = []() { flag++; };
    std::vector<NG::OptionParam> params = {};
    std::function<void()> buildFunc;
    MenuParam menuParam;
    /**
     * @tc.steps: step2. call Bind and BindContextMenu multiple times with unless parameters
     * @tc.expected: The show or hide method will not call flagFunc.
     */
    viewAbstractModelNG.BindMenu(std::move(params), std::move(buildFunc), menuParam);
    EXPECT_FALSE(MockPipelineBase::GetCurrent()->GetOverlayManager()->onShowMenuCallback_);
    buildFunc = []() {};
    viewAbstractModelNG.BindMenu(std::move(params), std::move(buildFunc), menuParam);
    EXPECT_TRUE(MockPipelineBase::GetCurrent()->GetOverlayManager()->onShowMenuCallback_);
    params.push_back(OptionParam());
    viewAbstractModelNG.BindMenu(std::move(params), std::move(buildFunc), menuParam);
    viewAbstractModelNG.BindContextMenu(ResponseType::LONG_PRESS, buildFunc, menuParam);
    CallShowHideFunc();
    EXPECT_EQ(flag, 0);
    /**
     * @tc.steps: step3. set appear and disappear and recall BindMenu and BindContextMenu;
     * @tc.expected: The flagFunc call times meet expectations.
     */
    menuParam.onAppear = flagFunc;
    menuParam.onDisappear = flagFunc;
    viewAbstractModelNG.BindMenu(std::move(params), std::move(buildFunc), menuParam);
    viewAbstractModelNG.BindContextMenu(ResponseType::RIGHT_CLICK, buildFunc, menuParam);
    CallShowHideFunc();
    EXPECT_EQ(flag, 4);
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
     * @tc.expected: StopPropagation in mouseInfo is true.
     */
    mouseInfo.SetButton(MouseButton::RIGHT_BUTTON);
    mouseInfo.SetAction(MouseAction::RELEASE);
    inputHub->showMenu_->onMouseCallback_(mouseInfo);
    EXPECT_TRUE(mouseInfo.IsStopPropagation());
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

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
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
    EXPECT_TRUE(callback);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}
} // namespace OHOS::Ace::NG
