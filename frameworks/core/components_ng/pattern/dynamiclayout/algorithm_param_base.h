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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DYNAMIC_LAYOUT_DYNAMIC_LAYOUT_ALGORITHM_PARAM_BASE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DYNAMIC_LAYOUT_DYNAMIC_LAYOUT_ALGORITHM_PARAM_BASE_H

#include <optional>
#include "base/geometry/calc_dimension.h"
#include "base/memory/ace_type.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/layout/constants.h"
#include "ui/properties/flex.h"

namespace OHOS::Ace::NG {
class LayoutWrapper;
enum DynamicLayoutType {
    DEFAULT_LAYOUT,
    CUSTOM_LAYOUT,
    COLUMN_LAYOUT,
    ROW_LAYOUT,
    STACK_LAYOUT,
    GRID_LAYOUT,  // Grid layout
};

using DynamicLayoutAlgorithmFunc = std::function<void(LayoutWrapper* layoutWrapper)>;

class AlgorithmParamBase : public virtual AceType {
    DECLARE_ACE_TYPE(AlgorithmParamBase, AceType);
public:
    DynamicLayoutType GetDynamicLayoutType() const;
protected:
    void SetDynamicLayoutType(DynamicLayoutType layoutType);
private:
    DynamicLayoutType layoutType_ = DynamicLayoutType::DEFAULT_LAYOUT;
};

class ACE_EXPORT LinearLayoutAlgorithmParam : public AlgorithmParamBase {
    DECLARE_ACE_TYPE(LinearLayoutAlgorithmParam, AlgorithmParamBase);
public:
    explicit LinearLayoutAlgorithmParam(bool isVertical);
    LinearLayoutAlgorithmParam(const CalcDimension &space, FlexAlign mainAxisAlign,
        FlexAlign crossAxisAlign) : space_(space), mainAxisAlign_(mainAxisAlign), crossAxisAlign_(crossAxisAlign) {}
    CalcDimension GetSpace() const
    {
        return space_;
    }
    FlexAlign GetMainAxisAlign() const
    {
        return mainAxisAlign_;
    }
    FlexAlign GetCrossAxisAlign() const
    {
        return crossAxisAlign_;
    }
    void SetSpace(const CalcDimension &space)
    {
        space_ = space;
    }
    void SetMainAxisAlign(FlexAlign mainAxisAlign)
    {
        mainAxisAlign_ = mainAxisAlign;
    }
    void SetCrossAxisAlign(FlexAlign crossAxisAlign)
    {
        crossAxisAlign_ = crossAxisAlign;
    }
    bool IsReverse() const
    {
        return isReverse_;
    }
    void SetIsReverse(bool isReverse)
    {
        isReverse_ = isReverse;
    }
private:
    CalcDimension space_;
    FlexAlign mainAxisAlign_ = FlexAlign::FLEX_START;
    FlexAlign crossAxisAlign_ = FlexAlign::FLEX_START;
    bool isReverse_ {false};
};

class ACE_EXPORT StackLayoutAlgorithmParam: public AlgorithmParamBase {
    DECLARE_ACE_TYPE(StackLayoutAlgorithmParam, AlgorithmParamBase);
public:
    StackLayoutAlgorithmParam()
    {
        SetDynamicLayoutType(DynamicLayoutType::STACK_LAYOUT);
    }

    StackLayoutAlgorithmParam(Alignment alignContent) : alignContent_(alignContent)
    {
        SetDynamicLayoutType(DynamicLayoutType::STACK_LAYOUT);
    }

    Alignment GetAlignContent() const
    {
        return alignContent_;
    }

    void SetAlignContent(Alignment alignContent)
    {
        alignContent_ = alignContent;
    }
private:
    Alignment alignContent_ = Alignment::CENTER;
};

class ACE_EXPORT CustomLayoutAlgorithmParam: public AlgorithmParamBase {
    DECLARE_ACE_TYPE(CustomLayoutAlgorithmParam, AlgorithmParamBase);
public:
    CustomLayoutAlgorithmParam()
    {
        SetDynamicLayoutType(DynamicLayoutType::CUSTOM_LAYOUT);
    }

    void SetOnMeasureSize(DynamicLayoutAlgorithmFunc&& onMeasureSizeFunc)
    {
        onMeasureSizeFunc_ = std::move(onMeasureSizeFunc);
    }

    void SetOnPlaceChildren(DynamicLayoutAlgorithmFunc&& onPlaceChildrenFunc)
    {
        onPlaceChildrenFunc_ = std::move(onPlaceChildrenFunc);
    }

    bool FireOnMeasureSize(LayoutWrapper* layoutWrapper) const;
    bool FireOnPlaceChildren(LayoutWrapper* layoutWrapper) const;
private:
    DynamicLayoutAlgorithmFunc onMeasureSizeFunc_;
    DynamicLayoutAlgorithmFunc onPlaceChildrenFunc_;
};

// Grid layout algorithm parameters
class ACE_EXPORT GridLayoutAlgorithmParam : public AlgorithmParamBase {
    DECLARE_ACE_TYPE(GridLayoutAlgorithmParam, AlgorithmParamBase);

public:
    GridLayoutAlgorithmParam()
    {
        SetDynamicLayoutType(DynamicLayoutType::GRID_LAYOUT);
    }

    // Column template settings
    void SetColumnsTemplate(const std::string& columnsTemplate) { columnsTemplate_ = columnsTemplate; }
    const std::string& GetColumnsTemplate() const { return columnsTemplate_; }

    // Fill policy settings
    void SetItemFillPolicy(PresetFillType itemFillPolicy) { itemFillPolicy_ = itemFillPolicy; }
    const std::optional<PresetFillType>& GetItemFillPolicy() const { return itemFillPolicy_; }

    // Gap settings
    void SetRowsGap(const CalcDimension& rowsGap) { rowsGap_ = rowsGap; }
    CalcDimension GetRowsGap() const { return rowsGap_; }

    void SetColumnsGap(const CalcDimension& columnsGap) { columnsGap_ = columnsGap; }
    CalcDimension GetColumnsGap() const { return columnsGap_; }

private:
    std::string columnsTemplate_;
    std::optional<PresetFillType> itemFillPolicy_;
    CalcDimension rowsGap_;
    CalcDimension columnsGap_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DYNAMIC_LAYOUT_DYNAMIC_LAYOUT_ALGORITHM_PARAM_BASE_H