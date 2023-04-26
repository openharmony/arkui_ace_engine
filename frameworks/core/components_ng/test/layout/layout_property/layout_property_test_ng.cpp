/*
 * Copyright (c) 2023 iSoftStone Information Technology (Group) Co.,Ltd.
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
#include "gtest/gtest.h"

#define protected public
#define private public
#include "core/components_ng/layout/layout_property.h"
#include "base/geometry/ng/size_t.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components_ng/property/magic_layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/base/view_stack_processor.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::optional<float> ZERO {0.0};
const std::optional<int32_t> SPAN_ONE {-1};
const std::optional<int32_t> OFFSET_ONE {-5};
const std::optional<int32_t> SPAN_TWO {1};
const std::optional<int32_t> OFFSET_TWO {0};
const Dimension TESTLEFT {2.0, DimensionUnit::VP};
const Dimension TESTRIGHT {3.0, DimensionUnit::VP};
const Dimension WIDTH {1.0, DimensionUnit::VP};
const Dimension HEIGHT {2.0, DimensionUnit::VP};
const Dimension TOPONE {3.0, DimensionUnit::VP};
const Dimension BOTTOMONE {4.0, DimensionUnit::VP};
constexpr char TAG_ROOT[] = "root";
const std::string STRING_TEST =
    "{\"top\":\"3.00vp\",\"right\":\"2.00vp\",\"bottom\":\"4.00vp\",\"left\":\"1.00vp\"}";
const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);

std::optional<int> widthOpt {10};
std::optional<int> heightOpt {5};
float paddingHorizontalDefault = 1.0f;
float paddingVerticalDefault = 2.0f;
float borderHorizontalDefault = 3.0f;
float borderVerticalDefault = 4.0f;

void MakeProperty(LayoutProperty& layoutProperty)
{
    layoutProperty.calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    layoutProperty.positionProperty_ = std::make_unique<PositionProperty>();
    layoutProperty.magicItemProperty_ = std::make_unique<MagicItemProperty>();
    layoutProperty.flexItemProperty_ = std::make_unique<FlexItemProperty>();
    layoutProperty.borderWidth_ = std::make_unique<BorderWidthProperty>();
    layoutProperty.gridProperty_ = std::make_unique<GridProperty>();
    layoutProperty.padding_ = std::make_unique<PaddingProperty>();
    layoutProperty.margin_ = std::make_unique<MarginProperty>();
}
} // namespace

class LayoutPropertyTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineBase::SetUp();
    }
    static void TeardownTestSuite()
    {
        MockPipelineBase::TearDown();
    }
};

/**
 * @tc.name: LayoutPropertyTest001
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    LayoutProperty layoutProperty;

    /**
     * @tc.steps: step2. callback ToJsonValue.push padding_ is null.
     */
    auto json = JsonUtil::Create(true);
    layoutProperty.ToJsonValue(json);

    /**
     * @tc.expected: Return expected results..
     */
    EXPECT_EQ(json->GetString("padding"), "0.00vp");
    EXPECT_EQ(json->GetString("margin"), "0.00vp");
    EXPECT_EQ(json->GetString("visibility"), "Visibility.Visible");
    EXPECT_EQ(json->GetString("direction"), "Direction.Auto");
}

/**
 * @tc.name: LayoutPropertyTest002
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    LayoutProperty layoutProperty;

    /**
     * @tc.steps: step2. callback ToJsonValue.push padding_ is not null.
     * @tc.steps: step2. push layoutDirection_ is TextDirection::INHERIT.
     * @tc.steps: step2. push propVisibility_ is VisibleType::INVISIBLE.
     */
    auto json = JsonUtil::Create(true);
    PaddingPropertyT<CalcLength> paddingPropertyT;
    paddingPropertyT.left = {CalcLength(WIDTH)};
    paddingPropertyT.right = {CalcLength(HEIGHT)};
    paddingPropertyT.top = {CalcLength(TOPONE)};
    paddingPropertyT.bottom = {CalcLength(BOTTOMONE)};

    MakeProperty(layoutProperty);
    layoutProperty.padding_ = std::make_unique<PaddingProperty>(paddingPropertyT);
    layoutProperty.layoutDirection_ = TextDirection::LTR;
    layoutProperty.propVisibility_ = VisibleType::VISIBLE;
    layoutProperty.ToJsonValue(json);

    /**
     * @tc.expected: Return expected results..
     */
    EXPECT_EQ(json->GetString("padding"), STRING_TEST);
    EXPECT_EQ(json->GetString("visibility"), "Visibility.Visible");
    EXPECT_EQ(json->GetString("direction"), "Direction.Ltr");
}

