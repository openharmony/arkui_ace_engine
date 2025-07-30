/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/simplified_inspector.h"

#include <memory>

#include "core/components/scroll/scroll_controller_base.h"
#if !defined(CROSS_PLATFORM) && defined(WEB_SUPPORTED)
#include "core/components_ng/pattern/web/web_pattern.h"
#endif
#include "core/common/recorder/inspector_tree_collector.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "interfaces/inner_api/ace/ui_event_observer.h"

namespace OHOS::Ace::NG {
namespace {
const char INSPECTOR_TYPE[] = "$type";
const char INSPECTOR_ID[] = "$ID";
const char INSPECTOR_RECT[] = "$rect";
const char INSPECTOR_ATTRS[] = "$attrs";
const char INSPECTOR_ROOT[] = "root";
const char INSPECTOR_WIDTH[] = "width";
const char INSPECTOR_HEIGHT[] = "height";
const char INSPECTOR_RESOLUTION[] = "$resolution";
const char INSPECTOR_CHILDREN[] = "$children";
const char INSPECTOR_BUNDLE[] = "bundleName";
const char INSPECTOR_ABILITY[] = "ability";
const char INSPECTOR_PAGE_URL[] = "pageUrl";
const char INSPECTOR_NAV_DST_NAME[] = "navDstName";
const char INSPECTOR_ATTR_ID[] = "id";
const char INSPECTOR_LABEL[] = "label";
const char INSPECTOR_CONTENT[] = "content";
const char INSPECTOR_ENABLED[] = "enabled";
const char INSPECTOR_OPACITY[] = "opacity";
const char INSPECTOR_ZINDEX[] = "zindex";
const char INSPECTOR_VISIBILITY[] = "visibility";
const char INSPECTOR_CHILDREN_COUNT[] = "$childrenCount";

constexpr char KEY_CODE[] = "code";
constexpr int32_t ERR_OK = 0;
constexpr int32_t ERR_INVALID_PARAM = 101;
constexpr int32_t ERR_NOT_FOUND_TARGET_NODE = 102;
constexpr int32_t ERR_NOT_FOUND_SCROLLABLE_NODE = 103;

enum class TargetType {
    UNKNOWN = 0,
    NODE,
    WEB,
    ENUM_END,
};

struct ScrollCommand {
    TargetType type { TargetType::UNKNOWN };
    int32_t nodeId { 0 };
    float scrollOffset { 0.0 };
    ScrollAlign scrollAlign { ScrollAlign::NONE };
    std::string webContentJs;
};

bool ParseCommandParam(const std::string& commandParams, ScrollCommand& command)
{
    auto jsonObj = JsonUtil::ParseJsonString(commandParams);
    if (!jsonObj || !jsonObj->IsValid() || !jsonObj->IsObject()) {
        return false;
    }
    auto action = jsonObj->GetString("action");
    if (action != "scroll") {
        return false;
    }
    auto type = jsonObj->GetInt("targetType", 0);
    if (type >= static_cast<int32_t>(TargetType::UNKNOWN) && type < static_cast<int32_t>(TargetType::ENUM_END)) {
        command.type = static_cast<TargetType>(type);
    }
    command.nodeId = jsonObj->GetInt("targetId", 0);
    command.scrollOffset = static_cast<float>(jsonObj->GetDouble("scrollOffset", 0.0));
    auto align = jsonObj->GetInt("scrollAlign", 0);
    if (type >= static_cast<int32_t>(ScrollAlign::START) && type <= static_cast<int32_t>(ScrollAlign::NONE)) {
        command.scrollAlign = static_cast<ScrollAlign>(align);
    }
    command.webContentJs = jsonObj->GetString("webContentJs");
    return true;
}

RefPtr<UINode> GetNodeById(const RefPtr<FrameNode>& root, int32_t id)
{
    std::queue<RefPtr<UINode>> elements;
    elements.push(root);
    RefPtr<UINode> inspectorElement;
    while (!elements.empty()) {
        auto current = elements.front();
        elements.pop();
        if (current == nullptr) {
            continue;
        }
        if (id == current->GetId()) {
            return current;
        }

        const auto& children = current->GetChildrenForInspector(true);
        for (const auto& child : children) {
            elements.push(child);
        }
    }
    return nullptr;
}

bool IsScrollable(const RefPtr<NG::FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto tag = frameNode->GetTag();
    if (tag == V2::LIST_ETS_TAG || tag == V2::SCROLL_ETS_TAG || tag == V2::WATERFLOW_ETS_TAG ||
        tag == V2::GRID_ETS_TAG) {
        auto pattern = frameNode->GetPattern<ScrollablePattern>();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->IsScrollable();
    }
    return false;
}

RefPtr<FrameNode> FindParentScrollable(const RefPtr<FrameNode>& child)
{
    auto parentFrameNode = child->GetAncestorNodeOfFrame(true);
    while (parentFrameNode) {
        if (IsScrollable(parentFrameNode)) {
            return parentFrameNode;
        }
        parentFrameNode = parentFrameNode->GetAncestorNodeOfFrame(true);
    }
    return nullptr;
}

int32_t ScrollToTarget(const ScrollCommand& command, const RefPtr<NG::FrameNode>& pageRootNode)
{
    CHECK_NULL_RETURN(pageRootNode, ERR_NOT_FOUND_TARGET_NODE);
    auto targetNode = GetNodeById(pageRootNode, command.nodeId);
    CHECK_NULL_RETURN(targetNode, ERR_NOT_FOUND_TARGET_NODE);
    auto target = AceType::DynamicCast<FrameNode>(targetNode);
    CHECK_NULL_RETURN(target, ERR_NOT_FOUND_TARGET_NODE);
    auto scrollable = FindParentScrollable(target);
    CHECK_NULL_RETURN(scrollable, ERR_NOT_FOUND_SCROLLABLE_NODE);
    ScrollablePattern::ScrollToTarget(scrollable, target, command.scrollOffset, command.scrollAlign);
    return ERR_OK;
}
} // namespace

void SimplifiedInspector::TestScrollToTarget(
    const std::vector<std::string>& params, const RefPtr<FrameNode>& pageRootNode)
{
    CHECK_NULL_VOID(pageRootNode);
    // -element -lastpage ${nodeid} ${offset} ${align}
    const int32_t PARAM_NODE_ID = 2;
    const int32_t PARAM_OFFSET = 3;
    const int32_t PARAM_ALIGN = 4;
    auto id = StringUtils::StringToInt(params[PARAM_NODE_ID]);
    auto offset = StringUtils::StringToFloat(params[PARAM_OFFSET]);
    auto align = StringUtils::StringToInt(params[PARAM_ALIGN]);
    ScrollCommand command { TargetType::NODE, id, offset, static_cast<ScrollAlign>(align) };
    ScrollToTarget(command, pageRootNode);
}

SimplifiedInspector::SimplifiedInspector(int32_t containerId, const TreeParams& params)
    : containerId_(containerId), params_(params), inspectorCfg_({ params.isContentOnly, !params.enableBackground }),
      isBackground_(params.enableBackground)
{}

SimplifiedInspector::SimplifiedInspector(int32_t containerId, const UICommandParams& params)
    : containerId_(containerId), commandParams_(params)
{}

RefPtr<NG::UINode> GetOverlayNode(const RefPtr<NG::UINode>& pageNode)
{
    CHECK_NULL_RETURN(pageNode, nullptr);
    auto stageNode = pageNode->GetParent();
    CHECK_NULL_RETURN(stageNode, nullptr);
    auto stageParent = stageNode->GetParent();
    CHECK_NULL_RETURN(stageParent, nullptr);
    auto overlayNode = stageParent->GetChildren().back();
    if (overlayNode->GetTag() == "stage") {
        return nullptr;
    }
    return overlayNode;
}

std::string SimplifiedInspector::GetInspector()
{
    TAG_LOGD(AceLogTag::ACE_UIEVENT, "Inspector1:container %{public}d", containerId_);
    auto jsonRoot = JsonUtil::Create(true);
    RefPtr<FrameNode> pageRootNode;
    auto success = GetInspectorStep1(jsonRoot, pageRootNode);
    if (!success) {
        return jsonRoot->ToString();
    }
    GetInspectorStep2(jsonRoot, pageRootNode);
    return jsonRoot->ToString();
}

bool SimplifiedInspector::GetInspectorStep1(const std::unique_ptr<JsonValue>& jsonRoot, RefPtr<FrameNode>& pageRootNode)
{
    jsonRoot->Put(INSPECTOR_TYPE, INSPECTOR_ROOT);
    auto context = NG::PipelineContext::GetContextByContainerId(containerId_);
    CHECK_NULL_RETURN(context, false);
    auto scale = context->GetViewScale();
    auto rootHeight = context->GetRootHeight();
    auto rootWidth = context->GetRootWidth();
    deviceRect_.SetRect(0, 0, rootWidth * scale, rootHeight * scale);
    jsonRoot->Put(INSPECTOR_WIDTH, std::to_string(rootWidth * scale).c_str());
    jsonRoot->Put(INSPECTOR_HEIGHT, std::to_string(rootHeight * scale).c_str());
    jsonRoot->Put(INSPECTOR_RESOLUTION, std::to_string(SystemProperties::GetResolution()).c_str());

    CHECK_NULL_RETURN(context->GetStageManager(), false);
    pageRootNode = context->GetStageManager()->GetLastPage();
    return pageRootNode != nullptr;
}

bool SimplifiedInspector::GetInspectorStep2(
    const std::unique_ptr<JsonValue>& jsonRoot, const RefPtr<FrameNode>& pageRootNode)
{
    auto pagePattern = pageRootNode->GetPattern<PagePattern>();
    CHECK_NULL_RETURN(pagePattern, false);
    auto pageInfo = pagePattern->GetPageInfo();
    CHECK_NULL_RETURN(pageInfo, false);
    jsonRoot->Put(INSPECTOR_BUNDLE, AceApplicationInfo::GetInstance().GetPackageName().c_str());
    jsonRoot->Put(INSPECTOR_ABILITY, AceApplicationInfo::GetInstance().GetAbilityName().c_str());
    jsonRoot->Put(INSPECTOR_PAGE_URL, pageInfo->GetPageUrl().c_str());
    jsonRoot->Put(INSPECTOR_NAV_DST_NAME, Recorder::EventRecorder::Get().GetNavDstName().c_str());

    pageId_ = pageRootNode->GetPageId();
    std::list<RefPtr<NG::UINode>> children;
    for (const auto& item : pageRootNode->GetChildrenForInspector(params_.enableCacheNode)) {
        GetFrameNodeChildren(item, children);
    }
    auto overlayNode = GetOverlayNode(pageRootNode);
    if (overlayNode) {
        GetFrameNodeChildren(overlayNode, children);
    }
    auto jsonNodeArray = JsonUtil::CreateArray(true);
    size_ = children.size();
    for (auto& uiNode : children) {
        GetInspectorChildren(uiNode, jsonNodeArray, true);
    }
    if (jsonNodeArray->GetArraySize()) {
        jsonRoot->PutRef(INSPECTOR_CHILDREN, std::move(jsonNodeArray));
    }
    jsonRoot->Put(INSPECTOR_CHILDREN_COUNT, size_);
    return true;
}

void SimplifiedInspector::GetFrameNodeChildren(
    const RefPtr<NG::UINode>& uiNode, std::list<RefPtr<NG::UINode>>& children)
{
    CHECK_NULL_VOID(uiNode);
    if (isBackground_) {
        collector_->RetainNode(uiNode);
    }
    if (AceType::InstanceOf<NG::FrameNode>(uiNode) || AceType::InstanceOf<SpanNode>(uiNode) ||
        AceType::InstanceOf<CustomNode>(uiNode)) {
        if (uiNode->GetTag() == "page") {
            if (uiNode->GetPageId() != pageId_) {
                return;
            }
        } else if (uiNode->GetTag() != "stage") {
            auto frameNode = AceType::DynamicCast<NG::FrameNode>(uiNode);
            auto spanNode = AceType::DynamicCast<NG::SpanNode>(uiNode);
            if ((frameNode && !frameNode->IsInternal()) || spanNode) {
                children.emplace_back(uiNode);
                return;
            }
        }
    }
    for (const auto& frameChild : uiNode->GetChildrenForInspector(params_.enableCacheNode)) {
        GetFrameNodeChildren(frameChild, children);
    }
}

void SimplifiedInspector::GetInspectorChildren(
    const RefPtr<NG::UINode>& parent, std::unique_ptr<OHOS::Ace::JsonValue>& jsonNodeArray, bool isActive)
{
    // Span is a special case in Inspector since span inherits from UINode
    if (AceType::InstanceOf<SpanNode>(parent)) {
        size_ += 1;
        GetSpanInspector(parent, jsonNodeArray);
        return;
    }
    auto jsonNode = JsonUtil::Create(true);
    auto node = AceType::DynamicCast<FrameNode>(parent);
    CHECK_NULL_VOID(node);
    auto active = isActive && node->IsActive();
    if (!isActive && !params_.enableAllNodes) {
        return;
    }
    auto lp = node->GetLayoutProperty();
    CHECK_NULL_VOID(lp);
    bool isVisible = lp->GetVisibilityValue(VisibleType::VISIBLE) == VisibleType::VISIBLE;
    if (!isVisible && !params_.enableAllNodes) {
        return;
    }
    jsonNode->Put(INSPECTOR_ID, node->GetId());
    jsonNode->Put(INSPECTOR_TYPE, parent->GetTag().c_str());
    RectF rect;
    if (!CheckNodeRect(node, rect, params_.isVisibleOnly)) {
        return;
    }
    jsonNode->Put(INSPECTOR_RECT, rect.ToBounds().c_str());
    size_ += 1;
    GetWebContentIfNeed(node);
    FillInspectorAttrs(parent, jsonNode);
    std::list<RefPtr<NG::UINode>> children;
    for (const auto& item : parent->GetChildrenForInspector(params_.enableCacheNode)) {
        GetFrameNodeChildren(item, children);
    }
    auto jsonChildrenArray = JsonUtil::CreateArray(true);
    for (auto uiNode : children) {
        GetInspectorChildren(uiNode, jsonChildrenArray, active);
    }
    if (jsonChildrenArray->GetArraySize()) {
        jsonNode->PutRef(INSPECTOR_CHILDREN, std::move(jsonChildrenArray));
    }
    jsonNodeArray->PutRef(std::move(jsonNode));
}

void SimplifiedInspector::GetSpanInspector(
    const RefPtr<NG::UINode>& parent, std::unique_ptr<OHOS::Ace::JsonValue>& jsonNodeArray)
{
    // span rect follows parent text size
    auto spanParentNode = parent->GetParent();
    CHECK_NULL_VOID(spanParentNode);
    auto node = AceType::DynamicCast<FrameNode>(spanParentNode);
    CHECK_NULL_VOID(node);
    auto jsonNode = JsonUtil::Create(true);

    FillInspectorAttrs(parent, jsonNode);

    jsonNode->Put(INSPECTOR_ID, parent->GetId());
    jsonNode->Put(INSPECTOR_TYPE, parent->GetTag().c_str());
    RectF rect = node->GetTransformRectRelativeToWindow();
    jsonNode->Put(INSPECTOR_RECT, rect.ToBounds().c_str());
    jsonNodeArray->PutRef(std::move(jsonNode));
}

void SimplifiedInspector::FillInspectorAttrs(
    const RefPtr<NG::UINode>& parent, std::unique_ptr<OHOS::Ace::JsonValue>& jsonNode)
{
    if (params_.isNewVersion) {
        auto tmpJson = JsonUtil::Create(true);
        parent->ToTreeJson(tmpJson, inspectorCfg_);
        jsonNode->PutRef(INSPECTOR_ATTRS, std::move(tmpJson));
        return;
    }
    auto tmpJson = JsonUtil::Create(true);
    InspectorFilter filter;
    parent->ToJsonValue(tmpJson, filter);
    if (params_.enableFullAttrs) {
        jsonNode->PutRef(INSPECTOR_ATTRS, std::move(tmpJson));
        return;
    }
    jsonNode->Put(INSPECTOR_ATTR_ID, tmpJson->GetString(INSPECTOR_ATTR_ID).c_str());

    auto jsonObject = JsonUtil::Create(true);
    if (tmpJson->Contains(INSPECTOR_LABEL)) {
        jsonObject->Put(INSPECTOR_LABEL, tmpJson->GetString(INSPECTOR_LABEL).c_str());
    }
    if (tmpJson->Contains(INSPECTOR_CONTENT)) {
        jsonObject->Put(INSPECTOR_CONTENT, tmpJson->GetString(INSPECTOR_CONTENT).c_str());
    }
    jsonObject->Put(INSPECTOR_ENABLED, tmpJson->GetBool(INSPECTOR_ENABLED));
    jsonObject->Put(INSPECTOR_OPACITY, tmpJson->GetDouble(INSPECTOR_OPACITY));
    jsonObject->Put(INSPECTOR_ZINDEX, tmpJson->GetInt(INSPECTOR_ZINDEX));
    jsonObject->Put(INSPECTOR_VISIBILITY, tmpJson->GetString(INSPECTOR_VISIBILITY).c_str());
    jsonNode->PutRef(INSPECTOR_ATTRS, std::move(jsonObject));
}

bool SimplifiedInspector::CheckNodeRect(const RefPtr<FrameNode>& node, RectF& rect, bool isVisibleOnly)
{
    auto renderContext = node->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);
    auto paintRect = renderContext->GetPaintRectWithoutTransform();
    if (paintRect.IsEmpty()) {
        return false;
    }
    rect = node->GetTransformRectRelativeToWindow();
    if (isVisibleOnly && !deviceRect_.IsIntersectWith(rect)) {
        return false;
    }
    return true;
}

