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

#include <cstdint>
#include <map>
#include <regex>
#include <string>

#include "native_node.h"
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
constexpr char PARAMS_SEPARATOR_LEVEL2 = ',';
constexpr int DEFAULT_ANGLE = 180;
constexpr ArkUI_Float32 DEFAULT_Z_SCALE = 1.0;
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
constexpr int DEFAULT_UNIT = 1;
const int ALLOW_SIZE_1(1);
const int ALLOW_SIZE_4(4);
const int ALLOW_SIZE_7(7);
const int ALLOW_SIZE_8(8);
const int ALLOW_SIZE_16(16);
const int ALLOW_SIZE_2(2);
const int ALLOW_SIZE_5(5);
const int ALLOW_SIZE_10(10);

constexpr int DEFAULT_SIZE_18 = 18;
constexpr int DEFAULT_SIZE_24 = 24;
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
constexpr int32_t DECORATION_TYPE_INDEX = 0;
constexpr int32_t DECORATION_COLOR_INDEX = 1;
constexpr int32_t DECORATION_STYLE_INDEX = 2;
constexpr int32_t DEFAULT_OBJECT_FIT = 2;

constexpr int32_t XCOMPONENT_TYPE_SURFACE = 0;
constexpr int32_t XCOMPONENT_TYPE_TEXTURE = 2;
const std::vector<std::string> BLUR_STY_ARRAY = { "no_material", "thin", "regular", "thick", "background_thin",
    "background_regular", "background_thick", "background_ultra_thick", "component_ultra_thin", "component_thin",
    "component_regular", "component_thick", "component_ultra_thick" };
const std::vector<std::string> COLOR_MODE_ARRAY = { "system", "light", "dark" };
const std::vector<std::string> ADAPTIVE_COLOR_ARRAY = { "default", "average" };
const std::vector<std::string> TEXT_ALIGN_ARRAY = { "left", "right", "center", "justify", "start", "end" };
const std::vector<std::string> TEXT_COPY_OPTION_ARRAY = { "none", "in-app", "local", "distributed" };
const std::vector<std::string> TEXT_DECORATION_TYPE_ARRAY = { "none", "underline", "overline", "line-through",
    "inherit" };
const std::vector<std::string> TEXT_DECORATION_STYLE_ARRAY = { "solid", "double", "dotted", "dashed", "wavy", "initial",
    "inherit" };
const std::vector<std::string> TEXT_TEXT_SHADOW_ARRAY = { "color", "blur" };
const std::vector<std::string> FONT_STYLE_ARRAY = { "normal", "italic" };
const std::vector<std::string> FONT_OVERFLOW_ARRAY = { "none", "clip", "ellipsis", "marquee" };
const std::vector<std::string> IMAGE_FIT_ARRAY = { "fill", "contain", "cover", "fitwidth", "fitheight", "none",
    "scale_down", "top_left" };
const std::vector<std::string> IMAGE_INTERPOLATION_ARRAY = { "none", "low", "medium", "high" };
const std::vector<std::string> IMAGE_REPEAT_ARRAY = { "no-repeat", "x", "y", "xy" };
const std::vector<std::string> TEXT_CASE_ARRAY = { "normal", "lowercase", "uppercase" };
const std::vector<std::string> IMAGE_SPAN_VERTICAL_ALIGN = { "top", "center", "bottom", "baseline", "none" };
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
const std::vector<std::string> CURVE_ARRAY = { "linear", "ease", "easein", "easeout", "easeinout", "fastoutslowin",
    "linearoutslowin", "fastoutlinearin", "extremedeceleration", "sharp", "rhythm", "smooth", "friction" };
const std::vector<std::string> PLAY_MODE_ARRAY = { "normal", "alternate", "reverse", "alternate_reverse" };
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
const std::vector<std::string> STROKE_LINE_CAP_ARRAY = { "butt", "round", "square" };
const std::vector<std::string> STROKE_LINE_JOIN = { "bevel", "miter", "round" };
typedef std::map<const std::string, ArkUI_Int32> AttrStringToIntMap;
constexpr int32_t TWO = 2;

constexpr int32_t MAX_ATTRIBUTE_ITEM_LEN = 12;
ArkUI_NumberValue g_numberValues[MAX_ATTRIBUTE_ITEM_LEN] = { 0 };
ArkUI_AttributeItem g_attributeItem = { g_numberValues, MAX_ATTRIBUTE_ITEM_LEN, nullptr, nullptr };

constexpr uint32_t DEFAULT_COLOR = 0xFFFFFFFF;
constexpr int32_t DEFAULT_X = 0;
constexpr int32_t DEFAULT_Y = 0;

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

double StringToDouble(const char* string, double defaultValue = 0.0)
{
    char* end = nullptr;
    auto value = strtod(string, &end);
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

// Common Arttributes functions
void SetWidth(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    // 1 for vp. check in DimensionUnit.
    fullImpl->getNodeModifiers()->getCommonModifier()->setWidth(
        node->uiNodeHandle, StringToFloat(value, 0.0f), UNIT_VP, nullptr);
}

int32_t SetWidth(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    // 1 for vp. check in DimensionUnit.
    fullImpl->getNodeModifiers()->getCommonModifier()->setWidth(
        node->uiNodeHandle, item->value[0].f32, UNIT_VP, nullptr);
    return ERROR_CODE_NO_ERROR;
}

void SetHeight(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setHeight(
        node->uiNodeHandle, StringToFloat(value, 0.0f), UNIT_VP, nullptr);
}

int32_t SetHeight(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    // 1 for vp. check in DimensionUnit.
    fullImpl->getNodeModifiers()->getCommonModifier()->setHeight(
        node->uiNodeHandle, item->value[0].f32, UNIT_VP, nullptr);
    return ERROR_CODE_NO_ERROR;
}

void SetBackgroundColor(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setBackgroundColor(
        node->uiNodeHandle, StringToColorInt(value, 0));
}

int32_t SetBackgroundColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setBackgroundColor(node->uiNodeHandle, item->value[0].u32);
    return ERROR_CODE_NO_ERROR;
}

void SetBackgroundImage(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::vector<std::string> bgImageVector;
    StringUtils::StringSplitter(value, ' ', bgImageVector);
    std::string repeat = bgImageVector.size() > 1 ? bgImageVector[1] : "";
    std::string bundle;
    std::string module;
    fullImpl->getNodeModifiers()->getCommonModifier()->setBackgroundImage(node->uiNodeHandle,
        bgImageVector[NUM_0].c_str(), bundle.c_str(), module.c_str(),
        StringToEnumInt(repeat.c_str(), IMAGE_REPEAT_ARRAY, 0));
}

void SetPadding(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::vector<std::string> paddingVal;
    StringUtils::StringSplitter(value, ' ', paddingVal);
    float padding[ALLOW_SIZE_4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    int units[ALLOW_SIZE_4] = { 1, 1, 1, 1 };
    int paddingSize = paddingVal.size();
    for (int i = 0; i < ALLOW_SIZE_4; i++) {
        if (paddingSize == 1) {
            padding[i] = StringToFloat(paddingVal[NUM_0].c_str(), 0.0f);
        } else if (i < paddingSize) {
            padding[i] = StringToFloat(paddingVal[i].c_str(), 0.0f);
        }
    }
    struct ArkUISizeType top = { padding[NUM_0], units[NUM_0] };
    struct ArkUISizeType right = { padding[NUM_1], units[NUM_1] };
    struct ArkUISizeType bottom = { padding[NUM_2], units[NUM_2] };
    struct ArkUISizeType left = { padding[NUM_3], units[NUM_3] };
    fullImpl->getNodeModifiers()->getCommonModifier()->setPadding(node->uiNodeHandle, &top, &right, &bottom, &left);
}

void SetKey(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setKey(node->uiNodeHandle, value);
}

void SetEnabled(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setEnabled(
        node->uiNodeHandle, static_cast<bool>(StringToBoolInt(value, 1)));
}

void SetMargin(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::vector<std::string> params;
    StringUtils::StringSplitter(value, ' ', params);
    if (params.size() != NUM_4) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return;
    }
    ArkUISizeType top;
    top.value = StringUtils::StringToDouble(params[NUM_0].c_str());
    ArkUISizeType right;
    right.value = StringUtils::StringToDouble(params[NUM_1].c_str());
    ArkUISizeType bottom;
    bottom.value = StringUtils::StringToDouble(params[NUM_2].c_str());
    ArkUISizeType left;
    left.value = StringUtils::StringToDouble(params[NUM_3].c_str());
    fullImpl->getNodeModifiers()->getCommonModifier()->setMargin(node->uiNodeHandle, &top, &right, &bottom, &left);
}

void SetTranslate(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    std::vector<std::string> valuesSrc;
    StringUtils::StringSplitter(value, PARAMS_SEPARATOR_LEVEL1, valuesSrc);
    auto size = valuesSrc.size();
    if (size <= 0) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "valuesSrc is empty");
        return;
    }
    ArkUI_Float32 values[size];
    ArkUI_Int32 units[size];
    for (int i = 0; i < size; ++i) {
        values[i] = StringUtils::StringToDouble(valuesSrc[i].c_str());
        units[i] = UNIT_VP;
    }

    fullImpl->getNodeModifiers()->getCommonModifier()->setTranslate(node->uiNodeHandle, values, units, size);
}

void SetScale(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    std::vector<std::string> valuesSrc;
    StringUtils::StringSplitter(value, ',', valuesSrc);
    auto size = valuesSrc.size();
    if (size != NUM_4) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "valuesSrc is invalid");
        return;
    }
    ArkUI_Float32 values[size + NUM_1];
    for (int i = 0; i < size; ++i) {
        values[i] = StringUtils::StringToDouble(valuesSrc[i].c_str());
    }
    values[size] = DEFAULT_Z_SCALE;

    ArkUI_Int32 units[NUM_2] = { UNIT_VP, UNIT_VP };

    fullImpl->getNodeModifiers()->getCommonModifier()->setScale(node->uiNodeHandle, values, size + NUM_1, units, NUM_2);
}

