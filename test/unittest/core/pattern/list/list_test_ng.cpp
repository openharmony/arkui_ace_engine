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
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components/button/button_theme.h"
#include "core/components/list/list_theme.h"
#include "core/components_ng/pattern/linear_layout/column_model_ng.h"
#include "core/components_ng/pattern/linear_layout/row_model_ng.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_model_ng.h"

namespace OHOS::Ace::NG {
void ListTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));
    auto listThemeConstants = CreateThemeConstants(THEME_PATTERN_LIST);
    auto listTheme = ListTheme::Builder().Build(listThemeConstants);
    EXPECT_CALL(*themeManager, GetTheme(ListTheme::TypeId())).WillRepeatedly(Return(listTheme));
    auto listItemThemeConstants = CreateThemeConstants(THEME_PATTERN_LIST_ITEM);
    auto listItemTheme = ListItemTheme::Builder().Build(listItemThemeConstants);
    EXPECT_CALL(*themeManager, GetTheme(ListItemTheme::TypeId())).WillRepeatedly(Return(listItemTheme));
    listItemTheme->itemDefaultColor_ = ITEMDEFAULT_COLOR;
    listItemTheme->hoverColor_ = HOVER_COLOR;
    listItemTheme->pressColor_ = PRESS_COLOR;
    int32_t hoverAnimationDuration = 250;
    int32_t hoverToPressAnimationDuration = 100;
    listItemTheme->hoverAnimationDuration_ = hoverAnimationDuration;
    listItemTheme->hoverToPressAnimationDuration_ = hoverToPressAnimationDuration;
    listItemTheme->disabledAlpha_ = DISABLED_ALPHA;
    listItemTheme->defaultColor_ = Color::WHITE;
    listItemTheme->defaultLeftMargin_ = GROUP_MARGIN;
    listItemTheme->defaultRightMargin_ = GROUP_MARGIN;
    listItemTheme->defaultPadding_ = Edge(0.0_vp);
    auto scrollableThemeConstants = CreateThemeConstants(THEME_PATTERN_SCROLLABLE);
    auto scrollableTheme = ScrollableTheme::Builder().Build(scrollableThemeConstants);
    EXPECT_CALL(*themeManager, GetTheme(ScrollableTheme::TypeId())).WillRepeatedly(Return(scrollableTheme));
    MockPipelineContext::GetCurrentContext()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    EXPECT_CALL(*MockPipelineContext::pipeline_, FlushUITasks).Times(AnyNumber());
    MockAnimationManager::Enable(true);
    testing::FLAGS_gmock_verbose = "error";
}

void ListTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void ListTestNg::SetUp()
{
    MockAnimationManager::GetInstance().Reset();
}

void ListTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    paintProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
    ClearOldNodes();  // Each testcase will create new list at begin
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
}

void ListTestNg::GetList()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<ListPattern>();
    eventHub_ = frameNode_->GetEventHub<ListEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<ListLayoutProperty>();
    paintProperty_ = frameNode_->GetPaintProperty<ScrollablePaintProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<ListAccessibilityProperty>();
}

ListModelNG ListTestNg::CreateList()
{
    ResetElmtId();
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    ListModelNG model;
    model.Create();
    ViewAbstract::SetWidth(CalcLength(LIST_WIDTH));
    ViewAbstract::SetHeight(CalcLength(LIST_HEIGHT));
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

void ListTestNg::AddItems(int32_t itemNumber, V2::ListItemStyle listItemStyle)
{
    for (int i = 0; i < itemNumber; ++i) {
        auto child = FrameNode::GetOrCreateFrameNode(V2::LIST_ITEM_ETS_TAG, -1,
            [listItemStyle]() { return AceType::MakeRefPtr<ListItemPattern>(nullptr, listItemStyle); });
        child->GetLayoutProperty()->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(LIST_WIDTH), CalcLength(Dimension(ITEM_HEIGHT))));
        frameNode_->AddChild(child);
    }
}

