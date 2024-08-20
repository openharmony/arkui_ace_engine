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

#include "tabs_test_ng.h"

#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/common/agingadapation/aging_adapation_dialog_theme.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components/tab_bar/tab_theme.h"
#include "core/components_ng/pattern/linear_layout/column_model_ng.h"

namespace OHOS::Ace::NG {
namespace {}

void TabsTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(dialogTheme));
    auto agingAdapationDialogTheme = AceType::MakeRefPtr<AgingAdapationDialogTheme>();
    EXPECT_CALL(*themeManager, GetTheme(AgingAdapationDialogTheme::TypeId()))
        .WillRepeatedly(Return(agingAdapationDialogTheme));
    agingAdapationDialogTheme->bigFontSizeScale_ = BIG_FONT_SIZE_SCALE;
    agingAdapationDialogTheme->largeFontSizeScale_ = LARGE_FONT_SIZE_SCALE;
    agingAdapationDialogTheme->maxFontSizeScale_ = MAX_FONT_SIZE_SCALE;
    agingAdapationDialogTheme->bigDialogWidth_ = BIG_DIALOG_WIDTH;
    agingAdapationDialogTheme->maxDialogWidth_ = MAX_DIALOG_WIDTH;
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_TAB);
    auto tabTheme = TabTheme::Builder().Build(themeConstants);
    EXPECT_CALL(*themeManager, GetTheme(TabTheme::TypeId())).WillRepeatedly(Return(tabTheme));
    tabTheme->defaultTabBarName_ = "tabBarItemName";
    tabTheme->tabBarDefaultWidth_ = Dimension(TABBAR_DEFAULT_WIDTH);
    tabTheme->tabBarDefaultHeight_ = Dimension(TABBAR_DEFAULT_HEIGHT);
    tabTheme->subTabBarHoverColor_ = Color::RED;
    tabTheme->subTabBarPressedColor_ = Color::GREEN;
    tabTheme->bottomTabSymbolOn_ = Color::BLUE;
    tabTheme->bottomTabIconOff_ = Color::BLACK;
    EXPECT_CALL(*MockPipelineContext::pipeline_, FlushUITasks).Times(AnyNumber());
}

void TabsTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void TabsTestNg::SetUp() {}

void TabsTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    layoutProperty_ = nullptr;

    swiperNode_ = nullptr;
    swiperPattern_ = nullptr;
    swiperLayoutProperty_ = nullptr;
    swiperPaintProperty_ = nullptr;
    swiperController_ = nullptr;

    tabBarNode_ = nullptr;
    tabBarPattern_ = nullptr;
    tabBarLayoutProperty_ = nullptr;
    tabBarPaintProperty_ = nullptr;
    tabBarAccessibilityProperty_ = nullptr;

    dividerNode_ = nullptr;
    dividerRenderProperty_ = nullptr;
    ClearOldNodes(); // Each testcase will create new list at begin
}

void TabsTestNg::GetTabs()
{
    // tabs
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    frameNode_ = AceType::DynamicCast<TabsNode>(element);
    pattern_ = frameNode_->GetPattern<TabsPattern>();
    layoutProperty_ = frameNode_->GetLayoutProperty<TabsLayoutProperty>();
    // swiper>tabContent
    swiperNode_ = AceType::DynamicCast<FrameNode>(frameNode_->GetTabs());
    swiperPattern_ = swiperNode_->GetPattern<SwiperPattern>();
    swiperLayoutProperty_ = swiperNode_->GetLayoutProperty<SwiperLayoutProperty>();
    swiperPaintProperty_ = swiperNode_->GetPaintProperty<SwiperPaintProperty>();
    swiperController_ = swiperPattern_->GetSwiperController();
    // tabBar
    tabBarNode_ = AceType::DynamicCast<FrameNode>(frameNode_->GetTabBar());
    tabBarPattern_ = tabBarNode_->GetPattern<TabBarPattern>();
    tabBarLayoutProperty_ = tabBarNode_->GetLayoutProperty<TabBarLayoutProperty>();
    tabBarPaintProperty_ = tabBarNode_->GetPaintProperty<TabBarPaintProperty>();
    tabBarAccessibilityProperty_ = tabBarNode_->GetAccessibilityProperty<TabBarAccessibilityProperty>();
    // divider
    dividerNode_ = AceType::DynamicCast<FrameNode>(frameNode_->GetDivider());
    dividerRenderProperty_ = dividerNode_->GetPaintProperty<DividerRenderProperty>();
}

