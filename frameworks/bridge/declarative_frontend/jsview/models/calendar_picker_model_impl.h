/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_CALENDAR_PICKER_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_CALENDAR_PICKER_MODEL_IMPL_H

#include "core/components_ng/pattern/calendar_picker/calendar_picker_model.h"
#include "core/common/resource/resource_object.h"

namespace OHOS::Ace::Framework {
class CalendarPickerModelImpl : public OHOS::Ace::CalendarPickerModel {
public:
    void Create(const NG::CalendarSettingData& settingData) override {};
    void SetEdgeAlign(const NG::CalendarEdgeAlign& alignType, const DimensionOffset& offset) override {};
    void ParseEdgeAlignResObj(const std::vector<RefPtr<ResourceObject>>& resArray) override {};
    void SetTextStyle(const NG::PickerTextStyle& textStyle) override {};
    void SetOnChange(NG::SelectedChangeEvent&& onChange) override {};
    void SetChangeEvent(NG::SelectedChangeEvent&& onChange) override {};
    void SetPadding(const NG::PaddingProperty& padding) override {};
    void ClearBorderColor() override {};
    void ClearBorderRadius() override {};
    void ClearHeight() override {};
    void ClearBorder() override {};
    void ClearBorderWidth() override {};
    void ClearPadding() override {};
    void SetMarkToday(bool isMarkToday) override {};
    void CalendarPickerRemoveResObj(const std::string& key) override {};
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_CALENDAR_PICKER_MODEL_IMPL_H
