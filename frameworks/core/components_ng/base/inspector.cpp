/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/inspector.h"

#include <unordered_set>

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/common/ace_application_info.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

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

const uint32_t LONG_PRESS_DELAY = 1000;
RectF deviceRect;

RefPtr<UINode> GetInspectorByKey(const RefPtr<FrameNode>& root, const std::string& key)
{
    std::queue<RefPtr<UINode>> elements;
    elements.push(root);
    RefPtr<UINode> inspectorElement;
    while (!elements.empty()) {
        auto current = elements.front();
        elements.pop();
        if (key == current->GetInspectorId().value_or("")) {
            return current;
        }

        const auto& children = current->GetChildren();
        for (const auto& child : children) {
            elements.push(child);
        }
    }
    return nullptr;
}

void DumpElementTree(
    int32_t depth, const RefPtr<UINode>& element, std::map<int32_t, std::list<RefPtr<UINode>>>& depthElementMap)
{
    if (element->GetChildren().empty()) {
        return;
    }
    const auto& children = element->GetChildren();
    depthElementMap[depth].insert(depthElementMap[depth].end(), children.begin(), children.end());
    for (const auto& depthElement : children) {
        DumpElementTree(depth + 1, depthElement, depthElementMap);
    }
}

TouchEvent GetUpPoint(const TouchEvent& downPoint)
{
    return {
        .x = downPoint.x, .y = downPoint.y, .type = TouchType::UP, .time = std::chrono::high_resolution_clock::now()
    };
}
#ifdef PREVIEW
void GetFrameNodeChildren(const RefPtr<NG::UINode>& uiNode, std::vector<RefPtr<NG::UINode>>& children, int32_t pageId)
{
    // Set ViewId for the fast preview.
    auto parent = uiNode->GetParent();
    if (parent && parent->GetTag() == "JsView") {
        uiNode->SetViewId(std::to_string(parent->GetId()));
    } else {
        uiNode->SetViewId(parent->GetViewId());
    }
    if (uiNode->GetTag() == "stage") {
    } else if (uiNode->GetTag() == "page") {
        if (uiNode->GetPageId() != pageId) {
            return;
        }
    } else {
        if (!uiNode->GetDebugLine().empty()) {
            children.emplace_back(uiNode);
            return;
        }
    }

    for (const auto& frameChild : uiNode->GetChildren()) {
        GetFrameNodeChildren(frameChild, children, pageId);
    }
}

void GetSpanInspector(
    const RefPtr<NG::UINode>& parent, std::unique_ptr<OHOS::Ace::JsonValue>& jsonNodeArray, int pageId)
{
    // span rect follows parent text size
    auto spanParentNode = parent->GetParent();
    CHECK_NULL_VOID_NOLOG(spanParentNode);
    auto node = AceType::DynamicCast<FrameNode>(spanParentNode);
    CHECK_NULL_VOID_NOLOG(node);
    auto jsonNode = JsonUtil::Create(true);
    auto jsonObject = JsonUtil::Create(true);
    parent->ToJsonValue(jsonObject);
    jsonNode->Put(INSPECTOR_ATTRS, jsonObject);
    jsonNode->Put(INSPECTOR_TYPE, parent->GetTag().c_str());
    jsonNode->Put(INSPECTOR_ID, parent->GetId());
    RectF rect = node->GetTransformRectRelativeToWindow();
    rect = rect.Constrain(deviceRect);
    if (rect.IsEmpty()) {
        rect.SetRect(0, 0, 0, 0);
    }
    auto strRec = std::to_string(rect.Left())
                      .append(",")
                      .append(std::to_string(rect.Top()))
                      .append(",")
                      .append(std::to_string(rect.Width()))
                      .append(",")
                      .append(std::to_string(rect.Height()));
    jsonNode->Put(INSPECTOR_RECT, strRec.c_str());
    jsonNode->Put("$debugLine", parent->GetDebugLine().c_str());
    jsonNode->Put("$viewID", parent->GetViewId().c_str());
    jsonNodeArray->Put(jsonNode);
}

