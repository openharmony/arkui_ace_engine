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
#include "core/interfaces/native/utility/reverse_converter.h"
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
    CHECK_NULL_RETURN(peer, static_cast<Ark_LengthUnit>(-1));
    DimensionUnit unit = peer->value.Unit();
    return Converter::ArkValue<Ark_LengthUnit>(unit);
}
void SetUnitImpl(Ark_LengthMetrics peer,
                 Ark_LengthUnit unit)
{
    CHECK_NULL_VOID(peer);
    auto convValue = Converter::OptConvert<DimensionUnit>(unit);
    peer->value.SetUnit(convValue.value_or(DimensionUnit::VP));
}
Ark_Number GetValueImpl(Ark_LengthMetrics peer)
{
    CHECK_NULL_RETURN(peer, Converter::ArkValue<Ark_Int32>(0));
    auto value = static_cast<int32_t>(peer->value.Value());
    LOGE("LengthMetricsAccessor::GetValueImpl wrong return type");
    return Converter::ArkValue<Ark_Int32>(value);
}
void SetValueImpl(Ark_LengthMetrics peer,
                  const Ark_Number* value)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<float>(*value);
    peer->value.SetValue(convValue);
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
