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
#include "core/components_ng/pattern/shape/shape_model_ng.h"
#include "core/interfaces/arkoala/utility/converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CommonShapeMethodModifier {
void StrokeImpl(Ark_NativePointer node,
                const ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    ShapeModelNG::SetStroke(frameNode, Converter::OptConvert<Color>(*value));
}
void FillImpl(Ark_NativePointer node,
              const ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    ShapeModelNG::SetFill(frameNode, Converter::OptConvert<Color>(*value));
}
void StrokeDashOffsetImpl(Ark_NativePointer node,
                          const Type_CommonShapeMethod_strokeDashOffset_Arg0* value)
{
}
void StrokeLineCapImpl(Ark_NativePointer node,
                       enum Ark_LineCapStyle value)
{
}
void StrokeLineJoinImpl(Ark_NativePointer node,
                        enum Ark_LineJoinStyle value)
{
}
void StrokeMiterLimitImpl(Ark_NativePointer node,
                          const Type_CommonShapeMethod_strokeMiterLimit_Arg0* value)
{
}
void StrokeOpacityImpl(Ark_NativePointer node,
                       const Type_CommonShapeMethod_strokeOpacity_Arg0* value)
{
}
void FillOpacityImpl(Ark_NativePointer node,
                     const Type_CommonShapeMethod_fillOpacity_Arg0* value)
{
}
void StrokeWidthImpl(Ark_NativePointer node,
                     const Ark_Length* value)
{
}
void AntiAliasImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
}
void StrokeDashArrayImpl(Ark_NativePointer node,
                         const Array_CustomObject* value)
{
}
} // CommonShapeMethodModifier
const GENERATED_ArkUICommonShapeMethodModifier* GetCommonShapeMethodModifier()
{
    static const GENERATED_ArkUICommonShapeMethodModifier ArkUICommonShapeMethodModifierImpl {
        CommonShapeMethodModifier::StrokeImpl,
        CommonShapeMethodModifier::FillImpl,
        CommonShapeMethodModifier::StrokeDashOffsetImpl,
        CommonShapeMethodModifier::StrokeLineCapImpl,
        CommonShapeMethodModifier::StrokeLineJoinImpl,
        CommonShapeMethodModifier::StrokeMiterLimitImpl,
        CommonShapeMethodModifier::StrokeOpacityImpl,
        CommonShapeMethodModifier::FillOpacityImpl,
        CommonShapeMethodModifier::StrokeWidthImpl,
        CommonShapeMethodModifier::AntiAliasImpl,
        CommonShapeMethodModifier::StrokeDashArrayImpl,
    };
    return &ArkUICommonShapeMethodModifierImpl;
}

}
