/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/text_drag/text_drag_paint_method.h"
#include "core/components_ng/pattern/text_drag/text_drag_pattern.h"

namespace OHOS::Ace::NG {
constexpr float CONSTANT_DOUBLE = 2.0f;
TextDragPaintMethod::TextDragPaintMethod(const WeakPtr<Pattern>& pattern,
    const RefPtr<TextDragOverlayModifier>& textDragOverlayModifier) : pattern_(pattern),
    overlayModifier_(textDragOverlayModifier) {}

RefPtr<Modifier> TextDragPaintMethod::GetOverlayModifier(PaintWrapper* paintWrapper)
{
    return overlayModifier_;
}

void TextDragPaintMethod::UpdateHandleInfo(const TextDragInfo& info)
{
    auto pipleline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipleline);
    auto textOverlayTheme = pipleline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_VOID(textOverlayTheme);
    auto modifier = DynamicCast<TextDragOverlayModifier>(overlayModifier_);
    CHECK_NULL_VOID(modifier);
    auto handleDiameter = textOverlayTheme->GetHandleDiameter().ConvertToPx();
    modifier->SetHandleRadius(handleDiameter / CONSTANT_DOUBLE);
    if (!AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        modifier->SetHandleColor(textOverlayTheme->GetHandleColor());
    } else {
        modifier->SetHandleColor(info.handleColor.value());
    }
    modifier->SetInnerHandleRadius(textOverlayTheme->GetHandleDiameterInner().ConvertToPx() / CONSTANT_DOUBLE);
    modifier->SetInnerHandleColor(textOverlayTheme->GetHandleColorInner());
    modifier->SetFirstHandle(info.firstHandle);
    modifier->SetSecondHandle(info.secondHandle);
    auto pattern = DynamicCast<TextDragPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    auto screenWdith = SystemProperties::GetDevicePhysicalWidth();
    auto screenHeight = SystemProperties::GetDevicePhysicalHeight();
    RectF boundsRect(-handleDiameter - screenWdith, -handleDiameter - screenHeight,
        pattern->GetFrameWidth() + (screenWdith + handleDiameter) * CONSTANT_DOUBLE,
        pattern->GetFrameHeight() + (screenHeight + handleDiameter) * CONSTANT_DOUBLE);
    modifier->SetBoundsRect(boundsRect);
    auto selectorColor = info.selectedBackgroundColor;
    modifier->SetSelectedColor(selectorColor->GetValue());
    modifier->SetIsInline(info.isInline);
}
} // namespace OHOS::Ace::NG
