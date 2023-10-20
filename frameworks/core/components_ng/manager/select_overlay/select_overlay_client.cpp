/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/manager/select_overlay/select_overlay_client.h"

#include <cstdint>

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void SelectOverlayClient::InitSelectOverlay()
{
    selectOverlayInfo_.menuCallback.onCopy = [weak = WeakClaim(this)]() {
        auto client = weak.Upgrade();
        CHECK_NULL_VOID(client);
        client->OnSelectOverlayMenuClicked(SelectOverlayMenuId::COPY);
    };
    selectOverlayInfo_.menuCallback.onCut = [weak = WeakClaim(this)]() {
        auto client = weak.Upgrade();
        CHECK_NULL_VOID(client);
        client->OnSelectOverlayMenuClicked(SelectOverlayMenuId::CUT);
    };
    selectOverlayInfo_.menuCallback.onSelectAll = [weak = WeakClaim(this)]() {
        auto client = weak.Upgrade();
        CHECK_NULL_VOID(client);
        client->OnSelectOverlayMenuClicked(SelectOverlayMenuId::SELECT_ALL);
    };
    selectOverlayInfo_.menuCallback.onPaste = [weak = WeakClaim(this)]() {
        auto client = weak.Upgrade();
        CHECK_NULL_VOID(client);
        client->OnSelectOverlayMenuClicked(SelectOverlayMenuId::PASTE);
    };
    selectOverlayInfo_.onHandleMoveStart = [weak = WeakClaim(this)](bool isFirst) {
        auto client = weak.Upgrade();
        CHECK_NULL_VOID(client);
        client->OnHandleMoveStart(isFirst);
    };
    selectOverlayInfo_.onHandleMove = [weak = WeakClaim(this)](const RectF& rect, bool isFirst) {
        auto client = weak.Upgrade();
        CHECK_NULL_VOID(client);
        client->OnHandleMove(rect, isFirst);
    };
    selectOverlayInfo_.onHandleMoveDone = [weak = WeakClaim(this)](const RectF& rect, bool isFirst) {
        auto client = weak.Upgrade();
        CHECK_NULL_VOID(client);
        client->OnHandleMoveDone(rect, isFirst);
    };
    selectOverlayInfo_.onClose = [weak = WeakClaim(this)](bool closedByGlobalEvent) {
        auto client = weak.Upgrade();
        CHECK_NULL_VOID(client);
        client->OnHandleClosed(closedByGlobalEvent);
    };
    selectOverlayInfo_.callerFrameNode = GetClientHost();
    selectOverlayInfo_.firstHandle.isShow = false;
    selectOverlayInfo_.secondHandle.isShow = false;
}

void SelectOverlayClient::RequestOpenSelectOverlay(const ClientOverlayInfo& showOverlayInfo)
{
    LOGI("RequestOpenSelectOverlay start, has first handle %{public}d, has second handle %{public}d",
        showOverlayInfo.firstHandleInfo.has_value(), showOverlayInfo.secondHandleInfo.has_value());
    if (SelectOverlayIsOn()) {
        UpdateShowingSelectOverlay(showOverlayInfo);
    } else {
        CreateSelectOverlay(showOverlayInfo);
    }
}

void SelectOverlayClient::CreateSelectOverlay(const ClientOverlayInfo& clientOverlayInfo)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto overlayInfo = GetSelectOverlayInfo(clientOverlayInfo);
    CHECK_NULL_VOID(overlayInfo);
    LOGD("first handle visibility %{public}d, second handle visibility %{public}d, select rect visibility "
            "%{public}d",
        overlayInfo.firstHandle.isShow, overlayInfo.secondHandle.isShow, overlayInfo.isSelectRegionVisible);
    selectOverlayProxy_ = pipeline->GetSelectOverlayManager()->CreateAndShowSelectOverlay(
        *overlayInfo, WeakClaim(this), clientOverlayInfo.animation);
    StartListeningScrollableParent(GetClientHost());
}

std::optional<SelectOverlayInfo> SelectOverlayClient::GetSelectOverlayInfo(const ClientOverlayInfo& clientInfo)
{
    auto firstHandleInfo = clientInfo.firstHandleInfo;
    auto secondHandleInfo = clientInfo.secondHandleInfo;
    if (firstHandleInfo.has_value()) {
        firstHandleInfo->isShow = CheckHandleVisible(firstHandleInfo->paintRect);
    }
    if (secondHandleInfo.has_value()) {
        secondHandleInfo->isShow = CheckHandleVisible(secondHandleInfo->paintRect);
    }
    SelectOverlayInfo overlayInfo = selectOverlayInfo_;
    overlayInfo.firstHandle = firstHandleInfo.has_value() ? *firstHandleInfo : overlayInfo.firstHandle;
    overlayInfo.secondHandle = secondHandleInfo.has_value() ? *secondHandleInfo : overlayInfo.secondHandle;
    overlayInfo.isSingleHandle = !firstHandleInfo && secondHandleInfo;
    overlayInfo.isSelectRegionVisible = CheckSelectionRectVisible();
    if (!GetMenuOptionItems().empty()) {
        overlayInfo.menuOptionItems = GetMenuOptionItems();
    }
    if (OnPreShowSelectOverlay(overlayInfo, clientInfo, SelectOverlayIsOn())) {
        return overlayInfo;
    }
    return std::nullopt;
}

