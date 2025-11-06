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

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"

#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/blank/blank_model_ng.h"
#include "core/components_ng/pattern/list/list_item_event_hub.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_v2/list/list_properties.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "generated/type_helpers.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
static constexpr int TEST_RESOURCE_ID_1 = 1001;
static constexpr int TEST_RESOURCE_ID_2 = 1002;
static constexpr int32_t NODE_ID_1 = 101;
static constexpr int32_t NODE_ID_2 = 102;
struct CheckEvent {
    int32_t resourceId;
    Ark_NativePointer parentNode;
};
static std::optional<CheckEvent> checkEvent_1 = std::nullopt;
static std::optional<RefPtr<UINode>> uiNode_1 = std::nullopt;
static std::optional<CheckEvent> checkEvent_2 = std::nullopt;
static std::optional<RefPtr<UINode>> uiNode_2 = std::nullopt;

class ListItemModifierTest : public ModifierTestBase<GENERATED_ArkUIListItemModifier,
    &GENERATED_ArkUINodeModifiers::getListItemModifier, GENERATED_ARKUI_LIST_ITEM> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
    }

    CustomNodeBuilder getBuilderCb(bool start)
    {
        auto checkCallback = [](
            const Ark_Int32 resourceId,
            const Ark_NativePointer parentNode,
            const Callback_Pointer_Void continuation) {
            if (TEST_RESOURCE_ID_1 == resourceId) {
                checkEvent_1 = {
                    .resourceId = resourceId,
                    .parentNode = parentNode
                };
                if (uiNode_1) {
                    CallbackHelper(continuation).InvokeSync(AceType::RawPtr(uiNode_1.value()));
                }
            }

            if (TEST_RESOURCE_ID_2 == resourceId) {
                checkEvent_2 = {
                    .resourceId = resourceId,
                    .parentNode = parentNode
                };
                if (uiNode_2) {
                    CallbackHelper(continuation).InvokeSync(AceType::RawPtr(uiNode_2.value()));
                }
            }
        };
        CustomNodeBuilder customBuilder = Converter::ArkValue<CustomNodeBuilder>(checkCallback,
            start ? TEST_RESOURCE_ID_1 : TEST_RESOURCE_ID_2);
        return customBuilder;
    }
};

/*
 * @tc.name: Construct
 * @tc.desc: Check the functionality of ListItemModifier.Construct
 * @tc.type: FUNC
 */
HWTEST_F(ListItemModifierTest, ConstructTest, TestSize.Level1)
{
    const auto id = GetId();
    auto node = modifier_->construct(id, 0);
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    ASSERT_TRUE(node);
    EXPECT_EQ(frameNode->GetId(), id);
    EXPECT_EQ(frameNode->GetTag(), V2::LIST_ITEM_ETS_TAG);
    auto pattern = frameNode->GetPattern<ListItemPattern>();
}

/*
 * @tc.name: setListItemOptionsTest
 * @tc.desc: Check the functionality of ListItemModifier.setListItemOptions
 * @tc.type: FUNC
 */
HWTEST_F(ListItemModifierTest, DISABLED_setListItemOptionsTest, TestSize.Level1)
{
    auto style = GetAttrValue<std::string>(node_, "itemStyle");
    EXPECT_EQ(style, "ListItemStyle.NONE");

    Ark_ListItemOptions listItemOptions = {.style = Converter::ArkValue<Opt_ListItemStyle>(V2::ListItemStyle::CARD)};
    Opt_ListItemOptions arg = Converter::ArkValue<Opt_ListItemOptions>(listItemOptions);
    modifier_->setListItemOptions(node_, &arg);
    style = GetAttrValue<std::string>(node_, "itemStyle");
    EXPECT_EQ(style, "ListItemStyle.CARD");

    arg = Converter::ArkValue<Opt_ListItemOptions>(Ark_Empty());
    modifier_->setListItemOptions(node_, &arg);
    style = GetAttrValue<std::string>(node_, "itemStyle");
    EXPECT_EQ(style, "ListItemStyle.CARD");

    listItemOptions = {.style = Converter::ArkValue<Opt_ListItemStyle>(Ark_Empty())};
    arg = Converter::ArkValue<Opt_ListItemOptions>(listItemOptions);
    modifier_->setListItemOptions(node_, &arg);
    style = GetAttrValue<std::string>(node_, "itemStyle");
    EXPECT_EQ(style, "ListItemStyle.NONE");
}

/*
 * @tc.name: setSelectableTest
 * @tc.desc: Check the functionality of ListItemModifier.setSelectable
 * @tc.type: FUNC
 */
HWTEST_F(ListItemModifierTest, setSelectableTest, TestSize.Level1)
{
    bool selectable = GetAttrValue<bool>(node_, "selectable");
    EXPECT_TRUE(selectable);
    auto optValue = Converter::ArkValue<Opt_Boolean>(false);
    modifier_->setSelectable(node_, &optValue);
    selectable = GetAttrValue<bool>(node_, "selectable");
    EXPECT_FALSE(selectable);
}

