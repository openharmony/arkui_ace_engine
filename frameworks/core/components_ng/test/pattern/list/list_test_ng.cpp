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
#include "core/components/scroll/scrollable.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/linear_layout/row_model_ng.h"
#define private public
#define protected public
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
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_v2/list/list_properties.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "frameworks/bridge/common/utils/utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float DEVICE_WIDTH = 480.f;
constexpr float DEVICE_HEIGHT = 800.f;
constexpr int32_t TOTAL_NUMBER = 10;
constexpr int32_t VIEWPORT_NUMBER = 8;
constexpr float ITEM_HEIGHT = 100.f;
constexpr float ITEM_WIDTH = 60.f;
constexpr Dimension FILL_LENGTH = Dimension(1.0, DimensionUnit::PERCENT);
constexpr float HEADER_MAIN_LENGTH = 50.f;
constexpr float START_NODE_SIZE = 80.f;
constexpr float END_NODE_SIZE = 100.f;
constexpr Dimension DELETE_AREA_DISTANCE = Dimension(50, DimensionUnit::VP);
constexpr float MOVE_DELTA_20 = 20.f;
constexpr float MOVE_DELTA_80 = 80.f;
constexpr float MOVE_DELTA_100 = 100.f;
constexpr Dimension GROUP_MARGIN = 12.0_vp;
constexpr float DEFAULT_STIFFNESS = 228;
constexpr float DEFAULT_DAMPING = 30;
constexpr float SWIPER_SPEED_TH = 1200.f;
constexpr float SWIPER_TH = 0.25f;
constexpr int32_t DEFAULT_LANES = 1;
constexpr int32_t DEFAULT_INTERVAL = 0;
constexpr int32_t DEFAULT_STARTINDEX = 0;
} // namespace

class ListTestNg : public testing::Test {
protected:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();
    RefPtr<LayoutWrapper> RunMeasureAndLayout(float width = DEVICE_WIDTH, float height = DEVICE_HEIGHT);
    static void SetWidth(const Dimension& width);
    static void SetHeight(const Dimension& height);
    void CreateList(int32_t number);
    void CreateListItemGroup(int32_t GroupCount);
    void CreateListItem(int32_t itemCount, Axis Direction = Axis::VERTICAL, bool focusable = false);
    void CreateListItemWithSwiper(
        std::function<void()> startAction, std::function<void()> endAction, V2::SwipeEdgeEffect effect);
    void CreateListItemWithSwipeActionItem(std::function<void()> builderAction, bool useDefaultDeleteAnimation,
        OnDeleteEvent onDelete, OnEnterDeleteAreaEvent onEnterDeleteArea, OnExitDeleteAreaEvent onExitDeleteArea,
        const Dimension& length, bool isStartArea, V2::SwipeEdgeEffect effect);
    RefPtr<FrameNode> GetChildFrameNode(int32_t index);
    RefPtr<FocusHub> GetChildFocusHub(int32_t index);
    RefPtr<ListItemPattern> GetItemPattern(int32_t index);
    RefPtr<ListItemGroupPattern> GetGroupPattern(int32_t index);
    const RectF& GetChildRect(const RefPtr<FrameNode>& frameNode, int32_t index);
    void ListItemSwipeMoveAndLayout(const RefPtr<ListItemPattern>& itemPattern, float moveDelta);
    std::function<void()> GetDefaultSwiperBuilder(float crossSize, bool spring);
    std::function<void()> GetDefaultHeaderBuilder();
    testing::AssertionResult VerifyItemPosition(int32_t expectCount, int32_t lanes = DEFAULT_LANES,
        float interval = DEFAULT_INTERVAL, int32_t startIndex = DEFAULT_STARTINDEX);
    testing::AssertionResult VerifyGroupItemPosition(int32_t groupIndex, int32_t expectCount,
        int32_t lanes = DEFAULT_LANES, float interval = DEFAULT_INTERVAL);
    testing::AssertionResult IsEqualNextFocusNode(FocusStep step, int32_t currentIndex, int32_t nextIndex = -1);
    testing::AssertionResult IsEqualCurrentOffset(Offset expectOffset);
    testing::AssertionResult IsEqualRect(RectF rect, RectF expectRect);
    testing::AssertionResult VerifySwiperItemChildRect(RefPtr<FrameNode> listItem, std::vector<RectF> expectRects);
    void MouseSelect(Offset start, Offset end);
    void MouseSelectRelease();
    void UpdateCurrentOffset(float offset);
    void ScrollToTop();
    void ScrollToBottom();
    void DragSwiperItem(int32_t index, GestureEvent info);
    void DragSwiperItem(int32_t index, float mainDelta, float mainVelocity = SWIPER_SPEED_TH);
    uint64_t GetActions();

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
    // set buttonTheme to themeManager before using themeManager to get buttonTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));
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
}

RefPtr<LayoutWrapper> ListTestNg::RunMeasureAndLayout(float width, float height)
{
    RefPtr<LayoutWrapper> layoutWrapper = frameNode_->CreateLayoutWrapper(false, false);
    layoutWrapper->SetActive();
    layoutWrapper->SetRootMeasureNode();
    LayoutConstraintF LayoutConstraint;
    LayoutConstraint.parentIdealSize = { DEVICE_WIDTH, DEVICE_HEIGHT };
    LayoutConstraint.percentReference = { DEVICE_WIDTH, DEVICE_HEIGHT };
    if (NonNegative(width) && NonNegative(height)) {
        LayoutConstraint.selfIdealSize = { width, height };
    }
    LayoutConstraint.maxSize = { DEVICE_WIDTH, DEVICE_HEIGHT };
    layoutWrapper->Measure(LayoutConstraint);
    layoutWrapper->Layout();
    layoutWrapper->MountToHostOnMainThread();
    return layoutWrapper;
}

void ListTestNg::SetWidth(const Dimension& width)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto layoutProperty = frameNode->GetLayoutProperty();
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(width), std::nullopt));
}

void ListTestNg::SetHeight(const Dimension& height)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto layoutProperty = frameNode->GetLayoutProperty();
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(height)));
}

void ListTestNg::CreateList(int32_t number)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItem(number);
    GetInstance();
    RunMeasureAndLayout();
}

void ListTestNg::CreateListItemGroup(int32_t GroupCount)
{
    for (int32_t index = 0; index < GroupCount; index++) {
        ListItemGroupModelNG listItemGroupModel;
        listItemGroupModel.Create(V2::ListItemGroupStyle::NONE);
        CreateListItem(VIEWPORT_NUMBER);
        ViewStackProcessor::GetInstance()->Pop();
    }
}

void ListTestNg::CreateListItem(int32_t itemCount, Axis Direction, bool focusable)
{
    for (int32_t index = 0; index < itemCount; index++) {
        ListItemModelNG listItemModel;
        listItemModel.Create();
        if (Direction == Axis::VERTICAL) {
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
    RunMeasureAndLayout();
}

RefPtr<FrameNode> ListTestNg::GetChildFrameNode(int32_t index)
{
    return AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(index));
}

RefPtr<FocusHub> ListTestNg::GetChildFocusHub(int32_t index)
{
    return GetChildFrameNode(index)->GetOrCreateFocusHub();
}

RefPtr<ListItemPattern> ListTestNg::GetItemPattern(int32_t index)
{
    return GetChildFrameNode(index)->GetPattern<ListItemPattern>();
}

RefPtr<ListItemGroupPattern> ListTestNg::GetGroupPattern(int32_t index)
{
    return GetChildFrameNode(index)->GetPattern<ListItemGroupPattern>();
}

const RectF& ListTestNg::GetChildRect(const RefPtr<FrameNode>& frameNode, int32_t index)
{
    auto child = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(index));
    return child->GetGeometryNode()->GetFrameRect();
}

std::function<void()> ListTestNg::GetDefaultSwiperBuilder(float crossSize, bool spring)
{
    return [crossSize, spring]() {
        RowModelNG rowModel;
        rowModel.Create(std::nullopt, nullptr, "");
        SetHeight(Dimension(ITEM_HEIGHT));
        if (spring) {
            RowModelNG rowModel;
            rowModel.Create(std::nullopt, nullptr, "");
            SetWidth(Dimension(crossSize));
            SetHeight(Dimension(ITEM_HEIGHT));
            ViewStackProcessor::GetInstance()->Pop();
        } else {
            SetWidth(Dimension(crossSize));
        }
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

testing::AssertionResult ListTestNg::VerifyItemPosition(
    int32_t expectCount, int32_t lanes, float interval, int32_t startIndex)
{
    if (lanes < 1) {
        return testing::AssertionFailure() << "lanes < 1";
    }
    auto itemPosition = pattern_->GetItemPosition();
    for (int32_t index = 0; index < expectCount; index++) {
        auto listItem = itemPosition[index + startIndex];
        float startPos = (index / lanes) * (ITEM_HEIGHT + interval);
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
    int32_t groupIndex, int32_t expectCount, int32_t lanes, float interval)
{
    if (lanes < 1) {
        return testing::AssertionFailure() << "lanes < 1";
    }
    auto itemPosition = GetGroupPattern(groupIndex)->GetItemPosition();
    for (int32_t index = 0; index < expectCount; index++) {
        auto listItem = itemPosition[index];
        float startPos = (index / lanes) * (ITEM_HEIGHT + interval);
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

testing::AssertionResult ListTestNg::IsEqualNextFocusNode(
    FocusStep step, int32_t currentIndex, int32_t nextIndex)
{
    RefPtr<FocusHub> currentFocusNode = GetChildFocusHub(currentIndex);
    currentFocusNode->RequestFocusImmediately();
    RefPtr<FocusHub> nextFocusNode = pattern_->GetNextFocusNode(step, currentFocusNode).Upgrade();
    if (nextIndex == -1 && nextFocusNode != nullptr) {
        return testing::AssertionFailure() << "Next FocusNode is not null.";
    }
    if (nextIndex != -1 && nextFocusNode != GetChildFocusHub(nextIndex)) {
        return testing::AssertionFailure() << "Get wrong next FocusNode.";
    }
    return testing::AssertionSuccess();
}

testing::AssertionResult ListTestNg::IsEqualCurrentOffset(Offset expectOffset)
{
    RunMeasureAndLayout();
    Offset currentOffset = pattern_->GetCurrentOffset();
    if (expectOffset == currentOffset) {
        return testing::AssertionSuccess();
    }
    return testing::AssertionFailure() <<
        "GetCurrentOffset(): " << currentOffset.ToString() <<
        " != " <<
        "expectOffset: " << expectOffset.ToString();
}

testing::AssertionResult ListTestNg::IsEqualRect(RectF rect, RectF expectRect)
{
    if (rect == expectRect) {
        return testing::AssertionSuccess();
    }
    return testing::AssertionFailure() <<
        "rect: " << rect.ToString() <<
        " != " <<
        "expectRect: " << expectRect.ToString();
}

testing::AssertionResult ListTestNg::VerifySwiperItemChildRect(
    RefPtr<FrameNode> listItem, std::vector<RectF> expectRects)
{
    size_t childrenSize = listItem->GetChildren().size();
    size_t expectRectsSize = expectRects.size();
    if (childrenSize != expectRectsSize) {
        return testing::AssertionFailure() <<
            "listItem children size:" << childrenSize <<
            " != " <<
            "expectRects size: " << expectRectsSize;
    }
    for (size_t index = 0; index < childrenSize; index++) {
        RectF rect = GetChildRect(listItem, index);
        if (rect != expectRects[index]) {
            return testing::AssertionFailure() <<
                "listItem child index: " << index <<
                ", rect: " << rect.ToString() <<
                " != " <<
                "expectRect: " << expectRects[index].ToString();
        }
    }
    return testing::AssertionSuccess();
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
}

void ListTestNg::MouseSelectRelease()
{
    MouseInfo info;
    info.SetButton(MouseButton::LEFT_BUTTON);
    info.SetAction(MouseAction::RELEASE);
    pattern_->HandleMouseEventWithoutKeyboard(info);
}

void ListTestNg::UpdateCurrentOffset(float offset)
{
    pattern_->UpdateCurrentOffset(offset, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout();
}

void ListTestNg::ScrollToTop()
{
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_TOP);
    RunMeasureAndLayout();
}

void ListTestNg::ScrollToBottom()
{
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM);
    RunMeasureAndLayout();
}

void ListTestNg::DragSwiperItem(int32_t index, GestureEvent info)
{
    auto itemPattern = GetItemPattern(index);
    itemPattern->HandleDragStart(info);
    itemPattern->HandleDragUpdate(info);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    RunMeasureAndLayout();
    // curOffset_ would be reset to 0/START_NODE_SIZE/END_NODE_SIZE by StartSpringMotion(),
    // but do not set, conducive to verification
    itemPattern->HandleDragEnd(info);
}

void ListTestNg::DragSwiperItem(int32_t index, float mainDelta, float mainVelocity)
{
    GestureEvent info;
    info.SetMainDelta(mainDelta);
    info.SetMainVelocity(mainVelocity);
    DragSwiperItem(index, info);
}

void ListTestNg::ListItemSwipeMoveAndLayout(const RefPtr<ListItemPattern>& itemPattern, float moveDelta)
{
    GestureEvent info;
    info.SetMainDelta(moveDelta);
    itemPattern->HandleDragUpdate(info);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    RunMeasureAndLayout();
}

uint64_t ListTestNg::GetActions()
{
    std::unordered_set<AceAction> supportAceActions = accessibilityProperty_->GetSupportAction();
    uint64_t actions = 0;
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    return actions;
}

/**
 * @tc.name: ListLayoutProperty001
 * @tc.desc: Test List layout properties.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListLayoutProperty001, TestSize.Level1)
{
    V2::ItemDivider itemDivider = V2::ItemDivider();
    itemDivider.strokeWidth = Dimension(10);
    itemDivider.startMargin = Dimension(5);
    itemDivider.endMargin = Dimension(5);
    itemDivider.color = Color(0x000000);

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetSpace(Dimension(10));
    listModelNG.SetInitialIndex(1);
    listModelNG.SetListDirection(Axis::VERTICAL);
    listModelNG.SetScrollBar(Ace::DisplayMode::ON);
    listModelNG.SetEditMode(true);
    listModelNG.SetChainAnimation(true);
    listModelNG.SetDivider(itemDivider);
    listModelNG.SetEdgeEffect(EdgeEffect::NONE);
    listModelNG.SetLanes(3);
    listModelNG.SetLaneMinLength(Dimension(40));
    listModelNG.SetLaneMaxLength(Dimension(60));
    listModelNG.SetListItemAlign(V2::ListItemAlign::CENTER);
    listModelNG.SetCachedCount(10);
    listModelNG.SetSticky(V2::StickyStyle::HEADER);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Call ToJsonValue()
     * @tc.expected: The json value is correct
     */
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json);
    EXPECT_EQ(Dimension::FromString(json->GetString("space")), Dimension(10));
    EXPECT_EQ(json->GetString("initialIndex"), "1");
    EXPECT_EQ(static_cast<Axis>(json->GetInt("listDirection")), Axis::VERTICAL);
    EXPECT_TRUE(json->GetBool("editMode"));
    EXPECT_TRUE(json->GetBool("chainAnimation"));
    auto dividerJson = json->GetObject("divider");
    EXPECT_EQ(Dimension::FromString(dividerJson->GetString("strokeWidth")), Dimension(10));
    EXPECT_EQ(Dimension::FromString(dividerJson->GetString("startMargin")), Dimension(5));
    EXPECT_EQ(Dimension::FromString(dividerJson->GetString("endMargin")), Dimension(5));
    EXPECT_EQ(Color::ColorFromString(dividerJson->GetString("color")), Color(0x000000));
    EXPECT_EQ(json->GetString("edgeEffect"), "EdgeEffect.None");
    EXPECT_EQ(json->GetString("lanes"), "3");
    EXPECT_EQ(Dimension::FromString(json->GetString("laneMinLength")), Dimension(40));
    EXPECT_EQ(Dimension::FromString(json->GetString("laneMaxLength")), Dimension(60));
    EXPECT_EQ(json->GetString("alignListItem"), "ListItemAlign.Center");
    EXPECT_EQ(json->GetString("cachedCount"), "10");
    EXPECT_EQ(json->GetString("sticky"), "StickyStyle.Header");

    /**
     * @tc.steps: step2. Change some property, Call ToJsonValue()
     * @tc.expected: The json value is correct
     */
    layoutProperty_->UpdateEdgeEffect(EdgeEffect::FADE);
    layoutProperty_->UpdateListItemAlign(V2::ListItemAlign::END);
    layoutProperty_->UpdateStickyStyle(V2::StickyStyle::FOOTER);
    json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json);
    EXPECT_EQ(json->GetString("edgeEffect"), "EdgeEffect.Fade");
    EXPECT_EQ(json->GetString("alignListItem"), "ListItemAlign.End");
    EXPECT_EQ(json->GetString("sticky"), "StickyStyle.Footer");

    /**
     * @tc.steps: step3. Change some property, Call ToJsonValue()
     * @tc.expected: The json value is changed
     */
    layoutProperty_->UpdateStickyStyle(V2::StickyStyle::BOTH);
    json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json);
    EXPECT_EQ(json->GetString("sticky"), "StickyStyle.Header | StickyStyle.Footer");

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
    CreateList(TOTAL_NUMBER);
    auto layoutProperty = GetChildFrameNode(0)->GetLayoutProperty<ListItemLayoutProperty>();

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
 * @tc.name: AttrSpace001
 * @tc.desc: Test property about space,
 * there is space between each ListItem
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrSpace001, TestSize.Level1)
{
    constexpr float space = 5.0f;

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetSpace(Dimension(space));
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_TRUE(VerifyItemPosition(VIEWPORT_NUMBER, 1, space));
}

