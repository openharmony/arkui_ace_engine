/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MODIFIER_H

#include <atomic>
#include <cstdint>
#include <functional>
#include <optional>
#include <vector>

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/animation/gradient_arithmetic.h"
#include "core/components_ng/base/linear_vector.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/drawing_forward.h"
#include "core/components_ng/render/modifier_adapter.h"

namespace OHOS::Ace::NG {
class ACE_FORCE_EXPORT Modifier : public virtual AceType {
    DECLARE_ACE_TYPE(Modifier, AceType);

public:
    Modifier();
    ~Modifier() override
    {
        ModifierAdapter::RemoveModifier(id_);
    }

    int32_t GetId() const
    {
        return id_;
    }

private:
    int32_t id_ = 0;
    ACE_DISALLOW_COPY_AND_MOVE(Modifier);
};

class PropertyBase : public virtual AceType {
    DECLARE_ACE_TYPE(PropertyBase, AceType);

public:
    PropertyBase() = default;
    ~PropertyBase() override = default;

private:
    ACE_DISALLOW_COPY_AND_MOVE(PropertyBase);
};

struct DrawingContext {
    RSCanvas& canvas;
    float width = 0;
    float height = 0;
};

template<typename T>
class NormalProperty : public PropertyBase {
    DECLARE_ACE_TYPE(NormalProperty, PropertyBase);

public:
    explicit NormalProperty(const T& value) : value_(value) {}
    ~NormalProperty() override = default;

    void SetUpCallbacks(std::function<T()>&& getFunc, std::function<void(const T&)>&& setFunc)
    {
        getFunc_ = getFunc;
        setFunc_ = setFunc;
    }

    T Get()
    {
        if (getFunc_) {
            return getFunc_();
        } else {
            return value_;
        }
    }

    void Set(const T& value)
    {
        if (setFunc_) {
            setFunc_(value);
        } else {
            value_ = value;
        }
    }

    void SetUpdateCallback(std::function<void(const T&)>&& callback)
    {
        updateCallback_ = std::move(callback);
    }

    std::function<void(const T&)> GetUpdateCallback() const
    {
        return updateCallback_;
    }

private:
    T value_;
    std::function<T()> getFunc_;
    std::function<void(const T&)> setFunc_;
    std::function<void(const T&)> updateCallback_;
    ACE_DISALLOW_COPY_AND_MOVE(NormalProperty);
};

template<typename T>
class AnimatableProperty : public NormalProperty<T> {
    DECLARE_ACE_TYPE(AnimatableProperty, NormalProperty<T>);

public:
    explicit AnimatableProperty(const T& value) : NormalProperty<T>(value) {}
    ~AnimatableProperty() override = default;
private:
    ACE_DISALLOW_COPY_AND_MOVE(AnimatableProperty);
};

class ContentModifier : public Modifier {
    DECLARE_ACE_TYPE(ContentModifier, Modifier);

public:
    ContentModifier() = default;
    ~ContentModifier() override = default;
    virtual void onDraw(DrawingContext& Context) = 0;

    void AttachProperty(const RefPtr<PropertyBase>& prop)
    {
        attachedProperties_.push_back(prop);
    }

    const std::vector<RefPtr<PropertyBase>>& GetAttachedProperties()
    {
        return attachedProperties_;
    }

    const std::optional<RectF>& GetBoundsRect()
    {
        return rect_;
    }

    void SetBoundsRect(const std::optional<RectF>& rect)
    {
        rect_ = rect;
    }

    void SetIsCustomFont(bool isCustomFont)
    {
        isCustomFont_ = isCustomFont;
    }

    bool GetIsCustomFont()
    {
        return isCustomFont_;
    }

private:
    std::vector<RefPtr<PropertyBase>> attachedProperties_;
    std::optional<RectF> rect_;
    bool isCustomFont_ = false;
    ACE_DISALLOW_COPY_AND_MOVE(ContentModifier);
};

class OverlayModifier : public Modifier {
    DECLARE_ACE_TYPE(OverlayModifier, Modifier);

public:
    OverlayModifier() = default;
    ~OverlayModifier() override = default;
    virtual void onDraw(DrawingContext& Context) = 0;

    void AttachProperty(const RefPtr<PropertyBase>& prop)
    {
        attachedProperties_.push_back(prop);
    }

    const std::vector<RefPtr<PropertyBase>>& GetAttachedProperties()
    {
        return attachedProperties_;
    }

    const RectF& GetBoundsRect()
    {
        return rect_;
    }

