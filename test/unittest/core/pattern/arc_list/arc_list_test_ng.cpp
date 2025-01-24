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

#include "arc_list_test_ng.h"

namespace OHOS::Ace::NG {
void ArcListTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));

    auto listTheme = AceType::MakeRefPtr<ArcListTheme>();
    EXPECT_CALL(*themeManager, GetTheme(ArcListTheme::TypeId())).WillRepeatedly(Return(listTheme));

    auto listItemTheme = AceType::MakeRefPtr<ArcListItemTheme>();
    EXPECT_CALL(*themeManager, GetTheme(ArcListItemTheme::TypeId())).WillRepeatedly(Return(listItemTheme));
    listItemTheme->itemDefaultColor_ = Color::WHITE;
    listItemTheme->hoverColor_ = Color::RED;
    listItemTheme->pressColor_ = Color::BLACK;
    int32_t hoverAnimationDuration = 250;
    int32_t hoverToPressAnimationDuration = 100;
    double disabledAlpha = 0.4;
    listItemTheme->hoverAnimationDuration_ = hoverAnimationDuration;
    listItemTheme->hoverToPressAnimationDuration_ = hoverToPressAnimationDuration;
    listItemTheme->disabledAlpha_ = disabledAlpha;
    MockPipelineContext::GetCurrentContext()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
}

void ArcListTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void ArcListTestNg::SetUp() {}

void ArcListTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    paintProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
    ClearOldNodes(); // Each testcase will create new arc_list at begin
}

void ArcListTestNg::GetList()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<ArcListPattern>();

    eventHub_ = frameNode_->GetEventHub<ListEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<ArcListLayoutProperty>();
    paintProperty_ = frameNode_->GetPaintProperty<ScrollablePaintProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<ListAccessibilityProperty>();
}

ListModelNG ArcListTestNg::CreateList()
{
    ResetElmtId();
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    ListModelNG model;
    model.Create(true);
    ViewAbstract::SetWidth(CalcLength(LIST_WIDTH));
    ViewAbstract::SetHeight(CalcLength(LIST_HEIGHT));
    RefPtr<ScrollControllerBase> scrollController = model.CreateScrollController();
    RefPtr<ScrollProxy> proxy = AceType::MakeRefPtr<NG::ScrollBarProxy>();
    model.SetScroller(scrollController, proxy);
    GetList();
    return model;
}

ListModelNG ArcListTestNg::CreateListWithHeader()
{
    ResetElmtId();
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    ListModelNG model;
    model.Create(true);
    ViewAbstract::SetWidth(CalcLength(LIST_WIDTH));
    ViewAbstract::SetHeight(CalcLength(LIST_HEIGHT));
    RefPtr<ScrollControllerBase> scrollController = model.CreateScrollController();
    RefPtr<ScrollProxy> proxy = AceType::MakeRefPtr<NG::ScrollBarProxy>();
    model.SetScroller(scrollController, proxy);

    AddHeader(&model);

    GetList();

    return model;
}

void ArcListTestNg::AddHeader(ListModelNG* model)
{
    auto nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    const char* tag = V2::ARC_LIST_ETS_TAG;
    RefPtr<FrameNode> frameNode =
        FrameNode::GetOrCreateFrameNode(tag, nodeId, []() { return AceType::MakeRefPtr<ArcListPattern>(); });
    model->SetHeader(frameNode);
}

