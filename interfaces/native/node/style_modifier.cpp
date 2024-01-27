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
constexpr int DEFAULT_UNIT = 1;
const int ALLOW_SIZE_1(1);
const int ALLOW_SIZE_4(4);
const int ALLOW_SIZE_7(7);
const int ALLOW_SIZE_8(8);
const int ALLOW_SIZE_16(16);
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
const std::vector<std::string> COMMON_SHADOW_TYPE = { "color", "blur" };
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
const std::vector<std::string> FONT_STYLES = { "normal", "italic" };
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
constexpr float HUNDRED = 100.0f;
constexpr int32_t MAX_ATTRIBUTE_ITEM_LEN = 12;
ArkUI_NumberValue g_numberValues[MAX_ATTRIBUTE_ITEM_LEN] = { 0 };
ArkUI_AttributeItem g_attributeItem = { g_numberValues, MAX_ATTRIBUTE_ITEM_LEN, nullptr, nullptr };

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

bool IsSingleNumber(const std::string& str)
{
    // 判断是否为单个数字
    return str.find_first_of("0123456789") != std::string::npos &&
           str.find_first_of(" \t\n\r\f\v") == std::string::npos;
}

bool IsMultipleNumbers(const std::string& str)
{
    // 判断是否为多个数字，使用空格连接
    return str.find_first_of("0123456789") != std::string::npos &&
           str.find_first_of(" \t\n\r\f\v") != std::string::npos;
}

bool IsMultipleWords(const std::string& str)
{
    return std::find(str.begin(), str.end(), ' ') != str.end();
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
        node->uiNodeHandle, item->value[NUM_0].f32, UNIT_VP, nullptr);
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
        node->uiNodeHandle, item->value[NUM_0].f32, UNIT_VP, nullptr);
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
    fullImpl->getNodeModifiers()->getCommonModifier()->setBackgroundColor(node->uiNodeHandle, item->value[NUM_0].u32);
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

int32_t SetMargin(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();

    if (!item && (item->size != NUM_4 || item->size != NUM_1)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }
    ArkUISizeType top, right, bottom, left;
    top.value= right.value = bottom.value = left.value = NUM_0;
    top.unit= right.unit = bottom.unit = left.unit = DEFAULT_UNIT;
    if (item->size == NUM_1) {
        top.value= right.value = bottom.value = left.value = item->value[NUM_0].f32;
    } else if (item->size == NUM_4) {
        top.value = item->value[NUM_0].f32;
        right.value = item->value[1].f32;
        bottom.value = item->value[2].f32;
        left.value = item->value[3].f32;
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

int32_t SetTranslate(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();

    if (!item && item->size != NUM_3) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }
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

    fullImpl->getNodeModifiers()->getCommonModifier()->setScale(
        node->uiNodeHandle, values, size + NUM_1, units, NUM_2);
}

int32_t SetScale(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();

    if (item->size != NUM_2) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }
    ArkUI_Float32 values[] = { item->value[NUM_0].f32, item->value[NUM_1].f32 };
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

int32_t SetRotate(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();

    if (!item && item->size != NUM_5) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }
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

int32_t SetBrightness(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();
    if (!item && item->size == NUM_1) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }
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

int32_t SetSaturate(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();

    if (!item && item->size == NUM_1) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }
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

int32_t SetBlur(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();

    if (!item && item->size == NUM_1) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }
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

int32_t SetLinearGradient(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();
    if (!item && !item->string) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }
    std::vector<std::string> params;
    StringUtils::StringSplitter(item->string, ' ', params);
    if (params.size() < NUM_1) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return ERROR_CODE_PARAM_INVALID;
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
    return ERROR_CODE_NO_ERROR;
}

