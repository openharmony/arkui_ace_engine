/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_TEST_UNITTEST_CAPI_MODIFIERS_RICHEDITOR_MODIFIER_TEST_H
#define FOUNDATION_ARKUI_ACE_ENGINE_TEST_UNITTEST_CAPI_MODIFIERS_RICHEDITOR_MODIFIER_TEST_H

#include "arkoala_api.h"
#include "arkoala_api_generated.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model.h"
#include "core/interfaces/native/implementation/rich_editor_controller_structs.h"

namespace OHOS::Ace::NG::Converter {
void AssignArkValue(Ark_DecorationStyleInterface& dst, const TextDecorationStruct& src);
void AssignArkValue(Ark_FontWeight& dst, OHOS::Ace::FontWeight src);
void AssignArkValue(Ark_RichEditorTextSpanOptions& dst, const OHOS::Ace::TextSpanOptions& src);
void AssignArkValue(Ark_RichEditorImageSpanOptions& dst, const OHOS::Ace::ImageSpanOptions& src);
void AssignArkValue(Ark_RichEditorSymbolSpanOptions& dst, const OHOS::Ace::SymbolSpanOptions& src);
void AssignArkValue(Ark_RichEditorBuilderSpanOptions& dst, const OHOS::Ace::SpanOptionBase& src);
void AssignArkValue(Ark_RichEditorUpdateTextSpanStyleOptions& dst, const TextSpanOptionsForUpdate& src);
void AssignArkValue(Ark_RichEditorTextStyle& dst, const OHOS::Ace::TextStyle& style);
void AssignArkValue(Ark_Type_RichEditorController_updateSpanStyle_value& dst, const TextSpanOptionsForUpdate& src);
void AssignArkValue(Ark_TextAlign& dst, const OHOS::Ace::TextAlign& src);
void AssignArkValue(Ark_WordBreak& dst, const OHOS::Ace::WordBreak& src);
void AssignArkValue(Ark_LineBreakStrategy& dst, const OHOS::Ace::LineBreakStrategy& src);
void AssignArkValue(Ark_RichEditorParagraphStyle& dst, const UpdateParagraphStyle& style);
void AssignArkValue(Ark_RichEditorRange& dst, const RangeOptions& src);
} // namespace OHOS::Ace::NG::Converter

#endif // FOUNDATION_ARKUI_ACE_ENGINE_TEST_UNITTEST_CAPI_MODIFIERS_RICHEDITOR_MODIFIER_TEST_H
