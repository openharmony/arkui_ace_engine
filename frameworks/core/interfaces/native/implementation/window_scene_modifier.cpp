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
    // auto frameNode = WindowSceneModel::CreateNode(id);
    // if (frameNode) {
    //     frameNode->IncRefCount();
    //     return AceType::RawPtr(frameNode);
    // }
    return {};
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
                          const Ark_Position* destination,
                          const Ark_Number* fraction)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(destination);
    CHECK_NULL_VOID(fraction);
    AttractionEffect effect;
    effect.fraction = Converter::Convert<float>(*fraction);
    effect.destinationX = CalcDimension(0);
    effect.destinationY = CalcDimension(0);
    if (auto x = Converter::OptConvert<Dimension>(destination->x); x) {
        effect.destinationX = x.value();
    }
    if (auto y = Converter::OptConvert<Dimension>(destination->y); y) {
        effect.destinationY = y.value();
    }
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
