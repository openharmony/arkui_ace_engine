/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include <optional>
#include <vector>
#include <string>

#include "gtest/gtest.h"

#include "base/geometry/dimension.h"
#include "base/geometry/offset.h"
#include "base/geometry/point.h"
#include "base/geometry/rect.h"

#define protected public
#define private public
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "base/memory/ace_type.h"
#include "core/common/container.h"
#include "base/memory/memory_monitor_def.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/panel/drag_bar_pattern.h"
#include "core/components_ng/pattern/panel/drag_bar_layout_algorithm.h"
#include "core/components_ng/pattern/panel/drag_bar_layout_property.h"
#include "core/components_ng/pattern/panel/drag_bar_paint_method.h"
#include "core/components_ng/pattern/panel/drag_bar_paint_property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
// Test constants definition
constexpr double TEST_DIMENSION_VAL = 10.0;
constexpr double TEST_OFFSET_VAL = 20.0;
constexpr float HALF_FLOAT = 2.0f;
constexpr float EPSILON = 0.001f;
constexpr DimensionUnit TEST_DIMENSION_UNIT = DimensionUnit::VP;
constexpr Dimension DRAG_ICON_WIDTH = 64.0_vp;
constexpr Dimension DRAG_ICON_HEIGHT = 24.0_vp;
constexpr Dimension HOT_REGION_WIDTH = 64.0_vp;
constexpr Dimension HOT_REGION_HEIGHT = 24.0_vp;
constexpr Dimension PADDING = 16.0_vp;

// Panel mode position constants for comprehensive testing
constexpr float MINI_PANEL_LEFT_X = 10.0f;
constexpr float MINI_PANEL_LEFT_Y = 20.0f;
constexpr float HALF_PANEL_CENTER_X = 150.0f;
constexpr float HALF_PANEL_CENTER_Y = 75.0f;
constexpr float FULL_PANEL_RIGHT_X = 300.0f;
constexpr float FULL_PANEL_RIGHT_Y = 100.0f;

// Hot region height test constants
constexpr float MIN_HOT_REGION_HEIGHT = 20.0f;     // Minimum reasonable height for touch target
constexpr float DEFAULT_HOT_REGION_HEIGHT = 24.0f; // Typical default height
constexpr float LARGE_HOT_REGION_HEIGHT = 40.0f;   // Larger height for better accessibility
constexpr float EDGE_CASE_HEIGHT = 0.0f;           // Edge case: zero height
constexpr float HOT_REGION_HEIGHT_NORMAL = 24.0f;
constexpr float HOT_REGION_HEIGHT_FULLSCREEN = 32.0f;
constexpr float UPDATED_HOT_REGION_HEIGHT = 28.0f;

// Layout algorithm test constants
constexpr float TEST_HOT_REGION_HEIGHT_SMALL = 20.0f;
constexpr float TEST_HOT_REGION_HEIGHT_MEDIUM = 30.0f;
constexpr float TEST_HOT_REGION_HEIGHT_LARGE = 40.0f;

// Constraint test constants
constexpr float CONSTRAINT_WIDTH = 200.0f;
constexpr float CONSTRAINT_HEIGHT = 100.0f;
constexpr float MAX_WIDTH = 400.0f;
constexpr float MAX_HEIGHT = 800.0f;
constexpr float SCREEN_WIDTH = 800.0f;
constexpr float SCREEN_HEIGHT = 1600.0f;
constexpr float SMALL_MAX_WIDTH = 100.0f;
constexpr float SMALL_MAX_HEIGHT = 50.0f;
constexpr float SMALL_MIN_SIZE = 10.0f;
constexpr float EXACT_WIDTH = 300.0f;
constexpr float EXACT_HEIGHT = 60.0f;
constexpr float FULL_SCREEN_WIDTH = 600.0f;
constexpr float FULL_SCREEN_HEIGHT = 1200.0f;
constexpr float TEST_WIDTH = 300.0f;
constexpr float TEST_HEIGHT = 100.0f;
constexpr float CONSTRAINT_WIDTH_LARGE = 500.0f;
constexpr float CONSTRAINT_HEIGHT_LARGE = 200.0f;

// Opacity test constants
constexpr float TEST_OPACITY_1 = 0.7f;
constexpr float TEST_OPACITY_2 = 0.8f;
constexpr float DEFAULT_OPACITY = 1.0f;

// Default values for property testing
constexpr bool DEFAULT_FULL_SCREEN_MODE = false;
constexpr float DEFAULT_HOT_REGION_HEIGHT_VALUE = 24.0f;
constexpr PanelMode DEFAULT_PANEL_MODE = PanelMode::FULL;
constexpr float DEFAULT_DRAG_OFFSET_X = 0.0f;
constexpr float DEFAULT_DRAG_OFFSET_Y = 0.0f;
} // namespace

class DragBarPatternTestTwoNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();

    void Create();

    RefPtr<FrameNode> frameNode_;
    RefPtr<DragBarPattern> pattern_;
    RefPtr<DragBarLayoutProperty> layoutProperty_;
    RefPtr<DragBarPaintProperty> paintProperty_;
};

void DragBarPatternTestTwoNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
}

void DragBarPatternTestTwoNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void DragBarPatternTestTwoNg::SetUp() {}

void DragBarPatternTestTwoNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    layoutProperty_ = nullptr;
    paintProperty_ = nullptr;
}

void DragBarPatternTestTwoNg::GetInstance()
{
    frameNode_ = FrameNode::GetOrCreateFrameNode(V2::DRAG_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<DragBarPattern>(); });
    ASSERT_NE(frameNode_, nullptr);
    pattern_ = frameNode_->GetPattern<DragBarPattern>();
    layoutProperty_ = frameNode_->GetLayoutProperty<DragBarLayoutProperty>();
    paintProperty_ = frameNode_->GetPaintProperty<DragBarPaintProperty>();
}

void DragBarPatternTestTwoNg::Create()
{
    GetInstance();
    FlushUITasks(frameNode_);
}

/**
 * @tc.name: DragBarPaintPropertyTest001
 * @tc.desc: Test drag bar pattern DragBarPaintProperty function with comprehensive property updates
 *           to verify basic property setting and retrieval functionality across multiple property types.
 * @tc.type: FUNC
 */
