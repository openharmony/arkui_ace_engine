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
#include "generated/type_helpers.h"
#include "test/unittest/capi/utils/custom_node_builder_test_helper.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG::GeneratedModifier {
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
        auto dragEventPeer = reinterpret_cast<DragEventPeer*>(dragEvent.ptr);
        return (dragEventPeer && dragEventPeer->dragInfo) ? dragEventPeer->dragInfo : nullptr;
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
        RefPtr<OHOS::Ace::DragEvent> dragEvent;
        std::optional<std::string> extraParams;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    const auto extraParamsString = "The test string";

    auto onDragFunc = [](const Ark_Int32 resourceId, const Ark_DragEvent event, const Opt_String extraParams) {
        checkEvent = {
            .nodeId = resourceId,
            .dragEvent = Converter::Convert<RefPtr<OHOS::Ace::DragEvent>>(event),
            .extraParams = Converter::OptConvert<std::string>(extraParams),
        };
        auto deletePtr = reinterpret_cast<DragEventPeer*>(event.ptr);
        GeneratedModifier::GetDragEventAccessor()->destroyPeer(deletePtr);
    };

    auto callBackValue = Converter::ArkValue<Callback_DragEvent_String_Void>(onDragFunc, frameNode->GetId());

    checkEvent = std::nullopt;
    modifier_->setOnDragEnter(node_, &callBackValue);
    EXPECT_FALSE(checkEvent.has_value());

    RefPtr<OHOS::Ace::DragEvent> dragEventPtr = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    eventHub->FireCustomerOnDragFunc(DragFuncType::DRAG_ENTER, dragEventPtr, extraParamsString);

    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->dragEvent.GetRawPtr(), dragEventPtr.GetRawPtr());
    EXPECT_EQ(checkEvent->extraParams, extraParamsString);
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
        RefPtr<OHOS::Ace::DragEvent> dragEvent;
        std::optional<std::string> extraParams;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    const auto extraParamsString = "The test string";

    auto onDragFunc = [](const Ark_Int32 resourceId, const Ark_DragEvent event, const Opt_String extraParams) {
        checkEvent = {
            .nodeId = resourceId,
            .dragEvent = Converter::Convert<RefPtr<OHOS::Ace::DragEvent>>(event),
            .extraParams = Converter::OptConvert<std::string>(extraParams),
        };
        auto deletePtr = reinterpret_cast<DragEventPeer*>(event.ptr);
        GeneratedModifier::GetDragEventAccessor()->destroyPeer(deletePtr);
    };

    auto callBackValue = Converter::ArkValue<Callback_DragEvent_String_Void>(onDragFunc, frameNode->GetId());

    checkEvent = std::nullopt;
    modifier_->setOnDragMove(node_, &callBackValue);
    EXPECT_FALSE(checkEvent.has_value());

    RefPtr<OHOS::Ace::DragEvent> dragEventPtr = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    eventHub->FireCustomerOnDragFunc(DragFuncType::DRAG_MOVE, dragEventPtr, extraParamsString);

    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->dragEvent.GetRawPtr(), dragEventPtr.GetRawPtr());
    EXPECT_EQ(checkEvent->extraParams, extraParamsString);
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
        RefPtr<OHOS::Ace::DragEvent> dragEvent;
        std::optional<std::string> extraParams;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    const auto extraParamsString = "The test string";

    auto onDragFunc = [](const Ark_Int32 resourceId, const Ark_DragEvent event, const Opt_String extraParams) {
        checkEvent = {
            .nodeId = resourceId,
            .dragEvent = Converter::Convert<RefPtr<OHOS::Ace::DragEvent>>(event),
            .extraParams = Converter::OptConvert<std::string>(extraParams),
        };
        auto deletePtr = reinterpret_cast<DragEventPeer*>(event.ptr);
        GeneratedModifier::GetDragEventAccessor()->destroyPeer(deletePtr);
    };

    auto callBackValue = Converter::ArkValue<Callback_DragEvent_String_Void>(onDragFunc, frameNode->GetId());

    checkEvent = std::nullopt;
    modifier_->setOnDragLeave(node_, &callBackValue);
    EXPECT_FALSE(checkEvent.has_value());

    RefPtr<OHOS::Ace::DragEvent> dragEventPtr = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    eventHub->FireCustomerOnDragFunc(DragFuncType::DRAG_LEAVE, dragEventPtr, extraParamsString);

    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->dragEvent.GetRawPtr(), dragEventPtr.GetRawPtr());
    EXPECT_EQ(checkEvent->extraParams, extraParamsString);
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
        RefPtr<OHOS::Ace::DragEvent> dragEvent;
        std::optional<std::string> extraParams;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    const auto extraParamsString = "The test string";

    auto onDragFunc = [](const Ark_Int32 resourceId, const Ark_DragEvent event, const Opt_String extraParams) {
        checkEvent = {
            .nodeId = resourceId,
            .dragEvent = Converter::Convert<RefPtr<OHOS::Ace::DragEvent>>(event),
            .extraParams = Converter::OptConvert<std::string>(extraParams),
        };
        auto deletePtr = reinterpret_cast<DragEventPeer*>(event.ptr);
        GeneratedModifier::GetDragEventAccessor()->destroyPeer(deletePtr);
    };

    auto callBackValue = Converter::ArkValue<Callback_DragEvent_String_Void>(onDragFunc, frameNode->GetId());

    checkEvent = std::nullopt;
    modifier_->setOnDrop(node_, &callBackValue);
    EXPECT_FALSE(checkEvent.has_value());

    RefPtr<OHOS::Ace::DragEvent> dragEventPtr = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    eventHub->FireCustomerOnDragFunc(DragFuncType::DRAG_DROP, dragEventPtr, extraParamsString);

    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->dragEvent.GetRawPtr(), dragEventPtr.GetRawPtr());
    EXPECT_EQ(checkEvent->extraParams, extraParamsString);
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
        RefPtr<OHOS::Ace::DragEvent> dragEvent;
        std::optional<std::string> extraParams;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    auto onDragFunc = [](const Ark_Int32 resourceId, const Ark_DragEvent event, const Opt_String extraParams) {
        checkEvent = {
            .nodeId = resourceId,
            .dragEvent = Converter::Convert<RefPtr<OHOS::Ace::DragEvent>>(event),
            .extraParams = Converter::OptConvert<std::string>(extraParams),
        };
        auto deletePtr = reinterpret_cast<DragEventPeer*>(event.ptr);
        GeneratedModifier::GetDragEventAccessor()->destroyPeer(deletePtr);
    };

    auto callBackValue = Converter::ArkValue<Callback_DragEvent_String_Void>(onDragFunc, frameNode->GetId());

    checkEvent = std::nullopt;
    modifier_->setOnDragEnd(node_, &callBackValue);
    EXPECT_FALSE(checkEvent.has_value());

    RefPtr<OHOS::Ace::DragEvent> dragEventPtr = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    eventHub->FireCustomerOnDragFunc(DragFuncType::DRAG_END, dragEventPtr);

    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->dragEvent.GetRawPtr(), dragEventPtr.GetRawPtr());
    EXPECT_EQ(checkEvent->extraParams, "");
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

    auto callsCount = 0;
    static const int32_t expectedResourceId = 123;
    static const std::string expectedInfo("key:value");
    static const CustomNodeBuilderTestHelper<CommonMethodModifierTest7> builderHelper(this, frameNode);

    static const CustomNodeBuilder builder = builderHelper.GetBuilder();

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
            TypeHelper::WriteToUnion<CustomNodeBuilder>(arkResult) = builder;
        } else {
            TypeHelper::WriteToUnion<Ark_DragItemInfo>(arkResult).extraInfo = Converter::ArkValue<Opt_String>(extraP);
        }
        CallbackHelper(continuation).Invoke(arkResult);
        auto deletePtr = reinterpret_cast<DragEventPeer*>(event.ptr);
        GeneratedModifier::GetDragEventAccessor()->destroyPeer(deletePtr);
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
    const DragDropInfo resultDragPreview = frameNode->GetDragPreview();
    EXPECT_EQ(builderHelper.GetCallsCount(), ++callsCount);
    EXPECT_EQ(ddInfo.extraInfo, std::string());

    dragEvent->SetDragBehavior(DragBehavior::COPY);
    ddInfo = fireOnDragStart(dragEvent, expectedInfo);
    EXPECT_EQ(ddInfo.customNode, nullptr);
    EXPECT_EQ(checkEvent->dragEvent.GetRawPtr(), dragEvent.GetRawPtr());
    EXPECT_EQ(ddInfo.extraInfo, expectedInfo);
}
}
