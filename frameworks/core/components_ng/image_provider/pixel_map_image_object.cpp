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

#include "core/components_ng/image_provider/pixel_map_image_object.h"

#include "core/components_ng/render/canvas_image.h"

namespace OHOS::Ace::NG {

void PixelMapImageObject::MakeCanvasImage(
    const LoadCallbacks& loadCallbacks, const SizeF& resizeTarget, bool forceResize)
{
    // TODO: support un-decoded pixel map that can specify size.
    // For current situation, pixel map is already decoded.

    // note that this function must be called on ui thread
    if (!pixmap_) {
        LOGW("pixmap is null when PixelMapImageObject try MakeCanvasImage, sourceInfo: %{public}s",
            sourceInfo_.ToString().c_str());
        loadCallbacks.loadFailCallback_(sourceInfo_, "", ImageLoadingCommand::MAKE_CANVAS_IMAGE_FAIL);
        return;
    }
    auto renderTaskHolder = ImageProvider::CreateRenderTaskHolder();
    CHECK_NULL_VOID(renderTaskHolder);
    SetCanvasImage(CanvasImage::Create(pixmap_, renderTaskHolder));
    loadCallbacks.loadSuccessCallback_(sourceInfo_);
}

RefPtr<PixelMapImageObject> PixelMapImageObject::Create(
    const ImageSourceInfo& sourceInfo, const RefPtr<ImageEncodedInfo>& encodedInfo, const RefPtr<ImageData>& data)
{
    if (!data->HasPixelMapData()) {
        LOGE("no decoded pixel map data when try make PixelMapImageObject, sourceInfo: %{public}s",
            sourceInfo.ToString().c_str());
        return nullptr;
    }
    return AceType::MakeRefPtr<NG::PixelMapImageObject>(data->GetPixelMapData(), sourceInfo, encodedInfo->GetImageSize());
}

} // namespace OHOS::Ace::NG
