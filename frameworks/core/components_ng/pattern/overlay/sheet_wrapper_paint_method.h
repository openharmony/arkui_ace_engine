/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_OVERLAY_SHEET_WRAPPER_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_OVERLAY_SHEET_WRAPPER_PAINT_METHOD_H

#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/render/node_paint_method.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT SheetWrapperPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(SheetWrapperPaintMethod, NodePaintMethod)
public:
    SheetWrapperPaintMethod() {}
    ~SheetWrapperPaintMethod() override = default;

    CanvasDrawFunction GetOverlayDrawFunction(PaintWrapper* paintWrapper) override
    {
        return [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
            auto sheet = weak.Upgrade();
            if (sheet) {
                sheet->PaintInnerBorder(canvas, paintWrapper);
                sheet->PaintOuterBorder(canvas, paintWrapper);
            }
        };
    }

    void PaintOuterBorder(RSCanvas& canvas, PaintWrapper* paintWrapper);
    void PaintInnerBorder(RSCanvas& canvas, PaintWrapper* paintWrapper);

private:
    RefPtr<FrameNode> GetSheetNode(PaintWrapper* paintWrapper);
    void SetBorderPenStyle(RSPen& pen, const Dimension& borderWidth, const Color& borderColor);
    void GetBorderDrawPath(RSPath& path, const RefPtr<FrameNode> sheetNode, const RefPtr<SheetTheme>& sheetTheme,
        float borderWidth, const BorderRadiusProperty& sheetRadius);
    bool IsDrawBorder(PaintWrapper* paintWrapper);

    ACE_DISALLOW_COPY_AND_MOVE(SheetWrapperPaintMethod);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_OVERLAY_SHEET_WRAPPER_PAINT_METHOD_H