void SetRotate(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::vector<std::string> valuesSrc;
    StringUtils::StringSplitter(value, ',', valuesSrc);
    auto size = valuesSrc.size();
    if (size <= 0) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "valuesSrc is empty");
        return;
    }
    ArkUI_Float32 values[size];
    for (int i = 0; i < size; ++i) {
        values[i] = StringUtils::StringToDouble(valuesSrc[i].c_str());
    }

    ArkUI_Int32 units[NUM_3] = { UNIT_VP, UNIT_VP, UNIT_VP };
    fullImpl->getNodeModifiers()->getCommonModifier()->setRotate(node->uiNodeHandle, values, size, units, NUM_3);
}

void SetBrightness(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }
    ArkUI_Float32 brightness = StringUtils::StringToDouble(value);
    fullImpl->getNodeModifiers()->getCommonModifier()->setBrightness(node->uiNodeHandle, brightness);
}

void SetSaturate(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }
    ArkUI_Float32 saturate = StringUtils::StringToDouble(value);
    fullImpl->getNodeModifiers()->getCommonModifier()->setSaturate(node->uiNodeHandle, saturate);
}

void SetBlur(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }
    ArkUI_Float32 blur = StringUtils::StringToDouble(value);
    fullImpl->getNodeModifiers()->getCommonModifier()->setBlur(node->uiNodeHandle, blur);
}

void SetLinearGradient(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }
    std::vector<std::string> params;
    StringUtils::StringSplitter(value, ' ', params);
    if (params.size() < NUM_1) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return;
    }

    std::vector<std::string> colorsSrc;
    StringUtils::StringSplitter(params[NUM_0], ',', colorsSrc);
    if (colorsSrc.size() % NUM_2) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "colorsSrc is invalid");
        return;
    }
    auto size = colorsSrc.size() / NUM_2 * NUM_3;
    ArkUI_Float32 colors[size];
    for (int i = 0, j = 0; i < colorsSrc.size() && j < size; i += NUM_2, j += NUM_3) {
        colors[j + NUM_0] = StringToColorInt(colorsSrc[i + NUM_0].c_str());
        colors[j + NUM_1] = true;
        colors[j + NUM_2] = StringUtils::StringToDouble(colorsSrc[i + NUM_1].c_str());
    }

    ArkUI_Float32 values[NUM_4] = { false, DEFAULT_ANGLE, NUM_3, false };
    if (params.size() > NUM_1) {
        values[NUM_0] = true;
        values[NUM_1] = StringUtils::StringToDouble(params[NUM_1].c_str());
    }

    if (params.size() > NUM_2) {
        values[NUM_2] = StringToEnumInt(params[NUM_2].c_str(), COMMON_GRADIENT_DIRECTION, NUM_3);
    }
    values[NUM_3] = (params.size() > NUM_3) ? StringToBoolInt(params[NUM_3].c_str()) : false;

    fullImpl->getNodeModifiers()->getCommonModifier()->setLinearGradient(
        node->uiNodeHandle, values, NUM_4, colors, size);
}

void SetAlign(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    auto attrVal = StringToEnumInt(value, COMMON_ALIGNMENT, NUM_0);
    fullImpl->getNodeModifiers()->getCommonModifier()->setAlign(node->uiNodeHandle, attrVal);
}

