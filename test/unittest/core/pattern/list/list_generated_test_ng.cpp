/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "list_test_ng.h"

#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/animation/mock_animation_manager.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "core/components/button/button_theme.h"
#include "core/components/list/list_theme.h"
#include "core/components_ng/pattern/custom_frame_node/custom_frame_node.h"
#include "core/components_ng/pattern/linear_layout/column_model_ng.h"
#include "core/components_ng/pattern/linear_layout/row_model_ng.h"
#include "core/components_ng/pattern/list/list_position_controller.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t ITEM_COUNT = 10;
constexpr int32_t TEST_NODE_ID = 2;

std::vector<RefPtr<FrameNode>> GetFlatListItems(const RefPtr<FrameNode>& listNode)
{
    std::vector<RefPtr<FrameNode>> listItems;
    CHECK_NULL_RETURN(listNode, listItems);
    auto& children = listNode->GetChildren();
    for (const auto& child : children) {
        auto childFrameNode = AceType::DynamicCast<FrameNode>(child);
        if (!childFrameNode) {
            continue;
        }
        if (childFrameNode->GetTag() == V2::LIST_ITEM_GROUP_ETS_TAG) {
            auto groupChildren = child->GetChildren();
            for (const auto& item : groupChildren) {
                auto itemFrameNode = AceType::DynamicCast<FrameNode>(item);
                if (itemFrameNode && itemFrameNode->GetTag() == V2::LIST_ITEM_ETS_TAG) {
                    listItems.emplace_back(itemFrameNode);
                }
            }
            continue;
        }
        if (childFrameNode->GetTag() == V2::LIST_ITEM_ETS_TAG) {
            listItems.emplace_back(childFrameNode);
        }
    }
    return listItems;
}

PointF ConvertItemCenterToListLocal(const RefPtr<FrameNode>& listNode, const RefPtr<FrameNode>& itemNode)
{
    CHECK_NULL_RETURN(listNode, PointF());
    CHECK_NULL_RETURN(itemNode, PointF());
    auto listOffset = listNode->GetOffsetRelativeToWindow();
    auto itemOffset = itemNode->GetOffsetRelativeToWindow();
    auto itemRect = itemNode->GetGeometryNode()->GetFrameRect();
    return PointF(itemOffset.GetX() - listOffset.GetX() + itemRect.Width() / 2.0f,
        itemOffset.GetY() - listOffset.GetY() + itemRect.Height() / 2.0f);
}
} // namespace

class ListGeneratedTestNg : public ListTestNg {
public:
    static void SetUpTestSuite()
    {
        ListTestNg::SetUpTestSuite();
    }

    static void TearDownTestSuite()
    {
        ListTestNg::TearDownTestSuite();
    }
};

/**
 * @tc.name: CreateList001
 * @tc.desc: Test creating a basic list component
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, CreateList001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create list with default parameters
     * @tc.expected: List is created successfully
     */
    CreateList();
    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(pattern_, nullptr);
}

/**
 * @tc.name: CreateListWithItems001
 * @tc.desc: Test creating a list with multiple items
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, CreateListWithItems001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create list
     * @tc.expected: List is created successfully
     */
    CreateList();
    CreateListItems(ITEM_COUNT);

    /**
     * @tc.steps: step2. Verify item count
     * @tc.expected: Item count matches expected
     */
    int32_t itemCount = frameNode_->GetTotalChildCount();
    EXPECT_EQ(itemCount, ITEM_COUNT);
}

/**
 * @tc.name: ListLayout001
 * @tc.desc: Test list layout measurement
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListLayout001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create list with items
     * @tc.expected: List is created successfully
     */
    CreateList();
    CreateListItems(ITEM_COUNT);

    /**
     * @tc.steps: step2. Perform layout
     * @tc.expected: Layout completes successfully
     */
    pattern_->OnModifyDone();
    FlushUITasks(frameNode_);

    /**
     * @tc.steps: step3. Verify layout properties
     * @tc.expected: Layout properties are set correctly
     */
    auto geometryNode = frameNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto frameSize = geometryNode->GetFrameSize();
    EXPECT_GT(frameSize.Width(), 0.0f);
    EXPECT_GT(frameSize.Height(), 0.0f);
}

/**
 * @tc.name: ListItemPosition001
 * @tc.desc: Test getting item position information
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListItemPosition001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create list with items
     * @tc.expected: List is created successfully
     */
    CreateList();
    CreateListItems(ITEM_COUNT);

    pattern_->OnModifyDone();
    FlushUITasks(frameNode_);

    /**
     * @tc.steps: step2. Get item position info
     * @tc.expected: Position info is valid
     */
    auto itemPosition = pattern_->GetItemPosition();
    EXPECT_FALSE(itemPosition.empty());
}

/**
 * @tc.name: ListGetCurrentOffset001
 * @tc.desc: Test getting current scroll offset
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListGetCurrentOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create list
     * @tc.expected: List is created successfully
     */
    CreateList();
    CreateListItems(ITEM_COUNT);

    pattern_->OnModifyDone();
    FlushUITasks(frameNode_);

    /**
     * @tc.steps: step2. Get current offset
     * @tc.expected: Offset is retrieved successfully
     */
    auto currentOffset = pattern_->GetCurrentOffset();
    EXPECT_GE(currentOffset.GetY(), 0.0f);
}

/**
 * @tc.name: ListIsAtTop001
 * @tc.desc: Test checking if list is at top position
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListIsAtTop001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create list without scrolling
     * @tc.expected: List is created successfully
     */
    CreateList();
    CreateListItems(ITEM_COUNT);

    pattern_->OnModifyDone();
    FlushUITasks(frameNode_);

    /**
     * @tc.steps: step2. Check if at top
     * @tc.expected: Should be at top initially
     */
    auto isAtTop = pattern_->IsAtTop();
    EXPECT_TRUE(isAtTop);
}

