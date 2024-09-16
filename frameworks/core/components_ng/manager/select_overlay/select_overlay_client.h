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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SELECT_OVERLAY_SELECT_OVERLAY_CLIENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SELECT_OVERLAY_SELECT_OVERLAY_CLIENT_H

#include <cstdint>
#include <functional>
#include <vector>

#include "base/geometry/offset.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/manager/select_overlay/select_overlay_proxy.h"
#include "core/components_ng/manager/select_overlay/selection_host.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

enum class HandleShowMode { DOUBLE, SINGLE, NONE };

struct OverlayExtraInfo {
    std::map<std::string, bool> boolExtra;

    bool GetBoolOrDefault(std::string key, bool defaultValue)
    {
        auto it = boolExtra.find(key);
        if (it == boolExtra.end()) {
            return defaultValue;
        }
        return it->second;
    };
};

struct ClientOverlayInfo {
    std::optional<SelectHandleInfo> firstHandleInfo;
    std::optional<SelectHandleInfo> secondHandleInfo;
    std::optional<Color> handlerColor;
    RectF selectArea;
    bool isNewAvoid = false;
    bool animation = true;
    bool isMenuShow = true;
    bool isShowMouseMenu = false;
    bool isShowPaste = false;
    bool isUpdateMenu = true;
};

struct ScrollableParentInfo {
    bool hasParent = true;
    std::vector<int32_t> parentIds;
};

enum class SelectOverlayMenuId {
    COPY,
    CUT,
    PASTE,
    SELECT_ALL,
    CAMERA_INPUT,
    AI_WRITE
};

class SelectOverlayClient : public SelectionHost {
    DECLARE_ACE_TYPE(SelectOverlayClient, SelectionHost);

public:
    void InitSelectOverlay();
    void InitMenuCallback();
    void RequestOpenSelectOverlay(ClientOverlayInfo& overlayInfo);
    virtual void RequestCloseSelectOverlay(bool animation);
    bool SelectOverlayIsOn();

    virtual bool CheckHandleVisible(const RectF& paintRect)
    {
        return true;
    }

    virtual bool CheckSelectionRectVisible()
    {
        return false;
    }

    virtual bool OnPreShowSelectOverlay(
        SelectOverlayInfo& overlayInfo, const ClientOverlayInfo& clientInfo, bool isSelectOverlayOn)
    {
        return false;
    }

    virtual void OnSelectOverlayMenuClicked(SelectOverlayMenuId menuId) {}
    virtual void OnHandleMoveStart(const GestureEvent& event, bool isFirst) {}
    virtual void OnHandleMove(const RectF&, bool isFirst) {}
    virtual void OnHandleMoveDone(const RectF&, bool isFirst) {}
    virtual void OnHandleClosed(bool closedByGlobalEvent)
    {
        if (closedByGlobalEvent) {
            StopListeningScrollableParent(GetClientHost());
        }
    }

    virtual RefPtr<FrameNode> GetClientHost() const
    {
        return nullptr;
    }

    void UpdateSelectInfo(const std::string& selectInfo);

    virtual void OnParentScrollStartOrEnd(bool isEnd, bool noAnimation = false);

    virtual void OnParentScrollCallback(Axis axis, int32_t offset) {};

    void StartListeningScrollableParent(const RefPtr<FrameNode>& host);

    void StopListeningScrollableParent(const RefPtr<FrameNode>& host);

    void UpdateSelectMenuInfo(std::function<void(SelectMenuInfo&)> updateAction);

    void UpdateSelectMenuVisibility(bool isVisible);

    bool IsShowingSingleHandle()
    {
        auto proxy = GetSelectOverlayProxy();
        CHECK_NULL_RETURN(proxy, false);
        return proxy->IsSingleHandle();
    }

    RectF GetVisibleContentRect(WeakPtr<FrameNode> parent, RectF visibleRect);

protected:
    const RefPtr<SelectOverlayProxy>& GetSelectOverlayProxy()
    {
        return selectOverlayProxy_;
    }

    void ResetSelectOverlayClient()
    {
        scrollableParentInfo_.hasParent = true;
        scrollableParentInfo_.parentIds.clear();
    }

    void UpdateOriginIsMenuShow(bool isShow)
    {
        originIsMenuShow_ = isShow;
    }
    
    bool GetOriginIsMenuShow()
    {
        return originIsMenuShow_;
    }

private:
    bool originIsMenuShow_ = true;
    void RegisterParentScrollCallback(int32_t parentId, int32_t callbackId);
    std::optional<SelectOverlayInfo> GetSelectOverlayInfo(const ClientOverlayInfo& clientInfo);
    void CreateSelectOverlay(const ClientOverlayInfo& showOverlayInfo);
    void UpdateShowingSelectOverlay(ClientOverlayInfo& clientInfo);
    ScrollableParentInfo scrollableParentInfo_;
    SelectOverlayInfo selectOverlayInfo_;
    RefPtr<SelectOverlayProxy> selectOverlayProxy_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SELECT_OVERLAY_SELECT_OVERLAY_CLIENT_H