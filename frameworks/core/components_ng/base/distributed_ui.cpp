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

#include "core/components_ng/base/distributed_ui.h"

#include <chrono>
#include <unordered_map>

#include "base/ressched/ressched_report.h"
#include "core/components_ng/pattern/common_view/common_view_pattern.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/flex/flex_layout_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/tabs/tab_bar_pattern.h"
#include "core/components_ng/pattern/tabs/tab_content_node.h"
#include "core/components_ng/pattern/tabs/tab_content_pattern.h"
#include "core/components_ng/pattern/tabs/tabs_model_ng.h"
#include "core/components_ng/pattern/tabs/tabs_pattern.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/syntax/for_each_node.h"
#include "core/components_ng/syntax/if_else_node.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"
#include "core/components_ng/syntax/syntax_item.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
const char DISTRIBUTE_UI_TYPE[] = "$type";
const char DISTRIBUTE_UI_ID[] = "$ID";
const char DISTRIBUTE_UI_ATTRS[] = "$attrs";
const char DISTRIBUTE_UI_PARENT[] = "$parent";
const char DISTRIBUTE_UI_DEPTH[] = "$depth";
const char DISTRIBUTE_UI_OPERATION[] = "$op";

const int32_t HANDLE_UPDATE_PER_VSYNC = 1;

void RestorePageNode(const RefPtr<NG::FrameNode>& pageNode)
{
    auto pagePattern = pageNode->GetPattern<NG::PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    pagePattern->SetOnBackPressed([]() { return true; });
}
} // namespace

SerializeableObjectArray DistributedUI::DumpUITree()
{
    LOGD("UITree interface start");
#ifdef ACE_DEBUG_LOG
    auto timeStart = std::chrono::high_resolution_clock::now();
#endif

    ResetDirtyNodes();

    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, SerializeableObjectArray());
    auto pageRootNode = currentPageId_ ? context->GetStageManager()->GetPageById(currentPageId_)
                                       : context->GetStageManager()->GetLastPage();
    CHECK_NULL_RETURN(pageRootNode, SerializeableObjectArray());
    LOGD("UITree Dump page: %{public}d", pageRootNode->GetPageId());

    SerializeableObjectArray objectArray;
    auto children = pageRootNode->GetChildren();
    for (const auto& uiNode : children) {
        DumpTreeInner(uiNode, objectArray, 1);
    }

    status_ = StateMachine::SOURCE_START;

#ifdef ACE_DEBUG_LOG
    auto timeEnd = std::chrono::high_resolution_clock::now();
    LOGD("UITree process use %{public}lld ms",
        static_cast<long long>(std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count()));
#endif
    return objectArray;
}

void DistributedUI::SubscribeUpdate(const std::function<void(int32_t, SerializeableObjectArray&)>& onUpdate)
{
    LOGD("UITree Subscribe Update");
    onUpdateCb_ = std::move(onUpdate);
}

void DistributedUI::UnSubscribeUpdate()
{
    onUpdateCb_ = nullptr;
    status_ = StateMachine::STOP;
}

void DistributedUI::ProcessSerializeableInputEvent(const SerializeableObjectArray& array)
{
    LOGD("UITree interface start");
#ifdef ACE_DEBUG_LOG
    auto timeStart = std::chrono::high_resolution_clock::now();
#endif

    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);

    TouchEvent event;
    std::unique_ptr<JsonValue>& json = (std::unique_ptr<JsonValue>&)array.front();
    event.FromJson(json);
    bool isSubPipe = json->GetBool("sub");

    context->OnTouchEvent(event, isSubPipe);

#ifdef ACE_DEBUG_LOG
    auto timeEnd = std::chrono::high_resolution_clock::now();
    LOGD("UITree process use %{public}lld ms",
        static_cast<long long>(std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count()));
#endif
}