/*
 * @tc.name: setSelectableTest
 * @tc.desc: Check the functionality of ListItemModifier.setSelected
 * @tc.type: FUNC
 */
HWTEST_F(ListItemModifierTest, setSelectedTest, TestSize.Level1)
{
    bool selected = GetAttrValue<bool>(node_, "selected");
    EXPECT_FALSE(selected);
    auto optValue = Converter::ArkUnion<Opt_Union_Boolean_Bindable, Ark_Boolean>(true);
    modifier_->setSelected(node_, &optValue);
    selected = GetAttrValue<bool>(node_, "selected");
    EXPECT_TRUE(selected);
}

/*
 * @tc.name: setOnSelectTest
 * @tc.desc: Check the functionality of ListItemModifier.setOnSelect
 * @tc.type: FUNC
 */
HWTEST_F(ListItemModifierTest, setOnSelectTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<ListItemEventHub>();

    struct CheckEvent {
        int32_t nodeId;
        bool isSelected;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    void (*checkCallback)(const Ark_Int32, const Ark_Boolean) =
        [](const Ark_Int32 resourceId, const Ark_Boolean param) {
            checkEvent = {
                .nodeId = resourceId,
                .isSelected = Converter::Convert<bool>(param)
            };
        };
    const int32_t contextId = 123;
    auto func = Converter::ArkValue<Callback_Boolean_Void>(checkCallback, contextId);
    auto optFunc = Converter::ArkValue<Opt_Callback_Boolean_Void>(func);
    modifier_->setOnSelect(node_, &optFunc);
    // check true value
    EXPECT_EQ(checkEvent.has_value(), false);
    eventHub->FireSelectChangeEvent(true);
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    EXPECT_EQ(checkEvent->isSelected, true);
    // check false value
    eventHub->FireSelectChangeEvent(false);
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    EXPECT_EQ(checkEvent->isSelected, false);
}

/**
 * @tc.name: setSwipeActionEdgeEffectTest
 * @tc.desc: Check the functionality of ListItemModifier.setSwipeAction
 * @tc.type: FUNC
 */
HWTEST_F(ListItemModifierTest, setSwipeActionEdgeEffectTest, TestSize.Level1)
{
    auto fullJson = GetJsonValue(node_);
    auto swipeAction = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "swipeAction");
    auto edgeEffect = GetAttrValue<std::string>(swipeAction, "edgeEffect");
    EXPECT_EQ(edgeEffect, "");

    Ark_SwipeActionOptions  options = {
        .start = Converter::ArkValue<Opt_Union_CustomBuilder_SwipeActionItem>(Ark_Empty()),
        .end = Converter::ArkValue<Opt_Union_CustomBuilder_SwipeActionItem>(Ark_Empty()),
        .onOffsetChange = Converter::ArkValue<Opt_Callback_F64_Void>(Ark_Empty()),
        .edgeEffect = Converter::ArkValue<Opt_SwipeEdgeEffect>(V2::SwipeEdgeEffect::None)
    };
    auto optOptions = Converter::ArkValue<Opt_SwipeActionOptions>(options);
    modifier_->setSwipeAction(node_, &optOptions);
    fullJson = GetJsonValue(node_);
    swipeAction = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "swipeAction");
    edgeEffect = GetAttrValue<std::string>(swipeAction, "edgeEffect");
    EXPECT_EQ(edgeEffect, "SwipeEdgeEffect.None");

    options = {
        .start = Converter::ArkValue<Opt_Union_CustomBuilder_SwipeActionItem>(Ark_Empty()),
        .end = Converter::ArkValue<Opt_Union_CustomBuilder_SwipeActionItem>(Ark_Empty()),
        .edgeEffect = Converter::ArkValue<Opt_SwipeEdgeEffect>(V2::SwipeEdgeEffect::Spring)
    };
    optOptions = Converter::ArkValue<Opt_SwipeActionOptions>(options);
    modifier_->setSwipeAction(node_, &optOptions);
    fullJson = GetJsonValue(node_);
    swipeAction = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "swipeAction");
    edgeEffect = GetAttrValue<std::string>(swipeAction, "edgeEffect");
    EXPECT_EQ(edgeEffect, "SwipeEdgeEffect.Spring");

    options = {
        .start = Converter::ArkValue<Opt_Union_CustomBuilder_SwipeActionItem>(Ark_Empty()),
        .end = Converter::ArkValue<Opt_Union_CustomBuilder_SwipeActionItem>(Ark_Empty()),
        .edgeEffect = Converter::ArkValue<Opt_SwipeEdgeEffect>(static_cast<V2::SwipeEdgeEffect>(-10))
    };
    optOptions = Converter::ArkValue<Opt_SwipeActionOptions>(options);
    modifier_->setSwipeAction(node_, &optOptions);
    fullJson = GetJsonValue(node_);
    swipeAction = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "swipeAction");
    edgeEffect = GetAttrValue<std::string>(swipeAction, "edgeEffect");
    EXPECT_EQ(edgeEffect, "");
}

