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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PARALLEL_STAGE_STAGE_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PARALLEL_STAGE_STAGE_PATTERN_H

#include "base/utils/noncopyable.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/pattern/stage/force_split/parallel_stage_layout_algorithm.h"
#include "core/components_ng/pattern/stage/force_split/parallel_page_pattern.h"

namespace OHOS::Ace::NG {
enum class PageMode {
    STACK = 0,
    SPLIT,
};

// StagePattern is the base class for root render node to perform page switch.
class ParallelStagePattern : public StagePattern {
    DECLARE_ACE_TYPE(ParallelStagePattern, StagePattern);
public:
    ParallelStagePattern() = default;
    ~ParallelStagePattern() = default;
    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return AceType::MakeRefPtr<ParallelStageLayoutAlgorithm>();
    }

    void SetPrimaryPage(const RefPtr<FrameNode>& pageNode) override;

    WeakPtr<FrameNode> GetPrimaryPage()
    {
        return primaryPageNode_;
    }

    bool GetIsSplit() const
    {
        return mode_ == PageMode::SPLIT;
    }

    void SetModeChangeCallback(std::function<void()>&& callback)
    {
        modeChangeCallback_ = std::move(callback);
    }

    void SetWindowStateChangeCallback(std::function<void(bool)>&& callback)
    {
        windowStateChangeCallback_ = std::move(callback);
    }

    void OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type) override;

    void OnAttachToMainTree() override;
    void OnDetachFromMainTree() override;

    RefPtr<FrameNode> GetDividerNode() const
    {
        return dividerNode_;
    }

    bool HasDividerNode() const
    {
        return hasDividerNode_;
    }

    void OnWindowShow() override;
    void OnWindowHide() override;

    void OnForceSplitConfigUpdate() override;

private:
    void FireModeChangeCallback();
    void CreateDividerNodeIfNeeded();
    bool CalculateMode(double width);
    void OnDirectionConfigurationUpdate() override;

    WeakPtr<FrameNode> primaryPageNode_;
    RefPtr<FrameNode> dividerNode_;
    PageMode mode_ = PageMode::STACK;
    bool hasDividerNode_ = false;
    std::function<void()> modeChangeCallback_;
    std::function<void(bool)> windowStateChangeCallback_;

    ACE_DISALLOW_COPY_AND_MOVE(ParallelStagePattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PARALLEL_PATTERNS_STAGE_STAGE_PATTERN_H
