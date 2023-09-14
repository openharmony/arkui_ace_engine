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

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#define private public
#define protected public
#include "core/components/scroll/scrollable.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/linear_layout/row_model_ng.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_model_ng.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components/button/button_theme.h"
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
#include "core/components_ng/test/mock/render/mock_render_context.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_ng/test/pattern/test_ng.h"
#include "core/components_v2/list/list_properties.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"
#include "frameworks/bridge/common/utils/utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float GROUP_WIDTH = 400.f;
constexpr float GROUP_HEIGHT = 600.f;
constexpr float GROUP_ITEM_WIDTH = 300.f;
constexpr int32_t TOTAL_NUMBER = 10;
constexpr int32_t VIEWPORT_NUMBER = 8;
constexpr int32_t GROUP_ITEM_NUMBER = 4;
constexpr float ITEM_HEIGHT = 100.f;
constexpr float ITEM_WIDTH = 60.f;
constexpr float HEADER_MAIN_LENGTH = 50.f;
constexpr float START_NODE_SIZE = 80.f;
constexpr float END_NODE_SIZE = 100.f;
constexpr float DELETE_AREA_DISTANCE = 50.f;
constexpr Dimension GROUP_MARGIN = 12.0_vp;
constexpr float DEFAULT_STIFFNESS = 228;
constexpr float DEFAULT_DAMPING = 30;
constexpr float SWIPER_SPEED_TH = 1200.f;
constexpr float SWIPER_TH = 0.25f;
constexpr int32_t DEFAULT_LANES = 1;
constexpr int32_t DEFAULT_SPACE = 0;
constexpr int32_t DEFAULT_STARTINDEX = 0;
constexpr float SPACE = 10.f;
constexpr float STROKE_WIDTH = 5.f;
const V2::ItemDivider ITEM_DIVIDER = { Dimension(STROKE_WIDTH), Dimension(10), Dimension(20), Color(0x000000)};
} // namespace

class ListTestNg : public testing::Test, public TestNG {
protected:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();

    void CreateList(const std::function<void(ListModelNG)>& callback = nullptr);
    void CreateListWithItem(const std::function<void(ListModelNG)>& callback = nullptr);
    void CreateSwipeList(bool isStartNode, V2::SwipeEdgeEffect swipeEdgeEffect, int32_t itemNumber = TOTAL_NUMBER);
    void CreateListItemWithSwipeActionItem(std::function<void()> builderAction, bool useDefaultDeleteAnimation,
        OnDeleteEvent onDelete, OnEnterDeleteAreaEvent onEnterDeleteArea, OnExitDeleteAreaEvent onExitDeleteArea,
        const Dimension& length, bool isStartArea, V2::SwipeEdgeEffect effect);

    static void CreateListItem(int32_t itemNumber, Axis axis = Axis::VERTICAL, bool focusable = false);
    static void CreateListItemGroup();
    static void CreateListItemGroup(int32_t groupNumber, Axis axis = Axis::VERTICAL, bool focusable = false);
    static void CreateListItemWithSwiper(
        std::function<void()> startAction, std::function<void()> endAction, V2::SwipeEdgeEffect effect);
    static std::function<void()> GetDefaultSwiperBuilder(float crossSize);
    static std::function<void()> GetDefaultHeaderBuilder();

    void UpdateCurrentOffset(float offset, int32_t source = SCROLL_FROM_UPDATE);
    void ScrollUp(float itemNumber = 1);
    void ScrollDown(float itemNumber = 1);
    void ScrollToEdge(ScrollEdgeType scrollEdgeType);
    void MouseSelect(Offset start, Offset end);
    void DragSwiperItem(int32_t index, float mainDelta, float mainVelocity = SWIPER_SPEED_TH);
    void HandleDragStart(int32_t index);
    void HandleDragUpdate(int32_t index, float mainDelta);
    void HandleDragEnd(int32_t index, float mainVelocity = SWIPER_SPEED_TH);

    testing::AssertionResult VerifyItemPosition(int32_t viewItemNumber, int32_t lanes = DEFAULT_LANES,
        float space = DEFAULT_SPACE, int32_t startIndex = DEFAULT_STARTINDEX);
    testing::AssertionResult VerifyGroupItemPosition(
        RefPtr<FrameNode> groupNode, int32_t viewItemNumber, int32_t lanes = DEFAULT_LANES,
        float space = DEFAULT_SPACE, float startOffset = 0);
    testing::AssertionResult IsEqualTotalOffset(float expectOffset);
    testing::AssertionResult IsEqualNextFocusNode(FocusStep step, int32_t currentIndex, int32_t expectNextIndex);
    testing::AssertionResult ScrollToIndex(int32_t index, bool smooth, ScrollAlign align, float expectOffset);
    testing::AssertionResult ScrollToIndex(int32_t index, int32_t indexInGroup, ScrollAlign align, float expectOffset);
    std::vector<RefPtr<FrameNode>> GetALLItem();
    int32_t findFocusNodeIndex(RefPtr<FocusHub>& focusNode);

    RefPtr<FrameNode> frameNode_;
    RefPtr<ListPattern> pattern_;
    RefPtr<ListEventHub> eventHub_;
    RefPtr<ListLayoutProperty> layoutProperty_;
    RefPtr<ListPaintProperty> paintProperty_;
    RefPtr<ListAccessibilityProperty> accessibilityProperty_;
};

void ListTestNg::SetUpTestSuite()
{
    MockPipelineBase::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
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
    MockPipelineBase::TearDown();
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
    paintProperty_ = frameNode_->GetPaintProperty<ListPaintProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<ListAccessibilityProperty>();
    EXPECT_CALL(
        *AceType::DynamicCast<MockRenderContext>(frameNode_->renderContext_),
        GetPaintRectWithTransform())
        .WillRepeatedly(Return(RectF()));
}

void ListTestNg::CreateList(const std::function<void(ListModelNG)>& callback)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    RefPtr<ScrollControllerBase> scrollController = listModelNG.CreateScrollController();
    RefPtr<ScrollProxy> proxy = AceType::MakeRefPtr<NG::ScrollBarProxy>();
    listModelNG.SetScroller(scrollController, proxy);
    if (callback) {
        callback(listModelNG);
    }
    GetInstance();
    RunMeasureAndLayout(frameNode_);
}

void ListTestNg::CreateListWithItem(const std::function<void(ListModelNG)>& callback)
{
    CreateList([callback](ListModelNG listModelNG) {
        if (callback) {
            callback(listModelNG);
        }
        CreateListItem(TOTAL_NUMBER);
    });
}

void ListTestNg::CreateSwipeList(bool isStartNode, V2::SwipeEdgeEffect swipeEdgeEffect, int32_t itemNumber)
{
    CreateList([isStartNode, swipeEdgeEffect, itemNumber](ListModelNG listModelNG) {
        auto startFunc = GetDefaultSwiperBuilder(START_NODE_SIZE);
        auto endFunc = GetDefaultSwiperBuilder(END_NODE_SIZE);
        for (int32_t index = 0; index < itemNumber; index++) {
            if (isStartNode) {
                CreateListItemWithSwiper(startFunc, nullptr, swipeEdgeEffect);
            } else {
                CreateListItemWithSwiper(nullptr, endFunc, swipeEdgeEffect);
            }
        }
    });
}

void ListTestNg::CreateListItemWithSwipeActionItem(std::function<void()> builderAction, bool useDefaultDeleteAnimation,
    OnDeleteEvent onDelete, OnEnterDeleteAreaEvent onEnterDeleteArea, OnExitDeleteAreaEvent onExitDeleteArea,
    const Dimension& length, bool isStartArea, V2::SwipeEdgeEffect effect)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    ListItemModelNG listItemModel;
    listItemModel.Create();
    SetHeight(Dimension(ITEM_HEIGHT));
    SetWidth(FILL_LENGTH);
    listItemModel.SetSwiperAction(nullptr, nullptr, effect);
    listItemModel.SetDeleteArea(std::move(builderAction), useDefaultDeleteAnimation, std::move(onDelete),
        std::move(onEnterDeleteArea), std::move(onExitDeleteArea), length, isStartArea);
    {
        RowModelNG rowModel;
        rowModel.Create(std::nullopt, nullptr, "");
        SetHeight(Dimension(ITEM_HEIGHT));
        SetWidth(FILL_LENGTH);
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();
    GetInstance();
    RunMeasureAndLayout(frameNode_);
}

void ListTestNg::CreateListItem(int32_t itemNumber, Axis axis, bool focusable)
{
    for (int32_t index = 0; index < itemNumber; index++) {
        ListItemModelNG listItemModel;
        listItemModel.Create();
        if (axis == Axis::VERTICAL) {
            SetHeight(Dimension(ITEM_HEIGHT));
            SetWidth(FILL_LENGTH);
        } else {
            SetWidth(Dimension(ITEM_WIDTH));
            SetHeight(FILL_LENGTH);
        }
        if (focusable) {
            ButtonModelNG buttonModelNG;
            buttonModelNG.CreateWithLabel("label");
            ViewStackProcessor::GetInstance()->Pop();
        }
        ViewStackProcessor::GetInstance()->Pop();
    }
}

void ListTestNg::CreateListItemGroup(int32_t groupNumber, Axis axis, bool focusable)
{
    for (int32_t index = 0; index < groupNumber; index++) {
        ListItemGroupModelNG listItemGroupModel;
        listItemGroupModel.Create(V2::ListItemGroupStyle::NONE);
        // do not fill List
        if (axis == Axis::VERTICAL) {
            SetWidth(Dimension(GROUP_WIDTH));
        } else {
            SetHeight(Dimension(GROUP_HEIGHT));
        }
        CreateListItem(GROUP_ITEM_NUMBER, axis, focusable);
        ViewStackProcessor::GetInstance()->Pop();
    }
}