/**
 * @tc.name: setSwipeActionActionsTest
 * @tc.desc: Check the functionality of ListItemModifier.setSwipeAction
 * @tc.type: FUNC
 */
HWTEST_F(ListItemModifierTest, setSwipeActionOffsetChangeTest, TestSize.Level1)
{
    const int32_t offsetArg = 5;

    struct CheckEvent {
        int32_t resourceId;
        int32_t offset;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    void (*checkCallback)(const Ark_Int32, const Ark_Float64) =
        [](const Ark_Int32 resourceId, const Ark_Float64 offset) {
            checkEvent = {
                .resourceId = resourceId,
                .offset = Converter::Convert<int32_t>(offset)
            };
        };

    Ark_SwipeActionOptions arkOptions = {
        .onOffsetChange = Converter::ArkValue<Opt_Callback_F64_Void>(
            Converter::ArkValue<Callback_F64_Void>(checkCallback, TEST_RESOURCE_ID_1))
    };
    auto optOptions = Converter::ArkValue<Opt_SwipeActionOptions>(arkOptions);
    modifier_->setSwipeAction(node_, &optOptions);

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<ListItemEventHub>();
    ASSERT_NE(eventHub, nullptr);

    eventHub->FireOffsetChangeEvent(offsetArg);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent.value().resourceId, TEST_RESOURCE_ID_1);
    EXPECT_EQ(checkEvent.value().offset, offsetArg);
}

/**
 * @tc.name: setSwipeActionActionsTest
 * @tc.desc: Check the functionality of ListItemModifier.setSwipeAction
 * @tc.type: FUNC
 */
HWTEST_F(ListItemModifierTest, setSwipeActionCustomBuilderTest, TestSize.Level1)
{
    uiNode_1 = BlankModelNG::CreateFrameNode(NODE_ID_1);
    auto customBuilderStart = getBuilderCb(true);
    Ark_Union_CustomBuilder_SwipeActionItem arkUnionStart;
    TypeHelper::WriteToUnion<CustomNodeBuilder>(arkUnionStart) = customBuilderStart;

    uiNode_2 = BlankModelNG::CreateFrameNode(NODE_ID_2);
    auto customBuilderEnd = getBuilderCb(false);
    Ark_Union_CustomBuilder_SwipeActionItem arkUnionEnd;
    TypeHelper::WriteToUnion<CustomNodeBuilder>(arkUnionEnd) = customBuilderEnd;

    Ark_SwipeActionOptions arkOptions = {
        .start = Converter::ArkValue<Opt_Union_CustomBuilder_SwipeActionItem>(arkUnionStart),
        .end = Converter::ArkValue<Opt_Union_CustomBuilder_SwipeActionItem>(arkUnionEnd)
    };
    auto optOptions = Converter::ArkValue<Opt_SwipeActionOptions>(arkOptions);
    modifier_->setSwipeAction(node_, &optOptions);

    ASSERT_EQ(checkEvent_1.has_value(), true);
    EXPECT_EQ(checkEvent_1->resourceId, TEST_RESOURCE_ID_1);
    EXPECT_EQ(reinterpret_cast<FrameNode*>(checkEvent_1->parentNode), reinterpret_cast<FrameNode*>(node_));

    ASSERT_EQ(checkEvent_2.has_value(), true);
    EXPECT_EQ(checkEvent_2->resourceId, TEST_RESOURCE_ID_2);
    EXPECT_EQ(reinterpret_cast<FrameNode*>(checkEvent_2->parentNode), reinterpret_cast<FrameNode*>(node_));
    uiNode_1 = std::nullopt;
    uiNode_2 = std::nullopt;
}

/**
 * @tc.name: setSwipeActionActionItemCustomBuilderTest
 * @tc.desc: Check the functionality of ListItemModifier.setSwipeAction
 * @tc.type: FUNC
 */
