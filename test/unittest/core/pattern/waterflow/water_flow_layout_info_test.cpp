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

#include "gtest/gtest.h"

#define protected public
#define private public
#include "test/unittest/core/pattern/test_ng.h"
#include "test/unittest/core/pattern/waterflow/water_flow_item_maps.h"

#include "core/components_ng/pattern/waterflow/water_flow_layout_info.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
class WaterFlowLayoutInfoTest : public TestNG {};

/**
 * @tc.name: GetCrossIndexForNextItem001
 * @tc.desc: Test functions in WaterFlowLayoutInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowLayoutInfoTest, GetCrossIndexForNextItem001, TestSize.Level1)
{
    WaterFlowLayoutInfo info;
    info.items_ = ITEM_MAP_1;

    auto res = info.GetCrossIndexForNextItem(0);
    EXPECT_EQ(res.crossIndex, 1);
    EXPECT_EQ(res.lastItemIndex, 1);

    res = info.GetCrossIndexForNextItem(1);
    EXPECT_EQ(res.crossIndex, 0);
    EXPECT_EQ(res.lastItemIndex, -1);

    res = info.GetCrossIndexForNextItem(2);
    EXPECT_EQ(res.crossIndex, 1);
    EXPECT_EQ(res.lastItemIndex, 5);
}
} // namespace OHOS::Ace::NG