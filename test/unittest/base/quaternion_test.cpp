/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include <cmath>

#include "gtest/gtest.h"

#include "base/geometry/quaternion.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
const double NUM_D1 = 1.0;
const double NUM_D2 = 0.2;
const double NUM_D3 = std::sin(std::acos(0.8)) / 3;
} // namespace

class QuaternionTest : public testing::Test {};

/**
 * @tc.name: QuaternionTest001
 * @tc.desc: Test all functions of the class Quaternion.
 * @tc.type: FUNC
 */
HWTEST_F(QuaternionTest, QuaternionTest001, TestSize.Level1)
{
    Quaternion quaternion1;
    quaternion1.SetX(NUM_D1);
    quaternion1.SetY(NUM_D1);
    quaternion1.SetZ(NUM_D1);
    quaternion1.SetW(NUM_D1);
    EXPECT_DOUBLE_EQ(quaternion1.GetX(), NUM_D1);
    EXPECT_DOUBLE_EQ(quaternion1.GetY(), NUM_D1);
    EXPECT_DOUBLE_EQ(quaternion1.GetZ(), NUM_D1);
    EXPECT_DOUBLE_EQ(quaternion1.GetW(), NUM_D1);

    Quaternion quaternion2 = quaternion1.inverse();
    EXPECT_DOUBLE_EQ(quaternion2.GetX(), -NUM_D1);
    EXPECT_DOUBLE_EQ(quaternion2.GetY(), -NUM_D1);
    EXPECT_DOUBLE_EQ(quaternion2.GetZ(), -NUM_D1);
    EXPECT_DOUBLE_EQ(quaternion2.GetW(), NUM_D1);

    Quaternion quaternion3 = quaternion1.Slerp(quaternion2, -1.0);
    EXPECT_DOUBLE_EQ(quaternion3.GetX(), NUM_D1);
    EXPECT_DOUBLE_EQ(quaternion3.GetY(), NUM_D1);
    EXPECT_DOUBLE_EQ(quaternion3.GetZ(), NUM_D1);
    EXPECT_DOUBLE_EQ(quaternion3.GetW(), NUM_D1);

    Quaternion quaternion4 = quaternion1.Slerp(quaternion2, 2.0);
    EXPECT_DOUBLE_EQ(quaternion4.GetX(), NUM_D1);
    EXPECT_DOUBLE_EQ(quaternion4.GetY(), NUM_D1);
    EXPECT_DOUBLE_EQ(quaternion4.GetZ(), NUM_D1);
    EXPECT_DOUBLE_EQ(quaternion4.GetW(), NUM_D1);

    quaternion2.SetW(-NUM_D1);
    Quaternion quaternion5 = quaternion1.Slerp(quaternion2, 1.0);
    EXPECT_DOUBLE_EQ(quaternion5.GetX(), NUM_D1);
    EXPECT_DOUBLE_EQ(quaternion5.GetY(), NUM_D1);
    EXPECT_DOUBLE_EQ(quaternion5.GetZ(), NUM_D1);
    EXPECT_DOUBLE_EQ(quaternion5.GetW(), NUM_D1);

    Quaternion quaternion6(NUM_D2, NUM_D2, NUM_D2, NUM_D2);
    Quaternion quaternion7 = quaternion1.Slerp(quaternion6, 1.0);
    EXPECT_DOUBLE_EQ(quaternion7.GetX(), NUM_D3);
    EXPECT_DOUBLE_EQ(quaternion7.GetY(), NUM_D3);
    EXPECT_DOUBLE_EQ(quaternion7.GetZ(), NUM_D3);
    EXPECT_DOUBLE_EQ(quaternion7.GetW(), NUM_D3);
}
} // namespace OHOS::Ace
