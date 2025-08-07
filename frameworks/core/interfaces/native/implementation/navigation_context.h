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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_NAVIGATION_CONTEXT_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_NAVIGATION_CONTEXT_H

#include "base/error/error_code.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navigation/navigation_stack.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/interfaces/native/utility/callback_helper.h"

namespace OHOS::Ace::NG::GeneratedModifier::NavigationContext {

class ExternalDataKeeper : public virtual Referenced {
public:
    ExternalDataKeeper() = default;
    ~ExternalDataKeeper() override = default;
    explicit ExternalDataKeeper(const Ark_Object& data): data_(data) {}
    Ark_Object data_;
    ACE_DISALLOW_COPY_AND_MOVE(ExternalDataKeeper);
};
using ExternalData = RefPtr<ExternalDataKeeper>;
using OnPopCallback = CallbackHelper<Callback_PopInfo_Void>;
using NavDestBuildCallback = CallbackHelper<Callback_String_Opt_Object_Void>;

struct Interception {
    std::function<void(NG::NavigationMode)> modeChange;
    std::function<void(const RefPtr<NG::NavDestinationContext>&,
        const RefPtr<NG::NavDestinationContext>&, NG::NavigationOperation, bool)> willShow;
    std::function<void(const RefPtr<NG::NavDestinationContext>&,
        const RefPtr<NG::NavDestinationContext>&, NG::NavigationOperation, bool)> didShow;
};
using InterceptionType = struct Interception *;

using ParamType = ExternalData;

struct PopInfo;

 // this correlates to OHOS::Ace::NG::NavPathInfo by sense
class PathInfo {
public:
    explicit PathInfo(const std::string& name) : PathInfo(name, nullptr) {}
    PathInfo(std::string name, const ParamType& param, OnPopCallback onPop = OnPopCallback(),
        bool isEntry = false) : name_(name), param_(param), onPop_(onPop), index_(-1), needUpdate_(false),
        needBuildNewInstance_(false), navDestinationId_(""), isEntry_(isEntry),
        fromRecovery_(false), mode_(0), needDelete_(false) {}
    PathInfo() : name_(), param_(), onPop_(OnPopCallback()), index_(-1), needUpdate_(false),
        needBuildNewInstance_(false), navDestinationId_(""), isEntry_(false),
        fromRecovery_(false), mode_(0), needDelete_(false) {}

    std::string name_;
    ParamType param_;
    OnPopCallback onPop_;
    int index_;
    bool needUpdate_;
    bool needBuildNewInstance_;
    std::optional<std::string> navDestinationId_;
    bool isEntry_;
    bool fromRecovery_;
    int32_t mode_;
    bool needDelete_;

    void InvokeOnPop(const PopInfo& popInfo);
};

using PopResultType = ExternalData;

struct PopInfo {
    PathInfo info;
    PopResultType result;
};

using PushDestinationResultType = int32_t;

class NavigationStack;

constexpr bool DEFAULT_ANIMATED = true;
constexpr LaunchMode DEFAULT_LAUNCH_MODE = LaunchMode::STANDARD;

// this duplicates the functionality of JS NavPathStack class
// (frameworks/bridge/declarative_frontend/engine/jsEnumStyle.js)
class PathStack : public virtual Referenced {
public:
    enum IsReplace {
        NO_ANIM_NO_REPLACE = 0, // replace value 0: don't do anything;
        BOTH_ANIM_AND_REPLACE = 1, // 1: replace value and do replace animation;
        ANIM_NO_REPLACE = 2 // 2: don't replace value but do replace animation
    };

    PathStack() = default;
    ~PathStack() override = default;

