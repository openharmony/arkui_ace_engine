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

#include "bridge/declarative_frontend/jsview/models/remote_window_model_impl.h"

#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/remote_window/remote_window_component.h"

namespace OHOS::Ace::Framework {
void RemoteWindowModelImpl::Create(const std::shared_ptr<OHOS::Rosen::RSNode>& rsNode)
{
    auto specializedComponent = AceType::MakeRefPtr<OHOS::Ace::RemoteWindowComponent>();
    CHECK_NULL_VOID(specializedComponent);
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_VOID(stack);
    stack->Push(specializedComponent);
    specializedComponent->SetExternalRSNode(rsNode);
}
} // namespace OHOS::Ace::Framework
