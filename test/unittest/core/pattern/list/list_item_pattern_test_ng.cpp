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

#include <utility>

#include "gtest/gtest.h"
#include "test/unittest/core/pattern/test_ng.h"
#include "list_test_ng.h"

#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/list/list_item_event_hub.h"
#include "core/components_ng/pattern/list/list_item_layout_property.h"
#include "core/components_ng/pattern/list/list_item_model_ng.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/syntax/shallow_builder.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_2_node.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

class ListItemPatternTestNg : public ListTestNg {
public:
    RefPtr<FrameNode> CreateSwipeNode()
    {
        auto column = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<LinearLayoutPattern>(true));
        auto button = FrameNode::CreateFrameNode(
            V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
        button->MountToParent(column);
        return column;
    };
};

/**
 * @tc.name: OnThemeScopeUpdate000
 * @tc.desc: Test ListItemPattern OnThemeScopeUpdate: API>=26 + CARD + UserNotSetBgColor
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, OnThemeScopeUpdate000, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with CARD style ListItem
     */
    CreateList();
    CreateListItems(1, V2::ListItemStyle::CARD);
    CreateDone();

    /**
     * @tc.steps: step2. Get ListItem node and set theme color
     */
    auto listItem = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(listItem, nullptr);

    auto pattern = listItem->GetPattern<ListItemPattern>();
    ASSERT_NE(pattern, nullptr);

    auto renderContext = listItem->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateBackgroundColor(Color::BLUE);

    // Set theme color to RED
    auto listItemTheme = MockPipelineContext::pipeline_->GetTheme<ListItemTheme>();
    auto originalColor = listItemTheme->itemDefaultColor_;
    listItemTheme->itemDefaultColor_ = Color::RED;

    /**
     * @tc.steps: step3. Set API version to VERSION_TWENTY_SIX and call OnThemeScopeUpdate
     * @tc.expected: Background color is updated to theme color (RED)
     */
    auto oriApiVersion = listItem->apiVersion_;
    listItem->apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX);
    pattern->OnThemeScopeUpdate(0);
    auto bgColor = renderContext->GetBackgroundColor();
    EXPECT_TRUE(bgColor.has_value());
    EXPECT_EQ(bgColor.value(), Color::RED); // Verify color equals theme color

    // Restore
    listItem->apiVersion_ = oriApiVersion;
    listItemTheme->itemDefaultColor_ = originalColor;
}

/**
 * @tc.name: OnThemeScopeUpdate001
 * @tc.desc: Test ListItemPattern OnThemeScopeUpdate: API>=26 + CARD + UserNotSetBgColor
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, OnThemeScopeUpdate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with CARD style ListItem
     */
    CreateList();
    CreateListItems(1, V2::ListItemStyle::CARD);
    CreateDone();

    /**
     * @tc.steps: step2. Get ListItem node and set theme color
     */
    auto listItem = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(listItem, nullptr);

    auto pattern = listItem->GetPattern<ListItemPattern>();
    ASSERT_NE(pattern, nullptr);

    auto renderContext = listItem->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    // Set theme color to RED
    auto listItemTheme = MockPipelineContext::pipeline_->GetTheme<ListItemTheme>();
    auto originalColor = listItemTheme->itemDefaultColor_;
    listItemTheme->itemDefaultColor_ = Color::RED;

    /**
     * @tc.steps: step3. Set API version to VERSION_TWENTY_SIX and call OnThemeScopeUpdate
     * @tc.expected: Background color is updated to theme color (RED)
     */
    auto oriApiVersion = listItem->apiVersion_;
    listItem->apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX);
    pattern->OnThemeScopeUpdate(0);
    auto bgColor = renderContext->GetBackgroundColor();
    EXPECT_TRUE(bgColor.has_value());
    EXPECT_EQ(bgColor.value(), Color::RED); // Verify color equals theme color

    // Restore
    listItem->apiVersion_ = oriApiVersion;
    listItemTheme->itemDefaultColor_ = originalColor;
}

/**
 * @tc.name: OnThemeScopeUpdate002
 * @tc.desc: Test ListItemPattern OnThemeScopeUpdate: API>=26 + CARD + UserSetBgColor
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, OnThemeScopeUpdate002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with CARD style ListItem
     */
    CreateList();
    CreateListItems(1, V2::ListItemStyle::CARD);
    CreateDone();

    /**
     * @tc.steps: step2. Get ListItem node and set background color
     */
    auto listItem = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(listItem, nullptr);

    auto pattern = listItem->GetPattern<ListItemPattern>();
    ASSERT_NE(pattern, nullptr);

    auto renderContext = listItem->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateBackgroundColor(Color::BLUE);

    auto layoutProperty = listItem->GetLayoutProperty<ListItemLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateIsUserSetBackgroundColor(true);

    /**
     * @tc.steps: step3. Set API version to VERSION_TWENTY_SIX and call OnThemeScopeUpdate
     * @tc.expected: Background color remains unchanged (equal to BLUE)
     */
    auto oriApiVersion = listItem->apiVersion_;
    listItem->apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX);
    pattern->OnThemeScopeUpdate(0);
    auto bgColor = renderContext->GetBackgroundColor();
    EXPECT_TRUE(bgColor.has_value());
    EXPECT_EQ(bgColor.value(), Color::BLUE);

    listItem->apiVersion_ = oriApiVersion;
}

