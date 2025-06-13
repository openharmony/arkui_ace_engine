/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_FRONTEND_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_FRONTEND_H

#include <string>
#include <utility>

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "base/utils/resource_configuration.h"
#include "bridge/common/utils/source_map.h"
#include "core/common/js_message_dispatcher.h"
#include "core/common/router_recover_record.h"
#include "core/event/ace_event_handler.h"
#include "interfaces/inner_api/ace/constants.h"

using FrontendDialogCallback = std::function<void(const std::string& event, const std::string& param)>;

typedef struct napi_value__* napi_value;

namespace OHOS::Ace {

class AcePage;
class PipelineBase;
class AssetManager;
class TaskExecutor;
class AccessibilityManager;
enum class ContentInfoType;

#ifndef WEARABLE_PRODUCT
constexpr int32_t DEFAULT_DESIGN_WIDTH = 720;
#else
constexpr int32_t DEFAULT_DESIGN_WIDTH = 454;
#endif

// Window config of frontend.
struct WindowConfig {
    // NOT runtime real design width, this is config value set by user.
    // Runtime design width should be considered together with autoDesignWidth.
    int32_t designWidth = DEFAULT_DESIGN_WIDTH;
    bool autoDesignWidth = false;
    bool boxWrap = false;
    double designWidthScale = 0.0;

    double GetDesignWidthScale(const double viewWidth)
    {
        if (NearEqual(designWidthScale, 0.0)) {
            if (designWidth <= 0) {
                LOGI("designWidth <= 0");
                designWidth = DEFAULT_DESIGN_WIDTH;
            }
            return viewWidth / designWidth;
        }
        return designWidthScale;
    }

    void UpdateDesignWidthScale(const double viewWidth)
    {
        if (designWidth <= 0) {
            LOGI("designWidth <= 0");
            designWidth = DEFAULT_DESIGN_WIDTH;
        }
        designWidthScale = viewWidth / designWidth;
    }
};

enum class FrontendType { JSON, JS, JS_CARD, DECLARATIVE_JS, JS_PLUGIN, ETS_CARD, DECLARATIVE_CJ, ARK_TS };
struct PageTarget;

class ACE_FORCE_EXPORT Frontend : public AceType {
    DECLARE_ACE_TYPE(Frontend, AceType);

public:
    Frontend() = default;
    ~Frontend() override;

    enum State : uint8_t { ON_CREATE = 0, ON_DESTROY, ON_SHOW, ON_HIDE, ON_ACTIVE, ON_INACTIVE, UNDEFINE };
    static std::string stateToString(int state);

    static RefPtr<Frontend> Create();
    static RefPtr<Frontend> CreateDefault();

    virtual bool Initialize(FrontendType type, const RefPtr<TaskExecutor>& taskExecutor) = 0;

    virtual void Destroy() = 0;

    virtual void AttachPipelineContext(const RefPtr<PipelineBase>& context) = 0;

    virtual void SetAssetManager(const RefPtr<AssetManager>& assetManager) = 0;

    virtual void AddPage(const RefPtr<AcePage>& page) = 0;

    virtual RefPtr<AcePage> GetPage(int32_t pageId) const = 0;

    // Get the currently running JS page information in NG structure.
    virtual std::string GetCurrentPageUrl() const
    {
        return "";
    }

    // Get the currently running JS page information in NG structure.
    virtual RefPtr<Framework::RevSourceMap> GetCurrentPageSourceMap() const
    {
        return nullptr;
    }

    // Get the currently running JS page information in NG structure.
    virtual RefPtr<Framework::RevSourceMap> GetFaAppSourceMap() const
    {
        return nullptr;
    }

    // Get the stage mode sourceMap.
    virtual void GetStageSourceMap(std::unordered_map<std::string, RefPtr<Framework::RevSourceMap>>& sourceMap) const {}

    virtual UIContentErrorCode RunPage(const std::string& content, const std::string& params)
    {
        return UIContentErrorCode::NO_ERRORS;
    }
    virtual UIContentErrorCode RunPage(const std::shared_ptr<std::vector<uint8_t>>& content, const std::string& params)
    {
        return UIContentErrorCode::NO_ERRORS;
    }
    virtual UIContentErrorCode RunDynamicPage(
        const std::string& content, const std::string& params, const std::string& entryPoint)
    {
        return UIContentErrorCode::NO_ERRORS;
    }

    virtual UIContentErrorCode RunPageByNamedRouter(const std::string& name, const std::string& params)
    {
        return UIContentErrorCode::NO_ERRORS;
    }

    virtual UIContentErrorCode RunIntentPage()
    {
        return UIContentErrorCode::NO_ERRORS;
    }

    virtual UIContentErrorCode SetRouterIntentInfo(const std::string& intentInfoSerialized, bool isColdStart,
        const std::function<void()>&& loadPageCallback)
    {
        return UIContentErrorCode::NO_ERRORS;
    }

    virtual std::string GetTopNavDestinationInfo(bool onlyFullScreen, bool needParam)
    {
        return "";
    }

    virtual void ReplacePage(const std::string& url, const std::string& params) = 0;

    virtual void PushPage(const std::string& url, const std::string& params) = 0;

    // Gets front-end event handler to handle ace event.
    virtual RefPtr<AceEventHandler> GetEventHandler() = 0;

    // Get window config of front end, which is used to calculate the pixel ratio of the real device.
    virtual WindowConfig& GetWindowConfig() = 0;

    std::unique_lock<std::recursive_mutex> GetLock() const
    {
        return std::unique_lock<std::recursive_mutex>(mutex_);
    }

    FrontendType GetType() const
    {
        return type_;
    }

    RefPtr<TaskExecutor> GetTaskExecutor() const;

