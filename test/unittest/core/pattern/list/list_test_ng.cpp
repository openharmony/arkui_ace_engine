/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include <functional>
#include <optional>

#include "gtest/gtest.h"
#include "test/mock/base/mock_drag_window.h"

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/property/safe_area_insets.h"
#define private public
#define protected public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "bridge/common/utils/utils.h"
#include "core/components/button/button_theme.h"
#include "core/components/scroll/scrollable.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_model_ng.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/linear_layout/row_model_ng.h"
#include "core/components_ng/pattern/list/list_item_group_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_item_group_layout_property.h"
#include "core/components_ng/pattern/list/list_item_group_model_ng.h"
#include "core/components_ng/pattern/list/list_item_group_paint_method.h"
#include "core/components_ng/pattern/list/list_item_group_pattern.h"
#include "core/components_ng/pattern/list/list_item_model.h"
#include "core/components_ng/pattern/list/list_item_model_ng.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/list/list_lanes_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/pattern/list/list_model_ng.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/list/list_position_controller.h"
#include "core/components_v2/list/list_properties.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float LIST_WIDTH = 480.f;
constexpr float LIST_HEIGHT = 800.f;
constexpr int32_t TOTAL_LINE_NUMBER = 10;
constexpr int32_t VIEW_LINE_NUMBER = 8;
constexpr float ITEM_WIDTH = LIST_WIDTH / VIEW_LINE_NUMBER;
constexpr float ITEM_HEIGHT = LIST_HEIGHT / VIEW_LINE_NUMBER;
constexpr int32_t GROUP_NUMBER = 4;
constexpr int32_t GROUP_LINE_NUMBER = 4;
constexpr float GROUP_HEADER_LEN = 50.f;
constexpr float START_NODE_LEN = 80.f;
constexpr float END_NODE_LEN = 100.f;
constexpr float DELETE_AREA_DISTANCE = 50.f;
constexpr Dimension GROUP_MARGIN = 12.0_vp;
constexpr float DEFAULT_STIFFNESS = 228;
constexpr float DEFAULT_DAMPING = 30;
constexpr float SWIPER_SPEED_TH = 1200.f;
constexpr float SWIPER_TH = 0.25f;
constexpr int32_t DEFAULT_LANES = 1;
constexpr int32_t DEFAULT_SPACE = 0;
constexpr float DEFAULT_STARTOFFSET = 0.f;
constexpr float SPACE = 10.f;
constexpr float STROKE_WIDTH = 5.f;
const V2::ItemDivider ITEM_DIVIDER = { Dimension(STROKE_WIDTH), Dimension(10), Dimension(20), Color(0x000000) };
struct SwipeActionItem {
    std::function<void()> builderAction;
    Dimension actionAreaDistance;
    OnDeleteEvent onDelete;
    OnEnterDeleteAreaEvent onEnterDeleteArea;
    OnExitDeleteAreaEvent onExitDeleteArea;
    OnStateChangedEvent onStateChange;
};
} // namespace

class ListTestNg : public TestNG {
protected:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();
    void Create(const std::function<void(ListModelNG)>& callback);
    void CreateWithItem(const std::function<void(ListModelNG)>& callback);
    void CreateWithSwipe(bool isStartNode, V2::SwipeEdgeEffect swipeEdgeEffect, int32_t itemNumber = TOTAL_LINE_NUMBER);
    void CreateWithSwipeAction(
        SwipeActionItem& item, bool isStartArea, OnOffsetChangeFunc onOffsetChange, V2::SwipeEdgeEffect effect);

    static void CreateItem(
        int32_t itemNumber, Axis axis = Axis::VERTICAL, V2::ListItemStyle listItemStyle = V2::ListItemStyle::NONE);
    static void CreateItemWithSize(
        int32_t itemNumber, SizeT<Dimension> itemSize, V2::ListItemStyle listItemStyle = V2::ListItemStyle::NONE);
    static void CreateGroup(int32_t groupNumber, Axis axis = Axis::VERTICAL);
    static void CreateGroupWithSetting(int32_t groupNumber, Axis axis, V2::ListItemGroupStyle listItemGroupStyle,
        int32_t itemNumber = GROUP_LINE_NUMBER);
    static void CreateItemWithSwipe(
        std::function<void()> startAction, std::function<void()> endAction, V2::SwipeEdgeEffect effect);
    static std::function<void()> GetDefaultSwiperBuilder(float crossSize);
    static std::function<void()> GetDefaultHeaderBuilder();

    void UpdateCurrentOffset(float offset, int32_t source = SCROLL_FROM_UPDATE);
    float GetInterval();
    void ScrollUp(float itemNumber = 1);
    void ScrollDown(float itemNumber = 1);
    void ScrollToEdge(ScrollEdgeType scrollEdgeType);
    void ScrollSnap(float offset, float velocity);
    void ScrollToIndex(int32_t index, bool smooth, ScrollAlign align);
    void ScrollToItemInGroup(int32_t index, int32_t indexInGroup, bool smooth, ScrollAlign align);
    void MouseSelect(Offset start, Offset end);
    void DragSwiperItem(int32_t index, float mainDelta, float mainVelocity = SWIPER_SPEED_TH);
    void HandleDragStart(int32_t index);
    void HandleDragUpdate(int32_t index, float mainDelta);
    void HandleDragEnd(int32_t index, float mainVelocity = SWIPER_SPEED_TH);
    void UpdateContentModifier();
    RefPtr<ListPaintMethod> UpdateOverlayModifier();

    AssertionResult VerifyPosition(
        const RefPtr<FrameNode>& frameNode, int32_t viewItemNumber, int32_t lanes, float space, float startOffset);
    AssertionResult VerifyItemPosition(
        const RefPtr<FrameNode>& frameNode, int32_t viewItemNumber, int32_t lanes, float space, int32_t initialIndex);
    AssertionResult VerifyGroupItemPosition(
        const RefPtr<FrameNode>& frameNode, int32_t viewItemNumber, int32_t lanes, float space, float startOffset);
    AssertionResult IsEqualTotalOffset(float expectOffset);
    AssertionResult IsEqualNextFocusNode(FocusStep step, int32_t currentIndex, int32_t expectNextIndex);
    AssertionResult ScrollToIndex(int32_t index, bool smooth, ScrollAlign align, float expectOffset);
    AssertionResult ScrollToItemInGroup(
        int32_t index, int32_t indexInGroup, bool smooth, ScrollAlign align, float expectOffset);
    AssertionResult VerifySticky(int32_t groupIndex, bool isHeader, float expectOffsetY);
    std::vector<RefPtr<FrameNode>> GetALLItem();
    int32_t findFocusNodeIndex(RefPtr<FocusHub>& focusNode);

    RefPtr<FrameNode> frameNode_;
    RefPtr<ListPattern> pattern_;
    RefPtr<ListEventHub> eventHub_;
    RefPtr<ListLayoutProperty> layoutProperty_;
    RefPtr<ScrollablePaintProperty> paintProperty_;
    RefPtr<ListAccessibilityProperty> accessibilityProperty_;
};

void ListTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));

    auto listItemTheme = AceType::MakeRefPtr<ListItemTheme>();
    EXPECT_CALL(*themeManager, GetTheme(ListItemTheme::TypeId())).WillRepeatedly(Return(listItemTheme));
    listItemTheme->itemDefaultColor_ = Color::WHITE;
    listItemTheme->hoverColor_ = Color::RED;
    listItemTheme->pressColor_ = Color::BLACK;
    int32_t hoverAnimationDuration = 250;
    int32_t hoverToPressAnimationDuration = 100;
    double disabledAlpha = 0.4;
    listItemTheme->hoverAnimationDuration_ = hoverAnimationDuration;
    listItemTheme->hoverToPressAnimationDuration_ = hoverToPressAnimationDuration;
    listItemTheme->disabledAlpha_ = disabledAlpha;
    listItemTheme->defaultColor_ = Color::WHITE;
    listItemTheme->defaultLeftMargin_ = GROUP_MARGIN;
    listItemTheme->defaultRightMargin_ = GROUP_MARGIN;
}

void ListTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void ListTestNg::SetUp() {}

void ListTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    paintProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
}

void ListTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<ListPattern>();
    eventHub_ = frameNode_->GetEventHub<ListEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<ListLayoutProperty>();
    paintProperty_ = frameNode_->GetPaintProperty<ScrollablePaintProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<ListAccessibilityProperty>();
}

void ListTestNg::Create(const std::function<void(ListModelNG)>& callback)
{
    ListModelNG model;
    model.Create();
    ViewAbstract::SetWidth(CalcLength(LIST_WIDTH));
    ViewAbstract::SetHeight(CalcLength(LIST_HEIGHT));
    RefPtr<ScrollControllerBase> scrollController = model.CreateScrollController();
    RefPtr<ScrollProxy> proxy = AceType::MakeRefPtr<NG::ScrollBarProxy>();
    model.SetScroller(scrollController, proxy);
    if (callback) {
        callback(model);
    }
    GetInstance();
    FlushLayoutTask(frameNode_);
}

void ListTestNg::CreateWithItem(const std::function<void(ListModelNG)>& callback)
{
    Create([callback](ListModelNG model) {
        if (callback) {
            callback(model);
        }
        CreateItem(TOTAL_LINE_NUMBER);
    });
}

void ListTestNg::CreateWithSwipe(bool isStartNode, V2::SwipeEdgeEffect swipeEdgeEffect, int32_t itemNumber)
{
    Create([isStartNode, swipeEdgeEffect, itemNumber](ListModelNG model) {
        auto startFunc = GetDefaultSwiperBuilder(START_NODE_LEN);
        auto endFunc = GetDefaultSwiperBuilder(END_NODE_LEN);
        for (int32_t index = 0; index < itemNumber; index++) {
            if (isStartNode) {
                CreateItemWithSwipe(startFunc, nullptr, swipeEdgeEffect);
            } else {
                CreateItemWithSwipe(nullptr, endFunc, swipeEdgeEffect);
            }
        }
    });
}

void ListTestNg::CreateWithSwipeAction(
    SwipeActionItem& item, bool isStartArea, OnOffsetChangeFunc onOffsetChange, V2::SwipeEdgeEffect effect)
{
    ListModelNG model;
    model.Create();
    ViewAbstract::SetWidth(CalcLength(LIST_WIDTH));
    ViewAbstract::SetHeight(CalcLength(LIST_HEIGHT));
    {
        ListItemModelNG itemModel;
        itemModel.Create();
        ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
        ViewAbstract::SetHeight(CalcLength(ITEM_HEIGHT));
        itemModel.SetSwiperAction(nullptr, nullptr, std::move(onOffsetChange), effect);
        itemModel.SetDeleteArea(std::move(item.builderAction), std::move(item.onDelete),
            std::move(item.onEnterDeleteArea), std::move(item.onExitDeleteArea), std::move(item.onStateChange),
            item.actionAreaDistance, isStartArea);
        {
            RowModelNG rowModel;
            rowModel.Create(std::nullopt, nullptr, "");
            ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
            ViewAbstract::SetHeight(CalcLength(ITEM_HEIGHT));
            ViewStackProcessor::GetInstance()->Pop();
        }
        ViewStackProcessor::GetInstance()->Pop();
    }
    GetInstance();
    FlushLayoutTask(frameNode_);
}

void ListTestNg::CreateItem(int32_t itemNumber, Axis axis, V2::ListItemStyle listItemStyle)
{
    for (int32_t index = 0; index < itemNumber; index++) {
        ListItemModelNG itemModel;
        itemModel.Create([](int32_t) {}, listItemStyle);
        if (axis == Axis::VERTICAL) {
            ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
            ViewAbstract::SetHeight(CalcLength(ITEM_HEIGHT));
        } else {
            ViewAbstract::SetWidth(CalcLength(ITEM_WIDTH));
            ViewAbstract::SetHeight(CalcLength(FILL_LENGTH));
        }
        {
            ButtonModelNG buttonModelNG;
            buttonModelNG.CreateWithLabel("label");
            ViewStackProcessor::GetInstance()->Pop();
        }
        ViewStackProcessor::GetInstance()->Pop();
    }
}

void ListTestNg::CreateItemWithSize(int32_t itemNumber, SizeT<Dimension> itemSize, V2::ListItemStyle listItemStyle)
{
    for (int32_t index = 0; index < itemNumber; ++index) {
        ListItemModelNG itemModel;
        itemModel.Create([](int32_t) {}, listItemStyle);
        ViewAbstract::SetWidth(CalcLength(itemSize.Width()));
        ViewAbstract::SetHeight(CalcLength(itemSize.Height()));
        {
            ButtonModelNG buttonModelNG;
            buttonModelNG.CreateWithLabel("label");
            ViewStackProcessor::GetInstance()->Pop();
        }
        ViewStackProcessor::GetInstance()->Pop();
    }
}

void ListTestNg::CreateGroupWithSetting(
    int32_t groupNumber, Axis axis, V2::ListItemGroupStyle listItemGroupStyle, int32_t itemNumber)
{
    for (int32_t index = 0; index < groupNumber; index++) {
        auto header = GetDefaultHeaderBuilder();
        auto footer = GetDefaultHeaderBuilder();
        ListItemGroupModelNG groupModel;
        groupModel.Create(listItemGroupStyle);
        groupModel.SetSpace(Dimension(SPACE));
        groupModel.SetDivider(ITEM_DIVIDER);
        groupModel.SetHeader(std::move(header));
        groupModel.SetFooter(std::move(footer));
        CreateItem(itemNumber, axis, static_cast<V2::ListItemStyle>(listItemGroupStyle));
        ViewStackProcessor::GetInstance()->Pop();
    }
}

void ListTestNg::CreateGroup(int32_t groupNumber, Axis axis)
{
    for (int32_t index = 0; index < groupNumber; index++) {
        ListItemGroupModelNG groupModel;
        groupModel.Create(V2::ListItemGroupStyle::NONE);
        CreateItem(GROUP_LINE_NUMBER, axis, V2::ListItemStyle::NONE);
        ViewStackProcessor::GetInstance()->Pop();
    }
}

void ListTestNg::CreateItemWithSwipe(
    std::function<void()> startAction, std::function<void()> endAction, V2::SwipeEdgeEffect effect)
{
    ListItemModelNG itemModel;
    itemModel.Create();
    ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
    ViewAbstract::SetHeight(CalcLength(ITEM_HEIGHT));
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
}

std::function<void()> ListTestNg::GetDefaultSwiperBuilder(float crossSize)
{
    return [crossSize]() {
        RowModelNG rowModel;
        rowModel.Create(std::nullopt, nullptr, "");
        ViewAbstract::SetWidth(CalcLength(crossSize));
        ViewAbstract::SetHeight(CalcLength(ITEM_HEIGHT));
    };
}

std::function<void()> ListTestNg::GetDefaultHeaderBuilder()
{
    return []() {
        RowModelNG rowModel;
        rowModel.Create(std::nullopt, nullptr, "");
        ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
        ViewAbstract::SetHeight(CalcLength(GROUP_HEADER_LEN));
    };
}

void ListTestNg::UpdateCurrentOffset(float offset, int32_t source)
{
    pattern_->UpdateCurrentOffset(offset, source);
    FlushLayoutTask(frameNode_);
}

float ListTestNg::GetInterval()
{
    float space = layoutProperty_->GetSpace().has_value() ? layoutProperty_->GetSpace().value().ConvertToPx() : 0.f;
    float strokeWidth = layoutProperty_->GetDivider().has_value()
                            ? layoutProperty_->GetDivider().value().strokeWidth.ConvertToPx()
                            : 0.f;
    return std::max(space, strokeWidth);
}

void ListTestNg::ScrollUp(float itemNumber)
{
    Axis axis = pattern_->GetAxis();
    float itemMainLength = (axis == Axis::VERTICAL) ? ITEM_HEIGHT : ITEM_WIDTH;
    float offset = (itemMainLength + GetInterval()) * itemNumber;
    pattern_->UpdateCurrentOffset(offset, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
}

void ListTestNg::ScrollDown(float itemNumber)
{
    Axis axis = pattern_->GetAxis();
    float itemMainLength = (axis == Axis::VERTICAL) ? ITEM_HEIGHT : ITEM_WIDTH;
    float offset = -(itemMainLength + GetInterval()) * itemNumber;
    pattern_->UpdateCurrentOffset(offset, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
}

void ListTestNg::ScrollToEdge(ScrollEdgeType scrollEdgeType)
{
    pattern_->ScrollToEdge(scrollEdgeType, false);
    FlushLayoutTask(frameNode_);
}

void ListTestNg::ScrollSnap(float offset, float velocity)
{
    pattern_->OnScrollSnapCallback(offset, velocity);
    FlushLayoutTask(frameNode_);
    float endValue = pattern_->scrollableEvent_->GetScrollable()->GetSnapFinalPosition();
    pattern_->ScrollBy(-endValue);
    FlushLayoutTask(frameNode_);
}

void ListTestNg::ScrollToIndex(int32_t index, bool smooth, ScrollAlign align)
{
    pattern_->ScrollToIndex(index, smooth, align);
    FlushLayoutTask(frameNode_);
    if (smooth) {
        float endValue = pattern_->GetFinalPosition();
        pattern_->ScrollTo(endValue);
        FlushLayoutTask(frameNode_);
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

void ListTestNg::MouseSelect(Offset start, Offset end)
{
    GestureEvent info;
    info.SetInputEventType(InputEventType::MOUSE_BUTTON);
    info.SetLocalLocation(start);
    info.SetGlobalLocation(start);
    pattern_->HandleDragStart(info);
    if (start != end) {
        info.SetLocalLocation(end);
        info.SetGlobalLocation(end);
        pattern_->HandleDragUpdate(info);
    }
    pattern_->HandleDragEnd(info);
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
    itemPattern->HandleDragStart(info);
}

void ListTestNg::HandleDragUpdate(int32_t index, float mainDelta)
{
    GestureEvent info;
    info.SetMainDelta(mainDelta);
    auto itemPattern = GetChildPattern<ListItemPattern>(frameNode_, index);
    itemPattern->HandleDragUpdate(info);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(frameNode_);
}

void ListTestNg::HandleDragEnd(int32_t index, float mainVelocity)
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

void ListTestNg::UpdateContentModifier()
{
    RefPtr<NodePaintMethod> paint = pattern_->CreateNodePaintMethod();
    RefPtr<ListPaintMethod> listPaint = AceType::DynamicCast<ListPaintMethod>(paint);
    auto paintWrapper = frameNode_->CreatePaintWrapper();
    listPaint->UpdateContentModifier(AceType::RawPtr(paintWrapper));
}

RefPtr<ListPaintMethod> ListTestNg::UpdateOverlayModifier()
{
    RefPtr<NodePaintMethod> paint = pattern_->CreateNodePaintMethod();
    RefPtr<ListPaintMethod> listPaint = AceType::DynamicCast<ListPaintMethod>(paint);
    auto paintWrapper = frameNode_->CreatePaintWrapper();
    listPaint->UpdateOverlayModifier(AceType::RawPtr(paintWrapper));
    return listPaint;
}

AssertionResult ListTestNg::VerifyPosition(
    const RefPtr<FrameNode>& frameNode, int32_t viewItemNumber, int32_t lanes, float space, float startOffset)
{
    bool isGroup = frameNode->GetTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
    if (isGroup) {
        return VerifyGroupItemPosition(frameNode, viewItemNumber, lanes, space, startOffset);
    } else {
        Axis axis = pattern_->GetAxis();
        float itemMainLength = (axis == Axis::VERTICAL) ? ITEM_HEIGHT : ITEM_WIDTH;
        float itemSpaceLength = itemMainLength + space;
        int32_t initialIndex = std::floor(startOffset / itemSpaceLength) * lanes;
        return VerifyItemPosition(frameNode, viewItemNumber, lanes, space, initialIndex);
    }
}

AssertionResult ListTestNg::VerifyItemPosition(
    const RefPtr<FrameNode>& frameNode, int32_t viewItemNumber, int32_t lanes, float space, int32_t initialIndex)
{
    if (lanes < 1) {
        return AssertionFailure() << "lanes < 1";
    }
    Axis axis = pattern_->GetAxis();
    float itemMainLength = (axis == Axis::VERTICAL) ? ITEM_HEIGHT : ITEM_WIDTH;
    float itemSpaceLength = itemMainLength + space;
    auto itemPosition = frameNode->GetPattern<ListPattern>()->GetItemPosition();
    if (itemPosition.size() != static_cast<size_t>(viewItemNumber)) {
        return AssertionFailure() << "The itemPosition size is not equal to viewItemNumber"
                                  << " itemPosition: " << itemPosition.size() << " viewItemNumber: " << viewItemNumber;
    }
    for (int32_t index = 0; index < viewItemNumber; index++) {
        int32_t itemIndex = index + initialIndex;
        float startPos = itemPosition[itemIndex].startPos;
        float endPos = itemPosition[itemIndex].endPos;
        float expectStartPos = (index / lanes) * itemSpaceLength;
        float expectEndPos = expectStartPos + itemMainLength;
        if (!NearEqual(startPos, expectStartPos) || !NearEqual(endPos, expectEndPos)) {
            return AssertionFailure() << "At itemPosition Index: " << itemIndex << " ItemPosition: (" << startPos
                                      << " - " << endPos << ")"
                                      << " != expectPosition: (" << expectStartPos << " - " << expectEndPos << ")";
        }
    }
    return AssertionSuccess();
}

AssertionResult ListTestNg::VerifyGroupItemPosition(
    const RefPtr<FrameNode>& frameNode, int32_t viewItemNumber, int32_t lanes, float space, float startOffset)
{
    if (lanes < 1) {
        return AssertionFailure() << "lanes < 1";
    }
    Axis axis = pattern_->GetAxis();
    float itemMainLength = (axis == Axis::VERTICAL) ? ITEM_HEIGHT : ITEM_WIDTH;
    float itemSpaceLength = itemMainLength + space;
    auto itemPosition = frameNode->GetPattern<ListItemGroupPattern>()->GetItemPosition();
    if (itemPosition.size() != static_cast<size_t>(viewItemNumber)) {
        return AssertionFailure() << "The itemPosition size is not equal to viewItemNumber"
                                  << " itemPosition: " << itemPosition.size() << " viewItemNumber: " << viewItemNumber;
    }
    for (int32_t index = 0; index < viewItemNumber; index++) {
        int32_t itemIndex = index;
        float startPos = itemPosition[itemIndex].first;
        float endPos = itemPosition[itemIndex].second;
        float expectStartPos = (index / lanes) * itemSpaceLength + startOffset;
        float expectEndPos = expectStartPos + itemMainLength;
        if (!NearEqual(startPos, expectStartPos) || !NearEqual(endPos, expectEndPos)) {
            return AssertionFailure() << "At itemPosition Index: " << itemIndex << " ItemPosition: (" << startPos
                                      << " - " << endPos << ")"
                                      << " != expectPosition: (" << expectStartPos << " - " << expectEndPos << ")";
        }
    }
    return AssertionSuccess();
}

AssertionResult ListTestNg::IsEqualTotalOffset(float expectOffset)
{
    FlushLayoutTask(frameNode_);
    return IsEqual(pattern_->GetTotalOffset(), expectOffset);
}

AssertionResult ListTestNg::IsEqualNextFocusNode(FocusStep step, int32_t currentIndex, int32_t expectNextIndex)
{
    std::vector<RefPtr<FrameNode>> listItems = GetALLItem();
    RefPtr<FocusHub> currentFocusNode = listItems[currentIndex]->GetOrCreateFocusHub();
    currentFocusNode->RequestFocusImmediately();
    RefPtr<FocusHub> nextFocusNode = pattern_->GetNextFocusNode(step, currentFocusNode).Upgrade();
    if (expectNextIndex != NULL_VALUE && nextFocusNode == nullptr) {
        return AssertionFailure() << "Next FocusNode is null.";
    }
    int32_t nextIndex = findFocusNodeIndex(nextFocusNode);
    return IsEqual(nextIndex, expectNextIndex);
}

AssertionResult ListTestNg::ScrollToIndex(int32_t index, bool smooth, ScrollAlign align, float expectOffset)
{
    float startOffset = pattern_->GetTotalOffset();
    pattern_->ScrollToIndex(index, smooth, align);
    FlushLayoutTask(frameNode_);
    if (smooth) {
        // Straight to the end of the anmiation
        // can not exceed scrollableDistance if is not spring
        float endValue = pattern_->GetFinalPosition();
        float scrollableDistance = pattern_->GetScrollableDistance();
        float two = 2.f;
        if (GreatNotEqual(endValue - startOffset * two, scrollableDistance)) {
            endValue = scrollableDistance;
        }
        if (LessNotEqual(endValue, 0)) {
            endValue = 0;
        }
        pattern_->UpdateCurrentOffset(pattern_->GetTotalOffset() - endValue,
            SCROLL_FROM_ANIMATION_CONTROLLER);
        FlushLayoutTask(frameNode_);
    }
    float currentOffset = pattern_->GetTotalOffset();
    // reset offset before return
    pattern_->ScrollTo(startOffset);
    FlushLayoutTask(frameNode_);
    return IsEqual(currentOffset, expectOffset);
}

AssertionResult ListTestNg::ScrollToItemInGroup(
    int32_t index, int32_t indexInGroup, bool smooth, ScrollAlign align, float expectOffset)
{
    float startOffset = pattern_->GetTotalOffset();
    pattern_->ScrollToItemInGroup(index, indexInGroup, smooth, align);
    FlushLayoutTask(frameNode_);
    if (smooth) {
        // Straight to the end of the anmiation
        // can not exceed scrollableDistance if is not spring
        float endValue = pattern_->GetFinalPosition();
        float scrollableDistance = pattern_->GetScrollableDistance();
        float two = 2.f;
        if (GreatNotEqual(endValue - startOffset * two, scrollableDistance)) {
            endValue = scrollableDistance;
        }
        if (LessNotEqual(endValue, 0)) {
            endValue = 0;
        }
        pattern_->UpdateCurrentOffset(pattern_->GetTotalOffset() - endValue,
            SCROLL_FROM_ANIMATION_CONTROLLER);
        FlushLayoutTask(frameNode_);
    }
    float currentOffset = pattern_->GetTotalOffset();
    // reset offset before return
    pattern_->ScrollTo(startOffset);
    FlushLayoutTask(frameNode_);
    return IsEqual(currentOffset, expectOffset);
}

AssertionResult ListTestNg::VerifySticky(int32_t groupIndex, bool isHeader, float expectOffsetY)
{
    RefPtr<FrameNode> groupNode = GetChildFrameNode(frameNode_, groupIndex);
    float offsetY = isHeader ? GetChildRect(groupNode, 0).GetY() : GetChildRect(groupNode, 1).GetY();
    return IsEqual(offsetY, expectOffsetY);
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

/**
 * @tc.name: ListLayoutProperty001
 * @tc.desc: Test List layout properties.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListLayoutProperty001, TestSize.Level1)
{
    Create([](ListModelNG model) {
        model.SetSpace(Dimension(10));
        model.SetInitialIndex(1);
        model.SetListDirection(Axis::VERTICAL);
        model.SetScrollBar(Ace::DisplayMode::ON);
        model.SetEditMode(true);
        model.SetChainAnimation(true);
        model.SetEdgeEffect(EdgeEffect::NONE, false);
        model.SetLanes(3);
        model.SetLaneMinLength(Dimension(40));
        model.SetLaneMaxLength(Dimension(60));
        model.SetListItemAlign(V2::ListItemAlign::CENTER);
        model.SetCachedCount(10);
        model.SetSticky(V2::StickyStyle::HEADER);
        model.SetScrollSnapAlign(V2::ScrollSnapAlign::START);
    });

    /**
     * @tc.steps: step1. Call ToJsonValue()
     * @tc.expected: The json value is correct
     */
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json);
    EXPECT_EQ(Dimension::FromString(json->GetString("space")), Dimension(10));
    EXPECT_EQ(json->GetString("initialIndex"), "1");
    EXPECT_EQ(json->GetString("listDirection"), "Axis.Vertical");
    EXPECT_TRUE(json->GetBool("editMode"));
    EXPECT_TRUE(json->GetBool("chainAnimation"));
    EXPECT_EQ(json->GetString("divider"), "");
    EXPECT_EQ(json->GetString("lanes"), "3");
    EXPECT_EQ(Dimension::FromString(json->GetString("laneMinLength")), Dimension(40));
    EXPECT_EQ(Dimension::FromString(json->GetString("laneMaxLength")), Dimension(60));
    EXPECT_EQ(json->GetString("alignListItem"), "ListItemAlign.Center");
    EXPECT_EQ(json->GetString("cachedCount"), "10");
    EXPECT_EQ(json->GetString("sticky"), "StickyStyle.Header");
    EXPECT_EQ(json->GetString("scrollSnapAlign"), "ScrollSnapAlign.START");

    /**
     * @tc.steps: step2. Change some property, Call ToJsonValue()
     * @tc.expected: The json value is correct
     */
    layoutProperty_->UpdateListDirection(Axis::HORIZONTAL);
    layoutProperty_->UpdateListItemAlign(V2::ListItemAlign::END);
    layoutProperty_->UpdateStickyStyle(V2::StickyStyle::FOOTER);
    layoutProperty_->UpdateScrollSnapAlign(V2::ScrollSnapAlign::CENTER);
    layoutProperty_->UpdateDivider(ITEM_DIVIDER);
    json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json);
    EXPECT_EQ(json->GetString("listDirection"), "Axis.Horizontal");
    EXPECT_EQ(json->GetString("alignListItem"), "ListItemAlign.End");
    EXPECT_EQ(json->GetString("sticky"), "StickyStyle.Footer");
    EXPECT_EQ(json->GetString("scrollSnapAlign"), "ScrollSnapAlign.CENTER");
    auto dividerJson = json->GetObject("divider");
    EXPECT_EQ(Dimension::FromString(dividerJson->GetString("strokeWidth")), Dimension(STROKE_WIDTH));
    EXPECT_EQ(Dimension::FromString(dividerJson->GetString("startMargin")), Dimension(10));
    EXPECT_EQ(Dimension::FromString(dividerJson->GetString("endMargin")), Dimension(20));
    EXPECT_EQ(Color::ColorFromString(dividerJson->GetString("color")), Color(0x000000));

    /**
     * @tc.steps: step3. Change some property, Call ToJsonValue()
     * @tc.expected: The json value is changed
     */
    layoutProperty_->UpdateListItemAlign(V2::ListItemAlign::START);
    layoutProperty_->UpdateStickyStyle(V2::StickyStyle::BOTH);
    layoutProperty_->UpdateScrollSnapAlign(V2::ScrollSnapAlign::END);
    json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json);
    EXPECT_EQ(json->GetString("alignListItem"), "ListItemAlign.Start");
    EXPECT_EQ(json->GetString("sticky"), "StickyStyle.Header | StickyStyle.Footer");
    EXPECT_EQ(json->GetString("scrollSnapAlign"), "ScrollSnapAlign.END");

    /**
     * @tc.steps: step3. Change some property, Call ToJsonValue()
     * @tc.expected: The json value is changed
     */
    layoutProperty_->UpdateStickyStyle(V2::StickyStyle::NONE);
    layoutProperty_->UpdateScrollSnapAlign(V2::ScrollSnapAlign::NONE);
    json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json);
    EXPECT_EQ(json->GetString("sticky"), "StickyStyle.None");
    EXPECT_EQ(json->GetString("scrollSnapAlign"), "ScrollSnapAlign.NONE");

    /**
     * @tc.steps: step4. The json include strokeWidth and Change it, call FromJson()
     * @tc.expected: The layoutProperty_->GetDividerValue().strokeWidth changed
     */
    dividerJson = json->GetObject("divider");
    dividerJson->Replace("strokeWidth", Dimension(20).ToString().c_str());
    layoutProperty_->FromJson(json);
    EXPECT_EQ(layoutProperty_->GetDividerValue().strokeWidth, Dimension(20));

    /**
     * @tc.steps: step5. The json not include strokeWidth, call FromJson()
     * @tc.expected: The layoutProperty_->GetDividerValue() not changed
     */
    dividerJson->Delete("strokeWidth");
    layoutProperty_->FromJson(json);
    EXPECT_EQ(layoutProperty_->GetDividerValue().strokeWidth, Dimension(20));
}

