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

#define private public
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/gauge/gauge_model_ng.h"
#include "core/components_ng/pattern/gauge/gauge_paint_method.h"
#include "core/components_ng/pattern/gauge/gauge_paint_property.h"
#include "core/components_ng/pattern/gauge/gauge_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr float START = 20.0f;
constexpr float LESS_START = 5.0f;
constexpr float INTERVAL = 30.0f;
constexpr float LESS_INTERVAL = -15.0f;
constexpr float PERCENT = 10.0f;

} // namespace
class GaugePaintMethodTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: GaugePaintMethodTest001
 * @tc.desc: Test Gauge PaintMethod ShouldHighLight
 * @tc.type: FUNC
 */
HWTEST_F(GaugePaintMethodTestNg, GaugePaintPropertyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create gaugePaintProperty.
     */
    GaugePaintMethod gaugePaintMethod;

    /**
     * @tc.steps: step2. test ShouldHighLight in different cases
     * @tc.expected: the result of ShouldHighLight is correct.
     */

    /**
    //     case1 : percent is LessOrEqual than start and LessOrEqual start + interval
    */
    float start = START;
    float interval = INTERVAL;
    float percent = PERCENT;
    bool result = gaugePaintMethod.ShouldHighLight(start, interval, percent);
    EXPECT_FALSE(result);

    /**
    //     case2 : percent is LessOrEqual than start and GreatOrEqual than start + interval
    */
    start = START;
    interval = LESS_INTERVAL;
    percent = PERCENT;
    result = gaugePaintMethod.ShouldHighLight(start, interval, percent);
    EXPECT_FALSE(result);

    /**
    //     case3 : percent is GreatOrEqual than start and GreatOrEqual than start + interval
    */
    start = LESS_START;
    interval = LESS_INTERVAL;
    percent = PERCENT;
    result = gaugePaintMethod.ShouldHighLight(start, interval, percent);
    EXPECT_FALSE(result);

    /**
    //     case4 : percent is GreatOrEqual than start and LessOrEqual than start + interval
    */
    start = LESS_START;
    interval = INTERVAL;
    percent = PERCENT;
    result = gaugePaintMethod.ShouldHighLight(start, interval, percent);
    EXPECT_TRUE(result);
}

} // namespace OHOS::Ace::NG