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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_PAGE_ROUTER_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_PAGE_ROUTER_MANAGER_H

#include <cstdint>
#include <list>
#include <string>
#include <utility>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/thread/task_executor.h"
#include "base/utils/noncopyable.h"
#include "bridge/declarative_frontend/ng/entry_page_info.h"
#include "core/common/router_recover_record.h"
#include "core/components_ng/base/frame_node.h"
#include "frameworks/bridge/common/manifest/manifest_parser.h"
#include "interfaces/inner_api/ace/constants.h"
#include "bridge/js_frontend/frontend_delegate.h"

namespace OHOS::Ace::NG {

using LoadPageCallback = std::function<bool(const std::string&,
    const std::function<void(const std::string&, int32_t)>&)>;
using LoadPageByBufferCallback = std::function<bool(const std::shared_ptr<std::vector<uint8_t>>& content,
    const std::function<void(const std::string&, int32_t)>&, const std::string& contentName)>;
using LoadCardCallback = std::function<bool(const std::string&, int64_t cardId, const std::string&)>;
using LoadNamedRouterCallback = std::function<bool(const std::string&, bool isTriggeredByJs)>;
using RestoreFullPathInfoCallback = std::function<void(std::unique_ptr<JsonValue>)>;
using GetFullPathInfoCallback = std::function<std::unique_ptr<JsonValue>()>;
using RestoreNamedRouterInfoCallback = std::function<void(std::unique_ptr<JsonValue>)>;
using GetNamedRouterInfoCallback = std::function<std::unique_ptr<JsonValue>()>;
using IsNamedRouterNeedPreloadCallback = std::function<bool(const std::string&)>;
using PreloadNamedRouterCallback = std::function<void(const std::string&, std::function<void(bool)>&&)>;
using UpdateRootComponentCallback = std::function<bool()>;
using GenerateIntentPageCallback = std::function<bool(const std::string&, const std::string&, const std::string&)>;
#if defined(PREVIEW)
using IsComponentPreviewCallback = std::function<bool()>;
#endif

enum class RouterMode {
    STANDARD = 0,
    SINGLE,
};

struct RouterIntentInfo {
    std::string bundleName;
    std::string moduleName;
    std::string pagePath;
    std::string param;
    std::function<void()> loadPageCallback;
    bool isColdStart;

    std::string ToString()
    {
        return "----------- RouterIntentInfo -----------\n"
               "bundleName:  " + bundleName + "\n"
               "moduleName:  " + moduleName + "\n"
               "pagePath:    " + pagePath + "\n"
               "isColdStart: " + (isColdStart? "yes" : "no") + "\n"
               "----------------------------------------\n";
    }
};

struct RouterPageInfo {
    std::string url;
    std::string params;
    bool recoverable = true;
    RouterMode routerMode = RouterMode::STANDARD;
    std::function<void(const std::string&, int32_t)> errorCallback;
    std::string path;
    bool isNamedRouterMode = false;
    std::shared_ptr<std::vector<uint8_t>> content;
    RouterIntentInfo intentInfo;
    bool isUseIntent = false;
};

class PageRouterManager : public AceType {
    DECLARE_ACE_TYPE(PageRouterManager, AceType);
public:
    PageRouterManager() = default;
    ~PageRouterManager() override = default;

    void RunPage(const std::string& url, const std::string& params);
    void RunPage(const std::shared_ptr<std::vector<uint8_t>>& content, const std::string& params);
    void RunPageByNamedRouter(const std::string& name, const std::string& params);
    UIContentErrorCode RunCard(
        const std::string& url, const std::string& params, int64_t cardId, const std::string& entryPoint = "");

    void SetManifestParser(const RefPtr<Framework::ManifestParser>& manifestParser)
    {
        manifestParser_ = manifestParser;
    }

    void SetLoadJsCallback(LoadPageCallback&& callback)
    {
        loadJs_ = std::move(callback);
    }

    void SetLoadJsByBufferCallback(LoadPageByBufferCallback&& callback)
    {
        loadJsByBuffer_ = std::move(callback);
    }

    void SetLoadCardCallback(const LoadCardCallback& callback)
    {
        loadCard_ = callback;
    }