void ArcListTestNg::CreateListItems(int32_t itemNumber, V2::ListItemStyle listItemStyle)
{
    for (int32_t index = 0; index < itemNumber; index++) {
        CreateListItem(listItemStyle);
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
}

ListItemModelNG ArcListTestNg::CreateListItem(V2::ListItemStyle listItemStyle)
{
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    ListItemModelNG itemModel;
    itemModel.Create([](int32_t) {}, listItemStyle, true);
    if (layoutProperty_->GetListDirection().value_or(Axis::VERTICAL) == Axis::VERTICAL) {
        ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
        ViewAbstract::SetHeight(CalcLength(ITEM_HEIGHT));
    } else {
        ViewAbstract::SetWidth(CalcLength(ITEM_WIDTH));
        ViewAbstract::SetHeight(CalcLength(FILL_LENGTH));
    }
    return itemModel;
}

void ArcListTestNg::CreateListItemsWithSize(std::vector<SizeT<Dimension>>& itemSizes, V2::ListItemStyle listItemStyle)
{
    for (auto iter = itemSizes.begin(); iter != itemSizes.end(); ++iter) {
        CreateListItemWithSize(*iter, listItemStyle);
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
}

void ArcListTestNg::CreateListItemsWithSize(
    int32_t itemNumber, SizeT<Dimension> itemSize, V2::ListItemStyle listItemStyle)
{
    for (int32_t index = 0; index < itemNumber; index++) {
        CreateListItemWithSize(itemSize, listItemStyle);
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
}

ListItemModelNG ArcListTestNg::CreateListItemWithSize(SizeT<Dimension> itemSize, V2::ListItemStyle listItemStyle)
{
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    ListItemModelNG itemModel;
    itemModel.Create([](int32_t) {}, listItemStyle, true);
    if (layoutProperty_->GetListDirection().value_or(Axis::VERTICAL) == Axis::VERTICAL) {
        ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
        ViewAbstract::SetHeight(CalcLength(itemSize.Height()));
    } else {
        ViewAbstract::SetWidth(CalcLength(itemSize.Width()));
        ViewAbstract::SetHeight(CalcLength(FILL_LENGTH));
    }
    return itemModel;
}

void ArcListTestNg::CreateItemWithSize(int32_t itemNumber, SizeT<Dimension> itemSize)
{
    for (int32_t index = 0; index < itemNumber; ++index) {
        ListItemModelNG itemModel = CreateListItem();
        ViewAbstract::SetWidth(CalcLength(itemSize.Width()));
        ViewAbstract::SetHeight(CalcLength(itemSize.Height()));
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
}

void ArcListTestNg::CreateItemWithSwipe(
    std::function<void()> startAction, std::function<void()> endAction, V2::SwipeEdgeEffect effect)
{
    ListItemModelNG itemModel = CreateListItem();
    itemModel.SetSwiperAction(std::move(startAction), std::move(endAction), nullptr, effect);
    if (startAction) {
        itemModel.SetDeleteArea(
            std::move(startAction), nullptr, nullptr, nullptr, nullptr, Dimension(DELETE_AREA_DISTANCE), true);
    }
    if (endAction) {
        itemModel.SetDeleteArea(
            std::move(endAction), nullptr, nullptr, nullptr, nullptr, Dimension(DELETE_AREA_DISTANCE), false);
    }
    {
        RowModelNG rowModel;
        rowModel.Create(std::nullopt, nullptr, "");
        ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
        ViewAbstract::SetHeight(CalcLength(ITEM_HEIGHT));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
}

std::function<void()> ArcListTestNg::GetDefaultSwiperBuilder(float crossSize)
{
    return [crossSize]() {
        RowModelNG rowModel;
        rowModel.Create(std::nullopt, nullptr, "");
        ViewAbstract::SetWidth(CalcLength(crossSize));
        ViewAbstract::SetHeight(CalcLength(ITEM_HEIGHT));
    };
}

std::function<void()> ArcListTestNg::GetDefaultHeaderBuilder()
{
    return []() {
        RowModelNG rowModel;
        rowModel.Create(std::nullopt, nullptr, "");
        ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
        ViewAbstract::SetHeight(CalcLength(GROUP_HEADER_LEN));
    };
}

void ArcListTestNg::UpdateCurrentOffset(float offset, int32_t source)
{
    pattern_->UpdateCurrentOffset(offset, source);
    FlushLayoutTask(frameNode_);
}

float ArcListTestNg::GetInterval()
{
    float space = layoutProperty_->GetSpace().has_value() ? layoutProperty_->GetSpace().value().ConvertToPx() : 0.f;
    return std::max(space, 0.f);
}

void ArcListTestNg::ScrollUp(float itemNumber)
{
    Axis axis = pattern_->GetAxis();
    float itemMainLength = (axis == Axis::VERTICAL) ? ITEM_HEIGHT : ITEM_WIDTH;
    float offset = (itemMainLength + GetInterval()) * itemNumber;
    pattern_->UpdateCurrentOffset(offset, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
}

void ArcListTestNg::ScrollDown(float itemNumber)
{
    Axis axis = pattern_->GetAxis();
    float itemMainLength = (axis == Axis::VERTICAL) ? ITEM_HEIGHT : ITEM_WIDTH;
    float offset = -(itemMainLength + GetInterval()) * itemNumber + itemMainLength / 2.f;
    pattern_->UpdateCurrentOffset(offset, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
}

void ArcListTestNg::ScrollToEdge(ScrollEdgeType scrollEdgeType)
{
    pattern_->ScrollToEdge(scrollEdgeType, false);
    FlushLayoutTask(frameNode_);
}

void ArcListTestNg::ScrollToIndex(int32_t index, bool smooth, ScrollAlign align)
{
    pattern_->ScrollToIndex(index, smooth, align);
    FlushLayoutTask(frameNode_);
    if (smooth) {
        float targetPos = 0.0f;
        if (!NearZero(targetPos)) {
            float endValue = pattern_->GetFinalPosition();
            pattern_->ScrollTo(endValue);
            FlushLayoutTask(frameNode_);
        }
    }
}

void ArcListTestNg::DragSwiperItem(int32_t index, float mainDelta, float mainVelocity)
{
    HandleDragStart(index);
    HandleDragUpdate(index, mainDelta);
    HandleDragEnd(index, mainVelocity);
}

void ArcListTestNg::HandleDragStart(int32_t index)
{
    GestureEvent info;
    auto itemPattern = GetChildPattern<ListItemPattern>(frameNode_, index);
    itemPattern->HandleDragStart(info);
}

void ArcListTestNg::HandleDragUpdate(int32_t index, float mainDelta)
{
    GestureEvent info;
    info.SetMainDelta(mainDelta);
    auto itemPattern = GetChildPattern<ListItemPattern>(frameNode_, index);
    itemPattern->HandleDragUpdate(info);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(frameNode_);
}

void ArcListTestNg::HandleDragEnd(int32_t index, float mainVelocity)
{
    GestureEvent info;
    info.SetMainVelocity(mainVelocity);
    auto itemPattern = GetChildPattern<ListItemPattern>(frameNode_, index);
    itemPattern->HandleDragEnd(info);
    // curOffset_ would be NodeSize or Zero
    EXPECT_NE(itemPattern->springMotion_, nullptr);
    double position = itemPattern->springMotion_->GetEndValue();
    itemPattern->UpdatePostion(position - itemPattern->curOffset_);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(frameNode_);
}

void ArcListTestNg::ScrollSnapForEqualHeightItem(float offset, float velocity)
{
    // Define (150.0, 500.0) as finger press position.
    double touchPosX = 150.0;
    double touchPosY = 500.0;
    // Generate pan gesture from finger for Arc_list sliding.
    GestureEvent info;
    info.SetMainVelocity(velocity);
    info.SetGlobalPoint(Point(touchPosX, touchPosY));
    info.SetGlobalLocation(Offset(touchPosX, touchPosY));
    info.SetSourceTool(SourceTool::FINGER);
    info.SetInputEventType(InputEventType::TOUCH_SCREEN);
    // Call HandleTouchDown and HandleDragStart.
    pattern_->scrollableEvent_->GetScrollable()->HandleTouchDown();
    pattern_->scrollableEvent_->GetScrollable()->isDragging_ = true;
    pattern_->scrollableEvent_->GetScrollable()->HandleDragStart(info);

    // Update finger position.
    info.SetGlobalLocation(Offset(touchPosX, touchPosY + offset));
    info.SetGlobalPoint(Point(touchPosX, touchPosY + offset));
    info.SetMainVelocity(velocity);
    info.SetMainDelta(offset);
    pattern_->scrollableEvent_->GetScrollable()->HandleDragUpdate(info);
    FlushLayoutTask(frameNode_);

    // Lift finger and end Arc_list sliding.
    info.SetMainVelocity(0.0);
    info.SetMainDelta(0.0);
    pattern_->scrollableEvent_->GetScrollable()->HandleTouchUp();
    pattern_->scrollableEvent_->GetScrollable()->HandleDragEnd(info);
    pattern_->scrollableEvent_->GetScrollable()->isDragging_ = false;
    FlushLayoutTask(frameNode_);

    if (pattern_->scrollableEvent_->GetScrollable()->IsSpringMotionRunning()) {
        // If current position is out of boundary, trig spring motion.
        float endValue = pattern_->scrollableEvent_->GetScrollable()->GetFinalPosition();
        pattern_->scrollableEvent_->GetScrollable()->ProcessSpringMotion(endValue);
        pattern_->scrollableEvent_->GetScrollable()->StopSpringAnimation();
        FlushLayoutTask(frameNode_);
    }

    pattern_->scrollableEvent_->GetScrollable()->StopScrollable();
}

void ArcListTestNg::ScrollSnap(float offset, float velocity)
{
    pattern_->OnScrollCallback(offset, velocity);
    FlushLayoutTask(frameNode_);
    // StartScrollSnapMotion, for condition that equal item height
    float endValue = pattern_->scrollableEvent_->GetScrollable()->GetSnapFinalPosition();
    pattern_->ScrollBy(-endValue);
    FlushLayoutTask(frameNode_);
    // UpdateScrollSnapEndWithOffset, for condition that different item height
    endValue -= pattern_->scrollableEvent_->GetScrollable()->GetSnapFinalPosition();
    pattern_->ScrollBy(endValue);
    FlushLayoutTask(frameNode_);
}

AssertionResult ArcListTestNg::IsEqualTotalOffset(float expectOffset)
{
    FlushLayoutTask(frameNode_);
    return IsEqual(pattern_->GetTotalOffset(), expectOffset);
}

AssertionResult ArcListTestNg::ScrollToIndex(int32_t index, bool smooth, ScrollAlign align, float expectOffset)
{
    // After every call to ScrollToIndex(), reset currentDelta_
    float startOffset = pattern_->GetTotalOffset();
    pattern_->ScrollToIndex(index, smooth, align);
    FlushLayoutTask(frameNode_);
    if (smooth) {
        // Because can not get targetPos, use source code
        float targetPos = 0.0f;
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
std::vector<RefPtr<FrameNode>> ArcListTestNg::GetALLItem()
{
    std::vector<RefPtr<FrameNode>> listItems;
    auto children = frameNode_->GetChildren();
    for (auto child : children) {
        auto childFrameNode = AceType::DynamicCast<FrameNode>(child);
        if (childFrameNode->GetTag() == V2::ARC_LIST_ITEM_ETS_TAG) {
            listItems.emplace_back(childFrameNode);
        }
    }
    return listItems;
}

int32_t ArcListTestNg::findFocusNodeIndex(RefPtr<FocusHub>& focusNode)
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

void ArcListTestNg::ScrollTo(float position)
{
    pattern_->ScrollTo(position);
    FlushLayoutTask(frameNode_);
}
} // namespace OHOS::Ace::NG
