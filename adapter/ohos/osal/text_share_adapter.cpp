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

#include "core/common/share/text_share_adapter.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "core/common/share/text_share_mgr.h"

namespace OHOS::Ace {
void TextShareAdapter::StartTextShareTask(
    const int32_t containerId, const NG::RectF& contentRect, const std::string& shareText)
{
    auto currentContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(currentContext);
    auto aceContainer = Platform::AceContainer::GetContainer(containerId);
    CHECK_NULL_VOID(aceContainer);
    auto abilityContext = aceContainer->GetAbilityContext();
    Rosen::Rect anchorRect {
        .posX_ = static_cast<int32_t>(contentRect.GetX()),
        .posY_ = static_cast<int32_t>(contentRect.GetY()),
        .width_ = static_cast<uint32_t>(contentRect.Width()),
        .height_ = static_cast<uint32_t>(contentRect.Height()),
    };
    auto windowName = aceContainer->GetWindowName();
    auto uiExecutor = SingleTaskExecutor::Make(
        currentContext->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    uiExecutor.PostTask(
        [abilityContext, anchorRect, windowName, shareText] {
            (void)TextShareMgr::GetInstance().StartUpShareFunc(
                abilityContext, anchorRect, windowName, shareText);
        },
        "ArkUITextInitTextShare", PriorityType::VIP);
}

uint64_t TextShareAdapter::GetMaxTextShareLength()
{
    return TextShareMgr::GetInstance().GetMaxTextLength();
}
} // namespace OHOS::Ace