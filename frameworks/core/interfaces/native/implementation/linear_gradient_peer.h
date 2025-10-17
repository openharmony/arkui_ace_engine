/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_LINEAR_GRADIENT_PEER_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_LINEAR_GRADIENT_PEER_H

#include "base/geometry/dimension.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/gauge/gauge_model_static.h"
#include "core/interfaces/native/utility/peer_utils.h"

struct LinearGradientPeer final {
    using LinearGradientColorSteps = OHOS::Ace::NG::GaugeModelStatic::LinearGradientColorSteps;

    LinearGradientColorSteps colorStops;

protected:
    explicit LinearGradientPeer(const LinearGradientColorSteps& src) : colorStops(src) {}
    ~LinearGradientPeer() = default;
    friend OHOS::Ace::NG::PeerUtils;
};
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_LINEAR_GRADIENT_PEER_H