void SimplifiedInspector::GetWebContentIfNeed(const RefPtr<FrameNode>& node)
{
    if (!isAsync_ || !collector_) {
        return;
    }
#if !defined(CROSS_PLATFORM) && defined(WEB_SUPPORTED)
    if (params_.enableWeb && !params_.webContentJs.empty() && node->GetTag() == V2::WEB_ETS_TAG) {
        auto pattern = node->GetPattern<WebPattern>();
        CHECK_NULL_VOID(pattern);
        if (!pattern->GetActiveStatus()) {
            return;
        }
        auto lambda = [webId = node->GetId(), collector = collector_](const std::string& result) {
            std::string key = "Web_" + std::to_string(webId);
            collector->GetJson()->Put(key.c_str(), result.c_str());
            collector->DecreaseTaskNum();
        };
        collector_->IncreaseTaskNum();
        if (!pattern->RunJavascriptAsync(params_.webContentJs, std::move(lambda))) {
            collector_->DecreaseTaskNum();
        }
    }
#endif
}

void SimplifiedInspector::GetInspectorAsync(const std::shared_ptr<Recorder::InspectorTreeCollector>& collector)
{
#if !defined(PREVIEW) && !defined(ACE_UNITTEST)
    CHECK_NULL_VOID(collector);
    collector->CreateJson();
    collector_ = collector;
    isAsync_ = true;
    TAG_LOGD(AceLogTag::ACE_UIEVENT, "Inspector2:container %{public}d", containerId_);
    collector->IncreaseTaskNum();
    auto& jsonRoot = collector->GetJson();
    RefPtr<FrameNode> pageRootNode;
    auto success = GetInspectorStep1(jsonRoot, pageRootNode);
    if (!success) {
        collector->DecreaseTaskNum();
        return;
    }
    GetInspectorStep2(jsonRoot, pageRootNode);
    collector->DecreaseTaskNum();
#endif
}