/**
 * @tc.name: ListItemLayoutProperty001
 * @tc.desc: Test ListItem layout properties.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemLayoutProperty001, TestSize.Level1)
{
    CreateWithItem([](ListModelNG model) {});
    auto layoutProperty = GetChildLayoutProperty<ListItemLayoutProperty>(frameNode_, 0);

    /**
     * @tc.steps: step1. Call ToJsonValue()
     * @tc.expected: The json value is correct
     */
    auto json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json);
    EXPECT_EQ(static_cast<V2::StickyMode>(json->GetInt("sticky")), V2::StickyMode::NONE);
    EXPECT_FALSE(json->GetBool("editable"));
    EXPECT_EQ(Dimension::FromString(json->GetString("startDeleteAreaDistance")), Dimension(0, DimensionUnit::VP));
    EXPECT_EQ(Dimension::FromString(json->GetString("endDeleteAreaDistance")), Dimension(0, DimensionUnit::VP));

    /**
     * @tc.steps: step2. Change some property, Call ToJsonValue()
     * @tc.expected: The json value is correct
     */
    layoutProperty->UpdateStickyMode(V2::StickyMode::NORMAL);
    layoutProperty->UpdateEditMode(V2::EditMode::NONE);
    layoutProperty->UpdateEdgeEffect(V2::SwipeEdgeEffect::Spring);
    json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json);
    EXPECT_EQ(json->GetString("sticky"), "Sticky.Normal");
    EXPECT_EQ(json->GetString("editable"), "EditMode.None");
    auto swipeAction = json->GetObject("swipeAction");
    EXPECT_EQ(static_cast<V2::SwipeEdgeEffect>(swipeAction->GetInt("edgeEffect")), V2::SwipeEdgeEffect::Spring);

    /**
     * @tc.steps: step3. Change some property, Call ToJsonValue()
     * @tc.expected: The json value is correct
     */
    layoutProperty->UpdateStickyMode(V2::StickyMode::OPACITY);
    layoutProperty->UpdateEditMode(V2::EditMode::MOVABLE);
    layoutProperty->UpdateEdgeEffect(V2::SwipeEdgeEffect::None);
    json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json);
    EXPECT_EQ(json->GetString("sticky"), "Sticky.Opacity");
    EXPECT_EQ(json->GetString("editable"), "EditMode.Movable");
    swipeAction = json->GetObject("swipeAction");
    EXPECT_EQ(swipeAction->GetString("edgeEffect"), "SwipeEdgeEffect.Node");

    /**
     * @tc.steps: step4. Change some property, Call ToJsonValue()
     * @tc.expected: The json value is correct
     */
    layoutProperty->UpdateEditMode(V2::EditMode::DELETABLE);
    json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json);
    EXPECT_EQ(json->GetString("editable"), "EditMode.Deletable");

    /**
     * @tc.steps: step5. Change some property, Call ToJsonValue()
     * @tc.expected: The json value is correct
     */
    layoutProperty->UpdateEditMode(V2::EditMode::DELETABLE | V2::EditMode::MOVABLE);
    json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json);
    EXPECT_TRUE(json->GetBool("editable"));
}

/**
 * @tc.name: AttrSpaceDivider001
 * @tc.desc: Test property about space/divider with Axis::VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrSpaceDivider001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set space
     */
    CreateWithItem([](ListModelNG model) { model.SetSpace(Dimension(SPACE)); });
    EXPECT_TRUE(VerifyPosition(frameNode_, VIEW_LINE_NUMBER, DEFAULT_LANES, SPACE, DEFAULT_STARTOFFSET));

    /**
     * @tc.steps: step2. Set divider
     */
    CreateWithItem([](ListModelNG model) { model.SetDivider(ITEM_DIVIDER); });
    EXPECT_TRUE(VerifyPosition(frameNode_, VIEW_LINE_NUMBER, DEFAULT_LANES, STROKE_WIDTH, DEFAULT_STARTOFFSET));

    /**
     * @tc.steps: step3. Set space less than divider's strokeWidth
     * @tc.expected: space was going to be strokeWidth
     */
    CreateWithItem([](ListModelNG model) {
        model.SetSpace(Dimension(STROKE_WIDTH - 1.f));
        model.SetDivider(ITEM_DIVIDER);
    });
    EXPECT_TRUE(VerifyPosition(frameNode_, VIEW_LINE_NUMBER, DEFAULT_LANES, STROKE_WIDTH, DEFAULT_STARTOFFSET));
}

/**
 * @tc.name: AttrSpaceDivider002
 * @tc.desc: Test property about space/divider with Axis::HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrSpaceDivider002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set space
     */
    Create([](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        model.SetSpace(Dimension(SPACE));
        CreateItem(TOTAL_LINE_NUMBER, Axis::HORIZONTAL);
    });
    EXPECT_TRUE(VerifyPosition(frameNode_, VIEW_LINE_NUMBER - 1, DEFAULT_LANES, SPACE, DEFAULT_STARTOFFSET));

    /**
     * @tc.steps: step2. Set divider
     */
    Create([](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        model.SetDivider(ITEM_DIVIDER);
        CreateItem(TOTAL_LINE_NUMBER, Axis::HORIZONTAL);
    });
    EXPECT_TRUE(VerifyPosition(frameNode_, VIEW_LINE_NUMBER, DEFAULT_LANES, STROKE_WIDTH, DEFAULT_STARTOFFSET));

    /**
     * @tc.steps: step3. Set space less than divider's strokeWidth
     * @tc.expected: space was going to be strokeWidth
     */
    Create([](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        model.SetSpace(Dimension(STROKE_WIDTH - 1.f));
        model.SetDivider(ITEM_DIVIDER);
        CreateItem(TOTAL_LINE_NUMBER, Axis::HORIZONTAL);
    });
    EXPECT_TRUE(VerifyPosition(frameNode_, VIEW_LINE_NUMBER, DEFAULT_LANES, STROKE_WIDTH, DEFAULT_STARTOFFSET));
}

/**
 * @tc.name: AttrSpaceDivider003
 * @tc.desc: Test property about space/divider with special value
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrSpaceDivider003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set space to LIST_HEIGHT
     * @tc.expected: space was going to be zero
     */
    CreateWithItem([](ListModelNG model) { model.SetSpace(Dimension(LIST_HEIGHT)); });
    EXPECT_TRUE(VerifyPosition(frameNode_, VIEW_LINE_NUMBER, DEFAULT_LANES, DEFAULT_SPACE, DEFAULT_STARTOFFSET));

    /**
     * @tc.steps: step2. Set strokeWidth to LIST_HEIGHT
     * @tc.expected: strokeWidth was going to be zero
     */
    auto divider = ITEM_DIVIDER;
    divider.strokeWidth = Dimension(LIST_HEIGHT);
    CreateWithItem([divider](ListModelNG model) { model.SetDivider(divider); });
    EXPECT_TRUE(VerifyPosition(frameNode_, VIEW_LINE_NUMBER, DEFAULT_LANES, DEFAULT_SPACE, DEFAULT_STARTOFFSET));
}

/**
 * @tc.name: AttrInitIndex001
 * @tc.desc: Test property about initialIndex with Axis::VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrInitIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set initIndex to 1
     * @tc.expected: List layout starting from initialIndex
     */
    CreateWithItem([](ListModelNG model) { model.SetInitialIndex(1); });
    EXPECT_TRUE(VerifyPosition(frameNode_, VIEW_LINE_NUMBER, DEFAULT_LANES, DEFAULT_SPACE, ITEM_HEIGHT));

    /**
     * @tc.steps: step2. Total ListItem size less than viewport
     * @tc.expected: List layout starting from first ListItem
     */
    Create([](ListModelNG model) {
        model.SetInitialIndex(1);
        CreateItem(5);
    });
    EXPECT_TRUE(VerifyPosition(frameNode_, 5, DEFAULT_LANES, DEFAULT_SPACE, DEFAULT_STARTOFFSET));

    /**
     * @tc.steps: step3. The total size of ListItems after initialIndex is less than viewport
     * @tc.expected: ListItem bottom to viewport
     */
    CreateWithItem([](ListModelNG model) { model.SetInitialIndex(5); });
    EXPECT_TRUE(VerifyPosition(frameNode_, VIEW_LINE_NUMBER, DEFAULT_LANES, DEFAULT_SPACE, ITEM_HEIGHT * 2));

    /**
     * @tc.steps: step4. initialIndex out of range
     * @tc.expected: ignore initialIndex
     */
    CreateWithItem([](ListModelNG model) { model.SetInitialIndex(100); });
    EXPECT_TRUE(VerifyPosition(frameNode_, VIEW_LINE_NUMBER, DEFAULT_LANES, DEFAULT_SPACE, DEFAULT_STARTOFFSET));

    /**
     * @tc.steps: step5. initialIndex is not an integer multiple of the lanes
     * @tc.expected: List layout starting from an index integer multiple of the lanes
     */
    Create([](ListModelNG model) {
        model.SetInitialIndex(3);
        model.SetLanes(2);
        CreateItem(20);
    });
    EXPECT_TRUE(VerifyPosition(frameNode_, 16, 2, DEFAULT_SPACE, ITEM_HEIGHT));
}

/**
 * @tc.name: AttrInitIndex002
 * @tc.desc: Test property about initialIndex with Axis::HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrInitIndex002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set initIndex to 1
     * @tc.expected: List layout starting from initialIndex
     */
    Create([](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        model.SetInitialIndex(1);
        CreateItem(TOTAL_LINE_NUMBER, Axis::HORIZONTAL);
    });
    EXPECT_TRUE(VerifyPosition(frameNode_, VIEW_LINE_NUMBER, DEFAULT_LANES, DEFAULT_SPACE, ITEM_WIDTH));

    /**
     * @tc.steps: step2. Total ListItem size less than viewport
     * @tc.expected: List layout starting from first ListItem
     */
    Create([](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        model.SetInitialIndex(1);
        CreateItem(5, Axis::HORIZONTAL);
    });
    EXPECT_TRUE(VerifyPosition(frameNode_, 5, DEFAULT_LANES, DEFAULT_SPACE, DEFAULT_STARTOFFSET));

    /**
     * @tc.steps: step3. The total size of ListItems after initialIndex is less than viewport
     * @tc.expected: ListItem bottom to viewport
     */
    Create([](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        model.SetInitialIndex(5);
        CreateItem(TOTAL_LINE_NUMBER, Axis::HORIZONTAL);
    });
    EXPECT_TRUE(VerifyPosition(frameNode_, VIEW_LINE_NUMBER, DEFAULT_LANES, DEFAULT_SPACE, ITEM_WIDTH * 2));

    /**
     * @tc.steps: step4. initialIndex out of range
     * @tc.expected: ignore initialIndex
     */
    Create([](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        model.SetInitialIndex(100);
        CreateItem(TOTAL_LINE_NUMBER, Axis::HORIZONTAL);
    });
    EXPECT_TRUE(VerifyPosition(frameNode_, VIEW_LINE_NUMBER, DEFAULT_LANES, DEFAULT_SPACE, DEFAULT_STARTOFFSET));

    /**
     * @tc.steps: step5. initialIndex is not an integer multiple of the lanes
     * @tc.expected: List layout starting from an index integer multiple of the lanes
     */
    Create([](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        model.SetInitialIndex(3);
        model.SetLanes(2);
        CreateItem(20, Axis::HORIZONTAL);
    });
    EXPECT_TRUE(VerifyPosition(frameNode_, 16, 2, DEFAULT_SPACE, ITEM_WIDTH));
}

/**
 * @tc.name: AttrScrollBar001
 * @tc.desc: Test property about scrollBar
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrScrollBar001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set scrollBar
     */
    CreateWithItem([](ListModelNG model) { model.SetScrollBar(Ace::DisplayMode::ON); });
    EXPECT_EQ(pattern_->GetScrollBar()->GetDisplayMode(), DisplayMode::ON);

    /**
     * @tc.steps: step1. Set scrollBar, set api version >= 10
     * @tc.expected: the default value is auto
     */
    MockPipelineContext::pipeline_->SetMinPlatformVersion(PLATFORM_VERSION_TEN);
    CreateWithItem([](ListModelNG model) {});
    EXPECT_EQ(pattern_->GetScrollBar()->GetDisplayMode(), DisplayMode::AUTO);
}

/**
 * @tc.name: AttrLanes001
 * @tc.desc: Test property about lanes with VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrLanes001, TestSize.Level1)
{
    Create([](ListModelNG model) {
        model.SetLanes(2);
        CreateItem(19);
    });
    EXPECT_TRUE(VerifyPosition(frameNode_, 16, 2, DEFAULT_SPACE, DEFAULT_STARTOFFSET));
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM);
    EXPECT_TRUE(VerifyPosition(frameNode_, 15, 2, DEFAULT_SPACE, ITEM_HEIGHT * 2));
}

/**
 * @tc.name: AttrLanes002
 * @tc.desc: Test property about lanes with HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrLanes002, TestSize.Level1)
{
    Create([](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        model.SetLanes(2);
        CreateItem(19, Axis::HORIZONTAL);
    });
    EXPECT_TRUE(VerifyPosition(frameNode_, 16, 2, DEFAULT_SPACE, DEFAULT_STARTOFFSET));
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM);
    EXPECT_TRUE(VerifyPosition(frameNode_, 15, 2, DEFAULT_SPACE, ITEM_WIDTH * 2));
}

/**
 * @tc.name: AttrLanes003
 * @tc.desc: Test LayoutProperty about minLaneLength/maxLaneLength with VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrLanes003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. SetLaneMinLength half of LIST_WIDTH
     * @tc.expected: List would has 2 lanes
     */
    Create([](ListModelNG model) {
        model.SetLaneMinLength(Dimension(LIST_WIDTH / 2 - 1));
        model.SetLaneMaxLength(Dimension(LIST_WIDTH));
        CreateItem(19);
    });
    EXPECT_TRUE(VerifyPosition(frameNode_, 16, 2, DEFAULT_SPACE, DEFAULT_STARTOFFSET));
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM);
    EXPECT_TRUE(VerifyPosition(frameNode_, 15, 2, DEFAULT_SPACE, ITEM_HEIGHT * 2));

    /**
     * @tc.steps: step2. Check ListItem width.
     * @tc.expected: ListItem width would self-adaption.
     */
    for (int32_t index = 0; index < 15; index++) {
        EXPECT_FLOAT_EQ(GetChildRect(frameNode_, index).Width(), LIST_WIDTH / 2);
    }
}

/**
 * @tc.name: AttrLanes004
 * @tc.desc: Test LayoutProperty about minLaneLength/maxLaneLength with HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrLanes004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. SetLaneMinLength half of LIST_HEIGHT
     * @tc.expected: List would has 2 lanes
     */
    Create([](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        model.SetLaneMinLength(Dimension(LIST_HEIGHT / 2 - 1));
        model.SetLaneMaxLength(Dimension(LIST_HEIGHT));
        CreateItem(19, Axis::HORIZONTAL);
    });
    EXPECT_TRUE(VerifyPosition(frameNode_, 16, 2, DEFAULT_SPACE, DEFAULT_STARTOFFSET));
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM);
    EXPECT_TRUE(VerifyPosition(frameNode_, 15, 2, DEFAULT_SPACE, ITEM_WIDTH * 2));

    /**
     * @tc.steps: step2. Check ListItem height.
     * @tc.expected: ListItem height would self-adaption.
     */
    for (int32_t index = 0; index < 15; index++) {
        EXPECT_FLOAT_EQ(GetChildRect(frameNode_, index).Height(), LIST_HEIGHT / 2);
    }
}

/**
 * @tc.name: AttrLanes005
 * @tc.desc: Test LayoutProperty about minLaneLength, maxLaneLength,
 * when maxLaneLength less than minLaneLength, use minLaneLength
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrLanes005, TestSize.Level1)
{
    const float minLaneLength = LIST_WIDTH / 2 - 1;
    Create([minLaneLength](ListModelNG model) {
        model.SetLaneMinLength(Dimension(minLaneLength));
        model.SetLaneMaxLength(Dimension(minLaneLength - 1));
        CreateItem(19);
    });
    EXPECT_TRUE(VerifyPosition(frameNode_, 16, 2, DEFAULT_SPACE, DEFAULT_STARTOFFSET));

    /**
     * @tc.steps: step1. Check ListItem width.
     * @tc.expected: ListItem width would be minLaneLength.
     */
    for (int32_t index = 0; index < 16; index++) {
        EXPECT_FLOAT_EQ(GetChildRect(frameNode_, index).Width(), minLaneLength);
    }
}

/**
 * @tc.name: AttrLanes006
 * @tc.desc: Test LayoutProperty about laneGutter with VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrLanes006, TestSize.Level1)
{
    const float laneGutter = 16.f;
    const int32_t lanes = 2;
    CreateWithItem([lanes, laneGutter](ListModelNG model) {
        model.SetLanes(lanes);
        model.SetLaneGutter(Dimension(laneGutter));
    });
    float itemWidth = (LIST_WIDTH - laneGutter * (lanes - 1)) / lanes;
    for (int32_t index = 0; index < VIEW_LINE_NUMBER; index++) {
        RectF expectRect = RectF((itemWidth + laneGutter) * (index % lanes), ITEM_HEIGHT * std::floor(index / lanes),
            itemWidth, ITEM_HEIGHT);
        EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, index), expectRect));
    }
}

/**
 * @tc.name: AttrLanes007
 * @tc.desc: Test LayoutProperty about laneGutter with HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrLanes007, TestSize.Level1)
{
    const float laneGutter = 16.f;
    const int32_t lanes = 2;
    Create([lanes, laneGutter](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        model.SetLanes(lanes);
        model.SetLaneGutter(Dimension(laneGutter));
        CreateItem(TOTAL_LINE_NUMBER, Axis::HORIZONTAL);
    });
    float itemHeight = (LIST_HEIGHT - laneGutter * (lanes - 1)) / lanes;
    for (int32_t index = 0; index < VIEW_LINE_NUMBER; index++) {
        RectF expectRect = RectF(ITEM_WIDTH * std::floor(index / lanes), (itemHeight + laneGutter) * (index % lanes),
            ITEM_WIDTH, itemHeight);
        EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, index), expectRect));
    }
}

/**
 * @tc.name: AttrAlignListItem001
 * @tc.desc: Test LayoutProperty about alignListItem with VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrAlignListItem001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set item width smaller than LIST_WIDTH
     * @tc.expected: the item default is align to start
     */
    constexpr float itemWidth = 400.f;
    Create([itemWidth](ListModelNG model) {
        for (int32_t index = 0; index < TOTAL_LINE_NUMBER; index++) {
            ListItemModelNG itemModel;
            itemModel.Create();
            ViewAbstract::SetWidth(CalcLength(itemWidth));
            ViewStackProcessor::GetInstance()->Pop();
        }
    });
    for (int32_t index = 0; index < TOTAL_LINE_NUMBER; index++) {
        EXPECT_EQ(GetChildRect(frameNode_, index).GetX(), 0);
    }

    /**
     * @tc.steps: step2. Set ListItemAlign::CENTER
     * @tc.expected: the item is align to center
     */
    layoutProperty_->UpdateListItemAlign(V2::ListItemAlign::CENTER);
    FlushLayoutTask(frameNode_);
    for (int32_t index = 0; index < TOTAL_LINE_NUMBER; index++) {
        EXPECT_EQ(GetChildRect(frameNode_, index).GetX(), (LIST_WIDTH - itemWidth) / 2);
    }

    /**
     * @tc.steps: step3. Set ListItemAlign::END
     * @tc.expected: the item is align to end
     */
    layoutProperty_->UpdateListItemAlign(V2::ListItemAlign::END);
    FlushLayoutTask(frameNode_);
    for (int32_t index = 0; index < TOTAL_LINE_NUMBER; index++) {
        EXPECT_EQ(GetChildRect(frameNode_, index).GetX(), LIST_WIDTH - itemWidth);
    }
}

/**
 * @tc.name: AttrAlignListItem002
 * @tc.desc: Test LayoutProperty about alignListItem HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrAlignListItem002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set item width smaller than LIST_WIDTH
     * @tc.expected: the item default is align to start
     */
    constexpr float itemHeight = 400.f;
    Create([itemHeight](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        for (int32_t index = 0; index < TOTAL_LINE_NUMBER; index++) {
            ListItemModelNG itemModel;
            itemModel.Create();
            ViewAbstract::SetHeight(CalcLength(itemHeight));
            ViewStackProcessor::GetInstance()->Pop();
        }
    });
    for (int32_t index = 0; index < TOTAL_LINE_NUMBER; index++) {
        EXPECT_EQ(GetChildRect(frameNode_, index).GetY(), 0);
    }

    /**
     * @tc.steps: step2. Set ListItemAlign::CENTER
     * @tc.expected: the item is align to center
     */
    layoutProperty_->UpdateListItemAlign(V2::ListItemAlign::CENTER);
    FlushLayoutTask(frameNode_);
    for (int32_t index = 0; index < TOTAL_LINE_NUMBER; index++) {
        EXPECT_EQ(GetChildRect(frameNode_, index).GetY(), (LIST_HEIGHT - itemHeight) / 2);
    }

    /**
     * @tc.steps: step3. Set ListItemAlign::END
     * @tc.expected: the item is align to end
     */
    layoutProperty_->UpdateListItemAlign(V2::ListItemAlign::END);
    FlushLayoutTask(frameNode_);
    for (int32_t index = 0; index < TOTAL_LINE_NUMBER; index++) {
        EXPECT_EQ(GetChildRect(frameNode_, index).GetY(), LIST_HEIGHT - itemHeight);
    }
}

/**
 * @tc.name: AttrScrollSnapAlign001
 * @tc.desc: Test LayoutProperty about ScrollSnapAlign with VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrScrollSnapAlign001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. V2::ScrollSnapAlign::START
     */
    const float halfItemHeight = ITEM_HEIGHT / 2;
    const float velocity = 1200.f;
    CreateWithItem([](ListModelNG model) { model.SetScrollSnapAlign(V2::ScrollSnapAlign::START); });
    ScrollDown(0.5);
    pattern_->OnScrollSnapCallback(-halfItemHeight, velocity);
    pattern_->HandleScroll(-halfItemHeight, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT));
    ScrollDown(0.5);
    pattern_->OnScrollSnapCallback(-halfItemHeight, velocity);
    pattern_->HandleScroll(-halfItemHeight, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT * 2));

    /**
     * @tc.steps: step2. V2::ScrollSnapAlign::END
     */
    CreateWithItem([](ListModelNG model) { model.SetScrollSnapAlign(V2::ScrollSnapAlign::END); });
    ScrollDown(0.5);
    pattern_->OnScrollSnapCallback(-halfItemHeight, velocity);
    pattern_->HandleScroll(-halfItemHeight, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT));
    ScrollDown(0.5);
    pattern_->OnScrollSnapCallback(-halfItemHeight, velocity);
    pattern_->HandleScroll(-halfItemHeight, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT * 2));

    /**
     * @tc.steps: step3. V2::ScrollSnapAlign::CENTER
     * @tc.expected: The first item is default at center
     */
    CreateWithItem([](ListModelNG model) { model.SetScrollSnapAlign(V2::ScrollSnapAlign::CENTER); });
    EXPECT_TRUE(IsEqualTotalOffset(-ITEM_HEIGHT * 3.5));
    ScrollDown(0.5);
    pattern_->OnScrollSnapCallback(-halfItemHeight, velocity);
    pattern_->HandleScroll(-halfItemHeight, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(-ITEM_HEIGHT * 2.5));
    ScrollDown(0.5);
    pattern_->OnScrollSnapCallback(-halfItemHeight, velocity);
    pattern_->HandleScroll(-halfItemHeight, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(-ITEM_HEIGHT * 1.5));
}

/**
 * @tc.name: AttrScrollSnapAlign002
 * @tc.desc: Test LayoutProperty about ScrollSnapAlign with HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrScrollSnapAlign002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. V2::ScrollSnapAlign::START
     */
    const float halfItemWidth = ITEM_WIDTH / 2;
    const float velocity = 1200.f;
    Create([](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        model.SetScrollSnapAlign(V2::ScrollSnapAlign::START);
        CreateItem(TOTAL_LINE_NUMBER, Axis::HORIZONTAL);
    });
    ScrollDown(0.5);
    pattern_->OnScrollSnapCallback(-halfItemWidth, velocity);
    pattern_->HandleScroll(-halfItemWidth, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_WIDTH));
    ScrollDown(0.5);
    pattern_->OnScrollSnapCallback(-halfItemWidth, velocity);
    pattern_->HandleScroll(-halfItemWidth, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_WIDTH * 2));

    /**
     * @tc.steps: step2. V2::ScrollSnapAlign::END
     */
    Create([](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        model.SetScrollSnapAlign(V2::ScrollSnapAlign::END);
        CreateItem(TOTAL_LINE_NUMBER, Axis::HORIZONTAL);
    });
    ScrollDown(0.5);
    pattern_->OnScrollSnapCallback(-halfItemWidth, velocity);
    pattern_->HandleScroll(-halfItemWidth, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_WIDTH));
    ScrollDown(0.5);
    pattern_->OnScrollSnapCallback(-halfItemWidth, velocity);
    pattern_->HandleScroll(-halfItemWidth, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_WIDTH * 2));

    /**
     * @tc.steps: step3. V2::ScrollSnapAlign::CENTER
     * @tc.expected: The first item is default at center
     */
    Create([](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        model.SetScrollSnapAlign(V2::ScrollSnapAlign::CENTER);
        CreateItem(TOTAL_LINE_NUMBER, Axis::HORIZONTAL);
    });
    EXPECT_TRUE(IsEqualTotalOffset(-ITEM_WIDTH * 3.5));
    ScrollDown(0.5);
    pattern_->OnScrollSnapCallback(-halfItemWidth, velocity);
    pattern_->HandleScroll(-halfItemWidth, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(-ITEM_WIDTH * 2.5));
    ScrollDown(0.5);
    pattern_->OnScrollSnapCallback(-halfItemWidth, velocity);
    pattern_->HandleScroll(-halfItemWidth, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(-ITEM_WIDTH * 1.5));
}

/**
 * @tc.name: AttrScrollSnapAlign003
 * @tc.desc: Test LayoutProperty about ScrollSnapAlign with VERTICAL and different itemHeight
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrScrollSnapAlign003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. V2::ScrollSnapAlign::START
     */
    const float halfItemHeight = ITEM_HEIGHT / 2;
    const float velocity = 1200.f;
    CreateWithItem([](ListModelNG model) { model.SetScrollSnapAlign(V2::ScrollSnapAlign::START); });
    GetChildLayoutProperty<ListItemLayoutProperty>(frameNode_, 1)
        ->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(ITEM_HEIGHT * 1.5)));
    ScrollDown(0.5);
    pattern_->OnScrollSnapCallback(-halfItemHeight, velocity);
    pattern_->HandleScroll(-halfItemHeight, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT));
    ScrollDown(1);
    pattern_->OnScrollSnapCallback(-halfItemHeight, velocity);
    pattern_->HandleScroll(-halfItemHeight, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT * 2.5));

    /**
     * @tc.steps: step2. V2::ScrollSnapAlign::END
     */
    CreateWithItem([](ListModelNG model) { model.SetScrollSnapAlign(V2::ScrollSnapAlign::END); });
    GetChildLayoutProperty<ListItemLayoutProperty>(frameNode_, 1)
        ->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(ITEM_HEIGHT * 1.5)));
    ScrollDown(0.5);
    pattern_->OnScrollSnapCallback(-halfItemHeight, velocity);
    pattern_->HandleScroll(-halfItemHeight, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT));
    ScrollDown(1);
    pattern_->OnScrollSnapCallback(-halfItemHeight, velocity);
    pattern_->HandleScroll(-halfItemHeight, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT * 2.5));

    /**
     * @tc.steps: step3. V2::ScrollSnapAlign::CENTER
     * @tc.expected: The first item is default at center
     */
    CreateWithItem([](ListModelNG model) { model.SetScrollSnapAlign(V2::ScrollSnapAlign::CENTER); });
    GetChildLayoutProperty<ListItemLayoutProperty>(frameNode_, 1)
        ->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(ITEM_HEIGHT * 1.5)));
    EXPECT_TRUE(IsEqualTotalOffset(-ITEM_HEIGHT * 3.5));
    ScrollDown(0.5);
    pattern_->OnScrollSnapCallback(-halfItemHeight, velocity);
    pattern_->HandleScroll(-halfItemHeight, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(-ITEM_HEIGHT * 2.5));
    ScrollDown(0.5);
    pattern_->OnScrollSnapCallback(-0.75 * ITEM_HEIGHT, velocity);
    pattern_->HandleScroll(-0.75 * ITEM_HEIGHT, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(-ITEM_HEIGHT * 1.25));
}