    void SetLoadNamedRouterCallback(LoadNamedRouterCallback&& callback)
    {
        loadNamedRouter_ = callback;
    }

    void SetRestoreFullPathInfoCallback(RestoreFullPathInfoCallback&& callback)
    {
        restoreFullPathInfo_ = callback;
    }

    void SetGetFullPathInfoCallback(GetFullPathInfoCallback&& callback)
    {
        getFullPathInfo_ = callback;
    }

    void SetRestoreNamedRouterInfoCallback(RestoreNamedRouterInfoCallback&& callback)
    {
        restoreNamedRouterInfo_ = callback;
    }

    void SetGetNamedRouterInfoCallback(GetNamedRouterInfoCallback&& callback)
    {
        getNamedRouterInfo_ = callback;
    }

    void SetIsNamedRouterNeedPreloadCallback(IsNamedRouterNeedPreloadCallback&& callback)
    {
        isNamedRouterNeedPreload_ = callback;
    }

    void SetPreloadNamedRouterCallback(PreloadNamedRouterCallback&& callback)
    {
        preloadNamedRouter_ = callback;
    }

    void SetUpdateRootComponentCallback(UpdateRootComponentCallback&& callback)
    {
        updateRootComponent_ = callback;
    }

    void SetGenerateIntentPageCallback(GenerateIntentPageCallback&& callback)
    {
        generateIntentPageCallback_ = callback;
    }
#if defined(PREVIEW)
    void SetIsComponentPreview(IsComponentPreviewCallback&& callback)
    {
        isComponentPreview_ = callback;
    }
#endif

    void EnableAlertBeforeBackPage(const std::string& message, std::function<void(int32_t)>&& callback);

    void DisableAlertBeforeBackPage();

    // router operation
    void Push(const RouterPageInfo& target);

    // For ArkTS1.2
    RefPtr<FrameNode> PushExtender(const RouterPageInfo& target);
    RefPtr<FrameNode> ReplaceExtender(const RouterPageInfo& target, std::function<void()>&& enterFinishCallback);
    RefPtr<FrameNode> RunPageExtender(const RouterPageInfo& target);

    void PushNamedRoute(const RouterPageInfo& target);
    bool Pop();
    void Replace(const RouterPageInfo& target);
    void ReplaceNamedRoute(const RouterPageInfo& target);
    void BackWithTarget(const RouterPageInfo& target);
    void BackToIndexWithTarget(int32_t index, const std::string& params);
    void Clear();
    int32_t GetStackSize() const;
    int32_t GetCurrentPageIndex() const;
    RouterPageInfo GetPageInfoByIndex(int32_t index, const std::string& params);

    void GetState(int32_t& index, std::string& name, std::string& path);
    void GetStateByIndex(int32_t index, std::string& name, std::string& path, std::string& params);
    void GetStateByUrl(std::string& url, std::vector<Framework::StateInfo>& stateArray);

    void GetPageNameAndPath(const std::string& url, std::string& name, std::string& path);
    int32_t GetPageIndex(const WeakPtr<FrameNode>& page);

    std::string GetInitParams() const;
    std::string GetParams() const;

    int32_t GetIndexByUrl(const std::string& url) const;

    RefPtr<FrameNode> GetCurrentPageNode() const
    {
        if (pageRouterStack_.empty()) {
            return nullptr;
        }
        return pageRouterStack_.back().Upgrade();
    }

    std::string GetCurrentPageUrl();

    // Get the currently running JS page information in NG structure.
    RefPtr<Framework::RevSourceMap> GetCurrentPageSourceMap(const RefPtr<AssetManager>& assetManager);

    void SetIsCard()
    {
        isCardRouter_ = true;
    }

    void FlushFrontend();

    std::unique_ptr<JsonValue> GetStackInfo(ContentInfoType type);
    std::unique_ptr<JsonValue> GetNamedRouterInfo();
    std::unique_ptr<JsonValue> GetFullPathInfo();

    std::pair<RouterRecoverRecord, UIContentErrorCode> RestoreRouterStack(
        std::unique_ptr<JsonValue> stackInfo, ContentInfoType type);
    void RestoreNamedRouterInfo(std::unique_ptr<JsonValue> namedRouterInfo);
    void RestoreFullPathInfo(std::unique_ptr<JsonValue> fullPathInfo);

