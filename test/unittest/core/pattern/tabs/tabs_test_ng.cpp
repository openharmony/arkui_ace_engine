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

namespace OHOS::Ace::NG {
namespace {}

void TabsTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto tabTheme = AceType::MakeRefPtr<TabTheme>();
    tabTheme->defaultTabBarName_ = "tabBarItemName";
    tabTheme->tabBarDefaultWidth_ = Dimension(TABBAR_DEFAULT_WIDTH);
    tabTheme->tabBarDefaultHeight_ = Dimension(TABBAR_DEFAULT_HEIGHT);
    tabTheme->subTabBarHoverColor_ = Color::RED;
    tabTheme->subTabBarPressedColor_ = Color::GREEN;
    tabTheme->bottomTabIconOn_ = Color::BLUE;
    tabTheme->bottomTabIconOff_ = Color::BLACK;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(tabTheme));
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
}

void TabsTestNg::GetInstance()
{
    // tabs
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
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

void TabsTestNg::Create(const std::function<void(TabsModelNG)>& callback, BarPosition barPosition, int32_t index)
{
    TabsModelNG model;
    model.Create(barPosition, index, nullptr, nullptr);
    ViewAbstract::SetWidth(CalcLength(TABS_WIDTH));
    ViewAbstract::SetHeight(CalcLength(TABS_HEIGHT));
    if (callback) {
        callback(model);
    }
    auto tabNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabNode->GetTabBar());
    tabBarNode->GetOrCreateFocusHub();
    model.Pop();
    GetInstance();
    FlushLayoutTask(frameNode_);
}

void TabsTestNg::CreateWithItem(
    const std::function<void(TabsModelNG)>& callback, BarPosition barPosition, int32_t index)
{
    Create(
        [callback](TabsModelNG model) {
            if (callback) {
                callback(model);
            }
            CreateItem(TABCONTENT_NUMBER);
        },
        barPosition, index);
}

void TabsTestNg::CreateWithItemWithoutBuilder(
    const std::function<void(TabsModelNG)>& callback, BarPosition barPosition, int32_t index)
{
    Create(
        [callback](TabsModelNG model) {
            if (callback) {
                callback(model);
            }
            for (int32_t index = 0; index < TABCONTENT_NUMBER; index++) {
                CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, index);
            }
        },
        barPosition, index);
}

void TabsTestNg::CreateItem(int32_t itemNumber, const std::function<void(TabContentModelNG, int32_t)>& callback)
{
    auto tabFrameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto weakTab = AceType::WeakClaim(AceType::RawPtr(tabFrameNode));
    int32_t nodeId = 0;
    for (int32_t index = 0; index < itemNumber; index++) {
        TabContentModelNG model;
        model.Create();
        auto tabBarItemFunc = TabBarItemBuilder();
        model.SetTabBar("", "", std::nullopt, std::move(tabBarItemFunc), true);
        ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
        ViewAbstract::SetHeight(CalcLength(FILL_LENGTH));
        if (callback) {
            callback(model, index);
        }
        auto tabContentFrameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
        auto tabContentNode = AceType::DynamicCast<TabContentNode>(tabContentFrameNode);
        tabContentNode->UpdateRecycleElmtId(nodeId); // for AddChildToGroup
        tabContentNode->GetTabBarItemId();           // for AddTabBarItem
        tabContentNode->SetParent(weakTab);          // for AddTabBarItem
        model.Pop();
        nodeId++;
    }
}

void TabsTestNg::CreateSingleItem(const std::function<void(TabContentModelNG)>& callback, int32_t nodeId)
{
    auto tabFrameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto weakTab = AceType::WeakClaim(AceType::RawPtr(tabFrameNode));
    TabContentModelNG model;
    model.Create();
    auto tabBarItemFunc = TabBarItemBuilder();
    model.SetTabBar("", "", std::nullopt, std::move(tabBarItemFunc), true);
    if (callback) {
        callback(model);
    }
    ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
    ViewAbstract::SetHeight(CalcLength(FILL_LENGTH));
    auto tabContentFrameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(tabContentFrameNode);
    tabContentNode->UpdateRecycleElmtId(nodeId); // for AddChildToGroup
    tabContentNode->GetTabBarItemId(); // for AddTabBarItem
    tabContentNode->SetParent(weakTab); // for AddTabBarItem
    model.Pop();
}