/**
 * @tc.name: AttrScrollSnapAlign004
 * @tc.desc: Test LayoutProperty about ScrollSnapAlign FixPredictSnapOffsetAlignStart/Center
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrScrollSnapAlign004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. V2::ScrollSnapAlign::START
     */
    float contentMainSize = TOTAL_LINE_NUMBER * ITEM_HEIGHT;
    const float halfItemHeight = ITEM_HEIGHT / 2;
    const float velocity = 1200.f;
    CreateWithItem([](ListModelNG model) { model.SetScrollSnapAlign(V2::ScrollSnapAlign::START); });
    ScrollUp(0.5);
    pattern_->OnScrollSnapCallback(halfItemHeight, velocity);
    pattern_->HandleScroll(halfItemHeight, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    CreateWithItem([](ListModelNG model) { model.SetScrollSnapAlign(V2::ScrollSnapAlign::START); });
    pattern_->OnScrollSnapCallback(-contentMainSize, velocity);
    pattern_->HandleScroll(-contentMainSize, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(contentMainSize));

    /**
     * @tc.steps: step2. V2::ScrollSnapAlign::END
     */
    CreateWithItem([](ListModelNG model) { model.SetScrollSnapAlign(V2::ScrollSnapAlign::END); });
    ScrollDown(0.5);
    pattern_->OnScrollSnapCallback(-halfItemHeight, velocity);
    pattern_->HandleScroll(-halfItemHeight, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT));

    /**
     * @tc.steps: step3. V2::ScrollSnapAlign::CENTER
     * @tc.expected: The first item is default at center
     */
    CreateWithItem([](ListModelNG model) { model.SetScrollSnapAlign(V2::ScrollSnapAlign::CENTER); });
    EXPECT_TRUE(IsEqualTotalOffset(-ITEM_HEIGHT * 3.5));
    pattern_->OnScrollSnapCallback(contentMainSize / 2, velocity);
    pattern_->HandleScroll(contentMainSize / 2, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(-ITEM_HEIGHT * 3.5 - contentMainSize / 2));
}

/**
 * @tc.name: AttrSLECM001
 * @tc.desc: Test property about scroller/listDirection/edgeEffect/chainAnimation/multiSelectable
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrSLECM001, TestSize.Level1)
{
    CreateWithItem([](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        model.SetEdgeEffect(EdgeEffect::SPRING, false);
        model.SetChainAnimation(true);
        model.SetMultiSelectable(true);
    });

    EXPECT_NE(pattern_->positionController_, nullptr);
    EXPECT_EQ(pattern_->GetAxis(), Axis::HORIZONTAL);
    EXPECT_NE(pattern_->GetScrollEdgeEffect(), nullptr);
    EXPECT_NE(pattern_->chainAnimation_, nullptr);
    EXPECT_TRUE(pattern_->multiSelectable_);
}

/**
 * @tc.name: AttrEnableScrollInteraction001
 * @tc.desc: Test property about enableScrollInteraction.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrEnableScrollInteraction001, TestSize.Level1)
{
    CreateWithItem([](ListModelNG model) { model.SetScrollEnabled(true); });
    EXPECT_TRUE(layoutProperty_->GetScrollEnabledValue());
    CreateWithItem([](ListModelNG model) { model.SetScrollEnabled(false); });
    EXPECT_FALSE(layoutProperty_->GetScrollEnabledValue());
}

/**
 * @tc.name: AttrFriction001
 * @tc.desc: Test SetFriction:friction shouled be more than 0.0,if out of range,should be default value.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrFriction001, TestSize.Level1)
{
    CreateWithItem([](ListModelNG model) { model.SetFriction(0); });
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), DEFAULT_FRICTION);
    CreateWithItem([](ListModelNG model) { model.SetFriction(-1); });
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), DEFAULT_FRICTION);
    CreateWithItem([](ListModelNG model) { model.SetFriction(1); });
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), 1);
}

/**
 * @tc.name: SwiperItem001
 * @tc.desc: Set startNode, List can swipe start but cannot swipe end.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SwiperItem001, TestSize.Level1)
{
    CreateWithSwipe(true, V2::SwipeEdgeEffect::None);
    const int32_t listItemIndex = 0;
    const RefPtr<FrameNode> listItem = GetChildFrameNode(frameNode_, listItemIndex);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
    const int32_t startNodeIndex = 0;
    const int32_t itemNodeIndex = 1;
    const RectF itemNodeInitialRect = RectF(0, 0, LIST_WIDTH, ITEM_HEIGHT);
    const RectF itemNodeSwipeStartRect = RectF(START_NODE_LEN, 0, LIST_WIDTH, ITEM_HEIGHT);
    const float slightSwipeDelta = START_NODE_LEN * SWIPER_TH;
    const float obviousSwipeDelta = START_NODE_LEN * SWIPER_TH + 1;
    const float exceedSwipeDelta = START_NODE_LEN + 1;

    /**
     * @tc.steps: step1. do nothing, verify initial rect.
     * @tc.expected: StartNode not layout
     */
    RectF startNodeRect = GetChildRect(listItem, startNodeIndex);
    RectF itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    RectF expectStartNodeRect = RectF();
    RectF expectItemNodeRect = itemNodeInitialRect;
    EXPECT_TRUE(IsEqual(startNodeRect, expectStartNodeRect));
    EXPECT_TRUE(IsEqual(itemNodeRect, expectItemNodeRect));
    ListItemSwipeIndex swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step2. Swipe end
     * @tc.expected: Can not move, StartNode not layout
     */
    DragSwiperItem(listItemIndex, -START_NODE_LEN);
    startNodeRect = GetChildRect(listItem, startNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectStartNodeRect = RectF();
    expectItemNodeRect = itemNodeInitialRect;
    EXPECT_TRUE(IsEqual(startNodeRect, expectStartNodeRect));
    EXPECT_TRUE(IsEqual(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step3. Swipe start slightly
     * @tc.expected: Can move, StartNode layout, curOffset_ will reset to Zero
     */
    DragSwiperItem(listItemIndex, slightSwipeDelta);
    startNodeRect = GetChildRect(listItem, startNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    // Because when curOffset_ is equal to zero, startNode will not layout
    expectStartNodeRect = RectF(slightSwipeDelta - START_NODE_LEN, 0, START_NODE_LEN, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeInitialRect;
    EXPECT_TRUE(IsEqual(startNodeRect, expectStartNodeRect));
    EXPECT_TRUE(IsEqual(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step4. Swipe start obviously
     * @tc.expected: swiperIndex_ change to SWIPER_START
     */
    DragSwiperItem(listItemIndex, obviousSwipeDelta);
    startNodeRect = GetChildRect(listItem, startNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectStartNodeRect = RectF(0, 0, START_NODE_LEN, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeSwipeStartRect;
    EXPECT_TRUE(IsEqual(startNodeRect, expectStartNodeRect));
    EXPECT_TRUE(IsEqual(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::SWIPER_START);

    /**
     * @tc.steps: step5. Swipe item slightly
     * @tc.expected: swiperIndex_ unchanged
     */
    DragSwiperItem(listItemIndex, -slightSwipeDelta);
    startNodeRect = GetChildRect(listItem, startNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectStartNodeRect = RectF(0, 0, START_NODE_LEN, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeSwipeStartRect;
    EXPECT_TRUE(IsEqual(startNodeRect, expectStartNodeRect));
    EXPECT_TRUE(IsEqual(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::SWIPER_START);

    /**
     * @tc.steps: step6. Swipe item obviously
     * @tc.expected: swiperIndex_ change to ITEM_CHILD
     */
    DragSwiperItem(listItemIndex, -obviousSwipeDelta);
    startNodeRect = GetChildRect(listItem, startNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectStartNodeRect = RectF(-obviousSwipeDelta, 0, START_NODE_LEN, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeInitialRect;
    EXPECT_TRUE(IsEqual(startNodeRect, expectStartNodeRect));
    EXPECT_TRUE(IsEqual(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step7. Swipe item exceed
     * @tc.expected: swiperIndex_ change to SWIPER_START, curOffset_ would be START_NODE_LEN
     */
    DragSwiperItem(listItemIndex, exceedSwipeDelta);
    startNodeRect = GetChildRect(listItem, startNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectStartNodeRect = RectF(0, 0, START_NODE_LEN, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeSwipeStartRect;
    EXPECT_TRUE(IsEqual(startNodeRect, expectStartNodeRect));
    EXPECT_TRUE(IsEqual(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::SWIPER_START);
}

/**
 * @tc.name: SwiperItem002
 * @tc.desc: Set endNode, List can swipe end but cannot swipe start.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SwiperItem002, TestSize.Level1)
{
    CreateWithSwipe(false, V2::SwipeEdgeEffect::None);
    const int32_t listItemIndex = 0;
    const RefPtr<FrameNode> listItem = GetChildFrameNode(frameNode_, listItemIndex);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
    const int32_t endNodeIndex = 0;
    const int32_t itemNodeIndex = 1;
    const RectF itemNodeInitialRect = RectF(0, 0, LIST_WIDTH, ITEM_HEIGHT);
    const RectF itemNodeSwipeEndRect = RectF(-END_NODE_LEN, 0, LIST_WIDTH, ITEM_HEIGHT);
    const float slightSwipeDelta = END_NODE_LEN * SWIPER_TH;
    const float obviousSwipeDelta = END_NODE_LEN * SWIPER_TH + 1;
    const float exceedSwipeDelta = END_NODE_LEN + 1;

    /**
     * @tc.steps: step1. do nothing, verify initial rect.
     * @tc.expected: EndNode not layout
     */
    RectF endNodeRect = GetChildRect(listItem, endNodeIndex);
    RectF itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    RectF expectEndNodeRect = RectF();
    RectF expectItemNodeRect = itemNodeInitialRect;
    EXPECT_TRUE(IsEqual(endNodeRect, expectEndNodeRect));
    EXPECT_TRUE(IsEqual(itemNodeRect, expectItemNodeRect));
    ListItemSwipeIndex swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step2. Swipe start
     * @tc.expected: Can not move, EndNode not layout
     */
    DragSwiperItem(listItemIndex, END_NODE_LEN);
    endNodeRect = GetChildRect(listItem, endNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectEndNodeRect = RectF();
    expectItemNodeRect = itemNodeInitialRect;
    EXPECT_TRUE(IsEqual(endNodeRect, expectEndNodeRect));
    EXPECT_TRUE(IsEqual(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step3. Swipe end slightSwipeDelta
     * @tc.expected: Can move, EndNode layout, curOffset_ will reset to Zero
     */
    DragSwiperItem(listItemIndex, -slightSwipeDelta);
    endNodeRect = GetChildRect(listItem, endNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    // Because when curOffset_ is equal to zero, endNode will not layout
    expectEndNodeRect = RectF(LIST_WIDTH - slightSwipeDelta, 0, END_NODE_LEN, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeInitialRect;
    EXPECT_TRUE(IsEqual(endNodeRect, expectEndNodeRect));
    EXPECT_TRUE(IsEqual(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step4. Swipe end obviously
     * @tc.expected: swiperIndex_ change to SWIPER_END
     */
    DragSwiperItem(listItemIndex, -obviousSwipeDelta);
    endNodeRect = GetChildRect(listItem, endNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectEndNodeRect = RectF(LIST_WIDTH - END_NODE_LEN, 0, END_NODE_LEN, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeSwipeEndRect;
    EXPECT_TRUE(IsEqual(endNodeRect, expectEndNodeRect));
    EXPECT_TRUE(IsEqual(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::SWIPER_END);

    /**
     * @tc.steps: step5. Swipe item slightSwipeDelta
     * @tc.expected: swiperIndex_ unchanged
     */
    DragSwiperItem(listItemIndex, slightSwipeDelta);
    endNodeRect = GetChildRect(listItem, endNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectEndNodeRect = RectF(LIST_WIDTH - END_NODE_LEN, 0, END_NODE_LEN, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeSwipeEndRect;
    EXPECT_TRUE(IsEqual(endNodeRect, expectEndNodeRect));
    EXPECT_TRUE(IsEqual(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::SWIPER_END);

    /**
     * @tc.steps: step6. Swipe item obviously
     * @tc.expected: swiperIndex_ change to ITEM_CHILD
     */
    DragSwiperItem(listItemIndex, obviousSwipeDelta);
    endNodeRect = GetChildRect(listItem, endNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectEndNodeRect = RectF(LIST_WIDTH - END_NODE_LEN + obviousSwipeDelta, 0, END_NODE_LEN, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeInitialRect;
    EXPECT_TRUE(IsEqual(endNodeRect, expectEndNodeRect));
    EXPECT_TRUE(IsEqual(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step7. Swipe end exceed
     * @tc.expected: swiperIndex_ change to SWIPER_END, curOffset_ would be -END_NODE_LEN
     */
    DragSwiperItem(listItemIndex, -exceedSwipeDelta);
    endNodeRect = GetChildRect(listItem, endNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectEndNodeRect = RectF(LIST_WIDTH - END_NODE_LEN, 0, END_NODE_LEN, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeSwipeEndRect;
    EXPECT_TRUE(IsEqual(endNodeRect, expectEndNodeRect));
    EXPECT_TRUE(IsEqual(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::SWIPER_END);
}

/**
 * @tc.name: SwiperItem003
 * @tc.desc: Set startNode and endNode. Drag to left or right with speed.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SwiperItem003, TestSize.Level1)
{
    CreateWithSwipe(true, V2::SwipeEdgeEffect::None);
    int32_t listItemIndex = 0;
    auto listItem = GetChildFrameNode(frameNode_, listItemIndex);
    auto listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
    const float fastSpeed = SWIPER_SPEED_TH + 1;
    const float swipeDelta = 1;

    /**
     * @tc.steps: step1. swiperIndex_ Default is ITEM_CHILD
     */
    ListItemSwipeIndex swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step2. Swipe start fast
     * @tc.expected: swiperIndex_ change to SWIPER_START
     */
    DragSwiperItem(listItemIndex, swipeDelta, fastSpeed);
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::SWIPER_START);

    /**
     * @tc.steps: step3. Swipe item fast
     * @tc.expected: swiperIndex_ change to ITEM_CHILD
     */
    DragSwiperItem(listItemIndex, -swipeDelta, -fastSpeed);
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step4. Swipe end fast
     * @tc.expected: swiperIndex_ change to SWIPER_END
     */
    CreateWithSwipe(false, V2::SwipeEdgeEffect::None);
    listItem = GetChildFrameNode(frameNode_, listItemIndex);
    listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);

    DragSwiperItem(listItemIndex, -swipeDelta, -fastSpeed);
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::SWIPER_END);

    /**
     * @tc.steps: step5. Swipe item fast
     * @tc.expected: swiperIndex_ change to ITEM_CHILD
     */
    DragSwiperItem(listItemIndex, swipeDelta, fastSpeed);
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);
}

/**
 * @tc.name: SwiperItem004
 * @tc.desc: Set startNode and endNode. if drag different ListItem, the previous item would be reset.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SwiperItem004, TestSize.Level1)
{
    CreateWithSwipe(true, V2::SwipeEdgeEffect::None);
    const float fastSpeed = SWIPER_SPEED_TH + 1;
    const float swipeDelta = 1;
    const int32_t firstItemIndex = 0;
    const int32_t secondItemIndex = 1;
    const RefPtr<ListItemPattern> firstItemPattern = GetChildPattern<ListItemPattern>(frameNode_, firstItemIndex);
    const RefPtr<ListItemPattern> secondItemPattern = GetChildPattern<ListItemPattern>(frameNode_, secondItemIndex);

    /**
     * @tc.steps: step1. Swipe first item fast
     * @tc.expected: The first item swiperIndex_ changed.
     */
    DragSwiperItem(firstItemIndex, swipeDelta, fastSpeed);
    ListItemSwipeIndex firstSwiperIndex = firstItemPattern->GetSwiperIndex();
    ListItemSwipeIndex secondSwiperIndex = secondItemPattern->GetSwiperIndex();
    EXPECT_EQ(firstSwiperIndex, ListItemSwipeIndex::SWIPER_START);
    EXPECT_EQ(secondSwiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step2. Swipe second item fast
     * @tc.expected: The second item swiperIndex_ changed, and first item reseted.
     */
    DragSwiperItem(secondItemIndex, swipeDelta, fastSpeed);
    firstSwiperIndex = firstItemPattern->GetSwiperIndex();
    secondSwiperIndex = secondItemPattern->GetSwiperIndex();
    EXPECT_EQ(firstSwiperIndex, ListItemSwipeIndex::ITEM_CHILD);
    EXPECT_EQ(secondSwiperIndex, ListItemSwipeIndex::SWIPER_START);
}

/**
 * @tc.name: SwiperItem005
 * @tc.desc: Set startNode and SwipeEdgeEffect::Spring, can continue to move when swipe exceed listItem size
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SwiperItem005, TestSize.Level1)
{
    CreateWithSwipe(true, V2::SwipeEdgeEffect::Spring);
    const int32_t listItemIndex = 0;
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);

    /**
     * @tc.steps: step1. swipe end exceed listItem size
     * @tc.expected: Can continue to move, and because of GetFriction(), less than move distance
     */
    float moveDelta = -1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_EQ(listItemPattern->curOffset_, moveDelta);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_GT(listItemPattern->curOffset_, moveDelta * 2);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(listItemPattern->curOffset_, 0);

    /**
     * @tc.steps: step2. swipe start exceed listItem size
     * @tc.expected: Can continue to move, and because of GetFriction(), less than move distance
     */
    moveDelta = 1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, START_NODE_LEN);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_EQ(listItemPattern->curOffset_, START_NODE_LEN + moveDelta);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_LT(listItemPattern->curOffset_, START_NODE_LEN + moveDelta * 2);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(listItemPattern->curOffset_, START_NODE_LEN);
}

/**
 * @tc.name: SwiperItem006
 * @tc.desc: Set endNode and SwipeEdgeEffect::Spring, can continue to move when swipe exceed listItem size
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SwiperItem006, TestSize.Level1)
{
    CreateWithSwipe(false, V2::SwipeEdgeEffect::Spring);
    const int32_t listItemIndex = 0;
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);

    /**
     * @tc.steps: step1. swipe start exceed listItem size
     * @tc.expected: Can continue to move, and because of GetFriction(), less than move distance
     */
    float moveDelta = 1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_EQ(listItemPattern->curOffset_, moveDelta);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_LT(listItemPattern->curOffset_, moveDelta * 2);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(listItemPattern->curOffset_, 0);

    /**
     * @tc.steps: step2. swipe end exceed listItem size
     * @tc.expected: Can continue to move, and because of GetFriction(), less than move distance
     */
    moveDelta = -1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -END_NODE_LEN);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_EQ(listItemPattern->curOffset_, -END_NODE_LEN + moveDelta);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_GT(listItemPattern->curOffset_, -END_NODE_LEN + moveDelta * 2);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(listItemPattern->curOffset_, -END_NODE_LEN);
}

/**
 * @tc.name: SwiperItem007
 * @tc.desc: Set startNode, startDeleteArea, deleteAreaDistance SwipeEdgeEffect::None
 * List can swiper right great than START_NODE_LEN
 * if great than START_NODE_LEN + deleteAreaDistance,
 * it will adjust to START_NODE_LEN + deleteAreaDistance
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SwiperItem007, TestSize.Level1)
{
    auto startFunc = GetDefaultSwiperBuilder(START_NODE_LEN);
    SwipeActionItem item = { .builderAction = std::move(startFunc),
        .actionAreaDistance = Dimension(DELETE_AREA_DISTANCE),
        .onDelete = nullptr,
        .onEnterDeleteArea = nullptr,
        .onExitDeleteArea = nullptr,
        .onStateChange = nullptr

    };
    CreateWithSwipeAction(item, true, nullptr, V2::SwipeEdgeEffect::None);
    const int32_t listItemIndex = 0;
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
    EXPECT_NE(listItemPattern, nullptr);
    const float maxDistance = START_NODE_LEN + DELETE_AREA_DISTANCE;

    /**
     * @tc.steps: step1. Swipe start greater than maxDistance
     * @tc.expected: cannot exceed maxDistance
     */
    float moveDelta = 1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, maxDistance);
    EXPECT_FLOAT_EQ(listItemPattern->curOffset_, maxDistance);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_FLOAT_EQ(listItemPattern->curOffset_, maxDistance);
    HandleDragEnd(listItemIndex);
    EXPECT_FLOAT_EQ(listItemPattern->curOffset_, START_NODE_LEN);

    /**
     * @tc.steps: step2. Swipe end
     * @tc.expected: cannot move
     */
    moveDelta = -1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -START_NODE_LEN);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_FLOAT_EQ(listItemPattern->curOffset_, 0);
    HandleDragEnd(listItemIndex);
    EXPECT_FLOAT_EQ(listItemPattern->curOffset_, 0);
}

/**
 * @tc.name: SwiperItem008
 * @tc.desc: Set the swiperAction Attribute for ListItem, set endNode, endDeleteArea, deleteAreaDistance and
 * EdgeEffect is none, List can swiper left great than endNode size, if great than endNode size +
 * deleteAreaDistance, it will adjust to endNode size + deleteAreaDistance
 *
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SwiperItem008, TestSize.Level1)
{
    auto endFunc = GetDefaultSwiperBuilder(END_NODE_LEN);
    SwipeActionItem item = { .builderAction = std::move(endFunc),
        .actionAreaDistance = Dimension(DELETE_AREA_DISTANCE),
        .onDelete = nullptr,
        .onEnterDeleteArea = nullptr,
        .onExitDeleteArea = nullptr,
        .onStateChange = nullptr

    };
    CreateWithSwipeAction(item, false, nullptr, V2::SwipeEdgeEffect::None);
    const int32_t listItemIndex = 0;
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
    const float maxDistance = END_NODE_LEN + DELETE_AREA_DISTANCE;

    /**
     * @tc.steps: step1. Swipe end greater than maxDistance
     * @tc.expected: can exceed maxDistance
     */
    float moveDelta = -1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -maxDistance);
    EXPECT_EQ(listItemPattern->curOffset_, -maxDistance);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_EQ(listItemPattern->curOffset_, -maxDistance);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(listItemPattern->curOffset_, -END_NODE_LEN);

    /**
     * @tc.steps: step1. Swipe start
     * @tc.expected: cannot move
     */
    moveDelta = 1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, END_NODE_LEN);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_EQ(listItemPattern->curOffset_, 0);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(listItemPattern->curOffset_, 0);
}

/**
 * @tc.name: SwiperItem009
 * @tc.desc: Test swiperAction Attribute for ListItem, set startNode, startDeleteArea, deleteAreaDistance and edge
 * effect is spring. move friction take effect when moving to the right distance great than startNode size +
 * deleteAreaDistance
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SwiperItem009, TestSize.Level1)
{
    auto startFunc = GetDefaultSwiperBuilder(START_NODE_LEN);
    SwipeActionState curState = SwipeActionState::COLLAPSED;
    auto onStateChangeFunc = [&curState](SwipeActionState state) { curState = state; };
    Dimension offset;
    auto onOffsetChange = [&offset](int val) { offset = Dimension(val, DimensionUnit::VP); };
    SwipeActionItem item = { .builderAction = std::move(startFunc),
        .actionAreaDistance = Dimension(DELETE_AREA_DISTANCE),
        .onDelete = nullptr,
        .onEnterDeleteArea = nullptr,
        .onExitDeleteArea = nullptr,
        .onStateChange = std::move(onStateChangeFunc) };
    CreateWithSwipeAction(item, true, std::move(onOffsetChange), V2::SwipeEdgeEffect::Spring);
    const int32_t listItemIndex = 0;
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
    const float maxDistance = START_NODE_LEN + DELETE_AREA_DISTANCE;

    /**
     * @tc.steps: step1. Swipe start greater than maxDistance
     * @tc.expected: Can continue to move
     */
    float moveDelta = 1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, maxDistance);
    EXPECT_EQ(listItemPattern->curOffset_, maxDistance);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_GT(listItemPattern->curOffset_, maxDistance);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(listItemPattern->curOffset_, START_NODE_LEN);
    EXPECT_EQ(offset.ConvertToPx(), START_NODE_LEN);

    /**
     * @tc.steps: step2. Swipe end
     * @tc.expected: Can continue to move
     */
    moveDelta = -1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -START_NODE_LEN);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_LT(listItemPattern->curOffset_, 0);
    EXPECT_EQ(offset.ConvertToPx(), listItemPattern->curOffset_);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(listItemPattern->curOffset_, 0);
    EXPECT_EQ(offset.ConvertToPx(), 0);
}

/**
 * @tc.name: SwiperItem010
 * @tc.desc: Test swiperAction Attribute for ListItem, set endNode, endDeleteArea, deleteAreaDistance and edge
 * effect is spring. move friction take effect when moving to the left distance great than endNode size +
 * deleteAreaDistance
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SwiperItem010, TestSize.Level1)
{
    auto endFunc = GetDefaultSwiperBuilder(END_NODE_LEN);
    SwipeActionState curState = SwipeActionState::COLLAPSED;
    auto onStateChangeFunc = [&curState](SwipeActionState state) { curState = state; };
    Dimension offset;
    auto onOffsetChange = [&offset](int val) { offset = Dimension(val, DimensionUnit::VP); };
    SwipeActionItem item = { .builderAction = std::move(endFunc),
        .actionAreaDistance = Dimension(DELETE_AREA_DISTANCE),
        .onDelete = nullptr,
        .onEnterDeleteArea = nullptr,
        .onExitDeleteArea = nullptr,
        .onStateChange = std::move(onStateChangeFunc) };
    CreateWithSwipeAction(item, false, std::move(onOffsetChange), V2::SwipeEdgeEffect::Spring);
    const int32_t listItemIndex = 0;
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
    const float maxDistance = END_NODE_LEN + DELETE_AREA_DISTANCE;
    /**
     * @tc.steps: step1. Swipe end greater than maxDistance
     * @tc.expected: Can continue to move
     */
    float moveDelta = -1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -maxDistance);
    EXPECT_EQ(listItemPattern->curOffset_, -maxDistance);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_LT(listItemPattern->curOffset_, -maxDistance);
    EXPECT_EQ(offset.ConvertToPx(), static_cast<int32_t>(listItemPattern->curOffset_));
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(listItemPattern->curOffset_, -END_NODE_LEN);
    EXPECT_EQ(offset.ConvertToPx(), -END_NODE_LEN);
    EXPECT_EQ(curState, SwipeActionState::EXPANDED);

    /**
     * @tc.steps: step1. Swipe start
     * @tc.expected: Can continue to move
     */
    moveDelta = 1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, END_NODE_LEN);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_GT(listItemPattern->curOffset_, 0);
    EXPECT_EQ(offset.ConvertToPx(), listItemPattern->curOffset_);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(listItemPattern->curOffset_, 0);
    EXPECT_EQ(offset.ConvertToPx(), 0);
}

/**
 * @tc.name: SwiperItem011
 * @tc.desc: Test swiperAction Attribute for ListItem, set enterStartDeleteArea callback and exitStartDeleteArea
 * callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SwiperItem011, TestSize.Level1)
{
    bool isDelete = false;
    bool isEntry = false;
    bool isExit = false;
    auto deleteEvent = [&isDelete]() { isDelete = true; };
    auto enterEvent = [&isEntry]() { isEntry = true; };
    auto exitEvent = [&isExit]() { isExit = true; };
    auto builder = GetDefaultSwiperBuilder(START_NODE_LEN);
    SwipeActionItem item = { .builderAction = std::move(builder),
        .actionAreaDistance = Dimension(DELETE_AREA_DISTANCE),
        .onDelete = std::move(deleteEvent),
        .onEnterDeleteArea = std::move(enterEvent),
        .onExitDeleteArea = std::move(exitEvent),
        .onStateChange = nullptr };
    CreateWithSwipeAction(item, true, nullptr, V2::SwipeEdgeEffect::Spring);
    const int32_t listItemIndex = 0;

    /**
     * @tc.steps: step1. Repeat entry and exit
     */
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, START_NODE_LEN);
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE);
    EXPECT_TRUE(isEntry);
    HandleDragUpdate(listItemIndex, -DELETE_AREA_DISTANCE);
    EXPECT_TRUE(isExit);
    isEntry = false;
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE);
    EXPECT_TRUE(isEntry);
    isExit = false;
    HandleDragUpdate(listItemIndex, -DELETE_AREA_DISTANCE);
    EXPECT_TRUE(isExit);
    HandleDragEnd(listItemIndex);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step2. move middle of DELETE_AREA_DISTANCE and release
     */
    isDelete = false;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE / 2);
    HandleDragEnd(listItemIndex);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step3. move DELETE_AREA_DISTANCE and release
     */
    isDelete = false;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE);
    HandleDragEnd(listItemIndex);
    EXPECT_TRUE(isDelete);

    /**
     * @tc.steps: step4. move exceed DELETE_AREA_DISTANCE and release
     */
    auto itemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
    itemPattern->SwiperReset();
    isDelete = false;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE + 1);
    HandleDragEnd(listItemIndex);
    EXPECT_TRUE(isDelete);
}

/**
 * @tc.name: SwiperItem012
 * @tc.desc: Test swiperAction Attribute for ListItem, set enterEndDeleteArea callback and exitEndDeleteArea
 * callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SwiperItem012, TestSize.Level1)
{
    bool isDelete = false;
    bool isEntry = false;
    bool isExit = false;
    auto deleteEvent = [&isDelete]() { isDelete = true; };
    auto enterEvent = [&isEntry]() { isEntry = true; };
    auto exitEvent = [&isExit]() { isExit = true; };
    auto builder = GetDefaultSwiperBuilder(END_NODE_LEN);
    SwipeActionItem item = { .builderAction = std::move(builder),
        .actionAreaDistance = Dimension(DELETE_AREA_DISTANCE),
        .onDelete = std::move(deleteEvent),
        .onEnterDeleteArea = std::move(enterEvent),
        .onExitDeleteArea = std::move(exitEvent),
        .onStateChange = nullptr };
    CreateWithSwipeAction(item, false, nullptr, V2::SwipeEdgeEffect::Spring);
    const int32_t listItemIndex = 0;
    const float exceedArea = DELETE_AREA_DISTANCE + 1;

    /**
     * @tc.steps: step1. Repeat entry and exit
     */
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -END_NODE_LEN);
    HandleDragUpdate(listItemIndex, -exceedArea);
    EXPECT_TRUE(isEntry);
    HandleDragUpdate(listItemIndex, exceedArea);
    EXPECT_TRUE(isExit);
    isEntry = false;
    HandleDragUpdate(listItemIndex, -exceedArea);
    EXPECT_TRUE(isEntry);
    isExit = false;
    HandleDragUpdate(listItemIndex, exceedArea);
    EXPECT_TRUE(isExit);
    HandleDragEnd(listItemIndex);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step2. move middle of exceedArea and release
     */
    isDelete = false;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -exceedArea / 2);
    HandleDragEnd(listItemIndex);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step3. move exceedArea and release
     */
    isDelete = false;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -exceedArea);
    HandleDragEnd(listItemIndex);
    EXPECT_TRUE(isDelete);

    /**
     * @tc.steps: step4. move exceed exceedArea and release
     */
    auto itemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
    itemPattern->SwiperReset();
    isDelete = false;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -(exceedArea + 1));
    HandleDragEnd(listItemIndex);
    EXPECT_TRUE(isDelete);
}

/**
 * @tc.name: SwiperItem013
 * @tc.desc: Test callback with no start node
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SwiperItem013, TestSize.Level1)
{
    bool isDelete = false;
    bool isEntry = false;
    bool isExit = false;
    auto deleteEvent = [&isDelete]() { isDelete = true; };
    auto enterEvent = [&isEntry]() { isEntry = true; };
    auto exitEvent = [&isExit]() { isExit = true; };
    SwipeActionItem item = { .builderAction = nullptr,
        .actionAreaDistance = Dimension(DELETE_AREA_DISTANCE),
        .onDelete = std::move(deleteEvent),
        .onEnterDeleteArea = std::move(enterEvent),
        .onExitDeleteArea = std::move(exitEvent),
        .onStateChange = nullptr };
    CreateWithSwipeAction(item, true, nullptr, V2::SwipeEdgeEffect::None);
    const int32_t listItemIndex = 0;

    /**
     * @tc.steps: step1. Repeat entry and exit
     */
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE);
    HandleDragUpdate(listItemIndex, 1.f);
    EXPECT_TRUE(isEntry);
    HandleDragUpdate(listItemIndex, -DELETE_AREA_DISTANCE);
    EXPECT_TRUE(isExit);
    isEntry = false;
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE);
    EXPECT_TRUE(isEntry);
    isExit = false;
    HandleDragUpdate(listItemIndex, -DELETE_AREA_DISTANCE);
    EXPECT_TRUE(isExit);
    HandleDragEnd(listItemIndex);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step2. move middle of DELETE_AREA_DISTANCE and release
     */
    isDelete = false;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE / 2);
    HandleDragEnd(listItemIndex);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step3. move exceed DELETE_AREA_DISTANCE and release
     */
    isDelete = false;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE);
    HandleDragUpdate(listItemIndex, 1.f);
    HandleDragEnd(listItemIndex);
    EXPECT_TRUE(isDelete);
}