HWTEST_F(DragBarPatternTestTwoNg, DragBarPaintPropertyTest001, TestSize.Level1)
{
    // Initialize test environment and verify component creation
    Create();
    ASSERT_NE(paintProperty_, nullptr);

    /**
     * @tc.steps: Test Property-Update functionality for all supported paint properties.
     * @tc.expected: All properties update correctly and maintain their values.
     */

    /**
     * @tc.subtest: Test PanelMode property with different enum values
     * @tc.desc: Verify PanelMode property can be set and retrieved correctly
     */
    PanelMode panelMode = PanelMode::HALF;
    ACE_UPDATE_NODE_PAINT_PROPERTY(DragBarPaintProperty, PanelMode, panelMode, frameNode_);
    EXPECT_TRUE(paintProperty_->HasPanelMode());
    auto panelModeVal = paintProperty_->GetPanelModeValue();
    EXPECT_EQ(panelMode, panelModeVal);

    /**
     * @tc.subtest: Test BarLeftPoint property with Dimension coordinates
     * @tc.desc: Verify 2D point properties with Dimension type work correctly
     */
    OffsetT<Dimension> barLeftPoint(Dimension(TEST_DIMENSION_VAL, TEST_DIMENSION_UNIT),
                                   Dimension(TEST_DIMENSION_VAL * 2, TEST_DIMENSION_UNIT));
    ACE_UPDATE_NODE_PAINT_PROPERTY(DragBarPaintProperty, BarLeftPoint, barLeftPoint, frameNode_);
    EXPECT_TRUE(paintProperty_->HasBarLeftPoint());
    auto barLeftPointVal = paintProperty_->GetBarLeftPointValue();
    EXPECT_EQ(barLeftPoint.GetX(), barLeftPointVal.GetX());
    EXPECT_EQ(barLeftPoint.GetY(), barLeftPointVal.GetY());

    /**
     * @tc.subtest: Test BarCenterPoint property with scaled Dimension values
     * @tc.desc: Verify point properties with different scaling factors
     */
    OffsetT<Dimension> barCenterPoint(Dimension(TEST_DIMENSION_VAL * 3, TEST_DIMENSION_UNIT),
                                     Dimension(TEST_DIMENSION_VAL * 4, TEST_DIMENSION_UNIT));
    ACE_UPDATE_NODE_PAINT_PROPERTY(DragBarPaintProperty, BarCenterPoint, barCenterPoint, frameNode_);
    EXPECT_TRUE(paintProperty_->HasBarCenterPoint());
    auto barCenterPointVal = paintProperty_->GetBarCenterPointValue();
    EXPECT_EQ(barCenterPoint.GetX(), barCenterPointVal.GetX());
    EXPECT_EQ(barCenterPoint.GetY(), barCenterPointVal.GetY());

    /**
     * @tc.subtest: Test BarRightPoint property with further scaled values
     * @tc.desc: Verify point properties maintain precision with larger values
     */
    OffsetT<Dimension> barRightPoint(Dimension(TEST_DIMENSION_VAL * 5, TEST_DIMENSION_UNIT),
                                    Dimension(TEST_DIMENSION_VAL * 6, TEST_DIMENSION_UNIT));
    ACE_UPDATE_NODE_PAINT_PROPERTY(DragBarPaintProperty, BarRightPoint, barRightPoint, frameNode_);
    EXPECT_TRUE(paintProperty_->HasBarRightPoint());
    auto barRightPointVal = paintProperty_->GetBarRightPointValue();
    EXPECT_EQ(barRightPoint.GetX(), barRightPointVal.GetX());
    EXPECT_EQ(barRightPoint.GetY(), barRightPointVal.GetY());

    /**
     * @tc.subtest: Test DragOffset property with OffsetF type
     * @tc.desc: Verify floating point offset properties work correctly
     */
    OffsetF dragOffset(TEST_OFFSET_VAL, TEST_OFFSET_VAL * 2);
    ACE_UPDATE_NODE_PAINT_PROPERTY(DragBarPaintProperty, DragOffset, dragOffset, frameNode_);
    EXPECT_TRUE(paintProperty_->HasDragOffset());
    auto dragOffsetVal = paintProperty_->GetDragOffsetValue();
    EXPECT_EQ(dragOffset.GetX(), dragOffsetVal.GetX());
    EXPECT_EQ(dragOffset.GetY(), dragOffsetVal.GetY());

    /**
     * @tc.subtest: Test Opacity property with float type
     * @tc.desc: Verify alpha transparency property works within valid range
     */
    float opacity = TEST_OPACITY_1;
    ACE_UPDATE_NODE_PAINT_PROPERTY(DragBarPaintProperty, Opacity, opacity, frameNode_);
    EXPECT_TRUE(paintProperty_->HasOpacity());
    auto opacityVal = paintProperty_->GetOpacityValue();
    EXPECT_FLOAT_EQ(opacity, opacityVal);

    // Verify all properties remain set after multiple updates
    EXPECT_TRUE(paintProperty_->HasPanelMode());
    EXPECT_TRUE(paintProperty_->HasBarLeftPoint());
    EXPECT_TRUE(paintProperty_->HasBarCenterPoint());
    EXPECT_TRUE(paintProperty_->HasBarRightPoint());
    EXPECT_TRUE(paintProperty_->HasDragOffset());
    EXPECT_TRUE(paintProperty_->HasOpacity());
}

/**
 * @tc.name: DragBarPaintPropertyTest002
 * @tc.desc: Test drag bar pattern DragBarPaintProperty clone and reset functions
 *           with comprehensive verification of property copying and restoration.
 * @tc.type: FUNC
 */
HWTEST_F(DragBarPatternTestTwoNg, DragBarPaintPropertyTest002, TestSize.Level1)
{
    Create();
    ASSERT_NE(paintProperty_, nullptr);

    // Set up test properties with different data types
    PanelMode panelMode = PanelMode::MINI;
    ACE_UPDATE_NODE_PAINT_PROPERTY(DragBarPaintProperty, PanelMode, panelMode, frameNode_);

    OffsetF dragOffset(TEST_OFFSET_VAL, TEST_OFFSET_VAL);
    ACE_UPDATE_NODE_PAINT_PROPERTY(DragBarPaintProperty, DragOffset, dragOffset, frameNode_);

    float opacity = TEST_OPACITY_2;
    ACE_UPDATE_NODE_PAINT_PROPERTY(DragBarPaintProperty, Opacity, opacity, frameNode_);

    /**
     * @tc.steps: step1. Clone paint property to create an identical copy.
     * @tc.expected: Clone operation successful and returns valid object.
     */
    auto paintPropertyClone = AceType::DynamicCast<DragBarPaintProperty>(paintProperty_->Clone());
    ASSERT_NE(paintPropertyClone, nullptr);

    /**
     * @tc.steps: step2. Verify cloned properties match original in all aspects.
     * @tc.expected: All cloned properties exactly match original values.
     */
    // Verify PanelMode property cloning
    EXPECT_TRUE(paintPropertyClone->HasPanelMode());
    auto panelModeCloneVal = paintPropertyClone->GetPanelModeValue();
    EXPECT_EQ(panelMode, panelModeCloneVal);

    // Verify DragOffset property cloning with coordinate precision
    EXPECT_TRUE(paintPropertyClone->HasDragOffset());
    auto dragOffsetCloneVal = paintPropertyClone->GetDragOffsetValue();
    EXPECT_EQ(dragOffset.GetX(), dragOffsetCloneVal.GetX());
    EXPECT_EQ(dragOffset.GetY(), dragOffsetCloneVal.GetY());

    // Verify Opacity property cloning with floating point precision
    EXPECT_TRUE(paintPropertyClone->HasOpacity());
    auto opacityCloneVal = paintPropertyClone->GetOpacityValue();
    EXPECT_FLOAT_EQ(opacity, opacityCloneVal);

    /**
     * @tc.steps: step3. Reset cloned property to default state.
     * @tc.expected: All properties cleared, Has methods return false.
     */
    paintPropertyClone->Reset();

    // Verify all properties are cleared in clone
    EXPECT_FALSE(paintPropertyClone->HasPanelMode());
    EXPECT_FALSE(paintPropertyClone->HasDragOffset());
    EXPECT_FALSE(paintPropertyClone->HasOpacity());

    // Verify original properties remain unchanged
    EXPECT_TRUE(paintProperty_->HasPanelMode());
    EXPECT_TRUE(paintProperty_->HasDragOffset());
    EXPECT_TRUE(paintProperty_->HasOpacity());

    /**
     * @tc.steps: step4. Verify default values using default parameters.
     * @tc.expected: Default values returned and differ from test values.
     */
    PanelMode defaultPanelMode = DEFAULT_PANEL_MODE;
    OffsetF defaultDragOffset(DEFAULT_DRAG_OFFSET_X, DEFAULT_DRAG_OFFSET_Y);
    float defaultOpacity = DEFAULT_OPACITY;

    auto panelModeCloneValAfterReset = paintPropertyClone->GetPanelModeValue(defaultPanelMode);
    auto dragOffsetCloneValAfterReset = paintPropertyClone->GetDragOffsetValue(defaultDragOffset);
    auto opacityCloneValAfterReset = paintPropertyClone->GetOpacityValue(defaultOpacity);

    // Verify default values are returned for cleared properties
    EXPECT_EQ(panelModeCloneValAfterReset, defaultPanelMode);
    EXPECT_EQ(dragOffsetCloneValAfterReset, defaultDragOffset);
    EXPECT_FLOAT_EQ(opacityCloneValAfterReset, defaultOpacity);

    // Verify defaults are different from original test values
    EXPECT_NE(panelModeCloneValAfterReset, panelMode);
    EXPECT_NE(dragOffsetCloneValAfterReset.GetX(), dragOffset.GetX());
    EXPECT_NE(dragOffsetCloneValAfterReset.GetY(), dragOffset.GetY());
    EXPECT_NE(opacityCloneValAfterReset, opacity);
}