void GetInspectorChildren(
    const RefPtr<NG::UINode>& parent, std::unique_ptr<OHOS::Ace::JsonValue>& jsonNodeArray, int pageId, bool isActive)
{
    // Span is a special case in Inspector since span inherits from UINode
    if (AceType::InstanceOf<SpanNode>(parent)) {
        GetSpanInspector(parent, jsonNodeArray, pageId);
        return;
    }
    auto jsonNode = JsonUtil::Create(true);
    jsonNode->Put(INSPECTOR_TYPE, parent->GetTag().c_str());
    jsonNode->Put(INSPECTOR_ID, parent->GetId());
    auto node = AceType::DynamicCast<FrameNode>(parent);
    if (node) {
        RectF rect;
        isActive = isActive && node->IsActive();
        if (isActive) {
            rect = node->GetTransformRectRelativeToWindow();
        }
        rect = rect.Constrain(deviceRect);
        if (rect.IsEmpty()) {
            rect.SetRect(0, 0, 0, 0);
        }
        auto strRec = std::to_string(rect.Left())
                          .append(",")
                          .append(std::to_string(rect.Top()))
                          .append(",")
                          .append(std::to_string(rect.Width()))
                          .append(",")
                          .append(std::to_string(rect.Height()));
        jsonNode->Put(INSPECTOR_RECT, strRec.c_str());
        jsonNode->Put("$debugLine", node->GetDebugLine().c_str());
        jsonNode->Put("$viewID", node->GetViewId().c_str());
        auto jsonObject = JsonUtil::Create(true);
        parent->ToJsonValue(jsonObject);
        jsonNode->Put(INSPECTOR_ATTRS, jsonObject);
    }

    std::vector<RefPtr<NG::UINode>> children;
    for (const auto& item : parent->GetChildren()) {
        GetFrameNodeChildren(item, children, pageId);
    }
    auto jsonChildrenArray = JsonUtil::CreateArray(true);
    for (auto uiNode : children) {
        GetInspectorChildren(uiNode, jsonChildrenArray, pageId, isActive);
    }
    if (jsonChildrenArray->GetArraySize()) {
        jsonNode->Put(INSPECTOR_CHILDREN, jsonChildrenArray);
    }
    jsonNodeArray->Put(jsonNode);
}

#else
void GetFrameNodeChildren(const RefPtr<NG::UINode>& uiNode, std::vector<RefPtr<NG::UINode>>& children, int32_t pageId)
{
    if (AceType::InstanceOf<NG::FrameNode>(uiNode) || AceType::InstanceOf<SpanNode>(uiNode)) {
        if (uiNode->GetTag() == "stage") {
        } else if (uiNode->GetTag() == "page") {
            if (uiNode->GetPageId() != pageId) {
                return;
            }
        } else {
            auto frameNode = AceType::DynamicCast<NG::FrameNode>(uiNode);
            auto spanNode = AceType::DynamicCast<NG::SpanNode>(uiNode);
            if ((frameNode && !frameNode->IsInternal()) || spanNode) {
                children.emplace_back(uiNode);
                return;
            }
        }
    }

    for (const auto& frameChild : uiNode->GetChildren()) {
        GetFrameNodeChildren(frameChild, children, pageId);
    }
}

void GetSpanInspector(
    const RefPtr<NG::UINode>& parent, std::unique_ptr<OHOS::Ace::JsonValue>& jsonNodeArray, int pageId)
{
    // span rect follows parent text size
    auto spanParentNode = parent->GetParent();
    CHECK_NULL_VOID_NOLOG(spanParentNode);
    auto node = AceType::DynamicCast<FrameNode>(spanParentNode);
    CHECK_NULL_VOID_NOLOG(node);
    auto jsonNode = JsonUtil::Create(true);
    auto jsonObject = JsonUtil::Create(true);
    parent->ToJsonValue(jsonObject);
    jsonNode->Put(INSPECTOR_ATTRS, jsonObject);
    jsonNode->Put(INSPECTOR_TYPE, parent->GetTag().c_str());
    jsonNode->Put(INSPECTOR_ID, parent->GetId());
    RectF rect = node->GetTransformRectRelativeToWindow();
    jsonNode->Put(INSPECTOR_RECT, rect.ToBounds().c_str());
    jsonNodeArray->Put(jsonNode);
}

