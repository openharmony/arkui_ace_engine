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

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

class PipelineContext;
class NGGestureRecognizer;

/**
 * @brief FrameNode finder providing FrameNode query functionality
 *
 * This class encapsulates the functionality of finding FrameNodes in the UI tree,
 * including coordinate-based queries and focus component queries.
 * Used by various executor classes to implement component positioning.
 */
class FrameNodeFinder {
public:
    explicit FrameNodeFinder(WeakPtr<PipelineContext> context);
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
    RefPtr<FrameNode> FindAt(float x, float y);

private:
    WeakPtr<PipelineContext> context_;
    std::set<WeakPtr<NG::FrameNode>> relaxedInteractionFrameNodes_;

    void SetRelaxedInteractionFrameNode(const std::list<RefPtr<NG::NGGestureRecognizer>>& touchTestResults);
    void CleanRelaxedInteractionGestureEventHub();
    void CollectHittedFrameNodes(const TouchTestResult& touchTestResult);
    void CleanGestureState(int32_t touchId);

    // Helper function: find FrameNode at specified coordinates
    RefPtr<FrameNode> FindAt(const RefPtr<UINode>& rootNode, float x, float y);

    // Helper function: extract FrameNode from touch test results
    RefPtr<FrameNode> ExtractFrameNodeFromResult(const TouchTestResult& touchTestResult);

    // Helper function: recursively find leaf gesture recognizer and get its attached node
    RefPtr<FrameNode> FindLeafGestureRecognizerNode(const RefPtr<NGGestureRecognizer>& gestureRecognizer);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RELAXED_INTERACTION_FRAME_NODE_FINDER_H