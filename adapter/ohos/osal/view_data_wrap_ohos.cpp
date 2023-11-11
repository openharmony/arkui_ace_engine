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

#include "view_data_wrap_ohos.h"

#include "base/utils/utils.h"

namespace OHOS::Ace {
RefPtr<PageNodeInfoWrap> PageNodeInfoWrap::CreatePageNodeInfoWrap()
{
    return AceType::MakeRefPtr<PageNodeInfoWrapOhos>();
}

const AbilityBase::PageNodeInfo& PageNodeInfoWrapOhos::GetPageNodeInfo() const
{
    return pageNodeInfo_;
}

RefPtr<ViewDataWrap> ViewDataWrap::CreateViewDataWrap()
{
    return AceType::MakeRefPtr<ViewDataWrapOhos>();
}

RefPtr<ViewDataWrap> ViewDataWrap::CreateViewDataWrap(const AbilityBase::ViewData& viewData)
{
    return AceType::MakeRefPtr<ViewDataWrapOhos>(viewData);
}

ViewDataWrapOhos::ViewDataWrapOhos(const AbilityBase::ViewData& viewData): viewData_(viewData)
{
    for (const auto& node: viewData.nodes) {
        pageNodeInfoWraps_.emplace_back(AceType::MakeRefPtr<PageNodeInfoWrapOhos>(node));
    }
}

const AbilityBase::ViewData& ViewDataWrapOhos::GetViewData()
{
    viewData_.nodes.clear();
    for (const auto& nodeWrap: pageNodeInfoWraps_) {
        auto nodeWrapOhos = AceType::DynamicCast<PageNodeInfoWrapOhos>(nodeWrap);
        if (nodeWrapOhos) {
            viewData_.nodes.emplace_back(nodeWrapOhos->GetPageNodeInfo());
        }
    }
    return viewData_;
}
} // namespace OHOS::Ace