    // begin from 1
    bool IsUnrestoreByIndex(int32_t index);

    void RunIntentPage();
    bool FireNavigationIntentActively(int32_t pageId, bool needTransition);
    void SetRouterIntentInfo(const std::string& intentInfoSerialized, bool isColdStart,
        const std::function<void()>&& loadPageCallback);
    std::string GetTopNavDestinationInfo(bool onlyFullScreen, bool needParam);

protected:
    class RouterOptScope {
    public:
        explicit RouterOptScope(PageRouterManager* manager) : manager_(manager)
        {
            manager_->inRouterOpt_ = true;
        }
        ~RouterOptScope()
        {
            manager_->inRouterOpt_ = false;
        }

    private:
        PageRouterManager* manager_ = nullptr;
    };

    // page id manage
    int32_t GenerateNextPageId();

    virtual int32_t GetLastPageIndex()
    {
        return static_cast<int32_t>(pageRouterStack_.size()) - 1;
    }

    std::pair<int32_t, RefPtr<FrameNode>> FindPageInStack(const std::string& url, bool needIgnoreBegin = false);
    std::pair<int32_t, RefPtr<FrameNode>> FindPageInStackByRouteName(
        const std::string& name, bool needIgnoreBegin = false);
    int32_t FindPageInRestoreStack(const std::string& url);

    void SetPageInfoRouteName(const RefPtr<EntryPageInfo>& info);

    void LoadOhmUrl(const RouterPageInfo& target);
    void PushOhmUrl(const RouterPageInfo& target);
    void ReplaceOhmUrl(const RouterPageInfo& target);
    void StartPush(const RouterPageInfo& target);
    void StartReplace(const RouterPageInfo& target);
    void StartBack(const RouterPageInfo& target);
    void StartBackToIndex(int32_t index, const std::string& params);
    bool StartPop();
    void StartRestore(const RouterPageInfo& target);
    void BackCheckAlert(const RouterPageInfo& target);
    void BackToIndexCheckAlert(int32_t index, const std::string& params);
    void StartClean();
    void CleanPageOverlay();

    void UpdateSrcPage();

    enum class RestorePageDestination : int32_t {
        TOP = 0,         // restore page to pageRouterStack_'s top
        BELLOW_TOP = 1,  // restore page bellow pageRouterStack_'s top
        BOTTOM = 2,      // restore page to pageRouterStack_'s bottom
    };

    // page operations
    virtual void LoadPage(int32_t pageId, const RouterPageInfo& target,
        bool needHideLast = true, bool needTransition = true, bool isPush = false);
    void MovePageToFront(int32_t index, const RefPtr<FrameNode>& pageNode, const RouterPageInfo& target,
        bool needHideLast, bool forceShowCurrent = false, bool needTransition = true);
    void RefreshPageIndex(std::list<WeakPtr<FrameNode>>::iterator startIter, int32_t startIndex);
    void RefreshAllPageIndex();
    void RestorePageWithTarget(int32_t index, bool removeRestorePages,
        const RouterPageInfo& target, RestorePageDestination dest, bool needTransition = true);
    void RestorePageWithTargetInner(
        const RouterPageInfo& target, RestorePageDestination dest, bool needTransition = true);
    void StartRestorePageWithTarget(const RouterPageInfo& target, std::function<void()>&& finishCallback,
        RestorePageDestination dest, bool needTransition);

    void PopPage(const std::string& params, bool needShowNext, bool needTransition, bool needReplaceParams = true);
    void PopPageToIndex(int32_t index, const std::string& params, bool needShowNext, bool needTransition);
    void DealReplacePage(const RouterPageInfo& target);
    virtual void ReplacePageInNewLifecycle(const RouterPageInfo& info);

    static bool OnPageReady(const RefPtr<FrameNode>& pageNode, bool needHideLast, bool needTransition,
        bool isCardRouter = false, int64_t cardId = 0);
    bool OnPageReadyAndHandleIntent(const RefPtr<FrameNode>& pageNode, bool needHideLast);
    bool OnPopPage(bool needShowNext, bool needTransition);
    static bool OnPopPageToIndex(int32_t index, bool needShowNext, bool needTransition);
    static bool OnCleanPageStack();

