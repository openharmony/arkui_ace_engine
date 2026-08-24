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

// SORTED_SECTION
#include "core/components_ng/base/view_abstract_model_static.h"
#include "core/interfaces/native/node/node_text_input_modifier.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/validators.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace {
const ArkUITextInputCustomModifier* GetTextFieldCustomModifier()
{
    return NodeModifier::GetTextInputCustomModifier();
}

void SetTextFieldWidthAuto(FrameNode* frameNode, bool value)
{
    auto* modifier = GetTextFieldCustomModifier();
    CHECK_NULL_VOID(modifier);
    modifier->setTextFieldWidthAuto(frameNode, value);
}

void SetTextFieldPadding(FrameNode* frameNode, const PaddingProperty& newPadding, bool tmp)
{
    auto* modifier = GetTextFieldCustomModifier();
    CHECK_NULL_VOID(modifier);
    modifier->setTextFieldPadding(frameNode, newPadding, tmp);
}

void SetTextFieldMargin(FrameNode* frameNode)
{
    auto* modifier = GetTextFieldCustomModifier();
    CHECK_NULL_VOID(modifier);
    modifier->setTextFieldMargin(frameNode);
}

void SetTextFieldBackBorder(FrameNode* frameNode)
{
    auto* modifier = GetTextFieldCustomModifier();
    CHECK_NULL_VOID(modifier);
    modifier->setTextFieldBackBorder(frameNode);
}

void SetTextFieldBackgroundColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    auto* modifier = GetTextFieldCustomModifier();
    CHECK_NULL_VOID(modifier);
    modifier->setTextFieldBackgroundColor(frameNode, color);
}

void SetTextFieldTextColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    auto* modifier = GetTextFieldCustomModifier();
    CHECK_NULL_VOID(modifier);
    modifier->setTextFieldTextColor(frameNode, color);
}

void UpdateTextFieldTextColor(FrameNode* frameNode, const Color& color)
{
    auto* modifier = GetTextFieldCustomModifier();
    CHECK_NULL_VOID(modifier);
    modifier->updateTextFieldTextColor(frameNode, color);
}

std::optional<BorderRadiusProperty> GetTextFieldThemeBorderRadius(FrameNode* frameNode)
{
    auto* modifier = GetTextFieldCustomModifier();
    CHECK_NULL_RETURN(modifier, std::nullopt);
    return modifier->getTextFieldThemeBorderRadius(frameNode);
}
} // namespace

namespace TextFieldModifier {
void SetWidthImpl(Ark_NativePointer node, const Opt_Union_Length_LayoutPolicy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Converter::VisitUnion(*value,
        [frameNode](const Ark_Length& value) {
            auto result = Converter::OptConvert<CalcDimension>(value);
            SetTextFieldWidthAuto(frameNode, false);
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
        SetTextFieldPadding(frameNode, padding.value(), false);
    } else {
        SetTextFieldPadding(frameNode, NG::PaddingProperty(), true);
    }
}
void SetMarginImpl(Ark_NativePointer node, const Opt_Union_Padding_Length_LocalizedPadding* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstractModelStatic::SetMargin(frameNode, Converter::OptConvertPtr<PaddingProperty>(value));
    SetTextFieldMargin(frameNode);
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
    SetTextFieldBackBorder(frameNode);
}
void SetBorderWidthImpl(Ark_NativePointer node, const Opt_Union_Length_EdgeWidths_LocalizedEdgeWidths* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto width = Converter::OptConvertPtr<BorderWidthProperty>(value);
    if (width) {
        ViewAbstractModelStatic::SetBorderWidth(frameNode, width.value());
    }
    SetTextFieldBackBorder(frameNode);
}
void SetBorderColorImpl(Ark_NativePointer node, const Opt_Union_ResourceColor_EdgeColors_LocalizedEdgeColors* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto color = Converter::OptConvertPtr<BorderColorProperty>(value);
    if (color) {
        ViewAbstractModelStatic::SetBorderColor(frameNode, color.value());
    }
    SetTextFieldBackBorder(frameNode);
}
void SetBorderStyleImpl(Ark_NativePointer node, const Opt_Union_BorderStyle_EdgeStyles* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto style = Converter::OptConvertPtr<BorderStyleProperty>(value);
    if (style) {
        ViewAbstractModelStatic::SetBorderStyle(frameNode, style.value());
    }
    SetTextFieldBackBorder(frameNode);
}
void SetBorderRadiusImpl(Ark_NativePointer node, const Opt_Union_Length_BorderRadiuses_LocalizedBorderRadiuses* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto radiuses = Converter::OptConvertPtr<BorderRadiusProperty>(value);
    if (!radiuses) {
        auto defaultBorderRadius = GetTextFieldThemeBorderRadius(frameNode);
        if (!defaultBorderRadius) {
            return;
        }
        ViewAbstractModelStatic::SetBorderRadius(frameNode, defaultBorderRadius.value());
        return;
    }
    ViewAbstractModelStatic::SetBorderRadius(frameNode, radiuses.value());
    SetTextFieldBackBorder(frameNode);
}
void SetBackgroundColorImpl(Ark_NativePointer node, const Opt_Union_ResourceColor_ColorMetricsExt* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto color = Converter::OptConvertPtr<Color>(value);
    ViewAbstractModelStatic::SetBackgroundColor(frameNode, color);
    SetTextFieldBackgroundColor(frameNode, color);
}
void SetForegroundColorImpl(Ark_NativePointer node, const Opt_Union_ResourceColor_ColoringStrategy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Converter::VisitUnionPtr(value,
        [frameNode](const Ark_ResourceColor& resourceColor) {
            auto colorOpt = Converter::OptConvertColorForMaterial(resourceColor);
            SetTextFieldTextColor(frameNode, colorOpt);
        },
        [frameNode](const Ark_ColoringStrategy& colorStrategy) {
            auto colorStrategyOpt = Converter::OptConvert<ForegroundColorStrategy>(colorStrategy);
            if (colorStrategyOpt.has_value()) {
                ViewAbstractModelStatic::SetForegroundColorStrategy(frameNode, colorStrategyOpt.value());
                UpdateTextFieldTextColor(frameNode, Color::FOREGROUND);
            } else {
                SetTextFieldTextColor(frameNode, std::nullopt);
            }
        },
        []() {}
    );
}
} // namespace TextFieldModifier
}
