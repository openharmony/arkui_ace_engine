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

#ifndef TEST_SEGMENTED_WATER_FLOW
#define protected public
#include "test/mock/base/mock_system_properties.h"
#undef protected
#endif
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/rosen/mock_canvas.h"

#define protected public
#define private public
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "water_flow_test_ng.h"

#include "core/components/scroll/scroll_controller_base.h"
#include "core/components_ng/pattern/button/button_model_ng.h"
#include "core/components_ng/pattern/linear_layout/row_model_ng.h"
#include "core/components_ng/syntax/lazy_for_each_model_ng.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"
#include "core/components_ng/syntax/lazy_layout_wrapper_builder.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_model_ng.h"
#include "core/components_ng/syntax/syntax_item.h"
#undef private
#undef protected
#include "test/mock/core/animation/mock_animation_manager.h"

namespace OHOS::Ace::NG {

void WaterFlowTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));
    auto scrollableThemeConstants = CreateThemeConstants(THEME_PATTERN_SCROLLABLE);
    auto scrollableTheme = ScrollableTheme::Builder().Build(scrollableThemeConstants);
    EXPECT_CALL(*themeManager, GetTheme(ScrollableTheme::TypeId())).WillRepeatedly(Return(scrollableTheme));
    MockAnimationManager::Enable(true);
    auto container = Container::Current();
    ASSERT_TRUE(container);
    container->SetUseNewPipeline();
#ifndef TEST_SEGMENTED_WATER_FLOW
    g_segmentedWaterflow = false;
#endif
    PipelineContext::GetCurrentContext()->SetMinPlatformVersion(12);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(12);
}

void WaterFlowTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void WaterFlowTestNg::SetUp()
{
    MockAnimationManager::GetInstance().Reset();
}

void WaterFlowTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
    ClearOldNodes(); // Each testCase will create new list at begin
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
    ViewStackProcessor::GetInstance()->ClearStack();
}

void WaterFlowTestNg::GetWaterFlow()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    frameNode_->isConstraintNotChanged_ = true;
    pattern_ = frameNode_->GetPattern<WaterFlowPattern>();
    eventHub_ = frameNode_->GetEventHub<WaterFlowEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<WaterFlowLayoutProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<WaterFlowAccessibilityProperty>();
    positionController_ = pattern_->GetOrCreatePositionController();
}

WaterFlowModelNG WaterFlowTestNg::CreateWaterFlow()
{
    ResetElmtId();
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    WaterFlowModelNG model;
    model.Create();
    ViewAbstract::SetWidth(CalcLength(WATER_FLOW_WIDTH));
    ViewAbstract::SetHeight(CalcLength(WATER_FLOW_HEIGHT));
    RefPtr<ScrollControllerBase> positionController = model.CreateScrollController();
    RefPtr<ScrollProxy> scrollBarProxy = model.CreateScrollBarProxy();
    model.SetScroller(positionController, scrollBarProxy);
#ifdef TEST_WATER_FLOW_SW
    model.SetLayoutMode(WaterFlowLayoutMode::SLIDING_WINDOW);
#endif
    GetWaterFlow();
    return model;
}

