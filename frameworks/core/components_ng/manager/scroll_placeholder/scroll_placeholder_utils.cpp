/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/manager/scroll_placeholder/scroll_placeholder_utils.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {
constexpr int32_t MAX_HOST_SEARCH_DEPTH = 32;
} // namespace

RefPtr<ScrollPlaceholderManager> ScrollPlaceholderUtils::GetManager(const RefPtr<UINode>& node)
{
    CHECK_NULL_RETURN(node, nullptr);
    return GetManager(node->GetContext());
}

RefPtr<ScrollPlaceholderManager> ScrollPlaceholderUtils::GetManager(PipelineContext* context)
{
    CHECK_NULL_RETURN(context, nullptr);
    return context->GetScrollPlaceholderManager();
}

bool ScrollPlaceholderUtils::IsScrollContainerTag(const std::string& tag)
{
    return tag == V2::LIST_ETS_TAG || tag == V2::GRID_ETS_TAG || tag == V2::WATERFLOW_ETS_TAG;
}

RefPtr<FrameNode> ScrollPlaceholderUtils::FindEnabledHost(const RefPtr<UINode>& start)
{
    CHECK_NULL_RETURN(start, nullptr);
    auto manager = GetManager(start);
    CHECK_NULL_RETURN(manager, nullptr);
    auto current = start->GetParent();
    int32_t depth = 0;
    while (current && depth < MAX_HOST_SEARCH_DEPTH) {
        ++depth;
        auto frame = AceType::DynamicCast<FrameNode>(current);
        if (frame && IsScrollContainerTag(frame->GetTag())) {
            if (manager->IsContainerRegistered(frame->GetId())) {
                return frame;
            }
            // A scroll container without the attribute terminates the search:
            // the feature is opt-in per container.
            return nullptr;
        }
        current = current->GetParent();
    }
    return nullptr;
}

bool ScrollPlaceholderUtils::ShouldContinuePlaceholderLayout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_RETURN(layoutWrapper, false);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, false);
    auto manager = GetManager(host);
    CHECK_NULL_RETURN(manager, false);
    return manager->ShouldContinuePlaceholderLayout(host->GetId());
}

void ScrollPlaceholderUtils::NotifyPlaceholderDataChanged(const RefPtr<UINode>& lazyNode)
{
    auto host = FindEnabledHost(lazyNode);
    CHECK_NULL_VOID(host);
    auto manager = GetManager(host);
    CHECK_NULL_VOID(manager);
    manager->NotifyDataChanged(host->GetId());
}

} // namespace OHOS::Ace::NG