void ListTestNg::CreateListItemGroup()
{
    // V2::ListItemGroupStyle::NONE
    auto header = GetDefaultHeaderBuilder();
    auto footer = GetDefaultHeaderBuilder();
    ListItemGroupModelNG listItemGroupModel_1;
    listItemGroupModel_1.Create(V2::ListItemGroupStyle::NONE);
    listItemGroupModel_1.SetSpace(Dimension(SPACE));
    listItemGroupModel_1.SetDivider(ITEM_DIVIDER);
    listItemGroupModel_1.SetHeader(std::move(header));
    listItemGroupModel_1.SetFooter(std::move(footer));
    SetWidth(Dimension(GROUP_WIDTH));
    CreateListItem(GROUP_ITEM_NUMBER);
    ViewStackProcessor::GetInstance()->Pop();

    // SetWidth
    // V2::ListItemGroupStyle::NONE
    ListItemGroupModelNG listItemGroupModel_2;
    listItemGroupModel_2.Create(V2::ListItemGroupStyle::NONE);
    listItemGroupModel_2.SetSpace(Dimension(SPACE));
    listItemGroupModel_2.SetHeader(std::move(header));
    listItemGroupModel_2.SetFooter(std::move(footer));
    SetWidth(Dimension(GROUP_WIDTH));
    for (int32_t index = 0; index < GROUP_ITEM_NUMBER; index++) {
        ListItemModelNG listItemModel;
        listItemModel.Create();
        SetHeight(Dimension(ITEM_HEIGHT));
        SetWidth(Dimension(GROUP_ITEM_WIDTH));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();

    // V2::ListItemGroupStyle::CARD
    ListItemGroupModelNG listItemGroupModel_3;
    listItemGroupModel_3.Create(V2::ListItemGroupStyle::CARD);
    listItemGroupModel_3.SetSpace(Dimension(SPACE));
    listItemGroupModel_3.SetDivider(ITEM_DIVIDER);
    SetWidth(Dimension(GROUP_WIDTH));
    CreateListItem(GROUP_ITEM_NUMBER);
    ViewStackProcessor::GetInstance()->Pop();

    // SetWidth
    ListItemGroupModelNG listItemGroupModel_4;
    listItemGroupModel_4.Create(V2::ListItemGroupStyle::NONE);
    SetWidth(Dimension(Infinity<float>()));
    CreateListItem(GROUP_ITEM_NUMBER);
    ViewStackProcessor::GetInstance()->Pop();

    // has no listItem
    ListItemGroupModelNG listItemGroupModel_5;
    listItemGroupModel_5.Create(V2::ListItemGroupStyle::NONE);
    SetWidth(Dimension(GROUP_WIDTH));
    ViewStackProcessor::GetInstance()->Pop();
}

void ListTestNg::CreateListItemWithSwiper(
    std::function<void()> startAction, std::function<void()> endAction, V2::SwipeEdgeEffect effect)
{
    ListItemModelNG listItemModel;
    listItemModel.Create();
    SetWidth(FILL_LENGTH);
    SetHeight(Dimension(ITEM_HEIGHT));
    listItemModel.SetSwiperAction(std::move(startAction), std::move(endAction), effect);
    {
        RowModelNG rowModel;
        rowModel.Create(std::nullopt, nullptr, "");
        SetWidth(FILL_LENGTH);
        SetHeight(Dimension(ITEM_HEIGHT));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();
}

std::function<void()> ListTestNg::GetDefaultSwiperBuilder(float crossSize)
{
    return [crossSize]() {
        RowModelNG rowModel;
        rowModel.Create(std::nullopt, nullptr, "");
        SetWidth(Dimension(crossSize));
        SetHeight(Dimension(ITEM_HEIGHT));
    };
}

std::function<void()> ListTestNg::GetDefaultHeaderBuilder()
{
    return []() {
        RowModelNG rowModel;
        rowModel.Create(std::nullopt, nullptr, "");
        SetWidth(FILL_LENGTH);
        SetHeight(Dimension(HEADER_MAIN_LENGTH));
    };
}

void ListTestNg::UpdateCurrentOffset(float offset, int32_t source)
{
    pattern_->UpdateCurrentOffset(offset, source);
    RunMeasureAndLayout(frameNode_);
}

void ListTestNg::ScrollUp(float itemNumber)
{
    float offset = ITEM_HEIGHT * itemNumber;
    pattern_->UpdateCurrentOffset(offset, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout(frameNode_);
}

void ListTestNg::ScrollDown(float itemNumber)
{
    float offset = -ITEM_HEIGHT * itemNumber;
    pattern_->UpdateCurrentOffset(offset, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout(frameNode_);
}

void ListTestNg::ScrollToEdge(ScrollEdgeType scrollEdgeType)
{
    pattern_->ScrollToEdge(scrollEdgeType);
    RunMeasureAndLayout(frameNode_);
}

void ListTestNg::MouseSelect(Offset start, Offset end)
{
    MouseInfo info;
    info.SetButton(MouseButton::LEFT_BUTTON);
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(start);
    pattern_->HandleMouseEventWithoutKeyboard(info);
    if (start != end) {
        info.SetAction(MouseAction::MOVE);
        info.SetLocalLocation(end);
        pattern_->HandleMouseEventWithoutKeyboard(info);
    }
    info.SetAction(MouseAction::RELEASE);
    pattern_->HandleMouseEventWithoutKeyboard(info);
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
    RunMeasureAndLayout(frameNode_);
}

void ListTestNg::HandleDragEnd(int32_t index, float mainVelocity)
{
    GestureEvent info;
    info.SetMainVelocity(mainVelocity);
    auto itemPattern = GetChildPattern<ListItemPattern>(frameNode_, index);
    itemPattern->HandleDragEnd(info);
    // curOffset_ would be NodeSize or Zero
    double position = itemPattern->springMotion_->GetEndValue();
    itemPattern->UpdatePostion(position - itemPattern->curOffset_);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    RunMeasureAndLayout(frameNode_);
}

testing::AssertionResult ListTestNg::VerifyItemPosition(
    int32_t viewItemNumber, int32_t lanes, float space, int32_t startIndex)
{
    if (lanes < 1) {
        return testing::AssertionFailure() << "lanes < 1";
    }
    auto itemPosition = pattern_->GetItemPosition();
    for (int32_t index = 0; index < viewItemNumber; index++) {
        int32_t itemIndex = index + startIndex;
        auto listItem = itemPosition[itemIndex];
        float startPos = (index / lanes) * (ITEM_HEIGHT + space);
        float endPos = startPos + ITEM_HEIGHT;
        if (!NearEqual(listItem.startPos, startPos) || !NearEqual(listItem.endPos, endPos)) {
            return testing::AssertionFailure() <<
                "At itemPosition Index: " << index <<
                " ItemPosition: (" << listItem.startPos << " - " << listItem.endPos << ")" <<
                " != " <<
                "expectPosition: (" << startPos << " - " << endPos << ")";
        }
    }
    return testing::AssertionSuccess();
}

testing::AssertionResult ListTestNg::VerifyGroupItemPosition(
    RefPtr<FrameNode> groupNode, int32_t viewItemNumber, int32_t lanes, float space, float startOffset)
{
    if (lanes < 1) {
        return testing::AssertionFailure() << "lanes < 1";
    }
    auto itemPosition = groupNode->GetPattern<ListItemGroupPattern>()->GetItemPosition();
    for (int32_t index = 0; index < viewItemNumber; index++) {
        auto listItem = itemPosition[index];
        float startPos = (index / lanes) * (ITEM_HEIGHT + space) + startOffset;
        float endPos = startPos + ITEM_HEIGHT;
        if (!NearEqual(listItem.first, startPos) || !NearEqual(listItem.second, endPos)) {
            return testing::AssertionFailure() <<
                "At itemPosition Index: " << index <<
                " Group ItemPosition: (" << listItem.first << " - " << listItem.second << ")" <<
                " != " <<
                "expectPosition: (" << startPos << " - " << endPos << ")";
        }
    }
    return testing::AssertionSuccess();
}

testing::AssertionResult ListTestNg::IsEqualTotalOffset(float expectOffset)
{
    RunMeasureAndLayout(frameNode_);
    float currentOffset = pattern_->GetTotalOffset();
    if (NearEqual(currentOffset, expectOffset)) {
        return testing::AssertionSuccess();
    }
    return testing::AssertionFailure() <<
        "currentOffset: " << currentOffset <<
        " != " <<
        "expectOffset: " << expectOffset;
}

testing::AssertionResult ListTestNg::IsEqualNextFocusNode(
    FocusStep step, int32_t currentIndex, int32_t expectNextIndex)
{
    std::vector<RefPtr<FrameNode>> listItems = GetALLItem();
    RefPtr<FocusHub> currentFocusNode = listItems[currentIndex]->GetOrCreateFocusHub();
    currentFocusNode->RequestFocusImmediately();
    RefPtr<FocusHub> nextFocusNode = pattern_->GetNextFocusNode(step, currentFocusNode).Upgrade();
    if (expectNextIndex != NULL_INDEX && nextFocusNode == nullptr) {
        return testing::AssertionFailure() << "Next FocusNode is null.";
    }
    int32_t nextIndex = findFocusNodeIndex(nextFocusNode);
    if (expectNextIndex != nextIndex) {
        return testing::AssertionFailure() <<
            "Get wrong Next FocusNode or Next FocusNode is not null. The nextIndex is " <<
            nextIndex;
    }
    return testing::AssertionSuccess();
}

testing::AssertionResult ListTestNg::ScrollToIndex(
    int32_t index, bool smooth, ScrollAlign align, float expectOffset)
{
    float originalOffsetY = pattern_->GetTotalOffset();
    pattern_->ScrollToIndex(index, smooth, align);
    RunMeasureAndLayout(frameNode_);
    float currentOffset = pattern_->GetTotalOffset();
    // reset offset before return
    pattern_->ScrollTo(originalOffsetY);
    RunMeasureAndLayout(frameNode_);
    if (!NearEqual(currentOffset, expectOffset)) {
        return testing::AssertionFailure() <<
            " currentOffset: " << currentOffset <<
            " != " <<
            "expectOffset: " << expectOffset;
    }
    return testing::AssertionSuccess();
}

testing::AssertionResult ListTestNg::ScrollToIndex(
    int32_t index, int32_t indexInGroup, ScrollAlign align, float expectOffset)
{
    float originalOffsetY = pattern_->GetTotalOffset();
    pattern_->ScrollToIndex(index, indexInGroup, align);
    RunMeasureAndLayout(frameNode_);
    float currentOffset = pattern_->GetTotalOffset();
    // reset offset before return
    pattern_->ScrollTo(originalOffsetY);
    RunMeasureAndLayout(frameNode_);
    if (!NearEqual(currentOffset, expectOffset)) {
        return testing::AssertionFailure() <<
            " currentOffset: " << currentOffset <<
            " != " <<
            "expectOffset: " << expectOffset;
    }
    return testing::AssertionSuccess();
}

std::vector<RefPtr<FrameNode>> ListTestNg::GetALLItem()
{
    std::vector<RefPtr<FrameNode>> listItems;
    auto children = frameNode_->GetChildren();
    for (auto child : children) {
        auto childFrameNode = AceType::DynamicCast<FrameNode>(child);
        if (AceType::InstanceOf<ListItemPattern>(childFrameNode->GetPattern())) {
            listItems.emplace_back(childFrameNode);
        }
        if (AceType::InstanceOf<ListItemGroupPattern>(childFrameNode->GetPattern())) {
            auto groupChildren = child->GetChildren();
            for (auto groupItem : groupChildren) {
                auto groupItemFrameNode = AceType::DynamicCast<FrameNode>(groupItem);
                if (AceType::InstanceOf<ListItemPattern>(groupItemFrameNode->GetPattern())) {
                    listItems.emplace_back(groupItemFrameNode);
                }
            }
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
    return NULL_INDEX;
}

/**
 * @tc.name: ListLayoutProperty001
 * @tc.desc: Test List layout properties.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListLayoutProperty001, TestSize.Level1)
{
    CreateList([](ListModelNG listModelNG) {
        listModelNG.SetSpace(Dimension(10));
        listModelNG.SetInitialIndex(1);
        listModelNG.SetListDirection(Axis::VERTICAL);
        listModelNG.SetScrollBar(Ace::DisplayMode::ON);
        listModelNG.SetEditMode(true);
        listModelNG.SetChainAnimation(true);
        listModelNG.SetEdgeEffect(EdgeEffect::NONE);
        listModelNG.SetLanes(3);
        listModelNG.SetLaneMinLength(Dimension(40));
        listModelNG.SetLaneMaxLength(Dimension(60));
        listModelNG.SetListItemAlign(V2::ListItemAlign::CENTER);
        listModelNG.SetCachedCount(10);
        listModelNG.SetSticky(V2::StickyStyle::HEADER);
        listModelNG.SetScrollSnapAlign(V2::ScrollSnapAlign::START);
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
    EXPECT_EQ(json->GetString("edgeEffect"), "EdgeEffect.None");
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
    layoutProperty_->UpdateEdgeEffect(EdgeEffect::FADE);
    layoutProperty_->UpdateListItemAlign(V2::ListItemAlign::END);
    layoutProperty_->UpdateStickyStyle(V2::StickyStyle::FOOTER);
    layoutProperty_->UpdateScrollSnapAlign(V2::ScrollSnapAlign::CENTER);
    layoutProperty_->UpdateDivider(ITEM_DIVIDER);
    json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json);
    EXPECT_EQ(json->GetString("listDirection"), "Axis.Horizontal");
    EXPECT_EQ(json->GetString("edgeEffect"), "EdgeEffect.Fade");
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
    layoutProperty_->UpdateEdgeEffect(EdgeEffect::SPRING);
    layoutProperty_->UpdateListItemAlign(V2::ListItemAlign::START);
    layoutProperty_->UpdateStickyStyle(V2::StickyStyle::BOTH);
    layoutProperty_->UpdateScrollSnapAlign(V2::ScrollSnapAlign::END);
    json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json);
    EXPECT_EQ(json->GetString("edgeEffect"), "EdgeEffect.Spring");
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
    CreateListWithItem();
    auto layoutProperty = GetChildLayoutProperty<ListItemLayoutProperty>(frameNode_, 0);

    /**
     * @tc.steps: step1. Call ToJsonValue()
     * @tc.expected: The json value is correct
     */
    auto json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json);
    EXPECT_EQ(static_cast<V2::StickyMode>(json->GetInt("sticky")), V2::StickyMode::NONE);
    EXPECT_EQ(json->GetBool("editable"), false);
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
 * @tc.desc: Test property about space/divider,
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrSpaceDivider001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set space
     */
    CreateListWithItem([](ListModelNG listModelNG) { listModelNG.SetSpace(Dimension(SPACE)); });
    EXPECT_TRUE(VerifyItemPosition(VIEWPORT_NUMBER, DEFAULT_LANES, SPACE, DEFAULT_STARTINDEX));

    /**
     * @tc.steps: step2. Set divider
     */
    CreateListWithItem([](ListModelNG listModelNG) { listModelNG.SetDivider(ITEM_DIVIDER); });
    EXPECT_TRUE(VerifyItemPosition(VIEWPORT_NUMBER, 1, STROKE_WIDTH));

    /**
     * @tc.steps: step3. Set space less than divider's strokeWidth
     * @tc.expected: space was going to be strokeWidth
     */
    CreateListWithItem([](ListModelNG listModelNG) {
        listModelNG.SetSpace(Dimension(STROKE_WIDTH - 1.f));
        listModelNG.SetDivider(ITEM_DIVIDER);
    });
    EXPECT_TRUE(VerifyItemPosition(VIEWPORT_NUMBER, DEFAULT_LANES, STROKE_WIDTH, DEFAULT_STARTINDEX));
}

/**
 * @tc.name: AttrInitIndex001
 * @tc.desc: Test property about initialIndex,
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrInitIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set initIndex to 1
     * @tc.expected: List layout starting from initialIndex
     */
    CreateListWithItem([](ListModelNG listModelNG) { listModelNG.SetInitialIndex(1); });
    EXPECT_TRUE(VerifyItemPosition(VIEWPORT_NUMBER, DEFAULT_LANES, DEFAULT_SPACE, 1));

    /**
     * @tc.steps: step2. Total ListItem size less than viewport
     * @tc.expected: List layout starting from first ListItem
     */
    CreateList([](ListModelNG listModelNG) {
        listModelNG.SetInitialIndex(1);
        CreateListItem(5);
    });
    EXPECT_TRUE(VerifyItemPosition(5, DEFAULT_LANES, DEFAULT_SPACE, DEFAULT_STARTINDEX));

    /**
     * @tc.steps: step3. The total size of ListItems after initialIndex is less than viewport
     * @tc.expected: ListItem bottom to viewport
     */
    CreateListWithItem([](ListModelNG listModelNG) { listModelNG.SetInitialIndex(5); });
    EXPECT_TRUE(VerifyItemPosition(VIEWPORT_NUMBER, DEFAULT_LANES, DEFAULT_SPACE, 2));

    /**
     * @tc.steps: step4. initialIndex out of range
     * @tc.expected: ignore initialIndex
     */
    CreateListWithItem([](ListModelNG listModelNG) { listModelNG.SetInitialIndex(100); });
    EXPECT_TRUE(VerifyItemPosition(VIEWPORT_NUMBER, DEFAULT_LANES, DEFAULT_SPACE, DEFAULT_STARTINDEX));

    /**
     * @tc.steps: step5. initialIndex is not an integer multiple of the lanes
     * @tc.expected: List layout starting from an index integer multiple of the lanes
     */
    CreateList([](ListModelNG listModelNG) {
        listModelNG.SetInitialIndex(3);
        listModelNG.SetLanes(2);
        CreateListItem(20);
    });
    EXPECT_TRUE(VerifyItemPosition(16, 2, DEFAULT_SPACE, 2));
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
    CreateListWithItem([](ListModelNG listModelNG) { listModelNG.SetScrollBar(Ace::DisplayMode::ON); });
    EXPECT_EQ(pattern_->GetScrollBar()->GetDisplayMode(), DisplayMode::ON);

    /**
     * @tc.steps: step1. Set scrollBar, set api version >= 10
     * @tc.expected: the default value is auto
     */
    MockPipelineBase::pipeline_->SetMinPlatformVersion(PLATFORM_VERSION_TEN);
    CreateListWithItem();
    EXPECT_EQ(pattern_->GetScrollBar()->GetDisplayMode(), DisplayMode::AUTO);
}

/**
 * @tc.name: AttrLanes001
 * @tc.desc: Test property about lanes,
 * List layout as 2 lanes
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrLanes001, TestSize.Level1)
{
    CreateList([](ListModelNG listModelNG) {
        listModelNG.SetLanes(2);
        CreateListItem(19);
    });
    EXPECT_TRUE(VerifyItemPosition(16, 2, DEFAULT_SPACE, DEFAULT_STARTINDEX));
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM);
    EXPECT_TRUE(VerifyItemPosition(15, 2, DEFAULT_SPACE, 4));
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP);
    EXPECT_TRUE(VerifyItemPosition(15, 2, DEFAULT_SPACE, DEFAULT_STARTINDEX));
}

/**
 * @tc.name: AttrLanes002
 * @tc.desc: Test LayoutProperty about minLaneLength, maxLaneLength,
 * List layout as 2 lanes.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrLanes002, TestSize.Level1)
{
    CreateList([](ListModelNG listModelNG) {
        listModelNG.SetLaneMinLength(Dimension(DEVICE_WIDTH / 2 - 1));
        listModelNG.SetLaneMaxLength(Dimension(DEVICE_WIDTH));
        CreateListItem(19);
    });
    EXPECT_TRUE(VerifyItemPosition(16, 2, DEFAULT_SPACE, DEFAULT_STARTINDEX));
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM);
    EXPECT_TRUE(VerifyItemPosition(15, 2, DEFAULT_SPACE, 4));
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP);
    EXPECT_TRUE(VerifyItemPosition(15, 2, DEFAULT_SPACE, DEFAULT_STARTINDEX));

    /**
     * @tc.steps: step1. Check ListItem width.
     * @tc.expected: ListItem width would self-adaption.
     */
    for (int32_t index = 0; index < 15; index++) {
        EXPECT_FLOAT_EQ( GetChildRect(frameNode_, index).Width(), DEVICE_WIDTH / 2);
    }
}

/**
 * @tc.name: AttrLanes003
 * @tc.desc: Test LayoutProperty about minLaneLength, maxLaneLength,
 * when maxLaneLength less than minLaneLength, use minLaneLength
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrLanes003, TestSize.Level1)
{
    const float minLaneLength = DEVICE_WIDTH / 2 - 1;
    CreateList([minLaneLength](ListModelNG listModelNG) {
        listModelNG.SetLaneMinLength(Dimension(minLaneLength));
        listModelNG.SetLaneMaxLength(Dimension(minLaneLength - 1));
        CreateListItem(19);
    });
    EXPECT_TRUE(VerifyItemPosition(16, 2, DEFAULT_SPACE, DEFAULT_STARTINDEX));

    /**
     * @tc.steps: step1. Check ListItem width.
     * @tc.expected: ListItem width would be minLaneLength.
     */
    for (int32_t index = 0; index < 16; index++) {
        EXPECT_FLOAT_EQ(GetChildRect(frameNode_, index).Width(), minLaneLength);
    }
}

/**
 * @tc.name: AttrLanes004
 * @tc.desc: Test LayoutProperty about laneGutter
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrLanes004, TestSize.Level1)
{
    const float laneGutter = 16.f;
    const int32_t lanes = 2;
    CreateListWithItem([lanes, laneGutter](ListModelNG listModelNG) {
        listModelNG.SetLanes(lanes);
        listModelNG.SetLaneGutter(Dimension(laneGutter));
    });
    float itemWidth = (DEVICE_WIDTH - laneGutter * (lanes - 1)) / lanes;
    for (int32_t index = 0; index < VIEWPORT_NUMBER; index++) {
        RectF expectRect = RectF(
            (itemWidth + laneGutter) * (index % lanes),
            ITEM_HEIGHT * std::floor(index / lanes),
            itemWidth,
            ITEM_HEIGHT
        );
        EXPECT_TRUE(IsEqualRect(GetChildRect(frameNode_, index), expectRect));
    }
}

/**
 * @tc.name: AttrAlignListItem001
 * @tc.desc: Test LayoutProperty about alignListItem,
 * when ListItem width less than List, the default is align to start
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrAlignListItem001, TestSize.Level1)
{
    constexpr float itemWidth = 400.f;
    CreateList([itemWidth](ListModelNG listModelNG) {
        for (int32_t index = 0; index < TOTAL_NUMBER; index++) {
            ListItemModelNG listItemModel;
            listItemModel.Create();
            SetWidth(Dimension(itemWidth));
            ViewStackProcessor::GetInstance()->Pop();
        }
    });

    for (int32_t index = 0; index < TOTAL_NUMBER; index++) {
        EXPECT_EQ(GetChildRect(frameNode_, index).GetX(), 0);
    }
}

/**
 * @tc.name: AttrAlignListItem002
 * @tc.desc: Test LayoutProperty about alignListItem,
 * when ListItem width less than List, align by set value ListItemAlign::CENTER
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrAlignListItem002, TestSize.Level1)
{
    constexpr float itemWidth = 400.f;
    CreateList([itemWidth](ListModelNG listModelNG) {
        listModelNG.SetListItemAlign(V2::ListItemAlign::CENTER);
        for (int32_t index = 0; index < TOTAL_NUMBER; index++) {
            ListItemModelNG listItemModel;
            listItemModel.Create();
            SetWidth(Dimension(itemWidth));
            ViewStackProcessor::GetInstance()->Pop();
        }
    });

    for (int32_t index = 0; index < TOTAL_NUMBER; index++) {
        EXPECT_EQ(GetChildRect(frameNode_, index).GetX(), (DEVICE_WIDTH - itemWidth) / 2);
    }
}

/**
 * @tc.name: AttrAlignListItem003
 * @tc.desc: Test LayoutProperty about alignListItem,
 * when ListItem width less than List, align by set value ListItemAlign::END
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrAlignListItem003, TestSize.Level1)
{
    constexpr float itemWidth = 400.f;
    CreateList([itemWidth](ListModelNG listModelNG) {
        listModelNG.SetListItemAlign(V2::ListItemAlign::END);
        for (int32_t index = 0; index < TOTAL_NUMBER; index++) {
            ListItemModelNG listItemModel;
            listItemModel.Create();
            SetWidth(Dimension(itemWidth));
            ViewStackProcessor::GetInstance()->Pop();
        }
    });

    for (int32_t index = 0; index < TOTAL_NUMBER; index++) {
        EXPECT_EQ(GetChildRect(frameNode_, index).GetX(), DEVICE_WIDTH - itemWidth);
    }
}

/**
 * @tc.name: AttrScrollSnapAlign001
 * @tc.desc: Test LayoutProperty about ScrollSnapAlign,
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrScrollSnapAlign001, TestSize.Level1)
{
    const float halfItemHeight = ITEM_HEIGHT / 2;
    const float velocity = 1200.f;
    CreateListWithItem([](ListModelNG listModelNG) { listModelNG.SetScrollSnapAlign(V2::ScrollSnapAlign::START); });
    pattern_->OnScrollSnapCallback(-halfItemHeight, velocity);
    ScrollDown(0.5);
    RunMeasureAndLayout(frameNode_);
    EXPECT_TRUE(IsEqualTotalOffset(halfItemHeight));

    CreateListWithItem([](ListModelNG listModelNG) { listModelNG.SetScrollSnapAlign(V2::ScrollSnapAlign::END); });
    pattern_->OnScrollSnapCallback(-halfItemHeight, velocity);
    ScrollDown(0.5);
    RunMeasureAndLayout(frameNode_);
    EXPECT_TRUE(IsEqualTotalOffset(halfItemHeight));

    CreateListWithItem([](ListModelNG listModelNG) { listModelNG.SetScrollSnapAlign(V2::ScrollSnapAlign::CENTER); });
    EXPECT_TRUE(IsEqualTotalOffset(-ITEM_HEIGHT * 3.5));
    pattern_->OnScrollSnapCallback(-halfItemHeight, velocity);
    ScrollDown(0.5);
    RunMeasureAndLayout(frameNode_);
    EXPECT_TRUE(IsEqualTotalOffset(-ITEM_HEIGHT * 3));
}

/**
 * @tc.name: AttrSLECM001
 * @tc.desc: Test property about scroller/listDirection/edgeEffect/chainAnimation/multiSelectable
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrSLECM001, TestSize.Level1)
{
    CreateListWithItem([](ListModelNG listModelNG) {
        listModelNG.SetListDirection(Axis::HORIZONTAL);
        listModelNG.SetEdgeEffect(EdgeEffect::SPRING);
        listModelNG.SetChainAnimation(true);
        listModelNG.SetMultiSelectable(true);
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
    CreateListWithItem([](ListModelNG listModelNG) { listModelNG.SetScrollEnabled(true); });
    EXPECT_TRUE(layoutProperty_->GetScrollEnabledValue());
    CreateListWithItem([](ListModelNG listModelNG) { listModelNG.SetScrollEnabled(false); });
    EXPECT_FALSE(layoutProperty_->GetScrollEnabledValue());
}

/**
 * @tc.name: SwiperItem001
 * @tc.desc: Set startNode, List can swipe start but cannot swipe end.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SwiperItem001, TestSize.Level1)
{
    CreateSwipeList(true, V2::SwipeEdgeEffect::None);
    const int32_t listItemIndex = 0;
    const RefPtr<FrameNode> listItem = GetChildFrameNode(frameNode_, listItemIndex);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
    const int32_t startNodeIndex = 0;
    const int32_t itemNodeIndex = 1;
    const RectF itemNodeInitialRect = RectF(0, 0, DEVICE_WIDTH, ITEM_HEIGHT);
    const RectF itemNodeSwipeStartRect = RectF(START_NODE_SIZE, 0, DEVICE_WIDTH, ITEM_HEIGHT);
    const float slightSwipeDelta = START_NODE_SIZE * SWIPER_TH;
    const float obviousSwipeDelta = START_NODE_SIZE * SWIPER_TH + 1;
    const float exceedSwipeDelta = START_NODE_SIZE + 1;

    /**
     * @tc.steps: step1. do nothing, verify initial rect.
     * @tc.expected: StartNode not layout
     */
    RectF startNodeRect = GetChildRect(listItem, startNodeIndex);
    RectF itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    RectF expectStartNodeRect = RectF();
    RectF expectItemNodeRect = itemNodeInitialRect;
    EXPECT_TRUE(IsEqualRect(startNodeRect, expectStartNodeRect));
    EXPECT_TRUE(IsEqualRect(itemNodeRect, expectItemNodeRect));
    ListItemSwipeIndex swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step2. Swipe end
     * @tc.expected: Can not move, StartNode not layout
     */
    DragSwiperItem(listItemIndex, -START_NODE_SIZE);
    startNodeRect = GetChildRect(listItem, startNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectStartNodeRect = RectF();
    expectItemNodeRect = itemNodeInitialRect;
    EXPECT_TRUE(IsEqualRect(startNodeRect, expectStartNodeRect));
    EXPECT_TRUE(IsEqualRect(itemNodeRect, expectItemNodeRect));
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
    expectStartNodeRect = RectF(slightSwipeDelta - START_NODE_SIZE, 0, START_NODE_SIZE, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeInitialRect;
    EXPECT_TRUE(IsEqualRect(startNodeRect, expectStartNodeRect));
    EXPECT_TRUE(IsEqualRect(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step4. Swipe start obviously
     * @tc.expected: swiperIndex_ change to SWIPER_START
     */
    DragSwiperItem(listItemIndex, obviousSwipeDelta);
    startNodeRect = GetChildRect(listItem, startNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectStartNodeRect = RectF(0, 0, START_NODE_SIZE, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeSwipeStartRect;
    EXPECT_TRUE(IsEqualRect(startNodeRect, expectStartNodeRect));
    EXPECT_TRUE(IsEqualRect(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::SWIPER_START);

    /**
     * @tc.steps: step5. Swipe item slightly
     * @tc.expected: swiperIndex_ unchanged
     */
    DragSwiperItem(listItemIndex, -slightSwipeDelta);
    startNodeRect = GetChildRect(listItem, startNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectStartNodeRect = RectF(0, 0, START_NODE_SIZE, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeSwipeStartRect;
    EXPECT_TRUE(IsEqualRect(startNodeRect, expectStartNodeRect));
    EXPECT_TRUE(IsEqualRect(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::SWIPER_START);

    /**
     * @tc.steps: step6. Swipe item obviously
     * @tc.expected: swiperIndex_ change to ITEM_CHILD
     */
    DragSwiperItem(listItemIndex, -obviousSwipeDelta);
    startNodeRect = GetChildRect(listItem, startNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectStartNodeRect = RectF(-obviousSwipeDelta, 0, START_NODE_SIZE, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeInitialRect;
    EXPECT_TRUE(IsEqualRect(startNodeRect, expectStartNodeRect));
    EXPECT_TRUE(IsEqualRect(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step7. Swipe item exceed
     * @tc.expected: swiperIndex_ change to SWIPER_START, curOffset_ would be START_NODE_SIZE
     */
    DragSwiperItem(listItemIndex, exceedSwipeDelta);
    startNodeRect = GetChildRect(listItem, startNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectStartNodeRect = RectF(0, 0, START_NODE_SIZE, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeSwipeStartRect;
    EXPECT_TRUE(IsEqualRect(startNodeRect, expectStartNodeRect));
    EXPECT_TRUE(IsEqualRect(itemNodeRect, expectItemNodeRect));
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
    CreateSwipeList(false, V2::SwipeEdgeEffect::None);
    const int32_t listItemIndex = 0;
    const RefPtr<FrameNode> listItem = GetChildFrameNode(frameNode_, listItemIndex);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
    const int32_t endNodeIndex = 0;
    const int32_t itemNodeIndex = 1;
    const RectF itemNodeInitialRect = RectF(0, 0, DEVICE_WIDTH, ITEM_HEIGHT);
    const RectF itemNodeSwipeEndRect = RectF(-END_NODE_SIZE, 0, DEVICE_WIDTH, ITEM_HEIGHT);
    const float slightSwipeDelta = END_NODE_SIZE * SWIPER_TH;
    const float obviousSwipeDelta = END_NODE_SIZE * SWIPER_TH + 1;
    const float exceedSwipeDelta = END_NODE_SIZE + 1;

    /**
     * @tc.steps: step1. do nothing, verify initial rect.
     * @tc.expected: EndNode not layout
     */
    RectF endNodeRect = GetChildRect(listItem, endNodeIndex);
    RectF itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    RectF expectEndNodeRect = RectF();
    RectF expectItemNodeRect = itemNodeInitialRect;
    EXPECT_TRUE(IsEqualRect(endNodeRect, expectEndNodeRect));
    EXPECT_TRUE(IsEqualRect(itemNodeRect, expectItemNodeRect));
    ListItemSwipeIndex swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step2. Swipe start
     * @tc.expected: Can not move, EndNode not layout
     */
    DragSwiperItem(listItemIndex, END_NODE_SIZE);
    endNodeRect = GetChildRect(listItem, endNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectEndNodeRect = RectF();
    expectItemNodeRect = itemNodeInitialRect;
    EXPECT_TRUE(IsEqualRect(endNodeRect, expectEndNodeRect));
    EXPECT_TRUE(IsEqualRect(itemNodeRect, expectItemNodeRect));
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
    expectEndNodeRect = RectF(DEVICE_WIDTH - slightSwipeDelta, 0, END_NODE_SIZE, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeInitialRect;
    EXPECT_TRUE(IsEqualRect(endNodeRect, expectEndNodeRect));
    EXPECT_TRUE(IsEqualRect(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step4. Swipe end obviously
     * @tc.expected: swiperIndex_ change to SWIPER_END
     */
    DragSwiperItem(listItemIndex, -obviousSwipeDelta);
    endNodeRect = GetChildRect(listItem, endNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectEndNodeRect = RectF(DEVICE_WIDTH - END_NODE_SIZE, 0, END_NODE_SIZE, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeSwipeEndRect;
    EXPECT_TRUE(IsEqualRect(endNodeRect, expectEndNodeRect));
    EXPECT_TRUE(IsEqualRect(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::SWIPER_END);

    /**
     * @tc.steps: step5. Swipe item slightSwipeDelta
     * @tc.expected: swiperIndex_ unchanged
     */
    DragSwiperItem(listItemIndex, slightSwipeDelta);
    endNodeRect = GetChildRect(listItem, endNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectEndNodeRect = RectF(DEVICE_WIDTH - END_NODE_SIZE, 0, END_NODE_SIZE, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeSwipeEndRect;
    EXPECT_TRUE(IsEqualRect(endNodeRect, expectEndNodeRect));
    EXPECT_TRUE(IsEqualRect(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::SWIPER_END);

    /**
     * @tc.steps: step6. Swipe item obviously
     * @tc.expected: swiperIndex_ change to ITEM_CHILD
     */
    DragSwiperItem(listItemIndex, obviousSwipeDelta);
    endNodeRect = GetChildRect(listItem, endNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectEndNodeRect = RectF(DEVICE_WIDTH - END_NODE_SIZE + obviousSwipeDelta, 0, END_NODE_SIZE, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeInitialRect;
    EXPECT_TRUE(IsEqualRect(endNodeRect, expectEndNodeRect));
    EXPECT_TRUE(IsEqualRect(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step7. Swipe end exceed
     * @tc.expected: swiperIndex_ change to SWIPER_END, curOffset_ would be -END_NODE_SIZE
     */
    DragSwiperItem(listItemIndex, -exceedSwipeDelta);
    endNodeRect = GetChildRect(listItem, endNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectEndNodeRect = RectF(DEVICE_WIDTH - END_NODE_SIZE, 0, END_NODE_SIZE, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeSwipeEndRect;
    EXPECT_TRUE(IsEqualRect(endNodeRect, expectEndNodeRect));
    EXPECT_TRUE(IsEqualRect(itemNodeRect, expectItemNodeRect));
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
    CreateSwipeList(true, V2::SwipeEdgeEffect::None);
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
    CreateSwipeList(false, V2::SwipeEdgeEffect::None);
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
    CreateSwipeList(true, V2::SwipeEdgeEffect::None);
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
    CreateSwipeList(true, V2::SwipeEdgeEffect::Spring);
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
    HandleDragUpdate(listItemIndex, START_NODE_SIZE);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_EQ(listItemPattern->curOffset_, START_NODE_SIZE + moveDelta);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_LT(listItemPattern->curOffset_, START_NODE_SIZE + moveDelta * 2);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(listItemPattern->curOffset_, START_NODE_SIZE);
}

/**
 * @tc.name: SwiperItem006
 * @tc.desc: Set endNode and SwipeEdgeEffect::Spring, can continue to move when swipe exceed listItem size
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SwiperItem006, TestSize.Level1)
{
    CreateSwipeList(false, V2::SwipeEdgeEffect::Spring);
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
    HandleDragUpdate(listItemIndex, -END_NODE_SIZE);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_EQ(listItemPattern->curOffset_, -END_NODE_SIZE + moveDelta);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_GT(listItemPattern->curOffset_, -END_NODE_SIZE + moveDelta * 2);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(listItemPattern->curOffset_, -END_NODE_SIZE);
}

/**
 * @tc.name: SwiperItem007
 * @tc.desc: Set startNode, startDeleteArea, deleteAreaDistance SwipeEdgeEffect::None
 * List can swiper right great than START_NODE_SIZE
 * if great than START_NODE_SIZE + deleteAreaDistance,
 * it will adjust to START_NODE_SIZE + deleteAreaDistance
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SwiperItem007, TestSize.Level1)
{
    auto startFunc = GetDefaultSwiperBuilder(START_NODE_SIZE);
    CreateListItemWithSwipeActionItem(
        startFunc, true, nullptr, nullptr, nullptr, Dimension(DELETE_AREA_DISTANCE), true, V2::SwipeEdgeEffect::None);
    const int32_t listItemIndex = 0;
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
    const float maxDistance = START_NODE_SIZE + DELETE_AREA_DISTANCE;

    /**
     * @tc.steps: step1. Swipe start greater than maxDistance
     * @tc.expected: cannot exceed maxDistance
     */
    float moveDelta = 1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, maxDistance);
    EXPECT_EQ(listItemPattern->curOffset_, maxDistance);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_EQ(listItemPattern->curOffset_, maxDistance);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(listItemPattern->curOffset_, START_NODE_SIZE);

    /**
     * @tc.steps: step2. Swipe end
     * @tc.expected: cannot move
     */
    moveDelta = -1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -START_NODE_SIZE);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_EQ(listItemPattern->curOffset_, 0);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(listItemPattern->curOffset_, 0);
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
    auto endFunc = GetDefaultSwiperBuilder(END_NODE_SIZE);
    CreateListItemWithSwipeActionItem(
        endFunc, true, nullptr, nullptr, nullptr, Dimension(DELETE_AREA_DISTANCE), false, V2::SwipeEdgeEffect::None);
    const int32_t listItemIndex = 0;
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
    const float maxDistance = END_NODE_SIZE + DELETE_AREA_DISTANCE;

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
    EXPECT_EQ(listItemPattern->curOffset_, -END_NODE_SIZE);

    /**
     * @tc.steps: step1. Swipe start
     * @tc.expected: cannot move
     */
    moveDelta = 1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, END_NODE_SIZE);
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
    auto startFunc = GetDefaultSwiperBuilder(START_NODE_SIZE);
    CreateListItemWithSwipeActionItem(
        startFunc, true, nullptr, nullptr, nullptr, Dimension(DELETE_AREA_DISTANCE), true, V2::SwipeEdgeEffect::Spring);
    const int32_t listItemIndex = 0;
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
    const float maxDistance = START_NODE_SIZE + DELETE_AREA_DISTANCE;

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
    EXPECT_EQ(listItemPattern->curOffset_, START_NODE_SIZE);

    /**
     * @tc.steps: step2. Swipe end
     * @tc.expected: Can continue to move
     */
    moveDelta = -1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -START_NODE_SIZE);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_LT(listItemPattern->curOffset_, 0);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(listItemPattern->curOffset_, 0);
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
    auto endFunc = GetDefaultSwiperBuilder(END_NODE_SIZE);
    CreateListItemWithSwipeActionItem(
        endFunc, true, nullptr, nullptr, nullptr, Dimension(DELETE_AREA_DISTANCE), false, V2::SwipeEdgeEffect::Spring);
    const int32_t listItemIndex = 0;
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
    const float maxDistance = END_NODE_SIZE + DELETE_AREA_DISTANCE;
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
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(listItemPattern->curOffset_, -END_NODE_SIZE);

    /**
     * @tc.steps: step1. Swipe start
     * @tc.expected: Can continue to move
     */
    moveDelta = 1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, END_NODE_SIZE);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_GT(listItemPattern->curOffset_, 0);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(listItemPattern->curOffset_, 0);
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
    auto builder = GetDefaultSwiperBuilder(START_NODE_SIZE);
    CreateListItemWithSwipeActionItem(builder, true, deleteEvent, enterEvent, exitEvent,
        Dimension(DELETE_AREA_DISTANCE), true, V2::SwipeEdgeEffect::Spring);
    const int32_t listItemIndex = 0;

    /**
     * @tc.steps: step1. Repeat entry and exit
     */
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, START_NODE_SIZE);
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
    auto builder = GetDefaultSwiperBuilder(END_NODE_SIZE);
    CreateListItemWithSwipeActionItem(builder, true, deleteEvent, enterEvent, exitEvent,
        Dimension(DELETE_AREA_DISTANCE), false, V2::SwipeEdgeEffect::Spring);
    const int32_t listItemIndex = 0;
    const float exceedArea = DELETE_AREA_DISTANCE + 1;

    /**
     * @tc.steps: step1. Repeat entry and exit
     */
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -END_NODE_SIZE);
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
    CreateListItemWithSwipeActionItem(nullptr, true, deleteEvent, enterEvent, exitEvent,
        Dimension(DELETE_AREA_DISTANCE), true, V2::SwipeEdgeEffect::None);
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
    CreateListItemWithSwipeActionItem(nullptr, true, deleteEvent, enterEvent, exitEvent,
        Dimension(DELETE_AREA_DISTANCE), false, V2::SwipeEdgeEffect::None);
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
    CreateSwipeList(true, V2::SwipeEdgeEffect::None);
    const int32_t listItemIndex = 0;
    const RefPtr<FrameNode> listItem = GetChildFrameNode(frameNode_, listItemIndex);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
    const int32_t startNodeIndex = 0;
    auto startFunc = GetDefaultSwiperBuilder(START_NODE_SIZE);
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
    CreateSwipeList(false, V2::SwipeEdgeEffect::None);
    const int32_t listItemIndex = 0;
    const RefPtr<FrameNode> listItem = GetChildFrameNode(frameNode_, listItemIndex);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
    const int32_t endNodeIndex = 0;
    auto endFunc = GetDefaultSwiperBuilder(END_NODE_SIZE);
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
    CreateSwipeList(true, V2::SwipeEdgeEffect::None);
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
 * @tc.name: ListItemGroup001
 * @tc.desc: check ListItem position
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemGroup001, TestSize.Level1)
{
    CreateList([](ListModelNG listModelNG) {
        listModelNG.SetInitialIndex(1);
        CreateListItemGroup();
    });

    /**
     * @tc.steps: step1. Verify second ListItemGroup itemPosition_/rect.
     */
    int32_t groupIndex = 1;
    auto groupNode = GetChildFrameNode(frameNode_, groupIndex);
    auto groupItemPosition = GetChildPattern<ListItemGroupPattern>(frameNode_, groupIndex)->GetItemPosition();
    EXPECT_EQ(groupItemPosition.size(), static_cast<size_t>(GROUP_ITEM_NUMBER));
    auto groupRect = GetChildRect(frameNode_, groupIndex);
    EXPECT_TRUE(IsEqualRect(groupRect, RectF(0, 0, GROUP_WIDTH,
        HEADER_MAIN_LENGTH * 2 + GROUP_ITEM_NUMBER * ITEM_HEIGHT + (GROUP_ITEM_NUMBER - 1) * SPACE)));
    auto headRect = GetChildRect(groupNode, 0);
    auto footRect = GetChildRect(groupNode, 1);
    EXPECT_TRUE(IsEqualRect(headRect, RectF(0, 0, GROUP_WIDTH, HEADER_MAIN_LENGTH)));
    float footOffsetY = GROUP_ITEM_NUMBER * ITEM_HEIGHT + (GROUP_ITEM_NUMBER - 1) * SPACE + HEADER_MAIN_LENGTH;
    EXPECT_TRUE(IsEqualRect(footRect, RectF(0, footOffsetY, GROUP_WIDTH, HEADER_MAIN_LENGTH)));
    VerifyGroupItemPosition(groupNode, GROUP_ITEM_NUMBER, DEFAULT_LANES, SPACE, HEADER_MAIN_LENGTH);

    /**
     * @tc.steps: step2. Verify third ListItemGroup itemPosition_/rect.
     */
    UpdateCurrentOffset(-GetChildRect(frameNode_, groupIndex).Height());
    groupIndex = 2;
    groupNode = GetChildFrameNode(frameNode_, groupIndex);
    groupItemPosition = GetChildPattern<ListItemGroupPattern>(frameNode_, groupIndex)->GetItemPosition();
    EXPECT_EQ(groupItemPosition.size(), static_cast<size_t>(GROUP_ITEM_NUMBER));
    VerifyGroupItemPosition(groupNode, GROUP_ITEM_NUMBER, DEFAULT_LANES, SPACE, 0);

    /**
     * @tc.steps: step3. Verify fourth ListItemGroup itemPosition_/rect.
     */
    UpdateCurrentOffset(-GetChildRect(frameNode_, groupIndex).Height());
    groupIndex = 3;
    groupNode = GetChildFrameNode(frameNode_, groupIndex);
    groupItemPosition = GetChildPattern<ListItemGroupPattern>(frameNode_, groupIndex)->GetItemPosition();
    EXPECT_EQ(groupItemPosition.size(), static_cast<size_t>(GROUP_ITEM_NUMBER));
    VerifyGroupItemPosition(groupNode, GROUP_ITEM_NUMBER, DEFAULT_LANES, SPACE, 0);

    /**
     * @tc.steps: step4. Verify fifth ListItemGroup itemPosition_/rect.
     */
    groupIndex = 4;
    groupNode = GetChildFrameNode(frameNode_, groupIndex);
    groupItemPosition = GetChildPattern<ListItemGroupPattern>(frameNode_, groupIndex)->GetItemPosition();
    EXPECT_EQ(groupItemPosition.size(), 0);
    EXPECT_EQ(GetChildRect(frameNode_, groupIndex).Height(), 0);
}

/**
 * @tc.name: ListItemGroup002
 * @tc.desc: List set sticky header and footer
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemGroup002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. V2::StickyStyle::HEADER
     * @tc.expected: head is Sticky
     */
    CreateList([](ListModelNG listModelNG) {
        listModelNG.SetSticky(V2::StickyStyle::HEADER);
        CreateListItemGroup();
    });
    int32_t groupIndex = 0;
    auto groupNode = GetChildFrameNode(frameNode_, groupIndex);
    auto headRect = GetChildRect(groupNode, 0);
    EXPECT_TRUE(IsEqualRect(headRect, RectF(0, 0, GROUP_WIDTH, HEADER_MAIN_LENGTH)));
    ScrollDown();
    headRect = GetChildRect(groupNode, 0);
    EXPECT_TRUE(IsEqualRect(headRect, RectF(0, ITEM_HEIGHT, GROUP_WIDTH, HEADER_MAIN_LENGTH)));

    /**
     * @tc.steps: step2. V2::StickyStyle::FOOTER
     * @tc.expected: foot is Sticky
     */
    CreateList([](ListModelNG listModelNG) {
        listModelNG.SetSticky(V2::StickyStyle::FOOTER);
        CreateListItemGroup();
    });
    groupIndex = 1;
    groupNode = GetChildFrameNode(frameNode_, groupIndex);
    auto footRect = GetChildRect(groupNode, 1);
    float footOffsetY = DEVICE_HEIGHT - GetChildRect(frameNode_, 0).Height() - HEADER_MAIN_LENGTH;
    EXPECT_TRUE(IsEqualRect(footRect, RectF(0, footOffsetY, GROUP_WIDTH, HEADER_MAIN_LENGTH)));
    ScrollDown();
    footRect = GetChildRect(groupNode, 1);
    EXPECT_TRUE(IsEqualRect(footRect, RectF(0, footOffsetY + ITEM_HEIGHT, GROUP_WIDTH, HEADER_MAIN_LENGTH)));

    /**
     * @tc.steps: step3. V2::StickyStyle::FOOTER
     * @tc.expected: head/foot is Sticky
     */
    CreateList([](ListModelNG listModelNG) {
        listModelNG.SetSticky(V2::StickyStyle::BOTH);
        CreateListItemGroup();
    });
    groupIndex = 0;
    groupNode = GetChildFrameNode(frameNode_, groupIndex);
    headRect = GetChildRect(groupNode, 0);
    EXPECT_TRUE(IsEqualRect(headRect, RectF(0, 0, GROUP_WIDTH, HEADER_MAIN_LENGTH)));
    ScrollDown();
    headRect = GetChildRect(groupNode, 0);
    EXPECT_TRUE(IsEqualRect(headRect, RectF(0, ITEM_HEIGHT, GROUP_WIDTH, HEADER_MAIN_LENGTH)));

    groupIndex = 1;
    groupNode = GetChildFrameNode(frameNode_, groupIndex);
    footRect = GetChildRect(groupNode, 1);
    footOffsetY = DEVICE_HEIGHT - GetChildRect(frameNode_, 0).Height() - HEADER_MAIN_LENGTH + ITEM_HEIGHT;
    EXPECT_TRUE(IsEqualRect(footRect, RectF(0, footOffsetY, GROUP_WIDTH, HEADER_MAIN_LENGTH)));
    ScrollUp();
    footRect = GetChildRect(groupNode, 1);
    EXPECT_TRUE(IsEqualRect(footRect, RectF(0, footOffsetY - ITEM_HEIGHT, GROUP_WIDTH, HEADER_MAIN_LENGTH)));
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
    constexpr int32_t lanes = 2;
    CreateList([lanes](ListModelNG listModelNG) {
        listModelNG.SetLanes(lanes);
        CreateListItemGroup();
    });
    int32_t groupIndex = 0;
    auto groupNode = GetChildFrameNode(frameNode_, groupIndex);
    auto groupRect = GetChildRect(frameNode_, groupIndex);
    EXPECT_TRUE(VerifyGroupItemPosition(groupNode, GROUP_ITEM_NUMBER, lanes, SPACE, HEADER_MAIN_LENGTH));
    int32_t rows = std::floor(GROUP_ITEM_NUMBER / lanes);
    float groupHeight = HEADER_MAIN_LENGTH * 2 + rows * ITEM_HEIGHT + (rows - 1) * SPACE;
    EXPECT_TRUE(IsEqualRect(groupRect, RectF(0, 0, GROUP_WIDTH, groupHeight)));

    /**
     * @tc.steps: step2. maxLaneLength > GROUP_WIDTH
     */
    float minLaneLength = 220.f;
    float maxLaneLength = 480.f;
    CreateList([minLaneLength, maxLaneLength](ListModelNG listModelNG) {
        listModelNG.SetLaneMinLength(Dimension(minLaneLength));
        listModelNG.SetLaneMaxLength(Dimension(maxLaneLength));
        CreateListItemGroup();
    });
    groupIndex = 0;
    groupNode = GetChildFrameNode(frameNode_, groupIndex);
    EXPECT_TRUE(VerifyGroupItemPosition(groupNode, GROUP_ITEM_NUMBER, DEFAULT_LANES, SPACE, HEADER_MAIN_LENGTH));
    EXPECT_EQ(GetChildRect(groupNode, 2).Width(), GROUP_WIDTH);

    /**
     * @tc.steps: step3. maxLaneLength < GROUP_WIDTH
     */
    minLaneLength = 220.f;
    maxLaneLength = 300.f;
    CreateList([minLaneLength, maxLaneLength](ListModelNG listModelNG) {
        listModelNG.SetLaneMinLength(Dimension(minLaneLength));
        listModelNG.SetLaneMaxLength(Dimension(maxLaneLength));
        CreateListItemGroup();
    });
    groupIndex = 0;
    groupNode = GetChildFrameNode(frameNode_, groupIndex);
    EXPECT_TRUE(VerifyGroupItemPosition(groupNode, GROUP_ITEM_NUMBER, DEFAULT_LANES, SPACE, HEADER_MAIN_LENGTH));
    EXPECT_EQ(GetChildRect(groupNode, 2).Width(), maxLaneLength);
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
    CreateList([](ListModelNG listModelNG) {
        listModelNG.SetListItemAlign(V2::ListItemAlign::START);
        CreateListItemGroup();
    });
    // scroll to second group
    UpdateCurrentOffset(-GetChildRect(frameNode_, 0).Height());
    int32_t groupIndex = 1;
    auto groupNode = GetChildFrameNode(frameNode_, groupIndex);
    auto listItemRect = GetChildRect(groupNode, 2);
    EXPECT_TRUE(IsEqualRect(listItemRect, RectF(0, HEADER_MAIN_LENGTH, GROUP_ITEM_WIDTH, ITEM_HEIGHT)));

    /**
     * @tc.steps: step2. V2::ListItemAlign::CENTER
     */
    CreateList([](ListModelNG listModelNG) {
        listModelNG.SetListItemAlign(V2::ListItemAlign::CENTER);
        CreateListItemGroup();
    });
    UpdateCurrentOffset(-GetChildRect(frameNode_, 0).Height());
    groupIndex = 1;
    groupNode = GetChildFrameNode(frameNode_, groupIndex);
    listItemRect = GetChildRect(groupNode, 2);
    EXPECT_TRUE(IsEqualRect(listItemRect, RectF((GROUP_WIDTH - GROUP_ITEM_WIDTH) / 2, HEADER_MAIN_LENGTH,
        GROUP_ITEM_WIDTH, ITEM_HEIGHT)));

    /**
     * @tc.steps: step3. V2::ListItemAlign::END
     */
    CreateList([](ListModelNG listModelNG) {
        listModelNG.SetListItemAlign(V2::ListItemAlign::END);
        CreateListItemGroup();
    });
    UpdateCurrentOffset(-GetChildRect(frameNode_, 0).Height());
    groupIndex = 1;
    groupNode = GetChildFrameNode(frameNode_, groupIndex);
    listItemRect = GetChildRect(groupNode, 2);
    EXPECT_TRUE(IsEqualRect(listItemRect,
        RectF(GROUP_WIDTH - GROUP_ITEM_WIDTH, HEADER_MAIN_LENGTH, GROUP_ITEM_WIDTH, ITEM_HEIGHT)));
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
    CreateList([](ListModelNG listModelNG) { CreateListItemGroup(2); });

    OverScrollOffset offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    OverScrollOffset expectOffset = { ITEM_HEIGHT, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, -ITEM_HEIGHT };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));

    ScrollDown();
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    expectOffset = { ITEM_HEIGHT, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, -ITEM_HEIGHT };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));

    /**
     * @tc.steps: step2. !IsScrollSnapAlignCenter
     */
    CreateList([](ListModelNG listModelNG) { CreateListItemGroup(1); });

    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT * 5);
    expectOffset = { 500, 400 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, -ITEM_HEIGHT };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));

    ScrollDown();
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    expectOffset = { ITEM_HEIGHT, ITEM_HEIGHT };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, -ITEM_HEIGHT };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));

    /**
     * @tc.steps: step3. IsScrollSnapAlignCenter
     */
    CreateList([](ListModelNG listModelNG) {
        listModelNG.SetScrollSnapAlign(V2::ScrollSnapAlign::CENTER);
        CreateListItemGroup(2);
    });

    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    expectOffset = { ITEM_HEIGHT, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));

    ScrollDown();
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT * 4);
    expectOffset = { 0, -ITEM_HEIGHT };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));

    /**
     * @tc.steps: step4. has no group, groupAtStart and groupAtEnd are false
     */
    CreateListWithItem();
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    expectOffset = { ITEM_HEIGHT, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
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
    CreateListWithItem([event](ListModelNG listModelNG) { listModelNG.SetOnScroll(event); });

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
    RunMeasureAndLayout(frameNode_);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_ANIMATION);
    pattern_->OnScrollEndCallback();
    RunMeasureAndLayout(frameNode_);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION_SPRING);
    pattern_->OnScrollEndCallback();
    RunMeasureAndLayout(frameNode_);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_NONE);
    pattern_->OnScrollEndCallback();
    RunMeasureAndLayout(frameNode_);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_AXIS);
    pattern_->OnScrollEndCallback();
    RunMeasureAndLayout(frameNode_);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_BAR);
    pattern_->OnScrollEndCallback();
    RunMeasureAndLayout(frameNode_);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION_CONTROLLER);
    pattern_->OnScrollEndCallback();
    RunMeasureAndLayout(frameNode_);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_BAR_FLING);
    pattern_->OnScrollEndCallback();
    RunMeasureAndLayout(frameNode_);
    EXPECT_TRUE(isTrigger);

    // SetMinPlatformVersion
    MockPipelineBase::pipeline_->SetMinPlatformVersion(PLATFORM_VERSION_TEN - 1);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_AXIS);
    pattern_->OnScrollEndCallback(); // set scrollStop_ to true
    RunMeasureAndLayout(frameNode_);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_BAR);
    pattern_->OnScrollEndCallback();
    RunMeasureAndLayout(frameNode_);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION_CONTROLLER);
    pattern_->OnScrollEndCallback();
    RunMeasureAndLayout(frameNode_);
    EXPECT_TRUE(isTrigger);

    // set back
    MockPipelineBase::pipeline_->SetMinPlatformVersion(PLATFORM_VERSION_TEN);
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
    CreateListWithItem([event](ListModelNG listModelNG) { listModelNG.SetOnScrollIndex(event); });

    ScrollDown();
    EXPECT_EQ(startIndex, 0);
    EXPECT_EQ(endIndex, 8);
    EXPECT_EQ(centerIndex, 4);

    ScrollDown();
    EXPECT_EQ(startIndex, 1);
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
    CreateListWithItem([event](ListModelNG listModelNG) { listModelNG.SetOnReachStart(event); });

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
     * @tc.steps: step3. Scroll up to start
     */
    isTrigger = false;
    ScrollUp(2);
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step4. Scroll down to start
     */
    isTrigger = false;
    ScrollDown();
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
    CreateListWithItem([event](ListModelNG listModelNG) { listModelNG.SetOnReachEnd(event); });

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
    CreateListWithItem([scrollStart, scrollStop](ListModelNG listModelNG) {
        listModelNG.SetChainAnimation(true);
        listModelNG.SetChainAnimationOptions(
            { Dimension(0), Dimension(10), 0, 0, 0, DEFAULT_STIFFNESS, DEFAULT_DAMPING });
        listModelNG.SetOnScrollStart(scrollStart);
        listModelNG.SetOnScrollStop(scrollStop);
    });

    pattern_->OnScrollCallback(100.f, SCROLL_FROM_START);
    EXPECT_TRUE(isScrollStartCalled);

    pattern_->OnScrollEndCallback();
    RunMeasureAndLayout(frameNode_);
    EXPECT_TRUE(isScrollStopCalled);

    isScrollStopCalled = false;
    pattern_->OnScrollEndCallback();
    pattern_->SetScrollAbort(true);
    RunMeasureAndLayout(frameNode_);
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
    CreateListWithItem([event](ListModelNG listModelNG) { listModelNG.SetOnScrollFrameBegin(event); });

    auto scrollableEvent = pattern_->GetScrollableEvent();
    ASSERT_NE(scrollableEvent, nullptr);
    auto scrollable = scrollableEvent->GetScrollable();
    EXPECT_NE(scrollable->scrollFrameBeginCallback_, nullptr);
    RunMeasureAndLayout(frameNode_);
}

