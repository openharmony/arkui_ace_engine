/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "grid_test_ng.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"

#include "core/components_ng/pattern/grid/grid_item_pattern.h"
namespace OHOS::Ace::NG {

namespace {
const InspectorFilter filter;
constexpr Dimension DEFAULT_SCROLL_WIDTH = 4.0_vp;
constexpr Dimension TEST_10_VP = 10.0_vp;
constexpr Dimension TEST_20_VP = 20.0_vp;
constexpr Color DEFAULT_SCROLL_BAR_COLOR = Color(0x66182431);
} // namespace
class GridAttrTestTwoNg : public GridTestNg {
public:
    AssertionResult VerifyBigItemRect(int32_t index, RectF expectRect);
};

AssertionResult GridAttrTestTwoNg::VerifyBigItemRect(int32_t index, RectF expectRect)
{
    return IsEqual(GetChildRect(frameNode_, index), expectRect);
}

/**
 * @tc.name: EdgeEffectOption001
 * @tc.desc: Test EdgeEffectOption
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestTwoNg, EdgeEffectOption001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFixedItems(20);
    model.SetEdgeEffect(EdgeEffect::SPRING, false);
    CreateDone();
    EXPECT_FALSE(pattern_->GetAlwaysEnabled());
    EXPECT_TRUE(pattern_->scrollable_);
}

/**
 * @tc.name: EdgeEffectOption002
 * @tc.desc: Test EdgeEffectOption
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestTwoNg, EdgeEffectOption002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFixedItems(20);
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateDone();
    EXPECT_TRUE(pattern_->GetAlwaysEnabled());
    EXPECT_TRUE(pattern_->scrollable_);
}

/**
 * @tc.name: EdgeEffectOption003
 * @tc.desc: Test EdgeEffectOption
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestTwoNg, EdgeEffectOption003, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFixedItems(3); // 3 is item count
    model.SetEdgeEffect(EdgeEffect::SPRING, false);
    CreateDone();
    EXPECT_FALSE(pattern_->GetAlwaysEnabled());
    EXPECT_FALSE(pattern_->scrollable_);
}

/**
 * @tc.name: EdgeEffectOption004
 * @tc.desc: Test EdgeEffectOption
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestTwoNg, EdgeEffectOption004, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFixedItems(3); // 3 is item count
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateDone();
    EXPECT_TRUE(pattern_->GetAlwaysEnabled());
    EXPECT_TRUE(pattern_->scrollable_);
}

/**
 * @tc.name: EdgeEffectOption005
 * @tc.desc: Test EdgeEffectOption
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestTwoNg, EdgeEffectOption005, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFixedItems(3); // 3 is item count
    model.SetEdgeEffect(EdgeEffect::SPRING, true, EffectEdge::ALL);
    CreateDone();
    EXPECT_TRUE(pattern_->GetAlwaysEnabled());
    EXPECT_TRUE(pattern_->scrollable_);
    EXPECT_EQ(pattern_->GetEffectEdge(), EffectEdge::ALL);
}

/**
 * @tc.name: GridSetFriction001
 * @tc.desc: Test SetFriction Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestTwoNg, GridSetFriction001, TestSize.Level1)
{
    /**
     * @tc.cases: Set friction less than zero
     * @tc.expected: friction would be default
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetFriction(-1.0);
    CreateDone();
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), DEFAULT_FRICTION);
}

/**
 * @tc.name: GridSetFriction002
 * @tc.desc: Test SetFriction Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestTwoNg, GridSetFriction002, TestSize.Level1)
{
    /**
     * @tc.cases: Set friction equal to zero
     * @tc.expected: friction would be default
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetFriction(0.0);
    CreateDone();
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), DEFAULT_FRICTION);
}

/**
 * @tc.name: GridSetFriction003
 * @tc.desc: Test SetFriction Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestTwoNg, GridSetFriction003, TestSize.Level1)
{
    /**
     * @tc.cases: Set friction greater than zero
     * @tc.expected: Friction would be itself
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetFriction(1.0);
    CreateDone();
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), 1.0);
}

/**
 * @tc.name: GridItemHoverEventTest001
 * @tc.desc: GridItem hover event test.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestTwoNg, GridItemHoverEventTest001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFixedItems(10, GridItemStyle::PLAIN);
    CreateDone();
    auto gridItemNode = GetChildFrameNode(frameNode_, 0);
    auto gridItemPattern = GetChildPattern<GridItemPattern>(frameNode_, 0);
    auto gridItemeventHub = gridItemNode->GetEventHub<GridItemEventHub>();
    auto gridItemInputHub = gridItemeventHub->GetOrCreateInputEventHub();
    auto HandleHoverEvent = gridItemInputHub->hoverEventActuator_->inputEvents_.back()->GetOnHoverEventFunc();

    /**
     * @tc.steps: step1. Hover gridItem
     * @tc.expected: isHover_ is true
     */
    HandleHoverEvent(true);
    EXPECT_TRUE(gridItemPattern->isHover_);