void TabsTestNg::CreateSingleItemWithoutBuilder(const std::function<void(TabContentModelNG)>& callback, int32_t nodeId)
{
    auto tabFrameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto weakTab = AceType::WeakClaim(AceType::RawPtr(tabFrameNode));
    TabContentModelNG model;
    model.Create();
    model.SetTabBar("", "", std::nullopt, nullptr, true);
    if (callback) {
        callback(model);
    }
    ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
    ViewAbstract::SetHeight(CalcLength(FILL_LENGTH));
    auto tabContentFrameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(tabContentFrameNode);
    tabContentNode->UpdateRecycleElmtId(nodeId); // for AddChildToGroup
    tabContentNode->GetTabBarItemId(); // for AddTabBarItem
    tabContentNode->SetParent(weakTab); // for AddTabBarItem
    model.Pop();
}

TabBarBuilderFunc TabsTestNg::TabBarItemBuilder()
{
    return []() {
        ColumnModelNG colModel;
        colModel.Create(Dimension(0), nullptr, "");
        ViewAbstract::SetWidth(CalcLength(10.f));
        ViewAbstract::SetHeight(CalcLength(10.f));
    };
}

void TabsTestNg::SwipeToWithoutAnimation(int32_t index)
{
    swiperController_->SwipeToWithoutAnimation(index);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE); // for update swiper
    FlushLayoutTask(frameNode_);
}

void TabsTestNg::ClickTo(Offset offset)
{
    GestureEvent info;
    info.SetLocalLocation(offset);
    tabBarPattern_->HandleClick(info);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE); // for update swiper
    FlushLayoutTask(frameNode_);
}

void TabsTestNg::MouseTo(MouseAction action, Offset location, bool isHover)
{
    MouseInfo mouseInfo;
    mouseInfo.SetAction(action);
    mouseInfo.SetLocalLocation(location);
    tabBarPattern_->HandleMouseEvent(mouseInfo);
    // when on the tabBar is true, else false
    tabBarPattern_->HandleHoverEvent(isHover);
}

void TabsTestNg::TouchTo(TouchType type, Offset location)
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
    CreateWithItem([](TabsModelNG model) {});

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
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 1);
    }, BarPosition::END);

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
 * @tc.name: TabContentNodelConvertFlexAlignToString001
 * @tc.desc: Test the ConvertFlexAlignToString function in the TabContentNodel class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentNodelConvertFlexAlignToString001, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {}, 0);
    });
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    FlexAlign verticalAlign = FlexAlign::FLEX_START;
    tabContentFrameNode->ConvertFlexAlignToString(verticalAlign);
    verticalAlign = FlexAlign::FLEX_END;
    tabContentFrameNode->ConvertFlexAlignToString(verticalAlign);

    /**
     * @tc.steps: steps2. ConvertFlexAlignToString.
     * @tc.expected: steps2. Check the result of ConvertFlexAlignToString.
     */
    EXPECT_EQ(tabContentFrameNode->ConvertFlexAlignToString(verticalAlign), "VerticalAlign.Bottom");
}

/**
 * @tc.name: TabContentNodelConvertLayoutModeToString001
 * @tc.desc: Test the ConvertLayoutModeToString function in the TabContentNodel class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentNodelConvertLayoutModeToString001, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {}, 0);
    });
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();

    /**
     * @tc.steps: steps2. Set different values for layoutMode to enter different branches.
     */
    LayoutMode layoutMode = LayoutMode::VERTICAL;
    tabContentFrameNode->ConvertLayoutModeToString(layoutMode);
    layoutMode = LayoutMode::HORIZONTAL;
    tabContentFrameNode->ConvertLayoutModeToString(layoutMode);
    layoutMode = LayoutMode::AUTO;
    tabContentFrameNode->ConvertLayoutModeToString(layoutMode);

    /**
     * @tc.steps: steps3. ConvertLayoutModeToString.
     * @tc.expected: steps3. Check the result of ConvertLayoutModeToString.
     */
    EXPECT_EQ(tabContentFrameNode->ConvertLayoutModeToString(layoutMode), "LayoutMode.AUTO");
}

