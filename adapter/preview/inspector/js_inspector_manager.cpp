/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "adapter/preview/inspector/js_inspector_manager.h"

#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>

#include "adapter/preview/inspector/inspector_client.h"
#ifdef NG_BUILD
#include "frameworks/bridge/declarative_frontend/ng/declarative_frontend_ng.h"
#else
#include "bridge/declarative_frontend/declarative_frontend.h"
#endif
#include "core/components_ng/base/inspector.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_v2/inspector/shape_composed_element.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::Framework {
namespace {

constexpr char INSPECTOR_CURRENT_VERSION[] = "1.0";
constexpr char INSPECTOR_DEVICE_TYPE[] = "deviceType";
constexpr char INSPECTOR_DEFAULT_VALUE[] = "defaultValue";
constexpr char INSPECTOR_TYPE[] = "$type";
constexpr char INSPECTOR_ROOT[] = "root";
constexpr char INSPECTOR_VERSION[] = "version";
constexpr char INSPECTOR_WIDTH[] = "width";
constexpr char INSPECTOR_HEIGHT[] = "height";
constexpr char INSPECTOR_RESOLUTION[] = "$resolution";
constexpr char INSPECTOR_CHILDREN[] = "$children";
constexpr char INSPECTOR_ID[] = "$ID";
constexpr char INSPECTOR_RECT[] = "$rect";
constexpr char INSPECTOR_Z_INDEX[] = "$z-index";
constexpr char INSPECTOR_ATTRS[] = "$attrs";
constexpr char INSPECTOR_STYLES[] = "$styles";
constexpr char INSPECTOR_INNER_DEBUGLINE[] = "debugLine";
constexpr char INSPECTOR_DEBUGLINE[] = "$debugLine";
constexpr char INSPECTOR_VIEW_ID[] = "$viewID";

std::list<std::string> specialComponentNameV1 = { "dialog", "panel" };

} // namespace

std::string GetDeviceTypeStr(const DeviceType& deviceType)
{
    std::string deviceName = "";
    if (deviceType == DeviceType::TV) {
        deviceName = "TV";
    } else if (deviceType == DeviceType::WATCH) {
        deviceName = "Watch";
    } else if (deviceType == DeviceType::CAR) {
        deviceName = "Car";
    } else {
        deviceName = "Phone";
    }
    return deviceName;
}

void JsInspectorManager::InitializeCallback()
{
    auto assembleJSONTreeCallback = [weak = WeakClaim(this)](std::string& jsonTreeStr) {
        auto jsInspectorManager = weak.Upgrade();
        if (!jsInspectorManager) {
            return false;
        }
        jsInspectorManager->AssembleJSONTree(jsonTreeStr);
        return true;
    };
    InspectorClient::GetInstance().RegisterJSONTreeCallback(assembleJSONTreeCallback);
    auto assembleDefaultJSONTreeCallback = [weak = WeakClaim(this)](std::string& jsonTreeStr) {
        auto jsInspectorManager = weak.Upgrade();
        if (!jsInspectorManager) {
            return false;
        }
        jsInspectorManager->AssembleDefaultJSONTree(jsonTreeStr);
        return true;
    };
    InspectorClient::GetInstance().RegisterDefaultJSONTreeCallback(assembleDefaultJSONTreeCallback);
    auto operateComponentCallback = [weak = WeakClaim(this)](const std::string& attrsJson) {
        auto jsInspectorManager = weak.Upgrade();
        if (!jsInspectorManager) {
            return false;
        }
        return jsInspectorManager->OperateComponent(attrsJson);
    };
    InspectorClient::GetInstance().RegisterOperateComponentCallback(operateComponentCallback);
}

// resourse the child from root node to assemble the JSON tree
void JsInspectorManager::AssembleJSONTree(std::string& jsonStr)
{
    if (Container::IsCurrentUseNewPipeline()) {
        jsonStr = NG::Inspector::GetInspector(false);
        return;
    }
    auto jsonNode = JsonUtil::Create(true);
    jsonNode->Put(INSPECTOR_TYPE, INSPECTOR_ROOT);

    auto context = GetPipelineContext().Upgrade();
    if (context) {
        float scale = context->GetViewScale();
        double rootHeight = context->GetRootHeight();
        double rootWidth = context->GetRootWidth();
        deviceRect_ = Rect(0, 0, rootWidth * scale, rootHeight * scale);
        jsonNode->Put(INSPECTOR_WIDTH, std::to_string(rootWidth * scale).c_str());
        jsonNode->Put(INSPECTOR_HEIGHT, std::to_string(rootHeight * scale).c_str());
    }
    jsonNode->Put(INSPECTOR_RESOLUTION, std::to_string(PipelineBase::GetCurrentDensity()).c_str());
    auto node = GetAccessibilityNodeFromPage(0);
    if (!node) {
        return;
    }
    jsonNode->Put(INSPECTOR_CHILDREN, GetChildrenJson(node));
    jsonStr = jsonNode->ToString();
}