/**
 * @tc.name: LayoutPropertyTest003
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    LayoutProperty layoutProperty;

    /**
     * @tc.steps: step2. callback ToJsonValue.push margin_ is not null.
     * @tc.steps: step2. push layoutDirection_ is TextDirection::INHERIT.
     * @tc.steps: step2. push propVisibility_ is VisibleType::INVISIBLE.
     */
    auto json = JsonUtil::Create(true);
    PaddingPropertyT<CalcLength> paddingPropertyT;
    paddingPropertyT.left = {CalcLength(WIDTH)};
    paddingPropertyT.right = {CalcLength(HEIGHT)};
    paddingPropertyT.top = {CalcLength(TOPONE)};
    paddingPropertyT.bottom = {CalcLength(BOTTOMONE)};

    MakeProperty(layoutProperty);
    layoutProperty.margin_ = std::make_unique<MarginProperty>(paddingPropertyT);
    layoutProperty.layoutDirection_ = TextDirection::INHERIT;
    layoutProperty.propVisibility_ = VisibleType::INVISIBLE;
    layoutProperty.ToJsonValue(json);

    /**
     * @tc.expected: Return expected results..
     */
    EXPECT_EQ(json->GetString("margin"), STRING_TEST);
    EXPECT_EQ(json->GetString("visibility"), "Visibility.Hidden");
    EXPECT_EQ(json->GetString("direction"), "Direction.Inherit");
}

/**
 * @tc.name: LayoutPropertyTest004
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    LayoutProperty layoutProperty;

    /**
     * @tc.steps: step2. callback ToJsonValue.push layoutDirection_ is TextDirection::AUTO.
     * @tc.steps: step2. push propVisibility_ is VisibleType::GONE.
     */
    auto json = JsonUtil::Create(true);
    MakeProperty(layoutProperty);

    layoutProperty.layoutDirection_ = TextDirection::AUTO;
    layoutProperty.propVisibility_ = VisibleType::GONE;
    layoutProperty.ToJsonValue(json);

    /**
     * @tc.expected: Return expected results..
     */
    EXPECT_EQ(json->GetString("visibility"), "Visibility.None");
    EXPECT_EQ(json->GetString("direction"), "Direction.Auto");
}

/**
 * @tc.name: LayoutPropertyTest005
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    LayoutProperty layoutProperty;

    /**
     * @tc.steps: step2. callback Reset.
     * @tc.expected: Return expected results..
     */
    MakeProperty(layoutProperty);
    layoutProperty.Reset();
    EXPECT_EQ(layoutProperty.propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);
}

/**
 * @tc.name: LayoutPropertyTest006
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    LayoutProperty layoutProperty;

    /**
     * @tc.steps: step2. callback Clone.
     * @tc.expected: Return expected results..
     */
    auto result = layoutProperty.Clone();
    EXPECT_NE(result, nullptr);
}

/**
 * @tc.name: LayoutPropertyTest007
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    LayoutProperty layoutProperty;

    /**
     * @tc.steps: step2. callback Clone.push calcLayoutConstraint_ is not null
     * @tc.expected: Return expected results..
     */
    MakeProperty(layoutProperty);
    auto result = layoutProperty.Clone();
    EXPECT_NE(result, nullptr);
}

/**
 * @tc.name: LayoutPropertyTest008
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    Property property;
    LayoutProperty layoutProperty;
    MeasureProperty constraint;

    /**
     * @tc.steps: step2. callback UpdateCalcLayoutProperty.push constraint is null.
     * @tc.expected: Return expected results..
     */
    layoutProperty.UpdateCalcLayoutProperty(std::move(constraint));
    EXPECT_EQ(property.propertyChangeFlag_, 0);
}

/**
 * @tc.name: LayoutPropertyTest009
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    LayoutProperty layoutProperty;
    MeasureProperty constraint;
    CalcSize calcSize {CalcLength(WIDTH), CalcLength(HEIGHT)};
    constraint.maxSize = calcSize;
    constraint.minSize = calcSize;
    constraint.selfIdealSize = calcSize;
    MakeProperty(layoutProperty);

    /**
     * @tc.steps: step2. callback UpdateCalcLayoutProperty.push constraint is not null.
     * @tc.expected: Return expected results..
     */
    layoutProperty.UpdateCalcLayoutProperty(std::move(constraint));
    EXPECT_EQ(layoutProperty.calcLayoutConstraint_->maxSize, calcSize);
    EXPECT_EQ(layoutProperty.propertyChangeFlag_, PROPERTY_UPDATE_MEASURE);
}

/**
 * @tc.name: LayoutPropertyTest010
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    Property property;
    LayoutProperty layoutProperty;
    LayoutConstraintF parentConstraint;

    /**
     * @tc.steps: step2. callback UpdateLayoutConstraint.push margin_ is null.
     * @tc.expected: Return expected results..
     */
    layoutProperty.UpdateLayoutConstraint(std::move(parentConstraint));
    EXPECT_EQ(property.propertyChangeFlag_, 0);
}

/**
 * @tc.name: LayoutPropertyTest011
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    Property property;
    LayoutProperty layoutProperty;
    LayoutConstraintF parentConstraint;

    /**
     * @tc.steps: step2. callback UpdateLayoutConstraint.push margin_ is not null.
     * @tc.expected: Return expected results..
     */
    MakeProperty(layoutProperty);
    layoutProperty.UpdateLayoutConstraint(std::move(parentConstraint));
    EXPECT_EQ(property.propertyChangeFlag_, 0);
}

