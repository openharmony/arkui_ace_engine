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

#ifdef WINDOW_SCENE_SUPPORTED
#include "core/components_ng/pattern/window_scene/scene/window_scene_model.h"
#else
#include "core/components_ng/pattern/window_scene/scene/window_scene_model.h"
#endif

#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace WindowSceneModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
#if defined(WINDOW_SCENE_SUPPORTED) || defined(ARKUI_CAPI_UNITTEST)
    auto frameNode = WindowSceneModel::CreateNode(id);
    if (frameNode) {
        frameNode->IncRefCount();
        return AceType::RawPtr(frameNode);
    }
#endif
    return {};
}
} // WindowSceneModifier
namespace WindowSceneInterfaceModifier {
void SetWindowSceneOptionsImpl(Ark_NativePointer node,
                               const Ark_Number* persistentId)
{
    CHECK_NULL_VOID(persistentId);
#if defined(WINDOW_SCENE_SUPPORTED) || defined(ARKUI_CAPI_UNITTEST)
    auto persistId = Converter::Convert<int32_t>(*persistentId);
    WindowSceneModel::Create(persistId);
#endif
}
} // WindowSceneInterfaceModifier
namespace WindowSceneAttributeModifier {
void AttractionEffectImpl(Ark_NativePointer node,
                          const Opt_Position* destination,
                          const Opt_Number* fraction)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optDestination = Converter::GetOptPtr(destination);
    auto x = optDestination ? Converter::OptConvert<Dimension>(optDestination->x) : std::nullopt;
    auto y = optDestination ? Converter::OptConvert<Dimension>(optDestination->y) : std::nullopt;
    AttractionEffect effect{};
    effect.fraction = Converter::OptConvert<float>(*fraction).value_or(effect.fraction);
    effect.destinationX = x.value_or(effect.destinationX);
    effect.destinationY = y.value_or(effect.destinationY);
#if defined(WINDOW_SCENE_SUPPORTED) || defined(ARKUI_CAPI_UNITTEST)
    WindowSceneModel::SetAttractionEffect(effect);
#endif
}
} // WindowSceneAttributeModifier
const GENERATED_ArkUIWindowSceneModifier* GetWindowSceneModifier()
{
    static const GENERATED_ArkUIWindowSceneModifier ArkUIWindowSceneModifierImpl {
        WindowSceneModifier::ConstructImpl,
        WindowSceneInterfaceModifier::SetWindowSceneOptionsImpl,
        WindowSceneAttributeModifier::AttractionEffectImpl,
    };
    return &ArkUIWindowSceneModifierImpl;
}

}
