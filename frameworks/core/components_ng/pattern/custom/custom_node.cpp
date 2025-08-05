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

#include "core/components_ng/pattern/custom/custom_node.h"

#include "base/log/ace_checker.h"
#include "base/log/ace_performance_check.h"
#include "base/log/ace_performance_monitor.h"
#include "base/log/dump_log.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
RefPtr<CustomNode> CustomNode::CreateCustomNode(int32_t nodeId, const std::string& viewKey)
{
    auto node = MakeRefPtr<CustomNode>(nodeId, viewKey);
    ElementRegister::GetInstance()->AddUINode(node);
    return node;
}

void CustomNode::Build(std::shared_ptr<std::list<ExtraInfo>> extraInfos)
{
    Render();
    if (extraInfos) {
        extraInfos_ = *extraInfos;
    }
    UINode::Build(extraInfos);
}

bool CustomNode::Render(int64_t deadline)
{
    // NOTE: this function will be re-enter, we need backup needMarkParent_ first and restore it later.
    bool needMarkParentBak = needMarkParent_;
    needMarkParent_ = false;
    if (renderFunction_) {
        RenderFunction renderFunction = nullptr;
        std::swap(renderFunction, renderFunction_);
        if (!CheckFireOnAppear()) {
            ACE_SCOPED_TRACE("CustomNode:OnAppear");
            FireOnAppear();
            if (deadline > 0 && GetSysTimestamp() > deadline) {
                std::swap(renderFunction, renderFunction_);
                return false;
            }
        }
        {
            int32_t id = -1;
            if (SystemProperties::GetAcePerformanceMonitorEnabled()) {
                id = Container::CurrentId();
            }
            COMPONENT_CREATION_DURATION(id);
            std::string reuseId = GetReuseId().empty() ? "-1" : GetReuseId();
            std::string parentInfo = "-1";
            if (SystemProperties::GetDynamicDetectionTraceEnabled()) {
                auto customParent = FindParentCustomNode();
                if (customParent) {
                    parentInfo = customParent->GetJSViewName() + "[" + std::to_string(customParent->GetId()) + "]";
                }
            }
            ACE_SCOPED_TRACE(
                "CustomNode:BuildItem [%s][self:%d][parent:%d][frameRound:%d][reuseId:%s][parentCustomNode:%s]",
                GetJSViewName().c_str(), GetId(), GetParent() ? GetParent()->GetId() : 0,
                prebuildFrameRounds_, reuseId.c_str(), parentInfo.c_str());
            ScopedViewStackProcessor scopedViewStackProcessor(prebuildViewStackProcessor_);
            auto parent = GetParent();
            bool parentNeedExportTexture = parent ? parent->IsNeedExportTexture() : false;
            ViewStackProcessor::GetInstance()->SetIsExportTexture(parentNeedExportTexture || IsNeedExportTexture());
            bool isTimeout = false;
            auto child = renderFunction(deadline, isTimeout);
            if (isTimeout) {
                prebuildFrameRounds_++;
                std::swap(renderFunction, renderFunction_);
                scopedViewStackProcessor.SwapViewStackProcessor(prebuildViewStackProcessor_);
                return false;
            }
            if (child) {
                child->MountToParent(Claim(this));
            }
        }
        {
            ACE_SCOPED_TRACE("CustomNode::DidBuild");
            FireDidBuild();
        }
    }
    {
        FireRecycleRenderFunc();
    }
    if (AceChecker::IsPerformanceCheckEnabled()) {
        auto child = GetFirstChild();
        if (child) {
            AceScopedPerformanceCheck::UpdateRecordPath(child->GetFilePath());
            AceScopedPerformanceCheck::ReportAllRecord();
        }
    }
    needMarkParent_ = needMarkParentBak;
    return true;
}

void CustomNode::FireCustomDisappear()
{
    if (!CheckFireOnAppear()) {
        FireOnAppear();
        FireDidBuild();
    }
    FireOnDisappear();
    Reset();
    UINode::FireCustomDisappear();
}