/**
 * @tc.name: LayoutPropertyTest012
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    Property property;
    LayoutProperty layoutProperty;
    LayoutConstraintF parentConstraint;
    MeasureProperty constraint;

    /**
     * @tc.steps: step2. callback UpdateLayoutConstraint.push calcLayoutConstraint_ is not null.
     * @tc.expected: Return expected results..
     */
    CalcSize calcSize {CalcLength(WIDTH), CalcLength(HEIGHT)};
    constraint.maxSize = calcSize;
    constraint.minSize = calcSize;
    constraint.selfIdealSize = calcSize;
    MakeProperty(layoutProperty);
    layoutProperty.calcLayoutConstraint_ = std::make_unique<MeasureProperty>(constraint);
    layoutProperty.UpdateLayoutConstraint(std::move(parentConstraint));
    EXPECT_EQ(property.propertyChangeFlag_, 0);
    EXPECT_EQ(layoutProperty.measureType_, std::nullopt);
}

/**
 * @tc.name: LayoutPropertyTest013
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    LayoutProperty layoutProperty;
    MeasureProperty constraint;

    /**
     * @tc.steps: step2. callback CheckSelfIdealSize.push measureType_ is MeasureType::MATCH_PARENT.
     * @tc.expected: Return expected results..
     */
    CalcSize calcSize {CalcLength(WIDTH), CalcLength(HEIGHT)};
    constraint.maxSize = calcSize;
    constraint.minSize = calcSize;
    constraint.selfIdealSize = calcSize;
    layoutProperty.calcLayoutConstraint_ = std::make_unique<MeasureProperty>(constraint);
    layoutProperty.measureType_ = MeasureType::MATCH_PARENT;
    layoutProperty.CheckSelfIdealSize();
    EXPECT_EQ(layoutProperty.calcLayoutConstraint_->maxSize, calcSize);
}

/**
 * @tc.name: LayoutPropertyTest014
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    LayoutProperty layoutProperty;
    LayoutConstraintF layoutConstraintF;

    /**
     * @tc.steps: step2. callback CheckBorderAndPadding.push selfIdealSize is {1,-1}.
     */
    layoutConstraintF.minSize = {1, 1};
    layoutConstraintF.maxSize = {10, 10};
    layoutConstraintF.selfIdealSize = {1, -1};
    layoutConstraintF.percentReference = {5, 5};
    layoutConstraintF.parentIdealSize = {2, 2};
    layoutProperty.layoutConstraint_ = layoutConstraintF;
    layoutProperty.CheckBorderAndPadding();
    PaddingPropertyF result = layoutProperty.CreatePaddingAndBorder();

    /**
     * @tc.expected: Return expected results..
     */
    EXPECT_EQ(layoutProperty.layoutConstraint_->selfIdealSize.Width(), 1);
    EXPECT_EQ(layoutProperty.layoutConstraint_->selfIdealSize.Height(), 0);
    EXPECT_EQ(result.left, ZERO);
    EXPECT_EQ(result.right, ZERO);
    EXPECT_EQ(result.top, ZERO);
    EXPECT_EQ(result.bottom, ZERO);
}

/**
 * @tc.name: LayoutPropertyTest015
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    LayoutProperty layoutProperty;
    LayoutConstraintF layoutConstraintF;

    /**
     * @tc.steps: step2. callback CheckSelfIdealSize.push selfIdealSize is {1,-1}.
     */
    layoutConstraintF.minSize = {1, 1};
    layoutConstraintF.maxSize = {10, 10};
    layoutConstraintF.selfIdealSize = {-1, 1};
    layoutConstraintF.percentReference = {5, 5};
    layoutConstraintF.parentIdealSize = {2, 2};
    layoutProperty.layoutConstraint_ = layoutConstraintF;
    layoutProperty.CheckBorderAndPadding();

    /**
     * @tc.expected: Return expected results..
     */
    EXPECT_EQ(layoutProperty.layoutConstraint_->selfIdealSize.Width(), 0);
    EXPECT_EQ(layoutProperty.layoutConstraint_->selfIdealSize.Height(), 1);
}

/**
 * @tc.name: LayoutPropertyTest016
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    LayoutProperty layoutProperty;

    /**
     * @tc.steps: step2. callback CheckAspectRatio.push AspectRatio is 1.0.
     * @tc.expected: Return expected results..
     */
    MagicItemProperty magicItemProperty;
    magicItemProperty.UpdateAspectRatio(1.0);
    magicItemProperty.UpdateLayoutWeight(1.0);
    MakeProperty(layoutProperty);

    layoutProperty.magicItemProperty_ = std::make_unique<MagicItemProperty>(magicItemProperty);
    layoutProperty.CheckAspectRatio();

    /**
     * @tc.expected: Return expected results..
     */
    EXPECT_EQ(layoutProperty.layoutConstraint_->selfIdealSize.Width(), std::nullopt);
}

/**
 * @tc.name: LayoutPropertyTest017
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    LayoutProperty layoutProperty;
    LayoutConstraintF layoutConstraintF;

    /**
     * @tc.steps: step2. callback CheckAspectRatio.push layoutConstraint_ is not null.
     */
    layoutConstraintF.maxSize = {1, 2};
    layoutConstraintF.selfIdealSize.SetWidth(widthOpt);
    layoutProperty.layoutConstraint_ = layoutConstraintF;

    MagicItemProperty magicItemProperty;
    magicItemProperty.UpdateAspectRatio(1.0);
    magicItemProperty.UpdateLayoutWeight(1.0);
    MakeProperty(layoutProperty);

    layoutProperty.magicItemProperty_ = std::make_unique<MagicItemProperty>(magicItemProperty);
    layoutProperty.CheckAspectRatio();

    /**
     * @tc.expected: Return expected results..
     */
    EXPECT_EQ(layoutProperty.layoutConstraint_->selfIdealSize.Width(), 1);
    EXPECT_EQ(layoutProperty.layoutConstraint_->selfIdealSize.Height(), 1);
}

