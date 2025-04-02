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

#include "navigation_context.h"
#include "core/components_ng/pattern/navrouter/navdestination_model_ng.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier::NavigationContext {
void PathInfo::InvokeOnPop(const PopInfo& popInfo)
{
    Ark_PopInfo arkPopInfo {
        .info = ::OHOS::Ace::NG::Converter::ArkValue<Ark_NavPathInfo>(popInfo.info),
        .result = ::OHOS::Ace::NG::Converter::ArkValue<Ark_CustomObject>(popInfo.result),
    };
    onPop_.Invoke(arkPopInfo);
}

int PathStack::GetJsIndexFromNativeIndex(int index)
{
    for (size_t i = 0; i < pathArray_.size(); i++) {
        if (pathArray_[i].index_ == index) {
            return i;
        }
    }
    return -1;
}

void PathStack::InitNavPathIndex(const std::vector<std::string>& pathName)
{
    popArray_.clear();
    for (size_t i = 0; i < pathArray_.size() && i < pathName.size(); i++) {
        if (pathName[i] == pathArray_[i].name_ && isReplace_ != BOTH_ANIM_AND_REPLACE) {
            pathArray_[i].index_ = i;
        }
    }
}

std::vector<int> PathStack::GetAllPathIndex()
{
    std::vector<int> array;
    for (const auto& element : pathArray_) {
        array.push_back(element.index_);
    }
    return array;
}

std::pair<int, std::optional<std::string>> PathStack::FindInPopArray(const std::string& name)
{
    for (int i = popArray_.size() - 1; i >= 0; i--) {
        if (name == popArray_[i].name_) {
            auto info = popArray_[i];
            popArray_.erase(popArray_.begin() + i);
            return {info.index_, info.navDestinationId_};
        }
    }
    return {-1, std::nullopt}; // add new navdestination
}

void PathStack::SetParent(const RefPtr<NavigationStack>& parent)
{
    parentStack_ = parent;
}

RefPtr<NavigationStack> PathStack::GetParent()
{
    return parentStack_;
}

void PathStack::PushName(const std::string& name, const ParamType& param)
{
    PathInfo info(name, param);
    std::tie(info.index_, info.navDestinationId_) = FindInPopArray(name);
    pathArray_.push_back(info);
    isReplace_ = NO_ANIM_NO_REPLACE;
    InvokeOnStateChanged();
}

void PathStack::PushPathByName(const std::string& name,
    const ParamType& param, const OnPopCallback& onPop, std::optional<bool> animated)
{
    PathInfo info(name, param, onPop);
    std::tie(info.index_, info.navDestinationId_) = FindInPopArray(name);
    pathArray_.push_back(info);
    isReplace_ = NO_ANIM_NO_REPLACE;
    animated_ = animated.value_or(DEFAULT_ANIMATED);
    InvokeOnStateChanged();
}

std::pair<LaunchMode, bool> PathStack::ParseNavigationOptions(const std::optional<Options>& param)
{
    if (param) {
        return { param->launchMode.value_or(DEFAULT_LAUNCH_MODE), param->animated.value_or(DEFAULT_ANIMATED) };
    }
    return { DEFAULT_LAUNCH_MODE, DEFAULT_ANIMATED };
}

bool PathStack::PushWithLaunchModeAndAnimated(PathInfo info, LaunchMode launchMode, bool animated)
{
    if (launchMode != LaunchMode::MOVE_TO_TOP_SINGLETON && launchMode != LaunchMode::POP_TO_SINGLETON) {
        return false;
    }
    auto it = FindNameInternal(info.name_);
    if (it == pathArray_.end()) {
        return false;
    }
    it->param_ = info.param_;
    it->onPop_ = info.onPop_;
    it->needUpdate_ = true;
    it->isEntry_ = info.isEntry_;
    if (launchMode == LaunchMode::MOVE_TO_TOP_SINGLETON) {
        MoveToTopInternal(it, animated);
    } else {
        PopToInternal(it, nullptr, animated);
    }
    return true;
}

