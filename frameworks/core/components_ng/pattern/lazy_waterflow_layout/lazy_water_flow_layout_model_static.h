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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_WATERFLOW_LAYOUT_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_WATERFLOW_LAYOUT_MODEL_STATIC_H

#include <functional>
#include <optional>
#include <string>

#include "base/geometry/dimension.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"

namespace OHOS::Ace::NG {

class FrameNode;
class UINode;

class ACE_EXPORT LazyWaterFlowLayoutModelStatic {
public:
    using VisibleIndexesChangeEvent = std::function<void(int32_t, int32_t)>;

    // Standalone FrameNode (not pushed onto the build stack); caller owns nodeId.
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetRowGap(FrameNode* frameNode, const std::optional<Dimension>& rowGap);
    static void SetColumnGap(FrameNode* frameNode, const std::optional<Dimension>& columnGap);
    static void SetOnVisibleIndexesChange(FrameNode* frameNode, VisibleIndexesChangeEvent&& onVisibleIndexesChange);
    // Set sticky style; nullopt resets to NONE. The integer must match the NG::StickyStyle enum.
    static void SetSticky(FrameNode* frameNode, const std::optional<int32_t>& stickyStyle);
    // Mount the header node directly.
    static void SetHeader(FrameNode* frameNode, const RefPtr<UINode>& headerNode);
    // Mount the footer node directly.
    static void SetFooter(FrameNode* frameNode, const RefPtr<UINode>& footerNode);
    // Remove the header.
    static void RemoveHeader(FrameNode* frameNode);
    // Remove the footer.
    static void RemoveFooter(FrameNode* frameNode);
};

class ACE_EXPORT LazyVWaterFlowLayoutModelStatic : public LazyWaterFlowLayoutModelStatic {
public:
    static void SetColumnsTemplate(FrameNode* frameNode, const std::string& value);
    // Higher priority than columnsTemplate.
    static void SetItemFillPolicy(FrameNode* frameNode, PresetFillType policy);
    static void ResetItemFillPolicy(FrameNode* frameNode);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_WATERFLOW_LAYOUT_MODEL_STATIC_H
