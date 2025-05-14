/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include <unistd.h>
#include <vector>

#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_ng/render/render_context.h"
#include "foundation/arkui/ace_engine/frameworks/base/utils/utf.h"

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
const char INSPECTOR_DEBUGLINE[] = "$debugLine";
#ifdef PREVIEW
const char INSPECTOR_VIEW_ID[] = "$viewID";
#else
const char INSPECTOR_CUSTOM_VIEW_TAG[] = "viewTag";
const char INSPECTOR_COMPONENT_TYPE[] = "type";
const char INSPECTOR_STATE_VAR[] = "state";
#endif

const std::vector SUPPORT_METHOD = {"ArkUI.tree", "ArkUI.tree.3D"};

const uint32_t LONG_PRESS_DELAY = 1000;
RectF deviceRect;

TouchEvent GetUpPoint(const TouchEvent& downPoint)
{
    return TouchEvent {}
        .SetX(downPoint.x)
        .SetY(downPoint.y)
        .SetType(TouchType::UP)
        .SetTime(std::chrono::high_resolution_clock::now())
        .SetSourceType(SourceType::TOUCH);
}
#ifdef PREVIEW
void GetFrameNodeChildren(const RefPtr<NG::UINode>& uiNode, std::vector<RefPtr<NG::UINode>>& children, int32_t pageId,
    bool isLayoutInspector = false)
{
    // Set ViewId for the fast preview.
    auto parent = uiNode->GetParent();
    if (parent) {
        if (parent->GetTag() == "JsView") {
            uiNode->SetViewId(std::to_string(parent->GetId()));
        } else {
            uiNode->SetViewId(parent->GetViewId());
        }
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
    while (spanParentNode != nullptr) {
        if (AceType::InstanceOf<NG::FrameNode>(spanParentNode)) {
            break;
        }
        spanParentNode = spanParentNode->GetParent();
    }
    CHECK_NULL_VOID(spanParentNode);
    auto node = AceType::DynamicCast<FrameNode>(spanParentNode);
    auto jsonNode = JsonUtil::Create(true);
    auto jsonObject = JsonUtil::Create(true);

    InspectorFilter filter;
    parent->ToJsonValue(jsonObject, filter);
    jsonNode->PutRef(INSPECTOR_ATTRS, std::move(jsonObject));
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
    jsonNode->Put(INSPECTOR_DEBUGLINE, parent->GetDebugLine().c_str());
    jsonNode->Put(INSPECTOR_VIEW_ID, parent->GetViewId().c_str());
    jsonNodeArray->PutRef(std::move(jsonNode));
}

void PutNodeInfoToJsonNode(RefPtr<OHOS::Ace::NG::FrameNode>& node,
    bool& isActive, std::unique_ptr<OHOS::Ace::JsonValue>& jsonNode, const RefPtr<NG::UINode>& parent)
{
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
        auto strRec = std::to_string(rect.Left()).append(",")
                          .append(std::to_string(rect.Top())).append(",")
                          .append(std::to_string(rect.Width())).append(",")
                          .append(std::to_string(rect.Height()));
        jsonNode->Put(INSPECTOR_RECT, strRec.c_str());
        jsonNode->Put(INSPECTOR_DEBUGLINE, node->GetDebugLine().c_str());
        jsonNode->Put(INSPECTOR_VIEW_ID, node->GetViewId().c_str());
        auto jsonObject = JsonUtil::Create(true);

        InspectorFilter filter;
        parent->ToJsonValue(jsonObject, filter);
        jsonNode->PutRef(INSPECTOR_ATTRS, std::move(jsonObject));
    }
}

