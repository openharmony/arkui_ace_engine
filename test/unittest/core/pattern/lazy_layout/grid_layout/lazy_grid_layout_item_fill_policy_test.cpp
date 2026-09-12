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

#include "arkoala_api_generated.h"
#include "lazy_grid_layout_test.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "base/utils/layout_break_point.h"
#include "core/components_ng/pattern/lazy_grid_layout/lazy_grid_layout_model.h"
#include "core/components_ng/pattern/lazy_grid_layout/lazy_grid_layout_property.h"
#include "core/components_ng/property/templates_parser.h"
#include "core/interfaces/native/utility/reverse_converter.h"

struct _ArkUINode;

namespace OHOS::Ace::NG::GeneratedModifier {
const GENERATED_ArkUILazyVGridLayoutModifier* GetLazyVGridLayoutStaticModifier();
}

namespace OHOS::Ace::NG {
void SetLazyGridLayoutItemFillPolicy(_ArkUINode* node, int32_t policy);
namespace {
// Width breakpoints (vp, density 1.0 in host tests): SM < 600, MD [600, 840), LG >= 840.
constexpr float WIDTH_SM = 200.0f;
constexpr float WIDTH_MD = 700.0f;
constexpr float WIDTH_LG = 1000.0f;
constexpr float VIEWPORT_HEIGHT = 450.0f;

class WidthBreakpointsGuard final {
public:
    explicit WidthBreakpointsGuard(const WidthLayoutBreakPoint& breakpoints)
        : original_(SystemProperties::GetWidthLayoutBreakpoints())
    {
        const_cast<WidthLayoutBreakPoint&>(SystemProperties::GetWidthLayoutBreakpoints()) = breakpoints;
    }

    ~WidthBreakpointsGuard()
    {
        const_cast<WidthLayoutBreakPoint&>(SystemProperties::GetWidthLayoutBreakpoints()) = original_;
    }

private:
    WidthLayoutBreakPoint original_;
};

class DensityGuard final {
public:
    explicit DensityGuard(double density) : pipeline_(MockPipelineContext::GetCurrent())
    {
        if (pipeline_) {
            original_ = pipeline_->GetDensity();
            pipeline_->SetDensity(density);
        }
    }

    ~DensityGuard()
    {
        if (pipeline_) {
            pipeline_->SetDensity(original_);
        }
    }

private:
    RefPtr<MockPipelineContext> pipeline_;
    double original_ = 1.0;
};

RefPtr<FrameNode> GetLazyGridChild(const RefPtr<FrameNode>& frameNode, int32_t index)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    return AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(index));
}
} // namespace

/**
 * @tc.name: ItemFillPolicyBreakpointTest001
 * @tc.desc: AC-1/AC-3. columnsTemplate(ItemFillPolicy SM1MD2LG3) renders 1/2/3 columns at SM/MD/LG
 *           container widths and re-measures when the width crosses breakpoints.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, ItemFillPolicyBreakpointTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy grid layout at SM width with ItemFillPolicy SM1MD2LG3.
     * @tc.expected: 1 lane at SM width.
     */
    CreateWaterFlow();
    CreateLazyGridLayout();
    CreateContent(30);
    CreateDone();
    LazyVGridLayoutModel::SetItemFillPolicy(AceType::RawPtr(frameNode_), PresetFillType::BREAKPOINT_SM1MD2LG3);
    FlushUITasks();
    EXPECT_TRUE(layoutProperty_->GetItemFillPolicy().has_value());
    EXPECT_FALSE(layoutProperty_->GetColumnsTemplate().has_value());
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 1);
    auto firstChild = GetLazyGridChild(frameNode_, 0);
    ASSERT_NE(firstChild, nullptr);
    EXPECT_NEAR(firstChild->GetGeometryNode()->GetFrameSize().Width(), WIDTH_SM, 0.01f);
    EXPECT_NEAR(firstChild->GetGeometryNode()->GetFrameOffset().GetX(), 0.0f, 0.01f);

    /**
     * @tc.steps: step2. Resize container to MD width.
     * @tc.expected: lanes re-measured to 2.
     */
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(WIDTH_MD), CalcLength(VIEWPORT_HEIGHT)));
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 2);
    auto secondChild = GetLazyGridChild(frameNode_, 1);
    ASSERT_NE(secondChild, nullptr);
    EXPECT_NEAR(firstChild->GetGeometryNode()->GetFrameSize().Width(), WIDTH_MD / 2.0f, 0.01f);
    EXPECT_NEAR(secondChild->GetGeometryNode()->GetFrameOffset().GetX(), WIDTH_MD / 2.0f, 0.01f);

    /**
     * @tc.steps: step3. Resize container to LG width.
     * @tc.expected: lanes re-measured to 3.
     */
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(WIDTH_LG), CalcLength(VIEWPORT_HEIGHT)));
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 3);
    EXPECT_NEAR(firstChild->GetGeometryNode()->GetFrameSize().Width(), WIDTH_LG / 3.0f, 0.01f);
    EXPECT_NEAR(secondChild->GetGeometryNode()->GetFrameOffset().GetX(), WIDTH_LG / 3.0f, 0.01f);

    /**
     * @tc.steps: step4. Resize container back to SM width.
     * @tc.expected: lanes re-measured to 1.
     */
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(WIDTH_SM), CalcLength(VIEWPORT_HEIGHT)));
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 1);
}