ListItemModelNG ListTestNg::CreateListItem(V2::ListItemStyle listItemStyle)
{
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    ListItemModelNG itemModel;
    itemModel.Create([](int32_t) {}, listItemStyle);
    if (layoutProperty_->GetListDirection().value_or(Axis::VERTICAL) == Axis::VERTICAL) {
        ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
        ViewAbstract::SetHeight(CalcLength(ITEM_HEIGHT));
    } else {
        ViewAbstract::SetWidth(CalcLength(ITEM_WIDTH));
        ViewAbstract::SetHeight(CalcLength(FILL_LENGTH));
    }
    return itemModel;
}

void ListTestNg::CreateListItemGroups(int32_t groupNumber, V2::ListItemGroupStyle listItemGroupStyle)
{
    for (int32_t index = 0; index < groupNumber; index++) {
        CreateListItemGroup(listItemGroupStyle);
        CreateListItems(GROUP_ITEM_NUMBER, static_cast<V2::ListItemStyle>(listItemGroupStyle));
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
}

ListItemGroupModelNG ListTestNg::CreateListItemGroup(V2::ListItemGroupStyle listItemGroupStyle)
{
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    ListItemGroupModelNG groupModel;
    groupModel.Create(listItemGroupStyle);
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

void ListTestNg::CreateGroupWithSettingChildrenMainSize(int32_t groupNumber)
{
    for (int32_t index = 0; index < groupNumber; ++index) {
        auto header = GetRowOrColBuilder(FILL_LENGTH, Dimension(GROUP_HEADER_LEN));
        auto footer = GetRowOrColBuilder(FILL_LENGTH, Dimension(GROUP_HEADER_LEN));
        ListItemGroupModelNG groupModel = CreateListItemGroup();
        groupModel.SetSpace(Dimension(SPACE));
        groupModel.SetDivider(ITEM_DIVIDER);
        groupModel.SetHeader(std::move(header));
        groupModel.SetFooter(std::move(footer));

        auto childrenSize = groupModel.GetOrCreateListChildrenMainSize();
        childrenSize->UpdateDefaultSize(ITEM_HEIGHT);
        const int32_t itemNumber = 2;
        childrenSize->ChangeData(1, itemNumber, { 50.f, 200.f });
        CreateListItems(1);
        CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(50.f)));
        CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(200.f)));
        CreateListItems(1);
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
}

void ListTestNg::CreateGroupChildrenMainSize(int32_t groupNumber)
{
    for (int32_t index = 0; index < groupNumber; index++) {
        ListItemGroupModelNG groupModel = CreateListItemGroup();
        auto childrenSize = groupModel.GetOrCreateListChildrenMainSize();
        childrenSize->UpdateDefaultSize(ITEM_HEIGHT);
        const int32_t itemNumber = 2;
        childrenSize->ChangeData(1, itemNumber, { 50.f, 200.f });
        CreateListItems(1);
        CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(50.f)));
        CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(200.f)));
        CreateListItems(1);
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
}

void ListTestNg::CreateGroupWithItem(int32_t groupNumber, Axis axis)
{
    for (int32_t index = 0; index < groupNumber; index++) {
        if (index & 1) {
            CreateListItems(1);
        } else {
            CreateListItemGroups(1);
        }
    }
}

