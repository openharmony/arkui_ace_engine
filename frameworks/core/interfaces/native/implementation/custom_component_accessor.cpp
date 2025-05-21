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
namespace CustomComponentAccessor {
void DestroyPeerImpl(Ark_CustomComponent peer)
{
}
Ark_CustomComponent CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_CustomObject AddProvidedVarImpl(Ark_CustomComponent peer,
                                    const Ark_String* varName,
                                    const Ark_String* providedPropName,
                                    const Ark_CustomObject* initValue,
                                    const Opt_Boolean* allowOverride,
                                    const Opt_WatchFuncType* watchFunc)
{
    return {};
}
Ark_ConsumeDecoratedVariable InitConsumeImpl(Ark_CustomComponent peer,
                                             const Ark_String* varName,
                                             const Ark_String* providedPropName,
                                             const Opt_WatchFuncType* watchFunc)
{
    return {};
}
Ark_CustomObject $_instantiateImpl(const Callback_S* factory,
                                   const Opt_CustomObject* initializers,
                                   const Opt_Callback_Void* content,
                                   const Opt_String* reuseKey)
{
    return {};
}
void AboutToAppearImpl(Ark_CustomComponent peer)
{
}
void AboutToDisappearImpl(Ark_CustomComponent peer)
{
}
void OnDidBuildImpl(Ark_CustomComponent peer)
{
}
void OnPageShowImpl(Ark_CustomComponent peer)
{
}
void OnPageHideImpl(Ark_CustomComponent peer)
{
}
Ark_Boolean OnBackPressImpl(Ark_CustomComponent peer)
{
    return {};
}
Ark_UIContext GetUIContextImpl(Ark_CustomComponent peer)
{
    return {};
}
void BuildImpl(Ark_CustomComponent peer)
{
}
void AboutToReuseImpl(Ark_CustomComponent peer)
{
}
void AboutToRecycleImpl(Ark_CustomComponent peer)
{
}
} // CustomComponentAccessor
const GENERATED_ArkUICustomComponentAccessor* GetCustomComponentAccessor()
{
    static const GENERATED_ArkUICustomComponentAccessor CustomComponentAccessorImpl {
        CustomComponentAccessor::DestroyPeerImpl,
        CustomComponentAccessor::CtorImpl,
        CustomComponentAccessor::GetFinalizerImpl,
        CustomComponentAccessor::AddProvidedVarImpl,
        CustomComponentAccessor::InitConsumeImpl,
        CustomComponentAccessor::$_instantiateImpl,
        CustomComponentAccessor::AboutToAppearImpl,
        CustomComponentAccessor::AboutToDisappearImpl,
        CustomComponentAccessor::OnDidBuildImpl,
        CustomComponentAccessor::OnPageShowImpl,
        CustomComponentAccessor::OnPageHideImpl,
        CustomComponentAccessor::OnBackPressImpl,
        CustomComponentAccessor::GetUIContextImpl,
        CustomComponentAccessor::BuildImpl,
        CustomComponentAccessor::AboutToReuseImpl,
        CustomComponentAccessor::AboutToRecycleImpl,
    };
    return &CustomComponentAccessorImpl;
}

}
