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

#include <cerrno>
#include <cstdint>
#include <cstdlib>
#include <map>
#include <regex>

#include "basic_node.h"
#include "node_model.h"

#include "base/log/log_wrapper.h"
#include "base/utils/string_utils.h"
#include "core/interfaces/native/node/node_api.h"
#include "core/components/common/properties/color.h"
namespace OHOS::Ace::NodeModel {
namespace {
const std::regex COLOR_WITH_MAGIC("#[0-9A-Fa-f]{8}");
const std::regex BRACKETS("\\(.*?\\)");
constexpr int DEFAULT_ANGLE = 180;
constexpr ArkUI_Float64 DEFAULT_Z_SCALE = 1.0;
constexpr int UNIT_VP = 1;
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
constexpr int32_t SCALE_CENTER_X_INDEX = 3;
constexpr int32_t SCALE_CENTER_Y_INDEX = 4;
constexpr int32_t ROTATE_CENTER_X_INDEX = 3;
constexpr int32_t ROTATE_CENTER_Y_INDEX = 4;
constexpr int32_t ROTATE_CENTER_Z_INDEX = 5;
constexpr int32_t ROTATE_PERSPECTIVE_INDEX = 6;
constexpr int32_t ROTATE_ANGLE_INDEX = 7;
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
const std::vector<std::string> BLUR_STY_ARRAY = { "no_material", "thin", "regular", "thick", "background_thin",
    "background_regular", "background_thick", "background_ultra_thick", "component_ultra_thin", "component_thin",
    "component_regular", "component_thick", "component_ultra_thick" };
const std::vector<std::string> COLOR_MODE_ARRAY = { "system", "light", "dark" };
const std::vector<std::string> ADAPTIVE_COLOR_ARRAY = { "default", "average" };
const std::vector<std::string> TEXT_ALIGN_ARRAY = { "left", "right", "center", "justify", "start", "end" };
const std::vector<std::string> TEXT_DECORATION_TYPE_ARRAY = { "none", "underline", "overline", "line_through",
    "inherit" };
const std::vector<std::string> TEXT_DECORATION_STYLE_ARRAY = { "solid", "double", "dotted", "dashed", "wavy", "initial",
    "inherit" };
const std::vector<std::string> FONT_STYLE_ARRAY = { "normal", "italic" };
const std::vector<std::string> FONT_OVERFLOW_ARRAY = { "none", "clip", "ellipsis", "marquee" };
const std::vector<std::string> IMAGE_FIT_ARRAY = { "fill", "contain", "cover", "fitwidth", "fitheight", "none",
    "scale_down", "top_left" };
const std::vector<std::string> IMAGE_INTERPOLATION_ARRAY = { "none", "low", "medium", "high" };
const std::vector<std::string> IMAGE_REPEAT_ARRAY = { "no_repeat", "repeat_x", "repeat_y", "repeat" };
const std::vector<std::string> TEXT_CASE_ARRAY = { "normal", "lowercase", "uppercase" };
const std::vector<std::string> IMAGE_SPAN_VERTICAL_ALIGN = { "top", "center", "bottom", "baseline", "none" };
typedef std::map<const std::string, ArkUI_Int32> AttrStringToIntMap;

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

void SetWidth(ArkUI_NodeHandle node, const char* value)
{
    auto* fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    // 1 for vp. check in DimensionUnit.
    fullImpl->getNodeModifiers()->getCommonModifier()->setWidth(
        node->uiNodeHandle, StringToFloat(value, 0.0f), 1, nullptr);
}

void SetHeight(ArkUI_NodeHandle node, const char* value)
{
    auto* fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setHeight(
        node->uiNodeHandle, StringToFloat(value, 0.0f), 1, nullptr);
}

void SetBackgroundColor(ArkUI_NodeHandle node, const char* value)
{
    auto* fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setBackgroundColor(
        node->uiNodeHandle, StringToColorInt(value, 0));
}

void SetBackgroundImage(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    std::vector<std::string> bgImageVector;
    StringUtils::StringSplitter(value, ' ', bgImageVector);
    std::vector<std::string> repeatVec = { "norepeat", "x", "y", "xy" };
    std::string repeat = bgImageVector.size() > 1 ? bgImageVector[1] : "";
    fullImpl->getNodeModifiers()->getCommonModifier()->setBackgroundImage(
        node->uiNodeHandle, bgImageVector[0].c_str(), nullptr, nullptr, StringToEnumInt(repeat.c_str(), repeatVec, 0));
}

void SetPadding(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    std::vector<std::string> paddingVal;
    StringUtils::StringSplitter(value, ' ', paddingVal);
    float padding[ALLOW_SIZE_4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    int units[ALLOW_SIZE_4] = { 1, 1, 1, 1 };
    int paddingSize = paddingVal.size();
    for (int i = 0; i < ALLOW_SIZE_4; i++) {
        if (paddingSize == 1) {
            padding[i] = StringToFloat(paddingVal[0].c_str(), 0.0f);
        } else if (i < paddingSize) {
            padding[i] = StringToFloat(paddingVal[i].c_str(), 0.0f);
        }
    }
    struct ArkUISizeType top = { padding[0], units[0] };
    struct ArkUISizeType right = { padding[1], units[1] };
    struct ArkUISizeType bottom = { padding[2], units[2] };
    struct ArkUISizeType left = { padding[3], units[3] };
    fullImpl->getNodeModifiers()->getCommonModifier()->setPadding(node->uiNodeHandle, &top, &right, &bottom, &left);
}

void SetKey(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setKey(node->uiNodeHandle, value);
}

void SetEnabled(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setEnabled(
        node->uiNodeHandle, static_cast<bool>(StringToBoolInt(value, 1)));
}

void SetMargin(ArkUI_NodeHandle node, const char* value)
{
    auto* fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
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
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }

    std::vector<std::string> valuesSrc;
    StringUtils::StringSplitter(value, ',', valuesSrc);
    auto size = valuesSrc.size();
    if (size <= 0) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "valuesSrc is empty");
        return;
    }
    ArkUI_Float64 values[size];
    ArkUI_Int32 units[size];
    for (int i = 0; i < size; ++i) {
        values[i] = StringUtils::StringToDouble(valuesSrc[i].c_str());
        units[i] = UNIT_VP;
    }

