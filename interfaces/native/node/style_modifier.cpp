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
#include "node/basic_types.h"
#include "node_model.h"

#include "base/log/log_wrapper.h"
#include "base/utils/string_utils.h"
#include "core/interfaces/native/node/node_api.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NodeModel {
namespace {
const std::regex COLOR_WITH_MAGIC("#[0-9A-Fa-f]{8}");
const int ALLOW_SIZE_4(4);
constexpr int UNIT_VP = 1;
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;

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

std::vector<std::string> StringSplit(const std::string& str, const std::string& delimiter)
{
    std::vector<std::string> result;

    size_t start = 0;
    size_t end = str.find(delimiter);
    while (end != std::string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }
    result.push_back(str.substr(start, end - start));

    return result;
}

int StringToEnumInt(const char* value, const std::vector<std::string>& vec, int defaultValue)
{
    std::string input(value);
    StringUtils::TransformStrCase(input, StringUtils::TEXT_CASE_UPPERCASE);
    auto it = std::find_if(vec.begin(), vec.end(), [&input](const std::string& str) {
        std::string enumStr = str;
        StringUtils::TransformStrCase(enumStr, StringUtils::TEXT_CASE_UPPERCASE);
        return str == input;
    });
    if (it != vec.end()) {
        return std::distance(vec.begin(), it);
    }
    return defaultValue;
}

// Common Arttributes functions
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
    std::vector<std::string> repeatVec = {"NOREPEAT", "X", "Y", "XY"};
    std::string repeat = bgImageVector.size() > 1 ? bgImageVector[1] : "";
    fullImpl->getNodeModifiers()->getCommonModifier()->setBackgroundImage(node->uiNodeHandle, bgImageVector[0].c_str(),
        nullptr, nullptr, StringToEnumInt(repeat.c_str(), repeatVec, 0));
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
    float padding[ALLOW_SIZE_4] = {0.0f, 0.0f, 0.0f, 0.0f};
    int units[ALLOW_SIZE_4] = {1, 1, 1, 1};
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
    std::vector<std::string> params = StringSplit(value, " ");
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

    std::vector<std::string> valuesSrc = StringSplit(value, ",");
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

    std::vector<std::string> valuesSrc = StringSplit(value, ",");
    auto size = valuesSrc.size();
    if (size <= 0) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "valuesSrc is empty");
        return;
    }
    ArkUI_Float64 values[size];
    for (int i = 0; i < size; ++i) {
        values[i] = StringUtils::StringToDouble(valuesSrc[i].c_str());
    }

    ArkUI_Int32 units[NUM_2] = { UNIT_VP, UNIT_VP };

    fullImpl->getNodeModifiers()->getCommonModifier()->setScale(node->uiNodeHandle, values, size, units, NUM_2);
}

void SetRotate(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    std::vector<std::string> valuesSrc = StringSplit(value, ",");
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
    std::vector<std::string> params = StringSplit(value, " ");
    if (params.size() != NUM_2) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return;
    }

    std::vector<std::string> valuesSrc = StringSplit(params[NUM_0], ",");
    auto size = valuesSrc.size();
    if (size != NUM_4) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "valuesSrc is invalid");
        return;
    }
    ArkUI_Float64 values[size];
    values[NUM_0] = StringToBoolInt(valuesSrc[NUM_0].c_str());
    values[NUM_1] = StringUtils::StringToDouble(valuesSrc[NUM_1].c_str());

    AttrStringToIntMap paramsMap = {
        { "Left", 0},
        { "Top", 1},
        { "Right", 2},
        { "Bottom", 3},
        { "LeftTop", 4},
        { "LeftBottom", 5},
        { "RightTop", 6},
        { "RightBottom", 7},
        { "None", 8},
    };

    auto attrVal = paramsMap.find(value) != paramsMap.end() ? paramsMap[value] : 0;
    values[NUM_2] = attrVal;
    values[NUM_3] = StringToBoolInt(valuesSrc[NUM_3].c_str());

    std::vector<std::string> colorsSrc = StringSplit(params[NUM_1], ",");
    ArkUI_Float64 colors[colorsSrc.size()];
    for (int i = 0; i < colorsSrc.size(); i += NUM_3) {
        colors[i + NUM_0] = StringToColorInt(colorsSrc[i + NUM_0].c_str());
        colors[i + NUM_1] = StringToBoolInt(colorsSrc[i + NUM_1].c_str());
        colors[i + NUM_2] = StringUtils::StringToDouble(colorsSrc[i + NUM_2].c_str());
    }

    fullImpl->getNodeModifiers()->getCommonModifier()->setLinearGradient(node->uiNodeHandle,
        values, size, colors, colorsSrc.size());
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
        { "TopStart", 0},
        { "Top", 1},
        { "TopEnd", 2},
        { "Start", 3},
        { "Center", 4},
        { "End", 5},
        { "BottomStart", 6},
        { "Bottom", 7},
        { "BottomEnd", 8}
    };

    auto attrVal = paramsMap.find(value) != paramsMap.end() ? paramsMap[value] : 0;
    fullImpl->getNodeModifiers()->getCommonModifier()->setAlign(node->uiNodeHandle, attrVal);
}

