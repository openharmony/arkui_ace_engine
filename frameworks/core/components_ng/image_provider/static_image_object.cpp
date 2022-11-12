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

#include "core/components_ng/image_provider/static_image_object.h"

namespace OHOS::Ace::NG {

void StaticImageObject::MakeCanvasImage(const LoadCallbacks& loadCallbacks, const SizeF& resizeTarget, bool forceResize)
{
    auto renderTaskHolder = ImageProvider::CreateRenderTaskHolder();
    CHECK_NULL_VOID(renderTaskHolder);
    ImageProvider::MakeCanvasImage(WeakClaim(this), loadCallbacks, resizeTarget, renderTaskHolder, forceResize);
}

RefPtr<StaticImageObject> StaticImageObject::Create(
    const ImageSourceInfo& sourceInfo, const RefPtr<ImageEncodedInfo>& encodedInfo, const RefPtr<ImageData>& data)
{
    return AceType::MakeRefPtr<NG::StaticImageObject>(
        sourceInfo, encodedInfo->GetImageSize(), encodedInfo->GetFrameCount(), data);
}

} // namespace OHOS::Ace::NG
