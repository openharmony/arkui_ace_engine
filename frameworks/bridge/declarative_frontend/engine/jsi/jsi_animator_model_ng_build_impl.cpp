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

#include "bridge/declarative_frontend/ng/declarative_frontend_ng.h"
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
        auto frontEnd = AceType::DynamicCast<DeclarativeFrontendNG>(container->GetFrontend());
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
    auto animatorInfo = page->GetJsAnimator(animatorId);
    if (!animatorInfo) {
        animatorInfo = AceType::MakeRefPtr<AnimatorInfo>();
        auto animator = CREATE_ANIMATOR(animatorId.c_str());
        animatorInfo->SetAnimator(animator);
        page->AddJsAnimator(animatorId, animatorInfo);
    }
}

RefPtr<AnimatorInfo> AnimatorModelNG::GetAnimatorInfo(const std::string& animatorId)
{
    auto page = GetCurrentPage();
    CHECK_NULL_RETURN(page, nullptr);
    auto animatorInfo = page->GetJsAnimator(animatorId);
    return animatorInfo;
}
} // namespace OHOS::Ace::Framework
