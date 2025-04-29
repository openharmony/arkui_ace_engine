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

#include "core/components_ng/pattern/animator/animator_model_ng.h"

#ifdef NG_BUILD
#include "bridge/declarative_frontend/ng/declarative_frontend_ng.h"
#else
#include "bridge/declarative_frontend/declarative_frontend.h"
#endif
#include "core/components_ng/pattern/stage/page_pattern.h"
#ifdef PLUGIN_COMPONENT_SUPPORTED
#include "core/common/plugin_manager.h"
#endif

namespace OHOS::Ace::Framework {
namespace {
RefPtr<NG::PagePattern> GetCurrentPage()
{
    RefPtr<NG::FrameNode> pageNode;
#ifdef PLUGIN_COMPONENT_SUPPORTED
    if (Container::CurrentId() >= MIN_PLUGIN_SUBCONTAINER_ID) {
        auto pluginContainer = PluginManager::GetInstance().GetPluginSubContainer(Container::CurrentId());
        CHECK_NULL_RETURN(pluginContainer, nullptr);
        pageNode = pluginContainer->GetPluginNode().Upgrade();
        CHECK_NULL_RETURN(pageNode, nullptr);
    } else
#endif
    {
        auto container = Container::Current();
        CHECK_NULL_RETURN(container, nullptr);
#ifdef NG_BUILD
        auto frontEnd = AceType::DynamicCast<DeclarativeFrontendNG>(container->GetFrontend());
#else
        auto frontEnd = AceType::DynamicCast<DeclarativeFrontend>(container->GetFrontend());
#endif
        CHECK_NULL_RETURN(frontEnd, nullptr);
        auto pageRouterManager = frontEnd->GetPageRouterManager();
        CHECK_NULL_RETURN(pageRouterManager, nullptr);
        pageNode = pageRouterManager->GetCurrentPageNode();
        CHECK_NULL_RETURN(pageNode, nullptr);
    }
    return pageNode->GetPattern<NG::PagePattern>();
}
} // namespace

void AnimatorModelNG::Create(const std::string& animatorId)
{
    auto page = GetCurrentPage();
    CHECK_NULL_VOID(page);
    auto pageNode = page->GetHost();
    CHECK_NULL_VOID(pageNode);
    auto animatorInfo = page->GetJsAnimator(animatorId);
    if (!animatorInfo) {
        animatorInfo = AceType::MakeRefPtr<AnimatorInfo>();
        TAG_LOGI(AceLogTag::ACE_ANIMATION,
            "create animator component, id:%{public}s, pageUrl:%{public}s, pageId:%{public}d", animatorId.c_str(),
            page->GetPageUrl().c_str(), pageNode->GetId());
        auto animator = CREATE_ANIMATOR(animatorId.c_str());
        animatorInfo->SetAnimator(animator);
        page->AddJsAnimator(animatorId, animatorInfo);
    }
}

RefPtr<AnimatorInfo> AnimatorModelNG::GetAnimatorInfo(const std::string& animatorId)
{
    auto page = GetCurrentPage();
    if (!page) {
        TAG_LOGW(AceLogTag::ACE_ANIMATION, "look for animator component, but current page is null, id:%{public}s",
            animatorId.c_str());
        return nullptr;
    }
    auto pageNode = page->GetHost();
    CHECK_NULL_RETURN(pageNode, nullptr);
    auto animatorInfo = page->GetJsAnimator(animatorId);
    if (!animatorInfo) {
        TAG_LOGW(AceLogTag::ACE_ANIMATION,
            "cannot find animator component in current page, id:%{public}s, pageUrl:%{public}s, pageId:%{public}d",
            animatorId.c_str(), page->GetPageUrl().c_str(), pageNode->GetId());
    }
    return animatorInfo;
}
} // namespace OHOS::Ace::Framework
