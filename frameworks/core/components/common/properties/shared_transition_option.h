/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_SHARED_TRANSITION_OPTION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_SHARED_TRANSITION_OPTION_H

#include <string>

#include "core/animation/curve.h"
#include "core/animation/shared_transition_effect.h"
#include "core/components/common/properties/motion_path_option.h"

namespace OHOS::Ace {

struct SharedTransitionOption {
    int32_t duration = 0;
    int32_t delay = 0;
    int32_t zIndex = 0;
    RefPtr<Curve> curve;
    MotionPathOption motionPathOption;
    SharedTransitionEffectType type = SharedTransitionEffectType::SHARED_EFFECT_EXCHANGE;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_SHARED_TRANSITION_OPTION_H
