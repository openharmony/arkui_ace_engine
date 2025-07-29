/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAYOUT_MANAGER_DFX_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAYOUT_MANAGER_DFX_H
#include <event_handler.h>
#include <queue>

#include "core/components_ng/pattern/window_scene/scene/window_scene_layout_manager.h"
#include "session_manager/include/scene_session_manager.h"

namespace OHOS::Rosen {
struct SessionUIParam;
}

namespace OHOS::Ace::NG {
constexpr uint32_t RECORD_LIST_MAX_CAPACITY = 10;

struct RecordResult {
    uint32_t size = 0;
    std::queue<TraverseResult> que;
};

class LayoutManagerDfx {
public:
    static LayoutManagerDfx* GetInstance();
    void RecordUIParams(TraverseResult uiParams);
    void ExecuteRecordUIParams(TraverseResult& res);

private:
    LayoutManagerDfx() = default;
    ~LayoutManagerDfx() = default;
    void DumpFlushInfo(const TraverseResult& res);
    void PerformUIParams();

    std::mutex recordMutex_;
    RecordResult recordRes_;
    int32_t curVsyncCnt_ = 0;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAYOUT_MANAGER_DFX_H