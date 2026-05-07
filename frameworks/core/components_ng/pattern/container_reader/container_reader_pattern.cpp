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

#include "core/components_ng/pattern/container_reader/container_reader_pattern.h"

#include "base/geometry/ng/size_t.h"
#include "base/log/dump_log.h"
#include "core/common/container.h"
#include "core/common/window_size_breakpoint.h"
#include "core/components_ng/pattern/container_reader/container_reader_event_hub.h"
#include "core/components_ng/pattern/container_reader/container_reader_layout_property.h"
#include "frameworks/core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {

namespace {
constexpr float INVALID_DIMENSION = 0.0f;
} // namespace

FocusPattern ContainerReaderPattern::GetFocusPattern() const
{
    return { FocusType::SCOPE, true };
}

bool ContainerReaderPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    renderFunction_ = nullptr;

    bool skip = Pattern::OnDirtyLayoutWrapperSwap(dirty, config);

    if (config.skipMeasure) {
        return skip;
    }

    UpdateBreakpointValues();

    return skip;
}

void ContainerReaderPattern::UpdateBreakpointValues()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);

    auto frameSize = geometryNode->GetFrameSize();
    auto layoutProperty = DynamicCast<ContainerReaderLayoutProperty>(host->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);

    auto newWidthBreakpoint = CalculateWidthBreakpoint(frameSize.Width());
    auto newHeightBreakpoint = CalculateHeightBreakpoint(frameSize.Height(), frameSize.Width());

    UpdateSizeChange(host, frameSize);
    UpdateWidthBreakpointChange(host, newWidthBreakpoint);
    UpdateHeightBreakpointChange(host, newHeightBreakpoint);
}

void ContainerReaderPattern::UpdateSizeChange(const RefPtr<FrameNode>& host, const SizeF& frameSize)
{
    if (lastSize_.has_value() && NearEqual(lastSize_.value().Width(), frameSize.Width())
        && NearEqual(lastSize_.value().Height(), frameSize.Height())) {
        return;
    }
    auto eventHub = host->GetEventHub<ContainerReaderEventHub>();
    if (eventHub) {
        auto context = PipelineContext::GetCurrentContextSafely();
        CHECK_NULL_VOID(context);
        
        SizeF size;
        size.SetWidth(context->ConvertPxToVp(Dimension(frameSize.Width(), DimensionUnit::PX)));
        size.SetHeight(context->ConvertPxToVp(Dimension(frameSize.Height(), DimensionUnit::PX)));
        eventHub->FireSizeChange(size);
    }
    lastSize_ = frameSize;
}

void ContainerReaderPattern::UpdateWidthBreakpointChange(
    const RefPtr<FrameNode>& host, WidthBreakpoint newBreakpoint)
{
    if (lastWidthBreakpoint_.has_value() && lastWidthBreakpoint_.value() == newBreakpoint) {
        return;
    }
    auto layoutProperty = DynamicCast<ContainerReaderLayoutProperty>(host->GetLayoutProperty());
    if (layoutProperty) {
        layoutProperty->UpdateWidthBreakpoint(newBreakpoint);
    }
    auto eventHub = host->GetEventHub<ContainerReaderEventHub>();
    if (eventHub) {
        eventHub->FireWidthBreakpointChange(newBreakpoint);
    }
    lastWidthBreakpoint_ = newBreakpoint;
}

void ContainerReaderPattern::UpdateHeightBreakpointChange(
    const RefPtr<FrameNode>& host, HeightBreakpoint newBreakpoint)
{
    if (lastHeightBreakpoint_.has_value() && lastHeightBreakpoint_.value() == newBreakpoint) {
        return;
    }
    auto layoutProperty = DynamicCast<ContainerReaderLayoutProperty>(host->GetLayoutProperty());
    if (layoutProperty) {
        layoutProperty->UpdateHeightBreakpoint(newBreakpoint);
    }
    auto eventHub = host->GetEventHub<ContainerReaderEventHub>();
    if (eventHub) {
        eventHub->FireHeightBreakpointChange(newBreakpoint);
    }
    lastHeightBreakpoint_ = newBreakpoint;
}

WidthBreakpoint ContainerReaderPattern::CalculateWidthBreakpoint(float width)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, WidthBreakpoint::WIDTH_XS);
    auto layoutProperty = DynamicCast<ContainerReaderLayoutProperty>(host->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, WidthBreakpoint::WIDTH_XS);

    // user defined
    auto breakPointConfig = layoutProperty->GetBreakPointConfig();
    if (breakPointConfig.has_value() &&
        breakPointConfig->widthBreakpoints.has_value() &&
        !breakPointConfig->widthBreakpoints->empty()) {
        const auto& customBreakpoints = breakPointConfig->widthBreakpoints.value();

        double density = PipelineBase::GetCurrentDensity();
        return GetCalcWidthBreakpoint(customBreakpoints, density, width);
    }

    double density = PipelineBase::GetCurrentDensity();
    return GetCommonWidthBreakpoint(width, density);
}

HeightBreakpoint ContainerReaderPattern::CalculateHeightBreakpoint(float height, float width)
{
    if (height <= INVALID_DIMENSION || width <= INVALID_DIMENSION) {
        return HeightBreakpoint::HEIGHT_SM;
    }

    auto host = GetHost();
    CHECK_NULL_RETURN(host, HeightBreakpoint::HEIGHT_SM);
    auto layoutProperty = DynamicCast<ContainerReaderLayoutProperty>(host->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, HeightBreakpoint::HEIGHT_SM);

    // user defined
    auto breakPointConfig = layoutProperty->GetBreakPointConfig();
    if (breakPointConfig.has_value() &&
        breakPointConfig->heightBreakpoints.has_value() &&
        !breakPointConfig->heightBreakpoints->empty()) {
        const auto& customBreakpoints = breakPointConfig->heightBreakpoints.value();

        double aspectRatio = static_cast<double>(height) / static_cast<double>(width);
        return GetCalcHeightBreakpoint(customBreakpoints, aspectRatio);
    }

    double aspectRatio = static_cast<double>(height) / static_cast<double>(width);
    return GetCommonHeightBreakpoint(aspectRatio);
}

void ContainerReaderPattern::DumpInfo()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = DynamicCast<ContainerReaderLayoutProperty>(host->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    
    auto size = layoutProperty->GetSize();
    if (size.has_value()) {
        DumpLog::GetInstance().AddDesc(std::string("size: ").append(size.value().ToString().c_str()));
    }
    
    auto widthBreakpoint = layoutProperty->GetWidthBreakpoint();
    if (widthBreakpoint.has_value()) {
        DumpLog::GetInstance().AddDesc(std::string("widthBreakpoint: ").append(
            std::to_string(static_cast<int32_t>(widthBreakpoint.value()))));
    }
    
    auto heightBreakpoint = layoutProperty->GetHeightBreakpoint();
    if (heightBreakpoint.has_value()) {
        DumpLog::GetInstance().AddDesc(std::string("heightBreakpoint: ").append(
            std::to_string(static_cast<int32_t>(heightBreakpoint.value()))));
    }
}

} // namespace OHOS::Ace::NG
