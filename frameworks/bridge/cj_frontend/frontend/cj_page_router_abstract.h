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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_CJ_FRONTEND_CJ_PAGE_ROUTER_ABSTRACT_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_CJ_FRONTEND_CJ_PAGE_ROUTER_ABSTRACT_H

#include "base/memory/ace_type.h"
#include "bridge/common/manifest/manifest_parser.h"

namespace OHOS::Ace {

class CJFrontendAbstract;

extern "C" ACE_EXPORT void* OHOSAceFrameworkGetCJFrontendLoader();

constexpr int32_t MAX_ROUTER_STACK_SIZE = 32;
class CJPageRouterAbstract : public AceType {
    DECLARE_ACE_TYPE(CJPageRouterAbstract, AceType)
public:
    enum class RouterMode {
        STANDARD = 0,
        SINGLE,
    };

    enum class RouterAction {
        DEFAULT = 0,
        PUSH,
        REPLACE,
        BACK,
        CLEAR,
    };

    struct RouterPageInfo {
        std::string url;
        RouterMode routerMode = RouterMode::STANDARD;
        std::string path;
        std::function<void(int32_t)> callback;
    };

    struct RouterTask {
        RouterAction action = RouterAction::PUSH;
        RouterPageInfo routerPageInfo;
        std::string params;
    };

    struct RouterState {
        int32_t index;
        char* name;
        char* path;
        char* params;
    };

    struct RouterStateList {
        RouterState* array;
        int64_t size;
        void (*free)(int64_t, RouterState*);
    };

    static void RouterStateListFree(int64_t size, RouterState* src)
    {
        if (!src) {
            return;
        }
        for (int64_t i = 0; i < size; i++) {
            if (src[i].name) {
                delete[] src[i].name;
            }
            if (src[i].path) {
                delete[] src[i].path;
            }
            if (src[i].params) {
                delete[] src[i].params;
            }
        }
        delete[] src;
    }

    virtual void OnShowCurrent() = 0;
    virtual void OnHideCurrent() = 0;
    virtual std::string GetParams() const = 0;
    virtual int32_t GetStackSize() const = 0;
    virtual std::string GetCurrentPageUrl() = 0;
    virtual void EnableAlertBeforeBackPage(const std::string& message, std::function<void(int32_t)> callback) = 0;
    virtual void DisableAlertBeforeBackPage() = 0;
    virtual bool AllowPopLastPage() = 0;
    virtual RefPtr<NG::FrameNode> GetCurrentPageNode()
    {
        return nullptr;
    }
    virtual bool PopWithExitCheck();
    virtual void StartPushPageWithCallback(const RouterPageInfo& target, const std::string& params) = 0;
    virtual void StartReplacePageWithCallback(const RouterPageInfo& target, const std::string& params) = 0;
    virtual void BackCheckAlertIndex(int32_t index, const std::string& params) = 0;
    virtual void GetState(int32_t& index, std::string& name, std::string& path, std::string& params) = 0;
    virtual void GetStateByIndex(int32_t& index, std::string& name, std::string& path, std::string& params) = 0;
    virtual std::vector<RouterState> GetStateByUrl(const std::string& url) = 0;
    void RunPage(const std::string& url, const std::string& params);
    void Push(const RouterPageInfo& target, const std::string& params, RouterMode = RouterMode::STANDARD);
    bool Pop();
    void Replace(const RouterPageInfo& target, const std::string& params, RouterMode = RouterMode::STANDARD);
    void BackWithTarget(const RouterPageInfo& target, const std::string& params);
    void Clear();
    virtual void FlushReload() = 0;
    void SetManifestParser(const RefPtr<Framework::ManifestParser>& manifestParser)
    {
        manifestParser_ = manifestParser;
    }

    std::list<int64_t> GetNativeViews()
    {
        return viewStack_;
    }

    void AddView(int64_t viewId)
    {
        viewStack_.emplace_back(viewId);
    }
    void PushPageWithCallback(const RouterPageInfo& target, const std::string& params);
    void ReplacePageWithCallback(const RouterPageInfo& target, const std::string& params);
    void BackWithIndex(int32_t index, const std::string& params);

protected:
    explicit CJPageRouterAbstract(WeakPtr<CJFrontendAbstract> frontend) : frontend_(std::move(frontend)) {}
    virtual void StartPush(
        const RouterPageInfo& target, const std::string& params, RouterMode mode = RouterMode::STANDARD) = 0;
    virtual bool StartPop() = 0;
    virtual void StartReplace(
        const RouterPageInfo& target, const std::string& params, RouterMode mode = RouterMode::STANDARD) = 0;
    virtual void BackCheckAlert(const RouterPageInfo& target, const std::string& params) = 0;
    virtual void StartClean() = 0;

    // page operations
    virtual void LoadPage(int32_t pageId, const RouterPageInfo& target, const std::string& params,
        bool isRestore = false, bool needHideLast = true, bool needTransition = true) = 0;
    virtual void PopPage(const std::string& params, bool needShowNext, bool needTransition) = 0;
    virtual void PopPageToIndex(int32_t index, const std::string& params, bool needShowNext, bool needTransition) = 0;

protected:
    class ProcessGuard {
    public:
        explicit ProcessGuard(CJPageRouterAbstract* router) : router_(router)
        {
            router_->inRouterOpt_ = true;
        }
        ~ProcessGuard()
        {
            router_->inRouterOpt_ = false;
            router_ = nullptr;
        }

    private:
        CJPageRouterAbstract* router_ = nullptr;
    };

    int32_t GenerateNextPageId();

    WeakPtr<CJFrontendAbstract> frontend_;
    RefPtr<Framework::ManifestParser> manifestParser_;
    bool inRouterOpt_ = false;
    RouterPageInfo ngBackUri_ = { "" };
    std::string backParam_;
    std::list<int64_t> viewStack_;
    int32_t ngBackIndex_ = 0;

private:
    int32_t nextPageId_ = 0;

    ACE_DISALLOW_COPY_AND_MOVE(CJPageRouterAbstract);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_CJ_FRONTEND_CJ_PAGE_ROUTER_ABSTRACT_H
