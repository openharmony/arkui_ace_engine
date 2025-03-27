/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/progress/progress_theme_wrapper.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/progress_mask_property.h"
#include "core/components_ng/render/render_context.h"
#include "core/components_ng/token_theme/token_theme_storage.h"
#include "core/interfaces/arkoala/arkoala_api.h"
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
constexpr bool ACTIVE_SETTING_FALSE = false;
constexpr uint32_t TOKEN_THEME_ID = 10001;

struct TestProperty {
    const ArkUI_Uint32 colors_[TokenColors::TOTAL_NUMBER] = {
        // id for color value for test
        125830976, /* BRAND = 0 */
        125830979, /* WARNING = 1; */
        125830980, /* ALERT = 2 */
        125830981, /* CONFIRM = 3 */
        125830982, /* FONT_PRIMARY = 4 */
        125830983, /* FONT_SECONDARY = 5 */
        125830984, /* FONT_TERTIARY = 6 */
        125830985, /* FONT_FOURTH = 7 */
        125830986, /* FONT_EMPHASIZE = 8 */
        125830987, /* FONT_ON_PRIMARY = 9 */
        125830988, /* FONT_ON_SECONDARY = 10 */
        125830989, /* FONT_ON_TERTIARY = 11 */
        125830990, /* FONT_ON_FOURTH = 12 */
        125830991, /* ICON_PRIMARY = 13 */
        125830992, /* ICON_SECONDARY = 14 */
        125830993, /* ICON_TERTIARY = 15 */
        125830994, /* ICON_FOURTH = 16 */
        125830995, /* ICON_EMPHASIZE = 17 */
        125830996, /* ICON_SUB_EMPHASIZE = 18 */
        125831057, /* ICON_ON_PRIMARY = 19 */
        125831058, /* ICON_ON_SECONDARY = 20 */
        125831059, /* ICON_ON_TERTIARY = 21 */
        125831060, /* ICON_ON_FOURTH = 22 */
        125831061, /* BACKGROUND_PRIMARY = 23 */
        125831062, /* BACKGROUND_SECONDARY = 24 */
        125831063, /* BACKGROUND_TERTIARY = 25 */
        125831064, /* BACKGROUND_FOURTH = 26 */
        125831065, /* BACKGROUND_EMPHASIZE = 27 */
        125831003, /* COMP_FOREGROUND_PRIMARY = 28 */
        125831004, /* COMP_BACKGROUND_PRIMARY = 29 */
        -1,        /* COMP_BACKGROUND_PRIMARY_TRAN = 30 */
        125831005, /* COMP_BACKGROUND_PRIMARY_CONTRARY = 31 */
        125831006, /* COMP_BACKGROUND_GRAY = 32 */
        125831007, /* COMP_BACKGROUND_SECONDARY = 33 */
        125831008, /* COMP_BACKGROUND_TERTIARY = 34 */
        125831009, /* COMP_BACKGROUND_EMPHASIZE = 35 */
        125831066, /* COMP_BACKGROUND_NEUTRAL = 36 */
        125831011, /* COMP_EMPHASIZE_SECONDARY = 37 */
        125831012, /* COMP_EMPHASIZE_TERTIARY = 38 */
        125831013, /* COMP_DIVIDER = 39 */
        125831014, /* COMP_COMMON_CONTRARY = 40 */
        125831015, /* COMP_BACKGROUND_FOCUS = 41 */
        125831016, /* COMP_FOCUSED_PRIMARY = 42 */
        125831017, /* COMP_FOCUSED_SECONDARY = 43 */
        125831018, /* COMP_FOCUSED_TERTIARY = 44 */
        125831019, /* INTERACTIVE_HOVER = 45 */
        125831020, /* INTERACTIVE_PRESSED = 46 */
        125831021, /* INTERACTIVE_FOCUS = 47 */
        125831022, /* INTERACTIVE_ACTIVE = 48 */
        125831023, /* INTERACTIVE_SELECT = 49 */
        125831024, /* INTERACTIVE_CLICK = 50 */
    };
    RefPtr<TokenColors> tokenColors_;
};

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