// used in HotReload to update root view @Component
void CustomNode::FlushReload()
{
    CHECK_NULL_VOID(completeReloadFunc_);
    Clean();
    renderFunction_ = completeReloadFunc_;
    executeFireOnAppear_ = false;
    Build(nullptr);
}

bool CustomNode::RenderCustomChild(int64_t deadline)
{
    if (GetSysTimestamp() > deadline) {
        return false;
    }
    if (!Render(deadline)) {
        return false;
    }
    return UINode::RenderCustomChild(deadline);
}

void CustomNode::SetJSViewActive(bool active, bool isLazyForEachNode, bool isReuse)
{
    if (GetJsActive() != active) {
        SetJsActive(active);
        FireSetActiveFunc(active, isReuse);
    }
}

void CustomNode::AdjustLayoutWrapperTree(const RefPtr<LayoutWrapperNode>& parent, bool forceMeasure, bool forceLayout)
{
    if (parent->GetHostTag() != V2::TAB_CONTENT_ITEM_ETS_TAG) {
        Render();
        UINode::AdjustLayoutWrapperTree(parent, forceMeasure, forceLayout);
        return;
    }

    if (!renderFunction_ && !HasRecycleRenderFunc()) {
        UINode::AdjustLayoutWrapperTree(parent, forceMeasure, forceLayout);
        return;
    }

    parent->AppendChild(MakeRefPtr<LayoutWrapperNode>(
        [weak = AceType::WeakClaim(this), forceMeasure, forceLayout](RefPtr<LayoutWrapperNode> layoutWrapper) {
            auto customNode = weak.Upgrade();
            CHECK_NULL_VOID(customNode);

            customNode->Render();
            if (customNode->GetChildren().empty()) {
                return;
            }
            auto child = customNode->GetChildren().front();
            while (!InstanceOf<FrameNode>(child)) {
                auto custom = DynamicCast<CustomNode>(child);
                if (custom) {
                    custom->Render();
                }
                auto children = child->GetChildren();
                if (children.empty()) {
                    return;
                }
                child = children.front();
            }
            auto frameChild = DynamicCast<FrameNode>(child);
            CHECK_NULL_VOID(frameChild);
            frameChild->UpdateLayoutWrapper(layoutWrapper, forceMeasure, forceLayout);
        }));
}

RefPtr<LayoutWrapperNode> CustomNode::CreateLayoutWrapper(bool forceMeasure, bool forceLayout)
{
    Build(nullptr);
    return UINode::CreateLayoutWrapper(forceMeasure, forceLayout);
}

void CustomNode::MarkNeedSyncRenderTree(bool needRebuild)
{
    if (needMarkParent_) {
        UINode::MarkNeedSyncRenderTree(needRebuild);
    }
}

RefPtr<UINode> CustomNode::GetFrameChildByIndex(uint32_t index, bool needBuild, bool isCache, bool addToRenderTree)
{
    if (!isCache) {
        SetJSViewActive(true);
    }
    Render();
    return UINode::GetFrameChildByIndex(index, needBuild, isCache, addToRenderTree);
}

void CustomNode::DoSetActiveChildRange(
    int32_t start, int32_t end, int32_t cacheStart, int32_t cacheEnd, bool showCache)
{
    if (showCache) {
        start -= cacheStart;
        end += cacheEnd;
    }
    if (start <= end) {
        if (start > 0 || end < 0) {
            SetActive(false);
            SetJSViewActive(false);
        } else {
            SetJSViewActive(true);
        }
    } else {
        if (end < 0 && start > 0) {
            SetActive(false);
            SetJSViewActive(false);
        } else {
            SetJSViewActive(true);
        }
    }
}

std::unique_ptr<JsonValue> CustomNode::GetStateInspectorInfo()
{
    std::string res = FireOnDumpInspectorFunc();
    TAG_LOGD(AceLogTag::ACE_STATE_MGMT, "ArkUI State Inspector dump info %{public}s", res.c_str());
    auto json = JsonUtil::ParseJsonString(res);
    return json;
}

