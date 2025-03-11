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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_navigation_stack_ffi.h"

#include "core/components_ng/pattern/navrouter/navdestination_model.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::Framework {

std::string CJRouteInfo::GetName()
{
    return name_;
}

void CJRouteInfo::SetName(const std::string& name)
{
    name_ = name;
}

void CJRouteInfo::SetParam(const std::string& param)
{
    param_ = param;
}

std::string CJRouteInfo::GetParam() const
{
    return param_;
}

void CJNavigationStack::SetDataSourceObj(int64_t dataSourceObjId)
{
    auto newObj = OHOS::FFI::FFIData::GetData<CJNavPathStack>(dataSourceObjId);
    if (newObj == nullptr) {
        LOGE("Navigation create error, Cannot get CJNavPathStack by id: %{public}" PRId64, dataSourceObjId);
        return;
    }
    UpdateOnStateChangedCallback(dataSourceObj_, nullptr);
    dataSourceObjId_ = dataSourceObjId;
    dataSourceObj_ = newObj;
    RemoveStack();
    UpdateOnStateChangedCallback(dataSourceObj_, onStateChangedCallback_);
}

sptr<CJNavPathStack> CJNavigationStack::GetDataSourceObj()
{
    return dataSourceObj_;
}

int64_t CJNavigationStack::GetDataSourceObjId()
{
    return dataSourceObjId_;
}

void CJNavigationStack::UpdateOnStateChangedCallback(sptr<CJNavPathStack> obj, std::function<void()> callback)
{
    if (obj == nullptr) {
        return;
    }
    obj->SetOnStateChangedCallback(callback);
    obj->OnStateChanged();
}

void CJNavigationStack::SetNavDestBuilderFunc(
    std::function<void(std::string name, std::string param)> navDestBuilderFunc)
{
    navDestBuilderFunc_ = navDestBuilderFunc;
}

bool CJNavigationStack::IsEmpty()
{
    return dataSourceObj_->IsEmpty();
}

void CJNavigationStack::Pop()
{
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    dataSourceObj_->Pop("", true);
}

void CJNavigationStack::Push(const std::string& name, const RefPtr<NG::RouteInfo>& routeInfo)
{
    std::string param;
    if (routeInfo) {
        auto cjRouteInfo = AceType::DynamicCast<CJRouteInfo>(routeInfo);
        param = cjRouteInfo->GetParam();
    } else {
        std::vector<std::string> params = dataSourceObj_->GetParamByName(name);
        if (!param.empty()) {
            param = params[0];
        }
    }

    dataSourceObj_->PushName(name, param);
}

void CJNavigationStack::Push(const std::string& name, int32_t index)
{
    dataSourceObj_->PushName(name, dataSourceObj_->GetParamByIndex(index));
}

void CJNavigationStack::RemoveName(const std::string& name)
{
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    dataSourceObj_->RemoveByName(name);
}

void CJNavigationStack::RemoveIndex(int32_t index)
{
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    dataSourceObj_->RemoveIndex(index);
}

void CJNavigationStack::Clear()
{
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    dataSourceObj_->Clear(true);
}

int32_t CJNavigationStack::GetReplaceValue() const
{
    if (dataSourceObj_->IsEmpty()) {
        return false;
    }
    return dataSourceObj_->GetIsReplace();
}

void CJNavigationStack::UpdateReplaceValue(int32_t isReplace) const
{
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    dataSourceObj_->SetIsReplace(isReplace);
}

bool CJNavigationStack::GetAnimatedValue() const
{
    if (dataSourceObj_->IsEmpty()) {
        return true;
    }
    return dataSourceObj_->GetAnimated();
}

void CJNavigationStack::UpdateAnimatedValue(bool animated)
{
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    dataSourceObj_->SetAnimated(animated);
}

bool CJNavigationStack::GetDisableAnimation() const
{
    if (dataSourceObj_->IsEmpty()) {
        return false;
    }
    return dataSourceObj_->GetDisableAllAnimation();
}