void WaterFlowTestNg::CreateWaterFlowItems(int32_t itemNumber)
{
    for (int32_t index = 0; index < itemNumber; index++) {
        // Set diff item height
        CreateWaterFlowItem((index & 1) == 0 ? ITEM_MAIN_SIZE : BIG_ITEM_MAIN_SIZE);
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
}

void WaterFlowTestNg::CreateItemsInRepeat(int32_t itemNumber, std::function<float(uint32_t)>&& getSize)
{
    RepeatVirtualScrollModelNG repeatModel;
    std::function<void(uint32_t)> createFunc = [this, getSize](uint32_t idx) { CreateItemWithHeight(getSize(idx)); };
    std::function<void(const std::string&, uint32_t)> updateFunc =
        [this, getSize](const std::string& value, uint32_t idx) { CreateItemWithHeight(getSize(idx)); };
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
    repeatModel.Create(itemNumber, {}, createFunc, updateFunc, getKeys, getTypes, [](uint32_t start, uint32_t end) {});
}

RefPtr<WaterFlowMockLazy> WaterFlowTestNg::CreateItemsInLazyForEach(
    int32_t itemNumber, std::function<float(int32_t)>&& getHeight)
{
    RefPtr<WaterFlowMockLazy> mockLazy = AceType::MakeRefPtr<WaterFlowMockLazy>(itemNumber, std::move(getHeight));
    RefPtr<LazyForEachActuator> mockLazyActuator = mockLazy;
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    LazyForEachModelNG lazyForEachModelNG;
    lazyForEachModelNG.Create(mockLazyActuator);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    return mockLazy;
}

std::pair<std::string, RefPtr<NG::UINode>> WaterFlowMockLazy::OnGetChildByIndex(
    int32_t index, std::unordered_map<std::string, NG::LazyForEachCacheChild>& expiringItems)
{
    ScopedViewStackProcessor scope;
    WaterFlowItemModelNG waterFlowItemModel;
    waterFlowItemModel.Create();
    ViewAbstract::SetWidth(CalcLength(CalcLength(FILL_LENGTH)));
    ViewAbstract::SetHeight(CalcLength(getHeight_(index)));
    auto node = ViewStackProcessor::GetInstance()->Finish();
    return { std::to_string(index), node };
}

void WaterFlowTestNg::AddItemInLazyForEach(int32_t index)
{
    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(frameNode_->GetChildAtIndex(0));
    lazyForEachNode->OnDataAdded(index);
}

void WaterFlowTestNg::DeleteItemInLazyForEach(int32_t index)
{
    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(frameNode_->GetChildAtIndex(0));
    lazyForEachNode->OnDataDeleted(index);
}

WaterFlowItemModelNG WaterFlowTestNg::CreateWaterFlowItem(float mainSize)
{
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    WaterFlowItemModelNG waterFlowItemModel;
    waterFlowItemModel.Create();
    Axis axis = Axis::VERTICAL;
    FlexDirection flexDirection = layoutProperty_->GetWaterflowDirection().value_or(FlexDirection::COLUMN);
    if (flexDirection == FlexDirection::ROW || flexDirection == FlexDirection::ROW_REVERSE) {
        axis = Axis::HORIZONTAL;
    }
    SetSize(axis, CalcLength(FILL_LENGTH), CalcLength(mainSize));
    return waterFlowItemModel;
}

void WaterFlowTestNg::CreateFocusableWaterFlowItems(int32_t itemNumber)
{
    for (int32_t index = 0; index < itemNumber; index++) {
        // Set diff item height
        CreateWaterFlowItem((index & 1) == 0 ? ITEM_MAIN_SIZE : BIG_ITEM_MAIN_SIZE);
        ButtonModelNG buttonModelNG;
        std::list<RefPtr<Component>> buttonChildren;
        buttonModelNG.CreateWithLabel({ .label = "label" }, buttonChildren);
        ViewStackProcessor::GetInstance()->GetMainElementNode()->onMainTree_ = true;
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->GetMainElementNode()->onMainTree_ = true;
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
}

void WaterFlowTestNg::CreateRandomWaterFlowItems(int32_t itemNumber)
{
    std::srand(0);
    for (int32_t i = 0; i < itemNumber; i++) {
        CreateWaterFlowItem(std::rand() % 200 + 50.0f);
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
}

void WaterFlowTestNg::AddItems(int32_t itemNumber)
{
    for (int i = 0; i < itemNumber; ++i) {
        auto child = WaterFlowItemNode::GetOrCreateFlowItem(
            V2::FLOW_ITEM_ETS_TAG, -1, []() { return AceType::MakeRefPtr<WaterFlowItemPattern>(); });
        if (i & 1) {
            child->GetLayoutProperty()->UpdateUserDefinedIdealSize(
                CalcSize(CalcLength(FILL_LENGTH), CalcLength(Dimension(BIG_ITEM_MAIN_SIZE))));
        } else {
            child->GetLayoutProperty()->UpdateUserDefinedIdealSize(
                CalcSize(CalcLength(FILL_LENGTH), CalcLength(Dimension(ITEM_MAIN_SIZE))));
        }
        frameNode_->AddChild(child);
    }
}

void WaterFlowTestNg::AddItemsAtSlot(int32_t itemNumber, float height, int32_t slotIdx)
{
    for (int i = 0; i < itemNumber; ++i) {
        auto child = WaterFlowItemNode::GetOrCreateFlowItem(
            V2::FLOW_ITEM_ETS_TAG, -1, []() { return AceType::MakeRefPtr<WaterFlowItemPattern>(); });
        child->GetLayoutProperty()->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(FILL_LENGTH), CalcLength(Dimension(height))));
        frameNode_->AddChild(child, slotIdx);
    }
}

void WaterFlowTestNg::CreateItemWithHeight(float height)
{
    CreateWaterFlowItem(height);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
}

void WaterFlowTestNg::UpdateCurrentOffset(float offset, int32_t source)
{
    pattern_->UpdateCurrentOffset(offset, source);
    FlushLayoutTask(frameNode_);
}

std::function<void()> WaterFlowTestNg::GetDefaultHeaderBuilder()
{
    return []() {
        RowModelNG rowModel;
        rowModel.Create(std::nullopt, nullptr, "");
        ViewAbstract::SetWidth(CalcLength(Dimension(1.0, DimensionUnit::PERCENT)));
        ViewAbstract::SetHeight(CalcLength(Dimension(50.f)));
    };
}

void WaterFlowTestNg::HandleDrag(float offset)
{
    GestureEvent info;
    info.SetMainVelocity(1200.f);
    info.SetGlobalPoint(Point(0.f, 0.f));
    info.SetGlobalLocation(Offset(0.f, 0.f));
    info.SetSourceTool(SourceTool::FINGER);
    info.SetInputEventType(InputEventType::TOUCH_SCREEN);
    pattern_->scrollableEvent_->GetScrollable()->HandleDragStart(info);

    info.SetGlobalLocation(Offset(0.f, -offset));
    info.SetGlobalPoint(Point(0.f, -offset));
    info.SetMainDelta(offset);
    pattern_->scrollableEvent_->GetScrollable()->HandleDragUpdate(info);
    FlushLayoutTask(frameNode_);

    info.SetMainVelocity(0.0);
    info.SetMainDelta(0.0);
    pattern_->scrollableEvent_->GetScrollable()->HandleDragEnd(info);
    FlushLayoutTask(frameNode_);
}

RectF WaterFlowTestNg::GetLazyChildRect(int32_t itemIndex)
{
    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(frameNode_->GetChildAtIndex(0));
    auto waterFlowItem = AceType::DynamicCast<FrameNode>(lazyForEachNode->GetChildAtIndex(itemIndex));
    return waterFlowItem->GetGeometryNode()->GetFrameRect();
}

RefPtr<FrameNode> WaterFlowTestNg::GetItem(int32_t index, bool isCache)
{
    return AceType::DynamicCast<FrameNode>(frameNode_->GetChildByIndex(index, isCache));
}

/**
 * @tc.name: LazyForeachLayout001
 * @tc.desc: Test LazyForeach Layout
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, LazyForeachLayout001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateItemsInLazyForEach(100, [](int32_t index) { return (index & 1) == 0 ? ITEM_MAIN_SIZE : BIG_ITEM_MAIN_SIZE; });
    CreateDone();
    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(frameNode_->GetChildAtIndex(0));
    EXPECT_TRUE(IsEqual(GetLazyChildRect(0), RectF(0, 0, 240, 100)));
    EXPECT_TRUE(IsEqual(GetLazyChildRect(1), RectF(240, 0, 240, 200)));
    EXPECT_TRUE(IsEqual(GetLazyChildRect(2), RectF(0, 100, 240, 100)));
    EXPECT_TRUE(IsEqual(GetLazyChildRect(3), RectF(0, 200, 240, 200)));
    EXPECT_TRUE(IsEqual(GetLazyChildRect(4), RectF(240, 200, 240, 100)));
    EXPECT_TRUE(IsEqual(GetLazyChildRect(5), RectF(240, 300, 240, 200)));
    EXPECT_TRUE(IsEqual(GetLazyChildRect(6), RectF(0, 400, 240, 100)));
    EXPECT_TRUE(IsEqual(GetLazyChildRect(7), RectF(0, 500, 240, 200)));
    EXPECT_TRUE(IsEqual(GetLazyChildRect(8), RectF(240, 500, 240, 100)));
    EXPECT_TRUE(IsEqual(GetLazyChildRect(9), RectF(240, 600, 240, 200)));
}

/**
 * @tc.name: Layout001
 * @tc.desc: Test Layout
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Layout001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems();
    CreateDone();
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 0), RectF(0, 0, 240, 100)));
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 1), RectF(240, 0, 240, 200)));
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 2), RectF(0, 100, 240, 100)));
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 3), RectF(0, 200, 240, 200)));
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 4), RectF(240, 200, 240, 100)));
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 5), RectF(240, 300, 240, 200)));
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 6), RectF(0, 400, 240, 100)));
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 7), RectF(0, 500, 240, 200)));
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 8), RectF(240, 500, 240, 100)));
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 9), RectF(240, 600, 240, 200)));
}

/**
 * @tc.name: Property001
 * @tc.desc: Test all the properties of WaterFlow.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Property001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetRowsTemplate("1fr 1fr 1fr");
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(5));
    model.SetColumnsGap(Dimension(10));
    model.SetLayoutDirection(FlexDirection::ROW);
    model.SetItemMinWidth(Dimension(10));
    model.SetItemMinHeight(Dimension(20));
    model.SetItemMaxWidth(Dimension(200));
    model.SetItemMaxHeight(Dimension(500));
    CreateWaterFlowItems();
    CreateDone();

    /**
     * @tc.steps: step1. compare waterFlow properties and expected value.
     * @tc.expected: waterFlow properties equals expected value.
     */
    EXPECT_EQ(layoutProperty_->GetRowsTemplateValue(), "1fr 1fr 1fr");
    EXPECT_EQ(layoutProperty_->GetColumnsTemplateValue(), "1fr 1fr");
    EXPECT_EQ(layoutProperty_->GetRowsGapValue(), Dimension(5));
    EXPECT_EQ(layoutProperty_->GetColumnsGapValue(), Dimension(10));
    EXPECT_EQ(layoutProperty_->GetWaterflowDirectionStr(), "FlexDirection.Row");

    auto minSize = layoutProperty_->GetItemMinSize();
    EXPECT_EQ(minSize->Width().value_or(CalcLength(Infinity<double>(), DimensionUnit::VP)).ToString(), "10.00px");
    EXPECT_EQ(minSize->Height().value_or(CalcLength(Infinity<double>(), DimensionUnit::VP)).ToString(), "20.00px");

    auto maxSize = layoutProperty_->GetItemMaxSize();
    EXPECT_EQ(maxSize->Width().value_or(CalcLength(Infinity<double>(), DimensionUnit::VP)).ToString(), "200.00px");
    EXPECT_EQ(maxSize->Height().value_or(CalcLength(Infinity<double>(), DimensionUnit::VP)).ToString(), "500.00px");

    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: Property002
 * @tc.desc: Test empty row/col template.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Property002, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetRowsTemplate("");
    model.SetColumnsTemplate("");
    CreateWaterFlowItems();
    CreateDone();

    /**
     * @tc.steps: step1. compare waterFlow properties and expected value after change.
     * @tc.expected: waterFlow properties equals expected value after change.
     */
    EXPECT_EQ(layoutProperty_->GetRowsTemplateValue(), "1fr");
    EXPECT_EQ(layoutProperty_->GetColumnsTemplateValue(), "1fr");
}

