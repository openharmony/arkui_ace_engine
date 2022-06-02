/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MODIFIERS_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MODIFIERS_MODIFIER_H

#include <functional>
#include <optional>

#include "base/log/log.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"

#define ACE_DEFINE_MODIFIER_TASK(Target, Base, Type)                      \
    do {                                                                  \
        if (!HasValue()) {                                                \
            return;                                                       \
        }                                                                 \
        auto task = [value = GetValue()](Base* prop##Base) {              \
            auto prop##Target = AceType::DynamicCast<Target>(prop##Base); \
            if (prop##Target) {                                           \
                prop##Target->Update##Type(value);                        \
            }                                                             \
        };                                                                \
        SetModifierTask(std::move(task));                                 \
    } while (false)

namespace OHOS::Ace::NG {
// Modifier base class that provides the underlying operation of property methods, which can be encapsulated by
// multithreaded tasks.
template<typename Target>
class Modifier {
public:
    using ModifierTask = std::function<void(Target* target)>;

    Modifier() = default;
    virtual ~Modifier() = default;

    void FlushModify(Target* target) const
    {
        if (target == nullptr) {
            return;
        }
        if (modifierTask_) {
            modifierTask_(target);
        }
    }

    void SetModifierTask(ModifierTask&& task)
    {
        modifierTask_ = std::move(task);
    }

protected:
    ModifierTask modifierTask_;
};

template<typename Property, typename Target>
class PropertyModifier : public Modifier<Target> {
public:
    PropertyModifier(const Property& value) : value_(value) {}
    ~PropertyModifier() override = default;

    bool HasValue() const
    {
        return value_.has_value();
    }

    // Must call HasValue before.
    const Property& GetValue() const
    {
        ACE_DCHECK(value_.has_value());
        return value_.value();
    }

private:
    std::optional<Property> value_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MODIFIERS_MODIFIER_H