/**
 * @tc.name: SwiperItem014
 * @tc.desc: Test callback with no end node
 * callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SwiperItem014, TestSize.Level1)
{
    bool isDelete = false;
    bool isEntry = false;
    bool isExit = false;
    auto deleteEvent = [&isDelete]() { isDelete = true; };
    auto enterEvent = [&isEntry]() { isEntry = true; };
    auto exitEvent = [&isExit]() { isExit = true; };
    SwipeActionItem item = { .builderAction = nullptr,
        .actionAreaDistance = Dimension(DELETE_AREA_DISTANCE),
        .onDelete = std::move(deleteEvent),
        .onEnterDeleteArea = std::move(enterEvent),
        .onExitDeleteArea = std::move(exitEvent),
        .onStateChange = nullptr };
    CreateWithSwipeAction(item, false, nullptr, V2::SwipeEdgeEffect::None);
    const int32_t listItemIndex = 0;
    const float exceedArea = DELETE_AREA_DISTANCE + 1;

    /**
     * @tc.steps: step1. Repeat entry and exit
     */
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -exceedArea);
    HandleDragUpdate(listItemIndex, -1.f);
    EXPECT_TRUE(isEntry);
    HandleDragUpdate(listItemIndex, exceedArea);
    EXPECT_TRUE(isExit);
    isEntry = false;
    HandleDragUpdate(listItemIndex, -exceedArea);
    EXPECT_TRUE(isEntry);
    isExit = false;
    HandleDragUpdate(listItemIndex, exceedArea);
    EXPECT_TRUE(isExit);
    HandleDragEnd(listItemIndex);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step2. move middle of exceedArea and release
     */
    isDelete = false;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -exceedArea / 2);
    HandleDragEnd(listItemIndex);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step3. move exceed exceedArea and release
     */
    isDelete = false;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -exceedArea);
    HandleDragUpdate(listItemIndex, -1.f);
    HandleDragEnd(listItemIndex);
    EXPECT_TRUE(isDelete);
}

/**
 * @tc.name: SwiperItem015
 * @tc.desc: Test SetStartNode
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SwiperItem015, TestSize.Level1)
{
    CreateWithSwipe(true, V2::SwipeEdgeEffect::None);
    const int32_t listItemIndex = 0;
    const RefPtr<FrameNode> listItem = GetChildFrameNode(frameNode_, listItemIndex);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
    const int32_t startNodeIndex = 0;
    auto startFunc = GetDefaultSwiperBuilder(START_NODE_LEN);
    RefPtr<NG::UINode> startNode;
    startFunc();
    startNode = NG::ViewStackProcessor::GetInstance()->Finish();
    listItemPattern->SetStartNode(startNode);
    EXPECT_EQ(GetChildFrameNode(listItem, startNodeIndex), startNode);
    listItemPattern->SetStartNode(nullptr);
    EXPECT_EQ(listItemPattern->startNodeIndex_, -1);
}

/**
 * @tc.name: SwiperItem016
 * @tc.desc: Test SetEndNode
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SwiperItem016, TestSize.Level1)
{
    CreateWithSwipe(false, V2::SwipeEdgeEffect::None);
    const int32_t listItemIndex = 0;
    const RefPtr<FrameNode> listItem = GetChildFrameNode(frameNode_, listItemIndex);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
    const int32_t endNodeIndex = 0;
    auto endFunc = GetDefaultSwiperBuilder(END_NODE_LEN);
    RefPtr<NG::UINode> endNode;
    endFunc();
    endNode = NG::ViewStackProcessor::GetInstance()->Finish();
    listItemPattern->SetEndNode(endNode);
    EXPECT_EQ(GetChildFrameNode(listItem, endNodeIndex), endNode);
    listItemPattern->SetEndNode(nullptr);
    EXPECT_EQ(listItemPattern->endNodeIndex_, -1);
}

/**
 * @tc.name: SwiperItem017
 * @tc.desc: Test InitSwiperAction
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SwiperItem017, TestSize.Level1)
{
    CreateWithSwipe(true, V2::SwipeEdgeEffect::None);
    const int32_t listItemIndex = 0;
    const RefPtr<FrameNode> listItem = GetChildFrameNode(frameNode_, listItemIndex);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);

    listItemPattern->curOffset_ = 10.f;
    listItemPattern->OnModifyDone();
    EXPECT_EQ(listItemPattern->curOffset_, 10.f);
    layoutProperty_->UpdateListDirection(Axis::HORIZONTAL);
    listItemPattern->OnModifyDone();
    EXPECT_EQ(listItemPattern->curOffset_, 0.f);
}

/**
 * @tc.name: SwiperItem018
 * @tc.desc: Test swiperAction Attribute for ListItem, set onOffsetChangeCallback & onStateChangeCallback
 * callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SwiperItem018, TestSize.Level1)
{
    bool isDelete = false;
    SwipeActionState curState = SwipeActionState::COLLAPSED;
    Dimension offset;
    auto onOffsetChange = [&offset](int val) { offset = Dimension(val, DimensionUnit::VP); };
    SwipeActionItem item = { .builderAction = GetDefaultSwiperBuilder(START_NODE_LEN),
        .actionAreaDistance = Dimension(DELETE_AREA_DISTANCE),
        .onDelete = [&isDelete]() { isDelete = true; },
        .onEnterDeleteArea = nullptr,
        .onExitDeleteArea = nullptr,
        .onStateChange = [&curState](SwipeActionState state) { curState = state; } };
    CreateWithSwipeAction(item, true, std::move(onOffsetChange), V2::SwipeEdgeEffect::Spring);
    const int32_t listItemIndex = 0;
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);

    /**
     * @tc.steps: step1. Repeat entry and exit
     */
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, START_NODE_LEN);
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE);
    EXPECT_EQ(offset.ConvertToPx(), static_cast<int32_t>(listItemPattern->curOffset_));
    HandleDragUpdate(listItemIndex, -DELETE_AREA_DISTANCE);
    EXPECT_EQ(offset.ConvertToPx(), static_cast<int32_t>(listItemPattern->curOffset_));
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE);
    HandleDragUpdate(listItemIndex, -DELETE_AREA_DISTANCE);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(curState, SwipeActionState::EXPANDED);

    /**
     * @tc.steps: step2. move middle of DELETE_AREA_DISTANCE and release
     */
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE / 2);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(offset.ConvertToPx(), START_NODE_LEN);
    EXPECT_EQ(curState, SwipeActionState::EXPANDED);

    /**
     * @tc.steps: step3. move DELETE_AREA_DISTANCE and release
     */
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(curState, SwipeActionState::ACTIONING);

    /**
     * @tc.steps: step4. move exceed DELETE_AREA_DISTANCE and release
     */
    auto itemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
    itemPattern->SwiperReset();
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE + 1);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(curState, SwipeActionState::ACTIONING);
}

/**
 * @tc.name: SwiperItem019
 * @tc.desc: Test swiperAction Attribute for ListItem, set onOffsetChangeCallback & onStateChangeCallback
 * callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SwiperItem019, TestSize.Level1)
{
    bool isDelete = false;
    SwipeActionState curState = SwipeActionState::COLLAPSED;
    Dimension offset;
    auto onOffsetChange = [&offset](int val) { offset = Dimension(val, DimensionUnit::VP); };
    SwipeActionItem item = { .builderAction = GetDefaultSwiperBuilder(START_NODE_LEN),
        .actionAreaDistance = Dimension(DELETE_AREA_DISTANCE),
        .onDelete = [&isDelete]() { isDelete = true; },
        .onEnterDeleteArea = nullptr,
        .onExitDeleteArea = nullptr,
        .onStateChange = [&curState](SwipeActionState state) { curState = state; } };
    CreateWithSwipeAction(item, false, std::move(onOffsetChange), V2::SwipeEdgeEffect::Spring);
    const int32_t listItemIndex = 0;
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);

    /**
     * @tc.steps: step1. Repeat entry and exit
     */
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -START_NODE_LEN);
    HandleDragUpdate(listItemIndex, -DELETE_AREA_DISTANCE);
    EXPECT_EQ(offset.ConvertToPx(), static_cast<int32_t>(listItemPattern->curOffset_));
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE);
    EXPECT_EQ(offset.ConvertToPx(), static_cast<int32_t>(listItemPattern->curOffset_));
    HandleDragUpdate(listItemIndex, -DELETE_AREA_DISTANCE);
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(curState, SwipeActionState::EXPANDED);

    /**
     * @tc.steps: step2. move middle of DELETE_AREA_DISTANCE and release
     */
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -DELETE_AREA_DISTANCE / 2);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(curState, SwipeActionState::EXPANDED);
    EXPECT_EQ(offset.ConvertToPx(), -START_NODE_LEN);

    /**
     * @tc.steps: step3. move DELETE_AREA_DISTANCE and release
     */
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -DELETE_AREA_DISTANCE);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(curState, SwipeActionState::ACTIONING);

    /**
     * @tc.steps: step4. move exceed DELETE_AREA_DISTANCE and release
     */
    auto itemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
    itemPattern->SwiperReset();
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -DELETE_AREA_DISTANCE - 1);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(curState, SwipeActionState::ACTIONING);
}

/**
 * @tc.name: SwiperItem020
 * @tc.desc: Test closeAllSwipeAction
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SwiperItem020, TestSize.Level1)
{
    auto endFunc = GetDefaultSwiperBuilder(END_NODE_LEN);
    SwipeActionState curState = SwipeActionState::COLLAPSED;
    auto onStateChangeFunc = [&curState](SwipeActionState state) { curState = state; };
    Dimension offset;
    auto onOffsetChange = [&offset](int val) { offset = Dimension(val, DimensionUnit::VP); };
    SwipeActionItem item = { .builderAction = std::move(endFunc),
        .actionAreaDistance = Dimension(DELETE_AREA_DISTANCE),
        .onDelete = nullptr,
        .onEnterDeleteArea = nullptr,
        .onExitDeleteArea = nullptr,
        .onStateChange = std::move(onStateChangeFunc) };
    CreateWithSwipeAction(item, false, std::move(onOffsetChange), V2::SwipeEdgeEffect::Spring);
    const int32_t listItemIndex = 0;
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
    const float maxDistance = END_NODE_LEN + DELETE_AREA_DISTANCE;
    /**
     * @tc.steps: step1. Swipe end greater than maxDistance
     * @tc.expected: Can continue to move
     */
    float moveDelta = -1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -maxDistance);
    HandleDragUpdate(listItemIndex, moveDelta);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(curState, SwipeActionState::EXPANDED);
    OnFinishFunc onFinishCallBack;
    listItemPattern->CloseSwipeAction(std::move(onFinishCallBack));
    EXPECT_EQ(curState, SwipeActionState::COLLAPSED);
}

/**
 * @tc.name: ListItemGroup001
 * @tc.desc: Test ListItemGroup rect and itemPosition with V2::ListItemGroupStyle::NONE
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemGroup001, TestSize.Level1)
{
    Create([](ListModelNG model) { CreateGroupWithSetting(1, Axis::VERTICAL, V2::ListItemGroupStyle::NONE); });
    RefPtr<FrameNode> groupNode = GetChildFrameNode(frameNode_, 0);
    float groupHeight = GROUP_LINE_NUMBER * (ITEM_HEIGHT + SPACE) - SPACE + GROUP_HEADER_LEN * 2;
    RectF groupRect = GetChildRect(frameNode_, 0);
    RectF headRect = GetChildRect(groupNode, 0);
    RectF footRect = GetChildRect(groupNode, 1);
    EXPECT_TRUE(IsEqual(groupRect, RectF(0, 0, LIST_WIDTH, groupHeight)));
    EXPECT_TRUE(IsEqual(headRect, RectF(0, 0, LIST_WIDTH, GROUP_HEADER_LEN)));
    EXPECT_TRUE(IsEqual(footRect, RectF(0, groupHeight - GROUP_HEADER_LEN, LIST_WIDTH, GROUP_HEADER_LEN)));
    EXPECT_TRUE(VerifyPosition(groupNode, GROUP_LINE_NUMBER, DEFAULT_LANES, SPACE, GROUP_HEADER_LEN));
}

/**
 * @tc.name: ListItemGroup002
 * @tc.desc: Test ListItemGroup rect and itemPosition with V2::ListItemGroupStyle::CARD
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemGroup002, TestSize.Level1)
{
    Create([](ListModelNG model) { CreateGroupWithSetting(1, Axis::VERTICAL, V2::ListItemGroupStyle::CARD); });
    RefPtr<FrameNode> groupNode = GetChildFrameNode(frameNode_, 0);
    float groupHeight = GROUP_LINE_NUMBER * (ITEM_HEIGHT + SPACE) - SPACE + GROUP_HEADER_LEN * 2;
    RectF groupRect = GetChildRect(frameNode_, 0);
    RectF headRect = GetChildRect(groupNode, 0);
    RectF footRect = GetChildRect(groupNode, 1);
    EXPECT_TRUE(IsEqual(groupRect, RectF(12.f, 0, -60.f, groupHeight)));
    EXPECT_TRUE(IsEqual(headRect, RectF(0, 0, 456.f, GROUP_HEADER_LEN)));
    EXPECT_TRUE(IsEqual(footRect, RectF(0, groupHeight - GROUP_HEADER_LEN, 456.f, GROUP_HEADER_LEN)));
    EXPECT_TRUE(VerifyPosition(groupNode, GROUP_LINE_NUMBER, DEFAULT_LANES, SPACE, GROUP_HEADER_LEN));
}

/**
 * @tc.name: ListItemGroup003
 * @tc.desc: List set sticky header and footer
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemGroup003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. V2::StickyStyle::HEADER
     * @tc.expected: head is Sticky
     */
    Create([](ListModelNG model) {
        model.SetSticky(V2::StickyStyle::HEADER);
        CreateGroupWithSetting(GROUP_NUMBER, Axis::VERTICAL, V2::ListItemGroupStyle::NONE);
    });
    EXPECT_TRUE(VerifySticky(0, true, 0));
    ScrollDown();
    EXPECT_TRUE(VerifySticky(0, true, ITEM_HEIGHT));

    /**
     * @tc.steps: step2. V2::StickyStyle::FOOTER
     * @tc.expected: foot is Sticky
     */
    Create([](ListModelNG model) {
        model.SetSticky(V2::StickyStyle::FOOTER);
        CreateGroupWithSetting(GROUP_NUMBER, Axis::VERTICAL, V2::ListItemGroupStyle::NONE);
    });
    float expectOffsetY = LIST_HEIGHT - GetChildRect(frameNode_, 0).Height() - GROUP_HEADER_LEN;
    EXPECT_TRUE(VerifySticky(1, false, expectOffsetY));
    ScrollDown();
    EXPECT_TRUE(VerifySticky(1, false, expectOffsetY + ITEM_HEIGHT));

    /**
     * @tc.steps: step3. V2::StickyStyle::BOTH
     * @tc.expected: head/foot is Sticky
     */
    Create([](ListModelNG model) {
        model.SetSticky(V2::StickyStyle::BOTH);
        CreateGroupWithSetting(GROUP_NUMBER, Axis::VERTICAL, V2::ListItemGroupStyle::NONE);
    });
    EXPECT_TRUE(VerifySticky(0, true, 0));
    ScrollDown();
    EXPECT_TRUE(VerifySticky(0, true, ITEM_HEIGHT));
    ScrollUp();

    expectOffsetY = LIST_HEIGHT - GetChildRect(frameNode_, 0).Height() - GROUP_HEADER_LEN;
    EXPECT_TRUE(VerifySticky(1, false, expectOffsetY));
    ScrollDown();
    EXPECT_TRUE(VerifySticky(1, false, expectOffsetY + ITEM_HEIGHT));
}

/**
 * @tc.name: ListItemGroup004
 * @tc.desc: test lanes
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemGroup004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. SetLanes 2
     * @tc.expected: has 2 lanes items
     */
    int32_t lanes = 2;
    Create([lanes](ListModelNG model) {
        model.SetLanes(lanes);
        CreateGroup(1, Axis::VERTICAL);
    });
    RefPtr<FrameNode> groupNode = GetChildFrameNode(frameNode_, 0);
    float groupHeight = GetChildRect(frameNode_, 0).Height();
    EXPECT_EQ(groupHeight, std::ceil(GROUP_LINE_NUMBER / lanes) * 2 * ITEM_HEIGHT);
    EXPECT_FALSE(VerifyPosition(groupNode, GROUP_LINE_NUMBER, lanes, DEFAULT_SPACE, DEFAULT_STARTOFFSET));

    /**
     * @tc.steps: step2. maxLaneLength > LIST_WIDTH
     * @tc.expected: has 1 lanes items
     */
    Create([](ListModelNG model) {
        model.SetLaneMinLength(Dimension(300.f));
        model.SetLaneMaxLength(Dimension(LIST_WIDTH + 100.f));
        CreateGroup(1, Axis::VERTICAL);
    });
    groupNode = GetChildFrameNode(frameNode_, 0);
    float groupWidth = GetChildRect(frameNode_, 0).Width();
    EXPECT_EQ(groupWidth, LIST_WIDTH);
    EXPECT_TRUE(VerifyPosition(groupNode, GROUP_LINE_NUMBER, DEFAULT_LANES, DEFAULT_SPACE, DEFAULT_STARTOFFSET));

    /**
     * @tc.steps: step3. maxLaneLength < LIST_WIDTH
     * @tc.expected: has 1 lanes items
     */
    Create([](ListModelNG model) {
        model.SetLaneMinLength(Dimension(300.f));
        model.SetLaneMaxLength(Dimension(400.f));
        CreateGroup(1, Axis::VERTICAL);
    });
    groupNode = GetChildFrameNode(frameNode_, 0);
    groupWidth = GetChildRect(frameNode_, 0).Width();
    EXPECT_EQ(groupWidth, LIST_WIDTH);
    EXPECT_TRUE(VerifyPosition(groupNode, GROUP_LINE_NUMBER, DEFAULT_LANES, DEFAULT_SPACE, DEFAULT_STARTOFFSET));

    /**
     * @tc.steps: step4. SetLanes 2 with header/footer/space ...
     * @tc.expected: has 2 lanes items
     */
    lanes = 2;
    Create([lanes](ListModelNG model) {
        model.SetLanes(lanes);
        CreateGroupWithSetting(1, Axis::VERTICAL, V2::ListItemGroupStyle::NONE);
    });
    groupNode = GetChildFrameNode(frameNode_, 0);
    EXPECT_FALSE(VerifyPosition(groupNode, GROUP_LINE_NUMBER, lanes, SPACE, GROUP_HEADER_LEN));

    /**
     * @tc.steps: step5. set minLaneLength/maxLaneLength with header/footer/space ...
     * @tc.expected: headWidth would be maxLaneLength
     */
    Create([](ListModelNG model) {
        model.SetLaneMinLength(Dimension(300.f));
        model.SetLaneMaxLength(Dimension(400.f));
        CreateGroupWithSetting(1, Axis::VERTICAL, V2::ListItemGroupStyle::NONE);
    });
    groupNode = GetChildFrameNode(frameNode_, 0);
    float headWidth = GetChildRect(groupNode, 0).Width();
    EXPECT_EQ(headWidth, LIST_WIDTH);
    EXPECT_TRUE(VerifyPosition(groupNode, GROUP_LINE_NUMBER, DEFAULT_LANES, SPACE, GROUP_HEADER_LEN));
}

/**
 * @tc.name: ListItemGroup005
 * @tc.desc: test SetListItemAlign
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemGroup005, TestSize.Level1)
{
    /**
     * @tc.steps: step2. V2::ListItemAlign::START
     */
    const float itemWidth = LIST_WIDTH - 100.f;
    Create([itemWidth](ListModelNG model) {
        model.SetListItemAlign(V2::ListItemAlign::START);
        {
            ListItemGroupModelNG groupModel;
            groupModel.Create(V2::ListItemGroupStyle::NONE);
            for (int32_t index = 0; index < GROUP_LINE_NUMBER; index++) {
                ListItemModelNG itemModel;
                itemModel.Create();
                ViewAbstract::SetWidth(CalcLength(itemWidth));
                ViewAbstract::SetHeight(CalcLength(ITEM_HEIGHT));
                ViewStackProcessor::GetInstance()->Pop();
            }
            ViewStackProcessor::GetInstance()->Pop();
        }
    });
    RefPtr<FrameNode> groupNode = GetChildFrameNode(frameNode_, 0);
    float itemOffsetX = GetChildRect(groupNode, 0).GetX();
    EXPECT_EQ(itemOffsetX, 0);

    /**
     * @tc.steps: step2. V2::ListItemAlign::CENTER
     */
    layoutProperty_->UpdateListItemAlign(V2::ListItemAlign::CENTER);
    FlushLayoutTask(frameNode_);
    groupNode = GetChildFrameNode(frameNode_, 0);
    itemOffsetX = GetChildRect(groupNode, 0).GetX();
    EXPECT_EQ(itemOffsetX, (LIST_WIDTH - itemWidth) / 2);

    /**
     * @tc.steps: step3. V2::ListItemAlign::END
     */
    layoutProperty_->UpdateListItemAlign(V2::ListItemAlign::END);
    FlushLayoutTask(frameNode_);
    groupNode = GetChildFrameNode(frameNode_, 0);
    itemOffsetX = GetChildRect(groupNode, 0).GetX();
    EXPECT_EQ(itemOffsetX, LIST_WIDTH - itemWidth);
}

/**
 * @tc.name: GetOverScrollOffset001
 * @tc.desc: Test GetOverScrollOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, GetOverScrollOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. !IsScrollSnapAlignCenter
     */
    Create([](ListModelNG model) { CreateGroup(2); });

    OverScrollOffset offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    OverScrollOffset expectOffset = { ITEM_HEIGHT, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, -ITEM_HEIGHT };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    ScrollDown();
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    expectOffset = { ITEM_HEIGHT, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, -ITEM_HEIGHT };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    /**
     * @tc.steps: step2. !IsScrollSnapAlignCenter
     */
    Create([](ListModelNG model) { CreateGroup(1); });

    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT * 5);
    expectOffset = { 500, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, -ITEM_HEIGHT };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    ScrollDown();
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    expectOffset = { ITEM_HEIGHT, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, -ITEM_HEIGHT };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    /**
     * @tc.steps: step3. IsScrollSnapAlignCenter
     */
    Create([](ListModelNG model) {
        model.SetScrollSnapAlign(V2::ScrollSnapAlign::CENTER);
        CreateGroup(2);
    });

    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    expectOffset = { ITEM_HEIGHT, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    ScrollDown();
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT * 4);
    expectOffset = { 0, -ITEM_HEIGHT };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    /**
     * @tc.steps: step4. has no group, groupAtStart and groupAtEnd are false
     */
    CreateWithItem([](ListModelNG model) {});
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    expectOffset = { ITEM_HEIGHT, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
}

/**
 * @tc.name: Event001
 * @tc.desc: Test scroll callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Event001, TestSize.Level1)
{
    bool isTrigger = false;
    auto event = [&isTrigger](Dimension offset, ScrollState state) { isTrigger = true; };
    CreateWithItem([event](ListModelNG model) { model.SetOnScroll(event); });

    /**
     * @tc.steps: step1. Cover condition that GetMinPlatformVersion() >= 10  && scrollStop_ && !GetScrollAbort()
     */
    isTrigger = false;
    UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_AXIS);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_BAR);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_ANIMATION);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION_SPRING);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_NONE);
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step2. Cover condition that onScroll && !NearZero(finalOffset)
     */
    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_UPDATE);
    pattern_->OnScrollEndCallback(); // set scrollStop_ to true
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_ANIMATION);
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION_SPRING);
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_NONE);
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_AXIS);
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_BAR);
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION_CONTROLLER);
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_BAR_FLING);
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isTrigger);

    // SetMinPlatformVersion
    MockPipelineContext::pipeline_->SetMinPlatformVersion(PLATFORM_VERSION_TEN - 1);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_AXIS);
    pattern_->OnScrollEndCallback(); // set scrollStop_ to true
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_BAR);
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION_CONTROLLER);
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isTrigger);

    // set back
    MockPipelineContext::pipeline_->SetMinPlatformVersion(PLATFORM_VERSION_TEN);
}

/**
 * @tc.name: Event002
 * @tc.desc: Test scroll callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Event002, TestSize.Level1)
{
    int32_t startIndex;
    int32_t endIndex;
    int32_t centerIndex;
    auto event = [&startIndex, &endIndex, &centerIndex](int32_t start, int32_t end, int32_t center) {
        startIndex = start;
        endIndex = end;
        centerIndex = center;
    };
    CreateWithItem([event](ListModelNG model) { model.SetOnScrollIndex(event); });

    ScrollDown();
    EXPECT_EQ(startIndex, 1);
    EXPECT_EQ(endIndex, 8);
    EXPECT_EQ(centerIndex, 4);

    ScrollDown();
    EXPECT_EQ(startIndex, 2);
    EXPECT_EQ(endIndex, 9);
    EXPECT_EQ(centerIndex, 5);
}

/**
 * @tc.name: Event003
 * @tc.desc: Test scroll callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Event003, TestSize.Level1)
{
    bool isTrigger = false;
    auto event = [&isTrigger]() { isTrigger = true; };
    CreateWithItem([event](ListModelNG model) { model.SetOnReachStart(event); });

    /**
     * @tc.steps: step1. list first init will trigger ReachStart.
     */
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step2. Scroll to middle.
     */
    isTrigger = false;
    ScrollDown();
    EXPECT_FALSE(isTrigger);

    /**
     * @tc.steps: step3. Scroll up half item.
     */
    UpdateCurrentOffset(ITEM_HEIGHT / 2.0f);

    /**
     * @tc.steps: step4. Scroll up to start
     */
    isTrigger = false;
    ScrollUp(2);
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step5. Scroll down to start
     */
    isTrigger = false;
    ScrollDown(1.5);
    EXPECT_TRUE(isTrigger);
}

/**
 * @tc.name: Event004
 * @tc.desc: Test scroll callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Event004, TestSize.Level1)
{
    bool isTrigger = false;
    auto event = [&isTrigger]() { isTrigger = true; };
    CreateWithItem([event](ListModelNG model) { model.SetOnReachEnd(event); });

    /**
     * @tc.steps: step1. Scroll down to end
     */
    isTrigger = false;
    ScrollDown(3);
    EXPECT_FALSE(isTrigger);

    /**
     * @tc.steps: step2. Scroll up to end
     */
    isTrigger = false;
    ScrollUp();
    EXPECT_TRUE(isTrigger);
}

/**
 * @tc.name: Event005
 * @tc.desc: Verify onScrollStart, onScrollStop callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Event005, TestSize.Level1)
{
    bool isScrollStartCalled = false;
    bool isScrollStopCalled = false;
    auto scrollStart = [&isScrollStartCalled]() { isScrollStartCalled = true; };
    auto scrollStop = [&isScrollStopCalled]() { isScrollStopCalled = true; };
    CreateWithItem([scrollStart, scrollStop](ListModelNG model) {
        model.SetChainAnimation(true);
        model.SetChainAnimationOptions({ Dimension(0), Dimension(10), 0, 0, 0, DEFAULT_STIFFNESS, DEFAULT_DAMPING });
        model.SetOnScrollStart(scrollStart);
        model.SetOnScrollStop(scrollStop);
    });

    pattern_->OnScrollCallback(100.f, SCROLL_FROM_START);
    EXPECT_TRUE(isScrollStartCalled);

    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isScrollStopCalled);

    isScrollStopCalled = false;
    pattern_->OnScrollEndCallback();
    pattern_->SetScrollAbort(true);
    FlushLayoutTask(frameNode_);
    EXPECT_FALSE(isScrollStopCalled);
}

/**
 * @tc.name: Event006
 * @tc.desc: Test other condition
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Event006, TestSize.Level1)
{
    auto event = [](Dimension, ScrollState) {
        ScrollFrameResult result;
        return result;
    };
    CreateWithItem([event](ListModelNG model) { model.SetOnScrollFrameBegin(event); });

    auto scrollableEvent = pattern_->GetScrollableEvent();
    ASSERT_NE(scrollableEvent, nullptr);
    auto scrollable = scrollableEvent->GetScrollable();
    EXPECT_NE(scrollable->callback_, nullptr);
    FlushLayoutTask(frameNode_);
}

/**
 * @tc.name: EventHub001
 * @tc.desc: Test Event hub
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, EventHub001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. EXPECT_CALL DrawFrameNode, HandleOnItemDragStart will trigger it
     */
    auto mockDragWindow = MockDragWindow::CreateDragWindow("", 0, 0, 0, 0);
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(mockDragWindow)), DrawFrameNode(_)).Times(2);

    /**
     * @tc.steps: step2. Run List GetDragExtraParams func.
     * @tc.expected: Would call pattern->GetItemIndexByPosition
     */
    auto onItemDragStart = [](const ItemDragInfo&, int32_t) {
        auto dragItem = AceType::MakeRefPtr<FrameNode>("test", 0, AceType::MakeRefPtr<Pattern>());
        return AceType::DynamicCast<UINode>(dragItem);
    };
    CreateWithItem([onItemDragStart](ListModelNG model) { model.SetOnItemDragStart(onItemDragStart); });
    auto jsonStr = eventHub_->GetDragExtraParams("", Point(0, 250), DragEventType::MOVE);
    EXPECT_EQ(jsonStr, "{\"insertIndex\":2}");

    /**
     * @tc.steps: step3. HandleOnItemDrag to end
     */
    GestureEvent info;
    info.SetGlobalPoint(Point(0, 250.f));
    eventHub_->HandleOnItemDragStart(info);
    EXPECT_EQ(eventHub_->draggedIndex_, 2);
    eventHub_->HandleOnItemDragUpdate(info);
    eventHub_->HandleOnItemDragEnd(info);
    EXPECT_EQ(eventHub_->draggedIndex_, 0);

    /**
     * @tc.steps: step3. HandleOnItemDrag to cancel
     */
    eventHub_->HandleOnItemDragStart(info);
    EXPECT_EQ(eventHub_->draggedIndex_, 2);
    eventHub_->HandleOnItemDragUpdate(info);
    eventHub_->HandleOnItemDragCancel();
    EXPECT_EQ(eventHub_->draggedIndex_, 0);
}