// find children of the current node and combine them with this node to form a JSON array object.
std::unique_ptr<JsonValue> JsInspectorManager::GetChildrenJson(RefPtr<AccessibilityNode> node)
{
    auto jsonNodeArray = JsonUtil::CreateArray(true);
    if (!node) {
        return jsonNodeArray;
    }
    auto child = node->GetChildList();
    for (auto item = child.begin(); item != child.end(); item++) {
        jsonNodeArray->Put(GetChildJson(*item));
    }
    return jsonNodeArray;
}

std::unique_ptr<JsonValue> JsInspectorManager::GetChildJson(RefPtr<AccessibilityNode> node)
{
    auto jsonNode = JsonUtil::Create(true);
    if (!node) {
        return jsonNode;
    }
    if (node->GetTag() == "inspectDialog") {
        RemoveAccessibilityNodes(node);
        return jsonNode;
    }

    jsonNode->Put(INSPECTOR_TYPE, node->GetTag().c_str());
    jsonNode->Put(INSPECTOR_ID, node->GetNodeId());
    jsonNode->Put(INSPECTOR_Z_INDEX, node->GetZIndex());
    if (GetVersion() == AccessibilityVersion::JS_VERSION) {
        jsonNode->Put(INSPECTOR_RECT, UpdateNodeRectStrInfo(node).c_str());
        GetAttrsAndStyles(jsonNode, node);
    } else {
        jsonNode->Put(INSPECTOR_RECT, UpdateNodeRectStrInfoV2(node).c_str());
        GetAttrsAndStylesV2(jsonNode, node);
    }
    jsonNode->Put(INSPECTOR_CHILDREN, GetChildrenJson(node));
    return jsonNode;
}

// assemble the default attrs and styles for all components
void JsInspectorManager::AssembleDefaultJSONTree(std::string& jsonStr)
{
    auto jsonNode = JsonUtil::Create(true);
    std::string deviceName = GetDeviceTypeStr(SystemProperties::GetDeviceType());

    jsonNode->Put(INSPECTOR_VERSION, INSPECTOR_CURRENT_VERSION);
    jsonNode->Put(INSPECTOR_DEVICE_TYPE, deviceName.c_str());
    static const std::vector<std::string> tagNames = { DOM_NODE_TAG_BADGE, DOM_NODE_TAG_BUTTON, DOM_NODE_TAG_CAMERA,
        DOM_NODE_TAG_CANVAS, DOM_NODE_TAG_CHART, DOM_NODE_TAG_DIALOG, DOM_NODE_TAG_DIV, DOM_NODE_TAG_DIVIDER,
        DOM_NODE_TAG_FORM, DOM_NODE_TAG_GRID_COLUMN, DOM_NODE_TAG_GRID_CONTAINER, DOM_NODE_TAG_GRID_ROW,
        DOM_NODE_TAG_IMAGE, DOM_NODE_TAG_IMAGE_ANIMATOR, DOM_NODE_TAG_INPUT, DOM_NODE_TAG_LABEL, DOM_NODE_TAG_LIST,
        DOM_NODE_TAG_LIST_ITEM, DOM_NODE_TAG_LIST_ITEM_GROUP, DOM_NODE_TAG_MARQUEE, DOM_NODE_TAG_MENU,
        DOM_NODE_TAG_NAVIGATION_BAR, DOM_NODE_TAG_OPTION, DOM_NODE_TAG_PANEL, DOM_NODE_TAG_PICKER_DIALOG,
        DOM_NODE_TAG_PICKER_VIEW, DOM_NODE_TAG_PIECE, DOM_NODE_TAG_POPUP, DOM_NODE_TAG_PROGRESS, DOM_NODE_TAG_QRCODE,
        DOM_NODE_TAG_RATING, DOM_NODE_TAG_REFRESH, DOM_NODE_TAG_SEARCH, DOM_NODE_TAG_SELECT, DOM_NODE_TAG_SLIDER,
        DOM_NODE_TAG_SPAN, DOM_NODE_TAG_STACK, DOM_NODE_TAG_STEPPER, DOM_NODE_TAG_STEPPER_ITEM, DOM_NODE_TAG_SWIPER,
        DOM_NODE_TAG_SWITCH, DOM_NODE_TAG_TAB_BAR, DOM_NODE_TAG_TAB_CONTENT, DOM_NODE_TAG_TABS, DOM_NODE_TAG_TEXT,
        DOM_NODE_TAG_TEXTAREA, DOM_NODE_TAG_TOGGLE, DOM_NODE_TAG_TOOL_BAR, DOM_NODE_TAG_TOOL_BAR_ITEM,
        DOM_NODE_TAG_VIDEO };

    auto jsonDefaultValue = JsonUtil::Create(true);
    for (const auto& tag : tagNames) {
        auto jsonDefaultAttrs = JsonUtil::Create(true);
        if (!GetDefaultAttrsByType(tag, jsonDefaultAttrs)) {
            LOGW("node type %{public}s is invalid", tag.c_str());
            return;
        }
        jsonDefaultValue->Put(tag.c_str(), jsonDefaultAttrs);
    }
    jsonNode->Put(INSPECTOR_DEFAULT_VALUE, jsonDefaultValue);
    jsonStr = jsonNode->ToString();
}