    fullImpl->getNodeModifiers()->getCommonModifier()->setTranslate(node->uiNodeHandle, values, units, size);
}

void SetScale(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
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
    ArkUI_Float64 values[size + NUM_1];
    for (int i = 0; i < size; ++i) {
        values[i] = StringUtils::StringToDouble(valuesSrc[i].c_str());
    }
    values[size] = DEFAULT_Z_SCALE;

    ArkUI_Int32 units[NUM_2] = { UNIT_VP, UNIT_VP };

    fullImpl->getNodeModifiers()->getCommonModifier()->setScale(node->uiNodeHandle, values,
        size + NUM_1, units, NUM_2);
}

void SetRotate(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    std::vector<std::string> valuesSrc;
    StringUtils::StringSplitter(value, ',', valuesSrc);
    auto size = valuesSrc.size();
    if (size <= 0) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "valuesSrc is empty");
        return;
    }
    ArkUI_Float64 values[size];
    for (int i = 0; i < size; ++i) {
        values[i] = StringUtils::StringToDouble(valuesSrc[i].c_str());
    }

    ArkUI_Int32 units[NUM_3] = { UNIT_VP, UNIT_VP, UNIT_VP };
    fullImpl->getNodeModifiers()->getCommonModifier()->setRotate(node->uiNodeHandle, values, size, units, NUM_3);
}

void SetBrightness(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }
    ArkUI_Float64 brightness = StringUtils::StringToDouble(value);
    fullImpl->getNodeModifiers()->getCommonModifier()->setBrightness(node->uiNodeHandle, brightness);
}

void SetSaturate(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }
    ArkUI_Float64 saturate = StringUtils::StringToDouble(value);
    fullImpl->getNodeModifiers()->getCommonModifier()->setSaturate(node->uiNodeHandle, saturate);
}

void SetBlur(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }
    ArkUI_Float64 blur = StringUtils::StringToDouble(value);
    fullImpl->getNodeModifiers()->getCommonModifier()->setBlur(node->uiNodeHandle, blur);
}

void SetLinearGradient(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
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
    ArkUI_Float64 colors[size];
    for (int i = 0, j = 0; i < colorsSrc.size() && j < size; i += NUM_2, j += NUM_3) {
        colors[j + NUM_0] = StringToColorInt(colorsSrc[i + NUM_0].c_str());
        colors[j + NUM_1] = true;
        colors[j + NUM_2] = StringUtils::StringToDouble(colorsSrc[i + NUM_1].c_str());
    }

    ArkUI_Float64 values[NUM_4] = { false, DEFAULT_ANGLE, NUM_3, false };
    if (params.size() > NUM_1) {
        values[NUM_0] = true;
        values[NUM_1] = StringUtils::StringToDouble(params[NUM_1].c_str());
    }

    AttrStringToIntMap paramsMap = {
        { "left", 0}, { "top", 1}, { "right", 2}, { "bottom", 3}, { "left-top", 4},
        { "left-bottom", 5}, { "right-top", 6}, { "right-bottom", 7}, { "none", 8},
    };

    if (params.size() > NUM_2) {
        values[NUM_2] = paramsMap.find(params[NUM_2]) != paramsMap.end() ? paramsMap[params[NUM_2]] : NUM_3;
    }
    values[NUM_3] = (params.size() > NUM_3) ? StringToBoolInt(params[NUM_3].c_str()) : false;

    fullImpl->getNodeModifiers()->getCommonModifier()->setLinearGradient(node->uiNodeHandle,
        values, NUM_4, colors, size);
}

void SetAlign(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    AttrStringToIntMap paramsMap = {
        { "top-start", 0},
        { "top", 1},
        { "top-end", 2},
        { "start", 3},
        { "center", 4},
        { "end", 5},
        { "bottom-start", 6},
        { "bottom", 7},
        { "bottom-end", 8}
    };

    auto attrVal = paramsMap.find(value) != paramsMap.end() ? paramsMap[value] : 0;
    fullImpl->getNodeModifiers()->getCommonModifier()->setAlign(node->uiNodeHandle, attrVal);
}

void SetOpacity(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setBackgroundColor(
        node->uiNodeHandle, StringToFloat(value, 0.0f));
}