/**
 * @tc.name: TabsNodeToJsonValue001
 * @tc.desc: Test the ToJsonValue function in the TabsNode class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsNodeToJsonValue001, TestSize.Level2)
{
    CreateWithItem([](TabsModelNG model) {});
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    tabBarPattern_->tabBarStyle_ = TabBarStyle::BOTTOMTABBATSTYLE;
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    frameNode_->tabBarId_ = frameNode_->GetTabBarId();

    /**
     * @tc.steps: steps2. Create ScrollableBarModeOptions and assign them different values to enter different branches.
     */
    ScrollableBarModeOptions options;
    options.margin = 0.0_vp;
    options.nonScrollableLayoutStyle = LayoutStyle::ALWAYS_AVERAGE_SPLIT;
    tabBarLayoutProperty_->UpdateScrollableBarModeOptions(options);
    frameNode_->ToJsonValue(json, filter);
    options.nonScrollableLayoutStyle = LayoutStyle::SPACE_BETWEEN_OR_CENTER;
    tabBarLayoutProperty_->UpdateScrollableBarModeOptions(options);
    frameNode_->ToJsonValue(json, filter);
    options.nonScrollableLayoutStyle = LayoutStyle::ALWAYS_CENTER;
    tabBarLayoutProperty_->UpdateScrollableBarModeOptions(options);
    frameNode_->ToJsonValue(json, filter);

    /**
     * @tc.steps: steps3. ToJsonValue.
     * @tc.expected: steps3. Check the result of ToJsonValue.
     */
    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: TabsNodeGetScrollableBarModeOptions001
 * @tc.desc: Test the GetScrollableBarModeOptions function in the TabsNode class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsNodeGetScrollableBarModeOptions001, TestSize.Level2)
{
    CreateWithItem([](TabsModelNG model) {});
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
 * @tc.name: TabsLayoutAlgorithmMeasure001
 * @tc.desc: Test the Measure function in the TabsLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsLayoutAlgorithmMeasure001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });

    /**
     * @tc.steps: steps2. Test Measure by using different conditions.
     */
    auto tabsLayoutAlgorithm = pattern_->CreateLayoutAlgorithm();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    LayoutConstraintF layoutConstraintVaild;
    float layoutSize = 10000.0f;
    layoutConstraintVaild.selfIdealSize.SetSize(SizeF(layoutSize, layoutSize));
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstraintVaild);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    /**
     * @tc.steps: step3. Create a child named swiperLayoutWrapper for layoutWrapper.
     */
    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode_, geometryNode1, swiperNode_->GetLayoutProperty());
    swiperLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(swiperLayoutWrapper);

    RefPtr<Scrollable> scrollable = AceType::MakeRefPtr<Scrollable>();
    scrollable->SetAxis(Axis::HORIZONTAL);
    frameNode_->GetLayoutProperty<TabsLayoutProperty>()->UpdateTabBarPosition(BarPosition::START);
    layoutWrapper.GetGeometryNode()->SetFrameSize(SizeF(10000.0f, 10000.0f));
    tabsLayoutAlgorithm->Layout(&layoutWrapper);
    frameNode_->GetLayoutProperty<TabsLayoutProperty>()->UpdateBarOverlap(true);

    /**
     * @tc.steps: steps4. Measure.
     * @tc.expected: steps4. Check the result of BarOverlap.
     */
    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_TRUE(frameNode_->GetLayoutProperty<TabsLayoutProperty>()->GetBarOverlap().value());
    frameNode_->GetLayoutProperty<TabsLayoutProperty>()->UpdateBarOverlap(false);
    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_FALSE(frameNode_->GetLayoutProperty<TabsLayoutProperty>()->GetBarOverlap().value());
}