/**
 * @tc.name: OnThemeScopeUpdate003
 * @tc.desc: Test ListItemPattern OnThemeScopeUpdate: API>=26 + NONE + UserNotSetBgColor
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, OnThemeScopeUpdate003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with NONE style ListItem
     */
    CreateList();
    CreateListItems(1, V2::ListItemStyle::NONE);
    CreateDone();

    /**
     * @tc.steps: step2. Get ListItem node and set API version
     */
    auto listItem = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(listItem, nullptr);

    auto pattern = listItem->GetPattern<ListItemPattern>();
    ASSERT_NE(pattern, nullptr);

    auto renderContext = listItem->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateBackgroundColor(Color::BLUE);

    /**
     * @tc.steps: step3. Set API version to VERSION_TWENTY_SIX and call OnThemeScopeUpdate
     * @tc.expected: Background color remains unchanged due to NONE style
     */
    auto oriApiVersion = listItem->apiVersion_;
    listItem->apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX);
    pattern->OnThemeScopeUpdate(0);
    auto bgColor = listItem->GetRenderContext()->GetBackgroundColor();
    EXPECT_TRUE(bgColor.has_value());
    EXPECT_EQ(bgColor.value(), Color::BLUE);

    listItem->apiVersion_ = oriApiVersion;
}

/**
 * @tc.name: OnThemeScopeUpdate004
 * @tc.desc: Test ListItemPattern OnThemeScopeUpdate: API>=26 + NONE + UserSetBgColor
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, OnThemeScopeUpdate004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with NONE style ListItem
     */
    CreateList();
    CreateListItems(1, V2::ListItemStyle::NONE);
    CreateDone();

    /**
     * @tc.steps: step2. Get ListItem node and set background color
     */
    auto listItem = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(listItem, nullptr);

    auto pattern = listItem->GetPattern<ListItemPattern>();
    ASSERT_NE(pattern, nullptr);

    auto renderContext = listItem->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateBackgroundColor(Color::GREEN);

    auto layoutProperty = listItem->GetLayoutProperty<ListItemLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateIsUserSetBackgroundColor(true);

    /**
     * @tc.steps: step3. Set API version to VERSION_TWENTY_SIX and call OnThemeScopeUpdate
     * @tc.expected: Background color remains unchanged (equal to GREEN)
     */
    auto oriApiVersion = listItem->apiVersion_;
    listItem->apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX);
    pattern->OnThemeScopeUpdate(0);
    auto bgColor = renderContext->GetBackgroundColor();
    EXPECT_TRUE(bgColor.has_value());
    EXPECT_EQ(bgColor.value(), Color::GREEN);

    listItem->apiVersion_ = oriApiVersion;
}

/**
 * @tc.name: OnThemeScopeUpdate005
 * @tc.desc: Test ListItemPattern OnThemeScopeUpdate: API<26 + CARD + UserNotSetBgColor
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, OnThemeScopeUpdate005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with CARD style ListItem
     */
    CreateList();
    CreateListItems(1, V2::ListItemStyle::CARD);
    CreateDone();

    /**
     * @tc.steps: step2. Get ListItem node and set background color
     */
    auto listItem = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(listItem, nullptr);

    auto pattern = listItem->GetPattern<ListItemPattern>();
    ASSERT_NE(pattern, nullptr);

    auto renderContext = listItem->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateBackgroundColor(Color::GRAY);

    auto layoutProperty = listItem->GetLayoutProperty<ListItemLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateIsUserSetBackgroundColor(false);

    /**
     * @tc.steps: step3. Set API version to VERSION_TWENTY_FIVE and call OnThemeScopeUpdate
     * @tc.expected: Background color remains unchanged (equal to GRAY) due to API < 26
     */
    auto oriApiVersion = listItem->apiVersion_;
    listItem->apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_FIVE);
    pattern->OnThemeScopeUpdate(0);
    auto bgColor = renderContext->GetBackgroundColor();
    EXPECT_TRUE(bgColor.has_value());
    EXPECT_EQ(bgColor.value(), Color::GRAY);

    listItem->apiVersion_ = oriApiVersion;
}

/**
 * @tc.name: OnThemeScopeUpdate006
 * @tc.desc: Test ListItemPattern OnThemeScopeUpdate: API<26 + CARD + UserSetBgColor
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, OnThemeScopeUpdate006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with CARD style ListItem
     */
    CreateList();
    CreateListItems(1, V2::ListItemStyle::CARD);
    CreateDone();

    /**
     * @tc.steps: step2. Get ListItem node and set background color
     */
    auto listItem = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(listItem, nullptr);

    auto pattern = listItem->GetPattern<ListItemPattern>();
    ASSERT_NE(pattern, nullptr);

    auto renderContext = listItem->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateBackgroundColor(Color::BLACK);

    auto layoutProperty = listItem->GetLayoutProperty<ListItemLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateIsUserSetBackgroundColor(true);

    /**
     * @tc.steps: step3. Set API version to VERSION_TWENTY_FIVE and call OnThemeScopeUpdate
     * @tc.expected: Background color remains unchanged (equal to BLACK)
     */
    auto oriApiVersion = listItem->apiVersion_;
    listItem->apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_FIVE);
    pattern->OnThemeScopeUpdate(0);
    auto bgColor = renderContext->GetBackgroundColor();
    EXPECT_TRUE(bgColor.has_value());
    EXPECT_EQ(bgColor.value(), Color::BLACK);

    listItem->apiVersion_ = oriApiVersion;
}

/**
 * @tc.name: OnThemeScopeUpdate007
 * @tc.desc: Test ListItemPattern OnThemeScopeUpdate: API<26 + NONE + UserNotSetBgColor
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, OnThemeScopeUpdate007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with NONE style ListItem
     */
    CreateList();
    CreateListItems(1, V2::ListItemStyle::NONE);
    CreateDone();

    /**
     * @tc.steps: step2. Get ListItem node and set background color
     */
    auto listItem = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(listItem, nullptr);

    auto pattern = listItem->GetPattern<ListItemPattern>();
    ASSERT_NE(pattern, nullptr);

    auto renderContext = listItem->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateBackgroundColor(Color::BLUE);

    auto layoutProperty = listItem->GetLayoutProperty<ListItemLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateIsUserSetBackgroundColor(false);

    /**
     * @tc.steps: step3. Set API version to VERSION_TWENTY_FIVE and call OnThemeScopeUpdate
     * @tc.expected: Background color remains unchanged due to API < 26
     */
    auto oriApiVersion = listItem->apiVersion_;
    listItem->apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_FIVE);
    pattern->OnThemeScopeUpdate(0);
    auto bgColor = renderContext->GetBackgroundColor();
    EXPECT_TRUE(bgColor.has_value());
    EXPECT_EQ(bgColor.value(), Color::BLUE);

    listItem->apiVersion_ = oriApiVersion;
}

