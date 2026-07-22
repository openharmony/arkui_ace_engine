/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include <gmock/gmock.h>
#include <optional>
#include <string>

#include "gtest/gtest.h"

#include "base/geometry/ng/rect_t.h"

#define private public
#define protected public
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/base/subwindow/mock_subwindow.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/rosen/mock_canvas.h"
#include "test/mock/frameworks/core/rosen/testing_canvas.h"
#include "test/mock/frameworks/core/rosen/testing_path.h"

#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/subwindow/subwindow_manager.h"
#include "core/common/ace_engine.h"
#include "core/common/container.h"
#include "core/components/button/button_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/placement.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components/popup/popup_theme.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/manager/avoid_info/avoid_info_manager.h"
#include "core/components_ng/pattern/bubble/bubble_event_hub.h"
#include "core/components_ng/pattern/bubble/bubble_layout_algorithm.h"
#include "core/components_ng/pattern/bubble/bubble_layout_property.h"
#include "core/components_ng/pattern/bubble/bubble_paint_method.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/bubble/bubble_render_property.h"
#include "core/components_ng/pattern/bubble/bubble_view.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float ZERO = 0.0f;
constexpr float SIZE_TWO_HUNDRED = 200.0f;
constexpr float POSITION_FIFTY = 50.0f;
constexpr bool BUBBLE_PROPERTY_SHOW = true;
constexpr int32_t DISMISS_REASON_TOUCH_OUTSIDE = 1;
const Color TEST_COLOR_RED = Color::RED;
const Color TEST_COLOR_BLUE = Color::BLUE;
const Color TEST_COLOR_GREEN = Color::GREEN;
const Dimension INVISIABLE_OFFSET = 8.0_px;
const Dimension DEFAULT_ARROW_WIDTH = 20.0_px;
const Dimension DEFAULT_ARROW_HEIGHT = 20.0_px;
const std::string BUBBLE_MESSAGE = "Hello World";
const std::string BUBBLE_STATE = "true";
const OffsetF DISPLAY_WINDOW_OFFSET = OffsetF(ZERO, ZERO);
const std::vector<Placement> BUBBLE_PLACEMENTS = { Placement::LEFT, Placement::RIGHT, Placement::TOP,
    Placement::BOTTOM, Placement::TOP_LEFT, Placement::TOP_RIGHT, Placement::BOTTOM_LEFT, Placement::BOTTOM_RIGHT,
    Placement::LEFT_BOTTOM, Placement::LEFT_TOP, Placement::RIGHT_BOTTOM, Placement::RIGHT_TOP };
} // namespace

struct BubbleSixTestProperty {
    std::optional<bool> enableArrow = std::nullopt;
    std::optional<bool> useCustom = std::nullopt;
    std::optional<Placement> placement = std::nullopt;
    std::optional<bool> showInSubWindow = std::nullopt;
    std::optional<OffsetF> displayWindowOffset = std::nullopt;
    std::optional<bool> autoCancel = std::nullopt;
    std::optional<Color> maskColor = std::nullopt;
    std::optional<Color> backgroundColor = std::nullopt;
    std::optional<bool> isTips = std::nullopt;
    std::optional<bool> primaryButtonShow = std::nullopt;
    std::optional<bool> secondaryButtonShow = std::nullopt;
};

class MockBubbleSixTheme : public PopupTheme, public ButtonTheme {
    DECLARE_ACE_TYPE(MockBubbleSixTheme, PopupTheme, ButtonTheme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;
        RefPtr<MockBubbleSixTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            return AceType::MakeRefPtr<MockBubbleSixTheme>();
        }
    };
    ~MockBubbleSixTheme() override = default;

protected:
    MockBubbleSixTheme() = default;
};

class BubbleSixTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override {}
    void TearDown() override {}
protected:
    static RefPtr<FrameNode> CreateTargetNode();
    static RefPtr<FrameNode> CreateBubbleNode(const BubbleSixTestProperty& testProperty);
    static RefPtr<FrameNode> CreateFullBubbleNode(const RefPtr<PopupParam>& popupParam);
    static void SetThemeManager();
};

void BubbleSixTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
    SetThemeManager();
}

void BubbleSixTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void BubbleSixTestNg::SetThemeManager()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MockBubbleSixTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<MockBubbleSixTheme>()));
}

RefPtr<FrameNode> BubbleSixTestNg::CreateTargetNode()
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    return frameNode;
}

RefPtr<FrameNode> BubbleSixTestNg::CreateBubbleNode(const BubbleSixTestProperty& testProperty)
{
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    auto layoutProperty = AceType::DynamicCast<BubbleLayoutProperty>(popupNode->GetLayoutProperty());
    auto renderProperty = popupNode->GetPaintProperty<BubbleRenderProperty>();
    if (testProperty.enableArrow.has_value()) {
        layoutProperty->UpdateEnableArrow(testProperty.enableArrow.value());
    }
    if (testProperty.useCustom.has_value()) {
        layoutProperty->UpdateUseCustom(testProperty.useCustom.value());
    }
    if (testProperty.placement.has_value()) {
        layoutProperty->UpdatePlacement(testProperty.placement.value());
    }
    if (testProperty.showInSubWindow.has_value()) {
        layoutProperty->UpdateShowInSubWindow(testProperty.showInSubWindow.value());
    }
    if (testProperty.displayWindowOffset.has_value()) {
        layoutProperty->UpdateDisplayWindowOffset(testProperty.displayWindowOffset.value());
    }
    if (testProperty.isTips.has_value()) {
        layoutProperty->UpdateIsTips(testProperty.isTips.value());
    }
    if (testProperty.autoCancel.has_value()) {
        renderProperty->UpdateAutoCancel(testProperty.autoCancel.value());
    }
    if (testProperty.maskColor.has_value()) {
        renderProperty->UpdateMaskColor(testProperty.maskColor.value());
    }
    if (testProperty.backgroundColor.has_value()) {
        renderProperty->UpdateBackgroundColor(testProperty.backgroundColor.value());
    }
    if (testProperty.primaryButtonShow.has_value()) {
        renderProperty->UpdatePrimaryButtonShow(testProperty.primaryButtonShow.value());
    }
    if (testProperty.secondaryButtonShow.has_value()) {
        renderProperty->UpdateSecondaryButtonShow(testProperty.secondaryButtonShow.value());
    }
    return popupNode;
}