/**
 * @tc.name: ItemFillPolicyBreakpointTest002
 * @tc.desc: AC-2. columnsTemplate(ItemFillPolicy SM2MD3LG5) renders 2/3/5 columns at SM/MD/LG widths.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, ItemFillPolicyBreakpointTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy grid layout at SM width with ItemFillPolicy SM2MD3LG5.
     * @tc.expected: 2 lanes at SM width.
     */
    CreateWaterFlow();
    CreateLazyGridLayout();
    CreateContent(30);
    CreateDone();
    LazyVGridLayoutModel::SetItemFillPolicy(AceType::RawPtr(frameNode_), PresetFillType::BREAKPOINT_SM2MD3LG5);
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 2);
    auto firstChild = GetLazyGridChild(frameNode_, 0);
    auto secondChild = GetLazyGridChild(frameNode_, 1);
    ASSERT_NE(firstChild, nullptr);
    ASSERT_NE(secondChild, nullptr);
    EXPECT_NEAR(firstChild->GetGeometryNode()->GetFrameSize().Width(), WIDTH_SM / 2.0f, 0.01f);
    EXPECT_NEAR(secondChild->GetGeometryNode()->GetFrameOffset().GetX(), WIDTH_SM / 2.0f, 0.01f);

    /**
     * @tc.steps: step2. Resize container to MD / LG width.
     * @tc.expected: 3 / 5 lanes.
     */
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(WIDTH_MD), CalcLength(VIEWPORT_HEIGHT)));
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 3);
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(WIDTH_LG), CalcLength(VIEWPORT_HEIGHT)));
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 5);
    EXPECT_NEAR(firstChild->GetGeometryNode()->GetFrameSize().Width(), WIDTH_LG / 5.0f, 0.01f);
    EXPECT_NEAR(secondChild->GetGeometryNode()->GetFrameOffset().GetX(), WIDTH_LG / 5.0f, 0.01f);
}

/**
 * @tc.name: ItemFillPolicyOverrideStringTest003
 * @tc.desc: AC-4. Setting the ItemFillPolicy form after the string form resets ColumnsTemplate (last-set-wins).
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, ItemFillPolicyOverrideStringTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy grid layout with columnsTemplate "1fr 1fr" (2 lanes).
     */
    CreateWaterFlow();
    CreateLazyGridLayout();
    CreateContent(30);
    CreateDone();
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 2);
    EXPECT_TRUE(layoutProperty_->GetColumnsTemplate().has_value());

    /**
     * @tc.steps: step2. Set ItemFillPolicy SM1MD2LG3 afterwards.
     * @tc.expected: ColumnsTemplate is reset, breakpoint policy takes effect (1 lane at SM width).
     */
    LazyVGridLayoutModel::SetItemFillPolicy(AceType::RawPtr(frameNode_), PresetFillType::BREAKPOINT_SM1MD2LG3);
    FlushUITasks();
    EXPECT_FALSE(layoutProperty_->GetColumnsTemplate().has_value());
    EXPECT_TRUE(layoutProperty_->GetItemFillPolicy().has_value());
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 1);
}