/**
 * @tc.name: EventHub001
 * @tc.desc: Test Event hub
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, EventHub001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Run List GetDragExtraParams func.
     * @tc.expected: Would call pattern->GetItemIndexByPosition
     */
    auto onItemDragStart = [](const ItemDragInfo&, int32_t) {
        auto dragItem = AceType::MakeRefPtr<FrameNode>("test", 0, AceType::MakeRefPtr<Pattern>());
        return AceType::DynamicCast<UINode>(dragItem);
    };
    CreateListWithItem([onItemDragStart](ListModelNG listModelNG) {
        listModelNG.SetOnItemDragStart(onItemDragStart);
    });
    auto jsonStr = eventHub_->GetDragExtraParams("", Point(0, 250), DragEventType::MOVE);
    EXPECT_EQ(jsonStr, "{\"insertIndex\":2}");

    /**
     * @tc.steps: step2. HandleOnItemDrag to end
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
    CreateListWithItem();
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
    CreateListWithItem([](ListModelNG listModelNG) { listModelNG.SetMultiSelectable(true); });

    /**
     * @tc.steps: step1. Select zone.
     * @tc.expected: The 1st and 2nd items are selected.
     */
    MouseSelect(Offset(0.f, 0.f), Offset(200.f, 100.f));
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 0)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 1)->IsSelected());

    /**
     * @tc.steps: step2. Change select zone.
     * @tc.expected: Selected items changed.
     */
    MouseSelect(Offset(200.f, 200.f), Offset(200.f, 300.f));
    EXPECT_FALSE(GetChildPattern<ListItemPattern>(frameNode_, 0)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 1)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 2)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 3)->IsSelected());

    /**
     * @tc.steps: step3. Click first item.
     * @tc.expected: Each item not selected.
     */
    MouseSelect(Offset(10.f, 10.f), Offset(10.f, 10.f));
    for (int32_t index = 0; index < VIEWPORT_NUMBER; index++) {
        EXPECT_FALSE(GetChildPattern<ListItemPattern>(frameNode_, index)->IsSelected()) << "Index: " << index;
    }
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
    CreateListWithItem([](ListModelNG listModelNG) { listModelNG.SetMultiSelectable(true); });

    /**
     * @tc.steps: step1. Select from LEFT_TOP to RIGHT_BOTTOM
     */
    MouseSelect(LEFT_TOP, RIGHT_BOTTOM);
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 2)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 3)->IsSelected());

    /**
     * @tc.steps: step2. Select from RIGHT_TOP to LEFT_BOTTOM
     */
    MouseSelect(RIGHT_TOP, LEFT_BOTTOM);
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 2)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 3)->IsSelected());

    /**
     * @tc.steps: step3. Select from LEFT_BOTTOM to RIGHT_TOP
     */
    MouseSelect(LEFT_BOTTOM, RIGHT_TOP);
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 2)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 3)->IsSelected());

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
    CreateListWithItem([](ListModelNG listModelNG) { listModelNG.SetMultiSelectable(true); });
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
 * @tc.name: MouseSelect004
 * @tc.desc: Test listItem selectable about other condition
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, MouseSelect004, TestSize.Level1)
{
    CreateListWithItem([](ListModelNG listModelNG) { listModelNG.SetMultiSelectable(true); });

    /**
     * @tc.steps: step1. Use RIGHT_BUTTON to select.
     * @tc.expected: Nothing selected.
     */
    MouseInfo info;
    info.SetButton(MouseButton::RIGHT_BUTTON);
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(Offset::Zero());
    pattern_->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(Offset(200.f, 100.f));
    pattern_->HandleMouseEventWithoutKeyboard(info);
    for (int32_t index = 0; index < VIEWPORT_NUMBER; index++) {
        EXPECT_FALSE(GetChildPattern<ListItemPattern>(frameNode_, index)->IsSelected()) << "Index: " << index;
    }

    /**
     * @tc.steps: step2. Use LEFT_BUTTON, but with MouseAction::HOVER to select.
     * @tc.expected: Nothing selected.
     */
    info.SetButton(MouseButton::LEFT_BUTTON);
    info.SetAction(MouseAction::HOVER);
    info.SetLocalLocation(Offset::Zero());
    pattern_->HandleMouseEventWithoutKeyboard(info);
    for (int32_t index = 0; index < VIEWPORT_NUMBER; index++) {
        EXPECT_FALSE(GetChildPattern<ListItemPattern>(frameNode_, index)->IsSelected()) << "Index: " << index;
    }
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
    CreateListWithItem();
    EXPECT_TRUE(accessibilityProperty_->IsScrollable());
    EXPECT_EQ(accessibilityProperty_->GetBeginIndex(), 0);
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), VIEWPORT_NUMBER - 1);
    EXPECT_EQ(accessibilityProperty_->GetCollectionItemCounts(), TOTAL_NUMBER);

    /**
     * @tc.steps: step2. scroll to second item
     */
    ScrollDown();
    EXPECT_EQ(accessibilityProperty_->GetBeginIndex(), 0);
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), VIEWPORT_NUMBER);

    /**
     * @tc.steps: step3. unScrollable List
     */
    CreateList([](ListModelNG listModelNG) { CreateListItem(VIEWPORT_NUMBER); });
    EXPECT_FALSE(accessibilityProperty_->IsScrollable());
    EXPECT_EQ(accessibilityProperty_->GetBeginIndex(), 0);
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), VIEWPORT_NUMBER - 1);
    EXPECT_EQ(accessibilityProperty_->GetCollectionItemCounts(), VIEWPORT_NUMBER);
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
    CreateListWithItem();
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
    CreateList([](ListModelNG listModelNG) { CreateListItem(VIEWPORT_NUMBER); });
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
    CreateListWithItem();
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
    CreateList([](ListModelNG listModelNG) { CreateListItemGroup(); });
    auto groupAccessibilityProperty =
        GetChildFrameNode(frameNode_, 0)->GetAccessibilityProperty<ListItemGroupAccessibilityProperty>();
    EXPECT_EQ(groupAccessibilityProperty->GetBeginIndex(), 0);
    EXPECT_EQ(groupAccessibilityProperty->GetEndIndex(), 3);

    groupAccessibilityProperty =
        GetChildFrameNode(frameNode_, 4)->GetAccessibilityProperty<ListItemGroupAccessibilityProperty>();
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
    CreateList([](ListModelNG listModelNG) { CreateListItem(VIEWPORT_NUMBER); });
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
    CreateList([](ListModelNG listModelNG) { CreateListItem(VIEWPORT_NUMBER); });
    accessibilityProperty_->ActActionScrollForward();
    EXPECT_TRUE(IsEqualTotalOffset(0));
    accessibilityProperty_->ActActionScrollBackward();
    EXPECT_TRUE(IsEqualTotalOffset(0));

    /**
     * @tc.steps: step2. When list is Scrollable
     * @tc.expected: can scrollpage
     */
    CreateListWithItem();
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
    CreateList([itemNumber](ListModelNG listModelNG) { CreateListItem(itemNumber); });
    auto controller = pattern_->positionController_;

    /**
     * @tc.steps: step1. Verify initial value
     */
    EXPECT_EQ(controller->GetScrollDirection(), Axis::VERTICAL);
    EXPECT_EQ(controller->GetCurrentOffset(), Offset::Zero());

    /**
     * @tc.steps: step2. Test ScrollBy
     */
    controller->ScrollBy(ITEM_WIDTH, ITEM_HEIGHT, true);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT));
    controller->ScrollBy(ITEM_WIDTH, -ITEM_HEIGHT, true);
    EXPECT_TRUE(IsEqualTotalOffset(0));

    /**
     * @tc.steps: step3. Test ScrollPage
     */
    controller->ScrollPage(false, true);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT * VIEWPORT_NUMBER));
    controller->ScrollPage(true, true);
    EXPECT_TRUE(IsEqualTotalOffset(0));

    /**
     * @tc.steps: step4. Test ScrollToEdge
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    EXPECT_TRUE(IsEqualTotalOffset((itemNumber - VIEWPORT_NUMBER) * ITEM_HEIGHT));
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, true);
    EXPECT_TRUE(IsEqualTotalOffset(0));
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_NONE, true);
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
    CreateList([itemNumber](ListModelNG listModelNG) {
        listModelNG.SetListDirection(Axis::HORIZONTAL);
        CreateListItem(itemNumber, Axis::HORIZONTAL);
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
    controller->ScrollBy(ITEM_WIDTH, ITEM_HEIGHT, true);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_WIDTH));
    controller->ScrollBy(-ITEM_WIDTH, ITEM_HEIGHT, true);
    EXPECT_TRUE(IsEqualTotalOffset(0));

    /**
     * @tc.steps: step3. Test ScrollPage
     */
    controller->ScrollPage(false, true);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_WIDTH * VIEWPORT_NUMBER));
    controller->ScrollPage(true, true);
    EXPECT_TRUE(IsEqualTotalOffset(0));

    /**
     * @tc.steps: step4. Test ScrollToEdge
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    EXPECT_TRUE(IsEqualTotalOffset((itemNumber - VIEWPORT_NUMBER) * ITEM_WIDTH));
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, true);
    EXPECT_TRUE(IsEqualTotalOffset(0));
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_NONE, true);
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
    CreateListWithItem([](ListModelNG listModelNG) { listModelNG.SetListDirection(Axis::NONE); });
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
    CreateList([](ListModelNG listModelNG) { CreateListItem(VIEWPORT_NUMBER, Axis::VERTICAL, true); });

    /**
     * @tc.steps: step1. GetNextFocusNode from top.
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_INDEX));

    /**
     * @tc.steps: step2. GetNextFocusNode from middle.
     */
    currentIndex = 4;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
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
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 6));
}

