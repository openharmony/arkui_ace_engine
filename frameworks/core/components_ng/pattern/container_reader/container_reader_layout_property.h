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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_READER_CONTAINER_READER_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_READER_CONTAINER_READER_LAYOUT_PROPERTY_H

#include <optional>
#include <sstream>
#include <vector>

#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "core/common/window_size_breakpoint.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {

class BreakPointConfig : public AceType {
    DECLARE_ACE_TYPE(BreakPointConfig, AceType);

public:
    BreakPointConfig() = default;
    
    DEFINE_COPY_CONSTRUCTOR_AND_COPY_OPERATOR_AND_COMPARE_OPERATOR_WITH_PROPERTIES(
        BreakPointConfig, (widthBreakpoints)(heightBreakpoints))
    
    std::optional<std::vector<double>> widthBreakpoints;
    
    std::optional<std::vector<double>> heightBreakpoints;

    std::string ToString() const
    {
        std::stringstream ss;
        ss << "BreakPointConfig: {";
        
        ss << "widthBreakpoints: ";
        if (widthBreakpoints.has_value()) {
            ss << "[";
            for (size_t i = 0; i < widthBreakpoints.value().size(); ++i) {
                ss << widthBreakpoints.value()[i];
                if (i < widthBreakpoints.value().size() - 1) {
                    ss << ", ";
                }
            }
            ss << "]";
        } else {
            ss << "null";
        }
        
        ss << ", heightBreakpoints: ";
        if (heightBreakpoints.has_value()) {
            ss << "[";
            for (size_t i = 0; i < heightBreakpoints.value().size(); ++i) {
                ss << heightBreakpoints.value()[i];
                if (i < heightBreakpoints.value().size() - 1) {
                    ss << ", ";
                }
            }
            ss << "]";
        } else {
            ss << "null";
        }
        
        ss << " }";
        return ss.str();
    }
};

class ContainerReaderLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(ContainerReaderLayoutProperty, LayoutProperty);

public:
    ContainerReaderLayoutProperty() = default;
    ~ContainerReaderLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<ContainerReaderLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->size_ = size_;
        value->widthBreakpoint_ = widthBreakpoint_;
        value->heightBreakpoint_ = heightBreakpoint_;
        value->propBreakPointConfig_ = CloneBreakPointConfig();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        size_.reset();
        widthBreakpoint_.reset();
        heightBreakpoint_.reset();
        ResetBreakPointConfig();
    }

    void UpdateSize(const SizeF& size)
    {
        if (size_.has_value() && size_.value() == size) {
            return;
        }
        size_ = size;
    }

    void UpdateWidthBreakpoint(WidthBreakpoint breakpoint)
    {
        if (widthBreakpoint_.has_value() && widthBreakpoint_.value() == breakpoint) {
            return;
        }
        widthBreakpoint_ = breakpoint;
    }

    void UpdateHeightBreakpoint(HeightBreakpoint breakpoint)
    {
        if (heightBreakpoint_.has_value() && heightBreakpoint_.value() == breakpoint) {
            return;
        }
        heightBreakpoint_ = breakpoint;
    }

    const std::optional<SizeF>& GetSize() const
    {
        return size_;
    }

    const std::optional<WidthBreakpoint>& GetWidthBreakpoint() const
    {
        return widthBreakpoint_;
    }

    const std::optional<HeightBreakpoint>& GetHeightBreakpoint() const
    {
        return heightBreakpoint_;
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BreakPointConfig, BreakPointConfig, PROPERTY_UPDATE_MEASURE);

private:
    std::optional<SizeF> size_;
    std::optional<WidthBreakpoint> widthBreakpoint_;
    std::optional<HeightBreakpoint> heightBreakpoint_;

    ACE_DISALLOW_COPY_AND_MOVE(ContainerReaderLayoutProperty);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_READER_CONTAINER_READER_LAYOUT_PROPERTY_H
