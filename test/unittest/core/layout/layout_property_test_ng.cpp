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
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/safe_area_insets.h"
#include "core/components_ng/property/grid_property.h"
#include "core/pipeline/base/element_register.h"


#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
const std::optional<float> ZERO { 0.0 };
const std::optional<int32_t> SPAN_ONE { -1 };
const std::optional<int32_t> OFFSET_ONE { -1 };
const std::optional<int> WIDTH_OPT { 10 };
const std::optional<int> HEIGHT_OPT { 5 };
const std::optional<int32_t> SPAN;
const std::optional<int32_t> OFFSET;

constexpr Dimension WIDTH = 1.0_vp;
constexpr Dimension HEIGHT = 2.0_vp;
constexpr Dimension TOPONE = 3.0_vp;
constexpr Dimension BOTTOMONE = 4.0_vp;

const std::string VALUE_TEST = "test";
const std::string STRING_TEST = "{\"top\":\"3.00vp\",\"right\":\"2.00vp\",\"bottom\":\"4.00vp\",\"left\":\"1.00vp\"}";

const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode("root", 1, AceType::MakeRefPtr<Pattern>(), true);
const auto FRAME_NODE_TEST = FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<Pattern>(), true);

const CalcSize CALC_SIZE = { CalcLength(WIDTH), CalcLength(HEIGHT) };

LayoutConstraintF layoutConstraintF = {
    .minSize = { 1, 1 },
    .maxSize = { 10, 10 },
    .percentReference = { 5, 5 },
    .parentIdealSize = { 2, 2 },
};

SafeAreaExpandOpts expandOpts = {
    .edges = SAFE_AREA_TYPE_SYSTEM,
    .type = SAFE_AREA_EDGE_TOP,
};

SafeAreaInsets::Inset inset = {
    .start = 0,
    .end = 1,
};

SafeAreaInsets safeAreaInset(inset, inset, inset, inset);

void MakeProperty(RefPtr<LayoutProperty> layoutProperty)
{
    layoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    layoutProperty->positionProperty_ = std::make_unique<PositionProperty>();
    layoutProperty->flexItemProperty_ = std::make_unique<FlexItemProperty>();
    layoutProperty->borderWidth_ = std::make_unique<BorderWidthProperty>();
    layoutProperty->gridProperty_ = std::make_unique<GridProperty>();
    layoutProperty->padding_ = std::make_unique<PaddingProperty>();
    layoutProperty->margin_ = std::make_unique<MarginProperty>();
    layoutProperty->safeAreaInsets_ = std::make_unique<SafeAreaInsets>();
    layoutProperty->safeAreaExpandOpts_ = std::make_unique<SafeAreaExpandOpts>();
}

PaddingPropertyT<CalcLength> MakePadding()
{
    PaddingPropertyT<CalcLength> paddingProperty;
    paddingProperty.left = { CalcLength(WIDTH) };
    paddingProperty.right = { CalcLength(HEIGHT) };
    paddingProperty.top = { CalcLength(TOPONE) };
    paddingProperty.bottom = { CalcLength(BOTTOMONE) };

    return paddingProperty;
}
} // namespace

class LayoutPropertyTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
    }
    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
    }
};

/**
 * @tc.name: ToJsonValue001
 * @tc.desc: Test cast to LayoutPropertyTestNg
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, ToJsonValue001, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty and json.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto json = JsonUtil::Create(true);

    /**
     * @tc.steps2 push the padding_ and margin_ is null.
     * @tc.steps2 push the layoutDirection_ and propVisibility_ index is -1.
     */
    auto direction = static_cast<TextDirection>(-1);
    auto visibility = static_cast<VisibleType>(-1);
    layoutProperty->layoutDirection_ = direction;
    layoutProperty->propVisibility_ = visibility;

    /**
     * @tc.steps3: call ToJsonValue with json.
     * @tc.expected: Return expected results..
     */
    layoutProperty->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("padding"), "0.00vp");
    EXPECT_EQ(json->GetString("margin"), "0.00vp");
    EXPECT_EQ(json->GetString("visibility"), "Visibility.Visible");
    EXPECT_EQ(json->GetString("direction"), "Direction.Ltr");

    /**
     * @tc.steps4: call Reset.
     * @tc.expected: Return expected results..
     */
    layoutProperty->Reset();
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);

    /**
     * @tc.steps5: call Clone, push calcLayoutConstraint_ is null.
     * @tc.expected: Return expected results.
     */
    auto result = layoutProperty->Clone();
    EXPECT_NE(result, nullptr);
}

/**
 * @tc.name: ToJsonValue002
 * @tc.desc: Test cast to LayoutPropertyTestNg
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, ToJsonValue002, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty and json.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto json = JsonUtil::Create(true);

    /**
     * @tc.steps2: push padding_ and margin_ is not null.
     * @tc.steps2: push layoutDirection_ is TextDirection::AUTO.
     * @tc.steps2: push propVisibility_ is VisibleType::GONE.
     */

    auto paddingProperty = MakePadding();
    MakeProperty(layoutProperty);
    layoutProperty->padding_ = std::make_unique<PaddingProperty>(paddingProperty);
    layoutProperty->margin_ = std::make_unique<MarginProperty>(paddingProperty);
    layoutProperty->layoutDirection_ = TextDirection::RTL;
    layoutProperty->propVisibility_ = VisibleType::INVISIBLE;

    /**
     * @tc.steps3: call ToJsonValue with json.
     * @tc.expected: Return expected results.
     */
    layoutProperty->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("padding"), STRING_TEST);
    EXPECT_EQ(json->GetString("margin"), STRING_TEST);
    EXPECT_EQ(json->GetString("direction"), "Direction.Rtl");
    EXPECT_EQ(json->GetString("visibility"), "Visibility.Hidden");

    /**
     * @tc.steps4: call Clone, push calcLayoutConstraint_ is not null.
     * @tc.expected: Return expected results.
     */
    layoutProperty->FromJson(json);
    auto result = layoutProperty->Clone();
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, 3);
}

/**
 * @tc.name: UpdateCalcLayoutProperty001
 * @tc.desc: Test cast to LayoutPropertyTestNg
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateCalcLayoutProperty001, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty and constraint.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    MeasureProperty constraint;

    /**
     * @tc.steps: step2. call UpdateCalcLayoutProperty, push constraint is null.
     * @tc.expected: Return expected results..
     */
    layoutProperty->UpdateCalcLayoutProperty(std::move(constraint));
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, 1);

    /**
     * @tc.steps3: call ToJsonValue with json.
     * @tc.expected: Return expected results..
     */
    auto json = JsonUtil::Create(true);
    layoutProperty->FromJson(json);
    EXPECT_EQ(json->GetString("padding"), "");
    EXPECT_EQ(json->GetString("margin"), "");
}

/**
 * @tc.name: UpdateLayoutConstraint001
 * @tc.desc: Test cast to LayoutPropertyTestNg
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateLayoutConstraint001, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty and constraint.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    MeasureProperty constraint;

    /**
     * @tc.steps2: call UpdateLayoutConstraint, push margin_ is null.
     * @tc.expected: expected layoutProperty->propertyChangeFlag_ is 0.
     */
    layoutProperty->UpdateLayoutConstraint(std::move(layoutConstraintF));
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, 0);

    /**
     * @tc.steps3: push margin_ and calcLayoutConstraint_ is default value.
     * @tc.steps3: call UpdateLayoutConstraint.
     * @tc.expected: expected layoutProperty->measureType_ is nullopt.
     */
    MakeProperty(layoutProperty);
    layoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>(constraint);
    layoutProperty->UpdateLayoutConstraint(std::move(layoutConstraintF));
    EXPECT_EQ(layoutProperty->measureType_, std::nullopt);

    /**
     * @tc.steps4: push calcLayoutConstraint_ maxSize minSize and selfIdealSize is has_value.
     * @tc.steps4: call UpdateLayoutConstraint.
     * @tc.expected: Return expected results.
     */
    constraint.maxSize = CALC_SIZE;
    constraint.minSize = CALC_SIZE;
    constraint.selfIdealSize = CALC_SIZE;
    layoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>(constraint);
    layoutProperty->magicItemProperty_.UpdateAspectRatio(1.0);
    layoutProperty->measureType_ = MeasureType::MATCH_PARENT;
    layoutProperty->UpdateLayoutConstraint(std::move(layoutConstraintF));
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->maxSize.value(), CALC_SIZE);
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->minSize.value(), CALC_SIZE);
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->selfIdealSize.value(), CALC_SIZE);
}