void PathStack::PushPath(PathInfo info, const std::optional<Options>& optionParam)
{
    auto [launchMode, animated] = ParseNavigationOptions(optionParam);
    auto ret = PushWithLaunchModeAndAnimated(info, launchMode, animated);
    if (ret) {
        return;
    }
    std::tie(info.index_, info.navDestinationId_) = FindInPopArray(info.name_);
    if (launchMode == LaunchMode::NEW_INSTANCE) {
        info.needBuildNewInstance_ = true;
    }
    pathArray_.push_back(info);
    isReplace_ = NO_ANIM_NO_REPLACE;
    animated_ = animated;
    InvokeOnStateChanged();
}

PushDestinationResultType PathStack::PushDestinationByName(const std::string& name,
    const ParamType& param, const OnPopCallback& onPop, std::optional<bool> animated)
{
    PathInfo info(name, param, onPop);
    isReplace_ = NO_ANIM_NO_REPLACE;
    animated_ = animated.value_or(DEFAULT_ANIMATED);
    std::tie(info.index_, info.navDestinationId_) = FindInPopArray(name);
    pathArray_.push_back(info);
    InvokeOnStateChanged();
    return ERROR_CODE_NO_ERROR;
}

PushDestinationResultType PathStack::PushDestination(PathInfo info,
    const std::optional<Options>& optionParam)
{
    auto [launchMode, animated] = ParseNavigationOptions(optionParam);
    auto ret = PushWithLaunchModeAndAnimated(info, launchMode, animated);
    if (ret) {
        return ERROR_CODE_NO_ERROR;
    }
    isReplace_ = NO_ANIM_NO_REPLACE;
    animated_ = animated;
    std::tie(info.index_, info.navDestinationId_) = FindInPopArray(info.name_);
    if (launchMode == LaunchMode::NEW_INSTANCE) {
        info.needBuildNewInstance_ = true;
    }
    pathArray_.push_back(info);
    InvokeOnStateChanged();
    return ERROR_CODE_NO_ERROR;
}

void PathStack::ReplacePath(PathInfo info, const std::optional<Options>& optionParam)
{
    auto [launchMode, animated] = ParseNavigationOptions(optionParam);
    auto it = pathArray_.end();
    if (launchMode == LaunchMode::MOVE_TO_TOP_SINGLETON || launchMode == LaunchMode::POP_TO_SINGLETON) {
        it = FindNameInternal(info.name_);
    }
    if (it != pathArray_.end()) { // is it singleton ?
        it->param_ = info.param_;
        it->onPop_ = info.onPop_;
        it->index_ = -1;
        if (it == (pathArray_.end() - 1)) {
            auto targetInfo = *it;
            it = pathArray_.erase(it);
            if (launchMode == LaunchMode::MOVE_TO_TOP_SINGLETON) {
                pathArray_.pop_back();
            } else {
                pathArray_.erase(it, pathArray_.end());
            }
            pathArray_.push_back(targetInfo);
        }
    } else {
        if (!pathArray_.empty()) {
            pathArray_.pop_back();
        }
        pathArray_.push_back(info);
        pathArray_.back().index_ = -1;
    }
    isReplace_ = BOTH_ANIM_AND_REPLACE;
    animated_ = animated;
    InvokeOnStateChanged();
}

void PathStack::ReplacePathByName(std::string name, const ParamType&  param, const std::optional<bool>& animated)
{
    if (!pathArray_.empty()) {
        pathArray_.pop_back();
    }
    isReplace_ = BOTH_ANIM_AND_REPLACE;
    pathArray_.push_back(PathInfo(name, param));
    pathArray_.back().index_ = -1;
    animated_ = animated.value_or(DEFAULT_ANIMATED);
    InvokeOnStateChanged();
}

void PathStack::SetIsReplace(enum IsReplace value)
{
    isReplace_ = value;
}

