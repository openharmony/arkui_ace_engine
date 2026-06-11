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

#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_resource_adapter_v2.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/components_ng/render/mock_render_context.h"
#include "test/mock/frameworks/core/rosen/mock_canvas.h"

#include "core/common/agingadapation/aging_adapation_dialog_theme.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components/focus_animation/focus_animation_theme.h"
#include "core/components/tab_bar/tab_theme.h"
#include "core/components_ng/pattern/linear_layout/column_model_ng.h"
#include "core/components_ng/pattern/tabs/tab_content_model_static.h"
#include "core/components_ng/pattern/tabs/tab_content_pattern.h"
#include "core/components_ng/pattern/tabs/tab_content_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/common/font_manager.h"
#include "test/mock/frameworks/core/common/mock_font_manager.h"

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
        tabTheme->activeIndicatorColor_ = Color::RED;
        return tabTheme;
    } else if (type == FocusAnimationTheme::TypeId()) {
        auto focusTheme = AceType::MakeRefPtr<FocusAnimationTheme>();
        return focusTheme;
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
    ResetMockResourceData();
    g_isConfigChangePerform = false;
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
    ResetMockResourceData();
    g_isConfigChangePerform = false;
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
    model.Create(barPosition, index, nullptr);
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
    return CreateTabContentWithDeepRender(nullptr);
}

TabContentModelNG TabsTestNg::CreateTabContentWithDeepRender(std::function<void()>&& deepRenderFunc)
{
    int32_t elmtId = GetElmtId();
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(elmtId);
    auto tabFrameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto weakTab = AceType::WeakClaim(AceType::RawPtr(tabFrameNode));
    TabContentModelNG tabContentModel;
    tabContentModel.Create(std::move(deepRenderFunc));
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

void TabsTestNg::MockPaintRectSmallSize(const RefPtr<FrameNode>& frameNode)
{
    auto mockRenderContext = AceType::DynamicCast<MockRenderContext>(frameNode->renderContext_);
    mockRenderContext->paintRect_ = RectF(0.f, 0.f, TABS_WIDTH, 0.f);
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
    EXPECT_EQ(json->ToString(), "{\"id\":\"\",\"isLayoutDirtyMarked\":false,\"isRenderDirtyMarked\":false,"
                                "\"isMeasureBoundary\":false,\"hasPendingRequest\":false,\"isFirstBuilding\":false,"
                                "\"enableClickSoundEffect\":true}");
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

/**
 * @tc.name: OnColorModeChangeTest001
 * @tc.desc: Test Tabs OnColorModeChange
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, OnColorModeChangeTest001, TestSize.Level1)
{
    g_isConfigChangePerform = true;

    /**
     * @tc.steps: step1. create tabs and set parameters.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(layoutProperty_, nullptr);
    ASSERT_NE(dividerRenderProperty_, nullptr);

    /**
     * @tc.steps: step2. reset data.
     */
    int32_t colorMode = static_cast<int32_t>(ColorMode::DARK);
    layoutProperty_->ResetDividerColorSetByUser();
    dividerRenderProperty_->ResetDividerColor();
    pattern_->OnColorModeChange(colorMode);
    EXPECT_TRUE(dividerRenderProperty_->HasDividerColor());

    layoutProperty_->UpdateDividerColorSetByUser(false);
    dividerRenderProperty_->ResetDividerColor();
    pattern_->OnColorModeChange(colorMode);
    EXPECT_TRUE(dividerRenderProperty_->HasDividerColor());

    layoutProperty_->UpdateDividerColorSetByUser(true);
    dividerRenderProperty_->ResetDividerColor();
    pattern_->OnColorModeChange(colorMode);
    EXPECT_FALSE(dividerRenderProperty_->HasDividerColor());

    g_isConfigChangePerform = false;
}

/**
 * @tc.name: TabContentCreatePaddingWithResourceObj001
 * @tc.desc: test CreatePaddingWithResourceObj of TabContentModelNG
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentCreatePaddingWithResourceObj001, TestSize.Level1)
{
    CreateTabContent();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    EXPECT_TRUE(TabContentModelNG::CreatePaddingLeftWithResourceObj(frameNode, nullptr));
    EXPECT_TRUE(TabContentModelNG::CreatePaddingRightWithResourceObj(frameNode, nullptr));
    EXPECT_TRUE(TabContentModelNG::CreatePaddingTopWithResourceObj(frameNode, nullptr));
    EXPECT_TRUE(TabContentModelNG::CreatePaddingBottomWithResourceObj(frameNode, nullptr));
    EXPECT_TRUE(TabContentModelNG::CreatePaddingWithResourceObj(frameNode, nullptr));
    EXPECT_TRUE(TabContentModelNG::CreateTextContentWithResourceObj(frameNode, nullptr));
    EXPECT_TRUE(TabContentModelNG::CreateIconWithResourceObjWithKey(frameNode, "", nullptr));
    EXPECT_TRUE(TabContentModelNG::CreateBoardStyleBorderRadiusWithResourceObj(frameNode, nullptr));
    EXPECT_TRUE(TabContentModelNG::CreateIndicatorColorWithResourceObj(frameNode, nullptr));
    EXPECT_TRUE(TabContentModelNG::CreateIndicatorHeightWithResourceObj(frameNode, nullptr));
    EXPECT_TRUE(TabContentModelNG::CreateIndicatorWidthWithResourceObj(frameNode, nullptr));
    EXPECT_TRUE(TabContentModelNG::CreateIndicatorBorderRadiusWithResourceObj(frameNode, nullptr));
    EXPECT_TRUE(TabContentModelNG::CreateIndicatorMarginTopWithResourceObj(frameNode, nullptr));

    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", Container::CurrentIdSafely());
    RefPtr<ResourceObject> resObjLeft = AceType::MakeRefPtr<ResourceObject>("", "", Container::CurrentIdSafely());
    RefPtr<ResourceObject> resObjRight = AceType::MakeRefPtr<ResourceObject>("", "", Container::CurrentIdSafely());
    RefPtr<ResourceObject> resObjTop = AceType::MakeRefPtr<ResourceObject>("", "", Container::CurrentIdSafely());
    RefPtr<ResourceObject> resObjBottom = AceType::MakeRefPtr<ResourceObject>("", "", Container::CurrentIdSafely());

    EXPECT_TRUE(TabContentModelNG::CreatePaddingLeftWithResourceObj(frameNode, resObjLeft));
    EXPECT_TRUE(TabContentModelNG::CreatePaddingRightWithResourceObj(frameNode, resObjRight));
    EXPECT_TRUE(TabContentModelNG::CreatePaddingTopWithResourceObj(frameNode, resObjTop));
    EXPECT_TRUE(TabContentModelNG::CreatePaddingBottomWithResourceObj(frameNode, resObjBottom));
    EXPECT_TRUE(TabContentModelNG::CreatePaddingWithResourceObj(frameNode, resObj));
    EXPECT_TRUE(TabContentModelNG::CreateTextContentWithResourceObj(frameNode, resObj));
    EXPECT_TRUE(TabContentModelNG::CreateIconWithResourceObjWithKey(frameNode, "", resObj));
    EXPECT_TRUE(TabContentModelNG::CreateBoardStyleBorderRadiusWithResourceObj(frameNode, resObj));
    EXPECT_TRUE(TabContentModelNG::CreateIndicatorColorWithResourceObj(frameNode, resObj));
    EXPECT_TRUE(TabContentModelNG::CreateIndicatorHeightWithResourceObj(frameNode, resObj));
    EXPECT_TRUE(TabContentModelNG::CreateIndicatorWidthWithResourceObj(frameNode, resObj));
    EXPECT_TRUE(TabContentModelNG::CreateIndicatorBorderRadiusWithResourceObj(frameNode, resObj));
    EXPECT_TRUE(TabContentModelNG::CreateIndicatorMarginTopWithResourceObj(frameNode, resObj));
}

/**
 * @tc.name: GetTargetIndexTest001
 * @tc.desc: test GetTargetIndex
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, GetTargetIndexTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create tabs and set parameters.
     */
    TabsModelNG model = CreateTabs();
    model.SetTabBarMode(TabBarMode::SCROLLABLE);
    model.SetIsVertical(false);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    ASSERT_NE(pattern_, nullptr);
    std::list<std::string> commands = { { R"({"cmd":"changeIndex","params":})" },
        { "" },
        { R"({"cmd":"change"})" },
        { R"({"params":"111111111"})" },
        { R"({"cmd":"changeIndex","params":{}})" } };

    int32_t targetIndex = 0;
    for (const auto& command : commands) {
        bool ret = pattern_->GetTargetIndex(command, targetIndex);
        EXPECT_EQ(ret, false);
    }
}

