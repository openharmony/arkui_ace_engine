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
        model.SetTabBar("", "", std::move(tabBarItemFunc), true);
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
    model.SetTabBar("", "", std::move(tabBarItemFunc), true);
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
    model.SetTabBar("", "", nullptr, true);
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
 * @tc.name: TabsModelSetFadingEdge001
 * @tc.desc: test SetFadingEdge
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelSetFadingEdge001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        model.SetFadingEdge(true);
    });
    EXPECT_EQ(frameNode_->GetTag(), V2::TABS_ETS_TAG);
    EXPECT_EQ(tabBarNode_->GetTag(), V2::TAB_BAR_ETS_TAG);
    EXPECT_TRUE(tabBarPaintProperty_->GetFadingEdgeValue());

    auto json = JsonUtil::Create(true);
    frameNode_->ToJsonValue(json);
    EXPECT_EQ(json->GetString("fadingEdge"), "true");
}

/**
 * @tc.name: TabsModelOnUpdateShowDivider001
 * @tc.desc: Test tabs OnUpdateShowDivider.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelOnUpdateShowDivider001, TestSize.Level1)
{
    Color color = Color::RED;
    TabsItemDivider divider;
    divider.color = color;
    CreateWithItem([divider](TabsModelNG model) { model.SetDivider(divider); });

    pattern_->OnUpdateShowDivider();
    auto dividerColor = dividerRenderProperty_->GetDividerColor();
    EXPECT_EQ(dividerColor.value().ColorToString(), color.ColorToString());
}

/**
 * @tc.name: TabsModelOnUpdateShowDivider002
 * @tc.desc: Test tabs OnUpdateShowDivider when pattern_ without host
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelOnUpdateShowDivider002, TestSize.Level2)
{
    auto pattern = AceType::MakeRefPtr<TabsPattern>();
    pattern->OnUpdateShowDivider();
    EXPECT_EQ(pattern->GetHostFrameSize(), std::nullopt);
}

/**
 * @tc.name: TabsModelOnUpdateShowDivider003
 * @tc.desc: Test tabs OnUpdateShowDivider when pattern_ without host
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelOnUpdateShowDivider003, TestSize.Level2)
{
    CreateWithItem([](TabsModelNG model) {});
    pattern_->OnUpdateShowDivider();
    EXPECT_EQ(frameNode_->GetTotalChildCount(), 3);
}

/**
 * @tc.name: TabsModelOnUpdateShowDivider004
 * @tc.desc: Test tabs OnUpdateShowDivider when pattern_ without host
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelOnUpdateShowDivider004, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    pattern_->OnUpdateShowDivider();
    auto childNode = frameNode_->GetChildAtIndex(1);
    EXPECT_EQ(childNode->GetTag(), V2::DIVIDER_ETS_TAG);
}

/**
 * @tc.name: TabsModelToJsonValue001
 * @tc.desc: Test tabs ToJsonValue when host has not child.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelToJsonValue001, TestSize.Level2)
{
    CreateWithItem([](TabsModelNG model) {});
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    frameNode_->ToJsonValue(json);
    auto dividerJson = json->GetValue("divider");
    EXPECT_TRUE(dividerJson->IsNull());
}

/**
 * @tc.name: TabContentModelSetIndicator001
 * @tc.desc: test SetIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelSetIndicator001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    IndicatorStyle indicator;
    indicator.color = Color::BLACK;
    indicator.height = 10.0_vp;
    indicator.width = 20.0_vp;
    indicator.borderRadius = 2.0_vp;
    indicator.marginTop = 3.0_vp;
    tabContentPattern->SetIndicatorStyle(indicator);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(tabContentPattern->GetIndicatorStyle().color, Color::BLACK);
    EXPECT_EQ(tabContentPattern->GetIndicatorStyle().height, 10.0_vp);
    EXPECT_EQ(tabContentPattern->GetIndicatorStyle().width, 20.0_vp);
    EXPECT_EQ(tabContentPattern->GetIndicatorStyle().borderRadius, 2.0_vp);
    EXPECT_EQ(tabContentPattern->GetIndicatorStyle().marginTop, 3.0_vp);
}

/**
 * @tc.name: TabContentModelSetIndicator002
 * @tc.desc: test SetIndicator with getTheme once
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelSetIndicator002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    tabContentPattern->SetIndicatorStyle(IndicatorStyle());
    EXPECT_EQ(tabContentPattern->GetIndicatorStyle().width, 0.0_vp);
    EXPECT_EQ(tabContentPattern->GetIndicatorStyle().borderRadius, 0.0_vp);
}

/**
 * @tc.name: TabContentModelCreate(std::function<void()>&& deepRenderFunc)
 * @tc.desc: Test Create(std::function<void()>&& deepRenderFunc)
 * @tc.type：FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelCreate001, TestSize.Level1)
{
    TabContentModelNG tabContentModel;
    tabContentModel.Create([]() {});
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
}

/**
 * @tc.name: TabContentModelSetSubTabBorderRadius001
 * @tc.desc: test SetSubTabBorderRadius
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelSetSubTabBorderRadius001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    BoardStyle boardStyle;
    boardStyle.borderRadius = 10.0_vp;
    tabContentPattern->SetBoardStyle(boardStyle);
    auto board = tabContentPattern->GetBoardStyle();
    EXPECT_EQ(board.borderRadius, boardStyle.borderRadius);
}

/**
 * @tc.name: TabContentModelSetSubTabBorderRadius002
 * @tc.desc: test SetSubTabBorderRadius with getTheme once
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelSetSubTabBorderRadius002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    BoardStyle boardStyle;
    boardStyle.borderRadius = 10.0_vp;
    tabContentPattern->SetBoardStyle(boardStyle);
    auto board = tabContentPattern->GetBoardStyle();
    EXPECT_EQ(board.borderRadius, boardStyle.borderRadius);
}

/**
 * @tc.name: TabContentModelSetSelectedMode001
 * @tc.desc: test SetSelectedMode
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelSetSelectedMode001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    EXPECT_EQ(tabContentPattern->GetSelectedMode(), SelectedMode::INDICATOR);
}

/**
 * @tc.name: TabContentModelSetLabelStyle001
 * @tc.desc: test SetLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelSetLabelStyle001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    LabelStyle labelStyle;
    tabContentPattern->SetLabelStyle(labelStyle);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().textOverflow, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().maxLines, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().minFontSize, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().maxFontSize, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().heightAdaptivePolicy, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().fontSize, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().fontWeight, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().fontFamily, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().fontStyle, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().unselectedColor, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().selectedColor, std::nullopt);
}

/**
 * @tc.name: TabContentModelSetLabelStyle002
 * @tc.desc: test SetLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelSetLabelStyle002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    LabelStyle labelStyle;
    labelStyle.textOverflow = TextOverflow::CLIP;
    labelStyle.maxLines = 0;
    labelStyle.minFontSize = 0.0_vp;
    labelStyle.maxFontSize = 0.0_vp;
    labelStyle.heightAdaptivePolicy = TextHeightAdaptivePolicy::MAX_LINES_FIRST;
    labelStyle.fontSize = 0.0_vp;
    labelStyle.fontWeight = FontWeight::NORMAL;
    labelStyle.fontFamily = { "unknown" };
    std::vector<std::string> fontVect = { "" };
    labelStyle.fontStyle = Ace::FontStyle::NORMAL;
    labelStyle.unselectedColor = Color::WHITE;
    labelStyle.selectedColor = Color::WHITE;
    tabContentPattern->SetLabelStyle(labelStyle);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().textOverflow, labelStyle.textOverflow);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().maxLines, labelStyle.maxLines);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().minFontSize->ToString(), labelStyle.minFontSize->ToString());
    EXPECT_EQ(tabContentPattern->GetLabelStyle().maxFontSize->ToString(), labelStyle.maxFontSize->ToString());
    EXPECT_EQ(tabContentPattern->GetLabelStyle().heightAdaptivePolicy, labelStyle.heightAdaptivePolicy);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().fontSize->ToString(), labelStyle.fontSize->ToString());
    EXPECT_EQ(tabContentPattern->GetLabelStyle().fontWeight, labelStyle.fontWeight);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().fontFamily, labelStyle.fontFamily);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().fontStyle, labelStyle.fontStyle);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().unselectedColor, labelStyle.unselectedColor);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().selectedColor, labelStyle.selectedColor);
}

/**
 * @tc.name: TabContentModelSetIconStyle001
 * @tc.desc: test SetIconStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelSetIconStyle001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    IconStyle iconStyle;
    tabContentPattern->SetIconStyle(iconStyle);
    EXPECT_EQ(tabContentPattern->GetIconStyle().unselectedColor, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetIconStyle().selectedColor, std::nullopt);
}

/**
 * @tc.name: TabContentModelSetIconStyle002
 * @tc.desc: test SetIconStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelSetIconStyle002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    IconStyle iconStyle;
    iconStyle.unselectedColor = Color::WHITE;
    iconStyle.selectedColor = Color::WHITE;
    tabContentPattern->SetIconStyle(iconStyle);
    EXPECT_EQ(tabContentPattern->GetIconStyle().unselectedColor, iconStyle.unselectedColor);
    EXPECT_EQ(tabContentPattern->GetIconStyle().selectedColor, iconStyle.selectedColor);
}

/**
 * @tc.name: TabContentModelUpdateLabelStyle001
 * @tc.desc: test UpdateLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelUpdateLabelStyle001, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    LabelStyle labelStyle;
    labelStyle.textOverflow = TextOverflow::CLIP;
    labelStyle.maxLines = 0;
    labelStyle.minFontSize = 0.0_vp;
    labelStyle.maxFontSize = 0.0_vp;
    labelStyle.heightAdaptivePolicy = TextHeightAdaptivePolicy::MAX_LINES_FIRST;
    labelStyle.fontSize = 0.0_vp;
    labelStyle.fontWeight = FontWeight::NORMAL;
    labelStyle.fontFamily = { "unknown" };
    std::vector<std::string> fontVect = { "" };
    labelStyle.fontStyle = Ace::FontStyle::NORMAL;
    Create([=](TabsModelNG model) {
        CreateSingleItem([=](TabContentModelNG tabContentModel) {
            tabContentModel.UpdateLabelStyle(labelStyle, layoutProperty);
        }, 0);
    });
    EXPECT_EQ(layoutProperty->GetTextOverflow(), labelStyle.textOverflow);
    EXPECT_EQ(layoutProperty->GetMaxLines(), labelStyle.maxLines);
    EXPECT_EQ(layoutProperty->GetAdaptMinFontSize(), labelStyle.minFontSize);
    EXPECT_EQ(layoutProperty->GetAdaptMaxFontSize(), labelStyle.maxFontSize);
    EXPECT_EQ(layoutProperty->GetHeightAdaptivePolicy(), labelStyle.heightAdaptivePolicy);
    EXPECT_EQ(layoutProperty->GetFontSize(), labelStyle.fontSize);
    EXPECT_EQ(layoutProperty->GetFontWeight(), labelStyle.fontWeight);
    EXPECT_EQ(layoutProperty->GetFontFamily(), labelStyle.fontFamily);
    EXPECT_EQ(layoutProperty->GetItalicFontStyle(), labelStyle.fontStyle);
}

/**
 * @tc.name: TabContentModelUpdateLabelStyle002
 * @tc.desc: test UpdateLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelUpdateLabelStyle002, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    LabelStyle labelStyle;
    Create([=](TabsModelNG model) {
        CreateSingleItem([=](TabContentModelNG tabContentModel) {
            tabContentModel.UpdateLabelStyle(labelStyle, layoutProperty);
        }, 0);
    });
    EXPECT_FALSE(layoutProperty->GetTextOverflow().has_value());
    EXPECT_FALSE(layoutProperty->GetMaxLines().has_value());
    EXPECT_FALSE(layoutProperty->GetAdaptMinFontSize().has_value());
    EXPECT_FALSE(layoutProperty->GetAdaptMaxFontSize().has_value());
    EXPECT_FALSE(layoutProperty->GetHeightAdaptivePolicy().has_value());
    EXPECT_FALSE(layoutProperty->GetFontSize().has_value());
    EXPECT_FALSE(layoutProperty->GetFontWeight().has_value());
    EXPECT_FALSE(layoutProperty->GetFontFamily().has_value());
    EXPECT_FALSE(layoutProperty->GetItalicFontStyle().has_value());
}

/**
 * @tc.name: TabContentModelToJsonValue001
 * @tc.desc: test SetIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelToJsonValue001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    LabelStyle labelStyle;
    labelStyle.textOverflow = TextOverflow::CLIP;
    labelStyle.maxLines = 0;
    labelStyle.minFontSize = 0.0_vp;
    labelStyle.maxFontSize = 0.0_vp;
    labelStyle.heightAdaptivePolicy = TextHeightAdaptivePolicy::MAX_LINES_FIRST;
    labelStyle.fontSize = 0.0_vp;
    labelStyle.fontWeight = FontWeight::NORMAL;
    labelStyle.fontFamily = { "unknown", "unknow2" };
    tabContentPattern->SetLabelStyle(labelStyle);
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    tabContentFrameNode->ToJsonValue(json);
    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: TabContentModelAddTabBarItem001
 * @tc.desc: test AddTabBarItem
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelAddTabBarItem001, TestSize.Level1)
{
    const std::string text_test = "text_test";
    TabContentModelNG tabContentModel;
    tabContentModel.Create();
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    tabContentFrameNode->GetTabBarItemId();
    tabContentFrameNode->MountToParent(swiperNode_);
    tabContentPattern->SetTabBar(text_test, "", nullptr);
    EXPECT_EQ(tabContentPattern->GetTabBarParam().GetText(), text_test);
    tabContentModel.AddTabBarItem(tabContentFrameNode, DEFAULT_NODE_SLOT, true);

    TabContentModelNG tabContentModel2;
    tabContentModel2.Create();
    auto tabContentFrameNode2 = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    auto tabContentPattern2 = tabContentFrameNode2->GetPattern<TabContentPattern>();
    tabContentFrameNode2->MountToParent(swiperNode_);
    tabContentPattern2->SetTabBar(text_test, "", nullptr);
    EXPECT_EQ(tabContentPattern2->GetTabBarParam().GetText(), text_test);
    tabContentModel.AddTabBarItem(tabContentFrameNode2, DEFAULT_NODE_SLOT, true);
}

/**
 * @tc.name: TabBarPatternOnDirtyLayoutWrapperSwap001
 * @tc.desc: test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternOnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        model.SetFadingEdge(true);
    });
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);
    DirtySwapConfig config;
    tabBarPattern_->OnDirtyLayoutWrapperSwap(frameNode_, config);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
    /**
     * @tc.steps: step2. creat different conditions and invoke OnDirtyLayoutWrapperSwap.
     * @tc.expected: step2. expect The function is run ok.
     */
    config.skipMeasure = true;
    EXPECT_FALSE(tabBarPattern_->OnDirtyLayoutWrapperSwap(frameNode_, config));

    config.skipLayout = true;
    EXPECT_FALSE(tabBarPattern_->OnDirtyLayoutWrapperSwap(frameNode_, config));

    config.skipMeasure = false;
    EXPECT_FALSE(tabBarPattern_->OnDirtyLayoutWrapperSwap(frameNode_, config));

    tabBarPattern_->isAnimating_ = true;
    EXPECT_FALSE(tabBarPattern_->OnDirtyLayoutWrapperSwap(frameNode_, config));
    EXPECT_EQ(tabBarPattern_->isAnimating_, true);
}

/**
 * @tc.name: TabBarPatternUpdateSubTabBoard001
 * @tc.desc: test UpdateSubTabBoard
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternUpdateSubTabBoard001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    tabBarPattern_->UpdateSubTabBoard();
    EXPECT_EQ(swiperNode_->GetTag(), V2::SWIPER_ETS_TAG);
    tabBarPattern_->UpdateSubTabBoard();

    EXPECT_EQ(tabBarPattern_->selectedModes_[0], SelectedMode::INDICATOR);
    tabBarPattern_->SetSelectedMode(SelectedMode::BOARD, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], SelectedMode::BOARD);
    tabBarPattern_->UpdateSubTabBoard();
    EXPECT_EQ(tabBarPattern_->indicator_, 0);

    tabBarPattern_->indicator_ = 1;
    tabBarPattern_->UpdateSubTabBoard();
    EXPECT_EQ(tabBarPattern_->indicator_, 1);

    IndicatorStyle style;
    tabBarPattern_->SetIndicatorStyle(style, 1);
    tabBarPattern_->UpdateSubTabBoard();
    EXPECT_EQ(tabBarPattern_->indicator_, 1);

    tabBarLayoutProperty_->UpdateAxis(Axis::VERTICAL);
    tabBarPattern_->UpdateSubTabBoard();
    EXPECT_EQ(tabBarPattern_->indicator_, 1);

    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern_->UpdateSubTabBoard();
    EXPECT_EQ(tabBarPattern_->indicator_, 1);

    tabBarPattern_->indicator_ = 0;
    tabBarPattern_->tabBarStyles_[0] = TabBarStyle::SUBTABBATSTYLE;
    tabBarPattern_->selectedModes_[0] = SelectedMode::BOARD;
    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern_->UpdateSubTabBoard();
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
}

/**
 * @tc.name: TabBarPatternUpdateGradientRegions001
 * @tc.desc: test UpdateGradientRegions
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternUpdateGradientRegions001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        model.SetTabBarMode(TabBarMode::SCROLLABLE);
    });
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    tabBarLayoutProperty_->UpdateAxis(Axis::VERTICAL);
    EXPECT_EQ(tabBarLayoutProperty_->GetAxisValue(), Axis::VERTICAL);

    tabBarPattern_->tabItemOffsets_ = { { -1.0f, -1.0f } };
    tabBarPattern_->childrenMainSize_ = 10.0f;
    tabBarPattern_->UpdateGradientRegions();
    EXPECT_TRUE(tabBarPattern_->gradientRegions_[2]);

    tabBarPattern_->tabItemOffsets_ = { { 1.0f, 1.0f } };
    tabBarPattern_->childrenMainSize_ = 10.0f;
    tabBarPattern_->UpdateGradientRegions();
    EXPECT_FALSE(tabBarPattern_->gradientRegions_[2]);

    tabBarPattern_->tabItemOffsets_ = { { 10.0f, 10.0f } };
    tabBarPattern_->childrenMainSize_ = 10.0f;
    tabBarPattern_->UpdateGradientRegions();
    EXPECT_FALSE(tabBarPattern_->gradientRegions_[3]);

    tabBarPattern_->tabItemOffsets_ = { { -10.0f, -10.0f } };
    tabBarPattern_->childrenMainSize_ = 5.0f;
    tabBarPattern_->UpdateGradientRegions();
    EXPECT_FALSE(tabBarPattern_->gradientRegions_[3]);

    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    EXPECT_EQ(tabBarLayoutProperty_->GetAxisValue(), Axis::HORIZONTAL);

    tabBarPattern_->tabItemOffsets_ = { { -1.0f, -1.0f } };
    tabBarPattern_->childrenMainSize_ = 10.0f;
    tabBarPattern_->UpdateGradientRegions();
    EXPECT_TRUE(tabBarPattern_->gradientRegions_[0]);

    tabBarPattern_->tabItemOffsets_ = { { 1.0f, 1.0f } };
    tabBarPattern_->childrenMainSize_ = 10.0f;
    tabBarPattern_->UpdateGradientRegions();
    EXPECT_FALSE(tabBarPattern_->gradientRegions_[0]);

    tabBarPattern_->tabItemOffsets_ = { { 10.0f, 10.0f } };
    tabBarPattern_->childrenMainSize_ = 10.0f;
    tabBarPattern_->UpdateGradientRegions();
    EXPECT_FALSE(tabBarPattern_->gradientRegions_[1]);

    tabBarPattern_->tabItemOffsets_ = { { -10.0f, -10.0f } };
    tabBarPattern_->childrenMainSize_ = 5.0f;
    tabBarPattern_->UpdateGradientRegions();
    EXPECT_FALSE(tabBarPattern_->gradientRegions_[1]);
}

/**
 * @tc.name: TabBarPatternSetSelectedMode001
 * @tc.desc: test SetSelectedMode
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternSetSelectedMode001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        model.SetFadingEdge(true);
    });
    EXPECT_EQ(tabBarPattern_->GetSelectedMode(), SelectedMode::INDICATOR);

    tabBarPattern_->SetSelectedMode(SelectedMode::INDICATOR, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], SelectedMode::INDICATOR);
    tabBarPattern_->SetSelectedMode(SelectedMode::INDICATOR, 1);
    EXPECT_EQ(tabBarPattern_->selectedModes_[1], SelectedMode::INDICATOR);
    tabBarPattern_->SetSelectedMode(SelectedMode::INDICATOR, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], SelectedMode::INDICATOR);

    IndicatorStyle indicator;
    tabBarPattern_->SetIndicatorStyle(indicator, 0);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[0], indicator);
    tabBarPattern_->SetIndicatorStyle(indicator, 1);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[1], indicator);
    tabBarPattern_->SetIndicatorStyle(indicator, 0);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[0], indicator);

    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_[1], TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);
}

/**
 * @tc.name: TabBarPatternUpdateIndicator001
 * @tc.desc: test UpdateIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternUpdateIndicator001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        model.SetFadingEdge(true);
    });

    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_[0], TabBarStyle::BOTTOMTABBATSTYLE);
    tabBarPattern_->UpdateIndicator(0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern_->UpdateIndicator(0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::NOSTYLE, 0);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_[0], TabBarStyle::NOSTYLE);
    tabBarPattern_->UpdateIndicator(0);

    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_[0], TabBarStyle::BOTTOMTABBATSTYLE);

    tabBarLayoutProperty_->UpdateAxis(Axis::VERTICAL);
    EXPECT_EQ(tabBarLayoutProperty_->GetAxisValue(), Axis::VERTICAL);
    tabBarPattern_->tabBarType_[0] = true;
    tabBarPattern_->UpdateIndicator(0);

    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);

    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    EXPECT_EQ(tabBarLayoutProperty_->GetAxisValue(), Axis::HORIZONTAL);
    tabBarPattern_->tabBarType_[0] = false;
    tabBarPattern_->UpdateIndicator(0);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);

    tabBarPattern_->indicator_ = 1;
    tabBarPattern_->UpdateIndicator(0);
    EXPECT_EQ(tabBarPattern_->indicator_, 1);
}

/**
 * @tc.name: TabBarPatternPlayPressAnimation001
 * @tc.desc: test PlayPressAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternPlayPressAnimation001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        model.SetFadingEdge(true);
    });

    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    IndicatorStyle indicatorStyle;
    tabBarPattern_->SetIndicatorStyle(indicatorStyle, 0);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern_->SetSelectedMode(SelectedMode::BOARD, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], SelectedMode::BOARD);
    tabBarPattern_->PlayPressAnimation(0, Color::BLACK, AnimationType::PRESS);

    tabBarPattern_->SetSelectedMode(SelectedMode::INDICATOR, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], SelectedMode::INDICATOR);
    tabBarPattern_->PlayPressAnimation(0, Color::BLACK, AnimationType::PRESS);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);

    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern_->SetSelectedMode(SelectedMode::BOARD, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], SelectedMode::BOARD);
    tabBarPattern_->PlayPressAnimation(0, Color::TRANSPARENT, AnimationType::PRESS);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);

    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern_->SetSelectedMode(SelectedMode::BOARD, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], SelectedMode::BOARD);
    tabBarPattern_->PlayPressAnimation(0, Color::BLACK, AnimationType::PRESS);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);

    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern_->SetSelectedMode(SelectedMode::INDICATOR, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], SelectedMode::INDICATOR);
    tabBarPattern_->PlayPressAnimation(0, Color::TRANSPARENT, AnimationType::PRESS);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);

    tabBarLayoutProperty_->UpdateAxis(Axis::VERTICAL);
    tabBarPattern_->SetSelectedMode(SelectedMode::BOARD, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], SelectedMode::BOARD);
    tabBarPattern_->PlayPressAnimation(0, Color::TRANSPARENT, AnimationType::PRESS);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
}

/**
 * @tc.name: TabContentModel001
 * @tc.desc: test TabsModel
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModel001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. SetTabBar without builder
     * @tc.expected: tabbarnode has default textNode and imageNode
     */
    Create([](TabsModelNG model) {
        auto tabFrameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
        auto weakTab = AceType::WeakClaim(AceType::RawPtr(tabFrameNode));
        TabContentModelNG tabContentModel;
        tabContentModel.Create();
        tabContentModel.SetTabBar("", "", nullptr, true); // SetTabBar without builder
        ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
        ViewAbstract::SetHeight(CalcLength(FILL_LENGTH));
        auto tabContentFrameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
        auto tabContentNode = AceType::DynamicCast<TabContentNode>(tabContentFrameNode);
        tabContentNode->UpdateRecycleElmtId(0); // for AddChildToGroup
        tabContentNode->GetTabBarItemId();           // for AddTabBarItem
        tabContentNode->SetParent(weakTab);          // for AddTabBarItem
        tabContentModel.Pop();
    });
    auto colNode = GetChildFrameNode(tabBarNode_, 0);
    EXPECT_EQ(colNode->GetTag(), V2::COLUMN_ETS_TAG);
    EXPECT_EQ(colNode->GetTotalChildCount(), 1);

    auto imageNode = GetChildFrameNode(colNode, 0);
    EXPECT_EQ(imageNode->GetTag(), V2::IMAGE_ETS_TAG);
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
    EXPECT_EQ(tabBarPattern_->windowSizeChangeReason_, WindowSizeChangeReason::ROTATION);
}

