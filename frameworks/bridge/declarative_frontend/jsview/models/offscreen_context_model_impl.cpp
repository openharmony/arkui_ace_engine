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

#include "frameworks/bridge/declarative_frontend/jsview/models/offscreen_context_model_impl.h"

#include "frameworks/core/common/container.h"
#include "frameworks/core/components/custom_paint/offscreen_canvas.h"
#include "frameworks/core/pipeline/pipeline_context.h"

namespace OHOS::Ace::Framework {
RefPtr<AceType> OffscreenContextModelImpl::CreateOffscreenPattern(int width, int height)
{
    auto container = Ace::Container::Current();
    CHECK_NULL_RETURN(container, nullptr);
    auto context = AceType::DynamicCast<Ace::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_RETURN(context, nullptr);
    auto offscreenPattern = context->CreateOffscreenCanvas(width, height);
    return offscreenPattern;
}
} // namespace OHOS::Ace::NG