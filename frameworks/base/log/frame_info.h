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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_LOG_FRAME_INFO_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_LOG_FRAME_INFO_H

#include <string>
#include <vector>

namespace OHOS::Ace {

struct TaskInfo {
    std::string tag_;
    int32_t id_ = -1;
    uint64_t time_ = 0;

    const std::string ToString() const
    {
        std::string info;
        info.append(tag_);
        info.append("(");
        info.append(std::to_string(id_));
        info.append("), \ttime cost: ");
        info.append(std::to_string(time_));
        return info;
    }
};

struct FrameInfo {
    enum class TaskType { LAYOUT, RENDER };

    uint64_t frameRecvTime_ = 0;
    uint64_t frameTimeStamp_ = 0;
    std::vector<TaskInfo> layoutInfos_;
    std::vector<TaskInfo> renderInfos_;

    void AddTaskInfo(const std::string& tag, const int32_t id, uint64_t time, TaskType type)
    {
        switch (type) {
            case TaskType::LAYOUT:
                layoutInfos_.push_back({ tag, id, time});
                break;
            case TaskType::RENDER:
                renderInfos_.push_back({ tag, id, time});
                break;
        }
    }

    const std::string GetTimeInfo() const
    {
        std::string info;
        info.append("VsyncTimeStamp: ");
        info.append(std::to_string(frameTimeStamp_));
        info.append("\t");
        info.append("recvTime: ");
        info.append(std::to_string(frameRecvTime_));
        return info;
    }
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_LOG_FRAME_INFO_H
