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
namespace MutableStyledStringAccessor {
void DestroyPeerImpl(MutableStyledStringPeer* peer)
{
}
MutableStyledStringPeer* CtorImpl()
{
    return new MutableStyledStringPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void ReplaceStringImpl(MutableStyledStringPeer* peer,
                       const Ark_Number* start,
                       const Ark_Number* length,
                       const Ark_String* other)
{
}
void InsertStringImpl(MutableStyledStringPeer* peer,
                      const Ark_Number* start,
                      const Ark_String* other)
{
}
void RemoveStringImpl(MutableStyledStringPeer* peer,
                      const Ark_Number* start,
                      const Ark_Number* length)
{
}
void ReplaceStyleImpl(MutableStyledStringPeer* peer,
                      const Ark_SpanStyle* spanStyle)
{
}
void SetStyleImpl(MutableStyledStringPeer* peer,
                  const Ark_SpanStyle* spanStyle)
{
}
void RemoveStyleImpl(MutableStyledStringPeer* peer,
                     const Ark_Number* start,
                     const Ark_Number* length,
                     Ark_StyledStringKey styledKey)
{
}
void RemoveStylesImpl(MutableStyledStringPeer* peer,
                      const Ark_Number* start,
                      const Ark_Number* length)
{
}
void ClearStylesImpl(MutableStyledStringPeer* peer)
{
}
void ReplaceStyledStringImpl(MutableStyledStringPeer* peer,
                             const Ark_Number* start,
                             const Ark_Number* length,
                             const Ark_StyledString* other)
{
}
void InsertStyledStringImpl(MutableStyledStringPeer* peer,
                            const Ark_Number* start,
                            const Ark_StyledString* other)
{
}
void AppendStyledStringImpl(MutableStyledStringPeer* peer,
                            const Ark_StyledString* other)
{
}
} // MutableStyledStringAccessor
const GENERATED_ArkUIMutableStyledStringAccessor* GetMutableStyledStringAccessor()
{
    static const GENERATED_ArkUIMutableStyledStringAccessor MutableStyledStringAccessorImpl {
        MutableStyledStringAccessor::DestroyPeerImpl,
        MutableStyledStringAccessor::CtorImpl,
        MutableStyledStringAccessor::GetFinalizerImpl,
        MutableStyledStringAccessor::ReplaceStringImpl,
        MutableStyledStringAccessor::InsertStringImpl,
        MutableStyledStringAccessor::RemoveStringImpl,
        MutableStyledStringAccessor::ReplaceStyleImpl,
        MutableStyledStringAccessor::SetStyleImpl,
        MutableStyledStringAccessor::RemoveStyleImpl,
        MutableStyledStringAccessor::RemoveStylesImpl,
        MutableStyledStringAccessor::ClearStylesImpl,
        MutableStyledStringAccessor::ReplaceStyledStringImpl,
        MutableStyledStringAccessor::InsertStyledStringImpl,
        MutableStyledStringAccessor::AppendStyledStringImpl,
    };
    return &MutableStyledStringAccessorImpl;
}

}
