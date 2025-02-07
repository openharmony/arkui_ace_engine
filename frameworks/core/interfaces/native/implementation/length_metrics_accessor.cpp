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

#include "length_metrics_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace LengthMetricsAccessor {
void DestroyPeerImpl(LengthMetricsPeer* peer)
{
    LengthMetricsPeer::Destroy(peer);
}
Ark_NativePointer CtorImpl()
{
    return LengthMetricsPeer::Create({});
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_NativePointer PxImpl(const Ark_Number* value)
{
    return nullptr;
}
Ark_NativePointer ResourceImpl(const Ark_Resource* value)
{
    return nullptr;
}
Ark_NativePointer GetUnitImpl(LengthMetricsPeer* peer)
{
    return nullptr;
}
void SetUnitImpl(LengthMetricsPeer* peer,
                 Ark_LengthUnit unit)
{
}
Ark_Int32 GetValueImpl(LengthMetricsPeer* peer)
{
    return 0;
}
void SetValueImpl(LengthMetricsPeer* peer,
                  const Ark_Number* value)
{
}
} // LengthMetricsAccessor
const GENERATED_ArkUILengthMetricsAccessor* GetLengthMetricsAccessor()
{
    static const GENERATED_ArkUILengthMetricsAccessor LengthMetricsAccessorImpl {
        LengthMetricsAccessor::DestroyPeerImpl,
        LengthMetricsAccessor::CtorImpl,
        LengthMetricsAccessor::GetFinalizerImpl,
        LengthMetricsAccessor::PxImpl,
        LengthMetricsAccessor::ResourceImpl,
        LengthMetricsAccessor::GetUnitImpl,
        LengthMetricsAccessor::SetUnitImpl,
        LengthMetricsAccessor::GetValueImpl,
        LengthMetricsAccessor::SetValueImpl,
    };
    return &LengthMetricsAccessorImpl;
}

struct LengthMetricsPeer {
    virtual ~LengthMetricsPeer() = default;
};
}
