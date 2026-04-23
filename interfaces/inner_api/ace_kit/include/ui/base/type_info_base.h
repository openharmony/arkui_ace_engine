/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_TYPE_INFO_BASE_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_TYPE_INFO_BASE_H

#include <string>
#include <type_traits>

#include "ui/base/memory_monitor_def.h"

// Generate 'TypeInfo' for each classes.
// And using hash code of its name for 'TypeId'.
namespace OHOS::Ace {
class TypeInfoHelper;
}
#define DECLARE_CLASS_TYPE_INFO(classname)                                                  \
public:                                                                                     \
    friend class OHOS::Ace::TypeInfoHelper;                                                 \
    static const char* TypeName()                                                           \
    {                                                                                       \
        return #classname;                                                                  \
    }                                                                                       \
    static TypeInfoBase::IdType TypeId()                                                    \
    {                                                                                       \
        static TypeInfoBase::IdType myTypeId = std::hash<std::string> {}(#classname);       \
        return myTypeId;                                                                    \
    }                                                                                       \
    DECLARE_CLASS_TYPE_SIZE(classname)

// Integrate it into class declaration to support 'DynamicCast'.
#define DECLARE_RELATIONSHIP_OF_CLASSES(classname, ...) DECLARE_CLASS_TYPE_INFO(classname)            \
protected:                                                                                            \
    template<class __T, class __O, class... __V>                                                      \
    uintptr_t TrySafeCastById(TypeInfoBase::IdType id) const                                          \
    {                                                                                                 \
        VERIFY_DECLARED_CLASS(__T);                                                                   \
        uintptr_t ptr = __T::SafeCastById(id);                                                        \
        return ptr != 0 ? ptr : TrySafeCastById<__O, __V...>(id);                                     \
    }                                                                                                 \
    template<class __T>                                                                               \
    uintptr_t TrySafeCastById(TypeInfoBase::IdType id) const                                          \
    {                                                                                                 \
        VERIFY_DECLARED_CLASS(__T);                                                                   \
        return __T::SafeCastById(id);                                                                 \
    }                                                                                                 \
    uintptr_t SafeCastById(TypeInfoBase::IdType id) const override                                    \
    {                                                                                                 \
        return id == TypeId() ? reinterpret_cast<uintptr_t>(this) : TrySafeCastById<__VA_ARGS__>(id); \
    }                                                                                                 \
    TypeInfoBase::IdType GetTypeId() const override                                                   \
    {                                                                                                 \
        return TypeId();                                                                              \
    }                                                                                                 \
    const char* GetTypeName() const override                                                          \
    {                                                                                                 \
        return TypeName();                                                                            \
    }                                                                                                 \
    DECLARE_CLASS_GET_TYPE_SIZE(classname)

namespace OHOS::Ace {

// Define the base class, inherit this class to support partial 'RTTI' feature.
class TypeInfoBase {
public:
    friend class TypeInfoHelper;
    virtual ~TypeInfoBase() = default;

    using IdType = std::size_t;
    DECLARE_CLASS_TYPE_INFO(TypeInfoBase);

protected:
    virtual uintptr_t SafeCastById(IdType id) const
    {
        return id == TypeId() ? reinterpret_cast<uintptr_t>(this) : 0;
    }

    virtual IdType GetTypeId() const = 0;
    virtual const char* GetTypeName() const = 0;
#ifdef ACE_DEBUG
    virtual size_t GetTypeSize() const { return 0; }
#endif
};

class TypeInfoHelper final {
public:
    TypeInfoHelper() = delete;
    ~TypeInfoHelper() = delete;

    // Convert pointer of instance inherited from 'TypeInfoBase'.
    // Notice: Result SHOULD BE checked with 'nullptr', because 'DynamicCast' might be failed.
    template<class T, class O>
    static T* DynamicCast(O* rawPtr)
    {
        VERIFY_DECLARED_CLASS(T);
        if constexpr(std::is_base_of_v<T, O>) {
            return rawPtr;
        } else {
            return rawPtr != nullptr ? reinterpret_cast<T*>(rawPtr->SafeCastById(T::TypeId())) : nullptr;
        }
    }
    template<class T, class O>
    static const T* DynamicCast(const O* rawPtr)
    {
        VERIFY_DECLARED_CLASS(T);
        if constexpr(std::is_base_of_v<T, O>) {
            return rawPtr;
        } else {
            return rawPtr != nullptr ? reinterpret_cast<const T*>(rawPtr->SafeCastById(T::TypeId())) : nullptr;
        }
    }

    // Get type info by instance.
    template<class T>
    static TypeInfoBase::IdType TypeId(const T* rawPtr)
    {
        return rawPtr != nullptr ? rawPtr->GetTypeId() : 0;
    }
    template<class T, std::enable_if_t<!std::is_pointer_v<T>, bool> = true>
    static TypeInfoBase::IdType TypeId(const T& instance)
    {
        return instance.GetTypeId();
    }
    template<class T>
    static const char* TypeName(const T* rawPtr)
    {
        return rawPtr != nullptr ? rawPtr->GetTypeName() : nullptr;
    }
    template<class T, std::enable_if_t<!std::is_pointer_v<T>, bool> = true>
    static const char* TypeName(const T& instance)
    {
        return instance.GetTypeName();
    }
#ifdef ACE_DEBUG
    template<class T>
    static size_t TypeSize(const T* rawPtr)
    {
        return rawPtr != nullptr ? rawPtr->GetTypeSize() : 0;
    }
    template<class T, std::enable_if_t<!std::is_pointer_v<T>, bool> = true>
    static size_t TypeSize(const T& instance)
    {
        return instance.GetTypeSize();
    }
#endif

    // Get type info by type itself.
    template<class T>
    static TypeInfoBase::IdType TypeId()
    {
        return T::TypeId();
    }
    template<class T>
    static const char* TypeName()
    {
        return T::TypeName();
    }

    // Check whether instance is the specified type
    template<class T, class O>
    static bool InstanceOf(const O* rawPtr)
    {
        if constexpr(std::is_base_of_v<T, O>) {
            return rawPtr != nullptr;
        } else {
            return DynamicCast<T>(rawPtr) != nullptr;
        }
    }
    template<class T, class O, std::enable_if_t<!std::is_pointer_v<O>, bool> = true>
    static bool InstanceOf(const O& instance)
    {
        if constexpr(std::is_base_of_v<T, O>) {
            return true;
        } else {
            return reinterpret_cast<T*>(instance.SafeCastById(T::TypeId())) != nullptr;
        }
    }
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_TYPE_INFO_BASE_H
