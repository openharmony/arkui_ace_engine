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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_DRAW_CANVAS_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_DRAW_CANVAS_PEER_IMPL_H

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/image_provider/image_data.h"
#include "core/components_ng/pattern/canvas/offscreen_canvas_paint_method.h"
#include "core/components_ng/pattern/canvas/offscreen_canvas_pattern.h"
#include "arkoala_api_generated.h"
#include "base/image/pixel_map.h"

class DrawingCanvasPeerImpl {
public:
    explicit DrawingCanvasPeerImpl(const OHOS::Ace::RefPtr<OHOS::Ace::PixelMap>& pixelmap)
        : pixelmap_(pixelmap)
    {
        pattern_ = OHOS::Ace::AceType::Claim(new OHOS::Ace::NG::OffscreenCanvasPattern(defaultSize, defaultSize));
        CHECK_NULL_VOID(pixelmap);
        // Setting Offscreen buffer size
        pattern_->UpdateSize(pixelmap->GetWidth(), pixelmap->GetHeight());
        // Setting image data to back buffer canvas
        OHOS::Ace::ImageData image;
        image.pixelMap = pixelmap;
        image.x = 0;
        image.y = 0;
        image.dirtyX = 0;
        image.dirtyY = 0;
        image.dirtyWidth = pixelmap->GetWidth();
        image.dirtyHeight = pixelmap->GetHeight();
        pattern_->PutImageData(image);
    }
    virtual ~DrawingCanvasPeerImpl() {}

    void FillRect(const OHOS::Ace::Rect& rect)
    {
        CHECK_NULL_VOID(pattern_);
        pattern_->FillRect(rect);
    }

    void SetPattern(const OHOS::Ace::RefPtr<OHOS::Ace::NG::OffscreenCanvasPattern>& pattern)
    {
        pattern_ = pattern;
    }

    void SetCanvas(const std::shared_ptr<OHOS::Ace::RSCanvas>& rsCanvas)
    {
        rsCanvas_ = rsCanvas;
    }

    std::shared_ptr<OHOS::Ace::RSCanvas> GetCanvas()
    {
        return rsCanvas_;
    }

private:
    OHOS::Ace::RefPtr<OHOS::Ace::NG::OffscreenCanvasPattern> pattern_;
    std::shared_ptr<OHOS::Ace::RSCanvas> rsCanvas_;
    const OHOS::Ace::RefPtr<OHOS::Ace::PixelMap> pixelmap_;
    static constexpr int defaultSize = 1; // The canvas size should be at least 1x1
};

struct DrawingCanvasPeer : public DrawingCanvasPeerImpl {
    explicit DrawingCanvasPeer(const OHOS::Ace::RefPtr<OHOS::Ace::PixelMap>& pixelmap)
        : DrawingCanvasPeerImpl(pixelmap) {}
    ~DrawingCanvasPeer() override {}
};
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_DRAW_CANVAS_PEER_IMPL_H
