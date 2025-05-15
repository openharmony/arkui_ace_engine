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

#include "base/error/error_code.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/listener.h"
#include "core/components_ng/manager/focus/focus_view.h"

namespace OHOS::Ace::NG {

class PipelineContext;

template<typename ContainerType, typename... Args>
class ACE_EXPORT FocusCallbackManager : public virtual AceType {
    DECLARE_ACE_TYPE(FocusCallbackManager, AceType);

public:
    using ValueType = std::function<void(Args...)>;
    FocusCallbackManager() = default;
    ~FocusCallbackManager() override = default;

    void SetListener(int32_t key, const ValueType& callback)
    {
        callbackContainer_.insert_or_assign(key, callback);
    }

    int32_t AddListener(const ValueType& callback)
    {
        if (callbackContainer_.size() == static_cast<size_t>(std::numeric_limits<int32_t>::max() - 1)) {
            return -1;
        }
        int32_t handler = nextKey_;
        callbackContainer_.emplace(handler, callback);

        do {
            nextKey_ = (nextKey_ == std::numeric_limits<int32_t>::max()) ? 0 : ++nextKey_;
        } while (callbackContainer_.count(nextKey_) != 0);
        return handler;
    }

    void RemoveListener(int32_t key)
    {
        callbackContainer_.erase(key);
    }

    void ClearListener()
    {
        callbackContainer_.clear();
    }

    void NotifyListener(Args... args)
    {
        for (const auto& [id, callback] : callbackContainer_) {
            if (callback) {
                callback(args...);
            }
        }
    }

private:
    ContainerType callbackContainer_;
    int32_t nextKey_ { 0 };
};

using FocusViewMap = std::unordered_map<int32_t, std::pair<WeakPtr<FocusView>, std::list<WeakPtr<FocusView>>>>;
using RequestFocusCallback = std::function<void(NG::RequestFocusResult result)>;
using FocusHubScopeMap = std::unordered_map<std::string, std::pair<WeakPtr<FocusHub>, std::list<WeakPtr<FocusHub>>>>;

using FocusChangeCallback =
    std::function<void(const WeakPtr<FocusHub>& last, const RefPtr<FocusHub>& current, FocusReason focusReason)>;
using FocusActiveChangeCallback = std::function<void(bool isFocusActive)>;
using IsFocusActiveUpdateEvent = std::function<void(bool isFocusActive)>;

using FocusChangeCallbackManager = FocusCallbackManager<std::map<int32_t, FocusChangeCallback>, const WeakPtr<FocusHub>,
    const RefPtr<FocusHub>, FocusReason>;
using FocusActiveChangeCallbackManager =
    FocusCallbackManager<std::unordered_map<int32_t, FocusActiveChangeCallback>, bool>;
using IsFocusActiveUpdateEventManager = FocusCallbackManager<std::map<int32_t, IsFocusActiveUpdateEvent>, bool>;

enum class FocusActiveReason : int32_t {
    POINTER_EVENT = 0,
    DEFAULT = 1,
    USE_API = 2,
    KEY_TAB = 3,
    ACTIVE_MARK = 4,
};

enum class FocusViewStackState : int32_t {
    IDLE = 0,
    SHOW = 1,
    CLOSE = 2,
};

enum class KeyProcessingMode : int32_t {
    FOCUS_NAVIGATION = 0,
    ANCESTOR_EVENT = 1,
};

#define DECLARE_FOCUS_CALLBACK_MANAGER(callbackName, callbackType, managerName, managerType) \
public:                                                                                      \
    void Set##callbackName(int32_t key, const callbackType& callback)                        \
    {                                                                                        \
        if (!focusCallbacks_) {                                                              \
            focusCallbacks_ = MakeRefPtr<FocusCallbacks>();                                  \
        }                                                                                    \
        focusCallbacks_->managerName##_->SetListener(key, callback);                         \
    }                                                                                        \
    int32_t Add##callbackName(const callbackType& callback)                                  \
    {                                                                                        \
        if (!focusCallbacks_) {                                                              \
            focusCallbacks_ = MakeRefPtr<FocusCallbacks>();                                  \
        }                                                                                    \
        return focusCallbacks_->managerName##_->AddListener(callback);                       \
    }                                                                                        \
    void Remove##callbackName(int32_t key)                                                   \
    {                                                                                        \
        if (focusCallbacks_) {                                                               \
            focusCallbacks_->managerName##_->RemoveListener(key);                            \
        }                                                                                    \
    }                                                                                        \
    void Clear##callbackName()                                                               \
    {                                                                                        \
        if (focusCallbacks_) {                                                               \
            focusCallbacks_->managerName##_->ClearListener();                                \
        }                                                                                    \
    }                                                                                        \
    RefPtr<managerType> Get##callbackName##Manager()                                         \
    {                                                                                        \
        if (focusCallbacks_) {                                                               \
            return focusCallbacks_->managerName##_;                                          \
        }                                                                                    \
        return nullptr;                                                                      \
    }

class FocusCallbacks : public virtual AceType {
    DECLARE_ACE_TYPE(FocusCallbacks, AceType);

public:
    FocusCallbacks()
    {
        focusActiveChangeCallbacks_ = MakeRefPtr<FocusActiveChangeCallbackManager>();
        focusChangeCallbacks_ = MakeRefPtr<FocusChangeCallbackManager>();
        isFocusActiveUpdateEvents_ = MakeRefPtr<IsFocusActiveUpdateEventManager>();
    }
    ~FocusCallbacks() override = default;