/**
 * @tc.name: DragBarPaintPropertyTest003
 * @tc.desc: Test drag bar pattern DragBarPaintProperty with different panel modes
 *           and associated positioning points for comprehensive mode-based behavior.
 * @tc.type: FUNC
 */
HWTEST_F(DragBarPatternTestTwoNg, DragBarPaintPropertyTest003, TestSize.Level1)
{
    Create();
    ASSERT_NE(paintProperty_, nullptr);

    /**
     * @tc.steps: step1. Test PanelMode::MINI with left-aligned positioning.
     * @tc.expected: Property set and retrieved correctly, left point set.
     */
    PanelMode miniMode = PanelMode::MINI;
    ACE_UPDATE_NODE_PAINT_PROPERTY(DragBarPaintProperty, PanelMode, miniMode, frameNode_);
    EXPECT_TRUE(paintProperty_->HasPanelMode());
    EXPECT_EQ(PanelMode::MINI, paintProperty_->GetPanelModeValue());

    // Set corresponding points for mini mode with left alignment
    OffsetT<Dimension> miniLeftPoint(
        Dimension(MINI_PANEL_LEFT_X, TEST_DIMENSION_UNIT),
        Dimension(MINI_PANEL_LEFT_Y, TEST_DIMENSION_UNIT));
    ACE_UPDATE_NODE_PAINT_PROPERTY(DragBarPaintProperty, BarLeftPoint, miniLeftPoint, frameNode_);

    /**
     * @tc.steps: step2. Test PanelMode::HALF with center positioning.
     * @tc.expected: Property updated correctly, center point set.
     */
    PanelMode halfMode = PanelMode::HALF;
    ACE_UPDATE_NODE_PAINT_PROPERTY(DragBarPaintProperty, PanelMode, halfMode, frameNode_);
    EXPECT_EQ(PanelMode::HALF, paintProperty_->GetPanelModeValue());

    // Update points for half mode with center alignment
    OffsetT<Dimension> halfCenterPoint(
        Dimension(HALF_PANEL_CENTER_X, TEST_DIMENSION_UNIT),
        Dimension(HALF_PANEL_CENTER_Y, TEST_DIMENSION_UNIT));
    ACE_UPDATE_NODE_PAINT_PROPERTY(DragBarPaintProperty, BarCenterPoint, halfCenterPoint, frameNode_);

    /**
     * @tc.steps: step3. Test PanelMode::FULL with right-aligned positioning.
     * @tc.expected: Property updated correctly, right point set.
     */
    PanelMode fullMode = PanelMode::FULL;
    ACE_UPDATE_NODE_PAINT_PROPERTY(DragBarPaintProperty, PanelMode, fullMode, frameNode_);
    EXPECT_EQ(PanelMode::FULL, paintProperty_->GetPanelModeValue());

    // Update points for full mode with right alignment
    OffsetT<Dimension> fullRightPoint(
        Dimension(FULL_PANEL_RIGHT_X, TEST_DIMENSION_UNIT),
        Dimension(FULL_PANEL_RIGHT_Y, TEST_DIMENSION_UNIT));
    ACE_UPDATE_NODE_PAINT_PROPERTY(DragBarPaintProperty, BarRightPoint, fullRightPoint, frameNode_);

    /**
     * @tc.steps: step4. Verify all properties are set and maintain values.
     * @tc.expected: All point properties correctly set with proper values.
     */
    EXPECT_TRUE(paintProperty_->HasBarLeftPoint());
    EXPECT_TRUE(paintProperty_->HasBarCenterPoint());
    EXPECT_TRUE(paintProperty_->HasBarRightPoint());

    auto leftPoint = paintProperty_->GetBarLeftPointValue();
    auto centerPoint = paintProperty_->GetBarCenterPointValue();
    auto rightPoint = paintProperty_->GetBarRightPointValue();

    // Verify left point coordinates for MINI mode
    EXPECT_EQ(Dimension(MINI_PANEL_LEFT_X, TEST_DIMENSION_UNIT), leftPoint.GetX());
    EXPECT_EQ(Dimension(MINI_PANEL_LEFT_Y, TEST_DIMENSION_UNIT), leftPoint.GetY());

    // Verify center point coordinates for HALF mode
    EXPECT_EQ(Dimension(HALF_PANEL_CENTER_X, TEST_DIMENSION_UNIT), centerPoint.GetX());
    EXPECT_EQ(Dimension(HALF_PANEL_CENTER_Y, TEST_DIMENSION_UNIT), centerPoint.GetY());

    // Verify right point coordinates for FULL mode
    EXPECT_EQ(Dimension(FULL_PANEL_RIGHT_X, TEST_DIMENSION_UNIT), rightPoint.GetX());
    EXPECT_EQ(Dimension(FULL_PANEL_RIGHT_Y, TEST_DIMENSION_UNIT), rightPoint.GetY());

    // Additional verification of coordinate relationships
    EXPECT_LT(leftPoint.GetX().Value(), centerPoint.GetX().Value());
    EXPECT_LT(centerPoint.GetX().Value(), rightPoint.GetX().Value());
    EXPECT_LT(leftPoint.GetY().Value(), rightPoint.GetY().Value());
}

/**
 * @tc.name: DragBarLayoutPropertyTest001
 * @tc.desc: Test drag bar pattern DragBarLayoutProperty basic function
 *           with comprehensive property interaction testing.
 * @tc.type: FUNC
 */