/**
 * @tc.name: AttrSpace002
 * @tc.desc: Test property about space,
 * when space less than divider's strokeWidth, space was going to be strokeWidth
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrSpace002, TestSize.Level1)
{
    constexpr float space = 5.0f;
    constexpr float strokeWidth = 10.f;
    V2::ItemDivider itemDivider = V2::ItemDivider();
    itemDivider.strokeWidth = Dimension(strokeWidth);

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetSpace(Dimension(space));
    listModelNG.SetDivider(itemDivider);
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_TRUE(VerifyItemPosition(VIEWPORT_NUMBER, 1, strokeWidth));
}

/**
 * @tc.name: AttrInitIndex001
 * @tc.desc: Test property about initialIndex,
 * list layout starting from initialIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrInitIndex001, TestSize.Level1)
{
    constexpr int32_t initIndex = 1;

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetInitialIndex(initIndex);
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_TRUE(VerifyItemPosition(VIEWPORT_NUMBER, 1, 0, initIndex));
}

/**
 * @tc.name: AttrInitIndex002
 * @tc.desc: Test property about initialIndex,
 * total ListItem size less than viewport, List layout starting from first
 * ListItem.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrInitIndex002, TestSize.Level1)
{
    constexpr int32_t initIndex = 1;
    constexpr size_t itemCount = 5;

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetInitialIndex(initIndex);
    CreateListItem(itemCount);
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_TRUE(VerifyItemPosition(itemCount));
}

/**
 * @tc.name: AttrInitIndex003
 * @tc.desc: Test property about initialIndex,
 * The total size of ListItems after initialIndex is less than viewport, ListItem bottom to viewport.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrInitIndex003, TestSize.Level1)
{
    constexpr int32_t initIndex = 5;
    constexpr int32_t expectStartIndex = 2;

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetInitialIndex(initIndex);
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_TRUE(VerifyItemPosition(VIEWPORT_NUMBER, 1, 0, expectStartIndex));
}

/**
 * @tc.name: AttrInitIndex004
 * @tc.desc: Test property about initialIndex,
 * initialIndex out of range, ignore.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrInitIndex004, TestSize.Level1)
{
    constexpr int32_t initIndex = 100;

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetInitialIndex(initIndex);
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_TRUE(VerifyItemPosition(VIEWPORT_NUMBER));
}

/**
 * @tc.name: AttrInitIndex005
 * @tc.desc: Test property about initialIndex,
 * initialIndex is not an integer multiple of the lanes,
 * List layout starting from an index integer multiple of the lanes.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrInitIndex005, TestSize.Level1)
{
    constexpr int32_t initIndex = 3;
    constexpr int32_t lanes = 2;
    constexpr int32_t itemCount = 20;
    constexpr size_t expectItemCount = 16;
    constexpr int32_t expectStartIndex = 2;

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetInitialIndex(initIndex);
    listModelNG.SetLanes(lanes);
    CreateListItem(itemCount);
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_TRUE(VerifyItemPosition(expectItemCount, lanes, 0, expectStartIndex));
}

/**
 * @tc.name: AttrDivider001
 * @tc.desc: Test property about divider,
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrDivider001, TestSize.Level1)
{
    constexpr float strokeWidth = 4;
    constexpr float startMargin = 10;
    constexpr float endMargin = 20;
    const Color color = Color(0x000000);
    V2::ItemDivider itemDivider = V2::ItemDivider();
    itemDivider.strokeWidth = Dimension(strokeWidth);
    itemDivider.startMargin = Dimension(startMargin);
    itemDivider.endMargin = Dimension(endMargin);
    itemDivider.color = color;

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetDivider(itemDivider);
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_TRUE(VerifyItemPosition(VIEWPORT_NUMBER, 1, strokeWidth));
}

/**
 * @tc.name: AttrScrollBar001
 * @tc.desc: Test property about scrollBar,
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrScrollBar001, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    RefPtr<ScrollControllerBase> scrollController = listModelNG.CreateScrollController();
    RefPtr<ScrollProxy> proxy = AceType::MakeRefPtr<NG::ScrollBarProxy>();
    listModelNG.SetScroller(scrollController, proxy);
    listModelNG.SetScrollBar(Ace::DisplayMode::ON);
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout();

    RefPtr<ScrollBar> scrollBar = pattern_->GetScrollBar();
    ASSERT_NE(scrollBar, nullptr);
    EXPECT_EQ(scrollBar->GetDisplayMode(), DisplayMode::ON);
}

/**
 * @tc.name: AttrScrollBar002
 * @tc.desc: Test property about scrollBar,
 * when api version >= 10, the default value is auto
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrScrollBar002, TestSize.Level1)
{
    constexpr int32_t platformVersionTen = 10;

    ListModelNG listModelNG;
    listModelNG.Create();
    RefPtr<ScrollControllerBase> scrollController = listModelNG.CreateScrollController();
    listModelNG.SetScroller(scrollController, nullptr);
    MockPipelineBase::pipeline_->SetMinPlatformVersion(platformVersionTen);
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout();

    RefPtr<ScrollBar> scrollBar = pattern_->GetScrollBar();
    ASSERT_NE(scrollBar, nullptr);
    EXPECT_EQ(scrollBar->GetDisplayMode(), DisplayMode::AUTO);
}

/**
 * @tc.name: AttrLanes001
 * @tc.desc: Test property about lanes,
 * List layout as 2 lanes
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrLanes001, TestSize.Level1)
{
    constexpr int32_t lanes = 2;
    constexpr int32_t itemCount = 19;
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetLanes(lanes);
    CreateListItem(itemCount);
    GetInstance();
    RunMeasureAndLayout();

    int32_t expectItemCount = 16;
    int32_t expectLanes = 2;
    EXPECT_TRUE(VerifyItemPosition(expectItemCount, expectLanes, DEFAULT_INTERVAL, DEFAULT_STARTINDEX));

    ScrollToBottom();
    int32_t expectStartIndex = 4;
    expectItemCount = 15;
    EXPECT_TRUE(VerifyItemPosition(expectItemCount, expectLanes, DEFAULT_INTERVAL, expectStartIndex));

    ScrollToTop();
    EXPECT_TRUE(VerifyItemPosition(expectItemCount, expectLanes, DEFAULT_INTERVAL, DEFAULT_STARTINDEX));
}

/**
 * @tc.name: AttrLanes002
 * @tc.desc: Test LayoutProperty about minLaneLength, maxLaneLength,
 * List layout as 2 lanes.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrLanes002, TestSize.Level1)
{
    constexpr float minLaneLength = 220.f;
    constexpr float maxLaneLength = 480.f;
    constexpr int32_t itemCount = 19;

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetLaneMinLength(Dimension(minLaneLength));
    listModelNG.SetLaneMaxLength(Dimension(maxLaneLength));
    CreateListItem(itemCount);
    GetInstance();
    RunMeasureAndLayout();

    int32_t expectLanes = 2;
    int32_t expectItemCount = 16;
    EXPECT_TRUE(VerifyItemPosition(expectItemCount, expectLanes, DEFAULT_INTERVAL, DEFAULT_STARTINDEX));

    ScrollToBottom();
    int32_t expectStartIndex = 4;
    expectItemCount = 15;
    EXPECT_TRUE(VerifyItemPosition(expectItemCount, expectLanes, DEFAULT_INTERVAL, expectStartIndex));

    ScrollToTop();
    EXPECT_TRUE(VerifyItemPosition(expectItemCount, expectLanes, DEFAULT_INTERVAL, DEFAULT_STARTINDEX));

    /**
     * @tc.steps: step1. Check ListItem width.
     * @tc.expected: ListItem width would self-adaption.
     */
    for (int32_t index = 0; index < expectItemCount; index++) {
        float width = GetChildRect(frameNode_, index).Width();
        EXPECT_FLOAT_EQ(width, 240.f);
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
    constexpr float minLaneLength = 220.f;
    constexpr float maxLaneLength = 100.f;
    constexpr int32_t itemCount = 19;

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetLaneMinLength(Dimension(minLaneLength));
    listModelNG.SetLaneMaxLength(Dimension(maxLaneLength));
    CreateListItem(itemCount);
    GetInstance();
    RunMeasureAndLayout();

    int32_t expectItemCount = 16;
    int32_t expectLanes = 2;
    EXPECT_TRUE(VerifyItemPosition(expectItemCount, expectLanes));

    /**
     * @tc.steps: step1. Check ListItem width.
     * @tc.expected: ListItem width would be minLaneLength.
     */
    for (int32_t index = 0; index < expectItemCount; index++) {
        float width = GetChildRect(frameNode_, index).Width();
        EXPECT_FLOAT_EQ(width, minLaneLength);
    }
}

/**
 * @tc.name: AttrLanes004
 * @tc.desc: Test LayoutProperty about lanes with ListItemGroup,
 * ListItemGroup is unchanged, but ListItem would be affected by lanes
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrLanes004, TestSize.Level1)
{
    constexpr int32_t lanes = 2;
    constexpr int32_t groupNumber = 3; // set 3 group to make list scrollable

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetLanes(lanes);
    // each group has VIEWPORT_NUMBER listItem
    CreateListItemGroup(groupNumber);
    GetInstance();
    RunMeasureAndLayout();

    int32_t groupIndex_0 = 0;
    int32_t groupIndex_1 = 1;
    int32_t groupIndex_2 = 1;
    int32_t expectItemCount = 8;
    int32_t expectLanes = 2;
    EXPECT_TRUE(VerifyGroupItemPosition(groupIndex_0, expectItemCount, expectLanes));
    EXPECT_TRUE(VerifyGroupItemPosition(groupIndex_1, expectItemCount, expectLanes));
    EXPECT_TRUE(VerifyGroupItemPosition(groupIndex_2, expectItemCount, expectLanes));

    // test scroll
    ScrollToBottom();
    EXPECT_TRUE(VerifyGroupItemPosition(groupIndex_0, expectItemCount, expectLanes));
    EXPECT_TRUE(VerifyGroupItemPosition(groupIndex_1, expectItemCount, expectLanes));
    EXPECT_TRUE(VerifyGroupItemPosition(groupIndex_2, expectItemCount, expectLanes));

    ScrollToTop();
    EXPECT_TRUE(VerifyGroupItemPosition(groupIndex_0, expectItemCount, expectLanes));
    EXPECT_TRUE(VerifyGroupItemPosition(groupIndex_1, expectItemCount, expectLanes));
    EXPECT_TRUE(VerifyGroupItemPosition(groupIndex_2, expectItemCount, expectLanes));
}

/**
 * @tc.name: AttrLanes005
 * @tc.desc: Test LayoutProperty about minLength, maxLength with ListItemGroup,
 * when ListItemGroup width less than List, the columns of ListItem in group would not equal to outside
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrLanes005, TestSize.Level1)
{
    constexpr float minLaneLength = 220.f;
    constexpr float maxLaneLength = 480.f;
    constexpr int32_t groupWidth = 400.f;

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetLaneMinLength(Dimension(minLaneLength));
    listModelNG.SetLaneMaxLength(Dimension(maxLaneLength));

    ListItemGroupModelNG listItemGroupModel;
    listItemGroupModel.Create(V2::ListItemGroupStyle::NONE);
    SetWidth(Dimension(groupWidth));
    CreateListItem(VIEWPORT_NUMBER);
    ViewStackProcessor::GetInstance()->Pop();

    CreateListItem(VIEWPORT_NUMBER * 2);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Check ListItem in group.
     * @tc.expected: ListItem columns would be 1.
     */
    constexpr int32_t expectItemCount1 = 8;
    EXPECT_TRUE(VerifyGroupItemPosition(0, expectItemCount1));

    /**
     * @tc.steps: step2. Check ListItem out of group.
     * @tc.expected: ListItem columns would be 2.
     */
    ScrollToBottom();
    constexpr int32_t expectItemCount2 = VIEWPORT_NUMBER * 2;
    constexpr int32_t expectLanes2 = 2;
    constexpr int32_t expectStartIndex2 = 1;
    EXPECT_TRUE(VerifyItemPosition(expectItemCount2, expectLanes2, 0, expectStartIndex2));
}

