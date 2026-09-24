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

#include "gtest/gtest.h"

#include "base/geometry/least_square_impl.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
const double NUM_D1 = 1.0;
const double NUM_D2 = 0.2;
const int32_t PARAMS_NUM1 = 1;
const int32_t PARAMS_NUM2 = 2;
const int32_t PARAMS_NUM3 = 3;
const int32_t PARAMS_NUM4 = 4;
} // namespace

class LeastSquareImplTest : public testing::Test {};

/**
 * @tc.name: LeastSquareImplTest001
 * @tc.desc: Test all functions of the class LeastSquareImpl.
 * @tc.type: FUNC
 */
HWTEST_F(LeastSquareImplTest, LeastSquareImplTest001, TestSize.Level1)
{
    LeastSquareImpl leastSquareImpl1(PARAMS_NUM1);
    std::vector<double> params;
    EXPECT_FALSE(leastSquareImpl1.GetLeastSquareParams(params));
    EXPECT_TRUE(params.empty());

    params.clear();
    LeastSquareImpl leastSquareImpl2(PARAMS_NUM2);
    leastSquareImpl2.UpdatePoint(NUM_D1, NUM_D2);
    leastSquareImpl2.UpdatePoint(NUM_D1, NUM_D2);
    EXPECT_FALSE(leastSquareImpl2.GetLeastSquareParams(params));

    params.clear();
    LeastSquareImpl leastSquareImpl3(PARAMS_NUM3);
    leastSquareImpl3.UpdatePoint(NUM_D1, NUM_D2);
    leastSquareImpl3.UpdatePoint(NUM_D1, NUM_D2);
    leastSquareImpl3.UpdatePoint(NUM_D1, NUM_D2);
    EXPECT_FALSE(leastSquareImpl3.GetLeastSquareParams(params));

    params.clear();
    LeastSquareImpl leastSquareImpl4(PARAMS_NUM4);
    leastSquareImpl4.UpdatePoint(NUM_D1, NUM_D2);
    leastSquareImpl4.UpdatePoint(NUM_D1, NUM_D2);
    leastSquareImpl4.UpdatePoint(NUM_D1, NUM_D2);
    leastSquareImpl4.UpdatePoint(NUM_D1, NUM_D2);
    EXPECT_TRUE(leastSquareImpl4.GetLeastSquareParams(params));
    // In the second call, the function is not calculated and returns directly.
    EXPECT_TRUE(leastSquareImpl4.GetLeastSquareParams(params));
}

/**
 * @tc.name: LeastSquareImplTest002
 * @tc.desc: Test ResetValsFromRaw of the class LeastSquareImpl.
 * @tc.type: FUNC
 */
HWTEST_F(LeastSquareImplTest, LeastSquareImplTest002, TestSize.Level1)
{
    LeastSquareImpl leastSquareImpl1(PARAMS_NUM1);
    std::vector<double> params;
    EXPECT_FALSE(leastSquareImpl1.GetLeastSquareParams(params));
    EXPECT_TRUE(params.empty());

    params.clear();
    LeastSquareImpl leastSquareImpl2(PARAMS_NUM2);
    leastSquareImpl2.UpdatePoint(NUM_D1, NUM_D2);
    leastSquareImpl2.UpdatePoint(NUM_D1, NUM_D2);
    LeastSquareImpl leastSquareImpl3(PARAMS_NUM3);
    leastSquareImpl3.ResetValsFromRaw(leastSquareImpl2, 2);
    EXPECT_FALSE(leastSquareImpl3.GetLeastSquareParams(params));
}

HWTEST_F(LeastSquareImplTest, LeastSquareImplTest003, TestSize.Level1)
{
    const int32_t countNum = 5;
    LeastSquareImpl impl(PARAMS_NUM3, countNum);
    for (int32_t i = 0; i < countNum * 2 + 1; ++i) {
        impl.UpdatePoint(static_cast<double>(i), static_cast<double>(i * 2));
    }
    EXPECT_EQ(impl.GetTrackNum(), countNum);
    const auto& xVals = impl.GetXVals();
    const auto& yVals = impl.GetYVals();
    EXPECT_DOUBLE_EQ(xVals.front(), static_cast<double>(countNum + 1));
    EXPECT_DOUBLE_EQ(yVals.front(), static_cast<double>((countNum + 1) * 2));
    EXPECT_DOUBLE_EQ(xVals.back(), static_cast<double>(countNum * 2));
    EXPECT_DOUBLE_EQ(yVals.back(), static_cast<double>(countNum * 2 * 2));
}

HWTEST_F(LeastSquareImplTest, LeastSquareImplTest004, TestSize.Level1)
{
    LeastSquareImpl impl(PARAMS_NUM3, 0);
    for (int32_t i = 0; i < 10; ++i) {
        impl.UpdatePoint(static_cast<double>(i), static_cast<double>(i));
    }
    EXPECT_EQ(impl.GetTrackNum(), 10);
}

HWTEST_F(LeastSquareImplTest, LeastSquareImplTest005, TestSize.Level1)
{
    LeastSquareImpl impl(PARAMS_NUM3, -1);
    for (int32_t i = 0; i < 10; ++i) {
        impl.UpdatePoint(static_cast<double>(i), static_cast<double>(i));
    }
    EXPECT_EQ(impl.GetTrackNum(), 10);
}
} // namespace OHOS::Ace