void DistributedUI::RestoreUITree(const SerializeableObjectArray& array)
{
    LOGD("UITree interface start");
#ifdef ACE_DEBUG_LOG
    auto timeStart = std::chrono::high_resolution_clock::now();
#endif

    status_ = StateMachine::SINK_START;
    RestoreUITreeInner(array);

#ifdef ACE_DEBUG_LOG
    auto timeEnd = std::chrono::high_resolution_clock::now();
    LOGD("UITree process use %{public}lld ms",
        static_cast<long long>(std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count()));
#endif
}

void DistributedUI::UpdateUITree(const SerializeableObjectArray& array)
{
    LOGD("UITree interface start");
    if (status_ != StateMachine::SINK_START) {
        LOGE("UpdateUITree failed. status=%{public}d", static_cast<uint8_t>(status_));
        return;
    }
    pendingUpdates_.emplace_back(std::move((SerializeableObjectArray&)array));

    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->RequestFrame();
}

void DistributedUI::SubscribeInputEventProcess(const std::function<void(SerializeableObjectArray&)>& onEvent)
{
    LOGD("UITree Subscribe Event");
    onEventCb_ = std::move(onEvent);
}

void DistributedUI::UnSubscribeInputEventProcess()
{
    onEventCb_ = nullptr;
    status_ = StateMachine::STOP;
    pendingUpdates_.clear();
}

void DistributedUI::AddDeletedNode(int32_t nodeId)
{
    if (!ReadyToDumpUpdate()) {
        return;
    }
    deletedNodes_.emplace(nodeId);
}

void DistributedUI::AddNewNode(int32_t nodeId)
{
    if (!ReadyToDumpUpdate()) {
        return;
    }
    newNodes_.emplace(nodeId);
}

void DistributedUI::AddDirtyCustomNode(int32_t nodeId)
{
    if (!ReadyToDumpUpdate()) {
        return;
    }
    dirtyCustomNodes_.emplace(nodeId);
}

void DistributedUI::AddDirtyRenderNode(int32_t nodeId)
{
    if (!ReadyToDumpUpdate()) {
        return;
    }
    dirtyRenderNodes_.emplace(nodeId);
}

void DistributedUI::AddDirtyLayoutNode(int32_t nodeId)
{
    if (!ReadyToDumpUpdate()) {
        return;
    }
    dirtyLayoutNodes_.emplace(nodeId);
}

void DistributedUI::OnTreeUpdate()
{
    if (!ReadyToDumpUpdate()) {
        return;
    }

    LOGD("UITree interface start");
#ifdef ACE_DEBUG_LOG
    auto timeStart = std::chrono::high_resolution_clock::now();
#endif

    DistributedUI::UpdateType updateType;
    SerializeableObjectArray update;
    if (pageChangeFlag_) {
        LOGD("UITree page changed. dump currentPage:%{public}d", currentPageId_);
        pageChangeFlag_ = false;
        ResetDirtyNodes();
        update = DumpUITree();
        updateType = UpdateType::PAGE_CHANGE;
    } else {
        update = DumpUpdate();
        if (update.empty()) {
            LOGD("UITree no need to update");
            return;
        }
        updateType = UpdateType::PAGE_UPDATE;
    }

#ifdef ACE_DEBUG_LOG
    auto timeEnd = std::chrono::high_resolution_clock::now();
    LOGD("UITree process use %{public}lld ms",
        static_cast<long long>(std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count()));
    timeStart = timeEnd;
#endif

    if (onUpdateCb_) {
        onUpdateCb_(updateType, update);
    }

#ifdef ACE_DEBUG_LOG
    timeEnd = std::chrono::high_resolution_clock::now();
    LOGD("UITree send process use %{public}lld ms",
        static_cast<long long>(std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count()));
#endif
}

void DistributedUI::OnPageChanged(int32_t pageId)
{
    if (status_ == StateMachine::SOURCE_START) {
        pageChangeFlag_ = true;
    }
    currentPageId_ = pageId;
    LOGD("UITree OnPageChanged to %{public}d", pageId);
}