void GetInspectorChildren(const RefPtr<NG::UINode>& parent, std::unique_ptr<OHOS::Ace::JsonValue>& jsonNodeArray,
    InspectorChildrenParameters inspectorParameters, const InspectorFilter& filter = InspectorFilter(),
    uint32_t depth = UINT32_MAX)
{
    // Span is a special case in Inspector since span inherits from UINode
    if (AceType::InstanceOf<SpanNode>(parent)) {
        GetSpanInspector(parent, jsonNodeArray, inspectorParameters.pageId);
        return;
    }
    auto jsonNode = JsonUtil::Create(true);
    jsonNode->Put(INSPECTOR_TYPE, parent->GetTag().c_str());
    jsonNode->Put(INSPECTOR_ID, parent->GetId());
    auto node = AceType::DynamicCast<FrameNode>(parent);
    PutNodeInfoToJsonNode(node, inspectorParameters.isActive, jsonNode, parent);

    std::vector<RefPtr<NG::UINode>> children;
    for (const auto& item : parent->GetChildren()) {
        GetFrameNodeChildren(item, children, inspectorParameters.pageId);
    }
    if (node != nullptr) {
        auto overlayNode = node->GetOverlayNode();
        if (overlayNode != nullptr) {
            GetFrameNodeChildren(overlayNode, children, inspectorParameters.pageId);
        }
    }
    if (depth) {
        auto jsonChildrenArray = JsonUtil::CreateArray(true);
        for (auto uiNode : children) {
            GetInspectorChildren(uiNode, jsonChildrenArray, inspectorParameters, filter, depth - 1);
        }
        if (jsonChildrenArray->GetArraySize()) {
            jsonNode->PutRef(INSPECTOR_CHILDREN, std::move(jsonChildrenArray));
        }
    }
    jsonNodeArray->PutRef(std::move(jsonNode));
}

#else
void GetFrameNodeChildren(const RefPtr<NG::UINode>& uiNode, std::vector<RefPtr<NG::UINode>>& children,
    int32_t pageId, bool isLayoutInspector = false)
{
    if (AceType::InstanceOf<NG::FrameNode>(uiNode) || AceType::InstanceOf<SpanNode>(uiNode) ||
        AceType::InstanceOf<CustomNode>(uiNode)) {
        if (uiNode->GetTag() == "stage") {
        } else if (uiNode->GetTag() == "page") {
            if (uiNode->GetPageId() != pageId) {
                return;
            }
        } else {
            auto custom = AceType::DynamicCast<NG::CustomNode>(uiNode);
            auto frameNode = AceType::DynamicCast<NG::FrameNode>(uiNode);
            auto spanNode = AceType::DynamicCast<NG::SpanNode>(uiNode);
            if ((frameNode && !frameNode->IsInternal()) || spanNode || (custom && isLayoutInspector)) {
                children.emplace_back(uiNode);
                return;
            }
        }
    }
    for (const auto& frameChild : uiNode->GetChildren()) {
        GetFrameNodeChildren(frameChild, children, pageId, isLayoutInspector);
    }
}

void GetSpanInspector(
    const RefPtr<NG::UINode>& parent, std::unique_ptr<OHOS::Ace::JsonValue>& jsonNodeArray, int pageId)
{
    // span rect follows parent text size
    auto spanParentNode = parent->GetParent();
    while (spanParentNode != nullptr) {
        if (AceType::InstanceOf<NG::FrameNode>(spanParentNode)) {
            break;
        }
        spanParentNode = spanParentNode->GetParent();
    }
    CHECK_NULL_VOID(spanParentNode);
    auto node = AceType::DynamicCast<FrameNode>(spanParentNode);
    auto jsonNode = JsonUtil::Create(true);
    auto jsonObject = JsonUtil::Create(true);

    InspectorFilter filter;
    parent->ToJsonValue(jsonObject, filter);
    jsonNode->PutRef(INSPECTOR_ATTRS, std::move(jsonObject));
    jsonNode->Put(INSPECTOR_TYPE, parent->GetTag().c_str());
    jsonNode->Put(INSPECTOR_ID, parent->GetId());
    jsonNode->Put(INSPECTOR_DEBUGLINE, parent->GetDebugLine().c_str());
    RectF rect = node->GetTransformRectRelativeToWindow();
    jsonNode->Put(INSPECTOR_RECT, rect.ToBounds().c_str());
    jsonNodeArray->PutRef(std::move(jsonNode));
}

