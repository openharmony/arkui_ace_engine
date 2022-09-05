/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_MODEL_NG_CPP
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_MODEL_NG_CPP

#include "core/components_ng/pattern/image/image_model_ng.h"

#include "core/components/image/image_event.h"
#include "core/components_ng/pattern/image/image_view.h"

namespace OHOS::Ace::NG {

#define SET_PROP_FOR_NG(propName, propType, propValue) \
    ImageView::Set##propName(static_cast<propType>(propValue));

void ImageModelNG::SetAlt(std::string src)
{
}

void ImageModelNG::SetImageFit(int32_t value)
{
    SET_PROP_FOR_NG(ObjectFit, ImageFit, value);
}

void ImageModelNG::SetMatchTextDirection(bool value)
{
}

void ImageModelNG::SetFitMaxSize(bool value)
{
}

void ImageModelNG::SetOnComplete(std::function<void(const LoadImageSuccessEvent& info)>&& callback)
{
    NG::ImageView::SetOnComplete(std::move(callback));
}

void ImageModelNG::SetOnError(std::function<void(const LoadImageFailEvent& info)>&& callback)
{
    NG::ImageView::SetOnError(std::move(callback));
}

void ImageModelNG::SetSvgAnimatorFinishEvent(std::function<void()>&& callback)
{
}

void ImageModelNG::Create(std::string src, bool noPixMap, RefPtr<PixelMap>& pixMap)
{
    NG::ImageView::Create(src);
}

void ImageModelNG::SetImageSourceSize(std::pair<Dimension, Dimension> size)
{
    NG::ImageView::SetImageSourceSize(size);
}

void ImageModelNG::SetImageFill(Color color)
{
}

void ImageModelNG::SetImageInterpolation(ImageInterpolation iterpolation)
{
    SET_PROP_FOR_NG(ImageInterpolation, ImageInterpolation, iterpolation);
}

void ImageModelNG::SetImageRepeat(ImageRepeat imageRepeat)
{
    SET_PROP_FOR_NG(ImageRepeat, ImageRepeat, imageRepeat);
}

void ImageModelNG::SetImageRenderMode(ImageRenderMode imageRenderMode)
{
    SET_PROP_FOR_NG(ImageRenderMode, ImageRenderMode, imageRenderMode);
}

bool ImageModelNG::IsSrcSvgImage()
{
    return false;
}

void ImageModelNG::SetAutoResize(bool autoResize)
{
    SET_PROP_FOR_NG(AutoResize, bool, autoResize);
}

void ImageModelNG::SetSyncMode(bool syncMode)
{
}

void ImageModelNG::SetColorFilterMatrix(const std::vector<float>& matrix)
{
}

void ImageModelNG::SetOnDragStartId(const OnDragFunc& onDragStartId)
{
}

void ImageModelNG::SetOnDragEnterId(const OnDropFunc&  onDragStartId)
{
}

void ImageModelNG::SetOnDragLeaveId(const OnDropFunc& onDragStartId)
{
}

void ImageModelNG::SetOnDragMoveId(const OnDropFunc& onDragMoveId)
{
}

void ImageModelNG::SetOnDropId(const OnDropFunc& onDropId)
{
}

void ImageModelNG::SetCopyOption(const CopyOptions& copyOption)
{
}

bool ImageModelNG::UpdateDragItemInfo(DragItemInfo& itemInfo)
{
    return false;
}

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_MODEL_NG_CPP
