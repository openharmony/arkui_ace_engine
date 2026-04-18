/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RELAXED_INTERACTION_FRAME_NODE_FINDER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RELAXED_INTERACTION_FRAME_NODE_FINDER_H

#include <string>
#include <set>
#include <utility>

#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/components_ng/relaxed_interaction/relaxed_interaction_types.h"

namespace OHOS::Ace::NG {

class PipelineContext;

using GestureRecognizerPred = std::function<bool (const RefPtr<NGGestureRecognizer>& gestureRecognizer)>;

class FrameNodeMatch {
public:
    FrameNodeMatch() = default;
    FrameNodeMatch(const RefPtr<NGGestureRecognizer>& gestureRecognizer)
        : gestureRecognizer_(gestureRecognizer)
    {
        if (!gestureRecognizer_) {
            return;
        }
        node_ = gestureRecognizer_->GetAttachedNode().Upgrade();
    }

    explicit operator bool() const noexcept
    {
        return gestureRecognizer_;
    }

    RefPtr<FrameNode> GetNode() const
    {
        return node_;
    }

    GestureEventFunc GetClickFunc() const
    {
        auto clickRecognizer = AceType::DynamicCast<ClickRecognizer>(gestureRecognizer_);
        if (!clickRecognizer) {
            return nullptr;
        }
        return clickRecognizer->GetTapActionFunc();
    }

private:
    RefPtr<NGGestureRecognizer> gestureRecognizer_;
    RefPtr<FrameNode> node_;
};

struct ClickRecognizerPred {
    bool operator()(const RefPtr<NGGestureRecognizer>& gestureRecognizer);
};

struct ContentSwitchRecognizerPred {
    bool operator()(const RefPtr<NGGestureRecognizer>& gestureRecognizer);
};

struct ScrollRecognizerPred {
    bool operator()(const RefPtr<NGGestureRecognizer>& gestureRecognizer);
};

/**
 * @brief FrameNode finder providing FrameNode query functionality
 *
 * This class encapsulates the functionality of finding FrameNodes in the UI tree,
 * including coordinate-based queries and focus component queries.
 * Used by various executor classes to implement component positioning.
 */
class FrameNodeFinder {
public:
    explicit FrameNodeFinder(WeakPtr<PipelineContext> context, GestureRecognizerPred pred);
    ~FrameNodeFinder() = default;

    /**
     * @brief Query FrameNode at specified coordinates
     *
     * Find the corresponding FrameNode based on screen coordinates,
     * used for position-based interaction operations.
     *
     * @param x Screen X coordinate
     * @param y Screen Y coordinate
     * @return RefPtr<FrameNode> Pointer to the found FrameNode, returns nullptr if not found
     */
    FrameNodeMatch FindAt(float x, float y);

private:
    WeakPtr<PipelineContext> context_;
    GestureRecognizerPred pred_;

    FrameNodeMatch FindAt(const RefPtr<UINode>& rootNode, float x, float y);
    FrameNodeMatch Find(const TouchTestResult& touchTestResult);
    FrameNodeMatch FindLeaf(const RefPtr<NGGestureRecognizer>& gestureRecognizer);
    void CleanResult(const TouchTestResult& touchTestResult, int32_t touchId);
    void GetFrameNodes(std::set<WeakPtr<NG::FrameNode>>& frameNodes,
        const std::list<RefPtr<NG::NGGestureRecognizer>>& touchTestResults);
    void CleanFrameNodes(std::set<WeakPtr<NG::FrameNode>>& frameNodes);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RELAXED_INTERACTION_FRAME_NODE_FINDER_H