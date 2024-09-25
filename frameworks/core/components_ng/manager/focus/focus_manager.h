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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_FOCUS_FOCUS_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_FOCUS_FOCUS_MANAGER_H

#include <list>
#include <optional>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/manager/focus/focus_view.h"

namespace OHOS::Ace::NG {

class PipelineContext;

using FocusViewMap = std::unordered_map<int32_t, std::pair<WeakPtr<FocusView>, std::list<WeakPtr<FocusView>>>>;
using RequestFocusCallback = std::function<void(NG::RequestFocusResult result)>;
using FocusHubScopeMap = std::unordered_map<std::string, std::pair<WeakPtr<FocusHub>, std::list<WeakPtr<FocusHub>>>>;
using FocusChangeCallback = std::function<void(const WeakPtr<FocusHub>& last, const RefPtr<FocusHub>& current)>;

enum class FocusActiveReason : int32_t {
    POINTER_EVENT = 0,
    KEYBOARD_EVENT = 1,
    USE_API = 2,
};

class FocusManager : public virtual AceType {
    DECLARE_ACE_TYPE(FocusManager, AceType);

public:
    class FocusGuard {
    public:
        explicit FocusGuard(const RefPtr<FocusHub>& focushub, SwitchingStartReason reason);
        FocusGuard() = delete;
        ~FocusGuard();
        void CreateFocusGuard(const RefPtr<FocusHub>& focushub, const RefPtr<FocusManager>& focusManager,
            SwitchingStartReason reason);
    private:
        RefPtr<FocusManager> focusMng_;
    };
    friend FocusGuard;

    explicit FocusManager(const RefPtr<PipelineContext>& pipeline);
    ~FocusManager() override = default;

    void FocusViewShow(const RefPtr<FocusView>& focusView, bool isTriggerByStep = false);
    void FocusViewHide(const RefPtr<FocusView>& focusView);
    void FocusViewClose(const RefPtr<FocusView>& focusView);

    void FlushFocusView();

    void DumpFocusManager();

    WeakPtr<FocusView> GetLastFocusView() const
    {
        return lastFocusView_;
    }

    const std::list<WeakPtr<FocusView>>& GetWeakFocusViewList() const
    {
        return focusViewStack_;
    }

    void SetRequestFocusCallback(const RequestFocusCallback& callback)
    {
        requestCallback_ = std::move(callback);
    }

    void ResetRequestFocusCallback()
    {
        requestCallback_ = nullptr;
    }

    void TriggerRequestFocusCallback(NG::RequestFocusResult result)
    {
        if (requestCallback_) {
            requestCallback_(result);
            requestCallback_ = nullptr;
        }
    }

    void SetLastFocusStateNode(const RefPtr<FocusHub>& node)
    {
        lastFocusStateNode_ = AceType::WeakClaim(AceType::RawPtr(node));
        isNeedTriggerScroll_ = true;
    }
    RefPtr<FocusHub> GetLastFocusStateNode() const
    {
        return lastFocusStateNode_.Upgrade();
    }

    void SetNeedTriggerScroll(bool isNeedTriggerScroll)
    {
        isNeedTriggerScroll_ = isNeedTriggerScroll;
    }
    bool GetNeedTriggerScroll() const
    {
        return isNeedTriggerScroll_;
    }

    void PaintFocusState();

    bool AddFocusScope(const std::string& focusScopeId, const RefPtr<FocusHub>& scopeFocusHub);
    void RemoveFocusScope(const std::string& focusScopeId);
    void AddScopePriorityNode(const std::string& focusScopeId, const RefPtr<FocusHub>& priorFocusHub, bool pushFront);
    void RemoveScopePriorityNode(const std::string& focusScopeId, const RefPtr<FocusHub>& priorFocusHub);
    std::optional<std::list<WeakPtr<FocusHub>>*> GetFocusScopePriorityList(const std::string& focusScopeId);

    void UpdateCurrentFocus(const RefPtr<FocusHub>& current, SwitchingUpdateReason reason);
    RefPtr<FocusHub> GetCurrentFocus();
    int32_t AddFocusListener(FocusChangeCallback&& callback);
    void RemoveFocusListener(int32_t id);
    void FocusSwitchingStart(const RefPtr<FocusHub>& focusHub, SwitchingStartReason reason);
    void FocusSwitchingEnd(SwitchingEndReason reason = SwitchingEndReason::FOCUS_GUARD_DESTROY);
    void WindowFocusMoveStart();
    void WindowFocusMoveEnd();
    void WindowFocus(bool isFocus);

    static RefPtr<FocusManager> GetFocusManager(RefPtr<FrameNode>& node);

private:
    void GetFocusViewMap(FocusViewMap& focusViewMap);
    void ReportFocusSwitching();

    std::list<WeakPtr<FocusView>> focusViewStack_;
    WeakPtr<FocusView> lastFocusView_;
    const WeakPtr<PipelineContext> pipeline_;

    RequestFocusCallback requestCallback_;

    WeakPtr<FocusHub> lastFocusStateNode_;
    WeakPtr<FocusHub> currentFocus_;
    bool isNeedTriggerScroll_ = false;
    FocusHubScopeMap focusHubScopeMap_;

    std::map<int32_t, FocusChangeCallback> listeners_;
    int32_t nextListenerHdl_ = -1;
    std::optional<bool> isSwitchingFocus_;
    bool isSwitchingWindow_ = false;
    RefPtr<FocusHub> switchingFocus_;

    std::optional<SwitchingStartReason> startReason_;
    std::optional<SwitchingEndReason> endReason_;
    std::optional<SwitchingUpdateReason> updateReason_;

    ACE_DISALLOW_COPY_AND_MOVE(FocusManager);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_FOCUS_FOCUS_MANAGER_H
