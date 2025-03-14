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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_OFFSCRN_CANVAS_RENDERING_CNTXT2D_PEER_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_OFFSCRN_CANVAS_RENDERING_CNTXT2D_PEER_H

#include "canvas_renderer_peer_impl.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {

class OffscreenCanvasRenderingContext2DPeerImpl : public CanvasRendererPeerImpl {
public:
    OffscreenCanvasRenderingContext2DPeerImpl();
    ~OffscreenCanvasRenderingContext2DPeerImpl() override = default;

    void SetOptions(double width, double height, const std::optional<RenderingContextSettingsPeer*>& optSettings);
    void RemoveOptions();
    ImageBitmapPeer* TransferToImageBitmap(ImageBitmapPeer* bitmap);
    static void AddOffscreenCanvasPattern(const RefPtr<AceType>& pattern)
    {
        CHECK_NULL_VOID(pattern);
        std::lock_guard<std::mutex> lock(mutex_);
        offscreenPatternMap_[offscreenPatternCount_++] = pattern;
    }
    static RefPtr<AceType> GetOffscreenPattern(int32_t id)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return offscreenPatternMap_[id];
    }
    uint32_t GetId()
    {
        return id_;
    }
    void SetWidth(double width)
    {
        width_ = width;
    }
    double GetWidth() const
    {
        return width_;
    }
    void SetHeight(double height)
    {
        height_ = height;
    }
    double GetHeight() const
    {
        return height_;
    }

private:
    static std::mutex mutex_;
    uint32_t id_ = 0;
    double width_ = 0.0f;
    double height_ = 0.0f;
    static std::unordered_map<uint32_t, RefPtr<AceType>> offscreenPatternMap_;
    static uint32_t offscreenPatternCount_;
};

} // namespace OHOS::Ace::NG::GeneratedModifier
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_OFFSCRN_CANVAS_RENDERING_CNTXT2D_PEER_H
