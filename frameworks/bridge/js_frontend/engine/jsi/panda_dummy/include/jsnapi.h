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

#ifndef PANDA_RUNTIME_ECMASCRIPT_NAPI_JSNAPI_H
#define PANDA_RUNTIME_ECMASCRIPT_NAPI_JSNAPI_H

#include <cstdint>
#include <string>
#include <vector>

namespace panda {
class JSNApiHelper;
class EscapeLocalScope;
template <typename T>
class Global;
class JSNApi;
class PrimitiveRef;
class ArrayRef;
class StringRef;
class ObjectRef;
class FunctionRef;
class NumberRef;
namespace test {
class JSNApiTests;
}  // namespace test

namespace ecmascript {
class EcmaVM;
}  // namespace ecmascript

using EcmaVM = ecmascript::EcmaVM;
using TaggedType = uint64_t;
static constexpr uint32_t DEFAULT_GC_POOL_SIZE = 256 * 1024 * 1024;

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define DISALLOW_COPY(className)           \
    className(const className &) = delete; \
    className &operator=(const className &) = delete

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define DISALLOW_MOVE(className)      \
    className(className &&) = delete; \
    className &operator=(className &&) = delete

template <typename T>
class Local {  // NOLINT(cppcoreguidelines-special-member-functions, hicpp-special-member-functions)
public:
    inline Local() = default;

    template <typename S>
    inline Local(const Local<S> &current) : address_(reinterpret_cast<uintptr_t>(*current))
    {
        // Check
    }

    Local(const EcmaVM *vm, const Global<T> &current);

    ~Local() = default;

    inline T *operator*() const
    {
        return GetAddress();
    }

    inline T *operator->() const
    {
        return GetAddress();
    }

    inline bool IsEmpty() const
    {
        return GetAddress() == nullptr;
    }

    inline bool CheckException() const
    {
        return IsEmpty() || GetAddress()->IsException();
    }

    inline bool IsException() const
    {
        return !IsEmpty() && GetAddress()->IsException();
    }

    inline bool IsNull() const
    {
        return IsEmpty() || GetAddress()->IsHole();
    }

private:
    explicit inline Local(uintptr_t addr) : address_(addr) {}
    inline T *GetAddress() const
    {
        return reinterpret_cast<T *>(address_);
    };
    uintptr_t address_ = 0U;
    friend JSNApiHelper;
    friend EscapeLocalScope;
};

template <typename T>
class Global {  // NOLINTNEXTLINE(cppcoreguidelines-special-member-functions
public:
    inline Global() = default;

    template <typename S>
    Global(const EcmaVM *vm, const Local<S> &current);
    ~Global();

    Local<T> ToLocal(const EcmaVM *vm) const
    {
        return Local<T>(vm, *this);
    }

    inline T *operator*() const
    {
        return GetAddress();
    }

    inline T *operator->() const
    {
        return GetAddress();
    }

    inline bool IsEmpty() const
    {
        return GetAddress() == nullptr;
    }

    inline bool CheckException() const
    {
        return IsEmpty() || GetAddress()->IsException();
    }

private:
    inline T *GetAddress() const
    {
        return reinterpret_cast<T *>(address_);
    };
    uintptr_t address_ = 0U;
    const EcmaVM* vm_ { nullptr };
};

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions, hicpp-special-member-functions)
class LocalScope {
public:
    explicit LocalScope(const EcmaVM *vm);
    virtual ~LocalScope();

protected:
    inline LocalScope(const EcmaVM *vm, TaggedType value);

private:
    void *prevNext_;
    void *prevEnd_;
    void *thread_ = nullptr;
};

class EscapeLocalScope final : public LocalScope {
public:
    explicit EscapeLocalScope(const EcmaVM *vm);
    ~EscapeLocalScope() override = default;

    DISALLOW_COPY(EscapeLocalScope);
    DISALLOW_MOVE(EscapeLocalScope);

    template <typename T>
    inline Local<T> Escape(Local<T> current)
    {
        alreadyEscape_ = true;
        *(reinterpret_cast<T *>(escapeHandle_)) = **current;
        return Local<T>(escapeHandle_);
    }

private:
    bool alreadyEscape_ = false;
    uintptr_t escapeHandle_ = 0U;
};

class JSExecutionScope {
public:
    explicit JSExecutionScope(const EcmaVM *vm);
    ~JSExecutionScope();
    DISALLOW_COPY(JSExecutionScope);
    DISALLOW_MOVE(JSExecutionScope);

private:
    void *last_current_thread_ = nullptr;
    bool is_revert_ = false;
};