/**
 * @tc.name: TabBarPatternGetIndicatorRect001
 * @tc.desc: test GetIndicatorRect
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternGetIndicatorRect001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto rect = tabBarLayoutProperty_->GetIndicatorRect(0);
    EXPECT_EQ(rect.GetX(), 85.f);
}

/**
 * @tc.name: TabBarPatternGetSelectedMode001
 * @tc.desc: test GetSelectedMode
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternGetSelectedMode001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    tabBarPattern_->indicator_ = 1;
    auto mode = tabBarPattern_->GetSelectedMode();
    EXPECT_EQ(mode, SelectedMode::INDICATOR);
}

/**
 * @tc.name: TabBarModifierSetIndicator001
 * @tc.desc: test SetIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarModifierSetIndicator001, TestSize.Level1)
{
    RectF rect(0.0f, 0.0f, 1.0f, 1.0f);
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    tabBarModifier->SetIndicator(rect);
    EXPECT_EQ(tabBarModifier->indicatorLeft_->Get(), 0.0f);
    EXPECT_EQ(tabBarModifier->indicatorTop_->Get(), 0.0f);
    tabBarModifier->indicatorLeft_ = nullptr;
    tabBarModifier->indicatorTop_ = nullptr;
    tabBarModifier->SetIndicator(rect);
    EXPECT_EQ(tabBarModifier->indicatorLeft_, nullptr);
    EXPECT_EQ(tabBarModifier->indicatorTop_, nullptr);
}

/**
 * @tc.name: TabBarModifierSetIndicatorColor001
 * @tc.desc: test SetIndicatorColor
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarModifierSetIndicatorColor001, TestSize.Level1)
{
    LinearColor indicatorColor(Color::BLACK);
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    tabBarModifier->SetIndicatorColor(indicatorColor);
    EXPECT_TRUE(tabBarModifier->indicatorColor_->Get() == indicatorColor);
    tabBarModifier->indicatorColor_ = nullptr;
    tabBarModifier->SetIndicatorColor(indicatorColor);
    EXPECT_EQ(tabBarModifier->indicatorColor_, nullptr);
}

/**
 * @tc.name: TabBarModifierSetIndicatorWidth001
 * @tc.desc: test SetIndicatorWidth
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarModifierSetIndicatorWidth001, TestSize.Level1)
{
    float indicatorWidth = 1.0f;
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    tabBarModifier->SetIndicatorWidth(indicatorWidth);
    EXPECT_EQ(tabBarModifier->indicatorWidth_->Get(), indicatorWidth);
    tabBarModifier->indicatorWidth_ = nullptr;
    tabBarModifier->SetIndicatorWidth(indicatorWidth);
    EXPECT_EQ(tabBarModifier->indicatorWidth_, nullptr);
}

/**
 * @tc.name: TabBarModifierSetIndicatorHeight001
 * @tc.desc: test SetIndicatorHeight
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarModifierSetIndicatorHeight001, TestSize.Level1)
{
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    float indicatorHeight = 1.0f;
    tabBarModifier->SetIndicatorHeight(indicatorHeight);
    EXPECT_EQ(tabBarModifier->indicatorHeight_->Get(), indicatorHeight);
    tabBarModifier->indicatorHeight_ = nullptr;
    tabBarModifier->SetIndicatorHeight(indicatorHeight);
    EXPECT_EQ(tabBarModifier->indicatorHeight_, nullptr);
}

/**
 * @tc.name: TabBarModifierSetIndicatorBorderRadius001
 * @tc.desc: test SetIndicatorBorderRadius
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarModifierSetIndicatorBorderRadius001, TestSize.Level1)
{
    float indicatorBorderRadius = 1.0f;
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    tabBarModifier->SetIndicatorBorderRadius(indicatorBorderRadius);
    EXPECT_EQ(tabBarModifier->indicatorBorderRadius_->Get(), indicatorBorderRadius);
    tabBarModifier->indicatorBorderRadius_ = nullptr;
    tabBarModifier->SetIndicatorBorderRadius(indicatorBorderRadius);
    EXPECT_EQ(tabBarModifier->indicatorBorderRadius_, nullptr);
}

/**
 * @tc.name: TabBarModifierSetIndicatorMarginTop001
 * @tc.desc: test SetIndicatorMarginTop
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarModifierSetIndicatorMarginTop001, TestSize.Level1)
{
    float indicatorMarginTop = 1.0f;
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    tabBarModifier->SetIndicatorMarginTop(indicatorMarginTop);
    EXPECT_EQ(tabBarModifier->indicatorMarginTop_->Get(), indicatorMarginTop);
    tabBarModifier->indicatorMarginTop_ = nullptr;
    tabBarModifier->SetIndicatorMarginTop(indicatorMarginTop);
    EXPECT_EQ(tabBarModifier->indicatorMarginTop_, nullptr);
}

/**
 * @tc.name: TabBarModifierSetSelectedMode001
 * @tc.desc: test SetSelectedMode
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarModifierSetSelectedMode001, TestSize.Level1)
{
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    ASSERT_NE(tabBarModifier->hasIndicator_, nullptr);
    EXPECT_TRUE(tabBarModifier->hasIndicator_->Get());
    tabBarModifier->hasIndicator_ = nullptr;
    tabBarModifier->SetSelectedMode(SelectedMode::INDICATOR);
    EXPECT_EQ(tabBarModifier->hasIndicator_, nullptr);
}

/**
 * @tc.name: TabBarModifierOnDraw001
 * @tc.desc: test onDraw
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarModifierOnDraw001, TestSize.Level1)
{
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();

    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRect(_)).Times(AnyNumber());
    EXPECT_CALL(rsCanvas, DrawRoundRect(_)).Times(AnyNumber());
    EXPECT_CALL(rsCanvas, Restore()).Times(AnyNumber());

    DrawingContext context { rsCanvas, 10.0f, 10.0f };
    float indicatorHeight = 1.0f;
    float indicatorWidth = 1.0f;
    float indicatorMarginTop = 1.0f;
    float indicatorBorderRadius = 1.0f;

    tabBarModifier->SetSelectedMode(SelectedMode::INDICATOR);
    tabBarModifier->SetIndicatorHeight(indicatorHeight);
    tabBarModifier->SetIndicatorWidth(indicatorWidth);
    tabBarModifier->SetIndicatorMarginTop(indicatorMarginTop);
    tabBarModifier->SetIndicatorBorderRadius(indicatorBorderRadius);
    tabBarModifier->onDraw(context);

    EXPECT_TRUE(tabBarModifier->hasIndicator_->Get());
    EXPECT_EQ(tabBarModifier->indicatorHeight_->Get(), indicatorHeight);
    EXPECT_EQ(tabBarModifier->indicatorWidth_->Get(), indicatorWidth);
    EXPECT_EQ(tabBarModifier->indicatorMarginTop_->Get(), indicatorMarginTop);
    EXPECT_EQ(tabBarModifier->indicatorBorderRadius_->Get(), indicatorBorderRadius);

    indicatorHeight = -1.0f;
    indicatorWidth = -1.0f;
    indicatorMarginTop = -1.0f;
    indicatorBorderRadius = -1.0f;

    tabBarModifier->SetSelectedMode(SelectedMode::INDICATOR);
    tabBarModifier->SetIndicatorHeight(indicatorHeight);
    tabBarModifier->SetIndicatorWidth(indicatorWidth);
    tabBarModifier->SetIndicatorMarginTop(indicatorMarginTop);
    tabBarModifier->SetIndicatorBorderRadius(indicatorBorderRadius);
    tabBarModifier->onDraw(context);

    EXPECT_TRUE(tabBarModifier->hasIndicator_->Get());
    EXPECT_EQ(tabBarModifier->indicatorHeight_->Get(), indicatorHeight);
    EXPECT_EQ(tabBarModifier->indicatorWidth_->Get(), indicatorWidth);
    EXPECT_EQ(tabBarModifier->indicatorMarginTop_->Get(), indicatorMarginTop);
    EXPECT_EQ(tabBarModifier->indicatorBorderRadius_->Get(), indicatorBorderRadius);

    tabBarModifier->SetSelectedMode(SelectedMode::BOARD);
    tabBarModifier->onDraw(context);
    EXPECT_FALSE(tabBarModifier->hasIndicator_->Get());

    tabBarModifier->hasIndicator_ = nullptr;
    tabBarModifier->onDraw(context);
    EXPECT_EQ(tabBarModifier->hasIndicator_, nullptr);
}

/**
 * @tc.name: TabBarPaintMethodGetForegroundDrawFunction001
 * @tc.desc: test GetForegroundDrawFunction
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPaintMethodGetForegroundDrawFunction001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    IndicatorStyle indicator;
    tabBarPattern_->SetIndicatorStyle(indicator, 0);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[0], indicator);
    SelectedMode selectedMode = SelectedMode::INDICATOR;
    tabBarPattern_->SetSelectedMode(selectedMode, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], selectedMode);

    auto paintMethod = tabBarPattern_->CreateNodePaintMethod();
    PaintWrapper paintWrapper(tabBarNode_->GetRenderContext(), tabBarNode_->GetGeometryNode(), tabBarPaintProperty_);
    auto drawFunction = paintMethod->GetForegroundDrawFunction(&paintWrapper);

    tabBarPaintProperty_->UpdateFadingEdge(false);
    EXPECT_FALSE(tabBarPaintProperty_->GetFadingEdgeValue());
    PaintWrapper paintWrapper2(tabBarNode_->GetRenderContext(), tabBarNode_->GetGeometryNode(), tabBarPaintProperty_);
    drawFunction = paintMethod->GetForegroundDrawFunction(&paintWrapper2);
    ASSERT_EQ(drawFunction, nullptr);
    auto clone = tabBarPaintProperty_->Clone();
    EXPECT_NE(clone, nullptr);
}

/**
 * @tc.name: TabBarPaintMethodGetContentModifier001
 * @tc.desc: test GetContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPaintMethodGetContentModifier001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    IndicatorStyle indicator;
    tabBarPattern_->SetIndicatorStyle(indicator, 0);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[0], indicator);
    SelectedMode selectedMode = SelectedMode::INDICATOR;
    tabBarPattern_->SetSelectedMode(selectedMode, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], selectedMode);
    auto paintMethod = tabBarPattern_->CreateNodePaintMethod();

    tabBarPattern_->indicator_ = 1;
    tabBarPattern_->CreateNodePaintMethod();

    IndicatorStyle style;
    tabBarPattern_->SetIndicatorStyle(style, 1);
    tabBarPattern_->CreateNodePaintMethod();

    PaintWrapper paintWrapper(tabBarNode_->GetRenderContext(), tabBarNode_->GetGeometryNode(), tabBarPaintProperty_);
    auto contentModifier = paintMethod->GetContentModifier(&paintWrapper);
    EXPECT_NE(contentModifier, nullptr);
}

/**
 * @tc.name: TabBarPaintMethodUpdateContentModifier001
 * @tc.desc: test UpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPaintMethodUpdateContentModifier001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    IndicatorStyle indicator;
    tabBarPattern_->SetIndicatorStyle(indicator, 0);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[0], indicator);
    SelectedMode selectedMode = SelectedMode::INDICATOR;
    tabBarPattern_->SetSelectedMode(selectedMode, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], selectedMode);

    auto paintMethod = tabBarPattern_->CreateNodePaintMethod();
    PaintWrapper paintWrapper(tabBarNode_->GetRenderContext(), tabBarNode_->GetGeometryNode(), tabBarPaintProperty_);
    paintMethod->UpdateContentModifier(&paintWrapper);
    auto tabBarPaintMethod = Ace::AceType::DynamicCast<TabBarPaintMethod>(paintMethod);
    EXPECT_NE(tabBarPaintMethod->tabBarModifier_, nullptr);

    PaintWrapper paintWrapper2(tabBarNode_->GetRenderContext(), tabBarNode_->GetGeometryNode(), nullptr);
    paintMethod->UpdateContentModifier(&paintWrapper2);
    EXPECT_NE(tabBarPaintMethod->tabBarModifier_, nullptr);
}

/**
 * @tc.name: TabBarPaintMethodPaintGradient001
 * @tc.desc: test PaintGradient
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPaintMethodPaintGradient001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    IndicatorStyle indicator;
    tabBarPattern_->SetIndicatorStyle(indicator, 0);
    SelectedMode selectedMode = SelectedMode::INDICATOR;
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[0], indicator);
    tabBarPattern_->SetSelectedMode(selectedMode, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], selectedMode);
    std::vector<bool> gradientRegions = { true, true, true, true, true };
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    auto paintMethod = AceType::MakeRefPtr<TabBarPaintMethod>(
        tabBarModifier, gradientRegions, Color::BLACK, indicator, 0.0, selectedMode);

    PaintWrapper paintWrapper(tabBarNode_->GetRenderContext(), tabBarNode_->GetGeometryNode(), tabBarPaintProperty_);
    auto drawFunction = paintMethod->GetForegroundDrawFunction(&paintWrapper);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRect(_)).WillRepeatedly(Return());
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    drawFunction(rsCanvas);
    EXPECT_TRUE(paintMethod->gradientRegions_[0]);

    gradientRegions[0] = false;
    paintMethod = AceType::MakeRefPtr<TabBarPaintMethod>(
        tabBarModifier, gradientRegions, Color::BLACK, indicator, 0.0, selectedMode);
    PaintWrapper paintWrapper2(tabBarNode_->GetRenderContext(), tabBarNode_->GetGeometryNode(), tabBarPaintProperty_);
    drawFunction = paintMethod->GetForegroundDrawFunction(&paintWrapper2);
    drawFunction(rsCanvas);
    EXPECT_FALSE(paintMethod->gradientRegions_[0]);
}

/**
 * @tc.name: TabsModelSetBarOverlap001
 * @tc.desc: test SetBarOverlap
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelSetBarOverlap001, TestSize.Level1)
{
    /**
     * @tc.steps: steps2. SetBarOverlap true
     * @tc.expected: steps2. Check the BarOverlap property value
     */
    CreateWithItem([](TabsModelNG model) {
        model.SetBarOverlap(true);
    });
    EXPECT_TRUE(layoutProperty_->GetBarOverlap().value());

    CreateWithItem([](TabsModelNG model) {
        model.SetBarOverlap(false);
    });
    EXPECT_FALSE(layoutProperty_->GetBarOverlap().value());

    CreateWithItem([](TabsModelNG model) {
        model.SetBarOverlap(true);
    });
    tabBarPaintProperty_->UpdateBarBackgroundColor(Color::RED);
    EXPECT_TRUE(layoutProperty_->GetBarOverlap().value());

    CreateWithItem([](TabsModelNG model) {
        model.SetBarOverlap(false);
    });
    tabBarPaintProperty_->UpdateBarBackgroundColor(Color::RED);
    EXPECT_FALSE(layoutProperty_->GetBarOverlap().value());
}

/**
 * @tc.name: TabBarPatternHandleBottomTabBarChange001
 * @tc.desc: test HandleBottomTabBarChange
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleBottomTabBarChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step2. call HandleBottomTabBarChange function.
     * @tc.expected: step2. expect The function is run ok.
     */
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 1);
    });
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 1);
    tabBarPattern_->indicator_ = 0;
    tabBarPattern_->HandleBottomTabBarChange(1);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
}

/**
 * @tc.name: TabBarPatternHandleBottomTabBarChange002
 * @tc.desc: test HandleBottomTabBarChange
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleBottomTabBarChange002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a bottom style tabbar and a sub style tabbar.
     */
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 1);
    });

    /**
     * @tc.steps: step2. call HandleBottomTabBarChange function.
     * @tc.expected: step2. expect The function is run ok.
     */
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    tabBarPattern_->indicator_ = 0;
    tabBarPattern_->HandleBottomTabBarChange(1);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
}

/**
 * @tc.name: TabBarPatternHandleBottomTabBarChange003
 * @tc.desc: test HandleBottomTabBarChange
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleBottomTabBarChange003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a bottom style tabbar and a sub style tabbar.
     */
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 1);
    });

    /**
     * @tc.steps: step2. call HandleBottomTabBarChange function.
     * @tc.expected: step2. expect The function is run ok.
     */
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    tabBarPattern_->indicator_ = 1;
    tabBarPattern_->HandleBottomTabBarChange(0);
    EXPECT_EQ(tabBarPattern_->indicator_, 1);
}

/**
 * @tc.name: TabBarPatternHandleBottomTabBarChange004
 * @tc.desc: test HandleBottomTabBarChange
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleBottomTabBarChange004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a sub style tabbar and a bottom style tabbar.
     */
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 1);
    });

    /**
     * @tc.steps: step2. call HandleBottomTabBarChange function.
     * @tc.expected: step2. expect The function is run ok.
     */
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 1);
    tabBarPattern_->indicator_ = 0;
    tabBarPattern_->HandleBottomTabBarChange(0);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
}

/**
 * @tc.name: TabBarPatternHandleBottomTabBarChange005
 * @tc.desc: test HandleBottomTabBarChange
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleBottomTabBarChange005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build two sub style tabbar.
     */
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 1);
    });

    /**
     * @tc.steps: step2. call HandleBottomTabBarChange function.
     * @tc.expected: step2. expect The function is run ok.
     */
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    tabBarPattern_->indicator_ = 0;
    tabBarPattern_->HandleBottomTabBarChange(1);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
}

/**
 * @tc.name: TabBarPatternMaskAnimationFinish001
 * @tc.desc: test MaskAnimationFinish
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternMaskAnimationFinish001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build two bottom style tabbar.
     */
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 1);
    });

    /**
     * @tc.steps: step2. call MaskAnimationFinish function.
     * @tc.expected: step2. expect The function is run ok.
     */
    tabBarPattern_->MaskAnimationFinish(tabBarNode_, 0, true);
    EXPECT_NE(tabBarNode_->GetChildAtIndex(0), nullptr);
    tabBarPattern_->MaskAnimationFinish(tabBarNode_, 1, false);
    EXPECT_NE(tabBarNode_->GetChildAtIndex(1), nullptr);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
}

/**
 * @tc.name: TabBarPatternMaskAnimationFinish002
 * @tc.desc: test MaskAnimationFinish
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternMaskAnimationFinish002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build two bottom style tabbar.
     */
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 1);
    });

    /**
     * @tc.steps: step2. call MaskAnimationFinish function.
     * @tc.expected: step2. expect The function is run ok.
     */
    IconStyle iconStyle;
    iconStyle.unselectedColor = Color::WHITE;
    iconStyle.selectedColor = Color::WHITE;
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    tabBarPattern_->MaskAnimationFinish(tabBarNode_, 0, false);
    EXPECT_NE(tabBarNode_->GetChildAtIndex(0), nullptr);
    tabBarPattern_->MaskAnimationFinish(tabBarNode_, 1, true);
    EXPECT_NE(tabBarNode_->GetChildAtIndex(1), nullptr);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
}

/**
 * @tc.name: TabBarPatternChangeMask001
 * @tc.desc: test ChangeMask
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternChangeMask001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build two bottom style tabbar.
     */
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 1);
    });

    /**
     * @tc.steps: step2. call ChangeMask function.
     * @tc.expected: step2. expect The function is run ok.
     */
    auto tabBarGeometryNode = tabBarNode_->GetGeometryNode();
    auto tabBarOffset = tabBarGeometryNode->GetMarginFrameOffset();

    auto maskNode1 = AceType::DynamicCast<FrameNode>(
        tabBarNode_->GetChildAtIndex(tabBarNode_->GetChildren().size() - TEST_SELECTED_MASK_COUNT));
    auto imageNode1 = AceType::DynamicCast<FrameNode>(maskNode1->GetChildren().front());

    auto maskNode2 = AceType::DynamicCast<FrameNode>(
        tabBarNode_->GetChildAtIndex(tabBarNode_->GetChildren().size() - TEST_SELECTED_MASK_COUNT + 1));
    auto imageNode2 = AceType::DynamicCast<FrameNode>(maskNode2->GetChildren().front());

    tabBarPattern_->ChangeMask(TEST_TAB_BAR_INDEX, 1.0f, tabBarOffset, 1.0f, TEST_MASK_MIDDLE_RADIUS_RATIO, true);
    tabBarPattern_->ChangeMask(TEST_TAB_BAR_INDEX, 1.0f, tabBarOffset, 0.99f, TEST_MASK_MIDDLE_RADIUS_RATIO, false);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);

    auto selectedmaskPosition = tabBarNode_->GetChildren().size() - TEST_SELECTED_MASK_COUNT;
    auto selectedMaskNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(selectedmaskPosition));
    auto selectedImageNode = AceType::DynamicCast<FrameNode>(selectedMaskNode->GetChildren().front());
    auto selectedImageRenderContext = selectedImageNode->GetRenderContext();
    EXPECT_DOUBLE_EQ(selectedImageRenderContext->GetOpacity().value(), 1.0f);
    auto unselectedmaskPosition = tabBarNode_->GetChildren().size() - TEST_UNSELECTED_MASK_COUNT;
    auto unselectedMaskNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(unselectedmaskPosition));
    auto unSelectedImageNode = AceType::DynamicCast<FrameNode>(unselectedMaskNode->GetChildren().front());
    auto unSelectedImageRenderContext = unSelectedImageNode->GetRenderContext();
    EXPECT_DOUBLE_EQ(unSelectedImageRenderContext->GetOpacity().value(), 0.99f);
}

/**
 * @tc.name: TabBarPatternUpdateImageColor001
 * @tc.desc: test UpdateImageColor
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternUpdateImageColor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build two bottom style tabbar.
     */
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 1);
    });

    /**
     * @tc.steps: step2. call UpdateImageColor function.
     * @tc.expected: step2. expect The function is run ok.
     */
    tabBarPattern_->UpdateImageColor(0);
    EXPECT_NE(tabBarNode_->GetChildAtIndex(0), nullptr);
    tabBarPattern_->UpdateImageColor(1);
    EXPECT_NE(tabBarNode_->GetChildAtIndex(1), nullptr);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
    tabBarPattern_->SetMaskAnimationByCreate(false);
    EXPECT_EQ(tabBarPattern_->IsMaskAnimationByCreate(), false);
}

/**
 * @tc.name: TabBarLayoutAlgorithmLayoutMask001
 * @tc.desc: test LayoutMask
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmLayoutMask001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call UpdateSelectedMask and UpdateUnselectedMask.
     */
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });

    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    tabBarLayoutProperty_->UpdateSelectedMask(0);
    tabBarLayoutProperty_->UpdateUnselectedMask(1);
    std::vector<OffsetF> childOffsetDelta = { OffsetF(), OffsetF() };
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarLayoutProperty_);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabBarLayoutAlgorithm));

    /**
     * @tc.steps: step2. build selectedMaskNode and unselectedMaskNode.
     */
    auto selectedmaskPosition = tabBarNode_->GetChildren().size() - TEST_SELECTED_MASK_COUNT;
    auto selectedMaskNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(selectedmaskPosition));
    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> selectedMaskLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(selectedMaskNode, geometryNode1, selectedMaskNode->GetLayoutProperty());
    layoutWrapper.AppendChild(selectedMaskLayoutWrapper);

    auto unselectedmaskPosition = tabBarNode_->GetChildren().size() - TEST_UNSELECTED_MASK_COUNT;
    auto unselectedMaskNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(unselectedmaskPosition));
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    auto unselectedProperty = unselectedMaskNode->GetLayoutProperty();
    RefPtr<LayoutWrapperNode> unselectedMaskLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(unselectedMaskNode, geometryNode2, unselectedProperty);
    layoutWrapper.AppendChild(unselectedMaskLayoutWrapper);

    /**
     * @tc.steps: step3. call LayoutMask function.
     * @tc.expected: step3. expect The function is run ok.
     */
    tabBarLayoutAlgorithm->LayoutMask(&layoutWrapper, childOffsetDelta);
    EXPECT_EQ(tabBarLayoutProperty_->GetSelectedMask().value_or(-1), 0);
    EXPECT_EQ(tabBarLayoutProperty_->GetUnselectedMask().value_or(-1), 1);
}

/**
 * @tc.name: TabBarLayoutAlgorithmLayoutMask002
 * @tc.desc: test LayoutMask
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmLayoutMask002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });

    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabBarLayoutAlgorithm));

    auto selectedmaskPosition = tabBarNode_->GetChildren().size() - TEST_SELECTED_MASK_COUNT;
    auto selectedMaskNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(selectedmaskPosition));
    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> selectedMaskLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(selectedMaskNode, geometryNode1, selectedMaskNode->GetLayoutProperty());
    layoutWrapper.AppendChild(selectedMaskLayoutWrapper);

    auto unselectedmaskPosition = tabBarNode_->GetChildren().size() - TEST_UNSELECTED_MASK_COUNT;
    auto unselectedMaskNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(unselectedmaskPosition));
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    auto unselectedProperty = unselectedMaskNode->GetLayoutProperty();
    RefPtr<LayoutWrapperNode> unselectedMaskLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(unselectedMaskNode, geometryNode2, unselectedProperty);
    layoutWrapper.AppendChild(unselectedMaskLayoutWrapper);

    /**
     * @tc.steps: step2. call LayoutMask function.
     * @tc.expected: step2. expect The function is run ok.
     */
    tabBarLayoutAlgorithm->LayoutMask(&layoutWrapper, {});
    EXPECT_EQ(tabBarLayoutProperty_->GetSelectedMask().value_or(-1), -1);
    EXPECT_EQ(tabBarLayoutProperty_->GetUnselectedMask().value_or(-1), -1);
}

/**
 * @tc.name: TabBarLayoutAlgorithmLayoutMask003
 * @tc.desc: test LayoutMask
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmLayoutMask003, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabBarLayoutAlgorithm));

    /**
     * @tc.steps: step2. call LayoutMask function.
     * @tc.expected: step2. expect The function is run ok.
     */
    tabBarLayoutAlgorithm->LayoutMask(&layoutWrapper, {});
}

/**
 * @tc.name: TabBarLayoutAlgorithmUpdateChildConstraint001
 * @tc.desc: test UpdateChildConstraint
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmUpdateChildConstraint001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build tabBarNode_ and ideaSize.
     */
    CreateWithItem([](TabsModelNG model) {});
    LayoutConstraintF childConstraint = LayoutConstraintF();
    std::optional<int32_t> tabBarTestId_(frameNode_->GetTabBarId());
    auto tabBarNode = GroupNode::GetFrameNode(V2::TAB_BAR_ETS_TAG, tabBarTestId_.value());
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());

    float width = 1.0;
    float height = 2.0;
    auto ideaSize = SizeF(width, height);
    int32_t childCount = 1;
    auto axis = Axis::HORIZONTAL;
    tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;

    /**
     * @tc.steps: step2. call UpdateChildConstraint function.
     * @tc.expected: The function is run ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarLayoutAlgorithm->UpdateChildConstraint(
                    childConstraint, tabBarLayoutProperty_, ideaSize, childCount, axis);
                axis = Axis::VERTICAL;
            }
            tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::BOTTOMTABBATSTYLE;
            axis = Axis::HORIZONTAL;
        }
        tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
        tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    }
}

/**
 * @tc.name: TabBarLayoutAlgorithmMeasureMaxHeight002
 * @tc.desc: test MeasureMaxHeight
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmMeasureMaxHeight002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty<TabBarLayoutProperty>());
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode_, geometryNode1, swiperNode_->GetLayoutProperty());
    swiperLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(swiperLayoutWrapper);

    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    SizeF frameSize(SizeF(0.0f, 0.0f));

    /**
     * @tc.steps: step2. call MeasureMaxHeight function.
     * @tc.expected: The function is run ok.
     */
    tabBarLayoutAlgorithm->MeasureMaxHeight(&layoutWrapper, 5);
    tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    tabBarLayoutAlgorithm->MeasureMaxHeight(&layoutWrapper, 5);
}

/**
 * @tc.name: TabBarLayoutAlgorithmMeasureItemWidths002
 * @tc.desc: test MeasureItemWidths
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmMeasureItemWidths002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty<TabBarLayoutProperty>());
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode_, geometryNode1, swiperNode_->GetLayoutProperty());
    swiperLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(swiperLayoutWrapper);
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());

    /**
     * @tc.steps: step2. call MeasureItemWidths function.
     * @tc.expected: The function is run ok.
     */
    tabBarLayoutAlgorithm->MeasureItemWidths(&layoutWrapper, 5);

    tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    tabBarLayoutAlgorithm->MeasureItemWidths(&layoutWrapper, 5);
    EXPECT_EQ(tabBarLayoutAlgorithm->maxHeight_, 0);
}

