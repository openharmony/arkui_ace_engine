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
namespace StyledStringModifier {
Ark_NativePointer CtorImpl(const Union_String_ImageAttachment_CustomSpan* value,
                           const Opt_Array_StyleOptions* styles)
{
    return 0;
}
Ark_NativePointer GetFinalizerImpl()
{
    return 0;
}
void GetStringImpl(StyledStringPeer* peer)
{
}
Ark_NativePointer GetStylesImpl(StyledStringPeer* peer,
                                const Ark_Number* start,
                                const Ark_Number* length,
                                const Opt_StyledStringKey* styledKey)
{
    return 0;
}
Ark_Boolean EqualsImpl(StyledStringPeer* peer,
                       const Ark_Materialized* other)
{
    return 0;
}
Ark_NativePointer SubStyledStringImpl(StyledStringPeer* peer,
                                      const Ark_Number* start,
                                      const Opt_Number* length)
{
    return 0;
}
Ark_NativePointer FromHtmlImpl(const Ark_String* html)
{
    return 0;
}
Ark_NativePointer MarshallingImpl(const Ark_Materialized* styledString)
{
    return 0;
}
Ark_NativePointer UnmarshallingImpl(const Ark_ArrayBuffer* buffer)
{
    return 0;
}
Ark_Int32 GetLengthImpl(StyledStringPeer* peer)
{
    return 0;
}
} // StyledStringModifier
const GENERATED_ArkUIStyledStringAccessor* GetStyledStringAccessor()
{
    static const GENERATED_ArkUIStyledStringAccessor StyledStringAccessorImpl {
        StyledStringModifier::CtorImpl,
        StyledStringModifier::GetFinalizerImpl,
        StyledStringModifier::GetStringImpl,
        StyledStringModifier::GetStylesImpl,
        StyledStringModifier::EqualsImpl,
        StyledStringModifier::SubStyledStringImpl,
        StyledStringModifier::FromHtmlImpl,
        StyledStringModifier::MarshallingImpl,
        StyledStringModifier::UnmarshallingImpl,
        StyledStringModifier::GetLengthImpl,
    };
    return &StyledStringAccessorImpl;
}

}