void SimplifiedInspector::GetInspectorBackgroundAsync(
    const std::shared_ptr<Recorder::InspectorTreeCollector>& collector)
{
    CHECK_NULL_VOID(collector);
    collector->CreateJson();
    collector_ = collector;
    isAsync_ = true;
    TAG_LOGD(AceLogTag::ACE_UIEVENT, "Inspector3:container %{public}d", containerId_);
    auto context = NG::PipelineContext::GetContextByContainerId(containerId_);
    CHECK_NULL_VOID(context);
    CHECK_NULL_VOID(context->GetStageManager());
    auto pageRootNode = context->GetStageManager()->GetLastPage();
    CHECK_NULL_VOID(pageRootNode);
    pageId_ = pageRootNode->GetPageId();
    auto pagePattern = pageRootNode->GetPattern<PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    auto pageInfo = pagePattern->GetPageInfo();
    CHECK_NULL_VOID(pageInfo);
    auto pageUrl = pageInfo->GetPageUrl();

    auto treeNode = std::make_shared<SimplifiedInspectorTree>();
    GetInspectorTreeNode(pageRootNode, treeNode);

    CHECK_NULL_VOID(context->GetTaskExecutor());
    collector->SetTaskExecutor(context->GetTaskExecutor());
    collector->IncreaseTaskNum();
    context->GetTaskExecutor()->PostTask(
        [inspector = shared_from_this(), context, pageUrl, treeNode]() {
            auto& jsonRoot = inspector->collector_->GetJson();
            jsonRoot->Put(INSPECTOR_TYPE, INSPECTOR_ROOT);
            auto scale = context->GetViewScale();
            auto rootHeight = context->GetRootHeight();
            auto rootWidth = context->GetRootWidth();
            inspector->deviceRect_.SetRect(0, 0, rootWidth * scale, rootHeight * scale);
            jsonRoot->Put(INSPECTOR_WIDTH, std::to_string(rootWidth * scale).c_str());
            jsonRoot->Put(INSPECTOR_HEIGHT, std::to_string(rootHeight * scale).c_str());
            jsonRoot->Put(INSPECTOR_RESOLUTION, std::to_string(SystemProperties::GetResolution()).c_str());
            jsonRoot->Put(INSPECTOR_ABILITY, AceApplicationInfo::GetInstance().GetAbilityName().c_str());
            jsonRoot->Put(INSPECTOR_BUNDLE, AceApplicationInfo::GetInstance().GetPackageName().c_str());
            jsonRoot->Put(INSPECTOR_PAGE_URL, pageUrl.c_str());
            jsonRoot->Put(INSPECTOR_NAV_DST_NAME, Recorder::EventRecorder::Get().GetNavDstName().c_str());
            auto jsonNodeArray = JsonUtil::CreateArray(true);
            inspector->size_ = 1;
            for (auto& subTreeNode : treeNode->children) {
                inspector->GetInspectorChildrenBackground(subTreeNode, jsonNodeArray);
            }
            if (jsonNodeArray->GetArraySize()) {
                jsonRoot->PutRef(INSPECTOR_CHILDREN, std::move(jsonNodeArray));
            }
            jsonRoot->Put(INSPECTOR_CHILDREN_COUNT, inspector->size_);
            inspector->collector_->DecreaseTaskNum();
        },
        TaskExecutor::TaskType::BACKGROUND, "GetSimplifiedInspector");
}

