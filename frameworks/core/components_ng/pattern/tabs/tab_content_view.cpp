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

#include "core/components_ng/pattern/tabs/tab_content_view.h"

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/tabs/tab_content_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
namespace {

constexpr char DEFAULT_TAB_BAR_NAME[] = "TabBar";

} // namespace

void TabContentView::Create(std::function<void(int32_t)>&& deepRenderFunc)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto deepRender = [nodeId, deepRenderFunc = std::move(deepRenderFunc)]() -> RefPtr<UINode> {
        CHECK_NULL_RETURN(deepRenderFunc, nullptr);
        deepRenderFunc(nodeId);
        auto deepChild = ViewStackProcessor::GetInstance()->Finish();
        auto parent = FrameNode::GetOrCreateFrameNode(V2::TAB_CONTENT_ITEM_ETS_TAG, nodeId, nullptr);
        if (deepChild && parent) {
            deepChild->MountToParent(parent);
        }
        return deepChild;
    };
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::TAB_CONTENT_ITEM_ETS_TAG, nodeId,
        [shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(std::move(deepRender))]() {
            return AceType::MakeRefPtr<TabContentPattern>(shallowBuilder);
        });
    stack->Push(frameNode);
    SetTabBar(DEFAULT_TAB_BAR_NAME, ""); // Set default tab bar.
}

void TabContentView::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = (stack == nullptr ? 0 : stack->ClaimNodeId());
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::TAB_CONTENT_ITEM_ETS_TAG, nodeId,
        []() { return AceType::MakeRefPtr<TabContentPattern>(nullptr); });
    stack->Push(frameNode);
}

void TabContentView::Pop()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto tabBarParam = stack->PopTabBar();
    if (tabBarParam.text.empty()) {
        LOGW("Text is empty.");
        return;
    }

    auto tabsNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(tabsNode);
    auto tabBarNode = tabsNode->GetChildren().front();
    CHECK_NULL_VOID(tabBarNode);

    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateContent(tabBarParam.text);
    textLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
    textLayoutProperty->UpdateMaxLines(1);
    textLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    textNode->MountToParent(tabBarNode);
    textNode->MarkModifyDone();
}

void TabContentView::SetTabBar(const std::string& text, const std::string& icon)
{
    TabBarParam tabBarParam { .text = text, .icon = icon };
    ViewStackProcessor::GetInstance()->PushTabBar(tabBarParam);
}

} // namespace OHOS::Ace::NG