int32_t DistributedUI::GetCurrentPageId()
{
    return currentPageId_;
}

void DistributedUI::BypassEvent(const TouchEvent& point, bool isSubPipe)
{
    LOGD("UITree interface start");
#ifdef ACE_DEBUG_LOG
    auto timeStart = std::chrono::high_resolution_clock::now();
#endif

    std::unique_ptr<JsonValue> json = NodeObject::Create();
    point.ToJsonValue(json);
    json->Put("sub", isSubPipe);
    SerializeableObjectArray eventArray;
    eventArray.push_back(std::move((std::unique_ptr<NodeObject>&)json));

#ifdef ACE_DEBUG_LOG
    auto timeEnd = std::chrono::high_resolution_clock::now();
    LOGD("UITree process use %{public}lld ms",
        static_cast<long long>(std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count()));
    timeStart = timeEnd;
#endif

    if (onEventCb_) {
        onEventCb_(eventArray);
    }

#ifdef ACE_DEBUG_LOG
    timeEnd = std::chrono::high_resolution_clock::now();
    LOGD("UITree send process use %{public}lld ms",
        static_cast<long long>(std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count()));
#endif
}

bool DistributedUI::IsSinkMode()
{
    if (onEventCb_ && status_ == StateMachine::SINK_START) {
        return true;
    }
    return false;
}

void DistributedUI::ApplyOneUpdate()
{
    LOGD("UITree interface start");
#ifdef ACE_DEBUG_LOG
    auto timeStart = std::chrono::high_resolution_clock::now();
#endif

    LOGD("UITree pendingUpdates.size=%{public}zu", pendingUpdates_.size());
    for (int i = 0; i < HANDLE_UPDATE_PER_VSYNC; i++) {
        if (pendingUpdates_.empty()) {
            return;
        }
        ResSchedReport::GetInstance().ResSchedDataReport("click");
        auto update = std::move(pendingUpdates_.front());
        pendingUpdates_.pop_front();
        UpdateUITreeInner(update);
    }

#ifdef ACE_DEBUG_LOG
    auto timeEnd = std::chrono::high_resolution_clock::now();
    LOGD("UITree process use %{public}lld ms",
        static_cast<long long>(std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count()));
#endif
}

void DistributedUI::DumpDirtyRenderNodes(SerializeableObjectArray& objectArray)
{
    for (const auto& nodeId : dirtyRenderNodes_) {
        auto node = ElementRegister::GetInstance()->GetUINodeById(nodeId);
        if (!node || !IsInCurrentPage(node, currentPageId_) || node->GetTag() == V2::PAGE_ETS_TAG) {
            LOGE("UITree |ERROR| Node not found or not in current page. %{public}d", nodeId);
            continue;
        }
        if (IsNewNode(nodeId)) {
            continue;
        }
        LOGD("UITree dirty Render node: %{public}s%{public}d", node->GetTag().c_str(), nodeId);
        auto nodeObject = NodeObject::Create();
        DumpNode(node, -1, OperationType::OP_MODIFY, nodeObject);
        if (IsRecordHash(nodeId, nodeObject->Hash())) {
            objectArray.push_back(std::move(nodeObject));
        }
    }
}

void DistributedUI::DumpDirtyLayoutNodes(SerializeableObjectArray& objectArray)
{
    for (const auto& nodeId : dirtyLayoutNodes_) {
        auto node = ElementRegister::GetInstance()->GetUINodeById(nodeId);
        if (!node || !IsInCurrentPage(node, currentPageId_)) {
            LOGE("UITree Node not found or not in current page. %{public}d", nodeId);
            continue;
        }
        if (IsNewNode(nodeId)) {
            continue;
        }
        LOGD("UITree dirty Layout node: %{public}s%{public}d", node->GetTag().c_str(), nodeId);
        auto nodeObject = NodeObject::Create();
        DumpNode(node, -1, OperationType::OP_MODIFY, nodeObject);
        if (IsRecordHash(nodeId, nodeObject->Hash())) {
            objectArray.push_back(std::move(nodeObject));
        }
    }
}

