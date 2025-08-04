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
namespace PageLifeCycleAccessor {
void DestroyPeerImpl(Ark_PageLifeCycle peer)
{
}
Ark_PageLifeCycle ConstructImpl()
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void OnPageShowImpl(Ark_PageLifeCycle peer)
{
}
void OnPageHideImpl(Ark_PageLifeCycle peer)
{
}
Ark_Boolean OnBackPressImpl(Ark_PageLifeCycle peer)
{
    return {};
}
void PageTransitionImpl(Ark_PageLifeCycle peer)
{
}
void OnNewParamImpl(Ark_PageLifeCycle peer,
                    const Opt_Object* param)
{
}
} // PageLifeCycleAccessor
const GENERATED_ArkUIPageLifeCycleAccessor* GetPageLifeCycleAccessor()
{
    static const GENERATED_ArkUIPageLifeCycleAccessor PageLifeCycleAccessorImpl {
        PageLifeCycleAccessor::DestroyPeerImpl,
        PageLifeCycleAccessor::ConstructImpl,
        PageLifeCycleAccessor::GetFinalizerImpl,
        PageLifeCycleAccessor::OnPageShowImpl,
        PageLifeCycleAccessor::OnPageHideImpl,
        PageLifeCycleAccessor::OnBackPressImpl,
        PageLifeCycleAccessor::PageTransitionImpl,
        PageLifeCycleAccessor::OnNewParamImpl,
    };
    return &PageLifeCycleAccessorImpl;
}

}