/**
 * @tc.name: CheckBorderAndPadding001
 * @tc.desc: Test cast to LayoutPropertyTestNg
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, CheckBorderAndPadding001, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2: call CheckBorderAndPadding.push selfIdealSize is {1,-1}.
     * @tc.expected: Return expected results..
     */
    layoutConstraintF.selfIdealSize = { 1, -1 };
    layoutProperty->layoutConstraint_ = layoutConstraintF;
    layoutProperty->CheckBorderAndPadding();
    EXPECT_EQ(layoutProperty->layoutConstraint_->selfIdealSize.Width(), 1);
    EXPECT_EQ(layoutProperty->layoutConstraint_->selfIdealSize.Height(), 0);

    /**
     * @tc.steps3: call CheckBorderAndPadding.push selfIdealSize is {-1,1}.
     * @tc.expected: Return expected results..
     */
    layoutConstraintF.selfIdealSize = { -1, 1 };
    layoutProperty->layoutConstraint_ = layoutConstraintF;
    layoutProperty->CheckBorderAndPadding();
    EXPECT_EQ(layoutProperty->layoutConstraint_->selfIdealSize.Width(), 0);
    EXPECT_EQ(layoutProperty->layoutConstraint_->selfIdealSize.Height(), 1);

    /**
     * @tc.steps4: call CreatePaddingAndBorder.
     * @tc.expected: Return expected results..
     */
    PaddingPropertyF paddingPropertyF = layoutProperty->CreatePaddingAndBorder();
    EXPECT_EQ(paddingPropertyF.left, ZERO);
    EXPECT_EQ(paddingPropertyF.right, ZERO);
    EXPECT_EQ(paddingPropertyF.top, ZERO);
    EXPECT_EQ(paddingPropertyF.bottom, ZERO);
}

/**
 * @tc.name: CheckAspectRatio001
 * @tc.desc: Test cast to LayoutPropertyTestNg
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, CheckAspectRatio001, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2: call CheckAspectRatio.push layoutConstraint_ is null.
     * @tc.steps2: push AspectRatio is 1.0
     * @tc.expected: Return expected results.
     */
    layoutProperty->magicItemProperty_.UpdateAspectRatio(1.0);
    layoutProperty->CheckAspectRatio();
    EXPECT_EQ(layoutProperty->layoutConstraint_, std::nullopt);

    /**
     * @tc.steps3: callback CheckAspectRatio.push layoutConstraint_ is not null.
     * @tc.steps3: push selfIdealSize Width hasvalue.
     * @tc.expected: Return expected results.
     */
    layoutConstraintF.maxSize = { 2, 4 };
    layoutConstraintF.selfIdealSize.SetWidth(WIDTH_OPT);
    layoutProperty->layoutConstraint_ = layoutConstraintF;
    layoutProperty->CheckAspectRatio();
    EXPECT_TRUE(layoutProperty->layoutConstraint_.has_value());
    EXPECT_TRUE(layoutProperty->layoutConstraint_->selfIdealSize.Width().has_value());
    EXPECT_TRUE(layoutProperty->layoutConstraint_->selfIdealSize.Height().has_value());
    EXPECT_EQ(layoutProperty->layoutConstraint_->selfIdealSize.Width(), 2);
    EXPECT_EQ(layoutProperty->layoutConstraint_->selfIdealSize.Height(), 2);
}

/**
 * @tc.name: CheckAspectRatio002
 * @tc.desc: Test cast to LayoutPropertyTestNg
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, CheckAspectRatio002, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    LayoutConstraintF constraintF;

    /**
     * @tc.steps2: call CheckAspectRatio, push AspectRatio is 0.5.
     * @tc.steps2: push selfIdealSize Height hasvalue.
     * @tc.expected: Return expected results.
     */
    constraintF.selfIdealSize.SetHeight(HEIGHT_OPT);
    layoutProperty->layoutConstraint_ = constraintF;
    layoutProperty->magicItemProperty_.UpdateAspectRatio(0.5);
    layoutProperty->CheckAspectRatio();

    EXPECT_EQ(layoutProperty->layoutConstraint_->selfIdealSize.Width(), 2.5);
    EXPECT_EQ(layoutProperty->layoutConstraint_->selfIdealSize.Height(), 5);

    /**
     * @tc.steps3: call CheckAspectRatio, push AspectRatio is 1.0.
     * @tc.steps3: push selfIdealSize maxSize hasvalue.
     * @tc.expected: Return expected results.
     */
    constraintF.maxSize = { 1, 2 };
    layoutProperty->layoutConstraint_ = constraintF;
    layoutProperty->magicItemProperty_.UpdateAspectRatio(1.0);
    layoutProperty->CheckAspectRatio();

    EXPECT_EQ(layoutProperty->layoutConstraint_->selfIdealSize.Width(), 1);
    EXPECT_EQ(layoutProperty->layoutConstraint_->selfIdealSize.Height(), 1);
}

/**
 * @tc.name: BuildGridProperty001
 * @tc.desc: Test cast to LayoutPropertyTestNg
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, BuildGridProperty001, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2: call BuildGridProperty, push gridProperty_ is null.
     * @tc.expected: Return expected results.
     */
    layoutProperty->Reset();
    layoutProperty->BuildGridProperty(FRAME_NODE_ROOT);
    auto parent = FRAME_NODE_ROOT->GetAncestorNodeOfFrame(false);
    EXPECT_EQ(parent, nullptr);

    /**
     * @tc.steps3: call BuildGridProperty, push gridProperty_ is hasvalue.
     * @tc.expected: Return expected results.
     */
    layoutProperty->gridProperty_ = std::make_unique<GridProperty>();
    FRAME_NODE_ROOT->SetParent(FRAME_NODE_TEST);
    FRAME_NODE_ROOT->NotifyVisibleChange(VisibleType::INVISIBLE, VisibleType::VISIBLE);
    layoutProperty->BuildGridProperty(FRAME_NODE_ROOT);
    auto result = FRAME_NODE_ROOT->GetAncestorNodeOfFrame(false);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->GetTag(), VALUE_TEST);

    /**
     * @tc.steps4: call CreatePaddingAndBorder, push layoutConstraint_ is null.
     * @tc.expected: Return paddingPropertyF left is ZERO.
     */
    PaddingPropertyF paddingPropertyF = layoutProperty->CreatePaddingAndBorder();
    EXPECT_EQ(paddingPropertyF.left, ZERO);
    EXPECT_EQ(paddingPropertyF.right, ZERO);
    EXPECT_EQ(paddingPropertyF.top, ZERO);
    EXPECT_EQ(paddingPropertyF.bottom, ZERO);
}

/**
 * @tc.name: UpdateGridProperty001
 * @tc.desc: Test cast to LayoutPropertyTestNg
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateGridProperty001, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2: call UpdateGridProperty, push gridProperty_ is null, push span is null.
     * @tc.expected: expected results propertyChangeFlag_ is PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->UpdateGridProperty(SPAN, OFFSET, GridSizeType::UNDEFINED);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);

    /**
     * @tc.steps3: call UpdateGridProperty, push gridProperty_ is null, push span is -1.
     * @tc.expected: expected results propertyChangeFlag_ is PROPERTY_UPDATE_MEASURE.
     */
    layoutProperty->UpdateGridProperty(SPAN_ONE, OFFSET_ONE, GridSizeType::XS);
    bool spanResult = layoutProperty->gridProperty_->UpdateSpan(SPAN_ONE.value(), GridSizeType::XS);
    EXPECT_FALSE(spanResult);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE);

    /**
     * @tc.steps4: call UpdateGridOffset, push gridProperty_ is null.
     * @tc.expected: Return results.is false.
     */
    bool result = layoutProperty->UpdateGridOffset(FRAME_NODE_ROOT);
    EXPECT_FALSE(result);

    /**
     * @tc.steps5: call UpdateGridProperty, push gridProperty_ is not null, push span is 1.
     * @tc.expected: Return expected results.
     */
    layoutProperty->gridProperty_ = std::make_unique<GridProperty>();
    layoutProperty->UpdateGridProperty(DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET, GridSizeType::UNDEFINED);
    EXPECT_FALSE(layoutProperty->layoutConstraint_.has_value());
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE);

    /**
     * @tc.steps6: call UpdateGridOffset, push gridProperty_ is not null.
     * @tc.expected: Return expected results.
     */
    layoutProperty->gridProperty_->gridInfo_ =
        GridSystemManager::GetInstance().GetInfoByType(GridColumnType::CAR_DIALOG);

    bool result1 = layoutProperty->UpdateGridOffset(FRAME_NODE_ROOT);
    EXPECT_EQ(layoutProperty->gridProperty_->GetOffset(), UNDEFINED_DIMENSION);
    EXPECT_FALSE(result1);
}

