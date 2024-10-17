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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_TABS_CONTROLLER_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_TABS_CONTROLLER_PEER_IMPL_H

#include <optional>
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
//#include "core/components/tab_bar/tab_controller.h"
#include "core/components/swiper/swiper_controller.h"

namespace OHOS::Ace::NG::GeneratedModifier {
class TabsControllerPeerImpl : public Referenced {
public:
    TabsControllerPeerImpl() = default;

    void SetTargetController(const WeakPtr<SwiperController> &controller)
    {
        CHECK_NULL_VOID(!controller.Invalid());
        controllerWeakPtr_ = controller;
    }
/* 
    void TriggerShowNext()
    {
        for (auto &handler: handlers_) {
            if (auto controller = handler.Upgrade(); controller) {
                controller->ShowNext();
            }
        }
    }

    void TriggerShowPrevios()
    {
        for (auto &handler: handlers_) {
            if (auto controller = handler.Upgrade(); controller) {
                controller->ShowPrevious();
            }
        }
    }

    void SetFinishCallback(const CommonFunc &callbackFunc)
    {
        for (auto &handler: handlers_) {
            if (auto controller = handler.Upgrade(); controller) {
                controller->SetFinishCallback(callbackFunc);
            }
        }
    }

    void TriggerFinishAnimation()
    {
        for (auto &handler: handlers_) {
            if (auto controller = handler.Upgrade(); controller) {
                controller->FinishAnimation();
            }
        }
    }
*/
    void TriggerChangeIndex(int32_t index)
    {
        index = index < 0 ? 0 : index;

        auto swiperController = controllerWeakPtr_.Upgrade();
        CHECK_NULL_VOID(swiperController);

        const auto& updateCubicCurveCallback = swiperController->GetUpdateCubicCurveCallback();
        if (updateCubicCurveCallback != nullptr) {
            updateCubicCurveCallback();
        }
        swiperController->SwipeTo(index);
    }

private:
    Ace::WeakPtr<SwiperController> controllerWeakPtr_;
};
} // namespace OHOS::Ace::NG::GeneratedModifier
#endif //FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_TABS_CONTROLLER_PEER_IMPL_H