/**
 * @tc.name: FocusStep002
 * @tc.desc: Test GetNextFocusNode func width HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, FocusStep002, TestSize.Level1)
{
    CreateList([](ListModelNG listModelNG) {
        listModelNG.SetListDirection(Axis::HORIZONTAL);
        CreateListItem(VIEWPORT_NUMBER, Axis::HORIZONTAL, true);
    });

    /**
     * @tc.steps: step1. GetNextFocusNode from left.
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_INDEX));

    /**
     * @tc.steps: step2. GetNextFocusNode from middle.
     */
    currentIndex = 4;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
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
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 6));
}

/**
 * @tc.name: FocusStep003
 * @tc.desc: Test GetNextFocusNode when List has ListItemGroup with VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, FocusStep003, TestSize.Level1)
{
    const int32_t groupNumber = 2;
    CreateList([groupNumber](ListModelNG listModelNG) {
        CreateListItemGroup(groupNumber, Axis::VERTICAL, true);
    });

    /**
     * @tc.steps: step1. GetNextFocusNode from top.
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_INDEX));

    /**
     * @tc.steps: step2. GetNextFocusNode from middle of first ListItemGroup.
     */
    currentIndex = 2;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
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
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
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
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
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
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 6));
}

/**
 * @tc.name: FocusStep004
 * @tc.desc: Test GetNextFocusNode when List has ListItemGroup with HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, FocusStep004, TestSize.Level1)
{
    const int32_t groupNumber = 2;
    CreateList([groupNumber](ListModelNG listModelNG) {
        listModelNG.SetListDirection(Axis::HORIZONTAL);
        CreateListItemGroup(groupNumber, Axis::HORIZONTAL, true);
    });

    /**
     * @tc.steps: step1. GetNextFocusNode from left.
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_INDEX));

    /**
     * @tc.steps: step2. GetNextFocusNode from middle of first ListItemGroup.
     */
    currentIndex = 2;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
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
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
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
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
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
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, NULL_INDEX));
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
    CreateList([](ListModelNG listModelNG) { CreateListItem(VIEWPORT_NUMBER, Axis::VERTICAL, true); });
    GetChildFocusHub(frameNode_, 1)->SetFocusable(false);
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, 0, 2));

    /**
     * @tc.steps: step2. GetNextFocusNode func from top boundary item
     * @tc.expected: Scroll to last item
     */
    CreateList([](ListModelNG listModelNG) { CreateListItem(TOTAL_NUMBER, Axis::VERTICAL, true); });
    UpdateCurrentOffset(-ITEM_HEIGHT - 1.f);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT + 1.f));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, 1, 0));
    EXPECT_TRUE(IsEqualTotalOffset(0));

    /**
     * @tc.steps: step3. GetNextFocusNode func from bottom boundary item
     * @tc.expected: Scroll to next item
     */
    CreateList([](ListModelNG listModelNG) { CreateListItem(TOTAL_NUMBER, Axis::VERTICAL, true); });
    ScrollDown();
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, 8, NULL_INDEX));
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT * 2));

    /**
     * @tc.steps: step4. GetNextFocusNode func from bottom boundary item
     * @tc.expected: Scroll to next item
     */
    // change focus between different group
    const float groupHeight = ITEM_HEIGHT * GROUP_ITEM_NUMBER;
    int32_t groupNumber = 3; // create scrollable List
    CreateList([groupNumber](ListModelNG listModelNG) {
        CreateListItemGroup(groupNumber, Axis::VERTICAL, true);
    });
    EXPECT_TRUE(IsEqualTotalOffset(0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, 7, NULL_INDEX));
    EXPECT_TRUE(IsEqualTotalOffset(groupHeight));
    // change focus in same group
    groupNumber = 3; // create scrollable List
    CreateList([groupNumber](ListModelNG listModelNG) {
        CreateListItemGroup(groupNumber, Axis::VERTICAL, true);
    });
    ScrollDown(2);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT * 2));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, 10, NULL_INDEX));
    EXPECT_TRUE(IsEqualTotalOffset(groupHeight));

    /**
     * @tc.steps: step5. GetNextFocusNode func from top boundary item
     * @tc.expected: Scroll to next item
     */
    // change focus between different group
    groupNumber = 3; // create scrollable List
    CreateList([groupNumber](ListModelNG listModelNG) {
        CreateListItemGroup(groupNumber, Axis::VERTICAL, true);
    });
    ScrollDown(GROUP_ITEM_NUMBER);
    EXPECT_TRUE(IsEqualTotalOffset(groupHeight));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, 3, 2));
    EXPECT_TRUE(IsEqualTotalOffset(0));
    // change focus in same group
    groupNumber = 3; // create scrollable List
    CreateList([groupNumber](ListModelNG listModelNG) {
        CreateListItemGroup(groupNumber, Axis::VERTICAL, true);
    });
    ScrollDown(3);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT * 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, 2, 1));
    EXPECT_TRUE(IsEqualTotalOffset(0));
}