void PathStack::SetAnimated(bool value)
{
    animated_ = value;
}

PathInfo PathStack::Pop(const PopResultType& result, const std::optional<bool>& animated)
{
    if (pathArray_.empty()) {
        return PathInfo();
    }
    PathInfo currentPathInfo = pathArray_.back();
    PathInfo pathInfo = pathArray_.back();
    pathArray_.pop_back();
    popArray_.push_back(pathInfo);
    isReplace_ = NO_ANIM_NO_REPLACE;
    if (result) {
        PopInfo popInfo = { currentPathInfo, result };
        currentPathInfo.InvokeOnPop(popInfo);
    }
    animated_ = animated.value_or(DEFAULT_ANIMATED);

    InvokeOnStateChanged();
    return pathInfo;
}

void PathStack::PopTo(const std::string& name, const std::optional<bool>& animated)
{
    PopToName(name, nullptr, animated);
}

int PathStack::PopToName(const std::string& name, const PopResultType& result, const std::optional<bool>& animated)
{
    auto it = FindNameInternal(name);
    if (it == pathArray_.end()) {
        return -1;
    }
    auto idx = std::distance(pathArray_.begin(), it);
    PopToInternal(it, result, animated);
    return idx;
}

void PathStack::PopToIndex(size_t index, const PopResultType& result, const std::optional<bool>& animated)
{
    auto it = std::next(pathArray_.begin(), index);
    if (it >= pathArray_.end()) {
        return;
    }
    PopToInternal(it, result, animated);
}

void PathStack::PopToInternal(std::vector<PathInfo>::iterator it,
    const PopResultType& result, const std::optional<bool>& animated)
{
    auto currentPathInfo = pathArray_.back();
    pathArray_.erase(std::next(it, 1), pathArray_.end());
    isReplace_ = NO_ANIM_NO_REPLACE;

    if (result) {
        PopInfo popInfo = {currentPathInfo, result};
        currentPathInfo.InvokeOnPop(popInfo);
    }
    animated_ = animated.value_or(DEFAULT_ANIMATED);
    InvokeOnStateChanged();
}

int PathStack::MoveToTop(const std::string& name, const std::optional<bool>& animated)
{
    auto it = FindNameInternal(name);
    if (it == pathArray_.end()) {
        return -1;
    }
    int idx = std::distance(pathArray_.begin(), it);
    MoveToTopInternal(it, animated);
    return idx;
}

void PathStack::MoveIndexToTop(size_t index, const std::optional<bool>& animated)
{
    auto it = std::next(pathArray_.begin(), index);
    if (it >= pathArray_.end()) {
        return;
    }
    MoveToTopInternal(it, animated);
}

void PathStack::MoveToTopInternal(std::vector<PathInfo>::iterator it, const std::optional<bool>& animated)
{
    auto info = *it;
    pathArray_.erase(it);
    pathArray_.push_back(info);
    isReplace_ = NO_ANIM_NO_REPLACE;
    animated_ = animated.value_or(DEFAULT_ANIMATED);
    InvokeOnStateChanged();
}

void PathStack::Clear(const std::optional<bool>& animated)
{
    if (pathArray_.empty()) {
        return;
    }
    pathArray_.clear();
    isReplace_ = NO_ANIM_NO_REPLACE;

    animated_ = animated.value_or(DEFAULT_ANIMATED);

    InvokeOnStateChanged();
}

int PathStack::RemoveByIndexes(const std::vector<int>& indexes)
{
    if (indexes.empty()) {
        return 0;
    }
    for (size_t idx = 0; idx < pathArray_.size(); idx++) {
        if (std::find(indexes.begin(), indexes.end(), idx) != indexes.end()) {
            pathArray_[idx].needDelete_ = true;
        }
    }
    auto it = std::remove_if(pathArray_.begin(), pathArray_.end(), [](const auto& item) { return item.needDelete_; });
    auto cnt = std::distance(it, pathArray_.end());
    pathArray_.erase(it, pathArray_.end());
    if (cnt > 0) {
        isReplace_ = NO_ANIM_NO_REPLACE;
        InvokeOnStateChanged();
    }
    return cnt;
}