void GetCustomNodeInfo(const RefPtr<NG::UINode> &customNode, std::unique_ptr<OHOS::Ace::JsonValue> &jsonNode)
{
    // custom node rect follows parent size
    auto hostNode = customNode->GetParent();
    while (hostNode != nullptr) {
        if (AceType::InstanceOf<NG::FrameNode>(hostNode)) {
            break;
        }
        hostNode = hostNode->GetParent();
    }
    CHECK_NULL_VOID(hostNode);
    jsonNode->Put(INSPECTOR_COMPONENT_TYPE, "custom");
    auto node = AceType::DynamicCast<CustomNode>(customNode);
    CHECK_NULL_VOID(node);
    auto nodeExtraInfo = node->GetExtraInfo();
    std::stringstream ss;
    ss << nodeExtraInfo.page << "(" << nodeExtraInfo.line << ":" << nodeExtraInfo.col << ")";
    auto jsonJumpLine = JsonUtil::Create(true);
    jsonJumpLine->Put("$line", ss.str().c_str());
    auto parentNode = AceType::DynamicCast<FrameNode>(hostNode);
    jsonNode->Put(INSPECTOR_STATE_VAR, node->GetStateInspectorInfo());
    RectF rect = parentNode->GetTransformRectRelativeToWindow();
    jsonNode->Put(INSPECTOR_RECT, rect.ToBounds().c_str());
    jsonNode->Put(INSPECTOR_DEBUGLINE, jsonJumpLine->ToString().c_str());
    jsonNode->Put(INSPECTOR_CUSTOM_VIEW_TAG, node->GetCustomTag().c_str());
}

void PutNodeInfoToJsonNode(RefPtr<OHOS::Ace::NG::FrameNode>& node,
    bool& isActive, std::unique_ptr<OHOS::Ace::JsonValue>& jsonNode)
{
    if (node) {
        RectF rect;
        isActive = isActive && node->IsActive();
        if (isActive) {
            rect = node->GetTransformRectRelativeToWindow();
        }
        jsonNode->Put(INSPECTOR_RECT, rect.ToBounds().c_str());
        jsonNode->Put(INSPECTOR_DEBUGLINE, node->GetDebugLine().c_str());
    }
}

void GetInspectorChildren(const RefPtr<NG::UINode>& parent, std::unique_ptr<OHOS::Ace::JsonValue>& jsonNodeArray,
    InspectorChildrenParameters inspectorParameters, const InspectorFilter& filter = InspectorFilter(),
    uint32_t depth = UINT32_MAX)
{
    // Span is a special case in Inspector since span inherits from UINode
    if (AceType::InstanceOf<SpanNode>(parent)) {
        GetSpanInspector(parent, jsonNodeArray, inspectorParameters.pageId);
        return;
    }
    if (AceType::InstanceOf<CustomNode>(parent) && !inspectorParameters.isLayoutInspector) {
        return;
    }
    auto jsonNode = JsonUtil::Create(true);
    jsonNode->Put(INSPECTOR_TYPE, parent->GetTag().c_str());
    jsonNode->Put(INSPECTOR_ID, parent->GetId());
    if (parent->GetTag() == V2::JS_VIEW_ETS_TAG) {
        GetCustomNodeInfo(parent, jsonNode);
    } else {
        jsonNode->Put(INSPECTOR_COMPONENT_TYPE, "build-in");
    }
    auto node = AceType::DynamicCast<FrameNode>(parent);
    PutNodeInfoToJsonNode(node, inspectorParameters.isActive, jsonNode);
    auto jsonObject = JsonUtil::Create(true);
    parent->ToJsonValue(jsonObject, filter);
    jsonNode->PutRef(INSPECTOR_ATTRS, std::move(jsonObject));
    std::string jsonNodeStr = jsonNode->ToString();
    ConvertIllegalStr(jsonNodeStr);
    auto jsonNodeNew = JsonUtil::ParseJsonString(jsonNodeStr);
    if (jsonNodeNew == nullptr || !jsonNodeNew->IsValid()) {
        LOGW("inspector info of %{public}s-%{public}d is illegal", parent->GetTag().c_str(), parent->GetId());
        return;
    }
    std::vector<RefPtr<NG::UINode>> children;
    for (const auto& item : parent->GetChildren()) {
        GetFrameNodeChildren(item, children, inspectorParameters.pageId, inspectorParameters.isLayoutInspector);
    }
    if (node) {
        auto overlayNode = node->GetOverlayNode();
        if (overlayNode != nullptr) {
            GetFrameNodeChildren(overlayNode, children, inspectorParameters.pageId,
                inspectorParameters.isLayoutInspector);
        }
    }
    if (depth) {
        auto jsonChildrenArray = JsonUtil::CreateArray(true);
        for (auto uiNode : children) {
            GetInspectorChildren(uiNode, jsonChildrenArray, inspectorParameters, filter, depth - 1);
        }
        if (jsonChildrenArray->GetArraySize()) {
            jsonNodeNew->PutRef(INSPECTOR_CHILDREN, std::move(jsonChildrenArray));
        }
    }
    jsonNodeArray->PutRef(std::move(jsonNodeNew));
}
#endif

