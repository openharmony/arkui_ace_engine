/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifdef WEB_SUPPORTED

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/web/web_model_ng.h"
#include "core/interfaces/native/utility/peer_utils.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "web_modifier_extension.h"

namespace OHOS::Ace::NG::Converter {
template<>
ScriptItem Convert(const Ark_ScriptItem& src)
{
    ScriptItem item = std::make_pair(
        Converter::Convert<std::string>(src.script), Converter::Convert<std::vector<std::string>>(src.scriptRules));
    return item;
}

template<>
ScriptItems Convert(const Array_ScriptItem& src)
{
    auto items = Converter::Convert<std::vector<ScriptItem>>(src);
    ScriptItems scriptItems;
    for (auto item : items) {
        if (scriptItems.find(item.first) == scriptItems.end()) {
            if (item.first.empty() || item.second.empty()) {
                continue;
            }
            scriptItems.insert(item);
        }
    }
    return scriptItems;
}

template<>
void AssignCast(std::optional<Ace::BlurOnKeyboardHideMode>& dst, const Ark_BlurOnKeyboardHideMode& src)
{
    switch (src) {
        case ARK_BLUR_ON_KEYBOARD_HIDE_MODE_SILENT: dst = Ace::BlurOnKeyboardHideMode::SILENT; break;
        case ARK_BLUR_ON_KEYBOARD_HIDE_MODE_BLUR: dst = Ace::BlurOnKeyboardHideMode::BLUR; break;
        default: LOGE("Unexpected enum value in Ark_BlurOnKeyboardHideMode: %{public}d", src);
    }
}
}  // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier::WebExtensionModifier {
ScriptItemsByOrder GetByOrder(ScriptItems scripts)
{
    ScriptItemsByOrder scriptItemsByOrder;
    for (const auto& [key, value] : scripts) {
        if (key.empty()) {
            continue;
        }
        scriptItemsByOrder.emplace_back(key);
    }
    return scriptItemsByOrder;
}
void BlurOnKeyboardHideMode(Ark_NativePointer node, Ark_BlurOnKeyboardHideMode value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Ace::BlurOnKeyboardHideMode>(value);
    WebModelNG::SetBlurOnKeyboardHideMode(frameNode, convValue);
}
void EnableFollowSystemFontWeight(Ark_NativePointer node, Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    WebModelNG::SetEnableFollowSystemFontWeight(frameNode, convValue);
}
void EnableWebAVSession(Ark_NativePointer node, Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    WebModelNG::SetWebMediaAVSessionEnabled(frameNode, convValue);
}
void OptimizeParserBudget(Ark_NativePointer node, Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    WebModelNG::SetOptimizeParserBudgetEnabled(frameNode, convValue);
}
void RunJavaScriptOnDocumentStart(Ark_NativePointer node, const Array_ScriptItem* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<ScriptItems>(*value);
    WebModelNG::JavaScriptOnDocumentStartByOrder(frameNode, convValue, GetByOrder(convValue));
}
void RunJavaScriptOnDocumentEnd(Ark_NativePointer node, const Array_ScriptItem* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<ScriptItems>(*value);
    WebModelNG::JavaScriptOnDocumentEndByOrder(frameNode, convValue, GetByOrder(convValue));
}
void RunJavaScriptOnHeadEnd(Ark_NativePointer node, const Array_ScriptItem* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<ScriptItems>(*value);
    WebModelNG::JavaScriptOnHeadReadyByOrder(frameNode, convValue, GetByOrder(convValue));
}
} // namespace OHOS::Ace::NG::GeneratedModifier::WebExtensionModifier
#endif // WEB_SUPPORTED