/**
 * @tc.name: EventHub002
 * @tc.desc: Test ListItem Event hub
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, EventHub002, TestSize.Level1)
{
    CreateWithItem([](ListModelNG model) {});
    auto itemEventHub = GetChildFrameNode(frameNode_, 0)->GetEventHub<ListItemEventHub>();
    auto jsonStr = itemEventHub->GetDragExtraParams("", Point(0, 250.f), DragEventType::START);
    EXPECT_EQ(jsonStr, "{\"selectedIndex\":0}");
    jsonStr = itemEventHub->GetDragExtraParams("info", Point(0, 250.f), DragEventType::MOVE);
    EXPECT_EQ(jsonStr, "{\"extraInfo\":\"info\"}");
}

/**
 * @tc.name: MouseSelect001
 * @tc.desc: Test mouse select
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, MouseSelect001, TestSize.Level1)
{
    CreateWithItem([](ListModelNG model) { model.SetMultiSelectable(true); });

    /**
     * @tc.steps: step1. Select zone.
     * @tc.expected: The 1st and 2nd items are selected.
     */
    MouseSelect(Offset(0.f, 0.f), Offset(LIST_WIDTH, 50.f));
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 0)->IsSelected());

    /**
     * @tc.steps: step2. Select from selected zone.
     * @tc.expected: Selected items unchanged.
     */
    MouseSelect(Offset(0.f, 50.f), Offset(LIST_WIDTH, 150.f));
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 0)->IsSelected());
    EXPECT_FALSE(GetChildPattern<ListItemPattern>(frameNode_, 1)->IsSelected());

    /**
     * @tc.steps: step3. Select from unselected zone.
     * @tc.expected: Selected items changed.
     */
    MouseSelect(Offset(0.f, 150.f), Offset(LIST_WIDTH, 170.f));
    EXPECT_FALSE(GetChildPattern<ListItemPattern>(frameNode_, 0)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 1)->IsSelected());

    /**
     * @tc.steps: step4. Click selected zone.
     * @tc.expected: Selected items unchanged.
     */
    MouseSelect(Offset(LIST_WIDTH / 2, 150.f), Offset(LIST_WIDTH / 2, 150.f));
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 1)->IsSelected());

    /**
     * @tc.steps: step5. Click unselected zone.
     * @tc.expected: Each item not selected.
     */
    MouseSelect(Offset(LIST_WIDTH / 2, 50.f), Offset(LIST_WIDTH / 2, 50.f));
    EXPECT_FALSE(GetChildPattern<ListItemPattern>(frameNode_, 0)->IsSelected());
    EXPECT_FALSE(GetChildPattern<ListItemPattern>(frameNode_, 1)->IsSelected());
}

/**
 * @tc.name: MouseSelect002
 * @tc.desc: Test mouse box selection, select from different directiong
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, MouseSelect002, TestSize.Level1)
{
    const Offset LEFT_TOP = Offset(120.f, 250.f);
    const Offset LEFT_BOTTOM = Offset(120.f, 350.f);
    const Offset RIGHT_TOP = Offset(360.f, 250.f);
    const Offset RIGHT_BOTTOM = Offset(360.f, 350.f);
    CreateWithItem([](ListModelNG model) { model.SetMultiSelectable(true); });

    /**
     * @tc.steps: step1. Select from LEFT_TOP to RIGHT_BOTTOM
     */
    MouseSelect(LEFT_TOP, RIGHT_BOTTOM);
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 2)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 3)->IsSelected());
    pattern_->ClearMultiSelect(); // clear all selected
    EXPECT_FALSE(GetChildPattern<ListItemPattern>(frameNode_, 2)->IsSelected());
    EXPECT_FALSE(GetChildPattern<ListItemPattern>(frameNode_, 3)->IsSelected());

    /**
     * @tc.steps: step2. Select from RIGHT_TOP to LEFT_BOTTOM
     */
    MouseSelect(RIGHT_TOP, LEFT_BOTTOM);
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 2)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 3)->IsSelected());
    pattern_->ClearMultiSelect();

    /**
     * @tc.steps: step3. Select from LEFT_BOTTOM to RIGHT_TOP
     */
    MouseSelect(LEFT_BOTTOM, RIGHT_TOP);
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 2)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 3)->IsSelected());
    pattern_->ClearMultiSelect();

    /**
     * @tc.steps: step4. Select from RIGHT_BOTTOM to LEFT_TOP
     */
    MouseSelect(RIGHT_BOTTOM, LEFT_TOP);
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 2)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 3)->IsSelected());
}

/**
 * @tc.name: MouseSelect003
 * @tc.desc: Test listItem selectable property and onSelect callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, MouseSelect003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create listItem and set an unselectable.
     */
    CreateWithItem([](ListModelNG model) { model.SetMultiSelectable(true); });
    bool isFifthItemSelected = false;
    auto selectCallback = [&isFifthItemSelected](bool) { isFifthItemSelected = true; };
    GetChildPattern<ListItemPattern>(frameNode_, 3)->SetSelectable(false);
    GetChildFrameNode(frameNode_, 4)->GetEventHub<ListItemEventHub>()->SetOnSelect(std::move(selectCallback));

    /**
     * @tc.steps: step2. Select zone.
     * @tc.expected: The 4th item is not selected but 5th item is selected.
     */
    MouseSelect(Offset(120.f, 350.f), Offset(360.f, 450.f));
    EXPECT_FALSE(GetChildPattern<ListItemPattern>(frameNode_, 3)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 4)->IsSelected());
    EXPECT_TRUE(isFifthItemSelected);
}

/**
 * @tc.name: AccessibilityProperty001
 * @tc.desc: Test List AccessibilityProperty func
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AccessibilityProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Scrollable List
     */
    CreateWithItem([](ListModelNG model) {});
    EXPECT_TRUE(accessibilityProperty_->IsScrollable());
    EXPECT_EQ(accessibilityProperty_->GetBeginIndex(), 0);
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), VIEW_LINE_NUMBER - 1);
    EXPECT_EQ(accessibilityProperty_->GetCollectionItemCounts(), TOTAL_LINE_NUMBER);

    /**
     * @tc.steps: step2. scroll to second item
     */
    ScrollDown();
    EXPECT_EQ(accessibilityProperty_->GetBeginIndex(), 1);
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), VIEW_LINE_NUMBER);

    /**
     * @tc.steps: step3. unScrollable List
     */
    Create([](ListModelNG model) { CreateItem(VIEW_LINE_NUMBER); });
    EXPECT_FALSE(accessibilityProperty_->IsScrollable());
    EXPECT_EQ(accessibilityProperty_->GetBeginIndex(), 0);
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), VIEW_LINE_NUMBER - 1);
    EXPECT_EQ(accessibilityProperty_->GetCollectionItemCounts(), VIEW_LINE_NUMBER);
}

/**
 * @tc.name: AccessibilityProperty002
 * @tc.desc: Test List SetSpecificSupportAction when scroll to middle
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AccessibilityProperty002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Scroll to Top.
     */
    CreateWithItem([](ListModelNG model) {});
    accessibilityProperty_->ResetSupportAction();
    uint64_t exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), exptectActions);

    /**
     * @tc.steps: step2. Scroll to middle.
     */
    ScrollDown();
    accessibilityProperty_->ResetSupportAction();
    exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), exptectActions);

    /**
     * @tc.steps: step3. Scroll to bottom.
     */
    ScrollDown();
    accessibilityProperty_->ResetSupportAction();
    exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), exptectActions);

    /**
     * @tc.steps: step4. UnScrollable List.
     */
    Create([](ListModelNG model) { CreateItem(VIEW_LINE_NUMBER); });
    accessibilityProperty_->ResetSupportAction();
    EXPECT_EQ(GetActions(accessibilityProperty_), 0);
}

/**
 * @tc.name: AccessibilityProperty003
 * @tc.desc: Test ListItem AccessibilityProperty func
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AccessibilityProperty003, TestSize.Level1)
{
    CreateWithItem([](ListModelNG model) {});
    auto listItem = GetChildFrameNode(frameNode_, 0);
    auto itemAccessibilityProperty = listItem->GetAccessibilityProperty<ListItemAccessibilityProperty>();
    EXPECT_FALSE(itemAccessibilityProperty->IsSelected());

    itemAccessibilityProperty->ResetSupportAction();
    uint64_t exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SELECT);
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_CLEAR_SELECTION);
    EXPECT_EQ(GetActions(itemAccessibilityProperty), exptectActions);
}

/**
 * @tc.name: AccessibilityProperty004
 * @tc.desc: Test ListItemGroup AccessibilityProperty func
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AccessibilityProperty004, TestSize.Level1)
{
    Create(
        [](ListModelNG model) { CreateGroupWithSetting(GROUP_NUMBER, Axis::VERTICAL, V2::ListItemGroupStyle::NONE); });
    auto groupAccessibilityProperty =
        GetChildFrameNode(frameNode_, 0)->GetAccessibilityProperty<ListItemGroupAccessibilityProperty>();
    EXPECT_EQ(groupAccessibilityProperty->GetBeginIndex(), 0);
    EXPECT_EQ(groupAccessibilityProperty->GetEndIndex(), 3);

    groupAccessibilityProperty =
        GetChildFrameNode(frameNode_, 3)->GetAccessibilityProperty<ListItemGroupAccessibilityProperty>();
    EXPECT_EQ(groupAccessibilityProperty->GetBeginIndex(), -1);
    EXPECT_EQ(groupAccessibilityProperty->GetEndIndex(), -1);
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: ListItem Accessibility PerformAction test Select and ClearSelection.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, PerformActionTest001, TestSize.Level1)
{
    Create([](ListModelNG model) { CreateItem(VIEW_LINE_NUMBER); });
    auto listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, 0);
    auto listItemAccessibilityProperty = GetChildAccessibilityProperty<ListItemAccessibilityProperty>(frameNode_, 0);

    /**
     * @tc.steps: step1. When listItem is unSelectable
     * @tc.expected: can not be selected
     */
    listItemPattern->SetSelectable(false);
    listItemAccessibilityProperty->ActActionSelect();
    EXPECT_FALSE(listItemPattern->IsSelected());
    listItemAccessibilityProperty->ActActionClearSelection();
    EXPECT_FALSE(listItemPattern->IsSelected());

    /**
     * @tc.steps: step2. When listItem is Selectable
     * @tc.expected: can be selected
     */
    listItemPattern->SetSelectable(true);
    listItemAccessibilityProperty->ActActionSelect();
    EXPECT_TRUE(listItemPattern->IsSelected());
    listItemAccessibilityProperty->ActActionClearSelection();
    EXPECT_FALSE(listItemPattern->IsSelected());
}

/**
 * @tc.name: PerformActionTest002
 * @tc.desc: List Accessibility PerformAction test ScrollForward and ScrollBackward.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, PerformActionTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. When list is not Scrollable
     * @tc.expected: can not scrollpage
     */
    Create([](ListModelNG model) { CreateItem(VIEW_LINE_NUMBER); });
    accessibilityProperty_->ActActionScrollForward();
    EXPECT_TRUE(IsEqualTotalOffset(0));
    accessibilityProperty_->ActActionScrollBackward();
    EXPECT_TRUE(IsEqualTotalOffset(0));

    /**
     * @tc.steps: step2. When list is Scrollable
     * @tc.expected: can scrollpage
     */
    CreateWithItem([](ListModelNG model) {});
    accessibilityProperty_->ActActionScrollForward();
    EXPECT_TRUE(IsEqualTotalOffset(800.f));
    accessibilityProperty_->ActActionScrollBackward();
    EXPECT_TRUE(IsEqualTotalOffset(0));
}

/**
 * @tc.name: PositionController001
 * @tc.desc: Test PositionController function with Axis::VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, PositionController001, TestSize.Level1)
{
    const int32_t itemNumber = 20;
    Create([itemNumber](ListModelNG model) { CreateItem(itemNumber); });
    auto controller = pattern_->positionController_;

    /**
     * @tc.steps: step1. Verify initial value
     */
    EXPECT_EQ(controller->GetScrollDirection(), Axis::VERTICAL);
    EXPECT_EQ(controller->GetCurrentOffset(), Offset::Zero());

    /**
     * @tc.steps: step2. Test ScrollBy
     */
    controller->ScrollBy(ITEM_WIDTH, ITEM_HEIGHT, false);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT));
    controller->ScrollBy(ITEM_WIDTH, -ITEM_HEIGHT, false);
    EXPECT_TRUE(IsEqualTotalOffset(0));

    /**
     * @tc.steps: step3. Test ScrollPage
     */
    controller->ScrollPage(false, true);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT * VIEW_LINE_NUMBER));
    controller->ScrollPage(true, true);
    EXPECT_TRUE(IsEqualTotalOffset(0));

    /**
     * @tc.steps: step4. Test ScrollToEdge
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_TRUE(IsEqualTotalOffset((itemNumber - VIEW_LINE_NUMBER) * ITEM_HEIGHT));
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    EXPECT_TRUE(IsEqualTotalOffset(0));
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_NONE, false);
    EXPECT_TRUE(IsEqualTotalOffset(0));

    /**
     * @tc.steps: step5. Test JumpTo
     */
    controller->JumpTo(1, false, ScrollAlign::START, 0);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT));
    controller->JumpTo(0, false, ScrollAlign::NONE, 0);
    EXPECT_TRUE(IsEqualTotalOffset(0));

    /**
     * @tc.steps: step6. Test IsAtEnd
     */
    EXPECT_FALSE(controller->IsAtEnd());
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM);
    EXPECT_TRUE(controller->IsAtEnd());
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP);
    EXPECT_FALSE(controller->IsAtEnd());

    /**
     * @tc.steps: step7. Test AnimateTo
     */
    EXPECT_FALSE(controller->AnimateTo(Dimension(1, DimensionUnit::PERCENT), 0, nullptr, false));
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 0, nullptr, false));
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 0, nullptr, true));
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 1.0, nullptr, false));
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 1.0, nullptr, true));
    RefPtr<Curve> curve;
    std::string icurveString = "spring(7.000000,1.000000,227.000000,33.000000)";
    curve = Framework::CreateCurve(icurveString);
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 1.0, curve, false));
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 1.0, curve, true));
    curve = Curves::EASE_IN;
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 1.0, curve, false));
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 1.0, curve, true));
}

/**
 * @tc.name: PositionController002
 * @tc.desc: Test PositionController function with Axis::HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, PositionController002, TestSize.Level1)
{
    constexpr int32_t itemNumber = 20;
    Create([itemNumber](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        CreateItem(itemNumber, Axis::HORIZONTAL);
    });
    auto controller = pattern_->positionController_;

    /**
     * @tc.steps: step1. Verify initial value
     */
    EXPECT_EQ(controller->GetScrollDirection(), Axis::HORIZONTAL);
    EXPECT_EQ(controller->GetCurrentOffset(), Offset::Zero());

    /**
     * @tc.steps: step2. Test ScrollBy
     */
    controller->ScrollBy(ITEM_WIDTH, ITEM_HEIGHT, false);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_WIDTH));
    controller->ScrollBy(-ITEM_WIDTH, ITEM_HEIGHT, false);
    EXPECT_TRUE(IsEqualTotalOffset(0));

    /**
     * @tc.steps: step3. Test ScrollPage
     */
    controller->ScrollPage(false, true);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_WIDTH * VIEW_LINE_NUMBER));
    controller->ScrollPage(true, true);
    EXPECT_TRUE(IsEqualTotalOffset(0));

    /**
     * @tc.steps: step4. Test ScrollToEdge
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_TRUE(IsEqualTotalOffset((itemNumber - VIEW_LINE_NUMBER) * ITEM_WIDTH));
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    EXPECT_TRUE(IsEqualTotalOffset(0));
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_NONE, false);
    EXPECT_TRUE(IsEqualTotalOffset(0));

    /**
     * @tc.steps: step5. Test JumpTo
     */
    controller->JumpTo(1, false, ScrollAlign::START, -1);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_WIDTH));
    controller->JumpTo(0, false, ScrollAlign::START, -1);
    EXPECT_TRUE(IsEqualTotalOffset(0));

    /**
     * @tc.steps: step6. Test IsAtEnd
     */
    EXPECT_FALSE(controller->IsAtEnd());
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM);
    EXPECT_TRUE(controller->IsAtEnd());
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP);
    EXPECT_FALSE(controller->IsAtEnd());
}

/**
 * @tc.name: PositionController003
 * @tc.desc: Test PositionController function with Axis::NONE
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, PositionController003, TestSize.Level1)
{
    CreateWithItem([](ListModelNG model) { model.SetListDirection(Axis::NONE); });
    auto controller = pattern_->positionController_;

    /**
     * @tc.steps: step1. Verify initial value
     */
    EXPECT_EQ(controller->GetScrollDirection(), Axis::NONE);
    EXPECT_EQ(controller->GetCurrentOffset(), Offset::Zero());

    /**
     * @tc.steps: step2. Test others
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    EXPECT_TRUE(IsEqualTotalOffset(0));
    controller->ScrollPage(false, true);
    EXPECT_TRUE(IsEqualTotalOffset(0));
    EXPECT_FALSE(controller->AnimateTo(Dimension(1), 0, nullptr, false));
}

/**
 * @tc.name: FocusStep001
 * @tc.desc: Test GetNextFocusNode func with VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, FocusStep001, TestSize.Level1)
{
    Create([](ListModelNG model) { CreateItem(VIEW_LINE_NUMBER, Axis::VERTICAL); });

    /**
     * @tc.steps: step1. GetNextFocusNode from top.
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_VALUE));

    /**
     * @tc.steps: step2. GetNextFocusNode from middle.
     */
    currentIndex = 4;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 3));

    /**
     * @tc.steps: step3. GetNextFocusNode from bottom.
     */
    currentIndex = 7;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 6));
}

/**
 * @tc.name: FocusStep002
 * @tc.desc: Test GetNextFocusNode func width HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, FocusStep002, TestSize.Level1)
{
    Create([](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        CreateItem(VIEW_LINE_NUMBER, Axis::HORIZONTAL);
    });

    /**
     * @tc.steps: step1. GetNextFocusNode from left.
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_VALUE));

    /**
     * @tc.steps: step2. GetNextFocusNode from middle.
     */
    currentIndex = 4;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 3));

    /**
     * @tc.steps: step3. GetNextFocusNode from right.
     */
    currentIndex = 7;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 6));
}

/**
 * @tc.name: FocusStep003
 * @tc.desc: Test GetNextFocusNode when List has ListItemGroup with VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, FocusStep003, TestSize.Level1)
{
    Create([](ListModelNG model) { CreateGroup(2); });

    /**
     * @tc.steps: step1. GetNextFocusNode from top.
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_VALUE));

    /**
     * @tc.steps: step2. GetNextFocusNode from middle of first ListItemGroup.
     */
    currentIndex = 2;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 1));

    /**
     * @tc.steps: step3. GetNextFocusNode from bottom of first ListItemGroup.
     */
    currentIndex = 3;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 2));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 2));

    /**
     * @tc.steps: step4. GetNextFocusNode from top of second ListItemGroup.
     */
    currentIndex = 4;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 3));

    /**
     * @tc.steps: step5. GetNextFocusNode from bottom.
     */
    currentIndex = 7;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 6));
}

/**
 * @tc.name: FocusStep004
 * @tc.desc: Test GetNextFocusNode when List has ListItemGroup with HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, FocusStep004, TestSize.Level1)
{
    Create([](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        CreateGroup(2, Axis::HORIZONTAL);
    });

    /**
     * @tc.steps: step1. GetNextFocusNode from left.
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_VALUE));

    /**
     * @tc.steps: step2. GetNextFocusNode from middle of first ListItemGroup.
     */
    currentIndex = 2;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 1));

    /**
     * @tc.steps: step3. GetNextFocusNode from right of first ListItemGroup.
     */
    currentIndex = 3;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 2));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 2));

    /**
     * @tc.steps: step4. GetNextFocusNode from left of second ListItemGroup.
     */
    currentIndex = 4;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 3));

    /**
     * @tc.steps: step5. GetNextFocusNode from right.
     */
    currentIndex = 7;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 6));
}

/**
 * @tc.name: FocusStep005
 * @tc.desc: Test GetNextFocusNode other condition
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, FocusStep005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. when List has unfocuseable item
     * @tc.expected: The unfocuseable item would be skiped.
     */
    Create([](ListModelNG model) { CreateItem(VIEW_LINE_NUMBER, Axis::VERTICAL); });
    GetChildFocusHub(frameNode_, 1)->SetFocusable(false);
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, 0, 2));

    /**
     * @tc.steps: step2. GetNextFocusNode func from top boundary item
     * @tc.expected: Scroll to last item
     */
    Create([](ListModelNG model) { CreateItem(TOTAL_LINE_NUMBER, Axis::VERTICAL); });
    UpdateCurrentOffset(-ITEM_HEIGHT - 1.f);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT + 1.f));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, 1, 0));
    EXPECT_TRUE(IsEqualTotalOffset(0));

    /**
     * @tc.steps: step3. GetNextFocusNode func from bottom boundary item
     * @tc.expected: Scroll to next item
     */
    Create([](ListModelNG model) { CreateItem(TOTAL_LINE_NUMBER, Axis::VERTICAL); });
    ScrollDown();
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, 8, NULL_VALUE));
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT * 2));

    /**
     * @tc.steps: step4. GetNextFocusNode func from bottom boundary item
     * @tc.expected: Scroll to next item
     */
    // change focus between different group
    const float groupHeight = ITEM_HEIGHT * GROUP_LINE_NUMBER;
    int32_t groupNumber = 3; // create scrollable List
    Create([groupNumber](ListModelNG model) { CreateGroup(groupNumber, Axis::VERTICAL); });
    EXPECT_TRUE(IsEqualTotalOffset(0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, 7, NULL_VALUE));
    EXPECT_TRUE(IsEqualTotalOffset(groupHeight));
    // change focus in same group
    groupNumber = 3; // create scrollable List
    Create([groupNumber](ListModelNG model) { CreateGroup(groupNumber, Axis::VERTICAL); });
    ScrollDown(2);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT * 2));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, 10, NULL_VALUE));
    EXPECT_TRUE(IsEqualTotalOffset(groupHeight / 2));

    /**
     * @tc.steps: step5. GetNextFocusNode func from top boundary item
     * @tc.expected: Scroll to next item
     */
    // change focus between different group
    groupNumber = 3; // create scrollable List
    Create([groupNumber](ListModelNG model) { CreateGroup(groupNumber, Axis::VERTICAL); });
    ScrollDown(GROUP_LINE_NUMBER);
    EXPECT_TRUE(IsEqualTotalOffset(groupHeight));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, 3, 2));
    EXPECT_FALSE(IsEqualTotalOffset(0));
    // change focus in same group
    groupNumber = 3; // create scrollable List
    Create([groupNumber](ListModelNG model) { CreateGroup(groupNumber, Axis::VERTICAL); });
    ScrollDown(3);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT * 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, 2, 1));
    EXPECT_FALSE(IsEqualTotalOffset(0));
}

/**
 * @tc.name: FocusStep006
 * @tc.desc: Test List focusing ability with lanes mode and VERTICAL.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, FocusStep006, TestSize.Level1)
{
    Create([](ListModelNG model) {
        model.SetLanes(4);
        CreateItem(10, Axis::VERTICAL);
    });

    /**
     * @tc.steps: step1. GetNextFocusNode from left_top.
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_VALUE));

    /**
     * @tc.steps: step2. GetNextFocusNode from right_top.
     */
    currentIndex = 3;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 2));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 2));

    /**
     * @tc.steps: step3. GetNextFocusNode from left_bottom.
     */
    currentIndex = 8;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 7));

    /**
     * @tc.steps: step4. GetNextFocusNode from right_bottom.
     */
    currentIndex = 9;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 8));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 8));

    /**
     * @tc.steps: step5. GetNextFocusNode from middle.
     */
    currentIndex = 5;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 4));
}

/**
 * @tc.name: FocusStep007
 * @tc.desc: Test List focusing ability with lanes mode and HORIZONTAL.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, FocusStep007, TestSize.Level1)
{
    Create([](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        model.SetLanes(4);
        CreateItem(10, Axis::HORIZONTAL);
    });

    /**
     * @tc.steps: step1. GetNextFocusNode from left_top.
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_VALUE));

    /**
     * @tc.steps: step2. GetNextFocusNode from right_top.
     */
    currentIndex = 8;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 7));

    /**
     * @tc.steps: step3. GetNextFocusNode from left_bottom.
     */
    currentIndex = 3;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 2));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 2));

    /**
     * @tc.steps: step4. GetNextFocusNode from right_bottom.
     */
    currentIndex = 9;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 8));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 8));

    /**
     * @tc.steps: step5. GetNextFocusNode from middle.
     */
    currentIndex = 5;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 4));
}

/**
 * @tc.name: FocusStep008
 * @tc.desc: Test List focusing ability with ListItemGroup and lanes mode and VERTICAL.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, FocusStep008, TestSize.Level1)
{
    Create([](ListModelNG model) {
        model.SetLanes(2);
        CreateGroup(2, Axis::VERTICAL);
    });

    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 2));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_VALUE));

    currentIndex = 3;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 2));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 2));

    currentIndex = 4;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 3));

    currentIndex = 7;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 6));
}

/**
 * @tc.name: FocusStep009
 * @tc.desc: Test List focusing ability with ListItemGroup and lanes mode and HORIZONTAL.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, FocusStep009, TestSize.Level1)
{
    Create([](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        model.SetLanes(2);
        CreateGroup(2, Axis::HORIZONTAL);
    });

    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 2));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_VALUE));

    currentIndex = 3;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 2));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 2));

    currentIndex = 4;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 3));

    currentIndex = 7;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 6));
}

/**
 * @tc.name: KeyEvent001
 * @tc.desc: Test list_pattern OnKeyEvent function
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, KeyEvent001, TestSize.Level1)
{
    CreateWithItem([](ListModelNG model) {});

    /**
     * @tc.steps: step1. Test other KeyEvent.
     * @tc.expected: CurrentOffset unchanged.
     */
    pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_UNKNOWN, KeyAction::UNKNOWN));
    EXPECT_TRUE(IsEqualTotalOffset(0));
    pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_UNKNOWN, KeyAction::DOWN));
    EXPECT_TRUE(IsEqualTotalOffset(0));

    /**
     * @tc.steps: step2. Test active KeyEvent.
     * @tc.expected: CurrentOffset changed.
     */
    pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_PAGE_DOWN, KeyAction::DOWN));
    EXPECT_TRUE(IsEqualTotalOffset(800.f));
    pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_PAGE_UP, KeyAction::DOWN));
    EXPECT_TRUE(IsEqualTotalOffset(0));
}

/**
 * @tc.name: PaintMethod001
 * @tc.desc: Test List paint method about UpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, PaintMethod001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Not set divider
     * @tc.expected: modifier dividerInfo_ has no value.
     */
    CreateWithItem([](ListModelNG model) {});
    UpdateContentModifier();
    auto dividerInfo = pattern_->listContentModifier_->dividerInfo_;
    EXPECT_FALSE(dividerInfo.has_value());

    /**
     * @tc.steps: step2. Set chainAnimation and divider
     * @tc.expected: modifier dividerInfo_ has no value.
     */
    V2::ItemDivider itemDivider = ITEM_DIVIDER;
    CreateWithItem([itemDivider](ListModelNG model) {
        model.SetDivider(itemDivider);
        model.SetChainAnimation(true);
    });
    UpdateContentModifier();
    dividerInfo = pattern_->listContentModifier_->dividerInfo_;
    EXPECT_FALSE(dividerInfo.has_value());

    /**
     * @tc.steps: step3. Set divider strokeWidth less than zero
     * @tc.expected: modifier dividerInfo_ has no value.
     */
    itemDivider = ITEM_DIVIDER;
    itemDivider.strokeWidth = Dimension(-1);
    CreateWithItem([itemDivider](ListModelNG model) { model.SetDivider(itemDivider); });
    UpdateContentModifier();
    dividerInfo = pattern_->listContentModifier_->dividerInfo_;
    EXPECT_FALSE(dividerInfo.has_value());

    /**
     * @tc.steps: step4. Set divider strokeWidth Unit as PERCENT
     * @tc.expected: modifier dividerInfo_ has no value.
     */
    itemDivider = ITEM_DIVIDER;
    itemDivider.strokeWidth = Dimension(STROKE_WIDTH, DimensionUnit::PERCENT);
    CreateWithItem([itemDivider](ListModelNG model) { model.SetDivider(itemDivider); });
    UpdateContentModifier();
    dividerInfo = pattern_->listContentModifier_->dividerInfo_;
    EXPECT_FALSE(dividerInfo.has_value());

    /**
     * @tc.steps: step5. Not create item
     * @tc.expected: modifier dividerInfo_ has no value.
     */
    itemDivider = ITEM_DIVIDER;
    Create([itemDivider](ListModelNG model) { model.SetDivider(itemDivider); });
    UpdateContentModifier();
    dividerInfo = pattern_->listContentModifier_->dividerInfo_;
    EXPECT_FALSE(dividerInfo.has_value());

    /**
     * @tc.steps: step6. Set divider strokeWidth greater than contentSize(LIST_HEIGHT)
     * @tc.expected: modifier dividerInfo_ has no value.
     */
    itemDivider = ITEM_DIVIDER;
    itemDivider.strokeWidth = Dimension(LIST_HEIGHT + 1);
    CreateWithItem([itemDivider](ListModelNG model) { model.SetDivider(itemDivider); });
    UpdateContentModifier();
    dividerInfo = pattern_->listContentModifier_->dividerInfo_;
    EXPECT_FALSE(dividerInfo.has_value());

    /**
     * @tc.steps: step7. Set divider startMargin + endMargin equal to crossSize(LIST_WIDTH)
     * @tc.expected: modifier dividerInfo_ has no value.
     */
    itemDivider = ITEM_DIVIDER;
    itemDivider.startMargin = Dimension(LIST_WIDTH / 2);
    itemDivider.endMargin = Dimension(LIST_WIDTH / 2);
    CreateWithItem([itemDivider](ListModelNG model) { model.SetDivider(itemDivider); });
    UpdateContentModifier();
    dividerInfo = pattern_->listContentModifier_->dividerInfo_;
    EXPECT_FALSE(dividerInfo.has_value());

    /**
     * @tc.steps: step8. Set divider startMargin + endMargin greater than crossSize(LIST_WIDTH)
     * @tc.expected: modifier dividerInfo_ has value and reset margin to zero.
     */
    itemDivider = ITEM_DIVIDER;
    itemDivider.startMargin = Dimension(LIST_WIDTH / 2);
    itemDivider.endMargin = Dimension(LIST_WIDTH / 2 + 1);
    CreateWithItem([itemDivider](ListModelNG model) { model.SetDivider(itemDivider); });
    UpdateContentModifier();
    dividerInfo = pattern_->listContentModifier_->dividerInfo_;
    EXPECT_TRUE(dividerInfo.has_value());
    EXPECT_EQ(dividerInfo.value().startMargin, 0.f);
    EXPECT_EQ(dividerInfo.value().endMargin, 0.f);

    /**
     * @tc.steps: step9. Set divider startMargin + endMargin less than crossSize(LIST_WIDTH)
     * @tc.expected: modifier dividerInfo_ has value and margin not change
     */
    itemDivider = ITEM_DIVIDER;
    CreateWithItem([itemDivider](ListModelNG model) { model.SetDivider(itemDivider); });
    UpdateContentModifier();
    dividerInfo = pattern_->listContentModifier_->dividerInfo_;
    EXPECT_TRUE(dividerInfo.has_value());
    EXPECT_EQ(dividerInfo.value().startMargin, ITEM_DIVIDER.startMargin.ConvertToPx());
    EXPECT_EQ(dividerInfo.value().endMargin, ITEM_DIVIDER.endMargin.ConvertToPx());
}

