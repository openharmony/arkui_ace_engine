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
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components_ng/pattern/rich_editor_drag/rich_editor_drag_info.h"
#include "core/components_ng/pattern/rich_editor_drag/rich_editor_drag_overlay_modifier.h"
#include "core/components_ng/pattern/rich_editor_drag/rich_editor_drag_paint_method.h"
#include "core/components_ng/pattern/text_drag/text_drag_pattern.h"

namespace OHOS::Ace::NG {
constexpr int32_t CONSTANT_DOUBLE = 2;
RichEditorDragPaintMethod::RichEditorDragPaintMethod(const WeakPtr<Pattern>& pattern,
    const RefPtr<TextDragOverlayModifier>& overlayMod, const RefPtr<RichEditorDragContentModifier>& contentMod,
    const TextDragInfo& info)
    : TextDragPaintMethod(pattern, overlayMod), contentModifier_(contentMod), info_(info)
{}

RefPtr<Modifier> RichEditorDragPaintMethod::GetContentModifier(PaintWrapper* paintWrapper)
{
    return contentModifier_;
}

void RichEditorDragPaintMethod::UpdateContentModifier(PaintWrapper* paintWrapper)
{
    auto pipleline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipleline);
    auto textOverlayTheme = pipleline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_VOID(textOverlayTheme);
    auto modifier = DynamicCast<RichEditorDragOverlayModifier>(overlayModifier_);
    CHECK_NULL_VOID(modifier);
    auto handleDiameter = textOverlayTheme->GetHandleDiameter().ConvertToPx();
    modifier->SetHandleRadius(handleDiameter / 2.0f);
    if (!AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        modifier->SetHandleColor(textOverlayTheme->GetHandleColor());
    } else {
        modifier->SetHandleColor(info_.handleColor.value_or(textOverlayTheme->GetHandleColor()));
    }
    modifier->SetInnerHandleRadius(textOverlayTheme->GetHandleDiameterInner().ConvertToPx() / 2.0f);
    modifier->SetInnerHandleColor(textOverlayTheme->GetHandleColorInner());
    auto pattern = DynamicCast<TextDragPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    auto screenWdith = SystemProperties::GetDevicePhysicalWidth();
    auto screenHeight = SystemProperties::GetDevicePhysicalHeight();
    RectF boundsRect(-handleDiameter - screenWdith, -handleDiameter - screenHeight,
        pattern->GetFrameWidth() + (screenWdith + handleDiameter) * CONSTANT_DOUBLE,
        pattern->GetFrameHeight() + (screenHeight + handleDiameter) * CONSTANT_DOUBLE);
    modifier->SetBoundsRect(boundsRect);
    CHECK_NULL_VOID(paintWrapper);
    auto offset = paintWrapper->GetGeometryNode()->GetFrameOffset();
    modifier->SetFirstHandle(info_.firstHandle - offset);
    modifier->SetSecondHandle(info_.secondHandle - offset);
    auto textTheme = pipleline->GetTheme<TextTheme>();
    CHECK_NULL_VOID(textTheme);
    auto selectorColor = info_.selectedBackgroundColor.value_or(textTheme->GetSelectedColor());
    modifier->SetSelectedColor(selectorColor.GetValue());
    modifier->SetDragBackgroundColor(info_.dragBackgroundColor);
    modifier->SetIsDragShadowNeeded(info_.isDragShadowNeeded);
    modifier->SetIsFirstHandleAnimated(info_.isFirstHandleAnimation);
    modifier->SetIsSecondHandleAnimated(info_.isSecondHandleAnimation);
}
} // namespace OHOS::Ace::NG
