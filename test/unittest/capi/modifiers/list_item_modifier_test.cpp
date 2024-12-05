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
#include "core/components_ng/pattern/list/list_item_event_hub.h"
#include "core/components_v2/list/list_properties.h"

#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace  {
    struct EventsTracker {
        static inline GENERATED_ArkUIListItemEventsReceiver listItemEventReceiver {};

        static inline const GENERATED_ArkUIEventsAPI eventsApiImpl = {
            .getListItemEventsReceiver = [] () -> const GENERATED_ArkUIListItemEventsReceiver* {
                return &listItemEventReceiver;
            }
        };
    }; // EventsTracker
} // namespace

class ListItemModifierTest : public ModifierTestBase<GENERATED_ArkUIListItemModifier,
    &GENERATED_ArkUINodeModifiers::getListItemModifier, GENERATED_ARKUI_LIST_ITEM> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        fullAPI_->setArkUIEventsAPI(&EventsTracker::eventsApiImpl);
    }
};

/*
 * @tc.name: setListItemOptions0Test
 * @tc.desc: Check the functionality of ListItemModifier.setListItemOptions0
 * @tc.type: FUNC
 */
HWTEST_F(ListItemModifierTest, setListItemOptions0Test, TestSize.Level1)
{
    auto style = GetAttrValue<std::string>(node_, "itemStyle");
    EXPECT_EQ(style, "ListItemStyle.NONE");

    Ark_ListItemOptions listItemOptions = {.style = Converter::ArkValue<Opt_ListItemStyle>(V2::ListItemStyle::CARD)};
    Opt_ListItemOptions arg = Converter::ArkValue<Opt_ListItemOptions>(listItemOptions);
    modifier_->setListItemOptions0(node_, &arg);
    style = GetAttrValue<std::string>(node_, "itemStyle");
    EXPECT_EQ(style, "ListItemStyle.CARD");

    arg = Converter::ArkValue<Opt_ListItemOptions>(Ark_Empty());
    modifier_->setListItemOptions0(node_, &arg);
    style = GetAttrValue<std::string>(node_, "itemStyle");
    EXPECT_EQ(style, "ListItemStyle.CARD");

    listItemOptions = {.style = Converter::ArkValue<Opt_ListItemStyle>(Ark_Empty())};
    arg = Converter::ArkValue<Opt_ListItemOptions>(listItemOptions);
    modifier_->setListItemOptions0(node_, &arg);
    style = GetAttrValue<std::string>(node_, "itemStyle");
    EXPECT_EQ(style, "ListItemStyle.NONE");
}

/**
 * @tc.name: setStickyTest
 * @tc.desc: Check the functionality of ListItemModifier.setSticky
 * @tc.type: FUNC
 */
HWTEST_F(ListItemModifierTest, setStickyTest, TestSize.Level1)
{
    auto checkValue = GetAttrValue<std::string>(node_, "sticky");
    EXPECT_EQ(checkValue, "Sticky.None");

    modifier_->setSticky(node_, Converter::ArkValue<Ark_Sticky>(V2::StickyMode::NORMAL));
    checkValue = GetAttrValue<std::string>(node_, "sticky");
    EXPECT_EQ(checkValue, "Sticky.Normal");

    modifier_->setSticky(node_, Converter::ArkValue<Ark_Sticky>(V2::StickyMode::NONE));
    checkValue = GetAttrValue<std::string>(node_, "sticky");
    EXPECT_EQ(checkValue, "Sticky.None");

    modifier_->setSticky(node_, Converter::ArkValue<Ark_Sticky>(V2::StickyMode::OPACITY));
    checkValue = GetAttrValue<std::string>(node_, "sticky");
    EXPECT_EQ(checkValue, "Sticky.Opacity");

    modifier_->setSticky(node_, Converter::ArkValue<Ark_Sticky>(static_cast<V2::StickyMode>(-10)));
    checkValue = GetAttrValue<std::string>(node_, "sticky");
    EXPECT_EQ(checkValue, "Sticky.None");
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
    modifier_->setSelectable(node_, Converter::ArkValue<Ark_Boolean>(false));
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
    modifier_->setSelected(node_, Converter::ArkValue<Ark_Boolean>(true));
    selected = GetAttrValue<bool>(node_, "selected");
    EXPECT_TRUE(selected);
}

/*
 * @tc.name: setEditableTest
 * @tc.desc: Check the functionality of ListItemModifier.setEditable
 * @tc.type: FUNC
 */
