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

#include <memory>
#include <limits>

#include "gtest/gtest.h"
#include "ui/base/geometry/ng/size_t.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class SizeTTest : public testing::Test {};

/**
 * @tc.name: SizeT_ToString_Normal_Case
 * @tc.desc: Test the function ToString of the class SizeT.
 * @tc.type: FUNC
 */
HWTEST_F(SizeTTest, SizeT_ToString_Normal_Case, TestSize.Level1)
{
    SizeT<double> sizeD(10.5, 20.75);
    std::string expected = "[10.50 x 20.75]";
    EXPECT_EQ(sizeD.ToString(), expected);
}

/**
 * @tc.name: SizeT_ToString_Boundary_Case_With_Zero
 * @tc.desc: Test the function ToString of the class SizeT.
 * @tc.type: FUNC
 */
HWTEST_F(SizeTTest, SizeT_ToString_Boundary_Case_With_Zero, TestSize.Level1)
{
    SizeT<double> sizeD(0, 20.75);
    std::string expected = "[0.00 x 20.75]";
    EXPECT_EQ(sizeD.ToString(), expected);

    sizeD = SizeT<double>(10.5, 0);
    expected = "[10.50 x 0.00]";
    EXPECT_EQ(sizeD.ToString(), expected);

    sizeD = SizeT<double>(0, 0);
    expected = "[0.00 x 0.00]";
    EXPECT_EQ(sizeD.ToString(), expected);
}

/**
 * @tc.name: SizeT_ToString_Boundary_Case_With_Nan_And_Inf
 * @tc.desc: Test the function ToString of the class SizeT.
 * @tc.type: FUNC
 */
HWTEST_F(SizeTTest, SizeT_ToString_Boundary_Case_With_Nan_And_Inf, TestSize.Level1)
{
    SizeT<double> sizeD(std::numeric_limits<double>::infinity(), 20.75);
    std::string expected = "[inf x 20.75]";
    EXPECT_EQ(sizeD.ToString(), expected);

    sizeD = SizeT<double>(10.5, -std::numeric_limits<double>::infinity());
    expected = "[10.50 x -inf]";
    EXPECT_EQ(sizeD.ToString(), expected);

    sizeD = SizeT<double>(std::numeric_limits<double>::quiet_NaN(), -std::numeric_limits<double>::quiet_NaN());
    expected = "[nan x -nan]";
    EXPECT_EQ(sizeD.ToString(), expected);
}

} // namespace OHOS::Ace