/**
 * @tc.name: FocusStep006
 * @tc.desc: Test List focusing ability with lanes mode and VERTICAL.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, FocusStep006, TestSize.Level1)
{
    CreateList([](ListModelNG listModelNG) {
        listModelNG.SetLanes(4);
        CreateListItem(10, Axis::VERTICAL, true);
    });

    /**
     * @tc.steps: step1. GetNextFocusNode from left_top.
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_INDEX));

    /**
     * @tc.steps: step2. GetNextFocusNode from right_top.
     */
    currentIndex = 3;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 2));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_INDEX));
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
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_INDEX));
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
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 8));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 8));

    /**
     * @tc.steps: step5. GetNextFocusNode from middle.
     */
    currentIndex = 5;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
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
    CreateList([](ListModelNG listModelNG) {
        listModelNG.SetListDirection(Axis::HORIZONTAL);
        listModelNG.SetLanes(4);
        CreateListItem(10, Axis::HORIZONTAL, true);
    });

    /**
     * @tc.steps: step1. GetNextFocusNode from left_top.
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_INDEX));

    /**
     * @tc.steps: step2. GetNextFocusNode from right_top.
     */
    currentIndex = 8;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_INDEX));
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
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 2));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_INDEX));
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
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 8));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 8));

    /**
     * @tc.steps: step5. GetNextFocusNode from middle.
     */
    currentIndex = 5;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
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
    CreateList([](ListModelNG listModelNG) {
        listModelNG.SetLanes(2);
        CreateListItemGroup(2, Axis::VERTICAL, true);
    });

    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 2));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_INDEX));

    currentIndex = 3;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 2));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 2));

    currentIndex = 4;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 3));

    currentIndex = 7;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 6));
}

