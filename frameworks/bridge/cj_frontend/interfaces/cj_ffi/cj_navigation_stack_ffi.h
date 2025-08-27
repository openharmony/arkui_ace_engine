/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef OHOS_ACE_FRAMEWORK_CJ_NAVIGATION_STACK_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_NAVIGATION_STACK_FFI_H

#include <functional>
#include <stdint.h>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_nav_path_stack_ffi.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/navigation/navigation_stack.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"

namespace OHOS::Ace::Framework {

class CJRouteInfo : public NG::RouteInfo {
    DECLARE_ACE_TYPE(CJRouteInfo, NG::RouteInfo);
public:
    CJRouteInfo() = default;
    ~CJRouteInfo() override = default;

    std::string GetName() override;
    void SetName(const std::string& name);
    void SetParam(const std::string& param);
    std::string GetParam() const;

protected:
    std::string name_;
    std::string param_;
};

class CJNavigationStack : public NG::NavigationStack {
    DECLARE_ACE_TYPE(CJNavigationStack, NG::NavigationStack);
public:
    CJNavigationStack() = default;
    ~CJNavigationStack() override = default;

    void SetOnStateChangedCallback(std::function<void()> callback) override
    {
        onStateChangedCallback_ = callback;
    }

    void UpdateStackInfo(const RefPtr<NavigationStack>& newStack) override
    {
        auto newCjStack = AceType::DynamicCast<CJNavigationStack>(newStack);
        if (newCjStack) {
            SetDataSourceObj(newCjStack->GetDataSourceObjId());
        }
    }

    void SetDataSourceObj(int64_t dataSourceObjId);
    sptr<CJNavPathStack> GetDataSourceObj();
    int64_t GetDataSourceObjId();
    void SetNavDestBuilderFunc(std::function<void(std::string name, std::string param)> navDestBuilderFunc);
    CJNavPathInfo CreatePathInfoWithNecessaryProperty(const RefPtr<NG::NavDestinationContext>& context);
    bool IsEmpty() override;
    void Pop() override;
    void Push(const std::string& name, const RefPtr<NG::RouteInfo>& routeInfo = nullptr) override;
    void Push(const std::string& name, int32_t index) override;
    void RemoveName(const std::string& name) override;
    void RemoveIndex(int32_t index) override;
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
    RefPtr<NG::UINode> CreateNodeByRouteInfo(
        const RefPtr<NG::RouteInfo>& routeInfo, const WeakPtr<NG::UINode>& node) override;
    std::string GetRouteParam() const override;
    void OnAttachToParent(RefPtr<NG::NavigationStack> parent) override;
    void OnDetachFromParent() override;
    std::vector<std::string> DumpStackInfo() const override;
    void FireNavigationInterception(bool isBefore, const RefPtr<NG::NavDestinationContext>& from,
        const RefPtr<NG::NavDestinationContext>& to, NG::NavigationOperation operation, bool isAnimated) override;
    void FireNavigationModeChange(NG::NavigationMode mode) override;
    int32_t GetJsIndexFromNativeIndex(int32_t index) override;
    void MoveIndexToTop(int32_t index) override;
    void UpdatePathInfoIfNeeded(RefPtr<NG::UINode>& uiNode, int32_t index) override;
    void RecoveryNavigationStack() override;
    bool NeedBuildNewInstance(int32_t index) override;
    void SetNeedBuildNewInstance(int32_t index, bool need) override;
    void SetIsEntryByIndex(int32_t index, bool isEntry) override;
    std::string GetStringifyParamByIndex(int32_t index) const override;
    void SetPathArray(const std::vector<NG::NavdestinationRecoveryInfo>& navdestinationsInfo) override;
    bool IsFromRecovery(int32_t index) override;
    void SetFromRecovery(int32_t index, bool fromRecovery) override;
    int32_t GetRecoveredDestinationMode(int32_t index) override;
    void SetRecoveryFromReplaceDestination(int32_t index, bool value) override;
    bool CheckIsReplacedDestination(int32_t index, std::string& replacedName, int32_t& replacedIndex) override;

protected:
    int64_t dataSourceObjId_;
    sptr<CJNavPathStack> dataSourceObj_;
    std::function<void(std::string name, std::string param)> navDestBuilderFunc_;
    std::function<void()> onStateChangedCallback_;

private:
    void UpdateOnStateChangedCallback(sptr<CJNavPathStack> obj, std::function<void()> callback);
    CJNavPathInfo* GetPathInfo(int32_t index);
    std::vector<CJNavPathInfo> GetPathArray();
    int32_t LoadDestination(const std::string& name, const std::string& param, const WeakPtr<NG::UINode>& customNode,
        RefPtr<NG::UINode>& node, RefPtr<NG::NavDestinationGroupNode>& desNode);
    bool GetNavDestinationNodeInUINode(RefPtr<NG::UINode> node, RefPtr<NG::NavDestinationGroupNode>& desNode);
    int32_t GetSize() const override;
    void SetCJParentStack(CJNavPathStack* parent);
};
} // namespace OHOS::Ace::Framework

#endif // OHOS_ACE_FRAMEWORK_CJ_NAVIGATION_STACK_FFI_H
