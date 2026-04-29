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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_READER_CONTAINER_READER_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_READER_CONTAINER_READER_PATTERN_H

#include <optional>

#include "base/log/dump_log.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/event/focus_type.h"
#include "core/components_ng/pattern/container_reader/container_reader_event_hub.h"
#include "core/components_ng/pattern/container_reader/container_reader_layout_algorithm.h"
#include "core/components_ng/pattern/container_reader/container_reader_layout_property.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {
class ContainerReaderPattern : public Pattern {
    DECLARE_ACE_TYPE(ContainerReaderPattern, Pattern);

public:
    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<ContainerReaderLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<ContainerReaderLayoutAlgorithm>(renderFunction_);
    }

    void SetRenderFunction(const ContainerReaderRenderFunction& renderFunction)
    {
        if (!isInitialRender_) {
            return;
        } else {
            renderFunction_ = renderFunction;
        }
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<ContainerReaderEventHub>();
    }

    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    FocusPattern GetFocusPattern() const override;

    void DumpInfo() override;

    void UpdateBreakpointValues();
    
    void SetIsInitialRender(bool isInitialRender)
    {
        isInitialRender_ = isInitialRender;
    }

private:
    std::optional<SizeF> lastSize_;
    std::optional<WidthBreakpoint> lastWidthBreakpoint_;
    std::optional<HeightBreakpoint> lastHeightBreakpoint_;
    ContainerReaderRenderFunction renderFunction_;
    bool isInitialRender_ = true;

    WidthBreakpoint CalculateWidthBreakpoint(float width);
    HeightBreakpoint CalculateHeightBreakpoint(float height, float width);
    void UpdateSizeChange(const RefPtr<FrameNode>& host, const SizeF& frameSize);
    void UpdateWidthBreakpointChange(const RefPtr<FrameNode>& host, WidthBreakpoint newBreakpoint);
    void UpdateHeightBreakpointChange(const RefPtr<FrameNode>& host, HeightBreakpoint newBreakpoint);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_READER_CONTAINER_READER_PATTERN_H
