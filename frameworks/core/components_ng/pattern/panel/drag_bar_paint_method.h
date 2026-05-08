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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PANEL_DRAG_BAR_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PANEL_DRAG_BAR_PAINT_METHOD_H

#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components_ng/render/node_paint_method.h"

namespace OHOS::Ace::NG {

class DragBarPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(DragBarPaintMethod, NodePaintMethod);
public:
    DragBarPaintMethod() = default;
    ~DragBarPaintMethod() override = default;
    CanvasDrawFunction GetContentDrawFunction(PaintWrapper* paintWrapper) override;

    void SetIconOffset(OffsetF iconOffset)
    {
        iconOffset_ = iconOffset;
    }

    void SetScaleWidth(float scaleWidth)
    {
        scaleWidth_ = scaleWidth;
    }

    void SetPanelMode(PanelMode panelMode)
    {
        panelMode_ = panelMode;
    }

protected:
    OffsetF iconOffset_;
    float scaleWidth_ = 1.0f;

private:
    void Paint(RSCanvas& canvas, PaintWrapper* paintWrapper) const;

    PanelMode panelMode_ = PanelMode::HALF;

    ACE_DISALLOW_COPY_AND_MOVE(DragBarPaintMethod);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PANEL_DRAG_BAR_PAINT_METHOD_H