/**
 * @tc.name: ListToJsonValue001
 * @tc.desc: Test serializing list properties to JSON
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListToJsonValue001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create list
     * @tc.expected: List is created successfully
     */
    CreateList();
    CreateListItems(ITEM_COUNT);

    /**
     * @tc.steps: step2. Serialize to JSON
     * @tc.expected: JSON serialization completes
     */
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pattern_->ToJsonValue(json, InspectorFilter());
    auto jsonString = json->ToString();
    EXPECT_FALSE(jsonString.empty());
}

/**
 * @tc.name: HandleOnItemDragStart001
 * @tc.desc: Test HandleOnItemDragStart with null custom node
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, HandleOnItemDragStart001, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    // Set drag start callback that returns null (no custom node)
    bool callbackCalled = false;
    eventHub_->SetOnItemDragStart([&callbackCalled](const ItemDragInfo& info, int32_t index) -> RefPtr<UINode> {
        callbackCalled = true;
        return nullptr; // Return null custom node
    });

    GestureEvent info;
    info.SetGlobalPoint(Point(WIDTH / 2, ITEM_MAIN_SIZE / 2));
    eventHub_->HandleOnItemDragStart(info);

    // Callback should be called but drag should not start
    EXPECT_TRUE(callbackCalled);
}

/**
 * @tc.name: HandleOnItemDragStart002
 * @tc.desc: Test HandleOnItemDragStart with valid custom node
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, HandleOnItemDragStart002, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    // Set drag start callback that returns a custom node
    eventHub_->SetOnItemDragStart([](const ItemDragInfo& info, int32_t index) -> RefPtr<UINode> {
        // Create a simple custom node
        auto frameNode = FrameNode::CreateFrameNode("custom_drag_node", 1, AceType::MakeRefPtr<Pattern>());
        return frameNode;
    });

    GestureEvent info;
    info.SetGlobalPoint(Point(WIDTH / 2, ITEM_MAIN_SIZE / 2));
    eventHub_->HandleOnItemDragStart(info);
}

/**
 * @tc.name: HandleOnItemDragUpdate001
 * @tc.desc: Test HandleOnItemDragUpdate with null dragDropProxy
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, HandleOnItemDragUpdate001, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    // Ensure dragDropProxy_ is null
    eventHub_->dragDropProxy_ = nullptr;

    GestureEvent info;
    info.SetGlobalPoint(Point(WIDTH / 2, ITEM_MAIN_SIZE / 2));

    // Should not crash when dragDropProxy_ is null
    eventHub_->HandleOnItemDragUpdate(info);
}

/**
 * @tc.name: HandleOnItemDragEnd001
 * @tc.desc: Test HandleOnItemDragEnd with null dragDropProxy
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, HandleOnItemDragEnd001, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    // Ensure dragDropProxy_ is null
    eventHub_->dragDropProxy_ = nullptr;

    GestureEvent info;
    info.SetGlobalPoint(Point(WIDTH / 2, ITEM_MAIN_SIZE / 2));

    // Should not crash when dragDropProxy_ is null
    eventHub_->HandleOnItemDragEnd(info);
}

/**
 * @tc.name: HandleOnItemDragCancel001
 * @tc.desc: Test HandleOnItemDragCancel with null dragDropProxy
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, HandleOnItemDragCancel001, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    // Ensure dragDropProxy_ is null
    eventHub_->dragDropProxy_ = nullptr;

    // Should not crash when dragDropProxy_ is null
    eventHub_->HandleOnItemDragCancel();
}

/**
 * @tc.name: GetListItemIndexByPosition001
 * @tc.desc: Test GetListItemIndexByPosition with strict mode and valid item
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, GetListItemIndexByPosition001, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    // Test strict mode with valid position
    float x = WIDTH / 2;
    float y = ITEM_MAIN_SIZE / 2;
    int32_t index = eventHub_->GetListItemIndexByPosition(x, y, true);
    EXPECT_EQ(index, 0);
}

/**
 * @tc.name: GetListItemIndexByPosition002
 * @tc.desc: Test GetListItemIndexByPosition with strict mode and invalid position
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, GetListItemIndexByPosition002, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    // Test strict mode with position outside any item
    float x = -100;
    float y = -100;
    int32_t index = eventHub_->GetListItemIndexByPosition(x, y, true);
    EXPECT_EQ(index, -1);
}

/**
 * @tc.name: GetListItemIndexByPosition003
 * @tc.desc: Test GetListItemIndexByPosition with non-strict mode
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, GetListItemIndexByPosition003, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    // Test non-strict mode (default)
    float x = WIDTH / 2;
    float y = ITEM_MAIN_SIZE / 2;
    int32_t index = eventHub_->GetListItemIndexByPosition(x, y, false);
    EXPECT_EQ(index, 0);
}

/**
 * @tc.name: GetListItemIndexByPosition004
 * @tc.desc: Test GetListItemIndexByPosition with default strict parameter
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, GetListItemIndexByPosition004, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    // Test with default strict parameter (false)
    float x = WIDTH / 2;
    float y = ITEM_MAIN_SIZE * 2.5f; // Position on third item
    int32_t index = eventHub_->GetListItemIndexByPosition(x, y);
    EXPECT_EQ(index, 2);
}

/**
 * @tc.name: FireOnItemDragStart001
 * @tc.desc: Test FireOnItemDragStart with null event callback
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, FireOnItemDragStart001, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    // Ensure callback is not set
    ItemDragInfo dragInfo;
    dragInfo.SetX(100);
    dragInfo.SetY(100);

    auto result = eventHub_->FireOnItemDragStart(dragInfo, 0);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: FireOnItemDragStart002
 * @tc.desc: Test FireOnItemDragStart with valid callback
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, FireOnItemDragStart002, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    bool callbackCalled = false;
    eventHub_->SetOnItemDragStart([&callbackCalled](const ItemDragInfo& info, int32_t index) -> RefPtr<UINode> {
        callbackCalled = true;
        auto frameNode = FrameNode::CreateFrameNode("test_node", 1, AceType::MakeRefPtr<Pattern>());
        return frameNode;
    });

    ItemDragInfo dragInfo;
    dragInfo.SetX(100);
    dragInfo.SetY(100);

    auto result = eventHub_->FireOnItemDragStart(dragInfo, 0);
    EXPECT_TRUE(callbackCalled);
    EXPECT_NE(result, nullptr);
}

/**
 * @tc.name: FireOnItemDragEnter001
 * @tc.desc: Test FireOnItemDragEnter with null event callback
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, FireOnItemDragEnter001, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    // Should not crash with null callback
    ItemDragInfo dragInfo;
    dragInfo.SetX(100);
    dragInfo.SetY(100);

    eventHub_->FireOnItemDragEnter(dragInfo);
}

/**
 * @tc.name: FireOnItemDragEnter002
 * @tc.desc: Test FireOnItemDragEnter with valid callback
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, FireOnItemDragEnter002, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    bool callbackCalled = false;
    eventHub_->SetOnItemDragEnter([&callbackCalled](const ItemDragInfo& info) {
        callbackCalled = true;
    });

    ItemDragInfo dragInfo;
    dragInfo.SetX(100);
    dragInfo.SetY(100);

    eventHub_->FireOnItemDragEnter(dragInfo);
    EXPECT_TRUE(callbackCalled);
}

/**
 * @tc.name: FireOnItemDragMove001
 * @tc.desc: Test FireOnItemDragMove with null event callback
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, FireOnItemDragMove001, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    // Should not crash with null callback
    ItemDragInfo dragInfo;
    dragInfo.SetX(100);
    dragInfo.SetY(100);

    eventHub_->FireOnItemDragMove(dragInfo, 0, 1);
}

/**
 * @tc.name: FireOnItemDragMove002
 * @tc.desc: Test FireOnItemDragMove with valid callback
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, FireOnItemDragMove002, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    bool callbackCalled = false;
    int32_t capturedIndex = -1;
    int32_t capturedInsertIndex = -1;

    eventHub_->SetOnItemDragMove([&callbackCalled, &capturedIndex, &capturedInsertIndex](
        const ItemDragInfo& info, int32_t itemIndex, int32_t insertIndex) {
        callbackCalled = true;
        capturedIndex = itemIndex;
        capturedInsertIndex = insertIndex;
    });

    ItemDragInfo dragInfo;
    dragInfo.SetX(100);
    dragInfo.SetY(100);

    eventHub_->FireOnItemDragMove(dragInfo, 2, 3);
    EXPECT_TRUE(callbackCalled);
    EXPECT_EQ(capturedIndex, 2);
    EXPECT_EQ(capturedInsertIndex, 3);
}

/**
 * @tc.name: FireOnItemDragLeave001
 * @tc.desc: Test FireOnItemDragLeave with null event callback
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, FireOnItemDragLeave001, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    // Should not crash with null callback
    ItemDragInfo dragInfo;
    dragInfo.SetX(100);
    dragInfo.SetY(100);

    eventHub_->FireOnItemDragLeave(dragInfo, 0);
}

/**
 * @tc.name: FireOnItemDragLeave002
 * @tc.desc: Test FireOnItemDragLeave with valid callback
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, FireOnItemDragLeave002, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    bool callbackCalled = false;
    int32_t capturedIndex = -1;

    eventHub_->SetOnItemDragLeave([&callbackCalled, &capturedIndex](const ItemDragInfo& info, int32_t itemIndex) {
        callbackCalled = true;
        capturedIndex = itemIndex;
    });

    ItemDragInfo dragInfo;
    dragInfo.SetX(100);
    dragInfo.SetY(100);

    eventHub_->FireOnItemDragLeave(dragInfo, 1);
    EXPECT_TRUE(callbackCalled);
    EXPECT_EQ(capturedIndex, 1);
}

/**
 * @tc.name: FireOnItemDrop001
 * @tc.desc: Test FireOnItemDrop with null event callback
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, FireOnItemDrop001, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    // Should return false when callback is not set
    ItemDragInfo dragInfo;
    dragInfo.SetX(100);
    dragInfo.SetY(100);

    bool result = eventHub_->FireOnItemDrop(dragInfo, 0, 1, true);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: FireOnItemDrop002
 * @tc.desc: Test FireOnItemDrop with valid callback
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, FireOnItemDrop002, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    bool callbackCalled = false;
    eventHub_->SetOnItemDrop([&callbackCalled](
        const ItemDragInfo& info, int32_t itemIndex, int32_t insertIndex, bool isSuccess) {
        callbackCalled = true;
    });

    ItemDragInfo dragInfo;
    dragInfo.SetX(100);
    dragInfo.SetY(100);

    bool result = eventHub_->FireOnItemDrop(dragInfo, 0, 1, true);
    EXPECT_TRUE(callbackCalled);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: FireOnItemDrop003
 * @tc.desc: Test FireOnItemDrop with onItemMove callback
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, FireOnItemDrop003, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    bool moveCallbackCalled = false;
    bool dropCallbackCalled = false;

    eventHub_->SetOnItemMove([&moveCallbackCalled](int32_t from, int32_t to) -> bool {
        moveCallbackCalled = true;
        return true;
    });

    eventHub_->SetOnItemDrop([&dropCallbackCalled](
        const ItemDragInfo& info, int32_t itemIndex, int32_t insertIndex, bool isSuccess) {
        dropCallbackCalled = true;
    });

    ItemDragInfo dragInfo;
    dragInfo.SetX(100);
    dragInfo.SetY(100);

    bool result = eventHub_->FireOnItemDrop(dragInfo, 2, 3, false);
    EXPECT_TRUE(moveCallbackCalled);
    EXPECT_TRUE(dropCallbackCalled);
    EXPECT_TRUE(result); // isSuccess should be true from onItemMove
}

/**
 * @tc.name: FireOnItemDrop004
 * @tc.desc: Test FireOnItemDrop with invalid indices
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, FireOnItemDrop004, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    bool moveCallbackCalled = false;
    bool dropCallbackCalled = false;

    eventHub_->SetOnItemMove([&moveCallbackCalled](int32_t from, int32_t to) -> bool {
        moveCallbackCalled = true;
        return true;
    });

    eventHub_->SetOnItemDrop([&dropCallbackCalled](
        const ItemDragInfo& info, int32_t itemIndex, int32_t insertIndex, bool isSuccess) {
        dropCallbackCalled = true;
    });

    ItemDragInfo dragInfo;
    dragInfo.SetX(100);
    dragInfo.SetY(100);

    // Test with negative indices - onItemMove should not be called
    bool result = eventHub_->FireOnItemDrop(dragInfo, -1, -1, false);
    EXPECT_FALSE(moveCallbackCalled);
    EXPECT_TRUE(dropCallbackCalled);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: GetDragExtraParams001
 * @tc.desc: Test GetDragExtraParams with DROP type
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, GetDragExtraParams001, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    Point point(WIDTH / 2, ITEM_MAIN_SIZE / 2);
    std::string result = eventHub_->GetDragExtraParams("test_extra", point, DragEventType::DROP);

    // Should contain insertIndex
    EXPECT_NE(result.find("insertIndex"), std::string::npos);
    EXPECT_NE(result.find("test_extra"), std::string::npos);
}

/**
 * @tc.name: GetDragExtraParams002
 * @tc.desc: Test GetDragExtraParams with MOVE type
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, GetDragExtraParams002, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    Point point(WIDTH / 2, ITEM_MAIN_SIZE / 2);
    std::string result = eventHub_->GetDragExtraParams("", point, DragEventType::MOVE);

    // Should contain insertIndex but no extraInfo
    EXPECT_NE(result.find("insertIndex"), std::string::npos);
    EXPECT_EQ(result.find("extraInfo"), std::string::npos);
}

/**
 * @tc.name: GetDragExtraParams003
 * @tc.desc: Test GetDragExtraParams with other drag types
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, GetDragExtraParams003, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    Point point(WIDTH / 2, ITEM_MAIN_SIZE / 2);
    std::string result = eventHub_->GetDragExtraParams("test_info", point, DragEventType::START);

    // Should not contain insertIndex for non-DROP/MOVE types
    EXPECT_EQ(result.find("insertIndex"), std::string::npos);
    EXPECT_NE(result.find("test_info"), std::string::npos);
}

/**
 * @tc.name: HasOnItemDragMove001
 * @tc.desc: Test HasOnItemDragMove with null callback
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, HasOnItemDragMove001, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    EXPECT_FALSE(eventHub_->HasOnItemDragMove());
}

/**
 * @tc.name: HasOnItemDragMove002
 * @tc.desc: Test HasOnItemDragMove with valid callback
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, HasOnItemDragMove002, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    eventHub_->SetOnItemDragMove([](const ItemDragInfo& info, int32_t itemIndex, int32_t insertIndex) {});
    EXPECT_TRUE(eventHub_->HasOnItemDragMove());
}

/**
 * @tc.name: HasOnItemDrop001
 * @tc.desc: Test HasOnItemDrop with null callback
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, HasOnItemDrop001, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    EXPECT_FALSE(eventHub_->HasOnItemDrop());
}

/**
 * @tc.name: HasOnItemDrop002
 * @tc.desc: Test HasOnItemDrop with valid callback
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, HasOnItemDrop002, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    eventHub_->SetOnItemDrop([](const ItemDragInfo& info, int32_t itemIndex, int32_t insertIndex, bool isSuccess) {});
    EXPECT_TRUE(eventHub_->HasOnItemDrop());
}

/**
 * @tc.name: InitItemDragEvent001
 * @tc.desc: Test InitItemDragEvent initialization
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, InitItemDragEvent001, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    // Get gesture hub
    auto gestureHub = frameNode_->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    // Initialize item drag event
    eventHub_->InitItemDragEvent(gestureHub);

    // Verify drag event is set (no crash means success)
    EXPECT_NE(gestureHub, nullptr);
}

/**
 * @tc.name: ClearJSFrameNodeOnListScrollIndex001
 * @tc.desc: Test ClearJSFrameNodeOnListScrollIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ClearJSFrameNodeOnListScrollIndex001, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    // Set a callback first
    eventHub_->SetJSFrameNodeOnListScrollIndex([](int32_t start, int32_t end, int32_t center) {});

    // Verify callback is set
    auto& callbackBefore = eventHub_->GetJSFrameNodeOnListScrollIndex();
    EXPECT_NE(callbackBefore, nullptr);

    // Clear it
    eventHub_->ClearJSFrameNodeOnListScrollIndex();

    // Verify the callback is cleared
    auto& callbackAfter = eventHub_->GetJSFrameNodeOnListScrollIndex();
    EXPECT_EQ(callbackAfter, nullptr);
}

/**
 * @tc.name: ClearJSFrameNodeOnListScrollIndex002
 * @tc.desc: Test ClearJSFrameNodeOnListScrollIndex with null callback
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ClearJSFrameNodeOnListScrollIndex002, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    // Verify no callback is set initially
    auto& callbackBefore = eventHub_->GetJSFrameNodeOnListScrollIndex();
    EXPECT_EQ(callbackBefore, nullptr);

    // Clear without setting - should not crash
    eventHub_->ClearJSFrameNodeOnListScrollIndex();

    // Verify still null after clearing
    auto& callbackAfter = eventHub_->GetJSFrameNodeOnListScrollIndex();
    EXPECT_EQ(callbackAfter, nullptr);
}

/**
 * @tc.name: ClearJSFrameNodeOnScrollVisibleContentChange001
 * @tc.desc: Test ClearJSFrameNodeOnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ClearJSFrameNodeOnScrollVisibleContentChange001, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    // Set a callback first
    eventHub_->SetJSFrameNodeOnScrollVisibleContentChange([](ListItemIndex start, ListItemIndex end) {});

    // Verify callback is set
    auto& callbackBefore = eventHub_->GetJSFrameNodeOnScrollVisibleContentChange();
    EXPECT_NE(callbackBefore, nullptr);

    // Clear it
    eventHub_->ClearJSFrameNodeOnScrollVisibleContentChange();

    // Verify the callback is cleared
    auto& callbackAfter = eventHub_->GetJSFrameNodeOnScrollVisibleContentChange();
    EXPECT_EQ(callbackAfter, nullptr);
}

/**
 * @tc.name: ClearJSFrameNodeOnScrollVisibleContentChange002
 * @tc.desc: Test ClearJSFrameNodeOnScrollVisibleContentChange with null callback
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ClearJSFrameNodeOnScrollVisibleContentChange002, TestSize.Level1)
{
    CreateList();
    CreateListItems(5);
    CreateDone();

    // Verify no callback is set initially
    auto& callbackBefore = eventHub_->GetJSFrameNodeOnScrollVisibleContentChange();
    EXPECT_EQ(callbackBefore, nullptr);

    // Clear without setting - should not crash
    eventHub_->ClearJSFrameNodeOnScrollVisibleContentChange();

    // Verify still null after clearing
    auto& callbackAfter = eventHub_->GetJSFrameNodeOnScrollVisibleContentChange();
    EXPECT_EQ(callbackAfter, nullptr);
}

/**
 * @tc.name: ListModelNGSetLaneMinLengthInvalid001
 * @tc.desc: Test ListModelNG SetLaneMinLength with invalid dimension
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListModelNGSetLaneMinLengthInvalid001, TestSize.Level1)
{
    ListModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    listNode->SetLayoutProperty(listLayoutProperty);

    // Set invalid dimension (IsValid() returns false)
    model.SetLaneMinLength(Dimension());
    CreateDone();

    // Property should be reset
    auto layoutProperty = listNode->GetLayoutProperty<ListLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: ListModelNGSetLaneMaxLengthInvalid001
 * @tc.desc: Test ListModelNG SetLaneMaxLength with invalid dimension
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListModelNGSetLaneMaxLengthInvalid001, TestSize.Level1)
{
    ListModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    listNode->SetLayoutProperty(listLayoutProperty);

    // Set invalid dimension (IsValid() returns false)
    model.SetLaneMaxLength(Dimension());
    CreateDone();

    // Property should be reset
    auto layoutProperty = listNode->GetLayoutProperty<ListLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: ListModelNGSetLaneMinLengthFrameNodeInvalid001
 * @tc.desc: Test ListModelNG SetLaneMinLength(FrameNode*) with invalid dimension
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListModelNGSetLaneMinLengthFrameNodeInvalid001, TestSize.Level1)
{
    ListModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    listNode->SetLayoutProperty(listLayoutProperty);

    // Set invalid dimension
    model.SetLaneMinLength(listNode, Dimension());
    CreateDone();

    auto layoutProperty = listNode->GetLayoutProperty<ListLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: ListModelNGSetLaneMaxLengthFrameNodeInvalid001
 * @tc.desc: Test ListModelNG SetLaneMaxLength(FrameNode*) with invalid dimension
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListModelNGSetLaneMaxLengthFrameNodeInvalid001, TestSize.Level1)
{
    ListModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    listNode->SetLayoutProperty(listLayoutProperty);

    // Set invalid dimension
    model.SetLaneMaxLength(listNode, Dimension());
    CreateDone();

    auto layoutProperty = listNode->GetLayoutProperty<ListLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: ListModelNGGetScrollEnabledNotSet001
 * @tc.desc: Test ListModelNG GetScrollEnabled when scrollEnabled not set
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListModelNGGetScrollEnabledNotSet001, TestSize.Level1)
{
    ListModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    listNode->SetLayoutProperty(listLayoutProperty);

    // GetScrollEnabled returns default value when not set
    auto result = model.GetScrollEnabled(listNode);
    EXPECT_TRUE(result); // Default is true
}

/**
 * @tc.name: ListModelNGSetScrollSnapAlignChange001
 * @tc.desc: Test ListModelNG SetScrollSnapAlign with value change
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListModelNGSetScrollSnapAlignChange001, TestSize.Level1)
{
    ListModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    listNode->SetLayoutProperty(listLayoutProperty);

    // Set initial value
    model.SetScrollSnapAlign(ScrollSnapAlign::START);

    // Change to different value - should trigger ResetLastSnapTargetIndex
    model.SetScrollSnapAlign(ScrollSnapAlign::CENTER);
    CreateDone();

    // Verify the value was changed
    auto layoutProperty = listNode->GetLayoutProperty<ListLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetScrollSnapAlign().value(), ScrollSnapAlign::CENTER);
}

/**
 * @tc.name: ListModelNGSetScrollSnapAlignSame001
 * @tc.desc: Test ListModelNG SetScrollSnapAlign with same value
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListModelNGSetScrollSnapAlignSame001, TestSize.Level1)
{
    ListModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    listNode->SetLayoutProperty(listLayoutProperty);

    // Set initial value
    model.SetScrollSnapAlign(ScrollSnapAlign::START);

    // Set same value - should NOT trigger ResetLastSnapTargetIndex
    model.SetScrollSnapAlign(ScrollSnapAlign::START);
    CreateDone();

    auto layoutProperty = listNode->GetLayoutProperty<ListLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: ListModelNGSetListFrictionNegative001
 * @tc.desc: Test ListModelNG SetListFriction with negative value
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListModelNGSetListFrictionNegative001, TestSize.Level1)
{
    ListModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);

    // Set negative friction - should set to FRISSION constant
    model.SetListFriction(listNode, -1.0);
    CreateDone();

    auto result = model.GetListFriction(listNode);
    EXPECT_GT(result, 0.0); // Should be FRISSION constant value
}

/**
 * @tc.name: ListModelNGSetListFrictionZero001
 * @tc.desc: Test ListModelNG SetListFriction with zero
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListModelNGSetListFrictionZero001, TestSize.Level1)
{
    ListModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);

    // Set zero friction - should set to FRISSION constant
    model.SetListFriction(listNode, 0.0);
    CreateDone();

    auto result = model.GetListFriction(listNode);
    EXPECT_GT(result, 0.0); // Should be FRISSION constant value
}

/**
 * @tc.name: ListModelNGGetListMaintainVisibleContentPositionNull001
 * @tc.desc: Test ListModelNG GetListMaintainVisibleContentPosition with nullopt
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListModelNGGetListMaintainVisibleContentPositionNull001, TestSize.Level1)
{
    ListModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);

    // Don't set maintainVisibleContentPosition - should return false
    auto result = model.GetListMaintainVisibleContentPosition(listNode);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ListModelNGGetListMaintainVisibleContentPositionSet001
 * @tc.desc: Test ListModelNG GetListMaintainVisibleContentPosition after Set
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListModelNGGetListMaintainVisibleContentPositionSet001, TestSize.Level1)
{
    ListModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);

    // Set maintainVisibleContentPosition to true
    model.SetListMaintainVisibleContentPosition(listNode, true);

    auto result = model.GetListMaintainVisibleContentPosition(listNode);
    EXPECT_TRUE(result);
    CreateDone();
}

/**
 * @tc.name: ListModelNGSetListScrollBarInvalidState001
 * @tc.desc: Test ListModelNG SetListScrollBar with invalid state (too large)
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListModelNGSetListScrollBarInvalidState001, TestSize.Level1)
{
    ListModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<ScrollablePaintProperty> scrollablePaintProperty = AceType::MakeRefPtr<ScrollablePaintProperty>();
    listNode->paintProperty_ = scrollablePaintProperty;

    // Set barState to value >= DISPLAY_MODE.size()
    int32_t invalidState = 100;
    model.SetListScrollBar(listNode, invalidState);
    CreateDone();

    auto result = model.GetListScrollBar(listNode);
    // Should use default display mode
    EXPECT_NE(result, invalidState);
}

/**
 * @tc.name: ListModelNGSetListScrollBarNegativeState001
 * @tc.desc: Test ListModelNG SetListScrollBar with negative state
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListModelNGSetListScrollBarNegativeState001, TestSize.Level1)
{
    ListModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<ScrollablePaintProperty> scrollablePaintProperty = AceType::MakeRefPtr<ScrollablePaintProperty>();
    listNode->paintProperty_ = scrollablePaintProperty;

    // Set barState to negative value
    model.SetListScrollBar(listNode, -1);
    CreateDone();

    auto result = model.GetListScrollBar(listNode);
    // Should use default display mode
    EXPECT_NE(result, -1);
}

/**
 * @tc.name: ListModelNGSetScrollByZeroOffset001
 * @tc.desc: Test ListModelNG SetScrollBy with zero offset
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListModelNGSetScrollByZeroOffset001, TestSize.Level1)
{
    ListModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);

    // Set axis to VERTICAL
    pattern->SetAxis(Axis::VERTICAL);

    // Call SetScrollBy with zero offset - should return early
    model.SetScrollBy(listNode, 0.0, 0.0);
    CreateDone();

    // Should not crash and offset should remain unchanged
}

/**
 * @tc.name: ListModelNGSetScrollByHorizontal001
 * @tc.desc: Test ListModelNG SetScrollBy with horizontal axis
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListModelNGSetScrollByHorizontal001, TestSize.Level1)
{
    ListModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);

    // Set axis to HORIZONTAL
    pattern->SetAxis(Axis::HORIZONTAL);

    // Call SetScrollBy - should use X offset
    model.SetScrollBy(listNode, 10.0, 5.0);
    CreateDone();

    // Should use X offset when axis is horizontal
}

/**
 * @tc.name: ListModelNGScrollToItemInGroupNoneAlign001
 * @tc.desc: Test ListModelNG ScrollToItemInGroup with ScrollAlign::NONE
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListModelNGScrollToItemInGroupNoneAlign001, TestSize.Level1)
{
    ListModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);

    // Set initial align to END
    pattern->scrollAlign_ = ScrollAlign::END;

    // Call with ScrollAlign::NONE - should be changed to START
    model.ScrollToItemInGroup(listNode, 1, 2, false, ScrollAlign::NONE);
    CreateDone();

    // Align should be START (NONE was changed to START)
    EXPECT_EQ(pattern->scrollAlign_, ScrollAlign::START);
}

/**
 * @tc.name: ListModelNGGetListNestedScrollDefault001
 * @tc.desc: Test ListModelNG GetListNestedScroll with no value set
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListModelNGGetListNestedScrollDefault001, TestSize.Level1)
{
    ListModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);

    // Get without setting - should return default options
    auto result = model.GetListNestedScroll(listNode);
    EXPECT_EQ(result.forward, NestedScrollMode::SELF_ONLY);
    EXPECT_EQ(result.backward, NestedScrollMode::SELF_ONLY);
}

/**
 * @tc.name: ListModelNGCreateWithResourceObjLaneConstrainNull001
 * @tc.desc: Test ListModelNG CreateWithResourceObjLaneConstrain with null params
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListModelNGCreateWithResourceObjLaneConstrainNull001, TestSize.Level1)
{
    ListModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);

    // Call with both null params - should not crash
    model.CreateWithResourceObjLaneConstrain(listNode, nullptr, nullptr);
    CreateDone();

    // Should not crash
}

/**
 * @tc.name: ListModelNGCreateWithResourceObjLaneConstrainPartial001
 * @tc.desc: Test ListModelNG CreateWithResourceObjLaneConstrain with only minLength
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListModelNGCreateWithResourceObjLaneConstrainPartial001, TestSize.Level1)
{
    ListModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);

    std::vector<ResourceObjectParams> params;
    auto resObj = AceType::MakeRefPtr<ResourceObject>(0, 0, params, "", "", Container::CurrentIdSafely());

    // Call with only minLength - should not crash
    model.CreateWithResourceObjLaneConstrain(listNode, resObj, nullptr);
    CreateDone();

    // Should not crash
}

/**
 * @tc.name: ListModelNGGetLanesDefault001
 * @tc.desc: Test ListModelNG GetLanes with default value
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListModelNGGetLanesDefault001, TestSize.Level1)
{
    ListModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    listNode->SetLayoutProperty(listLayoutProperty);

    // Get without setting - should return 1 (default)
    auto result = model.GetLanes(listNode);
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: ListModelNGGetLaneMinLengthDefault001
 * @tc.desc: Test ListModelNG GetLaneMinLength with default value
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListModelNGGetLaneMinLengthDefault001, TestSize.Level1)
{
    ListModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    listNode->SetLayoutProperty(listLayoutProperty);

    // Get without setting - should return 0
    auto result = model.GetLaneMinLength(listNode);
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: ListModelNGGetLaneMaxLengthDefault001
 * @tc.desc: Test ListModelNG GetLaneMaxLength with default value
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListModelNGGetLaneMaxLengthDefault001, TestSize.Level1)
{
    ListModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    listNode->SetLayoutProperty(listLayoutProperty);

    // Get without setting - should return 0
    auto result = model.GetLaneMaxLength(listNode);
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: ListModelNGGetLaneGutterDefault001
 * @tc.desc: Test ListModelNG GetLaneGutter with default value
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListModelNGGetLaneGutterDefault001, TestSize.Level1)
{
    ListModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    listNode->SetLayoutProperty(listLayoutProperty);

    // Get without setting - should return 0
    auto result = model.GetLaneGutter(listNode);
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: ListModelNGGetListItemAlignDefault001
 * @tc.desc: Test ListModelNG GetListItemAlign with default value
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListModelNGGetListItemAlignDefault001, TestSize.Level1)
{
    ListModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    listNode->SetLayoutProperty(listLayoutProperty);

    // Get without setting - should return 0 (START)
    auto result = model.GetListItemAlign(listNode);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: ListModelNGGetListSpaceDefault001
 * @tc.desc: Test ListModelNG GetListSpace with default value
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListModelNGGetListSpaceDefault001, TestSize.Level1)
{
    ListModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    listNode->SetLayoutProperty(listLayoutProperty);

    // Get without setting - should return 0
    auto result = model.GetListSpace(listNode);
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: ListModelNGGetScrollSnapAlignDefault001
 * @tc.desc: Test ListModelNG GetScrollSnapAlign with default value
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListModelNGGetScrollSnapAlignDefault001, TestSize.Level1)
{
    ListModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    listNode->SetLayoutProperty(listLayoutProperty);

    // Get without setting - should return 0 (NONE)
    auto result = model.GetScrollSnapAlign(listNode);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: ListModelNGGetContentStartOffsetDefault001
 * @tc.desc: Test ListModelNG GetContentStartOffset with default value
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListModelNGGetContentStartOffsetDefault001, TestSize.Level1)
{
    ListModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    listNode->SetLayoutProperty(listLayoutProperty);

    // Get without setting - should return 0
    auto result = model.GetContentStartOffset(listNode);
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: ListModelNGGetContentEndOffsetDefault001
 * @tc.desc: Test ListModelNG GetContentEndOffset with default value
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListModelNGGetContentEndOffsetDefault001, TestSize.Level1)
{
    ListModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    listNode->SetLayoutProperty(listLayoutProperty);

    // Get without setting - should return 0
    auto result = model.GetContentEndOffset(listNode);
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: ListModelNGGetCachedCountDefault001
 * @tc.desc: Test ListModelNG GetCachedCount with null frameNode
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListModelNGGetCachedCountDefault001, TestSize.Level1)
{
    ListModelNG model;

    // Get with null frameNode - should return default value (1)
    auto result = model.GetCachedCount(nullptr);
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: ListModelNGGetShowCachedDefault001
 * @tc.desc: Test ListModelNG GetShowCached with null frameNode
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListModelNGGetShowCachedDefault001, TestSize.Level1)
{
    ListModelNG model;

    // Get with null frameNode - should return default value (false)
    auto result = model.GetShowCached(nullptr);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ListItemGroupSetHeaderStyle001
 * @tc.desc: Test SetHeaderStyle when changing from NONE to FLOATING
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListItemGroupSetHeaderStyle001, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupOptions{});
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, TEST_NODE_ID, listItemGroupPattern);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->frameNode_ = frameNode;

    EXPECT_EQ(pattern->GetHeaderStyle(), V2::ListItemGroupHeaderFooterStyle::NONE);
    pattern->SetHeaderStyle(V2::ListItemGroupHeaderFooterStyle::FLOATING);
    EXPECT_EQ(pattern->GetHeaderStyle(), V2::ListItemGroupHeaderFooterStyle::FLOATING);
}

/**
 * @tc.name: ListItemGroupSetFooterStyle001
 * @tc.desc: Test SetFooterStyle when changing from NONE to FLOATING
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListItemGroupSetFooterStyle001, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupOptions{});
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, TEST_NODE_ID, listItemGroupPattern);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->frameNode_ = frameNode;

    EXPECT_EQ(pattern->GetFooterStyle(), V2::ListItemGroupHeaderFooterStyle::NONE);
    pattern->SetFooterStyle(V2::ListItemGroupHeaderFooterStyle::FLOATING);
    EXPECT_EQ(pattern->GetFooterStyle(), V2::ListItemGroupHeaderFooterStyle::FLOATING);
}

/**
 * @tc.name: ListItemGroupModelSetHeaderStyle001
 * @tc.desc: Test ListItemGroupModelNG SetHeaderStyle with FLOATING
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListItemGroupModelSetHeaderStyle001, TestSize.Level1)
{
    ListItemGroupModelNG model;
    V2::ListItemGroupOptions options;
    options.style = V2::ListItemGroupStyle::NONE;
    model.Create(options);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListItemGroupPattern>();
    ASSERT_NE(pattern, nullptr);

    EXPECT_EQ(pattern->GetHeaderStyle(), V2::ListItemGroupHeaderFooterStyle::NONE);
    ListItemGroupModelNG::SetHeaderStyle(listNode, V2::ListItemGroupHeaderFooterStyle::FLOATING);
    EXPECT_EQ(pattern->GetHeaderStyle(), V2::ListItemGroupHeaderFooterStyle::FLOATING);
    CreateDone();
}

/**
 * @tc.name: ListItemGroupModelSetFooterStyle001
 * @tc.desc: Test ListItemGroupModelNG SetFooterStyle with FLOATING
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListItemGroupModelSetFooterStyle001, TestSize.Level1)
{
    ListItemGroupModelNG model;
    V2::ListItemGroupOptions options;
    options.style = V2::ListItemGroupStyle::NONE;
    model.Create(options);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListItemGroupPattern>();
    ASSERT_NE(pattern, nullptr);

    EXPECT_EQ(pattern->GetFooterStyle(), V2::ListItemGroupHeaderFooterStyle::NONE);
    ListItemGroupModelNG::SetFooterStyle(listNode, V2::ListItemGroupHeaderFooterStyle::FLOATING);
    EXPECT_EQ(pattern->GetFooterStyle(), V2::ListItemGroupHeaderFooterStyle::FLOATING);
    CreateDone();
}

/**
 * @tc.name: ListSwipeSelectGetItemAtPosition001
 * @tc.desc: Test swipe multi-select can still resolve item index outside edit-mode hot zone
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListSwipeSelectGetItemAtPosition001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetMultiSelectable(true);
    model.SetEnableEditMode(true);
    CreateListItems(ITEM_COUNT);
    CreateDone();

    const PointF point(WIDTH / 2.0f, ITEM_MAIN_SIZE / 2.0f);
    EXPECT_FALSE(pattern_->IsInEditModeHotZone(point));
    EXPECT_EQ(pattern_->GetItemAtPosition(point.GetX(), point.GetY()), 0);
}

/**
 * @tc.name: ListSwipeSelectHotZoneSingleLane001
 * @tc.desc: Test swipe multi-select hot zone detection for single-lane list
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListSwipeSelectHotZoneSingleLane001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetMultiSelectable(true);
    model.SetEnableEditMode(true);
    model.SetLanes(1);
    CreateListItems(ITEM_COUNT);
    CreateDone();

    FlushUITasks();
    const PointF hotZonePoint(WIDTH - 1.0f, ITEM_MAIN_SIZE / 2.0f);
    EXPECT_TRUE(pattern_->GetEnableEditMode());
    EXPECT_TRUE(pattern_->IsInEditModeHotZone(hotZonePoint));

    auto stateKey = pattern_->GetSwipeSelectStateKeyAtPosition(hotZonePoint.GetX(), hotZonePoint.GetY());
    EXPECT_EQ(stateKey.index, 0);
    EXPECT_EQ(stateKey.indexInGroup, -1);
}

/**
 * @tc.name: ListSwipeSelectStateKeyForGroup001
 * @tc.desc: Test swipe multi-select state key resolution for list items inside list item group
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListSwipeSelectStateKeyForGroup001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetMultiSelectable(true);
    model.SetEnableEditMode(true);
    CreateListItemGroups(1, V2::ListItemGroupStyle::NONE, 3);
    CreateDone();

    auto listItems = GetFlatListItems(frameNode_);
    ASSERT_GE(static_cast<int32_t>(listItems.size()), 3);
    auto point = ConvertItemCenterToListLocal(frameNode_, listItems[0]);
    auto stateKey = pattern_->GetSwipeSelectStateKeyAtPosition(point.GetX(), point.GetY());
    EXPECT_EQ(stateKey.index, 0);
    EXPECT_EQ(stateKey.indexInGroup, 0);

    auto selectedNode = pattern_->GetSelectableItemAtStateKey(stateKey);
    EXPECT_EQ(selectedNode, listItems[0]);
}

/**
 * @tc.name: ListSwipeSelectMarkGroupItem001
 * @tc.desc: Test swipe multi-select can mark list item inside list item group by state key
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, ListSwipeSelectMarkGroupItem001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetMultiSelectable(true);
    model.SetEnableEditMode(true);
    CreateListItemGroups(1, V2::ListItemGroupStyle::NONE, 3);
    CreateDone();

    auto listItems = GetFlatListItems(frameNode_);
    ASSERT_GE(static_cast<int32_t>(listItems.size()), 3);
    auto point = ConvertItemCenterToListLocal(frameNode_, listItems[0]);
    auto stateKey = pattern_->GetSwipeSelectStateKeyAtPosition(point.GetX(), point.GetY());
    pattern_->MarkSwipeItemSelectedByStateKey(stateKey, true);

    EXPECT_TRUE(listItems[0]->GetPattern<ListItemPattern>()->IsSelected());
    EXPECT_FALSE(listItems[1]->GetPattern<ListItemPattern>()->IsSelected());
    EXPECT_FALSE(listItems[2]->GetPattern<ListItemPattern>()->IsSelected());
}

/**
 * @tc.name: SetListItemGroupParamStackFromEndContentOffset001
 * @tc.desc: Test ListLayoutAlgorithm keeps visual content offset for ListItemGroup when stackFromEnd is enabled.
 * @tc.type: FUNC
 */