void SelectOverlayClient::UpdateShowingSelectOverlay(const ClientOverlayInfo& clientInfo)
{
    auto isCurrentSingleHandle = IsShowingSingleHandle();
    auto hasRequestSingleHandle = !clientInfo.firstHandleInfo && clientInfo.secondHandleInfo;
    if (clientInfo.isShowMouseMenu || isCurrentSingleHandle ^ hasRequestSingleHandle) {
        RequestCloseSelectOverlay(true);
        CreateSelectOverlay(clientInfo);
        return;
    }
    auto selectOverlayInfo = GetSelectOverlayInfo(clientInfo);
    CHECK_NULL_VOID(selectOverlayInfo);
    auto proxy = GetSelectOverlayProxy();
    CHECK_NULL_VOID(proxy);
    if (hasRequestSingleHandle) {
        proxy->UpdateSelectMenuInfo([newMenuInfo = selectOverlayInfo->menuInfo](SelectMenuInfo& menuInfo) {
            menuInfo.showPaste = newMenuInfo.showPaste;
            menuInfo.showCopyAll = newMenuInfo.showCopyAll;
        });
        proxy->UpdateSecondSelectHandleInfo(selectOverlayInfo->secondHandle);
    } else {
        proxy->UpdateSelectMenuInfo([newMenuInfo = selectOverlayInfo->menuInfo](SelectMenuInfo& menuInfo) {
            menuInfo.showPaste = newMenuInfo.showPaste;
            menuInfo.showCopyAll = newMenuInfo.showCopyAll;
            menuInfo.showCopy = newMenuInfo.showCopy;
            menuInfo.showCut = newMenuInfo.showCut;
        });
        proxy->UpdateFirstAndSecondHandleInfo(selectOverlayInfo->firstHandle, selectOverlayInfo->secondHandle);
    }
}

void SelectOverlayClient::RequestCloseSelectOverlay(bool animation)
{
    StopListeningScrollableParent(GetClientHost());
    if (selectOverlayProxy_ && !selectOverlayProxy_->IsClosed()) {
        selectOverlayProxy_->Close(animation);
    }
}

bool SelectOverlayClient::SelectOverlayIsOn()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    CHECK_NULL_RETURN(selectOverlayProxy_, false);
    auto overlayId = selectOverlayProxy_->GetSelectOverlayId();
    return pipeline->GetSelectOverlayManager()->HasSelectOverlay(overlayId);
}

void SelectOverlayClient::UpdateSelectInfo(const std::string& selectInfo)
{
    auto selectOverlay = GetSelectOverlayProxy();
    CHECK_NULL_VOID(selectOverlay);
    selectOverlay->SetSelectInfo(selectInfo);
}

void SelectOverlayClient::UpdateSelectMenuInfo(std::function<void(SelectMenuInfo&)> updateAction)
{
    auto selectOverlay = GetSelectOverlayProxy();
    CHECK_NULL_VOID(selectOverlay);
    selectOverlay->UpdateSelectMenuInfo(updateAction);
}

void SelectOverlayClient::UpdateSelectMenuVisibility(bool isVisible)
{
    auto selectOverlay = GetSelectOverlayProxy();
    CHECK_NULL_VOID(selectOverlay);
    selectOverlay->ShowOrHiddenMenu(!isVisible);
}

void SelectOverlayClient::StartListeningScrollableParent(const RefPtr<FrameNode>& host)
{
    if (!scrollableParentInfo_.hasParent) {
        LOGI("has no scrollable parent");
        return;
    }
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto registerScrollCallback = [&](int32_t parentId, int32_t callbackId) {
        if (!scrollCallback_) {
            scrollCallback_ = [weak = WeakClaim(this)](bool isEnd) {
                auto client = weak.Upgrade();
                CHECK_NULL_VOID(client);
                client->OnParentScrollCallback(isEnd);
            };
        }
        context->GetSelectOverlayManager()->RegisterScrollCallback(parentId, callbackId, std::move(scrollCallback_));
    };
    if (scrollableParentInfo_.parentIds.empty()) {
        auto parent = host->GetParent();
        while (parent && parent->GetTag() != V2::PAGE_ETS_TAG) {
            auto parentNode = AceType::DynamicCast<FrameNode>(parent);
            if (parentNode) {
                auto pattern = parentNode->GetPattern<ScrollablePattern>();
                if (pattern) {
                    scrollableParentInfo_.parentIds.emplace_back(parentNode->GetId());
                    registerScrollCallback(parentNode->GetId(), host->GetId());
                }
            }
            parent = parent->GetParent();
        }
        scrollableParentInfo_.hasParent = !scrollableParentInfo_.parentIds.empty();
        LOGI("find scrollable parent %{public}d", scrollableParentInfo_.hasParent);
    } else {
        for (const auto& scrollId : scrollableParentInfo_.parentIds) {
            registerScrollCallback(scrollId, host->GetId());
        }
    }
}

void SelectOverlayClient::StopListeningScrollableParent(const RefPtr<FrameNode>& host)
{
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    context->GetSelectOverlayManager()->RemoveScrollCallback(host->GetId());
}

} // namespace OHOS::Ace::NG