/**
 * @tc.name: UpdateGridProperty002
 * @tc.desc: Test cast to LayoutPropertyTestNg
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateGridProperty002, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2: call UpdateGridProperty, push gridProperty_ is not null, push span is not null.
     * @tc.expected: expected results propertyChangeFlag_ is PROPERTY_UPDATE_MEASURE.
     */
    std::optional<int32_t> spanTemp = 1;
    std::optional<int32_t> offsetTemp = 1;
    layoutProperty->UpdateGridProperty(spanTemp, offsetTemp, GridSizeType::UNDEFINED);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE);

    /**
     * @tc.steps3: call UpdateGridOffset.
     * @tc.expected: expected parent is false and return false.
     */
    auto framenodeTemp = FrameNode::CreateFrameNode("root", 2, AceType::MakeRefPtr<Pattern>(), true);
    bool result1 = layoutProperty->UpdateGridOffset(framenodeTemp);
    EXPECT_NE(layoutProperty->gridProperty_->GetOffset(), UNDEFINED_DIMENSION);
    EXPECT_EQ(framenodeTemp->GetAncestorNodeOfFrame(false), nullptr);
    EXPECT_FALSE(result1);
}

/**
 * @tc.name: CreatePaddingAndBorderWithDefault001
 * @tc.desc: Test cast to LayoutPropertyTestNg
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, CreatePaddingAndBorderWithDefault001, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2: call CreatePaddingAndBorderWithDefault, push layoutConstraint_is null.
     * @tc.expected: Return paddingPropertyF left == 1.0 + 3.0
     */
    PaddingPropertyF paddingPropertyF = layoutProperty->CreatePaddingAndBorderWithDefault(1.0, 2.0, 3.0, 4.0);
    EXPECT_EQ(paddingPropertyF.left, 1.0 + 3.0);
    EXPECT_EQ(paddingPropertyF.right, 1.0 + 3.0);

    /**
     * @tc.steps4: call CreateMargin, push layoutConstraint_ null.
     * @tc.expected: Return margin is nullopt.
     */
    PaddingPropertyF margin = layoutProperty->CreateMargin();
    EXPECT_EQ(margin.top, std::nullopt);
    EXPECT_EQ(margin.bottom, std::nullopt);

    /**
     * @tc.steps5: call CreatePaddingAndBorderWithDefault, push layoutConstraint_is not null.
     * @tc.expected: Return paddingProperty top == 2.0 + 4.0
     */
    LayoutConstraintF constraintF;
    layoutProperty->layoutConstraint_ = constraintF;
    PaddingPropertyF paddingPropertyT = layoutProperty->CreatePaddingAndBorderWithDefault(1.0, 2.0, 3.0, 4.0);
    EXPECT_EQ(paddingPropertyT.top, 2.0 + 4.0);
    EXPECT_EQ(paddingPropertyT.bottom, 2.0 + 4.0);

    /**
     * @tc.steps6: call CreatePaddingWithoutBorder, push layoutConstraint_is not null.
     * @tc.expected: Return frameNodeHost left hasvalue.
     */
    auto paddingProperty = MakePadding();
    layoutProperty->padding_ = std::make_unique<PaddingProperty>(paddingProperty);
    PaddingPropertyF paddingTwo = layoutProperty->CreatePaddingWithoutBorder();
    EXPECT_EQ(paddingTwo.left, 1);
    EXPECT_EQ(paddingTwo.right, 2);
    EXPECT_EQ(paddingTwo.top, 3);
    EXPECT_EQ(paddingTwo.bottom, 4);
}

/**
 * @tc.name: OnVisibilityUpdate001
 * @tc.desc: Test cast to LayoutPropertyTestNg
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, OnVisibilityUpdate001, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2: call OnVisibilityUpdate, push VisibleType::VISIBLE.
     * @tc.expected: expected host is null.
     */
    layoutProperty->OnVisibilityUpdate(VisibleType::VISIBLE, false);
    auto host = layoutProperty->GetHost();
    EXPECT_EQ(host, nullptr);

    /**
     * @tc.steps3: call OnVisibilityUpdate and SetHost, push VisibleType::VISIBLE.
     * @tc.expected: expected parent is null.
     */
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);
    layoutProperty->OnVisibilityUpdate(VisibleType::INVISIBLE, true);
    auto parent = layoutProperty->GetHost()->GetAncestorNodeOfFrame(false);
    EXPECT_EQ(parent, nullptr);

    /**
     * @tc.steps4: call OnVisibilityUpdate and SetParent, push VisibleType::VISIBLE.
     * @tc.expected: expected host_test is not null.
     */
    FRAME_NODE_ROOT->SetParent(FRAME_NODE_TEST);
    layoutProperty->SetHost(FRAME_NODE_ROOT);
    layoutProperty->OnVisibilityUpdate(VisibleType::VISIBLE, true);
    auto host_test = layoutProperty->GetHost();
    ASSERT_NE(host_test, nullptr);

    /**
     * @tc.steps5: call OnVisibilityUpdate, push VisibleType::GONE.
     * @tc.expected: expected parent_test is not null.
     */
    layoutProperty->OnVisibilityUpdate(VisibleType::GONE);
    auto parent_test = layoutProperty->GetHost()->GetAncestorNodeOfFrame(false);
    ASSERT_NE(parent_test, nullptr);
}

/**
 * @tc.name: CreateChildConstraint001
 * @tc.desc: Test cast to LayoutPropertyTestNg
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, CreateChildConstraint001, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2: call CreateChildConstraint, push layoutConstraint_is null.
     * @tc.expected: Return oneResult parentIdealSize is null.
     */
    LayoutConstraintF oneResult = layoutProperty->CreateChildConstraint();
    EXPECT_EQ(oneResult.parentIdealSize.Width(), std::nullopt);
    EXPECT_EQ(oneResult.parentIdealSize.Height(), std::nullopt);

    /**
     * @tc.steps3: call CreateChildConstraint, push layoutConstraint_ selfIdealSize is {10, 1}.
     * @tc.expected: Return twoResult maxSize and percentReference is {10, 1}.
     */
    layoutProperty->layoutConstraint_ = layoutConstraintF;
    layoutProperty->contentConstraint_ = layoutConstraintF;
    LayoutConstraintF twoResult = layoutProperty->CreateChildConstraint();
    EXPECT_EQ(twoResult.maxSize.Width(), 10);
    EXPECT_EQ(twoResult.maxSize.Height(), 1);
    EXPECT_EQ(twoResult.percentReference.Width(), 10);
    EXPECT_EQ(twoResult.percentReference.Height(), 1);

    /**
     * @tc.steps4: call CreateChildConstraint, push layoutConstraint_ selfIdealSize is default value.
     * @tc.expected: Return threeResult percentReference is {0, 0}.
     */
    LayoutConstraintF constraintF;
    layoutProperty->layoutConstraint_ = constraintF;
    layoutProperty->contentConstraint_ = constraintF;
    LayoutConstraintF threeResult = layoutProperty->CreateChildConstraint();
    EXPECT_EQ(threeResult.percentReference.Width(), 0);
    EXPECT_EQ(threeResult.percentReference.Height(), 0);
}