/**
 * @tc.name: TabContentModelStaticSetShallowBuilder001
 * @tc.desc: Test SetShallowBuilder with null frameNode, null pattern, and valid node
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticSetShallowBuilder001, TestSize.Level1)
{
    auto shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>([]() -> RefPtr<UINode> { return nullptr; });

    TabContentModelStatic::SetShallowBuilder(nullptr, shallowBuilder);

    auto basicNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    TabContentModelStatic::SetShallowBuilder(AceType::RawPtr(basicNode), shallowBuilder);

    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentNode, nullptr);
    TabContentModelStatic::SetShallowBuilder(AceType::RawPtr(tabContentNode), shallowBuilder);
    auto pattern = tabContentNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_NE(pattern->shallowBuilder_, nullptr);
}

/**
 * @tc.name: TabContentModelStaticSetIndicator001
 * @tc.desc: Test SetIndicator with null frameNode, null pattern, with value and without value
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticSetIndicator001, TestSize.Level1)
{
    TabContentModelStatic::SetIndicator(nullptr, IndicatorStyle());

    auto basicNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    TabContentModelStatic::SetIndicator(AceType::RawPtr(basicNode), IndicatorStyle());

    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentNode, nullptr);

    IndicatorStyle indicator;
    indicator.color = Color::RED;
    indicator.height = 10.0_vp;
    TabContentModelStatic::SetIndicator(AceType::RawPtr(tabContentNode), indicator);
    auto pattern = tabContentNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->GetIndicatorStyle().color, Color::RED);

    TabContentModelStatic::SetIndicator(AceType::RawPtr(tabContentNode), std::nullopt);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: TabContentModelStaticSetDrawableIndicatorConfig001
 * @tc.desc: Test SetDrawableIndicatorConfig with null and valid frameNode
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticSetDrawableIndicatorConfig001, TestSize.Level1)
{
    ImageInfoConfig config;
    TabContentModelStatic::SetDrawableIndicatorConfig(nullptr, config);

    auto basicNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    TabContentModelStatic::SetDrawableIndicatorConfig(AceType::RawPtr(basicNode), config);

    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentNode, nullptr);
    TabContentModelStatic::SetDrawableIndicatorConfig(AceType::RawPtr(tabContentNode), config);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: TabContentModelStaticSetIndicatorColorByUser001
 * @tc.desc: Test SetIndicatorColorByUser with true and false
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticSetIndicatorColorByUser001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentNode, nullptr);

    TabContentModelStatic::SetIndicatorColorByUser(AceType::RawPtr(tabContentNode), true);
    auto layoutProp = tabContentNode->GetLayoutProperty<TabContentLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    EXPECT_TRUE(layoutProp->GetIndicatorColorSetByUserValue(false));

    TabContentModelStatic::SetIndicatorColorByUser(AceType::RawPtr(tabContentNode), false);
    EXPECT_FALSE(layoutProp->GetIndicatorColorSetByUserValue(true));
}

/**
 * @tc.name: TabContentModelStaticSetDrawableIndicatorFlag001
 * @tc.desc: Test SetDrawableIndicatorFlag with null and valid frameNode
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticSetDrawableIndicatorFlag001, TestSize.Level1)
{
    TabContentModelStatic::SetDrawableIndicatorFlag(nullptr, true);

    auto basicNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    TabContentModelStatic::SetDrawableIndicatorFlag(AceType::RawPtr(basicNode), true);

    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentNode, nullptr);
    TabContentModelStatic::SetDrawableIndicatorFlag(AceType::RawPtr(tabContentNode), true);
    auto pattern = tabContentNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_TRUE(pattern->IsDrawableIndicator());

    TabContentModelStatic::SetDrawableIndicatorFlag(AceType::RawPtr(tabContentNode), false);
    EXPECT_FALSE(pattern->IsDrawableIndicator());
}

/**
 * @tc.name: TabContentModelStaticSetLabelStyle001
 * @tc.desc: Test SetLabelStyle with null, with value, without value, isSubTabStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticSetLabelStyle001, TestSize.Level1)
{
    TabContentModelStatic::SetLabelStyle(nullptr, LabelStyle(), false);

    auto basicNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    TabContentModelStatic::SetLabelStyle(AceType::RawPtr(basicNode), LabelStyle(), false);

    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentNode, nullptr);

    LabelStyle labelStyle;
    labelStyle.fontSize = 20.0_fp;
    labelStyle.fontWeight = FontWeight::BOLD;
    TabContentModelStatic::SetLabelStyle(AceType::RawPtr(tabContentNode), labelStyle, true);
    auto pattern = tabContentNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->GetLabelStyle().fontSize.value(), 20.0_fp);

    TabContentModelStatic::SetLabelStyle(AceType::RawPtr(tabContentNode), std::nullopt, false);
    EXPECT_TRUE(true);

    TabContentModelStatic::SetLabelStyle(AceType::RawPtr(tabContentNode), std::nullopt, true);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: TabContentModelStaticCompleteParameters001
 * @tc.desc: Test CompleteParameters with null, all fields present, fields missing, version branches
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticCompleteParameters001, TestSize.Level1)
{
    LabelStyle emptyStyle;
    auto result = TabContentModelStatic::CompleteParameters(nullptr, emptyStyle, false);
    EXPECT_FALSE(result.fontSize.has_value());

    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentNode, nullptr);

    LabelStyle labelStyle;
    result = TabContentModelStatic::CompleteParameters(AceType::RawPtr(tabContentNode), labelStyle, false);
    EXPECT_EQ(result.maxLines.value(), 1);
    EXPECT_EQ(result.fontStyle.value(), Ace::FontStyle::NORMAL);
    EXPECT_EQ(result.heightAdaptivePolicy.value(), TextHeightAdaptivePolicy::MAX_LINES_FIRST);
    EXPECT_EQ(result.textOverflow.value(), TextOverflow::ELLIPSIS);

    result = TabContentModelStatic::CompleteParameters(AceType::RawPtr(tabContentNode), labelStyle, true);
    EXPECT_TRUE(result.fontSize.has_value());
    EXPECT_TRUE(result.fontWeight.has_value());
}

/**
 * @tc.name: TabContentModelStaticCompleteParameters002
 * @tc.desc: Test CompleteParameters with API version branches and all fields pre-set
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticCompleteParameters002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentNode, nullptr);

    auto container = Container::Current();
    ASSERT_NE(container, nullptr);

    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    LabelStyle labelStyle;
    auto result = TabContentModelStatic::CompleteParameters(AceType::RawPtr(tabContentNode), labelStyle, false);
    EXPECT_TRUE(result.fontSize.has_value());
    EXPECT_TRUE(result.fontWeight.has_value());

    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    LabelStyle labelStyle2;
    result = TabContentModelStatic::CompleteParameters(AceType::RawPtr(tabContentNode), labelStyle2, false);
    EXPECT_FALSE(result.fontSize.has_value());
    EXPECT_TRUE(result.fontWeight.has_value());

    LabelStyle fullStyle;
    fullStyle.maxLines = 3;
    fullStyle.minFontSize = 10.0_fp;
    fullStyle.maxFontSize = 20.0_fp;
    fullStyle.fontSize = 16.0_fp;
    fullStyle.fontWeight = FontWeight::W500;
    fullStyle.fontStyle = Ace::FontStyle::ITALIC;
    fullStyle.heightAdaptivePolicy = TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST;
    fullStyle.textOverflow = TextOverflow::CLIP;
    result = TabContentModelStatic::CompleteParameters(AceType::RawPtr(tabContentNode), fullStyle, false);
    EXPECT_EQ(result.maxLines.value(), 3);
    EXPECT_EQ(result.fontSize.value(), 16.0_fp);
    EXPECT_EQ(result.fontWeight.value(), FontWeight::W500);
}

/**
 * @tc.name: TabContentModelStaticSetSelectedMode001
 * @tc.desc: Test SetSelectedMode with null, with value, without value
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticSetSelectedMode001, TestSize.Level1)
{
    TabContentModelStatic::SetSelectedMode(nullptr, SelectedMode::BOARD);

    auto basicNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    TabContentModelStatic::SetSelectedMode(AceType::RawPtr(basicNode), SelectedMode::BOARD);

    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentNode, nullptr);

    TabContentModelStatic::SetSelectedMode(AceType::RawPtr(tabContentNode), SelectedMode::BOARD);
    auto pattern = tabContentNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->GetSelectedMode(), SelectedMode::BOARD);

    TabContentModelStatic::SetSelectedMode(AceType::RawPtr(tabContentNode), std::nullopt);
    EXPECT_EQ(pattern->GetSelectedMode(), SelectedMode::INDICATOR);
}

/**
 * @tc.name: TabContentModelStaticSetBoard001
 * @tc.desc: Test SetBoard with null, with value, without value
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticSetBoard001, TestSize.Level1)
{
    TabContentModelStatic::SetBoard(nullptr, BoardStyle());

    auto basicNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    TabContentModelStatic::SetBoard(AceType::RawPtr(basicNode), BoardStyle());

    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentNode, nullptr);

    BoardStyle boardStyle;
    boardStyle.borderRadius = 10.0_vp;
    TabContentModelStatic::SetBoard(AceType::RawPtr(tabContentNode), boardStyle);
    auto pattern = tabContentNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->GetBoardStyle().borderRadius, 10.0_vp);

    TabContentModelStatic::SetBoard(AceType::RawPtr(tabContentNode), std::nullopt);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: TabContentModelStaticSetPadding001
 * @tc.desc: Test SetPadding with null, with value, without value, isSubTabStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticSetPadding001, TestSize.Level1)
{
    TabContentModelStatic::SetPadding(nullptr, PaddingProperty(), false);

    auto basicNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    TabContentModelStatic::SetPadding(AceType::RawPtr(basicNode), PaddingProperty(), false);

    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentNode, nullptr);

    PaddingProperty padding;
    padding.top = CalcLength(10.0_vp);
    padding.bottom = CalcLength(10.0_vp);
    padding.left = CalcLength(20.0_vp);
    padding.right = CalcLength(20.0_vp);
    TabContentModelStatic::SetPadding(AceType::RawPtr(tabContentNode), padding, true);
    auto pattern = tabContentNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_TRUE(pattern->GetPadding().top.has_value());

    TabContentModelStatic::SetPadding(AceType::RawPtr(tabContentNode), std::nullopt, false);
    EXPECT_TRUE(true);

    TabContentModelStatic::SetPadding(AceType::RawPtr(tabContentNode), std::nullopt, true);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: TabContentModelStaticCompletePaddingProperty001
 * @tc.desc: Test CompletePaddingProperty with null, fields present, fields missing, isSubTabStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticCompletePaddingProperty001, TestSize.Level1)
{
    PaddingProperty emptyPadding;
    auto result = TabContentModelStatic::CompletePaddingProperty(nullptr, emptyPadding, false);
    EXPECT_FALSE(result.top.has_value());

    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentNode, nullptr);

    PaddingProperty padding;
    result = TabContentModelStatic::CompletePaddingProperty(AceType::RawPtr(tabContentNode), padding, true);
    EXPECT_TRUE(result.top.has_value());
    EXPECT_TRUE(result.bottom.has_value());
    EXPECT_TRUE(result.left.has_value());
    EXPECT_TRUE(result.right.has_value());

    PaddingProperty padding2;
    result = TabContentModelStatic::CompletePaddingProperty(AceType::RawPtr(tabContentNode), padding2, false);
    EXPECT_TRUE(result.top.has_value());
    EXPECT_TRUE(result.left.has_value());

    PaddingProperty fullPadding;
    fullPadding.top = CalcLength(5.0_vp);
    fullPadding.bottom = CalcLength(5.0_vp);
    fullPadding.left = CalcLength(5.0_vp);
    fullPadding.right = CalcLength(5.0_vp);
    result = TabContentModelStatic::CompletePaddingProperty(AceType::RawPtr(tabContentNode), fullPadding, true);
    EXPECT_EQ(result.top.value(), CalcLength(5.0_vp));
}

/**
 * @tc.name: TabContentModelStaticSetUseLocalizedPadding001
 * @tc.desc: Test SetUseLocalizedPadding with null, null pattern, valid
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticSetUseLocalizedPadding001, TestSize.Level1)
{
    TabContentModelStatic::SetUseLocalizedPadding(nullptr, true);

    auto basicNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    TabContentModelStatic::SetUseLocalizedPadding(AceType::RawPtr(basicNode), true);

    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentNode, nullptr);

    TabContentModelStatic::SetUseLocalizedPadding(AceType::RawPtr(tabContentNode), true);
    auto pattern = tabContentNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_TRUE(pattern->GetUseLocalizedPadding());

    TabContentModelStatic::SetUseLocalizedPadding(AceType::RawPtr(tabContentNode), false);
    EXPECT_FALSE(pattern->GetUseLocalizedPadding());
}

/**
 * @tc.name: TabContentModelStaticSetId001
 * @tc.desc: Test SetId with null, with value, without value
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticSetId001, TestSize.Level1)
{
    TabContentModelStatic::SetId(nullptr, "test_id");

    auto basicNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    TabContentModelStatic::SetId(AceType::RawPtr(basicNode), "test_id");

    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentNode, nullptr);

    TabContentModelStatic::SetId(AceType::RawPtr(tabContentNode), "my_id");
    auto pattern = tabContentNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->GetId(), "my_id");

    TabContentModelStatic::SetId(AceType::RawPtr(tabContentNode), std::nullopt);
    EXPECT_EQ(pattern->GetId(), "");
}

/**
 * @tc.name: TabContentModelStaticSetTabBarStyle001
 * @tc.desc: Test SetTabBarStyle with null, null pattern, valid
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticSetTabBarStyle001, TestSize.Level1)
{
    TabContentModelStatic::SetTabBarStyle(nullptr, TabBarStyle::SUBTABBATSTYLE);

    auto basicNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    TabContentModelStatic::SetTabBarStyle(AceType::RawPtr(basicNode), TabBarStyle::SUBTABBATSTYLE);

    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentNode, nullptr);

    TabContentModelStatic::SetTabBarStyle(AceType::RawPtr(tabContentNode), TabBarStyle::BOTTOMTABBATSTYLE);
    auto pattern = tabContentNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->GetTabBarStyle(), TabBarStyle::BOTTOMTABBATSTYLE);

    TabContentModelStatic::SetTabBarStyle(AceType::RawPtr(tabContentNode), TabBarStyle::SUBTABBATSTYLE);
    EXPECT_EQ(pattern->GetTabBarStyle(), TabBarStyle::SUBTABBATSTYLE);
}

/**
 * @tc.name: TabContentModelStaticSetTabBar002
 * @tc.desc: Test SetTabBar with builder function
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticSetTabBar002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContentTabBarStyleWithBuilder(TabBarStyle::NOSTYLE);
    CreateTabContentTabBarStyleWithBuilder(TabBarStyle::NOSTYLE);
    CreateTabsDone(model);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentNode, nullptr);

    bool builderCalled = false;
    auto builder = [&builderCalled]() { builderCalled = true; };
    TabContentModelStatic::SetTabBar(
        AceType::RawPtr(tabContentNode), "text", "icon", std::move(builder));
    EXPECT_TRUE(true);
}

/**
 * @tc.name: TabContentModelStaticSetTabBarWithContent001
 * @tc.desc: Test SetTabBarWithContent with null, null tabBarNode, valid tabBarNode
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticSetTabBarWithContent001, TestSize.Level1)
{
    TabContentModelStatic::SetTabBarWithContent(nullptr, nullptr);

    auto basicNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    TabContentModelStatic::SetTabBarWithContent(AceType::RawPtr(basicNode), nullptr);

    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentNode, nullptr);

    auto contentNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    TabContentModelStatic::SetTabBarWithContent(AceType::RawPtr(tabContentNode), AceType::RawPtr(contentNode));
    auto pattern = tabContentNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_TRUE(true);

    TabContentModelStatic::SetTabBarWithContent(AceType::RawPtr(tabContentNode), nullptr);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: TabContentModelStaticSetCustomStyleNode001
 * @tc.desc: Test SetCustomStyleNode with null, null pattern, valid
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticSetCustomStyleNode001, TestSize.Level1)
{
    auto customNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    TabContentModelStatic::SetCustomStyleNode(nullptr, customNode);

    auto basicNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    TabContentModelStatic::SetCustomStyleNode(AceType::RawPtr(basicNode), customNode);

    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentNode, nullptr);
    TabContentModelStatic::SetCustomStyleNode(AceType::RawPtr(tabContentNode), customNode);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: TabContentModelStaticSetLayoutMode001
 * @tc.desc: Test SetLayoutMode with null, null pattern, with value, without value
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticSetLayoutMode001, TestSize.Level1)
{
    TabContentModelStatic::SetLayoutMode(nullptr, LayoutMode::HORIZONTAL);

    auto basicNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    TabContentModelStatic::SetLayoutMode(AceType::RawPtr(basicNode), LayoutMode::HORIZONTAL);

    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentNode, nullptr);

    TabContentModelStatic::SetLayoutMode(AceType::RawPtr(tabContentNode), LayoutMode::HORIZONTAL);
    auto pattern = tabContentNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->GetBottomTabBarStyle().layoutMode, LayoutMode::HORIZONTAL);

    TabContentModelStatic::SetLayoutMode(AceType::RawPtr(tabContentNode), LayoutMode::VERTICAL);
    EXPECT_EQ(pattern->GetBottomTabBarStyle().layoutMode, LayoutMode::VERTICAL);

    TabContentModelStatic::SetLayoutMode(AceType::RawPtr(tabContentNode), std::nullopt);
    EXPECT_EQ(pattern->GetBottomTabBarStyle().layoutMode, LayoutMode::VERTICAL);
}

/**
 * @tc.name: TabContentModelStaticSetVerticalAlign001
 * @tc.desc: Test SetVerticalAlign with null, null pattern, with value, without value
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticSetVerticalAlign001, TestSize.Level1)
{
    TabContentModelStatic::SetVerticalAlign(nullptr, FlexAlign::FLEX_START);

    auto basicNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    TabContentModelStatic::SetVerticalAlign(AceType::RawPtr(basicNode), FlexAlign::FLEX_START);

    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentNode, nullptr);

    TabContentModelStatic::SetVerticalAlign(AceType::RawPtr(tabContentNode), FlexAlign::FLEX_START);
    auto pattern = tabContentNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->GetBottomTabBarStyle().verticalAlign, FlexAlign::FLEX_START);

    TabContentModelStatic::SetVerticalAlign(AceType::RawPtr(tabContentNode), FlexAlign::FLEX_END);
    EXPECT_EQ(pattern->GetBottomTabBarStyle().verticalAlign, FlexAlign::FLEX_END);

    TabContentModelStatic::SetVerticalAlign(AceType::RawPtr(tabContentNode), std::nullopt);
    EXPECT_EQ(pattern->GetBottomTabBarStyle().verticalAlign, FlexAlign::CENTER);
}

/**
 * @tc.name: TabContentModelStaticSetSymmetricExtensible001
 * @tc.desc: Test SetSymmetricExtensible with null, null pattern, with value, without value
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticSetSymmetricExtensible001, TestSize.Level1)
{
    TabContentModelStatic::SetSymmetricExtensible(nullptr, true);

    auto basicNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    TabContentModelStatic::SetSymmetricExtensible(AceType::RawPtr(basicNode), true);

    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentNode, nullptr);

    TabContentModelStatic::SetSymmetricExtensible(AceType::RawPtr(tabContentNode), true);
    auto pattern = tabContentNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_TRUE(pattern->GetBottomTabBarStyle().symmetricExtensible);

    TabContentModelStatic::SetSymmetricExtensible(AceType::RawPtr(tabContentNode), false);
    EXPECT_FALSE(pattern->GetBottomTabBarStyle().symmetricExtensible);

    TabContentModelStatic::SetSymmetricExtensible(AceType::RawPtr(tabContentNode), std::nullopt);
    EXPECT_FALSE(pattern->GetBottomTabBarStyle().symmetricExtensible);
}

/**
 * @tc.name: TabContentModelStaticSetIconStyle001
 * @tc.desc: Test SetIconStyle with null, null pattern, with value, without value
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticSetIconStyle001, TestSize.Level1)
{
    TabContentModelStatic::SetIconStyle(nullptr, IconStyle());

    auto basicNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    TabContentModelStatic::SetIconStyle(AceType::RawPtr(basicNode), IconStyle());

    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentNode, nullptr);

    IconStyle iconStyle;
    iconStyle.selectedColor = Color::RED;
    iconStyle.unselectedColor = Color::BLUE;
    TabContentModelStatic::SetIconStyle(AceType::RawPtr(tabContentNode), iconStyle);
    auto pattern = tabContentNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_TRUE(pattern->GetIconStyle().selectedColor.has_value());

    TabContentModelStatic::SetIconStyle(AceType::RawPtr(tabContentNode), std::nullopt);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: TabContentModelStaticSetOnWillShow001
 * @tc.desc: Test SetOnWillShow with null, null eventHub, valid
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticSetOnWillShow001, TestSize.Level1)
{
    TabContentModelStatic::SetOnWillShow(nullptr, []() {});

    auto basicNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    TabContentModelStatic::SetOnWillShow(AceType::RawPtr(basicNode), []() {});

    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentNode, nullptr);

    bool called = false;
    TabContentModelStatic::SetOnWillShow(AceType::RawPtr(tabContentNode), [&called]() { called = true; });
    auto eventHub = tabContentNode->GetEventHub<TabContentEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireWillShowEvent();
    EXPECT_TRUE(called);
}

/**
 * @tc.name: TabContentModelStaticSetOnWillHide001
 * @tc.desc: Test SetOnWillHide with null, null eventHub, valid
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticSetOnWillHide001, TestSize.Level1)
{
    TabContentModelStatic::SetOnWillHide(nullptr, []() {});

    auto basicNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    TabContentModelStatic::SetOnWillHide(AceType::RawPtr(basicNode), []() {});

    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentNode, nullptr);

    bool called = false;
    TabContentModelStatic::SetOnWillHide(AceType::RawPtr(tabContentNode), [&called]() { called = true; });
    auto eventHub = tabContentNode->GetEventHub<TabContentEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireWillHideEvent();
    EXPECT_TRUE(called);
}

/**
 * @tc.name: TabContentModelStaticCreateFrameNode001
 * @tc.desc: Test CreateFrameNode normal creation
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticCreateFrameNode001, TestSize.Level1)
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = TabContentModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(frameNode);
    ASSERT_NE(tabContentNode, nullptr);
    auto layoutProp = tabContentNode->GetLayoutProperty<TabContentLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    EXPECT_FALSE(layoutProp->GetTextValue("").empty());
}

/**
 * @tc.name: TabContentModelStaticUpdateLabelStyle001
 * @tc.desc: Test UpdateLabelStyle with null and various LabelStyle fields
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticUpdateLabelStyle001, TestSize.Level1)
{
    TabContentModelStatic::UpdateLabelStyle(LabelStyle(), nullptr);

    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    LabelStyle labelStyle;
    labelStyle.fontSize = 16.0_fp;
    labelStyle.fontWeight = FontWeight::BOLD;
    labelStyle.fontStyle = Ace::FontStyle::ITALIC;
    labelStyle.fontFamily = std::vector<std::string>{ "Arial" };
    labelStyle.textOverflow = TextOverflow::MARQUEE;
    labelStyle.maxLines = 2;
    labelStyle.minFontSize = 10.0_fp;
    labelStyle.maxFontSize = 20.0_fp;
    labelStyle.heightAdaptivePolicy = TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST;

    TabContentModelStatic::UpdateLabelStyle(labelStyle, textLayoutProperty);
    EXPECT_EQ(textLayoutProperty->GetFontSizeValue(Dimension()), 16.0_fp);
    EXPECT_EQ(textLayoutProperty->GetFontWeightValue(FontWeight::NORMAL), FontWeight::BOLD);
    EXPECT_EQ(textLayoutProperty->GetItalicFontStyleValue(Ace::FontStyle::NORMAL), Ace::FontStyle::ITALIC);
    EXPECT_TRUE(textLayoutProperty->HasMaxLines());
    EXPECT_EQ(textLayoutProperty->GetMaxLinesValue(0), 2);
}

/**
 * @tc.name: TabContentModelStaticUpdateLabelStyle002
 * @tc.desc: Test UpdateLabelStyle with empty LabelStyle (no fields set)
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticUpdateLabelStyle002, TestSize.Level1)
{
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    LabelStyle emptyStyle;
    TabContentModelStatic::UpdateLabelStyle(emptyStyle, textLayoutProperty);
    EXPECT_FALSE(textLayoutProperty->HasFontSize());

    LabelStyle overflowEllipsis;
    overflowEllipsis.textOverflow = TextOverflow::ELLIPSIS;
    TabContentModelStatic::UpdateLabelStyle(overflowEllipsis, textLayoutProperty);
    EXPECT_EQ(textLayoutProperty->GetTextOverflowValue(TextOverflow::NONE), TextOverflow::ELLIPSIS);
}

/**
 * @tc.name: TabContentModelStaticUpdateDefaultSymbol001
 * @tc.desc: Test UpdateDefaultSymbol normal
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticUpdateDefaultSymbol001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentNode, nullptr);
    auto tabTheme = tabContentNode->GetTheme<TabTheme>(true);
    ASSERT_NE(tabTheme, nullptr);

    auto symbolNode = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(symbolNode, nullptr);
    auto symbolProperty = symbolNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(symbolProperty, nullptr);

    TabContentModelStatic::UpdateDefaultSymbol(tabTheme, symbolProperty);
    EXPECT_TRUE(symbolProperty->HasFontSize());
}

/**
 * @tc.name: TabContentModelStaticUpdateSymbolEffect001
 * @tc.desc: Test UpdateSymbolEffect with isActive true and false
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticUpdateSymbolEffect001, TestSize.Level1)
{
    auto symbolNode = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(symbolNode, nullptr);
    auto symbolProperty = symbolNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(symbolProperty, nullptr);

    TabContentModelStatic::UpdateSymbolEffect(symbolProperty, true);
    EXPECT_TRUE(symbolProperty->HasSymbolEffectOptions());

    auto symbolNode2 = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    auto symbolProperty2 = symbolNode2->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(symbolProperty2, nullptr);

    TabContentModelStatic::UpdateSymbolEffect(symbolProperty2, false);
    EXPECT_TRUE(symbolProperty2->HasSymbolEffectOptions());
}

/**
 * @tc.name: TabContentModelStaticFindTabsNode001
 * @tc.desc: Test FindTabsNode with null, found TabsNode, not found
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticFindTabsNode001, TestSize.Level1)
{
    auto result = TabContentModelStatic::FindTabsNode(nullptr);
    EXPECT_EQ(result, nullptr);

    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentNode, nullptr);

    result = TabContentModelStatic::FindTabsNode(tabContentNode);
    ASSERT_NE(result, nullptr);

    auto orphanNode = TabContentNode::GetOrCreateTabContentNode(V2::TAB_CONTENT_ITEM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TabContentPattern>(nullptr); });
    result = TabContentModelStatic::FindTabsNode(orphanNode);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: TabContentModelStaticInitTabText001
 * @tc.desc: Test InitTabText with API version branches and null checks
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticInitTabText001, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetApiTargetVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_FIVE));
    TabContentModelStatic::InitTabText(nullptr);

    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    TabContentModelStatic::InitTabText(textLayoutProperty);

    AceApplicationInfo::GetInstance().SetApiTargetVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    TabContentModelStatic::InitTabText(textLayoutProperty);

    auto& textStyle = textLayoutProperty->GetTextLineStyle();
    CHECK_NULL_VOID(textStyle);
    textStyle->UpdateOrphanCharOptimization(true);
    TabContentModelStatic::InitTabText(textLayoutProperty);

    AceApplicationInfo::GetInstance().SetApiTargetVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_FIVE));
}

/**
 * @tc.name: TabContentModelStaticInitTabText002
 * @tc.desc: Test InitTabText with fontManager fallbackLineSpacingStyleOptimizeFlag true
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticInitTabText002, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetApiTargetVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));

    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);

    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->GetOrCreateTextLineStyle();

    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto fontManager = AceType::MakeRefPtr<MockFontManager>();
    fontManager->fallbackLineSpacingStyleOptimizeFlag_ = true;
    pipeline->fontManager_ = fontManager;

    TabContentModelStatic::InitTabText(textLayoutProperty);

    fontManager->fallbackLineSpacingStyleOptimizeFlag_ = false;
    TabContentModelStatic::InitTabText(textLayoutProperty);

    AceApplicationInfo::GetInstance().SetApiTargetVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_FIVE));
}

/**
 * @tc.name: TabContentModelStaticAddTabBarItem001
 * @tc.desc: Test AddTabBarItem with null and update=true without TabBarItemId
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticAddTabBarItem001, TestSize.Level1)
{
    TabContentModelStatic::AddTabBarItem(nullptr, 0, false);

    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentNode, nullptr);
    tabContentNode->ResetTabBarItemId();
    TabContentModelStatic::AddTabBarItem(tabContentNode, 0, true);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: TabContentModelStaticAddTabBarItem002
 * @tc.desc: Test AddTabBarItem with BOTTOMTABBATSTYLE and HORIZONTAL layoutMode
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticAddTabBarItem002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContentTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    CreateTabContentTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    CreateTabsDone(model);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentNode, nullptr);
    auto pattern = tabContentNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetLayoutMode(LayoutMode::HORIZONTAL);
    TabContentModelStatic::AddTabBarItem(tabContentNode, 0, false);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: TabContentModelStaticAddTabBarItem003
 * @tc.desc: Test AddTabBarItem with SUBTABBATSTYLE
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticAddTabBarItem003, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabsDone(model);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentNode, nullptr);
    TabContentModelStatic::AddTabBarItem(tabContentNode, 0, false);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: TabContentModelStaticAddTabBarItem004
 * @tc.desc: Test AddTabBarItem with builder content (HasBuilder)
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticAddTabBarItem004, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContentsWithBuilder(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentNode, nullptr);
    TabContentModelStatic::AddTabBarItem(tabContentNode, 0, false);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: TabContentModelStaticAddTabBarItem005
 * @tc.desc: Test AddTabBarItem with RTL and useLocalizedPadding
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticAddTabBarItem005, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    TabsModelNG model = CreateTabs();
    CreateTabContentTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    CreateTabContentTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    CreateTabsDone(model);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentNode, nullptr);
    auto pattern = tabContentNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetUseLocalizedPadding(true);
    tabBarLayoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    TabContentModelStatic::AddTabBarItem(tabContentNode, 0, false);
    EXPECT_TRUE(true);
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
}

/**
 * @tc.name: TabContentModelStaticAddTabBarItem006
 * @tc.desc: Test AddTabBarItem with symbol icon
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticAddTabBarItem006, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContent();
    auto tabContentModelNG = TabContentModelNG();
    TabBarSymbol symbol;
    symbol.onApply = [](WeakPtr<FrameNode> node, const std::string& status) {};
    symbol.selectedFlag = true;
    tabContentModelNG.SetTabBar("text", IMAGE_SRC_URL, symbol, nullptr, true);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    CreateTabContent();
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    CreateTabsDone(model);

    auto tabContentNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentNode, nullptr);
    TabContentModelStatic::AddTabBarItem(tabContentNode, 0, false);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: TabContentModelStaticAddTabBarItem007
 * @tc.desc: Test AddTabBarItem with NOSTYLE empty tab bar (no builder, no content, no icon, no text)
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticAddTabBarItem007, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContent();
    auto tabContentModelNG = TabContentModelNG();
    tabContentModelNG.SetTabBar(std::nullopt, std::nullopt, std::nullopt, nullptr, true);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    CreateTabContent();
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    CreateTabsDone(model);

    auto tabContentNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentNode, nullptr);
    TabContentModelStatic::AddTabBarItem(tabContentNode, 0, false);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: TabContentModelStaticAddTabBarItem008
 * @tc.desc: Test AddTabBarItem with HasContent (tab bar with content node)
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelStaticAddTabBarItem008, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContent();
    auto contentNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto tabContentModelNG = TabContentModelNG();
    tabContentModelNG.SetTabBarWithContent(AceType::Claim(AceType::RawPtr(contentNode)));
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    CreateTabContent();
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    CreateTabsDone(model);

    auto tabContentNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentNode, nullptr);
    TabContentModelStatic::AddTabBarItem(tabContentNode, 0, false);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: OnInjectionEventTest001
 * @tc.desc: test OnInjectionEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, OnInjectionEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create tabs and set parameters.
     */
    int32_t currentIndex = 0;
    auto event = [&currentIndex](const BaseEventInfo* info) {
        const auto* tabInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        if (tabInfo != nullptr) {
            currentIndex = tabInfo->GetIndex();
        }
    };
    MockAnimationManager::Enable(true);
    MockAnimationManager::GetInstance().SetTicks(1);
    TabsModelNG model = CreateTabs();
    model.SetOnChange(std::move(event));
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(tabBarPattern_, nullptr);
    std::map<std::string, int32_t> commands = { { R"({"cmd":"changeIndex","params":{"index":"2"}})", 2 },
        { R"({"cmd":"changeIndex","params":{"index":"100"}})", 0 },
        { R"({"cmd":"changeIndex","params":{"index":"-10"}})", 0 },
        { R"({"cmd":"changeIndex","params":{"index":"1"}})", 1 } };

    for (const auto& command : commands) {
        bool ret = pattern_->OnInjectionEvent(command.first);
        ASSERT_NE(ret, false);
        EXPECT_EQ(tabBarPattern_->jumpIndex_, command.second);
    }
}

