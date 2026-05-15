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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_DRAWABLE_PIXEL_MAP_DRAWABLE_DESCRIPTOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_DRAWABLE_PIXEL_MAP_DRAWABLE_DESCRIPTOR_H

#include <memory>
#include <mutex>

#include "core/drawable/drawable_descriptor.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT PixelMapDrawableDescriptor : public DrawableDescriptor {
    DECLARE_ACE_TYPE(PixelMapDrawableDescriptor, DrawableDescriptor);
public:
    PixelMapDrawableDescriptor() = default;
    explicit PixelMapDrawableDescriptor(const RefPtr<PixelMap>& pixelmap) : pixelmap_(pixelmap) {}
    ~PixelMapDrawableDescriptor() override = default;

    RefPtr<PixelMap> GetPixelMap() override;

    DrawableDescriptorLoadResult LoadSync() override;

    void LoadAsync(const LoadCallback&& callback) override;

    void SetPixelMap(const RefPtr<PixelMap>& pixelmap)
    {
        pixelmap_ = pixelmap;
    }

    DrawableType GetDrawableType() const override
    {
        return DrawableType::PIXELMAP;
    }

private:
    void CreatePixelMap() override;

    RefPtr<PixelMap> pixelmap_;
    mutable std::mutex loadMutx_;
};
}; // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_DRAWABLE_PIXEL_MAP_DRAWABLE_DESCRIPTOR_H
