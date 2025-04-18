/*
 * Copyright (C) 2025 Huawei Device Co., Ltd.
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

#include "interfaces/napi/kits/promptaction/js_level_order.h"

#include "base/subwindow/subwindow_manager.h"
#include "bridge/common/utils/engine_helper.h"
#include "core/components_ng/pattern/overlay/level_order.h"
#include "interfaces/napi/kits/utils/napi_utils.h"
#include "napi/native_api.h"
#include "napi/native_node_api.h"

namespace OHOS::Ace::Napi {
namespace {
const int32_t CLAMP_PARAM_TOTAL = 2;
#ifdef OHOS_STANDARD_SYSTEM
bool ContainerIsService()
{
    auto containerId = Container::CurrentIdSafely();
    // Get active container when current instanceid is less than 0
    if (containerId < 0) {
        auto container = Container::GetActive();
        if (container) {
            containerId = container->GetInstanceId();
        }
    }
    // for pa service
    return containerId >= MIN_PA_SERVICE_ID || containerId < 0;
}
#endif
} // namespace

void JSLevelOrder::Destructor(napi_env env, void* data, void* hint)
{
    NG::LevelOrder* levelOrder = reinterpret_cast<NG::LevelOrder*>(data);
    CHECK_NULL_VOID(levelOrder);
    delete levelOrder;
    levelOrder = nullptr;
}

napi_value JSLevelOrder::GetOrder(napi_env env, std::optional<double> levelOrder)
{
    if (!levelOrder.has_value()) {
        return nullptr;
    }

    napi_value result = nullptr;
    napi_create_double(env, levelOrder.value(), &result);
    return result;
}

napi_value JSLevelOrder::JSClamp(napi_env env, napi_callback_info info)
{
    size_t argc = CLAMP_PARAM_TOTAL;
    napi_value argv[CLAMP_PARAM_TOTAL] = { nullptr };
    napi_value thisArg = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisArg, nullptr));
    if (argc < CLAMP_PARAM_TOTAL) {
        NapiThrow(env, "The number of parameters is incorrect.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }

    NG::LevelOrder* levelOrder = new (std::nothrow) NG::LevelOrder();
    napi_status status = napi_wrap(env, argv[0], levelOrder, Destructor, nullptr, nullptr);
    if (status != napi_ok) {
        LOGE("Failed to wrap LevelOrder.");
        delete levelOrder;
        return nullptr;
    }

    CHECK_NULL_RETURN(levelOrder, nullptr);
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, argv[1], &valueType);
    if (valueType != napi_number) {
        levelOrder->SetOrder(NG::LevelOrder::ORDER_DEFAULT);
        return thisArg;
    }

    double order = NG::LevelOrder::ORDER_DEFAULT;
    napi_get_value_double(env, argv[1], &order);
    levelOrder->SetOrder(order);
    return thisArg;
}

napi_value JSLevelOrder::JSGetOrder(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv[1] = { nullptr };
    napi_value thisArg = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisArg, nullptr));
    if (argc < 1) {
        NapiThrow(env, "The number of parameters is incorrect.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }

    NG::LevelOrder* levelOrder = nullptr;
    napi_status status = napi_unwrap(env, argv[0], reinterpret_cast<void**>(&levelOrder));
    if (status != napi_ok || !levelOrder) {
        LOGE("Failed to unwrap LevelOrder.");
        return nullptr;
    }

    double order = levelOrder->GetOrder();
    return GetOrder(env, std::make_optional(order));
}

napi_value JSLevelOrder::JSGetTopOrder(napi_env env, napi_callback_info info)
{
#ifdef OHOS_STANDARD_SYSTEM
    if (SystemProperties::GetExtSurfaceEnabled() || !ContainerIsService()) {
        auto delegate = EngineHelper::GetCurrentDelegateSafely();
        if (delegate) {
            std::optional<double> topOrder = delegate->GetTopOrder();
            return GetOrder(env, topOrder);
        }
    } else if (SubwindowManager::GetInstance() != nullptr) {
        std::optional<double> topOrder = SubwindowManager::GetInstance()->GetTopOrder();
        return GetOrder(env, topOrder);
    }
#else
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (delegate) {
        std::optional<double> topOrder = delegate->GetTopOrder();
        return GetOrder(env, topOrder);
    }
#endif
    return nullptr;
}

napi_value JSLevelOrder::JSGetBottomOrder(napi_env env, napi_callback_info info)
{
#ifdef OHOS_STANDARD_SYSTEM
    if (SystemProperties::GetExtSurfaceEnabled() || !ContainerIsService()) {
        auto delegate = EngineHelper::GetCurrentDelegateSafely();
        if (delegate) {
            std::optional<double> bottomOrder = delegate->GetBottomOrder();
            return GetOrder(env, bottomOrder);
        }
    } else if (SubwindowManager::GetInstance() != nullptr) {
        std::optional<double> bottomOrder = SubwindowManager::GetInstance()->GetBottomOrder();
        return GetOrder(env, bottomOrder);
    }
#else
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (delegate) {
        std::optional<double> bottomOrder = delegate->GetBottomOrder();
        return GetOrder(env, bottomOrder);
    }
#endif
    return nullptr;
}

napi_status JSLevelOrder::Define(napi_env env, napi_value exports)
{
    napi_value levelOrder = nullptr;
    napi_create_object(env, &levelOrder);

    napi_value clampFunc = nullptr;
    napi_create_function(env, "clamp", NAPI_AUTO_LENGTH, JSClamp, nullptr, &clampFunc);
    napi_set_named_property(env, levelOrder, "clamp", clampFunc);
    napi_value getOrderFunc = nullptr;
    napi_create_function(env, "getOrder", NAPI_AUTO_LENGTH, JSGetOrder, nullptr, &getOrderFunc);
    napi_set_named_property(env, levelOrder, "getOrder", getOrderFunc);
    napi_value getTopOrderFunc = nullptr;
    napi_create_function(env, "getTopOrder", NAPI_AUTO_LENGTH, JSGetTopOrder, nullptr, &getTopOrderFunc);
    napi_set_named_property(env, levelOrder, "getTopOrder", getTopOrderFunc);
    napi_value getBottomOrderFunc = nullptr;
    napi_create_function(env, "getBottomOrder", NAPI_AUTO_LENGTH, JSGetBottomOrder, nullptr, &getBottomOrderFunc);
    napi_set_named_property(env, levelOrder, "getBottomOrder", getBottomOrderFunc);

    napi_set_named_property(env, exports, "LevelOrder", levelOrder);
    return napi_ok;
}
} // namespace OHOS::Ace::Napi