void SimplifiedInspector::GetInspectorTreeNode(
    const RefPtr<NG::UINode>& pageRootNode, std::shared_ptr<SimplifiedInspectorTree>& root)
{
    collector_->RetainNode(pageRootNode);
    std::list<RefPtr<NG::UINode>> children;
    for (const auto& item : pageRootNode->GetChildrenForInspector(params_.enableCacheNode)) {
        GetFrameNodeChildren(item, children);
    }
    auto overlayNode2 = GetOverlayNode(pageRootNode);
    if (overlayNode2) {
        GetFrameNodeChildren(overlayNode2, children);
    }
    root->node = pageRootNode;
    std::list<std::shared_ptr<SimplifiedInspectorTree>> childNodes;
    for (const auto& uiNode : children) {
        auto treeNode = std::make_shared<SimplifiedInspectorTree>();
        GetInspectorTreeNodeChildren(uiNode, treeNode, true);
        if (treeNode->node.Upgrade()) {
            childNodes.emplace_back(treeNode);
        }
    }
    root->children = std::move(childNodes);
}

void SimplifiedInspector::GetInspectorTreeNodeChildren(
    const RefPtr<NG::UINode>& parent, std::shared_ptr<SimplifiedInspectorTree>& treeNode, bool isActive)
{
    if (AceType::InstanceOf<SpanNode>(parent)) {
        treeNode->node = parent;
        return;
    }
    auto node = AceType::DynamicCast<FrameNode>(parent);
    if (!node) {
        return;
    }
    auto active = isActive && node->IsActive();
    if (!isActive && !params_.enableAllNodes) {
        return;
    }
    treeNode->node = parent;
    std::list<RefPtr<NG::UINode>> children;
    for (const auto& item : parent->GetChildrenForInspector(params_.enableCacheNode)) {
        GetFrameNodeChildren(item, children);
    }
    for (auto uiNode : children) {
        auto subTreeNode = std::make_shared<SimplifiedInspectorTree>();
        GetInspectorTreeNodeChildren(uiNode, subTreeNode, active);
        if (subTreeNode->node.Upgrade()) {
            treeNode->children.emplace_back(subTreeNode);
        }
    }
}

