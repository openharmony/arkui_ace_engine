/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RichEditorControllerAccessor {
void DestroyPeerImpl(Ark_RichEditorController peer)
{
}
Ark_RichEditorController CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Number AddTextSpanImpl(Ark_RichEditorController peer,
                           const Ark_String* value,
                           const Opt_RichEditorTextSpanOptions* options)
{
    return {};
}
Ark_Number AddImageSpanImpl(Ark_RichEditorController peer,
                            const Ark_Union_PixelMap_ResourceStr* value,
                            const Opt_RichEditorImageSpanOptions* options)
{
    return {};
}
Ark_Number AddBuilderSpanImpl(Ark_RichEditorController peer,
                              const CustomNodeBuilder* value,
                              const Opt_RichEditorBuilderSpanOptions* options)
{
    return {};
}
Ark_Number AddSymbolSpanImpl(Ark_RichEditorController peer,
                             const Ark_Resource* value,
                             const Opt_RichEditorSymbolSpanOptions* options)
{
    return {};
}
void UpdateSpanStyleImpl(Ark_RichEditorController peer,
                         const Ark_Type_RichEditorController_updateSpanStyle_value* value)
{
}
void UpdateParagraphStyleImpl(Ark_RichEditorController peer,
                              const Ark_RichEditorParagraphStyleOptions* value)
{
}
void DeleteSpansImpl(Ark_RichEditorController peer,
                     const Opt_RichEditorRange* value)
{
}
Array_Union_RichEditorImageSpanResult_RichEditorTextSpanResult GetSpansImpl(Ark_RichEditorController peer,
                                                                            const Opt_RichEditorRange* value)
{
    return {};
}
Array_RichEditorParagraphResult GetParagraphsImpl(Ark_RichEditorController peer,
                                                  const Opt_RichEditorRange* value)
{
    return {};
}
Ark_RichEditorSelection GetSelectionImpl(Ark_RichEditorController peer)
{
    return {};
}
Array_RichEditorSpan FromStyledStringImpl(Ark_VMContext vmContext,
                                          Ark_RichEditorController peer,
                                          Ark_StyledString value)
{
    return {};
}
Ark_StyledString ToStyledStringImpl(Ark_VMContext vmContext,
                                    Ark_RichEditorController peer,
                                    const Ark_RichEditorRange* value)
{
    return {};
}
} // RichEditorControllerAccessor
const GENERATED_ArkUIRichEditorControllerAccessor* GetRichEditorControllerAccessor()
{
    static const GENERATED_ArkUIRichEditorControllerAccessor RichEditorControllerAccessorImpl {
        RichEditorControllerAccessor::DestroyPeerImpl,
        RichEditorControllerAccessor::CtorImpl,
        RichEditorControllerAccessor::GetFinalizerImpl,
        RichEditorControllerAccessor::AddTextSpanImpl,
        RichEditorControllerAccessor::AddImageSpanImpl,
        RichEditorControllerAccessor::AddBuilderSpanImpl,
        RichEditorControllerAccessor::AddSymbolSpanImpl,
        RichEditorControllerAccessor::UpdateSpanStyleImpl,
        RichEditorControllerAccessor::UpdateParagraphStyleImpl,
        RichEditorControllerAccessor::DeleteSpansImpl,
        RichEditorControllerAccessor::GetSpansImpl,
        RichEditorControllerAccessor::GetParagraphsImpl,
        RichEditorControllerAccessor::GetSelectionImpl,
        RichEditorControllerAccessor::FromStyledStringImpl,
        RichEditorControllerAccessor::ToStyledStringImpl,
    };
    return &RichEditorControllerAccessorImpl;
}

}