    /**
     * @tc.steps: step2. Leave gridItem
     * @tc.expected: isHover_ is false
     */
    HandleHoverEvent(false);
    EXPECT_FALSE(gridItemPattern->isHover_);
}

/**
 * @tc.name: GridItemPressEventTest001
 * @tc.desc: GridItem press event test.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestTwoNg, GridItemPressEventTest001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFixedItems(10, GridItemStyle::PLAIN);
    CreateDone();
    auto gridItemNode = GetChildFrameNode(frameNode_, 0);
    auto gridItemPattern = GetChildPattern<GridItemPattern>(frameNode_, 0);
    auto gridItemeventHub = gridItemNode->GetEventHub<GridItemEventHub>();
    auto gridItemGesture = gridItemeventHub->GetOrCreateGestureEventHub();
    auto HandlePressEvent = gridItemGesture->touchEventActuator_->touchEvents_.back()->GetTouchEventCallback();

    /**
     * @tc.steps: step1. Press gridItem
     * @tc.expected: isPressed_ is true
     */
    auto info = CreateTouchEventInfo(TouchType::DOWN, Offset::Zero());
    HandlePressEvent(info);
    EXPECT_TRUE(gridItemPattern->isPressed_);

    /**
     * @tc.steps: step2. Move on gridItem
     * @tc.expected: isPressed_ not change
     */
    info = CreateTouchEventInfo(TouchType::MOVE, Offset(10.f, 10.f));
    HandlePressEvent(info);
    EXPECT_TRUE(gridItemPattern->isPressed_);

    /**
     * @tc.steps: step3. Release gridItem
     * @tc.expected: isPressed_ is false
     */
    info = CreateTouchEventInfo(TouchType::UP, Offset(10.f, 10.f));
    HandlePressEvent(info);
    EXPECT_FALSE(gridItemPattern->isPressed_);
}

/**
 * @tc.name: GridItemSetSelectableTest001
 * @tc.desc: GridItem setselectable test.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestTwoNg, GridItemSetSelectableTest001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFixedItems(20);
    CreateDone();

    /**
     * @tc.steps: step1. Get gridItemPattern.
     */
    auto gridItemPattern = GetChildPattern<GridItemPattern>(frameNode_, 0);

    /**
     * @tc.steps: step2. When gridItem is unSelectable isSelected_ and selectable_ is true.
     * @tc.expected: gridItemPattern->selectable_ is false.
     */
    gridItemPattern->isSelected_ = true;
    gridItemPattern->selectable_ = true;
    gridItemPattern->SetSelectable(false);
    EXPECT_FALSE(gridItemPattern->selectable_);
}

