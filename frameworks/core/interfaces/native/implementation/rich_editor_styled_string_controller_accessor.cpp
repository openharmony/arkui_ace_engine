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
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

struct RichEditorStyledStringControllerPeer {};

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RichEditorStyledStringControllerAccessor {
void DestroyPeerImpl(RichEditorStyledStringControllerPeer* peer)
{
}
RichEditorStyledStringControllerPeer* CtorImpl()
{
    return new RichEditorStyledStringControllerPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void SetStyledStringImpl(RichEditorStyledStringControllerPeer* peer,
                         const Ark_StyledString* styledString)
{
}
Ark_NativePointer GetStyledStringImpl(RichEditorStyledStringControllerPeer* peer)
{
    return 0;
}
Ark_NativePointer GetSelectionImpl(RichEditorStyledStringControllerPeer* peer)
{
    return 0;
}
void OnContentChangedImpl(RichEditorStyledStringControllerPeer* peer,
                          const Ark_StyledStringChangedListener* listener)
{
}
} // RichEditorStyledStringControllerAccessor
const GENERATED_ArkUIRichEditorStyledStringControllerAccessor* GetRichEditorStyledStringControllerAccessor()
{
    static const GENERATED_ArkUIRichEditorStyledStringControllerAccessor RichEditorStyledStringControllerAccessorImpl {
        RichEditorStyledStringControllerAccessor::DestroyPeerImpl,
        RichEditorStyledStringControllerAccessor::CtorImpl,
        RichEditorStyledStringControllerAccessor::GetFinalizerImpl,
        RichEditorStyledStringControllerAccessor::SetStyledStringImpl,
        RichEditorStyledStringControllerAccessor::GetStyledStringImpl,
        RichEditorStyledStringControllerAccessor::GetSelectionImpl,
        RichEditorStyledStringControllerAccessor::OnContentChangedImpl,
    };
    return &RichEditorStyledStringControllerAccessorImpl;
}

}