/**
 * @tc.name: PaintMethod002
 * @tc.desc: Test List paint method about GetForegroundDrawFunction/PaintEdgeEffect
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, PaintMethod002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set EdgeEffect::FADE
     */
    CreateWithItem([](ListModelNG model) { model.SetEdgeEffect(EdgeEffect::FADE, false); });
    RefPtr<NodePaintMethod> paint = pattern_->CreateNodePaintMethod();
    RefPtr<ListPaintMethod> listPaint = AceType::DynamicCast<ListPaintMethod>(paint);
    auto paintWrapper = frameNode_->CreatePaintWrapper();
    RSCanvas canvas;
    listPaint->GetForegroundDrawFunction(AceType::RawPtr(paintWrapper));
    listPaint->PaintEdgeEffect(AceType::RawPtr(paintWrapper), canvas);
    SUCCEED();
}

/**
 * @tc.name: PaintMethod003
 * @tc.desc: Test List paint method about UpdateOverlayModifier
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, PaintMethod003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test default
     * @tc.expected: The displayMode is AUTO, has scrollbar and on the right
     */
    CreateWithItem([](ListModelNG model) {});
    RefPtr<ListPaintMethod> paint = UpdateOverlayModifier();
    auto scrollBarOverlayModifier = paint->scrollBarOverlayModifier_.Upgrade();
    auto scrollBar = paint->scrollBar_.Upgrade();
    EXPECT_NE(scrollBar, nullptr);
    EXPECT_EQ(scrollBar->displayMode_, DisplayMode::AUTO);
    EXPECT_TRUE(scrollBar->NeedPaint());
    EXPECT_EQ(scrollBarOverlayModifier->positionMode_, PositionMode::RIGHT);

    /**
     * @tc.steps: step2. Update axis
     * @tc.expected: The scrollbar and on the bottom
     */
    layoutProperty_->UpdateListDirection(Axis::HORIZONTAL);
    pattern_->OnModifyDone();
    FlushLayoutTask(frameNode_);
    paint = UpdateOverlayModifier();
    scrollBarOverlayModifier = paint->scrollBarOverlayModifier_.Upgrade();
    scrollBar = paint->scrollBar_.Upgrade();
    EXPECT_NE(scrollBar, nullptr);
    EXPECT_TRUE(scrollBar->NeedPaint());
    EXPECT_EQ(scrollBarOverlayModifier->positionMode_, PositionMode::BOTTOM);

    /**
     * @tc.steps: step3. Set DisplayMode::OFF
     * @tc.expected: Has no scrollbar
     */
    CreateWithItem([](ListModelNG model) { model.SetScrollBar(Ace::DisplayMode::OFF); });
    paint = UpdateOverlayModifier();
    scrollBarOverlayModifier = paint->scrollBarOverlayModifier_.Upgrade();
    scrollBar = paint->scrollBar_.Upgrade();
    EXPECT_EQ(scrollBar, nullptr);

    /**
     * @tc.steps: step4. Set DisplayMode::ON
     * @tc.expected: Has scrollbar and on the right
     */
    CreateWithItem([](ListModelNG model) { model.SetScrollBar(Ace::DisplayMode::ON); });
    paint = UpdateOverlayModifier();
    scrollBarOverlayModifier = paint->scrollBarOverlayModifier_.Upgrade();
    scrollBar = paint->scrollBar_.Upgrade();
    EXPECT_NE(scrollBar, nullptr);
    EXPECT_TRUE(scrollBar->NeedPaint());
    EXPECT_EQ(scrollBarOverlayModifier->positionMode_, PositionMode::RIGHT);

    /**
     * @tc.steps: step5. Has no item
     * @tc.expected: UnScrollable, has no scrollbar
     */
    Create([](ListModelNG model) {});
    paint = UpdateOverlayModifier();
    scrollBarOverlayModifier = paint->scrollBarOverlayModifier_.Upgrade();
    scrollBar = paint->scrollBar_.Upgrade();
    EXPECT_NE(scrollBar, nullptr);
    EXPECT_FALSE(scrollBar->NeedPaint());

    /**
     * @tc.steps: step6. Set HORIZONTAL direction
     * @tc.expected: Has scrollbar and on the bottom
     */
    Create([](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        CreateItem(TOTAL_LINE_NUMBER, Axis::HORIZONTAL);
    });
    paint = UpdateOverlayModifier();
    scrollBarOverlayModifier = paint->scrollBarOverlayModifier_.Upgrade();
    scrollBar = paint->scrollBar_.Upgrade();
    EXPECT_NE(scrollBar, nullptr);
    EXPECT_TRUE(scrollBar->NeedPaint());
    EXPECT_EQ(scrollBarOverlayModifier->positionMode_, PositionMode::BOTTOM);
}

/**
 * @tc.name: PaintMethod004
 * @tc.desc: Test List paint method about PaintDivider
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, PaintMethod004, TestSize.Level1)
{
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, ClipRect(_, _)).Times(3);
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawLine(_, _)).Times(14);
    DrawingContext ctx = { canvas, 1, 1 };

    /**
     * @tc.steps: step1. Set divider
     */
    Create([](ListModelNG model) {
        model.SetDivider(ITEM_DIVIDER);
        CreateGroupWithSetting(GROUP_NUMBER, Axis::VERTICAL, V2::ListItemGroupStyle::NONE);
        CreateItem(TOTAL_LINE_NUMBER);
    });
    UpdateContentModifier();
    pattern_->listContentModifier_->onDraw(ctx);

    /**
     * @tc.steps: step2. Set lanes greater than 1
     */
    Create([](ListModelNG model) {
        model.SetLanes(2);
        model.SetDivider(ITEM_DIVIDER);
        CreateGroupWithSetting(GROUP_NUMBER, Axis::VERTICAL, V2::ListItemGroupStyle::NONE);
        CreateItem(TOTAL_LINE_NUMBER);
    });
    UpdateContentModifier();
    pattern_->listContentModifier_->onDraw(ctx);

    /**
     * @tc.steps: step3. Set lanes greater than 1 and lastIsItemGroup
     */
    Create([](ListModelNG model) {
        model.SetLanes(2);
        model.SetDivider(ITEM_DIVIDER);
        CreateItem(TOTAL_LINE_NUMBER);
        CreateGroupWithSetting(GROUP_NUMBER, Axis::VERTICAL, V2::ListItemGroupStyle::NONE);
    });
    UpdateContentModifier();
    pattern_->listContentModifier_->onDraw(ctx);
}

/**
 * @tc.name: PaintMethod005
 * @tc.desc: Test ListItemGroup paint method about PaintDivider
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, PaintMethod005, TestSize.Level1)
{
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawLine(_, _)).Times(6);

    Create(
        [](ListModelNG model) { CreateGroupWithSetting(GROUP_NUMBER, Axis::VERTICAL, V2::ListItemGroupStyle::NONE); });
    auto groupFrameNode = GetChildFrameNode(frameNode_, 0);
    auto groupPattern = groupFrameNode->GetPattern<ListItemGroupPattern>();
    RefPtr<NodePaintMethod> paint = groupPattern->CreateNodePaintMethod();
    RefPtr<ListItemGroupPaintMethod> groupPaint = AceType::DynamicCast<ListItemGroupPaintMethod>(paint);
    auto paintWrapper = groupFrameNode->CreatePaintWrapper();
    groupPaint->PaintDivider(AceType::RawPtr(paintWrapper), canvas);

    groupPaint->divider_.strokeWidth = Dimension(-1);
    groupPaint->PaintDivider(AceType::RawPtr(paintWrapper), canvas);

    groupPaint->divider_.strokeWidth = Dimension(STROKE_WIDTH, DimensionUnit::PERCENT);
    groupPaint->PaintDivider(AceType::RawPtr(paintWrapper), canvas);

    groupPaint->divider_ = ITEM_DIVIDER;
    groupPaint->divider_.startMargin = Dimension(LIST_WIDTH / 2);
    groupPaint->divider_.endMargin = Dimension(LIST_WIDTH / 2);
    groupPaint->PaintDivider(AceType::RawPtr(paintWrapper), canvas);

    groupPaint->divider_ = ITEM_DIVIDER;
    groupPaint->divider_.startMargin = Dimension(LIST_WIDTH / 2);
    groupPaint->divider_.endMargin = Dimension(LIST_WIDTH / 2 + 1);
    groupPaint->PaintDivider(AceType::RawPtr(paintWrapper), canvas);
}

/**
 * @tc.name: ChainAnimation001
 * @tc.desc: Test SetChainAnimationOptions
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ChainAnimation001, TestSize.Level1)
{
    constexpr float minSpace = 10.f;
    constexpr float maxSpace = 2.f;
    constexpr float conductivity = 5.f;
    constexpr float intensity = 5.f;
    ChainAnimationOptions options = {
        .minSpace = Dimension(minSpace),
        .maxSpace = Dimension(maxSpace),
        .conductivity = conductivity,
        .intensity = intensity,
        .edgeEffect = 0,
        .stiffness = DEFAULT_STIFFNESS,
        .damping = DEFAULT_DAMPING,
    };
    CreateWithItem([options](ListModelNG model) {
        model.SetSpace(Dimension(SPACE));
        model.SetChainAnimation(true);
        model.SetChainAnimationOptions(options);
    });

    /**
     * @tc.steps: step1. When minSpace > maxSpace.
     * @tc.expected: minSpace and maxSpace would be SPACE.
     */
    auto chainAnimation = pattern_->chainAnimation_;
    EXPECT_FLOAT_EQ(chainAnimation->minSpace_, SPACE);
    EXPECT_FLOAT_EQ(chainAnimation->maxSpace_, SPACE);

    /**
     * @tc.steps: step2. When conductivity > 1, intensity > 1.
     * @tc.expected: conductivity/intensity would be default value.
     */
    EXPECT_FLOAT_EQ(chainAnimation->conductivity_, ChainAnimation::DEFAULT_CONDUCTIVITY);
    EXPECT_FLOAT_EQ(chainAnimation->intensity_, ChainAnimation::DEFAULT_INTENSITY);

    /**
     * @tc.steps: step3. SetChainAnimationOptions again
     */
    pattern_->SetChainAnimationOptions(options);
    chainAnimation = pattern_->chainAnimation_;
    EXPECT_FLOAT_EQ(chainAnimation->minSpace_, SPACE);
    EXPECT_FLOAT_EQ(chainAnimation->maxSpace_, SPACE);
    EXPECT_FLOAT_EQ(chainAnimation->conductivity_, ChainAnimation::DEFAULT_CONDUCTIVITY);
    EXPECT_FLOAT_EQ(chainAnimation->intensity_, ChainAnimation::DEFAULT_INTENSITY);
}

/**
 * @tc.name: ChainAnimation002
 * @tc.desc: Test SetChainAnimationOptions
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ChainAnimation002, TestSize.Level1)
{
    constexpr float minSpace = 2.f;
    constexpr float maxSpace = 10.f;
    constexpr float conductivity = -5.f;
    constexpr float intensity = -5.f;
    ChainAnimationOptions options = {
        .minSpace = Dimension(minSpace),
        .maxSpace = Dimension(maxSpace),
        .conductivity = conductivity,
        .intensity = intensity,
        .edgeEffect = 0,
        .stiffness = DEFAULT_STIFFNESS,
        .damping = DEFAULT_DAMPING,
    };
    CreateWithItem([options](ListModelNG model) {
        model.SetSpace(Dimension(SPACE));
        model.SetChainAnimation(true);
        model.SetChainAnimationOptions(options);
    });

    /**
     * @tc.steps: step1. When minSpace < maxSpace.
     * @tc.expected: minSpace and maxSpace would be itself.
     */
    auto chainAnimation = pattern_->chainAnimation_;
    EXPECT_FLOAT_EQ(chainAnimation->minSpace_, minSpace);
    EXPECT_FLOAT_EQ(chainAnimation->maxSpace_, maxSpace);

    /**
     * @tc.steps: step2. When conductivity < 0, intensity < 0
     * @tc.expected: conductivity/intensity would be default value.
     */
    EXPECT_FLOAT_EQ(chainAnimation->conductivity_, ChainAnimation::DEFAULT_CONDUCTIVITY);
    EXPECT_FLOAT_EQ(chainAnimation->intensity_, ChainAnimation::DEFAULT_INTENSITY);

    /**
     * @tc.steps: step3. SetChainAnimationOptions again
     */
    pattern_->SetChainAnimationOptions(options);
    chainAnimation = pattern_->chainAnimation_;
    EXPECT_FLOAT_EQ(chainAnimation->minSpace_, minSpace);
    EXPECT_FLOAT_EQ(chainAnimation->maxSpace_, maxSpace);
    EXPECT_FLOAT_EQ(chainAnimation->conductivity_, ChainAnimation::DEFAULT_CONDUCTIVITY);
    EXPECT_FLOAT_EQ(chainAnimation->intensity_, ChainAnimation::DEFAULT_INTENSITY);
}

/**
 * @tc.name: ChainAnimation003
 * @tc.desc: Test SetChainAnimationOptions
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ChainAnimation003, TestSize.Level1)
{
    constexpr float minSpace = 2.f;
    constexpr float maxSpace = 10.f;
    constexpr float conductivity = 0;
    constexpr float intensity = 0;
    ChainAnimationOptions options = {
        .minSpace = Dimension(minSpace),
        .maxSpace = Dimension(maxSpace),
        .conductivity = conductivity,
        .intensity = intensity,
        .edgeEffect = 0,
        .stiffness = DEFAULT_STIFFNESS,
        .damping = DEFAULT_DAMPING,
    };
    CreateWithItem([options](ListModelNG model) {
        model.SetSpace(Dimension(SPACE));
        model.SetChainAnimation(true);
        model.SetChainAnimationOptions(options);
    });

    /**
     * @tc.steps: step1. When conductivity == 0, intensity == 0
     * @tc.expected: conductivity/intensity would be itself.
     */
    auto chainAnimation = pattern_->chainAnimation_;
    EXPECT_FLOAT_EQ(chainAnimation->conductivity_, conductivity);
    EXPECT_FLOAT_EQ(chainAnimation->intensity_, intensity);

    /**
     * @tc.steps: step2. SetChainAnimationOptions again
     */
    pattern_->SetChainAnimationOptions(options);
    chainAnimation = pattern_->chainAnimation_;
    EXPECT_FLOAT_EQ(chainAnimation->conductivity_, conductivity);
    EXPECT_FLOAT_EQ(chainAnimation->intensity_, intensity);
}

/**
 * @tc.name: OnModifyDone001
 * @tc.desc: Test list_pattern OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, OnModifyDone001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set multiSelectable_ to true
     * @tc.expected: InitMouseEvent() triggered by OnModifyDone()
     */
    ListModelNG model;
    model.Create();
    ViewAbstract::SetWidth(CalcLength(LIST_WIDTH));
    ViewAbstract::SetHeight(CalcLength(LIST_HEIGHT));
    model.SetMultiSelectable(true);
    CreateItem(TOTAL_LINE_NUMBER);
    GetInstance();
    EXPECT_NE(pattern_->GetScrollableEvent(), nullptr);
    ASSERT_NE(pattern_->GetScrollBar(), nullptr);
    EXPECT_EQ(pattern_->GetScrollBar()->GetDisplayMode(), DisplayMode::AUTO);
    EXPECT_TRUE(pattern_->isMouseEventInit_);

    /**
     * @tc.steps: step2. Call OnDirtyLayoutWrapperSwap()
     * @tc.expected: isInitialized_ would be true
     */
    EXPECT_FALSE(pattern_->isInitialized_);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(pattern_->isInitialized_);

    /**
     * @tc.steps: step3. When isMouseEventInit_ is true, Call OnModifyDone()
     * @tc.expected: UninitMouseEvent() would not be triggered, isMouseEventInit_ is still be true
     */
    pattern_->OnModifyDone();
    EXPECT_TRUE(pattern_->isMouseEventInit_);

    /**
     * @tc.steps: step4. Change multiSelectable_ to false, call OnModifyDone()
     * @tc.expected: UninitMouseEvent() triggered
     */
    pattern_->SetMultiSelectable(false);
    EXPECT_FALSE(pattern_->multiSelectable_);
    pattern_->OnModifyDone();
    EXPECT_FALSE(pattern_->isMouseEventInit_);
}

/**
 * @tc.name: Pattern002
 * @tc.desc: Test list_pattern AnimateTo function
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern002, TestSize.Level1)
{
    CreateWithItem([](ListModelNG model) {});

    pattern_->AnimateTo(0, 0, nullptr, true);
    EXPECT_NE(pattern_->springAnimation_, nullptr);

    pattern_->StopAnimate();
    pattern_->AnimateTo(0, 0, nullptr, true);
    EXPECT_NE(pattern_->springAnimation_, nullptr);

    pattern_->StopAnimate();
    pattern_->AnimateTo(0, 0, nullptr, false);
    EXPECT_NE(pattern_->curveAnimation_, nullptr);
}

/**
 * @tc.name: Pattern003
 * @tc.desc: Test OutBoundaryCallback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern003, TestSize.Level1)
{
    CreateWithItem([](ListModelNG model) {});
    EXPECT_TRUE(pattern_->OutBoundaryCallback());
    ScrollDown();
    EXPECT_FALSE(pattern_->OutBoundaryCallback());
    ScrollDown();
    EXPECT_TRUE(pattern_->OutBoundaryCallback());

    CreateWithItem([](ListModelNG model) {
        model.SetChainAnimation(true);
        model.SetChainAnimationOptions({ Dimension(0), Dimension(10), 0, 0, 0, DEFAULT_STIFFNESS, DEFAULT_DAMPING });
    });
    EXPECT_NE(pattern_->springProperty_, nullptr);
    EXPECT_NE(pattern_->chainAnimation_, nullptr);
    pattern_->OutBoundaryCallback();
    EXPECT_TRUE(pattern_->dragFromSpring_);
}

/**
 * @tc.name: ScrollToIndex001
 * @tc.desc: Test ScrollToIndex with ListItem
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ScrollToIndex001, TestSize.Level1)
{
    Create([](ListModelNG model) { CreateItem(20); });

    /**
     * @tc.steps: step1. first item in viewport
     */
    int32_t index = 0;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 0.f));

    /**
     * @tc.steps: step2. the item in viewport
     */
    index = 6;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 600.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 250.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 600.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 250.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 0.f));

    /**
     * @tc.steps: step3. the item below viewport
     */
    index = 9;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 900.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 550.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 900.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 550.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 200.f));

    /**
     * @tc.steps: step4. last item below viewport
     */
    index = ListLayoutAlgorithm::LAST_ITEM;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 200.f));

    /**
     * @tc.steps: step5. scroll to middle, first item above viewport
     */
    ScrollDown(8);
    index = 0;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 0.f));

    /**
     * @tc.steps: step6. the item above viewport
     */
    index = 6;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 600.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 250.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 600.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 600.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 250.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 600.f));

    /**
     * @tc.steps: step7. scroll to bottom, last item in viewport
     */
    ScrollDown(4);
    index = ListLayoutAlgorithm::LAST_ITEM;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 600.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 600.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 600.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 600.f));

    /**
     * @tc.steps: step8. Invalid index, index < -1
     */
    index = -2;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 600.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 600.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 600.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 600.f));
}

/**
 * @tc.name: ScrollToIndex002
 * @tc.desc: Test ScrollToIndex with ListItem and lanes > 1
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ScrollToIndex002, TestSize.Level1)
{
    constexpr int32_t itemNumber = 20;
    constexpr int32_t lanes = 2;
    Create([itemNumber, lanes](ListModelNG model) {
        model.SetLanes(lanes);
        CreateItem(itemNumber);
    });

    /**
     * @tc.steps: step1. first item in viewport
     */
    int32_t index = 0;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 0.f));

    /**
     * @tc.steps: step2. the item in viewport
     */
    index = 3;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 100.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 100.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 0.f));

    /**
     * @tc.steps: step3. the item below viewport
     */
    index = 16;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 100.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 100.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 100.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 100.f));

    /**
     * @tc.steps: step4. last item below viewport
     */
    index = ListLayoutAlgorithm::LAST_ITEM;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 100.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 100.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 100.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 100.f));

    /**
     * @tc.steps: step5. scroll to bottom, first item above viewport
     */
    ScrollDown(2);
    index = 0;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 0.f));

    /**
     * @tc.steps: step6. the item above viewport
     */
    index = 3;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 100.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 100.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 100.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 100.f));

    /**
     * @tc.steps: step7. last item in viewport
     */
    index = ListLayoutAlgorithm::LAST_ITEM;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 100.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 100.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 100.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 100.f));
}

/**
 * @tc.name: ScrollToIndex003
 * @tc.desc: Test ScrollToIndex with ListItemGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ScrollToIndex003, TestSize.Level1)
{
    Create([](ListModelNG model) { CreateGroup(5); });

    /**
     * @tc.steps: step1. first group in viewport
     */
    int32_t index = 0;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 0.f));

    /**
     * @tc.steps: step2. the group in viewport
     */
    index = 1;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 400.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 0));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 400.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 200.f));

    /**
     * @tc.steps: step3. the group below viewport
     */
    index = 2;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 800.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 600.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 400.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 400.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 800.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 600.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 400.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 400.f));

    /**
     * @tc.steps: step4. last group below viewport
     */
    index = ListLayoutAlgorithm::LAST_ITEM;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 400.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 400.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 400.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 400.f));

    /**
     * @tc.steps: step5. scroll to middle, first group above viewport
     */
    ScrollDown(8);
    index = 0;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 0.f));

    /**
     * @tc.steps: step6. the group above viewport
     */
    index = 1;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 400.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 400.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 400.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 400.f));

    /**
     * @tc.steps: step7. scroll to bottom, last item in viewport
     */
    ScrollDown(4);
    index = ListLayoutAlgorithm::LAST_ITEM;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 400.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 400.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 400.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 400.f));
}

/**
 * @tc.name: ScrollToItemInGroup001
 * @tc.desc: Test ScrollToItemInGroup with ListItemGroup and indexInGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ScrollToItemInGroup001, TestSize.Level1)
{
    Create([](ListModelNG listModelNG) { CreateGroup(GROUP_NUMBER); });
    constexpr int32_t indexInGroup = 2;

    /**
     * @tc.steps: step1. first group in viewport
     */
    int32_t index = 0;
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::START, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::END, 0.f));

    /**
     * @tc.steps: step2. the group below viewport
     */
    index = 2;
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::START, 600.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::CENTER, 600.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::END, 300.f));

    /**
     * @tc.steps: step3. last group below viewport
     */
    index = ListLayoutAlgorithm::LAST_ITEM;
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::START, 500.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::CENTER, 750.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::END, 700.f - 100.f / 3.f));

    /**
     * @tc.steps: step4. scroll to bottom, first group above viewport
     */
    ScrollDown(12);
    index = 0;
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::START, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::END, 0.f));

    /**
     * @tc.steps: step5. the group above viewport
     */
    index = 1;
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::START, 300.f + 100.f / 3.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::CENTER, 250.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::END, 0.f));

    /**
     * @tc.steps: step6. last item in viewport
     */
    index = ListLayoutAlgorithm::LAST_ITEM;
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::START, 600.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::CENTER, 750.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::END, 700.f - 100.f / 3.f));
}

/**
 * @tc.name: ScrollToItemInGroup002
 * @tc.desc: Test ScrollToItemInGroup with ListItemGroup and indexInGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ScrollToItemInGroup002, TestSize.Level1)
{
    Create([](ListModelNG listModelNG) { CreateGroup(GROUP_NUMBER); });
    constexpr int32_t indexInGroup = 2;

    /**
     * @tc.steps: step1. first group in viewport
     */
    int32_t index = 0;
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::START, 200.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::END, 0.f));

    /**
     * @tc.steps: step2. the group below viewport
     */
    index = 2;
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::START, 800.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::CENTER, 650.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::END, 300.f));

    /**
     * @tc.steps: step3. last group below viewport
     */
    index = ListLayoutAlgorithm::LAST_ITEM;
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::START, 300.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::CENTER, 300.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::END, 300.f));

    /**
     * @tc.steps: step4. scroll to bottom, first group above viewport
     */
    ScrollDown(12);
    index = 0;
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::START, 200.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::END, 0.f));

    /**
     * @tc.steps: step5. the group above viewport
     */
    index = 1;
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::START, 600.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::CENTER, 250.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::END, 0.f));

    /**
     * @tc.steps: step6. last item in viewport
     */
    index = ListLayoutAlgorithm::LAST_ITEM;
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::START, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::END, 0.f));
}

/**
 * @tc.name: ScrollToItemInGroup003
 * @tc.desc: Test ScrollToItemInGroup with ListItemGroup and indexInGroup and lanes
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ScrollToItemInGroup003, TestSize.Level1)
{
    Create([](ListModelNG listModelNG) {
        listModelNG.SetLanes(2);
        CreateGroup(2 * GROUP_NUMBER);
    });

    /**
     * @tc.steps: step1. first group in viewport
     */
    int32_t index = 0;
    int32_t indexInGroup = 0;
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::START, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::END, 0.f));

    /**
     * @tc.steps: step2. the group below viewport
     */
    index = 4;
    indexInGroup = 3;
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::START, 700.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::CENTER, 433.333374f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::END, 400.f));

    /**
     * @tc.steps: step3. last group below viewport
     */
    index = ListLayoutAlgorithm::LAST_ITEM;
    indexInGroup = 3;
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::START, 300.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::CENTER, 766.666687f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::END, 800.f));

    /**
     * @tc.steps: step4. scroll to bottom, first group above viewport
     */
    ScrollDown(20);
    index = 0;
    indexInGroup = 0;
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::START, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::END, 0.f));

    /**
     * @tc.steps: step5. the group above viewport
     */
    index = 2;
    indexInGroup = 1;
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::START, 333.333374f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::CENTER, 50.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::END, 0.f));

    /**
     * @tc.steps: step6. last item in viewport
     */
    index = ListLayoutAlgorithm::LAST_ITEM;
    indexInGroup = 3;
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::START, 300.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::CENTER, 650.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::END, 533.333374f));
}

/**
 * @tc.name: ScrollToItemInGroup004
 * @tc.desc: Test ScrollToItemInGroup with ListItemGroup and indexInGroup and lanes
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ScrollToItemInGroup004, TestSize.Level1)
{
    Create([](ListModelNG listModelNG) {
        listModelNG.SetLanes(2);
        CreateGroup(2 * GROUP_NUMBER);
    });

    /**
     * @tc.steps: step1. first group in viewport
     */
    int32_t index = 0;
    int32_t indexInGroup = 0;
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::START, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::END, 0.f));

    /**
     * @tc.steps: step2. the group below viewport
     */
    index = 4;
    indexInGroup = 3;
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::START, 400.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::CENTER, 400.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::END, 200.f));

    /**
     * @tc.steps: step3. last group below viewport
     */
    index = ListLayoutAlgorithm::LAST_ITEM;
    indexInGroup = 3;
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::START, 200.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::CENTER, 200.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::END, 200.f));

    /**
     * @tc.steps: step4. scroll to bottom, first group above viewport
     */
    ScrollDown(20);
    index = 0;
    indexInGroup = 0;
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::START, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::END, 0.f));

    /**
     * @tc.steps: step5. the group above viewport
     */
    index = 2;
    indexInGroup = 1;
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::START, 400.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::CENTER, 50.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::END, 0.f));

    /**
     * @tc.steps: step6. last item in viewport
     */
    index = ListLayoutAlgorithm::LAST_ITEM;
    indexInGroup = 3;
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::START, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::END, 0.f));
}

