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

#include "test/unittest/core/base/view_abstract_test_ng.h"

#include "base/subwindow/subwindow_manager.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/event/key_event.h"
#include "test/mock/base/mock_system_properties.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
/**
 * @tc.name: ViewAbstractDisableAxisByFrameNodeTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableAxisByFrameNodeTest, TestSize.Level1)
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
    OnAxisEventFunc onAxisEventFunc;
    ViewAbstract::SetOnAxisEvent(AceType::RawPtr(node), std::move(onAxisEventFunc));
    auto eventHub = node->GetOrCreateInputEventHub();
    auto& callback = eventHub->axisEventActuator_->userCallback_;
    EXPECT_NE(callback, nullptr);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnAxisEvent(AceType::RawPtr(node));
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
    OnKeyConsumeFunc onKeyCallback = [](KeyEventInfo& info) -> bool { return false; };
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

/**
 * @tc.name: SetForegroundEffectTest
 * @tc.desc: Test the operation of setting foreground effect with different conditions.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetForegroundEffectTest, TestSize.Level1)
{
    /**
     * @tc.steps: Build a object viewAbstract and set visual state.
     */
    ViewStackProcessor viewStackProcessor;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: Build a object viewAbstract and set visual state.
     * @tc.expected: The foreground effect is not changed.
     */
    auto originValue = frameNode->GetRenderContext()->GetForegroundEffect();
    ViewAbstract::SetForegroundEffect(1.1f);
    ASSERT_NE(frameNode->GetRenderContext()->GetForegroundEffect(), 1.1f);
    ASSERT_EQ(frameNode->GetRenderContext()->GetForegroundEffect(), originValue);

    /**
     * @tc.steps: Set visual state to null and check the current visual state process
     * @tc.expected: The foreground effect is changed as expected.
     */
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    ViewAbstract::SetForegroundEffect(1.1f);
    ASSERT_EQ(frameNode->GetRenderContext()->GetForegroundEffect(), 1.1f);
}

/**
 * @tc.name: ViewAbstractTest045
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest045, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    frameNode->GetOrCreateFocusHub();

    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    focusHub->currentFocus_ = true;

    /**
    * @tc.steps: Set frameNode attached context null
    * @tc.expected: do not set scop instanceId and excute lost focus to view root.
    */
    frameNode->DetachContext(true);
    ViewAbstract::SetNeedFocus(AceType::RawPtr(frameNode), false);
    EXPECT_EQ(ContainerScope::CurrentId(), -1);
}

/**
 * @tc.name: RemoveResObj
 * @tc.desc: Test RemoveResObj of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest046, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    g_isConfigChangePerform = true;
    std::string key = "clipShape";
    ViewAbstractModelNG::RemoveResObj(frameNode, key);
    g_isConfigChangePerform = false;
    ViewAbstractModelNG::RemoveResObj(frameNode, key);
}

/**
 * @tc.name: ViewAbstractDisableOnKeyEventDispatchTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableOnKeyEventDispatchTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    OnKeyConsumeFunc onKeyCallback = [](KeyEventInfo& info) -> bool { return false; };
    ViewAbstract::SetOnKeyEventDispatch(std::move(onKeyCallback));

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    auto focusHub = node->GetOrCreateFocusHub();
    auto& callback = focusHub->focusCallbackEvents_->onKeyEventDispatchCallback_;
    EXPECT_TRUE(callback);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnKeyEventDispatch();
    EXPECT_FALSE(callback);

    /**
     * @tc.steps: step3. Add callback again.
     * @tc.expected: callback is not null.
     */
    OnKeyConsumeFunc onKeyCallback2 = [](KeyEventInfo& info) -> bool { return false; };
    ViewAbstract::SetOnKeyEventDispatch(std::move(onKeyCallback2));
    EXPECT_TRUE(callback);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: DispatchKeyEvent001
 * @tc.desc: Test DispatchKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, DispatchKeyEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode.
     */
    std::string tag = "uiNode1";
    int32_t nodeId = 1;
    FrameNode frameNode(tag, nodeId, AceType::MakeRefPtr<Pattern>());
    int32_t repeatTime = 0;
    int64_t timeStamp = 0;
    int64_t deviceId = 0;

    /**
     * @tc.steps: step2. Create keyEvent.
     */
    KeyEvent keyEvent(KeyCode::KEY_UNKNOWN, KeyAction::UNKNOWN, repeatTime, timeStamp, deviceId, SourceType::KEYBOARD);
    ViewAbstract::DispatchKeyEvent(&frameNode, keyEvent);
    EXPECT_NE(&frameNode, nullptr);
}

