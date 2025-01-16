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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_LIST_LIST_TEST_NG_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_LIST_LIST_TEST_NG_H

#include "test/unittest/core/pattern/scrollable/scrollable_utils_test_ng.h"
#define private public
#define protected public
#include "core/components_ng/pattern/list/list_item_group_model_ng.h"
#include "core/components_ng/pattern/list/list_item_model_ng.h"
#include "core/components_ng/pattern/list/list_model_ng.h"
#include "core/components_ng/pattern/list/list_pattern.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
constexpr float LIST_WIDTH = 240.f;
constexpr float LIST_HEIGHT = 400.f;
constexpr float ITEM_MAIN_SIZE = 100.f;
constexpr float CONTENT_MAIN_SIZE = 1000.f;
constexpr int32_t TOTAL_ITEM_NUMBER = CONTENT_MAIN_SIZE / ITEM_MAIN_SIZE;
constexpr float VERTICAL_SCROLLABLE_DISTANCE = CONTENT_MAIN_SIZE - LIST_HEIGHT;
constexpr float HORIZONTAL_SCROLLABLE_DISTANCE = CONTENT_MAIN_SIZE - LIST_WIDTH;
constexpr int32_t GROUP_NUMBER = 4;
constexpr int32_t GROUP_ITEM_NUMBER = 2;
constexpr float GROUP_HEADER_LEN = 50.f;
constexpr float START_NODE_LEN = 80.f;
constexpr float END_NODE_LEN = 100.f;
constexpr float DELETE_AREA_DISTANCE = 50.f;
constexpr Dimension GROUP_MARGIN = 12.0_vp;
constexpr float DEFAULT_STIFFNESS = 228;
constexpr float DEFAULT_DAMPING = 30;
constexpr float SWIPER_SPEED_TH = 1500.f;
constexpr float SWIPER_TH = 0.25f;
constexpr int32_t DEFAULT_LANES = 1;
constexpr int32_t DEFAULT_SPACE = 0;
constexpr float SPACE = 10.f;
constexpr float STROKE_WIDTH = 5.f;
const V2::ItemDivider ITEM_DIVIDER = { Dimension(STROKE_WIDTH), Dimension(10), Dimension(20), Color(0x000000) };
constexpr int32_t HEADER_INDEX = 0;
constexpr int32_t FOOTER_INDEX = 1;
const Color ITEM_DEFAULT_COLOR = Color::WHITE;
const Color HOVER_COLOR = Color::RED;
const Color PRESS_COLOR = Color::BLACK;
constexpr double DISABLED_ALPHA = 0.4;
constexpr int32_t TICK = 2;

class ListTestNg : public ScrollableUtilsTestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    static RefPtr<FrameNode> CreateCustomNode(const std::string& tag, float crossSize, float mainSize);
    void SetUp() override;
    void TearDown() override;
    void GetList();
    ListModelNG CreateList();
    ListItemModelNG CreateListItem(V2::ListItemStyle listItemStyle = V2::ListItemStyle::NONE);
    void CreateListItems(
        int32_t itemNumber = TOTAL_ITEM_NUMBER, V2::ListItemStyle listItemStyle = V2::ListItemStyle::NONE);
    void AddItems(int32_t itemNumber, V2::ListItemStyle listItemStyle = V2::ListItemStyle::NONE);
    ListItemGroupModelNG CreateListItemGroup(V2::ListItemGroupStyle listItemGroupStyle = V2::ListItemGroupStyle::NONE);
    void CreateListItemGroups(int32_t groupNumber,
        V2::ListItemGroupStyle listItemGroupStyle = V2::ListItemGroupStyle::NONE,
        int32_t itemNumber = GROUP_ITEM_NUMBER);
    void CreateItemWithSize(int32_t itemNumber, SizeT<Dimension> itemSize);
    void CreateGroupChildrenMainSize(int32_t groupNumber);
    void CreateGroupWithItem(int32_t groupNumber, Axis axis = Axis::VERTICAL);
    void CreateGroupWithSetting(
        int32_t groupNumber, V2::ListItemGroupStyle listItemGroupStyle, int32_t itemNumber = GROUP_ITEM_NUMBER);
    void CreateGroupWithSettingWithComponentContent(
        int32_t groupNumber, V2::ListItemGroupStyle listItemGroupStyle, int32_t itemNumber = GROUP_ITEM_NUMBER);
    void CreateGroupWithSettingChildrenMainSize(int32_t groupNumber);
    void CreateRepeatVirtualScrollNode(int32_t itemNumber, const std::function<void(uint32_t)>& createFunc);
    std::function<void()> GetRowOrColBuilder(float crossSize, float mainSize);
    std::function<void()> GetRowOrColBuilder(Dimension crossSize, Dimension mainSize);
    void CreateSwipeItemsWithComponentContent(const RefPtr<NG::UINode>& startBuilderNode,
        const RefPtr<NG::UINode>& endBuilderNode, V2::SwipeEdgeEffect effect, int32_t itemNumber = TOTAL_ITEM_NUMBER);

    void UpdateCurrentOffset(float offset, int32_t source = SCROLL_FROM_UPDATE);
    void FlushIdleTask(const RefPtr<ListPattern>& listPattern);
    void SetChildrenMainSize(
        const RefPtr<FrameNode>& frameNode, int32_t startIndex, const std::vector<float>& newChildrenSize);
    AssertionResult Position(const RefPtr<FrameNode>& frameNode, float expectOffset) override;
    AssertionResult Position(float expectOffset) override;
    void JumpToItemInGroup(int32_t index, int32_t indexInGroup, bool smooth, ScrollAlign align);
    void CreateItemsInLazyForEach(
        int32_t itemNumber, float itemMainSize, std::function<void(int32_t, int32_t)> onMove = nullptr);
    void CreateItemGroupsInLazyForEach(int32_t itemNumber, std::function<void(int32_t, int32_t)> onMove = nullptr);

    RefPtr<ListPattern> pattern_;
    RefPtr<ListEventHub> eventHub_;
    RefPtr<ListLayoutProperty> layoutProperty_;
    RefPtr<ScrollablePaintProperty> paintProperty_;
    RefPtr<ListAccessibilityProperty> accessibilityProperty_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_LIST_LIST_TEST_NG_H
