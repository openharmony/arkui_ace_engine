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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_WRAPPER_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_WRAPPER_PAINT_METHOD_H

#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/placement.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/components_v2/list/list_component.h"

// @deprecated
namespace OHOS::Ace::NG {
struct MenuParam;
struct MenuPathParams {
    float radiusTopLeftPx = 0.0f;
    float radiusTopRightPx = 0.0f;
    float radiusBottomLeftPx = 0.0f;
    float radiusBottomRightPx = 0.0f;
    OffsetF childOffset = OffsetF();
    SizeF frameSize = SizeF();
    OffsetF arrowPosition = OffsetF();
    Placement arrowPlacement = Placement::NONE;
    bool didNeedArrow = false;
};

class ACE_EXPORT MenuWrapperPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(MenuWrapperPaintMethod, NodePaintMethod)
public:
    MenuWrapperPaintMethod() = default;
    ~MenuWrapperPaintMethod() override = default;

    CanvasDrawFunction GetOverlayDrawFunction(PaintWrapper* paintWrapper) override;

private:
    void PaintDoubleBorder(RSCanvas& canvas, PaintWrapper* paintWrapper);
    void PaintInnerBorderAndClipSinglePath(RSCanvas& canvas, PaintWrapper* paintWrapper, const MenuPathParams& path);
    void PaintOuterBorderAndClipSinglePath(RSCanvas& canvas, PaintWrapper* paintWrapper, const MenuPathParams& path);
    void BuildCompletePath(RSPath& rsPath, const MenuPathParams& params);
    void BuildTopLinePath(RSPath& rsPath, const MenuPathParams& params);
    void BuildRightLinePath(RSPath& rsPath, const MenuPathParams& params);
    void BuildBottomLinePath(RSPath& rsPath, const MenuPathParams& params);
    void BuildLeftLinePath(RSPath& rsPath, const MenuPathParams& params);
    void BuildBottomArrowPath(RSPath& rsPath, float arrowX, float arrowY);
    void BuildTopArrowPath(RSPath& rsPath, float arrowX, float arrowY);
    void BuildRightArrowPath(RSPath& rsPath, float arrowX, float arrowY);
    void BuildLeftArrowPath(RSPath& rsPath, float arrowX, float arrowY);
    void PaintEdgeOuterBorder(
        const MenuPathParams& params, RSCanvas& canvas, const MenuParam& menuParam, const RSPath& rsPath);
    ACE_DISALLOW_COPY_AND_MOVE(MenuWrapperPaintMethod);

};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_PAINT_METHOD_H