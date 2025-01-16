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

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/animation/mock_animation_manager.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/syntax/mock_lazy_for_each_builder.h"

#include "core/components/button/button_theme.h"
#include "core/components/list/list_theme.h"
#include "core/components_ng/pattern/linear_layout/column_model_ng.h"
#include "core/components_ng/pattern/linear_layout/row_model_ng.h"
#include "core/components_ng/pattern/list/list_position_controller.h"
#include "core/components_ng/syntax/lazy_for_each_model_ng.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_model_ng.h"

namespace OHOS::Ace::NG {
void ListTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
    MockPipelineContext::GetCurrentContext()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockAnimationManager::Enable(true);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonThemeConstants = CreateThemeConstants(THEME_PATTERN_BUTTON);
    auto buttonTheme = ButtonTheme::Builder().Build(buttonThemeConstants);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));
    auto listThemeConstants = CreateThemeConstants(THEME_PATTERN_LIST);
    auto listTheme = ListTheme::Builder().Build(listThemeConstants);
    EXPECT_CALL(*themeManager, GetTheme(ListTheme::TypeId())).WillRepeatedly(Return(listTheme));
    auto listItemThemeConstants = CreateThemeConstants(THEME_PATTERN_LIST_ITEM);
    auto listItemTheme = ListItemTheme::Builder().Build(listItemThemeConstants);
    EXPECT_CALL(*themeManager, GetTheme(ListItemTheme::TypeId())).WillRepeatedly(Return(listItemTheme));
    listItemTheme->itemDefaultColor_ = ITEM_DEFAULT_COLOR;
    listItemTheme->hoverColor_ = HOVER_COLOR;
    listItemTheme->pressColor_ = PRESS_COLOR;
    listItemTheme->hoverAnimationDuration_ = 250;
    listItemTheme->hoverToPressAnimationDuration_ = 100;
    listItemTheme->disabledAlpha_ = DISABLED_ALPHA;
    listItemTheme->defaultColor_ = Color::WHITE;
    listItemTheme->defaultLeftMargin_ = GROUP_MARGIN;
    listItemTheme->defaultRightMargin_ = GROUP_MARGIN;
    listItemTheme->defaultPadding_ = Edge(0.0_vp);
    auto scrollableThemeConstants = CreateThemeConstants(THEME_PATTERN_SCROLLABLE);
    auto scrollableTheme = ScrollableTheme::Builder().Build(scrollableThemeConstants);
    EXPECT_CALL(*themeManager, GetTheme(ScrollableTheme::TypeId())).WillRepeatedly(Return(scrollableTheme));
}

void ListTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void ListTestNg::SetUp() {}

void ListTestNg::TearDown()
{
    RemoveFromStageNode();
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    paintProperty_ = nullptr;
    positionController_ = nullptr;
    ClearOldNodes(); // Each testCase will create new list at begin
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
    MockAnimationManager::GetInstance().Reset();
}

void ListTestNg::GetList()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<ListPattern>();
    eventHub_ = frameNode_->GetEventHub<ListEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<ListLayoutProperty>();
    paintProperty_ = frameNode_->GetPaintProperty<ScrollablePaintProperty>();
    positionController_ = AceType::DynamicCast<ListPositionController>(pattern_->GetPositionController());
}

ListModelNG ListTestNg::CreateList()
{
    ResetElmtId();
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    ListModelNG model;
    model.Create();
    ViewAbstract::SetWidth(CalcLength(WIDTH));
    ViewAbstract::SetHeight(CalcLength(HEIGHT));
    RefPtr<ScrollControllerBase> scrollController = model.CreateScrollController();
    RefPtr<ScrollProxy> proxy = AceType::MakeRefPtr<NG::ScrollBarProxy>();
    model.SetScroller(scrollController, proxy);
    GetList();
    return model;
}

