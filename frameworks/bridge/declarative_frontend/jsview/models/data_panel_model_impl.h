/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_DATA_PANEL_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_DATA_PANEL_MODEL_IMPL_H

#include "core/components_ng/pattern/data_panel/data_panel_model.h"

namespace OHOS::Ace::Framework {

class DataPanelModelImpl : public OHOS::Ace::DataPanelModel {
public:
    void Create(const std::vector<double>& values, double max, int32_t dataPanelType) override;
    void SetEffect(bool isCloseEffect) override;
    void SetValueColors(const std::vector<NG::Gradient>& valueColors) override {}
    void SetTrackBackground(const Color& trackBackgroundColor) override {}
    void SetStrokeWidth(const Dimension& strokeWidth) override {}
    void SetShadowOption(const OHOS::Ace::NG::DataPanelShadow& shadowOption) override {}
    void CreateWithResourceObj(DataPanelResourceType colorType, const RefPtr<ResourceObject>& resObj) override {}
    void SetValueColorsSetByUser(bool value) override {};
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_DATA_PANEL_MODEL_IMPL_H