/**
 * @tc.name: LayoutPropertyTest018
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    LayoutProperty layoutProperty;
    LayoutConstraintF layoutConstraintF;

    /**
     * @tc.steps: step2. callback CheckAspectRatio.push layoutConstraint_ is not null.
     */
    layoutConstraintF.maxSize = {1, 2};
    layoutConstraintF.selfIdealSize.SetHeight(heightOpt);
    layoutProperty.layoutConstraint_ = layoutConstraintF;

    MagicItemProperty magicItemProperty;
    magicItemProperty.UpdateAspectRatio(1.0);
    magicItemProperty.UpdateLayoutWeight(1.0);
    MakeProperty(layoutProperty);
    layoutProperty.magicItemProperty_ = std::make_unique<MagicItemProperty>(magicItemProperty);
    layoutProperty.CheckAspectRatio();

    /**
     * @tc.expected: Return expected results..
     */
    EXPECT_EQ(layoutProperty.layoutConstraint_->selfIdealSize.Width(), 1);
    EXPECT_EQ(layoutProperty.layoutConstraint_->selfIdealSize.Height(), 1);
}

/**
 * @tc.name: LayoutPropertyTest019
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    LayoutProperty layoutProperty;

    /**
     * @tc.steps: step2. callback BuildGridProperty.push gridProperty_ is null.
     * @tc.expected: Return expected results..
     */
    layoutProperty.Reset();
    layoutProperty.BuildGridProperty(FRAME_NODE_ROOT);
    auto parent = FRAME_NODE_ROOT->GetAncestorNodeOfFrame();
    EXPECT_EQ(parent, nullptr);
}

/**
 * @tc.name: LayoutPropertyTest020
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    LayoutProperty layoutProperty;

    /**
     * @tc.steps: step2. callback BuildGridProperty.push gridProperty_ is not null.
     * @tc.expected: Return expected results..
     */
    MakeProperty(layoutProperty);
    auto MOCK_PATTERN_HOST = AceType::MakeRefPtr<Pattern>();
    RefPtr<FrameNode> frameNodeHost = FrameNode::CreateFrameNode("host", 1, MOCK_PATTERN_HOST, true);
    RefPtr<FrameNode> frameNodeTest = FrameNode::CreateFrameNode("test", 0, MOCK_PATTERN_HOST, true);
    frameNodeHost->SetParent(frameNodeTest);
    frameNodeHost->OnVisibleChange(true);

    layoutProperty.BuildGridProperty(frameNodeHost);
    auto parent = frameNodeHost->GetAncestorNodeOfFrame();
    ASSERT_NE(parent, nullptr);
    auto result = parent->GetTag();
    EXPECT_EQ(result, "test");
}

/**
 * @tc.name: LayoutPropertyTest021
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    LayoutProperty layoutProperty;
    LayoutConstraintF layoutConstraintF;

    /**
     * @tc.steps: step2. callback CheckAspectRatio.push AspectRatio is 0.5.
     */
    layoutConstraintF.selfIdealSize.SetWidth(widthOpt);
    layoutProperty.layoutConstraint_ = layoutConstraintF;

    MagicItemProperty magicItemProperty;
    magicItemProperty.UpdateAspectRatio(0.5);
    magicItemProperty.UpdateLayoutWeight(1.0);
    MakeProperty(layoutProperty);
    layoutProperty.magicItemProperty_ = std::make_unique<MagicItemProperty>(magicItemProperty);
    layoutProperty.CheckAspectRatio();

    /**
     * @tc.expected: Return expected results..
     */
    EXPECT_EQ(layoutProperty.layoutConstraint_->selfIdealSize.Width(), 10);
    EXPECT_EQ(layoutProperty.layoutConstraint_->selfIdealSize.Height(), 20);
}

/**
 * @tc.name: LayoutPropertyTest022
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    LayoutProperty layoutProperty;
    LayoutConstraintF layoutConstraintF;

    /**
     * @tc.steps: step2. callback CheckAspectRatio.push AspectRatio is 0.5.
     */
    layoutConstraintF.selfIdealSize.SetHeight(heightOpt);
    layoutProperty.layoutConstraint_ = layoutConstraintF;

    MagicItemProperty magicItemProperty;
    magicItemProperty.UpdateAspectRatio(0.5);
    magicItemProperty.UpdateLayoutWeight(1.0);
    MakeProperty(layoutProperty);

    layoutProperty.magicItemProperty_ = std::make_unique<MagicItemProperty>(magicItemProperty);
    layoutProperty.CheckAspectRatio();

    /**
     * @tc.expected: Return expected results..
     */
    EXPECT_EQ(layoutProperty.layoutConstraint_->selfIdealSize.Width(), 2.5);
    EXPECT_EQ(layoutProperty.layoutConstraint_->selfIdealSize.Height(), 5);
}

