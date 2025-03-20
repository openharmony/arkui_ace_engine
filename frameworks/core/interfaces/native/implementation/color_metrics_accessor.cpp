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
#include "color_metrics_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ColorMetricsAccessor {
void DestroyPeerImpl(Ark_ColorMetrics peer)
{
    delete peer;
}
Ark_ColorMetrics CtorImpl()
{
    return new ColorMetricsPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_ColorMetrics NumericImpl(const Ark_Number* value)
{
    auto* peer = new ColorMetricsPeer();
    CHECK_NULL_RETURN(peer, peer);
    CHECK_NULL_RETURN(value, peer);
    peer->colorValue.value = Converter::Convert<uint32_t>(*value);
    return peer;
}
Ark_ColorMetrics RgbaImpl(const Ark_Number* red,
                          const Ark_Number* green,
                          const Ark_Number* blue,
                          const Opt_Number* alpha)
{
    auto* peer = new ColorMetricsPeer();
    CHECK_NULL_RETURN(peer, peer);
    peer->colorValue.argb.red = red ? Converter::Convert<uint32_t>(*red) : 0x00;
    peer->colorValue.argb.green = green ? Converter::Convert<uint32_t>(*green) : 0x00;
    peer->colorValue.argb.blue = blue ? Converter::Convert<uint32_t>(*blue) : 0x00;
    peer->colorValue.argb.alpha = alpha ? Converter::Convert<uint32_t>(*alpha) : 0xff;
    return peer;
}
Ark_ColorMetrics ResourceColorImpl(const Ark_ResourceColor* color)
{
    auto* peer = new ColorMetricsPeer();
    CHECK_NULL_RETURN(peer, peer);
    CHECK_NULL_RETURN(color, peer);
    OHOS::Ace::Color aceColor = Converter::Convert<OHOS::Ace::Color>(*color);
    peer->colorValue.value = color.GetValue();
    return peer;
}
Ark_ColorMetrics BlendColorImpl(Ark_ColorMetrics peer,
                                Ark_ColorMetrics overlayColor)
{
    return {};
}
Ark_String GetColorImpl(Ark_ColorMetrics peer)
{
    CHECK_NULL_RETURN(peer, {});
    return Ace::Color(peer->colorValue.value).ToString();
}
Ark_Number GetRedImpl(Ark_ColorMetrics peer)
{
    CHECK_NULL_RETURN(peer, Converter::ArkValue(0));
    return Converter::ArkValue(peer->colorValue.argb.red);
}
Ark_Number GetGreenImpl(Ark_ColorMetrics peer)
{
    CHECK_NULL_RETURN(peer, Converter::ArkValue(0));
    return Converter::ArkValue(peer->colorValue.argb.green);
}
Ark_Number GetBlueImpl(Ark_ColorMetrics peer)
{
    CHECK_NULL_RETURN(peer, Converter::ArkValue(0));
    return Converter::ArkValue(peer->colorValue.argb.blue);
}
Ark_Number GetAlphaImpl(Ark_ColorMetrics peer)
{
    CHECK_NULL_RETURN(peer, Converter::ArkValue(0xff));
    return Converter::ArkValue(peer->colorValue.argb.alpha);
}
} // ColorMetricsAccessor
const GENERATED_ArkUIColorMetricsAccessor* GetColorMetricsAccessor()
{
    static const GENERATED_ArkUIColorMetricsAccessor ColorMetricsAccessorImpl {
        ColorMetricsAccessor::DestroyPeerImpl,
        ColorMetricsAccessor::CtorImpl,
        ColorMetricsAccessor::GetFinalizerImpl,
        ColorMetricsAccessor::NumericImpl,
        ColorMetricsAccessor::RgbaImpl,
        ColorMetricsAccessor::ResourceColorImpl,
        ColorMetricsAccessor::BlendColorImpl,
        ColorMetricsAccessor::GetColorImpl,
        ColorMetricsAccessor::GetRedImpl,
        ColorMetricsAccessor::GetGreenImpl,
        ColorMetricsAccessor::GetBlueImpl,
        ColorMetricsAccessor::GetAlphaImpl,
    };
    return &ColorMetricsAccessorImpl;
}

}
