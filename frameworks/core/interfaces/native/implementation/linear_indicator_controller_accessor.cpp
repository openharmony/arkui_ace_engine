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

struct LinearIndicatorControllerPeer {};

namespace OHOS::Ace::NG::GeneratedModifier {
namespace LinearIndicatorControllerAccessor {
void DestroyPeerImpl(Ark_LinearIndicatorController peer)
{
}
Ark_LinearIndicatorController CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void SetProgressImpl(Ark_LinearIndicatorController peer,
                     const Ark_Number* index,
                     const Ark_Number* progress)
{
}
void StartImpl(Ark_LinearIndicatorController peer,
               const Opt_LinearIndicatorStartOptions* options)
{
}
void PauseImpl(Ark_LinearIndicatorController peer)
{
}
void StopImpl(Ark_LinearIndicatorController peer)
{
}
} // LinearIndicatorControllerAccessor
const GENERATED_ArkUILinearIndicatorControllerAccessor* GetLinearIndicatorControllerAccessor()
{
    static const GENERATED_ArkUILinearIndicatorControllerAccessor LinearIndicatorControllerAccessorImpl {
        LinearIndicatorControllerAccessor::DestroyPeerImpl,
        LinearIndicatorControllerAccessor::CtorImpl,
        LinearIndicatorControllerAccessor::GetFinalizerImpl,
        LinearIndicatorControllerAccessor::SetProgressImpl,
        LinearIndicatorControllerAccessor::StartImpl,
        LinearIndicatorControllerAccessor::PauseImpl,
        LinearIndicatorControllerAccessor::StopImpl,
    };
    return &LinearIndicatorControllerAccessorImpl;
}

struct LinearIndicatorControllerPeer {
    virtual ~LinearIndicatorControllerPeer() = default;
};
}
