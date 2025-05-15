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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_SYNTAX_REPEAT_VIRTUAL_2_TEST_NG_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_SYNTAX_REPEAT_VIRTUAL_2_TEST_NG_H

#include <optional>
#include <utility>

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"

#define private public
#define protected public
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_2_model_ng.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_2_node.h"
#include "core/components_ng/pattern/list/list_item_layout_property.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#undef private
#undef protected

namespace OHOS::Ace::NG {
class RepeatVirtual2TestNg : public testing::Test {
public:
    void SetUp() override
    {
        MockPipelineContext::SetUp();
    }

    void TearDown() override
    {
        MockPipelineContext::TearDown();
    }

    RefPtr<FrameNode> CreateNode(const std::string& tag);

    RefPtr<RepeatVirtualScroll2Node> CreateRepeatVirtualNode(uint32_t totalCount);

    // create ListItemNode with 2 Text Node inside
    RefPtr<FrameNode> CreateListItemNode();

    ElementIdType GetElmtId()
    {
        elmtId_++;
        return elmtId_;
    }

    ElementIdType elmtId_ = 10000;

    /**
     * Map: Repeat node index -> L1 cache repeat node rid
     */
    std::map<IndexType, RIDType> l1Rid4Index_;
    /**
     * Function needed by RepeatVirtualScrollCaches constructor is special test case
     */
    std::function<std::pair<RIDType, uint32_t>(IndexType)> onGetRid4Index_;
    std::function<void(IndexType, IndexType)> onRecycleItems_;
    std::function<void(int32_t, int32_t, int32_t, int32_t, bool)> onActiveRange_;
    std::function<void(IndexType, IndexType)> onMoveFromTo_;
    std::function<void()> onPurge_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_SYNTAX_REPEAT_VIRTUAL_2_TEST_NG_H