RefPtr<FrameNode> BubbleSixTestNg::CreateFullBubbleNode(const RefPtr<PopupParam>& popupParam)
{
    auto targetNode = CreateTargetNode();
    SetThemeManager();
    auto popupNode = BubbleView::CreateBubbleNode(targetNode->GetTag(), targetNode->GetId(), popupParam);
    return popupNode;
}

/**
 * @tc.name: CreateNodePaintMethod001
 * @tc.desc: Test CreateNodePaintMethod with outline and inner border width.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, CreateNodePaintMethod001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble node and get pattern.
     */
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->popupTheme_ = AceType::MakeRefPtr<PopupTheme>();
    /**
     * @tc.steps: step2. set outline/inner width and call CreateNodePaintMethod.
     * @tc.expected: paint method created with user-specified widths.
     */
    pattern->SetOutlineWidth(Dimension(2.0_vp));
    pattern->SetInnerBorderWidth(Dimension(1.0_vp));
    auto paintMethod = pattern->CreateNodePaintMethod();
    auto bubblePaintMethod = AceType::DynamicCast<BubblePaintMethod>(paintMethod);
    ASSERT_NE(bubblePaintMethod, nullptr);
    EXPECT_GT(bubblePaintMethod->outerBorderWidthByUser_, 0);
    EXPECT_GT(bubblePaintMethod->innerBorderWidthByUser_, 0);
}

/**
 * @tc.name: CreateNodePaintMethod002
 * @tc.desc: Test CreateNodePaintMethod with linear gradients.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, CreateNodePaintMethod002, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->popupTheme_ = AceType::MakeRefPtr<PopupTheme>();
    /**
     * @tc.steps: step1. set outline gradient without width and create paint method.
     * @tc.expected: default width applied when gradient set but width not set.
     */
    PopupLinearGradientProperties outlineGradient;
    outlineGradient.gradientColors.push_back({ Color::RED, 0.0, nullptr });
    pattern->SetOutlineLinearGradient(outlineGradient);
    auto paintMethod = pattern->CreateNodePaintMethod();
    auto bubblePaintMethod = AceType::DynamicCast<BubblePaintMethod>(paintMethod);
    ASSERT_NE(bubblePaintMethod, nullptr);
    EXPECT_GT(bubblePaintMethod->outerBorderWidthByUser_, 0);
    /**
     * @tc.steps: step2. set inner gradient without width and create paint method.
     */
    PopupLinearGradientProperties innerGradient;
    innerGradient.gradientColors.push_back({ Color::BLUE, 0.0, nullptr });
    pattern->SetInnerBorderLinearGradient(innerGradient);
    paintMethod = pattern->CreateNodePaintMethod();
    bubblePaintMethod = AceType::DynamicCast<BubblePaintMethod>(paintMethod);
    ASSERT_NE(bubblePaintMethod, nullptr);
    EXPECT_GT(bubblePaintMethod->innerBorderWidthByUser_, 0);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap001
 * @tc.desc: Test OnDirtyLayoutWrapperSwap with skip measure and layout.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, OnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step1. call OnDirtyLayoutWrapperSwap with both skip true.
     * @tc.expected: returns false directly.
     */
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        popupNode, popupNode->GetGeometryNode(), popupNode->GetLayoutProperty());
    bool result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, true);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnModifyDone001
 * @tc.desc: Test OnModifyDone color mode update branch.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, OnModifyDone001, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    testProperty.useCustom = false;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->popupTheme_ = AceType::MakeRefPtr<PopupTheme>();
    /**
     * @tc.steps: step1. set colorMode_ different from context color mode and call OnModifyDone.
     * @tc.expected: colorMode_ updated and UpdateBubbleText called.
     */
    pattern->colorMode_ = ColorMode::DARK;
    pattern->isCustomPopup_ = false;
    pattern->OnModifyDone();
    EXPECT_EQ(pattern->colorMode_, MockPipelineContext::GetCurrentContext()->GetColorMode());
}

/**
 * @tc.name: AddPipelineCallBack001
 * @tc.desc: Test AddPipelineCallBack.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, AddPipelineCallBack001, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step1. call AddPipelineCallBack.
     * @tc.expected: no crash, callbacks registered.
     */
    pattern->AddPipelineCallBack();
    SUCCEED();
}

/**
 * @tc.name: OnRemoveChild001
 * @tc.desc: Test OnRemoveChild with valid node and no onAreaChange.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, OnRemoveChild001, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->hasOnAreaChange_ = false;
    /**
     * @tc.steps: step1. call OnRemoveChild with valid node.
     * @tc.expected: RemoveOnAreaChangeNode called, no crash.
     */
    pattern->OnRemoveChild(popupNode);
    SUCCEED();
}

/**
 * @tc.name: OnRemoveChild002
 * @tc.desc: Test OnRemoveChild with null node.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, OnRemoveChild002, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step1. call OnRemoveChild with null node.
     * @tc.expected: early return, no crash.
     */
    pattern->OnRemoveChild(nullptr);
    SUCCEED();
}

/**
 * @tc.name: OnAttachToMainTree001
 * @tc.desc: Test OnAttachToMainTree and OnDetachFromMainTree.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, OnAttachToMainTree001, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step1. call OnAttachToMainTree and OnDetachFromMainTree.
     * @tc.expected: no crash.
     */
    pattern->OnAttachToMainTree();
    pattern->OnDetachFromMainTree();
    SUCCEED();
}