/**
 * @tc.name: UpdateContentConstraint001
 * @tc.desc: Test cast to LayoutPropertyTestNg
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateContentConstraint001, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2: call CreateChildConstraint, push layoutConstraint_is null.
     * @tc.expected: Return contentConstraint_ is nullopt.
     */
    layoutProperty->UpdateContentConstraint();
    EXPECT_EQ(layoutProperty->layoutConstraint_, std::nullopt);
    EXPECT_EQ(layoutProperty->contentConstraint_, std::nullopt);

    /**
     * @tc.steps3: call UpdateContentConstraint, push layoutConstraint_ is hasvalue, the parentIdealSize is null.
     * @tc.expected: Return expected percentReference is {1, 0}.
     */
    LayoutConstraintF constraintF;
    constraintF.percentReference = { 1, 0 };
    layoutProperty->layoutConstraint_ = constraintF;
    layoutProperty->UpdateContentConstraint();
    EXPECT_EQ(layoutProperty->contentConstraint_->percentReference.Width(), 1);
    EXPECT_EQ(layoutProperty->contentConstraint_->percentReference.Height(), 0);

    /**
     * @tc.steps4: call UpdateContentConstraint, push layoutConstraint_ is hasvalue, the parentIdealSize is {4, 4}.
     * @tc.expected: Return expected percentReference is {4, 4}.
     */
    constraintF.parentIdealSize = { 4, 4 };
    layoutProperty->layoutConstraint_ = constraintF;
    MakeProperty(layoutProperty);
    layoutProperty->UpdateContentConstraint();
    EXPECT_EQ(layoutProperty->contentConstraint_->percentReference.Width(), 4);
    EXPECT_EQ(layoutProperty->contentConstraint_->percentReference.Height(), 4);
}

/**
 * @tc.name: UpdateSafeAreaExpandOpts001
 * @tc.desc: Test cast to LayoutPropertyTestNg
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateSafeAreaExpandOpts001, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    SafeAreaExpandOpts opts;
    SafeAreaInsets safeArea;

    /**
     * @tc.steps2: push safeAreaExpandOpts_ and safeAreaInsets_ is null.
     * @tc.steps2: call UpdateSafeAreaExpandOpts and UpdateSafeAreaInsets.
     * @tc.expected: Return safeAreaExpandOpts_ edges is 0.
     */
    layoutProperty->UpdateSafeAreaExpandOpts(opts);
    layoutProperty->UpdateSafeAreaInsets(safeArea);
    EXPECT_EQ(layoutProperty->safeAreaExpandOpts_->edges, SAFE_AREA_TYPE_NONE);
    EXPECT_EQ(layoutProperty->safeAreaExpandOpts_->type, SAFE_AREA_EDGE_NONE);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, 0);

    /**
     * @tc.steps3: push safeAreaExpandOpts_ and safeAreaInsets_ is not null.
     * @tc.steps3: call UpdateSafeAreaExpandOpts and UpdateSafeAreaInsets.
     * @tc.expected: Return safeAreaExpandOpts_ edges is 1.
     */
    layoutProperty->safeAreaExpandOpts_ = std::make_unique<SafeAreaExpandOpts>(opts);
    layoutProperty->safeAreaInsets_ = std::make_unique<SafeAreaInsets>(safeArea);
    layoutProperty->UpdateSafeAreaExpandOpts(expandOpts);
    layoutProperty->UpdateSafeAreaInsets(safeAreaInset);
    EXPECT_EQ(layoutProperty->safeAreaExpandOpts_->edges, SAFE_AREA_TYPE_SYSTEM);
    EXPECT_EQ(layoutProperty->safeAreaExpandOpts_->type, SAFE_AREA_EDGE_TOP);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, 3);
}

/**
 * @tc.name: ResetCalcMinSize001
 * @tc.desc: Test cast to ResetCalcMinSize
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, ResetCalcMinSize001, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto width = CalcLength::FromString("1px");
    auto height = CalcLength::FromString("1px");
    CalcSize calcSize(width, height);
    MeasureProperty calcLayoutConstraint;
    calcLayoutConstraint.UpdateMinSizeWithCheck(calcSize);

    width = CalcLength::FromString("0px");
    height = CalcLength::FromString("0px");
    CalcSize resetCalcSize(width, height);

    /**
     * @tc.steps2 call ResetCalcMinSize with calcLayoutConstraint.
     */
    layoutProperty->UpdateCalcLayoutProperty(calcLayoutConstraint);
    layoutProperty->ResetCalcMinSize();
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL | PROPERTY_UPDATE_MEASURE);
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->minSize, std::nullopt);

    /**
     * @tc.steps3 call ResetCalcMinSize with calcLayoutConstraint_ NULL.
     */
    layoutProperty->calcLayoutConstraint_.reset();
    layoutProperty->ResetCalcMinSize();
    EXPECT_FALSE(layoutProperty->calcLayoutConstraint_);
}

/**
 * @tc.name: ResetCalcMinSize002
 * @tc.desc: Test cast to ResetCalcMinSize(bool resetWidth)
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, ResetCalcMinSize002, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto width = CalcLength::FromString("1px");
    auto height = CalcLength::FromString("1px");
    CalcSize calcSize(width, height);
    MeasureProperty calcLayoutConstraint;
    calcLayoutConstraint.UpdateMinSizeWithCheck(calcSize);
    layoutProperty->UpdateCalcLayoutProperty(calcLayoutConstraint);

    /**
     * @tc.steps2 call ResetCalcMinSize with resetWidth false calcLayoutConstraint.
     */
    layoutProperty->ResetCalcMinSize(false);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL | PROPERTY_UPDATE_MEASURE);
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->minSize.value().Width(), width);
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->minSize.value().Height(), std::nullopt);

    /**
     * @tc.steps3 call ResetCalcMinSize with resetWidth true calcLayoutConstraint.
     */
    calcLayoutConstraint.UpdateMinSizeWithCheck(calcSize);
    layoutProperty->UpdateCalcLayoutProperty(calcLayoutConstraint);
    layoutProperty->ResetCalcMinSize(true);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL | PROPERTY_UPDATE_MEASURE);
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->minSize.value().Height(), height);
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->minSize.value().Width(), std::nullopt);

    /**
     * @tc.steps3 call ResetCalcMinSize with calcLayoutConstraint_ NULL.
     */
    layoutProperty->calcLayoutConstraint_.reset();
    layoutProperty->ResetCalcMinSize();
    EXPECT_FALSE(layoutProperty->calcLayoutConstraint_);
}

/**
 * @tc.name: ResetCalcMinSize001
 * @tc.desc: Test cast to ResetCalcMaxSize
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, ResetCalcMaxSize001, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto width = CalcLength::FromString("10px");
    auto height = CalcLength::FromString("10px");
    CalcSize calcSize(width, height);
    MeasureProperty calcLayoutConstraint;
    calcLayoutConstraint.UpdateMaxSizeWithCheck(calcSize);
    layoutProperty->UpdateCalcLayoutProperty(calcLayoutConstraint);
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->maxSize, calcSize);

    /**
     * @tc.steps2 call ResetCalcMaxSize with calcLayoutConstraint.
     */
    layoutProperty->ResetCalcMaxSize();
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL | PROPERTY_UPDATE_MEASURE);
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->maxSize, std::nullopt);

    /**
     * @tc.steps3 call ResetCalcMaxSize with calcLayoutConstraint_ NULL.
     */
    layoutProperty->calcLayoutConstraint_.reset();
    layoutProperty->ResetCalcMaxSize();
    EXPECT_FALSE(layoutProperty->calcLayoutConstraint_);
}

