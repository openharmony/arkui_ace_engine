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

#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace MutableStyledStringModifier {
Ark_NativePointer CtorImpl()
{
    return 0;
}
Ark_NativePointer GetFinalizerImpl()
{
    return 0;
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
                     enum Ark_StyledStringKey styledKey)
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
                             const Ark_Materialized* other)
{
}
void InsertStyledStringImpl(MutableStyledStringPeer* peer,
                            const Ark_Number* start,
                            const Ark_Materialized* other)
{
}
void AppendStyledStringImpl(MutableStyledStringPeer* peer,
                            const Ark_Materialized* other)
{
}
} // MutableStyledStringModifier
const GENERATED_ArkUIMutableStyledStringAccessor* GetMutableStyledStringAccessor()
{
    static const GENERATED_ArkUIMutableStyledStringAccessor MutableStyledStringAccessorImpl {
        MutableStyledStringModifier::CtorImpl,
        MutableStyledStringModifier::GetFinalizerImpl,
        MutableStyledStringModifier::ReplaceStringImpl,
        MutableStyledStringModifier::InsertStringImpl,
        MutableStyledStringModifier::RemoveStringImpl,
        MutableStyledStringModifier::ReplaceStyleImpl,
        MutableStyledStringModifier::SetStyleImpl,
        MutableStyledStringModifier::RemoveStyleImpl,
        MutableStyledStringModifier::RemoveStylesImpl,
        MutableStyledStringModifier::ClearStylesImpl,
        MutableStyledStringModifier::ReplaceStyledStringImpl,
        MutableStyledStringModifier::InsertStyledStringImpl,
        MutableStyledStringModifier::AppendStyledStringImpl,
    };
    return &MutableStyledStringAccessorImpl;
}

}
