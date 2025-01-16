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
#undef private
#undef protected

namespace OHOS::Ace::NG {
constexpr int32_t TOTAL_ITEM_NUMBER = CONTENT_MAIN_SIZE / ITEM_MAIN_SIZE;
constexpr int32_t GROUP_NUMBER = 4;
constexpr int32_t GROUP_ITEM_NUMBER = 2;
constexpr float GROUP_HEADER_LEN = 50.f;
constexpr Dimension GROUP_MARGIN = 12.0_vp;
constexpr float DEFAULT_STIFFNESS = 228;
constexpr float DEFAULT_DAMPING = 30;
constexpr float SPACE = 10.f;
constexpr float STROKE_WIDTH = 5.f;
const V2::ItemDivider ITEM_DIVIDER = { Dimension(STROKE_WIDTH), Dimension(10), Dimension(20), Color(0x000000) };
const Color ITEM_DEFAULT_COLOR = Color::WHITE;
const Color HOVER_COLOR = Color::RED;
const Color PRESS_COLOR = Color::BLACK;
constexpr double DISABLED_ALPHA = 0.4;

class ListTestNg : public ScrollableUtilsTestNG {
protected:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;

    virtual void GetList();
    ListModelNG CreateList();
    ListItemModelNG CreateListItem(V2::ListItemStyle listItemStyle = V2::ListItemStyle::NONE);
    void CreateListItems(
        int32_t itemNumber = TOTAL_ITEM_NUMBER, V2::ListItemStyle listItemStyle = V2::ListItemStyle::NONE);
    void CreateItemWithSize(int32_t itemNumber, SizeT<Dimension> itemSize);
    ListItemGroupModelNG CreateListItemGroup(V2::ListItemGroupStyle listItemGroupStyle = V2::ListItemGroupStyle::NONE);
    void CreateListItemGroups(int32_t groupNumber,
        V2::ListItemGroupStyle listItemGroupStyle = V2::ListItemGroupStyle::NONE,
        int32_t itemNumber = GROUP_ITEM_NUMBER);
    void CreateGroupWithSetting(
        int32_t groupNumber, V2::ListItemGroupStyle listItemGroupStyle, int32_t itemNumber = GROUP_ITEM_NUMBER);
    void CreateRepeatVirtualScrollNode(int32_t itemNumber, const std::function<void(uint32_t)>& createFunc);
    void CreateItemsInLazyForEach(
        int32_t itemNumber, float itemMainSize, std::function<void(int32_t, int32_t)> onMove = nullptr);
    void CreateItemGroupsInLazyForEach(int32_t itemNumber, std::function<void(int32_t, int32_t)> onMove = nullptr);
    static RefPtr<FrameNode> CreateCustomNode(const std::string& tag, float crossSize, float mainSize);

    // utils
    std::function<void()> GetRowOrColBuilder(float crossSize, float mainSize);
    std::function<void()> GetRowOrColBuilder(Dimension crossSize, Dimension mainSize);
    void AddListItem(V2::ListItemStyle listItemStyle = V2::ListItemStyle::NONE);
    void UpdateCurrentOffset(float offset, int32_t source = SCROLL_FROM_UPDATE);
    void FlushIdleTask(const RefPtr<ListPattern>& listPattern);
    void SetChildrenMainSize(
        const RefPtr<FrameNode>& frameNode, int32_t startIndex, const std::vector<float>& newChildrenSize);
    void JumpToItemInGroup(int32_t index, int32_t indexInGroup, bool smooth, ScrollAlign align);

    // AssertionResult
    AssertionResult Position(const RefPtr<FrameNode>& frameNode, float expectOffset) override;
    AssertionResult Position(float expectOffset) override;

    RefPtr<ListPattern> pattern_;
    RefPtr<ListEventHub> eventHub_;
    RefPtr<ListLayoutProperty> layoutProperty_;
    RefPtr<ScrollablePaintProperty> paintProperty_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_LIST_LIST_TEST_NG_H
