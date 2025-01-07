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

#include "common_method_modifier_test.h"

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "generated/type_helpers.h"
#include "core/components_ng/gestures/recognizers/click_recognizer.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace Converter {
    template<>
    PreDragStatus Convert(const Ark_PreDragStatus& src)
    {
        PreDragStatus dst;
        switch (src) {
            case ARK_PRE_DRAG_STATUS_ACTION_DETECTING_STATUS:
                dst = PreDragStatus::ACTION_DETECTING_STATUS;
                break;
            case ARK_PRE_DRAG_STATUS_READY_TO_TRIGGER_DRAG_ACTION:
                dst = PreDragStatus::READY_TO_TRIGGER_DRAG_ACTION;
                break;
            case ARK_PRE_DRAG_STATUS_PREVIEW_LIFT_STARTED:
                dst = PreDragStatus::PREVIEW_LIFT_STARTED;
                break;
            case ARK_PRE_DRAG_STATUS_PREVIEW_LIFT_FINISHED:
                dst = PreDragStatus::PREVIEW_LIFT_FINISHED;
                break;
            case ARK_PRE_DRAG_STATUS_PREVIEW_LANDING_STARTED:
                dst = PreDragStatus::PREVIEW_LANDING_STARTED;
                break;
            case ARK_PRE_DRAG_STATUS_PREVIEW_LANDING_FINISHED:
                dst = PreDragStatus::PREVIEW_LANDING_FINISHED;
                break;
            case ARK_PRE_DRAG_STATUS_ACTION_CANCELED_BEFORE_DRAG:
                dst = PreDragStatus::ACTION_CANCELED_BEFORE_DRAG;
                break;
            default:
                break;
        }
        return dst;
    }
    template<>
    DragBehavior Convert(const Ark_DragBehavior& src)
    {
        DragBehavior dst;
        switch (src) {
            case ARK_DRAG_BEHAVIOR_COPY: dst = DragBehavior::COPY; break;
            case ARK_DRAG_BEHAVIOR_MOVE: dst = DragBehavior::MOVE; break;
            default:
                dst = DragBehavior::COPY;
                break;
        }
        return dst;
    }
}

class CommonMethodModifierTest7 : public ModifierTestBase<GENERATED_ArkUICommonMethodModifier,
    &GENERATED_ArkUINodeModifiers::getCommonMethodModifier,
    GENERATED_ARKUI_BLANK // test common methods on frameNode for Blank component
    > {
public:
    RefPtr<RenderContext> render_;

    void *CreateNodeImpl() override
    {
        return nodeModifiers_->getBlankModifier()->construct(GetId(), 0);
    }

    RefPtr<GestureEventHub> GetGestureEventHub()
    {
        if (auto fnode = reinterpret_cast<FrameNode *>(node_); fnode) {
            if (auto eventHub = fnode->GetEventHub<NG::EventHub>(); eventHub) {
                return eventHub->GetOrCreateGestureEventHub();
            }
        }
        return nullptr;
    }
};

