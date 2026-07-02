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

#include "core/common/container.h"
#include "core/interfaces/native/implementation/canvas_runtime_bridge.h"
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
    auto* bridge = GetCanvasRuntimeBridgeFromModule();
    if (bridge && bridge->createOffscreenCanvasRenderingContext2DModel) {
        renderingContext2DModel_ = bridge->createOffscreenCanvasRenderingContext2DModel();
    }
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
        auto* bridge = GetCanvasRuntimeBridgeFromModule();
        CHECK_NULL_VOID(bridge);
        CHECK_NULL_VOID(bridge->createOffscreenPattern);
        auto offscreenPattern = bridge->createOffscreenPattern(round(width), round(height));
        CHECK_NULL_VOID(offscreenPattern);
        SetOffscreenPattern(offscreenPattern);
        AddOffscreenCanvasPattern(offscreenPattern);
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
ImageBitmapPeer* OffscreenCanvasRenderingContext2DPeerImpl::TransferToImageBitmap()
{
    ContainerScope scope(instanceId_);
    auto offscreenCanvasPattern = GetOffscreenPattern(id_);
    CHECK_NULL_RETURN(offscreenCanvasPattern, nullptr);
    auto* bridge = GetCanvasRuntimeBridgeFromModule();
    CHECK_NULL_RETURN(bridge, nullptr);
    CHECK_NULL_RETURN(bridge->transferOffscreenToImageBitmap, nullptr);
    auto pixelMap = bridge->transferOffscreenToImageBitmap(offscreenCanvasPattern);
    auto bitmap = PeerUtils::CreatePeer<ImageBitmapPeer>();
    ImageBitmapPeer::LoadImageConstructor(bitmap, pixelMap);
#ifndef PIXEL_MAP_SUPPORTED
    CHECK_NULL_RETURN(bridge->getOffscreenImageData, bitmap);
    auto imageData = bridge->getOffscreenImageData(offscreenCanvasPattern, 0, 0, width_, height_);
    bitmap->SetImageData(std::make_shared<Ace::ImageData>(*imageData));
#endif
    bitmap->SetUnit(GetUnit());
    bitmap->SetWidth(GetWidth());
    bitmap->SetHeight(GetHeight());
    return bitmap;
}
} // namespace OHOS::Ace::NG::GeneratedModifier
