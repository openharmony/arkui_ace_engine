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

#include "core/common/event_dump.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr size_t MAX_EVENT_TREE_RECORD_CNT = 5;
constexpr size_t MAX_FRAME_NODE_CNT = 256;
constexpr int32_t MAX_EVENT_TREE_TOUCH_DOWN_CNT = 10;
constexpr int32_t MAX_EVENT_TREE_TOUCH_POINT_CNT = 20;
constexpr int32_t MAX_EVENT_TREE_AXIS_UPDATE_CNT = 20;
constexpr int32_t MAX_EVENT_TREE_AXIS_CNT = 20;
constexpr int32_t MAX_EVENT_TREE_GESTURE_CNT = 100;
} // end of namespace

void FrameNodeSnapshot::Dump(std::list<std::pair<int32_t, std::string>>& dumpList, int32_t depth) const
{
    std::stringstream oss;
    oss << "nodeId: " << nodeId << ", "
        << "parentId: " << parentNodeId << ", "
        << "tag: " << tag << ", ";
    if (!comId.empty()) {
        oss << "comId: " << comId << ", ";
    }
    oss << "monopolizeEvents: " << monopolizeEvents << ", "
        << "isHit: " << isHit << ", "
        << "hitTestMode: " << hitTestMode << ", ";
#ifndef IS_RELEASE_VERSION
    oss << "responseRegion: ";
    for (const auto& rect : responseRegionList) {
        oss << rect.ToString().c_str();
    }
#else
    oss << "responseRegionSize: ";
    for (const auto& rect : responseRegionList) {
        oss << rect.GetSize().ToString().c_str();
    }
#endif
    dumpList.emplace_back(std::make_pair(depth, oss.str()));
}

TouchPointSnapshot::TouchPointSnapshot(const TouchEvent& event)
{
    id = event.id;
    point = OffsetF(event.x, event.y);
    screenPoint = OffsetF(event.screenX, event.screenY);
    type = event.type;
    timestamp = GetCurrentTimestamp();
    isInjected = event.isInjected;
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto eventManager = pipeline->GetEventManager();
    CHECK_NULL_VOID(eventManager);
    downFingerIds = eventManager->GetDownFingerIds();
}

AxisSnapshot::AxisSnapshot(const AxisEvent& event)
{
    id = event.id;
    point = OffsetF(event.x, event.y);
    screenPoint = OffsetF(event.screenX, event.screenY);
    action = event.action;
    timestamp = GetCurrentTimestamp();
    isInjected = event.isInjected;
}

void TouchPointSnapshot::Dump(std::list<std::pair<int32_t, std::string>>& dumpList, int32_t depth) const
{
    std::string downFingerIdStr = "";
    for (const auto& iter : downFingerIds) {
        downFingerIdStr += std::to_string(iter.first) + " ";
    }
    std::stringstream oss;
#ifdef IS_RELEASE_VERSION
    oss << "id: " << id << ", "
        << "type: " << GestureSnapshot::TransTouchType(type) << ", "
        << "timestamp: " << ConvertTimestampToStr(timestamp) << ", "
        << "isInjected: " << isInjected << ", "
        << "downFingerIds: " << downFingerIdStr;
#else
    oss << "id: " << id << ", "
        << "point: " << point.ToString() << ", "
        << "screenPoint: " << screenPoint.ToString() << ", "
        << "type: " << GestureSnapshot::TransTouchType(type) << ", "
        << "timestamp: " << ConvertTimestampToStr(timestamp) << ", "
        << "isInjected: " << isInjected << ", "
        << "downFingerIds: " << downFingerIdStr;
#endif
    dumpList.emplace_back(std::make_pair(depth, oss.str()));
}

