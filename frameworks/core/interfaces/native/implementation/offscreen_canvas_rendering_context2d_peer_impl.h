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

#include "arkoala_api_generated.h"
#include "canvas_renderer_peer_impl.h"

#include "core/interfaces/native/utility/peer_utils.h"

namespace OHOS::Ace::NG::GeneratedModifier {

class OffscreenCanvasRenderingContext2DPeerImpl : public CanvasRendererPeerImpl {
protected:
    OffscreenCanvasRenderingContext2DPeerImpl();
    ~OffscreenCanvasRenderingContext2DPeerImpl() = default;

public:
    void SetOptions(double width, double height, const std::optional<RenderingContextSettingsPeer*>& optSettings);
    ImageBitmapPeer* TransferToImageBitmap();
    RefPtr<AceType> GetOffscreenPattern()
    {
        return offscreenPattern_;
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
    double width_ = 0.0;
    double height_ = 0.0;
};

} // namespace OHOS::Ace::NG::GeneratedModifier

struct OffscreenCanvasRenderingContext2DPeer :
    public OHOS::Ace::NG::GeneratedModifier::OffscreenCanvasRenderingContext2DPeerImpl {
protected:
    OffscreenCanvasRenderingContext2DPeer() = default;
    ~OffscreenCanvasRenderingContext2DPeer() override = default;
    friend OHOS::Ace::NG::PeerUtils;
};

#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_OFFSCRN_CANVAS_RENDERING_CNTXT2D_PEER_H