#ifdef SUPPORT_DIGITAL_CROWN
/**
 * @tc.name: ViewAbstract
 * @tc.desc: Test DisableOnCrownEvent001 of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, DisableOnCrownEvent001, TestSize.Level1)
{
    /**
    * @tc.steps1: create and put frameNode
    * @tc.expected: frameNode is't nullptr.
    */
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);

    /**
     * @tc.steps2: Call the function SetOnCrownEvent and DisableOnCrownEvent
     */
    OnCrownCallbackFunc onCrownCallback = [](CrownEventInfo& info) {};
    ViewAbstract::SetOnCrownEvent(AceType::RawPtr(node), std::move(onCrownCallback));
    ViewAbstract::DisableOnCrownEvent(AceType::RawPtr(node));
    EXPECT_NE(onCrownCallback, nullptr);
}

/**
 * @tc.name: ViewAbstract
 * @tc.desc: Test DisableOnCrownEvent002 of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, DisableOnCrownEvent002, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    frameNode->GetOrCreateFocusHub();

    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    focusHub->currentFocus_ = true;

    /**
     * @tc.steps: Call the function SetOnCrownEvent and DisableOnCrownEvent
     */
    OnCrownCallbackFunc onCrownCallback = [](CrownEventInfo& info) {};
    ViewAbstract::SetOnCrownEvent(std::move(onCrownCallback));
    ViewAbstract::DisableOnCrownEvent();
    EXPECT_EQ(ContainerScope::CurrentId(), -1);
}

/**
 * @tc.name: ViewAbstract
 * @tc.desc: Test DisableOnCrownEvent003 of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, DisableOnCrownEvent003, TestSize.Level1)
{
    /**
     * @tc.steps: Call the function SetOnCrownEvent, node is nullptr
     */
    auto node = AceType::DynamicCast<NG::FrameNode>((AceType*)nullptr);
    OnCrownCallbackFunc onCrownCallback = [](CrownEventInfo& info) {};

    ViewAbstract::SetOnCrownEvent(node, std::move(onCrownCallback));
    EXPECT_NE(onCrownCallback, nullptr);
}
#endif