    RefPtr<FocusActiveChangeCallbackManager> focusActiveChangeCallbacks_;
    RefPtr<FocusChangeCallbackManager> focusChangeCallbacks_;
    RefPtr<IsFocusActiveUpdateEventManager> isFocusActiveUpdateEvents_;
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
    void FocusViewClose(const RefPtr<FocusView>& focusView, bool isDetachFromTree = false);

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

    void SetRequestFocusResult(const int32_t requestFocusResult)
    {
        requestFocusResult_ = requestFocusResult;
    }

    int32_t GetRequestFocusResult()
    {
        return requestFocusResult_;
    }

    void ResetRequestFocusResult()
    {
        requestFocusResult_ = ERROR_CODE_NO_ERROR;
    }

    void SetLastFocusStateNode(const RefPtr<FocusHub>& node)
    {
        lastFocusStateNode_ = AceType::WeakClaim(AceType::RawPtr(node));
        if (isNeedTriggerScroll_.has_value()) {
            isNeedTriggerScroll_ = true;
        }
    }
    RefPtr<FocusHub> GetLastFocusStateNode() const
    {
        return lastFocusStateNode_.Upgrade();
    }

    void SetNeedTriggerScroll(std::optional<bool> isNeedTriggerScroll)
    {
        isNeedTriggerScroll_ = isNeedTriggerScroll;
    }

    bool GetNeedTriggerScroll() const
    {
        return isNeedTriggerScroll_.value_or(false);
    }

    void SetIsAutoFocusTransfer(bool isAutoFocusTransfer)
    {
        isAutoFocusTransfer_ = isAutoFocusTransfer;
    }

    bool IsAutoFocusTransfer() const
    {
        return isAutoFocusTransfer_;
    }

    bool RearrangeViewStack();

    void SetFocusViewStackState(FocusViewStackState focusViewStackState)
    {
        focusViewStackState_ = focusViewStackState;
    }

    void SetKeyProcessingMode(KeyProcessingMode keyProcessingMode)
    {
        keyProcessingMode_ = keyProcessingMode;
    }

    KeyProcessingMode GetKeyProcessingMode() const
    {
        return keyProcessingMode_;
    }

    bool SetFocusViewRootScope(const RefPtr<FocusView>& focusView);

    void PaintFocusState();

    bool AddFocusScope(const std::string& focusScopeId, const RefPtr<FocusHub>& scopeFocusHub);
    void RemoveFocusScope(const std::string& focusScopeId);
    void AddScopePriorityNode(const std::string& focusScopeId, const RefPtr<FocusHub>& priorFocusHub, bool pushFront);
    void RemoveScopePriorityNode(const std::string& focusScopeId, const RefPtr<FocusHub>& priorFocusHub);
    std::optional<std::list<WeakPtr<FocusHub>>*> GetFocusScopePriorityList(const std::string& focusScopeId);

