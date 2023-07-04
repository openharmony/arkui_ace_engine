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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_JSI_TYPES_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_JSI_TYPES_H

#include "ecmascript/napi/include/jsnapi.h"

#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_fwd.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_value_conversions.h"

#define FAKE_PTR_FOR_FUNCTION_ACCESS(klass) \
    const klass* operator->() const         \
    {                                       \
        return this;                        \
    }

namespace OHOS::Ace::Framework {

using JsiFunctionCallback = panda::Local<panda::JSValueRef> (*)(panda::JsiRuntimeCallInfo*);

template<typename T>
class JsiType {
public:
    JsiType() = default;
    JsiType(const JsiType& rhs);
    JsiType(JsiType&& rhs);
    virtual ~JsiType() = default;

    explicit JsiType(panda::Local<T> val);
    explicit JsiType(const panda::CopyableGlobal<T>& other);

    template<typename S>
    explicit JsiType(panda::Local<S> val);

    JsiType& operator=(const JsiType& rhs);
    JsiType& operator=(JsiType&& rhs);

    template<typename S>
    static JsiType<T> Cast(const JsiType<S>& that)
    {
        return JsiType<T>(that.GetHandle());
    }
    static JsiType<T> New();

    void SetWeak();
    const panda::CopyableGlobal<T>& GetHandle() const;
    const panda::CopyableGlobal<T>& operator->() const;
    Local<T> GetLocalHandle() const;
    bool IsEmpty() const;
    bool IsWeak() const;
    void Reset();
    operator panda::CopyableGlobal<T>() const;

    const EcmaVM* GetEcmaVM() const;

private:
    panda::CopyableGlobal<T> handle_;
};

class JsiValue : public JsiType<panda::JSValueRef> {
public:
    JsiValue() = default;
    explicit JsiValue(const panda::CopyableGlobal<panda::JSValueRef>& val);
    explicit JsiValue(panda::Local<panda::JSValueRef> val);
    ~JsiValue() override = default;

    bool IsEmpty() const;
    bool IsFunction() const;
    bool IsNumber() const;
    bool IsString() const;
    bool IsBoolean() const;
    bool IsObject() const;
    bool IsArray() const;
    bool IsUndefined() const;
    bool IsNull() const;
    std::string ToString() const;
    bool ToBoolean() const;

    template<typename T>
    T ToNumber() const;

    static JsiRef<JsiValue> Undefined();
    static JsiRef<JsiValue> Null();
    static JsiRef<JsiValue> True();
    static JsiRef<JsiValue> False();

    FAKE_PTR_FOR_FUNCTION_ACCESS(JsiValue)
};

/**
 * @brief A wrapper around a panda::StringRef
 *
 */
class JsiString : public JsiValue {
public:
    explicit JsiString(const char* str);
    explicit JsiString(JsiValue str);
    static JsiString New(const char* str);
    FAKE_PTR_FOR_FUNCTION_ACCESS(JsiString)
};

/**
 * @brief A wrapper around a panda::ArrayRef
 *
 */
class JsiArray : public JsiType<panda::ArrayRef> {
public:
    JsiArray();
    explicit JsiArray(panda::Local<panda::ArrayRef> val);
    explicit JsiArray(const panda::CopyableGlobal<panda::ArrayRef>& val);
    ~JsiArray() override = default;
    JsiRef<JsiValue> GetValueAt(size_t index) const;
    void SetValueAt(size_t index, JsiRef<JsiValue> value) const;
    JsiRef<JsiValue> GetProperty(const char* prop) const;
    size_t Length() const;
    bool IsArray() const;
    FAKE_PTR_FOR_FUNCTION_ACCESS(JsiArray)
};

/**
 * @brief A wrapper around panda::ObjectRef
 *
 */
class JsiObject : public JsiType<panda::ObjectRef> {
public:
    JsiObject();
    explicit JsiObject(panda::Local<panda::ObjectRef> val);
    explicit JsiObject(const panda::CopyableGlobal<panda::ObjectRef>& val);
    bool IsUndefined() const;
    ~JsiObject() override = default;
    enum InternalFieldIndex { INSTANCE = 0 };

    template<typename T>
    T* Unwrap() const;

    template<typename T>
    void Wrap(T* data) const;

