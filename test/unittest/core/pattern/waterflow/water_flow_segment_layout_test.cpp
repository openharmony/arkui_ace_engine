/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "test/unittest/core/pattern/waterflow/water_flow_item_maps.h"
#include "test/unittest/core/pattern/waterflow/water_flow_test_ng.h"

#include "core/components_ng/property/measure_property.h"

#define protected public
#define private public
#include "frameworks/core/components_ng/pattern/waterflow/water_flow_segmented_layout.h"
#undef private
#undef protected

namespace OHOS::Ace::NG {
class WaterFlowSegmentTest : public WaterFlowTestNg {};

/**
 * @tc.name: Fill001
 * @tc.desc: Test SegmentedLayout::Fill.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentTest, Fill001, TestSize.Level1)
{
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        CreateItemWithHeight(50.0f);
        CreateItemWithHeight(30.0f);
        CreateItemWithHeight(40.0f);
        CreateItemWithHeight(60.0f);
        CreateItemWithHeight(20.0f);
        CreateItemWithHeight(50.0f);
        CreateItemWithHeight(30.0f);
        CreateItemWithHeight(40.0f);
        CreateItemWithHeight(2.0f);
        CreateItemWithHeight(20.0f);
    });

    auto algo = AceType::MakeRefPtr<WaterFlowSegmentedLayout>(WaterFlowLayoutInfo {});
    algo->wrapper_ = AceType::RawPtr(frameNode_);
    algo->mainSize_ = 2000.0f;
    algo->itemsCrossSize_ = { { 50.0f, 50.0f, 50.0f, 50.0f }, {}, { 70.0f, 70.0f, 70.0f } };
    algo->mainGaps_ = { 5.0f, 0.0f, 1.0f };
    algo->margins_ = { {}, {}, PaddingPropertyF { .top = 5.0f } };

    auto& info = algo->info_;

    info.items_.resize(3);
    for (int i = 0; i < 3; ++i) {
        info.items_[0][i] = {};
        info.items_[2][i] = {};
    }
    info.items_[0][3] = {};

    info.segmentTails_ = SEGMENT_TAILS_1;

    algo->Fill();
    EXPECT_EQ(info.items_, ITEM_MAP_1);
}
} // namespace OHOS::Ace::NG