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

#include "bridge/declarative_frontend/jsview/models/list_item_group_model_impl.h"

#include "base/memory/referenced.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "core/components_v2/list/list_item_group_component.h"

namespace OHOS::Ace::Framework {

void ListItemGroupModelImpl::Create(V2::ListItemGroupStyle listItemGroupStyle)
{
    auto listItemGroupComponent = AceType::MakeRefPtr<V2::ListItemGroupComponent>();
    ViewStackProcessor::GetInstance()->Push(listItemGroupComponent);
}

void ListItemGroupModelImpl::SetSpace(const Dimension& space)
{
    JSViewSetProperty(&V2::ListItemGroupComponent::SetSpace, space);
}

void ListItemGroupModelImpl::SetDivider(const V2::ItemDivider& divider)
{
    auto dividerPtr = std::make_unique<V2::ItemDivider>(divider);
    JSViewSetProperty(&V2::ListItemGroupComponent::SetItemDivider, std::move(dividerPtr));
}

void ListItemGroupModelImpl::SetHeader(std::function<void()>&& header)
{
    auto listItemGroup =
        AceType::DynamicCast<V2::ListItemGroupComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!listItemGroup) {
        LOGW("Failed to get '%{public}s' in view stack", AceType::TypeName<V2::ListItemGroupComponent>());
        return;
    }
    if (header) {
        ScopedViewStackProcessor builderViewStackProcessor;
        header();
        RefPtr<Component> customComponent = ViewStackProcessor::GetInstance()->Finish();
        listItemGroup->SetHeaderComponent(customComponent);
    }
}

void ListItemGroupModelImpl::SetFooter(std::function<void()>&& footer)
{
    auto listItemGroup =
        AceType::DynamicCast<V2::ListItemGroupComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!listItemGroup) {
        LOGW("Failed to get '%{public}s' in view stack", AceType::TypeName<V2::ListItemGroupComponent>());
        return;
    }
    if (footer) {
        ScopedViewStackProcessor builderViewStackProcessor;
        footer();
        RefPtr<Component> customComponent = ViewStackProcessor::GetInstance()->Finish();
        listItemGroup->SetFooterComponent(customComponent);
    }
}

} // namespace OHOS::Ace::Framework
