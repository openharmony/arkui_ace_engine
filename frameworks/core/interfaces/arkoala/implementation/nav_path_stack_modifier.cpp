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
namespace NavPathStackModifier {
Ark_NativePointer CtorImpl()
{
    return 0;
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
                         const Ark_Object* param,
                         Ark_Function onPop,
                         const Opt_Boolean* animated)
{
}
Ark_NativePointer PushDestinationByName0Impl(NavPathStackPeer* peer,
                                             const Ark_String* name,
                                             const Ark_Object* param,
                                             const Opt_Boolean* animated)
{
    return 0;
}
Ark_NativePointer PushDestinationByName1Impl(NavPathStackPeer* peer,
                                             const Ark_String* name,
                                             const Ark_Object* param,
                                             Ark_Function onPop,
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
                           const Ark_Object* param,
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
void Pop0Impl(NavPathStackPeer* peer,
              const Opt_Boolean* animated)
{
}
void Pop1Impl(NavPathStackPeer* peer,
              const Ark_Object* result,
              const Opt_Boolean* animated)
{
}
Ark_Int32 PopToName0Impl(NavPathStackPeer* peer,
                         const Ark_String* name,
                         const Opt_Boolean* animated)
{
    return 0;
}
Ark_Int32 PopToName1Impl(NavPathStackPeer* peer,
                         const Ark_String* name,
                         const Ark_Object* result,
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
                     const Ark_Object* result,
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
Ark_NativePointer GetAllPathNameImpl(NavPathStackPeer* peer)
{
    return 0;
}
void GetParamByIndexImpl(NavPathStackPeer* peer,
                         const Ark_Number* index)
{
}
Ark_NativePointer GetParamByNameImpl(NavPathStackPeer* peer,
                                     const Ark_String* name)
{
    return 0;
}
Ark_NativePointer GetIndexByNameImpl(NavPathStackPeer* peer,
                                     const Ark_String* name)
{
    return 0;
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
} // NavPathStackModifier
const GENERATED_ArkUINavPathStackAccessor* GetNavPathStackAccessor()
{
    static const GENERATED_ArkUINavPathStackAccessor NavPathStackAccessorImpl {
        NavPathStackModifier::CtorImpl,
        NavPathStackModifier::GetFinalizerImpl,
        NavPathStackModifier::PushPath0Impl,
        NavPathStackModifier::PushPath1Impl,
        NavPathStackModifier::PushDestination0Impl,
        NavPathStackModifier::PushDestination1Impl,
        NavPathStackModifier::PushPathByName0Impl,
        NavPathStackModifier::PushPathByName1Impl,
        NavPathStackModifier::PushDestinationByName0Impl,
        NavPathStackModifier::PushDestinationByName1Impl,
        NavPathStackModifier::ReplacePath0Impl,
        NavPathStackModifier::ReplacePath1Impl,
        NavPathStackModifier::ReplacePathByNameImpl,
        NavPathStackModifier::RemoveByIndexesImpl,
        NavPathStackModifier::RemoveByNameImpl,
        NavPathStackModifier::RemoveByNavDestinationIdImpl,
        NavPathStackModifier::Pop0Impl,
        NavPathStackModifier::Pop1Impl,
        NavPathStackModifier::PopToName0Impl,
        NavPathStackModifier::PopToName1Impl,
        NavPathStackModifier::PopToIndex0Impl,
        NavPathStackModifier::PopToIndex1Impl,
        NavPathStackModifier::MoveToTopImpl,
        NavPathStackModifier::MoveIndexToTopImpl,
        NavPathStackModifier::ClearImpl,
        NavPathStackModifier::GetAllPathNameImpl,
        NavPathStackModifier::GetParamByIndexImpl,
        NavPathStackModifier::GetParamByNameImpl,
        NavPathStackModifier::GetIndexByNameImpl,
        NavPathStackModifier::GetParentImpl,
        NavPathStackModifier::SizeImpl,
        NavPathStackModifier::DisableAnimationImpl,
        NavPathStackModifier::SetInterceptionImpl,
    };
    return &NavPathStackAccessorImpl;
}

}
