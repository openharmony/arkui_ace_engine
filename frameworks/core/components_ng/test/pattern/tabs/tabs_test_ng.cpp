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

#include <cstddef>
#include <utility>

#include "gtest/gtest.h"

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"

#define private public
#define protected public
#include "core/components/scroll/scrollable.h"
#include "core/components/tab_bar/tab_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/layout/layout_wrapper_builder.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/divider/divider_render_property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_event_hub.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/tabs/tab_bar_pattern.h"
#include "core/components_ng/pattern/tabs/tab_content_model_ng.h"
#include "core/components_ng/pattern/tabs/tab_content_pattern.h"
#include "core/components_ng/pattern/tabs/tabs_model_ng.h"
#include "core/components_ng/pattern/tabs/tabs_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/test/mock/rosen/mock_canvas.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float FIRST_ITEM_WIDTH = 800.0f;
constexpr float FIRST_ITEM_HEIGHT = 800.0f;
const SizeF FIRST_ITEM_SIZE(FIRST_ITEM_WIDTH, FIRST_ITEM_HEIGHT);
constexpr float INFINITY_NUM = 1000000.0f;
const SizeF INFINITY_SIZE(INFINITY_NUM, INFINITY_NUM);
constexpr float NEGTIVE_NUM = -100.0f;
const SizeF NEGTIVE_SIZE(NEGTIVE_NUM, NEGTIVE_NUM);
constexpr float TABBAR_WIDTH = 50.0f;
constexpr float SWIPER_WIDTH = 750.0f;
const double DEFAULT_OFFSET = -1.0f;
const int DEFAULT_ITEMCOUNT = 1;
const int DEFAULT_INDEX = -1;
const int BEGIN_INDEX = 0;
const int CURRENT_INDEX = 1;
const int END_INDEX = 0;
const OffsetF CURRENT_OFFSET(1.0f, 1.0f);
constexpr float TEST_MASK_A_RADIUS_RATIO = 0.0f;
constexpr float TEST_MASK_B_RADIUS_RATIO = 1.414f;
constexpr float TEST_MASK_MIDDLE_RADIUS_RATIO = (TEST_MASK_A_RADIUS_RATIO + TEST_MASK_B_RADIUS_RATIO) / 2.0f;
constexpr int32_t TEST_SWIPER_INDEX = 0;
constexpr int32_t TEST_DIVIDER_INDEX = 1;
constexpr int32_t TEST_TAB_BAR_INDEX = 2;
constexpr int32_t TEST_SELECTED_MASK_COUNT = 2;
constexpr int32_t TEST_UNSELECTED_MASK_COUNT = 1;
} // namespace

class TabsTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void MockPipelineContextGetTheme();
};

void TabsTestNg::SetUpTestSuite()
{
    MockPipelineBase::SetUp();
}

void TabsTestNg::TearDownTestSuite()
{
    MockPipelineBase::TearDown();
}

void TabsTestNg::MockPipelineContextGetTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TabTheme>()));
}

/**
 * @tc.name: TabsModelSetDivider001
 * @tc.desc: test SetDivider
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelSetDivider001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    TabsModelNG tabsModel;
    TabsItemDivider divider;
    Dimension strokeWidth = 10.0_vp;
    Dimension startMargin = 3.0_vp;
    Dimension endMargin = 4.0_vp;
    Color color = Color::BLACK;

    divider.strokeWidth = strokeWidth;
    divider.startMargin = startMargin;
    divider.endMargin = endMargin;
    divider.color = color;
    divider.isNull = false;

    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    tabsModel.SetDivider(divider);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto dividerNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(1));
    ASSERT_NE(dividerNode, nullptr);
    EXPECT_EQ(dividerNode->GetTag(), V2::DIVIDER_ETS_TAG);
    auto layoutProperty = tabsFrameNode->GetLayoutProperty<TabsLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetDivider()->color.ColorToString(), color.ColorToString());
    EXPECT_EQ(layoutProperty->GetDivider()->strokeWidth.ToString(), strokeWidth.ToString());
    EXPECT_EQ(layoutProperty->GetDivider()->startMargin.ToString(), startMargin.ToString());
    EXPECT_EQ(layoutProperty->GetDivider()->endMargin.ToString(), endMargin.ToString());
    EXPECT_EQ(layoutProperty->GetDivider()->isNull, false);

    auto clone = layoutProperty->Clone();
    clone.Reset();
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    layoutProperty->ToJsonValue(json);
    ASSERT_NE(json, nullptr);

    auto dividerJson = json->GetValue("divider");
    ASSERT_NE(dividerJson, nullptr);
    layoutProperty->Reset();
    layoutProperty->ToJsonValue(json);
    tabsModel.Pop();

    TabsItemDivider divider2;
    EXPECT_FALSE(divider == divider2);
}

/**
 * @tc.name: TabsModelSetDivider002
 * @tc.desc: test SetDivider
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelSetDivider002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    TabsModelNG tabsModel;
    TabsItemDivider divider;
    divider.isNull = true;

    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    tabsModel.SetDivider(divider);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto dividerNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(1));
    ASSERT_NE(dividerNode, nullptr);
    EXPECT_EQ(dividerNode->GetTag(), V2::DIVIDER_ETS_TAG);
    auto layoutProperty = tabsFrameNode->GetLayoutProperty<TabsLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetDivider()->isNull, true);

    auto clone = layoutProperty->Clone();
    clone.Reset();
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    layoutProperty->ToJsonValue(json);
    ASSERT_NE(json, nullptr);
}

/**
 * @tc.name: TabsModelSetFadingEdge001
 * @tc.desc: test SetFadingEdge
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelSetFadingEdge001, TestSize.Level1)
{
    MockPipelineContextGetTheme();

    TabsModelNG tabsModel;
    bool fadingEdge = true;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    tabsModel.SetFadingEdge(fadingEdge);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsFrameNode, nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);
    auto tabBarPaintProperty = tabBarNode->GetPaintProperty<TabBarPaintProperty>();
    ASSERT_NE(tabBarPaintProperty, nullptr);
    EXPECT_TRUE(tabBarPaintProperty->GetFadingEdgeValue());

    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    tabsFrameNode->ToJsonValue(json);

    auto fadingEdgeJson = json->GetValue("fadingEdge");
    EXPECT_NE(fadingEdgeJson, nullptr);
}

/**
 * @tc.name: TabsModelMeasure001
 * @tc.desc: Test Divider Measure and Layout.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelMeasure001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    MockPipelineContextGetTheme();

    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    instance.SetDivider(divider);

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step2. related function is called.
     */
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto pattern = tabsFrameNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    auto tabsLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(tabsLayoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapper layoutWrapper = LayoutWrapper(tabsFrameNode, geometryNode, tabsFrameNode->GetLayoutProperty());
    LayoutConstraintF layoutConstraintVaild;
    float layoutSize = 10000.0f;
    layoutConstraintVaild.selfIdealSize.SetSize(SizeF(layoutSize, layoutSize));
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstraintVaild);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(swiperNode, geometryNode1, swiperNode->GetLayoutProperty());
    swiperLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(swiperLayoutWrapper);

    auto dividerNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_DIVIDER_INDEX));
    ASSERT_NE(dividerNode, nullptr);
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> dividerLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(dividerNode, geometryNode2, dividerNode->GetLayoutProperty());
    dividerLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    dividerLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(dividerLayoutWrapper);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> tabBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(tabBarNode, geometryNode3, tabBarNode->GetLayoutProperty());
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(tabBarLayoutWrapper);

    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    tabsLayoutAlgorithm->Layout(&layoutWrapper);
    auto dividerOffset = dividerLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_EQ(dividerOffset.GetX(), 0);
    EXPECT_EQ(dividerOffset.GetY(), 0);

    tabsFrameNode->GetLayoutProperty<TabsLayoutProperty>()->UpdateTabBarPosition(BarPosition::END);
    layoutWrapper.GetGeometryNode()->SetFrameSize(SizeF(10000.0f, 10000.0f));
    tabsLayoutAlgorithm->Layout(&layoutWrapper);
    dividerOffset = dividerLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_EQ(dividerOffset.GetX(), 0);
    EXPECT_EQ(dividerOffset.GetY(), layoutSize);

    instance.SetIsVertical(true);
    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    tabsLayoutAlgorithm->Layout(&layoutWrapper);
    dividerOffset = dividerLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_EQ(dividerOffset.GetX(), layoutSize);
    EXPECT_EQ(dividerOffset.GetY(), 0);

    tabsFrameNode->GetLayoutProperty<TabsLayoutProperty>()->UpdateTabBarPosition(BarPosition::START);
    layoutWrapper.GetGeometryNode()->SetFrameSize(SizeF(10000.0f, 10000.0f));
    tabsLayoutAlgorithm->Layout(&layoutWrapper);
    dividerOffset = dividerLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_EQ(dividerOffset.GetX(), 0);
    EXPECT_EQ(dividerOffset.GetY(), 0);
    tabsFrameNode->GetLayoutProperty<TabsLayoutProperty>()->UpdateBarOverlap(true);
    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_TRUE(tabsFrameNode->GetLayoutProperty<TabsLayoutProperty>()->GetBarOverlap().value());

    tabsFrameNode->GetLayoutProperty<TabsLayoutProperty>()->UpdateBarOverlap(false);
    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_FALSE(tabsFrameNode->GetLayoutProperty<TabsLayoutProperty>()->GetBarOverlap().value());
}

/**
 * @tc.name: TabsModelMeasure002
 * @tc.desc: Test Tabs Measure and Layout.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelMeasure002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    MockPipelineContextGetTheme();

    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: related function is called.
     */
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto pattern = tabsFrameNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    auto tabsLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(tabsLayoutAlgorithm, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(tabsFrameNode, geometryNode, tabsFrameNode->GetLayoutProperty());
    LayoutConstraintF layoutConstrain;
    layoutConstrain.maxSize = FIRST_ITEM_SIZE;
    layoutConstrain.percentReference = FIRST_ITEM_SIZE;
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstrain);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = SizeF(FIRST_ITEM_SIZE);
    childLayoutConstraint.minSize = SizeF(0.0f, 0.0f);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    RefPtr<GeometryNode> swiperGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(swiperNode, swiperGeometryNode, swiperNode->GetLayoutProperty());

    auto swipeLayoutAlgorithm = swiperNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    ASSERT_NE(swipeLayoutAlgorithm, nullptr);
    swiperLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(swipeLayoutAlgorithm));

    swiperLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(SWIPER_WIDTH)));
    layoutWrapper.AppendChild(swiperLayoutWrapper);

    auto dividerNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_DIVIDER_INDEX));
    ASSERT_NE(dividerNode, nullptr);
    RefPtr<GeometryNode> dividerGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> dividerLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(dividerNode, dividerGeometryNode, dividerNode->GetLayoutProperty());

    auto dividerLayoutAlgorithm = dividerNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    ASSERT_NE(dividerLayoutAlgorithm, nullptr);
    dividerLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(dividerLayoutAlgorithm));

    dividerLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    dividerLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(0.0f)));
    layoutWrapper.AppendChild(dividerLayoutWrapper);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    RefPtr<GeometryNode> tabbarGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> tabBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(tabBarNode, tabbarGeometryNode, tabBarNode->GetLayoutProperty());

    auto tabbarLayoutAlgorithm = tabBarNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    ASSERT_NE(tabbarLayoutAlgorithm, nullptr);
    tabBarLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(tabbarLayoutAlgorithm));

    tabBarLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(TABBAR_WIDTH)));
    layoutWrapper.AppendChild(tabBarLayoutWrapper);

    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    tabsLayoutAlgorithm->Layout(&layoutWrapper);

    auto tabbarOffset = tabBarLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_EQ(tabbarOffset.GetX(), 0.0f);
    EXPECT_EQ(tabbarOffset.GetY(), 0.0f);

    auto tabBarSize = tabBarLayoutWrapper->GetGeometryNode()->GetFrameSize();
    EXPECT_EQ(tabBarSize.Width(), FIRST_ITEM_WIDTH);
    EXPECT_EQ(tabBarSize.Height(), TABBAR_WIDTH);

    auto swiperOffset = swiperLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_EQ(swiperOffset.GetX(), 0.0f);
    EXPECT_EQ(swiperOffset.GetY(), TABBAR_WIDTH);

    auto swiperSize = swiperLayoutWrapper->GetGeometryNode()->GetFrameSize();
    EXPECT_EQ(swiperSize.Width(), FIRST_ITEM_WIDTH);
    EXPECT_EQ(swiperSize.Height(), SWIPER_WIDTH);

    tabsFrameNode->GetLayoutProperty<TabsLayoutProperty>()->UpdateTabBarPosition(BarPosition::END);
    tabsLayoutAlgorithm->Layout(&layoutWrapper);

    tabbarOffset = tabBarLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_EQ(tabbarOffset.GetX(), 0.0f);
    EXPECT_EQ(tabbarOffset.GetY(), SWIPER_WIDTH);

    swiperOffset = swiperLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_EQ(swiperOffset.GetX(), 0.0f);
    EXPECT_EQ(swiperOffset.GetY(), 0.0f);
}

/**
 * @tc.name: TabsModelMeasure003
 * @tc.desc: Test Tabs Measure and Layout when is vertical.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelMeasure003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    MockPipelineContextGetTheme();

    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    instance.SetIsVertical(true);

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: related function is called.
     */
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto pattern = tabsFrameNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    auto tabsLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(tabsLayoutAlgorithm, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(tabsFrameNode, geometryNode, tabsFrameNode->GetLayoutProperty());
    LayoutConstraintF layoutConstrain;
    layoutConstrain.maxSize = FIRST_ITEM_SIZE;
    layoutConstrain.percentReference = FIRST_ITEM_SIZE;
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstrain);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = SizeF(FIRST_ITEM_SIZE);
    childLayoutConstraint.minSize = SizeF(0.0f, 0.0f);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    RefPtr<GeometryNode> swiperGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(swiperNode, swiperGeometryNode, swiperNode->GetLayoutProperty());

    auto swipeLayoutAlgorithm = swiperNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    ASSERT_NE(swipeLayoutAlgorithm, nullptr);
    swiperLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(swipeLayoutAlgorithm));

    swiperLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(SWIPER_WIDTH), CalcLength(FIRST_ITEM_WIDTH)));
    layoutWrapper.AppendChild(swiperLayoutWrapper);
    auto dividerNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_DIVIDER_INDEX));
    ASSERT_NE(dividerNode, nullptr);
    RefPtr<GeometryNode> dividerGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> dividerLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(dividerNode, dividerGeometryNode, dividerNode->GetLayoutProperty());

    auto dividerLayoutAlgorithm = dividerNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    ASSERT_NE(dividerLayoutAlgorithm, nullptr);
    dividerLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(dividerLayoutAlgorithm));

    dividerLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    dividerLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(0.0f), CalcLength(FIRST_ITEM_WIDTH)));
    layoutWrapper.AppendChild(dividerLayoutWrapper);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    RefPtr<GeometryNode> tabbarGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> tabBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(tabBarNode, tabbarGeometryNode, tabBarNode->GetLayoutProperty());

    auto tabbarLayoutAlgorithm = tabBarNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    ASSERT_NE(tabbarLayoutAlgorithm, nullptr);
    tabBarLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(tabbarLayoutAlgorithm));

    tabBarLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(TABBAR_WIDTH), CalcLength(FIRST_ITEM_WIDTH)));
    layoutWrapper.AppendChild(tabBarLayoutWrapper);

    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    tabsLayoutAlgorithm->Layout(&layoutWrapper);

    auto tabbarOffset = tabBarLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_EQ(tabbarOffset.GetX(), 0.0f);
    EXPECT_EQ(tabbarOffset.GetY(), 0.0f);

    auto tabBarSize = tabBarLayoutWrapper->GetGeometryNode()->GetFrameSize();
    EXPECT_EQ(tabBarSize.Width(), TABBAR_WIDTH);
    EXPECT_EQ(tabBarSize.Height(), FIRST_ITEM_WIDTH);

    auto swiperOffset = swiperLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_EQ(swiperOffset.GetX(), TABBAR_WIDTH);
    EXPECT_EQ(swiperOffset.GetY(), 0.0f);

    auto swiperSize = swiperLayoutWrapper->GetGeometryNode()->GetFrameSize();
    EXPECT_EQ(swiperSize.Width(), SWIPER_WIDTH);
    EXPECT_EQ(swiperSize.Height(), FIRST_ITEM_WIDTH);

    tabsFrameNode->GetLayoutProperty<TabsLayoutProperty>()->UpdateTabBarPosition(BarPosition::END);
    tabsLayoutAlgorithm->Layout(&layoutWrapper);

    tabbarOffset = tabBarLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_EQ(tabbarOffset.GetX(), SWIPER_WIDTH);
    EXPECT_EQ(tabbarOffset.GetY(), 0.0f);

    swiperOffset = swiperLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_EQ(swiperOffset.GetX(), 0.0f);
    EXPECT_EQ(swiperOffset.GetY(), 0.0f);
}

/**
 * @tc.name: TabsModelMeasure004
 * @tc.desc: Test Tabs Measure and Layout when the ideaSize is infinity.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelMeasure004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    MockPipelineContextGetTheme();

    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    instance.SetIsVertical(true);

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: related function is called.
     */
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto pattern = tabsFrameNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    auto tabsLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(tabsLayoutAlgorithm, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(tabsFrameNode, geometryNode, tabsFrameNode->GetLayoutProperty());
    LayoutConstraintF layoutConstrain;
    layoutConstrain.selfIdealSize.SetSize(SizeF(FIRST_ITEM_WIDTH, INFINITY_NUM));
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstrain);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    tabsLayoutAlgorithm->Layout(&layoutWrapper);

    auto tabsSize = layoutWrapper.GetGeometryNode()->GetFrameSize();
    EXPECT_EQ(tabsSize.Width(), 0.0f);
    EXPECT_EQ(tabsSize.Height(), 0.0f);

    layoutConstrain.selfIdealSize.SetSize(SizeF(INFINITY_NUM, FIRST_ITEM_HEIGHT));
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstrain);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));

    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    tabsLayoutAlgorithm->Layout(&layoutWrapper);

    tabsSize = layoutWrapper.GetGeometryNode()->GetFrameSize();
    EXPECT_EQ(tabsSize.Width(), 0.0f);
    EXPECT_EQ(tabsSize.Height(), 0.0f);

    layoutConstrain.selfIdealSize.SetSize(NEGTIVE_SIZE);
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstrain);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));

    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    tabsLayoutAlgorithm->Layout(&layoutWrapper);

    auto tabsOffset = layoutWrapper.GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_EQ(tabsOffset.GetX(), 0.0f);
    EXPECT_EQ(tabsOffset.GetY(), 0.0f);

    layoutConstrain.selfIdealSize.SetSize(FIRST_ITEM_SIZE);
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstrain);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));

    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = SizeF(FIRST_ITEM_SIZE);
    childLayoutConstraint.minSize = SizeF(0.0f, 0.0f);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(0));
    ASSERT_NE(tabBarNode, nullptr);
    RefPtr<GeometryNode> tabbarGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> tabBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(tabBarNode, tabbarGeometryNode, tabBarNode->GetLayoutProperty());

    auto tabbarLayoutAlgorithm = tabBarNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    ASSERT_NE(tabbarLayoutAlgorithm, nullptr);
    tabBarLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(tabbarLayoutAlgorithm));

    tabBarLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(TABBAR_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(tabBarLayoutWrapper);

    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    tabsLayoutAlgorithm->Layout(&layoutWrapper);

    tabsOffset = layoutWrapper.GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_EQ(tabsOffset.GetX(), 0.0f);
    EXPECT_EQ(tabsOffset.GetY(), 0.0f);

    auto dividerNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(1));
    ASSERT_NE(dividerNode, nullptr);
    RefPtr<GeometryNode> dividerGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> dividerLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(dividerNode, dividerGeometryNode, dividerNode->GetLayoutProperty());

    auto dividerLayoutAlgorithm = dividerNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    ASSERT_NE(dividerLayoutAlgorithm, nullptr);
    dividerLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(dividerLayoutAlgorithm));

    dividerLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    dividerLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(0.0f), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(dividerLayoutWrapper);

    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    tabsLayoutAlgorithm->Layout(&layoutWrapper);

    tabsOffset = layoutWrapper.GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_EQ(tabsOffset.GetX(), 0.0f);
    EXPECT_EQ(tabsOffset.GetY(), 0.0f);
}