// TextInput Arttributes functions
void SetFontColor(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    if (node->type == ARKUI_NODE_TEXT_INPUT) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputFontColor(
            node->uiNodeHandle, StringToColorInt(value, 0));
    }
}

void SetFontWeight(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    if (node->type == ARKUI_NODE_TEXT_INPUT) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputFontWeight(node->uiNodeHandle, value);
    }
}

void SetFontSize(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    struct ArkUILengthType fontSize = { nullptr, StringToFloat(value, 0.0f), 2 };
    if (node->type == ARKUI_NODE_TEXT_INPUT) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputFontSize(node->uiNodeHandle, &fontSize);
    }
}

void SetFontStyle(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    std::vector<std::string> style = {"Normal", "Italic"};
    if (node->type == ARKUI_NODE_TEXT_INPUT) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputFontStyle(
            node->uiNodeHandle, StringToEnumInt(value, style, 0));
    }
}

void SetTextAlign(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    std::vector<std::string> align = {"Start", "Center", "End", "Justify"};
    if (node->type == ARKUI_NODE_TEXT_INPUT) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputTextAlign(
            node->uiNodeHandle, StringToEnumInt(value, align, 0));
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
    std::vector<std::string> enterKeyType = {"Begin", "None", "Go", "Search", "Send",
        "Next", "Done", "Previous", "NewLine" };
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
    std::vector<std::string> style = {"Normal", "Italic"};
    struct ArkUILengthType size = { nullptr, StringToFloat(font[0].c_str(), 0.0f), 2 };
    std::string familyStr = font[3];
    int fontFamilyLength = familyStr.length();
    struct ArkUIPlaceholderFontType palceHolderFont = { &size, font[1].c_str(),
        nullptr, 0, StringToEnumInt(font[2].c_str(), style, 0)};
    if (fontFamilyLength) {
        std::vector<std::string> fontFamilies;
        
        StringUtils::StringSplitter(familyStr.c_str(), ',', fontFamilies);
        auto families = std::make_unique<char* []>(fontFamilies.size());
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

    std::vector<std::string> inputType = {"Normal", "Multiline", "Number", "PhoneNumber",
        "DateTime", "Email", "Url", "Password", "NumberPassword", "ScreenLockPassword",
        "UserName", "NewPassword", "NumberDecimal"};
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

    AttrStringToIntMap paramsMap = {
        { "TopStart", 0},
        { "Top", 1},
        { "TopEnd", 2},
        { "Start", 3},
        { "Center", 4},
        { "End", 5},
        { "BottomStart", 6},
        { "Bottom", 7},
        { "BottomEnd", 8}
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
    std::vector<std::string> params = StringSplit(value, " ");
    if (params.size() == 0) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "value is null");
        return;
    }
    std::vector<std::string> paginationValueSrc = StringSplit(params[NUM_0], ",");
    auto size = paginationValueSrc.size();
    if (paginationValueSrc.empty()) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "paginationValueSrc.len is 0");
        return;
    }
    ArkUI_Float64 paginationValue[size];
    for (int i = 0; i < size; ++i) {
        paginationValue[i] = StringToFloat(paginationValueSrc[i].c_str());
    }

    std::vector<std::string> paginationParamsSrc = StringSplit(params[NUM_1], ",");
    if (paginationParamsSrc.empty()) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "paginationParamsSrc.len is 0");
        return;
    }
    ArkUI_Int32 paginationParams[paginationParamsSrc.size() + size];
    for (int i = 0; i < paginationParamsSrc.size() + size; ++i) {
        if (i < size) {
            paginationParams[i] = UNIT_VP;
            continue;
        }
        paginationParams[i] = StringToFloat(paginationParamsSrc[i].c_str());
    }

    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollScrollSnap(node->uiNodeHandle, paginationValue,
        size, paginationParams, paginationParamsSrc.size());
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
        { "Off", 0},
        { "Auto", 1},
        { "On", 2},
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
        { "Vertical", 0},
        { "Horizontal", 1},
        { "Free", 2},
        { "None", 3},
    };

    auto attrVal = paramsMap.find(value) != paramsMap.end() ? paramsMap[value] : 0;
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
    bool enabled = false;
    std::vector<std::string> params = StringSplit(value, " ");
    if (params.size() != NUM_2) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return;
    }

    AttrStringToIntMap paramsMap = {
        { "Spring", 0},
        { "Fade", 1},
        { "None", 2},
    };

    auto attrVal = paramsMap.find(value) != paramsMap.end() ? paramsMap[value] : 0;
    enabled = StringToBoolInt(params[NUM_1].c_str());
    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollEdgeEffect(node->uiNodeHandle, attrVal, enabled);
}

