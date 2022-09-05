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

#include "core/components_ng/syntax/lazy_layout_wrapper_builder.h"

#include <list>

#include "base/log/ace_trace.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"

namespace OHOS::Ace::NG {

LazyLayoutWrapperBuilder::LazyLayoutWrapperBuilder(
    const RefPtr<LazyForEachBuilder>& builder, const WeakPtr<LazyForEachNode>& host)
    : builder_(builder), host_(host)
{}

void LazyLayoutWrapperBuilder::SwapDirtyAndUpdateBuildCache()
{
    auto host = host_.Upgrade();
    CHECK_NULL_VOID(host);
    std::list<int32_t> indexes;
    for (const auto& child : buildItems_) {
        if (child.second->IsActive()) {
            child.second->SwapDirtyLayoutWrapperOnMainThread();
            indexes.emplace_back(child.first);
        }
    }
    host->UpdateCachedItems(indexes);
}

int32_t LazyLayoutWrapperBuilder::OnGetTotalCount()
{
    if (!builder_) {
        return 0;
    }
    return builder_->GetTotalCount();
}

RefPtr<LayoutWrapper> LazyLayoutWrapperBuilder::OnGetOrCreateWrapperByIndex(int32_t index)
{
    if ((index < 0) || (index >= GetTotalCount())) {
        LOGE("index is illegal: %{public}d", index);
        return nullptr;
    }
    CHECK_NULL_RETURN(builder_, nullptr);
    auto uiNode = builder_->GetChildByIndex(index);
    CHECK_NULL_RETURN(uiNode, nullptr);
    auto frameNode = DynamicCast<FrameNode>(uiNode);
    if (frameNode) {
        return frameNode->CreateLayoutWrapperOnCreate();
    }
    // TODO: Check only ifelse syntax node can use LazyForEach and get wrapper from ifelse syntax node.
    return nullptr;
}

std::list<RefPtr<LayoutWrapper>> LazyLayoutWrapperBuilder::OnExpandChildLayoutWrapper()
{
    std::list<RefPtr<LayoutWrapper>> items;
    CHECK_NULL_RETURN(builder_, items);
    auto total = GetTotalCount();
    for (int32_t index = 0; index < total; ++index) {
        auto wrapper = OnGetOrCreateWrapperByIndex(index);
        if (!wrapper) {
            LOGE("fail to create wrapper");
            continue;
        }
        items.emplace_back(wrapper);
    }
    return items;
}

} // namespace OHOS::Ace::NG