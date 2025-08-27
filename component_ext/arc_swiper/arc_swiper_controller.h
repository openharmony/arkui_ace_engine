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

#ifndef COMPONENT_EXT_ARC_SWIPER_ARC_SWIPER_CONTROLLER_H
#define COMPONENT_EXT_ARC_SWIPER_ARC_SWIPER_CONTROLLER_H

#include <functional>

#include "base/memory/ace_type.h"
#include "core/components/swiper/swiper_controller.h"

namespace OHOS::Ace::NG {

class JsArcSwiperController : public virtual AceType {
    DECLARE_ACE_TYPE(JsArcSwiperController, AceType);

public:
    JsArcSwiperController() = default;
    ~JsArcSwiperController() override = default;

    void ShowNext()
    {
        if (controller_) {
            controller_->ShowNext();
        }
    }

    void ShowPrevious()
    {
        if (controller_) {
            controller_->ShowPrevious();
        }
    }

    void FinishAnimation(const CommonFunc& onFinish)
    {
        if (!controller_) {
            return;
        }
        if (onFinish) {
            controller_->SetFinishCallback(onFinish);
        }
        controller_->FinishAnimation();
    }

    void SetController(const RefPtr<SwiperController>& controller)
    {
        controller_ = controller;
    }

private:
    RefPtr<SwiperController> controller_;

    ACE_DISALLOW_COPY_AND_MOVE(JsArcSwiperController);
};

} // namespace OHOS::Ace::NG
 
#endif // COMPONENT_EXT_ARC_SWIPER_ARC_SWIPER_CONTROLLER_H