void AxisSnapshot::Dump(std::list<std::pair<int32_t, std::string>>& dumpList, int32_t depth) const
{
    std::stringstream oss;
    std::string strAction = std::string("Node");
    switch (action) {
        case AxisAction::BEGIN:
            strAction = std::string("BEGIN");
            break;
        case AxisAction::UPDATE:
            strAction = std::string("UPDATE");
            break;
        case AxisAction::END:
            strAction = std::string("END");
            break;
        default:
            LOGW("AxisAction: Unknown AxisAction action %{public}d", action);
            break;
    }
#ifdef IS_RELEASE_VERSION
    oss << "id: " << id << ", "
        << "action: " << strAction << ", "
        << "timestamp: " << ConvertTimestampToStr(timestamp) << ", "
        << "isInjected: " << isInjected;
#else
    oss << "id: " << id << ", "
        << "point: " << point.ToString() << ", "
        << "screenPoint: " << screenPoint.ToString() << ", "
        << "action: " << strAction << ", "
        << "timestamp: " << ConvertTimestampToStr(timestamp) << ", "
        << "isInjected: " << isInjected;
#endif
    dumpList.emplace_back(std::make_pair(depth, oss.str()));
}

void EventTreeRecord::AddAxis(const AxisEvent& event)
{
    if (!eventTreeList.empty() && eventTreeList.back().axis.size() > MAX_EVENT_TREE_AXIS_CNT) {
        eventTreeList.pop_back();
        TAG_LOGW(AceLogTag::ACE_INPUTTRACKING,
            "EventTreeList last record axis size is over limit! Last record is cleaned.");
    }
    if (!eventTreeList.empty() && event.action == Ace::AxisAction::BEGIN &&
        eventTreeList.back().updateAxisIds_.count(event.id) > 0) {
        eventTreeList.pop_back();
        TAG_LOGW(AceLogTag::ACE_INPUTTRACKING,
            "EventTreeList last record receive BEGIN event twice. Last record is cleaned.");
    }
    AxisAction action = event.action;
    if (action == Ace::AxisAction::BEGIN) {
        if (eventTreeList.empty() || eventTreeList.back().axisUpdateCount <= 0 ||
            eventTreeList.back().axisUpdateCount >= MAX_EVENT_TREE_AXIS_UPDATE_CNT) {
            eventTreeList.emplace_back(EventTree());
            if (eventTreeList.size() > MAX_EVENT_TREE_RECORD_CNT) {
                eventTreeList.erase(eventTreeList.begin());
            }
        }
        eventTreeList.back().axisUpdateCount++;
        eventTreeList.back().updateAxisIds_.insert(event.id);
    }
    if (eventTreeList.empty()) {
        return;
    }
    if (action == AxisAction::END || action == AxisAction::CANCEL) {
        eventTreeList.back().axisUpdateCount--;
        eventTreeList.back().updateAxisIds_.erase(event.id);
    }
    eventTreeList.back().axis.emplace_back(AxisSnapshot(event));
}

void EventTreeRecord::AddTouchPoint(const TouchEvent& event)
{
    if (!eventTreeList.empty() && eventTreeList.back().touchPoints.size() > MAX_EVENT_TREE_TOUCH_POINT_CNT) {
        eventTreeList.pop_back();
        TAG_LOGW(AceLogTag::ACE_INPUTTRACKING,
            "EventTreeList last record touchPoint size is over limit! Last record is cleaned.");
    }
    if (!eventTreeList.empty() && event.type == Ace::TouchType::DOWN &&
        eventTreeList.back().downFingerIds_.count(event.id) > 0) {
        eventTreeList.pop_back();
        TAG_LOGW(AceLogTag::ACE_INPUTTRACKING,
            "EventTreeList last record receive DOWN event twice. Last record is cleaned.");
    }
    TouchType type = event.type;
    if (type == Ace::TouchType::DOWN) {
        // multi fingers touch down will be in one tree
        if (eventTreeList.empty() || eventTreeList.back().touchDownCount <= 0 ||
            eventTreeList.back().touchDownCount >= MAX_EVENT_TREE_TOUCH_DOWN_CNT) {
            eventTreeList.emplace_back(EventTree());
            if (eventTreeList.size() > MAX_EVENT_TREE_RECORD_CNT) {
                eventTreeList.erase(eventTreeList.begin());
            }
        }
        eventTreeList.back().touchDownCount++;
        eventTreeList.back().downFingerIds_.insert(event.id);
    }

    if (eventTreeList.empty()) {
        return;
    }

    if (type == TouchType::UP || type == TouchType::CANCEL || type == TouchType::PULL_UP ||
        type == TouchType::PULL_OUT_WINDOW) {
        eventTreeList.back().touchDownCount--;
        eventTreeList.back().downFingerIds_.erase(event.id);
    }
    eventTreeList.back().touchPoints.emplace_back(TouchPointSnapshot(event));
}

