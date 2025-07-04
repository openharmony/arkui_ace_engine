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
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace DataPanelModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // DataPanelModifier
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
void SetCloseEffectImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //DataPanelModelNG::SetSetCloseEffect(frameNode, convValue);
}
void SetValueColorsImpl(Ark_NativePointer node,
                        const Opt_Array_Union_ResourceColor_LinearGradient* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //DataPanelModelNG::SetSetValueColors(frameNode, convValue);
}
void SetTrackBackgroundColorImpl(Ark_NativePointer node,
                                 const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //DataPanelModelNG::SetSetTrackBackgroundColor(frameNode, convValue);
}
void SetStrokeWidthImpl(Ark_NativePointer node,
                        const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto width = value ? Converter::OptConvertFromArkLength(value->value, DimensionUnit::VP) : std::nullopt;
    Validator::ValidateNonNegative(width);
    Validator::ValidateNonPercent(width);
    DataPanelModelStatic::SetStrokeWidth(frameNode, width);
}
void SetTrackShadowImpl(Ark_NativePointer node,
                        const Opt_DataPanelShadowOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //DataPanelModelNG::SetSetTrackShadow(frameNode, convValue);
}
void SetContentModifierImpl(Ark_NativePointer node,
                            const Opt_ContentModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //DataPanelModelNG::SetSetContentModifier(frameNode, convValue);
}
} // DataPanelAttributeModifier
const GENERATED_ArkUIDataPanelModifier* GetDataPanelModifier()
{
    static const GENERATED_ArkUIDataPanelModifier ArkUIDataPanelModifierImpl {
        DataPanelModifier::ConstructImpl,
        DataPanelInterfaceModifier::SetDataPanelOptionsImpl,
        DataPanelAttributeModifier::SetCloseEffectImpl,
        DataPanelAttributeModifier::SetValueColorsImpl,
        DataPanelAttributeModifier::SetTrackBackgroundColorImpl,
        DataPanelAttributeModifier::SetStrokeWidthImpl,
        DataPanelAttributeModifier::SetTrackShadowImpl,
        DataPanelAttributeModifier::SetContentModifierImpl,
    };
    return &ArkUIDataPanelModifierImpl;
}

}