    JsiRef<JsiArray> GetPropertyNames() const;
    JsiRef<JsiValue> GetProperty(const char* prop) const;
    JsiRef<JsiValue> ToJsonObject(const char* value) const;

    template<typename T>
    void SetProperty(const char* prop, const T value) const;
    void SetPropertyJsonObject(const char* prop, const char* value) const;
    void SetPropertyObject(const char* prop, JsiRef<JsiValue> value) const;

    FAKE_PTR_FOR_FUNCTION_ACCESS(JsiObject)
};

/**
 * @brief A wrapper around panda::FunctionRef
 *
 */
class JsiFunction : public JsiType<panda::FunctionRef> {
public:
    JsiFunction();
    explicit JsiFunction(panda::Local<panda::FunctionRef> val);
    explicit JsiFunction(const panda::CopyableGlobal<panda::FunctionRef>& val);
    ~JsiFunction() override = default;

    JsiRef<JsiValue> Call(JsiRef<JsiValue> thisVal, int argc = 0, JsiRef<JsiValue> argv[] = nullptr) const;
    static panda::Local<panda::FunctionRef> New(JsiFunctionCallback func);

    FAKE_PTR_FOR_FUNCTION_ACCESS(JsiFunction)
};

class JsiObjTemplate : public JsiObject {
public:
    JsiObjTemplate() = default;
    explicit JsiObjTemplate(panda::Local<panda::ObjectRef> val);
    explicit JsiObjTemplate(const panda::CopyableGlobal<panda::ObjectRef>& val);
    ~JsiObjTemplate() override = default;

    void SetInternalFieldCount(int32_t count) const;
    JsiRef<JsiObject> NewInstance() const;
    static panda::Local<panda::JSValueRef> New();

    FAKE_PTR_FOR_FUNCTION_ACCESS(JsiObjTemplate)
};

struct JsiExecutionContext {
    panda::ecmascript::EcmaVM* vm_ = nullptr;
};

class JsiCallbackInfo {
public:
    JsiCallbackInfo(panda::JsiRuntimeCallInfo* info);
    ~JsiCallbackInfo() = default;
    JsiCallbackInfo(const JsiCallbackInfo&) = delete;
    JsiCallbackInfo& operator=(const JsiCallbackInfo&) = delete;

    JsiRef<JsiValue> operator[](size_t index) const;
    JsiRef<JsiObject> This() const;
    int Length() const;

    template<typename T>
    void SetReturnValue(T* instance) const;

    template<typename T>
    void SetReturnValue(JsiRef<T> val) const;

    void ReturnSelf() const;

    std::variant<void*, panda::CopyableGlobal<panda::JSValueRef>> GetReturnValue()
    {
        return retVal_;
    }

    JsiExecutionContext GetExecutionContext() const
    {
        return JsiExecutionContext { info_->GetVM() };
    }

    panda::ecmascript::EcmaVM* GetVm() const
    {
        return info_->GetVM();
    }

private:
    panda::JsiRuntimeCallInfo* info_ = nullptr;

    mutable std::variant<void*, panda::CopyableGlobal<panda::JSValueRef>> retVal_;
};

class JsiGCMarkCallbackInfo {
public:
    template<typename T>
    void Mark(const JsiRef<T>& val) const
    {}
};

class JsiDate : public JsiType<panda::DateRef> {
public:
    JsiDate() = default;
    explicit JsiDate(panda::Local<panda::DateRef> val);
    explicit JsiDate(const panda::CopyableGlobal<panda::DateRef>& val);
    ~JsiDate() override = default;

    static JsiRef<JsiValue> New(double value);
    FAKE_PTR_FOR_FUNCTION_ACCESS(JsiDate)
};

class JsiException {
public:
    template<typename... Args>
    static void Throw(const char* format, Args... args);
    template<typename... Args>
    static void ThrowRangeError(const char* format, Args... args);
    template<typename... Args>
    static void ThrowReferenceError(const char* format, Args... args);
    template<typename... Args>
    static void ThrowSyntaxError(const char* format, Args... args);
    template<typename... Args>
    static void ThrowTypeError(const char* format, Args... args);
    template<typename... Args>
    static void ThrowEvalError(const char* format, Args... args);
};

} // namespace OHOS::Ace::Framework

#include "jsi_types.inl"

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_JSI_TYPES_H