/**
 * @tc.name: LayoutPropertyTest023
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    LayoutProperty layoutProperty;

    /**
     * @tc.steps: step2. callback UpdateGridProperty.push gridProperty_ is not null.
     */
    MakeProperty(layoutProperty);
    layoutProperty.UpdateGridProperty(DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET, GridSizeType::UNDEFINED);

    /**
     * @tc.expected: Return expected results..
     */
    EXPECT_EQ(layoutProperty.layoutConstraint_->minSize.Width(), 0);
    EXPECT_EQ(layoutProperty.layoutConstraint_->minSize.Height(), 0);
    EXPECT_EQ(layoutProperty.propertyChangeFlag_, PROPERTY_UPDATE_MEASURE);
}

/**
 * @tc.name: LayoutPropertyTest024
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    LayoutProperty layoutProperty;
    std::optional<int32_t> span;
    std::optional<int32_t> offset;

    /**
     * @tc.steps: step2. callback UpdateGridProperty.push gridProperty_ is null.push span is null.
     * @tc.expected: Return expected results..
     */
    layoutProperty.UpdateGridProperty(span, offset, GridSizeType::UNDEFINED);
    EXPECT_EQ(layoutProperty.propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);

    /**
     * @tc.steps: step3. callback UpdateGridProperty.push gridProperty_ is null.push span is -1.
     * @tc.expected: Return expected results..
     */
    GridProperty testGridProperty;
    GridTypedProperty testGridTypedProperty0 {GridSizeType::XS, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    GridTypedProperty testGridTypedProperty1 {GridSizeType::SM, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    GridTypedProperty testGridTypedProperty2 {GridSizeType::MD, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    GridTypedProperty testGridTypedProperty3 {GridSizeType::LG, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    GridTypedProperty testGridTypedProperty4 {GridSizeType::XL, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    GridTypedProperty testGridTypedProperty5 {GridSizeType::UNDEFINED, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty0);
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty1);
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty2);
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty3);
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty4);
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty5);
    layoutProperty.UpdateGridProperty(SPAN_ONE, OFFSET_ONE, GridSizeType::XS);
    bool spanResult = layoutProperty.gridProperty_->UpdateSpan(SPAN_ONE.value(), GridSizeType::XS);
    EXPECT_FALSE(spanResult);
    EXPECT_EQ(layoutProperty.propertyChangeFlag_, PROPERTY_UPDATE_MEASURE);
}

/**
 * @tc.name: LayoutPropertyTest025
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    LayoutProperty layoutProperty;
    GridProperty testGridProperty;

    /**
     * @tc.steps: step3. callback UpdateGridProperty.push gridProperty_ is null.push span is 1.
     */
    GridTypedProperty testGridTypedProperty0 {GridSizeType::XS, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    GridTypedProperty testGridTypedProperty1 {GridSizeType::SM, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    GridTypedProperty testGridTypedProperty2 {GridSizeType::MD, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    GridTypedProperty testGridTypedProperty3 {GridSizeType::LG, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    GridTypedProperty testGridTypedProperty4 {GridSizeType::XL, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    GridTypedProperty testGridTypedProperty5 {GridSizeType::UNDEFINED, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty0);
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty1);
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty2);
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty3);
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty4);
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty5);
    layoutProperty.UpdateGridProperty(SPAN_TWO, OFFSET_TWO, GridSizeType::UNDEFINED);
    bool spanResult = layoutProperty.gridProperty_->UpdateSpan(SPAN_TWO.value(), GridSizeType::UNDEFINED);

    /**
     * @tc.expected: Return expected results..
     */
    EXPECT_TRUE(spanResult);
    EXPECT_EQ(layoutProperty.propertyChangeFlag_, PROPERTY_UPDATE_MEASURE);
}

/**
 * @tc.name: LayoutPropertyTest026
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    LayoutProperty layoutProperty;

    /**
     * @tc.steps: step2. callback UpdateGridOffset.push gridProperty_ is null.
     * @tc.expected: Return results.is false.
     */
    bool result = layoutProperty.UpdateGridOffset(FRAME_NODE_ROOT);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step3. callback UpdateGridOffset.push gridProperty_ is not null.
     * @tc.expected: Return expected results..
     */
    layoutProperty.gridProperty_ = std::make_unique<GridProperty>();
    layoutProperty.gridProperty_->gridInfo_ =
        GridSystemManager::GetInstance().GetInfoByType(GridColumnType::CAR_DIALOG);

    bool result1 = layoutProperty.UpdateGridOffset(FRAME_NODE_ROOT);
    EXPECT_EQ(layoutProperty.gridProperty_->GetOffset(), UNDEFINED_DIMENSION);
    EXPECT_FALSE(result1);
}

