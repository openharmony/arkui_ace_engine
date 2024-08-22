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


#include "interfaces/napi/kits/utils/napi_utils.h"


namespace OHOS::Ace::Napi {
static RefPtr<NG::AppBarView> ObtainAppBar()
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, nullptr);
    return container->GetAppBar();
}

static void SetBarInUIThread(TaskExecutor::Task&& task, const std::string& name)
{
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(std::move(task), TaskExecutor::TaskType::UI, name, PriorityType::VIP);
}

static napi_value JSSetVisible(napi_env env, napi_callback_info info)
{
    napi_value argv[1] = { 0 };
    napi_valuetype valueType = napi_undefined;
    if (!GetSingleParam(env, info, argv, valueType) || (valueType != napi_boolean)) {
        LOGW("invalid boolean value for visible");
        return nullptr;
    }
    bool visible = true;
    napi_get_value_bool(env, argv[0], &visible);
    auto appBar = ObtainAppBar();
    CHECK_NULL_RETURN(appBar, nullptr);
    SetBarInUIThread([visible, appBar]() { appBar->SetVisible(visible); }, "ArkUIAppBarSetVisible");
    return nullptr;
}

static napi_value JSSetBackgroundColor(napi_env env, napi_callback_info info)
{
    napi_value argv[1] = { 0 };
    napi_valuetype valueType = napi_undefined;
    if (!GetSingleParam(env, info, argv, valueType)) {
        return nullptr;
    }
    std::optional<Color> color = GetOptionalColor(env, argv[0], valueType);
    if (!color && valueType != napi_undefined) {
        return nullptr;
    }
    auto appBar = ObtainAppBar();
    CHECK_NULL_RETURN(appBar, nullptr);
    SetBarInUIThread([color, appBar]() { appBar->SetRowColor(color); }, "ArkUIAppBarSetRowColor");
    return nullptr;
}

static napi_value JSSetTitleContent(napi_env env, napi_callback_info info)
{
    napi_value argv[1] = { 0 };
    napi_valuetype valueType;
    std::string str;
    if (!GetSingleParam(env, info, argv, valueType) || (valueType != napi_string)) {
        LOGW("invalid string value for content");
        return nullptr;
    }
    bool result = GetNapiString(env, argv[0], str, valueType);
    if (!result) {
        return nullptr;
    }
    auto appBar = ObtainAppBar();
    CHECK_NULL_RETURN(appBar, nullptr);
    SetBarInUIThread([str, appBar]() { appBar->SetContent(str); }, "ArkUIAppBarSetContent");
    return nullptr;
}

static napi_value JSSetTitleFontStyle(napi_env env, napi_callback_info info)
{
    napi_value argv[1] = { 0 };
    napi_valuetype valueType = napi_undefined;
    if (!GetSingleParam(env, info, argv, valueType) || (valueType != napi_number)) {
        LOGW("invalid number value for fontStyle");
        return nullptr;
    }
    uint32_t num;
    napi_get_value_uint32(env, argv[0], &num);
    auto appBar = ObtainAppBar();
    CHECK_NULL_RETURN(appBar, nullptr);
    SetBarInUIThread(
        [num, appBar]() { appBar->SetFontStyle(num == 0 ? Ace::FontStyle::NORMAL : Ace::FontStyle::ITALIC); },
        "ArkUIAppBarSetFontStyle");
    return nullptr;
}

static napi_value JSSetIconColor(napi_env env, napi_callback_info info)
{
    napi_value argv[1] = { 0 };
    napi_valuetype valueType = napi_undefined;
    if (!GetSingleParam(env, info, argv, valueType)) {
        return nullptr;
    }
    std::optional<Color> color = GetOptionalColor(env, argv[0], valueType);
    if (!color && valueType != napi_undefined) {
        return nullptr;
    }
    auto appBar = ObtainAppBar();
    CHECK_NULL_RETURN(appBar, nullptr);
    SetBarInUIThread([color, appBar]() { appBar->SetIconColor(color); }, "ArkUIAppBarSetIconColor");
    return nullptr;
}

static napi_value Export(napi_env env, napi_value exports)
{
    napi_property_descriptor properties[] = {
        DECLARE_NAPI_FUNCTION("setVisible", JSSetVisible),
        DECLARE_NAPI_FUNCTION("setBackgroundColor", JSSetBackgroundColor),
        DECLARE_NAPI_FUNCTION("setTitleContent", JSSetTitleContent),
        DECLARE_NAPI_FUNCTION("setTitleFontStyle", JSSetTitleFontStyle),
        DECLARE_NAPI_FUNCTION("setIconColor", JSSetIconColor),
    };
    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(properties) / sizeof(properties[0]), properties));
    return exports;
}

static napi_module atomic_service_bar_module = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Export,
    .nm_modname = "atomicservicebar",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void RegisterAtomicServiceBar()
{
    napi_module_register(&atomic_service_bar_module);
}
} // namespace OHOS::Ace::Napi
