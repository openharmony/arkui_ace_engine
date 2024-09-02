/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/models/image_animator_model_impl.h"

#include "bridge/declarative_frontend/view_stack_processor.h"

constexpr uint32_t DEFAULT_DURATION = 1000; // ms
constexpr uint32_t DEFAULT_ITERATIONS = 1;

namespace OHOS::Ace::Framework {
void ImageAnimatorModelImpl::Create()
{
    RefPtr<ImageAnimatorComponent> imageAnimator = AceType::MakeRefPtr<ImageAnimatorComponent>("ImageAnimator");
    imageAnimator->SetIteration(DEFAULT_ITERATIONS);
    imageAnimator->SetDuration(DEFAULT_DURATION);
    ViewStackProcessor::GetInstance()->Push(imageAnimator);
    // Init Common Styles for ImageAnimator
    ViewStackProcessor::GetInstance()->GetBoxComponent();
}

void ImageAnimatorModelImpl::SetImages(const std::vector<ImageProperties>& images)
{
    auto imageAnimator =
        AceType::DynamicCast<ImageAnimatorComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (imageAnimator) {
        imageAnimator->SetImageProperties(images);
    }
}

void ImageAnimatorModelImpl::SetState(int32_t state)
{
    auto imageAnimator =
        AceType::DynamicCast<ImageAnimatorComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (imageAnimator) {
        imageAnimator->SetStatus(static_cast<Animator::Status>(state));
    }
}

void ImageAnimatorModelImpl::SetDuration(int32_t duration)
{
    auto imageAnimator =
        AceType::DynamicCast<ImageAnimatorComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (imageAnimator) {
        imageAnimator->SetDuration(duration);
    }
}

void ImageAnimatorModelImpl::SetIteration(int32_t iteration)
{
    auto imageAnimator =
        AceType::DynamicCast<ImageAnimatorComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (imageAnimator) {
        imageAnimator->SetIteration(iteration);
    }
}

void ImageAnimatorModelImpl::SetFillMode(int32_t fillMode)
{
    auto imageAnimator =
        AceType::DynamicCast<ImageAnimatorComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (imageAnimator) {
        imageAnimator->SetFillMode(static_cast<FillMode>(fillMode));
    }
}

void ImageAnimatorModelImpl::SetPreDecode(int32_t preDecode)
{
    auto imageAnimator =
        AceType::DynamicCast<ImageAnimatorComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (imageAnimator) {
        imageAnimator->SetPreDecode(preDecode);
    }
}

void ImageAnimatorModelImpl::SetIsReverse(bool isReverse)
{
    auto imageAnimator =
        AceType::DynamicCast<ImageAnimatorComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (imageAnimator) {
        imageAnimator->SetIsReverse(isReverse);
    }
}

void ImageAnimatorModelImpl::SetFixedSize(bool fixedSize)
{
    auto imageAnimator =
        AceType::DynamicCast<ImageAnimatorComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (imageAnimator) {
        imageAnimator->SetIsFixedSize(fixedSize);
    }
}

void ImageAnimatorModelImpl::SetOnStart(std::function<void()>&& OnStart)
{
    auto imageAnimator =
        AceType::DynamicCast<ImageAnimatorComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!imageAnimator) {
        return;
    }
    const auto& controller = imageAnimator->GetImageAnimatorController();
    if (controller) {
        auto startEvent = EventMarker(std::move(OnStart));
        controller->SetStartEvent(startEvent);
    }
}

void ImageAnimatorModelImpl::SetOnPause(std::function<void()>&& OnPause)
{
    auto imageAnimator =
        AceType::DynamicCast<ImageAnimatorComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!imageAnimator) {
        return;
    }
    const auto& controller = imageAnimator->GetImageAnimatorController();
    if (controller) {
        auto startEvent = EventMarker(std::move(OnPause));
        controller->SetPauseEvent(startEvent);
    }
}

void ImageAnimatorModelImpl::SetOnRepeat(std::function<void()>&& OnRepeat)
{
    auto imageAnimator =
        AceType::DynamicCast<ImageAnimatorComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!imageAnimator) {
        return;
    }
    const auto& controller = imageAnimator->GetImageAnimatorController();
    if (controller) {
        auto startEvent = EventMarker(std::move(OnRepeat));
        controller->SetRepeatEvent(startEvent);
    }
}

void ImageAnimatorModelImpl::SetOnCancel(std::function<void()>&& OnCancel)
{
    auto imageAnimator =
        AceType::DynamicCast<ImageAnimatorComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!imageAnimator) {
        return;
    }
    const auto& controller = imageAnimator->GetImageAnimatorController();
    if (controller) {
        auto startEvent = EventMarker(std::move(OnCancel));
        controller->SetCancelEvent(startEvent);
    }
}

void ImageAnimatorModelImpl::SetOnFinish(std::function<void()>&& OnFinish)
{
    auto imageAnimator =
        AceType::DynamicCast<ImageAnimatorComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!imageAnimator) {
        return;
    }
    const auto& controller = imageAnimator->GetImageAnimatorController();
    if (controller) {
        auto startEvent = EventMarker(std::move(OnFinish));
        controller->SetStopEvent(startEvent);
    }
}
} // namespace OHOS::Ace::Framework