void SetBorderWidth(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    std::string widths(value);
    double widthVals[ALLOW_SIZE_4] = { 1, 1, 1, 1 };
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
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    std::string radius(value);
    double radiusVals[ALLOW_SIZE_4] = { 1, 1, 1, 1 };
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
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    std::string colorStr(value);
    int colors[ALLOW_SIZE_4] = { 0, 0, 0, 0 };

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
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    std::string styleStr(value);
    std::vector<std::string> borderStyle = { "solid", "dashed", "dotted" };
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
            styles[i] = StringToEnumInt(styleProps[i].c_str(), borderStyle, 0);
        }
        fullImpl->getNodeModifiers()->getCommonModifier()->setBorderStyle(node->uiNodeHandle, styles, ALLOW_SIZE_4);
    } else {
        int styles[NUM_1] = { 0 };
        styles[NUM_0] = StringToEnumInt(styleStr.c_str(), borderStyle, 0);
        fullImpl->getNodeModifiers()->getCommonModifier()->setBorderStyle(node->uiNodeHandle, styles, ALLOW_SIZE_1);
    }
}

void SetZIndex(ArkUI_NodeHandle node, const char* value = "0")
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    std::string zIndex(value);
    fullImpl->getNodeModifiers()->getCommonModifier()->setZIndex(node->uiNodeHandle, StringUtils::StringToInt(zIndex));
}

void SetVisibility(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    std::vector<std::string> visibleStyle = { "visible", "hidden", "none" };
    fullImpl->getNodeModifiers()->getCommonModifier()->setVisibility(
        node->uiNodeHandle, StringToEnumInt(value, visibleStyle, 0));
}

void SetClip(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    std::string clipStr(value);
    StringUtils::TrimStr(clipStr);
    if (std::regex_search(clipStr, BRACKETS)) {
        std::size_t pos1 = clipStr.find_first_of('('); // 查找左括号的位置
        std::size_t pos2 = clipStr.find_first_of(')'); // 查找右括号的位置
        std::string shape = clipStr.substr(0, pos1);
        std::string content = clipStr.substr(pos1 + 1, pos2 - pos1 - 1);
        std::vector<std::string> attributeProps;
        StringUtils::StringSplitter(content.c_str(), ',', attributeProps);
        if (std::strcmp(shape.c_str(), "path") == 0) {
            double pathAttributes[NUM_2];
            for (int i = 0; i < NUM_2; ++i) {
                pathAttributes[i] = StringToFloat(attributeProps[i].c_str(), 0.0f);
            }
            std::string commands(attributeProps[NUM_2]);
            fullImpl->getNodeModifiers()->getCommonModifier()->setClipPath(
                node->uiNodeHandle, StringUtils::TrimStr(shape).c_str(), pathAttributes, commands.c_str());
        } else {
            double attributes[attributeProps.size()];
            for (int i = 0; i < attributeProps.size(); ++i) {
                attributes[i] = StringToFloat(attributeProps[i].c_str(), 0.0f);
            }
            fullImpl->getNodeModifiers()->getCommonModifier()->setClipShape(
                node->uiNodeHandle, StringUtils::TrimStr(shape).c_str(), attributes, attributeProps.size());
        }
    } else {
        int isClip = StringToBoolInt(clipStr.c_str(), 0);
        fullImpl->getNodeModifiers()->getCommonModifier()->setClip(node->uiNodeHandle, isClip);
    }
}

void SetTransform(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
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
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    std::vector<std::string> hitTestModeStyle = { "default", "block", "transparent" };
    fullImpl->getNodeModifiers()->getCommonModifier()->setHitTestBehavior(
        node->uiNodeHandle, StringToEnumInt(value, hitTestModeStyle, 0));
}

void SetPosition(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    std::string positionStr(value);
    float positions[ALLOW_SIZE_4] = { 0, 1, 0, 1 };
    std::vector<std::string> positionProps;
    StringUtils::StringSplitter(positionStr.c_str(), ' ', positionProps);
    positions[NUM_0] = StringToFloat(positionProps[NUM_0].c_str(), 0.0f);
    positions[NUM_2] = StringToFloat(positionProps[NUM_1].c_str(), 0.0f);
    fullImpl->getNodeModifiers()->getCommonModifier()->setPosition(
        node->uiNodeHandle, positions[NUM_0], positions[NUM_1], positions[NUM_2], positions[NUM_3]);
}

void SetShadow(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    std::string shadowStr(value);
    if (IsMultipleWords(shadowStr)) {
        std::string coloringStrategyValues = "invert average primary";
        double shadows[ALLOW_SIZE_7] = { 0, 2, 0, 0, 0, 0, 0 };
        int length;
        std::vector<std::string> ShadowProps;
        StringUtils::StringSplitter(shadowStr.c_str(), ' ', ShadowProps);
        length = ShadowProps.size();
        shadows[NUM_0] = StringToFloat(ShadowProps[NUM_0].c_str(), 0.0f); // radius
        shadows[NUM_1] = 2;                                               // 1: has ColorStrategy; 2: has Color
        if (coloringStrategyValues.find(ShadowProps[NUM_4]) != std::string::npos) {
            std::vector<std::string> shadowColoringStrategy = { "invert", "average", "primary" };
            shadows[NUM_1] = COLOR_STRATEGY_STYLE;
            shadows[NUM_5] = StringToEnumInt(value, shadowColoringStrategy, 0);
        } else {
            shadows[NUM_1] = COLOR_STYLE;
            shadows[NUM_5] = StringToColorInt(ShadowProps[NUM_4].c_str(), 0);
        }
        shadows[NUM_2] = StringToFloat(ShadowProps[NUM_1].c_str(), 0.0f); // OffsetX
        shadows[NUM_3] = StringToFloat(ShadowProps[NUM_2].c_str(), 0.0f); // OffsetY
        shadows[NUM_4] = 0;
        std::vector<std::string> shadowType = { "color", "blur" };
        shadows[NUM_4] = StringToEnumInt(ShadowProps[NUM_3].c_str(), shadowType, 0);
        shadows[NUM_6] = StringToBoolInt(ShadowProps[NUM_5].c_str(), 0);
        fullImpl->getNodeModifiers()->getCommonModifier()->setBackShadow(node->uiNodeHandle, shadows, ALLOW_SIZE_7);
    } else {
        double shadows[NUM_1] = { 0 };
        std::vector<std::string> shadowStyle = { "outer-default-xs", "outer-default-sm", "outer-default-md",
            "outer-default-lg", "outer-floating-sm", "outer-floating-md", "none" };
        shadows[NUM_0] = StringToEnumInt(value, shadowStyle, 0);
        fullImpl->getNodeModifiers()->getCommonModifier()->setBackShadow(node->uiNodeHandle, shadows, ALLOW_SIZE_1);
    }
}

