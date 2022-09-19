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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_MODIFIER_H

#include "render_service_client/core/modifier/rs_extended_modifier.h"
#include "render_service_client/core/modifier/rs_modifier.h"
#include "render_service_client/core/ui/rs_node.h"

namespace OHOS::Ace {
using RSModifierBase = Rosen::RSModifierBase;
using RSNode = Rosen::RSNode;
using RSAnimationTimingProtocol = Rosen::RSAnimationTimingProtocol;
using RSAnimationTimingCurve = Rosen::RSAnimationTimingCurve;
template<typename T>
using RSAnimatableProperty = Rosen::RSAnimatableProperty<T>;
template<typename T>
using RSAnimatableArithmetic = Rosen::RSAnimatableArithmetic<T>;
template<typename T>
using RSContentStyleModifier = Rosen::RSContentStyleModifier<T>;
template<typename T>
using RSOverlayStyleModifier = Rosen::RSOverlayStyleModifier<T>;
using RSDrawingContext = Rosen::RSDrawingContext;
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_MODIFIER_H