/*
 * @tc.name: SetOnPreDrag
 * @tc.desc: Checking the callback operation for a change in breakpoint.
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest7, SetOnPreDragTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        PreDragStatus preDragStatus;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    auto onPreDrag = [](Ark_Int32 nodeId, const Ark_PreDragStatus preDragStatus) {
        checkEvent = {
            .nodeId = nodeId,
            .preDragStatus = Converter::Convert<PreDragStatus>(preDragStatus),
        };
    };

    Callback_PreDragStatus_Void callBackValue = {
        .resource = Ark_CallbackResource {
            .resourceId = frameNode->GetId(),
            .hold = nullptr,
            .release = nullptr,
        },
        .call = onPreDrag
    };

    auto test = [this, &callBackValue, eventHub, frameNode](const PreDragStatus& testValue) {
        checkEvent = std::nullopt;
        modifier_->setOnPreDrag(node_, &callBackValue);
        EXPECT_FALSE(checkEvent.has_value());
        auto onPreDragFunc = eventHub->GetOnPreDrag();
        onPreDragFunc(testValue);
        ASSERT_TRUE(checkEvent.has_value());
        EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
        EXPECT_EQ(checkEvent->preDragStatus, testValue);
    };

    test(PreDragStatus::ACTION_DETECTING_STATUS);
    test(PreDragStatus::READY_TO_TRIGGER_DRAG_ACTION);
    test(PreDragStatus::PREVIEW_LIFT_STARTED);
    test(PreDragStatus::PREVIEW_LIFT_FINISHED);
    test(PreDragStatus::PREVIEW_LANDING_STARTED);
    test(PreDragStatus::PREVIEW_LANDING_FINISHED);
    test(PreDragStatus::ACTION_CANCELED_BEFORE_DRAG);
}

/*
 * @tc.name: SetOnDragEnter
 * @tc.desc: Checking the callback operation for a change in breakpoint.
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest7, SetOnDragEnterTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    // OHOS::Ace::NG::EventHub
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        DragBehavior dragBehavior;
        bool useCustomDropAnimation;
        std::optional<std::string> extraParams;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    auto onDragEnterFunc = [](const Ark_Int32 resourceId, const Ark_DragEvent event, const Opt_String extraParams) {
        checkEvent = {
            .nodeId = resourceId,
            .dragBehavior = Converter::Convert<DragBehavior>(event.dragBehavior),
            .useCustomDropAnimation = Converter::Convert<bool>(event.useCustomDropAnimation),
            .extraParams = Converter::OptConvert<std::string>(extraParams),
        };
    };

    Callback_DragEvent_String_Void callBackValue = {
        .resource = Ark_CallbackResource {
            .resourceId = frameNode->GetId(),
            .hold = nullptr,
            .release = nullptr,
        },
        .call = onDragEnterFunc,
    };

    auto test = [this, &callBackValue, eventHub, frameNode](DragBehavior dragBehavior, bool useCustomDropAnimation,
                                                            const std::string& extraParams) {
        checkEvent = std::nullopt;
        modifier_->setOnDragEnter(node_, &callBackValue);
        EXPECT_FALSE(checkEvent.has_value());

        RefPtr<OHOS::Ace::DragEvent> dragEventPtr = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
        dragEventPtr->SetDragBehavior(dragBehavior);
        dragEventPtr->UseCustomAnimation(useCustomDropAnimation);
        eventHub->FireCustomerOnDragFunc(DragFuncType::DRAG_ENTER, dragEventPtr, extraParams);

        ASSERT_TRUE(checkEvent.has_value());
        EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
        EXPECT_EQ(checkEvent->dragBehavior, dragBehavior);
        EXPECT_EQ(checkEvent->useCustomDropAnimation, useCustomDropAnimation);
        EXPECT_EQ(checkEvent->extraParams, extraParams);
    };
    test(DragBehavior::COPY, true, "The test string 1");
    test(DragBehavior::MOVE, true, "The test string 2");
    test(DragBehavior::COPY, false, "The test string 3");
    test(DragBehavior::MOVE, false, "The test string 4");
}

/*
 * @tc.name: SetOnDragMove
 * @tc.desc: Checking the callback operation for a change in breakpoint.
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest7, SetOnDragMoveTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    // OHOS::Ace::NG::EventHub
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        DragBehavior dragBehavior;
        bool useCustomDropAnimation;
        std::optional<std::string> extraParams;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    auto onDragMoveFunc = [](const Ark_Int32 resourceId, const Ark_DragEvent event, const Opt_String extraParams) {
        checkEvent = {
            .nodeId = resourceId,
            .dragBehavior = Converter::Convert<DragBehavior>(event.dragBehavior),
            .useCustomDropAnimation = Converter::Convert<bool>(event.useCustomDropAnimation),
            .extraParams = Converter::OptConvert<std::string>(extraParams),
        };
    };

    Callback_DragEvent_String_Void callBackValue = {
        .resource = Ark_CallbackResource {
            .resourceId = frameNode->GetId(),
            .hold = nullptr,
            .release = nullptr,
        },
        .call = onDragMoveFunc,
    };

    auto test = [this, &callBackValue, eventHub, frameNode](DragBehavior dragBehavior, bool useCustomDropAnimation,
                                                            const std::string& extraParams) {
        checkEvent = std::nullopt;
        modifier_->setOnDragMove(node_, &callBackValue);
        EXPECT_FALSE(checkEvent.has_value());

        RefPtr<OHOS::Ace::DragEvent> dragEventPtr = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
        dragEventPtr->SetDragBehavior(dragBehavior);
        dragEventPtr->UseCustomAnimation(useCustomDropAnimation);
        eventHub->FireCustomerOnDragFunc(DragFuncType::DRAG_MOVE, dragEventPtr, extraParams);

        ASSERT_TRUE(checkEvent.has_value());
        EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
        EXPECT_EQ(checkEvent->dragBehavior, dragBehavior);
        EXPECT_EQ(checkEvent->useCustomDropAnimation, useCustomDropAnimation);
        EXPECT_EQ(checkEvent->extraParams, extraParams);
    };
    test(DragBehavior::COPY, true, "The test string 1");
    test(DragBehavior::MOVE, true, "The test string 2");
    test(DragBehavior::COPY, false, "The test string 3");
    test(DragBehavior::MOVE, false, "The test string 4");
}

/*
 * @tc.name: SetOnDragLeave
 * @tc.desc: Checking the callback operation for a change in breakpoint.
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest7, SetOnDragLeaveTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    // OHOS::Ace::NG::EventHub
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        DragBehavior dragBehavior;
        bool useCustomDropAnimation;
        std::optional<std::string> extraParams;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    auto onDragLeaveFunc = [](const Ark_Int32 resourceId, const Ark_DragEvent event, const Opt_String extraParams) {
        checkEvent = {
            .nodeId = resourceId,
            .dragBehavior = Converter::Convert<DragBehavior>(event.dragBehavior),
            .useCustomDropAnimation = Converter::Convert<bool>(event.useCustomDropAnimation),
            .extraParams = Converter::OptConvert<std::string>(extraParams),
        };
    };

    Callback_DragEvent_String_Void callBackValue = {
        .resource = Ark_CallbackResource {
            .resourceId = frameNode->GetId(),
            .hold = nullptr,
            .release = nullptr,
        },
        .call = onDragLeaveFunc,
    };

    auto test = [this, &callBackValue, eventHub, frameNode](DragBehavior dragBehavior, bool useCustomDropAnimation,
                                                            const std::string& extraParams) {
        checkEvent = std::nullopt;
        modifier_->setOnDragLeave(node_, &callBackValue);
        EXPECT_FALSE(checkEvent.has_value());

        RefPtr<OHOS::Ace::DragEvent> dragEventPtr = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
        dragEventPtr->SetDragBehavior(dragBehavior);
        dragEventPtr->UseCustomAnimation(useCustomDropAnimation);
        eventHub->FireCustomerOnDragFunc(DragFuncType::DRAG_LEAVE, dragEventPtr, extraParams);

        ASSERT_TRUE(checkEvent.has_value());
        EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
        EXPECT_EQ(checkEvent->dragBehavior, dragBehavior);
        EXPECT_EQ(checkEvent->useCustomDropAnimation, useCustomDropAnimation);
        EXPECT_EQ(checkEvent->extraParams, extraParams);
    };
    test(DragBehavior::COPY, true, "The test string 1");
    test(DragBehavior::MOVE, true, "The test string 2");
    test(DragBehavior::COPY, false, "The test string 3");
    test(DragBehavior::MOVE, false, "The test string 4");
}

/*
 * @tc.name: SetOnDrop
 * @tc.desc: Checking the callback operation for a change in breakpoint.
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest7, SetOnDropTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    // OHOS::Ace::NG::EventHub
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        DragBehavior dragBehavior;
        bool useCustomDropAnimation;
        std::optional<std::string> extraParams;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    auto onDropFunc = [](const Ark_Int32 resourceId, const Ark_DragEvent event, const Opt_String extraParams) {
        checkEvent = {
            .nodeId = resourceId,
            .dragBehavior = Converter::Convert<DragBehavior>(event.dragBehavior),
            .useCustomDropAnimation = Converter::Convert<bool>(event.useCustomDropAnimation),
            .extraParams = Converter::OptConvert<std::string>(extraParams),
        };
    };

    Callback_DragEvent_String_Void callBackValue = {
        .resource = Ark_CallbackResource {
            .resourceId = frameNode->GetId(),
            .hold = nullptr,
            .release = nullptr,
        },
        .call = onDropFunc,
    };

    auto test = [this, &callBackValue, eventHub, frameNode](DragBehavior dragBehavior, bool useCustomDropAnimation,
                                                            const std::string& extraParams) {
        checkEvent = std::nullopt;
        modifier_->setOnDrop(node_, &callBackValue);
        EXPECT_FALSE(checkEvent.has_value());

        RefPtr<OHOS::Ace::DragEvent> dragEventPtr = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
        dragEventPtr->SetDragBehavior(dragBehavior);
        dragEventPtr->UseCustomAnimation(useCustomDropAnimation);
        eventHub->FireCustomerOnDragFunc(DragFuncType::DRAG_DROP, dragEventPtr, extraParams);

        ASSERT_TRUE(checkEvent.has_value());
        EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
        EXPECT_EQ(checkEvent->dragBehavior, dragBehavior);
        EXPECT_EQ(checkEvent->useCustomDropAnimation, useCustomDropAnimation);
        EXPECT_EQ(checkEvent->extraParams, extraParams);
    };
    test(DragBehavior::COPY, true, "The test string 1");
    test(DragBehavior::MOVE, true, "The test string 2");
    test(DragBehavior::COPY, false, "The test string 3");
    test(DragBehavior::MOVE, false, "The test string 4");
}

/*
 * @tc.name: SetOnDragEnd
 * @tc.desc: Checking the callback operation for a change in breakpoint.
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest7, SetOnDragEndTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    // OHOS::Ace::NG::EventHub
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        DragBehavior dragBehavior;
        bool useCustomDropAnimation;
        std::optional<std::string> extraParams;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    auto onDragEndFunc = [](const Ark_Int32 resourceId, const Ark_DragEvent event, const Opt_String extraParams) {
        checkEvent = {
            .nodeId = resourceId,
            .dragBehavior = Converter::Convert<DragBehavior>(event.dragBehavior),
            .useCustomDropAnimation = Converter::Convert<bool>(event.useCustomDropAnimation),
            .extraParams = Converter::OptConvert<std::string>(extraParams),
        };
    };

    Callback_DragEvent_String_Void callBackValue = {
        .resource = Ark_CallbackResource {
            .resourceId = frameNode->GetId(),
            .hold = nullptr,
            .release = nullptr,
        },
        .call = onDragEndFunc,
    };

    auto test = [this, &callBackValue, eventHub, frameNode](DragBehavior dragBehavior, bool useCustomDropAnimation) {
        checkEvent = std::nullopt;
        modifier_->setOnDragEnd(node_, &callBackValue);
        EXPECT_FALSE(checkEvent.has_value());

        RefPtr<OHOS::Ace::DragEvent> dragEventPtr = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
        dragEventPtr->SetDragBehavior(dragBehavior);
        dragEventPtr->UseCustomAnimation(useCustomDropAnimation);
        eventHub->FireCustomerOnDragFunc(DragFuncType::DRAG_END, dragEventPtr);

        ASSERT_TRUE(checkEvent.has_value());
        EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
        EXPECT_EQ(checkEvent->dragBehavior, dragBehavior);
        EXPECT_EQ(checkEvent->useCustomDropAnimation, useCustomDropAnimation);
    };
    test(DragBehavior::COPY, true);
    test(DragBehavior::MOVE, true);
    test(DragBehavior::COPY, false);
    test(DragBehavior::MOVE, false);
}

/*
 * @tc.name: SetOnDragStart
 * @tc.desc: Checking the callback operation for a change in breakpoint.
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest7, SetOnDragStartTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnDragStart, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    static const int32_t expectedResourceId = 123;
    static auto expectedCustomNode = CreateNode();
    static const FrameNode *expectedParentNode = frameNode;
    static const std::string expectedInfo("key:value");

    static const CustomNodeBuilder builder = {
        .callSync = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
            const Callback_Pointer_Void continuation) {
            EXPECT_EQ(reinterpret_cast<FrameNode*>(parentNode), expectedParentNode);
            CallbackHelper(continuation).Invoke(reinterpret_cast<Ark_NativePointer>(expectedCustomNode));
        }
    };

    auto callSyncFunc = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_DragEvent event,
        const Opt_String extraP, const Callback_Union_CustomBuilder_DragItemInfo_Void continuation)
    {
        EXPECT_EQ(Converter::Convert<int32_t>(resourceId), expectedResourceId);
        // the defferent type in return value depending on input data
        auto isNeedBuilder = Converter::Convert<DragBehavior>(event.dragBehavior) == DragBehavior::MOVE;
        Ark_Union_CustomBuilder_DragItemInfo arkResult;
        if (isNeedBuilder) {
            TypeHelper::WriteToUnion<CustomNodeBuilder>(arkResult) = builder;
        } else {
            TypeHelper::WriteToUnion<Ark_DragItemInfo>(arkResult).extraInfo = Converter::ArkValue<Opt_String>(extraP);
        }
        CallbackHelper(continuation).Invoke(arkResult);
    };

    auto arkCallback = Converter::ArkValue<Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo>(nullptr,
        callSyncFunc, expectedResourceId);
    modifier_->setOnDragStart(node_, &arkCallback);

    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto fireOnDragStart = eventHub->GetOnDragStart();
    ASSERT_NE(fireOnDragStart, nullptr);

    auto dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    dragEvent->SetDragBehavior(DragBehavior::MOVE);
    DragDropInfo ddInfo = fireOnDragStart(dragEvent, expectedInfo);
    EXPECT_EQ(reinterpret_cast<Ark_NativePointer>(ddInfo.customNode.GetRawPtr()),
        reinterpret_cast<Ark_NativePointer>(expectedCustomNode));
    EXPECT_EQ(ddInfo.extraInfo, std::string());

    dragEvent->SetDragBehavior(DragBehavior::COPY);
    ddInfo = fireOnDragStart(dragEvent, expectedInfo);
    EXPECT_EQ(ddInfo.customNode, nullptr);
    EXPECT_EQ(ddInfo.extraInfo, expectedInfo);

    DisposeNode(expectedCustomNode);
}

/*
 * @tc.name: SetOnChildTouchTest
 * @tc.desc: Checking the callback operation for a change in breakpoint.
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest7, SetOnChildTouchTest, TestSize.Level1)
{
    using namespace Converter;
    ASSERT_NE(modifier_->setOnChildTouchTest, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    static const int32_t expectedResourceId = 123;

    auto callSyncFunc = [](Ark_VMContext context, const Ark_Int32 resourceId, const Array_TouchTestInfo value,
        const Callback_TouchResult_Void continuation)
    {
        EXPECT_EQ(Convert<int32_t>(resourceId), expectedResourceId);
        auto isCompetition = value.length > 0;
        auto fakeId = std::to_string(value.length);
        Ark_TouchResult arkResult = {
            .strategy = isCompetition ? ARK_TOUCH_TEST_STRATEGY_FORWARD_COMPETITION : ARK_TOUCH_TEST_STRATEGY_FORWARD,
            .id = ArkValue<Opt_String>(fakeId)
        };
        CallbackHelper(continuation).Invoke(arkResult);
    };
    auto arkCallback = Converter::ArkValue<Callback_Array_TouchTestInfo_TouchResult>(nullptr,
        callSyncFunc, expectedResourceId);

    // expect default when nothing callback
    auto result = frameNode->GetOnChildTouchTestRet({});
    EXPECT_EQ(result.strategy, TouchTestStrategy::DEFAULT);

    // set callback func
    modifier_->setOnChildTouchTest(node_, &arkCallback);

    // expect different results depending on input data
    result = frameNode->GetOnChildTouchTestRet({});
    EXPECT_EQ(result.strategy, TouchTestStrategy::FORWARD);
    EXPECT_EQ(result.id, "0");

    std::vector<TouchTestInfo> touchInfo = { TouchTestInfo() };
    result = frameNode->GetOnChildTouchTestRet(touchInfo);
    EXPECT_EQ(result.strategy, TouchTestStrategy::FORWARD_COMPETITION);
    EXPECT_EQ(result.id, "1");
}

/*
 * @tc.name: SetOnOnGestureJudgeBeginTest
 * @tc.desc: Checking the callback operation for a change in breakpoint.
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest7, SetOnOnGestureJudgeBeginTest, TestSize.Level1)
{
    using namespace Converter;
    ASSERT_NE(modifier_->setOnGestureJudgeBegin, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    static const int32_t expectedResourceId = 123;

    auto callSyncFunc = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_GestureInfo gestureInfo,
        const Ark_BaseGestureEvent event, const Callback_GestureJudgeResult_Void continuation)
    {
        EXPECT_EQ(Convert<int32_t>(resourceId), expectedResourceId);
        auto isOk = Convert<bool>(gestureInfo.isSystemGesture);
        Ark_GestureJudgeResult arkResult = isOk ? ARK_GESTURE_JUDGE_RESULT_CONTINUE : ARK_GESTURE_JUDGE_RESULT_REJECT;
        CallbackHelper(continuation).Invoke(arkResult);
    };
    auto arkCallback = Converter::ArkValue<Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult>(nullptr,
        callSyncFunc, expectedResourceId);

    // set callback func
    modifier_->setOnGestureJudgeBegin(node_, &arkCallback);

    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    auto fireOnGestureJudgeBeginCallback = gestureHub->GetOnGestureJudgeBeginCallback();
    ASSERT_NE(fireOnGestureJudgeBeginCallback, nullptr);

    auto baseEvent = std::make_shared<BaseGestureEvent>();
    auto gestInfo = AceType::MakeRefPtr<GestureInfo>();
    gestInfo->SetIsSystemGesture(true);
    GestureJudgeResult gjResult = fireOnGestureJudgeBeginCallback(gestInfo, baseEvent);
    EXPECT_EQ(gjResult, GestureJudgeResult::CONTINUE);

    gestInfo->SetIsSystemGesture(false);
    gjResult = fireOnGestureJudgeBeginCallback(gestInfo, baseEvent);
    EXPECT_EQ(gjResult, GestureJudgeResult::REJECT);
}

/*
 * @tc.name: SetOnGestureRecognizerJudgeBegin1Test
 * @tc.desc: Checking the callback operation for a change in breakpoint.
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest7, SetOnGestureRecognizerJudgeBegin1Test, TestSize.Level1)
{
    using namespace Converter;
    ASSERT_NE(modifier_->setOnGestureRecognizerJudgeBegin1, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    auto callSyncFunc = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_BaseGestureEvent event,
        const Ark_GestureRecognizer current, const Array_GestureRecognizer recognizers,
        const Callback_GestureJudgeResult_Void continuation)
    {
        auto isOk = event.source != ARK_SOURCE_TYPE_UNKNOWN;
        Ark_GestureJudgeResult arkResult = isOk ? ARK_GESTURE_JUDGE_RESULT_CONTINUE : ARK_GESTURE_JUDGE_RESULT_REJECT;
        CallbackHelper(continuation).Invoke(arkResult);
    };
    auto arkCallback = Converter::ArkValue<GestureRecognizerJudgeBeginCallback>(nullptr, callSyncFunc);
    modifier_->setOnGestureRecognizerJudgeBegin1(node_, &arkCallback, ArkValue<Ark_Boolean>(false));

    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    auto fireOnGestureRecognizerJudgeBegin = gestureHub->GetOnGestureRecognizerJudgeBegin();
    ASSERT_NE(fireOnGestureRecognizerJudgeBegin, nullptr);

    auto info = std::make_shared<BaseGestureEvent>();
    auto current = AceType::MakeRefPtr<ClickRecognizer>();
    info->SetSourceDevice(SourceType::MOUSE);
    GestureJudgeResult gjResult = fireOnGestureRecognizerJudgeBegin(info, current, {});
    EXPECT_EQ(gjResult, GestureJudgeResult::CONTINUE);

    info->SetSourceDevice(SourceType::NONE);
    gjResult = fireOnGestureRecognizerJudgeBegin(info, current, {});
    EXPECT_EQ(gjResult, GestureJudgeResult::REJECT);
}

/*
 * @tc.name: SetShouldBuiltInRecognizerParallelWithTest
 * @tc.desc: Checking the callback operation for a change in breakpoint.
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest7, SetShouldBuiltInRecognizerParallelWithTest, TestSize.Level1)
{
    using namespace Converter;
    ASSERT_NE(modifier_->setShouldBuiltInRecognizerParallelWith, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    auto callSyncFunc = [](Ark_VMContext context, const Ark_Int32 resourceId,
        const Ark_GestureRecognizer current, const Array_GestureRecognizer others,
        const Callback_GestureRecognizer_Void continuation)
    {
        Ark_GestureRecognizer arkResult = others.length > 0 && others.array ? *(others.array) : current;
        CallbackHelper(continuation).Invoke(arkResult);
    };
    auto arkCallback = Converter::ArkValue<ShouldBuiltInRecognizerParallelWithCallback>(nullptr, callSyncFunc);
    modifier_->setShouldBuiltInRecognizerParallelWith(node_, &arkCallback);

    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    auto shouldBuiltInRecognizerParallelWithFunc = gestureHub->GetParallelInnerGestureToFunc();
    ASSERT_NE(shouldBuiltInRecognizerParallelWithFunc, nullptr);

    auto current = AceType::MakeRefPtr<ClickRecognizer>();
    auto response = AceType::MakeRefPtr<ClickRecognizer>();
    RefPtr<NGGestureRecognizer> final = shouldBuiltInRecognizerParallelWithFunc(current, {response});
    EXPECT_EQ(final, response);

    final = shouldBuiltInRecognizerParallelWithFunc(current, {});
    EXPECT_EQ(final, current);
}
}