/**
 * @tc.name: AttrLanes006
 * @tc.desc: Test LayoutProperty about laneGutter,
 * LaneGutter can be set correctly
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrLanes006, TestSize.Level1)
{
    constexpr Dimension laneGutter = 16.0_vp;
    constexpr int32_t lanes = 3;
    constexpr int32_t groupCount = 10;
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetLanes(lanes);
    listModelNG.SetLaneGutter(laneGutter);
    CreateListItemGroup(groupCount);
    GetInstance();
    RunMeasureAndLayout();

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto layoutProperty = frameNode->GetLayoutProperty<ListLayoutProperty>();

    EXPECT_EQ(laneGutter, layoutProperty->GetLaneGutter());
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

    ListModelNG listModelNG;
    listModelNG.Create();
    for (int32_t index = 0; index < TOTAL_NUMBER; index++) {
        ListItemModelNG listItemModel;
        listItemModel.Create();
        SetWidth(Dimension(itemWidth));
        ViewStackProcessor::GetInstance()->Pop();
    }
    GetInstance();
    RunMeasureAndLayout();

    for (int32_t index = 0; index < TOTAL_NUMBER; index++) {
        float offsetX = GetChildRect(frameNode_, index).GetX();
        EXPECT_EQ(offsetX, 0);
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

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetListItemAlign(V2::ListItemAlign::CENTER);
    for (int32_t index = 0; index < TOTAL_NUMBER; index++) {
        ListItemModelNG listItemModel;
        listItemModel.Create();
        SetWidth(Dimension(itemWidth));
        ViewStackProcessor::GetInstance()->Pop();
    }
    GetInstance();
    RunMeasureAndLayout();

    for (int32_t index = 0; index < TOTAL_NUMBER; index++) {
        float offsetX = GetChildRect(frameNode_, index).GetX();
        float expectOffsetX = (DEVICE_WIDTH - itemWidth) / 2;
        EXPECT_EQ(offsetX, expectOffsetX);
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

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetListItemAlign(V2::ListItemAlign::END);
    for (int32_t index = 0; index < TOTAL_NUMBER; index++) {
        ListItemModelNG listItemModel;
        listItemModel.Create();
        SetWidth(Dimension(itemWidth));
        ViewStackProcessor::GetInstance()->Pop();
    }
    GetInstance();
    RunMeasureAndLayout();

    for (int32_t index = 0; index < TOTAL_NUMBER; index++) {
        float offsetX = GetChildRect(frameNode_, index).GetX();
        float expectOffsetX = DEVICE_WIDTH - itemWidth;
        EXPECT_EQ(offsetX, expectOffsetX);
    }
}

/**
 * @tc.name: AttrSLECM001
 * @tc.desc: Test property about scroller/listDirection/edgeEffect/chainAnimation/multiSelectable
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrSLECM001, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    RefPtr<ScrollControllerBase> scrollController = listModelNG.CreateScrollController();
    RefPtr<ScrollProxy> proxy = AceType::MakeRefPtr<NG::ScrollBarProxy>();
    listModelNG.SetScroller(scrollController, proxy);
    listModelNG.SetListDirection(Axis::HORIZONTAL);
    listModelNG.SetEdgeEffect(EdgeEffect::SPRING);
    listModelNG.SetChainAnimation(true);
    listModelNG.SetMultiSelectable(true);
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_NE(pattern_->positionController_, nullptr);
    EXPECT_EQ(pattern_->GetAxis(), Axis::HORIZONTAL);
    EXPECT_NE(pattern_->GetScrollEdgeEffect(), nullptr);
    EXPECT_NE(pattern_->chainAnimation_, nullptr);
    EXPECT_TRUE(pattern_->multiSelectable_);
}

/**
 * @tc.name: ListItemAttrSwiperTest001
 * @tc.desc: Set startNode and SwipeEdgeEffect::None, List cannot swiper Left but can swiper right.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemAttrSwiperTest001, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    auto startFunc = GetDefaultSwiperBuilder(START_NODE_SIZE, false);
    CreateListItemWithSwiper(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. do nothing, verify rect.
     * @tc.expected: StartNode not load
     */
    int32_t listItemIndex = 0;
    auto listItem = GetChildFrameNode(listItemIndex);
    auto listItemPattern = GetItemPattern(listItemIndex);
    EXPECT_TRUE(VerifySwiperItemChildRect(listItem, {
        RectF(),
        RectF(0, 0, DEVICE_WIDTH, ITEM_HEIGHT),
    }));
    EXPECT_EQ(listItemPattern->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step2. Move item right to left
     * @tc.expected: Can not move, StartNode not load
     *  _____________________480
     * |_____________________|
     */
    DragSwiperItem(listItemIndex, -START_NODE_SIZE);
    EXPECT_TRUE(VerifySwiperItemChildRect(listItem, {
        RectF(),
        RectF(0, 0, DEVICE_WIDTH, ITEM_HEIGHT),
    }));
    EXPECT_EQ(listItemPattern->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step3. Move item left to right, distance < START_NODE_SIZE * SWIPER_TH
     * @tc.expected: Can move, StartNode loaded, but will reset curOffset_
     *  _20__________________480
     * |_|___________________|
     */
    DragSwiperItem(listItemIndex, START_NODE_SIZE * SWIPER_TH);
    EXPECT_TRUE(VerifySwiperItemChildRect(listItem, {
        RectF(-START_NODE_SIZE * (1.f - SWIPER_TH), 0, START_NODE_SIZE, ITEM_HEIGHT),
        RectF(START_NODE_SIZE * SWIPER_TH, 0, DEVICE_WIDTH, ITEM_HEIGHT),
    }));
    EXPECT_EQ(listItemPattern->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step4. move item left to right, distance > START_NODE_SIZE * SWIPER_TH
     * @tc.expected: change swiperIndex_ to SWIPER_START
     *  _21__________________480
     * |_|___________________|
     */
    const float delta = 1.f;
    DragSwiperItem(listItemIndex, delta);
    EXPECT_TRUE(VerifySwiperItemChildRect(listItem, {
        RectF(-START_NODE_SIZE * (1.f - SWIPER_TH) + delta, 0, START_NODE_SIZE, ITEM_HEIGHT),
        RectF(START_NODE_SIZE * SWIPER_TH + delta, 0, DEVICE_WIDTH, ITEM_HEIGHT),
    }));
    EXPECT_EQ(listItemPattern->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_START);

    /**
     * @tc.steps: step5. move item right to left
     * @tc.expected: change swiperIndex_ to ITEM_CHILD
     *  _20__________________480
     * |_|___________________|
     */
    DragSwiperItem(listItemIndex, -delta);
    EXPECT_TRUE(VerifySwiperItemChildRect(listItem, {
        RectF(-START_NODE_SIZE * (1.f - SWIPER_TH), 0, START_NODE_SIZE, ITEM_HEIGHT),
        RectF(START_NODE_SIZE * SWIPER_TH, 0, DEVICE_WIDTH, ITEM_HEIGHT),
    }));
    EXPECT_EQ(listItemPattern->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);
}

/**
 * @tc.name: ListItemAttrSwiperTest002
 * @tc.desc: Set startNode and SwipeEdgeEffect::None, List cannot swiper right but can swiper left.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemAttrSwiperTest002, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    auto endFunc = GetDefaultSwiperBuilder(END_NODE_SIZE, false);
    CreateListItemWithSwiper(nullptr, endFunc, V2::SwipeEdgeEffect::None);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. do nothing, verify rect.
     * @tc.expected: EndNode not load
     */
    int32_t listItemIndex = 0;
    auto listItem = GetChildFrameNode(listItemIndex);
    auto listItemPattern = GetItemPattern(listItemIndex);
    EXPECT_TRUE(VerifySwiperItemChildRect(listItem, {
        RectF(),
        RectF(0, 0, DEVICE_WIDTH, ITEM_HEIGHT),
    }));
    EXPECT_EQ(listItemPattern->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step2. Move item left to right
     * @tc.expected: Can not move, EndNode not load
     *  _____________________480
     * |_____________________|
     */
    DragSwiperItem(listItemIndex, END_NODE_SIZE);
    EXPECT_TRUE(VerifySwiperItemChildRect(listItem, {
        RectF(),
        RectF(0, 0, DEVICE_WIDTH, ITEM_HEIGHT),
    }));
    EXPECT_EQ(listItemPattern->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step3. Move item right to left, distance < END_NODE_SIZE * SWIPER_TH
     * @tc.expected: Can move, EndNode loaded
     *  _________________455_480
     * |_________________|___|
     */
    DragSwiperItem(listItemIndex, -END_NODE_SIZE * SWIPER_TH);
    EXPECT_TRUE(VerifySwiperItemChildRect(listItem, {
        RectF(DEVICE_WIDTH - END_NODE_SIZE * SWIPER_TH, 0, END_NODE_SIZE, ITEM_HEIGHT),
        RectF(-END_NODE_SIZE * SWIPER_TH, 0, DEVICE_WIDTH, ITEM_HEIGHT),
    }));
    EXPECT_EQ(listItemPattern->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step4. Move item right to left, distance > END_NODE_SIZE * SWIPER_TH
     * @tc.expected: change swiperIndex_ to SWIPER_END
     *  _________________454_480
     * |_________________|___|
     */
    const float delta = -1.f;
    DragSwiperItem(listItemIndex, delta);
    EXPECT_TRUE(VerifySwiperItemChildRect(listItem, {
        RectF(DEVICE_WIDTH - END_NODE_SIZE * SWIPER_TH + delta, 0, END_NODE_SIZE, ITEM_HEIGHT),
        RectF(-END_NODE_SIZE * SWIPER_TH + delta, 0, DEVICE_WIDTH, ITEM_HEIGHT),
    }));
    EXPECT_EQ(listItemPattern->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_END);

    /**
     * @tc.steps: step5. Move item left to right
     * @tc.expected: change swiperIndex_ to ITEM_CHILD
     *  _________________455_480
     * |_________________|___|
     */
    DragSwiperItem(listItemIndex, -delta);
    EXPECT_TRUE(VerifySwiperItemChildRect(listItem, {
        RectF(DEVICE_WIDTH - END_NODE_SIZE * SWIPER_TH, 0, END_NODE_SIZE, ITEM_HEIGHT),
        RectF(-END_NODE_SIZE * SWIPER_TH, 0, DEVICE_WIDTH, ITEM_HEIGHT),
    }));
    EXPECT_EQ(listItemPattern->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);
}

/**
 * @tc.name: ListItemAttrSwiperTest003
 * @tc.desc: Test swiperAction Attribute for ListItem, set startNode and endNode.
 * Drag the ListItem left or right with speed.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemAttrSwiperTest003, TestSize.Level1)
{
    auto builder = GetDefaultSwiperBuilder(START_NODE_SIZE, false);

    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItemWithSwiper(builder, builder, V2::SwipeEdgeEffect::Spring);
    GetInstance();
    RunMeasureAndLayout();

    int32_t listItemIndex = 0;
    auto listItem = GetChildFrameNode(listItemIndex);
    auto listItemPattern = GetItemPattern(listItemIndex);
    EXPECT_EQ(listItemPattern->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);

    DragSwiperItem(listItemIndex, 10.f, SWIPER_SPEED_TH + 1.f);
    auto itemPattern = GetItemPattern(0);
    EXPECT_EQ(itemPattern->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_START);

    DragSwiperItem(listItemIndex, -20.f, -SWIPER_SPEED_TH - 1.f);
    EXPECT_EQ(itemPattern->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);

    DragSwiperItem(listItemIndex, -10.f, -SWIPER_SPEED_TH - 1.f);
    EXPECT_EQ(itemPattern->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_END);
}

/**
 * @tc.name: ListItemAttrSwiperTest004
 * @tc.desc: Test swiperAction Attribute for ListItem, set startNode and endNode.
 * When switch ListItem to drag, the previous would be reset.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemAttrSwiperTest004, TestSize.Level1)
{
    auto builder = GetDefaultSwiperBuilder(START_NODE_SIZE, false);

    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItemWithSwiper(builder, builder, V2::SwipeEdgeEffect::Spring);
    CreateListItemWithSwiper(builder, builder, V2::SwipeEdgeEffect::Spring);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Drag first item to 30.
     * @tc.expected: The first item swiperIndex_ changed.
     */
    GestureEvent info;
    info.SetMainDelta(30.f);
    info.SetMainVelocity(1300.f);
    DragSwiperItem(0, info);
    auto firstItemPattern = GetItemPattern(0);
    EXPECT_EQ(firstItemPattern->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_START);
    EXPECT_FLOAT_EQ(firstItemPattern->springMotion_->GetCurrentVelocity(), 1300.f);

    /**
     * @tc.steps: step2. Drag second item to 30.
     * @tc.expected: The second item swiperIndex_ changed, and first item reseted.
     */
    DragSwiperItem(1, info);
    auto secondItemPattern = GetItemPattern(1);
    EXPECT_EQ(firstItemPattern->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);
    EXPECT_EQ(secondItemPattern->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_START);
    EXPECT_FLOAT_EQ(firstItemPattern->springMotion_->GetCurrentVelocity(), 1300.f);
    EXPECT_FLOAT_EQ(secondItemPattern->springMotion_->GetCurrentVelocity(), 1300.f);
}

/**
 * @tc.name: ListItemAttrSwiperTest005
 * @tc.desc: Set startNode and SwipeEdgeEffect::Spring, move friction take effect
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemAttrSwiperTest005, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    auto startFunc = GetDefaultSwiperBuilder(START_NODE_SIZE, false);
    CreateListItemWithSwiper(startFunc, nullptr, V2::SwipeEdgeEffect::Spring);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. When curOffset_ exceed listItem size(start + item), swipe left
     * @tc.expected: Move friction would take effect
     */
    constexpr int32_t listItemIndex = 0;
    auto listItem = GetChildFrameNode(listItemIndex);
    auto listItemPattern = GetItemPattern(listItemIndex);
    float curOffset = -1.f;
    // set curOffset_ to exceed listItem size
    listItemPattern->curOffset_ = curOffset;
    float moveDelta = -20.f;
    DragSwiperItem(listItemIndex, moveDelta);
    float friction = listItemPattern->CalculateFriction(-curOffset / DEVICE_WIDTH);
    float expOffsetX = friction * moveDelta + curOffset;
    EXPECT_TRUE(VerifySwiperItemChildRect(listItem, {
        RectF(),
        RectF(expOffsetX, 0, DEVICE_WIDTH, ITEM_HEIGHT),
    }));

    /**
     * @tc.steps: step2. When curOffset_ exceed listItem size(start + item), swipe right
     * @tc.expected: Move friction would take effect
     */
    curOffset = START_NODE_SIZE + 1.f;
    // set curOffset_ to exceed listItem size
    listItemPattern->curOffset_ = curOffset;
    moveDelta = 20.f;
    DragSwiperItem(listItemIndex, moveDelta);
    friction = listItemPattern->CalculateFriction(curOffset / DEVICE_WIDTH);
    expOffsetX = friction * moveDelta + curOffset;
    EXPECT_TRUE(VerifySwiperItemChildRect(listItem, {
        RectF(expOffsetX - START_NODE_SIZE, 0, START_NODE_SIZE, ITEM_HEIGHT),
        RectF(expOffsetX, 0, DEVICE_WIDTH, ITEM_HEIGHT),
    }));
}

/**
 * @tc.name: ListItemAttrSwiperTest006
 * @tc.desc: Set endNode and SwipeEdgeEffect::Spring, move friction take effect
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemAttrSwiperTest006, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    auto endFunc = GetDefaultSwiperBuilder(END_NODE_SIZE, false);
    CreateListItemWithSwiper(nullptr, endFunc, V2::SwipeEdgeEffect::Spring);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. When curOffset_ exceed listItem size(end + item), swipe right
     * @tc.expected: Move friction would take effect
     */
    constexpr int32_t listItemIndex = 0;
    auto listItem = GetChildFrameNode(listItemIndex);
    auto listItemPattern = GetItemPattern(listItemIndex);
    float curOffset = 1.f;
    // set curOffset_ to exceed listItem size
    listItemPattern->curOffset_ = curOffset;
    float moveDelta = 20.f;
    DragSwiperItem(listItemIndex, moveDelta);
    float friction = listItemPattern->CalculateFriction(curOffset / DEVICE_WIDTH);
    float expOffsetX = friction * moveDelta + curOffset;
    EXPECT_TRUE(VerifySwiperItemChildRect(listItem, {
        RectF(),
        RectF(expOffsetX, 0, DEVICE_WIDTH, ITEM_HEIGHT),
    }));

    /**
     * @tc.steps: step2. When curOffset_ exceed listItem size(end + item), swipe left
     * @tc.expected: Move friction would take effect
     */
    curOffset = -END_NODE_SIZE - 1.f;
    // set curOffset_ to exceed listItem size
    listItemPattern->curOffset_ = curOffset;
    moveDelta = -20.f;
    DragSwiperItem(listItemIndex, moveDelta);
    friction = listItemPattern->CalculateFriction(-curOffset / DEVICE_WIDTH);
    expOffsetX = friction * moveDelta + curOffset;
    EXPECT_TRUE(VerifySwiperItemChildRect(listItem, {
        RectF(expOffsetX + DEVICE_WIDTH, 0, END_NODE_SIZE, ITEM_HEIGHT),
        RectF(expOffsetX, 0, DEVICE_WIDTH, ITEM_HEIGHT),
    }));
}

/**
 * @tc.name: ListItemAttrSwiperTest008
 * @tc.desc: Set startNode, startDeleteArea, deleteAreaDistance SwipeEdgeEffect::None
 * List can swiper right great than START_NODE_SIZE
 * if great than START_NODE_SIZE + deleteAreaDistance,
 * it will adjust to START_NODE_SIZE + deleteAreaDistance
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemAttrSwiperTest008, TestSize.Level1)
{
    auto startFunc = GetDefaultSwiperBuilder(START_NODE_SIZE, false);
    CreateListItemWithSwipeActionItem(
        startFunc, true, nullptr, nullptr, nullptr, DELETE_AREA_DISTANCE, true, V2::SwipeEdgeEffect::None);

    /**
     * @tc.steps: step1. move right 80px, RunMeasureAndLayout and check result.
     * @tc.expected: startNode loaded, x position is 80px - START_NODE_SIZE
     */
    ListItemSwipeMoveAndLayout(GetItemPattern(0), MOVE_DELTA_80);
    auto listItem = GetChildFrameNode(0);
    EXPECT_TRUE(IsEqualRect(GetChildRect(listItem, 1), RectF(MOVE_DELTA_80, 0, DEVICE_WIDTH, ITEM_HEIGHT)));
    EXPECT_TRUE(IsEqualRect(GetChildRect(listItem, 0),
        RectF(MOVE_DELTA_80 - START_NODE_SIZE, 0, START_NODE_SIZE, ITEM_HEIGHT)));

    /**
     * @tc.steps: step2. continue move right 80px, RunMeasureAndLayout and check result.
     * @tc.expected: startNode loaded, x position is deleteAreaDistance, child node position is START_NODE_SIZE +
     * deleteAreaDistance
     */
    ListItemSwipeMoveAndLayout(GetItemPattern(0), MOVE_DELTA_80);
    const float deleteAreaDistance = DELETE_AREA_DISTANCE.ConvertToPx();
    EXPECT_TRUE(IsEqualRect(GetChildRect(listItem, 1),
        RectF(START_NODE_SIZE + deleteAreaDistance, 0, DEVICE_WIDTH, ITEM_HEIGHT)));
    EXPECT_TRUE(IsEqualRect(GetChildRect(listItem, 0),
        RectF(deleteAreaDistance, 0, START_NODE_SIZE, ITEM_HEIGHT)));
}

/**
 * @tc.name: ListItemAttrSwiperTest009
 * @tc.desc: Set the swiperAction Attribute for ListItem, set endNode, endDeleteArea, deleteAreaDistance and
 * EdgeEffect is none, List can swiper left great than endNode size, if great than endNode size +
 * deleteAreaDistance, it will adjust to endNode size + deleteAreaDistance
 *
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemAttrSwiperTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get frameNode and set SetSwiperAction for ListItem.
     */
    auto endFunc = GetDefaultSwiperBuilder(END_NODE_SIZE, false);

    CreateListItemWithSwipeActionItem(
        endFunc, true, nullptr, nullptr, nullptr, DELETE_AREA_DISTANCE, false, V2::SwipeEdgeEffect::None);

    /**
     * @tc.steps: step2. move left 100px, RunMeasureAndLayout and check result.
     * @tc.expected: endNode loaded, x position is DEVICE_WIDTH - 100px
     */
    ListItemSwipeMoveAndLayout(GetItemPattern(0), -MOVE_DELTA_100);
    auto listItem = GetChildFrameNode(0);
    EXPECT_TRUE(IsEqualRect(GetChildRect(listItem, 1), RectF(-MOVE_DELTA_100, 0, DEVICE_WIDTH, ITEM_HEIGHT)));
    EXPECT_TRUE(IsEqualRect(GetChildRect(listItem, 0),
        RectF(DEVICE_WIDTH - MOVE_DELTA_100, 0, END_NODE_SIZE, ITEM_HEIGHT)));

    /**
     * @tc.steps: step3. continue move left 100px, RunMeasureAndLayout and check result.
     * @tc.expected: endNode loaded, x position is DEVICE_WIDTH - endNodeSize - deleteAreaDistance, child node
     * position is endNodeSize + deleteAreaDistance
     */
    ListItemSwipeMoveAndLayout(GetItemPattern(0), -MOVE_DELTA_100);
    const float deleteAreaDistance = DELETE_AREA_DISTANCE.ConvertToPx();
    EXPECT_TRUE(IsEqualRect(GetChildRect(listItem, 1),
        RectF(-END_NODE_SIZE - deleteAreaDistance, 0, DEVICE_WIDTH, ITEM_HEIGHT)));
    EXPECT_TRUE(IsEqualRect(GetChildRect(listItem, 0),
        RectF(DEVICE_WIDTH - END_NODE_SIZE - deleteAreaDistance, 0, END_NODE_SIZE, ITEM_HEIGHT)));
}

/**
 * @tc.name: ListItemAttrSwiperTest010
 * @tc.desc: Test swiperAction Attribute for ListItem, set startNode, startDeleteArea, deleteAreaDistance and edge
 * effect is spring. move friction take effect when moving to the right distance great than startNode size +
 * deleteAreaDistance
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemAttrSwiperTest010, TestSize.Level1)
{
    auto startFunc = GetDefaultSwiperBuilder(START_NODE_SIZE, true);
    CreateListItemWithSwipeActionItem(
        startFunc, true, nullptr, nullptr, nullptr, DELETE_AREA_DISTANCE, true, V2::SwipeEdgeEffect::Spring);

    /**
     * @tc.steps: step1. moving to the right distance great than startNode size + deleteAreaDistance, check startNode
     * position.
     */
    ListItemSwipeMoveAndLayout(GetItemPattern(0), MOVE_DELTA_100);
    ListItemSwipeMoveAndLayout(GetItemPattern(0), MOVE_DELTA_20);
    auto factor = ListItemPattern::CalculateFriction(MOVE_DELTA_20 / (DEVICE_WIDTH - START_NODE_SIZE));
    float expOffsetX = factor * MOVE_DELTA_20 + MOVE_DELTA_100;
    auto listItem = GetChildFrameNode(0);
    EXPECT_TRUE(IsEqualRect(GetChildRect(listItem, 1), RectF(expOffsetX, 0, DEVICE_WIDTH, ITEM_HEIGHT)));
    EXPECT_TRUE(IsEqualRect(GetChildRect(listItem, 0), RectF(0, 0, expOffsetX, ITEM_HEIGHT)));
}

/**
 * @tc.name: ListItemAttrSwiperTest011
 * @tc.desc: Test swiperAction Attribute for ListItem, set endNode, endDeleteArea, deleteAreaDistance and edge
 * effect is spring. move friction take effect when moving to the left distance great than endNode size +
 * deleteAreaDistance
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemAttrSwiperTest011, TestSize.Level1)
{
    auto endFunc = GetDefaultSwiperBuilder(END_NODE_SIZE, true);
    CreateListItemWithSwipeActionItem(
        endFunc, true, nullptr, nullptr, nullptr, DELETE_AREA_DISTANCE, false, V2::SwipeEdgeEffect::Spring);

    /**
     * @tc.steps: step1. moving to the left distance great than endNode size + deleteAreaDistance, check startNode
     * position.
     */
    ListItemSwipeMoveAndLayout(GetItemPattern(0), -MOVE_DELTA_100 - MOVE_DELTA_20);
    ListItemSwipeMoveAndLayout(GetItemPattern(0), -MOVE_DELTA_20);
    auto factor = ListItemPattern::CalculateFriction(MOVE_DELTA_20 / (DEVICE_WIDTH - END_NODE_SIZE));
    float expOffsetX = factor * -MOVE_DELTA_20 - MOVE_DELTA_100 - MOVE_DELTA_20;
    auto listItem = GetChildFrameNode(0);
    EXPECT_TRUE(IsEqualRect(GetChildRect(listItem, 1), RectF(expOffsetX, 0, DEVICE_WIDTH, ITEM_HEIGHT)));
    EXPECT_TRUE(IsEqualRect(GetChildRect(listItem, 0),
        RectF(DEVICE_WIDTH + expOffsetX, 0, -expOffsetX, ITEM_HEIGHT)));
}

/**
 * @tc.name: ListItemAttrSwiperTest012
 * @tc.desc: Test swiperAction Attribute for ListItem, set enterStartDeleteArea callback and exitStartDeleteArea
 * callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemAttrSwiperTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get frameNode and set SetSwiperAction for ListItem.
     */
    auto builder = GetDefaultSwiperBuilder(START_NODE_SIZE, false);

    bool isEnterStartDeleteAreaCalled = false;
    bool isExitStartDeleteAreaCalled = false;
    auto enterStartDeleteArea = [&isEnterStartDeleteAreaCalled]() { isEnterStartDeleteAreaCalled = true; };
    auto exitStartDeleteArea = [&isExitStartDeleteAreaCalled]() { isExitStartDeleteAreaCalled = true; };
    CreateListItemWithSwipeActionItem(builder, true, nullptr, enterStartDeleteArea, exitStartDeleteArea,
        DELETE_AREA_DISTANCE, true, V2::SwipeEdgeEffect::Spring);

    /**
     * @tc.steps: step2. moving to the right distance great than startNode size + deleteAreaDistance, check
     * enterStartDeleteArea callback.
     */
    auto itemPattern = GetItemPattern(0);
    ListItemSwipeMoveAndLayout(itemPattern, MOVE_DELTA_80);
    ListItemSwipeMoveAndLayout(itemPattern, DELETE_AREA_DISTANCE.ConvertToPx());
    ListItemSwipeMoveAndLayout(itemPattern, MOVE_DELTA_20);
    EXPECT_TRUE(isEnterStartDeleteAreaCalled);

    /**
     * @tc.steps: step3. moving to the left distance less than startNode size + deleteAreaDistance, check
     * exitStartDeleteArea callback.
     */
    ListItemSwipeMoveAndLayout(itemPattern, -MOVE_DELTA_80);
    EXPECT_TRUE(isExitStartDeleteAreaCalled);
}

