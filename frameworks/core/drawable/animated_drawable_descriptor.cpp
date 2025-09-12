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

#include "core/drawable/animated_drawable_descriptor.h"

#include <numeric>

#include "base/error/error_code.h"
#include "base/image/image_source.h"
#include "core/components_ng/base/inspector.h"
#include "core/components_ng/image_provider/image_utils.h"
#include "core/drawable/drawable_descriptor_loader.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace {
namespace {
constexpr int32_t DEFAULT_DURATION = 1000;
} // namespace

DrawableDescriptorLoadResult AnimatedDrawableDescriptor::LoadSync()
{
    std::scoped_lock<std::mutex> lock(loadMutx_);
    if (!pixelMapList_.empty()) {
        auto pixelMap = pixelMapList_[0];
        return { pixelMap->GetWidth(), pixelMap->GetHeight(), 0 };
    }
    if (!info_) {
        LOGW("Must to set resource/base64/file info.");
        return { 0, 0, ERROR_CODE_DRAWABLE_LOADER_ERROR };
    }
    if (imageSize_.width > 0) {
        return { imageSize_.width, imageSize_.height, 0 };
    }
    auto mediaData = DrawableDescriptorLoader::GetInstance()->LoadData(info_);
    rawData_.len = mediaData.len;
    rawData_.data.reset(mediaData.data.release());
    auto imageSource = ImageSource::Create(rawData_.data.get(), rawData_.len);
    if (!imageSource) {
        LOGW("Image source create failed.");
        return { 0, 0, ERROR_CODE_DRAWABLE_LOADER_ERROR };
    }
    auto size = imageSource->GetImageSize();
    imageSize_.width = size.first;
    imageSize_.height = size.second;
    return { size.first, size.second, 0 };
}

void AnimatedDrawableDescriptor::LoadAsync(const LoadCallback&& callback)
{
    NG::ImageUtils::PostToBg(
        [weak = WeakClaim(this), callback = std::move(callback)]() {
            auto self = weak.Upgrade();
            CHECK_NULL_VOID(self);
            auto result = self->LoadSync();
            callback(result);
        },
        "AnimatedDrawableDescriptorLoadAsync");
}

void AnimatedDrawableDescriptor::ControllAnimation(int32_t nodeId, bool play)
{
    // first: find animator
    auto it = animators_.find(nodeId);
    if (it == animators_.end()) {
        return;
    }
    auto animator = it->second;
    // second: animator operate
    // visible and auto play is true, start to forward.
    if (play && !autoPlay_) {
        FlushUpdateCallbacksByNodeId(0, nodeId);
    }
    if (play && autoPlay_) {
        animator->Forward();
    }
    // invisible, pause animation.
    auto status = animator->GetControlStatus();
    if (!play && status == ControlledAnimator::ControlStatus::RUNNING) {
        animator->Pause();
    }
}

RefPtr<ControlledAnimator> AnimatedDrawableDescriptor::GetControlledAnimator(const std::string& id)
{
    if (animators_.size() == 1) {
        return animators_.begin()->second;
    }
    auto node = ElementRegister::GetInstance()->GetAttachedFrameNodeById(id);
    if (!node) {
        return nullptr;
    }
    auto nodeId = node->GetId();
    auto it = animators_.find(nodeId);
    if (it == animators_.end()) {
        return nullptr;
    }
    return it->second;
}

RefPtr<PixelMap> AnimatedDrawableDescriptor::GetPixelMap()
{
    if (!pixelMapList_.empty()) {
        return pixelMapList_[0];
    }
    auto imageSource = ImageSource::Create(rawData_.data.get(), rawData_.len);
    CHECK_NULL_RETURN(imageSource, nullptr);
    uint32_t errorCode = 0;
    auto pixelMap = imageSource->CreatePixelMap(0, { -1, -1 }, errorCode, {});
    return pixelMap;
}

int32_t AnimatedDrawableDescriptor::GetOriginalWidth()
{
    auto pixelMap = GetPixelMap();
    if (pixelMap) {
        return pixelMap->GetWidth();
    }
    return -1;
}

int32_t AnimatedDrawableDescriptor::GetOriginalHeight()
{
    auto pixelMap = GetPixelMap();
    if (pixelMap) {
        return pixelMap->GetHeight();
    }
    return -1;
}

uint32_t AnimatedDrawableDescriptor::GetFrameCount() const
{
    return frameCount_;
}

int32_t AnimatedDrawableDescriptor::GetIterations() const
{
    return iterations_;
}

int32_t AnimatedDrawableDescriptor::GetTotalDuration()
{
    if (totalDuration_ > 0) {
        return totalDuration_;
    }
    if (pixelMapList_.size() > 0) {
        totalDuration_ = static_cast<int32_t>(pixelMapList_.size()) * DEFAULT_DURATION;
    }
    if (selfDurations_.size() > 0) {
        totalDuration_ = std::accumulate(selfDurations_.begin(), selfDurations_.end(), 0);
    }
    return totalDuration_;
}

