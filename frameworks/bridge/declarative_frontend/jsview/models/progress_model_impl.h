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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_PROGRESS_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_PROGRESS_MODEL_IMPL_H

#include "core/components_ng/pattern/progress/progress_model.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"

namespace OHOS::Ace::Framework {

class ProgressModelImpl : public OHOS::Ace::ProgressModel {
public:
    void Create(double min, double value, double cachedValue, double max, NG::ProgressType type) override;
    void SetValue(double value) override;
    void SetColor(const Color& value) override;
    void SetBackgroundColor(const Color& value) override;
    void SetStrokeWidth(const Dimension& value) override;
    void SetScaleCount(int32_t value) override;
    void SetScaleWidth(const Dimension& value) override;
    void SetBorderColor(const Color& value) override {}
    void SetBorderWidth(const Dimension& value) override {}
    void SetFontSize(const Dimension& value) override {}
    void SetFontColor(const Color& value) override {}
    void SetText(const std::optional<std::string>& value) override {}
    void SetItalicFontStyle(const Ace::FontStyle& value) override {}
    void SetFontWeight(const FontWeight& value) override {}
    void SetFontFamily(const std::vector<std::string>& value) override {}
    void SetSweepingEffect(bool value) override {}
    void SetGradientColor(const NG::Gradient& value) override {}
    void SetPaintShadow(bool paintShadow) override {}
    void SetProgressStatus(NG::ProgressStatus status) override {}
    void SetShowText(bool value) override {};
    void SetRingSweepingEffect(bool value) override {};
    void SetLinearSweepingEffect(bool value) override {};
    void SetSmoothEffect(bool value) override {};
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_IMAGE_MODEL_IMPL_H
