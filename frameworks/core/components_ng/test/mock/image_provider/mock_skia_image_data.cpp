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

#ifndef USE_ROSEN_DRAWING
#include "core/components_ng/image_provider/adapter/skia_image_data.h"
#else
#include "core/components_ng/image_provider/adapter/rosen/drawing_image_data.h"
#endif

namespace OHOS::Ace::NG {
static int32_t frameCount { 0 };
SkiaImageData::SkiaImageData(const void* data, size_t length)
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

size_t SkiaImageData::GetSize() const
{
    CHECK_NULL_RETURN(skData_, 0);
    return skData_->size();
}

const void* SkiaImageData::GetData() const
{
    CHECK_NULL_RETURN(skData_, nullptr);
    return skData_->data();
}

sk_sp<SkData> SkiaImageData::GetSkData() const
{
    CHECK_NULL_RETURN(skData_, nullptr);
    return skData_;
}

RefPtr<SvgDomBase> SkiaImageData::MakeSvgDom(const std::optional<Color>& svgFillColor)
{
    return nullptr;
}

std::pair<SizeF, int32_t> SkiaImageData::Parse() const
{
    return { SizeF(1, 1), frameCount };
}

const void* SkiaImageData::GetDataWrapper() const
{
    return nullptr;
}
} // namespace OHOS::Ace::NG