class JSValueRef {
public:
    static Local<PrimitiveRef> Undefined(const EcmaVM *vm);
    static Local<PrimitiveRef> Null(const EcmaVM *vm);
    static Local<PrimitiveRef> True(const EcmaVM *vm);
    static Local<PrimitiveRef> False(const EcmaVM *vm);
    static Local<JSValueRef> Exception(const EcmaVM *vm);

    int32_t ToInt32(const EcmaVM *vm);
    Local<NumberRef> ToNumber(const EcmaVM *vm);
    bool ToBoolean();
    Local<StringRef> ToString(const EcmaVM *vm);
    Local<ObjectRef> ToObject(const EcmaVM *vm);
    bool IsUndefined();
    bool IsNull();
    bool IsHole();
    bool IsNumber();
    bool IsInt();
    bool IsBoolean();
    bool IsString();
    bool IsObject();
    bool IsArray(const EcmaVM *vm);
    bool IsFunction();
    bool IsProxy();
    bool IsException();

private:
    TaggedType value_;
    friend JSNApi;
    template <typename T>
    friend class Global;
    template <typename T>
    friend class Local;
};

class PrimitiveRef : public JSValueRef {
};

class IntegerRef : public PrimitiveRef {
public:
    static Local<IntegerRef> New(const EcmaVM *vm, int input);
    inline int operator*();
};

class NumberRef : public PrimitiveRef {
public:
    static Local<NumberRef> New(const EcmaVM *vm, double input);
    double Value();
    inline double operator*();
};

class BooleanRef : public PrimitiveRef {
public:
    static Local<BooleanRef> New(const EcmaVM *vm, bool input);
};

class StringRef : public PrimitiveRef {
public:
    static Local<StringRef> NewFromUtf8(const EcmaVM *vm, const char *utf8);
    std::string ToString();
    int32_t Length();
};

class NativePoint : public JSValueRef {
public:
    static NativePoint NewNativePointer(const EcmaVM *vm, void *nativePoint);
};

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions, hicpp-special-member-functions)
class PropertyAttribute {
public:
    static PropertyAttribute Default()
    {
        return PropertyAttribute();
    }
    PropertyAttribute() = default;
    PropertyAttribute(bool w, bool e, bool c) : writable_(w), enumerable_(e), configurable_(c){};
    ~PropertyAttribute() = default;

    bool IsWritable() const
    {
        return writable_;
    }
    bool IsEnumerable() const
    {
        return enumerable_;
    }
    bool IsConfigurable() const
    {
        return configurable_;
    }

private:
    bool writable_ = false;
    bool enumerable_ = false;
    bool configurable_ = false;
};

class ObjectRef : public JSValueRef {
public:
    static inline ObjectRef *Cast(JSValueRef *value)
    {
        // check
        return static_cast<ObjectRef *>(value);
    }
    static Local<ObjectRef> New(const EcmaVM *vm);
    bool Set(const EcmaVM *vm, Local<JSValueRef> key, Local<JSValueRef> value);
    bool Set(const EcmaVM *vm, uint32_t key, Local<JSValueRef> value);
    bool SetAccessorProperty(const EcmaVM *vm, Local<JSValueRef> key, Local<FunctionRef> getter,
                             Local<FunctionRef> setter, PropertyAttribute attribute = PropertyAttribute::Default());
    Local<JSValueRef> Get(const EcmaVM *vm, Local<JSValueRef> key);
    Local<JSValueRef> Get(const EcmaVM *vm, int32_t key);
    Local<ArrayRef> GetOwnPropertyNames(const EcmaVM *vm);
    Local<ArrayRef> GetOwnEnumerablePropertyNames(const EcmaVM *vm);
};

using FunctionCallback = Local<JSValueRef> (*)(EcmaVM *, Local<JSValueRef>,
                                               const Local<JSValueRef>[],  // NOLINTNEXTLINE(modernize-avoid-c-arrays)
                                               int32_t, void *);
class FunctionRef : public ObjectRef {
public:
    static Local<FunctionRef> New(EcmaVM *vm, FunctionCallback nativeFunc, void *data);
    Local<JSValueRef> Call(const EcmaVM *vm, Local<JSValueRef> thisObj,
                           const Local<JSValueRef> argv[],  // NOLINTNEXTLINE(modernize-avoid-c-arrays)
                           int32_t length);
};

class ArrayRef : public ObjectRef {
public:
    static Local<ArrayRef> New(const EcmaVM *vm, int32_t length = 0);
    int32_t Length(const EcmaVM *vm);
};

class JSON {
public:
    static Local<JSValueRef> Parse(const EcmaVM *vm, Local<StringRef> string);
};

using LOG_PRINT = int (*)(int id, int level, const char *tag, const char *fmt, const char *message);

