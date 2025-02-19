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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_TOGGLE_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_TOGGLE_MODEL_IMPL_H

#include "core/components_ng/pattern/toggle/toggle_model.h"

namespace OHOS::Ace::Framework {

class ToggleModelImpl : public OHOS::Ace::ToggleModel {
public:
    void Create(NG::ToggleType toggleType, bool isOn) override;
    void SetSelectedColor(const std::optional<Color>& selectedColor) override;
    void SetSwitchPointColor(const std::optional<Color>& switchPointColor) override;
    void OnChange(NG::ChangeEvent&& onChange) override;
    void SetWidth(const Dimension& width) override;
    void SetHeight(const Dimension& height) override;
    void SetPadding(const NG::PaddingPropertyF& args, const NG::PaddingProperty& newArgs) override;
    bool IsToggle() override;
    void OnChangeEvent(NG::ChangeEvent&& onChange) override {};
    void SetResponseRegion(const std::vector<DimensionRect>& responseRegion) override {};
    void SetHoverEffect(HoverEffectType hoverEffect) override {};
    void Pop() override;
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_TOGGLE_MODEL_IMPL_H
