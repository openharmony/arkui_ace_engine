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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_READER_CONTAINER_READER_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_READER_CONTAINER_READER_MODEL_NG_H

#include <functional>
#include <vector>

#include "base/geometry/ng/size_t.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "core/common/window_size_breakpoint.h"

namespace OHOS::Ace::NG {

class UINode;
class FrameNode;

using ContainerReaderRenderFunction = std::function<RefPtr<UINode>(int64_t, bool&)>;

} // namespace OHOS::Ace::NG

using SizeF = OHOS::Ace::NG::SizeT<float>;

namespace OHOS::Ace {

class ContainerReaderModel {
public:
    virtual ~ContainerReaderModel() = default;

    virtual void Create() = 0;
    virtual void SetBreakPointConfig(const std::vector<double>& widthBreakpoints,
                                     const std::vector<double>& heightBreakpoints) = 0;
    virtual void SetOnSizeChange(std::function<void(const SizeF&)>&& event) = 0;
    virtual void SetOnWidthBreakpointChange(std::function<void(WidthBreakpoint)>&& event) = 0;
    virtual void SetOnHeightBreakpointChange(std::function<void(HeightBreakpoint)>&& event) = 0;
    virtual void SetRenderFunction(const NG::ContainerReaderRenderFunction& renderFunction) = 0;
};

} // namespace OHOS::Ace

namespace OHOS::Ace::NG {

class ACE_EXPORT ContainerReaderModelNG : public ContainerReaderModel {
public:
    void Create() override;
    void SetBreakPointConfig(const std::vector<double>& widthBreakpoints,
                             const std::vector<double>& heightBreakpoints) override;
    void SetOnSizeChange(std::function<void(const SizeF&)>&& event) override;
    void SetOnWidthBreakpointChange(std::function<void(WidthBreakpoint)>&& event) override;
    void SetOnHeightBreakpointChange(std::function<void(HeightBreakpoint)>&& event) override;
    void SetRenderFunction(const ContainerReaderRenderFunction& renderFunction) override;
    static void SetRenderFunction(FrameNode* frameNode, const ContainerReaderRenderFunction& renderFunction);

    static void SetBreakPointConfig(FrameNode* frameNode, const std::vector<double>& widthBreakpoints,
                                    const std::vector<double>& heightBreakpoints);
    static void ResetBreakPointConfig(FrameNode* frameNode);
    static void SetOnSizeChange(FrameNode* frameNode, std::function<void(const SizeF&)>&& event);
    static void SetOnWidthBreakpointChange(FrameNode* frameNode, std::function<void(WidthBreakpoint)>&& event);
    static void SetOnHeightBreakpointChange(FrameNode* frameNode, std::function<void(HeightBreakpoint)>&& event);

private:
    static RefPtr<FrameNode> GetFrameNode();
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_READER_CONTAINER_READER_MODEL_NG_H
