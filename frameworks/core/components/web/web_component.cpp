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

#include "core/components/web/web_component.h"

#include "base/geometry/offset.h"
#include "base/geometry/size.h"
#include "base/log/log.h"
#include "core/components/web/render_web.h"
#include "core/components/web/resource/web_delegate.h"
#include "core/components/web/web_element.h"

#include <iomanip>
#include <sstream>

namespace OHOS::Ace {

WebComponent::WebComponent(const std::string& type) : type_(type)
{
    ACE_DCHECK(!type_.empty());
}

RefPtr<RenderNode> WebComponent::CreateRenderNode()
{
    RefPtr<RenderNode> renderNode = RenderWeb::Create();
    delegate_ = AceType::MakeRefPtr<WebDelegate>(AceType::WeakClaim<WebComponent>(this),
                                                 renderNode->GetContext(),
                                                 std::move(errorCallback_), type_);
    if (createdCallback_ != nullptr) {
        delegate_->AddCreatedCallback(createdCallback_);
    }
    auto renderWeb = AceType::DynamicCast<RenderWeb>(renderNode);
    delegate_->AddCreatedCallback([renderWeb, this]() {
        if (!renderWeb) {
            LOGE("renderWeb is null");
            return;
        }
        auto pipelineContext = renderWeb->GetContext().Upgrade();
        if (!pipelineContext) {
            LOGE("fail to create Update due to context is null");
            return;
        }
        auto uiTaskExecutor = SingleTaskExecutor::Make(pipelineContext->GetTaskExecutor(),
                                                       TaskExecutor::TaskType::UI);
        uiTaskExecutor.PostTask([renderWeb, this] {
            if (renderWeb) {
                renderWeb->Update(AceType::Claim<Component>(this));
            }
        });
    });
    renderWeb->SetDelegate(delegate_);
    return renderNode;
}

RefPtr<Element> WebComponent::CreateElement()
{
    return AceType::MakeRefPtr<WebElement>();
}

} // namespace OHOS::Ace