/**
 * @tc.name: TabBarAddChildToGroup001.
 * @tc.desc: Test the AddChildToGroup function in the TabContentNode class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, AddChildToGroup001, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            LabelStyle labelStyle;
            tabContentModel.SetLabelStyle(labelStyle);
        }, 0);
    });
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    frameNode_->AddChildToGroup(tabContentFrameNode, 1);
    frameNode_->swiperChildren_.insert(1);
    frameNode_->swiperChildren_.insert(2);
    frameNode_->AddChildToGroup(tabContentFrameNode, 1);
    auto tabBarNodeswiper =
        FrameNode::GetOrCreateFrameNode("test", 2, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    frameNode_->children_.clear();
    frameNode_->children_.push_back(tabBarNodeswiper);
    tabContentFrameNode->nodeId_ = 0;
    frameNode_->AddChildToGroup(tabContentFrameNode, 1);
    EXPECT_NE(tabBarNodeswiper, nullptr);
}

/**
 * @tc.name: OnDetachFromMainTree001.
 * @tc.desc: Test the OnDetachFromMainTree function in the TabContentNode class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, OnDetachFromMainTree001, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            LabelStyle labelStyle;
            tabContentModel.SetLabelStyle(labelStyle);
        }, 0);
    });
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabBarNodeswiper =
        FrameNode::GetOrCreateFrameNode("test", 1, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    frameNode_->children_.clear();
    frameNode_->children_.push_back(tabBarNodeswiper);

    /**
     * @tc.steps: step2. Invoke OnDetachFromMainTree.
     */
    tabContentFrameNode->OnDetachFromMainTree(true);
    EXPECT_NE(tabContentFrameNode, nullptr);
    swiperPattern_->currentIndex_ = 1;
    tabContentFrameNode->OnDetachFromMainTree(true);
    EXPECT_NE(tabContentFrameNode, nullptr);
}

/**
 * @tc.name: TabPatternOnModifyDone001.
 * @tc.desc: test OnModifyDone in TabsPattern class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabPatternOnModifyDone001, TestSize.Level1)
{
    Color color = Color::RED;
    TabsItemDivider divider;
    divider.color = color;
    CreateWithItem([divider](TabsModelNG model) {
        model.SetDivider(divider);
    });

    /**
     * @tc.steps: step3. invoke OnModifyDone and onChangeEvent_.
     * @tc.expected: step3. related function is called.
     */
    pattern_->OnModifyDone();
    pattern_->onChangeEvent_ = std::make_shared<ChangeEvent>();
    pattern_->OnModifyDone();
}

/**
 * @tc.name: SetOnIndexChangeEvent001.
 * @tc.desc: test SetOnIndexChangeEvent in TabsPattern class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, SetOnIndexChangeEvent001, TestSize.Level1)
{
    Color color = Color::RED;
    TabsItemDivider divider;
    divider.color = color;
    CreateWithItem([divider](TabsModelNG model) {
        model.SetDivider(divider);
    });

    /**
     * @tc.steps: step3. invoke OnModifyDone and onChangeEvent_.
     * @tc.expected: step3. related function is called.
     */
    pattern_->onIndexChangeEvent_ = std::make_shared<ChangeEvent>();
    pattern_->SetOnIndexChangeEvent([](const BaseEventInfo* info) {});
    pattern_->onIndexChangeEvent_ = nullptr;
    pattern_->SetOnIndexChangeEvent([](const BaseEventInfo* info) {});
    swiperPattern_->FireChangeEvent();
}

