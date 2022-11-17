/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/models/loading_progress_model_impl.h"

#include "base/geometry/dimension.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::Framework {
void LoadingProgressModelImpl::Create()
{
    RefPtr<LoadingProgressComponent> loadingProgressComponent =
        AceType::MakeRefPtr<OHOS::Ace::LoadingProgressComponent>();
    ViewStackProcessor::GetInstance()->ClaimElementId(loadingProgressComponent);
    ViewStackProcessor::GetInstance()->Push(loadingProgressComponent);
}

void LoadingProgressModelImpl::SetColor(const Color& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto loadingProgress = AceType::DynamicCast<LoadingProgressComponent>(component);
    loadingProgress->SetProgressColor(value);
}
} // namespace OHOS::Ace::Framework
