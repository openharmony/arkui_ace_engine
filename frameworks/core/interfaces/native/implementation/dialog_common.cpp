/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "dialog_common.h"

#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"

#include "dismiss_dialog_action_peer.h"

namespace OHOS::Ace::NG {
namespace GeneratedModifier {
void AddOnWillDismiss(DialogProperties& properties, Opt_Callback_DismissDialogAction_Void onWillDismiss)
{
    auto onWillDismissOpt = Converter::OptConvert<Callback_DismissDialogAction_Void>(onWillDismiss);
    CHECK_NULL_VOID(onWillDismissOpt);
    properties.onWillDismiss = [callback = CallbackHelper(onWillDismissOpt.value())](
        const int32_t& info, const int32_t& instanceId
    ) {
        auto peer = PeerUtils::CreatePeer<DismissDialogActionPeer>();
        peer->reason = static_cast<BindSheetDismissReason>(info);
        callback.InvokeSync(peer);
    };
}
} // namespace GeneratedModifier
namespace Converter {
template<>
void AssignCast(std::optional<PopupLinearGradientProperties>& dst, const Ark_PopupBorderLinearGradient& src)
{
    PopupLinearGradientProperties popupBorderLinearGradient;
    popupBorderLinearGradient.popupDirection = OHOS::Ace::GradientDirection::BOTTOM;
    auto directionOpt = Converter::OptConvert<GradientDirection>(src.direction);
    if (directionOpt) {
        popupBorderLinearGradient.popupDirection = static_cast<OHOS::Ace::GradientDirection>(directionOpt.value());
    }
    for (int32_t i = 0; i < src.colors.length; i++) {
        PopupGradientColor gradientColor;
        auto color = OptConvert<Color>(src.colors.array[i].value0);
        if (color) {
            gradientColor.gradientColor = color.value();
        }
        gradientColor.gradientNumber = Convert<double>(src.colors.array[i].value1);
        popupBorderLinearGradient.gradientColors.push_back(gradientColor);
    }
    dst = popupBorderLinearGradient;
}

template<>
MenuPreviewAnimationOptions Convert(const Ark_AnimationNumberRange& options)
{
    auto scaleFrom = Convert<float>(options.value0);
    auto scaleTo = Convert<float>(options.value1);
    return {
        .scaleFrom = LessOrEqual(scaleFrom, 0.0) ? -1.0f : scaleFrom,
        .scaleTo = LessOrEqual(scaleTo, 0.0) ? -1.0f : scaleTo
    };
}

template<>
NG::MenuParam Convert(const Ark_ContextMenuAnimationOptions& options)
{
    NG::MenuParam menuParam;
    auto scale = OptConvert<MenuPreviewAnimationOptions>(options.scale);
    if (scale) {
        menuParam.previewAnimationOptions = *scale;
    }
    menuParam.hasPreviewTransitionEffect = false;
    auto previewTransition = OptConvert<RefPtr<NG::ChainedTransitionEffect>>(options.transition);
    if (previewTransition && *previewTransition) {
        menuParam.hasPreviewTransitionEffect = true;
        menuParam.previewTransition = *previewTransition;
    }
    auto hoverScale = OptConvert<MenuPreviewAnimationOptions>(options.hoverScale);
    menuParam.isShowHoverImage = false;
    if (hoverScale) {
        menuParam.hoverImageAnimationOptions = *hoverScale;
        menuParam.isShowHoverImage = true;
    }
    auto hoverScaleInterruption = OptConvert<bool>(options.hoverScaleInterruption);
    menuParam.hoverScaleInterruption = hoverScaleInterruption.value_or(false);
    return menuParam;
}

template<>
MenuKeyboardAvoidMode Convert(const Ark_MenuKeyboardAvoidMode& options)
{
    if (options == Ark_MenuKeyboardAvoidMode::ARK_MENU_KEYBOARD_AVOID_MODE_TRANSLATE_AND_RESIZE) {
        return MenuKeyboardAvoidMode::TRANSLATE_AND_RESIZE;
    }
    return MenuKeyboardAvoidMode::NONE;
}
} // namespace Converter
} // namespace OHOS::Ace::NG