/**
 * @tc.name: StringOverrideItemFillPolicyTest004
 * @tc.desc: AC-5. Setting the string form after the ItemFillPolicy form resets ItemFillPolicy (last-set-wins).
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, StringOverrideItemFillPolicyTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy grid layout and set ItemFillPolicy SM2MD3LG5 (2 lanes at SM width).
     */
    CreateWaterFlow();
    CreateLazyGridLayout();
    CreateContent(30);
    CreateDone();
    LazyVGridLayoutModel::SetItemFillPolicy(AceType::RawPtr(frameNode_), PresetFillType::BREAKPOINT_SM2MD3LG5);
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 2);

    /**
     * @tc.steps: step2. Set columnsTemplate "1fr 1fr 1fr" afterwards.
     * @tc.expected: ItemFillPolicy is reset, fixed 3 lanes regardless of width.
     */
    LazyVGridLayoutModel::SetColumnsTemplate(AceType::RawPtr(frameNode_), "1fr 1fr 1fr");
    FlushUITasks();
    EXPECT_FALSE(layoutProperty_->GetItemFillPolicy().has_value());
    EXPECT_TRUE(layoutProperty_->GetColumnsTemplate().has_value());
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 3);
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(WIDTH_LG), CalcLength(VIEWPORT_HEIGHT)));
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 3);
}

/**
 * @tc.name: ResetItemFillPolicyTest005
 * @tc.desc: AC-6. Resetting the policy clears the setting and restores the default single column.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, ResetItemFillPolicyTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy grid layout with ItemFillPolicy SM2MD3LG5.
     */
    CreateWaterFlow();
    CreateLazyGridLayout();
    CreateContent(30);
    CreateDone();
    const auto* modifier = GeneratedModifier::GetLazyVGridLayoutStaticModifier();
    ASSERT_NE(modifier, nullptr);
    ASSERT_NE(modifier->setColumnsTemplate1, nullptr);
    auto nativeNode = reinterpret_cast<Ark_NativePointer>(AceType::RawPtr(frameNode_));
    Opt_Union_String_ItemFillPolicy unionPolicy {};
    unionPolicy.tag = INTEROP_TAG_OBJECT;
    unionPolicy.value.selector = 1;
    unionPolicy.value.value1.fillType.tag = INTEROP_TAG_OBJECT;
    unionPolicy.value.value1.fillType.value = ARK_PRESET_FILL_TYPE_BREAKPOINT_SM2MD3LG5;
    modifier->setColumnsTemplate1(nativeNode, &unionPolicy);
    FlushUITasks();
    EXPECT_TRUE(layoutProperty_->GetItemFillPolicy().has_value());
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 2);

    /**
     * @tc.steps: step2. Pass undefined through the public static columnsTemplate union slot.
     * @tc.expected: policy is cleared and the default "1fr" template is written back.
     */
    auto undefinedValue = Converter::ArkValue<Opt_Union_String_ItemFillPolicy>();
    modifier->setColumnsTemplate1(nativeNode, &undefinedValue);
    FlushUITasks();
    EXPECT_FALSE(layoutProperty_->GetItemFillPolicy().has_value());
    EXPECT_EQ(layoutProperty_->GetColumnsTemplate().value_or(""), "1fr");
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 1);
}

/**
 * @tc.name: ColumnsTemplateOnlyRegressionTest006
 * @tc.desc: AC-7/AC-8. Using only columnsTemplate(string) keeps the legacy behavior.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, ColumnsTemplateOnlyRegressionTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy grid layout with columnsTemplate "1fr 1fr" only.
     * @tc.expected: 2 lanes, no ItemFillPolicy set, template unchanged across widths.
     */
    CreateWaterFlow();
    CreateLazyGridLayout();
    CreateContent(30);
    CreateDone();
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 2);
    EXPECT_FALSE(layoutProperty_->GetItemFillPolicy().has_value());
    EXPECT_EQ(layoutProperty_->GetColumnsTemplate().value_or(""), "1fr 1fr");

    /**
     * @tc.steps: step2. Re-set another string template.
     * @tc.expected: fixed lanes follow the string template, no policy involved.
     */
    LazyVGridLayoutModel::SetColumnsTemplate(AceType::RawPtr(frameNode_), "1fr 1fr 1fr 1fr");
    FlushUITasks();
    EXPECT_FALSE(layoutProperty_->GetItemFillPolicy().has_value());
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 4);
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(WIDTH_LG), CalcLength(VIEWPORT_HEIGHT)));
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 4);
}