/**
 * @tc.name: TabBarLayoutAlgorithmMeasure001
 * @tc.desc: Test Divider Measure.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmMeasure001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    MockPipelineContextGetTheme();

    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    instance.SetDivider(divider);

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: Related function is called.
     */
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto pattern = tabsFrameNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    auto tabsLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(tabsLayoutAlgorithm, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapper layoutWrapper =
        LayoutWrapper(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty<TabBarLayoutProperty>());
    LayoutConstraintF layoutConstraintVaild;
    float layoutSize = 10000.0f;
    float layoutSize_test = 5000.0f;
    layoutConstraintVaild.selfIdealSize.SetSize(SizeF(layoutSize, layoutSize));
    layoutConstraintVaild.parentIdealSize.SetSize(SizeF(layoutSize_test, layoutSize_test));
    LayoutConstraintF layoutConstraintVaild_test;
    layoutConstraintVaild_test.minSize.SetSizeT(SizeF(layoutSize, layoutSize));
    AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstraintVaild);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    for (int32_t i = 0; i <= 2; i++) {
        auto tabBarNode_test = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
        ASSERT_NE(tabBarNode_test, nullptr);
        RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();
        RefPtr<LayoutWrapper> tabBarLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapper>(tabBarNode_test, geometryNode3, tabBarNode->GetLayoutProperty());
        tabBarLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
        tabBarLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
        layoutWrapper.AppendChild(tabBarLayoutWrapper);
    }

    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern->CreateLayoutAlgorithm());
    ASSERT_NE(tabBarLayoutAlgorithm, nullptr);

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabsLayoutAlgorithm->Measure(&layoutWrapper);
                tabBarLayoutAlgorithm->Measure(&layoutWrapper);
                AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())
                    ->UpdateAxis(Axis::VERTICAL);
                tabBarLayoutAlgorithm->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
            }
            AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())->UpdateAxis(Axis::HORIZONTAL);
            tabBarLayoutAlgorithm->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }
        AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())
            ->UpdateLayoutConstraint(layoutConstraintVaild_test);
        AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())->UpdateAxis(Axis::HORIZONTAL);
        tabBarLayoutAlgorithm->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    }
}

/**
 * @tc.name: TabBarLayoutAlgorithmLayout001
 * @tc.desc: Test Divider Layout.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmLayout001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    MockPipelineContextGetTheme();

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: Related function is called.
     */
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto pattern = tabsFrameNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapper layoutWrapper =
        LayoutWrapper(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty<TabBarLayoutProperty>());
    LayoutConstraintF layoutConstraintVaild;
    float layoutSize = 10000.0f;
    float layoutSize_test = 5000.0f;
    layoutConstraintVaild.selfIdealSize.SetSize(SizeF(layoutSize, layoutSize));
    layoutConstraintVaild.parentIdealSize.SetSize(SizeF(layoutSize_test, layoutSize_test));
    LayoutConstraintF layoutConstraintVaild_test;
    layoutConstraintVaild_test.minSize.SetSizeT(SizeF(layoutSize, layoutSize));
    AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())->UpdateTabBarMode(TabBarMode::FIXED);
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    for (int32_t i = 0; i <= 2; i++) {
        auto tabBarNode_test = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
        ASSERT_NE(tabBarNode_test, nullptr);
        RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();
        RefPtr<LayoutWrapper> tabBarLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapper>(tabBarNode_test, geometryNode3, tabBarNode->GetLayoutProperty());
        tabBarLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
        tabBarLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
        layoutWrapper.AppendChild(tabBarLayoutWrapper);
    }

    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern->CreateLayoutAlgorithm());
    ASSERT_NE(tabBarLayoutAlgorithm, nullptr);
    int32_t indicator = -1;
    int32_t indicator_test = 0;
    AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())->UpdateAxis(Axis::VERTICAL);
    AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())->UpdateIndicator(indicator_test);
    tabBarLayoutAlgorithm->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    tabBarLayoutAlgorithm->SetIndicator(indicator);

    float childrenMainSize = 0.0f;
    float childrenMainSize1 = 0.2f;
    float childrenMainSize_test = 0.1f;
    int32_t index = 0;
    auto axis = Axis::HORIZONTAL;
    tabBarLayoutAlgorithm->SetChildrenMainSize(childrenMainSize);
    layoutWrapper.GetGeometryNode()->SetFrameSize(SizeF(layoutSize, layoutSize));
    layoutWrapper.GetGeometryNode()->GetFrameSize().SetMainSize(childrenMainSize_test, axis);
    AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateTabBarMode(TabBarMode::SCROLLABLE);

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarLayoutAlgorithm->Layout(&layoutWrapper);
                AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())
                    ->UpdateAxis(Axis::VERTICAL);
                tabBarLayoutAlgorithm->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
                tabBarLayoutAlgorithm->SetIndicator(indicator_test);
                AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())
                    ->UpdateIndicator(indicator);
            }
            AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())->UpdateAxis(Axis::HORIZONTAL);
            tabBarLayoutAlgorithm->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
            tabBarLayoutAlgorithm->SetChildrenMainSize(childrenMainSize1);
            layoutWrapper.GetOrCreateChildByIndex(index)->GetGeometryNode()->GetMarginFrameSize().SetMainSize(
                childrenMainSize_test, axis);
            layoutWrapper.GetOrCreateChildByIndex(indicator_test)
                ->GetGeometryNode()
                ->GetMarginFrameSize()
                .SetMainSize(childrenMainSize_test, axis);
            layoutWrapper.GetGeometryNode()->SetFrameSize(SizeF(layoutSize, layoutSize));
            AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())
                ->UpdateIndicator(indicator_test);
            tabBarLayoutAlgorithm->SetIndicator(indicator);
        }
        AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())
            ->UpdateLayoutConstraint(layoutConstraintVaild_test);
        AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())->UpdateAxis(Axis::HORIZONTAL);
        tabBarLayoutAlgorithm->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    }
}

/**
 * @tc.name: TabBarLayoutAlgorithmGetSpace001
 * @tc.desc: Test GetSpace and CalculateFrontChildrenMainSize.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmGetSpace001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    MockPipelineContextGetTheme();

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call GetSpace and
     * CalculateFrontChildrenMainSize functions.
     * @tc.expected: Related function is called.
     */
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto pattern = tabsFrameNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    auto tabsLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(tabsLayoutAlgorithm, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapper layoutWrapper =
        LayoutWrapper(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty<TabBarLayoutProperty>());
    LayoutWrapper layoutWrapper_test =
        LayoutWrapper(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty<TabBarLayoutProperty>());
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(swiperNode, geometryNode1, swiperNode->GetLayoutProperty());
    swiperLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(swiperLayoutWrapper);

    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern->CreateLayoutAlgorithm());
    ASSERT_NE(tabBarLayoutAlgorithm, nullptr);
    int32_t indicator = 0;
    SizeF frameSize(SizeF(0.0f, 0.0f));
    auto axis = Axis::HORIZONTAL;

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            tabBarLayoutAlgorithm->GetSpace(&layoutWrapper, indicator, frameSize, axis);
            tabBarLayoutAlgorithm->CalculateFrontChildrenMainSize(
                &(j == 0 ? layoutWrapper_test : (indicator == 1 ? layoutWrapper : layoutWrapper_test)), indicator,
                axis);
            indicator = (i == 1 ? 0 : 1);
        }
    }
}

/**
 * @tc.name: TabsModelOnUpdateShowDivider001
 * @tc.desc: Test tabs OnUpdateShowDivider.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelOnUpdateShowDivider001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    MockPipelineContextGetTheme();

    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    Color color = Color::RED;
    TabsItemDivider divider;
    divider.color = color;
    instance.SetDivider(divider);

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step2. related function is called.
     */
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsFrameNode, nullptr);

    auto pattern = tabsFrameNode->GetPattern<TabsPattern>();
    pattern->OnUpdateShowDivider();

    auto dividerNode = tabsFrameNode->GetChildAtIndex(1);
    ASSERT_NE(dividerNode, nullptr);
    auto dividerFrameNode = AceType::DynamicCast<FrameNode>(dividerNode);

    auto dividerRenderProperty = dividerFrameNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(dividerRenderProperty, nullptr);
    auto dividerColor = dividerRenderProperty->GetDividerColor();
    EXPECT_EQ(dividerColor.value().ColorToString(), color.ColorToString());
}

