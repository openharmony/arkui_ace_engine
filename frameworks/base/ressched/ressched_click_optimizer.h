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
#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_RESSCHED_RESSCHED_CLICK_OPTIMIZER_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_RESSCHED_RESSCHED_CLICK_OPTIMIZER_H

#include <atomic>

#include "base/utils/macros.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace {
class ACE_EXPORT ResSchedClickOptimizer final : public std::enable_shared_from_this<ResSchedClickOptimizer> {
public:
    ResSchedClickOptimizer() = default;
    ~ResSchedClickOptimizer() = default;

    void Init();

    void ReportClick(const WeakPtr<NG::FrameNode> weakNode, const GestureEvent& gestureEvent);

    bool GetClickExtEnabled()
    {
        return clickExtEnabled_;
    };

    void SetClickExtEnabled(bool value)
    {
        clickExtEnabled_ = value;
    };

    int32_t GetDepth()
    {
        return depth_;
    }

    void SetDepth(int32_t value)
    {
        depth_ = std::clamp(value, 0, MAX_DEPTH);
    }

private:
    static void GetComponentTextAndImageSourceRecursive(
        const WeakPtr<NG::FrameNode> weakNode, std::string& text, std::string& imgSrc, const int32_t remain);

    bool isInit_ = false;
    std::atomic_bool clickExtEnabled_ = false;
    std::atomic<int32_t> depth_ = DEFAULT_DEPTH;

    static constexpr int32_t MAX_DEPTH = 20;
    static constexpr int32_t DEFAULT_DEPTH = 5;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_RESSCHED_RESSCHED_CLICK_OPTIMIZER_H