int PathStack::RemoveByName(const std::string& name)
{
    auto it = std::remove_if(pathArray_.begin(), pathArray_.end(), [&name](const auto& it) {
        return name == it.name_;
    });
    auto cnt = std::distance(it, pathArray_.end());
    pathArray_.erase(it, pathArray_.end());
    if (cnt > 0) {
        isReplace_ = NO_ANIM_NO_REPLACE;
        InvokeOnStateChanged();
    }
    return cnt;
}

bool PathStack::RemoveByNavDestinationId(const std::string& navDestinationId)
{
    auto it = std::remove_if(pathArray_.begin(), pathArray_.end(), [&navDestinationId](const auto& item) {
        return item.navDestinationId_ && *(item.navDestinationId_) == navDestinationId;
    });
    auto cnt = std::distance(it, pathArray_.end());
    pathArray_.erase(it, pathArray_.end());
    if (cnt == 0) {
        return false;
    }
    isReplace_ = NO_ANIM_NO_REPLACE;
    InvokeOnStateChanged();
    return true;
}

void PathStack::RemoveIndex(size_t index)
{
    auto it = std::next(pathArray_.begin(), index);
    if (it >= pathArray_.end()) {
        return;
    }
    pathArray_.erase(it);
    isReplace_ = NO_ANIM_NO_REPLACE;
    InvokeOnStateChanged();
}

void PathStack::RemoveInvalidPage(size_t index)
{
    pathArray_.erase(std::next(pathArray_.begin(), index));
}

std::vector<std::string> PathStack::GetAllPathName()
{
    std::vector<std::string> array;
    for (const auto& element : pathArray_) {
        array.push_back(element.name_);
    }
    return array;
}

std::vector<ParamType> PathStack::GetParamByName(const std::string& name)
{
    std::vector<ParamType> array;
    for (const auto& element : pathArray_) {
        if (element.name_ == name) {
            array.push_back(element.param_);
        }
    }
    return array;
}

std::vector<uint32_t> PathStack::GetIndexByName(const std::string& name)
{
    std::vector<uint32_t> array;
    for (uint32_t index = 0; index < static_cast<uint32_t>(pathArray_.size()); index++) {
        if (pathArray_[index].name_ == name) {
            array.push_back(index);
        }
    }
    return array;
}

size_t PathStack::GetSize() const
{
    return pathArray_.size();
}

void PathStack::DisableAnimation(bool disableAnimation)
{
    disableAllAnimation_ = disableAnimation;
}

void PathStack::SetInterception(InterceptionType interception)
{
    interception_ = interception;
}

// the extra NavigationStack invokes this
void PathStack::SetOnStateChangedCallback(std::function<void()> callback)
{
    onStateChangedCallback_ = callback;
}

void PathStack::InvokeOnStateChanged()
{
    onStateChangedCallback_ ? onStateChangedCallback_() : (void)0;
}

std::vector<PathInfo>::iterator PathStack::FindNameInternal(const std::string& name)
{
    return std::find_if(pathArray_.begin(), pathArray_.end(), [&name](const auto& item) {
        return item.name_ == name;
    });
}

PathInfo* PathStack::GetPathInfo(size_t index)
{
    return index >= pathArray_.size() ? nullptr : (pathArray_.data() + index);
}
const PathInfo* PathStack::GetPathInfo(size_t index) const
{
    return index >= pathArray_.size() ? nullptr : (pathArray_.data() + index);
}

constexpr int32_t INVALID_DESTINATION_MODE = -1;

void NavigationStack::SetDataSourceObj(const RefPtr<PathStack>& dataSourceObj)
{
}

const RefPtr<PathStack>& NavigationStack::GetDataSourceObj()
{
    return dataSourceObj_;
}