/**
 * @tc.name: TabsModelOnUpdateShowDivider002
 * @tc.desc: Test tabs OnUpdateShowDivider when pattern without host
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelOnUpdateShowDivider002, TestSize.Level2)
{
    auto pattern = AceType::MakeRefPtr<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnUpdateShowDivider();
    EXPECT_EQ(pattern->GetHostFrameSize(), std::nullopt);
}

/**
 * @tc.name: TabsModelOnUpdateShowDivider003
 * @tc.desc: Test tabs OnUpdateShowDivider when pattern without host
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelOnUpdateShowDivider003, TestSize.Level2)
{
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto tabsNode =
        TabsModelNG::GetOrCreateTabsNode(V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
    auto pattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnUpdateShowDivider();
    EXPECT_LT(tabsNode->GetChildren().size(), static_cast<std::size_t>(2));
}

/**
 * @tc.name: TabsModelOnUpdateShowDivider004
 * @tc.desc: Test tabs OnUpdateShowDivider when pattern without host
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelOnUpdateShowDivider004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto tabsNode =
        TabsModelNG::GetOrCreateTabsNode(V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
    ASSERT_NE(tabsNode, nullptr);

    bool hasTabBarNode = tabsNode->HasTabBarNode();
    auto controller = AceType::MakeRefPtr<SwiperController>();
    auto tabBarId = tabsNode->GetTabBarId();
    auto tabBarNode = FrameNode::GetOrCreateFrameNode(
        V2::TAB_BAR_ETS_TAG, tabBarId, [controller]() { return AceType::MakeRefPtr<TabBarPattern>(controller); });
    ASSERT_NE(tabBarNode, nullptr);

    if (!hasTabBarNode) {
        tabBarNode->MountToParent(tabsNode);
    }

    bool hasSwiperNode = tabsNode->HasSwiperNode();
    auto swiperId = tabsNode->GetSwiperId();
    auto swiperNode = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_ETS_TAG, swiperId, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    ASSERT_NE(swiperNode, nullptr);

    if (!hasSwiperNode) {
        swiperNode->MountToParent(tabsNode);
    }

    auto pattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnUpdateShowDivider();
    auto childNode = tabsNode->GetChildAtIndex(1);
    ASSERT_NE(childNode, nullptr);
    EXPECT_NE(childNode->GetTag(), V2::DIVIDER_ETS_TAG);
}

/**
 * @tc.name: TabsModelToJsonValue001
 * @tc.desc: Test tabs ToJsonValue when host has not child.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelToJsonValue001, TestSize.Level2)
{
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto tabsNode =
        TabsModelNG::GetOrCreateTabsNode(V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
    ASSERT_NE(tabsNode, nullptr);
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    tabsNode->ToJsonValue(json);
    ASSERT_NE(json, nullptr);
    auto dividerJson = json->GetValue("divider");
    ASSERT_NE(dividerJson, nullptr);
    EXPECT_TRUE(dividerJson->IsNull());
}

/**
 * @tc.name: TabContentModelSetIndicator001
 * @tc.desc: test SetIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelSetIndicator001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);

    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TabTheme>()));

    TabContentModelNG tabContentModel;
    IndicatorStyle indicator;
    Color color = Color::BLACK;
    Dimension height = 10.0_vp;
    Dimension width = 20.0_vp;
    Dimension borderRadius = 2.0_vp;
    Dimension marginTop = 3.0_vp;

    indicator.color = color;
    indicator.height = height;
    indicator.width = width;
    indicator.borderRadius = borderRadius;
    indicator.marginTop = marginTop;

    tabContentModel.Create();
    tabContentModel.SetIndicator(indicator);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    EXPECT_EQ(tabContentFrameNode->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);

    EXPECT_EQ(tabContentPattern->GetIndicatorStyle().color.ColorToString(), color.ColorToString());
    EXPECT_EQ(tabContentPattern->GetIndicatorStyle().height.ToString(), height.ToString());
    EXPECT_EQ(tabContentPattern->GetIndicatorStyle().width.ToString(), width.ToString());
    EXPECT_EQ(tabContentPattern->GetIndicatorStyle().borderRadius.ToString(), borderRadius.ToString());
    EXPECT_EQ(tabContentPattern->GetIndicatorStyle().marginTop.ToString(), marginTop.ToString());
}

/**
 * @tc.name: TabContentModelSetIndicator002
 * @tc.desc: test SetIndicator with getTheme once
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelSetIndicator002, TestSize.Level1)
{
    MockPipelineContextGetTheme();

    TabContentModelNG tabContentModel;
    IndicatorStyle indicator;
    Dimension width = 0.0_vp;
    Dimension borderRadius = 0.0_vp;

    tabContentModel.Create();
    tabContentModel.SetIndicator(indicator);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    EXPECT_EQ(tabContentFrameNode->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);

    EXPECT_EQ(tabContentPattern->GetIndicatorStyle().width.ToString(), width.ToString());
    EXPECT_EQ(tabContentPattern->GetIndicatorStyle().borderRadius.ToString(), borderRadius.ToString());
}

/**
 * @tc.name: TabContentModelCreate(std::function<void()>&& deepRenderFunc)
 * @tc.desc: Test Create(std::function<void()>&& deepRenderFunc)
 * @tc.type：FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelCreate001, TestSize.Level1)
{
    MockPipelineContextGetTheme();

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
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);

    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TabTheme>()));
    TabContentModelNG tabContentModel;
    BoardStyle boardStyle;
    boardStyle.borderRadius = 10.0_vp;
    tabContentModel.Create();
    tabContentModel.SetBoard(boardStyle);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    EXPECT_EQ(tabContentFrameNode->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    auto board = tabContentPattern->GetBoardStyle();
    EXPECT_EQ(board.borderRadius.ToString(), boardStyle.borderRadius.ToString());
}

/**
 * @tc.name: TabContentModelSetSubTabBorderRadius002
 * @tc.desc: test SetSubTabBorderRadius with getTheme once
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelSetSubTabBorderRadius002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    TabContentModelNG tabContentModel;
    BoardStyle boardStyle;
    boardStyle.borderRadius = 10.0_vp;
    tabContentModel.Create();
    tabContentModel.SetBoard(boardStyle);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    EXPECT_EQ(tabContentFrameNode->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    auto board = tabContentPattern->GetBoardStyle();
    EXPECT_EQ(board.borderRadius.ToString(), boardStyle.borderRadius.ToString());
}

/**
 * @tc.name: TabContentModelSetSelectedMode001
 * @tc.desc: test SetSelectedMode
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelSetSelectedMode001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    TabContentModelNG tabContentModel;
    SelectedMode selectedMode = SelectedMode::INDICATOR;
    tabContentModel.Create();
    tabContentModel.SetSelectedMode(selectedMode);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    EXPECT_EQ(tabContentFrameNode->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_EQ(tabContentPattern->GetSelectedMode(), selectedMode);
}

/**
 * @tc.name: TabContentModelSetLabelStyle001
 * @tc.desc: test SetLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelSetLabelStyle001, TestSize.Level1)
{
    MockPipelineContextGetTheme();

    TabContentModelNG tabContentModel;
    LabelStyle labelStyle;
    tabContentModel.Create();
    tabContentModel.SetLabelStyle(labelStyle);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    EXPECT_EQ(tabContentFrameNode->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().textOverflow, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().maxLines, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().minFontSize, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().maxFontSize, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().heightAdaptivePolicy, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().fontSize, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().fontWeight, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().fontFamily, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().fontStyle, std::nullopt);
}

/**
 * @tc.name: TabContentModelSetLabelStyle002
 * @tc.desc: test SetLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelSetLabelStyle002, TestSize.Level1)
{
    MockPipelineContextGetTheme();

    TabContentModelNG tabContentModel;
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
    tabContentModel.Create();
    tabContentModel.SetLabelStyle(labelStyle);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    EXPECT_EQ(tabContentFrameNode->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().textOverflow, labelStyle.textOverflow);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().maxLines, labelStyle.maxLines);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().minFontSize->ToString(), labelStyle.minFontSize->ToString());
    EXPECT_EQ(tabContentPattern->GetLabelStyle().maxFontSize->ToString(), labelStyle.maxFontSize->ToString());
    EXPECT_EQ(tabContentPattern->GetLabelStyle().heightAdaptivePolicy, labelStyle.heightAdaptivePolicy);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().fontSize->ToString(), labelStyle.fontSize->ToString());
    EXPECT_EQ(tabContentPattern->GetLabelStyle().fontWeight, labelStyle.fontWeight);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().fontFamily, labelStyle.fontFamily);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().fontStyle, labelStyle.fontStyle);
}

/**
 * @tc.name: TabContentModelUpdateLabelStyle001
 * @tc.desc: test UpdateLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelUpdateLabelStyle001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    auto layoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();

    TabContentModelNG tabContentModel;
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
    tabContentModel.Create();
    tabContentModel.UpdateLabelStyle(labelStyle, layoutProperty);
    EXPECT_EQ(layoutProperty->GetTextOverflow(), labelStyle.textOverflow);
    EXPECT_EQ(layoutProperty->GetMaxLines(), labelStyle.maxLines);
    EXPECT_EQ(layoutProperty->GetAdaptMinFontSize()->ToString(), labelStyle.minFontSize->ToString());
    EXPECT_EQ(layoutProperty->GetAdaptMaxFontSize()->ToString(), labelStyle.maxFontSize->ToString());
    EXPECT_EQ(layoutProperty->GetHeightAdaptivePolicy(), labelStyle.heightAdaptivePolicy);
    EXPECT_EQ(layoutProperty->GetFontSize()->ToString(), labelStyle.fontSize->ToString());
    EXPECT_EQ(layoutProperty->GetFontWeight(), labelStyle.fontWeight);
    EXPECT_EQ(layoutProperty->GetFontFamily(), labelStyle.fontFamily);
    EXPECT_EQ(layoutProperty->GetItalicFontStyle(), labelStyle.fontStyle);
}

/**
 * @tc.name: TabContentModelToJsonValue001
 * @tc.desc: test SetIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelToJsonValue001, TestSize.Level1)
{
    MockPipelineContextGetTheme();

    LabelStyle labelStyle;
    labelStyle.textOverflow = TextOverflow::CLIP;
    labelStyle.maxLines = 0;
    labelStyle.minFontSize = 0.0_vp;
    labelStyle.maxFontSize = 0.0_vp;
    labelStyle.heightAdaptivePolicy = TextHeightAdaptivePolicy::MAX_LINES_FIRST;
    labelStyle.fontSize = 0.0_vp;
    labelStyle.fontWeight = FontWeight::NORMAL;
    labelStyle.fontFamily = { "unknown", "unknow2" };

    TabContentModelNG tabContentModel;
    tabContentModel.Create();
    tabContentModel.SetLabelStyle(labelStyle);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    EXPECT_EQ(tabContentFrameNode->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);
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
    MockPipelineContextGetTheme();
    const std::string text_test = "text_test";
    TabContentModelNG tabContentModel;
    SelectedMode selectedMode = SelectedMode::INDICATOR;
    tabContentModel.Create();
    tabContentModel.SetSelectedMode(selectedMode);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    EXPECT_EQ(tabContentFrameNode->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    tabContentFrameNode->GetTabBarItemId();
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    tabContentFrameNode->MountToParent(swiperNode);
    tabContentPattern->SetTabBar(text_test, "", nullptr);
    EXPECT_EQ(tabContentPattern->GetTabBarParam().GetText(), text_test);
    tabContentModel.AddTabBarItem(tabContentFrameNode, DEFAULT_NODE_SLOT, true);
    EXPECT_EQ(tabContentPattern->GetSelectedMode(), selectedMode);

    TabContentModelNG tabContentModel2;
    tabContentModel2.Create();
    tabContentModel2.SetSelectedMode(selectedMode);
    auto tabContentFrameNode2 = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode2, nullptr);
    EXPECT_EQ(tabContentFrameNode2->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);
    auto tabContentPattern2 = tabContentFrameNode2->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern2, nullptr);
    tabContentFrameNode2->MountToParent(swiperNode);
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
    MockPipelineContextGetTheme();
    TabsModelNG tabsModel;
    bool fadingEdge = true;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    tabsModel.SetFadingEdge(fadingEdge);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsFrameNode, nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    auto layoutAlgorithm = tabBarPattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    DirtySwapConfig config;
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(tabBarNode, tabBarNode->GetGeometryNode(), tabBarLayoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);
    auto algorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm, false, false);
    ASSERT_NE(algorithmWrapper, nullptr);

    layoutWrapper->SetLayoutAlgorithm(algorithmWrapper);
    EXPECT_EQ(layoutWrapper->layoutAlgorithm_, algorithmWrapper);
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(tabBarPattern->indicator_, 0);
}

/**
 * @tc.name: TabBarPatternUpdateSubTabBoard001
 * @tc.desc: test UpdateSubTabBoard
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternUpdateSubTabBoard001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    const std::string text_test = "text_test";

    TabContentModelNG tabContentModel;

    SelectedMode selectedMode = SelectedMode::INDICATOR;
    tabContentModel.Create();
    tabContentModel.SetSelectedMode(selectedMode);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    EXPECT_EQ(tabContentFrameNode->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarPattern->UpdateSubTabBoard();

    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_EQ(tabContentPattern->GetSelectedMode(), selectedMode);
    tabContentFrameNode->GetTabBarItemId();

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    EXPECT_EQ(swiperNode->GetTag(), V2::SWIPER_ETS_TAG);
    tabContentFrameNode->MountToParent(swiperNode);
    tabContentPattern->SetTabBar(text_test, "", nullptr);
    EXPECT_EQ(tabContentPattern->GetTabBarParam().GetText(), text_test);

    tabContentModel.AddTabBarItem(tabContentFrameNode, DEFAULT_NODE_SLOT, true);
    tabBarPattern->UpdateSubTabBoard();

    tabBarPattern->SetSelectedMode(SelectedMode::BOARD, 0);
    EXPECT_EQ(tabBarPattern->selectedModes_[0], SelectedMode::BOARD);
    tabBarPattern->UpdateSubTabBoard();

    tabBarPattern->SetSelectedMode(SelectedMode::INDICATOR, 0);
    EXPECT_EQ(tabBarPattern->selectedModes_[0], SelectedMode::INDICATOR);
    TabContentModelNG tabContentModel2;
    tabContentModel2.Create();
    tabContentModel2.SetSelectedMode(selectedMode);
    tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    EXPECT_EQ(tabContentFrameNode->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);
    tabContentFrameNode->MountToParent(swiperNode);
    tabContentPattern->SetTabBar(text_test, "", nullptr);
    EXPECT_EQ(tabContentPattern->GetTabBarParam().GetText(), text_test);
    tabContentModel.AddTabBarItem(tabContentFrameNode, DEFAULT_NODE_SLOT, true);
    tabBarPattern->UpdateSubTabBoard();
    EXPECT_EQ(tabBarPattern->indicator_, 0);

    tabBarPattern->indicator_ = 1;
    tabBarPattern->UpdateSubTabBoard();
    EXPECT_EQ(tabBarPattern->indicator_, 1);

    IndicatorStyle style;
    tabBarPattern->SetIndicatorStyle(style, 1);
    tabBarPattern->UpdateSubTabBoard();
    EXPECT_EQ(tabBarPattern->indicator_, 1);

    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    tabBarLayoutProperty->UpdateAxis(Axis::VERTICAL);
    tabBarPattern->UpdateSubTabBoard();
    EXPECT_EQ(tabBarPattern->indicator_, 1);

    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern->UpdateSubTabBoard();
    EXPECT_EQ(tabBarPattern->indicator_, 1);
}

/**
 * @tc.name: TabBarPatternUpdateGradientRegions001
 * @tc.desc: test UpdateGradientRegions
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternUpdateGradientRegions001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    const std::string text_test = "text_test";

    TabContentModelNG tabContentModel;

    SelectedMode selectedMode = SelectedMode::INDICATOR;
    tabContentModel.Create();
    tabContentModel.SetSelectedMode(selectedMode);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    EXPECT_EQ(tabContentFrameNode->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    tabsModel.SetTabBarMode(TabBarMode::SCROLLABLE);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    EXPECT_EQ(tabsNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_EQ(tabContentPattern->GetSelectedMode(), selectedMode);
    tabContentFrameNode->GetTabBarItemId();

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    EXPECT_EQ(swiperNode->GetTag(), V2::SWIPER_ETS_TAG);
    tabContentFrameNode->MountToParent(swiperNode);
    tabContentPattern->SetTabBar(text_test, "", nullptr);
    EXPECT_EQ(tabContentPattern->GetTabBarParam().GetText(), text_test);
    tabContentModel.AddTabBarItem(tabContentFrameNode, DEFAULT_NODE_SLOT, true);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);

    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    tabBarLayoutProperty->UpdateAxis(Axis::VERTICAL);
    EXPECT_EQ(tabBarLayoutProperty->GetAxisValue(), Axis::VERTICAL);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarPattern->tabItemOffsets_ = { { -1.0f, -1.0f } };
    tabBarPattern->childrenMainSize_ = 10.0f;
    tabBarPattern->UpdateGradientRegions();
    EXPECT_TRUE(tabBarPattern->gradientRegions_[2]);

    tabBarPattern->tabItemOffsets_ = { { 1.0f, 1.0f } };
    tabBarPattern->childrenMainSize_ = 10.0f;
    tabBarPattern->UpdateGradientRegions();
    EXPECT_FALSE(tabBarPattern->gradientRegions_[2]);

    tabBarPattern->tabItemOffsets_ = { { 10.0f, 10.0f } };
    tabBarPattern->childrenMainSize_ = 10.0f;
    tabBarPattern->UpdateGradientRegions();
    EXPECT_TRUE(tabBarPattern->gradientRegions_[3]);

    tabBarPattern->tabItemOffsets_ = { { -10.0f, -10.0f } };
    tabBarPattern->childrenMainSize_ = 5.0f;
    tabBarPattern->UpdateGradientRegions();
    EXPECT_FALSE(tabBarPattern->gradientRegions_[3]);

    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    EXPECT_EQ(tabBarLayoutProperty->GetAxisValue(), Axis::HORIZONTAL);

    tabBarPattern->tabItemOffsets_ = { { -1.0f, -1.0f } };
    tabBarPattern->childrenMainSize_ = 10.0f;
    tabBarPattern->UpdateGradientRegions();
    EXPECT_TRUE(tabBarPattern->gradientRegions_[0]);

    tabBarPattern->tabItemOffsets_ = { { 1.0f, 1.0f } };
    tabBarPattern->childrenMainSize_ = 10.0f;
    tabBarPattern->UpdateGradientRegions();
    EXPECT_FALSE(tabBarPattern->gradientRegions_[0]);

    tabBarPattern->tabItemOffsets_ = { { 10.0f, 10.0f } };
    tabBarPattern->childrenMainSize_ = 10.0f;
    tabBarPattern->UpdateGradientRegions();
    EXPECT_TRUE(tabBarPattern->gradientRegions_[1]);

    tabBarPattern->tabItemOffsets_ = { { -10.0f, -10.0f } };
    tabBarPattern->childrenMainSize_ = 5.0f;
    tabBarPattern->UpdateGradientRegions();
    EXPECT_FALSE(tabBarPattern->gradientRegions_[1]);
}

/**
 * @tc.name: TabBarPatternSetSelectedMode001
 * @tc.desc: test SetSelectedMode
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternSetSelectedMode001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    TabsModelNG tabsModel;
    bool fadingEdge = true;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    tabsModel.SetFadingEdge(fadingEdge);

    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsFrameNode, nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);
    auto tabBarPaintProperty = tabBarNode->GetPaintProperty<TabBarPaintProperty>();
    ASSERT_NE(tabBarPaintProperty, nullptr);
    EXPECT_EQ(tabBarPaintProperty->GetFadingEdgeValue(), fadingEdge);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarPattern->SetSelectedMode(SelectedMode::INDICATOR, 0);
    EXPECT_EQ(tabBarPattern->selectedModes_[0], SelectedMode::INDICATOR);
    tabBarPattern->SetSelectedMode(SelectedMode::INDICATOR, 1);
    EXPECT_EQ(tabBarPattern->selectedModes_[1], SelectedMode::INDICATOR);
    tabBarPattern->SetSelectedMode(SelectedMode::INDICATOR, 0);
    EXPECT_EQ(tabBarPattern->selectedModes_[0], SelectedMode::INDICATOR);

    IndicatorStyle indicator;
    tabBarPattern->SetIndicatorStyle(indicator, 0);
    EXPECT_EQ(tabBarPattern->indicatorStyles_[0], indicator);
    tabBarPattern->SetIndicatorStyle(indicator, 1);
    EXPECT_EQ(tabBarPattern->indicatorStyles_[1], indicator);
    tabBarPattern->SetIndicatorStyle(indicator, 0);
    EXPECT_EQ(tabBarPattern->indicatorStyles_[0], indicator);

    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    EXPECT_EQ(tabBarPattern->tabBarStyles_[1], TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);

    auto selectedMode = tabBarPattern->GetSelectedMode();
    EXPECT_EQ(selectedMode, SelectedMode::INDICATOR);
}

/**
 * @tc.name: TabBarPatternUpdateIndicator001
 * @tc.desc: test UpdateIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternUpdateIndicator001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    TabsModelNG tabsModel;
    bool fadingEdge = true;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    tabsModel.SetFadingEdge(fadingEdge);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsFrameNode, nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);

    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);

    auto tabBarPaintProperty = tabBarNode->GetPaintProperty<TabBarPaintProperty>();
    ASSERT_NE(tabBarPaintProperty, nullptr);
    EXPECT_EQ(tabBarPaintProperty->GetFadingEdgeValue(), fadingEdge);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern->tabBarStyles_[0], TabBarStyle::BOTTOMTABBATSTYLE);
    tabBarPattern->UpdateIndicator(0);
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern->UpdateIndicator(0);
    tabBarPattern->SetTabBarStyle(TabBarStyle::NOSTYLE, 0);
    EXPECT_EQ(tabBarPattern->tabBarStyles_[0], TabBarStyle::NOSTYLE);
    tabBarPattern->UpdateIndicator(0);

    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern->tabBarStyles_[0], TabBarStyle::BOTTOMTABBATSTYLE);

    tabBarLayoutProperty->UpdateAxis(Axis::VERTICAL);
    EXPECT_EQ(tabBarLayoutProperty->GetAxisValue(), Axis::VERTICAL);
    tabBarPattern->tabBarType_[0] = true;
    tabBarPattern->UpdateIndicator(0);

    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);

    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    EXPECT_EQ(tabBarLayoutProperty->GetAxisValue(), Axis::HORIZONTAL);
    tabBarPattern->tabBarType_[0] = false;
    tabBarPattern->UpdateIndicator(0);
    EXPECT_EQ(tabBarPattern->indicator_, 0);

    tabBarPattern->indicator_ = 1;
    tabBarPattern->UpdateIndicator(0);
    EXPECT_EQ(tabBarPattern->indicator_, 1);
}

/**
 * @tc.name: TabBarPatternPlayPressAnimation001
 * @tc.desc: test PlayPressAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternPlayPressAnimation001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    TabsModelNG tabsModel;
    bool fadingEdge = true;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    tabsModel.SetFadingEdge(fadingEdge);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsFrameNode, nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);

    auto tabBarPaintProperty = tabBarNode->GetPaintProperty<TabBarPaintProperty>();
    ASSERT_NE(tabBarPaintProperty, nullptr);
    EXPECT_EQ(tabBarPaintProperty->GetFadingEdgeValue(), fadingEdge);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    IndicatorStyle indicatorStyle;
    tabBarPattern->SetIndicatorStyle(indicatorStyle, 0);
    EXPECT_EQ(tabBarPattern->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern->SetSelectedMode(SelectedMode::BOARD, 0);
    EXPECT_EQ(tabBarPattern->selectedModes_[0], SelectedMode::BOARD);
    tabBarPattern->PlayPressAnimation(0, Color::BLACK, AnimationType::PRESS);

    tabBarPattern->SetSelectedMode(SelectedMode::INDICATOR, 0);
    EXPECT_EQ(tabBarPattern->selectedModes_[0], SelectedMode::INDICATOR);
    tabBarPattern->PlayPressAnimation(0, Color::BLACK, AnimationType::PRESS);
    EXPECT_EQ(tabBarPattern->indicator_, 0);

    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);

    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern->SetSelectedMode(SelectedMode::BOARD, 0);
    EXPECT_EQ(tabBarPattern->selectedModes_[0], SelectedMode::BOARD);
    tabBarPattern->PlayPressAnimation(0, Color::TRANSPARENT, AnimationType::PRESS);
    EXPECT_EQ(tabBarPattern->indicator_, 0);

    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern->SetSelectedMode(SelectedMode::BOARD, 0);
    EXPECT_EQ(tabBarPattern->selectedModes_[0], SelectedMode::BOARD);
    tabBarPattern->PlayPressAnimation(0, Color::BLACK, AnimationType::PRESS);
    EXPECT_EQ(tabBarPattern->indicator_, 0);

    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern->SetSelectedMode(SelectedMode::INDICATOR, 0);
    EXPECT_EQ(tabBarPattern->selectedModes_[0], SelectedMode::INDICATOR);
    tabBarPattern->PlayPressAnimation(0, Color::TRANSPARENT, AnimationType::PRESS);
    EXPECT_EQ(tabBarPattern->indicator_, 0);

    tabBarLayoutProperty->UpdateAxis(Axis::VERTICAL);
    tabBarPattern->SetSelectedMode(SelectedMode::BOARD, 0);
    EXPECT_EQ(tabBarPattern->selectedModes_[0], SelectedMode::BOARD);
    tabBarPattern->PlayPressAnimation(0, Color::TRANSPARENT, AnimationType::PRESS);
    EXPECT_EQ(tabBarPattern->indicator_, 0);
}

/**
 * @tc.name: TabBarPatternHandleClick001
 * @tc.desc: test HandleClick
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleClick001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    const std::string text_test = "text_test";

    TabContentModelNG tabContentModel;

    SelectedMode selectedMode = SelectedMode::INDICATOR;
    tabContentModel.Create();
    tabContentModel.SetSelectedMode(selectedMode);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    EXPECT_EQ(tabContentFrameNode->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    EXPECT_EQ(tabsNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_EQ(tabContentPattern->GetSelectedMode(), SelectedMode::INDICATOR);
    tabContentFrameNode->GetTabBarItemId();

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    EXPECT_EQ(swiperNode->GetTag(), V2::SWIPER_ETS_TAG);
    tabContentFrameNode->MountToParent(swiperNode);
    tabContentPattern->SetTabBar(text_test, "", nullptr);
    EXPECT_EQ(tabContentPattern->GetTabBarParam().GetText(), text_test);
    tabContentModel.AddTabBarItem(tabContentFrameNode, DEFAULT_NODE_SLOT, true);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    tabBarLayoutProperty->UpdateAxis(Axis::VERTICAL);
    EXPECT_EQ(tabBarLayoutProperty->GetAxisValue(), Axis::VERTICAL);
    tabBarPattern->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    tabBarPattern->tabItemOffsets_ = { { 0.0f, 0.0f }, { 10.0f, 10.0f } };

    GestureEvent info;
    Offset offset(1, 1);
    info.SetLocalLocation(offset);
    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern->HandleClick(info);
    EXPECT_EQ(tabBarLayoutProperty->GetAxisValue(), Axis::HORIZONTAL);

    tabBarPattern->indicator_ = 1;
    tabBarPattern->HandleClick(info);
    EXPECT_EQ(tabBarPattern->indicator_, 1);
}

/**
 * @tc.name: TabBarPatternHandleSubTabBarClick001
 * @tc.desc: test HandleSubTabBarClick
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleSubTabBarClick001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    const std::string text_test = "text_test";

    TabContentModelNG tabContentModel;

    SelectedMode selectedMode = SelectedMode::INDICATOR;
    tabContentModel.Create();
    tabContentModel.SetSelectedMode(selectedMode);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    EXPECT_EQ(tabContentFrameNode->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    tabContentFrameNode->GetTabBarItemId();

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    EXPECT_EQ(swiperNode->GetTag(), V2::SWIPER_ETS_TAG);
    tabContentFrameNode->MountToParent(swiperNode);
    tabContentPattern->SetTabBar(text_test, "", nullptr);
    EXPECT_EQ(tabContentPattern->GetTabBarParam().GetText(), text_test);

    tabContentPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    EXPECT_EQ(tabContentPattern->GetTabBarStyle(), TabBarStyle::SUBTABBATSTYLE);
    tabContentModel.AddTabBarItem(tabContentFrameNode, DEFAULT_NODE_SLOT, true);
    tabContentPattern->SetTabBar(text_test, "", nullptr);
    EXPECT_EQ(tabContentPattern->GetTabBarParam().GetText(), text_test);

    tabContentPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    EXPECT_EQ(tabContentPattern->GetTabBarStyle(), TabBarStyle::SUBTABBATSTYLE);
    tabContentModel.AddTabBarItem(tabContentFrameNode, DEFAULT_NODE_SLOT, true);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    tabBarLayoutProperty->UpdateAxis(Axis::VERTICAL);
    EXPECT_EQ(tabBarLayoutProperty->GetAxisValue(), Axis::VERTICAL);
    tabBarPattern->tabItemOffsets_ = { { 0.0f, 0.0f }, { 10.0f, 10.0f } };

    GestureEvent info;
    Offset offset(1, 1);
    info.SetLocalLocation(offset);
    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    EXPECT_EQ(tabBarLayoutProperty->GetAxisValue(), Axis::HORIZONTAL);
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    EXPECT_EQ(tabBarPattern->tabBarStyles_[1], TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern->indicator_ = 1;
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern->HandleClick(info);

    tabBarLayoutProperty->UpdateAxis(Axis::VERTICAL);
    EXPECT_EQ(tabBarLayoutProperty->GetAxisValue(), Axis::VERTICAL);
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    EXPECT_EQ(tabBarPattern->tabBarStyles_[1], TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern->indicator_ = 1;
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern->HandleClick(info);

    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    EXPECT_EQ(tabBarLayoutProperty->GetAxisValue(), Axis::HORIZONTAL);
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    EXPECT_EQ(tabBarPattern->tabBarStyles_[1], TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern->indicator_ = 1;
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern->tabBarStyles_[0], TabBarStyle::BOTTOMTABBATSTYLE);
    tabBarPattern->HandleClick(info);

    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 1);
    EXPECT_EQ(tabBarPattern->tabBarStyles_[1], TabBarStyle::BOTTOMTABBATSTYLE);
    tabBarPattern->indicator_ = 1;
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern->HandleClick(info);

    tabBarPattern->indicator_ = 1;
    tabBarPattern->HandleSubTabBarClick(tabBarLayoutProperty, 1);
    EXPECT_EQ(tabBarPattern->indicator_, 1);
    PipelineContext::GetCurrentContext()->SetThemeManager(nullptr);
}

/**
 * @tc.name: TabBarPatternGetIndicatorRect001
 * @tc.desc: test GetIndicatorRect
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternGetIndicatorRect001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    const std::string text_test = "text_test";

    TabContentModelNG tabContentModel;

    SelectedMode selectedMode = SelectedMode::INDICATOR;
    tabContentModel.Create();
    tabContentModel.SetSelectedMode(selectedMode);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    EXPECT_EQ(tabContentFrameNode->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_EQ(tabContentPattern->GetSelectedMode(), selectedMode);
    tabContentFrameNode->GetTabBarItemId();

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    EXPECT_EQ(swiperNode->GetTag(), V2::SWIPER_ETS_TAG);
    tabContentFrameNode->MountToParent(swiperNode);
    tabContentPattern->SetTabBar(text_test, "", nullptr);
    EXPECT_EQ(tabContentPattern->GetTabBarParam().GetText(), text_test);
    tabContentModel.AddTabBarItem(tabContentFrameNode, DEFAULT_NODE_SLOT, true);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    auto rect = tabBarLayoutProperty->GetIndicatorRect(0);
    EXPECT_EQ(rect.GetX(), 0);
}

/**
 * @tc.name: TabBarPatternGetSelectedMode001
 * @tc.desc: test GetSelectedMode
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternGetSelectedMode001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    const std::string text_test = "text_test";

    TabContentModelNG tabContentModel;

    SelectedMode selectedMode = SelectedMode::INDICATOR;
    tabContentModel.Create();
    tabContentModel.SetSelectedMode(selectedMode);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    EXPECT_EQ(tabContentFrameNode->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_EQ(tabContentPattern->GetSelectedMode(), selectedMode);
    tabContentFrameNode->GetTabBarItemId();

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    EXPECT_EQ(swiperNode->GetTag(), V2::SWIPER_ETS_TAG);
    tabContentFrameNode->MountToParent(swiperNode);
    tabContentPattern->SetTabBar(text_test, "", nullptr);
    EXPECT_EQ(tabContentPattern->GetTabBarParam().GetText(), text_test);
    tabContentModel.AddTabBarItem(tabContentFrameNode, DEFAULT_NODE_SLOT, true);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    tabBarPattern->indicator_ = 1;
    auto mode = tabBarPattern->GetSelectedMode();
    EXPECT_EQ(mode, selectedMode);
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
    SelectedMode selectedMode = SelectedMode::INDICATOR;
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    tabBarModifier->SetSelectedMode(selectedMode);
    ASSERT_NE(tabBarModifier->hasIndicator_, nullptr);
    EXPECT_TRUE(tabBarModifier->hasIndicator_->Get());
    tabBarModifier->hasIndicator_ = nullptr;
    tabBarModifier->SetSelectedMode(selectedMode);
    EXPECT_EQ(tabBarModifier->hasIndicator_, nullptr);
}

/**
 * @tc.name: TabBarModifierOnDraw001
 * @tc.desc: test onDraw
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarModifierOnDraw001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    EXPECT_FALSE(tabBarModifier == nullptr);

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
    MockPipelineContextGetTheme();
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);

    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());

    ASSERT_NE(tabsFrameNode, nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabBarFrameNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarFrameNode, nullptr);
    EXPECT_EQ(tabBarFrameNode->GetTag(), V2::TAB_BAR_ETS_TAG);
    auto tabBarPattern = tabBarFrameNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto paintProperty = tabBarPattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    IndicatorStyle indicator;
    tabBarPattern->SetIndicatorStyle(indicator, 0);
    EXPECT_EQ(tabBarPattern->indicatorStyles_[0], indicator);
    SelectedMode selectedMode = SelectedMode::INDICATOR;
    tabBarPattern->SetSelectedMode(selectedMode, 0);
    EXPECT_EQ(tabBarPattern->selectedModes_[0], selectedMode);
    auto paintMethod = tabBarPattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod, nullptr);

    auto paintMethod2 = tabBarPattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod2, nullptr);

    PaintWrapper paintWrapper(tabBarFrameNode->GetRenderContext(), tabBarFrameNode->GetGeometryNode(), paintProperty);
    auto drawFunction = paintMethod->GetForegroundDrawFunction(&paintWrapper);
    ASSERT_NE(drawFunction, nullptr);

    paintProperty = tabBarPattern->CreatePaintProperty();
    auto tabBarPaintProperty = AceType::DynamicCast<TabBarPaintProperty>(paintProperty);
    tabBarPaintProperty->UpdateFadingEdge(false);
    EXPECT_FALSE(tabBarPaintProperty->GetFadingEdgeValue());
    PaintWrapper paintWrapper2(tabBarFrameNode->GetRenderContext(), tabBarFrameNode->GetGeometryNode(), paintProperty);
    drawFunction = paintMethod->GetForegroundDrawFunction(&paintWrapper2);
    ASSERT_EQ(drawFunction, nullptr);
    auto clone = paintProperty->Clone();
    EXPECT_NE(clone, nullptr);
}

/**
 * @tc.name: TabBarPaintMethodGetContentModifier001
 * @tc.desc: test GetContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPaintMethodGetContentModifier001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);

    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());

    ASSERT_NE(tabsFrameNode, nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabBarFrameNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarFrameNode, nullptr);
    EXPECT_EQ(tabBarFrameNode->GetTag(), V2::TAB_BAR_ETS_TAG);
    auto tabBarPattern = tabBarFrameNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto paintProperty = tabBarPattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    IndicatorStyle indicator;
    tabBarPattern->SetIndicatorStyle(indicator, 0);
    EXPECT_EQ(tabBarPattern->indicatorStyles_[0], indicator);
    SelectedMode selectedMode = SelectedMode::INDICATOR;
    tabBarPattern->SetSelectedMode(selectedMode, 0);
    EXPECT_EQ(tabBarPattern->selectedModes_[0], selectedMode);
    auto paintMethod = tabBarPattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod, nullptr);

    tabBarPattern->indicator_ = 1;
    auto paintMethod2 = tabBarPattern->CreateNodePaintMethod();
    ASSERT_EQ(paintMethod2, nullptr);

    IndicatorStyle style;
    tabBarPattern->SetIndicatorStyle(style, 1);
    auto paintMethod3 = tabBarPattern->CreateNodePaintMethod();
    ASSERT_EQ(paintMethod3, nullptr);

    PaintWrapper paintWrapper(tabBarFrameNode->GetRenderContext(), tabBarFrameNode->GetGeometryNode(), paintProperty);
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
    MockPipelineContextGetTheme();
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);

    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());

    ASSERT_NE(tabsFrameNode, nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabBarFrameNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarFrameNode, nullptr);
    EXPECT_EQ(tabBarFrameNode->GetTag(), V2::TAB_BAR_ETS_TAG);
    auto tabBarPattern = tabBarFrameNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto paintProperty = tabBarPattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    IndicatorStyle indicator;
    tabBarPattern->SetIndicatorStyle(indicator, 0);
    EXPECT_EQ(tabBarPattern->indicatorStyles_[0], indicator);
    SelectedMode selectedMode = SelectedMode::INDICATOR;
    tabBarPattern->SetSelectedMode(selectedMode, 0);
    EXPECT_EQ(tabBarPattern->selectedModes_[0], selectedMode);
    auto paintMethod = tabBarPattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod, nullptr);

    PaintWrapper paintWrapper(tabBarFrameNode->GetRenderContext(), tabBarFrameNode->GetGeometryNode(), paintProperty);
    paintMethod->UpdateContentModifier(&paintWrapper);
    auto tabBarPaintMethod = Ace::AceType::DynamicCast<TabBarPaintMethod>(paintMethod);
    ASSERT_NE(tabBarPaintMethod, nullptr);
    EXPECT_NE(tabBarPaintMethod->tabBarModifier_, nullptr);

    PaintWrapper paintWrapper2(tabBarFrameNode->GetRenderContext(), tabBarFrameNode->GetGeometryNode(), nullptr);
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
    MockPipelineContextGetTheme();
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);

    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());

    ASSERT_NE(tabsFrameNode, nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabBarFrameNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarFrameNode, nullptr);
    EXPECT_EQ(tabBarFrameNode->GetTag(), V2::TAB_BAR_ETS_TAG);
    auto tabBarPattern = tabBarFrameNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto paintProperty = tabBarPattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    IndicatorStyle indicator;
    tabBarPattern->SetIndicatorStyle(indicator, 0);
    SelectedMode selectedMode = SelectedMode::INDICATOR;
    EXPECT_EQ(tabBarPattern->indicatorStyles_[0], indicator);
    tabBarPattern->SetSelectedMode(selectedMode, 0);
    EXPECT_EQ(tabBarPattern->selectedModes_[0], selectedMode);
    std::vector<bool> gradientRegions = { true, true, true, true, true };
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    auto paintMethod = AceType::MakeRefPtr<TabBarPaintMethod>(
        tabBarModifier, gradientRegions, Color::BLACK, indicator, 0.0, selectedMode);
    ASSERT_NE(paintMethod, nullptr);

    PaintWrapper paintWrapper(tabBarFrameNode->GetRenderContext(), tabBarFrameNode->GetGeometryNode(), paintProperty);
    auto drawFunction = paintMethod->GetForegroundDrawFunction(&paintWrapper);
    ASSERT_NE(drawFunction, nullptr);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRect(_)).WillRepeatedly(Return());
    drawFunction(rsCanvas);
    EXPECT_TRUE(paintMethod->gradientRegions_[0]);

    gradientRegions[0] = false;
    paintMethod = AceType::MakeRefPtr<TabBarPaintMethod>(
        tabBarModifier, gradientRegions, Color::BLACK, indicator, 0.0, selectedMode);
    ASSERT_NE(paintMethod, nullptr);
    PaintWrapper paintWrapper2(tabBarFrameNode->GetRenderContext(), tabBarFrameNode->GetGeometryNode(), paintProperty);
    drawFunction = paintMethod->GetForegroundDrawFunction(&paintWrapper2);
    ASSERT_NE(drawFunction, nullptr);
    drawFunction(rsCanvas);
    EXPECT_FALSE(paintMethod->gradientRegions_[0]);
}

/**
 * @tc.name: TabBarAccessibilityPropertyTestNg001
 * @tc.desc: Test the ItemCount property of TabBar.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarAccessibilityPropertyTestNg001, TestSize.Level1)
{
    TabContentModelNG tabContentModel;
    tabContentModel.Create();
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    tabContentFrameNode->MountToParent(swiperNode);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);

    auto accessibilityProperty = tabBarNode->GetAccessibilityProperty<TabBarAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetCollectionItemCounts(), DEFAULT_ITEMCOUNT);
}

/**
 * @tc.name: TabBarAccessibilityPropertyTestNg002
 * @tc.desc: Test the IsScrollable property of TabBar.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarAccessibilityPropertyTestNg002, TestSize.Level1)
{
    TabContentModelNG tabContentModel1;
    tabContentModel1.Create();
    auto tabContentFrameNode1 =
        AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabContentFrameNode1, nullptr);

    TabContentModelNG tabContentModel2;
    tabContentModel2.Create();
    auto tabContentFrameNode2 =
        AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabContentFrameNode2, nullptr);

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    tabBarLayoutProperty->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto accessibilityProperty = tabBarNode->GetAccessibilityProperty<TabBarAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_FALSE(accessibilityProperty->IsScrollable());

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    tabContentFrameNode1->MountToParent(swiperNode);
    tabContentFrameNode2->MountToParent(swiperNode);
    EXPECT_TRUE(accessibilityProperty->IsScrollable());

    tabBarLayoutProperty->UpdateTabBarMode(TabBarMode::FIXED);
    EXPECT_FALSE(accessibilityProperty->IsScrollable());

    tabBarLayoutProperty->UpdateTabBarMode(TabBarMode::FIXED_START);
    EXPECT_FALSE(accessibilityProperty->IsScrollable());
}

/**
 * @tc.name: TabBarAccessibilityPropertyTestNg003
 * @tc.desc: Test the index properties of tabbar.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarAccessibilityPropertyTestNg003, TestSize.Level1)
{
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarAccessibilityProperty = tabBarNode->GetAccessibilityProperty<TabBarAccessibilityProperty>();
    ASSERT_NE(tabBarAccessibilityProperty, nullptr);
    EXPECT_EQ(tabBarAccessibilityProperty->GetBeginIndex(), DEFAULT_INDEX);
    EXPECT_EQ(tabBarAccessibilityProperty->GetCurrentIndex(), DEFAULT_INDEX);
    EXPECT_EQ(tabBarAccessibilityProperty->GetEndIndex(), DEFAULT_INDEX);

    TabContentModelNG tabContentModel;
    tabContentModel.Create();
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    tabContentFrameNode->MountToParent(swiperNode);

    auto pattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetIndicator(CURRENT_INDEX);

    EXPECT_EQ(tabBarAccessibilityProperty->GetBeginIndex(), BEGIN_INDEX);
    EXPECT_EQ(tabBarAccessibilityProperty->GetCurrentIndex(), CURRENT_INDEX);
    EXPECT_EQ(tabBarAccessibilityProperty->GetEndIndex(), END_INDEX);
}

/**
 * @tc.name: TabBarAccessibilityPropertyTestNg004
 * @tc.desc: Test the SupportActions property of tabbar.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarAccessibilityPropertyTestNg004, TestSize.Level1)
{
    TabContentModelNG tabContentModel1;
    tabContentModel1.Create();
    auto tabContentFrameNode1 =
        AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabContentFrameNode1, nullptr);

    TabContentModelNG tabContentModel2;
    tabContentModel2.Create();
    auto tabContentFrameNode2 =
        AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabContentFrameNode2, nullptr);

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    tabContentFrameNode1->MountToParent(swiperNode);
    tabContentFrameNode2->MountToParent(swiperNode);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    RefPtr<GeometryNode> geometryNode_ = Ace::Referenced::MakeRefPtr<GeometryNode>();
    tabBarNode->SetGeometryNode(geometryNode_);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    tabBarLayoutProperty->UpdateTabBarMode(TabBarMode::SCROLLABLE);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarPattern->currentOffset_ = DEFAULT_OFFSET;
    tabBarPattern->tabItemOffsets_.emplace_back(CURRENT_OFFSET);

    auto accessibilityProperty = tabBarNode->GetAccessibilityProperty<TabBarAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = accessibilityProperty->GetSupportAction();
    uint64_t actions = 0, exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, exptectActions);
}

/**
 * @tc.name: TabsModelSetBarOverlap001
 * @tc.desc: test SetBarOverlap
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelSetBarOverlap001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).WillRepeatedly(Return());

    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);

    auto layoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto barPaintProperty = tabBarNode->GetPaintProperty<TabBarPaintProperty>();
    ASSERT_NE(barPaintProperty, nullptr);

    /**
     * @tc.steps: steps2. SetBarOverlap true
     * @tc.expected: steps2. Check the BarOverlap property value
     */
    tabsModel.SetBarOverlap(true);
    EXPECT_TRUE(layoutProperty->GetBarOverlap().value());

    tabsModel.SetBarOverlap(false);
    EXPECT_FALSE(layoutProperty->GetBarOverlap().value());

    barPaintProperty->UpdateBarBackgroundColor(Color::RED);

    tabsModel.SetBarOverlap(true);
    EXPECT_TRUE(layoutProperty->GetBarOverlap().value());

    tabsModel.SetBarOverlap(false);
    EXPECT_FALSE(layoutProperty->GetBarOverlap().value());
}

