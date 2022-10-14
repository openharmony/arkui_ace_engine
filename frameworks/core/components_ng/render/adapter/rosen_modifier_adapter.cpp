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
#include "core/components_ng/render/adapter/rosen_modifier_adapter.h"

#include <mutex>
#include <unordered_map>

#include "base/utils/utils.h"
#include "core/components_ng/render/modifier_adapter.h"

namespace OHOS::Ace::NG {

std::unordered_map<int32_t, std::shared_ptr<RSModifier>> g_ModifiersMap;
std::mutex g_ModifiersMapLock;

std::shared_ptr<RSModifier> ConvertModifier(const RefPtr<Modifier>& modifier)
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

void ModifierAdapter::RemoveModifier(int32_t modifierId)
{
    std::lock_guard<std::mutex> lock(g_ModifiersMapLock);
    g_ModifiersMap.erase(modifierId);
}

void ContentModifierAdapter::Draw(RSDrawingContext& context) const
{
    // use dummy deleter avoid delete the SkCanvas by shared_ptr, its owned by context
    std::shared_ptr<SkCanvas> skCanvas { context.canvas, [](SkCanvas*) {} };
    RSCanvas canvas(&skCanvas);
    if (modifier_) {
        DrawingContext context_ = { canvas, context.width, context.height };
        modifier_->onDraw(context_);
    }
}

template<typename T>
void UpdateRSPropWithAnimation(
    const std::shared_ptr<RSAnimatableProperty<T>>& rsProp, const AnimateConfig& config, const T& value)
{
    RSAnimationTimingProtocol protocol;
    protocol.SetSpeed(config.speed);
    protocol.SetAutoReverse(config.autoReverse);
    protocol.SetRepeatCount(config.repeatTimes);
    RSNode::Animate(
        protocol, RSAnimationTimingCurve::LINEAR, [rsProp, value]() { 
            rsProp->Set(value);
        });
}

#define CONVERT_PROPS(prop, srcType, propType)                                                    \
    if (AceType::InstanceOf<srcType>(prop)) {                                                     \
        auto castProp = AceType::DynamicCast<srcType>(prop);                                      \
        auto rsProp = std::make_shared<RSAnimatableProperty<propType>>(castProp->Get());          \
        castProp->SetUpCallbacks([rsProp]() -> propType { return rsProp->Get(); },                \
            [rsProp](const propType& value) { rsProp->Set(value); },                              \
            [rsProp](const AnimateConfig& config, const propType& value) {                        \
                UpdateRSPropWithAnimation(rsProp, config, value);                                 \
            });                                                                                   \
        return rsProp;                                                                            \
    }

inline std::shared_ptr<RSPropertyBase> ConvertToRSProperty(const RefPtr<AnimatablePropBase>& prop)
{
    // should manually add convert type here
    CONVERT_PROPS(prop, AnimatablePropFloat, float);
    return nullptr;
}

inline std::shared_ptr<RSPropertyBase> ConvertToRSPropertyColor(const RefPtr<AnimatablePropBase>& prop)
{
    // should manually add convert type here
    CONVERT_PROPS(prop, AnimatableProp<Color>, Color);
    return nullptr;
}

void ContentModifierAdapter::AttachProperties()
{
    if (!attachedProperties_.size() && modifier_) {
        auto propFloat = modifier_->GetAttachedProps()[0];
        auto rsPropFloat = ConvertToRSProperty(propFloat);
        AttachProperty(rsPropFloat);
        attachedProperties_.emplace_back(rsPropFloat);

        auto propColor = modifier_->GetAttachedProps()[1];
        auto rsPropColor = ConvertToRSPropertyColor(propColor);
        AttachProperty(rsPropColor);
        attachedProperties_.emplace_back(rsPropColor);
    }
}

} // namespace OHOS::Ace::NG