HWTEST_F(DragBarPatternTestTwoNg, DragBarLayoutPropertyTest001, TestSize.Level1)
{
    Create();
    ASSERT_NE(layoutProperty_, nullptr);
    ASSERT_NE(frameNode_, nullptr);

    /**
     * @tc.steps: step1. Test FullScreenMode property set to true.
     * @tc.expected: Property set and retrieved correctly with boolean type.
     */
    bool fullScreenMode = true;
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DragBarLayoutProperty, FullScreenMode, fullScreenMode, frameNode_);
    EXPECT_TRUE(layoutProperty_->HasFullScreenMode());
    auto fullScreenModeVal = layoutProperty_->GetFullScreenModeValue();
    EXPECT_EQ(fullScreenMode, fullScreenModeVal);

    /**
     * @tc.steps: step2. Test FullScreenMode property set to false.
     * @tc.expected: Property updated correctly, value changes appropriately.
     */
    bool nonFullScreenMode = false;
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DragBarLayoutProperty, FullScreenMode, nonFullScreenMode, frameNode_);
    EXPECT_EQ(nonFullScreenMode, layoutProperty_->GetFullScreenModeValue());

    /**
     * @tc.steps: step3. Test HotRegionHeight property with floating point value.
     * @tc.expected: Property set and retrieved correctly with float precision.
     */
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DragBarLayoutProperty, HotRegionHeight, HOT_REGION_HEIGHT_NORMAL, frameNode_);
    EXPECT_TRUE(layoutProperty_->HasHotRegionHeight());
    auto hotRegionHeightVal = layoutProperty_->GetHotRegionHeightValue();
    EXPECT_FLOAT_EQ(HOT_REGION_HEIGHT_NORMAL, hotRegionHeightVal);

    /**
     * @tc.steps: step4. Test property independence and co-existence.
     * @tc.expected: Changing one property does not affect the other.
     */
    EXPECT_TRUE(layoutProperty_->HasFullScreenMode());
    EXPECT_TRUE(layoutProperty_->HasHotRegionHeight());
    EXPECT_EQ(nonFullScreenMode, layoutProperty_->GetFullScreenModeValue());
    EXPECT_FLOAT_EQ(HOT_REGION_HEIGHT_NORMAL, layoutProperty_->GetHotRegionHeightValue());

    // Additional verification of property persistence
    EXPECT_NE(fullScreenMode, nonFullScreenMode);
    EXPECT_TRUE(layoutProperty_->GetFullScreenModeValue() == false);
    EXPECT_TRUE(layoutProperty_->GetHotRegionHeightValue() > 0.0f);
}

/**
 * @tc.name: DragBarLayoutPropertyTest002
 * @tc.desc: Test drag bar pattern DragBarLayoutProperty clone and reset functions
 *           with comprehensive state management verification.
 * @tc.type: FUNC
 */
HWTEST_F(DragBarPatternTestTwoNg, DragBarLayoutPropertyTest002, TestSize.Level1)
{
    Create();
    ASSERT_NE(layoutProperty_, nullptr);
    ASSERT_NE(frameNode_, nullptr);

    /**
     * @tc.steps: step1. Set layout properties with various data types.
     * @tc.expected: Properties set correctly and ready for cloning.
     */
    bool fullScreenMode = true;
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DragBarLayoutProperty, FullScreenMode, fullScreenMode, frameNode_);

    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DragBarLayoutProperty, HotRegionHeight, TEST_HOT_REGION_HEIGHT_MEDIUM, frameNode_);

    /**
     * @tc.steps: step2. Clone layout property to create identical instance.
     * @tc.expected: Clone successful with valid object creation.
     */
    auto layoutPropertyClone = AceType::DynamicCast<DragBarLayoutProperty>(layoutProperty_->Clone());
    ASSERT_NE(layoutPropertyClone, nullptr);

    /**
     * @tc.steps: step3. Verify cloned properties match original exactly.
     * @tc.expected: Cloned properties maintain all values and states.
     */
    EXPECT_EQ(layoutProperty_->HasFullScreenMode(), layoutPropertyClone->HasFullScreenMode());
    auto fullScreenModeVal = layoutProperty_->GetFullScreenModeValue();
    auto fullScreenModeCloneVal = layoutPropertyClone->GetFullScreenModeValue();
    EXPECT_EQ(fullScreenModeVal, fullScreenModeCloneVal);

    EXPECT_EQ(layoutProperty_->HasHotRegionHeight(), layoutPropertyClone->HasHotRegionHeight());
    auto hotRegionHeightVal = layoutProperty_->GetHotRegionHeightValue();
    auto hotRegionHeightCloneVal = layoutPropertyClone->GetHotRegionHeightValue();
    EXPECT_FLOAT_EQ(hotRegionHeightVal, hotRegionHeightCloneVal);

    /**
     * @tc.steps: step4. Reset cloned property to default state.
     * @tc.expected: Properties cleared, Has methods return false.
     */
    layoutPropertyClone->Reset();

    EXPECT_FALSE(layoutPropertyClone->HasFullScreenMode());
    EXPECT_TRUE(layoutProperty_->HasFullScreenMode());

    EXPECT_FALSE(layoutPropertyClone->HasHotRegionHeight());
    EXPECT_TRUE(layoutProperty_->HasHotRegionHeight());

    /**
     * @tc.steps: step5. Verify default values and state differences.
     * @tc.expected: Default values returned and differ from test values.
     */
    bool defaultFullScreenMode = DEFAULT_FULL_SCREEN_MODE;
    float defaultHotRegionHeight = DEFAULT_HOT_REGION_HEIGHT_VALUE;

    auto fullScreenModeCloneValAfterReset = layoutPropertyClone->GetFullScreenModeValue(defaultFullScreenMode);
    auto hotRegionHeightCloneValAfterReset = layoutPropertyClone->GetHotRegionHeightValue(defaultHotRegionHeight);

    // Verify default values are correctly returned
    EXPECT_EQ(fullScreenModeCloneValAfterReset, defaultFullScreenMode);
    EXPECT_FLOAT_EQ(hotRegionHeightCloneValAfterReset, defaultHotRegionHeight);

    // Verify reset values differ from original test values
    EXPECT_NE(fullScreenModeCloneValAfterReset, fullScreenModeVal);
    EXPECT_NE(hotRegionHeightCloneValAfterReset, hotRegionHeightVal);
}

/**
 * @tc.name: DragBarLayoutPropertyTest003
 * @tc.desc: Test drag bar pattern DragBarLayoutProperty with different hot region heights
 *           covering edge cases and typical usage scenarios.
 * @tc.type: FUNC
 */
