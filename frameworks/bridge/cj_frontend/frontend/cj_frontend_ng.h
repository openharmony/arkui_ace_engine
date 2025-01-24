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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_CJ_FRONTEND_CJ_FRONTEND_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_CJ_FRONTEND_CJ_FRONTEND_NG_H

#include "bridge/cj_frontend/frontend/cj_page_router_abstract.h"
#include "bridge/cj_frontend/frontend/cj_frontend_abstract.h"
#include "bridge/cj_frontend/frontend/cj_page_router_ng.h"
#include "core/components_ng/pattern/container_modal/container_modal_view.h"

namespace OHOS::Ace::Framework {

class ACE_FORCE_EXPORT CJFrontendNG final : public CJFrontendAbstract {
    DECLARE_ACE_TYPE(CJFrontendNG, CJFrontendAbstract)

protected:
    void InternalInitialize() override;

private:
    RefPtr<CJPageRouterNG> ngRouter_;
};

}

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_CJ_FRONTEND_CJ_FRONTEND_NG_H