/**
 * @tc.name: TabsEventHubChangeEvent001
 * @tc.desc: Tabs OnChangeEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsEventHubChangeEvent001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    TabsModelNG tabsModel;
    TabsItemDivider divider;
    Dimension strokeWidth = 10.0_vp;
    Dimension startMargin = 3.0_vp;
    Dimension endMargin = 4.0_vp;
    Color color = Color::BLACK;

    divider.strokeWidth = strokeWidth;
    divider.startMargin = startMargin;
    divider.endMargin = endMargin;
    divider.color = color;
    divider.isNull = false;

    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    tabsModel.SetOnChangeEvent([](const BaseEventInfo* info) {});
    tabsModel.SetDivider(divider);
    auto frameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->onIndexChangeEvent_, nullptr);
}

void BuildTabBar(const RefPtr<TabsNode>& tabsNode, TabBarStyle tabBarStyle1, TabBarStyle tabBarStyle2)
{
    const std::string text_test = "text_test";
    TabContentModelNG tabContentModel;
    SelectedMode selectedMode = SelectedMode::INDICATOR;
    tabContentModel.Create();
    tabContentModel.SetSelectedMode(selectedMode);
    auto tabContentFrameNode =
        AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabContentFrameNode, nullptr);
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    EXPECT_EQ(swiperNode->GetTag(), V2::SWIPER_ETS_TAG);
    tabContentFrameNode->MountToParent(swiperNode);
    tabContentPattern->SetTabBar(text_test, "", nullptr);
    tabContentPattern->SetTabBarStyle(tabBarStyle1);
    EXPECT_EQ(tabContentPattern->GetTabBarParam().GetText(), text_test);
    tabContentModel.AddTabBarItem(tabContentFrameNode, 0, false);

    TabContentModelNG tabContentModel2;
    tabContentModel2.Create();
    tabContentModel2.SetSelectedMode(selectedMode);
    auto tabContentFrameNode2 =
        AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabContentFrameNode2, nullptr);
    auto tabContentPattern2 = tabContentFrameNode2->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern2, nullptr);
    tabContentFrameNode2->MountToParent(swiperNode);
    tabContentPattern2->SetTabBar(text_test, "", nullptr);
    tabContentPattern2->SetTabBarStyle(tabBarStyle2);
    EXPECT_EQ(tabContentPattern2->GetTabBarParam().GetText(), text_test);
    tabContentModel2.AddTabBarItem(tabContentFrameNode2, 1, false);
}

/**
 * @tc.name: TabBarPatternHandleBottomTabBarChange001
 * @tc.desc: test HandleBottomTabBarChange
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleBottomTabBarChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build two bottom style tabbar.
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    BuildTabBar(tabsNode, TabBarStyle::BOTTOMTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE);

    /**
     * @tc.steps: step2. call HandleBottomTabBarChange function.
     * @tc.expected: step2. expect The function is run ok.
     */
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 1);
    tabBarPattern->indicator_ = 0;
    tabBarPattern->HandleBottomTabBarChange(1);
    EXPECT_EQ(tabBarPattern->indicator_, 0);
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
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    BuildTabBar(tabsNode, TabBarStyle::BOTTOMTABBATSTYLE, TabBarStyle::SUBTABBATSTYLE);

    /**
     * @tc.steps: step2. call HandleBottomTabBarChange function.
     * @tc.expected: step2. expect The function is run ok.
     */
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    tabBarPattern->indicator_ = 0;
    tabBarPattern->HandleBottomTabBarChange(1);
    EXPECT_EQ(tabBarPattern->indicator_, 0);
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
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 0, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    BuildTabBar(tabsNode, TabBarStyle::BOTTOMTABBATSTYLE, TabBarStyle::SUBTABBATSTYLE);

    /**
     * @tc.steps: step2. call HandleBottomTabBarChange function.
     * @tc.expected: step2. expect The function is run ok.
     */
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    tabBarPattern->indicator_ = 1;
    tabBarPattern->HandleBottomTabBarChange(0);
    EXPECT_EQ(tabBarPattern->indicator_, 1);
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
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    BuildTabBar(tabsNode, TabBarStyle::SUBTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE);

    /**
     * @tc.steps: step2. call HandleBottomTabBarChange function.
     * @tc.expected: step2. expect The function is run ok.
     */
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 1);
    tabBarPattern->indicator_ = 0;
    tabBarPattern->HandleBottomTabBarChange(0);
    EXPECT_EQ(tabBarPattern->indicator_, 0);
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
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    BuildTabBar(tabsNode, TabBarStyle::SUBTABBATSTYLE, TabBarStyle::SUBTABBATSTYLE);

    /**
     * @tc.steps: step2. call HandleBottomTabBarChange function.
     * @tc.expected: step2. expect The function is run ok.
     */
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    tabBarPattern->indicator_ = 0;
    tabBarPattern->HandleBottomTabBarChange(1);
    EXPECT_EQ(tabBarPattern->indicator_, 0);
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
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    BuildTabBar(tabsNode, TabBarStyle::BOTTOMTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE);

    /**
     * @tc.steps: step2. call MaskAnimationFinish function.
     * @tc.expected: step2. expect The function is run ok.
     */
    tabBarPattern->MaskAnimationFinish(tabBarNode, 0, true);
    EXPECT_NE(tabBarNode->GetChildAtIndex(0), nullptr);
    tabBarPattern->MaskAnimationFinish(tabBarNode, 1, false);
    EXPECT_NE(tabBarNode->GetChildAtIndex(1), nullptr);
    EXPECT_EQ(tabBarPattern->indicator_, 0);
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
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    BuildTabBar(tabsNode, TabBarStyle::BOTTOMTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE);

    /**
     * @tc.steps: step2. call MaskAnimationFinish function.
     * @tc.expected: step2. expect The function is run ok.
     */
    tabBarPattern->MaskAnimationFinish(tabBarNode, 0, false);
    EXPECT_NE(tabBarNode->GetChildAtIndex(0), nullptr);
    tabBarPattern->MaskAnimationFinish(tabBarNode, 1, true);
    EXPECT_NE(tabBarNode->GetChildAtIndex(1), nullptr);
    EXPECT_EQ(tabBarPattern->indicator_, 0);
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
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    BuildTabBar(tabsNode, TabBarStyle::BOTTOMTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE);

    /**
     * @tc.steps: step2. call ChangeMask function.
     * @tc.expected: step2. expect The function is run ok.
     */
    auto tabBarGeometryNode = tabBarNode->GetGeometryNode();
    ASSERT_NE(tabBarGeometryNode, nullptr);
    auto tabBarOffset = tabBarGeometryNode->GetMarginFrameOffset();
    tabBarPattern->ChangeMask(tabBarNode, 1.0f, tabBarOffset, 1.0f, TEST_MASK_MIDDLE_RADIUS_RATIO, true);
    tabBarPattern->ChangeMask(tabBarNode, 1.0f, tabBarOffset, 0.99f, TEST_MASK_MIDDLE_RADIUS_RATIO, false);
    EXPECT_EQ(tabBarPattern->indicator_, 0);

    auto selectedmaskPosition = tabBarNode->GetChildren().size() - TEST_SELECTED_MASK_COUNT;
    auto selectedMaskNode = AceType::DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(selectedmaskPosition));
    ASSERT_NE(selectedMaskNode, nullptr);
    auto selectedImageNode = AceType::DynamicCast<FrameNode>(selectedMaskNode->GetChildren().front());
    ASSERT_NE(selectedImageNode, nullptr);
    auto selectedImageRenderContext = selectedImageNode->GetRenderContext();
    ASSERT_NE(selectedImageRenderContext, nullptr);
    EXPECT_DOUBLE_EQ(selectedImageRenderContext->GetOpacity().value(), 1.0f);
    auto unselectedmaskPosition = tabBarNode->GetChildren().size() - TEST_UNSELECTED_MASK_COUNT;
    auto unselectedMaskNode = AceType::DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(unselectedmaskPosition));
    ASSERT_NE(unselectedMaskNode, nullptr);
    auto unSelectedImageNode = AceType::DynamicCast<FrameNode>(unselectedMaskNode->GetChildren().front());
    ASSERT_NE(unSelectedImageNode, nullptr);
    auto unSelectedImageRenderContext = unSelectedImageNode->GetRenderContext();
    ASSERT_NE(unSelectedImageRenderContext, nullptr);
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
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    BuildTabBar(tabsNode, TabBarStyle::BOTTOMTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE);

    /**
     * @tc.steps: step2. call UpdateImageColor function.
     * @tc.expected: step2. expect The function is run ok.
     */
    tabBarPattern->UpdateImageColor(0);
    EXPECT_NE(tabBarNode->GetChildAtIndex(0), nullptr);
    tabBarPattern->UpdateImageColor(1);
    EXPECT_NE(tabBarNode->GetChildAtIndex(1), nullptr);
    EXPECT_EQ(tabBarPattern->indicator_, 0);
    tabBarPattern->SetMaskAnimationByCreate(false);
    EXPECT_EQ(tabBarPattern->IsMaskAnimationByCreate(), false);
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
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    tabsModel.SetDivider(divider);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto pattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern->CreateLayoutAlgorithm());
    ASSERT_NE(tabBarLayoutAlgorithm, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    tabBarLayoutProperty->UpdateSelectedMask(0);
    tabBarLayoutProperty->UpdateUnselectedMask(1);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapper layoutWrapper = LayoutWrapper(tabBarNode, geometryNode, tabBarLayoutProperty);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabBarLayoutAlgorithm));

    /**
     * @tc.steps: step2. build selectedMaskNode and unselectedMaskNode.
     */
    auto selectedmaskPosition = tabBarNode->GetChildren().size() - TEST_SELECTED_MASK_COUNT;
    auto selectedMaskNode = AceType::DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(selectedmaskPosition));
    ASSERT_NE(selectedMaskNode, nullptr);
    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> selectedMaskLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(selectedMaskNode, geometryNode1, selectedMaskNode->GetLayoutProperty());
    layoutWrapper.AppendChild(selectedMaskLayoutWrapper);

    auto unselectedmaskPosition = tabBarNode->GetChildren().size() - TEST_UNSELECTED_MASK_COUNT;
    auto unselectedMaskNode = AceType::DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(unselectedmaskPosition));
    ASSERT_NE(unselectedMaskNode, nullptr);
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> unselectedMaskLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(unselectedMaskNode, geometryNode2, unselectedMaskNode->GetLayoutProperty());
    layoutWrapper.AppendChild(unselectedMaskLayoutWrapper);

    /**
     * @tc.steps: step3. call LayoutMask function.
     * @tc.expected: step3. expect The function is run ok.
     */
    tabBarLayoutAlgorithm->LayoutMask(&layoutWrapper);
    EXPECT_EQ(tabBarLayoutProperty->GetSelectedMask().value_or(-1), 0);
    EXPECT_EQ(tabBarLayoutProperty->GetUnselectedMask().value_or(-1), 1);
}

