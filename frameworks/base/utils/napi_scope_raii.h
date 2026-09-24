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

#ifndef FRAMEWORKS_BASE_UTILS_NAPI_SCOPE_RAII_H
#define FRAMEWORKS_BASE_UTILS_NAPI_SCOPE_RAII_H

#include "napi/native_api.h"

namespace OHOS::Ace {

// RAII wrapper for napi_open_handle_scope / napi_close_handle_scope.
// Automatically closes the scope when the object goes out of scope,
// eliminating the risk of forgetting to call napi_close_handle_scope.
class ScopeRAII {
public:
    explicit ScopeRAII(napi_env env) : env_(env), scope_(nullptr)
    {
        napi_open_handle_scope(env_, &scope_);
    }

    ~ScopeRAII()
    {
        napi_close_handle_scope(env_, scope_);
    }

    explicit operator bool() const
    {
        return scope_ != nullptr;
    }

    ScopeRAII(const ScopeRAII&) = delete;
    ScopeRAII& operator=(const ScopeRAII&) = delete;
    ScopeRAII(ScopeRAII&&) = delete;
    ScopeRAII& operator=(ScopeRAII&&) = delete;

private:
    napi_env env_;
    napi_handle_scope scope_;
};

// RAII wrapper for napi_open_escapable_handle_scope /
// napi_close_escapable_handle_scope. Provides an Escape() method that
// forwards to napi_escape_handle with the correct arguments.
// An escapable scope can only escape once; subsequent calls return
// napi_escape_called_twice without calling the NAPI C API again.
class EscapableScopeRAII {
public:
    explicit EscapableScopeRAII(napi_env env) : env_(env), scope_(nullptr)
    {
        napi_open_escapable_handle_scope(env_, &scope_);
    }

    ~EscapableScopeRAII()
    {
        napi_close_escapable_handle_scope(env_, scope_);
    }

    napi_status Escape(napi_value escapee, napi_value* result) const
    {
        return napi_escape_handle(env_, scope_, escapee, result);
    }

    napi_value Escape(napi_value escapee) const
    {
        napi_value result = nullptr;
        napi_escape_handle(env_, scope_, escapee, &result);
        return result;
    }

    explicit operator bool() const
    {
        return scope_ != nullptr;
    }

    EscapableScopeRAII(const EscapableScopeRAII&) = delete;
    EscapableScopeRAII& operator=(const EscapableScopeRAII&) = delete;
    EscapableScopeRAII(EscapableScopeRAII&&) = delete;
    EscapableScopeRAII& operator=(EscapableScopeRAII&&) = delete;

private:
    napi_env env_;
    napi_escapable_handle_scope scope_;
};

} // namespace OHOS::Ace

#endif // FRAMEWORKS_BASE_UTILS_NAPI_SCOPE_RAII_H
