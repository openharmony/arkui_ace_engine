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
namespace uiObserver_DensityInfoAccessor {
void DestroyPeerImpl(Ark_uiObserver_DensityInfo peer)
{
}
Ark_uiObserver_DensityInfo ConstructImpl()
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_UIContext GetContextImpl(Ark_uiObserver_DensityInfo peer)
{
    return {};
}
void SetContextImpl(Ark_uiObserver_DensityInfo peer,
                    Ark_UIContext context)
{
}
Ark_Number GetDensityImpl(Ark_uiObserver_DensityInfo peer)
{
    return {};
}
void SetDensityImpl(Ark_uiObserver_DensityInfo peer,
                    const Ark_Number* density)
{
}
} // uiObserver_DensityInfoAccessor
const GENERATED_ArkUIUiObserver_DensityInfoAccessor* GetUiObserver_DensityInfoAccessor()
{
    static const GENERATED_ArkUIUiObserver_DensityInfoAccessor UiObserver_DensityInfoAccessorImpl {
        uiObserver_DensityInfoAccessor::DestroyPeerImpl,
        uiObserver_DensityInfoAccessor::ConstructImpl,
        uiObserver_DensityInfoAccessor::GetFinalizerImpl,
        uiObserver_DensityInfoAccessor::GetContextImpl,
        uiObserver_DensityInfoAccessor::SetContextImpl,
        uiObserver_DensityInfoAccessor::GetDensityImpl,
        uiObserver_DensityInfoAccessor::SetDensityImpl,
    };
    return &UiObserver_DensityInfoAccessorImpl;
}

}
