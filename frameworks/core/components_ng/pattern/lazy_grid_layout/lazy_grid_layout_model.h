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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_GRID_LAYOUT_LAYOUT_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_GRID_LAYOUT_LAYOUT_MODEL_H

#include <cstdint>
#include <functional>
#include <memory>

#include "base/geometry/dimension.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

class UINode;
enum class StickyStyle : uint32_t;

class ACE_EXPORT LazyGridLayoutModel {
public:
    using VisibleIndexesChangeEvent = std::function<void(int32_t, int32_t)>;

    static void Create();
    static void SetRowGap(const Dimension& space);
    static void SetColumnGap(const Dimension& space);
    static void SetRowGap(FrameNode* frameNode, const Dimension& space);
    static void SetColumnGap(FrameNode* frameNode, const Dimension& space);
    static void SetOnVisibleIndexesChange(VisibleIndexesChangeEvent&& onVisibleIndexesChange);
    static void SetOnVisibleIndexesChange(FrameNode* frameNode, VisibleIndexesChangeEvent&& onVisibleIndexesChange);
    // Set the header / footer sticky behavior (declarative).
    static void SetSticky(StickyStyle stickyStyle);
    // Set the header / footer sticky behavior (per-node).
    static void SetSticky(FrameNode* frameNode, StickyStyle stickyStyle);
    // Declare a header via builder closure (declarative).
    static void SetHeader(std::function<void()>&& header);
    // Declare a footer via builder closure (declarative).
    static void SetFooter(std::function<void()>&& footer);
    // Mount an already-constructed header node (per-node).
    static void SetHeader(FrameNode* frameNode, const RefPtr<UINode>& headerNode);
    // Mount an already-constructed footer node (per-node).
    static void SetFooter(FrameNode* frameNode, const RefPtr<UINode>& footerNode);
    // Remove the header (declarative).
    static void RemoveHeader();
    // Remove the footer (declarative).
    static void RemoveFooter();
    // Remove the header (per-node).
    static void RemoveHeader(FrameNode* frameNode);
    // Remove the footer (per-node).
    static void RemoveFooter(FrameNode* frameNode);
};

class ACE_EXPORT LazyVGridLayoutModel : public LazyGridLayoutModel {
public:
    static void SetColumnsTemplate(const std::string& value);
    static void SetColumnsTemplate(FrameNode* frameNode, const std::string& value);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_GRID_LAYOUT_LAYOUT_MODEL_H
