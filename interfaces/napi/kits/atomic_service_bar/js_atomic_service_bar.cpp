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

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "interfaces/napi/kits/utils/napi_utils.h"
#include "js_native_api.h"
#include "js_native_api_types.h"
#include "napi/native_api.h"
#include "napi/native_engine/native_value.h"
#include "napi/native_node_api.h"

#include "core/components_ng/pattern/app_bar/app_bar_view.h"
#include "frameworks/base/log/log.h"
#include "bridge/common/media_query/media_queryer.h"
#include "core/common/container.h"
#include "bridge/common/utils/utils.h"
#include "core/common/ace_engine.h"
#include "adapter/ohos/entrance/ace_new_pipe_judgement.h"
#include "frameworks/bridge/common/utils/engine_helper.h"

namespace OHOS::Ace::Napi {

WeakPtr<TaskExecutor> taskExecutor_;

RefPtr<TaskExecutor> ObtainTaskExecutor()
{
    auto taskExecutor = taskExecutor_.Upgrade();
    if (taskExecutor) {
        return taskExecutor;
    }
    auto instanceId = Container::CurrentId();
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        return nullptr;
    }
    taskExecutor_ = container->GetTaskExecutor();
    return taskExecutor_.Upgrade();
}

bool ObtainValue(napi_env env, napi_callback_info info, napi_value* argv, napi_valuetype& valueType)
{
    size_t argc = 1;
    napi_value thisArg = nullptr;
    napi_get_cb_info(env, info, &argc, argv, &thisArg, nullptr);
    if (argc != 1) {
        return true;
    }
    napi_typeof(env, argv[0], &valueType);
    return false;
}

static napi_value JSSetVisible(napi_env env, napi_callback_info info)
{
    napi_value argv[1] = {0};
    napi_valuetype valueType = napi_undefined;
    if (ObtainValue(env, info, argv, valueType)) {
        return nullptr;
    }
    auto taskExecutor = ObtainTaskExecutor();
    if (!taskExecutor) {
        return nullptr;
    }

    if (valueType == napi_boolean) {
        bool visible = true;
        napi_get_value_bool(env, argv[0], &visible);
        taskExecutor->PostTask([visible](){
            NG::AppBarView::SetVisible(visible);
        }, TaskExecutor::TaskType::UI);
    } else {
        LOGI("lqc: cannot get value");
    }
    return nullptr;
}
static napi_value JSSetBackGroundColor(napi_env env, napi_callback_info info)
{
    napi_value argv[1] = {0};
    napi_valuetype valueType = napi_undefined;
    if (ObtainValue(env, info, argv, valueType)) {
        return nullptr;
    }
    auto taskExecutor = ObtainTaskExecutor();
    if (!taskExecutor) {
        return nullptr;
    }

    if (valueType == napi_number) {
        uint32_t num;
        napi_get_value_uint32(env, argv[0], &num);
        Color rowColor(num);
        LOGI("lqc: number=%{public}d", num);
        
        taskExecutor->PostTask([rowColor](){
            NG::AppBarView::SetRowColor(rowColor);
        }, TaskExecutor::TaskType::UI);
    } else if (valueType == napi_string) {
        size_t len = 0;
        napi_status status = napi_get_value_string_utf8(env, argv[0], nullptr, 0, &len);
        if (status != napi_ok || len <= 0) {
            return nullptr;
        }
        std::vector<char> buf(len + 1);
        size_t ret = 0;
        napi_get_value_string_utf8(env, argv[0], buf.data(), len + 1, &ret);
        std::string str(buf.data());
        LOGI("lqc: string=%{public}s", str.c_str());
        taskExecutor->PostTask([str](){
            NG::AppBarView::SetRowColor(str);
        }, TaskExecutor::TaskType::UI);
    } else {
        LOGI("lqc: recognized undefined");
        taskExecutor->PostTask([](){
            NG::AppBarView::SetRowColor();
        }, TaskExecutor::TaskType::UI);
    }
    return nullptr;
}