void ListTestNg::CreateSwipeItems(
    std::function<void()> startAction, std::function<void()> endAction,
    V2::SwipeEdgeEffect effect, int32_t itemNumber)
{
    for (int32_t index = 0; index < itemNumber; index++) {
        ListItemModelNG itemModel = CreateListItem();
        itemModel.SetSwiperAction(nullptr, nullptr, nullptr, effect);
        if (startAction) {
            itemModel.SetDeleteArea(
                std::move(startAction), nullptr, nullptr, nullptr, nullptr, Dimension(DELETE_AREA_DISTANCE), true);
        }
        if (endAction) {
            itemModel.SetDeleteArea(
                std::move(endAction), nullptr, nullptr, nullptr, nullptr, Dimension(DELETE_AREA_DISTANCE), false);
        }
        {
            Axis axis = layoutProperty_->GetListDirection().value_or(Axis::VERTICAL);
            float mainSize = axis == Axis::VERTICAL ? ITEM_HEIGHT : ITEM_WIDTH;
            GetRowOrColBuilder(FILL_LENGTH, Dimension(mainSize))();
            ViewStackProcessor::GetInstance()->Pop();
        }
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
    FlushLayoutTask(frameNode_);
}

void ListTestNg::ScrollToEdge(ScrollEdgeType scrollEdgeType)
{
    pattern_->ScrollToEdge(scrollEdgeType, false);
    FlushLayoutTask(frameNode_);
}

void ListTestNg::ScrollToIndex(int32_t index, bool smooth, ScrollAlign align, std::optional<float> extraOffset)
{
    pattern_->ScrollToIndex(index, smooth, align, extraOffset);
    FlushLayoutTask(frameNode_);
    if (smooth) {
        auto iter = pattern_->itemPosition_.find(index);
        float targetPos = 0.0f;
        if (iter->second.isGroup) {
            if (!pattern_->GetListItemGroupAnimatePosWithoutIndexInGroup(index, iter->second.startPos,
                iter->second.endPos, align, targetPos)) {
                return;
            }
        } else {
            pattern_->GetListItemAnimatePos(iter->second.startPos, iter->second.endPos, align, targetPos);
        }
        if (extraOffset.has_value()) {
            targetPos += extraOffset.value();
        }
        if (!NearZero(targetPos)) {
            float endValue = pattern_->GetFinalPosition();
            pattern_->ScrollTo(endValue);
            FlushLayoutTask(frameNode_);
        }
    }
}

void ListTestNg::ScrollToItemInGroup(int32_t index, int32_t indexInGroup, bool smooth, ScrollAlign align)
{
    pattern_->ScrollToItemInGroup(index, indexInGroup, smooth, align);
    FlushLayoutTask(frameNode_);
    if (smooth) {
        float endValue = pattern_->GetFinalPosition();
        pattern_->ScrollTo(endValue);
        FlushLayoutTask(frameNode_);
    }
}

void ListTestNg::DragSwiperItem(int32_t index, float mainDelta, float mainVelocity)
{
    HandleDragStart(index);
    HandleDragUpdate(index, mainDelta);
    HandleDragEnd(index, mainVelocity);
}

void ListTestNg::HandleDragStart(int32_t index)
{
    GestureEvent info;
    auto itemPattern = GetChildPattern<ListItemPattern>(frameNode_, index);
    auto handleDragStart = itemPattern->panEvent_->GetActionStartEventFunc();
    handleDragStart(info);
}

void ListTestNg::HandleDragUpdate(int32_t index, float mainDelta)
{
    GestureEvent info;
    info.SetMainDelta(mainDelta);
    auto itemPattern = GetChildPattern<ListItemPattern>(frameNode_, index);
    auto handleDragUpdate = itemPattern->panEvent_->GetActionUpdateEventFunc();
    handleDragUpdate(info);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(frameNode_);
}

void ListTestNg::HandleDragEnd(int32_t index, float mainVelocity)
{
    GestureEvent info;
    info.SetMainVelocity(mainVelocity);
    auto itemPattern = GetChildPattern<ListItemPattern>(frameNode_, index);
    auto handleDragEnd = itemPattern->panEvent_->GetActionEndEventFunc();
    handleDragEnd(info);
    // curOffset_ would be NodeSize or Zero
    EXPECT_NE(itemPattern->springMotion_, nullptr);
    double position = itemPattern->springMotion_->GetEndValue();
    itemPattern->UpdatePostion(position - itemPattern->curOffset_);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(frameNode_);
}

void ListTestNg::ScrollSnap(double offset, double endVelocity)
{
    double velocity = offset > 0.f ? 1200.f : -1200.f;
    // Define (150.0, 500.0) as finger press position.
    double touchPosX = 150.0;
    double touchPosY = 500.0;
    // Generate pan gesture from finger for List sliding.
    GestureEvent info;
    info.SetMainVelocity(velocity);
    info.SetGlobalPoint(Point(touchPosX, touchPosY));
    info.SetGlobalLocation(Offset(touchPosX, touchPosY));
    info.SetSourceTool(SourceTool::FINGER);
    info.SetInputEventType(InputEventType::TOUCH_SCREEN);
    // Call HandleTouchDown and HandleDragStart.
    auto scrollable = pattern_->scrollableEvent_->GetScrollable();
    scrollable->HandleTouchDown();
    scrollable->isDragging_ = true;
    scrollable->HandleDragStart(info);

    // Update finger position.
    info.SetGlobalLocation(Offset(touchPosX, touchPosY + offset));
    info.SetGlobalPoint(Point(touchPosX, touchPosY + offset));
    info.SetMainVelocity(velocity);
    info.SetMainDelta(offset);
    scrollable->HandleDragUpdate(info);
    FlushLayoutTask(frameNode_);

    // Lift finger and end List sliding.
    info.SetMainVelocity(endVelocity);
    info.SetMainDelta(0.0);
    scrollable->HandleTouchUp();
    scrollable->HandleDragEnd(info);
    scrollable->isDragging_ = false;
    FlushLayoutTask(frameNode_);

    if (scrollable->IsSpringMotionRunning()) {
        // If current position is out of boundary, trig spring motion.
        float endValue = scrollable->GetFinalPosition();
        scrollable->ProcessSpringMotion(endValue);
        scrollable->StopSpringAnimation();
        FlushLayoutTask(frameNode_);
    } else if (scrollable->state_ == Scrollable::AnimationState::SNAP) {
        // StartListSnapAnimation, for condition that equal item height.
        float endValue = scrollable->GetSnapFinalPosition();
        scrollable->ProcessListSnapMotion(endValue);
        scrollable->ProcessScrollSnapStop();
        FlushLayoutTask(frameNode_);
    }
    scrollable->StopScrollable();
}

AssertionResult ListTestNg::ScrollToIndex(int32_t index, bool smooth, ScrollAlign align, float expectOffset)
{
    // After every call to ScrollToIndex(), reset currentDelta_
    float startOffset = pattern_->GetTotalOffset();
    pattern_->ScrollToIndex(index, smooth, align);
    FlushLayoutTask(frameNode_);
    if (smooth) {
        // Because can not get targetPos, use source code
        auto iter = pattern_->itemPosition_.find(index);
        float targetPos = 0.0f;
        if (iter->second.isGroup) {
            pattern_->GetListItemGroupAnimatePosWithoutIndexInGroup(index, iter->second.startPos,
                iter->second.endPos, align, targetPos);
        } else {
            pattern_->GetListItemAnimatePos(iter->second.startPos, iter->second.endPos, align, targetPos);
        }
        if (!NearZero(targetPos)) {
            // Straight to the end of the anmiation, use ScrollTo replace AnimateTo
            float finalPosition = pattern_->GetFinalPosition();
            float totalHeight = pattern_->GetTotalHeight();
            finalPosition = std::clamp(finalPosition, 0.f, totalHeight); // limit scrollDistance
            pattern_->ScrollTo(finalPosition);
            FlushLayoutTask(frameNode_);
        }
    }
    float currentOffset = pattern_->GetTotalOffset();
    pattern_->ScrollTo(startOffset); // reset offset before return
    FlushLayoutTask(frameNode_);
    return IsEqual(currentOffset, expectOffset);
}

AssertionResult ListTestNg::JumpToItemInGroup(
    int32_t index, int32_t indexInGroup, bool smooth, ScrollAlign align, float expectOffset)
{
    auto controller = pattern_->positionController_;
    float startOffset = pattern_->GetTotalOffset();
    controller->JumpToItemInGroup(index, indexInGroup, smooth, align);
    FlushLayoutTask(frameNode_);
    if (smooth) {
        // Because can not get targetPos, use source code
        auto iter = pattern_->itemPosition_.find(index);
        float targetPos = 0.0f;
        if (iter->second.isGroup) {
            pattern_->GetListItemGroupAnimatePosWithIndexInGroup(index, indexInGroup,
                iter->second.startPos, align, targetPos);
        } else {
            pattern_->GetListItemAnimatePos(iter->second.startPos, iter->second.endPos, align, targetPos);
        }
        if (!NearZero(targetPos)) {
            // Straight to the end of the anmiation, use ScrollTo replace AnimateTo
            float finalPosition = pattern_->GetFinalPosition();
            float totalHeight = pattern_->GetTotalHeight();
            finalPosition = std::clamp(finalPosition, 0.f, totalHeight); // limit scrollDistance
            pattern_->ScrollTo(finalPosition);
            FlushLayoutTask(frameNode_);
        }
    }
    float currentOffset = pattern_->GetTotalOffset();
    pattern_->ScrollTo(startOffset); // reset offset before return
    FlushLayoutTask(frameNode_);
    return IsEqual(currentOffset, expectOffset);
}

// Get all listItem that in or not in listItemGroup
std::vector<RefPtr<FrameNode>> ListTestNg::GetALLItem()
{
    std::vector<RefPtr<FrameNode>> listItems;
    auto children = frameNode_->GetChildren();
    for (auto child : children) {
        auto childFrameNode = AceType::DynamicCast<FrameNode>(child);
        if (childFrameNode->GetTag() == V2::LIST_ITEM_GROUP_ETS_TAG) {
            auto group = child->GetChildren();
            for (auto item : group) {
                auto itemFrameNode = AceType::DynamicCast<FrameNode>(item);
                if (itemFrameNode->GetTag() == V2::LIST_ITEM_ETS_TAG) {
                    listItems.emplace_back(itemFrameNode);
                }
            }
        } else if (childFrameNode->GetTag() == V2::LIST_ITEM_ETS_TAG) {
            listItems.emplace_back(childFrameNode);
        }
    }
    return listItems;
}

int32_t ListTestNg::findFocusNodeIndex(RefPtr<FocusHub>& focusNode)
{
    std::vector<RefPtr<FrameNode>> listItems = GetALLItem();
    int32_t size = static_cast<int32_t>(listItems.size());
    for (int32_t index = 0; index < size; index++) {
        if (focusNode == listItems[index]->GetOrCreateFocusHub()) {
            return index;
        }
    }
    return NULL_VALUE;
}

void ListTestNg::ScrollTo(float position)
{
    pattern_->ScrollTo(position);
    FlushLayoutTask(frameNode_);
}

void ListTestNg::CreateRepeatVirtualScrollNode(int32_t itemNumber, const std::function<void(uint32_t)>& createFunc)
{
    RepeatVirtualScrollModelNG repeatModel;
    std::function<void(const std::string&, uint32_t)> updateFunc =
        [&createFunc](const std::string& value, uint32_t idx) {
            createFunc(idx);
        };
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
    std::function<void(uint32_t, uint32_t)> setActiveRange = [](uint32_t start, uint32_t end) {
    };
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
        FlushLayoutTask(frameNode_);
        predictParam = listPattern->GetPredictLayoutParamV2();
        tryCount--;
    }
}

void ListTestNg::CreateGroupWithSettingWithComponentContent(
    int32_t groupNumber, V2::ListItemGroupStyle listItemGroupStyle, int32_t itemNumber)
{
    for (int32_t index = 0; index < groupNumber; index++) {
        ListItemGroupModelNG groupModel = CreateListItemGroup(listItemGroupStyle);
        groupModel.SetSpace(Dimension(SPACE));
        groupModel.SetDivider(ITEM_DIVIDER);
        groupModel.SetHeaderComponent(CreateCustomNode("Header"));
        groupModel.SetFooterComponent(CreateCustomNode("Footer"));
        CreateListItems(itemNumber, static_cast<V2::ListItemStyle>(listItemGroupStyle));
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
}

RefPtr<FrameNode> ListTestNg::CreateCustomNode(const std::string& tag)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>(
        tag, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto layoutProperty = frameNode->GetLayoutProperty();
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(LIST_WIDTH), CalcLength(LIST_HEIGHT)));
    return frameNode;
}
} // namespace OHOS::Ace::NG
