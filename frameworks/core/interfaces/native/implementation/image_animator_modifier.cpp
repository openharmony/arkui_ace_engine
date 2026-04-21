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
#include "core/interfaces/native/utility/validators.h"
#include "core/components_ng/pattern/image_animator/image_animator_model_ng.h"
#include "core/components_ng/pattern/image_animator/image_animator_model_static.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::Converter {
template<>
void AssignCast(std::optional<int32_t>& dst, const Ark_AnimationStatus& src)
{
    switch (src) {
        case Ark_AnimationStatus::ARK_ANIMATION_STATUS_INITIAL: dst = static_cast<int32_t>(src); break;
        case Ark_AnimationStatus::ARK_ANIMATION_STATUS_RUNNING: dst = static_cast<int32_t>(src); break;
        case Ark_AnimationStatus::ARK_ANIMATION_STATUS_PAUSED: dst = static_cast<int32_t>(src); break;
        case Ark_AnimationStatus::ARK_ANIMATION_STATUS_STOPPED: dst = static_cast<int32_t>(src); break;
        default: LOGE("Unexpected enum value in Ark_AnimationStatus: %{public}d", src);
    }
}
template<>
void AssignCast(std::optional<int32_t>& dst, const Ark_FillMode& src)
{
    switch (src) {
        case Ark_FillMode::ARK_FILL_MODE_NONE: dst = static_cast<int32_t>(src); break;
        case Ark_FillMode::ARK_FILL_MODE_FORWARDS: dst = static_cast<int32_t>(src); break;
        case Ark_FillMode::ARK_FILL_MODE_BACKWARDS: dst = static_cast<int32_t>(src); break;
        case Ark_FillMode::ARK_FILL_MODE_BOTH: dst = static_cast<int32_t>(src); break;
        default: LOGE("Unexpected enum value in Ark_FillMode: %{public}d", src);
    }
}