void EventTreeRecord::AddFrameNodeSnapshot(FrameNodeSnapshot&& node)
{
    if (eventTreeList.empty()) {
        return;
    }
    if (eventTreeList.back().hitTestTree.size() < MAX_FRAME_NODE_CNT) {
        bool isInList = false;
        for (auto& iter : eventTreeList.back().hitTestTree) {
            if (iter.nodeId == node.nodeId) {
                isInList = true;
                break;
            }
        }
        if (isInList) {
            return;
        }
        eventTreeList.back().hitTestTree.emplace_back(node);
    }
}

void EventTreeRecord::AddGestureSnapshot(int32_t finger, RefPtr<GestureSnapshot>&& gesture)
{
    if (eventTreeList.empty()) {
        return;
    }
    if (eventTreeList.size() > MAX_EVENT_TREE_RECORD_CNT) {
        eventTreeList.clear();
        TAG_LOGW(AceLogTag::ACE_INPUTTRACKING, "EventTreeList size is over MAX, clean event tree.");
        return;
    }
    auto& gestureTree = eventTreeList.back().gestureTree;
    auto& gestureMap = eventTreeList.back().gestureMap;
    if (gestureMap.size() > MAX_EVENT_TREE_GESTURE_CNT) {
        eventTreeList.clear();
        TAG_LOGW(AceLogTag::ACE_INPUTTRACKING, "GestureMap size is over MAX, clean event tree.");
        return;
    }
    gestureMap[gesture->id] = gesture;
    gestureTree[finger].emplace_back(gesture);
}

void EventTreeRecord::AddGestureProcedure(uint64_t id, const std::string& procedure, const std::string& extraInfo,
    const std::string& state, const std::string& disposal, int64_t timestamp)
{
    if (eventTreeList.empty()) {
        return;
    }
    auto& gestureMap = eventTreeList.back().gestureMap;
    auto iter = gestureMap.find(id);
    if (iter == gestureMap.end()) {
        return;
    }
    // TouchEventActuator don't record move
    if (iter->second->type == "TouchEventActuator") {
        return;
    }
    iter->second->AddProcedure(procedure, extraInfo, state, disposal, timestamp);
}

void EventTreeRecord::AddGestureProcedure(uint64_t id, const TouchEvent& point, const std::string& extraInfo,
    const std::string& state, const std::string& disposal, int64_t timestamp)
{
    if (eventTreeList.empty()) {
        return;
    }
    auto& gestureMap = eventTreeList.back().gestureMap;
    auto iter = gestureMap.find(id);
    if (iter == gestureMap.end()) {
        return;
    }

    if ((point.type == TouchType::MOVE || point.type == TouchType::PULL_MOVE) &&
        !iter->second->CheckNeedAddMove(state, disposal)) {
        return;
    }
    std::string procedure = std::string("Handle").append(GestureSnapshot::TransTouchType(point.type));
    iter->second->AddProcedure(procedure, extraInfo, state, disposal, timestamp);
}

