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

#include "offscreen_canvas_peer.h"
#include "core/common/container_scope.h"
#include "image_bitmap_peer_impl.h"
#include "rendering_context_settings_peer.h"

void OffscreenCanvasPeer::SetOptions(const double cw, const double ch)
{
    OHOS::Ace::ContainerScope scope(OHOS::Ace::Container::CurrentIdSafely());
    double density = GetDensity();
    double fWidth = cw * density;
    double fHeight = ch * density;
    SetWidth(fWidth);
    SetHeight(fHeight);
    offscreenCanvasPattern = OHOS::Ace::AceType::MakeRefPtr<OHOS::Ace::NG::OffscreenCanvasPattern>(
        static_cast<int32_t>(fWidth), static_cast<int32_t>(fHeight));
    offscreenCanvasPattern->IncRefCount();
}
void OffscreenCanvasPeer::RemoveOptions()
{
    CHECK_NULL_VOID(offscreenCanvasPattern);
    offscreenCanvasPattern->DecRefCount();
}
ImageBitmapPeer* OffscreenCanvasPeer::TransferToImageBitmap(ImageBitmapPeer* bitmap)
{
    CHECK_NULL_RETURN(offscreenCanvasPattern, nullptr);
    CHECK_NULL_RETURN(offscreenCanvasContext, nullptr);
    CHECK_NULL_RETURN(bitmap, nullptr);
    OHOS::Ace::ContainerScope scope(OHOS::Ace::Container::CurrentIdSafely());
    auto pixelMap = offscreenCanvasPattern->TransferToImageBitmap();
    ImageBitmapPeer::LoadImageConstructor(bitmap, pixelMap);
#ifndef PIXEL_MAP_SUPPORTED
    auto imageData = offscreenCanvasPattern->GetImageData(0, 0, width, height);
    if (imageData == nullptr) {
        return nullptr;
    }
    bitmap->SetImageData(std::make_shared<OHOS::Ace::ImageData>(*imageData));
#endif
    bitmap->SetUnit(GetUnit());
    bitmap->SetWidth(GetWidth());
    bitmap->SetHeight(GetHeight());
    return bitmap;
}
OffscreenCanvasRenderingContext2DPeer* OffscreenCanvasPeer::GetContext2D(
    OffscreenCanvasRenderingContext2DPeer* offscreenCanvasContextPeer,
    RenderingContextSettingsPeer* offscreenCanvasSettingsPeer)
{
    CHECK_NULL_RETURN(offscreenCanvasContext, nullptr);
    OHOS::Ace::ContainerScope scope(OHOS::Ace::Container::CurrentIdSafely());
    if (isDetached) {
        return nullptr;
    }
    isGetContext = true;
    if (!OHOS::Ace::Container::IsCurrentUseNewPipeline()) {
        return nullptr;
    }
    contextType = ContextType::CONTEXT_2D;
    if (offscreenCanvasPattern == nullptr) {
        return offscreenCanvasContextPeer;
    }
    offscreenCanvasContext =
        reinterpret_cast<OHOS::Ace::NG::GeneratedModifier::OffscreenCanvasRenderingContext2DPeerImpl*>(
            offscreenCanvasContextPeer);
    CHECK_NULL_RETURN(offscreenCanvasContext, nullptr);
    offscreenCanvasContext->SetInstanceId(OHOS::Ace::Container::CurrentId());
    offscreenCanvasContext->SetOffscreenPattern(offscreenCanvasPattern);
    offscreenCanvasContext->AddOffscreenCanvasPattern(offscreenCanvasPattern);
    offscreenCanvasContext->SetWidth(width);
    offscreenCanvasContext->SetHeight(height);
    offscreenCanvasSettings = offscreenCanvasSettingsPeer;
    if (offscreenCanvasSettings && offscreenCanvasContext) {
        if (offscreenCanvasSettings->antialias) {
            bool anti = offscreenCanvasSettings->antialias.value();
            offscreenCanvasContext->SetAnti(anti);
            offscreenCanvasContext->SetAntiAlias();
        }
    }
    offscreenCanvasContext->SetUnit(GetUnit());
    offscreenCanvasContext->SetDensity();
    return offscreenCanvasContextPeer;
}
double OffscreenCanvasPeer::OnGetHeight(double errValue)
{
    OHOS::Ace::ContainerScope scope(OHOS::Ace::Container::CurrentIdSafely());
    if (isDetached) {
        return errValue;
    }
    auto density = GetDensity();
    auto fHeight = GetHeight();
    if (density == 0) {
        return errValue;
    }
    fHeight /= density;
    return fHeight;
}
void OffscreenCanvasPeer::OnSetHeight(double value)
{
    OHOS::Ace::ContainerScope scope(OHOS::Ace::Container::CurrentIdSafely());
    if (isDetached) {
        return;
    }
    CHECK_NULL_VOID(offscreenCanvasPattern);
    double density = GetDensity();
    value *= density;
    if (height != value) {
        height = value;
        offscreenCanvasPattern->UpdateSize(width, height);
        if (offscreenCanvasContext != nullptr) {
            offscreenCanvasContext->SetHeight(height);
        }
    }
}
double OffscreenCanvasPeer::OnGetWidth(double errValue)
{
    OHOS::Ace::ContainerScope scope(OHOS::Ace::Container::CurrentIdSafely());
    if (isDetached) {
        return errValue;
    }
    auto density = GetDensity();
    auto fWidth = GetWidth();
    if (density == 0) {
        return errValue;
    }
    fWidth /= density;
    return fWidth / density;
}
void OffscreenCanvasPeer::OnSetWidth(double value)
{
    OHOS::Ace::ContainerScope scope(OHOS::Ace::Container::CurrentIdSafely());
    if (isDetached) {
        return;
    }
    CHECK_NULL_VOID(offscreenCanvasPattern);
    double density = GetDensity();
    value *= density;
    if (width != value) {
        width = value;
        offscreenCanvasPattern->UpdateSize(width, height);
        if (offscreenCanvasContext != nullptr) {
            offscreenCanvasContext->SetWidth(width);
        }
    }
}
