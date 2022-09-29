/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_IMAGE_IMAGE_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_IMAGE_IMAGE_PATTERN_H

#include <memory>

#include "base/memory/referenced.h"
#include "core/components_ng/pattern/image/image_event_hub.h"
#include "core/components_ng/pattern/image/image_layout_algorithm.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_render_property.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/canvas_image.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ImagePattern : public Pattern {
    DECLARE_ACE_TYPE(ImagePattern, Pattern);

public:
    explicit ImagePattern(const ImageSourceInfo& imageSourceInfo);
    ~ImagePattern() override = default;

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override;

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<ImageLayoutProperty>();
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<ImageRenderProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx_, altLoadingCtx_);
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<ImageEventHub>();
    }

    // Called on main thread to check if need rerender of the content.
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    FocusType GetFocusType() override
    {
        return FocusType::NODE;
    }
    bool GetFocusable() override
    {
        return false;
    }

private:
    void OnModifyDone() override;
    void OnActive() override
    {
        isActive_ = true;
    }

    void OnInActive() override
    {
        isActive_ = false;
    }

    void PaintImage(RenderContext* renderContext, const OffsetF& offset);

    void OnImageDataReady();
    void OnImageLoadFail();
    void OnImageLoadSuccess();
    void CacheImageObject();

    DataReadyNotifyTask CreateDataReadyCallback();
    LoadSuccessNotifyTask CreateLoadSuccessCallback();
    LoadFailNotifyTask CreateLoadFailCallback();

    DataReadyNotifyTask CreateDataReadyCallbackForAlt();
    LoadSuccessNotifyTask CreateLoadSuccessCallbackForAlt();
    LoadFailNotifyTask CreateLoadFailCallbackForAlt();

    RefPtr<ImageLoadingContext> loadingCtx_;
    RefPtr<CanvasImage> lastCanvasImage_;
    RectF lastDstRect_;
    RectF lastSrcRect_;

    bool isActive_ = false;

    // clear alt data after [OnImageLoadSuccess] being called
    RefPtr<ImageLoadingContext> altLoadingCtx_;
    RefPtr<CanvasImage> lastAltCanvasImage_;
    std::unique_ptr<RectF> lastAltDstRect_;
    std::unique_ptr<RectF> lastAltSrcRect_;

    ACE_DISALLOW_COPY_AND_MOVE(ImagePattern);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_IMAGE_IMAGE_PATTERN_H
