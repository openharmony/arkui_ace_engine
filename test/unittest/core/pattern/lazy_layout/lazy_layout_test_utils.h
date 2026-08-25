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

#ifndef TEST_UNITTEST_CORE_PATTERN_LAZY_LAYOUT_LAZY_LAYOUT_TEST_UTILS_H
#define TEST_UNITTEST_CORE_PATTERN_LAZY_LAYOUT_LAZY_LAYOUT_TEST_UTILS_H

#include <array>
#include <string>

#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/lazy_layout/lazy_layout_utils.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_property.h"
#include "core/components_ng/pattern/waterflow/water_flow_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

enum class LazyScrollableParentType {
    LIST,
    WATER_FLOW,
    SCROLL,
};

struct LazyScrollableParentCase {
    const char* name;
    const char* tag;
    LazyScrollableParentType type;
};

constexpr std::array<LazyScrollableParentCase, 3> CACHED_LAZY_PARENT_CASES = {{
    { "List", V2::LIST_ETS_TAG, LazyScrollableParentType::LIST },
    { "WaterFlow", V2::WATERFLOW_ETS_TAG, LazyScrollableParentType::WATER_FLOW },
    { "Scroll", V2::SCROLL_ETS_TAG, LazyScrollableParentType::SCROLL },
}};

struct CachedLazyParentTestContext {
    RefPtr<FrameNode> parentNode;
    RefPtr<FrameNode> intermediateNode;
    RefPtr<FrameNode> lazyNode;
    RefPtr<LayoutWrapperNode> layoutWrapper;
};

struct CachedLazyLayoutTestContext {
    RefPtr<FrameNode> parent;
    RefPtr<FrameNode> host;
    RefPtr<LayoutWrapperNode> wrapper;
    LayoutConstraintF parentConstraint;
};

constexpr int32_t CACHED_LAZY_PARENT_NODE_ID = -3000;
constexpr int32_t CACHED_LAZY_HOST_NODE_ID = -3001;

void AppendFixedHeightChild(
    const RefPtr<LayoutWrapperNode>& parent, int32_t nodeId, float height, int32_t& measureCount);

CachedLazyLayoutTestContext CreateCachedLazyLayoutTestContext(const std::string& lazyTag,
    const RefPtr<Pattern>& lazyPattern, const RefPtr<LayoutAlgorithm>& algorithm, const SizeF& viewportSize);

inline RefPtr<Pattern> CreateLazyScrollableParentPattern(LazyScrollableParentType type)
{
    switch (type) {
        case LazyScrollableParentType::LIST:
            return AceType::MakeRefPtr<ListPattern>();
        case LazyScrollableParentType::WATER_FLOW:
            return AceType::MakeRefPtr<WaterFlowPattern>();
        case LazyScrollableParentType::SCROLL:
            return AceType::MakeRefPtr<ScrollPattern>();
        default:
            return nullptr;
    }
}

template<typename LazyPattern>
CachedLazyParentTestContext CreateCachedLazyParentTestContext(
    const LazyScrollableParentCase& parentCase, const char* lazyTag, int32_t& nodeId)
{
    CachedLazyParentTestContext context;
    auto parentPattern = CreateLazyScrollableParentPattern(parentCase.type);
    if (!parentPattern) {
        return context;
    }
    context.parentNode = FrameNode::CreateFrameNode(parentCase.tag, nodeId--, parentPattern);
    if (!context.parentNode) {
        return context;
    }
    auto scrollablePattern = context.parentNode->GetPattern<ScrollablePattern>();
    if (!scrollablePattern) {
        return context;
    }
    scrollablePattern->SetAxis(Axis::VERTICAL);

    context.lazyNode = FrameNode::CreateFrameNode(lazyTag, nodeId--, AceType::MakeRefPtr<LazyPattern>());
    const char* intermediateTag = parentCase.type == LazyScrollableParentType::WATER_FLOW
        ? V2::FLOW_ITEM_ETS_TAG
        : V2::COMMON_VIEW_ETS_TAG;
    context.intermediateNode =
        FrameNode::CreateFrameNode(intermediateTag, nodeId--, AceType::MakeRefPtr<Pattern>());
    if (!context.lazyNode || !context.intermediateNode) {
        return context;
    }
    context.intermediateNode->MountToParent(context.parentNode, DEFAULT_NODE_SLOT, true);
    context.layoutWrapper = context.lazyNode->CreateLayoutWrapper();
    return context;
}

} // namespace OHOS::Ace::NG

#endif // TEST_UNITTEST_CORE_PATTERN_LAZY_LAYOUT_LAZY_LAYOUT_TEST_UTILS_H