/**
 * @tc.name: OnThemeScopeUpdate008
 * @tc.desc: Test ListItemPattern OnThemeScopeUpdate: API<26 + NONE + UserSetBgColor
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, OnThemeScopeUpdate008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with NONE style ListItem
     */
    CreateList();
    CreateListItems(1, V2::ListItemStyle::NONE);
    CreateDone();

    /**
     * @tc.steps: step2. Get ListItem node and set background color
     */
    auto listItem = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(listItem, nullptr);

    auto pattern = listItem->GetPattern<ListItemPattern>();
    ASSERT_NE(pattern, nullptr);

    auto renderContext = listItem->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateBackgroundColor(Color::GREEN);

    auto layoutProperty = listItem->GetLayoutProperty<ListItemLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateIsUserSetBackgroundColor(true);

    /**
     * @tc.steps: step3. Set API version to VERSION_TWENTY_FIVE and call OnThemeScopeUpdate
     * @tc.expected: Background color remains unchanged
     */
    auto oriApiVersion = listItem->apiVersion_;
    listItem->apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_FIVE);
    pattern->OnThemeScopeUpdate(0);
    auto bgColor = renderContext->GetBackgroundColor();
    EXPECT_TRUE(bgColor.has_value());
    EXPECT_EQ(bgColor.value(), Color::GREEN);

    listItem->apiVersion_ = oriApiVersion;
}

