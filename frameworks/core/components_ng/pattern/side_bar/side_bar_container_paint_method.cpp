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

#include "core/components_ng/pattern/side_bar/side_bar_container_paint_method.h"

namespace OHOS::Ace::NG {
CanvasDrawFunction SideBarContainerPaintMethod::GetContentDrawFunction(PaintWrapper* paintWrapper)
{
    auto paintFunc = [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
        auto painter = weak.Upgrade();
        CHECK_NULL_VOID(painter);
        painter->ClipPadding(paintWrapper, canvas);
    };
    return paintFunc;
}

void SideBarContainerPaintMethod::ClipPadding(PaintWrapper* paintWrapper, RSCanvas& canvas) const
{
    if (!needClipPadding_) {
        return;
    }
    const auto& geometryNode = paintWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameSize = geometryNode->GetPaddingSize();
    OffsetF paddingOffset = geometryNode->GetPaddingOffset() - geometryNode->GetFrameOffset();
    auto renderContext = paintWrapper->GetRenderContext();
    if (!renderContext || renderContext->GetClipEdge().value_or(true)) {
        auto clipRect = RSRect(paddingOffset.GetX(), paddingOffset.GetY(), frameSize.Width() + paddingOffset.GetX(),
                    paddingOffset.GetY() + frameSize.Height());
        canvas.ClipRect(clipRect, RSClipOp::INTERSECT);
    }
}
} // namespace OHOS::Ace::NG
