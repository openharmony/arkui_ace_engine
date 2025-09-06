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
namespace ExtendableComponentAccessor {
void DestroyPeerImpl(Ark_ExtendableComponent peer)
{
}
Ark_ExtendableComponent ConstructImpl()
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_UIContext GetUIContextImpl(Ark_ExtendableComponent peer)
{
    return {};
}
Ark_Int32 GetUniqueIdImpl(Ark_ExtendableComponent peer)
{
    return {};
}
Opt_uiObserver_NavDestinationInfo QueryNavDestinationInfo0Impl(Ark_ExtendableComponent peer)
{
    return {};
}
Opt_uiObserver_NavDestinationInfo QueryNavDestinationInfo1Impl(Ark_ExtendableComponent peer,
                                                               const Opt_Boolean* isInner)
{
    return {};
}
Opt_uiObserver_NavigationInfo QueryNavigationInfoImpl(Ark_ExtendableComponent peer)
{
    return {};
}
Opt_uiObserver_RouterPageInfo QueryRouterPageInfoImpl(Ark_ExtendableComponent peer)
{
    return {};
}
} // ExtendableComponentAccessor
const GENERATED_ArkUIExtendableComponentAccessor* GetExtendableComponentAccessor()
{
    static const GENERATED_ArkUIExtendableComponentAccessor ExtendableComponentAccessorImpl {
        ExtendableComponentAccessor::DestroyPeerImpl,
        ExtendableComponentAccessor::ConstructImpl,
        ExtendableComponentAccessor::GetFinalizerImpl,
        ExtendableComponentAccessor::GetUIContextImpl,
        ExtendableComponentAccessor::GetUniqueIdImpl,
        ExtendableComponentAccessor::QueryNavDestinationInfo0Impl,
        ExtendableComponentAccessor::QueryNavDestinationInfo1Impl,
        ExtendableComponentAccessor::QueryNavigationInfoImpl,
        ExtendableComponentAccessor::QueryRouterPageInfoImpl,
    };
    return &ExtendableComponentAccessorImpl;
}

}
