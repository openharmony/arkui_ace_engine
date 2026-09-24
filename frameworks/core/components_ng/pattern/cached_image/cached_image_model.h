/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2023-2024. All rights reserved.
 */
 
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CACHED_IMAGE_CACHED_IMAGE_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CACHED_IMAGE_CACHED_IMAGE_MODEL_H

#include <mutex>

#include "base/geometry/dimension.h"
#include "base/image/pixel_map.h"
#include "core/image/image_source_info.h"

namespace OHOS::Ace {

class CachedImageModel {
public:
    static CachedImageModel* GetInstance();
    virtual ~CachedImageModel() = default;

    virtual void Create(const std::string& src, RefPtr<PixelMap>& pixmap) = 0;
    virtual void Create(const std::vector<std::string>& sources, uint32_t column) = 0;
    virtual void SetImageSourceSize(const std::pair<Dimension, Dimension>& size) = 0;
    virtual void SetAlt(const ImageSourceInfo& src) = 0;

private:
    static std::unique_ptr<CachedImageModel> instance_;
    static std::mutex mutex_;
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CACHED_IMAGE_CACHED_IMAGE_MODEL_H