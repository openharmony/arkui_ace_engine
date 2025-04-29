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

#include "core/components_ng/pattern/form_button/form_button_pattern.h"

#include "want.h"

#include "form_constants.h"
#include "form_mgr.h"

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

FormButtonPattern::FormButtonPattern()
{
    ACE_SCOPED_TRACE("FormButtonCreate");
}

FormButtonPattern::~FormButtonPattern() = default;

void FormButtonPattern::OnAttachToFrameNode()
{
    InitClickEvent();
}

void FormButtonPattern::InitClickEvent()
{
    TAG_LOGI(AceLogTag::ACE_FORM, "FormButtonPattern InitClickEvent begin");
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureEventHub = host->GetOrCreateGestureEventHub();
    auto clickCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto formButtonPattern = weak.Upgrade();
        TAG_LOGI(AceLogTag::ACE_FORM, "gestureEvent - clickCallback");
        CHECK_NULL_VOID(formButtonPattern);

        OHOS::AAFwk::Want want;
        const std::string bundleName = formButtonPattern->GetBundleName();
        const std::string abilityName = formButtonPattern->GetAbilityName();
        const std::string cardName = formButtonPattern->GetCardName();
        const std::string moduleName = formButtonPattern->GetModuleName();
        int32_t dimension = formButtonPattern->GetDimension();

        want.SetElementName(bundleName, abilityName);
        want.SetParam("name", cardName);
        want.SetParam("moduleName", moduleName);
        want.SetParam("dimension", dimension);

        OHOS::AAFwk::Want wantToScb(want);
        wantToScb.SetAction(AppExecFwk::Constants::FORM_PAGE_ACTION);
        wantToScb.SetParam(AppExecFwk::Constants::PARAM_PAGE_ROUTER_SERVICE_CODE,
            AppExecFwk::Constants::PAGE_ROUTER_SERVICE_CODE_FORM_MANAGE);
        const std::string key = AppExecFwk::Constants::PARMA_REQUEST_METHOD;
        const std::string value = AppExecFwk::Constants::OPEN_FORM_MANAGE_VIEW;
        wantToScb.SetParam(key, value);
        AppExecFwk::FormMgr::GetInstance().StartAbilityByFms(wantToScb);
    };
    auto clickEvent = AceType::MakeRefPtr<ClickEvent>(std::move(clickCallback));
    gestureEventHub->AddClickEvent(clickEvent);
}
} // namespace OHOS::Ace::NG