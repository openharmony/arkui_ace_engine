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

#include "core/components_ng/pattern/image/image_pattern.h"

#include "base/utils/utils.h"
#include "core/components_ng/pattern/image/image_paint_method.h"
#include "core/components_ng/render/image_painter.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {

ImageObjSuccessCallback ImagePattern::CreateSuccessCallback()
{
    auto task = [weak = WeakClaim(this)](const ImageSourceInfo& info, const RefPtr<ImageObject>& image) {
        auto pattern = weak.Upgrade();
        if (pattern && pattern->isActive_) {
            pattern->OnImageObjectReady(image);
        }
    };
    return task;
}

UploadSuccessCallback ImagePattern::CreateUploadSuccessCallback()
{
    auto task = [weak = WeakClaim(this)](
#ifdef NG_BUILD
                    const ImageSourceInfo& imageSourceInfo, RefPtr<CanvasImage> image) {
#else
                    const ImageSourceInfo& imageSourceInfo, fml::RefPtr<flutter::CanvasImage> image) {
#endif
        auto pattern = weak.Upgrade();
        if (pattern && pattern->isActive_) {
            pattern->OnImageDataUploaded(image);
        }
    };
    return task;
}

FailedCallback ImagePattern::CreateFailedCallback()
{
    // TODO: impl
    return nullptr;
}

OnPostBackgroundTask ImagePattern::CreateOnBackgroundTaskPostCallback()
{
    auto task = [weak = WeakClaim(this)](const CancelableTask& task) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->SetFetchImageObjBackgroundTask(task);
        }
    };
    return task;
}

#ifdef NG_BUILD
void ImagePattern::OnImageDataUploaded(RefPtr<CanvasImage> image)
#else
void ImagePattern::OnImageDataUploaded(fml::RefPtr<flutter::CanvasImage> image)
#endif
{
    LOGD("on image data uploaded, %{public}s.", imageObject_->GetSourceInfo().GetSrc().c_str());
#ifdef NG_BUILD
    image_ = image;
#else
    image_ = CanvasImage::Create(&image);
#endif
    if (imageObject_ && (imageObject_->GetSourceInfo().GetSrcType() != SrcType::MEMORY) &&
        imageObject_->IsSingleFrame()) {
        imageObject_->ClearData();
    }
    CacheImageObject();
    auto host = frameNode_.Upgrade();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    host->RequestNextFrame();
}

void ImagePattern::CacheImageObject()
{
    auto host = frameNode_.Upgrade();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);

    auto imageCache = context->GetImageCache();
    if (imageCache && imageObject_ && imageObject_->IsSingleFrame()) {
        imageCache->CacheImgObj(imageObject_->GetSourceInfo().ToString(), imageObject_);
    }
}

void ImagePattern::OnImageObjectReady(const RefPtr<ImageObject>& imageObj)
{
    LOGD("on image object ready: %{public}s", imageObj->GetSourceInfo().GetSrc().c_str());
    imageObject_ = imageObj;
    auto host = frameNode_.Upgrade();
    CHECK_NULL_VOID(host);

    const auto& geometryNode = host->GetGeometryNode();
    if (!geometryNode->GetContent()) {
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        host->RequestNextFrame();
        return;
    }
}

RefPtr<NodePaintMethod> ImagePattern::CreateNodePaintMethod()
{
    CHECK_NULL_RETURN(image_, nullptr);
    CHECK_NULL_RETURN(imageObject_, nullptr);
    auto size = imageObject_->GetImageSize();
    SizeF imageSize = { static_cast<float>(size.Width()), static_cast<float>(size.Height()) };
    return MakeRefPtr<ImagePaintMethod>(image_, imageSize);
}

bool ImagePattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout)
{
    if (skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }
    return image_;
}

} // namespace OHOS::Ace::NG