/**
 * @tc.name: ListItemAttrSwiperTest013
 * @tc.desc: Test swiperAction Attribute for ListItem, set enterEndDeleteArea callback and exitEndDeleteArea
 * callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemAttrSwiperTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get frameNode and set SetSwiperAction for ListItem.
     */
    auto builder = GetDefaultSwiperBuilder(END_NODE_SIZE, false);

    bool isEnterEndDeleteAreaCalled = false;
    bool isExitEndDeleteAreaCalled = false;
    auto enterEndDeleteArea = [&isEnterEndDeleteAreaCalled]() { isEnterEndDeleteAreaCalled = true; };
    auto exitEndDeleteArea = [&isExitEndDeleteAreaCalled]() { isExitEndDeleteAreaCalled = true; };
    CreateListItemWithSwipeActionItem(builder, true, nullptr, enterEndDeleteArea, exitEndDeleteArea,
        DELETE_AREA_DISTANCE, false, V2::SwipeEdgeEffect::Spring);

    /**
     * @tc.steps: step2. moving to the left distance great than endNode size + deleteAreaDistance, check
     * enterEndDeleteArea callback.
     */
    auto itemPattern = GetItemPattern(0);
    ListItemSwipeMoveAndLayout(itemPattern, -MOVE_DELTA_100);
    ListItemSwipeMoveAndLayout(itemPattern, -DELETE_AREA_DISTANCE.ConvertToPx());
    ListItemSwipeMoveAndLayout(itemPattern, -MOVE_DELTA_20);
    EXPECT_TRUE(isEnterEndDeleteAreaCalled);

    /**
     * @tc.steps: step3. moving to the right distance less than endNode size + deleteAreaDistance, check
     * exitEndDeleteArea callback.
     */
    ListItemSwipeMoveAndLayout(itemPattern, MOVE_DELTA_100);
    EXPECT_TRUE(isExitEndDeleteAreaCalled);
}

/**
 * @tc.name: ListItemAttrSwiperTest014
 * @tc.desc: Test swiperAction Attribute for ListItem, set deleteArea, deleteAreaDistance and onDeleteCallBack, Drag the
 * ListItem left or right to obtain the correct SwipeIndex.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemAttrSwiperTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get frameNode and set SetSwiperAction for ListItem.
     */
    auto builder = GetDefaultSwiperBuilder(START_NODE_SIZE, false);

    bool isStartOnDeleteCalled = false;
    auto startOnDelete = [&isStartOnDeleteCalled]() { isStartOnDeleteCalled = true; };
    CreateListItemWithSwipeActionItem(
        builder, true, startOnDelete, nullptr, nullptr, DELETE_AREA_DISTANCE, true, V2::SwipeEdgeEffect::Spring);

    /**
     * @tc.steps: step2. moving to the right distance great than startNode size + deleteAreaDistance, check
     * SwipeIndex.
     */
    auto itemPattern = GetItemPattern(0);
    ListItemSwipeMoveAndLayout(itemPattern, MOVE_DELTA_80);
    ListItemSwipeMoveAndLayout(itemPattern, DELETE_AREA_DISTANCE.ConvertToPx());
    ListItemSwipeMoveAndLayout(itemPattern, MOVE_DELTA_20);
    GestureEvent info;
    itemPattern->HandleDragEnd(info);
    EXPECT_EQ(itemPattern->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_START);

    /**
     * @tc.steps: step3. moving to the left distance great than endNode size + deleteAreaDistance, check
     * SwipeIndex.
     */
    ListItemSwipeMoveAndLayout(itemPattern, -MOVE_DELTA_80);
    ListItemSwipeMoveAndLayout(itemPattern, -DELETE_AREA_DISTANCE.ConvertToPx());
    ListItemSwipeMoveAndLayout(itemPattern, -MOVE_DELTA_20);
    ListItemSwipeMoveAndLayout(itemPattern, -MOVE_DELTA_80);
    ListItemSwipeMoveAndLayout(itemPattern, -DELETE_AREA_DISTANCE.ConvertToPx());
    ListItemSwipeMoveAndLayout(itemPattern, -MOVE_DELTA_20);
    itemPattern->HandleDragEnd(info);
    EXPECT_EQ(itemPattern->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_START);
}

/**
 * @tc.name: ListItemGroupSpaceTest001
 * @tc.desc: ListItemGroup set the Space attribute. There is a space between ListItems
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemGroupSpaceTest001, TestSize.Level1)
{
    constexpr float space = 5.0f;
    constexpr int32_t itemCount = 5;

    ListModelNG listModelNG;
    listModelNG.Create();
    ListItemGroupModelNG listItemGroupModel;
    listItemGroupModel.Create(V2::ListItemGroupStyle::NONE);
    listItemGroupModel.SetSpace(Dimension(space));
    CreateListItem(itemCount);
    ViewStackProcessor::GetInstance()->Pop();
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_TRUE(VerifyGroupItemPosition(0, itemCount, 1, space));
}

/**
 * @tc.name: ListItemGroupHeaderFooterTest001
 * @tc.desc: ListItemGroup set the header and footer
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemGroupHeaderFooterTest001, TestSize.Level1)
{
    constexpr int32_t itemCount = 5;
    auto header = GetDefaultHeaderBuilder();
    auto footer = GetDefaultHeaderBuilder();

    /**
     * @tc.steps: step1. create List/ListItemGroup/ListItem.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    ListItemGroupModelNG listItemGroupModel;
    listItemGroupModel.Create(V2::ListItemGroupStyle::NONE);
    listItemGroupModel.SetHeader(std::move(header));
    listItemGroupModel.SetFooter(std::move(footer));
    CreateListItem(itemCount);
    ViewStackProcessor::GetInstance()->Pop();
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. RunMeasureAndLayout and check ListItem position.
     */
    auto itemPosition = GetGroupPattern(0)->GetItemPosition();
    EXPECT_EQ(itemPosition.size(), static_cast<size_t>(itemCount));
    for (int32_t index = 0; index < itemCount; index++) {
        EXPECT_FLOAT_EQ(itemPosition[index].first, (index * ITEM_HEIGHT) + HEADER_MAIN_LENGTH);
        EXPECT_FLOAT_EQ(itemPosition[index].second, ((index + 1) * ITEM_HEIGHT) + HEADER_MAIN_LENGTH);
    }
    auto group = GetChildFrameNode(0);
    EXPECT_FLOAT_EQ(GetChildRect(group, 0).GetY(), 0.0f);
    EXPECT_FLOAT_EQ(GetChildRect(group, 1).GetY(), 550.f);
}

/**
 * @tc.name: ListItemGroupHeaderFooterTest002
 * @tc.desc: ListItemGroup set the header and footer, List set sticky header and footer
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemGroupHeaderFooterTest002, TestSize.Level1)
{
    constexpr float itemHeight = 750.f;
    auto header = GetDefaultHeaderBuilder();
    auto footer = GetDefaultHeaderBuilder();

    /**
     * @tc.steps: step1. create List/ListItemGroup/ListItem.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetSticky(V2::StickyStyle::BOTH);
    // Create ListItem
    ListItemModelNG listItemModel1;
    listItemModel1.Create();
    SetHeight(Dimension(itemHeight));
    SetWidth(FILL_LENGTH);
    ViewStackProcessor::GetInstance()->Pop();
    // Create ListItemGroup
    ListItemGroupModelNG listItemGroupModel;
    listItemGroupModel.Create(V2::ListItemGroupStyle::NONE);
    listItemGroupModel.SetHeader(std::move(header));
    listItemGroupModel.SetFooter(std::move(footer));
    CreateListItem(4);
    ViewStackProcessor::GetInstance()->Pop();
    // Create ListItem
    ListItemModelNG listItemModel2;
    listItemModel2.Create();
    SetHeight(Dimension(itemHeight));
    SetWidth(FILL_LENGTH);
    ViewStackProcessor::GetInstance()->Pop();
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. RunMeasureAndLayout and check ListItemGroup footer position.
     * @tc.expected: footer is sticky under header
     */
    auto itemGroupFrameNode = GetChildFrameNode(1);
    EXPECT_FLOAT_EQ(GetChildRect(frameNode_, 1).GetY(), itemHeight);
    EXPECT_FLOAT_EQ(GetChildRect(itemGroupFrameNode, 0).GetY(), 0.0f);
    EXPECT_FLOAT_EQ(GetChildRect(itemGroupFrameNode, 1).GetY(), 50.f);

    /**
     * @tc.steps: step3. Scroll 250px, RunMeasureAndLayout and check ListItemGroup footer position.
     * @tc.expected: header is sticky at bottom of List
     */
    UpdateCurrentOffset(-250.f);
    EXPECT_FLOAT_EQ(GetChildRect(frameNode_, 1).GetY(), 500.f);
    EXPECT_FLOAT_EQ(GetChildRect(itemGroupFrameNode, 0).GetY(), 0.0f);
    EXPECT_FLOAT_EQ(GetChildRect(itemGroupFrameNode, 1).GetY(), 250.f);

    /**
     * @tc.steps: step4. Scroll 700px, RunMeasureAndLayout and check ListItemGroup footer position.
     * @tc.expected: header is sticky at to of List
     */
    UpdateCurrentOffset(-700.f);
    EXPECT_FLOAT_EQ(GetChildRect(frameNode_, 1).GetY(), -200.f);
    EXPECT_FLOAT_EQ(GetChildRect(itemGroupFrameNode, 0).GetY(), 200.f);
    EXPECT_FLOAT_EQ(GetChildRect(itemGroupFrameNode, 1).GetY(), 450.f);

    /**
     * @tc.steps: step4. Scroll 250px, RunMeasureAndLayout and check ListItemGroup footer position.
     * @tc.expected: header is sticky upper footer
     */
    UpdateCurrentOffset(-250.f);
    EXPECT_FLOAT_EQ(GetChildRect(frameNode_, 1).GetY(), -450.f);
    EXPECT_FLOAT_EQ(GetChildRect(itemGroupFrameNode, 0).GetY(), 400.f);
    EXPECT_FLOAT_EQ(GetChildRect(itemGroupFrameNode, 1).GetY(), 450.f);
}

/**
 * @tc.name: ListItemGroupHeaderFooterTest003
 * @tc.desc: ListItemGroup set the header and footer with null
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemGroupHeaderFooterTest003, TestSize.Level1)
{
    constexpr int32_t itemCount = 5;

    ListModelNG listModelNG;
    listModelNG.Create();
    ListItemGroupModelNG listItemGroupModel;
    listItemGroupModel.Create(V2::ListItemGroupStyle::NONE);
    listItemGroupModel.SetHeader(nullptr);
    listItemGroupModel.SetFooter(nullptr);
    CreateListItem(itemCount);
    ViewStackProcessor::GetInstance()->Pop();
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Has no head and foot.
     * @tc.expected: Children count is ListItem count.
     */
    size_t expectCount = 1;
    EXPECT_EQ(frameNode_->GetChildren().size(), expectCount);
}

/**
 * @tc.name: ListItemGroupHeaderFooterTest004
 * @tc.desc: ListItemGroup set divider, space
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemGroupHeaderFooterTest004, TestSize.Level1)
{
    constexpr float space = 10.f;
    constexpr float strokeWidth = 4.f;
    constexpr float startMargin = 10.f;
    constexpr float endMargin = 20.f;
    const Color color = Color(0x000000);
    V2::ItemDivider itemDivider = V2::ItemDivider();
    itemDivider.strokeWidth = Dimension(strokeWidth);
    itemDivider.startMargin = Dimension(startMargin);
    itemDivider.endMargin = Dimension(endMargin);
    itemDivider.color = color;

    ListModelNG listModelNG;
    listModelNG.Create();

    ListItemGroupModelNG listItemGroupModel1;
    listItemGroupModel1.Create(V2::ListItemGroupStyle::NONE);
    listItemGroupModel1.SetDivider(itemDivider);
    listItemGroupModel1.SetSpace(Dimension(space));
    CreateListItem(VIEWPORT_NUMBER);
    ViewStackProcessor::GetInstance()->Pop();

    // empty listItem
    ListItemGroupModelNG listItemGroupModel2;
    listItemGroupModel2.Create(V2::ListItemGroupStyle::NONE);
    listItemGroupModel2.SetDivider(itemDivider);
    ViewStackProcessor::GetInstance()->Pop();

    GetInstance();
    RunMeasureAndLayout();

    EXPECT_TRUE(VerifyGroupItemPosition(0, VIEWPORT_NUMBER, 1, space));
}

/**
 * @tc.name: ListItemGroupHeaderFooterTest005
 * @tc.desc: ListItemGroup OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemGroupHeaderFooterTest005, TestSize.Level1)
{
    constexpr float space = 10.f;
    constexpr float strokeWidth = 4.f;
    constexpr float startMargin = 10.f;
    constexpr float endMargin = 20.f;
    const Color color = Color(0x000000);
    V2::ItemDivider itemDivider = V2::ItemDivider();
    itemDivider.strokeWidth = Dimension(strokeWidth);
    itemDivider.startMargin = Dimension(startMargin);
    itemDivider.endMargin = Dimension(endMargin);
    itemDivider.color = color;

    ListModelNG listModelNG;
    listModelNG.Create();
    ListItemGroupModelNG listItemGroupModel;
    listItemGroupModel.Create(V2::ListItemGroupStyle::NONE);
    listItemGroupModel.SetDivider(itemDivider);
    listItemGroupModel.SetSpace(Dimension(space));
    CreateListItem(VIEWPORT_NUMBER);
    ViewStackProcessor::GetInstance()->Pop();
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_TRUE(VerifyGroupItemPosition(0, VIEWPORT_NUMBER, 1, space));

    auto group = frameNode_->GetChildAtIndex(0);
    auto groupFrameNode = AceType::DynamicCast<FrameNode>(group);
    auto layoutWrapper = groupFrameNode->CreateLayoutWrapper(false, false);
    auto itemGroupPattern = groupFrameNode->GetPattern<ListItemGroupPattern>();
    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = true;
    EXPECT_FALSE(itemGroupPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));

    config.skipMeasure = false;
    config.skipLayout = false;
    EXPECT_FALSE(itemGroupPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));

    config.skipMeasure = true;
    config.skipLayout = false;
    EXPECT_FALSE(itemGroupPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));

    config.skipMeasure = false;
    config.skipLayout = true;
    EXPECT_FALSE(itemGroupPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
}

/**
 * @tc.name: ListItemGroupLayoutTest001
 * @tc.desc: ListItemGroup forward layout, stop layout when ListItem out of viewport
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemGroupLayoutTest001, TestSize.Level1)
{
    constexpr int32_t itemCount = 10;
    constexpr size_t expectItemCount = 9;

    ListModelNG listModelNG;
    listModelNG.Create();
    ListItemGroupModelNG listItemGroupModel;
    listItemGroupModel.Create(V2::ListItemGroupStyle::NONE);
    CreateListItem(itemCount);
    ViewStackProcessor::GetInstance()->Pop();
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. RunMeasureAndLayout and check ListItem position.
     */
    auto itemPosition = GetGroupPattern(0)->GetItemPosition();
    EXPECT_EQ(itemPosition.size(), expectItemCount);
    for (size_t index = 0; index < expectItemCount; index++) {
        EXPECT_FLOAT_EQ(itemPosition[index].first, (index * ITEM_HEIGHT));
        EXPECT_FLOAT_EQ(itemPosition[index].second, ((index + 1) * ITEM_HEIGHT));
    }
}

/**
 * @tc.name: ListItemGroupLayoutTest002
 * @tc.desc: ListItemGroup backward layout, stop layout when ListItem out of viewport
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemGroupLayoutTest002, TestSize.Level1)
{
    constexpr int32_t itemCount = 10;
    constexpr size_t expectItemCount = 8;

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetInitialIndex(1);
    ListItemGroupModelNG listItemGroupModel;
    listItemGroupModel.Create(V2::ListItemGroupStyle::NONE);
    CreateListItem(itemCount);
    ViewStackProcessor::GetInstance()->Pop();
    CreateListItem(1);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. RunMeasureAndLayout and check ListItem position.
     */
    auto itemPosition = GetGroupPattern(0)->GetItemPosition();
    auto offset = GetGroupPattern(0)->GetHostFrameOffset();
    constexpr float ITEM_GROUP_OFFSET = -100.f;
    EXPECT_FLOAT_EQ(offset->GetY(), ITEM_GROUP_OFFSET);
    constexpr int32_t ITEM_START = 2;
    EXPECT_EQ(itemPosition.size(), expectItemCount);
    for (size_t index = ITEM_START; index < itemCount; index++) {
        EXPECT_FLOAT_EQ(itemPosition[index].first, ((index - ITEM_START) * ITEM_HEIGHT));
        EXPECT_FLOAT_EQ(itemPosition[index].second, ((index - ITEM_START + 1) * ITEM_HEIGHT));
    }
}

/**
 * @tc.name: Callback001
 * @tc.desc: Test scroll callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Callback001, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    bool isScrollCalled = false;
    bool isScrollIndexCalled = false;
    bool isReachStartCalled = false;
    bool isReachEndCalled = false;
    auto scroll = [&isScrollCalled](Dimension, ScrollState) { isScrollCalled = true; };
    auto scrollIndex = [&isScrollIndexCalled](int32_t, int32_t, int32_t) { isScrollIndexCalled = true; };
    auto reachStart = [&isReachStartCalled]() { isReachStartCalled = true; };
    auto reachEnd = [&isReachEndCalled]() { isReachEndCalled = true; };
    listModelNG.SetOnScroll(scroll);
    listModelNG.SetOnScrollIndex(scrollIndex);
    listModelNG.SetOnReachStart(reachStart);
    listModelNG.SetOnReachEnd(reachEnd);
    CreateListItem(10);
    GetInstance();
    RunMeasureAndLayout();

    constexpr float scrollUpOffset = ITEM_HEIGHT;
    constexpr float scrollDownOffset = -ITEM_HEIGHT;

    /**
     * @tc.steps: step1. Scroll up 100px.
     * @tc.expected: Callback is called.
     */
    UpdateCurrentOffset(scrollUpOffset);
    EXPECT_TRUE(isScrollIndexCalled);

    /**
     * @tc.steps: step1. Scroll down 100px.
     * @tc.expected: Callback is called.
     */
    pattern_->UpdateCurrentOffset(scrollDownOffset, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout();
    EXPECT_TRUE(isScrollIndexCalled);

    /**
     * @tc.steps: step2. Scroll up 100px.
     * @tc.expected: Callback is called.
     */
    isScrollCalled = false;
    pattern_->UpdateCurrentOffset(scrollUpOffset, SCROLL_FROM_ANIMATION);
    RunMeasureAndLayout();
    EXPECT_TRUE(isScrollCalled);
    EXPECT_TRUE(isReachStartCalled);

    /**
     * @tc.steps: step3. Scroll down 100px.
     * @tc.expected: Callback is called.
     */
    isScrollCalled = false;
    pattern_->UpdateCurrentOffset(scrollDownOffset, SCROLL_FROM_ANIMATION_SPRING);
    RunMeasureAndLayout();
    EXPECT_TRUE(isScrollCalled);

    /**
     * @tc.steps: step3. Scroll up 100px.
     * @tc.expected: Callback is called.
     */
    isScrollCalled = false;
    pattern_->UpdateCurrentOffset(scrollUpOffset, SCROLL_FROM_NONE);
    RunMeasureAndLayout();
    EXPECT_TRUE(isScrollCalled);

    /**
     * @tc.steps: step3. Scroll down 200px.
     * @tc.expected: Callback is called.
     */
    UpdateCurrentOffset(scrollDownOffset * 2);
    EXPECT_TRUE(isReachEndCalled);

    UpdateCurrentOffset(scrollDownOffset);
    EXPECT_TRUE(isReachEndCalled);
}

