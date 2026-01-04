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

#include "water_flow_test_ng.h"

#include "core/components_ng/pattern/waterflow/water_flow_model_static.h"

namespace OHOS::Ace::NG {

class WaterFlowStaticTest : public WaterFlowTestNg {};

/**
 * @tc.name: SetColumnsTemplate
 * @tc.desc: Test SetColumnsTemplate
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowStaticTest, SetColumnsTemplate, TestSize.Level1)
{
    CreateWaterFlow();
    std::optional<std::string> columnsTemplate = "1fr";
    WaterFlowModelStatic::SetColumnsTemplate(AceType::RawPtr(frameNode_), columnsTemplate);
    ASSERT_NE(layoutProperty_, nullptr);
    auto ret = layoutProperty_->GetColumnsTemplateValue("");
    EXPECT_EQ(ret, columnsTemplate.value());

    columnsTemplate.reset();
    WaterFlowModelStatic::SetColumnsTemplate(AceType::RawPtr(frameNode_), columnsTemplate);
    EXPECT_FALSE(layoutProperty_->GetColumnsTemplate().has_value());
}


/**
 * @tc.name: SetRowsTemplate
 * @tc.desc: Test SetRowsTemplate
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowStaticTest, SetRowsTemplate, TestSize.Level1)
{
    CreateWaterFlow();
    std::optional<std::string> rowsTemplate = "1fr";
    WaterFlowModelStatic::SetRowsTemplate(AceType::RawPtr(frameNode_), rowsTemplate);
    ASSERT_NE(layoutProperty_, nullptr);
    auto ret = layoutProperty_->GetRowsTemplateValue("");
    EXPECT_EQ(ret, rowsTemplate.value());

    rowsTemplate.reset();
    WaterFlowModelStatic::SetRowsTemplate(AceType::RawPtr(frameNode_), rowsTemplate);
    EXPECT_FALSE(layoutProperty_->GetRowsTemplate().has_value());
}

/**
 * @tc.name: ResetItemLayoutConstraint
 * @tc.desc: Test ResetItemLayoutConstraint function when undefined is passed
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, ResetItemLayoutConstraint, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create waterFlow and set initial constraints
     */
    WaterFlowModelNG model;
    model.Create();
    ViewAbstract::SetWidth(CalcLength(WATER_FLOW_WIDTH));
    ViewAbstract::SetHeight(CalcLength(WATER_FLOW_HEIGHT));
    model.SetScroller(model.CreateScrollController(), model.CreateScrollBarProxy());
    GetWaterFlow();
    CreateWaterFlowItems(TOTAL_LINE_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step2. Set valid constraints first
     * @tc.expected: Constraints should be applied
     */
    model.SetItemMinWidth(AceType::RawPtr(frameNode_), Dimension(100.f));
    model.SetItemMaxWidth(AceType::RawPtr(frameNode_), Dimension(200.f));
    model.SetItemMinHeight(AceType::RawPtr(frameNode_), Dimension(50.f));
    model.SetItemMaxHeight(AceType::RawPtr(frameNode_), Dimension(150.f));
    FlushUITasks();

    EXPECT_TRUE(layoutProperty_->HasItemLayoutConstraint());
    EXPECT_EQ(model.GetItemMinWidth(AceType::RawPtr(frameNode_)), Dimension(100.f));
    EXPECT_EQ(model.GetItemMaxWidth(AceType::RawPtr(frameNode_)), Dimension(200.f));

    /**
     * @tc.steps: step3. Call ResetItemLayoutConstraint
     * @tc.expected: All constraints should be cleared
     */
    WaterFlowModelStatic::ResetItemLayoutConstraint(AceType::RawPtr(frameNode_));
    FlushUITasks();

    EXPECT_FALSE(layoutProperty_->HasItemLayoutConstraint());
}
} // namespace OHOS::Ace::NG