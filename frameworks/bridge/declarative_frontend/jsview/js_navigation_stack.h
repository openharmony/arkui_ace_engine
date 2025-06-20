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
#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_NAVIGATION_STACK_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_NAVIGATION_STACK_H

#include <functional>
#include <stdint.h>

#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "core/components_ng/pattern/navigation/navigation_stack.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"

namespace OHOS::Ace::Framework {

struct HomePathInfo {
    std::string name;
    JSRef<JSVal> param;
};

struct NavPathInfoUINode {
    NavPathInfoUINode(const std::string& name, const JSRef<JSVal>& param, RefPtr<NG::UINode>& uiNode, int32_t index)
    {
        this->name = name;
        this->param = param;
        this->uiNode = uiNode;
        this->index = index;
    }
    std::string name;
    JSRef<JSVal> param;
    RefPtr<NG::UINode> uiNode;
    int32_t index = -1;
};

class JSRouteInfo : public NG::RouteInfo {
    DECLARE_ACE_TYPE(JSRouteInfo, NG::RouteInfo)
public:
    JSRouteInfo() = default;
    ~JSRouteInfo() override = default;

    std::string GetName() override;
    void SetName(const std::string& name);
    void SetParam(const JSRef<JSVal>& param);
    JSRef<JSVal> GetParam() const;

protected:
    std::string name_;
    JSRef<JSVal> param_;
};

class JSNavigationStack : public NG::NavigationStack {
    DECLARE_ACE_TYPE(JSNavigationStack, NG::NavigationStack)
public:
    JSNavigationStack() = default;
    ~JSNavigationStack() override = default;

    void SetOnStateChangedCallback(std::function<void()> callback) override
    {
        onStateChangedCallback_ = callback;
    }

    void UpdateStackInfo(const RefPtr<NavigationStack>& newStack) override
    {
        auto newJsStack = AceType::DynamicCast<JSNavigationStack>(newStack);
        if (newJsStack) {
            SetDataSourceObj(newJsStack->GetDataSourceObj());
        }
    }
    void SetDataSourceObj(const JSRef<JSObject>& dataSourceObj);
    const JSRef<JSObject>& GetDataSourceObj();
    void SetNavDestBuilderFunc(const JSRef<JSFunc>& navDestBuilderFunc);
    bool IsEmpty() override;
    void Pop() override;
    void Push(const std::string& name, const RefPtr<NG::RouteInfo>& routeInfo = nullptr) override;
    void Push(const std::string& name, int32_t index) override;
    void PushName(const std::string& name, const JSRef<JSVal>& param);
    void RemoveName(const std::string& name) override;
    void RemoveIndex(int32_t index) override;
    void RemoveInvalidPage(int32_t index);
    void Clear() override;
    int32_t GetReplaceValue() const override;
    void UpdateReplaceValue(int32_t isReplace) const override;
    bool GetAnimatedValue() const override;
    void UpdateAnimatedValue(bool animated) override;
    bool GetDisableAnimation() const override;
    std::vector<std::string> GetAllPathName() override;
    std::vector<int32_t> GetAllPathIndex() override;
    void InitNavPathIndex(const std::vector<std::string>& pathNames) override;
    void SetDestinationIdToJsStack(int32_t index, const std::string& navDestinationId) override;
    bool CreateNodeByIndex(int32_t index, const WeakPtr<NG::UINode>& customNode, RefPtr<NG::UINode>& node) override;
    RefPtr<NG::UINode> CreateNodeByRouteInfo(const RefPtr<NG::RouteInfo>& routeInfo,
        const WeakPtr<NG::UINode>& node) override;
    void SetJSExecutionContext(const JSExecutionContext& context);
    std::string GetRouteParam() const override;
    void OnAttachToParent(RefPtr<NG::NavigationStack> parent) override;
    void OnDetachFromParent() override;
    std::vector<std::string> DumpStackInfo() const override;
    void FireNavigationInterception(bool isBefore, const RefPtr<NG::NavDestinationContext>& from,
        const RefPtr<NG::NavDestinationContext>& to, NG::NavigationOperation operation, bool isAnimated) override;
    void FireNavigationModeChange(NG::NavigationMode mode) override;
    JSRef<JSVal> GetParamByIndex(int32_t index) const;
    int32_t GetJsIndexFromNativeIndex(int32_t index) override;
    void MoveIndexToTop(int32_t index) override;
    void UpdatePathInfoIfNeeded(RefPtr<NG::UINode>& uiNode, int32_t index) override;
    void RecoveryNavigationStack() override;
    bool NeedBuildNewInstance(int32_t index) override;
    void SetNeedBuildNewInstance(int32_t index, bool need) override;
    void SetIsEntryByIndex(int32_t index, bool isEntry) override;