TabsModelNG TabsTestNg::CreateTabs(BarPosition barPosition, int32_t index)
{
    ResetElmtId();
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    TabsModelNG model;
    model.Create(barPosition, index, nullptr, nullptr);
    ViewAbstract::SetWidth(CalcLength(TABS_WIDTH));
    ViewAbstract::SetHeight(CalcLength(TABS_HEIGHT));
    auto tabNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabNode->GetTabBar());
    tabBarNode->GetOrCreateFocusHub();
    GetTabs();
    ViewStackProcessor::GetInstance()->GetMainElementNode()->onMainTree_ = true;
    return model;
}

TabContentModelNG TabsTestNg::CreateTabContent()
{
    int32_t elmtId = GetElmtId();
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(elmtId);
    auto tabFrameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto weakTab = AceType::WeakClaim(AceType::RawPtr(tabFrameNode));
    TabContentModelNG tabContentModel;
    tabContentModel.Create();
    ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
    ViewAbstract::SetHeight(CalcLength(FILL_LENGTH));
    auto tabContentFrameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(tabContentFrameNode);
    tabContentNode->UpdateRecycleElmtId(elmtId); // for AddChildToGroup
    tabContentNode->GetTabBarItemId();           // for AddTabBarItem
    tabContentNode->SetParent(weakTab);          // for AddTabBarItem
    ViewStackProcessor::GetInstance()->GetMainElementNode()->onMainTree_ = true;
    return tabContentModel;
}

RefPtr<PaintWrapper> TabsTestNg::CreateTabsDone(TabsModelNG model)
{
    model.Pop();
    frameNode_->ProcessOffscreenTask();
    return CreateDone();
}

void TabsTestNg::CreateTabContents(int32_t itemNumber)
{
    for (int32_t index = 0; index < itemNumber; index++) {
        TabContentModelNG tabContentModel = CreateTabContent();
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
}

void TabsTestNg::CreateTabContentsWithBuilder(int32_t itemNumber)
{
    for (int32_t index = 0; index < itemNumber; index++) {
        TabContentModelNG tabContentModel = CreateTabContent();
        auto tabBarItemFunc = TabBarItemBuilder();
        tabContentModel.SetTabBar("", "", std::nullopt, std::move(tabBarItemFunc), true);
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
}

TabBarBuilderFunc TabsTestNg::TabBarItemBuilder()
{
    return []() {
        ColumnModelNG colModel;
        colModel.Create(Dimension(0), nullptr, "");
        ViewAbstract::SetWidth(CalcLength(BARITEM_SIZE));
        ViewAbstract::SetHeight(CalcLength(BARITEM_SIZE));
    };
}

void TabsTestNg::CreateTabContentTabBarStyle(TabBarStyle tabBarStyle)
{
    TabContentModelNG tabContentModel = CreateTabContent();
    tabContentModel.SetTabBarStyle(tabBarStyle);
    tabContentModel.SetTabBar("text", "icon", std::nullopt, nullptr, true);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
}

void TabsTestNg::CreateTabContentTabBarStyleWithBuilder(TabBarStyle tabBarStyle)
{
    TabContentModelNG tabContentModel = CreateTabContent();
    tabContentModel.SetTabBarStyle(tabBarStyle);
    auto tabBarItemFunc = TabBarItemBuilder();
    tabContentModel.SetTabBar("", "", std::nullopt, std::move(tabBarItemFunc), true);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
}

void TabsTestNg::SwipeToWithoutAnimation(int32_t index)
{
    swiperController_->SwipeToWithoutAnimation(index);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE); // for update swiper
    FlushLayoutTask(frameNode_);
}

void TabsTestNg::HandleClick(Offset offset, int32_t index)
{
    GestureEvent info;
    info.SetLocalLocation(offset);
    tabBarPattern_->HandleClick(info, index);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE); // for update swiper
    FlushLayoutTask(frameNode_);
}

void TabsTestNg::HandleMouseEvent(MouseAction action, Offset location)
{
    MouseInfo mouseInfo;
    mouseInfo.SetAction(action);
    mouseInfo.SetLocalLocation(location);
    tabBarPattern_->HandleMouseEvent(mouseInfo);
}

