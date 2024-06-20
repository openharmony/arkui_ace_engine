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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_PAINT_WRAPPER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_PAINT_WRAPPER_H

#include <functional>
#include <memory>

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/thread/cancelable_callback.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/render/paint_property.h"
#include "core/components_ng/render/render_context.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
class NodePaintMethod;

// PaintWrapper are used to flush dirty render task.
class PaintWrapper : public virtual AceType {
    DECLARE_ACE_TYPE(PaintWrapper, AceType)

public:
    PaintWrapper(WeakPtr<RenderContext> renderContext, RefPtr<GeometryNode> geometryNode,
        RefPtr<PaintProperty> layoutProperty, RefPtr<ExtensionHandler> handler = nullptr);
    ~PaintWrapper() override;

    void SetNodePaintMethod(const RefPtr<NodePaintMethod>& nodePaintImpl);

    void SetTaskThread(TaskThread taskThread)
    {
        taskThread_ = taskThread;
    }

    void FlushRender();

    TaskThread CanRunOnWhichThread() const
    {
        return taskThread_;
    }

    bool CheckShouldRunOnMain() const
    {
        return (CanRunOnWhichThread() & MAIN_TASK) == MAIN_TASK;
    }

    const RefPtr<PaintProperty>& GetPaintProperty() const
    {
        return paintProperty_;
    }

    const RefPtr<GeometryNode>& GetGeometryNode() const
    {
        return geometryNode_;
    }

    RefPtr<RenderContext> GetRenderContext() const
    {
        return renderContext_.Upgrade();
    }

    SizeF GetContentSize() const
    {
        return geometryNode_->GetContentSize();
    }

    OffsetF GetContentOffset() const
    {
        return geometryNode_->GetContentOffset();
    }

    bool HasForegroundColor() const
    {
        auto renderContext = renderContext_.Upgrade();
        return renderContext->HasForegroundColor();
    }

    bool HasForegroundColorStrategy() const
    {
        auto renderContext = renderContext_.Upgrade();
        return renderContext->HasForegroundColorStrategy();
    }

    Color GetForegroundColor() const
    {
        auto renderContext = renderContext_.Upgrade();
        return renderContext->GetForegroundColor().value_or(Color::FOREGROUND);
    }

    void FlushOverlayModifier();

    void FlushContentModifier();

    void FlushForegroundModifier();

private:
    WeakPtr<RenderContext> renderContext_;
    RefPtr<GeometryNode> geometryNode_;
    RefPtr<PaintProperty> paintProperty_;
    RefPtr<NodePaintMethod> nodePaintImpl_;
    RefPtr<ExtensionHandler> extensionHandler_;
    TaskThread taskThread_ = MAIN_TASK;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_PAINT_WRAPPER_H
