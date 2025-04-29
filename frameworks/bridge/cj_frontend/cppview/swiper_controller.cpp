/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "bridge/cj_frontend/cppview/swiper_controller.h"

namespace OHOS::Ace::Framework {

NativeSwiperController::NativeSwiperController() : FFIData()
{
    LOGI("Native SwiperController constructed: %{public}" PRId64, GetID());
}

NativeSwiperController::~NativeSwiperController()
{
    LOGI("Native SwiperController Destroyed: %{public}" PRId64, GetID());
}

void NativeSwiperController::ShowNext()
{
    if (controller_) {
        controller_->ShowNext();
    }
}

void NativeSwiperController::ShowPrevious()
{
    if (controller_) {
        controller_->ShowPrevious();
    }
}

void NativeSwiperController::FinishAnimation()
{
    if (controller_) {
        controller_->FinishAnimation();
    }
}

void NativeSwiperController::FinishAnimationWithCallback(const std::function<void()>& callback)
{
    if (controller_) {
        controller_->SetFinishCallback(callback);
        controller_->FinishAnimation();
    }
}

void NativeSwiperController::SetController(const RefPtr<SwiperController>& controller)
{
    controller_ = controller;
}

void NativeSwiperController::ChangeIndex(int32_t index, bool useAnimation)
{
    controller_->ChangeIndex(index, useAnimation);
}

} // namespace OHOS::Ace::Framework