void TabsTestNg::HandleHoverEvent(bool isHover)
{
    tabBarPattern_->HandleHoverEvent(isHover);
}

void TabsTestNg::HandleTouchEvent(TouchType type, Offset location)
{
    TouchLocationInfo touchInfo(0);
    touchInfo.SetTouchType(type);
    touchInfo.SetLocalLocation(location);
    tabBarPattern_->HandleTouchEvent(touchInfo);
}

/**
 * @tc.name: InitSurfaceChangedCallback001
 * @tc.desc: test InitSurfaceChangedCallback
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, InitSurfaceChangedCallback001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: case1. WindowSizeChangeReason::UNDEFINED
     */
    auto callbackId = tabBarPattern_->surfaceChangedCallbackId_.value();
    auto func = MockPipelineContext::GetCurrent()->surfaceChangedCallbackMap_[callbackId];
    func(100.f, 100.f, TABS_WIDTH, TABS_HEIGHT, WindowSizeChangeReason::UNDEFINED);
    EXPECT_EQ(tabBarPattern_->windowSizeChangeReason_, WindowSizeChangeReason::UNDEFINED);

    /**
     * @tc.steps: case2. WindowSizeChangeReason::ROTATION
     * @tc.expected: StopTranslateAnimation
     */
    func(100.f, 100.f, TABS_WIDTH, TABS_HEIGHT, WindowSizeChangeReason::ROTATION);
    EXPECT_EQ(tabBarPattern_->windowSizeChangeReason_, WindowSizeChangeReason::ROTATION);
    EXPECT_FALSE(tabBarPattern_->indicatorAnimationIsRunning_);
    EXPECT_FALSE(tabBarPattern_->translateAnimationIsRunning_);

    /**
     * @tc.steps: case3. Other WindowSizeChangeReason
     * @tc.expected: Nothing happend
     */
    func(100.f, 100.f, TABS_WIDTH, TABS_HEIGHT, WindowSizeChangeReason::TRANSFORM);
    EXPECT_EQ(tabBarPattern_->windowSizeChangeReason_, WindowSizeChangeReason::TRANSFORM);
}

/**
 * @tc.name: TabsPatternGetScopeFocusAlgorithm001
 * @tc.desc: test GetScopeFocusAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsPatternGetScopeFocusAlgorithm001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs(BarPosition::END);
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabsDone(model);

    /**
     * @tc.steps: steps2. GetScopeFocusAlgorithm
     * @tc.expected: steps2. Check the result of GetScopeFocusAlgorithm
     */
    auto tabsLayoutProperty = layoutProperty_;
    auto tabsPattern = frameNode_->GetPattern<TabsPattern>();
    tabsLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    tabsPattern->GetScopeFocusAlgorithm();
    EXPECT_EQ(tabsLayoutProperty->GetAxis().value(), Axis::HORIZONTAL);
    tabsLayoutProperty->UpdateAxis(Axis::VERTICAL);
    tabsPattern->GetScopeFocusAlgorithm();
    EXPECT_EQ(tabsLayoutProperty->GetAxis().value(), Axis::VERTICAL);
}

