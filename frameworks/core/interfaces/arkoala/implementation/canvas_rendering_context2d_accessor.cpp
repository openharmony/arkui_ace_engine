/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/arkoala/utility/converter.h"

#include "canvas_rendering_context2d_peer_impl.h"
#include "drawing_rendering_context_peer_impl.h"

#include "arkoala_api_generated.h"

namespace {
constexpr auto ERROR_VALUE = -1;
} // namespace

namespace OHOS::Ace::NG::Converter {
template<>
inline void AssignCast(std::optional<bool>& dst, const Ark_RenderingContextSettings& src)
{
    dst = Converter::OptConvert<bool>(src.antialias);
}
inline void AssignCast(std::optional<bool>& dst, const Ark_RenderingContextSettings& src)
{
    dst = Converter::OptConvert<bool>(src.antialias);
}
template<>
inline void AssignCast(std::optional<ImageAnalyzerType>& dst, const Ark_ImageAnalyzerType& src)
{
    switch (src) {
        case ARK_IMAGE_ANALYZER_TYPE_TEXT: dst = ImageAnalyzerType::TEXT; break;
        case ARK_IMAGE_ANALYZER_TYPE_SUBJECT: dst = ImageAnalyzerType::SUBJECT; break;
        default: LOGE("Unexpected enum value in Ark_ImageAnalyzerType: %{public}d", src);
    }
}
template<>
std::vector<ImageAnalyzerType> Convert(const Array_ImageAnalyzerType& src)
{
    std::vector<ImageAnalyzerType> dst;
    auto length = Converter::Convert<int>(src.length);
    for (int i = 0; i < length; i++) {
        auto opt = Converter::OptConvert<ImageAnalyzerType>(*(src.array + i));
        if (opt) {
            dst.push_back(*opt);
        }
    }
    return dst;
}

} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CanvasRenderingContext2DAccessor {
static void DestroyPeer(CanvasRenderingContext2DPeerImpl* peerImpl)
{
    if (peerImpl) {
        peerImpl->DecRefCount();
    }
}
CanvasRenderingContext2DPeer* CtorImpl(const Opt_RenderingContextSettings* settings)
{
    CHECK_NULL_RETURN(settings, nullptr);

    auto peerImpl = Referenced::MakeRefPtr<CanvasRenderingContext2DPeerImpl>();
    peerImpl->IncRefCount();
    auto antialias = Converter::OptConvert<bool>(*settings);
    if (antialias) {
        peerImpl->SetAntiAlias(*antialias);
    }
    return reinterpret_cast<CanvasRenderingContext2DPeer*>(Referenced::RawPtr(peerImpl));
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void*>(&DestroyPeer);
}
void ToDataURLImpl(CanvasRenderingContext2DPeer* peer,
                   const Opt_String* type,
                   const Opt_CustomObject* quality)
{
    auto peerImpl = reinterpret_cast<CanvasRenderingContext2DPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(type);
    CHECK_NULL_VOID(quality);

    auto dataUrl = Converter::OptConvert<std::string>(*type);
    if (!dataUrl) {
        return;
    }
    LOGE("ARKOALA CanvasRenderingContext2DPeerImpl::TriggerToDataURL Opt_CustomObject not implemented.");
}
Ark_NativePointer StartImageAnalyzerImpl(CanvasRenderingContext2DPeer* peer,
                                         const Ark_ImageAnalyzerConfig* config)
{
    auto peerImpl = reinterpret_cast<CanvasRenderingContext2DPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, nullptr);
    CHECK_NULL_RETURN(config, nullptr);

    auto vector = Converter::Convert<std::vector<ImageAnalyzerType>>(config->types);
    return peerImpl->TriggerStartImageAnalyzer(vector);
}
void StopImageAnalyzerImpl(CanvasRenderingContext2DPeer* peer)
{
    auto peerImpl = reinterpret_cast<CanvasRenderingContext2DPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerStopImageAnalyzer();
}
Ark_Int32 GetHeightImpl(CanvasRenderingContext2DPeer* peer)
{
    auto peerImpl = reinterpret_cast<CanvasRenderingContext2DPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, ::ERROR_VALUE);
    return peerImpl->TriggerGetHeight();
}
Ark_Int32 GetWidthImpl(CanvasRenderingContext2DPeer* peer)
{
    auto peerImpl = reinterpret_cast<CanvasRenderingContext2DPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, ::ERROR_VALUE);
    return peerImpl->TriggerGetWidth();
}
} // CanvasRenderingContext2DAccessor
const GENERATED_ArkUICanvasRenderingContext2DAccessor* GetCanvasRenderingContext2DAccessor()
{
    static const GENERATED_ArkUICanvasRenderingContext2DAccessor CanvasRenderingContext2DAccessorImpl {
        CanvasRenderingContext2DAccessor::CtorImpl,
        CanvasRenderingContext2DAccessor::GetFinalizerImpl,
        CanvasRenderingContext2DAccessor::ToDataURLImpl,
        CanvasRenderingContext2DAccessor::StartImageAnalyzerImpl,
        CanvasRenderingContext2DAccessor::StopImageAnalyzerImpl,
        CanvasRenderingContext2DAccessor::GetHeightImpl,
        CanvasRenderingContext2DAccessor::GetWidthImpl,
    };
    return &CanvasRenderingContext2DAccessorImpl;
}

}
