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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STAGE_STAGE_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STAGE_STAGE_MANAGER_H

#include <cstdint>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/base/ui_node.h"

namespace OHOS::Ace::NG {
class FrameNode;
class StagePattern;
class OverlayManager;

// StageManager is the base class for root render node to perform page switch.
class ACE_EXPORT StageManager : public virtual AceType {
    DECLARE_ACE_TYPE(StageManager, AceType);

public:
    explicit StageManager(const RefPtr<FrameNode>& stage);
    ~StageManager() override = default;

    bool PushPage(const RefPtr<FrameNode>& node, bool needHideLast = true);
    bool PopPage(bool needShowNext = true);
    bool PopPageToIndex(int32_t index, bool needShowNext = true);
    bool CleanPageStack();

    bool MovePageToFront(const RefPtr<FrameNode>& node, bool needHideLast = true);

    static void FirePageHide(const RefPtr<UINode>& node);
    static void FirePageShow(const RefPtr<UINode>& node);

    RefPtr<FrameNode> GetLastPage();

private:
    RefPtr<FrameNode> stageNode_;
    RefPtr<StagePattern> stagePattern_;

    ACE_DISALLOW_COPY_AND_MOVE(StageManager);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STAGE_STAGE_MANAGER_H