/**
 * @tc.name: OnDidPop001
 * @tc.desc: Test ListItemPattern OnDidPop
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, OnDidPop001, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->children_ = { frameNode, frameNode, frameNode, frameNode, frameNode };
    listItemPattern->frameNode_ = frameNode;
    listItemPattern->endNodeIndex_ = 2;
    listItemPattern->childNodeIndex_ = 3;
    listItemPattern->OnDidPop();
    EXPECT_EQ(listItemPattern->endNodeIndex_, 0);
    EXPECT_EQ(listItemPattern->childNodeIndex_, 2);
}

/**
 * @tc.name: OnDidPop002
 * @tc.desc: Test ListItemPattern OnDidPop
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, OnDidPop002, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->children_ = { frameNode, frameNode, frameNode, frameNode, frameNode };
    listItemPattern->frameNode_ = frameNode;
    listItemPattern->endNodeIndex_ = 2;
    listItemPattern->childNodeIndex_ = 1;
    listItemPattern->OnDidPop();
    EXPECT_EQ(listItemPattern->endNodeIndex_, 2);
    EXPECT_EQ(listItemPattern->childNodeIndex_, 1);
}

/**
 * @tc.name: OnDidPop003
 * @tc.desc: Test ListItemPattern OnDidPop
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, OnDidPop003, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->children_ = { frameNode, frameNode, frameNode, frameNode, frameNode };
    listItemPattern->frameNode_ = frameNode;
    listItemPattern->endNodeIndex_ = -1;
    listItemPattern->childNodeIndex_ = 2;
    listItemPattern->OnDidPop();
    EXPECT_EQ(listItemPattern->endNodeIndex_, -1);
    EXPECT_EQ(listItemPattern->childNodeIndex_, 2);
}

/**
 * @tc.name: GetParentFrameNode001
 * @tc.desc: Test ListItemPattern GetParentFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, GetParentFrameNode001, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->parent_ = frameNode;
    listItemPattern->frameNode_ = frameNode;
    auto result = listItemPattern->GetParentFrameNode();
    EXPECT_EQ(result, frameNode);
}

/**
 * @tc.name: GetParentFrameNode002
 * @tc.desc: Test ListItemPattern GetParentFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, GetParentFrameNode002, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->parent_ = nullptr;
    listItemPattern->frameNode_ = frameNode;
    auto result = listItemPattern->GetParentFrameNode();
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: GetParentFrameNode003
 * @tc.desc: Test ListItemPattern GetParentFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, GetParentFrameNode003, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    std::function<std::pair<RIDType, uint32_t>(IndexType, bool, bool)> onGetRid4Index = [](int32_t index,
        bool inAnimation, bool forceCreateNewChild) {
        return std::make_pair(2, 0);
    };
    std::function<void(IndexType, IndexType)> onRecycleItems = [](int32_t start, int32_t end) {};
    std::function<void(int32_t, int32_t, int32_t, int32_t, bool, bool)> onActiveRange =
        [](int32_t start, int32_t end, int32_t vStart, int32_t vEnd, bool isCache, bool forceUpdate) {};
    std::function<void(IndexType, IndexType)> onMoveFromTo = [](int32_t start, int32_t end) {};
    std::function<void()> onPurge = []() {};
    std::function<void()> onPurgeAll = []() {};
    std::function<void()> onUpdateDirty = []() {};
    RefPtr<RepeatVirtualScroll2Node> node = AceType::MakeRefPtr<RepeatVirtualScroll2Node>(
        2, 2, 5, 0, onGetRid4Index, onRecycleItems, onActiveRange, onMoveFromTo, onPurge, onPurgeAll, onUpdateDirty);
    ASSERT_NE(node, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    node->parent_ = frameNode;
    frameNode->parent_ = node;
    listItemPattern->frameNode_ = frameNode;
    auto result = listItemPattern->GetParentFrameNode();
    EXPECT_EQ(result, frameNode);
}

/**
 * @tc.name: HandleDragStart001
 * @tc.desc: Test ListItemPattern HandleDragStart
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, HandleDragStart001, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    GestureEvent info;
    info.inputEventType_ = InputEventType::AXIS;
    info.sourceTool_ = SourceTool::MOUSE;
    listItemPattern->HandleDragStart(info);
    EXPECT_FALSE(listItemPattern->isDragging_);
}

/**
 * @tc.name: HandleDragStart002
 * @tc.desc: Test ListItemPattern HandleDragStart
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, HandleDragStart002, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    GestureEvent info;
    info.inputEventType_ = InputEventType::MOUSE_BUTTON;
    info.sourceTool_ = SourceTool::MOUSE;
    listItemPattern->HandleDragStart(info);
    EXPECT_TRUE(listItemPattern->isDragging_);
}

/**
 * @tc.name: HandleDragStart003
 * @tc.desc: Test ListItemPattern HandleDragStart
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, HandleDragStart003, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    GestureEvent info;
    info.inputEventType_ = InputEventType::AXIS;
    info.sourceTool_ = SourceTool::AIRBRUSH;
    listItemPattern->HandleDragStart(info);
    EXPECT_TRUE(listItemPattern->isDragging_);
}

/**
 * @tc.name: CalculateFriction001
 * @tc.desc: Test ListItemPattern CalculateFriction
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, CalculateFriction001, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    auto result = listItemPattern->CalculateFriction(2.0f);
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: CalculateFriction002
 * @tc.desc: Test ListItemPattern CalculateFriction
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, CalculateFriction002, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    auto result = listItemPattern->CalculateFriction(-5.0f);
    EXPECT_EQ(result, 1.0f);
}

/**
 * @tc.name: HandleDragUpdate001
 * @tc.desc: Test ListItemPattern HandleDragUpdate
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, HandleDragUpdate001, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    GestureEvent info;
    info.inputEventType_ = InputEventType::AXIS;
    info.sourceTool_ = SourceTool::MOUSE;
    listItemPattern->hasStartDeleteArea_ = true;
    listItemPattern->HandleDragUpdate(info);
    EXPECT_TRUE(listItemPattern->hasStartDeleteArea_);
}

/**
 * @tc.name: HandleDragUpdate002
 * @tc.desc: Test ListItemPattern HandleDragUpdate
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, HandleDragUpdate002, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    RefPtr<ListItemLayoutProperty> listItemLayoutProperty = AceType::MakeRefPtr<ListItemLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = listItemLayoutProperty;
    listItemPattern->frameNode_ = frameNode;
    GestureEvent info;
    info.inputEventType_ = InputEventType::MOUSE_BUTTON;
    info.sourceTool_ = SourceTool::MOUSE;
    listItemPattern->hasStartDeleteArea_ = true;
    listItemPattern->HandleDragUpdate(info);
    EXPECT_FALSE(listItemPattern->hasStartDeleteArea_);
}

/**
 * @tc.name: HandleDragUpdate003
 * @tc.desc: Test ListItemPattern HandleDragUpdate
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, HandleDragUpdate003, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    RefPtr<ListItemLayoutProperty> listItemLayoutProperty = AceType::MakeRefPtr<ListItemLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = listItemLayoutProperty;
    listItemPattern->frameNode_ = frameNode;
    GestureEvent info;
    info.inputEventType_ = InputEventType::AXIS;
    info.sourceTool_ = SourceTool::AIRBRUSH;
    listItemPattern->hasStartDeleteArea_ = true;
    listItemPattern->HandleDragUpdate(info);
    EXPECT_FALSE(listItemPattern->hasStartDeleteArea_);
}

/**
 * @tc.name: OnRecycle001
 * @tc.desc: Test ListItemPatternTestNg OnRecycle001
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, OnRecycle001, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    listItemPattern->OnRecycle();
    EXPECT_EQ(listItemPattern->swipeActionState_, SwipeActionState::COLLAPSED);
    EXPECT_EQ(listItemPattern->curOffset_, 0.0f);
}


/**
 * @tc.name: HandleDragEnd001
 * @tc.desc: Test ListItemPattern HandleDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, HandleDragEnd001, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    GestureEvent info;
    info.inputEventType_ = InputEventType::AXIS;
    info.sourceTool_ = SourceTool::MOUSE;
    listItemPattern->isDragging_ = true;
    listItemPattern->HandleDragEnd(info);
    EXPECT_TRUE(listItemPattern->isDragging_);
}

/**
 * @tc.name: HandleDragEnd002
 * @tc.desc: Test ListItemPattern HandleDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, HandleDragEnd002, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    auto node = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, listPattern);
    ASSERT_NE(node, nullptr);
    node->tag_ = V2::LIST_ETS_TAG;
    node->pattern_ = listPattern;
    frameNode->parent_ = node;
    listItemPattern->frameNode_ = frameNode;
    listPattern->swiperItem_ = listItemPattern;
    listPattern->canReplaceSwiperItem_ = false;
    RefPtr<ListItemEventHub> listItemEventHub = AceType::MakeRefPtr<ListItemEventHub>();
    listItemEventHub->startOnDeleteEvent_ = []() {};
    listItemEventHub->endOnDeleteEvent_ = []() {};
    frameNode->eventHub_ = listItemEventHub;
    GestureEvent info;
    info.inputEventType_ = InputEventType::MOUSE_BUTTON;
    info.sourceTool_ = SourceTool::MOUSE;
    listItemPattern->isDragging_ = true;
    listItemPattern->HandleDragEnd(info);
    EXPECT_TRUE(listPattern->canReplaceSwiperItem_);
    EXPECT_FALSE(listItemPattern->isDragging_);
}

/**
 * @tc.name: HandleDragEnd003
 * @tc.desc: Test ListItemPattern HandleDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, HandleDragEnd003, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    auto node = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, listPattern);
    ASSERT_NE(node, nullptr);
    node->tag_ = V2::LIST_ETS_TAG;
    node->pattern_ = listPattern;
    frameNode->parent_ = node;
    listItemPattern->frameNode_ = frameNode;
    listPattern->swiperItem_ = listItemPattern;
    listPattern->canReplaceSwiperItem_ = false;
    RefPtr<ListItemEventHub> listItemEventHub = AceType::MakeRefPtr<ListItemEventHub>();
    listItemEventHub->startOnDeleteEvent_ = []() {};
    listItemEventHub->endOnDeleteEvent_ = []() {};
    frameNode->eventHub_ = listItemEventHub;
    GestureEvent info;
    info.inputEventType_ = InputEventType::AXIS;
    info.sourceTool_ = SourceTool::AIRBRUSH;
    listItemPattern->isDragging_ = true;
    listItemPattern->HandleDragEnd(info);
    EXPECT_TRUE(listPattern->canReplaceSwiperItem_);
    EXPECT_FALSE(listItemPattern->isDragging_);
}

/**
 * @tc.name: ExpandSwipeAction001
 * @tc.desc: Test ListItemPattern ExpandSwipeAction
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, ExpandSwipeAction001, TestSize.Level1)
{
    RefPtr<ListItemPattern> listItemPattern = AceType::MakeRefPtr<ListItemPattern>(nullptr, V2::ListItemStyle::NONE);
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto listItem = FrameNode::CreateFrameNode(
        V2::LIST_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), listItemPattern);
    ASSERT_NE(listItem, nullptr);
    auto list =
        FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), listPattern);
    ASSERT_NE(list, nullptr);
    listItem->MountToParent(list);
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    listItem->SetActive(true);
    listItemPattern->axis_ = Axis::VERTICAL;
    listItemPattern->springMotion_ = AceType::MakeRefPtr<SpringMotion>(.0f, .0f, .0f, nullptr);
    listItemPattern->springController_ = CREATE_ANIMATOR(MockPipelineContext::GetCurrentContext());
    listItemPattern->SetStartNode(CreateSwipeNode());
    listItemPattern->SetEndNode(CreateSwipeNode());
    auto layoutProperty = listItem->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(1.0f), CalcLength(1.0f)));
    /**
     * @tc.desc: ListItem isn't on tree.
     */
    ListItemModelNG::ExpandSwipeAction(AceType::RawPtr(listItem), ListItemSwipeActionDirection::START);
    pipelineContext->FlushUITaskWithSingleDirtyNode(listItem);
    EXPECT_EQ(listItemPattern->swiperIndex_, ListItemSwipeIndex::ITEM_CHILD);
    ListItemModelNG::ExpandSwipeAction(AceType::RawPtr(listItem), ListItemSwipeActionDirection::END);
    pipelineContext->FlushUITaskWithSingleDirtyNode(listItem);
    EXPECT_EQ(listItemPattern->swiperIndex_, ListItemSwipeIndex::ITEM_CHILD);
    /**
     * @tc.desc: ListItem is on tree.
     */
    listItem->onMainTree_ = true;
    ListItemModelNG::ExpandSwipeAction(AceType::RawPtr(listItem), ListItemSwipeActionDirection::START);
    pipelineContext->FlushUITaskWithSingleDirtyNode(listItem);
    EXPECT_EQ(listItemPattern->swiperIndex_, ListItemSwipeIndex::SWIPER_START);
    ListItemModelNG::ExpandSwipeAction(AceType::RawPtr(listItem), ListItemSwipeActionDirection::END);
    pipelineContext->FlushUITaskWithSingleDirtyNode(listItem);
    EXPECT_EQ(listItemPattern->swiperIndex_, ListItemSwipeIndex::SWIPER_END);
    ListItemModelNG::ExpandSwipeAction(AceType::RawPtr(listItem), ListItemSwipeActionDirection::END);
    pipelineContext->FlushUITaskWithSingleDirtyNode(listItem);
    EXPECT_EQ(listItemPattern->swiperIndex_, ListItemSwipeIndex::SWIPER_END);
}

