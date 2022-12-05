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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_RADIO_RADIO_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_RADIO_RADIO_PAINT_METHOD_H

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components_ng/render/canvas.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/node_paint_method.h"

namespace OHOS::Ace::NG {

enum class UIStatus {
    SELECTED = 0,
    UNSELECTED,
    FOCUS,
    ON_TO_OFF,
    OFF_TO_ON,
    PART,
    PART_TO_OFF,
    OFF_TO_PART,
    PART_TO_ON,
    ON_TO_PART,
};
class RadioPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(RadioPaintMethod, NodePaintMethod)

public:
    RadioPaintMethod(bool enabled, bool isTouch, bool isHover, float totalScale, float pointScale, UIStatus uiStatus)
        : enabled_(enabled), isTouch_(isTouch), isHover_(isHover), totalScale_(totalScale), pointScale_(pointScale),
          uiStatus_(uiStatus) {};
    ~RadioPaintMethod() override = default;
    CanvasDrawFunction GetContentDrawFunction(PaintWrapper* paintWrapper) override;

private:
    void InitializeParam();
    void PaintRadio(RSCanvas& canvas, bool checked, const SizeF& contentSize, const OffsetF& offset) const;
    void DrawUnselected(RSCanvas& canvas, const OffsetF& origin, RSPen& pen, SizeF& paintSize) const;
    void DrawTouchBoard(RSCanvas& canvas, const SizeF& contentSize, const OffsetF& offset) const;
    void DrawHoverBoard(RSCanvas& canvas, const SizeF& contentSize, const OffsetF& offset) const;

    float shadowWidth_ = 1.5f;
    float borderWidth_ = 1.5f;
    Color pointColor_ = Color::WHITE;
    Color activeColor_ = Color::BLUE;
    Color inactiveColor_ = Color::WHITE;
    Color shadowColor_ = Color::RED;
    Color clickEffectColor_ = Color::WHITE;
    Color hoverColor_ = Color::WHITE;
    Dimension hotZoneHorizontalPadding_ = 11.0_vp;

    bool enabled_ = true;
    bool isTouch_ = false;
    bool isHover_ = false;
    float totalScale_ = 1.0f;
    float pointScale_ = 0.5f;
    UIStatus uiStatus_ = UIStatus::UNSELECTED;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_RADIO_RADIO_PAINT_METHOD_H
