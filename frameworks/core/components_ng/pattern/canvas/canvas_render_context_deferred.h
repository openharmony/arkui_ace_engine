/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CANVAS_RENDER_CONTEXT_DEFERRED_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CANVAS_RENDER_CONTEXT_DEFERRED_H

#include "core/components/common/properties/paint_state.h"
#include "core/components_ng/pattern/canvas/canvas_render_context.h"
#include "core/components_ng/render/drawing.h"
namespace OHOS::Ace::NG {
class ACE_EXPORT CanvasRenderContextDeferred : public virtual CanvasRenderContext {
    DECLARE_ACE_TYPE(CanvasRenderContextDeferred, CanvasRenderContext);

public:
    ~CanvasRenderContextDeferred() override = default;
    void PushTask(std::function<void(CanvasPaintMethod&)>&& task) override;
    bool NeedRender() const override;
    void FlushTask() override;
    void SetCustomNodeName(const std::string& customNodeName) override
    {
        customNodeName_ = customNodeName;
    }
    void ResetStates() override;

    TransformParam GetTransform() const override;
    LineDashParam GetLineDash() const override;
    void SaveProperties() override;
    void RestoreProperties() override;
    void ResetTransformMatrix() override;
    void ResetLineDash() override;
    void RotateMatrix(double angle) override;
    void ScaleMatrix(double x, double y) override;
    void SetTransformMatrix(const TransformParam& param) override;
    void TransformMatrix(const TransformParam& param) override;
    void TranslateMatrix(double tx, double ty) override;
    void SetLineDashParam(const std::vector<double>& segments) override;

private:
    std::string customNodeName_;
    std::list<std::function<void(CanvasPaintMethod&)>> tasks_;

    RSMatrix matrix_;
    std::vector<RSMatrix> matrixStates_;
    LineDashParam lineDash_;
    std::vector<LineDashParam> lineDashStates_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CANVAS_RENDER_CONTEXT_DEFERRED_H
