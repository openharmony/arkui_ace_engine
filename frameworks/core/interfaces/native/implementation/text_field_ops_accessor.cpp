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
#include "core/interfaces/native/node/node_text_input_modifier.h"
#include "core/interfaces/native/utility/callback_helper.h"
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

void UpdateTextFieldValueAtCreation(FrameNode* frameNode, const std::optional<std::u16string>& value)
{
    auto* modifier = GetTextFieldCustomModifier();
    CHECK_NULL_VOID(modifier);
    modifier->updateTextFieldValueAtCreation(frameNode, value);
}

void SetTextFieldOnChangeEvent(FrameNode* frameNode, std::function<void(const std::u16string&)>&& func)
{
    auto* modifier = GetTextFieldCustomModifier();
    CHECK_NULL_VOID(modifier);
    modifier->setTextFieldOnChangeEvent(frameNode, std::move(func));
}
} // namespace

namespace TextFieldOpsAccessor {
Ark_NativePointer RegisterTextFieldValueCallbackImpl(Ark_NativePointer node,
                                                     const Ark_ResourceStr* value,
                                                     const TextFieldValueCallback* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode && value && callback, nullptr);
    auto text = Converter::OptConvert<std::u16string>(*value);

    UpdateTextFieldValueAtCreation(frameNode, text);
    auto onEvent = [arkCallback = CallbackHelper(*callback)](const std::u16string& content) {
        Converter::ConvContext ctx;
        auto arkContent = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(content, &ctx);
        arkCallback.InvokeSync(arkContent);
    };
    SetTextFieldOnChangeEvent(frameNode, std::move(onEvent));
    return node;
}
Ark_NativePointer TextFieldOpsSetWidthImpl(Ark_NativePointer node,
                                           const Opt_Union_Length_LayoutPolicy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
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
            LOGE("ARKOALA: TextFieldOpsSetWidthImpl: Ark_LayoutPolicy is not supported.\n");
        },
        []() {}
    );

    // todo: auto set
    // if (jsValue->IsString() && jsValue->ToString() == "auto") {
    //     ViewAbstractModel::ClearWidthOrHeight(frameNode, true);
    //     TextFieldModel::GetInstance()->SetWidthAuto(frameNode, true);
    //     return;
    // }

    return {};
}
Ark_NativePointer TextFieldOpsSetHeightImpl(Ark_NativePointer node,
                                            const Opt_Union_Length_LayoutPolicy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
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
            LOGE("ARKOALA: TextFieldOpsSetHeightImpl: Ark_LayoutPolicy is not supported.\n");
        },
        []() {}
    );
    return {};
}
Ark_NativePointer TextFieldOpsSetPaddingImpl(Ark_NativePointer node,
                                             const Opt_Union_Padding_Length_LocalizedPadding* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto padding = Converter::OptConvertPtr<PaddingProperty>(value);
    ViewAbstractModelStatic::SetPadding(frameNode, padding);
    if (padding) {
        SetTextFieldPadding(frameNode, padding.value(), false);
    } else {
        SetTextFieldPadding(frameNode, NG::PaddingProperty(), true);
    }
    return {};
}
Ark_NativePointer TextFieldOpsSetMarginImpl(Ark_NativePointer node,
                                            const Opt_Union_Padding_Length_LocalizedPadding* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    ViewAbstractModelStatic::SetMargin(frameNode, Converter::OptConvertPtr<PaddingProperty>(value));
    SetTextFieldMargin(frameNode);
    return {};
}
Ark_NativePointer TextFieldOpsSetBorderImpl(Ark_NativePointer node,
                                            const Opt_BorderOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto optValue = Converter::GetOptPtr(value);
    CHECK_NULL_RETURN(optValue, nullptr);
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
    return {};
}
Ark_NativePointer TextFieldOpsSetBorderWidthImpl(Ark_NativePointer node,
                                                 const Opt_Union_Length_EdgeWidths_LocalizedEdgeWidths* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto width = Converter::OptConvertPtr<BorderWidthProperty>(value);
    if (width) {
        ViewAbstractModelStatic::SetBorderWidth(frameNode, width.value());
    }
    SetTextFieldBackBorder(frameNode);
    return {};
}
Ark_NativePointer TextFieldOpsSetBorderColorImpl(Ark_NativePointer node,
                                                 const Opt_Union_ResourceColor_EdgeColors_LocalizedEdgeColors* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto color = Converter::OptConvertPtr<BorderColorProperty>(value);
    if (color) {
        ViewAbstractModelStatic::SetBorderColor(frameNode, color.value());
    }
    SetTextFieldBackBorder(frameNode);
    return {};
}
Ark_NativePointer TextFieldOpsSetBorderStyleImpl(Ark_NativePointer node,
                                                 const Opt_Union_BorderStyle_EdgeStyles* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto style = Converter::OptConvertPtr<BorderStyleProperty>(value);
    if (style) {
        ViewAbstractModelStatic::SetBorderStyle(frameNode, style.value());
    }
    SetTextFieldBackBorder(frameNode);
    return {};
}
Ark_NativePointer TextFieldOpsSetBorderRadiusImpl(Ark_NativePointer node,
                                                  const Opt_Union_Length_BorderRadiuses_LocalizedBorderRadiuses* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto radiuses = Converter::OptConvertPtr<BorderRadiusProperty>(value);
    if (radiuses) {
        ViewAbstractModelStatic::SetBorderRadius(frameNode, radiuses.value());
    }
    SetTextFieldBackBorder(frameNode);
    return {};
}
Ark_NativePointer TextFieldOpsSetBackgroundColorImpl(Ark_NativePointer node,
                                                     const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto color = Converter::OptConvertPtr<Color>(value);
    ViewAbstractModelStatic::SetBackgroundColor(frameNode, color);
    SetTextFieldBackgroundColor(frameNode, color);
    return {};
}
} // TextFieldOpsAccessor
const GENERATED_ArkUITextFieldOpsAccessor* GetTextFieldOpsAccessor()
{
    static const GENERATED_ArkUITextFieldOpsAccessor TextFieldOpsAccessorImpl {
        TextFieldOpsAccessor::RegisterTextFieldValueCallbackImpl,
        TextFieldOpsAccessor::TextFieldOpsSetWidthImpl,
        TextFieldOpsAccessor::TextFieldOpsSetHeightImpl,
        TextFieldOpsAccessor::TextFieldOpsSetPaddingImpl,
        TextFieldOpsAccessor::TextFieldOpsSetMarginImpl,
        TextFieldOpsAccessor::TextFieldOpsSetBorderImpl,
        TextFieldOpsAccessor::TextFieldOpsSetBorderWidthImpl,
        TextFieldOpsAccessor::TextFieldOpsSetBorderColorImpl,
        TextFieldOpsAccessor::TextFieldOpsSetBorderStyleImpl,
        TextFieldOpsAccessor::TextFieldOpsSetBorderRadiusImpl,
        TextFieldOpsAccessor::TextFieldOpsSetBackgroundColorImpl,
    };
    return &TextFieldOpsAccessorImpl;
}

}