void GetInspectorChildren(
    const RefPtr<NG::UINode>& parent, std::unique_ptr<OHOS::Ace::JsonValue>& jsonNodeArray, int pageId, bool isActive)
{
    // Span is a special case in Inspector since span inherits from UINode
    if (AceType::InstanceOf<SpanNode>(parent)) {
        GetSpanInspector(parent, jsonNodeArray, pageId);
        return;
    }
    auto jsonNode = JsonUtil::Create(true);
    jsonNode->Put(INSPECTOR_TYPE, parent->GetTag().c_str());
    jsonNode->Put(INSPECTOR_ID, parent->GetId());
    auto node = AceType::DynamicCast<FrameNode>(parent);
    auto ctx = node->GetRenderContext();

    RectF rect;
    isActive = isActive && node->IsActive();
    if (isActive) {
        rect = node->GetTransformRectRelativeToWindow();
    }

    jsonNode->Put(INSPECTOR_RECT, rect.ToBounds().c_str());
    auto jsonObject = JsonUtil::Create(true);
    parent->ToJsonValue(jsonObject);
    jsonNode->Put(INSPECTOR_ATTRS, jsonObject);
    std::vector<RefPtr<NG::UINode>> children;
    for (const auto& item : parent->GetChildren()) {
        GetFrameNodeChildren(item, children, pageId);
    }
    auto jsonChildrenArray = JsonUtil::CreateArray(true);
    for (auto uiNode : children) {
        GetInspectorChildren(uiNode, jsonChildrenArray, pageId, isActive);
    }
    if (jsonChildrenArray->GetArraySize()) {
        jsonNode->Put(INSPECTOR_CHILDREN, jsonChildrenArray);
    }
    jsonNodeArray->Put(jsonNode);
}
#endif

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
    LOGI("GetOverlayNode if overlay node has showed");
    return overlayNode;
}
} // namespace

std::string Inspector::GetInspectorNodeByKey(const std::string& key)
{
    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, "");
    auto rootNode = context->GetRootElement();
    CHECK_NULL_RETURN(rootNode, "");

    auto inspectorElement = GetInspectorByKey(rootNode, key);
    CHECK_NULL_RETURN(inspectorElement, "");

    auto jsonNode = JsonUtil::Create(true);
    jsonNode->Put(INSPECTOR_TYPE, inspectorElement->GetTag().c_str());
    jsonNode->Put(INSPECTOR_ID, inspectorElement->GetId());
    auto frameNode = AceType::DynamicCast<FrameNode>(inspectorElement);
    if (frameNode) {
        auto rect = frameNode->GetTransformRectRelativeToWindow();
        jsonNode->Put(INSPECTOR_RECT, rect.ToBounds().c_str());
    }
    auto jsonAttrs = JsonUtil::Create(true);
    inspectorElement->ToJsonValue(jsonAttrs);
    jsonNode->Put(INSPECTOR_ATTRS, jsonAttrs);
    return jsonNode->ToString();
}

