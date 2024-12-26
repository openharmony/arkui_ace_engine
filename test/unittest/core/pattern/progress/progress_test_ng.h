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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_PROGRESS_PROGRESS_TEST_NG_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_PROGRESS_PROGRESS_TEST_NG_H

#include <cmath>
#include <cstddef>
#include <memory>
#include <optional>
#include <vector>

#include "gtest/gtest.h"

#include "base/memory/referenced.h"
#define private public
#define protected public

#include "test/mock/base/mock_task_executor.h"

#include "base/memory/ace_type.h"
#include "core/components/progress/progress_theme.h"
#include "core/components/theme/app_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/progress/progress_layout_algorithm.h"
#include "core/components_ng/pattern/progress/progress_layout_property.h"
#include "core/components_ng/pattern/progress/progress_model_ng.h"
#include "core/components_ng/pattern/progress/progress_paint_property.h"
#include "core/components_ng/pattern/progress/progress_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/progress_mask_property.h"
#include "core/components_ng/render/render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/test_ng.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
const InspectorFilter filter;
constexpr double MAX_VALUE_OF_PROGRESS = 120.0;
constexpr double PROGRESS_MODEL_NG_CACHEDVALUE = 10.0;
constexpr double PROGRESS_MODEL_NG_MAX = 20.0;
constexpr double PROGRESS_MODEL_NG_MIN = 5.0;
constexpr double PROGRESS_MODEL_NG_VALUE = 10.0;
constexpr double VALUE_OF_PROGRESS = 20.0;
constexpr double VALUE_OF_PROGRESS_2 = 40.0;
constexpr ProgressType PROGRESS_TYPE_LINEAR = ProgressType::LINEAR;
constexpr ProgressType PROGRESS_TYPE_RING = ProgressType::RING;
constexpr ProgressType PROGRESS_TYPE_SCALE = ProgressType::SCALE;
constexpr ProgressType PROGRESS_TYPE_MOON = ProgressType::MOON;
constexpr ProgressType PROGRESS_TYPE_CAPSULE = ProgressType::CAPSULE;
constexpr ProgressType PROGRESS_TYPE_CIRCLE = ProgressType::CIRCLE;
constexpr Dimension STROKE_WIDTH = 10.0_vp;
constexpr Dimension LARG_STROKE_WIDTH = 500.0_vp;
constexpr Dimension SCALE_WIDTH = 10.0_vp;
constexpr int32_t SCALE_COUNT = 120;
constexpr int32_t TYPE_OF_PROGRESS = 5;
constexpr Color FRONT_COLOR = Color(0xff0000ff);
constexpr Color BG_COLOR = Color(0xffc0c0c0);
constexpr Color BORDER_COLOR = Color(0xffc0c0c0);
constexpr float PROGRESS_COMPONENT_MAXSIZE_WIDTH = 720.0f;
constexpr float PROGRESS_COMPONENT_MAXSIZE_HEIGHT = 1400.0f;
constexpr float PROGRESS_COMPONENT_WIDTH = 200.0f;
constexpr float LARG_PROGRESS_COMPONENT_WIDTH = 2000.0f;
constexpr float PROGRESS_COMPONENT_HEIGHT = 200.0f;
constexpr float LARG_PROGRESS_COMPONENT_HEIGHT = 2000.0f;
constexpr float PROGRESS_STROKE_WIDTH = 10.0f;
constexpr float PROGRESS_LARGE_STROKE_WIDTH = 200.0f;
constexpr float PROGRESS_MODIFIER_VALUE = 100.0f;
constexpr float PROGRESS_MODIFIER_LARGE_VALUE = 200.0f;
constexpr float PROGRESS_MODIFIER_MAX_VALUE = 10000.0f;
constexpr float CONTEXT_WIDTH = 100.0f;
constexpr float CONTEXT_HEIGHT = 100.0f;
constexpr float CONTEXT_LARGE_HEIGHT = 200.0f;
constexpr float CONTEXT_HUGE_WIDTH = 20000.0f;
constexpr float CONTEXT_HUGE_HEIGHT = 20000.0f;
constexpr Dimension DEFAULT_RING_DIAMETER = 72.0_vp;
constexpr Dimension DEFAULT_CAPSULE_WIDTH = 28.0_vp;
constexpr Dimension TEST_PROGRESS_THICKNESS = 4.0_vp;
constexpr Dimension TEST_PROGRESS_STROKE_WIDTH = 10.0_vp;
constexpr Dimension TEST_PROGRESS_DEFAULT_DIAMETER = 72.0_vp;
constexpr Dimension TEST_PROGRESS_SCALE_WIDTH = 2.0_vp;
constexpr Dimension DEFAULT_STROKE_WIDTH = 2.0_vp;
const Color TEST_COLOR = Color::BLUE;
const LinearColor TEST_LINEARCOLOR = LinearColor(TEST_COLOR);
constexpr float VALUE_OF_SET_VALUE = 10.0f;
const std::vector<std::string> FONT_FAMILY = { "serif" };
constexpr Dimension DEFAULT_SPACE = 3.0_vp;

class ProgressTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetProgress();
    ProgressModelNG CreateProgress(double value, double max, NG::ProgressType type);
    RefPtr<ProgressModifier> CreateProgressModifier();

    RefPtr<FrameNode> frameNode_;
    RefPtr<ProgressPattern> pattern_;
    RefPtr<EventHub> eventHub_;
    RefPtr<ProgressLayoutProperty> layoutProperty_;
    RefPtr<ProgressPaintProperty> paintProperty_;
    RefPtr<ProgressAccessibilityProperty> accessibilityProperty_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_PROGRESS_PROGRESS_TEST_NG_H