void ResetLinearGradient(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getCommonModifier()->resetLinearGradient(node->uiNodeHandle);
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

int32_t SetAlign(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();
    if (!item && item->size != NUM_1) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

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

void SetOpacity(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setOpacity(node->uiNodeHandle, StringToFloat(value, 0.0f));
}

void SetBorderWidth(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::string widths(value);
    ArkUI_Float32 widthVals[ALLOW_SIZE_4] = { 0, 0, 0, 0 };
    int widthUnits[ALLOW_SIZE_4];

    if (IsSingleNumber(widths)) {
        for (int i = 0; i < ALLOW_SIZE_4; ++i) {
            widthVals[i] = StringToFloat(widths.c_str(), 0.0f); // 将整数i转换为浮点数并赋值给数组的相应位置
            widthUnits[i] = DEFAULT_UNIT;
        }
    }

    if (IsMultipleNumbers(widths)) {
        std::vector<std::string> widthsProps;
        StringUtils::StringSplitter(widths.c_str(), ' ', widthsProps);
        int widthsSize;
        if (widthsProps.size() <= ALLOW_SIZE_4) {
            widthsSize = widthsProps.size();
        } else {
            widthsSize = ALLOW_SIZE_4;
        }

        for (int i = 0; i < widthsSize; ++i) {
            widthVals[i] = StringToFloat(widthsProps[i].c_str(), 0.0f); // 将整数i转换为浮点数并赋值给数组的相应位置
            widthUnits[i] = DEFAULT_UNIT;
        }
    }

    fullImpl->getNodeModifiers()->getCommonModifier()->setBorderWidth(
        node->uiNodeHandle, widthVals, widthUnits, ALLOW_SIZE_4);
}

void SetBorderRadius(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::string radius(value);
    ArkUI_Float32 radiusVals[ALLOW_SIZE_4] = { 1, 1, 1, 1 };
    int radiusUnits[ALLOW_SIZE_4];

    if (IsSingleNumber(radius)) {
        for (int i = 0; i < ALLOW_SIZE_4; ++i) {
            radiusVals[i] = StringToFloat(radius.c_str(), 0.0f);
            radiusUnits[i] = DEFAULT_UNIT;
        }
    }

    if (IsMultipleNumbers(radius)) {
        std::vector<std::string> radiusProps;
        StringUtils::StringSplitter(radius.c_str(), ' ', radiusProps);
        int radiusSize;
        if (radiusProps.size() <= ALLOW_SIZE_4) {
            radiusSize = radiusProps.size();
        } else {
            radiusSize = ALLOW_SIZE_4;
        }

        for (int i = 0; i < radiusSize; ++i) {
            radiusVals[i] = StringToFloat(radiusProps[i].c_str(), 0.0f);
            radiusUnits[i] = DEFAULT_UNIT;
        }
    }

    fullImpl->getNodeModifiers()->getCommonModifier()->setBorderRadius(
        node->uiNodeHandle, radiusVals, radiusUnits, ALLOW_SIZE_4);
}

void SetBorderColor(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    ArkUI_Float32 defaultBackgroundColor = StringToColorInt("#00000000", 0);
    std::string colorStr(value);
    int colors[ALLOW_SIZE_4] = { defaultBackgroundColor, defaultBackgroundColor, defaultBackgroundColor,
        defaultBackgroundColor };

    if (IsMultipleWords(colorStr)) {
        std::vector<std::string> colorsProps;
        StringUtils::StringSplitter(colorStr.c_str(), ' ', colorsProps);
        int colorsSize;
        if (colorsProps.size() <= ALLOW_SIZE_4) {
            colorsSize = colorsProps.size();
        } else {
            colorsSize = ALLOW_SIZE_4;
        }

        for (int i = 0; i < colorsSize; ++i) {
            colors[i] = StringToColorInt(colorsProps[i].c_str(), 0);
        }
    } else {
        for (int i = 0; i < ALLOW_SIZE_4; ++i) {
            colors[i] = StringToColorInt(value, 0);
        }
    }

    fullImpl->getNodeModifiers()->getCommonModifier()->setBorderColor(
        node->uiNodeHandle, colors[NUM_0], colors[NUM_1], colors[NUM_2], colors[NUM_3]);
}

void SetBorderStyle(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::string styleStr(value);

    if (IsMultipleWords(styleStr)) {
        int styles[ALLOW_SIZE_4] = { 0, 0, 0, 0 };
        std::vector<std::string> styleProps;
        StringUtils::StringSplitter(styleStr.c_str(), ' ', styleProps);
        int styleSize;
        if (styleProps.size() <= ALLOW_SIZE_4) {
            styleSize = styleProps.size();
        } else {
            styleSize = ALLOW_SIZE_4;
        }
        for (int i = 0; i < styleSize; ++i) {
            styles[i] = StringToEnumInt(styleProps[i].c_str(), COMMON_BORDER_STYLE, 0);
        }
        fullImpl->getNodeModifiers()->getCommonModifier()->setBorderStyle(node->uiNodeHandle, styles, ALLOW_SIZE_4);
    } else {
        int styles[NUM_1] = { 0 };
        styles[NUM_0] = StringToEnumInt(styleStr.c_str(), COMMON_BORDER_STYLE, 0);
        fullImpl->getNodeModifiers()->getCommonModifier()->setBorderStyle(node->uiNodeHandle, styles, ALLOW_SIZE_1);
    }
}

void SetZIndex(ArkUI_NodeHandle node, const char* value = "0")
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::string zIndex(value);
    fullImpl->getNodeModifiers()->getCommonModifier()->setZIndex(node->uiNodeHandle, StringUtils::StringToInt(zIndex));
}

void SetVisibility(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setVisibility(
        node->uiNodeHandle, StringToEnumInt(value, COMMON_VISIBLE_STYLE, 0));
}

void SetClip(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::string clipStr(value);
    StringUtils::TrimStr(clipStr);
    if (std::regex_search(clipStr, BRACKETS)) {
        std::size_t pos1 = clipStr.find_first_of('(');
        std::size_t pos2 = clipStr.find_first_of(')');
        std::string shape = clipStr.substr(0, pos1);
        std::string content = clipStr.substr(pos1 + 1, pos2 - pos1 - 1);
        std::vector<std::string> attributeProps;
        StringUtils::StringSplitter(content.c_str(), ',', attributeProps);
        if (std::string("path") == shape) {
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
}

void SetTransform(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::string transformStr(value);
    float transforms[ALLOW_SIZE_16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
    std::vector<std::string> TransformProps;
    StringUtils::StringSplitter(transformStr.c_str(), ' ', TransformProps);
    for (int i = 0; i < TransformProps.size(); ++i) {
        transforms[i] = StringToFloat(TransformProps[i].c_str(), 0);
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setTransform(node->uiNodeHandle, transforms, ALLOW_SIZE_16);
}

void SetHitTestBehavior(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setHitTestBehavior(
        node->uiNodeHandle, StringToEnumInt(value, COMMON_HIT_TEST_MODE_STYLE, 0));
}

void SetPosition(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::string positionStr(value);
    float positions[ALLOW_SIZE_4] = { 0, 1, 0, 1 };
    std::vector<std::string> positionProps;
    StringUtils::StringSplitter(positionStr.c_str(), ' ', positionProps);
    if (positionProps.size() > NUM_0) {
        positions[NUM_0] = StringToFloat(positionProps[NUM_0].c_str(), 0.0f);
    }
    if (positionProps.size() > NUM_1) {
        positions[NUM_2] = StringToFloat(positionProps[NUM_1].c_str(), 0.0f);
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setPosition(
        node->uiNodeHandle, positions[NUM_0], positions[NUM_1], positions[NUM_2], positions[NUM_3]);
}

void SetShadow(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::string shadowStr(value);
    if (IsMultipleWords(shadowStr)) {
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
    } else {
        ArkUI_Float32 shadows[NUM_1] = { 0 };
        shadows[NUM_0] = StringToEnumInt(value, COMMON_SHADOW_STYLE, 0);
        fullImpl->getNodeModifiers()->getCommonModifier()->setBackShadow(node->uiNodeHandle, shadows, ALLOW_SIZE_1);
    }
}

int32_t SetFocusable(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setFocusable(
        node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetFocusable(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetFocusable(
        node->uiNodeHandle);
}

int32_t SetAccessibilityGroup(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setAccessibilityGroup(
        node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;    
}

void ResetAccessibilityGroup(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetAccessibilityGroup(
        node->uiNodeHandle);
}

int32_t SetAccessibilityText(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setAccessibilityText(
        node->uiNodeHandle, item->string);
    return ERROR_CODE_NO_ERROR;
}

void ResetAccessibilityText(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetAccessibilityText(
        node->uiNodeHandle);
}

int32_t SetAccessibilityLevel(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setAccessibilityLevel(
        node->uiNodeHandle, item->string);
    return ERROR_CODE_NO_ERROR;
}

void ResetAccessibilityLevel(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetAccessibilityLevel(
        node->uiNodeHandle);
}

int32_t SetAccessibilityDescription(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setAccessibilityDescription(
        node->uiNodeHandle, item->string);
    return ERROR_CODE_NO_ERROR;
}

void ResetAccessibilityDescription(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetAccessibilityDescription(
        node->uiNodeHandle);
}

int32_t SetDefaultFocus(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setDefaultFocus(
        node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetDefaultFocus(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetDefaultFocus(
        node->uiNodeHandle);
}

int32_t SetResponseRegion(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || item->size % NUM_4 > 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();

    std::vector<float> valuesArray;
    std::vector<int> unitsArray;

    for (int i = 0; i < item->size; i ++) {
        int remainder = i % NUM_4;
        valuesArray.push_back(remainder > 1 ? (item->value[i].f32)/HUNDRED : item->value[i].f32);
            // unit 1 3
        unitsArray.push_back(remainder > 1 ? NUM_3 : NUM_1);
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setResponseRegion(
        node->uiNodeHandle, valuesArray.data(), unitsArray.data(), valuesArray.size());
    return ERROR_CODE_NO_ERROR;
}

void ResetResponseRegion(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetResponseRegion(
        node->uiNodeHandle);
}

int32_t SetOverlay(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();

    ArkUI_Float32 values[ALLOW_SIZE_10] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

    if (item->size > 0) {
        values[0] = 1;
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

void ResetOverlay(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetOverlay(
        node->uiNodeHandle);
}

void SetBackgroundImagePosition(ArkUI_NodeHandle node, const char* value)
{
    auto* fullImpl = GetFullImpl();
    std::vector<std::string> positions;
    StringUtils::StringSplitter(value, PARAMS_SEPARATOR_LEVEL1, positions);
    if (positions.size() != NUM_2) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "positions are invalid");
        return;
    }
    ArkUI_Float32 values[NUM_2] = { NUM_0, NUM_0 };
    ArkUI_Int32 units[NUM_2] = { UNIT_VP, UNIT_VP };

    values[NUM_0] = StringUtils::StringToDouble(positions[NUM_0]);
    values[NUM_1] = StringUtils::StringToDouble(positions[NUM_1]);

    fullImpl->getNodeModifiers()->getCommonModifier()->setBackgroundImagePosition(
        node->uiNodeHandle, values, units, false, NUM_2);
}

int32_t SetBackgroundImagePosition(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();

    if (!item && item->size != NUM_2) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "positions are invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    ArkUI_Float32 values[] = { item->value[NUM_0].f32, item->value[NUM_1].f32 };
    ArkUI_Int32 units[] = { DEFAULT_UNIT, DEFAULT_UNIT };

    fullImpl->getNodeModifiers()->getCommonModifier()->setBackgroundImagePosition(node->uiNodeHandle,
        values, units, false, NUM_2);
    return ERROR_CODE_NO_ERROR;
}

void ResetBackgroundImagePosition(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getCommonModifier()->resetBackgroundImagePosition(node->uiNodeHandle);
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
            alignStyleArray[i / TWO] = ((i / TWO) < HORIZONTAL_DIRECTION_RANGE)
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

int32_t SetAlignContent(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();

    if (!item && item->size != NUM_1) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

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

// Scroll Arttribute functions
void SetScrollFriction(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollFriction(node->uiNodeHandle, StringToFloat(value));
}

int32_t SetScrollFriction(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();

    if (!item && item->size != NUM_1) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

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

int32_t SetScrollScrollSnap(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();

    if (!item && item->size < NUM_4) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }
    auto snapAlign = item->value[NUM_0].i32;
    auto enableSnapToStart = item->value[NUM_1].i32;
    auto enableSnapToEnd = item->value[NUM_2].i32;

    ArkUI_Float32 paginations[item->size];
    ArkUI_Int32 paginationParams[item->size + 1];
    for (int i = 0; i < item->size - NUM_3; ++i) {
        paginations[i] = item->value[i].f32;
        paginationParams[i] = UNIT_VP;
    }

    paginationParams[item->size + NUM_0] = snapAlign;
    paginationParams[item->size + NUM_1] = enableSnapToStart;
    paginationParams[item->size + NUM_2] = enableSnapToEnd;
    paginationParams[item->size + NUM_3] = (item->size - NUM_3 > 1) ? true : false;

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

int32_t SetScrollScrollBar(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();

    if (!item && item->size == NUM_1) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }
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

int32_t SetScrollScrollBarWidth(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();

    if (!item && item->size == NUM_1) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }
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

void ResetScrollScrollBarWidth(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    if (node->type == ARKUI_NODE_LIST) {
        fullImpl->getNodeModifiers()->getListModifier()->resetListScrollBarWidth(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_SCROLL) {
        fullImpl->getNodeModifiers()->getScrollModifier()->resetScrollScrollBarWidth(node->uiNodeHandle);
    }
}

void SetScrollScrollBarColor(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    auto color = StringToColorInt(value, 0);
    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollScrollBarColor(node->uiNodeHandle, color);
}

int32_t SetScrollScrollBarColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();

    if (!item && item->size == NUM_1) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }
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

int32_t SetScrollScrollable(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();

    if (!item && item->size == NUM_1) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

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

int32_t SetScrollEdgeEffect(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();

    if (!item && (item->size < NUM_1 || item->size > NUM_2)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

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

int32_t SetScrollEnableScrollInteraction(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();

    if (!item && item->size != NUM_1) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }
    bool enableScrollInteraction = item->value[NUM_0].i32;
    fullImpl->getNodeModifiers()->getScrollModifier()->setEnableScrollInteraction(
        node->uiNodeHandle, enableScrollInteraction);
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
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    int first = item->value[NUM_0].i32;
    int second = 0;
    if (item->size > ALLOW_SIZE_1) {
        second = item->value[NUM_1].i32;
    }
    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollNestedScroll(node->uiNodeHandle,
        first,second);
    return ERROR_CODE_NO_ERROR;
}

void ResetScrollNestedScroll(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getScrollModifier()->resetScrollNestedScroll(
        node->uiNodeHandle);
}

int32_t SetScrollTo(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size < 2) {
        return ERROR_CODE_PARAM_INVALID;
    }
    TAG_LOGI(AceLogTag::ACE_NATIVE_NODE, "SetScrollTo:%{public}d", item->size);
    auto* fullImpl = GetFullImpl();
    ArkUI_Float32 values[ALLOW_SIZE_7] = { 0.0, UNIT_VP, 0.0, UNIT_VP, DEFAULT_DURATION, 1, 0.0 };
    values[0] = item->value[0].f32;
    values[1] = UNIT_VP;
    values[2] = item->value[1].f32;
    values[3] = UNIT_VP;
    if (item->size > 2) {
        values[4] = item->value[2].i32;
    }
    if (item->size > 3) {
        values[5] = item->value[3].i32;
    }
    if (item->size > 4) {
        values[6] = item->value[4].i32;
    }
    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollTo(node->uiNodeHandle, values);
    return ERROR_CODE_NO_ERROR;
}

void ResetScrollTo(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getScrollModifier()->resetScrollTo(
        node->uiNodeHandle);
}

int32_t SetScrollEdge(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollEdge(
        node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetScrollEdge(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getScrollModifier()->resetScrollEdge(
        node->uiNodeHandle);
}

void SetScrollEnablePaging(ArkUI_NodeHandle node, const char* value)
{
    auto* fullImpl = GetFullImpl();

    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    auto enablePaging = StringToBoolInt(value, false);

    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollEnablePaging(node->uiNodeHandle, enablePaging);
}

int32_t SetScrollEnablePaging(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();

    if (!item && item->size != NUM_1) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getScrollModifier()->setEnableScrollInteraction(node->uiNodeHandle,
        item->value[NUM_0].i32);
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

int32_t SetListDirection(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();

    if (!item && item->size != NUM_1) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

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

int32_t SetListSticky(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();

    if (!item && item->size != NUM_1) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

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

int32_t SetListSpace(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();

    if (!item && item->size != NUM_1) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    fullImpl->getNodeModifiers()->getListModifier()->setListSpace(node->uiNodeHandle, item->value[NUM_0].f32);
    return ERROR_CODE_NO_ERROR;
}

void ResetListSpace(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getListModifier()->resetListSpace(node->uiNodeHandle);
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
int32_t SetToggleSelectedColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getToggleModifier()->setToggleSelectedColor(
        node->uiNodeHandle, item->value[0].u32);
    return ERROR_CODE_NO_ERROR;
}

void ResetToggleSelectedColor(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getToggleModifier()->resetToggleSelectedColor(
        node->uiNodeHandle);
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

void ResetToggleSwitchPointColor(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getToggleModifier()->resetToggleSwitchPointColor(
        node->uiNodeHandle);
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
    auto fullImpl = GetFullImpl();

    if (!item && item->size != NUM_1) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    fullImpl->getNodeModifiers()->getLoadingProgressModifier()->setEnableLoading(
        node->uiNodeHandle, item->value[NUM_0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetLoadingProgressEnableLoading(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getLoadingProgressModifier()->resetEnableLoading(node->uiNodeHandle);
}

void SetSwiperLoop(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    int isLoop = StringToBoolInt(value, 1);
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperLoop(node->uiNodeHandle, static_cast<bool>(isLoop));
}

void SetSwiperAutoPlay(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    int isAutoplay = StringToBoolInt(value, 0);
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperAutoPlay(
        node->uiNodeHandle, static_cast<bool>(isAutoplay));
}

void SetSwiperShowIndicator(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::string indicatorStr(value);
    std::vector<std::string> IndicatorProps = { "boolean", "true" };
    IndicatorProps[NUM_1] = std::to_string(StringToBoolInt(indicatorStr.c_str(), 1));
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
}

void SetSwiperInterval(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::string intervalStr(value);
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperInterval(
        node->uiNodeHandle, StringUtils::StringToInt(intervalStr));
}

void SetSwiperVertical(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    int isVertical = StringToBoolInt(value, 0);
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperVertical(
        node->uiNodeHandle, static_cast<bool>(isVertical));
}

void SetSwiperDuration(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::string durationStr(value);
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperDuration(
        node->uiNodeHandle, StringUtils::StringToInt(durationStr));
}

void SetSwiperCurve(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::string curveStr(value);
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperCurve(node->uiNodeHandle, curveStr.c_str());
}

void SetSwiperItemSpace(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperItemSpace(
        node->uiNodeHandle, StringToFloat(value, 0.0f), 1);
}

void SetSwiperIndex(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::string indexStr(value);
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperIndex(
        node->uiNodeHandle, StringUtils::StringToInt(indexStr));
}

void SetSwiperDisplayCount(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::string displayCountStr(value);
    std::string type = "number";
    if (StringUtils::IsNumber(displayCountStr)) {
        type = "number";
    } else if (std::strcmp(displayCountStr.c_str(), "auto") == 0) {
        type = "string";
    } else {
        type = "undefined";
    }
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperDisplayCount(
        node->uiNodeHandle, displayCountStr.c_str(), type.c_str());
}

void SetSwiperDisableSwipe(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    int isDisable = StringToBoolInt(value, 0);
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperDisableSwipe(
        node->uiNodeHandle, static_cast<bool>(isDisable));
}

void SetSwiperShowDisplayArrow(ArkUI_NodeHandle node, const char* value)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    double defaultBackgroundColor = StringToColorInt("#00000000", 0);
    double defaultArrowColor = StringToColorInt("#FF182431", 0);
    double displayArrow[ALLOW_SIZE_8] = { 1, 0, 0, DEFAULT_SIZE_24, defaultBackgroundColor, DEFAULT_SIZE_18,
        defaultArrowColor, 0 };
    std::string displayArrowStr(value);
    if (std::strcmp(displayArrowStr.c_str(), "showOnHover")) {
        displayArrow[NUM_0] = DISPLAY_ARROW_TRUE;
        displayArrow[NUM_7] = DISPLAY_ARROW_TRUE;
    } else {
        displayArrow[NUM_0] = StringToBoolInt(displayArrowStr.c_str(), 0);
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
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperIndicator(node->uiNodeHandle, result.c_str());
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

int32_t SetTextFontFamily(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
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

void ResetTextFontFamily(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT_INPUT) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputFontFamily(
            node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_TEXT) {
        fullImpl->getNodeModifiers()->getTextModifier()->resetTextFontFamily(
            node->uiNodeHandle);
    }
}

int32_t SetTextCopyOption(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT) {
        fullImpl->getNodeModifiers()->getTextModifier()->setTextCopyOption(
            node->uiNodeHandle, item->value[0].i32);
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetTextCopyOption(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT) {
        fullImpl->getNodeModifiers()->getTextModifier()->resetTextCopyOption(
            node->uiNodeHandle);
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

int32_t SetListItemGroupHeader(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();

    if (!item && !item->object) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    auto headerNodeHandle = reinterpret_cast<ArkUI_NodeHandle>(item->object);
    fullImpl->getNodeModifiers()->getListItemGroupModifier()->listItemGroupSetHeader(node->uiNodeHandle,
        headerNodeHandle->uiNodeHandle);
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
    auto fullImpl = GetFullImpl();

    if (!item && !item->object) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    auto footerNodeHandle = reinterpret_cast<ArkUI_NodeHandle>(item->object);
    fullImpl->getNodeModifiers()->getListItemGroupModifier()->listItemGroupSetFooter(node->uiNodeHandle,
        footerNodeHandle->uiNodeHandle);
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
    auto fullImpl = GetFullImpl();

    if (!item && item->size != NUM_4) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    auto color = item->value[NUM_0].u32;
    ArkUI_Float32 values[NUM_3] = { item->value[NUM_0].f32, item->value[NUM_1].f32, item->value[NUM_2].f32 };
    ArkUI_Int32 units[NUM_3] = { UNIT_VP, UNIT_VP, UNIT_VP };

    fullImpl->getNodeModifiers()->getListItemGroupModifier()->listItemGroupSetDivider(node->uiNodeHandle,
        color, values, units, NUM_3);
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

int32_t SetDatePickerLunar(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();

    if (!item && item->size != NUM_1) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }
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

int32_t SetDatePickerStart(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();

    if (!item && !item->string) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

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

int32_t SetDatePickerEnd(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();

    if (!item && !item->string) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

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

int32_t SetDatePickerSelected(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();

    if (!item && !item->string) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

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

    fullImpl->getNodeModifiers()->getDatePickerModifier()->setDisappearTextStyle(node->uiNodeHandle,
        fontInfo.c_str(), color, style);
}

int32_t SetDatePickerDisappearTextStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();

    if (!item && !item->string) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    std::vector<std::string> params;
    StringUtils::StringSplitter(item->string, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() != NUM_5) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    ArkUI_Uint32 color = StringToColorInt(params[NUM_0].c_str());
    auto style = StringToEnumInt(params[NUM_4].c_str(), FONT_STYLES, NUM_0);
    std::string fontInfo = params[NUM_1] + '|' + params[NUM_2] + '|' + params[NUM_3];

    fullImpl->getNodeModifiers()->getDatePickerModifier()->setDisappearTextStyle(node->uiNodeHandle,
        fontInfo.c_str(), color, style);

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

    fullImpl->getNodeModifiers()->getDatePickerModifier()->setDatePickerTextStyle(node->uiNodeHandle,
        fontInfo.c_str(), color, style);
}

int32_t SetDatePickerTextStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();

    if (!item && !item->string) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    std::vector<std::string> params;
    StringUtils::StringSplitter(item->string, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() != NUM_5) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    ArkUI_Uint32 color = StringToColorInt(params[NUM_0].c_str());
    auto style = StringToEnumInt(params[NUM_4].c_str(), FONT_STYLES, NUM_0);
    std::string fontInfo = params[NUM_1] + '|' + params[NUM_2] + '|' + params[NUM_3];

    fullImpl->getNodeModifiers()->getDatePickerModifier()->setDatePickerTextStyle(node->uiNodeHandle,
        fontInfo.c_str(), color, style);

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

    fullImpl->getNodeModifiers()->getDatePickerModifier()->setSelectedTextStyle(node->uiNodeHandle,
        fontInfo.c_str(), color, style);
}

int32_t SetDatePickerSelectedTextStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();

    if (!item && !item->string) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    std::vector<std::string> params;
    StringUtils::StringSplitter(item->string, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() != NUM_5) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    ArkUI_Uint32 color = StringToColorInt(params[NUM_0].c_str());
    auto style = StringToEnumInt(params[NUM_4].c_str(), FONT_STYLES, NUM_0);
    std::string fontInfo = params[NUM_1] + '|' + params[NUM_2] + '|' + params[NUM_3];

    fullImpl->getNodeModifiers()->getDatePickerModifier()->setSelectedTextStyle(node->uiNodeHandle,
        fontInfo.c_str(), color, style);

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

    fullImpl->getNodeModifiers()->getTimepickerModifier()->setTimepickerSelectedTextStyle(node->uiNodeHandle,
        color, fontInfo.c_str(), style);
}

int32_t SetTimePickerSelected(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();

    if (!item && !item->string) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

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

    fullImpl->getNodeModifiers()->getTimepickerModifier()->SetTimepickerUseMilitaryTime(node->uiNodeHandle,
        StringToBoolInt(value));
}

int32_t SetTimePickerUseMilitaryTime(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();

    if (!item && item->size != NUM_1) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    fullImpl->getNodeModifiers()->getTimepickerModifier()->SetTimepickerUseMilitaryTime(node->uiNodeHandle,
        item->value[NUM_0].i32);

    return ERROR_CODE_NO_ERROR;
}

void ResetTimePickerUseMilitaryTime(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getTimepickerModifier()->ResetTimepickerUseMilitaryTime(node->uiNodeHandle);
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

    fullImpl->getNodeModifiers()->getTimepickerModifier()->setTimepickerDisappearTextStyle(node->uiNodeHandle,
        color, fontInfo.c_str(), style);
}

int32_t SetTimePickerDisappearTextStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();

    if (!item && !item->string) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    std::vector<std::string> params;
    StringUtils::StringSplitter(item->string, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() != NUM_5) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    ArkUI_Uint32 color = StringToColorInt(params[NUM_0].c_str());
    auto style = StringToEnumInt(params[NUM_4].c_str(), FONT_STYLES, NUM_0);
    std::string fontInfo = params[NUM_1] + '|' + params[NUM_2] + '|' + params[NUM_3];

    fullImpl->getNodeModifiers()->getTimepickerModifier()->setTimepickerDisappearTextStyle(node->uiNodeHandle,
        color, fontInfo.c_str(), style);

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

    fullImpl->getNodeModifiers()->getTimepickerModifier()->setTimepickerTextStyle(node->uiNodeHandle,
        color, fontInfo.c_str(), style);
}

int32_t SetTimePickerTextStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();

    if (!item && !item->string) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    std::vector<std::string> params;
    StringUtils::StringSplitter(item->string, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() != NUM_5) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    ArkUI_Uint32 color = StringToColorInt(params[NUM_0].c_str());
    auto style = StringToEnumInt(params[NUM_4].c_str(), FONT_STYLES, NUM_0);
    std::string fontInfo = params[NUM_1] + '|' + params[NUM_2] + '|' + params[NUM_3];

    fullImpl->getNodeModifiers()->getTimepickerModifier()->setTimepickerTextStyle(node->uiNodeHandle,
        color, fontInfo.c_str(), style);

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

    fullImpl->getNodeModifiers()->getTimepickerModifier()->setTimepickerSelectedTextStyle(node->uiNodeHandle,
        color, fontInfo.c_str(), style);
}

int32_t SetTimePickerSelectedTextStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();

    if (!item && !item->string) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    std::vector<std::string> params;
    StringUtils::StringSplitter(item->string, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() != NUM_5) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    ArkUI_Uint32 color = StringToColorInt(params[NUM_0].c_str());
    auto style = StringToEnumInt(params[NUM_4].c_str(), FONT_STYLES, NUM_0);
    std::string fontInfo = params[NUM_1] + '|' + params[NUM_2] + '|' + params[NUM_3];

    fullImpl->getNodeModifiers()->getTimepickerModifier()->setTimepickerSelectedTextStyle(node->uiNodeHandle,
        color, fontInfo.c_str(), style);

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

    fullImpl->getNodeModifiers()->getTextPickerModifier()->setTextPickerDisappearTextStyle(node->uiNodeHandle,
        color, fontInfo.c_str(), style);
}

int32_t SetTextPickerDisappearTextStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();

    if (!item && !item->string) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    std::vector<std::string> params;
    StringUtils::StringSplitter(item->string, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() != NUM_5) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    ArkUI_Uint32 color = StringToColorInt(params[NUM_0].c_str());
    auto style = StringToEnumInt(params[NUM_4].c_str(), FONT_STYLES, NUM_0);
    std::string fontInfo = params[NUM_1] + '|' + params[NUM_2] + '|' + params[NUM_3];

    fullImpl->getNodeModifiers()->getTextPickerModifier()->setTextPickerDisappearTextStyle(node->uiNodeHandle,
        color, fontInfo.c_str(), style);

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

    fullImpl->getNodeModifiers()->getTextPickerModifier()->setTextPickerTextStyle(node->uiNodeHandle,
        color, fontInfo.c_str(), style);
}

int32_t SetTextPickerTextStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();

    if (!item && !item->string) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    std::vector<std::string> params;
    StringUtils::StringSplitter(item->string, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() != NUM_5) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    ArkUI_Uint32 color = StringToColorInt(params[NUM_0].c_str());
    auto style = StringToEnumInt(params[NUM_4].c_str(), FONT_STYLES, NUM_0);
    std::string fontInfo = params[NUM_1] + '|' + params[NUM_2] + '|' + params[NUM_3];

    fullImpl->getNodeModifiers()->getTextPickerModifier()->setTextPickerTextStyle(node->uiNodeHandle,
        color, fontInfo.c_str(), style);

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

    fullImpl->getNodeModifiers()->getTextPickerModifier()->setTextPickerSelectedTextStyle(node->uiNodeHandle,
        color, fontInfo.c_str(), style);
}

int32_t SetTextPickerSelectedTextStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();

    if (!item && !item->string) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    std::vector<std::string> params;
    StringUtils::StringSplitter(item->string, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() != NUM_5) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    ArkUI_Uint32 color = StringToColorInt(params[NUM_0].c_str());
    auto style = StringToEnumInt(params[NUM_4].c_str(), FONT_STYLES, NUM_0);
    std::string fontInfo = params[NUM_1] + '|' + params[NUM_2] + '|' + params[NUM_3];

    fullImpl->getNodeModifiers()->getTextPickerModifier()->setTextPickerSelectedTextStyle(node->uiNodeHandle,
        color, fontInfo.c_str(), style);

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

int32_t SetTextPickerSelectedIndex(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();

    if (!item) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "item is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

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

    fullImpl->getNodeModifiers()->getTextPickerModifier()->resetTextPickerSelected(node->uiNodeHandle);
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
        SetLinearGradient, SetAlign, SetOpacity, SetBorderWidth, SetBorderRadius, SetBorderColor, SetBorderStyle,
        SetZIndex, SetVisibility, SetClip, SetTransform, SetHitTestBehavior, SetPosition, SetShadow,
        SetBackgroundImageSize, nullptr, SetBackgroundBlurStyle, SetTransitionCenter, SetOpacityTransition,
        SetRotateTransition, SetScaleTransition, SetTranslateTransition, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, SetBackgroundImagePosition, SetOffset, SetMarkAnchor, SetAlignRules };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "common node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    setters[subTypeId](node, value);
}

int32_t SetCommonAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* value)
{
    using Setter = int32_t(ArkUI_NodeHandle node, const ArkUI_AttributeItem* value);
    static Setter* setters[] = {
        SetWidth, SetHeight, SetBackgroundColor, nullptr, nullptr, nullptr, nullptr, SetMargin,
        SetTranslate, SetScale, SetRotate, SetBrightness, SetSaturate, SetBlur, SetLinearGradient,
        SetAlign, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, SetFocusable, SetAccessibilityGroup, SetAccessibilityText,
        SetAccessibilityLevel, SetAccessibilityDescription, SetDefaultFocus, SetResponseRegion, SetOverlay,
        SetBackgroundImagePosition,
    };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "common node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, value);
}

void ResetCommonAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Resetter = void(ArkUI_NodeHandle node);
    static Resetter* resetters[] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, ResetMargin, ResetTranslate, ResetScale, ResetRotate, ResetBrightness, ResetSaturate, ResetBlur,
        ResetLinearGradient, ResetAlign, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        ResetBackgroundImageSize,
        ResetBackgroundBlurStyle, ResetTransitionCenter, ResetOpacityTransition, ResetRotateTransition,
        ResetScaleTransition, ResetTranslateTransition,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        ResetBackgroundImagePosition, ResetOffset, ResetMarkAnchor, ResetAlignRules };
    if (subTypeId >= sizeof(resetters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "common node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    resetters[subTypeId](node);
}

void SetTextAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const char* value)
{
    static Setter* setters[] = { SetTextContent, SetFontColor, SetFontSize, SetFontStyle, SetFontWeight, SetLineHeight,
        SetDecoration, SetTextCase, SetLetterSpacing, SetMaxLines, SetTextAlign, SetTextOverflow, nullptr,
        nullptr, SetTextBaselineOffset, SetTextTextShadow, SetTextIndent };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "text node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    setters[subTypeId](node, value);
}

int32_t SetTextAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* value)
{
    using Setter = int32_t(ArkUI_NodeHandle node, const ArkUI_AttributeItem* value);
    static Setter* setters[] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, SetTextFontFamily,
        SetTextCopyOption, nullptr, nullptr };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "common node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, value);
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
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "stack node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    setters[subTypeId](node, value);
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

void SetScrollAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const char* value)
{
    static Setter* setters[] = { SetScrollScrollBar, SetScrollScrollBarWidth, SetScrollScrollBarColor,
        SetScrollScrollable, SetScrollEdgeEffect, SetScrollEnableScrollInteraction, SetScrollFriction,
        SetScrollScrollSnap, nullptr, nullptr, nullptr, SetScrollEnablePaging };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "scroll node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ;
    }
    setters[subTypeId](node, value);
}

int32_t SetScrollAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    using Setter = int32_t(ArkUI_NodeHandle node, const ArkUI_AttributeItem* value);
    static Setter* setters[] = {
        SetScrollScrollBar, SetScrollScrollBarWidth, SetScrollScrollBarColor,
        SetScrollScrollable, SetScrollEdgeEffect, SetScrollEnableScrollInteraction, SetScrollFriction,
        SetScrollScrollSnap, SetScrollNestedScroll, SetScrollTo, SetScrollEdge, SetScrollEnablePaging
    };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "scroll node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

void ResetScrollAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Resetter = void(ArkUI_NodeHandle node);
    static Resetter* resetters[] = {
        ResetScrollScrollBar, ResetScrollScrollBarWidth, ResetScrollScrollBarColor,
        ResetScrollScrollable, ResetScrollEdgeEffect, ResetScrollEnableScrollInteraction, ResetScrollFriction,
        ResetScrollScrollSnap, nullptr, nullptr, nullptr, ResetScrollEnablePaging
    };
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

void SetSwiperAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const char* value)
{
    static Setter* setters[] = { SetSwiperLoop, SetSwiperAutoPlay, SetSwiperShowIndicator, SetSwiperInterval,
        SetSwiperVertical, SetSwiperDuration, SetSwiperCurve, SetSwiperItemSpace, SetSwiperIndex, SetSwiperDisplayCount,
        SetSwiperDisableSwipe, SetSwiperShowDisplayArrow };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "textinput node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    setters[subTypeId](node, value);
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

int32_t SetDatePickerAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    using Setter = int32_t(ArkUI_NodeHandle node, const ArkUI_AttributeItem* value);
    static Setter* setters[] = {
        SetDatePickerLunar, SetDatePickerStart, SetDatePickerEnd, SetDatePickerSelected,
        SetDatePickerDisappearTextStyle, SetDatePickerTextStyle, SetDatePickerSelectedTextStyle
    };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "datepicker node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

void ResetDatePickerAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Resetter = void(ArkUI_NodeHandle node);
    static Resetter* resetters[] = {
        ResetDatePickerLunar, ResetDatePickerStart, ResetDatePickerEnd, ResetDatePickerSelected,
        ResetDatePickerDisappearTextStyle, ResetDatePickerTextStyle, ResetDatePickerSelectedTextStyle
    };
    if (subTypeId >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "datepicker node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    return resetters[subTypeId](node);
}

void SetTimePickerAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const char* value)
{
    static Setter* setters[] = {
        SetTimePickerSelected, SetTimePickerUseMilitaryTime, SetTimePickerDisappearTextStyle, SetTimePickerTextStyle,
        SetTimePickerSelectedTextStyle
    };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "timepicker node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    setters[subTypeId](node, value);
}

int32_t SetTimePickerAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    using Setter = int32_t(ArkUI_NodeHandle node, const ArkUI_AttributeItem* value);
    static Setter* setters[] = {
        SetTimePickerSelected, SetTimePickerUseMilitaryTime, SetTimePickerDisappearTextStyle, SetTimePickerTextStyle,
        SetTimePickerSelectedTextStyle
    };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "timepicker node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

void ResetTimePickerAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Resetter = void(ArkUI_NodeHandle node);
    static Resetter* resetters[] = {
        ResetTimePickerSelected, ResetTimePickerUseMilitaryTime, ResetTimePickerDisappearTextStyle,
        ResetTimePickerTextStyle, ResetTimePickerSelectedTextStyle
    };
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

void ResetTextAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = { ResetTextContent, nullptr, nullptr, nullptr, nullptr, ResetLineHeight,
        ResetDecoration, ResetTextCase, ResetLetterSpacing, ResetMaxLines, ResetTextAlign, ResetTextOverflow, nullptr,
        ResetTextFontFamily, ResetTextCopyOption, nullptr, nullptr };
    if (subTypeId >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "text node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    resetters[subTypeId](node);
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

void SetScrollAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = { nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr,
        nullptr, ResetScrollNestedScroll, ResetScrollTo, ResetScrollEdge, nullptr };
    if (subTypeId >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "scroll node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    resetters[subTypeId](node);
}
int32_t SetTextPickerAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    using Setter = int32_t(ArkUI_NodeHandle node, const ArkUI_AttributeItem* value);
    static Setter* setters[] = {
        SetTextPickerDisappearTextStyle, SetTextPickerTextStyle, SetTextPickerSelectedTextStyle,
        SetTextPickerSelectedIndex
    };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "textpicker node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

void ResetTextPickerAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    using Resetter = void(ArkUI_NodeHandle node);
    static Resetter* resetters[] = {
        ResetTextPickerDisappearTextStyle, ResetTextPickerTextStyle, ResetTextPickerSelectedTextStyle,
        ResetTextPickerSelectedIndex
    };
    if (subTypeId >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "timepicker node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    return resetters[subTypeId](node);
}

} // namespace

void SetNodeAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType type, const char* value)
{
    using AttributeSetterClass = void(ArkUI_NodeHandle node, int32_t subTypeId, const char* value);
    static AttributeSetterClass* setterClasses[] = { SetCommonAttribute, SetTextAttribute, SetSpanAttribute,
        SetImageSpanAttribute, SetImageAttribute, nullptr, SetLoadingProgressAttribute,
        SetTextInputAttribute, SetStackAttribute, SetScrollAttribute, SetListAttribute, SetSwiperAttribute,
        SetTextAreaAttribute, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        SetXComponentAttribute, SetListItemGroupAttribute, SetDatePickerAttribute, SetTimePickerAttribute,
        SetTextPickerAttribute };
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
    static AttributeSetterClass* setterClasses[] = {
        SetCommonAttribute, SetTextAttribute, nullptr, nullptr, nullptr,
        SetToggleAttribute, SetLoadingProgressAttribute, nullptr, SetStackAttribute, SetScrollAttribute,
        SetListAttribute, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, SetListItemGroupAttribute, SetDatePickerAttribute, SetTimePickerAttribute,
        SetTextPickerAttribute,
    };
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
    static AttributeGetterClass* getterClasses[] = {
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        GetLoadingProgressAttribute,
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
        nullptr,
        nullptr,
        nullptr
    };
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
    static AttributeResetterClass* resetterClasses[] = {
        ResetCommonAttribute,
        ResetTextAttribute,
        ResetSpanAttribute,
        ResetImageSpanAttribute,
        ResetImageAttribute,
        ResetToggleAttribute,
        ResetLoadingProgressAttribute,
        nullptr,
        ResetStackAttribute,
        ResetScrollAttribute,
        ResetListAttribute,
        nullptr,
        SetScrollAttribute,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        ResetListItemGroupAttribute,
        ResetDatePickerAttribute,
        ResetTimePickerAttribute,
        ResetTextPickerAttribute
    };
    int32_t subTypeClass = type / MAX_NODE_SCOPE_NUM;
    int32_t subTypeId = type % MAX_NODE_SCOPE_NUM;
    if (subTypeClass > sizeof(resetterClasses) / sizeof(AttributeResetterClass*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "node attribute: %{public}d NOT IMPLEMENT", type);
        return;
    }
    resetterClasses[subTypeClass](node, subTypeId);
}

} // namespace OHOS::Ace::NodeModel
