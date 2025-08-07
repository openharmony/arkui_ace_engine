/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
#include "test/unittest/core/syntax/mock_lazy_for_each_actuator.h"
#include "test/unittest/core/syntax/mock_lazy_for_each_builder.h"
#define private public
#define protected public
#include "core/components_ng/pattern/list/list_item_group_model_ng.h"
#include "core/components_ng/pattern/list/list_item_model_ng.h"
#include "core/components_ng/pattern/list/list_model_ng.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/syntax/for_each_model_ng.h"
#include "core/components_ng/syntax/lazy_for_each_model_ng.h"
#include "test/mock/core/common/mock_resource_adapter_v2.h"
#include "test/mock/base/mock_system_properties.h"
#undef private
#undef protected

namespace OHOS::Ace::NG {
constexpr int32_t TOTAL_ITEM_NUMBER = CONTENT_MAIN_SIZE / ITEM_MAIN_SIZE;
constexpr int32_t GROUP_NUMBER = 4;
constexpr int32_t GROUP_ITEM_NUMBER = 2;
constexpr int32_t EVEN_NUMBER_MOD = 2;
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

class ListItemMockLazy : public Framework::MockLazyForEachBuilder {
public:
    ListItemMockLazy(int32_t itemCnt, float itemMainSize) : itemCnt_(itemCnt), itemMainSize_(itemMainSize) {}

    void SetTotalCount(int32_t count)
    {
        itemCnt_ = count;
    }

protected:
    int32_t OnGetTotalCount() override
    {
        return itemCnt_;
    }

    std::pair<std::string, RefPtr<NG::UINode>> OnGetChildByIndex(
        int32_t index, std::unordered_map<std::string, NG::LazyForEachCacheChild>& expiringItems) override
    {
        ListItemModelNG itemModel;
        itemModel.Create();
        ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
        ViewAbstract::SetHeight(CalcLength(itemMainSize_));
        ViewAbstract::SetFocusable(true);
        auto node = ViewStackProcessor::GetInstance()->Finish();
        return { std::to_string(index), node };
    }

private:
    int32_t itemCnt_ = 0;
    float itemMainSize_ = 100.0f;
};

class ListItemGroupMockLazy : public Framework::MockLazyForEachBuilder {
public:
    explicit ListItemGroupMockLazy(int32_t itemGroupCnt) : itemGroupCnt_(itemGroupCnt) {}

protected:
    int32_t OnGetTotalCount() override
    {
        return itemGroupCnt_;
    }

    std::pair<std::string, RefPtr<NG::UINode>> OnGetChildByIndex(
        int32_t index, std::unordered_map<std::string, NG::LazyForEachCacheChild>& expiringItems) override
    {
        auto listNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
        auto weakList = AceType::WeakClaim(AceType::RawPtr(listNode));
        ListItemGroupModelNG groupModel;
        groupModel.Create(V2::ListItemGroupStyle::NONE);
        auto listItemGroup = ViewStackProcessor::GetInstance()->GetMainElementNode();
        listItemGroup->SetParent(weakList);
        // 2: each ListItemGroup contains 2 items
        for (int32_t index = 0; index < 2; ++index) {
            ListItemModelNG itemModel;
            itemModel.Create();
            ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
            ViewAbstract::SetHeight(CalcLength(100.0f));
            ViewAbstract::SetFocusable(true);
            ViewStackProcessor::GetInstance()->Pop();
        }
        auto groupNode = ViewStackProcessor::GetInstance()->Finish();
        return { std::to_string(index), groupNode };
    }

private:
    int32_t itemGroupCnt_ = 0;
};

class ListTestNg : public ScrollableUtilsTestNG {
protected:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;

    virtual void GetList();
    ListModelNG CreateList();
    RefPtr<FrameNode> CreateList(const std::function<void(ListModelNG)>& callback);
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
    RefPtr<ListItemMockLazy> CreateItemsInLazyForEachWithHandle(
        int32_t itemNumber, float itemMainSize, std::function<void(int32_t, int32_t)> onMove = nullptr);
    static RefPtr<FrameNode> CreateCustomNode(const std::string& tag, float crossSize, float mainSize);
    LazyForEachModelNG CreateItemsInForLazyEachForItemDragEvent(int32_t itemNumber, float itemMainSize);
    ForEachModelNG CreateForEachListForItemDragEvent(int32_t itemNumber, int32_t lanes);
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

    void AddCustomNode();

    RefPtr<ListPattern> pattern_;
    RefPtr<ListEventHub> eventHub_;
    RefPtr<ListLayoutProperty> layoutProperty_;
    std::vector<RefPtr<ListItemGroupPattern>> itemGroupPatters_;
};

class ListItemGroupPatternTestNg : public TestNG {
    void SetUp() override;
    void TearDown() override;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_LIST_LIST_TEST_NG_H