/**
 * @tc.name: InvalidFillPolicyTest007
 * @tc.desc: AC-9. The dynamic modifier normalizes an out-of-range fillType to BREAKPOINT_DEFAULT (2/3/5).
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, InvalidFillPolicyTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Pass an out-of-range PresetFillType value through the production dynamic modifier.
     * @tc.expected: value is normalized to BREAKPOINT_DEFAULT and renders 2 lanes at SM width.
     */
    CreateWaterFlow();
    CreateLazyGridLayout();
    CreateContent(30);
    CreateDone();
    const std::array<int32_t, 3> invalidFillTypes = { -1, 3, 99 };
    for (const auto invalidFillType : invalidFillTypes) {
        SetLazyGridLayoutItemFillPolicy(reinterpret_cast<_ArkUINode*>(AceType::RawPtr(frameNode_)), invalidFillType);
        FlushUITasks();
        ASSERT_TRUE(layoutProperty_->GetItemFillPolicy().has_value());
        EXPECT_EQ(layoutProperty_->GetItemFillPolicy().value(), PresetFillType::BREAKPOINT_DEFAULT);
        EXPECT_EQ(pattern_->layoutInfo_->lanes_, 2) << "invalidFillType=" << invalidFillType;
    }

    /**
     * @tc.steps: step2. Resize the same layout across MD and LG breakpoints.
     * @tc.expected: normalized DEFAULT policy renders 3 and 5 lanes respectively.
     */
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(WIDTH_MD), CalcLength(VIEWPORT_HEIGHT)));
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 3);
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(WIDTH_LG), CalcLength(VIEWPORT_HEIGHT)));
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 5);

    /**
     * @tc.steps: step3. Apply valid values after invalid values.
     * @tc.expected: The layout recovers through both the string and policy paths.
     */
    LazyVGridLayoutModel::SetColumnsTemplate(AceType::RawPtr(frameNode_), "1fr 1fr 1fr");
    FlushUITasks();
    EXPECT_FALSE(layoutProperty_->GetItemFillPolicy().has_value());
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 3);
    LazyVGridLayoutModel::SetItemFillPolicy(AceType::RawPtr(frameNode_), PresetFillType::BREAKPOINT_SM1MD2LG3);
    FlushUITasks();
    EXPECT_FALSE(layoutProperty_->GetColumnsTemplate().has_value());
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 3);
}

/**
 * @tc.name: StaticColumnsTemplateUnionTest008
 * @tc.desc: AC-4/AC-5. Generated static string and union slots are both registered and handle string templates.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, StaticColumnsTemplateUnionTest008, TestSize.Level1)
{
    CreateWaterFlow();
    CreateLazyGridLayout();
    CreateContent(30);
    CreateDone();

    const auto* modifier = GeneratedModifier::GetLazyVGridLayoutStaticModifier();
    ASSERT_NE(modifier, nullptr);
    ASSERT_NE(modifier->setColumnsTemplate0, nullptr);
    ASSERT_NE(modifier->setColumnsTemplate1, nullptr);
    auto nativeNode = reinterpret_cast<Ark_NativePointer>(AceType::RawPtr(frameNode_));

    /**
     * @tc.steps: step1. Set a fixed template through generated slot 0.
     * @tc.expected: Legacy string behavior remains available and renders four lanes.
     */
    auto stringValue = Converter::ArkValue<Opt_String>("1fr 1fr 1fr 1fr");
    modifier->setColumnsTemplate0(nativeNode, &stringValue);
    FlushUITasks();
    EXPECT_FALSE(layoutProperty_->GetItemFillPolicy().has_value());
    EXPECT_EQ(layoutProperty_->GetColumnsTemplate().value_or(""), "1fr 1fr 1fr 1fr");
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 4);

    /**
     * @tc.steps: step2. Set a string through generated union slot 1.
     * @tc.expected: The string union branch is reachable and renders three lanes.
     */
    auto unionString = Converter::ArkUnion<Opt_Union_String_ItemFillPolicy, Ark_String>("1fr 1fr 1fr");
    modifier->setColumnsTemplate1(nativeNode, &unionString);
    FlushUITasks();
    EXPECT_FALSE(layoutProperty_->GetItemFillPolicy().has_value());
    EXPECT_EQ(layoutProperty_->GetColumnsTemplate().value_or(""), "1fr 1fr 1fr");
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 3);
}