void SetScrollEnableScrollInteraction(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    bool enableScrollInteraction = StringToBoolInt(value);
    fullImpl->getNodeModifiers()->getScrollModifier()->setEnableScrollInteraction(node->uiNodeHandle,
        enableScrollInteraction);
}

// List Attributes functions
void SetListCachedCount(ArkUI_NodeHandle node, const char* value)
{
    auto fullImpl = GetFullImpl();
    if (!fullImpl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get full impl");
        return;
    }
    fullImpl->getNodeModifiers()->getListModifier()->setCachedCount(node->uiNodeHandle, StringToInt(value));
}

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
        { "Vertical", 0},
        { "Horizontal", 1},
        { "Free", 2},
        { "None", 3},
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
        { "Vertical", 0},
        { "Horizontal", 1},
        { "Free", 2},
        { "None", 3},
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
        { "None", 0},
        { "Header", 1},
        { "Footer", 2},
        { "Both", 3}
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
    bool enableScrollInteraction = StringToBoolInt(value);
    fullImpl->getNodeModifiers()->getListModifier()->setEnableScrollInteraction(node->uiNodeHandle,
        enableScrollInteraction);
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
    ArkUI_Bool alwaysEnabled = false;
    std::vector<std::string> params = StringSplit(value, " ");
    if (params.size() != NUM_2) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params is invalid");
        return;
    }

    AttrStringToIntMap paramsMap = {
        { "Spring", 0},
        { "Fade", 1},
        { "None", 2},
    };

    auto attrVal = paramsMap.find(value) != paramsMap.end() ? paramsMap[value] : 0;

    alwaysEnabled = StringToBoolInt(params[NUM_1].c_str());
    fullImpl->getNodeModifiers()->getListModifier()->setListEdgeEffect(node->uiNodeHandle, attrVal, alwaysEnabled);
}

using Setter = void(ArkUI_NodeHandle node, const char* value);
void SetCommonAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const char* value)
{
    static Setter* setters[] = {
        SetWidth, SetHeight, SetBackgroundColor, SetBackgroundImage, SetPadding, SetKey, SetEnabled,
        SetMargin, SetTranslate, SetScale, SetRotate, SetBrightness, SetSaturate, SetBlur,
        SetLinearGradient, SetAlign
    };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "common node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    setters[subTypeId](node, value);
}

void SetTextAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const char* value)
{
    static Setter* setters[] = { SetFontColor, SetFontSize, SetFontWeight, SetFontStyle, SetTextAlign };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "text node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    setters[subTypeId](node, value);
}

void SetTextInputAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const char* value)
{
    static Setter* setters[] = { SetTextInputPlaceholder, SetTextInputText, SetCaretColor,
        SetCaretStyle, SetShowUnderline, SetMaxLength, SetEnterKeyType, SetPlaceholderColor,
        SetTextInputPlaceholderFont, SetEnableKeybordOnFocus, SetTextInputType, SetSelectedBackgroundColor,
        SetShowPasswordIcon };
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
    static Setter* setters[] = {
        SetScrollScrollBar, SetScrollScrollBarWidth, SetScrollScrollBarColor, SetScrollScrollable,
        SetScrollEdgeEffect, SetScrollEnableScrollInteraction, SetScrollFriction, SetScrollScrollSnap
    };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "scroll node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    setters[subTypeId](node, value);
}

void SetListAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const char* value)
{
    static Setter* setters[] = {
        SetListCachedCount, SetListScrollBar, SetListListDirection, SetListListSticky, SetListEdgeEffect,
        SetListEnableScrollInteraction
    };
    if (subTypeId >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "list node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    setters[subTypeId](node, value);
}

} // namespace

void SetNodeAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType type, const char* value)
{
    using AttributeSetterClass = void(ArkUI_NodeHandle node, int32_t subTypeId, const char* value);
    static AttributeSetterClass* setterClasses[] = {
        SetCommonAttribute, SetTextAttribute, nullptr, nullptr, nullptr, nullptr,
        nullptr, SetTextInputAttribute, SetStackAttribute, SetScrollAttribute, SetListAttribute, nullptr
    };
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