void EventTreeRecord::Dump(std::list<std::pair<int32_t, std::string>>& dumpList,
    int32_t depth, int32_t startNumber) const
{
    int32_t index = 0;
    int32_t listDepth = depth + 1;
    int32_t detailDepth = listDepth + 1;
    for (auto& tree : eventTreeList) {
        if (index < startNumber) {
            index++;
            continue;
        }
        std::string header = std::to_string(index).append(": event tree =>");

        // dump needful touch points:
        dumpList.emplace_back(std::make_pair(depth, header));
        dumpList.emplace_back(std::make_pair(listDepth, "touch points:"));
        for (auto& item : tree.touchPoints) {
            item.Dump(dumpList, detailDepth);
        }

        // dump needful axis:
        dumpList.emplace_back(std::make_pair(listDepth, "axis:"));
        for (auto& item : tree.axis) {
            item.Dump(dumpList, detailDepth);
        }

        // dump hit test frame nodes:
        dumpList.emplace_back(std::make_pair(listDepth, "hittest:"));
        for (auto& item : tree.hitTestTree) {
            item.Dump(dumpList, detailDepth);
        }

        // dump gesture event and procedure:
        dumpList.emplace_back(std::make_pair(listDepth, "event procedures:"));
        for (auto iter = tree.gestureTree.begin(); iter != tree.gestureTree.end(); ++iter) {
            dumpList.emplace_back(std::make_pair(detailDepth,
                std::string("finger:").append(std::to_string(iter->first))));
            for (const auto& item : iter->second) {
                item->Dump(dumpList, detailDepth + 1);
            }
        }
        ++index;
    }
}

void FrameNodeSnapshot::Dump(std::unique_ptr<JsonValue>& json) const
{
    json->Put("nodeId", nodeId);
    json->Put("parentId", parentNodeId);
    json->Put("tag", tag.c_str());
    if (!comId.empty()) {
        json->Put("comId", comId.c_str());
    }
    json->Put("monopolizeEvents", monopolizeEvents);
    json->Put("isHit", isHit);
    json->Put("hitTestMode", hitTestMode);
    std::string region = "";
    for (const auto& rect : responseRegionList) {
        region.append(rect.ToString());
    }
    json->Put("responseRegion", region.c_str());
}

void TouchPointSnapshot::Dump(std::unique_ptr<JsonValue>& json) const
{
    std::string downFingerIdStr = "";
    for (const auto& iter : downFingerIds) {
        downFingerIdStr += std::to_string(iter.first) + " ";
    }
    json->Put("point", point.ToString().c_str());
    json->Put("screenPoint", screenPoint.ToString().c_str());
    json->Put("type", GestureSnapshot::TransTouchType(type).c_str());
    json->Put("timestamp", ConvertTimestampToStr(timestamp).c_str());
    json->Put("isInjected", isInjected);
    json->Put("downFingerIds", downFingerIdStr.c_str());
}

void AxisSnapshot::Dump(std::unique_ptr<JsonValue>& json) const
{
    json->Put("point", point.ToString().c_str());
    json->Put("screenPoint", screenPoint.ToString().c_str());
    switch (action) {
        case AxisAction::BEGIN:
            json->Put("action", "BEGIN");
            break;
        case AxisAction::UPDATE:
            json->Put("action", "UPDATE");
            break;
        case AxisAction::END:
            json->Put("action", "END");
            break;
        default:
            LOGW("AxisAction: Unknown AxisAction action %{public}d", action);
            break;
    }
    json->Put("timestamp", ConvertTimestampToStr(timestamp).c_str());
    json->Put("isInjected", isInjected);
}

void EventTreeRecord::BuildTouchPoints(
    std::list<TouchPointSnapshot> touchPoints, std::unique_ptr<JsonValue>& json) const
{
    std::unique_ptr<JsonValue> touch = JsonUtil::CreateArray(true);
    for (auto& item : touchPoints) {
        std::unique_ptr<JsonValue> child = JsonUtil::Create(true);
        item.Dump(child);
        touch->Put(child);
    }
    json->Put("touch points", touch);
}