bool JsInspectorManager::OperateComponent(const std::string& jsCode)
{
    auto root = JsonUtil::ParseJsonString(jsCode);
    auto parentID = root->GetInt("parentID", -1);
    auto slot = root->GetInt("slot", -1);
    if (Container::IsCurrentUseNewPipeline()) {
        static RefPtr<NG::UINode> parent = nullptr;
        auto newChild = GetNewFrameNodeWithJsCode(root);
        CHECK_NULL_RETURN(newChild, false); // newChild should not be nullptr
        NG::Inspector::HideAllMenus();
        if (!root->Contains("id")) {
            parent = (parentID <= 0) ? GetRootUINode() : ElementRegister::GetInstance()->GetUINodeById(parentID);
            return OperateGeneralUINode(parent, slot, newChild);
        }
        auto nodeId = root->GetInt("id");
        auto oldChild = ElementRegister::GetInstance()->GetUINodeById(nodeId);
        if (!oldChild) {
            // Quickly modify components
            auto iter = parents_.find(nodeId);
            if (iter != parents_.end()) {
                auto uiNode = iter->second.Upgrade()->GetChildAtIndex(slots_[nodeId]);
                slots_.emplace(uiNode->GetId(), slots_[nodeId]);
                parents_.emplace(uiNode->GetId(), parents_[nodeId]);
                return OperateGeneralUINode(parents_[uiNode->GetId()].Upgrade(), slots_[uiNode->GetId()], newChild);
            }
            return false;
        }
        parent = oldChild->GetParent();
        CHECK_NULL_RETURN(parent, false); // Parent should not be nullptr
        slot = parent->GetChildIndex(oldChild);
        slots_.emplace(nodeId, slot);
        parents_.emplace(nodeId, parent);
        return OperateGeneralUINode(parent, slot, newChild);
    } else {
        auto operateType = root->GetString("type", "");
        auto newComponent = GetNewComponentWithJsCode(root);
        if (parentID <= 0) {
            return OperateRootComponent(newComponent);
        } else {
            return OperateGeneralComponent(parentID, slot, operateType, newComponent);
        }
    }
}

bool JsInspectorManager::OperateRootComponent(RefPtr<Component> newComponent)
{
    if (!newComponent) {
        return false;
    }
    auto rootElement = GetRootElement().Upgrade();
    auto child = rootElement->GetChildBySlot(-1); // rootElement only has one child,and use the default slot -1

    rootElement->UpdateChildWithSlot(child, newComponent, -1, -1);
    return true;
}

bool JsInspectorManager::OperateGeneralComponent(
    int32_t parentID, int32_t slot, std::string& operateType, RefPtr<Component> newComponent)
{
    auto parentElement = GetInspectorElementById(parentID);
    if (!parentElement) {
        return false;
    }

    if (operateType == "DeleteComponent") {
        parentElement->DeleteChildWithSlot(slot);
        return true;
    }

    if (newComponent) {
        if (operateType == "AddComponent") {
            parentElement->AddChildWithSlot(slot, newComponent);
        }
        if (operateType == "UpdateComponent") {
            parentElement->UpdateChildWithSlot(slot, newComponent);
        }
        return true;
    }
    return false;
}