/**
 * @tc.name: TabBarLayoutAlgorithmHandleAlwaysAverageSplitLayoutStyle003
 * @tc.desc: test HandleAlwaysAverageSplitLayoutStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmHandleAlwaysAverageSplitLayoutStyle003, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty<TabBarLayoutProperty>());
    LayoutWrapperNode layoutWrapper_test =
        LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty<TabBarLayoutProperty>());
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode_, geometryNode1, swiperLayoutProperty_);
    swiperLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(swiperLayoutWrapper);

    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    tabBarLayoutAlgorithm->HandleAlwaysAverageSplitLayoutStyle(&layoutWrapper, FIRST_ITEM_SIZE, 5);
    tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    tabBarLayoutAlgorithm->HandleAlwaysAverageSplitLayoutStyle(&layoutWrapper, FIRST_ITEM_SIZE, 5);
}

/**
 * @tc.name: TabBarLayoutAlgorithmHandleSpaceBetweenOrCenterLayoutStyle002
 * @tc.desc: test HandleSpaceBetweenOrCenterLayoutStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmHandleSpaceBetweenOrCenterLayoutStyle002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(tabBarNode_, geometryNode, tabBarLayoutProperty_);
    LayoutWrapperNode layoutWrapper_test =
        LayoutWrapperNode(tabBarNode_, geometryNode, tabBarLayoutProperty_);
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode_, geometryNode1, swiperNode_->GetLayoutProperty());
    swiperLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(swiperLayoutWrapper);

    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    SizeF frameSize(SizeF(0.0f, 0.0f));
    /**
     * @tc.steps: step2. call HandleSpaceBetweenOrCenterLayoutStyle function.
     * @tc.expected: The function is run ok.
     */
    tabBarLayoutAlgorithm->HandleSpaceBetweenOrCenterLayoutStyle(&layoutWrapper, FIRST_ITEM_SIZE, 5);
    tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    tabBarLayoutAlgorithm->HandleSpaceBetweenOrCenterLayoutStyle(&layoutWrapper, FIRST_ITEM_SIZE, 5);
}

/**
 * @tc.name: TabBarLayoutAlgorithmGetGridSizeType002
 * @tc.desc: test GetGridSizeType
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmGetGridSizeType002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    CreateWithItem([](TabsModelNG model) {});
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(tabBarNode_, geometryNode, tabBarLayoutProperty_);
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    /**
     * @tc.steps: step2. call GetGridSizeType function.
     * @tc.expected: The function is run ok.
     */
    tabBarLayoutAlgorithm->GetGridSizeType(FIRST_ITEM_SIZE);
    tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    tabBarLayoutAlgorithm->GetGridSizeType(FIRST_ITEM_SIZE);
}

/**
 * @tc.name: TabBarLayoutAlgorithmCalculateBackChildrenMainSize001
 * @tc.desc: test CalculateBackChildrenMainSize
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmCalculateBackChildrenMainSize001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    tabBarLayoutProperty_->UpdateSelectedMask(0);
    tabBarLayoutProperty_->UpdateUnselectedMask(1);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarLayoutProperty_);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabBarLayoutAlgorithm));
    int32_t indicator = -2;
    auto axis = Axis::HORIZONTAL;

    /**
     * @tc.steps: step2. build selectedMaskNode.
     */
    for (int i = 0; i <= 2; i++) {
        auto selectedmaskPosition = tabBarNode_->GetChildren().size() - TEST_SELECTED_MASK_COUNT;
        auto selectedMaskNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(selectedmaskPosition));
            RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();
        RefPtr<LayoutWrapperNode> selectedMaskLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
            selectedMaskNode, geometryNode1, selectedMaskNode->GetLayoutProperty());
        layoutWrapper.AppendChild(selectedMaskLayoutWrapper);
    }

    /**
     * @tc.steps: step3. call CalculateBackChildrenMainSize function.
     * @tc.expected: The function is run ok.
     */
    for (int i = 0; i <= 1; i++) {
        ASSERT_FLOAT_EQ(tabBarLayoutAlgorithm->CalculateBackChildrenMainSize(&layoutWrapper, indicator, axis), 0.0f);
        indicator = -1;
    }
}

/**
 * @tc.name: TabsModelSetBarBackgroundColor001
 * @tc.desc: test SetBarBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelSetBarBackgroundColor001, TestSize.Level1)
{
    /**
     * @tc.steps: steps2. SetBarBackgroundColor true
     * @tc.expected: steps2. Check the BarBarBackgroundColor property value
     */
    CreateWithItem([](TabsModelNG model) {
        model.SetBarBackgroundColor(Color::RED);
    });
    EXPECT_EQ(tabBarPaintProperty_->GetBarBackgroundColor().value_or(Color::BLACK), Color::RED);
}

/**
 * @tc.name: TabsModelSetTabBarWidth001
 * @tc.desc: test SetTabBarWidth
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelSetTabBarWidth001, TestSize.Level1)
{
    /**
     * @tc.steps: step2. Test function SetTabBarWidth and SetTabBarHeight When tabBarWidth and tabBarHeight change.
     * @tc.expected: Related functions run ok.
     */
    CreateWithItem([](TabsModelNG model) {
        Dimension tabBarWidth = 10.0_vp;
        Dimension tabBarHeight = 3.0_vp;
        for (int i = 0; i <= 1; i++) {
            model.SetTabBarWidth(tabBarWidth);
            model.SetTabBarHeight(tabBarHeight);
            tabBarWidth = -1.0_vp;
            tabBarHeight = -1.0_vp;
        }
    });
}

/**
 * @tc.name: TabsModelSetWidthAuto001
 * @tc.desc: test SetWidthAuto and SetHeightAuto
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelSetWidthAuto001, TestSize.Level1)
{
 /**
  * @tc.steps: step1. Test function SetWidthAuto and SetHeightAuto When isAuto is true.
  * @tc.expected: Related functions run ok.
  */
    CreateWithItem([](TabsModelNG model) {
        model.SetWidthAuto(true);
        model.SetHeightAuto(true);
    });
    auto tabsLayoutProperty = layoutProperty_;
    EXPECT_TRUE(tabsLayoutProperty->GetWidthAutoValue(false));
    EXPECT_TRUE(tabsLayoutProperty->GetHeightAutoValue(false));
}

/**
 * @tc.name: TabsModelSetAnimationDuration001
 * @tc.desc: test SetAnimationDuration
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelSetAnimationDuration001, TestSize.Level1)
{
    /**
     * @tc.steps: step2. Test function SetAnimationDuration.
     * @tc.expected: Related function runs ok.
     */
    CreateWithItem([](TabsModelNG model) {
        bool duration = true;
        for (int i = 0; i <= 1; i++) {
            model.SetAnimationDuration(duration);
            duration = false;
        }
    });
}

/**
 * @tc.name: TabsModelGetOrCreateTabsNode001
 * @tc.desc: test GetOrCreateTabsNode
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelGetOrCreateTabsNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step2. Test function TabsModelGetOrCreateTabsNode.
     * @tc.expected: Related function runs ok.
     */
    CreateWithItem([](TabsModelNG model) {});
    const std::string tag = "TabsID";
    int32_t nodeId = 1;
    auto frameNode = TabsModelNG::GetOrCreateTabsNode(tag, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: TabBarPatternInitClick001
 * @tc.desc: test InitClick
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternInitClick001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    tabBarPattern_->clickEvent_ = nullptr;

    /**
     * @tc.steps: step2. Test function InitClick.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->InitClick(gestureHub);
        tabBarPattern_->clickEvent_ = AceType::MakeRefPtr<ClickEvent>([](GestureEvent&) {});
    }
}

/**
 * @tc.name: TabBarPatternInitScrollable001
 * @tc.desc: test InitScrollable
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternInitScrollable001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    tabBarPattern_->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(Axis::HORIZONTAL);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);

    /**
     * @tc.steps: step2. Test function InitScrollable.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            tabBarPattern_->InitScrollable(gestureHub);
            tabBarPattern_->axis_ = Axis::VERTICAL;
        }
        tabBarPattern_->scrollableEvent_ = nullptr;
    }
}

/**
 * @tc.name: TabBarPatternInitTouche001
 * @tc.desc: test InitTouch, InitHoverEvent and InitMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternInitTouche001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    tabBarPattern_->touchEvent_ = AceType::MakeRefPtr<TouchEventImpl>([](TouchEventInfo&) {});
    tabBarPattern_->hoverEvent_ = AceType::MakeRefPtr<InputEvent>([](MouseInfo&) {});
    tabBarPattern_->mouseEvent_ = AceType::MakeRefPtr<InputEvent>([](MouseInfo&) {});

    /**
     * @tc.steps: step2. Test function InitTouch, InitHoverEvent and InitMouseEvent.
     * @tc.expected: Related functions run ok.
     */
    tabBarPattern_->InitTouch(gestureHub);
    tabBarPattern_->InitHoverEvent();
    tabBarPattern_->InitMouseEvent();
}

/**
 * @tc.name: TabBarPatternHandleMouseEvent001
 * @tc.desc: test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleMouseEvent001, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    auto info = MouseInfo();
    Offset s1(0.1, 0.1);
    OffsetF c1(0.1f, 0.1f);
    OffsetF c2(0.2f, 0.2f);
    info.SetLocalLocation(s1);
    tabBarPattern_->tabItemOffsets_.emplace_back(c1);
    tabBarPattern_->tabItemOffsets_.emplace_back(c2);

    /**
     * @tc.steps: step2. Test function HandleMouseEvent.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            tabBarPattern_->HandleMouseEvent(info);
        }
        tabBarPattern_->AddTabBarItemType(1, true);
    }
}

/**
 * @tc.name: TabBarmodifieronDraw002
 * @tc.desc: test onDraw
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarmodifieronDraw002, TestSize.Level1)
{
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRect(_)).Times(AnyNumber());
    EXPECT_CALL(rsCanvas, DrawRoundRect(_)).Times(AnyNumber());
    EXPECT_CALL(rsCanvas, Restore()).Times(AnyNumber());

    /**
     * @tc.steps: step2. Test function onDraw.
     * @tc.expected: Related function runs ok.
     */
    float height = 1.0f;
    DrawingContext context { rsCanvas, 10.0f, 10.0f };
    tabBarModifier->hasIndicator_ = nullptr;
    tabBarModifier->indicator_.SetHeight(height);
    tabBarModifier->onDraw(context);
}

/*
 * @tc.name: TabBarPatternHandleMouseEvent002
 * @tc.desc: test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleMouseEvent002, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
    tabBarNode_->Clean(false, false);

    /**
     * @tc.steps: step2. Test function GetBottomTabBarImageSizeAndOffset.
     * @tc.expected: Related function runs ok.
     */
    auto info = MouseInfo();
    int32_t nodeId = 1;
    tabBarPattern_->HandleMouseEvent(info);
    for (int i = 0; i <= 2; i++) {
        auto frameNode_ = TabsModelNG::GetOrCreateTabsNode(
            V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
        tabBarNode_->AddChild(frameNode_);
    }

    Offset s1(0.1, 0.1);
    OffsetF c1(0.1f, 0.1f);
    OffsetF c2(0.2f, 0.2f);
    info.SetLocalLocation(s1);
    tabBarPattern_->tabItemOffsets_.emplace_back(c1);
    tabBarPattern_->tabItemOffsets_.emplace_back(c2);
    tabBarPattern_->HandleMouseEvent(info);
}

/**
 * @tc.name: TabBarPatternGetBottomTabBarImageSizeAndOffset001
 * @tc.desc: test GetBottomTabBarImageSizeAndOffset
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternGetBottomTabBarImageSizeAndOffset001, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
    std::vector<int32_t> selectedIndexes(1, 1);
    float selectedImageSize = 1.0f;
    float unselectedImageSize = 1.1f;
    OffsetF originalSelectedMaskOffset(1.0f, 1.1f);
    OffsetF originalUnselectedMaskOffset(0.0f, 1.0f);

    /**
     * @tc.steps: step2. Test function HandleMouseEvent.
     * @tc.expected: Related function runs ok.
     */
    int32_t maskIndex = 0;
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->GetBottomTabBarImageSizeAndOffset(selectedIndexes, maskIndex, selectedImageSize,
            unselectedImageSize, originalSelectedMaskOffset, originalUnselectedMaskOffset);
        maskIndex = 1;
    }

    IconStyle iconStyle;
    iconStyle.unselectedColor = Color::WHITE;
    iconStyle.selectedColor = Color::WHITE;
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    maskIndex = 0;
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->GetBottomTabBarImageSizeAndOffset(selectedIndexes, maskIndex, selectedImageSize,
            unselectedImageSize, originalSelectedMaskOffset, originalUnselectedMaskOffset);
        maskIndex = 1;
    }

    int32_t nodeId = 1;
    for (int i = 0; i <= 2; i++) {
        auto frameNode_ = TabsModelNG::GetOrCreateTabsNode(
            V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
        tabBarNode_->AddChild(frameNode_);
    }
    maskIndex = 0;
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            tabBarPattern_->GetBottomTabBarImageSizeAndOffset(selectedIndexes, maskIndex, selectedImageSize,
                unselectedImageSize, originalSelectedMaskOffset, originalUnselectedMaskOffset);
            maskIndex = 1;
        }
        tabBarNode_->Clean(false, false);
    }
}

/*
 * @tc.name: TabBarPatternHandleMouseEvent003
 * @tc.desc: test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleMouseEvent003, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });

    /**
     * @tc.steps: step2. Test function HandleMouseEvent.
     * @tc.expected: Related function runs ok.
     */
    auto info = MouseInfo();
    int32_t nodeId = 1;
    for (int i = 0; i <= 2; i++) {
        auto frameNode_ = TabsModelNG::GetOrCreateTabsNode(
            V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
        tabBarNode_->AddChild(frameNode_);
    }
    Offset s1(0.2, 0.2);
    Offset s2(0.3, 0.3);
    OffsetF c1(0.1f, 0.1f);
    OffsetF c2(0.2f, 0.2f);
    OffsetF c3(0.3f, 0.3f);
    info.SetLocalLocation(s1);
    tabBarPattern_->tabItemOffsets_ = { c1, c2, c3 };
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->HandleMouseEvent(info);
        info.SetLocalLocation(s2);
    }
}

/**
 * @tc.name: TabBarPatternHandleBottomTabBarClick001
 * @tc.desc: test HandleBottomTabBarClick
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleBottomTabBarClick001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    int32_t selectedIndex = 1;
    int32_t unselectedIndex = 1;

    /**
     * @tc.steps: step2. Test function HandleBottomTabBarClick.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern_->HandleBottomTabBarClick(selectedIndex, unselectedIndex);
}

/**
 * @tc.name: TabBarPatternHandleSubTabBarClick002
 * @tc.desc: test HandleSubTabBarClick
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleSubTabBarClick002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    int32_t index = 1;
    SizeF size(0.1f, 0.2f);
    tabBarNode_->GetGeometryNode()->SetFrameSize(size);
    tabBarPattern_->SetChildrenMainSize(0.3f);
    auto swiperFrameNode = AceType::DynamicCast<FrameNode>(frameNode_->GetTabs());
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    swiperPattern->currentIndex_ = 0;
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarPattern_->axis_ = Axis::HORIZONTAL;

    int32_t nodeId = 1;
    for (int i = 0; i <= 4; i++) {
        auto frameNode_ = TabsModelNG::GetOrCreateTabsNode(
            V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
        tabBarNode_->AddChild(frameNode_);
    }
    tabBarNode_->GetGeometryNode()->GetFrameSize().SetMainSize(2.0f, Axis::HORIZONTAL);
    auto childFrameNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(index));
    auto childGeometryNode = childFrameNode->GetGeometryNode();
    childGeometryNode->GetMarginFrameSize().SetMainSize(1.0f, Axis::HORIZONTAL);
    auto childFrameNode1 = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(index - 1));
    auto childGeometryNode1 = childFrameNode1->GetGeometryNode();
    auto childFrameSize1 = childGeometryNode1->GetMarginFrameSize();
    childFrameSize1.SetMainSize(0.1f, Axis::HORIZONTAL);
    OffsetF c1(0.1f, 0.2f);
    tabBarPattern_->tabItemOffsets_.emplace_back(c1);

    /**
     * @tc.steps: step2. Test function HandleSubTabBarClick.
     * @tc.expected: Related function runs ok.
     */
    for (int32_t i = 0; i <= 1; i++) {
        tabBarPattern_->HandleSubTabBarClick(tabBarLayoutProperty_, index);
        tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::FIXED);
    }
}

/**
 * @tc.name: TabBarPatternOnKeyEvent001
 * @tc.desc: test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternOnKeyEvent001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    EXPECT_EQ(swiperNode_->TotalChildCount(), 4);
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->isFocusActive_ = true;

    /**
     * @tc.steps: steps2. OnKeyEvent
     * @tc.expected: steps2. Check the result of OnKeyEvent
     */
    KeyEvent event;
    event.code = KeyCode::KEY_DPAD_RIGHT;
    tabBarLayoutProperty_->UpdateIndicator(2);
    EXPECT_FALSE(tabBarPattern_->OnKeyEvent(event));
}

/**
 * @tc.name: TabBarPatternHandleTouchEvent001
 * @tc.desc: test HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleTouchEvent001, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);

    /**
     * @tc.steps: steps2. HandleTouchEvent
     * @tc.expected: steps2. Check the number of tabBarNode_ TotalChildCount
     */
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchLocationInfo.SetLocalLocation(Offset(0.f, 0.f));
    tabBarPattern_->tabItemOffsets_ = { { -1.0f, -1.0f }, { 1.0f, 1.0f }, { 2.0f, 2.0f } };
    tabBarPattern_->HandleTouchEvent(touchLocationInfo);
    EXPECT_EQ(tabBarNode_->TotalChildCount(), 3);
}

/**
 * @tc.name: TabBarmodifierPaintIndicator001
 * @tc.desc: test PaintIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarmodifierPaintIndicator001, TestSize.Level1)
{
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRect(_)).Times(AnyNumber());
    EXPECT_CALL(rsCanvas, DrawRoundRect(_)).Times(AnyNumber());
    EXPECT_CALL(rsCanvas, Restore()).Times(AnyNumber());

    DrawingContext context { rsCanvas, 10.0f, 10.0f };
    RectF indicator(0.0f, 0.0f, 1.0f, 1.0f);
    tabBarModifier->indicatorHeight_->SetUpCallbacks([]() { return 1.0f; }, [](const float&) {});
    tabBarModifier->indicatorWidth_->SetUpCallbacks([]() { return 1.0f; }, [](const float&) {});
    tabBarModifier->indicatorMarginTop_->SetUpCallbacks([]() { return 1.0f; }, [](const float&) {});
    tabBarModifier->indicatorBorderRadius_->SetUpCallbacks([]() { return 1.0f; }, [](const float&) {});

    /**
     * @tc.steps: step2. Test function PaintIndicator.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        tabBarModifier->PaintIndicator(context, indicator);
        tabBarModifier->indicatorHeight_->SetUpCallbacks([]() { return 0.0f; }, [](const float&) {});
        tabBarModifier->indicatorWidth_->SetUpCallbacks([]() { return 0.0f; }, [](const float&) {});
        tabBarModifier->indicatorMarginTop_->SetUpCallbacks([]() { return 0.0f; }, [](const float&) {});
        tabBarModifier->indicatorBorderRadius_->SetUpCallbacks([]() { return 0.0f; }, [](const float&) {});
    }
}

/**
 * @tc.name: TabBarPatternHandleHoverEvent001
 * @tc.desc: test HandleHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleHoverEvent001, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
    bool isHover = true;
    std::optional<int32_t> hoverIndex_test(0);
    OffsetF c1(0.1f, 0.1f);
    OffsetF c2(0.2f, 0.2f);
    tabBarPattern_->tabItemOffsets_.emplace_back(c1);
    tabBarPattern_->tabItemOffsets_.emplace_back(c2);
    tabBarPattern_->hoverIndex_ = hoverIndex_test;
    tabBarPattern_->touchingIndex_ = hoverIndex_test;

    /**
     * @tc.steps: step2. Test function HandleHoverEvent.
     * @tc.expected: Related functions run ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern_->HandleHoverEvent(isHover);
                isHover = false;
                tabBarPattern_->hoverIndex_ = {};
            }
            tabBarPattern_->hoverIndex_ = hoverIndex_test;
        }
        isHover = true;
        tabBarPattern_->hoverIndex_ = {};
    }

    isHover = false;
    IndicatorStyle style;
    style.color = Color::BLACK;
    tabBarPattern_->hoverIndex_ = hoverIndex_test;
    tabBarPattern_->touchingIndex_ = {};
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarPattern_->SetSelectedMode(SelectedMode::BOARD, 0);
    tabBarPattern_->SetIndicatorStyle(style, 0);

    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->HandleHoverEvent(isHover);
        tabBarPattern_->AddTabBarItemType(1, true);
    }
}

/**
 * @tc.name: TabBarPatternHandleHoverOnEvent001
 * @tc.desc: test HandleHoverOnEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleHoverOnEvent001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    std::optional<int32_t> hoverIndex_test(0);
    OffsetF c1(0.1f, 0.1f);
    OffsetF c2(0.2f, 0.2f);
    tabBarPattern_->tabItemOffsets_.emplace_back(c1);
    tabBarPattern_->tabItemOffsets_.emplace_back(c2);
    tabBarPattern_->hoverIndex_ = hoverIndex_test;
    tabBarPattern_->touchingIndex_ = hoverIndex_test;

    /**
     * @tc.steps: step2. Test function HandleHoverOnEvent.
     * @tc.expected: Related functions run ok.
     */
    IndicatorStyle style;
    style.color = Color::BLACK;
    tabBarPattern_->hoverIndex_ = hoverIndex_test;
    tabBarPattern_->touchingIndex_ = {};
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarPattern_->SetSelectedMode(SelectedMode::BOARD, 0);
    tabBarPattern_->SetIndicatorStyle(style, 0);

    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->HandleHoverOnEvent(0);
        tabBarPattern_->AddTabBarItemType(1, true);
    }
}

/**
 * @tc.name: TabsModelSetOnChange001
 * @tc.desc: test SetOnChange
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelSetOnChange001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        model.SetOnChange(nullptr);
    });

    /**
     * @tc.steps: step2. Test function SetOnChange.
     * @tc.expected: Related function runs ok.
     */
    ASSERT_NE(frameNode_, nullptr);
}

/**
 * @tc.name: TabsModelNg001
 * @tc.desc: Tabs Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelNg001, TestSize.Level1)
{
    auto onGestureSwipe = [](int32_t index, const AnimationCallbackInfo& info) {};
    CreateWithItem([=](TabsModelNG model) {
        model.SetOnGestureSwipe(std::move(onGestureSwipe));
    });
    auto eventHub = swiperNode_->GetEventHub<SwiperEventHub>();
    EXPECT_NE(eventHub->gestureSwipeEvent_, nullptr);
}

/**
 * @tc.name: TabsModelSetScrollable001
 * @tc.desc: test SetScrollable
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelSetScrollable001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        model.SetScrollable(true);
        model.SetScrollable(false);
    });
}

/**
 * @tc.name: TabsModelSetClipEdge001
 * @tc.desc: test SetClipEdge
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelSetClipEdge001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        model.SetClipEdge(true);
        model.SetClipEdge(false);
    });
}
/**
 * @tc.name: TabBarPatternOnKeyEvent002
 * @tc.desc: test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternOnKeyEvent002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});

    /**
     * @tc.steps: step2. Test function OnKeyEvent.
     * @tc.expected: Related functions run ok.
     */
    KeyCode code = KeyCode::KEY_CLEAR;
    KeyAction action = KeyAction::CLICK;
    std::vector<KeyCode> pressedCodes;
    pressedCodes.emplace_back(KeyCode::KEY_0);
    pressedCodes.emplace_back(KeyCode::KEY_1);
    int32_t repeatTime = 1;
    int64_t timeStamp = 0;
    std::chrono::milliseconds milliseconds(timeStamp);
    TimeStamp time(milliseconds);
    int32_t metaKey = 1;
    int64_t deviceId = 1;
    SourceType sourceType = SourceType::NONE;
    tabBarPattern_->GetLayoutProperty<TabBarLayoutProperty>()->UpdateAxis(Axis::HORIZONTAL);

    auto event = KeyEvent(code, action, pressedCodes, repeatTime, time, metaKey, deviceId, sourceType, {});
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern_->OnKeyEvent(event);
                event.action = KeyAction::DOWN;
                event.code = KeyCode::KEY_DPAD_LEFT;
            }
            event.code = KeyCode::KEY_DPAD_UP;
        }
        tabBarPattern_->GetLayoutProperty<TabBarLayoutProperty>()->UpdateAxis(Axis::VERTICAL);
    }
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern_->OnKeyEvent(event);
                event.code = KeyCode::KEY_DPAD_RIGHT;
            }
            event.code = KeyCode::KEY_DPAD_DOWN;
        }
        tabBarPattern_->GetLayoutProperty<TabBarLayoutProperty>()->UpdateAxis(Axis::VERTICAL);
    }
    event.code = KeyCode::KEY_TAB;
    tabBarPattern_->GetLayoutProperty<TabBarLayoutProperty>()->UpdateIndicator(1);
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->OnKeyEvent(event);
        tabBarPattern_->GetLayoutProperty<TabBarLayoutProperty>()->UpdateIndicator(-2);
    }
}

/**
 * @tc.name: TabBarPatternHandleTouchEvent002
 * @tc.desc: test HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleTouchEvent002, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);

    /**
     * @tc.steps: steps2. HandleTouchEvent
     * @tc.expected: steps2. Check the number of tabBarNode_ TotalChildCount
     */
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchLocationInfo.SetLocalLocation(Offset(0.f, 0.f));
    tabBarPattern_->tabItemOffsets_ = { { -1.0f, -1.0f }, { 1.0f, 1.0f }, { 2.0f, 2.0f } };
    tabBarPattern_->HandleTouchEvent(touchLocationInfo);
    EXPECT_EQ(tabBarNode_->TotalChildCount(), 3);
}

/**
 * @tc.name: TabBarPatternFocusIndexChange001
 * @tc.desc: test FocusIndexChange
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternFocusIndexChange001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    int32_t index = 1;
    std::optional<int32_t> animation_test = 1;

    /**
     * @tc.steps: step2. Test function FocusIndexChange.
     * @tc.expected: Related functions run ok.
     */
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->FocusIndexChange(index);
        tabBarPattern_->animationDuration_ = animation_test;
    }
}