HWTEST_F(ListItemModifierTest, setSwipeActionActionItemCustomBuilderTest, TestSize.Level1)
{
    uiNode_1 = BlankModelNG::CreateFrameNode(NODE_ID_1);
    auto customBuilderStart = getBuilderCb(true);
    Ark_SwipeActionItem itemStart = {
        .builder = Converter::ArkValue<Opt_CustomNodeBuilder>(customBuilderStart)
    };
    Ark_Union_CustomBuilder_SwipeActionItem arkUnionStart;
    TypeHelper::WriteToUnion<Ark_SwipeActionItem>(arkUnionStart) = itemStart;

    uiNode_2 = BlankModelNG::CreateFrameNode(NODE_ID_2);
    auto customBuilderEnd = getBuilderCb(false);
    Ark_SwipeActionItem itemEnd = {
        .builder = Converter::ArkValue<Opt_CustomNodeBuilder>(customBuilderEnd)
    };
    Ark_Union_CustomBuilder_SwipeActionItem arkUnionEnd;
    TypeHelper::WriteToUnion<Ark_SwipeActionItem>(arkUnionEnd) = itemEnd;

    Ark_SwipeActionOptions arkOptions = {
        .start = Converter::ArkValue<Opt_Union_CustomBuilder_SwipeActionItem>(arkUnionStart),
        .end = Converter::ArkValue<Opt_Union_CustomBuilder_SwipeActionItem>(arkUnionEnd)
    };
    auto optOptions = Converter::ArkValue<Opt_SwipeActionOptions>(arkOptions);
    modifier_->setSwipeAction(node_, &optOptions);

    ASSERT_EQ(checkEvent_1.has_value(), true);
    EXPECT_EQ(checkEvent_1->resourceId, TEST_RESOURCE_ID_1);
    EXPECT_EQ(reinterpret_cast<FrameNode*>(checkEvent_1->parentNode), reinterpret_cast<FrameNode*>(node_));

    ASSERT_EQ(checkEvent_2.has_value(), true);
    EXPECT_EQ(checkEvent_2->resourceId, TEST_RESOURCE_ID_2);
    EXPECT_EQ(reinterpret_cast<FrameNode*>(checkEvent_2->parentNode), reinterpret_cast<FrameNode*>(node_));
    uiNode_1 = std::nullopt;
    uiNode_2 = std::nullopt;
}

/**
 * @tc.name: setSwipeActionActionItemOnActionCallbackTest
 * @tc.desc: Check the functionality of ListItemModifier.setSwipeAction
 * @tc.type: FUNC
 */
HWTEST_F(ListItemModifierTest, setSwipeActionActionItemOnActionCallbackTest, TestSize.Level1)
{
    static std::optional<CheckEvent> checkEventStart = std::nullopt;
    void (*checkCallbackStart)(const Ark_Int32) =
        [](const Ark_Int32 resourceId) {
            checkEventStart = {
                .resourceId = resourceId,
            };
        };

    Ark_SwipeActionItem itemStart = {
        .builder = Converter::ArkValue<Opt_CustomNodeBuilder>(Ark_Empty()),
        .onAction = Converter::ArkValue<Opt_Callback_Void>(
            Converter::ArkValue<Callback_Void>(checkCallbackStart, TEST_RESOURCE_ID_1))
    };
    Ark_Union_CustomBuilder_SwipeActionItem arkUnionStart;
    TypeHelper::WriteToUnion<Ark_SwipeActionItem>(arkUnionStart) = itemStart;

    static std::optional<CheckEvent> checkEventEnd = std::nullopt;
    void (*checkCallbackEnd)(const Ark_Int32) =
        [](const Ark_Int32 resourceId) {
            checkEventEnd = {
                .resourceId = resourceId,
            };
        };

    Ark_SwipeActionItem itemEnd = {
        .builder = Converter::ArkValue<Opt_CustomNodeBuilder>(Ark_Empty()),
        .onAction = Converter::ArkValue<Opt_Callback_Void>(
            Converter::ArkValue<Callback_Void>(checkCallbackEnd, TEST_RESOURCE_ID_2))
    };
    Ark_Union_CustomBuilder_SwipeActionItem arkUnionEnd;
    TypeHelper::WriteToUnion<Ark_SwipeActionItem>(arkUnionEnd) = itemEnd;

    Ark_SwipeActionOptions arkOptions = {
        .start = Converter::ArkValue<Opt_Union_CustomBuilder_SwipeActionItem>(arkUnionStart),
        .end = Converter::ArkValue<Opt_Union_CustomBuilder_SwipeActionItem>(arkUnionEnd)
    };
    auto optOptions = Converter::ArkValue<Opt_SwipeActionOptions>(arkOptions);
    modifier_->setSwipeAction(node_, &optOptions);

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<ListItemEventHub>();
    ASSERT_NE(eventHub, nullptr);

    auto onDeleteStart = eventHub->GetStartOnDelete();
    ASSERT_NE(onDeleteStart, nullptr);
    onDeleteStart();
    ASSERT_TRUE(checkEventStart.has_value());
    EXPECT_EQ(checkEventStart.value().resourceId, TEST_RESOURCE_ID_1);

    auto onDeleteEnd = eventHub->GetEndOnDelete();
    ASSERT_NE(onDeleteEnd, nullptr);
    onDeleteEnd();
    ASSERT_TRUE(checkEventEnd.has_value());
    EXPECT_EQ(checkEventEnd.value().resourceId, TEST_RESOURCE_ID_2);
}

/**
 * @tc.name: setSwipeActionActionItemOnEnterActionAreaCallbackTest
 * @tc.desc: Check the functionality of ListItemModifier.setSwipeAction
 * @tc.type: FUNC
 */
