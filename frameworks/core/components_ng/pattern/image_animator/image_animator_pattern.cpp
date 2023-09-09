/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#include <algorithm>
#include <string>

#include "base/log/ace_trace.h"
#include "core/components_ng/pattern/image/image_event_hub.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {

constexpr uint32_t DEFAULT_DURATION = 1000; // ms
constexpr uint32_t CRITICAL_TIME = 50;      // ms. If show time of image is less than this, use more cacheImages.

} // namespace

ImageAnimatorPattern::ImageAnimatorPattern()
{
    animator_ = CREATE_ANIMATOR(PipelineContext::GetCurrentContext());
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
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(host->GetChildren().front());
    CHECK_NULL_VOID(imageFrameNode);
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    if (index >= static_cast<int32_t>(images_.size())) {
        LOGW("ImageAnimator update index error, index: %{public}d, size: %{public}zu", index, images_.size());
        return;
    }
    nowImageIndex_ = index;
    auto cacheImageIter = FindCacheImageNode(images_[index].src);
    if (IsShowingSrc(imageFrameNode, images_[index].src)) {
        ACE_SCOPED_TRACE("ImageAnimator same src %s, index %d", images_[index].src.c_str(), index);
        UpdateShowingImageInfo(imageFrameNode, index);
    } else if (cacheImageIter == cacheImages_.end()) {
        ACE_SCOPED_TRACE("ImageAnimator no cache found, src %s, index %d", images_[index].src.c_str(), index);
        UpdateShowingImageInfo(imageFrameNode, index);
    } else if (cacheImageIter->isLoaded) {
        ACE_SCOPED_TRACE("ImageAnimator useCache src %s, index %d", images_[index].src.c_str(), index);
        auto cacheImageNode = cacheImageIter->imageNode;
        host->RemoveChild(imageFrameNode);
        host->AddChild(cacheImageNode, DEFAULT_NODE_SLOT, true);
        host->RebuildRenderContextTree();
        cacheImages_.erase(cacheImageIter);
        cacheImages_.emplace_back(CacheImageStruct(imageFrameNode));
        UpdateShowingImageInfo(cacheImageNode, index);
    } else {
        // wait for cache image loading
        ACE_SCOPED_TRACE("ImageAnimator waitForCache src %s, index %d", images_[index].src.c_str(), index);
        return;
    }
    // update cache images
    CHECK_NULL_VOID(cacheImages_.size());
    int32_t nextIndex = GetNextIndex(index);
    for (auto& cacheImage : cacheImages_) {
        UpdateCacheImageInfo(cacheImage, nextIndex);
        nextIndex = GetNextIndex(nextIndex);
    }
}

void ImageAnimatorPattern::UpdateShowingImageInfo(const RefPtr<FrameNode>& imageFrameNode, int32_t index)
{
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
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
        imageFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        return;
    }
    margin.SetEdges(CalcLength(0.0));
    imageLayoutProperty->UpdateMargin(margin);
    imageLayoutProperty->ClearUserDefinedIdealSize(true, true);
    imageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    imageFrameNode->MarkModifyDone();
    imageFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void ImageAnimatorPattern::UpdateCacheImageInfo(CacheImageStruct& cacheImage, int32_t index)
{
    if (index >= static_cast<int32_t>(images_.size())) {
        LOGW("PrepareImageInfo index error, index: %{public}d, size: %{public}zu", index, images_.size());
        return;
    }
    auto imageLayoutProperty = cacheImage.imageNode->GetLayoutProperty<ImageLayoutProperty>();
    auto preSrc =
        imageLayoutProperty->HasImageSourceInfo() ? imageLayoutProperty->GetImageSourceInfoValue().GetSrc() : "";
    if (preSrc != images_[index].src) {
        // need to cache newImage
        imageLayoutProperty->UpdateImageSourceInfo(ImageSourceInfo(images_[index].src));
        cacheImage.index = index;
        cacheImage.isLoaded = false;
    }
    if (!fixedSize_) {
        CalcSize realSize = { CalcLength(images_[index].width), CalcLength(images_[index].height) };
        imageLayoutProperty->UpdateUserDefinedIdealSize(realSize);
        cacheImage.imageNode->MarkModifyDone();
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hostSize = host->GetGeometryNode()->GetPaddingSize();
    if (!hostSize.IsPositive()) {
        // if imageNode size is nonPositive, no pixelMap will be generated. Wait for size.
        return;
    }
    imageLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(hostSize.Width()), CalcLength(hostSize.Height())));
    cacheImage.imageNode->MarkModifyDone();
}

