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

#include "core/components_ng/pattern/image_animator/image_animator_pattern.h"

#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {

constexpr uint32_t DEFAULT_DURATION = 1000; // ms

} // namespace

ImageAnimatorPattern::ImageAnimatorPattern()
{
    animator_ = AceType::MakeRefPtr<Animator>(PipelineContext::GetCurrentContext());
    animator_->SetFillMode(FillMode::FORWARDS);
    animator_->SetDuration(DEFAULT_DURATION);
}

RefPtr<PictureAnimation<int32_t>> ImageAnimatorPattern::CreatePictureAnimation(int32_t size)
{
    auto pictureAnimation = MakeRefPtr<PictureAnimation<int32_t>>();

    if (durationTotal_ > 0) {
        for (int32_t index = 0; index < size; ++index) {
            pictureAnimation->AddPicture(images_[index].duration / static_cast<float>(durationTotal_), index);
        }
        animator_->SetDuration(durationTotal_);
    } else {
        for (int32_t index = 0; index < size; ++index) {
            pictureAnimation->AddPicture(NORMALIZED_DURATION_MAX / static_cast<float>(size), index);
        }
    }

    pictureAnimation->AddListener([weak = WeakClaim(this)](int32_t index) {
        auto imageAnimator = weak.Upgrade();
        CHECK_NULL_VOID(imageAnimator);
        auto frameNode = imageAnimator->GetHost();
        CHECK_NULL_VOID(frameNode);
        auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
        CHECK_NULL_VOID(imageFrameNode);
        auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageLayoutProperty);
        imageLayoutProperty->UpdateImageSourceInfo(ImageSourceInfo(imageAnimator->images_[index].src));
        imageFrameNode->MarkModifyDone();

        MarginProperty margin;
        if (!imageAnimator->fixedSize_) {
            margin.left = CalcLength(imageAnimator->images_[index].left);
            margin.top = CalcLength(imageAnimator->images_[index].top);
            imageLayoutProperty->UpdateMargin(margin);
            CalcSize realSize = { CalcLength(imageAnimator->images_[index].width),
                CalcLength(imageAnimator->images_[index].height) };
            imageLayoutProperty->UpdateUserDefinedIdealSize(realSize);
            imageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_CONTENT);
            return;
        }
        margin.SetEdges(CalcLength(0.0));
        imageLayoutProperty->UpdateMargin(margin);
        imageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    });
    return pictureAnimation;
}

void ImageAnimatorPattern::OnModifyDone()
{
    auto size = static_cast<int32_t>(images_.size());
    if (size <= 0) {
        LOGE("image size is less than 0.");
        return;
    }
    if (status_ == Animator::Status::IDLE || status_ == Animator::Status::STOPPED) {
        auto frameNode = GetHost();
        CHECK_NULL_VOID(frameNode);
        auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
        CHECK_NULL_VOID(imageFrameNode);
        ImageProperties childImage = isReverse_ ? images_.back() : images_.front();
        auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageLayoutProperty);
        imageLayoutProperty->UpdateImageSourceInfo(ImageSourceInfo(childImage.src));
        imageFrameNode->MarkModifyDone();
    }

    if (imagesChangedFlag_) {
        animator_->ClearInterpolators();
        animator_->AddInterpolator(CreatePictureAnimation(size));
        imagesChangedFlag_ = false;
    }
    if (firstUpdateEvent_) {
        UpdateEventCallback();
        firstUpdateEvent_ = false;
    }

    switch (status_) {
        case Animator::Status::IDLE:
            animator_->Cancel();
            break;
        case Animator::Status::PAUSED:
            animator_->Pause();
            break;
        case Animator::Status::STOPPED:
            animator_->Stop();
            break;
        default:
            isReverse_ ? animator_->Backward() : animator_->Forward();
    }
}

void ImageAnimatorPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetRenderContext();
    CHECK_NULL_VOID(context);
    context->SetClipToFrame(true);
}

void ImageAnimatorPattern::UpdateEventCallback()
{
    auto eventHub = GetEventHub<ImageAnimatorEventHub>();
    CHECK_NULL_VOID(eventHub);

    animator_->ClearAllListeners();
    auto startEvent = eventHub->GetStartEvent();
    if (startEvent != nullptr) {
        animator_->AddStartListener([startEvent] { startEvent(); });
    }

    auto stopEvent = eventHub->GetStopEvent();
    if (stopEvent != nullptr) {
        animator_->AddStopListener([stopEvent] { stopEvent(); });
    }

    auto pauseEvent = eventHub->GetPauseEvent();
    if (pauseEvent != nullptr) {
        animator_->AddPauseListener([pauseEvent] { pauseEvent(); });
    }

    auto repeatEvent = eventHub->GetRepeatEvent();
    if (repeatEvent != nullptr) {
        animator_->AddRepeatListener([repeatEvent] { repeatEvent(); });
    }

    auto cancelEvent = eventHub->GetCancelEvent();
    if (cancelEvent != nullptr) {
        animator_->AddIdleListener([cancelEvent] { cancelEvent(); });
    }
}

} // namespace OHOS::Ace::NG