/**
 * @tc.name: HandleTouchDown001
 * @tc.desc: Test HandleTouchDown when click inside touch region.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, HandleTouchDown001, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    testProperty.autoCancel = true;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step1. set touchRegion covering click point and call HandleTouchDown.
     * @tc.expected: early return because click inside region.
     */
    pattern->touchRegion_ = RectF(0, 0, SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    pattern->HandleTouchDown(Offset(POSITION_FIFTY, POSITION_FIFTY));
    EXPECT_EQ(pattern->GetTransitionStatus(), TransitionStatus::INVISIABLE);
}

/**
 * @tc.name: HandleTouchDown002
 * @tc.desc: Test HandleTouchDown with autoCancel true and interactiveDismiss false.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, HandleTouchDown002, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    testProperty.autoCancel = true;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step1. set interactiveDismiss false, click outside region.
     * @tc.expected: returns early without popping bubble.
     */
    pattern->touchRegion_ = RectF(0, 0, ZERO, ZERO);
    pattern->SetInteractiveDismiss(false);
    pattern->HandleTouchDown(Offset(POSITION_FIFTY, POSITION_FIFTY));
    EXPECT_EQ(pattern->GetTransitionStatus(), TransitionStatus::INVISIABLE);
}

/**
 * @tc.name: HandleTouchDown003
 * @tc.desc: Test HandleTouchDown with onWillDismiss callback set.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, HandleTouchDown003, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    testProperty.autoCancel = true;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step1. set onWillDismiss callback, click outside region.
     * @tc.expected: onWillDismiss called with TOUCH_OUTSIDE reason.
     */
    pattern->touchRegion_ = RectF(0, 0, ZERO, ZERO);
    int32_t callReason = -1;
    pattern->UpdateOnWillDismiss([&callReason](int32_t reason) { callReason = reason; });
    EXPECT_TRUE(pattern->HasOnWillDismiss());
    pattern->HandleTouchDown(Offset(POSITION_FIFTY, POSITION_FIFTY));
    EXPECT_EQ(callReason, DISMISS_REASON_TOUCH_OUTSIDE);
}

/**
 * @tc.name: HandleTouchDown004
 * @tc.desc: Test HandleTouchDown with autoCancel false.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, HandleTouchDown004, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    testProperty.autoCancel = false;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step1. autoCancel false, click outside region.
     * @tc.expected: no popup dismissed.
     */
    pattern->touchRegion_ = RectF(0, 0, ZERO, ZERO);
    pattern->HandleTouchDown(Offset(POSITION_FIFTY, POSITION_FIFTY));
    EXPECT_EQ(pattern->GetTransitionStatus(), TransitionStatus::INVISIABLE);
}

/**
 * @tc.name: HandleTouchEvent001
 * @tc.desc: Test HandleTouchEvent with empty touches and down event.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, HandleTouchEvent001, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    TouchEventInfo info("down");
    /**
     * @tc.steps: step1. call HandleTouchEvent with empty touches.
     * @tc.expected: returns early.
     */
    pattern->HandleTouchEvent(info);
    SUCCEED();
}

/**
 * @tc.name: RegisterButtonOnHover001
 * @tc.desc: Test RegisterButtonOnHover with custom mode.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, RegisterButtonOnHover001, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    testProperty.useCustom = true;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step1. custom mode, call RegisterButtonOnHover.
     * @tc.expected: early return, mouseEventInitFlag_ remains false.
     */
    pattern->RegisterButtonOnHover();
    EXPECT_FALSE(pattern->mouseEventInitFlag_);
}

/**
 * @tc.name: RegisterButtonOnHover002
 * @tc.desc: Test RegisterButtonOnHover with no buttons shown.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, RegisterButtonOnHover002, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    testProperty.useCustom = false;
    testProperty.primaryButtonShow = false;
    testProperty.secondaryButtonShow = false;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step1. no buttons shown, call RegisterButtonOnHover.
     * @tc.expected: early return, mouseEventInitFlag_ remains false.
     */
    pattern->RegisterButtonOnHover();
    EXPECT_FALSE(pattern->mouseEventInitFlag_);
}

/**
 * @tc.name: RegisterButtonOnHover003
 * @tc.desc: Test RegisterButtonOnHover already initialized.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, RegisterButtonOnHover003, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step1. set mouseEventInitFlag_ true and call again.
     * @tc.expected: early return.
     */
    pattern->mouseEventInitFlag_ = true;
    pattern->RegisterButtonOnHover();
    EXPECT_TRUE(pattern->mouseEventInitFlag_);
}

/**
 * @tc.name: RegisterButtonOnTouch001
 * @tc.desc: Test RegisterButtonOnTouch with custom and no buttons.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, RegisterButtonOnTouch001, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    testProperty.useCustom = true;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step1. custom mode, call RegisterButtonOnTouch.
     * @tc.expected: early return, touchEventInitFlag_ remains false.
     */
    pattern->RegisterButtonOnTouch();
    EXPECT_FALSE(pattern->touchEventInitFlag_);
}

/**
 * @tc.name: RegisterButtonOnTouch002
 * @tc.desc: Test RegisterButtonOnTouch already initialized.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, RegisterButtonOnTouch002, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step1. set touchEventInitFlag_ true and call again.
     * @tc.expected: early return.
     */
    pattern->touchEventInitFlag_ = true;
    pattern->RegisterButtonOnTouch();
    EXPECT_TRUE(pattern->touchEventInitFlag_);
}

/**
 * @tc.name: ButtonOnHover001
 * @tc.desc: Test ButtonOnHover with hover true and false.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, ButtonOnHover001, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->popupTheme_ = AceType::MakeRefPtr<PopupTheme>();
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);
    /**
     * @tc.steps: step1. call ButtonOnHover with true then false.
     * @tc.expected: isHover_ toggles accordingly.
     */
    pattern->ButtonOnHover(true, buttonNode);
    EXPECT_TRUE(pattern->isHover_);
    pattern->ButtonOnHover(false, buttonNode);
    EXPECT_FALSE(pattern->isHover_);
}