    void UpdateCurrentFocus(const RefPtr<FocusHub>& current, SwitchingUpdateReason reason);
    RefPtr<FocusHub> GetCurrentFocus();
    void UpdateSwitchingEndReason(SwitchingEndReason reason)
    {
        if (isSwitchingFocus_.value_or(false)) {
            endReason_ = reason;
        }
    }
    void TriggerAllFocusActiveChangeCallback(bool isFocusActive);
    void FocusSwitchingStart(const RefPtr<FocusHub>& focusHub, SwitchingStartReason reason);
    void FocusSwitchingEnd(SwitchingEndReason reason = SwitchingEndReason::FOCUS_GUARD_DESTROY);
    void WindowFocusMoveStart();
    void WindowFocusMoveEnd();
    void WindowFocus(bool isFocus);
    std::optional<FocusEvent> GetCurrentFocusEvent()
    {
        return currentFocusEvent_;
    }

    void SetCurrentFocusEvent(const FocusEvent& event)
    {
        currentFocusEvent_.reset();
        currentFocusEvent_.emplace(event);
    }

    void ResetCurrentFocusEvent()
    {
        currentFocusEvent_.reset();
    }

    static RefPtr<FocusManager> GetFocusManager(RefPtr<FrameNode>& node);

    bool SetIsFocusActive(
        bool isFocusActive, FocusActiveReason reason = FocusActiveReason::DEFAULT, bool autoFocusInactive = true);
    bool GetIsFocusActive() const
    {
        return isFocusActive_;
    }
    bool HandleKeyForExtendOrActivateFocus(const KeyEvent& event, const RefPtr<FocusView>& curFocusView);
    bool ExtendOrActivateFocus(
        const RefPtr<FocusView>& curFocusView, FocusActiveReason reason = FocusActiveReason::DEFAULT);

private:
    void GetFocusViewMap(FocusViewMap& focusViewMap);
    void ReportFocusSwitching(FocusReason focusReason);
    bool NeedChangeFocusAvtive(bool isFocusActive, FocusActiveReason reason, bool autoFocusInactive);

    std::list<WeakPtr<FocusView>> focusViewStack_;
    WeakPtr<FocusView> lastFocusView_;
    const WeakPtr<PipelineContext> pipeline_;

    RequestFocusCallback requestCallback_;

    WeakPtr<FocusHub> lastFocusStateNode_;
    WeakPtr<FocusHub> currentFocus_;
    /**
     * In the case of a scrollable component's sliding state, this variable will be set to nullopt to prevent the
     * ScrollBy animation triggered by FireFocusScroll from interrupting the sliding animation of the component.
     * In the SetLastFocusStateNode method, this variable will not be set to true until it has value.
     */
    std::optional<bool> isNeedTriggerScroll_ = false;
    FocusHubScopeMap focusHubScopeMap_;

    DECLARE_FOCUS_CALLBACK_MANAGER(FocusActiveChangeCallback, FocusActiveChangeCallback, focusActiveChangeCallbacks,
        FocusActiveChangeCallbackManager);
    DECLARE_FOCUS_CALLBACK_MANAGER(
        FocusChangeCallback, FocusChangeCallback, focusChangeCallbacks, FocusChangeCallbackManager);
    DECLARE_FOCUS_CALLBACK_MANAGER(
        IsFocusActiveUpdateEvent, IsFocusActiveUpdateEvent, isFocusActiveUpdateEvents, IsFocusActiveUpdateEventManager);
    RefPtr<FocusCallbacks> focusCallbacks_;

    std::optional<bool> isSwitchingFocus_;
    bool isSwitchingWindow_ = false;
    RefPtr<FocusHub> switchingFocus_;

    std::optional<SwitchingStartReason> startReason_;
    std::optional<SwitchingEndReason> endReason_;
    std::optional<SwitchingUpdateReason> updateReason_;

    bool isAutoFocusTransfer_ = true;
    bool isFocusActive_ = false;
    bool autoFocusInactive_ = true;
    FocusViewStackState focusViewStackState_ = FocusViewStackState::IDLE;

    int32_t requestFocusResult_ = ERROR_CODE_NO_ERROR;
    std::optional<FocusEvent> currentFocusEvent_;
    KeyProcessingMode keyProcessingMode_ = KeyProcessingMode::FOCUS_NAVIGATION;
    ACE_DISALLOW_COPY_AND_MOVE(FocusManager);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_FOCUS_FOCUS_MANAGER_H
