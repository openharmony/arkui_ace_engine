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

#include "base/geometry/ng/rect_t.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/animation_option.h"
#include "core/components_ng/animation/gradient_arithmetic.h"
#include "core/components_ng/base/linear_vector.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/drawing_forward.h"
#include "core/components_ng/render/modifier_adapter.h"

enum class ThresholdType {
    LAYOUT,  // 0.5f for properties like position, as the difference in properties by 0.5 appears visually unchanged
    COARSE,  // 1.0f / 256.0f
    MEDIUM,  // 1.0f / 1000.0f
    FINE,    // 1.0f / 3072.0f
    COLOR,   // 0.0f
    DEFAULT, // 1.0f / 256.0f
    ZERO,    // 0.0f for noanimatable property
};

enum class PropertyUnit {
    UNKNOWN,
    PIXEL_POSITION, // animatable properties are related to position of the object, the unit is pixels
};

namespace OHOS::Ace::NG {

class ExtensionHandler;

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

using DrawModifierFunc = std::function<void(NG::DrawingContext& drawingContext)>;

class ACE_EXPORT DrawModifier : public virtual AceType {
public:
    DECLARE_ACE_TYPE(DrawModifier, AceType);

public:
    DrawModifierFunc drawBehindFunc;
    DrawModifierFunc drawContentFunc;
    DrawModifierFunc drawFrontFunc;
    DrawModifierFunc drawForegroundFunc;
};

template<typename T>
class NormalProperty : public PropertyBase {
    DECLARE_ACE_TYPE(NormalProperty, PropertyBase);

public:
    explicit NormalProperty(const T& value) : value_(value) {}
    ~NormalProperty() override = default;

