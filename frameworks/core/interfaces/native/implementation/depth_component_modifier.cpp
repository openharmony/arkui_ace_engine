/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace DepthComponentModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // DepthComponentModifier
namespace DepthComponentInterfaceModifier {
void SetDepthComponentOptionsImpl(Ark_NativePointer node,
                                  const Ark_ResourceStr* background,
                                  const Opt_DepthComponentOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(background);
    //auto convValue = Converter::OptConvert<type>(background); // for enums
    // DepthComponentModelNG::SetSetDepthComponentOptions(frameNode, convValue);
}
} // DepthComponentInterfaceModifier
namespace DepthComponentAttributeModifier {
void SetDepthMapImpl(Ark_NativePointer node,
                     const Ark_Union_ResourceStr_image_PixelMap* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    // DepthComponentModelNG::SetSetDepthMap(frameNode, convValue);
}
void SetCameraImpl(Ark_NativePointer node,
                   const Ark_DepthCameraParams* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    // DepthComponentModelNG::SetSetCamera(frameNode, convValue);
}
void SetLightImpl(Ark_NativePointer node,
                  const Ark_DepthLightParams* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    // DepthComponentModelNG::SetSetLight(frameNode, convValue);
}
void SetBackgroundOffsetImpl(Ark_NativePointer node,
                             const Ark_Union_Position_Edges_LocalizedEdges* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    // DepthComponentModelNG::SetSetBackgroundOffset(frameNode, convValue);
}
void SetBackgroundScaleImpl(Ark_NativePointer node,
                            const Ark_ScaleOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    // DepthComponentModelNG::SetSetBackgroundScale(frameNode, convValue);
}
} // DepthComponentAttributeModifier
const GENERATED_ArkUIDepthComponentModifier* GetDepthComponentModifier()
{
    static const GENERATED_ArkUIDepthComponentModifier ArkUIDepthComponentModifierImpl {
        DepthComponentModifier::ConstructImpl,
        DepthComponentInterfaceModifier::SetDepthComponentOptionsImpl,
        DepthComponentAttributeModifier::SetDepthMapImpl,
        DepthComponentAttributeModifier::SetCameraImpl,
        DepthComponentAttributeModifier::SetLightImpl,
        DepthComponentAttributeModifier::SetBackgroundOffsetImpl,
        DepthComponentAttributeModifier::SetBackgroundScaleImpl,
    };
    return &ArkUIDepthComponentModifierImpl;
}
}