void NavigationStack::SetNavDestBuilderFunc(const NavDestBuildCallback& navDestBuilderFunc)
{
    navDestBuilderFunc_ = navDestBuilderFunc;
}

bool NavigationStack::IsEmpty()
{
    return false; // this can't be empty due to PathStack is one of the base classes
}

void NavigationStack::Pop()
{
    PathStack::Pop(PopResultType(), std::nullopt);
}

void NavigationStack::Push(const std::string& name, const RefPtr<NG::RouteInfo>& routeInfo)
{
    ParamType param = nullptr;
    if (routeInfo) {
        // the inherited from RouteInfo class required here for store the external specific type parameter
        auto extRouteInfo = AceType::DynamicCast<RouteInfo>(routeInfo);
        CHECK_NULL_VOID(extRouteInfo);
        param = ParamType(); // getting of the external specific type parameter may be here
    } else {
        auto params = PathStack::GetParamByName(name);
        param = !params.empty() ? params.front() : ParamType();
    }
    this->PathStack::PushName(name, param);
}

void NavigationStack::Push(const std::string& name, int32_t index)
{
    auto param = GetParamByIndex(index);
    PathStack::PushName(name, param);
}

void NavigationStack::RemoveName(const std::string& name)
{
    PathStack::RemoveByName(name);
}

void NavigationStack::RemoveIndex(int32_t index)
{
    PathStack::RemoveIndex(index);
}

void NavigationStack::Clear()
{
    PathStack::Clear(std::nullopt);
}

std::vector<std::string> NavigationStack::GetAllPathName()
{
    return PathStack::GetAllPathName();
}

std::vector<int32_t> NavigationStack::GetAllPathIndex()
{
    return PathStack::GetAllPathIndex();
}

void NavigationStack::InitNavPathIndex(const std::vector<std::string>& pathNames)
{
    PathStack::InitNavPathIndex(pathNames);
}

void NavigationStack::SetDestinationIdToJsStack(int32_t index, const std::string& navDestinationId)
{
    if (auto pathInfo = PathStack::GetPathInfo(index); pathInfo) {
        pathInfo->navDestinationId_ = navDestinationId;
    }
}

bool NavigationStack::CreateNodeByIndex(int32_t index, const WeakPtr<NG::UINode>& customNode,
    RefPtr<NG::UINode>& node)
{
    auto pathInfo = PathStack::GetPathInfo(index);
    CHECK_NULL_RETURN(pathInfo, false);
    auto name = pathInfo->name_;
    auto param = pathInfo->param_;
    auto isEntry = pathInfo->isEntry_;
    RefPtr<NG::UINode> targetNode;
    RefPtr<NG::NavDestinationGroupNode> desNode;
    int32_t errorCode = ERROR_CODE_DESTINATION_NOT_FOUND;
    for (auto iter = nodes_.begin(); iter != nodes_.end(); iter++) {
        if (iter->first == index) {
            targetNode = iter->second;
            break;
        }
    }
    if (GetNavDestinationNodeInUINode(targetNode, desNode)) {
        errorCode = ERROR_CODE_NO_ERROR;
    }
    if (errorCode != ERROR_CODE_NO_ERROR) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "can't find target destination by index, create empty node");
        // node = AceType::DynamicCast<NG::UINode>(NavDestinationModelNG::CreateFrameNode(0));
        return true;
    }
    node = targetNode;
    CHECK_NULL_RETURN(desNode, false);
    auto pattern = AceType::DynamicCast<NG::NavDestinationPattern>(desNode->GetPattern());
    if (pattern) {
        pattern->SetName(name);
        pattern->SetIndex(index);
        TAG_LOGD(AceLogTag::ACE_NAVIGATION, "create destination node, isEntry %{public}d", isEntry);
        auto pathInfoData = AceType::MakeRefPtr<NavPathInfo>(name, isEntry); // `param` and `onPop` data may be added
        pattern->SetNavPathInfo(pathInfoData);
        pattern->SetNavigationStack(WeakClaim(this));
    }
    return true;
}

