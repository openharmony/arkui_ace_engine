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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOR_EACH_FOR_EACH_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOR_EACH_FOR_EACH_MODEL_NG_H

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/syntax/lazy_for_each_builder.h"
#include "core/components_ng/syntax/lazy_for_each_model.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT LazyForEachModelNG : public LazyForEachModel {
public:
    void Create(const RefPtr<LazyForEachActuator>& actuator) override
    {
        auto builder = AceType::DynamicCast<LazyForEachBuilder>(actuator);
        Create(builder);
    }

    void OnMove(std::function<void(int32_t, int32_t)>&& onMove) override
    {
        auto* stack = ViewStackProcessor::GetInstance();
        auto node = AceType::DynamicCast<LazyForEachNode>(stack->GetMainElementNode());
        CHECK_NULL_VOID(node);
        node->SetOnMove(std::move(onMove));
    }

    void SetItemDragHandler(std::function<void(int32_t)>&& onLongPress, std::function<void(int32_t)>&& onDragStart,
        std::function<void(int32_t, int32_t)>&& onMoveThrough, std::function<void(int32_t)>&& onDrop) override
    {
        auto* stack = ViewStackProcessor::GetInstance();
        auto node = AceType::DynamicCast<LazyForEachNode>(stack->GetMainElementNode());
        CHECK_NULL_VOID(node);
        node->SetItemDragHandler(
            std::move(onLongPress), std::move(onDragStart), std::move(onMoveThrough), std::move(onDrop));
    }

private:
    void Create(const RefPtr<LazyForEachBuilder>& forEachBuilder)
    {
        auto* stack = ViewStackProcessor::GetInstance();
        auto nodeId = stack->ClaimNodeId();

        if (stack->GetMainFrameNode() && stack->GetMainFrameNode()->GetTag() == V2::TABS_ETS_TAG) {
            forEachBuilder->ExpandChildrenOnInitial();
            return;
        }

        auto lazyForEach = LazyForEachNode::GetOrCreateLazyForEachNode(nodeId, forEachBuilder);
        stack->Push(lazyForEach);
    }
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOR_EACH_FOR_EACH_MODEL_NG_H
