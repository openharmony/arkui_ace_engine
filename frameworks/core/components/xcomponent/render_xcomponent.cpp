/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/components/xcomponent/render_xcomponent.h"

namespace OHOS::Ace {
void RenderXComponent::PushTask(const TaskFunction& func)
{
    tasks_.emplace_back(func);
    MarkNeedRender();
}

void RenderXComponent::Update(const RefPtr<Component>& component)
{
    const RefPtr<XComponentComponent> xcomponent = AceType::DynamicCast<XComponentComponent>(component);
    if (!xcomponent) {
        return;
    }

    textureId_ = xcomponent->GetTextureId();

    const auto& taskPool = xcomponent->GetTaskPool();
    if (taskPool) {
        taskPool->SetRenderNode(AceType::WeakClaim(this));
        pool_ = taskPool;
        tasks_ = std::list<TaskFunction>(taskPool->GetTasks().begin(), taskPool->GetTasks().end());
        taskPool->ClearTasks();
        pool_->SetPushToRenderNodeFunc([weak = AceType::WeakClaim(this)](const TaskFunction& taskFunc) {
            auto client = weak.Upgrade();
            if (client) {
                client->PushTask(taskFunc);
            }
        });
    }

    MarkNeedLayout();
}

void RenderXComponent::PerformLayout()
{
    if (!NeedLayout()) {
        return;
    }

    // render xcomponent do not support child.
    drawSize_ = Size(GetLayoutParam().GetMaxSize().Width(),
                     (GetLayoutParam().GetMaxSize().Height() == Size::INFINITE_SIZE) ?
                     Size::INFINITE_SIZE :
                     (GetLayoutParam().GetMaxSize().Height()));
    SetLayoutSize(drawSize_);
    SetNeedLayout(false);
    MarkNeedRender();
}

void RenderXComponent::Paint(RenderContext& context, const Offset& offset)
{
    position_ = GetGlobalOffset();
    if (!isXComponentInit) {
        prePosition_ = position_;
        preDrawSize_ = drawSize_;

        NativeXComponentOffset(position_.GetX(), position_.GetY());

        if (xcomponentSizeInitEvent_ && (!drawSize_.IsHeightInfinite())) {
            xcomponentSizeInitEvent_(textureId_, drawSize_.Width(), drawSize_.Height());
        }
        isXComponentInit = true;
    } else {
        if ((!NearEqual(prePosition_.GetX(), position_.GetX())) ||
            (!NearEqual(prePosition_.GetY(), position_.GetY()))) {
            prePosition_ = position_;
            positionChange_ = true;
        }

        if ((!NearEqual(preDrawSize_.Width(), drawSize_.Width())) ||
            (!NearEqual(preDrawSize_.Height(), drawSize_.Height()))) {
            preDrawSize_ = drawSize_;
            sizeChange_ = true;
        }
    }

    if (positionChange_) {
        positionChange_ = false;
        NativeXComponentOffset(position_.GetX(), position_.GetY());
    }

    if (sizeChange_) {
        sizeChange_ = false;
        if (xcomponentSizeChangeEvent_ && (!drawSize_.IsHeightInfinite())) {
            xcomponentSizeChangeEvent_(textureId_, drawSize_.Width(), drawSize_.Height());
        }
    }

    RenderNode::Paint(context, offset);
}

void RenderXComponent::NativeXComponentInit(
    OH_NativeXComponent* nativeXComponent,
    WeakPtr<NativeXComponentImpl> nativeXComponentImpl)
{
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("NativeXComponentInit pipelineContext is null");
        return;
    }
    nativeXComponent_ = nativeXComponent;
    nativeXComponentImpl_ = nativeXComponentImpl;

    pipelineContext->GetTaskExecutor()->PostTask(
        [weakNXCompImpl = nativeXComponentImpl_, nXComp = nativeXComponent_,
            w = drawSize_.Width(), h = drawSize_.Height()] {
            auto nXCompImpl = weakNXCompImpl.Upgrade();
            if (nXComp && nXCompImpl) {
                nXCompImpl->SetXComponentWidth((int)(w));
                nXCompImpl->SetXComponentHeight((int)(h));
                auto surface = const_cast<void*>(nXCompImpl->GetSurface());
                auto callback = nXCompImpl->GetCallback();
                if (callback && callback->OnSurfaceCreated != nullptr) {
                    callback->OnSurfaceCreated(nXComp, surface);
                }
            } else {
                LOGE("Native XComponent nullptr");
            }
         },
         TaskExecutor::TaskType::JS);
}

