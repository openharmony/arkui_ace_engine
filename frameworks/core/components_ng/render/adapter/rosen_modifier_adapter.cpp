/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
#include "core/components_ng/render/adapter/rosen_modifier_adapter.h"
#include "interfaces/inner_api/ace_kit/include/ui/view/draw/modifier.h"

#include "core/components_ng/animation/animatable_arithmetic_proxy.h"
#include "core/animation/native_curve_helper.h"

namespace OHOS::Ace::NG {

std::unordered_map<int32_t, std::shared_ptr<RSModifier>> g_ModifiersMap;
std::mutex g_ModifiersMapLock;

std::shared_ptr<RSModifier> ConvertKitContentModifier(const RefPtr<Kit::Modifier>& modifier)
{
    CHECK_NULL_RETURN(modifier, nullptr);
    auto modifierAdapter = std::make_shared<ContentModifierAdapter>(modifier);
    return modifierAdapter;
}

std::shared_ptr<RSModifier> ConvertContentModifier(const RefPtr<Modifier>& modifier)
{
    CHECK_NULL_RETURN(modifier, nullptr);
    std::lock_guard<std::mutex> lock(g_ModifiersMapLock);
    const auto& iter = g_ModifiersMap.find(modifier->GetId());
    if (iter != g_ModifiersMap.end()) {
        return iter->second;
    }
    auto modifierAdapter = std::make_shared<ContentModifierAdapter>(modifier);
    g_ModifiersMap.emplace(modifier->GetId(), modifierAdapter);
    return modifierAdapter;
}

std::shared_ptr<RSModifier> ConvertOverlayModifier(const RefPtr<Modifier>& modifier)
{
    CHECK_NULL_RETURN(modifier, nullptr);
    std::lock_guard<std::mutex> lock(g_ModifiersMapLock);
    const auto& iter = g_ModifiersMap.find(modifier->GetId());
    if (iter != g_ModifiersMap.end()) {
        return iter->second;
    }
    auto modifierAdapter = std::make_shared<OverlayModifierAdapter>(modifier);
    g_ModifiersMap.emplace(modifier->GetId(), modifierAdapter);
    return modifierAdapter;
}

std::shared_ptr<RSModifier> ConvertForegroundModifier(const RefPtr<Modifier>& modifier)
{
    CHECK_NULL_RETURN(modifier, nullptr);
    std::lock_guard<std::mutex> lock(g_ModifiersMapLock);
    const auto& iter = g_ModifiersMap.find(modifier->GetId());
    if (iter != g_ModifiersMap.end()) {
        return iter->second;
    }
    auto modifierAdapter = std::make_shared<ForegroundModifierAdapter>(modifier);
    g_ModifiersMap.emplace(modifier->GetId(), modifierAdapter);
    return modifierAdapter;
}

void ModifierAdapter::RemoveModifier(int32_t modifierId)
{
    std::lock_guard<std::mutex> lock(g_ModifiersMapLock);
    g_ModifiersMap.erase(modifierId);
}

void ContentModifierAdapter::Draw(RSDrawingContext& context) const
{
    if (kitModifier_) {
        Kit::DrawingContext drawingContext = { context.canvas, context.width, context.height };
        kitModifier_->OnDraw(&drawingContext);
        return;
    }
    // use dummy deleter avoid delete the SkCanvas by shared_ptr, its owned by context
    CHECK_NULL_VOID(context.canvas);
    auto modifier = modifier_.Upgrade();
    CHECK_NULL_VOID(modifier);
    DrawingContext context_ = { *context.canvas, context.width, context.height };
    modifier->Draw(context_);
}

#define CONVERT_PROP(prop, srcType, propType)                                      \
    if (AceType::InstanceOf<srcType>(prop)) {                                      \
        auto castProp = AceType::DynamicCast<srcType>(prop);                       \
        auto rsProp = std::make_shared<RSProperty<propType>>(castProp->Get());     \
        castProp->SetUpCallbacks([rsProp]() -> propType { return rsProp->Get(); }, \
            [rsProp](const propType& value) { rsProp->Set(value); },               \
            [rsProp]() -> propType { return rsProp->Get(); });                     \
        return rsProp;                                                             \
    }

#define CONVERT_ANIMATABLE_PROP(prop, srcType, propType)                                 \
    if (AceType::InstanceOf<srcType>(prop)) {                                            \
        auto castProp = AceType::DynamicCast<srcType>(prop);                             \
        auto rsProp = std::make_shared<RSAnimatableProperty<propType>>(castProp->Get()); \
        castProp->SetUpCallbacks([rsProp]() -> propType { return rsProp->Get(); },       \
            [rsProp](const propType& value) { rsProp->Set(value); },                     \
            [rsProp]() -> propType { return rsProp->GetStagingValue(); });               \
        rsProp->SetUpdateCallback(castProp->GetUpdateCallback());                        \
        return rsProp;                                                                   \
    }

inline std::shared_ptr<RSPropertyBase> ConvertToRSProperty(const RefPtr<PropertyBase>& property)
{
    // should manually add convert type here
    CONVERT_PROP(property, PropertyBool, bool);
    CONVERT_PROP(property, PropertySizeF, SizeF);
    CONVERT_PROP(property, PropertyOffsetF, OffsetF);
    CONVERT_PROP(property, PropertyInt, int32_t);
    CONVERT_PROP(property, PropertyFloat, float);
    CONVERT_PROP(property, PropertyString, std::string);
    CONVERT_PROP(property, PropertyColor, Color);
    CONVERT_PROP(property, PropertyRectF, RectF);
    CONVERT_PROP(property, PropertyVectorFloat, LinearVector<float>);
    CONVERT_PROP(property, PropertyCanvasImageModifierWrapper, CanvasImageModifierWrapper);
    CONVERT_ANIMATABLE_PROP(property, AnimatablePropertyOffsetF, OffsetF);
    CONVERT_ANIMATABLE_PROP(property, AnimatablePropertyUint8, uint8_t);
    CONVERT_ANIMATABLE_PROP(property, AnimatablePropertyFloat, float);
    CONVERT_ANIMATABLE_PROP(property, AnimatablePropertyColor, LinearColor);
    CONVERT_ANIMATABLE_PROP(property, AnimatablePropertyVectorColor, GradientArithmetic);
    CONVERT_ANIMATABLE_PROP(property, AnimatablePropertyVectorFloat, LinearVector<float>);
    CONVERT_ANIMATABLE_PROP(property, AnimatablePropertySizeF, SizeF);

    if (AceType::InstanceOf<AnimatableArithmeticProperty>(property)) {
        auto castProp = AceType::DynamicCast<AnimatableArithmeticProperty>(property);
        if (!castProp && !castProp->Get()) {
            LOGE("ConvertToRSProperty: Failed converting to RSProperty - AnimatableArithmeticProperty is null");
            return nullptr;
        }
        AnimatableArithmeticProxy proxy(castProp->Get());
        auto rsProp = std::make_shared<RSAnimatableProperty<AnimatableArithmeticProxy>>(proxy);
        auto getter = [rsProp]() -> RefPtr<CustomAnimatableArithmetic> { return rsProp->Get().GetObject(); };
        auto setter = [rsProp](const RefPtr<CustomAnimatableArithmetic>& value) {
            rsProp->Set(AnimatableArithmeticProxy(value));
        };
        castProp->SetUpCallbacks(getter, setter);
        if (castProp->GetUpdateCallback()) {
            rsProp->SetUpdateCallback(
                [cb = castProp->GetUpdateCallback()](const AnimatableArithmeticProxy& value) {
                    cb(value.GetObject());
                });
        }
        return rsProp;
    }

    LOGE("ConvertToRSProperty failed!");
    return nullptr;
}

void ContentModifierAdapter::AttachProperties()
{
    auto modifier = modifier_.Upgrade();
    if (!hasAttached_ && modifier && modifier->GetAttachedProperties().size()) {
        for (const auto& property : modifier->GetAttachedProperties()) {
            auto rsProperty = ConvertToRSProperty(property);
            AttachProperty(rsProperty);
        }
        hasAttached_ = true;
    }
}

void OverlayModifierAdapter::Draw(RSDrawingContext& context) const
{
    // use dummy deleter avoid delete the SkCanvas by shared_ptr, its owned by context
    CHECK_NULL_VOID(context.canvas);
    auto modifier = modifier_.Upgrade();
    CHECK_NULL_VOID(modifier);
    DrawingContext context_ = { *context.canvas, context.width, context.height };
    modifier->Draw(context_);
}

void OverlayModifierAdapter::AttachProperties()
{
    auto modifier = modifier_.Upgrade();
    if (!hasAttached_ && modifier && modifier->GetAttachedProperties().size()) {
        for (const auto& property : modifier->GetAttachedProperties()) {
            auto rsProperty = ConvertToRSProperty(property);
            AttachProperty(rsProperty);
        }
        hasAttached_ = true;
    }
}

void ForegroundModifierAdapter::Draw(RSDrawingContext& context) const
{
    // use dummy deleter avoid delete the SkCanvas by shared_ptr, its owned by context
    CHECK_NULL_VOID(context.canvas);
    auto modifier = modifier_.Upgrade();
    CHECK_NULL_VOID(modifier);
    DrawingContext context_ = { *context.canvas, context.width, context.height };
    modifier->Draw(context_);
}

void ForegroundModifierAdapter::AttachProperties()
{
    auto modifier = modifier_.Upgrade();
    if (!hasAttached_ && modifier && modifier->GetAttachedProperties().size()) {
        for (const auto& property : modifier->GetAttachedProperties()) {
            auto rsProperty = ConvertToRSProperty(property);
            AttachProperty(rsProperty);
        }
        hasAttached_ = true;
    }
}

void RSNodeModifierImpl::AddProperty(const RefPtr<PropertyBase>& property)
{
    if (!attachedProperty_) {
        auto rsProperty = ConvertToRSProperty(property);
        AttachProperty(rsProperty);
        attachedProperty_ = rsProperty;
    }
}

namespace {
Rosen::FinishCallbackType ToAnimationFinishCallbackType(const FinishCallbackType finishCallbackType)
{
    if (finishCallbackType == FinishCallbackType::LOGICALLY) {
        return Rosen::FinishCallbackType::LOGICALLY;
    } else if (finishCallbackType == FinishCallbackType::REMOVED) {
        return Rosen::FinishCallbackType::TIME_SENSITIVE;
    } else {
        return Rosen::FinishCallbackType::TIME_SENSITIVE;
    }
}
Rosen::RSAnimationTimingProtocol OptionToTimingProtocol(const AnimationOption& option)
{
    Rosen::RSAnimationTimingProtocol timingProtocol;
    timingProtocol.SetDuration(option.GetDuration());
    timingProtocol.SetStartDelay(option.GetDelay());
    timingProtocol.SetSpeed(option.GetTempo());
    timingProtocol.SetRepeatCount(option.GetIteration());
    timingProtocol.SetDirection(option.GetAnimationDirection() == AnimationDirection::NORMAL ||
                                option.GetAnimationDirection() == AnimationDirection::ALTERNATE);
    timingProtocol.SetAutoReverse(option.GetAnimationDirection() == AnimationDirection::ALTERNATE ||
                                  option.GetAnimationDirection() == AnimationDirection::ALTERNATE_REVERSE);
    timingProtocol.SetFillMode(static_cast<Rosen::FillMode>(option.GetFillMode()));
    timingProtocol.SetFinishCallbackType(ToAnimationFinishCallbackType(option.GetFinishCallbackType()));
    return timingProtocol;
}
} // namespace

template<>
void NodeAnimatableProperty<float, AnimatablePropertyFloat>::AnimateWithVelocity(const AnimationOption& option,
    float value, float velocity, const FinishCallback& finishCallback)
{
    const auto& timingProtocol = OptionToTimingProtocol(option);
    auto targetValue = std::make_shared<RSAnimatableProperty<float>>(value);
    auto initialVelocity = std::make_shared<RSAnimatableProperty<float>>(velocity);
    auto modify = std::static_pointer_cast<RSNodeModifierImpl>(GetModifyImpl());
    if (modify) {
        auto property = std::static_pointer_cast<RSAnimatableProperty<float>>(modify->GetProperty());
        if (property) {
            property->AnimateWithInitialVelocity(timingProtocol, NativeCurveHelper::ToNativeCurve(option.GetCurve()),
                targetValue, initialVelocity, finishCallback, nullptr);
        }
    }
}

template<>
void NodeAnimatableProperty<float, AnimatablePropertyFloat>::SetThresholdType(ThresholdType type)
{
    auto modify = std::static_pointer_cast<RSNodeModifierImpl>(GetModifyImpl());
    CHECK_NULL_VOID(modify);
    auto property = std::static_pointer_cast<RSPropertyBase>(modify->GetProperty());
    CHECK_NULL_VOID(property);
    property->SetThresholdType(static_cast<Rosen::ThresholdType>(type));
}

template<>
void NodeAnimatableProperty<float, AnimatablePropertyFloat>::SetPropertyUnit(PropertyUnit unit)
{
    auto modify = std::static_pointer_cast<RSNodeModifierImpl>(GetModifyImpl());
    CHECK_NULL_VOID(modify);
    auto property = std::static_pointer_cast<RSAnimatableProperty<float>>(modify->GetProperty());
    CHECK_NULL_VOID(property);
    property->SetPropertyUnit(static_cast<Rosen::RSPropertyUnit>(unit));
}
} // namespace OHOS::Ace::NG