/**
* @tc.name: InitScrollable001
* @tc.desc: test AdjustFocusPosition
* @tc.type: FUNC
*/
HWTEST_F(TabsTestNg, InitScrollable001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    auto axis_test = Axis::HORIZONTAL;
    tabBarPattern_->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(axis_test);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    /**
    * @tc.steps: step2. Clear tabitemOffsets_ InitScrollable is called after data in
    * @tc.expected: TabItem Offsets_ Value is empty
    */
    tabBarPattern_->tabItemOffsets_.clear();
    tabBarPattern_->InitScrollable(gestureHub);
    tabBarPattern_->axis_ = Axis::VERTICAL;
    ASSERT_TRUE(tabBarPattern_->tabItemOffsets_.empty());
}

/**
* @tc.name: AdjustFocusPosition005
* @tc.desc: test AdjustFocusPosition
* @tc.type: FUNC
*/
HWTEST_F(TabsTestNg, AdjustFocusPosition005, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {}, BarPosition::END);
    tabBarPattern_->focusIndicator_ = -10;
    tabBarPattern_->AdjustFocusPosition();
    /**
    * @tc.steps: steps2. GetScopeFocusAlgorithm
    * @tc.expected: steps2. Check the result of GetScopeFocusAlgorithm
    */
    tabBarPattern_->AdjustFocusPosition();
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarPattern_->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    tabBarPattern_->tabItemOffsets_.clear();
    OffsetF c1(-1.0f, -1.0f);
    tabBarPattern_->tabItemOffsets_.emplace_back(c1);
    tabBarPattern_->focusIndicator_ = 0;
    tabBarPattern_->AdjustFocusPosition();
    EXPECT_EQ(tabBarPattern_->GetTabBarStyle(), TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern_->axis_ = Axis::VERTICAL;
    tabBarPattern_->focusIndicator_ = -2;
    tabBarPattern_->AdjustFocusPosition();
    EXPECT_EQ(tabBarPattern_->GetTabBarStyle(), TabBarStyle::SUBTABBATSTYLE);
}

/**
* @tc.name: DumpAdvanceInfo005
* @tc.desc: test AddTabBarItem
* @tc.type: FUNC
*/
HWTEST_F(TabsTestNg, DumpAdvanceInfo005, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});

    /**
    * @tc.steps: steps1. Set axis_ Axis: HORIZONTAL
    * @tc.expected: Calling DumpAdvanceInfo() expects HORIZONTAL
    */
    tabBarPattern_->DumpAdvanceInfo();
    ASSERT_EQ(tabBarPattern_->axis_, Axis::HORIZONTAL);
    /**
    * @tc.steps: steps1. Set axis_ Axis: VERTICAL
    * @tc.expected: Calling DumpAdvanceInfo() expects VERTICAL
        */
    tabBarPattern_->axis_ = Axis::VERTICAL;
    tabBarPattern_->DumpAdvanceInfo();
    ASSERT_EQ(tabBarPattern_->axis_, Axis::VERTICAL);
    /**
    * @tc.steps: steps1. Set axis_ Axis: FREE
    * @tc.expected: Calling DumpAdvanceInfo() expects FREE
    */
    tabBarPattern_->axis_ = Axis::FREE;
    tabBarPattern_->DumpAdvanceInfo();
    ASSERT_EQ(tabBarPattern_->axis_, Axis::FREE);
    /**
    * @tc.steps: steps1. Set axis_ Axis: NONE
    * @tc.expected: Calling DumpAdvanceInfo() expects NONE
    */
    tabBarPattern_->axis_ = Axis::NONE;
    tabBarPattern_->DumpAdvanceInfo();
    ASSERT_EQ(tabBarPattern_->axis_, Axis::NONE);
}

