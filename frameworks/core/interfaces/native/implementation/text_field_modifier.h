/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_TEXT_FIELD_MODIFIER_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_TEXT_FIELD_MODIFIER_H

#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TextFieldModifier {
void SetWidthImpl(Ark_NativePointer node, const Opt_Union_Length_LayoutPolicy* value);
void SetHeightImpl(Ark_NativePointer node, const Opt_Union_Length_LayoutPolicy* value);
void SetPaddingImpl(Ark_NativePointer node, const Opt_Union_Padding_Length_LocalizedPadding* value);
void SetMarginImpl(Ark_NativePointer node, const Opt_Union_Margin_Length_LocalizedMargin* value);
void SetBorderImpl(Ark_NativePointer node, const Opt_BorderOptions* value);
void SetBorderWidthImpl(Ark_NativePointer node, const Opt_Union_Length_EdgeWidths_LocalizedEdgeWidths* value);
void SetBorderColorImpl(Ark_NativePointer node, const Opt_Union_ResourceColor_EdgeColors_LocalizedEdgeColors* value);
void SetBorderStyleImpl(Ark_NativePointer node, const Opt_Union_BorderStyle_EdgeStyles* value);
void SetBorderRadiusImpl(Ark_NativePointer node, const Opt_Union_Length_BorderRadiuses_LocalizedBorderRadiuses* value);
void SetBackgroundColorImpl(Ark_NativePointer node, const Opt_Union_ResourceColor_ColorMetrics* value);
} // namespace TextFieldModifier
} // namespace OHOS::Ace::NG::GeneratedModifier

#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_TEXT_FIELD_MODIFIER_H