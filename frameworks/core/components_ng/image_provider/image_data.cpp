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

#include "core/components_ng/image_provider/image_data.h"

namespace OHOS::Ace::NG {

size_t ImageData::GetSize() const
{
    if (!pixelMap_) {
        return 0;
    }
    return pixelMap_->GetByteCount();
}

const void* ImageData::GetData() const
{
    if (!pixelMap_) {
        return nullptr;
    }
    return pixelMap_->GetPixels();
}

RefPtr<ImageData> ImageData::MakeFromPixelMap(const RefPtr<PixelMap>& pixelMap)
{
    if (!pixelMap) {
        return nullptr;
    }
    return MakeRefPtr<ImageData>(pixelMap);
}

bool ImageData::HasPixelMapData()
{
    return pixelMap_;
}

RefPtr<PixelMap>& ImageData::GetPixelMapData()
{
    return pixelMap_;
}

} // namespace OHOS::Ace::NG