int32_t SetOpacity(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
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
        for (int i = 0; i < ALLOW_SIZE_4; ++i) {
            widthVals[i] = item->value[0].f32;
        }
    } else if (item->size == 4) {
        for (int i = 0; i < ALLOW_SIZE_4; ++i) {
            widthVals[i] = item->value[i].f32;
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

int32_t SetBorderRadius(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    float radiusVals[ALLOW_SIZE_4] = { 1, 1, 1, 1 };
    int radiusUnits[ALLOW_SIZE_4] = { DEFAULT_UNIT, DEFAULT_UNIT, DEFAULT_UNIT, DEFAULT_UNIT };

    if (item->size == 1) {
        for (int i = 0; i < ALLOW_SIZE_4; ++i) {
            radiusVals[i] = item->value[0].f32;
        }
    } else if (item->size == 4) {
        for (int i = 0; i < ALLOW_SIZE_4; ++i) {
            radiusVals[i] = item->value[i].f32;
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
    } else if (item->size == 4) {
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

int32_t SetBorderStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    int styles[ALLOW_SIZE_4] = { 0, 0, 0, 0 };
    if (item->size == 1) {
        for (int i = 0; i < ALLOW_SIZE_4; ++i) {
            styles[i] = item->value[0].i32;
        }
        fullImpl->getNodeModifiers()->getCommonModifier()->setBorderStyle(node->uiNodeHandle, styles, ALLOW_SIZE_4);
    } else if (item->size == 4) {
        for (int i = 0; i < ALLOW_SIZE_4; ++i) {
            styles[i] = item->value[i].i32;
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

int32_t SetZIndex(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
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

int32_t SetVisibility(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
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

int32_t SetClip(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
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

int32_t SetClipShape(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::string clipStr(item->string);
    StringUtils::TrimStr(clipStr);
    if (std::regex_search(clipStr, BRACKETS)) {
        std::size_t pos1 = clipStr.find_first_of('(');
        std::size_t pos2 = clipStr.find_first_of(')');
        std::string shape = clipStr.substr(0, pos1);
        std::string content = clipStr.substr(pos1 + 1, pos2 - pos1 - 1);
        std::vector<std::string> attributeProps;
        StringUtils::StringSplitter(content.c_str(), ',', attributeProps);
        if (shape == "path") {
            ArkUI_Float32 pathAttributes[NUM_2];
            for (int i = 0; i < NUM_2; ++i) {
                pathAttributes[i] = StringToFloat(attributeProps[i].c_str(), 0.0f);
            }
            std::string commands(attributeProps[NUM_2]);
            fullImpl->getNodeModifiers()->getCommonModifier()->setClipPath(
                node->uiNodeHandle, shape.c_str(), pathAttributes, commands.c_str());
        } else {
            ArkUI_Float32 attributes[attributeProps.size()];
            for (int i = 0; i < attributeProps.size(); ++i) {
                attributes[i] = StringToFloat(attributeProps[i].c_str(), 0.0f);
            }
            fullImpl->getNodeModifiers()->getCommonModifier()->setClipShape(
                node->uiNodeHandle, shape.c_str(), attributes, attributeProps.size());
        }
    } else {
        int isClip = StringToBoolInt(clipStr.c_str(), 0);
        fullImpl->getNodeModifiers()->getCommonModifier()->setClip(node->uiNodeHandle, isClip);
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetClipShape(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetClip(node->uiNodeHandle);
}

int32_t SetTransform(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 && item->size != ALLOW_SIZE_16) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    float transforms[ALLOW_SIZE_16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
    for (int i = 0; i < ALLOW_SIZE_16; ++i) {
        transforms[i] = item->value[i].i32;
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setTransform(node->uiNodeHandle, transforms, ALLOW_SIZE_16);
    return ERROR_CODE_NO_ERROR;
}

void ResetTransform(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetTransform(node->uiNodeHandle);
}

int32_t SetHitTestBehavior(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
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

int32_t SetPosition(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 && item->size != 2) {
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

int32_t SetShadow(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
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

int32_t SetCustomShadow(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::string shadowStr(item->string);
    ArkUI_Float32 shadows[ALLOW_SIZE_7] = { 0, 2, 0, 0, 0, 0, 0 };
    int length;
    std::vector<std::string> ShadowProps;
    StringUtils::StringSplitter(shadowStr.c_str(), ' ', ShadowProps);
    length = ShadowProps.size();
    if (length > NUM_0) {
        shadows[NUM_0] = StringToFloat(ShadowProps[NUM_0].c_str(), 0.0f); // radius
    }
    if (length > NUM_2) {
        shadows[NUM_2] = StringToFloat(ShadowProps[NUM_1].c_str(), 0.0f); // OffsetX
    }
    if (length > NUM_3) {
        shadows[NUM_3] = StringToFloat(ShadowProps[NUM_2].c_str(), 0.0f); // OffsetY
    }
    if (length > NUM_4) {
        shadows[NUM_4] = StringToEnumInt(ShadowProps[NUM_3].c_str(), COMMON_SHADOW_TYPE, 0);
    }
    if (length > NUM_5) {
        std::string coloringStrategyValues = "invert average primary";
        if (coloringStrategyValues.find(ShadowProps[NUM_4]) != std::string::npos) {
            shadows[NUM_1] = COLOR_STRATEGY_STYLE;
            shadows[NUM_5] = StringToEnumInt(ShadowProps[NUM_4].c_str(), COMMON_SHADOW_COLORING_STRATEGY, 0);
        } else {
            shadows[NUM_1] = COLOR_STYLE;
            shadows[NUM_5] = StringToColorInt(ShadowProps[NUM_4].c_str(), 0);
        }
    }
    if (length > NUM_6) {
        shadows[NUM_6] = StringToBoolInt(ShadowProps[NUM_5].c_str(), 0);
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setBackShadow(node->uiNodeHandle, shadows, ALLOW_SIZE_7);
    return ERROR_CODE_NO_ERROR;
}

void ResetCustomShadow(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetBackShadow(node->uiNodeHandle);
}

void SetFocusable(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setFocusable(
        node->uiNodeHandle, static_cast<bool>(StringToBoolInt(value, 1)));
}

void SetAccessibilityGroup(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setAccessibilityGroup(
        node->uiNodeHandle, static_cast<bool>(StringToBoolInt(value, 0)));
}

void SetAccessibilityText(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setAccessibilityText(node->uiNodeHandle, value);
}

void SetAccessibilityLevel(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setAccessibilityLevel(node->uiNodeHandle, value);
}

void SetAccessibilityDescription(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setAccessibilityDescription(node->uiNodeHandle, value);
}

void SetDefaultFocus(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setDefaultFocus(
        node->uiNodeHandle, static_cast<bool>(StringToBoolInt(value, 0)));
}

// "{1 2 3 4},{1 2 3 4}"
void SetResponseRegion(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    std::vector<std::string> regionArray;
    StringUtils::StringSplitter(value, ',', regionArray);
    std::vector<ArkUI_Float32> valuesArray;
    std::vector<int> unitsArray;
    if (regionArray.size() == 1) {
        std::vector<std::string> regionVal;
        // 取第一个值进行分解
        StringUtils::StringSplitter(regionArray[0], ' ', regionVal);
        if (regionVal.size() < ALLOW_SIZE_4) {
            return;
        }
        for (int i = 0; i < regionVal.size(); i++) {
            valuesArray.push_back(StringToDouble(regionVal[i].c_str(), 0.0f));
            // unit 1 3
            unitsArray.push_back(i > NUM_1 ? NUM_3 : NUM_1);
        }
    } else if (regionArray.size() > 1) {
        for (const std::string& region : regionArray) {
            // 判断第一个字符是否符合要求
            if (!region.empty() && region.size() > ALLOW_SIZE_2 && region[0] == '{' && region.back() == '}') {
                std::string regionString = region.substr(1, region.length() - ALLOW_SIZE_2);
                std::vector<std::string> regionVal;
                StringUtils::StringSplitter(regionString, ' ', regionVal);
                if (regionVal.size() < ALLOW_SIZE_4) {
                    return;
                }
                for (int i = 0; i < ALLOW_SIZE_4; i++) {
                    valuesArray.push_back(StringToDouble(regionVal[i].c_str(), 0.0f));
                    // unit 1 3
                    unitsArray.push_back(i > NUM_1 ? NUM_3 : NUM_1);
                }
            }
        }
    }

    fullImpl->getNodeModifiers()->getCommonModifier()->setResponseRegion(
        node->uiNodeHandle, valuesArray.data(), unitsArray.data(), valuesArray.size());
}

void SetOverlay(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    std::vector<std::string> valueVal;
    StringUtils::StringSplitter(value, ' ', valueVal);

    if (valueVal.size() < ALLOW_SIZE_4) {
        return;
    }

    ArkUI_Float32 values[ALLOW_SIZE_10] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1, 1 };
    std::vector<std::string> alignment = { "top-start", "top", "top-end", "start", "center", "end", "bottom-start",
        "bottom", "bottom-end" };
    // 调用函数参数要求
    values[0] = 1;
    values[1] = StringToEnumInt(valueVal[1].c_str(), alignment, 0);
    // 组装对应的参数
    if (StringToInt(valueVal[2].c_str(), 0) > 0) {
        values[2] = 1;
        values[3] = StringToDouble(valueVal[2].c_str(), 0.0);
        values[4] = 1;
    }
    // 组装对应的参数
    if (StringToInt(valueVal[3].c_str(), 0) > 0) {
        values[5] = 1;
        values[6] = StringToDouble(valueVal[3].c_str(), 0.0);
        values[7] = 1;
    }

    fullImpl->getNodeModifiers()->getCommonModifier()->setOverlay(
        node->uiNodeHandle, valueVal[0].c_str(), values, ALLOW_SIZE_10);
}

void SetBackgroundImagePosition(ArkUI_NodeHandle node, const char* value)
{
    std::vector<std::string> positions;
    StringUtils::StringSplitter(value, ' ', positions);
    if (positions.size() != NUM_2) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "positions are invalid");
        return;
    }
}

int32_t SetSweepGradient(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();

    std::vector<std::string> params;
    StringUtils::StringSplitter(item->string, ';', params);
    if (params.size() < NUM_1) {
        return ERROR_CODE_PARAM_INVALID;
    }

    std::vector<std::string> colorsSrc;
    StringUtils::StringSplitter(params[NUM_0], ',', colorsSrc);
    if (colorsSrc.size() % NUM_2) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto size = colorsSrc.size() / NUM_2 * NUM_3;
    ArkUI_Float32 colors[size];
    for (int i = 0, j = 0; i < colorsSrc.size() && j < size; i += NUM_2, j += NUM_3) {
        colors[j + NUM_0] = StringToColorInt(colorsSrc[i + NUM_0].c_str());
        colors[j + NUM_1] = true;
        colors[j + NUM_2] = StringUtils::StringToDouble(colorsSrc[i + NUM_1].c_str());
    }

    ArkUI_Float32 values[NUM_13] = { false, DEFAULT_X, UNIT_VP, false, DEFAULT_Y, UNIT_VP, false, NUM_0, false, NUM_0,
        false, NUM_0, false };
    if (params.size() > NUM_1) {
        values[NUM_0] = true;
        values[NUM_1] = StringUtils::StringToDouble(params[NUM_1].c_str());
    }

    if (params.size() > NUM_2) {
        values[NUM_3] = true;
        values[NUM_4] = StringUtils::StringToDouble(params[NUM_2].c_str());
    }

    if (params.size() > NUM_3) {
        values[NUM_6] = true;
        values[NUM_7] = StringUtils::StringToDouble(params[NUM_3].c_str());
    }

    if (params.size() > NUM_4) {
        values[NUM_8] = true;
        values[NUM_9] = StringUtils::StringToDouble(params[NUM_4].c_str());
    }

    if (params.size() > NUM_5) {
        values[NUM_10] = true;
        values[NUM_11] = StringUtils::StringToDouble(params[NUM_5].c_str());
    }

    values[NUM_12] = (params.size() > NUM_6) ? StringToBoolInt(params[NUM_6].c_str()) : false;

    fullImpl->getNodeModifiers()->getCommonModifier()->setSweepGradient(
        node->uiNodeHandle, values, NUM_13, colors, size);
    return ERROR_CODE_NO_ERROR;
}

void ResetSweepGradient(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetSweepGradient(node->uiNodeHandle);
}

int32_t SetRadialGradient(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    std::vector<std::string> params;
    StringUtils::StringSplitter(item->string, ' ', params);
    if (params.size() < NUM_1) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return ERROR_CODE_PARAM_INVALID;
        ;
    }

    std::vector<std::string> colorsSrc;
    StringUtils::StringSplitter(params[NUM_0], ',', colorsSrc);
    if (colorsSrc.size() % NUM_2) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "colorsSrc is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }
    auto size = colorsSrc.size() / NUM_2 * NUM_3;
    ArkUI_Float32 colors[size];
    for (int i = 0, j = 0; i < colorsSrc.size() && j < size; i += NUM_2, j += NUM_3) {
        colors[j + NUM_0] = StringToColorInt(colorsSrc[i + NUM_0].c_str());
        colors[j + NUM_1] = true;
        colors[j + NUM_2] = StringUtils::StringToDouble(colorsSrc[i + NUM_1].c_str());
    }

    ArkUI_Float32 values[NUM_10] = { false, DEFAULT_X, UNIT_VP, false, DEFAULT_Y, UNIT_VP, false, DEFAULT_Y, UNIT_VP,
        false };
    if (params.size() > NUM_1) {
        values[NUM_0] = true;
        values[NUM_1] = StringUtils::StringToDouble(params[NUM_1].c_str());
    }

    if (params.size() > NUM_2) {
        values[NUM_3] = true;
        values[NUM_4] = StringUtils::StringToDouble(params[NUM_2].c_str());
    }

    if (params.size() > NUM_3) {
        values[NUM_6] = true;
        values[NUM_7] = StringUtils::StringToDouble(params[NUM_3].c_str());
    }

    values[NUM_9] = (params.size() > NUM_4) ? StringToBoolInt(params[NUM_4].c_str()) : false;

    fullImpl->getNodeModifiers()->getCommonModifier()->setRadialGradient(
        node->uiNodeHandle, values, NUM_10, colors, size);
    return ERROR_CODE_NO_ERROR;
}

void ResetRadialGradient(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetRadialGradient(node->uiNodeHandle);
}

int32_t SetMask(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    std::string maskStr(item->string);
    StringUtils::TrimStr(maskStr);
    if (std::regex_search(maskStr, BRACKETS)) {
        std::size_t pos1 = maskStr.find_first_of('(');
        std::size_t pos2 = maskStr.find_first_of(')');
        std::string shape = maskStr.substr(0, pos1);
        std::string content = maskStr.substr(pos1 + 1, pos2 - pos1 - 1);
        std::vector<std::string> attributeProps;
        StringUtils::StringSplitter(content.c_str(), ',', attributeProps);
        if (shape == "path") {
            double pathAttributes[NUM_2];
            for (int i = 0; i < NUM_2; ++i) {
                pathAttributes[i] = StringToFloat(attributeProps[i].c_str(), 0.0f);
            }
            std::string commands(attributeProps[NUM_2]);
            fullImpl->getNodeModifiers()->getCommonModifier()->setMaskPath(
                node->uiNodeHandle, shape.c_str(), pathAttributes, commands.c_str());
        } else if (shape == "progressMask") {
            double progressAttributes[NUM_3];
            for (int i = 0; i < NUM_2; ++i) {
                progressAttributes[i] = StringToInt(attributeProps[i].c_str(), 0);
            }
            progressAttributes[NUM_2] = StringToColorInt(attributeProps[NUM_2].c_str(), 0);
            fullImpl->getNodeModifiers()->getCommonModifier()->setMaskShape(
                node->uiNodeHandle, shape.c_str(), progressAttributes, NUM_3);
        } else {
            double attributes[attributeProps.size()];
            for (int i = 0; i < attributeProps.size(); ++i) {
                attributes[i] = StringToFloat(attributeProps[i].c_str(), 0.0f);
            }
            fullImpl->getNodeModifiers()->getCommonModifier()->setMaskShape(
                node->uiNodeHandle, shape.c_str(), attributes, attributeProps.size());
        }
        return ERROR_CODE_NO_ERROR;
    } else {
        return ERROR_CODE_PARAM_INVALID;
    }
}

int32_t SetBlendMode(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setBlendMode(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetBlendMode(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetBlendMode(node->uiNodeHandle);
}

int32_t SetDirection(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
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

int32_t SetAlignSelf(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
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

int32_t SetFlexGrow(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
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

int32_t SetFlexShrink(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
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

int32_t SetFlexBasis(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
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

int32_t SetConstraintSize(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || item->size != 4) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    ArkUI_Float64 constraintSize[ALLOW_SIZE_4] = { 0.0f, DBL_MAX, 0.0f, DBL_MAX };
    ArkUI_Int32 units[ALLOW_SIZE_4] = { 1, 1, 1, 1 };

    if (item->size == 1) {
        constraintSize[0] = item->value[0].f32;
        constraintSize[1] = item->value[0].f32;
        constraintSize[2] = item->value[0].f32;
        constraintSize[3] = item->value[0].f32;
    } else if (item->size == 4) {
        for (int i = 0; i < ALLOW_SIZE_4; ++i) {
            constraintSize[i] = item->value[i].f32;
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

int32_t SetGrayscale(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
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

int32_t SetInvert(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
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

int32_t SetSepia(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
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

int32_t SetContrast(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
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

int32_t SetForegroundColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    bool isColor = true;
    if (item->value[0].i32 == ArkUI_ColoringStrategy::ARKUI_COLOR_STRATEGY_INVERT ||
        item->value[0].i32 == ArkUI_ColoringStrategy::ARKUI_COLOR_STRATEGY_AVERAGE ||
        item->value[0].i32 == ArkUI_ColoringStrategy::ARKUI_COLOR_STRATEGY_PRIMARY) {
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

void SetOffset(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    std::vector<std::string> offsetVector;
    StringUtils::StringSplitter(std::string(value), ' ', offsetVector);
    CalcDimension xDimension(0);
    if (NUM_0 < offsetVector.size()) {
        StringUtils::StringToCalcDimensionNG(offsetVector[NUM_0], xDimension, false, DimensionUnit::VP);
    }
    CalcDimension yDimension(0);
    if (NUM_1 < offsetVector.size()) {
        StringUtils::StringToCalcDimensionNG(offsetVector[NUM_1], yDimension, false, DimensionUnit::VP);
    }
}

void SetMarkAnchor(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    std::vector<std::string> anchorVector;
    StringUtils::StringSplitter(std::string(value), ' ', anchorVector);
    CalcDimension xDimension(0);
    if (NUM_0 < anchorVector.size()) {
        StringUtils::StringToCalcDimensionNG(anchorVector[NUM_0], xDimension, false, DimensionUnit::VP);
    }
    CalcDimension yDimension(0);
    if (NUM_1 < anchorVector.size()) {
        StringUtils::StringToCalcDimensionNG(anchorVector[NUM_1], yDimension, false, DimensionUnit::VP);
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setMarkAnchor(node->uiNodeHandle, xDimension.Value(),
        static_cast<int32_t>(xDimension.Unit()), yDimension.Value(), static_cast<int32_t>(yDimension.Unit()));
}

void SetAlignRules(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    std::vector<std::string> alignRulesVector;
    StringUtils::StringSplitter(std::string(value), ' ', alignRulesVector);
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
}

void SetTextIndent(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
}

// TextInput Arttributes functions
void SetFontColor(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_TEXT_INPUT:
            fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputFontColor(
                node->uiNodeHandle, StringToColorInt(value, 0));
            break;
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->setFontColor(
                node->uiNodeHandle, StringToColorInt(value, 0));
            break;
        case ARKUI_NODE_SPAN:
            fullImpl->getNodeModifiers()->getSpanModifier()->setSpanFontColor(
                node->uiNodeHandle, StringToColorInt(value, 0));
            break;
        default:
            break;
    }
}

void SetFontWeight(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_TEXT_INPUT:
            fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputFontWeight(node->uiNodeHandle, value);
            break;
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->setFontWeight(node->uiNodeHandle, value);
            break;
        case ARKUI_NODE_SPAN:
            fullImpl->getNodeModifiers()->getSpanModifier()->setSpanFontWeight(node->uiNodeHandle, value);
            break;
        default:
            break;
    }
}

void SetFontSize(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT_INPUT) {
        struct ArkUILengthType fontSize = { nullptr, StringToFloat(value, 0.0f), UNIT_FP };
        fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputFontSize(node->uiNodeHandle, &fontSize);
    } else if (node->type == ARKUI_NODE_TEXT) {
        CalcDimension textFontSize;
        if (StringUtils::StringToCalcDimensionNG(std::string(value), textFontSize, false, DimensionUnit::VP)) {
            fullImpl->getNodeModifiers()->getTextModifier()->setFontSize(
                node->uiNodeHandle, textFontSize.Value(), static_cast<int32_t>(textFontSize.Unit()));
        }
    } else if (node->type == ARKUI_NODE_SPAN) {
        CalcDimension spanFontSize;
        if (StringUtils::StringToCalcDimensionNG(std::string(value), spanFontSize, false, DimensionUnit::VP)) {
            fullImpl->getNodeModifiers()->getTextModifier()->setFontSize(
                node->uiNodeHandle, spanFontSize.Value(), static_cast<int32_t>(spanFontSize.Unit()));
        }
    }
}

void SetFontStyle(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    int32_t fontStyle = StringToEnumInt(value, FONT_STYLE_ARRAY, 0);
    switch (node->type) {
        case ARKUI_NODE_TEXT_INPUT:
            fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputFontStyle(node->uiNodeHandle, fontStyle);
            break;
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->setFontStyle(node->uiNodeHandle, fontStyle);
            break;
        case ARKUI_NODE_SPAN:
            fullImpl->getNodeModifiers()->getSpanModifier()->setSpanFontStyle(node->uiNodeHandle, fontStyle);
            break;
        default:
            break;
    }
}

void SetTextAlign(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_TEXT_INPUT:
            fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputTextAlign(
                node->uiNodeHandle, StringToEnumInt(value, TEXT_ALIGN_ARRAY, 0));
            break;
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->setTextAlign(
                node->uiNodeHandle, StringToEnumInt(value, TEXT_ALIGN_ARRAY, 0));
            break;
        default:
            break;
    }
}

void SetTextInputPlaceholder(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputPlaceholderString(node->uiNodeHandle, value);
}

void SetTextInputText(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputTextString(node->uiNodeHandle, value);
}

void SetCaretColor(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT_INPUT) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputCaretColor(
            node->uiNodeHandle, StringToColorInt(value, 0));
    } else if (node->type == ARKUI_NODE_TEXT_AREA) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaCaretColor(
            node->uiNodeHandle, StringToColorInt(value, 0));
    }
}

void SetCaretStyle(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    struct ArkUILengthType width = { nullptr, StringToFloat(value, 0.0f), 1 };
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputCaretStyle(node->uiNodeHandle, &width);
}

void SetShowUnderline(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputShowUnderline(
        node->uiNodeHandle, StringToBoolInt(value, 0));
}

void SetMaxLength(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT_INPUT) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputMaxLength(
            node->uiNodeHandle, StringToInt(value, 0));
    } else if (node->type == ARKUI_NODE_TEXT_AREA) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaMaxLength(
            node->uiNodeHandle, StringToInt(value, 0));
    }
}

void SetEnterKeyType(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputEnterKeyType(
        node->uiNodeHandle, StringToEnumInt(value, TEXT_INPUT_ENTER_KEY_TYPE, NUM_6));
}

void SetPlaceholderColor(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT_INPUT) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputPlaceholderColor(
            node->uiNodeHandle, StringToColorInt(value, 0));
    } else if (node->type == ARKUI_NODE_TEXT_AREA) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaPlaceholderColor(
            node->uiNodeHandle, StringToColorInt(value, 0));
    }
}

void SetTextInputPlaceholderFont(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::vector<std::string> font;
    StringUtils::StringSplitter(value, ' ', font);
    for (int i = font.size(); i < ALLOW_SIZE_4; i++) {
        font.emplace_back("");
    }
    struct ArkUILengthType size = { nullptr, StringToFloat(font[NUM_0].c_str(), 0.0f), UNIT_FP };
    std::string familyStr = font[NUM_3];
    int fontFamilyLength = familyStr.length();
    struct ArkUIPlaceholderFontType palceHolderFont = { &size, font[NUM_1].c_str(), nullptr, 0,
        StringToEnumInt(font[NUM_2].c_str(), FONT_STYLE_ARRAY, 0) };
    if (fontFamilyLength) {
        std::vector<std::string> fontFamilies = Framework::ConvertStrToFontFamilies(familyStr);
        auto families = std::make_unique<char*[]>(fontFamilies.size());
        for (uint32_t i = 0; i < fontFamilies.size(); i++) {
            families[i] = const_cast<char*>(fontFamilies.at(i).c_str());
        }
        palceHolderFont.fontFamilies = const_cast<const char**>(families.get());
        palceHolderFont.length = fontFamilies.size();
    }

    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputPlaceholderFont(
        node->uiNodeHandle, &palceHolderFont);
}

void SetEnableKeybordOnFocus(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputEnableKeyboardOnFocus(
        node->uiNodeHandle, StringToBoolInt(value, 1));
}

void SetTextInputType(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputType(
        node->uiNodeHandle, StringToEnumInt(value, TEXT_INPUT_TYPE, 0));
}

void SetSelectedBackgroundColor(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputSelectedBackgroundColor(
        node->uiNodeHandle, StringToColorInt(value, 0));
}

void SetShowPasswordIcon(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputShowPasswordIcon(
        node->uiNodeHandle, StringToBoolInt(value, 1));
}

// Stack Arttribute functions
void SetAlignContent(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    auto attrVal = StringToEnumInt(value, COMMON_ALIGNMENT, NUM_0);
    fullImpl->getNodeModifiers()->getStackModifier()->setAlignContent(node->uiNodeHandle, attrVal);
}

// Scroll Arttribute functions
void SetScrollFriction(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollFriction(node->uiNodeHandle, StringToFloat(value));
}

void SetScrollScrollSnap(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::vector<std::string> params;
    StringUtils::StringSplitter(value, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() != NUM_4) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return;
    }
    std::vector<std::string> paginationsSrc;
    StringUtils::StringSplitter(value, PARAMS_SEPARATOR_LEVEL2, paginationsSrc);
    auto size = paginationsSrc.size();
    if (paginationsSrc.empty()) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "paginationsSrc is empty");
        return;
    }
    ArkUI_Float32 paginations[size];
    ArkUI_Int32 paginationParams[NUM_4 + size];
    for (int i = 0; i < size; ++i) {
        paginations[i] = StringUtils::StringToDouble(paginationsSrc[i].c_str());
        paginationParams[i] = UNIT_VP;
    }

    paginationParams[size + NUM_0] = StringToBoolInt(params[NUM_0].c_str());
    paginationParams[size + NUM_1] = StringToBoolInt(params[NUM_2].c_str());
    paginationParams[size + NUM_2] = StringToBoolInt(params[NUM_3].c_str());
    paginationParams[size + NUM_3] = (size > 1) ? true : false;

    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollScrollSnap(
        node->uiNodeHandle, paginations, size, paginationParams, NUM_4 + size);
}

void SetScrollScrollBar(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    auto attrVal = StringToEnumInt(value, SCROLL_DISPLAY_MODE, NUM_1);
    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollScrollBar(node->uiNodeHandle, attrVal);
}

void SetScrollScrollBarWidth(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }
    auto attrVal = StringUtils::StringToDouble(value);
    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollScrollBarWidth(node->uiNodeHandle, attrVal, UNIT_VP);
}

void SetScrollScrollBarColor(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    auto color = StringToColorInt(value, 0);
    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollScrollBarColor(node->uiNodeHandle, color);
}

void SetScrollScrollable(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    auto attrVal = StringToEnumInt(value, SCROLL_AXIS, NUM_0);
    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollScrollable(node->uiNodeHandle, attrVal);
}

void SetScrollEdgeEffect(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }
    bool alwaysEnabled = true;
    std::vector<std::string> params;
    StringUtils::StringSplitter(value, ' ', params);
    auto size = params.size();
    if (size <= 0) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return;
    }

    auto attrVal = StringToEnumInt(value, SCROLL_EDGE_EFFECT, NUM_2);
    alwaysEnabled = (size > NUM_1) ? StringToBoolInt(params[NUM_1].c_str()) : true;
    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollEdgeEffect(node->uiNodeHandle, attrVal, alwaysEnabled);
}

void SetScrollEnableScrollInteraction(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }
    bool enableScrollInteraction = StringToBoolInt(value);
    fullImpl->getNodeModifiers()->getScrollModifier()->setEnableScrollInteraction(
        node->uiNodeHandle, enableScrollInteraction);
}

void SetScrollNestedScroll(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::vector<std::string> valueVal;
    StringUtils::StringSplitter(value, ' ', valueVal);

    if (valueVal.size() < ALLOW_SIZE_2) {
        return;
    }
    std::vector<std::string> nestedScrollOptions = { "self-only", "self-first", "parent-first", "parallel" };
    // 组装对应的参数
    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollNestedScroll(node->uiNodeHandle,
        StringToEnumInt(valueVal[0].c_str(), nestedScrollOptions, 0),
        StringToEnumInt(valueVal[1].c_str(), nestedScrollOptions, 0));
}

void SetScrollTo(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::vector<std::string> valueVal;
    StringUtils::StringSplitter(value, ' ', valueVal);
    if (valueVal.size() < ALLOW_SIZE_5) {
        return;
    }

    std::vector<std::string> curve = { "linear", "ease", "easeIn", "easeOut", "ease-in-out", "fast-out-slow-in",
        "linear-out-slow-in", "fast-out-linear-in", "extreme-deceleration", "sharp", "rhythm", "smooth", "friction" };
    // 组装对应的参数
    ArkUI_Float32 values[ALLOW_SIZE_7] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    values[0] = StringToDouble(valueVal[0].c_str(), 0.0);
    values[1] = 1;
    values[2] = StringToDouble(valueVal[1].c_str(), 0.0);
    values[3] = 1;
    values[4] = StringToDouble(valueVal[2].c_str(), 0.0);
    values[5] = StringToEnumInt(valueVal[3].c_str(), curve, 0);
    values[6] = StringToBoolInt(valueVal[4].c_str(), 0.0);
    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollTo(node->uiNodeHandle, values);
}

void SetScrollEdge(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::vector<std::string> edge = { "top", "center", "bottom", "baseline", "start", "middle", "end" };
    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollEdge(
        node->uiNodeHandle, StringToEnumInt(value, edge, 0));
}

void SetScrollEnablePaging(ArkUI_NodeHandle node, const char* value)
{
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }
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

void SetListListDirection(ArkUI_NodeHandle node, const char* value)
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

void SetListListSticky(ArkUI_NodeHandle node, const char* value)
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

void SetTextAreaPlaceholderFont(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::vector<std::string> font;
    StringUtils::StringSplitter(value, ' ', font);
    for (int i = font.size(); i < ALLOW_SIZE_4; i++) {
        font.emplace_back("");
    }
    struct ArkUIResourceLength size = { StringToFloat(font[NUM_0].c_str(), 0.0f), UNIT_FP };
    std::string weight = font[NUM_1];
    int fontStyle = StringToEnumInt(font[NUM_2].c_str(), FONT_STYLE_ARRAY, 0);
    std::string family = font[NUM_3];
    fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaPlaceholderFont(
        node->uiNodeHandle, &size, weight.c_str(), family.c_str(), fontStyle);
}

void SetTextAreaPlaceholder(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaPlaceholderString(node->uiNodeHandle, value);
}

void SetTextAreaText(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaTextString(node->uiNodeHandle, value);
}

void StopTextAreaEditing(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (!StringToBoolInt(value, 0)) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->stopTextAreaTextEditing(node->uiNodeHandle);
    }
}

void SetXComponentId(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getXComponentModifier()->setXComponentId(node->uiNodeHandle, value);
}

void SetXComponentType(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::string input(value);
    ArkUI_Uint32 type = input == "texture" ? XCOMPONENT_TYPE_TEXTURE : XCOMPONENT_TYPE_SURFACE;
    fullImpl->getNodeModifiers()->getXComponentModifier()->setXComponentType(node->uiNodeHandle, type);
}

void SetXComponentSurfaceSize(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::vector<std::string> size;
    StringUtils::StringSplitter(value, ' ', size);
    std::string width = size[NUM_0];
    std::string height = size[NUM_1];
    fullImpl->getNodeModifiers()->getXComponentModifier()->setXComponentSurfaceSize(
        node->uiNodeHandle, StringToInt(width.c_str(), 0), StringToInt(height.c_str(), 0));
}

// Text Attributes functions
void SetTextBaselineOffset(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    struct ArkUIStringAndFloat offset = { 0.0, nullptr };

    std::string valueString = std::string(value);
    if (std::regex_match(valueString, FLOAT_MAGIC)) {
        offset.value = StringToFloat(value);
    } else if (std::regex_match(valueString, SIZE_TYPE_MAGIC)) {
        offset.valueStr = value;
    }

    fullImpl->getNodeModifiers()->getTextModifier()->setTextBaselineOffset(node->uiNodeHandle, &offset);
}

void SetTextTextShadow(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    std::vector<struct ArkUITextShadowStruct> shadows;
    std::vector<std::string> values;
    StringUtils::StringSplitter(value, ',', values);
    for (auto& items : values) {
        struct ArkUITextShadowStruct shadow;
        std::vector<std::string> item;
        StringUtils::StringSplitter(items.c_str(), ' ', item);
        size_t length = item.size();
        if (length > 0) {
            shadow.radius = StringToFloat(item[NUM_0].c_str());
        }
        if (length > NUM_1) {
            shadow.type = StringToEnumInt(item[NUM_1].c_str(), TEXT_TEXT_SHADOW_ARRAY, 0);
        }
        if (length > NUM_2) {
            shadow.color = StringToColorInt(item[NUM_2].c_str());
        }
        if (length > NUM_3) {
            shadow.offsetX = StringToFloat(item[NUM_3].c_str());
        }
        if (length > NUM_4) {
            shadow.offsetY = StringToFloat(item[NUM_4].c_str());
        }
        shadows.emplace_back(shadow);
    }

    fullImpl->getNodeModifiers()->getTextModifier()->setTextTextShadow(node->uiNodeHandle, &shadows[0], shadows.size());
}

// Toggle Attributes functions
void SetToggleSelectedColor(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getToggleModifier()->setToggleSelectedColor(
        node->uiNodeHandle, StringToColorInt(value, 0));
}

void SetToggleSwitchPointColor(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getToggleModifier()->setToggleSwitchPointColor(
        node->uiNodeHandle, StringToColorInt(value, 0));
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
    auto fullImpl = GetFullImpl();

    if (!item && item->size != NUM_1) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    fullImpl->getNodeModifiers()->getLoadingProgressModifier()->setColor(node->uiNodeHandle, item->value[0].u32);
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
    auto fullImpl = GetFullImpl();

    if (!item && item->size != NUM_1) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    fullImpl->getNodeModifiers()->getLoadingProgressModifier()->setEnableLoading(
        node->uiNodeHandle, item->value[0].i32);
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

int32_t SetSwiperAutoPlay(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
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

int32_t SetSwiperShowIndicator(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
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

int32_t SetSwiperInterval(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperInterval(node->uiNodeHandle, item->value[0].f32);
    return ERROR_CODE_NO_ERROR;
}

void ResetSwiperInterval(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->resetSwiperInterval(node->uiNodeHandle);
}

int32_t SetSwiperVertical(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
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

int32_t SetSwiperDuration(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
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

int32_t SetSwiperCurve(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
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

int32_t SetSwiperItemSpace(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
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

int32_t SetSwiperIndex(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
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

int32_t SetSwiperDisplayCount(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
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

int32_t SetSwiperDisableSwipe(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
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

int32_t SetSwiperShowDisplayArrow(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    double defaultBackgroundColor = StringToColorInt("#00000000", 0);
    double defaultArrowColor = StringToColorInt("#FF182431", 0);
    double displayArrow[ALLOW_SIZE_8] = { 1, 0, 0, DEFAULT_SIZE_24, defaultBackgroundColor, DEFAULT_SIZE_18,
        defaultArrowColor, 0 };
    if (item->value[0].i32 == ArkUI_SwiperDisplayArrow::ARKUI_SWIPER_ARROW__SHOW_ON_HOVER) {
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

void SetTextContent(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextModifier()->setContent(node->uiNodeHandle, value);
}

void SetSpanContent(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSpanModifier()->setContent(node->uiNodeHandle, value);
}

void SetBackgroundImageSize(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::vector<std::string> imageSizeVector;
    StringUtils::StringSplitter(std::string(value), ' ', imageSizeVector);
    CalcDimension width(0);
    if (BACKGROUND_IMAGE_WIDTH_INDEX < imageSizeVector.size()) {
        StringUtils::StringToCalcDimensionNG(
            imageSizeVector[BACKGROUND_IMAGE_WIDTH_INDEX], width, false, DimensionUnit::VP);
    }
    CalcDimension height(0);
    if (BACKGROUND_IMAGE_HEIGHT_INDEX < imageSizeVector.size()) {
        StringUtils::StringToCalcDimensionNG(
            imageSizeVector[BACKGROUND_IMAGE_HEIGHT_INDEX], height, false, DimensionUnit::VP);
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setBackgroundImageSize(node->uiNodeHandle, width.Value(),
        height.Value(), static_cast<int32_t>(width.Unit()), static_cast<int32_t>(height.Unit()));
}

void SetTransitionCenter(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::vector<std::string> transitionCenterVector;
    StringUtils::StringSplitter(std::string(value), ' ', transitionCenterVector);
    CalcDimension centerX(0);
    if (CENTER_X_INDEX < transitionCenterVector.size()) {
        StringUtils::StringToCalcDimensionNG(transitionCenterVector[CENTER_X_INDEX], centerX, false, DimensionUnit::VP);
    }
    CalcDimension centerY(0);
    if (CENTER_Y_INDEX < transitionCenterVector.size()) {
        StringUtils::StringToCalcDimensionNG(transitionCenterVector[CENTER_Y_INDEX], centerY, false, DimensionUnit::VP);
    }
    CalcDimension centerZ(0);
    if (CENTER_Z_INDEX < transitionCenterVector.size()) {
        StringUtils::StringToCalcDimensionNG(transitionCenterVector[CENTER_Z_INDEX], centerZ, false, DimensionUnit::VP);
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setTransitionCenter(node->uiNodeHandle, centerX.Value(),
        static_cast<int32_t>(centerX.Unit()), centerY.Value(), static_cast<int32_t>(centerY.Unit()), centerZ.Value(),
        static_cast<int32_t>(centerZ.Unit()));
}

void ParseAnimation(
    std::vector<std::string>& sourceVector, ArkUIAnimationOptionType& animationOption, const int animationIndexBase)
{
    const int32_t animationDurationIndex = animationIndexBase + ANIMATION_DURATION_INDEX;
    int32_t duration = DEFAULT_DURATION;
    if (animationDurationIndex < sourceVector.size()) {
        duration = StringToInt(sourceVector[animationDurationIndex].c_str(), DEFAULT_DURATION);
    }
    const int32_t animationCurveIndex = animationIndexBase + ANIMATION_CURVE_INDEX;
    std::string curve = DEFAULT_CURVE;
    if (animationCurveIndex < sourceVector.size()) {
        curve = sourceVector[animationCurveIndex];
    }
    const int32_t animationDelayIndex = animationIndexBase + ANIMATION_DELAY_INDEX;
    int32_t delay = 0;
    if (animationDelayIndex < sourceVector.size()) {
        delay = StringToInt(sourceVector[animationDelayIndex].c_str(), 0);
    }
    const int32_t animationIterationsIndex = animationIndexBase + ANIMATION_INTERATION_INDEX;
    int32_t iterations = 1;
    if (animationIterationsIndex < sourceVector.size()) {
        iterations = StringToInt(sourceVector[animationIterationsIndex].c_str(), 1);
    }
    const int32_t animationPlayModeIndex = animationIndexBase + ANIMATION_PLAY_MODE_INDEX;
    int32_t direction = 0;
    if (animationPlayModeIndex < sourceVector.size()) {
        direction = StringToEnumInt(sourceVector[animationPlayModeIndex].c_str(), PLAY_MODE_ARRAY, 0);
    }
    const int32_t animationTempoIndex = animationIndexBase + ANIMATION_TEMPO_INDEX;
    float tempo = 1.0f;
    if (animationTempoIndex < sourceVector.size()) {
        tempo = StringToFloat(sourceVector[animationTempoIndex].c_str(), 1.0f);
    }
    animationOption.duration = duration;
    animationOption.curve = curve.c_str();
    animationOption.delay = delay;
    animationOption.iteration = iterations;
    animationOption.palyMode = direction;
    animationOption.tempo = tempo;
}

void SetOpacityTransition(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::vector<std::string> opacityVector;
    StringUtils::StringSplitter(std::string(value), ' ', opacityVector);
    float opacity = DEFAULT_OPACITY;
    if (opacityVector.size() > 0) {
        opacity = std::clamp(StringUtils::StringToFloat(opacityVector[0]), 0.0f, 1.0f);
    }
    ArkUIAnimationOptionType animationOption;
    ParseAnimation(opacityVector, animationOption, OPACITY_ANIMATION_BASE);
    fullImpl->getNodeModifiers()->getCommonModifier()->setOpacityTransition(
        node->uiNodeHandle, opacity, &animationOption);
}

void SetRotateTransition(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::vector<std::string> rotateVector;
    StringUtils::StringSplitter(std::string(value), ' ', rotateVector);
    std::array<float, ARRAY_SIZE> rotateArray;
    for (size_t i = 0; i < rotateVector.size() && i < rotateArray.size(); i++) {
        rotateArray[i] = StringUtils::StringToFloat(rotateVector[i]);
    }
    float angle = 0.0f;
    if (ROTATE_ANGLE_INDEX < rotateVector.size()) {
        angle = StringUtils::StringToFloat(rotateVector[ROTATE_ANGLE_INDEX]);
    }
    float perspective = 0.0f;
    if (ROTATE_PERSPECTIVE_INDEX < rotateVector.size()) {
        perspective = StringUtils::StringToFloat(rotateVector[ROTATE_PERSPECTIVE_INDEX]);
    }
    ArkUIAnimationOptionType animationOption;
    ParseAnimation(rotateVector, animationOption, ROTATE_ANIMATION_BASE);
    fullImpl->getNodeModifiers()->getCommonModifier()->setRotateTransition(
        node->uiNodeHandle, &rotateArray[0], ARRAY_SIZE, perspective, angle, &animationOption);
}

void SetScaleTransition(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::vector<std::string> scaleVector;
    StringUtils::StringSplitter(std::string(value), ' ', scaleVector);
    std::array<float, ARRAY_SIZE> scaleFloatArray;
    for (size_t i = 0; i < scaleVector.size() && i < scaleFloatArray.size(); i++) {
        scaleFloatArray[i] = StringUtils::StringToFloat(scaleVector[i]);
    }
    ArkUIAnimationOptionType animationOption;
    ParseAnimation(scaleVector, animationOption, SCALE_ANIMATION_BASE);
    fullImpl->getNodeModifiers()->getCommonModifier()->setScaleTransition(
        node->uiNodeHandle, &scaleFloatArray[0], scaleFloatArray.size(), &animationOption);
}

void SetTranslateTransition(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::vector<std::string> translateVector;
    StringUtils::StringSplitter(std::string(value), ' ', translateVector);
    CalcDimension xDimension(0);
    if (X_INDEX < translateVector.size()) {
        StringUtils::StringToCalcDimensionNG(translateVector[X_INDEX], xDimension, false, DimensionUnit::VP);
    }
    CalcDimension yDimension(0);
    if (Y_INDEX < translateVector.size()) {
        StringUtils::StringToCalcDimensionNG(translateVector[Y_INDEX], yDimension, false, DimensionUnit::VP);
    }
    CalcDimension zDimension(0);
    if (Z_INDEX < translateVector.size()) {
        StringUtils::StringToCalcDimensionNG(translateVector[Z_INDEX], zDimension, false, DimensionUnit::VP);
    }
    ArkUIAnimationOptionType animationOption;
    ParseAnimation(translateVector, animationOption, TRANSLATE_ANIMATION_BASE);
    fullImpl->getNodeModifiers()->getCommonModifier()->setTranslateTransition(node->uiNodeHandle, xDimension.Value(),
        static_cast<int32_t>(xDimension.Unit()), yDimension.Value(), static_cast<int32_t>(yDimension.Unit()),
        zDimension.Value(), static_cast<int32_t>(zDimension.Unit()), &animationOption);
}

void SetBackgroundBlurStyle(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::vector<std::string> blurStyleVector;
    StringUtils::StringSplitter(std::string(value), ' ', blurStyleVector);
    int32_t blurStyle = 0;
    if (BLUR_STYLE_INDEX < blurStyleVector.size()) {
        blurStyle = StringToEnumInt(blurStyleVector[BLUR_STYLE_INDEX].c_str(), BLUR_STY_ARRAY, 0);
    }
    int32_t colorMode = 0;
    if (COLOR_MODE_INDEX < blurStyleVector.size()) {
        colorMode = StringToEnumInt(blurStyleVector[COLOR_MODE_INDEX].c_str(), COLOR_MODE_ARRAY, 0);
    }
    int32_t adaptiveColor = 0;
    if (ADAPTIVE_COLOR_INDEX < blurStyleVector.size()) {
        adaptiveColor = StringToEnumInt(blurStyleVector[ADAPTIVE_COLOR_INDEX].c_str(), ADAPTIVE_COLOR_ARRAY, 0);
    }
    float scale = 1.0f;
    if (SCALE_INDEX < blurStyleVector.size()) {
        scale = StringUtils::StringToFloat(blurStyleVector[SCALE_INDEX]);
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setBackgroundBlurStyle(
        node->uiNodeHandle, blurStyle, colorMode, adaptiveColor, scale);
}

void SetMaxLines(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->setTextMaxLines(
                node->uiNodeHandle, StringUtils::StringToInt(value));
            break;
        default:
            break;
    }
}

void SetLineHeight(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    CalcDimension lineHeight;
    if (StringUtils::StringToCalcDimensionNG(std::string(value), lineHeight, false, DimensionUnit::VP)) {
        switch (node->type) {
            case ARKUI_NODE_TEXT:
                fullImpl->getNodeModifiers()->getTextModifier()->setTextLineHeight(
                    node->uiNodeHandle, lineHeight.Value(), static_cast<int32_t>(lineHeight.Unit()));
                break;
            case ARKUI_NODE_SPAN:
                fullImpl->getNodeModifiers()->getSpanModifier()->setSpanLineHeight(
                    node->uiNodeHandle, lineHeight.Value(), static_cast<int32_t>(lineHeight.Unit()));
                break;
            default:
                break;
        }
        return;
    }
}

void SetTextOverflow(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextModifier()->setTextOverflow(
        node->uiNodeHandle, StringToEnumInt(value, FONT_OVERFLOW_ARRAY, 0));
}

void SetFontFamily(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

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
}

void SetCopyOption(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT) {
        fullImpl->getNodeModifiers()->getTextModifier()->setTextCopyOption(
            node->uiNodeHandle, StringToEnumInt(value, TEXT_COPY_OPTION_ARRAY, 0));
    }
}

void SetDecoration(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::vector<std::string> decorationVector;
    StringUtils::StringSplitter(std::string(value), ' ', decorationVector);
    int32_t decoration = 0;
    if (DECORATION_TYPE_INDEX < decorationVector.size()) {
        decoration = StringToEnumInt(decorationVector[DECORATION_TYPE_INDEX].c_str(), TEXT_DECORATION_TYPE_ARRAY, 0);
    }
    Color decorationColor;
    Color::ParseColorString(decorationVector[DECORATION_COLOR_INDEX], decorationColor);
    int32_t style = 0;
    if (DECORATION_STYLE_INDEX < decorationVector.size()) {
        style = StringToEnumInt(decorationVector[DECORATION_STYLE_INDEX].c_str(), TEXT_DECORATION_STYLE_ARRAY, 0);
    }
    switch (node->type) {
        case ARKUI_NODE_SPAN:
            fullImpl->getNodeModifiers()->getSpanModifier()->setSpanDecoration(
                node->uiNodeHandle, decoration, decorationColor.GetValue(), style);
            break;
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->setTextDecoration(
                node->uiNodeHandle, decoration, decorationColor.GetValue(), style);
        default:
            break;
    }
}

void SetLetterSpacing(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    ArkUIStringAndFloat letterSpacingValue = { 0.0, value };
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
}

void SetTextCase(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_SPAN:
            fullImpl->getNodeModifiers()->getSpanModifier()->setSpanTextCase(
                node->uiNodeHandle, StringToEnumInt(value, TEXT_CASE_ARRAY, 0));
            break;
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->setTextCase(
                node->uiNodeHandle, StringToEnumInt(value, TEXT_CASE_ARRAY, 0));
        default:
            break;
    }
}

// image span
void SetImageSpanSrc(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageModifier()->setSrc(node->uiNodeHandle, value);
}

void SetVerticalAlign(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageSpanModifier()->setImageSpanVerticalAlign(
        node->uiNodeHandle, StringToEnumInt(value, IMAGE_SPAN_VERTICAL_ALIGN, 0));
}

// image
void SetImageSrc(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageModifier()->setSrc(node->uiNodeHandle, value);
}

void SetObjectFit(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_IMAGE_SPAN:
            fullImpl->getNodeModifiers()->getImageSpanModifier()->setImageSpanObjectFit(
                node->uiNodeHandle, StringToEnumInt(value, IMAGE_FIT_ARRAY, DEFAULT_OBJECT_FIT));
            break;
        case ARKUI_IMAGE:
            fullImpl->getNodeModifiers()->getImageModifier()->setObjectFit(
                node->uiNodeHandle, StringToEnumInt(value, IMAGE_FIT_ARRAY, DEFAULT_OBJECT_FIT));
            break;
        default:
            break;
    }
}

void SetInterpolation(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageModifier()->setImageInterpolation(
        node->uiNodeHandle, StringToEnumInt(value, IMAGE_INTERPOLATION_ARRAY, 0));
}

void SetObjectRepeat(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageModifier()->setObjectRepeat(
        node->uiNodeHandle, StringToEnumInt(value, IMAGE_REPEAT_ARRAY, 0));
}

void SetColorFilter(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::vector<std::string> colorFilterArray;
    StringUtils::StringSplitter(std::string(value), ' ', colorFilterArray);
    std::vector<float> colorFloatArray;

    for (size_t i = 0; i < colorFilterArray.size(); i++) {
        colorFloatArray.emplace_back(StringUtils::StringToFloat(colorFilterArray[i]));
    }
    if (!colorFloatArray.empty()) {
        fullImpl->getNodeModifiers()->getImageModifier()->setColorFilter(
            node->uiNodeHandle, &colorFloatArray[0], colorFilterArray.size());
    } else {
        fullImpl->getNodeModifiers()->getImageModifier()->resetColorFilter(node->uiNodeHandle);
    }
}

void SetAutoResize(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getImageModifier()->setAutoResize(
        node->uiNodeHandle, static_cast<bool>(StringToBoolInt(value, 0)));
}

void SetAlt(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getImageModifier()->setAlt(node->uiNodeHandle, value, nullptr, nullptr);
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

// datepicker
void SetDatePickerLunar(ArkUI_NodeHandle node, const char* value)
{
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }
}

void SetDatePickerStart(ArkUI_NodeHandle node, const char* value)
{
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    std::vector<std::string> date;
    StringUtils::StringSplitter(std::string(value), '-', date);
    if (date.size() != NUM_3) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "date is valid");
        return;
    }
}

void SetDatePickerEnd(ArkUI_NodeHandle node, const char* value)
{
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    std::vector<std::string> date;
    StringUtils::StringSplitter(std::string(value), '-', date);
    if (date.size() != NUM_3) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "date is valid");
        return;
    }
}

void SetDatePickerSelected(ArkUI_NodeHandle node, const char* value)
{
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    std::vector<std::string> date;
    StringUtils::StringSplitter(std::string(value), '-', date);
    if (date.size() != NUM_3) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "date is valid");
        return;
    }
}

void SetDatePickerDisappearTextStyle(ArkUI_NodeHandle node, const char* value)
{
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }
}

void SetDatePickerTextStyle(ArkUI_NodeHandle node, const char* value)
{
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }
}

void SetDatePickerSelectedTextStyle(ArkUI_NodeHandle node, const char* value)
{
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }
}

// timepicker
void SetTimePickerSelected(ArkUI_NodeHandle node, const char* value)
{
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }
}

void SetTimeUseMilitaryTime(ArkUI_NodeHandle node, const char* value)
{
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }
}

void SetTimePickerDisappearTextStyle(ArkUI_NodeHandle node, const char* value)
{
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }
}

void SetTimePickerTextStyle(ArkUI_NodeHandle node, const char* value)
{
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }
}

void SetTimePickerSelectedTextStyle(ArkUI_NodeHandle node, const char* value)
{
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }
}

// TextPicker
void SetTextPickerDisappearTextStyle(ArkUI_NodeHandle node, const char* value)
{
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }
}

void SetTextPickerTextStyle(ArkUI_NodeHandle node, const char* value)
{
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }
}

void SetTextPickerSelectedTextStyle(ArkUI_NodeHandle node, const char* value)
{
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }
}

void SetTextPickerSelectedIndex(ArkUI_NodeHandle node, const char* value)
{
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }
}