/**
 * @tc.name: ResetCalcMaxSize002
 * @tc.desc: Test cast to ResetCalcMaxSize(bool resetWidth)
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, ResetCalcMaxSize002, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto width = CalcLength::FromString("10px");
    auto height = CalcLength::FromString("10px");
    CalcSize calcSize(width, height);
    MeasureProperty calcLayoutConstraint;
    calcLayoutConstraint.UpdateMaxSizeWithCheck(calcSize);
    layoutProperty->UpdateCalcLayoutProperty(calcLayoutConstraint);

    /**
     * @tc.steps2 call ResetCalcMaxSize with resetWidth false calcLayoutConstraint.
     */
    layoutProperty->ResetCalcMaxSize(false);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL | PROPERTY_UPDATE_MEASURE);
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->maxSize.value().Width(), width);
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->maxSize.value().Height(), std::nullopt);

    /**
     * @tc.steps3 call ResetCalcMaxSize with resetWidth true calcLayoutConstraint.
     */
    calcLayoutConstraint.UpdateMaxSizeWithCheck(calcSize);
    layoutProperty->UpdateCalcLayoutProperty(calcLayoutConstraint);
    layoutProperty->ResetCalcMaxSize(true);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL | PROPERTY_UPDATE_MEASURE);
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->maxSize.value().Height(), height);
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->maxSize.value().Width(), std::nullopt);

    /**
     * @tc.steps3 call ResetCalcMaxSize with calcLayoutConstraint_ NULL.
     */
    layoutProperty->calcLayoutConstraint_.reset();
    layoutProperty->ResetCalcMaxSize();
    EXPECT_FALSE(layoutProperty->calcLayoutConstraint_);
}

/**
 * @tc.name: UpdateFlexGrow001
 * @tc.desc: Test cast to UpdateFlexGrow
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateFlexGrow001, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    EXPECT_FALSE(layoutProperty->flexItemProperty_);

    layoutProperty->UpdateFlexGrow(1);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL | PROPERTY_UPDATE_MEASURE);
    EXPECT_FALSE(layoutProperty->flexItemProperty_->GetTwoHorizontalDirectionAligned());
}

/**
 * @tc.name: ResetFlexGrow001
 * @tc.desc: Test cast to UpdateFlexGrow
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, ResetFlexGrow001, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2 Call ResetFlexGrow without flexItemProperty_.
     */
    layoutProperty->ResetFlexGrow();
    EXPECT_FALSE(layoutProperty->flexItemProperty_);

    /**
     * @tc.steps3 Call ResetFlexGrow with flexItemProperty_.
     */
    layoutProperty->UpdateFlexGrow(1.0);
    layoutProperty->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;
    layoutProperty->ResetFlexGrow();
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL | PROPERTY_UPDATE_MEASURE);
}

/**
 * @tc.name: ResetFlexShrink001
 * @tc.desc: Test cast to ResetFlexShrink
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, ResetFlexShrink001, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2 Call ResetFlexShrink without flexItemProperty_.
     */
    layoutProperty->ResetFlexShrink();
    EXPECT_FALSE(layoutProperty->flexItemProperty_);

    /**
     * @tc.steps3 Call ResetFlexShrink with flexItemProperty_.
     */
    layoutProperty->UpdateFlexShrink(1.0);
    layoutProperty->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;
    layoutProperty->ResetFlexShrink();
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL | PROPERTY_UPDATE_MEASURE);
}

/**
 * @tc.name: UpdateFlexBasis001
 * @tc.desc: Test cast to UpdateFlexBasis
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateFlexBasis001, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2 Call UpdateFlexBasis without flexItemProperty_.
     */
    auto flexBasis = Dimension::FromString("1px");
    layoutProperty->UpdateFlexBasis(flexBasis);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL | PROPERTY_UPDATE_MEASURE);
}

/**
 * @tc.name: ResetAlignSelf001
 * @tc.desc: Test cast to ResetAlignSelf
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, ResetAlignSelf001, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2 Call UpdateFlexBasis without flexItemProperty_.
     */
    layoutProperty->ResetAlignSelf();
    EXPECT_FALSE(layoutProperty->flexItemProperty_);

    /**
     * @tc.steps3 Call UpdateFlexBasis with flexItemProperty_.
     */
    FlexAlign flexAlign = FlexAlign::CENTER;
    layoutProperty->UpdateAlignSelf(flexAlign);
    layoutProperty->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;
    layoutProperty->ResetAlignSelf();
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL | PROPERTY_UPDATE_MEASURE);

    /**
     * @tc.steps4 reset propAlignSelf.
     */
    flexAlign = FlexAlign::CENTER;
    layoutProperty->flexItemProperty_->propAlignSelf.reset();
    layoutProperty->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;
    layoutProperty->ResetAlignSelf();
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);
}

/**
 * @tc.name: UpdateDisplayIndex001
 * @tc.desc: Test cast to UpdateDisplayIndex
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateDisplayIndex001, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2 Call UpdateFlexBasis without flexItemProperty_.
     */
    EXPECT_FALSE(layoutProperty->flexItemProperty_);
    layoutProperty->UpdateDisplayIndex(0);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL | PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);

    /**
     * @tc.steps3 Call UpdateFlexBasis with flexItemProperty_ again.
     * @tc.expect Update fail
     */
    layoutProperty->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;
    layoutProperty->UpdateDisplayIndex(0);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);
}

/**
 * @tc.name: SetOverlayOffset001
 * @tc.desc: Test cast to SetOverlayOffset
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, SetOverlayOffset001, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->overlayOffsetX_ = Dimension::FromString("1px");
    layoutProperty->overlayOffsetY_ = Dimension::FromString("1px");

    /**
     * @tc.steps2 Call UpdateFlexBasis with overlayOffsetX and overlayOffsetY.
            xChanged = false, yChanged = false.
     */
    auto overlayOffsetX = std::make_optional<Dimension>(Dimension::FromString("1px"));
    auto overlayOffsetY = std::make_optional<Dimension>(Dimension::FromString("1px"));
    layoutProperty->SetOverlayOffset(overlayOffsetX, overlayOffsetY);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);

    /**
     * @tc.steps3 Call UpdateFlexBasis with overlayOffsetX and overlayOffsetY.
        @tc.expect: overlayOffsetX_ == overlayOffsetX and overlayOffsetY_ == overlayOffsetY
     */
    overlayOffsetX = std::make_optional<Dimension>(Dimension::FromString("2px"));
    overlayOffsetY = std::make_optional<Dimension>(Dimension::FromString("2px"));
    layoutProperty->SetOverlayOffset(overlayOffsetX, overlayOffsetY);
    EXPECT_EQ(layoutProperty->overlayOffsetX_, overlayOffsetX.value());
    EXPECT_EQ(layoutProperty->overlayOffsetY_, overlayOffsetY.value());

    /**
     * @tc.steps3 Call UpdateFlexBasis with overlayOffsetX and overlayOffsetY.
        @tc.expect: overlayOffsetX_ == overlayOffsetX and overlayOffsetY_ == overlayOffsetY
     */
    overlayOffsetX = std::nullopt;
    overlayOffsetY = std::nullopt;
    layoutProperty->SetOverlayOffset(overlayOffsetX, overlayOffsetY);
    EXPECT_EQ(layoutProperty->overlayOffsetX_, Dimension::FromString("0.0px"));
    EXPECT_EQ(layoutProperty->overlayOffsetY_, Dimension::FromString("0.0px"));
}

/**
 * @tc.name: UpdateAllGeometryTransition001
 * @tc.desc: Test cast to UpdateAllGeometryTransition
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateAllGeometryTransition001, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto parent = FrameNode::CreateFrameNode("parentNode", 0, AceType::MakeRefPtr<Pattern>());
    parent->GetLayoutProperty()->UpdateGeometryTransition("parent", true, true);

    auto child = FrameNode::CreateFrameNode("childNode", 1, AceType::MakeRefPtr<Pattern>());
    child->GetLayoutProperty()->UpdateGeometryTransition("child", false, true);
    child->MountToParent(parent);

    LayoutProperty::UpdateAllGeometryTransition(parent);
    EXPECT_TRUE(child->GetLayoutProperty()->GetGeometryTransition());
}

/**
 * @tc.name: CreateMargin001
 * @tc.desc: Test cast to CreateMargin
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, CreateMargin001, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2: call CreateMargin, push layoutConstraint_ null.
     * @tc.expected: Return margin is nullopt.
     */
    PaddingPropertyF margin = layoutProperty->CreateMargin();
    EXPECT_EQ(margin.top, std::nullopt);
    EXPECT_EQ(margin.bottom, std::nullopt);

    /**
     * @tc.steps3: call CreatePaddingAndBorderWithDefault, push layoutConstraint_is null.
     * @tc.expected: Return paddingPropertyF left == 1.0 + 3.0
     */
    layoutProperty->margin_ = std::make_unique<MarginProperty>();

    /**
     * @tc.steps4: call CreateMargin, push layoutConstraint_ null.
     * @tc.expected: Return margin is 0.
     */
    margin = layoutProperty->CreateMargin();
    EXPECT_FALSE(layoutProperty->layoutConstraint_.has_value());
    EXPECT_EQ(margin.top, std::nullopt);
    EXPECT_EQ(margin.bottom, std::nullopt);
}