HWTEST_F(DragBarPatternTestTwoNg, DragBarLayoutPropertyTest003, TestSize.Level1)
{
    Create();
    ASSERT_NE(layoutProperty_, nullptr);
    ASSERT_NE(frameNode_, nullptr);

    /**
     * @tc.steps: step1. Test minimum hot region height.
     * @tc.expected: Property set correctly with minimum valid value.
     */
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DragBarLayoutProperty, HotRegionHeight, MIN_HOT_REGION_HEIGHT, frameNode_);
    EXPECT_TRUE(layoutProperty_->HasHotRegionHeight());
    EXPECT_FLOAT_EQ(MIN_HOT_REGION_HEIGHT, layoutProperty_->GetHotRegionHeightValue());

    /**
     * @tc.steps: step2. Test default hot region height.
     * @tc.expected: Property updated correctly, value changes appropriately.
     */
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DragBarLayoutProperty, HotRegionHeight, DEFAULT_HOT_REGION_HEIGHT, frameNode_);
    EXPECT_FLOAT_EQ(DEFAULT_HOT_REGION_HEIGHT, layoutProperty_->GetHotRegionHeightValue());

    /**
     * @tc.steps: step3. Test large hot region height.
     * @tc.expected: Property updated correctly with larger value.
     */
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DragBarLayoutProperty, HotRegionHeight, LARGE_HOT_REGION_HEIGHT, frameNode_);
    EXPECT_FLOAT_EQ(LARGE_HOT_REGION_HEIGHT, layoutProperty_->GetHotRegionHeightValue());

    /**
     * @tc.steps: step4. Test edge case: zero height.
     * @tc.expected: Property accepts zero value for edge case handling.
     */
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DragBarLayoutProperty, HotRegionHeight, EDGE_CASE_HEIGHT, frameNode_);
    EXPECT_FLOAT_EQ(EDGE_CASE_HEIGHT, layoutProperty_->GetHotRegionHeightValue());

    /**
     * @tc.steps: step5. Verify property persistence and final state.
     * @tc.expected: Last set value is preserved correctly.
     */
    EXPECT_TRUE(layoutProperty_->HasHotRegionHeight());
    EXPECT_FLOAT_EQ(EDGE_CASE_HEIGHT, layoutProperty_->GetHotRegionHeightValue());

    // Additional verification of value progression
    EXPECT_GE(MIN_HOT_REGION_HEIGHT, EDGE_CASE_HEIGHT);
    EXPECT_LE(EDGE_CASE_HEIGHT, LARGE_HOT_REGION_HEIGHT);
    EXPECT_TRUE(layoutProperty_->GetHotRegionHeightValue() >= 0.0f);
}

/**
 * @tc.name: DragBarLayoutPropertyTest004
 * @tc.desc: Test drag bar pattern DragBarLayoutProperty interaction with full screen mode
 *           and hot region height combinations.
 * @tc.type: FUNC
 */
HWTEST_F(DragBarPatternTestTwoNg, DragBarLayoutPropertyTest004, TestSize.Level1)
{
    Create();
    ASSERT_NE(layoutProperty_, nullptr);
    ASSERT_NE(frameNode_, nullptr);

    /**
     * @tc.steps: step1. Test normal mode with standard hot region.
     * @tc.expected: Properties set independently in normal mode.
     */
    bool fullScreenModeFalse = false;
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DragBarLayoutProperty, FullScreenMode, fullScreenModeFalse, frameNode_);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DragBarLayoutProperty, HotRegionHeight, HOT_REGION_HEIGHT_NORMAL, frameNode_);

    EXPECT_EQ(fullScreenModeFalse, layoutProperty_->GetFullScreenModeValue());
    EXPECT_FLOAT_EQ(HOT_REGION_HEIGHT_NORMAL, layoutProperty_->GetHotRegionHeightValue());

    /**
     * @tc.steps: step2. Test full screen mode with larger hot region.
     * @tc.expected: Properties updated correctly in full screen mode.
     */
    bool fullScreenModeTrue = true;
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DragBarLayoutProperty, FullScreenMode, fullScreenModeTrue, frameNode_);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DragBarLayoutProperty, HotRegionHeight, HOT_REGION_HEIGHT_FULLSCREEN, frameNode_);

    EXPECT_EQ(fullScreenModeTrue, layoutProperty_->GetFullScreenModeValue());
    EXPECT_FLOAT_EQ(HOT_REGION_HEIGHT_FULLSCREEN, layoutProperty_->GetHotRegionHeightValue());

    /**
     * @tc.steps: step3. Test property update sequence and independence.
     * @tc.expected: Properties maintain correct values after multiple updates.
     */
    // Update only hot region height while maintaining full screen mode
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DragBarLayoutProperty, HotRegionHeight, UPDATED_HOT_REGION_HEIGHT, frameNode_);

    EXPECT_EQ(fullScreenModeTrue, layoutProperty_->GetFullScreenModeValue());
    EXPECT_FLOAT_EQ(UPDATED_HOT_REGION_HEIGHT, layoutProperty_->GetHotRegionHeightValue());

    // Update only full screen mode while maintaining hot region height
    bool updatedFullScreenMode = false;
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DragBarLayoutProperty, FullScreenMode, updatedFullScreenMode, frameNode_);

    EXPECT_EQ(updatedFullScreenMode, layoutProperty_->GetFullScreenModeValue());
    EXPECT_FLOAT_EQ(UPDATED_HOT_REGION_HEIGHT, layoutProperty_->GetHotRegionHeightValue());

    // Verify mode transitions don't affect other properties
    EXPECT_NE(fullScreenModeFalse, fullScreenModeTrue);
    EXPECT_NE(HOT_REGION_HEIGHT_NORMAL, HOT_REGION_HEIGHT_FULLSCREEN);
}

/**
 * @tc.name: DragBarLayoutPropertyTest005
 * @tc.desc: Test drag bar pattern DragBarLayoutProperty property change flags
 *           with comprehensive dirty flag management.
 * @tc.type: FUNC
 */
HWTEST_F(DragBarPatternTestTwoNg, DragBarLayoutPropertyTest005, TestSize.Level1)
{
    Create();
    ASSERT_NE(layoutProperty_, nullptr);
    ASSERT_NE(frameNode_, nullptr);

    /**
     * @tc.steps: step1. Check initial property change flag state.
     * @tc.expected: Initial flag is PROPERTY_UPDATE_NORMAL indicating clean state.
     */
    auto initialFlag = layoutProperty_->GetPropertyChangeFlag();
    EXPECT_EQ(PROPERTY_UPDATE_NORMAL, initialFlag);

    /**
     * @tc.steps: step2. Update FullScreenMode and verify flag changes.
     * @tc.expected: Flag includes PROPERTY_UPDATE_MEASURE indicating layout change.
     */
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DragBarLayoutProperty, FullScreenMode, true, frameNode_);
    auto flagAfterFullScreenUpdate = layoutProperty_->GetPropertyChangeFlag();
    EXPECT_TRUE(flagAfterFullScreenUpdate & PROPERTY_UPDATE_MEASURE);

    /**
     * @tc.steps: step3. Clean dirty flag and update HotRegionHeight.
     * @tc.expected: Flag reset and updated again for new change.
     */
    layoutProperty_->CleanDirty();
    auto flagAfterClean = layoutProperty_->GetPropertyChangeFlag();
    EXPECT_EQ(PROPERTY_UPDATE_NORMAL, flagAfterClean);

    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DragBarLayoutProperty, HotRegionHeight, TEST_HOT_REGION_HEIGHT_MEDIUM, frameNode_);
    auto flagAfterHotRegionUpdate = layoutProperty_->GetPropertyChangeFlag();
    EXPECT_TRUE(flagAfterHotRegionUpdate & PROPERTY_UPDATE_MEASURE);

    /**
     * @tc.steps: step4. Update with same value and verify no flag change.
     * @tc.expected: Flag should not change for identical value updates.
     */
    layoutProperty_->CleanDirty();
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DragBarLayoutProperty, HotRegionHeight, TEST_HOT_REGION_HEIGHT_MEDIUM, frameNode_);
    auto flagAfterSameValue = layoutProperty_->GetPropertyChangeFlag();
    EXPECT_EQ(PROPERTY_UPDATE_NORMAL, flagAfterSameValue);

    // Additional verification of flag behavior
    EXPECT_NE(initialFlag, flagAfterFullScreenUpdate);
    EXPECT_NE(flagAfterFullScreenUpdate, flagAfterClean);
    EXPECT_EQ(flagAfterClean, flagAfterSameValue);
}