void SetFocusable(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setFocusable(
        node->uiNodeHandle, static_cast<bool>(StringToBoolInt(value, 1)));
}

void SetAccessibilityGroup(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setAccessibilityGroup(
        node->uiNodeHandle, static_cast<bool>(StringToBoolInt(value, 0)));
}

void SetAccessibilityText(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setAccessibilityText(
        node->uiNodeHandle, value);
}

void SetAccessibilityLevel(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setAccessibilityLevel(
        node->uiNodeHandle, value);
}

void SetAccessibilityDescription(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setAccessibilityDescription(
        node->uiNodeHandle, value);
}

void SetDefaultFocus(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setDefaultFocus(
        node->uiNodeHandle, static_cast<bool>(StringToBoolInt(value, 0)));
}

// "{1 2 3 4},{1 2 3 4}"
void SetResponseRegion(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }

    std::vector<std::string> regionArray;
    StringUtils::StringSplitter(value, ',', regionArray);
    std::vector<double> valuesArray;
    std::vector<int> unitsArray;
    if (regionArray.size() == 1) {
        std::vector<std::string> regionVal;
        //取第一个值进行分解
        StringUtils::StringSplitter(regionArray[0], ' ', regionVal);
        for (int i = 0; i < regionVal.size(); i++) {
            valuesArray.push_back(StringToDouble(regionVal[i].c_str(), 0.0f));
                    //unit 1
            unitsArray.push_back(1);
        }
    } else if (regionArray.size() > 1) {
        for (const std::string& region : regionArray) {
            //判断第一个字符是否符合要求
            if (!region.empty() && region.size() > ALLOW_SIZE_2 &&
             region[0] == '{' && region.back() == '}') {
                std::string regionString = region.substr(1, region.length() - ALLOW_SIZE_2);
                std::vector<std::string> regionVal;
                StringUtils::StringSplitter(regionString, ' ', regionVal);
                for (int i = 0; i < ALLOW_SIZE_4; i++) {
                    valuesArray.push_back(StringToDouble(regionVal[i].c_str(), 0.0f));
                    //unit 1
                    unitsArray.push_back(1);
                }
            }
        }
    }
    double* firstValue = valuesArray.data();
    int* firstUnit = unitsArray.data();
    fullImpl->getNodeModifiers()->getCommonModifier()->setResponseRegion(
        node->uiNodeHandle, firstValue, firstUnit, valuesArray.size());
}

void SetOverlay(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }

    std::vector<std::string> valueVal;
    StringUtils::StringSplitter(value, ' ', valueVal);

    if (valueVal.size() < ALLOW_SIZE_4) {
        return;
    }

    double values[ALLOW_SIZE_10] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1, 1};
    std::vector<std::string> alignment = { "top-start", "top", "top-end",
         "start", "center", "end", "bottom-start", "bottom", "bottom-end" };
    //调用函数参数要求
    values[0] = 1;
    values[1] = StringToEnumInt(valueVal[1].c_str(), alignment, 0);
    //组装对应的参数
    if (StringToInt(valueVal[2].c_str(), 0) > 0) {
        values[2] = 1;
        values[3] = StringToDouble(valueVal[2].c_str(), 0.0);
        values[4] = 1;
    }
    //组装对应的参数
    if (StringToInt(valueVal[3].c_str(), 0) > 0) {
        values[5] = 1;
        values[6] = StringToDouble(valueVal[3].c_str(), 0.0);
        values[7] = 1;
    }

    fullImpl->getNodeModifiers()->getCommonModifier()->setOverlay(
        node->uiNodeHandle, valueVal[0].c_str(), values, ALLOW_SIZE_10);
}

