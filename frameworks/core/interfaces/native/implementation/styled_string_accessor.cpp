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
namespace StyledStringAccessor {
void DestroyPeerImpl(Ark_StyledString peer)
{
}
Ark_StyledString CtorImpl(const Ark_Union_String_ImageAttachment_CustomSpan* value,
                          const Opt_Array_StyleOptions* styles)
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_String GetStringImpl(Ark_StyledString peer)
{
    return {};
}
Array_SpanStyle GetStylesImpl(Ark_VMContext vmContext,
                              Ark_StyledString peer,
                              const Ark_Number* start,
                              const Ark_Number* length,
                              const Opt_StyledStringKey* styledKey)
{
    return {};
}
Ark_Boolean EqualsImpl(Ark_StyledString peer,
                       Ark_StyledString other)
{
    return {};
}
Ark_StyledString SubStyledStringImpl(Ark_VMContext vmContext,
                                     Ark_StyledString peer,
                                     const Ark_Number* start,
                                     const Opt_Number* length)
{
    return {};
}
void FromHtmlImpl(Ark_VMContext vmContext,
                  Ark_AsyncWorkerPtr asyncWorker,
                  const Ark_String* html,
                  const Callback_Opt_StyledString_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
}
Ark_String ToHtmlImpl(Ark_VMContext vmContext,
                      Ark_StyledString styledString)
{
    return {};
}
Ark_Buffer Marshalling0Impl(Ark_StyledString styledString,
                            const StyledStringMarshallCallback* callback_)
{
    return {};
}
void Unmarshalling0Impl(Ark_VMContext vmContext,
                        Ark_AsyncWorkerPtr asyncWorker,
                        const Ark_Buffer* buffer,
                        const StyledStringUnmarshallCallback* callback_,
                        const Callback_Opt_StyledString_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
}
Ark_Buffer Marshalling1Impl(Ark_StyledString styledString)
{
    return {};
}
void Unmarshalling1Impl(Ark_VMContext vmContext,
                        Ark_AsyncWorkerPtr asyncWorker,
                        const Ark_Buffer* buffer,
                        const Callback_Opt_StyledString_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
}
Ark_Number GetLengthImpl(Ark_StyledString peer)
{
    return {};
}
} // StyledStringAccessor
const GENERATED_ArkUIStyledStringAccessor* GetStyledStringAccessor()
{
    static const GENERATED_ArkUIStyledStringAccessor StyledStringAccessorImpl {
        StyledStringAccessor::DestroyPeerImpl,
        StyledStringAccessor::CtorImpl,
        StyledStringAccessor::GetFinalizerImpl,
        StyledStringAccessor::GetStringImpl,
        StyledStringAccessor::GetStylesImpl,
        StyledStringAccessor::EqualsImpl,
        StyledStringAccessor::SubStyledStringImpl,
        StyledStringAccessor::FromHtmlImpl,
        StyledStringAccessor::ToHtmlImpl,
        StyledStringAccessor::Marshalling0Impl,
        StyledStringAccessor::Unmarshalling0Impl,
        StyledStringAccessor::Marshalling1Impl,
        StyledStringAccessor::Unmarshalling1Impl,
        StyledStringAccessor::GetLengthImpl,
    };
    return &StyledStringAccessorImpl;
}

}
