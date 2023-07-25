/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components/side_bar/rosen_render_side_bar_container.h"

#ifndef USE_ROSEN_DRAWING
#include "include/core/SkPath.h"
#else
#include "core/components_ng/render/drawing.h"
#endif
#include "render_service_client/core/ui/rs_node.h"

#include "core/pipeline/base/rosen_render_context.h"

namespace OHOS::Ace {
void RosenRenderSideBarContainer::Paint(RenderContext& context, const Offset& offset)
{
    auto rsNode = static_cast<RosenRenderContext*>(&context)->GetRSNode();
    if (rsNode == nullptr) {
        LOGE("rsNode is null.");
        return;
    }

    rsNode->SetClipToBounds(true);
    auto paintRect = GetPaintRect();
#ifndef USE_ROSEN_DRAWING
    SkPath skPath;
    skPath.addRect(SkRect::MakeXYWH(paintRect.Left(), paintRect.Top(), paintRect.Width(), paintRect.Height()));
    rsNode->SetClipBounds(Rosen::RSPath::CreateRSPath(skPath));
#else
    RSRecordingPath dPath;
    dPath.AddRect(RSRect(paintRect.Left(), paintRect.Top(), paintRect.Right(), paintRect.Bottom()));
    rsNode->SetClipBounds(Rosen::RSPath::CreateRSPath(dPath));
#endif

    RenderNode::Paint(context, offset);
}
} // namespace OHOS::Ace