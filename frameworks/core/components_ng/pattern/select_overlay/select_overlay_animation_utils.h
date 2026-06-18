/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECT_OVERLAY_SELECT_OVERLAY_ANIMATION_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECT_OVERLAY_SELECT_OVERLAY_ANIMATION_UTILS_H

#include "base/utils/system_properties.h"
#include "core/common/container.h"
#include "core/components/common/properties/ui_material.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

inline bool UseNewMaterial(const RefPtr<FrameNode>& frameNode = nullptr)
{
    bool disableNewMaterialByCCM = MaterialUtils::GetConfiguredMaterialState() == MaterialState::DEFAULT &&
        !SystemProperties::IsDeviceSystemMaterialSupported();
    if (frameNode) {
        return frameNode->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY_SIX) &&
               !MaterialUtils::IsMaterialDisabled() && !disableNewMaterialByCCM;
    }
    return Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY_SIX) &&
           !MaterialUtils::IsMaterialDisabled() && !disableNewMaterialByCCM;
}

inline bool UseNewAnimation(const RefPtr<FrameNode>& frameNode = nullptr)
{
    return UseNewMaterial(frameNode) && SystemProperties::GetUiMaterialLevel() != UiMaterialLevel::SMOOTH;
}

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECT_OVERLAY_SELECT_OVERLAY_ANIMATION_UTILS_H