class RuntimeOption {
public:
    enum class GC_TYPE : uint8_t { EPSILON, GEN_GC, STW };
    enum class LOG_LEVEL : uint8_t {
        DEBUG = 3,
        INFO = 4,
        WARN = 5,
        ERROR = 6,
        FATAL = 7,
    };

    void SetPandaStdFile(const std::string &pandaStdFile)
    {
        pandaStdFile_ = pandaStdFile;
    }

    void SetGcType(GC_TYPE type)
    {
        gcType_ = type;
    }

    void SetGcPoolSize(uint32_t size)
    {
        gcPoolSize_ = size;
    }

    void SetLogLevel(LOG_LEVEL logLevel)
    {
        logLevel_ = logLevel;
    }

    void SetLogBufPrint(LOG_PRINT out)
    {
        logBufPrint_ = out;
    }

    void SetDebuggerLibraryPath(const std::string &path)
    {
        debuggerLibraryPath_ = path;
    }

private:
    std::string GetGcType() const
    {
        std::string gcType;
        switch (gcType_) {
            case GC_TYPE::GEN_GC:
                gcType = "gen-gc";
                break;
            case GC_TYPE::STW:
                gcType = "stw";
                break;
            case GC_TYPE::EPSILON:
                gcType = "epsilon";
                break;
            default:
                gcType = "gen-gc";
                break;
        }
        return gcType;
    }

    std::string GetLogLevel() const
    {
        std::string logLevel;
        switch (logLevel_) {
            case LOG_LEVEL::INFO:
            case LOG_LEVEL::WARN:
                logLevel = "info";
                break;
            case LOG_LEVEL::ERROR:
                logLevel = "error";
                break;
            case LOG_LEVEL::FATAL:
                logLevel = "fatal";
                break;
            case LOG_LEVEL::DEBUG:
            default:
                logLevel = "debug";
                break;
        }

        return logLevel;
    }

    uint32_t GetGcPoolSize() const
    {
        return gcPoolSize_;
    }

    std::string GetPandaStdFile() const
    {
        return pandaStdFile_;
    }

    LOG_PRINT GetLogBufPrint() const
    {
        return logBufPrint_;
    }

    std::string GetDebuggerLibraryPath() const
    {
        return debuggerLibraryPath_;
    }

    GC_TYPE gcType_ = GC_TYPE::EPSILON;
    LOG_LEVEL logLevel_ = LOG_LEVEL::DEBUG;
    uint32_t gcPoolSize_ = DEFAULT_GC_POOL_SIZE;
    std::string pandaStdFile_;
    LOG_PRINT logBufPrint_ { nullptr };
    std::string debuggerLibraryPath_ {};
    friend JSNApi;
};

class JSNApi {
public:
    // JSVM
    static EcmaVM *CreateJSVM(const RuntimeOption &option);
    static void DestoryJSVM(EcmaVM *ecmaVm);

    // JS code
    static bool Execute(EcmaVM *vm, Local<StringRef> fileName, Local<StringRef> entry);
    static bool Execute(EcmaVM *vm, const uint8_t *data, int32_t size, Local<StringRef> entry);

    // ObjectRef Operation
    static Local<ObjectRef> GetGlobalObject(const EcmaVM *vm);
    static void ExecutePendingJob(const EcmaVM *vm);

    // Memory
    static void TriggerGC(const EcmaVM *vm);

    static Local<ObjectRef> GetUncaughtException(const EcmaVM *vm);
    static void EnableUserUncaughtErrorHandler(EcmaVM *vm);

    static bool StartDebugger(const char *library_path, EcmaVM *vm);

private:
    static uintptr_t GetHandleAddr(const EcmaVM *vm, uintptr_t localAddress);
    static uintptr_t GetGlobalHandleAddr(const EcmaVM *vm, uintptr_t localAddress);
    static void DisposeGlobalHandleAddr(const EcmaVM *vm, uintptr_t addr);
    template <typename T>
    friend class Global;
    template <typename T>
    friend class Local;
    friend class test::JSNApiTests;
};

template <typename T>
template <typename S>
Global<T>::Global(const EcmaVM *vm, const Local<S> &current) : vm_(vm)
{
    address_ = JSNApi::GetGlobalHandleAddr(vm_, reinterpret_cast<uintptr_t>(*current));
}

template <typename T>
Global<T>::~Global()
{
    JSNApi::DisposeGlobalHandleAddr(vm_, address_);
}

// ---------------------------------- Local --------------------------------------------
template <typename T>
Local<T>::Local([[maybe_unused]] const EcmaVM *vm, const Global<T> &current)
{
    address_ = JSNApi::GetHandleAddr(vm, reinterpret_cast<uintptr_t>(*current));
}
}  // namespace panda
#endif  // PANDA_RUNTIME_ECMASCRIPT_JSNAPI_JSNAPI_H