void GenerateParameters(InspectorChildrenParameters& inspectorParameters,
    int32_t& pageId, bool isActive, bool isLayoutInspector = false)
{
    inspectorParameters.pageId = pageId;
    inspectorParameters.isActive = isActive;
    inspectorParameters.isLayoutInspector = isLayoutInspector;
}

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

void GetContextInfo(const RefPtr<PipelineContext>& context, std::unique_ptr<JsonValue>& jsonRoot)
{
    auto scale = context->GetViewScale();
    auto rootHeight = context->GetRootHeight();
    auto rootWidth = context->GetRootWidth();
    deviceRect.SetRect(0, 0, rootWidth * scale, rootHeight * scale);
    jsonRoot->Put(INSPECTOR_WIDTH, std::to_string(rootWidth * scale).c_str());
    jsonRoot->Put(INSPECTOR_HEIGHT, std::to_string(rootHeight * scale).c_str());
    jsonRoot->Put(INSPECTOR_RESOLUTION, std::to_string(PipelineBase::GetCurrentDensity()).c_str());
}

std::string GetInspectorInfo(std::vector<RefPtr<NG::UINode>> children, int32_t pageId,
    std::unique_ptr<JsonValue> jsonRoot, bool isLayoutInspector, const InspectorFilter& filter = InspectorFilter())
{
    auto jsonNodeArray = JsonUtil::CreateArray(true);
    auto depth = filter.GetFilterDepth();
    InspectorChildrenParameters inspectorParameters;
    GenerateParameters(inspectorParameters, pageId, true, isLayoutInspector);
    for (auto& uiNode : children) {
        GetInspectorChildren(uiNode, jsonNodeArray, inspectorParameters, filter, depth - 1);
    }
    if (jsonNodeArray->GetArraySize()) {
        jsonRoot->PutRef(INSPECTOR_CHILDREN, std::move(jsonNodeArray));
    }

    if (isLayoutInspector) {
        auto jsonTree = JsonUtil::Create(true);
        jsonTree->Put("type", "root");
        jsonTree->PutRef("content", std::move(jsonRoot));
        auto pipeline = PipelineContext::GetCurrentContextSafely();
        if (pipeline) {
            jsonTree->Put("VsyncID", (int32_t)pipeline->GetFrameCount());
            jsonTree->Put("ProcessID", getpid());
            jsonTree->Put("WindowID", (int32_t)pipeline->GetWindowId());
        }
        return jsonTree->ToString();
    }

    return jsonRoot->ToString();
}
} // namespace

std::set<RefPtr<FrameNode>> Inspector::offscreenNodes;

RefPtr<FrameNode> Inspector::GetFrameNodeByKey(const std::string& key, bool notDetach, bool skipoffscreenNodes)
{
    // 如果查找的目标节点确定是已经挂树的节点，可以跳过offscreenNodes的遍历，避免offscreenNodes过多的情况消耗性能。
    if (!offscreenNodes.empty() && !skipoffscreenNodes) {
        for (auto node : offscreenNodes) {
            auto frameNode = AceType::DynamicCast<FrameNode>(GetInspectorByKey(node, key, notDetach));
            if (frameNode) {
                return frameNode;
            }
        }
    }
    auto context = NG::PipelineContext::GetCurrentContextSafely();
    if (!context) {
        LOGW("Internal error! Context is null.");
        return nullptr;
    }
    auto rootNode = context->GetRootElement();
    if (!rootNode) {
        LOGW("Internal error! RootNode is null.");
        return nullptr;
    }

    return AceType::DynamicCast<FrameNode>(GetInspectorByKey(rootNode, key, notDetach));
}

