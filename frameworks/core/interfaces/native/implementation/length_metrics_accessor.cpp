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
using namespace Converter;
void DestroyPeerImpl(Ark_LengthMetrics peer)
{
    LengthMetricsPeer::Destroy(peer);
}
Ark_LengthMetrics CtorImpl()
{
    return LengthMetricsPeer::Create({});
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_LengthMetrics PxImpl(const Ark_Number* value)
{
    return LengthMetricsPeer::Create(Dimension(Convert<float>(*value)));
}
Ark_LengthMetrics VpImpl(const Ark_Number* value)
{
    return {};
}
Ark_LengthMetrics FpImpl(const Ark_Number* value)
{
    return {};
}
Ark_LengthMetrics PercentImpl(const Ark_Number* value)
{
    return {};
}
Ark_LengthMetrics LpxImpl(const Ark_Number* value)
{
    return {};
}
Ark_LengthMetrics ResourceImpl(const Ark_Resource* value)
{
    return LengthMetricsPeer::Create(Converter::OptConvert<Dimension>(*value).value_or(Dimension()));
}
Ark_LengthUnit GetUnitImpl(Ark_LengthMetrics peer)
{
    return {};
}
void SetUnitImpl(Ark_LengthMetrics peer,
                 Ark_LengthUnit unit)
{
}
Ark_Number GetValueImpl(Ark_LengthMetrics peer)
{
    return {};
}
void SetValueImpl(Ark_LengthMetrics peer,
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
        LengthMetricsAccessor::VpImpl,
        LengthMetricsAccessor::FpImpl,
        LengthMetricsAccessor::PercentImpl,
        LengthMetricsAccessor::LpxImpl,
        LengthMetricsAccessor::ResourceImpl,
        LengthMetricsAccessor::GetUnitImpl,
        LengthMetricsAccessor::SetUnitImpl,
        LengthMetricsAccessor::GetValueImpl,
        LengthMetricsAccessor::SetValueImpl,
    };
    return &LengthMetricsAccessorImpl;
}

}
