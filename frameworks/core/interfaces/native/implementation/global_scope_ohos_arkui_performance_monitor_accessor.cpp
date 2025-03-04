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
namespace GlobalScope_ohos_arkui_performanceMonitorAccessor {
void DestroyPeerImpl(Ark_GlobalScope_ohos_arkui_performanceMonitor peer)
{
}
Ark_GlobalScope_ohos_arkui_performanceMonitor CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void BeginImpl(const Ark_String* scene,
               Ark_PerfMonitorActionType startInputType,
               const Opt_String* note)
{
}
void EndImpl(const Ark_String* scene)
{
}
void RecordInputEventTimeImpl(Ark_PerfMonitorActionType actionType,
                              Ark_PerfMonitorSourceType sourceType,
                              const Ark_Number* time)
{
}
} // GlobalScope_ohos_arkui_performanceMonitorAccessor
const GENERATED_ArkUIGlobalScope_ohos_arkui_performanceMonitorAccessor* GetGlobalScope_ohos_arkui_performanceMonitorAccessor()
{
    static const GENERATED_ArkUIGlobalScope_ohos_arkui_performanceMonitorAccessor GlobalScope_ohos_arkui_performanceMonitorAccessorImpl {
        GlobalScope_ohos_arkui_performanceMonitorAccessor::DestroyPeerImpl,
        GlobalScope_ohos_arkui_performanceMonitorAccessor::CtorImpl,
        GlobalScope_ohos_arkui_performanceMonitorAccessor::GetFinalizerImpl,
        GlobalScope_ohos_arkui_performanceMonitorAccessor::BeginImpl,
        GlobalScope_ohos_arkui_performanceMonitorAccessor::EndImpl,
        GlobalScope_ohos_arkui_performanceMonitorAccessor::RecordInputEventTimeImpl,
    };
    return &GlobalScope_ohos_arkui_performanceMonitorAccessorImpl;
}

}
