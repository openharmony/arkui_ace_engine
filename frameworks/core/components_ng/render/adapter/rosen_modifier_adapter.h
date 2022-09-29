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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_MODIFIER_ADAPTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_MODIFIER_ADAPTER_H

#include <functional>
#include <memory>

#include "include/core/SkCanvas.h"
#include "render_service_client/core/modifier/rs_extended_modifier.h"
#include "render_service_client/core/modifier/rs_modifier.h"
#include "render_service_client/core/ui/rs_node.h"

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {

using RSModifier = Rosen::RSModifier;
using RSNode = Rosen::RSNode;
using RSAnimationTimingProtocol = Rosen::RSAnimationTimingProtocol;
using RSAnimationTimingCurve = Rosen::RSAnimationTimingCurve;
template<typename T>
using RSAnimatableProperty = Rosen::RSAnimatableProperty<T>;
template<typename T>
using RSAnimatableArithmetic = Rosen::RSAnimatableArithmetic<T>;
using RSContentStyleModifier = Rosen::RSContentStyleModifier;
using RSOverlayStyleModifier = Rosen::RSOverlayStyleModifier;
using RSDrawingContext = Rosen::RSDrawingContext;

template<typename T>
class ContentModifierAdapter : public RSContentStyleModifier {
public:
    ContentModifierAdapter() = default;
    ContentModifierAdapter(
        const RefPtr<ContentModifier<T>>& modifier, const std::shared_ptr<RSAnimatableProperty<T>>& property)
        : Rosen::RSContentStyleModifier(property), modifier_(modifier), property_(property)
    {
        if (modifier) {
            modifier->SetUpdateFunc(
                [this](const AnimateConfig& config, const T& propValue) { UpdateModifier(config, propValue); });
        }
    }
    ~ContentModifierAdapter() override = default;

    void Draw(RSDrawingContext& context) const override
    {
        // use dummy deleter avoid delete the SkCanvas by shared_ptr, its owned by context
        std::shared_ptr<SkCanvas> skCanvas { context.canvas, [](SkCanvas*) {} };
        RSCanvas canvas(&skCanvas);
        if (modifier_ && property_) {
            DrawingContext context_ = { canvas, context.width, context.height };
            modifier_->onDraw(context_, property_->Get());
        }
    }

    void UpdateModifier(const AnimateConfig& config, const T& propValue)
    {
        std::shared_ptr<RSAnimatableProperty<T>> property = property_;
        RSAnimationTimingProtocol protocol;
        protocol.SetSpeed(config.speed);
        protocol.SetAutoReverse(config.autoReverse);
        protocol.SetRepeatCount(config.repeatTimes);
        RSNode::Animate(
            protocol, RSAnimationTimingCurve::LINEAR, [property, propValue]() { property->Set(propValue); }, []() {});
    }

private:
    RefPtr<ContentModifier<T>> modifier_;
    std::shared_ptr<RSAnimatableProperty<T>> property_;

    ACE_DISALLOW_COPY_AND_MOVE(ContentModifierAdapter);
};

#define CONVERT_MODIFIER(modifier, srcType, dstType, propertyType)                                             \
    if (AceType::InstanceOf<srcType>(modifier)) {                                                              \
        auto castModifier = AceType::DynamicCast<srcType>(modifier);                                           \
        return std::make_shared<dstType<propertyType>>(                                                        \
            castModifier, std::make_shared<RSAnimatableProperty<propertyType>>(castModifier->GetInitValue())); \
    }

inline std::shared_ptr<RSModifier> ConvertModifier(const RefPtr<Modifier>& modifier)
{
    // should manually add convert type here
    CONVERT_MODIFIER(modifier, ContentModifierFloat, ContentModifierAdapter, float);
    return nullptr;
}

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_MODIFIER_ADAPTER_H