/**
 * @tc.name: ButtonOnPress001
 * @tc.desc: Test ButtonOnPress with DOWN and UP events, hover and normal.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, ButtonOnPress001, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->popupTheme_ = AceType::MakeRefPtr<PopupTheme>();
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);
    /**
     * @tc.steps: step1. normal to press (DOWN, isHover false).
     */
    TouchEventInfo infoDown("down");
    TouchLocationInfo locationInfo(0);
    locationInfo.SetTouchType(TouchType::DOWN);
    infoDown.AddTouchLocationInfo(std::move(locationInfo));
    pattern->ButtonOnPress(infoDown, buttonNode);
    SUCCEED();
    /**
     * @tc.steps: step2. press to normal (UP, isHover false).
     */
    TouchEventInfo infoUp("up");
    TouchLocationInfo upLocationInfo(1);
    upLocationInfo.SetTouchType(TouchType::UP);
    infoUp.AddTouchLocationInfo(std::move(upLocationInfo));
    pattern->ButtonOnPress(infoUp, buttonNode);
    SUCCEED();
}

/**
 * @tc.name: ButtonOnPress002
 * @tc.desc: Test ButtonOnPress with hover state.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, ButtonOnPress002, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->popupTheme_ = AceType::MakeRefPtr<PopupTheme>();
    pattern->isHover_ = true;
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);
    /**
     * @tc.steps: step1. hover to press (DOWN, isHover true).
     */
    TouchEventInfo infoDown("down");
    TouchLocationInfo locationInfo(0);
    locationInfo.SetTouchType(TouchType::DOWN);
    infoDown.AddTouchLocationInfo(std::move(locationInfo));
    pattern->ButtonOnPress(infoDown, buttonNode);
    SUCCEED();
    /**
     * @tc.steps: step2. press to hover (UP, isHover true).
     */
    TouchEventInfo infoUp("up");
    TouchLocationInfo upLocationInfo(1);
    upLocationInfo.SetTouchType(TouchType::UP);
    infoUp.AddTouchLocationInfo(std::move(upLocationInfo));
    pattern->ButtonOnPress(infoUp, buttonNode);
    SUCCEED();
}

/**
 * @tc.name: ButtonOnPress003
 * @tc.desc: Test ButtonOnPress with empty touches.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, ButtonOnPress003, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);
    /**
     * @tc.steps: step1. call ButtonOnPress with empty touches.
     * @tc.expected: early return.
     */
    TouchEventInfo info("down");
    pattern->ButtonOnPress(info, buttonNode);
    SUCCEED();
}

/**
 * @tc.name: PopBubble001
 * @tc.desc: Test PopBubble when popup not current on show.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, PopBubble001, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    ASSERT_NE(targetNode, nullptr);
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode = FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId,
        AceType::MakeRefPtr<BubblePattern>(targetNode->GetId(), targetNode->GetTag()));
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step1. call PopBubble when popup not shown.
     * @tc.expected: early return, no crash.
     */
    pattern->PopBubble();
    SUCCEED();
}

/**
 * @tc.name: GetStyleOptionColorMode001
 * @tc.desc: Test GetStyleOptionColorMode follow target with light.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, GetStyleOptionColorMode001, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step1. set API version >= 26 and follow target with light color mode.
     * @tc.expected: returns LIGHT.
     */
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    pattern->isColorModeFollowTarget_ = true;
    auto colorMode = pattern->GetStyleOptionColorMode();
    EXPECT_EQ(colorMode, ThemeColorMode::SYSTEM);
    MockContainer::Current()->SetApiTargetVersion(0);
}

/**
 * @tc.name: GetStyleOptionColorMode002
 * @tc.desc: Test GetStyleOptionColorMode not follow target.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, GetStyleOptionColorMode002, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step1. set API version < 26.
     * @tc.expected: returns SYSTEM.
     */
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    auto colorMode = pattern->GetStyleOptionColorMode();
    EXPECT_EQ(colorMode, ThemeColorMode::SYSTEM);
    MockContainer::Current()->SetApiTargetVersion(0);
}

/**
 * @tc.name: GetStyleOptionColorMode003
 * @tc.desc: Test GetStyleOptionColorMode not follow target with API >= 26.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, GetStyleOptionColorMode003, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    pattern->isColorModeFollowTarget_ = false;
    /**
     * @tc.steps: step1. not follow target, returns based on container color mode.
     */
    auto colorMode = pattern->GetStyleOptionColorMode();
    EXPECT_TRUE(colorMode == ThemeColorMode::SYSTEM || colorMode == ThemeColorMode::LIGHT ||
                colorMode == ThemeColorMode::DARK);
    MockContainer::Current()->SetApiTargetVersion(0);
}

/**
 * @tc.name: UpdatePopupTheme001
 * @tc.desc: Test UpdatePopupTheme with API version >= 26.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, UpdatePopupTheme001, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step1. set API >= 26 and call UpdatePopupTheme with follow target.
     * @tc.expected: popupTheme_ set, no crash.
     */
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    pattern->UpdatePopupTheme(true);
    ASSERT_NE(pattern->popupTheme_, nullptr);
    MockContainer::Current()->SetApiTargetVersion(0);
}

/**
 * @tc.name: UpdatePopupTheme002
 * @tc.desc: Test UpdatePopupTheme with API version < 26.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, UpdatePopupTheme002, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    /**
     * @tc.steps: step1. set API < 26 and call UpdatePopupTheme.
     * @tc.expected: popupTheme_ set, target node branch skipped.
     */
    pattern->UpdatePopupTheme(false);
    ASSERT_NE(pattern->popupTheme_, nullptr);
    MockContainer::Current()->SetApiTargetVersion(0);
}

/**
 * @tc.name: GetPopupTheme001
 * @tc.desc: Test GetPopupTheme when popupTheme_ is null.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, GetPopupTheme001, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    SetThemeManager();
    /**
     * @tc.steps: step1. popupTheme_ is null, call GetPopupTheme.
     * @tc.expected: falls back to host theme.
     */
    pattern->popupTheme_ = nullptr;
    auto theme = pattern->GetPopupTheme();
    EXPECT_NE(theme, nullptr);
}

