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
#include "core/interfaces/arkoala/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace DataPanelInterfaceModifier {
void SetDataPanelOptionsImpl(Ark_NativePointer node,
                             const Ark_DataPanelOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    //auto convValue = Converter::OptConvert<type_name>(*options);
    //DataPanelModelNG::SetSetDataPanelOptions(frameNode, convValue);
}
} // DataPanelInterfaceModifier
namespace DataPanelAttributeModifier {
void CloseEffectImpl(Ark_NativePointer node,
                     Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //DataPanelModelNG::SetCloseEffect(frameNode, convValue);
}
void ValueColorsImpl(Ark_NativePointer node,
                     const Array_Union_ResourceColor_LinearGradient* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //DataPanelModelNG::SetValueColors(frameNode, convValue);
}
void TrackBackgroundColorImpl(Ark_NativePointer node,
                              const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //DataPanelModelNG::SetTrackBackgroundColor(frameNode, convValue);
}
void StrokeWidthImpl(Ark_NativePointer node,
                     const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //DataPanelModelNG::SetStrokeWidth(frameNode, convValue);
}
void TrackShadowImpl(Ark_NativePointer node,
                     const Ark_DataPanelShadowOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //DataPanelModelNG::SetTrackShadow(frameNode, convValue);
}
void ContentModifierImpl(Ark_NativePointer node,
                         const Ark_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //DataPanelModelNG::SetContentModifier(frameNode, convValue);
}
} // DataPanelAttributeModifier
const GENERATED_ArkUIDataPanelModifier* GetDataPanelModifier()
{
    static const GENERATED_ArkUIDataPanelModifier ArkUIDataPanelModifierImpl {
        DataPanelInterfaceModifier::SetDataPanelOptionsImpl,
        DataPanelAttributeModifier::CloseEffectImpl,
        DataPanelAttributeModifier::ValueColorsImpl,
        DataPanelAttributeModifier::TrackBackgroundColorImpl,
        DataPanelAttributeModifier::StrokeWidthImpl,
        DataPanelAttributeModifier::TrackShadowImpl,
        DataPanelAttributeModifier::ContentModifierImpl,
    };
    return &ArkUIDataPanelModifierImpl;
}

}
