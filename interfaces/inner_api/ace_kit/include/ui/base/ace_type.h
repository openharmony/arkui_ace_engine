/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_ACE_TYPE_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_ACE_TYPE_H

#include "ui/base/referenced.h"

#include "ui/base/type_info_base.h"

/**
 * Example:
 *     class BaseA : public virtual AceType {
 *         DECLARE_ACE_TYPE(BaseA, AceType);
 *     };
 *
 *     class BaseB : public virtual AceType {
 *         DECLARE_ACE_TYPE(BaseB, AceType);
 *     };
 *
 *     class BaseC : public BaseA, public BaseB {
 *         DECLARE_ACE_TYPE(BaseC, BaseA, BaseB);
 *     };
 */
// Integrate it into class declaration to support 'DynamicCast'.
#define DECLARE_ACE_TYPE(...); DECLARE_RELATIONSHIP_OF_CLASSES(__VA_ARGS__) \
friend class Referenced;

namespace OHOS::Ace {
    
enum class ColorMode : int32_t {
    LIGHT = 0,
    DARK,
    COLOR_MODE_UNDEFINED,
};

// Inherit 'AceType' to manager pointers using 'RefPtr', 'WeakPtr' and 'AceType::DynamicCast'.
class AceType : public virtual TypeInfoBase, public virtual Referenced {
    DECLARE_ACE_TYPE(AceType, TypeInfoBase);

public:
    ~AceType() override = default;

    template<class T, class O>
    static T* DynamicCast(O* rawPtr)
    {
        return TypeInfoHelper::DynamicCast<T>(rawPtr);
    }
    template<class T, class O>
    static const T* DynamicCast(const O* rawPtr)
    {
        return TypeInfoHelper::DynamicCast<T>(rawPtr);
    }
    template<class T, class O>
    static RefPtr<T> DynamicCast(const RefPtr<O>& ptr)
    {
        return Claim(DynamicCast<T>(RawPtr(ptr)));
    }
    template<class T, class O>
    static RefPtr<T> DynamicCast(RefPtr<O>&& ptr)
    {
        return Transfer<T>(ptr);
    }
    template<class T, class O>
    static WeakPtr<T> DynamicCast(const WeakPtr<O>& weak)
    {
        auto ptr = weak.Upgrade();
        return WeakClaim(DynamicCast<T>(RawPtr(ptr)));
    }

    // Get type info by instance.
    template<class T>
    static AceType::IdType TypeId(const T* rawPtr)
    {
        return TypeInfoHelper::TypeId(rawPtr);
    }
    template<class T>
    static AceType::IdType TypeId(const RefPtr<T>& ptr)
    {
        return TypeId(AceType::RawPtr(ptr));
    }
    template<class T, std::enable_if_t<!std::is_pointer_v<T>, bool> = true>
    static AceType::IdType TypeId(const T& instance)
    {
        return TypeInfoHelper::TypeId(instance);
    }
    template<class T>
    static const char* TypeName(const T* rawPtr)
    {
        return TypeInfoHelper::TypeName(rawPtr);
    }
    template<class T>
    static const char* TypeName(const RefPtr<T>& ptr)
    {
        return TypeName(AceType::RawPtr(ptr));
    }
    template<class T, std::enable_if_t<!std::is_pointer_v<T>, bool> = true>
    static const char* TypeName(const T& instance)
    {
        return TypeInfoHelper::TypeName(instance);
    }

    // Get type info by type itself.
    template<class T>
    static AceType::IdType TypeId()
    {
        return TypeInfoHelper::TypeId<T>();
    }
    template<class T>
    static const char* TypeName()
    {
        return TypeInfoHelper::TypeName<T>();
    }

    // Check whether instance is the specified type
    template<class T, class O>
    static bool InstanceOf(const O* rawPtr)
    {
        return TypeInfoHelper::InstanceOf<T>(rawPtr);
    }
    template<class T, class O, std::enable_if_t<!std::is_pointer_v<O>, bool> = true>
    static bool InstanceOf(const O& instance)
    {
        return TypeInfoHelper::InstanceOf<T>(instance);
    }
    template<class T, class O>
    static bool InstanceOf(const RefPtr<O>& ptr)
    {
        return TypeInfoHelper::InstanceOf<T>(RawPtr(ptr));
    }

protected:
    AceType() = default;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_ACE_TYPE_H