HWTEST_F(ListItemModifierTest, setSwipeActionActionItemOnEnterActionAreaCallbackTest, TestSize.Level1)
{
    static std::optional<CheckEvent> checkEventStart = std::nullopt;
    void (*checkCallbackStart)(const Ark_Int32) =
        [](const Ark_Int32 resourceId) {
            checkEventStart = {
                .resourceId = resourceId,
            };
        };

    Ark_SwipeActionItem itemStart = {
        .builder = Converter::ArkValue<Opt_CustomNodeBuilder>(Ark_Empty()),
        .onEnterActionArea = Converter::ArkValue<Opt_Callback_Void>(
            Converter::ArkValue<Callback_Void>(checkCallbackStart, TEST_RESOURCE_ID_1))
    };
    Ark_Union_CustomBuilder_SwipeActionItem arkUnionStart;
    TypeHelper::WriteToUnion<Ark_SwipeActionItem>(arkUnionStart) = itemStart;

    static std::optional<CheckEvent> checkEventEnd = std::nullopt;
    void (*checkCallbackEnd)(const Ark_Int32) =
        [](const Ark_Int32 resourceId) {
            checkEventEnd = {
                .resourceId = resourceId,
            };
        };

    Ark_SwipeActionItem itemEnd = {
        .builder = Converter::ArkValue<Opt_CustomNodeBuilder>(Ark_Empty()),
        .onEnterActionArea = Converter::ArkValue<Opt_Callback_Void>(
            Converter::ArkValue<Callback_Void>(checkCallbackEnd, TEST_RESOURCE_ID_2))
    };
    Ark_Union_CustomBuilder_SwipeActionItem arkUnionEnd;
    TypeHelper::WriteToUnion<Ark_SwipeActionItem>(arkUnionEnd) = itemEnd;

    Ark_SwipeActionOptions arkOptions = {
        .start = Converter::ArkValue<Opt_Union_CustomBuilder_SwipeActionItem>(arkUnionStart),
        .end = Converter::ArkValue<Opt_Union_CustomBuilder_SwipeActionItem>(arkUnionEnd)
    };
    auto optOptions = Converter::ArkValue<Opt_SwipeActionOptions>(arkOptions);
    modifier_->setSwipeAction(node_, &optOptions);

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<ListItemEventHub>();
    ASSERT_NE(eventHub, nullptr);

    auto onEnterDeleteStart = eventHub->GetOnEnterStartDeleteArea();
    ASSERT_NE(onEnterDeleteStart, nullptr);
    onEnterDeleteStart();
    ASSERT_TRUE(checkEventStart.has_value());
    EXPECT_EQ(checkEventStart.value().resourceId, TEST_RESOURCE_ID_1);

    auto onEnterDeleteEnd = eventHub->GetOnEnterEndDeleteArea();
    ASSERT_NE(onEnterDeleteEnd, nullptr);
    onEnterDeleteEnd();
    ASSERT_TRUE(checkEventEnd.has_value());
    EXPECT_EQ(checkEventEnd.value().resourceId, TEST_RESOURCE_ID_2);
}

/**
 * @tc.name: setSwipeActionActionItemOnExitActionAreaCallbackTest
 * @tc.desc: Check the functionality of ListItemModifier.setSwipeAction
 * @tc.type: FUNC
 */
HWTEST_F(ListItemModifierTest, setSwipeActionActionItemOnExitActionAreaCallbackTest, TestSize.Level1)
{
    static std::optional<CheckEvent> checkEventStart = std::nullopt;
    void (*checkCallbackStart)(const Ark_Int32) =
        [](const Ark_Int32 resourceId) {
            checkEventStart = {
                .resourceId = resourceId,
            };
        };

    Ark_SwipeActionItem itemStart = {
        .builder = Converter::ArkValue<Opt_CustomNodeBuilder>(Ark_Empty()),
        .onExitActionArea = Converter::ArkValue<Opt_Callback_Void>(
            Converter::ArkValue<Callback_Void>(checkCallbackStart, TEST_RESOURCE_ID_1))
    };
    Ark_Union_CustomBuilder_SwipeActionItem arkUnionStart;
    TypeHelper::WriteToUnion<Ark_SwipeActionItem>(arkUnionStart) = itemStart;

    static std::optional<CheckEvent> checkEventEnd = std::nullopt;
    void (*checkCallbackEnd)(const Ark_Int32) =
        [](const Ark_Int32 resourceId) {
            checkEventEnd = {
                .resourceId = resourceId,
            };
        };

    Ark_SwipeActionItem itemEnd = {
        .builder = Converter::ArkValue<Opt_CustomNodeBuilder>(Ark_Empty()),
        .onExitActionArea = Converter::ArkValue<Opt_Callback_Void>(
            Converter::ArkValue<Callback_Void>(checkCallbackEnd, TEST_RESOURCE_ID_2))
    };
    Ark_Union_CustomBuilder_SwipeActionItem arkUnionEnd;
    TypeHelper::WriteToUnion<Ark_SwipeActionItem>(arkUnionEnd) = itemEnd;

    Ark_SwipeActionOptions arkOptions = {
        .start = Converter::ArkValue<Opt_Union_CustomBuilder_SwipeActionItem>(arkUnionStart),
        .end = Converter::ArkValue<Opt_Union_CustomBuilder_SwipeActionItem>(arkUnionEnd)
    };
    auto optOptions = Converter::ArkValue<Opt_SwipeActionOptions>(arkOptions);
    modifier_->setSwipeAction(node_, &optOptions);

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<ListItemEventHub>();
    ASSERT_NE(eventHub, nullptr);

    auto onExitDeleteStart = eventHub->GetOnExitStartDeleteArea();
    ASSERT_NE(onExitDeleteStart, nullptr);
    onExitDeleteStart();
    ASSERT_TRUE(checkEventStart.has_value());
    EXPECT_EQ(checkEventStart.value().resourceId, TEST_RESOURCE_ID_1);

    auto onExitDeleteEnd = eventHub->GetOnExitEndDeleteArea();
    ASSERT_NE(onExitDeleteEnd, nullptr);
    onExitDeleteEnd();
    ASSERT_TRUE(checkEventEnd.has_value());
    EXPECT_EQ(checkEventEnd.value().resourceId, TEST_RESOURCE_ID_2);
}