void ResetBackgroundImageSize(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    // 1 for vp. check in DimensionUnit.
    fullImpl->getNodeModifiers()->getCommonModifier()->resetBackgroundImageSize(node->uiNodeHandle);
}

void ResetBackgroundBlurStyle(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    // 1 for vp. check in DimensionUnit.
    fullImpl->getNodeModifiers()->getCommonModifier()->resetBackgroundBlurStyle(node->uiNodeHandle);
}

void ResetTransitionCenter(ArkUI_NodeHandle node) {}

void ResetOpacityTransition(ArkUI_NodeHandle node) {}

void ResetRotateTransition(ArkUI_NodeHandle node) {}

void ResetScaleTransition(ArkUI_NodeHandle node) {}

void ResetTranslateTransition(ArkUI_NodeHandle node) {}

void ResetOffset(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->resetOffset(node->uiNodeHandle);
}

void ResetMarkAnchor(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->resetMarkAnchor(node->uiNodeHandle);
}

void ResetAlignRules(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->resetAlignRules(node->uiNodeHandle);
}

void ResetTextContent(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
}

void ResetLineHeight(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
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
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
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
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
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
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
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
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
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
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
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
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getTextModifier()->resetTextOverflow(node->uiNodeHandle);
}

void ResetSpanContent(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
}