    void SetUpCallbacks(std::function<T()>&& getFunc, std::function<void(const T&)>&& setFunc,
        std::function<T()>&& getStageFunc = nullptr)
    {
        getFunc_ = std::move(getFunc);
        setFunc_ =  std::move(setFunc);
        getStageFunc_ =  std::move(getStageFunc);
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

    T GetStagingValue() const
    {
        if (getStageFunc_) {
            return getStageFunc_();
        } else {
            return value_;
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
    std::function<T()> getStageFunc_;
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

#define DECLARE_PROP_TYPED_CLASS(classname, template_class, type)        \
    class classname : public template_class<type> {                      \
        DECLARE_ACE_TYPE(classname, template_class);                     \
                                                                         \
    public:                                                              \
        explicit classname(const type& value) : template_class(value) {} \
        ~classname() override = default;                                 \
        ACE_DISALLOW_COPY_AND_MOVE(classname);                           \
    }

DECLARE_PROP_TYPED_CLASS(PropertyBool, NormalProperty, bool);
DECLARE_PROP_TYPED_CLASS(PropertySizeF, NormalProperty, SizeF);
DECLARE_PROP_TYPED_CLASS(PropertyOffsetF, NormalProperty, OffsetF);
DECLARE_PROP_TYPED_CLASS(PropertyInt, NormalProperty, int32_t);
DECLARE_PROP_TYPED_CLASS(PropertyFloat, NormalProperty, float);
DECLARE_PROP_TYPED_CLASS(PropertyString, NormalProperty, std::string);
DECLARE_PROP_TYPED_CLASS(PropertyU16String, NormalProperty, std::u16string);
DECLARE_PROP_TYPED_CLASS(PropertyColor, NormalProperty, Color);
DECLARE_PROP_TYPED_CLASS(PropertyRectF, NormalProperty, RectF);
DECLARE_PROP_TYPED_CLASS(PropertyVectorFloat, NormalProperty, LinearVector<float>);
DECLARE_PROP_TYPED_CLASS(PropertyCanvasImageModifierWrapper, NormalProperty, CanvasImageModifierWrapper);
DECLARE_PROP_TYPED_CLASS(AnimatablePropertyFloat, AnimatableProperty, float);
DECLARE_PROP_TYPED_CLASS(AnimatablePropertyUint8, AnimatableProperty, uint8_t);
DECLARE_PROP_TYPED_CLASS(AnimatablePropertyColor, AnimatableProperty, LinearColor);
DECLARE_PROP_TYPED_CLASS(AnimatablePropertyVectorFloat, AnimatableProperty, LinearVector<float>);
DECLARE_PROP_TYPED_CLASS(AnimatablePropertyVectorColor, AnimatableProperty, GradientArithmetic);
DECLARE_PROP_TYPED_CLASS(AnimatablePropertyVectorLinearVector, AnimatableProperty, LinearVector<LinearColor>);
DECLARE_PROP_TYPED_CLASS(AnimatablePropertyOffsetF, AnimatableProperty, OffsetF);
DECLARE_PROP_TYPED_CLASS(AnimatablePropertySizeF, AnimatableProperty, SizeF);
DECLARE_PROP_TYPED_CLASS(AnimatableArithmeticProperty, AnimatableProperty, RefPtr<CustomAnimatableArithmetic>);

class OverlayModifier : public Modifier {
    DECLARE_ACE_TYPE(OverlayModifier, Modifier);

public:
    OverlayModifier()
    {
        changeCount_ = MakeRefPtr<PropertyInt>(0);
        AttachProperty(changeCount_);
    };
    ~OverlayModifier() override = default;
    virtual void onDraw(DrawingContext& Context) = 0;
    void Draw(DrawingContext& Context);

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

    void SetExtensionHandler(const RefPtr<ExtensionHandler>& extensionHandler);

    void SetOverlayChange()
    {
        changeCount_->Set(changeCount_->Get() + 1);
    }

private:
    std::vector<RefPtr<PropertyBase>> attachedProperties_;
    RectF rect_;
    RefPtr<PropertyInt> changeCount_;
    ACE_DISALLOW_COPY_AND_MOVE(OverlayModifier);
    WeakPtr<ExtensionHandler> extensionHandler_;
};

class ForegroundModifier : public Modifier {
    DECLARE_ACE_TYPE(ForegroundModifier, Modifier);

public:
    ForegroundModifier()
    {
        changeCount_ = MakeRefPtr<PropertyInt>(0);
        AttachProperty(changeCount_);
    };
    ~ForegroundModifier() override = default;
    virtual void onDraw(DrawingContext& Context) = 0;
    void Draw(DrawingContext& Context);

    void AttachProperty(const RefPtr<PropertyBase>& prop)
    {
        attachedProperties_.push_back(prop);
    }

    const std::vector<RefPtr<PropertyBase>>& GetAttachedProperties() const
    {
        return attachedProperties_;
    }

    const RectF& GetBoundsRect() const
    {
        return rect_;
    }

    void SetBoundsRect(const RectF& rect)
    {
        rect_ = rect;
    }

    void SetExtensionHandler(const RefPtr<ExtensionHandler>& extensionHandler);

    void SetForegroundChange()
    {
        changeCount_->Set(changeCount_->Get() + 1);
    }

private:
    std::vector<RefPtr<PropertyBase>> attachedProperties_;
    RectF rect_;
    RefPtr<PropertyInt> changeCount_;
    ACE_DISALLOW_COPY_AND_MOVE(ForegroundModifier);
    WeakPtr<ExtensionHandler> extensionHandler_;
};

class ContentModifier : public Modifier {
    DECLARE_ACE_TYPE(ContentModifier, Modifier);

public:
    ContentModifier()
    {
        changeCount_ = MakeRefPtr<PropertyInt>(0);
        AttachProperty(changeCount_);
    };
    ~ContentModifier() override = default;
    virtual void onDraw(DrawingContext& Context) = 0;

    void Draw(DrawingContext& Context);

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

    bool GetIsCustomFont() const
    {
        return isCustomFont_;
    }

    void SetContentChange()
    {
        changeCount_->Set(changeCount_->Get() + 1);
    }

    void SetExtensionHandler(const RefPtr<ExtensionHandler>& extensionHandler);

private:
    std::vector<RefPtr<PropertyBase>> attachedProperties_;
    std::optional<RectF> rect_;
    bool isCustomFont_ = false;
    RefPtr<PropertyInt> changeCount_; // use to trigger rerendering
    WeakPtr<ExtensionHandler> extensionHandler_;

    ACE_DISALLOW_COPY_AND_MOVE(ContentModifier);
};

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

using FinishCallback = std::function<void()>;

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

    void SetThresholdType(ThresholdType type);

    void SetPropertyUnit(PropertyUnit unit);

    T Get() const
    {
        auto property = AceType::DynamicCast<S>(GetProperty());
        if (property) {
            return property->Get();
        }
        return {};
    }
    void AnimateWithVelocity(const AnimationOption& option, T value, T velocity,
        const FinishCallback& finishCallback);
private:
    ACE_DISALLOW_COPY_AND_MOVE(NodeAnimatableProperty);
};

using NodeAnimatablePropertyFloat = NodeAnimatableProperty<float, AnimatablePropertyFloat>;
using NodeAnimatableArithmeticProperty =
    NodeAnimatableProperty<RefPtr<CustomAnimatableArithmetic>, AnimatableArithmeticProperty>;
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MODIFIER_H
