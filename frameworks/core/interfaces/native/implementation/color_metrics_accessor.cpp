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
namespace ColorMetricsAccessor {
void DestroyPeerImpl(Ark_ColorMetrics peer)
{
    auto peerImpl = reinterpret_cast<ColorMetricsPeerImpl *>(peer);
    if (peerImpl) {
        delete peerImpl;
    }
}
Ark_ColorMetrics ConstructImpl()
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_ColorMetrics NumericImpl(const Ark_Number* value)
{
    return {};
}
Ark_ColorMetrics RgbaImpl(const Ark_Number* red,
                          const Ark_Number* green,
                          const Ark_Number* blue,
                          const Ark_Number* alpha)
{
    return {};
}
Ark_ColorMetrics ResourceColorImpl(const Ark_ResourceColor* color)
{
    return {};
}
Ark_ColorMetrics BlendColorImpl(Ark_ColorMetrics peer,
                                Ark_ColorMetrics overlayColor)
{
    return {};
}
Ark_String ColorImpl(Ark_ColorMetrics peer)
{
    return {};
}
Ark_Number RedImpl(Ark_ColorMetrics peer)
{
    return {};
}
Ark_Number GreenImpl(Ark_ColorMetrics peer)
{
    return {};
}
Ark_Number BlueImpl(Ark_ColorMetrics peer)
{
    return {};
}
Ark_Number AlphaImpl(Ark_ColorMetrics peer)
{
    return {};
}
} // ColorMetricsAccessor
const GENERATED_ArkUIColorMetricsAccessor* GetColorMetricsAccessor()
{
    static const GENERATED_ArkUIColorMetricsAccessor ColorMetricsAccessorImpl {
        ColorMetricsAccessor::DestroyPeerImpl,
        ColorMetricsAccessor::ConstructImpl,
        ColorMetricsAccessor::GetFinalizerImpl,
        ColorMetricsAccessor::NumericImpl,
        ColorMetricsAccessor::RgbaImpl,
        ColorMetricsAccessor::ResourceColorImpl,
        ColorMetricsAccessor::BlendColorImpl,
        ColorMetricsAccessor::ColorImpl,
        ColorMetricsAccessor::RedImpl,
        ColorMetricsAccessor::GreenImpl,
        ColorMetricsAccessor::BlueImpl,
        ColorMetricsAccessor::AlphaImpl,
    };
    return &ColorMetricsAccessorImpl;
}

struct ColorMetricsPeer {
    virtual ~ColorMetricsPeer() = default;
};
}