RefPtr<NG::UINode> NavigationStack::CreateNodeByRouteInfo(const RefPtr<NG::RouteInfo>& routeInfo,
    const WeakPtr<NG::UINode>& customNode)
{
    // the inherited from RouteInfo class required here for store the external specific type parameter
    auto extRouteInfo = AceType::DynamicCast<RouteInfo>(routeInfo);
    if (!extRouteInfo) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "route info is invalid");
        // return AceType::DynamicCast<NG::UINode>(NavDestinationModelNG::CreateFrameNode(0));
    }
    auto name = extRouteInfo->GetName();
    auto param = ParamType(); // getting of the external specific type parameter may be here
    RefPtr<NG::UINode> node;
    RefPtr<NG::NavDestinationGroupNode> desNode;
    int32_t errorCode = LoadDestination(name, param, customNode, node, desNode);
    if (errorCode == ERROR_CODE_NO_ERROR && desNode) {
        auto pattern = AceType::DynamicCast<NG::NavDestinationPattern>(desNode->GetPattern());
        if (pattern) {
            auto pathInfo = AceType::MakeRefPtr<NavPathInfo>(name); // `param`data may be added
            pattern->SetNavPathInfo(pathInfo);
            pattern->SetName(name);
            pattern->SetNavigationStack(WeakClaim(this));
        }
        return node;
    }
    return nullptr;
    // return AceType::DynamicCast<NG::UINode>(NavDestinationModelNG::CreateFrameNode(0));
}

std::string NavigationStack::GetNameByIndex(int32_t index) const
{
    auto pathInfo = PathStack::GetPathInfo(index);
    return pathInfo ? pathInfo->name_ : "";
}
ParamType NavigationStack::GetParamByIndex(int32_t index) const
{
    auto pathInfo = PathStack::GetPathInfo(index);
    return pathInfo ? pathInfo->param_ : ParamType();
}
OnPopCallback NavigationStack::GetOnPopByIndex(int32_t index) const
{
    auto pathInfo = PathStack::GetPathInfo(index);
    return pathInfo ? pathInfo->onPop_ : OnPopCallback();
}
bool NavigationStack::GetIsEntryByIndex(int32_t index)
{
    auto pathInfo = PathStack::GetPathInfo(index);
    return pathInfo && pathInfo->isEntry_;
}

void NavigationStack::SetIsEntryByIndex(int32_t index, bool isEntry)
{
    if (auto pathInfo = PathStack::GetPathInfo(index); pathInfo) {
        pathInfo->isEntry_ = isEntry;
    }
}

int32_t NavigationStack::GetReplaceValue() const
{
    return PathStack::isReplace_;
}

void NavigationStack::UpdateReplaceValue(int32_t replaceValue) const
{
    const_cast<NavigationStack *>(this)->SetIsReplace(replaceValue);
}

std::string NavigationStack::GetRouteParam() const
{
    auto size = PathStack::GetSize();
    if (size > 0) {
        auto param = GetParamByIndex(size - 1);
        return ConvertParamToString(param, true);
    }
    return "";
}

std::string NavigationStack::ConvertParamToString(const ParamType& param, bool needLimit) const
{
    return {};
}
bool NavigationStack::GetAnimatedValue() const
{
    return PathStack::animated_;
}

void NavigationStack::UpdateAnimatedValue(bool animated)
{
    PathStack::SetAnimated(animated);
}

bool NavigationStack::GetDisableAnimation() const
{
    return PathStack::disableAllAnimation_;
}

void NavigationStack::OnAttachToParent(RefPtr<NG::NavigationStack> parent)
{
    auto stack = AceType::DynamicCast<NavigationStack>(parent);
    PathStack::SetParent(stack);
}

void NavigationStack::OnDetachFromParent()
{
    PathStack::SetParent(nullptr);
}

void NavigationStack::RemoveInvalidPage(int32_t index)
{
    PathStack::RemoveInvalidPage(index);
}

