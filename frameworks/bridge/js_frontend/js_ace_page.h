/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_JS_FRONTEND_JS_ACE_PAGE_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_JS_FRONTEND_JS_ACE_PAGE_H

#include <string>
#include <unordered_set>
#include <vector>

#include "base/utils/macros.h"
#include "core/common/ace_page.h"
#include "core/components/checkable/radio_group_component.h"
#include "core/components/page_transition/page_transition_component.h"
#include "frameworks/bridge/common/dom/dom_document.h"
#include "frameworks/bridge/common/utils/source_map.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/js_frontend/engine/common/base_animation_bridge.h"
#include "frameworks/bridge/js_frontend/engine/common/base_canvas_bridge.h"
#include "frameworks/bridge/js_frontend/js_command.h"

namespace OHOS::Ace::Framework {

using JsPageRadioGroups = std::unordered_map<std::string, RadioGroupComponent<std::string>>;

// One JsAcePage corresponding to a JS bundle, so it should maintain page's lifecycle.
class ACE_EXPORT JsAcePage final : public AcePage {
    DECLARE_ACE_TYPE(JsAcePage, AcePage);

public:
    JsAcePage(int32_t pageId, const RefPtr<DOMDocument>& document, const std::string& url)
        : AcePage(pageId), domDoc_(document), url_(url), radioGroups_(std::make_shared<JsPageRadioGroups>())
    {
        ACE_DCHECK(domDoc_);
    }

    ~JsAcePage() override;

    RefPtr<PageComponent> BuildPage(const std::string& url) override;
    RefPtr<ComposedComponent> BuildPagePatch(int32_t nodeId);

    RefPtr<DOMDocument> GetDomDocument() const
    {
        return domDoc_;
    }

    const std::string& GetUrl() const
    {
        return url_;
    }

    bool CheckPageCreated() const
    {
        return pageCreated_;
    }

    void SetPageCreated()
    {
        pageCreated_ = true;
    }

    void SetPageTransition(const RefPtr<PageTransitionComponent>& pageTransition)
    {
        pageTransition_ = pageTransition;
    }

    void PushCommand(const RefPtr<JsCommand>& jsCommand)
    {
        jsCommands_.emplace_back(jsCommand);
    }

    void PopAllCommands(std::vector<RefPtr<JsCommand>>& jsCommands)
    {
        jsCommands = std::move(jsCommands_);
    }

    void PushNewNode(NodeId nodeId, NodeId parentNodeId)
    {
        dirtyNodes_.emplace(nodeId);
        PushDirtyNode(parentNodeId);
    }

    void PushDirtyNode(NodeId nodeId)
    {
        auto result = dirtyNodes_.emplace(nodeId);
        if (result.second) {
            dirtyNodesOrderedByTime_.emplace_back(nodeId);
        }
    }

    void PopAllDirtyNodes(std::vector<NodeId>& dirtyNodes)
    {
        dirtyNodes = std::move(dirtyNodesOrderedByTime_);
        dirtyNodes_.clear();
    }

    void ClearAllDirtyNodes()
    {
        dirtyNodesOrderedByTime_.clear();
        dirtyNodes_.clear();
    }

    void ReserveShowCommand(const RefPtr<JsCommand>& command)
    {
        if (command) {
            showCommands_.emplace_back(command);
        }
    }

    void UpdateShowAttr()
    {
        if (showCommands_.empty()) {
            return;
        }

        for (auto& command : showCommands_) {
            command->Execute(AceType::Claim(this));
        }
        showCommandConsumed_ = true;
    }

    bool CheckShowCommandConsumed() const
    {
        return showCommandConsumed_;
    }

    void ClearShowCommand()
    {
        showCommands_.clear();
        showCommandConsumed_ = false;
    }

    RefPtr<BaseCanvasBridge> GetBridgeById(NodeId nodeId);
    void PushCanvasBridge(NodeId nodeId, const RefPtr<BaseCanvasBridge>& bridge);