bool JsInspectorManager::OperateGeneralUINode(RefPtr<NG::UINode> parent, int32_t slot, RefPtr<NG::UINode> newChild)
{
    CHECK_NULL_RETURN(parent, false);
    parent->FastPreviewUpdateChild(slot, newChild);
    newChild->FastPreviewUpdateChildDone();
    newChild->FlushUpdateAndMarkDirty();
    parent->FlushUpdateAndMarkDirty();
    return true;
}

RefPtr<Component> JsInspectorManager::GetNewComponentWithJsCode(const std::unique_ptr<JsonValue>& root)
{
    std::string jsCode = root->GetString("jsCode", "");
    std::string viewID = root->GetString("viewID", "");
    if (jsCode.length() == 0) {
        LOGW("Get jsCode Failed");
        return nullptr;
    }
    auto context = context_.Upgrade();
    if (!context) {
        return nullptr;
    }
    auto frontend = context->GetFrontend();
    if (!frontend) {
        return nullptr;
    }
#ifdef NG_BUILD
    auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontendNG>(frontend);
#else
    auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontend>(frontend);
#endif
    if (!declarativeFrontend) {
        return nullptr;
    }
    auto component = declarativeFrontend->GetNewComponentWithJsCode(jsCode, viewID);
    return component;
}

RefPtr<NG::UINode> JsInspectorManager::GetNewFrameNodeWithJsCode(const std::unique_ptr<JsonValue>& root)
{
    std::string jsCode = root->GetString("jsCode", "");
    std::string viewID = root->GetString("viewID", "");
    if (jsCode.empty() || viewID.empty()) {
        return nullptr;
    }
    auto pipeline = context_.Upgrade();
    CHECK_NULL_RETURN(pipeline, nullptr);
#ifdef NG_BUILD
    auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontendNG>(pipeline->GetFrontend());
#else
    auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontend>(pipeline->GetFrontend());
#endif

    CHECK_NULL_RETURN(declarativeFrontend, nullptr);
    auto jsEngine = declarativeFrontend->GetJsEngine();
    CHECK_NULL_RETURN(jsEngine, nullptr);
    if (!jsEngine->ExecuteJsForFastPreview(jsCode, viewID)) {
        return nullptr;
    }
    return NG::ViewStackProcessor::GetInstance()->GetNewUINode();
}

RefPtr<V2::InspectorComposedElement> JsInspectorManager::GetInspectorElementById(NodeId nodeId)
{
    auto composedElement = GetComposedElementFromPage(nodeId).Upgrade();
    if (!composedElement) {
        return nullptr;
    }
    auto inspectorElement = AceType::DynamicCast<V2::InspectorComposedElement>(composedElement);
    if (!inspectorElement) {
        return nullptr;
    }
    return inspectorElement;
}

WeakPtr<Element> JsInspectorManager::GetRootElement()
{
    auto node = GetAccessibilityNodeFromPage(0);
    if (!node) {
        return nullptr;
    }
    auto child = node->GetChildList();
    if (child.empty()) {
        return nullptr;
    }
    auto InspectorComponentElement = GetInspectorElementById(child.front()->GetNodeId());
    if (!InspectorComponentElement) {
        return nullptr;
    }
    return InspectorComponentElement->GetElementParent();
}

const RefPtr<NG::UINode> JsInspectorManager::GetRootUINode()
{
    auto context = context_.Upgrade();
    auto ngContext = AceType::DynamicCast<NG::PipelineContext>(context);
    CHECK_NULL_RETURN(ngContext, nullptr);

    auto node = ngContext->GetStageManager()->GetLastPage();
    CHECK_NULL_RETURN(node, nullptr);
    auto child = node->GetLastChild();
    return child;
}

// get attrs and styles from AccessibilityNode to JsonValue
void JsInspectorManager::GetAttrsAndStyles(std::unique_ptr<JsonValue>& jsonNode, const RefPtr<AccessibilityNode>& node)
{
    auto attrJsonNode = JsonUtil::Create(true);
    for (auto attr : node->GetAttrs()) {
        // this attr is wrong in API5,will delete in API7
        if (attr.first.find("clickEffect") != std::string::npos) {
            attr.first = ConvertStrToPropertyType(attr.first);
        }
        attrJsonNode->Put(attr.first.c_str(), attr.second.c_str());
    }
    // change debugLine to $debugLine and move out of attrs
    std::string debugLine = attrJsonNode->GetString(INSPECTOR_INNER_DEBUGLINE);
    jsonNode->Put(INSPECTOR_DEBUGLINE, debugLine.c_str());
    attrJsonNode->Delete(INSPECTOR_INNER_DEBUGLINE);
    jsonNode->Put(INSPECTOR_ATTRS, attrJsonNode);

    auto styleJsonNode = JsonUtil::Create(true);
    for (auto style : node->GetStyles()) {
        if (!style.second.empty()) {
            styleJsonNode->Put(ConvertStrToPropertyType(style.first).c_str(), style.second.c_str());
        }
    }
    jsonNode->Put(INSPECTOR_STYLES, styleJsonNode);
}

