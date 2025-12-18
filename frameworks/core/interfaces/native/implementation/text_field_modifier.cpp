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

#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"
#include "core/common/container.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract_model_static.h"
#include "core/components_ng/pattern/text_field/text_field_model_static.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/validators.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TextFieldModifier {
void SetWidthImpl(Ark_NativePointer node, const Opt_Union_Length_LayoutPolicy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Converter::VisitUnion(*value,
        [frameNode](const Ark_Length& value) {
            auto result = Converter::OptConvert<CalcDimension>(value);
            TextFieldModelStatic::SetWidthAuto(frameNode, false);
            Validator::ValidateNonNegative(result);
            if (!result) {
                ViewAbstract::ClearWidthOrHeight(frameNode, true);
                return;
            }
            ViewAbstractModelStatic::SetWidth(frameNode, *result);
        },
        [frameNode](const Ark_LayoutPolicy& value) {
            LOGE("ARKOALA: SetWidthImpl: Ark_LayoutPolicy is not supported.\n");
        },
        []() {}
    );
}
void SetHeightImpl(Ark_NativePointer node, const Opt_Union_Length_LayoutPolicy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Converter::VisitUnion(*value,
        [frameNode](const Ark_Length& value) {
            auto result = Converter::OptConvert<CalcDimension>(value);
            Validator::ValidateNonNegative(result);
            if (!result) {
                ViewAbstract::ClearWidthOrHeight(frameNode, false);
                return;
            }
            ViewAbstractModelStatic::SetHeight(frameNode, *result);
        },
        [frameNode](const Ark_LayoutPolicy& value) {
            LOGE("ARKOALA: SetHeightImpl: Ark_LayoutPolicy is not supported.\n");
        },
        []() {}
    );
}
void SetPaddingImpl(Ark_NativePointer node, const Opt_Union_Padding_Length_LocalizedPadding* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto padding = Converter::OptConvertPtr<PaddingProperty>(value);
    ViewAbstractModelStatic::SetPadding(frameNode, padding);
    if (padding) {
        TextFieldModelStatic::SetPadding(frameNode, padding.value(), false);
    } else {
        TextFieldModelStatic::SetPadding(frameNode, NG::PaddingProperty(), true);
    }
}
void SetMarginImpl(Ark_NativePointer node, const Opt_Union_Padding_Length_LocalizedPadding* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstractModelStatic::SetMargin(frameNode, Converter::OptConvertPtr<PaddingProperty>(value));
    TextFieldModelStatic::SetMargin(frameNode);
}
void SetBorderImpl(Ark_NativePointer node, const Opt_BorderOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    CHECK_NULL_VOID(optValue);
    auto style = Converter::OptConvert<BorderStyleProperty>(optValue->style);
    if (style) {
        ViewAbstractModelStatic::SetBorderStyle(frameNode, style.value());
    }
    auto width = Converter::OptConvert<BorderWidthProperty>(optValue->width);
    if (width) {
        ViewAbstractModelStatic::SetBorderWidth(frameNode, width.value());
    }
    auto color = Converter::OptConvert<BorderColorProperty>(optValue->color);
    if (color) {
        ViewAbstractModelStatic::SetBorderColor(frameNode, color.value());
    }
    auto radius = Converter::OptConvert<BorderRadiusProperty>(optValue->radius);
    if (radius) {
        ViewAbstractModelStatic::SetBorderRadius(frameNode, radius.value());
    }
    auto dashGap = Converter::OptConvert<BorderWidthProperty>(optValue->dashGap);
    if (dashGap) {
        ViewAbstractModelStatic::SetDashGap(frameNode, dashGap.value());
    }
    auto dashWidth = Converter::OptConvert<BorderWidthProperty>(optValue->dashWidth);
    if (dashWidth) {
        ViewAbstractModelStatic::SetDashWidth(frameNode, dashWidth.value());
    }
    TextFieldModelStatic::SetBackBorder(frameNode);
}
void SetBorderWidthImpl(Ark_NativePointer node, const Opt_Union_Length_EdgeWidths_LocalizedEdgeWidths* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto width = Converter::OptConvertPtr<BorderWidthProperty>(value);
    if (width) {
        ViewAbstractModelStatic::SetBorderWidth(frameNode, width.value());
    }
    TextFieldModelStatic::SetBackBorder(frameNode);
}
void SetBorderColorImpl(Ark_NativePointer node, const Opt_Union_ResourceColor_EdgeColors_LocalizedEdgeColors* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto color = Converter::OptConvertPtr<BorderColorProperty>(value);
    if (color) {
        ViewAbstractModelStatic::SetBorderColor(frameNode, color.value());
    }
    TextFieldModelStatic::SetBackBorder(frameNode);
}
void SetBorderStyleImpl(Ark_NativePointer node, const Opt_Union_BorderStyle_EdgeStyles* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto style = Converter::OptConvertPtr<BorderStyleProperty>(value);
    if (style) {
        ViewAbstractModelStatic::SetBorderStyle(frameNode, style.value());
    }
    TextFieldModelStatic::SetBackBorder(frameNode);
}
void SetBorderRadiusImpl(Ark_NativePointer node, const Opt_Union_Length_BorderRadiuses_LocalizedBorderRadiuses* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto radiuses = Converter::OptConvertPtr<BorderRadiusProperty>(value);
    if (radiuses) {
        ViewAbstractModelStatic::SetBorderRadius(frameNode, radiuses.value());
    }
    TextFieldModelStatic::SetBackBorder(frameNode);
}
void SetBackgroundColorImpl(Ark_NativePointer node, const Opt_Union_ResourceColor_ColorMetrics* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto color = Converter::OptConvertPtr<Color>(value);
    ViewAbstractModelStatic::SetBackgroundColor(frameNode, color);
    TextFieldModelStatic::SetBackgroundColor(frameNode, color);
}
} // namespace TextFieldModifier
}