/**
 * @tc.name: ConvertToString001
 * @tc.desc: Test the ConvertLayoutModeToString function in the TabContentNodel class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, ConvertToString001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    EXPECT_EQ(tabContentFrameNode->ConvertFlexAlignToString(FlexAlign::FLEX_START), "VerticalAlign.Top");
    EXPECT_EQ(tabContentFrameNode->ConvertFlexAlignToString(FlexAlign::FLEX_END), "VerticalAlign.Bottom");
    EXPECT_EQ(tabContentFrameNode->ConvertLayoutModeToString(LayoutMode::VERTICAL), "LayoutMode.VERTICAL");
    EXPECT_EQ(tabContentFrameNode->ConvertLayoutModeToString(LayoutMode::HORIZONTAL), "LayoutMode.HORIZONTAL");
    EXPECT_EQ(tabContentFrameNode->ConvertLayoutModeToString(LayoutMode::AUTO), "LayoutMode.AUTO");
}

/**
 * @tc.name: TabsNodeToJsonValue001
 * @tc.desc: Test the ToJsonValue function in the TabsNode class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsNodeToJsonValue001, TestSize.Level2)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);

    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    frameNode_->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("index"), "0");
    EXPECT_EQ(json->GetString("animationDuration"), "");
    EXPECT_EQ(json->GetString("barMode"), "BarMode.Fixed");
    EXPECT_EQ(json->GetString("barWidth"), "720.000000");
    EXPECT_EQ(json->GetString("barHeight"), "56.000000");
    EXPECT_EQ(json->GetString("fadingEdge"), "true");
    EXPECT_EQ(json->GetString("barBackgroundColor"), "#00000000");
    EXPECT_EQ(json->GetString("barBackgroundBlurStyle"), "BlurStyle.NONE");
    EXPECT_EQ(json->GetString("animationMode"), "AnimationMode.CONTENT_FIRST");
    EXPECT_EQ(json->GetString("edgeEffect"), "EdgeEffect::SPRING");
    EXPECT_EQ(json->GetString("barGridAlign"), "");

    pattern_->SetAnimateMode(TabAnimateMode::ACTION_FIRST);
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    swiperPaintProperty_->UpdateEdgeEffect(EdgeEffect::FADE);
    json = JsonUtil::Create(true);
    frameNode_->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("barMode"),
        "BarMode.Scrollable,{\"margin\":\"0.00vp\",\"nonScrollableLayoutStyle\":\"LayoutStyle.ALWAYS_CENTER\"}");
    EXPECT_EQ(json->GetString("animationMode"), "AnimationMode.ACTION_FIRST");
    EXPECT_EQ(json->GetString("edgeEffect"), "EdgeEffect::FADE");

    ScrollableBarModeOptions options;
    options.nonScrollableLayoutStyle = LayoutStyle::ALWAYS_AVERAGE_SPLIT;
    tabBarLayoutProperty_->UpdateScrollableBarModeOptions(options);
    pattern_->SetAnimateMode(TabAnimateMode::NO_ANIMATION);
    swiperPaintProperty_->UpdateEdgeEffect(EdgeEffect::NONE);
    json = JsonUtil::Create(true);
    frameNode_->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("barMode"),
        "BarMode.Scrollable,{\"margin\":\"0.00vp\",\"nonScrollableLayoutStyle\":\"LayoutStyle.ALWAYS_AVERAGE_SPLIT\"}");
    EXPECT_EQ(json->GetString("animationMode"), "AnimationMode.NO_ANIMATION");
    EXPECT_EQ(json->GetString("edgeEffect"), "EdgeEffect::NONE");

    options.nonScrollableLayoutStyle = LayoutStyle::SPACE_BETWEEN_OR_CENTER;
    tabBarLayoutProperty_->UpdateScrollableBarModeOptions(options);
    pattern_->SetAnimateMode(TabAnimateMode::MAX_VALUE);
    json = JsonUtil::Create(true);
    frameNode_->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("barMode"), "BarMode.Scrollable,{\"margin\":\"0.00vp\",\"nonScrollableLayoutStyle\":"
                                          "\"LayoutStyle.SPACE_BETWEEN_OR_CENTER\"}");
    EXPECT_EQ(json->GetString("animationMode"), "AnimationMode.CONTENT_FIRST");
}

/**
 * @tc.name: TabsNodeToJsonValue002
 * @tc.desc: Test the ToJsonValue function in the TabsNode class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsNodeToJsonValue002, TestSize.Level2)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);

    frameNode_->swiperId_ = std::nullopt;
    frameNode_->tabBarId_ = std::nullopt;
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    frameNode_->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("index"), "0");
    EXPECT_EQ(json->GetString("animationDuration"), "");
    EXPECT_EQ(json->GetString("barMode"), "BarMode.Fixed");
    EXPECT_EQ(json->GetString("barWidth"), "0.000000");
    EXPECT_EQ(json->GetString("barHeight"), "0.000000");
    EXPECT_EQ(json->GetString("fadingEdge"), "true");
    EXPECT_EQ(json->GetString("barBackgroundColor"), "#00000000");
    EXPECT_EQ(json->GetString("barBackgroundBlurStyle"), "BlurStyle.NONE");
    EXPECT_EQ(json->GetString("animationMode"), "AnimationMode.CONTENT_FIRST");
    EXPECT_EQ(json->GetString("edgeEffect"), "EdgeEffect::SPRING");
    EXPECT_EQ(json->GetString("barGridAlign"), "");

    std::string attr = "id";
    filter.AddFilterAttr(attr);
    json = JsonUtil::Create(true);
    frameNode_->ToJsonValue(json, filter);
    EXPECT_TRUE(filter.IsFastFilter());
    EXPECT_EQ(json->ToString(), "{\"id\":\"\"}");
}

/**
 * @tc.name: TabsNodeGetScrollableBarModeOptions001
 * @tc.desc: Test the GetScrollableBarModeOptions function in the TabsNode class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsNodeGetScrollableBarModeOptions001, TestSize.Level2)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    tabBarPattern_->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;

    /**
     * @tc.steps: steps2. GetScrollableBarModeOptions.
     * @tc.expected: steps2. Check the result of GetScrollableBarModeOptions.
     */
    frameNode_->GetScrollableBarModeOptions();
    frameNode_->tabBarId_ = frameNode_->GetTabBarId();
    ScrollableBarModeOptions option = frameNode_->GetScrollableBarModeOptions();
    EXPECT_EQ(option.margin.Value(), 0.0f);
    EXPECT_EQ(option.nonScrollableLayoutStyle, LayoutStyle::ALWAYS_CENTER);
    frameNode_->tabBarId_ = {};
    option = frameNode_->GetScrollableBarModeOptions();
    EXPECT_EQ(option.margin.Value(), 0.0f);
    EXPECT_EQ(option.nonScrollableLayoutStyle, LayoutStyle::ALWAYS_CENTER);
}

