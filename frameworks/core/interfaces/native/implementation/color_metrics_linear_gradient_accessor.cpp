/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "arkoala_api_generated.h"
#include "color_metrics_linear_gradient_peer_impl.h"

#include "core/interfaces/native/utility/converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ColorMetricsLinearGradientAccessor {
void DestroyPeerImpl(Ark_ColorMetricsLinearGradient peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_ColorMetricsLinearGradient ConstructImpl(const Array_ColorMetricsStop* colorStops)
{
    ColorMetricsLinearGradientPeer* peer = PeerUtils::CreatePeer<ColorMetricsLinearGradientPeer>();
    CHECK_NULL_RETURN(colorStops, peer);
    for (int32_t i = 0; i < colorStops->length; i++) {
        NG::GradientColor gradientColor;
        auto colorOpt = Converter::OptConvert<Color>(colorStops->array[i].color);
        CHECK_EQUAL_RETURN(colorOpt.has_value(), false, peer);
        Color color = colorOpt.value();
        auto offsetOpt = Converter::OptConvert<CalcDimension>(colorStops->array[i].offset);
        CHECK_EQUAL_RETURN(offsetOpt.has_value(), false, peer);
        CalcDimension offset = offsetOpt.value();
        if (Negative(offset.Value())) {
            offset = Dimension(0.0);
        }
        if (GreatNotEqual(offset.Value(), 1.0)) {
            offset = Dimension(1.0);
        }
        gradientColor.SetLinearColor(LinearColor(color));
        gradientColor.SetDimension(offset);
        peer->gradient.AddColor(gradientColor);
        if (colorStops->length == 1) {
            // If there is only one color, then this color is used for both the begin and end side.
            peer->gradient.AddColor(gradientColor);
        }
    }
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void*>(&DestroyPeerImpl);
}
} // namespace ColorMetricsLinearGradientAccessor
const GENERATED_ArkUIColorMetricsLinearGradientAccessor* GetColorMetricsLinearGradientAccessor()
{
    static const GENERATED_ArkUIColorMetricsLinearGradientAccessor ColorMetricsLinearGradientAccessorImpl {
        ColorMetricsLinearGradientAccessor::DestroyPeerImpl,
        ColorMetricsLinearGradientAccessor::ConstructImpl,
        ColorMetricsLinearGradientAccessor::GetFinalizerImpl,
    };
    return &ColorMetricsLinearGradientAccessorImpl;
}
} // namespace OHOS::Ace::NG::GeneratedModifier
