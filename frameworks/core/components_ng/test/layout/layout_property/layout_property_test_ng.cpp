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

#define protected public
#define private public
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components_ng/property/safe_area_insets.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::optional<float> ZERO {0.0};
const std::optional<int32_t> SPAN_ONE {-1};
const std::optional<int32_t> OFFSET_ONE {-1};
const std::optional<int> WIDTH_OPT {10};
const std::optional<int> HEIGHT_OPT {5};
const std::optional<int32_t> SPAN;
const std::optional<int32_t> OFFSET;

constexpr Dimension WIDTH = 1.0_vp;
constexpr Dimension HEIGHT = 2.0_vp;
constexpr Dimension TOPONE = 3.0_vp;
constexpr Dimension BOTTOMONE = 4.0_vp;

const std::string VALUE_TEST = "test";
const std::string STRING_TEST =
    "{\"top\":\"3.00vp\",\"right\":\"2.00vp\",\"bottom\":\"4.00vp\",\"left\":\"1.00vp\"}";

const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode("root", 1, AceType::MakeRefPtr<Pattern>(), true);
const auto FRAME_NODE_TEST = FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<Pattern>(), true);

const CalcSize CALC_SIZE = {CalcLength(WIDTH), CalcLength(HEIGHT)};
MagicItemProperty magicItemProperty;

