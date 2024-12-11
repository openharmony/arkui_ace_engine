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

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    // const auto ATTRIBUTE_LINEAR_GRADIENT_BLUR_NAME = "linearGradientBlur";
    // const auto ATTRIBUTE_LINEAR_GRADIENT_BLUR_DEFAULT_VALUE = "";
    // Structure for tracking events
    // struct EventsTracker {
    //     static inline GENERATED_ArkUICommonMethodEventsReceiver commonMethodEventsReceiver {};
    //     static inline const GENERATED_ArkUIEventsAPI eventsApiImpl = {
    //         .getCommonMethodEventsReceiver = []() -> const GENERATED_ArkUICommonMethodEventsReceiver* {
    //             return &commonMethodEventsReceiver;
    //         }
    //     };
    // }; // EventsTracker
}
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
}

class CommonMethodModifierTest7 : public ModifierTestBase<GENERATED_ArkUICommonMethodModifier,
    &GENERATED_ArkUINodeModifiers::getCommonMethodModifier,
    GENERATED_ARKUI_BLANK // test common methods on frameNode for Blank component
    > {
public:
    RefPtr<RenderContext> render_;

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

/* Auto generated test
 * @tc.name: SetOnPreDrag
 * @tc.desc: Checking the callback operation for a change in breakpoint.
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest7, SetOnPreDragTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
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

    auto Test = [this, &callBackValue, eventHub, frameNode](const PreDragStatus& testValue) {
        checkEvent = std::nullopt;
        modifier_->setOnPreDrag(node_, &callBackValue);
        EXPECT_FALSE(checkEvent.has_value());
        auto onPreDragFunc = eventHub->GetOnPreDrag();
        onPreDragFunc(testValue);
        ASSERT_TRUE(checkEvent.has_value());
        EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
        EXPECT_EQ(checkEvent->preDragStatus, testValue);
    };

    Test(PreDragStatus::ACTION_DETECTING_STATUS);
    Test(PreDragStatus::READY_TO_TRIGGER_DRAG_ACTION);
    Test(PreDragStatus::PREVIEW_LIFT_STARTED);
    Test(PreDragStatus::PREVIEW_LIFT_FINISHED);
    Test(PreDragStatus::PREVIEW_LANDING_STARTED);
    Test(PreDragStatus::PREVIEW_LANDING_FINISHED);
    Test(PreDragStatus::ACTION_CANCELED_BEFORE_DRAG);
}

/* Auto generated test
 * @tc.name: SetOnDragEnter
 * @tc.desc: Checking the callback operation for a change in breakpoint.
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest7, SetOnDragEnterTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        PreDragStatus preDragStatus;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    auto onDragEnter = [](Ark_Int32 nodeId, const Ark_PreDragStatus preDragStatus) {
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
        .call = onDragEnter
    };

    auto Test = [this, &callBackValue, eventHub, frameNode](const RefPtr<DragEvent>& testDragEventPtr,
                                                            const std::string& testStrValue) {
        checkEvent = std::nullopt;
        modifier_->setOnDragEnter(node_, &callBackValue);
        EXPECT_FALSE(checkEvent.has_value());
        auto onDragEnterFunc = eventHub->GetOnDragEnter();
        onDragEnterFunc(testDragEventPtr, testStrValue);
        ASSERT_TRUE(checkEvent.has_value());
        EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
        EXPECT_EQ(checkEvent->preDragStatus, testValue);
    };

    Test(PreDragStatus::ACTION_DETECTING_STATUS);
    Test(PreDragStatus::READY_TO_TRIGGER_DRAG_ACTION);
    Test(PreDragStatus::PREVIEW_LIFT_STARTED);
    Test(PreDragStatus::PREVIEW_LIFT_FINISHED);
    Test(PreDragStatus::PREVIEW_LANDING_STARTED);
    Test(PreDragStatus::PREVIEW_LANDING_FINISHED);
    Test(PreDragStatus::ACTION_CANCELED_BEFORE_DRAG);
}
}