/**
 * @tc.name: Callback002
 * @tc.desc: Verify onScrollStart, onScrollStop callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Callback002, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetChainAnimation(true);
    listModelNG.SetChainAnimationOptions(
        { Dimension(0), Dimension(10), 0, 0, 0, DEFAULT_STIFFNESS, DEFAULT_DAMPING });
    bool isScrollStartCalled = false;
    bool isScrollStopCalled = false;
    auto scrollStart = [&isScrollStartCalled]() { isScrollStartCalled = true; };
    auto scrollStop = [&isScrollStopCalled]() { isScrollStopCalled = true; };
    listModelNG.SetOnScrollStart(scrollStart);
    listModelNG.SetOnScrollStop(scrollStop);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Call func.
     * @tc.expected: The callback is called.
     */
    pattern_->OnScrollCallback(100.f, SCROLL_FROM_START);
    EXPECT_TRUE(isScrollStartCalled);

    pattern_->OnScrollEndCallback();
    RunMeasureAndLayout();
    EXPECT_TRUE(isScrollStopCalled);

    pattern_->OnScrollCallback(100.f, SCROLL_FROM_UPDATE);
}

/**
 * @tc.name: Callback004
 * @tc.desc: Test other condition
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Callback004, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetOnScrollBegin([](Dimension, Dimension) {
        ScrollInfo info;
        return info;
    });
    listModelNG.SetOnScrollFrameBegin([](Dimension, ScrollState) {
        ScrollFrameResult result;
        return result;
    });
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Get jumpIndex_.
     * @tc.expected: The jumpIndex_ is changed.
     */
    auto scrollableEvent = pattern_->GetScrollableEvent();
    ASSERT_NE(scrollableEvent, nullptr);
    EXPECT_NE(scrollableEvent->GetScrollBeginCallback(), nullptr);
    EXPECT_NE(scrollableEvent->GetScrollFrameBeginCallback(), nullptr);
    RunMeasureAndLayout();
}

/**
 * @tc.name: Drag001
 * @tc.desc: Verify onItemDragStart, onItemDragEnter, onItemDragMove, onItemDragLeave, onItemDrop callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Drag001, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItem(10);
    bool isItemDragStartCalled = false;
    auto itemDragStart = [&isItemDragStartCalled](const ItemDragInfo&, int32_t) {
        isItemDragStartCalled = true;
        auto dragItem = AceType::MakeRefPtr<FrameNode>("test", 0, AceType::MakeRefPtr<Pattern>());
        return dragItem;
    };
    listModelNG.SetOnItemDragStart(itemDragStart);
    listModelNG.SetOnItemDragEnter([](const ItemDragInfo&) {});
    listModelNG.SetOnItemDragLeave([](const ItemDragInfo&, int32_t) {});
    listModelNG.SetOnItemDragMove([](const ItemDragInfo&, int32_t, int32_t) {});
    listModelNG.SetOnItemDrop([](const ItemDragInfo&, int32_t, int32_t, bool) {});
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Trigger HandleOnItemDragStart.
     * @tc.expected: Verify some values of the drag.
     */
    GestureEvent info;
    Point globalPoint = Point(200.f, 150.f); // Point at the second item.
    info.SetGlobalPoint(globalPoint);
    eventHub_->HandleOnItemDragStart(info);
    EXPECT_TRUE(isItemDragStartCalled);
    EXPECT_EQ(eventHub_->draggedIndex_, 1);
    EXPECT_NE(eventHub_->dragDropProxy_, nullptr);

    /**
     * @tc.steps: step2. Trigger HandleOnItemDragUpdate and HandleOnItemDragEnd.
     * @tc.expected: Verify some values of the drag.
     */
    eventHub_->HandleOnItemDragUpdate(info);
    eventHub_->HandleOnItemDragEnd(info);
    EXPECT_EQ(eventHub_->draggedIndex_, 0);
    EXPECT_EQ(eventHub_->dragDropProxy_, nullptr);

    /**
     * @tc.steps: step3. Trigger HandleOnItemDragStart, HandleOnItemDragUpdate and HandleOnItemDragCancel.
     * @tc.expected: Verify some values of the drag.
     */
    eventHub_->HandleOnItemDragStart(info);
    eventHub_->HandleOnItemDragUpdate(info);
    eventHub_->HandleOnItemDragCancel();
    EXPECT_EQ(eventHub_->draggedIndex_, 0);
    EXPECT_EQ(eventHub_->dragDropProxy_, nullptr);
}

/**
 * @tc.name: EventHub001
 * @tc.desc: Test ListItem Event func
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, EventHub001, TestSize.Level1)
{
    CreateList(TOTAL_NUMBER);

    /**
     * @tc.steps: step1. Run GetDragExtraParams func.
     * @tc.expected: Verify return value.
     */
    auto itemFrameNode = GetChildFrameNode(0);
    auto itemEventHub = itemFrameNode->GetEventHub<ListItemEventHub>();
    auto jsonStr = itemEventHub->GetDragExtraParams("", Point(0, 200.f), DragEventType::START);
    EXPECT_NE(jsonStr, "");
    jsonStr = itemEventHub->GetDragExtraParams("info", Point(0, 200.f), DragEventType::MOVE);
    EXPECT_NE(jsonStr, "");
}

/**
 * @tc.name: EventHub002
 * @tc.desc: Test List Event func
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, EventHub002, TestSize.Level1)
{
    CreateList(TOTAL_NUMBER);

    /**
     * @tc.steps: step1. Run GetDragExtraParams func.
     * @tc.expected: Would call pattern->GetItemIndexByPosition
     */
    auto jsonStr = eventHub_->GetDragExtraParams("", Point(0, 0), DragEventType::MOVE);
    EXPECT_EQ(jsonStr, "{\"insertIndex\":0}");
}

/**
 * @tc.name: MouseSelect001
 * @tc.desc: Test mouse click to select, only PRESS and RELEASE the mouse
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, MouseSelect001, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetMultiSelectable(true);
    CreateListItem(9);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Click the (0, 0) point of firstItem.
     * @tc.expected: Can not select by click, the item is not selected.
     */
    MouseSelect(Offset(0.f, 0.f), Offset(0.f, 0.f));
    EXPECT_FALSE(GetItemPattern(0)->IsSelected());
}

/**
 * @tc.name: MouseSelect002
 * @tc.desc: Test mouse box selection, PRESS, MOVE and RELEASE the mouse
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, MouseSelect002, TestSize.Level1)
{
    const Offset LEFT_TOP = Offset(120.f, 250.f);
    const Offset LEFT_BOTTOM = Offset(120.f, 350.f);
    const Offset RIGHT_TOP = Offset(360.f, 250.f);
    const Offset RIGHT_BOTTOM = Offset(360.f, 350.f);

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetMultiSelectable(true);
    CreateListItem(9);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Select (0, 0) - (200, 100) zone.
     * @tc.expected: The 1st and 2nd items are selected.
     */
    MouseSelect(Offset(0.f, 0.f), Offset(200.f, 100.f));
    EXPECT_TRUE(GetItemPattern(0)->IsSelected());
    EXPECT_TRUE(GetItemPattern(1)->IsSelected());
    MouseSelectRelease();
    GetItemPattern(0)->MarkIsSelected(false);
    GetItemPattern(1)->MarkIsSelected(false);

    /**
     * @tc.steps: step2. Select (120, 150) - (360, 250) zone, from the LEFT_TOP to the RIGHT_BOTTOM.
     * @tc.expected: The 3rd and 4th are selected.
     */
    MouseSelect(LEFT_TOP, RIGHT_BOTTOM);
    EXPECT_TRUE(GetItemPattern(2)->IsSelected());
    EXPECT_TRUE(GetItemPattern(3)->IsSelected());
    MouseSelectRelease();
    GetItemPattern(2)->MarkIsSelected(false);
    GetItemPattern(3)->MarkIsSelected(false);

    /**
     * @tc.steps: step3. Select (120, 150) - (360, 250) zone, from the RIGHT_TOP to the LEFT_BOTTOM.
     * @tc.expected: The 3rd and 4th are selected.
     */
    MouseSelect(RIGHT_TOP, LEFT_BOTTOM);
    EXPECT_TRUE(GetItemPattern(2)->IsSelected());
    EXPECT_TRUE(GetItemPattern(3)->IsSelected());
    MouseSelectRelease();
    GetItemPattern(2)->MarkIsSelected(false);
    GetItemPattern(3)->MarkIsSelected(false);

    /**
     * @tc.steps: step4. Select (120, 150) - (360, 250) zone, from the LEFT_BOTTOM to the RIGHT_TOP.
     * @tc.expected: The 3rd and 4th are selected.
     */
    MouseSelect(LEFT_BOTTOM, RIGHT_TOP);
    EXPECT_TRUE(GetItemPattern(2)->IsSelected());
    EXPECT_TRUE(GetItemPattern(3)->IsSelected());
    MouseSelectRelease();
    GetItemPattern(2)->MarkIsSelected(false);
    GetItemPattern(3)->MarkIsSelected(false);

    /**
     * @tc.steps: step5. Select (120, 150) - (360, 250) zone, from the RIGHT_BOTTOM to the LEFT_TOP.
     * @tc.expected: The 3rd and 4th are selected.
     */
    MouseSelect(RIGHT_BOTTOM, LEFT_TOP);
    EXPECT_TRUE(GetItemPattern(2)->IsSelected());
    EXPECT_TRUE(GetItemPattern(3)->IsSelected());
    MouseSelectRelease();
    GetItemPattern(2)->MarkIsSelected(false);
    GetItemPattern(3)->MarkIsSelected(false);
}

/**
 * @tc.name: MouseSelect003
 * @tc.desc: Test listItem selectable property and onSelect callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, MouseSelect003, TestSize.Level1)
{
    constexpr int32_t itemCount = 9;

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetMultiSelectable(true);

    /**
     * @tc.steps: step1. Create listItem and set an unselectable.
     */
    bool isFifthItemSelected = false;
    auto selectCallback = [&isFifthItemSelected](bool) { isFifthItemSelected = true; };
    for (int32_t index = 0; index < itemCount; index++) {
        ListItemModelNG listItemModel;
        listItemModel.Create();
        SetHeight(Dimension(ITEM_HEIGHT));
        SetWidth(FILL_LENGTH);
        if (index == 3) {
            listItemModel.SetSelectable(false);
        }
        if (index == 4) {
            listItemModel.SetSelectCallback(std::move(selectCallback));
        }
        ViewStackProcessor::GetInstance()->Pop();
    }
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. Select (120, 250) - (360, 350) zone.
     * @tc.expected: The 4th item is not selected but 5th item is selected.
     */
    MouseSelect(Offset(120.f, 350.f), Offset(360.f, 450.f));
    EXPECT_FALSE(GetItemPattern(3)->IsSelected());
    EXPECT_TRUE(GetItemPattern(4)->IsSelected());
    EXPECT_TRUE(isFifthItemSelected);
}

/**
 * @tc.name: MouseSelect004
 * @tc.desc: Test listItem selectable about other condition
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, MouseSelect004, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetMultiSelectable(true);
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Use RIGHT_BUTTON to select.
     * @tc.expected: Nothing selected.
     */
    MouseInfo info;
    info.SetButton(MouseButton::RIGHT_BUTTON);
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(Offset(0, 0));
    pattern_->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(Offset(200.f, 100.f));
    pattern_->HandleMouseEventWithoutKeyboard(info);
    // Nothing selected
    for (int32_t index = 0; index < VIEWPORT_NUMBER; index++) {
        EXPECT_FALSE(GetItemPattern(index)->IsSelected()) << "Index: " << index;
    }

    /**
     * @tc.steps: step2. Use LEFT_BUTTON, but with MouseAction::HOVER to select.
     * @tc.expected: Nothing selected.
     */
    info.SetButton(MouseButton::LEFT_BUTTON);
    info.SetAction(MouseAction::HOVER);
    info.SetLocalLocation(Offset(0, 0));
    pattern_->HandleMouseEventWithoutKeyboard(info);
    // Nothing selected
    for (int32_t index = 0; index < VIEWPORT_NUMBER; index++) {
        EXPECT_FALSE(GetItemPattern(index)->IsSelected()) << "Index: " << index;
    }
}

/**
 * @tc.name: AccessibilityProperty001
 * @tc.desc: Test List AccessibilityProperty func
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AccessibilityProperty001, TestSize.Level1)
{
    CreateList(TOTAL_NUMBER);

    /**
     * @tc.steps: step1. Run accessibilityProperty func.
     * @tc.expected: Verify return value.
     */
    EXPECT_TRUE(accessibilityProperty_->IsScrollable());
    EXPECT_EQ(accessibilityProperty_->GetBeginIndex(), 0);
    EXPECT_EQ(accessibilityProperty_->GetCurrentIndex(), 0);
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), 7);
    EXPECT_EQ(accessibilityProperty_->GetCollectionItemCounts(), 10);
}

/**
 * @tc.name: AccessibilityProperty002
 * @tc.desc: Test List SetSpecificSupportAction when scroll to middle
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AccessibilityProperty002, TestSize.Level1)
{
    CreateList(TOTAL_NUMBER);

    /**
     * @tc.steps: step1. Scroll to Top.
     * @tc.expected: Verify return value.
     */
    accessibilityProperty_->ResetSupportAction();
    uint64_t exptectActions_1 = 0;
    exptectActions_1 |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    EXPECT_EQ(GetActions(), exptectActions_1);

    /**
     * @tc.steps: step2. Scroll to middle.
     * @tc.expected: Verify return value.
     */
    UpdateCurrentOffset(-ITEM_HEIGHT);
    accessibilityProperty_->ResetSupportAction();
    uint64_t exptectActions_2 = 0;
    exptectActions_2 |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    exptectActions_2 |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    EXPECT_EQ(GetActions(), exptectActions_2);

    /**
     * @tc.steps: step3. Scroll to bottom.
     * @tc.expected: Verify return value.
     */
    UpdateCurrentOffset(-ITEM_HEIGHT);
    accessibilityProperty_->ResetSupportAction();
    uint64_t exptectActions_3 = 0;
    exptectActions_3 |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    EXPECT_EQ(GetActions(), exptectActions_3);

    /**
     * @tc.steps: step4. UnScrollable List.
     * @tc.expected: Verify return value.
     */
    CreateList(8);
    accessibilityProperty_->ResetSupportAction();
    uint64_t exptectActions_4 = 0;
    EXPECT_EQ(GetActions(), exptectActions_4);
}

/**
 * @tc.name: AccessibilityProperty006
 * @tc.desc: Test ListItem AccessibilityProperty func
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AccessibilityProperty006, TestSize.Level1)
{
    CreateList(TOTAL_NUMBER);

    /**
     * @tc.steps: step1. Call IsSelected.
     * @tc.expected: Verify return value.
     */
    auto itemFrameNode = GetChildFrameNode(1);
    auto itemAccessibilityProperty = itemFrameNode->GetAccessibilityProperty<ListItemAccessibilityProperty>();
    EXPECT_FALSE(itemAccessibilityProperty->IsSelected());

    /**
     * @tc.steps: step2. Call SetSpecificSupportAction.
     * @tc.expected: Verify return value.
     */
    itemAccessibilityProperty->ResetSupportAction();
    uint64_t actions = 0, exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SELECT);
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_CLEAR_SELECTION);
    std::unordered_set<AceAction> supportAceActions = itemAccessibilityProperty->GetSupportAction();
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, exptectActions);
}

/**
 * @tc.name: AccessibilityProperty007
 * @tc.desc: Test ListItemGroup AccessibilityProperty func
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AccessibilityProperty007, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    ListItemGroupModelNG listItemGroupModel;
    listItemGroupModel.Create(V2::ListItemGroupStyle::NONE);
    CreateListItem(4);
    ViewStackProcessor::GetInstance()->Pop();
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. When group has ListItem
     * @tc.expected: GetBeginIndex() and GetEndIndex() can get correct index
     */
    auto groupFrameNode = GetChildFrameNode(0);
    auto groupAccessibilityProperty = groupFrameNode->GetAccessibilityProperty<ListItemGroupAccessibilityProperty>();
    EXPECT_EQ(groupAccessibilityProperty->GetBeginIndex(), 0);
    EXPECT_EQ(groupAccessibilityProperty->GetEndIndex(), 3);

    /**
     * @tc.steps: step1. When group has no ListItem
     * @tc.expected: GetBeginIndex() and GetEndIndex() return -1
     */
    auto groupPattern = GetGroupPattern(0);
    groupPattern->itemPosition_.clear();
    EXPECT_EQ(groupAccessibilityProperty->GetBeginIndex(), -1);
    EXPECT_EQ(groupAccessibilityProperty->GetEndIndex(), -1);
}

/**
 * @tc.name: PositionController001
 * @tc.desc: Test PositionController function with Axis::VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, PositionController001, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    RefPtr<ScrollControllerBase> scroller = listModelNG.CreateScrollController();
    listModelNG.SetScroller(scroller, nullptr);
    CreateListItem(10);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Get positionController and set scroll_.
     */
    auto controller = pattern_->positionController_;
    controller->scroll_ = AceType::WeakClaim(AceType::RawPtr(pattern_));

    /**
     * @tc.steps: step2. Call func.
     */
    EXPECT_EQ(controller->GetScrollDirection(), Axis::VERTICAL);

    controller->ScrollBy(50.f, 100.f, true);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, 100.f)));

    controller->ScrollPage(false, true);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, 200.f)));
    controller->ScrollPage(true, true);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, 0)));

    Offset currentOffset = controller->GetCurrentOffset();
    EXPECT_EQ(currentOffset, Offset(0, 0));

    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    EXPECT_EQ(pattern_->jumpIndex_, -1);
    EXPECT_EQ(pattern_->scrollAlign_, ScrollAlign::END);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, true);
    EXPECT_EQ(pattern_->jumpIndex_, 0);
    EXPECT_EQ(pattern_->scrollAlign_, ScrollAlign::START);

    controller->JumpTo(1, false, ScrollAlign::START, -1);
    EXPECT_EQ(pattern_->jumpIndex_, 1);

    EXPECT_FALSE(controller->AnimateTo(Dimension(1, DimensionUnit::PERCENT), 0, nullptr, false));
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 0, nullptr, false));
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 1, nullptr, false));
}

/**
 * @tc.name: PositionController002
 * @tc.desc: Test PositionController function with Axis::HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, PositionController002, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetListDirection(Axis::HORIZONTAL);
    RefPtr<ScrollControllerBase> scroller = listModelNG.CreateScrollController();
    listModelNG.SetScroller(scroller, nullptr);
    CreateListItem(10, Axis::HORIZONTAL);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Get positionController and set scroll_.
     */
    auto controller = pattern_->positionController_;
    controller->scroll_ = AceType::WeakClaim(AceType::RawPtr(pattern_));

    /**
     * @tc.steps: step2. Call func.
     */
    EXPECT_EQ(controller->GetScrollDirection(), Axis::HORIZONTAL);

    controller->ScrollBy(50.f, 100.f, true);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(50.f, 0)));

    controller->ScrollPage(false, true);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(120.f, 0)));
    controller->ScrollPage(true, true);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, 0)));

    Offset currentOffset = controller->GetCurrentOffset();
    EXPECT_EQ(currentOffset, Offset(0, 0));

    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    EXPECT_EQ(pattern_->jumpIndex_, -1);
    EXPECT_EQ(pattern_->scrollAlign_, ScrollAlign::END);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, true);
    EXPECT_EQ(pattern_->jumpIndex_, 0);
    EXPECT_EQ(pattern_->scrollAlign_, ScrollAlign::START);

    controller->JumpTo(1, false, ScrollAlign::START, -1);
    EXPECT_EQ(pattern_->jumpIndex_, 1);

    EXPECT_FALSE(controller->AnimateTo(Dimension(1, DimensionUnit::PERCENT), 0, nullptr, false));
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 0, nullptr, false));
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 1, nullptr, false));
}

