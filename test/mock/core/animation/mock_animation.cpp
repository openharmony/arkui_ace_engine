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

#include "core/animation/test/mock/mock_animation.h"

#include "base/log/log.h"
#include "core/components/dialog_modal/dialog_modal_component.h"
#include "core/components/semi_modal/semi_modal_component.h"
#include "core/image/image_loader.h"

namespace OHOS::Ace {
void MockAnimation::OnPostFlush()
{
    postFlushCallTimes_++;
    CreateInterpolators();
    AddListeners();
    animator_->SetDuration(animationDuration_);
    setRepeatSucc_ = animator_->SetIteration(iteration_);
    animator_->SetStartDelay(startDelay_);
    ExecuteOperation();
}

void MockAnimation::ExecuteOperation()
{
    switch (operation_) {
        case AnimationOperation::PLAY:
            animator_->Play();
            break;
        case AnimationOperation::REVERSE:
            animator_->Reverse();
            break;
        case AnimationOperation::FINISH:
            animator_->Finish();
            break;
        case AnimationOperation::PAUSE:
            animator_->Pause();
            break;
        case AnimationOperation::CANCEL:
            animator_->Cancel();
            break;
        case AnimationOperation::NONE:
        default:
            break;
    }
}

void MockAnimation::AddListeners()
{
    auto weak = AceType::WeakClaim(this);
    animator_->AddStartListener([weak]() {
        auto simulator = weak.Upgrade();
        if (simulator) {
            simulator->animationStartStatus_ = true;
        }
    });
    animator_->AddStopListener([weak]() {
        auto simulator = weak.Upgrade();
        if (simulator) {
            simulator->animationStopStatus_ = true;
            simulator->animationIntStopValue_ = simulator->animationIntValue_;
        }
    });
    animator_->AddRepeatListener([weak]() {
        auto simulator = weak.Upgrade();
        if (simulator) {
            ++(simulator->repeatDoneTimes_);
        }
    });
    animator_->AddIdleListener([weak]() {
        auto simulator = weak.Upgrade();
        if (simulator) {
            simulator->animationIdleStatus_ = true;
        }
    });
    animator_->AddPauseListener([weak]() {
        auto simulator = weak.Upgrade();
        if (simulator) {
            simulator->animationPauseStatus_ = true;
        }
    });
}

void MockAnimation::CreatePictureInterpolators()
{
    auto weak = AceType::WeakClaim(this);
    if (pictureInt_) {
        pictureInt_->AddListener([weak](const int& value) {
            auto simulator = weak.Upgrade();
            if (simulator) {
                simulator->pictureIntValue_ = value;
            }
        });
        animator_->AddInterpolator(pictureInt_);
    }
    if (pictureString_) {
        pictureString_->AddListener([weak](const std::string& value) {
            auto simulator = weak.Upgrade();
            if (simulator) {
                simulator->pictureStringValue_ = value;
            }
        });
        animator_->AddInterpolator(pictureString_);
    }
}

void MockAnimation::CreateInterpolators()
{
    auto weak = AceType::WeakClaim(this);
    if (animationInt_) {
        animationInt_->AddListener([weak](const int& value) {
            auto simulator = weak.Upgrade();
            if (simulator) {
                simulator->animationIntValue_ = value;
            }
        });
        animator_->AddInterpolator(animationInt_);
    }
    if (animationFloat_) {
        animationFloat_->AddListener([weak](const float& value) {
            auto simulator = weak.Upgrade();
            if (simulator) {
                simulator->animationFloatValue_ = value;
            }
        });
        animator_->AddInterpolator(animationFloat_);
    }
    if (keyframeAnimation_) {
        keyframeAnimation_->AddListener([weak](const float& value) {
            auto simulator = weak.Upgrade();
            if (simulator) {
                simulator->keyframeAnimationValue_ = value;
            }
        });
        animator_->AddInterpolator(keyframeAnimation_);
    }
    if (animationColor_) {
        animationColor_->AddListener([weak](const Color& value) {
            auto simulator = weak.Upgrade();
            if (simulator) {
                simulator->animationColorValue_ = value;
            }
        });
        animator_->AddInterpolator(animationColor_);
    }
    CreatePictureInterpolators();
}

const RefPtr<Animator>& MockAnimation::GetAnimator() const
{
    return animator_;
}

double MockAnimation::GetPositionResult() const
{
    return positionResult_;
}

void MockAnimation::SetPositionResult(double positionResult)
{
    positionResult_ = positionResult;
}

RefPtr<Component> SemiModalComponent::Create(
    RefPtr<Component> child, bool isFullScreen, int32_t modalHeight, uint32_t color)
{
    return nullptr;
}

RefPtr<Component> DialogModalComponent::Create(RefPtr<Component> child)
{
    return nullptr;
}

#ifndef USE_ROSEN_DRAWING
sk_sp<SkData> FileImageLoader::LoadImageData(const std::string& src, const WeakPtr<PipelineContext> context)
#else
std::shared_ptr<RSData> FileImageLoader::LoadImageData(const std::string& src, const WeakPtr<PipelineContext> context)
#endif
{
    return nullptr;
}
} // namespace OHOS::Ace