/**
 * @tc.name: TabBarPatternOnModifyDone001
 * @tc.desc: test OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternOnModifyDone001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);

    /**
     * @tc.steps: step2. Test function FocusIndexChange.
     * @tc.expected: Related functions run ok.
     */
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->OnModifyDone();
        tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::FIXED);
    }
}

/**
 * @tc.name: TabBarPatternMaskAnimationFinish003
 * @tc.desc: test MaskAnimationFinish
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternMaskAnimationFinish003, TestSize.Level1)
{
    /**
     * @tc.steps: step2. Test function MaskAnimationFinish.
     * @tc.expected: Related functions run ok.
     */
    CreateWithItem([](TabsModelNG model) {});
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    int32_t selectedIndex = -1;
    bool isSelected = true;
    tabBarPattern_->MaskAnimationFinish(tabBarNode_, selectedIndex, isSelected);
}

/**
 * @tc.name: TabBarDistributedTest001
 * @tc.desc: Test the distributed capability of TabBar
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarDistributedTest001, TestSize.Level1)
{
    TabsItemDivider divider;
    CreateWithItem([divider](TabsModelNG model) {
        model.SetDivider(divider);
    });

    /**
     * @tc.steps: step2. Set Indicator.
     * @tc.expected: Function ProvideRestoreInfo is called.
     */
    tabBarPattern_->UpdateIndicator(0);
    std::string ret = tabBarPattern_->ProvideRestoreInfo();
    EXPECT_TRUE(ret == R"({"Index":0})");

    /**
     * @tc.steps: step3. Function OnRestoreInfo is called.
     * @tc.expected: Passing invalid & valid JSON format.
     */
    std::string restoreInfo_ = R"({"Index":0})";
    pattern_->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(tabBarLayoutProperty_->GetIndicator().value_or(0), 0);
    restoreInfo_ = R"({"Index":1})";
    pattern_->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(tabBarLayoutProperty_->GetIndicator().value_or(0), 1);
    restoreInfo_ = "invalid_json_string";
    pattern_->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(tabBarLayoutProperty_->GetIndicator().value_or(0), 1);
}

/**
 * @tc.name: TabBarPatternHandleTouchDown001
 * @tc.desc: test HandleTouchDown
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleTouchDown001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarPattern_->swiperController_->SetRemoveSwiperEventCallback(nullptr);
    tabBarPattern_->tabBarStyles_ = { TabBarStyle::SUBTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE };

    /**
     * @tc.steps: step2. Test function HandleTouchDown.
     * @tc.expected: Related functions run ok.
     */
    int32_t index = 1;
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->HandleTouchDown(index);
        tabBarPattern_->swiperController_->SetRemoveSwiperEventCallback([]() {});
    }
}

/**
 * @tc.name: TabBarPatternHandleTouchUp001
 * @tc.desc: test HandleTouchUp
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleTouchUp001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarPattern_->swiperController_->SetAddSwiperEventCallback(nullptr);
    tabBarPattern_->SetTouching(false);
    tabBarPattern_->tabBarStyles_ = { TabBarStyle::SUBTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE };

    /**
     * @tc.steps: step2. Test function HandleTouchUp.
     * @tc.expected: Related functions run ok.
     */
    int32_t index = 1;
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->HandleTouchUp(index);
        tabBarPattern_->swiperController_->SetAddSwiperEventCallback([]() {});
    }
}

/**
 * @tc.name: TabBarPatternHandleTouchUp002
 * @tc.desc: test HandleTouchUp
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleTouchUp002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });

    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    int32_t index = 1;
    tabBarPattern_->swiperController_->SetAddSwiperEventCallback(nullptr);
    tabBarPattern_->SetTouching(true);
    IndicatorStyle indicatorStyle1;
    IndicatorStyle indicatorStyle2;
    indicatorStyle1.color = Color::BLACK;
    indicatorStyle2.color = Color::RED;
    tabBarPattern_->tabBarStyles_ = { TabBarStyle::SUBTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE };
    tabBarPattern_->selectedModes_ = { SelectedMode::BOARD, SelectedMode::INDICATOR };
    tabBarPattern_->indicatorStyles_ = { indicatorStyle1, indicatorStyle2 };

    /**
     * @tc.steps: step2. Test function HandleTouchUp.
     * @tc.expected: Related functions run ok.
     */
    tabBarPattern_->hoverIndex_.emplace(1);
    EXPECT_EQ(tabBarPattern_->hoverIndex_.value(), 1);
    tabBarPattern_->touchingIndex_.emplace(1);
    EXPECT_EQ(tabBarPattern_->touchingIndex_.value(), 1);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern_->HandleTouchUp(index);
                tabBarPattern_->SetTouching(true);
                tabBarPattern_->swiperController_->SetAddSwiperEventCallback([]() {});
                tabBarPattern_->hoverIndex_.reset();
                EXPECT_FALSE(tabBarPattern_->hoverIndex_.has_value());
            }
            tabBarPattern_->touchingIndex_.emplace(0);
        }
        tabBarPattern_->hoverIndex_.emplace(1);
    }

    tabBarPattern_->hoverIndex_.reset();
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->HandleTouchUp(index);
        tabBarPattern_->SetTouching(true);
        tabBarPattern_->hoverIndex_.emplace(1);
    }
}

/**
 * @tc.name: TabBarPatternPlayPressAnimation002
 * @tc.desc: test PlayPressAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternPlayPressAnimation002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    int32_t index = 1;
    auto pressColor = Color();
    pressColor.SetValue(1);
    auto animationType = AnimationType::HOVERTOPRESS;
    IndicatorStyle indicatorStyle1;
    IndicatorStyle indicatorStyle2;
    indicatorStyle1.color = Color::BLACK;
    indicatorStyle2.color = Color::RED;
    tabBarPattern_->tabBarStyles_ = { TabBarStyle::SUBTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE };
    tabBarPattern_->selectedModes_ = { SelectedMode::BOARD, SelectedMode::INDICATOR };
    tabBarPattern_->indicatorStyles_ = { indicatorStyle1, indicatorStyle2 };

    /**
     * @tc.steps: step2. Test function PlayPressAnimation.
     * @tc.expected: Related functions run ok.
     */
    for (int32_t i = 0; i <= 1; i++) {
        tabBarPattern_->PlayPressAnimation(index, pressColor, animationType);
        animationType = AnimationType::HOVER;
    }
}

/**
 * @tc.name: TabBarPatternStopTabBarTranslateAnimation001
 * @tc.desc: test StopTabBarTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternStopTabBarTranslateAnimation001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);

    /**
     * @tc.steps: step2. Test function StopTabBarTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->StopTabBarTranslateAnimation();
    }
    EXPECT_FALSE(tabBarPattern_->tabBarTranslateAnimation_);
}

/**
 * @tc.name: TabBarPatternSetEdgeEffect001
 * @tc.desc: test SetEdgeEffect
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternSetEdgeEffect001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);

    /**
     * @tc.steps: step2. Test function SetEdgeEffect.
     * @tc.expected: Related function runs ok.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    tabBarPattern_->SetEdgeEffect(gestureHub);
}

/**
 * @tc.name: TabBarPatternHandleTouchEvent003
 * @tc.desc: test HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleTouchEvent003, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern_->tabBarType_.emplace(std::make_pair(1, true));

    /**
     * @tc.steps: steps2. HandleTouchEvent
     * @tc.expected: steps2. Check the number of tabBarNode_ TotalChildCount
     */
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchLocationInfo.SetLocalLocation(Offset(0.f, 0.f));
    tabBarPattern_->tabItemOffsets_ = { { -1.0f, -1.0f }, { 1.0f, 1.0f }, { 2.0f, 2.0f } };
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->HandleTouchEvent(touchLocationInfo);
        tabBarPattern_->tabBarType_.clear();
        tabBarNode_->RemoveChildAtIndex(1);
    }
    EXPECT_EQ(tabBarNode_->TotalChildCount(), 1);
}

/**
 * @tc.name: TabBarPatternUpdateTextColorAndFontWeight001
 * @tc.desc: test UpdateTextColorAndFontWeight and UpdateImageColor
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternUpdateTextColorAndFontWeight001, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto pr = tabBarPattern_->tabBarType_.emplace(std::make_pair(1, true));
    ASSERT_TRUE(pr.second);
    /**
     * @tc.steps: step2. Test function UpdateTextColorAndFontWeight and UpdateImageColor.
     * @tc.expected: Related functions run ok.
     */
    int32_t index = 0;
    tabBarPattern_->UpdateTextColorAndFontWeight(index);
    tabBarPattern_->UpdateImageColor(index);

    IconStyle iconStyle;
    iconStyle.unselectedColor = Color::WHITE;
    iconStyle.selectedColor = Color::WHITE;
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    index = 0;
    tabBarPattern_->UpdateTextColorAndFontWeight(index);
    tabBarPattern_->UpdateImageColor(index);
}

/**
 * @tc.name: TabBarPatternUpdateTextColorAndFontWeight002
 * @tc.desc: test UpdateTextColorAndFontWeight
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternUpdateTextColorAndFontWeight002, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    for (int i = 0; i <= 1; i++) {
        AceType::DynamicCast<FrameNode>(
            AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(i))->GetChildren().back())
            ->layoutProperty_ = AceType::MakeRefPtr<TextLayoutProperty>();
        ASSERT_NE(AceType::DynamicCast<FrameNode>(
                      AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(i))->GetChildren().back())
                      ->layoutProperty_,
            nullptr);
    }

    /**
     * @tc.steps: step2. Test function UpdateTextColorAndFontWeight.
     * @tc.expected: Related function runs ok.
     */
    int32_t index = 0;
    tabBarPattern_->UpdateTextColorAndFontWeight(index);
}

/**
 * @tc.name: TabBarPatternInitClick002
 * @tc.desc: test InitClick
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternInitClick002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    tabBarPattern_->clickEvent_ = nullptr;

    /**
     * @tc.steps: step2. Test function InitClick.
     * @tc.expected: Related function runs ok.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    tabBarPattern_->InitClick(gestureHub);
    auto info = GestureEvent();
    tabBarPattern_->clickEvent_->callback_(info);
}

/**
 * @tc.name: TabBarPatternInitScrollable002
 * @tc.desc: test InitScrollable
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternInitScrollable002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    tabBarLayoutProperty_->UpdateAxis(Axis::VERTICAL);
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    scrollable->SetAxis(Axis::HORIZONTAL);
    auto scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(Axis::HORIZONTAL);
    scrollableEvent->SetAxis(Axis::VERTICAL);
    scrollableEvent->SetScrollable(scrollable);
    tabBarPattern_->scrollableEvent_ = scrollableEvent;

    /**
     * @tc.steps: step2. Test function InitScrollable.
     * @tc.expected: Related function runs ok.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->InitScrollable(gestureHub);
        tabBarPattern_->swiperController_->tabBarFinishCallback_();
        scrollableEvent->SetScrollable(nullptr);
        tabBarPattern_->scrollableEvent_ = scrollableEvent;
    }
}

/**
 * @tc.name: TabBarPatternInitScrollable003
 * @tc.desc: test InitScrollable
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternInitScrollable003, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    tabBarLayoutProperty_->UpdateAxis(Axis::VERTICAL);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);

    /**
     * @tc.steps: step2. Test function InitScrollable.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern_->InitScrollable(gestureHub);
                ASSERT_NE(tabBarPattern_->scrollableEvent_, nullptr);
                auto scrollable = tabBarPattern_->scrollableEvent_->GetScrollable();
                scrollable->callback_(0.1, SCROLL_FROM_NONE);
                tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
                tabBarPattern_->axis_ = Axis::HORIZONTAL;
            }
            tabBarPattern_->axis_ = Axis::VERTICAL;
            tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
            tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }
        tabBarPattern_->tabItemOffsets_ = { { -1.0f, -1.0f } };
    }
    auto scrollable = tabBarPattern_->scrollableEvent_->GetScrollable();
    scrollable->callback_(0.1, SCROLL_FROM_START);
    tabBarPattern_->axis_ = Axis::VERTICAL;
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    int32_t source = SCROLL_FROM_UPDATE;
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->InitScrollable(gestureHub);
        scrollable = tabBarPattern_->scrollableEvent_->GetScrollable();
        scrollable->callback_(0.1, source);
        tabBarPattern_->axis_ = Axis::VERTICAL;
        tabBarPattern_->tabItemOffsets_.clear();
        tabBarPattern_->tabItemOffsets_ = { { 1.0f, -1.0f } };
        tabBarNode_->GetGeometryNode()->SetFrameSize(SizeF(1.0f, 2.0f));
    }
}

/**
 * @tc.name: TabBarPatternInitHoverEvent001
 * @tc.desc: test InitHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternInitHoverEvent001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    tabBarPattern_->hoverEvent_ = nullptr;
    tabBarPattern_->mouseEvent_ = nullptr;

    /**
     * @tc.steps: step2. Test function InitHoverEvent and InitMouseEvent.
     * @tc.expected: Related functions run ok.
     */
    tabBarPattern_->InitHoverEvent();
    tabBarPattern_->InitMouseEvent();
    ASSERT_NE(tabBarPattern_->hoverEvent_, nullptr);
    ASSERT_NE(tabBarPattern_->mouseEvent_, nullptr);
    tabBarPattern_->hoverEvent_->onHoverCallback_(true);
    auto info = MouseInfo();
    tabBarPattern_->mouseEvent_->onMouseCallback_(info);
}

/**
 * @tc.name: TabBarPatternInitOnKeyEvent001
 * @tc.desc: test InitOnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternInitOnKeyEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step2. Test function InitOnKeyEvent.
     * @tc.expected: Related function runs ok.
     */
    CreateWithItem([](TabsModelNG model) {});
    auto focusHub = tabBarNode_->GetOrCreateFocusHub();
    auto event = KeyEvent();
    auto paintRect = RoundRect();
    tabBarPattern_->InitOnKeyEvent(focusHub);
    focusHub->ProcessOnKeyEventInternal(event);
    focusHub->getInnerFocusRectFunc_(paintRect);
}

/*
 * @tc.name: TabBarPatternHandleMouseEvent004
 * @tc.desc: test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleMouseEvent004, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
    auto info = MouseInfo();

    /**
     * @tc.steps: step2. Test function HandleMouseEvent.
     * @tc.expected: Related function runs ok.
     */
    int32_t nodeId = 1;
    for (int i = 0; i <= 2; i++) {
        auto frameNode_ = TabsModelNG::GetOrCreateTabsNode(
            V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
        tabBarNode_->AddChild(frameNode_);
    }
    Offset s1(0.1, 0.1);
    Offset s2(0.4, 0.4);
    OffsetF c1(0.1f, 0.1f);
    OffsetF c2(0.2f, 0.2f);
    OffsetF c3(0.3f, 0.3f);
    OffsetF c4(0.4f, 0.4f);
    info.SetLocalLocation(s1);
    ASSERT_EQ(tabBarPattern_->CalculateSelectedIndex(info.GetLocalLocation()), 0);
    tabBarPattern_->hoverIndex_.emplace(1);
    tabBarPattern_->tabItemOffsets_ = { c1, c2, c3, c4 };
    IndicatorStyle indicatorStyle1;
    IndicatorStyle indicatorStyle2;
    IndicatorStyle indicatorStyle3;
    indicatorStyle1.color = Color::BLACK;
    indicatorStyle2.color = Color::RED;
    indicatorStyle3.color = Color::BLUE;
    tabBarPattern_->tabBarStyles_ = { TabBarStyle::SUBTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE,
        TabBarStyle::NOSTYLE };
    tabBarPattern_->selectedModes_ = { SelectedMode::BOARD, SelectedMode::INDICATOR, SelectedMode::BOARD };
    tabBarPattern_->indicatorStyles_ = { indicatorStyle1, indicatorStyle2, indicatorStyle3 };

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            tabBarPattern_->HandleMouseEvent(info);
            info.SetLocalLocation(s2);
            ASSERT_EQ(tabBarPattern_->CalculateSelectedIndex(info.GetLocalLocation()), 2);
            tabBarPattern_->hoverIndex_.reset();
        }
        tabBarPattern_->hoverIndex_.emplace(1);
        tabBarPattern_->touchingIndex_.emplace(1);
    }

    Offset s3(0.2, 0.2);
    info.SetLocalLocation(s3);
    ASSERT_EQ(tabBarPattern_->CalculateSelectedIndex(info.GetLocalLocation()), 0);
    info.SetAction(MouseAction::MOVE);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern_->HandleMouseEvent(info);
                tabBarPattern_->touchingIndex_.reset();
                tabBarPattern_->hoverIndex_ = 1;
            }
            tabBarPattern_->hoverIndex_.reset();
        }
        tabBarPattern_->hoverIndex_.emplace(0);
        info.SetAction(MouseAction::WINDOW_ENTER);
    }

    info.SetAction(MouseAction::WINDOW_LEAVE);
    tabBarPattern_->HandleMouseEvent(info);
}

/**
 * @tc.name: TabBarPatternOnKeyEvent003
 * @tc.desc: test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternOnKeyEvent003, TestSize.Level1)
{
    /**
     * @tc.steps: step2. Test function OnKeyEvent.
     * @tc.expected: Related functions run ok.
     */
    CreateWithItem([](TabsModelNG model) {});
    KeyCode code = KeyCode::KEY_DPAD_LEFT;
    KeyAction action = KeyAction::DOWN;
    std::vector<KeyCode> pressedCodes;
    pressedCodes.emplace_back(KeyCode::KEY_0);
    pressedCodes.emplace_back(KeyCode::KEY_1);
    int32_t repeatTime = 1;
    int64_t timeStamp = 0;
    std::chrono::milliseconds milliseconds(timeStamp);
    TimeStamp time(milliseconds);
    int32_t metaKey = 1;
    int64_t deviceId = 1;
    SourceType sourceType = SourceType::NONE;
    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    tabBarLayoutProperty_->UpdateIndicator(1);
    auto event = KeyEvent(code, action, pressedCodes, repeatTime, time, metaKey, deviceId, sourceType, {});
    tabBarPattern_->OnKeyEvent(event);
}

/**
 * @tc.name: TabBarLayoutAlgorithmLayout002
 * @tc.desc: Test Divider Layout.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmLayout002, TestSize.Level1)
{
    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call Layout function.
     * @tc.expected: Related function is called.
     */
    CreateWithItem([](TabsModelNG model) {});
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(tabBarNode_, geometryNode, tabBarLayoutProperty_);
    AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())->UpdateTabBarMode(TabBarMode::FIXED);
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::BOTTOMTABBATSTYLE;
    AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())->UpdateAxis(Axis::VERTICAL);
    tabBarLayoutAlgorithm->Layout(&layoutWrapper);
}

/**
 * @tc.name: TabBarLayoutAlgorithmLayout003
 * @tc.desc: Test Divider Layout.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmLayout003, TestSize.Level1)
{
    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call Layout function.
     * @tc.expected: Related function is called.
     */
    CreateWithItem([](TabsModelNG model) {});
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(tabBarNode_, geometryNode, tabBarLayoutProperty_);
    auto layoutWrapper1 = AceType::MakeRefPtr<LayoutWrapperNode>(
        tabBarNode_, geometryNode, tabBarLayoutProperty_);
    auto layoutWrapper2 = AceType::MakeRefPtr<LayoutWrapperNode>(
        tabBarNode_, geometryNode, tabBarLayoutProperty_);
    auto layoutWrapper3 = AceType::MakeRefPtr<LayoutWrapperNode>(
        tabBarNode_, geometryNode, tabBarLayoutProperty_);
    auto layoutWrapper4 = AceType::MakeRefPtr<LayoutWrapperNode>(
        tabBarNode_, geometryNode, tabBarLayoutProperty_);
    auto layoutWrapper5 = AceType::MakeRefPtr<LayoutWrapperNode>(
        tabBarNode_, geometryNode, tabBarLayoutProperty_);
    AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())->UpdateAxis(Axis::HORIZONTAL);
    AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())->UpdateIndicator(1);
    tabBarLayoutAlgorithm->indicator_ = 0;
    layoutWrapper.GetGeometryNode()->SetFrameSize(SizeF(0.1f, 0.2f));
    tabBarLayoutAlgorithm->childrenMainSize_ = 0.3f;
    layoutWrapper.AppendChild(layoutWrapper1);
    layoutWrapper.AppendChild(layoutWrapper2);
    layoutWrapper.AppendChild(layoutWrapper3);
    layoutWrapper.AppendChild(layoutWrapper4);
    layoutWrapper.AppendChild(layoutWrapper5);
    layoutWrapper1->GetGeometryNode()->SetFrameSize(SizeF(0.0f, 0.0f));
    layoutWrapper3->GetGeometryNode()->SetFrameSize(SizeF(0.0f, 0.0f));

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarLayoutAlgorithm->Layout(&layoutWrapper);
                tabBarLayoutAlgorithm->indicator_ = 2;
                tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::BOTTOMTABBATSTYLE;
            }
            layoutWrapper.GetGeometryNode()->SetFrameSize(SizeF(1.0f, 1.0f));
            layoutWrapper1->GetGeometryNode()->SetFrameSize(SizeF(2.0f, 2.0f));
            layoutWrapper2->GetGeometryNode()->SetFrameSize(SizeF(0.0f, 0.0f));
        }
        AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())->UpdateAxis(Axis::VERTICAL);
    }

    layoutWrapper3->GetGeometryNode()->SetFrameSize(SizeF(2.0f, 2.0f));
    for (int i = 0; i <= 1; i++) {
        tabBarLayoutAlgorithm->Layout(&layoutWrapper);
        AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())->UpdateAxis(Axis::HORIZONTAL);
    }
}

/**
 * @tc.name: TabBarPatternPlayMaskAnimation001
 * @tc.desc: test PlayMaskAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternPlayMaskAnimation001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});

    /**
     * @tc.steps: step2. Test function PlayMaskAnimation.
     * @tc.expected: Related function runs ok.
     */
    float selectedImageSize = 0.1f;
    OffsetF originalSelectedMaskOffset(0.1f, 0.2f);
    int32_t selectedIndex = 1;
    float unselectedImageSize = 0.2f;
    OffsetF originalUnselectedMaskOffset(0.1f, 0.2f);
    int32_t unselectedIndex = 1;

    auto maskNode1 = AceType::DynamicCast<FrameNode>(
        tabBarNode_->GetChildAtIndex(tabBarNode_->GetChildren().size() - TEST_SELECTED_MASK_COUNT));
    auto imageNode1 = AceType::DynamicCast<FrameNode>(maskNode1->GetChildren().front());

    auto maskNode2 = AceType::DynamicCast<FrameNode>(
        tabBarNode_->GetChildAtIndex(tabBarNode_->GetChildren().size() - TEST_SELECTED_MASK_COUNT + 1));
    auto imageNode2 = AceType::DynamicCast<FrameNode>(maskNode2->GetChildren().front());

    tabBarPattern_->PlayMaskAnimation(selectedImageSize, originalSelectedMaskOffset, selectedIndex, unselectedImageSize,
        originalUnselectedMaskOffset, unselectedIndex);
}

/**
 * @tc.name: TabBarPatternHandleTouchEvent004
 * @tc.desc: test HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleTouchEvent004, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
    IndicatorStyle indicatorStyle1;
    IndicatorStyle indicatorStyle2;
    indicatorStyle1.color = Color::BLACK;
    indicatorStyle2.color = Color::RED;
    tabBarPattern_->tabBarStyles_ = { TabBarStyle::SUBTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE };
    tabBarPattern_->selectedModes_ = { SelectedMode::BOARD, SelectedMode::INDICATOR };
    tabBarPattern_->indicatorStyles_ = { indicatorStyle1, indicatorStyle2 };

    /**
     * @tc.steps: step2. Test function HandleTouchEvent.
     * @tc.expected: Related function runs ok.
     */
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchLocationInfo.SetLocalLocation(Offset(1.0f, 1.0f));
    tabBarPattern_->tabItemOffsets_ = { { -1.0f, -1.0f }, { 1.0f, 1.0f }, { 2.0f, 2.0f } };
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->HandleTouchEvent(touchLocationInfo);
        touchLocationInfo.SetLocalLocation(Offset(-1.0f, -1.0f));
    }
    EXPECT_EQ(tabBarNode_->TotalChildCount(), 3);
    tabBarPattern_->touchingIndex_ = 1;
    touchLocationInfo.SetTouchType(TouchType::UP);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern_->HandleTouchEvent(touchLocationInfo);
                tabBarPattern_->touchingIndex_ = 1;
                touchLocationInfo.SetTouchType(TouchType::CANCEL);
            }
            touchLocationInfo.SetTouchType(TouchType::DOWN);
        }
        tabBarPattern_->touchingIndex_.reset();
    }
}

/**
 * @tc.name: TabBarPatternPlayTranslateAnimation001
 * @tc.desc: test PlayTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternPlayTranslateAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step2. Test function PlayTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    CreateWithItem([](TabsModelNG model) {});
    float startPos = 0.1f;
    float endPos = 0.2f;
    float targetCurrentOffset = 0.3f;
    auto offset = 0.1f;
    tabBarPattern_->currentOffset_ = offset;
    tabBarPattern_->PlayTranslateAnimation(startPos, endPos, targetCurrentOffset);
    EXPECT_FALSE(tabBarPattern_->indicatorAnimationIsRunning_);
    EXPECT_FALSE(tabBarPattern_->translateAnimationIsRunning_);
}

/**
 * @tc.name: TabBarPatternSetEdgeEffect002
 * @tc.desc: test SetEdgeEffect
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternSetEdgeEffect002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarPattern_->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>();

    /**
     * @tc.steps: step2. Test function SetEdgeEffect.
     * @tc.expected: Related function runs ok.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    tabBarPattern_->SetEdgeEffect(gestureHub);
}

/**
 * @tc.name: TabBarPatternPlayTabBarTranslateAnimation001
 * @tc.desc: test PlayTabBarTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternPlayTabBarTranslateAnimation001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });
    int32_t targetIndex = 1;
    tabBarPattern_->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>();
    tabBarNode_->GetGeometryNode()->SetFrameSize(SizeF(1.0f, 1.0f));
    tabBarPattern_->childrenMainSize_ = 0.1f;
    AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(targetIndex))
        ->GetGeometryNode()
        ->SetFrameSize(SizeF(0.0f, 0.0f));
    AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(targetIndex - 1))
        ->GetGeometryNode()
        ->SetFrameSize(SizeF(0.0f, 0.0f));
    int32_t nodeId = 1;
    for (int i = 0; i <= 2; i++) {
        auto frameNode_ = TabsModelNG::GetOrCreateTabsNode(
            V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
        tabBarNode_->AddChild(frameNode_);
    }
    AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(targetIndex + 1))
        ->GetGeometryNode()
        ->SetFrameSize(SizeF(0.0f, 0.0f));

    /**
     * @tc.steps: step2. Test function PlayTabBarTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */

    tabBarPattern_->PlayTabBarTranslateAnimation(targetIndex);
    EXPECT_FALSE(tabBarPattern_->tabBarTranslateAnimationIsRunning_);
}

