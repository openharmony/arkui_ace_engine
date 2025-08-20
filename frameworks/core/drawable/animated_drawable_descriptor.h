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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_DRAWABLE_ANIMATED_DRAWABLE_DESCRIPTOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_DRAWABLE_ANIMATED_DRAWABLE_DESCRIPTOR_H

#include <memory>
#include <vector>

#include "core/drawable/drawable_descriptor.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT AnimatedDrawableDescriptor : public DrawableDescriptor {
public:
    AnimatedDrawableDescriptor() = default;
    ~AnimatedDrawableDescriptor() override = default;

    RefPtr<PixelMap> GetPixelMap() override;

    int32_t GetTotalDuration();

    void SetDurations(const std::vector<int32_t>& durations);

    std::vector<int32_t> GetDurations();

    DrawableType GetDrawableType() const override
    {
        return DrawableType::ANIMATED;
    }

    void SetRawData(uint8_t* data, size_t len)
    {
        rawData_.data.reset(data);
        rawData_.len = len;
    }

    std::vector<RefPtr<PixelMap>> GetPixelMapList()
    {
        return pixelMapList_;
    }

    void SetPixelMapList(const std::vector<RefPtr<PixelMap>> pixelMapList)
    {
        pixelMapList_ = pixelMapList;
    }

    int32_t GetIterations() const
    {
        return iterations_;
    }

    void SetTotalDuration(const int32_t totalDuration)
    {
        totalDuration_ = totalDuration;
    }

    void SetIterations(const int32_t iterations)
    {
        iterations_ = iterations;
    }

private:
    int32_t totalDuration_ = -1;
    int32_t iterations_ = 1;
    MediaData rawData_;
    std::vector<int32_t> durations_;
    std::vector<RefPtr<PixelMap>> pixelMapList_;
};
}; // namesapce OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_DRAWABLE_ANIMATED_DRAWABLE_DESCRIPTOR_H
