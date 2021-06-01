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

#include "core/components/image/image_animator_component.h"

#include "core/animation/animation_pub.h"
#include "core/components/image/image_animator_element.h"

namespace OHOS::Ace {
namespace {

const char* PREFIX = "ImageAnimator";
uint32_t g_componentId = 0;

} // namespace

RefPtr<Element> ImageAnimatorComponent::CreateElement()
{
    return AceType::MakeRefPtr<ImageAnimatorElement>(GetId());
}

RefPtr<Animator> ImageAnimatorComponent::GetAnimator() const
{
    return controller_;
}

void ImageAnimatorComponent::SetAnimator(const RefPtr<Animator>& controller)
{
    controller_ = controller;
}

void ImageAnimatorComponent::SetIteration(int32_t iteration)
{
    iteration_ = iteration;
}

int32_t ImageAnimatorComponent::GetIteration() const
{
    return iteration_;
}

void ImageAnimatorComponent::SetPreDecode(int32_t preDecode)
{
    preDecode_ = preDecode;
}

int32_t ImageAnimatorComponent::GetPreDecode() const
{
    return preDecode_;
}

void ImageAnimatorComponent::SetDuration(int32_t duration)
{
    if (duration <= 0) {
        duration_ = 0;
        return;
    }
    duration_ = duration;
}

int32_t ImageAnimatorComponent::GetDuration() const
{
    return duration_;
}

void ImageAnimatorComponent::SetBorder(const Border& border)
{
    border_ = border;
}

const Border& ImageAnimatorComponent::GetBorder() const
{
    return border_;
}

void ImageAnimatorComponent::SetIsReverse(bool isReverse)
{
    isReverse_ = isReverse;
}

bool ImageAnimatorComponent::GetIsReverse() const
{
    return isReverse_;
}

void ImageAnimatorComponent::SetIsFixedSize(bool isFixedSize)
{
    isFixedSize_ = isFixedSize;
}

bool ImageAnimatorComponent::GetIsFixedSize() const
{
    return isFixedSize_;
}

void ImageAnimatorComponent::SetImageProperties(const std::vector<ImageProperties>& images)
{
    if (images.empty()) {
        LOGW("Images are empty.");
        return;
    }
    images_ = images;
}

const std::vector<ImageProperties>& ImageAnimatorComponent::GetImageProperties() const
{
    return images_;
}

ComposeId ImageAnimatorComponent::GenerateComponentId()
{
    return PREFIX + (std::to_string(g_componentId++));
}

} // namespace OHOS::Ace