LayoutConstraintF layoutConstraintF = {
    .minSize = {1, 1},
    .maxSize = {10, 10},
    .percentReference = {5, 5},
    .parentIdealSize = {2, 2},
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
    layoutProperty->magicItemProperty_ = std::make_unique<MagicItemProperty>();
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
    paddingProperty.left = {CalcLength(WIDTH)};
    paddingProperty.right = {CalcLength(HEIGHT)};
    paddingProperty.top = {CalcLength(TOPONE)};
    paddingProperty.bottom = {CalcLength(BOTTOMONE)};

    return paddingProperty;
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
    layoutProperty->ToJsonValue(json);
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
    layoutProperty->ToJsonValue(json);
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
    magicItemProperty.UpdateAspectRatio(1.0);
    layoutProperty->magicItemProperty_ = std::make_unique<MagicItemProperty>(magicItemProperty);
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
    layoutConstraintF.selfIdealSize = {1, -1};
    layoutProperty->layoutConstraint_ = layoutConstraintF;
    layoutProperty->CheckBorderAndPadding();
    EXPECT_EQ(layoutProperty->layoutConstraint_->selfIdealSize.Width(), 1);
    EXPECT_EQ(layoutProperty->layoutConstraint_->selfIdealSize.Height(), 0);

    /**
     * @tc.steps3: call CheckBorderAndPadding.push selfIdealSize is {-1,1}.
     * @tc.expected: Return expected results..
     */
    layoutConstraintF.selfIdealSize = {-1, 1};
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
    magicItemProperty.UpdateAspectRatio(1.0);
    layoutProperty->magicItemProperty_ = std::make_unique<MagicItemProperty>(magicItemProperty);
    layoutProperty->CheckAspectRatio();
    EXPECT_EQ(layoutProperty->layoutConstraint_->selfIdealSize.Width(), std::nullopt);
    EXPECT_EQ(layoutProperty->layoutConstraint_->selfIdealSize.Height(), std::nullopt);

    /**
     * @tc.steps3: callback CheckAspectRatio.push layoutConstraint_ is not null.
     * @tc.steps3: push selfIdealSize Width hasvalue.
     * @tc.expected: Return expected results.
     */
    layoutConstraintF.maxSize = {2, 4};
    layoutConstraintF.selfIdealSize.SetWidth(WIDTH_OPT);
    layoutProperty->layoutConstraint_ = layoutConstraintF;
    layoutProperty->CheckAspectRatio();
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
    magicItemProperty.UpdateAspectRatio(0.5);
    layoutProperty->magicItemProperty_ = std::make_unique<MagicItemProperty>(magicItemProperty);
    layoutProperty->CheckAspectRatio();

    EXPECT_EQ(layoutProperty->layoutConstraint_->selfIdealSize.Width(), 2.5);
    EXPECT_EQ(layoutProperty->layoutConstraint_->selfIdealSize.Height(), 5);

    /**
     * @tc.steps3: call CheckAspectRatio, push AspectRatio is 1.0.
     * @tc.steps3: push selfIdealSize maxSize hasvalue.
     * @tc.expected: Return expected results.
     */
    constraintF.maxSize = {1, 2};
    layoutProperty->layoutConstraint_ = constraintF;
    magicItemProperty.UpdateAspectRatio(1.0);
    layoutProperty->magicItemProperty_ = std::make_unique<MagicItemProperty>(magicItemProperty);
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
    auto parent = FRAME_NODE_ROOT->GetAncestorNodeOfFrame();
    EXPECT_EQ(parent, nullptr);

    /**
     * @tc.steps3: call BuildGridProperty, push gridProperty_ is hasvalue.
     * @tc.expected: Return expected results.
     */
    layoutProperty->gridProperty_ = std::make_unique<GridProperty>();
    FRAME_NODE_ROOT->SetParent(FRAME_NODE_TEST);
    FRAME_NODE_ROOT->OnVisibleChange(true);
    layoutProperty->BuildGridProperty(FRAME_NODE_ROOT);
    auto result = FRAME_NODE_ROOT->GetAncestorNodeOfFrame();
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
    EXPECT_EQ(layoutProperty->layoutConstraint_->minSize.Width(), 0);
    EXPECT_EQ(layoutProperty->layoutConstraint_->minSize.Height(), 0);
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
     * @tc.steps3: call CreatePaddingWithoutBorder, push layoutConstraint_is null.
     * @tc.expected: Return paddingOne is nullopt.
     */
    PaddingPropertyF paddingOne = layoutProperty->CreatePaddingWithoutBorder();
    EXPECT_EQ(paddingOne.left, std::nullopt);
    EXPECT_EQ(paddingOne.right, std::nullopt);

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
    auto host =layoutProperty->GetHost();
    EXPECT_EQ(host, nullptr);

    /**
     * @tc.steps3: call OnVisibilityUpdate and SetHost, push VisibleType::VISIBLE.
     * @tc.expected: expected parent is null.
     */
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);
    layoutProperty->OnVisibilityUpdate(VisibleType::INVISIBLE, true);
    auto parent = layoutProperty->GetHost()->GetAncestorNodeOfFrame();
    EXPECT_EQ(parent, nullptr);

    /**
     * @tc.steps4: call OnVisibilityUpdate and SetParent, push VisibleType::VISIBLE.
     * @tc.expected: expected host_test is not null.
     */
    FRAME_NODE_ROOT->SetParent(FRAME_NODE_TEST);
    layoutProperty->SetHost(FRAME_NODE_ROOT);
    layoutProperty->OnVisibilityUpdate(VisibleType::VISIBLE, true);
    auto host_test =layoutProperty->GetHost();
    ASSERT_NE(host_test, nullptr);

    /**
     * @tc.steps5: call OnVisibilityUpdate, push VisibleType::GONE.
     * @tc.expected: expected parent_test is not null.
     */
    layoutProperty->OnVisibilityUpdate(VisibleType::GONE);
    auto parent_test = layoutProperty->GetHost()->GetAncestorNodeOfFrame();
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
    constraintF.percentReference = {1, 0};
    layoutProperty->layoutConstraint_ = constraintF;
    layoutProperty->UpdateContentConstraint();
    EXPECT_EQ(layoutProperty->contentConstraint_->percentReference.Width(), 1);
    EXPECT_EQ(layoutProperty->contentConstraint_->percentReference.Height(), 0);

    /**
     * @tc.steps4: call UpdateContentConstraint, push layoutConstraint_ is hasvalue, the parentIdealSize is {4, 4}.
     * @tc.expected: Return expected percentReference is {4, 4}.
     */
    constraintF.parentIdealSize = {4, 4};
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
    layoutProperty->safeAreaExpandOpts_= std::make_unique<SafeAreaExpandOpts>(opts);
    layoutProperty->safeAreaInsets_= std::make_unique<SafeAreaInsets>(safeArea);
    layoutProperty->UpdateSafeAreaExpandOpts(expandOpts);
    layoutProperty->UpdateSafeAreaInsets(safeAreaInset);
    EXPECT_EQ(layoutProperty->safeAreaExpandOpts_->edges, SAFE_AREA_TYPE_SYSTEM);
    EXPECT_EQ(layoutProperty->safeAreaExpandOpts_->type, SAFE_AREA_EDGE_TOP);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, 3);
}
}