/**
 * @tc.name: DragBarLayoutAlgorithmTest001
 * @tc.desc: Test drag bar pattern DragBarLayoutAlgorithm MeasureContent with normal mode
 *           and comprehensive constraint handling.
 * @tc.type: FUNC
 */
HWTEST_F(DragBarPatternTestTwoNg, DragBarLayoutAlgorithmTest001, TestSize.Level1)
{
    Create();
    ASSERT_NE(layoutProperty_, nullptr);
    ASSERT_NE(frameNode_, nullptr);

    /**
     * @tc.steps: step1. Create layout algorithm instance.
     * @tc.expected: Layout algorithm created successfully.
     */
    auto layoutAlgorithm = AceType::MakeRefPtr<DragBarLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);

    /**
     * @tc.steps: step2. Set normal mode layout properties.
     * @tc.expected: Properties set correctly for normal mode testing.
     */
    const bool fullScreenMode = false;
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DragBarLayoutProperty, FullScreenMode, fullScreenMode, frameNode_);

    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DragBarLayoutProperty, HotRegionHeight, TEST_HOT_REGION_HEIGHT_MEDIUM, frameNode_);

    /**
     * @tc.steps: step3. Create comprehensive layout constraint.
     * @tc.expected: Constraint set correctly with various size parameters.
     */
    LayoutConstraintF contentConstraint;

    contentConstraint.selfIdealSize.SetWidth(CONSTRAINT_WIDTH);
    contentConstraint.selfIdealSize.SetHeight(CONSTRAINT_HEIGHT);
    contentConstraint.maxSize = SizeF(MAX_WIDTH, MAX_HEIGHT);
    contentConstraint.minSize = SizeF(0.0f, 0.0f);

    /**
     * @tc.steps: step4. Call MeasureContent with constraints.
     * @tc.expected: Measure result computed correctly.
     */
    auto result = layoutAlgorithm->MeasureContent(contentConstraint, frameNode_.GetRawPtr());

    /**
     * @tc.steps: step5. Verify measurement results for normal mode.
     * @tc.expected: Size matches hot region dimensions, not constraint sizes.
     */
    ASSERT_TRUE(result.has_value());
    const float expectedHotRegionWidth = HOT_REGION_WIDTH.ConvertToPx();
    EXPECT_FLOAT_EQ(expectedHotRegionWidth, result->Width());
    EXPECT_FLOAT_EQ(TEST_HOT_REGION_HEIGHT_MEDIUM, result->Height());

    /**
     * @tc.steps: step6. Verify icon offset calculation and centering.
     * @tc.expected: Icon positioned correctly within hot region.
     */
    auto iconOffset = layoutAlgorithm->GetIconOffset();
    const float dragIconWidth = DRAG_ICON_WIDTH.ConvertToPx();
    const float dragIconHeight = DRAG_ICON_HEIGHT.ConvertToPx();
    const float expectedIconX = (result->Width() - dragIconWidth) / HALF_FLOAT;
    const float expectedIconY = (result->Height() - dragIconHeight) / HALF_FLOAT;

    EXPECT_NEAR(expectedIconX, iconOffset.GetX(), EPSILON);
    EXPECT_NEAR(expectedIconY, iconOffset.GetY(), EPSILON);
}

/**
 * @tc.name: DragBarLayoutAlgorithmTest002
 * @tc.desc: Test drag bar pattern DragBarLayoutAlgorithm MeasureContent with full screen mode
 *           and comprehensive screen size handling.
 * @tc.type: FUNC
 */
HWTEST_F(DragBarPatternTestTwoNg, DragBarLayoutAlgorithmTest002, TestSize.Level1)
{
    Create();
    ASSERT_NE(layoutProperty_, nullptr);
    ASSERT_NE(frameNode_, nullptr);

    /**
     * @tc.steps: step1. Create layout algorithm instance.
     * @tc.expected: Layout algorithm created successfully.
     */
    auto layoutAlgorithm = AceType::MakeRefPtr<DragBarLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);

    /**
     * @tc.steps: step2. Set full screen mode layout properties.
     * @tc.expected: Properties set correctly for full screen testing.
     */
    const bool fullScreenMode = true;
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DragBarLayoutProperty, FullScreenMode, fullScreenMode, frameNode_);

    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DragBarLayoutProperty, HotRegionHeight, TEST_HOT_REGION_HEIGHT_LARGE, frameNode_);

    /**
     * @tc.steps: step3. Create layout constraint for screen size simulation.
     * @tc.expected: Constraint set correctly with screen dimensions.
     */
    LayoutConstraintF contentConstraint;

    contentConstraint.maxSize = SizeF(SCREEN_WIDTH, SCREEN_HEIGHT);
    contentConstraint.minSize = SizeF(0.0f, 0.0f);

    /**
     * @tc.steps: step3.5. Set layout constraint to frame node.
     * @tc.expected: Layout constraint properly propagated for measurement.
     */
    layoutProperty_->UpdateLayoutConstraint(contentConstraint);

    /**
     * @tc.steps: step4. Call MeasureContent with screen constraints.
     * @tc.expected: Measure result computed for full screen mode.
     */
    auto result = layoutAlgorithm->MeasureContent(contentConstraint, frameNode_.GetRawPtr());

    /**
     * @tc.steps: step5. Verify measurement results for full screen mode.
     * @tc.expected: Width matches max width, height matches hot region height.
     */
    ASSERT_TRUE(result.has_value());
    EXPECT_FLOAT_EQ(SCREEN_WIDTH, result->Width());
    EXPECT_FLOAT_EQ(TEST_HOT_REGION_HEIGHT_LARGE, result->Height());

    /**
     * @tc.steps: step6. Verify icon offset in full screen mode.
     * @tc.expected: Icon centered horizontally within full width.
     */
    auto iconOffset = layoutAlgorithm->GetIconOffset();
    const float dragIconWidth = DRAG_ICON_WIDTH.ConvertToPx();
    const float dragIconHeight = DRAG_ICON_HEIGHT.ConvertToPx();
    const float expectedIconX = (result->Width() - dragIconWidth) / HALF_FLOAT;
    const float expectedIconY = (result->Height() - dragIconHeight) / HALF_FLOAT;

    EXPECT_NEAR(expectedIconX, iconOffset.GetX(), EPSILON);
    EXPECT_NEAR(expectedIconY, iconOffset.GetY(), EPSILON);

    // Additional verification of full screen characteristics
    EXPECT_GT(SCREEN_WIDTH, dragIconWidth);
    EXPECT_GT(TEST_HOT_REGION_HEIGHT_LARGE, dragIconHeight);
    EXPECT_LT(iconOffset.GetX(), SCREEN_WIDTH - dragIconWidth);
}

/**
 * @tc.name: DragBarLayoutAlgorithmTest003
 * @tc.desc: Test drag bar pattern DragBarLayoutAlgorithm MeasureContent with default hot region height
 *           and fallback behavior verification.
 * @tc.type: FUNC
 */