/**
 * @tc.name: FocusStep009
 * @tc.desc: Test List focusing ability with ListItemGroup and lanes mode and HORIZONTAL.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, FocusStep009, TestSize.Level1)
{
    CreateList([](ListModelNG listModelNG) {
        listModelNG.SetListDirection(Axis::HORIZONTAL);
        listModelNG.SetLanes(2);
        CreateListItemGroup(2, Axis::HORIZONTAL, true);
    });

    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 2));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_INDEX));

    currentIndex = 3;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 2));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 2));

    currentIndex = 4;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_INDEX));
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
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 6));
}

/**
 * @tc.name: KeyEvent001
 * @tc.desc: Test list_pattern OnKeyEvent function
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, KeyEvent001, TestSize.Level1)
{
    CreateListWithItem();

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
 * @tc.desc: Test List paint method
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, PaintMethod001, TestSize.Level1)
{
    CreateList([](ListModelNG listModelNG) { listModelNG.SetChainAnimation(true); });

    RefPtr<NodePaintMethod> paint = pattern_->CreateNodePaintMethod();
    ASSERT_NE(paint, nullptr);
    EXPECT_NE(pattern_->listContentModifier_, nullptr);
    paint = pattern_->CreateNodePaintMethod();
    EXPECT_NE(pattern_->listContentModifier_, nullptr);

    RefPtr<ListPaintMethod> listPaint = AceType::DynamicCast<ListPaintMethod>(paint);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper paintWrapper(nullptr, geometryNode, paintProperty_);
    listPaint->UpdateContentModifier(&paintWrapper);
    RSCanvas canvas;
    listPaint->GetForegroundDrawFunction(&paintWrapper);
    listPaint->PaintEdgeEffect(&paintWrapper, canvas);
    listPaint->PaintScrollBar(canvas);
    SUCCEED();
}

/**
 * @tc.name: PaintMethod002
 * @tc.desc: Test List paint method
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, PaintMethod002, TestSize.Level1)
{
    CreateList([](ListModelNG listModelNG) {
        listModelNG.SetScrollBar(Ace::DisplayMode::ON);
        listModelNG.SetDivider(ITEM_DIVIDER);
        CreateListItemGroup();
        CreateListItem(TOTAL_NUMBER);
    });

    auto scrollBar = pattern_->GetScrollBar();
    scrollBar->SetScrollable(true);
    scrollBar->normalWidth_ = Dimension(10);

    RefPtr<NodePaintMethod> paint = pattern_->CreateNodePaintMethod();
    RefPtr<ListPaintMethod> listPaint = AceType::DynamicCast<ListPaintMethod>(paint);
    listPaint->SetTotalItemCount(10);

    RSCanvas canvas;
    auto modifier = pattern_->listContentModifier_;
    DrawingContext ctx = { canvas, 1, 1};
    modifier->onDraw(ctx);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(100, 100));
    auto renderContext = frameNode_->GetRenderContext();
    renderContext->UpdateClipEdge(false);
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty_);
    listPaint->UpdateContentModifier(&paintWrapper);
    listPaint->PaintScrollBar(canvas);
    modifier->onDraw(ctx);
    SUCCEED();
}

/**
 * @tc.name: PaintMethod003
 * @tc.desc: Test List paint method
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, PaintMethod003, TestSize.Level1)
{
    CreateList([](ListModelNG listModelNG) {
        listModelNG.SetScrollBar(Ace::DisplayMode::ON);
        listModelNG.SetDivider(ITEM_DIVIDER);
        listModelNG.SetListDirection(Axis::HORIZONTAL);
        listModelNG.SetLanes(2);
        CreateListItemGroup();
        CreateListItem(TOTAL_NUMBER);
    });

    RefPtr<NodePaintMethod> paint = pattern_->CreateNodePaintMethod();
    RefPtr<ListPaintMethod> listPaint = AceType::DynamicCast<ListPaintMethod>(paint);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(100, 100));
    PaintWrapper paintWrapper(nullptr, geometryNode, paintProperty_);
    listPaint->UpdateContentModifier(&paintWrapper);
    RSCanvas canvas;
    listPaint->PaintScrollBar(canvas);

    auto modifier = pattern_->listContentModifier_;
    DrawingContext ctx = { canvas, 1, 1};
    modifier->onDraw(ctx);
    SUCCEED();
}

/**
 * @tc.name: PaintMethod004
 * @tc.desc: Test ListItemGroup paint method
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, PaintMethod004, TestSize.Level1)
{
    CreateList([](ListModelNG listModelNG) {
        CreateListItemGroup();
    });

    auto groupFrameNode = GetChildFrameNode(frameNode_, 0);
    auto groupPattern = groupFrameNode->GetPattern<ListItemGroupPattern>();

    RefPtr<NodePaintMethod> paint = groupPattern->CreateNodePaintMethod();
    RefPtr<ListItemGroupPaintMethod> groupPaint = AceType::DynamicCast<ListItemGroupPaintMethod>(paint);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper paintWrapper(nullptr, geometryNode, paintProperty_);
    RSCanvas canvas;
    groupPaint->PaintDivider(&paintWrapper, canvas);

    groupPaint->divider_ = ITEM_DIVIDER;
    groupPaint->PaintDivider(&paintWrapper, canvas);

    groupPaint->lanes_ = 2;
    groupPaint->PaintDivider(&paintWrapper, canvas);

    groupPaint->vertical_ = true;
    groupPaint->PaintDivider(&paintWrapper, canvas);

    EXPECT_TRUE(true);
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
    CreateListWithItem([options](ListModelNG listModelNG) {
        listModelNG.SetSpace(Dimension(SPACE));
        listModelNG.SetChainAnimation(true);
        listModelNG.SetChainAnimationOptions(options);
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
    CreateListWithItem([options](ListModelNG listModelNG) {
        listModelNG.SetSpace(Dimension(SPACE));
        listModelNG.SetChainAnimation(true);
        listModelNG.SetChainAnimationOptions(options);
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
    CreateListWithItem([options](ListModelNG listModelNG) {
        listModelNG.SetSpace(Dimension(SPACE));
        listModelNG.SetChainAnimation(true);
        listModelNG.SetChainAnimationOptions(options);
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
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetMultiSelectable(true);
    CreateListItem(TOTAL_NUMBER);
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
    RunMeasureAndLayout(frameNode_);
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
    CreateListWithItem();

    pattern_->AnimateTo(0, 0, nullptr, true);
    EXPECT_NE(pattern_->animator_, nullptr);

    pattern_->animator_->Pause();
    pattern_->AnimateTo(0, 0, nullptr, true);
    EXPECT_NE(pattern_->animator_, nullptr);

    pattern_->animator_->Stop();
    pattern_->AnimateTo(0, 0, nullptr, true);
    EXPECT_NE(pattern_->animator_, nullptr);
}

/**
 * @tc.name: Pattern003
 * @tc.desc: Test OutBoundaryCallback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern003, TestSize.Level1)
{
    CreateListWithItem();
    EXPECT_TRUE(pattern_->OutBoundaryCallback());
    ScrollDown();
    EXPECT_FALSE(pattern_->OutBoundaryCallback());
    ScrollDown();
    EXPECT_TRUE(pattern_->OutBoundaryCallback());

    CreateListWithItem([](ListModelNG listModelNG) {
        listModelNG.SetChainAnimation(true);
        listModelNG.SetChainAnimationOptions(
            { Dimension(0), Dimension(10), 0, 0, 0, DEFAULT_STIFFNESS, DEFAULT_DAMPING });
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
    constexpr int32_t itemNumber = 20;
    CreateList([itemNumber](ListModelNG listModelNG) { CreateListItem(itemNumber); });
    /**
     * @tc.steps: step1. first item in viewport
     */
    int32_t index = 0;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 0));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 0));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 0));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 0));

    /**
     * @tc.steps: step2. the item in viewport
     */
    index = 6;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 600.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 250.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 0));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 0));

    /**
     * @tc.steps: step3. the item below viewport
     */
    index = 9;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 900.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 550.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 0));

    /**
     * @tc.steps: step4. last item below viewport
     */
    index = ListLayoutAlgorithm::LAST_ITEM;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 0));

    /**
     * @tc.steps: step5. scroll to middle, first item above viewport
     */
    ScrollDown(8);
    index = 0;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 0));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 0));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 0));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 800.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 800.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 800.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 800.f));

    /**
     * @tc.steps: step6. the item above viewport
     */
    index = 6;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 600.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 250.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 0));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 600.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 800.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 800.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 800.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 800.f));

    /**
     * @tc.steps: step7. scroll to bottom, last item in viewport
     */
    ScrollDown(4);
    index = ListLayoutAlgorithm::LAST_ITEM;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 1200.f));

    /**
     * @tc.steps: step8. Invalid index, index < -1
     */
    index = -2;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 1200.f));
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
    CreateList([itemNumber, lanes](ListModelNG listModelNG) {
        listModelNG.SetLanes(lanes);
        CreateListItem(itemNumber);
    });

    /**
     * @tc.steps: step1. first item in viewport
     */
    int32_t index = 0;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 0));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 0));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 0));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 0));

    /**
     * @tc.steps: step2. the item in viewport
     */
    index = 3;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 100.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 0));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 0));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 0));

    /**
     * @tc.steps: step3. the item below viewport
     */
    index = 16;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 100.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 100.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 0));

    /**
     * @tc.steps: step4. last item below viewport
     */
    index = ListLayoutAlgorithm::LAST_ITEM;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 0));

    /**
     * @tc.steps: step5. scroll to bottom, first item above viewport
     */
    ScrollDown(20);
    index = 0;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 0));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 0));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 0));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 200.f));

    /**
     * @tc.steps: step6. the item above viewport
     */
    index = 3;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 100.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 0));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 0));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 100.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 200.f));

    /**
     * @tc.steps: step7. last item in viewport
     */
    index = ListLayoutAlgorithm::LAST_ITEM;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 200.f));
}