/**
 * @tc.name: GetAspectRatio001
 * @tc.desc: Test cast to GetAspectRatio
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, GetAspectRatio001, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2: set magicItemProperty_ is null.
     */

    /**
     * @tc.steps4: call GetAspectRatio.
     * @tc.expected: Return fTemp is 0.
     */
    float fTemp = layoutProperty->GetAspectRatio();
    EXPECT_EQ(fTemp, 0.0f);
}

/**
 * @tc.name: UpdateAspectRatio001
 * @tc.desc: Test cast to UpdateAspectRatio
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateAspectRatio001, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2: create magicItemProperty_.
     */
    layoutProperty->magicItemProperty_.propAspectRatio = 1.0f;

    /**
     * @tc.steps3: call UpdateAspectRatio.
     * @tc.expected: Update false and propertyChangeFlag_ is still PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->UpdateAspectRatio(1.0f);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);
}

/**
 * @tc.name: UpdateAspectRatio002
 * @tc.desc: Test cast to UpdateAspectRatio
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateAspectRatio002, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2: call UpdateAspectRatio.
     * @tc.expected: Update true and propertyChangeFlag_ is PROPERTY_UPDATE_MEASURE.
     */
    layoutProperty->UpdateAspectRatio(1.0f);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE);
}

/**
 * @tc.name: ResetAspectRatio001
 * @tc.desc: Test cast to ResetAspectRatio
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, ResetAspectRatio001, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->ResetAspectRatio();

    /**
     * @tc.steps2: create magicItemProperty_.
     */

    /**
     * @tc.steps3: call ResetAspectRatio.
     * @tc.expected: Reset success and propertyChangeFlag_ is still PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->ResetAspectRatio();
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);
    EXPECT_FALSE(layoutProperty->magicItemProperty_.propAspectRatio.has_value());

    /**
     * @tc.steps4: create propAspectRatio.
     */
    layoutProperty->magicItemProperty_.propAspectRatio = 1.0f;

    /**
     * @tc.steps5: call ResetAspectRatio.
     * @tc.expected: Reset success and propertyChangeFlag_ is still PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->ResetAspectRatio();
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE);
    EXPECT_FALSE(layoutProperty->magicItemProperty_.propAspectRatio.has_value());
}

/**
 * @tc.name: UpdateAllGeometryTransition002
 * @tc.desc: Test cast to UpdateAllGeometryTransition
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateAllGeometryTransition002, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2 Create a weakparent.
     * @tc.expected: GetHost is not null
     */
    RefPtr<FrameNode> parent = FrameNode::CreateFrameNode("parentNode", 0, AceType::MakeRefPtr<Pattern>());
    WeakPtr<FrameNode> weakparent = AceType::WeakClaim(AceType::RawPtr(parent));
    layoutProperty->host_ = weakparent;
    EXPECT_NE(layoutProperty->GetHost(), nullptr);

    /**
     * @tc.steps3 Create a weakGeo.
     * @tc.expected: GetGeometryTransition is not null
     */
    RefPtr<GeometryTransition> geo = AceType::MakeRefPtr<GeometryTransition>("test", true, true);
    WeakPtr<GeometryTransition> weakGeo = AceType::WeakClaim(AceType::RawPtr(geo));
    layoutProperty->geometryTransition_ = weakGeo;
    EXPECT_NE(layoutProperty->GetGeometryTransition(), nullptr);

    /**
     * @tc.steps4 call UpdateGeometryTransition.
     * @tc.expected: geometryTransition_ is Changed to new
     */
    SystemProperties::debugEnabled_ = true;
    layoutProperty->UpdateGeometryTransition("test1", true, true);
    EXPECT_EQ(layoutProperty->geometryTransition_.Upgrade()->id_, "test1");
}

/**
 * @tc.name: UpdateOuterBorderWidth001
 * @tc.desc: Test cast to UpdateOuterBorderWidth
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateOuterBorderWidth001, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2: call UpdateOuterBorderWidth.
     * @tc.expected: Update false and propertyChangeFlag_ is PROPERTY_UPDATE_NORMAL.
     */
    BorderWidthProperty borderWidth;
    layoutProperty->UpdateOuterBorderWidth(borderWidth);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);

    /**
     * @tc.steps3: create borderWidth_ and call UpdateOuterBorderWidth.
     * @tc.expected: Update true and propertyChangeFlag_ is PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->outerBorderWidth_ = std::make_unique<BorderWidthProperty>();
    layoutProperty->outerBorderWidth_->leftDimen = Dimension(1.0f, DimensionUnit::PX);
    borderWidth.leftDimen = Dimension(2.0f, DimensionUnit::FP);
    layoutProperty->UpdateOuterBorderWidth(borderWidth);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_LAYOUT | PROPERTY_UPDATE_MEASURE);
    EXPECT_EQ(layoutProperty->outerBorderWidth_->leftDimen, Dimension(2.0f, DimensionUnit::FP));
}

/**
 * @tc.name: ClearUserDefinedIdealSize001
 * @tc.desc: Test cast to ClearUserDefinedIdealSize
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, ClearUserDefinedIdealSize001, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2: call ClearUserDefinedIdealSize.
     * @tc.expected: Clear false and propertyChangeFlag_ is PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->ClearUserDefinedIdealSize(true, true);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);

    /**
     * @tc.steps2: create calcLayoutConstraint_ and call ClearUserDefinedIdealSize.
     * @tc.expected: Clear false and propertyChangeFlag_ is PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    layoutProperty->ClearUserDefinedIdealSize(true, true);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);

    /**
     * @tc.steps3: set selfIdealSize.
     * @tc.expected: selfIdealSize has value is true.
     */
    auto width = CalcLength::FromString("10px");
    auto height = CalcLength::FromString("10px");
    CalcSize calcSize(width, height);
    layoutProperty->calcLayoutConstraint_->UpdateSelfIdealSizeWithCheck(calcSize);
    EXPECT_TRUE(layoutProperty->calcLayoutConstraint_->selfIdealSize.has_value());

    /**
     * @tc.steps4: call ClearUserDefinedIdealSize.
     * @tc.expected: Clear success and propertyChangeFlag_ is PROPERTY_UPDATE_MEASURE.
     */
    layoutProperty->ClearUserDefinedIdealSize(true, true);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE);
}

/**
 * @tc.name: UpdateMarginSelfIdealSize001
 * @tc.desc: Test cast to UpdateMarginSelfIdealSize
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateMarginSelfIdealSize001, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2: call UpdateMarginSelfIdealSize.
     * @tc.expected: update true and propertyChangeFlag_ is PROPERTY_UPDATE_MEASURE.
     */
    SizeF calcSize(1.0f, 2.0f);
    layoutProperty->UpdateMarginSelfIdealSize(calcSize);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE);

    /**
     * @tc.steps2: create calcLayoutConstraint_ and call ClearUserDefinedIdealSize.
     * @tc.expected: update false and propertyChangeFlag_ is PROPERTY_UPDATE_MEASURE.
     */
    layoutProperty->layoutConstraint_ = LayoutConstraintF();
    layoutProperty->UpdateMarginSelfIdealSize(calcSize);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE);

    /**
     * @tc.steps3: set selfIdealSize.
     */
    layoutProperty->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;
    OptionalSize<float> opSizeTemp(1.0f, 2.0f);
    layoutProperty->layoutConstraint_->selfIdealSize = opSizeTemp;

    /**
     * @tc.steps4: call UpdateMarginSelfIdealSize.
     * @tc.expected: update success and propertyChangeFlag_ is PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->UpdateMarginSelfIdealSize(calcSize);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);
}

/**
 * @tc.name: ResetCalcMinSize003
 * @tc.desc: Test cast to ResetCalcMinSize
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, ResetCalcMinSize003, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2: call UpdateMarginSelfIdealSize.
     * @tc.expected: update false and propertyChangeFlag_ is PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->ResetCalcMinSize();
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);

    /**
     * @tc.steps2: create calcLayoutConstraint_ and call ClearUserDefinedIdealSize.
     * @tc.expected: update false and propertyChangeFlag_ is PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    layoutProperty->ResetCalcMinSize();
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);

    /**
     * @tc.steps3: set selfIdealSize.
     */
    layoutProperty->calcLayoutConstraint_->minSize = CALC_SIZE;

    /**
     * @tc.steps4: call UpdateMarginSelfIdealSize.
     * @tc.expected: update success and propertyChangeFlag_ is PROPERTY_UPDATE_MEASURE.
     */
    layoutProperty->ResetCalcMinSize();
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE);
}

