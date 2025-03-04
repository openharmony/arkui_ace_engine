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
#include "core/components_ng/property/transition_property.h"
#include "core/components_ng/pattern/tabs/tabs_controller.h"

namespace OHOS::Ace::NG::GeneratedModifier {
class TabsControllerPeerImpl : public Referenced {
public:
    TabsControllerPeerImpl() = default;

    void SetTargetController(const WeakPtr<TabsControllerNG> &controller)
    {
        CHECK_NULL_VOID(!controller.Invalid());
        controllerWeakPtr_ = controller;
    }

    void TriggerChangeIndex(int32_t index) const
    {
        index = index < 0 ? 0 : index;

        auto controller = controllerWeakPtr_.Upgrade();
        CHECK_NULL_VOID(controller);

        const auto& updateCubicCurveCallback = controller->GetUpdateCubicCurveCallback();
        if (updateCubicCurveCallback != nullptr) {
            updateCubicCurveCallback();
        }
        controller->SwipeTo(index);
    }

    void TriggerPreloadItems(const std::set<int32_t>& indexSet) const
    {
        auto controller = controllerWeakPtr_.Upgrade();
        CHECK_NULL_VOID(controller);
        controller->PreloadItems(indexSet);
    }

    void TriggerSetTabBarTranslate(const NG::TranslateOptions& translate) const
    {
        auto controller = controllerWeakPtr_.Upgrade();
        CHECK_NULL_VOID(controller);
        controller->SetTabBarTranslate(translate);
    }

    void TriggerSetTabBarOpacity(const double opacity) const
    {
        auto controller = controllerWeakPtr_.Upgrade();
        CHECK_NULL_VOID(controller);
        controller->SetTabBarOpacity(std::clamp(opacity, 0.0, 1.0));
    }

private:
    Ace::WeakPtr<TabsControllerNG> controllerWeakPtr_;
};
} // namespace OHOS::Ace::NG::GeneratedModifier

struct TabsControllerPeer : public OHOS::Ace::NG::GeneratedModifier::TabsControllerPeerImpl {};
#endif //FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_TABS_CONTROLLER_PEER_IMPL_H