/**
 * @tc.name: GridItemDisableEventTest001
 * @tc.desc: GridItem disable event test.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestTwoNg, GridItemDisableEventTest001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    CreateFixedItems(10, GridItemStyle::PLAIN);
    CreateDone();

    /**
     * @tc.steps: step2. Get gridItem frameNode and pattern, set callback function.
     * @tc.expected: Related function is called.
     */
    auto gridItemPattern = GetChildPattern<GridItemPattern>(frameNode_, 0);
    auto gridItemEventHub = GetChildEventHub<GridItemEventHub>(frameNode_, 0);
    auto gridItemFrameNode = GetChildFrameNode(frameNode_, 0);
    auto renderContext = gridItemFrameNode->renderContext_;
    auto mockRenderContext = AceType::DynamicCast<MockRenderContext>(renderContext);
    EXPECT_EQ(mockRenderContext->opacityMultiplier_, 1.0f);
    gridItemEventHub->SetEnabled(false);
    gridItemPattern->InitDisableStyle();
    EXPECT_EQ(mockRenderContext->opacityMultiplier_, 0.4f);
    gridItemEventHub->SetEnabled(true);
    gridItemPattern->InitDisableStyle();
    EXPECT_EQ(mockRenderContext->opacityMultiplier_, 1.0f);
}

/**
 * @tc.name: GridItemDisableEventTest002
 * @tc.desc: GridItem disable event test.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestTwoNg, GridItemDisableEventTest002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    CreateFixedItems(10, GridItemStyle::PLAIN);
    CreateDone();

    /**
     * @tc.steps: step2. Get gridItem frameNode and pattern, set callback function.
     * @tc.expected: Related function is called.
     */
    auto gridItemPattern = GetChildPattern<GridItemPattern>(frameNode_, 0);
    auto gridItemEventHub = GetChildEventHub<GridItemEventHub>(frameNode_, 0);
    auto gridItemFrameNode = GetChildFrameNode(frameNode_, 0);
    auto renderContext = gridItemFrameNode->renderContext_;
    auto mockRenderContext = AceType::DynamicCast<MockRenderContext>(renderContext);
    EXPECT_EQ(mockRenderContext->opacityMultiplier_, 1.0f);
    gridItemEventHub->SetEnabled(false);
    gridItemPattern->InitDisableStyle();
    EXPECT_EQ(mockRenderContext->opacityMultiplier_, 0.4f);
    gridItemPattern->InitDisableStyle();
    EXPECT_EQ(mockRenderContext->opacityMultiplier_, 0.4f);
}

/**
 * @tc.name: Property005
 * @tc.desc: Test selectable and selected of GridItem.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestTwoNg, Property005, TestSize.Level1)
{
    GridItemModelNG itemModel;
    itemModel.Create(GridItemStyle::NONE);
    itemModel.SetSelectable(false);
    itemModel.SetOnSelect([](bool) {});
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = frameNode->GetPattern<GridItemPattern>();

    /**
     * @tc.steps: step1. Test ToJsonValue
     */
    auto json = JsonUtil::Create(true);
    pattern->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("selected"), "false");
    EXPECT_EQ(json->GetString("selectable"), "false");

    /**
     * @tc.steps: step2. Update GridItemPattern Test ToJsonValue
     */
    pattern->SetSelectable(true);
    pattern->SetSelected(true);
    json = JsonUtil::Create(true);
    pattern->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("selected"), "true");
    EXPECT_EQ(json->GetString("selectable"), "true");
}