template<>
ImageProperties Convert(const Ark_ImageFrameInfo& src)
{
    ImageProperties options;
    Converter::VisitUnion(src.src,
        [&options](const Ark_String& srcArkStr) {
            auto srcStr = Converter::Convert<std::string>(srcArkStr);
            if (!srcStr.empty()) {
                options.src = srcStr;
            }
        },
        [&options](const Ark_Resource& srcArkRes) {
            auto srcStr = Converter::OptConvert<std::string>(srcArkRes);
            auto moduleName = Converter::Convert<std::string>(srcArkRes.moduleName);
            auto bundleName = Converter::Convert<std::string>(srcArkRes.bundleName);
            if (!srcStr->empty()) {
                options.src = *srcStr;
                options.moduleName = moduleName;
                options.bundleName = bundleName;
            }
        },
        [&options](const Ark_image_PixelMap& srcArkPixelMap) {
            options.pixelMap = Converter::Convert<RefPtr<PixelMap>>(srcArkPixelMap);
        },
        []() {}
    );

    options.width =  OptConvert<CalcDimension>(src.width).value_or(CalcDimension(0, DimensionUnit::VP));
    options.height = OptConvert<CalcDimension>(src.height).value_or(CalcDimension(0, DimensionUnit::VP));
    options.top = OptConvert<CalcDimension>(src.top).value_or(CalcDimension(0, DimensionUnit::VP));
    options.left = OptConvert<CalcDimension>(src.left).value_or(CalcDimension(0, DimensionUnit::VP));
    options.duration = Converter::OptConvert<int32_t>(src.duration).value_or(0);

    return options;
}
} // OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ImageAnimatorModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = ImageAnimatorModelStatic::CreateFrameNode(id);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // ImageAnimatorModifier
namespace ImageAnimatorInterfaceModifier {
void SetImageAnimatorOptionsImpl(Ark_NativePointer node)
{
    // No implementation is required
}
} // ImageAnimatorInterfaceModifier
namespace ImageAnimatorAttributeModifier {
void SetImagesImpl(Ark_NativePointer node,
                   const Opt_Array_ImageFrameInfo* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto images = Converter::OptConvert<std::vector<ImageProperties>>(*value);
    if (!images) {
        ImageAnimatorModelNG::SetImages(frameNode, std::vector<ImageProperties>());
        return;
    }
    ImageAnimatorModelNG::SetImages(frameNode, *images);
}
void SetStateImpl(Ark_NativePointer node,
                  const Opt_AnimationStatus* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto stateOpt = Converter::OptConvertPtr<int32_t>(value);
    ImageAnimatorModelStatic::SetState(frameNode, stateOpt);
}
void SetDurationImpl(Ark_NativePointer node,
                     const Opt_Int32* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto durationOpt = Converter::OptConvertPtr<int32_t>(value);
    Validator::ValidateNonNegative(durationOpt);
    ImageAnimatorModelStatic::SetDuration(frameNode, durationOpt);
}
void SetReverseImpl(Ark_NativePointer node,
                    const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        ImageAnimatorModelNG::SetIsReverse(frameNode, false);
        return;
    }
    ImageAnimatorModelNG::SetIsReverse(frameNode, *convValue);
}
void SetFixedSizeImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        ImageAnimatorModelNG::SetFixedSize(frameNode, true);
        return;
    }
    ImageAnimatorModelNG::SetFixedSize(frameNode, *convValue);
}
void SetFillModeImpl(Ark_NativePointer node,
                     const Opt_FillMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto fillModeOpt = Converter::OptConvertPtr<int32_t>(value);
    ImageAnimatorModelStatic::SetFillMode(frameNode, fillModeOpt);
}
void SetIterationsImpl(Ark_NativePointer node,
                       const Opt_Int32* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto iterationOpt = Converter::OptConvertPtr<int32_t>(value);
    Validator::ValidateGreatOrEqual(iterationOpt, -1);
    ImageAnimatorModelStatic::SetIteration(frameNode, iterationOpt);
}
void SetMonitorInvisibleAreaImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        ImageAnimatorModelNG::SetAutoMonitorInvisibleArea(frameNode, false);
        return;
    }
    ImageAnimatorModelNG::SetAutoMonitorInvisibleArea(frameNode, *convValue);
}
void SetOnStartImpl(Ark_NativePointer node,
                    const Opt_synthetic_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ImageAnimatorModelNG::SetOnStart(frameNode, nullptr);
        return;
    }
    auto onStart = [arkCallback = CallbackHelper(*optValue)]() -> void {
        arkCallback.Invoke();
    };
    ImageAnimatorModelNG::SetOnStart(frameNode, std::move(onStart));
}
void SetOnPauseImpl(Ark_NativePointer node,
                    const Opt_synthetic_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ImageAnimatorModelNG::SetOnPause(frameNode, nullptr);
        return;
    }
    auto onPause = [arkCallback = CallbackHelper(*optValue)]() -> void {
        arkCallback.Invoke();
    };
    ImageAnimatorModelNG::SetOnPause(frameNode, std::move(onPause));
}
void SetOnRepeatImpl(Ark_NativePointer node,
                     const Opt_synthetic_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ImageAnimatorModelNG::SetOnRepeat(frameNode, nullptr);
        return;
    }
    auto onRepeat = [arkCallback = CallbackHelper(*optValue)]() -> void {
        arkCallback.Invoke();
    };
    ImageAnimatorModelNG::SetOnRepeat(frameNode, onRepeat);
}
void SetOnCancelImpl(Ark_NativePointer node,
                     const Opt_synthetic_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ImageAnimatorModelNG::SetOnCancel(frameNode, nullptr);
        return;
    }
    auto onCancel = [arkCallback = CallbackHelper(*optValue)]() -> void {
        arkCallback.Invoke();
    };
    ImageAnimatorModelNG::SetOnCancel(frameNode, onCancel);
}
void SetOnFinishImpl(Ark_NativePointer node,
                     const Opt_synthetic_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ImageAnimatorModelNG::SetOnFinish(frameNode, nullptr);
        return;
    }
    auto onFinish = [arkCallback = CallbackHelper(*optValue)]() -> void {
        arkCallback.Invoke();
    };
    ImageAnimatorModelNG::SetOnFinish(frameNode, onFinish);
}
} // ImageAnimatorAttributeModifier
const GENERATED_ArkUIImageAnimatorModifier* GetImageAnimatorModifier()
{
    static const GENERATED_ArkUIImageAnimatorModifier ArkUIImageAnimatorModifierImpl {
        ImageAnimatorModifier::ConstructImpl,
        ImageAnimatorInterfaceModifier::SetImageAnimatorOptionsImpl,
        ImageAnimatorAttributeModifier::SetImagesImpl,
        ImageAnimatorAttributeModifier::SetStateImpl,
        ImageAnimatorAttributeModifier::SetDurationImpl,
        ImageAnimatorAttributeModifier::SetReverseImpl,
        ImageAnimatorAttributeModifier::SetFixedSizeImpl,
        ImageAnimatorAttributeModifier::SetFillModeImpl,
        ImageAnimatorAttributeModifier::SetIterationsImpl,
        ImageAnimatorAttributeModifier::SetMonitorInvisibleAreaImpl,
        ImageAnimatorAttributeModifier::SetOnStartImpl,
        ImageAnimatorAttributeModifier::SetOnPauseImpl,
        ImageAnimatorAttributeModifier::SetOnRepeatImpl,
        ImageAnimatorAttributeModifier::SetOnCancelImpl,
        ImageAnimatorAttributeModifier::SetOnFinishImpl,
    };
    return &ArkUIImageAnimatorModifierImpl;
}

}