/**
 * @tc.name: setSwipeActionActionItemOnStateChangeCallbackTest
 * @tc.desc: Check the functionality of ListItemModifier.setSwipeAction
 * @tc.type: FUNC
 */
HWTEST_F(ListItemModifierTest, setSwipeActionActionItemOnStateChangeCallbackTest, TestSize.Level1)
{
    struct CheckEvent { int32_t resourceId; std::optional<SwipeActionState> state; };
    static std::optional<CheckEvent> checkEventStart = std::nullopt;
    void (*checkCallbackStart)(const Ark_Int32, const Ark_SwipeActionState) =
        [](const Ark_Int32 resourceId, const Ark_SwipeActionState state) {
            checkEventStart = { .resourceId = resourceId,
                .state = Converter::OptConvert<SwipeActionState>(state) };
        };

    Ark_SwipeActionItem itemStart = {
        .builder = Converter::ArkValue<Opt_CustomNodeBuilder>(Ark_Empty()),
        .onStateChange = Converter::ArkValue<Opt_Callback_SwipeActionState_Void>(
            Converter::ArkValue<Callback_SwipeActionState_Void>(checkCallbackStart, TEST_RESOURCE_ID_1))
    };
    Ark_Union_CustomBuilder_SwipeActionItem arkUnionStart;
    TypeHelper::WriteToUnion<Ark_SwipeActionItem>(arkUnionStart) = itemStart;

    static std::optional<CheckEvent> checkEventEnd = std::nullopt;
    void (*checkCallbackEnd)(const Ark_Int32, const Ark_SwipeActionState) =
        [](const Ark_Int32 resourceId, const Ark_SwipeActionState state) {
            checkEventEnd = { .resourceId = resourceId,
                .state = Converter::OptConvert<SwipeActionState>(state) };
        };

    Ark_SwipeActionItem itemEnd = {
        .builder = Converter::ArkValue<Opt_CustomNodeBuilder>(Ark_Empty()),
        .onStateChange = Converter::ArkValue<Opt_Callback_SwipeActionState_Void>(
            Converter::ArkValue<Callback_SwipeActionState_Void>(checkCallbackEnd, TEST_RESOURCE_ID_2))
    };
    Ark_Union_CustomBuilder_SwipeActionItem arkUnionEnd;
    TypeHelper::WriteToUnion<Ark_SwipeActionItem>(arkUnionEnd) = itemEnd;

    Ark_SwipeActionOptions arkOptions = {
        .start = Converter::ArkValue<Opt_Union_CustomBuilder_SwipeActionItem>(arkUnionStart),
        .end = Converter::ArkValue<Opt_Union_CustomBuilder_SwipeActionItem>(arkUnionEnd)
    };
    auto optOptions = Converter::ArkValue<Opt_SwipeActionOptions>(arkOptions);
    modifier_->setSwipeAction(node_, &optOptions);

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<ListItemEventHub>();
    ASSERT_NE(eventHub, nullptr);

    eventHub->FireStateChangeEvent(SwipeActionState::COLLAPSED, true);
    ASSERT_TRUE(checkEventStart.has_value());
    EXPECT_EQ(checkEventStart.value().resourceId, TEST_RESOURCE_ID_1);
    ASSERT_TRUE(checkEventStart.value().state.has_value());
    EXPECT_EQ(checkEventStart.value().state.value(), SwipeActionState::COLLAPSED);

    eventHub->FireStateChangeEvent(SwipeActionState::EXPANDED, false);
    ASSERT_TRUE(checkEventEnd.has_value());
    EXPECT_EQ(checkEventEnd.value().resourceId, TEST_RESOURCE_ID_2);
    ASSERT_TRUE(checkEventEnd.value().state.has_value());
    EXPECT_EQ(checkEventEnd.value().state.value(), SwipeActionState::EXPANDED);
}