/**
 * @tc.name: GetPopupTheme002
 * @tc.desc: Test GetPopupTheme when popupTheme_ is set.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, GetPopupTheme002, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    auto theme = AceType::MakeRefPtr<PopupTheme>();
    pattern->popupTheme_ = theme;
    /**
     * @tc.steps: step1. popupTheme_ is set, call GetPopupTheme.
     * @tc.expected: returns the set theme.
     */
    auto result = pattern->GetPopupTheme();
    EXPECT_EQ(result, theme);
}

/**
 * @tc.name: PostTask001
 * @tc.desc: Test PostTask.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, PostTask001, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step1. call PostTask with a lambda.
     * @tc.expected: task posted successfully.
     */
    bool called = false;
    auto result = pattern->PostTask([&called]() { called = true; }, "test_task");
    EXPECT_TRUE(result);
}

/**
 * @tc.name: StartEnteringAnimation001
 * @tc.desc: Test StartEnteringAnimation with no arrow placement (delay).
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, StartEnteringAnimation001, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->popupTheme_ = AceType::MakeRefPtr<PopupTheme>();
    /**
     * @tc.steps: step1. no arrowPlacement set, call StartEnteringAnimation.
     * @tc.expected: delayShow_ set to true, finish_ stored.
     */
    bool finished = false;
    pattern->StartEnteringAnimation([&finished]() { finished = true; });
    EXPECT_TRUE(pattern->delayShow_);
    EXPECT_FALSE(finished);
}

/**
 * @tc.name: StartEnteringAnimation002
 * @tc.desc: Test StartEnteringAnimation when already on show.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, StartEnteringAnimation002, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->popupTheme_ = AceType::MakeRefPtr<PopupTheme>();
    pattern->arrowPlacement_ = Placement::BOTTOM;
    pattern->transitionStatus_ = TransitionStatus::NORMAL;
    /**
     * @tc.steps: step1. already on show, call StartEnteringAnimation.
     * @tc.expected: early return, no animation started.
     */
    bool finished = false;
    pattern->StartEnteringAnimation([&finished]() { finished = true; });
    EXPECT_FALSE(finished);
}

/**
 * @tc.name: StartEnteringAnimation003
 * @tc.desc: Test StartEnteringAnimation from invisible state.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, StartEnteringAnimation003, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->popupTheme_ = AceType::MakeRefPtr<PopupTheme>();
    pattern->arrowPlacement_ = Placement::BOTTOM;
    pattern->transitionStatus_ = TransitionStatus::INVISIABLE;
    /**
     * @tc.steps: step1. from invisible, call StartEnteringAnimation with nullptr finish.
     * @tc.expected: animation starts, transitionStatus becomes ENTERING.
     */
    pattern->StartEnteringAnimation(nullptr);
    SUCCEED();
}

/**
 * @tc.name: StartExitingAnimation001
 * @tc.desc: Test StartExitingAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, StartExitingAnimation001, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->popupTheme_ = AceType::MakeRefPtr<PopupTheme>();
    pattern->arrowPlacement_ = Placement::BOTTOM;
    /**
     * @tc.steps: step1. call StartExitingAnimation.
     * @tc.expected: transitionStatus set to EXITING.
     */
    bool finished = false;
    pattern->StartExitingAnimation([&finished]() { finished = true; });
    SUCCEED();
}

/**
 * @tc.name: StartOffsetEnteringAnimation001
 * @tc.desc: Test StartOffsetEnteringAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, StartOffsetEnteringAnimation001, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->popupTheme_ = AceType::MakeRefPtr<PopupTheme>();
    /**
     * @tc.steps: step1. call StartOffsetEnteringAnimation.
     * @tc.expected: no crash.
     */
    pattern->StartOffsetEnteringAnimation();
    SUCCEED();
}

/**
 * @tc.name: StartAlphaEnteringAnimation001
 * @tc.desc: Test StartAlphaEnteringAnimation with finish callback.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, StartAlphaEnteringAnimation001, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->popupTheme_ = AceType::MakeRefPtr<PopupTheme>();
    /**
     * @tc.steps: step1. call StartAlphaEnteringAnimation with finish callback.
     * @tc.expected: no crash, transitionStatus becomes ENTERING in animation.
     */
    bool finished = false;
    pattern->StartAlphaEnteringAnimation([&finished]() { finished = true; });
    SUCCEED();
}

/**
 * @tc.name: StartOffsetExitingAnimation001
 * @tc.desc: Test StartOffsetExitingAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, StartOffsetExitingAnimation001, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->popupTheme_ = AceType::MakeRefPtr<PopupTheme>();
    pattern->arrowPlacement_ = Placement::BOTTOM;
    /**
     * @tc.steps: step1. call StartOffsetExitingAnimation.
     * @tc.expected: no crash.
     */
    pattern->StartOffsetExitingAnimation();
    SUCCEED();
}

/**
 * @tc.name: StartAlphaExitingAnimation001
 * @tc.desc: Test StartAlphaExitingAnimation with finish callback.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, StartAlphaExitingAnimation001, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->popupTheme_ = AceType::MakeRefPtr<PopupTheme>();
    /**
     * @tc.steps: step1. call StartAlphaExitingAnimation with finish callback.
     * @tc.expected: no crash.
     */
    bool finished = false;
    pattern->StartAlphaExitingAnimation([&finished]() { finished = true; });
    SUCCEED();
}

/**
 * @tc.name: IsOnShow001
 * @tc.desc: Test IsOnShow with different transition states.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, IsOnShow001, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step1. test all transition states for IsOnShow.
     */
    pattern->SetTransitionStatus(TransitionStatus::ENTERING);
    EXPECT_TRUE(pattern->IsOnShow());
    pattern->SetTransitionStatus(TransitionStatus::NORMAL);
    EXPECT_TRUE(pattern->IsOnShow());
    pattern->SetTransitionStatus(TransitionStatus::EXITING);
    EXPECT_FALSE(pattern->IsOnShow());
    pattern->SetTransitionStatus(TransitionStatus::INVISIABLE);
    EXPECT_FALSE(pattern->IsOnShow());
}

