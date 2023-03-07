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
#include <string>

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
        imageAnimator->SetShowingIndex(index);
    });
    return pictureAnimation;
}

void ImageAnimatorPattern::SetShowingIndex(int32_t index)
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(imageFrameNode);
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    if (index >= static_cast<int32_t>(images_.size())) {
        LOGW("ImageAnimator update index error, index: %{public}d, size: %{public}zu", index, images_.size());
        return;
    }
    nowImageIndex_ = index;
    imageLayoutProperty->UpdateImageSourceInfo(ImageSourceInfo(images_[index].src));

    MarginProperty margin;
    if (!fixedSize_) {
        margin.left = CalcLength(images_[index].left);
        margin.top = CalcLength(images_[index].top);
        imageLayoutProperty->UpdateMargin(margin);
        CalcSize realSize = { CalcLength(images_[index].width), CalcLength(images_[index].height) };
        imageLayoutProperty->UpdateUserDefinedIdealSize(realSize);
        imageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_CONTENT);
        imageFrameNode->MarkModifyDone();
        return;
    }
    margin.SetEdges(CalcLength(0.0));
    imageLayoutProperty->UpdateMargin(margin);
    imageLayoutProperty->ClearUserDefinedIdealSize(true, true);
    imageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    imageFrameNode->MarkModifyDone();
}

void ImageAnimatorPattern::OnModifyDone()
{
    auto size = static_cast<int32_t>(images_.size());
    if (size <= 0) {
        LOGE("image size is less than 0.");
        return;
    }
    auto index = nowImageIndex_;
    if ((status_ == Animator::Status::IDLE || status_ == Animator::Status::STOPPED) && firstUpdateEvent_) {
        index = isReverse_ ? (size - 1) : 0;
    }
    SetShowingIndex(index);

    if (imagesChangedFlag_) {
        animator_->ClearInterpolators();
        animator_->AddInterpolator(CreatePictureAnimation(size));
        AdaptSelfSize();
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
            animator_->Finish();
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

void ImageAnimatorPattern::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    Pattern::ToJsonValue(json);
    static const char* STATUS_MODE[] = { "AnimationStatus.Initial", "AnimationStatus.Running", "AnimationStatus.Paused",
        "AnimationStatus.Stopped" };
    json->Put("state", STATUS_MODE[static_cast<int32_t>(status_)]);
    json->Put("duration", std::to_string(animator_->GetDuration()).c_str());
    json->Put("reverse", isReverse_ ? "true" : "false");
    json->Put("fixedSize", fixedSize_ ? "true" : "false");
    static const char* FILL_MODE[] = { "FillMode.None", "FillMode.Forwards", "FillMode.Backwards", "FillMode.Both" };
    json->Put("fillMode", FILL_MODE[static_cast<int32_t>(animator_->GetFillMode())]);
    json->Put("iterations", std::to_string(animator_->GetIteration()).c_str());
    json->Put("images", ImagesToString().c_str());
}

std::string ImageAnimatorPattern::ImagesToString() const
{
    auto imageArray = JsonUtil::CreateArray(true);
    for (const auto& image : images_) {
        auto item = JsonUtil::Create(true);
        item->Put("src", image.src.c_str());
        item->Put("left", image.left.ToString().c_str());
        item->Put("top", image.top.ToString().c_str());
        item->Put("width", image.width.ToString().c_str());
        item->Put("height", image.height.ToString().c_str());
        item->Put("duration", std::to_string(image.duration).c_str());
        imageArray->Put(item);
    }
    return imageArray->ToString();
}

void ImageAnimatorPattern::AdaptSelfSize()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetCalcLayoutConstraint() && layoutProperty->GetCalcLayoutConstraint()->selfIdealSize &&
        layoutProperty->GetCalcLayoutConstraint()->selfIdealSize->IsValid()) {
        return;
    }
    Dimension maxWidth;
    Dimension maxHeight;
    double maxWidthPx = 0.0;
    double maxHeightPx = 0.0;
    for (const auto& image : images_) {
        if (image.width.Unit() != DimensionUnit::PERCENT) {
            auto widthPx = image.width.ConvertToPx();
            if (widthPx > maxWidthPx) {
                maxWidthPx = widthPx;
                maxWidth = image.width;
            }
        }
        if (image.height.Unit() != DimensionUnit::PERCENT) {
            auto heightPx = image.height.ConvertToPx();
            if (heightPx > maxHeightPx) {
                maxHeightPx = heightPx;
                maxHeight = image.height;
            }
        }
    }
    if (!maxWidth.IsValid() || !maxHeight.IsValid()) {
        return;
    }
    const auto& layoutConstraint = layoutProperty->GetCalcLayoutConstraint();
    if (!layoutConstraint || !layoutConstraint->selfIdealSize) {
        layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(maxWidth), CalcLength(maxHeight)));
        return;
    }
    if (!layoutConstraint->selfIdealSize->Width()) {
        layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(maxWidth), std::nullopt));
        return;
    }
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(maxHeight)));
}

} // namespace OHOS::Ace::NG
