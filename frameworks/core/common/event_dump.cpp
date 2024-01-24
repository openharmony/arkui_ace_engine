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

namespace OHOS::Ace::NG {
namespace {
constexpr size_t MAX_EVENT_TREE_RECORD_CNT = 5;
constexpr size_t MAX_FRAME_NODE_CNT = 256;
constexpr int32_t MAX_EVENT_TREE_TOUCH_DOWN_CNT = 10;
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
    oss << "responseRegion: ";
    for (const auto& rect : responseRegionList) {
        oss << rect.ToString().c_str();
    }
    dumpList.emplace_back(std::make_pair(depth, oss.str()));
}

TouchPointSnapshot::TouchPointSnapshot(const TouchEvent& event)
{
    id = event.id;
    point = OffsetF(event.x, event.y);
    screenPoint = OffsetF(event.screenX, event.screenY);
    type = event.type;
    timestamp = GetCurrentTimestamp();
}

void TouchPointSnapshot::Dump(std::list<std::pair<int32_t, std::string>>& dumpList, int32_t depth) const
{
    std::stringstream oss;
    oss << "id: " << id << ", "
        << "point: " << point.ToString() << ", "
        << "screenPoint: " << screenPoint.ToString() << ", "
        << "type: " << GestureSnapshot::TransTouchType(type) << ", "
        << "timestamp: " << ConvertTimestampToStr(timestamp);
    dumpList.emplace_back(std::make_pair(depth, oss.str()));
}

void EventTreeRecord::AddTouchPoint(const TouchEvent& event)
{
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
    }

    if (eventTreeList.empty()) {
        return;
    }

    if (type == TouchType::UP || type == TouchType::CANCEL || type == TouchType::PULL_UP ||
        type == TouchType::PULL_OUT_WINDOW) {
        eventTreeList.back().touchDownCount--;
    }
    eventTreeList.back().touchPoints.emplace_back(TouchPointSnapshot(event));
}

void EventTreeRecord::AddFrameNodeSnapshot(FrameNodeSnapshot&& node)
{
    if (eventTreeList.empty()) {
        return;
    }
    if (eventTreeList.back().hitTestTree.size() < MAX_FRAME_NODE_CNT) {
        eventTreeList.back().hitTestTree.emplace_back(node);
    }
}

void EventTreeRecord::AddGestureSnapshot(int32_t finger, RefPtr<GestureSnapshot>&& gesture)
{
    if (eventTreeList.empty()) {
        return;
    }
    auto& gestureTree = eventTreeList.back().gestureTree;
    auto& gestureMap = eventTreeList.back().gestureMap;
    gestureMap[gesture->id] = gesture;
    gestureTree[finger].emplace_back(gesture);
}

void EventTreeRecord::AddGestureProcedure(uint64_t id,
    const std::string& procedure, const std::string& state, const std::string& disposal, int64_t timestamp)
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
    if (iter->second->type == "TouchEventActuator" && procedure == "HandleTouchMove") {
        return;
    }
    iter->second->AddProcedure(procedure, state, disposal, timestamp);
}

void EventTreeRecord::AddGestureProcedure(uint64_t id,
    const TouchEvent& point, const std::string& state, const std::string& disposal, int64_t timestamp)
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
    iter->second->AddProcedure(procedure, state, disposal, timestamp);
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
} // end of namespace
