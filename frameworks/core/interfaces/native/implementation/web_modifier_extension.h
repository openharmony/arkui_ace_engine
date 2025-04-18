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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_WEB_MODIFIER_EXTENSION_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_WEB_MODIFIER_EXTENSION_H

#ifdef WEB_SUPPORTED
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"

namespace OHOS::Ace {
using ScriptItem = std::pair<std::string, std::vector<std::string>>;
} // namespace OHOS::Ace

namespace OHOS::Ace::NG::Converter {
template<>
void AssignCast(std::optional<Ace::BlurOnKeyboardHideMode>& dst, const Ark_BlurOnKeyboardHideMode& src);
template<>
ScriptItems Convert(const Array_ScriptItem& src);
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier::WebExtensionModifier {
void BlurOnKeyboardHideMode(Ark_NativePointer node, Ark_BlurOnKeyboardHideMode value);
void EnableFollowSystemFontWeight(Ark_NativePointer node, Ark_Boolean value);
void EnableWebAVSession(Ark_NativePointer node, Ark_Boolean value);
void OptimizeParserBudget(Ark_NativePointer node, Ark_Boolean value);
void RunJavaScriptOnDocumentStart(Ark_NativePointer node, const Array_ScriptItem* value);
void RunJavaScriptOnDocumentEnd(Ark_NativePointer node, const Array_ScriptItem* value);
void RunJavaScriptOnHeadEnd(Ark_NativePointer node, const Array_ScriptItem* value);
} // namespace OHOS::Ace::NG::GeneratedModifier::WebExtensionModifier
#endif // WEB_SUPPORTED
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_WEB_MODIFIER_EXTENSION_H
