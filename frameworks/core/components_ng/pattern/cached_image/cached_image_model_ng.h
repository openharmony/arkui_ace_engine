/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2023-2024. All rights reserved.
 */

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CACHED_IMAGE_CACHED_IMAGE_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CACHED_IMAGE_CACHED_IMAGE_MODEL_NG_H

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/cached_image/cached_image_model.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT CachedImageModelNG : public CachedImageModel {
public:
    void Create(const std::string& src, RefPtr<PixelMap>& pixMap) override;
    void Create(const std::vector<std::string>& sources, uint32_t column) override;
    void SetImageSourceSize(const std::pair<Dimension, Dimension>& size) override;
    void SetAlt(const ImageSourceInfo& src) override;

    static void SetCachedImageSrc(FrameNode* frameNode, const std::string& src, RefPtr<PixelMap>& pixMap);
    static void SetCachedImageASTC(FrameNode* frameNode, const std::vector<std::string>& sources, uint32_t column);
    static void SetCachedImageAlt(FrameNode* frameNode, RefPtr<PixelMap>& pixelMap);

private:
    void PushFrameNode();
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CACHED_IMAGE_CACHED_IMAGE_MODEL_NG_H