/**
 * @tc.name: setSwipeActionActionItemActionAreaDistanceTest
 * @tc.desc: Check the functionality of ListItemModifier.setSwipeAction
 * @tc.type: FUNC
 */
HWTEST_F(ListItemModifierTest, setSwipeActionActionItemActionAreaDistanceTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    auto startDeleteAreaDistance = GetAttrValue<std::string>(node_, "startDeleteAreaDistance");
    auto endDeleteAreaDistance = GetAttrValue<std::string>(node_, "endDeleteAreaDistance");
    EXPECT_EQ(startDeleteAreaDistance, "0.00vp");
    EXPECT_EQ(endDeleteAreaDistance, "0.00vp");

    Ark_SwipeActionItem itemStart = {
        .builder = Converter::ArkValue<Opt_CustomNodeBuilder>(Ark_Empty()),
        .actionAreaDistance = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(55.5f)),
    };
    Ark_Union_CustomBuilder_SwipeActionItem arkUnionStart;
    TypeHelper::WriteToUnion<Ark_SwipeActionItem>(arkUnionStart) = itemStart;

    Ark_SwipeActionItem itemEnd = {
        .builder = Converter::ArkValue<Opt_CustomNodeBuilder>(Ark_Empty()),
        .actionAreaDistance = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(77.7f)),
    };
    Ark_Union_CustomBuilder_SwipeActionItem arkUnionEnd;
    TypeHelper::WriteToUnion<Ark_SwipeActionItem>(arkUnionEnd) = itemEnd;

    Ark_SwipeActionOptions arkOptions = {
        .start = Converter::ArkValue<Opt_Union_CustomBuilder_SwipeActionItem>(arkUnionStart),
        .end = Converter::ArkValue<Opt_Union_CustomBuilder_SwipeActionItem>(arkUnionEnd)
    };
    auto optOptions = Converter::ArkValue<Opt_SwipeActionOptions>(arkOptions);
    modifier_->setSwipeAction(node_, &optOptions);

    startDeleteAreaDistance = GetAttrValue<std::string>(node_, "startDeleteAreaDistance");
    endDeleteAreaDistance = GetAttrValue<std::string>(node_, "endDeleteAreaDistance");
    EXPECT_EQ(startDeleteAreaDistance, "55.50vp");
    EXPECT_EQ(endDeleteAreaDistance, "77.70vp");
}

/**
 * @tc.name: setSwipeActionActionItemActionAreaDistanceNegativeTest
 * @tc.desc: Check the functionality of ListItemModifier.setSwipeAction
 * @tc.type: FUNC
 */
HWTEST_F(ListItemModifierTest, setSwipeActionActionItemActionAreaDistanceNegativeTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    auto startDeleteAreaDistance = GetAttrValue<std::string>(node_, "startDeleteAreaDistance");
    auto endDeleteAreaDistance = GetAttrValue<std::string>(node_, "endDeleteAreaDistance");
    EXPECT_EQ(startDeleteAreaDistance, "0.00vp");
    EXPECT_EQ(endDeleteAreaDistance, "0.00vp");

    Ark_SwipeActionItem itemStart = {
        .builder = Converter::ArkValue<Opt_CustomNodeBuilder>(Ark_Empty()),
        .actionAreaDistance = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(-55.5f)),
    };
    Ark_Union_CustomBuilder_SwipeActionItem arkUnionStart;
    TypeHelper::WriteToUnion<Ark_SwipeActionItem>(arkUnionStart) = itemStart;

    Ark_SwipeActionItem itemEnd = {
        .builder = Converter::ArkValue<Opt_CustomNodeBuilder>(Ark_Empty()),
        .actionAreaDistance = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(-77.7f)),
    };
    Ark_Union_CustomBuilder_SwipeActionItem arkUnionEnd;
    TypeHelper::WriteToUnion<Ark_SwipeActionItem>(arkUnionEnd) = itemEnd;

    Ark_SwipeActionOptions arkOptions = {
        .start = Converter::ArkValue<Opt_Union_CustomBuilder_SwipeActionItem>(arkUnionStart),
        .end = Converter::ArkValue<Opt_Union_CustomBuilder_SwipeActionItem>(arkUnionEnd)
    };
    auto optOptions = Converter::ArkValue<Opt_SwipeActionOptions>(arkOptions);
    modifier_->setSwipeAction(node_, &optOptions);

    startDeleteAreaDistance = GetAttrValue<std::string>(node_, "startDeleteAreaDistance");
    endDeleteAreaDistance = GetAttrValue<std::string>(node_, "endDeleteAreaDistance");
    EXPECT_EQ(startDeleteAreaDistance, "-55.50vp");
    EXPECT_EQ(endDeleteAreaDistance, "-77.70vp");
}

