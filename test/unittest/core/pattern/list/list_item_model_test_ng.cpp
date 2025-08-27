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

#include <cstdint>

#include "gtest/gtest.h"
#include "list_test_ng.h"

#include "core/components_ng/pattern/arc_list/arc_list_item_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

class ListItemModelTestNg : public ListTestNg {};

/**
 * @tc.name: Create_OneParameter_isCreateArc
 * @tc.desc: Test ListItemModelNG Create
 * @tc.type: FUNC
 */
HWTEST_F(ListItemModelTestNg, Create_OneParameter_isCreateArc, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create listitem model
     */
    ListItemModelNG model;
    model.Create(true);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);

    /**
     * @tc.steps: step2. Get the pattern of listitem node
     * @tc.expected: The pattern is typed as ArcListItemPattern
     */
    auto pattern = listNode->GetPattern<ArcListItemPattern>();
    EXPECT_NE(pattern, nullptr);
    CreateDone();
}

/**
 * @tc.name: SetSelectable_OneParameter
 * @tc.desc: Test ListItemModelNG SetSelectable
 * @tc.type: FUNC
 */
HWTEST_F(ListItemModelTestNg, SetSelectable_OneParameter, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create listitem model
     */
    ListItemModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListItemPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Calling the SetSelectable function
     * @tc.expected: The Selectable of pattern return true
     */
    model.SetSelectable(true);
    EXPECT_TRUE(pattern->Selectable());
    CreateDone();
}

/**
 * @tc.name: SetSelected_OneParameter
 * @tc.desc: Test ListItemModelNG SetSelected
 * @tc.type: FUNC
 */
HWTEST_F(ListItemModelTestNg, SetSelected_OneParameter, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create listitem model
     */
    ListItemModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListItemPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<ListItemEventHub> listItemEventHub = AceType::MakeRefPtr<ListItemEventHub>();
    listNode->eventHub_ = listItemEventHub;
    auto eventHub = listNode->GetEventHub<ListItemEventHub>();

    /**
     * @tc.steps: step2. Calling the SetSelected function
     * @tc.expected: The IsSelected of pattern return true and the stateStyleMgr_ currentState_ is UI_STATE_SELECTED
     */
    model.SetSelected(true);
    EXPECT_TRUE(pattern->IsSelected());
    EXPECT_EQ(eventHub->stateStyleMgr_->currentState_, UI_STATE_SELECTED);
    CreateDone();
}

/**
 * @tc.name: SetSelectChangeEvent
 * @tc.desc: Test ListItemModelNG SetSelectChangeEvent
 * @tc.type: FUNC
 */
HWTEST_F(ListItemModelTestNg, SetSelectChangeEvent, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create listitem model
     */
    ListItemModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListItemPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<ListItemEventHub> listItemEventHub = AceType::MakeRefPtr<ListItemEventHub>();
    listNode->eventHub_ = listItemEventHub;
    auto eventHub = listNode->GetEventHub<ListItemEventHub>();

    /**
     * @tc.steps: step2. Set the isChanged to false
     * and set the selectChangeEvent
     */
    bool isChanged = false;
    auto selectChange = [&isChanged](bool isSelected) {
        if (isSelected) {
            isChanged = true;
        } else {
            isChanged = false;
        }
    };

    /**
     * @tc.steps: step3. Calling the SetSelectChangeEvent function
     * @tc.expected: The isChanged is true after calling the FireSelectChangeEvent
     */
    model.SetSelectChangeEvent(std::move(selectChange));
    eventHub->FireSelectChangeEvent(true);
    EXPECT_TRUE(isChanged);
    CreateDone();
}

/**
 * @tc.name: SetSelectCallback_OneParameter
 * @tc.desc: Test ListItemModelNG SetSelectCallback
 * @tc.type: FUNC
 */
HWTEST_F(ListItemModelTestNg, SetSelectCallback_OneParameter, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create listitem model
     */
    ListItemModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListItemPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<ListItemEventHub> listItemEventHub = AceType::MakeRefPtr<ListItemEventHub>();
    listNode->eventHub_ = listItemEventHub;
    auto eventHub = listNode->GetEventHub<ListItemEventHub>();

    /**
     * @tc.steps: step2. Set the isChanged to false
     * and set the selectChangeEvent
     */
    bool isChanged = false;
    auto onSelect = [&isChanged](bool isSelected) {
        if (isSelected) {
            isChanged = true;
        } else {
            isChanged = false;
        }
    };

    /**
     * @tc.steps: step3. Calling the SetSelectCallback function
     * @tc.expected: The isChanged is true after calling the selectCallback
     */
    model.SetSelectCallback(std::move(onSelect));
    auto selectCallback = eventHub->GetOnSelect();
    selectCallback(true);
    EXPECT_TRUE(isChanged);
    CreateDone();
}

/**
 * @tc.name: SetSelected_TwoParameters
 * @tc.desc: Test ListItemModelNG SetSelected
 * @tc.type: FUNC
 */
HWTEST_F(ListItemModelTestNg, SetSelected_TwoParameters, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create listitem model
     */
    ListItemModelNG model;
    auto listNode = FrameNode::CreateFrameNode(
        V2::LIST_ITEM_ETS_TAG, 0, AceType::MakeRefPtr<ListItemPattern>(nullptr, V2::ListItemStyle::NONE));
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListItemPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<ListItemEventHub> listItemEventHub = AceType::MakeRefPtr<ListItemEventHub>();
    listNode->eventHub_ = listItemEventHub;
    auto eventHub = listNode->GetEventHub<ListItemEventHub>();

    /**
     * @tc.steps: step2. Calling the SetSelected function
     */
    model.SetSelected(AceType::RawPtr(listNode), true);

    /**
     * @tc.steps: step3. Calling the IsSelected function
     * @tc.expected: The result return true and the stateStyleMgr_ currentState_ is UI_STATE_SELECTED
     */
    auto result = pattern->IsSelected();
    EXPECT_TRUE(result);
    EXPECT_EQ(eventHub->stateStyleMgr_->currentState_, UI_STATE_SELECTED);
}