void FocusTest(const RefPtr<TabBarLayoutProperty>& tabBarLayoutProperty, const RefPtr<TabBarPattern>& tabBarPattern)
{
    KeyEvent event;
    event.action = KeyAction::DOWN;

    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    event.code = KeyCode::KEY_DPAD_RIGHT;
    tabBarPattern->focusIndicator_ = 1;
    EXPECT_FALSE(tabBarPattern->OnKeyEvent(event));
    tabBarPattern->focusIndicator_ = 0;
    EXPECT_TRUE(tabBarPattern->OnKeyEvent(event));
    event.code = KeyCode::KEY_SPACE;
    EXPECT_TRUE(tabBarPattern->OnKeyEvent(event));
    event.code = KeyCode::KEY_DPAD_LEFT;
    tabBarPattern->focusIndicator_ = 0;
    EXPECT_FALSE(tabBarPattern->OnKeyEvent(event));
    tabBarPattern->focusIndicator_ = 1;
    EXPECT_TRUE(tabBarPattern->OnKeyEvent(event));
    event.code = KeyCode::KEY_ENTER;
    EXPECT_TRUE(tabBarPattern->OnKeyEvent(event));
    event.code = KeyCode::KEY_MOVE_HOME;
    tabBarPattern->focusIndicator_ = 1;
    EXPECT_TRUE(tabBarPattern->OnKeyEvent(event));
    event.code = KeyCode::KEY_MOVE_END;
    tabBarPattern->focusIndicator_ = 0;
    EXPECT_TRUE(tabBarPattern->OnKeyEvent(event));
    event.code = KeyCode::KEY_TAB;
    tabBarPattern->focusIndicator_ = 0;
    EXPECT_TRUE(tabBarPattern->OnKeyEvent(event));

    tabBarLayoutProperty->UpdateAxis(Axis::VERTICAL);
    event.code = KeyCode::KEY_DPAD_DOWN;
    tabBarPattern->focusIndicator_ = 1;
    EXPECT_FALSE(tabBarPattern->OnKeyEvent(event));
    tabBarPattern->focusIndicator_ = 0;
    EXPECT_TRUE(tabBarPattern->OnKeyEvent(event));
    event.code = KeyCode::KEY_DPAD_UP;
    tabBarPattern->focusIndicator_ = 0;
    EXPECT_FALSE(tabBarPattern->OnKeyEvent(event));
    tabBarPattern->focusIndicator_ = 1;
    EXPECT_TRUE(tabBarPattern->OnKeyEvent(event));
}

/**
 * @tc.name: TabBarPatternOnKeyEvent004
 * @tc.desc: test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternOnKeyEvent004, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::NOSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::NOSTYLE);
        }, 1);
    });
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->isFocusActive_ = true;

    /**
     * @tc.steps: steps2. OnKeyEvent
     * @tc.expected: steps2. Check the result of OnKeyEvent
     */
    KeyEvent event;
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_MOVE_HOME;
    tabBarPattern_->SetTabBarStyle(TabBarStyle::NOSTYLE);
    tabBarPattern_->focusIndicator_ = 1;
    EXPECT_TRUE(tabBarPattern_->OnKeyEvent(event));

    event.code = KeyCode::KEY_MOVE_END;
    tabBarPattern_->focusIndicator_ = 0;
    EXPECT_TRUE(tabBarPattern_->OnKeyEvent(event));

    layoutProperty_->UpdateTabBarPosition(BarPosition::START);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    FocusTest(tabBarLayoutProperty_, tabBarPattern_);
}

/**
 * @tc.name: TabBarPatternOnKeyEvent005
 * @tc.desc: test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternOnKeyEvent005, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::NOSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::NOSTYLE);
        }, 1);
    }, BarPosition::END);
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->isFocusActive_ = true;

    /**
     * @tc.steps: steps2. OnKeyEvent
     * @tc.expected: steps2. Check the result of OnKeyEvent
     */
    layoutProperty_->UpdateTabBarPosition(BarPosition::END);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    FocusTest(tabBarLayoutProperty_, tabBarPattern_);
}

/**
 * @tc.name: TabBarPatternOnKeyEvent006
 * @tc.desc: test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternOnKeyEvent006, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::NOSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::NOSTYLE);
        }, 1);
    }, BarPosition::END);
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->isFocusActive_ = true;

    /**
     * @tc.steps: steps2. OnKeyEvent
     * @tc.expected: steps2. Check the result of OnKeyEvent
     */
    layoutProperty_->UpdateTabBarPosition(BarPosition::END);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    tabBarPattern_->SetFirstFocus(true);
    FocusTest(tabBarLayoutProperty_, tabBarPattern_);
}

/**
 * @tc.name: TabBarPatternOnKeyEvent007
 * @tc.desc: test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternOnKeyEvent007, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::NOSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::NOSTYLE);
        }, 1);
    }, BarPosition::END);

    /**
     * @tc.steps: steps2. OnKeyEvent
     * @tc.expected: steps2. Check the result of OnKeyEvent
     */
    layoutProperty_->UpdateTabBarPosition(BarPosition::END);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    KeyEvent event;
    event.action = KeyAction::DOWN;
    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->isFocusActive_ = false;
    event.code = KeyCode::KEY_DPAD_RIGHT;
    tabBarPattern_->focusIndicator_ = 0;
    EXPECT_FALSE(tabBarPattern_->OnKeyEvent(event));

    pipeline->isFocusActive_ = true;
    event.code = KeyCode::KEY_A;
    tabBarPattern_->focusIndicator_ = 0;
    EXPECT_FALSE(tabBarPattern_->OnKeyEvent(event));
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
 * @tc.name: TabBarPatternAdjustFocusPosition001
 * @tc.desc: test AdjustFocusPosition
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternAdjustFocusPosition001, TestSize.Level1)
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
    tabBarPattern_->focusIndicator_ = 0;
    tabBarPattern_->AdjustFocusPosition();
    EXPECT_EQ(tabBarPattern_->GetTabBarStyle(), TabBarStyle::SUBTABBATSTYLE);
}

/**
 * @tc.name: TabBarPatternAdjustFocusPosition002
 * @tc.desc: test AdjustFocusPosition
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternAdjustFocusPosition002, TestSize.Level1)
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
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarPattern_->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    tabBarPattern_->tabItemOffsets_.clear();
    OffsetF c1(1.0f, 1.0f);
    OffsetF c2(100.0f, 100.0f);
    tabBarPattern_->tabItemOffsets_.emplace_back(c1);
    tabBarPattern_->tabItemOffsets_.emplace_back(c2);
    tabBarPattern_->focusIndicator_ = 0;
    tabBarPattern_->AdjustFocusPosition();
    EXPECT_EQ(tabBarPattern_->GetTabBarStyle(), TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern_->axis_ = Axis::VERTICAL;
    tabBarPattern_->focusIndicator_ = 0;
    tabBarPattern_->AdjustFocusPosition();
    EXPECT_EQ(tabBarPattern_->GetTabBarStyle(), TabBarStyle::SUBTABBATSTYLE);
}

/**
 * @tc.name: TabBarPatternCreateNodePaintMethod001
 * @tc.desc: test CreateNodePaintMethod
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternCreateNodePaintMethod001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    IndicatorStyle indicator;
    tabBarPattern_->SetIndicatorStyle(indicator, 0);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[0], indicator);
    SelectedMode selectedMode = SelectedMode::INDICATOR;
    tabBarPattern_->SetSelectedMode(selectedMode, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], selectedMode);

    /**
     * @tc.steps: steps2. CreateNodePaintMethod
     * @tc.expected: steps2. Check the result of CreateNodePaintMethod
     */
    auto tabBarRenderContext = tabBarNode_->GetRenderContext();
    tabBarRenderContext->UpdateBackgroundColor(Color::RED);
    auto paintMethod = tabBarPattern_->CreateNodePaintMethod();
    EXPECT_EQ(tabBarRenderContext->GetBackgroundColor().value(), Color::RED);
}

/**
 * @tc.name: TabsModelSetOnTabBarClick001
 * @tc.desc: Tabs SetOnTabBarClick
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelSetOnTabBarClick001, TestSize.Level1)
{
    /**
     * @tc.steps: steps2. SetOnTabBarClick
     * @tc.expected: steps2. Check the result of SetOnTabBarClick
     */
    CreateWithItem([](TabsModelNG model) {
        model.SetOnTabBarClick([](const BaseEventInfo* info) {});
        model.SetOnTabBarClick([](const BaseEventInfo* info) {});
    });
    EXPECT_NE(pattern_->onTabBarClickEvent_, nullptr);
    EXPECT_NE(pattern_->onTabBarClickEvent_, nullptr);
}

/**
 * @tc.name: TabBarPatternInitScrollable004
 * @tc.desc: test InitScrollable
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternInitScrollable004, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 1);
    });
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    tabBarLayoutProperty_->UpdateAxis(Axis::VERTICAL);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);

    /**
     * @tc.steps: step2. Test function InitScrollable.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern_->InitScrollable(gestureHub);
                ASSERT_NE(tabBarPattern_->scrollableEvent_, nullptr);
                auto scrollable = tabBarPattern_->scrollableEvent_->GetScrollable();
                scrollable->callback_(0.1, SCROLL_FROM_NONE);
                tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
                tabBarPattern_->axis_ = Axis::HORIZONTAL;
            }
            tabBarPattern_->axis_ = Axis::VERTICAL;
            tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
            tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }
        tabBarPattern_->tabItemOffsets_ = { { -1.0f, -1.0f } };
    }
    tabBarPattern_->axis_ = Axis::VERTICAL;
    tabBarPattern_->currentOffset_ = DEFAULT_OFFSET;
    auto scrollable = tabBarPattern_->scrollableEvent_->GetScrollable();
    scrollable->callback_(0.1, SCROLL_FROM_AXIS);
    scrollable->callback_(1.1, SCROLL_FROM_AXIS);
    EXPECT_EQ(tabBarPattern_->GetTabBarStyle(), TabBarStyle::BOTTOMTABBATSTYLE);
}

/**
 * @tc.name: TabBarPatternGetIndicatorStyle001
 * @tc.desc: test GetIndicatorStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternGetIndicatorStyle001, TestSize.Level1)
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
     * @tc.steps: steps2. GetIndicatorStyle
     * @tc.expected: steps2. Check the result of GetIndicatorStyle
     */
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    tabBarPattern_->isTouchingSwiper_ = true;
    tabBarPattern_->SetSelectedMode(SelectedMode::INDICATOR, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], SelectedMode::INDICATOR);
    tabBarPattern_->SetSelectedMode(SelectedMode::INDICATOR, 1);
    EXPECT_EQ(tabBarPattern_->selectedModes_[1], SelectedMode::INDICATOR);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    tabBarPattern_->swiperStartIndex_ = 0;
    IndicatorStyle indicator;
    tabBarPattern_->SetIndicatorStyle(indicator, 0);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[0], indicator);
    IndicatorStyle indicator1;
    indicator1.width = -1.0_vp;
    tabBarPattern_->SetIndicatorStyle(indicator1, 1);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[1], indicator1);
    tabBarPattern_->indicator_ = 0;
    tabBarPattern_->turnPageRate_ = -0.9f;
    IndicatorStyle indicator2;
    tabBarPattern_->GetIndicatorStyle(indicator2);
    indicator1.width = 1.0_vp;
    tabBarPattern_->SetIndicatorStyle(indicator1, 1);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[1], indicator1);
    tabBarPattern_->GetIndicatorStyle(indicator2);
    tabBarPattern_->indicator_ = 0;
    tabBarPattern_->turnPageRate_ = 0.9f;
    IndicatorStyle indicator3;
    tabBarPattern_->GetIndicatorStyle(indicator3);
    tabBarPattern_->SetIndicatorStyle(indicator3, 0);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[0], indicator3);
    tabBarPattern_->indicator_ = -1;
    tabBarPattern_->GetIndicatorStyle(indicator2);
    tabBarPattern_->SetIndicatorStyle(indicator1, 1);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[1], indicator1);
    tabBarPattern_->GetIndicatorStyle(indicator3);
    tabBarPattern_->SetIndicatorStyle(indicator3, 0);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[0], indicator3);
}

/**
 * @tc.name: TabBarPatternCheckSwiperDisable001
 * @tc.desc: test CheckSwiperDisable
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternCheckSwiperDisable001, TestSize.Level1)
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
     * @tc.steps: steps2. CheckSwiperDisable
     * @tc.expected: steps2. Check the result of CheckSwiperDisable
     */
    EXPECT_EQ(tabBarPattern_->CheckSwiperDisable(), false);
}

/**
 * @tc.name: TabBarPatternApplyTurnPageRateToIndicator001
 * @tc.desc: test ApplyTurnPageRateToIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternApplyTurnPageRateToIndicator001, TestSize.Level1)
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
     * @tc.steps: steps2. ApplyTurnPageRateToIndicator
     * @tc.expected: steps2. Check the result of ApplyTurnPageRateToIndicator
     */
    tabBarPattern_->SetSelectedMode(SelectedMode::INDICATOR, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], SelectedMode::INDICATOR);
    tabBarPattern_->SetSelectedMode(SelectedMode::INDICATOR, 1);
    EXPECT_EQ(tabBarPattern_->selectedModes_[1], SelectedMode::INDICATOR);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    tabBarPattern_->ApplyTurnPageRateToIndicator(0.0f);
    tabBarPattern_->ApplyTurnPageRateToIndicator(2.0f);
    tabBarPattern_->ApplyTurnPageRateToIndicator(-2.0f);
    EXPECT_EQ(tabBarPattern_->turnPageRate_, 0.0f);
    tabBarPattern_->swiperStartIndex_ = 0;
    tabBarPattern_->ApplyTurnPageRateToIndicator(0.9f);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 1);
    tabBarPattern_->ApplyTurnPageRateToIndicator(-0.9f);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    tabBarPattern_->ApplyTurnPageRateToIndicator(-0.9f);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);
}

/**
 * @tc.name: TabBarLayoutAlgorithmLayoutMask004
 * @tc.desc: Test the LayoutMask function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmLayoutMask004, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    tabBarLayoutProperty_->UpdateSelectedMask(0);
    tabBarLayoutProperty_->UpdateUnselectedMask(1);
    std::vector<OffsetF> childOffsetDelta = { OffsetF(), OffsetF() };
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarLayoutProperty_);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabBarLayoutAlgorithm));

    /**
     * @tc.steps: step2. build selectedMaskNode and unselectedMaskNode.
     */
    auto selectedmaskPosition = tabBarNode_->GetChildren().size() - TEST_SELECTED_MASK_COUNT;
    auto selectedMaskNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(selectedmaskPosition));
    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> selectedMaskLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(selectedMaskNode, geometryNode1, selectedMaskNode->GetLayoutProperty());
    layoutWrapper.AppendChild(selectedMaskLayoutWrapper);

    auto unselectedmaskPosition = tabBarNode_->GetChildren().size() - TEST_UNSELECTED_MASK_COUNT;
    auto unselectedMaskNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(unselectedmaskPosition));
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    auto unselectedProperty = unselectedMaskNode->GetLayoutProperty();
    RefPtr<LayoutWrapperNode> unselectedMaskLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(unselectedMaskNode, geometryNode2, unselectedProperty);
    layoutWrapper.AppendChild(unselectedMaskLayoutWrapper);

    /**
     * @tc.steps: steps3. Create a child named imageLayoutWrapper for currentWrapper.
     */
    auto currentWrapper = selectedMaskLayoutWrapper;
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    RefPtr<GeometryNode> geometryNode5 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> imageLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(imageNode, geometryNode5, imageNode->GetLayoutProperty());
    auto imageLayoutProperty = AceType::DynamicCast<ImageLayoutProperty>(imageLayoutWrapper->GetLayoutProperty());
    selectedMaskLayoutWrapper->AppendChild(imageLayoutWrapper);

    /**
     * @tc.steps: step4. call LayoutMask function.
     * @tc.expected: step4. expect The function is run ok.
     */
    tabBarLayoutAlgorithm->LayoutMask(&layoutWrapper, childOffsetDelta);
    EXPECT_EQ(tabBarLayoutProperty_->GetSelectedMask().value_or(-1), 0);
    EXPECT_EQ(tabBarLayoutProperty_->GetUnselectedMask().value_or(-1), 1);
}

/**
 * @tc.name: TabBarLayoutAlgorithmGetGridWidth001
 * @tc.desc: Test the GetGridWidth function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmGetGridWidth001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    tabBarPattern_->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarNode_->GetPattern<TabBarPattern>()->CreateLayoutAlgorithm());

    /**
     * @tc.steps: steps2. Create different conditions for GetGridWidth.
     */
    int32_t columns = -10;
    auto frameSize = SizeF(1.0f, 1.0f);
    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(tabBarNode_->GetLayoutProperty());
    BarGridColumnOptions option;
    float resultWidth1 = tabbarLayoutAlgorithm->GetGridWidth(option, frameSize, columns);
    columns = 10;
    float resultWidth2 = tabbarLayoutAlgorithm->GetGridWidth(option, frameSize, columns);

    /**
     * @tc.steps: steps3. GetGridWidth.
     * @tc.expected: steps3. expect The function is run ok.
     */
    EXPECT_EQ(resultWidth1, 0.0f);
    EXPECT_EQ(resultWidth2, columns * frameSize.Width() / XS_COLUMN_NUM);
}

/**
 * @tc.name: TabBarLayoutAlgorithmApplyBarGridAlign001
 * @tc.desc: Test the ApplyBarGridAlign function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmApplyBarGridAlign001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    tabBarPattern_->tabBarStyle_ = TabBarStyle::BOTTOMTABBATSTYLE;
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarNode_->GetPattern<TabBarPattern>()->CreateLayoutAlgorithm());
    auto tabBarProperty = tabBarLayoutProperty_;

    /**
     * @tc.steps: steps2. Create different conditions for ApplyBarGridAlign.
     */
    BarGridColumnOptions option;
    option.sm = 6;
    tabBarLayoutProperty_->UpdateBarGridAlign(option);
    auto frameSize = SizeF(400.0f, 400.0f);
    float result1 = tabbarLayoutAlgorithm->ApplyBarGridAlign(tabBarProperty, frameSize);
    option.md = 10;
    tabBarLayoutProperty_->UpdateBarGridAlign(option);
    frameSize = SizeF(800.0f, 800.0f);
    float result2 = tabbarLayoutAlgorithm->ApplyBarGridAlign(tabBarProperty, frameSize);
    option.lg = 16;
    tabBarLayoutProperty_->UpdateBarGridAlign(option);
    frameSize = SizeF(1000.0f, 1000.0f);
    float result3 = tabbarLayoutAlgorithm->ApplyBarGridAlign(tabBarProperty, frameSize);
    option.lg = -2;
    tabBarLayoutProperty_->UpdateBarGridAlign(option);
    float result4 = tabbarLayoutAlgorithm->ApplyBarGridAlign(tabBarProperty, frameSize);
    option.lg = 2;
    tabBarLayoutProperty_->UpdateBarGridAlign(option);
    float result5 = tabbarLayoutAlgorithm->ApplyBarGridAlign(tabBarProperty, frameSize);

    /**
     * @tc.steps: steps3. ApplyBarGridAlign.
     * @tc.expected: steps3. Cexpect The function is run ok.
     */
    EXPECT_EQ(result1, 0.0f);
    EXPECT_EQ(result2, 0.0f);
    EXPECT_EQ(result3, 0.0f);
    EXPECT_EQ(result4, 0.0f);
    float columnWidth = frameSize.Width() / LG_COLUMN_NUM;
    float expectedWidth = (LG_COLUMN_NUM - option.lg) * columnWidth / 2;
    EXPECT_EQ(NearEqual(result5, expectedWidth), true);
}

/**
 * @tc.name: TabBarLayoutAlgorithmConfigHorizontal001
 * @tc.desc: Test the ConfigHorizontal function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmConfigHorizontal001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarNode_->GetPattern<TabBarPattern>()->CreateLayoutAlgorithm());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabbarLayoutAlgorithm));
    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty());

    /**
     * @tc.steps: steps2. Create different input parameters.
     */
    layoutProperty->UpdateTabBarMode(TabBarMode::FIXED);
    int32_t childCount = 0;
    BarGridColumnOptions option;
    option.lg = 2;
    tabBarLayoutProperty_->UpdateBarGridAlign(option);
    auto frameSize = SizeF(1000.0f, 1000.0f);

    /**
     * @tc.steps: steps3. ConfigHorizontal.
     * @tc.expected: steps3. Check the results of ConfigHorizontal under different conditions.
     */
    tabbarLayoutAlgorithm->ConfigHorizontal(&layoutWrapper, frameSize, childCount);
    childCount = 1;
    layoutProperty->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    ScrollableBarModeOptions options;
    options.margin = 0.0_vp;
    options.nonScrollableLayoutStyle = LayoutStyle::ALWAYS_AVERAGE_SPLIT;
    tabBarLayoutProperty_->UpdateScrollableBarModeOptions(options);
    tabbarLayoutAlgorithm->ConfigHorizontal(&layoutWrapper, frameSize, childCount);
    options.nonScrollableLayoutStyle = LayoutStyle::SPACE_BETWEEN_OR_CENTER;
    tabBarLayoutProperty_->UpdateScrollableBarModeOptions(options);
    tabbarLayoutAlgorithm->ConfigHorizontal(&layoutWrapper, frameSize, childCount);
    options.nonScrollableLayoutStyle = LayoutStyle::ALWAYS_CENTER;
    tabBarLayoutProperty_->UpdateScrollableBarModeOptions(options);
    tabbarLayoutAlgorithm->childrenMainSize_ = 0.0f;
    tabbarLayoutAlgorithm->ConfigHorizontal(&layoutWrapper, frameSize, childCount);
    layoutProperty->UpdateBarAdaptiveHeight(true);
    tabbarLayoutAlgorithm->ConfigHorizontal(&layoutWrapper, frameSize, childCount);
    EXPECT_EQ(tabbarLayoutAlgorithm->scrollMargin_, 0.0f);
}

/**
 * @tc.name: TabBarLayoutAlgorithmHandleAlwaysAverageSplitLayoutStyle001
 * @tc.desc: Test the HandleAlwaysAverageSplitLayoutStyle function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmHandleAlwaysAverageSplitLayoutStyle001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarNode_->GetPattern<TabBarPattern>()->CreateLayoutAlgorithm());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabbarLayoutAlgorithm));
    auto frameSize = SizeF(20.0f, 20.0f);
    int32_t childCount = 2;
    tabbarLayoutAlgorithm->childrenMainSize_ = 10000.0f;
    tabbarLayoutAlgorithm->scrollMargin_ = 10000.0f;
    tabbarLayoutAlgorithm->itemWidths_.clear();
    tabbarLayoutAlgorithm->itemWidths_.emplace_back(0.0f);
    tabbarLayoutAlgorithm->itemWidths_.emplace_back(0.0f);
    tabbarLayoutAlgorithm->itemWidths_.emplace_back(0.0f);
    tabbarLayoutAlgorithm->HandleAlwaysAverageSplitLayoutStyle(&layoutWrapper, frameSize, childCount);

    /**
     * @tc.steps: steps2. HandleAlwaysAverageSplitLayoutStyle.
     * @tc.expected: steps2. Check itemWidths after HandleAlwaysAverageSplitLayoutStyle by using different itemWidths.
     */
    frameSize = SizeF(0.0f, 0.0f);
    tabbarLayoutAlgorithm->childrenMainSize_ = 0.0f;
    tabbarLayoutAlgorithm->itemWidths_.clear();

    float itemWidth = 1000.0f;
    tabbarLayoutAlgorithm->itemWidths_.emplace_back(itemWidth);
    tabbarLayoutAlgorithm->itemWidths_.emplace_back(itemWidth);
    tabbarLayoutAlgorithm->HandleAlwaysAverageSplitLayoutStyle(&layoutWrapper, frameSize, childCount);
    EXPECT_EQ(tabbarLayoutAlgorithm->itemWidths_[0], itemWidth);
    EXPECT_EQ(tabbarLayoutAlgorithm->itemWidths_[1], itemWidth);

    itemWidth = 10.0f;
    tabbarLayoutAlgorithm->itemWidths_.clear();
    tabbarLayoutAlgorithm->itemWidths_.emplace_back(itemWidth);
    tabbarLayoutAlgorithm->itemWidths_.emplace_back(itemWidth);
    tabbarLayoutAlgorithm->HandleAlwaysAverageSplitLayoutStyle(&layoutWrapper, frameSize, childCount);
    EXPECT_EQ(tabbarLayoutAlgorithm->itemWidths_[0], itemWidth);
    EXPECT_EQ(tabbarLayoutAlgorithm->itemWidths_[1], itemWidth);

    itemWidth = 0.0f;
    tabbarLayoutAlgorithm->itemWidths_.clear();
    tabbarLayoutAlgorithm->itemWidths_.emplace_back(itemWidth);
    tabbarLayoutAlgorithm->itemWidths_.emplace_back(itemWidth);
    tabbarLayoutAlgorithm->HandleAlwaysAverageSplitLayoutStyle(&layoutWrapper, frameSize, childCount);
    EXPECT_EQ(tabbarLayoutAlgorithm->itemWidths_[0], itemWidth);
    EXPECT_EQ(tabbarLayoutAlgorithm->itemWidths_[1], itemWidth);
}