/**
 * @tc.name: LayoutPropertyTest027
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    LayoutProperty layoutProperty;
    layoutProperty.gridProperty_ = std::make_unique<GridProperty>();

    GridColumnInfo::Builder columnBuilder;
    layoutProperty.gridProperty_->gridInfo_ = columnBuilder.Build();
    GridContainerInfo::Builder builder;
    builder.SetColumns(1);
    builder.SetGutterWidth(WIDTH);
    builder.SetMarginLeft(TESTLEFT);
    builder.SetMarginRight(TESTRIGHT);
    builder.SetSizeType(GridSizeType::XL);
    builder.SetColumnType(GridColumnType::NONE);
    builder.SetGridTemplateType(GridTemplateType::NORMAL);

    layoutProperty.gridProperty_->gridInfo_->parent_ = builder.Build();
    layoutProperty.gridProperty_->gridInfo_->dimOffsets_ = {WIDTH};
    layoutProperty.gridProperty_->gridInfo_->hasColumnOffset_ = true;

    /**
     * @tc.steps: step2. callback UpdateGridOffset.push gridProperty_ is not null.
     * @tc.expected: Return results.is true.
     */
    bool result = layoutProperty.UpdateGridOffset(FRAME_NODE_ROOT);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: LayoutPropertyTest028
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    LayoutProperty layoutProperty;

    /**
     * @tc.steps: step2. callback CreatePaddingAndBorder.push layoutConstraint_ is null.
     * @tc.expected: Return result.left.is 0.
     */
    PaddingPropertyF result = layoutProperty.CreatePaddingAndBorder();
    EXPECT_EQ(result.left, ZERO);
    EXPECT_EQ(result.right, ZERO);
    EXPECT_EQ(result.top, ZERO);
    EXPECT_EQ(result.bottom, ZERO);
}

/**
 * @tc.name: LayoutPropertyTest029
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    LayoutProperty layoutProperty;

    /**
     * @tc.steps: step2. callback GetHost.
     * @tc.expected: Return results.is SetHost.
     */
    auto MOCK_PATTERN_HOST = AceType::MakeRefPtr<Pattern>();
    RefPtr<FrameNode> frameNodeHost = FrameNode::CreateFrameNode("host", 1, MOCK_PATTERN_HOST, true);
    layoutProperty.SetHost(frameNodeHost);

    RefPtr<FrameNode> result = layoutProperty.GetHost();
    EXPECT_EQ(result, frameNodeHost);
}

/**
 * @tc.name: LayoutPropertyTest030
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    LayoutProperty layoutProperty;

    /**
     * @tc.steps: step2. callback CreatePaddingAndBorderWithDefault.push layoutConstraint_is null.
     * @tc.expected: Return frameNodeHost.left.is paddingHorizontalDefault+borderHorizontalDefault.
     */
    PaddingPropertyF frameNodeHost = layoutProperty.CreatePaddingAndBorderWithDefault(paddingHorizontalDefault,
        paddingVerticalDefault, borderHorizontalDefault, borderVerticalDefault);
    EXPECT_EQ(frameNodeHost.left, paddingHorizontalDefault+borderHorizontalDefault);
    EXPECT_EQ(frameNodeHost.right, paddingHorizontalDefault+borderHorizontalDefault);
    EXPECT_EQ(frameNodeHost.top, paddingVerticalDefault+borderVerticalDefault);
    EXPECT_EQ(frameNodeHost.bottom, paddingVerticalDefault+borderVerticalDefault);
}

/**
 * @tc.name: LayoutPropertyTest031
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    LayoutProperty layoutProperty;
    LayoutConstraintF layoutConstraintF;

    layoutConstraintF.minSize = {1, 1};
    layoutConstraintF.minSize = {10, 10};
    layoutConstraintF.percentReference = {5, 5};
    layoutConstraintF.parentIdealSize = {1, 1};
    layoutConstraintF.selfIdealSize = {1, 1};
    layoutProperty.layoutConstraint_ = layoutConstraintF;

    /**
     * @tc.steps: step2. callback CreatePaddingAndBorderWithDefault.push layoutConstraint_is not null.
     * @tc.expected: Return frameNodeHost.left.is paddingHorizontalDefault+borderHorizontalDefault..
     */
    PaddingPropertyF frameNodeHost = layoutProperty.CreatePaddingAndBorderWithDefault(paddingHorizontalDefault,
        paddingVerticalDefault, borderHorizontalDefault, borderVerticalDefault);
    EXPECT_EQ(frameNodeHost.left, 4);
    EXPECT_EQ(frameNodeHost.right, 4);
    EXPECT_EQ(frameNodeHost.top, 6);
    EXPECT_EQ(frameNodeHost.bottom, 6);
}

/**
 * @tc.name: LayoutPropertyTest032
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    LayoutProperty layoutProperty;

    /**
     * @tc.steps: step2. callback CreatePaddingWithoutBorder.push layoutConstraint_is null.
     * @tc.expected: Return frameNodeHost.is nullopt.
     */
    PaddingPropertyF paddingOne = layoutProperty.CreatePaddingWithoutBorder();
    EXPECT_EQ(paddingOne.left, std::nullopt);

    /**
     * @tc.steps: step3. callback CreatePaddingAndBorderWithDefault.push layoutConstraint_is not null.
     */
    LayoutConstraintF layoutConstraintF;
    PaddingPropertyT<CalcLength> paddingPropertyT;
    paddingPropertyT.left = {CalcLength(WIDTH)};
    paddingPropertyT.right = {CalcLength(HEIGHT)};
    paddingPropertyT.top = {CalcLength(TOPONE)};
    paddingPropertyT.bottom = {CalcLength(BOTTOMONE)};

    layoutProperty.padding_ = std::make_unique<PaddingProperty>(paddingPropertyT);
    layoutProperty.margin_ = std::make_unique<MarginProperty>();
    layoutConstraintF.minSize = {1, 1};
    layoutConstraintF.minSize = {10, 10};
    layoutConstraintF.percentReference = {5, 5};
    layoutConstraintF.parentIdealSize = {1, 1};
    layoutConstraintF.selfIdealSize = {1, 1};
    layoutProperty.layoutConstraint_ = layoutConstraintF;
    PaddingPropertyF paddingTwo = layoutProperty.CreatePaddingWithoutBorder();

    /**
     * @tc.expected: Return frameNodeHost.left.is 1.0.
     */
    EXPECT_EQ(paddingTwo.left, 1.0);
    EXPECT_EQ(paddingTwo.right, 2.0);
    EXPECT_EQ(paddingTwo.top, 3.0);
    EXPECT_EQ(paddingTwo.bottom, 4.0);
}