/**
 * @tc.name: ResetCalcMaxSize003
 * @tc.desc: Test cast to ResetCalcMaxSize
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, ResetCalcMaxSize003, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2: call UpdateMarginSelfIdealSize.
     * @tc.expected: update false and propertyChangeFlag_ is PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->ResetCalcMaxSize();
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);

    /**
     * @tc.steps2: create calcLayoutConstraint_ and call ClearUserDefinedIdealSize.
     * @tc.expected: update false and propertyChangeFlag_ is PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    layoutProperty->ResetCalcMaxSize();
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);

    /**
     * @tc.steps3: set selfIdealSize.
     */
    layoutProperty->calcLayoutConstraint_->maxSize = CALC_SIZE;

    /**
     * @tc.steps4: call UpdateMarginSelfIdealSize.
     * @tc.expected: update success and propertyChangeFlag_ is PROPERTY_UPDATE_MEASURE.
     */
    layoutProperty->ResetCalcMaxSize();
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE);
}

/**
 * @tc.name: UpdateFlexGrow002
 * @tc.desc: Test cast to UpdateFlexGrow
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateFlexGrow002, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2 Call ResetFlexGrow without flexItemProperty_.
     */
    layoutProperty->UpdateFlexGrow(1.0);

    /**
     * @tc.steps3 Call ResetFlexGrow with flexItemProperty_.
     */
    layoutProperty->UpdateFlexGrow(1.0);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL | PROPERTY_UPDATE_MEASURE);

    /**
     * @tc.steps4 reset propertyChangeFlag_ and call UpdateFlexGrow.
     * @tc.expected: update fail and propertyChangeFlag_ is PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;
    layoutProperty->flexItemProperty_->propFlexGrow = 1.0f;
    layoutProperty->UpdateFlexGrow(1.0);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);

    /**
     * @tc.steps4 call UpdateFlexGrow.
     * @tc.expected: update success and propertyChangeFlag_ is PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->UpdateFlexGrow(2.0);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE);
    EXPECT_EQ(layoutProperty->flexItemProperty_->propFlexGrow, 2.0f);
}

/**
 * @tc.name: ResetFlexGrow002
 * @tc.desc: Test cast to ResetFlexGrow
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, ResetFlexGrow002, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2 Call ResetFlexGrow without flexItemProperty_.
     */
    layoutProperty->ResetFlexGrow();
    EXPECT_FALSE(layoutProperty->flexItemProperty_);

    /**
     * @tc.steps3 Call ResetFlexGrow with flexItemProperty_.
     * @tc.expected: propertyChangeFlag_ is PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->flexItemProperty_ = std::make_unique<FlexItemProperty>();
    layoutProperty->ResetFlexGrow();
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);

    /**
     * @tc.steps4 set propFlexGrow and call ResetFlexGrow.
     * @tc.expected: propertyChangeFlag_ is PROPERTY_UPDATE_MEASURE.
     */
    layoutProperty->flexItemProperty_->propFlexGrow = 2.0f;
    layoutProperty->ResetFlexGrow();
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE);
}

/**
 * @tc.name: UpdateFlexShrink001
 * @tc.desc: Test cast to UpdateFlexShrink
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateFlexShrink001, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2 Call ResetFlexGrow without flexItemProperty_.
     */
    layoutProperty->UpdateFlexShrink(1.0);

    /**
     * @tc.steps3 Call ResetFlexGrow with flexItemProperty_.
     */
    layoutProperty->UpdateFlexShrink(1.0);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL | PROPERTY_UPDATE_MEASURE);

    /**
     * @tc.steps4 reset propertyChangeFlag_ and call UpdateFlexGrow.
     * @tc.expected: update fail and propertyChangeFlag_ is PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;
    layoutProperty->flexItemProperty_->propFlexShrink = 1.0f;
    layoutProperty->UpdateFlexShrink(1.0);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);

    /**
     * @tc.steps4 call UpdateFlexGrow.
     * @tc.expected: update success and propertyChangeFlag_ is PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->UpdateFlexShrink(2.0);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE);
    EXPECT_EQ(layoutProperty->flexItemProperty_->propFlexShrink, 2.0f);
}

/**
 * @tc.name: ResetFlexShrink002
 * @tc.desc: Test cast to ResetFlexShrink
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, ResetFlexShrink002, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2 Call ResetFlexShrink without flexItemProperty_.
     */
    layoutProperty->ResetFlexShrink();
    EXPECT_FALSE(layoutProperty->flexItemProperty_);

    /**
     * @tc.steps3 Call ResetFlexShrink with flexItemProperty_.
     * @tc.expected: propertyChangeFlag_ is PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->flexItemProperty_ = std::make_unique<FlexItemProperty>();
    layoutProperty->ResetFlexShrink();
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);

    /**
     * @tc.steps3 Set propFlexShrink and Call ResetFlexShrink with flexItemProperty_.
     * @tc.expected: propertyChangeFlag_ is PROPERTY_UPDATE_MEASURE.
     */
    layoutProperty->flexItemProperty_->propFlexShrink = 1.0f;
    layoutProperty->ResetFlexShrink();
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL | PROPERTY_UPDATE_MEASURE);
}

/**
 * @tc.name: UpdateFlexBasis002
 * @tc.desc: Test cast to UpdateFlexBasis
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateFlexBasis002, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2 Call ResetFlexGrow without flexItemProperty_.
     */
    Dimension dim(1.0, DimensionUnit::PX);
    layoutProperty->UpdateFlexBasis(dim);

    /**
     * @tc.steps3 Call ResetFlexGrow with flexItemProperty_.
     */
    layoutProperty->UpdateFlexBasis(dim);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL | PROPERTY_UPDATE_MEASURE);

    /**
     * @tc.steps4 reset propertyChangeFlag_ and call UpdateFlexGrow.
     * @tc.expected: update fail and propertyChangeFlag_ is PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;
    layoutProperty->flexItemProperty_->propFlexBasis = dim;
    layoutProperty->UpdateFlexBasis(dim);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);

    /**
     * @tc.steps4 call UpdateFlexGrow.
     * @tc.expected: update success and propertyChangeFlag_ is PROPERTY_UPDATE_MEASURE.
     */
    layoutProperty->UpdateFlexBasis(Dimension(2.0, DimensionUnit::VP));
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE);
    EXPECT_EQ(layoutProperty->flexItemProperty_->propFlexBasis, Dimension(2.0, DimensionUnit::VP));
}

