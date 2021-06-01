/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_QUICKJS_QJS_VALUE_CONVERSIONS_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_QUICKJS_QJS_VALUE_CONVERSIONS_H

#include <string>

#include "frameworks/bridge/js_frontend/engine/quickjs/qjs_utils.h"

namespace __private__ {

template<typename T>
struct is_signed_int {
    static constexpr bool value =
        std::is_integral<T>::value && std::is_signed<T>::value && !std::is_same<T, bool>::value;
};

} // namespace __private__

namespace __remove__ {

template<typename T, typename E = void>
struct QJSValueConvertor;

template<typename T>
struct QJSValueConvertor<T, typename std::enable_if<std::is_same<T, std::string>::value>::type> {
    static T FromJSValue(JSValue val)
    {
        auto* ctx = OHOS::Ace::Framework::QJSContext::current();
        OHOS::Ace::Framework::ScopedString str(ctx, val);
        return str.get();
    }

    static bool Validate(JSValue val)
    {
        if (JS_IsString(val)) {
            return true;
        }

        return false;
    }
};

template<typename T>
struct QJSValueConvertor<T, typename std::enable_if<std::is_unsigned<T>::value>::type> {
    static T FromJSValue(JSValue value)
    {
        auto* ctx = OHOS::Ace::Framework::QJSContext::current();
        uint32_t pres;
        JS_ToUint32(ctx, &pres, value);
        return pres;
    }

    static bool Validate(JSValue value)
    {
        if (JS_IsNumber(value)) {
            return true;
        }

        return false;
    }
};

template<typename T>
struct QJSValueConvertor<T, typename std::enable_if<__private__::is_signed_int<T>::value>::type> {
    static T FromJSValue(JSValue value)
    {
        auto* ctx = OHOS::Ace::Framework::QJSContext::current();
        int32_t pres;
        JS_ToInt32(ctx, &pres, value);
        return pres;
    }

    static bool Validate(JSValue value)
    {
        if (JS_IsInteger(value)) {
            return true;
        }

        return false;
    }
};

} // namespace __remove__

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_QUICKJS_QJS_VALUE_CONVERSIONS_H