    std::string GetStringifyParamByIndex(int32_t index) const override;
    std::string GetSerializedParamSafely(int32_t index) const override;
    void SetPathArray(const std::vector<NG::NavdestinationRecoveryInfo>& navdestinationsInfo) override;
    bool IsFromRecovery(int32_t index) override;
    void SetFromRecovery(int32_t index, bool fromRecovery) override;
    int32_t GetRecoveredDestinationMode(int32_t index) override;
    void SetRecoveryFromReplaceDestination(int32_t index, bool value) override;
    bool CheckIsReplacedDestination(int32_t index, std::string& replacedName, int32_t& replacedIndex) override;

    bool HasSingletonMoved() override;
    bool IsTopFromSingletonMoved() override;
    void ResetSingletonMoved() override;

    uint64_t GetNavDestinationIdInt(int32_t index) override;
    bool GetIsForceSet(int32_t index) override;
    void ResetIsForceSetFlag(int32_t index) override;
    void PushIntentNavDestination(const std::string& name, const std::string& params, bool needTransition) override;
    void CallPushDestinationInner(const NG::NavdestinationRecoveryInfo& navdestinationsInfo) override;

    void RemoveByIndexes(const std::vector<int32_t>& indexes) override;

    void SetHomePathInfo(HomePathInfo&& pathInfo)
    {
        homePathInfo_ = std::move(pathInfo);
    }
    bool CreateHomeDestination(const WeakPtr<NG::UINode>& customNode, RefPtr<NG::UINode>& node) override;

protected:
    JSRef<JSObject> dataSourceObj_;
    JSRef<JSFunc> navDestBuilderFunc_;
    JSExecutionContext executionContext_;
    std::function<void()> onStateChangedCallback_;

private:
    JSRef<JSArray> GetJsPathArray() const;
    JSRef<JSObject> GetJsPathInfo(int32_t index) const;
    std::string GetNameByIndex(int32_t index);
    JSRef<JSVal> GetOnPopByIndex(int32_t index) const;
    bool GetIsEntryByIndex(int32_t index);
    JSRef<JSObject> CreatePathInfoWithNecessaryProperty(const RefPtr<NG::NavDestinationContext>& context);
    bool GetNavDestinationNodeInUINode(RefPtr<NG::UINode> node, RefPtr<NG::NavDestinationGroupNode>& desNode);
    int32_t GetSize() const override;
    void SetJSParentStack(JSRef<JSVal> parent);
    std::string ConvertParamToString(const JSRef<JSVal>& param, bool needLimit = false) const;
    void ParseJsObject(
        std::unique_ptr<JsonValue>& json, const JSRef<JSObject>& obj, int32_t depthLimit, bool needLimit) const;
    void UpdateOnStateChangedCallback(JSRef<JSObject> obj, std::function<void()> callback);

    int LoadDestination(const std::string& name, const JSRef<JSVal>& param, const WeakPtr<NG::UINode>& customNode,
        RefPtr<NG::UINode>& node, RefPtr<NG::NavDestinationGroupNode>& desNode);
    bool LoadDestinationByBuilder(const std::string& name, const JSRef<JSVal>& param, RefPtr<NG::UINode>& node,
        RefPtr<NG::NavDestinationGroupNode>& desNode);
    bool GetFlagByIndex(int32_t index) const;
    bool CheckAndGetInterceptionFunc(const std::string& name, JSRef<JSFunc>& func);

    bool GetNeedUpdatePathInfo(int32_t index);
    void SetNeedUpdatePathInfo(int32_t index, bool need);
    int32_t ExecuteBuilderByConfig(const std::string& name,
        const WeakPtr<NG::UINode>& customNode, const JSRef<JSVal>& param);

    JSRef<JSArray> GetPathArray();
    JSRef<JSObject> GetPathInfo(int32_t index);

    std::string ErrorToMessage(int32_t errorCode);

    bool RemoveDestinationIfNeeded(const JSRef<JSObject>& param, int32_t errorCode, int32_t index);

    bool ExecutePopCallbackInStack(const JSRef<JSVal>& param);
    bool ExecutePopCallback(const RefPtr<NG::UINode>& uiNode, uint64_t navDestinationId, const JSRef<JSVal>& param);
    void ExecutePopCallbackForHomeNavDestination(const JSRef<JSVal>& param);

private:
    JSRef<JSObject> thisObj_;

    std::optional<HomePathInfo> homePathInfo_;
    WeakPtr<NG::NavDestinationGroupNode> homeDestinationNode_;
};
} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_NAVIGATION_STACK_H
