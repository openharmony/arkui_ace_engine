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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_CONTENT_CHANGE_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_CONTENT_CHANGE_MANAGER_H

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/geometry/ng/rect_t.h"
#include "interfaces/inner_api/ui_session/param_config.h"

#include <set>
#include <optional>

namespace OHOS::Ace::NG {
class FrameNode;
class ContentChangeManager final : public AceType {
    DECLARE_ACE_TYPE(ContentChangeManager, AceType);
public:
    ContentChangeManager() = default;
    virtual ~ContentChangeManager() = default;
    void StartContentChangeReport(const ContentChangeConfig& config);
    void StopContentChangeReport();
    void AddOnContentChangeNode(WeakPtr<FrameNode> node);
    void RemoveOnContentChangeNode(WeakPtr<FrameNode> node);
    bool IsContentChangeDetectEnable() const
    {
        return currentContentChangeConfig_.has_value();
    }

    void OnPageTransitionEnd(const RefPtr<FrameNode>& keyNode);
    void OnScrollChangeEnd(const RefPtr<FrameNode>& keyNode);
    void OnSwiperChangeEnd(const RefPtr<FrameNode>& keyNode, bool hasTabsAncestor);
    void OnDialogChangeEnd(const RefPtr<FrameNode>& keyNode, bool isShow);
    void OnTextChangeEnd(const RectF& rect);
    void OnVsyncStart();
    void OnVsyncEnd(const RectF& rootRect);
    bool IsTextAABBCollecting() const;

private:
    void StartTextAABBCollecting();
    void StopTextAABBCollecting(const RectF& rootRect);

    std::set<WeakPtr<FrameNode>> onContentChangeNodes_;
    std::optional<ContentChangeConfig> currentContentChangeConfig_;

    static constexpr uint64_t NS_PER_MS = 1000000;
    static constexpr float DEFAULT_TEXT_CONTENT_RATIO = 0.15f;
    static constexpr int32_t DEFAULT_TEXT_MIN_REPORT_TIME = 100;
    float textContentRatio_ = 0.15f; // default text content ratio is 0.15
    uint64_t textContentInterval_ = 100 * NS_PER_MS; // minimum text content change interval is 100 ms.
    uint64_t lastTextReportTime_ = 0;
    bool textCollecting_ = false;
    bool scrollReported_ = false;
    std::set<std::pair<WeakPtr<FrameNode>, bool>> changedSwiperNodes_;
    RectF textAABB_; // Axis-aligned bounding box(AABB) of Text rects.
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_CONTENT_CHANGE_MANAGER_H
