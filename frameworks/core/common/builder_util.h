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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_UTIL_BUILDER_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_UTIL_BUILDER_UTILS_H

#include "core/components_ng/base/ui_node.h"

namespace OHOS::Ace::BuilderUtils {
    bool IsBuilderRootNode(const RefPtr<NG::UINode>& node);
    bool IsBuilderContainer(const RefPtr<NG::UINode>& node);
    void AddBuilderToParent(const RefPtr<NG::UINode>& parentNode, std::list<RefPtr<NG::UINode>> nodes);
    void AddBuilderToParent(const RefPtr<NG::UINode>& parentNode, const RefPtr<NG::UINode>& childNode);
    void AddBuilderToContainer(const RefPtr<NG::UINode>& node, const std::list<RefPtr<NG::UINode>>& nodes);
    void AddBuilderToBuilder(const RefPtr<NG::UINode>& node, const std::list<RefPtr<NG::UINode>>& nodes);
    void RemoveBuilderFromParent(const RefPtr<NG::UINode>& parentNode, std::list<RefPtr<NG::UINode>> nodes);
    void RemoveBuilderFromParent(const RefPtr<NG::UINode>& parentNode, const RefPtr<NG::UINode>& childNode);
    void RemoveBuilderFromContainer(const RefPtr<NG::UINode>& node, const std::list<RefPtr<NG::UINode>>& nodes);
    void RemoveBuilderFromBuilder(const RefPtr<NG::UINode>& node, const std::list<RefPtr<NG::UINode>>& nodes);
    void GetBuilderNodes(const RefPtr<NG::UINode>& node, std::list<RefPtr<NG::UINode>>& nodes);
    void GetFirstBuilderNode(const RefPtr<NG::UINode>& node, std::list<RefPtr<NG::UINode>>& nodes);
    void ClearChildInBuilderContainer(int32_t nodeId, std::list<RefPtr<NG::UINode>>& nodes);
} // namespace OHOS::Ace::BuilderUtils

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_UTIL_BUILDER_UTILS_H