void ResetImageSpanSrc(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
}
void ResetVerticalAlign(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
}
void ResetImageSrc(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
}
void ResetObjectFit(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getImageModifier()->resetObjectFit(node->uiNodeHandle);
}

void ResetInterpolation(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getImageModifier()->resetImageInterpolation(node->uiNodeHandle);
}

void ResetObjectRepeat(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getImageModifier()->resetObjectRepeat(node->uiNodeHandle);
}

void ResetColorFilter(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getImageModifier()->resetColorFilter(node->uiNodeHandle);
}

void ResetAutoResize(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getImageModifier()->resetAutoResize(node->uiNodeHandle);
}

void ResetAlt(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getImageModifier()->resetAlt(node->uiNodeHandle);
}
using Setter = void(ArkUI_NodeHandle node, const char* value);
using Resetter = void(ArkUI_NodeHandle node);
void SetCommonAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const char* value)
{
    static Setter* setters[] = { SetWidth, SetHeight, SetBackgroundColor, SetBackgroundImage, SetPadding, SetKey,
        SetEnabled, SetMargin, SetTranslate, SetScale, SetRotate, SetBrightness, SetSaturate, SetBlur,
        SetLinearGradient, SetAlign, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, SetBackgroundImageSize, SetBackgroundBlurStyle, SetTransitionCenter,
        SetOpacityTransition, SetRotateTransition, SetScaleTransition, SetTranslateTransition, SetFocusable,
        SetAccessibilityGroup, SetAccessibilityText, SetAccessibilityLevel, SetAccessibilityDescription,
        SetDefaultFocus, SetResponseRegion, SetOverlay, SetBackgroundImagePosition, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        SetOffset, SetMarkAnchor, SetAlignRules, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "common node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    setters[subTypeId](node, value);
}

int32_t SetCommonAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* value)
{
    using Setter = int32_t(ArkUI_NodeHandle node, const ArkUI_AttributeItem* value);
    static Setter* setters[] = { SetWidth, SetHeight, SetBackgroundColor, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, SetOpacity, SetBorderWidth,
        SetBorderRadius, SetBorderColor, SetBorderStyle, SetZIndex, SetVisibility, SetClip, SetClipShape, SetTransform,
        SetHitTestBehavior, SetPosition, SetShadow, SetCustomShadow, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        SetSweepGradient, SetRadialGradient, SetMask, SetBlendMode, SetDirection, SetAlignSelf, SetFlexGrow,
        SetFlexShrink, SetFlexBasis, SetConstraintSize, SetGrayscale, SetInvert, SetSepia, SetContrast,
        SetForegroundColor };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "common node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, value);
}

void SetTextAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const char* value)
{
    static Setter* setters[] = { SetTextContent, SetFontColor, SetFontSize, SetFontStyle, SetFontWeight, SetLineHeight,
        SetDecoration, SetTextCase, SetLetterSpacing, SetMaxLines, SetTextAlign, SetTextOverflow, SetFontFamily,
        SetCopyOption, SetTextBaselineOffset, SetTextTextShadow, SetTextIndent };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "text node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    setters[subTypeId](node, value);
}

void SetSpanAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const char* value)
{
    static Setter* setters[] = { SetSpanContent };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "span node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    setters[subTypeId](node, value);
}

void SetImageSpanAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const char* value)
{
    static Setter* setters[] = { SetImageSpanSrc, SetVerticalAlign };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "image span node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    setters[subTypeId](node, value);
}

void SetImageAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const char* value)
{
    static Setter* setters[] = { SetImageSrc, SetObjectFit, SetInterpolation, SetObjectRepeat, SetColorFilter,
        SetAutoResize, SetAlt };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "image node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    setters[subTypeId](node, value);
}

void SetTextInputAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const char* value)
{
    static Setter* setters[] = { SetTextInputPlaceholder, SetTextInputText, SetCaretColor, SetCaretStyle,
        SetShowUnderline, SetMaxLength, SetEnterKeyType, SetPlaceholderColor, SetTextInputPlaceholderFont,
        SetEnableKeybordOnFocus, SetTextInputType, SetSelectedBackgroundColor, SetShowPasswordIcon };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "textinput node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    setters[subTypeId](node, value);
}

void SetStackAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const char* value)
{
    static Setter* setters[] = { SetAlignContent };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "common node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    setters[subTypeId](node, value);
}

void SetToggleAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const char* value)
{
    static Setter* setters[] = { SetToggleSelectedColor, SetToggleSwitchPointColor };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "toggle node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    setters[subTypeId](node, value);
}

void SetScrollAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const char* value)
{
    static Setter* setters[] = { SetScrollScrollBar, SetScrollScrollBarWidth, SetScrollScrollBarColor,
        SetScrollScrollable, SetScrollEdgeEffect, SetScrollEnableScrollInteraction, SetScrollFriction,
        SetScrollScrollSnap, SetScrollNestedScroll, SetScrollTo, SetScrollEdge, SetScrollEnablePaging };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "scroll node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    setters[subTypeId](node, value);
}

void SetListAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const char* value)
{
    static Setter* setters[] = { SetListScrollBar, SetListScrollBarWidth, SetListScrollBarColor, SetListListDirection,
        SetListListSticky, SetListEdgeEffect, SetListEnableScrollInteraction, SetListFriction, SetListSpace };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "list node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    setters[subTypeId](node, value);
}

void SetTextAreaAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const char* value)
{
    static Setter* setters[] = { SetTextAreaPlaceholder, SetTextAreaText, SetMaxLength, SetPlaceholderColor,
        SetTextAreaPlaceholderFont, SetCaretColor, StopTextAreaEditing };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "textarea node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    setters[subTypeId](node, value);
}

void SetXComponentAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const char* value)
{
    static Setter* setters[] = {
        SetXComponentId,
        SetXComponentType,
        SetXComponentSurfaceSize,
    };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "xcomponent node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    setters[subTypeId](node, value);
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

void SetTimePickerAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const char* value)
{
    static Setter* setters[] = { SetTimePickerSelected, SetTimeUseMilitaryTime, SetTimePickerDisappearTextStyle,
        SetTimePickerTextStyle, SetTimePickerSelectedTextStyle };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "timepicker node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    setters[subTypeId](node, value);
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

void ResetCommonAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, ResetOpacity, ResetBorderWidth,
        ResetBorderRadius, ResetBorderColor, ResetBorderStyle, ResetZIndex, ResetVisibility, ResetClip, ResetClipShape,
        ResetTransform, ResetHitTestBehavior, ResetPosition, ResetShadow, ResetCustomShadow, ResetBackgroundImageSize,
        ResetBackgroundBlurStyle, ResetTransitionCenter, ResetOpacityTransition, ResetRotateTransition,
        ResetScaleTransition, ResetTranslateTransition, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, ResetSweepGradient, ResetRadialGradient, nullptr, ResetBlendMode,
        ResetDirection, ResetAlignSelf, ResetFlexGrow, ResetFlexShrink, ResetFlexBasis, ResetConstraintSize,
        ResetGrayscale, ResetInvert, ResetSepia, ResetContrast, ResetForegroundColor, ResetOffset, ResetMarkAnchor,
        ResetAlignRules };
    if (subTypeId >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "common node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    resetters[subTypeId](node);
}

void ResetTextAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = { ResetTextContent, nullptr, nullptr, nullptr, nullptr, ResetLineHeight,
        ResetDecoration, ResetTextCase, ResetLetterSpacing, ResetMaxLines, ResetTextAlign, ResetTextOverflow, nullptr,
        nullptr, nullptr, nullptr, nullptr };
    if (subTypeId >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "text node attribute: %{public}d NOT IMPLEMENT", subTypeId);
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
} // namespace

void SetNodeAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType type, const char* value)
{
    using AttributeSetterClass = void(ArkUI_NodeHandle node, int32_t subTypeId, const char* value);
    static AttributeSetterClass* setterClasses[] = { SetCommonAttribute, SetTextAttribute, SetSpanAttribute,
        SetImageSpanAttribute, SetImageAttribute, SetToggleAttribute, SetLoadingProgressAttribute,
        SetTextInputAttribute, SetStackAttribute, SetScrollAttribute, SetListAttribute, nullptr, SetTextAreaAttribute,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, SetXComponentAttribute,
        SetListItemGroupAttribute, SetDatePickerAttribute, SetTimePickerAttribute, SetTextPickerAttribute };
    int32_t subTypeClass = type / MAX_NODE_SCOPE_NUM;
    int32_t subTypeId = type % MAX_NODE_SCOPE_NUM;
    if (subTypeClass > sizeof(setterClasses) / sizeof(AttributeSetterClass*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "node attribute: %{public}d NOT IMPLEMENT", type);
        return;
    }
    setterClasses[subTypeClass](node, subTypeId, value);
}

int32_t SetNodeAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType type, const ArkUI_AttributeItem* item)
{
    using AttributeSetterClass = int32_t(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item);
    static AttributeSetterClass* setterClasses[] = { SetCommonAttribute, nullptr, nullptr, nullptr, nullptr, nullptr,
        SetLoadingProgressAttribute, nullptr, nullptr, nullptr, nullptr, SetSwiperAttribute, nullptr, nullptr,
        nullptr };
    int32_t subTypeClass = type / MAX_NODE_SCOPE_NUM;
    int32_t subTypeId = type % MAX_NODE_SCOPE_NUM;
    if (subTypeClass > sizeof(setterClasses) / sizeof(AttributeSetterClass*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "node attribute: %{public}d NOT IMPLEMENT", type);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    auto result = setterClasses[subTypeClass](node, subTypeId, item);
    if (result == ERROR_CODE_NO_ERROR) {
        GetFullImpl()->getBasicAPI()->markDirty(node->uiNodeHandle, ARKUI_DIRTY_FLAG_ATTRIBUTE_DIFF);
    }
    return result;
}

const ArkUI_AttributeItem* GetNodeAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType type)
{
    ResetAttributeItem();
    using AttributeGetterClass = const ArkUI_AttributeItem*(ArkUI_NodeHandle node, int32_t subTypeId);
    static AttributeGetterClass* getterClasses[] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        GetLoadingProgressAttribute, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
    int32_t subTypeClass = type / MAX_NODE_SCOPE_NUM;
    int32_t subTypeId = type % MAX_NODE_SCOPE_NUM;
    if (subTypeClass > sizeof(getterClasses) / sizeof(AttributeGetterClass*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "node attribute: %{public}d NOT IMPLEMENT", type);
        return &g_attributeItem;
    }
    return getterClasses[subTypeClass](node, subTypeId);
}

void ResetNodeAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType type)
{
    using AttributeResetterClass = void(ArkUI_NodeHandle node, int32_t subTypeId);
    static AttributeResetterClass* resetterClasses[] = { ResetCommonAttribute, ResetTextAttribute, ResetSpanAttribute,
        ResetImageSpanAttribute, ResetImageAttribute, nullptr, ResetLoadingProgressAttribute, nullptr, nullptr, nullptr,
        nullptr, ResetSwiperAttribute, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr };
    int32_t subTypeClass = type / MAX_NODE_SCOPE_NUM;
    int32_t subTypeId = type % MAX_NODE_SCOPE_NUM;
    if (subTypeClass > sizeof(resetterClasses) / sizeof(AttributeResetterClass*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "node attribute: %{public}d NOT IMPLEMENT", type);
        return;
    }
    resetterClasses[subTypeClass](node, subTypeId);
}

} // namespace OHOS::Ace::NodeModel