std::vector<std::string> NavigationStack::DumpStackInfo() const
{
    std::vector<std::string> dumpInfos;
    for (size_t i = 0; i < navPathList_.size(); ++i) {
        const auto& name = navPathList_[i].first;
        std::string info = "[" + std::to_string(i) + "]{ name: \"" + name + "\"";
        std::string param = ConvertParamToString(GetParamByIndex(i));
        if (param.length() > 0) {
            info += ", param: " + param;
        }
        info += " }";
        dumpInfos.push_back(std::move(info));
    }
    return dumpInfos;
}

void NavigationStack::FireNavigationInterception(bool isBefore, const RefPtr<NG::NavDestinationContext>& from,
    const RefPtr<NG::NavDestinationContext>& to, NG::NavigationOperation operation, bool isAnimated)
{
    APP_LOGE("NavigationContext::NavigationStack::FireNavigationInterception - not implemented");
}

void NavigationStack::FireNavigationModeChange(NG::NavigationMode mode)
{
    APP_LOGE("NavigationContext::NavigationStack::FireNavigationModeChange - not implemented");
}

int32_t NavigationStack::LoadDestination(const std::string& name, const ParamType& param,
    const WeakPtr<NG::UINode>& customNode, RefPtr<NG::UINode>& node,
    RefPtr<NG::NavDestinationGroupNode>& desNode)
{
    // execute navdestination attribute builder
    if (LoadDestinationByBuilder(name, param, node, desNode)) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "load destination by buildermap");
        return ERROR_CODE_NO_ERROR;
    }
    TAG_LOGE(AceLogTag::ACE_NAVIGATION, "NavigationContext::NavigationStack::LoadDestination"
        ", loading by URL not implemneted");
    APP_LOGE("NavigationContext::NavigationStack::LoadDestination"
        ", loading by URL not implemneted");
    return ERROR_CODE_DESTINATION_NOT_FOUND;
}

bool NavigationStack::LoadDestinationByBuilder(const std::string& name, const ParamType& param,
    RefPtr<NG::UINode>& node, RefPtr<NG::NavDestinationGroupNode>& desNode)
{
    if (!navDestBuilderFunc_.IsValid()) {
        TAG_LOGW(AceLogTag::ACE_NAVIGATION, "Builder function is empty");
        return false;
    }
    auto arkName = Converter::ArkValue<Ark_String>(name);
    auto arkParam = Converter::ArkValue<Ark_CustomObject>(param);
    navDestBuilderFunc_.Invoke(arkName, arkParam);
    TAG_LOGE(AceLogTag::ACE_NAVIGATION, "NavigationContext::NavigationStack::LoadDestination"
        ", No way to obtain the FrameNode in result of the build func execution.");
    APP_LOGE("NavigationContext::NavigationStack::LoadDestination"
        ", No way to obtain the FrameNode in result of the build func execution.");
    RefPtr<NG::UINode> resultNode = nullptr;
    node = resultNode;
    return GetNavDestinationNodeInUINode(node, desNode);
}

bool NavigationStack::GetNavDestinationNodeInUINode(
    RefPtr<NG::UINode> node, RefPtr<NG::NavDestinationGroupNode>& desNode)
{
    RefPtr<NG::CustomNode> customNode;
    while (node) {
        if (node->GetTag() == V2::JS_VIEW_ETS_TAG) {
            customNode = AceType::DynamicCast<NG::CustomNode>(node);
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "render current custom node: %{public}s",
                customNode->GetCustomTag().c_str());
            // record parent navigationNode before customNode is rendered in case of navDestinationNode
            auto navigationNode = GetNavigationNode();
            customNode->SetNavigationNode(navigationNode);
            // render, and find deep further
            customNode->Render();
        } else if (node->GetTag() == V2::NAVDESTINATION_VIEW_ETS_TAG) {
            desNode = AceType::DynamicCast<NG::NavDestinationGroupNode>(node);
            if (desNode) {
                desNode->SetNavDestinationCustomNode(AceType::WeakClaim(AceType::RawPtr(customNode)));
            }
            return true;
        }
        auto children = node->GetChildren();
        if (children.size() != 1) {
            TAG_LOGI(AceLogTag::ACE_NAVIGATION,
                "router map is invalid, child size is not one: %{public}zu", children.size());
        }
        node = children.front();
    }
    return false;
}

