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

#include "core/components_ng/pattern/canvas/canvas_render_context_deferred.h"

namespace OHOS::Ace::NG {
void CanvasRenderContextDeferred::PushTask(std::function<void(CanvasPaintMethod&)>&& task)
{
    static constexpr uint32_t suggestSize = 100000;
    tasks_.emplace_back(task);
    if (tasks_.size() >= suggestSize && tasks_.size() % suggestSize == 0) {
        TAG_LOGI(AceLogTag::ACE_CANVAS, "[%{public}s] Canvas task size: %{public}zu", customNodeName_.c_str(),
            tasks_.size());
    }
}

bool CanvasRenderContextDeferred::NeedRender() const
{
    return !tasks_.empty();
}

void CanvasRenderContextDeferred::FlushTask()
{
    CHECK_NULL_VOID(paintMethod_);
    ACE_SCOPED_TRACE("Canvas tasks count: %zu.", tasks_.size());
    for (auto& task : tasks_) {
        task(*paintMethod_);
    }
    tasks_.clear();
}

void CanvasRenderContextDeferred::ResetStates()
{
    std::vector<RSMatrix>().swap(matrixStates_);
    std::vector<LineDashParam>().swap(lineDashStates_);
}

TransformParam CanvasRenderContextDeferred::GetTransform() const
{
    TransformParam param;
    param.scaleX = matrix_.Get(static_cast<int>(RSMatrix::Index::SCALE_X));
    param.scaleY = matrix_.Get(static_cast<int>(RSMatrix::Index::SCALE_Y));
    param.skewX = matrix_.Get(static_cast<int>(RSMatrix::Index::SKEW_X));
    param.skewY = matrix_.Get(static_cast<int>(RSMatrix::Index::SKEW_Y));
    param.translateX = matrix_.Get(static_cast<int>(RSMatrix::Index::TRANS_X));
    param.translateY = matrix_.Get(static_cast<int>(RSMatrix::Index::TRANS_Y));
    return param;
}

void CanvasRenderContextDeferred::SaveProperties()
{
    matrixStates_.push_back(matrix_);
    lineDashStates_.push_back(lineDash_);
}

void CanvasRenderContextDeferred::RestoreProperties()
{
    if (!matrixStates_.empty()) {
        matrix_ = matrixStates_.back();
        matrixStates_.pop_back();
    }
    if (!lineDashStates_.empty()) {
        lineDash_ = lineDashStates_.back();
        lineDashStates_.pop_back();
    }
}

void CanvasRenderContextDeferred::ResetTransformMatrix()
{
    matrix_.Reset();
}

void CanvasRenderContextDeferred::ResetLineDash()
{
    std::vector<double>().swap(lineDash_.lineDash);
    lineDash_.dashOffset = 0.0;
}

void CanvasRenderContextDeferred::RotateMatrix(double angle)
{
    RSMatrix matrix;
    matrix.Rotate(angle * 180.0 / ACE_PI, 0, 0); // 180.0 means half of a full 360° circle
    matrix_.PreConcat(matrix);
}

void CanvasRenderContextDeferred::ScaleMatrix(double sx, double sy)
{
    RSMatrix matrix;
    matrix.SetScale(sx, sy);
    matrix_.PreConcat(matrix);
}

void CanvasRenderContextDeferred::SetTransformMatrix(const TransformParam& param)
{
    matrix_.SetMatrix(
        param.scaleX, param.skewX, param.translateX, param.skewY, param.scaleY, param.translateY, 0, 0, 1);
}

void CanvasRenderContextDeferred::TransformMatrix(const TransformParam& param)
{
    RSMatrix matrix;
    matrix.SetMatrix(param.scaleX, param.skewY, param.translateX, param.skewX, param.scaleY, param.translateY, 0, 0, 1);
    matrix_.PreConcat(matrix);
}

void CanvasRenderContextDeferred::TranslateMatrix(double tx, double ty)
{
    if (tx || ty) {
        matrix_.PreTranslate(tx, ty);
    }
}

void CanvasRenderContextDeferred::SetLineDashParam(const std::vector<double>& segments)
{
    lineDash_.lineDash = segments;
}

LineDashParam CanvasRenderContextDeferred::GetLineDash() const
{
    return lineDash_;
}
} // namespace OHOS::Ace::NG
