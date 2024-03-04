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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FOLDER_EVENT_INFO_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FOLDER_EVENT_INFO_H

#include "core/common/display_info.h"
#include "core/event/ace_events.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT FolderEventInfo : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(FolderEventInfo, BaseEventInfo);

public:
    FolderEventInfo(FoldStatus foldStatus) : BaseEventInfo("FolderStackInfo"), folderState_(foldStatus) {}
    FolderEventInfo(FoldStatus foldStatus, bool intoHover, Rotation rotation, WindowMode windowMode)
        : BaseEventInfo("FolderStackInfo"), folderState_(foldStatus), isHoverMode_(intoHover), appRotation_(rotation),
          windowMode_(windowMode)
    {}

    ~FolderEventInfo() = default;

    FoldStatus GetFolderState() const
    {
        return folderState_;
    }
    bool IsHoverMode() const
    {
        return isHoverMode_;
    }

    Rotation GetRotation() const
    {
        return appRotation_;
    }

    WindowMode GetWindowMode() const
    {
        return windowMode_;
    }

private:
    FoldStatus folderState_ = FoldStatus::UNKNOWN;
    bool isHoverMode_ = false;
    Rotation appRotation_ = Rotation::ROTATION_0;
    WindowMode windowMode_ = WindowMode::WINDOW_MODE_UNDEFINED;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FOLDER_EVENT_INFO_H