/**
 * @tc.name: Property003
 * @tc.desc: Test GetWaterFlowDirectionStr func.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Property003, TestSize.Level1)
{
    CreateWaterFlow();
    CreateWaterFlowItems();
    CreateDone();
    EXPECT_EQ(layoutProperty_->GetWaterflowDirectionStr(), "FlexDirection.Column");
    EXPECT_FALSE(layoutProperty_->IsReverse());
    EXPECT_EQ(layoutProperty_->GetAxis(), Axis::VERTICAL);
    layoutProperty_->UpdateWaterflowDirection(FlexDirection::ROW);
    EXPECT_EQ(layoutProperty_->GetWaterflowDirectionStr(), "FlexDirection.Row");
    layoutProperty_->UpdateWaterflowDirection(FlexDirection::COLUMN_REVERSE);
    EXPECT_EQ(layoutProperty_->GetWaterflowDirectionStr(), "FlexDirection.ColumnReverse");
    layoutProperty_->UpdateWaterflowDirection(FlexDirection::ROW_REVERSE);
    EXPECT_EQ(layoutProperty_->GetWaterflowDirectionStr(), "FlexDirection.RowReverse");
    EXPECT_TRUE(layoutProperty_->IsReverse());
    EXPECT_EQ(layoutProperty_->GetAxis(), Axis::HORIZONTAL);
}

/**
 * @tc.name: Property004
 * @tc.desc: Test auto row/col template.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Property004, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetRowsTemplate("auto");
    model.SetColumnsTemplate("auto");
    CreateWaterFlowItems();
    CreateDone();
    EXPECT_EQ(pattern_->GetColumns(), 1);
    EXPECT_EQ(pattern_->GetRows(), 6);
}

/**
 * @tc.name: Property006
 * @tc.desc: Test repeat col template.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Property006, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("repeat(3, 2fr)");
    CreateWaterFlowItems();
    CreateDone();
    EXPECT_EQ(pattern_->GetRows(), VIEW_LINE_NUMBER / 2);
}

/**
 * @tc.name: Property007
 * @tc.desc: Test auto-fill row/col template.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Property007, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetRowsTemplate("repeat(auto-fill, 72px)");
    model.SetColumnsTemplate("repeat(auto-fill, 113px)");
    CreateWaterFlowItems();
    CreateDone();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: Property008
 * @tc.desc: Test some invaild properties of WaterFlow.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Property008, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetRowsTemplate("1fr 1fr 1fr");
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(-5));
    model.SetColumnsGap(Dimension(-10));
    CreateWaterFlowItems();
    CreateDone();

    EXPECT_EQ(GetChildWidth(frameNode_, 0), WATER_FLOW_WIDTH / 2.0f);
    EXPECT_EQ(GetChildWidth(frameNode_, 1), WATER_FLOW_WIDTH / 2.0f);

    layoutProperty_->UpdateColumnsGap(Dimension(5.0f));
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(GetChildWidth(frameNode_, 0), (WATER_FLOW_WIDTH - 5.0f) / 2.0f);
    EXPECT_EQ(GetChildWidth(frameNode_, 1), (WATER_FLOW_WIDTH - 5.0f) / 2.0f);
    EXPECT_EQ(GetChildX(frameNode_, 1), WATER_FLOW_WIDTH / 2.0f + 2.5f);
    layoutProperty_->UpdateColumnsGap(Dimension(10.0f));
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(GetChildWidth(frameNode_, 0), (WATER_FLOW_WIDTH - 10.0f) / 2.0f);
    EXPECT_EQ(GetChildWidth(frameNode_, 1), (WATER_FLOW_WIDTH - 10.0f) / 2.0f);
    EXPECT_EQ(GetChildX(frameNode_, 1), WATER_FLOW_WIDTH / 2.0f + 5.0f);
}

/**
 * @tc.name: Property009
 * @tc.desc: Test enableScrollInteraction of WaterFlow.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Property009, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetScrollEnabled(true);
    CreateWaterFlowItems();
    CreateDone();
    EXPECT_EQ(layoutProperty_->GetScrollEnabled(), true);
    layoutProperty_->UpdateScrollEnabled(false);
    EXPECT_EQ(layoutProperty_->GetScrollEnabled(), false);
}

/**
 * @tc.name: Property010
 * @tc.desc: Test ToJsonValue of WaterFlowLayoutProperty.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Property010, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetRowsTemplate("1fr 1fr 1fr");
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(5));
    model.SetColumnsGap(Dimension(10));
    model.SetLayoutDirection(FlexDirection::ROW);
    model.SetItemMinWidth(Dimension(10));
    model.SetItemMinHeight(Dimension(20));
    model.SetItemMaxWidth(Dimension(200));
    model.SetItemMaxHeight(Dimension(500));
    CreateWaterFlowItems();
    CreateDone();

    /**
     * @tc.steps: step2. test function.
     * @tc.expected: function ToJsonValue is called.
     */
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_NE(json, nullptr);

    layoutProperty_->Reset();
    json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: Property011
 * @tc.desc: Test ToJsonValue of WaterFlowLayoutProperty.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Property011, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    CreateWaterFlowItems(TOTAL_LINE_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step2. set valid value.
     * @tc.expected: the value of layoutProperty_ is right.
     */
    const std::string value = "1fr 1fr";
    const Dimension gaps = Dimension(10.f);
    model.SetColumnsTemplate(AceType::RawPtr(frameNode_), value);
    model.SetRowsTemplate(AceType::RawPtr(frameNode_), value);
    model.SetColumnsGap(AceType::RawPtr(frameNode_), gaps);
    model.SetRowsGap(AceType::RawPtr(frameNode_), gaps);

    EXPECT_EQ(layoutProperty_->GetColumnsTemplateValue("1fr"), value);
    EXPECT_EQ(layoutProperty_->GetRowsTemplateValue("1fr"), value);
    EXPECT_EQ(layoutProperty_->GetColumnsGapValue(Dimension(0.f)), gaps);
    EXPECT_EQ(layoutProperty_->GetRowsGapValue(Dimension(0.f)), gaps);

    /**
     * @tc.steps: step3. set invalid value.
     * @tc.expected: the value of layoutProperty_ is right.
     */
    model.SetColumnsTemplate(AceType::RawPtr(frameNode_), "");
    model.SetRowsTemplate(AceType::RawPtr(frameNode_), "");
    model.SetColumnsGap(AceType::RawPtr(frameNode_), -gaps);
    model.SetRowsGap(AceType::RawPtr(frameNode_), -gaps);

    EXPECT_EQ(layoutProperty_->GetColumnsTemplateValue("1fr"), "1fr");
    EXPECT_EQ(layoutProperty_->GetRowsTemplateValue("1fr"), "1fr");
    EXPECT_EQ(layoutProperty_->GetColumnsGapValue(Dimension(0.f)), gaps);
    EXPECT_EQ(layoutProperty_->GetRowsGapValue(Dimension(0.f)), gaps);
}

/**
 * @tc.name: Property012
 * @tc.desc: all the properties of WaterFlow.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Property012, TestSize.Level1)
{
    ViewStackProcessor::GetInstance()->SetVisualState(VisualState::FOCUSED);
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetItemMinWidth(Dimension(10));
    model.SetItemMinHeight(Dimension(10));
    model.SetItemMaxWidth(Dimension(300));
    model.SetItemMaxHeight(Dimension(300));
    CreateWaterFlowItems();
    CreateDone();

    /**
     * @tc.steps: step2. set value when IsCurrentVisualStateProcess is false.
     * @tc.expected: the value not set.
     */
    EXPECT_EQ(layoutProperty_->itemLayoutConstraint_, nullptr);
    ViewStackProcessor::GetInstance()->ClearVisualState();
}

/**
 * @tc.name: Property013
 * @tc.desc: Test the return value of IsReverse.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Property013, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    CreateWaterFlowItems();
    CreateDone();

    /**
     * @tc.steps: step2. set WaterflowDirection and LayoutDirection, test the return value of IsReverse.
     */
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    EXPECT_FALSE(layoutProperty_->IsReverse());

    layoutProperty_->UpdateWaterflowDirection(FlexDirection::COLUMN_REVERSE);
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    EXPECT_TRUE(layoutProperty_->IsReverse());

    layoutProperty_->UpdateWaterflowDirection(FlexDirection::ROW);
    layoutProperty_->UpdateLayoutDirection(TextDirection::LTR);
    EXPECT_FALSE(layoutProperty_->IsReverse());

    layoutProperty_->UpdateWaterflowDirection(FlexDirection::ROW);
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    EXPECT_TRUE(layoutProperty_->IsReverse());

    layoutProperty_->UpdateWaterflowDirection(FlexDirection::ROW_REVERSE);
    layoutProperty_->UpdateLayoutDirection(TextDirection::LTR);
    EXPECT_TRUE(layoutProperty_->IsReverse());

    layoutProperty_->UpdateWaterflowDirection(FlexDirection::ROW_REVERSE);
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    EXPECT_FALSE(layoutProperty_->IsReverse());
}

/**
 * @tc.name: WaterFlowTest001
 * @tc.desc: Fill all items to waterFlow with fixed row and column
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetRowsTemplate("1fr 1fr 1fr");
    model.SetColumnsTemplate("1fr 1fr 1fr");
    CreateWaterFlowItems();
    CreateDone();

    /**
     * @tc.steps: step1. When setting fixed rows and columns, check the status of child nodes in the waterFlow.
     * @tc.expected: All child nodes are active.
     */
    for (int32_t i = 0; i < 9; ++i) {
        EXPECT_TRUE(GetChildFrameNode(frameNode_, i)->IsActive());
    }
}