    // inform the frontend that onCreate or onDestroy
    virtual void UpdateState(State) = 0;

    // dump frontend info
    virtual void DumpFrontend() const = 0;

    virtual std::string GetPagePath() const = 0;

    // send the message by js callback
    virtual void SendCallbackMessage(const std::string& callbackId, const std::string& data) const = 0;

    // set the message transfer to js instance
    virtual void SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher>& transfer) const = 0;

    // transfer data back from platform side to component side
    virtual void TransferComponentResponseData(int32_t callbackId, int32_t code, std::vector<uint8_t>&& data) const = 0;

    // transfer data back from platform side to js side
    virtual void TransferJsResponseData(int32_t callbackId, int32_t code, std::vector<uint8_t>&& data) const = 0;

    // transfer error message get in plugin from platform side to js side
    virtual void TransferJsPluginGetError(int32_t callbackId, int32_t errorCode, std::string&& errorMessage) const = 0;

    // transfer event data from platform side to js side
    virtual void TransferJsEventData(int32_t callbackId, int32_t code, std::vector<uint8_t>&& data) const = 0;

    // get system plugin used in application
    virtual void GetPluginsUsed(std::string& data) {}

    // get js code from plugin and load in js engine
    virtual void LoadPluginJsCode(std::string&& jsCode) const = 0;

    virtual void LoadPluginJsByteCode(std::vector<uint8_t>&& jsCode, std::vector<int32_t>&& jsCodeLen) const = 0;

    // when this is foreground frontend
    virtual bool IsForeground() = 0;

    // get accessibility manager handler.
    virtual RefPtr<AccessibilityManager> GetAccessibilityManager() const = 0;

    // when back pressed
    virtual bool OnBackPressed() = 0;

    // when interface show up
    virtual void OnShow() = 0;

    // when interface hide
    virtual void OnHide() = 0;

    // when configuration update
    virtual void OnConfigurationUpdated(const std::string& data) {}

    virtual void OnSaveAbilityState(std::string& data) = 0;

    virtual void OnMemoryLevel(int32_t level) = 0;

    virtual void OnRestoreAbilityState(const std::string& data) = 0;

    // when front on active
    virtual void OnActive() = 0;

    // when front on inactive
    virtual void OnInactive() = 0;

    // when front on asks a user whether to start the migration
    virtual bool OnStartContinuation() = 0;

    // when front on a local ability migration is complete
    virtual void OnCompleteContinuation(int32_t code) = 0;

    // interface to save the user data
    virtual void OnSaveData(std::string& data) = 0;

    // interface to restores the user data on the remote device
    virtual bool OnRestoreData(const std::string& data) = 0;

    virtual void OnRemoteTerminated() = 0;

    // start the ability when it's running
    virtual void OnNewRequest(const std::string& data) = 0;

    virtual void OnNewWant(const std::string& data) = 0;

    // call router back
    virtual void CallRouterBack() = 0;

    virtual void OnSurfaceChanged(int32_t width, int32_t height) = 0;

    virtual void OnLayoutCompleted(const std::string& componentId) = 0;
    virtual void OnDrawCompleted(const std::string& componentId) = 0;
    virtual void OnDrawChildrenCompleted(const std::string& componentId) = 0;
    virtual bool IsDrawChildrenCallbackFuncExist(const std::string& componentId) = 0;

    virtual void TriggerGarbageCollection() {}

    virtual void DumpHeapSnapshot(bool isPrivate) {}

    virtual void DestroyHeapProfiler() {}

    virtual void ForceFullGC() {}

    virtual void NotifyUIIdle() {}

    virtual void RebuildAllPages() {}

    virtual void SetColorMode(ColorMode colorMode) {}

    // navigator component call router
    virtual void NavigatePage(uint8_t type, const PageTarget& target, const std::string& params) {}

    // restore
    virtual std::pair<RouterRecoverRecord, UIContentErrorCode> RestoreRouterStack(
        const std::string& contentInfo, ContentInfoType type)
    {
        return std::make_pair(RouterRecoverRecord(), UIContentErrorCode::NO_ERRORS);
    }

    virtual std::string GetContentInfo(ContentInfoType type) const
    {
        return "";
    }

    // only declarative frontend need to support
    virtual int32_t GetRouterSize() const
    {
        return -1;
    }

    virtual void NotifyAppStorage(const std::string& key, const std::string& value) {}

    virtual napi_value GetContextValue()
    {
        napi_value value = nullptr;
        return value;
    }

    virtual napi_value GetFrameNodeValueByNodeId(int32_t nodeId)
    {
        return nullptr;
    }
#ifdef PREVIEW
    virtual void RunNativeEngineLoop() {}
#endif

    // Disallow pop last page
    void DisallowPopLastPage()
    {
        disallowPopLastPage_ = true;
    }

    virtual void SetDialogCallback(FrontendDialogCallback callback)
    {
        dialogCallback_ = std::move(callback);
    }

    virtual void FlushReload() {}
    // flush frontend for HotReload feature in NG
    virtual void HotReload() {}

    State GetState() const
    {
        return state_;
    }

    virtual void SetErrorEventHandler(std::function<void(const std::string&, const std::string&)>&& errorCallback) {}

    virtual std::string GetPagePathByUrl(const std::string& url) const
    {
        return "";
    }

protected:
    virtual bool MaybeRelease() override;
    FrontendType type_ = FrontendType::JS;
    RefPtr<TaskExecutor> taskExecutor_;
    bool disallowPopLastPage_ = false;
    FrontendDialogCallback dialogCallback_ = nullptr;
    State state_ = State::UNDEFINE;
    mutable std::recursive_mutex mutex_;
    mutable std::mutex destructMutex_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_FRONTEND_H
