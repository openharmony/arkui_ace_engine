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

#include "bridge/cj_frontend/frontend/cj_frontend_loader.h"

#include "bridge/cj_frontend/cppview/native_view.h"
#include "bridge/cj_frontend/frontend/cj_frontend_abstract.h"
#include "bridge/cj_frontend/frontend/cj_frontend_ng.h"
#include "bridge/cj_frontend/frontend/cj_frontend.h"
#include "bridge/cj_frontend/frontend/cj_page_loader.h"
#include "bridge/cj_frontend/frontend/cj_page_router.h"
#include "core/components_ng/pattern/stage/page_pattern.h"

namespace OHOS::Ace {
namespace Framework {
bool LoadNativeView(const sptr<NativeView>& view)
{
#ifdef NG_BUILD
    return LoadNativeViewNG(view.GetRefPtr());
#else
    if (Container::IsCurrentUseNewPipeline()) {
        return LoadNativeViewNG(view.GetRefPtr());
    } else {
        return LoadNativeViewClassic(view.GetRefPtr());
    }
#endif
}

RefPtr<Frontend> LoadAndCreateCJFrontend(bool useNewPipeline)
{
#ifdef NG_BUILD
    return AceType::MakeRefPtr<CJFrontendNG>();
#else
    if (useNewPipeline) {
        return AceType::MakeRefPtr<CJFrontendNG>();
    } else {
        return AceType::MakeRefPtr<CJFrontend>();
    }
#endif
}

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_CreateCJFrontend(bool useNewPipeline, bool isStageModel)
{
    CJFrontendAbstract* frontend_ = nullptr;
#ifdef NG_BUILD
    frontend_ = new CJFrontendNG();
    return frontend_;
#else
    if (useNewPipeline) {
        frontend_ = new CJFrontendNG();
        frontend_->SetStageModel(isStageModel);
        return frontend_;
    } else {
        frontend_ = new CJFrontend();
        frontend_->SetStageModel(isStageModel);
        return frontend_;
    }
#endif
}
}
}