/**
 * @tc.name: ExpandSwipeAction002
 * @tc.desc: Test ListItemPattern ExpandSwipeAction
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, ExpandSwipeAction002, TestSize.Level1)
{
    RefPtr<ListItemPattern> listItemPattern = AceType::MakeRefPtr<ListItemPattern>(nullptr, V2::ListItemStyle::NONE);
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto listItem = FrameNode::CreateFrameNode(
        V2::LIST_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), listItemPattern);
    ASSERT_NE(listItem, nullptr);
    auto list =
        FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), listPattern);
    ASSERT_NE(list, nullptr);
    listItem->MountToParent(list);
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    listItemPattern->axis_ = Axis::VERTICAL;
    listItem->onMainTree_ = true;
    listItem->SetActive(true);
    ListItemModelNG::ExpandSwipeAction(AceType::RawPtr(listItem), ListItemSwipeActionDirection::START);
    pipelineContext->FlushUITaskWithSingleDirtyNode(listItem);
    EXPECT_EQ(listItemPattern->swiperIndex_, ListItemSwipeIndex::ITEM_CHILD);

    listItemPattern->SetStartNode(CreateSwipeNode());
    listItemPattern->SetEndNode(CreateSwipeNode());
    /**
     * @tc.desc: The goal direction has no size.
     */
    listItemPattern->startNodeSize_ = .0f;
    ListItemModelNG::ExpandSwipeAction(AceType::RawPtr(listItem), ListItemSwipeActionDirection::END);
    pipelineContext->FlushUITaskWithSingleDirtyNode(listItem);
    EXPECT_EQ(listItemPattern->swiperIndex_, ListItemSwipeIndex::SWIPER_END);
    /**
     * @tc.desc: The target direction already has a size.
     */
    listItemPattern->endNodeSize_ = 1.0f;
    ListItemModelNG::ExpandSwipeAction(AceType::RawPtr(listItem), ListItemSwipeActionDirection::START);
    pipelineContext->FlushUITaskWithSingleDirtyNode(listItem);
    EXPECT_EQ(listItemPattern->swiperIndex_, ListItemSwipeIndex::SWIPER_START);
}

