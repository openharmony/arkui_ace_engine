/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RatingModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // RatingModifier
namespace RatingInterfaceModifier {
void SetRatingOptionsImpl(Ark_NativePointer node,
                          const Opt_RatingOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = options ? Converter::OptConvert<type>(*options) : std::nullopt;
    //RatingModelNG::SetSetRatingOptions(frameNode, convValue);
}
} // RatingInterfaceModifier
namespace RatingAttributeModifier {
void Stars0Impl(Ark_NativePointer node,
                const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //RatingModelNG::SetStars0(frameNode, convValue);
}
void Stars1Impl(Ark_NativePointer node,
                const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RatingModelNG::SetStars1(frameNode, convValue);
}
void StepSize0Impl(Ark_NativePointer node,
                   const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //RatingModelNG::SetStepSize0(frameNode, convValue);
}
void StepSize1Impl(Ark_NativePointer node,
                   const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RatingModelNG::SetStepSize1(frameNode, convValue);
}
void StarStyle0Impl(Ark_NativePointer node,
                    const Ark_StarStyleOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //RatingModelNG::SetStarStyle0(frameNode, convValue);
}
void StarStyle1Impl(Ark_NativePointer node,
                    const Opt_StarStyleOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RatingModelNG::SetStarStyle1(frameNode, convValue);
}
void OnChange0Impl(Ark_NativePointer node,
                   const Callback_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //RatingModelNG::SetOnChange0(frameNode, convValue);
}
void OnChange1Impl(Ark_NativePointer node,
                   const Opt_OnRatingChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RatingModelNG::SetOnChange1(frameNode, convValue);
}
void ContentModifier0Impl(Ark_NativePointer node,
                          const Ark_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //RatingModelNG::SetContentModifier0(frameNode, convValue);
}
void ContentModifier1Impl(Ark_NativePointer node,
                          const Opt_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RatingModelNG::SetContentModifier1(frameNode, convValue);
}
void _onChangeEvent_ratingImpl(Ark_NativePointer node,
                               const Callback_Number_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    //auto convValue = Converter::OptConvert<type_name>(*callback);
    //RatingModelNG::Set_onChangeEvent_rating(frameNode, convValue);
}
} // RatingAttributeModifier
const GENERATED_ArkUIRatingModifier* GetRatingModifier()
{
    static const GENERATED_ArkUIRatingModifier ArkUIRatingModifierImpl {
        RatingModifier::ConstructImpl,
        RatingInterfaceModifier::SetRatingOptionsImpl,
        RatingAttributeModifier::Stars0Impl,
        RatingAttributeModifier::Stars1Impl,
        RatingAttributeModifier::StepSize0Impl,
        RatingAttributeModifier::StepSize1Impl,
        RatingAttributeModifier::StarStyle0Impl,
        RatingAttributeModifier::StarStyle1Impl,
        RatingAttributeModifier::OnChange0Impl,
        RatingAttributeModifier::OnChange1Impl,
        RatingAttributeModifier::ContentModifier0Impl,
        RatingAttributeModifier::ContentModifier1Impl,
        RatingAttributeModifier::_onChangeEvent_ratingImpl,
    };
    return &ArkUIRatingModifierImpl;
}

}