// TextInput Arttributes functions
void SetFontColor(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
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
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
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
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    if (node->type == ARKUI_NODE_TEXT_INPUT) {
        struct ArkUILengthType fontSize = { nullptr, StringToFloat(value, 0.0f), 2 };
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
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
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
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
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
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputPlaceholderString(node->uiNodeHandle, value);
}

void SetTextInputText(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputTextString(node->uiNodeHandle, value);
}

void SetCaretColor(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputCaretColor(
        node->uiNodeHandle, StringToColorInt(value, 0));
}

void SetCaretStyle(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    struct ArkUILengthType width = { nullptr, StringToFloat(value, 0.0f), 1 };
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputCaretStyle(node->uiNodeHandle, &width);
}

void SetShowUnderline(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputShowUnderline(
        node->uiNodeHandle, StringToBoolInt(value, 0));
}

void SetMaxLength(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputMaxLength(
        node->uiNodeHandle, StringToInt(value, 0));
}

void SetEnterKeyType(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    std::vector<std::string> enterKeyType = { "begin", "none", "go", "search", "send", "next", "done", "previous",
        "newLine" };
    int defaultValue = 6;
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputEnterKeyType(
        node->uiNodeHandle, StringToEnumInt(value, enterKeyType, defaultValue));
}

void SetPlaceholderColor(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputPlaceholderColor(
        node->uiNodeHandle, StringToColorInt(value, 0));
}

void SetTextInputPlaceholderFont(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    std::vector<std::string> font;
    StringUtils::StringSplitter(value, ' ', font);
    for (int i = font.size(); i < ALLOW_SIZE_4; i++) {
        font.emplace_back("");
    }
    std::vector<std::string> style = { "normal", "italic" };
    struct ArkUILengthType size = { nullptr, StringToFloat(font[0].c_str(), 0.0f), 2 };
    std::string familyStr = font[3];
    int fontFamilyLength = familyStr.length();
    struct ArkUIPlaceholderFontType palceHolderFont = { &size, font[1].c_str(), nullptr, 0,
        StringToEnumInt(font[2].c_str(), style, 0) };
    if (fontFamilyLength) {
        std::vector<std::string> fontFamilies;

        StringUtils::StringSplitter(familyStr.c_str(), ',', fontFamilies);
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
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputEnableKeyboardOnFocus(
        node->uiNodeHandle, StringToBoolInt(value, 1));
}

void SetTextInputType(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }

    std::vector<std::string> inputType = { "normal", "multiline", "number", "phone-number", "date-time", "email", "url",
        "password", "number-password", "screen-lock-password", "user-name", "new-password", "number-decimal" };
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputType(
        node->uiNodeHandle, StringToEnumInt(value, inputType, 0));
}

void SetSelectedBackgroundColor(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputSelectedBackgroundColor(
        node->uiNodeHandle, StringToColorInt(value, 0));
}

void SetShowPasswordIcon(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputShowPasswordIcon(
        node->uiNodeHandle, StringToBoolInt(value, 1));
}

// Stack Arttribute functions
void SetAlignContent(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    AttrStringToIntMap paramsMap = {
        { "top-start", 0},
        { "top", 1},
        { "top-end", 2},
        { "start", 3},
        { "center", 4},
        { "end", 5},
        { "bottom-start", 6},
        { "bottom", 7},
        { "bottom-end", 8}
    };

    auto attrVal = paramsMap.find(value) != paramsMap.end() ? paramsMap[value] : 0;
    fullImpl->getNodeModifiers()->getStackModifier()->setAlignContent(node->uiNodeHandle, attrVal);
}

// Scroll Arttribute functions
void SetScrollFriction(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }

    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollFriction(node->uiNodeHandle, StringToFloat(value));
}

void SetScrollScrollSnap(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    std::vector<std::string> params;
    StringUtils::StringSplitter(value, ' ', params);
    if (params.size() != NUM_4) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return;
    }
    std::vector<std::string> paginationsSrc;
    StringUtils::StringSplitter(value, ',', paginationsSrc);
    auto size = paginationsSrc.size();
    if (paginationsSrc.empty()) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "paginationsSrc is empty");
        return;
    }
    ArkUI_Float64 paginations[size];
    ArkUI_Int32 paginationParams[NUM_4 + size];
    for (int i = 0; i < size; ++i) {
        paginations[i] = StringUtils::StringToDouble(paginationsSrc[i].c_str());
        paginationParams[i] = UNIT_VP;
    }

    paginationParams[size + NUM_0] = StringToBoolInt(params[NUM_0].c_str());
    paginationParams[size + NUM_1] = StringToBoolInt(params[NUM_2].c_str());
    paginationParams[size + NUM_2] = StringToBoolInt(params[NUM_3].c_str());
    paginationParams[size + NUM_3] = (size > 1) ? true : false;

    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollScrollSnap(node->uiNodeHandle, paginations,
        size, paginationParams, NUM_4 + size);
}

void SetScrollScrollBar(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    AttrStringToIntMap paramsMap = {
        { "off", 0},
        { "auto", 1},
        { "on", 2},
    };

    auto attrVal = paramsMap.find(value) != paramsMap.end() ? paramsMap[value] : 0;
    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollScrollBar(node->uiNodeHandle, attrVal);
}

void SetScrollScrollBarWidth(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }
    auto attrVal = StringUtils::StringToDouble(value);
    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollScrollBarWidth(node->uiNodeHandle, attrVal, UNIT_VP);
}

void SetScrollScrollBarColor(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    auto color = StringToColorInt(value, 0);
    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollScrollBarColor(node->uiNodeHandle, color);
}

void SetScrollScrollable(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    AttrStringToIntMap paramsMap = {
        { "vertical", 0},
        { "horizontal", 1},
        { "free", 2},
        { "none", 3},
    };

    auto attrVal = paramsMap.find(value) != paramsMap.end() ? paramsMap[value] : NUM_0;
    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollScrollable(node->uiNodeHandle, attrVal);
}