/**
 * @tc.name: SetSelectable_TwoParameters
 * @tc.desc: Test ListItemModelNG SetSelectable
 * @tc.type: FUNC
 */
HWTEST_F(ListItemModelTestNg, SetSelectable_TwoParameters, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create listitem model
     */
    ListItemModelNG model;
    auto listNode = FrameNode::CreateFrameNode(
        V2::LIST_ITEM_ETS_TAG, 0, AceType::MakeRefPtr<ListItemPattern>(nullptr, V2::ListItemStyle::NONE));
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListItemPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Calling the SetSelectable function
     */
    model.SetSelectable(AceType::RawPtr(listNode), true);

    /**
     * @tc.steps: step3. Calling the Selectable function
     * @tc.expected: The result return true
     */
    auto result = pattern->Selectable();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: SetSwiperAction
 * @tc.desc: Test ListItemModelNG SetSwiperAction
 * @tc.type: FUNC
 */
HWTEST_F(ListItemModelTestNg, SetSwiperAction, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create listitem model
     */
    ListItemModelNG model;
    auto listNode = FrameNode::CreateFrameNode(
        V2::LIST_ITEM_ETS_TAG, 0, AceType::MakeRefPtr<ListItemPattern>(nullptr, V2::ListItemStyle::NONE));
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListItemPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<ListItemLayoutProperty> listItemLayoutProperty = AceType::MakeRefPtr<ListItemLayoutProperty>();
    listNode->SetLayoutProperty(listItemLayoutProperty);
    auto layoutProperty = listNode->GetLayoutProperty<ListItemLayoutProperty>();
    RefPtr<ListItemEventHub> listItemEventHub = AceType::MakeRefPtr<ListItemEventHub>();
    listNode->eventHub_ = listItemEventHub;
    auto eventHub = listNode->GetEventHub<ListItemEventHub>();

    /**
     * @tc.steps: step2. Calling the SetSwiperAction function
     * and set the startAction, endAction and onOffsetChangeFunc
     */
    auto startAction = []() {};
    auto endAction = []() {};
    int32_t data = 2;
    auto onOffsetChangeFunc = [&data](int32_t offset) { data += offset; };
    model.SetSwiperAction(AceType::RawPtr(listNode), std::move(startAction), std::move(endAction),
        std::move(onOffsetChangeFunc), V2::SwipeEdgeEffect::Spring);

    /**
     * @tc.steps: step3. Calling the FireOffsetChangeEvent function
     * @tc.expected: The data return 12 and the edgeEffect is Spring
     */
    eventHub->FireOffsetChangeEvent(10);
    EXPECT_EQ(data, 12);
    EXPECT_EQ(layoutProperty->GetEdgeEffect().value(), V2::SwipeEdgeEffect::Spring);
}

/**
 * @tc.name: SetSelectCallback_TwoParameters
 * @tc.desc: Test ListItemModelNG SetSelectCallback
 * @tc.type: FUNC
 */
HWTEST_F(ListItemModelTestNg, SetSelectCallback_TwoParameters, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create listitem model
     */
    ListItemModelNG model;
    auto listNode = FrameNode::CreateFrameNode(
        V2::LIST_ITEM_ETS_TAG, 0, AceType::MakeRefPtr<ListItemPattern>(nullptr, V2::ListItemStyle::NONE));
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListItemPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<ListItemEventHub> listItemEventHub = AceType::MakeRefPtr<ListItemEventHub>();
    listNode->eventHub_ = listItemEventHub;
    auto eventHub = listNode->GetEventHub<ListItemEventHub>();

    /**
     * @tc.steps: step2. Set the isChanged to false
     * and set the selectChangeEvent
     */
    bool isChanged = false;
    auto onSelect = [&isChanged](bool isSelected) {
        if (isSelected) {
            isChanged = true;
        } else {
            isChanged = false;
        }
    };

    /**
     * @tc.steps: step3. Calling the SetSelectCallback function
     * @tc.expected: The isChanged is true after calling the selectCallback
     */
    model.SetSelectCallback(AceType::RawPtr(listNode), std::move(onSelect));
    auto selectCallback = eventHub->GetOnSelect();
    selectCallback(true);
    EXPECT_TRUE(isChanged);
}

/**
 * @tc.name: SetStyle_TwoParameters
 * @tc.desc: Test ListItemModelNG SetStyle
 * @tc.type: FUNC
 */
HWTEST_F(ListItemModelTestNg, SetStyle_TwoParameters, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create listitem model
     */
    ListItemModelNG model;
    auto listNode = FrameNode::CreateFrameNode(
        V2::LIST_ITEM_ETS_TAG, 0, AceType::MakeRefPtr<ListItemPattern>(nullptr, V2::ListItemStyle::NONE));
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListItemPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Calling the SetStyle function
     * @tc.expected: The listItemStyle_ of pattern is V2::ListItemStyle::CARD
     */
    model.SetStyle(AceType::RawPtr(listNode), V2::ListItemStyle::CARD);
    EXPECT_EQ(pattern->listItemStyle_, V2::ListItemStyle::CARD);
}
} // namespace OHOS::Ace::NG