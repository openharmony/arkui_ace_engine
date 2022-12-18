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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWITCH_SWITCH_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWITCH_SWITCH_PAINT_METHOD_H

#include "core/components_ng/pattern/toggle/switch_paint_property.h"
#include "core/components_ng/render/canvas.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/components_ng/render/paint_wrapper.h"
#include "core/components_ng/render/render_context.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT SwitchPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(SwitchPaintMethod, NodePaintMethod)
public:
    explicit SwitchPaintMethod(float mainDelta, bool enabled, bool isTouch, bool isHover)
        : mainDelta_(mainDelta), enabled_(enabled), isTouch_(isTouch), isHover_(isHover) {};
    ~SwitchPaintMethod() override = default;

    CanvasDrawFunction GetContentDrawFunction(PaintWrapper* paintWrapper) override;

private:
    void PaintContent(
        RSCanvas& canvas, RefPtr<SwitchPaintProperty> paintProperty, SizeF contentSize, OffsetF contentOffset);

    void DrawTouchBoard(RSCanvas& canvas, const OffsetF& offset) const;
    void DrawHoverBoard(RSCanvas& canvas, const OffsetF& offset) const;
    float GetSwitchWidth(const SizeF& contentSize) const;
    float mainDelta_ = 0.0f;
    float actualWidth_ = 0.0f;
    float actualHeight_ = 0.0f;
    float pointRadius_ = 0.0f;
    const float radiusGap_ = 2.0f;
    bool enabled_ = true;
    Color clickEffectColor_ = Color::WHITE;
    Color hoverColor_ = Color::WHITE;
    Dimension hoverRadius_ = 8.0_vp;

    bool isTouch_ = false;
    bool isHover_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(SwitchPaintMethod);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWITCH_SWITCH_PAINT_METHOD_H