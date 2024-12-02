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

size_t PixmapData::GetSize() const
{
    return pixmap_ ? pixmap_->GetByteCount() : 0;
}
const void* PixmapData::GetData() const
{
    return pixmap_ ? pixmap_->GetPixels() : nullptr;
}

std::string PixmapData::ToString() const
{
    if (pixmap_) {
        return "PixmapData-> pixelMapId: " + pixmap_->GetId() + ",[width*height]:" + "[" +
               std::to_string(pixmap_->GetWidth()) + "*" + std::to_string(pixmap_->GetHeight()) + "]" +
               ", ByteCount: " + std::to_string(pixmap_->GetByteCount()) + "(B)";
    }
    return "";
}
} // namespace OHOS::Ace::NG
