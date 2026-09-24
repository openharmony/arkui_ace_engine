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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SCROLL_PLACEHOLDER_SCROLL_PLACEHOLDER_NODE_CLONE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SCROLL_PLACEHOLDER_SCROLL_PLACEHOLDER_NODE_CLONE_H

#include <functional>

#include "base/memory/ace_type.h"
#include "core/components_ng/base/ui_node.h"

namespace OHOS::Ace::NG {

// Materializes one node of the immutable placeholder source subtree into its copy. Returning
// nullptr marks the node kind as not copyable: the whole subtree copy then fails and the pool
// degrades to the UI-thread synchronous creation path. The restricted copy protocol for
// JS-backed subtrees is provided by the compiler restricted factory contract (step2); the
// hook is the single swap-in point for it.
using ScrollPlaceholderNodeCopyFn = std::function<RefPtr<UINode>(const RefPtr<UINode>&)>;

// Top-down copy of a built placeholder source instance: parents are copied before children
// and attached as the traversal descends. The source is only read (the placeholder template
// subtree is immutable and render-only by contract), so the traversal is safe to run on a
// background worker. Any uncopyable node fails the whole copy; a half-copied subtree is
// never returned.
inline RefPtr<UINode> CloneScrollPlaceholderSubtreeTopDown(
    const RefPtr<UINode>& source, const ScrollPlaceholderNodeCopyFn& copyNode)
{
    if (!source || !copyNode) {
        return nullptr;
    }
    auto copy = copyNode(source);
    if (!copy) {
        return nullptr;
    }
    for (const auto& child : source->GetChildren()) {
        auto childCopy = CloneScrollPlaceholderSubtreeTopDown(child, copyNode);
        if (!childCopy) {
            return nullptr;
        }
        copy->AddChild(childCopy);
    }
    return copy;
}

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SCROLL_PLACEHOLDER_SCROLL_PLACEHOLDER_NODE_CLONE_H