/**
 * @tc.name: PositionController003
 * @tc.desc: Test PositionController function with Axis::NONE
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, PositionController003, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetListDirection(Axis::NONE);
    RefPtr<ScrollControllerBase> scroller = listModelNG.CreateScrollController();
    listModelNG.SetScroller(scroller, nullptr);
    CreateListItem(10);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Get positionController and set scroll_.
     */
    auto controller = pattern_->positionController_;
    controller->scroll_ = AceType::WeakClaim(AceType::RawPtr(pattern_));

    /**
     * @tc.steps: step2. Call func.
     */
    EXPECT_EQ(controller->GetScrollDirection(), Axis::NONE);

    controller->ScrollBy(50.f, 100.f, true);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, 50.f)));

    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    EXPECT_EQ(pattern_->jumpIndex_, std::nullopt);

    controller->ScrollPage(false, true);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, 50.f)));

    controller->JumpTo(1, false, ScrollAlign::START, -1);
    EXPECT_EQ(pattern_->jumpIndex_, 1);

    EXPECT_FALSE(controller->AnimateTo(Dimension(1, DimensionUnit::PERCENT), 0, nullptr, false));
}

/**
 * @tc.name: FocusStep001
 * @tc.desc: Test GetNextFocusNode func
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, FocusStep001, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItem(8, Axis::VERTICAL, true); // Create focusable ListItem.
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. GetNextFocusNode from top.
     * @tc.expected: Verify all condition of FocusStep.
     */
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, 0, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, 0, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, 0, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, 0, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, 0, 7));

    /**
     * @tc.steps: step2. GetNextFocusNode from middle.
     * @tc.expected: Verify all condition of FocusStep.
     */
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, 4, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, 4, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, 4, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, 4, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, 4, 7));

    /**
     * @tc.steps: step3. GetNextFocusNode from bottom.
     * @tc.expected: Verify all condition of FocusStep.
     */
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, 7, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, 7, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, 7, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, 7, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, 7, -1));
}

/**
 * @tc.name: FocusStep002
 * @tc.desc: Test GetNextFocusNode func in HORIZONTAL List
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, FocusStep002, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetListDirection(Axis::HORIZONTAL); // HORIZONTAL List.
    CreateListItem(8, Axis::HORIZONTAL, true); // Create focusable ListItem.
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. GetNextFocusNode from top.
     * @tc.expected: Verify all condition of FocusStep.
     */
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, 0, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, 0, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, 0, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, 0, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, 0, 7));

    /**
     * @tc.steps: step2. GetNextFocusNode from middle.
     * @tc.expected: Verify all condition of FocusStep.
     */
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, 4, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, 4, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, 4, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, 4, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, 4, 7));

    /**
     * @tc.steps: step3. GetNextFocusNode from bottom.
     * @tc.expected: Verify all condition of FocusStep.
     */
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, 7, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, 7, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, 7, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, 7, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, 7, -1));
}

/**
 * @tc.name: FocusStep003
 * @tc.desc: Test GetNextFocusNode func when List has unfocuseable item
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, FocusStep003, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItem(8, Axis::VERTICAL, true); // Create focusable ListItem.
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. GetNextFocusNode from 1st item and FocusStep::DOWN.
     * @tc.expected: The 3rd item is focused.
     */
    GetChildFocusHub(1)->SetFocusable(false); // The 2nd item can not focus.
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, 0, 2));
}

/**
 * @tc.name: FocusStep004
 * @tc.desc: Test GetNextFocusNode func from top boundary item
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, FocusStep004, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItem(10, Axis::VERTICAL, true); // Create focusable ListItem.
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Scroll to 150
     */
    constexpr float scrollOffset = -ITEM_HEIGHT - 1.f;
    UpdateCurrentOffset(scrollOffset);

    /**
     * @tc.steps: step2. UP to 1st item from 2nd item.
     */
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, 1, 0));
    EXPECT_EQ(pattern_->jumpIndex_, 0);
}

/**
 * @tc.name: FocusStep005
 * @tc.desc: Test GetNextFocusNode func from bottom boundary item
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, FocusStep005, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItem(10, Axis::VERTICAL, true); // Create focusable ListItem.
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Scroll to 99
     */
    constexpr float scrollOffset = -ITEM_HEIGHT + 1.f;
    UpdateCurrentOffset(scrollOffset);

    /**
     * @tc.steps: step2. DOWN to 10th item from 9th item.
     */
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, 8, -1));
    EXPECT_EQ(pattern_->jumpIndex_, 9);
}

/**
 * @tc.name: KeyEvent001
 * @tc.desc: Test list_pattern OnKeyEvent function
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, KeyEvent001, TestSize.Level1)
{
    CreateList(TOTAL_NUMBER);

    /**
     * @tc.steps: step1. Test other KeyEvent.
     * @tc.expected: CurrentOffset unchanged.
     */
    pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_UNKNOWN, KeyAction::UNKNOWN));
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, 0)));
    pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_UNKNOWN, KeyAction::DOWN));
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, 0)));

    /**
     * @tc.steps: step2. Test active KeyEvent.
     * @tc.expected: CurrentOffset changed.
     */
    pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_PAGE_DOWN, KeyAction::DOWN));
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, 200.f)));
    pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_PAGE_UP, KeyAction::DOWN));
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, 0)));
}

/**
 * @tc.name: PaintMethod001
 * @tc.desc: Test List paint method
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, PaintMethod001, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetChainAnimation(true);
    RefPtr<ScrollControllerBase> scrollController = listModelNG.CreateScrollController();
    listModelNG.SetScroller(scrollController, nullptr);
    GetInstance();
    RunMeasureAndLayout();

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

    EXPECT_TRUE(true);
}

/**
 * @tc.name: PaintMethod002
 * @tc.desc: Test List paint method
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, PaintMethod002, TestSize.Level1)
{
    V2::ItemDivider itemDivider = V2::ItemDivider();
    itemDivider.strokeWidth = Dimension(10.f);

    ListModelNG listModelNG;
    listModelNG.Create();
    RefPtr<ScrollControllerBase> scrollController = listModelNG.CreateScrollController();
    listModelNG.SetScroller(scrollController, nullptr);
    listModelNG.SetScrollBar(Ace::DisplayMode::ON);
    listModelNG.SetDivider(itemDivider);
    CreateListItemGroup(3);
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout();

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
    auto renderContext = frameNode_->GetRenderContext();
    renderContext->UpdateClipEdge(false);
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty_);
    listPaint->UpdateContentModifier(&paintWrapper);
    listPaint->PaintScrollBar(canvas);

    modifier->onDraw(ctx);

    EXPECT_TRUE(true);
}

/**
 * @tc.name: PaintMethod003
 * @tc.desc: Test List paint method
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, PaintMethod003, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    RefPtr<ScrollControllerBase> scrollController = listModelNG.CreateScrollController();
    listModelNG.SetScroller(scrollController, nullptr);
    listModelNG.SetScrollBar(Ace::DisplayMode::ON);
    V2::ItemDivider itemDivider = V2::ItemDivider();
    itemDivider.strokeWidth = Dimension(10.f);
    listModelNG.SetDivider(itemDivider);
    listModelNG.SetListDirection(Axis::HORIZONTAL);
    listModelNG.SetLanes(2);
    CreateListItemGroup(3);
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout();

    RefPtr<NodePaintMethod> paint = pattern_->CreateNodePaintMethod();
    RefPtr<ListPaintMethod> listPaint = AceType::DynamicCast<ListPaintMethod>(paint);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper paintWrapper(nullptr, geometryNode, paintProperty_);
    listPaint->UpdateContentModifier(&paintWrapper);
    RSCanvas canvas;
    listPaint->PaintScrollBar(canvas);

    auto modifier = pattern_->listContentModifier_;
    DrawingContext ctx = { canvas, 1, 1};
    modifier->onDraw(ctx);

    EXPECT_TRUE(true);
}

/**
 * @tc.name: PaintMethod004
 * @tc.desc: Test ListItemGroup paint method
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, PaintMethod004, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    ListItemGroupModelNG listItemGroupModelNG;
    listItemGroupModelNG.Create(V2::ListItemGroupStyle::NONE);
    CreateListItem(TOTAL_NUMBER);
    ViewStackProcessor::GetInstance()->Pop();
    GetInstance();
    RunMeasureAndLayout();

    auto groupFrameNode = GetChildFrameNode(0);
    auto groupPattern = groupFrameNode->GetPattern<ListItemGroupPattern>();

    RefPtr<NodePaintMethod> paint = groupPattern->CreateNodePaintMethod();
    RefPtr<ListItemGroupPaintMethod> groupPaint = AceType::DynamicCast<ListItemGroupPaintMethod>(paint);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper paintWrapper(nullptr, geometryNode, paintProperty_);
    RSCanvas canvas;
    groupPaint->PaintDivider(&paintWrapper, canvas);

    V2::ItemDivider itemDivider = V2::ItemDivider();
    itemDivider.strokeWidth = Dimension(10.f);
    groupPaint->divider_ = itemDivider;
    groupPaint->PaintDivider(&paintWrapper, canvas);

    groupPaint->lanes_ = 2;
    groupPaint->PaintDivider(&paintWrapper, canvas);

    groupPaint->vertical_ = true;
    groupPaint->PaintDivider(&paintWrapper, canvas);

    EXPECT_TRUE(true);
}

/**
 * @tc.name: Pattern001
 * @tc.desc: Test list_pattern OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern001, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetMultiSelectable(true);
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout();

    pattern_->OnModifyDone();
    EXPECT_TRUE(pattern_->isMouseEventInit_);
    EXPECT_TRUE(pattern_->isInitialized_);
    EXPECT_TRUE(pattern_->GetScrollableEvent());
}

/**
 * @tc.name: Pattern002
 * @tc.desc: Test list_pattern AnimateTo function
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern002, TestSize.Level1)
{
    CreateList(TOTAL_NUMBER);

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
 * @tc.desc: Test CreateNodePaintMethod
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern003, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    RefPtr<ScrollControllerBase> scrollController = listModelNG.CreateScrollController();
    listModelNG.SetScroller(scrollController, nullptr);
    listModelNG.SetEdgeEffect(EdgeEffect::FADE);
    GetInstance();
    RunMeasureAndLayout();

    auto paint = pattern_->CreateNodePaintMethod();
    RefPtr<ListPaintMethod> listPaint = AceType::DynamicCast<ListPaintMethod>(paint);
    EXPECT_EQ(listPaint->edgeEffect_.Upgrade(), pattern_->GetScrollEdgeEffect());
}

/**
 * @tc.name: Pattern004
 * @tc.desc: Test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern004, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    auto layoutWrapper = RunMeasureAndLayout();

    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = false;
    pattern_->isScrollEnd_ = true;
    EXPECT_TRUE(pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
}

/**
 * @tc.name: Pattern005
 * @tc.desc: Test SetChainAnimationOptions
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern005, TestSize.Level1)
{
    constexpr float space = 5.f;
    constexpr float minSpace = 10.f;
    constexpr float maxSpace = 2.f;
    constexpr float conductivity = 5.f;
    constexpr float intensity = 5.f;

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetSpace(Dimension(space));
    listModelNG.SetChainAnimation(true);
    listModelNG.SetChainAnimationOptions(
        { Dimension(minSpace), Dimension(maxSpace), conductivity, intensity, 0, DEFAULT_STIFFNESS, DEFAULT_DAMPING });
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout();

    ChainAnimationOptions options = {
        .minSpace = Dimension(minSpace),
        .maxSpace = Dimension(maxSpace),
        .conductivity = conductivity,
        .intensity = intensity,
        .edgeEffect = 0,
        .stiffness = DEFAULT_STIFFNESS,
        .damping = DEFAULT_DAMPING,
    };
    pattern_->SetChainAnimationOptions(options);

    /**
     * @tc.steps: step1. When minSpace > maxSpace.
     * @tc.expected: minSpace and maxSpace would be space.
     */
    const auto chainAnimation = pattern_->chainAnimation_;
    EXPECT_FLOAT_EQ(chainAnimation->minSpace_, space);
    EXPECT_FLOAT_EQ(chainAnimation->maxSpace_, space);

    /**
     * @tc.steps: step2. When conductivity > 1.
     * @tc.expected: conductivity would be default value.
     */
    EXPECT_FLOAT_EQ(chainAnimation->conductivity_, ChainAnimation::DEFAULT_CONDUCTIVITY);

    /**
     * @tc.steps: step3. When intensity > 1.
     * @tc.expected: conductivity would be default value.
     */
    EXPECT_FLOAT_EQ(chainAnimation->intensity_, ChainAnimation::DEFAULT_INTENSITY);
}

/**
 * @tc.name: Pattern006
 * @tc.desc: Test SetChainAnimationOptions
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern006, TestSize.Level1)
{
    constexpr float space = 5.f;
    constexpr float minSpace = 2.f;
    constexpr float maxSpace = 10.f;
    constexpr float conductivity = -5.f;
    constexpr float intensity = -5.f;

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetSpace(Dimension(space));
    listModelNG.SetChainAnimation(true);
    listModelNG.SetChainAnimationOptions(
        { Dimension(minSpace), Dimension(maxSpace), conductivity, intensity, 0, DEFAULT_STIFFNESS, DEFAULT_DAMPING });
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout();

    ChainAnimationOptions options = {
        .minSpace = Dimension(minSpace),
        .maxSpace = Dimension(maxSpace),
        .conductivity = conductivity,
        .intensity = intensity,
        .edgeEffect = 0,
        .stiffness = DEFAULT_STIFFNESS,
        .damping = DEFAULT_DAMPING,
    };
    pattern_->SetChainAnimationOptions(options);

    /**
     * @tc.steps: step1. When minSpace < maxSpace.
     * @tc.expected: minSpace and maxSpace would be itself.
     */
    const auto chainAnimation = pattern_->chainAnimation_;
    EXPECT_FLOAT_EQ(chainAnimation->minSpace_, minSpace);
    EXPECT_FLOAT_EQ(chainAnimation->maxSpace_, maxSpace);

    /**
     * @tc.steps: step2. When conductivity < 0.
     * @tc.expected: conductivity would be default value.
     */
    EXPECT_FLOAT_EQ(chainAnimation->conductivity_, ChainAnimation::DEFAULT_CONDUCTIVITY);

    /**
     * @tc.steps: step3. When intensity < 0.
     * @tc.expected: conductivity would be default value.
     */
    EXPECT_FLOAT_EQ(chainAnimation->intensity_, ChainAnimation::DEFAULT_INTENSITY);
}

/**
 * @tc.name: Pattern007
 * @tc.desc: Test SetChainAnimationOptions
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern007, TestSize.Level1)
{
    constexpr float space = 5.f;
    constexpr float minSpace = 2.f;
    constexpr float maxSpace = 10.f;
    constexpr float conductivity = 0;
    constexpr float intensity = 0;

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetSpace(Dimension(space));
    listModelNG.SetChainAnimation(true);
    listModelNG.SetChainAnimationOptions(
        { Dimension(minSpace), Dimension(maxSpace), conductivity, intensity, 0, DEFAULT_STIFFNESS, DEFAULT_DAMPING });
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout();

    ChainAnimationOptions options = {
        .minSpace = Dimension(minSpace),
        .maxSpace = Dimension(maxSpace),
        .conductivity = conductivity,
        .intensity = intensity,
        .edgeEffect = 0,
        .stiffness = DEFAULT_STIFFNESS,
        .damping = DEFAULT_DAMPING,
    };
    pattern_->SetChainAnimationOptions(options);

    /**
     * @tc.steps: step1. When conductivity == 0.
     * @tc.expected: conductivity would be itself.
     */
    const auto chainAnimation = pattern_->chainAnimation_;
    EXPECT_FLOAT_EQ(chainAnimation->conductivity_, conductivity);

    /**
     * @tc.steps: step2. When intensity == 0.
     * @tc.expected: conductivity would be itself.
     */
    EXPECT_FLOAT_EQ(chainAnimation->intensity_, intensity);
}

/**
 * @tc.name: Pattern008
 * @tc.desc: Test OutBoundaryCallback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern008, TestSize.Level1)
{
    CreateList(TOTAL_NUMBER);

    EXPECT_TRUE(pattern_->OutBoundaryCallback());

    constexpr float scrollOffset = -ITEM_HEIGHT;
    UpdateCurrentOffset(scrollOffset);
    EXPECT_FALSE(pattern_->OutBoundaryCallback());

    UpdateCurrentOffset(scrollOffset);
    EXPECT_TRUE(pattern_->OutBoundaryCallback());
}

/**
 * @tc.name: Pattern009
 * @tc.desc: Test OutBoundaryCallback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern009, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetChainAnimation(true);
    listModelNG.SetChainAnimationOptions(
        { Dimension(0), Dimension(10), 0, 0, 0, DEFAULT_STIFFNESS, DEFAULT_DAMPING });
    CreateListItem(10);
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_NE(pattern_->springProperty_, nullptr);
    EXPECT_NE(pattern_->chainAnimation_, nullptr);
    pattern_->OutBoundaryCallback();
    EXPECT_TRUE(pattern_->dragFromSpring_);
}

/**
 * @tc.name: Pattern010
 * @tc.desc: Test ScrollToIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern010, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItem(20);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Test ScrollToIndex.
     */
    pattern_->ScrollToIndex(1, 0, ScrollAlign::START);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, 100)));
    pattern_->ScrollToIndex(2, 0, ScrollAlign::CENTER);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, 0)));
    pattern_->ScrollToIndex(3, 0, ScrollAlign::END);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, 0)));
    pattern_->ScrollToIndex(4, 0, ScrollAlign::AUTO);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, 0)));

    pattern_->ScrollToIndex(1, false, ScrollAlign::START);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, 100)));
    pattern_->ScrollToIndex(2, false, ScrollAlign::CENTER);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, 0)));
    pattern_->ScrollToIndex(3, false, ScrollAlign::END);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, 0)));
    pattern_->ScrollToIndex(4, false, ScrollAlign::AUTO);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, 0)));

    pattern_->ScrollToIndex(1, true, ScrollAlign::START);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, 0)));
    pattern_->ScrollToIndex(2, true, ScrollAlign::CENTER);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, 0)));
    pattern_->ScrollToIndex(3, true, ScrollAlign::END);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, 0)));
    pattern_->ScrollToIndex(4, true, ScrollAlign::AUTO);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, 0)));

    pattern_->ScrollToIndex(-1, 0, ScrollAlign::END);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, 1200))); // Scroll to last ListItem.
    pattern_->ScrollToIndex(-2, 0, ScrollAlign::END);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, 1200)));  // Invalid param, not scroll.

    pattern_->ScrollToIndex(-2, false, ScrollAlign::END);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, 1200)));  // Invalid param, not scroll.
    pattern_->ScrollToIndex(1, true, ScrollAlign::END);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, 1200))); // Use animate not update offset immediately.
}

