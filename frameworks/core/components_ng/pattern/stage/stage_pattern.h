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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STAGE_STAGE_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STAGE_STAGE_PATTERN_H

#include "stage_layout_algorithm.h"

#include "base/utils/noncopyable.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {
// StagePattern is the base class for root render node to perform page switch.
class ACE_EXPORT StagePattern : public Pattern {
    DECLARE_ACE_TYPE(StagePattern, Pattern);

public:
    StagePattern() = default;
    ~StagePattern() override = default;

    bool IsMeasureBoundary() const override
    {
        return true;
    }

    bool IsAtomicNode() const override
    {
        return false;
    }

    void OnAttachToFrameNode() override;

    void OnRebuildFrame() override
    {
        if (onRebuildFrameCallback_) {
            onRebuildFrameCallback_();
        }
    }

    void SetOnRebuildFrameCallback(std::function<void()>&& callback)
    {
        onRebuildFrameCallback_ = std::move(callback);
    }

    virtual void SetPrimaryPage(const RefPtr<FrameNode>& primaryPage) {}

    void SetCurrentPageIndex(int32_t index)
    {
        currentPageIndex_ = index;
    }

protected:
    std::function<void()> onRebuildFrameCallback_;
    int32_t currentPageIndex_ = 0;

    ACE_DISALLOW_COPY_AND_MOVE(StagePattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STAGE_STAGE_PATTERN_H