std::string Inspector::GetInspectorNodeByKey(const std::string& key, const InspectorFilter& filter)
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
    std::string debugLine = inspectorElement->GetDebugLine();
    jsonNode->Put(INSPECTOR_DEBUGLINE, debugLine.c_str());

    inspectorElement->ToJsonValue(jsonAttrs, filter);
    jsonNode->PutRef(INSPECTOR_ATTRS, std::move(jsonAttrs));
    return jsonNode->ToString();
}

void Inspector::GetRectangleById(const std::string& key, Rectangle& rectangle)
{
    auto frameNode = Inspector::GetFrameNodeByKey(key, true);
    if (!frameNode) {
        LOGW("Can't find component, check your parameters");
        return;
    }
    rectangle.size = frameNode->GetGeometryNode()->GetFrameSize();
    auto context = frameNode->GetRenderContext();
    if (!context) {
        LOGW("Internal error! Component(id=%{public}d, tag=%{public}s) is null",
            frameNode->GetId(), frameNode->GetTag().c_str());
        return;
    }
    rectangle.localOffset = context->GetPaintRectWithTransform().GetOffset();
    rectangle.windowOffset = frameNode->GetOffsetRelativeToWindow();
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto container = Container::Current();
    if (container && container->IsDynamicRender() &&
        container->GetUIContentType() == UIContentType::DYNAMIC_COMPONENT) {
        rectangle.windowOffset = rectangle.windowOffset + OffsetF(pipeline->GetHostParentOffsetToWindow().GetX(),
            pipeline->GetHostParentOffsetToWindow().GetY());
    }
    rectangle.screenRect = pipeline->GetCurrentWindowRect();
    ACE_SCOPED_TRACE("Inspector::GetRectangleById_Id=%d_Tag=%s_Key=%s",
        frameNode->GetId(), frameNode->GetTag().c_str(), key.c_str());
    TAG_LOGD(AceLogTag::ACE_LAYOUT_INSPECTOR, "GetRectangleById Id:%{public}d key:%{public}s localOffset:%{public}s"
         "screenRect:%{public}s",
        frameNode->GetId(), key.c_str(), rectangle.localOffset.ToString().c_str(),
        rectangle.screenRect.ToString().c_str());
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    Matrix4 defMatrix4 = Matrix4::CreateIdentity();
    Matrix4 matrix4 = renderContext->GetTransformMatrixValue(defMatrix4);
    rectangle.matrix4 = matrix4;
    auto rect = renderContext->GetPaintRectWithoutTransform();
    const double halfDimension = 50.0;
    auto center = renderContext->GetTransformCenter().value_or(DimensionOffset(
        Dimension(halfDimension, DimensionUnit::PERCENT), Dimension(halfDimension, DimensionUnit::PERCENT)));
    double centerX = 0.0;
    double centerY = 0.0;
    if (center.GetX().Unit() == DimensionUnit::PERCENT || center.GetY().Unit() == DimensionUnit::PERCENT) {
        if (rect.IsValid()) {
            centerX = Dimension(center.GetX().ConvertToPxWithSize(rect.Width()), DimensionUnit::PX).ConvertToVp();
            centerY = Dimension(center.GetY().ConvertToPxWithSize(rect.Height()), DimensionUnit::PX).ConvertToVp();
        }
    } else {
        centerX = center.GetX().ConvertToVp();
        centerY = center.GetY().ConvertToVp();
    }
    VectorF defScale = VectorF(1.0, 1.0);
    VectorF scale = renderContext->GetTransformScaleValue(defScale);
    rectangle.scale.x = scale.x;
    rectangle.scale.y = scale.y;
    rectangle.scale.z = 1.0;
    rectangle.scale.centerX = centerX;
    rectangle.scale.centerY = centerY;
    Vector5F defRotate = Vector5F(0.0, 0.0, 0.0, 0.0, 0.0);
    Vector5F rotate = renderContext->GetTransformRotateValue(defRotate);
    rectangle.rotate.x = rotate.x;
    rectangle.rotate.y = rotate.y;
    rectangle.rotate.z = rotate.z;
    rectangle.rotate.angle = rotate.w;
    rectangle.rotate.centerX = centerX;
    rectangle.rotate.centerY = centerY;
    TranslateOptions defTranslate = TranslateOptions(0.0, 0.0, 0.0);
    TranslateOptions translate = renderContext->GetTransformTranslateValue(defTranslate);
    if ((translate.x.Unit() == DimensionUnit::PERCENT) && rect.IsValid()) {
        rectangle.translate.x =
            Dimension(translate.x.ConvertToPxWithSize(rect.Width()), DimensionUnit::PX).ConvertToVp();
    } else {
        rectangle.translate.x = translate.x.ConvertToVp();
    }
    if ((translate.y.Unit() == DimensionUnit::PERCENT) && rect.IsValid()) {
        rectangle.translate.y =
            Dimension(translate.y.ConvertToPxWithSize(rect.Height()), DimensionUnit::PX).ConvertToVp();
    } else {
        rectangle.translate.y = translate.y.ConvertToVp();
    }
    rectangle.translate.z = translate.z.ConvertToVp();
}

