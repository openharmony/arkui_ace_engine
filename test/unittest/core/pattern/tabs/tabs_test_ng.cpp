/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "core/common/agingadapation/aging_adapation_dialog_theme.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components/tab_bar/tab_theme.h"
#include "core/components_ng/pattern/linear_layout/column_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
RefPtr<Theme> GetTheme(ThemeType type)
{
    if (type == AgingAdapationDialogTheme::TypeId()) {
        auto agingAdapationDialogTheme = AceType::MakeRefPtr<AgingAdapationDialogTheme>();
        agingAdapationDialogTheme->bigFontSizeScale_ = BIG_FONT_SIZE_SCALE;
        agingAdapationDialogTheme->largeFontSizeScale_ = LARGE_FONT_SIZE_SCALE;
        agingAdapationDialogTheme->maxFontSizeScale_ = MAX_FONT_SIZE_SCALE;
        agingAdapationDialogTheme->bigDialogWidth_ = BIG_DIALOG_WIDTH;
        agingAdapationDialogTheme->maxDialogWidth_ = MAX_DIALOG_WIDTH;
        return agingAdapationDialogTheme;
    } else if (type == TabTheme::TypeId()) {
        auto themeConstants = TestNG::CreateThemeConstants(THEME_PATTERN_TAB);
        auto tabTheme = TabTheme::Builder().Build(themeConstants);
        tabTheme->defaultTabBarName_ = "tabBarItemName";
        tabTheme->tabBarDefaultWidth_ = Dimension(TAB_BAR_SIZE);
        tabTheme->tabBarDefaultHeight_ = Dimension(TAB_BAR_SIZE);
        tabTheme->subTabBarHoverColor_ = Color::RED;
        tabTheme->subTabBarPressedColor_ = Color::GREEN;
        tabTheme->bottomTabSymbolOn_ = Color::BLUE;
        tabTheme->bottomTabIconOff_ = Color::BLACK;
        tabTheme->tabBarFocusedColor_ = Color::GRAY;
        return tabTheme;
    } else {
        return AceType::MakeRefPtr<DialogTheme>();
    }
}
} // namespace

void TabsTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void TabsTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void TabsTestNg::SetUp() {}

void TabsTestNg::TearDown()
{
    RemoveFromStageNode();
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
    ClearOldNodes(); // Each testCase will create new list at begin
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
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
    return tabContentModel;
}

void TabsTestNg::CreateTabsDone(TabsModelNG model)
{
    model.Pop();
    CreateDone();
    auto pipeline = frameNode_->GetContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
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
        ViewAbstract::SetWidth(CalcLength(BAR_ITEM_SIZE));
        ViewAbstract::SetHeight(CalcLength(BAR_ITEM_SIZE));
    };
}

void TabsTestNg::CreateTabContentTabBarStyle(TabBarStyle tabBarStyle)
{
    TabContentModelNG tabContentModel = CreateTabContent();
    tabContentModel.SetTabBarStyle(tabBarStyle);
    tabContentModel.SetTabBar("text", IMAGE_SRC_URL, std::nullopt, nullptr, true);
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

void TabsTestNg::ChangeIndex(int32_t index)
{
    swiperController_->SwipeTo(index);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE); // for update swiper
    FlushUITasks();
}

void TabsTestNg::HandleClick(int32_t index)
{
    tabBarPattern_->HandleClick(SourceType::NONE, index);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE); // for update swiper
    FlushUITasks();
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

GestureEvent TabsTestNg::CreateDragInfo(bool moveDirection)
{
    GestureEvent info;
    info.SetInputEventType(InputEventType::AXIS);
    info.SetSourceTool(SourceTool::TOUCHPAD);
    info.SetGlobalLocation(Offset(100.f, 100.f));
    info.SetMainDelta(moveDirection ? -DRAG_DELTA : DRAG_DELTA);
    info.SetMainVelocity(moveDirection ? -2000.f : 2000.f);
    return info;
}

AssertionResult TabsTestNg::CurrentIndex(int32_t expectIndex)
{
    if (swiperPattern_->GetCurrentIndex() != expectIndex) {
        return IsEqual(swiperPattern_->GetCurrentIndex(), expectIndex);
    }
    if (tabBarLayoutProperty_->GetIndicatorValue() != expectIndex) {
        return IsEqual(tabBarLayoutProperty_->GetIndicatorValue(), expectIndex);
    }
    if (!GetChildFrameNode(swiperNode_, expectIndex)) {
        return AssertionFailure() << "There is no item at expectIndex: " << expectIndex;
    }
    if (!GetChildFrameNode(swiperNode_, expectIndex)->IsActive()) {
        return AssertionFailure() << "The expectIndex item is not active";
    }
    if (GetChildFrameNode(swiperNode_, expectIndex)->GetLayoutProperty()->GetVisibility() != VisibleType::GONE) {
        if (NearZero(GetChildWidth(swiperNode_, expectIndex))) {
            return AssertionFailure() << "The expectIndex item width is 0";
        }
        if (NearZero(GetChildHeight(swiperNode_, expectIndex))) {
            return AssertionFailure() << "The expectIndex item height is 0";
        }
    }
    return AssertionSuccess();
}