/**
 * @tc.name: LayoutPropertyTest033
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    LayoutProperty layoutProperty;

    /**
     * @tc.steps: step2. callback CreateMargin.push layoutConstraint_ null.
     * @tc.expected: Return margin.is nullopt.
     */
    PaddingPropertyF margin = layoutProperty.CreateMargin();
    EXPECT_EQ(margin.left, std::nullopt);
}

/**
 * @tc.name: LayoutPropertyTest034
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest034, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    LayoutProperty layoutProperty;

    /**
     * @tc.steps: step2. callback OnVisibilityUpdate.push VisibleType::VISIBLE.
     * @tc.expected: Return host.is null.
     */
    layoutProperty.OnVisibilityUpdate(VisibleType::VISIBLE);
    auto host =layoutProperty.GetHost();
    EXPECT_EQ(host, nullptr);

    /**
     * @tc.steps: step3. callback OnVisibilityUpdate.push VisibleType::VISIBLE.
     * @tc.expected: Return parent.is null.
     */
    auto MOCK_PATTERN_HOST = AceType::MakeRefPtr<Pattern>();
    RefPtr<FrameNode> frameNodeHost = FrameNode::CreateFrameNode("host", 1, MOCK_PATTERN_HOST, true);
    layoutProperty.SetHost(frameNodeHost);

    layoutProperty.OnVisibilityUpdate(VisibleType::INVISIBLE);
    auto parent = layoutProperty.GetHost()->GetAncestorNodeOfFrame();
    EXPECT_EQ(parent, nullptr);
}

/**
 * @tc.name: LayoutPropertyTest035
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest035, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    LayoutProperty layoutProperty;

    auto MOCK_PATTERN_HOST = AceType::MakeRefPtr<Pattern>();
    RefPtr<FrameNode> frameNodeHost = FrameNode::CreateFrameNode("host", 1, MOCK_PATTERN_HOST, true);
    RefPtr<FrameNode> frameNodeTest = FrameNode::CreateFrameNode("test", 0, MOCK_PATTERN_HOST, true);

    frameNodeHost->SetParent(frameNodeTest);
    layoutProperty.SetHost(frameNodeHost);

    /**
     * @tc.steps: step2. callback OnVisibilityUpdate.push VisibleType::VISIBLE.
     * @tc.expected: Return parent.is not null.
     */
    layoutProperty.OnVisibilityUpdate(VisibleType::VISIBLE);
    auto host =layoutProperty.GetHost();
    ASSERT_NE(host, nullptr);
    auto parent = layoutProperty.GetHost()->GetAncestorNodeOfFrame();
    ASSERT_NE(parent, nullptr);
}

/**
 * @tc.name: LayoutPropertyTest036
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest036, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    LayoutProperty layoutProperty;

    /**
     * @tc.steps: step2. callback CreateChildConstraint.push layoutConstraint_is null.
     * @tc.expected: Return parent.is not null.
     */
    LayoutConstraintF oneConstraint = layoutProperty.CreateChildConstraint();
    EXPECT_EQ(oneConstraint.minSize.Width(), 0);

    /**
     * @tc.steps: step3. callback CreateChildConstraint.push layoutConstraint_ maxSize is {10, 10}.
     */
    LayoutConstraintF layoutConstraintF;
    layoutConstraintF.minSize = {1, 1};
    layoutConstraintF.maxSize = {10, 10};
    layoutConstraintF.percentReference = {5, 5};
    layoutConstraintF.parentIdealSize = {1, 1};

    layoutProperty.layoutConstraint_ = layoutConstraintF;
    layoutProperty.contentConstraint_ = layoutConstraintF;

    LayoutConstraintF twoConstraint = layoutProperty.CreateChildConstraint();

    /**
     * @tc.expected: Return twoConstraint.maxSize is {10, 10}.
     */
    EXPECT_EQ(twoConstraint.maxSize.Width(), 10);
    EXPECT_EQ(twoConstraint.maxSize.Height(), 10);
    EXPECT_EQ(twoConstraint.percentReference.Width(), 5);
    EXPECT_EQ(twoConstraint.percentReference.Height(), 5);
    EXPECT_EQ(twoConstraint.selfIdealSize.Width(), std::nullopt);
}