void CustomNode::DumpComponentInfo(std::unique_ptr<JsonValue>& componentInfo)
{
    DumpLog::GetInstance().AddDesc("ComponentName: " + componentInfo->GetValue("ComponentName")->ToString());
    DumpLog::GetInstance().AddDesc("isV2: " + componentInfo->GetValue("isV2")->ToString());
    DumpLog::GetInstance().AddDesc("isFreezeAllowed: " + \
                                    componentInfo->GetValue("isCompFreezeAllowed_")->ToString());
    DumpLog::GetInstance().AddDesc("isViewActive: " + componentInfo->GetValue("isViewActive_")->ToString());
}

void CustomNode::DumpDecoratorInfo(std::unique_ptr<JsonValue>& decoratorInfo)
{
    int size = decoratorInfo->GetArraySize();

    DumpLog::GetInstance().AddDesc("-----start print decoratorInfo");
    for (int i = 0; i < size; i++) {
        auto decoratorItem = decoratorInfo->GetArrayItem(i);
        DumpLog::GetInstance().AddDesc("decorator:" + decoratorItem->GetValue("decorator")->ToString() + \
                                       " propertyName:" + decoratorItem->GetValue("propertyName")->ToString() + \
                                       " value:" + decoratorItem->GetValue("value")->ToString());
        DumpLog::GetInstance().AddDesc("state Variable id: " + decoratorItem->GetValue("id")->ToString());
        DumpLog::GetInstance().AddDesc("inRenderingElementId: " + \
                                        decoratorItem->GetValue("inRenderingElementId")->ToString());
        DumpLog::GetInstance().AddDesc("dependentElementIds: " + \
                                        decoratorItem->GetValue("dependentElementIds")->ToString());
        if (i < size - 1) {
            DumpLog::GetInstance().AddDesc("------------------------------");
        }
    }
    DumpLog::GetInstance().AddDesc("-----end print decoratorInfo");
}

void CustomNode::DumpInfo()
{
    std::string ret = FireOnDumpInspectorFunc();
    TAG_LOGD(AceLogTag::ACE_STATE_MGMT, "ArkUI DumpInfo %{public}s", ret.c_str());
    if (ret != "") {
        auto json = JsonUtil::ParseJsonString(ret);
        if (json == nullptr || !json->IsValid()) {
            TAG_LOGE(AceLogTag::ACE_STATE_MGMT, "ParseJsonString failed");
            return;
        }
        auto componentInfo = json->GetValue("viewInfo");
        if (componentInfo != nullptr) {
            DumpComponentInfo(componentInfo);
        }
        auto decoratorInfo = json->GetValue("observedPropertiesInfo");
        if (decoratorInfo != nullptr) {
            DumpDecoratorInfo(decoratorInfo);
        }
    }
}

void CustomNode::FireRecycleRenderFunc()
{
    if (HasRecycleRenderFunc()) {
        std::string reuseId = GetReuseId().empty() ? "-1" : GetReuseId();
        std::string parentInfo = "-1";
        if (SystemProperties::GetDynamicDetectionTraceEnabled()) {
            auto customParent = FindParentCustomNode();
            if (customParent) {
                parentInfo = customParent->GetJSViewName() + "[" + std::to_string(customParent->GetId()) + "]";
            }
        }

        ACE_SCOPED_TRACE("CustomNode:BuildRecycle [%s][self:%d][parent:%d][reuseId:%s][parentCustomNode:%s]",
            GetJSViewName().c_str(), GetId(), GetParent() ? GetParent()->GetId() : 0,
            reuseId.c_str(), parentInfo.c_str());
    }

    CustomNodeBase::FireRecycleRenderFunc();
}

RefPtr<CustomNode> CustomNode::FindParentCustomNode() const
{
    auto current = GetParent();
    while (current) {
        auto customParent = DynamicCast<CustomNode>(current);
        if (customParent) {
            return customParent;
        }
        current = current->GetParent();
    }
    return nullptr;
}

void CustomNode::OnDestroyingStateChange(bool isDestroying, bool cleanStatus)
{
    if (isDestroying && cleanStatus) {
        auto context = GetContext();
        CHECK_NULL_VOID(context);
        context->AddPendingDeleteCustomNode(Claim(this));
    }
}
} // namespace OHOS::Ace::NG