/**
 * @tc.name: WaterFlowTest002
 * @tc.desc: waterFlow with fixed column
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest002, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    CreateWaterFlowItems();
    CreateDone();

    /**
     * @tc.steps: step1. When setting fixed rows and columns, check the status of child nodes in the waterFlow.
     * @tc.expected: All child nodes are active.
     */
    for (int32_t i = 0; i < 9; ++i) {
        EXPECT_TRUE(GetChildFrameNode(frameNode_, i)->IsActive());
    }
}

/**
 * @tc.name: WaterFlowTest003
 * @tc.desc: waterFlow with fixed column, some waterFlowitem not show
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest003, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(WATER_FLOW_WIDTH));
    ViewAbstract::SetHeight(CalcLength(200.f));
    model.SetColumnsTemplate("1fr 1fr 1fr");
    CreateWaterFlowItems();
    CreateDone();
    FlushLayoutTask(frameNode_);
    auto& info = pattern_->layoutInfo_;
    EXPECT_EQ(info->startIndex_, 0);
    EXPECT_EQ(info->endIndex_, 4);
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 3)->IsActive());
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 4)->IsActive());
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 5)->IsActive());
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 6)->IsActive());
}

/**
 * @tc.name: WaterFlowTest004
 * @tc.desc: waterFlow with fixed column, some waterFlowitem not fully show
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest004, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(WATER_FLOW_WIDTH));
    ViewAbstract::SetHeight(CalcLength(250.f));
    model.SetColumnsTemplate("1fr 1fr 1fr");
    CreateWaterFlowItems();
    CreateDone();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 5)->IsActive());
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 6)->IsActive());
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 7)->IsActive());
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 8)->IsActive());
}

/**
 * @tc.name: WaterFlowTest005
 * @tc.desc: waterFlow with fixed column, scroll to show one more line
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest005, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(WATER_FLOW_WIDTH));
    ViewAbstract::SetHeight(CalcLength(200.f));
    model.SetColumnsTemplate("1fr 1fr 1fr");
    CreateWaterFlowItems();
    CreateDone();
    pattern_->UpdateCurrentOffset(-50.f, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 5)->IsActive());
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 6)->IsActive());
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 7)->IsActive());
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 8)->IsActive());
}

/**
 * @tc.name: WaterFlowTest006
 * @tc.desc: waterFlow with fixed column, scroll to end
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest006, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(WATER_FLOW_WIDTH));
    ViewAbstract::SetHeight(CalcLength(200.f));
    model.SetColumnsTemplate("1fr 1fr 1fr");
    CreateWaterFlowItems();
    CreateDone();
    pattern_->UpdateCurrentOffset(-100.f, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->FirstIdx(), 1);
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 0)->IsActive());
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 1)->IsActive());
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 6)->IsActive());
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 7)->IsActive());
}

/**
 * @tc.name: WaterFlowTest008
 * @tc.desc: waterFlow with fixed column, scroll to index not fully showed at first line
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest008, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(WATER_FLOW_WIDTH));
    ViewAbstract::SetHeight(CalcLength(200.f));
    model.SetColumnsTemplate("1fr 1fr 1fr");
    CreateWaterFlowItems();
    CreateDone();
    pattern_->UpdateStartIndex(1);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 3)->IsActive());
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 4)->IsActive());
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 5)->IsActive());
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 6)->IsActive());
}

/**
 * @tc.name: WaterFlowTest009
 * @tc.desc: waterFlow with fixed column, scroll to index fully showed
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest009, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(WATER_FLOW_WIDTH));
    ViewAbstract::SetHeight(CalcLength(200.f));
    model.SetColumnsTemplate("1fr 1fr 1fr");
    CreateWaterFlowItems();
    CreateDone();
    pattern_->UpdateStartIndex(3);
    FlushLayoutTask(frameNode_);
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 0)->IsActive());
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 1)->IsActive());
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 6)->IsActive());
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 7)->IsActive());
}

/**
 * @tc.name: WaterFlowTest010
 * @tc.desc: waterFlow with fixed column, scroll to index out of view
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest010, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(WATER_FLOW_WIDTH));
    ViewAbstract::SetHeight(CalcLength(200.f));
    model.SetColumnsTemplate("1fr 1fr 1fr");
    CreateWaterFlowItems();
    CreateDone();
    pattern_->UpdateStartIndex(9);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 9)->IsActive());

    pattern_->UpdateStartIndex(0);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 0)->IsActive());
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 9)->IsActive());
}

/**
 * @tc.name: WaterFlowTest011
 * @tc.desc: Test GetOverScrollOffset
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest011, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr");
    CreateWaterFlowItems();
    CreateDone();

    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE), { ITEM_MAIN_SIZE, 0 }));
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(0.f), { 0, 0 }));
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE), { 0, 0 }));

    UpdateCurrentOffset(-ITEM_MAIN_SIZE);
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE * 2), { 0, 0 }));
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(0.f), { 0, 0 }));
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE * 2), { 0, 0 }));

    UpdateCurrentOffset(-WATER_FLOW_HEIGHT);
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE), { 0, 0 }));
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(0.f), { 0, 0 }));
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE), { 0, -ITEM_MAIN_SIZE }));

    // enable overScroll
    pattern_->SetEdgeEffect(EdgeEffect::SPRING);
    pattern_->animateOverScroll_ = true;
    pattern_->layoutInfo_->startIndex_ = 0;
    // total offset = ITEM_MAIN_SIZE
    pattern_->layoutInfo_->UpdateOffset(WATER_FLOW_HEIGHT);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE), { ITEM_MAIN_SIZE, 0 }));
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(0.f), { 0, 0 }));
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE * 2), { -ITEM_MAIN_SIZE, 0 }));

    // total offset = -ITEM_MAIN_SIZE * 3
    pattern_->layoutInfo_->UpdateOffset(-ITEM_MAIN_SIZE * 4);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE * 2), { 0, 0 }));
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(0.f), { 0, 0 }));
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE), { 0, 0 }));
}

/**
 * @tc.name: WaterFlowTest013
 * @tc.desc: Test direction
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create waterFlow with the RTL direction.
     * @tc.expected: layout from right to left.
     */
    WaterFlowModelNG model = CreateWaterFlow();
    ViewAbstract::SetLayoutDirection(TextDirection::RTL);
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(TOTAL_LINE_NUMBER);
    CreateDone();
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(0), Rect(WATER_FLOW_WIDTH / 2, 0, WATER_FLOW_WIDTH / 2, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(1), Rect(0, 0, WATER_FLOW_WIDTH / 2, BIG_ITEM_MAIN_SIZE)));

    layoutProperty_->UpdateLayoutDirection(TextDirection::LTR);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(0), Rect(0, 0, WATER_FLOW_WIDTH / 2, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(
        IsEqual(pattern_->GetItemRect(1), Rect(WATER_FLOW_WIDTH / 2, 0, WATER_FLOW_WIDTH / 2, BIG_ITEM_MAIN_SIZE)));
}

/**
 * @tc.name: WaterFlowTest014
 * @tc.desc: Test direction
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create waterFlow with the RTL direction.
     * @tc.expected: layout from right to left.
     */
    WaterFlowModelNG model = CreateWaterFlow();
    ViewAbstract::SetLayoutDirection(TextDirection::RTL);
    ViewAbstract::SetWidth(CalcLength(620));
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetRowsGap(Dimension(5));
    model.SetColumnsGap(Dimension(10));
    CreateWaterFlowItems(TOTAL_LINE_NUMBER);
    CreateDone();
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(0), Rect(420.0f, 0, 200.0f, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(1), Rect(210.0f, 0, 200.0f, BIG_ITEM_MAIN_SIZE)));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(2), Rect(0.0f, 0, 200.0f, ITEM_MAIN_SIZE)));

    layoutProperty_->UpdateLayoutDirection(TextDirection::LTR);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(0), Rect(0.0f, 0, 200.0f, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(1), Rect(210.0f, 0, 200.0f, BIG_ITEM_MAIN_SIZE)));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(2), Rect(420.0f, 0, 200.0f, ITEM_MAIN_SIZE)));
}