    RefPtr<BaseAnimationBridge> GetAnimationBridge(NodeId nodeId);
    void RemoveAnimationBridge(NodeId nodeId);
    void AddAnimationBridge(NodeId nodeId, const RefPtr<BaseAnimationBridge>& animationBridge);

    void SetPageParams(const std::string& params)
    {
        pageParams_ = params;
    }

    const std::string& GetPageParams() const
    {
        return pageParams_;
    }

    void SetFlushCallback(std::function<void(const RefPtr<JsAcePage>&)>&& callback)
    {
        flushCallback_ = std::move(callback);
    }

    void FlushCommands()
    {
        if (flushCallback_) {
            fragmentCount_++;
            flushCallback_(AceType::Claim(this));
        }
    }

    int32_t FragmentCount() const
    {
        return fragmentCount_;
    }

    size_t GetCommandSize() const
    {
        return jsCommands_.size();
    }

    void SetPipelineContext(const WeakPtr<PipelineContext>& pipelineContext)
    {
        pipelineContext_ = pipelineContext;
    }

    WeakPtr<PipelineContext> GetPipelineContext() const
    {
        return pipelineContext_;
    }

    bool IsLiteStyle() const
    {
        return useLiteStyle_;
    }

    void SetUseLiteStyle(bool useLiteStyle)
    {
        useLiteStyle_ = useLiteStyle;
    }

    bool IsUseBoxWrap() const
    {
        return useBoxWrap_;
    }

    void SetUseBoxWrap(bool useBoxWrap)
    {
        useBoxWrap_ = useBoxWrap;
    }

    void AddNodeEvent(int32_t nodeId, const std::string& actionType, const std::string& eventAction);

    std::string& GetNodeEventAction(int32_t nodeId, const std::string& actionType);
    std::shared_ptr<JsPageRadioGroups> GetRadioGroups();

    void SetRootComponent(const RefPtr<Component>& component)
    {
        component_ = component;
    }

    void SetPageMap(const std::string& pageMap)
    {
        pageMap_ = AceType::MakeRefPtr<RevSourceMap>();
        pageMap_->Init(pageMap);
    }

    RefPtr<RevSourceMap> GetPageMap() const
    {
        return pageMap_;
    }

    void SetAppMap(const std::string& appMap)
    {
        appMap_ = AceType::MakeRefPtr<RevSourceMap>();
        appMap_->Init(appMap);
    }

    RefPtr<RevSourceMap> GetAppMap() const
    {
        return appMap_;
    }

private:
    void SwapBackgroundDecoration(const RefPtr<PageTransitionComponent>& transition);

    bool pageCreated_ = false;
    bool showCommandConsumed_ = false;
    int32_t fragmentCount_ = 0;

    WeakPtr<PipelineContext> pipelineContext_;
    RefPtr<PageTransitionComponent> pageTransition_;
    RefPtr<Component> component_;
    RefPtr<DOMDocument> domDoc_;
    std::string url_;

    RefPtr<RevSourceMap> pageMap_;
    RefPtr<RevSourceMap> appMap_;
    bool useLiteStyle_ = false;
    bool useBoxWrap_ = false;

    std::vector<RefPtr<JsCommand>> jsCommands_;
    std::vector<NodeId> dirtyNodesOrderedByTime_;
    std::unordered_set<NodeId> dirtyNodes_;
    std::vector<RefPtr<JsCommand>> showCommands_;
    std::function<void(const RefPtr<JsAcePage>&)> flushCallback_;
    std::string pageParams_;
    std::unordered_map<NodeId, std::unordered_map<std::string, std::string>> nodeEvent_;
    std::unordered_map<NodeId, RefPtr<BaseAnimationBridge>> animationBridges_;
    std::unordered_map<NodeId, RefPtr<BaseCanvasBridge>> canvasBridges_;
    std::shared_ptr<JsPageRadioGroups> radioGroups_;
};

} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_JS_FRONTEND_JS_ACE_PAGE_H
