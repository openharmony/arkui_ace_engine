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
}

void CJNavigationStack::Push(const std::string& name, const RefPtr<NG::RouteInfo>& routeInfo)
{
}

void CJNavigationStack::Push(const std::string& name, int32_t index)
{
}

void CJNavigationStack::RemoveName(const std::string& name)
{
}

void CJNavigationStack::RemoveIndex(int32_t index)
{
}

void CJNavigationStack::Clear()
{
}

int32_t CJNavigationStack::GetReplaceValue() const
{
    return dataSourceObj_->GetIsReplace();
}

void CJNavigationStack::UpdateReplaceValue(int32_t isReplace) const
{
    dataSourceObj_->SetIsReplace(isReplace);
}

bool CJNavigationStack::GetAnimatedValue() const
{
    return dataSourceObj_->GetAnimated();
}

void CJNavigationStack::UpdateAnimatedValue(bool animated)
{
    dataSourceObj_->SetAnimated(animated);
}

bool CJNavigationStack::GetDisableAnimation() const
{
    return false;
}

std::vector<std::string> CJNavigationStack::GetAllPathName()
{
    return dataSourceObj_->GetAllPathName();
}

std::vector<int32_t> CJNavigationStack::GetAllPathIndex()
{
    return dataSourceObj_->GetAllPathIndex();
}

void CJNavigationStack::InitNavPathIndex(const std::vector<std::string>& pathNames)
{
    dataSourceObj_->InitNavPathIndex(pathNames);
}

void CJNavigationStack::SetDestinationIdToJsStack(int32_t index, const std::string& navDestinationId)
{
    dataSourceObj_->SetNavDestinationId(index, navDestinationId);
}

bool CJNavigationStack::CreateNodeByIndex(
    int32_t index,
    const WeakPtr<NG::UINode>& customNode,
    RefPtr<NG::UINode>& node)
{
    auto pathInfo = dataSourceObj_->GetPathInfo(index);
    std::string name = pathInfo.name;
    std::string param = pathInfo.param;

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
    const WeakPtr<NG::UINode>& customNode, RefPtr<NG::UINode>& node,
    RefPtr<NG::NavDestinationGroupNode>& desNode)
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
            TAG_LOGI(AceLogTag::ACE_NAVIGATION,
                "router map is invalid, child size is not one: %{public}zu", children.size());
        }
        node = children.front();
    }
    return false;
}

RefPtr<NG::UINode> CJNavigationStack::CreateNodeByRouteInfo(
    const RefPtr<NG::RouteInfo>& routeInfo,
    const WeakPtr<NG::UINode>& node)
{
    return DynamicCast<NG::UINode>(NavDestinationModel::GetInstance()->CreateEmpty());
}

std::string CJNavigationStack::GetRouteParam() const
{
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
{
}

void CJNavigationStack::FireNavigationModeChange(NG::NavigationMode mode)
{
}

int32_t CJNavigationStack::GetJsIndexFromNativeIndex(int32_t index)
{
    return -1;
}

void CJNavigationStack::MoveIndexToTop(int32_t index)
{
}

void CJNavigationStack::UpdatePathInfoIfNeeded(RefPtr<NG::UINode>& uiNode, int32_t index)
{
    return;
}

void CJNavigationStack::RecoveryNavigationStack()
{
}

bool CJNavigationStack::NeedBuildNewInstance(int32_t index)
{
    return false;
}

void CJNavigationStack::SetNeedBuildNewInstance(int32_t index, bool need)
{
}

void CJNavigationStack::SetIsEntryByIndex(int32_t index, bool isEntry)
{
}

std::string CJNavigationStack::GetStringifyParamByIndex(int32_t index) const
{
    return "undefined";
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
    return false;
}

void CJNavigationStack::SetFromRecovery(int32_t index, bool fromRecovery)
{
}

int32_t CJNavigationStack::GetRecoveredDestinationMode(int32_t index)
{
    return -1;
}

void CJNavigationStack::SetRecoveryFromReplaceDestination(int32_t index, bool value)
{
}

bool CJNavigationStack::CheckIsReplacedDestination(int32_t index, std::string& replacedName, int32_t& replacedIndex)
{
    return false;
}
}