/**
 * @tc.name: LayoutPropertyTest037
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest037, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    LayoutProperty layoutProperty;
    LayoutConstraintF layoutConstraintF;

    /**
     * @tc.steps: step2. callback CreateChildConstraint.push layoutConstraint_ selfIdealSize is {1, 1}.
     */
    layoutConstraintF.minSize = {1, 1};
    layoutConstraintF.maxSize = {10, 10};
    layoutConstraintF.percentReference = {5, 5};
    layoutConstraintF.parentIdealSize = {1, 1};
    layoutConstraintF.selfIdealSize = {1, 1};

    layoutProperty.layoutConstraint_ = layoutConstraintF;
    layoutProperty.contentConstraint_ = layoutConstraintF;
    LayoutConstraintF twoConstraint = layoutProperty.CreateChildConstraint();

    /**
     * @tc.expected: Return twoConstraint.maxSize is {1, 1}.
     */
    EXPECT_EQ(twoConstraint.maxSize.Width(), 1);
    EXPECT_EQ(twoConstraint.maxSize.Height(), 1);
    EXPECT_EQ(twoConstraint.percentReference.Width(), 1);
    EXPECT_EQ(twoConstraint.percentReference.Height(), 1);
    EXPECT_EQ(twoConstraint.selfIdealSize.Width(), std::nullopt);
}

/**
 * @tc.name: LayoutPropertyTest038
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest038, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    LayoutProperty layoutProperty;
    LayoutConstraintF layoutConstraintF;

    /**
     * @tc.steps: step2. callback CreateChildConstraint.push layoutConstraint_is null.
     * @tc.expected: Return layoutConstraint_.minSize.is {0, 0}.
     */
    layoutProperty.UpdateContentConstraint();
    EXPECT_EQ(layoutProperty.layoutConstraint_->minSize.Width(), 0);
    EXPECT_EQ(layoutProperty.layoutConstraint_->minSize.Height(), 0);

    /**
     * @tc.steps: step3. callback UpdateContentConstraint.push layoutConstraint_ parentIdealSize is null.
     * @tc.expected: Return contentConstraint_.contentConstraint_ is {5, 5}.
     */
    layoutConstraintF.minSize = {1, 1};
    layoutConstraintF.maxSize = {10, 10};
    layoutConstraintF.selfIdealSize = {1, 1};
    layoutConstraintF.percentReference = {5, 5};

    layoutProperty.layoutConstraint_ = layoutConstraintF;

    layoutProperty.UpdateContentConstraint();
    EXPECT_EQ(layoutProperty.contentConstraint_->percentReference.Width(), 5);
    EXPECT_EQ(layoutProperty.contentConstraint_->percentReference.Height(), 5);
}

/**
 * @tc.name: LayoutPropertyTest039
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest039, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    LayoutProperty layoutProperty;
    LayoutConstraintF layoutConstraintF;

    /**
     * @tc.steps: step2. callback UpdateContentConstraint.push layoutConstraint_ parentIdealSize is {2, 2}.
     */
    layoutConstraintF.minSize = {1, 1};
    layoutConstraintF.maxSize = {10, 10};
    layoutConstraintF.selfIdealSize = {1, 1};
    layoutConstraintF.percentReference = {5, 5};
    layoutConstraintF.parentIdealSize = {2, 2};

    layoutProperty.layoutConstraint_ = layoutConstraintF;
    MakeProperty(layoutProperty);
    layoutProperty.UpdateContentConstraint();

    /**
     * @tc.expected: Return contentConstraint_.percentReference is {2, 2}.
     */
    EXPECT_EQ(layoutProperty.contentConstraint_->percentReference.Width(), 2);
    EXPECT_EQ(layoutProperty.contentConstraint_->percentReference.Height(), 2);
}

/**
 * @tc.name: LayoutPropertyTest040
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest040, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    LayoutProperty layoutProperty;
    LayoutConstraintF layoutConstraintF;

    /**
     * @tc.steps: step2. callback CheckSelfIdealSize.push selfIdealSize is {1, 0}.
     */
    layoutConstraintF.minSize = {1, 1};
    layoutConstraintF.maxSize = {10, 10};
    layoutConstraintF.selfIdealSize = {1, 0};
    layoutConstraintF.percentReference = {5, 5};
    layoutConstraintF.parentIdealSize = {2, 2};
    layoutProperty.layoutConstraint_ = layoutConstraintF;
    layoutProperty.CheckBorderAndPadding();

    /**
     * @tc.expected: Return expected results..
     */
    EXPECT_EQ(layoutProperty.layoutConstraint_->selfIdealSize.Width(), 1);
    EXPECT_EQ(layoutProperty.layoutConstraint_->selfIdealSize.Height(), 0);
}

/**
 * @tc.name: LayoutPropertyTest041
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, LayoutPropertyTest041, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object layoutProperty.
     */
    LayoutProperty layoutProperty;

    auto MOCK_PATTERN_HOST = AceType::MakeRefPtr<Pattern>();
    RefPtr<FrameNode> frameNodeHost = FrameNode::CreateFrameNode("host", 1, MOCK_PATTERN_HOST, true);
    RefPtr<FrameNode> frameNodeTest = FrameNode::CreateFrameNode("test", 0, MOCK_PATTERN_HOST, true);

    /**
     * @tc.steps: step2. callback OnVisibilityUpdate.push VisibleType::GONE.
     * @tc.expected: Return parent.is not null.
     */
    frameNodeHost->SetParent(frameNodeTest);
    layoutProperty.SetHost(frameNodeHost);

    layoutProperty.OnVisibilityUpdate(VisibleType::GONE);
    auto host =layoutProperty.GetHost();
    ASSERT_NE(host, nullptr);
    auto parent = layoutProperty.GetHost()->GetAncestorNodeOfFrame();
    ASSERT_NE(parent, nullptr);
}
}
