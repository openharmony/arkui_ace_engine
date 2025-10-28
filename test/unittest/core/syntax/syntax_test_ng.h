/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_SYNTAX_SYNTAX_TEST_NG_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_SYNTAX_SYNTAX_TEST_NG_H

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "test/unittest/core/pattern/test_ng.h"

#define PRIVATE public
#define PROTECTED public
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"

#include "core/components_ng/syntax/for_each_model_ng.h"
#include "core/components_ng/syntax/for_each_node.h"
#include "core/components_ng/syntax/lazy_for_each_model_ng.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"
#include "core/components_ng/syntax/repeat_model_ng.h"
#include "core/components_ng/syntax/repeat_node.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_model_ng.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_node.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_2_model_ng.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_2_node.h"

#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/list/list_item_layout_property.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/waterflow/layout/water_flow_layout_algorithm_base.h"
#undef PRIVATE
#undef PROTECTED

namespace OHOS::Ace::NG {
enum class Scroller : std::string {
    SCROLLER = "Scroller",
    LIST = "List",
    GRID = "Grid",
    SWIPER = "Swiper",
    WATER_FLOW = "WaterFlow"
};

constexpr IF_ELSE = "IfElse";
enum class ForEachX : std::string {
    FOR_EACH = "ForEach",
    LAZY_FOR_EACH = "LazyForEach"
    REPEAT = "Repeat"
};

enum class TotalCount : uint32_t {
    EMPTY = 0,
    SINGLE = 1,
    MULTI = 5,
    MEDIUM = 50,
    LARGE = 500,
    VERY_LARGE = 5000
};

constexpr std::string TEXT_CONTEXT = "Hello, World!";
constexpr int32_t INDEX_0 = 0;
constexpr int32_t INDEX_1 = 1;
constexpr int32_t INDEX_2 = 2;
constexpr int32_t INDEX_3 = 3;
constexpr int32_t INDEX_4 = 4;
constexpr int32_t INDEX_5 = 5;
constexpr int32_t INDEX_9 = 9;

class SyntaxTestNg : public TestNG {
protected:
    void SetUp() override
    {
        MockPipelineContext::SetUp();
    }

    void TearDown() override
    {
        MockPipelineContext::TearDown();
    }

    RefPtr<FrameNode> GetMainFrameNode();

    // create basic nodes
    RefPtr<FrameNode> CreateTextNode(const std::string& content);
    RefPtr<FrameNode> CreateImageNode();

    // create scroller nodes
    RefPtr<FrameNode> CreateList();
    RefPtr<FrameNode> CreateGrid();
    RefPtr<FrameNode> CreateSwiper();
    RefPtr<FrameNode> CreateWaterFlow(WaterFlowLayoutMode mode = WaterFlowLayoutMode::TOP_DOWN);
    RefPtr<FrameNode> CreateScroller(const Scroller& parentTag);

    // create syntax nodes
    RefPtr<ForEachNode> CreateForEach();
    RefPtr<LazyForEachNode> CreateLazyForEach();
    RefPtr<RepeatNode> CreateRepeat();
    RefPtr<RepeatVirtualScrollNode> CreateRepeatVirtual();
    RefPtr<RepeatVirtualScroll2Node> CreateRepeatVirtual2();

    // create syntax nodes with children
    RefPtr<ForEachNode> CreateForEachWithChildren(const TotalCount totalCount);
    RefPtr<LazyForEachNode> CreateLazyForEachWithChildren(const TotalCount totalCount);
    RefPtr<RepeatNode> CreateRepeatWithChildren(const TotalCount totalCount);
    RefPtr<RepeatVirtualScrollNode> CreateRepeatVirtualWithChildren(const TotalCount totalCount);
    RefPtr<RepeatVirtualScroll2Node> CreateRepeatVirtual2WithChildren(const TotalCount totalCount);

    // create scroller with syntax nodes
    RefPtr<ForEachNode> CreateScrollerWithForEach(const Scroller& parentTag, const TotalCount totalCount);
    RefPtr<LazyForEachNode> CreateScrollerWithLazyForEach(const Scroller& parentTag, const TotalCount totalCount);
    RefPtr<RepeatNode> CreateScrollerWithRepeat(const Scroller& parentTag, const TotalCount totalCount);
    RefPtr<RepeatVirtualScrollNode> CreateScrollerWithRepeatVirtual(
        const Scroller& parentTag, const TotalCount totalCount);
    RefPtr<RepeatVirtualScroll2Node> CreateScrollerWithRepeatVirtual2(
        const Scroller& parentTag, const TotalCount totalCount);

private:
    RefPtr<FrameNode> listNode_;
    RefPtr<FrameNode> gridNode_;
    RefPtr<FrameNode> swiperNode_;
    RefPtr<FrameNode> waterFlowNode_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_SYNTAX_SYNTAX_TEST_NG_H