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

#include "gtest/gtest.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"

#define private public
#define protected public

#include "core/components/select/select_theme.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
#include "core/components_ng/pattern/menu/menu_layout_algorithm.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/menu/multi_menu_layout_algorithm.h"
#include "core/components_ng/pattern/menu/sub_menu_layout_algorithm.h"
#include "core/components_ng/syntax/lazy_for_each_model.h"
#include "core/components_ng/syntax/lazy_layout_wrapper_builder.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr float POSITION_OFFSET = 100.0f;
constexpr float TARGET_SIZE_WIDTH = 100.0f;
constexpr float TARGET_SIZE_HEIGHT = 100.0f;
constexpr float MENU_SIZE_WIDTH = 150.0f;
constexpr float MENU_SIZE_HEIGHT = 150.0f;
constexpr double MENU_OFFSET_X = 10.0;
constexpr double MENU_OFFSET_Y = 10.0;
constexpr float MENU_ITEM_SIZE_WIDTH = 100.0f;
constexpr float MENU_ITEM_SIZE_HEIGHT = 50.0f;

constexpr int CHILD_SIZE_X = 1;
constexpr int CHILD_SIZE_Y = 2;
constexpr int TOP_POSITION_X = 10;
constexpr int TOP_POSITION_Y = 20;
constexpr int BOTTOM_POSITION_X = 30;
constexpr int BOTTOM_POSITION_Y = 40;
constexpr int SIZE_X_FIRST = 0;
constexpr int SIZE_Y_FIRST = 2;
constexpr int OFFSET_X_FIRST = 10;
constexpr int OFFSET_Y_FIRST = 50;
constexpr int CHILD_OFFSET_X = 10;
constexpr int CHILD_OFFSET_Y = 20;
constexpr int OFFSET_X_SECOND = 0;
constexpr int OFFSET_Y_SECOND = 20;
constexpr int SIZE_X_SECOND = 20;
constexpr int SIZE_Y_SECOND = 20;
constexpr int OFFSET_X_THIRD = 100;
constexpr int OFFSET_Y_THIRD = 20;
constexpr int NODEID = 1;
constexpr int TOP_LEFT_X = 100;
constexpr int TOP_LEFT_Y = 18;
constexpr int TOP_RIGHT_X = 119;
constexpr int TOP_RIGHT_Y = 18;
constexpr int BOTTOM_LEFT_X = 100;
constexpr int BOTTOM_LEFT_Y = 40;
constexpr int BOTTOM_RIGHT_X = 119;
constexpr int BOTTOM_RIGHT_Y = 40;
constexpr int PLACEMENT_LEFT_X = 99;
constexpr int PLACEMENT_LEFT_Y = 29;
constexpr int PLACEMENT_LEFT_TOP_X = 99;
constexpr int PLACEMENT_LEFT_TOP_Y = 20;
constexpr int PLACEMENT_LEFT_BOTTOM_X = 99;
constexpr int PLACEMENT_LEFT_BOTTOM_Y = 38;
constexpr int PLACEMENT_RIGHT_X = 120;
constexpr int PLACEMENT_RIGHT_Y = 29;
constexpr int PLACEMENT_RIGHT_TOP_X = 120;
constexpr int PLACEMENT_RIGHT_TOP_Y = 20;
constexpr int PLACEMENT_RIGHT_BOTTOM_X = 120;
constexpr int PLACEMENT_RIGHT_BOTTOM_Y = 38;

const SizeF FULL_SCREEN_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
} // namespace

class MenuLayoutAlgorithmTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void MenuLayoutAlgorithmTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}
void MenuLayoutAlgorithmTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}
void MenuLayoutAlgorithmTestNg::SetUp() {}
void MenuLayoutAlgorithmTestNg::TearDown() {}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg001
 * @tc.desc: Verify HorizontalLayout.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg001, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF size(50, 100);
    SizeF size_f(100, 200);
    float clickPosition = 50.0f;
    menuLayoutAlgorithm->wrapperSize_ = size_f;
    auto result = menuLayoutAlgorithm->HorizontalLayout(size, clickPosition);
    EXPECT_EQ(result, clickPosition);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg002
 * @tc.desc: Verify HorizontalLayout.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg002, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF size(50, 100);
    SizeF size_f(100, 200);
    float clickPosition = 60.0f;
    menuLayoutAlgorithm->wrapperSize_ = size_f;
    auto result = menuLayoutAlgorithm->HorizontalLayout(size, clickPosition);
    EXPECT_EQ(result, size_f.Width() - size.Width());
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg003
 * @tc.desc: Verify HorizontalLayout.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg003, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF size(70, 100);
    SizeF size_f(100, 200);
    float clickPosition = 60.0f;
    menuLayoutAlgorithm->wrapperSize_ = size_f;
    auto result = menuLayoutAlgorithm->HorizontalLayout(size, clickPosition);
    EXPECT_EQ(result, menuLayoutAlgorithm->wrapperSize_.Width() - size.Width());
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg004
 * @tc.desc: Verify HorizontalLayout.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg004, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF size(100, 100);
    SizeF size_f(100, 200);
    float clickPosition = 60.0f;
    menuLayoutAlgorithm->wrapperSize_ = size_f;
    auto result = menuLayoutAlgorithm->HorizontalLayout(size, clickPosition);
    EXPECT_EQ(result, 0.0);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg005
 * @tc.desc: Verify VerticalLayout.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg005, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF size(100, 100);
    SizeF size_f(100, 200);
    float clickPosition = 100.0f;
    menuLayoutAlgorithm->wrapperSize_ = size_f;
    auto result = menuLayoutAlgorithm->VerticalLayout(size, clickPosition);
    EXPECT_EQ(result, clickPosition);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg006
 * @tc.desc: Verify VerticalLayout.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg006, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF size(100, 100);
    float clickPosition = 150.0f;
    menuLayoutAlgorithm->topSpace_ = 200.0f;
    auto result = menuLayoutAlgorithm->VerticalLayout(size, clickPosition);
    EXPECT_EQ(result, menuLayoutAlgorithm->topSpace_ - size.Height());
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg007
 * @tc.desc: Verify VerticalLayout.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg007, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF size(100, 150);
    SizeF size_f(100, 200);
    float clickPosition = 100.0f;
    menuLayoutAlgorithm->wrapperSize_ = size_f;
    auto result = menuLayoutAlgorithm->VerticalLayout(size, clickPosition);
    EXPECT_EQ(result, menuLayoutAlgorithm->wrapperSize_.Height() - size.Height());
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg008
 * @tc.desc: Verify VerticalLayout.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg008, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF size(100, 200);
    SizeF size_f(100, 200);
    float clickPosition = 100.0f;
    menuLayoutAlgorithm->wrapperSize_ = size_f;
    auto result = menuLayoutAlgorithm->VerticalLayout(size, clickPosition);
    EXPECT_EQ(result, 0.0);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg009
 * @tc.desc: Verify Initialize.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg009, TestSize.Level1)
{
    // set buttonTheme to themeManager before using themeManager to get buttonTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    const std::string tag = "tag";
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<Pattern>();
    MenuView menuView;
    std::vector<SelectParam> params;
    params.emplace_back("A", "B");
    int32_t targetId = 1;
    auto frameNode = menuView.Create(params, targetId);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapper* layoutWrapper = new LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
    menuLayoutAlgorithm->Initialize(layoutWrapper);
    EXPECT_EQ(menuLayoutAlgorithm->wrapperSize_.Width(), 0);
    delete layoutWrapper;
    layoutWrapper = nullptr;
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg010
 * @tc.desc: Verify Layout.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg010, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    OffsetF offset(10, 10);
    menuLayoutAlgorithm->position_ = offset;
    const std::string tag = "tag";
    int32_t nodeId = 1;
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<Pattern>();
    bool isRoot = false;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<FrameNode> frameNode = AceType::MakeRefPtr<FrameNode>(tag, nodeId, pattern, isRoot);
    LayoutWrapper* layoutWrapper = new LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
    RefPtr<LazyForEachActuator> actuator = AceType::MakeRefPtr<LazyForEachActuator>();
    auto builder = AceType::DynamicCast<LazyForEachBuilder>(actuator);
    RefPtr<LazyForEachNode> host_ = AceType::MakeRefPtr<LazyForEachNode>(nodeId, builder);
    WeakPtr<LazyForEachNode> host(host_);
    RefPtr<LazyLayoutWrapperBuilder> wrapperBuilder = AceType::MakeRefPtr<LazyLayoutWrapperBuilder>(builder, host);
    wrapperBuilder->OnGetOrCreateWrapperByIndex(nodeId);
    auto children = wrapperBuilder->OnExpandChildLayoutWrapper();
    auto layoutWrapper_ = wrapperBuilder->GetOrCreateWrapperByIndex(nodeId);
    menuLayoutAlgorithm->Layout(layoutWrapper);
    EXPECT_EQ(menuLayoutAlgorithm->position_.GetX(), 10);
    delete layoutWrapper;
    layoutWrapper = nullptr;
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg011
 * @tc.desc: Verify positionOffset of Layout.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg011, TestSize.Level1)
{
    std::function<void()> action = [] {};
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem1", "", action);
    optionParams.emplace_back("MenuItem2", "", action);
    MenuParam menuParam;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(property, nullptr);
    ASSERT_TRUE(property->GetPositionOffset().has_value());
    EXPECT_EQ(property->GetPositionOffset().value(), OffsetF());
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapper layoutWrapper(menuNode, geometryNode, menuNode->GetLayoutProperty());

    layoutWrapper.GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(FULL_SCREEN_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    layoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(layoutAlgorithm->position_, OffsetF());
    EXPECT_EQ(layoutAlgorithm->positionOffset_, OffsetF());
    EXPECT_EQ(layoutAlgorithm->wrapperSize_, SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));
    layoutAlgorithm->Layout(&layoutWrapper);
    EXPECT_EQ(geometryNode->GetMarginFrameOffset(), OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg012
 * @tc.desc: Verify positionOffset of Layout.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg012, TestSize.Level1)
{
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem1", "", nullptr);
    optionParams.emplace_back("MenuItem2", "", nullptr);
    MenuParam menuParam = { "", { POSITION_OFFSET, POSITION_OFFSET } };
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(property, nullptr);
    ASSERT_TRUE(property->GetPositionOffset().has_value());
    EXPECT_EQ(property->GetPositionOffset().value(), OffsetF(POSITION_OFFSET, POSITION_OFFSET));

    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapper layoutWrapper(menuNode, geometryNode, menuNode->GetLayoutProperty());
    layoutWrapper.GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(FULL_SCREEN_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    layoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(layoutAlgorithm->position_, OffsetF());
    EXPECT_EQ(layoutAlgorithm->positionOffset_, OffsetF(POSITION_OFFSET, POSITION_OFFSET));
    EXPECT_EQ(layoutAlgorithm->wrapperSize_, SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));
    layoutAlgorithm->Layout(&layoutWrapper);
    EXPECT_EQ(geometryNode->GetMarginFrameOffset(), OffsetF(POSITION_OFFSET, POSITION_OFFSET));
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg013
 * @tc.desc: Verify ComputeMenuPositionByAlignType.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg013, TestSize.Level1)
{
    std::vector<SelectParam> selectParams;
    selectParams.emplace_back(std::make_pair("MenuItem1", "Icon1"));
    selectParams.emplace_back(std::make_pair("MenuItem2", "Icon2"));
    // create select menu
    auto menuWrapperNode = MenuView::Create(std::move(selectParams), 1);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(property, nullptr);
    SizeF targetSize(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT);
    property->UpdateTargetSize(targetSize);

    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(menuLayoutAlgorithm, nullptr);

    /**
     * @tc.cases: case1. the menu align type is start.
     */
    SizeF menuSize(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT);
    menuLayoutAlgorithm->position_ = OffsetF(0, 0);
    property->UpdateAlignType(MenuAlignType::START);
    menuLayoutAlgorithm->ComputeMenuPositionByAlignType(property, menuSize);
    EXPECT_EQ(menuLayoutAlgorithm->position_.GetX(), 0);

    /**
     * @tc.cases: case2. the menu align type is center.
     */
    menuLayoutAlgorithm->position_ = OffsetF(0, 0);
    property->UpdateAlignType(MenuAlignType::CENTER);
    menuLayoutAlgorithm->ComputeMenuPositionByAlignType(property, menuSize);
    float expectResult = -25.0f;
    EXPECT_EQ(menuLayoutAlgorithm->position_.GetX(), expectResult);

    /**
     * @tc.cases: case3. the menu align type is end.
     */
    menuLayoutAlgorithm->position_ = OffsetF(0, 0);
    property->UpdateAlignType(MenuAlignType::END);
    menuLayoutAlgorithm->ComputeMenuPositionByAlignType(property, menuSize);
    expectResult = -50.0f;
    EXPECT_EQ(menuLayoutAlgorithm->position_.GetX(), expectResult);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg014
 * @tc.desc: Verify ComputeMenuPositionByOffset.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg014, TestSize.Level1)
{
    std::vector<SelectParam> selectParams;
    selectParams.emplace_back(std::make_pair("MenuItem1", "Icon1"));
    selectParams.emplace_back(std::make_pair("MenuItem2", "Icon2"));
    // create select menu
    auto menuWrapperNode = MenuView::Create(std::move(selectParams), 1);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(property, nullptr);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));
    property->UpdateLayoutConstraint(parentLayoutConstraint);

    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(menuLayoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT));

    /**
     * @tc.cases: case1. parameter is valid, return the valid offset.
     */
    property->UpdateOffset(
        DimensionOffset(Dimension(MENU_OFFSET_X, DimensionUnit::VP), Dimension(MENU_OFFSET_Y, DimensionUnit::VP)));
    auto resultOffset = menuLayoutAlgorithm->ComputeMenuPositionByOffset(property, geometryNode);
    EXPECT_EQ(resultOffset, OffsetF(MENU_OFFSET_X, MENU_OFFSET_Y));

    /**
     * @tc.cases: case2. parameter property is nullptr, return OffsetF(0.0, 0.0).
     */
    resultOffset = menuLayoutAlgorithm->ComputeMenuPositionByOffset(nullptr, geometryNode);
    EXPECT_EQ(resultOffset, OffsetF(0.0, 0.0));

    /**
     * @tc.cases: case3. parameter geometryNode is nullptr, return OffsetF(0.0, 0.0).
     */
    resultOffset = menuLayoutAlgorithm->ComputeMenuPositionByOffset(property, nullptr);
    EXPECT_EQ(resultOffset, OffsetF(0.0, 0.0));
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg015
 * @tc.desc: Verify ComputeMenuPositionByOffset.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg015, TestSize.Level1)
{
    std::vector<SelectParam> selectParams;
    selectParams.emplace_back(std::make_pair("MenuItem1", "Icon1"));
    selectParams.emplace_back(std::make_pair("MenuItem2", "Icon2"));

    // create select menu
    auto menuWrapperNode = MenuView::Create(std::move(selectParams), 1);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(property, nullptr);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));
    property->UpdateLayoutConstraint(parentLayoutConstraint);

    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(menuLayoutAlgorithm, nullptr);

    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->isSelectMenu_ = true;
    SizeF size(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT);

    /**
     * @tc.cases: case1. parameter property is nullptr, return OffsetF(0.0, 0.0).
     */
    auto resultOffset = menuLayoutAlgorithm->MenuLayoutAvoidAlgorithm(nullptr, menuPattern, size);
    EXPECT_EQ(resultOffset, OffsetF(0.0, 0.0));

    /**
     * @tc.cases: case2. parameter menuPattern is nullptr, return OffsetF(0.0, 0.0).
     */
    resultOffset = menuLayoutAlgorithm->MenuLayoutAvoidAlgorithm(property, nullptr, size);
    EXPECT_EQ(resultOffset, OffsetF(0.0, 0.0));

    /**
     * @tc.cases: case3. menu property has placement value and has targetSize.
     */
    property->UpdateMenuPlacement(Placement::RIGHT);
    menuLayoutAlgorithm->targetSize_ = SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT);
    resultOffset = menuLayoutAlgorithm->MenuLayoutAvoidAlgorithm(property, menuPattern, size);
    float expectOffsetX = -150.0f;
    float expectOffsetY = -150.0f;
    EXPECT_EQ(resultOffset, OffsetF(expectOffsetX, expectOffsetY));

    /**
     * @tc.cases: case4. menu property not has placement value and is select menu.
     */
    property->ResetMenuPlacement();
    resultOffset = menuLayoutAlgorithm->MenuLayoutAvoidAlgorithm(property, menuPattern, size);
    EXPECT_EQ(resultOffset, OffsetF(expectOffsetX, expectOffsetY));

    /**
     * @tc.cases: case5. menu property not has placement value and is context menu.
     */
    menuPattern->type_ = MenuType::CONTEXT_MENU;
    resultOffset = menuLayoutAlgorithm->MenuLayoutAvoidAlgorithm(property, menuPattern, size);
    EXPECT_EQ(resultOffset, OffsetF(expectOffsetX, expectOffsetY));
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg016
 * @tc.desc: Test MultiMenu layout algorithm.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg016, TestSize.Level1)
{
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::MULTI_MENU);
    auto multiMenu = AceType::MakeRefPtr<FrameNode>("", -1, menuPattern);
    auto algorithm = AceType::MakeRefPtr<MultiMenuLayoutAlgorithm>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT));
    auto layoutProp = AceType::MakeRefPtr<MenuLayoutProperty>();
    auto* wrapper = new LayoutWrapper(multiMenu, geometryNode, layoutProp);

    for (int32_t i = 0; i < 3; ++i) {
        auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
        auto menuItem = AceType::MakeRefPtr<FrameNode>("", -1, itemPattern);
        auto itemGeoNode = AceType::MakeRefPtr<GeometryNode>();
        itemGeoNode->SetFrameSize(SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT / 3));
        auto childWrapper = AceType::MakeRefPtr<LayoutWrapper>(menuItem, itemGeoNode, layoutProp);
        wrapper->AppendChild(childWrapper);
    }

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<SelectTheme>()));

    algorithm->Layout(wrapper);
    // default padding from theme is zero, so the offset on the first child is zero.
    OffsetF offset;
    for (auto&& child : wrapper->GetAllChildrenWithBuild()) {
        EXPECT_EQ(child->GetGeometryNode()->GetMarginFrameOffset(), offset);
        offset.AddY(MENU_SIZE_HEIGHT / 3);
    }
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg017
 * @tc.desc: Verify GetPositionWithPlacement.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm, set childSize, topPosition, bottomPosition
     */
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(menuLayoutAlgorithm, nullptr);
    SizeF childSize(CHILD_SIZE_X, CHILD_SIZE_Y);
    OffsetF topPosition(TOP_POSITION_X, TOP_POSITION_Y);
    OffsetF bottomPosition(BOTTOM_POSITION_X, BOTTOM_POSITION_Y);
    auto result = menuLayoutAlgorithm->GetPositionWithPlacement(childSize, topPosition, bottomPosition);
    EXPECT_EQ(result.GetX(), 0);
    EXPECT_EQ(result.GetY(), 0);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg018
 * @tc.desc: Verify GetPositionWithPlacement with targetNodeId, targetTag
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm, set childSize, topPosition, bottomPosition, targetNodeId, targetTag
     */
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(menuLayoutAlgorithm, nullptr);
    SizeF childSize(CHILD_SIZE_X, CHILD_SIZE_Y);
    OffsetF topPosition(TOP_POSITION_X, TOP_POSITION_Y);
    OffsetF bottomPosition(BOTTOM_POSITION_X, BOTTOM_POSITION_Y);
    const std::string tag = "tag";
    MenuLayoutAlgorithm menu(NODEID, tag);
    auto result = menu.GetPositionWithPlacement(childSize, topPosition, bottomPosition);
    EXPECT_NE(result.GetX(), 0);
    EXPECT_NE(result.GetY(), 0);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg019
 * @tc.desc: Verify GetErrorPositionType with normal position
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm, offset to normal position
     * @tc.expected: step1. result is NORMAL
     */
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    OffsetF offset(OFFSET_X_FIRST, OFFSET_Y_FIRST);
    SizeF size(SIZE_X_FIRST, SIZE_Y_FIRST);
    menuLayoutAlgorithm->targetOffset_ = offset;
    menuLayoutAlgorithm->targetSize_ = size;
    OffsetF childOffset(CHILD_OFFSET_X, CHILD_OFFSET_Y);
    SizeF childSize(CHILD_SIZE_X, CHILD_SIZE_Y);
    auto result = menuLayoutAlgorithm->GetErrorPositionType(childOffset, childSize);
    EXPECT_EQ(result, MenuLayoutAlgorithm::ErrorPositionType::NORMAL);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg020
 * @tc.desc: Verify GetErrorPositionType with top left position
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm, offset to top left
     * @tc.expected: step1. result is TOP_LEFT_ERROR
     */
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    OffsetF offset(OFFSET_X_SECOND, OFFSET_Y_SECOND);
    SizeF size(SIZE_X_SECOND, SIZE_Y_SECOND);
    menuLayoutAlgorithm->targetOffset_ = offset;
    menuLayoutAlgorithm->targetSize_ = size;
    OffsetF childOffset(CHILD_OFFSET_X, CHILD_OFFSET_Y);
    SizeF childSize(CHILD_SIZE_X, CHILD_SIZE_Y);
    auto result = menuLayoutAlgorithm->GetErrorPositionType(childOffset, childSize);
    EXPECT_EQ(result, MenuLayoutAlgorithm::ErrorPositionType::TOP_LEFT_ERROR);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg021
 * @tc.desc: Verify GetPositionWithPlacementTop.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm, set childSize, topPosition, bottomPosition
     * @tc.expected: step1. position is topPosition
     */
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF childSize(CHILD_SIZE_X, CHILD_SIZE_Y);
    OffsetF topPosition(TOP_POSITION_X, TOP_POSITION_Y);
    OffsetF bottomPosition(BOTTOM_POSITION_X, BOTTOM_POSITION_Y);
    auto result = menuLayoutAlgorithm->GetPositionWithPlacementTop(childSize, topPosition, bottomPosition);
    EXPECT_EQ(result.GetX(), TOP_POSITION_X);
    EXPECT_EQ(result.GetY(), TOP_POSITION_Y);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg022
 * @tc.desc: Verify GetPositionWithPlacementTopLeft.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm, set childSize, topPosition, bottomPosition and targetOffset
     * @tc.expected: step1. position is (targetOffset_.GetX(), targetOffset_.GetY() - childSize.Height())
     */
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF childSize(CHILD_SIZE_X, CHILD_SIZE_Y);
    OffsetF topPosition(TOP_POSITION_X, TOP_POSITION_Y);
    OffsetF bottomPosition(BOTTOM_POSITION_X, BOTTOM_POSITION_Y);
    OffsetF offset(OFFSET_X_THIRD, OFFSET_Y_THIRD);
    menuLayoutAlgorithm->targetOffset_ = offset;
    auto result = menuLayoutAlgorithm->GetPositionWithPlacementTopLeft(childSize, topPosition, bottomPosition);
    EXPECT_EQ(result.GetX(), TOP_LEFT_X);
    EXPECT_EQ(result.GetY(), TOP_LEFT_Y);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg023
 * @tc.desc: Verify GetPositionWithPlacementTopRight.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm, set childSize, topPosition, bottomPosition and targetOffset
     * @tc.expected: step1. position is (targetOffset_.GetX() + targetSize_.Width() - childSize.Width(),
     * targetOffset_.GetY() - childSize.Height())
     */
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF childSize(CHILD_SIZE_X, CHILD_SIZE_Y);
    OffsetF topPosition(TOP_POSITION_X, TOP_POSITION_Y);
    OffsetF bottomPosition(BOTTOM_POSITION_X, BOTTOM_POSITION_Y);
    OffsetF offset(OFFSET_X_THIRD, OFFSET_Y_THIRD);
    menuLayoutAlgorithm->targetOffset_ = offset;
    SizeF size(SIZE_X_SECOND, SIZE_Y_SECOND);
    menuLayoutAlgorithm->targetSize_ = size;
    auto result = menuLayoutAlgorithm->GetPositionWithPlacementTopRight(childSize, topPosition, bottomPosition);
    EXPECT_EQ(result.GetX(), TOP_RIGHT_X);
    EXPECT_EQ(result.GetY(), TOP_RIGHT_Y);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg024
 * @tc.desc: Verify GetPositionWithPlacementBottom.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm, set childSize, topPosition, bottomPosition
     * @tc.expected: step1. position is bottomPosition
     */
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF childSize(CHILD_SIZE_X, CHILD_SIZE_Y);
    OffsetF topPosition(TOP_POSITION_X, TOP_POSITION_Y);
    OffsetF bottomPosition(BOTTOM_POSITION_X, BOTTOM_POSITION_Y);
    auto result = menuLayoutAlgorithm->GetPositionWithPlacementBottom(childSize, topPosition, bottomPosition);
    EXPECT_EQ(result.GetX(), BOTTOM_POSITION_X);
    EXPECT_EQ(result.GetY(), BOTTOM_POSITION_Y);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg025
 * @tc.desc: Verify GetPositionWithPlacementBottomLeft.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm, set childSize, topPosition, bottomPosition, targetOffset and
     * targetSize
     * @tc.expected: step1. position is (targetOffset_.GetX(), targetOffset_.GetY() + targetSize_.Height())
     */
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF childSize(CHILD_SIZE_X, CHILD_SIZE_Y);
    OffsetF topPosition(TOP_POSITION_X, TOP_POSITION_Y);
    OffsetF bottomPosition(BOTTOM_POSITION_X, BOTTOM_POSITION_Y);
    OffsetF offset(OFFSET_X_THIRD, OFFSET_Y_THIRD);
    menuLayoutAlgorithm->targetOffset_ = offset;
    SizeF size(SIZE_X_SECOND, SIZE_Y_SECOND);
    menuLayoutAlgorithm->targetSize_ = size;
    auto result = menuLayoutAlgorithm->GetPositionWithPlacementBottomLeft(childSize, topPosition, bottomPosition);
    EXPECT_EQ(result.GetX(), BOTTOM_LEFT_X);
    EXPECT_EQ(result.GetY(), BOTTOM_LEFT_Y);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg026
 * @tc.desc: Verify GetPositionWithPlacementBottomRight.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm, set childSize, topPosition, bottomPosition, targetOffset and
     * targetSize
     * @tc.expected: step1. position is (targetOffset_.GetX() + targetSize_.Width() - childSize.Width(),
     * targetOffset_.GetY() + targetSize_.Height())
     */
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF childSize(CHILD_SIZE_X, CHILD_SIZE_Y);
    OffsetF topPosition(TOP_POSITION_X, TOP_POSITION_Y);
    OffsetF bottomPosition(BOTTOM_POSITION_X, BOTTOM_POSITION_Y);
    OffsetF offset(OFFSET_X_THIRD, OFFSET_Y_THIRD);
    menuLayoutAlgorithm->targetOffset_ = offset;
    SizeF size(SIZE_X_SECOND, SIZE_Y_SECOND);
    menuLayoutAlgorithm->targetSize_ = size;
    auto result = menuLayoutAlgorithm->GetPositionWithPlacementBottomRight(childSize, topPosition, bottomPosition);
    EXPECT_EQ(result.GetX(), BOTTOM_RIGHT_X);
    EXPECT_EQ(result.GetY(), BOTTOM_RIGHT_Y);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg027
 * @tc.desc: Verify GetPositionWithPlacementLeft.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm, set childSize, topPosition, bottomPosition, targetOffset and
     * targetSize
     * @tc.expected: step1. position is (targetOffset_.GetX() - childSize.Width(),
     * targetOffset_.GetY() + targetSize_.Height() / 2.0 - childSize.Height() / 2.0)
     */
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF childSize(CHILD_SIZE_X, CHILD_SIZE_Y);
    OffsetF topPosition(TOP_POSITION_X, TOP_POSITION_Y);
    OffsetF bottomPosition(BOTTOM_POSITION_X, BOTTOM_POSITION_Y);
    OffsetF offset(OFFSET_X_THIRD, OFFSET_Y_THIRD);
    menuLayoutAlgorithm->targetOffset_ = offset;
    SizeF size(SIZE_X_SECOND, SIZE_Y_SECOND);
    menuLayoutAlgorithm->targetSize_ = size;
    auto result = menuLayoutAlgorithm->GetPositionWithPlacementLeft(childSize, topPosition, bottomPosition);
    EXPECT_EQ(result.GetX(), PLACEMENT_LEFT_X);
    EXPECT_EQ(result.GetY(), PLACEMENT_LEFT_Y);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg028
 * @tc.desc: Verify GetPositionWithPlacementLeftTop.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm, set childSize, topPosition, bottomPosition, targetOffset and
     * targetSize
     * @tc.expected: step1. position is (targetOffset_.GetX() - childSize.Width(),
     * targetOffset_.GetY())
     */
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF childSize(CHILD_SIZE_X, CHILD_SIZE_Y);
    OffsetF topPosition(TOP_POSITION_X, TOP_POSITION_Y);
    OffsetF bottomPosition(BOTTOM_POSITION_X, BOTTOM_POSITION_Y);
    OffsetF offset(OFFSET_X_THIRD, OFFSET_Y_THIRD);
    menuLayoutAlgorithm->targetOffset_ = offset;
    SizeF size(SIZE_X_SECOND, SIZE_Y_SECOND);
    menuLayoutAlgorithm->targetSize_ = size;
    auto result = menuLayoutAlgorithm->GetPositionWithPlacementLeftTop(childSize, topPosition, bottomPosition);
    EXPECT_EQ(result.GetX(), PLACEMENT_LEFT_TOP_X);
    EXPECT_EQ(result.GetY(), PLACEMENT_LEFT_TOP_Y);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg029
 * @tc.desc: Verify GetPositionWithPlacementLeftBottom.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm, set childSize, topPosition, bottomPosition, targetOffset and
     * targetSize
     * @tc.expected: step1. position is (targetOffset_.GetX() - childSize.Width(),
     * targetOffset_.GetY() + targetSize_.Height() - childSize.Height())
     */
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF childSize(CHILD_SIZE_X, CHILD_SIZE_Y);
    OffsetF topPosition(TOP_POSITION_X, TOP_POSITION_Y);
    OffsetF bottomPosition(BOTTOM_POSITION_X, BOTTOM_POSITION_Y);
    OffsetF offset(OFFSET_X_THIRD, OFFSET_Y_THIRD);
    menuLayoutAlgorithm->targetOffset_ = offset;
    SizeF size(SIZE_X_SECOND, SIZE_Y_SECOND);
    menuLayoutAlgorithm->targetSize_ = size;
    auto result = menuLayoutAlgorithm->GetPositionWithPlacementLeftBottom(childSize, topPosition, bottomPosition);
    EXPECT_EQ(result.GetX(), PLACEMENT_LEFT_BOTTOM_X);
    EXPECT_EQ(result.GetY(), PLACEMENT_LEFT_BOTTOM_Y);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg030
 * @tc.desc: Verify GetPositionWithPlacementRight.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm, set childSize, topPosition, bottomPosition, targetOffset and
     * targetSize
     * @tc.expected: step1. position is (targetOffset_.GetX() + targetSize_.Width(),
     * targetOffset_.GetY() + targetSize_.Height() / 2.0 - childSize.Height() / 2.0)
     */
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF childSize(CHILD_SIZE_X, CHILD_SIZE_Y);
    OffsetF topPosition(TOP_POSITION_X, TOP_POSITION_Y);
    OffsetF bottomPosition(BOTTOM_POSITION_X, BOTTOM_POSITION_Y);
    OffsetF offset(OFFSET_X_THIRD, OFFSET_Y_THIRD);
    menuLayoutAlgorithm->targetOffset_ = offset;
    SizeF size(SIZE_X_SECOND, SIZE_Y_SECOND);
    menuLayoutAlgorithm->targetSize_ = size;
    auto result = menuLayoutAlgorithm->GetPositionWithPlacementRight(childSize, topPosition, bottomPosition);
    EXPECT_EQ(result.GetX(), PLACEMENT_RIGHT_X);
    EXPECT_EQ(result.GetY(), PLACEMENT_RIGHT_Y);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg031
 * @tc.desc: Verify GetPositionWithPlacementRightTop.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm, set childSize, topPosition, bottomPosition, targetOffset and
     * targetSize
     * @tc.expected: step1. position is (targetOffset_.GetX() + targetSize_.Width(),
     * targetOffset_.GetY())
     */
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF childSize(CHILD_SIZE_X, CHILD_SIZE_Y);
    OffsetF topPosition(TOP_POSITION_X, TOP_POSITION_Y);
    OffsetF bottomPosition(BOTTOM_POSITION_X, BOTTOM_POSITION_Y);
    OffsetF offset(OFFSET_X_THIRD, OFFSET_Y_THIRD);
    menuLayoutAlgorithm->targetOffset_ = offset;
    SizeF size(SIZE_X_SECOND, SIZE_Y_SECOND);
    menuLayoutAlgorithm->targetSize_ = size;
    auto result = menuLayoutAlgorithm->GetPositionWithPlacementRightTop(childSize, topPosition, bottomPosition);
    EXPECT_EQ(result.GetX(), PLACEMENT_RIGHT_TOP_X);
    EXPECT_EQ(result.GetY(), PLACEMENT_RIGHT_TOP_Y);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg032
 * @tc.desc: Verify GetPositionWithPlacementRightBottom.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm, set childSize, topPosition, bottomPosition, targetOffset and
     * targetSize
     * @tc.expected: step1. position is (targetOffset_.GetX() + targetSize_.Width(),
     * targetOffset_.GetY() + targetSize_.Height() - childSize.Height())
     */
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF childSize(CHILD_SIZE_X, CHILD_SIZE_Y);
    OffsetF topPosition(TOP_POSITION_X, TOP_POSITION_Y);
    OffsetF bottomPosition(BOTTOM_POSITION_X, BOTTOM_POSITION_Y);
    OffsetF offset(OFFSET_X_THIRD, OFFSET_Y_THIRD);
    menuLayoutAlgorithm->targetOffset_ = offset;
    SizeF size(SIZE_X_SECOND, SIZE_Y_SECOND);
    menuLayoutAlgorithm->targetSize_ = size;
    auto result = menuLayoutAlgorithm->GetPositionWithPlacementRightBottom(childSize, topPosition, bottomPosition);
    EXPECT_EQ(result.GetX(), PLACEMENT_RIGHT_BOTTOM_X);
    EXPECT_EQ(result.GetY(), PLACEMENT_RIGHT_BOTTOM_Y);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg033
 * @tc.desc: Test SubMenu layout algorithm.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg033, TestSize.Level1)
{
    // create parent menu item
    auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
    auto item = AceType::MakeRefPtr<FrameNode>("MenuItem", -1, itemPattern);
    // set parent item size
    auto itemGeometryNode = item->GetGeometryNode();
    ASSERT_TRUE(itemGeometryNode);
    item->GetGeometryNode()->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));

    // create submenu
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::SUB_MENU);
    auto subMenu = AceType::MakeRefPtr<FrameNode>("", -1, menuPattern);
    auto algorithm = AceType::DynamicCast<SubMenuLayoutAlgorithm>(menuPattern->CreateLayoutAlgorithm());
    ASSERT_TRUE(algorithm);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT));
    auto layoutProp = AceType::MakeRefPtr<MenuLayoutProperty>();
    auto* wrapper = new LayoutWrapper(subMenu, geometryNode, layoutProp);
    // link parent menu item and sub menu
    ASSERT_TRUE(menuPattern);
    menuPattern->SetParentMenuItem(item);
    item->GetGeometryNode()->SetFrameOffset(OffsetF(MENU_OFFSET_X, MENU_OFFSET_Y));
    algorithm->pageOffset_ = OffsetF();
    algorithm->wrapperSize_ = SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);

    // @tc.cases: case1. sub menu show on the right side of item
    algorithm->position_ = OffsetF(MENU_OFFSET_X + MENU_ITEM_SIZE_WIDTH, MENU_OFFSET_Y);
    algorithm->Layout(wrapper);

    EXPECT_EQ(wrapper->GetGeometryNode()->GetMarginFrameOffset(),
        OffsetF(MENU_OFFSET_X + MENU_ITEM_SIZE_WIDTH, MENU_OFFSET_Y));

    // @tc.cases: case2. sub menu show on the left side of item
    algorithm->position_ = OffsetF(FULL_SCREEN_WIDTH, MENU_OFFSET_Y);
    algorithm->Layout(wrapper);

    EXPECT_EQ(wrapper->GetGeometryNode()->GetMarginFrameOffset().GetX(),
        (FULL_SCREEN_WIDTH - MENU_ITEM_SIZE_WIDTH - MENU_SIZE_WIDTH));
    EXPECT_EQ(wrapper->GetGeometryNode()->GetMarginFrameOffset().GetY(), MENU_OFFSET_Y);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg034
 * @tc.desc: Test MultiMenu measure algorithm.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg034, TestSize.Level1)
{
    // set screen width for grid column
    ScreenSystemManager::GetInstance().SetWindowInfo(FULL_SCREEN_WIDTH, 1.0, 1.0);
    // create multi menu
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::MULTI_MENU);
    auto multiMenu = AceType::MakeRefPtr<FrameNode>("", -1, menuPattern);
    auto algorithm = AceType::MakeRefPtr<MultiMenuLayoutAlgorithm>();
    ASSERT_TRUE(algorithm);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProp = AceType::MakeRefPtr<MenuLayoutProperty>();
    auto* wrapper = new LayoutWrapper(multiMenu, geometryNode, layoutProp);
    // create menu item
    for (int32_t i = 0; i < 3; ++i) {
        auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
        auto menuItem = AceType::MakeRefPtr<FrameNode>("", -1, itemPattern);
        auto itemGeoNode = AceType::MakeRefPtr<GeometryNode>();
        itemGeoNode->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
        auto childWrapper = AceType::MakeRefPtr<LayoutWrapper>(menuItem, itemGeoNode, layoutProp);
        wrapper->AppendChild(childWrapper);
    }

    algorithm->Measure(wrapper);
    // @tc.expected: menu content width = item width, height = sum(item height)
    auto expectedSize = SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT * 3);
    EXPECT_EQ(wrapper->GetGeometryNode()->GetContentSize(), expectedSize);
}
} // namespace OHOS::Ace::NG
