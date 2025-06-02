/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "cj_lambda.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_paste_button_ffi.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/pattern/security_component/paste_button/paste_button_common.h"
#include "core/components_ng/pattern/security_component/paste_button/paste_button_model_ng.h"
#include "core/components_ng/pattern/security_component/security_component_theme.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;
using OHOS::Ace::NG::PasteButtonModelNG;
using OHOS::Ace::NG::SecurityComponentTheme;

extern "C" {
void FfiOHOSAceFrameworkPasteButtonCreate()
{
    PasteButtonModelNG::GetInstance()->Create(
        static_cast<int32_t>(PasteButtonPasteDescription::PASTE),
        static_cast<int32_t>(PasteButtonIconStyle::ICON_LINE),
        static_cast<int32_t>(ButtonType::CAPSULE), false);
}

void FfiOHOSAceFrameworkPasteButtonCreateWithButtonOptions(int32_t icon, int32_t text, int32_t buttonType)
{
    PasteButtonModelNG::GetInstance()->Create(text, icon, buttonType, false);
}

void FfiOHOSAceFrameworkPasteButtonOnClick(void (*callback)(CJClickInfo event, int32_t result))
{
    auto lambda = [ffiOnClick = CJLambda::Create(callback)](const GestureEvent& info) -> void {
        int32_t res = static_cast<int32_t>(SecurityComponentHandleResult::CLICK_GRANT_FAILED);
        auto secEventValue = info.GetSecCompHandleEvent();
        if (secEventValue != nullptr) {
            res = secEventValue->GetInt("handleRes", res);
            if (res == static_cast<int32_t>(SecurityComponentHandleResult::DROP_CLICK)) {
                return;
            }
        }
        CJClickInfo cjClickInfo {};
        CJEventTarget cjEventTarget {};
        CJArea cjArea {};
        CJPosition cjPosition {};
        CJPosition cjGlobalPosition {};
        AssambleCJClickInfo(info, cjClickInfo, cjEventTarget, cjArea, cjPosition, cjGlobalPosition);
        ffiOnClick(cjClickInfo, res);
    };
    double distanceThreshold = std::numeric_limits<double>::infinity();
    NG::ViewAbstract::SetOnClick(std::move(lambda), distanceThreshold);
}
}