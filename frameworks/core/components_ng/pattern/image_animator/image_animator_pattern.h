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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_IMAGE_ANIMATOR_IMAGE_ANIMATOR_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_IMAGE_ANIMATOR_IMAGE_ANIMATOR_PATTERN_H

#include "core/animation/animator.h"
#include "core/animation/picture_animation.h"
#include "core/components/declaration/image/image_animator_declaration.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/image_animator/image_animator_event_hub.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ImageAnimatorPattern : public Pattern {
    DECLARE_ACE_TYPE(ImageAnimatorPattern, Pattern);

public:
    ImageAnimatorPattern();
    ~ImageAnimatorPattern() override
    {
        animator_ = nullptr;
    }

    struct CacheImageStruct {
        CacheImageStruct() = default;
        CacheImageStruct(const RefPtr<FrameNode>& imageNode) : imageNode(imageNode) {}
        virtual ~CacheImageStruct() = default;
        RefPtr<FrameNode> imageNode;
        int32_t index = 0;
        bool isLoaded = false;
    };

    void OnModifyDone() override;

    void OnAttachToFrameNode() override;

    bool IsAtomicNode() const override
    {
        return true;
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<ImageAnimatorEventHub>();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override;

    void SetImages(std::vector<ImageProperties>&& images)
    {
        if (images_.size() == images.size()) {
            return;
        }
        images_ = std::move(images);
        durationTotal_ = 0;
        for (const auto& childImage : images_) {
            if (!childImage.src.empty() && childImage.duration > 0) {
                durationTotal_ += childImage.duration;
            }
        }
        imagesChangedFlag_ = true;
    }

    void SetStatus(Animator::Status status)
    {
        status_ = status;
    }

    void SetDuration(int32_t duration)
    {
        auto finalDuration = durationTotal_ > 0 ? durationTotal_ : duration;
        if (animator_->GetDuration() == finalDuration) {
            animator_->RemoveRepeatListener(repeatCallbackId_);
            return;
        }
        if (animator_->GetStatus() == Animator::Status::IDLE || animator_->GetStatus() == Animator::Status::STOPPED) {
            animator_->SetDuration(finalDuration);
            animator_->RemoveRepeatListener(repeatCallbackId_);
            return;
        }
        // if animator is running or paused, duration will work next time
        animator_->RemoveRepeatListener(repeatCallbackId_);
        repeatCallbackId_ = animator_->AddRepeatListener([weak = WeakClaim(this), finalDuration]() {
            auto imageAnimator = weak.Upgrade();
            CHECK_NULL_VOID(imageAnimator);
            imageAnimator->animator_->SetDuration(finalDuration);
        });
    }

    void SetIteration(int32_t iteration)
    {
        animator_->SetIteration(iteration);
    }

    void SetFillMode(FillMode fillMode)
    {
        animator_->SetFillMode(fillMode);
    }

    void SetPreDecode(int32_t preDecode) {}

    void SetIsReverse(bool isReverse)
    {
        isReverse_ = isReverse;
    }

    void SetFixedSize(bool fixedSize)
    {
        fixedSize_ = fixedSize;
    }

    void OnInActive() override
    {
        if (status_ == Animator::Status::RUNNING) {
            animator_->Pause();
        }
    }

    void OnActive() override
    {
        if (status_ == Animator::Status::RUNNING && animator_->GetStatus() != Animator::Status::RUNNING) {
            isReverse_ ? animator_->Backward() : animator_->Forward();
        }
    }

private:
    RefPtr<PictureAnimation<int32_t>> CreatePictureAnimation(int32_t size);
    void UpdateEventCallback();
    std::string ImagesToString() const;
    void AdaptSelfSize();
    void SetShowingIndex(int32_t index);
    void UpdateShowingImageInfo(const RefPtr<FrameNode>& imageFrameNode, int32_t index);
    void UpdateCacheImageInfo(CacheImageStruct& cacheImage, int32_t index);
    std::list<CacheImageStruct>::iterator FindCacheImageNode(const std::string& src);
    int32_t GetNextIndex(int32_t preIndex);
    void GenerateCachedImages();
    void AddImageLoadSuccessEvent(const RefPtr<FrameNode>& imageFrameNode);
    static bool IsShowingSrc(const RefPtr<FrameNode>& imageFrameNode, const std::string& src);
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& wrapper, const DirtySwapConfig& config) override;

    RefPtr<Animator> animator_;
    std::vector<ImageProperties> images_;
    std::list<CacheImageStruct> cacheImages_;
    Animator::Status status_ = Animator::Status::IDLE;
    int32_t durationTotal_ = 0;
    int32_t nowImageIndex_ = 0;
    uint64_t repeatCallbackId_ = 0;
    bool isReverse_ = false;
    bool fixedSize_ = true;

    bool imagesChangedFlag_ = false;
    bool firstUpdateEvent_ = true;
    bool isLayouted_ = false;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_IMAGE_ANIMATOR_IMAGE_ANIMATOR_PATTERN_H
