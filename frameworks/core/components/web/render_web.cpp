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

#include "core/components/web/render_web.h"

#include <iomanip>
#include <sstream>

#include "base/log/log.h"
#include "core/event/ace_event_helper.h"

namespace OHOS::Ace {

void RenderWeb::OnAttachContext()
{
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("OnAttachContext context null");
        return;
    }
    if (delegate_) {
        // web component is displayed in full screen by default.
        drawSize_ = Size(pipelineContext->GetRootWidth(), pipelineContext->GetRootHeight());
        position_ = Offset(0, 0);
        delegate_->CreatePlatformResource(drawSize_, position_, context_);
    }
}

void RenderWeb::Update(const RefPtr<Component>& component)
{
    if (!component) {
        return;
    }
    MarkNeedLayout();
}

void RenderWeb::PerformLayout()
{
    if (!NeedLayout()) {
        LOGI("RenderWeb::PerformLayout No Need to Layout");
        return;
    }

    // render web do not support child.
    drawSize_ = Size(GetLayoutParam().GetMaxSize().Width(),
                     (GetLayoutParam().GetMaxSize().Height() == Size::INFINITE_SIZE) ?
                     Size::INFINITE_SIZE :
                     (GetLayoutParam().GetMaxSize().Height()));
    SetLayoutSize(drawSize_);
    SetNeedLayout(false);
    MarkNeedRender();
}

void RenderWeb::MarkNeedRender(bool overlay)
{
    RenderNode::MarkNeedRender(overlay);
}

} // namespace OHOS::Ace
