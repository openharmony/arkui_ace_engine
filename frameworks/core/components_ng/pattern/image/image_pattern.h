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
    ImagePattern() = default;
    ~ImagePattern() override = default;

    RenderWrapper::ContentPaintImpl CreateContentPaintImpl() override
    {
        auto task = [weak = WeakClaim(this)](RenderContext* renderContext, const OffsetF& offset) {
            auto pattern = weak.Upgrade();
            if (pattern) {
                pattern->PaintImage(renderContext, offset);
            }
        };
        return task;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<ImageLayoutProperty>();
    }

    RefPtr<PaintProperty> CreateRenderProperty() override
    {
        return MakeRefPtr<ImageRenderProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        auto layoutAlgorithm = MakeRefPtr<ImageLayoutAlgorithm>(CreateSuccessCallback(), CreateUploadSuccessCallback(),
            CreateFailedCallback(), CreateOnBackgroundTaskPostCallback());
        layoutAlgorithm->SetImageObject(imageObject_);
        return layoutAlgorithm;
    }

        // Called on main thread to check if need rerender of the content.
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout) override;

private:
    void OnActive() override
    {
        isActive_ = true;
    }

    void OnInActive() override
    {
        fetchImageObjTask_.Reset(nullptr);
        isActive_ = false;
    }

    void PaintImage(RenderContext* renderContext, const OffsetF& offset);

    void SetFetchImageObjBackgroundTask(const CancelableTask& task)
    {
        if (fetchImageObjTask_) {
            fetchImageObjTask_.Cancel(false);
        }
        fetchImageObjTask_ = task;
    }

    void OnImageObjectReady(const RefPtr<ImageObject>& imageObj);
    // TODO: add adapter for image.
    void OnImageDataUploaded(fml::RefPtr<flutter::CanvasImage> image);
    void CacheImageObject();

    ImageObjSuccessCallback CreateSuccessCallback();
    UploadSuccessCallback CreateUploadSuccessCallback();
    FailedCallback CreateFailedCallback();
    OnPostBackgroundTask CreateOnBackgroundTaskPostCallback();

    RefPtr<ImageObject> imageObject_;
    RefPtr<CanvasImage> image_;
    CancelableTask fetchImageObjTask_;
    bool isActive_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(ImagePattern);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_IMAGE_IMAGE_PATTERN_H
