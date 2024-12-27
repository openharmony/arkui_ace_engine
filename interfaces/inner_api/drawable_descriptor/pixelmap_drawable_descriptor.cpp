/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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

#include "pixelmap_drawable_descriptor.h"
#include "drawable_descriptor_utils.h"

namespace OHOS::Ace::Napi {

DrawableDescriptor::DrawableType PixelmapDrawableDescriptor::GetDrawableType()
{
    return DrawableType::PIXELMAP;
}

void PixelmapDrawableDescriptor::DecodeImage()
{
    if (rawData_ == nullptr) {
        HILOGW("raw data null.");
        return;
    }
    pixelMap_ = rawData_->CreatePixelMap(0, rawData_->GetImageSize(), AIImageQuality::NONE, false);
}

int32_t PixelmapDrawableDescriptor::FetchSync(DrawableInfo& info)
{
    // step1:create iamge loader
    auto imageLoader = DrawableDescriptorUtils::CreateImageLoader(src_);
    if (imageLoader == nullptr) {
        HILOGW("failed to create image loader");
        return ERROR_CODE_FETCH_LOADING_ERROR;
    }
    // step2:load image data to memory
    auto rawData_ = imageLoader->GetImageData(src_);
    if (rawData_ == nullptr) {
        HILOGW("failed to load image data");
        return ERROR_CODE_FETCH_LOADING_ERROR;
    }
    auto size = rawData_->GetImageSize();
    info.originalWidth = size.first;
    info.originalHeight = size.second;
    // step3:decode image data
    DecodeImage();
    if (pixelMap_ == nullptr) {
        HILOGW("failed to decode image data");
        return ERROR_CODE_FETCH_DECODE_ERROR;
    }
    return ERROR_CODE_NO_ERROR;
}
} // namespace OHOS::Ace::Napi