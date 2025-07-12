/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"
#include "rendering_context_settings_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RenderingContextSettingsAccessor {
void DestroyPeerImpl(Ark_RenderingContextSettings peer)
{
    RenderingContextSettingsPeer::Destroy(peer);
}
Ark_RenderingContextSettings CtorImpl(const Opt_Boolean* antialias)
{
    auto value = antialias ? Converter::OptConvert<bool>(*antialias) : std::nullopt;
    return RenderingContextSettingsPeer::Create(value);
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Opt_Boolean GetAntialiasImpl(Ark_RenderingContextSettings peer)
{
    auto invalid = Converter::ArkValue<Opt_Boolean>();
    CHECK_NULL_RETURN(peer, invalid);
    return Converter::ArkValue<Opt_Boolean>(peer->antialias);
}
void SetAntialiasImpl(Ark_RenderingContextSettings peer,
                      Ark_Boolean antialias)
{
    CHECK_NULL_VOID(peer);
    auto value = Converter::Convert<bool>(antialias);
    peer->antialias = value;
}
} // RenderingContextSettingsAccessor
const GENERATED_ArkUIRenderingContextSettingsAccessor* GetRenderingContextSettingsAccessor()
{
    static const GENERATED_ArkUIRenderingContextSettingsAccessor RenderingContextSettingsAccessorImpl {
        RenderingContextSettingsAccessor::DestroyPeerImpl,
        RenderingContextSettingsAccessor::CtorImpl,
        RenderingContextSettingsAccessor::GetFinalizerImpl,
        RenderingContextSettingsAccessor::GetAntialiasImpl,
        RenderingContextSettingsAccessor::SetAntialiasImpl,
    };
    return &RenderingContextSettingsAccessorImpl;
}

}