/**
 * @tc.name: TabBarLayoutAlgorithmLayoutMask002
 * @tc.desc: test LayoutMask
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmLayoutMask002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build selectedMaskNode and unselectedMaskNode.
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    tabsModel.SetDivider(divider);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto pattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern->CreateLayoutAlgorithm());
    ASSERT_NE(tabBarLayoutAlgorithm, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapper layoutWrapper = LayoutWrapper(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabBarLayoutAlgorithm));

    auto selectedmaskPosition = tabBarNode->GetChildren().size() - TEST_SELECTED_MASK_COUNT;
    auto selectedMaskNode = AceType::DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(selectedmaskPosition));
    ASSERT_NE(selectedMaskNode, nullptr);
    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> selectedMaskLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(selectedMaskNode, geometryNode1, selectedMaskNode->GetLayoutProperty());
    layoutWrapper.AppendChild(selectedMaskLayoutWrapper);

    auto unselectedmaskPosition = tabBarNode->GetChildren().size() - TEST_UNSELECTED_MASK_COUNT;
    auto unselectedMaskNode = AceType::DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(unselectedmaskPosition));
    ASSERT_NE(unselectedMaskNode, nullptr);
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> unselectedMaskLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(unselectedMaskNode, geometryNode2, unselectedMaskNode->GetLayoutProperty());
    layoutWrapper.AppendChild(unselectedMaskLayoutWrapper);

    /**
     * @tc.steps: step2. call LayoutMask function.
     * @tc.expected: step2. expect The function is run ok.
     */
    tabBarLayoutAlgorithm->LayoutMask(&layoutWrapper);
    EXPECT_EQ(tabBarLayoutProperty->GetSelectedMask().value_or(-1), -1);
    EXPECT_EQ(tabBarLayoutProperty->GetUnselectedMask().value_or(-1), -1);
}

/**
 * @tc.name: TabBarLayoutAlgorithmLayoutMask003
 * @tc.desc: test LayoutMask
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmLayoutMask003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build layoutWrapper.
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    tabsModel.SetDivider(divider);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto pattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern->CreateLayoutAlgorithm());
    ASSERT_NE(tabBarLayoutAlgorithm, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapper layoutWrapper = LayoutWrapper(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabBarLayoutAlgorithm));

    /**
     * @tc.steps: step2. call LayoutMask function.
     * @tc.expected: step2. expect The function is run ok.
     */
    tabBarLayoutAlgorithm->LayoutMask(&layoutWrapper);
}

/**
 * @tc.name: TabBarLayoutAlgorithmUpdateChildConstraint001
 * @tc.desc: test UpdateChildConstraint
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmUpdateChildConstraint001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build tabBarNode and ideaSize.
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    LayoutConstraintF childConstraint = LayoutConstraintF();
    std::optional<int32_t> tabBarTestId_(1);
    auto tabBarNode = GroupNode::GetFrameNode(V2::TAB_BAR_ETS_TAG, tabBarTestId_.value());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern->CreateLayoutAlgorithm());
    ASSERT_NE(tabBarLayoutAlgorithm, nullptr);
    auto tabBarProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarProperty, nullptr);

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
                    childConstraint, tabBarProperty, ideaSize, childCount, axis);
                axis = Axis::VERTICAL;
            }
            tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::BOTTOMTABBATSTYLE;
            axis = Axis::HORIZONTAL;
        }
        tabBarProperty->UpdateTabBarMode(TabBarMode::SCROLLABLE);
        tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    }
}

/**
 * @tc.name: TabBarLayoutAlgorithmCalculateBackChildrenMainSize001
 * @tc.desc: test CalculateBackChildrenMainSize
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmCalculateBackChildrenMainSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call UpdateSelectedMask and UpdateUnselectedMask.
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    tabsModel.SetDivider(divider);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto pattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern->CreateLayoutAlgorithm());
    ASSERT_NE(tabBarLayoutAlgorithm, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    tabBarLayoutProperty->UpdateSelectedMask(0);
    tabBarLayoutProperty->UpdateUnselectedMask(1);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapper(tabBarNode, geometryNode, tabBarLayoutProperty);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabBarLayoutAlgorithm));

    int32_t indicator = -2;
    auto axis = Axis::HORIZONTAL;

    /**
     * @tc.steps: step2. build selectedMaskNode.
     */
    for (int i = 0; i <= 2; i++) {
        auto selectedmaskPosition = tabBarNode->GetChildren().size() - TEST_SELECTED_MASK_COUNT;
        auto selectedMaskNode = AceType::DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(selectedmaskPosition));
        ASSERT_NE(selectedMaskNode, nullptr);
        RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();
        RefPtr<LayoutWrapper> selectedMaskLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapper>(selectedMaskNode, geometryNode1, selectedMaskNode->GetLayoutProperty());
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
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);

    auto tabBarPaintProperty = tabBarNode->GetPaintProperty<TabBarPaintProperty>();
    ASSERT_NE(tabBarPaintProperty, nullptr);

    /**
     * @tc.steps: steps2. SetBarBackgroundColor true
     * @tc.expected: steps2. Check the BarBarBackgroundColor property value
     */
    Color color = Color::RED;
    tabsModel.SetBarBackgroundColor(color);
    EXPECT_EQ(tabBarPaintProperty->GetBarBackgroundColor().value_or(Color::BLACK), color);
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: TabBar Accessibility PerformAction test ScrollForward and ScrollBackward.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, PerformActionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create tabBar frameNode and pattern, set callback function.
     * @tc.expected: Related function is called.
     */
    auto controller = AceType::MakeRefPtr<SwiperController>();
    ASSERT_NE(controller, nullptr);
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::TAB_BAR_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
            [controller]() { return AceType::MakeRefPtr<TabBarPattern>(controller); });
    ASSERT_NE(frameNode, nullptr);
    auto tabBarPattern = frameNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutProperty = tabBarPattern->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    tabBarLayoutProperty->UpdateTabBarMode(TabBarMode::FIXED);
    tabBarPattern->SetAccessibilityAction();

    /**
     * @tc.steps: step2. Get tabBar accessibilityProperty to call callback function.
     * @tc.expected: Related function is called.
     */
    auto tabBarAccessibilityProperty = frameNode->GetAccessibilityProperty<TabBarAccessibilityProperty>();
    ASSERT_NE(tabBarAccessibilityProperty, nullptr);

    /**
     * @tc.steps: step3. When tabBar TabBarMode is FIXED and child is null, call the callback function in
     *                   tabBarAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    EXPECT_TRUE(tabBarAccessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(tabBarAccessibilityProperty->ActActionScrollBackward());

    /**
     * @tc.steps: step4. When tabBar TabBarMode is SCROLLABLE and child is null, call the callback function in
     *                   tabBarAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    tabBarLayoutProperty->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    EXPECT_TRUE(tabBarAccessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(tabBarAccessibilityProperty->ActActionScrollBackward());

    /**
     * @tc.steps: step5. When tabBar TabBarMode is SCROLLABLE and child is not null, call the callback function in
     *                   tabBarAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    auto columnNode1 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(columnNode1, nullptr);
    columnNode1->MountToParent(frameNode);

    auto columnNode2 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(columnNode2, nullptr);
    columnNode2->MountToParent(frameNode);
    EXPECT_TRUE(tabBarAccessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(tabBarAccessibilityProperty->ActActionScrollBackward());

    /**
     * @tc.steps: step6. When tabBar TabBarMode is FIXED and child is not null, call the callback function in
     *                   tabBarAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    tabBarLayoutProperty->UpdateTabBarMode(TabBarMode::FIXED);
    EXPECT_TRUE(tabBarAccessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(tabBarAccessibilityProperty->ActActionScrollBackward());
}

/**
 * @tc.name: TabsModelSetTabBarWidth001
 * @tc.desc: test SetTabBarWidth
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelSetTabBarWidth001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */
    MockPipelineContextGetTheme();
    TabsModelNG tabsModel;
    Dimension tabBarWidth = 10.0_vp;
    Dimension tabBarHeight = 3.0_vp;

    /**
     * @tc.steps: step2. Test function SetTabBarWidth and SetTabBarHeight When tabBarWidth and tabBarHeight change.
     * @tc.expected: Related functions run ok.
     */
    for (int i = 0; i <= 1; i++) {
        tabsModel.SetTabBarWidth(tabBarWidth);
        tabsModel.SetTabBarHeight(tabBarHeight);
        tabBarWidth = -1.0_vp;
        tabBarHeight = -1.0_vp;
    }
}

/**
 * @tc.name: TabsModelSetAnimationDuration001
 * @tc.desc: test SetAnimationDuration
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelSetAnimationDuration001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */
    MockPipelineContextGetTheme();
    TabsModelNG tabsModel;
    bool duration = true;

    /**
     * @tc.steps: step2. Test function SetAnimationDuration.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        tabsModel.SetAnimationDuration(duration);
        duration = false;
    }
}

/**
 * @tc.name: TabsModelGetOrCreateTabsNode001
 * @tc.desc: test GetOrCreateTabsNode
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelGetOrCreateTabsNode001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */
    MockPipelineContextGetTheme();
    TabsModelNG tabsModel;
    const std::string tag = "TabsID";
    int32_t nodeId = 1;

    /**
     * @tc.steps: step2. Test function TabsModelGetOrCreateTabsNode.
     * @tc.expected: Related function runs ok.
     */
    auto tabsNode = TabsModelNG::GetOrCreateTabsNode(tag, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
    ASSERT_NE(tabsNode, nullptr);
}

