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
namespace GlobalScope_Profiler_inspectorAccessor {
void DestroyPeerImpl(Ark_GlobalScope_Profiler_inspector peer)
{
}
void RegisterVsyncCallbackImpl(const Callback_String_Void* callback_)
{
}
void UnregisterVsyncCallbackImpl()
{
}
} // GlobalScope_Profiler_inspectorAccessor
const GENERATED_ArkUIGlobalScope_Profiler_inspectorAccessor* GetGlobalScope_Profiler_inspectorAccessor()
{
    static const GENERATED_ArkUIGlobalScope_Profiler_inspectorAccessor GlobalScope_Profiler_inspectorAccessorImpl {
        GlobalScope_Profiler_inspectorAccessor::DestroyPeerImpl,
        GlobalScope_Profiler_inspectorAccessor::RegisterVsyncCallbackImpl,
        GlobalScope_Profiler_inspectorAccessor::UnregisterVsyncCallbackImpl,
    };
    return &GlobalScope_Profiler_inspectorAccessorImpl;
}

struct GlobalScope_Profiler_inspectorPeer {
    virtual ~GlobalScope_Profiler_inspectorPeer() = default;
};
}