/**
 * @tc.name: Pattern011
 * @tc.desc: Test OnScrollCallback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern011, TestSize.Level1)
{
    auto startFunc = GetDefaultSwiperBuilder(80.f, false);
    ListModelNG listModelNG;
    listModelNG.SetChainAnimation(true);
    listModelNG.Create();
    RefPtr<ScrollControllerBase> scrollController = listModelNG.CreateScrollController();
    RefPtr<ScrollProxy> proxy = AceType::MakeRefPtr<NG::ScrollBarProxy>();
    listModelNG.SetScroller(scrollController, proxy);
    CreateListItemWithSwiper(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout();

    // Set swiperItem_ to list pattern
    GestureEvent info;
    DragSwiperItem(0, info);

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
    const Offset expectOffset1 = Offset(0, 0);
    IsEqualCurrentOffset(expectOffset1);
    EXPECT_TRUE(pattern_->animator_->IsStopped());

    /**
     * @tc.steps: step2. When has animator_ and stop, call OnScrollCallback.
     * @tc.expected:
     */
    ASSERT_NE(pattern_->GetScrollBar(), nullptr);
    pattern_->GetScrollBar()->SetDriving(true);
    pattern_->OnScrollCallback(100.f, SCROLL_FROM_UPDATE);
    const Offset expectOffset2 = Offset(0, 100.f);
    IsEqualCurrentOffset(expectOffset2);

    /**
     * @tc.steps: step3. Offset is 0, ProcessDragUpdate do nothing.
     * @tc.expected: CurrentOffset unchange.
     */
    pattern_->GetScrollBar()->SetDriving(false);
    pattern_->OnScrollCallback(0, SCROLL_FROM_UPDATE);
    const Offset expectOffset3 = Offset(0, 100.f);
    IsEqualCurrentOffset(expectOffset3);

    /**
     * @tc.steps: step4. When has animator_ and stop, call StopAnimate.
     * @tc.expected: Nothing.
     */
    pattern_->StopAnimate();
}

/**
 * @tc.name: Pattern012
 * @tc.desc: Test GetItemIndexByPosition
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern012, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetLanes(2);
    CreateListItem(VIEWPORT_NUMBER);
    GetInstance();
    RunMeasureAndLayout();

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
 * @tc.name: Pattern013
 * @tc.desc: Test GetItemIndexByPosition
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern013, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItem(VIEWPORT_NUMBER);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. When has ListItem, position not at any ListItem
     * @tc.expected: Would return the last itemIndex
     */
    const Point point = Point(0, 1000.f);
    int32_t itemIndex = pattern_->GetItemIndexByPosition(point.GetX(), point.GetY());
    EXPECT_EQ(itemIndex, VIEWPORT_NUMBER);
}

/**
 * @tc.name: Pattern014
 * @tc.desc: Test GetItemIndexByPosition
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern014, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. When has no ListItem, call GetItemIndexByPosition
     * @tc.expected: Would return 0
     */
    const Point point = Point(0, 1000.f);
    int32_t itemIndex = pattern_->GetItemIndexByPosition(point.GetX(), point.GetY());
    EXPECT_EQ(itemIndex, 0);
}

/**
 * @tc.name: Pattern015
 * @tc.desc: Test UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern015, TestSize.Level1)
{
    constexpr int32_t itemCount = 5;

    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItem(itemCount);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. UpdateCurrentOffset -100
     * @tc.expected: The list is unscrollable, offset is 0
     */
    constexpr float offset = -100.f;
    pattern_->UpdateCurrentOffset(offset, SCROLL_FROM_UPDATE);
    const Offset expectOffset = Offset(0, 0);
    EXPECT_TRUE(IsEqualCurrentOffset(expectOffset));
}

/**
 * @tc.name: Pattern016
 * @tc.desc: Test UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern016, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. UpdateCurrentOffset -100 with SCROLL_FROM_START
     * @tc.expected: The offset was not effected by friction
     */
    constexpr float offset = -100.f;
    pattern_->UpdateCurrentOffset(offset, SCROLL_FROM_START);
    constexpr float expectDelta = 100.f;
    EXPECT_EQ(pattern_->currentDelta_, expectDelta);
}

/**
 * @tc.name: Pattern017
 * @tc.desc: Test layout
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. do not set selfIdealSize, 0 listItem
     */
    ListModelNG listModelNG_1;
    listModelNG_1.Create();
    GetInstance();
    RunMeasureAndLayout(-1, -1);
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Width(), DEVICE_WIDTH);

    /**
     * @tc.steps: step1. do not set selfIdealSize, TOTAL_NUMBER listItem
     */
    ListModelNG listModelNG_2;
    listModelNG_2.Create();
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout(-1, -1);
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Width(), DEVICE_WIDTH);

    /**
     * @tc.steps: step1. set width Infinity
     */
    ListModelNG listModelNG_3;
    listModelNG_3.Create();
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout(Infinity<float>(), DEVICE_HEIGHT);
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Width(), Infinity<float>());
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
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetMultiSelectable(true);
    ListItemGroupModelNG listItemGroupModel;
    listItemGroupModel.Create(V2::ListItemGroupStyle::CARD);
    CreateListItem(9);
    ViewStackProcessor::GetInstance()->Pop();
    GetInstance();
    RunMeasureAndLayout();

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
    ASSERT_NE(frameNode_, nullptr);
    auto itemGroup = frameNode_->GetChildAtIndex(0);
    ASSERT_NE(itemGroup, nullptr);
    auto itemGroupFrameNode = AceType::DynamicCast<FrameNode>(itemGroup);
    ASSERT_NE(itemGroupFrameNode, nullptr);
    auto item = itemGroupFrameNode->GetChildAtIndex(0);
    ASSERT_NE(item, nullptr);
    auto itemFrameNode = AceType::DynamicCast<FrameNode>(item);
    ASSERT_NE(itemFrameNode, nullptr);
    RefPtr<ListItemPattern> firstItemPattern = itemFrameNode->GetPattern<ListItemPattern>();
    ASSERT_NE(firstItemPattern, nullptr);
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
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetMultiSelectable(true);
    ListItemGroupModelNG listItemGroupModel;
    listItemGroupModel.Create(V2::ListItemGroupStyle::CARD);
    CreateListItem(9);
    ViewStackProcessor::GetInstance()->Pop();
    GetInstance();
    RunMeasureAndLayout();

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
    ASSERT_NE(frameNode_, nullptr);
    auto itemGroup = frameNode_->GetChildAtIndex(0);
    ASSERT_NE(itemGroup, nullptr);
    auto itemGroupFrameNode = AceType::DynamicCast<FrameNode>(itemGroup);
    ASSERT_NE(itemGroupFrameNode, nullptr);
    auto item = itemGroupFrameNode->GetChildAtIndex(0);
    ASSERT_NE(item, nullptr);
    auto itemFrameNode = AceType::DynamicCast<FrameNode>(item);
    ASSERT_NE(itemFrameNode, nullptr);
    RefPtr<ListItemPattern> firstItemPattern = itemFrameNode->GetPattern<ListItemPattern>();
    ASSERT_NE(firstItemPattern, nullptr);
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
    constexpr int32_t itemCount = 9;

    /**
     * @tc.steps: step1. create List/ListItemGroup/ListItem and ListItem set to unselectable.
     * @tc.expected: step1. create a card style ListItemGroup success.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
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
    GetInstance();
    RunMeasureAndLayout();

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
    auto itemGroupFrameNode = GetChildFrameNode(0);
    ASSERT_NE(itemGroupFrameNode, nullptr);
    auto itemFourth = itemGroupFrameNode->GetChildAtIndex(3);
    ASSERT_NE(itemFourth, nullptr);
    auto itemFourthFrameNode = AceType::DynamicCast<FrameNode>(itemFourth);
    ASSERT_NE(itemFourthFrameNode, nullptr);
    RefPtr<ListItemPattern> fourthItemPattern = itemFourthFrameNode->GetPattern<ListItemPattern>();
    ASSERT_NE(fourthItemPattern, nullptr);
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
     * @tc.steps: step1. create ListItem theme and set default attributes.
     * @tc.expected: step1. create ListItem theme success.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto listTheme = AceType::MakeRefPtr<ListItemTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(listTheme));

    listTheme->defaultColor_ = Color::WHITE;
    listTheme->defaultLeftMargin_ = GROUP_MARGIN;
    listTheme->defaultRightMargin_ = GROUP_MARGIN;

    /**
     * @tc.steps: step2. create ListItemGroup.
     * @tc.expected: step2. create a card style ListItemGroup success.
     */
    ListItemGroupModelNG listItemGroupModelNG;
    listItemGroupModelNG.Create(V2::ListItemGroupStyle::CARD);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
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
     * @tc.steps: step1. create ListItem theme and set default attributes.
     * @tc.expected: step1. create ListItem theme success.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto listTheme = AceType::MakeRefPtr<ListItemTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(listTheme));
    listTheme->itemDefaultColor_ = Color::WHITE;

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
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(pattern->GetListItemStyle(), V2::ListItemStyle::CARD);

    /**
     * @tc.steps: step3. compare the obtained value with the set value.
     * @tc.expected: step3. the obtained value is equal to the set value.
     */
    auto renderContext = frameNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::WHITE);
}

/**
 * @tc.name: ListItemCallEventsForCardModeTest001
 * @tc.desc: Test whether the event has been called when listItem is in card mode.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemCallEventsForCardModeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ListItem theme and set default attributes.
     * @tc.expected: step1. create ListItem theme success.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto listTheme = AceType::MakeRefPtr<ListItemTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(listTheme));

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
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(pattern->GetListItemStyle(), V2::ListItemStyle::CARD);
    auto renderContext = frameNode->GetRenderContext();
    renderContext->UpdateBackgroundColor(Color::WHITE);

    /**
     * @tc.steps: step3. call function - InitListItemCardStyleForList.
     * @tc.expected: step3. the function can be called.
     */
    pattern->InitListItemCardStyleForList();
    EXPECT_EQ(pattern->currentBackgroundColor_, Color::WHITE);
}

/**
 * @tc.name: ListItemHoverEventForCardModeTest001
 * @tc.desc: Test the hover event when the hover status of card mode listItem is true.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemHoverEventForCardModeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ListItem theme and set default attributes.
     * @tc.expected: step1. create ListItem theme success.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto listTheme = AceType::MakeRefPtr<ListItemTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(listTheme));
    listTheme->hoverColor_ = Color::RED;
    listTheme->hoverAnimationDuration_ = 250;

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
}

/**
 * @tc.name: ListItemHoverEventForCardModeTest002
 * @tc.desc: Test the hover event when the hover status of card mode listItem is false.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemHoverEventForCardModeTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ListItem theme and set default attributes.
     * @tc.expected: step1. create ListItem theme success.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto listTheme = AceType::MakeRefPtr<ListItemTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(listTheme));
    listTheme->hoverColor_ = Color::RED;
    listTheme->hoverAnimationDuration_ = 250;

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
    pattern->currentBackgroundColor_ = Color::WHITE;

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
     * @tc.steps: step1. create ListItem theme and set default attributes.
     * @tc.expected: step1. create ListItem theme success.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto listTheme = AceType::MakeRefPtr<ListItemTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(listTheme));
    listTheme->hoverColor_ = Color::RED;
    listTheme->pressColor_ = Color::BLACK;
    listTheme->hoverToPressAnimationDuration_ = 100;

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
    auto renderContext = frameNode->GetRenderContext();
    pattern->currentBackgroundColor_ = Color::WHITE;

    /**
     * @tc.steps: step3. call function HandlePressEvent, set TouchType to DOWN and set hover status is true.
     * @tc.expected: step3. the color is different from the initial color when the listItem is pressed with the mouse.
     */
    TouchLocationInfo touchLocationInfo1(1);
    touchLocationInfo1.SetTouchType(TouchType::DOWN);
    TouchEventInfo touchEventInfo1("onTouchDown");
    touchEventInfo1.AddTouchLocationInfo(std::move(touchLocationInfo1));
    pattern->isHover_ = true;
    pattern->HandlePressEvent(touchEventInfo1, frameNode);
    EXPECT_NE(renderContext->GetBackgroundColorValue(), pattern->currentBackgroundColor_);

    /**
     * @tc.steps: step4. call function HandlePressEvent, set TouchType to DOWN and set hover status is false.
     * @tc.expected: step4. the color is different from the initial color when the listItem is pressed with gesture.
     */
    pattern->isHover_ = false;
    pattern->HandlePressEvent(touchEventInfo1, frameNode);
    EXPECT_NE(renderContext->GetBackgroundColorValue(), pattern->currentBackgroundColor_);

    /**
     * @tc.steps: step5. call function HandlePressEvent, set TouchType to UP and set hover status is true.
     * @tc.expected: step5. the color differs from the initial color when mouse hovers over listItem after pressing.
     */
    TouchLocationInfo touchLocationInfo2(1);
    touchLocationInfo2.SetTouchType(TouchType::UP);
    TouchEventInfo touchEventInfo2("onTouchUp");
    touchEventInfo2.AddTouchLocationInfo(std::move(touchLocationInfo2));
    pattern->isHover_ = true;
    pattern->HandlePressEvent(touchEventInfo2, frameNode);
    EXPECT_NE(renderContext->GetBackgroundColorValue(), pattern->currentBackgroundColor_);

    /**
     * @tc.steps: step6. call function HandlePressEvent, set TouchType to UP and set hover status is false.
     * @tc.expected: step6. the color returns to its original color after pressing on listItem through gestures.
     */
    pattern->isHover_ = false;
    renderContext->UpdateBackgroundColor(pattern->currentBackgroundColor_);
    pattern->HandlePressEvent(touchEventInfo2, frameNode);
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), pattern->currentBackgroundColor_);
}

/**
 * @tc.name: ListItemDisableEventForCardModeTest001
 * @tc.desc: Test disable event when the enable status of the listItem is false.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemDisableEventForCardModeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ListItem theme and set default attributes.
     * @tc.expected: step1. create ListItem theme success.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto listTheme = AceType::MakeRefPtr<ListItemTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(listTheme));
    listTheme->disabledAlpha_ = 0.4;

    /**
     * @tc.steps: step2. create ListItem in card mode.
     * @tc.expected: step2. create a card style ListItem success and set enable status to false.
     */
    ListItemModelNG listItemModel;
    listItemModel.Create([](int32_t) {}, V2::ListItemStyle::CARD);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ListItemPattern>();
    ASSERT_NE(pattern, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto eventHub = frameNode->GetEventHub<ListItemEventHub>();
    eventHub->SetEnabled(false);
    pattern->selectable_ = true;
    pattern->currentBackgroundColor_ = Color::WHITE;

    /**
     * @tc.steps: step3. call function InitDisableEvent.
     * @tc.expected: step3. the background color has been updated and selectable has been set to false.
     */
    pattern->InitDisableEvent();
    EXPECT_FALSE(pattern->selectable_);
    EXPECT_NE(renderContext->GetBackgroundColorValue(), pattern->currentBackgroundColor_);
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: ListItem Accessibility PerformAction test Select and ClearSelection.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, PerformActionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create listItem and initialize related properties.
     */
    ListItemModelNG listItemModel;
    listItemModel.Create();

    /**
     * @tc.steps: step2. Get listItem frameNode and pattern, set callback function.
     * @tc.expected: Related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto listItemPattern = frameNode->GetPattern<ListItemPattern>();
    ASSERT_NE(listItemPattern, nullptr);
    listItemPattern->SetSelectable(false);
    listItemPattern->SetAccessibilityAction();

    /**
     * @tc.steps: step3. Get listItem accessibilityProperty to call callback function.
     * @tc.expected: Related function is called.
     */
    auto listItemAccessibilityProperty = frameNode->GetAccessibilityProperty<ListItemAccessibilityProperty>();
    ASSERT_NE(listItemAccessibilityProperty, nullptr);

    /**
     * @tc.steps: step4. When listItem is not Selectable, call the callback function in listItemAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    EXPECT_TRUE(listItemAccessibilityProperty->ActActionSelect());
    EXPECT_TRUE(listItemAccessibilityProperty->ActActionClearSelection());

    /**
     * @tc.steps: step5. When listItem is Selectable, call the callback function in listItemAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    listItemPattern->SetSelectable(true);
    EXPECT_TRUE(listItemAccessibilityProperty->ActActionSelect());
    EXPECT_TRUE(listItemAccessibilityProperty->ActActionClearSelection());
}

/**
 * @tc.name: PerformActionTest002
 * @tc.desc: List Accessibility PerformAction test ScrollForward and ScrollBackward.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, PerformActionTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create list and initialize related properties.
     */
    ListModelNG listModelNG;
    listModelNG.Create();

    /**
     * @tc.steps: step2. Get list frameNode and pattern, set callback function.
     * @tc.expected: Related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto listPattern = frameNode->GetPattern<ListPattern>();
    ASSERT_NE(listPattern, nullptr);
    listPattern->scrollable_ = false;
    listPattern->SetAccessibilityAction();

    /**
     * @tc.steps: step3. Get list accessibilityProperty to call callback function.
     * @tc.expected: Related function is called.
     */
    auto listAccessibilityProperty = frameNode->GetAccessibilityProperty<ListAccessibilityProperty>();
    ASSERT_NE(listAccessibilityProperty, nullptr);

    /**
     * @tc.steps: step4. When list is not Scrollable, call the callback function in listAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    EXPECT_TRUE(listAccessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(listAccessibilityProperty->ActActionScrollBackward());

    /**
     * @tc.steps: step5. When list is Scrollable, call the callback function in listAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    listPattern->scrollable_ = true;
    EXPECT_TRUE(listAccessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(listAccessibilityProperty->ActActionScrollBackward());
}

/**
 * @tc.name: ListPattern_ScrollToIndex001
 * @tc.desc: Test ScrollToIndex when smooth is true and index is different value.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListPattern_ScrollToIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create list item.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    GetInstance();
    
    /**
     * @tc.steps: step2. Test ScrollToIndex when index is -2.
     * @tc.expected: Related function is called.
     */
    pattern_->ScrollToIndex(-2, true);
    EXPECT_EQ(pattern_->scrollAlign_, ScrollAlign::START);
    EXPECT_EQ(pattern_->currentDelta_, 0.0);
    EXPECT_FALSE(pattern_->targetIndex_.has_value());

    /**
     * @tc.steps: step3. Test ScrollToIndex when index is 11.
     * @tc.expected: Related function is called.
     */
    pattern_->ScrollToIndex(11, true);
    EXPECT_FALSE(pattern_->targetIndex_.has_value());

    /**
     * @tc.steps: step4. Test ScrollToIndex when index is -1.
     * @tc.expected: Related function is called.
     */
    pattern_->ScrollToIndex(-1, true);
    EXPECT_EQ(pattern_->targetIndex_, -1);
}