/**
 * @tc.name: TabBarPatternInitClick001
 * @tc.desc: test InitClick
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternInitClick001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureHub, nullptr);
    tabBarPattern->clickEvent_ = nullptr;

    /**
     * @tc.steps: step2. Test function InitClick.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        tabBarPattern->InitClick(gestureHub);
        tabBarPattern->clickEvent_ = AceType::MakeRefPtr<ClickEvent>([](GestureEvent&) {});
    }
}

/**
 * @tc.name: TabBarPatternInitScrollable001
 * @tc.desc: test InitScrollable
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternInitScrollable001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarPattern->axis_ = Axis::HORIZONTAL;
    auto axis_test = Axis::HORIZONTAL;
    tabBarPattern->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(axis_test);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: step2. Test function InitScrollable.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            tabBarPattern->InitScrollable(gestureHub);
            tabBarPattern->axis_ = Axis::VERTICAL;
        }
        tabBarPattern->scrollableEvent_ = nullptr;
    }
}

/**
 * @tc.name: TabBarPatternInitTouche001
 * @tc.desc: test InitTouch, InitHoverEvent and InitMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternInitTouche001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureHub, nullptr);
    tabBarPattern->touchEvent_ = AceType::MakeRefPtr<TouchEventImpl>([](TouchEventInfo&) {});
    tabBarPattern->hoverEvent_ = AceType::MakeRefPtr<InputEvent>([](MouseInfo&) {});
    tabBarPattern->mouseEvent_ = AceType::MakeRefPtr<InputEvent>([](MouseInfo&) {});

    /**
     * @tc.steps: step2. Test function InitTouch, InitHoverEvent and InitMouseEvent.
     * @tc.expected: Related functions run ok.
     */
    tabBarPattern->InitTouch(gestureHub);
    tabBarPattern->InitHoverEvent();
    tabBarPattern->InitMouseEvent();
}

/**
 * @tc.name: TabBarPatternHandleMouseEvent001
 * @tc.desc: test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleMouseEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureHub, nullptr);
    auto info = MouseInfo();
    Offset s1(0.1, 0.1);
    OffsetF c1(0.1f, 0.1f);
    OffsetF c2(0.2f, 0.2f);
    info.SetLocalLocation(s1);
    tabBarPattern->tabItemOffsets_.emplace_back(c1);
    tabBarPattern->tabItemOffsets_.emplace_back(c2);

    /**
     * @tc.steps: step2. Test function HandleMouseEvent.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            tabBarPattern->HandleMouseEvent(info);
        }
        tabBarPattern->AddTabBarItemType(1, true);
    }
}

/**
 * @tc.name: TabBarmodifieronDraw002
 * @tc.desc: test onDraw
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarmodifieronDraw002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabBarmodifier
     */
    MockPipelineContextGetTheme();

    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    ASSERT_NE(tabBarModifier, nullptr);

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
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarNode->Clean(false, false);
    auto info = MouseInfo();

    /**
     * @tc.steps: step2. Test function GetBottomTabBarImageSizeAndOffset.
     * @tc.expected: Related function runs ok.
     */
    int32_t nodeId = 1;
    tabBarPattern->HandleMouseEvent(info);
    for (int i = 0; i <= 2; i++) {
        auto tabsNode = TabsModelNG::GetOrCreateTabsNode(
            V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
        tabBarNode->AddChild(tabsNode);
    }

    Offset s1(0.1, 0.1);
    OffsetF c1(0.1f, 0.1f);
    OffsetF c2(0.2f, 0.2f);
    info.SetLocalLocation(s1);
    tabBarPattern->tabItemOffsets_.emplace_back(c1);
    tabBarPattern->tabItemOffsets_.emplace_back(c2);
    tabBarPattern->HandleMouseEvent(info);
}

/**
 * @tc.name: TabBarPatternGetBottomTabBarImageSizeAndOffset001
 * @tc.desc: test GetBottomTabBarImageSizeAndOffset
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternGetBottomTabBarImageSizeAndOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
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
        tabBarPattern->GetBottomTabBarImageSizeAndOffset(selectedIndexes, maskIndex, selectedImageSize,
            unselectedImageSize, originalSelectedMaskOffset, originalUnselectedMaskOffset);
        maskIndex = 1;
    }

    int32_t nodeId = 1;
    for (int i = 0; i <= 2; i++) {
        auto tabsNode = TabsModelNG::GetOrCreateTabsNode(
            V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
        tabBarNode->AddChild(tabsNode);
    }
    maskIndex = 0;
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            tabBarPattern->GetBottomTabBarImageSizeAndOffset(selectedIndexes, maskIndex, selectedImageSize,
                unselectedImageSize, originalSelectedMaskOffset, originalUnselectedMaskOffset);
            maskIndex = 1;
        }
        tabBarNode->Clean(false, false);
    }
}

/*
 * @tc.name: TabBarPatternHandleMouseEvent003
 * @tc.desc: test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleMouseEvent003, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto info = MouseInfo();

    /**
     * @tc.steps: step2. Test function HandleMouseEvent.
     * @tc.expected: Related function runs ok.
     */
    int32_t nodeId = 1;
    for (int i = 0; i <= 2; i++) {
        auto tabsNode = TabsModelNG::GetOrCreateTabsNode(
            V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
        tabBarNode->AddChild(tabsNode);
    }
    Offset s1(0.2, 0.2);
    Offset s2(0.3, 0.3);
    OffsetF c1(0.1f, 0.1f);
    OffsetF c2(0.2f, 0.2f);
    OffsetF c3(0.3f, 0.3f);
    info.SetLocalLocation(s1);
    tabBarPattern->tabItemOffsets_ = { c1, c2, c3 };
    for (int i = 0; i <= 1; i++) {
        tabBarPattern->HandleMouseEvent(info);
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
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    int32_t selectedIndex = 1;
    int32_t unselectedIndex = 1;

    /**
     * @tc.steps: step2. Test function HandleBottomTabBarClick.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern->HandleBottomTabBarClick(selectedIndex, unselectedIndex);
}

/**
 * @tc.name: TabBarPatternHandleSubTabBarClick002
 * @tc.desc: test HandleSubTabBarClick
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleSubTabBarClick002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto layoutProperty = AceType::MakeRefPtr<TabBarLayoutProperty>();
    int32_t index = 1;
    SizeF size(0.1f, 0.2f);
    tabBarNode->GetGeometryNode()->SetFrameSize(size);
    tabBarPattern->SetChildrenMainSize(0.3f);
    auto swiperFrameNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    swiperPattern->currentIndex_ = 0;
    layoutProperty->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarPattern->axis_ = Axis::HORIZONTAL;

    int32_t nodeId = 1;
    for (int i = 0; i <= 4; i++) {
        auto tabsNode = TabsModelNG::GetOrCreateTabsNode(
            V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
        tabBarNode->AddChild(tabsNode);
    }
    tabBarNode->GetGeometryNode()->GetFrameSize().SetMainSize(2.0f, Axis::HORIZONTAL);
    auto childFrameNode = AceType::DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(index));
    auto childGeometryNode = childFrameNode->GetGeometryNode();
    childGeometryNode->GetMarginFrameSize().SetMainSize(1.0f, Axis::HORIZONTAL);
    auto childFrameNode1 = AceType::DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(index - 1));
    auto childGeometryNode1 = childFrameNode1->GetGeometryNode();
    auto childFrameSize1 = childGeometryNode1->GetMarginFrameSize();
    childFrameSize1.SetMainSize(0.1f, Axis::HORIZONTAL);
    OffsetF c1(0.1f, 0.2f);
    tabBarPattern->tabItemOffsets_.emplace_back(c1);

    /**
     * @tc.steps: step2. Test function HandleSubTabBarClick.
     * @tc.expected: Related function runs ok.
     */
    for (int32_t i = 0; i <= 1; i++) {
        tabBarPattern->HandleSubTabBarClick(layoutProperty, index);
        layoutProperty->UpdateTabBarMode(TabBarMode::FIXED);
    }
}

/**
 * @tc.name: TabBarPatternOnKeyEvent001
 * @tc.desc: test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternOnKeyEvent001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabContentModelNG tabContentModel1;
    tabContentModel1.Create();
    auto tabContentFrameNode1 =
        AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabContentFrameNode1, nullptr);

    TabContentModelNG tabContentModel2;
    tabContentModel2.Create();
    auto tabContentFrameNode2 =
        AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabContentFrameNode2, nullptr);

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    tabContentFrameNode1->MountToParent(swiperNode);
    tabContentFrameNode2->MountToParent(swiperNode);
    EXPECT_EQ(swiperNode->TotalChildCount(), 2);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->isFocusActive_ = true;

    /**
     * @tc.steps: steps2. OnKeyEvent
     * @tc.expected: steps2. Check the result of OnKeyEvent
     */
    KeyEvent event;
    event.code = KeyCode::KEY_DPAD_RIGHT;
    tabBarLayoutProperty->UpdateIndicator(2);
    EXPECT_FALSE(tabBarPattern->OnKeyEvent(event));
}

/**
 * @tc.name: TabBarPatternHandleTouchEvent001
 * @tc.desc: test HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleTouchEvent001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabContentModelNG tabContentModel1;
    tabContentModel1.Create();
    auto tabContentFrameNode1 =
        AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabContentFrameNode1, nullptr);

    TabContentModelNG tabContentModel2;
    tabContentModel2.Create();
    auto tabContentFrameNode2 =
        AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabContentFrameNode2, nullptr);

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    tabContentFrameNode1->MountToParent(swiperNode);
    tabContentFrameNode2->MountToParent(swiperNode);
    EXPECT_EQ(swiperNode->TotalChildCount(), 2);

    /**
     * @tc.steps: steps2. HandleTouchEvent
     * @tc.expected: steps2. Check the number of tabBarNode TotalChildCount
     */
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchLocationInfo.SetLocalLocation(Offset(0.f, 0.f));
    tabBarPattern->tabItemOffsets_ = { { -1.0f, -1.0f }, { 1.0f, 1.0f }, { 2.0f, 2.0f } };
    tabBarPattern->HandleTouchEvent(touchLocationInfo);
    EXPECT_EQ(tabBarNode->TotalChildCount(), 2);
}

/**
 * @tc.name: TabBarmodifierPaintIndicator001
 * @tc.desc: test PaintIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarmodifierPaintIndicator001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabBarmodifier
     */
    MockPipelineContextGetTheme();

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
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    bool isHover = true;
    std::optional<int32_t> hoverIndex_test(0);
    OffsetF c1(0.1f, 0.1f);
    OffsetF c2(0.2f, 0.2f);
    tabBarPattern->tabItemOffsets_.emplace_back(c1);
    tabBarPattern->tabItemOffsets_.emplace_back(c2);
    tabBarPattern->hoverIndex_ = hoverIndex_test;
    tabBarPattern->touchingIndex_ = hoverIndex_test;

    /**
     * @tc.steps: step2. Test function HandleHoverEvent.
     * @tc.expected: Related functions run ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern->HandleHoverEvent(isHover);
                isHover = false;
                tabBarPattern->hoverIndex_ = {};
            }
            tabBarPattern->hoverIndex_ = hoverIndex_test;
        }
        isHover = true;
        tabBarPattern->hoverIndex_ = {};
    }

    isHover = false;
    IndicatorStyle style;
    style.color = Color::BLACK;
    tabBarPattern->hoverIndex_ = hoverIndex_test;
    tabBarPattern->touchingIndex_ = {};
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarPattern->SetSelectedMode(SelectedMode::BOARD, 0);
    tabBarPattern->SetIndicatorStyle(style, 0);

    for (int i = 0; i <= 1; i++) {
        tabBarPattern->HandleHoverEvent(isHover);
        tabBarPattern->AddTabBarItemType(1, true);
    }
}

/**
 * @tc.name: TabBarPatternOnKeyEvent002
 * @tc.desc: test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternOnKeyEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

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
    tabBarPattern->GetLayoutProperty<TabBarLayoutProperty>()->UpdateAxis(Axis::HORIZONTAL);

    auto event = KeyEvent(code, action, pressedCodes, repeatTime, time, metaKey, deviceId, sourceType);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern->OnKeyEvent(event);
                event.action = KeyAction::DOWN;
                event.code = KeyCode::KEY_DPAD_LEFT;
            }
            event.code = KeyCode::KEY_DPAD_UP;
        }
        tabBarPattern->GetLayoutProperty<TabBarLayoutProperty>()->UpdateAxis(Axis::VERTICAL);
    }
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern->OnKeyEvent(event);
                event.code = KeyCode::KEY_DPAD_RIGHT;
            }
            event.code = KeyCode::KEY_DPAD_DOWN;
        }
        tabBarPattern->GetLayoutProperty<TabBarLayoutProperty>()->UpdateAxis(Axis::VERTICAL);
    }
    event.code = KeyCode::KEY_TAB;
    tabBarPattern->GetLayoutProperty<TabBarLayoutProperty>()->UpdateIndicator(1);
    for (int i = 0; i <= 1; i++) {
        tabBarPattern->OnKeyEvent(event);
        tabBarPattern->GetLayoutProperty<TabBarLayoutProperty>()->UpdateIndicator(-2);
    }
}

/**
 * @tc.name: TabBarPatternHandleTouchEvent002
 * @tc.desc: test HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleTouchEvent002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabContentModelNG tabContentModel1;
    tabContentModel1.Create();
    auto tabContentFrameNode1 =
        AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabContentFrameNode1, nullptr);

    TabContentModelNG tabContentModel2;
    tabContentModel2.Create();
    auto tabContentFrameNode2 =
        AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabContentFrameNode2, nullptr);

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    tabContentFrameNode1->MountToParent(swiperNode);
    tabContentFrameNode2->MountToParent(swiperNode);
    EXPECT_EQ(swiperNode->TotalChildCount(), 2);

    /**
     * @tc.steps: steps2. HandleTouchEvent
     * @tc.expected: steps2. Check the number of tabBarNode TotalChildCount
     */
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchLocationInfo.SetLocalLocation(Offset(0.f, 0.f));
    tabBarPattern->tabItemOffsets_ = { { -1.0f, -1.0f }, { 1.0f, 1.0f }, { 2.0f, 2.0f } };
    tabBarPattern->HandleTouchEvent(touchLocationInfo);
    EXPECT_EQ(tabBarNode->TotalChildCount(), 2);
}

/**
 * @tc.name: TabBarPatternFocusIndexChange001
 * @tc.desc: test FocusIndexChange
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternFocusIndexChange001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    int32_t index = 1;
    std::optional<int32_t> animation_test = 1;

    /**
     * @tc.steps: step2. Test function FocusIndexChange.
     * @tc.expected: Related functions run ok.
     */
    for (int i = 0; i <= 1; i++) {
        tabBarPattern->FocusIndexChange(index);
        tabBarPattern->animationDuration_ = animation_test;
    }
}

/**
 * @tc.name: TabBarPatternOnModifyDone001
 * @tc.desc: test OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternOnModifyDone001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    /**
     * @tc.steps: step2. Test function FocusIndexChange.
     * @tc.expected: Related functions run ok.
     */
    for (int i = 0; i <= 1; i++) {
        tabBarPattern->OnModifyDone();
        tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateTabBarMode(TabBarMode::FIXED);
    }
}

/**
 * @tc.name: TabBarPatternHandleClick002
 * @tc.desc: test HandleClick
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleClick002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateAxis(Axis::HORIZONTAL);
    GestureEvent info;
    Offset offset(1, 1);
    info.SetLocalLocation(offset);
    RefPtr<Scrollable> scrollable = AceType::MakeRefPtr<Scrollable>();
    ASSERT_NE(scrollable, nullptr);
    scrollable->SetAxis(Axis::HORIZONTAL);
    scrollable->springController_ = nullptr;
    scrollable->controller_ = nullptr;
    auto scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(Axis::HORIZONTAL);
    scrollableEvent->SetAxis(Axis::VERTICAL);
    scrollableEvent->SetScrollable(scrollable);
    tabBarPattern->scrollableEvent_ = scrollableEvent;

    /**
     * @tc.steps: step2. Test function HandleClick.
     * @tc.expected: Related functions run ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern->HandleClick(info);
                tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateTabBarMode(TabBarMode::FIXED);
            }
            tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateAxis(Axis::VERTICAL);
        }
        tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    }

    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateAxis(Axis::HORIZONTAL);
    auto springController = AceType::MakeRefPtr<Animator>();
    springController->SetTempo(0.1f);
    springController->status_ = Animator::Status::RUNNING;
    for (int i = 0; i <= 1; i++) {
        tabBarPattern->HandleClick(info);
        scrollable->springController_ = springController;
        tabBarPattern->scrollableEvent_ = scrollableEvent;
    }

    OffsetF c1(0.1f, 0.1f);
    OffsetF c2(0.2f, 0.2f);
    tabBarPattern->tabItemOffsets_.emplace_back(c1);
    tabBarPattern->tabItemOffsets_.emplace_back(c2);
    tabBarPattern->HandleClick(info);
}

/**
 * @tc.name: TabBarPatternMaskAnimationFinish003
 * @tc.desc: test MaskAnimationFinish
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternMaskAnimationFinish003, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    int32_t selectedIndex = -1;
    bool isSelected = true;

    /**
     * @tc.steps: step2. Test function MaskAnimationFinish.
     * @tc.expected: Related functions run ok.
     */
    tabBarPattern->MaskAnimationFinish(tabBarNode, selectedIndex, isSelected);
}

/**
 * @tc.name: TabBarDistributedTest001
 * @tc.desc: Test the distributed capability of TabBar
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarDistributedTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and get pattern.
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    tabsModel.SetDivider(divider);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutProperty = tabBarPattern->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    auto pattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    auto tabsLayoutProperty = tabBarPattern->GetLayoutProperty<TabsLayoutProperty>();

    /**
     * @tc.steps: step2. Set Indicator.
     * @tc.expected: Function ProvideRestoreInfo is called.
     */
    tabBarPattern->UpdateIndicator(0);
    std::string ret = tabBarPattern->ProvideRestoreInfo();
    EXPECT_TRUE(ret == R"({"Index":0})");

    /**
     * @tc.steps: step3. Function OnRestoreInfo is called.
     * @tc.expected: Passing invalid & valid JSON format.
     */
    std::string restoreInfo_ = R"({"Index":0})";
    pattern->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(tabBarLayoutProperty->GetIndicator().value_or(0), 0);
    restoreInfo_ = R"({"Index":1})";
    pattern->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(tabBarLayoutProperty->GetIndicator().value_or(0), 0);
    restoreInfo_ = "invalid_json_string";
    pattern->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(tabBarLayoutProperty->GetIndicator().value_or(0), 0);
}