/**
 * @tc.name: ProvideRestoreInfo001
 * @tc.desc: test AddTabBarItem
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, ProvideRestoreInfo001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    EXPECT_EQ(tabBarPattern_->ProvideRestoreInfo(), "{\"Index\":0}");
    SwipeToWithoutAnimation(1);
    EXPECT_EQ(tabBarPattern_->ProvideRestoreInfo(), "{\"Index\":1}");
}

/**
 * @tc.name: SetEdgeEffect002
 * @tc.desc: test SetEdgeEffect
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, SetEdgeEffect002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    TabsItemDivider divider;
    model.SetDivider(divider);
    CreateTabsDone(model);
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);

    /**
     * @tc.steps: step1. Test function SetEdgeEffect.
     * @tc.expected: SetEdgeEffect calling interface.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    tabBarPattern_->SetEdgeEffect(gestureHub);
    /**
     * @tc.steps: step1. Set scrollEffect_ Value is empty.
     * @tc.expected: SetEdgeEffect calling interface
     */
    tabBarPattern_->scrollEffect_ = nullptr;
    tabBarPattern_->SetEdgeEffect(gestureHub);
}

/**
 * @tc.name: Create003
 * @tc.desc: test SetEdgeEffect
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, Create003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct TabContentModelNG object
     */
    int32_t testIndex = 0;
    TabsModelNG model = CreateTabs(BarPosition::END, testIndex);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. Test function Create.
     * @tc.expected: TestIndex greater than or equal to 0
     */
    swiperPaintProperty_->UpdateEdgeEffect(EdgeEffect::SPRING);
    EXPECT_TRUE(testIndex >= 0);
}

/**
 * @tc.name: TabsPatternParseJsonString002
 * @tc.desc: test ParseJsonString
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsPatternOnRestoreInfo002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Function OnRestoreInfo is called.
     * @tc.expected: Passing invalid & valid JSON format.
     */
    TabsModelNG model = CreateTabs(BarPosition::END);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    pattern_->OnRestoreInfo("");
    auto info = JsonUtil::ParseJsonString("");
    EXPECT_FALSE(info->IsObject());
}

