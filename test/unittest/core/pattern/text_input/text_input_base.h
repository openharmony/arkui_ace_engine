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

#include <array>
#include <cstddef>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#ifdef WINDOWS_PLATFORM
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "gtest/gtest.h"
#include <unicode/uversion.h>
#include <unicode/putil.h>
#include <unicode/uclean.h>

#define private public
#define protected public

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_data_detector_mgr.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/unittest/core/pattern/test_ng.h"
#include "test/unittest/core/pattern/text_input/mock/mock_text_field_select_overlay.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/offset.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/string_utils.h"
#include "base/utils/type_definition.h"
#include "core/common/ace_application_info.h"
#include "core/common/ai/data_detector_mgr.h"
#include "core/common/ime/constant.h"
#include "core/common/ime/text_editing_value.h"
#include "core/common/ime/text_input_action.h"
#include "core/common/ime/text_input_type.h"
#include "core/common/ime/text_selection.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/scroll/scroll_bar_theme.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components/theme/theme_manager.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_event_hub.h"
#include "core/components_ng/pattern/text_field/text_input_response_area.h"
#include "core/event/key_event.h"
#include "core/event/touch_event.h"
#include "core/gestures/gesture_info.h"
#include "core/components/common/properties/text_style_parser.h"

#undef private
#undef protected

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
const InspectorFilter filter;
constexpr double ICON_SIZE = 24;
constexpr double ICON_HOT_ZONE_SIZE = 40;
constexpr double FONT_SIZE = 16;
constexpr int32_t DEFAULT_NODE_ID = 1;
constexpr int32_t MAX_BACKWARD_NUMBER = 30;
constexpr int32_t MAX_FORWARD_NUMBER = 30;
constexpr uint32_t DEFAULT_MAX_LINES = 1;
constexpr uint32_t DEFAULT_MAX_LENGTH = 30;
constexpr int32_t MIN_PLATFORM_VERSION = 10;
constexpr int32_t WORD_LIMIT_LEN = 5;
constexpr int32_t WORD_LIMIT_RETURN = 2;
constexpr int32_t BEYOND_LIMIT_RETURN = 4;
constexpr int32_t DEFAULT_RETURN_VALUE = -1;
const std::string DEFAULT_TEXT = "abcdefghijklmnopqrstuvwxyz";
const std::u16string DEFAULT_TEXT_U16 = u"abcdefghijklmnopqrstuvwxyz";
const std::string HELLO_TEXT = "hello";
const std::u16string HELLO_TEXT_U16 = u"hello";
const std::string DEFAULT_PLACE_HOLDER = "please input text here";
const std::string LOWERCASE_FILTER = "[a-z]";
const std::string NUMBER_FILTER = "^[0-9]*$";
const Color DEFAULT_PLACE_HODER_COLOR = Color::RED;
const Color DEFAULT_SELECTED_BACKFROUND_COLOR = Color::BLUE;
const Color DEFAULT_CARET_COLOR = Color::BLACK;
const Color DEFAULT_TEXT_COLOR = Color::BLACK;
const Dimension DEFAULT_FONT_SIZE = Dimension(16, DimensionUnit::VP);
const Dimension DEFAULT_INDENT_SIZE = Dimension(5, DimensionUnit::VP);
const FontWeight DEFAULT_FONT_WEIGHT = FontWeight::W500;
const std::string DEFAULT_INPUT_FILTER = "[a-z]";
const InputStyle DEFAULT_INPUT_STYLE = InputStyle::INLINE;
const CopyOptions DEFAULT_COPY_OPTIONS = CopyOptions::InApp;
const TextAlign DEFAULT_TEXT_ALIGN = TextAlign::LEFT;
const CaretStyle DEFAULT_CARET_STYLE = { Dimension(3, DimensionUnit::VP) };
const OHOS::Ace::DisplayMode DEFAULT_DISPLAY_MODE = OHOS::Ace::DisplayMode::AUTO;
const TextInputAction DEFAULT_ENTER_KEY_TYPE = TextInputAction::BEGIN;
const std::list<std::pair<std::string, int32_t>> FONT_FEATURE_VALUE_1 = ParseFontFeatureSettings("\"ss01\" 1");
const std::list<std::pair<std::string, int32_t>> FONT_FEATURE_VALUE_0 = ParseFontFeatureSettings("\"ss01\" 0");
const PreviewTextInfo PREVIEW_ONE = {u"ni", {-1, -1}};
const PreviewTextInfo PREVIEW_TWO = {u"你", {-1, -1}};
const PreviewTextInfo PREVIEW_THR = {u"hello", {0, 5}};
const PreviewTextInfo PREVIEW_FOR = {u"ab", {0, 2}};
const PreviewTextInfo PREVIEW_BAD_DATA = {u"bad", {0, -1}};
const TextOverflow OVERFLOW_ELLIPSIS = TextOverflow::ELLIPSIS;
const TextOverflow OVERFLOW_MARQUEE = TextOverflow::MARQUEE;
const TextOverflow OVERFLOW_DEFAULT = TextOverflow::DEFAULT;
const WordBreak WORDBREAK_ALL = WordBreak::BREAK_ALL;
template<typename CheckItem, typename Expected>
struct TestItem {
    CheckItem item;
    Expected expected;
    std::string error;
    TestItem(CheckItem checkItem, Expected expectedValue, std::string message = "")
        : item(checkItem), expected(expectedValue), error(std::move(message))
    {}
    TestItem() = default;
};
struct ExpectParagraphParams {
    float height = 50.f;
    float longestLine = 460.f;
    float maxWidth = 460.f;
    size_t lineCount = 1;
    bool firstCalc = true;
    bool secondCalc = true;
};
constexpr float CONTEXT_WIDTH_VALUE = 300.0f;
constexpr float CONTEXT_HEIGHT_VALUE = 150.0f;

class TextInputBases : public TestNG {
protected:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void TearDown() override;

    void CreateTextField(const std::string& text = "", const std::string& placeHolder = "",
        const std::function<void(TextFieldModelNG&)>& callback = nullptr);
    static void ExpectCallParagraphMethods(ExpectParagraphParams params);
    void GetFocus();
    RefPtr<TextFieldTheme> GetTheme();

    RefPtr<FrameNode> frameNode_;
    RefPtr<TextFieldPattern> pattern_;
    RefPtr<TextFieldEventHub> eventHub_;
    RefPtr<TextFieldLayoutProperty> layoutProperty_;
    RefPtr<TextFieldAccessibilityProperty> accessibilityProperty_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_TEXTFIELD_TEXTINPUT_TEST_NG_H