/**
 * @tc.name: TabBarLayoutAlgorithmHandleSpaceBetweenOrCenterLayoutStyle001
 * @tc.desc: Test the HandleSpaceBetweenOrCenterLayoutStyle function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmHandleSpaceBetweenOrCenterLayoutStyle001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarNode_->GetPattern<TabBarPattern>()->CreateLayoutAlgorithm());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabbarLayoutAlgorithm));
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);
    auto layoutProperty = tabBarLayoutProperty_;
    int32_t childCount = 2;

    /**
     * @tc.steps: steps2. Create two children for layoutWrapper.
     */
    auto tabBarNode_test = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode_test, nullptr);
    RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> tabBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode_test, geometryNode3, tabBarNode_test->GetLayoutProperty());
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(tabBarLayoutWrapper);
    auto tabBarNode_test1 = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode_test1, nullptr);
    RefPtr<GeometryNode> geometryNode4 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> tabBarLayoutWrapper1 =
        AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode_test1, geometryNode4, tabBarNode_test1->GetLayoutProperty());
    tabBarLayoutWrapper1->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    tabBarLayoutWrapper1->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(tabBarLayoutWrapper1);

    /**
     * @tc.steps: steps3.  Create a padding and assign it an initial value.
     */
    PaddingProperty padding;
    padding.left = CalcLength(20.0_vp);
    padding.right = CalcLength(20.0_vp);
    padding.top = CalcLength(20.0_vp);
    padding.bottom = CalcLength(20.0_vp);
    layoutProperty->UpdatePadding(padding);

    /**
     * @tc.steps: steps4.  Create different conditions for entering a branch for HandleSpaceBetweenOrCenterLayoutStyle.
     */
    tabbarLayoutAlgorithm->childrenMainSize_ = 100000.0f;
    auto frameSize = SizeF(150.0f, 150.0f);
    tabbarLayoutAlgorithm->HandleSpaceBetweenOrCenterLayoutStyle(&layoutWrapper, frameSize, childCount);
    tabbarLayoutAlgorithm->itemWidths_.clear();
    tabbarLayoutAlgorithm->itemWidths_.emplace_back(0.0f);
    tabbarLayoutAlgorithm->itemWidths_.emplace_back(2.0f);
    tabbarLayoutAlgorithm->childrenMainSize_ = 149.5f;
    tabbarLayoutAlgorithm->scrollMargin_ = 1.0f;
    tabbarLayoutAlgorithm->HandleSpaceBetweenOrCenterLayoutStyle(&layoutWrapper, frameSize, childCount);
    tabbarLayoutAlgorithm->childrenMainSize_ = 10.0f;
    tabbarLayoutAlgorithm->scrollMargin_ = 2.0f;
    tabbarLayoutAlgorithm->HandleSpaceBetweenOrCenterLayoutStyle(&layoutWrapper, frameSize, childCount);

    /**
     * @tc.steps: steps5. HandleSpaceBetweenOrCenterLayoutStyle.
     * @tc.expected: steps5. Check the result of childrenMainSize.
     */
    EXPECT_EQ(tabbarLayoutAlgorithm->childrenMainSize_, 6.0f);
}

/**
 * @tc.name: TabBarLayoutAlgorithmMeasureItemWidths001
 * @tc.desc: Test the MeasureItemWidths function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmMeasureItemWidths001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarNode_->GetPattern<TabBarPattern>()->CreateLayoutAlgorithm());

    /**
     * @tc.steps: steps2. Create a child for layoutWrapper.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabbarLayoutAlgorithm));
    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty());
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);
    auto columnNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> columnLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode, geometryNode2, columnNode->GetLayoutProperty());
    columnLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    columnLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(columnLayoutWrapper);

    /**
     * @tc.steps: steps3. Create a first child named imageLayoutWrapper for columnLayoutWrapper.
     */
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    RefPtr<GeometryNode> geometryNode5 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> imageLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(imageNode, geometryNode5, imageNode->GetLayoutProperty());
    auto imageLayoutProperty = AceType::DynamicCast<ImageLayoutProperty>(imageLayoutWrapper->GetLayoutProperty());
    columnLayoutWrapper->AppendChild(imageLayoutWrapper);

    /**
     * @tc.steps: steps4. Create a second child named textLayoutWrapper for columnLayoutWrapper.
     */
    auto linearLayoutProperty = AceType::DynamicCast<LinearLayoutProperty>(columnLayoutWrapper->GetLayoutProperty());
    auto textId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, textId, AceType::MakeRefPtr<TextPattern>());
    RefPtr<GeometryNode> geometryNode4 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> textLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textNode, geometryNode4, textNode->GetLayoutProperty());
    columnLayoutWrapper->AppendChild(textLayoutWrapper);
    int32_t childCount = 3;
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 1);
    tabbarLayoutAlgorithm->scrollMargin_ = 0.0f;

    /**
     * @tc.steps: steps5.MeasureItemWidths.
     * @tc.expected: steps5. Testing childrenMainSize under MeasureItemWidths Value of.
     */
    tabbarLayoutAlgorithm->MeasureItemWidths(&layoutWrapper, childCount);
    EXPECT_EQ(tabbarLayoutAlgorithm->childrenMainSize_, 0.0f);
}

/**
 * @tc.name: TabBarLayoutAlgorithmMeasureMaxHeight001
 * @tc.desc: Test the MeasureMaxHeight function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmMeasureMaxHeight001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarNode_->GetPattern<TabBarPattern>()->CreateLayoutAlgorithm());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabbarLayoutAlgorithm));
    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty());
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);
    tabbarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;

    /**
     * @tc.steps: steps2. Set itemWidths_ Clear and reassign and
     *                    Create two children named columnLayoutWrapper using a loop for layoutWrapper.
     */
    tabbarLayoutAlgorithm->itemWidths_.clear();
    tabbarLayoutAlgorithm->itemWidths_.emplace_back(10.0f);
    for (int32_t i = 0; i < 2; i++) {
        auto columnNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
            RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
        RefPtr<LayoutWrapperNode> columnLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(columnNode, geometryNode2, columnNode->GetLayoutProperty());
        columnLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
        columnLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
        layoutWrapper.AppendChild(columnLayoutWrapper);
    }

    /**
     * @tc.steps: steps3.MeasureMaxHeight.
     * @tc.expected: steps3. Test itemWidths under MeasureMaxHeight Value of.
     */
    int32_t childCount = 2;
    tabbarLayoutAlgorithm->itemWidths_.emplace_back(2.0f);
    tabbarLayoutAlgorithm->MeasureMaxHeight(&layoutWrapper, childCount);
    EXPECT_EQ(tabbarLayoutAlgorithm->itemWidths_[0], 10.0f);
}

/**
 * @tc.name: TabBarLayoutAlgorithmApplyLayoutMode001
 * @tc.desc: Test the ApplyLayoutMode function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmApplyLayoutMode001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarNode_->GetPattern<TabBarPattern>()->CreateLayoutAlgorithm());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabbarLayoutAlgorithm));
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);
    auto bottomTabBarStyle = tabBarPattern_->GetBottomTabBarStyle(0);

    /**
     * @tc.steps: steps2. Create two children named columnLayoutWrapper and columnLayoutWrapper1 for layoutWrapper.
     */
    auto columnNode1 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> columnLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode1, geometryNode3, columnNode1->GetLayoutProperty());
    columnLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    columnLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(columnLayoutWrapper);
    auto columnNode2 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    RefPtr<GeometryNode> geometryNode4 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> columnLayoutWrapper1 =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode2, geometryNode4, columnNode2->GetLayoutProperty());
    columnLayoutWrapper1->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    columnLayoutWrapper1->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(columnLayoutWrapper1);
    auto linearLayoutProperty = AceType::DynamicCast<LinearLayoutProperty>(columnLayoutWrapper->GetLayoutProperty());

    /**
     * @tc.steps: steps3. Using a loop to create two children named textLayoutWrapper for columnLayoutWrapper.
     */
    for (int32_t i = 0; i < 2; i++) {
        auto textId = ElementRegister::GetInstance()->MakeUniqueId();
        auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, textId, AceType::MakeRefPtr<TextPattern>());
        RefPtr<GeometryNode> geometryNode5 = AceType::MakeRefPtr<GeometryNode>();
        RefPtr<LayoutWrapperNode> textLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(textNode, geometryNode5, textNode->GetLayoutProperty());
        columnLayoutWrapper->AppendChild(textLayoutWrapper);
    }
    float allocatedWidth = 0.0f;
    int32_t childCount = 2;

    /**
     * @tc.steps: steps4. ApplyLayoutMode.
     * @tc.expected: steps4. Create different conditions and check the result of ApplyLayoutMode.
     */
    bottomTabBarStyle.layoutMode = LayoutMode::VERTICAL;
    tabBarPattern_->SetBottomTabBarStyle(bottomTabBarStyle, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabbarLayoutAlgorithm->ApplyLayoutMode(&layoutWrapper, allocatedWidth, childCount);
    bottomTabBarStyle.layoutMode = LayoutMode::AUTO;
    tabBarPattern_->SetBottomTabBarStyle(bottomTabBarStyle, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 1);
    tabbarLayoutAlgorithm->ApplyLayoutMode(&layoutWrapper, allocatedWidth, childCount);
    allocatedWidth = 200000.0f;
    tabbarLayoutAlgorithm->ApplyLayoutMode(&layoutWrapper, allocatedWidth, childCount);
    EXPECT_FALSE(linearLayoutProperty->IsVertical());
}

/**
 * @tc.name: TabBarLayoutAlgorithmLayoutChildren001
 * @tc.desc: Test the LayoutChildren function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmLayoutChildren001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();

    /**
     * @tc.steps: steps2. Create padding and assign initial values to it.
     */
    PaddingProperty padding;
    padding.left = CalcLength(200.0_vp);
    padding.right = CalcLength(200.0_vp);
    padding.top = CalcLength(200.0_vp);
    padding.bottom = CalcLength(200.0_vp);
    tabBarLayoutProperty_->UpdatePadding(padding);
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabbarLayoutAlgorithm));
    layoutWrapper.currentChildCount_ = 5;
    auto frameSize = SizeF(0.0f, 0.0f);
    auto axis = Axis::HORIZONTAL;
    tabbarLayoutAlgorithm->childrenMainSize_ = 10000.0f;
    OffsetF childOffset(0.0f, 0.0f);
    tabbarLayoutAlgorithm->LayoutChildren(&layoutWrapper, frameSize, axis, childOffset);

    /**
     * @tc.steps: steps3. LayoutChildren.
     * @tc.expected: steps3. Verify childrenMainSize under LayoutChildren Value of.
     */
    EXPECT_EQ(tabbarLayoutAlgorithm->tabItemOffset_[0].GetX(), childOffset.GetX());
    EXPECT_EQ(tabbarLayoutAlgorithm->tabItemOffset_[0].GetY(), childOffset.GetY());
}

/**
 * @tc.name: TabBarLayoutAlgorithmGetContentWidth001
 * @tc.desc: Test the GetContentWidth function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmGetContentWidth001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    tabBarPattern_->tabBarStyle_ = TabBarStyle::BOTTOMTABBATSTYLE;
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    auto layoutProperty = tabBarLayoutProperty_;
    auto frameSize = SizeF(0.0f, 0.0f);

    /**
     * @tc.steps: steps2. Create padding and assign initial values to it.
     */
    PaddingProperty padding;
    padding.left = CalcLength(200.0_vp);
    padding.right = CalcLength(200.0_vp);
    padding.top = CalcLength(200.0_vp);
    padding.bottom = CalcLength(200.0_vp);

    /**
     * @tc.steps: steps3. GetContentWidth.
     * @tc.expected: steps3. Check the result of GetContentWidth.
     */
    layoutProperty->UpdatePadding(padding);
    float resultWidth = tabbarLayoutAlgorithm->GetContentWidth(layoutProperty, frameSize);
    EXPECT_EQ(resultWidth, 0.0f);
}

/**
 * @tc.name: TabBarLayoutAlgorithmApplySymmetricExtensible001
 * @tc.desc: Test the ApplySymmetricExtensible function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmApplySymmetricExtensible001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabBarLayoutAlgorithm));
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    /**
     * @tc.steps: steps2. Create three children named columnLayoutWrapper1, columnLayoutWrapper2,
     *                    and columnLayoutWrapper3 for layoutWrapper in sequence.
     */
    auto columnNode1 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> columnLayoutWrapper1 =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode1, geometryNode2, columnNode1->GetLayoutProperty());
    columnLayoutWrapper1->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    columnLayoutWrapper1->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(columnLayoutWrapper1);
    auto linearLayoutProperty = AceType::DynamicCast<LinearLayoutProperty>(columnLayoutWrapper1->GetLayoutProperty());
    auto columnNode2 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> columnLayoutWrapper2 =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode2, geometryNode3, columnNode2->GetLayoutProperty());
    columnLayoutWrapper2->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    columnLayoutWrapper2->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(columnLayoutWrapper2);
    auto columnNode3 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    RefPtr<GeometryNode> geometryNode7 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> columnLayoutWrapper3 =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode3, geometryNode7, columnNode3->GetLayoutProperty());
    columnLayoutWrapper3->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    columnLayoutWrapper3->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(columnLayoutWrapper3);

    /**
     * @tc.steps: steps3. Test ApplySymmetricExtensible by using different conditions.
     */
    float allocatedWidth = 0.0f;
    int32_t childCount = 1;
    tabBarLayoutAlgorithm->itemWidths_.clear();
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(1000.0f);
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(2000.0f);
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(3000.0f);
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth, childCount);
    EXPECT_NE(tabBarLayoutAlgorithm->itemWidths_.size(), 1);
    tabBarLayoutAlgorithm->itemWidths_.clear();
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(1000.0f);
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth, childCount);
    EXPECT_EQ(tabBarLayoutAlgorithm->itemWidths_.size(), 1);
    childCount = 3;
    tabBarLayoutAlgorithm->itemWidths_.clear();
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(1000.0f);
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(2000.0f);
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(3000.0f);
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth, childCount);
    EXPECT_EQ(tabBarLayoutAlgorithm->itemWidths_.size(), 3);
    tabBarLayoutAlgorithm->itemWidths_.clear();
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(1000.0f);
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth, childCount);
    EXPECT_EQ(tabBarLayoutAlgorithm->itemWidths_.size(), 1);
    tabBarLayoutAlgorithm->itemWidths_.clear();
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(1000.0f);
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(2000.0f);
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(3000.0f);

    /**
     * @tc.steps: steps4. ApplySymmetricExtensible.
     * @tc.expected: steps4. Check the result of ApplySymmetricExtensible.
     */
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth, childCount);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    linearLayoutProperty->UpdateFlexDirection(FlexDirection::ROW_REVERSE);
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth, childCount);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    linearLayoutProperty->UpdateFlexDirection(FlexDirection::COLUMN);
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth, childCount);
    allocatedWidth = 100000.0f;
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth, childCount);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    linearLayoutProperty->UpdateFlexDirection(FlexDirection::COLUMN);
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth, childCount);
    EXPECT_EQ(tabBarLayoutAlgorithm->itemWidths_[0], allocatedWidth);
}

/**
 * @tc.name: TabBarLayoutAlgorithmCalculateItemWidthsForSymmetricExtensible001
 * @tc.desc: Test the CalculateItemWidthsForSymmetricExtensible function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmCalculateItemWidthsForSymmetricExtensible001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabBarLayoutAlgorithm));
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    /**
     * @tc.steps: steps2. Create a child for layoutWrapper.
     */
    auto columnNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> columnLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode, geometryNode2, columnNode->GetLayoutProperty());
    columnLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    columnLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(columnLayoutWrapper);

    /**
     * @tc.steps: steps3. Create a first child named imageLayoutWrapper for columnLayoutWrapper.
     */
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    RefPtr<GeometryNode> geometryNode5 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> imageLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(imageNode, geometryNode5, imageNode->GetLayoutProperty());
    auto imageLayoutProperty = AceType::DynamicCast<ImageLayoutProperty>(imageLayoutWrapper->GetLayoutProperty());
    columnLayoutWrapper->AppendChild(imageLayoutWrapper);

    /**
     * @tc.steps: steps4. Create a second child named textLayoutWrapper for columnLayoutWrapper.
     */
    auto linearLayoutProperty = AceType::DynamicCast<LinearLayoutProperty>(columnLayoutWrapper->GetLayoutProperty());
    auto textId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, textId, AceType::MakeRefPtr<TextPattern>());
    RefPtr<GeometryNode> geometryNode4 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> textLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textNode, geometryNode4, textNode->GetLayoutProperty());
    columnLayoutWrapper->AppendChild(textLayoutWrapper);

    float allocatedWidth = 0.0f;
    int32_t childCount = 2;

    /**
     * @tc.steps: steps5. Test CalculateItemWidthsForSymmetricExtensible by using different conditions.
     */
    tabBarLayoutAlgorithm->itemWidths_.clear();
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(10.0f);
    std::vector<float> spaceRequests;
    spaceRequests.clear();
    spaceRequests.emplace_back(10.0f);
    std::vector<float> leftBuffers;
    leftBuffers.clear();
    leftBuffers.emplace_back(10.0f);
    std::vector<float> rightBuffers;
    rightBuffers.clear();
    rightBuffers.emplace_back(10.0f);
    tabBarLayoutAlgorithm->CalculateItemWidthsForSymmetricExtensible(
        &layoutWrapper, childCount, spaceRequests, leftBuffers, rightBuffers, allocatedWidth);
    tabBarLayoutAlgorithm->itemWidths_.clear();
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(100.0f);
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(100.0f);
    spaceRequests.clear();
    spaceRequests.emplace_back(100.0f);
    spaceRequests.emplace_back(100.0f);
    leftBuffers.clear();
    leftBuffers.emplace_back(100.0f);
    leftBuffers.emplace_back(100.0f);
    rightBuffers.clear();
    rightBuffers.emplace_back(100.0f);
    rightBuffers.emplace_back(100.0f);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarLayoutAlgorithm->CalculateItemWidthsForSymmetricExtensible(
        &layoutWrapper, childCount, spaceRequests, leftBuffers, rightBuffers, allocatedWidth);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 1);
    tabBarLayoutAlgorithm->CalculateItemWidthsForSymmetricExtensible(
        &layoutWrapper, childCount, spaceRequests, leftBuffers, rightBuffers, allocatedWidth);
    spaceRequests.clear();
    spaceRequests.emplace_back(0.0f);
    spaceRequests.emplace_back(0.0f);
    leftBuffers.clear();
    leftBuffers.emplace_back(100.0f);
    leftBuffers.emplace_back(100.0f);
    rightBuffers.clear();
    rightBuffers.emplace_back(100.0f);
    rightBuffers.emplace_back(100.0f);
    tabBarLayoutAlgorithm->CalculateItemWidthsForSymmetricExtensible(
        &layoutWrapper, childCount, spaceRequests, leftBuffers, rightBuffers, allocatedWidth);
    leftBuffers.clear();
    leftBuffers.emplace_back(0.0f);
    leftBuffers.emplace_back(0.0f);
    rightBuffers.clear();
    rightBuffers.emplace_back(0.0f);
    rightBuffers.emplace_back(0.0f);

    /**
     * @tc.steps: steps6. CalculateItemWidthsForSymmetricExtensible.
     * @tc.expected: steps6. erify itemWidths in CalculateItemWidthsForSymmetricExtensible Value of.
     */
    tabBarLayoutAlgorithm->CalculateItemWidthsForSymmetricExtensible(
        &layoutWrapper, childCount, spaceRequests, leftBuffers, rightBuffers, allocatedWidth);
    EXPECT_EQ(tabBarLayoutAlgorithm->itemWidths_[0], 0.0f);
}

/**
 * @tc.name: TabBarPaintMethodGetForegroundDrawFunction002
 * @tc.desc: Test the GetForegroundDrawFunction function in the TabBarPaintMethod class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPaintMethodGetForegroundDrawFunction002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    IndicatorStyle indicator;
    tabBarPattern_->SetIndicatorStyle(indicator, 0);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[0], indicator);
    SelectedMode selectedMode = SelectedMode::INDICATOR;
    tabBarPattern_->SetSelectedMode(selectedMode, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], selectedMode);
    auto paintMethod = tabBarPattern_->CreateNodePaintMethod();
    auto paintMethod2 = tabBarPattern_->CreateNodePaintMethod();
    auto geometryNode = tabBarNode_->GetGeometryNode();

    /**
     * @tc.steps: steps2. Create padding and assign initial values to it.
     */
    MarginPropertyF padding;
    padding.left = 20.0f;
    padding.right = 20.0f;
    padding.top = 20.0f;
    padding.bottom = 20.0f;
    geometryNode->UpdatePaddingWithBorder(padding);
    PaintWrapper paintWrapper(tabBarNode_->GetRenderContext(), geometryNode, tabBarPaintProperty_);
    auto drawFunction = paintMethod->GetForegroundDrawFunction(&paintWrapper);
    tabBarPaintProperty_->UpdateFadingEdge(false);

    /**
     * @tc.steps: steps3. GetForegroundDrawFunction.
     * @tc.expected: steps3. expect The function is run ok.
     */
    EXPECT_FALSE(tabBarPaintProperty_->GetFadingEdgeValue());
    PaintWrapper paintWrapper2(tabBarNode_->GetRenderContext(), tabBarNode_->GetGeometryNode(), tabBarPaintProperty_);
    drawFunction = paintMethod->GetForegroundDrawFunction(&paintWrapper2);
    ASSERT_EQ(drawFunction, nullptr);
    auto clone = tabBarPaintProperty_->Clone();
    EXPECT_NE(clone, nullptr);
}

/**
 * @tc.name: TabBarLayoutAlgorithmHandleAlwaysAverageSplitLayoutStyle002
 * @tc.desc: Test the HandleAlwaysAverageSplitLayoutStyle function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmHandleAlwaysAverageSplitLayoutStyle002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabbarLayoutAlgorithm));
    auto frameSize = SizeF(3000.0f, 3000.0f);
    tabbarLayoutAlgorithm->scrollMargin_ = 0.0f;
    int32_t childCount = 1;

    /**
     * @tc.steps: steps2. HandleAlwaysAverageSplitLayoutStyle.
     * @tc.expected: steps2. Check itemWidths in CalculateItemWidthsForSymmetricExtensible Value of.
     */
    tabbarLayoutAlgorithm->childrenMainSize_ = 0.0f;
    tabbarLayoutAlgorithm->itemWidths_.clear();
    tabbarLayoutAlgorithm->itemWidths_.emplace_back(0.0f);
    tabbarLayoutAlgorithm->HandleAlwaysAverageSplitLayoutStyle(&layoutWrapper, frameSize, childCount);
    EXPECT_EQ(tabbarLayoutAlgorithm->itemWidths_[0], 3000.0f);
}

/**
 * @tc.name: TabContentModelSetPadding001
 * @tc.desc: Test the SetPadding function in the TabContentModel class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelSetPadding001, TestSize.Level1)
{
    /**
     * @tc.steps: steps2. Create padding and assign initial values to it.
     */
    PaddingProperty padding;
    padding.left = CalcLength(20.0_vp);
    padding.right = CalcLength(20.0_vp);
    padding.top = CalcLength(20.0_vp);
    padding.bottom = CalcLength(20.0_vp);
    Create([=](TabsModelNG model) {
        CreateSingleItem([=](TabContentModelNG tabContentModel) {
            tabContentModel.SetPadding(padding);
        }, 0);
    });
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();

    /**
     * @tc.steps: steps3. SetPadding.
     * @tc.expected: steps3. Check if the setting value for padding was successful.
     */
    EXPECT_EQ(tabContentPattern->GetPadding().left, padding.left);
    EXPECT_EQ(tabContentPattern->GetPadding().right, padding.right);
    EXPECT_EQ(tabContentPattern->GetPadding().top, padding.top);
    EXPECT_EQ(tabContentPattern->GetPadding().bottom, padding.bottom);
}

/**
 * @tc.name: TabContentModelSetLayoutMode001
 * @tc.desc: Test the SetLayoutMode function in the TabContentModel class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelSetLayoutMode001, TestSize.Level1)
{
    LayoutMode layoutMode = LayoutMode::AUTO;
    Create([=](TabsModelNG model) {
        CreateSingleItem([=](TabContentModelNG tabContentModel) {
            tabContentModel.SetLayoutMode(layoutMode);
        }, 0);
    });
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();

    /**
     * @tc.steps: steps2. SetLayoutMode.
     * @tc.expected: steps2. Check if the value set for layoutMode was successful.
     */
    EXPECT_EQ(tabContentPattern->GetBottomTabBarStyle().layoutMode, layoutMode);
}

/**
 * @tc.name: TabContentModelSetVerticalAlign001
 * @tc.desc: Test the SetVerticalAlign function in the TabContentModel class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelSetVerticalAlign001, TestSize.Level1)
{
    FlexAlign verticalAlign = FlexAlign::CENTER;
    Create([=](TabsModelNG model) {
        CreateSingleItem([=](TabContentModelNG tabContentModel) {
            tabContentModel.SetVerticalAlign(verticalAlign);
        }, 0);
    });
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();

    /**
     * @tc.steps: steps2. SetVerticalAlign.
     * @tc.expected: steps2. Check if the value set for verticalAlign was successful.
     */
    EXPECT_EQ(tabContentPattern->GetBottomTabBarStyle().verticalAlign, verticalAlign);
}

/**
 * @tc.name: TabContentModelSetSymmetricExtensible001
 * @tc.desc: Test the SetSymmetricExtensible function in the TabContentModel class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelSetSymmetricExtensible001, TestSize.Level1)
{
    bool isExtensible = true;
    Create([=](TabsModelNG model) {
        CreateSingleItem([=](TabContentModelNG tabContentModel) {
            tabContentModel.SetSymmetricExtensible(isExtensible);
        }, 0);
    });
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();

    /**
     * @tc.steps: steps2. SetSymmetricExtensible.
     * @tc.expected: steps2. Check the result of SetSymmetricExtensible.
     */
    EXPECT_EQ(tabContentPattern->GetBottomTabBarStyle().symmetricExtensible, isExtensible);
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
 * @tc.name: TabBarPatternAdjustFocusPosition003
 * @tc.desc: Test the AdjustFocusPosition function in the TabBarPattern class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternAdjustFocusPosition003, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 1);
    }, BarPosition::END);
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarPattern_->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    tabBarPattern_->tabItemOffsets_.clear();
    OffsetF c1(0.0f, 0.0f);
    OffsetF c2(10.0f, 10.0f);
    tabBarPattern_->tabItemOffsets_.emplace_back(c1);
    tabBarPattern_->tabItemOffsets_.emplace_back(c2);
    tabBarPattern_->focusIndicator_ = 0;
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    auto geometryNode = tabBarNode_->GetGeometryNode();

    /**
     * @tc.steps: steps2. Create padding and assign initial values to it.
     */
    MarginPropertyF padding;
    padding.left = 10000.0f;
    padding.right = 10000.0f;
    padding.top = 10000.0f;
    padding.bottom = 10000.0f;
    geometryNode->UpdatePaddingWithBorder(padding);

    /**
     * @tc.steps: steps3. AdjustFocusPosition.
     * @tc.expected: steps3. Check the value of TabBarStyle under the AdjustFocusPosition function.
     */
    tabBarPattern_->AdjustFocusPosition();
    EXPECT_EQ(tabBarPattern_->currentOffset_, padding.left);
}

/**
 * @tc.name: TabsModelSetBarAdaptiveHeight001
 * @tc.desc: Test the SetBarAdaptiveHeight function in the TabsModel class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelSetBarAdaptiveHeight001, TestSize.Level1)
{
    /**
     * @tc.steps: steps2. SetBarAdaptiveHeight.
     * @tc.expected: steps2. Check the result of SetBarAdaptiveHeight.
     */
    CreateWithItem([](TabsModelNG model) {
        model.SetBarAdaptiveHeight(false);
    });
    EXPECT_TRUE(tabBarLayoutProperty_->GetBarAdaptiveHeight());
}

