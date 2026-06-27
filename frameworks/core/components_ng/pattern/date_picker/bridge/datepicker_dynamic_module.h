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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATE_PICKER_BRIDGE_DATE_PICKER_DYNAMIC_MODULE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATE_PICKER_BRIDGE_DATE_PICKER_DYNAMIC_MODULE_H

#include "core/common/dynamic_module.h"
#include "core/components_ng/pattern/date_picker/bridge/datepicker_util.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"
#include "core/interfaces/native/node/node_date_picker_modifier.h"

namespace OHOS::Ace {

namespace NG {
namespace NodeModifier {
const ArkUIDatePickerModifier* GetDatePickerDynamicModifier();
const CJUIDatePickerModifier* GetCJUIDatepickerModifier();
} // namespace NodeModifier
namespace DatePickerUtil {
const DatepickerCustomModifier* GetDatePickerCustomModifier();
} // namespace DatePickerUtil
} // namespace NG

class DatePickerDynamicModule : public DynamicModule {
public:
    DatePickerDynamicModule() = default;
    ~DatePickerDynamicModule() = default;

    void RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm) override;
    const void* GetDynamicModifier() override;
    const void* GetStaticModifier() override;
    const void* GetCjModifier() override;
    void* GetModel() override;
    const void* GetCustomModifier(const std::string& name = "") override;
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATE_PICKER_BRIDGE_DATE_PICKER_DYNAMIC_MODULE_H
