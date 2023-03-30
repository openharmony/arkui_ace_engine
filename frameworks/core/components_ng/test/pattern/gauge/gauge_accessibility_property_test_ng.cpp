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

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/gauge/gauge_accessibility_property.h"
#include "core/components_ng/pattern/gauge/gauge_model_ng.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr float VALUE = 50.0f;
constexpr float MAX = 100.0f;
constexpr float MIN = 0.0f;
} // namespace

class GaugeAccessibilityPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void GaugeAccessibilityPropertyTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void GaugeAccessibilityPropertyTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: GaugeAccessibilityPropertyTestNg001
 * @tc.desc: Test the HasRange and RangeInfo properties of Gauge
 * @tc.type: FUNC
 */
HWTEST_F(GaugeAccessibilityPropertyTestNg, GaugeAccessibilityPropertyTestNg001, TestSize.Level1)
{
    GaugeModelNG gauge;
    gauge.Create(VALUE, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto gaugeAccessibilityProperty = frameNode->GetAccessibilityProperty<GaugeAccessibilityProperty>();
    ASSERT_NE(gaugeAccessibilityProperty, nullptr);
    EXPECT_TRUE(gaugeAccessibilityProperty->HasRange());
    EXPECT_EQ(gaugeAccessibilityProperty->GetAccessibilityValue().current, VALUE);
    EXPECT_EQ(gaugeAccessibilityProperty->GetAccessibilityValue().max, MAX);
    EXPECT_EQ(gaugeAccessibilityProperty->GetAccessibilityValue().min, MIN);
}

/**
 * @tc.name: GaugeAccessibilityPropertyTestNg002
 * @tc.desc: Test the Text property of Gauge
 * @tc.type: FUNC
 */
HWTEST_F(GaugeAccessibilityPropertyTestNg, GaugeAccessibilityPropertyTestNg002, TestSize.Level1)
{
    GaugeModelNG gauge;
    gauge.Create(VALUE, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto gaugeAccessibilityProperty = frameNode->GetAccessibilityProperty<GaugeAccessibilityProperty>();
    ASSERT_NE(gaugeAccessibilityProperty, nullptr);
    EXPECT_EQ(gaugeAccessibilityProperty->GetText(), std::to_string(VALUE));
}
} // namespace OHOS::Ace::NG