std::vector<std::string> CJNavigationStack::GetAllPathName()
{
    if (dataSourceObj_->IsEmpty()) {
        return {};
    }
    return dataSourceObj_->GetAllPathName();
}

std::vector<int32_t> CJNavigationStack::GetAllPathIndex()
{
    if (dataSourceObj_->IsEmpty()) {
        return {};
    }
    return dataSourceObj_->GetAllPathIndex();
}

void CJNavigationStack::InitNavPathIndex(const std::vector<std::string>& pathNames)
{
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    dataSourceObj_->InitNavPathIndex(pathNames);
}

void CJNavigationStack::SetDestinationIdToJsStack(int32_t index, const std::string& navDestinationId)
{
    dataSourceObj_->SetNavDestinationId(index, navDestinationId);
}

bool CJNavigationStack::CreateNodeByIndex(
    int32_t index, const WeakPtr<NG::UINode>& customNode, RefPtr<NG::UINode>& node)
{
    std::string name;
    std::string param;
    auto pathInfo = dataSourceObj_->GetPathInfo(index);
    if (pathInfo.has_value()) {
        auto data = pathInfo.value();
        name = data.name;
        param = data.param;
    }

    RefPtr<NG::UINode> targetNode;
    RefPtr<NG::NavDestinationGroupNode> desNode;
    NG::ScopedViewStackProcessor scopedViewStackProcessor;
    int32_t errorCode = LoadDestination(name, param, customNode, targetNode, desNode);
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
        TAG_LOGD(AceLogTag::ACE_NAVIGATION, "create destination node");
        auto pathInfo = AceType::MakeRefPtr<CJNavPathInfoNG>(name, param);
        pattern->SetNavPathInfo(pathInfo);
        pattern->SetNavigationStack(WeakClaim(this));
    }
    return true;
}

int32_t CJNavigationStack::LoadDestination(const std::string& name, const std::string& param,
    const WeakPtr<NG::UINode>& customNode, RefPtr<NG::UINode>& node, RefPtr<NG::NavDestinationGroupNode>& desNode)
{
    NG::ScopedViewStackProcessor scopedViewStackProcessor;

    navDestBuilderFunc_(name, param);
    node = NG::ViewStackProcessor::GetInstance()->Finish();
    (void)GetNavDestinationNodeInUINode(node, desNode);
    return ERROR_CODE_NO_ERROR;
}

bool CJNavigationStack::GetNavDestinationNodeInUINode(
    RefPtr<NG::UINode> node, RefPtr<NG::NavDestinationGroupNode>& desNode)
{
    RefPtr<NG::CustomNode> customNode;
    while (node) {
        if (node->GetTag() == "JsView") {
            customNode = AceType::DynamicCast<NG::CustomNode>(node);
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "render current custom node: %{public}s",
                customNode->GetCustomTag().c_str());
            // record parent navigationNode before customNode is rendered in case of navDestinationNode
            auto navigationNode = GetNavigationNode();
            customNode->SetNavigationNode(navigationNode);
            // render, and find deep further
            customNode->Render();
        } else if (node->GetTag() == "NavDestination") {
            desNode = AceType::DynamicCast<NG::NavDestinationGroupNode>(node);
            if (desNode) {
                desNode->SetNavDestinationCustomNode(AceType::WeakClaim(AceType::RawPtr(customNode)));
            }
            return true;
        }
        auto children = node->GetChildren();
        if (children.size() != 1) {
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "router map is invalid, child size is not one: %{public}zu",
                children.size());
        }
        node = children.front();
    }
    return false;
}

