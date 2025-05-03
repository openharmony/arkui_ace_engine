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

#include "core/components_ng/pattern/qrcode/qrcode_napi.h"

#include "base/utils/utils.h"
#include "core/components/qrcode/qrcode_theme.h"
#include "core/components_ng/common_napi_utils/common_napi_utils.h"
#include "core/components_ng/pattern/qrcode/qrcode_model.h"
#include "core/components_ng/pattern/qrcode/qrcode_model_ng.h"
#include "core/pipeline/pipeline_base.h"

extern const char _binary_arkui_qrcode_js_start[];
extern const char _binary_arkui_qrcode_abc_start[];
#if !defined(IOS_PLATFORM)
extern const char _binary_arkui_qrcode_js_end[];
extern const char _binary_arkui_qrcode_abc_end[];
#else
extern const char* _binary_arkui_qrcode_js_end;
extern const char* _binary_arkui_qrcode_abc_end;
#endif

namespace OHOS::Ace {
namespace {
static constexpr const size_t MAX_ARG_NUM = 10;
static constexpr const int32_t ARG_NUM_1 = 1;
} // namespace

std::unique_ptr<QRCodeModel> QRCodeModel::instance_ = nullptr;

template<typename T>
RefPtr<T> GetTheme()
{
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, nullptr);
    return themeManager->GetTheme<T>();
}

QRCodeModel* QRCodeModel::GetInstance()
{
    if (!instance_) {
        instance_.reset(new NG::QRCodeModelNG());
    }
    return instance_.get();
}

napi_value JsCreate(napi_env env, napi_callback_info info)
{
    size_t argc = MAX_ARG_NUM;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr));
    NAPI_ASSERT(env, argc >= ARG_NUM_1, "Wrong number of arguments");

    std::string result = CommonNapiUtils::GetStringFromValueUtf8(env, argv[0]);

    QRCodeModel::GetInstance()->Create(result);
    return CommonNapiUtils::CreateNull(env);
}

napi_value JsColor(napi_env env, napi_callback_info info)
{
    size_t argc = MAX_ARG_NUM;
    napi_value thisVal = nullptr;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVal, nullptr));
    NAPI_ASSERT(env, argc >= ARG_NUM_1, "QRCodeModelNapi color wrong number of arguments");

    Color qrcodeColor;
    if (!CommonNapiUtils::ParseColor(env, argv[0], qrcodeColor)) {
        RefPtr<QrcodeTheme> qrcodeTheme = GetTheme<QrcodeTheme>();
        CHECK_NULL_RETURN(qrcodeTheme, CommonNapiUtils::CreateNull(env));
        qrcodeColor = qrcodeTheme->GetQrcodeColor();
    }
    QRCodeModel::GetInstance()->SetQRCodeColor(qrcodeColor);
    return CommonNapiUtils::CreateNull(env);
}

napi_value JsBackgroundColor(napi_env env, napi_callback_info info)
{
    size_t argc = MAX_ARG_NUM;
    napi_value thisVal = nullptr;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVal, nullptr));
    NAPI_ASSERT(env, argc >= ARG_NUM_1, "QRCodeModelNapi backgroundColor wrong number of arguments");

    Color backgroundColor;
    if (!CommonNapiUtils::ParseColor(env, argv[0], backgroundColor)) {
        RefPtr<QrcodeTheme> qrcodeTheme = GetTheme<QrcodeTheme>();
        CHECK_NULL_RETURN(qrcodeTheme, CommonNapiUtils::CreateNull(env));
        backgroundColor = qrcodeTheme->GetBackgroundColor();
    }
    QRCodeModel::GetInstance()->SetQRBackgroundColor(backgroundColor);
    return CommonNapiUtils::CreateNull(env);
}

napi_value Init(napi_env env, napi_value exports)
{
    static napi_property_descriptor desc[] = {
        DECLARE_NAPI_FUNCTION("create", JsCreate),
        DECLARE_NAPI_FUNCTION("color", JsColor),
        DECLARE_NAPI_FUNCTION("backgroundColor", JsBackgroundColor),
    };
    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));
    return exports;
}
} // namespace OHOS::Ace

extern "C" __attribute__((visibility("default"))) void NAPI_arkui_qrcode_GetJSCode(const char** buf, int* bufLen)
{
    if (buf != nullptr) {
        *buf = _binary_arkui_qrcode_js_start;
    }

    if (bufLen != nullptr) {
        *bufLen = _binary_arkui_qrcode_js_end - _binary_arkui_qrcode_js_start;
    }
}

// arkui_qrcode JS register
extern "C" __attribute__((visibility("default"))) void NAPI_arkui_qrcode_GetABCCode(const char** buf, int* buflen)
{
    if (buf != nullptr) {
        *buf = _binary_arkui_qrcode_abc_start;
    }
    if (buflen != nullptr) {
        *buflen = _binary_arkui_qrcode_abc_end - _binary_arkui_qrcode_abc_start;
    }
}

static napi_module_with_js modules = {
    .nm_filename = "arkui/libqrcode.z.so/arkui_qrcode.js",
    .nm_version = 1,
    .nm_flags = 0,
    .nm_register_func = OHOS::Ace::Init,
    .nm_modname = "arkui.qrcode",
    .nm_priv = ((void*)0),
    .nm_get_abc_code = NAPI_arkui_qrcode_GetABCCode,
    .nm_get_js_code = NAPI_arkui_qrcode_GetJSCode,
};

extern "C" __attribute__((constructor)) void RegisterModule()
{
    napi_module_with_js_register(&modules);
}
