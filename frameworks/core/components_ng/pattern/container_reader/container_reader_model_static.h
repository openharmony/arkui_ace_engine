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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CONTAINER_READER_CONTAINER_READER_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CONTAINER_READER_CONTAINER_READER_MODEL_STATIC_H

#include <functional>
#include <vector>

#include "base/geometry/ng/size_t.h"
#include "base/memory/referenced.h"
#include "core/common/window_size_breakpoint.h"
#include "core/components_ng/base/frame_node.h"

using SizeF = OHOS::Ace::NG::SizeT<float>;

namespace OHOS::Ace::NG {

using ContainerReaderRenderFunction = std::function<RefPtr<UINode>(int64_t, bool&)>;

class ACE_EXPORT ContainerReaderModelStatic {
public:
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetBreakPointConfig(FrameNode* frameNode,
                                    const std::vector<double>& widthBreakpoints,
                                    const std::vector<double>& heightBreakpoints);
    static void ResetBreakPointConfig(FrameNode* frameNode);
    static void SetOnSizeChange(FrameNode* frameNode, std::function<void(const SizeF&)>&& event);
    static void SetOnWidthBreakpointChange(FrameNode* frameNode,
                                            std::function<void(WidthBreakpoint)>&& event);
    static void SetOnHeightBreakpointChange(FrameNode* frameNode,
                                             std::function<void(HeightBreakpoint)>&& event);
    static void SetRenderFunction(FrameNode* frameNode, const ContainerReaderRenderFunction& renderFunction);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CONTAINER_READER_CONTAINER_READER_MODEL_STATIC_H