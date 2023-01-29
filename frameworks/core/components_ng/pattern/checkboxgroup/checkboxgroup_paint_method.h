/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_CHECKBOXGROUP_CHECKBOXGROUP_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_CHECKBOXGROUP_CHECKBOXGROUP_PAINT_METHOD_H

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components_ng/pattern/radio/radio_paint_method.h"
#include "core/components_ng/render/canvas.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/node_paint_method.h"

namespace OHOS::Ace::NG {

class CheckBoxGroupPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(CheckBoxGroupPaintMethod, NodePaintMethod)

public:
    CheckBoxGroupPaintMethod(bool enabled, bool isTouch, bool isHover, float shapeScale, UIStatus uiStatus)
        : enabled_(enabled), isTouch_(isTouch), isHover_(isHover), shapeScale_(shapeScale), uiStatus_(uiStatus) {};

    ~CheckBoxGroupPaintMethod() override = default;

    CanvasDrawFunction GetContentDrawFunction(PaintWrapper* paintWrapper) override;

    void SetHotZoneOffset(OffsetF& hotZoneOffset)
    {
        hotZoneOffset_ = hotZoneOffset;
    }

    void SetHotZoneSize(SizeF& hotZoneSize)
    {
        hotZoneSize_ = hotZoneSize;
    }

private:
    void InitializeParam();
    void PaintCheckBox(RSCanvas& canvas, PaintWrapper* paintWrapper) const;
    void DrawUnselected(RSCanvas& canvas, const OffsetF& origin, RSPen& pen, SizeF& paintSize) const;
    void DrawActiveBorder(RSCanvas& canvas, const OffsetF& paintOffset, RSBrush& brush, const SizeF& paintSize) const;
    void DrawUnselectedBorder(
        RSCanvas& canvas, const OffsetF& paintOffset, RSBrush& brush, const SizeF& paintSize) const;
    void DrawPart(RSCanvas& canvas, const OffsetF& origin, RSPen& pen, const SizeF& paintSize) const;
    void DrawTouchBoard(RSCanvas& canvas, const SizeF& contentSize, const OffsetF& offset) const;
    void DrawHoverBoard(RSCanvas& canvas, const SizeF& contentSize, const OffsetF& offset) const;
    void DrawAnimationOffToOn(RSCanvas& canvas, const OffsetF& origin, RSPen& pen, const SizeF& paintSize) const;
    void DrawAnimationOnToOff(RSCanvas& canvas, const OffsetF& origin, RSPen& pen, const SizeF& paintSize) const;

    float borderWidth_ = 0.0f;
    float borderRadius_ = 0.0f;
    float checkStroke_ = 0.0f;
    Color pointColor_;
    Color activeColor_;
    Color inactiveColor_;
    Color shadowColor_;
    Color clickEffectColor_;
    Color hoverColor_;
    Color inactivePointColor_;
    Dimension hoverRadius_;
    Dimension hotZoneHorizontalPadding_;
    Dimension hotZoneVerticalPadding_;
    Dimension shadowWidth_;

    bool enabled_ = true;
    bool isTouch_ = false;
    bool isHover_ = false;
    float shapeScale_ = 1.0f;
    UIStatus uiStatus_ = UIStatus::UNSELECTED;
    OffsetF hotZoneOffset_;
    SizeF hotZoneSize_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_CHECKBOXGROUP_CHECKBOXGROUP_PAINT_METHOD_H