/**
 * @tc.name: ExpandSwipeAction003
 * @tc.desc: Test ListItemPattern ExpandSwipeAction
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, ExpandSwipeAction003, TestSize.Level1)
{
    RefPtr<ListItemPattern> listItemPattern = AceType::MakeRefPtr<ListItemPattern>(nullptr, V2::ListItemStyle::NONE);
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto listItem = FrameNode::CreateFrameNode(
        V2::LIST_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), listItemPattern);
    ASSERT_NE(listItem, nullptr);
    auto list =
        FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), listPattern);
    ASSERT_NE(list, nullptr);
    listItem->MountToParent(list);
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    listItem->SetActive(true);
    listItemPattern->axis_ = Axis::VERTICAL;
    listItemPattern->springMotion_ = AceType::MakeRefPtr<SpringMotion>(.0f, .0f, .0f, nullptr);
    listItemPattern->springController_ = CREATE_ANIMATOR(MockPipelineContext::GetCurrentContext());
    listItemPattern->SetStartNode(CreateSwipeNode());
    auto layoutProperty = listItem->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(1.0f), CalcLength(1.0f)));
    listItem->onMainTree_ = true;
    ListItemModelNG::ExpandSwipeAction(AceType::RawPtr(listItem), ListItemSwipeActionDirection::END);
    pipelineContext->FlushUITaskWithSingleDirtyNode(listItem);
    EXPECT_EQ(listItemPattern->swiperIndex_, ListItemSwipeIndex::ITEM_CHILD);
    ListItemModelNG::ExpandSwipeAction(AceType::RawPtr(listItem), ListItemSwipeActionDirection::START);
    pipelineContext->FlushUITaskWithSingleDirtyNode(listItem);
    EXPECT_EQ(listItemPattern->swiperIndex_, ListItemSwipeIndex::SWIPER_START);
}

/**
 * @tc.name: ExpandSwipeAction004
 * @tc.desc: Test ListItemPattern ExpandSwipeAction
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, ExpandSwipeAction004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List an ListItem.
     */
    RefPtr<ListItemPattern> listItemPattern = AceType::MakeRefPtr<ListItemPattern>(nullptr, V2::ListItemStyle::NONE);
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto listItem = FrameNode::CreateFrameNode(
        V2::LIST_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), listItemPattern);
    ASSERT_NE(listItem, nullptr);
    auto list =
        FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), listPattern);
    ASSERT_NE(list, nullptr);
    listItem->MountToParent(list);
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    listItem->SetActive(true);
    listItemPattern->axis_ = Axis::VERTICAL;
    listItemPattern->springMotion_ = AceType::MakeRefPtr<SpringMotion>(.0f, .0f, .0f, nullptr);
    listItemPattern->springController_ = CREATE_ANIMATOR(MockPipelineContext::GetCurrentContext());
    listItemPattern->SetStartNode(CreateSwipeNode());
    listItemPattern->SetEndNode(CreateSwipeNode());
    auto layoutProperty = listItem->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(1.0f), CalcLength(1.0f)));
    listItem->onMainTree_ = true;

    /**
     * @tc.steps: step2. Expand swipe action with start direction.
     * @tc.expected: The start node will be layout.
     */
    ListItemModelNG::ExpandSwipeAction(AceType::RawPtr(listItem), ListItemSwipeActionDirection::END);
    pipelineContext->FlushUITaskWithSingleDirtyNode(listItem);
    EXPECT_EQ(listItemPattern->swiperIndex_, ListItemSwipeIndex::SWIPER_END);
    auto endNode = AceType::DynamicCast<FrameNode>(listItem->GetChildAtIndex(listItemPattern->endNodeIndex_));
    ASSERT_NE(endNode, nullptr);
    EXPECT_TRUE(endNode->IsLayoutComplete());

    /**
     * @tc.steps: step3. Expand swipe action with end direction.
     * @tc.expected: The end node will be layout.
     */
    ListItemModelNG::ExpandSwipeAction(AceType::RawPtr(listItem), ListItemSwipeActionDirection::START);
    pipelineContext->FlushUITaskWithSingleDirtyNode(listItem);
    EXPECT_EQ(listItemPattern->swiperIndex_, ListItemSwipeIndex::SWIPER_START);
    auto startNode = AceType::DynamicCast<FrameNode>(listItem->GetChildAtIndex(listItemPattern->startNodeIndex_));
    ASSERT_NE(startNode, nullptr);
    EXPECT_TRUE(startNode->IsLayoutComplete());
}

/**
 * @tc.name: CollapseSwipeAction001
 * @tc.desc: Test ListItemPattern CollapseSwipeAction
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, CollapseSwipeAction001, TestSize.Level1)
{
    /**
     * @tc.desc: Create ListItem node.
     */
    RefPtr<ListItemPattern> listItemPattern = AceType::MakeRefPtr<ListItemPattern>(nullptr, V2::ListItemStyle::NONE);
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto listItem = FrameNode::CreateFrameNode(
        V2::LIST_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), listItemPattern);
    ASSERT_NE(listItem, nullptr);
    auto list =
        FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), listPattern);
    ASSERT_NE(list, nullptr);
    listItem->MountToParent(list);
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    listItem->SetActive(true);
    listItemPattern->axis_ = Axis::VERTICAL;
    listItemPattern->springMotion_ = AceType::MakeRefPtr<SpringMotion>(.0f, .0f, .0f, nullptr);
    listItemPattern->springController_ = CREATE_ANIMATOR(MockPipelineContext::GetCurrentContext());
    listItemPattern->SetStartNode(CreateSwipeNode());
    listItemPattern->SetEndNode(CreateSwipeNode());
    /**
     * @tc.desc: ListItem is on tree.
     */
    listItem->onMainTree_ = true;
    ListItemModelNG::ExpandSwipeAction(AceType::RawPtr(listItem), ListItemSwipeActionDirection::START);
    pipelineContext->FlushUITaskWithSingleDirtyNode(listItem);
    EXPECT_EQ(listItemPattern->swiperIndex_, ListItemSwipeIndex::SWIPER_START);
    ListItemModelNG::CollapseSwipeAction(AceType::RawPtr(listItem));
    EXPECT_EQ(listItemPattern->swiperIndex_, ListItemSwipeIndex::ITEM_CHILD);

    ListItemModelNG::ExpandSwipeAction(AceType::RawPtr(listItem), ListItemSwipeActionDirection::END);
    pipelineContext->FlushUITaskWithSingleDirtyNode(listItem);
    EXPECT_EQ(listItemPattern->swiperIndex_, ListItemSwipeIndex::SWIPER_END);
    ListItemModelNG::CollapseSwipeAction(AceType::RawPtr(listItem));
    EXPECT_EQ(listItemPattern->swiperIndex_, ListItemSwipeIndex::ITEM_CHILD);
}

