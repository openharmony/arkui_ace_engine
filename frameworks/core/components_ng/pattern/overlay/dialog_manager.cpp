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

RefPtr<OverlayManager> DialogManager::GetEmbeddedOverlay(int32_t uniqueId, const RefPtr<PipelineContext>& context)
{
    CHECK_NULL_RETURN(context, nullptr);
    if (uniqueId >= 0) {
        auto currentNode = ElementRegister::GetInstance()->GetSpecificItemById<NG::FrameNode>(uniqueId);
        if (currentNode == nullptr || !currentNode->IsOnMainTree()) {
            TAG_LOGE(AceLogTag::ACE_DIALOG, "Level uniqueId/%{public}d does not exist or not on main tree.", uniqueId);
        } else {
            auto getOverlayManager = SheetManager::FindPageNodeOverlay(currentNode, true, true);
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

} // namespace OHOS::Ace::NG
