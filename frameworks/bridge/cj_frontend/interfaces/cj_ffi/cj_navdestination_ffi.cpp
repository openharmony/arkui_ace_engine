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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_navdestination_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_navigation_stack_ffi.h"
#include "core/components_ng/pattern/navrouter/navdestination_model_ng.h"
#include "core/components_ng/pattern/navrouter/navdestination_context.h"

#include "cj_lambda.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace {
std::unique_ptr<NavDestinationModel> NavDestinationModel::instance_ = nullptr;
std::mutex NavDestinationModel::mutex_;

NavDestinationModel* NavDestinationModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        instance_.reset(new NG::NavDestinationModelNG());
    }
    return instance_.get();
}
} // namespace OHOS::Ace

extern "C" {
void FfiOHOSAceFrameworkNavdestinationCreate()
{
    auto builderFunc = []() {};
    auto ctx = AceType::MakeRefPtr<NG::NavDestinationContext>();
    auto navPathInfo = AceType::MakeRefPtr<CJNavPathInfoNG>();
    ctx->SetNavPathInfo(navPathInfo);
    NavDestinationModel::GetInstance()->Create(std::move(builderFunc), std::move(ctx));
}

void FfiOHOSAceFrameworkNavdestinationSetOnBackPressed(bool (*callback)())
{
    NavDestinationModel::GetInstance()->SetOnBackPressed(CJLambda::Create(callback));
}

void FfiOHOSAceFrameworkNavdestinationSetOnReady(void (*callback)(CJNavDestinationContext context))
{
    auto onReadyCallback = [ffiCallback = CJLambda::Create(callback)](RefPtr<NG::NavDestinationContext> context) {
        auto pathInfo = context->GetNavPathInfo();
        CJNavPathInfoFFi info = CJNavPathInfoFFi();
        info.name = strdup(pathInfo->GetName().c_str());
        int64_t pathStackId = 0;
        auto stack = context->GetNavigationStack().Upgrade();
        if (stack) {
            auto cjStack = AceType::DynamicCast<CJNavigationStack>(stack);
            if (cjStack) {
                pathStackId = cjStack->GetDataSourceObjId();
            }
        }
        CJNavDestinationContext cjContext = CJNavDestinationContext();
        cjContext.navDestinationId = context->GetNavDestinationId();
        cjContext.pathStack = pathStackId;
        cjContext.pathInfo = info;
        ffiCallback(cjContext);
    };
    NavDestinationModel::GetInstance()->SetOnReady(std::move(onReadyCallback));
}
} //extern "C"
