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

#include "core/components_ng/pattern/view_context/view_context_model_ng.h"

#include "core/common/container.h"
#include "core/components_ng/base/view_stack_processor.h"

namespace OHOS::Ace::NG {
void ViewContextModelNG::closeAnimation(const AnimationOption& option, bool needFlush)
{
    NG::ViewStackProcessor::GetInstance()->SetImplicitAnimationOption(option);
    if (needFlush) {
        NG::ViewStackProcessor::GetInstance()->FlushImplicitAnimation();
    }
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto pipelineContextBase = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContextBase);
    pipelineContextBase->CloseImplicitAnimation();
}

void ViewContextModelNG::openAnimation(const AnimationOption& option)
{
    NG::ViewStackProcessor::GetInstance()->SetImplicitAnimationOption(option);

    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto pipelineContextBase = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContextBase);
    pipelineContextBase->OpenImplicitAnimation(option, option.GetCurve(), option.GetOnFinishEvent());
}
} // namespace OHOS::Ace::NG
