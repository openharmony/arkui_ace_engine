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

#include "mock_canvas_image.h"

#include "base/image/pixel_map.h"
#include "core/components_ng/render/adapter/pixelmap_image.h"

namespace OHOS::Ace::NG {
RefPtr<CanvasImage> CanvasImage::Create(void* rawImage)
{
    return nullptr;
}

RefPtr<CanvasImage> CanvasImage::Create()
{
    return nullptr;
}

RefPtr<CanvasImage> CanvasImage::Create(const RefPtr<PixelMap>& pixelMap)
{
    return MakeRefPtr<PixelMapImage>(pixelMap);
}

} // namespace OHOS::Ace::NG
