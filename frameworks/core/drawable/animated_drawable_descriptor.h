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
#include <shared_mutex>
#include <string>
#include <unordered_map>
#include <vector>

#include "base/image/controlled_animator.h"
#include "base/image/image_source.h"
#include "core/drawable/drawable_descriptor.h"
#include "core/drawable/drawable_descriptor_info.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT AnimatedDrawableDescriptor : public DrawableDescriptor {
    DECLARE_ACE_TYPE(AnimatedDrawableDescriptor, DrawableDescriptor);

public:
    AnimatedDrawableDescriptor() = default;
    ~AnimatedDrawableDescriptor() override = default;

    RefPtr<PixelMap> GetPixelMap() override;

    int32_t GetOriginalWidth() override;

    int32_t GetOriginalHeight() override;

    DrawableDescriptorLoadResult LoadSync() override;

    void LoadAsync(const LoadCallback&& callback) override;

    DrawableType GetDrawableType() const override
    {
        return DrawableType::ANIMATED;
    }

    int32_t GetTotalDuration();

    std::vector<int32_t> GetDurations();

    void SetDurations(const std::vector<int32_t>& durations);

    void SetPixelMapList(const std::vector<RefPtr<PixelMap>>& pixelMapList);

    std::vector<RefPtr<PixelMap>> GetPixelMapList() const
    {
        return pixelMapList_;
    }

    uint32_t GetFrameCount() const;

    int32_t GetIterations() const;

    void SetAutoPlay(bool autoPlay)
    {
        autoPlay_ = autoPlay;
    }

    void SetTotalDuration(const int32_t totalDuration);

    void SetIterations(const int32_t iterations);

    void SetDrawableDescriptorInfo(const RefPtr<DrawableDescriptorInfo>& info);

    void ControllAnimation(int32_t nodeId, bool play);

    RefPtr<ControlledAnimator> GetControlledAnimator(const std::string& id);

    void RegisterUpdateCallback(int32_t nodeId, const UpdateCallback&& callback) override;

    void UnRegisterUpdateCallback(int32_t nodeId) override;

private:
    void FlushUpdateCallbacksByNodeId(int32_t index, int32_t nodeId);

    RefPtr<PixelMap> GetFrameByIndex(int32_t index, int32_t nodeId);

    void CreateParamsFromImageSource(int32_t nodeId);

    void CreateAnimator(int32_t nodeId);

    bool autoPlay_ = true;
    int32_t totalDuration_ = -1;
    uint32_t frameCount_ = 0;
    int32_t iterations_ = 1;
    std::vector<int32_t> userDurations_;
    std::vector<int32_t> selfDurations_;
    MediaData rawData_;
    RefPtr<DrawableDescriptorInfo> info_;
    std::vector<RefPtr<PixelMap>> pixelMapList_;
    mutable std::shared_mutex callMutx_;
    mutable std::mutex loadMutx_;
    std::unordered_map<int32_t, RefPtr<ControlledAnimator>> animators_;
    std::unordered_map<int32_t, UpdateCallback> updateCallbacks_;
    std::unordered_map<int32_t, RefPtr<ImageSource>> imageSources_;
};
}; // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_DRAWABLE_ANIMATED_DRAWABLE_DESCRIPTOR_H