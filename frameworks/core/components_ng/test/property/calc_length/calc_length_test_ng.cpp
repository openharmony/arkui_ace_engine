/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#define private public
#define protected public
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "frameworks/core/components_ng/property/calc_length.h"


using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr double VP_SCALE = 10.0;
constexpr double FP_SCALE = 10.0;
constexpr double LPX_SCALE = 10.0;
constexpr double PARENT_LENGTH = 10.0;
} // namespace

class CalcLengthTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: CalcLengthTestTest001
 * @tc.desc: NormalizeToPx method test
 * @tc.type: FUNC
 */
HWTEST_F(CalcLengthTestNg, calcLengthTest001, TestSize.Level1)
{
    CalcLength calc;
    double result = 0.0;

    /**
     * @tc.steps: step1. When the unit of member variable size is px.
     * @tc.expected: step1. The return value of the NormalizeToPx method is true.
     */
    calc.dimension_ = Dimension(100.0, DimensionUnit::PX);
    auto calcBool = calc.NormalizeToPx(VP_SCALE, FP_SCALE, LPX_SCALE, PARENT_LENGTH, result);
    EXPECT_TRUE(calcBool);
    calc.SetCalcValue("calcLengthTest");
    calcBool = calc.NormalizeToPx(VP_SCALE, FP_SCALE, LPX_SCALE, PARENT_LENGTH, result);
    EXPECT_TRUE(calcBool);

    /**
     * @tc.steps: step1. When the unit of member variable size is vp.
     * @tc.expected: step1. The return value of the NormalizeToPx method is true.
     */
    calc.dimension_ = Dimension(100.0, DimensionUnit::VP);
    calc.NormalizeToPx(VP_SCALE, FP_SCALE, LPX_SCALE, PARENT_LENGTH, result);
    EXPECT_TRUE(calcBool);
}
} // namespace OHOS::Ace::NG