/**
 * @tc.name: TabsModelSetScrollableBarModeOptions001
 * @tc.desc: Test the SetScrollableBarModeOptions function in the TabsModel class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelSetScrollableBarModeOptions001, TestSize.Level1)
{
    /**
     * @tc.steps: steps2. SetScrollableBarModeOptions.
     * @tc.expected: steps2. Check if the SetScrollableBarModeOptions function successfully sets
     *                       ScrollableBarModeOptions.
     */
    ScrollableBarModeOptions option;
    option.margin = 0.0_vp;
    option.nonScrollableLayoutStyle = LayoutStyle::ALWAYS_CENTER;
    CreateWithItem([option](TabsModelNG model) {
        model.SetScrollableBarModeOptions(option);
    });
    EXPECT_EQ(tabBarLayoutProperty_->GetScrollableBarModeOptions(), option);
}

/**
 * @tc.name: TabsModelSetBarGridAlign001
 * @tc.desc: Test the SetBarGridAlign function in the TabsModel class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelSetBarGridAlign001, TestSize.Level1)
{
    /**
     * @tc.steps: steps2. Create BarGridColumnOptions and assign them initial values.
     */
    BarGridColumnOptions BarGridColumnOptions;
    BarGridColumnOptions.sm = -1;
    BarGridColumnOptions.md = -1;
    BarGridColumnOptions.lg = -1;
    BarGridColumnOptions.gutter = 0.0_vp;
    BarGridColumnOptions.margin = 0.0_vp;
    CreateWithItem([BarGridColumnOptions](TabsModelNG model) {
        model.SetBarGridAlign(BarGridColumnOptions);
    });

    /**
     * @tc.steps: steps3. SetBarGridAlign.
     * @tc.expected: steps3. Check if the SetBarGridAlign function has successfully set BarGridColumnOptions.
     */
    EXPECT_EQ(tabBarLayoutProperty_->GetBarGridAlign(), BarGridColumnOptions);
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
    frameNode_->ToJsonValue(json);
    options.nonScrollableLayoutStyle = LayoutStyle::SPACE_BETWEEN_OR_CENTER;
    tabBarLayoutProperty_->UpdateScrollableBarModeOptions(options);
    frameNode_->ToJsonValue(json);
    options.nonScrollableLayoutStyle = LayoutStyle::ALWAYS_CENTER;
    tabBarLayoutProperty_->UpdateScrollableBarModeOptions(options);
    frameNode_->ToJsonValue(json);

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
 * @tc.name: TabBarLayoutAlgorithmApplySymmetricExtensible002
 * @tc.desc: Test the ApplySymmetricExtensible function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmApplySymmetricExtensible002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabBarLayoutAlgorithm));
    tabBarLayoutAlgorithm->itemWidths_.clear();
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(1000.0f);
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(2000.0f);
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(3000.0f);
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    /**
     * @tc.steps: steps2. Create three children for layoutWrapper in sequence.
     */
    auto columnNode1 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> columnLayoutWrapper1 =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode1, geometryNode2, columnNode1->GetLayoutProperty());
    columnLayoutWrapper1->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    columnLayoutWrapper1->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(columnLayoutWrapper1);
    auto columnNode2 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> columnLayoutWrapper2 =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode2, geometryNode3, columnNode2->GetLayoutProperty());
    columnLayoutWrapper2->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    columnLayoutWrapper2->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(columnLayoutWrapper2);
    auto columnNode3 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    RefPtr<GeometryNode> geometryNode7 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> columnLayoutWrapper3 =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode3, geometryNode7, columnNode3->GetLayoutProperty());
    columnLayoutWrapper3->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    columnLayoutWrapper3->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(columnLayoutWrapper3);
    auto linearLayoutProperty = AceType::DynamicCast<LinearLayoutProperty>(columnLayoutWrapper1->GetLayoutProperty());

    /**
     * @tc.steps: steps3. ApplySymmetricExtensible.
     * @tc.expected: steps3. Check the value of itemWidths under the ApplySymmetricExtensible function.
     */
    float allocatedWidth = 0.0f;
    int32_t childCount = 3;
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth, childCount);
    EXPECT_EQ(tabBarLayoutAlgorithm->itemWidths_[0], 0.0f);
}

/**
 * @tc.name: TabBarLayoutAlgorithmAdjustFixedItem001
 * @tc.desc: Test the AdjustFixedItem function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmAdjustFixedItem001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabBarLayoutAlgorithm));
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);
    auto axis = Axis::HORIZONTAL;
    auto frameSize = OptionalSizeF(0.0f, 0.0f);

    /**
     * @tc.steps: step2. Create a child named childwrapper for layoutWrapper.
     */
    auto columnNode1 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> childWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode1, geometryNode2, columnNode1->GetLayoutProperty());
    childWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    childWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(childWrapper);

    /**
     * @tc.steps: steps3. AdjustFixedItem.
     * @tc.expected: steps3. Check the result of AdjustFixedItem.
     */
    childWrapper->GetGeometryNode()->SetFrameSize(SizeF(10000.0f, 10000.0f));
    tabBarLayoutAlgorithm->AdjustFixedItem(childWrapper, frameSize, axis);
    axis = Axis::VERTICAL;
    tabBarLayoutAlgorithm->AdjustFixedItem(childWrapper, frameSize, axis);
    EXPECT_EQ(childWrapper->GetGeometryNode()->GetFrameSize(), SizeF(0.0f, 0.0f));
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
 * @tc.name: TabBarLayoutAlgorithmCalculateItemWidthsForSymmetricExtensible002
 * @tc.desc: Test the CalculateItemWidthsForSymmetricExtensible function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmCalculateItemWidthsForSymmetricExtensible002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabBarLayoutAlgorithm));
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    /**
     * @tc.steps: steps2. Create a child for layoutWrapper.
     */
    auto columnNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> columnLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode, geometryNode2, columnNode->GetLayoutProperty());
    columnLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    columnLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(columnLayoutWrapper);

    /**
     * @tc.steps: steps3. Create a first child named imageLayoutWrapper for columnLayoutWrapper.
     */
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    RefPtr<GeometryNode> geometryNode5 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> imageLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(imageNode, geometryNode5, imageNode->GetLayoutProperty());
    auto imageLayoutProperty = AceType::DynamicCast<ImageLayoutProperty>(imageLayoutWrapper->GetLayoutProperty());
    columnLayoutWrapper->AppendChild(imageLayoutWrapper);

    /**
     * @tc.steps: steps4. Create a second child named textLayoutWrapper for columnLayoutWrapper.
     */
    auto linearLayoutProperty = AceType::DynamicCast<LinearLayoutProperty>(columnLayoutWrapper->GetLayoutProperty());
    auto textId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, textId, AceType::MakeRefPtr<TextPattern>());
    RefPtr<GeometryNode> geometryNode4 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> textLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textNode, geometryNode4, textNode->GetLayoutProperty());
    columnLayoutWrapper->AppendChild(textLayoutWrapper);

    /**
     * @tc.steps: steps5. Test CalculateItemWidthsForSymmetricExtensible by using different conditions.
     */
    float allocatedWidth = 100.0f;
    int32_t childCount = 2;
    std::vector<float> spaceRequests;
    std::vector<float> leftBuffers;
    std::vector<float> rightBuffers;
    tabBarLayoutAlgorithm->itemWidths_.clear();
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(100.0f);
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(100.0f);
    spaceRequests.clear();
    spaceRequests.emplace_back(100.0f);
    spaceRequests.emplace_back(100.0f);
    leftBuffers.clear();
    leftBuffers.emplace_back(100.0f);
    leftBuffers.emplace_back(100.0f);
    rightBuffers.clear();
    rightBuffers.emplace_back(100.0f);
    rightBuffers.emplace_back(100.0f);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 1);
    tabBarLayoutAlgorithm->CalculateItemWidthsForSymmetricExtensible(
        &layoutWrapper, childCount, spaceRequests, leftBuffers, rightBuffers, allocatedWidth);
    spaceRequests.clear();
    spaceRequests.emplace_back(0.0f);
    spaceRequests.emplace_back(0.0f);
    leftBuffers.clear();
    leftBuffers.emplace_back(10.0f);
    leftBuffers.emplace_back(10.0f);
    rightBuffers.clear();
    rightBuffers.emplace_back(30.0f);
    rightBuffers.emplace_back(30.0f);
    linearLayoutProperty->UpdateFlexDirection(FlexDirection::ROW);

    /**
     * @tc.steps: steps6. CalculateItemWidthsForSymmetricExtensible.
     * @tc.expected: steps6. Check the value of itemWidths in the CalculateItemWidthsForSymmetricExtensible function.
     */
    tabBarLayoutAlgorithm->CalculateItemWidthsForSymmetricExtensible(
        &layoutWrapper, childCount, spaceRequests, leftBuffers, rightBuffers, allocatedWidth);
    EXPECT_EQ(tabBarLayoutAlgorithm->itemWidths_[0], 60.0f);
}

/**
 * @tc.name: TabBarOnAttachToMainTree001.
 * @tc.desc: Test the OnAttachToMainTree function in the TabContentNode class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarOnAttachToMainTree001, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            LabelStyle labelStyle;
            tabContentModel.SetLabelStyle(labelStyle);
        }, 0);
    });
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();

    /**
     * @tc.steps: step2. Invoke OnAttachToMainTree.
     */
    tabContentFrameNode->OnAttachToMainTree(true);
    EXPECT_FALSE(tabContentFrameNode->useOffscreenProcess_);
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
 * @tc.name: TabsModelSetAnimationDuration002
 * @tc.desc: test SetAnimationDuration
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelSetAnimationDuration002, TestSize.Level1)
{
    float duration = 1;
    CreateWithItem([duration](TabsModelNG model) {
        model.SetAnimationDuration(duration);
    });
    EXPECT_FLOAT_EQ(duration, 1);

    /**
     * @tc.steps: step2. Test function SetAnimationDuration.
     * @tc.expected: Related function runs ok.
     */
    duration = -1;
    CreateWithItem([duration](TabsModelNG model) {
        model.SetAnimationDuration(duration);
    });
    EXPECT_FLOAT_EQ(duration, -1);
}

/**
 * @tc.name: TabsModelSetAnimationDuration003
 * @tc.desc: test SetAnimationDuration
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelSetAnimationDuration003, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto pipeline = PipelineContext::GetCurrentContext();
    auto tabTheme = pipeline->GetTheme<TabTheme>();
    auto defaultDuration = tabTheme->GetTabContentAnimationDuration();

    /**
     * @tc.steps: step2. Test function SetAnimationDuration in APIVersion 10.
     * @tc.expected: Related function runs ok.
     */
    pipeline->SetMinPlatformVersion(PLATFORM_VERSION_10);
    ASSERT_FALSE(tabBarPattern_->GetAnimationDuration().has_value());
    tabBarPattern_->animationDuration_.reset();
    tabBarPattern_->SetAnimationDuration(1);
    EXPECT_FLOAT_EQ(tabBarPattern_->GetAnimationDuration().value_or(-1), 1);
    tabBarPattern_->animationDuration_.reset();
    tabBarPattern_->SetAnimationDuration(-1);
    EXPECT_FLOAT_EQ(tabBarPattern_->GetAnimationDuration().value_or(-1), defaultDuration);
    tabBarPattern_->animationDuration_.reset();

    /**
     * @tc.steps: step3. Test function SetAnimationDuration in APIVersion 11.
     * @tc.expected: Related function runs ok.
     */
    pipeline->SetMinPlatformVersion(PLATFORM_VERSION_11);
    EXPECT_FLOAT_EQ(tabBarPattern_->GetAnimationDuration().value_or(-1), defaultDuration);
    tabBarPattern_->animationDuration_.reset();
    tabBarPattern_->SetAnimationDuration(1);
    EXPECT_FLOAT_EQ(tabBarPattern_->GetAnimationDuration().value_or(-1), 1);
    tabBarPattern_->animationDuration_.reset();
    tabBarPattern_->SetAnimationDuration(-1);
    EXPECT_FLOAT_EQ(tabBarPattern_->GetAnimationDuration().value_or(-1), defaultDuration);
    tabBarPattern_->animationDuration_.reset();

    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    EXPECT_FLOAT_EQ(tabBarPattern_->GetAnimationDuration().value_or(-1), 0);
    tabBarPattern_->animationDuration_.reset();
    tabBarPattern_->SetAnimationDuration(1);
    EXPECT_FLOAT_EQ(tabBarPattern_->GetAnimationDuration().value_or(-1), 1);
    tabBarPattern_->animationDuration_.reset();
    tabBarPattern_->SetAnimationDuration(-1);
    EXPECT_FLOAT_EQ(tabBarPattern_->GetAnimationDuration().value_or(-1), 0);
    tabBarPattern_->animationDuration_.reset();
}

/**
 * @tc.name: SetOnChangeEvent002.
 * @tc.desc: Test the SetOnChangeEvent function in the TabsPattern class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, SetOnChangeEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */

    Color color = Color::RED;
    TabsItemDivider divider;
    divider.color = color;
    CreateWithItem([divider](TabsModelNG model) {
        model.SetDivider(divider);
    });

    /**
     * @tc.steps: step2. set different conditions and invoke SetOnChangeEvent.
     * @tc.expected: step2. related function is called.
     */
    pattern_->onIndexChangeEvent_ = nullptr;
    pattern_->SetOnIndexChangeEvent([](const BaseEventInfo* info) {});
    swiperPattern_->FireChangeEvent();
    tabBarPattern_->isMaskAnimationByCreate_ = true;
    swiperPattern_->FireChangeEvent();
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    swiperPattern_->FireChangeEvent();
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    swiperPattern_->FireChangeEvent();
    EXPECT_EQ(tabBarLayoutProperty_->GetAxisValue(Axis::HORIZONTAL), Axis::HORIZONTAL);
    tabBarPattern_->changeByClick_ = true;
    swiperPattern_->FireChangeEvent();
    pattern_->SetOnTabBarClickEvent([](const BaseEventInfo* info) {});
    auto onTabBarClickEvent = pattern_->GetTabBarClickEvent();
    (*onTabBarClickEvent)(1);
    EXPECT_NE(pattern_->onTabBarClickEvent_, nullptr);
}

/**
 * @tc.name: TabBarPatternGetInnerFocusPaintRect001
 * @tc.desc: test GetInnerFocusPaintRect
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternGetInnerFocusPaintRect001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});

    /**
     * @tc.steps: step2. Test function InitOnKeyEvent.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern_->tabBarStyle_ = TabBarStyle::BOTTOMTABBATSTYLE;
    tabBarPattern_->isFirstFocus_ = true;
    auto event = KeyEvent();
    auto paintRect = RoundRect();
    tabBarPattern_->GetInnerFocusPaintRect(paintRect);
    EXPECT_TRUE(tabBarPattern_->isFirstFocus_);
}

/**
 * @tc.name: TabBarPatternInitScrollable005
 * @tc.desc: test InitScrollable
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternInitScrollable005, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    tabBarLayoutProperty_->UpdateAxis(Axis::VERTICAL);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);

    /**
     * @tc.steps: step2. Test function InitScrollable in different conditons.
     * @tc.expected: Related function is called.
     */

    tabBarPattern_->InitScrollable(gestureHub);
    ASSERT_NE(tabBarPattern_->scrollableEvent_, nullptr);
    auto scrollable = tabBarPattern_->scrollableEvent_->GetScrollable();
    scrollable->callback_(0.1, SCROLL_FROM_NONE);
    scrollable->callback_(0.1, SCROLL_FROM_NONE);
    ASSERT_NE(tabBarPattern_->scrollableEvent_, nullptr);
    scrollable->callback_(0.1, SCROLL_FROM_NONE);
    tabBarPattern_->scrollableEvent_->scrollable_ = nullptr;
    scrollable->callback_(0.1, SCROLL_FROM_NONE);
    EXPECT_EQ(tabBarPattern_->scrollableEvent_->scrollable_, nullptr);
}

/**
 * @tc.name: TabsModelNGSetIndex001
 * @tc.desc: Test the SetIndex function in the TabsModelNG class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelNGSetIndex001, TestSize.Level2)
{
    /**
     * @tc.steps: steps2. GetScrollableBarModeOptions.
     * @tc.expected: steps2. Check the result of GetScrollableBarModeOptions.
     */
    CreateWithItem([](TabsModelNG model) {});
    swiperLayoutProperty_->UpdateIndex(1);
    EXPECT_EQ(swiperNode_->TotalChildCount(), 4);
    CreateWithItem([](TabsModelNG model) {}, BarPosition::START, 1);
    EXPECT_EQ(swiperNode_->TotalChildCount(), 4);
}

/*
 * @tc.name: TabBarPatternCalculateSelectedIndex001
 * @tc.desc: test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternCalculateSelectedIndex001, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
    auto info = MouseInfo();
    Offset s1(0.1, 0.1);
    Offset s2(0.4, 0.4);
    OffsetF c0(0.0f, 0.0f);
    OffsetF c1(0.1f, 0.1f);
    OffsetF c2(0.2f, 0.2f);
    OffsetF c3(0.3f, 0.3f);
    OffsetF c4(0.4f, 0.4f);
    info.SetLocalLocation(s1);
    /**
     * @tc.steps: step2. Test function HandleMouseEvent.
     * @tc.expected: Related function runs ok.
     */

    tabBarPattern_->hoverIndex_.emplace(1);
    tabBarPattern_->tabItemOffsets_ = { c1, c2, c3, c4 };
    tabBarPattern_->axis_ = Axis::VERTICAL;
    tabBarPattern_->isRTL_ = true;
    tabBarPattern_->CalculateSelectedIndex(info.GetLocalLocation());
    EXPECT_TRUE(tabBarPattern_->isRTL_);
    tabBarPattern_->tabItemOffsets_ = { c0, c2, c3, c4 };
    tabBarPattern_->CalculateSelectedIndex(info.GetLocalLocation());
    EXPECT_EQ(tabBarPattern_->CalculateSelectedIndex(info.GetLocalLocation()), -1);
}

/**
 * @tc.name: TabBarPatternGetIndicatorStyle002
 * @tc.desc: test GetIndicatorStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternGetIndicatorStyle002, TestSize.Level1)
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
     * @tc.steps: steps2. GetIndicatorStyle
     * @tc.expected: steps2. Check the result of GetIndicatorStyle
     */
    tabBarPattern_->indicatorStyles_.clear();
    IndicatorStyle indicator;
    IndicatorStyle indicator2;
    tabBarPattern_->indicator_ = -1;
    tabBarPattern_->GetIndicatorStyle(indicator);
    EXPECT_EQ(tabBarPattern_->indicator_, -1);
    tabBarPattern_->indicator_ = 0;
    tabBarPattern_->GetIndicatorStyle(indicator);
    tabBarPattern_->indicatorStyles_.push_back(indicator2);
    tabBarPattern_->indicatorStyles_.push_back(indicator);
    tabBarPattern_->GetIndicatorStyle(indicator);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
    indicator.width.SetValue(1.0);
    tabBarPattern_->GetIndicatorStyle(indicator);
    EXPECT_EQ(indicator.width.Value(), 10);
    tabBarPattern_->isTouchingSwiper_ = false;
    tabBarPattern_->GetIndicatorStyle(indicator);
    tabBarPattern_->axis_ = Axis::FREE;
    tabBarPattern_->GetIndicatorStyle(indicator);
    EXPECT_EQ(tabBarPattern_->axis_, Axis::FREE);
    tabBarPattern_->isTouchingSwiper_ = true;
    tabBarPattern_->GetIndicatorStyle(indicator);
    EXPECT_TRUE(tabBarPattern_->isTouchingSwiper_);
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    tabBarPattern_->GetIndicatorStyle(indicator);
    EXPECT_EQ(tabBarPattern_->axis_, Axis::HORIZONTAL);
    tabBarPattern_->turnPageRate_ = 2.0f;
    tabBarPattern_->GetIndicatorStyle(indicator);
    EXPECT_EQ(tabBarPattern_->turnPageRate_, 1.0f);
    tabBarPattern_->swiperStartIndex_ = 1;
    tabBarPattern_->GetIndicatorStyle(indicator);
    EXPECT_EQ(tabBarPattern_->swiperStartIndex_, 1);
    tabBarPattern_->swiperStartIndex_ = 1;
    auto tabBarStyles1 = TabBarStyle::NOSTYLE;
    auto tabBarStyles2 = TabBarStyle::SUBTABBATSTYLE;
    tabBarPattern_->tabBarStyles_ = { tabBarStyles1, tabBarStyles2 };
    tabBarPattern_->GetIndicatorStyle(indicator);
    EXPECT_EQ(tabBarPattern_->swiperStartIndex_, 1);
    tabBarPattern_->swiperStartIndex_ = -1;
    tabBarPattern_->GetIndicatorStyle(indicator);
    EXPECT_EQ(tabBarPattern_->swiperStartIndex_, -1);
}

/**
 * @tc.name: TabBarPatternOnModifyDone002
 * @tc.desc: test OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternOnModifyDone002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarLayoutProperty_->UpdateAxis(Axis::VERTICAL);
    /**
     * @tc.steps: step2. Test function FocusIndexChange.
     * @tc.expected: Related functions run ok.
     */
    tabBarPattern_->OnModifyDone();
    auto layoutProperty = tabBarLayoutProperty_;
    EXPECT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarPattern_->OnModifyDone();
    tabBarNode_->eventHub_ = AceType::MakeRefPtr<EventHub>();
    tabBarNode_->eventHub_->focusHub_ = AceType::MakeRefPtr<FocusHub>(tabBarNode_->eventHub_);
    ASSERT_NE(tabBarNode_->eventHub_->focusHub_, nullptr);
    tabBarPattern_->OnModifyDone();
    tabBarPattern_->swiperController_->removeTabBarEventCallback_();
    tabBarPattern_->swiperController_->addTabBarEventCallback_();
    EXPECT_NE(tabBarPattern_->swiperController_, nullptr);
}

/**
 * @tc.name: TabBarPatternIsAtBottom001
 * @tc.desc: test OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternIsAtBottom001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);

    /**
     * @tc.steps: step2. Test function IsAtBottom001.
     * @tc.expected: Related functions run ok.
     */
    tabBarPattern_->tabItemOffsets_.clear();
    tabBarPattern_->IsAtBottom();
    EXPECT_FALSE(tabBarPattern_->IsAtBottom());
}

/**
 * @tc.name: TabBarPatternApplyTurnPageRateToIndicator002
 * @tc.desc: test ApplyTurnPageRateToIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternApplyTurnPageRateToIndicator002, TestSize.Level1)
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
     * @tc.steps: steps2. ApplyTurnPageRateToIndicator
     * @tc.expected: steps2. Check the result of ApplyTurnPageRateToIndicator
     */
    tabBarPattern_->swiperStartIndex_ = 0;
    auto tabBarStyles1 = TabBarStyle::NOSTYLE;
    auto tabBarStyles2 = TabBarStyle::SUBTABBATSTYLE;
    auto selectedMode1 = SelectedMode::INDICATOR;
    auto selectedMode2 = SelectedMode::BOARD;
    tabBarPattern_->tabBarStyles_.clear();
    tabBarPattern_->tabBarStyles_.push_back(tabBarStyles2);
    tabBarPattern_->selectedModes_.clear();
    tabBarPattern_->selectedModes_.push_back(selectedMode1);
    tabBarPattern_->ApplyTurnPageRateToIndicator(0.0f);
    EXPECT_EQ(tabBarPattern_->swiperStartIndex_, -1);
    tabBarPattern_->selectedModes_.clear();
    tabBarPattern_->selectedModes_.push_back(selectedMode2);
    tabBarPattern_->ApplyTurnPageRateToIndicator(0.0f);
    tabBarPattern_->swiperStartIndex_ = 1;
    tabBarPattern_->ApplyTurnPageRateToIndicator(0.0f);
    tabBarPattern_->tabBarStyles_.push_back(tabBarStyles1);
    tabBarPattern_->ApplyTurnPageRateToIndicator(0.0f);
    tabBarPattern_->swiperStartIndex_ = 2;
    tabBarPattern_->ApplyTurnPageRateToIndicator(0.0f);
    tabBarPattern_->swiperStartIndex_ = -1;
    tabBarPattern_->ApplyTurnPageRateToIndicator(0.0f);
    EXPECT_EQ(tabBarPattern_->swiperStartIndex_, -1);
}

/**
 * @tc.name: TabBarPatternApplyTurnPageRateToIndicator003
 * @tc.desc: test ApplyTurnPageRateToIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternApplyTurnPageRateToIndicator003, TestSize.Level1)
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
     * @tc.steps: steps2. ApplyTurnPageRateToIndicator
     * @tc.expected: steps2. Check the result of ApplyTurnPageRateToIndicator
     */
    tabBarPattern_->swiperStartIndex_ = 0;
    auto tabBarStyles1 = TabBarStyle::SUBTABBATSTYLE;
    auto tabBarStyles2 = TabBarStyle::NOSTYLE;
    auto selectedMode1 = SelectedMode::INDICATOR;
    auto selectedMode2 = SelectedMode::BOARD;
    tabBarPattern_->tabBarStyles_.clear();
    tabBarPattern_->tabBarStyles_.push_back(tabBarStyles1);
    tabBarPattern_->selectedModes_.clear();
    tabBarPattern_->selectedModes_.push_back(selectedMode1);
    tabBarPattern_->ApplyTurnPageRateToIndicator(0.0f);
    EXPECT_EQ(tabBarPattern_->swiperStartIndex_, -1);
    tabBarPattern_->swiperStartIndex_ = 0;
    tabBarPattern_->tabBarStyles_.push_back(tabBarStyles2);
    tabBarPattern_->ApplyTurnPageRateToIndicator(0.0f);
    tabBarPattern_->swiperStartIndex_ = 0;
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    tabBarPattern_->selectedModes_.push_back(selectedMode2);
    tabBarPattern_->ApplyTurnPageRateToIndicator(0.0f);
    EXPECT_EQ(tabBarPattern_->swiperStartIndex_, 0);

    /**
     * @tc.steps: steps3. ApplyTurnPageRateToIndicator
     * @tc.expected: steps3. Check the result of ApplyTurnPageRateToIndicator
     */

    tabBarPattern_->swiperStartIndex_ = 0;
    auto tabBarStyles3 = TabBarStyle::SUBTABBATSTYLE;
    auto selectedMode3 = SelectedMode::INDICATOR;
    tabBarPattern_->tabBarStyles_.clear();
    tabBarPattern_->tabBarStyles_.push_back(tabBarStyles3);
    tabBarPattern_->selectedModes_.clear();
    tabBarPattern_->selectedModes_.push_back(selectedMode3);
    tabBarPattern_->ApplyTurnPageRateToIndicator(-0.5f);
    EXPECT_EQ(tabBarPattern_->swiperStartIndex_, -1);
    tabBarPattern_->swiperStartIndex_ = 0;
    tabBarPattern_->ApplyTurnPageRateToIndicator(-0.7f);
    EXPECT_EQ(tabBarPattern_->swiperStartIndex_, -1);
    tabBarPattern_->swiperStartIndex_ = 0;
    tabBarPattern_->turnPageRate_ = 0.5f;
    tabBarPattern_->ApplyTurnPageRateToIndicator(-0.7f);
    EXPECT_EQ(tabBarPattern_->swiperStartIndex_, -1);
    tabBarPattern_->swiperStartIndex_ = 0;
    tabBarPattern_->turnPageRate_ = 0.5f;
    tabBarPattern_->ApplyTurnPageRateToIndicator(-0.5f);
    EXPECT_EQ(tabBarPattern_->swiperStartIndex_, -1);
}

