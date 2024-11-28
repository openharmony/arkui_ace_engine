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
#include "arkoala_api_generated.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"

namespace OHOS::Ace::NG::GeneratedModifier::NavigationContext {

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
        if (pathName[i] == pathArray_[i].name_ && isReplace_ != 1) {
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
            popArray_.erase(std::next(pathArray_.begin(), i));
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

void PathStack::PushName(const std::string& name, const ParamType& param) {
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
    bool isRegular = true;
    if (launchMode == LaunchMode::MOVE_TO_TOP_SINGLETON || launchMode == LaunchMode::POP_TO_SINGLETON) {
        auto it = FindNameInternal(info.name_);
        if (it != pathArray_.end()) {
            isRegular = false;
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
        }
    }
    if (isRegular) {
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
    pathArray_.erase(it, pathArray_.end());
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

std::vector<size_t> PathStack::GetIndexByName(const std::string& name)
{
    std::vector<size_t> array;
    for (size_t index = 0; index < pathArray_.size(); index++) {
        if (pathArray_[index].name_ == name) {
            array.push_back(index);
        }
    }
    return array;
}

size_t PathStack::Size() const
{
    return pathArray_.size();
}

void PathStack::DisableAnimation(bool disableAnimation)
{
    disableAllAnimation_ = disableAnimation;
}

void PathStack::SetInterception(Interception interception)
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
/*
    // clean callback from old JSNavPathStack
    CHECK_NULL_VOID(dataSourceObj_);
    dataSourceObj_->SetOnStateChangedCallback(nullptr);
    dataSourceObj_ = dataSourceObj;
    // add callback to new JSNavPathStack
    RemoveStack();
    CHECK_NULL_VOID(dataSourceObj_);
    dataSourceObj_->SetOnStateChangedCallback(onStateChangedCallback_);
*/
}

const RefPtr<PathStack>& NavigationStack::GetDataSourceObj()
{
    return dataSourceObj_;
}

/*
void NavigationStack::SetNavDestBuilderFunc(const JSRef<JSFunc>& navDestBuilderFunc)
{
    navDestBuilderFunc_ = navDestBuilderFunc;
}
*/
bool NavigationStack::IsEmpty()
{
    return dataSourceObj_ != nullptr;
    // return dataSourceObj_->IsEmpty();
}

void NavigationStack::Pop()
{
    PathStack::Pop(PopResultType(), std::nullopt);
/*     JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    auto popFunc = dataSourceObj_->GetProperty("pop");
    if (!popFunc->IsFunction()) {
        return;
    }
    auto func = JSRef<JSFunc>::Cast(popFunc);
    JSRef<JSVal>::Cast(func->Call(dataSourceObj_));
*/
}

void NavigationStack::Push(const std::string& name, const RefPtr<NG::RouteInfo>& routeInfo)
{
    ExternalData param = nullptr;
    if (routeInfo) {
        // auto jsRouteInfo = AceType::DynamicCast<JSRouteInfo>(routeInfo);
        // param = jsRouteInfo->GetParam();
    } else {
        auto params = PathStack::GetParamByName(name);
        param = !params.empty() ? params.front() : ExternalData();
    }
    this->PathStack::PushName(name, param);

/*     // obtain param from NavPathStack
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    JSRef<JSVal> param;
    if (routeInfo) {
        auto jsRouteInfo = AceType::DynamicCast<JSRouteInfo>(routeInfo);
        param = jsRouteInfo->GetParam();
    } else {
        auto getParamByNameFunc = dataSourceObj_->GetProperty("getParamByName");
        if (getParamByNameFunc->IsFunction()) {
            auto getFunc = JSRef<JSFunc>::Cast(getParamByNameFunc);
            auto funcArray = getFunc->Call(dataSourceObj_);
            if (funcArray->IsArray()) {
                auto result = JSRef<JSArray>::Cast(funcArray);
                param = result->GetValueAt(0);
            }
        }
    }
    auto pushNameFunc = dataSourceObj_->GetProperty("pushName");
    if (pushNameFunc->IsFunction()) {
        auto pushFunc = JSRef<JSFunc>::Cast(pushNameFunc);
        JSRef<JSVal> params[2];
        params[0] = JSRef<JSVal>::Make(ToJSValue(name));
        params[1] = param;
        pushFunc->Call(dataSourceObj_, 2, params);
    }
*/
}

/*void NavigationStack::PushName(const std::string& name, const JSRef<JSVal>& param)
{
     // obtain param from routeInfo
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    auto pushNameFunc = dataSourceObj_->GetProperty("pushName");
    if (pushNameFunc->IsFunction()) {
        auto pushFunc = JSRef<JSFunc>::Cast(pushNameFunc);
        JSRef<JSVal> params[2];
        params[0] = JSRef<JSVal>::Make(ToJSValue(name));
        params[1] = param;
        pushFunc->Call(dataSourceObj_, 2, params);
    }
}
*/
void NavigationStack::Push(const std::string& name, int32_t index)
{
    auto param = GetParamByIndex(index);
    PathStack::PushName(name, param);

/*     JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    auto getParamByIndexFunc = dataSourceObj_->GetProperty("getParamByIndex");
    if (!getParamByIndexFunc->IsFunction()) {
        return ;
    }
    auto pushNameFunc = dataSourceObj_->GetProperty("pushName");
    if (!pushNameFunc->IsFunction()) {
        return ;
    }
    auto getFunc = JSRef<JSFunc>::Cast(getParamByIndexFunc);
    auto param = JSRef<JSVal>::Cast(getFunc->Call(dataSourceObj_));
    auto pushFunc = JSRef<JSFunc>::Cast(pushNameFunc);
    JSRef<JSVal> params[ARGC_COUNT_TWO];
    params[0] = JSRef<JSVal>::Make(ToJSValue(name));
    params[1] = param;
    pushFunc->Call(dataSourceObj_, ARGC_COUNT_TWO, params);
*/
}

void NavigationStack::RemoveName(const std::string& name)
{
    PathStack::RemoveByName(name);
/*     JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    auto removeByNameFunc = dataSourceObj_->GetProperty("removeByName");
    if (!removeByNameFunc->IsFunction()) {
        return;
    }
    auto func = JSRef<JSFunc>::Cast(removeByNameFunc);
    JSRef<JSVal> params[1];
    params[0] = JSRef<JSVal>::Make(ToJSValue(name));
    func->Call(dataSourceObj_, 1, params);
*/
}

void NavigationStack::RemoveIndex(int32_t index)
{
    PathStack::RemoveIndex(index);
/*     JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    auto removeIndexFunc = dataSourceObj_->GetProperty("removeIndex");
    if (removeIndexFunc->IsFunction()) {
        auto func = JSRef<JSFunc>::Cast(removeIndexFunc);
        JSRef<JSVal> params[1];
        params[0] = JSRef<JSVal>::Make(ToJSValue(index));
        func->Call(dataSourceObj_, 1, params);
    }
*/
}

void NavigationStack::Clear()
{
    PathStack::Clear(std::nullopt);

/*     JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    auto clearFunc = dataSourceObj_->GetProperty("clear");
    if (!clearFunc->IsFunction()) {
        return;
    }
    auto func = JSRef<JSFunc>::Cast(clearFunc);
    func->Call(dataSourceObj_);
*/
}

std::vector<std::string> NavigationStack::GetAllPathName()
{
    return PathStack::GetAllPathName();
/*     JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, {});
    if (dataSourceObj_->IsEmpty()) {
        return {};
    }
    auto getAllPathNameFunc = dataSourceObj_->GetProperty("getAllPathName");
    if (!getAllPathNameFunc->IsFunction()) {
        return {};
    }
    auto func = JSRef<JSFunc>::Cast(getAllPathNameFunc);
    auto funcArray = func->Call(dataSourceObj_);
    if (!funcArray->IsArray()) {
        return {};
    }
    auto array = JSRef<JSArray>::Cast(funcArray);
    if (array->IsEmpty()) {
        return {};
    }
    std::vector<std::string> pathNames;
    for (size_t i = 0; i < array->Length(); i++) {
        auto value = array->GetValueAt(i);
        if (value->IsString()) {
            pathNames.emplace_back(value->ToString());
        }
    }

    return pathNames;
*/
}

std::vector<int32_t> NavigationStack::GetAllPathIndex()
{
    return PathStack::GetAllPathIndex();

/*     JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, {});
    if (dataSourceObj_->IsEmpty()) {
        return {};
    }
    auto getAllPathIndexFunc = dataSourceObj_->GetProperty("getAllPathIndex");
    if (!getAllPathIndexFunc->IsFunction()) {
        return {};
    }
    auto func = JSRef<JSFunc>::Cast(getAllPathIndexFunc);
    auto funcArray = func->Call(dataSourceObj_);
    if (!funcArray->IsArray()) {
        return {};
    }
    auto array = JSRef<JSArray>::Cast(funcArray);
    if (array->IsEmpty()) {
        return {};
    }
    std::vector<int32_t> pathIndex;
    for (size_t i = 0; i < array->Length(); i++) {
        auto value = array->GetValueAt(i);
        if (value->IsNumber()) {
            pathIndex.emplace_back(value->ToNumber<int32_t>());
        }
    }

    return pathIndex;
*/
}

void NavigationStack::InitNavPathIndex(const std::vector<std::string>& pathNames)
{
    PathStack::InitNavPathIndex(pathNames);
/*     JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    if (dataSourceObj_->IsEmpty()) {
        return;
    }

    JSRef<JSArray> nameArray = JSRef<JSArray>::New();
    JSRef<JSVal> params[1];
    for (size_t i = 0; i < pathNames.size(); i++) {
        JSRef<JSVal> info = JSRef<JSVal>::Make(ToJSValue(pathNames[i]));
        nameArray->SetValueAt(i, info);
    }
    params[0] = nameArray;
    auto initNavPathIndexFunc = dataSourceObj_->GetProperty("initNavPathIndex");
    if (!initNavPathIndexFunc->IsFunction()) {
        return;
    }
    auto func = JSRef<JSFunc>::Cast(initNavPathIndexFunc);
    func->Call(dataSourceObj_, 1, params);
*/
}

void NavigationStack::SetDestinationIdToJsStack(int32_t index, const std::string& navDestinationId)
{
    if (auto pathInfo = PathStack::GetPathInfo(index); pathInfo) {
        pathInfo->navDestinationId_ = navDestinationId;
    }
/*     JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    auto pathInfo = GetJsPathInfo(index);
    if (pathInfo->IsEmpty()) {
        return;
    }
    pathInfo->SetProperty<std::string>("navDestinationId", navDestinationId);
*/
}

bool NavigationStack::CreateNodeByIndex(int32_t index, const WeakPtr<NG::UINode>& customNode,
    RefPtr<NG::UINode>& node)
{
    return {};
/*
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, false);
    auto pathInfo = GetJsPathInfo(index);
    auto name = pathInfo->GetPropertyValue<std::string>("name", "");
    auto param = pathInfo->GetProperty("param");
    RefPtr<NG::UINode> targetNode;
    RefPtr<NG::NavDestinationGroupNode> desNode;
    NG::ScopedViewStackProcessor scopedViewStackProcessor;
    int32_t errorCode = LoadDestination(name, param, customNode, targetNode, desNode);
    // isRemove true, set destination info, false, current destination create failed
    bool isRemove = RemoveDestinationIfNeeded(pathInfo, errorCode, index);
    if (!isRemove) {
        return false;
    }
    if (errorCode != ERROR_CODE_NO_ERROR) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "can't find target destination by index, create empty node");
        node = AceType::DynamicCast<NG::UINode>(NavDestinationModel::GetInstance()->CreateEmpty());
        return true;
    }
    node = targetNode;
    auto pattern = AceType::DynamicCast<NG::NavDestinationPattern>(desNode->GetPattern());
    if (pattern) {
        pattern->SetName(name);
        pattern->SetIndex(index);
        auto onPop = GetOnPopByIndex(index);
        auto isEntry = GetIsEntryByIndex(index);
        TAG_LOGD(AceLogTag::ACE_NAVIGATION, "create destination node, isEntry %{public}d", isEntry);
        auto pathInfo = AceType::MakeRefPtr<JSNavPathInfo>(name, param, onPop, isEntry);
        pattern->SetNavPathInfo(pathInfo);
        pattern->SetNavigationStack(WeakClaim(this));
    }
    return true;
*/
}

RefPtr<NG::UINode> NavigationStack::CreateNodeByRouteInfo(const RefPtr<NG::RouteInfo>& routeInfo,
    const WeakPtr<NG::UINode>& customNode)
{
    return {};

/*     JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, nullptr);
    auto jsRouteInfo = AceType::DynamicCast<JSRouteInfo>(routeInfo);
    if (!jsRouteInfo) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "route info is invalid");
        return DynamicCast<NG::UINode>(NavDestinationModel::GetInstance()->CreateEmpty());
    }
    auto name = jsRouteInfo->GetName();
    auto param = jsRouteInfo->GetParam();
    RefPtr<NG::UINode> node;
    RefPtr<NG::NavDestinationGroupNode> desNode;
    int32_t errorCode = LoadDestination(name, param, customNode, node, desNode);
    if (errorCode == ERROR_CODE_NO_ERROR) {
        auto pattern = AceType::DynamicCast<NG::NavDestinationPattern>(desNode->GetPattern());
        if (pattern) {
            auto pathInfo = AceType::MakeRefPtr<JSNavPathInfo>(name, param);
            pattern->SetNavPathInfo(pathInfo);
            pattern->SetName(name);
            pattern->SetNavigationStack(WeakClaim(this));
        }
        return node;
    }
    return DynamicCast<NG::UINode>(NavDestinationModel::GetInstance()->CreateEmpty()); */
}

std::string NavigationStack::GetNameByIndex(int32_t index) const
{
    auto pathInfo = PathStack::GetPathInfo(index);
    return pathInfo ? pathInfo->name_ : "";
/*     auto pathNames = GetAllPathName();
    if (index < 0 || index >= static_cast<int32_t>(pathNames.size())) {
        return "";
    }

    return pathNames[index];
 */
}
ParamType NavigationStack::GetParamByIndex(int32_t index) const
{
    auto pathInfo = PathStack::GetPathInfo(index);
    return pathInfo ? pathInfo->param_ : ParamType();
/*
    if (dataSourceObj_->IsEmpty()) {
        return JSRef<JSVal>::Make();
    }
    auto getParamByIndexFunc = dataSourceObj_->GetProperty("getParamByIndex");
    if (!getParamByIndexFunc->IsFunction()) {
        return JSRef<JSVal>::Make();
    }
    auto func = JSRef<JSFunc>::Cast(getParamByIndexFunc);
    JSRef<JSVal> params[1];
    params[0] = JSRef<JSVal>::Make(ToJSValue(index));
    return func->Call(dataSourceObj_, 1, params);
*/
}
OnPopCallback NavigationStack::GetOnPopByIndex(int32_t index) const
{
    auto pathInfo = PathStack::GetPathInfo(index);
    return pathInfo ? pathInfo->onPop_ : OnPopCallback();
/*
    if (dataSourceObj_->IsEmpty()) {
        return JSRef<JSVal>::Make();
    }
    auto getOnPopByIndexFunc = dataSourceObj_->GetProperty("getOnPopByIndex");
    if (!getOnPopByIndexFunc->IsFunction()) {
        return JSRef<JSVal>::Make();
    }
    auto func = JSRef<JSFunc>::Cast(getOnPopByIndexFunc);
    JSRef<JSVal> params[1];
    params[0] = JSRef<JSVal>::Make(ToJSValue(index));
    return func->Call(dataSourceObj_, 1, params);
 */
}
bool NavigationStack::GetIsEntryByIndex(int32_t index)
{
    auto pathInfo = PathStack::GetPathInfo(index);
    return pathInfo && pathInfo->isEntry_;
/*     JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, false);
    if (dataSourceObj_->IsEmpty()) {
        return false;
    }
    auto getIsEntryFunc = dataSourceObj_->GetProperty("getIsEntryByIndex");
    if (!getIsEntryFunc->IsFunction()) {
        return false;
    }
    auto func = JSRef<JSFunc>::Cast(getIsEntryFunc);
    JSRef<JSVal> params[1];
    params[0] = JSRef<JSVal>::Make(ToJSValue(index));
    auto result = func->Call(dataSourceObj_, 1, params);
    if (!result->IsBoolean()) {
        return false;
    }
    return result->ToBoolean();
 */}

void NavigationStack::SetIsEntryByIndex(int32_t index, bool isEntry)
{
    if (auto pathInfo = PathStack::GetPathInfo(index); pathInfo) {
        pathInfo->isEntry_ = isEntry;
    }
/*
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    CHECK_NULL_VOID(dataSourceObj_->IsEmpty());
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    auto setIsEntryFunc = dataSourceObj_->GetProperty("setIsEntryByIndex");
    if (!setIsEntryFunc->IsFunction()) {
        return;
    }
    auto func = JSRef<JSFunc>::Cast(setIsEntryFunc);
    JSRef<JSVal> params[ARGC_COUNT_TWO];
    params[0] = JSRef<JSVal>::Make(ToJSValue(index));
    params[1] = JSRef<JSVal>::Make(ToJSValue(isEntry));
    func->Call(dataSourceObj_, ARGC_COUNT_TWO, params);
*/
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

int32_t NavigationStack::GetReplaceValue() const
{
    return PathStack::isReplace_;
/*     if (dataSourceObj_->IsEmpty()) {
        return false;
    }
    auto replace = dataSourceObj_->GetProperty("isReplace");
    return replace->ToNumber<int32_t>();
 */
}

void NavigationStack::UpdateReplaceValue(int32_t replaceValue) const
{
    const_cast<NavigationStack *>(this)->SetIsReplace(replaceValue);
/*     JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    auto setIsReplaceFunc = dataSourceObj_->GetProperty("setIsReplace");
    if (!setIsReplaceFunc->IsFunction()) {
        return;
    }
    auto replaceFunc = JSRef<JSFunc>::Cast(setIsReplaceFunc);
    JSRef<JSVal> params[1];
    params[0] = JSRef<JSVal>::Make(ToJSValue(replaceValue));
    replaceFunc->Call(dataSourceObj_, 1, params);
 */
}

std::string NavigationStack::GetRouteParam() const
{
    auto size = GetSize();
    if (size > 0) {
        auto param = GetParamByIndex(size - 1);
        return ConvertParamToString(param, true);
    }
    return "";
 }

int32_t NavigationStack::GetSize() const
{
    return PathStack::Size();
/*     JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, 0);
    if (dataSourceObj_->IsEmpty()) {
        return 0;
    }
    auto sizeFunc = dataSourceObj_->GetProperty("size");
    if (!sizeFunc->IsFunction()) {
        return 0;
    }
    auto func = JSRef<JSFunc>::Cast(sizeFunc);
    auto jsValue = JSRef<JSVal>::Cast(func->Call(dataSourceObj_));
    if (jsValue->IsNumber()) {
        return jsValue->ToNumber<int32_t>();
    }
    return 0;
*/
}
std::string NavigationStack::ConvertParamToString(const ParamType& param, bool needLimit) const
{
    return {};
/*auto errorCode = 
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, "");
    if (param->IsBoolean()) {
        bool ret = param->ToBoolean();
        return ret ? "true" : "false";
    } else if (param->IsNumber()) {
        double ret = param->ToNumber<double>();
        std::ostringstream oss;
        oss << ret;
        return oss.str();
    } else if (param->IsString()) {
        std::string ret = param->ToString();
        if (needLimit && ret.size() > MAX_PARSE_LENGTH) {
            return ret.substr(0, MAX_PARSE_LENGTH);
        }
        return ret;
    } else if (param->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(param);
        auto jsonObj = JsonUtil::Create(true);
        ParseJsObject(jsonObj, obj, MAX_PARSE_DEPTH, needLimit);
        return jsonObj->ToString();
    }
    return "";
*/
}
bool NavigationStack::GetAnimatedValue() const
{
    return PathStack::animated_;
/*     if (dataSourceObj_->IsEmpty()) {
        return true;
    }
    auto animated = dataSourceObj_->GetProperty("animated");
    return animated->ToBoolean();
*/
}

void NavigationStack::UpdateAnimatedValue(bool animated)
{
    PathStack::SetAnimated(animated);
/*     JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    auto setAnimatedFunc = dataSourceObj_->GetProperty("setAnimated");
    if (!setAnimatedFunc->IsFunction()) {
        return;
    }
    auto animatedFunc = JSRef<JSFunc>::Cast(setAnimatedFunc);
    JSRef<JSVal> params[1];
    params[0] = JSRef<JSVal>::Make(ToJSValue(animated));
    animatedFunc->Call(dataSourceObj_, 1, params);
 */}


bool NavigationStack::GetDisableAnimation() const
{
    return PathStack::disableAllAnimation_;
/*     if (dataSourceObj_->IsEmpty()) {
        return false;
    }
    auto disableAllAnimation = dataSourceObj_->GetProperty("disableAllAnimation");
    return disableAllAnimation->ToBoolean();
 */
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
/*
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    auto removeInvalidPage = dataSourceObj_->GetProperty("removeInvalidPage");
    if (removeInvalidPage->IsFunction()) {
        auto func = JSRef<JSFunc>::Cast(removeInvalidPage);
        auto pathName = info->GetProperty("name");
        auto param = info->GetProperty("param");
        JSRef<JSVal> params[ARGC_COUNT_TWO] = { pathName, param };
        func->Call(dataSourceObj_, ARGC_COUNT_TWO, params);
    }
*/
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
/*     JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    std::string targetName = isBefore ? "willShow" : "didShow";
    JSRef<JSFunc> targetFunc;
    if (!CheckAndGetInterceptionFunc(targetName, targetFunc)) {
        return;
    }
    const uint8_t argsNum = 4;
    JSRef<JSVal> params[argsNum];
    auto preDestination = AceType::DynamicCast<NG::NavDestinationContext>(from);
    if (!preDestination) {
        params[0] = JSRef<JSVal>::Make(ToJSValue("navBar"));
    } else if (preDestination->GetIsEmpty()) {
        params[0] = JSRef<JSObject>::New();
    } else {
        JSRef<JSObject> preObj = JSClass<JSNavDestinationContext>::NewInstance();
        auto preProxy = Referenced::Claim(preObj->Unwrap<JSNavDestinationContext>());
        preProxy->SetNavDestinationContext(from);
        params[0] = preObj;
    }

    auto topDestination = AceType::DynamicCast<NG::NavDestinationContext>(to);
    if (!topDestination) {
        params[1] = JSRef<JSVal>::Make(ToJSValue("navBar"));
    } else if (topDestination->GetIsEmpty()) {
        params[1] = JSRef<JSObject>::New();
    } else {
        JSRef<JSObject> topObj = JSClass<JSNavDestinationContext>::NewInstance();
        auto topProxy = Referenced::Claim(topObj->Unwrap<JSNavDestinationContext>());
        topProxy->SetNavDestinationContext(to);
        params[1] = topObj;
    }
    const uint8_t operationIndex = 2;
    params[operationIndex] = JSRef<JSVal>::Make(ToJSValue(static_cast<int32_t>(operation)));
    const uint8_t animatedIndex = 3;
    params[animatedIndex] = JSRef<JSVal>::Make(ToJSValue(isAnimated));
    targetFunc->Call(JSRef<JSObject>(), argsNum, params);
*/
}

void NavigationStack::FireNavigationModeChange(NG::NavigationMode mode)
{
/*     JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    JSRef<JSFunc> modeFunc;
    if (!CheckAndGetInterceptionFunc("modeChange", modeFunc)) {
        return;
    }
    JSRef<JSVal> params[1];
    params[0] = JSRef<JSVal>::Make(ToJSValue(static_cast<int32_t>(mode)));
    modeFunc->Call(JSRef<JSObject>(), 1, params);
*/
}

/* bool NavigationStack::CheckAndGetInterceptionFunc(const std::string& name, JSRef<JSFunc>& func)
{
    return bool();
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, false);
    if (dataSourceObj_->IsEmpty()) {
        return false;
    }
    JSRef<JSVal> delegateProp = dataSourceObj_->GetProperty("interception");
    if (!delegateProp->IsObject()) {
        return false;
    }
    JSRef<JSObject> delegate = JSRef<JSObject>::Cast(delegateProp);
    JSRef<JSVal> funcProp = delegate->GetProperty(name.c_str());
    if (!funcProp->IsFunction()) {
        return false;
    }
    func = JSRef<JSFunc>::Cast(funcProp);
    return true;
}
 */
/*auto errorCode = 
bool NavigationStack::LoadDestinationByBuilder(const std::string& name, const JSRef<JSVal>& param,
    RefPtr<NG::UINode>& node, RefPtr<NG::NavDestinationGroupNode>& desNode)
{
    return bool();
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, false);
    if (navDestBuilderFunc_->IsEmpty()) {
        TAG_LOGW(AceLogTag::ACE_NAVIGATION, "Builder function is empty");
        return false;
    }
    auto builderObj = JSRef<JSObject>::Cast(navDestBuilderFunc_);
    const int32_t number = builderObj->GetProperty("length")->ToNumber<int32_t>();
    JSRef<JSVal> params[number];
    if (number >= 1) {
        params[0] = JSRef<JSVal>::Make(ToJSValue(name));
    }
    if (number >= ARGC_COUNT_TWO) {
        params[1] = param;
    }
    navDestBuilderFunc_->Call(JSRef<JSObject>(), number, params);
    node = NG::ViewStackProcessor::GetInstance()->Finish();
    return GetNavDestinationNodeInUINode(node, desNode);
}
*/
/*auto errorCode = 
int32_t NavigationStack::LoadDestination(const std::string& name, const JSRef<JSVal>& param,
    const WeakPtr<NG::UINode>& customNode, RefPtr<NG::UINode>& node,
    RefPtr<NG::NavDestinationGroupNode>& desNode)
{
    NG::ScopedViewStackProcessor scopedViewStackProcessor;
    // execute navdestination attribute builder
    if (LoadDestinationByBuilder(name, param, node, desNode)) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "load destination by buildermap");
        return ERROR_CODE_NO_ERROR;
    }
    // deal route config and execute route config builder
    auto container = Container::Current();
    auto navigationRoute = container->GetNavigationRoute();
    if (!navigationRoute->HasLoaded(name)) {
        int32_t res = navigationRoute->LoadPage(name);
        if (res != 0) {
            TAG_LOGE(AceLogTag::ACE_NAVIGATION, "load page failed: %{public}s", name.c_str());
            return navDestBuilderFunc_->IsEmpty() ? ERROR_CODE_BUILDER_FUNCTION_NOT_REGISTERED
                : ERROR_CODE_DESTINATION_NOT_FOUND;
        }
    }
    auto parentCustomNode = AceType::DynamicCast<NG::CustomNode>(customNode.Upgrade());
    CHECK_NULL_RETURN(parentCustomNode, ERROR_CODE_INTERNAL_ERROR);
    auto thisObjTmp = parentCustomNode->FireThisFunc();
    CHECK_NULL_RETURN(thisObjTmp, ERROR_CODE_INTERNAL_ERROR);
    JSRef<JSObject> thisObj = *(JSRef<JSObject>*)(thisObjTmp);
    auto engine = AceType::DynamicCast<Framework::JsiDeclarativeEngine>(EngineHelper::GetCurrentEngine());
    CHECK_NULL_RETURN(engine, ERROR_CODE_INTERNAL_ERROR);
    JSRef<JSObject> wrapBuilder = JSRef<JSObject>::Make(engine->GetNavigationBuilder(name).ToLocal());
    if (wrapBuilder->IsEmpty()) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "wrap builder is empty: %{public}s", name.c_str());
        return ERROR_CODE_BUILDER_FUNCTION_NOT_REGISTERED;
    }
    auto builderProp = wrapBuilder->GetProperty("builder");
    if (!builderProp->IsFunction()) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "get builder failed: %{public}s", name.c_str());
        return ERROR_CODE_BUILDER_FUNCTION_NOT_REGISTERED;
    }
    auto builderObj = JSRef<JSObject>::Cast(builderProp);
    const int32_t number = builderObj->GetProperty("length")->ToNumber<int32_t>();
    JSRef<JSVal> params[number];
    if (number >= 1) {
        params[0] = JSRef<JSVal>::Make(ToJSValue(name));
    }
    if (number >= ARGC_COUNT_TWO) {
        params[1] = param;
    }
    auto builder = JSRef<JSFunc>::Cast(builderProp);
    builder->Call(thisObj, number, params);
    node = NG::ViewStackProcessor::GetInstance()->Finish();
    if (!GetNavDestinationNodeInUINode(node, desNode)) {
        return ERROR_CODE_DESTINATION_NOT_FOUND;
    }
    return ERROR_CODE_NO_ERROR;
}
*/

int32_t NavigationStack::GetJsIndexFromNativeIndex(int32_t index)
{
    return PathStack::GetJsIndexFromNativeIndex(index);
/*     JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, -1);
    if (dataSourceObj_->IsEmpty()) {
        return -1;
    }
    auto getIndexFunc = dataSourceObj_->GetProperty("getJsIndexFromNativeIndex");
    if (!getIndexFunc->IsFunction()) {
        return -1;
    }
    auto func = JSRef<JSFunc>::Cast(getIndexFunc);
    JSRef<JSVal> param = JSRef<JSVal>::Make(ToJSValue(index));
    auto res = func->Call(dataSourceObj_, 1, &param);
    if (res->IsNumber()) {
        return res->ToNumber<int32_t>();
    }
    return -1;
*/
}

void NavigationStack::MoveIndexToTop(int32_t index)
{
    PathStack::MoveIndexToTop(index, std::nullopt);
/*     JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    auto moveIndexToTopFunc = dataSourceObj_->GetProperty("moveIndexToTop");
    if (!moveIndexToTopFunc->IsFunction()) {
        return;
    }
    auto func = JSRef<JSFunc>::Cast(moveIndexToTopFunc);
    JSRef<JSVal> param = JSRef<JSVal>::Make(ToJSValue(index));
    func->Call(dataSourceObj_, 1, &param); */
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
/*
    auto name = GetNameByIndex(index);
    auto param = GetParamByIndex(index);
    auto onPop = GetOnPopByIndex(index);
 */
    auto pathInfoData = AceType::MakeRefPtr<NavPathInfo>(pathInfo->name_); // temp stub
    pattern->SetNavPathInfo(pathInfoData);
}

bool NavigationStack::GetNeedUpdatePathInfo(int32_t index)
{
    auto pathInfo = PathStack::GetPathInfo(index);
    return pathInfo && pathInfo->needUpdate_;

/*     JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, false);
    auto path = GetJsPathInfo(index);
    if (path->IsEmpty()) {
        return false;
    }
    auto needUpdate = path->GetProperty("needUpdate");
    if (!needUpdate->IsBoolean()) {
        return false;
    }
    return needUpdate->ToBoolean() */;
}

void NavigationStack::SetNeedUpdatePathInfo(int32_t index, bool need)
{
    if (auto pathInfo = PathStack::GetPathInfo(index); pathInfo) {
        pathInfo->needUpdate_ = need;
    }
/*     JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    auto path = GetJsPathInfo(index);
    if (path->IsEmpty()) {
        return;
    }
    path->SetProperty<bool>("needUpdate", need); */
}

void NavigationStack::RecoveryNavigationStack()
{
/*     JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    navPathList_ = preNavPathList_;
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    JSRef<JSArray> pathArray = JSRef<JSArray>::New();
    for (int32_t index = 0; index < static_cast<int32_t>(navPathList_.size()); index++) {
        auto node = navPathList_[index].second;
        auto navDestinationGroupNode = AceType::DynamicCast<NG::NavDestinationGroupNode>(
            NG::NavigationGroupNode::GetNavDestinationNode(node));
        if (!navDestinationGroupNode) {
            continue;
        }
        auto pattern = AceType::DynamicCast<NG::NavDestinationPattern>(navDestinationGroupNode->GetPattern());
        if (!pattern) {
            continue;
        }
        auto context = pattern->GetNavDestinationContext();
        if (!context) {
            continue;
        }
        JSRef<JSObject> item = CreatePathInfoWithNecessaryProperty(context);
        pathArray->SetValueAt(index, item);
    }
    dataSourceObj_->SetPropertyObject("pathArray", pathArray); */
}

bool NavigationStack::NeedBuildNewInstance(int32_t index)
{
    auto pathInfo = PathStack::GetPathInfo(index);
    return pathInfo && pathInfo->needBuildNewInstance_;
/*     JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, false);
    auto pathInfo = GetJsPathInfo(index);
    if (pathInfo->IsEmpty()) {
        return false;
    }
    auto needBuildNewInstance = pathInfo->GetProperty("needBuildNewInstance");
    if (!needBuildNewInstance->IsBoolean()) {
        return false;
    }
    return needBuildNewInstance->ToBoolean(); */
}

void NavigationStack::SetNeedBuildNewInstance(int32_t index, bool need)
{
    if (auto pathInfo = PathStack::GetPathInfo(index); pathInfo) {
        pathInfo->needBuildNewInstance_ = need;
    }
/*     JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    auto pathInfo = GetJsPathInfo(index);
    if (pathInfo->IsEmpty()) {
        return;
    }
    pathInfo->SetProperty<bool>("needBuildNewInstance", need); */
}

/*
JSRef<JSObject> NavigationStack::CreatePathInfoWithNecessaryProperty(
    const RefPtr<NG::NavDestinationContext>& context)
{
    auto pathInfo = JSRef<JSObject>::New();
    CHECK_NULL_RETURN(context, pathInfo);
    auto jsPathInfo = AceType::DynamicCast<JSNavPathInfo>(context->GetNavPathInfo());
    CHECK_NULL_RETURN(jsPathInfo, pathInfo);

    pathInfo->SetProperty<std::string>("name", jsPathInfo->GetName());
    pathInfo->SetProperty<int32_t>("index", context->GetIndex());
    pathInfo->SetProperty<std::string>("navDestinationId", std::to_string(context->GetNavDestinationId()));
    pathInfo->SetProperty("param", jsPathInfo->GetParam());
    pathInfo->SetProperty("onPop", jsPathInfo->GetOnPop());
    pathInfo->SetProperty("isEntry", jsPathInfo->GetIsEntry());
    return pathInfo;
}
*/
std::string NavigationStack::GetStringifyParamByIndex(int32_t index) const
{
    return std::string();
/*     auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_RETURN(engine, JS_STRINGIFIED_UNDEFINED);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_RETURN(nativeEngine, JS_STRINGIFIED_UNDEFINED);
    auto env = reinterpret_cast<napi_env>(nativeEngine);

    if (dataSourceObj_->IsEmpty()) {
        return JS_STRINGIFIED_UNDEFINED;
    }
    napi_value navPathStack = JsConverter::ConvertJsValToNapiValue(dataSourceObj_);
    napi_value getParamByIndex;
    napi_get_named_property(env, navPathStack, "getParamByIndex", &getParamByIndex);
    napi_value napiIndex;
    napi_create_int32(env, index, &napiIndex);
    napi_value param;
    napi_call_function(env, navPathStack, getParamByIndex, 1, &napiIndex, &param);

    napi_value globalValue;
    napi_get_global(env, &globalValue);
    napi_value jsonClass;
    napi_get_named_property(env, globalValue, "JSON", &jsonClass);
    napi_value stringifyFunc;
    napi_get_named_property(env, jsonClass, "stringify", &stringifyFunc);
    napi_value stringifyParam;
    if (napi_call_function(env, jsonClass, stringifyFunc, 1, &param, &stringifyParam) != napi_ok) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "Can not stringify current param!");
        napi_get_and_clear_last_exception(env, &stringifyParam);
        return JS_STRINGIFIED_UNDEFINED;
    }
    size_t len = 0;
    napi_get_value_string_utf8(env, stringifyParam, nullptr, 0, &len);
    std::unique_ptr<char[]> paramChar = std::make_unique<char[]>(len + 1);
    napi_get_value_string_utf8(env, stringifyParam, paramChar.get(), len + 1, &len);
    return paramChar.get();
 */}

void NavigationStack::SetPathArray(const std::vector<NG::NavdestinationRecoveryInfo>& navdestinationsInfo)
{
/*     JSRef<JSArray> newPathArray = JSRef<JSArray>::New();
    for (int32_t index = 0; index < static_cast<int32_t>(navdestinationsInfo.size()); ++index) {
        auto infoName = navdestinationsInfo[index].name;
        auto infoParam = navdestinationsInfo[index].param;
        auto infoMode = navdestinationsInfo[index].mode;

        JSRef<JSObject> navPathInfo = JSRef<JSObject>::New();
        navPathInfo->SetProperty<std::string>("name", infoName);
        if (!infoParam.empty() && infoParam != JS_STRINGIFIED_UNDEFINED) {
            navPathInfo->SetPropertyObject("param", JSRef<JSObject>::New()->ToJsonObject(infoParam.c_str()));
        }
        navPathInfo->SetProperty<bool>("fromRecovery", true);
        navPathInfo->SetProperty<int32_t>("mode", infoMode);
        newPathArray->SetValueAt(index, navPathInfo);
    }
    dataSourceObj_->SetPropertyObject("pathArray", newPathArray);
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "Set navPathArray by recovery info success");
 */
}

bool NavigationStack::IsFromRecovery(int32_t index)
{
    auto pathInfo = PathStack::GetPathInfo(index);
    return pathInfo && pathInfo->fromRecovery_;
/*     auto pathInfo = GetJsPathInfo(index);
    if (pathInfo->IsEmpty()) {
        return false;
    }
    auto fromRecovery = pathInfo->GetProperty("fromRecovery");
    if (!fromRecovery->IsBoolean()) {
        return false;
    }
    return fromRecovery->ToBoolean();
*/
}

void NavigationStack::SetFromRecovery(int32_t index, bool fromRecovery)
{
    if (auto pathInfo = PathStack::GetPathInfo(index); pathInfo) {
        pathInfo->fromRecovery_ = fromRecovery;
    }
/*     auto pathInfo = GetJsPathInfo(index);
    if (pathInfo->IsEmpty()) {
        return;
    }
    pathInfo->SetProperty<bool>("fromRecovery", fromRecovery);
*/
}

int32_t NavigationStack::GetRecoveredDestinationMode(int32_t index)
{
    auto pathInfo = PathStack::GetPathInfo(index);
    return pathInfo ? pathInfo->mode_ : INVALID_DESTINATION_MODE;
/*     auto pathInfo = GetJsPathInfo(index);
    if (pathInfo->IsEmpty()) {
        return INVALID_DESTINATION_MODE;
    }
    auto mode = pathInfo->GetProperty("mode");
    if (!mode->IsNumber()) {
        return INVALID_DESTINATION_MODE;
    }
    return mode->ToNumber<int32_t>();
*/
}
} // namespace OHOS::Ace::NG::GeneratedModifier::NavigationContext
