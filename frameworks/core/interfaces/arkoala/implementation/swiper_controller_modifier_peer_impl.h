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

#include <iostream>

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/swiper/swiper_controller.h"

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPLEMENTATION_SWIPER_CONTROLLER_MODIFIER_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPLEMENTATION_SWIPER_CONTROLLER_MODIFIER_PEER_IMPL_H

namespace OHOS::Ace::NG::GeneratedModifier::SwiperControllerModifier {
class SwiperControllerPeerImpl : public Referenced {
public:
    SwiperControllerPeerImpl() = default;

    void AddListener(const RefPtr<SwiperController> &listener) {
        CHECK_NULL_VOID(listener);
        listeners_.push_back(listener);
    }

    void TriggerShowNext() {
        for(auto &listener: listeners_) {
            listener->ShowNext();
        }
    }
private:
    std::vector<RefPtr<SwiperController>> listeners_;
};
} // namespace OHOS::Ace::NG
#endif //FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPLEMENTATION_SWIPER_CONTROLLER_MODIFIER_PEER_IMPL_H