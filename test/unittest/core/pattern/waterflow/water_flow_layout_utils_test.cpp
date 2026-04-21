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

#include "test/unittest/core/pattern/scrollable/scrollable_utils_test_ng.h"
#include "water_flow_test_ng.h"
#include "core/components_ng/pattern/waterflow/layout/water_flow_layout_utils.h"
#define protected public
#define private public

namespace OHOS::Ace::NG {
class WaterFlowLayoutUtilsTest : public WaterFlowTestNg {};
/**
 * @tc.name: WaterFlowLazyEmptyBranchTest001
 * @tc.desc: Test when waterFlow get empty child from LazyForEach
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowLayoutUtilsTest, LazyEmptyBranchTest001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    auto wrapper0 = WaterFlowLayoutUtils::GetWaterFlowItem(AceType::RawPtr(frameNode_), 0);
    EXPECT_EQ(wrapper0, nullptr);

    model.SetSupportLazyLoadingEmptyBranch(true);
    auto layoutProperty = frameNode_->GetLayoutProperty<WaterFlowLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetSupportLazyLoadingEmptyBranch().value_or(false), true);

    auto wrapper1 = WaterFlowLayoutUtils::GetWaterFlowItem(AceType::RawPtr(frameNode_), 0);
    EXPECT_NE(wrapper1, nullptr);
}
} // namespace OHOS::Ace::NG