/**
 * @tc.name: TabBarPatternInitTurnPageRateEvent001
 * @tc.desc: test InitTurnPageRateEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternInitTurnPageRateEvent001, TestSize.Level1)
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
     * @tc.steps: steps2. InitTurnPageRateEvent
     * @tc.expected: steps2. Check the result of InitTurnPageRateEvent
     */

    tabBarPattern_->InitTurnPageRateEvent();
    int32_t testswipingIndex = 1;
    float testturnPageRate = 1.0f;
    tabBarPattern_->swiperController_->turnPageRateCallback_(testswipingIndex, testturnPageRate);
    AnimationCallbackInfo info;
    (*(tabBarPattern_->animationEndEvent_))(testswipingIndex, info);
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    tabBarPattern_->isTouchingSwiper_ = true;
    tabBarPattern_->swiperController_->turnPageRateCallback_(testswipingIndex, testturnPageRate);
    tabBarPattern_->turnPageRate_ = 1.0f;
    tabBarPattern_->swiperController_->turnPageRateCallback_(testswipingIndex, testturnPageRate);
    tabBarPattern_->turnPageRate_ = 0.5f;
    tabBarPattern_->swiperController_->turnPageRateCallback_(testswipingIndex, testturnPageRate);
}

/**
 * @tc.name: TabBarPatternUpdateIndicator002
 * @tc.desc: test UpdateIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternUpdateIndicator002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        model.SetFadingEdge(true);
    });
    EXPECT_TRUE(tabBarPaintProperty_->GetFadingEdgeValue());

    /**
     * @tc.steps: steps2. UpdateIndicator
     * @tc.expected: steps2. Check the result of UpdateIndicator
     */
    tabBarPattern_->indicator_ = 0;
    auto tabBarStyle1 = TabBarStyle::NOSTYLE;
    tabBarPattern_->tabBarStyles_.clear();
    tabBarPattern_->tabBarStyles_.push_back(tabBarStyle1);
    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern_->isTouchingSwiper_ = true;
    tabBarPattern_->UpdateIndicator(0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarPattern_->UpdateIndicator(0);
    tabBarPattern_->isTouchingSwiper_ = false;
    tabBarPattern_->UpdateIndicator(0);
}

/**
 * @tc.name: TabsModelPop001
 * @tc.desc: test SetDivider
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelPop001, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 1);
    }, BarPosition::END);
    tabBarNode_->eventHub_ = AceType::MakeRefPtr<EventHub>();
    tabBarNode_->eventHub_->focusHub_ = AceType::MakeRefPtr<FocusHub>(tabBarNode_->eventHub_);
    ASSERT_NE(tabBarNode_->eventHub_->focusHub_, nullptr);
    tabBarPattern_->OnModifyDone();
    tabBarPattern_->swiperController_->removeTabBarEventCallback_();
    tabBarPattern_->swiperController_->addTabBarEventCallback_();
    EXPECT_NE(tabBarPattern_->swiperController_, nullptr);
}

/**
 * @tc.name: TabContentModelCreate2(std::function<void()>&& deepRenderFunc)
 * @tc.desc: Test Create(std::function<void()>&& deepRenderFunc)
 * @tc.type：FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelCreate002, TestSize.Level1)
{
    TabContentModelNG tabContentModel;
    auto deepRenderFunc = []() { AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>()); };
    tabContentModel.Create(deepRenderFunc);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();

    TabsModelNG Mode1NG;
    Mode1NG.Create(BarPosition::END, 0, nullptr, nullptr);
    tabContentPattern->shallowBuilder_->deepRenderFunc_();
}

/**
 * @tc.name: TabsModelGetOrCreateTabsNode002
 * @tc.desc: test GetOrCreateTabsNode
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelGetOrCreateTabsNode002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */

    TabsModelNG tabsModel;
    const std::string tag = "TabsID";
    int32_t nodeId = 1;

    /**
     * @tc.steps: step2. Test function TabsModelGetOrCreateTabsNode.
     * @tc.expected: Related function runs ok.
     */
    auto frameNode = TabsModelNG::GetOrCreateTabsNode(tag, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto tabsNode2 =
        TabsModelNG::GetOrCreateTabsNode("TabsID2", nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
    ASSERT_NE(tabsNode2, nullptr);
}

/**
 * @tc.name: TabBarPatternOnRestoreInfo001
 * @tc.desc: Test the TabBarPatternOnRestoreInfo
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternOnRestoreInfo001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});

    /**
     * @tc.steps: step2. Set Indicator.
     * @tc.expected: Function ProvideRestoreInfo is called.
     */
    tabBarPattern_->UpdateIndicator(0);
    std::string ret = tabBarPattern_->ProvideRestoreInfo();
    EXPECT_TRUE(ret == R"({"Index":0})");

    /**
     * @tc.steps: step3. Function OnRestoreInfo is called.
     * @tc.expected: Passing invalid & valid JSON format.
     */
    std::string restoreInfo_ = R"({"Index":0})";
    auto info = JsonUtil::ParseJsonString(restoreInfo_);
    auto jsonIsOn = info->GetValue("Index");
    tabBarPattern_->SetTabBarStyle(TabBarStyle::NOSTYLE, 0);
    pattern_->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(tabBarLayoutProperty_->GetIndicator().value_or(0), 0);
    tabBarPattern_->SetAnimationDuration(1);
    pattern_->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(tabBarLayoutProperty_->GetIndicator().value_or(0), 0);
    tabBarPattern_->swiperController_ = nullptr;
    pattern_->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(tabBarLayoutProperty_->GetIndicator().value_or(0), 0);
    auto columnNode1 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    columnNode1->MountToParent(tabBarNode_);
    auto columnNode2 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    columnNode2->MountToParent(tabBarNode_);
    pattern_->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(tabBarLayoutProperty_->GetIndicator().value_or(0), 0);
}

/**
 * @tc.name: TabBarPatternInitTurnPageRateEvent002
 * @tc.desc: test InitTurnPageRateEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternInitTurnPageRateEvent002, TestSize.Level1)
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
     * @tc.steps: steps2. InitTurnPageRateEvent
     * @tc.expected: steps2. Check the result of InitTurnPageRateEvent
     */

    tabBarPattern_->InitTurnPageRateEvent();
    int32_t testswipingIndex = 1;
    float testturnPageRate = 1.0f;
    tabBarPattern_->swiperController_->turnPageRateCallback_(testswipingIndex, testturnPageRate);
    AnimationCallbackInfo info;
    (*(tabBarPattern_->animationEndEvent_))(testswipingIndex, info);
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    tabBarPattern_->isTouchingSwiper_ = true;
    tabBarPattern_->swiperController_->turnPageRateCallback_(testswipingIndex, testturnPageRate);
    tabBarPattern_->axis_ = Axis::VERTICAL;
    tabBarPattern_->isTouchingSwiper_ = false;
    tabBarPattern_->swiperController_->turnPageRateCallback_(testswipingIndex, testturnPageRate);
    tabBarPattern_->axis_ = Axis::VERTICAL;
    tabBarPattern_->isTouchingSwiper_ = true;
    tabBarPattern_->swiperController_->turnPageRateCallback_(testswipingIndex, testturnPageRate);
    tabBarPattern_->turnPageRate_ = 2.0f;
    (*(tabBarPattern_->animationEndEvent_))(testswipingIndex, info);
    tabBarPattern_->turnPageRate_ = 1.0f;
    (*(tabBarPattern_->animationEndEvent_))(testswipingIndex, info);
    tabBarPattern_->turnPageRate_ = 0.0f;
    (*(tabBarPattern_->animationEndEvent_))(testswipingIndex, info);
    tabBarPattern_->turnPageRate_ = -1.0f;
    (*(tabBarPattern_->animationEndEvent_))(testswipingIndex, info);
}

/**
 * @tc.name: TabBarPatternOnDirtyLayoutWrapperSwap002
 * @tc.desc: test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternOnDirtyLayoutWrapperSwap002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        model.SetFadingEdge(true);
    });
    auto layoutAlgorithm = tabBarPattern_->CreateLayoutAlgorithm();
    DirtySwapConfig config;
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode_, tabBarNode_->GetGeometryNode(), tabBarLayoutProperty_);
    auto algorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm, false, false);
    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper->GetLayoutProperty());

    layoutWrapper->SetLayoutAlgorithm(algorithmWrapper);
    EXPECT_EQ(layoutWrapper->layoutAlgorithm_, algorithmWrapper);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);

    /**
     * @tc.steps: step2. creat different conditions and invoke OnDirtyLayoutWrapperSwap.
     * @tc.expected: step2. expect The function is run ok.
     */
    config.skipMeasure = false;
    tabBarPattern_->isTouchingSwiper_ = true;
    layoutProperty->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarPattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_TRUE(tabBarPattern_->isTouchingSwiper_);
}

/**
 * @tc.name: TabBarPatternSetEdgeEffect003
 * @tc.desc: test SetEdgeEffect
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternSetEdgeEffect003, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);

    /**
     * @tc.steps: step2. Test function SetEdgeEffect.
     * @tc.expected: Related function runs ok.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    tabBarPattern_->SetEdgeEffect(gestureHub);
}

/**
 * @tc.name: TabBarLayoutAlgorithmUpdateChildConstraint002
 * @tc.desc: test UpdateChildConstraint
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmUpdateChildConstraint002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build tabBarNode_ and ideaSize.
     */
    CreateWithItem([](TabsModelNG model) {});
    LayoutConstraintF childConstraint = LayoutConstraintF();
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::FIXED);
    float width = 1.0;
    float height = 2.0;
    auto ideaSize = SizeF(width, height);
    int32_t childCount = 1;
    auto axis = Axis::FREE;
    tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;

    /**
     * @tc.steps: step2. call UpdateChildConstraint function.
     * @tc.expected: The function is run ok.
     */
    tabBarLayoutAlgorithm->UpdateChildConstraint(childConstraint, tabBarLayoutProperty_, ideaSize, childCount, axis);
    EXPECT_EQ(tabBarLayoutProperty_->GetTabBarMode().value(), TabBarMode::FIXED);
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarLayoutAlgorithm->UpdateChildConstraint(childConstraint, tabBarLayoutProperty_, ideaSize, childCount, axis);
    EXPECT_EQ(tabBarLayoutProperty_->GetTabBarMode().value(), TabBarMode::SCROLLABLE);
}

/**
 * @tc.name: TabBarBlurStyle001
 * @tc.desc: test TabBarBlurStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarBlurStyle001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->SetMinPlatformVersion(PLATFORM_VERSION_11);

    /**
     * @tc.steps: step2. update blurstyle
     * @tc.expected: step2. expect The blurstyle is COMPONENT_THICK.
     */
    BlurStyleOption styleOption;
    styleOption.blurStyle = BlurStyle::COMPONENT_THICK;
    auto tabBarRenderContext = tabBarNode_->GetRenderContext();
    if (!Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        tabBarRenderContext->UpdateBackBlurStyle(styleOption);
    }
    EXPECT_EQ(tabBarRenderContext->GetBackBlurStyle()->blurStyle, BlurStyle::COMPONENT_THICK);
}

/**
 * @tc.name: TabBarLayoutAlgorithmCheckMarqueeForScrollable001
 * @tc.desc: Test the CheckMarqueeForScrollable function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmCheckMarqueeForScrollable001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabbarLayoutAlgorithm));
    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty());

    /**
     * @tc.steps: steps2. Create different input parameters.
     */
    layoutProperty->UpdateTabBarMode(TabBarMode::FIXED);
    int32_t childCount = 0;
    BarGridColumnOptions option;
    option.lg = 2;
    tabBarLayoutProperty_->UpdateBarGridAlign(option);

    /**
     * @tc.steps: steps3. CheckMarqueeForScrollable.
     * @tc.expected: steps3. Check the results of CheckMarqueeForScrollable under different conditions.
     */
    tabbarLayoutAlgorithm->CheckMarqueeForScrollable(&layoutWrapper, childCount);
    EXPECT_NE(tabbarLayoutAlgorithm, nullptr);
    childCount = 1;
    tabbarLayoutAlgorithm->CheckMarqueeForScrollable(&layoutWrapper, childCount);
    EXPECT_NE(tabbarLayoutAlgorithm, nullptr);
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
* @tc.name: SetTabBarStyle001
* @tc.desc: test AddTabBarItem
* @tc.type: FUNC
*/
HWTEST_F(TabsTestNg, SetTabBarStyle001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();

    /**
    * @tc.steps: step1. step1.SetTabBarStyle Set TabBarStyle to TabBarStyle: SUBTABBATSTYLE
    * @tc.steps: sCall the GetTabBarStyle interface under the TabContentModelNG
    * @tc.expected: Equal to TabBarStyle: SUBTABBATSTYLE.
    */
    const std::string text_test = "text_test";
    tabContentPattern->SetTabBar(text_test, "", nullptr);
    EXPECT_EQ(tabContentPattern->GetTabBarParam().GetText(), text_test);

    tabContentPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    EXPECT_EQ(tabContentPattern->GetTabBarStyle(), TabBarStyle::SUBTABBATSTYLE);
    tabContentPattern->SetTabBar(text_test, "", nullptr);
    EXPECT_EQ(tabContentPattern->GetTabBarParam().GetText(), text_test);

    tabContentPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    EXPECT_EQ(tabContentPattern->GetTabBarStyle(), TabBarStyle::SUBTABBATSTYLE);
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
* @tc.name: TabsModelMeasure007
* @tc.desc: test Measure
* @tc.type: FUNC
*/
HWTEST_F(TabsTestNg, TabsModelMeasure007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });

    /**
     * @tc.steps: step1. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step1. related function is called.
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

    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode_, geometryNode1, swiperNode_->GetLayoutProperty());
    swiperLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);

    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));

    layoutWrapper.AppendChild(swiperLayoutWrapper);
    auto dividerNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(TEST_DIVIDER_INDEX));
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> dividerLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(dividerNode, geometryNode2, dividerNode->GetLayoutProperty());
    dividerLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    dividerLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(dividerLayoutWrapper);

    RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> tabBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode_, geometryNode3, tabBarNode_->GetLayoutProperty());
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(tabBarLayoutWrapper);

    /**
     * @tc.steps: step1. Set currentChildCount_ Value is 0
     * @tc.expected: step1. After calling the Measure interface, layoutWrapper GetTotalChildCount() -2 <=0
     */
    layoutWrapper.currentChildCount_ = 0;
    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    tabsLayoutAlgorithm->Layout(&layoutWrapper);
    EXPECT_TRUE(layoutWrapper.GetTotalChildCount() - 2 <= 0);
}

/**
* @tc.name: TabBarPatternProvideRestoreInfo003
* @tc.desc: test Measure
* @tc.type: FUNC
*/
HWTEST_F(TabsTestNg, TabBarPatternProvideRestoreInfo003, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });

    /**
     * @tc.steps: step1.1. Constructing TabBarPattern class pointers
     * @tc.expected:tabBarPattern_->ProvideRestoreInfo() not null.
     */
    EXPECT_TRUE(tabBarPattern_->ProvideRestoreInfo() != "");
}

/**
* @tc.name: TabBarPatternBeforeCreateLayoutWrapper003
* @tc.desc: test Measure
* @tc.type: FUNC
*/
HWTEST_F(TabsTestNg, TabBarPatternBeforeCreateLayoutWrapper003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });
    tabBarPattern_->BeforeCreateLayoutWrapper();
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
 * @tc.name: TabBarModifierSetSelectedMode002
 * @tc.desc: test SetSelectedMode
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarModifierSetSelectedMode002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Select mode as BOARD
     */
    SelectedMode selectedMode = SelectedMode::BOARD;
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    tabBarModifier->SetSelectedMode(selectedMode);
    ASSERT_NE(tabBarModifier->hasIndicator_, nullptr);
    tabBarModifier->hasIndicator_ = nullptr;

    /**
     * @tc.steps: steps2.Calling the SetSelectedMode interface to pass in SelectedMode:: BOARD
     * @tc.expected: steps2. TabBarModifier -> has Indicator_ nullptr
     */
    tabBarModifier->SetSelectedMode(selectedMode);
    EXPECT_EQ(tabBarModifier->hasIndicator_, nullptr);
}

/**
 * @tc.name: TabBarPatternAdjustFocusPosition003
 * @tc.desc: test AdjustFocusPosition
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternAdjustFocusPosition004, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});

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
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    EXPECT_EQ(tabBarPattern_->GetTabBarStyle(), TabBarStyle::SUBTABBATSTYLE);

    /**
     * @tc.steps: steps3. Set TabBarStyle: NOSTYLE
     * @tc.expected: Expected value is TabBarStyle: NOSTYLE
     */
    tabBarPattern_->SetTabBarStyle(TabBarStyle::NOSTYLE);
    EXPECT_EQ(tabBarPattern_->GetTabBarStyle(), TabBarStyle::NOSTYLE);

    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    EXPECT_EQ(tabBarPattern_->GetTabBarStyle(), TabBarStyle::BOTTOMTABBATSTYLE);
}

/**
 * @tc.name: TabBarLayoutAlgorithmUpdateChildConstraint002
 * @tc.desc: test UpdateChildConstraint
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmUpdateChildConstraint003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build tabBarNode_ and ideaSize.
     */
    LayoutConstraintF childConstraint = LayoutConstraintF();
    CreateWithItem([](TabsModelNG model) {});

    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::FIXED);

    /**
     * @tc.steps: step2. Set width and height
     */
    float width = 1.0;
    float height = 2.0;
    auto ideaSize = SizeF(width, height);
    int32_t childCount = 1;
    auto axis = Axis::FREE;
    tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;

    /**
     * @tc.steps: step2. call UpdateChildConstraint function.
     * @tc.expected: The function is run ok.
     */
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::FIXED_START);
    tabBarLayoutAlgorithm->UpdateChildConstraint(childConstraint, tabBarLayoutProperty_, ideaSize, childCount, axis);
    EXPECT_EQ(tabBarLayoutProperty_->GetTabBarMode().value(), TabBarMode::FIXED_START);
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
 * @tc.name: SetOnContentWillChangeTest001
 * @tc.desc: test onContentWillChange
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, SetOnContentWillChangeTest001, TestSize.Level1)
{
    auto callback = [](int32_t currentIndex, int32_t comingIndex) -> bool { return true; };
    CreateWithItem([=](TabsModelNG model) {
        model.SetOnContentWillChange(std::move(callback));
    });
    EXPECT_TRUE(pattern_->GetInterceptStatus());

    auto ret = pattern_->OnContentWillChange(CURRENT_INDEX, BEGIN_INDEX);
    EXPECT_TRUE(ret.value());
    EXPECT_TRUE(swiperPattern_->ContentWillChange(BEGIN_INDEX));
    EXPECT_TRUE(swiperPattern_->ContentWillChange(CURRENT_INDEX, BEGIN_INDEX));
    EXPECT_TRUE(tabBarPattern_->ContentWillChange(BEGIN_INDEX));
    EXPECT_TRUE(tabBarPattern_->ContentWillChange(CURRENT_INDEX, BEGIN_INDEX));
}

/**
 * @tc.name: SetOnContentWillChangeTest002
 * @tc.desc: test OnWillShow and OnWillHide
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, SetOnContentWillChangeTest002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create parent node
     */
    int32_t nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    auto parentNode = FrameNode::CreateFrameNode(
        V2::PAGE_ETS_TAG, nodeId, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    ViewStackProcessor::GetInstance()->Push(parentNode);

    /**
     * @tc.steps: steps2. Create tabs
     */
    TabsModelNG model;
    model.Create(BarPosition::START, 1, nullptr, nullptr);
    ViewAbstract::SetWidth(CalcLength(TABS_WIDTH));
    ViewAbstract::SetHeight(CalcLength(TABS_HEIGHT));
    bool isShow = false;
    CreateItem(TABCONTENT_NUMBER, [&isShow](TabContentModelNG model, int32_t index) {
        std::function<void()> showEvent = [&isShow]() { isShow = true; };
        std::function<void()> hideEvent = [&isShow]() { isShow = false; };
        model.SetOnWillShow(std::move(showEvent));
        model.SetOnWillHide(std::move(hideEvent));
    });
    frameNode_ = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ViewStackProcessor::GetInstance()->Pop();

    /**
     * @tc.steps: step3. first display.
     * @tc.expected: isShow = true
     */
    FlushLayoutTask(frameNode_);
    ViewStackProcessor::GetInstance()->Finish();
    EXPECT_TRUE(isShow);

    /**
     * @tc.steps: step4. callback.
     * @tc.expected: isShow = false
     */
    auto callback = parentNode->GetPattern<PagePattern>()->onHiddenChange_;
    ASSERT_NE(callback, nullptr);
    callback(false);
    EXPECT_FALSE(isShow);

    /**
     * @tc.steps: step5. callback.
     * @tc.expected: isShow = true
     */
    callback(true);
    EXPECT_TRUE(isShow);
}

/**
 * @tc.name: SetOnContentWillChangeTest003
 * @tc.desc: test OnWillShow and OnWillHide
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, SetOnContentWillChangeTest003, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create parent node
     */
    int32_t nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    auto parentNode = FrameNode::CreateFrameNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, nodeId, AceType::MakeRefPtr<NavDestinationPattern>());
    ViewStackProcessor::GetInstance()->Push(parentNode);

    /**
     * @tc.steps: steps2. Create tabs
     */
    TabsModelNG model;
    model.Create(BarPosition::START, 1, nullptr, nullptr);
    ViewAbstract::SetWidth(CalcLength(TABS_WIDTH));
    ViewAbstract::SetHeight(CalcLength(TABS_HEIGHT));

    bool isShow = false;
    CreateItem(TABCONTENT_NUMBER, [&isShow](TabContentModelNG model, int32_t index) {
        std::function<void()> showEvent = [&isShow]() { isShow = true; };
        std::function<void()> hideEvent = [&isShow]() { isShow = false; };
        model.SetOnWillShow(std::move(showEvent));
        model.SetOnWillHide(std::move(hideEvent));
    });
    frameNode_ = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ViewStackProcessor::GetInstance()->Pop();
    FlushLayoutTask(frameNode_);
    ViewStackProcessor::GetInstance()->Finish();

    /**
     * @tc.steps: step3. callback.
     * @tc.expected: isShow = false
     */
    auto callback =
        parentNode->GetPattern<NavDestinationPattern>()->GetEventHub<NavDestinationEventHub>()->onHiddenChange_;
    ASSERT_NE(callback, nullptr);
    callback(false);
    EXPECT_FALSE(isShow);

    /**
     * @tc.steps: step4. callback.
     * @tc.expected: isShow = true
     */
    callback(true);
    EXPECT_TRUE(isShow);
}

/**
 * @tc.name: SetOnContentWillChangeTest004
 * @tc.desc: test OnWillShow and OnWillHide
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, SetOnContentWillChangeTest004, TestSize.Level1)
{
    /**
     * @tc.steps: steps2. Create parentNode
     */
    auto parentNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ViewStackProcessor::GetInstance()->Push(parentNode);

    /**
     * @tc.steps: steps2. Create tabs
     */
    TabsModelNG model;
    model.Create(BarPosition::START, 0, nullptr, nullptr);
    ViewAbstract::SetWidth(CalcLength(TABS_WIDTH));
    ViewAbstract::SetHeight(CalcLength(TABS_HEIGHT));

    int isShow = 0;
    CreateItem(TABCONTENT_NUMBER, [&isShow](TabContentModelNG model, int32_t index) {
        std::function<void()> showEvent = [&isShow, index]() { isShow |= 1 << index; };
        std::function<void()> hideEvent = [&isShow, index]() { isShow &= ~(1 << index); };
        model.SetOnWillShow(std::move(showEvent));
        model.SetOnWillHide(std::move(hideEvent));
    });

    auto tabNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabNode->GetTabBar());
    tabBarNode->GetOrCreateFocusHub();
    frameNode_ = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ViewStackProcessor::GetInstance()->Pop();
    swiperNode_ = AceType::DynamicCast<FrameNode>(frameNode_->GetTabs());
    swiperPattern_ = swiperNode_->GetPattern<SwiperPattern>();
    swiperController_ = swiperPattern_->GetSwiperController();

    /**
     * @tc.steps: step3. first display.
     * @tc.expected: isShow = 0b0001
     */
    FlushLayoutTask(frameNode_);
    ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(isShow, 1);

    /**
     * @tc.steps: step4. SwipeTo 1.
     * @tc.expected: isShow = 0b0010
     */
    swiperController_->SwipeTo(1);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE); // for update swiper
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(isShow, 2);

    /**
     * @tc.steps: step6. SwipeTo 3.
     * @tc.expected: isShow = 0b1000
     */
    swiperController_->SwipeTo(3);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE); // for update swiper
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(isShow, 8);
}

/**
 * @tc.name: SetOnContentWillChangeTest005
 * @tc.desc: test the middle tabcontents does not trigger OnWillShow and OnWillHide
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, SetOnContentWillChangeTest005, TestSize.Level1)
{
    /**
     * @tc.steps: steps2. Create parentNode
     */
    auto parentNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ViewStackProcessor::GetInstance()->Push(parentNode);

    /**
     * @tc.steps: steps2. Create tabs
     */
    TabsModelNG model;
    model.Create(BarPosition::START, 0, nullptr, nullptr);
    ViewAbstract::SetWidth(CalcLength(TABS_WIDTH));
    ViewAbstract::SetHeight(CalcLength(TABS_HEIGHT));

    int isShow = 0;
    CreateItem(TABCONTENT_NUMBER, [&isShow](TabContentModelNG model, int32_t index) {
        std::function<void()> showEvent = [&isShow, index]() { isShow |= 1 << index; };
        model.SetOnWillShow(std::move(showEvent));
    });

    auto tabNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabNode->GetTabBar());
    tabBarNode->GetOrCreateFocusHub();
    frameNode_ = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ViewStackProcessor::GetInstance()->Pop();
    swiperNode_ = AceType::DynamicCast<FrameNode>(frameNode_->GetTabs());
    swiperPattern_ = swiperNode_->GetPattern<SwiperPattern>();
    swiperController_ = swiperPattern_->GetSwiperController();

    /**
     * @tc.steps: step3. first display.
     * @tc.expected: isShow = 0b0001
     */
    FlushLayoutTask(frameNode_);
    ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(isShow, 1);

    /**
     * @tc.steps: step4. SwipeTo 3.
     * @tc.expected: The middle tabcontents does not trigger OnWillShow.
                    isShow = 0b1001
     */
    swiperController_->SwipeTo(3);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE); // for update swiper
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(isShow, 9);
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
