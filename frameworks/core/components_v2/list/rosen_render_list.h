/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_LIST_ROSEN_RENDER_LIST_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_LIST_ROSEN_RENDER_LIST_H

#ifndef USE_ROSEN_DRAWING
#include "include/core/SkPaint.h"
#endif

#include "base/utils/noncopyable.h"
#include "core/components_v2/list/render_list.h"
#ifdef USE_ROSEN_DRAWING
#include "core/components_ng/render/drawing_forward.h"
#endif

namespace OHOS::Ace::V2 {

class RosenRenderList : public RenderList {
    DECLARE_ACE_TYPE(V2::RosenRenderList, RenderList);

public:
    RosenRenderList() = default;
    ~RosenRenderList() override = default;

    void Update(const RefPtr<Component>& component) override;
    void Paint(RenderContext& context, const Offset& offset) override;

private:
    void PaintSelectedZone(RenderContext& context);
    void PaintItemZone(RenderContext& context, const RefPtr<RenderListItem>& item);
    void PaintDivider(const std::shared_ptr<RSNode>& rsNode);
#ifndef USE_ROSEN_DRAWING
    void DrawDividerOnNode(const std::shared_ptr<RSNode>& rsNode, const SkPaint& paint, bool isVertical,
        double startCrossAxis, double mainAxis, double endCrossAxis);
#else
    void DrawDividerOnNode(const std::shared_ptr<RSNode>& rsNode, const RSPen& pen, bool isVertical,
        double startCrossAxis, double mainAxis, double endCrossAxis);
#endif
    RefPtr<RenderListItem> prevStickyItem_;
    ACE_DISALLOW_COPY_AND_MOVE(RosenRenderList);
};

} // namespace OHOS::Ace::V2

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_LIST_ROSEN_RENDER_LIST_H
