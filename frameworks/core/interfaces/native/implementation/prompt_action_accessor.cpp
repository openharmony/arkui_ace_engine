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

#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components/toast/toast_theme.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components_ng/pattern/overlay/dialog_manager_static.h"
#include "frameworks/base/utils/utils.h"
#include "frameworks/base/utils/system_properties.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/core/components_ng/pattern/toast/toast_layout_property.h"

namespace OHOS::Ace::NG {
constexpr int32_t TOAST_TIME_MAX = 10000;    // ms
constexpr int32_t TOAST_TIME_DEFAULT = 1500; // ms
#ifdef OHOS_STANDARD_SYSTEM
bool ContainerIsService()
{
    auto containerId = Container::CurrentIdSafely();
    if (containerId < 0) {
        auto container = Container::GetActive();
        if (container) {
            containerId = container->GetInstanceId();
        }
    }
    return containerId >= MIN_PA_SERVICE_ID || containerId < 0;
}

bool ContainerIsScenceBoard()
{
    auto container = Container::CurrentSafely();
    if (!container) {
        container = Container::GetActive();
    }
    return container && container->IsScenceBoardWindow();
}
#endif
} // OHOS::Ace::NG

namespace OHOS::Ace::NG::Converter {
template<>
void AssignCast(std::optional<NG::ToastShowMode>& dst, const Ark_ToastShowMode& src)
{
    switch (src) {
        case ARK_TOAST_SHOW_MODE_DEFAULT: dst = NG::ToastShowMode::DEFAULT; break;
        case ARK_TOAST_SHOW_MODE_TOP_MOST: dst = NG::ToastShowMode::TOP_MOST; break;
        case ARK_TOAST_SHOW_MODE_SYSTEM_TOP_MOST: dst = NG::ToastShowMode::SYSTEM_TOP_MOST; break;
        default: LOGE("Unexpected enum value in Ark_ToastShowMode: %{public}d", src);
    }
}

template<>
ToastInfo Convert(const Ark_ShowToastOptions& options)
{
    int32_t alignment = -1;
    auto pipelineContext = PipelineContext::GetCurrentContext();
    if (pipelineContext) {
        auto toastTheme = pipelineContext->GetTheme<ToastTheme>();
        if (toastTheme) {
            alignment = toastTheme->GetAlign();
        }
    }
    NG::ToastInfo toastInfo;
    Converter::VisitUnion(options.message,
        [&toastInfo](const Ark_String& val) {
            toastInfo.message = Converter::Convert<std::string>(val);
        },
        [&toastInfo](const Ark_Resource& val) {
            auto msgResourceStr = Converter::OptConvert<std::string>(val).value_or("");
        }, []() {}
    );
    toastInfo.duration = std::clamp(Converter::OptConvert<int32_t>(options.duration).value_or(-1),
        TOAST_TIME_DEFAULT, TOAST_TIME_MAX);
    Converter::VisitUnion(options.bottom,
        [&toastInfo](const Ark_String& val) {
            toastInfo.bottom = Converter::Convert<std::string>(val);
        },
        [&toastInfo](const Ark_Number& val) {
            toastInfo.bottom = std::to_string(Converter::Convert<int32_t>(val));
        }, []() {}
    );
    toastInfo.showMode = Converter::OptConvert<NG::ToastShowMode>(options.showMode).value_or(
        NG::ToastShowMode::DEFAULT
    );
    toastInfo.alignment = options.alignment.tag == InteropTag::INTEROP_TAG_UNDEFINED ? alignment :
        static_cast<int32_t>(options.alignment.value);
    toastInfo.offset = Converter::OptConvert<DimensionOffset>(options.offset);
    toastInfo.backgroundColor = Converter::OptConvert<Color>(options.backgroundColor);
    toastInfo.textColor = Converter::OptConvert<Color>(options.textColor);
    auto backgroundBlurStyle = Converter::OptConvert<BlurStyle>(options.backgroundBlurStyle);
    toastInfo.backgroundBlurStyle = backgroundBlurStyle ?
        std::optional<int32_t>(static_cast<int32_t>(backgroundBlurStyle.value())) : std::nullopt;
    toastInfo.shadow = Converter::OptConvert<Shadow>(options.shadow);
    if (options.shadow.tag != INTEROP_TAG_UNDEFINED && options.shadow.value.selector == 0) {
        toastInfo.isTypeStyleShadow = false;
    }
    toastInfo.enableHoverMode = Converter::OptConvert<bool>(options.enableHoverMode).value_or(
        toastInfo.enableHoverMode);
    auto hoverModeArea = Converter::OptConvert<HoverModeAreaType>(options.hoverModeArea);
    if (hoverModeArea.has_value()) {
        toastInfo.hoverModeArea = hoverModeArea.value();
    }
    toastInfo.isRightToLeft = AceApplicationInfo::GetInstance().IsRightToLeft();
    return toastInfo;
}
} // OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace PromptActionAccessor {
void ShowToastImpl(const Ark_ShowToastOptions* options,
    const Callback_Number_Void* callback_value)
{
    auto toastInfo = Converter::Convert<ToastInfo>(*options);
    std::function<void(int32_t)> toastCallback = nullptr;
    if (callback_value) {
        toastCallback = [arkCallback = CallbackHelper(*callback_value)](int32_t toastId) {
            arkCallback.Invoke(Converter::ArkValue<Ark_Number>(toastId));
        };
    }
#ifdef OHOS_STANDARD_SYSTEM
    if ((OHOS::Ace::SystemProperties::GetExtSurfaceEnabled() || !ContainerIsService()) && !ContainerIsScenceBoard() &&
        toastInfo.showMode == OHOS::Ace::NG::ToastShowMode::DEFAULT) {
        DialogManagerStatic::ShowToastStatic(toastInfo, std::move(toastCallback), INSTANCE_ID_UNDEFINED);
    } else if (OHOS::Ace::SubwindowManager::GetInstance() != nullptr) {
        OHOS::Ace::SubwindowManager::GetInstance()->ShowToastStatic(toastInfo, std::move(toastCallback));
    }
#else
    if (toastInfo.showMode == OHOS::Ace::NG::ToastShowMode::DEFAULT) {
        DialogManagerStatic::ShowToastStatic(toastInfo, std::move(toastCallback), INSTANCE_ID_UNDEFINED);
    } else if (OHOS::Ace::SubwindowManager::GetInstance() != nullptr) {
        OHOS::Ace::SubwindowManager::GetInstance()->ShowToastStatic(toastInfo, std::move(toastCallback));
    }
#endif
}

