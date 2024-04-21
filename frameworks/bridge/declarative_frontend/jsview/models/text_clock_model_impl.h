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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_TEXT_CLOCK_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_TEXT_CLOCK_MODEL_IMPL_H

#include "bridge/declarative_frontend/jsview/js_container_base.h"
#include "core/components/text_clock/text_clock_component.h"
#include "core/components/text_clock/text_clock_controller.h"
#include "core/components_ng/pattern/text_clock/text_clock_model.h"

namespace OHOS::Ace::Framework {
class ACE_EXPORT TextClockModelImpl : public TextClockModel {
public:
    RefPtr<TextClockController> Create() override;
    void SetFormat(const std::string& format) override;
    void SetHoursWest(float hoursWest) override;
    void SetOnDateChange(std::function<void(const std::string)>&& onChange) override;
    void SetFontSize(const Dimension& value) override;
    void SetTextColor(const Color& value) override;
    void SetItalicFontStyle(Ace::FontStyle value) override;
    void SetFontWeight(FontWeight value) override;
    void SetFontFamily(const std::vector<std::string>& value) override;
    void SetTextShadow(const std::vector<Shadow>& value) override {};
    void SetFontFeature(const std::list<std::pair<std::string, int32_t>>& value) override {};
    void InitFontDefault(const TextStyle& textStyle) override;
    
private:
    static RefPtr<TextClockComponent> GetComponent();
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_TEXT_CLOCK_MODEL_IMPL_H