/**
 * @tc.name: TabBarPatternHandleTouchDown001
 * @tc.desc: test HandleTouchDown
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleTouchDown001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    int32_t index = 1;
    tabBarPattern->swiperController_->SetRemoveSwiperEventCallback(nullptr);
    tabBarPattern->tabBarStyles_ = { TabBarStyle::SUBTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE };

    /**
     * @tc.steps: step2. Test function HandleTouchDown.
     * @tc.expected: Related functions run ok.
     */
    for (int i = 0; i <= 1; i++) {
        tabBarPattern->HandleTouchDown(index);
        tabBarPattern->swiperController_->SetRemoveSwiperEventCallback([]() {});
    }
}

/**
 * @tc.name: TabBarPatternHandleTouchUp001
 * @tc.desc: test HandleTouchUp
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleTouchUp001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    int32_t index = 1;
    tabBarPattern->swiperController_->SetAddSwiperEventCallback(nullptr);
    tabBarPattern->SetTouching(false);
    tabBarPattern->tabBarStyles_ = { TabBarStyle::SUBTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE };

    /**
     * @tc.steps: step2. Test function HandleTouchUp.
     * @tc.expected: Related functions run ok.
     */
    for (int i = 0; i <= 1; i++) {
        tabBarPattern->HandleTouchUp(index);
        tabBarPattern->swiperController_->SetAddSwiperEventCallback([]() {});
    }
}

/**
 * @tc.name: TabBarPatternHandleTouchUp002
 * @tc.desc: test HandleTouchUp
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleTouchUp002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    tabsModel.SetDivider(divider);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    int32_t index = 1;
    tabBarPattern->swiperController_->SetAddSwiperEventCallback(nullptr);
    tabBarPattern->SetTouching(true);
    IndicatorStyle indicatorStyle1;
    IndicatorStyle indicatorStyle2;
    indicatorStyle1.color = Color::BLACK;
    indicatorStyle2.color = Color::RED;
    tabBarPattern->tabBarStyles_ = { TabBarStyle::SUBTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE };
    tabBarPattern->selectedModes_ = { SelectedMode::BOARD, SelectedMode::INDICATOR };
    tabBarPattern->indicatorStyles_ = { indicatorStyle1, indicatorStyle2 };

    /**
     * @tc.steps: step2. Test function HandleTouchUp.
     * @tc.expected: Related functions run ok.
     */
    tabBarPattern->hoverIndex_.emplace(1);
    EXPECT_EQ(tabBarPattern->hoverIndex_.value(), 1);
    tabBarPattern->touchingIndex_.emplace(1);
    EXPECT_EQ(tabBarPattern->touchingIndex_.value(), 1);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern->HandleTouchUp(index);
                tabBarPattern->SetTouching(true);
                tabBarPattern->swiperController_->SetAddSwiperEventCallback([]() {});
                tabBarPattern->hoverIndex_.reset();
                EXPECT_FALSE(tabBarPattern->hoverIndex_.has_value());
            }
            tabBarPattern->touchingIndex_.emplace(0);
        }
        tabBarPattern->hoverIndex_.emplace(1);
    }

    tabBarPattern->hoverIndex_.reset();
    for (int i = 0; i <= 1; i++) {
        tabBarPattern->HandleTouchUp(index);
        tabBarPattern->SetTouching(true);
        tabBarPattern->hoverIndex_.emplace(1);
    }
}

/**
 * @tc.name: TabBarPatternPlayPressAnimation002
 * @tc.desc: test PlayPressAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternPlayPressAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    tabsModel.SetDivider(divider);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    int32_t index = 1;
    auto pressColor = Color();
    pressColor.SetValue(1);
    auto animationType = AnimationType::HOVERTOPRESS;
    IndicatorStyle indicatorStyle1;
    IndicatorStyle indicatorStyle2;
    indicatorStyle1.color = Color::BLACK;
    indicatorStyle2.color = Color::RED;
    tabBarPattern->tabBarStyles_ = { TabBarStyle::SUBTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE };
    tabBarPattern->selectedModes_ = { SelectedMode::BOARD, SelectedMode::INDICATOR };
    tabBarPattern->indicatorStyles_ = { indicatorStyle1, indicatorStyle2 };

    /**
     * @tc.steps: step2. Test function PlayPressAnimation.
     * @tc.expected: Related functions run ok.
     */
    for (int32_t i = 0; i <= 1; i++) {
        tabBarPattern->PlayPressAnimation(index, pressColor, animationType);
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
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    tabsModel.SetDivider(divider);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarPattern->tabBarTranslateController_ = AceType::MakeRefPtr<Animator>();
    tabBarPattern->tabBarTranslateController_->status_ = Animator::Status::RUNNING;

    /**
     * @tc.steps: step2. Test function StopTabBarTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        tabBarPattern->StopTabBarTranslateAnimation();
        tabBarPattern->tabBarTranslateController_->status_ = Animator::Status::STOPPED;
    }
}

/**
 * @tc.name: TabBarPatternSetEdgeEffect001
 * @tc.desc: test SetEdgeEffect
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternSetEdgeEffect001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    tabsModel.SetDivider(divider);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    /**
     * @tc.steps: step2. Test function SetEdgeEffect.
     * @tc.expected: Related function runs ok.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureHub, nullptr);
    tabBarPattern->SetEdgeEffect(gestureHub);
}

/**
 * @tc.name: TabBarPatternHandleTouchEvent003
 * @tc.desc: test HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleTouchEvent003, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabContentModelNG tabContentModel1;
    tabContentModel1.Create();
    auto tabContentFrameNode1 =
        AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabContentFrameNode1, nullptr);

    TabContentModelNG tabContentModel2;
    tabContentModel2.Create();
    auto tabContentFrameNode2 =
        AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabContentFrameNode2, nullptr);

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);

    tabBarPattern->tabBarType_.emplace(std::make_pair(1, true));

    /**
     * @tc.steps: steps2. HandleTouchEvent
     * @tc.expected: steps2. Check the number of tabBarNode TotalChildCount
     */
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchLocationInfo.SetLocalLocation(Offset(0.f, 0.f));
    tabBarPattern->tabItemOffsets_ = { { -1.0f, -1.0f }, { 1.0f, 1.0f }, { 2.0f, 2.0f } };
    for (int i = 0; i <= 1; i++) {
        tabBarPattern->HandleTouchEvent(touchLocationInfo);
        tabBarPattern->tabBarType_.clear();
        tabBarNode->RemoveChildAtIndex(1);
    }
    EXPECT_EQ(tabBarNode->TotalChildCount(), 1);
}

/**
 * @tc.name: TabBarPatternUpdateTextColor001
 * @tc.desc: test UpdateTextColor and UpdateImageColor
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternUpdateTextColor001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    tabsModel.SetDivider(divider);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    int32_t index = 0;
    auto pr = tabBarPattern->tabBarType_.emplace(std::make_pair(1, true));
    ASSERT_TRUE(pr.second);
    /**
     * @tc.steps: step2. Test function UpdateTextColor and UpdateImageColor.
     * @tc.expected: Related functions run ok.
     */
    tabBarPattern->UpdateTextColor(index);
    tabBarPattern->UpdateImageColor(index);
}

/**
 * @tc.name: TabBarPatternUpdateTextColor002
 * @tc.desc: test UpdateTextColor
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternUpdateTextColor002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    tabsModel.SetDivider(divider);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    int32_t index = 0;
    for (int i = 0; i <= 1; i++) {
        AceType::DynamicCast<FrameNode>(
            AceType::DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(i))->GetChildren().back())
            ->layoutProperty_ = AceType::MakeRefPtr<TextLayoutProperty>();
        ASSERT_NE(AceType::DynamicCast<FrameNode>(
                      AceType::DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(i))->GetChildren().back())
                      ->layoutProperty_,
            nullptr);
    }

    /**
     * @tc.steps: step2. Test function UpdateTextColor.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern->UpdateTextColor(index);
}

/**
 * @tc.name: TabBarPatternInitClick002
 * @tc.desc: test InitClick
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternInitClick002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureHub, nullptr);
    tabBarPattern->clickEvent_ = nullptr;
    auto info = GestureEvent();

    /**
     * @tc.steps: step2. Test function InitClick.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern->InitClick(gestureHub);
    tabBarPattern->clickEvent_->callback_(info);
}

/**
 * @tc.name: TabBarPatternInitScrollable002
 * @tc.desc: test InitScrollable
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternInitScrollable002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarPattern->axis_ = Axis::HORIZONTAL;
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureHub, nullptr);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateAxis(Axis::VERTICAL);
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    ASSERT_NE(scrollable, nullptr);
    scrollable->SetAxis(Axis::HORIZONTAL);
    scrollable->springController_ = nullptr;
    scrollable->controller_ = nullptr;
    auto scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(Axis::HORIZONTAL);
    scrollableEvent->SetAxis(Axis::VERTICAL);
    scrollableEvent->SetScrollable(scrollable);
    tabBarPattern->scrollableEvent_ = scrollableEvent;

    /**
     * @tc.steps: step2. Test function InitScrollable.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        tabBarPattern->InitScrollable(gestureHub);
        tabBarPattern->swiperController_->tabBarFinishCallback_();
        scrollableEvent->SetScrollable(nullptr);
        tabBarPattern->scrollableEvent_ = scrollableEvent;
    }
}

/**
 * @tc.name: TabBarPatternInitScrollable003
 * @tc.desc: test InitScrollable
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternInitScrollable003, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarPattern->axis_ = Axis::HORIZONTAL;
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureHub, nullptr);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateAxis(Axis::VERTICAL);
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);

    /**
     * @tc.steps: step2. Test function InitScrollable.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern->InitScrollable(gestureHub);
                ASSERT_NE(tabBarPattern->scrollableEvent_, nullptr);
                tabBarPattern->scrollableEvent_->callback_(0.1, SCROLL_FROM_NONE);
                tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
                tabBarPattern->axis_ = Axis::HORIZONTAL;
            }
            tabBarPattern->axis_ = Axis::VERTICAL;
            tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateAxis(Axis::HORIZONTAL);
            tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }
        tabBarPattern->tabItemOffsets_ = { { -1.0f, -1.0f } };
    }
    tabBarPattern->scrollableEvent_->callback_(0.1, SCROLL_FROM_START);
    tabBarPattern->axis_ = Axis::VERTICAL;
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    int32_t source = SCROLL_FROM_UPDATE;
    for (int i = 0; i <= 1; i++) {
        tabBarPattern->InitScrollable(gestureHub);
        tabBarPattern->scrollableEvent_->callback_(0.1, source);
        tabBarPattern->axis_ = Axis::VERTICAL;
        tabBarPattern->tabItemOffsets_.clear();
        tabBarPattern->tabItemOffsets_ = { { 1.0f, -1.0f } };
        tabBarNode->GetGeometryNode()->SetFrameSize(SizeF(1.0f, 2.0f));
    }
}

/**
 * @tc.name: TabBarPatternInitHoverEvent001
 * @tc.desc: test InitHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternInitHoverEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarPattern->axis_ = Axis::HORIZONTAL;
    tabBarPattern->hoverEvent_ = nullptr;
    tabBarPattern->mouseEvent_ = nullptr;
    auto info = MouseInfo();

    /**
     * @tc.steps: step2. Test function InitHoverEvent and InitMouseEvent.
     * @tc.expected: Related functions run ok.
     */
    tabBarPattern->InitHoverEvent();
    tabBarPattern->InitMouseEvent();
    ASSERT_NE(tabBarPattern->hoverEvent_, nullptr);
    ASSERT_NE(tabBarPattern->mouseEvent_, nullptr);
    tabBarPattern->hoverEvent_->onHoverCallback_(true);
    tabBarPattern->mouseEvent_->onMouseCallback_(info);
}

/**
 * @tc.name: TabBarPatternInitOnKeyEvent001
 * @tc.desc: test InitOnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternInitOnKeyEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto focusHub = tabBarNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto event = KeyEvent();
    auto paintRect = RoundRect();

    /**
     * @tc.steps: step2. Test function InitOnKeyEvent.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern->InitOnKeyEvent(focusHub);
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
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto info = MouseInfo();

    /**
     * @tc.steps: step2. Test function HandleMouseEvent.
     * @tc.expected: Related function runs ok.
     */
    int32_t nodeId = 1;
    for (int i = 0; i <= 2; i++) {
        auto tabsNode = TabsModelNG::GetOrCreateTabsNode(
            V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
        tabBarNode->AddChild(tabsNode);
    }
    Offset s1(0.1, 0.1);
    Offset s2(0.4, 0.4);
    OffsetF c1(0.1f, 0.1f);
    OffsetF c2(0.2f, 0.2f);
    OffsetF c3(0.3f, 0.3f);
    OffsetF c4(0.4f, 0.4f);
    info.SetLocalLocation(s1);
    ASSERT_EQ(tabBarPattern->CalculateSelectedIndex(info.GetLocalLocation()), -1);
    tabBarPattern->hoverIndex_.emplace(1);
    tabBarPattern->tabItemOffsets_ = { c1, c2, c3, c4 };
    IndicatorStyle indicatorStyle1;
    IndicatorStyle indicatorStyle2;
    IndicatorStyle indicatorStyle3;
    indicatorStyle1.color = Color::BLACK;
    indicatorStyle2.color = Color::RED;
    indicatorStyle3.color = Color::BLUE;
    tabBarPattern->tabBarStyles_ = { TabBarStyle::SUBTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE,
        TabBarStyle::NOSTYLE };
    tabBarPattern->selectedModes_ = { SelectedMode::BOARD, SelectedMode::INDICATOR, SelectedMode::BOARD };
    tabBarPattern->indicatorStyles_ = { indicatorStyle1, indicatorStyle2, indicatorStyle3 };

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            tabBarPattern->HandleMouseEvent(info);
            info.SetLocalLocation(s2);
            ASSERT_EQ(tabBarPattern->CalculateSelectedIndex(info.GetLocalLocation()), 2);
            tabBarPattern->hoverIndex_.reset();
        }
        tabBarPattern->hoverIndex_.emplace(1);
        tabBarPattern->touchingIndex_.emplace(1);
    }

    Offset s3(0.2, 0.2);
    info.SetLocalLocation(s3);
    ASSERT_EQ(tabBarPattern->CalculateSelectedIndex(info.GetLocalLocation()), 0);
    info.SetAction(MouseAction::MOVE);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern->HandleMouseEvent(info);
                tabBarPattern->touchingIndex_.reset();
                tabBarPattern->hoverIndex_ = 1;
            }
            tabBarPattern->hoverIndex_.reset();
        }
        tabBarPattern->hoverIndex_.emplace(0);
        info.SetAction(MouseAction::WINDOW_ENTER);
    }

    info.SetAction(MouseAction::WINDOW_LEAVE);
    tabBarPattern->HandleMouseEvent(info);
}

/**
 * @tc.name: TabBarPatternOnKeyEvent003
 * @tc.desc: test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternOnKeyEvent003, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    /**
     * @tc.steps: step2. Test function OnKeyEvent.
     * @tc.expected: Related functions run ok.
     */
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
    tabBarPattern->GetLayoutProperty<TabBarLayoutProperty>()->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern->GetLayoutProperty<TabBarLayoutProperty>()->UpdateIndicator(1);
    auto event = KeyEvent(code, action, pressedCodes, repeatTime, time, metaKey, deviceId, sourceType);
    tabBarPattern->OnKeyEvent(event);
}

/**
 * @tc.name: TabBarLayoutAlgorithmLayout002
 * @tc.desc: Test Divider Layout.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmLayout002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    MockPipelineContextGetTheme();

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call Layout function.
     * @tc.expected: Related function is called.
     */
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto pattern = tabsFrameNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper =
        LayoutWrapper(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty<TabBarLayoutProperty>());
    AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())->UpdateTabBarMode(TabBarMode::FIXED);
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern->CreateLayoutAlgorithm());
    ASSERT_NE(tabBarLayoutAlgorithm, nullptr);
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
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    MockPipelineContextGetTheme();

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call Layout function.
     * @tc.expected: Related function is called.
     */
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto pattern = tabsFrameNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper =
        LayoutWrapper(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty<TabBarLayoutProperty>());
    auto layoutWrapper1 = AceType::MakeRefPtr<LayoutWrapper>(
        tabBarNode, geometryNode, tabBarNode->GetLayoutProperty<TabBarLayoutProperty>());
    ASSERT_NE(layoutWrapper1, nullptr);
    auto layoutWrapper2 = AceType::MakeRefPtr<LayoutWrapper>(
        tabBarNode, geometryNode, tabBarNode->GetLayoutProperty<TabBarLayoutProperty>());
    ASSERT_NE(layoutWrapper2, nullptr);
    auto layoutWrapper3 = AceType::MakeRefPtr<LayoutWrapper>(
        tabBarNode, geometryNode, tabBarNode->GetLayoutProperty<TabBarLayoutProperty>());
    ASSERT_NE(layoutWrapper3, nullptr);
    auto layoutWrapper4 = AceType::MakeRefPtr<LayoutWrapper>(
        tabBarNode, geometryNode, tabBarNode->GetLayoutProperty<TabBarLayoutProperty>());
    ASSERT_NE(layoutWrapper4, nullptr);
    auto layoutWrapper5 = AceType::MakeRefPtr<LayoutWrapper>(
        tabBarNode, geometryNode, tabBarNode->GetLayoutProperty<TabBarLayoutProperty>());
    ASSERT_NE(layoutWrapper5, nullptr);
    AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern->CreateLayoutAlgorithm());
    ASSERT_NE(tabBarLayoutAlgorithm, nullptr);
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
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

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
    tabBarPattern->PlayMaskAnimation(selectedImageSize, originalSelectedMaskOffset, selectedIndex, unselectedImageSize,
        originalUnselectedMaskOffset, unselectedIndex);
}

