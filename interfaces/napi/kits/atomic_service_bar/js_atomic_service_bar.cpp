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


#include <sys/time.h>
#include "interfaces/napi/kits/utils/napi_utils.h"


namespace OHOS::Ace::Napi {
namespace {
struct BarRectCallbackContext {
    napi_env env = nullptr;
    napi_ref ref = nullptr;
};

constexpr uint32_t DELAY_TIME = 100;
constexpr int64_t SEC_TO_MILLISEC = 1000;
constexpr int64_t MILLISEC_TO_MICROSEC = 1000;

int64_t GetCurrentTimestamp()
{
    struct timeval currentTime;
    gettimeofday(&currentTime, nullptr);
    return static_cast<int64_t>(currentTime.tv_sec) * SEC_TO_MILLISEC + currentTime.tv_usec / MILLISEC_TO_MICROSEC;
}

void SetRectProperty(napi_env env, napi_value jsFrame, const char* propertyName, float value)
{
    napi_value napiValue = nullptr;
    napi_create_double(env, value, &napiValue);
    napi_set_named_property(env, jsFrame, propertyName, napiValue);
}

napi_value GetBarRect(napi_env env, RefPtr<NG::AppBarView> appBar)
{
    CHECK_NULL_RETURN(appBar, nullptr);
    NG::RectF barRect(0, 0, 0, 0);
    std::optional<NG::RectF> rectOpt = appBar->GetAppBarRect();
    if (rectOpt) {
        const NG::RectF& rect = rectOpt.value();
        barRect.SetLeft(Dimension(rect.Left(), DimensionUnit::PX).ConvertToVp());
        barRect.SetTop(Dimension(rect.Top(), DimensionUnit::PX).ConvertToVp());
        barRect.SetWidth(Dimension(rect.Width(), DimensionUnit::PX).ConvertToVp());
        barRect.SetHeight(Dimension(rect.Height(), DimensionUnit::PX).ConvertToVp());
    }
    napi_value jsFrame = nullptr;
    napi_create_object(env, &jsFrame);
    SetRectProperty(env, jsFrame, "x", barRect.Left());
    SetRectProperty(env, jsFrame, "y", barRect.Top());
    SetRectProperty(env, jsFrame, "width", barRect.Width());
    SetRectProperty(env, jsFrame, "height", barRect.Height());
    return jsFrame;
}

void FreeBarRectCallbackContext(void* ctx)
{
    CHECK_NULL_VOID(ctx);
    auto* context = static_cast<BarRectCallbackContext*>(ctx);
    if (context == nullptr) {
        return;
    }
    if (context->ref && context->env) {
        napi_delete_reference(context->env, context->ref);
    }
    delete context;
}

static void UpdateAppBarRectCallback(napi_env env, napi_value jsFunc, RefPtr<NG::AppBarView> appBar)
{
    CHECK_NULL_VOID(appBar);
    void* oldCtx = appBar->GetRectChangeCallbackContext();
    if (oldCtx) {
        FreeBarRectCallbackContext(oldCtx);
        appBar->SetRectChangeCallbackContext(nullptr, nullptr);
    }
    if (jsFunc == nullptr) {
        return;
    }
    auto* ctx = new BarRectCallbackContext();
    ctx->env = env;
    napi_create_reference(env, jsFunc, 1, &ctx->ref);
    appBar->SetRectChangeCallbackContext(static_cast<void*>(ctx), FreeBarRectCallbackContext);
}

void PostBarRectChangeTask(int64_t createTime, WeakPtr<NG::AppBarView> weakAppBar)
{
    auto appBar = weakAppBar.Upgrade();
    CHECK_NULL_VOID(appBar);
    if (createTime != appBar->GetLastRectChangeTime()) {
        return;
    }
    auto* ctx = static_cast<BarRectCallbackContext*>(appBar->GetRectChangeCallbackContext());
    if (!ctx || !ctx->env || !ctx->ref) {
        return;
    }
    napi_handle_scope scope = nullptr;
    napi_open_handle_scope(ctx->env, &scope);
    CHECK_NULL_VOID(scope);
    napi_value jsCallback = nullptr;
    napi_get_reference_value(ctx->env, ctx->ref, &jsCallback);
    if (jsCallback) {
        napi_value jsFrame = GetBarRect(ctx->env, appBar);
        napi_value argv[1] = { jsFrame };
        napi_call_function(ctx->env, nullptr, jsCallback, 1, argv, nullptr);
    }
    napi_close_handle_scope(ctx->env, scope);
}

void RegisterBarRectChangeCallback(RefPtr<NG::AppBarView> appBar)
{
    appBar->SetRectChangeCallback([
        weakAppBar = WeakPtr<NG::AppBarView>(appBar),
        weakTaskExecutor = WeakPtr<TaskExecutor>(Container::CurrentTaskExecutor())
    ](const NG::RectF& oldRect, const NG::RectF& rect) {
        auto appBar = weakAppBar.Upgrade();
        CHECK_NULL_VOID(appBar);
        auto taskExecutor = weakTaskExecutor.Upgrade();
        CHECK_NULL_VOID(taskExecutor);
        auto createTime = GetCurrentTimestamp();
        appBar->SetLastRectChangeTime(createTime);
        auto task = [createTime, weakAppBar]() {
            PostBarRectChangeTask(createTime, weakAppBar);
        };
        taskExecutor->PostDelayedTask(task, TaskExecutor::TaskType::UI, DELAY_TIME, "ArkUIAtomicServiceBarTask");
    });
}

void UnregisterBarRectChangeCallback(napi_env env, RefPtr<NG::AppBarView> appBar)
{
    UpdateAppBarRectCallback(env, nullptr, appBar);
    appBar->SetRectChangeCallback(nullptr);
}
}

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

static void SetFrameProperty(napi_env env, napi_value jsFrame, const char* propertyName, float value)
{
    napi_value napiValue = nullptr;
    napi_create_double(env, value, &napiValue);
    napi_set_named_property(env, jsFrame, propertyName, napiValue);
}

static napi_value JSGetBarRect(napi_env env, napi_callback_info info)
{
    auto appBar = ObtainAppBar();
    CHECK_NULL_RETURN(appBar, nullptr);
    NG::RectF barRect(0, 0, 0, 0);
    std::optional<NG::RectF> rectOpt = appBar->GetAppBarRect();
    if (rectOpt) {
        const NG::RectF& rect = rectOpt.value();
        barRect.SetLeft(Dimension(rect.Left(), DimensionUnit::PX).ConvertToVp());
        barRect.SetTop(Dimension(rect.Top(), DimensionUnit::PX).ConvertToVp());
        barRect.SetWidth(Dimension(rect.Width(), DimensionUnit::PX).ConvertToVp());
        barRect.SetHeight(Dimension(rect.Height(), DimensionUnit::PX).ConvertToVp());
    }
    napi_value jsFrame = nullptr;
    napi_create_object(env, &jsFrame);
    SetFrameProperty(env, jsFrame, "x", barRect.Left());
    SetFrameProperty(env, jsFrame, "y", barRect.Top());
    SetFrameProperty(env, jsFrame, "width", barRect.Width());
    SetFrameProperty(env, jsFrame, "height", barRect.Height());
    return jsFrame;
}

static napi_value JSOnBarRectChange(napi_env env, napi_callback_info info)
{
    napi_handle_scope scope = nullptr;
    napi_open_handle_scope(env, &scope);
    CHECK_NULL_RETURN(scope, nullptr);
    napi_value argv[1] = { 0 };
    napi_valuetype valueType = napi_undefined;
    if (!GetSingleParam(env, info, argv, valueType)) {
        LOGW("invalid function value for callback");
        napi_close_handle_scope(env, scope);
        return nullptr;
    }
    auto appBar = ObtainAppBar();
    CHECK_NULL_RETURN(appBar, nullptr);
    if (valueType == napi_undefined) {
        UnregisterBarRectChangeCallback(env, appBar);
        napi_close_handle_scope(env, scope);
        return nullptr;
    }
    UpdateAppBarRectCallback(env, argv[0], appBar);
    RegisterBarRectChangeCallback(appBar);
    napi_close_handle_scope(env, scope);
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
        DECLARE_NAPI_FUNCTION("getBarRect", JSGetBarRect),
        DECLARE_NAPI_FUNCTION("onBarRectChange", JSOnBarRectChange),
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
