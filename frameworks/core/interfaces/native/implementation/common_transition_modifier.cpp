/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/pattern/stage/page_transition_effect.h"
#include "core/components_ng/pattern/stage/page_transition_model_ng.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

using namespace OHOS::Ace::NG::Converter;

namespace OHOS::Ace::NG {
namespace Converter {
template<>
void AssignCast(std::optional<SlideEffect>& dst, const Ark_SlideEffect& src)
{
    switch (src) {
        case ARK_SLIDE_EFFECT_LEFT: dst = SlideEffect::LEFT; break;
        case ARK_SLIDE_EFFECT_RIGHT: dst = SlideEffect::RIGHT; break;
        case ARK_SLIDE_EFFECT_TOP: dst = SlideEffect::TOP; break;
        case ARK_SLIDE_EFFECT_BOTTOM: dst = SlideEffect::BOTTOM; break;
        case ARK_SLIDE_EFFECT_START: dst = SlideEffect::START; break;
        case ARK_SLIDE_EFFECT_END: dst = SlideEffect::END; break;
        default: LOGE("Unexpected enum value in Ark_SlideEffect: %{public}d", src);
    }
}
} // namespace Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CommonTransitionModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return nullptr;
}
void SlideImpl(Ark_NativePointer node,
               Ark_SlideEffect value)
{
    auto transition = reinterpret_cast<PageTransitionEffect *>(node);
    CHECK_NULL_VOID(transition);
    auto convValue = Converter::OptConvert<SlideEffect>(value);
    PageTransitionModelNG::SetSlideEffect(transition, convValue);
}
void TranslateImpl(Ark_NativePointer node,
                   const Ark_TranslateOptions* value)
{
    auto transition = reinterpret_cast<PageTransitionEffect *>(node);
    CHECK_NULL_VOID(transition);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<TranslateOptions>(*value);
    PageTransitionModelNG::SetTranslateEffect(transition, convValue);
}
void ScaleImpl(Ark_NativePointer node,
               const Ark_ScaleOptions* value)
{
    auto transition = reinterpret_cast<PageTransitionEffect *>(node);
    CHECK_NULL_VOID(transition);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<ScaleOpt>(*value);
    ScaleOptions option;
    option.centerX = convValue.centerX ? convValue.centerX.value() : 0.5_pct;
    option.centerY = convValue.centerY ? convValue.centerY.value() : 0.5_pct;
    if (convValue.x) {
        option.xScale = convValue.x.value();
    }
    if (convValue.y) {
        option.yScale = convValue.y.value();
    }
    if (convValue.z) {
        option.zScale = convValue.z.value();
    }
    PageTransitionModelNG::SetScaleEffect(transition, option);
}
void OpacityImpl(Ark_NativePointer node,
                 const Ark_Number* value)
{
    auto transition = reinterpret_cast<PageTransitionEffect *>(node);
    CHECK_NULL_VOID(transition);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<float>(*value);
    PageTransitionModelNG::SetOpacityEffect(transition, convValue);
}
} // CommonTransitionModifier
const GENERATED_ArkUICommonTransitionModifier* GetCommonTransitionModifier()
{
    static const GENERATED_ArkUICommonTransitionModifier ArkUICommonTransitionModifierImpl {
        CommonTransitionModifier::ConstructImpl,
        CommonTransitionModifier::SlideImpl,
        CommonTransitionModifier::TranslateImpl,
        CommonTransitionModifier::ScaleImpl,
        CommonTransitionModifier::OpacityImpl,
    };
    return &ArkUICommonTransitionModifierImpl;
}

}