/**
 * @tc.name: CheckLocalizedMarginOrPadding001
 * @tc.desc: Test CheckLocalizedMarginOrPadding when start,top,bottom,left have values
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, CheckLocalizedMarginOrPadding001, TestSize.Level1)
{
    PaddingProperty paddingProperty;
    paddingProperty.start = std::make_optional<CalcLength>(5.0);
    paddingProperty.top = std::make_optional<CalcLength>(6.0);
    paddingProperty.bottom = std::make_optional<CalcLength>(7.0);
    paddingProperty.left = std::make_optional<CalcLength>(8.0);

    auto textDirection = TextDirection::LTR;
    ViewAbstract::CheckLocalizedMarginOrPadding(paddingProperty, textDirection);
    EXPECT_EQ(paddingProperty.left.value(), CalcLength(5.0));

    textDirection = TextDirection::RTL;
    ViewAbstract::CheckLocalizedMarginOrPadding(paddingProperty, textDirection);
    EXPECT_EQ(paddingProperty.right.value(), CalcLength(5.0));
}

/**
 * @tc.name: CheckLocalizedMarginOrPadding002
 * @tc.desc: Test CheckLocalizedMarginOrPadding when end,right have values
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, CheckLocalizedMarginOrPadding002, TestSize.Level1)
{
    PaddingProperty paddingProperty;
    paddingProperty.end = std::make_optional<CalcLength>(5.0);
    paddingProperty.right = std::make_optional<CalcLength>(6.0);

    auto textDirection = TextDirection::LTR;
    ViewAbstract::CheckLocalizedMarginOrPadding(paddingProperty, textDirection);
    EXPECT_EQ(paddingProperty.right.value(), CalcLength(5.0));

    textDirection = TextDirection::RTL;
    ViewAbstract::CheckLocalizedMarginOrPadding(paddingProperty, textDirection);
    EXPECT_EQ(paddingProperty.left.value(), CalcLength(5.0));
}

/**
 * @tc.name: CheckLocalizedMarginOrPadding003
 * @tc.desc: Test CheckLocalizedMarginOrPadding When neither start nor end has a value
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, CheckLocalizedMarginOrPadding003, TestSize.Level1)
{
    PaddingProperty paddingProperty;

    auto textDirection = TextDirection::LTR;
    ViewAbstract::CheckLocalizedMarginOrPadding(paddingProperty, textDirection);
    EXPECT_FALSE(paddingProperty.right.has_value());
    EXPECT_FALSE(paddingProperty.left.has_value());
}

/**
 * @tc.name: CheckPositionOrOffsetLocalizedEdges001
 * @tc.desc: Test CheckPositionOrOffsetLocalizedEdges
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, CheckPositionOrOffsetLocalizedEdges001, TestSize.Level1)
{
    auto top = CalcDimension(1.0);
    auto bottom = CalcDimension(2.0);
    auto start = CalcDimension(3.0);
    auto end = CalcDimension(4.0);

    EdgesParam edges;
    edges.SetTop(top);
    edges.SetBottom(bottom);
    edges.start = start;
    edges.end = end;

    auto textDirection = TextDirection::LTR;
    ViewAbstract::CheckPositionOrOffsetLocalizedEdges(edges, textDirection);
    EXPECT_EQ(edges.left.value(), start);

    textDirection = TextDirection::RTL;
    ViewAbstract::CheckPositionOrOffsetLocalizedEdges(edges, textDirection);
    EXPECT_EQ(edges.left.value(), end);
}

/**
 * @tc.name: CheckPositionOrOffsetLocalizedEdges002
 * @tc.desc: Test CheckPositionOrOffsetLocalizedEdges
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, CheckPositionOrOffsetLocalizedEdges002, TestSize.Level1)
{
    EdgesParam edges;

    auto textDirection = TextDirection::LTR;
    ViewAbstract::CheckPositionOrOffsetLocalizedEdges(edges, textDirection);
    EXPECT_FALSE(edges.left.has_value());
    EXPECT_FALSE(edges.right.has_value());
}

/**
 * @tc.name: RegisterRadiusesResObj
 * @tc.desc: Test RegisterRadiusesResObj
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, RegisterRadiusesResObj, TestSize.Level1)
{
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    NG::BorderRadiusProperty borderRadius;
    ViewAbstractModelNG::RegisterRadiusesResObj("borderRadius.topLeft", borderRadius, resObj);
    borderRadius.ReloadResources();
    EXPECT_EQ(borderRadius.resMap_.size(), 1);
    ViewAbstractModelNG::RegisterRadiusesResObj("borderRadius.topRight", borderRadius, resObj);
    borderRadius.ReloadResources();
    EXPECT_EQ(borderRadius.resMap_.size(), 2);
    ViewAbstractModelNG::RegisterRadiusesResObj("borderRadius.bottomLeft", borderRadius, resObj);
    borderRadius.ReloadResources();
    EXPECT_EQ(borderRadius.resMap_.size(), 3);
    ViewAbstractModelNG::RegisterRadiusesResObj("borderRadius.bottomRight", borderRadius, resObj);
    borderRadius.ReloadResources();
    EXPECT_EQ(borderRadius.resMap_.size(), 4);
    ViewAbstractModelNG::RegisterRadiusesResObj("", borderRadius, nullptr);
    EXPECT_EQ(borderRadius.resMap_.size(), 4);
}

/**
 * @tc.name: RegisterLocationPropsEdgesResObj
 * @tc.desc: Test RegisterLocationPropsEdgesResObj
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, RegisterLocationPropsEdgesResObj, TestSize.Level1)
{
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    EdgesParam edges;
    ViewAbstractModelNG::RegisterLocationPropsEdgesResObj("edges.top", edges, resObj);
    edges.ReloadResources();
    EXPECT_EQ(edges.resMap_.size(), 1);
    ViewAbstractModelNG::RegisterLocationPropsEdgesResObj("edges.left", edges, resObj);
    edges.ReloadResources();
    EXPECT_EQ(edges.resMap_.size(), 2);
    ViewAbstractModelNG::RegisterLocationPropsEdgesResObj("edges.bottom", edges, resObj);
    edges.ReloadResources();
    EXPECT_EQ(edges.resMap_.size(), 3);
    ViewAbstractModelNG::RegisterLocationPropsEdgesResObj("edges.right", edges, resObj);
    edges.ReloadResources();
    EXPECT_EQ(edges.resMap_.size(), 4);
    ViewAbstractModelNG::RegisterLocationPropsEdgesResObj("", edges, nullptr);
    EXPECT_EQ(edges.resMap_.size(), 4);
}

/**
 * @tc.name: RegisterEdgesWidthResObj
 * @tc.desc: Test RegisterEdgesWidthResObj
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, RegisterEdgesWidthResObj, TestSize.Level1)
{
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    NG::BorderWidthProperty borderWidth;
    ViewAbstractModelNG::RegisterEdgesWidthResObj("borderWidth.top", borderWidth, resObj);
    borderWidth.ReloadResources();
    EXPECT_EQ(borderWidth.resMap_.size(), 1);
    ViewAbstractModelNG::RegisterEdgesWidthResObj("borderWidth.left", borderWidth, resObj);
    borderWidth.ReloadResources();
    EXPECT_EQ(borderWidth.resMap_.size(), 2);
    ViewAbstractModelNG::RegisterEdgesWidthResObj("borderWidth.bottom", borderWidth, resObj);
    borderWidth.ReloadResources();
    EXPECT_EQ(borderWidth.resMap_.size(), 3);
    ViewAbstractModelNG::RegisterEdgesWidthResObj("borderWidth.right", borderWidth, resObj);
    borderWidth.ReloadResources();
    EXPECT_EQ(borderWidth.resMap_.size(), 4);
    ViewAbstractModelNG::RegisterEdgesWidthResObj("", borderWidth, nullptr);
    EXPECT_EQ(borderWidth.resMap_.size(), 4);
}

/**
 * @tc.name: RegisterEdgeMarginsResObj
 * @tc.desc: Test RegisterEdgeMarginsResObj
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, RegisterEdgeMarginsResObj, TestSize.Level1)
{
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    NG::MarginProperty margins;
    ViewAbstractModelNG::RegisterEdgeMarginsResObj("margin.top", margins, resObj);
    margins.ReloadResources();
    EXPECT_EQ(margins.resMap_.size(), 1);
    ViewAbstractModelNG::RegisterEdgeMarginsResObj("margin.left", margins, resObj);
    margins.ReloadResources();
    EXPECT_EQ(margins.resMap_.size(), 2);
    ViewAbstractModelNG::RegisterEdgeMarginsResObj("margin.bottom", margins, resObj);
    margins.ReloadResources();
    EXPECT_EQ(margins.resMap_.size(), 3);
    ViewAbstractModelNG::RegisterEdgeMarginsResObj("margin.right", margins, resObj);
    margins.ReloadResources();
    EXPECT_EQ(margins.resMap_.size(), 4);
    ViewAbstractModelNG::RegisterEdgeMarginsResObj("", margins, nullptr);
    EXPECT_EQ(margins.resMap_.size(), 4);
}

/**
 * @tc.name: RegisterLocalizedBorderColor
 * @tc.desc: Test RegisterLocalizedBorderColor
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, RegisterLocalizedBorderColor, TestSize.Level1)
{
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    NG::BorderColorProperty borderColors;
    ViewAbstractModelNG::RegisterLocalizedBorderColor("borderColor.top", borderColors, resObj);
    borderColors.ReloadResources();
    EXPECT_EQ(borderColors.resMap_.size(), 1);
    ViewAbstractModelNG::RegisterLocalizedBorderColor("borderColor.start", borderColors, resObj);
    borderColors.ReloadResources();
    EXPECT_EQ(borderColors.resMap_.size(), 2);
    ViewAbstractModelNG::RegisterLocalizedBorderColor("borderColor.bottom", borderColors, resObj);
    borderColors.ReloadResources();
    EXPECT_EQ(borderColors.resMap_.size(), 3);
    ViewAbstractModelNG::RegisterLocalizedBorderColor("borderColor.end", borderColors, resObj);
    borderColors.ReloadResources();
    EXPECT_EQ(borderColors.resMap_.size(), 4);
    ViewAbstractModelNG::RegisterLocalizedBorderColor("", borderColors, nullptr);
    EXPECT_EQ(borderColors.resMap_.size(), 4);
}

/**
 * @tc.name: backgroundImagePostionCheckDiff
 * @tc.desc: Test backgroundImagePostionCheckDiff
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, backgroundImagePostionCheckDiff, TestSize.Level1)
{
    BackgroundImagePosition backgroundImagePosition1;
    BackgroundImagePosition backgroundImagePosition2;
    EXPECT_TRUE(backgroundImagePosition1 == backgroundImagePosition2);
    auto animatableDimension = AnimatableDimension(50.0);
    backgroundImagePosition1.SetPercentX(animatableDimension);
    EXPECT_FALSE(backgroundImagePosition1 == backgroundImagePosition2);
    backgroundImagePosition2.SetPercentX(animatableDimension);
    EXPECT_TRUE(backgroundImagePosition1 == backgroundImagePosition2);
    backgroundImagePosition1.SetIsAlign(true);
    EXPECT_TRUE(backgroundImagePosition1 == backgroundImagePosition2);
}

/**
 * @tc.name: AllowForceDark001
 * @tc.desc: Test AllowForceDark
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, AllowForceDark001, TestSize.Level1)
{
    auto topNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    ViewAbstract::AllowForceDark(false);
    EXPECT_FALSE(topNode->GetForceDarkAllowed());
    ViewAbstract::AllowForceDark(AceType::RawPtr(topNode), true);
    EXPECT_TRUE(topNode->GetForceDarkAllowed());
}

/**
 * @tc.name: SetForegroundColor
 * @tc.desc: Branch: if (SystemProperties::ConfigChangePerform() && resObj) => true.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetForegroundColorTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Turn on the dark and light switch, before test "SetForegroundColor".
     */
    g_isConfigChangePerform = true;
    EXPECT_TRUE(SystemProperties::ConfigChangePerform());

    /**
     * @tc.steps: step2. Get frame node and pattern.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. Initialize the color value of the foreground.
     */
    std::string foregroundColor = pattern->GetResCacheMapByKey("foreground");
    EXPECT_EQ(foregroundColor, "");
    std::string bundleName = "com.example.foregroundTest";
    std::string moduleName = "Entry";
    RefPtr<ResourceObject> colorResObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    Color color;
    ViewAbstract::SetForegroundColor(frameNode, color, colorResObj);
    Color finalColor;
    ResourceParseUtils::ParseResColor(colorResObj, finalColor);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
    EXPECT_FALSE(SystemProperties::ConfigChangePerform());
    foregroundColor = pattern->GetResCacheMapByKey("foregroundColor");
    EXPECT_EQ(foregroundColor, finalColor.ColorToString());
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_TRUE(renderContext->GetForegroundColorFlagValue());
}

