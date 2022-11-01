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

#include "core/components_ng/base/inspector.h"

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/pipeline/base/element_register.h"
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

RefPtr<UINode> GetInspectorByKey(const RefPtr<FrameNode>& root, const std::string& key)
{
    std::queue<RefPtr<UINode>> elements;
    elements.push(root);
    RefPtr<UINode> inspectorElement;
    while (!elements.empty()) {
        auto current = elements.front();
        elements.pop();
        inspectorElement = AceType::DynamicCast<FrameNode>(current);
        if (inspectorElement && inspectorElement->HasInspectorId()) {
            if (key == inspectorElement->GetInspectorIdValue()) {
                return inspectorElement;
            }
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
} // namespace

std::string Inspector::GetInspectorNodeByKey(const std::string& key)
{
    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, "");
    auto rootNode = context->GetRootElement();
    CHECK_NULL_RETURN(rootNode, "");

    auto inspectorElement = GetInspectorByKey(rootNode, key);
    if (!inspectorElement) {
        LOGE("no inspector with key:%{public}s is found", key.c_str());
        return "";
    }

    auto jsonNode = JsonUtil::Create(true);
    jsonNode->Put(INSPECTOR_TYPE, inspectorElement->GetTag().c_str());
    jsonNode->Put(INSPECTOR_ID, inspectorElement->GetId());
    if (AceType::InstanceOf<FrameNode>(inspectorElement)) {
        jsonNode->Put(INSPECTOR_RECT,
            AceType::DynamicCast<FrameNode>(inspectorElement)->GetGeometryNode()->GetFrameRect().ToBounds().c_str());
    }
    auto jsonAttrs = JsonUtil::Create(true);
    inspectorElement->ToJsonValue(jsonAttrs);
    jsonNode->Put(INSPECTOR_ATTRS, jsonAttrs);
    return jsonNode->ToString();
}

std::string Inspector::GetInspectorTree()
{
    auto jsonRoot = JsonUtil::Create(true);
    jsonRoot->Put(INSPECTOR_TYPE, INSPECTOR_ROOT);

    auto context = NG::PipelineContext::GetCurrentContext();
    if (!context) {
        return jsonRoot->ToString();
    }
    auto scale = context->GetViewScale();
    auto rootHeight = context->GetRootHeight();
    auto rootWidth = context->GetRootWidth();
    jsonRoot->Put(INSPECTOR_WIDTH, std::to_string(rootWidth * scale).c_str());
    jsonRoot->Put(INSPECTOR_HEIGHT, std::to_string(rootHeight * scale).c_str());
    jsonRoot->Put(INSPECTOR_RESOLUTION, std::to_string(SystemProperties::GetResolution()).c_str());

    auto root = context->GetRootElement();
    if (root == nullptr) {
        return jsonRoot->ToString();
    }

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

            auto jsonNode = JsonUtil::Create(false);
            jsonNode->Put(INSPECTOR_TYPE, inspectorElement->GetTag().c_str());
            jsonNode->Put(INSPECTOR_ID, inspectorElement->GetId());
            jsonNode->Put(INSPECTOR_RECT, inspectorElement->GetGeometryNode()->GetFrameRect().ToBounds().c_str());
            auto jsonObject = JsonUtil::Create(false);
            inspectorElement->ToJsonValue(jsonObject);
            jsonNode->Put(INSPECTOR_ATTRS, jsonObject);
            if (!element->GetChildren().empty()) {
                if (height > 0) {
                    auto jsonNodeArray = JsonUtil::CreateArray(false);
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

    auto jsonChildren = JsonUtil::CreateArray(false);
    auto firstDepthNodeVec = elementJSONInfoMap[elementJSONInfoMap.size() - 1];
    for (const auto& nodeJSONInfo : firstDepthNodeVec) {
        auto nodeJSONValue = JsonUtil::ParseJsonString(nodeJSONInfo.second);
        jsonChildren->Put(nodeJSONValue);
    }
    jsonRoot->Put(INSPECTOR_CHILDREN, jsonChildren);
    return jsonRoot->ToString();
}

bool Inspector::SendEventByKey(const std::string& key, int action, const std::string& params)
{
    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, false);
    auto rootNode = context->GetRootElement();
    CHECK_NULL_RETURN(rootNode, false);

    auto inspectorElement = AceType::DynamicCast<FrameNode>(GetInspectorByKey(rootNode, key));
    if (!inspectorElement) {
        LOGE("no inspector with key:%{public}s is found", key.c_str());
        return false;
    }

    auto size = inspectorElement->GetGeometryNode()->GetFrameSize();
    auto offset = inspectorElement->GetOffsetRelativeToWindow();
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
            context->OnTouchEvent(point);

            switch (action) {
                case static_cast<int>(AceAction::ACTION_CLICK): {
                    context->OnTouchEvent(GetUpPoint(point));
                    break;
                }
                case static_cast<int>(AceAction::ACTION_LONG_CLICK): {
                    CancelableCallback<void()> inspectorTimer;
                    auto&& callback = [weak, point]() {
                        auto refPtr = weak.Upgrade();
                        if (refPtr) {
                            refPtr->OnTouchEvent(GetUpPoint(point));
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
} // namespace OHOS::Ace::NG
