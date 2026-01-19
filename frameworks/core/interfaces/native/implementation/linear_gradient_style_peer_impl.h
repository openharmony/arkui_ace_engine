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

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_LINEAR_GRADIENT_STYLE_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_LINEAR_GRADIENT_STYLE_PEER_IMPL_H

#include <optional>
#include <string>
#include "arkoala_api_generated.h"
#include "core/interfaces/native/implementation/shader_style_peer_impl.h"
#include "core/interfaces/native/utility/peer_utils.h"

struct LinearGradientStylePeer final : ShaderStylePeer {
protected:
    explicit LinearGradientStylePeer(
        std::optional<OHOS::Ace::NG::Gradient> optLinearGradientOptions
    ) : ShaderStylePeer(ShaderStyleType::LINEAR_GRADIENT, optLinearGradientOptions) {}
    ~LinearGradientStylePeer() override = default;
    friend OHOS::Ace::NG::PeerUtils;
};

#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_LINEAR_GRADIENT_STYLE_PEER_IMPL_H