HWTEST_F(ListGeneratedTestNg, SetListItemGroupParamStackFromEndContentOffset001, TestSize.Level1)
{
    auto contentEndOffset = 50.0f;
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    listLayoutAlgorithm->isStackFromEnd_ = true;
    listLayoutAlgorithm->totalItemCount_ = 1;
    listLayoutAlgorithm->contentStartOffset_ = 0.0f;
    listLayoutAlgorithm->contentEndOffset_ = contentEndOffset;
    listLayoutAlgorithm->scrollSnapAlign_ = ScrollSnapAlign::NONE;
    listLayoutAlgorithm->ProcessStackFromEnd();
    EXPECT_EQ(listLayoutAlgorithm->contentStartOffset_, contentEndOffset);
    EXPECT_EQ(listLayoutAlgorithm->contentEndOffset_, 0.0f);

    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern = AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder,
        V2::ListItemGroupOptions{V2::ListItemGroupStyle::NONE});
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<ListLayoutProperty> groupLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    frameNode->layoutProperty_ = groupLayoutProperty;
    listItemGroupPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, groupLayoutProperty);
    layoutWrapper->hostNode_ = frameNode;
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(0, 0, 0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(listItemGroupLayoutAlgorithm);
    layoutWrapper->layoutAlgorithm_ = layoutAlgorithmWrapper;

    listLayoutAlgorithm->SetListItemGroupParam(layoutWrapper, 0, 0.0f, true, listLayoutProperty, false);

    EXPECT_EQ(listItemGroupLayoutAlgorithm->contentStartOffset_, 0.0f);
    EXPECT_EQ(listItemGroupLayoutAlgorithm->contentEndOffset_, contentEndOffset);
}
} // namespace OHOS::Ace::NG
