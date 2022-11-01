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

class RadioPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(RadioPaintMethod, NodePaintMethod)

public:
    RadioPaintMethod(bool enabled) : enabled_(enabled) {};
    ~RadioPaintMethod() override = default;

    CanvasDrawFunction GetContentDrawFunction(PaintWrapper* paintWrapper) override;

private:
    void InitializeParam();
    void PaintRadio(RSCanvas& canvas, bool checked, const SizeF& contentSize, const OffsetF& offset) const;
    void DrawUnselected(RSCanvas& canvas, const OffsetF& origin, RSPen& pen, SizeF& paintSize) const;

    float shadowWidth_ = 1.5f;
    float borderWidth_ = 1.5f;
    Color activeColor_ = Color::BLUE;
    Color inactiveColor_ = Color::WHITE;
    Color shadowColor_ = Color::RED;

    bool enabled_ = true;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_RADIO_RADIO_PAINT_METHOD_H
