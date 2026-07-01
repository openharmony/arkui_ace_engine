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

#include "core/components_ng/pattern/dialog/bridge/dialog_dynamic_module.h"

#include "ecmascript/napi/include/jsnapi.h"

#include "core/components_ng/pattern/dialog/action_sheet/action_sheet_model_ng.h"
#include "core/components_ng/pattern/dialog/alert_dialog/alert_dialog_model_ng.h"
#include "core/components_ng/pattern/dialog/bridge/inner_modifier/dialog_inner_modifier.h"
#include "core/components_ng/pattern/dialog/custom_dialog/custom_dialog_controller_model_ng.h"
#include "core/interfaces/cjui/cjui_api.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"
extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_Dialog()
{
    return new OHOS::Ace::DialogDynamicModule();
}

namespace OHOS::Ace {
namespace {
constexpr const char* DIALOG_CAPI = "dialogCAPI";
constexpr const char* DIALOG_INNER_MODIFIER = "dialogInnerModifier";
constexpr const char* ACTION_SHEET_MODEL_NG = "actionSheetModelNG";
constexpr const char* ALERT_DIALOG_MODEL_NG = "alertDialogModelNG";
constexpr const char* CUSTOM_DIALOG_CONTROLLER_MODEL_NG = "customDialogControllerModelNG";
#ifdef INCLUDE_GENERATED_SOURCES
constexpr const char* ACTION_SHEET_ACCESSOR = "actionSheetAccessor";
constexpr const char* ALERT_DIALOG_ACCESSOR = "alertDialogAccessor";
constexpr const char* CUSTOM_DIALOG_CONTROLLER_EXTENDER_ACCESSOR = "customDialogControllerExtenderAccessor";
#endif
} // namespace

namespace NG {
const ArkUIDialogAPI* GetDialogAPI();
const CJUIDialogAPI* GetCJUIDialogAPI();
namespace InnerModifier {
const ArkUIDialogInnerModifier* GetDialogInnerModifier();
} // namespace InnerModifier
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
const GENERATED_ArkUIActionSheetAccessor* GetActionSheetStaticAccessor();
const GENERATED_ArkUIAlertDialogAccessor* GetAlertDialogStaticAccessor();
const GENERATED_ArkUICustomDialogControllerExtenderAccessor* GetCustomDialogControllerStaticExtenderAccessor();
} // namespace GeneratedModifier
#endif
} // namespace NG

void DialogDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm) {}

const void* DialogDynamicModule::GetDynamicModifier()
{
    return nullptr;
}

const void* DialogDynamicModule::GetStaticModifier()
{
    return nullptr;
}

const void* DialogDynamicModule::GetCjModifier()
{
    return NG::GetCJUIDialogAPI();
}

void* DialogDynamicModule::GetModel()
{
    return nullptr;
}

void* DialogDynamicModule::GetModel(const std::string& name)
{
    if (name == ACTION_SHEET_MODEL_NG) {
        static NG::ActionSheetModelNG actionSheetModel;
        return &actionSheetModel;
    }
    if (name == ALERT_DIALOG_MODEL_NG) {
        static NG::AlertDialogModelNG alertDialogModel;
        return &alertDialogModel;
    }
    if (name == CUSTOM_DIALOG_CONTROLLER_MODEL_NG) {
        static NG::CustomDialogControllerModelNG customDialogControllerModel;
        return &customDialogControllerModel;
    }
    return nullptr;
}

const void* DialogDynamicModule::GetCustomModifier(const std::string& name)
{
    if (name == DIALOG_INNER_MODIFIER) {
        return NG::InnerModifier::GetDialogInnerModifier();
    }
    if (name == DIALOG_CAPI) {
        return NG::GetDialogAPI();
    }
#ifdef INCLUDE_GENERATED_SOURCES
    if (name == ACTION_SHEET_ACCESSOR) {
        return NG::GeneratedModifier::GetActionSheetStaticAccessor();
    }
    if (name == ALERT_DIALOG_ACCESSOR) {
        return NG::GeneratedModifier::GetAlertDialogStaticAccessor();
    }
    if (name == CUSTOM_DIALOG_CONTROLLER_EXTENDER_ACCESSOR) {
        return NG::GeneratedModifier::GetCustomDialogControllerStaticExtenderAccessor();
    }
#endif
    return nullptr;
}

} // namespace OHOS::Ace
