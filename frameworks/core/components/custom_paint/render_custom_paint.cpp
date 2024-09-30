/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/custom_paint/render_custom_paint.h"

namespace OHOS::Ace {

RenderCustomPaint::RenderCustomPaint() : RenderNode(true) {}

void RenderCustomPaint::PushTask(const TaskFunc& func)
{
    tasks_.emplace_back(func);
    MarkNeedRender();
}

void RenderCustomPaint::FlushPipelineImmediately()
{
    auto context = context_.Upgrade();
    if (context) {
        context->FlushPipelineImmediately();
    }
}

void RenderCustomPaint::Update(const RefPtr<Component>& component)
{
    const RefPtr<CustomPaintComponent> customPaint = AceType::DynamicCast<CustomPaintComponent>(component);
    if (!customPaint) {
        return;
    }
    width_ = customPaint->GetWidth();
    height_ = customPaint->GetHeight();
    SetTextDirection(customPaint->GetTextDirection());

    const auto& taskPool = customPaint->GetTaskPool();
    if (taskPool) {
        taskPool->SetRenderNode(AceType::WeakClaim(this));
        pool_ = taskPool;
        std::copy(taskPool->GetTasks().begin(), taskPool->GetTasks().end(), std::back_inserter(tasks_));
        taskPool->ClearTasks();
        pool_->SetPushToRenderNodeFunc([weak = AceType::WeakClaim(this)](const TaskFunc& taskFunc) {
            auto client = weak.Upgrade();
            if (client) {
                client->PushTask(taskFunc);
            }
        });

        canvasOnReadyEvent_ = taskPool->GetOnReadyEvent();
        // trigger onReady() every time build() is triggered, to support camera application.
        if (isCanvasInit_) {
            isCanvasInit_ = false;
        }
    }
    MarkNeedLayout();
}

void RenderCustomPaint::PerformLayout()
{
    drawSize_ = GetLayoutParam().GetMaxSize();
    SetLayoutSize(drawSize_);
}

void RenderCustomPaint::OnPositionChanged()
{
    isCanvasInit_ = false;
}

void RenderCustomPaint::OnSizeChanged()
{
    isCanvasInit_ = false;
}

void RenderCustomPaint::TriggerOnReadyEvent()
{
    // The first time enter the Paint(), drawSize is (0, 0)
    if (NearEqual(drawSize_.Width(), 0) || NearEqual(drawSize_.Height(), 0)) {
        return;
    }

    // OnReady() should be triggered after drawsize_ is determined in PerformLayout().
    if (!isCanvasInit_) {
        if (canvasOnReadyEvent_ && (!drawSize_.IsHeightInfinite())) {
            canvasOnReadyEvent_();
            isCanvasInit_ = true;
        }
    }
}

} // namespace OHOS::Ace
