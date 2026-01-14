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

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_SHADER_STYLE_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_SHADER_STYLE_PEER_IMPL_H

#include <optional>
#include <string>
#include "core/interfaces/native/utility/peer_utils.h"
#include "interfaces/inner_api/ace_kit/include/ui/properties/gradient_property.h"

enum class ShaderStyleType {
    UNKNOWN = 0,
    LINEAR_GRADIENT = 1,
    RADIAL_GRADIENT = 2,
    SOLID_COLOR = 3,
};

struct ShaderStylePeer {
    const ShaderStyleType type;
    std::optional<OHOS::Ace::NG::Gradient> gradientOptions;
    std::optional<OHOS::Ace::Color> colorValue;

protected:
    explicit ShaderStylePeer(ShaderStyleType shaderStyleType = ShaderStyleType::UNKNOWN,
        std::optional<OHOS::Ace::NG::Gradient> gradientOptions = std::nullopt,
        std::optional<OHOS::Ace::Color> optColorValue = std::nullopt)
        : type(shaderStyleType), gradientOptions(gradientOptions),
          colorValue(optColorValue) {}
    virtual ~ShaderStylePeer() = default;
    friend OHOS::Ace::NG::PeerUtils;
};

#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_SHADER_STYLE_PEER_IMPL_H