/**
 * @tc.name: OnThemeScopeUpdate009
 * @tc.desc: Test ListItemPattern OnThemeScopeUpdate: Verify FocusPaintParams is set
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, OnThemeScopeUpdate009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with CARD style ListItem
     */
    CreateList();
    CreateListItems(1, V2::ListItemStyle::CARD);
    CreateDone();

    /**
     * @tc.steps: step2. Get ListItem node and components
     */
    auto listItem = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(listItem, nullptr);

    auto pattern = listItem->GetPattern<ListItemPattern>();
    ASSERT_NE(pattern, nullptr);

    auto focusHub = listItem->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);

    /**
     * @tc.steps: step3. Set theme focus colors
     */
    auto listItemTheme = MockPipelineContext::pipeline_->GetTheme<ListItemTheme>();
    auto originalBorderColor = listItemTheme->focusBorderColor_;
    auto originalBorderWidth = listItemTheme->focusBorderWidth_;
    listItemTheme->focusBorderColor_ = Color::RED;
    listItemTheme->focusBorderWidth_ = Dimension(5.0, DimensionUnit::VP);

    /**
     * @tc.steps: step4. Set API version to VERSION_TWENTY_SIX and call OnThemeScopeUpdate
     * @tc.expected: FocusPaintParams is set with theme colors
     */
    auto oriApiVersion = listItem->apiVersion_;
    listItem->apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX);
    pattern->OnThemeScopeUpdate(0);

    EXPECT_TRUE(focusHub->HasPaintColor());
    EXPECT_EQ(focusHub->GetPaintColor(), Color::RED);
    EXPECT_TRUE(focusHub->HasPaintWidth());
    EXPECT_EQ(focusHub->GetPaintWidth(), Dimension(5.0, DimensionUnit::VP));

    // Restore
    listItem->apiVersion_ = oriApiVersion;
    listItemTheme->focusBorderColor_ = originalBorderColor;
    listItemTheme->focusBorderWidth_ = originalBorderWidth;
}

/**
 * @tc.name: OnThemeScopeUpdate010
 * @tc.desc: Test ListItemPattern OnThemeScopeUpdate: HasStateStyle(SELECTED)=true, BlendBgColor not called
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, OnThemeScopeUpdate010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with CARD style ListItem
     */
    CreateList();
    CreateListItems(1, V2::ListItemStyle::CARD);
    CreateDone();

    /**
     * @tc.steps: step2. Get ListItem node and components
     */
    auto listItem = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(listItem, nullptr);

    auto pattern = listItem->GetPattern<ListItemPattern>();
    ASSERT_NE(pattern, nullptr);

    auto eventHub = listItem->GetEventHub<ListItemEventHub>();
    ASSERT_NE(eventHub, nullptr);

    auto renderContext = listItem->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    /**
     * @tc.steps: step3. Set SELECTED state
     */
    eventHub->AddSupportedState(UI_STATE_SELECTED);
    eventHub->MarkModifyDone();
    eventHub->UpdateCurrentUIState(UI_STATE_SELECTED);

    /**
     * @tc.steps: step4. Set theme color
     */
    auto listItemTheme = MockPipelineContext::pipeline_->GetTheme<ListItemTheme>();
    auto originalDefaultColor = listItemTheme->itemDefaultColor_;
    listItemTheme->itemDefaultColor_ = Color::BLUE;

    /**
     * @tc.steps: step5. Set API version to VERSION_TWENTY_SIX and call OnThemeScopeUpdate
     * @tc.expected: Background color equals theme default color, BlendBgColor not called
     */
    auto oriApiVersion = listItem->apiVersion_;
    listItem->apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX);
    pattern->OnThemeScopeUpdate(0);

    auto bgColor = renderContext->GetBackgroundColor();
    EXPECT_TRUE(bgColor.has_value());
    EXPECT_EQ(bgColor.value(), Color::BLUE);
    EXPECT_TRUE(eventHub->HasStateStyle(UI_STATE_SELECTED));

    // Restore
    listItem->apiVersion_ = oriApiVersion;
    listItemTheme->itemDefaultColor_ = originalDefaultColor;
}