    // For ArkTS1.2
    virtual bool LoadPageExtender(int32_t pageId, const RouterPageInfo& target,
        bool needHideLast = true, bool needTransition = true, bool isPush = false);
    RefPtr<FrameNode> CreatePageExtender(int32_t pageId, const RouterPageInfo& target);

    UIContentErrorCode LoadCard(int32_t pageId, const RouterPageInfo& target, const std::string& params, int64_t cardId,
        bool isRestore = false, bool needHideLast = true, const std::string& entryPoint = "");

    bool CheckIndexValid(int32_t index) const;
    bool CheckOhmUrlValid(const std::string& ohmUrl);
    void ThrowError(const std::string& msg, int32_t code);

    bool TryPreloadNamedRouter(const std::string& name, std::function<void()>&& finishCallback);
    void PushNamedRouteInner(const RouterPageInfo& target);
    void ReplaceNamedRouteInner(const RouterPageInfo& target);
    void RunPageByNamedRouterInner(const std::string& name, const std::string& params);

    RefPtr<FrameNode> CreatePage(int32_t pageId, const RouterPageInfo& target);
    void RestoreOhmUrl(const RouterPageInfo& target, std::function<void()>&& finishCallback,
        RestorePageDestination dest, bool needTransition);
    void PushPageToTop(RefPtr<FrameNode>& pageNode, std::function<void()>&& finishCallback, bool needTransition);
    void InsertPageBellowTop(RefPtr<FrameNode>& pageNode, std::function<void()>&& finishCallback);
    void InsertPageToBottom(RefPtr<FrameNode>& pageNode, std::function<void()>&& finishCallback);
    void LoadOhmUrlPage(const std::string& url, std::function<void()>&& finishCallback,
        const std::function<void(const std::string& errorMsg, int32_t errorCode)>& errorCallback,
        const std::string& finishCallbackTaskName, const std::string& errorCallbackTaskName);
    bool GenerateRouterPageInner(const RouterPageInfo& target);
    std::pair<int32_t, RefPtr<FrameNode>> FindIntentPageInStack() const;
    RouterIntentInfo ParseRouterIntentInfo(const std::string& intentInfoSerialized);
    // only for @normalized ohmUrl
    std::string ParseUrlNameFromOhmUrl(const std::string& ohmUrl);

    RefPtr<Framework::ManifestParser> manifestParser_;

    enum class InsertPageProcessingType : int32_t {
        NONE = 0,
        INSERT_BELLOW_TOP = 1,
        INSERT_BOTTOM = 2,
    };
    InsertPageProcessingType insertPageProcessingType_ = InsertPageProcessingType::NONE;
    bool inRouterOpt_ = false;
    LoadPageCallback loadJs_;
    LoadPageByBufferCallback loadJsByBuffer_;
    LoadCardCallback loadCard_;
    LoadNamedRouterCallback loadNamedRouter_;
    GetFullPathInfoCallback getFullPathInfo_;
    RestoreFullPathInfoCallback restoreFullPathInfo_;
    GetNamedRouterInfoCallback getNamedRouterInfo_;
    RestoreNamedRouterInfoCallback restoreNamedRouterInfo_;
    IsNamedRouterNeedPreloadCallback isNamedRouterNeedPreload_;
    PreloadNamedRouterCallback preloadNamedRouter_;
    UpdateRootComponentCallback updateRootComponent_;
    GenerateIntentPageCallback generateIntentPageCallback_;
    bool isCardRouter_ = false;
    int32_t pageId_ = 0;
    std::list<WeakPtr<FrameNode>> pageRouterStack_;
    std::list<RouterRecoverRecord> restorePageStack_;
    RouterPageInfo ngBackTarget_;
    bool isNewPageReplacing_ = false;
#if defined(PREVIEW)
    IsComponentPreviewCallback isComponentPreview_;
#endif
    std::optional<RouterIntentInfo> intentInfo_ = std::nullopt;

    ACE_DISALLOW_COPY_AND_MOVE(PageRouterManager);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_PAGE_ROUTER_MANAGER_H
