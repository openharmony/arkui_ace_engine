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
} // namespace OHOS::Ace::NG