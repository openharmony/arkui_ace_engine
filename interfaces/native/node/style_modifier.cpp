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
#include "style_modifier.h"

#include <cstddef>
#include <cstdint>
#include <map>
#include <regex>
#include <string>

#include "native_node.h"
#include "native_type.h"
#include "node_model.h"

#include "base/error/error_code.h"
#include "base/log/log_wrapper.h"
#include "base/utils/string_utils.h"
#include "bridge/common/utils/utils.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/native/node/node_api.h"

namespace OHOS::Ace::NodeModel {
namespace {
const std::regex COLOR_WITH_MAGIC("#[0-9A-Fa-f]{8}");
const std::regex BRACKETS("\\(.*?\\)");
const std::regex FLOAT_MAGIC("^[0-9]+(\\.[0-9]+)?$");
const std::regex SIZE_TYPE_MAGIC("([0-9]+)([a-z]+)");
constexpr char PARAMS_SEPARATOR_LEVEL1 = ';';
constexpr int DEFAULT_ANGLE = 180;
constexpr int UNIT_VP = 1;
constexpr int UNIT_FP = 2;
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
constexpr int NUM_6 = 6;
constexpr int NUM_7 = 7;
constexpr int NUM_8 = 8;
constexpr int NUM_9 = 9;
constexpr int NUM_10 = 10;
constexpr int NUM_11 = 11;
constexpr int NUM_12 = 12;
constexpr int NUM_13 = 13;
constexpr int NUM_16 = 16;
constexpr int DEFAULT_UNIT = 1;
const int ALLOW_SIZE_1(1);
const int ALLOW_SIZE_2(2);
const int ALLOW_SIZE_4(4);
const int ALLOW_SIZE_7(7);
const int ALLOW_SIZE_8(8);
const int ALLOW_SIZE_16(16);
const int ALLOW_SIZE_10(10);

constexpr int DEFAULT_SIZE_18 = 18;
constexpr int DEFAULT_SIZE_24 = 24;
constexpr int DEFAULT_SIZE_50 = 50;
constexpr int COLOR_STRATEGY_STYLE = 1;
constexpr int COLOR_STYLE = 2;
constexpr int DISPLAY_ARROW_FALSE = 0;
constexpr int DISPLAY_ARROW_TRUE = 1;
constexpr int32_t X_INDEX = 0;
constexpr int32_t Y_INDEX = 1;
constexpr int32_t Z_INDEX = 2;
constexpr int32_t CENTER_X_INDEX = 0;
constexpr int32_t CENTER_Y_INDEX = 1;
constexpr int32_t CENTER_Z_INDEX = 2;
constexpr int32_t CENTER_X_PERCENT_INDEX = 3;
constexpr int32_t CENTER_Y_PERCENT_INDEX = 4;
constexpr int32_t CENTER_Z_PERCENT_INDEX = 5;
constexpr int32_t ROTATE_PERSPECTIVE_INDEX = 4;
constexpr int32_t ROTATE_ANGLE_INDEX = 3;
constexpr uint32_t ARRAY_SIZE = 3;
constexpr int32_t BACKGROUND_IMAGE_WIDTH_INDEX = 0;
constexpr int32_t BACKGROUND_IMAGE_HEIGHT_INDEX = 1;
constexpr float DEFAULT_OPACITY = 1.0f;

constexpr int32_t BLUR_STYLE_INDEX = 0;
constexpr int32_t COLOR_MODE_INDEX = 1;
constexpr int32_t ADAPTIVE_COLOR_INDEX = 2;
constexpr int32_t SCALE_INDEX = 3;
constexpr int32_t DECORATION_COLOR_INDEX = 1;
constexpr int32_t XCOMPONENT_TYPE_SURFACE = 0;
constexpr int32_t XCOMPONENT_TYPE_TEXTURE = 2;
const std::vector<std::string> TEXT_COPY_OPTION_ARRAY = { "none", "in-app", "local", "distributed" };
const std::vector<std::string> TEXT_TEXT_SHADOW_ARRAY = { "color", "blur" };
const std::vector<std::string> FONT_STYLE_ARRAY = { "normal", "italic" };
const std::vector<std::string> FONT_OVERFLOW_ARRAY = { "none", "clip", "ellipsis", "marquee" };
const std::vector<std::string> IMAGE_REPEAT_ARRAY = { "no-repeat", "x", "y", "xy" };
const std::vector<std::string> TEXT_INPUT_ENTER_KEY_TYPE = { "begin", "none", "go", "search", "send", "next", "done",
    "previous", "new-line" };
const std::vector<std::string> TEXT_INPUT_TYPE = { "normal", "multiline", "number", "phone-number", "date-time",
    "email", "url", "password", "number-password", "screen-lock-password", "user-name", "new-password",
    "number-decimal" };
const std::vector<std::string> COMMON_GRADIENT_DIRECTION = { "left", "top", "right", "bottom", "left-top",
    "left-bottom", "right-top", "right-bottom", "none" };
const std::vector<std::string> COMMON_ALIGNMENT = { "top-start", "top", "top-end", "start", "center", "end",
    "bottom-start", "bottom", "bottom-end" };
const std::vector<std::string> COMMON_BORDER_STYLE = { "solid", "dashed", "dotted" };
const std::vector<std::string> COMMON_VISIBLE_STYLE = { "visible", "hidden", "none" };
const std::vector<std::string> COMMON_HIT_TEST_MODE_STYLE = { "default", "block", "transparent" };
const std::vector<std::string> COMMON_SHADOW_TYPE = { "COLOR", "BLUR" };
const std::vector<std::string> COMMON_SHADOW_COLORING_STRATEGY = { "invert", "average", "primary" };
const std::vector<std::string> COMMON_SHADOW_STYLE = { "outer-default-xs", "outer-default-sm", "outer-default-md",
    "outer-default-lg", "outer-floating-sm", "outer-floating-md", "none" };
const std::vector<std::string> SCROLL_DISPLAY_MODE = { "off", "auto", "on" };
const std::vector<std::string> SCROLL_AXIS = { "vertical", "horizontal", "free", "none" };
const std::vector<std::string> SCROLL_EDGE_EFFECT = { "spring", "fade", "none" };
const std::vector<std::string> LIST_STICKY_STYLE = { "none", "header", "footer", "both" };
const std::vector<std::string> CURVE_ARRAY = { "linear", "ease", "ease-in", "ease-out", "ease-in-out",
    "fast-out-slow-in", "linear-out-slow-in", "fast-out-linear-in", "extreme-deceleration", "sharp", "rhythm", "smooth",
    "friction" };
const std::vector<std::string> PLAY_MODE_ARRAY = { "normal", "alternate", "reverse", "alternate_reverse" };
const std::vector<std::string> FONT_STYLES = { "normal", "italic" };
const std::vector<int32_t> SPAN_ATTRIBUTES = { static_cast<int32_t>(NODE_SPAN_CONTENT),
    static_cast<int32_t>(NODE_TEXT_DECORATION), static_cast<int32_t>(NODE_FONT_COLOR),
    static_cast<int32_t>(NODE_FONT_SIZE), static_cast<int32_t>(NODE_FONT_STYLE), static_cast<int32_t>(NODE_FONT_WEIGHT),
    static_cast<int32_t>(NODE_TEXT_LINE_HEIGHT), static_cast<int32_t>(NODE_TEXT_CASE),
    static_cast<int32_t>(NODE_TEXT_LETTER_SPACING) };
const std::string DEFAULT_CURVE = "linear";
constexpr int32_t ANIMATION_DURATION_INDEX = 0;
constexpr int32_t ANIMATION_CURVE_INDEX = 1;
constexpr int32_t ANIMATION_DELAY_INDEX = 2;
constexpr int32_t ANIMATION_INTERATION_INDEX = 3;
constexpr int32_t ANIMATION_PLAY_MODE_INDEX = 4;
constexpr int32_t ANIMATION_TEMPO_INDEX = 5;
constexpr int32_t OPACITY_ANIMATION_BASE = 1;
constexpr int32_t ROTATE_ANIMATION_BASE = 5;
constexpr int32_t SCALE_ANIMATION_BASE = 3;
constexpr int32_t TRANSLATE_ANIMATION_BASE = 3;
constexpr int32_t DEFAULT_DURATION = 1000;
constexpr int32_t ALIGN_RULES_ARRAY_LENGTH = 6;
const std::vector<std::string> ALIGN_RULES_HORIZONTAL_ARRAY = { "start", "center", "end" };
const std::vector<std::string> ALIGN_RULES_VERTICAL_ARRAY = { "top", "center", "bottom" };
typedef std::map<const std::string, ArkUI_Int32> AttrStringToIntMap;
constexpr int32_t TWO = 2;
constexpr float ZERO_F = 0.0f;
constexpr float HUNDRED = 100.0f;
constexpr float SLIDER_STEP_MIN_F = 0.01f;
constexpr float HALF = 0.5f;
constexpr int32_t REQUIRED_ONE_PARAM = 1;
constexpr int32_t REQUIRED_TWO_PARAM = 2;
constexpr int32_t REQUIRED_TREE_PARAM = 3;
constexpr int32_t REQUIRED_FOUR_PARAM = 4;
constexpr int32_t REQUIRED_FIVE_PARAM = 5;
constexpr int32_t REQUIRED_SEVEN_PARAM = 7;
constexpr int32_t REQUIRED_TWENTY_PARAM = 20;
constexpr int32_t MAX_ATTRIBUTE_ITEM_LEN = 12;
ArkUI_NumberValue g_numberValues[MAX_ATTRIBUTE_ITEM_LEN] = { 0 };
ArkUI_AttributeItem g_attributeItem = { g_numberValues, MAX_ATTRIBUTE_ITEM_LEN, nullptr, nullptr };

constexpr uint32_t DEFAULT_COLOR = 0xFFFFFFFF;
constexpr uint32_t DEFAULT_FIll_COLOR = 0x00000000;
constexpr int32_t DEFAULT_X = 0;
constexpr int32_t DEFAULT_Y = 0;

constexpr int32_t DEFAULT_TRUE = 1;
constexpr int32_t DEFAULT_FALSE = 0;

constexpr int32_t RETURN_SIZE_ONE = 1;

const std::vector<std::string> ACCESSIBILITY_LEVEL_VECTOR = { "auto", "yes", "no", "no-hide-descendants" };
std::map<std::string, int32_t> ACCESSIBILITY_LEVEL_MAP = { { "auto", 0 }, { "yes", 1 }, { "no", 2 },
    { "no-hide-descendants", 3 } };

void ResetAttributeItem()
{
    for (int i = 0; i < MAX_ATTRIBUTE_ITEM_LEN; ++i) {
        g_numberValues[i].i32 = 0;
    }
    g_attributeItem.size = 0;
    g_attributeItem.string = nullptr;
    g_attributeItem.object = nullptr;
}
uint32_t StringToColorInt(const char* string, uint32_t defaultValue = 0)
{
    std::smatch matches;
    std::string colorStr(string);
    if (std::regex_match(colorStr, matches, COLOR_WITH_MAGIC)) {
        colorStr.erase(0, 1);
        constexpr int colorNumFormat = 16;
        auto value = stoul(colorStr, nullptr, colorNumFormat);
        return value;
    }
    return defaultValue;
}

float StringToFloat(const char* string, float defaultValue = 0.0f)
{
    char* end = nullptr;
    auto value = strtof(string, &end);
    if (end == string || errno == ERANGE) {
        return defaultValue;
    }
    return value;
}

int StringToInt(const char* string, int defaultValue = 0)
{
    char* end;
    auto value = std::strtol(string, &end, 10);
    if (end == string || errno == ERANGE || (value < INT_MIN || value > INT_MAX)) {
        return defaultValue;
    }
    return value;
}

int StringToBoolInt(const char* value, int defaultValue = 1)
{
    std::string trueValues = "TRUE";
    std::string falseValues = "FALSE";
    std::string input(value);
    StringUtils::TransformStrCase(input, StringUtils::TEXT_CASE_UPPERCASE);
    if (input == trueValues) {
        return 1;
    } else if (input == falseValues) {
        return 0;
    } else {
        return defaultValue;
    }
}

int StringToEnumInt(const char* value, const std::vector<std::string>& vec, int defaultValue)
{
    std::string input(value);
    auto it = std::find_if(vec.begin(), vec.end(), [&input](const std::string& str) { return str == input; });
    if (it != vec.end()) {
        return std::distance(vec.begin(), it);
    }
    return defaultValue;
}

std::string CurveToString(int curve)
{
    std::string curveStr = "linear";
    switch (curve) {
        case ArkUI_AnimationCurve::ARKUI_CURVE_LINEAR:
            curveStr = "Linear";
            break;
        case ArkUI_AnimationCurve::ARKUI_CURVE_EASE:
            curveStr = "Ease";
            break;
        case ArkUI_AnimationCurve::ARKUI_CURVE_EASE_IN:
            curveStr = "EaseIn";
            break;
        case ArkUI_AnimationCurve::ARKUI_CURVE_EASE_OUT:
            curveStr = "EaseOut";
            break;
        case ArkUI_AnimationCurve::ARKUI_CURVE_EASE_IN_OUT:
            curveStr = "EaseInOut";
            break;
        case ArkUI_AnimationCurve::ARKUI_CURVE_FAST_OUT_SLOW_IN:
            curveStr = "FastOutSlowIn";
            break;
        case ArkUI_AnimationCurve::ARKUI_CURVE_LINEAR_OUT_SLOW_IN:
            curveStr = "LinearOutSlowIn";
            break;
        case ArkUI_AnimationCurve::ARKUI_CURVE_FAST_OUT_LINEAR_IN:
            curveStr = "FastOutLinearIn";
            break;
        case ArkUI_AnimationCurve::ARKUI_CURVE_EXTREME_DECELERATION:
            curveStr = "ExtremeDeceleration";
            break;
        case ArkUI_AnimationCurve::ARKUI_CURVE_SHARP:
            curveStr = "Sharp";
            break;
        case ArkUI_AnimationCurve::ARKUI_CURVE_RHYTHM:
            curveStr = "Rhythm";
            break;
        case ArkUI_AnimationCurve::ARKUI_CURVE_SMOOTH:
            curveStr = "Smooth";
            break;
        case ArkUI_AnimationCurve::ARKUI_CURVE_FRICTION:
            curveStr = "Friction";
            break;
        default:
            break;
    }
    return curveStr;
}

std::string ShapeToString(int shape)
{
    std::string shapeStr = "rect";
    switch (shape) {
        case NUM_0:
            shapeStr = "rect";
            break;
        case NUM_1:
            shapeStr = "circle";
            break;
        case NUM_2:
            shapeStr = "ellipse";
            break;
        case NUM_3:
            shapeStr = "path";
            break;
        case NUM_4:
            shapeStr = "progress";
            break;
        default:
            break;
    }
    return shapeStr;
}

int32_t CheckAttributeItemArray(const ArkUI_AttributeItem* item, int32_t requiredAtLeastSize)
{
    CHECK_NULL_RETURN(item, -1);
    if (item->size < requiredAtLeastSize) {
        return -1;
    }
    return item->size;
}

bool CheckAttributeIsBool(int32_t value)
{
    if (value == DEFAULT_FALSE || value == DEFAULT_TRUE) {
        return true;
    }
    return false;
}

bool CheckAttributeIsAlignment(int32_t value)
{
    int32_t minEnumValue = static_cast<int32_t>(ArkUI_Alignment::ARKUI_ALIGNMENT_TOP_START);
    int32_t maxEnumValue = static_cast<int32_t>(ArkUI_Alignment::ARKUI_ALIGNMENT_BOTTOM_END);
    return value >= minEnumValue && value <= maxEnumValue;
}

bool CheckAttributeIsFontWeight(int32_t value)
{
    int32_t minEnumValue = static_cast<int32_t>(ArkUI_FontWeight::ARKUI_FONT_WEIGHT_W100);
    int32_t maxEnumValue = static_cast<int32_t>(ArkUI_FontWeight::ARKUI_FONT_WEIGHT_REGULAR);
    return value >= minEnumValue && value <= maxEnumValue;
}

bool CheckAttributeIsFontStyle(int32_t value)
{
    int32_t minEnumValue = static_cast<int32_t>(ArkUI_FontStyle::ARKUI_FONT_STYLE_NORMAL);
    int32_t maxEnumValue = static_cast<int32_t>(ArkUI_FontStyle::ARKUI_FONT_STYLE_ITALIC);
    return value >= minEnumValue && value <= maxEnumValue;
}

bool CheckAttributeIsTextHeightAdaptivePolicy(int32_t value)
{
    int32_t minEnumValue =
        static_cast<int32_t>(ArkUI_TextHeightAdaptivePolicy::ARKUI_TEXT_HEIGHT_ADAPTIVE_POLICY_MAX_LINES_FIRST);
    int32_t maxEnumValue =
        static_cast<int32_t>(ArkUI_TextHeightAdaptivePolicy::ARKUI_TEXT_HEIGHT_ADAPTIVE_POLICY_LAYOUT_CONSTRAINT_FIRST);
    return value >= minEnumValue && value <= maxEnumValue;
}

bool CheckAttributeIsCopyOptions(int32_t value)
{
    int32_t minEnumValue = static_cast<int32_t>(ArkUI_CopyOptions::ARKUI_COPY_OPTIONS_NONE);
    int32_t maxEnumValue = static_cast<int32_t>(ArkUI_CopyOptions::ARKUI_COPY_OPTIONS_CROSS_DEVICE);
    return value >= minEnumValue && value <= maxEnumValue;
}

bool CheckAttributeIsAnimationCurve(int32_t value)
{
    int32_t minEnumValue = static_cast<int32_t>(ArkUI_AnimationCurve::ARKUI_CURVE_LINEAR);
    int32_t maxEnumValue = static_cast<int32_t>(ArkUI_AnimationCurve::ARKUI_CURVE_FRICTION);
    return value >= minEnumValue && value <= maxEnumValue;
}

bool CheckAttributeIsScrollNestedMode(int32_t value)
{
    int32_t minEnumValue = static_cast<int32_t>(ArkUI_ScrollNestedMode::ARKUI_SCROLL_NESTED_MODE_SELF_ONLY);
    int32_t maxEnumValue = static_cast<int32_t>(ArkUI_ScrollNestedMode::ARKUI_SCROLL_NESTED_MODE_PARALLEL);
    return value >= minEnumValue && value <= maxEnumValue;
}

bool CheckAttributeIsSliderStyle(int32_t value)
{
    int32_t minEnumValue = static_cast<int32_t>(ArkUI_SliderStyle::ARKUI_SLIDER_STYLE_OUT_SET);
    int32_t maxEnumValue = static_cast<int32_t>(ArkUI_SliderStyle::ARKUI_SLIDER_STYLE_IN_SET);
    return value >= minEnumValue && value <= maxEnumValue;
}

bool CheckAttributeIsSliderBlockStyle(int32_t value)
{
    int32_t minEnumValue = static_cast<int32_t>(ArkUI_SliderBlockStyle::ARKUI_SLIDER_BLOCK_STYLE_DEFAULT);
    int32_t maxEnumValue = static_cast<int32_t>(ArkUI_SliderBlockStyle::ARKUI_SLIDER_BLOCK_STYLE_SHAPE);
    return value >= minEnumValue && value <= maxEnumValue;
}

bool CheckAttributeIsSliderDirection(int32_t value)
{
    int32_t minEnumValue = static_cast<int32_t>(ArkUI_SliderDirection::ARKUI_SLIDER_DIRECTION_VERTICAL);
    int32_t maxEnumValue = static_cast<int32_t>(ArkUI_SliderDirection::ARKUI_SLIDER_DIRECTION_HORIZONTAL);
    return value >= minEnumValue && value <= maxEnumValue;
}

bool CheckAttributeIsCheckboxShape(int32_t value)
{
    int32_t minEnumValue = static_cast<int32_t>(ArkUI_CheckboxShape::ArkUI_CHECKBOX_SHAPE_CIRCLE);
    int32_t maxEnumValue = static_cast<int32_t>(ArkUI_CheckboxShape::ArkUI_CHECKBOX_SHAPE_ROUNDED_SQUARE);
    return value >= minEnumValue && value <= maxEnumValue;
}

bool CheckAttributeIsAccessibilityLevel(int32_t value)
{
    int32_t minEnumValue = static_cast<int32_t>(ArkUI_AccessibilityLevel::ARKUI_ACCESSIBILITY_LEVEL_AUTO);
    int32_t maxEnumValue =
        static_cast<int32_t>(ArkUI_AccessibilityLevel::ARKUI_ACCESSIBILITY_LEVEL_NO_HIDE_DESCENDANTS);
    return value >= minEnumValue && value <= maxEnumValue;
}

bool CheckAttributeString(const ArkUI_AttributeItem* item)
{
    CHECK_NULL_RETURN(item, false);
    if (!item->string) {
        return false;
    }
    return true;
}

bool CheckRangFloat(float start, float end, float value)
{
    return value >= start && value <= end;
}

bool CheckAnimation(const ArkUI_AttributeItem* item, int32_t size, int32_t animationIndexBase)
{
    CHECK_NULL_RETURN(item, false);
    const int32_t animationCurveIndex = animationIndexBase + ANIMATION_CURVE_INDEX;
    if (animationCurveIndex < size &&
        (item->value[animationCurveIndex].i32 < 0 ||
            item->value[animationCurveIndex].i32 > static_cast<int32_t>(ARKUI_CURVE_FRICTION))) {
        return false;
    }
    const int32_t playModeIndex = animationIndexBase + ANIMATION_PLAY_MODE_INDEX;
    if (playModeIndex < size &&
        (item->value[playModeIndex].i32 < 0 ||
            item->value[playModeIndex].i32 > static_cast<int32_t>(ARKUI_ANIMATION_PLAY_MODE_ALTERNATE_REVERSE))) {
        return false;
    }
    const int32_t animationTempoIndex = animationIndexBase + ANIMATION_TEMPO_INDEX;
    if (animationTempoIndex < size && LessNotEqual(item->value[animationTempoIndex].f32, 0.0f)) {
        return false;
    }
    return true;
}

void ParseAnimation(const ArkUI_AttributeItem* item, int32_t actualSize, ArkUIAnimationOptionType& animationOption,
    const int animationIndexBase)
{
    const int32_t animationDurationIndex = animationIndexBase + ANIMATION_DURATION_INDEX;
    int32_t duration = DEFAULT_DURATION;
    if (animationDurationIndex < actualSize) {
        duration = item->value[animationDurationIndex].i32;
    }
    const int32_t animationCurveIndex = animationIndexBase + ANIMATION_CURVE_INDEX;
    std::string curve = DEFAULT_CURVE;
    if (animationCurveIndex < actualSize &&
        item->value[animationCurveIndex].i32 < static_cast<int32_t>(CURVE_ARRAY.size())) {
        curve = CURVE_ARRAY[item->value[animationCurveIndex].i32];
    }
    const int32_t animationDelayIndex = animationIndexBase + ANIMATION_DELAY_INDEX;
    int32_t delay = 0;
    if (animationDelayIndex < actualSize) {
        delay = item->value[animationDelayIndex].i32;
    }
    const int32_t animationIterationsIndex = animationIndexBase + ANIMATION_INTERATION_INDEX;
    int32_t iterations = 1;
    if (animationIterationsIndex < actualSize) {
        iterations = item->value[animationIterationsIndex].i32;
    }
    const int32_t animationPlayModeIndex = animationIndexBase + ANIMATION_PLAY_MODE_INDEX;
    int32_t direction = 0;
    if (animationPlayModeIndex < actualSize) {
        direction = item->value[animationPlayModeIndex].i32;
    }
    const int32_t animationTempoIndex = animationIndexBase + ANIMATION_TEMPO_INDEX;
    float tempo = 1.0f;
    if (animationTempoIndex < actualSize) {
        tempo = item->value[animationTempoIndex].f32;
    }
    animationOption.duration = duration;
    animationOption.curve = curve.c_str();
    animationOption.delay = delay;
    animationOption.iteration = iterations;
    animationOption.palyMode = direction;
    animationOption.tempo = tempo;
}

void ResetAnimation(ArkUIAnimationOptionType& animationOption)
{
    animationOption.duration = DEFAULT_DURATION;
    animationOption.curve = DEFAULT_CURVE.c_str();
    animationOption.delay = 0;
    animationOption.iteration = 1;
    animationOption.palyMode = 0;
    animationOption.tempo = 1.0f;
}

// Common Arttributes functions
int32_t SetWidth(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || LessNotEqual(item->value[NUM_0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    // 1 for vp. check in DimensionUnit.
    fullImpl->getNodeModifiers()->getCommonModifier()->setWidth(
        node->uiNodeHandle, item->value[NUM_0].f32, UNIT_VP, nullptr);
    return ERROR_CODE_NO_ERROR;
}

void ResetWidth(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetWidth(node->uiNodeHandle);
}

int32_t SetHeight(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || LessNotEqual(item->value[NUM_0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    // 1 for vp. check in DimensionUnit.
    fullImpl->getNodeModifiers()->getCommonModifier()->setHeight(
        node->uiNodeHandle, item->value[NUM_0].f32, UNIT_VP, nullptr);
    return ERROR_CODE_NO_ERROR;
}

void ResetHeight(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetHeight(node->uiNodeHandle);
}

int32_t SetBackgroundColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setBackgroundColor(node->uiNodeHandle, item->value[NUM_0].u32);
    return ERROR_CODE_NO_ERROR;
}

void ResetBackgroundColor(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetBackgroundColor(node->uiNodeHandle);
}

int32_t SetBackgroundImage(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->string) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->size == NUM_1 &&
        (item->value[NUM_0].i32 < 0 || item->value[NUM_0].i32 > static_cast<int32_t>(ARKUI_IMAGE_REPEAT_XY))) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::string bundle;
    std::string module;
    int repeat = item->size == NUM_1 ? item->value[NUM_0].i32 : ARKUI_IMAGE_REPEAT_NONE;
    fullImpl->getNodeModifiers()->getCommonModifier()->setBackgroundImage(
        node->uiNodeHandle, item->string, bundle.c_str(), module.c_str(), repeat);
    return ERROR_CODE_NO_ERROR;
}

void ResetBackgroundImage(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetBackgroundImage(node->uiNodeHandle);
}

int32_t SetPadding(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size != NUM_1 && item->size != NUM_4) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    int topIndex = NUM_0;
    int rightIndex = item->size == NUM_1 ? NUM_0 : NUM_1;
    int bottomIndex = item->size == NUM_1 ? NUM_0 : NUM_2;
    int leftIndex = item->size == NUM_1 ? NUM_0 : NUM_3;
    struct ArkUISizeType top = { item->value[topIndex].f32, UNIT_VP };
    struct ArkUISizeType right = { item->value[rightIndex].f32, UNIT_VP };
    struct ArkUISizeType bottom = { item->value[bottomIndex].f32, UNIT_VP };
    struct ArkUISizeType left = { item->value[leftIndex].f32, UNIT_VP };
    fullImpl->getNodeModifiers()->getCommonModifier()->setPadding(node->uiNodeHandle, &top, &right, &bottom, &left);
    return ERROR_CODE_NO_ERROR;
}

void ResetPadding(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetPadding(node->uiNodeHandle);
}

int32_t SetKey(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->string) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setKey(node->uiNodeHandle, item->string);
    return ERROR_CODE_NO_ERROR;
}

void ResetKey(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetKey(node->uiNodeHandle);
}

int32_t SetEnabled(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || item->value[NUM_0].i32 < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setEnabled(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetEnabled(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetEnabled(node->uiNodeHandle);
}

int32_t SetMargin(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item || (item->size != NUM_4 && item->size != NUM_1)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    ArkUISizeType top, right, bottom, left;
    top.value = right.value = bottom.value = left.value = NUM_0;
    top.unit = right.unit = bottom.unit = left.unit = DEFAULT_UNIT;
    if (item->size == NUM_1) {
        top.value = right.value = bottom.value = left.value = item->value[NUM_0].f32;
    } else if (item->size == NUM_4) {
        top.value = item->value[NUM_0].f32;
        right.value = item->value[NUM_1].f32;
        bottom.value = item->value[NUM_2].f32;
        left.value = item->value[NUM_3].f32;
    }

    fullImpl->getNodeModifiers()->getCommonModifier()->setMargin(node->uiNodeHandle, &top, &right, &bottom, &left);
    return ERROR_CODE_NO_ERROR;
}

void ResetMargin(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getCommonModifier()->resetMargin(node->uiNodeHandle);
}

int32_t SetTranslate(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_TREE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    ArkUI_Float32 values[item->size];
    ArkUI_Int32 units[item->size];
    for (int i = 0; i < item->size; ++i) {
        values[i] = item->value[i].f32;
        units[i] = UNIT_VP;
    }

    fullImpl->getNodeModifiers()->getCommonModifier()->setTranslate(node->uiNodeHandle, values, units, item->size);
    return ERROR_CODE_NO_ERROR;
}

void ResetTranslate(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getCommonModifier()->resetTranslate(node->uiNodeHandle);
}

int32_t SetScale(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();

    if (item->size != NUM_5 && item->size != NUM_2) {
        return ERROR_CODE_PARAM_INVALID;
    }
    ArkUI_Float32 values[item->size];
    for (int i = 0; i < item->size; i++) {
        values[i] = item->value[i].f32;
    }
    ArkUI_Int32 units[NUM_2] = { UNIT_VP, UNIT_VP };
    fullImpl->getNodeModifiers()->getCommonModifier()->setScale(node->uiNodeHandle, values, item->size, units, NUM_2);
    return ERROR_CODE_NO_ERROR;
}

void ResetScale(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getCommonModifier()->resetScale(node->uiNodeHandle);
}

int32_t SetRotate(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_FIVE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    ArkUI_Float32 values[item->size];
    for (int i = 0; i < item->size; ++i) {
        values[i] = item->value[i].f32;
    }

    fullImpl->getNodeModifiers()->getCommonModifier()->setRotateWithoutTransformCenter(
        node->uiNodeHandle, values, item->size);
    return ERROR_CODE_NO_ERROR;
}

void ResetRotate(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getCommonModifier()->resetRotate(node->uiNodeHandle);
}

int32_t SetBrightness(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    auto brightness = item->value[NUM_0].f32;
    fullImpl->getNodeModifiers()->getCommonModifier()->setBrightness(node->uiNodeHandle, brightness);
    return ERROR_CODE_NO_ERROR;
}

void ResetBrightness(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getCommonModifier()->resetBrightness(node->uiNodeHandle);
}

int32_t SetSaturate(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !InRegion(NUM_0, DEFAULT_SIZE_50, item->value[NUM_0].f32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    auto saturate = item->value[NUM_0].f32;
    fullImpl->getNodeModifiers()->getCommonModifier()->setSaturate(node->uiNodeHandle, saturate);
    return ERROR_CODE_NO_ERROR;
}

void ResetSaturate(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getCommonModifier()->resetSaturate(node->uiNodeHandle);
}

int32_t SetBlur(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    ArkUI_Float64 blur = item->value[NUM_0].f32;
    fullImpl->getNodeModifiers()->getCommonModifier()->setBlur(node->uiNodeHandle, blur);
    return ERROR_CODE_NO_ERROR;
}

void ResetBlur(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getCommonModifier()->resetBlur(node->uiNodeHandle);
}

int32_t SetLinearGradient(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->object == nullptr) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    const ArkUI_ColorStop* colorStop = reinterpret_cast<ArkUI_ColorStop*>(item->object);
    int size = colorStop->size;
    ArkUI_Float32 colors[size * NUM_3];
    for (int i = 0; i < size; i++) {
        colors[i * NUM_3 + NUM_0] = colorStop->colors[i];
        colors[i * NUM_3 + NUM_1] = true;
        colors[i * NUM_3 + NUM_2] = colorStop->stops[i];
    }

    ArkUI_Float32 values[NUM_4] = { false, DEFAULT_ANGLE, NUM_3, false };
    if (item->size > NUM_0) {
        values[NUM_0] = true;
        values[NUM_1] = item->value[NUM_0].f32;
    }

    if (item->size > NUM_1) {
        values[NUM_2] = item->value[NUM_1].i32;
    }
    values[NUM_3] = (item->size > NUM_2) ? item->value[NUM_2].i32 : false;
    fullImpl->getNodeModifiers()->getCommonModifier()->setLinearGradient(
        node->uiNodeHandle, values, NUM_4, colors, size * NUM_3);
    return ERROR_CODE_NO_ERROR;
}

void ResetLinearGradient(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getCommonModifier()->resetLinearGradient(node->uiNodeHandle);
}

int32_t SetAlign(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    auto attrVal = item->value[NUM_0].i32;
    fullImpl->getNodeModifiers()->getCommonModifier()->setAlign(node->uiNodeHandle, attrVal);
    return ERROR_CODE_NO_ERROR;
}

void ResetAlign(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getCommonModifier()->resetAlign(node->uiNodeHandle);
}

int32_t SetOpacity(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (LessNotEqual(item->value[0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setOpacity(node->uiNodeHandle, item->value[0].f32);
    return ERROR_CODE_NO_ERROR;
}

void ResetOpacity(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetOpacity(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetOpacity(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].f32 = modifier->getOpacity(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetBorderWidth(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    float widthVals[ALLOW_SIZE_4] = { 0, 0, 0, 0 };
    int widthUnits[ALLOW_SIZE_4] = { DEFAULT_UNIT, DEFAULT_UNIT, DEFAULT_UNIT, DEFAULT_UNIT };

    if (item->size == 1) {
        if (LessNotEqual(item->value[0].f32, 0.0f)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        for (int i = 0; i < ALLOW_SIZE_4; ++i) {
            widthVals[i] = item->value[0].f32;
        }
    } else if (item->size == ALLOW_SIZE_4) {
        for (int i = 0; i < ALLOW_SIZE_4; ++i) {
            if (LessNotEqual(item->value[0].f32, 0.0f)) {
                return ERROR_CODE_PARAM_INVALID;
            } else {
                widthVals[i] = item->value[i].f32;
            }
        }
    } else {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setBorderWidth(
        node->uiNodeHandle, widthVals, widthUnits, ALLOW_SIZE_4);
    return ERROR_CODE_NO_ERROR;
}

void ResetBorderWidth(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetBorderWidth(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetBorderWidth(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    ArkUI_Float32 borderWidth[NUM_4];
    fullImpl->getNodeModifiers()->getCommonModifier()->getBorderWidth(node->uiNodeHandle, borderWidth);
    g_numberValues[NUM_0].f32 = borderWidth[NUM_0];
    g_numberValues[NUM_1].f32 = borderWidth[NUM_1];
    g_numberValues[NUM_2].f32 = borderWidth[NUM_2];
    g_numberValues[NUM_3].f32 = borderWidth[NUM_3];
    return &g_attributeItem;
}

int32_t SetBorderRadius(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    float radiusVals[ALLOW_SIZE_4] = { NUM_1, NUM_1, NUM_1, NUM_1 };
    int radiusUnits[ALLOW_SIZE_4] = { DEFAULT_UNIT, DEFAULT_UNIT, DEFAULT_UNIT, DEFAULT_UNIT };

    if (item->size == 1) {
        if (LessNotEqual(item->value[NUM_0].f32, 0.0f)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        for (int i = 0; i < ALLOW_SIZE_4; ++i) {
            radiusVals[i] = item->value[NUM_0].f32;
        }
    } else if (item->size == ALLOW_SIZE_4) {
        for (int i = 0; i < ALLOW_SIZE_4; ++i) {
            if (LessNotEqual(item->value[NUM_0].f32, 0.0f)) {
                return ERROR_CODE_PARAM_INVALID;
            } else {
                radiusVals[i] = item->value[i].f32;
            }
        }
    } else {
        return ERROR_CODE_PARAM_INVALID;
    }

    fullImpl->getNodeModifiers()->getCommonModifier()->setBorderRadius(
        node->uiNodeHandle, radiusVals, radiusUnits, ALLOW_SIZE_4);
    return ERROR_CODE_NO_ERROR;
}

void ResetBorderRadius(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetBorderRadius(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetBorderRadius(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    ArkUI_Float32 borderRadius[NUM_4];
    fullImpl->getNodeModifiers()->getCommonModifier()->getBorderRadius(node->uiNodeHandle, borderRadius);
    g_numberValues[NUM_0].f32 = borderRadius[NUM_0];
    g_numberValues[NUM_1].f32 = borderRadius[NUM_1];
    g_numberValues[NUM_2].f32 = borderRadius[NUM_2];
    g_numberValues[NUM_3].f32 = borderRadius[NUM_3];
    return &g_attributeItem;
}

int32_t SetBorderColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    uint32_t colors[ALLOW_SIZE_4] = { DEFAULT_COLOR, DEFAULT_COLOR, DEFAULT_COLOR, DEFAULT_COLOR };
    if (item->size == 1) {
        for (int i = 0; i < ALLOW_SIZE_4; ++i) {
            colors[i] = item->value[0].u32;
        }
    } else if (item->size == ALLOW_SIZE_4) {
        for (int i = 0; i < ALLOW_SIZE_4; ++i) {
            colors[i] = item->value[i].u32;
        }
    } else {
        return ERROR_CODE_PARAM_INVALID;
    }

    fullImpl->getNodeModifiers()->getCommonModifier()->setBorderColor(
        node->uiNodeHandle, colors[NUM_0], colors[NUM_1], colors[NUM_2], colors[NUM_3]);
    return ERROR_CODE_NO_ERROR;
}

void ResetBorderColor(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetBorderColor(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetBorderColor(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    ArkUI_Uint32 colors[NUM_4];
    fullImpl->getNodeModifiers()->getCommonModifier()->getBorderColor(node->uiNodeHandle, colors);
    g_numberValues[NUM_0].u32 = colors[NUM_0];
    g_numberValues[NUM_1].u32 = colors[NUM_1];
    g_numberValues[NUM_2].u32 = colors[NUM_2];
    g_numberValues[NUM_3].u32 = colors[NUM_3];
    return &g_attributeItem;
}

int32_t SetBorderStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    int styles[ALLOW_SIZE_4] = { 0, 0, 0, 0 };
    if (item->size == 1) {
        if (item->value[0].f32 < ArkUI_BorderStyle::ARKUI_BORDER_STYLE_SOLID ||
            item->value[0].f32 > ArkUI_BorderStyle::ARKUI_BORDER_STYLE_DOTTED) {
            return ERROR_CODE_PARAM_INVALID;
        }
        for (int i = 0; i < ALLOW_SIZE_4; ++i) {
            styles[i] = item->value[0].i32;
        }
        fullImpl->getNodeModifiers()->getCommonModifier()->setBorderStyle(node->uiNodeHandle, styles, ALLOW_SIZE_4);
    } else if (item->size == ALLOW_SIZE_4) {
        for (int i = 0; i < ALLOW_SIZE_4; ++i) {
            if (item->value[i].f32 < ArkUI_BorderStyle::ARKUI_BORDER_STYLE_SOLID ||
                item->value[i].f32 > ArkUI_BorderStyle::ARKUI_BORDER_STYLE_DOTTED) {
                return ERROR_CODE_PARAM_INVALID;
            } else {
                styles[i] = item->value[i].i32;
            }
        }
        fullImpl->getNodeModifiers()->getCommonModifier()->setBorderStyle(node->uiNodeHandle, styles, ALLOW_SIZE_4);
    } else {
        return ERROR_CODE_PARAM_INVALID;
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetBorderStyle(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetBorderStyle(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetBorderStyle(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    ArkUI_Int32 styles[NUM_4];
    fullImpl->getNodeModifiers()->getCommonModifier()->getBorderStyle(node->uiNodeHandle, styles);
    g_numberValues[NUM_0].i32 = styles[NUM_0];
    g_numberValues[NUM_1].i32 = styles[NUM_1];
    g_numberValues[NUM_2].i32 = styles[NUM_2];
    g_numberValues[NUM_3].i32 = styles[NUM_3];
    return &g_attributeItem;
}

int32_t SetZIndex(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setZIndex(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetZIndex(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetZIndex(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetZIndex(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].i32 = modifier->getZIndex(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetVisibility(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < ArkUI_Visibility::ARKUI_VISIBILITY_HIDDEN ||
        item->value[0].i32 > ArkUI_Visibility::ARKUI_VISIBILITY_NONE) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setVisibility(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetVisibility(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetVisibility(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetVisibility(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].i32 = modifier->getVisibility(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetClip(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < NUM_0 || item->value[0].i32 > NUM_1) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setClip(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetClip(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetClip(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetClip(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].i32 = modifier->getClip(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetClipShape(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    if (item->value[0].i32 == ArkUI_ClipType::ARKUI_CLIP_TYPE_PATH) {
        ArkUI_Float32 pathAttributes[NUM_2];
        if (LessNotEqual(item->value[NUM_1].f32, 0.0f) || LessNotEqual(item->value[NUM_2].f32, 0.0f)) {
            return ERROR_CODE_PARAM_INVALID;
        } else {
            pathAttributes[NUM_0] = item->value[NUM_1].f32;
            pathAttributes[NUM_1] = item->value[NUM_2].f32;
        }

        fullImpl->getNodeModifiers()->getCommonModifier()->setClipPath(
            node->uiNodeHandle, "path", pathAttributes, item->string);
    } else {
        ArkUI_Float32 attributes[item->size - NUM_1];
        for (int i = NUM_1; i < item->size; i++) {
            if (LessNotEqual(item->value[i].f32, 0.0f)) {
                return ERROR_CODE_PARAM_INVALID;
            } else {
                attributes[i - NUM_1] = item->value[i].f32;
            }
        }
        fullImpl->getNodeModifiers()->getCommonModifier()->setClipShape(
            node->uiNodeHandle, ShapeToString(item->value[0].i32).c_str(), attributes, item->size - NUM_1);
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetClipShape(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetClip(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetClipShape(ArkUI_NodeHandle node)
{
    ArkUIClipShapeOptions options;
    GetFullImpl()->getNodeModifiers()->getCommonModifier()->getClipShape(node->uiNodeHandle, &options);
    g_numberValues[NUM_0].i32 = options.type;
    if (g_numberValues[NUM_0].i32 == ArkUI_ClipType::ARKUI_CLIP_TYPE_RECT) {
        g_numberValues[NUM_1].f32 = options.width;
        g_numberValues[NUM_2].f32 = options.height;
        g_numberValues[NUM_3].f32 = options.radiusWidth;
        g_numberValues[NUM_4].f32 = options.radiusHeight;
    } else if (g_numberValues[NUM_0].i32 == ArkUI_ClipType::ARKUI_CLIP_TYPE_CIRCLE ||
               g_numberValues[NUM_0].i32 == ArkUI_ClipType::ARKUI_CLIP_TYPE_ELLIPSE) {
        g_numberValues[NUM_1].f32 = options.width;
        g_numberValues[NUM_2].f32 = options.height;
    } else {
        g_numberValues[NUM_1].f32 = options.width;
        g_numberValues[NUM_2].f32 = options.height;
        g_attributeItem.string = options.commands;
    }
    return &g_attributeItem;
}

int32_t SetTransform(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    float transforms[ALLOW_SIZE_16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
    for (int i = 0; i < item->size; ++i) {
        transforms[i] = item->value[i].f32;
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setTransform(node->uiNodeHandle, transforms, ALLOW_SIZE_16);
    return ERROR_CODE_NO_ERROR;
}

void ResetTransform(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetTransform(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetTransform(ArkUI_NodeHandle node)
{
    ArkUI_Float32 values[NUM_16];
    GetFullImpl()->getNodeModifiers()->getCommonModifier()->getTransform(node->uiNodeHandle, values);
    for (int i = 0; i < NUM_16; i++) {
        g_numberValues[i].f32 = values[i];
    }
    return &g_attributeItem;
}

int32_t SetHitTestBehavior(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < ArkUI_HitTestMode::ARKUI_HIT_TEST_MODE_DEFAULT ||
        item->value[0].i32 > ArkUI_HitTestMode::ARKUI_HIT_TEST_MODE_NONE) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setHitTestBehavior(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetHitTestBehavior(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetHitTestBehavior(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetHitTestBehavior(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].i32 = modifier->getHitTestBehavior(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetPosition(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 && item->size != ALLOW_SIZE_2) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (LessNotEqual(item->value[0].f32, 0.0f) || LessNotEqual(item->value[1].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    float positions[ALLOW_SIZE_4] = { 0, 1, 0, 1 };
    positions[NUM_0] = item->value[0].f32;
    positions[NUM_2] = item->value[1].f32;
    fullImpl->getNodeModifiers()->getCommonModifier()->setPosition(
        node->uiNodeHandle, positions[NUM_0], positions[NUM_1], positions[NUM_2], positions[NUM_3]);
    return ERROR_CODE_NO_ERROR;
}

void ResetPosition(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetPosition(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetPosition(ArkUI_NodeHandle node)
{
    ArkUIPositionOptions options;
    GetFullImpl()->getNodeModifiers()->getCommonModifier()->getPosition(node->uiNodeHandle, &options);
    g_numberValues[NUM_0].f32 = options.x;
    g_numberValues[NUM_1].f32 = options.y;
    return &g_attributeItem;
}

int32_t SetShadow(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < ArkUI_ShadowStyle::ARKUI_SHADOW_STYLE_OUTER_DEFAULT_XS ||
        item->value[0].i32 > ArkUI_ShadowStyle::ARKUI_SHADOW_STYLE_OUTER_FLOATING_MD) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    ArkUI_Float32 shadows[NUM_1] = { ArkUI_ShadowStyle::ARKUI_SHADOW_STYLE_OUTER_DEFAULT_XS };
    shadows[NUM_0] = item->value[0].i32;
    fullImpl->getNodeModifiers()->getCommonModifier()->setBackShadow(node->uiNodeHandle, shadows, ALLOW_SIZE_1);
    return ERROR_CODE_NO_ERROR;
}

void ResetShadow(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetBackShadow(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetShadow(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].i32 = modifier->getShadow(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetCustomShadow(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    ArkUI_Float32 shadows[ALLOW_SIZE_7] = { 0, NUM_2, 0, 0, 0, StringToColorInt("#FFFFFFFF", 0), 0 };
    int length = item->size;
    if (length > NUM_0) {
        if (LessNotEqual(item->value[NUM_0].f32, 0.0f)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        shadows[NUM_0] = item->value[NUM_0].f32; // radius
    }
    if (length > NUM_2) {
        if (LessNotEqual(item->value[NUM_2].f32, 0.0f)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        shadows[NUM_2] = item->value[NUM_2].f32; // OffsetX
    }
    if (length > NUM_3) {
        if (LessNotEqual(item->value[NUM_3].f32, 0.0f)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        shadows[NUM_3] = item->value[NUM_3].f32; // OffsetY
    }
    if (length > NUM_4) {
        if (item->value[NUM_3].i32 < ArkUI_ShadowType::ARKUI_SHADOW_TYPE_COLOR ||
            item->value[NUM_3].i32 > ArkUI_ShadowType::ARKUI_SHADOW_TYPE_BLUR) {
            return ERROR_CODE_PARAM_INVALID;
        }
        shadows[NUM_4] = item->value[NUM_4].i32;
    }
    if (length > NUM_5) {
        if (item->value[NUM_1].i32) {
            if (item->value[NUM_5].i32 < ArkUI_ColorStrategy::ARKUI_COLOR_STRATEGY_INVERT ||
                item->value[NUM_5].i32 > ArkUI_ColorStrategy::ARKUI_COLOR_STRATEGY_PRIMARY) {
                return ERROR_CODE_PARAM_INVALID;
            }
            shadows[NUM_1] = COLOR_STRATEGY_STYLE;
            shadows[NUM_5] = item->value[NUM_5].i32;
        } else {
            shadows[NUM_1] = COLOR_STYLE;
            shadows[NUM_5] = item->value[NUM_5].u32;
        }
    }
    if (length > NUM_6) {
        shadows[NUM_6] = item->value[NUM_6].i32;
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setBackShadow(node->uiNodeHandle, shadows, ALLOW_SIZE_7);
    return ERROR_CODE_NO_ERROR;
}

void ResetCustomShadow(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetBackShadow(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetCustomShadow(ArkUI_NodeHandle node)
{
    ArkUICustomShadowOptions options;
    GetFullImpl()->getNodeModifiers()->getCommonModifier()->getCustomShadow(node->uiNodeHandle, &options);
    g_numberValues[NUM_0].i32 = options.radius;
    g_numberValues[NUM_1].f32 = options.offsetX;
    g_numberValues[NUM_2].f32 = options.offsetY;
    g_numberValues[NUM_3].i32 = options.shadowType;
    g_numberValues[NUM_4].u32 = options.color;
    g_numberValues[NUM_5].i32 = options.colorStrategy;
    g_numberValues[NUM_6].i32 = options.fill;
    return &g_attributeItem;
}

int32_t SetFocusable(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !CheckAttributeIsBool(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setFocusable(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetFocusable(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getCommonModifier()->getFocusable(node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

void ResetFocusable(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetFocusable(node->uiNodeHandle);
}

int32_t SetAccessibilityGroup(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !CheckAttributeIsBool(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setAccessibilityGroup(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetAccessibilityGroup(ArkUI_NodeHandle node)
{
    auto resultValue =
        GetFullImpl()->getNodeModifiers()->getCommonModifier()->getAccessibilityGroup(node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

void ResetAccessibilityGroup(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetAccessibilityGroup(node->uiNodeHandle);
}

int32_t SetAccessibilityText(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->string == nullptr) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setAccessibilityText(node->uiNodeHandle, item->string);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetAccessibilityText(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getCommonModifier()->getAccessibilityText(node->uiNodeHandle);
    g_attributeItem.string = resultValue;
    g_attributeItem.size = 0;
    return &g_attributeItem;
}

void ResetAccessibilityText(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetAccessibilityText(node->uiNodeHandle);
}

int32_t SetAccessibilityLevel(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 && !CheckAttributeIsAccessibilityLevel(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    auto levelString = ACCESSIBILITY_LEVEL_VECTOR[item->value[0].i32];
    fullImpl->getNodeModifiers()->getCommonModifier()->setAccessibilityLevel(node->uiNodeHandle, levelString.c_str());
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetAccessibilityLevel(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getCommonModifier()->getAccessibilityLevel(
        node->uiNodeHandle);
    std::string levelString(resultValue);
    g_numberValues[0].i32 = ACCESSIBILITY_LEVEL_MAP[levelString];
    return &g_attributeItem;
}

void ResetAccessibilityLevel(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetAccessibilityLevel(node->uiNodeHandle);
}

int32_t SetAccessibilityDescription(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->string == nullptr) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setAccessibilityDescription(node->uiNodeHandle, item->string);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetAccessibilityDescription(ArkUI_NodeHandle node)
{
    auto resultValue =
        GetFullImpl()->getNodeModifiers()->getCommonModifier()->getAccessibilityDescription(node->uiNodeHandle);
    g_attributeItem.string = resultValue;
    g_attributeItem.size = 0;
    return &g_attributeItem;
}

void ResetAccessibilityDescription(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetAccessibilityDescription(node->uiNodeHandle);
}

int32_t SetDefaultFocus(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !CheckAttributeIsBool(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setDefaultFocus(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetDefaultFocus(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getCommonModifier()->getDefaultFocus(node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

void ResetDefaultFocus(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetDefaultFocus(node->uiNodeHandle);
}

int32_t SetResponseRegion(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || item->size % NUM_4 > 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();

    std::vector<float> valuesArray;
    std::vector<int> unitsArray;

    for (int i = 0; i < item->size; i++) {
        int remainder = i % NUM_4;
        valuesArray.push_back(remainder > 1 ? (item->value[i].f32) / HUNDRED : item->value[i].f32);
        // unit 1 3
        unitsArray.push_back(remainder > 1 ? NUM_3 : NUM_1);
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setResponseRegion(
        node->uiNodeHandle, valuesArray.data(), unitsArray.data(), valuesArray.size());
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetResponseRegion(ArkUI_NodeHandle node)
{
    ArkUI_Float32 values[32];
    auto valueSize =
        GetFullImpl()->getNodeModifiers()->getCommonModifier()->getResponseRegion(node->uiNodeHandle, values);
    for (int i = 0; i < valueSize; i++) {
        g_numberValues[i].f32 = values[i];
    }
    
    g_attributeItem.size = valueSize;
    return &g_attributeItem;
}

void ResetResponseRegion(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetResponseRegion(node->uiNodeHandle);
}

int32_t SetOverlay(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->string == nullptr) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();

    ArkUI_Float32 values[ALLOW_SIZE_10] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

    if (item->size > 0) {
        values[0] = 1;
        if (!CheckAttributeIsAlignment(item->value[0].i32)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        values[1] = item->value[0].i32;
    }

    if (item->size > 1) {
        values[2] = 1;
        values[3] = item->value[1].f32;
        values[4] = UNIT_VP;
    }

    if (item->size > 2) {
        values[5] = 1;
        values[6] = item->value[2].f32;
        values[7] = UNIT_VP;
    }
    values[8] = item->size > 0 ? 1 : 0;
    values[9] = item->size > 1 ? 1 : 0;
    fullImpl->getNodeModifiers()->getCommonModifier()->setOverlay(
        node->uiNodeHandle, item->string, values, ALLOW_SIZE_10);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetOverlay(ArkUI_NodeHandle node)
{
    ArkUIOverlayOptions options;
    auto contentStr = GetFullImpl()->getNodeModifiers()->getCommonModifier()->getOverlay(
        node->uiNodeHandle, &options);
    g_attributeItem.string = contentStr;
    int index = 0;
    //index 0 : align
    g_numberValues[index++].i32 = options.align;
    //index 1 : offset x
    g_numberValues[index++].f32 = options.x;
    //index 2 : offset y
    g_numberValues[index++].f32 = options.y;
    g_attributeItem.size = index;
    return &g_attributeItem;
}

void ResetOverlay(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetOverlay(node->uiNodeHandle);
}

int32_t SetBackgroundImagePosition(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_TWO_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    ArkUI_Float32 values[] = { item->value[NUM_0].f32, item->value[NUM_1].f32 };
    ArkUI_Int32 units[] = { DEFAULT_UNIT, DEFAULT_UNIT };

    fullImpl->getNodeModifiers()->getCommonModifier()->setBackgroundImagePosition(
        node->uiNodeHandle, values, units, false, NUM_2);
    return ERROR_CODE_NO_ERROR;
}

void ResetBackgroundImagePosition(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getCommonModifier()->resetBackgroundImagePosition(node->uiNodeHandle);
}

int32_t SetSweepGradient(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->object == nullptr) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    const ArkUI_ColorStop* colorStop = reinterpret_cast<ArkUI_ColorStop*>(item->object);
    int size = colorStop->size;
    ArkUI_Float32 colors[size * NUM_3];
    for (int i = 0; i < size; i++) {
        colors[i * NUM_3 + NUM_0] = colorStop->colors[i];
        colors[i * NUM_3 + NUM_1] = true;
        colors[i * NUM_3 + NUM_2] = colorStop->stops[i];
    }
    ArkUI_Float32 values[NUM_13] = { false, DEFAULT_X, UNIT_VP, false, DEFAULT_Y, UNIT_VP, false, NUM_0, false, NUM_0,
        false, NUM_0, false };
    if (item->size > NUM_0) {
        values[NUM_0] = true;
        values[NUM_1] = item->value[NUM_0].f32;
    }

    if (item->size > NUM_1) {
        values[NUM_3] = true;
        values[NUM_4] = item->value[NUM_1].f32;
    }

    if (item->size > NUM_2) {
        values[NUM_6] = true;
        values[NUM_7] = item->value[NUM_2].f32;
    }

    if (item->size > NUM_3) {
        values[NUM_8] = true;
        values[NUM_9] = item->value[NUM_3].f32;
    }

    if (item->size > NUM_4) {
        values[NUM_10] = true;
        values[NUM_11] = item->value[NUM_4].f32;
    }

    values[NUM_12] = (item->size > NUM_5) ? item->value[NUM_5].i32 : false;
    fullImpl->getNodeModifiers()->getCommonModifier()->setSweepGradient(
        node->uiNodeHandle, values, NUM_13, colors, size * NUM_3);
    return ERROR_CODE_NO_ERROR;
}

void ResetSweepGradient(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetSweepGradient(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetSweepGradient(ArkUI_NodeHandle node)
{
    ArkUISweepGradientOptions options;
    static ArkUI_ColorStop colorStops;
    GetFullImpl()->getNodeModifiers()->getCommonModifier()->getSweepGradient(node->uiNodeHandle, &options);
    colorStops.colors = options.colors;
    colorStops.stops = options.dimensions;
    colorStops.size = options.colorSize;
    g_numberValues[NUM_0].f32 = options.ceneterX;
    g_numberValues[NUM_1].f32 = options.ceneterX;
    g_numberValues[NUM_2].f32 = options.startAngle;
    g_numberValues[NUM_3].f32 = options.endAngle;
    g_numberValues[NUM_4].f32 = options.rotation;
    g_numberValues[NUM_5].i32 = options.repeating;
    g_attributeItem.object = reinterpret_cast<void*>(&colorStops);
    return &g_attributeItem;
}

int32_t SetRadialGradient(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->object == nullptr) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    const ArkUI_ColorStop* colorStop = reinterpret_cast<ArkUI_ColorStop*>(item->object);
    int size = colorStop->size;
    ArkUI_Float32 colors[size * NUM_3];
    for (int i = 0; i < size; i++) {
        colors[i * NUM_3 + NUM_0] = colorStop->colors[i];
        colors[i * NUM_3 + NUM_1] = true;
        colors[i * NUM_3 + NUM_2] = colorStop->stops[i];
    }

    ArkUI_Float32 values[NUM_10] = { false, DEFAULT_X, UNIT_VP, false, DEFAULT_Y, UNIT_VP, false, NUM_0, UNIT_VP,
        false };
    if (item->size > NUM_0) {
        values[NUM_0] = true;
        values[NUM_1] = item->value[NUM_0].f32;
    }

    if (item->size > NUM_1) {
        values[NUM_3] = true;
        values[NUM_4] = item->value[NUM_1].f32;
    }

    if (item->size > NUM_2) {
        values[NUM_6] = true;
        values[NUM_7] = item->value[NUM_2].f32;
    }

    values[NUM_9] = (item->size > NUM_4) ? item->value[NUM_3].i32 : false;

    fullImpl->getNodeModifiers()->getCommonModifier()->setRadialGradient(
        node->uiNodeHandle, values, NUM_10, colors, size * NUM_3);
    return ERROR_CODE_NO_ERROR;
}

void ResetRadialGradient(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetRadialGradient(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetRadialGradient(ArkUI_NodeHandle node)
{
    ArkUIRadialGradientOptions options;
    static ArkUI_ColorStop colorStops;
    GetFullImpl()->getNodeModifiers()->getCommonModifier()->getRadialGradient(node->uiNodeHandle, &options);
    colorStops.colors = options.colors;
    colorStops.stops = options.dimensions;
    colorStops.size = options.colorSize;
    g_numberValues[NUM_0].f32 = options.ceneterX;
    g_numberValues[NUM_1].f32 = options.ceneterY;
    g_numberValues[NUM_2].f32 = options.radius;
    g_numberValues[NUM_3].i32 = options.repeating;
    g_attributeItem.object = reinterpret_cast<void*>(&colorStops);
    return &g_attributeItem;
}

int32_t SetMask(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    if (item->value[NUM_3].i32 == ArkUI_MaskType::ARKUI_MASK_TYPE_PATH) {
        int fill = item->size > NUM_0 ? item->value[0].u32 : DEFAULT_FIll_COLOR;
        int strock = item->size > NUM_1 ? item->value[NUM_1].u32 : DEFAULT_FIll_COLOR;
        float strockWidth = item->size > NUM_2 ? item->value[NUM_2].f32 : NUM_0;
        ArkUI_Float32 pathAttributes[NUM_2];
        if (LessNotEqual(item->value[NUM_4].f32, 0.0f) || LessNotEqual(item->value[NUM_5].f32, 0.0f)) {
            return ERROR_CODE_PARAM_INVALID;
        } else {
            pathAttributes[NUM_0] = item->value[NUM_4].f32;
            pathAttributes[NUM_1] = item->value[NUM_5].f32;
        }
        fullImpl->getNodeModifiers()->getCommonModifier()->setMaskPath(
            node->uiNodeHandle, "path", fill, strock, strockWidth, pathAttributes, item->string);
    } else if (item->value[0].i32 == ArkUI_MaskType::ARKUI_MASK_TYPE_PROGRESS) {
        ArkUI_Float32 progressAttributes[NUM_3];
        for (int i = 0; i < NUM_3; i++) {
            progressAttributes[i] = item->value[i].f32;
        }
        uint32_t color = item->value[NUM_3].u32;
        fullImpl->getNodeModifiers()->getCommonModifier()->setProgressMask(
            node->uiNodeHandle, progressAttributes, color);
    } else {
        int fill = item->size > NUM_0 ? item->value[0].u32 : DEFAULT_FIll_COLOR;
        int strock = item->size > NUM_1 ? item->value[NUM_1].u32 : DEFAULT_FIll_COLOR;
        float strockWidth = item->size > NUM_2 ? item->value[NUM_2].f32 : NUM_0;
        ArkUI_Float32 attributes[item->size - NUM_4];
        for (int i = 0; i < item->size - NUM_4; i++) {
            if (LessNotEqual(item->value[i + NUM_4].f32, 0.0f)) {
                return ERROR_CODE_PARAM_INVALID;
            } else {
                attributes[i] = item->value[i + NUM_4].f32;
            }
        }
        fullImpl->getNodeModifiers()->getCommonModifier()->setMaskShape(node->uiNodeHandle,
            ShapeToString(item->value[NUM_3].i32).c_str(), fill, strock, strockWidth, attributes, item->size - NUM_4);
    }
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetMask(ArkUI_NodeHandle node)
{
    ArkUIMaskOptions options;
    GetFullImpl()->getNodeModifiers()->getCommonModifier()->getMask(node->uiNodeHandle, &options);
    if (static_cast<ShapeType>(options.type) == ShapeType::RECT) {
        g_numberValues[NUM_0].u32 = options.fill;
        g_numberValues[NUM_1].u32 = options.strockColor;
        g_numberValues[NUM_2].f32 = options.strockWidth;
        g_numberValues[NUM_3].i32 = options.type;
        g_numberValues[NUM_4].f32 = options.width;
        g_numberValues[NUM_5].f32 = options.height;
        g_numberValues[NUM_6].f32 = options.radiusWidth;
        g_numberValues[NUM_7].f32 = options.radiusHeight;
    } else if (static_cast<ShapeType>(options.type) == ShapeType::CIRCLE) {
        g_numberValues[NUM_0].u32 = options.fill;
        g_numberValues[NUM_1].u32 = options.strockColor;
        g_numberValues[NUM_2].f32 = options.strockWidth;
        g_numberValues[NUM_3].i32 = options.type;
        g_numberValues[NUM_4].f32 = options.width;
        g_numberValues[NUM_5].f32 = options.height;
    } else if (static_cast<ShapeType>(options.type) == ShapeType::ELLIPSE) {
        g_numberValues[NUM_0].u32 = options.fill;
        g_numberValues[NUM_1].u32 = options.strockColor;
        g_numberValues[NUM_2].f32 = options.strockWidth;
        g_numberValues[NUM_3].i32 = options.type;
        g_numberValues[NUM_4].f32 = options.width;
        g_numberValues[NUM_5].f32 = options.height;
    } else if (static_cast<ShapeType>(options.type) == ShapeType::PATH) {
        g_numberValues[NUM_0].u32 = options.fill;
        g_numberValues[NUM_1].u32 = options.strockColor;
        g_numberValues[NUM_2].f32 = options.strockWidth;
        g_numberValues[NUM_3].i32 = options.type;
        g_numberValues[NUM_4].f32 = options.width;
        g_numberValues[NUM_5].f32 = options.height;
        g_attributeItem.string = options.commands;
    } else {
        g_numberValues[NUM_0].i32 = options.type;
        g_numberValues[NUM_1].f32 = options.value;
        g_numberValues[NUM_2].f32 = options.maxValue;
    }
    return &g_attributeItem;
}

int32_t SetBlendMode(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[NUM_0].i32 < ArkUI_BlendMode::ARKUI_BLEND_MODE_NONE ||
        item->value[NUM_0].i32 > ArkUI_BlendMode::ARKUI_BLEND_MODE_LUMINOSITY) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setBlendMode(node->uiNodeHandle, item->value[0].i32, 0);
    return ERROR_CODE_NO_ERROR;
}

void ResetBlendMode(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetBlendMode(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetBlendMode(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].i32 = modifier->getBlendMode(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetDirection(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < ArkUI_Direction::ARKUI_DIRECTION_LTR ||
        item->value[0].i32 > ArkUI_Direction::ARKUI_DIRECTION_AUTO) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setDirection(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetDirection(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetDirection(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetDirection(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].i32 = modifier->getDirection(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetAlignSelf(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < ArkUI_ItemAlign::ARKUI_ITEM_ALIGN_AUTO ||
        item->value[0].i32 > ArkUI_ItemAlign::ARKUI_ITEM_ALIGN_BASELINE) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setAlignSelf(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetAlignSelf(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetAlignSelf(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetAlignSelf(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].i32 = modifier->getAlignSelf(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetFlexGrow(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (LessNotEqual(item->value[0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setFlexGrow(node->uiNodeHandle, item->value[0].f32);
    return ERROR_CODE_NO_ERROR;
}

void ResetFlexGrow(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetFlexGrow(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetFlexGrow(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].f32 = modifier->getFlexGrow(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetFlexShrink(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (LessNotEqual(item->value[0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setFlexShrink(node->uiNodeHandle, item->value[0].f32);
    return ERROR_CODE_NO_ERROR;
}

void ResetFlexShrink(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetFlexShrink(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetFlexShrink(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].f32 = modifier->getFlexShrink(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetFlexBasis(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (LessNotEqual(item->value[0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    struct ArkUIStringAndFloat basis = { item->value[0].f32, nullptr };
    fullImpl->getNodeModifiers()->getCommonModifier()->setFlexBasis(node->uiNodeHandle, &basis);
    return ERROR_CODE_NO_ERROR;
}

void ResetFlexBasis(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetFlexBasis(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetFlexBasis(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].f32 = modifier->getFlexBasis(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetConstraintSize(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || item->size != ALLOW_SIZE_4) {
        return ERROR_CODE_PARAM_INVALID;
    }

    auto* fullImpl = GetFullImpl();
    ArkUI_Float32 constraintSize[ALLOW_SIZE_4] = { 0.0f, FLT_MAX, 0.0f, FLT_MAX };
    ArkUI_Int32 units[ALLOW_SIZE_4] = { UNIT_VP, UNIT_VP, UNIT_VP, UNIT_VP };

    if (item->size == 1) {
        if (LessNotEqual(item->value[0].f32, 0.0f)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        constraintSize[NUM_0] = item->value[NUM_0].f32;
        constraintSize[NUM_1] = item->value[NUM_0].f32;
        constraintSize[NUM_2] = item->value[NUM_0].f32;
        constraintSize[NUM_3] = item->value[NUM_0].f32;
    } else if (item->size == ALLOW_SIZE_4) {
        for (int i = 0; i < ALLOW_SIZE_4; ++i) {
            if (LessNotEqual(item->value[0].f32, 0.0f)) {
                return ERROR_CODE_PARAM_INVALID;
            } else {
                constraintSize[i] = item->value[i].f32;
            }
        }
    } else {
        return ERROR_CODE_PARAM_INVALID;
    }

    fullImpl->getNodeModifiers()->getCommonModifier()->setConstraintSize(node->uiNodeHandle, constraintSize, units);
    return ERROR_CODE_NO_ERROR;
}

void ResetConstraintSize(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetConstraintSize(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetConstraintSize(ArkUI_NodeHandle node)
{
    ArkUIConstraintSizeOptions options;
    GetFullImpl()->getNodeModifiers()->getCommonModifier()->getConstraintSize(node->uiNodeHandle, &options);
    g_numberValues[NUM_0].f32 = options.minWidth;
    g_numberValues[NUM_1].f32 = options.maxWidth;
    g_numberValues[NUM_2].f32 = options.minHeight;
    g_numberValues[NUM_3].f32 = options.maxWidth;
    return &g_attributeItem;
}

int32_t SetGrayscale(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (LessNotEqual(item->value[0].f32, 0.0f) || GreatNotEqual(item->value[0].f32, 1.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setGrayscale(node->uiNodeHandle, item->value[0].f32);
    return ERROR_CODE_NO_ERROR;
}

void ResetGrayscale(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetGrayscale(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetGrayscale(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].f32 = modifier->getGrayscale(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetInvert(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (LessNotEqual(item->value[0].f32, 0.0f) || GreatNotEqual(item->value[0].f32, 1.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setInvert(node->uiNodeHandle, item->value[0].f32);
    return ERROR_CODE_NO_ERROR;
}

void ResetInvert(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetInvert(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetInvert(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].f32 = modifier->getInvert(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetSepia(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (LessNotEqual(item->value[0].f32, 0.0f) || GreatNotEqual(item->value[0].f32, 1.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setSepia(node->uiNodeHandle, item->value[0].f32);
    return ERROR_CODE_NO_ERROR;
}

void ResetSepia(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetSepia(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetSepia(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].f32 = modifier->getSepia(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetContrast(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (LessNotEqual(item->value[0].f32, 0.0f) || GreatOrEqual(item->value[0].f32, 10.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setContrast(node->uiNodeHandle, item->value[0].f32);
    return ERROR_CODE_NO_ERROR;
}

void ResetContrast(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetContrast(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetContrast(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].f32 = modifier->getContrast(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetForegroundColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    bool isColor = true;
    if (item->value[0].i32 == ArkUI_ColorStrategy::ARKUI_COLOR_STRATEGY_INVERT ||
        item->value[0].i32 == ArkUI_ColorStrategy::ARKUI_COLOR_STRATEGY_AVERAGE ||
        item->value[0].i32 == ArkUI_ColorStrategy::ARKUI_COLOR_STRATEGY_PRIMARY) {
        isColor = false;
        fullImpl->getNodeModifiers()->getCommonModifier()->setForegroundColor(
            node->uiNodeHandle, isColor, item->value[0].i32);
    } else {
        isColor = true;
        fullImpl->getNodeModifiers()->getCommonModifier()->setForegroundColor(
            node->uiNodeHandle, isColor, item->value[0].u32);
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetForegroundColor(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetForegroundColor(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetForegroundColor(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].u32 = modifier->getForegroundColor(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetNeedFocus(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !CheckAttributeIsBool(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getCommonModifier()->setNeedFocus(
        node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetNeedFocus(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getCommonModifier()->getNeedFocus(node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

int32_t SetFontColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == NUM_0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_TEXT_INPUT:
            fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputFontColor(
                node->uiNodeHandle, item->value[0].u32);
            break;
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->setFontColor(node->uiNodeHandle, item->value[0].u32);
            break;
        case ARKUI_NODE_SPAN:
            fullImpl->getNodeModifiers()->getSpanModifier()->setSpanFontColor(node->uiNodeHandle, item->value[0].u32);
            break;
        case ARKUI_NODE_BUTTON:
            fullImpl->getNodeModifiers()->getButtonModifier()->setButtonFontColor(
                node->uiNodeHandle, item->value[0].u32);
            break;
        default:
            return ERROR_CODE_PARAM_INVALID;
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetFontColor(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT) {
        fullImpl->getNodeModifiers()->getTextModifier()->resetFontColor(node->uiNodeHandle);
    }
}

int32_t SetFontWeight(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || item->value[NUM_0].i32 < 0 ||
        item->value[NUM_0].i32 > static_cast<int32_t>(ARKUI_FONT_WEIGHT_REGULAR)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_TEXT_INPUT:
            fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputFontWeight(
                node->uiNodeHandle, item->value[0].i32);
            break;
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->setFontWeight(node->uiNodeHandle, item->value[0].i32);
            break;
        case ARKUI_NODE_SPAN:
            fullImpl->getNodeModifiers()->getSpanModifier()->setSpanFontWeight(node->uiNodeHandle, item->value[0].i32);
            break;
        case ARKUI_NODE_BUTTON:
            fullImpl->getNodeModifiers()->getButtonModifier()->setButtonFontWeightEnum(node->uiNodeHandle,
                item->value[0].i32);
            break;
        default:
            return ERROR_CODE_PARAM_INVALID;
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetFontWeight(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT) {
        fullImpl->getNodeModifiers()->getTextModifier()->resetFontWeight(node->uiNodeHandle);
    }
}

int32_t SetFontSize(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || LessNotEqual(item->value[NUM_0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT_INPUT) {
        struct ArkUILengthType fontSize = { nullptr, item->value[0].f32, UNIT_FP };
        fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputFontSize(node->uiNodeHandle, &fontSize);
    } else if (node->type == ARKUI_NODE_TEXT) {
        fullImpl->getNodeModifiers()->getTextModifier()->setFontSize(node->uiNodeHandle, item->value[0].f32, UNIT_FP);
    } else if (node->type == ARKUI_NODE_SPAN) {
        fullImpl->getNodeModifiers()->getSpanModifier()->setSpanFontSize(
            node->uiNodeHandle, item->value[0].f32, UNIT_FP);
    } else if (node->type == ARKUI_NODE_BUTTON) {
        fullImpl->getNodeModifiers()->getButtonModifier()->setButtonFontSize(node->uiNodeHandle,
            item->value[0].f32, UNIT_FP);
    } else {
        return ERROR_CODE_PARAM_INVALID;
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetFontSize(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT) {
        fullImpl->getNodeModifiers()->getTextModifier()->resetFontSize(node->uiNodeHandle);
    }
}

int32_t SetFontStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || item->value[NUM_0].i32 < 0 ||
        item->value[NUM_0].i32 > static_cast<int32_t>(ARKUI_FONT_STYLE_ITALIC)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_TEXT_INPUT:
            fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputFontStyle(
                node->uiNodeHandle, item->value[0].i32);
            break;
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->setFontStyle(node->uiNodeHandle, item->value[0].i32);
            break;
        case ARKUI_NODE_SPAN:
            fullImpl->getNodeModifiers()->getSpanModifier()->setSpanFontStyle(node->uiNodeHandle, item->value[0].i32);
            break;
        default:
            return ERROR_CODE_PARAM_INVALID;
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetFontStyle(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT) {
        fullImpl->getNodeModifiers()->getTextModifier()->resetFontStyle(node->uiNodeHandle);
    }
}

int32_t SetTextInputPlaceholder(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputPlaceholderString(
        node->uiNodeHandle, item->string);
    return ERROR_CODE_NO_ERROR;
}

void ResetTextInputPlaceholder(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputPlaceholderString(node->uiNodeHandle, "");
}

int32_t SetTextInputText(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputTextString(node->uiNodeHandle, item->string);
    return ERROR_CODE_NO_ERROR;
}

void ResetTextInputText(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputTextString(node->uiNodeHandle, "");
}

int32_t SetCaretColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT_INPUT) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputCaretColor(
            node->uiNodeHandle, item->value[NUM_0].u32);
    } else if (node->type == ARKUI_NODE_TEXT_AREA) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaCaretColor(
            node->uiNodeHandle, item->value[NUM_0].u32);
    } else {
        return ERROR_CODE_PARAM_INVALID;
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetCaretColor(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_TEXT_INPUT:
            fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputCaretColor(node->uiNodeHandle);
            break;
        case ARKUI_NODE_TEXT_AREA:
            fullImpl->getNodeModifiers()->getTextAreaModifier()->resetTextAreaCaretColor(node->uiNodeHandle);
            break;
        default:
            break;
    }
}

int32_t SetCaretStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || LessNotEqual(item->value[NUM_0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    struct ArkUILengthType width = { nullptr, item->value[NUM_0].f32, DEFAULT_UNIT };
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputCaretStyle(node->uiNodeHandle, &width);
    return ERROR_CODE_NO_ERROR;
}

void ResetCaretStyle(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputCaretStyle(node->uiNodeHandle);
}

int32_t SetShowUnderline(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || item->value[NUM_0].i32 < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputShowUnderline(
        node->uiNodeHandle, item->value[NUM_0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetShowUnderline(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputShowUnderline(node->uiNodeHandle);
}

int32_t SetMaxLength(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || item->value[NUM_0].i32 < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT_INPUT) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputMaxLength(
            node->uiNodeHandle, item->value[NUM_0].i32);
    } else if (node->type == ARKUI_NODE_TEXT_AREA) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaMaxLength(
            node->uiNodeHandle, item->value[NUM_0].i32);
    } else {
        return ERROR_CODE_PARAM_INVALID;
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetMaxLength(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_TEXT_INPUT:
            fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputMaxLength(node->uiNodeHandle);
            break;
        case ARKUI_NODE_TEXT_AREA:
            fullImpl->getNodeModifiers()->getTextAreaModifier()->resetTextAreaMaxLength(node->uiNodeHandle);
            break;
        default:
            break;
    }
}

int32_t SetEnterKeyType(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || item->value[NUM_0].i32 < static_cast<int32_t>(ARKUI_ENTER_KEY_TYPE_GO) ||
        item->value[NUM_0].i32 > static_cast<int32_t>(ARKUI_ENTER_KEY_TYPE_NEW_LINE)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputEnterKeyType(
        node->uiNodeHandle, item->value[NUM_0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetEnterKeyType(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputEnterKeyType(node->uiNodeHandle);
}

int32_t SetPlaceholderColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT_INPUT) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputPlaceholderColor(
            node->uiNodeHandle, item->value[NUM_0].u32);
    } else if (node->type == ARKUI_NODE_TEXT_AREA) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaPlaceholderColor(
            node->uiNodeHandle, item->value[NUM_0].u32);
    } else {
        return ERROR_CODE_PARAM_INVALID;
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetPlaceholderColor(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_TEXT_INPUT:
            fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputPlaceholderColor(node->uiNodeHandle);
            break;
        case ARKUI_NODE_TEXT_AREA:
            fullImpl->getNodeModifiers()->getTextAreaModifier()->resetTextAreaPlaceholderColor(node->uiNodeHandle);
            break;
        default:
            break;
    }
}

int32_t SetTextInputPlaceholderFont(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    struct ArkUILengthType size = { nullptr, 16.0, UNIT_FP };
    if (item->size > NUM_0) {
        if (LessNotEqual(item->value[NUM_0].f32, 0.0f)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        size.number = item->value[NUM_0].f32;
    }
    struct ArkUIPlaceholderFontType palceHolderFont = { &size, nullptr, nullptr, 0,
        ARKUI_FONT_STYLE_NORMAL, ARKUI_FONT_WEIGHT_NORMAL };
    if (item->size > NUM_1) {
        if (item->value[NUM_1].i32 < 0 || item->value[NUM_1].i32 > static_cast<int32_t>(ARKUI_FONT_STYLE_ITALIC)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        palceHolderFont.style = item->value[NUM_1].i32;
    }
    if (item->size > NUM_2) {
        if (item->value[NUM_2].i32 < 0 || item->value[NUM_2].i32 > static_cast<int32_t>(ARKUI_FONT_WEIGHT_REGULAR)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        palceHolderFont.weightEnum = item->value[NUM_2].i32;
    }
    if (item->string) {
        std::vector<std::string> fontFamilies = Framework::ConvertStrToFontFamilies(item->string);
        auto families = std::make_unique<char*[]>(fontFamilies.size());
        for (uint32_t i = 0; i < fontFamilies.size(); i++) {
            families[i] = const_cast<char*>(fontFamilies.at(i).c_str());
        }
        palceHolderFont.fontFamilies = const_cast<const char**>(families.get());
        palceHolderFont.length = fontFamilies.size();
    }
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputPlaceholderFont(
        node->uiNodeHandle, &palceHolderFont);
    return ERROR_CODE_NO_ERROR;
}

void ResetTextInputPlaceholderFont(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputPlaceholderFont(node->uiNodeHandle);
}

int32_t SetEnableKeybordOnFocus(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || item->value[NUM_0].i32 < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputEnableKeyboardOnFocus(
        node->uiNodeHandle, item->value[NUM_0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetEnableKeybordOnFocus(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputEnableKeyboardOnFocus(node->uiNodeHandle);
}

int32_t SetTextInputType(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || item->value[NUM_0].i32 < static_cast<int32_t>(ARKUI_TEXTINPUT_TYPE_NORMAL) ||
        item->value[NUM_0].i32 > static_cast<int32_t>(ARKUI_TEXTINPUT_TYPE_NUMBER_DECIMAL)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputType(
        node->uiNodeHandle, item->value[NUM_0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetTextInputType(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputType(node->uiNodeHandle);
}

int32_t SetSelectedBackgroundColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputSelectedBackgroundColor(
        node->uiNodeHandle, item->value[0].u32);
    return ERROR_CODE_NO_ERROR;
}

void ResetSelectedBackgroundColor(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputSelectedBackgroundColor(node->uiNodeHandle);
}

int32_t SetShowPasswordIcon(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || item->value[NUM_0].i32 < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputShowPasswordIcon(
        node->uiNodeHandle, item->value[NUM_0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetShowPasswordIcon(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputShowPasswordIcon(node->uiNodeHandle);
}

int32_t StopTextInputEditing(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || item->value[NUM_0].i32 < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (item->value[NUM_0].i32 == 0) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->stopTextInputTextEditing(node->uiNodeHandle);
    }
    return ERROR_CODE_NO_ERROR;
}

// Stack Arttribute functions
int32_t SetAlignContent(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !InRegion(NUM_0, NUM_8, item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    auto attrVal = item->value[NUM_0].i32;
    fullImpl->getNodeModifiers()->getStackModifier()->setAlignContent(node->uiNodeHandle, attrVal);
    return ERROR_CODE_NO_ERROR;
}

void ResetAlignContent(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getStackModifier()->resetAlignContent(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetScrollFriction(ArkUI_NodeHandle node)
{
    if (node->type == ARKUI_NODE_LIST) {
        g_numberValues[0].f32 =
            GetFullImpl()->getNodeModifiers()->getListModifier()->getListFriction(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_SCROLL) {
        g_numberValues[0].f32 =
            GetFullImpl()->getNodeModifiers()->getScrollModifier()->getScrollFriction(node->uiNodeHandle);
    }
    return &g_attributeItem;
}

int32_t SetScrollFriction(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || LessOrEqual(item->value[NUM_0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    auto friction = item->value[NUM_0].f32;
    if (node->type == ARKUI_NODE_LIST) {
        fullImpl->getNodeModifiers()->getListModifier()->setListFriction(node->uiNodeHandle, friction);
    } else if (node->type == ARKUI_NODE_SCROLL) {
        fullImpl->getNodeModifiers()->getScrollModifier()->setScrollFriction(node->uiNodeHandle, friction);
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetScrollFriction(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    if (node->type == ARKUI_NODE_LIST) {
        fullImpl->getNodeModifiers()->getListModifier()->resetListFriction(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_SCROLL) {
        fullImpl->getNodeModifiers()->getScrollModifier()->resetScrollFriction(node->uiNodeHandle);
    }
}

int32_t SetScrollScrollSnap(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_FOUR_PARAM);
    if (actualSize < 0 || !InRegion(NUM_0, NUM_3, item->value[NUM_0].i32) ||
        !InRegion(NUM_0, NUM_1, item->value[NUM_1].i32) || !InRegion(NUM_0, NUM_1, item->value[NUM_2].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    auto snapAlign = item->value[NUM_0].i32;
    auto enableSnapToStart = item->value[NUM_1].i32;
    auto enableSnapToEnd = item->value[NUM_2].i32;

    ArkUI_Float32 paginations[item->size - NUM_3];
    ArkUI_Int32 paginationParams[item->size + NUM_1];
    for (int i = 0; i < item->size - NUM_3; ++i) {
        paginations[i] = item->value[i + NUM_3].f32;
        paginationParams[i] = UNIT_VP;
        if (LessNotEqual(item->value[NUM_0].f32, 0.0f)) {
            return ERROR_CODE_PARAM_INVALID;
        }
    }

    paginationParams[item->size - NUM_3 + NUM_0] = snapAlign;
    paginationParams[item->size - NUM_3 + NUM_1] = enableSnapToStart;
    paginationParams[item->size - NUM_3 + NUM_2] = enableSnapToEnd;
    paginationParams[item->size] = (item->size - NUM_3 > 1) ? true : false;

    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollScrollSnap(
        node->uiNodeHandle, paginations, item->size - NUM_3, paginationParams, item->size + NUM_1);
    return ERROR_CODE_NO_ERROR;
}

void ResetScrollScrollSnap(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getScrollModifier()->resetScrollScrollSnap(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetScrollScrollBar(ArkUI_NodeHandle node)
{
    if (node->type == ARKUI_NODE_LIST) {
        g_numberValues[0].i32 =
            GetFullImpl()->getNodeModifiers()->getListModifier()->getListScrollBar(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_SCROLL) {
        g_numberValues[0].i32 =
            GetFullImpl()->getNodeModifiers()->getScrollModifier()->getScrollScrollBar(node->uiNodeHandle);
    }
    return &g_attributeItem;
}

int32_t SetScrollScrollBar(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !InRegion(NUM_0, NUM_2, item->value[NUM_0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    auto attrVal = item->value[NUM_0].i32;
    if (node->type == ARKUI_NODE_LIST) {
        fullImpl->getNodeModifiers()->getListModifier()->setListScrollBar(node->uiNodeHandle, attrVal);
    } else if (node->type == ARKUI_NODE_SCROLL) {
        fullImpl->getNodeModifiers()->getScrollModifier()->setScrollScrollBar(node->uiNodeHandle, attrVal);
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetScrollScrollBar(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    if (node->type == ARKUI_NODE_LIST) {
        fullImpl->getNodeModifiers()->getListModifier()->resetListScrollBar(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_SCROLL) {
        fullImpl->getNodeModifiers()->getScrollModifier()->resetScrollScrollBar(node->uiNodeHandle);
    }
}

const ArkUI_AttributeItem* GetScrollScrollBarWidth(ArkUI_NodeHandle node)
{
    if (node->type == ARKUI_NODE_LIST) {
        g_numberValues[0].f32 =
            GetFullImpl()->getNodeModifiers()->getListModifier()->getListScrollBarWidth(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_SCROLL) {
        g_numberValues[0].f32 =
            GetFullImpl()->getNodeModifiers()->getScrollModifier()->getScrollScrollBarWidth(node->uiNodeHandle);
    }
    return &g_attributeItem;
}

int32_t SetScrollScrollBarWidth(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || LessNotEqual(item->value[NUM_0].f32, NUM_0)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    auto attrVal = item->value[NUM_0].f32;
    if (node->type == ARKUI_NODE_LIST) {
        auto width = std::to_string(attrVal) + "vp";
        fullImpl->getNodeModifiers()->getListModifier()->setListScrollBarWidth(node->uiNodeHandle, width.c_str());
    } else if (node->type == ARKUI_NODE_SCROLL) {
        fullImpl->getNodeModifiers()->getScrollModifier()->setScrollScrollBarWidth(
            node->uiNodeHandle, attrVal, UNIT_VP);
    }
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetScrollScrollBarColor(ArkUI_NodeHandle node)
{
    if (node->type == ARKUI_NODE_LIST) {
        g_numberValues[0].u32 =
            GetFullImpl()->getNodeModifiers()->getListModifier()->getListScrollBarColor(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_SCROLL) {
        g_numberValues[0].u32 =
            GetFullImpl()->getNodeModifiers()->getScrollModifier()->getScrollScrollBarColor(node->uiNodeHandle);
    }
    return &g_attributeItem;
}

int32_t SetScrollScrollBarColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    auto color = item->value[NUM_0].u32;
    if (node->type == ARKUI_NODE_LIST) {
        auto value = Color(color).ColorToString();
        fullImpl->getNodeModifiers()->getListModifier()->setListScrollBarColor(node->uiNodeHandle, value.c_str());
    } else if (node->type == ARKUI_NODE_SCROLL) {
        fullImpl->getNodeModifiers()->getScrollModifier()->setScrollScrollBarColor(node->uiNodeHandle, color);
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetScrollScrollBarColor(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    if (node->type == ARKUI_NODE_LIST) {
        fullImpl->getNodeModifiers()->getListModifier()->resetListScrollBarColor(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_SCROLL) {
        fullImpl->getNodeModifiers()->getScrollModifier()->resetScrollScrollBarColor(node->uiNodeHandle);
    }
}

const ArkUI_AttributeItem* GetScrollScrollable(ArkUI_NodeHandle node)
{
    auto value = GetFullImpl()->getNodeModifiers()->getScrollModifier()->getScrollScrollable(node->uiNodeHandle);
    g_numberValues[0].i32 = value;
    return &g_attributeItem;
}

int32_t SetScrollScrollable(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !InRegion(NUM_0, NUM_3, item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    auto attrVal = item->value[NUM_0].i32;
    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollScrollable(node->uiNodeHandle, attrVal);
    return ERROR_CODE_NO_ERROR;
}

void ResetScrollScrollable(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getScrollModifier()->resetScrollScrollable(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetScrollEdgeEffect(ArkUI_NodeHandle node)
{
    ArkUI_Int32 values[32];
    auto valueSize =
        GetFullImpl()->getNodeModifiers()->getScrollModifier()->getScrollEdgeEffect(node->uiNodeHandle, values);
    for (int i = 0; i < valueSize; i++) {
        g_numberValues[i].i32 = values[i];
    }
    g_attributeItem.size = valueSize;
    return &g_attributeItem;
}

int32_t SetScrollEdgeEffect(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_TWO_PARAM);
    if (actualSize < 0 || !InRegion(NUM_0, NUM_2, item->value[0].i32) || !InRegion(NUM_0, NUM_1, item->value[1].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    auto attrVal = item->value[NUM_0].i32;
    auto alwaysEnabled = (item->size > NUM_1) ? item->value[NUM_1].i32 : true;
    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollEdgeEffect(node->uiNodeHandle, attrVal, alwaysEnabled);
    return ERROR_CODE_NO_ERROR;
}

void ResetScrollEdgeEffect(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    if (node->type == ARKUI_NODE_LIST) {
        fullImpl->getNodeModifiers()->getListModifier()->resetListEdgeEffect(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_SCROLL) {
        fullImpl->getNodeModifiers()->getScrollModifier()->resetScrollEdgeEffect(node->uiNodeHandle);
    }
}

const ArkUI_AttributeItem* GetScrollEnableScrollInteraction(ArkUI_NodeHandle node)
{
    if (node->type == ARKUI_NODE_LIST) {
        g_numberValues[0].i32 =
            GetFullImpl()->getNodeModifiers()->getListModifier()->getEnableScrollInteraction(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_SCROLL) {
        g_numberValues[0].i32 =
            GetFullImpl()->getNodeModifiers()->getScrollModifier()->getEnableScrollInteraction(node->uiNodeHandle);
    }
    return &g_attributeItem;
}

int32_t SetScrollEnableScrollInteraction(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !InRegion(NUM_0, NUM_1, item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    bool enableScrollInteraction = item->value[NUM_0].i32;
    if (node->type == ARKUI_NODE_LIST) {
        fullImpl->getNodeModifiers()->getListModifier()->setEnableScrollInteraction(
            node->uiNodeHandle, enableScrollInteraction);
    } else if (node->type == ARKUI_NODE_SCROLL) {
        fullImpl->getNodeModifiers()->getScrollModifier()->setEnableScrollInteraction(
            node->uiNodeHandle, enableScrollInteraction);
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetScrollEnableScrollInteraction(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    if (node->type == ARKUI_NODE_LIST) {
        fullImpl->getNodeModifiers()->getListModifier()->resetEnableScrollInteraction(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_SCROLL) {
        fullImpl->getNodeModifiers()->getScrollModifier()->resetEnableScrollInteraction(node->uiNodeHandle);
    }
}

int32_t SetScrollNestedScroll(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    // The size must be greater than 2 and check value is Nested Mode
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_TWO_PARAM);
    if (actualSize < 0 || !CheckAttributeIsScrollNestedMode(item->value[0].i32) ||
        !CheckAttributeIsScrollNestedMode(item->value[1].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    int first = item->value[NUM_0].i32;
    int second = item->value[NUM_1].i32;
    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollNestedScroll(node->uiNodeHandle, first, second);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetScrollNestedScroll(ArkUI_NodeHandle node)
{
    ArkUI_Int32 values[2];
    GetFullImpl()->getNodeModifiers()->getScrollModifier()->getScrollNestedScroll(node->uiNodeHandle, values);
    //size index
    g_numberValues[0].i32 = values[0];
    g_numberValues[1].i32 = values[1];
    g_attributeItem.size = ALLOW_SIZE_2;
    return &g_attributeItem;
}

void ResetScrollNestedScroll(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getScrollModifier()->resetScrollNestedScroll(node->uiNodeHandle);
}

int32_t SetScrollTo(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_TWO_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    ArkUI_Float32 values[ALLOW_SIZE_7] = { 0.0, UNIT_VP, 0.0, UNIT_VP, DEFAULT_DURATION, 1, 0.0 };
    values[0] = item->value[0].f32;
    values[1] = UNIT_VP;
    values[2] = item->value[1].f32;
    values[3] = UNIT_VP;
    if (item->size > 2) {
        values[4] = item->value[2].i32;
    }
    // check size
    if (item->size > 3 || !CheckAttributeIsAnimationCurve(item->value[3].i32)) {
        values[5] = item->value[3].i32;
    }
    if (item->size > 4) {
        values[6] = item->value[4].i32;
    }
    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollTo(node->uiNodeHandle, values);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetScrollOffset(ArkUI_NodeHandle node)
{
    ArkUI_Float32 values[2];
    GetFullImpl()->getNodeModifiers()->getScrollModifier()->getScrollOffset(node->uiNodeHandle, values);
    //size index
    g_numberValues[0].i32 = values[0];
    g_numberValues[1].i32 = values[1];
    g_attributeItem.size = ALLOW_SIZE_2;
    return &g_attributeItem;
}

void ResetScrollTo(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getScrollModifier()->resetScrollTo(node->uiNodeHandle);
}

int32_t SetScrollEdge(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollEdge(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetScrollEdge(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getScrollModifier()->getScrollEdge(node->uiNodeHandle);
    //size index
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

void ResetScrollEdge(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getScrollModifier()->resetScrollEdge(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetScrollEnablePaging(ArkUI_NodeHandle node)
{
    auto value = GetFullImpl()->getNodeModifiers()->getScrollModifier()->getScrollEnablePaging(node->uiNodeHandle);
    g_numberValues[0].i32 = value;
    return &g_attributeItem;
}

int32_t SetScrollEnablePaging(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !InRegion(NUM_0, NUM_1, item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollEnablePaging(
        node->uiNodeHandle, item->value[NUM_0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetScrollEnablePaging(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getScrollModifier()->resetScrollEnablePaging(node->uiNodeHandle);
}

// List Attributes functions
void SetListScrollBar(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    auto attrVal = StringToEnumInt(value, SCROLL_DISPLAY_MODE, NUM_1);
    fullImpl->getNodeModifiers()->getListModifier()->setListScrollBar(node->uiNodeHandle, attrVal);
}

void SetListScrollBarWidth(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    auto width = std::string(value) + "vp";
    fullImpl->getNodeModifiers()->getListModifier()->setListScrollBarWidth(node->uiNodeHandle, width.c_str());
}

void ResetScrollScrollBarWidth(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getScrollModifier()->resetScrollScrollBarWidth(node->uiNodeHandle);
}

void SetListScrollBarColor(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    fullImpl->getNodeModifiers()->getListModifier()->setListScrollBarColor(node->uiNodeHandle, value);
}

void SetListDirection(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    auto attrVal = StringToEnumInt(value, SCROLL_AXIS, NUM_0);
    fullImpl->getNodeModifiers()->getListModifier()->setListDirection(node->uiNodeHandle, attrVal);
}

const ArkUI_AttributeItem* GetListDirection(ArkUI_NodeHandle node)
{
    auto value = GetFullImpl()->getNodeModifiers()->getListModifier()->getListDirection(node->uiNodeHandle);
    g_numberValues[0].i32 = value;
    return &g_attributeItem;
}

int32_t SetListDirection(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !InRegion(NUM_0, NUM_1, item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    auto attrVal = item->value[0].i32;
    fullImpl->getNodeModifiers()->getListModifier()->setListDirection(node->uiNodeHandle, attrVal);
    return ERROR_CODE_NO_ERROR;
}

void ResetListDirection(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getListModifier()->resetListDirection(node->uiNodeHandle);
}

void SetListSticky(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    auto attrVal = StringToEnumInt(value, LIST_STICKY_STYLE, NUM_0);

    fullImpl->getNodeModifiers()->getListModifier()->setSticky(node->uiNodeHandle, attrVal);
}

const ArkUI_AttributeItem* GetListSticky(ArkUI_NodeHandle node)
{
    auto value = GetFullImpl()->getNodeModifiers()->getListModifier()->getSticky(node->uiNodeHandle);
    g_numberValues[0].i32 = value;
    return &g_attributeItem;
}

int32_t SetListSticky(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !InRegion(NUM_0, NUM_3, item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    auto attrVal = item->value[0].i32;
    fullImpl->getNodeModifiers()->getListModifier()->setSticky(node->uiNodeHandle, attrVal);
    return ERROR_CODE_NO_ERROR;
}

void ResetListSticky(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getListModifier()->resetSticky(node->uiNodeHandle);
}

void SetListEnableScrollInteraction(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }
    bool enableScrollInteraction = StringToBoolInt(value);
    fullImpl->getNodeModifiers()->getListModifier()->setEnableScrollInteraction(
        node->uiNodeHandle, enableScrollInteraction);
}

void SetListEdgeEffect(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }
    ArkUI_Bool alwaysEnabled = true;
    std::vector<std::string> params;
    StringUtils::StringSplitter(value, ' ', params);
    auto size = params.size();
    if (size <= 0) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return;
    }

    auto attrVal = StringToEnumInt(value, SCROLL_EDGE_EFFECT, NUM_2);
    alwaysEnabled = (size > NUM_1) ? StringToBoolInt(params[NUM_1].c_str()) : true;
    fullImpl->getNodeModifiers()->getListModifier()->setListEdgeEffect(node->uiNodeHandle, attrVal, alwaysEnabled);
}

void SetListFriction(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    fullImpl->getNodeModifiers()->getListModifier()->setListFriction(node->uiNodeHandle, StringToFloat(value));
}

void SetListSpace(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    fullImpl->getNodeModifiers()->getListModifier()->setListSpace(node->uiNodeHandle, StringToFloat(value));
}

const ArkUI_AttributeItem* GetListSpace(ArkUI_NodeHandle node)
{
    auto value = GetFullImpl()->getNodeModifiers()->getListModifier()->getListSpace(node->uiNodeHandle);
    g_numberValues[0].f32 = value;
    return &g_attributeItem;
}

int32_t SetListSpace(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || LessNotEqual(item->value[0].i32, NUM_0)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getListModifier()->setListSpace(node->uiNodeHandle, item->value[NUM_0].f32);
    return ERROR_CODE_NO_ERROR;
}

void ResetListSpace(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getListModifier()->resetListSpace(node->uiNodeHandle);
}

int32_t SetTextAreaPlaceholderFont(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    struct ArkUIResourceLength size = { 16.0, UNIT_FP };
    int weight = ARKUI_FONT_WEIGHT_NORMAL;
    int style = ARKUI_FONT_STYLE_NORMAL;
    if (item->size > NUM_0) {
        if (LessNotEqual(item->value[NUM_0].f32, 0.0f)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        size.value = item->value[NUM_0].f32;
    }
    if (item->size > NUM_1) {
        if (item->value[NUM_1].i32 < 0 || item->value[NUM_1].i32 > static_cast<int32_t>(ARKUI_FONT_STYLE_ITALIC)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        style = item->value[NUM_1].i32;
    }
    if (item->size > NUM_2) {
        if (item->value[NUM_2].i32 < 0 || item->value[NUM_2].i32 > static_cast<int32_t>(ARKUI_FONT_WEIGHT_REGULAR)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        weight = item->value[NUM_2].i32;
    }
    fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaPlaceholderFontEnum(
        node->uiNodeHandle, &size, weight, item->string, style);
    return ERROR_CODE_NO_ERROR;
}

void ResetTextAreaPlaceholderFont(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextAreaModifier()->resetTextAreaPlaceholderFont(node->uiNodeHandle);
}

int32_t SetTextAreaPlaceholder(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaPlaceholderString(node->uiNodeHandle, item->string);
    return ERROR_CODE_NO_ERROR;
}

void ResetTextAreaPlaceholder(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaPlaceholderString(node->uiNodeHandle, "");
}

int32_t SetTextAreaText(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaTextString(node->uiNodeHandle, item->string);
    return ERROR_CODE_NO_ERROR;
}

void ResetTextAreaText(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaTextString(node->uiNodeHandle, "");
}

int32_t StopTextAreaEditing(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || item->value[NUM_0].i32 < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (item->value[NUM_0].i32 == 0) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->stopTextAreaTextEditing(node->uiNodeHandle);
    }
    return ERROR_CODE_NO_ERROR;
}

int32_t SetButtonLabel(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    if (item->value[NUM_0].i32 == 0) {
        fullImpl->getNodeModifiers()->getButtonModifier()->setButtonLabel(node->uiNodeHandle, item->string);
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetButtonLabel(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getButtonModifier()->setButtonLabel(node->uiNodeHandle, "");
}

int32_t SetProgressValue(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || LessNotEqual(item->value[0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getProgressModifier()->setProgressValue(node->uiNodeHandle, item->value[0].f32);
    return ERROR_CODE_NO_ERROR;
}

void ResetProgressValue(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getProgressModifier()->resetProgressValue(node->uiNodeHandle);
}

int32_t SetProgressTotal(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || LessNotEqual(item->value[0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getProgressModifier()->setProgressTotal(node->uiNodeHandle, item->value[0].f32);
    return ERROR_CODE_NO_ERROR;
}

void ResetProgressTotal(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getProgressModifier()->resetProgressValue(node->uiNodeHandle);
}

int32_t SetProgressColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getProgressModifier()->setProgressColor(node->uiNodeHandle, item->value[0].u32);
    return ERROR_CODE_NO_ERROR;
}

void ResetProgressColor(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getProgressModifier()->resetProgressColor(node->uiNodeHandle);
}

int32_t SetProgressType(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || item->value[NUM_0].i32 < static_cast<int32_t>(ARKUI_PROGRESS_LINEAR) ||
        item->value[NUM_0].i32 > static_cast<int32_t>(ARKUI_PROGRESS_CAPSULE)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getProgressModifier()->setProgressType(node->uiNodeHandle, item->value[NUM_0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetProgressType(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getProgressModifier()->resetProgressType(node->uiNodeHandle);
}

int32_t SetXComponentId(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getXComponentModifier()->setXComponentId(node->uiNodeHandle, item->string);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetXComponentType(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->string) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::string input(item->string);
    uint32_t type = input == "texture" ? XCOMPONENT_TYPE_TEXTURE : XCOMPONENT_TYPE_SURFACE;
    fullImpl->getNodeModifiers()->getXComponentModifier()->setXComponentType(node->uiNodeHandle, type);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetXComponentSurfaceSize(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_TWO_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getXComponentModifier()->setXComponentSurfaceSize(
        node->uiNodeHandle, item->value[0].u32, item->value[1].u32);
    return ERROR_CODE_NO_ERROR;
}

void ResetXComponentSurfaceSize(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getXComponentModifier()->setXComponentSurfaceSize(node->uiNodeHandle, 0, 0);
}

int32_t SetTextBaselineOffset(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == NUM_0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    struct ArkUIStringAndFloat offset = { item->value[0].f32 };

    fullImpl->getNodeModifiers()->getTextModifier()->setTextBaselineOffset(node->uiNodeHandle, &offset);
    return ERROR_CODE_NO_ERROR;
}

void ResetTextBaselineOffset(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextModifier()->resetTextBaselineOffset(node->uiNodeHandle);
}

int32_t SetTextShadow(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size < NUM_5) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    std::vector<struct ArkUITextShadowStruct> shadows;
    struct ArkUITextShadowStruct shadow = { item->value[0].f32, item->value[1].i32, item->value[2].u32,
        item->value[3].f32, item->value[4].f32 };
    shadows.emplace_back(shadow);

    fullImpl->getNodeModifiers()->getTextModifier()->setTextShadow(node->uiNodeHandle, &shadows[0], shadows.size());
    return ERROR_CODE_NO_ERROR;
}

void ResetTextShadow(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextModifier()->resetTextShadow(node->uiNodeHandle);
}

int32_t SetTextMinFontSize(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextModifier()->setTextMinFontSize(
        node->uiNodeHandle, item->value[0].f32, UNIT_FP);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextMinFontSize(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getTextModifier()->getTextMinFontSize(node->uiNodeHandle);
    g_numberValues[0].f32 = resultValue;
    return &g_attributeItem;
}

void ResetTextMinFontSize(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextModifier()->resetTextMinFontSize(node->uiNodeHandle);
}

int32_t SetTextMaxFontSize(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextModifier()->setTextMaxFontSize(
        node->uiNodeHandle, item->value[0].f32, UNIT_FP);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextMaxFontSize(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getTextModifier()->getTextMaxFontSize(node->uiNodeHandle);
    g_numberValues[0].f32 = resultValue;
    return &g_attributeItem;
}

void ResetTextMaxFontSize(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextModifier()->resetTextMaxFontSize(node->uiNodeHandle);
}

int32_t SetTextFont(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    // size
    double size = item->value[0].f32;
    // weight
    int weight = 10; // default
    if (item->size > 1) {
        if (!CheckAttributeIsFontWeight(item->value[1].i32)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        weight = item->value[1].i32;
    }
    // style
    int style = 0;
    if (item->size > 2) {
        // get value 2 is font style
        if (!CheckAttributeIsFontStyle(item->value[2].i32)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        style = item->value[NUM_2].i32;
    }
    // family
    std::vector<std::string> familyArray;
    if (item->string == nullptr) {
        std::string value(item->string);
        StringUtils::StringSplitter(value, ',', familyArray);
    }

    ArkUIFontStruct fontStruct;
    fontStruct.fontSizeNumber = size;
    fontStruct.fontSizeUnit = UNIT_FP;
    fontStruct.fontWeight = weight;
    if (familyArray.size() > 0) {
        std::vector<const char*> fontFamilies;
        for (const auto& element : familyArray) {
            fontFamilies.push_back(element.c_str());
        }
        fontStruct.fontFamilies = fontFamilies.data();
    }
    fontStruct.fontStyle = style;
    ArkUIFontStruct* fontInfo = &fontStruct;
    fullImpl->getNodeModifiers()->getTextModifier()->setTextFont(node->uiNodeHandle, fontInfo);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextFont(ArkUI_NodeHandle node)
{
    ArkUITextFont font;
    GetFullImpl()->getNodeModifiers()->getTextModifier()->getFont(node->uiNodeHandle, &font);
    int index = 0;
    g_numberValues[index++].f32 = font.fontSize;
    g_numberValues[index++].i32 = font.fontWeight;
    g_numberValues[index++].i32 = font.fontStyle;
    g_attributeItem.size = index;
    g_attributeItem.string = font.fontFamilies;
    return &g_attributeItem;
}

void ResetTextFont(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextModifier()->resetTextFont(node->uiNodeHandle);
}

int32_t SetTextHeightAdaptivePolicy(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !CheckAttributeIsTextHeightAdaptivePolicy(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextModifier()->setTextHeightAdaptivePolicy(
        node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextHeightAdaptivePolicy(ArkUI_NodeHandle node)
{
    auto resultValue =
        GetFullImpl()->getNodeModifiers()->getTextModifier()->getHeightAdaptivePolicy(node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

void ResetTextHeightAdaptivePolicy(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextModifier()->resetTextHeightAdaptivePolicy(node->uiNodeHandle);
}

// Toggle Attributes functions
int32_t SetToggleSelectedColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getToggleModifier()->setToggleSelectedColor(node->uiNodeHandle, item->value[0].u32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetToggleSelectedColor(ArkUI_NodeHandle node)
{
    auto resultValue =
        GetFullImpl()->getNodeModifiers()->getToggleModifier()->getToggleSelectedColor(node->uiNodeHandle);
    g_numberValues[0].u32 = resultValue;
    return &g_attributeItem;
}

void ResetToggleSelectedColor(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getToggleModifier()->resetToggleSelectedColor(node->uiNodeHandle);
}

int32_t SetToggleSwitchPointColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getToggleModifier()->setToggleSwitchPointColor(
        node->uiNodeHandle, item->value[0].u32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetToggleSwitchPointColor(ArkUI_NodeHandle node)
{
    auto resultValue =
        GetFullImpl()->getNodeModifiers()->getToggleModifier()->getToggleSwitchPointColor(node->uiNodeHandle);
    g_numberValues[0].u32 = resultValue;
    return &g_attributeItem;
}

void ResetToggleSwitchPointColor(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getToggleModifier()->resetToggleSwitchPointColor(node->uiNodeHandle);
}

// LoadingProgress Attributes functions
void SetLoadingProgressColor(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getLoadingProgressModifier()->setColor(node->uiNodeHandle, StringToColorInt(value));
}

const ArkUI_AttributeItem* GetLoadingProgressColor(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getLoadingProgressModifier();

    g_numberValues[0].u32 = modifier->getColor(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetLoadingProgressColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    // already check in entry point.
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getLoadingProgressModifier()->setColor(node->uiNodeHandle, item->value[NUM_0].u32);
    return ERROR_CODE_NO_ERROR;
}

void ResetLoadingProgressColor(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getLoadingProgressModifier()->resetColor(node->uiNodeHandle);
}

void SetLoadingProgressEnableLoading(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getLoadingProgressModifier()->setEnableLoading(
        node->uiNodeHandle, std::strcmp(value, "false"));
}

const ArkUI_AttributeItem* GetLoadingProgressEnableLoading(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getLoadingProgressModifier();

    g_numberValues[0].i32 = modifier->getEnableLoading(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetLoadingProgressEnableLoading(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !InRegion(NUM_0, NUM_1, item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getLoadingProgressModifier()->setEnableLoading(
        node->uiNodeHandle, item->value[NUM_0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetLoadingProgressEnableLoading(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getLoadingProgressModifier()->resetEnableLoading(node->uiNodeHandle);
}

// Swiper Attributes functions
int32_t SetSwiperLoop(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < NUM_0 || item->value[0].i32 > NUM_1) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperLoop(
        node->uiNodeHandle, static_cast<bool>(item->value[0].i32));
    return ERROR_CODE_NO_ERROR;
}

void ResetSwiperLoop(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->resetSwiperLoop(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetSwiperLoop(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getSwiperModifier();
    g_numberValues[0].i32 = modifier->getSwiperLoop(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetSwiperAutoPlay(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < NUM_0 || item->value[0].i32 > NUM_1) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperAutoPlay(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetSwiperAutoPlay(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->resetSwiperAutoPlay(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetSwiperAutoPlay(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getSwiperModifier();
    g_numberValues[0].i32 = modifier->getSwiperAutoPlay(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetSwiperShowIndicator(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < NUM_0 || item->value[0].i32 > NUM_1) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    std::vector<std::string> IndicatorProps = { "boolean", "true" };
    IndicatorProps[NUM_1] = std::to_string(item->value[0].i32);
    std::stringstream ss;
    for (const auto& str : IndicatorProps) {
        ss << str << "|";
    }
    std::string result;
    ss >> result;
    if (!result.empty()) {
        result.pop_back(); // 删除最后一个字符
    }
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperIndicator(node->uiNodeHandle, result.c_str());
    return ERROR_CODE_NO_ERROR;
}

void ResetSwiperShowIndicator(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->resetSwiperIndicator(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetSwiperShowIndicator(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getSwiperModifier();
    g_numberValues[0].i32 = modifier->getSwiperShowIndicator(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetSwiperInterval(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (LessNotEqual(item->value[0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperInterval(
        node->uiNodeHandle, static_cast<uint32_t>(item->value[0].f32));
    return ERROR_CODE_NO_ERROR;
}

void ResetSwiperInterval(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->resetSwiperInterval(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetSwiperInterval(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getSwiperModifier();
    g_numberValues[0].f32 = modifier->getSwiperInterval(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetSwiperVertical(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < NUM_0 || item->value[0].i32 > NUM_1) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperVertical(
        node->uiNodeHandle, static_cast<bool>(item->value[0].i32));
    return ERROR_CODE_NO_ERROR;
}

void ResetSwiperVertical(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->resetSwiperVertical(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetSwiperVertical(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getSwiperModifier();
    g_numberValues[0].i32 = modifier->getSwiperVertical(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetSwiperDuration(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (LessNotEqual(item->value[0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperDuration(node->uiNodeHandle, item->value[0].f32);
    return ERROR_CODE_NO_ERROR;
}

void ResetSwiperDuration(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->resetSwiperDuration(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetSwiperDuration(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getSwiperModifier();
    g_numberValues[0].f32 = modifier->getSwiperDuration(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetSwiperCurve(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < ArkUI_AnimationCurve::ARKUI_CURVE_LINEAR ||
        item->value[0].i32 > ArkUI_AnimationCurve::ARKUI_CURVE_FRICTION) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperCurve(
        node->uiNodeHandle, CurveToString(item->value[0].i32).c_str());
    return ERROR_CODE_NO_ERROR;
}

void ResetSwiperCurve(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->resetSwiperCurve(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetSwiperCurve(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getSwiperModifier();
    g_numberValues[0].i32 = modifier->getSwiperCurve(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetSwiperItemSpace(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (LessNotEqual(item->value[0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperItemSpace(
        node->uiNodeHandle, item->value[0].f32, NUM_1);
    return ERROR_CODE_NO_ERROR;
}

void ResetSwiperItemSpace(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->resetSwiperItemSpace(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetSwiperItemSpace(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getSwiperModifier();
    g_numberValues[0].f32 = modifier->getSwiperItemSpace(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetSwiperIndex(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperIndex(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetSwiperIndex(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->resetSwiperIndex(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetSwiperIndex(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getSwiperModifier();
    g_numberValues[0].i32 = modifier->getSwiperIndex(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetSwiperDisplayCount(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (LessNotEqual(item->value[0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    std::string type = "number";
    std::string displayCount = std::to_string(item->value[0].i32);
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperDisplayCount(
        node->uiNodeHandle, displayCount.c_str(), type.c_str());
    return ERROR_CODE_NO_ERROR;
}

void ResetSwiperDisplayCount(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->resetSwiperDisplayCount(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetSwiperDisplayCount(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getSwiperModifier();
    g_numberValues[0].i32 = modifier->getSwiperDisplayCount(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetSwiperDisableSwipe(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < NUM_0 || item->value[0].i32 > NUM_1) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperDisableSwipe(
        node->uiNodeHandle, static_cast<bool>(item->value[0].i32));
    return ERROR_CODE_NO_ERROR;
}

void ResetSwiperDisableSwipe(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->resetSwiperDisableSwipe(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetSwiperDisableSwipe(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getSwiperModifier();
    g_numberValues[0].i32 = modifier->getSwiperDisableSwipe(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetSwiperShowDisplayArrow(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < NUM_0 || item->value[0].i32 > NUM_1) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    double defaultBackgroundColor = StringToColorInt("#00000000", 0);
    double defaultArrowColor = StringToColorInt("#FF182431", 0);
    double displayArrow[ALLOW_SIZE_8] = { 1, 0, 0, DEFAULT_SIZE_24, defaultBackgroundColor, DEFAULT_SIZE_18,
        defaultArrowColor, 0 };
    if (item->value[0].i32 == ArkUI_SwiperArrow::ARKUI_SWIPER_ARROW_SHOW_ON_HOVER) {
        displayArrow[NUM_0] = DISPLAY_ARROW_TRUE;
        displayArrow[NUM_7] = DISPLAY_ARROW_TRUE;
    } else {
        displayArrow[NUM_0] = item->value[0].i32;
        displayArrow[NUM_7] = DISPLAY_ARROW_FALSE;
    }
    std::stringstream ss;
    for (const auto& str : displayArrow) {
        ss << str << "|";
    }
    std::string result;
    ss >> result;
    if (!result.empty()) {
        result.pop_back(); // 删除最后一个字符
    }
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperDisplayArrow(node->uiNodeHandle, result.c_str());
    return ERROR_CODE_NO_ERROR;
}

void ResetSwiperShowDisplayArrow(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->resetSwiperDisplayArrow(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetSwiperShowDisplayArrow(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getSwiperModifier();
    g_numberValues[0].i32 = modifier->getSwiperShowDisplayArrow(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetTextFontFamily(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->string == nullptr) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    std::string value(item->string);
    std::vector<std::string> fontFamilies;
    StringUtils::StringSplitter(value, ',', fontFamilies);
    auto families = std::make_unique<char*[]>(fontFamilies.size());
    for (uint32_t i = 0; i < fontFamilies.size(); i++) {
        families[i] = const_cast<char*>(fontFamilies.at(i).c_str());
    }

    if (node->type == ARKUI_NODE_TEXT_INPUT) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputFontFamily(
            node->uiNodeHandle, const_cast<const char**>(families.get()), fontFamilies.size());
    } else if (node->type == ARKUI_NODE_TEXT) {
        fullImpl->getNodeModifiers()->getTextModifier()->setTextFontFamily(
            node->uiNodeHandle, const_cast<const char**>(families.get()), fontFamilies.size());
    }
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextFontFamily(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getTextModifier()->getFontFamily(node->uiNodeHandle);
    g_attributeItem.string = resultValue;
    g_attributeItem.size = 0;
    return &g_attributeItem;
}

void ResetTextFontFamily(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT_INPUT) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputFontFamily(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_TEXT) {
        fullImpl->getNodeModifiers()->getTextModifier()->resetTextFontFamily(node->uiNodeHandle);
    }
}

void ResetTextCopyOption(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT) {
        fullImpl->getNodeModifiers()->getTextModifier()->resetTextCopyOption(node->uiNodeHandle);
    }
}

int32_t SetTextCopyOption(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == NUM_0 || !CheckAttributeIsCopyOptions(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT) {
        fullImpl->getNodeModifiers()->getTextModifier()->setTextCopyOption(node->uiNodeHandle, item->value[0].i32);
    } else {
        return ERROR_CODE_PARAM_INVALID;
    }
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextCopyOption(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getTextModifier()->getCopyOption(node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

// ListItemGroup
void SetListItemGroupHeader(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    auto headerNodeHandle = reinterpret_cast<ArkUI_NodeHandle>(std::stoull(value));
    fullImpl->getNodeModifiers()->getListItemGroupModifier()->listItemGroupSetHeader(
        node->uiNodeHandle, headerNodeHandle->uiNodeHandle);
}

int32_t SetListItemGroupHeader(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->object) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    auto headerNodeHandle = reinterpret_cast<ArkUI_NodeHandle>(item->object);
    fullImpl->getNodeModifiers()->getListItemGroupModifier()->listItemGroupSetHeader(
        node->uiNodeHandle, headerNodeHandle->uiNodeHandle);
    return ERROR_CODE_NO_ERROR;
}

void SetListItemGroupFooter(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    auto footerNodeHandle = reinterpret_cast<ArkUI_NodeHandle>(std::stoull(value));
    fullImpl->getNodeModifiers()->getListItemGroupModifier()->listItemGroupSetFooter(
        node->uiNodeHandle, footerNodeHandle->uiNodeHandle);
}

int32_t SetListItemGroupFooter(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->object) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    auto footerNodeHandle = reinterpret_cast<ArkUI_NodeHandle>(item->object);
    fullImpl->getNodeModifiers()->getListItemGroupModifier()->listItemGroupSetFooter(
        node->uiNodeHandle, footerNodeHandle->uiNodeHandle);
    return ERROR_CODE_NO_ERROR;
}

void SetListItemGroupDivider(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    std::vector<std::string> params;
    StringUtils::StringSplitter(value, ' ', params);
    if (params.size() != NUM_4) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return;
    }

    auto color = StringToColorInt(params[NUM_0].c_str());
    ArkUI_Float32 values[NUM_3];
    ArkUI_Int32 units[NUM_3] = { UNIT_VP, UNIT_VP, UNIT_VP };
    for (int i = 0; i < NUM_3; ++i) {
        values[i] = StringUtils::StringToDouble(params[i]);
    }

    fullImpl->getNodeModifiers()->getListItemGroupModifier()->listItemGroupSetDivider(
        node->uiNodeHandle, color, values, units, NUM_3);
}

int32_t SetListItemGroupDivider(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_FOUR_PARAM);
    if (actualSize < 0 || LessNotEqual(item->value[NUM_1].f32, NUM_0) || LessNotEqual(item->value[NUM_2].f32, NUM_0) ||
        LessNotEqual(item->value[NUM_3].f32, NUM_0)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    auto color = item->value[NUM_0].u32;
    ArkUI_Float32 values[NUM_3] = { item->value[NUM_1].f32, item->value[NUM_2].f32, item->value[NUM_3].f32 };
    ArkUI_Int32 units[NUM_3] = { UNIT_VP, UNIT_VP, UNIT_VP };

    fullImpl->getNodeModifiers()->getListItemGroupModifier()->listItemGroupSetDivider(
        node->uiNodeHandle, color, values, units, NUM_3);
    return ERROR_CODE_NO_ERROR;
}

void ResetListItemGroupDivider(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getListItemGroupModifier()->listItemGroupResetDivider(node->uiNodeHandle);
}

// datepicker
void SetDatePickerLunar(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    auto lunar = StringToBoolInt(value, false);
    fullImpl->getNodeModifiers()->getDatePickerModifier()->setLunar(node->uiNodeHandle, lunar);
}

const ArkUI_AttributeItem* GetDatePickerLunar(ArkUI_NodeHandle node)
{
    auto value = GetFullImpl()->getNodeModifiers()->getDatePickerModifier()->getLunar(node->uiNodeHandle);
    g_numberValues[0].i32 = value;
    return &g_attributeItem;
}

int32_t SetDatePickerLunar(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !InRegion(NUM_0, NUM_1, item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getDatePickerModifier()->setLunar(node->uiNodeHandle, item->value[NUM_0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetDatePickerLunar(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getDatePickerModifier()->resetLunar(node->uiNodeHandle);
}

void SetDatePickerStart(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();

    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    std::vector<std::string> date;
    StringUtils::StringSplitter(std::string(value), '-', date);
    if (date.size() != NUM_3) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "date is invalid");
        return;
    }

    auto year = StringToInt(date[NUM_0].c_str());
    auto month = StringToInt(date[NUM_1].c_str());
    auto day = StringToInt(date[NUM_2].c_str());
    fullImpl->getNodeModifiers()->getDatePickerModifier()->setStartDate(node->uiNodeHandle, year, month, day);
}

const ArkUI_AttributeItem* GetDatePickerStart(ArkUI_NodeHandle node)
{
    auto value = GetFullImpl()->getNodeModifiers()->getDatePickerModifier()->getStartDate(node->uiNodeHandle);
    g_attributeItem.string = value;
    return &g_attributeItem;
}

int32_t SetDatePickerStart(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->string) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    std::vector<std::string> date;
    StringUtils::StringSplitter(item->string, '-', date);
    if (date.size() != NUM_3) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "date is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    auto year = StringToInt(date[NUM_0].c_str());
    auto month = StringToInt(date[NUM_1].c_str());
    auto day = StringToInt(date[NUM_2].c_str());
    fullImpl->getNodeModifiers()->getDatePickerModifier()->setStartDate(node->uiNodeHandle, year, month, day);

    return ERROR_CODE_NO_ERROR;
}

void ResetDatePickerStart(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getDatePickerModifier()->resetStartDate(node->uiNodeHandle);
}

void SetDatePickerEnd(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();

    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    std::vector<std::string> date;
    StringUtils::StringSplitter(std::string(value), '-', date);
    if (date.size() != NUM_3) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "date is invalid");
        return;
    }

    auto year = StringToInt(date[NUM_0].c_str());
    auto month = StringToInt(date[NUM_1].c_str());
    auto day = StringToInt(date[NUM_2].c_str());
    fullImpl->getNodeModifiers()->getDatePickerModifier()->setEndDate(node->uiNodeHandle, year, month, day);
}

const ArkUI_AttributeItem* GetDatePickerEnd(ArkUI_NodeHandle node)
{
    auto value = GetFullImpl()->getNodeModifiers()->getDatePickerModifier()->getEndDate(node->uiNodeHandle);
    g_attributeItem.string = value;
    return &g_attributeItem;
}

int32_t SetDatePickerEnd(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->string) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    std::vector<std::string> date;
    StringUtils::StringSplitter(item->string, '-', date);
    if (date.size() != NUM_3) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "date is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    auto year = StringToInt(date[NUM_0].c_str());
    auto month = StringToInt(date[NUM_1].c_str());
    auto day = StringToInt(date[NUM_2].c_str());
    fullImpl->getNodeModifiers()->getDatePickerModifier()->setEndDate(node->uiNodeHandle, year, month, day);

    return ERROR_CODE_NO_ERROR;
}

void ResetDatePickerEnd(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getDatePickerModifier()->resetEndDate(node->uiNodeHandle);
}

void SetDatePickerSelected(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();

    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    std::vector<std::string> date;
    StringUtils::StringSplitter(std::string(value), '-', date);
    if (date.size() != NUM_3) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "date is invalid");
        return;
    }

    auto year = StringToInt(date[NUM_0].c_str());
    auto month = StringToInt(date[NUM_1].c_str());
    auto day = StringToInt(date[NUM_2].c_str());
    fullImpl->getNodeModifiers()->getDatePickerModifier()->setSelectedDate(node->uiNodeHandle, year, month, day);
}

const ArkUI_AttributeItem* GetDatePickerSelected(ArkUI_NodeHandle node)
{
    auto value = GetFullImpl()->getNodeModifiers()->getDatePickerModifier()->getSelectedDate(node->uiNodeHandle);
    g_attributeItem.string = value;
    return &g_attributeItem;
}

int32_t SetDatePickerSelected(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->string) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    std::vector<std::string> date;
    StringUtils::StringSplitter(item->string, '-', date);
    if (date.size() != NUM_3) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "date is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    auto year = StringToInt(date[NUM_0].c_str());
    auto month = StringToInt(date[NUM_1].c_str());
    auto day = StringToInt(date[NUM_2].c_str());
    fullImpl->getNodeModifiers()->getDatePickerModifier()->setSelectedDate(node->uiNodeHandle, year, month, day);

    return ERROR_CODE_NO_ERROR;
}

void ResetDatePickerSelected(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getDatePickerModifier()->resetSelectedDate(node->uiNodeHandle);
}

void SetDatePickerDisappearTextStyle(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();

    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    std::vector<std::string> params;
    StringUtils::StringSplitter(value, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() != NUM_5) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return;
    }

    ArkUI_Uint32 color = StringToColorInt(params[NUM_0].c_str());
    auto style = StringToEnumInt(params[NUM_4].c_str(), FONT_STYLES, NUM_0);
    std::string fontInfo = params[NUM_1] + '|' + params[NUM_2] + '|' + params[NUM_3];

    fullImpl->getNodeModifiers()->getDatePickerModifier()->setDisappearTextStyle(
        node->uiNodeHandle, fontInfo.c_str(), color, style);
}

const ArkUI_AttributeItem* GetDatePickerDisappearTextStyle(ArkUI_NodeHandle node)
{
    auto value = GetFullImpl()->getNodeModifiers()->getDatePickerModifier()->getDisappearTextStyle(node->uiNodeHandle);
    g_attributeItem.string = value;
    return &g_attributeItem;
}

int32_t SetDatePickerDisappearTextStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->string) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    std::vector<std::string> params;
    StringUtils::StringSplitter(item->string, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() != NUM_5) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    ArkUI_Uint32 color = StringToColorInt(params[NUM_0].c_str());
    auto style = StringToEnumInt(params[NUM_4].c_str(), FONT_STYLES, NUM_0);
    std::string fontInfo = params[NUM_1] + '|' + params[NUM_2] + '|' + params[NUM_3];

    fullImpl->getNodeModifiers()->getDatePickerModifier()->setDisappearTextStyle(
        node->uiNodeHandle, fontInfo.c_str(), color, style);

    return ERROR_CODE_NO_ERROR;
}

void ResetDatePickerDisappearTextStyle(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getDatePickerModifier()->resetDisappearTextStyle(node->uiNodeHandle);
}

void SetDatePickerTextStyle(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();

    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    std::vector<std::string> params;
    StringUtils::StringSplitter(value, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() != NUM_5) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return;
    }

    ArkUI_Uint32 color = StringToColorInt(params[NUM_0].c_str());
    auto style = StringToEnumInt(params[NUM_4].c_str(), FONT_STYLES, NUM_0);
    std::string fontInfo = params[NUM_1] + '|' + params[NUM_2] + '|' + params[NUM_3];

    fullImpl->getNodeModifiers()->getDatePickerModifier()->setDatePickerTextStyle(
        node->uiNodeHandle, fontInfo.c_str(), color, style);
}

const ArkUI_AttributeItem* GetDatePickerTextStyle(ArkUI_NodeHandle node)
{
    auto value = GetFullImpl()->getNodeModifiers()->getDatePickerModifier()->getDatePickerTextStyle(node->uiNodeHandle);
    g_attributeItem.string = value;
    return &g_attributeItem;
}

int32_t SetDatePickerTextStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->string) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    std::vector<std::string> params;
    StringUtils::StringSplitter(item->string, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() != NUM_5) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    ArkUI_Uint32 color = StringToColorInt(params[NUM_0].c_str());
    auto style = StringToEnumInt(params[NUM_4].c_str(), FONT_STYLES, NUM_0);
    std::string fontInfo = params[NUM_1] + '|' + params[NUM_2] + '|' + params[NUM_3];

    fullImpl->getNodeModifiers()->getDatePickerModifier()->setDatePickerTextStyle(
        node->uiNodeHandle, fontInfo.c_str(), color, style);

    return ERROR_CODE_NO_ERROR;
}

void ResetDatePickerTextStyle(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getDatePickerModifier()->resetDatePickerTextStyle(node->uiNodeHandle);
}

void SetDatePickerSelectedTextStyle(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();

    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    std::vector<std::string> params;
    StringUtils::StringSplitter(value, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() != NUM_5) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return;
    }

    ArkUI_Uint32 color = StringToColorInt(params[NUM_0].c_str());
    auto style = StringToEnumInt(params[NUM_4].c_str(), FONT_STYLES, NUM_0);
    std::string fontInfo = params[NUM_1] + '|' + params[NUM_2] + '|' + params[NUM_3];

    fullImpl->getNodeModifiers()->getDatePickerModifier()->setSelectedTextStyle(
        node->uiNodeHandle, fontInfo.c_str(), color, style);
}

const ArkUI_AttributeItem* GetDatePickerSelectedTextStyle(ArkUI_NodeHandle node)
{
    auto value = GetFullImpl()->getNodeModifiers()->getDatePickerModifier()->getSelectedTextStyle(node->uiNodeHandle);
    g_attributeItem.string = value;
    return &g_attributeItem;
}

int32_t SetDatePickerSelectedTextStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->string) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    std::vector<std::string> params;
    StringUtils::StringSplitter(item->string, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() != NUM_5) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    ArkUI_Uint32 color = StringToColorInt(params[NUM_0].c_str());
    auto style = StringToEnumInt(params[NUM_4].c_str(), FONT_STYLES, NUM_0);
    std::string fontInfo = params[NUM_1] + '|' + params[NUM_2] + '|' + params[NUM_3];

    fullImpl->getNodeModifiers()->getDatePickerModifier()->setSelectedTextStyle(
        node->uiNodeHandle, fontInfo.c_str(), color, style);

    return ERROR_CODE_NO_ERROR;
}

void ResetDatePickerSelectedTextStyle(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getDatePickerModifier()->resetSelectedTextStyle(node->uiNodeHandle);
}

// timepicker
void SetTimePickerSelected(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();

    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    std::vector<std::string> params;
    StringUtils::StringSplitter(value, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() != NUM_5) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return;
    }

    ArkUI_Uint32 color = StringToColorInt(params[NUM_0].c_str());
    auto style = StringToEnumInt(params[NUM_4].c_str(), FONT_STYLES, NUM_0);
    std::string fontInfo = params[NUM_1] + '|' + params[NUM_2] + '|' + params[NUM_3];

    fullImpl->getNodeModifiers()->getTimepickerModifier()->setTimepickerSelectedTextStyle(
        node->uiNodeHandle, color, fontInfo.c_str(), style);
}

const ArkUI_AttributeItem* GetTimePickerSelected(ArkUI_NodeHandle node)
{
    auto value = GetFullImpl()->getNodeModifiers()->getTimepickerModifier()->getTimepickerSelected(node->uiNodeHandle);
    g_attributeItem.string = value;
    return &g_attributeItem;
}

int32_t SetTimePickerSelected(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->string) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    std::vector<std::string> time;
    StringUtils::StringSplitter(item->string, '-', time);
    if (time.size() != NUM_2) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "time is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    auto hour = StringToInt(time[NUM_0].c_str());
    auto minute = StringToInt(time[NUM_1].c_str());
    fullImpl->getNodeModifiers()->getTimepickerModifier()->setTimepickerSelected(node->uiNodeHandle, hour, minute);

    return ERROR_CODE_NO_ERROR;
}

void ResetTimePickerSelected(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getTimepickerModifier()->resetTimepickerSelected(node->uiNodeHandle);
}

void SetTimePickerUseMilitaryTime(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();

    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    fullImpl->getNodeModifiers()->getTimepickerModifier()->setTimepickerUseMilitaryTime(
        node->uiNodeHandle, StringToBoolInt(value));
}

const ArkUI_AttributeItem* GetTimePickerUseMilitaryTime(ArkUI_NodeHandle node)
{
    auto value =
        GetFullImpl()->getNodeModifiers()->getTimepickerModifier()->getTimepickerUseMilitaryTime(node->uiNodeHandle);
    g_numberValues[0].i32 = value;
    return &g_attributeItem;
}

int32_t SetTimePickerUseMilitaryTime(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTimepickerModifier()->setTimepickerUseMilitaryTime(
        node->uiNodeHandle, item->value[NUM_0].i32);

    return ERROR_CODE_NO_ERROR;
}

void ResetTimePickerUseMilitaryTime(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getTimepickerModifier()->resetTimepickerUseMilitaryTime(node->uiNodeHandle);
}

void SetTimePickerDisappearTextStyle(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();

    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    std::vector<std::string> params;
    StringUtils::StringSplitter(value, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() != NUM_5) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return;
    }

    ArkUI_Uint32 color = StringToColorInt(params[NUM_0].c_str());
    auto style = StringToEnumInt(params[NUM_4].c_str(), FONT_STYLES, NUM_0);
    std::string fontInfo = params[NUM_1] + '|' + params[NUM_2] + '|' + params[NUM_3];

    fullImpl->getNodeModifiers()->getTimepickerModifier()->setTimepickerDisappearTextStyle(
        node->uiNodeHandle, color, fontInfo.c_str(), style);
}

const ArkUI_AttributeItem* GetTimePickerDisappearTextStyle(ArkUI_NodeHandle node)
{
    auto value =
        GetFullImpl()->getNodeModifiers()->getTimepickerModifier()->getTimepickerSelectedTextStyle(node->uiNodeHandle);
    g_attributeItem.string = value;
    return &g_attributeItem;
}

int32_t SetTimePickerDisappearTextStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->string) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    std::vector<std::string> params;
    StringUtils::StringSplitter(item->string, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() != NUM_5) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    ArkUI_Uint32 color = StringToColorInt(params[NUM_0].c_str());
    auto style = StringToEnumInt(params[NUM_4].c_str(), FONT_STYLES, NUM_0);
    std::string fontInfo = params[NUM_1] + '|' + params[NUM_2] + '|' + params[NUM_3];

    fullImpl->getNodeModifiers()->getTimepickerModifier()->setTimepickerDisappearTextStyle(
        node->uiNodeHandle, color, fontInfo.c_str(), style);

    return ERROR_CODE_NO_ERROR;
}

void ResetTimePickerDisappearTextStyle(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getTimepickerModifier()->resetTimepickerDisappearTextStyle(node->uiNodeHandle);
}

void SetTimePickerTextStyle(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();

    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    std::vector<std::string> params;
    StringUtils::StringSplitter(value, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() != NUM_5) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return;
    }

    ArkUI_Uint32 color = StringToColorInt(params[NUM_0].c_str());
    auto style = StringToEnumInt(params[NUM_4].c_str(), FONT_STYLES, NUM_0);
    std::string fontInfo = params[NUM_1] + '|' + params[NUM_2] + '|' + params[NUM_3];

    fullImpl->getNodeModifiers()->getTimepickerModifier()->setTimepickerTextStyle(
        node->uiNodeHandle, color, fontInfo.c_str(), style);
}

const ArkUI_AttributeItem* GetTimePickerTextStyle(ArkUI_NodeHandle node)
{
    auto value =
        GetFullImpl()->getNodeModifiers()->getTimepickerModifier()->getTimepickerTextStyle(node->uiNodeHandle);
    g_attributeItem.string = value;
    return &g_attributeItem;
}

int32_t SetTimePickerTextStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->string) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    std::vector<std::string> params;
    StringUtils::StringSplitter(item->string, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() != NUM_5) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    ArkUI_Uint32 color = StringToColorInt(params[NUM_0].c_str());
    auto style = StringToEnumInt(params[NUM_4].c_str(), FONT_STYLES, NUM_0);
    std::string fontInfo = params[NUM_1] + '|' + params[NUM_2] + '|' + params[NUM_3];

    fullImpl->getNodeModifiers()->getTimepickerModifier()->setTimepickerTextStyle(
        node->uiNodeHandle, color, fontInfo.c_str(), style);

    return ERROR_CODE_NO_ERROR;
}

void ResetTimePickerTextStyle(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getTimepickerModifier()->resetTimepickerTextStyle(node->uiNodeHandle);
}

void SetTimePickerSelectedTextStyle(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();

    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    std::vector<std::string> params;
    StringUtils::StringSplitter(value, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() != NUM_5) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return;
    }

    ArkUI_Uint32 color = StringToColorInt(params[NUM_0].c_str());
    auto style = StringToEnumInt(params[NUM_4].c_str(), FONT_STYLES, NUM_0);
    std::string fontInfo = params[NUM_1] + '|' + params[NUM_2] + '|' + params[NUM_3];

    fullImpl->getNodeModifiers()->getTimepickerModifier()->setTimepickerSelectedTextStyle(
        node->uiNodeHandle, color, fontInfo.c_str(), style);
}

const ArkUI_AttributeItem* GetTimePickerSelectedTextStyle(ArkUI_NodeHandle node)
{
    auto value =
        GetFullImpl()->getNodeModifiers()->getTimepickerModifier()->getTimepickerSelectedTextStyle(node->uiNodeHandle);
    g_attributeItem.string = value;
    return &g_attributeItem;
}

int32_t SetTimePickerSelectedTextStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->string) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    std::vector<std::string> params;
    StringUtils::StringSplitter(item->string, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() != NUM_5) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    ArkUI_Uint32 color = StringToColorInt(params[NUM_0].c_str());
    auto style = StringToEnumInt(params[NUM_4].c_str(), FONT_STYLES, NUM_0);
    std::string fontInfo = params[NUM_1] + '|' + params[NUM_2] + '|' + params[NUM_3];

    fullImpl->getNodeModifiers()->getTimepickerModifier()->setTimepickerSelectedTextStyle(
        node->uiNodeHandle, color, fontInfo.c_str(), style);

    return ERROR_CODE_NO_ERROR;
}

void ResetTimePickerSelectedTextStyle(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getTimepickerModifier()->resetTimepickerSelectedTextStyle(node->uiNodeHandle);
}

// TextPicker
void SetTextPickerDisappearTextStyle(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();

    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    std::vector<std::string> params;
    StringUtils::StringSplitter(value, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() != NUM_5) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return;
    }

    ArkUI_Uint32 color = StringToColorInt(params[NUM_0].c_str());
    auto style = StringToEnumInt(params[NUM_4].c_str(), FONT_STYLES, NUM_0);
    std::string fontInfo = params[NUM_1] + '|' + params[NUM_2] + '|' + params[NUM_3];

    fullImpl->getNodeModifiers()->getTextPickerModifier()->setTextPickerDisappearTextStyle(
        node->uiNodeHandle, color, fontInfo.c_str(), style);
}

const ArkUI_AttributeItem* GetTextPickerDisappearTextStyle(ArkUI_NodeHandle node)
{
    auto value =
        GetFullImpl()->getNodeModifiers()->getTextPickerModifier()->getTextPickerDisappearTextStyle(node->uiNodeHandle);
    g_attributeItem.string = value;
    return &g_attributeItem;
}

int32_t SetTextPickerDisappearTextStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->string) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    std::vector<std::string> params;
    StringUtils::StringSplitter(item->string, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() != NUM_5) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    ArkUI_Uint32 color = StringToColorInt(params[NUM_0].c_str());
    auto style = StringToEnumInt(params[NUM_4].c_str(), FONT_STYLES, NUM_0);
    std::string fontInfo = params[NUM_1] + '|' + params[NUM_2] + '|' + params[NUM_3];

    fullImpl->getNodeModifiers()->getTextPickerModifier()->setTextPickerDisappearTextStyle(
        node->uiNodeHandle, color, fontInfo.c_str(), style);

    return ERROR_CODE_NO_ERROR;
}

void ResetTextPickerDisappearTextStyle(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getTextPickerModifier()->resetTextPickerDisappearTextStyle(node->uiNodeHandle);
}

void SetTextPickerTextStyle(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();

    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    std::vector<std::string> params;
    StringUtils::StringSplitter(value, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() != NUM_5) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return;
    }

    ArkUI_Uint32 color = StringToColorInt(params[NUM_0].c_str());
    auto style = StringToEnumInt(params[NUM_4].c_str(), FONT_STYLES, NUM_0);
    std::string fontInfo = params[NUM_1] + '|' + params[NUM_2] + '|' + params[NUM_3];

    fullImpl->getNodeModifiers()->getTextPickerModifier()->setTextPickerTextStyle(
        node->uiNodeHandle, color, fontInfo.c_str(), style);
}

const ArkUI_AttributeItem* GetTextPickerTextStyle(ArkUI_NodeHandle node)
{
    auto value =
        GetFullImpl()->getNodeModifiers()->getTextPickerModifier()->getTextPickerTextStyle(node->uiNodeHandle);
    g_attributeItem.string = value;
    return &g_attributeItem;
}

int32_t SetTextPickerTextStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->string) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    std::vector<std::string> params;
    StringUtils::StringSplitter(item->string, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() != NUM_5) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    ArkUI_Uint32 color = StringToColorInt(params[NUM_0].c_str());
    auto style = StringToEnumInt(params[NUM_4].c_str(), FONT_STYLES, NUM_0);
    std::string fontInfo = params[NUM_1] + '|' + params[NUM_2] + '|' + params[NUM_3];

    fullImpl->getNodeModifiers()->getTextPickerModifier()->setTextPickerTextStyle(
        node->uiNodeHandle, color, fontInfo.c_str(), style);

    return ERROR_CODE_NO_ERROR;
}

void ResetTextPickerTextStyle(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getTextPickerModifier()->resetTextPickerTextStyle(node->uiNodeHandle);
}

void SetTextPickerSelectedTextStyle(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();

    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    std::vector<std::string> params;
    StringUtils::StringSplitter(value, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() != NUM_5) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return;
    }

    ArkUI_Uint32 color = StringToColorInt(params[NUM_0].c_str());
    auto style = StringToEnumInt(params[NUM_4].c_str(), FONT_STYLES, NUM_0);
    std::string fontInfo = params[NUM_1] + '|' + params[NUM_2] + '|' + params[NUM_3];

    fullImpl->getNodeModifiers()->getTextPickerModifier()->setTextPickerSelectedTextStyle(
        node->uiNodeHandle, color, fontInfo.c_str(), style);
}

const ArkUI_AttributeItem* GetTextPickerSelectedTextStyle(ArkUI_NodeHandle node)
{
    auto value =
        GetFullImpl()->getNodeModifiers()->getTextPickerModifier()->getTextPickerSelectedTextStyle(node->uiNodeHandle);
    g_attributeItem.string = value;
    return &g_attributeItem;
}

int32_t SetTextPickerSelectedTextStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->string) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    std::vector<std::string> params;
    StringUtils::StringSplitter(item->string, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() != NUM_5) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    ArkUI_Uint32 color = StringToColorInt(params[NUM_0].c_str());
    auto style = StringToEnumInt(params[NUM_4].c_str(), FONT_STYLES, NUM_0);
    std::string fontInfo = params[NUM_1] + '|' + params[NUM_2] + '|' + params[NUM_3];

    fullImpl->getNodeModifiers()->getTextPickerModifier()->setTextPickerSelectedTextStyle(
        node->uiNodeHandle, color, fontInfo.c_str(), style);

    return ERROR_CODE_NO_ERROR;
}

void ResetTextPickerSelectedTextStyle(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getTextPickerModifier()->resetTextPickerSelectedTextStyle(node->uiNodeHandle);
}

void SetTextPickerSelectedIndex(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();

    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    std::vector<std::string> params;
    StringUtils::StringSplitter(value, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() == NUM_0) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return;
    }
    ArkUI_Uint32 values[params.size()];
    for (int i = 0; i < params.size(); ++i) {
        values[i] = StringToInt(params[i].c_str());
    }
    fullImpl->getNodeModifiers()->getTextPickerModifier()->setTextPickerSelectedIndex(
        node->uiNodeHandle, values, params.size());
}

const ArkUI_AttributeItem* GetTextPickerSelectedIndex(ArkUI_NodeHandle node)
{
    auto value =
        GetFullImpl()->getNodeModifiers()->getTextPickerModifier()->getTextPickerSelectedIndex(node->uiNodeHandle);
    g_numberValues[0].i32 = value;
    return &g_attributeItem;
}

int32_t SetTextPickerSelectedIndex(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !LessNotEqual(item->value[0].i32, NUM_0)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    ArkUI_Uint32 values[item->size];
    for (int i = 0; i < item->size; ++i) {
        values[i] = item->value[i].i32;
    }
    fullImpl->getNodeModifiers()->getTextPickerModifier()->setTextPickerSelectedIndex(
        node->uiNodeHandle, values, item->size);
    return ERROR_CODE_NO_ERROR;
}

void ResetTextPickerSelectedIndex(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getTextPickerModifier()->resetTextPickerSelectedIndex(node->uiNodeHandle);
}

// Row&Column
int32_t SetAlignItems(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_COLUMN:
            fullImpl->getNodeModifiers()->getColumnModifier()->setColumnAlignItems(
                node->uiNodeHandle, item->value[0].i32 + NUM_1);
            break;
        case ARKUI_NODE_ROW:
            fullImpl->getNodeModifiers()->getRowModifier()->setRowAlignItems(
                node->uiNodeHandle, item->value[0].i32 + NUM_1);
            break;
        default:
            break;
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetAlignItems(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_COLUMN:
            fullImpl->getNodeModifiers()->getColumnModifier()->resetColumnAlignItems(node->uiNodeHandle);
            break;
        case ARKUI_NODE_ROW:
            fullImpl->getNodeModifiers()->getRowModifier()->resetRowAlignItems(node->uiNodeHandle);
            break;
        default:
            break;
    }
}

const ArkUI_AttributeItem* GetAlignItems(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_COLUMN:
            g_numberValues[0].i32 =
                fullImpl->getNodeModifiers()->getColumnModifier()->getColumnAlignItems(node->uiNodeHandle);
            break;
        case ARKUI_NODE_ROW:
            g_numberValues[0].i32 =
                fullImpl->getNodeModifiers()->getRowModifier()->getRowAlignItems(node->uiNodeHandle);
            break;
        default:
            break;
    }
    return &g_attributeItem;
}

int32_t SetJustifyContent(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_COLUMN:
            fullImpl->getNodeModifiers()->getColumnModifier()->setColumnJustifyContent(
                node->uiNodeHandle, item->value[0].i32 + NUM_1);
            break;
        case ARKUI_NODE_ROW:
            fullImpl->getNodeModifiers()->getRowModifier()->setRowJustifyContent(
                node->uiNodeHandle, item->value[0].i32 + NUM_1);
            break;
        default:
            break;
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetJustifyContent(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_COLUMN:
            fullImpl->getNodeModifiers()->getColumnModifier()->resetColumnJustifyContent(node->uiNodeHandle);
            break;
        case ARKUI_NODE_ROW:
            fullImpl->getNodeModifiers()->getRowModifier()->resetRowJustifyContent(node->uiNodeHandle);
            break;
        default:
            break;
    }
}

const ArkUI_AttributeItem* GetJustifyContent(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_COLUMN:
            g_numberValues[0].i32 =
                fullImpl->getNodeModifiers()->getColumnModifier()->getColumnJustifyContent(node->uiNodeHandle);
            break;
        case ARKUI_NODE_ROW:
            g_numberValues[0].i32 =
                fullImpl->getNodeModifiers()->getRowModifier()->getRowJustifyContent(node->uiNodeHandle);
            break;
        default:
            break;
    }
    return &g_attributeItem;
}

// Flex
int32_t SetFlexOptions(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    int options[NUM_5] = { 0, 0, 0, 1, 0 };
    if (item->size > NUM_0) {
        options[NUM_0] = item->value[NUM_0].i32;
    }
    if (item->size > NUM_1) {
        options[NUM_1] = item->value[NUM_1].i32;
    }
    if (item->size > NUM_2) {
        options[NUM_2] = item->value[NUM_2].i32;
    }
    if (item->size > NUM_3) {
        options[NUM_3] = item->value[NUM_3].i32;
    }
    if (item->size > NUM_4) {
        options[NUM_4] = item->value[NUM_4].i32;
    }
    fullImpl->getNodeModifiers()->getFlexModifier()->setFlexOptions(node->uiNodeHandle, options, NUM_5);
    return ERROR_CODE_NO_ERROR;
}

void ResetFlexOptions(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getFlexModifier()->resetFlexOptions(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetFlexOptions(ArkUI_NodeHandle node)
{
    ArkUIFlexOptions options;
    GetFullImpl()->getNodeModifiers()->getFlexModifier()->getFlexOptions(node->uiNodeHandle, &options);
    g_numberValues[NUM_0].i32 = options.direction;
    g_numberValues[NUM_1].i32 = options.wrap;
    g_numberValues[NUM_2].i32 = options.justifyContent;
    g_numberValues[NUM_3].i32 = options.alignItems;
    g_numberValues[NUM_4].i32 = options.alignContent;
    return &g_attributeItem;
}

int32_t SetBackgroundImageSize(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_TWO_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setBackgroundImageSize(node->uiNodeHandle,
        item->value[BACKGROUND_IMAGE_WIDTH_INDEX].f32, item->value[BACKGROUND_IMAGE_HEIGHT_INDEX].f32, 0, 0);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetBackgroundImageSizeWithStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || item->value[0].i32 < 0 ||
        item->value[0].i32 > static_cast<int32_t>(ARKUI_IMAGE_SIZE_CONTAIN)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setBackgroundImageSize(
        node->uiNodeHandle, -1.0f, -1.0f, item->value[0].i32, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

bool CheckBackgroundBlurStyleInput(const ArkUI_AttributeItem* item, int32_t size)
{
    CHECK_NULL_RETURN(item, false);
    if (BLUR_STYLE_INDEX < size &&
        (item->value[BLUR_STYLE_INDEX].i32 < 0 ||
            item->value[BLUR_STYLE_INDEX].i32 > static_cast<int32_t>(ARKUI_BLUR_STYLE_COMPONENT_ULTRA_THICK))) {
        return false;
    }
    if (COLOR_MODE_INDEX < size &&
        (item->value[COLOR_MODE_INDEX].i32 < 0 ||
            item->value[COLOR_MODE_INDEX].i32 > static_cast<int32_t>(ARKUI_COLOR_MODE_DARK))) {
        return false;
    }
    if (ADAPTIVE_COLOR_INDEX < size &&
        (item->value[ADAPTIVE_COLOR_INDEX].i32 < 0 ||
            item->value[ADAPTIVE_COLOR_INDEX].i32 > static_cast<int32_t>(ARKUI_ADAPTIVE_COLOR_AVERAGE))) {
        return false;
    }
    if (SCALE_INDEX < size &&
        (LessNotEqual(item->value[SCALE_INDEX].f32, 0.0f) || GreatNotEqual(item->value[SCALE_INDEX].f32, 1.0f))) {
        return false;
    }
    return true;
}

int32_t SetBackgroundBlurStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto isInputValid = CheckBackgroundBlurStyleInput(item, actualSize);
    if (!isInputValid) {
        return ERROR_CODE_PARAM_INVALID;
    }
    int32_t blurStyle = ARKUI_BLUR_STYLE_THIN;
    if (BLUR_STYLE_INDEX < actualSize) {
        blurStyle = item->value[BLUR_STYLE_INDEX].i32;
    }
    int32_t colorMode = ARKUI_COLOR_MODE_SYSTEM;
    if (COLOR_MODE_INDEX < actualSize) {
        colorMode = item->value[COLOR_MODE_INDEX].i32;
    }
    int32_t adaptiveColor = ARKUI_ADAPTIVE_COLOR_DEFAULT;
    if (ADAPTIVE_COLOR_INDEX < actualSize) {
        adaptiveColor = item->value[ADAPTIVE_COLOR_INDEX].i32;
    }
    float scale = 1.0f;
    if (SCALE_INDEX < actualSize) {
        scale = item->value[SCALE_INDEX].f32;
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setBackgroundBlurStyle(
        node->uiNodeHandle, blurStyle, colorMode, adaptiveColor, scale);
    return ERROR_CODE_NO_ERROR;
}

bool CheckTransformCenter(const ArkUI_AttributeItem* item, int32_t size)
{
    CHECK_NULL_RETURN(item, false);
    if (CENTER_X_PERCENT_INDEX < size && (LessNotEqual(item->value[CENTER_X_PERCENT_INDEX].f32, 0.0f) ||
                                             GreatNotEqual(item->value[CENTER_X_PERCENT_INDEX].f32, 1.0f))) {
        return false;
    }
    if (CENTER_Y_PERCENT_INDEX < size && (LessNotEqual(item->value[CENTER_Y_PERCENT_INDEX].f32, 0.0f) ||
                                             GreatNotEqual(item->value[CENTER_Y_PERCENT_INDEX].f32, 1.0f))) {
        return false;
    }
    if (CENTER_Z_PERCENT_INDEX < size && (LessNotEqual(item->value[CENTER_Z_PERCENT_INDEX].f32, 0.0f) ||
                                             GreatNotEqual(item->value[CENTER_Z_PERCENT_INDEX].f32, 1.0f))) {
        return false;
    }
    return true;
}

int32_t SetTransformCenter(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, 0);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto isTransformCenterValid = CheckTransformCenter(item, actualSize);
    if (!isTransformCenterValid) {
        return ERROR_CODE_PARAM_INVALID;
    }
    CalcDimension centerX(HALF, DimensionUnit::PERCENT);
    if (CENTER_X_INDEX < actualSize) {
        centerX.SetValue(item->value[CENTER_X_INDEX].f32);
        centerX.SetUnit(DimensionUnit::VP);
    }
    CalcDimension centerY(HALF, DimensionUnit::PERCENT);
    if (CENTER_Y_INDEX < actualSize) {
        centerY.SetValue(item->value[CENTER_Y_INDEX].f32);
        centerY.SetUnit(DimensionUnit::VP);
    }
    CalcDimension centerZ(0, DimensionUnit::VP);
    if (CENTER_Z_INDEX < actualSize) {
        centerZ.SetValue(item->value[CENTER_Z_INDEX].f32);
    }
    if (CENTER_X_PERCENT_INDEX < actualSize) {
        centerX.SetValue(item->value[CENTER_X_PERCENT_INDEX].f32);
        centerX.SetUnit(DimensionUnit::PERCENT);
    }
    if (CENTER_Y_PERCENT_INDEX < actualSize) {
        centerY.SetValue(item->value[CENTER_Y_PERCENT_INDEX].f32);
        centerY.SetUnit(DimensionUnit::PERCENT);
    }
    if (CENTER_Z_PERCENT_INDEX < actualSize) {
        centerZ.SetValue(item->value[CENTER_Z_PERCENT_INDEX].f32);
        centerZ.SetUnit(DimensionUnit::PERCENT);
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setTransitionCenter(node->uiNodeHandle, centerX.Value(),
        static_cast<int32_t>(centerX.Unit()), centerY.Value(), static_cast<int32_t>(centerY.Unit()), centerZ.Value(),
        static_cast<int32_t>(centerZ.Unit()));
    return ERROR_CODE_NO_ERROR;
}

int32_t SetOpacityTransition(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_TREE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (!CheckAnimation(item, actualSize, OPACITY_ANIMATION_BASE)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    float opacity = DEFAULT_OPACITY;
    if (actualSize > 0) {
        opacity = item->value[0].f32;
    }
    ArkUIAnimationOptionType animationOption;
    ParseAnimation(item, actualSize, animationOption, OPACITY_ANIMATION_BASE);
    fullImpl->getNodeModifiers()->getCommonModifier()->setOpacityTransition(
        node->uiNodeHandle, opacity, &animationOption);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetRotateTransition(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_SEVEN_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (!CheckAnimation(item, actualSize, ROTATE_ANIMATION_BASE)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    std::array<float, ARRAY_SIZE> rotateArray;
    for (int32_t i = 0; i < actualSize && i < rotateArray.size(); i++) {
        rotateArray[i] = item->value[i].f32;
    }
    float angle = 0.0f;
    if (ROTATE_ANGLE_INDEX < actualSize) {
        angle = item->value[ROTATE_ANGLE_INDEX].f32;
    }
    float perspective = 0.0f;
    if (ROTATE_PERSPECTIVE_INDEX < actualSize) {
        perspective = item->value[ROTATE_PERSPECTIVE_INDEX].f32;
    }
    ArkUIAnimationOptionType animationOption;
    ParseAnimation(item, actualSize, animationOption, ROTATE_ANIMATION_BASE);
    fullImpl->getNodeModifiers()->getCommonModifier()->setRotateTransition(
        node->uiNodeHandle, &rotateArray[0], ARRAY_SIZE, perspective, angle, &animationOption);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetScaleTransition(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_FIVE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (!CheckAnimation(item, actualSize, SCALE_ANIMATION_BASE)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    std::array<float, ARRAY_SIZE> scaleFloatArray;
    for (size_t i = 0; i < actualSize && i < scaleFloatArray.size(); i++) {
        scaleFloatArray[i] = item->value[i].f32;
    }
    ArkUIAnimationOptionType animationOption;
    ParseAnimation(item, actualSize, animationOption, SCALE_ANIMATION_BASE);
    fullImpl->getNodeModifiers()->getCommonModifier()->setScaleTransition(
        node->uiNodeHandle, &scaleFloatArray[0], scaleFloatArray.size(), &animationOption);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetTranslateTransition(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_FIVE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (!CheckAnimation(item, actualSize, TRANSLATE_ANIMATION_BASE)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    CalcDimension xDimension(0, DimensionUnit::VP);
    if (X_INDEX < actualSize) {
        xDimension.SetValue(item->value[X_INDEX].f32);
    }
    CalcDimension yDimension(0, DimensionUnit::VP);
    if (Y_INDEX < actualSize) {
        yDimension.SetValue(item->value[Y_INDEX].f32);
    }
    CalcDimension zDimension(0, DimensionUnit::VP);
    if (Z_INDEX < actualSize) {
        zDimension.SetValue(item->value[Z_INDEX].f32);
    }
    ArkUIAnimationOptionType animationOption;
    ParseAnimation(item, actualSize, animationOption, TRANSLATE_ANIMATION_BASE);
    fullImpl->getNodeModifiers()->getCommonModifier()->setTranslateTransition(node->uiNodeHandle, xDimension.Value(),
        static_cast<int32_t>(xDimension.Unit()), yDimension.Value(), static_cast<int32_t>(yDimension.Unit()),
        zDimension.Value(), static_cast<int32_t>(zDimension.Unit()), &animationOption);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetOffset(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_TWO_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    CalcDimension xDimension(0, DimensionUnit::VP);
    if (NUM_0 < actualSize) {
        xDimension.SetValue(item->value[NUM_0].f32);
    }
    CalcDimension yDimension(0, DimensionUnit::VP);
    if (NUM_1 < actualSize) {
        yDimension.SetValue(item->value[NUM_1].f32);
    }
    std::array<float, TWO> offsetValue = { xDimension.Value(), yDimension.Value() };
    std::array<int32_t, TWO> offsetUnit = { static_cast<int32_t>(xDimension.Unit()),
        static_cast<int32_t>(yDimension.Unit()) };
    fullImpl->getNodeModifiers()->getCommonModifier()->setOffset(node->uiNodeHandle, &offsetValue[0], &offsetUnit[0]);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetMarkAnchor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_TWO_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    CalcDimension xDimension(0, DimensionUnit::VP);
    if (NUM_0 < actualSize) {
        xDimension.SetValue(item->value[NUM_0].f32);
    }
    CalcDimension yDimension(0, DimensionUnit::VP);
    if (NUM_1 < actualSize) {
        yDimension.SetValue(item->value[NUM_1].f32);
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setMarkAnchor(node->uiNodeHandle, xDimension.Value(),
        static_cast<int32_t>(xDimension.Unit()), yDimension.Value(), static_cast<int32_t>(yDimension.Unit()));
    return ERROR_CODE_NO_ERROR;
}

int32_t SetAlignRules(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();
    std::vector<std::string> alignRulesVector;
    StringUtils::StringSplitter(std::string(item->string), ' ', alignRulesVector);
    const char* alignAnchorArray[ALIGN_RULES_ARRAY_LENGTH];
    ArkUI_Int32 alignStyleArray[ALIGN_RULES_ARRAY_LENGTH];
    for (size_t i = 0; i < alignRulesVector.size() && i < ALIGN_RULES_ARRAY_LENGTH; i++) {
        if (i % TWO == 0) {
            alignAnchorArray[i / TWO] = alignRulesVector[i].c_str();
        } else {
            alignStyleArray[i / TWO] =
                ((i / TWO) < HORIZONTAL_DIRECTION_RANGE)
                    ? StringToEnumInt(alignRulesVector[i].c_str(), ALIGN_RULES_HORIZONTAL_ARRAY, 0)
                    : StringToEnumInt(alignRulesVector[i].c_str(), ALIGN_RULES_VERTICAL_ARRAY, 0);
        }
    }
    // todo
    fullImpl->getNodeModifiers()->getCommonModifier()->setAlignRules(
        node->uiNodeHandle, nullptr, nullptr, ALIGN_RULES_ARRAY_LENGTH);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetTextContent(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    if (!CheckAttributeString(item)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getTextModifier()->setContent(node->uiNodeHandle, item->string);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetLineHeight(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    CalcDimension lineHeight(item->value[0].f32, DimensionUnit::FP);
    switch (node->type) {
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->setTextLineHeight(
                node->uiNodeHandle, lineHeight.Value(), static_cast<int32_t>(DimensionUnit::FP));
            break;
        case ARKUI_NODE_SPAN:
            fullImpl->getNodeModifiers()->getSpanModifier()->setSpanLineHeight(
                node->uiNodeHandle, lineHeight.Value(), static_cast<int32_t>(DimensionUnit::FP));
            break;
        default:
            break;
    }
    return ERROR_CODE_NO_ERROR;
}

int32_t SetDecoration(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < 0 || item->value[0].i32 > static_cast<int32_t>(ARKUI_TEXT_DECORATION_TYPE_LINE_THROUGH)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    int32_t decoration = item->value[0].i32;
    auto decorationColor = Color::BLACK.GetValue();
    if (DECORATION_COLOR_INDEX < actualSize) {
        decorationColor = item->value[DECORATION_COLOR_INDEX].u32;
    }
    switch (node->type) {
        case ARKUI_NODE_SPAN:
            fullImpl->getNodeModifiers()->getSpanModifier()->setSpanDecoration(
                node->uiNodeHandle, decoration, decorationColor, 0);
            break;
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->setTextDecoration(
                node->uiNodeHandle, decoration, decorationColor, 0);
        default:
            break;
    }
    return ERROR_CODE_NO_ERROR;
}

int32_t SetTextCase(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < 0 || item->value[0].i32 > static_cast<int32_t>(ARKUI_TEXT_CASE_UPPER)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    switch (node->type) {
        case ARKUI_NODE_SPAN:
            fullImpl->getNodeModifiers()->getSpanModifier()->setSpanTextCase(node->uiNodeHandle, item->value[0].i32);
            break;
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->setTextCase(node->uiNodeHandle, item->value[0].i32);
        default:
            break;
    }
    return ERROR_CODE_NO_ERROR;
}

int32_t SetLetterSpacing(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    ArkUIStringAndFloat letterSpacingValue = { item->value[0].f32, nullptr };
    switch (node->type) {
        case ARKUI_NODE_SPAN:
            fullImpl->getNodeModifiers()->getSpanModifier()->setSpanLetterSpacing(
                node->uiNodeHandle, &letterSpacingValue);
            break;
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->setTextLetterSpacing(
                node->uiNodeHandle, &letterSpacingValue);
        default:
            break;
    }
    return ERROR_CODE_NO_ERROR;
}

int32_t SetMaxLines(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    switch (node->type) {
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->setTextMaxLines(node->uiNodeHandle, item->value[0].i32);
            break;
        default:
            break;
    }
    return ERROR_CODE_NO_ERROR;
}

int32_t SetTextAlign(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < 0 || item->value[0].i32 > static_cast<int32_t>(ARKUI_TEXT_ALIGNMENT_JUSTIFY)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    switch (node->type) {
        case ARKUI_NODE_TEXT_INPUT:
            fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputTextAlign(
                node->uiNodeHandle, item->value[0].i32);
            break;
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->setTextAlign(node->uiNodeHandle, item->value[0].i32);
            break;
        default:
            break;
    }
    return ERROR_CODE_NO_ERROR;
}

int32_t SetTextOverflow(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < 0 || item->value[0].i32 > static_cast<int32_t>(ARKUI_TEXT_OVERFLOW_MARQUEE)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getTextModifier()->setTextOverflow(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetTextIndent(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    struct ArkUIStringAndFloat offset = { item->value[0].f32, nullptr };
    fullImpl->getNodeModifiers()->getTextModifier()->setTextIndent(node->uiNodeHandle, &offset);
    return ERROR_CODE_NO_ERROR;
}

void ResetTextIndent(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    struct ArkUIStringAndFloat offset = { 0.0, nullptr };
    fullImpl->getNodeModifiers()->getTextModifier()->setTextIndent(node->uiNodeHandle, &offset);
}

int32_t SetSpanContent(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    if (!CheckAttributeString(item)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getSpanModifier()->setContent(node->uiNodeHandle, item->string);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetImageSpanSrc(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    if (!CheckAttributeString(item)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getImageModifier()->setSrc(node->uiNodeHandle, item->string);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetVerticalAlign(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < 0 || item->value[0].i32 > static_cast<int32_t>(ARKUI_IMAGE_SPAN_ALIGNMENT_TOP)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getImageSpanModifier()->setImageSpanVerticalAlign(
        node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetImageSrc(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    if (!CheckAttributeString(item)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getImageModifier()->setSrc(node->uiNodeHandle, item->string);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetObjectFit(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < 0 || item->value[0].i32 > static_cast<int32_t>(ARKUI_OBJECT_FIT_NONE)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    switch (node->type) {
        case ARKUI_IMAGE_SPAN:
            fullImpl->getNodeModifiers()->getImageSpanModifier()->setImageSpanObjectFit(
                node->uiNodeHandle, item->value[0].i32);
            break;
        case ARKUI_IMAGE:
            fullImpl->getNodeModifiers()->getImageModifier()->setObjectFit(node->uiNodeHandle, item->value[0].i32);
            break;
        default:
            break;
    }
    return ERROR_CODE_NO_ERROR;
}

int32_t SetInterpolation(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < 0 || item->value[0].i32 > static_cast<int32_t>(ARKUI_IMAGE_INTERPOLATION_HIGH)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getImageModifier()->setImageInterpolation(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetObjectRepeat(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < 0 || item->value[0].i32 > static_cast<int32_t>(ARKUI_IMAGE_REPEAT_XY)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getImageModifier()->setObjectRepeat(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetColorFilter(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_TWENTY_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    std::vector<float> colorFloatArray;
    for (size_t i = 0; i < actualSize && i < REQUIRED_TWENTY_PARAM; i++) {
        colorFloatArray.emplace_back(static_cast<float>(item->value[i].i32));
    }
    fullImpl->getNodeModifiers()->getImageModifier()->setColorFilter(
        node->uiNodeHandle, &colorFloatArray[0], colorFloatArray.size());
    return ERROR_CODE_NO_ERROR;
}

int32_t SetAutoResize(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getImageModifier()->setAutoResize(
        node->uiNodeHandle, static_cast<bool>(item->value[0].i32));
    return ERROR_CODE_NO_ERROR;
}

int32_t SetAlt(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    if (!CheckAttributeString(item)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getImageModifier()->setAlt(node->uiNodeHandle, item->string, "", "");
    return ERROR_CODE_NO_ERROR;
}

void ResetBackgroundImageSize(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetBackgroundImageSize(node->uiNodeHandle);
}

void ResetBackgroundImageSizeWithStyle(ArkUI_NodeHandle node)
{
    ResetBackgroundImageSize(node);
}

void ResetBackgroundBlurStyle(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetBackgroundBlurStyle(node->uiNodeHandle);
}

void ResetTransformCenter(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    CalcDimension centerX(HALF, DimensionUnit::PERCENT);
    CalcDimension centerY(HALF, DimensionUnit::PERCENT);
    CalcDimension centerZ(0, DimensionUnit::VP);
    fullImpl->getNodeModifiers()->getCommonModifier()->setTransitionCenter(node->uiNodeHandle, centerX.Value(),
        static_cast<int32_t>(centerX.Unit()), centerY.Value(), static_cast<int32_t>(centerY.Unit()), centerZ.Value(),
        static_cast<int32_t>(centerZ.Unit()));
}

void ResetOpacityTransition(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    ArkUIAnimationOptionType animationOption;
    ResetAnimation(animationOption);
    fullImpl->getNodeModifiers()->getCommonModifier()->setOpacityTransition(
        node->uiNodeHandle, DEFAULT_OPACITY, &animationOption);
}

void ResetRotateTransition(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    std::array<float, ARRAY_SIZE> rotateArray;
    ArkUIAnimationOptionType animationOption;
    ResetAnimation(animationOption);
    fullImpl->getNodeModifiers()->getCommonModifier()->setRotateTransition(
        node->uiNodeHandle, &rotateArray[0], ARRAY_SIZE, 0.0f, 0.0f, &animationOption);
}

void ResetScaleTransition(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    std::array<float, ARRAY_SIZE> scaleFloatArray;
    ArkUIAnimationOptionType animationOption;
    ResetAnimation(animationOption);
    fullImpl->getNodeModifiers()->getCommonModifier()->setScaleTransition(
        node->uiNodeHandle, &scaleFloatArray[0], scaleFloatArray.size(), &animationOption);
}

void ResetTranslateTransition(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    std::array<float, ARRAY_SIZE> scaleFloatArray;
    ArkUIAnimationOptionType animationOption;
    ResetAnimation(animationOption);
    fullImpl->getNodeModifiers()->getCommonModifier()->setScaleTransition(
        node->uiNodeHandle, &scaleFloatArray[0], scaleFloatArray.size(), &animationOption);
    fullImpl->getNodeModifiers()->getCommonModifier()->setTranslateTransition(node->uiNodeHandle, 0.0f,
        static_cast<int32_t>(DimensionUnit::VP), 0.0f, static_cast<int32_t>(DimensionUnit::VP), 0.0f,
        static_cast<int32_t>(DimensionUnit::VP), &animationOption);
}

void ResetOffset(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetOffset(node->uiNodeHandle);
}

void ResetMarkAnchor(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetMarkAnchor(node->uiNodeHandle);
}

void ResetAlignRules(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetAlignRules(node->uiNodeHandle);
}

void ResetTextContent(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextModifier()->setContent(node->uiNodeHandle, "");
}

void ResetLineHeight(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->resetTextLineHeight(node->uiNodeHandle);
            break;
        default:
            break;
    }
}

void ResetDecoration(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_SPAN:
            fullImpl->getNodeModifiers()->getSpanModifier()->resetSpanDecoration(node->uiNodeHandle);
            break;
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->resetTextDecoration(node->uiNodeHandle);
        default:
            break;
    }
}

void ResetTextCase(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_SPAN:
            fullImpl->getNodeModifiers()->getSpanModifier()->resetSpanTextCase(node->uiNodeHandle);
            break;
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->resetTextCase(node->uiNodeHandle);
        default:
            break;
    }
}

void ResetLetterSpacing(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_SPAN:
            fullImpl->getNodeModifiers()->getSpanModifier()->resetSpanLetterSpacing(node->uiNodeHandle);
            break;
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->resetTextLetterSpacing(node->uiNodeHandle);
        default:
            break;
    }
}

void ResetMaxLines(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->resetTextMaxLines(node->uiNodeHandle);
            break;
        default:
            break;
    }
}

void ResetTextAlign(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->resetTextAlign(node->uiNodeHandle);
            break;
        default:
            break;
    }
}

void ResetTextOverflow(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextModifier()->resetTextOverflow(node->uiNodeHandle);
}

void ResetSpanContent(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSpanModifier()->setContent(node->uiNodeHandle, "");
}

void ResetImageSpanSrc(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageModifier()->setSrc(node->uiNodeHandle, "");
}

void ResetVerticalAlign(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageSpanModifier()->setImageSpanVerticalAlign(
        node->uiNodeHandle, static_cast<int32_t>(ARKUI_IMAGE_SPAN_ALIGNMENT_BASELINE));
}

void ResetImageSrc(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageModifier()->setSrc(node->uiNodeHandle, "");
}

void ResetObjectFit(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageModifier()->resetObjectFit(node->uiNodeHandle);
}

void ResetInterpolation(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageModifier()->resetImageInterpolation(node->uiNodeHandle);
}

void ResetObjectRepeat(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageModifier()->resetObjectRepeat(node->uiNodeHandle);
}

void ResetColorFilter(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageModifier()->resetColorFilter(node->uiNodeHandle);
}

void ResetAutoResize(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageModifier()->resetAutoResize(node->uiNodeHandle);
}

void ResetAlt(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageModifier()->resetAlt(node->uiNodeHandle);
}

int32_t SetCheckboxSelect(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !CheckAttributeIsBool(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->setSelect(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetCheckboxSelect(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->getSelect(node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

void ResetCheckboxSelect(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->resetSelect(node->uiNodeHandle);
}

int32_t SetCheckboxSelectedColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->setSelectedColor(node->uiNodeHandle, item->value[0].u32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetCheckboxSelectedColor(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->getSelectedColor(node->uiNodeHandle);
    g_numberValues[0].u32 = resultValue;
    return &g_attributeItem;
}

void ResetCheckboxSelectedColor(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->resetSelectedColor(node->uiNodeHandle);
}

int32_t SetCheckboxUnSelectedColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->setUnSelectedColor(
        node->uiNodeHandle, item->value[0].u32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetCheckboxUnSelectedColor(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->getUnSelectedColor(node->uiNodeHandle);
    g_numberValues[0].u32 = resultValue;
    return &g_attributeItem;
}

void ResetCheckboxUnSelectedColor(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->resetUnSelectedColor(node->uiNodeHandle);
}

int32_t SetCheckboxMark(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // defalut white
    int strokeColor = item->value[0].u32;
    double size = -1;
    if (item->size > 1) {
        //check 2 for size
        if (LessNotEqual(item->value[1].f32, 0.0f)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        //set 2 for size
        size = item->value[1].f32;
    }
    // defalut 2
    double strokeWidth = 2;
    if (item->size > ALLOW_SIZE_2) {
        //check 2 for strokeWidth
        if (LessNotEqual(item->value[2].f32, 0.0f)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        //set 2 for strokeWidth
        strokeWidth = item->value[2].f32;
    }

    GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->setMark(
        node->uiNodeHandle, strokeColor, size, strokeWidth);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetCheckboxMark(ArkUI_NodeHandle node)
{
    auto strokeColor = GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->getCheckMarkColor(node->uiNodeHandle);
    auto size = GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->getCheckMarkSize(node->uiNodeHandle);
    auto strokeWidth = GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->getCheckMarkWidth(node->uiNodeHandle);
    int index = 0;
    g_numberValues[index++].u32 = strokeColor;
    g_numberValues[index++].f32 = size;
    g_numberValues[index++].f32 = strokeWidth;
    g_attributeItem.size = index;
    return &g_attributeItem;
}

void ResetCheckboxMark(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->resetMark(node->uiNodeHandle);
}

int32_t SetCheckboxShape(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !CheckAttributeIsCheckboxShape(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->setCheckboxShape(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetCheckboxShape(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->getCheckboxShape(node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

void ResetCheckboxShape(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->resetCheckboxShape(node->uiNodeHandle);
}

int32_t SetSliderBlockColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->setBlockColor(node->uiNodeHandle, item->value[0].u32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetSliderBlockColor(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getSliderModifier()->getBlockColor(node->uiNodeHandle);
    g_numberValues[0].u32 = resultValue;
    return &g_attributeItem;
}

void ResetSliderBlockColor(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->resetBlockColor(node->uiNodeHandle);
}

int32_t SetSliderTrackColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->setTrackBackgroundColor(
        node->uiNodeHandle, item->value[0].u32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetSliderTrackColor(ArkUI_NodeHandle node)
{
    auto resultValue =
        GetFullImpl()->getNodeModifiers()->getSliderModifier()->getTrackBackgroundColor(node->uiNodeHandle);
    g_numberValues[0].u32 = resultValue;
    return &g_attributeItem;
}

void ResetSliderTrackColor(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->resetTrackBackgroundColor(node->uiNodeHandle);
}

int32_t SetSliderSelectedColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->setSelectColor(node->uiNodeHandle, item->value[0].u32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetSliderSelectedColor(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getSliderModifier()->getSelectColor(node->uiNodeHandle);
    g_numberValues[0].u32 = resultValue;
    return &g_attributeItem;
}

void ResetSliderSelectedColor(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->resetSelectColor(node->uiNodeHandle);
}

int32_t SetSliderShowSteps(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !CheckAttributeIsBool(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->setShowSteps(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetSliderShowSteps(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getSliderModifier()->getShowSteps(node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

void ResetSliderShowSteps(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->resetShowSteps(node->uiNodeHandle);
}

int32_t SetSliderBlockStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !CheckAttributeIsSliderBlockStyle(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    int style = item->value[0].i32;

    if (style == NUM_1) {
        if (item->string == nullptr) {
            return ERROR_CODE_PARAM_INVALID;
        }
        // image
        std::string src(item->string);
        std::string bundle;
        std::string module;
        GetFullImpl()->getNodeModifiers()->getSliderModifier()->setSliderBlockImage(
            node->uiNodeHandle, src.c_str(), bundle.c_str(), module.c_str());
    } else if (style == NUM_2) {
        if (item->size == 0) {
            return ERROR_CODE_PARAM_INVALID;
        }
        auto* fullImpl = GetFullImpl();
        if (item->value[1].i32 == ArkUI_ClipType::ARKUI_CLIP_TYPE_PATH) {
            ArkUI_Float32 pathAttributes[NUM_2];
            if (LessNotEqual(item->value[NUM_2].f32, 0.0f) || LessNotEqual(item->value[NUM_3].f32, 0.0f)) {
                return ERROR_CODE_PARAM_INVALID;
            } else {
                pathAttributes[NUM_0] = item->value[NUM_2].f32;
                pathAttributes[NUM_1] = item->value[NUM_3].f32;
            }

            fullImpl->getNodeModifiers()->getSliderModifier()->setSliderBlockPath(
                node->uiNodeHandle, "path", pathAttributes, item->string);
        } else {
            ArkUI_Float32 attributes[item->size - NUM_2];
            for (int i = NUM_2; i < item->size; i++) {
                if (LessNotEqual(item->value[i].f32, 0.0f)) {
                    return ERROR_CODE_PARAM_INVALID;
                } else {
                    attributes[i - NUM_2] = item->value[i].f32;
                }
            }
            fullImpl->getNodeModifiers()->getSliderModifier()->setSliderBlockShape(
                node->uiNodeHandle, ShapeToString(item->value[1].i32).c_str(), attributes, item->size - NUM_2);
        }
    }
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->setSliderBlockType(node->uiNodeHandle, style);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetSliderBlockStyle(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getSliderModifier()->getBlockType(node->uiNodeHandle);
    //index 0 style
    g_numberValues[0].i32 = resultValue;
    switch (resultValue) {
        case NUM_1: {
            auto imageValue =
                GetFullImpl()->getNodeModifiers()->getSliderModifier()->getBlockImageValue(node->uiNodeHandle);
            g_attributeItem.string = imageValue;
            break;
        }
        case NUM_2: {
            ArkUI_Float32 values[NUM_5];
            auto pathCommands =
                GetFullImpl()->getNodeModifiers()->getSliderModifier()->getSliderBlockShape(node->uiNodeHandle, values);
            //index 1 shapeType
            g_numberValues[1].i32 = values[0];
            //index 2 width
            g_numberValues[2].f32 = values[1];
            //index 3 height
            g_numberValues[3].f32 = values[2];
            g_attributeItem.size = NUM_3;
            ArkUI_ShapeType shapeType = static_cast<ArkUI_ShapeType>(values[0]);
            if (shapeType == ArkUI_ShapeType::ARKUI_SHAPE_TYPE_RECT) {
                //index 4 width
                g_numberValues[4].f32 = values[3];
                //index 5 height
                g_numberValues[5].f32 = values[4];
                g_attributeItem.size = NUM_6;
            } else if (shapeType == ArkUI_ShapeType::ARKUI_SHAPE_TYPE_PATH) {
                g_attributeItem.string = pathCommands;
            }
            break;
        }
        default:
            break;
    }

    return &g_attributeItem;
}

void ResetSliderBlockStyle(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->resetSliderBlockImage(node->uiNodeHandle);
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->resetSliderBlockShape(node->uiNodeHandle);
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->resetSliderBlockType(node->uiNodeHandle);
}

int32_t SetSliderValue(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !CheckRangFloat(ZERO_F, HUNDRED, item->value[0].f32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->setSliderValue(node->uiNodeHandle, item->value[0].f32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetSliderValue(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getSliderModifier()->getSliderValue(node->uiNodeHandle);
    g_numberValues[0].f32 = resultValue;
    return &g_attributeItem;
}

void ResetSliderValue(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->resetSliderValue(node->uiNodeHandle);
}

int32_t SetSliderMinValue(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !CheckRangFloat(ZERO_F, HUNDRED, item->value[0].f32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->setMinLabel(node->uiNodeHandle, item->value[0].f32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetSliderMinValue(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getSliderModifier()->getMinLabel(node->uiNodeHandle);
    g_numberValues[0].f32 = resultValue;
    return &g_attributeItem;
}

void ResetSliderMinValue(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->resetMinLabel(node->uiNodeHandle);
}

int32_t SetSliderMaxValue(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !CheckRangFloat(ZERO_F, HUNDRED, item->value[0].f32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->setMaxLabel(node->uiNodeHandle, item->value[0].f32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetSliderMaxValue(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getSliderModifier()->getMaxLabel(node->uiNodeHandle);
    g_numberValues[0].f32 = resultValue;
    return &g_attributeItem;
}

void ResetSliderMaxValue(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->resetMaxLabel(node->uiNodeHandle);
}

int32_t SetSliderStep(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !CheckRangFloat(SLIDER_STEP_MIN_F, HUNDRED, item->value[0].f32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->setStep(node->uiNodeHandle, item->value[0].f32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetSliderStep(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getSliderModifier()->getStep(node->uiNodeHandle);
    g_numberValues[0].f32 = resultValue;
    return &g_attributeItem;
}

void ResetSliderStep(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->resetStep(node->uiNodeHandle);
}

int32_t SetSliderDirection(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !CheckAttributeIsSliderDirection(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->setDirection(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetSliderDirection(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getSliderModifier()->getDirection(node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

void ResetSliderDirection(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->resetDirection(node->uiNodeHandle);
}

int32_t SetSliderReverse(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !CheckAttributeIsBool(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->setReverse(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetSliderReverse(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getSliderModifier()->getReverse(node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

void ResetSliderReverse(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->resetReverse(node->uiNodeHandle);
}

int32_t SetSliderStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !CheckAttributeIsSliderStyle(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->setSliderStyle(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetSliderStyle(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getSliderModifier()->getSliderStyle(node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

void ResetSliderStyle(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->resetSliderStyle(node->uiNodeHandle);
}

int32_t SetRefreshRefreshing(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !CheckAttributeIsBool(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getRefreshModifier()->setRefreshing(
        node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetRefreshRefreshing(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getRefreshModifier()->getRefreshing(node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}


bool CheckIfAttributeLegal(ArkUI_NodeHandle node, int32_t type)
{
    if (node->type == ARKUI_NODE_SPAN) {
        auto it = std::find(SPAN_ATTRIBUTES.begin(), SPAN_ATTRIBUTES.end(), type);
        if (it != SPAN_ATTRIBUTES.end()) {
            return true;
        }
        return false;
    }
    return true;
}

using Setter = void(ArkUI_NodeHandle node, const char* value);
using Resetter = void(ArkUI_NodeHandle node);

int32_t SetCommonAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* value)
{
    using Setter = int32_t(ArkUI_NodeHandle node, const ArkUI_AttributeItem* value);
    static Setter* setters[] = {
        SetWidth,
        SetHeight,
        SetBackgroundColor,
        SetBackgroundImage,
        SetPadding,
        SetKey,
        SetEnabled,
        SetMargin,
        SetTranslate,
        SetScale,
        SetRotate,
        SetBrightness,
        SetSaturate,
        SetBlur,
        SetLinearGradient,
        SetAlign,
        SetOpacity,
        SetBorderWidth,
        SetBorderRadius,
        SetBorderColor,
        SetBorderStyle,
        SetZIndex,
        SetVisibility,
        SetClip,
        SetClipShape,
        SetTransform,
        SetHitTestBehavior,
        SetPosition,
        SetShadow,
        SetCustomShadow,
        SetBackgroundImageSize,
        SetBackgroundImageSizeWithStyle,
        SetBackgroundBlurStyle,
        SetTransformCenter,
        SetOpacityTransition,
        SetRotateTransition,
        SetScaleTransition,
        SetTranslateTransition,
        SetFocusable,
        SetDefaultFocus,
        SetResponseRegion,
        SetOverlay,
        SetSweepGradient,
        SetRadialGradient,
        SetMask,
        SetBlendMode,
        SetDirection,
        SetConstraintSize,
        SetGrayscale,
        SetInvert,
        SetSepia,
        SetContrast,
        SetForegroundColor,
        SetOffset,
        SetMarkAnchor,
        SetBackgroundImagePosition,
        SetAlignRules,
        SetAlignSelf,
        SetFlexGrow,
        SetFlexShrink,
        SetFlexBasis,
        SetAccessibilityGroup,
        SetAccessibilityText,
        SetAccessibilityLevel,
        SetAccessibilityDescription,
        SetNeedFocus,
    };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "common node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, value);
}

const ArkUI_AttributeItem* GetCommonAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Getter = const ArkUI_AttributeItem*(ArkUI_NodeHandle node);
    static Getter* getters[] = {
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        GetOpacity,
        GetBorderWidth,
        GetBorderRadius,
        GetBorderColor,
        GetBorderStyle,
        GetZIndex,
        GetVisibility,
        GetClip,
        GetClipShape,
        GetTransform,
        GetHitTestBehavior,
        GetPosition,
        GetShadow,
        GetCustomShadow,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        GetFocusable,
        GetDefaultFocus,
        GetResponseRegion,
        GetOverlay,
        GetSweepGradient,
        GetRadialGradient,
        GetMask,
        GetBlendMode,
        GetDirection,
        GetConstraintSize,
        GetGrayscale,
        GetInvert,
        GetSepia,
        GetContrast,
        GetForegroundColor,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        GetAlignSelf,
        GetFlexGrow,
        GetFlexShrink,
        GetFlexBasis,
        GetAccessibilityGroup,
        GetAccessibilityText,
        GetAccessibilityLevel,
        GetAccessibilityDescription,
        GetNeedFocus,
    };
    if (subTypeId >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "common node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    g_attributeItem.size = RETURN_SIZE_ONE;
    return getters[subTypeId](node);
}

void ResetCommonAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Resetter = void(ArkUI_NodeHandle node);
    static Resetter* resetters[] = {
        ResetWidth,
        ResetHeight,
        ResetBackgroundColor,
        ResetBackgroundImage,
        ResetPadding,
        ResetKey,
        ResetEnabled,
        ResetMargin,
        ResetTranslate,
        ResetScale,
        ResetRotate,
        ResetBrightness,
        ResetSaturate,
        ResetBlur,
        ResetLinearGradient,
        ResetAlign,
        ResetOpacity,
        ResetBorderWidth,
        ResetBorderRadius,
        ResetBorderColor,
        ResetBorderStyle,
        ResetZIndex,
        ResetVisibility,
        ResetClip,
        ResetClipShape,
        ResetTransform,
        ResetHitTestBehavior,
        ResetPosition,
        ResetShadow,
        ResetCustomShadow,
        ResetBackgroundImageSize,
        ResetBackgroundImageSizeWithStyle,
        ResetBackgroundBlurStyle,
        ResetTransformCenter,
        ResetOpacityTransition,
        ResetRotateTransition,
        ResetScaleTransition,
        ResetTranslateTransition,
        ResetFocusable,
        ResetDefaultFocus,
        ResetResponseRegion,
        ResetOverlay,
        ResetSweepGradient,
        ResetRadialGradient,
        nullptr,
        ResetBlendMode,
        ResetDirection,
        ResetConstraintSize,
        ResetGrayscale,
        ResetInvert,
        ResetSepia,
        ResetContrast,
        ResetForegroundColor,
        ResetOffset,
        ResetMarkAnchor,
        ResetBackgroundImagePosition,
        ResetAlignRules,
        ResetAlignSelf,
        ResetFlexGrow,
        ResetFlexShrink,
        ResetFlexBasis,
        ResetAccessibilityGroup,
        ResetAccessibilityText,
        ResetAccessibilityLevel,
        ResetAccessibilityDescription,
    };
    if (subTypeId >= sizeof(resetters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "common node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    resetters[subTypeId](node);
}

int32_t SetTextAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* value)
{
    using Setter = int32_t(ArkUI_NodeHandle node, const ArkUI_AttributeItem* value);
    static Setter* setters[] = { SetTextContent, SetFontColor, SetFontSize, SetFontStyle, SetFontWeight, SetLineHeight,
        SetDecoration, SetTextCase, SetLetterSpacing, SetMaxLines, SetTextAlign, SetTextOverflow, SetTextFontFamily,
        SetTextCopyOption, SetTextBaselineOffset, SetTextShadow, SetTextMinFontSize, SetTextMaxFontSize, SetTextFont,
        SetTextHeightAdaptivePolicy, SetTextIndent };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "text node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, value);
}

const ArkUI_AttributeItem* GetTextAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Getter = const ArkUI_AttributeItem*(ArkUI_NodeHandle node);
    static Getter* getters[] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, GetTextFontFamily, GetTextCopyOption, nullptr, nullptr, GetTextMinFontSize,
        GetTextMaxFontSize, GetTextFont, GetTextHeightAdaptivePolicy, nullptr };
    if (subTypeId >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "slider node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    g_attributeItem.size = RETURN_SIZE_ONE;
    return getters[subTypeId](node);
}

void ResetTextAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = { ResetTextContent, ResetFontColor, ResetFontSize, ResetFontStyle, ResetFontWeight,
        ResetLineHeight, ResetDecoration, ResetTextCase, ResetLetterSpacing, ResetMaxLines, ResetTextAlign,
        ResetTextOverflow, ResetTextFontFamily, ResetTextCopyOption, ResetTextBaselineOffset, ResetTextShadow,
        ResetTextMinFontSize, ResetTextMaxFontSize, ResetTextFont, ResetTextHeightAdaptivePolicy, ResetTextIndent };
    if (subTypeId >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "text node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    resetters[subTypeId](node);
}

int32_t SetSpanAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* value)
{
    using Setter = int32_t(ArkUI_NodeHandle node, const ArkUI_AttributeItem* value);
    static Setter* setters[] = { SetSpanContent };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "span node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, value);
}

int32_t SetImageSpanAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* value)
{
    using Setter = int32_t(ArkUI_NodeHandle node, const ArkUI_AttributeItem* value);
    static Setter* setters[] = { SetImageSpanSrc, SetVerticalAlign };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "image span node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, value);
}

int32_t SetImageAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* value)
{
    using Setter = int32_t(ArkUI_NodeHandle node, const ArkUI_AttributeItem* value);
    static Setter* setters[] = { SetImageSrc, SetObjectFit, SetInterpolation, SetObjectRepeat, SetColorFilter,
        SetAutoResize, SetAlt };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "image node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, value);
}

int32_t SetTextInputAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* value)
{
    using Setter = int32_t(ArkUI_NodeHandle node, const ArkUI_AttributeItem* value);
    static Setter* setters[] = { SetTextInputPlaceholder, SetTextInputText, SetCaretColor, SetCaretStyle,
        SetShowUnderline, SetMaxLength, SetEnterKeyType, SetPlaceholderColor, SetTextInputPlaceholderFont,
        SetEnableKeybordOnFocus, SetTextInputType, SetSelectedBackgroundColor, SetShowPasswordIcon,
        StopTextInputEditing, };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "textinput node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, value);
}

void ResetTextInputAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Resetter = void(ArkUI_NodeHandle node);
    static Resetter* setters[] = { ResetTextInputPlaceholder, ResetTextInputText, ResetCaretColor, ResetCaretStyle,
        ResetShowUnderline, ResetMaxLength, ResetEnterKeyType, ResetPlaceholderColor, ResetTextInputPlaceholderFont,
        ResetEnableKeybordOnFocus, ResetTextInputType, ResetSelectedBackgroundColor, ResetShowPasswordIcon,
        nullptr,
    };
    if (subTypeId >= sizeof(setters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "textinput node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    if (setters[subTypeId]) {
        setters[subTypeId](node);
    }
}

int32_t SetStackAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    using Setter = int32_t(ArkUI_NodeHandle node, const ArkUI_AttributeItem* value);
    static Setter* setters[] = { SetAlignContent };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "stack node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

void ResetStackAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Resetter = void(ArkUI_NodeHandle node);
    static Resetter* setters[] = { ResetAlignContent };
    if (subTypeId >= sizeof(setters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "stack node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    setters[subTypeId](node);
}

int32_t SetToggleAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* value)
{
    using Setter = int32_t(ArkUI_NodeHandle node, const ArkUI_AttributeItem* value);
    static Setter* setters[] = { SetToggleSelectedColor, SetToggleSwitchPointColor };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "toggle node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, value);
}

const ArkUI_AttributeItem* GetToggleAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Getter = const ArkUI_AttributeItem*(ArkUI_NodeHandle node);
    static Getter* getters[] = { GetToggleSelectedColor, GetToggleSwitchPointColor };
    if (subTypeId >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "slider node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    g_attributeItem.size = RETURN_SIZE_ONE;
    return getters[subTypeId](node);
}

int32_t SetScrollAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    using Setter = int32_t(ArkUI_NodeHandle node, const ArkUI_AttributeItem* value);
    static Setter* setters[] = { SetScrollScrollBar, SetScrollScrollBarWidth, SetScrollScrollBarColor,
        SetScrollScrollable, SetScrollEdgeEffect, SetScrollEnableScrollInteraction, SetScrollFriction,
        SetScrollScrollSnap, SetScrollNestedScroll, SetScrollTo, SetScrollEdge, SetScrollEnablePaging };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "scroll node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

const ArkUI_AttributeItem* GetScrollAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Getter = const ArkUI_AttributeItem*(ArkUI_NodeHandle node);
    static Getter* getters[] = { GetScrollScrollBar, GetScrollScrollBarWidth, GetScrollScrollBarColor,
        GetScrollScrollable, GetScrollEdgeEffect, GetScrollEnableScrollInteraction, GetScrollFriction,
        nullptr, GetScrollNestedScroll, GetScrollOffset, GetScrollEdge, GetScrollEnablePaging };
    if (subTypeId >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "slider node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    g_attributeItem.size = RETURN_SIZE_ONE;
    return getters[subTypeId](node);
}

void ResetScrollAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Resetter = void(ArkUI_NodeHandle node);
    static Resetter* resetters[] = { ResetScrollScrollBar, ResetScrollScrollBarWidth, ResetScrollScrollBarColor,
        ResetScrollScrollable, ResetScrollEdgeEffect, ResetScrollEnableScrollInteraction, ResetScrollFriction,
        ResetScrollScrollSnap, ResetScrollNestedScroll, ResetScrollTo, ResetScrollEdge, ResetScrollEnablePaging };
    if (subTypeId >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "list node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    return resetters[subTypeId](node);
}

void SetListAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const char* value)
{
    static Setter* setters[] = { SetListScrollBar, SetListScrollBarWidth, SetListScrollBarColor, SetListDirection,
        SetListSticky, SetListEdgeEffect, SetListEnableScrollInteraction, SetListFriction, SetListSpace };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "list node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    setters[subTypeId](node, value);
}

const ArkUI_AttributeItem* GetListAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Getter = const ArkUI_AttributeItem*(ArkUI_NodeHandle node);
    static Getter* getters[] = { GetListDirection, GetListSticky, GetListSpace };
    if (subTypeId >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "loadingprogress node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return &g_attributeItem;
    }
    return getters[subTypeId](node);
}

int32_t SetListAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* value)
{
    using Setter = int32_t(ArkUI_NodeHandle node, const ArkUI_AttributeItem* value);
    static Setter* setters[] = { SetListDirection, SetListSticky, SetListSpace };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "list node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, value);
}

void ResetListAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Resetter = void(ArkUI_NodeHandle node);
    static Resetter* resetters[] = { ResetListDirection, ResetListSticky, ResetListSpace };
    if (subTypeId >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "list node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    return resetters[subTypeId](node);
}

int32_t SetTextAreaAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* value)
{
    using Setter = int32_t(ArkUI_NodeHandle node, const ArkUI_AttributeItem* value);
    static Setter* setters[] = { SetTextAreaPlaceholder, SetTextAreaText, SetMaxLength, SetPlaceholderColor,
        SetTextAreaPlaceholderFont, SetCaretColor, StopTextAreaEditing };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "textarea node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, value);
}

void ResetTextAreaAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Resetter = void(ArkUI_NodeHandle node);
    static Resetter* setters[] = { ResetTextAreaPlaceholder, ResetTextAreaText, ResetMaxLength, ResetPlaceholderColor,
        ResetTextAreaPlaceholderFont, ResetCaretColor, nullptr };
    if (subTypeId >= sizeof(setters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "textarea node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    if (setters[subTypeId]) {
        setters[subTypeId](node);
    }
}

int32_t SetXComponentAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* value)
{
    using Setter = int32_t(ArkUI_NodeHandle node, const ArkUI_AttributeItem* value);
    static Setter* setters[] = {
        SetXComponentId,
        SetXComponentType,
        SetXComponentSurfaceSize,
    };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "xcomponent node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, value);
}

void ResetXComponentAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Resetter = void(ArkUI_NodeHandle node);
    static Resetter* setters[] = { nullptr, nullptr, ResetXComponentSurfaceSize };
    if (subTypeId >= sizeof(setters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "textarea node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    if (setters[subTypeId]) {
        setters[subTypeId](node);
    }
}

int32_t SetSwiperAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* value)
{
    using Setter = int32_t(ArkUI_NodeHandle node, const ArkUI_AttributeItem* value);
    static Setter* setters[] = { SetSwiperLoop, SetSwiperAutoPlay, SetSwiperShowIndicator, SetSwiperInterval,
        SetSwiperVertical, SetSwiperDuration, SetSwiperCurve, SetSwiperItemSpace, SetSwiperIndex, SetSwiperDisplayCount,
        SetSwiperDisableSwipe, SetSwiperShowDisplayArrow };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "swiper node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, value);
}

void SetLoadingProgressAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const char* value)
{
    static Setter* setters[] = { SetLoadingProgressColor, SetLoadingProgressEnableLoading };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "loadingprogress node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    setters[subTypeId](node, value);
}

int32_t SetLoadingProgressAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    using Setter = int32_t(ArkUI_NodeHandle node, const ArkUI_AttributeItem* value);
    static Setter* setters[] = { SetLoadingProgressColor, SetLoadingProgressEnableLoading };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "loadingprogress node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

void ResetLoadingProgressAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Resetter = void(ArkUI_NodeHandle node);
    static Resetter* resetters[] = { ResetLoadingProgressColor, ResetLoadingProgressEnableLoading };
    if (subTypeId >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "loadingprogress node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    return resetters[subTypeId](node);
}

const ArkUI_AttributeItem* GetLoadingProgressAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Getter = const ArkUI_AttributeItem*(ArkUI_NodeHandle node);
    static Getter* getters[] = { GetLoadingProgressColor, GetLoadingProgressEnableLoading };
    if (subTypeId >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "loadingprogress node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return &g_attributeItem;
    }
    return getters[subTypeId](node);
}

void SetListItemGroupAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const char* value)
{
    static Setter* setters[] = { SetListItemGroupHeader, SetListItemGroupFooter, SetListItemGroupDivider };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "listitemgroup node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    setters[subTypeId](node, value);
}

int32_t SetListItemGroupAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    using Setter = int32_t(ArkUI_NodeHandle node, const ArkUI_AttributeItem* value);
    static Setter* setters[] = { SetListItemGroupHeader, SetListItemGroupFooter, SetListItemGroupDivider };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "listitemgroup node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

void ResetListItemGroupAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Resetter = void(ArkUI_NodeHandle node);
    static Resetter* resetters[] = { nullptr, nullptr, ResetListItemGroupDivider };
    if (subTypeId >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "list node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    return resetters[subTypeId](node);
}

void SetDatePickerAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const char* value)
{
    static Setter* setters[] = { SetDatePickerLunar, SetDatePickerStart, SetDatePickerEnd, SetDatePickerSelected,
        SetDatePickerDisappearTextStyle, SetDatePickerTextStyle, SetDatePickerSelectedTextStyle };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "datepicker node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    setters[subTypeId](node, value);
}

const ArkUI_AttributeItem* GetDatePickerAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Getter = const ArkUI_AttributeItem*(ArkUI_NodeHandle node);
    static Getter* getters[] = { GetDatePickerLunar, GetDatePickerStart, GetDatePickerEnd, GetDatePickerSelected,
        GetDatePickerDisappearTextStyle, GetDatePickerTextStyle, GetDatePickerSelectedTextStyle };
    if (subTypeId >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "loadingprogress node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return &g_attributeItem;
    }
    return getters[subTypeId](node);
}

int32_t SetDatePickerAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    using Setter = int32_t(ArkUI_NodeHandle node, const ArkUI_AttributeItem* value);
    static Setter* setters[] = { SetDatePickerLunar, SetDatePickerStart, SetDatePickerEnd, SetDatePickerSelected,
        SetDatePickerDisappearTextStyle, SetDatePickerTextStyle, SetDatePickerSelectedTextStyle };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "datepicker node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

void ResetDatePickerAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Resetter = void(ArkUI_NodeHandle node);
    static Resetter* resetters[] = { ResetDatePickerLunar, ResetDatePickerStart, ResetDatePickerEnd,
        ResetDatePickerSelected, ResetDatePickerDisappearTextStyle, ResetDatePickerTextStyle,
        ResetDatePickerSelectedTextStyle };
    if (subTypeId >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "datepicker node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    return resetters[subTypeId](node);
}

const ArkUI_AttributeItem* GetTimePickerAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Getter = const ArkUI_AttributeItem*(ArkUI_NodeHandle node);
    static Getter* getters[] = { GetTimePickerSelected, GetTimePickerUseMilitaryTime, GetTimePickerDisappearTextStyle,
        GetTimePickerTextStyle, GetTimePickerSelectedTextStyle };
    if (subTypeId >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "loadingprogress node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return &g_attributeItem;
    }
    return getters[subTypeId](node);
}

void SetTimePickerAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const char* value)
{
    static Setter* setters[] = { SetTimePickerSelected, SetTimePickerUseMilitaryTime, SetTimePickerDisappearTextStyle,
        SetTimePickerTextStyle, SetTimePickerSelectedTextStyle };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "timepicker node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    setters[subTypeId](node, value);
}

int32_t SetTimePickerAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    using Setter = int32_t(ArkUI_NodeHandle node, const ArkUI_AttributeItem* value);
    static Setter* setters[] = { SetTimePickerSelected, SetTimePickerUseMilitaryTime, SetTimePickerDisappearTextStyle,
        SetTimePickerTextStyle, SetTimePickerSelectedTextStyle };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "timepicker node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

void ResetTimePickerAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Resetter = void(ArkUI_NodeHandle node);
    static Resetter* resetters[] = { ResetTimePickerSelected, ResetTimePickerUseMilitaryTime,
        ResetTimePickerDisappearTextStyle, ResetTimePickerTextStyle, ResetTimePickerSelectedTextStyle };
    if (subTypeId >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "timepicker node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    return resetters[subTypeId](node);
}

void SetTextPickerAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const char* value)
{
    static Setter* setters[] = { SetTextPickerDisappearTextStyle, SetTextPickerTextStyle,
        SetTextPickerSelectedTextStyle, SetTextPickerSelectedIndex };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "textpicker node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    setters[subTypeId](node, value);
}

void ResetToggleAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = { ResetToggleSelectedColor, ResetToggleSwitchPointColor };
    if (subTypeId >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "toggle node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    resetters[subTypeId](node);
}

void ResetSpanAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = { ResetSpanContent };
    if (subTypeId >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "span node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    resetters[subTypeId](node);
}

void ResetImageSpanAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = { ResetImageSpanSrc, ResetVerticalAlign };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "image span node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    resetters[subTypeId](node);
}

void ResetImageAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = { ResetImageSrc, ResetObjectFit, ResetInterpolation, ResetObjectRepeat,
        ResetColorFilter, ResetAutoResize, ResetAlt };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "image node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    resetters[subTypeId](node);
}

void ResetSwiperAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = { ResetSwiperLoop, ResetSwiperAutoPlay, ResetSwiperShowIndicator,
        ResetSwiperInterval, ResetSwiperVertical, ResetSwiperDuration, ResetSwiperCurve, ResetSwiperItemSpace,
        ResetSwiperIndex, ResetSwiperDisplayCount, ResetSwiperDisableSwipe, ResetSwiperShowDisplayArrow };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "swiper node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    resetters[subTypeId](node);
}

const ArkUI_AttributeItem* GetSwiperAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Getter = const ArkUI_AttributeItem*(ArkUI_NodeHandle node);
    static Getter* getters[] = { GetSwiperLoop, GetSwiperAutoPlay, GetSwiperShowIndicator, GetSwiperInterval,
        GetSwiperVertical, GetSwiperDuration, GetSwiperCurve, GetSwiperItemSpace, GetSwiperIndex, GetSwiperDisplayCount,
        GetSwiperDisableSwipe, GetSwiperShowDisplayArrow };
    if (subTypeId >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "swiper node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    g_attributeItem.size = RETURN_SIZE_ONE;
    return getters[subTypeId](node);
}

int32_t SetColumnAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    using Setter = int32_t(ArkUI_NodeHandle node, const ArkUI_AttributeItem* value);
    static Setter* setters[] = { SetAlignItems, SetJustifyContent };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "column node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

void ResetColumnAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Resetter = void(ArkUI_NodeHandle node);
    static Resetter* resetters[] = { ResetAlignItems, ResetJustifyContent };
    if (subTypeId >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "column node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    return resetters[subTypeId](node);
}

const ArkUI_AttributeItem* GetColumnAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Getter = const ArkUI_AttributeItem*(ArkUI_NodeHandle node);
    static Getter* getters[] = { GetAlignItems, GetJustifyContent };
    if (subTypeId >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "column node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    g_attributeItem.size = RETURN_SIZE_ONE;
    return getters[subTypeId](node);
}

int32_t SetRowAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    using Setter = int32_t(ArkUI_NodeHandle node, const ArkUI_AttributeItem* value);
    static Setter* setters[] = { SetAlignItems, SetJustifyContent };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "row node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

void ResetRowAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Resetter = void(ArkUI_NodeHandle node);
    static Resetter* resetters[] = { ResetAlignItems, ResetJustifyContent };
    if (subTypeId >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "row node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    return resetters[subTypeId](node);
}

const ArkUI_AttributeItem* GetRowAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Getter = const ArkUI_AttributeItem*(ArkUI_NodeHandle node);
    static Getter* getters[] = { GetAlignItems, GetJustifyContent };
    if (subTypeId >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "row node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    g_attributeItem.size = RETURN_SIZE_ONE;
    return getters[subTypeId](node);
}

int32_t SetFlexAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    using Setter = int32_t(ArkUI_NodeHandle node, const ArkUI_AttributeItem* value);
    static Setter* setters[] = { SetFlexOptions };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "flex node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

void ResetFlexAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Resetter = void(ArkUI_NodeHandle node);
    static Resetter* resetters[] = { ResetFlexOptions };
    if (subTypeId >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "flex node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    return resetters[subTypeId](node);
}

const ArkUI_AttributeItem* GetFlexAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Getter = const ArkUI_AttributeItem*(ArkUI_NodeHandle node);
    static Getter* getters[] = { GetFlexOptions };
    if (subTypeId >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "flex node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    g_attributeItem.size = RETURN_SIZE_ONE;
    return getters[subTypeId](node);
}

const ArkUI_AttributeItem* GetTextPickerAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Getter = const ArkUI_AttributeItem*(ArkUI_NodeHandle node);
    static Getter* getters[] = { GetTextPickerDisappearTextStyle, GetTextPickerTextStyle,
        GetTextPickerSelectedTextStyle, GetTextPickerSelectedIndex };
    if (subTypeId >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "loadingprogress node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return &g_attributeItem;
    }
    return getters[subTypeId](node);
}

int32_t SetTextPickerAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    using Setter = int32_t(ArkUI_NodeHandle node, const ArkUI_AttributeItem* value);
    static Setter* setters[] = { SetTextPickerDisappearTextStyle, SetTextPickerTextStyle,
        SetTextPickerSelectedTextStyle, SetTextPickerSelectedIndex };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "textpicker node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

void ResetTextPickerAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Resetter = void(ArkUI_NodeHandle node);
    static Resetter* resetters[] = { ResetTextPickerDisappearTextStyle, ResetTextPickerTextStyle,
        ResetTextPickerSelectedTextStyle, ResetTextPickerSelectedIndex };
    if (subTypeId >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "timepicker node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    return resetters[subTypeId](node);
}

int32_t SetButtonAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    using Setter = int32_t(ArkUI_NodeHandle node, const ArkUI_AttributeItem* value);
    static Setter* setters[] = { SetButtonLabel };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "button node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

int32_t SetCheckboxAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    using Setter = int32_t(ArkUI_NodeHandle node, const ArkUI_AttributeItem* value);
    static Setter* setters[] = { SetCheckboxSelect, SetCheckboxSelectedColor, SetCheckboxUnSelectedColor,
        SetCheckboxMark, SetCheckboxShape };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "Checkbox node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

void ResetButtonAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Resetter = void(ArkUI_NodeHandle node);
    static Resetter* resetters[] = { ResetButtonLabel };
    if (subTypeId >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "button node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    return resetters[subTypeId](node);
}

void ResetCheckboxAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Resetter = void(ArkUI_NodeHandle node);
    static Resetter* resetters[] = { ResetCheckboxSelect, ResetCheckboxSelectedColor, ResetCheckboxUnSelectedColor,
        ResetCheckboxMark, ResetCheckboxShape };
    if (subTypeId >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "Checkbox node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    return resetters[subTypeId](node);
}

int32_t SetProgressAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    using Setter = int32_t(ArkUI_NodeHandle node, const ArkUI_AttributeItem* value);
    static Setter* setters[] = { SetProgressValue, SetProgressTotal, SetProgressColor, SetProgressType };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "progress node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

const ArkUI_AttributeItem* GetCheckboxAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Getter = const ArkUI_AttributeItem*(ArkUI_NodeHandle node);
    static Getter* getters[] = { GetCheckboxSelect, GetCheckboxSelectedColor, GetCheckboxUnSelectedColor,
        GetCheckboxMark, GetCheckboxShape };
    if (subTypeId >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "Checkbox node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    g_attributeItem.size = RETURN_SIZE_ONE;
    return getters[subTypeId](node);
}

int32_t SetSliderAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    using Setter = int32_t(ArkUI_NodeHandle node, const ArkUI_AttributeItem* value);
    static Setter* setters[] = {
        SetSliderBlockColor,
        SetSliderTrackColor,
        SetSliderSelectedColor,
        SetSliderShowSteps,
        SetSliderBlockStyle,
        SetSliderValue,
        SetSliderMinValue,
        SetSliderMaxValue,
        SetSliderStep,
        SetSliderDirection,
        SetSliderReverse,
        SetSliderStyle,
    };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "slider node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

void ResetProgressAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Resetter = void(ArkUI_NodeHandle node);
    static Resetter* resetters[] = { ResetProgressValue, ResetProgressTotal, ResetProgressColor, ResetProgressType };
    if (subTypeId >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "progress node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    return resetters[subTypeId](node);
}

const ArkUI_AttributeItem* GetSliderAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Getter = const ArkUI_AttributeItem*(ArkUI_NodeHandle node);
    static Getter* getters[] = {
        GetSliderBlockColor,
        GetSliderTrackColor,
        GetSliderSelectedColor,
        GetSliderShowSteps,
        GetSliderBlockStyle,
        GetSliderValue,
        GetSliderMinValue,
        GetSliderMaxValue,
        GetSliderStep,
        GetSliderDirection,
        GetSliderReverse,
        GetSliderStyle,
    };
    if (subTypeId >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "slider node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    g_attributeItem.size = RETURN_SIZE_ONE;
    return getters[subTypeId](node);
}

void ResetSliderAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Resetter = void(ArkUI_NodeHandle node);
    static Resetter* resetters[] = {
        ResetSliderBlockColor,
        ResetSliderTrackColor,
        ResetSliderSelectedColor,
        ResetSliderShowSteps,
        ResetSliderBlockStyle,
        ResetSliderValue,
        ResetSliderMinValue,
        ResetSliderMaxValue,
        ResetSliderStep,
        ResetSliderDirection,
        ResetSliderReverse,
        ResetSliderStyle,
    };
    if (subTypeId >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "slider node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    return resetters[subTypeId](node);
}

int32_t SetRefreshAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    using Setter = int32_t(ArkUI_NodeHandle node, const ArkUI_AttributeItem* value);
    static Setter* setters[] = { SetRefreshRefreshing };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "slider node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

const ArkUI_AttributeItem* GetRefreshAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Getter = const ArkUI_AttributeItem*(ArkUI_NodeHandle node);
    static Getter* getters[] = { GetRefreshRefreshing };
    if (subTypeId >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "slider node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    g_attributeItem.size = RETURN_SIZE_ONE;
    return getters[subTypeId](node);
}

} // namespace

void SetNodeAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType type, const char* value)
{
    using AttributeSetterClass = void(ArkUI_NodeHandle node, int32_t subTypeId, const char* value);
    static AttributeSetterClass* setterClasses[] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        SetLoadingProgressAttribute, nullptr, nullptr, nullptr, SetListAttribute,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, SetListItemGroupAttribute, SetDatePickerAttribute, SetTimePickerAttribute,
        SetTextPickerAttribute };
    int32_t subTypeClass = type / MAX_NODE_SCOPE_NUM;
    int32_t subTypeId = type % MAX_NODE_SCOPE_NUM;
    if ((subTypeClass > sizeof(setterClasses) / sizeof(AttributeSetterClass*)) ||
        !CheckIfAttributeLegal(node, type)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "node attribute: %{public}d NOT IMPLEMENT", type);
        return;
    }
    setterClasses[subTypeClass](node, subTypeId, value);
}

int32_t SetNodeAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType type, const ArkUI_AttributeItem* item)
{
    using AttributeSetterClass = int32_t(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item);
    static AttributeSetterClass* setterClasses[] = {
        SetCommonAttribute,
        SetTextAttribute,
        SetSpanAttribute,
        SetImageSpanAttribute,
        SetImageAttribute,
        SetToggleAttribute,
        SetLoadingProgressAttribute,
        SetTextInputAttribute,
        SetTextAreaAttribute,
        SetButtonAttribute,
        SetProgressAttribute,
        SetCheckboxAttribute,
        SetXComponentAttribute,
        SetDatePickerAttribute,
        SetTimePickerAttribute,
        SetTextPickerAttribute,
        nullptr,
        SetSliderAttribute,
        SetStackAttribute,
        SetSwiperAttribute,
        SetScrollAttribute,
        SetListAttribute,
        nullptr,
        SetListItemGroupAttribute,
        SetColumnAttribute,
        SetRowAttribute,
        SetFlexAttribute,
        SetRefreshAttribute,
    };
    int32_t subTypeClass = type / MAX_NODE_SCOPE_NUM;
    int32_t subTypeId = type % MAX_NODE_SCOPE_NUM;
    int32_t nodeSubTypeClass =
        subTypeClass < MAX_NODE_SCOPE_NUM ? subTypeClass : (subTypeClass - MAX_NODE_SCOPE_NUM + BASIC_COMPONENT_NUM);
    if ((nodeSubTypeClass > sizeof(setterClasses) / sizeof(AttributeSetterClass*)) ||
        !CheckIfAttributeLegal(node, type)) {
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    auto result = setterClasses[nodeSubTypeClass](node, subTypeId, item);
    if (result == ERROR_CODE_NO_ERROR) {
        GetFullImpl()->getBasicAPI()->markDirty(node->uiNodeHandle, ARKUI_DIRTY_FLAG_ATTRIBUTE_DIFF);
    }
    return result;
}

const ArkUI_AttributeItem* GetNodeAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType type)
{
    ResetAttributeItem();
    using AttributeGetterClass = const ArkUI_AttributeItem*(ArkUI_NodeHandle node, int32_t subTypeId);
    static AttributeGetterClass* getterClasses[] = { GetCommonAttribute, GetTextAttribute, nullptr, nullptr, nullptr,
        GetToggleAttribute, GetLoadingProgressAttribute, nullptr, nullptr, nullptr, nullptr, GetCheckboxAttribute,
        nullptr, nullptr, GetDatePickerAttribute, GetTimePickerAttribute, GetTextPickerAttribute, GetSliderAttribute,
        GetSwiperAttribute, GetScrollAttribute, GetListAttribute, nullptr, nullptr, GetColumnAttribute, GetRowAttribute,
        GetFlexAttribute, GetRefreshAttribute };
    int32_t subTypeClass = type / MAX_NODE_SCOPE_NUM;
    int32_t subTypeId = type % MAX_NODE_SCOPE_NUM;
    int32_t nodeSubTypeClass =
        subTypeClass < MAX_NODE_SCOPE_NUM ? subTypeClass : (subTypeClass - MAX_NODE_SCOPE_NUM + BASIC_COMPONENT_NUM);
    if ((nodeSubTypeClass > sizeof(getterClasses) / sizeof(AttributeGetterClass*)) ||
        !CheckIfAttributeLegal(node, type)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "node attribute: %{public}d NOT IMPLEMENT", type);
        return &g_attributeItem;
    }
    return getterClasses[nodeSubTypeClass](node, subTypeId);
}

int32_t ResetNodeAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType type)
{
    using AttributeResetterClass = void(ArkUI_NodeHandle node, int32_t subTypeId);
    static AttributeResetterClass* resetterClasses[] = {
        ResetCommonAttribute,
        ResetTextAttribute,
        ResetSpanAttribute,
        ResetImageSpanAttribute,
        ResetImageAttribute,
        ResetToggleAttribute,
        ResetLoadingProgressAttribute,
        ResetTextInputAttribute,
        ResetTextAreaAttribute,
        ResetButtonAttribute,
        ResetProgressAttribute,
        ResetCheckboxAttribute,
        ResetXComponentAttribute,
        ResetDatePickerAttribute,
        ResetTimePickerAttribute,
        ResetTextPickerAttribute,
        ResetSliderAttribute,
        ResetStackAttribute,
        ResetSwiperAttribute,
        ResetScrollAttribute,
        ResetListAttribute,
        nullptr,
        ResetListItemGroupAttribute,
        ResetColumnAttribute,
        ResetRowAttribute,
        ResetFlexAttribute,
        nullptr,
    };
    int32_t subTypeClass = type / MAX_NODE_SCOPE_NUM;
    int32_t subTypeId = type % MAX_NODE_SCOPE_NUM;
    int32_t nodeSubTypeClass =
        subTypeClass < MAX_NODE_SCOPE_NUM ? subTypeClass : (subTypeClass - MAX_NODE_SCOPE_NUM + BASIC_COMPONENT_NUM);
    if ((nodeSubTypeClass > sizeof(resetterClasses) / sizeof(AttributeResetterClass*)) ||
        !CheckIfAttributeLegal(node, type)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "node attribute: %{public}d NOT IMPLEMENT", type);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    resetterClasses[nodeSubTypeClass](node, subTypeId);
    return ERROR_CODE_NO_ERROR;
}

} // namespace OHOS::Ace::NodeModel
