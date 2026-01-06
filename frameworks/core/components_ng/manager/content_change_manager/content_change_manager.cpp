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

#include "content_change_manager.h"

#include "base/utils/time_util.h"
#include "base/log/ace_trace.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/pattern.h"
#include "interfaces/inner_api/ui_session/ui_session_manager.h"

namespace OHOS::Ace::NG {
void ContentChangeManager::StartContentChangeReport(const ContentChangeConfig& config)
{
    currentContentChangeConfig_ = config;
    if (LessNotEqual(config.textContentRatio, 0.0) || GreatNotEqual(config.textContentRatio, 1.0)) {
        currentContentChangeConfig_->textContentRatio = DEFAULT_TEXT_CONTENT_RATIO;
    }
    if (config.minReportTime < 0) {
        currentContentChangeConfig_->minReportTime = DEFAULT_TEXT_MIN_REPORT_TIME;
    }
    ACE_SCOPED_TRACE("[ContentChangeManager] StartContentChangeReport: ratio:%f, minReportTime:%d",
        currentContentChangeConfig_->textContentRatio, currentContentChangeConfig_->minReportTime);
    LOGI("[ContentChangeManager] StartContentChangeReport: ratio:%{public}f, minReportTime:%{public}d",
        currentContentChangeConfig_->textContentRatio, currentContentChangeConfig_->minReportTime);
    textContentRatio_ = currentContentChangeConfig_->textContentRatio;
    textContentInterval_ = currentContentChangeConfig_->minReportTime * NS_PER_MS;
    for (auto& weak : onContentChangeNodes_) {
        auto node = weak.Upgrade();
        if (!node) {
            continue;
        }
        node->OnContentChangeRegister(config);
    }
}

void ContentChangeManager::StopContentChangeReport()
{
    ACE_SCOPED_TRACE("[ContentChangeManager] StopContentChangeReport");
    LOGI("[ContentChangeManager] StopContentChangeReport");
    currentContentChangeConfig_.reset();
    for (auto& weak : onContentChangeNodes_) {
        auto node = weak.Upgrade();
        if (!node) {
            continue;
        }
        node->OnContentChangeUnregister();
    }
}

void ContentChangeManager::AddOnContentChangeNode(WeakPtr<FrameNode> node)
{
    onContentChangeNodes_.emplace(node);
    if (IsContentChangeDetectEnable()) {
        auto nodePtr = node.Upgrade();
        CHECK_NULL_VOID(nodePtr);
        nodePtr->OnContentChangeRegister(currentContentChangeConfig_.value());
    }
}

void ContentChangeManager::RemoveOnContentChangeNode(WeakPtr<FrameNode> node)
{
    onContentChangeNodes_.erase(node);
}

void ContentChangeManager::OnPageTransitionEnd(const RefPtr<FrameNode>& keyNode)
{
    if (!IsContentChangeDetectEnable() || !keyNode || IsScrolling()) {
        return;
    }
    ACE_SCOPED_TRACE("[ContentChangeManager] OnPageTransitionEnd");
    auto simpleTree = JsonUtil::CreateSharedPtrJson(true);
    keyNode->DumpSimplifyTreeWithParamConfig(0, simpleTree, false, {false, false, false});
    UiSessionManager::GetInstance()->ReportContentChangeEvent(ChangeType::PAGE, simpleTree->ToString());
}

void ContentChangeManager::OnScrollChangeEnd(const RefPtr<FrameNode>& keyNode)
{
    if (!IsContentChangeDetectEnable() || !keyNode) {
        return;
    }
    ACE_SCOPED_TRACE("[ContentChangeManager] OnScrollChangeEnd");
    scrollingNodes_.erase(keyNode->GetId());
    if (!scrollingNodes_.empty()) {
        return;
    }
    UiSessionManager::GetInstance()->ReportContentChangeEvent(ChangeType::SCROLL, "");
}

void ContentChangeManager::OnSwiperChangeEnd(const RefPtr<FrameNode>& keyNode, bool hasTabsAncestor)
{
    if (!IsContentChangeDetectEnable() || !keyNode || IsScrolling()) {
        return;
    }

    ACE_SCOPED_TRACE("[ContentChangeManager] OnSwiperChangeEnd");
    changedSwiperNodes_.emplace(std::make_pair(WeakPtr(keyNode), hasTabsAncestor));
}

void ContentChangeManager::OnDialogChangeEnd(const RefPtr<FrameNode>& keyNode, bool isShow)
{
    if (!IsContentChangeDetectEnable() || !keyNode || IsScrolling()) {
        return;
    }
    ACE_SCOPED_TRACE("[ContentChangeManager] OnDialogChangeEnd");
    auto simpleTree = JsonUtil::CreateSharedPtrJson(true);
    if (isShow) {
        keyNode->DumpSimplifyTreeWithParamConfig(0, simpleTree, false, {false, false, false});
    } else {
        simpleTree->Put("$type", keyNode->GetTag().c_str());
    }
    simpleTree->Put("show", isShow);
    UiSessionManager::GetInstance()->ReportContentChangeEvent(ChangeType::DIALOG, simpleTree->ToString());
}

void ContentChangeManager::OnTextChangeEnd(const RectF& rect)
{
    if (!IsContentChangeDetectEnable() || !textCollecting_ || rect.IsEmpty() || IsScrolling()) {
        return;
    }
    ACE_SCOPED_TRACE("[ContentChangeManager] OntextChange {%s}", rect.ToString().c_str());
    if (textAABB_.IsEmpty()) {
        textAABB_ = rect;
    } else {
        textAABB_.CombineRectTInner(rect);
    }
}

void ContentChangeManager::OnVsyncStart()
{
    if (!IsContentChangeDetectEnable()) {
        return;
    }

    StartTextAABBCollecting();
}

void ContentChangeManager::OnVsyncEnd(const RectF& rootRect)
{
    if (!IsContentChangeDetectEnable()) {
        return;
    }

    std::set<std::pair<WeakPtr<FrameNode>, bool>> changedSwiperNodes;
    changedSwiperNodes_.swap(changedSwiperNodes);
    for (auto [weak, hasTabsAncestor] : changedSwiperNodes) {
        auto node = weak.Upgrade();
        if (!node) {
            continue;
        }
        ACE_SCOPED_TRACE("[ContentChangeManager] On%sChanged Reporting", hasTabsAncestor ? "Tabs" : "Swiper");
        auto simpleTree = JsonUtil::CreateSharedPtrJson(true);
        node->DumpSimplifyTreeWithParamConfig(0, simpleTree, true, {false, false, false});
        UiSessionManager::GetInstance()->ReportContentChangeEvent(
            hasTabsAncestor ? ChangeType::TABS : ChangeType::SWIPER, simpleTree->ToString());
    }

    StopTextAABBCollecting(rootRect);
}

bool ContentChangeManager::IsTextAABBCollecting() const
{
    return IsContentChangeDetectEnable() && textCollecting_;
}

void ContentChangeManager::StartTextAABBCollecting()
{
    if (!IsContentChangeDetectEnable() || textCollecting_ || IsScrolling()) {
        return;
    }

    uint64_t curr = GetSysTimestamp();
    if (curr - lastTextReportTime_ < textContentInterval_) {
        return;
    }
    textCollecting_ = true;
}

void ContentChangeManager::StopTextAABBCollecting(const RectF& rootRect)
{
    if (!IsContentChangeDetectEnable() || textAABB_.IsEmpty() || IsScrolling()) {
        return;
    }
    if (rootRect.IsIntersectWith(textAABB_)) {
        float rootSize = rootRect.Height() * rootRect.Width();
        RectF intersectRect = rootRect.IntersectRectT(textAABB_);
        float textAABBSize = intersectRect.Height() * intersectRect.Width();
        ACE_SCOPED_TRACE("[ContentChangeManager] StopTextAABBCollecting {%s} / {%s} = %f",
            intersectRect.ToString().c_str(), rootRect.ToString().c_str(), textAABBSize / rootSize);
        if (textAABBSize >= rootSize * textContentRatio_) {
            UiSessionManager::GetInstance()->ReportContentChangeEvent(ChangeType::TEXT, "");
            lastTextReportTime_ = GetSysTimestamp();
        }
    }

    textAABB_.Reset();
    textCollecting_ = false;
}

void ContentChangeManager::OnScrollChangeStart(const RefPtr<FrameNode>& keyNode)
{
    if (!IsContentChangeDetectEnable() || !keyNode) {
        return;
    }
    scrollingNodes_.emplace(keyNode->GetId());
}

void ContentChangeManager::OnScrollRemoved(int32_t nodeId)
{
    if (scrollingNodes_.count(nodeId)) {
        scrollingNodes_.erase(nodeId);
    }
}

bool ContentChangeManager::IsScrolling() const
{
    return !scrollingNodes_.empty();
}
} // namespace OHOS::Ace::NG
