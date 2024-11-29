/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/arkoala/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RichEditorControllerAccessor {
void DestroyPeerImpl(RichEditorControllerPeer* peer)
{
}
RichEditorControllerPeer* CtorImpl()
{
    return new RichEditorControllerPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Int32 AddTextSpanImpl(RichEditorControllerPeer* peer,
                          const Ark_String* value,
                          const Opt_RichEditorTextSpanOptions* options)
{
    return 0;
}
Ark_Int32 AddImageSpanImpl(RichEditorControllerPeer* peer,
                           const Ark_Union_PixelMap_ResourceStr* value,
                           const Opt_RichEditorImageSpanOptions* options)
{
    return 0;
}
Ark_Int32 AddBuilderSpanImpl(RichEditorControllerPeer* peer,
                             const Callback_Any* value,
                             const Opt_RichEditorBuilderSpanOptions* options)
{
    return 0;
}
Ark_Int32 AddSymbolSpanImpl(RichEditorControllerPeer* peer,
                            const Ark_Resource* value,
                            const Opt_RichEditorSymbolSpanOptions* options)
{
    return 0;
}
void UpdateSpanStyleImpl(RichEditorControllerPeer* peer,
                         const Ark_Type_RichEditorController_updateSpanStyle_value* value)
{
}
void UpdateParagraphStyleImpl(RichEditorControllerPeer* peer,
                              const Ark_RichEditorParagraphStyleOptions* value)
{
}
void DeleteSpansImpl(RichEditorControllerPeer* peer,
                     const Opt_RichEditorRange* value)
{
}
void GetSpansImpl(RichEditorControllerPeer* peer,
                  const Opt_RichEditorRange* value)
{
}
void GetParagraphsImpl(RichEditorControllerPeer* peer,
                       const Opt_RichEditorRange* value)
{
}
Ark_NativePointer GetSelectionImpl(RichEditorControllerPeer* peer)
{
    return 0;
}
void FromStyledStringImpl(RichEditorControllerPeer* peer,
                          const Ark_StyledString* value)
{
}
Ark_NativePointer ToStyledStringImpl(RichEditorControllerPeer* peer,
                                     const Ark_RichEditorRange* value)
{
    return 0;
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
