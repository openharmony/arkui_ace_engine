/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "want.h"
#include "core/common/modal_ui_extension.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_manager.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_model_ng.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_pattern.h"

namespace OHOS::Ace {
RefPtr<NG::FrameNode> ModalUIExtension::Create(const AAFwk::Want& want, const ModalUIExtensionCallbacks& callbacks,
    const NG::InnerModalUIExtensionConfig& config)
{
    return NG::UIExtensionModelNG::Create(want, callbacks, config);
}

int32_t ModalUIExtension::GetSessionId(const RefPtr<NG::FrameNode>& uiExtNode)
{
    auto pattern = uiExtNode->GetPattern<NG::UIExtensionPattern>();
    CHECK_NULL_RETURN(pattern, 0);
    return pattern->GetSessionId();
}

void ModalUIExtension::SetBindModalCallback(const RefPtr<NG::FrameNode>& uiExtNode,
    std::function<void()>&& bindModalCallback)
{
    CHECK_NULL_VOID(uiExtNode);
    auto pattern = uiExtNode->GetPattern<NG::UIExtensionPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetBindModalCallback(std::move(bindModalCallback));
}

OHOS::AAFwk::Want GetWantFromUECHostMaskInfo(const UECHostMaskInfo& maskInfo)
{
    OHOS::AAFwk::Want want;
    want.SetParam("uuid", maskInfo.uuid);
    want.SetParam("instanceId", maskInfo.instanceId);
    want.SetParam("overlayTag", maskInfo.overlayTag);
    want.SetParam("overlayId", maskInfo.overlayId);
    want.SetParam("maskAction", static_cast<int32_t>(maskInfo.maskAction));
    want.SetParam("maskType", static_cast<int32_t>(maskInfo.maskType));
    if (maskInfo.maskColor.has_value()) {
        want.SetParam("maskColor", maskInfo.maskColor.value().ToString());
    }
    return want;
}

UECHostMaskInfo ModalUIExtension::GetUECHostMaskInfoFromWant(const OHOS::AAFwk::Want& want)
{
    UECHostMaskInfo maskInfo;
    maskInfo.uuid = want.GetStringParam("uuid");
    maskInfo.instanceId = want.GetIntParam("instanceId", -1);
    maskInfo.overlayTag = want.GetStringParam("overlayTag");
    maskInfo.overlayId = want.GetIntParam("overlayId", -1);
    maskInfo.maskAction = static_cast<UECHostMaskAction>(want.GetIntParam("maskAction", 0));
    maskInfo.maskType = static_cast<UECHostMaskType>(want.GetIntParam("maskType", 0));

    if (want.HasParameter("maskColor")) {
        maskInfo.maskColor = Color::FromString(want.GetStringParam("maskColor"));
    }
    return maskInfo;
}

void ModalUIExtension::RegisterBusinessConsumeCallbackOnUEA(const RefPtr<NG::UIExtensionManager>& uiExtMgr,
    NG::UIContentBusinessCode code, BusinessDataUECConsumeCallback callback)
{
    CHECK_NULL_VOID(uiExtMgr);
    uiExtMgr->RegisterBusinessDataConsumeCallback(code, std::move(callback));
}

void ModalUIExtension::RegisterBusinessConsumeCallbackOnHost(
    const RefPtr<NG::FrameNode>& uiExtNode, NG::UIContentBusinessCode code, BusinessDataUECConsumeCallback callback)
{
    CHECK_NULL_VOID(uiExtNode);
    auto pattern = uiExtNode->GetPattern<NG::UIExtensionPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RegisterUIExtBusinessConsumeCallback(code, std::move(callback));
}

bool ModalUIExtension::SendOverlayMaskInfoToUEA(const RefPtr<NG::FrameNode>& uiExtNode, const UECHostMaskInfo& info,
    NG::UIContentBusinessCode code, NG::BusinessDataSendType type)
{
    CHECK_NULL_RETURN(uiExtNode, false);
    auto pattern = uiExtNode->GetPattern<NG::UIExtensionPattern>();
    CHECK_NULL_RETURN(pattern, false);

    OHOS::AAFwk::Want data = GetWantFromUECHostMaskInfo(info);
    return pattern->SendBusinessData(code, std::move(data), type);
}

bool ModalUIExtension::SendOverlayMaskInfoToHost(const RefPtr<NG::UIExtensionManager>& uiExtMgr,
    const UECHostMaskInfo& info, NG::UIContentBusinessCode code, NG::BusinessDataSendType type)
{
    CHECK_NULL_RETURN(uiExtMgr, false);

    OHOS::AAFwk::Want data = GetWantFromUECHostMaskInfo(info);
    return uiExtMgr->SendBusinessToHost(code, std::move(data), type);
}
} // namespace OHOS::Ace
