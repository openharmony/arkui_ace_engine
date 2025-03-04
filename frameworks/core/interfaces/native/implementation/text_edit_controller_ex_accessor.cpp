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
namespace TextEditControllerExAccessor {
void DestroyPeerImpl(Ark_TextEditControllerEx peer)
{
}
Ark_TextEditControllerEx CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Boolean IsEditingImpl(Ark_TextEditControllerEx peer)
{
    return {};
}
void StopEditingImpl(Ark_TextEditControllerEx peer)
{
}
Ark_Boolean SetCaretOffsetImpl(Ark_TextEditControllerEx peer,
                               const Ark_Number* offset)
{
    return {};
}
Ark_Number GetCaretOffsetImpl(Ark_TextEditControllerEx peer)
{
    return {};
}
Ark_PreviewText GetPreviewTextImpl(Ark_TextEditControllerEx peer)
{
    return {};
}
} // TextEditControllerExAccessor
const GENERATED_ArkUITextEditControllerExAccessor* GetTextEditControllerExAccessor()
{
    static const GENERATED_ArkUITextEditControllerExAccessor TextEditControllerExAccessorImpl {
        TextEditControllerExAccessor::DestroyPeerImpl,
        TextEditControllerExAccessor::CtorImpl,
        TextEditControllerExAccessor::GetFinalizerImpl,
        TextEditControllerExAccessor::IsEditingImpl,
        TextEditControllerExAccessor::StopEditingImpl,
        TextEditControllerExAccessor::SetCaretOffsetImpl,
        TextEditControllerExAccessor::GetCaretOffsetImpl,
        TextEditControllerExAccessor::GetPreviewTextImpl,
    };
    return &TextEditControllerExAccessorImpl;
}

}