/**
 * @tc.name: WaterFlowTest015
 * @tc.desc: In less-than fillViewport scene, test GetOverScrollOffset.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest015, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateWaterFlowItems(2);
    CreateDone();
    EXPECT_FALSE(NEAR_ZERO(pattern_->layoutInfo_->GetContentHeight()));
    EXPECT_LT(pattern_->layoutInfo_->GetContentHeight(), pattern_->layoutInfo_->lastMainSize_);

    /**
     * @tc.steps: step1. input a delta(>0), make overScroll at top.
     * @tc.expected: offset.start is equal to this delta, offset.end is zero.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(100.0f), { 100.0f, 0 }));

    /**
     * @tc.steps: step2. input a delta(<0), make overScroll at bottom.
     * @tc.expected: offset.start is zero, offset.end is equal to this delta.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(-100.f), { 0, -100.f }));

    // enable overScroll, layout in overScroll status at top.
    pattern_->SetAnimateCanOverScroll(true);
    pattern_->layoutInfo_->UpdateOffset(100.0f);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(GetChildY(frameNode_, 0), 100.0f);

    /**
     * @tc.steps: step1. input a delta(>0), make overScroll at top.
     * @tc.expected: offset.start is equal to this delta, offset.end is zero.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(100.0f), { 100.0f, 0 }));

    /**
     * @tc.steps: step2. input a delta(<0), make overScroll at top.
     * @tc.expected: offset.start is equal to this delta, offset.end is zero.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(-100.0f), { -100.0f, 0 }));

    /**
     * @tc.steps: step3. input a delta(<0), make overScroll at bottom.
     * @tc.expected: offset.start is equal to overScroll offset at top, offset.end is equal to overScroll offset at
     * bottom.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(-400.0f), { -100.0f, -300.0f }));

    // layout in overScroll status at bottom.
    pattern_->layoutInfo_->UpdateOffset(-150.0f);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(GetChildY(frameNode_, 0), -50.0f);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);

    /**
     * @tc.steps: step1. input a delta(>0), make overScroll at bottom.
     * @tc.expected: offset.start is zero, offset.end is equal to this delta.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(20.0f), { 0, 20.0f }));

    /**
     * @tc.steps: step2. input a delta(<0), make overScroll at bottom.
     * @tc.expected: offset.start is equal to this delta, offset.end is zero.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(-100.0f), { 0, -100.0f }));

    /**
     * @tc.steps: step3. input a delta(>0), make overScroll at top.
     * @tc.expected: offset.start is equal to overScroll offset at top, offset.end is equal to overScroll offset at
     * bottom.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(400.0f), { 350.0f, 50.0f }));
}

namespace {
constexpr float SCROLL_FIXED_VELOCITY_005 = 400.f;
constexpr float OFFSET_TIME_005 = 100.f;
constexpr int32_t TIME_CHANGED_COUNTS_005 = 20;
} // namespace
/**
 * @tc.name: PositionController005
 * @tc.desc: Test PositionController ScrollBy
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, PositionController005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List Item
     */
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * 2);
    CreateDone();
    auto controller = pattern_->positionController_;

    /**
     * @tc.steps: step2. Scroll to the left edge
     * expected: Return fixed verify
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_LEFT, SCROLL_FIXED_VELOCITY_005);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);

    /**
     * @tc.steps: step3. Scroll to the right edge
     * expected: Return fixed verify
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_RIGHT, SCROLL_FIXED_VELOCITY_005);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);

    /**
     * @tc.steps: step4. Scroll to the bottom edge
     * expected: 1.Return fixed verify
     * expected: 2.The current Velocity is equal to the set fixed velocity
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, SCROLL_FIXED_VELOCITY_005);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), -SCROLL_FIXED_VELOCITY_005);

    /**
     * @tc.steps: step5. 1. Set offset time
     *                   2. Set changed count
     *                   3. Flush layout
     * expected: Scroll to the bottom edge
     */
    int32_t offsetTime = OFFSET_TIME_005;
    for (int i = 0; i < TIME_CHANGED_COUNTS_005; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME_005;
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtBottom());

    /**
     * @tc.steps: step6. Scroll to the top edge
     * expected: 1.Fixed Verify is is non-zero.
     *           2.The current Velocity is equal to the set fixed velocity
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, SCROLL_FIXED_VELOCITY_005);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), SCROLL_FIXED_VELOCITY_005);

    /**
     * @tc.steps: step7. 1. Set offset time
     *                   2. Set changed count
     *                   3. Flush layout
     * expected: Scroll to the top edge
     */
    offsetTime = OFFSET_TIME_005;
    for (int i = 0; i < TIME_CHANGED_COUNTS_005; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME_005;
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtTop());

    /**
     * @tc.steps: step8. Test ScrollBy
     */
    ScrollBy(0, ITEM_MAIN_SIZE, true);
    EXPECT_TRUE(Position(-ITEM_MAIN_SIZE));
    EXPECT_EQ(controller->GetCurrentOffset().GetY(), ITEM_MAIN_SIZE);
}

namespace {
constexpr float SCROLL_FIXED_VELOCITY_006 = 300.f;
constexpr float OFFSET_TIME_006 = 200.f;
constexpr int32_t TIME_CHANGED_COUNTS_006 = 30;
} // namespace
/**
 * @tc.name: PositionController006
 * @tc.desc: Test PositionController AnimateTo
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, PositionController006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List Item
     */
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * 2);
    CreateDone();
    auto controller = pattern_->positionController_;

    /**
     * @tc.steps: step2. Scroll to the left edge
     * expected: Return fixed verify
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_LEFT, SCROLL_FIXED_VELOCITY_006);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);

    /**
     * @tc.steps: step3. Scroll to the right edge
     * expected: Return fixed verify
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_RIGHT, SCROLL_FIXED_VELOCITY_006);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);

    /**
     * @tc.steps: step4. Scroll to the bottom edge
     * expected: 1.Return fixed verify
     * expected: 2.The current Velocity is equal to the set fixed velocity
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, SCROLL_FIXED_VELOCITY_006);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), -SCROLL_FIXED_VELOCITY_006);

    /**
     * @tc.steps: step5. 1. Set offset time
     *                   2. Set changed count
     *                   3. Flush layout
     * expected: Scroll to the bottom edge
     */
    int32_t offsetTime = OFFSET_TIME_006;
    for (int i = 0; i < TIME_CHANGED_COUNTS_006; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME_006;
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtBottom());

    /**
     * @tc.steps: step6. Scroll to the top edge
     * expected: 1.Fixed Verify is is non-zero.
     *           2.The current Velocity is equal to the set fixed velocity
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, SCROLL_FIXED_VELOCITY_006);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), SCROLL_FIXED_VELOCITY_006);

    /**
     * @tc.steps: step7. 1. Set offset time
     *                   2. Set changed count
     *                   3. Flush layout
     * expected: Scroll to the top edge
     */
    offsetTime = OFFSET_TIME_006;
    for (int i = 0; i < TIME_CHANGED_COUNTS_006; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME_006;
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtTop());
}

namespace {
constexpr float SCROLL_FIXED_VELOCITY_007 = 400.f;
constexpr float OFFSET_TIME_007 = 300.f;
constexpr int32_t TIME_CHANGED_COUNTS_007 = 40;
} // namespace
/**
 * @tc.name: PositionController007
 * @tc.desc: Test PositionController ScrollPage
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, PositionController007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List Item
     */
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * 2);
    CreateDone();
    auto controller = pattern_->positionController_;

    /**
     * @tc.steps: step2. Scroll to the left edge
     * expected: Return fixed verify
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_LEFT, SCROLL_FIXED_VELOCITY_007);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);

    /**
     * @tc.steps: step3. Scroll to the right edge
     * expected: Return fixed verify
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_RIGHT, SCROLL_FIXED_VELOCITY_007);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);

    /**
     * @tc.steps: step4. Scroll to the bottom edge
     * expected: 1.Return fixed verify
     * expected: 2.The current Velocity is equal to the set fixed velocity
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, SCROLL_FIXED_VELOCITY_007);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), -SCROLL_FIXED_VELOCITY_007);

    /**
     * @tc.steps: step5. 1. Set offset time
     *                   2. Set changed count
     *                   3. Flush layout
     * expected: Scroll to the bottom edge
     */
    int32_t offsetTime = OFFSET_TIME_007;
    for (int i = 0; i < TIME_CHANGED_COUNTS_007; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME_007;
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtBottom());

    /**
     * @tc.steps: step6. Scroll to the top edge
     * expected: 1.Fixed Verify is is non-zero.
     *           2.The current Velocity is equal to the set fixed velocity
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, SCROLL_FIXED_VELOCITY_007);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), SCROLL_FIXED_VELOCITY_007);

    /**
     * @tc.steps: step7. 1. Set offset time
     *                   2. Set changed count
     *                   3. Flush layout
     * expected: Scroll to the top edge
     */
    offsetTime = OFFSET_TIME_007;
    for (int i = 0; i < TIME_CHANGED_COUNTS_007; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME_007;
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtTop());
}