std::list<ImageAnimatorPattern::CacheImageStruct>::iterator ImageAnimatorPattern::FindCacheImageNode(
    const std::string& src)
{
    for (auto iter = cacheImages_.begin(); iter != cacheImages_.end(); ++iter) {
        if (IsShowingSrc(iter->imageNode, src)) {
            return iter;
        }
    }
    return cacheImages_.end();
}

void ImageAnimatorPattern::GenerateCachedImages()
{
    CHECK_NULL_VOID(images_.size());
    auto averageShowTime = animator_->GetDuration() / images_.size();
    size_t cacheImageNum = averageShowTime >= CRITICAL_TIME ? 1 : 2;
    cacheImageNum = std::min(images_.size() - 1, cacheImageNum);
    if (cacheImages_.size() > cacheImageNum) {
        cacheImages_.resize(cacheImageNum);
        return;
    }
    while (cacheImages_.size() < cacheImageNum) {
        auto imageNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, -1, AceType::MakeRefPtr<ImagePattern>());
        auto imageLayoutProperty = imageNode->GetLayoutProperty();
        imageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
        imageLayoutProperty->UpdateAlignment(Alignment::TOP_LEFT);
        AddImageLoadSuccessEvent(imageNode);
        cacheImages_.emplace_back(CacheImageStruct(imageNode));
    }
}

bool ImageAnimatorPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& wrapper, const DirtySwapConfig& config)
{
    if (!isLayouted_) {
        isLayouted_ = true;
        if (fixedSize_ && images_.size()) {
            int32_t nextIndex = GetNextIndex(nowImageIndex_);
            for (auto& cacheImage : cacheImages_) {
                UpdateCacheImageInfo(cacheImage, nextIndex);
                nextIndex = GetNextIndex(nextIndex);
            }
        }
    }
    return false;
}

void ImageAnimatorPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    Pattern::OnModifyDone();
    auto size = static_cast<int32_t>(images_.size());
    if (size <= 0) {
        LOGE("image size is less than 0.");
        return;
    }
    GenerateCachedImages();
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
        auto imageFrameNode = AceType::DynamicCast<FrameNode>(host->GetChildren().front());
        AddImageLoadSuccessEvent(imageFrameNode);
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

int32_t ImageAnimatorPattern::GetNextIndex(int32_t preIndex)
{
    if (isReverse_) {
        return preIndex == 0 ? (static_cast<int32_t>(images_.size()) - 1) : (preIndex - 1);
    }
    return (preIndex + 1) % static_cast<int32_t>(images_.size());
}

void ImageAnimatorPattern::AddImageLoadSuccessEvent(const RefPtr<FrameNode>& imageFrameNode)
{
    CHECK_NULL_VOID(imageFrameNode);
    auto eventHub = imageFrameNode->GetEventHub<ImageEventHub>();
    eventHub->SetOnComplete(
        [weakImage = WeakPtr<FrameNode>(imageFrameNode), weak = WeakClaim(this)](const LoadImageSuccessEvent& info) {
            if (info.GetLoadingStatus() != 1) {
                // status 1 means load success. Only need loadSuccess event.
                return;
            }
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto cacheImageNode = weakImage.Upgrade();
            CHECK_NULL_VOID(cacheImageNode);
            auto imageAnimator = pattern->GetHost();
            CHECK_NULL_VOID(imageAnimator);
            auto cacheLayoutProperty = cacheImageNode->GetLayoutProperty<ImageLayoutProperty>();
            auto cacheSrc = cacheLayoutProperty->GetImageSourceInfoValue(ImageSourceInfo()).GetSrc();
            ACE_SCOPED_TRACE("ImageAnimator cache succeed. src %s", cacheSrc.c_str());
            auto iter = std::find_if(pattern->cacheImages_.begin(), pattern->cacheImages_.end(),
                [&cacheImageNode](const CacheImageStruct& other) { return other.imageNode == cacheImageNode; });
            if (iter == pattern->cacheImages_.end()) {
                return;
            }
            iter->isLoaded = true;
            if (pattern->nowImageIndex_ >= static_cast<int32_t>(pattern->images_.size())) {
                LOGW("ImageAnimator showImage index is invalid");
                return;
            }
            if (pattern->nowImageIndex_ == iter->index &&
                IsShowingSrc(cacheImageNode, pattern->images_[pattern->nowImageIndex_].src)) {
                pattern->SetShowingIndex(pattern->nowImageIndex_);
            }
        });
}

bool ImageAnimatorPattern::IsShowingSrc(const RefPtr<FrameNode>& imageFrameNode, const std::string& src)
{
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    return imageLayoutProperty->HasImageSourceInfo() && imageLayoutProperty->GetImageSourceInfoValue().GetSrc() == src;
}

} // namespace OHOS::Ace::NG
