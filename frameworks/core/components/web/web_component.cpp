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

#include "core/components/web/web_component.h"

#include "core/components/web/render_web.h"
#include "core/components/web/resource/web_delegate.h"
#include "core/components/web/web_element.h"

namespace OHOS::Ace {

WebComponent::WebComponent(const std::string& type) : type_(type)
{
    ACE_DCHECK(!type_.empty());
    if (!declaration_) {
        declaration_ = AceType::MakeRefPtr<WebDeclaration>();
        declaration_->Init();
    }
    webController_ = AceType::MakeRefPtr<WebController>();
    if (SystemProperties::GetAllowWindowOpenMethodEnabled()) {
        isAllowWindowOpenMethod_ = true;
    }
}

RefPtr<RenderNode> WebComponent::CreateRenderNode()
{
    RefPtr<RenderNode> renderNode = RenderWeb::Create();
    delegate_ = AceType::MakeRefPtr<WebDelegate>(renderNode->GetContext(),
                                                 std::move(errorCallback_), type_);
    delegate_->SetComponent(AceType::Claim(this));
    delegate_->SetPopup(isPopup_);
    delegate_->SetParentNWebId(parentNWebId_);
    if (createdCallback_ != nullptr) {
        delegate_->AddCreatedCallback(createdCallback_);
    }
    auto renderWeb = AceType::DynamicCast<RenderWeb>(renderNode);
    delegate_->AddCreatedCallback([weakRenderWeb = AceType::WeakClaim(AceType::RawPtr(renderWeb)),
        weakCom = AceType::WeakClaim(this)]() {
        auto renderWeb = weakRenderWeb.Upgrade();
        if (!renderWeb) {
            return;
        }
        auto pipelineContext = renderWeb->GetContext().Upgrade();
        if (!pipelineContext) {
            return;
        }
        auto uiTaskExecutor = SingleTaskExecutor::Make(pipelineContext->GetTaskExecutor(),
                                                       TaskExecutor::TaskType::UI);
        uiTaskExecutor.PostTask([weakRender = weakRenderWeb, weakWeb = weakCom] {
            auto renderWeb = weakRender.Upgrade();
            if (renderWeb) {
                renderWeb->Update(weakWeb.Upgrade());
            }
        }, "ArkUIWebUpdateRenderNode");
    });
    renderWeb->SetDelegate(delegate_);
    return renderNode;
}

RefPtr<Element> WebComponent::CreateElement()
{
    auto webElement = AceType::MakeRefPtr<WebElement>();
    focusElement_ = webElement;
    return webElement;
}

bool WebComponent::RequestFocus()
{
    bool result = false;
#ifndef NG_BUILD
    auto focus = focusElement_.Upgrade();
    if (focus) {
        result = focus->RequestFocusImmediately();
    }
#else
    TAG_LOGW(AceLogTag::ACE_WEB, "not support focus node in new pipeline");
#endif
    return result;
}

} // namespace OHOS::Ace
