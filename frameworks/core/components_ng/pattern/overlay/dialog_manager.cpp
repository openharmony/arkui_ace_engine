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


#include "base/error/error_code.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/overlay/dialog_manager.h"
#include "core/components_ng/pattern/overlay/sheet_manager.h"
#include "core/components_ng/pattern/stage/page_pattern.h"

namespace OHOS::Ace::NG {
namespace {
} // namespace

DialogManager::DialogManager() = default;

DialogManager::~DialogManager() = default;

void DialogManager::ShowInEmbeddedOverlay(std::function<void(RefPtr<NG::OverlayManager>)>&& task,
    const std::string& name, int32_t uniqueId)
{
    auto currentId = Container::CurrentId();
    ContainerScope scope(currentId);
    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    auto embeddedOverlay = GetEmbeddedOverlay(uniqueId, context);
    if (embeddedOverlay) {
        overlayManager = embeddedOverlay;
    }
    context->GetTaskExecutor()->PostTask(
        [task = std::move(task), weak = WeakPtr<NG::OverlayManager>(overlayManager)] {
            auto overlayManager = weak.Upgrade();
            task(overlayManager);
        },
        TaskExecutor::TaskType::UI, name);
}

RefPtr<OverlayManager> DialogManager::FindPageNodeOverlay(const RefPtr<FrameNode>& currentNode)
{
    if (currentNode == nullptr || !currentNode->IsOnMainTree()) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "dialog node does not exist or not on main tree.");
    } else {
        return SheetManager::FindPageNodeOverlay(currentNode, true, true);
    }
    return nullptr;
}

RefPtr<OverlayManager> DialogManager::GetEmbeddedOverlay(int32_t uniqueId, const RefPtr<PipelineContext>& context)
{
    CHECK_NULL_RETURN(context, nullptr);
    if (uniqueId >= 0) {
        auto currentNode = ElementRegister::GetInstance()->GetSpecificItemById<NG::FrameNode>(uniqueId);
        if (currentNode == nullptr || !currentNode->IsOnMainTree()) {
            TAG_LOGE(AceLogTag::ACE_DIALOG, "Level uniqueId/%{public}d does not exist or not on main tree.", uniqueId);
        } else {
            auto getOverlayManager = FindPageNodeOverlay(currentNode);
            if (getOverlayManager) {
                return getOverlayManager;
            } else {
                TAG_LOGE(AceLogTag::ACE_DIALOG, "Level uniqueId/%{public}d can not get overlay manager.", uniqueId);
            }
        }
    } else {
        auto stateMgr = context->GetStageManager();
        if (stateMgr && stateMgr->GetLastPage()) {
            auto pagePattern = stateMgr->GetLastPage()->GetPattern<NG::PagePattern>();
            if (pagePattern) {
                pagePattern->CreateOverlayManager(true);
                return pagePattern->GetOverlayManager();
            }
        } else {
            TAG_LOGE(AceLogTag::ACE_DIALOG, "Can not get current page");
        }
    }
    return nullptr;
}

RefPtr<OverlayManager> DialogManager::GetEmbeddedOverlayWithNode(const RefPtr<UINode>& dialogNode)
{
    CHECK_NULL_RETURN(dialogNode, nullptr);
    auto parent = dialogNode->GetParent();
    CHECK_NULL_RETURN(parent, nullptr);
    auto parentNode = AceType::DynamicCast<FrameNode>(parent);
    CHECK_NULL_RETURN(parentNode, nullptr);
    if (parentNode->GetTag() == V2::PAGE_ETS_TAG) {
        auto pattern = parentNode->GetPattern<PagePattern>();
        CHECK_NULL_RETURN(pattern, nullptr);
        return pattern->GetOverlayManager();
    } else if (parentNode->GetTag() == V2::NAVDESTINATION_VIEW_ETS_TAG) {
        auto pattern = parentNode->GetPattern<NavDestinationPattern>();
        CHECK_NULL_RETURN(pattern, nullptr);
        return pattern->GetOverlayManager();
    }
    return nullptr;
}

RefPtr<UINode> DialogManager::GetDialogNodeByContentNode(const RefPtr<UINode>& currentNode)
{
    RefPtr<UINode> parent = currentNode;
    bool getDialogNode = false;
    while (parent) {
        if (parent->GetTag() == V2::DIALOG_ETS_TAG) {
            getDialogNode = true;
            break;
        }
        parent = parent->GetParent();
    }
    if (getDialogNode) {
        return parent;
    }
    return nullptr;
}
} // namespace OHOS::Ace::NG