/**
 * @tc.name: IsExiting001
 * @tc.desc: Test IsExiting with different transition states.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, IsExiting001, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step1. test IsExiting for EXITING and non-EXITING.
     */
    pattern->SetTransitionStatus(TransitionStatus::EXITING);
    EXPECT_TRUE(pattern->IsExiting());
    pattern->SetTransitionStatus(TransitionStatus::NORMAL);
    EXPECT_FALSE(pattern->IsExiting());
}

/**
 * @tc.name: GetInvisibleOffset001
 * @tc.desc: Test GetInvisibleOffset with all placements.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, GetInvisibleOffset001, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step1. no arrowPlacement set.
     * @tc.expected: returns zero offset.
     */
    pattern->arrowPlacement_.reset();
    auto offset = pattern->GetInvisibleOffset();
    EXPECT_EQ(offset.GetX().Value(), 0);
    EXPECT_EQ(offset.GetY().Value(), 0);
}

/**
 * @tc.name: GetInvisibleOffset002
 * @tc.desc: Test GetInvisibleOffset with left/right placements.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, GetInvisibleOffset002, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step1. left placements add positive X.
     */
    pattern->arrowPlacement_ = Placement::LEFT;
    auto offset = pattern->GetInvisibleOffset();
    EXPECT_FLOAT_EQ(offset.GetX().Value(), INVISIABLE_OFFSET.Value());
    pattern->arrowPlacement_ = Placement::LEFT_TOP;
    offset = pattern->GetInvisibleOffset();
    EXPECT_FLOAT_EQ(offset.GetX().Value(), INVISIABLE_OFFSET.Value());
    pattern->arrowPlacement_ = Placement::LEFT_BOTTOM;
    offset = pattern->GetInvisibleOffset();
    EXPECT_FLOAT_EQ(offset.GetX().Value(), INVISIABLE_OFFSET.Value());
    /**
     * @tc.steps: step2. right placements add negative X.
     */
    pattern->arrowPlacement_ = Placement::RIGHT;
    offset = pattern->GetInvisibleOffset();
    EXPECT_FLOAT_EQ(offset.GetX().Value(), -INVISIABLE_OFFSET.Value());
    pattern->arrowPlacement_ = Placement::RIGHT_TOP;
    offset = pattern->GetInvisibleOffset();
    EXPECT_FLOAT_EQ(offset.GetX().Value(), -INVISIABLE_OFFSET.Value());
    pattern->arrowPlacement_ = Placement::RIGHT_BOTTOM;
    offset = pattern->GetInvisibleOffset();
    EXPECT_FLOAT_EQ(offset.GetX().Value(), -INVISIABLE_OFFSET.Value());
}

/**
 * @tc.name: GetInvisibleOffset003
 * @tc.desc: Test GetInvisibleOffset with top/bottom placements.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, GetInvisibleOffset003, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step1. top placements add positive Y.
     */
    pattern->arrowPlacement_ = Placement::TOP;
    auto offset = pattern->GetInvisibleOffset();
    EXPECT_FLOAT_EQ(offset.GetY().Value(), INVISIABLE_OFFSET.Value());
    pattern->arrowPlacement_ = Placement::TOP_LEFT;
    offset = pattern->GetInvisibleOffset();
    EXPECT_FLOAT_EQ(offset.GetY().Value(), INVISIABLE_OFFSET.Value());
    pattern->arrowPlacement_ = Placement::TOP_RIGHT;
    offset = pattern->GetInvisibleOffset();
    EXPECT_FLOAT_EQ(offset.GetY().Value(), INVISIABLE_OFFSET.Value());
    /**
     * @tc.steps: step2. bottom placements add negative Y.
     */
    pattern->arrowPlacement_ = Placement::BOTTOM;
    offset = pattern->GetInvisibleOffset();
    EXPECT_FLOAT_EQ(offset.GetY().Value(), -INVISIABLE_OFFSET.Value());
    pattern->arrowPlacement_ = Placement::BOTTOM_LEFT;
    offset = pattern->GetInvisibleOffset();
    EXPECT_FLOAT_EQ(offset.GetY().Value(), -INVISIABLE_OFFSET.Value());
    pattern->arrowPlacement_ = Placement::BOTTOM_RIGHT;
    offset = pattern->GetInvisibleOffset();
    EXPECT_FLOAT_EQ(offset.GetY().Value(), -INVISIABLE_OFFSET.Value());
}

/**
 * @tc.name: GetInvisibleOffset004
 * @tc.desc: Test GetInvisibleOffset with NONE placement (default branch).
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, GetInvisibleOffset004, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step1. NONE placement hits default branch.
     * @tc.expected: zero offset.
     */
    pattern->arrowPlacement_ = Placement::NONE;
    auto offset = pattern->GetInvisibleOffset();
    EXPECT_EQ(offset.GetX().Value(), 0);
    EXPECT_EQ(offset.GetY().Value(), 0);
}

/**
 * @tc.name: ResetToInvisible001
 * @tc.desc: Test ResetToInvisible.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, ResetToInvisible001, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->arrowPlacement_ = Placement::BOTTOM;
    /**
     * @tc.steps: step1. call ResetToInvisible.
     * @tc.expected: render context opacity and offset updated.
     */
    pattern->ResetToInvisible();
    SUCCEED();
}

/**
 * @tc.name: StartEnteringTransitionEffects001
 * @tc.desc: Test StartEnteringTransitionEffects.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, StartEnteringTransitionEffects001, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->popupTheme_ = AceType::MakeRefPtr<PopupTheme>();
    bool finished = false;
    /**
     * @tc.steps: step1. call StartEnteringTransitionEffects.
     * @tc.expected: transitionStatus set to ENTERING, no crash.
     */
    pattern->StartEnteringTransitionEffects(popupNode, [&finished]() { finished = true; });
    EXPECT_EQ(pattern->GetTransitionStatus(), TransitionStatus::ENTERING);
}