RefPtr<TabBarModifier> TabsTestNg::OnDraw()
{
    RefPtr<NodePaintMethod> paint = tabBarPattern_->CreateNodePaintMethod();
    RefPtr<TabBarPaintMethod> tabBarPaint = AceType::DynamicCast<TabBarPaintMethod>(paint);
    auto tabBarPaintWrapper = tabBarNode_->CreatePaintWrapper();
    tabBarPaint->UpdateContentModifier(AceType::RawPtr(tabBarPaintWrapper));

    auto modifier = tabBarPaint->GetContentModifier(nullptr);
    auto tabBarModifier = AceType::DynamicCast<TabBarModifier>(modifier);
    Testing::MockCanvas canvas;
    DrawingContext drawingContext = { canvas, TABS_WIDTH, TABS_HEIGHT };
    tabBarModifier->onDraw(drawingContext);
    return tabBarModifier;
}

AssertionResult TabsTestNg::VerifyBackgroundColor(int32_t itemIndex, Color expectColor)
{
    Color actualColor = GetChildFrameNode(tabBarNode_, itemIndex)->GetRenderContext()->GetBackgroundColor().value();
    return IsEqual(actualColor, expectColor);
}

void TabsTestNg::MockPaintRect(const RefPtr<FrameNode>& frameNode)
{
    auto mockRenderContext = AceType::DynamicCast<MockRenderContext>(frameNode->renderContext_);
    mockRenderContext->paintRect_ = RectF(0.f, 0.f, TABS_WIDTH, TABS_HEIGHT);
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
 * @tc.name: TabsNodeToJsonValue003
 * @tc.desc: Test the ToJsonValue function in the TabsNode class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsNodeToJsonValue003, TestSize.Level2)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);
    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(pattern_, nullptr);

    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    frameNode_->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("animationMode"), "AnimationMode.CONTENT_FIRST");

    pattern_->SetAnimateMode(TabAnimateMode::CONTENT_FIRST_WITH_JUMP);
    json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    frameNode_->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("animationMode"), "AnimationMode.CONTENT_FIRST_WITH_JUMP");

    pattern_->SetAnimateMode(TabAnimateMode::ACTION_FIRST_WITH_JUMP);
    json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    frameNode_->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("animationMode"), "AnimationMode.ACTION_FIRST_WITH_JUMP");
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
    EXPECT_EQ(option.nonScrollableLayoutStyle, std::nullopt);
    frameNode_->tabBarId_ = {};
    option = frameNode_->GetScrollableBarModeOptions();
    EXPECT_EQ(option.margin.Value(), 0.0f);
    EXPECT_EQ(option.nonScrollableLayoutStyle, std::nullopt);
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
    ChangeIndex(1);
    EXPECT_EQ(tabBarPattern_->ProvideRestoreInfo(), "{\"Index\":1}");
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
    swiperController_->GetTurnPageRateCallback()(testswipingIndex, testturnPageRate);

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
    swiperLayoutProperty_->UpdateIndex(1);
    GestureEvent info;
    Offset offset(1, 1);
    info.SetLocalLocation(offset);
    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern_->HandleClick(info.GetSourceDevice(), 0);
    EXPECT_TRUE(swiperPattern_->IsDisableSwipe());
    EXPECT_TRUE(swiperPattern_->customAnimationToIndex_.has_value());

    swiperPattern_->OnCustomAnimationFinish(1, 0, false);
    EXPECT_FALSE(swiperPattern_->customAnimationToIndex_.has_value());

    swiperPattern_->SwipeTo(1);
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

/**
 * @tc.name: DragSwiper001
 * @tc.desc: Could drag swiper, change tabBar index
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, DragSwiper001, TestSize.Level1)
{
    MockAnimationManager::Enable(true);
    MockAnimationManager::GetInstance().SetTicks(1);
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    EXPECT_TRUE(swiperPattern_->panEvent_);

    GestureEvent info = CreateDragInfo(true);
    swiperPattern_->HandleDragStart(info);
    swiperPattern_->HandleDragUpdate(info);
    FlushUITasks();
    swiperPattern_->HandleDragEnd(info.GetMainVelocity());
    FlushUITasks();
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_TRUE(CurrentIndex(1));
    MockAnimationManager::Enable(false);
}

/**
 * @tc.name: DragSwiper002
 * @tc.desc: Set BOTTOMTABBATSTYLE, Test drag swiper, would change tabBar index
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, DragSwiper002, TestSize.Level1)
{
    MockAnimationManager::Enable(true);
    MockAnimationManager::GetInstance().SetTicks(1);
    TabsModelNG model = CreateTabs();
    // set BOTTOMTABBATSTYLE
    CreateTabContentTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    CreateTabContentTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    CreateTabsDone(model);

    GestureEvent info = CreateDragInfo(true);
    swiperPattern_->HandleDragStart(info);
    swiperPattern_->HandleDragUpdate(info);
    FlushUITasks();
    swiperPattern_->HandleDragEnd(info.GetMainVelocity());
    FlushUITasks();
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_TRUE(CurrentIndex(1));
    MockAnimationManager::Enable(false);
}

/**
 * @tc.name: DragSwiper003
 * @tc.desc: SetScrollable to false, could not drag to change page
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, DragSwiper003, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    // SetScrollable to false, could not drag to change page
    model.SetScrollable(false);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    EXPECT_FALSE(swiperPattern_->panEvent_);
}
} // namespace OHOS::Ace::NG