std::string Inspector::GetInspector(bool isLayoutInspector)
{
    InspectorFilter filter;
    bool needThrow = false;
    return GetInspector(isLayoutInspector, filter, needThrow);
}

std::string Inspector::GetInspector(bool isLayoutInspector, const InspectorFilter& filter, bool& needThrow)
{
    auto jsonRoot = JsonUtil::Create(true);
    jsonRoot->Put(INSPECTOR_TYPE, INSPECTOR_ROOT);
    needThrow = false;
    auto context = NG::PipelineContext::GetCurrentContext();
    if (context == nullptr) {
        needThrow = true;
        return jsonRoot->ToString();
    }
    GetContextInfo(context, jsonRoot);

    RefPtr<UINode> pageRootNode;
    const std::string key = filter.GetFilterID();
    if (key.empty()) {
        pageRootNode = context->GetStageManager()->GetLastPage();
    } else {
        auto rootNode = context->GetStageManager()->GetLastPage();
        if (rootNode == nullptr) {
            needThrow = true;
            return jsonRoot->ToString();
        }
        pageRootNode = GetInspectorByKey(rootNode, key);
    }
    if (pageRootNode == nullptr) {
        needThrow = true;
        return jsonRoot->ToString();
    }
    auto pageId = context->GetStageManager()->GetLastPage()->GetPageId();
    std::vector<RefPtr<NG::UINode>> children;
    if (key.empty()) {
        for (const auto& item : pageRootNode->GetChildren()) {
            GetFrameNodeChildren(item, children, pageId, isLayoutInspector);
        }
        auto overlayNode = GetOverlayNode(pageRootNode);
        if (overlayNode) {
            GetFrameNodeChildren(overlayNode, children, pageId, isLayoutInspector);
        }
    } else {
        children.emplace_back(pageRootNode);
    }
    return GetInspectorInfo(children, pageId, std::move(jsonRoot), isLayoutInspector, filter);
}

std::string Inspector::GetInspectorOfNode(RefPtr<NG::UINode> node)
{
    auto jsonRoot = JsonUtil::Create(true);

    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, jsonRoot->ToString());
    GetContextInfo(context, jsonRoot);
    CHECK_NULL_RETURN(node, jsonRoot->ToString());
    RefPtr<UINode> lastPage = context->GetStageManager()->GetLastPage();
    CHECK_NULL_RETURN(lastPage, jsonRoot->ToString());
    auto pageId = lastPage->GetPageId();
    auto jsonNodeArray = JsonUtil::CreateArray(true);
    InspectorChildrenParameters inspectorParameters;
    GenerateParameters(inspectorParameters, pageId, true);
    GetInspectorChildren(node, jsonNodeArray, inspectorParameters, InspectorFilter(), 0);
    if (jsonNodeArray->GetArraySize()) {
        jsonRoot = jsonNodeArray->GetArrayItem(0);
        GetContextInfo(context, jsonRoot);
    }

    return jsonRoot->ToString();
}