/**
 * @tc.name: TabBarPatternHandleTouchEvent004
 * @tc.desc: test HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleTouchEvent004, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarNode1 = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode1, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabsNode1 =
        TabsModelNG::GetOrCreateTabsNode(V2::TABS_ETS_TAG, 1, []() { return AceType::MakeRefPtr<TabsPattern>(); });
    tabBarNode->AddChild(tabsNode1);
    IndicatorStyle indicatorStyle1;
    IndicatorStyle indicatorStyle2;
    indicatorStyle1.color = Color::BLACK;
    indicatorStyle2.color = Color::RED;
    tabBarPattern->tabBarStyles_ = { TabBarStyle::SUBTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE };
    tabBarPattern->selectedModes_ = { SelectedMode::BOARD, SelectedMode::INDICATOR };
    tabBarPattern->indicatorStyles_ = { indicatorStyle1, indicatorStyle2 };

    /**
     * @tc.steps: step2. Test function HandleTouchEvent.
     * @tc.expected: Related function runs ok.
     */
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchLocationInfo.SetLocalLocation(Offset(1.0f, 1.0f));
    tabBarPattern->tabItemOffsets_ = { { -1.0f, -1.0f }, { 1.0f, 1.0f }, { 2.0f, 2.0f } };
    for (int i = 0; i <= 1; i++) {
        tabBarPattern->HandleTouchEvent(touchLocationInfo);
        touchLocationInfo.SetLocalLocation(Offset(-1.0f, -1.0f));
    }
    EXPECT_EQ(tabBarNode->TotalChildCount(), 3);
    tabBarPattern->touchingIndex_ = 1;
    touchLocationInfo.SetTouchType(TouchType::UP);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern->HandleTouchEvent(touchLocationInfo);
                tabBarPattern->touchingIndex_ = 1;
                touchLocationInfo.SetTouchType(TouchType::CANCEL);
            }
            touchLocationInfo.SetTouchType(TouchType::DOWN);
        }
        tabBarPattern->touchingIndex_.reset();
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
     * @tc.steps: steps1. Create TabBarPattern
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    /**
     * @tc.steps: step2. Test function PlayTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    float startPos = 0.1f;
    float endPos = 0.2f;
    float targetCurrentOffset = 0.3f;
    double value = 0;
    auto offset = 0.1f;
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern->currentOffset_ = offset;
                tabBarPattern->PlayTranslateAnimation(startPos, endPos, targetCurrentOffset);
                ASSERT_NE(tabBarPattern->controller_, nullptr);
                auto interpolator = tabBarPattern->controller_->interpolators_.front();
                ASSERT_NE(interpolator, nullptr);
                auto* translate = static_cast<CurveAnimation<double>*>(AceType::RawPtr(interpolator));
                ASSERT_NE(translate, nullptr);
                Animation<double>::ValueCallback valueCallback = translate->callbacks_.begin()->second;
                valueCallback.callback_(value);
                tabBarPattern->controller_->ClearInterpolators();
                value = 0;
                startPos = 0.0f;
                endPos = 0.0f;
            }
            endPos = 0.1f;
        }
        endPos = 0.0f;
        startPos = 0.1f;
    }

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern->currentOffset_ = offset;
                tabBarPattern->PlayTranslateAnimation(startPos, endPos, targetCurrentOffset);
                ASSERT_NE(tabBarPattern->controller_, nullptr);
                auto interpolator = tabBarPattern->controller_->interpolators_.back();
                ASSERT_NE(interpolator, nullptr);
                auto* tabBarTranslate = static_cast<CurveAnimation<double>*>(AceType::RawPtr(interpolator));
                ASSERT_NE(tabBarTranslate, nullptr);
                Animation<double>::ValueCallback valueCallback = tabBarTranslate->callbacks_.begin()->second;
                valueCallback.callback_(value);
                tabBarPattern->controller_->ClearInterpolators();
                value = 0;
                offset = 0.0f;
                targetCurrentOffset = 0.0f;
            }
            offset = 0.1f;
        }
        offset = 0.0f;
        targetCurrentOffset = 0.1f;
    }
}

/**
 * @tc.name: TabBarPatternSetEdgeEffect002
 * @tc.desc: test SetEdgeEffect
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternSetEdgeEffect002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    tabsModel.SetDivider(divider);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarPattern->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>();

    /**
     * @tc.steps: step2. Test function SetEdgeEffect.
     * @tc.expected: Related function runs ok.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureHub, nullptr);
    tabBarPattern->SetEdgeEffect(gestureHub);
}

/**
 * @tc.name: TabBarPatternPlayTabBarTranslateAnimation001
 * @tc.desc: test PlayTabBarTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternPlayTabBarTranslateAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    tabsModel.SetDivider(divider);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    int32_t targetIndex = 1;
    tabBarPattern->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>();
    tabBarNode->GetGeometryNode()->SetFrameSize(SizeF(1.0f, 1.0f));
    tabBarPattern->childrenMainSize_ = 0.1f;
    AceType::DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(targetIndex))
        ->GetGeometryNode()
        ->SetFrameSize(SizeF(0.0f, 0.0f));
    AceType::DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(targetIndex - 1))
        ->GetGeometryNode()
        ->SetFrameSize(SizeF(0.0f, 0.0f));
    int32_t nodeId = 1;
    for (int i = 0; i <= 2; i++) {
        auto tabsNode = TabsModelNG::GetOrCreateTabsNode(
            V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
        tabBarNode->AddChild(tabsNode);
    }
    AceType::DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(targetIndex + 1))
        ->GetGeometryNode()
        ->SetFrameSize(SizeF(0.0f, 0.0f));

    /**
     * @tc.steps: step2. Test function PlayTabBarTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern->PlayTabBarTranslateAnimation(targetIndex);
                tabBarPattern->childrenMainSize_ = 2.0f;
            }
            AceType::DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(targetIndex - 1))
                ->GetGeometryNode()
                ->SetFrameSize(SizeF(2.0f, 2.0f));
        }
        AceType::DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(targetIndex + 1))
            ->GetGeometryNode()
            ->SetFrameSize(SizeF(2.0f, 2.0f));
    }

    double value = 0.0;
    float offset = 0.0f;
    AceType::DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(targetIndex - 1))
        ->GetGeometryNode()
        ->SetFrameSize(SizeF(0.0f, 0.0f));
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern->currentOffset_ = offset;
                tabBarPattern->PlayTabBarTranslateAnimation(targetIndex);
                ASSERT_NE(tabBarPattern->controller_, nullptr);
                auto interpolator = tabBarPattern->controller_->interpolators_.front();
                ASSERT_NE(interpolator, nullptr);
                auto* tabBarTranslate = static_cast<CurveAnimation<double>*>(AceType::RawPtr(interpolator));
                ASSERT_NE(tabBarTranslate, nullptr);
                Animation<double>::ValueCallback valueCallback = tabBarTranslate->callbacks_.begin()->second;
                valueCallback.callback_(value);
                tabBarPattern->controller_->ClearInterpolators();
                value = 1.0;
                offset = 2.0f;
            }
            offset = 0.0f;
        }
        offset = 2.0f;
        value = 0.0;
    }
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
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 0, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    BuildTabBar(tabsNode, TabBarStyle::NOSTYLE, TabBarStyle::NOSTYLE);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->isFocusActive_ = true;

    /**
     * @tc.steps: steps2. OnKeyEvent
     * @tc.expected: steps2. Check the result of OnKeyEvent
     */
    KeyEvent event;
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_MOVE_HOME;
    tabBarPattern->SetTabBarStyle(TabBarStyle::NOSTYLE);
    tabBarPattern->focusIndicator_ = 1;
    EXPECT_TRUE(tabBarPattern->OnKeyEvent(event));

    event.code = KeyCode::KEY_MOVE_END;
    tabBarPattern->focusIndicator_ = 0;
    EXPECT_TRUE(tabBarPattern->OnKeyEvent(event));

    tabsNode->GetLayoutProperty<TabsLayoutProperty>()->UpdateTabBarPosition(BarPosition::START);
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    FocusTest(tabBarLayoutProperty, tabBarPattern);
}

/**
 * @tc.name: TabBarPatternOnKeyEvent005
 * @tc.desc: test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternOnKeyEvent005, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::END, 0, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    BuildTabBar(tabsNode, TabBarStyle::NOSTYLE, TabBarStyle::NOSTYLE);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->isFocusActive_ = true;

    /**
     * @tc.steps: steps2. OnKeyEvent
     * @tc.expected: steps2. Check the result of OnKeyEvent
     */
    tabsNode->GetLayoutProperty<TabsLayoutProperty>()->UpdateTabBarPosition(BarPosition::END);
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    FocusTest(tabBarLayoutProperty, tabBarPattern);
}

/**
 * @tc.name: TabBarPatternOnKeyEvent006
 * @tc.desc: test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternOnKeyEvent006, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::END, 0, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    BuildTabBar(tabsNode, TabBarStyle::NOSTYLE, TabBarStyle::NOSTYLE);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->isFocusActive_ = true;

    /**
     * @tc.steps: steps2. OnKeyEvent
     * @tc.expected: steps2. Check the result of OnKeyEvent
     */
    tabsNode->GetLayoutProperty<TabsLayoutProperty>()->UpdateTabBarPosition(BarPosition::END);
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    tabBarPattern->SetFirstFocus(true);
    FocusTest(tabBarLayoutProperty, tabBarPattern);
}

/**
 * @tc.name: TabBarPatternOnKeyEvent007
 * @tc.desc: test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternOnKeyEvent007, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::END, 0, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    BuildTabBar(tabsNode, TabBarStyle::NOSTYLE, TabBarStyle::NOSTYLE);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);

    /**
     * @tc.steps: steps2. OnKeyEvent
     * @tc.expected: steps2. Check the result of OnKeyEvent
     */
    tabsNode->GetLayoutProperty<TabsLayoutProperty>()->UpdateTabBarPosition(BarPosition::END);
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    KeyEvent event;
    event.action = KeyAction::DOWN;
    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->isFocusActive_ = false;
    event.code = KeyCode::KEY_DPAD_RIGHT;
    tabBarPattern->focusIndicator_ = 0;
    EXPECT_TRUE(tabBarPattern->OnKeyEvent(event));

    pipeline->isFocusActive_ = true;
    event.code = KeyCode::KEY_A;
    tabBarPattern->focusIndicator_ = 0;
    EXPECT_FALSE(tabBarPattern->OnKeyEvent(event));
}

/**
 * @tc.name: TabsPatternGetScopeFocusAlgorithm001
 * @tc.desc: test GetScopeFocusAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsPatternGetScopeFocusAlgorithm001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::END, 0, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    BuildTabBar(tabsNode, TabBarStyle::SUBTABBATSTYLE, TabBarStyle::SUBTABBATSTYLE);

    /**
     * @tc.steps: steps2. GetScopeFocusAlgorithm
     * @tc.expected: steps2. Check the result of GetScopeFocusAlgorithm
     */
    auto tabsLayoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    ASSERT_NE(tabsLayoutProperty, nullptr);
    auto tabsPattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);
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
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::END, 0, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    BuildTabBar(tabsNode, TabBarStyle::SUBTABBATSTYLE, TabBarStyle::SUBTABBATSTYLE);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);

    /**
     * @tc.steps: steps2. GetScopeFocusAlgorithm
     * @tc.expected: steps2. Check the result of GetScopeFocusAlgorithm
     */
    tabBarPattern->AdjustFocusPosition();
    tabBarLayoutProperty->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarPattern->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    tabBarPattern->axis_ = Axis::HORIZONTAL;
    tabBarPattern->tabItemOffsets_.clear();
    OffsetF c1(-1.0f, -1.0f);
    tabBarPattern->tabItemOffsets_.emplace_back(c1);
    tabBarPattern->focusIndicator_ = 0;
    tabBarPattern->AdjustFocusPosition();
    EXPECT_EQ(tabBarPattern->GetTabBarStyle(), TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern->axis_ = Axis::VERTICAL;
    tabBarPattern->focusIndicator_ = 0;
    tabBarPattern->AdjustFocusPosition();
    EXPECT_EQ(tabBarPattern->GetTabBarStyle(), TabBarStyle::SUBTABBATSTYLE);
}

/**
 * @tc.name: TabBarPatternAdjustFocusPosition002
 * @tc.desc: test AdjustFocusPosition
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternAdjustFocusPosition002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::END, 0, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    BuildTabBar(tabsNode, TabBarStyle::SUBTABBATSTYLE, TabBarStyle::SUBTABBATSTYLE);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);

    /**
     * @tc.steps: steps2. GetScopeFocusAlgorithm
     * @tc.expected: steps2. Check the result of GetScopeFocusAlgorithm
     */
    tabBarLayoutProperty->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarPattern->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    tabBarPattern->axis_ = Axis::HORIZONTAL;
    tabBarPattern->tabItemOffsets_.clear();
    OffsetF c1(1.0f, 1.0f);
    OffsetF c2(100.0f, 100.0f);
    tabBarPattern->tabItemOffsets_.emplace_back(c1);
    tabBarPattern->tabItemOffsets_.emplace_back(c2);
    tabBarPattern->focusIndicator_ = 0;
    tabBarPattern->AdjustFocusPosition();
    EXPECT_EQ(tabBarPattern->GetTabBarStyle(), TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern->axis_ = Axis::VERTICAL;
    tabBarPattern->focusIndicator_ = 0;
    tabBarPattern->AdjustFocusPosition();
    EXPECT_EQ(tabBarPattern->GetTabBarStyle(), TabBarStyle::SUBTABBATSTYLE);
}

/**
 * @tc.name: TabBarPatternCreateNodePaintMethod001
 * @tc.desc: test CreateNodePaintMethod
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternCreateNodePaintMethod001, TestSize.Level1)
{
    MockPipelineContextGetTheme();

    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsFrameNode, nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabBarFrameNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarFrameNode, nullptr);
    EXPECT_EQ(tabBarFrameNode->GetTag(), V2::TAB_BAR_ETS_TAG);
    auto tabBarPattern = tabBarFrameNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto paintProperty = tabBarPattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    IndicatorStyle indicator;
    tabBarPattern->SetIndicatorStyle(indicator, 0);
    EXPECT_EQ(tabBarPattern->indicatorStyles_[0], indicator);
    SelectedMode selectedMode = SelectedMode::INDICATOR;
    tabBarPattern->SetSelectedMode(selectedMode, 0);
    EXPECT_EQ(tabBarPattern->selectedModes_[0], selectedMode);

    /**
     * @tc.steps: steps2. CreateNodePaintMethod
     * @tc.expected: steps2. Check the result of CreateNodePaintMethod
     */
    auto tabBarRenderContext = tabBarFrameNode->GetRenderContext();
    ASSERT_NE(tabBarRenderContext, nullptr);
    tabBarRenderContext->UpdateBackgroundColor(Color::RED);
    auto paintMethod = tabBarPattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod, nullptr);
    EXPECT_EQ(tabBarRenderContext->GetBackgroundColor().value(), Color::RED);
}

/**
 * @tc.name: TabsModelSetOnTabBarClick001
 * @tc.desc: Tabs SetOnTabBarClick
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelSetOnTabBarClick001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);

    /**
     * @tc.steps: steps2. SetOnTabBarClick
     * @tc.expected: steps2. Check the result of SetOnTabBarClick
     */
    tabsModel.SetOnTabBarClick([](const BaseEventInfo* info) {});
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabsNode, nullptr);
    auto pattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_NE(pattern->onTabBarClickEvent_, nullptr);

    tabsModel.SetOnTabBarClick([](const BaseEventInfo* info) {});
    EXPECT_NE(pattern->onTabBarClickEvent_, nullptr);
}

/**
 * @tc.name: TabBarPatternGetNextFocusNode001
 * @tc.desc: test GetNextFocusNode
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternGetNextFocusNode001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_)).Times(AnyNumber());

    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::END, 0, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    BuildTabBar(tabsNode, TabBarStyle::BOTTOMTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    tabBarNode->GetOrCreateFocusHub();
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    auto tabsPattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);
    auto tabsLayoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    ASSERT_NE(tabsLayoutProperty, nullptr);
    auto swiperFocusNode = swiperNode->GetFocusHub();
    ASSERT_NE(swiperFocusNode, nullptr);
    auto tabBarFocusNode = tabBarNode->GetFocusHub();
    ASSERT_NE(tabBarFocusNode, nullptr);

    /**
     * @tc.steps: steps2. GetNextFocusNode
     * @tc.expected: steps2. Check the result of GetNextFocusNode
     */
    tabsLayoutProperty->UpdateTabBarPosition(BarPosition::START);
    tabsLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    tabsPattern->GetNextFocusNode(FocusStep::DOWN, tabBarFocusNode);
    EXPECT_EQ(tabsLayoutProperty->GetAxis().value(), Axis::HORIZONTAL);

    tabsLayoutProperty->UpdateTabBarPosition(BarPosition::START);
    tabsLayoutProperty->UpdateAxis(Axis::VERTICAL);
    tabsPattern->GetNextFocusNode(FocusStep::RIGHT, tabBarFocusNode);
    EXPECT_EQ(tabsLayoutProperty->GetAxis().value(), Axis::VERTICAL);

    tabsLayoutProperty->UpdateTabBarPosition(BarPosition::END);
    tabsLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    tabsPattern->GetNextFocusNode(FocusStep::UP, tabBarFocusNode);
    EXPECT_EQ(tabsLayoutProperty->GetAxis().value(), Axis::HORIZONTAL);

    tabsLayoutProperty->UpdateTabBarPosition(BarPosition::END);
    tabsLayoutProperty->UpdateAxis(Axis::VERTICAL);
    tabsPattern->GetNextFocusNode(FocusStep::LEFT, tabBarFocusNode);
    EXPECT_EQ(tabsLayoutProperty->GetAxis().value(), Axis::VERTICAL);

    tabsLayoutProperty->UpdateTabBarPosition(BarPosition::START);
    tabsLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    tabsPattern->GetNextFocusNode(FocusStep::UP, swiperFocusNode);
    tabsPattern->GetNextFocusNode(FocusStep::UP_END, swiperFocusNode);
    EXPECT_EQ(tabsLayoutProperty->GetAxis().value(), Axis::HORIZONTAL);

    tabsLayoutProperty->UpdateTabBarPosition(BarPosition::START);
    tabsLayoutProperty->UpdateAxis(Axis::VERTICAL);
    tabsPattern->GetNextFocusNode(FocusStep::LEFT, swiperFocusNode);
    tabsPattern->GetNextFocusNode(FocusStep::LEFT_END, swiperFocusNode);
    EXPECT_EQ(tabsLayoutProperty->GetAxis().value(), Axis::VERTICAL);

    tabsLayoutProperty->UpdateTabBarPosition(BarPosition::END);
    tabsLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    tabsPattern->GetNextFocusNode(FocusStep::DOWN, swiperFocusNode);
    tabsPattern->GetNextFocusNode(FocusStep::DOWN_END, swiperFocusNode);
    EXPECT_EQ(tabsLayoutProperty->GetAxis().value(), Axis::HORIZONTAL);

    tabsLayoutProperty->UpdateTabBarPosition(BarPosition::END);
    tabsLayoutProperty->UpdateAxis(Axis::VERTICAL);
    tabsPattern->GetNextFocusNode(FocusStep::UP, swiperFocusNode);
    EXPECT_EQ(tabsLayoutProperty->GetAxis().value(), Axis::VERTICAL);

    tabsLayoutProperty->UpdateTabBarPosition(BarPosition::END);
    tabsLayoutProperty->UpdateAxis(Axis::VERTICAL);
    tabsPattern->GetNextFocusNode(FocusStep::RIGHT, swiperFocusNode);
    tabsPattern->GetNextFocusNode(FocusStep::RIGHT_END, swiperFocusNode);
    EXPECT_EQ(tabsLayoutProperty->GetAxis().value(), Axis::VERTICAL);
}
} // namespace OHOS::Ace::NG