static napi_value JSSetTitleContent(napi_env env, napi_callback_info info)
{
    napi_value argv[1] = {0};
    napi_valuetype valueType = napi_undefined;
    if (ObtainValue(env, info, argv, valueType)) {
        return nullptr;
    }
    auto taskExecutor = ObtainTaskExecutor();
    if (!taskExecutor) {
        return nullptr;
    }

    if (valueType == napi_string) {
        size_t len = 0;
        napi_status status = napi_get_value_string_utf8(env, argv[0], nullptr, 0, &len);
        if (status != napi_ok || len <= 0) {
            return nullptr;
        }
        std::vector<char> buf(len + 1);
        size_t ret = 0;
        napi_get_value_string_utf8(env, argv[0], buf.data(), len + 1, &ret);
        std::string str(buf.data());
        LOGI("lqc: string=%{public}s", str.c_str());
        taskExecutor->PostTask([str](){
            NG::AppBarView::SetTitleContent(str);
        }, TaskExecutor::TaskType::UI);
    } else {
        LOGI("lqc: cannot get value");
    }
    return nullptr;
}

static napi_value JSSetTitleFontStyle(napi_env env, napi_callback_info info)
{
    napi_value argv[1] = {0};
    napi_valuetype valueType = napi_undefined;
    if (ObtainValue(env, info, argv, valueType)) {
        return nullptr;
    }
    auto taskExecutor = ObtainTaskExecutor();
    if (!taskExecutor) {
        return nullptr;
    }

    if (valueType == napi_number) {
        uint32_t num;
        napi_get_value_uint32(env, argv[0], &num);
        LOGI("lqc: number=%{public}d", num);

        taskExecutor->PostTask([num](){
            NG::AppBarView::SetTitleFontStyle(num == 0 ? FontStyle::NORMAL : FontStyle::ITALIC);
        }, TaskExecutor::TaskType::UI);
    } else {
        LOGI("lqc: cannot get value");
    }
    return nullptr;
}

static napi_value JSSetAtomicServiceIconColor(napi_env env, napi_callback_info info)
{
    napi_value argv[1] = {0};
    napi_valuetype valueType = napi_undefined;
    if (ObtainValue(env, info, argv, valueType)) {
        return nullptr;
    }
    auto taskExecutor = ObtainTaskExecutor();
    if (!taskExecutor) {
        return nullptr;
    }

    if (valueType == napi_number) {
        uint32_t num;
        napi_get_value_uint32(env, argv[0], &num);
        Color rowColor(num);
        LOGI("lqc: number=%{public}d", num);
        
        taskExecutor->PostTask([rowColor](){
            NG::AppBarView::SetIconColor(rowColor);
        }, TaskExecutor::TaskType::UI);
    } else if (valueType == napi_string) {
        size_t len = 0;
        napi_status status = napi_get_value_string_utf8(env, argv[0], nullptr, 0, &len);
        if (status != napi_ok || len <= 0) {
            return nullptr;
        }
        std::vector<char> buf(len + 1);
        size_t ret = 0;
        napi_get_value_string_utf8(env, argv[0], buf.data(), len + 1, &ret);
        std::string str(buf.data());
        LOGI("lqc: string=%{public}s", str.c_str());
        taskExecutor->PostTask([str](){
            NG::AppBarView::SetIconColor(str);
        }, TaskExecutor::TaskType::UI);
    } else {
        LOGI("lqc: cannot get value");
    }
    return nullptr;
}

static napi_value Export(napi_env env, napi_value exports)
{
    napi_property_descriptor properties[] = {
        DECLARE_NAPI_FUNCTION("setVisible", JSSetVisible),
        DECLARE_NAPI_FUNCTION("setBackgroundColor", JSSetBackGroundColor),
        DECLARE_NAPI_FUNCTION("setTitleContent", JSSetTitleContent),
        DECLARE_NAPI_FUNCTION("setTitleFontStyle", JSSetTitleFontStyle),
        DECLARE_NAPI_FUNCTION("setAtomicServiceIconColor", JSSetAtomicServiceIconColor),
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