RefPtr<UINode> Inspector::GetInspectorByKey(const RefPtr<FrameNode>& root, const std::string& key, bool notDetach)
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

        const auto& children = current->GetChildren(notDetach);
        for (const auto& child : children) {
            elements.push(child);
        }
    }
    return nullptr;
}

std::string Inspector::GetSubWindowInspector(bool isLayoutInspector)
{
    auto jsonRoot = JsonUtil::Create(true);
    jsonRoot->Put(INSPECTOR_TYPE, INSPECTOR_ROOT);

    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, jsonRoot->ToString());
    GetContextInfo(context, jsonRoot);
    auto overlayNode = context->GetOverlayManager()->GetRootNode().Upgrade();
    CHECK_NULL_RETURN(overlayNode, jsonRoot->ToString());
    auto pageId = 0;
    std::vector<RefPtr<NG::UINode>> children;
    GetFrameNodeChildren(overlayNode, children, pageId, isLayoutInspector);

    return GetInspectorInfo(children, 0, std::move(jsonRoot), isLayoutInspector);
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
            TouchEvent point;
            point.SetX(static_cast<float>(rect.Left() + rect.Width() / 2))
                .SetY(static_cast<float>(rect.Top() + rect.Height() / 2))
                .SetType(TouchType::DOWN)
                .SetTime(std::chrono::high_resolution_clock::now())
                .SetSourceType(SourceType::TOUCH);
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
                    taskExecutor.PostDelayedTask(inspectorTimer, LONG_PRESS_DELAY, "ArkUIInspectorLongPressTouchEvent");
                    break;
                }
                default:
                    break;
            }
        },
        TaskExecutor::TaskType::UI, "ArkUIInspectorSendEventByKey");

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

void Inspector::AddOffscreenNode(RefPtr<FrameNode> node)
{
    CHECK_NULL_VOID(node);
    offscreenNodes.insert(node);
}

void Inspector::RemoveOffscreenNode(RefPtr<FrameNode> node)
{
    CHECK_NULL_VOID(node);
    offscreenNodes.erase(node);
}

void Inspector::GetInspectorTree(InspectorTreeMap& treesInfo)
{
    treesInfo.clear();
    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto stageManager = context->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    RefPtr<UINode> pageRootNode = stageManager->GetLastPage();
    CHECK_NULL_VOID(pageRootNode);
    auto rootNode = AddInspectorTreeNode(pageRootNode, treesInfo);
    CHECK_NULL_VOID(rootNode);
    auto pageId = pageRootNode->GetPageId();
    std::vector<RefPtr<NG::UINode>> children;
    for (const auto& item : pageRootNode->GetChildren()) {
        GetFrameNodeChildren(item, children, pageId, false);
    }
    auto overlayNode = GetOverlayNode(pageRootNode);
    if (overlayNode) {
        GetFrameNodeChildren(overlayNode, children, pageId, false);
    }
    return GetInspectorTreeInfo(children, pageId, treesInfo);
}

void Inspector::RecordOnePageNodes(const RefPtr<NG::UINode>& pageNode, InspectorTreeMap& treesInfo)
{
    CHECK_NULL_VOID(pageNode);
    std::vector<RefPtr<NG::UINode>> children;
    auto pageId = pageNode->GetPageId();
    auto rootNode = AddInspectorTreeNode(pageNode, treesInfo);
    CHECK_NULL_VOID(rootNode);
    for (const auto& item : pageNode->GetChildren()) {
        GetFrameNodeChildren(item, children, pageId, true);
    }
    auto overlayNode = GetOverlayNode(pageNode);
    if (overlayNode) {
        GetFrameNodeChildren(overlayNode, children, pageId, true);
    }
    GetInspectorTreeInfo(children, pageId, treesInfo);
}

void Inspector::GetRecordAllPagesNodes(InspectorTreeMap& treesInfo)
{
    treesInfo.clear();
    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto stageManager = context->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    auto stageNode = stageManager->GetStageNode();
    CHECK_NULL_VOID(stageNode);
    for (const auto& item : stageNode->GetChildren()) {
        auto frameNode = AceType::DynamicCast<FrameNode>(item);
        if (frameNode == nullptr) {
            continue;
        }
        auto pagePattern = frameNode->GetPattern<PagePattern>();
        if (pagePattern == nullptr) {
            continue;
        }
        RecordOnePageNodes(item, treesInfo);
    }
}