/**
 * @tc.name: Pattern005
 * @tc.desc: Test OnScrollCallback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern005, TestSize.Level1)
{
    CreateWithItem([](ListModelNG model) {
        model.SetScrollSnapAlign(V2::ScrollSnapAlign::START);
        model.SetChainAnimation(true);
        auto startFunc = GetDefaultSwiperBuilder(START_NODE_LEN);
        CreateItemWithSwipe(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    });

    // Set swiperItem_ to list pattern
    DragSwiperItem(0, 1.f);

    /**
     * @tc.steps: step1. When has animator_ and not stop, call OnScrollCallback.
     * @tc.expected: Would stop.
     */
    pattern_->AnimateTo(0, 0, nullptr, true);
    EXPECT_TRUE(pattern_->IsAnimationStop());
    double offset = 100.0;
    pattern_->OnScrollPosition(offset, SCROLL_FROM_START);
    EXPECT_FALSE(pattern_->scrollAbort_);
    pattern_->OnScrollCallback(100.f, SCROLL_FROM_START);
    EXPECT_FALSE(pattern_->scrollAbort_);
    EXPECT_TRUE(IsEqualTotalOffset(0));
    EXPECT_TRUE(pattern_->IsAnimationStop());

    /**
     * @tc.steps: step2. When has animator_ and stop, call OnScrollCallback.
     * @tc.expected:
     */
    ASSERT_NE(pattern_->GetScrollBar(), nullptr);
    pattern_->OnScrollCallback(100.f, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    EXPECT_GT(pattern_->GetTotalOffset(), -ITEM_HEIGHT);

    /**
     * @tc.steps: step3. Offset is 0, ProcessDragUpdate do nothing.
     * @tc.expected: CurrentOffset unchange.
     */
    pattern_->OnScrollCallback(0, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    EXPECT_GT(pattern_->GetTotalOffset(), -ITEM_HEIGHT);

    /**
     * @tc.steps: step4. When has animator_ and stop, call StopAnimate.
     * @tc.expected: Nothing.
     */
    pattern_->StopAnimate();

    pattern_->OnScrollCallback(850.f, SCROLL_FROM_START);
    EXPECT_EQ(pattern_->chainAnimation_->GetControlIndex(), 6);
    pattern_->OnScrollCallback(0.f, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    pattern_->OnScrollCallback(-100.f, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    pattern_->OnScrollCallback(100.f, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
}

/**
 * @tc.name: Pattern006
 * @tc.desc: Test GetItemIndexByPosition
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern006, TestSize.Level1)
{
    Create([](ListModelNG model) {
        model.SetLanes(2);
        CreateItem(VIEW_LINE_NUMBER);
    });

    /**
     * @tc.steps: step1. When lanes > 1, call GetItemIndexByPosition
     * @tc.expected: Would return correct itemIndex
     */
    const Point point = Point(300.f, 250.f);
    int32_t itemIndex = pattern_->GetItemIndexByPosition(point.GetX(), point.GetY());
    EXPECT_EQ(itemIndex, 5);
}

/**
 * @tc.name: Pattern007
 * @tc.desc: Test GetItemIndexByPosition
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. When has ListItem, position not at any ListItem
     * @tc.expected: Would return the last itemIndex
     */
    Create([](ListModelNG model) { CreateItem(VIEW_LINE_NUMBER); });
    const Point point = Point(0, 1000.f);
    int32_t itemIndex = pattern_->GetItemIndexByPosition(point.GetX(), point.GetY());
    EXPECT_EQ(itemIndex, VIEW_LINE_NUMBER);
}

/**
 * @tc.name: Pattern008
 * @tc.desc: Test GetItemIndexByPosition
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. When has no ListItem, call GetItemIndexByPosition
     * @tc.expected: Would return 0
     */
    Create([](ListModelNG model) {});
    const Point point = Point(0, 1000.f);
    int32_t itemIndex = pattern_->GetItemIndexByPosition(point.GetX(), point.GetY());
    EXPECT_EQ(itemIndex, 0);
}

/**
 * @tc.name: UpdateCurrentOffset001
 * @tc.desc: Test UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, UpdateCurrentOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. has no listItem
     */
    Create([](ListModelNG model) {});
    UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(IsEqualTotalOffset(0));

    /**
     * @tc.steps: step2. unscrollable List
     */
    Create([](ListModelNG model) { CreateItem(VIEW_LINE_NUMBER); });
    UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(IsEqualTotalOffset(0));

    /**
     * @tc.steps: step3. UpdateCurrentOffset with SCROLL_FROM_START
     * @tc.expected: The offset was not effected by friction
     */
    CreateWithItem([](ListModelNG model) {});
    UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_START);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT));

    /**
     * @tc.steps: step4. UpdateCurrentOffset with SCROLL_FROM_START
     * @tc.expected: The offset was not effected by friction
     */
    CreateWithItem([](ListModelNG model) { model.SetScrollSnapAlign(V2::ScrollSnapAlign::CENTER); });
    UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_UPDATE);
    EXPECT_LT(pattern_->GetTotalOffset(), -350.f);
    UpdateCurrentOffset(-ITEM_HEIGHT * 8, SCROLL_FROM_UPDATE);
    EXPECT_LT(pattern_->GetTotalOffset(), 450.f);
}

/**
 * @tc.name: Pattern010
 * @tc.desc: Test layout
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. do not set selfIdealSize, 0 listItem
     */
    ListModelNG listModelNG_1;
    listModelNG_1.Create();
    ViewAbstract::SetWidth(CalcLength(LIST_WIDTH));
    ViewAbstract::SetHeight(CalcLength(LIST_HEIGHT));
    GetInstance();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Width(), LIST_WIDTH);

    /**
     * @tc.steps: step1. do not set selfIdealSize, TOTAL_LINE_NUMBER listItem
     */
    ListModelNG listModelNG_2;
    listModelNG_2.Create();
    ViewAbstract::SetWidth(CalcLength(LIST_WIDTH));
    ViewAbstract::SetHeight(CalcLength(LIST_HEIGHT));
    CreateItem(TOTAL_LINE_NUMBER);
    GetInstance();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Width(), LIST_WIDTH);

    /**
     * @tc.steps: step1. set width Infinity
     */
    ListModelNG listModelNG_3;
    listModelNG_3.Create();
    ViewAbstract::SetWidth(CalcLength(Infinity<float>()));
    ViewAbstract::SetHeight(CalcLength(LIST_HEIGHT));
    CreateItem(TOTAL_LINE_NUMBER);
    GetInstance();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Width(), Infinity<float>());

    /**
     * @tc.steps: step1. set width Infinity, but no item
     */
    ListModelNG listModelNG_4;
    listModelNG_4.Create();
    ViewAbstract::SetWidth(CalcLength(Infinity<float>()));
    ViewAbstract::SetHeight(CalcLength(LIST_HEIGHT));
    GetInstance();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Width(), 0);
}

/**
 * @tc.name: SetEdgeEffectCallback001
 * @tc.desc: Test SetEdgeEffectCallback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SetEdgeEffectCallback001, TestSize.Level1)
{
    CreateWithItem([](ListModelNG model) { model.SetEdgeEffect(EdgeEffect::SPRING, false); });
    RefPtr<ScrollEdgeEffect> scrollEdgeEffect = pattern_->GetScrollEdgeEffect();
    EXPECT_EQ(scrollEdgeEffect->currentPositionCallback_(), 0);
    EXPECT_EQ(scrollEdgeEffect->leadingCallback_(), 0);
    EXPECT_EQ(scrollEdgeEffect->trailingCallback_(), 0.0);
    EXPECT_EQ(scrollEdgeEffect->initLeadingCallback_(), 0);
    EXPECT_EQ(scrollEdgeEffect->initTrailingCallback_(), 0.0);

    CreateWithItem([](ListModelNG model) {
        model.SetScrollSnapAlign(V2::ScrollSnapAlign::CENTER);
        model.SetEdgeEffect(EdgeEffect::SPRING, false);
    });
    scrollEdgeEffect = pattern_->GetScrollEdgeEffect();
    EXPECT_EQ(scrollEdgeEffect->currentPositionCallback_(), 350.0);
    EXPECT_EQ(scrollEdgeEffect->leadingCallback_(), -50.0);
    EXPECT_EQ(scrollEdgeEffect->trailingCallback_(), 350.f);
    EXPECT_EQ(scrollEdgeEffect->initLeadingCallback_(), -50.0);
    EXPECT_EQ(scrollEdgeEffect->initTrailingCallback_(), 350.f);

    Create([](ListModelNG model) {
        model.SetScrollSnapAlign(V2::ScrollSnapAlign::CENTER);
        model.SetEdgeEffect(EdgeEffect::SPRING, false);
    });
    scrollEdgeEffect = pattern_->GetScrollEdgeEffect();
    EXPECT_EQ(scrollEdgeEffect->currentPositionCallback_(), 0);
    EXPECT_EQ(scrollEdgeEffect->leadingCallback_(), 800);
    EXPECT_EQ(scrollEdgeEffect->trailingCallback_(), 0.0);
    EXPECT_EQ(scrollEdgeEffect->initLeadingCallback_(), 800);
    EXPECT_EQ(scrollEdgeEffect->initTrailingCallback_(), 0.0);
}

/**
 * @tc.name: Pattern012
 * @tc.desc: Test ScrollToNode
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern012, TestSize.Level1)
{
    // test ScrollToNode
    CreateWithItem([](ListModelNG model) {});
    auto listItem = GetChildFrameNode(frameNode_, 8);
    bool ret = pattern_->ScrollToNode(listItem);
    EXPECT_TRUE(ret);

    // test GetTotalHeight
    Create([](ListModelNG model) {});
    EXPECT_EQ(pattern_->GetTotalHeight(), 0.f);
    CreateWithItem([](ListModelNG model) {});
    EXPECT_EQ(pattern_->GetTotalHeight(), TOTAL_LINE_NUMBER * ITEM_HEIGHT);

    // test ToJsonValue/FromJson
    CreateWithItem([](ListModelNG model) {});
    auto json = JsonUtil::Create(true);
    pattern_->ToJsonValue(json);
    EXPECT_EQ(json->GetBool("multiSelectable"), false);
    EXPECT_EQ(json->GetInt("startIndex"), 0);
    EXPECT_EQ(json->GetDouble("itemStartPos"), 0.0);
    EXPECT_EQ(json->GetDouble("friction"), DEFAULT_FRICTION);
    pattern_->FromJson(json);
    EXPECT_TRUE(IsEqualTotalOffset(0));
}

/**
 * @tc.name: ListSelectForCardModeTest001
 * @tc.desc: Test the card mode for select.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListSelectForCardModeTest001, TestSize.Level1)
{
    Create([](ListModelNG model) {
        model.SetMultiSelectable(true);
        ListItemGroupModelNG groupModel;
        groupModel.Create(V2::ListItemGroupStyle::CARD);
        CreateItem(GROUP_LINE_NUMBER, Axis::VERTICAL, V2::ListItemStyle::CARD);
        ViewStackProcessor::GetInstance()->Pop();
    });
    RefPtr<FrameNode> group = GetChildFrameNode(frameNode_, 0);

    /**
     * @tc.steps: step1. Select zone.
     * @tc.expected: The 1st and 2nd items are selected.
     */
    MouseSelect(Offset(0.f, 0.f), Offset(200.f, 100.f));
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(group, 0)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(group, 1)->IsSelected());
    pattern_->ClearMultiSelect();

    /**
     * @tc.steps: step2. Change select zone.
     * @tc.expected: Selected items changed.
     */
    MouseSelect(Offset(0.f, 200.f), Offset(200.f, 300.f));
    EXPECT_FALSE(GetChildPattern<ListItemPattern>(group, 0)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(group, 1)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(group, 2)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(group, 3)->IsSelected());
    pattern_->ClearMultiSelect();

    /**
     * @tc.steps: step3. Click first item.
     * @tc.expected: Each item not selected.
     */
    MouseSelect(Offset(0.f, 10.f), Offset(0.f, 10.f));
    for (int32_t index = 0; index < GROUP_LINE_NUMBER; index++) {
        EXPECT_FALSE(GetChildPattern<ListItemPattern>(group, index)->IsSelected()) << "Index: " << index;
    }
}

/**
 * @tc.name: ListSelectForCardModeTest002
 * @tc.desc: Test the card mode for select.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListSelectForCardModeTest002, TestSize.Level1)
{
    const Offset LEFT_TOP = Offset(0.f, 0.f);
    const Offset LEFT_BOTTOM = Offset(0.f, 150.f);
    const Offset RIGHT_TOP = Offset(360.f, 0.f);
    const Offset RIGHT_BOTTOM = Offset(360.f, 150.f);
    Create([](ListModelNG model) {
        model.SetMultiSelectable(true);
        ListItemGroupModelNG groupModel;
        groupModel.Create(V2::ListItemGroupStyle::CARD);
        CreateItem(GROUP_LINE_NUMBER, Axis::VERTICAL, V2::ListItemStyle::CARD);
        ViewStackProcessor::GetInstance()->Pop();
    });
    RefPtr<FrameNode> group = GetChildFrameNode(frameNode_, 0);

    /**
     * @tc.steps: step1. Select from LEFT_TOP to RIGHT_BOTTOM
     */
    MouseSelect(LEFT_TOP, RIGHT_BOTTOM);
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(group, 0)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(group, 1)->IsSelected());
    pattern_->ClearMultiSelect();

    /**
     * @tc.steps: step2. Select from RIGHT_TOP to LEFT_BOTTOM
     */
    MouseSelect(RIGHT_TOP, LEFT_BOTTOM);
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(group, 0)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(group, 1)->IsSelected());
    pattern_->ClearMultiSelect();

    /**
     * @tc.steps: step3. Select from LEFT_BOTTOM to RIGHT_TOP
     */
    MouseSelect(LEFT_BOTTOM, RIGHT_TOP);
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(group, 0)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(group, 1)->IsSelected());
    pattern_->ClearMultiSelect();

    /**
     * @tc.steps: step4. Select from RIGHT_BOTTOM to LEFT_TOP
     */
    MouseSelect(RIGHT_BOTTOM, LEFT_TOP);
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(group, 0)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(group, 1)->IsSelected());
}

/**
 * @tc.name: ListSelectForCardModeTest003
 * @tc.desc: Test the card mode for select when the 'selectable' of listItem  is false.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListSelectForCardModeTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List/ListItemGroup/ListItem and ListItem set to unselectable.
     * @tc.expected: step1. create a card style ListItemGroup success.
     */
    Create([](ListModelNG model) {
        model.SetMultiSelectable(true);
        ListItemGroupModelNG groupModel;
        groupModel.Create(V2::ListItemGroupStyle::CARD);
        CreateItem(5, Axis::VERTICAL, V2::ListItemStyle::CARD);
        ViewStackProcessor::GetInstance()->Pop();
    });
    auto group = GetChildFrameNode(frameNode_, 0);

    bool isFifthItemSelected = false;
    auto selectCallback = [&isFifthItemSelected](bool) { isFifthItemSelected = true; };
    GetChildPattern<ListItemPattern>(group, 3)->SetSelectable(false);
    GetChildFrameNode(group, 4)->GetEventHub<ListItemEventHub>()->SetOnSelect(std::move(selectCallback));

    /**
     * @tc.steps: step2. Select zone.
     * @tc.expected: The 4th item is not selected but 5th item is selected.
     */
    MouseSelect(Offset(0.f, 350.f), Offset(360.f, 450.f));
    EXPECT_FALSE(GetChildPattern<ListItemPattern>(group, 3)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(group, 4)->IsSelected());
    EXPECT_TRUE(isFifthItemSelected);
}

/**
 * @tc.name: ListItemGroupCreateForCardModeTest001
 * @tc.desc: Test the initialization of listItem in card mode.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemGroupCreateForCardModeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create ListItemGroup.
     * @tc.expected: step2. create a card style ListItemGroup success.
     */
    ListItemGroupModelNG groupModel;
    groupModel.Create(V2::ListItemGroupStyle::CARD);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_EQ(pattern->GetListItemGroupStyle(), V2::ListItemGroupStyle::CARD);

    /**
     * @tc.steps: step3. compare the obtained value with the set value.
     * @tc.expected: step3. the obtained value is equal to the set value.
     */
    auto renderContext = frameNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::WHITE);
    EXPECT_EQ(layoutProperty->GetMarginProperty()->left.value(), CalcLength(GROUP_MARGIN));
    EXPECT_EQ(layoutProperty->GetMarginProperty()->right.value(), CalcLength(GROUP_MARGIN));
}

/**
 * @tc.name: ListItemCreateForCardModeTest001
 * @tc.desc: Test the initialization of listItem in card mode.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemCreateForCardModeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create ListItem in card mode.
     * @tc.expected: step2. create a card style ListItem success.
     */
    ListItemModelNG itemModel;
    itemModel.Create([](int32_t) {}, V2::ListItemStyle::CARD);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = frameNode->GetPattern<ListItemPattern>();
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_EQ(pattern->GetListItemStyle(), V2::ListItemStyle::CARD);

    /**
     * @tc.steps: step3. compare the obtained value with the set value.
     * @tc.expected: step3. the obtained value is equal to the set value.
     */
    auto renderContext = frameNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::WHITE);
}

/**
 * @tc.name: ListItemHoverEventForCardModeTest001
 * @tc.desc: Test the hover event when the hover status of card mode listItem is true.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemHoverEventForCardModeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create ListItem in card mode.
     * @tc.expected: step2. create a card style ListItem success.
     */
    ListItemModelNG itemModel;
    itemModel.Create([](int32_t) {}, V2::ListItemStyle::CARD);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ListItemPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. call function HandleHoverEvent and Set hover status to true.
     * @tc.expected: step3. the hover status is true.
     */
    pattern->HandleHoverEvent(true, frameNode);
    EXPECT_TRUE(pattern->isHover_);

    /**
     * @tc.steps: step3. call function HandleHoverEvent and Set hover status to false.
     * @tc.expected: step3. the hover status is false.
     */
    pattern->HandleHoverEvent(false, frameNode);
    EXPECT_FALSE(pattern->isHover_);
}

/**
 * @tc.name: ListItemPressEventForCardModeTest001
 * @tc.desc: Test the press event when the TouchType is DOWN.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemPressEventForCardModeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create ListItem in card mode.
     * @tc.expected: step2. create a card style ListItem success.
     */
    ListItemModelNG itemModel;
    itemModel.Create([](int32_t) {}, V2::ListItemStyle::CARD);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = frameNode->GetPattern<ListItemPattern>();

    /**
     * @tc.steps: step3. call function HandlePressEvent, set TouchType to DOWN and set hover status is true.
     * @tc.expected: step3. the color is different from the initial color when the listItem is pressed with the mouse.
     */
    pattern->isHover_ = true;
    pattern->HandlePressEvent(true, frameNode);
    EXPECT_TRUE(pattern->isPressed_);

    /**
     * @tc.steps: step4. call function HandlePressEvent, set TouchType to DOWN and set hover status is false.
     * @tc.expected: step4. the color is different from the initial color when the listItem is pressed with gesture.
     */
    pattern->isHover_ = false;
    pattern->HandlePressEvent(true, frameNode);
    EXPECT_TRUE(pattern->isPressed_);

    /**
     * @tc.steps: step5. call function HandlePressEvent, set TouchType to UP and set hover status is true.
     * @tc.expected: step5. the color differs from the initial color when mouse hovers over listItem after pressing.
     */
    pattern->isHover_ = true;
    pattern->HandlePressEvent(false, frameNode);
    EXPECT_FALSE(pattern->isPressed_);

    /**
     * @tc.steps: step6. call function HandlePressEvent, set TouchType to UP and set hover status is false.
     * @tc.expected: step6. the color returns to its original color after pressing on listItem through gestures.
     */
    pattern->isHover_ = false;
    pattern->HandlePressEvent(false, frameNode);
    EXPECT_FALSE(pattern->isPressed_);
}

/**
 * @tc.name: ListItemDisableEventForCardModeTest001
 * @tc.desc: Test disable event when the enable status of the listItem is false.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemDisableEventForCardModeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create ListItem in card mode.
     * @tc.expected: step2. create a card style ListItem success and set enable status to false.
     */
    ListItemModelNG itemModel;
    itemModel.Create([](int32_t) {}, V2::ListItemStyle::CARD);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = frameNode->GetPattern<ListItemPattern>();
    auto eventHub = frameNode->GetEventHub<ListItemEventHub>();
    eventHub->SetEnabled(false);
    pattern->selectable_ = true;

    /**
     * @tc.steps: step3. call function InitDisableEvent.
     * @tc.expected: step3. the background color has been updated and selectable has been set to false.
     */
    pattern->InitDisableEvent();
    EXPECT_FALSE(pattern->selectable_);
}

/**
 * @tc.name: ListPattern_UpdateScrollSnap001
 * @tc.desc: Test UpdateScrollSnap.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListPattern_UpdateScrollSnap001, TestSize.Level1)
{
    CreateWithItem([](ListModelNG model) {});
    pattern_->AnimateTo(0, 0, nullptr, true);
    pattern_->UpdateScrollSnap();
    EXPECT_TRUE(pattern_->predictSnapOffset_.has_value());

    pattern_->StopAnimate();
    pattern_->UpdateScrollSnap();
    EXPECT_EQ(pattern_->predictSnapOffset_.value(), 0.0);
}

/**
 * @tc.name: ListPattern_Distributed001
 * @tc.desc: Test the distributed capability of List.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListPattern_Distributed001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init List node
     */
    CreateWithItem([](ListModelNG model) {});

    /**
     * @tc.steps: step2. get pattern .
     * @tc.expected: function ProvideRestoreInfo is called.
     */
    pattern_->startIndex_ = 1;
    std::string ret = pattern_->ProvideRestoreInfo();

    /**
     * @tc.steps: step3. function OnRestoreInfo is called.
     * @tc.expected: Passing JSON format.
     */
    pattern_->OnRestoreInfo(ret);
    EXPECT_EQ(pattern_->jumpIndex_, 1);
}

/**
 * @tc.name: ListPattern_GetItemRect001
 * @tc.desc: Test the GetItemRect function of List.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListPattern_GetItemRect001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init List then slide List by Scroller.
     */
    Create([](ListModelNG model) {
        model.SetInitialIndex(1);
        CreateItem(TOTAL_LINE_NUMBER * 2);
    });
    pattern_->ScrollBy(ITEM_HEIGHT / 2.0f);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Get invalid ListItem Rect.
     * @tc.expected: Return 0 when input invalid index.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(-1), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(0), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(TOTAL_LINE_NUMBER * 2 - 1), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(TOTAL_LINE_NUMBER * 2), Rect()));

    /**
     * @tc.steps: step3. Get ListItem Rect by GetItemRectInGroup.
     * @tc.expected: Return 0 when get ListItem Rect by GetItemRectInGroup.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetItemRectInGroup(1, 0), Rect()));

    /**
     * @tc.steps: step4. Get valid ListItem Rect.
     * @tc.expected: Return actual Rect when input valid index.
     */
    EXPECT_TRUE(
        IsEqual(pattern_->GetItemRect(1), Rect(0, -ITEM_HEIGHT / 2.0f, FILL_LENGTH.Value() * LIST_WIDTH, ITEM_HEIGHT)));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(3),
        Rect(0, -ITEM_HEIGHT / 2.0f + ITEM_HEIGHT * 2, FILL_LENGTH.Value() * LIST_WIDTH, ITEM_HEIGHT)));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(9),
        Rect(0, -ITEM_HEIGHT / 2.0f + ITEM_HEIGHT * 8, FILL_LENGTH.Value() * LIST_WIDTH, ITEM_HEIGHT)));
    /**
     * @tc.steps: step5. Slide List by Scroller.
     */
    pattern_->ScrollToIndex(10);
    FlushLayoutTask(frameNode_);
    /**
     * @tc.steps: step6. Get invalid ListItem Rect.
     * @tc.expected: Return 0 when input invalid index.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(9), Rect()));

    /**
     * @tc.steps: step7. Get valid ListItem Rect.
     * @tc.expected: Return actual Rect when input valid index.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(pattern_->GetEndIndex()),
        Rect(0, LIST_HEIGHT - ITEM_HEIGHT, FILL_LENGTH.Value() * LIST_WIDTH, ITEM_HEIGHT)));
}

/**
 * @tc.name: ListPattern_GetItemRectInGroup001
 * @tc.desc: Test the GetItemRectInGroup function of List.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListPattern_GetItemRectInGroup001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init List then slide List by Scroller.
     */
    Create([](ListModelNG model) {
        model.SetInitialIndex(1);
        CreateGroup(TOTAL_LINE_NUMBER, Axis::VERTICAL);
    });
    pattern_->ScrollBy(ITEM_HEIGHT * 2);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Get invalid group item Rect.
     * @tc.expected: Return 0 when input invalid group index.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetItemRectInGroup(-1, 0), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRectInGroup(2, -1), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRectInGroup(0, 0), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRectInGroup(TOTAL_LINE_NUMBER - 1, 0), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRectInGroup(1, 0), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRectInGroup(1, GROUP_LINE_NUMBER), Rect()));

    /**
     * @tc.steps: step3. Get valid group item Rect.
     * @tc.expected: Return actual Rect when input valid group index.
     */
    EXPECT_TRUE(IsEqual(
        pattern_->GetItemRectInGroup(2, 0), Rect(0, ITEM_HEIGHT * 2, FILL_LENGTH.Value() * LIST_WIDTH, ITEM_HEIGHT)));

    /**
     * @tc.steps: step4. Get valid ListItemGroup Rect.
     * @tc.expected: Return actual Rect when input valid index.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(2),
        Rect(0, ITEM_HEIGHT * 2, FILL_LENGTH.Value() * LIST_WIDTH, ITEM_HEIGHT * GROUP_LINE_NUMBER)));
}

/**
 * @tc.name: ListLayout_SafeArea001
 * @tc.desc: Test list layout with expandSafeArea.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListLayout_SafeArea001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init List.
     */
    Create([](ListModelNG model) {
        model.SetInitialIndex(1);
        CreateItem(TOTAL_LINE_NUMBER * 2);
    });

    EXPECT_CALL(*MockPipelineContext::pipeline_, GetSafeArea)
        .Times(1)
        .WillOnce(Return(SafeAreaInsets { {}, {}, {}, { .start = 0, .end = 100 } }));
    layoutProperty_->UpdateSafeAreaExpandOpts({ .type = SAFE_AREA_TYPE_SYSTEM, .edges = SAFE_AREA_EDGE_ALL });
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->contentEndOffset_, 100);
    EXPECT_TRUE(IsEqual(frameNode_->geometryNode_->GetFrameSize(), SizeF(LIST_WIDTH, LIST_HEIGHT)));
}

/**
 * @tc.name: ListLayout_SafeArea002
 * @tc.desc: Test list layout with expandSafeArea.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListLayout_SafeArea002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init List.
     */
    Create([](ListModelNG model) {
        model.SetInitialIndex(1);
        CreateItem(TOTAL_LINE_NUMBER * 2);
    });

    EXPECT_CALL(*MockPipelineContext::pipeline_, GetSafeArea).Times(0);
    layoutProperty_->UpdateSafeAreaExpandOpts({ .type = SAFE_AREA_TYPE_SYSTEM, .edges = SAFE_AREA_EDGE_TOP });
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->contentEndOffset_, 0);
    EXPECT_TRUE(IsEqual(frameNode_->geometryNode_->GetFrameSize(), SizeF(LIST_WIDTH, LIST_HEIGHT)));
}

/**
 * @tc.name: EdgeEffectOption001
 * @tc.desc: Test EdgeEffectOption
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, EdgeEffectOption001, TestSize.Level1)
{
    Create([](ListModelNG model) {
        CreateItem(TOTAL_LINE_NUMBER);
        model.SetEdgeEffect(EdgeEffect::SPRING, false);
    });
    EXPECT_FALSE(pattern_->GetAlwaysEnabled());
    EXPECT_TRUE(pattern_->scrollable_);
}

/**
 * @tc.name: EdgeEffectOption002
 * @tc.desc: Test EdgeEffectOption
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, EdgeEffectOption002, TestSize.Level1)
{
    Create([](ListModelNG model) {
        CreateItem(TOTAL_LINE_NUMBER);
        model.SetEdgeEffect(EdgeEffect::SPRING, true);
    });
    EXPECT_TRUE(pattern_->GetAlwaysEnabled());
    EXPECT_TRUE(pattern_->scrollable_);
}

/**
 * @tc.name: EdgeEffectOption003
 * @tc.desc: Test EdgeEffectOption
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, EdgeEffectOption003, TestSize.Level1)
{
    Create([](ListModelNG model) {
        CreateItem(1); // 1 is item count.
        model.SetEdgeEffect(EdgeEffect::SPRING, false);
    });
    EXPECT_FALSE(pattern_->GetAlwaysEnabled());
    EXPECT_FALSE(pattern_->scrollable_);
}

/**
 * @tc.name: EdgeEffectOption004
 * @tc.desc: Test EdgeEffectOption
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, EdgeEffectOption004, TestSize.Level1)
{
    Create([](ListModelNG model) {
        CreateItem(1); // 1 is item count.
        model.SetEdgeEffect(EdgeEffect::SPRING, true);
    });
    EXPECT_TRUE(pattern_->GetAlwaysEnabled());
    EXPECT_TRUE(pattern_->scrollable_);
}

/**
 * @tc.name: FRCCallback001
 * @tc.desc: Test FRC callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, FRCCallback001, TestSize.Level1)
{
    Create([](ListModelNG model) {});
    auto renderContext = AceType::MakeRefPtr<MockRenderContext>();
    frameNode_->renderContext_ = renderContext;
    EXPECT_CALL(*renderContext, CalcExpectedFrameRate(_, _)).Times(1);
    pattern_->NotifyFRCSceneInfo("", 0.0f, SceneStatus::START);
}

/**
 * @tc.name: PositionController004
 * @tc.desc: Test GetItemRectInGroup function when set ListItemGroup space
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, PositionController004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List/ListItemGroup and Set Space
     */
    int32_t itemNumber = 6;
    Create([=](ListModelNG model) {
        CreateGroupWithSetting(1, Axis::VERTICAL, V2::ListItemGroupStyle::NONE, itemNumber);
    });
    auto controller = AceType::MakeRefPtr<ListPositionController>();
    pattern_->SetPositionController(controller);

    /**
     * @tc.steps: step2. Get invalid ListItemGroup Rect.
     * @tc.expected: Return Rect() when input invalid index.
     */
    double groupHeight = ITEM_HEIGHT * itemNumber + GROUP_HEADER_LEN * 2 + (itemNumber - 1) * SPACE;
    EXPECT_TRUE(IsEqual(controller->GetItemRect(-1), Rect()));

    /**
     * @tc.steps: step3. Get valid ListItemGroup Rect.
     * @tc.expected: Return actual Rect when input valid index.
     */
    EXPECT_TRUE(IsEqual(controller->GetItemRect(0), Rect(0, 0, FILL_LENGTH.Value() * LIST_WIDTH, groupHeight)));
    /**
     * @tc.steps: step4. Get invalid ListItem Rect.
     * @tc.expected: Return Rect() when input invalid index.
     */
    EXPECT_TRUE(IsEqual(controller->GetItemRectInGroup(0, -1), Rect()));
    for (int32_t j = 0; j < itemNumber; ++j) {
        /**
         * @tc.steps: step5. Get valid ListItem Rect.
         * @tc.expected: Return actual Rect when input valid index.
         */
        double itemY = j * (ITEM_HEIGHT + SPACE) + GROUP_HEADER_LEN;
        EXPECT_TRUE(IsEqual(
            controller->GetItemRectInGroup(0, j), Rect(0, itemY, FILL_LENGTH.Value() * LIST_WIDTH, ITEM_HEIGHT)));
    }
    /**
     * @tc.steps: step6. Get invalid ListItem Rect.
     * @tc.expected: Return Rect() when input invalid index.
     */
    EXPECT_TRUE(IsEqual(controller->GetItemRectInGroup(0, itemNumber), Rect()));

    /**
     * @tc.steps: step7. Get invalid ListItemGroup Rect.
     * @tc.expected: Return Rect() when input invalid index.
     */
    EXPECT_TRUE(IsEqual(controller->GetItemRect(1), Rect()));
}