void DistributedUI::DumpNewNodes(SerializeableObjectArray& objectArray)
{
    for (const auto& nodeId : newNodes_) {
        auto node = ElementRegister::GetInstance()->GetUINodeById(nodeId);
        if (node) {
            LOGD("UITree node");
        }
        if (!node || !IsInCurrentPage(node, currentPageId_)) {
            LOGE("UITree |ERROR| Node not found or not in current page. %{public}d", nodeId);
            continue;
        }
        LOGD("UITree new node: %{public}s%{public}d", node->GetTag().c_str(), nodeId);
        auto nodeObject = NodeObject::Create();
        DumpNode(node, -1, OperationType::OP_ADD, nodeObject);
        AddNodeHash(nodeId, nodeObject->Hash());
        objectArray.push_back(std::move(nodeObject));
    }
}

void DistributedUI::DumpDelNodes(SerializeableObjectArray& objectArray)
{
    for (const auto& nodeId : deletedNodes_) {
        LOGD("UITree del node: %{public}d", nodeId);
        auto nodeObject = NodeObject::Create();
        nodeObject->Put(DISTRIBUTE_UI_ID, nodeId);
        nodeObject->Put(DISTRIBUTE_UI_OPERATION, static_cast<int32_t>(OperationType::OP_DELETE));
        objectArray.push_back(std::move(nodeObject));
        DelNodeHash(nodeId);
    }
}

SerializeableObjectArray DistributedUI::DumpUpdate()
{
    if (newNodes_.size() + dirtyRenderNodes_.size() + deletedNodes_.size() + dirtyLayoutNodes_.size() == 0) {
        return SerializeableObjectArray();
    }
#ifdef ACE_DEBUG_LOG
    auto timeStart = std::chrono::high_resolution_clock::now();
#endif
    SerializeableObjectArray objectArray;

    DumpDirtyRenderNodes(objectArray);
    DumpDirtyLayoutNodes(objectArray);
    DumpNewNodes(objectArray);
    DumpDelNodes(objectArray);
    ResetDirtyNodes();

#ifdef ACE_DEBUG_LOG
    auto timeEnd = std::chrono::high_resolution_clock::now();
    LOGD("UITree process use %{public}lld ms",
        static_cast<long long>(std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count()));
#endif
    return objectArray;
}

void DistributedUI::ResetDirtyNodes()
{
    newNodes_.clear();
    dirtyRenderNodes_.clear();
    deletedNodes_.clear();
    dirtyLayoutNodes_.clear();
}

bool DistributedUI::IsNewNode(int32_t nodeId)
{
    if (newNodes_.find(nodeId) != newNodes_.end()) {
        return true;
    }
    return false;
}

bool DistributedUI::ReadyToDumpUpdate()
{
    if (onUpdateCb_ && status_ == StateMachine::SOURCE_START) {
        return true;
    }
    return false;
}

void DistributedUI::SetIdMapping(int32_t srcNodeId, int32_t sinkNodeId)
{
    if (nodeIdMapping_.count(srcNodeId)) {
        LOGW("UITree |WARN| has mapping [%{public}d, %{public}d]", srcNodeId, nodeIdMapping_[srcNodeId]);
    }
    nodeIdMapping_[srcNodeId] = sinkNodeId;
    LOGD("UITree set mapping [%{public}d, %{public}d]", srcNodeId, nodeIdMapping_[srcNodeId]);
}

int32_t DistributedUI::GetIdMapping(int32_t srcNodeId)
{
    int32_t sinkNodeId = ElementRegister::UndefinedElementId;
    if (nodeIdMapping_.count(srcNodeId)) {
        sinkNodeId = nodeIdMapping_[srcNodeId];
    }
    LOGD("UITree get mapping [%{public}d, %{public}d]", srcNodeId, sinkNodeId);
    return sinkNodeId;
}

