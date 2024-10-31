/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "canvas_rendering_context2d_peer_impl.h"

namespace {
constexpr auto ERROR_VALUE = -1;

} // namespace

namespace OHOS::Ace::NG::Converter {

template<>
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
int32_t Convert(const ImageAnalyzerType& src)
{
    switch (src) {
        case ImageAnalyzerType::TEXT: return 1;
        case ImageAnalyzerType::SUBJECT: return 2;
        default: LOGE("Unexpected enum value in Ark_ImageAnalyzerType: %{public}d", src);
        
    }
    return ERROR_VALUE;
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
void CanvasRenderingContext2DPeerImpl::TriggerToDataURL(const Opt_String* type, const Opt_CustomObject* quality) {
    CHECK_NULL_VOID(type);
    CHECK_NULL_VOID(quality);

    if (!pattern_) {
        LOGE("ARKOALA CanvasRenderingContext2DPeerImpl::TriggerToDataURL pattern "
            "not bound to component.");
        return;
    }

    auto dataUrl = Converter::OptConvert<std::string>(*type);
    if (!dataUrl) {
        return;
    }
    LOGE("ARKOALA CanvasRenderingContext2DPeerImpl::TriggerToDataURL Opt_CustomObject not implemented.");
}

Ark_NativePointer CanvasRenderingContext2DPeerImpl::TriggerStartImageAnalyzer(const Ark_ImageAnalyzerConfig* config) {
    if (isImageAnalyzing_) {
        return nullptr;
    }
    CHECK_NULL_RETURN(config, nullptr);
    if (!pattern_) {
        LOGE("ARKOALA CanvasRenderingContext2DPeerImpl::TriggerStartImageAnalyzer pattern "
             "not bound to component.");
        return nullptr;
    }

    vector_ = Converter::Convert<std::vector<ImageAnalyzerType>>(config->types);
    void* config_ = reinterpret_cast<void*>(&vector_);

    OnAnalyzedCallback onAnalyzed = [weakCtx = WeakClaim(this)](ImageAnalyzerState state) -> void {
        auto ctx = weakCtx.Upgrade();
        CHECK_NULL_VOID(ctx);
        ctx->isImageAnalyzing_ = false;
    };

    isImageAnalyzing_ = true;
    pattern_->StartImageAnalyzer(config_, onAnalyzed);
    LOGE("ARKOALA CanvasRenderingContext2DPeerImpl::TriggerStartImageAnalyzer return pointer not implemented.");
    return 0;
}

void CanvasRenderingContext2DPeerImpl::TriggerStopImageAnalyzer() {
    if (!pattern_) {
        LOGE("ARKOALA CanvasRenderingContext2DPeerImpl::TriggerStopImageAnalyzer pattern "
            "not bound to component.");
        return;
    }
    pattern_->StopImageAnalyzer();
}
Ark_Int32 CanvasRenderingContext2DPeerImpl::TriggerGetHeight() {
    if (!pattern_) {
        LOGE("ARKOALA CanvasRenderingContext2DPeerImpl::TriggerGetHeight pattern "
            "not bound to component.");
        return ::ERROR_VALUE;
    }
    auto height = PipelineBase::Px2VpWithCurrentDensity(pattern_-> GetHeight());
    return  Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(height));
}
Ark_Int32 CanvasRenderingContext2DPeerImpl::TriggerGetWidth() {
    if (!pattern_) {
        LOGE("ARKOALA CanvasRenderingContext2DPeerImpl::TriggerGetWidth pattern "
            "not bound to component.");
        return ::ERROR_VALUE;
    }
    auto width = PipelineBase::Px2VpWithCurrentDensity(pattern_-> GetWidth());
    return  Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(width));
}

} // namespace OHOS::Ace::NG::GeneratedModifier
