/*
 * Copyright (c) 2021-2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <utility>

#include "base/log/ace_scoring_log.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/functions/js_event_function.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "bridge/declarative_frontend/ark_theme/theme_apply/js_date_picker_theme.h"
#include "compatible/components/component_loader.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/pattern/date_picker/picker_types.h"
#include "core/components_ng/pattern/date_picker/picker_theme.h"
#include "core/components_ng/pattern/date_picker/picker_change_event.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/date_picker/datepicker_model_ng.h"
#include "core/components_ng/pattern/time_picker/timepicker_model.h"
#include "core/components_ng/pattern/time_picker/timepicker_model_ng.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/ace_event_helper.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/common/dynamic_module_helper.h"
#include "core/common/resource/resource_object.h"
#include "core/common/resource/resource_parse_utils.h"

namespace OHOS::Ace {
std::unique_ptr<DatePickerModel> DatePickerModel::datePickerInstance_ = nullptr;
std::unique_ptr<DatePickerDialogModel> DatePickerDialogModel::datePickerDialogInstance_ = nullptr;
std::unique_ptr<TimePickerModel> TimePickerModel::timePickerInstance_ = nullptr;
std::unique_ptr<TimePickerDialogModel> TimePickerDialogModel::timePickerDialogInstance_ = nullptr;
std::once_flag DatePickerModel::onceFlag_;
std::once_flag DatePickerDialogModel::onceFlag_;
std::once_flag TimePickerModel::onceFlag_;
std::once_flag TimePickerDialogModel::onceFlag_;

DatePickerModel* DatePickerModel::GetInstance()
{
    // Dynamically load the independently compiled so library
    // from frameworks/core/components_ng/pattern/picker directory
    auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("DatePicker");
    if (module == nullptr) {
        LOGF_ABORT("Can't find DatePicker dynamic module");
    }
    auto* model = reinterpret_cast<const NG::DatePickerModelNG*>(module->GetModel());
    CHECK_NULL_RETURN(model, nullptr);
    std::call_once(onceFlag_, [model]() {
#ifdef NG_BUILD
        datePickerInstance_.reset(const_cast<NG::DatePickerModelNG*>(model));
#else
        if (Container::IsCurrentUseNewPipeline()) {
            datePickerInstance_.reset(const_cast<NG::DatePickerModelNG*>(model));
        } else {
            // Load the datePicker loader from frameworks/compatible/components/picker directory
            static auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("datePicker");
            if (!loader) {
                LOGF("Can't find datePicker loader");
                return;
            }
            datePickerInstance_.reset(reinterpret_cast<DatePickerModel*>(loader->CreateModel()));
        }
#endif
    });

    return datePickerInstance_.get();
}

DatePickerDialogModel* DatePickerDialogModel::GetInstance()
{
    // Dynamically load the independently compiled so library
    // from frameworks/core/components_ng/pattern/picker directory
    auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("DatePickerDialog");
    if (module == nullptr) {
        LOGF_ABORT("Can't find DatePickerDialog dynamic module");
    }
    auto* model = reinterpret_cast<const NG::DatePickerDialogModelNG*>(module->GetModel());
    CHECK_NULL_RETURN(model, nullptr);
    std::call_once(onceFlag_, [model]() {
#ifdef NG_BUILD
        datePickerDialogInstance_.reset(const_cast<NG::DatePickerDialogModelNG*>(model));
#else
        if (Container::IsCurrentUseNewPipeline()) {
            datePickerDialogInstance_.reset(const_cast<NG::DatePickerDialogModelNG*>(model));
        } else {
            // Load the datePicker loader from frameworks/compatible/components/picker directory
            static auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("datePickerDialog");
            if (!loader) {
                LOGF("Can't find datePickerDialog loader");
                return;
            }
            datePickerDialogInstance_.reset(reinterpret_cast<DatePickerDialogModel*>(loader->CreateModel()));
        }
#endif
    });

    return datePickerDialogInstance_.get();
}

TimePickerModel* TimePickerModel::GetInstance()
{
    // Dynamically load the independently compiled so library
    // from frameworks/core/components_ng/pattern/time_picker directory
    auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("TimePicker");
    if (module == nullptr) {
        LOGF("Can't find TimePicker dynamic module");
        abort();
    }
    auto* model = reinterpret_cast<const NG::TimePickerModelNG*>(module->GetModel());
    CHECK_NULL_RETURN(model, nullptr);
    std::call_once(onceFlag_, [model]() {
#ifdef NG_BUILD
        timePickerInstance_.reset(const_cast<NG::TimePickerModelNG*>(model));
#else
        if (Container::IsCurrentUseNewPipeline()) {
            timePickerInstance_.reset(const_cast<NG::TimePickerModelNG*>(model));
        } else {
            // Load the timePicker loader from frameworks/compatible/components/picker directory
            static auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("timePicker");
            if (!loader) {
                LOGF("Can't find timePicker loader");
                return;
            }
            timePickerInstance_.reset(reinterpret_cast<TimePickerModel*>(loader->CreateModel()));
        }
#endif
    });

    return timePickerInstance_.get();
}

TimePickerDialogModel* TimePickerDialogModel::GetInstance()
{
    // Dynamically load the independently compiled so library
    // from frameworks/core/components_ng/pattern/time_picker directory
    auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("TimePickerDialog");
    if (module == nullptr) {
        LOGF("Can't find TimePickerDialog dynamic module");
        abort();
    }
    auto* model = reinterpret_cast<const NG::TimePickerDialogModelNG*>(module->GetModel());
    CHECK_NULL_RETURN(model, nullptr);
    std::call_once(onceFlag_, [model]() {
#ifdef NG_BUILD
        timePickerDialogInstance_.reset(const_cast<NG::TimePickerDialogModelNG*>(model));
#else
        if (Container::IsCurrentUseNewPipeline()) {
            timePickerDialogInstance_.reset(const_cast<NG::TimePickerDialogModelNG*>(model));
        } else {
            // Load the timePicker loader from frameworks/compatible/components/picker directory
            static auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("timePickerDialog");
            if (!loader) {
                LOGF("Can't find timePickerDialog loader");
                return;
            }
            timePickerDialogInstance_.reset(reinterpret_cast<TimePickerDialogModel*>(loader->CreateModel()));
        }
#endif
    });

    return timePickerDialogInstance_.get();
}
} // namespace OHOS::Ace
