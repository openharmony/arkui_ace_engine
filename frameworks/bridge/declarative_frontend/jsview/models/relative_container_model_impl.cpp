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

#include "bridge/declarative_frontend/jsview/models/relative_container_model_impl.h"

#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"

namespace OHOS::Ace::Framework {

void RelativeContainerModelImpl::Create()
{
    std::list<RefPtr<Component>> children;
    RefPtr<OHOS::Ace::RelativeContainerComponent> component = AceType::MakeRefPtr<RelativeContainerComponent>(children);
    ViewStackProcessor::GetInstance()->Push(component);
    JSInteractableView::SetFocusNode(true);
}

} // namespace OHOS::Ace::Framework