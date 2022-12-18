/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DATA_PANEL_DATA_PANEL_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DATA_PANEL_DATA_PANEL_PAINT_METHOD_H

#include "core/components_ng/pattern/data_panel/data_panel_modifer.h"
#include "core/components_ng/pattern/data_panel/data_panel_paint_property.h"
#include "core/components_ng/render/node_paint_method.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT DataPanelPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(DataPanelPaintMethod, NodePaintMethod)
public:
    explicit DataPanelPaintMethod(const RefPtr<DataPanelModifier>& dataPanelModifier)
        : dataPanelModifier_(dataPanelModifier)
    {}
    ~DataPanelPaintMethod() override = default;

    RefPtr<Modifier> GetModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_RETURN(dataPanelModifier_, nullptr);
        return dataPanelModifier_;
    }

    void UpdateModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_VOID(dataPanelModifier_);
        auto paintProperty = DynamicCast<DataPanelPaintProperty>(paintWrapper->GetPaintProperty());

        auto values_ = paintProperty->GetValues().value();
        auto max_ = paintProperty->GetMax().value_or(100);
        auto dataPanelType_ = paintProperty->GetDataPanelType().value_or(0);
        auto effect_ = paintProperty->GetEffect().value_or(false);
        auto offset_ = paintWrapper->GetContentOffset();
        dataPanelModifier_->SetDate(1);
        dataPanelModifier_->SetValues(values_);
        dataPanelModifier_->SetMax(max_);
        dataPanelModifier_->SetDataPanelType(dataPanelType_);
        dataPanelModifier_->SetEffect(effect_);
        dataPanelModifier_->SetOffset(offset_);
    }

private:
    RefPtr<DataPanelModifier> dataPanelModifier_;
    ACE_DISALLOW_COPY_AND_MOVE(DataPanelPaintMethod);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DATA_PANEL_DATA_PANEL_PAINT_METHOD_H