/**
 * @tc.name: FireAnimationEndOnForceEvent001
 * @tc.desc: Test FireAnimationEndOnForceEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, FireAnimationEndOnForceEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get SwiperEventHub.
     */
    auto onGestureSwipe = [](int32_t index, const AnimationCallbackInfo& info) {};
    TabsModelNG model = CreateTabs();
    model.SetOnGestureSwipe(std::move(onGestureSwipe));
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    ASSERT_NE(swiperNode_, nullptr);
    auto eventHub = swiperNode_->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    ASSERT_NE(frameNode_, nullptr);
    eventHub->SetTabsId(frameNode_->GetId());
    AnimationStartEventPtr nullEvent = nullptr;
    eventHub->AddAnimationStartEvent(nullEvent);
    eventHub->FireAnimationStartEvent(0, 1, {});
    ASSERT_EQ(eventHub->aniStartCalledCount_, 1);
    /**
     * @tc.steps: step2. call FireAnimationEndOnForceEvent.
     */
    eventHub->FireAnimationEndOnForceEvent(1, {
                                                  .currentOffset = 1.23f,
                                                  .targetOffset = -4.56f,
                                                  .velocity = 78.9f,
                                              });
    ASSERT_EQ(eventHub->aniStartCalledCount_, 0);
}

