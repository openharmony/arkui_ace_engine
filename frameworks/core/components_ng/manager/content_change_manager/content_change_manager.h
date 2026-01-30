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
#ifndef IS_RELEASE_VERSION
class ContentChangeDumpManager;
#endif

class ContentChangeManager final : public AceType {
    DECLARE_ACE_TYPE(ContentChangeManager, AceType);
public:
    enum ContentIgnoreEventType : uint32_t {
        NONE = 0,            // no event
        SCROLL_TO = 1 << 0,  // SCROLL: scrollTo
    };

    ContentChangeManager();
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
    void OnScrollChangeStart(const RefPtr<FrameNode>& keyNode);
    void OnScrollChangeEnd(const RefPtr<FrameNode>& keyNode);
    void OnSwiperChangeEnd(const RefPtr<FrameNode>& keyNode, bool hasTabsAncestor);
    void OnDialogChangeEnd(const RefPtr<FrameNode>& keyNode, bool isShow);
    void OnScrollRemoved(int32_t nodeId);
    bool IsScrolling() const;
    void OnTextChangeEnd(const RectF& rect, const RectF& rootRect);
    void OnVsyncStart();
    void OnVsyncEnd(const RectF& rootRect);
    bool IsTextAABBCollecting() const;

    uint32_t ConvertEventStringToEnum(const std::string& type) const;
    uint32_t GetIgnoreEventMask(const std::string& ignoreEventType) const;
    bool IsIgnoringEventType(uint32_t type) const;

#ifndef IS_RELEASE_VERSION
    std::string DumpInfo() const;
#endif

private:
    void ProcessSwiperNodes();
    void ReportSwiperEvent(const RefPtr<FrameNode>& node, bool hasTabsAncestor);
    void StartTextAABBCollecting();
    void StopTextAABBCollecting(const RectF& rootRect);

    std::set<WeakPtr<FrameNode>> onContentChangeNodes_;
    std::optional<ContentChangeConfig> currentContentChangeConfig_;

    static constexpr uint64_t NS_PER_MS = 1000000;
    static constexpr float DEFAULT_TEXT_CONTENT_RATIO = 0.15f;
    static constexpr int32_t DEFAULT_TEXT_MIN_REPORT_TIME = 100;
    float textContentRatio_ = 0.15f; // default text content ratio is 0.15
    uint64_t textContentInterval_ = 100 * NS_PER_MS; // minimum text content change interval is 100 ms.
    uint32_t ignoreEventMask_ = NONE; // default ignore event mask is no event
    uint64_t lastTextReportTime_ = 0;
    bool textCollecting_ = false;
    std::set<std::pair<WeakPtr<FrameNode>, bool>> changedSwiperNodes_;
    std::set<int32_t> scrollingNodes_;
    RectF textAABB_; // Axis-aligned bounding box(AABB) of Text rects.
#ifndef IS_RELEASE_VERSION
    std::shared_ptr<ContentChangeDumpManager> dumpMgr_;
#endif
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_CONTENT_CHANGE_MANAGER_H
