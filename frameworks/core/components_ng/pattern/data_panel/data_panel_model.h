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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATA_PANEL_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATA_PANEL_MODEL_H

#include <mutex>

#include "base/geometry/dimension.h"
#include "core/common/resource/resource_object.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/data_panel/data_panel_paint_property.h"
#include "core/components_ng/property/gradient_property.h"

namespace OHOS::Ace {
enum class DataPanelResourceType {
    TRACK_BACKGROUND_COLOR,
    VALUE_COLORS,
    STROKE_WIDTH
};
class ACE_FORCE_EXPORT DataPanelModel {
public:
    static DataPanelModel* GetInstance();
    virtual ~DataPanelModel() = default;

    virtual void Create(const std::vector<double>& values, double max, int32_t dataPanelType) = 0;
    virtual void SetEffect(bool isCloseEffect) = 0;
    virtual void SetValueColors(const std::vector<NG::Gradient>& valueColors) = 0;
    virtual void SetTrackBackground(const Color& trackBackgroundColor) = 0;
    virtual void SetStrokeWidth(const Dimension& strokeWidth) = 0;
    virtual void SetShadowOption(const OHOS::Ace::NG::DataPanelShadow& shadowOption) = 0;
    virtual void CreateWithResourceObj(DataPanelResourceType colorType, const RefPtr<ResourceObject>& resObj) = 0;
    virtual void SetValueColorsSetByUser(bool value) = 0;

private:
    static std::unique_ptr<DataPanelModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATA_PANEL_MODEL_H