/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "compatible/components/text_field/modifier/text_field_modifier.h"

#include "compatible/components/text_field/render_text_field.h"
#include "compatible/components/text_field/rosen_render_text_field.h"
#include "interfaces/inner_api/ace_kit/include/ui/base/ace_type.h"

#include "frameworks/core/components/text_overlay/render_text_overlay.h"

namespace OHOS::Ace::TextFieldModifier {
namespace {
void SetEditingValue(const RefPtr<RenderTextField>& textfield, std::string selectedText)
{
    CHECK_NULL_VOID(textfield);
    auto value = textfield->GetEditingValue();
    value.Append(selectedText);
    textfield->SetEditingValue(std::move(value));
}

std::string GetEditingValue(const RefPtr<RenderTextField>& textfield)
{
    CHECK_NULL_RETURN(textfield, "");
    return textfield->GetEditingValue().GetSelectedText();
}

int32_t GetTextEditingEnd(const RefPtr<RenderTextField>& textfield)
{
    CHECK_NULL_RETURN(textfield, 0);
    return textfield->GetEditingValue().selection.GetEnd();
}

int32_t GetEditingStart(const RefPtr<RenderTextField>& textfield)
{
    CHECK_NULL_RETURN(textfield, 0);
    return textfield->GetEditingValue().selection.GetStart();
}

int32_t GetEditingEnd(const RefPtr<RenderTextField>& textfield)
{
    CHECK_NULL_RETURN(textfield, 0);
    return textfield->GetEditingValue().selection.GetEnd();
}

bool LiftPanelForVirtualKeyboard(const RefPtr<RenderTextField>& textfield, double fullHeight, double offsetY)
{
    CHECK_NULL_RETURN(textfield, false);
    auto slidingPanelParent = textfield->GetSlidingPanelAncest();
    CHECK_NULL_RETURN(slidingPanelParent, false);
    if (GreatNotEqual(textfield->GetPaintRect().Height() + textfield->GetGlobalOffset().GetY(), fullHeight)) {
        LOGI("Raising panel with offset %{public}f",
            textfield->GetPaintRect().Height() + textfield->GetGlobalOffset().GetY() - fullHeight);
        offsetY -= textfield->GetPaintRect().Height() + textfield->GetGlobalOffset().GetY() - fullHeight;
    }
    slidingPanelParent->LiftPanelForVirtualKeyboard(offsetY);
    return true;
}

bool UpdatePanelHeightByCurrentMode(const RefPtr<RenderTextField>& textfield)
{
    CHECK_NULL_RETURN(textfield, false);
    auto slidingPanelParent = textfield->GetSlidingPanelAncest();
    CHECK_NULL_RETURN(slidingPanelParent, false);
    slidingPanelParent->UpdatePanelHeightByCurrentMode();
    return true;
}

void SetIsOverlayShowed(const RefPtr<RenderTextField>& textfield, bool value, bool needStart)
{
    CHECK_NULL_VOID(textfield);
    textfield->SetIsOverlayShowed(value, needStart);
    textfield->SetTextOverlayPushed(false);
}

void SetUpdateHandlePosition(
    const RefPtr<RenderTextField>& textfield, const std::function<void(const OverlayShowOption&)>& updateHandlePosition)
{
    CHECK_NULL_VOID(textfield);
    textfield->SetUpdateHandlePosition(updateHandlePosition);
}

void SetUpdateHandleDiameter(
    const RefPtr<RenderTextField>& textfield, const std::function<void(const double&)>& updateHandleDiameter)
{
    CHECK_NULL_VOID(textfield);
    textfield->SetUpdateHandleDiameter(updateHandleDiameter);
}

void SetUpdateHandleDiameterInner(
    const RefPtr<RenderTextField>& textfield, const std::function<void(const double&)>& updateHandleDiameterInner)
{
    CHECK_NULL_VOID(textfield);
    textfield->SetUpdateHandleDiameterInner(updateHandleDiameterInner);
}

void SetOnValueChange(const RefPtr<RenderTextField>& textfield, const std::function<void()>& onValueChange)
{
    CHECK_NULL_VOID(textfield);
    textfield->SetOnValueChange(onValueChange);
}

void SetOnKeyboardClose(const RefPtr<RenderTextField>& textfield, const std::function<void(bool)>& onKeyboardClose)
{
    CHECK_NULL_VOID(textfield);
    textfield->SetOnKeyboardClose(onKeyboardClose);
}

void SetOnClipRectChanged(
    const RefPtr<RenderTextField>& textfield, const std::function<void(const Rect&)>& onClipRectChanged)
{
    CHECK_NULL_VOID(textfield);
    textfield->SetOnClipRectChanged(onClipRectChanged);
}
} // namespace
const ArkUITextFieldModifierCompatible* GetTextFieldModifier()
{
    static const ArkUITextFieldModifierCompatible instance = {
        .setEditingValue = SetEditingValue,
        .getEditingValue = GetEditingValue,
        .getTextEditingEnd = GetTextEditingEnd,
        .getEditingStart = GetEditingStart,
        .getEditingEnd = GetEditingEnd,
        .liftPanelForVirtualKeyboard = LiftPanelForVirtualKeyboard,
        .updatePanelHeightByCurrentMode = UpdatePanelHeightByCurrentMode,
        .setIsOverlayShowed = SetIsOverlayShowed,
        .setUpdateHandlePosition = SetUpdateHandlePosition,
        .setUpdateHandleDiameter = SetUpdateHandleDiameter,
        .setUpdateHandleDiameterInner = SetUpdateHandleDiameterInner,
        .setOnValueChange = SetOnValueChange,
        .setOnKeyboardClose = SetOnKeyboardClose,
        .setOnClipRectChanged = SetOnClipRectChanged,
    };
    return &instance;
}
} // namespace OHOS::Ace::TextFieldModifier