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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_IMAGE_DATA_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_IMAGE_DATA_H

#include "base/image/pixel_map.h"
#include "frameworks/base/memory/ace_type.h"
namespace OHOS::Ace::NG {

class ImageData : public AceType {
    DECLARE_ACE_TYPE(ImageData, AceType);

public:
    ImageData() = default;
    ~ImageData() override = default;
    static RefPtr<ImageData> MakeFromDataWithCopy(const void* data, size_t length);
    // for sk_sp<SkData>
    static RefPtr<ImageData> MakeFromDataWrapper(void* dataWrapper);
    virtual const void* GetDataWrapper() const
    {
        return nullptr;
    };

    virtual size_t GetSize() const = 0;
    virtual const void* GetData() const = 0;
    virtual std::string ToString() const
    {
        return "";
    }

    void SetDfxConfig(int32_t nodeId, int64_t accessibilityId)
    {
        nodeId_ = nodeId;
        accessibilityId_ = accessibilityId;
    }

    int32_t nodeId_ = -1;
    int64_t accessibilityId_ = -1;

    ACE_DISALLOW_COPY_AND_MOVE(ImageData);
};

class PixmapData : public ImageData {
    DECLARE_ACE_TYPE(PixmapData, ImageData);

public:
    explicit PixmapData(const RefPtr<PixelMap>& data) : pixmap_(data) {}
    ~PixmapData() override = default;

    size_t GetSize() const override;
    const void* GetData() const override;
    const RefPtr<PixelMap>& GetPixmap()
    {
        return pixmap_;
    }

    std::string ToString() const override;

private:
    const RefPtr<PixelMap> pixmap_;

    ACE_DISALLOW_COPY_AND_MOVE(PixmapData);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_IMAGE_DATA_H
