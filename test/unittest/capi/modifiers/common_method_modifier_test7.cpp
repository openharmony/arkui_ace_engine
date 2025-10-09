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
#include "core/interfaces/native/implementation/drag_event_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/components_ng/gestures/recognizers/click_recognizer.h"
#include "generated/type_helpers.h"
#include "test/unittest/capi/utils/custom_node_builder_test_helper.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG::GeneratedModifier {
    const GENERATED_ArkUIBaseGestureEventAccessor* GetBaseGestureEventAccessor();
    const GENERATED_ArkUIDragEventAccessor* GetDragEventAccessor();
}

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
            case ARK_PRE_DRAG_STATUS_PREPARING_FOR_DRAG_DETECTION:
                dst = PreDragStatus::PREPARING_FOR_DRAG_DETECTION;
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

    template<>
    RefPtr<OHOS::Ace::DragEvent> Convert(const Ark_DragEvent& dragEvent)
    {
        return dragEvent ? dragEvent->dragInfo : nullptr;
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
HWTEST_F(CommonMethodModifierTest7, DISABLED_SetOnPreDragTest, TestSize.Level1)
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

    Callback_PreDragStatus_Void arkCallBackValue = {
        .resource = Ark_CallbackResource {
            .resourceId = frameNode->GetId(),
            .hold = nullptr,
            .release = nullptr,
        },
        .call = onPreDrag
    };
    auto callBackValue = Converter::ArkValue<Opt_Callback_PreDragStatus_Void>(arkCallBackValue);

    auto test = [this, &callBackValue, eventHub, frameNode](const PreDragStatus& testValue) {
        checkEvent = std::nullopt;
        modifier_->setOnPreDrag(node_, &callBackValue);
        EXPECT_FALSE(checkEvent.has_value());
        auto onPreDragFunc = eventHub->GetOnPreDrag();
        ASSERT_NE(onPreDragFunc, nullptr);
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
    test(PreDragStatus::PREPARING_FOR_DRAG_DETECTION);
}

/*
 * @tc.name: SetOnDragEnter
 * @tc.desc: Checking the callback operation for a change in breakpoint.
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest7, DISABLED_SetOnDragEnterTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    // OHOS::Ace::NG::EventHub
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        RefPtr<OHOS::Ace::DragEvent> dragEvent;
        std::optional<std::string> extraParams;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    const auto extraParamsString = "The test string";

    auto onDragFunc = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_DragEvent event,
        const Opt_String extraParams) {
        checkEvent = {
            .nodeId = resourceId,
            .dragEvent = Converter::Convert<RefPtr<OHOS::Ace::DragEvent>>(event),
            .extraParams = Converter::OptConvert<std::string>(extraParams),
        };
        GeneratedModifier::GetDragEventAccessor()->destroyPeer(event);
    };

    auto arkCallBackValue = Converter::ArkValue<Callback_DragEvent_Opt_String_Void>(
        nullptr, onDragFunc, frameNode->GetId());
    auto callBackValue = Converter::ArkValue<Opt_Callback_DragEvent_Opt_String_Void>(arkCallBackValue);

    checkEvent = std::nullopt;
    modifier_->setOnDragEnter(node_, &callBackValue);
    EXPECT_FALSE(checkEvent.has_value());

    RefPtr<OHOS::Ace::DragEvent> dragEventPtr = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    eventHub->FireCustomerOnDragFunc(DragFuncType::DRAG_ENTER, dragEventPtr, extraParamsString);

    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->dragEvent, dragEventPtr);
    EXPECT_EQ(checkEvent->extraParams, extraParamsString);
}

/*
 * @tc.name: SetOnDragMove
 * @tc.desc: Checking the callback operation for a change in breakpoint.
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest7, DISABLED_SetOnDragMoveTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    // OHOS::Ace::NG::EventHub
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        RefPtr<OHOS::Ace::DragEvent> dragEvent;
        std::optional<std::string> extraParams;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    const auto extraParamsString = "The test string";

    auto onDragFunc = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_DragEvent event,
        const Opt_String extraParams) {
        checkEvent = {
            .nodeId = resourceId,
            .dragEvent = Converter::Convert<RefPtr<OHOS::Ace::DragEvent>>(event),
            .extraParams = Converter::OptConvert<std::string>(extraParams),
        };
        GeneratedModifier::GetDragEventAccessor()->destroyPeer(event);
    };

    auto arkCallBackValue = Converter::ArkValue<Callback_DragEvent_Opt_String_Void>(
        nullptr, onDragFunc, frameNode->GetId());
    auto callBackValue = Converter::ArkValue<Opt_Callback_DragEvent_Opt_String_Void>(arkCallBackValue);

    checkEvent = std::nullopt;
    modifier_->setOnDragMove(node_, &callBackValue);
    EXPECT_FALSE(checkEvent.has_value());

    RefPtr<OHOS::Ace::DragEvent> dragEventPtr = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    eventHub->FireCustomerOnDragFunc(DragFuncType::DRAG_MOVE, dragEventPtr, extraParamsString);

    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->dragEvent, dragEventPtr);
    EXPECT_EQ(checkEvent->extraParams, extraParamsString);
}

/*
 * @tc.name: SetOnDragLeave
 * @tc.desc: Checking the callback operation for a change in breakpoint.
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest7, DISABLED_SetOnDragLeaveTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    // OHOS::Ace::NG::EventHub
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        RefPtr<OHOS::Ace::DragEvent> dragEvent;
        std::optional<std::string> extraParams;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    const auto extraParamsString = "The test string";

    auto onDragFunc = [](Ark_VMContext context, const Ark_Int32 resourceId,
        const Ark_DragEvent event, const Opt_String extraParams) {
        checkEvent = {
            .nodeId = resourceId,
            .dragEvent = Converter::Convert<RefPtr<OHOS::Ace::DragEvent>>(event),
            .extraParams = Converter::OptConvert<std::string>(extraParams),
        };
        GeneratedModifier::GetDragEventAccessor()->destroyPeer(event);
    };

    auto arkCallBackValue = Converter::ArkValue<Callback_DragEvent_Opt_String_Void>(
        nullptr, onDragFunc, frameNode->GetId());
    auto callBackValue = Converter::ArkValue<Opt_Callback_DragEvent_Opt_String_Void>(arkCallBackValue);

    checkEvent = std::nullopt;
    modifier_->setOnDragLeave(node_, &callBackValue);
    EXPECT_FALSE(checkEvent.has_value());

    RefPtr<OHOS::Ace::DragEvent> dragEventPtr = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    eventHub->FireCustomerOnDragFunc(DragFuncType::DRAG_LEAVE, dragEventPtr, extraParamsString);

    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->dragEvent, dragEventPtr);
    EXPECT_EQ(checkEvent->extraParams, extraParamsString);
}

/*
 * @tc.name: SetOnDrop
 * @tc.desc: Checking the callback operation for a change in breakpoint.
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest7, DISABLED_SetOnDrop0Test, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    // OHOS::Ace::NG::EventHub
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        RefPtr<OHOS::Ace::DragEvent> dragEvent;
        std::optional<std::string> extraParams;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    const auto extraParamsString = "The test string";

    auto onDragFunc = [](Ark_VMContext context, const Ark_Int32 resourceId,
        const Ark_DragEvent event, const Opt_String extraParams) {
        checkEvent = {
            .nodeId = resourceId,
            .dragEvent = Converter::Convert<RefPtr<OHOS::Ace::DragEvent>>(event),
            .extraParams = Converter::OptConvert<std::string>(extraParams),
        };
        GeneratedModifier::GetDragEventAccessor()->destroyPeer(event);
    };

    auto arkCallBackValue = Converter::ArkValue<Callback_DragEvent_Opt_String_Void>(
        nullptr, onDragFunc, frameNode->GetId());
    auto callBackValue = Converter::ArkValue<Opt_Callback_DragEvent_Opt_String_Void>(arkCallBackValue);

    checkEvent = std::nullopt;
    modifier_->setOnDrop0(node_, &callBackValue);
    EXPECT_FALSE(checkEvent.has_value());

    RefPtr<OHOS::Ace::DragEvent> dragEventPtr = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    eventHub->FireCustomerOnDragFunc(DragFuncType::DRAG_DROP, dragEventPtr, extraParamsString);

    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->dragEvent, dragEventPtr);
    EXPECT_EQ(checkEvent->extraParams, extraParamsString);
}

/*
 * @tc.name: SetOnDragEnd
 * @tc.desc: Checking the callback operation for a change in breakpoint.
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest7, DISABLED_SetOnDragEndTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    // OHOS::Ace::NG::EventHub
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        RefPtr<OHOS::Ace::DragEvent> dragEvent;
        std::optional<std::string> extraParams;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    auto onDragFunc = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_DragEvent event,
        const Opt_String extraParams) {
        checkEvent = {
            .nodeId = resourceId,
            .dragEvent = Converter::Convert<RefPtr<OHOS::Ace::DragEvent>>(event),
            .extraParams = Converter::OptConvert<std::string>(extraParams),
        };
        GeneratedModifier::GetDragEventAccessor()->destroyPeer(event);
    };

    auto arkCallBackValue = Converter::ArkValue<Callback_DragEvent_Opt_String_Void>(
        nullptr, onDragFunc, frameNode->GetId());
    auto callBackValue = Converter::ArkValue<Opt_Callback_DragEvent_Opt_String_Void>(arkCallBackValue);

    checkEvent = std::nullopt;
    modifier_->setOnDragEnd(node_, &callBackValue);
    EXPECT_FALSE(checkEvent.has_value());

    RefPtr<OHOS::Ace::DragEvent> dragEventPtr = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    eventHub->FireCustomerOnDragFunc(DragFuncType::DRAG_END, dragEventPtr);

    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->dragEvent, dragEventPtr);
    EXPECT_EQ(checkEvent->extraParams, "");
}

/*
 * @tc.name: SetOnDragStartTestCOPY
 * @tc.desc: Checking the callback operation for a change in breakpoint.
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest7, DISABLED_SetOnDragStartTestCOPY, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnDragStart, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    static const int32_t expectedResourceId = 123;
    static const std::string expectedInfo("key:value");
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest7> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;

    struct CheckEvent {
        int32_t nodeId;
        RefPtr<OHOS::Ace::DragEvent> dragEvent;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    auto callSyncFunc = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_DragEvent event,
        const Opt_String extraP, const Callback_Union_CustomBuilder_DragItemInfo_Void continuation)
    {
        EXPECT_EQ(Converter::Convert<int32_t>(resourceId), expectedResourceId);
        // the different type in return value depending on input data
        Ark_Union_CustomBuilder_DragItemInfo arkResult;
        checkEvent->dragEvent = Converter::Convert<RefPtr<OHOS::Ace::DragEvent>>(event);
        checkEvent->nodeId = resourceId;
        auto isNeedBuilder = checkEvent->dragEvent->GetDragBehavior() == DragBehavior::MOVE;
        if (isNeedBuilder) {
            TypeHelper::WriteToUnion<CustomNodeBuilder>(arkResult) = *arkBuilder;
        } else {
            TypeHelper::WriteToUnion<Ark_DragItemInfo>(arkResult).extraInfo = Converter::ArkValue<Opt_String>(extraP);
        }
        CallbackHelper(continuation).InvokeSync(arkResult);
        GeneratedModifier::GetDragEventAccessor()->destroyPeer(event);
    };

    auto arkCallback = Converter::ArkValue<Type_CommonMethod_onDragStart>(nullptr,
        callSyncFunc, expectedResourceId);
    auto optCallback = Converter::ArkValue<Opt_Type_CommonMethod_onDragStart>(arkCallback);
    modifier_->setOnDragStart(node_, &optCallback);

    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto fireOnDragStart = eventHub->GetOnDragStart();
    ASSERT_NE(fireOnDragStart, nullptr);

    auto dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    dragEvent->SetDragBehavior(DragBehavior::COPY);
    DragDropInfo ddInfo = fireOnDragStart(dragEvent, expectedInfo);
    EXPECT_EQ(ddInfo.customNode, nullptr);
    EXPECT_EQ(checkEvent->dragEvent, dragEvent);
    EXPECT_EQ(ddInfo.extraInfo, expectedInfo);
    arkBuilder = nullptr;
}

/*
 * @tc.name: SetOnDragStartTestMOVE
 * @tc.desc: Checking the callback operation for a change in breakpoint.
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest7, DISABLED_SetOnDragStartTestMOVE, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnDragStart, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    auto callsCount = 0;
    static const int32_t expectedResourceId = 123;
    static const std::string expectedInfo("key:value");
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest7> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;

    struct CheckEvent {
        int32_t nodeId;
        RefPtr<OHOS::Ace::DragEvent> dragEvent;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto callSyncFunc = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_DragEvent event,
        const Opt_String extraP, const Callback_Union_CustomBuilder_DragItemInfo_Void continuation)
    {
        EXPECT_EQ(Converter::Convert<int32_t>(resourceId), expectedResourceId);
        // the different type in return value depending on input data
        Ark_Union_CustomBuilder_DragItemInfo arkResult;
        checkEvent->dragEvent = Converter::Convert<RefPtr<OHOS::Ace::DragEvent>>(event);
        checkEvent->nodeId = resourceId;
        auto isNeedBuilder = checkEvent->dragEvent->GetDragBehavior() == DragBehavior::MOVE;
        if (isNeedBuilder) {
            TypeHelper::WriteToUnion<CustomNodeBuilder>(arkResult) = *arkBuilder;
        } else {
            TypeHelper::WriteToUnion<Ark_DragItemInfo>(arkResult).extraInfo = Converter::ArkValue<Opt_String>(extraP);
        }
        CallbackHelper(continuation).InvokeSync(arkResult);
        GeneratedModifier::GetDragEventAccessor()->destroyPeer(event);
    };

    auto arkCallback = Converter::ArkValue<Type_CommonMethod_onDragStart>(nullptr,
        callSyncFunc, expectedResourceId);
    auto optCallback = Converter::ArkValue<Opt_Type_CommonMethod_onDragStart>(arkCallback);
    modifier_->setOnDragStart(node_, &optCallback);

    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto fireOnDragStart = eventHub->GetOnDragStart();
    ASSERT_NE(fireOnDragStart, nullptr);

    auto dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    dragEvent->SetDragBehavior(DragBehavior::MOVE);
    DragDropInfo ddInfo = fireOnDragStart(dragEvent, expectedInfo);
    const DragDropInfo resultDragPreview = frameNode->GetDragPreview();
    EXPECT_EQ(builderHelper.GetCallsCount(), ++callsCount);
    EXPECT_EQ(ddInfo.extraInfo, std::string());
    arkBuilder = nullptr;
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
        CallbackHelper(continuation).InvokeSync(arkResult);
    };
    auto arkCallback = Converter::ArkValue<Callback_Array_TouchTestInfo_TouchResult>(nullptr,
        callSyncFunc, expectedResourceId);
    auto optCallback = Converter::ArkValue<Opt_Callback_Array_TouchTestInfo_TouchResult>(arkCallback);

    // expect default when nothing callback
    auto result = frameNode->GetOnChildTouchTestRet({});
    EXPECT_EQ(result.strategy, TouchTestStrategy::DEFAULT);

    // set callback func
    modifier_->setOnChildTouchTest(node_, &optCallback);

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
        CallbackHelper(continuation).InvokeSync(arkResult);
    };
    auto arkCallback = Converter::ArkValue<Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult>(nullptr,
        callSyncFunc, expectedResourceId);
    auto optCallback = Converter::ArkValue<Opt_Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult>(arkCallback);

    // set callback func
    modifier_->setOnGestureJudgeBegin(node_, &optCallback);

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
 * @tc.name: SetOnGestureRecognizerJudgeBegin0Test
 * @tc.desc: Checking the callback operation for a change in breakpoint.
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest7, DISABLED_SetOnGestureRecognizerJudgeBegin0Test, TestSize.Level1)
{
    using namespace Converter;
    ASSERT_NE(modifier_->setOnGestureRecognizerJudgeBegin0, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    auto callSyncFunc = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_BaseGestureEvent event,
        const Ark_GestureRecognizer current, const Array_GestureRecognizer recognizers,
        const Callback_GestureJudgeResult_Void continuation)
    {
        auto info = event ? event->GetBaseGestureInfo() : nullptr;
        GeneratedModifier::GetBaseGestureEventAccessor()->destroyPeer(event);
        ASSERT_NE(info, nullptr);
        auto isOk = info->GetSourceDevice() != SourceType::NONE;
        Ark_GestureJudgeResult arkResult = isOk ? ARK_GESTURE_JUDGE_RESULT_CONTINUE : ARK_GESTURE_JUDGE_RESULT_REJECT;
        CallbackHelper(continuation).InvokeSync(arkResult);
    };
    auto arkCallback = Converter::ArkValue<GestureRecognizerJudgeBeginCallback>(nullptr, callSyncFunc);
    auto optCallback = Converter::ArkValue<Opt_GestureRecognizerJudgeBeginCallback>(arkCallback);
    modifier_->setOnGestureRecognizerJudgeBegin0(node_, &optCallback);

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
 * @tc.name: SetOnGestureRecognizerJudgeBegin1Test
 * @tc.desc: Checking the callback operation for a change in breakpoint.
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest7, DISABLED_SetOnGestureRecognizerJudgeBegin1Test, TestSize.Level1)
{
    using namespace Converter;
    ASSERT_NE(modifier_->setOnGestureRecognizerJudgeBegin1, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    auto callSyncFunc = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_BaseGestureEvent event,
        const Ark_GestureRecognizer current, const Array_GestureRecognizer recognizers,
        const Callback_GestureJudgeResult_Void continuation)
    {
        auto info = event ? event->GetBaseGestureInfo() : nullptr;
        GeneratedModifier::GetBaseGestureEventAccessor()->destroyPeer(event);
        ASSERT_NE(info, nullptr);
        auto isOk = info->GetSourceDevice() != SourceType::NONE;
        Ark_GestureJudgeResult arkResult = isOk ? ARK_GESTURE_JUDGE_RESULT_CONTINUE : ARK_GESTURE_JUDGE_RESULT_REJECT;
        CallbackHelper(continuation).InvokeSync(arkResult);
    };
    auto arkCallback = Converter::ArkValue<GestureRecognizerJudgeBeginCallback>(nullptr, callSyncFunc);
    auto optCallback = Converter::ArkValue<Opt_GestureRecognizerJudgeBeginCallback>(arkCallback);
    auto exposeInnerGesture = Converter::ArkValue<Opt_Boolean>(false);
    modifier_->setOnGestureRecognizerJudgeBegin1(node_, &optCallback, &exposeInnerGesture);

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
        CallbackHelper(continuation).InvokeSync(arkResult);
    };
    auto arkCallback = Converter::ArkValue<ShouldBuiltInRecognizerParallelWithCallback>(nullptr, callSyncFunc);
    auto optCallback = Converter::ArkValue<Opt_ShouldBuiltInRecognizerParallelWithCallback>(arkCallback);
    modifier_->setShouldBuiltInRecognizerParallelWith(node_, &optCallback);

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
