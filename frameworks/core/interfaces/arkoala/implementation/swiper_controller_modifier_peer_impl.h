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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_SWIPER_CONTROLLER_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_SWIPER_CONTROLLER_PEER_IMPL_H

#include <optional>
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/swiper/swiper_controller.h"

namespace OHOS::Ace::NG::GeneratedModifier {
class SwiperControllerPeerImpl : public Referenced {
public:
    SwiperControllerPeerImpl() = default;

    void AddListener(const RefPtr<SwiperController> &listener)
    {
        CHECK_NULL_VOID(listener);
        listeners_.push_back(listener);
    }

    void TriggerShowNext()
    {
        for (auto &listener: listeners_) {
            listener->ShowNext();
        }
    }

    void TriggerShowPrevios()
    {
        for (auto &listener: listeners_) {
            listener->ShowPrevious();
        }
    }

    void TriggerChangeIndex(int32_t index, const std::optional<bool> &useAnimationOpt)
    {
        index = index < 0 ? 0 : index;
        bool useAnim = useAnimationOpt && *useAnimationOpt;
        for (auto &listener: listeners_) {
            listener->ChangeIndex(index, useAnim);
        }
    }

    void SetFinishCallback(const CommonFunc &callbackFunc)
    {
        for (auto &listener: listeners_) {
            listener->SetFinishCallback(callbackFunc);
        }
    }

    void TriggerFinishAnimation()
    {
        for (auto &listener: listeners_) {
            listener->FinishAnimation();
        }
    }
private:
    std::vector<RefPtr<SwiperController>> listeners_;
};
} // namespace OHOS::Ace::NG::GeneratedModifier
#endif //FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_SWIPER_CONTROLLER_PEER_IMPL_H