void JsInspectorManager::GetAttrsAndStylesV2(
    std::unique_ptr<JsonValue>& jsonNode, const RefPtr<AccessibilityNode>& node)
{
    auto weakComposedElement = GetComposedElementFromPage(node->GetNodeId());
    auto composedElement = DynamicCast<V2::InspectorComposedElement>(weakComposedElement.Upgrade());
    if (!composedElement) {
        return;
    }
    std::string debugLine = composedElement->GetDebugLine();
    std::string viewId = composedElement->GetViewId();
    jsonNode->Put(INSPECTOR_DEBUGLINE, debugLine.c_str());
    jsonNode->Put(INSPECTOR_VIEW_ID, viewId.c_str());
    auto inspectorElement = AceType::DynamicCast<V2::InspectorComposedElement>(composedElement);
    if (inspectorElement) {
        auto jsonObject = inspectorElement->ToJsonObject();
        jsonObject->Put("viewId", viewId.c_str());
        jsonNode->Put(INSPECTOR_ATTRS, jsonObject);
    }
    auto shapeComposedElement = AceType::DynamicCast<V2::ShapeComposedElement>(inspectorElement);
    if (shapeComposedElement) {
        jsonNode->Replace(INSPECTOR_TYPE, shapeComposedElement->GetShapeType().c_str());
    }
}

std::string JsInspectorManager::UpdateNodeRectStrInfo(const RefPtr<AccessibilityNode> node)
{
    auto it = std::find(specialComponentNameV1.begin(), specialComponentNameV1.end(), node->GetTag());
    if (it != specialComponentNameV1.end()) {
        node->UpdateRectWithChildRect();
    }

    PositionInfo positionInfo = { 0, 0, 0, 0 };
    if (node->GetTag() == DOM_NODE_TAG_SPAN) {
        positionInfo = { node->GetParentNode()->GetWidth(), node->GetParentNode()->GetHeight(),
            node->GetParentNode()->GetLeft(), node->GetParentNode()->GetTop() };
    } else {
        positionInfo = { node->GetWidth(), node->GetHeight(), node->GetLeft(), node->GetTop() };
    }
    if (!node->GetVisible()) {
        positionInfo = { 0, 0, 0, 0 };
    }
    // the dialog node is hidden, while the position and size of the node are not cleared.
    if (node->GetClearRectInfoFlag() == true) {
        positionInfo = { 0, 0, 0, 0 };
    }
    std::string strRec = std::to_string(positionInfo.left)
                             .append(",")
                             .append(std::to_string(positionInfo.top))
                             .append(",")
                             .append(std::to_string(positionInfo.width))
                             .append(",")
                             .append(std::to_string(positionInfo.height));
    return strRec;
}

std::string JsInspectorManager::UpdateNodeRectStrInfoV2(const RefPtr<AccessibilityNode> node)
{
    std::string strRec;
    auto weakComposedElement = GetComposedElementFromPage(node->GetNodeId());
    auto composedElement = weakComposedElement.Upgrade();
    if (!composedElement) {
        return strRec;
    }
    auto inspectorElement = AceType::DynamicCast<V2::InspectorComposedElement>(composedElement);
    if (inspectorElement) {
        auto rect = inspectorElement->GetRenderRect();
        if (!rect.IsIntersectByCommonSideWith(deviceRect_)) {
            return "0,0,0,0";
        }
        strRec = inspectorElement->GetRect();
        return strRec;
    }
    return strRec;
}

std::string JsInspectorManager::ConvertStrToPropertyType(std::string& typeValue)
{
    if (typeValue == "transitionEnterName") {
        typeValue = "transitionEnter";
    } else if (typeValue == "transitionExitName") {
        typeValue = "transitionExit";
    }
    std::string dstStr;
    std::regex regex("([A-Z])");
    dstStr = regex_replace(typeValue, regex, "-$1");
    std::transform(dstStr.begin(), dstStr.end(), dstStr.begin(), ::tolower);
    return dstStr;
}

RefPtr<AccessibilityNodeManager> AccessibilityNodeManager::Create()
{
    return AceType::MakeRefPtr<JsInspectorManager>();
}
} // namespace OHOS::Ace::Framework