void SetScrollEdgeEffect(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
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

    AttrStringToIntMap paramsMap = {
        { "spring", 0},
        { "fade", 1},
        { "none", 2},
    };

    auto attrVal = paramsMap.find(params[NUM_0]) != paramsMap.end() ? paramsMap[params[NUM_0]] : NUM_0;
    alwaysEnabled = (size > NUM_1) ? StringToBoolInt(params[NUM_1].c_str()) : true;
    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollEdgeEffect(node->uiNodeHandle, attrVal, alwaysEnabled);
}

void SetScrollEnableScrollInteraction(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
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
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    std::vector<std::string> valueVal;
    StringUtils::StringSplitter(value, ' ', valueVal);

    std::vector<std::string> nestedScrollOptions = { "self-only", "self-first",
     "parent-first", "parallel" };
    //组装对应的参数
    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollNestedScroll(
        node->uiNodeHandle, StringToEnumInt(valueVal[0].c_str(), nestedScrollOptions, 0),
        StringToEnumInt(valueVal[1].c_str(), nestedScrollOptions, 0));
}

void SetScrollTo(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    std::vector<std::string> valueVal;
    StringUtils::StringSplitter(value, ' ', valueVal);
    if (valueVal.size() < ALLOW_SIZE_5) {
        return;
    }

    std::vector<std::string> curve = { "linear", "ease", "easeIn",
     "easeOut", "ease-in-out", "fast-out-slow-in", "linear-out-slow-in", "fast-out-linear-in",
     "extreme-deceleration", "sharp", "rhythm", "smooth", "friction" };
    //组装对应的参数
    double values[ALLOW_SIZE_7] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    values[0] = StringToDouble(valueVal[0].c_str(), 0.0);
    values[1] = 1;
    values[2] = StringToDouble(valueVal[1].c_str(), 0.0);
    values[3] = 1;
    values[4] = StringToDouble(valueVal[2].c_str(), 0.0);
    values[5] = StringToEnumInt(valueVal[3].c_str(), curve, 0);
    values[6] = StringToBoolInt(valueVal[4].c_str(), 0.0);
    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollTo(
        node->uiNodeHandle, values);
}

void SetScrollEdge(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    std::vector<std::string> edge = { "top", "center", "bottom",
     "baseline", "start", "middle", "end" };
    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollEdge(
        node->uiNodeHandle, StringToEnumInt(value, edge, 0));
}

// List Attributes functions
void SetListScrollBar(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    AttrStringToIntMap paramsMap = {
        { "off", 0},
        { "auto", 1},
        { "on", 2},
    };

    auto attrVal = paramsMap.find(value) != paramsMap.end() ? paramsMap[value] : 0;
    fullImpl->getNodeModifiers()->getListModifier()->setListScrollBar(node->uiNodeHandle, attrVal);
}

void SetListListDirection(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    AttrStringToIntMap paramsMap = {
        { "vertical", 0},
        { "horizontal", 1},
        { "free", 2},
        { "none", 3},
    };

    auto attrVal = paramsMap.find(value) != paramsMap.end() ? paramsMap[value] : 0;
    fullImpl->getNodeModifiers()->getListModifier()->setListDirection(node->uiNodeHandle, attrVal);
}

void SetListListSticky(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }

    if (!value) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is nullptr");
        return;
    }

    AttrStringToIntMap paramsMap = {
        { "none", 0},
        { "header", 1},
        { "footer", 2},
        { "both", 3}
    };

    auto attrVal = paramsMap.find(value) != paramsMap.end() ? paramsMap[value] : 0;

    fullImpl->getNodeModifiers()->getListModifier()->setSticky(node->uiNodeHandle, attrVal);
}

void SetListEnableScrollInteraction(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
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
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
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

    AttrStringToIntMap paramsMap = {
        { "spring", 0},
        { "fade", 1},
        { "none", 2},
    };

    auto attrVal = paramsMap.find(params[NUM_0]) != paramsMap.end() ? paramsMap[params[NUM_0]] : NUM_0;
    alwaysEnabled = (size > NUM_1) ? StringToBoolInt(params[NUM_1].c_str()) : true;
    fullImpl->getNodeModifiers()->getListModifier()->setListEdgeEffect(node->uiNodeHandle, attrVal, alwaysEnabled);
}

void SetSwiperLoop(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    int isLoop = StringToBoolInt(value, 1);
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperLoop(node->uiNodeHandle, static_cast<bool>(isLoop));
}

void SetSwiperAutoPlay(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    int isAutoplay = StringToBoolInt(value, 0);
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperAutoPlay(
        node->uiNodeHandle, static_cast<bool>(isAutoplay));
}

void SetSwiperShowIndicator(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
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
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    std::string intervalStr(value);
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperInterval(
        node->uiNodeHandle, StringUtils::StringToInt(intervalStr));
}

void SetSwiperVertical(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    int isVertical = StringToBoolInt(value, 0);
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperVertical(
        node->uiNodeHandle, static_cast<bool>(isVertical));
}

void SetSwiperDuration(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    std::string durationStr(value);
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperDuration(
        node->uiNodeHandle, StringUtils::StringToInt(durationStr));
}

void SetSwiperCurve(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    std::string curveStr(value);
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperCurve(node->uiNodeHandle, curveStr.c_str());
}

void SetSwiperItemSpace(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperItemSpace(
        node->uiNodeHandle, StringToFloat(value, 0.0f), 1);
}

void SetSwiperIndex(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    std::string indexStr(value);
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperInterval(
        node->uiNodeHandle, StringUtils::StringToInt(indexStr));
}

