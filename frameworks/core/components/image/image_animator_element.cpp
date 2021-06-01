/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/image/image_animator_element.h"

#include "base/utils/string_utils.h"
#include "core/components/image/image_animator_component.h"
#include "core/components/image/image_component.h"

namespace OHOS::Ace {

ImageAnimatorElement::~ImageAnimatorElement()
{
    auto pageElement = pageElement_.Upgrade();
    if (pageElement && callbackId_ >= 0) {
        pageElement->CancelHiddenCallback(callbackId_);
    }
}

void Ace::ImageAnimatorElement::Update()
{
    const auto imageAnimatorComponent = AceType::DynamicCast<ImageAnimatorComponent>(component_);
    if (!imageAnimatorComponent) {
        LOGE("ImageAnimator element update failed. imageAnimatorComponent is null.");
        return;
    }

    if (controller_) {
        controller_->ClearRepeatListeners();
    }
    controller_ = imageAnimatorComponent->GetAnimator();
    if ((controller_) && (!controller_->HasScheduler())) {
        controller_->AttachScheduler(context_);
    }
    iteration_ = imageAnimatorComponent->GetIteration();
    preDecode_ = imageAnimatorComponent->GetPreDecode();
    duration_ = imageAnimatorComponent->GetDuration();
    isReverse_ = imageAnimatorComponent->GetIsReverse();
    images_ = imageAnimatorComponent->GetImageProperties();
    isFixedSize_ = imageAnimatorComponent->GetIsFixedSize();
    border_ = imageAnimatorComponent->GetBorder();
    UpdateFilterImages();

    if (!pageElement_.Invalid()) {
        return;
    }

    auto pageElement = GetPageElement();
    if (!pageElement) {
        return;
    }
    pageElement_ = pageElement;
    callbackId_ = pageElement->RegisterHiddenCallback([weak = AceType::WeakClaim(this)](bool hidden) {
        auto element = weak.Upgrade();
        if (!element || !element->controller_) {
            return;
        }

        if (hidden) {
            if (element->controller_->GetStatus() == Animator::Status::RUNNING) {
                element->controller_->Pause();
                element->isPaused_ = true;
            }
        } else {
            if (element->isPaused_) {
                if (element->isReverse_) {
                    element->controller_->Backward();
                } else {
                    element->controller_->Forward();
                }
                element->isPaused_ = false;
            }
        }
    });
}

void ImageAnimatorElement::PerformBuild()
{
    int32_t size = images_.size();
    if (size <= 0) {
        LOGE("image size is less than 0.");
        return;
    }
    if (children_.empty()) {
        // first time to set image child.
        childComponent_ = BuildChild();
        ComposedElement::PerformBuild();
    }
    if (preDecode_ > 1) {
        auto boxComponent = DynamicCast<BoxComponent>(childComponent_);
        UpdatePreLoadImages(boxComponent);
    }
    CreatePictureAnimation(size);
    if (!controller_) {
        LOGE("controller is null, need to get controller first.");
        return;
    }
    // update duration after a loop of animation.
    if (!isSetDuration_) {
        if (durationTotal_ > 0.0f) {
            controller_->SetDuration(durationTotal_);
        } else {
            controller_->SetDuration(duration_);
        }
        isSetDuration_ = true;
    }
    controller_->ClearInterpolators();
    controller_->AddInterpolator(pictureAnimation_);
    controller_->SetIteration(iteration_);
    controller_->ClearRepeatListeners();
    controller_->AddRepeatListener([weak = WeakClaim(this)]() {
        auto imageAnimator = weak.Upgrade();
        if (imageAnimator) {
            auto controller = imageAnimator->controller_;
            if (controller) {
                if (imageAnimator->durationTotal_ > 0.0f) {
                    controller->SetDuration(imageAnimator->durationTotal_);
                } else {
                    controller->SetDuration(imageAnimator->duration_);
                }
            }
        }
    });
    controller_->RemoveStopListener(stopCallbackId_);
    stopCallbackId_ = controller_->AddStopListener([weak = WeakClaim(this)]() {
        auto imageAnimator = weak.Upgrade();
        if (imageAnimator) {
            imageAnimator->isSetDuration_ = false;
        }
    });
    if (isReverse_) {
        controller_->Backward();
    } else {
        controller_->Forward();
    }
}

RefPtr<Component> ImageAnimatorElement::BuildChild()
{
    int32_t size = images_.size();
    if (size <= 0) {
        LOGE("image size is less than 0.");
        return nullptr;
    }
    auto boxComponent = AceType::MakeRefPtr<BoxComponent>();
    ImageProperties childImage;
    if (durationTotal_ > 0.0f) {
        childImage = (isReverse_ ? filterImages_.back() : filterImages_.front());
    } else {
        childImage = (isReverse_ ? images_.back() : images_.front());
    }
    if (!isFixedSize_) {
        UpdateImageBox(childImage, boxComponent);
    }
    if (!childImage.src.empty()) {
        auto imageComponent = AceType::MakeRefPtr<ImageComponent>(childImage.src);
        imageComponent->SetBorder(border_);
        imageComponent->SetFitMaxSize(true);
        boxComponent->SetChild(imageComponent);
    }
    return boxComponent;
}

void ImageAnimatorElement::UpdatePreLoadImages(const RefPtr<BoxComponent>& box)
{
    if (!box) {
        LOGE("boxComponent is null.");
        return;
    }
    int32_t size = images_.size();
    for (int32_t idx = 0; (idx < preDecode_) && (idx < size); idx++) {
        auto imageComponent = DynamicCast<ImageComponent>(box->GetChild());
        if (!imageComponent) {
            LOGE("imageComponent is null.");
            return;
        }
        ImageProperties childImage = images_[idx];
        if (!childImage.src.empty()) {
            imageComponent->SetSrc(childImage.src);
        }
        UpdateChild(GetFirstChild(), box);
    }
}

void ImageAnimatorElement::CreatePictureAnimation(int32_t size)
{
    if (!pictureAnimation_) {
        pictureAnimation_ = MakeRefPtr<PictureAnimation<int32_t>>();
    }

    pictureAnimation_->ClearListeners();
    pictureAnimation_->ClearPictures();
    if (durationTotal_ > 0.0f) {
        int32_t filterImagesSize = filterImages_.size();
        for (int32_t index = 0; index < filterImagesSize; ++index) {
            double imageDuration = StringUtils::StringToDouble(filterImages_[index].duration);
            pictureAnimation_->AddPicture(imageDuration / durationTotal_, index);
        }
    } else {
        for (int32_t index = 0; index < size; ++index) {
            pictureAnimation_->AddPicture(NORMALIZED_DURATION_MAX / size, index);
        }
    }
    pictureAnimation_->AddListener([weak = WeakClaim(this)](const int32_t index) {
        auto imageAnimator = weak.Upgrade();
        if (imageAnimator) {
            imageAnimator->PlayImageAnimator(index);
        }
    });
}

void ImageAnimatorElement::UpdateFilterImages()
{
    filterImages_.clear();
    durationTotal_ = 0.0f;
    for (auto& childImage : images_) {
        if (!childImage.src.empty() && !childImage.duration.empty()) {
            durationNums_++;
            double childDuration = StringUtils::StringToDouble(childImage.duration);
            if (childDuration > 0.0) {
                durationTotal_ += childDuration;
                filterImages_.emplace_back(childImage);
            }
        }
    }
}

void ImageAnimatorElement::PlayImageAnimator(int32_t index)
{
    auto boxComponent = DynamicCast<BoxComponent>(childComponent_);
    if (!boxComponent) {
        LOGE("child boxComponent is null.");
        return;
    }
    auto imageComponent = DynamicCast<ImageComponent>(boxComponent->GetChild());
    if (!imageComponent) {
        LOGE("imageComponent is null.");
        return;
    }
    ImageProperties childImage;
    if (durationTotal_ > 0.0f) {
        childImage = filterImages_[index];
    } else {
        childImage = images_[index];
    }
    if (!isFixedSize_) {
        UpdateImageBox(childImage, boxComponent);
        isResetBox_ = false;
    } else {
        if (!isResetBox_) {
            boxComponent->SetMargin(Edge());
            // Follows the size of the parent component
            boxComponent->SetWidth(-1.0);
            boxComponent->SetHeight(-1.0);
            isResetBox_ = true;
        }
    }
    if (!childImage.src.empty()) {
        imageComponent->SetSrc(childImage.src);
    }
    UpdateChild(GetFirstChild(), boxComponent);
}

void ImageAnimatorElement::UpdateImageBox(ImageProperties& imageProperties, const RefPtr<BoxComponent>& box)
{
    auto edge = Edge();
    if (!imageProperties.left.empty()) {
        edge.SetLeft(StringUtils::StringToDimension(imageProperties.left));
    }
    if (!imageProperties.top.empty()) {
        edge.SetTop(StringUtils::StringToDimension(imageProperties.top));
    }
    box->SetMargin(edge);
    if (!imageProperties.width.empty()) {
        box->SetWidth(StringUtils::StringToDouble(imageProperties.width));
    }
    if (!imageProperties.height.empty()) {
        box->SetHeight(StringUtils::StringToDouble(imageProperties.height));
    }
}

} // namespace OHOS::Ace