HWTEST_F(ListItemModifierTest, setEditableTest, TestSize.Level1)
{
    bool editable = GetAttrValue<bool>(node_, "editable");
    EXPECT_FALSE(editable);

    auto argEditMode = Converter::ArkUnion<Ark_Union_Boolean_EditMode, Ark_EditMode>
        (Ark_EditMode::ARK_EDIT_MODE_NONE);
    modifier_->setEditable(node_, &argEditMode);
    auto editableStr = GetAttrValue<std::string>(node_, "editable");
    EXPECT_EQ(editableStr, "EditMode.None");

    argEditMode = Converter::ArkUnion<Ark_Union_Boolean_EditMode, Ark_EditMode>
        (Ark_EditMode::ARK_EDIT_MODE_DELETABLE);
    modifier_->setEditable(node_, &argEditMode);
    editableStr = GetAttrValue<std::string>(node_, "editable");
    EXPECT_EQ(editableStr, "EditMode.Deletable");

    argEditMode = Converter::ArkUnion<Ark_Union_Boolean_EditMode, Ark_EditMode>
        (Ark_EditMode::ARK_EDIT_MODE_MOVABLE);
    modifier_->setEditable(node_, &argEditMode);
    editableStr = GetAttrValue<std::string>(node_, "editable");
    EXPECT_EQ(editableStr, "EditMode.Movable");

    auto argBool = Converter::ArkUnion<Ark_Union_Boolean_EditMode, Ark_Boolean>(true);
    modifier_->setEditable(node_, &argBool);
    editable = GetAttrValue<bool>(node_, "editable");
    EXPECT_TRUE(editable);

    argBool = Converter::ArkUnion<Ark_Union_Boolean_EditMode, Ark_Boolean>(false);
    modifier_->setEditable(node_, &argBool);
    editableStr = GetAttrValue<std::string>(node_, "editable");
    EXPECT_EQ(editableStr, "EditMode.None");
}

/*
 * @tc.name: setOnSelectTest
 * @tc.desc: Check the functionality of ListItemModifier.setOnSelect
 * @tc.type: FUNC
 */
HWTEST_F(ListItemModifierTest, setOnSelectTest, TestSize.Level1)
{
    Callback_Boolean_Void func{};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<ListItemEventHub>();

    struct CheckEvent {
        int32_t nodeId;
        bool isSelected;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    EventsTracker::listItemEventReceiver.onSelect = [](Ark_Int32 nodeId, const Ark_Boolean isSelected)
    {
        checkEvent = {
            .nodeId = nodeId,
            .isSelected = Converter::ArkValue<Ark_Boolean>(isSelected)
        };
    };

    modifier_->setOnSelect(node_, &func);
    // check true value
    EXPECT_EQ(checkEvent.has_value(), false);
    eventHub->FireSelectChangeEvent(true);
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->isSelected, true);
    // check false value
    eventHub->FireSelectChangeEvent(false);
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->isSelected, false);
}

/**
 * @tc.name: setSwipeActionEdgeEffectTest
 * @tc.desc: Check the functionality of ListItemModifier.setSwipeAction
 * @tc.type: FUNC
 */
HWTEST_F(ListItemModifierTest, DISABLED_setSwipeActionEdgeEffectTest, TestSize.Level1)
{
    // the test is disabled since there is a mistake in ListItemLayoutProperty::ToJsonValue
    // it returns "SwipeEdgeEffect.Node" string for SwipeEdgeEffect.None
    // https://gitee.com/openharmony/arkui_ace_engine/issues/IAT4SB?from=project-issue

    auto fullJson = GetJsonValue(node_);
    auto swipeAction = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "swipeAction");
    auto edgeEffect = GetAttrValue<std::string>(swipeAction, "edgeEffect");
    EXPECT_EQ(edgeEffect, "");

    Ark_SwipeActionOptions  options = {
        .start = Converter::ArkValue<Opt_Union_CustomBuilder_SwipeActionItem>(Ark_Empty()),
        .end = Converter::ArkValue<Opt_Union_CustomBuilder_SwipeActionItem>(Ark_Empty()),
        .onOffsetChange = Converter::ArkValue<Opt_Callback_Number_Void>(Ark_Empty()),
        .edgeEffect = Converter::ArkValue<Opt_SwipeEdgeEffect>(V2::SwipeEdgeEffect::None)
    };
    modifier_->setSwipeAction(node_, &options);
    fullJson = GetJsonValue(node_);
    swipeAction = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "swipeAction");
    edgeEffect = GetAttrValue<std::string>(swipeAction, "edgeEffect");
    EXPECT_EQ(edgeEffect, "SwipeEdgeEffect.None");

    options = {
        .start = Converter::ArkValue<Opt_Union_CustomBuilder_SwipeActionItem>(Ark_Empty()),
        .end = Converter::ArkValue<Opt_Union_CustomBuilder_SwipeActionItem>(Ark_Empty()),
        .edgeEffect = Converter::ArkValue<Opt_SwipeEdgeEffect>(V2::SwipeEdgeEffect::Spring)
    };
    modifier_->setSwipeAction(node_, &options);
    fullJson = GetJsonValue(node_);
    swipeAction = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "swipeAction");
    edgeEffect = GetAttrValue<std::string>(swipeAction, "edgeEffect");
    EXPECT_EQ(edgeEffect, "SwipeEdgeEffect.Spring");

    options = {
        .start = Converter::ArkValue<Opt_Union_CustomBuilder_SwipeActionItem>(Ark_Empty()),
        .end = Converter::ArkValue<Opt_Union_CustomBuilder_SwipeActionItem>(Ark_Empty()),
        .edgeEffect = Converter::ArkValue<Opt_SwipeEdgeEffect>(static_cast<V2::SwipeEdgeEffect>(-10))
    };
    modifier_->setSwipeAction(node_, &options);
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
HWTEST_F(ListItemModifierTest, DISABLED_setSwipeActionActionsTest, TestSize.Level1)
{
}
} // namespace OHOS::Ace::NG