/**
 * @tc.name: ScrollToIndex003
 * @tc.desc: Test ScrollToIndex with ListItemGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ScrollToIndex003, TestSize.Level1)
{
    constexpr int32_t groupNumber = 5;
    CreateList([groupNumber](ListModelNG listModelNG) {
        CreateListItemGroup(groupNumber);
    });

    /**
     * @tc.steps: step1. first group in viewport
     */
    int32_t index = 0;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 0));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 0));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 0));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 0));

    /**
     * @tc.steps: step2. the group in viewport
     */
    index = 1;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 400.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 0));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 0));

    /**
     * @tc.steps: step3. the group below viewport
     */
    index = 2;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 800.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 600.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 400.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 400.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 0));

    /**
     * @tc.steps: step4. last group below viewport
     */
    index = ListLayoutAlgorithm::LAST_ITEM;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 0));

    /**
     * @tc.steps: step5. scroll to middle, first group above viewport
     */
    ScrollDown(8);
    index = 0;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 0));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 0));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 0));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 0));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 800.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 800.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 800.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 800.f));

    /**
     * @tc.steps: step6. the group above viewport
     */
    index = 1;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 400.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 0));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 400.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 800.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 800.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 800.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 800.f));

    /**
     * @tc.steps: step7. scroll to bottom, last item in viewport
     */
    ScrollDown(20);
    index = ListLayoutAlgorithm::LAST_ITEM;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 1600.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 1200.f));
}

/**
 * @tc.name: ScrollToIndex004
 * @tc.desc: Test ScrollToIndex with ListItemGroup and indexInGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ScrollToIndex004, TestSize.Level1)
{
    constexpr int32_t groupNumber = 5;
    CreateList([groupNumber](ListModelNG listModelNG) {
        CreateListItemGroup(groupNumber);
    });
    constexpr int32_t indexInGroup = 2;

    /**
     * @tc.steps: step1. first group in viewport
     */
    int32_t index = 0;
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::START, 0));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::CENTER, 0));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::END, 0));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::AUTO, 0));

    /**
     * @tc.steps: step2. the group below viewport
     */
    index = 2;
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::START, 600.f));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::CENTER, 400.f + 100.f / 3));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::END, 300.f));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::AUTO, 400.f));

    /**
     * @tc.steps: step3. last group below viewport
     */
    index = ListLayoutAlgorithm::LAST_ITEM;
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::START, 1000.f));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::CENTER, 1000.f));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::END, 1000.f + 100.f / 3));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::AUTO, 1200.f));

    /**
     * @tc.steps: step4. scroll to bottom, first group above viewport
     */
    ScrollDown(12);
    index = 0;
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::START, 0));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::CENTER, 0));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::END, 0));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::AUTO, 0));

    /**
     * @tc.steps: step5. the group above viewport
     */
    index = 1;
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::START, 300.f + 100.f / 3));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::CENTER, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::END, 0));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::AUTO, 400.f));

    /**
     * @tc.steps: step6. last item in viewport
     */
    index = ListLayoutAlgorithm::LAST_ITEM;
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::START, 800.f));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::CENTER, 1000.f));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::END, 1000.f + 100.f / 3));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::AUTO, 1200.f));
}

/**
 * @tc.name: ScrollToIndex005
 * @tc.desc: Test ScrollToIndex with ListItemGroup and indexInGroup and lanes
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ScrollToIndex005, TestSize.Level1)
{
    constexpr int32_t groupNumber = 10;
    constexpr int32_t lanes = 2;
    CreateList([groupNumber, lanes](ListModelNG listModelNG) {
        listModelNG.SetLanes(lanes);
        CreateListItemGroup(groupNumber);
    });

    /**
     * @tc.steps: step1. first group in viewport
     */
    int32_t index = 0;
    int32_t indexInGroup = 0;
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::START, 0));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::CENTER, 0));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::END, 0));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::AUTO, 0));

    /**
     * @tc.steps: step2. the group below viewport
     */
    index = 4;
    indexInGroup = 3;
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::START, 600.f));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::CENTER, 350.f));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::END, 400.f));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::AUTO, 400.f));

    /**
     * @tc.steps: step3. last group below viewport
     */
    index = ListLayoutAlgorithm::LAST_ITEM;
    indexInGroup = 3;
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::START, 400.f));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::CENTER, 700.f));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::END, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::AUTO, 1200.f));

    /**
     * @tc.steps: step4. scroll to bottom, first group above viewport
     */
    ScrollDown(20);
    index = 0;
    indexInGroup = 0;
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::START, 0));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::CENTER, 0));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::END, 0));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::AUTO, 0));

    /**
     * @tc.steps: step5. the group above viewport
     */
    index = 2;
    indexInGroup = 1;
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::START, 400.f));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::CENTER, 100.f));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::END, 0));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::AUTO, 400.f));

    /**
     * @tc.steps: step6. last item in viewport
     */
    index = ListLayoutAlgorithm::LAST_ITEM;
    indexInGroup = 3;
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::START, 400.f));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::CENTER, 700.f));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::END, 1200.f));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::AUTO, 1200.f));
}