    void SetBoundsRect(const RectF& rect)
    {
        rect_ = rect;
    }

private:
    std::vector<RefPtr<PropertyBase>> attachedProperties_;
    RectF rect_;
    ACE_DISALLOW_COPY_AND_MOVE(OverlayModifier);
};

#define DECLARE_PROP_TYPED_CLASS(classname, template_class, type)        \
    class classname : public template_class<type> {                      \
        DECLARE_ACE_TYPE(classname, template_class);                     \
                                                                         \
    public:                                                              \
        explicit classname(const type& value) : template_class(value) {} \
        ~classname() override = default;                                 \
        ACE_DISALLOW_COPY_AND_MOVE(classname);                           \
    };

DECLARE_PROP_TYPED_CLASS(PropertyBool, NormalProperty, bool);
DECLARE_PROP_TYPED_CLASS(PropertySizeF, NormalProperty, SizeF);
DECLARE_PROP_TYPED_CLASS(PropertyOffsetF, NormalProperty, OffsetF);
DECLARE_PROP_TYPED_CLASS(PropertyInt, NormalProperty, int32_t);
DECLARE_PROP_TYPED_CLASS(PropertyFloat, NormalProperty, float);
DECLARE_PROP_TYPED_CLASS(PropertyString, NormalProperty, std::string);
DECLARE_PROP_TYPED_CLASS(PropertyColor, NormalProperty, Color);
DECLARE_PROP_TYPED_CLASS(AnimatablePropertyFloat, AnimatableProperty, float);
DECLARE_PROP_TYPED_CLASS(AnimatablePropertyUint8, AnimatableProperty, uint8_t);
DECLARE_PROP_TYPED_CLASS(AnimatablePropertyColor, AnimatableProperty, LinearColor);
DECLARE_PROP_TYPED_CLASS(AnimatablePropertyVectorFloat, AnimatableProperty, LinearVector<float>);
DECLARE_PROP_TYPED_CLASS(AnimatablePropertyVectorColor, AnimatableProperty, GradientArithmetic);
DECLARE_PROP_TYPED_CLASS(AnimatablePropertyOffsetF, AnimatableProperty, OffsetF);
DECLARE_PROP_TYPED_CLASS(AnimatablePropertySizeF, AnimatableProperty, SizeF);
DECLARE_PROP_TYPED_CLASS(AnimatableArithmeticProperty, AnimatableProperty, RefPtr<CustomAnimatableArithmetic>);

class ModifierImpl {
};

class NodeAnimatablePropertyBase : public AceType {
    DECLARE_ACE_TYPE(NodeAnimatablePropertyBase, AceType);

public:
    NodeAnimatablePropertyBase() = default;
    ~NodeAnimatablePropertyBase() override = default;

    const std::shared_ptr<ModifierImpl>& GetModifyImpl() const
    {
        return modifyImpl_;
    }

    void SetModifyImpl(const std::shared_ptr<ModifierImpl>& impl)
    {
        modifyImpl_ = impl;
    }

    const RefPtr<PropertyBase>& GetProperty() const
    {
        return property_;
    }

    void SetProperty(const RefPtr<PropertyBase>& property)
    {
        property_ = property;
    }

private:
    std::shared_ptr<ModifierImpl> modifyImpl_;
    RefPtr<PropertyBase> property_;

    ACE_DISALLOW_COPY_AND_MOVE(NodeAnimatablePropertyBase);
};

template<typename T, typename S>
class NodeAnimatableProperty : public NodeAnimatablePropertyBase {
    DECLARE_ACE_TYPE(NodeAnimatableProperty, NodeAnimatablePropertyBase);

public:
    NodeAnimatableProperty(const T& value, std::function<void(const T&)>&& updateCallback)
    {
        auto property = AceType::MakeRefPtr<S>(value);
        property->SetUpdateCallback(std::move(updateCallback));
        SetProperty(property);
    }
    ~NodeAnimatableProperty() override = default;

    void Set(const T& value)
    {
        auto property = AceType::DynamicCast<S>(GetProperty());
        if (property) {
            property->Set(value);
        }
    }

    T Get() const
    {
        auto property = AceType::DynamicCast<S>(GetProperty());
        if (property) {
            return property->Get();
        }
        return {};
    }
private:
    ACE_DISALLOW_COPY_AND_MOVE(NodeAnimatableProperty);
};

using NodeAnimatablePropertyFloat = NodeAnimatableProperty<float, AnimatablePropertyFloat>;
using NodeAnimatableArithmeticProperty =
    NodeAnimatableProperty<RefPtr<CustomAnimatableArithmetic>, AnimatableArithmeticProperty>;
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MODIFIER_H