void SetSwiperDisplayCount(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
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
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    int isDisable = StringToBoolInt(value, 0);
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperDisableSwipe(
        node->uiNodeHandle, static_cast<bool>(isDisable));
}

void SetSwiperShowDisplayArrow(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
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
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getTextModifier()->setContent(node->uiNodeHandle, value);
}

void SetSpanContent(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getSpanModifier()->setContent(node->uiNodeHandle, value);
}

void SetBackgroundImageSize(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
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

void SetOpacityTransition(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setOpacityTransition(
        node->uiNodeHandle, StringToFloat(value, DEFAULT_OPACITY));
}

void SetRotateTransition(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    std::vector<std::string> rotateVector;
    StringUtils::StringSplitter(std::string(value), ' ', rotateVector);
    std::array<float, ARRAY_SIZE> rotateArray;
    for (size_t i = 0; i < rotateVector.size() && i < rotateArray.size(); i++) {
        rotateArray[i] = StringUtils::StringToFloat(rotateVector[i]);
    }
    CalcDimension centerX(0);
    if (ROTATE_CENTER_X_INDEX < rotateVector.size()) {
        StringUtils::StringToCalcDimensionNG(rotateVector[ROTATE_CENTER_X_INDEX], centerX, false, DimensionUnit::VP);
    }
    CalcDimension centerY(0);
    if (ROTATE_CENTER_Y_INDEX < rotateVector.size()) {
        StringUtils::StringToCalcDimensionNG(rotateVector[ROTATE_CENTER_Y_INDEX], centerY, false, DimensionUnit::VP);
    }
    CalcDimension centerZ(0);
    if (ROTATE_CENTER_Z_INDEX < rotateVector.size()) {
        StringUtils::StringToCalcDimensionNG(rotateVector[ROTATE_CENTER_Z_INDEX], centerZ, false, DimensionUnit::VP);
    }
    float perspective = 0.0f;
    if (ROTATE_PERSPECTIVE_INDEX < rotateVector.size()) {
        perspective = StringUtils::StringToFloat(rotateVector[ROTATE_PERSPECTIVE_INDEX]);
    }
    float angle = 0.0f;
    if (ROTATE_ANGLE_INDEX < rotateVector.size()) {
        angle = StringUtils::StringToFloat(rotateVector[ROTATE_ANGLE_INDEX]);
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setRotateTransition(node->uiNodeHandle, &rotateArray[0],
        ARRAY_SIZE, centerX.Value(), static_cast<int32_t>(centerX.Unit()), centerY.Value(),
        static_cast<int32_t>(centerY.Unit()), centerZ.Value(), static_cast<int32_t>(centerZ.Unit()), perspective,
        angle);
}

void SetScaleTransition(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    std::vector<std::string> scaleVector;
    StringUtils::StringSplitter(std::string(value), ' ', scaleVector);
    std::array<float, ARRAY_SIZE> scaleFloatArray;
    for (size_t i = 0; i < scaleVector.size() && i < scaleFloatArray.size(); i++) {
        scaleFloatArray[i] = StringUtils::StringToFloat(scaleVector[i]);
    }

    CalcDimension centerX(0);
    if (SCALE_CENTER_X_INDEX < scaleVector.size()) {
        StringUtils::StringToCalcDimensionNG(scaleVector[SCALE_CENTER_X_INDEX], centerX, false, DimensionUnit::VP);
    }
    CalcDimension centerY(0);
    if (SCALE_CENTER_Y_INDEX < scaleVector.size()) {
        StringUtils::StringToCalcDimensionNG(scaleVector[SCALE_CENTER_Y_INDEX], centerY, false, DimensionUnit::VP);
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setScaleTransition(node->uiNodeHandle, &scaleFloatArray[0],
        scaleFloatArray.size(), centerX.Value(), static_cast<int32_t>(centerX.Unit()), centerY.Value(),
        static_cast<int32_t>(centerY.Unit()));
}

void SetTranslateTransition(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
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
    fullImpl->getNodeModifiers()->getCommonModifier()->setTranslateTransition(node->uiNodeHandle, xDimension.Value(),
        static_cast<int32_t>(xDimension.Unit()), yDimension.Value(), static_cast<int32_t>(yDimension.Unit()),
        zDimension.Value(), static_cast<int32_t>(zDimension.Unit()));
}

void SetBackgroundBlurStyle(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
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
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
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
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
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
    switch (node->type) {
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->resetTextLineHeight(node->uiNodeHandle);
            break;
        default:
            break;
    }
}

void SetTextOverflow(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getTextModifier()->setTextTextOverflow(
        node->uiNodeHandle, StringToEnumInt(value, FONT_OVERFLOW_ARRAY, 0));
}

void SetFontFamily(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }

    std::vector<std::string> fontFamilies;
    StringUtils::StringSplitter(value, ',', fontFamilies);

    auto families = std::make_unique<char* []>(fontFamilies.size());
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
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    if (node->type == ARKUI_NODE_TEXT) {
        std::vector<std::string> option = { "none", "in-app", "local-device", "cross-device" };
        fullImpl->getNodeModifiers()->getTextModifier()->setTextCopyOption(
            node->uiNodeHandle, StringToEnumInt(value, option, 0));
    }
}

void SetDecoration(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
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
        default:
            break;
    }
}

void SetLetterSpacing(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    StringAndDouble letterSpacingValue = { 0.0, value };
    switch (node->type) {
        case ARKUI_NODE_SPAN:
            fullImpl->getNodeModifiers()->getSpanModifier()->setSpanLetterSpacing(
                node->uiNodeHandle, &letterSpacingValue);
            break;
        default:
            break;
    }
}

void SetTextCase(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    switch (node->type) {
        case ARKUI_NODE_SPAN:
            fullImpl->getNodeModifiers()->getSpanModifier()->setSpanTextCase(
                node->uiNodeHandle, StringToEnumInt(value, TEXT_CASE_ARRAY, 0));
            break;
        default:
            break;
    }
}

// image span
void SetImageSpanSrc(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getImageModifier()->setSrc(node->uiNodeHandle, value);
}

void SetVerticalAlign(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getImageSpanModifier()->setImageSpanVerticalAlign(
        node->uiNodeHandle, StringToEnumInt(value, IMAGE_SPAN_VERTICAL_ALIGN, 0));
}

// image
void SetImageSrc(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getImageModifier()->setSrc(node->uiNodeHandle, value);
}

void SetObjectFit(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
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
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getImageModifier()->setImageInterpolation(
        node->uiNodeHandle, StringToEnumInt(value, IMAGE_INTERPOLATION_ARRAY, 0));
}

void SetObjectRepeat(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getImageModifier()->setObjectRepeat(
        node->uiNodeHandle, StringToEnumInt(value, IMAGE_REPEAT_ARRAY, 0));
}

void SetColorFilter(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
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

using Setter = void(ArkUI_NodeHandle node, const char* value);
void SetCommonAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const char* value)
{
    static Setter* setters[] = { SetWidth, SetHeight, SetBackgroundColor, SetBackgroundImage, SetPadding, SetKey,
        SetEnabled, SetMargin, SetTranslate, SetScale, SetRotate, SetBrightness, SetSaturate, SetBlur,
        SetLinearGradient, SetAlign, SetOpacity, SetBorderWidth, SetBorderRadius, SetBorderColor, SetBorderStyle,
        SetZIndex, SetVisibility, SetClip, SetTransform, SetHitTestBehavior, SetPosition, SetShadow,
        SetBackgroundImageSize, SetBackgroundBlurStyle, SetOpacityTransition, SetRotateTransition, SetScaleTransition,
        SetTranslateTransition,
        SetFocusable, SetAccessibilityGroup, SetAccessibilityText,
        SetAccessibilityLevel, SetAccessibilityDescription, SetDefaultFocus,
        SetResponseRegion, SetOverlay };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "common node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    setters[subTypeId](node, value);
}

void SetTextAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const char* value)
{
    static Setter* setters[] = { SetTextContent, SetFontColor, SetFontSize, SetFontStyle, SetFontWeight, SetLineHeight,
        SetDecoration, SetTextCase, SetLetterSpacing, SetMaxLines, SetTextAlign, SetTextOverflow,
        SetFontFamily, SetCopyOption };
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
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "text node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    setters[subTypeId](node, value);
}

void SetImageSpanAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const char* value)
{
    static Setter* setters[] = { SetImageSpanSrc, SetVerticalAlign };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "common node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    setters[subTypeId](node, value);
}

void SetImageAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const char* value)
{
    static Setter* setters[] = { SetImageSrc, SetObjectFit, SetInterpolation, SetObjectRepeat, SetColorFilter };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "common node attribute: %{public}d NOT IMPLEMENT", subTypeId);
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

void SetScrollAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const char* value)
{
    static Setter* setters[] = { SetScrollScrollBar, SetScrollScrollBarWidth, SetScrollScrollBarColor,
        SetScrollScrollable, SetScrollEdgeEffect, SetScrollEnableScrollInteraction, SetScrollFriction,
        SetScrollScrollSnap, SetScrollNestedScroll, SetScrollTo, SetScrollEdge };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "scroll node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    setters[subTypeId](node, value);
}

void SetListAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const char* value)
{
    static Setter* setters[] = {
        SetListScrollBar, SetListListDirection, SetListListSticky, SetListEdgeEffect,
        SetListEnableScrollInteraction
    };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "list node attribute: %{public}d NOT IMPLEMENT", subTypeId);
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

} // namespace

void SetNodeAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType type, const char* value)
{
    using AttributeSetterClass = void(ArkUI_NodeHandle node, int32_t subTypeId, const char* value);
    static AttributeSetterClass* setterClasses[] = { SetCommonAttribute, SetTextAttribute, SetSpanAttribute,
        SetImageSpanAttribute, SetImageAttribute, nullptr, nullptr, SetTextInputAttribute, SetStackAttribute,
        SetScrollAttribute, SetListAttribute, SetSwiperAttribute };
    int32_t subTypeClass = type / MAX_NODE_SCOPE_NUM;
    int32_t subTypeId = type % MAX_NODE_SCOPE_NUM;
    if (subTypeClass > sizeof(setterClasses) / sizeof(AttributeSetterClass*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "node attribute: %{public}d NOT IMPLEMENT", type);
        return;
    }
    setterClasses[subTypeClass](node, subTypeId, value);
}

const char* GetNodeAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType type)
{
    TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "the GetNodeAttribute  not impl");
    return "";
}

void ResetNodeAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType type)
{
    TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "the reset attribute not impl: %{public}d", type);
}

} // namespace OHOS::Ace::NodeModel
