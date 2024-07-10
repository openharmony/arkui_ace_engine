/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "ui_service_mgr_xcollie.h"

#include "ui_service_hilog.h"

#ifdef UISERVICE_MGR_XCOLLIE_ENABLE
#include "xcollie/xcollie.h"
#endif

namespace OHOS::Ace {
UIServiceMgrXCollie::UIServiceMgrXCollie(const std::string& tag, uint32_t timeoutSeconds)
{
    tag_ = tag;
#ifdef UISERVICE_MGR_XCOLLIE_ENABLE
    id_ = HiviewDFX::XCollie::GetInstance().SetTimer(tag_, timeoutSeconds, nullptr, nullptr,
        OHOS::HiviewDFX::XCOLLIE_FLAG_LOG | OHOS::HiviewDFX::XCOLLIE_FLAG_RECOVERY);
#else
    id_ = -1;
#endif
    isCanceled_ = false;
    LOGI("start UIServiceMgrXCollie, tag:%{public}s, timeout: %{public}u, id: %{public}d", tag_.c_str(),
        timeoutSeconds, id_);
}

UIServiceMgrXCollie::~UIServiceMgrXCollie()
{
    CancelUIServiceMgrXCollie();
}

void UIServiceMgrXCollie::CancelUIServiceMgrXCollie()
{
    if (!isCanceled_) {
#ifdef UISERVICE_MGR_XCOLLIE_ENABLE
        HiviewDFX::XCollie::GetInstance().CancelTimer(id_);
#endif
        isCanceled_ = true;
        LOGI("cancel UIServiceMgrXCollie, tag: %{public}s, id: %{public}d", tag_.c_str(), id_);
    }
}
}  // namespace OHOS::Ace