namespace {
constexpr float SCROLL_FIXED_VELOCITY_008 = 500.f;
constexpr float OFFSET_TIME_008 = 100.f;
constexpr int32_t TIME_CHANGED_COUNTS_008 = 50;
} // namespace
/**
 * @tc.name: PositionController008
 * @tc.desc: Test PositionController ActActionScrollForward
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, PositionController008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List Item
     */
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * 2);
    CreateDone();
    auto controller = pattern_->positionController_;

    /**
     * @tc.steps: step2. Scroll to the left edge
     * expected: Return fixed verify
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_LEFT, SCROLL_FIXED_VELOCITY_008);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);

    /**
     * @tc.steps: step3. Scroll to the right edge
     * expected: Return fixed verify
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_RIGHT, SCROLL_FIXED_VELOCITY_008);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);

    /**
     * @tc.steps: step4. Scroll to the bottom edge
     * expected: 1.Return fixed verify
     * expected: 2.The current Velocity is equal to the set fixed velocity
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, SCROLL_FIXED_VELOCITY_008);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), -SCROLL_FIXED_VELOCITY_008);

    /**
     * @tc.steps: step5. 1. Set offset time
     *                   2. Set changed count
     *                   3. Flush layout
     * expected: Scroll to the bottom edge
     */
    int32_t offsetTime = OFFSET_TIME_008;
    for (int i = 0; i < TIME_CHANGED_COUNTS_008; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME_008;
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtBottom());

    /**
     * @tc.steps: step6. Scroll to the top edge
     * expected: 1.Fixed Verify is is non-zero.
     *           2.The current Velocity is equal to the set fixed velocity
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, SCROLL_FIXED_VELOCITY_008);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), SCROLL_FIXED_VELOCITY_008);

    /**
     * @tc.steps: step7. 1. Set offset time
     *                   2. Set changed count
     *                   3. Flush layout
     * expected: Scroll to the top edge
     */
    offsetTime = OFFSET_TIME_008;
    for (int i = 0; i < TIME_CHANGED_COUNTS_008; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME_008;
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtTop());
}

namespace {
constexpr float SCROLL_FIXED_VELOCITY_009 = 600.f;
constexpr float OFFSET_TIME_009 = 200.f;
constexpr int32_t TIME_CHANGED_COUNTS_009 = 60;
} // namespace
/**
 * @tc.name: PositionController009
 * @tc.desc: Test PositionController event
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, PositionController009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List Item
     */
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * 2);
    CreateDone();
    auto controller = pattern_->positionController_;

    /**
     * @tc.steps: step2. Scroll to the left edge
     * expected: Return fixed verify
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_LEFT, SCROLL_FIXED_VELOCITY_009);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);

    /**
     * @tc.steps: step3. Scroll to the right edge
     * expected: Return fixed verify
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_RIGHT, SCROLL_FIXED_VELOCITY_009);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);

    /**
     * @tc.steps: step4. Scroll to the bottom edge
     * expected: 1.Return fixed verify
     * expected: 2.The current Velocity is equal to the set fixed velocity
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, SCROLL_FIXED_VELOCITY_009);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), -SCROLL_FIXED_VELOCITY_009);

    /**
     * @tc.steps: step5. 1. Set offset time
     *                   2. Set changed count
     *                   3. Flush layout
     * expected: Scroll to the bottom edge
     */
    int32_t offsetTime = OFFSET_TIME_009;
    for (int i = 0; i < TIME_CHANGED_COUNTS_009; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME_009;
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtBottom());

    /**
     * @tc.steps: step6. Scroll to the top edge
     * expected: 1.Fixed Verify is is non-zero.
     *           2.The current Velocity is equal to the set fixed velocity
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, SCROLL_FIXED_VELOCITY_009);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), SCROLL_FIXED_VELOCITY_009);

    /**
     * @tc.steps: step7. 1. Set offset time
     *                   2. Set changed count
     *                   3. Flush layout
     * expected: Scroll to the top edge
     */
    offsetTime = OFFSET_TIME_009;
    for (int i = 0; i < TIME_CHANGED_COUNTS_009; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME_009;
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtTop());
}

/**
 * @tc.name: WaterFlowPatternTest001
 * @tc.desc: Test water flow pattern func
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowPatternTest001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * 4);
    CreateDone();

    /**
     * @tc.steps: step1. Run pattern func.
     * @tc.expected: The return_value is correct.
     */
    EXPECT_TRUE(pattern_->IsScrollable());
    EXPECT_TRUE(pattern_->IsAtTop());
    EXPECT_FALSE(pattern_->IsAtBottom());

    /**
     * @tc.steps: step2. Scroll to bottom
     */
    UpdateCurrentOffset(-WATER_FLOW_HEIGHT);
    EXPECT_FALSE(pattern_->IsAtTop());
    EXPECT_TRUE(pattern_->IsAtBottom());
}

/**
 * @tc.name: WaterFlowPatternTest002
 * @tc.desc: Test water flow pattern func
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowPatternTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create waterFlow
     * @tc.expected: startIndex_ = 0  endIndex_ = 21
     */
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetLayoutDirection(FlexDirection::COLUMN_REVERSE);
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * 4);
    CreateDone();
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 21);

    /**
     * @tc.steps: step2. UpdateCurrentOffset -100.f.
     * @tc.expected: startIndex_ = 0  endIndex_ = 21.
     */
    HandleDrag(-100.f);
    pattern_->UpdateScrollBarOffset();
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), 0.f);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 21);

    /**
     * @tc.steps: step3. UpdateCurrentOffset 200.f.
     * @tc.expected: startIndex_ = 5  endIndex_ = 27.
     */
    HandleDrag(200.f);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -ITEM_MAIN_SIZE * 2);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 5);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 27);
}

/**
 * @tc.name: WaterFlowPatternTest003
 * @tc.desc: Test water flow pattern OutBoundaryCallback
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowPatternTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create waterFlow
     * @tc.expected: OutBoundaryCallback() return false
     */
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems();
    CreateDone();
    EXPECT_FALSE(pattern_->OutBoundaryCallback());
}

/**
 * @tc.name: WaterFlowAccessibilityTest001
 * @tc.desc: Test Accessibility func
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowAccessibilityTest001, TestSize.Level1)
{
    float colNumber = 4;
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * colNumber);
    CreateDone();

    /**
     * @tc.steps: step1. Run Accessibility func.
     * @tc.expected: The return_value is correct.
     */
    EXPECT_EQ(accessibilityProperty_->GetBeginIndex(), 0);
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), 21);
    EXPECT_EQ(accessibilityProperty_->GetCollectionItemCounts(), TOTAL_LINE_NUMBER * colNumber);
    AceCollectionInfo info = accessibilityProperty_->GetCollectionInfo();
    EXPECT_EQ(info.rows, 6);
    EXPECT_EQ(info.columns, colNumber);

    /**
     * @tc.steps: step2. Scroll to Top.
     * @tc.expected: Verify return value.
     */
    UpdateCurrentOffset(ITEM_MAIN_SIZE);
    accessibilityProperty_->ResetSupportAction();
    uint64_t exptectActions_1 = 0;
    exptectActions_1 |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), exptectActions_1);

    /**
     * @tc.steps: step3. Scroll to middle.
     * @tc.expected: Verify return value.
     */
    UpdateCurrentOffset(-ITEM_MAIN_SIZE);
    accessibilityProperty_->ResetSupportAction();
    uint64_t exptectActions_2 = 0;
    exptectActions_2 |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    exptectActions_2 |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), exptectActions_2);

    /**
     * @tc.steps: step4. Scroll to bottom.
     * @tc.expected: Verify return value.
     */
    UpdateCurrentOffset(-WATER_FLOW_HEIGHT);
    accessibilityProperty_->ResetSupportAction();
    uint64_t exptectActions_3 = 0;
    exptectActions_3 |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), exptectActions_3);

    /**
     * @tc.steps: step5. UnScrollable.
     * @tc.expected: Verify return value.
     */
    ClearOldNodes();
    model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateWaterFlowItems(1);
    CreateDone();
    accessibilityProperty_->ResetSupportAction();
    uint64_t exptectActions_4 = 0;
    EXPECT_EQ(GetActions(accessibilityProperty_), exptectActions_4);
}

