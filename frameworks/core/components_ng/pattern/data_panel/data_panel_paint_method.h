/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components/common/properties/color.h"
#include "core/components/data_panel/data_panel_theme.h"
#include "core/components_ng/pattern/data_panel/data_panel_modifier.h"
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

    RefPtr<Modifier> GetContentModifier(PaintWrapper* paintWrapper) override;
    void UpdateContentModifier(PaintWrapper* paintWrapper) override;

private:
    void CreateGradient(const std::pair<Color, Color>& itemParam, Gradient& gradient) const;
    RefPtr<DataPanelModifier> dataPanelModifier_;
    ACE_DISALLOW_COPY_AND_MOVE(DataPanelPaintMethod);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DATA_PANEL_DATA_PANEL_PAINT_METHOD_H