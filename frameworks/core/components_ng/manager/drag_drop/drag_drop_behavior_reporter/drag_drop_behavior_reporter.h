/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_BEHAVIOR_REPORTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_BEHAVIOR_REPORTER_H

#include <set>
#include <string>

#include "core/common/container_consts.h"


namespace OHOS::Ace::NG {
enum class DragStartResult : int32_t {
    UNKNOW = -1,
    DRAG_START_SUCCESS = 0,
    APP_REFUSE_DRAG = 1,
    DRAGFWK_START_FAIL = 2,
    SET_DATA_FAIL = 3,
    REPEAT_DRAG_FAIL = 4,
    SNAPSHOT_FAIL = 5,
    TEXT_NOT_SELECT = 6
};

enum class DragStopResult : int32_t {
    UNKNOW = -1,
    DRAG_SOTP_SUCCESS = 0,
    APP_REFUSE_DATA = 1,
    APP_RECEIVE_FAIL = 2,
    APP_DATA_UNSUPPORT = 3,
    USER_STOP_DRAG = 4,
    GET_UDKEY_FAIL = 5,
    GET_UDMF_FAIL = 6,
    DRAGFWK_STOP_FAIL = 7
};

enum class CrossingEnd : int32_t {
    NOT_CROSSING = 0,
    IS_CROSSING = 1
};

enum class DragReporterPharse {
    DRAG_START,
    DRAG_STOP
};

class DragDropBehaviorReporter {
public:
    static DragDropBehaviorReporter& GetInstance();

    void UpdateAllowDropType(const std::set<std::string>& allowDropType);
    void UpdateIsCrossing(CrossingEnd isCrossing);
    void UpdateDragStartResult(DragStartResult result);
    void UpdateDragStopResult(DragStopResult result);
    void UpdateRecordSize(int32_t recordSize);
    void UpdateSummaryType(const std::string& summaryType);
    void UpdateContainerId(int32_t containerId);
    void Submit(DragReporterPharse pharse, int32_t contanerID);

private:
    DragDropBehaviorReporter() = default;
    ~DragDropBehaviorReporter() = default;
    void Reset();

    int32_t containerId_ = INSTANCE_ID_UNDEFINED;
    int32_t recordSize_ = 0;
    CrossingEnd isCrossing_ = CrossingEnd::NOT_CROSSING;
    DragStartResult startResult_ = DragStartResult::UNKNOW;
    DragStopResult stopResult_ = DragStopResult::UNKNOW;
    std::string summaryType_;
    std::set<std::string> allowDropType_;
};

class DragDropBehaviorReporterTrigger final {
public:
    DragDropBehaviorReporterTrigger(DragReporterPharse pharse, int32_t containerId)
        : pharse_(pharse), containerId_(containerId) {}
    ~DragDropBehaviorReporterTrigger()
    {
        DragDropBehaviorReporter::GetInstance().Submit(pharse_, containerId_);
    }

private:
    DragReporterPharse pharse_;
    int32_t containerId_ = 0;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_BEHAVIOR_REPORTER_H
