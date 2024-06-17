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
#include "test/unittest/core/pattern/test_ng.h"
#include "water_flow_item_maps.h"

#include "frameworks/core/components_ng/pattern/waterflow/water_flow_sections.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

class WaterFlowSectionTest : public TestNG {};

/**
 * @tc.name: Update001
 * @tc.desc: Test Update
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSectionTest, Update001, TestSize.Level1)
{
    WaterFlowSections s;
    int32_t startIdx = -1;
    s.SetOnDataChange([&startIdx](int32_t start) { startIdx = start; });
    s.ChangeData(0, 0, SECTION_5);
    EXPECT_EQ(startIdx, 0);

    // update with the same data, should do nothing
    s.ChangeData(0, 5, SECTION_5);
    EXPECT_EQ(startIdx, 5);

    auto newSection = SECTION_5;
    newSection[3].itemsCount = 100;
    s.ChangeData(0, 5, newSection);
    EXPECT_EQ(startIdx, 4);

    // replace last section. item count update can be skipped
    newSection[4].itemsCount = 10;
    s.ChangeData(4, 1, { newSection[4] });
    EXPECT_EQ(startIdx, 5);

    // updating other properties can't be skipped
    newSection[4].crossCount = 3;
    s.ChangeData(4, 1, { newSection[4] });
    EXPECT_EQ(startIdx, 4);
}
} // namespace OHOS::Ace::NG