/**
 * @tc.name: TabsPatternSetOnAnimationEnd002
 * @tc.desc: test Measure
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsPatternSetOnAnimationEnd002, TestSize.Level1)
{
    auto onAnimationStart = [](int32_t index, int32_t targetIndex, const AnimationCallbackInfo& info) {};
    auto onAnimationEnd = [](int32_t index, const AnimationCallbackInfo& info) {};
    TabsModelNG model = CreateTabs();
    model.SetOnAnimationStart(std::move(onAnimationStart));
    model.SetOnAnimationEnd(std::move(onAnimationEnd));
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2.2. Test SetOnAnimationEnd function.
     * @tc.expected:pattern_->animationEndEvent_ not null.
     */
    tabBarPattern_->InitTurnPageRateEvent();
    int32_t testswipingIndex = 1;
    float testturnPageRate = 1.0f;
    tabBarPattern_->swiperController_->turnPageRateCallback_(testswipingIndex, testturnPageRate);

    /**
     * @tc.steps: step1. Convert lvalue to rvalue reference using std:: move()
     */
    EXPECT_NE(pattern_->animationEndEvent_, nullptr);
    pattern_->SetAnimationEndEvent(std::move(*tabBarPattern_->animationEndEvent_));
    EXPECT_NE(pattern_->animationEndEvent_, nullptr);
}

/**
 * @tc.name: TabsPatternGetAxis003
 * @tc.desc: test GetAxis
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsPatternGetAxis003, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: steps2. GetScopeFocusAlgorithm
     * @tc.expected: steps2. Check the result of GetScopeFocusAlgorithm
     */
    layoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    pattern_->GetScopeFocusAlgorithm();
    EXPECT_EQ(layoutProperty_->GetAxis().value(), Axis::HORIZONTAL);

    layoutProperty_->UpdateAxis(Axis::VERTICAL);
    pattern_->GetScopeFocusAlgorithm();
    EXPECT_EQ(layoutProperty_->GetAxis().value(), Axis::VERTICAL);

    layoutProperty_->UpdateAxis(Axis::FREE);
    pattern_->GetScopeFocusAlgorithm();
    EXPECT_EQ(layoutProperty_->GetAxis().value(), Axis::FREE);

    layoutProperty_->UpdateAxis(Axis::NONE);
    pattern_->GetScopeFocusAlgorithm();
    EXPECT_EQ(layoutProperty_->GetAxis().value(), Axis::NONE);
}

/**
 * @tc.name: TabsPatternGetScopeFocusAlgorithm004
 * @tc.desc: test GetScopeFocusAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsPatternGetScopeFocusAlgorithm004, TestSize.Level1)
{
    /**
     * @tc.steps: steps2. GetScopeFocusAlgorithm
     * @tc.expected: steps2. Check the result of GetScopeFocusAlgorithm
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    layoutProperty_->Reset();
    pattern_->GetScopeFocusAlgorithm();
    EXPECT_FALSE(layoutProperty_->GetAxis().has_value());
}

/**
 * @tc.name: CustomAnimationTest001
 * @tc.desc: test custom animation disable swipe
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, CustomAnimationTest001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs(BarPosition::START, 1);
    model.SetIsCustomAnimation(true);
    model.SetOnCustomAnimation([](int32_t from, int32_t to) -> TabContentAnimatedTransition {
        TabContentAnimatedTransition transitionInfo;
        transitionInfo.transition = [](const RefPtr<TabContentTransitionProxy>& proxy) {};
        return transitionInfo;
    });
    CreateTabContentsWithBuilder(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    tabBarLayoutProperty_->UpdateAxis(Axis::VERTICAL);
    EXPECT_EQ(tabBarLayoutProperty_->GetAxisValue(), Axis::VERTICAL);
    tabBarPattern_->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    tabBarPattern_->visibleItemPosition_[0] = { 0.0f, 10.0f };
    swiperLayoutProperty_->UpdateIndex(INDEX_ONE);
    GestureEvent info;
    Offset offset(1, 1);
    info.SetLocalLocation(offset);
    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern_->HandleClick(info, 0);
    EXPECT_TRUE(swiperPattern_->IsDisableSwipe());
    EXPECT_TRUE(swiperPattern_->customAnimationToIndex_.has_value());

    swiperPattern_->OnCustomAnimationFinish(INDEX_ONE, INDEX_ZERO, false);
    EXPECT_FALSE(swiperPattern_->customAnimationToIndex_.has_value());

    swiperPattern_->SwipeTo(INDEX_ONE);
    EXPECT_TRUE(swiperPattern_->customAnimationToIndex_.has_value());
}

/**
 * @tc.name: CustomAnimationTest002
 * @tc.desc: test custom animation set undefined
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, CustomAnimationTest002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    model.SetIsCustomAnimation(false);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    EXPECT_FALSE(swiperPattern_->IsDisableSwipe());
}
} // namespace OHOS::Ace::NG
