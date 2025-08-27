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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_EVENT_DUMP_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_EVENT_DUMP_H

#include <cstdint>
#include <list>
#include <map>
#include <string>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "core/event/touch_event.h"

namespace OHOS::Ace::NG {
struct FrameNodeSnapshot {
    void Dump(std::list<std::pair<int32_t, std::string>>& dumpList, int32_t depth) const;
    void Dump(std::unique_ptr<JsonValue>& json) const;

    int32_t nodeId = -1;
    int32_t parentNodeId = -1;
    std::string tag;
    std::string comId;
    bool monopolizeEvents = false;
    bool isHit = false;
    int32_t hitTestMode = 0;
    std::vector<RectF> responseRegionList;
    bool active = false;
};

struct TouchPointSnapshot {
    TouchPointSnapshot() = default;
    TouchPointSnapshot(const TouchEvent& event);

    void Dump(std::list<std::pair<int32_t, std::string>>& dumpList, int32_t depth) const;
    void Dump(std::unique_ptr<JsonValue>& json) const;
    int32_t id = -1;
    OffsetF point;
    OffsetF screenPoint;
    TouchType type = TouchType::UNKNOWN;
    int64_t timestamp = 0;
    bool isInjected = false;
    std::unordered_map<int32_t, int32_t> downFingerIds;
};

struct AxisSnapshot {
    AxisSnapshot() = default;
    AxisSnapshot(const AxisEvent& event);

    void Dump(std::list<std::pair<int32_t, std::string>>& dumpList, int32_t depth) const;
    void Dump(std::unique_ptr<JsonValue>& json) const;
    int32_t id = -1;
    OffsetF point;
    OffsetF screenPoint;
    AxisAction action = AxisAction::NONE;
    int64_t timestamp = 0;
    bool isInjected = false;
};

struct EventTree {
    std::list<AxisSnapshot> axis;
    std::list<TouchPointSnapshot> touchPoints;
    std::list<FrameNodeSnapshot> hitTestTree;

    std::map<int32_t, std::list<RefPtr<GestureSnapshot>>> gestureTree;
    std::map<uint64_t, RefPtr<GestureSnapshot>> gestureMap;

    int32_t touchDownCount = 0;
    int32_t axisUpdateCount = 0;
    std::set<int32_t> downFingerIds_;
    std::set<int32_t> updateAxisIds_;
};

struct EventTreeRecord {
    void AddAxis(const AxisEvent& event);

    void AddTouchPoint(const TouchEvent& event);

    void AddFrameNodeSnapshot(FrameNodeSnapshot&& node);

    void AddGestureSnapshot(int32_t finger, RefPtr<GestureSnapshot>&& gesture);

    void AddGestureProcedure(uint64_t id, const std::string& procedure, const std::string& extraInfo,
        const std::string& state, const std::string& disposal, int64_t timestamp = 0);

    void AddGestureProcedure(uint64_t id, const TouchEvent& point, const std::string& extraInfo,
        const std::string& state, const std::string& disposal, int64_t timestamp = 0);

    void AddGestureProcedure(uint64_t id, const AxisEvent& event, const std::string& extraInfo,
        const std::string& state, const std::string& disposal, int64_t timestamp = 0);

    void Dump(std::list<std::pair<int32_t, std::string>>& dumpList, int32_t depth, int32_t startNumber = 0) const;

    void Dump(std::unique_ptr<JsonValue>& json, int32_t depth, int32_t startNumber = 0) const;
    void BuildTouchPoints(std::list<TouchPointSnapshot> touchPoints, std::unique_ptr<JsonValue>& json) const;
    void BuildAxis(std::list<AxisSnapshot> axis, std::unique_ptr<JsonValue>& json) const;

    void BuildGestureTree(
        std::map<int32_t, std::list<RefPtr<GestureSnapshot>>> gestureTreeMap, std::unique_ptr<JsonValue>& json) const;
    void BuildHitTestTree(std::list<FrameNodeSnapshot> hitTestTree, std::unique_ptr<JsonValue>& json) const;
    void MountToParent(
        std::vector<std::pair<std::string, std::pair<std::string, std::unique_ptr<JsonValue>>>> stateInfoList,
        std::unique_ptr<JsonValue>& json) const;
    std::list<EventTree> eventTreeList;
};
}
#endif
