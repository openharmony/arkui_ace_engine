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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_STATIC_IMAGE_OBJECT_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_STATIC_IMAGE_OBJECT_NG_H

#include "core/components_ng/image_provider/image_object.h"

namespace OHOS::Ace::NG {

class StaticImageObject : public ImageObject {
    DECLARE_ACE_TYPE(StaticImageObject, ImageObject);

public:
    StaticImageObject(
        const ImageSourceInfo& sourceInfo, const SizeF& imageSize, int32_t frameCount, const RefPtr<ImageData>& data)
        : ImageObject(sourceInfo, imageSize, frameCount, data)
    {}
    ~StaticImageObject() override = default;

    void MakeCanvasImage(const LoadCallbacks& loadCallbacks, const SizeF& resizeTarget, bool forceResize) override;

    static RefPtr<StaticImageObject> Create(const ImageSourceInfo& sourceInfo, const RefPtr<ImageEncodedInfo>& encodedInfo,
        const RefPtr<ImageData>& data);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_STATIC_IMAGE_OBJECT_NG_H
