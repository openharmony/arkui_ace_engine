/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/select_content_overlay/select_content_overlay_pattern.h"

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
void SelectContentOverlayPattern::UpdateMenuIsShow(bool menuIsShow, bool noAnimation)
{
    if (info_->menuInfo.menuIsShow == menuIsShow) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(host);
    CHECK_NULL_VOID(selectOverlayNode);
    info_->menuInfo.menuIsShow = menuIsShow;
    selectOverlayNode->UpdateToolBar(false, noAnimation);
}

void SelectContentOverlayPattern::UpdateMenuInfo(const SelectMenuInfo& info)
{
    auto host = DynamicCast<SelectOverlayNode>(GetHost());
    CHECK_NULL_VOID(host);
    auto itemChanged = info_->menuInfo.IsIconChanged(info);
    info_->menuInfo = info;
    host->UpdateToolBar(itemChanged, true);
}

void SelectContentOverlayPattern::UpdateIsShowHandleLine(bool isHandleLineShow)
{
    if (info_->isHandleLineShow == isHandleLineShow) {
        return;
    }
    auto host = DynamicCast<SelectOverlayNode>(GetHost());
    CHECK_NULL_VOID(host);
    info_->isHandleLineShow = isHandleLineShow;
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SelectContentOverlayPattern::UpdateIsSingleHandle(bool isSingleHandle)
{
    if (info_->isSingleHandle == isSingleHandle) {
        return;
    }
    auto host = DynamicCast<SelectOverlayNode>(GetHost());
    CHECK_NULL_VOID(host);
    info_->isSingleHandle = isSingleHandle;
    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
}

void SelectContentOverlayPattern::RestartHiddenHandleTask(bool isDelay)
{
    CancelHiddenHandleTask();
    StartHiddenHandleTask(isDelay);
}

void SelectContentOverlayPattern::CancelHiddenHandleTask()
{
    hiddenHandleTask_.Cancel();
    isHiddenHandle_ = false;
    auto host = DynamicCast<SelectOverlayNode>(GetHost());
    CHECK_NULL_VOID(host);
    host->GetOrCreateGestureEventHub()->AddClickEvent(clickEvent_);
    host->GetOrCreateGestureEventHub()->AddPanEvent(panEvent_, { PanDirection::ALL }, 1, DEFAULT_PAN_DISTANCE);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

SelectMenuInfo SelectContentOverlayPattern::GetSelectMenuInfo()
{
    return info_->menuInfo;
}
} // namespace OHOS::Ace::NG