    int GetJsIndexFromNativeIndex(int index);
    void InitNavPathIndex(const std::vector<std::string>& pathName);
    std::vector<int> GetAllPathIndex();
    std::pair<int, std::optional<std::string>> FindInPopArray(const PathInfo& info);
    void SetParent(const RefPtr<NavigationStack>& parent);
    RefPtr<NavigationStack> GetParent();
    void PushName(const std::string& name, const ParamType& param);
    void PushPathByName(const std::string& name,
        const ParamType& param, const OnPopCallback& onPop, std::optional<bool> animated);
    std::pair<LaunchMode, bool> ParseNavigationOptions(const std::optional<NavigationOptions>& param);
    bool PushWithLaunchModeAndAnimated(PathInfo info, LaunchMode launchMode, bool animated);
    void PushPath(PathInfo info, const std::optional<NavigationOptions>& optionParam);
    PushDestinationResultType PushDestinationByName(const std::string& name,
        const ParamType& param, const OnPopCallback& onPop, std::optional<bool> animated);
    PushDestinationResultType PushDestination(PathInfo info,
        const std::optional<NavigationOptions>& optionParam);
    void ReplacePath(PathInfo info, const std::optional<NavigationOptions>& optionParam);
    void ReplacePathByName(std::string name, const ParamType&  param, const std::optional<bool>& animated);
    void SetIsReplace(enum IsReplace value);
    void SetAnimated(bool value);
    PathInfo Pop(bool isAnimated);
    void PopTo(const std::string& name, const std::optional<bool>& animated);
    int PopToName(const std::string& name, const std::optional<bool>& animated);
    void PopToIndex(size_t index, const std::optional<bool>& animated);
    void PopToInternal(std::vector<PathInfo>::iterator it, const std::optional<bool>& animated);
    int MoveToTop(const std::string& name, const std::optional<bool>& animated);
    void MoveIndexToTop(size_t index, const std::optional<bool>& animated);
    void MoveToTopInternal(std::vector<PathInfo>::iterator it, const std::optional<bool>& animated);
    void Clear(const std::optional<bool>& animated);
    int RemoveInfoByIndexes(const std::vector<int>& indexes);
    int RemoveByName(const std::string& name);
    bool RemoveByNavDestinationId(const std::string& navDestinationId);
    void RemoveIndex(size_t index);
    void RemoveInvalidPage(size_t index);
    std::vector<std::string> GetAllPathName();
    std::vector<ParamType> GetParamByName(const std::string& name);
    std::vector<size_t> GetIndexByName(const std::string& name);
    size_t Size() const;
    void DisableAnimation(bool disableAnimation);
    void SetInterception(InterceptionType interception);
    InterceptionType GetInterception()
    {
        return interception_;
    }
    PathInfo* GetPathInfo(size_t index);
    std::vector<std::string> GetIdByName(const std::string& name);
    void SetOnPopCallback(std::function<void(const std::string)> popCallback)
    {
        onPopCallback_ = popCallback;
    }
protected:
    std::vector<PathInfo> pathArray_;
    enum IsReplace isReplace_ = NO_ANIM_NO_REPLACE;
    bool disableAllAnimation_ = false; // control all navigation transition animations.
    bool animated_ = DEFAULT_ANIMATED; // control a single navigation transition animation.
    RefPtr<NavigationStack> parentStack_ = nullptr;
    std::vector<PathInfo> popArray_ = {};
    InterceptionType interception_ = nullptr;
    std::function<void()> onStateChangedCallback_;
    std::function<void(const std::string)> onPopCallback_;
    void SetOnStateChangedCallback(std::function<void()> callback); // the extra NavigationStack invokes this
    void InvokeOnStateChanged();
    std::vector<PathInfo>::iterator FindNameInternal(const std::string& name);
    const PathInfo* GetPathInfo(size_t index) const;
};

// this repeats the functionality of JSNavigationStack, interacts with PathStack
class NavigationStack : public ::OHOS::Ace::NG::NavigationStack, public PathStack {
    DECLARE_ACE_TYPE(NavigationStack, ::OHOS::Ace::NG::NavigationStack);
public:
    void SetOnStateChangedCallback(std::function<void()> callback) override
    {
        PathStack::SetOnStateChangedCallback(callback);
    }

    void UpdateStackInfo(const RefPtr<::OHOS::Ace::NG::NavigationStack>& newStack) override
    {
        auto stack = AceType::DynamicCast<NavigationStack>(newStack);
        if (stack) {
            SetDataSourceObj(stack->GetDataSourceObj());
        }
    }
    void SetDataSourceObj(const RefPtr<PathStack>& dataSourceObj);
    const RefPtr<PathStack>& GetDataSourceObj();

    void SetNavDestBuilderFunc(const NavDestBuildCallback& navDestBuilderFunc);

    bool IsEmpty() override;
    void Pop() override;
    void Push(const std::string& name, const RefPtr<NG::RouteInfo>& routeInfo = nullptr) override;
    void Push(const std::string& name, int32_t index) override;
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
    void AddCustomNode(int32_t index, const RefPtr<NG::UINode>& node)
    {
        nodes_.insert(std::pair<int32_t, RefPtr<NG::UINode>>(index, node));
    }

    void ClearNodeList()
    {
        nodes_.clear();
    }
protected:
    std::map<int32_t, RefPtr<NG::UINode>> nodes_;
    RefPtr<PathStack> dataSourceObj_;
    NavDestBuildCallback navDestBuilderFunc_;
    std::function<void()> onStateChangedCallback_;

private:
    void SetIsReplace(int32_t value)
    {
        PathStack::SetIsReplace(static_cast<PathStack::IsReplace>(value));
    }
    int32_t GetSize() const override;
    std::string GetNameByIndex(int32_t index) const;
    ParamType GetParamByIndex(int32_t index) const;
    OnPopCallback GetOnPopByIndex(int32_t index) const;
    bool GetIsEntryByIndex(int32_t index);
    std::string ConvertParamToString(const ParamType& param, bool needLimit = false) const;
    int LoadDestination(const std::string& name, const ParamType& param, const WeakPtr<NG::UINode>& customNode,
        RefPtr<NG::UINode>& node, RefPtr<NG::NavDestinationGroupNode>& desNode);
    bool LoadDestinationByBuilder(const std::string& name, const ParamType& param, RefPtr<NG::UINode>& node,
        RefPtr<NG::NavDestinationGroupNode>& desNode);
    bool GetNavDestinationNodeInUINode(RefPtr<NG::UINode> node, RefPtr<NG::NavDestinationGroupNode>& desNode);
    bool GetNeedUpdatePathInfo(int32_t index);
    void SetNeedUpdatePathInfo(int32_t index, bool need);
};
} // namespace OHOS::Ace::NG::GeneratedModifier::NavigationContext

namespace OHOS::Ace::NG::Converter {
void AssignArkValue(Ark_Object& dst, const GeneratedModifier::NavigationContext::ExternalData& src);
void AssignArkValue(Ark_NavPathInfo& dst, const GeneratedModifier::NavigationContext::PathInfo& src);
template<> GeneratedModifier::NavigationContext::ExternalData Convert(const Ark_Object& src);
template<> GeneratedModifier::NavigationContext::PathInfo Convert(const Ark_NavPathInfo& src);
} // namespace OHOS::Ace::NG::Converter
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_NAVIGATION_CONTEXT_H
