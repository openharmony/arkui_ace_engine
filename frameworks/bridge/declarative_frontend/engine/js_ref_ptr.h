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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JS_REF_PTR_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JS_REF_PTR_H

#include "frameworks/bridge/declarative_frontend/engine/quickjs/qjs_ref.h"

#include "frameworks/bridge/declarative_frontend/engine/js_types.h"

namespace OHOS::Ace::Framework {

template<typename T, typename ImplDetail>
class JSRefPtrImpl {
public:
    JSRefPtrImpl() {}
    ~JSRefPtrImpl() {}

    // Conversion from the implementation detail to JSRefPtr
    JSRefPtrImpl(const ImplDetail& rhs) : object_(rhs) {}
    JSRefPtrImpl(ImplDetail&& rhs) : object_(std::move(rhs)) {}

    JSRefPtrImpl(const JSRefPtrImpl<T, ImplDetail>& rhs) : object_(rhs.object_) {}
    JSRefPtrImpl(JSRefPtrImpl<T, ImplDetail>&& rhs) : object_(std::move(rhs.object_)) {}
    JSRefPtrImpl<T, ImplDetail>& operator=(const JSRefPtrImpl<T, ImplDetail>& rhs)
    {
        object_.Reset();
        object_ = rhs.object_;
        return *this;
    }

    JSRefPtrImpl<T, ImplDetail>& operator=(JSRefPtrImpl<T, ImplDetail>&& rhs)
    {
        object_.Reset();
        object_ = std::move(rhs.object_);
        return *this;
    }

    T* operator->() const
    {
        return object_.template Unwrap<T>();
    }

    void Reset()
    {
        object_.Reset();
    }

    operator bool() const
    {
        return !object_.IsEmpty();
    }

    operator ImplDetail() const
    {
        return object_;
    }

    const ImplDetail& Get() const
    {
        return object_;
    }

private:
    ImplDetail object_;
};

template<typename T>
using JSRef = QJSRef<T>;
template<typename T>
using JSWeak = QJSWeak<T>;
template<typename T>
using JSRefPtr = JSRefPtrImpl<T, QJSRef<QJSObject>>;
template<typename T>
using JSWeakPtr = JSRefPtrImpl<T, QJSWeak<QJSObject>>;

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JS_REF_PTR