/**
 * @tc.name: GridItemStyleTest
 * @tc.desc: GridItem get itemStyle test.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestTwoNg, GridItemStyleTest, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    CreateFixedItems(10, GridItemStyle::PLAIN);
    CreateDone();

    auto itemModel  = CreateGridItem(60, 550);
    auto node = GetChildFrameNode(frameNode_, 0);
    auto pattern = node->GetPattern<GridItemPattern>();
    ASSERT_NE(pattern, nullptr);
    itemModel.SetGridItemStyle(node.GetRawPtr(), GridItemStyle::NONE);
    auto itemStyle = itemModel.GetGridItemStyle(node.GetRawPtr());
    EXPECT_EQ(itemStyle, GridItemStyle::NONE);
    auto gridItemPattern = GetChildPattern<GridItemPattern>(frameNode_, 0);
    ASSERT_NE(gridItemPattern, nullptr);
    EXPECT_EQ(gridItemPattern->GetGridItemStyle(), GridItemStyle::NONE);

    itemModel.SetGridItemStyle(node.GetRawPtr(), GridItemStyle::PLAIN);
    itemStyle = itemModel.GetGridItemStyle(node.GetRawPtr());
    EXPECT_EQ(itemStyle, GridItemStyle::PLAIN);
    EXPECT_EQ(gridItemPattern->GetGridItemStyle(), GridItemStyle::PLAIN);

    itemStyle = itemModel.GetGridItemStyle(nullptr);
    EXPECT_EQ(itemStyle, GridItemStyle::NONE);

    node->pattern_ = nullptr;
    itemStyle = itemModel.GetGridItemStyle(node.GetRawPtr());
    EXPECT_EQ(itemStyle, GridItemStyle::NONE);
    node->pattern_ = pattern;
}

/**
 * @tc.name: AlignItemsTest
 * @tc.desc: GridModelNG GetAlignItems test.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestTwoNg, AlignItemsTest, TestSize.Level1)
{
    GridModelNG gridModel = CreateGrid();
    CreateFixedItems(10, GridItemStyle::PLAIN);
    CreateDone();

    auto node = AceType::RawPtr(frameNode_);
    ASSERT_NE(node, nullptr);

    gridModel.SetAlignItems(node, GridItemAlignment::DEFAULT);
    EXPECT_EQ(gridModel.GetAlignItems(node), GridItemAlignment::DEFAULT);

    gridModel.SetAlignItems(node, GridItemAlignment::STRETCH);
    EXPECT_EQ(gridModel.GetAlignItems(node), GridItemAlignment::STRETCH);

    EXPECT_EQ(gridModel.GetAlignItems(nullptr), GridItemAlignment::DEFAULT);
}

/**
 * @tc.name: ScrollBarModeTest
 * @tc.desc: GridModelNG GetScrollBarMode test.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestTwoNg, ScrollBarModeTest, TestSize.Level1)
{
    GridModelNG gridModel = CreateGrid();
    gridModel.SetColumnsTemplate("1fr 1fr");
    gridModel.SetScrollBarMode(DisplayMode::ON);
    CreateFixedItems(10, GridItemStyle::PLAIN);
    CreateDone();
    
    auto node = AceType::RawPtr(frameNode_);
    ASSERT_NE(node, nullptr);
    gridModel.SetScrollBarMode(node,  DisplayMode::AUTO);
    EXPECT_EQ(gridModel.GetScrollBarMode(node), static_cast<int32_t>(DisplayMode::AUTO));

    gridModel.SetScrollBarMode(node, DisplayMode::ON);
    EXPECT_EQ(gridModel.GetScrollBarMode(node), static_cast<int32_t>(DisplayMode::ON));

    gridModel.SetScrollBarMode(node, DisplayMode::OFF);
    EXPECT_EQ(gridModel.GetScrollBarMode(node), static_cast<int32_t>(DisplayMode::OFF));

    EXPECT_EQ(gridModel.GetScrollBarMode(nullptr), static_cast<int32_t>(DisplayMode::AUTO));
}

/**
 * @tc.name: ScrollBarWidthTest
 * @tc.desc: GridModelNG GetScrollBarWidth test.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestTwoNg, ScrollBarWidthTest, TestSize.Level1)
{
    GridModelNG gridModel = CreateGrid();
    CreateFixedItems(10, GridItemStyle::PLAIN);
    CreateDone();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<ScrollBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    auto node = AceType::RawPtr(frameNode_);
    gridModel.SetScrollBarWidth(node, TEST_10_VP);
    EXPECT_EQ(gridModel.GetScrollBarWidth(node), TEST_10_VP.ConvertToVp());

    gridModel.SetScrollBarWidth(node, TEST_20_VP);
    EXPECT_EQ(gridModel.GetScrollBarWidth(node), TEST_20_VP.ConvertToVp());

    EXPECT_EQ(gridModel.GetScrollBarWidth(nullptr), DEFAULT_SCROLL_WIDTH.ConvertToVp());
}

/**
 * @tc.name: ScrollBarColorTest
 * @tc.desc: GridModelNG GetScrollColor test.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestTwoNg, ScrollBarColorTest, TestSize.Level1)
{
    GridModelNG gridModel = CreateGrid();
    CreateFixedItems(10, GridItemStyle::PLAIN);
    CreateDone();

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<ScrollBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));

    auto node = AceType::RawPtr(frameNode_);
    ASSERT_NE(node, nullptr);
    gridModel.SetScrollBarColor(node, Color::RED);
    EXPECT_EQ(gridModel.GetScrollBarColor(node), Color::RED.GetValue());

    gridModel.SetScrollBarColor(node, Color::BLUE);
    EXPECT_EQ(gridModel.GetScrollBarColor(node), Color::BLUE.GetValue());

    EXPECT_EQ(gridModel.GetScrollBarColor(nullptr), DEFAULT_SCROLL_BAR_COLOR.GetValue());
}

/**
 * @tc.name: GetNestedScrollTest
 * @tc.desc: GridModelNG GetNestedScroll test.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestTwoNg, GetNestedScrollTest, TestSize.Level1)
{
    GridModelNG gridModel = CreateGrid();
    CreateFixedItems(10, GridItemStyle::PLAIN);
    CreateDone();

    auto node = AceType::RawPtr(frameNode_);
    ASSERT_NE(node, nullptr);
    auto pattern = node->GetPattern<GridPattern>();
    ASSERT_NE(pattern, nullptr);
    NestedScrollOptions retNestedScrollOptions = gridModel.GetNestedScroll(node);
    EXPECT_EQ(retNestedScrollOptions.forward, NestedScrollMode::SELF_ONLY);
    EXPECT_EQ(retNestedScrollOptions.backward, NestedScrollMode::SELF_ONLY);

    NestedScrollOptions nestedScrollOptions;
    nestedScrollOptions.forward = NestedScrollMode::PARENT_FIRST;
    nestedScrollOptions.backward = NestedScrollMode::PARENT_FIRST;

    gridModel.SetNestedScroll(node, nestedScrollOptions);
    retNestedScrollOptions = gridModel.GetNestedScroll(node);
    EXPECT_EQ(retNestedScrollOptions.forward, NestedScrollMode::PARENT_FIRST);
    EXPECT_EQ(retNestedScrollOptions.backward, NestedScrollMode::PARENT_FIRST);

    retNestedScrollOptions = gridModel.GetNestedScroll(nullptr);
    EXPECT_EQ(retNestedScrollOptions.forward, NestedScrollMode::SELF_ONLY);
    EXPECT_EQ(retNestedScrollOptions.backward, NestedScrollMode::SELF_ONLY);

    node->pattern_ = nullptr;
    retNestedScrollOptions = gridModel.GetNestedScroll(node);
    EXPECT_EQ(retNestedScrollOptions.forward, NestedScrollMode::SELF_ONLY);
    EXPECT_EQ(retNestedScrollOptions.backward, NestedScrollMode::SELF_ONLY);
    node->pattern_ = pattern;
}

/**
 * @tc.name: GetScrollEnabledTest
 * @tc.desc: GridModelNG GetScrollEnabled test.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestTwoNg, GetScrollEnabledTest, TestSize.Level1)
{
    GridModelNG gridModel = CreateGrid();
    CreateFixedItems(10, GridItemStyle::PLAIN);
    CreateDone();

    auto node = AceType::RawPtr(frameNode_);
    ASSERT_NE(node, nullptr);
    gridModel.SetScrollEnabled(node, true);
    EXPECT_TRUE(gridModel.GetScrollEnabled(node));
    
    gridModel.SetScrollEnabled(node, false);
    EXPECT_FALSE(gridModel.GetScrollEnabled(node));

    EXPECT_TRUE(gridModel.GetScrollEnabled(nullptr));
}

/**
 * @tc.name: GetFrictionTest001
 * @tc.desc: GridModelNG GetFriction test.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestTwoNg, GetFrictionTest001, TestSize.Level1)
{
    MockContainer::SetUp();
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    GridModelNG gridModel = CreateGrid();
    CreateFixedItems(10, GridItemStyle::PLAIN);
    CreateDone();

    auto node = AceType::RawPtr(frameNode_);
    ASSERT_NE(node, nullptr);
    auto pattern = node->GetPattern<GridPattern>();
    ASSERT_NE(pattern, nullptr);
    gridModel.SetFriction(node, 0.8);
    EXPECT_EQ(gridModel.GetFriction(node),  0.8);
#ifndef WEARABLE_PRODUCT
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<ScrollableTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    auto friction = theme->GetFriction();

    node->pattern_ = nullptr;
    EXPECT_EQ(node->GetPattern<GridPattern>(), nullptr);
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    EXPECT_EQ(gridModel.GetFriction(nullptr), FRICTION);
    EXPECT_EQ(gridModel.GetFriction(node), FRICTION);

    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    EXPECT_EQ(gridModel.GetFriction(nullptr),  API11_FRICTION);
    EXPECT_EQ(gridModel.GetFriction(node), API11_FRICTION);

    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    EXPECT_EQ(gridModel.GetFriction(nullptr),  API12_FRICTION);
    EXPECT_EQ(gridModel.GetFriction(node), API12_FRICTION);

    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN));
    EXPECT_EQ(gridModel.GetFriction(nullptr),  friction);
    EXPECT_EQ(gridModel.GetFriction(node), friction);
    node->pattern_ = pattern;
#endif
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
    MockContainer::TearDown();
}

/**
 * @tc.name: GetFrictionTest002
 * @tc.desc: GridModelNG GetFriction test.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestTwoNg, GetFrictionTest002, TestSize.Level1)
{
    MockContainer::SetUp();
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    GridModelNG gridModel = CreateGrid();
    CreateFixedItems(10, GridItemStyle::PLAIN);
    CreateDone();

    auto node = AceType::RawPtr(frameNode_);
    ASSERT_NE(node, nullptr);
    auto pattern = node->GetPattern<GridPattern>();
    ASSERT_NE(pattern, nullptr);
#ifndef WEARABLE_PRODUCT
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<ScrollableTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    auto friction = theme->GetFriction();

    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    gridModel.SetFriction(node, std::optional<double>());
    EXPECT_EQ(gridModel.GetFriction(node), FRICTION);

    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    gridModel.SetFriction(node, std::optional<double>());
    EXPECT_EQ(gridModel.GetFriction(node), API11_FRICTION);

    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    gridModel.SetFriction(node, std::optional<double>());
    EXPECT_EQ(gridModel.GetFriction(node), API12_FRICTION);

    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN));
    gridModel.SetFriction(node, std::optional<double>());
    EXPECT_EQ(gridModel.GetFriction(node), friction);
#endif
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
    MockContainer::TearDown();
}

/**
 * @tc.name: GetDefaultFriction
 * @tc.desc: Test GetDefaultFriction function
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GetDefaultFriction, TestSize.Level1)
{
    MockContainer::SetUp();
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<ScrollableTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    auto friction = theme->GetFriction();

#ifndef WEARABLE_PRODUCT
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    EXPECT_EQ(gridPattern->GetDefaultFriction(), OHOS::Ace::NG::FRICTION);
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    EXPECT_EQ(gridPattern->GetDefaultFriction(), OHOS::Ace::NG::API11_FRICTION);
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    EXPECT_EQ(gridPattern->GetDefaultFriction(), OHOS::Ace::NG::API12_FRICTION);
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN));
    EXPECT_EQ(gridPattern->GetDefaultFriction(), friction);
#else
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    EXPECT_EQ(gridPattern->GetDefaultFriction(), OHOS::Ace::NG::FRICTION);

    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    EXPECT_EQ(gridPattern->GetDefaultFriction(), OHOS::Ace::NG::FRICTION);

    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));;
    EXPECT_EQ(gridPattern->GetDefaultFriction(), OHOS::Ace::NG::FRICTION);

    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN));
    EXPECT_EQ(gridPattern->GetDefaultFriction(), OHOS::Ace::NG::FRICTION);
#endif
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
    MockContainer::TearDown();
}

/**
 * @tc.name: GetLayoutOptionsTest001
 * @tc.desc: GridModelNG GetLayoutOptions test.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestTwoNg, GridModelNGTest008, TestSize.Level1)
{
    GridModelNG gridModel = CreateGrid();
    CreateFixedItems(10, GridItemStyle::PLAIN);
    CreateDone();

    auto node = AceType::RawPtr(frameNode_);
    ASSERT_NE(node, nullptr);
    GridLayoutOptions option;
    option.irregularIndexes = { 6, 1, 3, 4, 5, 0 };
    GetSizeByIndex onGetIrregularSizeByIndex = [](int32_t index) {
        if (index == 3) {
            return GridItemSize { 1, 2 };
        }
        return GridItemSize { 1, 4 };
    };
    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);

    GetRectByIndex onGetRectByIndex = [](int32_t index) -> GridItemRect {
        GridItemRect itemRect = { 0, 0, 1, 1 };
        return itemRect;
    };
    option.getRectByIndex = std::move(onGetRectByIndex);
    gridModel.SetLayoutOptions(node, option);
    auto retOption = gridModel.GetLayoutOptions(node);
    ASSERT_NE(retOption, std::nullopt);
    EXPECT_EQ(retOption->irregularIndexes, option.irregularIndexes);
    ASSERT_NE(retOption->getSizeByIndex, nullptr);
    EXPECT_EQ(retOption->getSizeByIndex(3).rows, 1);
    EXPECT_EQ(retOption->getSizeByIndex(3).columns, 2);
    EXPECT_EQ(retOption->getSizeByIndex(0).rows, 1);
    EXPECT_EQ(retOption->getSizeByIndex(0).columns, 4);
}

/**
 * @tc.name: SelectableTest
 * @tc.desc: GridModelNG GetSelectableTest test.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestTwoNg, SelectableTest, TestSize.Level1)
{
    auto node = GridItemModelNG::CreateFrameNode(-1);
    ASSERT_NE(node, nullptr);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(frameNode, nullptr);

    GridItemModelNG::SetSelectable(frameNode, false);
    EXPECT_EQ(GridItemModelNG::GetSelectable(frameNode), false);

    GridItemModelNG::SetSelectable(frameNode, true);
    EXPECT_EQ(GridItemModelNG::GetSelectable(frameNode), true);
}

/**
 * @tc.name: EditableTest
 * @tc.desc: GridModelNG GetEditable test.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestTwoNg, EditableTest, TestSize.Level1)
{
    GridModelNG gridModel = CreateGrid();
    CreateFixedItems(10, GridItemStyle::PLAIN);
    CreateDone();

    auto node = AceType::RawPtr(frameNode_);
    ASSERT_NE(node, nullptr);

    gridModel.SetEditable(node, false);
    EXPECT_EQ(gridModel.GetEditable(node), false);

    gridModel.SetEditable(node, true);
    EXPECT_EQ(gridModel.GetEditable(node), true);

    EXPECT_EQ(gridModel.GetEditable(nullptr), false);
}

/**
 * @tc.name: MultiSelectableTest
 * @tc.desc: GridModelNG GetMultiSelectable test.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestTwoNg, MultiSelectableTest, TestSize.Level1)
{
    GridModelNG gridModel = CreateGrid();
    CreateFixedItems(10, GridItemStyle::PLAIN);
    CreateDone();

    auto node = AceType::RawPtr(frameNode_);
    ASSERT_NE(node, nullptr);

    gridModel.SetMultiSelectable(node, false);
    EXPECT_EQ(gridModel.GetMultiSelectable(node), false);

    gridModel.SetMultiSelectable(node, true);
    EXPECT_EQ(gridModel.GetMultiSelectable(node), true);

    EXPECT_EQ(gridModel.GetMultiSelectable(nullptr), false);
}

/**
 * @tc.name: SupportAnimationTest
 * @tc.desc: GridModelNG GetMultiSelectable test.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestTwoNg, GetSupportAnimation, TestSize.Level1)
{
    GridModelNG gridModel = CreateGrid();
    CreateFixedItems(10, GridItemStyle::PLAIN);
    CreateDone();

    auto node = AceType::RawPtr(frameNode_);
    ASSERT_NE(node, nullptr);

    gridModel.SetSupportAnimation(node, false);
    EXPECT_EQ(gridModel.GetSupportAnimation(node), false);

    gridModel.SetSupportAnimation(node, true);
    EXPECT_EQ(gridModel.GetSupportAnimation(node), true);

    EXPECT_EQ(gridModel.GetSupportAnimation(nullptr), false);
}

/*
 * @tc.name: ResetLayoutPolicy
 * @tc.desc: GridModelNG ResetLayoutPolicy test.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestTwoNg, ResetLayoutPolicy, TestSize.Level1)
{
    GridModelNG gridModel = CreateGrid();
    CreateFixedItems(10, GridItemStyle::PLAIN);
    ViewAbstract::UpdateLayoutPolicyProperty(AceType::RawPtr(frameNode_), LayoutCalPolicy::MATCH_PARENT, false);
    EXPECT_TRUE(layoutProperty_->GetLayoutPolicyProperty().value().IsHeightMatch());
    gridModel.ReSetGridHeightLayoutPolicy();
    EXPECT_TRUE(layoutProperty_->GetLayoutPolicyProperty().value().IsHeightNoMatch());
    CreateDone();
}

/*
 * @tc.name: ResetColumnsTemplate
 * @tc.desc: GridModelNG ResetColumnsTemplate test.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestTwoNg, ResetColumnsTemplate, TestSize.Level1)
{
    GridModelNG gridModel = CreateGrid();
    gridModel.SetColumnsTemplate("1fr");
    gridModel.SetScrollBarMode(DisplayMode::ON);
    CreateFixedItems(20);
    CreateDone();
    /**
     * @tc.steps: step1. Reset columnsTemplate.
     * @tc.expected: Grid scrollBar will be free.
     */
    layoutProperty_->ResetColumnsTemplate();
    layoutProperty_->OnColumnsTemplateUpdate("");
    pattern_->OnModifyDone();
    FlushUITasks(frameNode_);
    RefPtr<ScrollBar> scrollBar = pattern_->GetScrollBar();
    EXPECT_FALSE(scrollBar);
}

/*
 * @tc.name: ResetRowsTemplate
 * @tc.desc: GridModelNG ResetRowsTemplate test.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestTwoNg, ResetRowsTemplate, TestSize.Level1)
{
    GridModelNG gridModel = CreateGrid();
    gridModel.SetRowsTemplate("1fr");
    gridModel.SetScrollBarMode(DisplayMode::ON);
    CreateFixedItems(20);
    CreateDone();
    /**
     * @tc.steps: step1. Reset rowsTemplate.
     * @tc.expected: Grid scrollBar will be free.
     */
    layoutProperty_->ResetRowsTemplate();
    layoutProperty_->OnRowsTemplateUpdate("");
    pattern_->OnModifyDone();
    FlushUITasks(frameNode_);
    RefPtr<ScrollBar> scrollBar = pattern_->GetScrollBar();
    EXPECT_FALSE(scrollBar);
}
} // namespace OHOS::Ace::NG