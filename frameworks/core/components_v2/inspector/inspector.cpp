/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "inspector.h"

#include "shape_composed_element.h"

#include "core/components/page/page_element.h"
#include "core/components/root/root_element.h"

namespace OHOS::Ace::V2 {
namespace {
const char INSPECTOR_TYPE[] = "$type";
const char INSPECTOR_ROOT[] = "root";
const char INSPECTOR_WIDTH[] = "width";
const char INSPECTOR_HEIGHT[] = "height";
const char INSPECTOR_RESOLUTION[] = "$resolution";
const char INSPECTOR_CHILDREN[] = "$children";
const char INSPECTOR_ID[] = "$ID";
const char INSPECTOR_RECT[] = "$rect";
const char INSPECTOR_Z_INDEX[] = "$z-index";
const char INSPECTOR_ATTRS[] = "$attrs";
const char INSPECTOR_DEBUGLINE[] = "$debugLine";
constexpr int32_t INSPECTOR_DELAY_TIME = 1000;

RefPtr<V2::InspectorComposedElement> GetInspectorByKey(const RefPtr<RootElement>& root, const std::string& key)
{
    std::queue<RefPtr<Element>> elements;
    elements.push(root);
    RefPtr<V2::InspectorComposedElement> inspectorElement;
    while (!elements.empty()) {
        auto current = elements.front();
        elements.pop();
        inspectorElement = AceType::DynamicCast<V2::InspectorComposedElement>(current);
        if (inspectorElement != nullptr) {
            if (key == inspectorElement->GetKey()) {
                return inspectorElement;
            }
        }
        const auto& children = current->GetChildren();
        for (auto& child : children) {
            elements.push(child);
        }
    }
    return nullptr;
}

void GetInspectorChildren(const RefPtr<Element>& element, std::list<RefPtr<Element>>& childrenList)
{
    if (element->GetChildren().empty()) {
        return;
    }
    const auto& children = element->GetChildren();
    for (auto& childElement : children) {
        if (AceType::InstanceOf<V2::InspectorComposedElement>(childElement)) {
            childrenList.emplace_back(childElement);
        } else {
            GetInspectorChildren(childElement, childrenList);
        }
    }
}

void DumpInspectorTree(
    const RefPtr<Element>& element, std::map<RefPtr<Element>, std::list<RefPtr<Element>>>& inspectorTreeMap)
{
    std::list<RefPtr<Element>> childrenList;
    GetInspectorChildren(element, childrenList);
    if (childrenList.empty()) {
        return;
    }
    inspectorTreeMap.emplace(element, childrenList);
    for (const auto& child : childrenList) {
        DumpInspectorTree(child, inspectorTreeMap);
    }
}

void ToJsonValue(const RefPtr<Element>& element,
    const std::map<RefPtr<Element>, std::list<RefPtr<Element>>>& inspectorTree, std::unique_ptr<JsonValue>& json)
{
    auto inspectorElement = AceType::DynamicCast<V2::InspectorComposedElement>(element);
    if (inspectorElement == nullptr) {
        return;
    }
    json->Put(INSPECTOR_TYPE, inspectorElement->GetTag().c_str());
    auto shapeComposedElement = AceType::DynamicCast<V2::ShapeComposedElement>(element);
    if (shapeComposedElement != nullptr) {
        int type = StringUtils::StringToInt(shapeComposedElement->GetShapeType());
        json->Replace(INSPECTOR_TYPE, SHAPE_TYPE_STRINGS[type]);
    }
    json->Put(INSPECTOR_ID, std::stoi(inspectorElement->GetId()));
    json->Put(INSPECTOR_Z_INDEX, inspectorElement->GetZIndex());
    json->Put(INSPECTOR_RECT, inspectorElement->GetRenderRect().ToBounds().c_str());
    auto jsonObject = inspectorElement->ToJsonObject();
    json->Put(INSPECTOR_ATTRS, jsonObject);

    auto iter = inspectorTree.find(element);
    if (iter == inspectorTree.end()) {
        return;
    }

    auto jsonNodeArray = JsonUtil::CreateArray(true);
    for (const auto& child : iter->second) {
        auto jsonChild = JsonUtil::Create(true);
        ToJsonValue(child, inspectorTree, jsonChild);
        jsonNodeArray->Put(jsonChild);
    }
    json->Put(INSPECTOR_CHILDREN, jsonNodeArray);
}
} // namespace

std::string Inspector::GetInspectorNodeByKey(const RefPtr<PipelineContext>& context, const std::string& key)
{
    auto inspectorElement = GetInspectorByKey(context->GetRootElement(), key);
    if (inspectorElement == nullptr) {
        return "";
    }

    auto jsonNode = JsonUtil::Create(true);
    jsonNode->Put(INSPECTOR_TYPE, inspectorElement->GetTag().c_str());
    jsonNode->Put(INSPECTOR_ID, std::stoi(inspectorElement->GetId()));
    jsonNode->Put(INSPECTOR_Z_INDEX, inspectorElement->GetZIndex());
    jsonNode->Put(INSPECTOR_RECT, inspectorElement->GetRenderRect().ToBounds().c_str());
    std::string debugLine = inspectorElement->GetDebugLine();
    jsonNode->Put(INSPECTOR_DEBUGLINE, debugLine.c_str());
    auto jsonObject = inspectorElement->ToJsonObject();
    jsonNode->Put(INSPECTOR_ATTRS, jsonObject);
    return jsonNode->ToString();
}

std::string Inspector::GetInspectorTree(const RefPtr<PipelineContext>& context, bool isLayoutInspector)
{
    auto jsonRoot = JsonUtil::Create(true);
    jsonRoot->Put(INSPECTOR_TYPE, INSPECTOR_ROOT);

    float scale = context->GetViewScale();
    double rootHeight = context->GetRootHeight();
    double rootWidth = context->GetRootWidth();
    jsonRoot->Put(INSPECTOR_WIDTH, std::to_string(rootWidth * scale).c_str());
    jsonRoot->Put(INSPECTOR_HEIGHT, std::to_string(rootHeight * scale).c_str());
    jsonRoot->Put(INSPECTOR_RESOLUTION, std::to_string(PipelineBase::GetCurrentDensity()).c_str());

    auto root = AceType::DynamicCast<Element>(context->GetRootElement());
    if (root == nullptr) {
        return jsonRoot->ToString();
    }

    auto pageElement = AceType::DynamicCast<Element>(context->GetLastPage());
    if (pageElement == nullptr) {
        return jsonRoot->ToString();
    }
    std::map<RefPtr<Element>, std::list<RefPtr<Element>>> inspectorTree;
    DumpInspectorTree(pageElement, inspectorTree);
    auto pageChildren = inspectorTree.find(pageElement);
    if (pageChildren != inspectorTree.end()) {
        auto jsonNodeArray = JsonUtil::CreateArray(true);
        for (const auto& child : pageChildren->second) {
            auto jsonChild = JsonUtil::Create(true);
            ToJsonValue(child, inspectorTree, jsonChild);
            jsonNodeArray->Put(jsonChild);
        }
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

bool Inspector::SendEventByKey(
    const RefPtr<PipelineContext>& context, const std::string& key, int action, const std::string& params)
{
    auto inspectorElement = GetInspectorByKey(context->GetRootElement(), key);
    if (inspectorElement == nullptr) {
        return false;
    }

    Rect rect = inspectorElement->GetRenderRect();

    context->GetTaskExecutor()->PostTask(
        [weak = AceType::WeakClaim(AceType::RawPtr(context)), rect, action, params, inspectorElement]() {
            auto context = weak.Upgrade();
            if (!context) {
                return;
            }
            TouchEvent point;
            point.SetX(static_cast<float>(rect.Left() + rect.Width() / 2))
                .SetY(static_cast<float>(rect.Top() + rect.Height() / 2))
                .SetType(TouchType::DOWN)
                .SetTime(std::chrono::high_resolution_clock::now());
            context->OnTouchEvent(point);

            switch (action) {
                case static_cast<int>(AceAction::ACTION_CLICK): {
                    TouchEvent upPoint;
                    upPoint.SetX(point.x)
                        .SetY(point.y)
                        .SetType(TouchType::UP)
                        .SetTime(std::chrono::high_resolution_clock::now());
                    context->OnTouchEvent(upPoint);
                    break;
                }
                case static_cast<int>(AceAction::ACTION_LONG_CLICK): {
                    CancelableCallback<void()> inspectorTimer;
                    auto&& callback = [weak, point]() {
                        auto refPtr = weak.Upgrade();
                        if (refPtr) {
                            TouchEvent upPoint;
                            upPoint.SetX(point.x)
                                .SetY(point.y)
                                .SetType(TouchType::UP)
                                .SetTime(std::chrono::high_resolution_clock::now());
                            refPtr->OnTouchEvent(upPoint);
                        }
                    };
                    inspectorTimer.Reset(callback);
                    auto taskExecutor =
                        SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
                    taskExecutor.PostDelayedTask(
                        inspectorTimer, INSPECTOR_DELAY_TIME, "ArkUIInspectorLongPressTouchEvent");
                    break;
                }
                default:
                    break;
            }
        },
        TaskExecutor::TaskType::UI, "ArkUIInspectorSendEventByKey");

    return true;
}

bool Inspector::SendKeyEvent(const RefPtr<PipelineContext>& context, const JsKeyEvent& event)
{
    KeyEvent keyEvent(event.code, event.action);
    keyEvent.metaKey = event.metaKey;
    keyEvent.deviceId = event.deviceId;
    keyEvent.repeatTime = 0;
    keyEvent.SetTimeStamp(event.timeStamp);
    keyEvent.sourceType = static_cast<SourceType>(event.sourceDevice);
    return context->GetTaskExecutor()->PostTask(
        [context, keyEvent]() { context->OnNonPointerEvent(keyEvent); },
        TaskExecutor::TaskType::UI, "ArkUIInspectorSendKeyEvent");
}
} // namespace OHOS::Ace::V2