RefPtr<RecNode> Inspector::AddInspectorTreeNode(const RefPtr<NG::UINode>& uiNode, InspectorTreeMap& recNodes)
{
    CHECK_NULL_RETURN(uiNode, nullptr);
    RefPtr<RecNode> recNode = AceType::MakeRefPtr<RecNode>();
    CHECK_NULL_RETURN(recNode, nullptr);
    recNode->SetNodeId(uiNode->GetId());
    std::string strTag = uiNode->GetTag();
    ConvertIllegalStr(strTag);
    recNode->SetName(strTag);
    std::string strDebugLine = uiNode->GetDebugLine();
    ConvertIllegalStr(strDebugLine);
    recNode->SetDebugLine(strDebugLine);
    auto frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    recNode->SetSelfId(renderContext->GetNodeId());
    auto parentNode = frameNode->GetParent();
    if (parentNode != nullptr) {
        recNode->SetParentId(parentNode->GetId());
    }
    recNodes.emplace(uiNode->GetId(), recNode);
    return recNode;
}

void Inspector::GetInspectorTreeInfo(
    std::vector<RefPtr<NG::UINode>> children, int32_t pageId, InspectorTreeMap& recNodes)
{
    for (auto& uiNode : children) {
        AddInspectorTreeNode(uiNode, recNodes);
        GetInspectorChildrenInfo(uiNode, recNodes, pageId);
    }
}

void Inspector::GetInspectorChildrenInfo(
    const RefPtr<NG::UINode>& parent, InspectorTreeMap& recNodes, int32_t pageId, uint32_t depth)
{
    // Span is a special case in Inspector since span inherits from UINode
    if (AceType::InstanceOf<SpanNode>(parent)) {
        return;
    }
    std::vector<RefPtr<NG::UINode>> children;
    for (const auto& item : parent->GetChildren()) {
        GetFrameNodeChildren(item, children, pageId, true);
    }
    auto node = AceType::DynamicCast<FrameNode>(parent);
    if (node != nullptr) {
        auto overlayNode = node->GetOverlayNode();
        if (overlayNode != nullptr) {
            GetFrameNodeChildren(overlayNode, children, pageId, false);
        }
    }
    if (depth) {
        for (auto uiNode : children) {
            AddInspectorTreeNode(uiNode, recNodes);
            GetInspectorChildrenInfo(uiNode, recNodes, pageId, depth - 1);
        }
    }
}

void Inspector::GetOffScreenTreeNodes(InspectorTreeMap& nodes)
{
    for (const auto& item : offscreenNodes) {
        AddInspectorTreeNode(item, nodes);
    }
}

std::pair<uint32_t, int32_t> Inspector::ParseWindowIdFromMsg(const std::string& message)
{
    TAG_LOGD(AceLogTag::ACE_LAYOUT_INSPECTOR, "start process inspector get window msg");
    uint32_t windowId = INVALID_WINDOW_ID;
    int32_t methodIndex = INVALID_METHOD_ID;
    auto json = JsonUtil::ParseJsonString(message);
    if (json == nullptr || !json->IsValid() || !json->IsObject()) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "input message is invalid");
        return {windowId, methodIndex};
    }
    auto methodVal = json->GetString(KEY_METHOD);
    auto it = std::find(SUPPORT_METHOD.begin(), SUPPORT_METHOD.end(), methodVal);
    if (it == SUPPORT_METHOD.end()) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "method is not supported");
        return {windowId, methodIndex};
    }
    methodIndex = std::distance(SUPPORT_METHOD.begin(), it);
    auto paramObj = json->GetObject(KEY_PARAMS);
    if (paramObj == nullptr || !paramObj->IsValid() || !paramObj->IsObject()) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "input message params is invalid");
        return {windowId, methodIndex};
    }
    windowId = StringUtils::StringToUint(paramObj->GetString("windowId"));
    return {windowId, methodIndex};
}
} // namespace OHOS::Ace::NG
