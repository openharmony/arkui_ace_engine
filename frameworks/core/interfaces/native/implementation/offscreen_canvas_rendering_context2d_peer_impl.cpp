/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/canvas/offscreen_canvas_rendering_context_2d_model_ng.h"
#include "image_bitmap_peer_impl.h"
#include "offscreen_canvas_rendering_context2d_peer_impl.h"
#include "rendering_context_settings_peer.h"

using namespace OHOS::Ace;
namespace OHOS::Ace::NG::GeneratedModifier {
std::mutex OffscreenCanvasRenderingContext2DPeerImpl::mutex_;
std::unordered_map<uint32_t, RefPtr<AceType>> OffscreenCanvasRenderingContext2DPeerImpl::offscreenPatternMap_;
uint32_t OffscreenCanvasRenderingContext2DPeerImpl::offscreenPatternCount_ = 0;

OffscreenCanvasRenderingContext2DPeerImpl::OffscreenCanvasRenderingContext2DPeerImpl()
{
    id_ = offscreenPatternCount_;
#ifdef NG_BUILD
    renderingContext2DModel_ = AceType::MakeRefPtr<NG::OffscreenCanvasRenderingContext2DModelNG>();
#else
    if (Container::IsCurrentUseNewPipeline()) {
        renderingContext2DModel_ = AceType::MakeRefPtr<NG::OffscreenCanvasRenderingContext2DModelNG>();
    } else {
        renderingContext2DModel_ = nullptr;
    }
#endif
}
void OffscreenCanvasRenderingContext2DPeerImpl::SetOptions(
    double width, double height, const std::optional<RenderingContextSettingsPeer*>& optSettings)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    double density = GetDensity();
    if (IfJudgeSpecialValue(width) && IfJudgeSpecialValue(height)) {
        width *= density;
        height *= density;
        SetWidth(width);
        SetHeight(height);
        auto renderingContext = AceType::DynamicCast<OffscreenCanvasRenderingContext2DModel>(renderingContext2DModel_);
        CHECK_NULL_VOID(renderingContext);
        auto offscreenPattern = renderingContext->CreateOffscreenPattern(round(width), round(height));
        CHECK_NULL_VOID(offscreenPattern);
        SetOffscreenPattern(offscreenPattern);
        std::lock_guard<std::mutex> lock(mutex_);
        offscreenPatternMap_[offscreenPatternCount_++] = offscreenPattern;
    }
    if (optSettings && optSettings.value() && optSettings.value()->antialias) {
        bool anti = optSettings.value()->antialias.value();
        SetAnti(anti);
        SetAntiAlias();
    }
    SetDensity();
}
void OffscreenCanvasRenderingContext2DPeerImpl::RemoveOptions()
{
    uint32_t contextId = GetId();
    std::lock_guard<std::mutex> lock(mutex_);
    offscreenPatternMap_.erase(contextId);
}
ImageBitmapPeer* OffscreenCanvasRenderingContext2DPeerImpl::TransferToImageBitmap(ImageBitmapPeer* bitmap)
{
    CHECK_NULL_RETURN(bitmap, nullptr);
    ContainerScope scope(instanceId_);
    auto offscreenCanvasPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(GetOffscreenPattern(id_));
    CHECK_NULL_RETURN(offscreenCanvasPattern, nullptr);
    auto pixelMap = offscreenCanvasPattern->TransferToImageBitmap();
    ImageBitmapPeer::LoadImageConstructor(bitmap, pixelMap);
#ifndef PIXEL_MAP_SUPPORTED
    auto imageData = offscreenCanvasPattern->GetImageData(0, 0, width_, height_);
    CHECK_NULL_RETURN(imageData, nullptr);
    bitmap->SetImageData(std::make_shared<Ace::ImageData>(*imageData));
#endif
    bitmap->SetUnit(GetUnit());
    bitmap->SetWidth(GetWidth());
    bitmap->SetHeight(GetHeight());
    return bitmap;
}
} // namespace OHOS::Ace::NG::GeneratedModifier
