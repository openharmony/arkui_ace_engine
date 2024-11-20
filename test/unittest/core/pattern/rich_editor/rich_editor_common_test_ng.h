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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_RICH_EDITOR_RICH_EDITOR_COMMON_TEST_NG_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_RICH_EDITOR_RICH_EDITOR_COMMON_TEST_NG_H

#include <optional>
#include <vector>

#include "gtest/gtest.h"

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
#include "test/mock/core/common/mock_udmf.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/image/pixel_map.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/string_utils.h"
#include "base/window/drag_window.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/overlay/keyboard_view.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_layout_algorithm.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_overlay_modifier.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/pattern/rich_editor/selection_info.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/pattern/text_field/text_selector.h"
#include "core/components_ng/render/paragraph.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/key_event.h"
#include "core/event/mouse_event.h"
#include "core/event/touch_event.h"
#include "core/pipeline/base/constants.h"
#include "test/unittest/core/pattern/test_ng.h"

namespace OHOS::Ace::NG {
namespace {
SelectionRangeInfo testSelectionRange(0, 0);
int32_t callBack1 = 0;
int32_t callBack2 = 0;
int32_t callBack3 = 0;
const std::string INIT_VALUE_1 = "hello1";
const std::string INIT_VALUE_2 = "hello2";
const std::string INIT_VALUE_3 = "hello world! hello world! hello world!";
const std::string TEST_INSERT_VALUE = "s";
const std::string TEST_INSERT_LINE_SEP = "\n";
const std::string EXCEPT_VALUE = "h\n";
const Dimension FONT_SIZE_VALUE = Dimension(20.1, DimensionUnit::PX);
const Dimension FONT_SIZE_VALUE_2 = Dimension(40, DimensionUnit::PX);
const Color TEXT_COLOR_VALUE = Color::FromRGB(255, 100, 100);
const Ace::FontStyle ITALIC_FONT_STYLE_VALUE = Ace::FontStyle::ITALIC;
const Ace::FontWeight FONT_WEIGHT_VALUE = Ace::FontWeight::W100;
const Ace::FontWeight FONT_WEIGHT_BOLD = Ace::FontWeight::BOLD;
const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
const Ace::TextDecoration TEXT_DECORATION_VALUE = Ace::TextDecoration::INHERIT;
const Color TEXT_DECORATION_COLOR_VALUE = Color::FromRGB(255, 100, 100);
const Ace::TextCase TEXT_CASE_VALUE = Ace::TextCase::LOWERCASE;
const Dimension LETTER_SPACING = Dimension(10, DimensionUnit::PX);
const Dimension LINE_HEIGHT_VALUE = Dimension(20.1, DimensionUnit::PX);
const Shadow TEXT_SHADOW1 = Shadow(0, 0, Offset(), Color::RED);
const Shadow TEXT_SHADOW2 = Shadow(0, 0, Offset(), Color::WHITE);
const std::vector<Shadow> SHADOWS { TEXT_SHADOW1, TEXT_SHADOW2 };
const std::string IMAGE_VALUE = "image1";
const std::string BUNDLE_NAME = "bundleName";
const std::string MODULE_NAME = "moduleName";
const std::string PREVIEW_TEXT_VALUE1 = "nihao";
const std::string PREVIEW_TEXT_VALUE2 = "nihaodajia";
const std::string PREVIEW_TEXT_VALUE3 = "dajia";
const std::string ROOT_TAG = "root";
const CalcLength CALC_LENGTH_CALC { 10.0, DimensionUnit::CALC };
const CalcLength ERROR_CALC_LENGTH_CALC { -10.0, DimensionUnit::CALC };
const Dimension CALC_TEST { 10.0, DimensionUnit::CALC };
const Dimension ERROR_CALC_TEST { -10.0, DimensionUnit::CALC };
const Offset MOUSE_GLOBAL_LOCATION = { 100, 200 };
constexpr int32_t WORD_LIMIT_LEN = 6;
constexpr int32_t WORD_LIMIT_RETURN = 2;
constexpr int32_t BEYOND_LIMIT_RETURN = 4;
constexpr int32_t DEFAULT_RETURN_VALUE = -1;
constexpr int32_t THIRD_PARAM = 2;
const float CONTAINER_WIDTH = 300.0f;
const float CONTAINER_HEIGHT = 300.0f;
const float BUILDER_WIDTH = 150.0f;
const float BUILDER_HEIGHT = 75.0f;
const SizeF BUILDER_SIZE(BUILDER_WIDTH, BUILDER_HEIGHT);
const uint32_t SYMBOL_ID = 1;
std::list<std::pair<std::string, int32_t>> TEXT_FONTFEATURE = {{ "subs", 1 }};
std::list<std::pair<std::string, int32_t>> TEXT_FONTFEATURE_2 = {{ "subs", 0 }};
std::vector<Color> SYMBOL_COLOR_LIST_1 = { Color::FromRGB(255, 100, 100) };
std::vector<Color> SYMBOL_COLOR_LIST_2 = { Color::FromRGB(255, 100, 100), Color::FromRGB(255, 255, 100) };
const uint32_t RENDER_STRATEGY_SINGLE = 0;
const uint32_t RENDER_STRATEGY_MULTI_COLOR = 1;
const uint32_t EFFECT_STRATEGY_NONE = 0;
const uint32_t EFFECT_STRATEGY_SCALE = 1;
const SizeF CONTAINER_SIZE(720.0f, 1136.0f);
constexpr float DEFAILT_OPACITY = 0.2f;
constexpr Color SYSTEM_CARET_COLOR = Color(0xff007dff);
constexpr Color SYSTEM_SELECT_BACKGROUND_COLOR = Color(0x33007dff);
constexpr float CONTEXT_WIDTH_VALUE = 300.0f;
constexpr float CONTEXT_HEIGHT_VALUE = 150.0f;
const Color DEFAULT_TEXT_COLOR_VALUE = Color::FromARGB(229, 0, 0, 0);
bool isOnWillChangeCalled = false;
bool isOnDidChangeCalled = false;
bool isOnEditChangeCalled = false;
RichEditorChangeValue onWillChangeValue;
RichEditorChangeValue onDidChangeValue;
auto& onWillRangeBefore = onWillChangeValue.rangeBefore_;
auto& onWillReplacedSpans = onWillChangeValue.replacedSpans_;
auto& onWillReplacedImageSpans = onWillChangeValue.replacedImageSpans_;
auto& onWillReplacedSymbolSpans = onWillChangeValue.replacedSymbolSpans_;
auto& onDidRangeBefore = onDidChangeValue.rangeBefore_;
auto& onDidRangeAfter = onDidChangeValue.rangeAfter_;
RichEditorDeleteValue aboutToDeleteValue;
const TextStyle TEXT_STYLE_1(10.0);
const TextStyle TEXT_STYLE_2(20.0);
const TextStyle TEXT_STYLE_3(30.0);
TextSpanOptions TEXT_SPAN_OPTIONS_1 = { .value = INIT_VALUE_1, .style = TEXT_STYLE_1 };
const ImageSpanAttribute IMAGE_SPAN_ATTRIBUTE_1 = {
    .size = ImageSpanSize{ .width = 200.0_px, .height = 100.0_px },
    .verticalAlign = VerticalAlign::CENTER,
    .objectFit = ImageFit::COVER,
    .marginProp = std::nullopt,
    .borderRadius = std::nullopt,
    .paddingProp = std::nullopt
};
const ImageSpanOptions IMAGE_SPAN_OPTIONS_1 = {
    .offset = std::nullopt,
    .image = "app.media.icon",
    .bundleName = std::nullopt,
    .moduleName = std::nullopt,
    .imagePixelMap = std::nullopt,
    .imageAttribute = IMAGE_SPAN_ATTRIBUTE_1
};
const SymbolSpanOptions SYMBOL_SPAN_OPTIONS_1 = {
    .offset = std::nullopt,
    .symbolId = 1,
    .style = TEXT_STYLE_1,
    .resourceObject = nullptr
};
auto BUILDER_NODE_1 = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
    []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
} // namespace

struct TestCursorItem {
    int32_t index;
    CaretMetricsF caretMetricsFDown;
    CaretMetricsF caretMetricsFUp;
};

struct TestParagraphRect {
    int32_t start;
    int32_t end;
    std::vector<RectF> rects;
};

struct TestParagraphItem {
    int32_t start;
    int32_t end;
    int32_t height;
    ParagraphStyle paragraphStyle;
    std::map<int32_t, Offset> indexOffsetMap;
    std::vector<TestCursorItem> testCursorItems;
    std::vector<TestParagraphRect> testParagraphRects;
};

class RichEditorCommonTestNg : public TestNG {
public:
    void AddSpan(const std::string& content);
    void AddImageSpan();
    void AddParagraph(TestParagraphItem testParagraphItem);
    void ClearParagraph();
    void ClearSpan();
    void InitAdjustObject(MockDataDetectorMgr& mockDataDetectorMgr);
    void RequestFocus();
    void GetFocus(const RefPtr<RichEditorPattern>& pattern);
    void OnDrawVerify(const SelectSpanType& type, const std::string& text, SymbolSpanOptions options, Offset offset,
        bool selected = false);
    void InitMagnifierParams(const SizeF& frameSize);
    static void MockKeyboardBuilder() {}
    RefPtr<FrameNode> richEditorNode_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_RICH_EDITOR_RICH_EDITOR_COMMON_TEST_NG_H