std::string Inspector::GetInspector(bool isLayoutInspector)
{
    LOGI("GetInspector start");
    auto jsonRoot = JsonUtil::Create(true);
    jsonRoot->Put(INSPECTOR_TYPE, INSPECTOR_ROOT);

    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN_NOLOG(context, jsonRoot->ToString());
    auto scale = context->GetViewScale();
    auto rootHeight = context->GetRootHeight();
    auto rootWidth = context->GetRootWidth();
    deviceRect.SetRect(0, 0, rootWidth * scale, rootHeight * scale);
    jsonRoot->Put(INSPECTOR_WIDTH, std::to_string(rootWidth * scale).c_str());
    jsonRoot->Put(INSPECTOR_HEIGHT, std::to_string(rootHeight * scale).c_str());
    jsonRoot->Put(INSPECTOR_RESOLUTION, std::to_string(SystemProperties::GetResolution()).c_str());

    auto pageRootNode = context->GetStageManager()->GetLastPage();
    CHECK_NULL_RETURN_NOLOG(pageRootNode, jsonRoot->ToString());
    auto pageId = context->GetStageManager()->GetLastPage()->GetPageId();
    std::vector<RefPtr<NG::UINode>> children;
    for (const auto& item : pageRootNode->GetChildren()) {
        GetFrameNodeChildren(item, children, pageId);
    }
    auto overlayNode = GetOverlayNode(pageRootNode);
    if (overlayNode) {
        GetFrameNodeChildren(overlayNode, children, pageId);
    }
    auto jsonNodeArray = JsonUtil::CreateArray(true);
    for (auto& uiNode : children) {
        GetInspectorChildren(uiNode, jsonNodeArray, pageId, true);
    }
    if (jsonNodeArray->GetArraySize()) {
        jsonRoot->Put(INSPECTOR_CHILDREN, jsonNodeArray);
    }

    if (isLayoutInspector) {
        auto jsonTree = JsonUtil::Create(true);
        jsonTree->Put("type", "root");
        jsonTree->Put("content", jsonRoot);
        return jsonTree->ToString();
    }

    return jsonRoot->ToString();
}

std::string Inspector::GetInspectorTree(bool isLayoutInspector)
{
    auto jsonRoot = JsonUtil::Create(true);
    jsonRoot->Put(INSPECTOR_TYPE, INSPECTOR_ROOT);

    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN_NOLOG(context, jsonRoot->ToString());
    auto scale = context->GetViewScale();
    auto rootHeight = context->GetRootHeight();
    auto rootWidth = context->GetRootWidth();
    jsonRoot->Put(INSPECTOR_WIDTH, std::to_string(rootWidth * scale).c_str());
    jsonRoot->Put(INSPECTOR_HEIGHT, std::to_string(rootHeight * scale).c_str());
    jsonRoot->Put(INSPECTOR_RESOLUTION, std::to_string(SystemProperties::GetResolution()).c_str());

    auto root = context->GetRootElement();
    CHECK_NULL_RETURN_NOLOG(root, jsonRoot->ToString());

    std::map<int32_t, std::list<RefPtr<UINode>>> depthElementMap;
    depthElementMap[0].emplace_back(root);
    DumpElementTree(1, root, depthElementMap);

    int32_t height = 0;
    std::unordered_map<int32_t, std::vector<std::pair<RefPtr<UINode>, std::string>>> elementJSONInfoMap;
    for (int depth = static_cast<int32_t>(depthElementMap.size()); depth > 0; depth--) {
        const auto& depthElements = depthElementMap[depth];
        for (const auto& element : depthElements) {
            auto inspectorElement = AceType::DynamicCast<FrameNode>(element);
            if (inspectorElement == nullptr) {
                continue;
            }

            auto jsonNode = JsonUtil::Create(true);
            jsonNode->Put(INSPECTOR_TYPE, inspectorElement->GetTag().c_str());
            jsonNode->Put(INSPECTOR_ID, inspectorElement->GetId());
            RectF rect;
            rect.SetOffset(inspectorElement->GetTransformRelativeOffset());
            rect.SetWidth(inspectorElement->GetGeometryNode()->GetFrameRect().Width());
            rect.SetHeight(inspectorElement->GetGeometryNode()->GetFrameRect().Height());
            jsonNode->Put(INSPECTOR_RECT, rect.ToBounds().c_str());
            auto jsonObject = JsonUtil::Create(true);
            inspectorElement->ToJsonValue(jsonObject);
            jsonNode->Put(INSPECTOR_ATTRS, jsonObject);
            if (!element->GetChildren().empty()) {
                if (height > 0) {
                    auto jsonNodeArray = JsonUtil::CreateArray(true);
                    auto childNodeJSONVec = elementJSONInfoMap[height - 1];
                    for (auto& iter : childNodeJSONVec) {
                        auto parent = iter.first->GetParent();
                        if (parent->GetId() == element->GetId()) {
                            auto childJSONValue = JsonUtil::ParseJsonString(iter.second);
                            jsonNodeArray->Put(childJSONValue);
                        }
                    }
                    if (jsonNodeArray->GetArraySize()) {
                        jsonNode->Put(INSPECTOR_CHILDREN, jsonNodeArray);
                    }
                }
            }
            elementJSONInfoMap[height].emplace_back(element, jsonNode->ToString());
        }
        if (elementJSONInfoMap.find(height) != elementJSONInfoMap.end()) {
            height++;
        }
    }

    auto jsonChildren = JsonUtil::CreateArray(true);
    auto firstDepthNodeVec = elementJSONInfoMap[elementJSONInfoMap.size() - 1];
    for (const auto& nodeJSONInfo : firstDepthNodeVec) {
        auto nodeJSONValue = JsonUtil::ParseJsonString(nodeJSONInfo.second);
        jsonChildren->Put(nodeJSONValue);
    }
    jsonRoot->Put(INSPECTOR_CHILDREN, jsonChildren);

    if (isLayoutInspector) {
        auto jsonTree = JsonUtil::Create(true);
        jsonTree->Put("type", "root");
        jsonTree->Put("content", jsonRoot);
        return jsonTree->ToString();
    }
    return jsonRoot->ToString();
}

