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

#include "background_task_helper_ohos.h"

#include "background_mode.h"
#include "background_task_mgr_helper.h"

#include "core/common/ace_application_info.h"

namespace OHOS::Ace {

BackgroundTaskHelper& BackgroundTaskHelper::GetInstance()
{
    static BackgroundTaskHelperOhos instance;
    return instance;
}

bool BackgroundTaskHelperOhos::HasBackgroundTask()
{
    int32_t creatorUid = AceApplicationInfo::GetInstance().GetUid();
    uint32_t backgroundMode = BackgroundTaskMgr::BackgroundMode::AUDIO_PLAYBACK;

    std::vector<std::shared_ptr<BackgroundTaskMgr::ContinuousTaskInfo>> continuousTaskList;
    ErrCode code = BackgroundTaskMgr::BackgroundTaskMgrHelper::RequestGetContinuousTasksByUidForInner(
        creatorUid, continuousTaskList);
    if (code != OHOS::ERR_OK) {
        TAG_LOGW(AceLogTag::ACE_VIDEO, "uid=%{public}d no continuous task list, code=%{public}d", creatorUid, code);
        return false;
    }

    for (const auto &task : continuousTaskList) {
        TAG_LOGW(AceLogTag::ACE_VIDEO, "uid=%{public}d taskCreatorUid=%{public}d", creatorUid, task->GetUid());

        std::vector<uint32_t> bgMode = task->GetBackgroundModes();
        auto it = std::find_if(bgMode.begin(), bgMode.end(), [ backgroundMode ](auto mode) {
            return (mode == backgroundMode);
        });
        if (it != bgMode.end()) {
            TAG_LOGW(AceLogTag::ACE_VIDEO, "uid=%{public}d is audio playback", creatorUid);
            return true;
        }
    }
    return false;
}

} // namespace OHOS::Ace