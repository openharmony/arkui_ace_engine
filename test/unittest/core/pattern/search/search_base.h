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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_TEXTFIELD_TEXTINPUT_TEST_NG_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_TEXTFIELD_TEXTINPUT_TEST_NG_H

#include "gtest/gtest.h"
#include "core/common/ime/text_input_action.h"

#define protected public
#define private public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"

#include "core/animation/curves.h"
#include "core/components/button/button_theme.h"
#include "core/components/common/properties/edge.h"
#include "core/components/search/search_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_render_property.h"
#include "core/components_ng/pattern/search/search_event_hub.h"
#include "core/components_ng/pattern/search/search_layout_algorithm.h"
#include "core/components_ng/pattern/search/search_layout_property.h"
#include "core/components_ng/pattern/search/search_model_ng.h"
#include "core/components_ng/pattern/search/search_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_event_hub.h"
#include "core/components_ng/pattern/text_field/text_field_layout_algorithm.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_paint_property.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "core/components/common/properties/text_style_parser.h"
#undef protected
#undef private

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace;

const InspectorFilter filter;
constexpr float COLUMN_HEIGHT = 200.0f;
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr float ZERO = 0.0f;
const SizeF CONTAINER_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
constexpr int32_t TEXTFIELD_INDEX = 0;
constexpr int32_t IMAGE_INDEX = 1;
constexpr int32_t CANCEL_IMAGE_INDEX = 2;
constexpr int32_t CANCEL_BUTTON_INDEX = 3;
constexpr int32_t BUTTON_INDEX = 4;
constexpr int32_t DIVIDER_INDEX = 5;
const std::string EMPTY_VALUE;
const std::string PLACEHOLDER = "DEFAULT PLACEHOLDER";
const std::string SEARCH_SVG = "resource:///ohos_search.svg";
const std::list<std::pair<std::string, int32_t>> FONT_FEATURE_VALUE_1 = ParseFontFeatureSettings("\"ss01\" 1");
const std::list<std::pair<std::string, int32_t>> FONT_FEATURE_VALUE_0 = ParseFontFeatureSettings("\"ss01\" 0");
const Color DEFAULT_SELECTED_BACKFROUND_COLOR_BLUE = Color::BLUE;
const Color DEFAULT_SELECTED_BACKFROUND_COLOR_RED = Color::RED;
const std::string DEFAULT_TEXT = "abcdefghijklmnopqrstuvwxyz";
const std::string DEFAULT_FILTER_TEXT = "CabcdefgABhCDEFG0123a456A789";
const std::string NUMBER_FILTER = "^[0-9]*$";
const std::string NUM_FILTER = "[0-9]";
const std::string FILTER_NUM_TEXT = "0123456789";
const Dimension DEFAULT_INDENT_SIZE = Dimension(5, DimensionUnit::VP);

class SearchBases : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
protected:
    std::pair<RefPtr<FrameNode>, RefPtr<LayoutWrapperNode>> CreateColumn();
    PaddingProperty CreatePadding(float left, float top, float right, float bottom);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_TEXTFIELD_TEXTINPUT_TEST_NG_H