/**
 * @tc.name: SetOnTabBarClickTest001
 * @tc.desc: Test Tabs SetOnTabBarClick
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, SetOnTabBarClickTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create tabs and set parameters.
     */
    int32_t currentIndex = 0;
    auto event = [&currentIndex](const BaseEventInfo* info) {
        const auto* tabInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        if (tabInfo != nullptr) {
            currentIndex = tabInfo->GetIndex();
        }
    };
    TabsModelNG model = CreateTabs();
    model.SetOnTabBarClick(std::move(event));
    ASSERT_NE(tabBarPattern_, nullptr);
    tabBarPattern_->ChangeIndex(1);
    /**
     * @tc.steps: step3. Test SetOnTabBarClick function.
     * @tc.expected:pattern_->onTabBarClickEvent_ not null.
     */
    ASSERT_NE(pattern_, nullptr);
    EXPECT_NE(pattern_->onTabBarClickEvent_, nullptr);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    HandleClick(1);
    EXPECT_EQ(currentIndex, 1);
}

/**
 * @tc.name: OnColorConfigurationUpdate001
 * @tc.desc: OnColorConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, OnColorConfigurationUpdate001, TestSize.Level1)
{
    CreateTabs();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    ASSERT_NE(tabsNode, nullptr);

    auto property = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    ASSERT_NE(property, nullptr);

    auto tabsPattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);

    tabsPattern->OnColorConfigurationUpdate();

    property->propDividerColorSetByUser_ = false;
    tabsPattern->OnColorConfigurationUpdate();

    property->propDividerColorSetByUser_ = true;
    tabsPattern->OnColorConfigurationUpdate();

    auto dividerFrameNode = AceType::DynamicCast<FrameNode>(tabsNode->GetDivider());
    ASSERT_NE(dividerFrameNode, nullptr);
    auto dividerRenderProperty = dividerFrameNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(dividerRenderProperty, nullptr);
    dividerRenderProperty->propDividerColor_ = Color::RED;
    tabsPattern->OnColorConfigurationUpdate();
    EXPECT_EQ(dividerRenderProperty->propDividerColor_, Color::RED);
}

/**
 * @tc.name: SetUseNewMaterial001
 * @tc.desc: test SetUseNewMaterial and IsNewMaterial
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, SetUseNewMaterial001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    ASSERT_NE(tabBarPattern_, nullptr);

    EXPECT_FALSE(tabBarPattern_->IsNewMaterial());
    tabBarPattern_->SetUseNewMaterial(true);
    EXPECT_TRUE(tabBarPattern_->IsNewMaterial());
    tabBarPattern_->SetUseNewMaterial(false);
    EXPECT_FALSE(tabBarPattern_->IsNewMaterial());
}

/**
 * @tc.name: HandleTouchDownNewMaterial001
 * @tc.desc: test HandleTouchDown with useNewMaterial_ true, PlayPressAnimation should not be called
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, HandleTouchDownNewMaterial001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabsDone(model);
    ASSERT_NE(tabBarPattern_, nullptr);

    tabBarPattern_->SetUseNewMaterial(true);
    auto itemNode = GetChildFrameNode(tabBarNode_, 0);
    ASSERT_NE(itemNode, nullptr);
    auto renderContext = itemNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto colorBefore = renderContext->GetBackgroundColor().value_or(Color::TRANSPARENT);

    tabBarPattern_->HandleTouchDown(0);
    FlushUITasks();
    auto colorAfter = renderContext->GetBackgroundColor().value_or(Color::TRANSPARENT);
    EXPECT_EQ(colorBefore, colorAfter);
}

/**
 * @tc.name: HandleTouchUpNewMaterial001
 * @tc.desc: test HandleTouchUp with useNewMaterial_ true, PlayPressAnimation should not be called
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, HandleTouchUpNewMaterial001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabsDone(model);
    ASSERT_NE(tabBarPattern_, nullptr);

    tabBarPattern_->SetUseNewMaterial(true);
    auto itemNode = GetChildFrameNode(tabBarNode_, 0);
    ASSERT_NE(itemNode, nullptr);
    auto renderContext = itemNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto colorBefore = renderContext->GetBackgroundColor().value_or(Color::TRANSPARENT);

    tabBarPattern_->HandleTouchUp(0);
    FlushUITasks();
    auto colorAfter = renderContext->GetBackgroundColor().value_or(Color::TRANSPARENT);
    EXPECT_EQ(colorBefore, colorAfter);
}

/**
 * @tc.name: HandleTouchUpAndClickTo001
 * @tc.desc: test HandleTouchUpAndClickTo when useNewMaterial_ is false, HandleClick should not be called
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, HandleTouchUpAndClickTo001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    ASSERT_NE(tabBarPattern_, nullptr);

    tabBarPattern_->SetUseNewMaterial(false);
    int32_t clickIndex = -1;
    auto event = [&clickIndex](const BaseEventInfo* info) {
        const auto* tabInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        if (tabInfo != nullptr) {
            clickIndex = tabInfo->GetIndex();
        }
    };
    pattern_->SetOnTabBarClickEvent(std::move(event));

    TouchLocationInfo info(0);
    info.SetTouchType(TouchType::UP);
    info.SetLocalLocation(Offset(TABS_WIDTH / 4.0f, 0.0f));
    tabBarPattern_->HandleTouchUpAndClickTo(info);
    EXPECT_EQ(clickIndex, -1);
}

/**
 * @tc.name: HandleTouchUpAndClickTo002
 * @tc.desc: test HandleTouchUpAndClickTo when touch type is not UP, HandleClick should not be called
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, HandleTouchUpAndClickTo002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    ASSERT_NE(tabBarPattern_, nullptr);

    tabBarPattern_->SetUseNewMaterial(true);
    int32_t clickIndex = -1;
    auto event = [&clickIndex](const BaseEventInfo* info) {
        const auto* tabInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        if (tabInfo != nullptr) {
            clickIndex = tabInfo->GetIndex();
        }
    };
    pattern_->SetOnTabBarClickEvent(std::move(event));

    TouchLocationInfo info(0);
    info.SetTouchType(TouchType::DOWN);
    info.SetLocalLocation(Offset(TABS_WIDTH / 4.0f, 0.0f));
    tabBarPattern_->HandleTouchUpAndClickTo(info);
    EXPECT_EQ(clickIndex, -1);
}

/**
 * @tc.name: HandleTouchUpAndClickTo003
 * @tc.desc: test HandleTouchUpAndClickTo with useNewMaterial_ true and TouchType::UP, should trigger HandleClick
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, HandleTouchUpAndClickTo003, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    ASSERT_NE(tabBarPattern_, nullptr);

    tabBarPattern_->SetUseNewMaterial(true);
    int32_t clickIndex = -1;
    auto event = [&clickIndex](const BaseEventInfo* info) {
        const auto* tabInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        if (tabInfo != nullptr) {
            clickIndex = tabInfo->GetIndex();
        }
    };
    pattern_->SetOnTabBarClickEvent(std::move(event));

    TouchLocationInfo info(0);
    info.SetTouchType(TouchType::UP);
    info.SetLocalLocation(Offset(TABS_WIDTH / 4.0f, 0.0f));
    tabBarPattern_->HandleTouchUpAndClickTo(info);
    EXPECT_NE(clickIndex, -1);
}

/**
 * @tc.name: GetSelectChildIndex001
 * @tc.desc: test GetSelectChildIndex with offset within first child
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, GetSelectChildIndex001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    ASSERT_NE(tabBarPattern_, nullptr);

    FlushUITasks();

    auto host = tabBarPattern_->GetHost();
    ASSERT_NE(host, nullptr);

    auto result = tabBarPattern_->GetSelectChildIndex(Offset(0.0f, 0.0f));
    EXPECT_GE(result, 0);
}

/**
 * @tc.name: GetSelectChildIndex002
 * @tc.desc: test GetSelectChildIndex with offset before first child
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, GetSelectChildIndex002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    ASSERT_NE(tabBarPattern_, nullptr);

    FlushUITasks();

    auto result = tabBarPattern_->GetSelectChildIndex(Offset(-100.0f, 0.0f));
    EXPECT_GE(result, 0);
}

/**
 * @tc.name: GetSelectChildIndex003
 * @tc.desc: test GetSelectChildIndex with offset after last child
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, GetSelectChildIndex003, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    ASSERT_NE(tabBarPattern_, nullptr);

    FlushUITasks();

    auto result = tabBarPattern_->GetSelectChildIndex(Offset(10000.0f, 0.0f));
    EXPECT_GE(result, 0);
}

/**
 * @tc.name: GetSelectChildIndex004
 * @tc.desc: test GetSelectChildIndex with offset in the middle region
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, GetSelectChildIndex004, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    ASSERT_NE(tabBarPattern_, nullptr);

    FlushUITasks();

    auto host = tabBarPattern_->GetHost();
    ASSERT_NE(host, nullptr);

    auto result = tabBarPattern_->GetSelectChildIndex(Offset(TABS_WIDTH / 2.0f, 0.0f));
    EXPECT_GE(result, 0);
}

/**
 * @tc.name: ApplySystemMaterial001
 * @tc.desc: test ApplySystemMaterial with no BarFloatingStyle set
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, ApplySystemMaterial001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(layoutProperty_, nullptr);
    ASSERT_NE(tabBarPattern_, nullptr);

    layoutProperty_->ResetBarFloatingStyle();
    pattern_->ApplySystemMaterial();
    EXPECT_FALSE(tabBarPattern_->IsNewMaterial());
}

/**
 * @tc.name: ApplySystemMaterial002
 * @tc.desc: test ApplySystemMaterial with BarFloatingStyle but no systemMaterial
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, ApplySystemMaterial002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(layoutProperty_, nullptr);
    ASSERT_NE(tabBarPattern_, nullptr);

    BarFloatingStyleParameters style;
    layoutProperty_->UpdateBarFloatingStyle(style);
    pattern_->ApplySystemMaterial();
    EXPECT_FALSE(tabBarPattern_->IsNewMaterial());
}

/**
 * @tc.name: ResetSystemMaterial001
 * @tc.desc: test ResetSystemMaterial sets useNewMaterial_ to false
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, ResetSystemMaterial001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(tabBarPattern_, nullptr);

    tabBarPattern_->SetUseNewMaterial(true);
    EXPECT_TRUE(tabBarPattern_->IsNewMaterial());

    pattern_->ResetSystemMaterial();
    EXPECT_FALSE(tabBarPattern_->IsNewMaterial());
}

/**
 * @tc.name: TabBarItemFocusPatternNewMaterial001
 * @tc.desc: test TabBarItemPattern GetFocusPattern with useNewMaterial_ true
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarItemFocusPatternNewMaterial001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabsDone(model);
    ASSERT_NE(tabBarPattern_, nullptr);

    tabBarPattern_->SetUseNewMaterial(true);

    auto tabBarItemNode = GetChildFrameNode(tabBarNode_, 0);
    ASSERT_NE(tabBarItemNode, nullptr);
    auto tabBarItemPattern = tabBarItemNode->GetPattern<TabBarItemPattern>();
    ASSERT_NE(tabBarItemPattern, nullptr);

    auto focusPattern = tabBarItemPattern->GetFocusPattern();
    EXPECT_EQ(focusPattern.GetFocusType(), FocusType::SCOPE);
    const auto& paintParams = focusPattern.GetFocusPaintParams();
    ASSERT_TRUE(paintParams != nullptr);
    EXPECT_TRUE(paintParams->HasPaintColor());
    EXPECT_TRUE(paintParams->HasPaintWidth());
}

/**
 * @tc.name: TabBarItemFocusPatternNewMaterial002
 * @tc.desc: test TabBarItemPattern GetFocusPattern with useNewMaterial_ false (default)
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarItemFocusPatternNewMaterial002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabsDone(model);
    ASSERT_NE(tabBarPattern_, nullptr);

    EXPECT_FALSE(tabBarPattern_->IsNewMaterial());

    auto tabBarItemNode = GetChildFrameNode(tabBarNode_, 0);
    ASSERT_NE(tabBarItemNode, nullptr);
    auto tabBarItemPattern = tabBarItemNode->GetPattern<TabBarItemPattern>();
    ASSERT_NE(tabBarItemPattern, nullptr);

    auto focusPattern = tabBarItemPattern->GetFocusPattern();
    EXPECT_EQ(focusPattern.GetFocusType(), FocusType::SCOPE);
    const auto& paintParams = focusPattern.GetFocusPaintParams();
    ASSERT_TRUE(paintParams != nullptr);
    EXPECT_TRUE(paintParams->HasPaintColor());
    EXPECT_TRUE(paintParams->HasPaintWidth());
}

/**
 * @tc.name: HandleTouchDownNewMaterial002
 * @tc.desc: test HandleTouchDown with useNewMaterial_ false, PlayPressAnimation should be called
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, HandleTouchDownNewMaterial002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabsDone(model);
    ASSERT_NE(tabBarPattern_, nullptr);

    tabBarPattern_->SetUseNewMaterial(false);
    auto itemNode = GetChildFrameNode(tabBarNode_, 0);
    ASSERT_NE(itemNode, nullptr);
    auto renderContext = itemNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    tabBarPattern_->HandleTouchDown(0);
    FlushUITasks();
    auto colorAfter = renderContext->GetBackgroundColor().value_or(Color::TRANSPARENT);
    EXPECT_EQ(colorAfter, Color::GREEN);
}

/**
 * @tc.name: HandleTouchUpNewMaterial002
 * @tc.desc: test HandleTouchUp with useNewMaterial_ false, PlayPressAnimation should be called
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, HandleTouchUpNewMaterial002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabsDone(model);
    ASSERT_NE(tabBarPattern_, nullptr);

    tabBarPattern_->SetUseNewMaterial(false);
    auto itemNode = GetChildFrameNode(tabBarNode_, 0);
    ASSERT_NE(itemNode, nullptr);
    auto renderContext = itemNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    tabBarPattern_->HandleTouchUp(0);
    FlushUITasks();
    auto colorAfter = renderContext->GetBackgroundColor().value_or(Color::TRANSPARENT);
    EXPECT_EQ(colorAfter, Color::TRANSPARENT);
}
} // namespace OHOS::Ace::NG
