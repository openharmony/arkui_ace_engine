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
namespace NavPathStackAccessor {
NavPathStackPeer* CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return 0;
}
void PushPath0Impl(NavPathStackPeer* peer,
                   const Ark_NavPathInfo* info,
                   const Opt_Boolean* animated)
{
}
void PushPath1Impl(NavPathStackPeer* peer,
                   const Ark_NavPathInfo* info,
                   const Opt_NavigationOptions* options)
{
}
Ark_NativePointer PushDestination0Impl(NavPathStackPeer* peer,
                                       const Ark_NavPathInfo* info,
                                       const Opt_Boolean* animated)
{
    return 0;
}
Ark_NativePointer PushDestination1Impl(NavPathStackPeer* peer,
                                       const Ark_NavPathInfo* info,
                                       const Opt_NavigationOptions* options)
{
    return 0;
}
void PushPathByName0Impl(NavPathStackPeer* peer,
                         const Ark_String* name,
                         const Ark_CustomObject* param,
                         const Opt_Boolean* animated)
{
}
void PushPathByName1Impl(NavPathStackPeer* peer,
                         const Ark_String* name,
                         const Ark_CustomObject* param,
                         const Callback_PopInfo_Void* onPop,
                         const Opt_Boolean* animated)
{
}
Ark_NativePointer PushDestinationByName0Impl(NavPathStackPeer* peer,
                                             const Ark_String* name,
                                             const Ark_CustomObject* param,
                                             const Opt_Boolean* animated)
{
    return 0;
}
Ark_NativePointer PushDestinationByName1Impl(NavPathStackPeer* peer,
                                             const Ark_String* name,
                                             const Ark_CustomObject* param,
                                             const Callback_PopInfo_Void* onPop,
                                             const Opt_Boolean* animated)
{
    return 0;
}
void ReplacePath0Impl(NavPathStackPeer* peer,
                      const Ark_NavPathInfo* info,
                      const Opt_Boolean* animated)
{
}
void ReplacePath1Impl(NavPathStackPeer* peer,
                      const Ark_NavPathInfo* info,
                      const Opt_NavigationOptions* options)
{
}
void ReplacePathByNameImpl(NavPathStackPeer* peer,
                           const Ark_String* name,
                           const Ark_CustomObject* param,
                           const Opt_Boolean* animated)
{
}
Ark_Int32 RemoveByIndexesImpl(NavPathStackPeer* peer,
                              const Array_Number* indexes)
{
    return 0;
}
Ark_Int32 RemoveByNameImpl(NavPathStackPeer* peer,
                           const Ark_String* name)
{
    return 0;
}
Ark_Boolean RemoveByNavDestinationIdImpl(NavPathStackPeer* peer,
                                         const Ark_String* navDestinationId)
{
    return 0;
}
Ark_NativePointer Pop0Impl(NavPathStackPeer* peer,
                           const Opt_Boolean* animated)
{
    return 0;
}
Ark_NativePointer Pop1Impl(NavPathStackPeer* peer,
                           const Ark_CustomObject* result,
                           const Opt_Boolean* animated)
{
    return 0;
}
Ark_Int32 PopToName0Impl(NavPathStackPeer* peer,
                         const Ark_String* name,
                         const Opt_Boolean* animated)
{
    return 0;
}
Ark_Int32 PopToName1Impl(NavPathStackPeer* peer,
                         const Ark_String* name,
                         const Ark_CustomObject* result,
                         const Opt_Boolean* animated)
{
    return 0;
}
void PopToIndex0Impl(NavPathStackPeer* peer,
                     const Ark_Number* index,
                     const Opt_Boolean* animated)
{
}
void PopToIndex1Impl(NavPathStackPeer* peer,
                     const Ark_Number* index,
                     const Ark_CustomObject* result,
                     const Opt_Boolean* animated)
{
}
Ark_Int32 MoveToTopImpl(NavPathStackPeer* peer,
                        const Ark_String* name,
                        const Opt_Boolean* animated)
{
    return 0;
}
void MoveIndexToTopImpl(NavPathStackPeer* peer,
                        const Ark_Number* index,
                        const Opt_Boolean* animated)
{
}
void ClearImpl(NavPathStackPeer* peer,
               const Opt_Boolean* animated)
{
}
void GetAllPathNameImpl(NavPathStackPeer* peer)
{
}
Ark_NativePointer GetParamByIndexImpl(NavPathStackPeer* peer,
                                      const Ark_Number* index)
{
    return 0;
}
void GetParamByNameImpl(NavPathStackPeer* peer,
                        const Ark_String* name)
{
}
void GetIndexByNameImpl(NavPathStackPeer* peer,
                        const Ark_String* name)
{
}
Ark_NativePointer GetParentImpl(NavPathStackPeer* peer)
{
    return 0;
}
Ark_Int32 SizeImpl(NavPathStackPeer* peer)
{
    return 0;
}
void DisableAnimationImpl(NavPathStackPeer* peer,
                          Ark_Boolean value)
{
}
void SetInterceptionImpl(NavPathStackPeer* peer,
                         const Ark_NavigationInterception* interception)
{
}
} // NavPathStackAccessor
const GENERATED_ArkUINavPathStackAccessor* GetNavPathStackAccessor()
{
    static const GENERATED_ArkUINavPathStackAccessor NavPathStackAccessorImpl {
        NavPathStackAccessor::CtorImpl,
        NavPathStackAccessor::GetFinalizerImpl,
        NavPathStackAccessor::PushPath0Impl,
        NavPathStackAccessor::PushPath1Impl,
        NavPathStackAccessor::PushDestination0Impl,
        NavPathStackAccessor::PushDestination1Impl,
        NavPathStackAccessor::PushPathByName0Impl,
        NavPathStackAccessor::PushPathByName1Impl,
        NavPathStackAccessor::PushDestinationByName0Impl,
        NavPathStackAccessor::PushDestinationByName1Impl,
        NavPathStackAccessor::ReplacePath0Impl,
        NavPathStackAccessor::ReplacePath1Impl,
        NavPathStackAccessor::ReplacePathByNameImpl,
        NavPathStackAccessor::RemoveByIndexesImpl,
        NavPathStackAccessor::RemoveByNameImpl,
        NavPathStackAccessor::RemoveByNavDestinationIdImpl,
        NavPathStackAccessor::Pop0Impl,
        NavPathStackAccessor::Pop1Impl,
        NavPathStackAccessor::PopToName0Impl,
        NavPathStackAccessor::PopToName1Impl,
        NavPathStackAccessor::PopToIndex0Impl,
        NavPathStackAccessor::PopToIndex1Impl,
        NavPathStackAccessor::MoveToTopImpl,
        NavPathStackAccessor::MoveIndexToTopImpl,
        NavPathStackAccessor::ClearImpl,
        NavPathStackAccessor::GetAllPathNameImpl,
        NavPathStackAccessor::GetParamByIndexImpl,
        NavPathStackAccessor::GetParamByNameImpl,
        NavPathStackAccessor::GetIndexByNameImpl,
        NavPathStackAccessor::GetParentImpl,
        NavPathStackAccessor::SizeImpl,
        NavPathStackAccessor::DisableAnimationImpl,
        NavPathStackAccessor::SetInterceptionImpl,
    };
    return &NavPathStackAccessorImpl;
}

}