std::vector<int32_t> AnimatedDrawableDescriptor::GetDurations()
{
    if (userDurations_.size() > 0) {
        return userDurations_;
    }
    if (totalDuration_ > 0) {
        std::vector<int32_t> result;
        result.resize(GetFrameCount(), totalDuration_ / GetFrameCount());
        return result;
    }
    if (totalDuration_ < 0 && pixelMapList_.size() > 0) {
        std::vector<int32_t> result;
        result.resize(pixelMapList_.size(), DEFAULT_DURATION);
        return result;
    }
    return selfDurations_;
}

void AnimatedDrawableDescriptor::SetDurations(const std::vector<int32_t>& durations)
{
    if (durations.size() == 0) {
        return;
    }
    userDurations_ = durations;
    totalDuration_ = std::accumulate(userDurations_.begin(), userDurations_.end(), 0);
}

void AnimatedDrawableDescriptor::SetTotalDuration(const int32_t totalDuration)
{
    if (totalDuration_ > 0 || totalDuration <= 0) {
        return;
    }
    totalDuration_ = totalDuration;
}

void AnimatedDrawableDescriptor::SetIterations(const int32_t iterations)
{
    if (iterations_ < -1) {
        iterations_ = 1;
        return;
    }
    iterations_ = iterations;
}

void AnimatedDrawableDescriptor::SetDrawableDescriptorInfo(const RefPtr<DrawableDescriptorInfo>& info)
{
    info_ = info;
}

void AnimatedDrawableDescriptor::SetPixelMapList(const std::vector<RefPtr<PixelMap>>& pixelMapList)
{
    pixelMapList_ = pixelMapList;
    frameCount_ = static_cast<uint32_t>(pixelMapList_.size());
}

void AnimatedDrawableDescriptor::CreateParamsFromImageSource(int32_t nodeId)
{
    auto imageSource = ImageSource::Create(rawData_.data.get(), rawData_.len);
    if (!imageSource) {
        return;
    }
    selfDurations_ = imageSource->GetDelayTime();
    frameCount_ = imageSource->GetFrameCount();
    imageSources_.insert({ nodeId, imageSource });
}

void AnimatedDrawableDescriptor::CreateAnimator(int32_t nodeId)
{
    auto animator = AceType::MakeRefPtr<ControlledAnimator>();
    animators_.insert({ nodeId, animator });
    auto durations = GetDurations();
    auto totalDuration = GetTotalDuration();
    auto iterations = GetIterations();
    animator->SetDuration(totalDuration);
    animator->SetIteration(iterations);
    animator->SetFillMode(FillMode::BACKWARDS);
    auto pictureAnimation = std::vector<PictureInfo>();
    for (uint32_t index = 0; index < GetFrameCount(); ++index) {
        pictureAnimation.emplace_back(
            durations[index] / static_cast<float>(totalDuration), static_cast<int32_t>(index));
    }
    animator->AddInterpolator(pictureAnimation);
    animator->AddListener([weak = WeakClaim(this), nodeId](int32_t index) {
        NG::ImageUtils::PostToBg(
            [weak, nodeId, index]() {
                auto drawable = weak.Upgrade();
                CHECK_NULL_VOID(drawable);
                drawable->FlushUpdateCallbacksByNodeId(index, nodeId);
            },
            "FlushUpdateCallbacksByNodeId");
    });
}

void AnimatedDrawableDescriptor::RegisterUpdateCallback(int32_t nodeId, const UpdateCallback&& callback)
{
    CreateParamsFromImageSource(nodeId);
    if (GetFrameCount() <= 0) {
        return;
    }
    CreateAnimator(nodeId);
    updateCallbacks_.insert({ nodeId, callback });
}

void AnimatedDrawableDescriptor::UnRegisterUpdateCallback(int32_t nodeId)
{
    // unregister callbacks and remove animator by node id
    auto it = animators_.find(nodeId);
    if (it != animators_.end()) {
        it->second->Pause();
    }
    std::unique_lock<std::shared_mutex> lock(callMutx_);
    updateCallbacks_.erase(nodeId);
    animators_.erase(nodeId);
    imageSources_.erase(nodeId);
}

void AnimatedDrawableDescriptor::FlushUpdateCallbacksByNodeId(int32_t index, int32_t nodeId)
{
    if (index < 0 || index >= static_cast<int32_t>(GetFrameCount())) {
        return;
    }
    std::shared_lock<std::shared_mutex> lock(callMutx_);
    auto it = updateCallbacks_.find(nodeId);
    if (it == updateCallbacks_.end()) {
        return;
    }
    auto pixelMap = GetFrameByIndex(index, nodeId);
    CHECK_NULL_VOID(pixelMap);
    it->second(pixelMap);
}

RefPtr<PixelMap> AnimatedDrawableDescriptor::GetFrameByIndex(int32_t index, int32_t nodeId)
{
    if (!pixelMapList_.empty()) {
        return pixelMapList_[index];
    }
    auto imageSource = imageSources_[nodeId];
    if (!imageSource) {
        LOGE("Find imageSource failed, nodeId: %{public}d", nodeId);
        return nullptr;
    }
    uint32_t errorCode = 0;
    auto frame = imageSource->CreatePixelMap(index, { -1, -1 }, errorCode, {});
    return frame;
}
} // namespace OHOS::Ace