/**
 * @tc.name: OnThemeScopeUpdate011
 * @tc.desc: Test ListItemPattern OnThemeScopeUpdate: HasStateStyle(SELECTED)=false, BlendBgColor called
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, OnThemeScopeUpdate011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with CARD style ListItem
     */
    CreateList();
    CreateListItems(1, V2::ListItemStyle::CARD);
    CreateDone();

    /**
     * @tc.steps: step2. Get ListItem node and components
     */
    auto listItem = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(listItem, nullptr);

    auto pattern = listItem->GetPattern<ListItemPattern>();
    ASSERT_NE(pattern, nullptr);

    auto eventHub = listItem->GetEventHub<ListItemEventHub>();
    ASSERT_NE(eventHub, nullptr);

    auto renderContext = listItem->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    /**
     * @tc.steps: step3. Set isSelected_ = true (not SELECTED state support)
     */
    pattern->isSelected_ = true;

    /**
     * @tc.steps: step4. Set theme colors
     */
    auto listItemTheme = MockPipelineContext::pipeline_->GetTheme<ListItemTheme>();
    auto originalDefaultColor = listItemTheme->itemDefaultColor_;
    auto originalSelectedColor = listItemTheme->selectedColor_;
    auto originalSelectedColorWithAlpha = listItemTheme->selectedColorWithAlpha_;
    listItemTheme->itemDefaultColor_ = Color(0xFF0000FF); // BLUE
    listItemTheme->selectedColor_ = Color(0x8000FF00); // GREEN (50% alpha)
    listItemTheme->selectedColorWithAlpha_ = Color(0x8000FF00); // GREEN (50% alpha)

    /**
     * @tc.steps: step5. Set API version to VERSION_TWENTY_SIX and call OnThemeScopeUpdate
     * @tc.expected: BlendBgColor is called, background color is blended
     */
    auto oriApiVersion = listItem->apiVersion_;
    listItem->apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX);
    pattern->OnThemeScopeUpdate(0);

    auto bgColor = renderContext->GetBackgroundColor();
    EXPECT_TRUE(bgColor.has_value());
    EXPECT_FALSE(eventHub->HasStateStyle(UI_STATE_SELECTED));

    // Restore
    listItem->apiVersion_ = oriApiVersion;
    listItemTheme->itemDefaultColor_ = originalDefaultColor;
    listItemTheme->selectedColor_ = originalSelectedColor;
    listItemTheme->selectedColorWithAlpha_ = originalSelectedColorWithAlpha;
    pattern->isSelected_ = false;
}

/**
 * @tc.name: OnThemeScopeUpdate012
 * @tc.desc: Test ListItemPattern OnThemeScopeUpdate: User set bg + HasStateStyle=false, BlendBgColor called
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, OnThemeScopeUpdate012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with CARD style ListItem
     */
    CreateList();
    CreateListItems(1, V2::ListItemStyle::CARD);
    CreateDone();

    /**
     * @tc.steps: step2. Get ListItem node and components
     */
    auto listItem = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(listItem, nullptr);

    auto pattern = listItem->GetPattern<ListItemPattern>();
    ASSERT_NE(pattern, nullptr);

    auto eventHub = listItem->GetEventHub<ListItemEventHub>();
    ASSERT_NE(eventHub, nullptr);

    auto renderContext = listItem->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    auto layoutProperty = listItem->GetLayoutProperty<ListItemLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step3. User sets background color
     */
    renderContext->UpdateBackgroundColor(Color::BLUE);
    layoutProperty->UpdateIsUserSetBackgroundColor(true);

    /**
     * @tc.steps: step4. Set isSelected_ = true
     */
    pattern->isSelected_ = true;

    /**
     * @tc.steps: step5. Set theme color
     */
    auto listItemTheme = MockPipelineContext::pipeline_->GetTheme<ListItemTheme>();
    auto originalSelectedColor = listItemTheme->selectedColor_;
    auto originalSelectedColorWithAlpha = listItemTheme->selectedColorWithAlpha_;
    listItemTheme->selectedColor_ = Color(0x80FF0000); // RED (50% alpha)
    listItemTheme->selectedColorWithAlpha_ = Color(0x80FF0000); // RED (50% alpha)

    /**
     * @tc.steps: step6. Set API version to VERSION_TWENTY_SIX and call OnThemeScopeUpdate
     * @tc.expected: User set BLUE is preserved and blended with RED
     */
    auto oriApiVersion = listItem->apiVersion_;
    listItem->apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX);
    pattern->OnThemeScopeUpdate(0);

    auto bgColor = renderContext->GetBackgroundColor();
    EXPECT_TRUE(bgColor.has_value());
    EXPECT_FALSE(eventHub->HasStateStyle(UI_STATE_SELECTED));

    // Restore
    listItem->apiVersion_ = oriApiVersion;
    listItemTheme->selectedColor_ = originalSelectedColor;
    listItemTheme->selectedColorWithAlpha_ = originalSelectedColorWithAlpha;
    pattern->isSelected_ = false;
    layoutProperty->UpdateIsUserSetBackgroundColor(false);
}

/**
 * @tc.name: OnThemeScopeUpdate013
 * @tc.desc: Test ListItemPattern OnThemeScopeUpdate: User set bg + HasStateStyle=true, BlendBgColor not called
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, OnThemeScopeUpdate013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with CARD style ListItem
     */
    CreateList();
    CreateListItems(1, V2::ListItemStyle::CARD);
    CreateDone();

    /**
     * @tc.steps: step2. Get ListItem node and components
     */
    auto listItem = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(listItem, nullptr);

    auto pattern = listItem->GetPattern<ListItemPattern>();
    ASSERT_NE(pattern, nullptr);

    auto eventHub = listItem->GetEventHub<ListItemEventHub>();
    ASSERT_NE(eventHub, nullptr);

    auto renderContext = listItem->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    auto layoutProperty = listItem->GetLayoutProperty<ListItemLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step3. User sets background color
     */
    renderContext->UpdateBackgroundColor(Color::GREEN);
    layoutProperty->UpdateIsUserSetBackgroundColor(true);

    /**
     * @tc.steps: step4. Set SELECTED state
     */
    eventHub->AddSupportedState(UI_STATE_SELECTED);
    eventHub->MarkModifyDone();
    eventHub->UpdateCurrentUIState(UI_STATE_SELECTED);

    /**
     * @tc.steps: step5. Set API version to VERSION_TWENTY_SIX and call OnThemeScopeUpdate
     * @tc.expected: User set GREEN is preserved, BlendBgColor not called
     */
    auto oriApiVersion = listItem->apiVersion_;
    listItem->apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX);
    pattern->OnThemeScopeUpdate(0);

    auto bgColor = renderContext->GetBackgroundColor();
    EXPECT_TRUE(bgColor.has_value());
    EXPECT_EQ(bgColor.value(), Color::GREEN);
    EXPECT_TRUE(eventHub->HasStateStyle(UI_STATE_SELECTED));

    // Restore
    listItem->apiVersion_ = oriApiVersion;
    layoutProperty->UpdateIsUserSetBackgroundColor(false);
}
} // namespace OHOS::Ace::NG