/**
 * @tc.name: PositionController005
 * @tc.desc: Test GetItemRect function when set ListItemGroup space and set List Space
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, PositionController005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List/ListItemGroup and Set Space
     */
    int32_t groupNumber = 2;
    int32_t itemNumber = 3;
    Create([=](ListModelNG model) {
        CreateGroupWithSetting(groupNumber, Axis::VERTICAL, V2::ListItemGroupStyle::NONE, itemNumber);
        model.SetSpace(Dimension(SPACE));
    });
    auto controller = AceType::MakeRefPtr<ListPositionController>();
    pattern_->SetPositionController(controller);
    EXPECT_EQ(GetALLItem().size(), 6);
    EXPECT_FLOAT_EQ(layoutProperty_->GetSpaceValue().Value(), SPACE);

    double groupHeight = ITEM_HEIGHT * itemNumber + GROUP_HEADER_LEN * 2 + (itemNumber - 1) * SPACE;
    for (int32_t i = 0; i < groupNumber; ++i) {
        /**
         * @tc.steps: step2. Get valid ListItemGroup Rect.
         * @tc.expected: Return actual Rect when input valid index.
         */
        double groupY = i * (groupHeight + SPACE);
        EXPECT_TRUE(
            IsEqual(controller->GetItemRect(i), Rect(0, groupY, FILL_LENGTH.Value() * LIST_WIDTH, groupHeight)));
        /**
         * @tc.steps: step3. Get invalid ListItem Rect.
         * @tc.expected: Return Rect() when input invalid index.
         */
        EXPECT_TRUE(IsEqual(controller->GetItemRectInGroup(i, -1), Rect()));
        for (int32_t j = 0; j < itemNumber; ++j) {
            /**
             * @tc.steps: step4. Get valid ListItem Rect.
             * @tc.expected: Return actual Rect when input valid index.
             */
            double itemY = groupY + j * (ITEM_HEIGHT + SPACE) + GROUP_HEADER_LEN;
            EXPECT_TRUE(IsEqual(
                controller->GetItemRectInGroup(i, j), Rect(0, itemY, FILL_LENGTH.Value() * LIST_WIDTH, ITEM_HEIGHT)));
        }
        /**
         * @tc.steps: step5. Get invalid ListItem Rect.
         * @tc.expected: Return Rect() when input invalid index.
         */
        EXPECT_TRUE(IsEqual(controller->GetItemRectInGroup(i, itemNumber), Rect()));
    }
}

/**
 * @tc.name: AttrLanes008
 * @tc.desc: Test LaneGutter
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrLanes008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List and Set lanes
     */
    int32_t itemNumber = 20;
    int32_t lanes = 5;
    Dimension laneGutter = Dimension::FromString("10%");
    Create([=](ListModelNG model) {
        CreateItem(itemNumber);
        model.SetScrollBar(Ace::DisplayMode::OFF);
        model.SetLanes(lanes);
        model.SetLaneGutter(laneGutter);
    });
    EXPECT_TRUE(VerifyPosition(frameNode_, itemNumber, 5, DEFAULT_SPACE, DEFAULT_STARTOFFSET));

    double gutter = laneGutter.ConvertToPxWithSize(LIST_WIDTH);
    double itemWidth = (FILL_LENGTH.Value() - laneGutter.Value() * (lanes - 1)) * LIST_WIDTH / lanes;
    for (int32_t i = 0; i < itemNumber; ++i) {
        int32_t x = i % lanes;
        int32_t y = i / lanes;
        EXPECT_TRUE(
            IsEqual(pattern_->GetItemRect(i), Rect(x * (gutter + itemWidth), y * ITEM_HEIGHT, itemWidth, ITEM_HEIGHT)));
    }
}

/**
 * @tc.name: Pattern013
 * @tc.desc: Test ScrollTo and ScrollBy
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List and Set lanes
     */
    int32_t itemNumber = 10;
    SizeT<Dimension> itemSize = SizeT<Dimension>(FILL_LENGTH, FILL_LENGTH);
    Create([=](ListModelNG model) {
        CreateItemWithSize(itemNumber, itemSize);
        model.SetListDirection(Axis::VERTICAL);
        model.SetScrollBar(Ace::DisplayMode::OFF);
    });

    /**
     * @tc.steps: step2. swipe forward 3 listItem
     */
    pattern_->ScrollTo(3 * LIST_HEIGHT);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(3), Rect(0, 0, LIST_WIDTH, LIST_HEIGHT)));

    /**
     * @tc.steps: step3. swipe backward 2.5 listItem
     */
    pattern_->ScrollBy(-2.5 * LIST_HEIGHT);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(0), Rect(0, -LIST_HEIGHT / 2.0, LIST_WIDTH, LIST_HEIGHT)));

    /**
     * @tc.steps: step4. swipe forward 3 listItem
     */
    pattern_->ScrollBy(3 * LIST_HEIGHT);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(3), Rect(0, -LIST_HEIGHT / 2.0, LIST_WIDTH, LIST_HEIGHT)));

    /**
     * @tc.steps: step5. swipe backward 2.5 listItem
     */
    pattern_->ScrollTo(LIST_HEIGHT);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(1), Rect(0, 0, LIST_WIDTH, LIST_HEIGHT)));
}

/**
 * @tc.name: Pattern014
 * @tc.desc: Test UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List
     */
    int32_t itemNumber = 20;
    Create([=](ListModelNG model) {
        CreateItem(itemNumber);
        model.SetScrollBar(Ace::DisplayMode::ON);
        model.SetEdgeEffect(EdgeEffect::NONE, true);
    });

    auto scrollBar = pattern_->GetScrollBar();
    Rect barRect = scrollBar->GetBarRect();
    Rect activeRectInit = scrollBar->GetActiveRect();
    Rect activeRectBot = Rect(LIST_WIDTH, LIST_HEIGHT - activeRectInit.Height(), 0, activeRectInit.Height());

    std::vector<int32_t> scrollFromVector = { SCROLL_FROM_NONE, SCROLL_FROM_UPDATE, SCROLL_FROM_ANIMATION,
        SCROLL_FROM_JUMP, SCROLL_FROM_ANIMATION_SPRING, SCROLL_FROM_BAR, SCROLL_FROM_ANIMATION_CONTROLLER,
        SCROLL_FROM_BAR_FLING };

    for (int32_t form : scrollFromVector) {
        bool isAtBottom = pattern_->IsAtBottom();
        float offset = isAtBottom ? 3 * LIST_HEIGHT : -3 * LIST_HEIGHT;
        EXPECT_TRUE(pattern_->UpdateCurrentOffset(offset, form));
        FlushLayoutTask(frameNode_);
        EXPECT_TRUE(IsEqual(scrollBar->GetBarRect(), barRect));
        if (isAtBottom) {
            EXPECT_FLOAT_EQ(pattern_->GetBarOffset(), 0);
            EXPECT_TRUE(IsEqual(scrollBar->GetActiveRect(), activeRectInit));
        } else {
            EXPECT_FLOAT_EQ(pattern_->GetBarOffset(), -1200);
            EXPECT_TRUE(IsEqual(scrollBar->GetActiveRect(), activeRectBot));
        }
    }
}

/**
 * @tc.name: Pattern015
 * @tc.desc: Test UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List
     */
    int32_t itemNumber = 20;
    Create([=](ListModelNG model) {
        CreateItem(itemNumber);
        model.SetScrollBar(Ace::DisplayMode::ON);
        model.SetEdgeEffect(EdgeEffect::FADE, false);
    });

    auto scrollBar = pattern_->GetScrollBar();
    Rect barRect = scrollBar->GetBarRect();
    Rect activeRectInit = scrollBar->GetActiveRect();
    Rect activeRectBot = Rect(LIST_WIDTH, LIST_HEIGHT - activeRectInit.Height(), 0, activeRectInit.Height());

    std::vector<int32_t> scrollFromVector = { SCROLL_FROM_NONE, SCROLL_FROM_UPDATE, SCROLL_FROM_ANIMATION,
        SCROLL_FROM_JUMP, SCROLL_FROM_ANIMATION_SPRING, SCROLL_FROM_BAR, SCROLL_FROM_ANIMATION_CONTROLLER,
        SCROLL_FROM_BAR_FLING };

    for (int32_t form : scrollFromVector) {
        bool isAtBottom = pattern_->IsAtBottom();
        float offset = isAtBottom ? 3 * LIST_HEIGHT : -3 * LIST_HEIGHT;
        EXPECT_TRUE(pattern_->UpdateCurrentOffset(offset, form));
        FlushLayoutTask(frameNode_);
        EXPECT_TRUE(IsEqual(scrollBar->GetBarRect(), barRect));
        if (isAtBottom) {
            EXPECT_FLOAT_EQ(pattern_->GetBarOffset(), 0);
            EXPECT_TRUE(IsEqual(scrollBar->GetActiveRect(), activeRectInit));
        } else {
            EXPECT_FLOAT_EQ(pattern_->GetBarOffset(), -1200);
            EXPECT_TRUE(IsEqual(scrollBar->GetActiveRect(), activeRectBot));
        }
    }
}

/**
 * @tc.name: Pattern016
 * @tc.desc: Test UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List
     */
    int32_t itemNumber = 20;
    Create([=](ListModelNG model) {
        CreateItem(itemNumber);
        model.SetScrollBar(Ace::DisplayMode::ON);
        model.SetEdgeEffect(EdgeEffect::SPRING, false);
    });

    auto scrollBar = pattern_->GetScrollBar();
    Rect barRect = scrollBar->GetBarRect();
    Rect activeRectInit = scrollBar->GetActiveRect();
    Rect activeRectBot = Rect(LIST_WIDTH, LIST_HEIGHT - activeRectInit.Height(), 0, activeRectInit.Height());

    std::vector<int32_t> scrollFromVector = { SCROLL_FROM_NONE, SCROLL_FROM_UPDATE, SCROLL_FROM_ANIMATION,
        SCROLL_FROM_JUMP, SCROLL_FROM_ANIMATION_SPRING, SCROLL_FROM_BAR, SCROLL_FROM_ANIMATION_CONTROLLER,
        SCROLL_FROM_BAR_FLING };

    for (int32_t form : scrollFromVector) {
        bool isAtBottom = pattern_->IsAtBottom();
        float offset = isAtBottom ? 3 * LIST_HEIGHT : -3 * LIST_HEIGHT;
        EXPECT_TRUE(pattern_->UpdateCurrentOffset(offset, form));
        FlushLayoutTask(frameNode_);
        EXPECT_TRUE(IsEqual(scrollBar->GetBarRect(), barRect));
        if (isAtBottom) {
            EXPECT_FLOAT_EQ(pattern_->GetBarOffset(), 0);
            EXPECT_TRUE(IsEqual(scrollBar->GetActiveRect(), activeRectInit));
        } else {
            EXPECT_FLOAT_EQ(pattern_->GetBarOffset(), -1200);
            EXPECT_TRUE(IsEqual(scrollBar->GetActiveRect(), activeRectBot));
        }
    }
}

/**
 * @tc.name: ContentEndOffset001
 * @tc.desc: Test ContentEndOffset should change behavior of IsAtBottom
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ContentEndOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List
     */
    Create([](ListModelNG model) {
        // total height = 2000
        CreateItem(20);
        model.SetScrollBar(Ace::DisplayMode::ON);
        model.SetEdgeEffect(EdgeEffect::FADE, false);
        model.SetContentEndOffset(100);
    });

    std::vector<int32_t> scrollFromVector = { SCROLL_FROM_NONE, SCROLL_FROM_UPDATE, SCROLL_FROM_ANIMATION,
        SCROLL_FROM_JUMP, SCROLL_FROM_ANIMATION_SPRING, SCROLL_FROM_BAR, SCROLL_FROM_ANIMATION_CONTROLLER,
        SCROLL_FROM_BAR_FLING };

    // ~ -1200 to reach bottom if no contentEndOffset
    EXPECT_TRUE(pattern_->UpdateCurrentOffset(-1195, SCROLL_FROM_UPDATE));
    FlushLayoutTask(frameNode_);
    EXPECT_FALSE(pattern_->IsAtBottom());

    // contentEndOffset_ takes 100 extra offset to reach bottom
    EXPECT_TRUE(pattern_->UpdateCurrentOffset(-50, SCROLL_FROM_UPDATE));
    FlushLayoutTask(frameNode_);
    EXPECT_FALSE(pattern_->IsAtBottom());

    EXPECT_TRUE(pattern_->UpdateCurrentOffset(-100, SCROLL_FROM_UPDATE));
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(pattern_->IsAtBottom());
}

/**
 * @tc.name: SwiperItem021
 * @tc.desc: Test swipeAction
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SwiperItem021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List
     */
    auto startFunc = GetDefaultSwiperBuilder(START_NODE_LEN);
    auto endFunc = GetDefaultSwiperBuilder(END_NODE_LEN);
    Create([startFunc, endFunc](
               ListModelNG model) { CreateItemWithSwipe(startFunc, endFunc, V2::SwipeEdgeEffect::None); });
    auto childNode = GetChildFrameNode(frameNode_, 0);
    auto childPattern = childNode->GetPattern<ListItemPattern>();
    auto childLayoutProperty = childNode->GetLayoutProperty<ListItemLayoutProperty>();
    int32_t childrenSize = childNode->GetChildren().size();
    EXPECT_EQ(childLayoutProperty->GetEdgeEffectValue(), V2::SwipeEdgeEffect::None);

    /**
     * @tc.steps: step2. swipeAction set null.
     * @tc.expected: check whether the properties is correct.
     */
    childLayoutProperty->UpdateEdgeEffect(V2::SwipeEdgeEffect::Spring);
    childPattern->SetStartNode(nullptr);
    childPattern->SetEndNode(nullptr);
    EXPECT_EQ(childNode->GetChildren().size(), childrenSize - 2);
    EXPECT_EQ(childLayoutProperty->GetEdgeEffectValue(), V2::SwipeEdgeEffect::Spring);

    /**
     * @tc.steps: step3. set swipeAction.
     * @tc.expected: check whether the properties is correct.
     */
    childLayoutProperty->UpdateEdgeEffect(V2::SwipeEdgeEffect::None);
    startFunc();
    childPattern->SetStartNode(ViewStackProcessor::GetInstance()->Finish());
    endFunc();
    childPattern->SetEndNode(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(childNode->GetChildren().size(), childrenSize);
    EXPECT_EQ(childLayoutProperty->GetEdgeEffectValue(), V2::SwipeEdgeEffect::None);
}

/**
 * @tc.name: ScrollToIndex006
 * @tc.desc: Test ScrollToIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ScrollToIndex006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List
     */
    const int32_t itemNumber = 20;
    Create([=](ListModelNG model) { CreateItem(itemNumber); });
    EXPECT_EQ(frameNode_->GetChildren().size(), itemNumber);

    /**
     * @tc.steps: step2. scroll to finally listItem.
     * @tc.expected: check whether the properties is correct.
     */
    EXPECT_TRUE(ScrollToIndex(itemNumber - 1, true, ScrollAlign::START, 1200.f));
    EXPECT_TRUE(ScrollToIndex(itemNumber - 1, true, ScrollAlign::CENTER, 1200.f));
    EXPECT_TRUE(ScrollToIndex(itemNumber - 1, true, ScrollAlign::END, 1200.f));
    EXPECT_TRUE(ScrollToIndex(itemNumber - 1, true, ScrollAlign::AUTO, 1200.f));
    EXPECT_TRUE(ScrollToIndex(itemNumber - 1, false, ScrollAlign::START, 1200.f));
    EXPECT_TRUE(ScrollToIndex(itemNumber - 1, false, ScrollAlign::CENTER, 1200.f));
    EXPECT_TRUE(ScrollToIndex(itemNumber - 1, false, ScrollAlign::END, 1200.f));
    EXPECT_TRUE(ScrollToIndex(itemNumber - 1, false, ScrollAlign::AUTO, 1200.f));

    /**
     * @tc.steps: step3. add listItem and scroll to the Item.
     * @tc.expected: check whether the properties is correct.
     */
    {
        ListItemModelNG itemModel;
        itemModel.Create();
        ViewAbstract::SetHeight(CalcLength(ITEM_HEIGHT));
        ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
        RefPtr<UINode> currentNode = ViewStackProcessor::GetInstance()->Finish();
        auto currentFrameNode = AceType::DynamicCast<FrameNode>(currentNode);
        currentFrameNode->MountToParent(frameNode_);
    }
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(frameNode_->GetChildren().size(), itemNumber + 1);
    EXPECT_TRUE(ScrollToIndex(itemNumber, true, ScrollAlign::START, 1300.f));
    EXPECT_TRUE(ScrollToIndex(itemNumber, true, ScrollAlign::CENTER, 1300.f));
    EXPECT_TRUE(ScrollToIndex(itemNumber, true, ScrollAlign::END, 1300.f));
    EXPECT_TRUE(ScrollToIndex(itemNumber, true, ScrollAlign::AUTO, 1300.f));
    EXPECT_TRUE(ScrollToIndex(itemNumber, false, ScrollAlign::START, 1300.f));
    EXPECT_TRUE(ScrollToIndex(itemNumber, false, ScrollAlign::CENTER, 1300.f));
    EXPECT_TRUE(ScrollToIndex(itemNumber, false, ScrollAlign::END, 1300.f));
    EXPECT_TRUE(ScrollToIndex(itemNumber, false, ScrollAlign::AUTO, 1300.f));
}

/**
 * @tc.name: ContentOffset001
 * @tc.desc: Test top content offset and bottom end offset
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ContentOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List
     * @tc.expected: Total Offset is negative contentStartOffset.
     */
    const int32_t itemNumber = 20;
    const float contentStartOffset = 100;
    const float contentEndOffset = 50;
    Create([=](ListModelNG model) {
        model.SetContentStartOffset(contentStartOffset);
        model.SetContentEndOffset(contentEndOffset);
        CreateItem(itemNumber);
    });

    for (int32_t index = 0; index < 7; index++) {
        EXPECT_EQ(GetChildRect(frameNode_, index).GetY(), contentStartOffset + index * ITEM_HEIGHT);
    }

    float offset = pattern_->GetTotalOffset();
    EXPECT_FLOAT_EQ(offset, -contentStartOffset);

    /**
     * @tc.steps: step2. scroll to bottom
     * @tc.expected: Bottom content offset equal to contentEndOffset.
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM);
    offset = pattern_->GetTotalOffset();
    EXPECT_FLOAT_EQ(offset, itemNumber * ITEM_HEIGHT - LIST_HEIGHT + contentEndOffset);

    /**
     * @tc.steps: step3. scroll to top
     * @tc.expected: Bottom content offset equal to contentEndOffset.
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP);
    offset = pattern_->GetTotalOffset();
    EXPECT_FLOAT_EQ(offset, -contentStartOffset);
}

/**
 * @tc.name: ContentOffset002
 * @tc.desc: Test scroll to Index with content offset
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ContentOffset002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List
     */
    const int32_t itemNumber = 20;
    const float contentStartOffset = 100;
    const float contentEndOffset = 50;
    Create([=](ListModelNG model) {
        model.SetContentStartOffset(contentStartOffset);
        model.SetContentEndOffset(contentEndOffset);
        CreateItem(itemNumber);
    });

    /**
     * @tc.steps: step2. scroll to target item align start.
     * @tc.expected: check whether the offset is correct.
     */
    EXPECT_TRUE(ScrollToIndex(0, false, ScrollAlign::START, -contentStartOffset));
    EXPECT_TRUE(ScrollToIndex(1, false, ScrollAlign::START, ITEM_HEIGHT - contentStartOffset));
    EXPECT_TRUE(ScrollToIndex(2, false, ScrollAlign::START, ITEM_HEIGHT * 2 - contentStartOffset));
    ScrollToIndex(0, true, ScrollAlign::START);
    EXPECT_EQ(pattern_->GetTotalOffset(), -contentStartOffset);
    ScrollToIndex(1, true, ScrollAlign::START);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_HEIGHT - contentStartOffset);
    ScrollToIndex(2, true, ScrollAlign::START);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_HEIGHT * 2 - contentStartOffset);

    /**
     * @tc.steps: step3. scroll to target item align end.
     * @tc.expected: check whether the offset is correct.
     */
    const float MAX_OFFSET = itemNumber * ITEM_HEIGHT - LIST_HEIGHT + contentEndOffset;
    EXPECT_TRUE(ScrollToIndex(itemNumber - 1, false, ScrollAlign::END, MAX_OFFSET));
    EXPECT_TRUE(ScrollToIndex(itemNumber - 2, false, ScrollAlign::END, MAX_OFFSET - ITEM_HEIGHT));
    EXPECT_TRUE(ScrollToIndex(itemNumber - 3, false, ScrollAlign::END, MAX_OFFSET - ITEM_HEIGHT * 2));
    ScrollToIndex(itemNumber - 1, true, ScrollAlign::END);
    EXPECT_EQ(pattern_->GetTotalOffset(), MAX_OFFSET);
    ScrollToIndex(itemNumber - 2, true, ScrollAlign::END);
    EXPECT_EQ(pattern_->GetTotalOffset(), MAX_OFFSET - ITEM_HEIGHT);
    ScrollToIndex(itemNumber - 3, true, ScrollAlign::END);
    EXPECT_EQ(pattern_->GetTotalOffset(), MAX_OFFSET - ITEM_HEIGHT * 2);
}

/**
 * @tc.name: ContentOffset003
 * @tc.desc: Test scroll to ListItemGroup with content offset
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ContentOffset003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List
     */
    const int32_t GroupNumber = 5;
    const float contentStartOffset = 100;
    const float contentEndOffset = 50;
    Create([=](ListModelNG model) {
        model.SetContentStartOffset(contentStartOffset);
        model.SetContentEndOffset(contentEndOffset);
        CreateGroup(GroupNumber);
    });

    /**
     * @tc.steps: step2. scroll to target group align start.
     * @tc.expected: check whether the offset is correct.
     */
    for (int32_t i = 0; i < 3; i++) {
        ScrollToIndex(i, false, ScrollAlign::START);
        EXPECT_EQ(GetChildRect(frameNode_, i).GetY(), contentStartOffset);
    }
    for (int32_t i = 0; i < 3; i++) {
        ScrollToIndex(i, true, ScrollAlign::START);
        EXPECT_EQ(GetChildRect(frameNode_, i).GetY(), contentStartOffset);
    }

    /**
     * @tc.steps: step3. scroll to target group align end.
     * @tc.expected: check whether the offset is correct.
     */
    for (int32_t i = 0; i < 3; i++) {
        int32_t index = GroupNumber - i - 1;
        ScrollToIndex(index, false, ScrollAlign::END);
        auto rect = GetChildRect(frameNode_, index);
        EXPECT_EQ(rect.Bottom(), LIST_HEIGHT - contentEndOffset);
    }
    for (int32_t i = 0; i < 3; i++) {
        int32_t index = GroupNumber - i - 1;
        ScrollToIndex(index, true, ScrollAlign::END);
        auto rect = GetChildRect(frameNode_, index);
        EXPECT_EQ(rect.Bottom(), LIST_HEIGHT - contentEndOffset);
    }
}

/**
 * @tc.name: ContentOffset004
 * @tc.desc: Test ListItemGroup Sticky postion
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ContentOffset004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List
     */
    const int32_t groupNumber = 5;
    const float contentStartOffset = 100;
    const float contentEndOffset = 50;
    Create([=](ListModelNG model) {
        model.SetContentStartOffset(contentStartOffset);
        model.SetContentEndOffset(contentEndOffset);
        CreateGroupWithSetting(groupNumber, Axis::VERTICAL, V2::ListItemGroupStyle::NONE);
    });

    /**
     * @tc.steps: step2. Scroll To ListItem in group.
     * @tc.expected: ListItem position is correct.
     */
    ScrollToItemInGroup(1, 1, false, ScrollAlign::START);
    auto group1 = GetChildFrameNode(frameNode_, 1);
    auto groupRect = group1->GetGeometryNode()->GetFrameRect();
    float groupPos = groupRect.Top();
    auto item1Rect = GetChildRect(group1, 3);
    EXPECT_EQ(item1Rect.Top(), contentStartOffset - groupPos);

    ScrollToItemInGroup(2, 2, false, ScrollAlign::END);
    auto group2 = GetChildFrameNode(frameNode_, 2);
    groupPos = group2->GetGeometryNode()->GetFrameRect().Top();
    auto item2Rect = GetChildRect(group1, 4);
    EXPECT_EQ(item2Rect.Bottom(), LIST_HEIGHT - contentEndOffset - groupPos);

    ScrollToItemInGroup(1, 1, true, ScrollAlign::START);
    group1 = GetChildFrameNode(frameNode_, 1);
    groupRect = group1->GetGeometryNode()->GetFrameRect();
    groupPos = groupRect.Top();
    item1Rect = GetChildRect(group1, 3);
    EXPECT_EQ(item1Rect.Top(), contentStartOffset - groupPos);

    ScrollToItemInGroup(2, 2, true, ScrollAlign::END);
    group2 = GetChildFrameNode(frameNode_, 2);
    groupPos = group2->GetGeometryNode()->GetFrameRect().Top();
    item2Rect = GetChildRect(group1, 4);
    EXPECT_EQ(item2Rect.Bottom(), LIST_HEIGHT - contentEndOffset - groupPos);
}

/**
 * @tc.name: ContentOffset005
 * @tc.desc: Test ListItemGroup Sticky postion
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ContentOffset005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List
     */
    const int32_t groupNumber = 5;
    const float contentStartOffset = 100;
    const float contentEndOffset = 50;
    Create([=](ListModelNG model) {
        model.SetContentStartOffset(contentStartOffset);
        model.SetContentEndOffset(contentEndOffset);
        model.SetSticky(V2::StickyStyle::BOTH);
        CreateGroupWithSetting(groupNumber, Axis::VERTICAL, V2::ListItemGroupStyle::NONE);
    });

    /**
     * @tc.steps: step2. scroll by 100.
     * @tc.expected: header stick postion and footer sticky postion is correct.
     */
    pattern_->UpdateCurrentOffset(-100, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    auto group0 = GetChildFrameNode(frameNode_, 0);
    auto groupPos = group0->GetGeometryNode()->GetFrameRect().Top();
    auto header0Rect = GetChildRect(group0, 0);
    EXPECT_EQ(header0Rect.Top(), contentStartOffset - groupPos);

    auto group1 = GetChildFrameNode(frameNode_, 1);
    groupPos = group1->GetGeometryNode()->GetFrameRect().Top();
    auto footer1Rect = GetChildRect(group1, 1);
    EXPECT_EQ(footer1Rect.Bottom(), LIST_HEIGHT - contentEndOffset - groupPos);

    /**
     * @tc.steps: step3. Scroll To ListItem in group.
     * @tc.expected: ListItem position is correct.
     */
    ScrollToItemInGroup(1, 1, false, ScrollAlign::START);
    group1 = GetChildFrameNode(frameNode_, 1);
    groupPos = group1->GetGeometryNode()->GetFrameRect().Top();
    auto item1Rect = GetChildRect(group1, 3);
    EXPECT_EQ(item1Rect.Top(), contentStartOffset + GROUP_HEADER_LEN - groupPos);

    ScrollToItemInGroup(2, 2, false, ScrollAlign::END);
    auto group2 = GetChildFrameNode(frameNode_, 2);
    groupPos = group2->GetGeometryNode()->GetFrameRect().Top();
    auto item2Rect = GetChildRect(group2, 4);
    EXPECT_EQ(item2Rect.Bottom(), LIST_HEIGHT - contentEndOffset - GROUP_HEADER_LEN - groupPos);

    ScrollToItemInGroup(1, 1, true, ScrollAlign::START);
    group1 = GetChildFrameNode(frameNode_, 1);
    groupPos = group1->GetGeometryNode()->GetFrameRect().Top();
    item1Rect = GetChildRect(group1, 3);
    EXPECT_EQ(item1Rect.Top(), contentStartOffset + GROUP_HEADER_LEN - groupPos);

    ScrollToItemInGroup(2, 2, true, ScrollAlign::END);
    group2 = GetChildFrameNode(frameNode_, 2);
    groupPos = group2->GetGeometryNode()->GetFrameRect().Top();
    item2Rect = GetChildRect(group2, 4);
    EXPECT_EQ(item2Rect.Bottom(), LIST_HEIGHT - contentEndOffset - GROUP_HEADER_LEN - groupPos);
}

/**
 * @tc.name: ContentOffset006
 * @tc.desc: Test top content offset and bottom end offset
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ContentOffset006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List with ScrollSnapAlign START
     * @tc.expected:
     */
    const int32_t itemNumber = 20;
    const float contentStartOffset = 100;
    const float contentEndOffset = 50;
    Create([=](ListModelNG model) {
        model.SetContentStartOffset(contentStartOffset);
        model.SetContentEndOffset(contentEndOffset);
        model.SetScrollSnapAlign(V2::ScrollSnapAlign::START);
        CreateItem(itemNumber);
    });

    /**
     * @tc.steps: step2. scroll snap
     * @tc.expected: item top snap to contentEndOffset.
     */
    ScrollSnap(-120, 0);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), ITEM_HEIGHT - contentStartOffset);
    ScrollSnap(-80, 0);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), ITEM_HEIGHT * 2 - contentStartOffset);

    /**
     * @tc.steps: step3. change scroll snap to END
     * @tc.expected: item bottom snap to contentEndOffset.
     */
    float firstEndSnap = -contentEndOffset; // LIST_HEIGHT % ITEM_HEIGHT - contentEndOffset;
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP);
    layoutProperty_->UpdateScrollSnapAlign(V2::ScrollSnapAlign::END);
    ScrollSnap(-40, 0);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), firstEndSnap);
    ScrollSnap(-110, 0);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), ITEM_HEIGHT + firstEndSnap);
}
} // namespace OHOS::Ace::NG