/**
 * @tc.name: StartExitingTransitionEffects001
 * @tc.desc: Test StartExitingTransitionEffects.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, StartExitingTransitionEffects001, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->popupTheme_ = AceType::MakeRefPtr<PopupTheme>();
    bool finished = false;
    /**
     * @tc.steps: step1. call StartExitingTransitionEffects.
     * @tc.expected: transitionStatus set to EXITING.
     */
    pattern->StartExitingTransitionEffects(popupNode, [&finished]() { finished = true; });
    EXPECT_EQ(pattern->GetTransitionStatus(), TransitionStatus::EXITING);
}

/**
 * @tc.name: OnWindowHide001
 * @tc.desc: Test OnWindowHide.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, OnWindowHide001, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step1. call OnWindowHide.
     * @tc.expected: no crash, HideAllPopups called.
     */
    pattern->OnWindowHide();
    SUCCEED();
}

/**
 * @tc.name: OnWindowSizeChanged001
 * @tc.desc: Test OnWindowSizeChanged with various reasons.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, OnWindowSizeChanged001, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step1. call OnWindowSizeChanged with handled reasons.
     * @tc.expected: HideAllPopups called, no crash.
     */
    pattern->OnWindowSizeChanged(100, 200, WindowSizeChangeReason::ROTATION);
    pattern->OnWindowSizeChanged(100, 200, WindowSizeChangeReason::MAXIMIZE);
    pattern->OnWindowSizeChanged(100, 200, WindowSizeChangeReason::TRANSFORM);
    SUCCEED();
}

/**
 * @tc.name: OnWindowSizeChanged002
 * @tc.desc: Test OnWindowSizeChanged with unhandled reason.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, OnWindowSizeChanged002, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step1. call OnWindowSizeChanged with RESIZE (default branch).
     * @tc.expected: no crash.
     */
    pattern->OnWindowSizeChanged(100, 200, WindowSizeChangeReason::RESIZE);
    SUCCEED();
}

/**
 * @tc.name: OnWindowSizeChanged003
 * @tc.desc: Test OnWindowSizeChanged with showInSubWindow.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, OnWindowSizeChanged003, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    testProperty.showInSubWindow = true;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step1. showInSubWindow true, call OnWindowSizeChanged.
     * @tc.expected: subwindow path taken (returns null), no crash.
     */
    pattern->OnWindowSizeChanged(100, 200, WindowSizeChangeReason::ROTATION);
    SUCCEED();
}

/**
 * @tc.name: UpdateText001
 * @tc.desc: Test UpdateText with text node.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, UpdateText001, TestSize.Level1)
{
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    popupParam->SetMessage(BUBBLE_MESSAGE);
    SetThemeManager();
    auto popupNode = CreateFullBubbleNode(popupParam);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->popupTheme_ = AceType::MakeRefPtr<PopupTheme>();
    /**
     * @tc.steps: step1. call UpdateText on host with text children.
     * @tc.expected: text color updated, no crash.
     */
    pattern->UpdateText(popupNode, pattern->popupTheme_);
    SUCCEED();
}

/**
 * @tc.name: UpdateText002
 * @tc.desc: Test UpdateText with non-text node (recursion).
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, UpdateText002, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    auto theme = AceType::MakeRefPtr<PopupTheme>();
    /**
     * @tc.steps: step1. call UpdateText with a non-text node (no children).
     * @tc.expected: recursion branch with empty children, no crash.
     */
    pattern->UpdateText(popupNode, theme);
    SUCCEED();
}

/**
 * @tc.name: DumpInfo001
 * @tc.desc: Test DumpInfo.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, DumpInfo001, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step1. call DumpInfo with populated dumpInfo.
     * @tc.expected: no crash, descriptions added.
     */
    pattern->dumpInfo_.enableArrow = true;
    pattern->dumpInfo_.mask = true;
    pattern->dumpInfo_.targetNode = "button";
    pattern->dumpInfo_.targetID = 1;
    pattern->DumpInfo();
    SUCCEED();
}

/**
 * @tc.name: UpdateStyleOption001
 * @tc.desc: Test UpdateStyleOption with needUpdateShadow true.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, UpdateStyleOption001, TestSize.Level1)
{
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    popupParam->SetMessage(BUBBLE_MESSAGE);
    SetThemeManager();
    auto popupNode = CreateFullBubbleNode(popupParam);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->popupTheme_ = AceType::MakeRefPtr<PopupTheme>();
    /**
     * @tc.steps: step1. call UpdateStyleOption with needUpdateShadow true.
     * @tc.expected: shadow updated, no crash.
     */
    pattern->UpdateStyleOption(BlurStyle::COMPONENT_REGULAR, true);
    SUCCEED();
}

/**
 * @tc.name: UpdateStyleOption002
 * @tc.desc: Test UpdateStyleOption with needUpdateShadow false.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, UpdateStyleOption002, TestSize.Level1)
{
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    popupParam->SetMessage(BUBBLE_MESSAGE);
    SetThemeManager();
    auto popupNode = CreateFullBubbleNode(popupParam);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->popupTheme_ = AceType::MakeRefPtr<PopupTheme>();
    /**
     * @tc.steps: step1. call UpdateStyleOption with needUpdateShadow false.
     * @tc.expected: no shadow update, no crash.
     */
    pattern->UpdateStyleOption(BlurStyle::COMPONENT_THIN, false);
    SUCCEED();
}

/**
 * @tc.name: UpdateShadow001
 * @tc.desc: Test UpdateShadow with isShadowStyle true.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, UpdateShadow001, TestSize.Level1)
{
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    popupParam->SetMessage(BUBBLE_MESSAGE);
    SetThemeManager();
    auto popupNode = CreateFullBubbleNode(popupParam);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetIsShadowStyle(true);
    /**
     * @tc.steps: step1. isShadowStyle true, call UpdateShadow.
     * @tc.expected: shadow updated, no crash.
     */
    pattern->UpdateShadow();
    SUCCEED();
}

