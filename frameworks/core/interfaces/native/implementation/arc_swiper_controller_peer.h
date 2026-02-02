/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_IMPL_ARC_SWIPER_CONTROLLER_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_IMPL_ARC_SWIPER_CONTROLLER_PEER_IMPL_H

#include "core/components/swiper/swiper_controller.h"

namespace OHOS::Ace::NG::GeneratedModifier {
class ArcSwiperControllerHelperPeerImpl : public Referenced {
public:
    ArcSwiperControllerHelperPeerImpl() = default;

    void UpdateTargetController(const WeakPtr<SwiperController> &handler)
    {
        CHECK_NULL_VOID(!handler.Invalid());
        handler_ = handler;
    }

    void TriggerShowNext()
    {
        if (auto controller = handler_.Upgrade(); controller) {
            controller->ShowNext();
        }
    }

    void TriggerShowPrevious()
    {
        if (auto controller = handler_.Upgrade(); controller) {
            controller->ShowPrevious();
        }
    }
    void SetFinishCallback(const CommonFunc &callbackFunc)
    {
        if (auto controller = handler_.Upgrade(); controller) {
            controller->SetFinishCallback(callbackFunc);
        }
    }

    void TriggerFinishAnimation()
    {
        if (auto controller = handler_.Upgrade(); controller) {
            controller->FinishAnimation();
        }
    }
private:
    Ace::WeakPtr<SwiperController> handler_;
};
} // namespace OHOS::Ace::NG::GeneratedModifier

struct ArcSwiperControllerHelperPeer : public OHOS::Ace::NG::GeneratedModifier::ArcSwiperControllerHelperPeerImpl {};
#endif //FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_IMPL_ARC_SWIPER_CONTROLLER_PEER_IMPL_H