/**
 * @tc.name: SetForegroundColor
 * @tc.desc: Branch: if (SystemProperties::ConfigChangePerform() && resObj) => false.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetForegroundColorTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Turn off the dark and light switch, before test "SetForegroundColor".
     */
    g_isConfigChangePerform = false;
    EXPECT_FALSE(SystemProperties::ConfigChangePerform());

    /**
     * @tc.steps: step2. Get frame node and pattern.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. Initialize the color value of the foreground.
     */
    Color color = Color::RED;
    ViewAbstract::SetForegroundColor(frameNode, color, nullptr);
    auto target = frameNode->GetRenderContext();
    ASSERT_NE(target, nullptr);
    EXPECT_TRUE(target->GetForegroundColorFlagValue());
}

/**
 * @tc.name: SetColorBlend
 * @tc.desc: Branch: if (SystemProperties::ConfigChangePerform() && resObj) => true.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetColorBlendTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Turn on the dark and light switch, before test "SetColorBlend".
     */
    g_isConfigChangePerform = true;
    EXPECT_TRUE(SystemProperties::ConfigChangePerform());

    /**
     * @tc.steps: step2. Get frame node and pattern.
     */
    auto targetNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(targetNode, nullptr);
    auto pattern = targetNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. Initialize the color value of the front color blend.
     */
    std::string frontColorBlend = pattern->GetResCacheMapByKey("frontColorBlend");
    EXPECT_EQ(frontColorBlend, "");
    std::string bundleName = "com.example.frontColorBlendTest";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> colorResObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    Color color = Color::BLUE;
    ViewAbstract::SetColorBlend(targetNode, color, colorResObj);
    Color finalColor;
    ResourceParseUtils::ParseResColor(colorResObj, finalColor);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
    EXPECT_FALSE(SystemProperties::ConfigChangePerform());
    frontColorBlend = pattern->GetResCacheMapByKey("viewAbstract.colorBlend");
    EXPECT_EQ(frontColorBlend, finalColor.ColorToString());
    auto renderContext = targetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_TRUE(renderContext->GetFrontColorBlend().has_value());
}

/**
 * @tc.name: SetColorBlend
 * @tc.desc: Branch: if (SystemProperties::ConfigChangePerform() && resObj) => false.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetColorBlendTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Turn off the dark and light switch, before test "SetColorBlend".
     */
    g_isConfigChangePerform = false;
    EXPECT_FALSE(SystemProperties::ConfigChangePerform());

    /**
     * @tc.steps: step2. Get frame node and pattern.
     */
    auto node = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(node, nullptr);
    auto pattern = node->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. Initialize the color value of the front color blend.
     */
    Color color = Color::GREEN;
    ViewAbstract::SetColorBlend(node, color, nullptr);
    auto renderContext = node->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_TRUE(renderContext->GetFrontColorBlend().has_value());
}
} // namespace OHOS::Ace::NG