/**
 * @tc.name: WaterFlowAccessibilityTest002
 * @tc.desc: Test Accessibility func
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowAccessibilityTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Run Accessibility func.
     * @tc.expected: Will trigger ScrollPage func
     */
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * 2);
    CreateDone();
    accessibilityProperty_->ActActionScrollForward();
    MockAnimationManager::GetInstance().Tick();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(Position(-WATER_FLOW_HEIGHT));
    accessibilityProperty_->ActActionScrollBackward();
    MockAnimationManager::GetInstance().Tick();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(Position(0));
}

/**
 * @tc.name: ScrollPage001
 * @tc.desc: Test ScrollPage func
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, ScrollPage001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * 2);
    CreateDone();
    auto controller = pattern_->positionController_;
    controller->ScrollPage(false, false);
    FlushUITasks();
    EXPECT_TRUE(Position(-WATER_FLOW_HEIGHT));
    EXPECT_EQ(controller->GetCurrentOffset().GetY(), WATER_FLOW_HEIGHT);
    EXPECT_EQ(accessibilityProperty_->GetScrollOffSet(), pattern_->GetTotalOffset());
    EXPECT_TRUE(controller->IsAtEnd());
}

/**
 * @tc.name: WaterFlowFooterTest001
 * @tc.desc: Test Footer func
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowFooterTest001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    auto footer = GetDefaultHeaderBuilder();
    model.SetFooter(std::move(footer));
    CreateWaterFlowItems(5);
    CreateDone();

    /**
     * @tc.steps: step1. Run footer func.
     * @tc.expected: The return_value is correct.
     */
    auto footerRect = GetChildRect(frameNode_, pattern_->layoutInfo_->footerIndex_);
    EXPECT_FLOAT_EQ(footerRect.GetY(), 200.f);
}

/**
 * @tc.name: WaterFlowFooterTest002
 * @tc.desc: Test Footer func
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowFooterTest002, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    auto footer = nullptr;
    model.SetFooter(std::move(footer));
    CreateWaterFlowItems(5);
    CreateDone();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: Callback001
 * @tc.desc: Test scroll callback
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Callback001, TestSize.Level1)
{
    bool isReachStartCalled = false;
    bool isReachEndCalled = false;
    auto reachStart = [&isReachStartCalled]() { isReachStartCalled = true; };
    auto reachEnd = [&isReachEndCalled]() { isReachEndCalled = true; };
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetOnReachStart(reachStart);
    model.SetOnReachEnd(reachEnd);
    CreateWaterFlowItems();
    CreateDone();

    /**
     * @tc.steps: step1. init will trigger once
     */
    EXPECT_TRUE(isReachStartCalled);
    isReachStartCalled = false;

    /**
     * @tc.steps: step2. Scroll down to end
     * @tc.expected: Trigger reachend
     */
    UpdateCurrentOffset(-WATER_FLOW_HEIGHT);
    EXPECT_TRUE(pattern_->layoutInfo_->offsetEnd_);
    EXPECT_TRUE(isReachEndCalled);

    /**
     * @tc.steps: step3. Scroll up to start
     * @tc.expected: Trigger reachstart
     */
    UpdateCurrentOffset(WATER_FLOW_HEIGHT);
    EXPECT_TRUE(isReachStartCalled);
}

/**
 * @tc.name: Callback002
 * @tc.desc: Test EdgeEffectCallback
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Callback002, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, false);
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * 2);
    CreateDone();

    auto gestureHub = pattern_->GetGestureHub();
    auto axis = pattern_->GetAxis();
    ASSERT_NE(gestureHub->scrollableActuator_, nullptr);
    EXPECT_EQ(axis, Axis::VERTICAL);
    auto effect = gestureHub->scrollableActuator_->scrollEffects_[axis];

    EXPECT_EQ(effect->leadingCallback_(), 0);
    EXPECT_EQ(effect->initLeadingCallback_(), 0);
    EXPECT_EQ(effect->currentPositionCallback_(), 0);

    pattern_->SetAlwaysEnabled(true);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(effect->leadingCallback_(), 0);
    EXPECT_EQ(effect->initLeadingCallback_(), 0);
    EXPECT_EQ(effect->currentPositionCallback_(), 0);

    pattern_->layoutInfo_->Reset();
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(effect->leadingCallback_(), 0);
    EXPECT_EQ(effect->initLeadingCallback_(), 0);
    EXPECT_EQ(effect->currentPositionCallback_(), 0);
}

/**
 * @tc.name: WaterFlowSetFriction001
 * @tc.desc: Test SetFriction. friction shouled be more than 0.0,if out of range,should be default value.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowSetFriction001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetFriction(0);
    CreateWaterFlowItems();
    CreateDone();
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), DEFAULT_FRICTION);
    model = CreateWaterFlow();
    model.SetFriction(-1);
    CreateWaterFlowItems();
    CreateDone();
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), DEFAULT_FRICTION);
    model = CreateWaterFlow();
    model.SetFriction(1);
    CreateWaterFlowItems();
    CreateDone();
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), 1);
}

/**
 * @tc.name: WaterFlowPattern_distributed001
 * @tc.desc: Test the distributed capability of WaterFlow.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowPattern_distributed001, TestSize.Level1)
{
    CreateWaterFlow();
    CreateDone();

    // need dpi to be 1
    /**
     * @tc.steps: step2. get pattern .
     * @tc.expected: function ProvideRestoreInfo is called.
     */
    pattern_->layoutInfo_->startIndex_ = 1;
    pattern_->layoutInfo_->storedOffset_ = 1.0f;
    std::string ret = pattern_->ProvideRestoreInfo();

    /**
     * @tc.steps: step3. function OnRestoreInfo is called.
     * @tc.expected: Passing JSON format.
     */
    // std::string restoreInfo = R"({"beginIndex":1,"offset":1.1})";
    pattern_->OnRestoreInfo(ret);
    EXPECT_EQ(pattern_->layoutInfo_->jumpIndex_, 1);
    EXPECT_DOUBLE_EQ(pattern_->layoutInfo_->restoreOffset_, 1.0f);
}

/**
 * @tc.name: WaterFlowContentModifier_onDraw001
 * @tc.desc: Test onDraw.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowContentModifier_onDraw001, TestSize.Level1)
{
    CreateWaterFlow();
    CreateDone();

    /**
     * @tc.steps: step2. Init contentModifier
     */
    pattern_->CreateNodePaintMethod();
    auto contentModifier = pattern_->contentModifier_;
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, ClipRect(_, _, _)).Times(AtLeast(1));
    DrawingContext context = { canvas, 1.f, 1.f };

    /**
     * @tc.steps: step3. test function.
     * @tc.expected: function onDraw is called.
     */
    contentModifier->SetClip(true);
    contentModifier->onDraw(context);
    EXPECT_EQ(contentModifier->clip_->Get(), true);

    contentModifier->SetClip(false);
    contentModifier->onDraw(context);
    EXPECT_EQ(contentModifier->clip_->Get(), false);
}

/**
 * @tc.name: WaterFlowPattern_OnDirtyLayoutWrapperSwap001
 * @tc.desc: Test OnDirtyLayoutWrapperSwap.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowPattern_OnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    CreateWaterFlow();
    CreateWaterFlowItems(TOTAL_LINE_NUMBER);
    CreateDone();
    pattern_->SetPositionController(nullptr);
    pattern_->AddScrollEvent();
    EXPECT_NE(pattern_->scrollableEvent_, nullptr);
    pattern_->OnModifyDone();
    EXPECT_FALSE(pattern_->CanOverScroll(SCROLL_FROM_UPDATE));

    /**
     * @tc.steps: step2. test function.
     * @tc.expected: function OnDirtyLayoutWrapperSwap is called.
     */
    auto geometryNode = frameNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    ASSERT_NE(layoutWrapper, nullptr);
    DirtySwapConfig config;
    config.skipLayout = true;
    config.skipMeasure = false;
    EXPECT_EQ(pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, config), false);

    config.skipLayout = false;
    config.skipMeasure = true;
    EXPECT_EQ(pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, config), false);
}