/**
 * @tc.name: UpdateAlignRules001
 * @tc.desc: Test cast to UpdateAlignRules
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateAlignRules001, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2 Call UpdateAlignRules without flexItemProperty_.
     * @tc.expected: update success and propertyChangeFlag_ is PROPERTY_UPDATE_MEASURE.
     */
    std::map<AlignDirection, AlignRule> firstItemAlignRules;
    AlignRule alignRule;
    alignRule.anchor = "test";
    alignRule.horizontal = HorizontalAlign::START;
    firstItemAlignRules[AlignDirection::LEFT] = alignRule;

    layoutProperty->UpdateAlignRules(firstItemAlignRules);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE);

    /**
     * @tc.steps2 Call ResetFlexGrow again with flexItemProperty_.
     * @tc.expected: update fail and propertyChangeFlag_ is PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;
    layoutProperty->UpdateAlignRules(firstItemAlignRules);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);
}

/**
 * @tc.name: GetPercentSensitive001
 * @tc.desc: Test cast to GetPercentSensitive
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, GetPercentSensitive001, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2 Call GetPercentSensitive without contentConstraint_.
     */
    std::pair<bool, bool> res = layoutProperty->GetPercentSensitive();
    EXPECT_EQ(res.first, false);
    EXPECT_EQ(res.second, false);

    /**
     * @tc.steps2 ReCall GetPercentSensitive with contentConstraint_ without calcLayoutConstraint_.
     */
    LayoutConstraintF layoutConstraintF;
    layoutConstraintF.maxSize = { 1.0, 1.0 };
    layoutProperty->contentConstraint_ = layoutConstraintF;
    res = layoutProperty->GetPercentSensitive();
    EXPECT_EQ(res.first, false);
    EXPECT_EQ(res.second, false);

    /**
     * @tc.steps3 ReCall GetPercentSensitive with contentConstraint_ without calcLayoutConstraint_.
     */
    layoutConstraintF.maxSize = { Infinity<float>() / 2.0f, Infinity<float>() / 2.0f };
    layoutProperty->contentConstraint_ = layoutConstraintF;
    res = layoutProperty->GetPercentSensitive();
    EXPECT_EQ(res.first, false);
    EXPECT_EQ(res.second, false);

    /**
     * @tc.steps4 ReCall GetPercentSensitive with contentConstraint_ with calcLayoutConstraint_.
     */
    CalcLength calcTemp("test1");
    calcTemp.dimension_ = Dimension(2.0f, DimensionUnit::PERCENT);
    layoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    CalcSize cTemp;
    cTemp.width_ = calcTemp;
    cTemp.height_ = calcTemp;
    layoutProperty->calcLayoutConstraint_->selfIdealSize = cTemp;
    res = layoutProperty->GetPercentSensitive();
    EXPECT_EQ(res.first, true);
    EXPECT_EQ(res.second, true);
}

/**
 * @tc.name: UpdatePercentSensitive001
 * @tc.desc: Test cast to UpdatePercentSensitive
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdatePercentSensitive001, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2 Call UpdatePercentSensitive without contentConstraint_.
     */
    std::pair<bool, bool> res = layoutProperty->UpdatePercentSensitive(false, false);
    EXPECT_EQ(res.first, false);
    EXPECT_EQ(res.second, false);

    /**
     * @tc.steps3 ReCall UpdatePercentSensitive with contentConstraint_.
     */
    LayoutConstraintF layoutConstraintF;
    layoutConstraintF.maxSize = { 1.0, 1.0 };
    layoutProperty->contentConstraint_ = layoutConstraintF;
    res = layoutProperty->UpdatePercentSensitive(false, false);
    EXPECT_EQ(res.first, false);
    EXPECT_EQ(res.second, false);

    /**
     * @tc.steps4 ReCall UpdatePercentSensitive with contentConstraint_ .
     */
    layoutConstraintF.maxSize = { Infinity<float>() / 2.0f, Infinity<float>() / 2.0f };
    layoutProperty->contentConstraint_ = layoutConstraintF;
    res = layoutProperty->UpdatePercentSensitive(false, false);
    EXPECT_EQ(res.first, false);
    EXPECT_EQ(res.second, false);

    /**
     * @tc.steps5 ReCall UpdatePercentSensitive with contentConstraint_.
     */
    layoutConstraintF.maxSize = { Infinity<float>() / 2.0f, Infinity<float>() / 2.0f };
    layoutProperty->contentConstraint_ = layoutConstraintF;
    res = layoutProperty->UpdatePercentSensitive(true, true);
    EXPECT_EQ(res.first, true);
    EXPECT_EQ(res.second, true);
}

/**
 * @tc.name: ConstraintEqual001
 * @tc.desc: Test cast to ConstraintEqual
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, ConstraintEqual001, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    LayoutConstraintF preLayoutTemp;
    LayoutConstraintF preContentTemp;

    /**
     * @tc.steps2 Call ConstraintEqual without preLayoutTemp,preLayoutTemp.
     */
    bool bResult = layoutProperty->ConstraintEqual(preLayoutTemp, preContentTemp); // 1065
    EXPECT_FALSE(bResult);

    /**
     * @tc.steps3 Call ConstraintEqual with layoutConstraint_.
     */
    layoutProperty->layoutConstraint_ = preLayoutTemp;
    bResult = layoutProperty->ConstraintEqual(preLayoutTemp, preContentTemp); // 1068
    EXPECT_FALSE(bResult);

    /**
     * @tc.steps4 Call ConstraintEqual with contentConstraint_.
     */
    preLayoutTemp.maxSize.width_ = Infinity<float>() / 2.0f;
    preLayoutTemp.maxSize.height_ = Infinity<float>() / 2.0f;
    layoutProperty->contentConstraint_ = preContentTemp;
    layoutProperty->widthPercentSensitive_ = false;
    bResult = layoutProperty->ConstraintEqual(preLayoutTemp, preContentTemp); // 1073
    EXPECT_TRUE(bResult);

    /**
     * @tc.steps5 Call ConstraintEqual with contentConstraint_ and Width true Height false.
     */
    layoutProperty->widthPercentSensitive_ = true;
    layoutProperty->heightPercentSensitive_ = false;
    bResult = layoutProperty->ConstraintEqual(preLayoutTemp, preContentTemp); // 1078
    EXPECT_TRUE(bResult);

    /**
     * @tc.steps6 Call ConstraintEqual with contentConstraint_and Width true Height true.
     */
    layoutProperty->heightPercentSensitive_ = true;
    bResult = layoutProperty->ConstraintEqual(preLayoutTemp, preContentTemp); // 1080
    EXPECT_FALSE(bResult);
}

/**
 * @tc.name: ConstraintEqual002
 * @tc.desc: Test cast to ConstraintEqual002
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, ConstraintEqual002, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    LayoutConstraintF preLayoutTemp;
    LayoutConstraintF preContentTemp;

    /**
     * @tc.steps2 Call ConstraintEqual without preLayoutTemp,preLayoutTemp.
     */
    bool bResult = layoutProperty->ConstraintEqual(preLayoutTemp, preContentTemp); // 1065
    EXPECT_FALSE(bResult);

    /**
     * @tc.steps3 Call ConstraintEqual with layoutConstraint_.
     */
    layoutProperty->layoutConstraint_ = preLayoutTemp;
    bResult = layoutProperty->ConstraintEqual(preLayoutTemp, preContentTemp); // 1068
    EXPECT_FALSE(bResult);

    /**
     * @tc.steps4 Call ConstraintEqual with contentConstraint_.
     */
    preContentTemp.maxSize.width_ = Infinity<float>() / 2.0f;
    preContentTemp.maxSize.height_ = Infinity<float>() / 2.0f;
    layoutProperty->contentConstraint_ = preContentTemp;
    layoutProperty->layoutConstraint_ = preLayoutTemp;
    layoutProperty->widthPercentSensitive_ = false;
    bResult = layoutProperty->ConstraintEqual(preLayoutTemp, preContentTemp); // 1073
    EXPECT_TRUE(bResult);

    /**
     * @tc.steps5 Call ConstraintEqual with contentConstraint_ and Width true Height false.
     */
    layoutProperty->widthPercentSensitive_ = true;
    layoutProperty->heightPercentSensitive_ = false;
    bResult = layoutProperty->ConstraintEqual(preLayoutTemp, preContentTemp); // 1078
    EXPECT_TRUE(bResult);

    /**
     * @tc.steps6 Call ConstraintEqual with contentConstraint_and Width true Height true.
     */
    layoutProperty->heightPercentSensitive_ = true;
    bResult = layoutProperty->ConstraintEqual(preLayoutTemp, preContentTemp); // 1080
    EXPECT_TRUE(bResult);
}
} // namespace OHOS::Ace::NG
