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
#include <memory>

#include "gtest/gtest.h"

#define private public
#include "base/geometry/offset.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/slider/slider_accessibility_property.h"
#include "core/components_ng/pattern/slider/slider_event_hub.h"
#include "core/components_ng/pattern/slider/slider_layout_algorithm.h"
#include "core/components_ng/pattern/slider/slider_layout_property.h"
#include "core/components_ng/pattern/slider/slider_model_ng.h"
#include "core/components_ng/pattern/slider/slider_paint_method.h"
#include "core/components_ng/pattern/slider/slider_paint_property.h"
#include "core/components_ng/pattern/slider/slider_pattern.h"
#include "core/components_ng/pattern/slider/slider_style.h"
#include "core/components_ng/test/mock/rosen/mock_canvas.h"
#include "core/components_ng/test/mock/rosen/testing_canvas.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr float VALUE = 50.0f;
constexpr float STEP = 10.0f;
constexpr float MIN = 0.0f;
constexpr float MAX = 100.0f;
} // namespace

class SliderPaintMethodTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void SliderPaintMethodTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void SliderPaintMethodTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: SliderPaintMethodTest001
 * @tc.desc: Test Slider PaintMethod GetContentDrawFunction
 * @tc.type: FUNC
 */
HWTEST_F(SliderPaintMethodTestNg, SliderPaintMethodTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sliderPaintProperty.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    SliderPaintMethod::Parameters parameter;
    SliderPaintMethod sliderPaintMethod(parameter);

    /**
     * @tc.steps: step2. get paintwrapper
     * @tc.expected: paintwrapper is not null
     */
    RefPtr<RenderContext> rendercontext;
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto* paintwrapper = new PaintWrapper(rendercontext, geometryNode, sliderPaintProperty);
    EXPECT_NE(paintwrapper, nullptr);
    sliderPaintMethod.GetContentDrawFunction(paintwrapper);
}
} // namespace OHOS::Ace::NG