void SimplifiedInspector::GetInspectorChildrenBackground(
    const std::shared_ptr<SimplifiedInspectorTree>& treeNode, std::unique_ptr<OHOS::Ace::JsonValue>& jsonNodeArray)
{
    auto parent = treeNode->node.Upgrade();
    CHECK_NULL_VOID(parent);
    // Span is a special case in Inspector since span inherits from UINode
    if (AceType::InstanceOf<SpanNode>(parent)) {
        size_ += 1;
        GetSpanInspector(parent, jsonNodeArray);
        return;
    }
    auto jsonNode = JsonUtil::Create(true);
    auto node = AceType::DynamicCast<FrameNode>(parent);
    CHECK_NULL_VOID(node);
    auto lp = node->GetLayoutProperty();
    CHECK_NULL_VOID(lp);
    bool isVisible = lp->GetVisibilityValue(VisibleType::VISIBLE) == VisibleType::VISIBLE;
    if (!isVisible && !params_.enableAllNodes) {
        return;
    }
    jsonNode->Put(INSPECTOR_ID, node->GetId());
    jsonNode->Put(INSPECTOR_TYPE, parent->GetTag().c_str());
    RectF rect;
    if (!CheckNodeRect(node, rect, params_.isVisibleOnly)) {
        return;
    }
    jsonNode->Put(INSPECTOR_RECT, rect.ToBounds().c_str());
    size_ += 1;
    GetWebContentIfNeed(node);
    FillInspectorAttrs(parent, jsonNode);
    std::list<RefPtr<NG::UINode>> children;
    for (const auto& item : parent->GetChildrenForInspector(params_.enableCacheNode)) {
        GetFrameNodeChildren(item, children);
    }
    auto jsonChildrenArray = JsonUtil::CreateArray(true);
    for (auto subTreeNode : treeNode->children) {
        GetInspectorChildrenBackground(subTreeNode, jsonChildrenArray);
    }
    if (jsonChildrenArray->GetArraySize()) {
        jsonNode->PutRef(INSPECTOR_CHILDREN, std::move(jsonChildrenArray));
    }
    jsonNodeArray->PutRef(std::move(jsonNode));
}

