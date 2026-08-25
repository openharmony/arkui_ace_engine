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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_DUMP_UTILS_DUMP_UTIL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_DUMP_UTILS_DUMP_UTIL_H

#include <list>
#include <string>
#include <vector>

#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

class OverlayManager;

// Starting nodes collected in Inspector-visible style. Each field carries an
// implicit branch marker so Inspector dump can build per-branch JSON, while
// PageScene consumes pageStartNodes and overlayNodes as traversal roots.
//
// Lifecycle: RefPtr fields are strong references. The result MUST be returned
// by value and used as a short-lived stack local. Do NOT cache it as a long
// lived member to avoid pinning FrameNodes alive.
struct DumpStartNodeSet {
    // Inspector-only branch markers
    RefPtr<FrameNode> containerModalTitleRow; // CONTAINER_MODAL title row; null when not container-modal
    RefPtr<FrameNode> dumpBeginNode; // container-modal stack node, or rootNode_ when not container-modal
    RefPtr<FrameNode> atomicServiceRoot;
    // Inspector-only marker. The menu bar is intentionally excluded from
    // PageScene input collection.
    RefPtr<FrameNode> atomicServiceMenuBar;

    // Page roots are reused by Inspector and PageScene. Overlay roots are
    // consumed by PageScene; Inspector discovers the same roots per branch.
    std::vector<RefPtr<FrameNode>> pageStartNodes; // lastPage narrowed via FindTopNavDestination
    std::vector<RefPtr<FrameNode>> overlayNodes; // direct overlay children of each Inspector dump branch
};

// Static utility for Inspector-visible starting node resolution. Follows the
// same "NG class + static methods" convention as Inspector and
// NavigationLayoutUtil, so the algorithm is not exposed as free functions in
// the NG namespace.
class ACE_FORCE_EXPORT DumpUtil {
public:
    // Pure algorithm: collect Inspector-style visible starting nodes.
    // Does NOT read ParamConfig.rectCulling, does NOT perform visible/active/
    // viewport/size checks (those stay in Inspector JSON dump and PageScene).
    // PipelineContext::GetDumpStartNodes() delegates here, passing already
    // resolved data so the util holds only algorithm.
    static DumpStartNodeSet CollectInspectorStartNodes(const RefPtr<FrameNode>& rootNode,
        const RefPtr<FrameNode>& containerModalNode, const RefPtr<FrameNode>& lastPageNode,
        const RefPtr<OverlayManager>& overlayManager);

    // Single source of truth for the overlay tag set shared by Inspector dump
    // and PageScene.
    static bool IsTagInOverlay(const std::string& tag);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_DUMP_UTILS_DUMP_UTIL_H