/**
 * @tc.name: setSwipeActionActionItemActionAreaDistanceOptionalTest
 * @tc.desc: Check the functionality of ListItemModifier.setSwipeAction
 * @tc.type: FUNC
 */
HWTEST_F(ListItemModifierTest, setSwipeActionActionItemActionAreaDistanceOptionalTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    auto startDeleteAreaDistance = GetAttrValue<std::string>(node_, "startDeleteAreaDistance");
    auto endDeleteAreaDistance = GetAttrValue<std::string>(node_, "endDeleteAreaDistance");
    EXPECT_EQ(startDeleteAreaDistance, "0.00vp");
    EXPECT_EQ(endDeleteAreaDistance, "0.00vp");

    Ark_SwipeActionItem itemStart = {
        .builder = Converter::ArkValue<Opt_CustomNodeBuilder>(Ark_Empty()),
        .actionAreaDistance = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(55.5f)),
    };
    Ark_Union_CustomBuilder_SwipeActionItem arkUnionStart;
    TypeHelper::WriteToUnion<Ark_SwipeActionItem>(arkUnionStart) = itemStart;

    Ark_SwipeActionItem itemEnd = {
        .builder = Converter::ArkValue<Opt_CustomNodeBuilder>(Ark_Empty()),
        .actionAreaDistance = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(77.7f)),
    };
    Ark_Union_CustomBuilder_SwipeActionItem arkUnionEnd;
    TypeHelper::WriteToUnion<Ark_SwipeActionItem>(arkUnionEnd) = itemEnd;

    Ark_SwipeActionOptions arkOptions = {
        .start = Converter::ArkValue<Opt_Union_CustomBuilder_SwipeActionItem>(arkUnionStart),
        .end = Converter::ArkValue<Opt_Union_CustomBuilder_SwipeActionItem>(arkUnionEnd)
    };
    auto optOptions = Converter::ArkValue<Opt_SwipeActionOptions>(arkOptions);
    modifier_->setSwipeAction(node_, &optOptions);

    startDeleteAreaDistance = GetAttrValue<std::string>(node_, "startDeleteAreaDistance");
    endDeleteAreaDistance = GetAttrValue<std::string>(node_, "endDeleteAreaDistance");
    EXPECT_EQ(startDeleteAreaDistance, "55.50vp");
    EXPECT_EQ(endDeleteAreaDistance, "77.70vp");

    // optional values
    itemStart = {
        .builder = Converter::ArkValue<Opt_CustomNodeBuilder>(Ark_Empty()),
        .actionAreaDistance = Converter::ArkValue<Opt_Length>(Ark_Empty())
    };
    TypeHelper::WriteToUnion<Ark_SwipeActionItem>(arkUnionStart) = itemStart;

    itemEnd = {
        .builder = Converter::ArkValue<Opt_CustomNodeBuilder>(Ark_Empty()),
        .actionAreaDistance = Converter::ArkValue<Opt_Length>(Ark_Empty())
    };
    TypeHelper::WriteToUnion<Ark_SwipeActionItem>(arkUnionEnd) = itemEnd;

    arkOptions = { .start = Converter::ArkValue<Opt_Union_CustomBuilder_SwipeActionItem>(arkUnionStart),
        .end = Converter::ArkValue<Opt_Union_CustomBuilder_SwipeActionItem>(arkUnionEnd)
    };
    optOptions = Converter::ArkValue<Opt_SwipeActionOptions>(arkOptions);
    modifier_->setSwipeAction(node_, &optOptions);

    startDeleteAreaDistance = GetAttrValue<std::string>(node_, "startDeleteAreaDistance");
    endDeleteAreaDistance = GetAttrValue<std::string>(node_, "endDeleteAreaDistance");
    EXPECT_EQ(startDeleteAreaDistance, "0.00vp");
    EXPECT_EQ(endDeleteAreaDistance, "0.00vp");
}

#ifdef WRONG_OLD_GEN
/*
 * @tc.name: setOnChangeEventSelectedImpl
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ListItemModifierTest, setOnChangeEventSelectedImpl, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<ListItemEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        std::optional<bool> value;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;

    auto checkCallback = [](const Ark_Int32 resourceId, const Opt_Boolean parameter) {
        checkEvent = {
            .nodeId = resourceId,
            .value = Converter::OptConvert<bool>(parameter)
        };
    };

    auto arkCallback = Converter::ArkValue<Callback_Opt_Boolean_Void>(checkCallback, contextId);
    modifier_->set_onChangeEvent_selected(node_, &arkCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    eventHub->FireSelectChangeEvent(true);
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    EXPECT_EQ(checkEvent->value, true);
    eventHub->FireSelectChangeEvent(false);
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    EXPECT_EQ(checkEvent->value, false);
}
#endif
} // namespace OHOS::Ace::NG