RefPtr<NG::UINode> CJNavigationStack::CreateNodeByRouteInfo(
    const RefPtr<NG::RouteInfo>& routeInfo, const WeakPtr<NG::UINode>& customNode)
{
    auto cjRouteInfo = AceType::DynamicCast<CJRouteInfo>(routeInfo);
    if (!cjRouteInfo) {
        return DynamicCast<NG::UINode>(NavDestinationModel::GetInstance()->CreateEmpty());
    }
    auto name = cjRouteInfo->GetName();
    auto param = cjRouteInfo->GetParam();
    RefPtr<NG::UINode> node;
    RefPtr<NG::NavDestinationGroupNode> desNode;
    int32_t errorCode = LoadDestination(name, param, customNode, node, desNode);
    if (errorCode == ERROR_CODE_NO_ERROR) {
        auto pattern = AceType::DynamicCast<NG::NavDestinationPattern>(desNode->GetPattern());
        if (pattern) {
            auto pathInfo = AceType::MakeRefPtr<CJNavPathInfoNG>(name, param);
            pattern->SetNavPathInfo(pathInfo);
            pattern->SetName(name);
            pattern->SetNavigationStack(WeakClaim(this));
        }
        return node;
    }
    return DynamicCast<NG::UINode>(NavDestinationModel::GetInstance()->CreateEmpty());
}

std::string CJNavigationStack::GetRouteParam() const
{
    auto size = GetSize();
    if (size > 0) {
        return dataSourceObj_->GetParamByIndex(size - 1);
    }
    return "";
}

int32_t CJNavigationStack::GetSize() const
{
    return dataSourceObj_->GetSize();
}

void CJNavigationStack::OnAttachToParent(RefPtr<NG::NavigationStack> parent)
{
    auto parentStack = AceType::DynamicCast<CJNavigationStack>(parent);
    if (!parentStack) {
        return;
    }

    dataSourceObj_->SetParent(parentStack->GetDataSourceObj());
}

void CJNavigationStack::OnDetachFromParent()
{
    dataSourceObj_->SetParent(nullptr);
}

std::vector<std::string> CJNavigationStack::DumpStackInfo() const
{
    return {};
}

void CJNavigationStack::FireNavigationInterception(bool isBefore, const RefPtr<NG::NavDestinationContext>& from,
    const RefPtr<NG::NavDestinationContext>& to, NG::NavigationOperation operation, bool isAnimated)
{}

void CJNavigationStack::FireNavigationModeChange(NG::NavigationMode mode) {}

int32_t CJNavigationStack::GetJsIndexFromNativeIndex(int32_t index)
{
    if (dataSourceObj_->IsEmpty()) {
        return -1;
    }
    return dataSourceObj_->GetIndexFromIndex(index);
}

void CJNavigationStack::MoveIndexToTop(int32_t index)
{
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    dataSourceObj_->MoveIndexToTop(index, true);
}

void CJNavigationStack::UpdatePathInfoIfNeeded(RefPtr<NG::UINode>& uiNode, int32_t index)
{
    auto pathInfo = dataSourceObj_->GetPathInfo(index);
    if (!pathInfo.has_value() || !pathInfo.value().needUpdate) {
        return;
    }
    dataSourceObj_->SetNeedUpdateByIndex(index, false);
    RefPtr<NG::NavDestinationGroupNode> desNode;
    if (!GetNavDestinationNodeInUINode(uiNode, desNode)) {
        return;
    }
    auto pattern = AceType::DynamicCast<NG::NavDestinationPattern>(desNode->GetPattern());
    if (!pattern) {
        return;
    }
    auto name = pathInfo.value().name;
    auto param = pathInfo.value().param;
    auto onPop = pathInfo.value().onPop;
    auto isEntry = pathInfo.value().isEntry;
    auto pathInfoNg = AceType::MakeRefPtr<CJNavPathInfoNG>(name, param, onPop, isEntry);
    pattern->SetNavPathInfo(pathInfoNg);
}

