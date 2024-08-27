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

#include "bridge/cj_frontend/frontend/cj_frontend_ng.h"
#include "bridge/cj_frontend/frontend/cj_page_loader.h"

namespace OHOS::Ace {
namespace Framework {
bool LoadNativeView(const sptr<NativeView>& view)
{
    return LoadNativeViewNG(view.GetRefPtr());
}

RefPtr<Frontend> LoadAndCreateCJFrontend(bool useNewPipeline)
{
    if (!useNewPipeline) {
        LOGE("only support new pipeline.");
        return nullptr;
    }
    return AceType::MakeRefPtr<CJFrontendNG>();
}

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_CreateCJFrontend(bool useNewPipeline, bool isStageModel)
{
    if (!useNewPipeline) {
        LOGE("only support new pipeline.");
        return nullptr;
    }
    CJFrontendAbstract* frontend_ = nullptr;
    frontend_ = new CJFrontendNG();
    frontend_->SetStageModel(isStageModel);
    return frontend_;
}
}
}