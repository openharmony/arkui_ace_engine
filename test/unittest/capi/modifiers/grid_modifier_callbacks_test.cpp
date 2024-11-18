/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <gtest/gtest.h>
#include <climits>

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"

#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/grid/grid_event_hub.h"

#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    struct EventsTracker {
        static inline GENERATED_ArkUIGridEventsReceiver gridEventsReceiver {};

        static inline const GENERATED_ArkUIEventsAPI eventsApiImpl = {
            .getGridEventsReceiver = [] () -> const GENERATED_ArkUIGridEventsReceiver* {
                return &gridEventsReceiver;
            }
        };
    }; // EventsTracker
} // namespace

class GridModifierCallbacksTest : public ModifierTestBase<GENERATED_ArkUIGridModifier,
    &GENERATED_ArkUINodeModifiers::getGridModifier, GENERATED_ARKUI_GRID> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        fullAPI_->setArkUIEventsAPI(&EventsTracker::eventsApiImpl);
    }
};

/*
 * @tc.name: DISABLED_setOnScrollBarUpdateTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierCallbacksTest, DISABLED_setOnScrollBarUpdateTest, TestSize.Level1)
{
    // test is disabled because onScrollBarUpdate callback should return value
    Callback_Number_Number_ComputedBarAttribute func{};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();

    struct CheckEvent {
        int32_t nodeId;
        int32_t index;
        Dimension offset;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    EventsTracker::gridEventsReceiver.onScrollBarUpdate =
        [](Ark_Int32 nodeId, const Ark_Number index, const Ark_Number offset)
    {
        checkEvent = {
            .nodeId = nodeId,
            .index = Converter::Convert<int32_t>(index),
            .offset = Converter::Convert<Dimension>(offset)
        };
    };

    modifier_->setOnScrollBarUpdate(node_, &func);

    // index: 1, offset: 2vp
    EXPECT_EQ(checkEvent.has_value(), false);
    eventHub->FireOnScrollBarUpdate(1, Dimension(2, DimensionUnit::VP));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->index, 1);
    EXPECT_EQ(checkEvent->offset.Value(), 2);
    EXPECT_EQ(checkEvent->offset.Unit(), DimensionUnit::VP);

    // index: 3, offset: 4px
    eventHub->FireOnScrollBarUpdate(3, Dimension(4, DimensionUnit::PX));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->index, 3);
    EXPECT_EQ(checkEvent->offset.Value(), 4);
    EXPECT_EQ(checkEvent->offset.Unit(), DimensionUnit::VP);

    // index: 5, offset: 6
    eventHub->FireOnScrollBarUpdate(5, Dimension(6, DimensionUnit::NONE));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->index, 5);
    EXPECT_EQ(checkEvent->offset.Value(), 6);
    EXPECT_EQ(checkEvent->offset.Unit(), DimensionUnit::VP);

    // index: 7, offset: 8fp
    eventHub->FireOnScrollBarUpdate(7, Dimension(8, DimensionUnit::FP));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->index, 7);
    EXPECT_EQ(checkEvent->offset.Value(), 8);
    EXPECT_EQ(checkEvent->offset.Unit(), DimensionUnit::VP);
}

/*
 * @tc.name: DISABLED_setOnScrollBarUpdateTestInvalid
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierCallbacksTest, DISABLED_setOnScrollBarUpdateTestInvalid, TestSize.Level1)
{
    // test is disabled because onScrollBarUpdate callback should return value
    Callback_Number_Number_ComputedBarAttribute func{};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();

    struct CheckEvent {
        int32_t nodeId;
        int32_t index;
        Dimension offset;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    EventsTracker::gridEventsReceiver.onScrollBarUpdate =
        [](Ark_Int32 nodeId, const Ark_Number index, const Ark_Number offset)
    {
        checkEvent = {
            .nodeId = nodeId,
            .index = Converter::Convert<int32_t>(index),
            .offset = Converter::Convert<Dimension>(offset)
        };
    };

    modifier_->setOnScrollBarUpdate(node_, &func);

    // index: 11, offset: 12 invalid
    EXPECT_EQ(checkEvent.has_value(), false);
    eventHub->FireOnScrollBarUpdate(11, Dimension(12, DimensionUnit::INVALID));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->index, 11);
    EXPECT_EQ(checkEvent->offset.Value(), 0);
    EXPECT_EQ(checkEvent->offset.Unit(), DimensionUnit::VP);

    // index: 12, offset: 14%
    eventHub->FireOnScrollBarUpdate(13, Dimension(14, DimensionUnit::PERCENT));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->index, 13);
    EXPECT_EQ(checkEvent->offset.Value(), 0);
    EXPECT_EQ(checkEvent->offset.Unit(), DimensionUnit::VP);

    // index: 15, offset: 16 auto
    eventHub->FireOnScrollBarUpdate(15, Dimension(16, DimensionUnit::AUTO));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->index, 15);
    EXPECT_EQ(checkEvent->offset.Value(), 0);
    EXPECT_EQ(checkEvent->offset.Unit(), DimensionUnit::VP);

    // index: 17, offset: 18 calc
    eventHub->FireOnScrollBarUpdate(17, Dimension(18, DimensionUnit::CALC));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->index, 17);
    EXPECT_EQ(checkEvent->offset.Value(), 0);
    EXPECT_EQ(checkEvent->offset.Unit(), DimensionUnit::VP);
}

/*
 * @tc.name: setOnScrollIndexTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierCallbacksTest, setOnScrollIndexTest, TestSize.Level1)
{
    Callback_Number_Number_Void func{};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();

    struct CheckEvent {
        int32_t nodeId;
        int32_t first;
        int32_t last;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    EventsTracker::gridEventsReceiver.onScrollIndex =
        [](Ark_Int32 nodeId, const Ark_Number first, const Ark_Number last)
    {
        checkEvent = {
            .nodeId = nodeId,
            .first = Converter::Convert<int32_t>(first),
            .last = Converter::Convert<int32_t>(last)
        };
    };

    modifier_->setOnScrollIndex(node_, &func);

    auto onScrollIndex = eventHub->GetOnScrollIndex();
    EXPECT_NE(onScrollIndex, nullptr);
    EXPECT_EQ(checkEvent.has_value(), false);

    // first: 0, last: 10
    onScrollIndex(0, 10);
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->first, 0);
    EXPECT_EQ(checkEvent->last, 10);

    // first: 5, last: 25
    onScrollIndex(5, 25);
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->first, 5);
    EXPECT_EQ(checkEvent->last, 25);
}

/*
 * @tc.name: DISABLED_setOnItemDragStartTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierCallbacksTest, DISABLED_setOnItemDragStartTest, TestSize.Level1)
{
    // test is disabled because onItemDragStart should return value
    Callback_ItemDragInfo_Number_Callback_Any func{};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    auto dragInfo = ItemDragInfo();

    struct CheckEvent {
        int32_t nodeId;
        ItemDragInfo dragInfo;
        int32_t itemIndex;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    EventsTracker::gridEventsReceiver.onItemDragStart = [](Ark_Int32 nodeId,
        const Ark_ItemDragInfo event, const Ark_Number itemIndex)
    {
        checkEvent = {
            .nodeId = nodeId,
            .dragInfo = Converter::Convert<ItemDragInfo>(event),
            .itemIndex = Converter::Convert<int32_t>(itemIndex)
        };
    };

    modifier_->setOnItemDragStart(node_, &func);

    dragInfo.SetX(357);
    dragInfo.SetY(468);

    EXPECT_FALSE(checkEvent.has_value());
    eventHub->FireOnItemDragStart(dragInfo, 7);
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->dragInfo.GetX(), 357);
    EXPECT_EQ(checkEvent->dragInfo.GetY(), 468);
    EXPECT_EQ(checkEvent->itemIndex, 7);
}

/*
 * @tc.name: setOnItemDragEnterTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierCallbacksTest, setOnItemDragEnterTest, TestSize.Level1)
{
    Callback_ItemDragInfo_Void func{};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    auto dragInfo = ItemDragInfo();

    struct CheckEvent {
        int32_t nodeId;
        ItemDragInfo dragInfo;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    EventsTracker::gridEventsReceiver.onItemDragEnter = [](
        Ark_Int32 nodeId, const Ark_ItemDragInfo event)
    {
        checkEvent = {
            .nodeId = nodeId,
            .dragInfo = Converter::Convert<ItemDragInfo>(event),
        };
    };

    modifier_->setOnItemDragEnter(node_, &func);

    dragInfo.SetX(234);
    dragInfo.SetY(567);

    EXPECT_FALSE(checkEvent.has_value());
    eventHub->FireOnItemDragEnter(dragInfo);
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->dragInfo.GetX(), 234);
    EXPECT_EQ(checkEvent->dragInfo.GetY(), 567);
}

/*
 * @tc.name: setOnItemDragMoveTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierCallbacksTest, setOnItemDragMoveTest, TestSize.Level1)
{
    Callback_ItemDragInfo_Number_Number_Void func{};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    auto dragInfo = ItemDragInfo();

    struct CheckEvent {
        int32_t nodeId;
        ItemDragInfo dragInfo;
        int32_t itemIndex;
        int32_t insertIndex;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    EventsTracker::gridEventsReceiver.onItemDragMove = [](Ark_Int32 nodeId,
        const Ark_ItemDragInfo event, const Ark_Number itemIndex, const Ark_Number insertIndex)
    {
        checkEvent = {
            .nodeId = nodeId,
            .dragInfo = Converter::Convert<ItemDragInfo>(event),
            .itemIndex = Converter::Convert<int32_t>(itemIndex),
            .insertIndex = Converter::Convert<int32_t>(insertIndex)
        };
    };

    modifier_->setOnItemDragMove(node_, &func);

    dragInfo.SetX(987);
    dragInfo.SetY(654);

    EXPECT_FALSE(checkEvent.has_value());
    eventHub->FireOnItemDragMove(dragInfo, 4, 35);
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->dragInfo.GetX(), 987);
    EXPECT_EQ(checkEvent->dragInfo.GetY(), 654);
    EXPECT_EQ(checkEvent->itemIndex, 4);
    EXPECT_EQ(checkEvent->insertIndex, 35);
}

/*
 * @tc.name: setOnItemDragLeaveTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierCallbacksTest, setOnItemDragLeaveTest, TestSize.Level1)
{
    Callback_ItemDragInfo_Number_Void func{};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    auto dragInfo = ItemDragInfo();

    struct CheckEvent {
        int32_t nodeId;
        ItemDragInfo dragInfo;
        int32_t itemIndex;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    EventsTracker::gridEventsReceiver.onItemDragLeave = [](Ark_Int32 nodeId,
        const Ark_ItemDragInfo event, const Ark_Number itemIndex)
    {
        checkEvent = {
            .nodeId = nodeId,
            .dragInfo = Converter::Convert<ItemDragInfo>(event),
            .itemIndex = Converter::Convert<int32_t>(itemIndex)
        };
    };

    modifier_->setOnItemDragLeave(node_, &func);

    dragInfo.SetX(135);
    dragInfo.SetY(246);

    EXPECT_FALSE(checkEvent.has_value());
    eventHub->FireOnItemDragLeave(dragInfo, 6);
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->dragInfo.GetX(), 135);
    EXPECT_EQ(checkEvent->dragInfo.GetY(), 246);
    EXPECT_EQ(checkEvent->itemIndex, 6);
}

/*
 * @tc.name: setOnItemDropTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierCallbacksTest, setOnItemDropTest, TestSize.Level1)
{
    Callback_ItemDragInfo_Number_Number_Boolean_Void func{};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    auto dragInfo = ItemDragInfo();

    struct CheckEvent {
        int32_t nodeId;
        ItemDragInfo dragInfo;
        int32_t itemIndex;
        int32_t insertIndex;
        bool isSuccess;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    EventsTracker::gridEventsReceiver.onItemDrop = [](Ark_Int32 nodeId, const Ark_ItemDragInfo event,
    const Ark_Number itemIndex, const Ark_Number insertIndex, const Ark_Boolean isSuccess)
    {
        checkEvent = {
            .nodeId = nodeId,
            .dragInfo = Converter::Convert<ItemDragInfo>(event),
            .itemIndex = Converter::Convert<int32_t>(itemIndex),
            .insertIndex = Converter::Convert<int32_t>(insertIndex),
            .isSuccess = Converter::Convert<bool>(isSuccess),
        };
    };

    modifier_->setOnItemDrop(node_, &func);

    dragInfo.SetX(975);
    dragInfo.SetY(864);

    EXPECT_FALSE(checkEvent.has_value());
    eventHub->FireOnItemDrop(dragInfo, 81, 99, true);
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->dragInfo.GetX(), 975);
    EXPECT_EQ(checkEvent->dragInfo.GetY(), 864);
    EXPECT_EQ(checkEvent->itemIndex, 81);
    EXPECT_EQ(checkEvent->insertIndex, 99);
    EXPECT_TRUE(checkEvent->isSuccess);
}

/*
 * @tc.name: setOnScrollTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierCallbacksTest, setOnScrollTest, TestSize.Level1)
{
    Callback_Number_ScrollState_Void func{};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();

    struct CheckEvent {
        int32_t nodeId;
        Dimension scrollOffset;
        std::optional<ScrollState> scrollState;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    EventsTracker::gridEventsReceiver.onScroll = [](
        Ark_Int32 nodeId, const Ark_Number scrollOffset, const Ark_ScrollState scrollState)
    {
        checkEvent = {
            .nodeId = nodeId,
            .scrollOffset = Converter::Convert<Dimension>(scrollOffset),
            .scrollState = Converter::OptConvert<ScrollState>(scrollState)
        };
    };

    auto onScroll = eventHub->GetOnScroll();
    EXPECT_EQ(onScroll, nullptr);
    modifier_->setOnScroll(node_, &func);
    onScroll = eventHub->GetOnScroll();
    EXPECT_NE(onScroll, nullptr);

    EXPECT_FALSE(checkEvent.has_value());
    onScroll(CalcDimension(55), ScrollState::FLING);
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->scrollOffset.Value(), 55);
    EXPECT_EQ(checkEvent->scrollOffset.Unit(), DimensionUnit::VP);
    EXPECT_TRUE(checkEvent->scrollState.has_value());
    EXPECT_EQ(checkEvent->scrollState.value(), ScrollState::FLING);
}

/*
 * @tc.name: setOnReachStartTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierCallbacksTest, setOnReachStartTest, TestSize.Level1)
{
    Callback_Void func{};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();

    struct CheckEvent {
        int32_t nodeId;
        bool result;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    EventsTracker::gridEventsReceiver.onReachStart = [](Ark_Int32 nodeId)
    {
        checkEvent = {
            .nodeId = nodeId,
            .result = true,
        };
    };

    auto onReachStart = eventHub->GetOnReachStart();
    EXPECT_EQ(onReachStart, nullptr);
    modifier_->setOnReachStart(node_, &func);
    onReachStart = eventHub->GetOnReachStart();
    EXPECT_NE(onReachStart, nullptr);

    EXPECT_FALSE(checkEvent.has_value());
    onReachStart();
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_TRUE(checkEvent->result);
}

/*
 * @tc.name: setOnReachEndTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierCallbacksTest, setOnReachEndTest, TestSize.Level1)
{
    Callback_Void func{};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();

    struct CheckEvent {
        int32_t nodeId;
        bool result;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    EventsTracker::gridEventsReceiver.onReachEnd = [](Ark_Int32 nodeId)
    {
        checkEvent = {
            .nodeId = nodeId,
            .result = true,
        };
    };

    auto onReachEnd = eventHub->GetOnReachEnd();
    EXPECT_EQ(onReachEnd, nullptr);
    modifier_->setOnReachEnd(node_, &func);
    onReachEnd = eventHub->GetOnReachEnd();
    EXPECT_NE(onReachEnd, nullptr);

    EXPECT_FALSE(checkEvent.has_value());
    onReachEnd();
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_TRUE(checkEvent->result);
}

/*
 * @tc.name: setOnScrollStartTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierCallbacksTest, setOnScrollStartTest, TestSize.Level1)
{
    Callback_Void func{};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();

    struct CheckEvent {
        int32_t nodeId;
        bool result;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    EventsTracker::gridEventsReceiver.onScrollStart = [](Ark_Int32 nodeId)
    {
        checkEvent = {
            .nodeId = nodeId,
            .result = true,
        };
    };

    auto onScrollStart = eventHub->GetOnScrollStart();
    EXPECT_EQ(onScrollStart, nullptr);
    modifier_->setOnScrollStart(node_, &func);
    onScrollStart = eventHub->GetOnScrollStart();
    EXPECT_NE(onScrollStart, nullptr);

    EXPECT_FALSE(checkEvent.has_value());
    onScrollStart();
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_TRUE(checkEvent->result);
}

/*
 * @tc.name: setOnScrollStopTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierCallbacksTest, setOnScrollStopTest, TestSize.Level1)
{
    Callback_Void func{};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();

    struct CheckEvent {
        int32_t nodeId;
        bool result;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    EventsTracker::gridEventsReceiver.onScrollStop = [](Ark_Int32 nodeId)
    {
        checkEvent = {
            .nodeId = nodeId,
            .result = true,
        };
    };

    auto onScrollStop = eventHub->GetOnScrollStop();
    EXPECT_EQ(onScrollStop, nullptr);
    modifier_->setOnScrollStop(node_, &func);
    onScrollStop = eventHub->GetOnScrollStop();
    EXPECT_NE(onScrollStop, nullptr);

    EXPECT_FALSE(checkEvent.has_value());
    onScrollStop();
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_TRUE(checkEvent->result);
}

/*
 * @tc.name: DISABLED_setOnScrollFrameBeginTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierCallbacksTest, DISABLED_setOnScrollFrameBeginTest, TestSize.Level1)
{
    // test is disabled because onScrollFrameBegin should return value
    Callback_Number_ScrollState_Literal_Number_offsetRemain func{};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();

    struct CheckEvent {
        int32_t nodeId;
        Dimension offset;
        std::optional<ScrollState> state;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    EventsTracker::gridEventsReceiver.onScrollFrameBegin = [](
        Ark_Int32 nodeId, const Ark_Number offset, const Ark_ScrollState state)
    {
        checkEvent = {
            .nodeId = nodeId,
            .offset = Converter::Convert<Dimension>(offset),
            .state = Converter::OptConvert<ScrollState>(state)
        };
    };

    auto onScrollFrameBegin = eventHub->GetOnScrollFrameBegin();
    EXPECT_EQ(onScrollFrameBegin, nullptr);
    modifier_->setOnScrollFrameBegin(node_, &func);
    onScrollFrameBegin = eventHub->GetOnScrollFrameBegin();
    EXPECT_NE(onScrollFrameBegin, nullptr);

    EXPECT_FALSE(checkEvent.has_value());
    onScrollFrameBegin(CalcDimension(43), ScrollState::SCROLL);
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->offset.Value(), 43);
    EXPECT_EQ(checkEvent->offset.Unit(), DimensionUnit::VP);
    EXPECT_TRUE(checkEvent->state.has_value());
    EXPECT_EQ(checkEvent->state.value(), ScrollState::SCROLL);
}
} // namespace OHOS::Ace::NG