HWTEST_F(DragBarPatternTestTwoNg, DragBarLayoutAlgorithmTest003, TestSize.Level1)
{
    Create();
    ASSERT_NE(layoutProperty_, nullptr);
    ASSERT_NE(frameNode_, nullptr);

    /**
     * @tc.steps: step1. Create layout algorithm instance.
     * @tc.expected: Layout algorithm created successfully.
     */
    auto layoutAlgorithm = AceType::MakeRefPtr<DragBarLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);

    /**
     * @tc.steps: step2. Test default value behavior without explicit HotRegionHeight.
     * @tc.expected: Default value should be used when property not set.
     */
    const bool fullScreenMode = false;
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DragBarLayoutProperty, FullScreenMode, fullScreenMode, frameNode_);
    // Note: Don't set HotRegionHeight to test default behavior

    /**
     * @tc.steps: step3. Create layout constraint for measurement.
     * @tc.expected: Constraint set correctly for default value testing.
     */
    LayoutConstraintF contentConstraint;

    contentConstraint.maxSize = SizeF(MAX_WIDTH, MAX_HEIGHT);

    /**
     * @tc.steps: step4. Call MeasureContent to test default behavior.
     * @tc.expected: Default hot region height should be used.
     */
    auto result = layoutAlgorithm->MeasureContent(contentConstraint, frameNode_.GetRawPtr());

    /**
     * @tc.steps: step5. Verify default height is used correctly.
     * @tc.expected: Should use HOT_REGION_HEIGHT constant as default.
     */
    ASSERT_TRUE(result.has_value());
    const float expectedHotRegionWidth = HOT_REGION_WIDTH.ConvertToPx();
    const float expectedHotRegionHeight = HOT_REGION_HEIGHT.ConvertToPx();

    EXPECT_FLOAT_EQ(expectedHotRegionWidth, result->Width());
    EXPECT_FLOAT_EQ(expectedHotRegionHeight, result->Height());

    // Additional verification of default behavior
    EXPECT_FALSE(layoutProperty_->HasHotRegionHeight());
    EXPECT_GT(expectedHotRegionHeight, 0.0f);
    EXPECT_LT(expectedHotRegionWidth, MAX_WIDTH);
}

/**
 * @tc.name: DragBarLayoutAlgorithmTest004
 * @tc.desc: Test drag bar pattern DragBarLayoutAlgorithm padding update functionality
 *           with comprehensive padding value verification.
 * @tc.type: FUNC
 */
HWTEST_F(DragBarPatternTestTwoNg, DragBarLayoutAlgorithmTest004, TestSize.Level1)
{
    Create();
    ASSERT_NE(layoutProperty_, nullptr);
    ASSERT_NE(frameNode_, nullptr);

    auto layoutAlgorithm = AceType::MakeRefPtr<DragBarLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.maxSize = SizeF(MAX_WIDTH, MAX_HEIGHT);

    auto result = layoutAlgorithm->MeasureContent(contentConstraint, frameNode_.GetRawPtr());
    ASSERT_TRUE(result.has_value());

    const std::unique_ptr<NG::PaddingProperty>& paddingProperty = layoutProperty_->GetPaddingProperty();
    ASSERT_NE(paddingProperty, nullptr);

    // Verify all padding values are set and accessible
    EXPECT_TRUE(paddingProperty->left.has_value());
    EXPECT_TRUE(paddingProperty->top.has_value());
    EXPECT_TRUE(paddingProperty->right.has_value());
    EXPECT_TRUE(paddingProperty->bottom.has_value());

    // Verify left padding matches PADDING constant (16.0_vp)
    auto leftDim = paddingProperty->left.value().GetDimension();
    EXPECT_FLOAT_EQ(PADDING.Value(), leftDim.Value());
    EXPECT_EQ(PADDING.Unit(), leftDim.Unit());

    // Verify top padding is zero (0.0_px)
    auto topDim = paddingProperty->top.value().GetDimension();
    EXPECT_FLOAT_EQ(0.0f, topDim.Value());
    EXPECT_EQ(DimensionUnit::PX, topDim.Unit());

    // Verify right padding matches PADDING constant (16.0_vp)
    auto rightDim = paddingProperty->right.value().GetDimension();
    EXPECT_FLOAT_EQ(PADDING.Value(), rightDim.Value());
    EXPECT_EQ(PADDING.Unit(), rightDim.Unit());

    // Verify bottom padding is zero (0.0_px)
    auto bottomDim = paddingProperty->bottom.value().GetDimension();
    EXPECT_FLOAT_EQ(0.0f, bottomDim.Value());
    EXPECT_EQ(DimensionUnit::PX, bottomDim.Unit());

    // Additional verification of padding consistency
    EXPECT_EQ(leftDim.Value(), rightDim.Value());
    EXPECT_EQ(topDim.Value(), bottomDim.Value());
    EXPECT_NE(leftDim.Unit(), topDim.Unit());
}

/**
 * @tc.name: DragBarLayoutAlgorithmTest005
 * @tc.desc: Test drag bar pattern DragBarLayoutAlgorithm with various constraints
 *           including edge cases and different screen scenarios.
 * @tc.type: FUNC
 */
HWTEST_F(DragBarPatternTestTwoNg, DragBarLayoutAlgorithmTest005, TestSize.Level1)
{
    Create();
    ASSERT_NE(layoutProperty_, nullptr);
    ASSERT_NE(frameNode_, nullptr);
    /**
     * @tc.steps: step1. Create layout algorithm instance.
     * @tc.expected: Layout algorithm created successfully.
     */
    auto layoutAlgorithm = AceType::MakeRefPtr<DragBarLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    /**
     * @tc.steps: step2. Set layout properties for constraint testing.
     * @tc.expected: Properties set correctly for various constraint scenarios.
     */
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DragBarLayoutProperty, HotRegionHeight, TEST_HOT_REGION_HEIGHT_SMALL, frameNode_);
    const float expectedHotRegionWidth = HOT_REGION_WIDTH.ConvertToPx();

    /**
     * @tc.subtest: Test case 1 - Very small constraint scenario
     * @tc.desc: Verify behavior with minimal available space
     */
    {
        bool fullScreenMode = false;
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(DragBarLayoutProperty, FullScreenMode, fullScreenMode, frameNode_);

        LayoutConstraintF smallConstraint;

        smallConstraint.maxSize = SizeF(SMALL_MAX_WIDTH, SMALL_MAX_HEIGHT);
        smallConstraint.minSize = SizeF(SMALL_MIN_SIZE, SMALL_MIN_SIZE);

        // Set layout constraint for small space scenario
        layoutProperty_->UpdateLayoutConstraint(smallConstraint);

        auto result = layoutAlgorithm->MeasureContent(smallConstraint, frameNode_.GetRawPtr());
        ASSERT_TRUE(result.has_value());
        EXPECT_FLOAT_EQ(expectedHotRegionWidth, result->Width());
        EXPECT_FLOAT_EQ(TEST_HOT_REGION_HEIGHT_SMALL, result->Height());
    }
    /**
     * @tc.subtest: Test case 2 - Exact size constraint scenario
     * @tc.desc: Verify behavior with specific size requirements
     */
    {
        bool fullScreenMode = false;
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(DragBarLayoutProperty, FullScreenMode, fullScreenMode, frameNode_);

        LayoutConstraintF exactConstraint;

        exactConstraint.selfIdealSize.SetWidth(EXACT_WIDTH);
        exactConstraint.selfIdealSize.SetHeight(EXACT_HEIGHT);

        // Set layout constraint for exact size scenario
        layoutProperty_->UpdateLayoutConstraint(exactConstraint);

        auto result = layoutAlgorithm->MeasureContent(exactConstraint, frameNode_.GetRawPtr());
        ASSERT_TRUE(result.has_value());
        EXPECT_FLOAT_EQ(expectedHotRegionWidth, result->Width());
        EXPECT_FLOAT_EQ(TEST_HOT_REGION_HEIGHT_SMALL, result->Height());
    }
    /**
     * @tc.subtest: Test case 3 - Full screen mode with different widths
     * @tc.desc: Verify full screen behavior across different screen sizes
     */
    {
        bool fullScreenModeTrue = true;
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(DragBarLayoutProperty, FullScreenMode, fullScreenModeTrue, frameNode_);

        LayoutConstraintF fullScreenConstraint;

        fullScreenConstraint.maxSize = SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);

        // Set layout constraint for full screen scenario
        layoutProperty_->UpdateLayoutConstraint(fullScreenConstraint);

        auto result = layoutAlgorithm->MeasureContent(fullScreenConstraint, frameNode_.GetRawPtr());
        ASSERT_TRUE(result.has_value());
        EXPECT_FLOAT_EQ(FULL_SCREEN_WIDTH, result->Width());
        EXPECT_FLOAT_EQ(TEST_HOT_REGION_HEIGHT_SMALL, result->Height());
    }
    // Additional verification of constraint handling consistency
    EXPECT_GT(expectedHotRegionWidth, 0.0f);
    EXPECT_GT(TEST_HOT_REGION_HEIGHT_SMALL, 0.0f);
}

