/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_DRAWABLE_LAYERED_DRAWABLE_DESCRIPTOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_DRAWABLE_LAYERED_DRAWABLE_DESCRIPTOR_H

#include <vector>

#include "core/drawable/drawable_descriptor.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT LayeredDrawableDescriptor : public DrawableDescriptor {
public:
    LayeredDrawableDescriptor() = default;
    ~LayeredDrawableDescriptor() = default;
    explicit LayeredDrawableDescriptor(
        const RefPtr<PixelMap>& foreground, const RefPtr<PixelMap>& background, const RefPtr<PixelMap>& mask)
        : foreground_(foreground), background_(background), mask_(mask)
    {}

    DrawableType GetDrawableType() const override
    {
        return DrawableType::LAYERED;
    }

    void SetForeground(const RefPtr<PixelMap>& foreground)
    {
        foreground_ = foreground;
    }

    void SetBackground(const RefPtr<PixelMap>& background)
    {
        background_ = background;
    }

    void SetMask(const RefPtr<PixelMap>& mask)
    {
        mask_ = mask;
    }

    void SetForegroundData(const std::vector<uint8_t>& data)
    {
        foregroundData_ = data;
    }

    void SetBackgroundData(const std::vector<uint8_t>& data)
    {
        backgroundData_ = data;
    }

    void SetMaskData(const std::vector<uint8_t>& data)
    {
        maskData_ = data;
    }

    void SetMaskPath(const std::string& path)
    {
        maskPath_ = path;
    }

    RefPtr<PixelMap> GetPixelMap() override;

    RefPtr<PixelMap> GetForeground();

    RefPtr<PixelMap> GetBackground();

    RefPtr<PixelMap> GetMask();

private:
    void CreatePixelMap() override;

    void CreateForeground();

    void CreateBackground();

    void CreateMask();

    bool CreateMaskByPath();

    bool CreateMaskByData();

    std::string maskPath_;
    std::vector<uint8_t> foregroundData_;
    std::vector<uint8_t> backgroundData_;
    std::vector<uint8_t> maskData_;
    RefPtr<PixelMap> foreground_;
    RefPtr<PixelMap> background_;
    RefPtr<PixelMap> mask_;
    RefPtr<PixelMap> composePixelMap_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_DRAWABLE_LAYERED_DRAWABLE_DESCRIPTOR_H
