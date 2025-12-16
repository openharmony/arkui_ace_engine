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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CANVAS_RENDER_CONTEXT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CANVAS_RENDER_CONTEXT_H

#include "ui/base/ace_type.h"
#include "ui/base/referenced.h"

#include "core/components/common/properties/paint_state.h"

namespace OHOS::Ace::NG {
class CanvasPaintMethod;
class ACE_EXPORT CanvasRenderContext : public virtual AceType {
    DECLARE_ACE_TYPE(CanvasRenderContext, AceType);

public:
    CanvasRenderContext() = default;
    ~CanvasRenderContext() override = default;

    virtual void PushTask(std::function<void(CanvasPaintMethod&)>&& task) = 0;
    virtual bool NeedRender() const = 0;
    virtual void FlushTask() = 0;

    virtual void SetCustomNodeName(const std::string& customNodeName) {}

    virtual TransformParam GetTransform() const = 0;
    virtual LineDashParam GetLineDash() const = 0;
    virtual void SaveProperties() {}
    virtual void RestoreProperties() {}
    virtual void ResetTransformMatrix() {}
    virtual void ResetLineDash() {}
    virtual void RotateMatrix(double angle) {}
    virtual void ScaleMatrix(double x, double y) {}
    virtual void SetTransformMatrix(const TransformParam& param) {}
    virtual void TransformMatrix(const TransformParam& param) {}
    virtual void TranslateMatrix(double tx, double ty) {}
    virtual void SetLineDashParam(const std::vector<double>& segments) {}
    virtual void ResetStates() {}

    void SetPaintMethod(CanvasPaintMethod* paintMethod)
    {
        paintMethod_ = paintMethod;
    }

protected:
    CanvasPaintMethod* paintMethod_ = nullptr;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CANVAS_RENDER_CONTEXT_H