/**
 * @tc.name: Pattern005
 * @tc.desc: Test OnScrollCallback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern005, TestSize.Level1)
{
    CreateListWithItem([](ListModelNG listModelNG) {
        listModelNG.SetScrollSnapAlign(V2::ScrollSnapAlign::START);
        listModelNG.SetChainAnimation(true);
        auto startFunc = GetDefaultSwiperBuilder(START_NODE_SIZE);
        CreateListItemWithSwiper(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    });

    // Set swiperItem_ to list pattern
    DragSwiperItem(0, 1.f);

    /**
     * @tc.steps: step1. When has animator_ and not stop, call OnScrollCallback.
     * @tc.expected: Would stop.
     */
    pattern_->AnimateTo(0, 0, nullptr, true);
    pattern_->animator_->Resume();
    EXPECT_TRUE(pattern_->animator_->IsRunning());
    pattern_->OnScrollPosition(100.f, SCROLL_FROM_START);
    EXPECT_TRUE(pattern_->scrollAbort_);
    pattern_->OnScrollCallback(100.f, SCROLL_FROM_START);
    EXPECT_TRUE(pattern_->scrollAbort_);
    EXPECT_TRUE(IsEqualTotalOffset(0));
    EXPECT_TRUE(pattern_->animator_->IsStopped());

    /**
     * @tc.steps: step2. When has animator_ and stop, call OnScrollCallback.
     * @tc.expected:
     */
    ASSERT_NE(pattern_->GetScrollBar(), nullptr);
    pattern_->OnScrollCallback(100.f, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout(frameNode_);
    EXPECT_GT(pattern_->GetTotalOffset(), -ITEM_HEIGHT);

    /**
     * @tc.steps: step3. Offset is 0, ProcessDragUpdate do nothing.
     * @tc.expected: CurrentOffset unchange.
     */
    pattern_->OnScrollCallback(0, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout(frameNode_);
    EXPECT_GT(pattern_->GetTotalOffset(), -ITEM_HEIGHT);

    /**
     * @tc.steps: step4. When has animator_ and stop, call StopAnimate.
     * @tc.expected: Nothing.
     */
    pattern_->StopAnimate();

    pattern_->OnScrollCallback(850.f, SCROLL_FROM_START);
    EXPECT_EQ(pattern_->chainAnimation_->GetControlIndex(), 6);
    pattern_->OnScrollCallback(0.f, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout(frameNode_);
    pattern_->OnScrollCallback(-100.f, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout(frameNode_);
    pattern_->OnScrollCallback(100.f, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout(frameNode_);
}

/**
 * @tc.name: Pattern006
 * @tc.desc: Test GetItemIndexByPosition
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern006, TestSize.Level1)
{
    CreateList([](ListModelNG listModelNG) {
        listModelNG.SetLanes(2);
        CreateListItem(VIEWPORT_NUMBER);
    });

    /**
     * @tc.steps: step1. When lanes > 1, call GetItemIndexByPosition
     * @tc.expected: Would return correct itemIndex
     */
    const Point point = Point(300.f, 250.f);
    constexpr int32_t expectIndex = 5;
    int32_t itemIndex = pattern_->GetItemIndexByPosition(point.GetX(), point.GetY());
    EXPECT_EQ(itemIndex, expectIndex);
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
    CreateList([](ListModelNG listModelNG) { CreateListItem(VIEWPORT_NUMBER); });
    const Point point = Point(0, 1000.f);
    int32_t itemIndex = pattern_->GetItemIndexByPosition(point.GetX(), point.GetY());
    EXPECT_EQ(itemIndex, VIEWPORT_NUMBER);
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
    CreateList();
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
    CreateList();
    UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(IsEqualTotalOffset(0));

    /**
     * @tc.steps: step2. unscrollable List
     */
    CreateList([](ListModelNG listModelNG) { CreateListItem(VIEWPORT_NUMBER); });
    UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(IsEqualTotalOffset(0));

    /**
     * @tc.steps: step3. UpdateCurrentOffset with SCROLL_FROM_START
     * @tc.expected: The offset was not effected by friction
     */
    CreateListWithItem();
    UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_START);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT));

    /**
     * @tc.steps: step4. UpdateCurrentOffset with SCROLL_FROM_START
     * @tc.expected: The offset was not effected by friction
     */
    CreateListWithItem([](ListModelNG listModelNG) { listModelNG.SetScrollSnapAlign(V2::ScrollSnapAlign::CENTER); });
    UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_UPDATE);
    EXPECT_LT(pattern_->GetTotalOffset(), -400.f);
    UpdateCurrentOffset(-ITEM_HEIGHT * 8, SCROLL_FROM_UPDATE);
    EXPECT_LT(pattern_->GetTotalOffset(), 400.f);
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
    GetInstance();
    RunMeasureAndLayout(frameNode_, -1, -1);
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Width(), DEVICE_WIDTH);

    /**
     * @tc.steps: step1. do not set selfIdealSize, TOTAL_NUMBER listItem
     */
    ListModelNG listModelNG_2;
    listModelNG_2.Create();
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout(frameNode_, -1, -1);
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Width(), DEVICE_WIDTH);

    /**
     * @tc.steps: step1. set width Infinity
     */
    ListModelNG listModelNG_3;
    listModelNG_3.Create();
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout(frameNode_, Infinity<float>(), DEVICE_HEIGHT);
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Width(), Infinity<float>());
}

/**
 * @tc.name: SetEdgeEffectCallback001
 * @tc.desc: Test SetEdgeEffectCallback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SetEdgeEffectCallback001, TestSize.Level1)
{
    CreateListWithItem([](ListModelNG listModelNG) { listModelNG.SetEdgeEffect(EdgeEffect::SPRING); });
    RefPtr<ScrollEdgeEffect> scrollEdgeEffect = pattern_->GetScrollEdgeEffect();
    auto currentPosition = scrollEdgeEffect->currentPositionCallback_();
    auto leading = scrollEdgeEffect->leadingCallback_();
    auto trailing = scrollEdgeEffect->trailingCallback_();
    auto initLeading = scrollEdgeEffect->initLeadingCallback_();
    auto initTrailing = scrollEdgeEffect->initTrailingCallback_();
    EXPECT_EQ(currentPosition, 0);
    EXPECT_EQ(leading, 0);
    EXPECT_EQ(trailing, 0.0);
    EXPECT_EQ(initLeading, 0);
    EXPECT_EQ(initTrailing, 0.0);

    CreateListWithItem([](ListModelNG listModelNG) {
        listModelNG.SetScrollSnapAlign(V2::ScrollSnapAlign::CENTER);
        listModelNG.SetEdgeEffect(EdgeEffect::SPRING);
    });
    scrollEdgeEffect = pattern_->GetScrollEdgeEffect();
    currentPosition = scrollEdgeEffect->currentPositionCallback_();
    leading = scrollEdgeEffect->leadingCallback_();
    trailing = scrollEdgeEffect->trailingCallback_();
    initLeading = scrollEdgeEffect->initLeadingCallback_();
    initTrailing = scrollEdgeEffect->initTrailingCallback_();
    EXPECT_EQ(currentPosition, 350.0);
    EXPECT_EQ(leading, -50.0);
    EXPECT_EQ(trailing, 350.f);
    EXPECT_EQ(initLeading, -50.0);
    EXPECT_EQ(initTrailing, 350.f);

    CreateList([](ListModelNG listModelNG) {
        listModelNG.SetScrollSnapAlign(V2::ScrollSnapAlign::CENTER);
        listModelNG.SetEdgeEffect(EdgeEffect::SPRING);
    });
    scrollEdgeEffect = pattern_->GetScrollEdgeEffect();
    currentPosition = scrollEdgeEffect->currentPositionCallback_();
    leading = scrollEdgeEffect->leadingCallback_();
    trailing = scrollEdgeEffect->trailingCallback_();
    initLeading = scrollEdgeEffect->initLeadingCallback_();
    initTrailing = scrollEdgeEffect->initTrailingCallback_();
    EXPECT_EQ(currentPosition, 0);
    EXPECT_EQ(leading, 800);
    EXPECT_EQ(trailing, 0.0);
    EXPECT_EQ(initLeading, 800);
    EXPECT_EQ(initTrailing, 0.0);
}

/**
 * @tc.name: Pattern012
 * @tc.desc: Test ScrollToNode
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern012, TestSize.Level1)
{
    // test ScrollToNode
    CreateListWithItem();
    auto listItem = GetChildFrameNode(frameNode_, 8);
    bool ret = pattern_->ScrollToNode(listItem);
    EXPECT_TRUE(ret);

    // test GetTotalHeight
    CreateList();
    EXPECT_EQ(pattern_->GetTotalHeight(), 0.f);
    CreateListWithItem();
    EXPECT_EQ(pattern_->GetTotalHeight(), TOTAL_NUMBER * ITEM_HEIGHT);

    // test ToJsonValue/FromJson
    CreateListWithItem();
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
    /**
     * @tc.steps: step1. Create List/ListItemGroup/ListItem.
     * @tc.expected: step1. create a card style ListItemGroup success.
     */
    CreateList([](ListModelNG listModelNG) {
        listModelNG.SetMultiSelectable(true);
        ListItemGroupModelNG listItemGroupModel;
        listItemGroupModel.Create(V2::ListItemGroupStyle::CARD);
        CreateListItem(9);
        ViewStackProcessor::GetInstance()->Pop();
    });

    /**
     * @tc.steps: step2. Click the (0, 0) point of firstItem.
     * @tc.expected: Can not select by click, the item is not selected.
     */
    MouseInfo info;
    info.SetButton(MouseButton::LEFT_BUTTON);
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(Offset(0.f, 0.f));
    pattern_->HandleMouseEventWithoutKeyboard(info);

    /**
     * @tc.steps: step3. Get ListItemGroup frameNode and ListItemPattern.
     * @tc.expected: Get ListItemGroup frameNode/ListItemPattern success, and judge the step2.
     */
    auto itemGroup = frameNode_->GetChildAtIndex(0);
    auto itemGroupFrameNode = AceType::DynamicCast<FrameNode>(itemGroup);
    auto item = itemGroupFrameNode->GetChildAtIndex(0);
    auto itemFrameNode = AceType::DynamicCast<FrameNode>(item);
    RefPtr<ListItemPattern> firstItemPattern = itemFrameNode->GetPattern<ListItemPattern>();
    EXPECT_FALSE(firstItemPattern->IsSelected());

    /**
     * @tc.steps: step4. Release the mouse to deselect.
     * @tc.expected: Release the mouse to deselect.
     */
    info.SetAction(MouseAction::RELEASE);
    pattern_->HandleMouseEventWithoutKeyboard(info);
    firstItemPattern->MarkIsSelected(false);
    EXPECT_FALSE(firstItemPattern->IsSelected());
}

/**
 * @tc.name: ListSelectForCardModeTest002
 * @tc.desc: Test the card mode for select.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListSelectForCardModeTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List/ListItemGroup/ListItem.
     * @tc.expected: step1. create a card style ListItemGroup success.
     */
    CreateList([](ListModelNG listModelNG) {
        listModelNG.SetMultiSelectable(true);
        ListItemGroupModelNG listItemGroupModel;
        listItemGroupModel.Create(V2::ListItemGroupStyle::CARD);
        CreateListItem(9);
        ViewStackProcessor::GetInstance()->Pop();
    });

    /**
     * @tc.steps: step2. Select (0, 0) - (200, 100) zone.
     * @tc.expected: The 1st item is selected.
     */
    MouseInfo info;
    info.SetButton(MouseButton::LEFT_BUTTON);
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(Offset(0.f, 0.f));
    pattern_->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(Offset(200.f, 100.f));
    pattern_->HandleMouseEventWithoutKeyboard(info);

    /**
     * @tc.steps: step3. Get ListItemGroup frameNode and ListItemPattern.
     * @tc.expected: Get ListItemGroup frameNode/ListItemPattern success, and judge the step2.
     */
    auto itemGroup = frameNode_->GetChildAtIndex(0);
    auto itemGroupFrameNode = AceType::DynamicCast<FrameNode>(itemGroup);
    auto item = itemGroupFrameNode->GetChildAtIndex(0);
    auto itemFrameNode = AceType::DynamicCast<FrameNode>(item);
    RefPtr<ListItemPattern> firstItemPattern = itemFrameNode->GetPattern<ListItemPattern>();
    EXPECT_TRUE(firstItemPattern->IsSelected());

    /**
     * @tc.steps: step4. Release the mouse to deselect.
     * @tc.expected: Release the mouse to deselect.
     */
    info.SetAction(MouseAction::RELEASE);
    pattern_->HandleMouseEventWithoutKeyboard(info);
    firstItemPattern->MarkIsSelected(false);
    EXPECT_FALSE(firstItemPattern->IsSelected());
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
    constexpr int32_t itemCount = 9;
    CreateList([itemCount](ListModelNG listModelNG) {
        listModelNG.SetMultiSelectable(true);
        ListItemGroupModelNG listItemGroupModel;
        listItemGroupModel.Create(V2::ListItemGroupStyle::CARD);
        for (int32_t i = 0; i < itemCount; i++) {
            ListItemModelNG listItemModel;
            listItemModel.Create();
            SetHeight(Dimension(ITEM_HEIGHT));
            SetWidth(FILL_LENGTH);
            if (i == 3) {
                listItemModel.SetSelectable(false);
            }
            ViewStackProcessor::GetInstance()->Pop();
        }
        ViewStackProcessor::GetInstance()->Pop();
    });

    /**
     * @tc.steps: step2. Select (120, 250) - (360, 350) zone.
     * @tc.expected: The third and fourth listItems cannot be selected.
     */
    MouseInfo info;
    info.SetButton(MouseButton::LEFT_BUTTON);
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(Offset(120.f, 350.f));
    pattern_->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(Offset(360.f, 450.f));
    pattern_->HandleMouseEventWithoutKeyboard(info);

    /**
     * @tc.steps: step3. Get ListItemGroup frameNode and ListItemPattern.
     * @tc.expected: Get ListItemGroup frameNode/ListItemPattern success, and judge the step2.
     */
    auto itemGroupFrameNode = GetChildFrameNode(frameNode_, 0);
    auto itemFourth = itemGroupFrameNode->GetChildAtIndex(3);
    auto itemFourthFrameNode = AceType::DynamicCast<FrameNode>(itemFourth);
    RefPtr<ListItemPattern> fourthItemPattern = itemFourthFrameNode->GetPattern<ListItemPattern>();
    EXPECT_FALSE(fourthItemPattern->IsSelected());

    /**
     * @tc.steps: step4. Release the mouse to deselect.
     * @tc.expected: Release the mouse to deselect.
     */
    info.SetAction(MouseAction::RELEASE);
    pattern_->HandleMouseEventWithoutKeyboard(info);
    fourthItemPattern->MarkIsSelected(false);
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
    ListItemGroupModelNG listItemGroupModelNG;
    listItemGroupModelNG.Create(V2::ListItemGroupStyle::CARD);
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
    ListItemModelNG listItemModel;
    listItemModel.Create([](int32_t) {}, V2::ListItemStyle::CARD);
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
    ListItemModelNG listItemModel;
    listItemModel.Create([](int32_t) {}, V2::ListItemStyle::CARD);
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
    ListItemModelNG listItemModel;
    listItemModel.Create([](int32_t) {}, V2::ListItemStyle::CARD);
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
    ListItemModelNG listItemModel;
    listItemModel.Create([](int32_t) {}, V2::ListItemStyle::CARD);
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
    CreateListWithItem();
    pattern_->AnimateTo(0, 0, nullptr, true);
    pattern_->UpdateScrollSnap();
    EXPECT_FALSE(pattern_->predictSnapOffset_.has_value());

    pattern_->animator_->Stop();
    pattern_->UpdateScrollSnap();
    EXPECT_EQ(pattern_->predictSnapOffset_.value(), 0.0);
}

/**
 * @tc.name: ListPattern_SetFriction001
 * @tc.desc: Test SetFriction:friction shouled be more than 0.0,if out of range,should be default value.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListPattern_SetFriction001, TestSize.Level1)
{
    CreateListWithItem([](ListModelNG listModelNG) { listModelNG.SetFriction(0); });
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), DEFAULT_FRICTION);
    CreateListWithItem([](ListModelNG listModelNG) { listModelNG.SetFriction(-1); });
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), DEFAULT_FRICTION);
    CreateListWithItem([](ListModelNG listModelNG) { listModelNG.SetFriction(1); });
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), 1);
}
} // namespace OHOS::Ace::NG