void SimplifiedInspector::ExecuteUICommand(const std::shared_ptr<Recorder::InspectorTreeCollector>& collector)
{
    CHECK_NULL_VOID(collector);
    collector_ = collector;
    ContainerScope scope(Container::CurrentIdSafely());
    collector->CreateJson();
    collector->IncreaseTaskNum();
    ScrollCommand command;
    if (!ParseCommandParam(commandParams_.params, command)) {
        collector->GetJson()->Put(KEY_CODE, ERR_INVALID_PARAM);
        collector->DecreaseTaskNum();
        return;
    }
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    CHECK_NULL_VOID(context->GetStageManager());
    auto pageRootNode = context->GetStageManager()->GetLastPage();
    CHECK_NULL_VOID(pageRootNode);
    if (command.type == TargetType::NODE) {
        TAG_LOGD(AceLogTag::ACE_UIEVENT, "ExecuteUICommand node");
        auto ret = ScrollToTarget(command, pageRootNode);
        collector->GetJson()->Put(KEY_CODE, ret);
        collector->DecreaseTaskNum();
    } else if (command.type == TargetType::WEB) {
        TAG_LOGD(AceLogTag::ACE_UIEVENT, "ExecuteUICommand web");
        auto ret = ExecuteWebScrollCommand(pageRootNode, command.nodeId, command.webContentJs);
        if (ret != ERR_OK) {
            collector->GetJson()->Put(KEY_CODE, ret);
            collector->DecreaseTaskNum();
        }
    }
}