void RenderXComponent::NativeXComponentChange()
{
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("PipelineContext is null");
        return;
    }

    pipelineContext->GetTaskExecutor()->PostTask(
        [weakNXCompImpl = nativeXComponentImpl_, nXComp = nativeXComponent_,
            w = drawSize_.Width(), h = drawSize_.Height()] {
            auto nXCompImpl = weakNXCompImpl.Upgrade();
            if (nXComp && nXCompImpl) {
                nXCompImpl->SetXComponentWidth((int)(w));
                nXCompImpl->SetXComponentHeight((int)(h));
                auto surface = const_cast<void*>(nXCompImpl->GetSurface());
                auto callback = nXCompImpl->GetCallback();
                if (callback && callback->OnSurfaceChanged!= nullptr) {
                    callback->OnSurfaceChanged(nXComp, surface);
                }
            } else {
                LOGE("Native XComponent nullptr");
            }
         },
         TaskExecutor::TaskType::JS);
}

void RenderXComponent::NativeXComponentDestroy()
{
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("NativeXComponentDestroy context null");
        return;
    }

    pipelineContext->GetTaskExecutor()->PostTask(
        [weakNXCompImpl = nativeXComponentImpl_, nXComp = nativeXComponent_] {
        auto nXCompImpl = weakNXCompImpl.Upgrade();
        if (nXComp != nullptr && nXCompImpl) {
            auto surface = const_cast<void*>(nXCompImpl->GetSurface());
            auto callback = nXCompImpl->GetCallback();
            if (callback != nullptr && callback->OnSurfaceDestroyed != nullptr) {
                callback->OnSurfaceDestroyed(nXComp, surface);
            }
        } else {
            LOGE("Native XComponent nullptr");
        }
    },
    TaskExecutor::TaskType::JS);
}

void RenderXComponent::NativeXComponentDispatchTouchEvent(const OH_NativeXComponent_TouchEvent& touchEvent)
{
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("NativeXComponentDispatchTouchEvent context null");
        return;
    }
    float scale = pipelineContext->GetViewScale();
    float diffX = touchEvent.x - position_.GetX() * scale;
    float diffY = touchEvent.y - position_.GetY() * scale;
    if ((diffX >= 0) && (diffX <= drawSize_.Width() * scale) && (diffY >= 0) && (diffY <= drawSize_.Height() * scale)) {
        pipelineContext->GetTaskExecutor()->PostTask(
            [weakNXCompImpl = nativeXComponentImpl_, nXComp = nativeXComponent_, touchEvent] {
                auto nXCompImpl = weakNXCompImpl.Upgrade();
                if (nXComp != nullptr && nXCompImpl) {
                    nXCompImpl->SetTouchEvent(touchEvent);
                    auto surface = const_cast<void*>(nXCompImpl->GetSurface());
                    auto callback = nXCompImpl->GetCallback();
                    if (callback != nullptr && callback->DispatchTouchEvent != nullptr) {
                        callback->DispatchTouchEvent(nXComp, surface);
                    }
                } else {
                    LOGE("Native XComponent nullptr");
                }
            },
            TaskExecutor::TaskType::JS);
    }
}

void RenderXComponent::NativeXComponentDispatchMouseEvent(const OH_NativeXComponent_MouseEvent& mouseEvent)
{
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("NativeXComponentDispatchTouchEvent context null");
        return;
    }
    float scale = pipelineContext->GetViewScale();
    float diffX = mouseEvent.x - position_.GetX() * scale;
    float diffY = mouseEvent.y - position_.GetY() * scale;
    if ((diffX >= 0) && (diffX <= drawSize_.Width() * scale) && (diffY >= 0) && (diffY <= drawSize_.Height() * scale)) {
        pipelineContext->GetTaskExecutor()->PostTask(
            [weakNXCompImpl = nativeXComponentImpl_, nXComp = nativeXComponent_, mouseEvent] {
                auto nXCompImpl = weakNXCompImpl.Upgrade();
                if (nXComp != nullptr && nXCompImpl) {
                    nXCompImpl->SetMouseEvent(mouseEvent);
                    auto surface = const_cast<void*>(nXCompImpl->GetSurface());
                    auto callback = nXCompImpl->GetCallback();
                    if (callback != nullptr && callback->DispatchMouseEvent != nullptr) {
                        callback->DispatchMouseEvent(nXComp, surface);
                    }
                } else {
                    LOGE("Native XComponent nullptr");
                }
            },
            TaskExecutor::TaskType::JS);
    }
}

void RenderXComponent::NativeXComponentOffset(const double&x, const double& y)
{
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("NativeXComponentOffset context null");
        return;
    }
    float scale = pipelineContext->GetViewScale();
    pipelineContext->GetTaskExecutor()->PostTask(
        [weakNXCompImpl = nativeXComponentImpl_, x, y, scale] {
            auto nXCompImpl = weakNXCompImpl.Upgrade();
            if (nXCompImpl) {
                nXCompImpl->SetXComponentOffsetX(x * scale);
                nXCompImpl->SetXComponentOffsetY(y * scale);
            }
        },
        TaskExecutor::TaskType::JS);
}
} // namespace OHOS::Ace