int32_t NavigationStack::GetJsIndexFromNativeIndex(int32_t index)
{
    return PathStack::GetJsIndexFromNativeIndex(index);
}

void NavigationStack::MoveIndexToTop(int32_t index)
{
    PathStack::MoveIndexToTop(index, std::nullopt);
}

void NavigationStack::UpdatePathInfoIfNeeded(RefPtr<NG::UINode>& uiNode, int32_t index)
{
    auto pathInfo = PathStack::GetPathInfo(index);
    CHECK_NULL_VOID(pathInfo);
    bool needUpdate = pathInfo->needUpdate_;
    if (!pathInfo->needUpdate_) {
        return;
    }
    pathInfo->needUpdate_ = false;

    RefPtr<NG::NavDestinationGroupNode> desNode;
    if (!GetNavDestinationNodeInUINode(uiNode, desNode)) {
        return;
    }
    auto pattern = AceType::DynamicCast<NavDestinationPattern>(desNode->GetPattern());
    if (!pattern) {
        return;
    }
    // temp stub WITHOUT `param` and `onPop` from pathInfo
    auto pathInfoData = AceType::MakeRefPtr<NavPathInfo>(pathInfo->name_, pathInfo->isEntry_);
    pattern->SetNavPathInfo(pathInfoData);
}

bool NavigationStack::GetNeedUpdatePathInfo(int32_t index)
{
    auto pathInfo = PathStack::GetPathInfo(index);
    return pathInfo && pathInfo->needUpdate_;
}

void NavigationStack::SetNeedUpdatePathInfo(int32_t index, bool need)
{
    if (auto pathInfo = PathStack::GetPathInfo(index); pathInfo) {
        pathInfo->needUpdate_ = need;
    }
}

void NavigationStack::RecoveryNavigationStack()
{
    APP_LOGE("NavigationContext::NavigationStack::FireNavigationModeChange - not implemented");
}

bool NavigationStack::NeedBuildNewInstance(int32_t index)
{
    auto pathInfo = PathStack::GetPathInfo(index);
    return pathInfo && pathInfo->needBuildNewInstance_;
}

void NavigationStack::SetNeedBuildNewInstance(int32_t index, bool need)
{
    if (auto pathInfo = PathStack::GetPathInfo(index); pathInfo) {
        pathInfo->needBuildNewInstance_ = need;
    }
}

std::string NavigationStack::GetStringifyParamByIndex(int32_t index) const
{
    APP_LOGE("NavigationContext::NavigationStack::GetStringifyParamByIndex - not implemented");
    return std::string();
}

void NavigationStack::SetPathArray(const std::vector<NG::NavdestinationRecoveryInfo>& navdestinationsInfo)
{
    APP_LOGE("NavigationContext::NavigationStack::SetPathArray - not implemented");
}

bool NavigationStack::IsFromRecovery(int32_t index)
{
    auto pathInfo = PathStack::GetPathInfo(index);
    return pathInfo && pathInfo->fromRecovery_;
}

void NavigationStack::SetFromRecovery(int32_t index, bool fromRecovery)
{
    if (auto pathInfo = PathStack::GetPathInfo(index); pathInfo) {
        pathInfo->fromRecovery_ = fromRecovery;
    }
}

int32_t NavigationStack::GetRecoveredDestinationMode(int32_t index)
{
    auto pathInfo = PathStack::GetPathInfo(index);
    return pathInfo ? pathInfo->mode_ : INVALID_DESTINATION_MODE;
}
} // namespace OHOS::Ace::NG::GeneratedModifier::NavigationContext