/**
 * @tc.name: ListPattern_OnDirtyLayoutWrapperSwap001
 * @tc.desc: Test OnDirtyLayoutWrapperSwap when targetIndex_ have value.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListPattern_OnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialization and create list item.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    GetInstance();
    auto layoutWrapper = RunMeasureAndLayout();
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(layoutWrapper->GetLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithmWrapper, nullptr);
    auto listLayoutAlgorithm = AceType::DynamicCast<ListLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(listLayoutAlgorithm, nullptr);
    float startPos = 0.0f;
    float endPos = 0.0f;
    float mainLen = 20.0f;
    bool isGroup = false;
    for (int i = 0; i < 10; i++) {
        startPos = endPos;
        listLayoutAlgorithm->itemPosition_[i] = { startPos, endPos, isGroup };
        endPos = startPos + mainLen;
    }

    /**
     * @tc.steps: step2. Assign a value to targetIndex_ and test OnDirtyLayoutWrapperSwap.
     * @tc.expected: Related function is called.
     */
    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = false;
    pattern_->targetIndex_ = VIEWPORT_NUMBER;
    EXPECT_TRUE(pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, config));

    pattern_->targetIndex_ = TOTAL_NUMBER + 1;
    EXPECT_TRUE(pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
    EXPECT_FALSE(pattern_->targetIndex_.has_value());

    /**
     * @tc.steps: step3. Take different values for scrollAlign_ and test OnDirtyLayoutWrapperSwap.
     * @tc.expected: Related function is called.
     */
    pattern_->targetIndex_ = VIEWPORT_NUMBER -1;
    pattern_->scrollAlign_ = ScrollAlign::END;
    EXPECT_TRUE(pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
}

/**
 * @tc.name: ListLayoutAlgorithm_OffScreenLayoutDirection001
 * @tc.desc: Test OffScreenLayoutDirection when targetIndex_ is in a different state.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListLayoutAlgorithm_OffScreenLayoutDirection001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialization.
     */
    constexpr float space = 5.0f;
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetSpace(Dimension(space));
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>();

    /**
     * @tc.steps: step2. When targetIndex_ is nullptr and test OffScreenLayoutDirection.
     * @tc.expected: Related function is called.
     */
    listLayoutAlgorithm->OffScreenLayoutDirection();
    EXPECT_FALSE(listLayoutAlgorithm->forwardFeature_);
    EXPECT_FALSE(listLayoutAlgorithm->backwardFeature_);

    /**
     * @tc.steps: step3. When targetIndex_ is nullptr and test OffScreenLayoutDirection.
     * @tc.expected: Related function is called.
     */
    listLayoutAlgorithm->SetTargetIndex(TOTAL_NUMBER - 2);
    listLayoutAlgorithm->OffScreenLayoutDirection();
    EXPECT_FALSE(listLayoutAlgorithm->forwardFeature_);
    EXPECT_FALSE(listLayoutAlgorithm->backwardFeature_);

    /**
     * @tc.steps: step4. Creat itemPosition_.
     */
    float startPos = 0.0f;
    float endPos = 0.0f;
    float mainLen = 20.0f;
    bool isGroup = false;
    for (int i = 0; i < 10; i++) {
        startPos = endPos;
        listLayoutAlgorithm->itemPosition_[i] = { startPos, endPos, isGroup };
        endPos = startPos + mainLen;
    }

    /**
     * @tc.steps: step5. Assign a value to targetIndex_ and test OffScreenLayoutDirection.
     * @tc.expected: Related function is called.
     */
    listLayoutAlgorithm->SetTargetIndex(TOTAL_NUMBER - 2);
    listLayoutAlgorithm->OffScreenLayoutDirection();
    EXPECT_FALSE(listLayoutAlgorithm->forwardFeature_);
    EXPECT_FALSE(listLayoutAlgorithm->backwardFeature_);

    listLayoutAlgorithm->SetTargetIndex(TOTAL_NUMBER + 1);
    listLayoutAlgorithm->OffScreenLayoutDirection();
    EXPECT_TRUE(listLayoutAlgorithm->forwardFeature_);
    EXPECT_FALSE(listLayoutAlgorithm->backwardFeature_);
}

/**
 * @tc.name: ListLayoutAlgorithm_OffScreenLayoutDirection002
 * @tc.desc: Test OffScreenLayoutDirection When the value of targetIndex_ is greater than endIndex.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListLayoutAlgorithm_OffScreenLayoutDirection002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialization.
     */
    constexpr float space = 5.0f;
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetSpace(Dimension(space));
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>();

    /**
     * @tc.steps: step2. Creat itemPosition_.
     */
    float startPos = 0.0f;
    float endPos = 0.0f;
    float mainLen = 20.0f;
    bool isGroup = false;
    for (int i = 10; i < 20; i++) {
        startPos = endPos;
        listLayoutAlgorithm->itemPosition_[i] = { startPos, endPos, isGroup };
        endPos = startPos + mainLen;
    }

    /**
     * @tc.steps: step3. Assign a value to targetIndex_ and test OffScreenLayoutDirection.
     * @tc.expected: Related function is called.
     */
    listLayoutAlgorithm->SetTargetIndex(TOTAL_NUMBER - 2);
    listLayoutAlgorithm->OffScreenLayoutDirection();
    EXPECT_FALSE(listLayoutAlgorithm->forwardFeature_);
    EXPECT_TRUE(listLayoutAlgorithm->backwardFeature_);
}
 /**
 * @tc.name: ListPositionControllerTest001
 * @tc.desc: Test PositionController function with smooth.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListPositionControllerTest001, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    RefPtr<ScrollControllerBase> scroller = listModelNG.CreateScrollController();
    listModelNG.SetScroller(scroller, nullptr);
    CreateListItem(10);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Get positionController and set scroll_.
     */
    auto controller = pattern_->positionController_;
    controller->scroll_ = AceType::WeakClaim(AceType::RawPtr(pattern_));

    /**
     * @tc.steps: step2. Call func when smooth is false or true.
     * @tc.expected: Return true.
     */
    EXPECT_EQ(controller->GetScrollDirection(), Axis::VERTICAL);
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 0, nullptr, false));
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 0, nullptr, true));

    /**
     * @tc.steps: step3. Call func when duration is positive.
     * @tc.expected: Return true.
     */
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 1.0, nullptr, false));
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 1.0, nullptr, true));
}

/**
 * @tc.name: ListPositionControllerTest002
 * @tc.desc: Test PositionController function with ICurve.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListPositionControllerTest002, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    RefPtr<ScrollControllerBase> scroller = listModelNG.CreateScrollController();
    listModelNG.SetScroller(scroller, nullptr);
    CreateListItem(10);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Get positionController and set scroll_.
     */
    auto controller = pattern_->positionController_;
    controller->scroll_ = AceType::WeakClaim(AceType::RawPtr(pattern_));

    /**
     * @tc.steps: step2. Create ICurve.
     */
    RefPtr<Curve> curve;
    std::string icurveString = "spring(7.000000,1.000000,227.000000,33.000000)";
    curve = Framework::CreateCurve(icurveString);

    /**
     * @tc.steps: step3. Call func when the duration and curve are valid.
     * @tc.expected: Return true.
     */
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 1.0, curve, false));
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 1.0, curve, true));
}

/**
 * @tc.name: ListPositionControllerTest003
 * @tc.desc: Test PositionController function with build-in curve.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListPositionControllerTest003, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    RefPtr<ScrollControllerBase> scroller = listModelNG.CreateScrollController();
    listModelNG.SetScroller(scroller, nullptr);
    CreateListItem(10);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Get positionController and set scroll_.
     */
    auto controller = pattern_->positionController_;
    controller->scroll_ = AceType::WeakClaim(AceType::RawPtr(pattern_));

    /**
     * @tc.steps: step2. Create build-in curve.
     */
    RefPtr<Curve> curve = Curves::EASE_IN;

    /**
     * @tc.steps: step3. Call func when the duration and curve are valid.
     * @tc.expected: Return true.
     */
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 1.0, curve, false));
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 1.0, curve, true));
}

/**
 * @tc.name: ListPositionControllerTest004
 * @tc.desc: Test IsAtEnd function
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListPositionControllerTest004, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    RefPtr<ScrollControllerBase> scrollController = listModelNG.CreateScrollController();
    RefPtr<ScrollProxy> proxy = AceType::MakeRefPtr<NG::ScrollBarProxy>();
    listModelNG.SetScroller(scrollController, proxy);
    CreateListItem(10);
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_FALSE(scrollController->IsAtEnd());

    const float delta = 200;
    UpdateCurrentOffset(-delta);
    EXPECT_TRUE(scrollController->IsAtEnd());
}

/**
 * @tc.name: AccessibilityEvent001
 * @tc.desc: Test AddStopListener callBack in animator
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AccessibilityEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create list and initialize related properties.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    GetInstance();

    /**
     * @tc.steps: step2. Call NotifyStopListener func.
     * @tc.expected isScrollEnd_ is true
     */
    pattern_->AnimateTo(0, 0, nullptr, true);
    pattern_->animator_->NotifyStopListener();
    EXPECT_TRUE(pattern_->isScrollEnd_);
}

/**
 * @tc.name: ScrollToIndexAlign001
 * @tc.desc: Test ScrollToIndex with assigning align
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ScrollToIndexAlign001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create list and initialize related properties.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetInitialIndex(0);
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    auto layoutWrapper = RunMeasureAndLayout();
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step2. Call ScrollToIndex func.
     * @tc.expected index and align is accurate.
     */
    pattern_->ScrollToIndex(TOTAL_NUMBER - 2, false, ScrollAlign::AUTO);
    EXPECT_EQ(pattern_->scrollAlign_, ScrollAlign::AUTO);
    EXPECT_EQ(pattern_->jumpIndex_, TOTAL_NUMBER - 2);
    EXPECT_FALSE(pattern_->targetIndex_.has_value());
    
    /**
     * @tc.steps: step3. Create listLayoutAlgorithm then measure and layout.
     * @tc.expected: Related function is called and layout is accurate.
     */
    auto listLayoutAlgorithm = AceType::DynamicCast<ListLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    ASSERT_NE(listLayoutAlgorithm, nullptr);
    EXPECT_EQ(listLayoutAlgorithm->jumpIndex_, TOTAL_NUMBER - 2);
    EXPECT_EQ(listLayoutAlgorithm->scrollAlign_, ScrollAlign::AUTO);
    EXPECT_EQ(listLayoutAlgorithm->GetStartIndex(), 0);
    layoutWrapper = RunMeasureAndLayout();
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(layoutWrapper->GetLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithmWrapper, nullptr);
    listLayoutAlgorithm = AceType::DynamicCast<ListLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(listLayoutAlgorithm, nullptr);
    EXPECT_NE(listLayoutAlgorithm->GetStartIndex(), 0);
    EXPECT_EQ(listLayoutAlgorithm->GetEndIndex(), TOTAL_NUMBER - 2);
    EXPECT_EQ(listLayoutAlgorithm->itemPosition_.rbegin()->second.endPos, listLayoutAlgorithm->contentMainSize_);
    DirtySwapConfig config;
    config.skipMeasure = false;
    config.skipLayout = false;
    EXPECT_TRUE(pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
    
    /**
     * @tc.steps: step4. Take different values for index, smooth and scrollAlign_ and test.
     * @tc.expected: Related function is called.
     */
    pattern_->ScrollToIndex(TOTAL_NUMBER - 1, true, ScrollAlign::AUTO);
    EXPECT_FALSE(pattern_->jumpIndex_.has_value());
    EXPECT_EQ(pattern_->targetIndex_, TOTAL_NUMBER - 1);
    EXPECT_EQ(pattern_->scrollAlign_, ScrollAlign::AUTO);
    layoutWrapper = RunMeasureAndLayout();
    ASSERT_NE(layoutWrapper, nullptr);
    EXPECT_TRUE(pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
    pattern_->scrollAlign_ = ScrollAlign::END;
    EXPECT_TRUE(pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
    pattern_->scrollAlign_ = ScrollAlign::CENTER;
    EXPECT_TRUE(pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
    pattern_->scrollAlign_ = ScrollAlign::START;
    EXPECT_TRUE(pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, config));

    /**
     * @tc.steps: step5. Call CalculateEstimateOffset in listLayoutAlgorithm.
     * @tc.expected: Related function is called.
     */
    listLayoutAlgorithm->jumpIndex_ = 1;
    listLayoutAlgorithm->scrollAlign_ = ScrollAlign::AUTO;
    listLayoutAlgorithm->scrollAutoType_ = ScrollAutoType::START;
    listLayoutAlgorithm->CalculateEstimateOffset(ScrollAlign::AUTO);
    EXPECT_NE(listLayoutAlgorithm->estimateOffset_, 0.0f);
    listLayoutAlgorithm->itemPosition_.clear();
    listLayoutAlgorithm->CalculateEstimateOffset(ScrollAlign::AUTO);
    EXPECT_EQ(listLayoutAlgorithm->estimateOffset_, 0.0f);
}

/**
 * @tc.name: ListLayoutAlgorithm_FixPredictSnapOffset001
 * @tc.desc: Test FixPredictSnapOffset when the scrollSnapAlign is start.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListLayoutAlgorithm_FixPredictSnapOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialization.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    GetInstance();
    auto listLayoutAlgorithm = AceType::DynamicCast<ListLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    layoutProperty_->UpdateScrollSnapAlign(V2::ScrollSnapAlign::START);

    /**
     * @tc.steps: step2. Creat itemPosition_.
     */
    float startPos = 0.0f;
    float endPos = 0.0f;
    float mainLen = 20.0f;
    bool isGroup = false;
    for (int i = 0; i < 10; i++) {
        startPos = endPos;
        listLayoutAlgorithm->itemPosition_[i] = { startPos, endPos, isGroup };
        endPos = startPos + mainLen;
    }
    /**
     * @tc.steps: step3. Set predictSnapOffset then call FixPredictSnapOffset and then get
     *            predictSnapOffset to check value.
     */
    listLayoutAlgorithm->SetSpaceWidth(5);
    listLayoutAlgorithm->SetPredictSnapOffset(10.0f);
    listLayoutAlgorithm->FixPredictSnapOffset(layoutProperty_);
    EXPECT_EQ(listLayoutAlgorithm->GetPredictSnapOffset().value(), 0);

    listLayoutAlgorithm->SetTotalOffset(20.0f);
    listLayoutAlgorithm->SetPredictSnapOffset(10.0f);
    listLayoutAlgorithm->FixPredictSnapOffset(layoutProperty_);
    EXPECT_EQ(listLayoutAlgorithm->GetPredictSnapOffset().value(), 20);

    listLayoutAlgorithm->SetTotalOffset(10.0f);
    listLayoutAlgorithm->SetPredictSnapOffset(10.0f);
    listLayoutAlgorithm->FixPredictSnapOffset(layoutProperty_);
    EXPECT_EQ(listLayoutAlgorithm->GetPredictSnapOffset().value(), 10);
}

/**
 * @tc.name: ListLayoutAlgorithm_FixPredictSnapOffset002
 * @tc.desc: Test FixPredictSnapOffset when the scrollSnapAlign is center.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListLayoutAlgorithm_FixPredictSnapOffset002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialization.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    GetInstance();
    auto listLayoutAlgorithm = AceType::DynamicCast<ListLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    layoutProperty_->UpdateScrollSnapAlign(V2::ScrollSnapAlign::CENTER);

    /**
     * @tc.steps: step2. Creat itemPosition_.
     */
    float startPos = 0.0f;
    float endPos = 0.0f;
    float mainLen = 20.0f;
    bool isGroup = false;
    for (int i = 0; i < 10; i++) {
        startPos = endPos;
        listLayoutAlgorithm->itemPosition_[i] = { startPos, endPos, isGroup };
        endPos = startPos + mainLen;
    }
    /**
     * @tc.steps: step3. Set predictSnapOffset then call FixPredictSnapOffset and then get
     *            predictSnapOffset to check value.
     */
    listLayoutAlgorithm->SetSpaceWidth(5);
    listLayoutAlgorithm->SetPredictSnapOffset(10.0f);
    listLayoutAlgorithm->FixPredictSnapOffset(layoutProperty_);
    EXPECT_EQ(listLayoutAlgorithm->GetPredictSnapOffset().value(), 0);

    listLayoutAlgorithm->SetTotalOffset(20.0f);
    listLayoutAlgorithm->SetPredictSnapOffset(10.0f);
    listLayoutAlgorithm->FixPredictSnapOffset(layoutProperty_);
    EXPECT_EQ(listLayoutAlgorithm->GetPredictSnapOffset().value(), 25);

    listLayoutAlgorithm->SetTotalOffset(10.0f);
    listLayoutAlgorithm->SetPredictSnapOffset(10.0f);
    listLayoutAlgorithm->FixPredictSnapOffset(layoutProperty_);
    EXPECT_EQ(listLayoutAlgorithm->GetPredictSnapOffset().value(), 10);
}

/**
 * @tc.name: ListLayoutAlgorithm_FixPredictSnapOffset003
 * @tc.desc: Test FixPredictSnapOffset when the scrollSnapAlign is end.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListLayoutAlgorithm_FixPredictSnapOffset003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialization.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    GetInstance();
    auto listLayoutAlgorithm = AceType::DynamicCast<ListLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    layoutProperty_->UpdateScrollSnapAlign(V2::ScrollSnapAlign::END);

    /**
     * @tc.steps: step2. Creat itemPosition_.
     */
    float startPos = 0.0f;
    float endPos = 0.0f;
    float mainLen = 20.0f;
    bool isGroup = false;
    for (int i = 0; i < 10; i++) {
        startPos = endPos;
        listLayoutAlgorithm->itemPosition_[i] = { startPos, endPos, isGroup };
        endPos = startPos + mainLen;
    }
    /**
     * @tc.steps: step3. Set predictSnapOffset then call FixPredictSnapOffset and then get
     *            predictSnapOffset to check value.
     */
    listLayoutAlgorithm->SetSpaceWidth(5);
    listLayoutAlgorithm->SetPredictSnapOffset(10.0f);
    listLayoutAlgorithm->FixPredictSnapOffset(layoutProperty_);
    EXPECT_EQ(listLayoutAlgorithm->GetPredictSnapOffset().value(), 0);

    listLayoutAlgorithm->SetTotalOffset(20.0f);
    listLayoutAlgorithm->SetPredictSnapOffset(10.0f);
    listLayoutAlgorithm->FixPredictSnapOffset(layoutProperty_);
    EXPECT_EQ(listLayoutAlgorithm->GetPredictSnapOffset().value(), 20);

    listLayoutAlgorithm->SetTotalOffset(10.0f);
    listLayoutAlgorithm->SetPredictSnapOffset(10.0f);
    listLayoutAlgorithm->FixPredictSnapOffset(layoutProperty_);
    EXPECT_EQ(listLayoutAlgorithm->GetPredictSnapOffset().value(), 15);
}

/**
 * @tc.name: ListPattern_UpdateScrollSnap001
 * @tc.desc: Test UpdateScrollSnap.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListPattern_UpdateScrollSnap001, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    GetInstance();
    pattern_->AnimateTo(0, 0, nullptr, true);
    pattern_->UpdateScrollSnap();
    EXPECT_FALSE(pattern_->predictSnapOffset_.has_value());
    pattern_->animator_->Stop();
    pattern_->UpdateScrollSnap();
    EXPECT_EQ(pattern_->predictSnapOffset_.value(), 0.0);
}

/**
 * @tc.name: ListPattern_NeedScrollSnapAlignEffect001
 * @tc.desc: Test NeedScrollSnapAlignEffect.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListPattern_NeedScrollSnapAlignEffect001, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    GetInstance();
    layoutProperty_->UpdateScrollSnapAlign(V2::ScrollSnapAlign::NONE);
    EXPECT_FALSE(pattern_->NeedScrollSnapAlignEffect());
    layoutProperty_->UpdateScrollSnapAlign(V2::ScrollSnapAlign::START);
    EXPECT_TRUE(pattern_->NeedScrollSnapAlignEffect());
}
} // namespace OHOS::Ace::NG