void CJNavigationStack::RecoveryNavigationStack()
{
    navPathList_ = preNavPathList_;
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    std::vector<CJNavPathInfo> pathArray;
    for (int32_t index = 0; index < static_cast<int32_t>(navPathList_.size()); index++) {
        auto node = navPathList_[index].second;
        auto navDestinationGroupNode =
            AceType::DynamicCast<NG::NavDestinationGroupNode>(NG::NavigationGroupNode::GetNavDestinationNode(node));
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
        CJNavPathInfo item = CreatePathInfoWithNecessaryProperty(context);
        pathArray.push_back(item);
    }
    dataSourceObj_->SetPathArray(pathArray);
}

CJNavPathInfo CJNavigationStack::CreatePathInfoWithNecessaryProperty(const RefPtr<NG::NavDestinationContext>& context)
{
    auto pathInfo = CJNavPathInfo();
    auto cjPathInfo = AceType::DynamicCast<CJNavPathInfoNG>(context->GetNavPathInfo());

    pathInfo.name = cjPathInfo->GetName();
    pathInfo.index = context->GetIndex();
    pathInfo.navDestinationId = std::to_string(context->GetNavDestinationId());
    pathInfo.isEntry = cjPathInfo->GetIsEntry();
    pathInfo.param = cjPathInfo->GetParam();
    pathInfo.onPop = cjPathInfo->GetOnPop();
    return pathInfo;
}

bool CJNavigationStack::NeedBuildNewInstance(int32_t index)
{
    auto pathInfo = dataSourceObj_->GetPathInfo(index);
    if (!pathInfo.has_value()) {
        return false;
    }
    return pathInfo.value().needBuildNewInstance;
}

void CJNavigationStack::SetNeedBuildNewInstance(int32_t index, bool need)
{
    dataSourceObj_->SetNeedBuildNewInstanceByIndex(index, need);
}

void CJNavigationStack::SetIsEntryByIndex(int32_t index, bool isEntry)
{
    dataSourceObj_->SetIsEntryByIndex(index, isEntry);
}

std::string CJNavigationStack::GetStringifyParamByIndex(int32_t index) const
{
    auto pathInfo = dataSourceObj_->GetPathInfo(index);
    if (!pathInfo.has_value()) {
        return "undefined";
    }
    return dataSourceObj_->GetParamByIndex(index);
}

void CJNavigationStack::SetPathArray(const std::vector<NG::NavdestinationRecoveryInfo>& navdestinationsInfo)
{
    std::vector<CJNavPathInfo> newPathArray;
    for (int32_t index = 0; index < static_cast<int32_t>(navdestinationsInfo.size()); ++index) {
        auto infoName = navdestinationsInfo[index].name;
        CJNavPathInfo newPathInfo = CJNavPathInfo();
        newPathInfo.name = infoName;
        newPathArray.push_back(newPathInfo);
    }
    dataSourceObj_->SetPathArray(newPathArray);
}

bool CJNavigationStack::IsFromRecovery(int32_t index)
{
    auto pathInfo = dataSourceObj_->GetPathInfo(index);
    if (!pathInfo.has_value()) {
        return false;
    }
    return pathInfo.value().fromRecovery;
}

void CJNavigationStack::SetFromRecovery(int32_t index, bool fromRecovery)
{
    dataSourceObj_->SetFromRecoveryByIndex(index, fromRecovery);
}

int32_t CJNavigationStack::GetRecoveredDestinationMode(int32_t index)
{
    auto pathInfo = dataSourceObj_->GetPathInfo(index);
    if (!pathInfo.has_value()) {
        return -1;
    }
    return pathInfo.value().mode;
}

void CJNavigationStack::SetRecoveryFromReplaceDestination(int32_t index, bool value)
{
    dataSourceObj_->SetRecoveryFromReplaceDestinationByIndex(index, value);
}

bool CJNavigationStack::CheckIsReplacedDestination(int32_t index, std::string& replacedName, int32_t& replacedIndex)
{
    auto pathInfo = dataSourceObj_->GetPathInfo(index);
    if (!pathInfo.has_value()) {
        return false;
    }
    return true;
}
} // namespace OHOS::Ace::Framework