/**
 * @tc.name: StaticColumnsTemplatePolicyRecoveryTest015
 * @tc.desc: AC-4/AC-5/AC-9. The union handles invalid or missing fillType and undefined after a string template.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, StaticColumnsTemplatePolicyRecoveryTest015, TestSize.Level1)
{
    CreateWaterFlow();
    CreateLazyGridLayout();
    CreateContent(30);
    CreateDone();
    const auto* modifier = GeneratedModifier::GetLazyVGridLayoutStaticModifier();
    ASSERT_NE(modifier, nullptr);
    ASSERT_NE(modifier->setColumnsTemplate1, nullptr);
    auto nativeNode = reinterpret_cast<Ark_NativePointer>(AceType::RawPtr(frameNode_));
    auto unionString = Converter::ArkUnion<Opt_Union_String_ItemFillPolicy, Ark_String>("1fr 1fr 1fr");
    modifier->setColumnsTemplate1(nativeNode, &unionString);
    FlushUITasks();

    /**
     * @tc.steps: step1. Set an invalid ItemFillPolicy through generated union slot 1 after a string template.
     * @tc.expected: The value is normalized to DEFAULT and renders 2/3/5 lanes at SM/MD/LG.
     */
    Opt_Union_String_ItemFillPolicy unionPolicy {};
    unionPolicy.tag = INTEROP_TAG_OBJECT;
    unionPolicy.value.selector = 1;
    unionPolicy.value.value1.fillType.tag = INTEROP_TAG_OBJECT;
    const std::array<int32_t, 3> invalidFillTypes = { -1, 3, 99 };
    for (const auto invalidFillType : invalidFillTypes) {
        unionPolicy.value.value1.fillType.value = static_cast<Ark_PresetFillType>(invalidFillType);
        modifier->setColumnsTemplate1(nativeNode, &unionPolicy);
        FlushUITasks();
        ASSERT_TRUE(layoutProperty_->GetItemFillPolicy().has_value());
        EXPECT_EQ(layoutProperty_->GetItemFillPolicy().value(), PresetFillType::BREAKPOINT_DEFAULT);
        EXPECT_EQ(pattern_->layoutInfo_->lanes_, 2) << "invalidFillType=" << invalidFillType;
    }
    unionPolicy.value.value1.fillType.tag = INTEROP_TAG_UNDEFINED;
    modifier->setColumnsTemplate1(nativeNode, &unionPolicy);
    FlushUITasks();
    ASSERT_TRUE(layoutProperty_->GetItemFillPolicy().has_value());
    EXPECT_EQ(layoutProperty_->GetItemFillPolicy().value(), PresetFillType::BREAKPOINT_DEFAULT);
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 2);
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(WIDTH_MD), CalcLength(VIEWPORT_HEIGHT)));
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 3);
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(WIDTH_LG), CalcLength(VIEWPORT_HEIGHT)));
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 5);

    /**
     * @tc.steps: step2. Pass undefined through generated union slot 1.
     * @tc.expected: ItemFillPolicy is cleared and the default single-column template is restored.
     */
    auto undefinedValue = Converter::ArkValue<Opt_Union_String_ItemFillPolicy>();
    modifier->setColumnsTemplate1(nativeNode, &undefinedValue);
    FlushUITasks();
    EXPECT_FALSE(layoutProperty_->GetItemFillPolicy().has_value());
    EXPECT_EQ(layoutProperty_->GetColumnsTemplate().value_or(""), "1fr");
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 1);
}

