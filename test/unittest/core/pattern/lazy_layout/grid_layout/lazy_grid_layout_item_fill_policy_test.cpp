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

#include "lazy_grid_layout_test.h"

#include "core/components_ng/pattern/lazy_grid_layout/lazy_grid_layout_model.h"
#include "core/components_ng/pattern/lazy_grid_layout/lazy_grid_layout_model_static.h"
#include "core/components_ng/pattern/lazy_grid_layout/lazy_grid_layout_property.h"

namespace OHOS::Ace::NG {
namespace {
// Width breakpoints (vp, density 1.0 in host tests): SM < 600, MD [600, 840), LG >= 840.
constexpr float WIDTH_SM = 200.0f;
constexpr float WIDTH_MD = 700.0f;
constexpr float WIDTH_LG = 1000.0f;
constexpr float VIEWPORT_HEIGHT = 450.0f;
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

    /**
     * @tc.steps: step2. Resize container to MD width.
     * @tc.expected: lanes re-measured to 2.
     */
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(WIDTH_MD), CalcLength(VIEWPORT_HEIGHT)));
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 2);

    /**
     * @tc.steps: step3. Resize container to LG width.
     * @tc.expected: lanes re-measured to 3.
     */
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(WIDTH_LG), CalcLength(VIEWPORT_HEIGHT)));
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 3);

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
    LazyVGridLayoutModel::SetItemFillPolicy(AceType::RawPtr(frameNode_), PresetFillType::BREAKPOINT_SM2MD3LG5);
    FlushUITasks();
    EXPECT_TRUE(layoutProperty_->GetItemFillPolicy().has_value());

    /**
     * @tc.steps: step2. Reset ItemFillPolicy (static side nullopt path).
     * @tc.expected: policy cleared, default single column restored.
     */
    LazyVGridLayoutModelStatic::SetItemFillPolicy(AceType::RawPtr(frameNode_), std::nullopt);
    FlushUITasks();
    EXPECT_FALSE(layoutProperty_->GetItemFillPolicy().has_value());
    EXPECT_FALSE(layoutProperty_->GetColumnsTemplate().has_value());
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 1);

    /**
     * @tc.steps: step3. Set ItemFillPolicy again via the static model, then reset via the dynamic model.
     * @tc.expected: static set applies (2 lanes at SM), dynamic reset clears it again.
     */
    LazyVGridLayoutModelStatic::SetItemFillPolicy(
        AceType::RawPtr(frameNode_), std::optional<PresetFillType>(PresetFillType::BREAKPOINT_SM2MD3LG5));
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 2);
    LazyVGridLayoutModel::ResetItemFillPolicy(AceType::RawPtr(frameNode_));
    FlushUITasks();
    EXPECT_FALSE(layoutProperty_->GetItemFillPolicy().has_value());
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
 * @tc.desc: AC-9. An out-of-range fillType value must not crash; layout still measures.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, InvalidFillPolicyTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set an out-of-range PresetFillType value directly (bypassing bridge validation).
     * @tc.expected: no crash, layout completes (engine falls back to the non-SM1MD2LG3 branch).
     */
    CreateWaterFlow();
    CreateLazyGridLayout();
    CreateContent(30);
    CreateDone();
    constexpr int32_t INVALID_FILL_TYPE = 99;
    LazyVGridLayoutModel::SetItemFillPolicy(
        AceType::RawPtr(frameNode_), static_cast<PresetFillType>(INVALID_FILL_TYPE));
    FlushUITasks();
    EXPECT_TRUE(layoutProperty_->GetItemFillPolicy().has_value());
    EXPECT_GT(pattern_->layoutInfo_->lanes_, 0);
    EXPECT_GE(pattern_->layoutInfo_->endIndex_, pattern_->layoutInfo_->startIndex_);
}
} // namespace OHOS::Ace::NG