void DistributedUI::AddNodeHash(int32_t nodeId, std::size_t hashValue)
{
    nodeHashs_[nodeId] = hashValue;
    LOGD("UITree add hash [%{public}d, %{public}zu]", nodeId, nodeHashs_.at(nodeId));
}

void DistributedUI::DelNodeHash(int32_t nodeId)
{
    if (nodeHashs_.count(nodeId)) {
        LOGD("UITree del hash [%{public}d, %{public}zu]", nodeId, nodeHashs_.at(nodeId));
        nodeHashs_.erase(nodeId);
    }
}

bool DistributedUI::IsRecordHash(int32_t nodeId, std::size_t hashValue)
{
    if (nodeHashs_.count(nodeId) && nodeHashs_.at(nodeId) == hashValue) {
        return false;
    }
    AddNodeHash(nodeId, hashValue);
    return true;
}

void DistributedUI::DumpNode(
    const RefPtr<NG::UINode>& node, int depth, OperationType op, std::unique_ptr<NodeObject>& nodeObject)
{
    nodeObject->Put(DISTRIBUTE_UI_TYPE, node->GetTag().c_str());
    nodeObject->Put(DISTRIBUTE_UI_ID, node->GetId());
    auto parent = node->GetParent();
    if (!parent) {
        LOGE("UITree |ERROR| parent not found %{public}d", node->GetId());
        nodeObject->Put(DISTRIBUTE_UI_PARENT, -1);
    } else {
        nodeObject->Put(DISTRIBUTE_UI_PARENT, parent->GetId());
    }
    nodeObject->Put(DISTRIBUTE_UI_DEPTH, depth);
    nodeObject->Put(DISTRIBUTE_UI_OPERATION, static_cast<int32_t>(op));

    std::unique_ptr<JsonValue> childObject = NodeObject::Create();
    node->ToJsonValue(childObject);
    nodeObject->Put(DISTRIBUTE_UI_ATTRS, (std::unique_ptr<NodeObject>&)childObject);
}

void DistributedUI::DumpTreeInner(const RefPtr<NG::UINode>& node, SerializeableObjectArray& objectArray, int depth)
{
    auto nodeObject = NodeObject::Create();
    DumpNode(node, depth, OperationType::OP_ADD, nodeObject);
    LOGD("UITree EstimateBufferSize=%{public}d", nodeObject->EstimateBufferSize());
    AddNodeHash(node->GetId(), nodeObject->Hash());
    objectArray.push_back(std::move(nodeObject));

    auto children = node->GetChildren();
    for (const auto& uiNode : children) {
        DumpTreeInner(uiNode, objectArray, depth + 1);
    }
}