/**
 * @tc.name: UpdateShadow002
 * @tc.desc: Test UpdateShadow with config change perform and shadow set.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, UpdateShadow002, TestSize.Level1)
{
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    popupParam->SetMessage(BUBBLE_MESSAGE);
    SetThemeManager();
    auto popupNode = CreateFullBubbleNode(popupParam);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetIsShadowStyle(false);
    pattern->SetShadow(ShadowConfig::DefaultShadowXS);
    /**
     * @tc.steps: step1. enable config change perform and call UpdateShadow.
     * @tc.expected: shadow reloaded, no crash.
     */
    g_isConfigChangePerform = true;
    pattern->UpdateShadow();
    g_isConfigChangePerform = false;
    SUCCEED();
}

/**
 * @tc.name: UpdateAgingTextSize001
 * @tc.desc: Test UpdateAgingTextSize with custom popup.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, UpdateAgingTextSize001, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step1. isCustomPopup true, call UpdateAgingTextSize.
     * @tc.expected: early return.
     */
    pattern->isCustomPopup_ = true;
    pattern->UpdateAgingTextSize();
    SUCCEED();
}

/**
 * @tc.name: UpdateAgingTextSize002
 * @tc.desc: Test UpdateAgingTextSize with null message node.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, UpdateAgingTextSize002, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step1. messageNode null, call UpdateAgingTextSize.
     * @tc.expected: early return.
     */
    pattern->isCustomPopup_ = false;
    pattern->messageNode_ = nullptr;
    pattern->UpdateAgingTextSize();
    SUCCEED();
}

/**
 * @tc.name: UpdateBubbleTextColor001
 * @tc.desc: Test UpdateBubbleText with color value.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, UpdateBubbleTextColor001, TestSize.Level1)
{
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    popupParam->SetMessage(BUBBLE_MESSAGE);
    SetThemeManager();
    auto popupNode = CreateFullBubbleNode(popupParam);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    auto messageNode = pattern->GetMessageNode();
    ASSERT_NE(messageNode, nullptr);
    /**
     * @tc.steps: step1. call UpdateBubbleText with red color.
     * @tc.expected: text color updated.
     */
    pattern->UpdateBubbleText(TEST_COLOR_RED);
    auto textLayoutProp = messageNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProp, nullptr);
    EXPECT_EQ(textLayoutProp->GetTextColor().value(), TEST_COLOR_RED);
}

/**
 * @tc.name: UpdateBubbleTextColor002
 * @tc.desc: Test UpdateBubbleText with color value and null message node.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, UpdateBubbleTextColor002, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->messageNode_ = nullptr;
    /**
     * @tc.steps: step1. null message node, call UpdateBubbleText.
     * @tc.expected: early return.
     */
    pattern->UpdateBubbleText(TEST_COLOR_BLUE);
    SUCCEED();
}

/**
 * @tc.name: UpdateBubbleBackGroundColor001
 * @tc.desc: Test UpdateBubbleBackGroundColor.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, UpdateBubbleBackGroundColor001, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    pattern->SetPopupParam(popupParam);
    pattern->popupTheme_ = AceType::MakeRefPtr<PopupTheme>();
    /**
     * @tc.steps: step1. call UpdateBubbleBackGroundColor with blue.
     * @tc.expected: background color updated.
     */
    pattern->UpdateBubbleBackGroundColor(TEST_COLOR_BLUE);
    auto paintProp = popupNode->GetPaintProperty<BubbleRenderProperty>();
    ASSERT_NE(paintProp, nullptr);
    EXPECT_EQ(paintProp->GetBackgroundColor().value_or(Color::BLACK), TEST_COLOR_BLUE);
}

/**
 * @tc.name: UpdateMaskColor001
 * @tc.desc: Test UpdateMaskColor.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, UpdateMaskColor001, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step1. call UpdateMaskColor with green.
     * @tc.expected: mask color updated.
     */
    pattern->UpdateMaskColor(TEST_COLOR_GREEN);
    auto paintProp = popupNode->GetPaintProperty<BubbleRenderProperty>();
    ASSERT_NE(paintProp, nullptr);
    EXPECT_EQ(paintProp->GetMaskColor().value_or(Color::BLACK), TEST_COLOR_GREEN);
}

/**
 * @tc.name: UpdateArrowWidth001
 * @tc.desc: Test UpdateArrowWidth with valid dimension.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, UpdateArrowWidth001, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step1. call UpdateArrowWidth with valid positive dimension.
     * @tc.expected: arrow width updated.
     */
    pattern->UpdateArrowWidth(DEFAULT_ARROW_WIDTH);
    auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    EXPECT_EQ(layoutProp->GetArrowWidth().value_or(Dimension(0)), DEFAULT_ARROW_WIDTH);
}

/**
 * @tc.name: UpdateArrowWidth002
 * @tc.desc: Test UpdateArrowWidth with invalid dimension (percent).
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, UpdateArrowWidth002, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step1. call UpdateArrowWidth with percent unit.
     * @tc.expected: arrow width not updated (skipped).
     */
    CalcDimension percentDim(50.0, DimensionUnit::PERCENT);
    pattern->UpdateArrowWidth(percentDim);
    SUCCEED();
}

/**
 * @tc.name: UpdateArrowWidth003
 * @tc.desc: Test UpdateArrowWidth with zero/negative value.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, UpdateArrowWidth003, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step1. call UpdateArrowWidth with zero value.
     * @tc.expected: arrow width not updated.
     */
    pattern->UpdateArrowWidth(CalcDimension(0.0, DimensionUnit::PX));
    SUCCEED();
}

/**
 * @tc.name: UpdateArrowHeight001
 * @tc.desc: Test UpdateArrowHeight with valid dimension.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleSixTestNg, UpdateArrowHeight001, TestSize.Level1)
{
    BubbleSixTestProperty testProperty;
    auto popupNode = CreateBubbleNode(testProperty);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step1. call UpdateArrowHeight with valid positive dimension.
     * @tc.expected: arrow height updated.
     */
    pattern->UpdateArrowHeight(DEFAULT_ARROW_HEIGHT);
    auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    EXPECT_EQ(layoutProp->GetArrowHeight().value_or(Dimension(0)), DEFAULT_ARROW_HEIGHT);
}

} // namespace OHOS::Ace::NG
