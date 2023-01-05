/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_IMAGE_OBJECT_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_IMAGE_OBJECT_NG_H

#include "base/utils/noncopyable.h"
#include "core/components_ng/image_provider/image_data.h"
#include "core/components_ng/image_provider/image_provider.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/image/image_source_info.h"

namespace OHOS::Ace::NG {

class ImageObject : public virtual AceType {
    DECLARE_ACE_TYPE(ImageObject, AceType);

public:
    ImageObject() = delete;
    ImageObject(
        const ImageSourceInfo& sourceInfo, const SizeF& imageSize, int32_t frameCount, const RefPtr<ImageData>& data)
        : src_(sourceInfo), imageSize_(imageSize), frameCount_(frameCount), data_(data)
    {}
    ~ImageObject() override = default;

    int32_t GetFrameCount() const;
    const SizeF& GetImageSize() const;
    const ImageSourceInfo& GetSourceInfo() const;
    const RefPtr<ImageData>& GetData() const;
    bool IsSingleFrame() const;

    void SetData(const RefPtr<ImageData>& data);
    void SetImageSize(const SizeF& imageSize);
    void ClearData();

    bool IsSupportCache() const
    {
        return src_.IsSupportCache();
    }

    virtual void MakeCanvasImage(
        const RefPtr<ImageLoadingContext>& ctx, const SizeF& resizeTarget, bool forceResize, bool syncLoad) = 0;

protected:
    ImageSourceInfo src_;
    SizeF imageSize_ { -1.0, -1.0 };
    int32_t frameCount_ = 1;
    // no longer needed after making canvas image
    RefPtr<ImageData> data_;

    ACE_DISALLOW_COPY_AND_MOVE(ImageObject);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_IMAGE_OBJECT_NG_H