RefPtr<UINode> DistributedUI::RestoreNode(const std::unique_ptr<NodeObject>& nodeObject)
{
    static const std::unordered_map<std::string, std::function<RefPtr<UINode>(const std::string&, int32_t)>>
        nodeCreate {
            { V2::JS_VIEW_ETS_TAG, [](const std::string& type,
                                       int32_t nodeId) { return NG::CustomNode::CreateCustomNode(nodeId, type); } },
            { V2::TEXT_ETS_TAG,
                [](const std::string& type, int32_t nodeId) {
                    return FrameNode::GetOrCreateFrameNode(
                        type, nodeId, []() { return AceType::MakeRefPtr<TextPattern>(); });
                } },
            { V2::COLUMN_ETS_TAG,
                [](const std::string& type, int32_t nodeId) {
                    return FrameNode::GetOrCreateFrameNode(
                        type, nodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
                } },
            { V2::ROW_ETS_TAG,
                [](const std::string& type, int32_t nodeId) {
                    return FrameNode::GetOrCreateFrameNode(
                        type, nodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
                } },
            { V2::LIST_ITEM_ETS_TAG,
                [](const std::string& type, int32_t nodeId) {
                    return FrameNode::GetOrCreateFrameNode(type, nodeId,
                        []() { return AceType::MakeRefPtr<ListItemPattern>(nullptr, V2::ListItemStyle::NONE); });
                } },
            { V2::LIST_ETS_TAG,
                [](const std::string& type, int32_t nodeId) {
                    return FrameNode::GetOrCreateFrameNode(
                        type, nodeId, []() { return AceType::MakeRefPtr<ListPattern>(); });
                } },
            { V2::STACK_ETS_TAG,
                [](const std::string& type, int32_t nodeId) {
                    return FrameNode::GetOrCreateFrameNode(
                        type, nodeId, []() { return AceType::MakeRefPtr<StackPattern>(); });
                } },
            { V2::IMAGE_ETS_TAG,
                [](const std::string& type, int32_t nodeId) {
                    return FrameNode::GetOrCreateFrameNode(
                        type, nodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
                } },
            { V2::FLEX_ETS_TAG,
                [](const std::string& type, int32_t nodeId) {
                    return FrameNode::GetOrCreateFrameNode(
                        type, nodeId, []() { return AceType::MakeRefPtr<FlexLayoutPattern>(); });
                } },
            { V2::TABS_ETS_TAG,
                [](const std::string& type, int32_t nodeId) {
                    return TabsModelNG::GetOrCreateTabsNode(
                        type, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
                } },
            { V2::TAB_BAR_ETS_TAG,
                [](const std::string& type, int32_t nodeId) {
                    return FrameNode::GetOrCreateFrameNode(
                        type, nodeId, []() { return AceType::MakeRefPtr<TabBarPattern>(nullptr); });
                } },
            { V2::SWIPER_ETS_TAG,
                [](const std::string& type, int32_t nodeId) {
                    return FrameNode::GetOrCreateFrameNode(
                        type, nodeId, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
                } },
            { V2::TAB_CONTENT_ITEM_ETS_TAG,
                [](const std::string& type, int32_t nodeId) {
                    return TabContentNode::GetOrCreateTabContentNode(
                        type, nodeId, []() { return AceType::MakeRefPtr<TabContentPattern>(nullptr); });
                } },
            { V2::COMMON_VIEW_ETS_TAG,
                [](const std::string& type, int32_t nodeId) {
                    return FrameNode::GetOrCreateFrameNode(
                        type, nodeId, []() { return AceType::MakeRefPtr<CommonViewPattern>(); });
                } },
            { V2::JS_FOR_EACH_ETS_TAG,
                [](const std::string& type, int32_t nodeId) { return ForEachNode::GetOrCreateForEachNode(nodeId); } },
            { V2::JS_SYNTAX_ITEM_ETS_TAG,
                [](const std::string& type, int32_t nodeId) { return SyntaxItem::CreateSyntaxItemNode(type); } },
            { V2::JS_LAZY_FOR_EACH_ETS_TAG,
                [](const std::string& type, int32_t nodeId) {
                    return LazyForEachNode::GetOrCreateLazyForEachNode(nodeId, nullptr);
                } },
            { V2::JS_IF_ELSE_ETS_TAG,
                [](const std::string& type, int32_t nodeId) { return IfElseNode::GetOrCreateIfElseNode(nodeId); } },
            { V2::TEXTINPUT_ETS_TAG,
                [](const std::string& type, int32_t nodeId) {
                    return FrameNode::GetOrCreateFrameNode(
                        type, nodeId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
                } },
            { V2::DIVIDER_ETS_TAG,
                [](const std::string& type, int32_t nodeId) {
                    return FrameNode::GetOrCreateFrameNode(
                        type, nodeId, []() { return AceType::MakeRefPtr<DividerPattern>(); });
                } },
        };

    auto type = nodeObject->GetString(DISTRIBUTE_UI_TYPE);
    auto srcNodeId = nodeObject->GetInt(DISTRIBUTE_UI_ID);
    auto srcParentNodeId = nodeObject->GetInt(DISTRIBUTE_UI_PARENT);
    auto depth = nodeObject->GetInt(DISTRIBUTE_UI_DEPTH);
    LOGD("UITree process type %{public}s id %{public}d pid %{public}d depth %{public}d", type.c_str(), srcNodeId,
        srcParentNodeId, depth);

    if (!nodeCreate.count(type)) {
        LOGE("UITree |ERROR| found no type %{public}s id %{public}d pid %{public}d depth %{public}d", type.c_str(),
            srcNodeId, srcParentNodeId, depth);
        return nullptr;
    }

    if (!nodeObject->Contains(DISTRIBUTE_UI_ATTRS)) {
        LOGE("UITree |ERROR| found no attrs");
        return nullptr;
    }
    auto attrs = nodeObject->GetValue(DISTRIBUTE_UI_ATTRS);

    auto sinkNodeId = srcNodeId == -1 ? -1 : ElementRegister::GetInstance()->MakeUniqueId();
    if (ElementRegister::GetInstance()->GetUINodeById(sinkNodeId)) {
        LOGE("UITree |ERROR| uiNode exist! id: %{public}d", sinkNodeId);
        return nullptr;
    }

    RefPtr<UINode> uiNode = nullptr;
    if (type == V2::JS_VIEW_ETS_TAG) {
        uiNode = nodeCreate.at(type)(attrs->GetString("viewKey"), sinkNodeId);
    } else if (type == V2::JS_SYNTAX_ITEM_ETS_TAG) {
        uiNode = nodeCreate.at(type)(attrs->GetString("key"), sinkNodeId);
    } else {
        uiNode = nodeCreate.at(type)(type, sinkNodeId);
    }
    if (!uiNode) {
        LOGE("UITree |ERROR| node create failed!");
        return nullptr;
    }

    SetIdMapping(srcNodeId, uiNode->GetId());
    uiNode->FromJson(attrs);

    if (type == V2::IMAGE_ETS_TAG) {
        AceType::DynamicCast<NG::FrameNode>(uiNode)->MarkModifyDone();
    }

    return uiNode;
}

void DistributedUI::AttachToTree(
    RefPtr<UINode> root, RefPtr<UINode> uiNode, const std::unique_ptr<NodeObject>& nodeObject)
{
    auto depth = nodeObject->GetInt(DISTRIBUTE_UI_DEPTH);
    auto sinkNodeId = uiNode->GetId();
    auto sinkParentNodeId = GetIdMapping(nodeObject->GetInt(DISTRIBUTE_UI_PARENT));
    LOGD("UITree process [%{public}d, %{public}d, %{public}d]", depth, sinkNodeId, sinkParentNodeId);

    if (depth == 1) {
        LOGI("UITree attach %{public}d to root", sinkNodeId);
        root->AddChild(uiNode);
    } else {
        LOGI("UITree attach %{public}d to %{public}d", sinkNodeId, sinkParentNodeId);
        auto parent = ElementRegister::GetInstance()->GetUINodeById(sinkParentNodeId);
        if (!parent) {
            LOGE("UITree |ERROR| found no sinkParentNodeId %{public}d", sinkParentNodeId);
            return;
        }
        parent->AddChild(uiNode);
    }
}

void DistributedUI::AddNode(const std::unique_ptr<NodeObject>& nodeObject, RefPtr<FrameNode> pageRootNode)
{
    auto uiNode = RestoreNode(nodeObject);
    if (!uiNode) {
        LOGE("UITree |ERROR| Frame Node is Null.");
        return;
    }
    LOGD("UITree new node: %{public}s%{public}d", uiNode->GetTag().c_str(), uiNode->GetId());
    AttachToTree(pageRootNode, uiNode, nodeObject);
}

void DistributedUI::ModNode(const std::unique_ptr<NodeObject>& nodeObject)
{
    auto sinkNodeId = GetIdMapping(nodeObject->GetInt(DISTRIBUTE_UI_ID));
    auto sinkNode = ElementRegister::GetInstance()->GetUINodeById(sinkNodeId);
    if (!sinkNode) {
        LOGE("UITree |ERROR| node not found %{public}d", sinkNodeId);
        return;
    }
    LOGD("UITree modify node: %{public}s%{public}d", sinkNode->GetTag().c_str(), sinkNode->GetId());
    auto attrs = nodeObject->GetValue(DISTRIBUTE_UI_ATTRS);
    sinkNode->FromJson(attrs);
    sinkNode->MarkDirtyNode();
}

void DistributedUI::DelNode(const std::unique_ptr<NodeObject>& nodeObject)
{
    auto sinkNodeId = GetIdMapping(nodeObject->GetInt(DISTRIBUTE_UI_ID));
    LOGD("UITree delete node: %{public}d", sinkNodeId);
    auto sinkNode = ElementRegister::GetInstance()->GetUINodeById(sinkNodeId);
    if (!sinkNode) {
        LOGE("UITree |ERROR| node not found %{public}d", sinkNodeId);
        return;
    }
    auto parent = sinkNode->GetParent();
    if (!parent) {
        LOGE("UITree |ERROR| parent node not found.");
        return;
    }
    parent->RemoveChild(sinkNode);
}

void DistributedUI::UpdateUITreeInner(SerializeableObjectArray& nodeArray)
{
#ifdef ACE_DEBUG_LOG
    auto timeStart = std::chrono::high_resolution_clock::now();
#endif

    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto pageRootNode = context->GetStageManager()->GetLastPage();
    CHECK_NULL_VOID(pageRootNode);

    LOGD("UITree Update %{public}zu nodes", nodeArray.size());
    for (const auto& nodeObject : nodeArray) {
        OperationType op = static_cast<OperationType>(nodeObject->GetInt(DISTRIBUTE_UI_OPERATION));
        if (op == OperationType::OP_ADD) {
            AddNode((std::unique_ptr<NodeObject>&)nodeObject, pageRootNode);
        } else if (op == OperationType::OP_MODIFY) {
            ModNode((std::unique_ptr<NodeObject>&)nodeObject);
        } else if (op == OperationType::OP_DELETE) {
            DelNode((std::unique_ptr<NodeObject>&)nodeObject);
        }
    }

    context->RequestFrame();
#ifdef ACE_DEBUG_LOG
    auto timeEnd = std::chrono::high_resolution_clock::now();
    LOGD("UITree process use %{public}lld ms",
        static_cast<long long>(std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count()));
#endif
}

void DistributedUI::RestoreUITreeInner(const SerializeableObjectArray& nodeArray)
{
    if (nodeArray.empty()) {
        LOGE("UITree |ERROR| nodeArray is empty.");
        return;
    }

    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto pageRootNode = context->GetStageManager()->GetLastPage();
    CHECK_NULL_VOID(pageRootNode);
    RestorePageNode(pageRootNode);
    sinkPageChildren_ = pageRootNode->GetChildren();
    for (const auto& child : sinkPageChildren_) {
        pageRootNode->RemoveChild(child);
    }

    for (const auto& nodeObject : nodeArray) {
        AddNode((std::unique_ptr<NodeObject>&)nodeObject, pageRootNode);
    }

    pageRootNode->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
}

bool DistributedUI::IsInCurrentPage(RefPtr<NG::UINode> node, int32_t pageId)
{
    if (node->GetTag() == V2::JS_SYNTAX_ITEM_ETS_TAG) {
        LOGD("UITree true");
        return true;
    }
    if (pageId != 0 && node->GetPageId() != pageId) {
        return false;
    }
    return true;
}
} // namespace OHOS::Ace::NG