/**
 * @tc.name: WaterFlowGetItemRectTest001
 * @tc.desc: Test WaterFlow GetItemRect function.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowGetItemRectTest001, TestSize.Level1)
{
    float colNumber = 4;
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * colNumber);
    CreateDone();

    /**
     * @tc.steps: step2. Get invalid WaterFlowItem Rect.
     * @tc.expected: Return 0 when input invalid index.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(-1), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(32), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(33), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(39), Rect()));

    /**
     * @tc.steps: step3. Get valid WaterFlowItem Rect.
     * @tc.expected: Return actual Rect when input valid index.
     */
    float itemWidth = WATER_FLOW_WIDTH / colNumber;
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(0), Rect(0, 0, itemWidth, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(5), Rect(itemWidth * 2, ITEM_MAIN_SIZE, itemWidth, BIG_ITEM_MAIN_SIZE)));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(10), Rect(itemWidth * 2, ITEM_MAIN_SIZE * 3, itemWidth, ITEM_MAIN_SIZE)));
}

/**
 * @tc.name: WaterFlowGetItemIndexTest001
 * @tc.desc: Test WaterFlow GetItemIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowGetItemIndexTest001, TestSize.Level1)
{
    float colNumber = 4;
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * colNumber);
    CreateDone();

    /**
     * @tc.steps: step1. Get invalid WaterFlowItem index.
     * @tc.expected: Return -1 when input invalid x and y coordinate.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetItemIndex(1000000, -1000000), -1));

    /**
     * @tc.steps: step2. Get valid WaterFlowItem index.
     * @tc.expected: Return actual index when input valid x and y coordinate.
     */
    float itemWidth = WATER_FLOW_WIDTH / colNumber;
    EXPECT_TRUE(IsEqual(pattern_->GetItemIndex(itemWidth / 2, ITEM_MAIN_SIZE / 2), 0));
}

/**
 * @tc.name: MeasureForAnimation001
 * @tc.desc: Test WaterFlow MeasureForAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, MeasureForAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create WithItem to test MeaseForAnimation for node creation .
     * @tc.expected: pattern_->layoutInfo_ There is corresponding index information in it.
     */
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * 2);
    CreateDone();
    pattern_->ScrollToIndex(15, true);

    /**
     * @tc.steps: step2. Get value from  pattern_ -> LayoutInfo_ .
     * @tc.expected: return value(crossIndex) is not -1.
     */
    auto crossIndex = pattern_->layoutInfo_->GetCrossIndex(10);
    EXPECT_FALSE(IsEqual(crossIndex, -1));
}

/**
 * @tc.name: Illegal001
 * @tc.desc: Test illegal columns template
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Illegal001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("a");
    model.SetFooter(GetDefaultHeaderBuilder());
    CreateWaterFlowItems(20);
    CreateDone();
    EXPECT_EQ(GetChildWidth(frameNode_, 1), WATER_FLOW_WIDTH);
    EXPECT_EQ(GetChildWidth(frameNode_, 2), WATER_FLOW_WIDTH);
    EXPECT_EQ(GetChildX(frameNode_, 1), 0.0f);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 5);
}

/**
 * @tc.name: Reverse001
 * @tc.desc: Test reverse layout
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Reverse001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("a");
    CreateWaterFlowItems(20);
    CreateDone();
    layoutProperty_->UpdateWaterflowDirection(FlexDirection::COLUMN_REVERSE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(GetChildY(frameNode_, 0), 700.0f);
    EXPECT_EQ(GetChildY(frameNode_, 1), 500.0f);
    EXPECT_EQ(GetChildY(frameNode_, 2), 400.0f);
    EXPECT_EQ(GetChildY(frameNode_, 3), 200.0f);
    EXPECT_EQ(GetChildY(frameNode_, 4), 100.0f);
    EXPECT_EQ(GetChildY(frameNode_, 5), -100.0f);
}

/**
 * @tc.name: MarginPadding001
 * @tc.desc: Test margin/padding
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, MarginPadding001, TestSize.Level1)
{
    ColumnModelNG colModel;
    colModel.Create(Dimension(0), nullptr, "");
    auto colNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(4);
    CreateDone();

    MarginProperty margin = { CalcLength(1), CalcLength(3), CalcLength(5), CalcLength(7) };
    PaddingProperty padding = { CalcLength(2), CalcLength(4), CalcLength(6), CalcLength(8) };
    layoutProperty_->UpdateMargin(margin);
    layoutProperty_->UpdatePadding(padding);
    auto itemLayoutProperty = GetChildLayoutProperty<WaterFlowItemLayoutProperty>(frameNode_, 2);
    itemLayoutProperty->UpdateMargin(margin);
    itemLayoutProperty->UpdatePadding(padding);
    FlushLayoutTask(colNode, true);
    EXPECT_TRUE(IsEqual(frameNode_->GetGeometryNode()->GetFrameRect(), RectF(1, 5, 480, 800)));
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 2), RectF(3, 111, 237, 100)));
}

/**
 * @tc.name: WaterFlowTest019
 * @tc.desc: Test layout when update offset repeatedly in one frame.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest019, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(WATER_FLOW_WIDTH));
    ViewAbstract::SetHeight(CalcLength(600.f));
    model.SetColumnsTemplate("1fr 1fr");
    for (int i = 0; i < 30; ++i) {
        CreateItemWithHeight(100.0f);
    }
    CreateDone();

    UpdateCurrentOffset(-500.0f);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 10);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 21);

    pattern_->UpdateCurrentOffset(-10.0f, SCROLL_FROM_UPDATE);
    pattern_->UpdateCurrentOffset(20.0f, SCROLL_FROM_UPDATE);
    pattern_->UpdateCurrentOffset(-5.0f, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 8);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 21);
    for (int32_t i = 8; i <= 21; i++) {
        EXPECT_TRUE(IsEqual(pattern_->GetItemRect(i),
            Rect(i % 2 == 0 ? 0 : WATER_FLOW_WIDTH / 2, -95.0f + 100.f * ((i - 8) / 2), WATER_FLOW_WIDTH / 2, 100.0f)));
    }

    pattern_->UpdateCurrentOffset(10.0f, SCROLL_FROM_UPDATE);
    pattern_->UpdateCurrentOffset(-25.0f, SCROLL_FROM_UPDATE);
    pattern_->UpdateCurrentOffset(5.0f, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 10);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 23);
    for (int32_t i = 10; i <= 23; i++) {
        EXPECT_TRUE(IsEqual(pattern_->GetItemRect(i),
            Rect(i % 2 == 0 ? 0 : WATER_FLOW_WIDTH / 2, -5.0f + 100.f * ((i - 10) / 2), WATER_FLOW_WIDTH / 2, 100.0f)));
    }
}

/**
 * @tc.name: Jump001
 * @tc.desc: Test jump function after changing dataSource.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Jump001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(30);
    CreateDone();

    AddItemsAtSlot(1, 100.0f, 15);
    frameNode_->ChildrenUpdatedFrom(15);
    ScrollToIndex(15, false, ScrollAlign::START);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 15);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 25);
    EXPECT_EQ(GetChildY(frameNode_, 15), 0.0f);

    AddItemsAtSlot(1, 100.0f, 0);
    frameNode_->ChildrenUpdatedFrom(0);
    ScrollToIndex(0, false, ScrollAlign::START);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 11);
    EXPECT_EQ(GetChildY(frameNode_, 0), 0.0f);
}

/**
 * @tc.name: Delete001
 * @tc.desc: Test layout after deleting all items on the screen.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Delete001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(43);
    CreateDone();

    pattern_->isAnimationStop_ = false;
    UpdateCurrentOffset(-4000.0f);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 31);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 42);

    // delete all items on the screen.
    for (int i = 42; i > 30; i--) {
        frameNode_->RemoveChildAtIndex(i);
        frameNode_->ChildrenUpdatedFrom(i);
    }
    frameNode_->ChildrenUpdatedFrom(31);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(frameNode_);

    // should layout at the end.
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 30);
    EXPECT_EQ(GetChildRect(frameNode_, 30).Bottom(), WATER_FLOW_HEIGHT);
}
} // namespace OHOS::Ace::NG
