/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/node/nav_router_modifier.h"
#include "core/components_ng/pattern/navrouter/navrouter_model_ng.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"

namespace OHOS::Ace::NG::Converter {
template<>
std::optional<int32_t> Convert(const std::optional<NavRouteMode>& src)
{
    if (src.has_value()) {
        return static_cast<int32_t>(*src);
    }
    return std::nullopt;
}
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace NavRouterInterfaceModifier {
void SetNavRouterOptions0Impl(Ark_NativePointer node)
{
    // still it empty for save default values
}
void SetNavRouterOptions1Impl(Ark_NativePointer node,
                              const Ark_RouteInfo* value)
{
    LOGE("ARKOALA SetNavRouterOptions1 -> Method is not implemented.");
}
} // NavRouterInterfaceModifier
namespace NavRouterAttributeModifier {
void OnStateChangeImpl(Ark_NativePointer node,
                       Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onStateChangeCallback = [frameNode](const bool isActivated) {
        auto arkIsActiveted = Converter::ArkValue<Ark_Boolean>(isActivated);
        GetFullAPI()->getEventsAPI()->getNavRouterEventsReceiver()->onStateChange(frameNode->GetId(), arkIsActiveted);
    };
    NavRouterModelNG::SetOnStateChange(frameNode, onStateChangeCallback);
}
void ModeImpl(Ark_NativePointer node,
              enum Ark_NavRouteMode mode)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto enumMode = Converter::OptConvert<NavRouteMode>(mode);
    auto value = Converter::Convert<std::optional<int32_t>>(enumMode);
    NavRouterModelNG::SetNavRouteMode(frameNode, value);
}
} // NavRouterAttributeModifier
const GENERATED_ArkUINavRouterModifier* GetNavRouterModifier()
{
    static const GENERATED_ArkUINavRouterModifier ArkUINavRouterModifierImpl {
        NavRouterInterfaceModifier::SetNavRouterOptions0Impl,
        NavRouterInterfaceModifier::SetNavRouterOptions1Impl,
        NavRouterAttributeModifier::OnStateChangeImpl,
        NavRouterAttributeModifier::ModeImpl,
    };
    return &ArkUINavRouterModifierImpl;
}

}