/**
 * @tc.name: DragBarLayoutAlgorithmTest006
 * @tc.desc: Test drag bar pattern DragBarLayoutAlgorithm padding values explicitly
 *           with comprehensive dimension and unit verification.
 * @tc.type: FUNC
 */
HWTEST_F(DragBarPatternTestTwoNg, DragBarLayoutAlgorithmTest006, TestSize.Level1)
{
    Create();
    ASSERT_NE(layoutProperty_, nullptr);
    ASSERT_NE(frameNode_, nullptr);

    auto layoutAlgorithm = AceType::MakeRefPtr<DragBarLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.maxSize = SizeF(TEST_WIDTH, TEST_HEIGHT);

    auto result = layoutAlgorithm->MeasureContent(contentConstraint, frameNode_.GetRawPtr());
    ASSERT_TRUE(result.has_value());

    const std::unique_ptr<NG::PaddingProperty>& paddingProperty = layoutProperty_->GetPaddingProperty();
    ASSERT_NE(paddingProperty, nullptr);

    ASSERT_TRUE(paddingProperty->left.has_value());
    ASSERT_TRUE(paddingProperty->top.has_value());
    ASSERT_TRUE(paddingProperty->right.has_value());
    ASSERT_TRUE(paddingProperty->bottom.has_value());

    // Verify left padding dimension and unit (should be 16.0_vp)
    auto leftDim = paddingProperty->left.value().GetDimension();
    EXPECT_FLOAT_EQ(PADDING.Value(), leftDim.Value());
    EXPECT_EQ(PADDING.Unit(), leftDim.Unit());

    // Verify top padding dimension and unit (should be 0.0_px)
    auto topDim = paddingProperty->top.value().GetDimension();
    EXPECT_FLOAT_EQ(0.0f, topDim.Value());
    EXPECT_EQ(DimensionUnit::PX, topDim.Unit());

    // Verify right padding dimension and unit (should be 16.0_vp)
    auto rightDim = paddingProperty->right.value().GetDimension();
    EXPECT_FLOAT_EQ(PADDING.Value(), rightDim.Value());
    EXPECT_EQ(PADDING.Unit(), rightDim.Unit());

    // Verify bottom padding dimension and unit (should be 0.0_px)
    auto bottomDim = paddingProperty->bottom.value().GetDimension();
    EXPECT_FLOAT_EQ(0.0f, bottomDim.Value());
    EXPECT_EQ(DimensionUnit::PX, bottomDim.Unit());

    // Verify string representation contains expected formatting
    std::string paddingStr = paddingProperty->ToString();
    EXPECT_FALSE(paddingStr.empty());
    EXPECT_NE(std::string::npos, paddingStr.find("16.00vp"));

    // Additional verification of padding value consistency
    EXPECT_NE(leftDim.Value(), topDim.Value());
    EXPECT_EQ(leftDim.Value(), rightDim.Value());
    EXPECT_EQ(topDim.Value(), bottomDim.Value());
}

/**
 * @tc.name: DragBarLayoutAlgorithmTest007
 * @tc.desc: Test drag bar pattern DragBarLayoutAlgorithm padding property type
 *           and value equality with comprehensive type checking.
 * @tc.type: FUNC
 */
HWTEST_F(DragBarPatternTestTwoNg, DragBarLayoutAlgorithmTest007, TestSize.Level1)
{
    Create();
    ASSERT_NE(layoutProperty_, nullptr);
    ASSERT_NE(frameNode_, nullptr);

    auto layoutAlgorithm = AceType::MakeRefPtr<DragBarLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.maxSize = SizeF(CONSTRAINT_WIDTH_LARGE, CONSTRAINT_HEIGHT_LARGE);

    auto result = layoutAlgorithm->MeasureContent(contentConstraint, frameNode_.GetRawPtr());
    ASSERT_TRUE(result.has_value());

    const std::unique_ptr<NG::PaddingProperty>& paddingPropertyRef = layoutProperty_->GetPaddingProperty();
    ASSERT_NE(paddingPropertyRef, nullptr);

    // Verify all padding properties have values
    ASSERT_TRUE(paddingPropertyRef->left.has_value());
    ASSERT_TRUE(paddingPropertyRef->top.has_value());
    ASSERT_TRUE(paddingPropertyRef->right.has_value());
    ASSERT_TRUE(paddingPropertyRef->bottom.has_value());

    // Get dimension values for comprehensive verification
    auto leftDim = paddingPropertyRef->left.value().GetDimension();
    auto topDim = paddingPropertyRef->top.value().GetDimension();
    auto rightDim = paddingPropertyRef->right.value().GetDimension();
    auto bottomDim = paddingPropertyRef->bottom.value().GetDimension();

    // Verify left padding values and units (should be 16.0_vp)
    EXPECT_FLOAT_EQ(PADDING.Value(), leftDim.Value());
    EXPECT_EQ(PADDING.Unit(), leftDim.Unit());

    // Verify top padding values and units (should be 0.0_px)
    EXPECT_FLOAT_EQ(0.0f, topDim.Value());
    EXPECT_EQ(DimensionUnit::PX, topDim.Unit());

    // Verify right padding values and units (should be 16.0_vp)
    EXPECT_FLOAT_EQ(PADDING.Value(), rightDim.Value());
    EXPECT_EQ(PADDING.Unit(), rightDim.Unit());

    // Verify bottom padding values and units (should be 0.0_px)
    EXPECT_FLOAT_EQ(0.0f, bottomDim.Value());
    EXPECT_EQ(DimensionUnit::PX, bottomDim.Unit());

    // Additional verification of dimension relationships and type consistency
    EXPECT_NE(leftDim.Unit(), topDim.Unit());
    EXPECT_EQ(leftDim.Unit(), rightDim.Unit());
    EXPECT_EQ(topDim.Unit(), bottomDim.Unit());
}
} // namespace OHOS::Ace::NG
