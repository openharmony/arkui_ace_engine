/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components/common/layout/constants.h"
#include "core/components_ng/image_provider/adapter/drawing_image_data.h"

namespace OHOS::Ace::NG {

static int32_t frameCount { 0 };

DrawingImageData::DrawingImageData(const void* data, size_t length)
{
    frameCount = length;
}

RefPtr<ImageData> ImageData::MakeFromDataWithCopy(const void* data, size_t length)
{
    return nullptr;
}

RefPtr<ImageData> ImageData::MakeFromDataWrapper(void* dataWrapper)
{
    return nullptr;
}

size_t DrawingImageData::GetSize() const
{
    CHECK_NULL_RETURN(rsData_, 0);
    return rsData_->GetSize();
}

const void* DrawingImageData::GetData() const
{
    CHECK_NULL_RETURN(rsData_, nullptr);
    return rsData_->GetData();
}

std::shared_ptr<RSData> DrawingImageData::GetRSData() const
{
    CHECK_NULL_RETURN(rsData_, nullptr);
    return rsData_;
}

RefPtr<SvgDomBase> DrawingImageData::MakeSvgDom(const ImageSourceInfo& src)
{
    return nullptr;
}

ImageCodec DrawingImageData::Parse() const
{
    return { SizeF(1, 1), frameCount, ImageRotateOrientation::UP };
}

std::string DrawingImageData::ToString() const
{
    return "";
}
} // namespace OHOS::Ace::NG
