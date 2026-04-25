/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/render/adapter/sidebar_content_mask_modifier.h"

#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

SidebarContentMaskModifier::SidebarContentMaskModifier(const WeakPtr<FrameNode>& maskNode)
{
    maskNode_ = maskNode;
}

void SidebarContentMaskModifier::onDraw(DrawingContext& context)
{
    auto node = maskNode_.Upgrade();
    CHECK_NULL_VOID(node);
    auto geometryNode = node->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto contentSize = geometryNode->GetFrameSize();
    frameSize_.SetWidth(contentSize.Width());
    frameSize_.SetHeight(contentSize.Height());
    PaintContentMask(context.canvas);
}

void SidebarContentMaskModifier::PaintContentMask(RSCanvas& canvas)
{
    RSBrush brush;
#ifndef USE_ROSEN_DRAWING
    RSPath path;
#else
    RSRecordingPath path;
#endif
    brush.SetAntiAlias(true);
    brush.SetColor(ToRSColor(maskColor_));
    canvas.AttachBrush(brush);
    path.SetFillStyle(RSPathFillType::EVENTODD);
    RSRect drawingRect(0, 0, frameSize_.Width(), frameSize_.Height());
    path.AddRect(drawingRect);
    canvas.DrawPath(path);
    canvas.DetachBrush();
    canvas.Restore();
}
} // namespace OHOS::Ace::NG
