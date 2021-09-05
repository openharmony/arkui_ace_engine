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

#include "core/components/xcomponent/render_xcomponent.h"

#include <iomanip>
#include <sstream>

#include "base/log/log.h"
#include "core/event/ace_event_helper.h"

namespace OHOS::Ace {
namespace {
const char NTC_PARAM_LEFT[] = "left";
const char NTC_PARAM_TOP[] = "top";
const char NTC_PARAM_WIDTH[] = "width";
const char NTC_PARAM_HEIGHT[] = "height";
const char NTC_METHOD_LAYOUT[] = "layout";
const char PARAM_CREATE_XCOMPONENT[] = "xcomponent";
const char PARAM_METHOD_AT[] = "@";
} // namespace

void RenderXComponent::PushTask(const TaskFunction& func)
{
    tasks_.emplace_back(func);
    MarkNeedRender();
}

void RenderXComponent::Update(const RefPtr<Component>& component)
{
    if (!component) {
        return;
    }
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

void RenderXComponent::OnPaintFinish()
{
    auto xcomponent = delegate_->GetXComponent().Upgrade();
    if (std::strcmp(xcomponent->GetXComponentType().c_str(), "texture") == 0) {
        return;
    }
    position_ = GetGlobalOffset();
    CreateXComponentPlatformResource();
    UpdateXComponentLayout();
}

void RenderXComponent::CreateXComponentPlatformResource()
{
    if ((delegate_) && (!isCreatePlatformResourceSuccess_) && (!drawSize_.IsHeightInfinite())) {
        // use drawSize to create a native XCOMPONENT resource
        delegate_->CreatePlatformResource(drawSize_, position_, context_);
        isCreatePlatformResourceSuccess_ = true;
    }
}

void RenderXComponent::UpdateXComponentLayout()
{
    if (delegate_ && (delegate_->GetId() != X_INVALID_ID) &&
        isCreatePlatformResourceSuccess_ && !drawSize_.IsHeightInfinite()) {
        CallXComponentLayoutMethod();
    }
    prePosition_ = position_;
    preDrawSize_ = drawSize_;
}

void RenderXComponent::CallXComponentLayoutMethod()
{
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("CallXComponentLayoutMethod context null");
        return;
    }

    // when left and top remain unchanged, the xcomponent layout will not update.
    if (NearEqual(prePosition_.GetX(), position_.GetX()) && NearEqual(prePosition_.GetY(), position_.GetY())) {
        return;
    }

    std::stringstream paramStream;
    paramStream << NTC_PARAM_LEFT
                << XCOMPONENT_PARAM_EQUALS
                << position_.GetX() * pipelineContext->GetViewScale()
                << XCOMPONENT_PARAM_AND
                << NTC_PARAM_TOP
                << XCOMPONENT_PARAM_EQUALS
                << position_.GetY() * pipelineContext->GetViewScale()
                << XCOMPONENT_PARAM_AND
                << NTC_PARAM_WIDTH
                << XCOMPONENT_PARAM_EQUALS
                << drawSize_.Width() * pipelineContext->GetViewScale()
                << XCOMPONENT_PARAM_AND
                << NTC_PARAM_HEIGHT
                << XCOMPONENT_PARAM_EQUALS
                << drawSize_.Height() * pipelineContext->GetViewScale();
    std::string param = paramStream.str();
    if (delegate_) {
        delegate_->CallResRegisterMethod(MakeMethodHash(NTC_METHOD_LAYOUT), param, nullptr);
    }
}

std::string RenderXComponent::MakeMethodHash(const std::string& method) const
{
    std::stringstream hashCode;
    hashCode << PARAM_CREATE_XCOMPONENT << PARAM_METHOD_AT << delegate_->GetId();
    std::string methodHash = hashCode.str();
    methodHash += std::string(XCOMPONENT_METHOD);
    methodHash += std::string(XCOMPONENT_PARAM_EQUALS);
    methodHash += method;
    methodHash += std::string(XCOMPONENT_PARAM_BEGIN);
    return methodHash;
}
} // namespace OHOS::Ace
