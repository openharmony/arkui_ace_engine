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
#include <regex>

#include "basic_node.h"
#include "node_model.h"

#include "base/log/log_wrapper.h"
#include "core/interfaces/native/node/node_api.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NodeModel {
namespace {
const std::regex COLOR_WITH_MAGIC("#[0-9A-Fa-f]{8}");
const int ALLOW_SIZE_4(4);

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

using Setter = void(ArkUI_NodeHandle node, const char* value);
void SetCommonAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const char* value)
{
    static Setter* setters[] = { SetWidth, SetHeight, SetBackgroundColor,
        SetBackgroundImage, SetPadding, SetKey, SetEnabled, };
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

} // namespace

void SetNodeAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType type, const char* value)
{
    using AttributeSetterClass = void(ArkUI_NodeHandle node, int32_t subTypeId, const char* value);
    static AttributeSetterClass* setterClasses[] = { SetCommonAttribute, SetTextAttribute,
        nullptr, nullptr, nullptr, nullptr, nullptr, SetTextInputAttribute,
        nullptr, nullptr, nullptr, nullptr};
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