/**
* @tc.name: Layout001
* @tc.desc: test AddTabBarItem
* @tc.type: FUNC
*/
HWTEST_F(TabsTestNg, Layout001, TestSize.Level1)
{
    TabsItemDivider divider;
    divider.strokeWidth = 10.0_vp;
    divider.startMargin = 3.0_vp;
    divider.endMargin = 4.0_vp;
    divider.color = Color::BLACK;
    divider.isNull = false;
    CreateWithItem([=](TabsModelNG model) {
        model.SetDivider(divider);
    });
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto tabsLayoutAlgorithm = pattern_->CreateLayoutAlgorithm();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    LayoutConstraintF layoutConstrain;
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstrain);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();;
    tabsLayoutAlgorithm->Layout(&layoutWrapper);
    ASSERT_NE(&layoutWrapper, nullptr);

    /**
    * @tc.steps: step1. Calling the Layout interface.
    * @tc.expected: TestTrovoid is not equal to nullptr.
    */
    auto wrapper = static_cast<LayoutWrapper*>(&layoutWrapper);
    tabsLayoutAlgorithm->Layout(wrapper);
    ASSERT_NE(wrapper, nullptr);
}

/**
* @tc.name: ProvideRestoreInfo001
* @tc.desc: test AddTabBarItem
* @tc.type: FUNC
*/
HWTEST_F(TabsTestNg, ProvideRestoreInfo001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });
    /**
    * @tc.steps: step1. Calling the ProvideRestoreInfo interface.
    * @tc.expected: TestTrovoid is not equal to nullpyt.
    */
    string testTrovid = tabBarPattern_->ProvideRestoreInfo();
    ASSERT_TRUE(!testTrovid.empty());
}

/**
* @tc.name: SetEdgeEffect002
* @tc.desc: test SetEdgeEffect
* @tc.type: FUNC
*/
HWTEST_F(TabsTestNg, SetEdgeEffect002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });
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
    CreateWithItem([](TabsModelNG model) {}, BarPosition::END, testIndex);

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
    CreateWithItem([](TabsModelNG model) {}, BarPosition::END);
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
    CreateWithItem([=](TabsModelNG model) {
        model.SetOnAnimationStart(std::move(onAnimationStart));
        model.SetOnAnimationEnd(std::move(onAnimationEnd));
    });

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
    CreateWithItem([](TabsModelNG model) {});

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
    CreateWithItem([](TabsModelNG model) {});
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
    CreateWithItem([](TabsModelNG model) {
        model.SetIsCustomAnimation(true);
        model.SetOnCustomAnimation([](int32_t from, int32_t to) -> TabContentAnimatedTransition {
            TabContentAnimatedTransition transitionInfo;
            transitionInfo.transition = [](const RefPtr<TabContentTransitionProxy>& proxy) {};
            return transitionInfo;
        });
    }, BarPosition::START, 1);
    const std::string text_test = "text_test";

    tabBarLayoutProperty_->UpdateAxis(Axis::VERTICAL);
    EXPECT_EQ(tabBarLayoutProperty_->GetAxisValue(), Axis::VERTICAL);
    tabBarPattern_->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    tabBarPattern_->tabItemOffsets_ = { { 0.0f, 0.0f }, { 10.0f, 10.0f } };
    swiperLayoutProperty_->UpdateIndex(INDEX_ONE);
    GestureEvent info;
    Offset offset(1, 1);
    info.SetLocalLocation(offset);
    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern_->HandleClick(info);
    EXPECT_TRUE(swiperPattern_->IsDisableSwipe());
    EXPECT_FALSE(swiperPattern_->customAnimationToIndex_.has_value());

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
    Create([](TabsModelNG model) {
        model.SetIsCustomAnimation(false);
        for (int32_t index = 0; index < 3; index++) {
            TabContentModelNG tabContentModel;
            tabContentModel.Create();
            ViewStackProcessor::GetInstance()->Pop();
        }
    });
    EXPECT_FALSE(swiperPattern_->IsDisableSwipe());
}

/**
 * @tc.name: SetCustomStyleNodeTest001
 * @tc.desc: test the node can be saved in the pattern
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, SetCustomStyleNodeTest001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    Create([=](TabsModelNG model) {
        CreateSingleItem([=](TabContentModelNG tabContentModel) {
            tabContentModel.SetCustomStyleNode(frameNode);
        }, 0);
    });
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_TRUE(tabContentPattern->HasSubTabBarStyleNode());
}
} // namespace OHOS::Ace::NG
