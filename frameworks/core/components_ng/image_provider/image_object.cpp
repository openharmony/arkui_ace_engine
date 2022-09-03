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

#include "core/components_ng/image_provider/image_object.h"

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void ImageObject::SetCanvasImage(const RefPtr<CanvasImage>& canvasImage)
{
    canvasImage_ = canvasImage;
}

const RefPtr<CanvasImage>& ImageObject::GetCanvasImage() const
{
    return canvasImage_;
}

std::string ImageObject::GenerateCacheKey(const ImageSourceInfo& srcInfo, const SizeF& targetImageSize)
{
    return srcInfo.GetCacheKey() + std::to_string(static_cast<int32_t>(targetImageSize.Width())) +
           std::to_string(static_cast<int32_t>(targetImageSize.Height()));
}

const SizeF& ImageObject::GetImageSize() const
{
    return imageSize_;
}

int32_t ImageObject::GetFrameCount() const
{
    return frameCount_;
}

bool ImageObject::IsSingleFrame() const
{
    return frameCount_ == 1;
}

const ImageSourceInfo& ImageObject::GetSourceInfo() const
{
    return sourceInfo_;
}

const RefPtr<ImageData>& ImageObject::GetData() const
{
    return data_;
}

void ImageObject::SetData(const RefPtr<ImageData>& data)
{
    data_ = data;
}

void ImageObject::ClearData()
{
    data_ = nullptr;
}

void StaticImageObject::MakeCanvasImage(const LoadCallbacks& loadCallbacks, const SizeF& resizeTarget, bool forceResize)
{
    auto renderTaskHolder = ImageProvider::CreateRenderTaskHolder();
    CHECK_NULL_VOID(renderTaskHolder);
    ImageProvider::MakeCanvasImage(WeakClaim(this), loadCallbacks, resizeTarget, renderTaskHolder, forceResize);
}

} // namespace OHOS::Ace::NG