int32_t SimplifiedInspector::ExecuteWebScrollCommand(
    const RefPtr<FrameNode>& rootNode, int32_t nodeId, const std::string& jsCode)
{
#if !defined(CROSS_PLATFORM) && defined(WEB_SUPPORTED)
    if (jsCode.empty()) {
        return ERR_INVALID_PARAM;
    }
    auto targetNode = GetNodeById(rootNode, nodeId);
    CHECK_NULL_RETURN(targetNode, ERR_NOT_FOUND_TARGET_NODE);
    if (targetNode->GetTag() != V2::WEB_ETS_TAG) {
        return ERR_NOT_FOUND_TARGET_NODE;
    }
    auto frameNode = AceType::DynamicCast<NG::FrameNode>(targetNode);
    CHECK_NULL_RETURN(frameNode, ERR_NOT_FOUND_TARGET_NODE);
    auto pattern = frameNode->GetPattern<WebPattern>();
    CHECK_NULL_RETURN(pattern, ERR_NOT_FOUND_TARGET_NODE);
    pattern->RunJavascriptAsync(jsCode, [collector = collector_](const std::string& result) {
        collector->GetJson()->Put(KEY_CODE, ERR_OK);
        collector->GetJson()->Put("ret", result.c_str());
        collector->DecreaseTaskNum();
    });
    return ERR_OK;
#else
    return ERR_NOT_FOUND_TARGET_NODE;
#endif
}
} // namespace OHOS::Ace::NG