void EventTreeRecord::BuildAxis(
    std::list<AxisSnapshot> axis, std::unique_ptr<JsonValue>& json) const
{
    std::unique_ptr<JsonValue> axisEvent = JsonUtil::CreateArray(true);
    for (auto& item : axis) {
        std::unique_ptr<JsonValue> child = JsonUtil::Create(true);
        item.Dump(child);
        axisEvent->Put(child);
    }
    json->Put("axis", axisEvent);
}

void EventTreeRecord::BuildHitTestTree(std::list<FrameNodeSnapshot> hitTestTree, std::unique_ptr<JsonValue>& json) const
{
    std::unique_ptr<JsonValue> hittest = JsonUtil::CreateArray(true);
    for (auto& item : hitTestTree) {
        std::unique_ptr<JsonValue> child = JsonUtil::Create(true);
        item.Dump(child);
        hittest->Put(child);
    }
    json->Put("hittest", hittest);
}

void EventTreeRecord::MountToParent(
    std::vector<std::pair<std::string, std::pair<std::string, std::unique_ptr<JsonValue>>>> stateInfoList,
    std::unique_ptr<JsonValue>& json) const
{
    for (auto entry = stateInfoList.rbegin(); entry != stateInfoList.rend(); ++entry) {
        std::string parentId = entry->second.first;
        if (parentId == "0x0") {
            continue;
        }
        auto it = std::find_if(
            stateInfoList.begin(), stateInfoList.end(), [&](const auto& pair) { return pair.first == parentId; });
        if (it != stateInfoList.end()) {
            std::string key = "detail_" + entry->first;
            it->second.second->Put(key.c_str(), entry->second.second);
        }
    }

    for (const auto& entry : stateInfoList) {
        if (entry.second.first == "0x0") {
            json->Put(("detail_" + entry.first).c_str(), std::move(entry.second.second));
        }
    }
}

void EventTreeRecord::BuildGestureTree(
    std::map<int32_t, std::list<RefPtr<GestureSnapshot>>> gestureTreeMap, std::unique_ptr<JsonValue>& json) const
{
    std::unique_ptr<JsonValue> procedures = JsonUtil::Create(true);
    std::unique_ptr<JsonValue> gestureTree = JsonUtil::Create(true);
    std::vector<std::pair<std::string, std::pair<std::string, std::unique_ptr<JsonValue>>>> stateInfoList;
    for (auto iter = gestureTreeMap.begin(); iter != gestureTreeMap.end(); ++iter) {
        stateInfoList.clear();
        for (const auto& item : iter->second) {
            auto result = item->GetIds();
            std::string id = std::get<0>(result);
            std::string parentId = std::get<1>(result);
            stateInfoList.push_back(std::make_pair(id, std::make_pair(parentId, JsonUtil::Create(true))));
            auto it = std::find_if(
                stateInfoList.begin(), stateInfoList.end(), [&](const auto& pair) { return pair.first == id; });
            if (it != stateInfoList.end()) {
                item->Dump(it->second.second);
            }
        }
        MountToParent(std::move(stateInfoList), gestureTree);
        procedures->Put(("finger_" + std::to_string(iter->first)).c_str(), gestureTree);
    }
    json->Put("event procedures", procedures);
}

void EventTreeRecord::Dump(std::unique_ptr<JsonValue>& json, int32_t depth, int32_t startNumber) const
{
    int32_t index = 0;
    for (auto& tree : eventTreeList) {
        if (index < startNumber) {
            index++;
            continue;
        }
        std::unique_ptr<JsonValue> children = JsonUtil::Create(true);
        BuildTouchPoints(tree.touchPoints, children);
        BuildAxis(tree.axis, children);
        BuildHitTestTree(tree.hitTestTree, children);
        BuildGestureTree(tree.gestureTree, children);
        std::string header = "event tree_" + std::to_string(index);
        json->Put(header.c_str(), children);
        ++index;
    }
}
} // namespace OHOS::Ace::NG