bool Inspector::SendEventByKey(const std::string& key, int action, const std::string& params)
{
    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, false);
    auto rootNode = context->GetRootElement();
    CHECK_NULL_RETURN(rootNode, false);

    auto inspectorElement = AceType::DynamicCast<FrameNode>(GetInspectorByKey(rootNode, key));
    CHECK_NULL_RETURN(inspectorElement, false);

    auto size = inspectorElement->GetGeometryNode()->GetFrameSize();
    auto offset = inspectorElement->GetTransformRelativeOffset();
    Rect rect { offset.GetX(), offset.GetY(), size.Width(), size.Height() };
    context->GetTaskExecutor()->PostTask(
        [weak = AceType::WeakClaim(AceType::RawPtr(context)), rect, action, params]() {
            auto context = weak.Upgrade();
            if (!context) {
                return;
            }

            TouchEvent point { .x = (rect.Left() + rect.Width() / 2),
                .y = (rect.Top() + rect.Height() / 2),
                .type = TouchType::DOWN,
                .time = std::chrono::high_resolution_clock::now() };
            context->OnTouchEvent(point.UpdatePointers());

            switch (action) {
                case static_cast<int>(AceAction::ACTION_CLICK): {
                    context->OnTouchEvent(GetUpPoint(point).UpdatePointers());
                    break;
                }
                case static_cast<int>(AceAction::ACTION_LONG_CLICK): {
                    CancelableCallback<void()> inspectorTimer;
                    auto&& callback = [weak, point]() {
                        auto refPtr = weak.Upgrade();
                        if (refPtr) {
                            refPtr->OnTouchEvent(GetUpPoint(point).UpdatePointers());
                        }
                    };
                    inspectorTimer.Reset(callback);
                    auto taskExecutor =
                        SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
                    taskExecutor.PostDelayedTask(inspectorTimer, LONG_PRESS_DELAY);
                    break;
                }
                default:
                    break;
            }
        },
        TaskExecutor::TaskType::UI);

    return true;
}

void Inspector::HideAllMenus()
{
    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->HideAllMenus();
}

} // namespace OHOS::Ace::NG