void ListTestNg::CreateListItems(int32_t itemNumber, V2::ListItemStyle listItemStyle)
{
    for (int32_t index = 0; index < itemNumber; index++) {
        CreateListItem(listItemStyle);
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
}

void ListTestNg::AddListItem(V2::ListItemStyle listItemStyle)
{
    CreateListItem(listItemStyle);
    RefPtr<UINode> currentNode = ViewStackProcessor::GetInstance()->Finish();
    auto currentFrameNode = AceType::DynamicCast<FrameNode>(currentNode);
    currentFrameNode->MountToParent(frameNode_);
}

ListItemModelNG ListTestNg::CreateListItem(V2::ListItemStyle listItemStyle)
{
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    ListItemModelNG itemModel;
    itemModel.Create([](int32_t) {}, listItemStyle);
    Axis axis = layoutProperty_->GetListDirection().value_or(Axis::VERTICAL);
    SetSize(axis, CalcLength(FILL_LENGTH), CalcLength(ITEM_MAIN_SIZE));
    return itemModel;
}

void ListTestNg::CreateListItemGroups(
    int32_t groupNumber, V2::ListItemGroupStyle listItemGroupStyle, int32_t itemNumber)
{
    for (int32_t index = 0; index < groupNumber; index++) {
        CreateListItemGroup(listItemGroupStyle);
        CreateListItems(itemNumber, static_cast<V2::ListItemStyle>(listItemGroupStyle));
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
}

ListItemGroupModelNG ListTestNg::CreateListItemGroup(V2::ListItemGroupStyle listItemGroupStyle)
{
    auto listNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto weakList = AceType::WeakClaim(AceType::RawPtr(listNode));
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    ListItemGroupModelNG groupModel;
    groupModel.Create(listItemGroupStyle);
    auto listItemGroup = ViewStackProcessor::GetInstance()->GetMainElementNode();
    listItemGroup->SetParent(weakList);
    return groupModel;
}

void ListTestNg::CreateItemWithSize(int32_t itemNumber, SizeT<Dimension> itemSize)
{
    for (int32_t index = 0; index < itemNumber; ++index) {
        ListItemModelNG itemModel = CreateListItem();
        ViewAbstract::SetWidth(CalcLength(itemSize.Width()));
        ViewAbstract::SetHeight(CalcLength(itemSize.Height()));
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
}

void ListTestNg::CreateGroupWithSetting(
    int32_t groupNumber, V2::ListItemGroupStyle listItemGroupStyle, int32_t itemNumber)
{
    for (int32_t index = 0; index < groupNumber; index++) {
        auto header = GetRowOrColBuilder(FILL_LENGTH, Dimension(GROUP_HEADER_LEN));
        auto footer = GetRowOrColBuilder(FILL_LENGTH, Dimension(GROUP_HEADER_LEN));
        ListItemGroupModelNG groupModel = CreateListItemGroup(listItemGroupStyle);
        groupModel.SetSpace(Dimension(SPACE));
        groupModel.SetDivider(ITEM_DIVIDER);
        groupModel.SetHeader(std::move(header));
        groupModel.SetFooter(std::move(footer));
        CreateListItems(itemNumber, static_cast<V2::ListItemStyle>(listItemGroupStyle));
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
}

std::function<void()> ListTestNg::GetRowOrColBuilder(float crossSize, float mainSize)
{
    return GetRowOrColBuilder(Dimension(crossSize), Dimension(mainSize));
}

std::function<void()> ListTestNg::GetRowOrColBuilder(Dimension crossSize, Dimension mainSize)
{
    Axis axis = layoutProperty_->GetListDirection().value_or(Axis::VERTICAL);
    return [axis, mainSize, crossSize]() {
        if (axis == Axis::VERTICAL) {
            RowModelNG rowModel;
            rowModel.Create(std::nullopt, nullptr, "");
            ViewAbstract::SetWidth(CalcLength(crossSize));
            ViewAbstract::SetHeight(CalcLength(mainSize));
        } else {
            ColumnModelNG colModel;
            colModel.Create(Dimension(0), nullptr, "");
            ViewAbstract::SetWidth(CalcLength(mainSize));
            ViewAbstract::SetHeight(CalcLength(crossSize));
        }
    };
}

void ListTestNg::UpdateCurrentOffset(float offset, int32_t source)
{
    pattern_->UpdateCurrentOffset(offset, source);
    FlushUITasks();
}

void ListTestNg::CreateRepeatVirtualScrollNode(int32_t itemNumber, const std::function<void(uint32_t)>& createFunc)
{
    RepeatVirtualScrollModelNG repeatModel;
    std::function<void(const std::string&, uint32_t)> updateFunc = [](const std::string& value, uint32_t idx) {};
    std::function<std::list<std::string>(uint32_t, uint32_t)> getKeys = [](uint32_t start, uint32_t end) {
        std::list<std::string> keys;
        for (uint32_t i = start; i <= end; ++i) {
            keys.emplace_back(std::to_string(i));
        }
        return keys;
    };
    std::function<std::list<std::string>(uint32_t, uint32_t)> getTypes = [](uint32_t start, uint32_t end) {
        std::list<std::string> keys;
        for (uint32_t i = start; i <= end; ++i) {
            keys.emplace_back("0");
        }
        return keys;
    };
    std::function<void(uint32_t, uint32_t)> setActiveRange = [](uint32_t start, uint32_t end) {};
    repeatModel.Create(itemNumber, {}, createFunc, updateFunc, getKeys, getTypes, setActiveRange);
}

void ListTestNg::FlushIdleTask(const RefPtr<ListPattern>& listPattern)
{
    int32_t tryCount = 10;
    auto predictParam = listPattern->GetPredictLayoutParamV2();
    while (predictParam && tryCount > 0) {
        const int64_t time = GetSysTimestamp();
        auto pipeline = listPattern->GetContext();
        pipeline->OnIdle(time + 16 * 1000000); // 16 * 1000000: 16ms
        FlushUITasks();
        predictParam = listPattern->GetPredictLayoutParamV2();
        tryCount--;
    }
}

void ListTestNg::SetChildrenMainSize(
    const RefPtr<FrameNode>& frameNode, int32_t startIndex, const std::vector<float>& newChildrenSize)
{
    int32_t size = static_cast<int32_t>(newChildrenSize.size());
    for (int32_t index = 0; index < size; index++) {
        auto child = GetChildFrameNode(frameNode, index + startIndex);
        ViewAbstract::SetHeight(AceType::RawPtr(child), CalcLength(newChildrenSize[index]));
    }
}

RefPtr<FrameNode> ListTestNg::CreateCustomNode(const std::string& tag, float crossSize, float mainSize)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>(
        tag, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto layoutProperty = frameNode->GetLayoutProperty();
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(crossSize), CalcLength(mainSize)));
    return frameNode;
}

AssertionResult ListTestNg::Position(const RefPtr<FrameNode>& frameNode, float expectOffset)
{
    Axis axis = layoutProperty_->GetListDirection().value_or(Axis::VERTICAL);
    if (AceType::InstanceOf<ListItemPattern>(frameNode->GetPattern())) {
        auto pattern = frameNode->GetPattern<ListItemPattern>();
        auto item = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild());
        if (axis == Axis::VERTICAL) {
            return IsEqual(item->GetGeometryNode()->GetFrameRect().GetX(), expectOffset);
        }
        return IsEqual(item->GetGeometryNode()->GetFrameRect().GetY(), expectOffset);
    }
    auto pattern = frameNode->GetPattern<ListPattern>();
    return IsEqual(-(pattern->GetTotalOffset()), expectOffset);
}

AssertionResult ListTestNg::Position(float expectOffset)
{
    return Position(frameNode_, expectOffset);
}

void ListTestNg::JumpToItemInGroup(int32_t index, int32_t indexInGroup, bool smooth, ScrollAlign align)
{
    positionController_->JumpToItemInGroup(index, indexInGroup, smooth, align);
    FlushUITasks();
}

class ListItemMockLazy : public Framework::MockLazyForEachBuilder {
public:
    ListItemMockLazy(int32_t itemCnt, float itemMainSize) : itemCnt_(itemCnt), itemMainSize_(itemMainSize) {}

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

void ListTestNg::CreateItemsInLazyForEach(
    int32_t itemNumber, float itemMainSize, std::function<void(int32_t, int32_t)> onMove)
{
    RefPtr<LazyForEachActuator> mockLazy = AceType::MakeRefPtr<ListItemMockLazy>(itemNumber, itemMainSize);
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    LazyForEachModelNG lazyForEachModelNG;
    lazyForEachModelNG.Create(mockLazy);
    lazyForEachModelNG.OnMove(std::move(onMove));
}

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

void ListTestNg::CreateItemGroupsInLazyForEach(int32_t itemNumber, std::function<void(int32_t, int32_t)> onMove)
{
    RefPtr<LazyForEachActuator> mockLazy = AceType::MakeRefPtr<ListItemGroupMockLazy>(itemNumber);
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    LazyForEachModelNG lazyForEachModelNG;
    lazyForEachModelNG.Create(mockLazy);
    lazyForEachModelNG.OnMove(std::move(onMove));
}
} // namespace OHOS::Ace::NG