void CloseToastImpl(const Ark_Number* id,
    const Callback_Number_Void* callback_value)
{
    auto toastCloseCallback = [arkCallback = CallbackHelper(*callback_value)](int32_t errorCode) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Number>(errorCode));
    };
    
    if (!id) {
        toastCloseCallback(ERROR_CODE_PARAM_INVALID);
        return;
    }
    int32_t showModeVal = static_cast<int32_t>(Converter::Convert<uint32_t>(*id) & 0b111);
    int32_t toastId = static_cast<int32_t>(Converter::Convert<uint32_t>(*id) >> 3);
    if (toastId < 0 || showModeVal < 0 || showModeVal > static_cast<int32_t>(NG::ToastShowMode::SYSTEM_TOP_MOST)) {
        toastCloseCallback(ERROR_CODE_TOAST_NOT_FOUND);
        return;
    }
    auto showMode = static_cast<NG::ToastShowMode>(showModeVal);
#ifdef OHOS_STANDARD_SYSTEM
    if ((OHOS::Ace::SystemProperties::GetExtSurfaceEnabled() || !ContainerIsService()) && !ContainerIsScenceBoard() &&
        showMode == NG::ToastShowMode::DEFAULT) {
        DialogManagerStatic::CloseToastStatic(toastId, std::move(toastCloseCallback), INSTANCE_ID_UNDEFINED);
    } else if (SubwindowManager::GetInstance() != nullptr) {
        SubwindowManager::GetInstance()->CloseToastStatic(toastId, showMode, std::move(toastCloseCallback));
    }
#else
    if (showMode == NG::ToastShowMode::DEFAULT) {
        DialogManagerStatic::CloseToastStatic(toastId, std::move(toastCloseCallback), INSTANCE_ID_UNDEFINED);
    } else if (SubwindowManager::GetInstance() != nullptr) {
        SubwindowManager::GetInstance()->CloseToastStatic(toastId, showMode, std::move(toastCloseCallback));
    }
#endif
}
} // PromptActionAccessor

const GENERATED_ArkUIPromptActionAccessor* GetPromptActionAccessor()
{
    static const GENERATED_ArkUIPromptActionAccessor PromptActionAccessorImpl {
        PromptActionAccessor::ShowToastImpl,
        PromptActionAccessor::CloseToastImpl,
    };
    return &PromptActionAccessorImpl;
}
}