/**
 * @tc.name: DefaultItemFillPolicyGeometryTest009
 * @tc.desc: AC-2. BREAKPOINT_DEFAULT is a valid public policy and renders the same 2/3/5 mapping as SM2MD3LG5;
 *           child geometry follows the computed lane width and position.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, DefaultItemFillPolicyGeometryTest009, TestSize.Level1)
{
    DensityGuard densityGuard(1.0);
    WidthBreakpointsGuard breakpointsGuard { WidthLayoutBreakPoint() };
    CreateWaterFlow();
    CreateLazyGridLayout();
    CreateContent(30);
    CreateDone();

    LazyVGridLayoutModel::SetItemFillPolicy(AceType::RawPtr(frameNode_), PresetFillType::BREAKPOINT_DEFAULT);
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 2);
    auto firstChild = GetLazyGridChild(frameNode_, 0);
    auto secondChild = GetLazyGridChild(frameNode_, 1);
    ASSERT_NE(firstChild, nullptr);
    ASSERT_NE(secondChild, nullptr);
    EXPECT_NEAR(firstChild->GetGeometryNode()->GetFrameSize().Width(), WIDTH_SM / 2.0f, 0.01f);
    EXPECT_NEAR(secondChild->GetGeometryNode()->GetFrameOffset().GetX(), WIDTH_SM / 2.0f, 0.01f);

    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(WIDTH_MD), CalcLength(VIEWPORT_HEIGHT)));
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 3);
    EXPECT_NEAR(firstChild->GetGeometryNode()->GetFrameSize().Width(), WIDTH_MD / 3.0f, 0.01f);
    EXPECT_NEAR(secondChild->GetGeometryNode()->GetFrameOffset().GetX(), WIDTH_MD / 3.0f, 0.01f);

    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(WIDTH_LG), CalcLength(VIEWPORT_HEIGHT)));
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 5);
    EXPECT_NEAR(firstChild->GetGeometryNode()->GetFrameSize().Width(), WIDTH_LG / 5.0f, 0.01f);
    EXPECT_NEAR(secondChild->GetGeometryNode()->GetFrameOffset().GetX(), WIDTH_LG / 5.0f, 0.01f);
}

/**
 * @tc.name: ExactDefaultBreakpointBoundaryTest010
 * @tc.desc: AC-3. Default density-one boundaries use strict greater-than comparisons: 320/600/840/1440
 *           enter the following WindowSizeType, while only 600 and 840 change the three-band lane mapping.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, ExactDefaultBreakpointBoundaryTest010, TestSize.Level1)
{
    DensityGuard densityGuard(1.0);
    WidthBreakpointsGuard breakpointsGuard { WidthLayoutBreakPoint() };
    CreateWaterFlow();
    CreateLazyGridLayout();
    CreateContent(30);
    CreateDone();
    LazyVGridLayoutModel::SetItemFillPolicy(AceType::RawPtr(frameNode_), PresetFillType::BREAKPOINT_SM1MD2LG3);

    const std::array<std::pair<float, int32_t>, 8> cases = { {
        { 319.0f, 1 },
        { 320.0f, 1 },
        { 599.0f, 1 },
        { 600.0f, 2 },
        { 839.0f, 2 },
        { 840.0f, 3 },
        { 1439.0f, 3 },
        { 1440.0f, 3 },
    } };
    for (const auto& [width, lanes] : cases) {
        layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(width), CalcLength(VIEWPORT_HEIGHT)));
        FlushUITasks();
        EXPECT_EQ(pattern_->layoutInfo_->lanes_, lanes) << "width=" << width;
        EXPECT_NEAR(frameNode_->GetGeometryNode()->GetFrameSize().Width(), width, 0.01f) << "width=" << width;
    }
}

/**
 * @tc.name: DensityScaledBreakpointTest011
 * @tc.desc: AC-3. The shared policy engine multiplies breakpoint thresholds by density while consuming cross size in
 * px.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, DensityScaledBreakpointTest011, TestSize.Level1)
{
    constexpr double testDensity = 2.0;
    WidthBreakpointsGuard breakpointsGuard { WidthLayoutBreakPoint() };
    struct DensityPolicyCase {
        float widthPx;
        const char* sm1;
        const char* defaultPolicy;
        const char* sm2;
    };
    const std::array<DensityPolicyCase, 4> cases = { {
        { 1199.0f, "1fr", "1fr 1fr", "1fr 1fr" },
        { 1200.0f, "1fr 1fr", "1fr 1fr 1fr", "1fr 1fr 1fr" },
        { 1679.0f, "1fr 1fr", "1fr 1fr 1fr", "1fr 1fr 1fr" },
        { 1680.0f, "1fr 1fr 1fr", "1fr 1fr 1fr 1fr 1fr", "1fr 1fr 1fr 1fr 1fr" },
    } };
    for (const auto& policyCase : cases) {
        EXPECT_EQ(BuildItemFillPolicyColumns(PresetFillType::BREAKPOINT_SM1MD2LG3, policyCase.widthPx, testDensity)
                      .value_or(""),
            policyCase.sm1);
        EXPECT_EQ(BuildItemFillPolicyColumns(PresetFillType::BREAKPOINT_DEFAULT, policyCase.widthPx, testDensity)
                      .value_or(""),
            policyCase.defaultPolicy);
        EXPECT_EQ(BuildItemFillPolicyColumns(PresetFillType::BREAKPOINT_SM2MD3LG5, policyCase.widthPx, testDensity)
                      .value_or(""),
            policyCase.sm2);
    }
}

/**
 * @tc.name: SystemCustomBreakpointTest012
 * @tc.desc: AC-3. A valid SystemProperties WidthLayoutBreakPoint replaces the default threshold values.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, SystemCustomBreakpointTest012, TestSize.Level1)
{
    DensityGuard densityGuard(1.0);
    WidthBreakpointsGuard breakpointsGuard { WidthLayoutBreakPoint(100.0, 300.0, 500.0, 700.0) };
    CreateWaterFlow();
    CreateLazyGridLayout();
    CreateContent(30);
    CreateDone();
    LazyVGridLayoutModel::SetItemFillPolicy(AceType::RawPtr(frameNode_), PresetFillType::BREAKPOINT_SM1MD2LG3);

    const std::array<std::pair<float, int32_t>, 8> cases = { {
        { 99.0f, 1 },
        { 100.0f, 1 },
        { 299.0f, 1 },
        { 300.0f, 2 },
        { 499.0f, 2 },
        { 500.0f, 3 },
        { 699.0f, 3 },
        { 700.0f, 3 },
    } };
    for (const auto& [width, lanes] : cases) {
        layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(width), CalcLength(VIEWPORT_HEIGHT)));
        FlushUITasks();
        EXPECT_EQ(pattern_->layoutInfo_->lanes_, lanes) << "width=" << width;
    }
}

/**
 * @tc.name: RepeatedDynamicSwitchAndStringRecoveryTest013
 * @tc.desc: AC-4/AC-5/AC-7. Dynamic Model switching keeps string and ItemFillPolicy mutually exclusive;
 *           empty or invalid strings render one lane and a later valid value recovers.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, RepeatedDynamicSwitchAndStringRecoveryTest013, TestSize.Level1)
{
    DensityGuard densityGuard(1.0);
    WidthBreakpointsGuard breakpointsGuard { WidthLayoutBreakPoint() };
    CreateWaterFlow();
    CreateLazyGridLayout();
    CreateContent(30);
    CreateDone();

    const std::array<std::pair<PresetFillType, int32_t>, 3> policies = { {
        { PresetFillType::BREAKPOINT_DEFAULT, 2 },
        { PresetFillType::BREAKPOINT_SM1MD2LG3, 1 },
        { PresetFillType::BREAKPOINT_SM2MD3LG5, 2 },
    } };
    for (const auto& [policy, lanes] : policies) {
        LazyVGridLayoutModel::SetColumnsTemplate(AceType::RawPtr(frameNode_), "1fr 1fr 1fr");
        FlushUITasks();
        EXPECT_TRUE(layoutProperty_->GetColumnsTemplate().has_value());
        EXPECT_FALSE(layoutProperty_->GetItemFillPolicy().has_value());
        EXPECT_EQ(pattern_->layoutInfo_->lanes_, 3);

        LazyVGridLayoutModel::SetItemFillPolicy(AceType::RawPtr(frameNode_), policy);
        FlushUITasks();
        EXPECT_FALSE(layoutProperty_->GetColumnsTemplate().has_value());
        ASSERT_TRUE(layoutProperty_->GetItemFillPolicy().has_value());
        EXPECT_EQ(layoutProperty_->GetItemFillPolicy().value(), policy);
        EXPECT_EQ(pattern_->layoutInfo_->lanes_, lanes);
    }

    LazyVGridLayoutModel::SetColumnsTemplate(AceType::RawPtr(frameNode_), "invalid-template");
    FlushUITasks();
    EXPECT_FALSE(layoutProperty_->GetItemFillPolicy().has_value());
    EXPECT_EQ(layoutProperty_->GetColumnsTemplate().value_or(""), "invalid-template");
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 1);

    LazyVGridLayoutModel::SetColumnsTemplate(AceType::RawPtr(frameNode_), "1fr 1fr 1fr 1fr");
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 4);

    LazyVGridLayoutModel::SetColumnsTemplate(AceType::RawPtr(frameNode_), "");
    FlushUITasks();
    EXPECT_FALSE(layoutProperty_->GetItemFillPolicy().has_value());
    EXPECT_EQ(layoutProperty_->GetColumnsTemplate().value_or(""), "1fr");
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 1);
}

/**
 * @tc.name: RepeatedStaticAllPoliciesAndUndefinedTest014
 * @tc.desc: AC-4/AC-5/AC-6/AC-11. The public static slots repeatedly switch between string and every valid
 *           ItemFillPolicy, keep the two stored forms mutually exclusive, and finish with undefined reset.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, RepeatedStaticAllPoliciesAndUndefinedTest014, TestSize.Level1)
{
    DensityGuard densityGuard(1.0);
    WidthBreakpointsGuard breakpointsGuard { WidthLayoutBreakPoint() };
    CreateWaterFlow();
    CreateLazyGridLayout();
    CreateContent(30);
    CreateDone();

    const auto* modifier = GeneratedModifier::GetLazyVGridLayoutStaticModifier();
    ASSERT_NE(modifier, nullptr);
    ASSERT_NE(modifier->setColumnsTemplate0, nullptr);
    ASSERT_NE(modifier->setColumnsTemplate1, nullptr);
    auto nativeNode = reinterpret_cast<Ark_NativePointer>(AceType::RawPtr(frameNode_));

    struct StaticPolicyCase {
        Ark_PresetFillType arkPolicy;
        PresetFillType policy;
        int32_t lanes;
    };
    const std::array<StaticPolicyCase, 3> policies = { {
        { ARK_PRESET_FILL_TYPE_BREAKPOINT_DEFAULT, PresetFillType::BREAKPOINT_DEFAULT, 2 },
        { ARK_PRESET_FILL_TYPE_BREAKPOINT_SM1MD2LG3, PresetFillType::BREAKPOINT_SM1MD2LG3, 1 },
        { ARK_PRESET_FILL_TYPE_BREAKPOINT_SM2MD3LG5, PresetFillType::BREAKPOINT_SM2MD3LG5, 2 },
    } };
    for (const auto& policyCase : policies) {
        auto stringValue = Converter::ArkValue<Opt_String>("1fr 1fr 1fr");
        modifier->setColumnsTemplate0(nativeNode, &stringValue);
        FlushUITasks();
        EXPECT_TRUE(layoutProperty_->GetColumnsTemplate().has_value());
        EXPECT_FALSE(layoutProperty_->GetItemFillPolicy().has_value());
        EXPECT_EQ(pattern_->layoutInfo_->lanes_, 3);

        Opt_Union_String_ItemFillPolicy unionPolicy {};
        unionPolicy.tag = INTEROP_TAG_OBJECT;
        unionPolicy.value.selector = 1;
        unionPolicy.value.value1.fillType.tag = INTEROP_TAG_OBJECT;
        unionPolicy.value.value1.fillType.value = policyCase.arkPolicy;
        modifier->setColumnsTemplate1(nativeNode, &unionPolicy);
        FlushUITasks();
        EXPECT_FALSE(layoutProperty_->GetColumnsTemplate().has_value());
        ASSERT_TRUE(layoutProperty_->GetItemFillPolicy().has_value());
        EXPECT_EQ(layoutProperty_->GetItemFillPolicy().value(), policyCase.policy);
        EXPECT_EQ(pattern_->layoutInfo_->lanes_, policyCase.lanes);
    }

    auto undefinedValue = Converter::ArkValue<Opt_Union_String_ItemFillPolicy>();
    modifier->setColumnsTemplate1(nativeNode, &undefinedValue);
    FlushUITasks();
    EXPECT_FALSE(layoutProperty_->GetItemFillPolicy().has_value());
    EXPECT_EQ(layoutProperty_->GetColumnsTemplate().value_or(""), "1fr");
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 1);
}
} // namespace OHOS::Ace::NG
