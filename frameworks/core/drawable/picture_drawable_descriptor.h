/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_DRAWABLE_PICTURE_DRAWABLE_DESCRIPTOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_DRAWABLE_PICTURE_DRAWABLE_DESCRIPTOR_H

#include <unordered_map>

#include "base/image/picture.h"
#include "base/image/contrast_enhancer_image.h"
#include "core/drawable/drawable_descriptor.h"

namespace OHOS::Ace {
struct Rectangle {
    int32_t x = 0;
    int32_t y = 0;
    int32_t width = 0;
    int32_t height = 0;
};

struct HdrCompositionConfig {
    Rectangle rect;
};

class ACE_FORCE_EXPORT PictureDrawableDescriptor : public DrawableDescriptor {
    DECLARE_ACE_TYPE(PictureDrawableDescriptor, DrawableDescriptor);

public:
    PictureDrawableDescriptor() = default;
    explicit PictureDrawableDescriptor(const RefPtr<Picture>& picture);
    ~PictureDrawableDescriptor() override = default;

    DrawableType GetDrawableType() const override
    {
        return DrawableType::PICTURE;
    }

    void SetPicture(const RefPtr<Picture>& picture);

    void SetHdrComposition(const HdrCompositionConfig& config);

    RefPtr<PixelMap> GetPixelMap() override;
    DrawableDescriptorLoadResult LoadSync() override;
    void LoadAsync(const LoadCallback&& callback) override;

    void RegisterUpdateCallback(int32_t nodeId, const UpdateCallback&& callback) override;

    void UnRegisterUpdateCallback(int32_t nodeId) override;

    void Invalidate() override;

private:
    bool IsHdrConfigValid() const;
    RefPtr<PixelMap> DoComposeFOV();

    RefPtr<Picture> picture_;
    RefPtr<PixelMap> cachedPixelMap_;
    std::unordered_map<int32_t, UpdateCallback> updateCallbacks_;
    HdrCompositionConfig hdrConfig_;
    RefPtr<ContrastEnhancerImage> enhancer_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_DRAWABLE_PICTURE_DRAWABLE_DESCRIPTOR_H
