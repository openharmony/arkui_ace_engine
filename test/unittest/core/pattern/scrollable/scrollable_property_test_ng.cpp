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
#include "scrollable_test_ng.h"

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pattern/mock_nestable_scroll_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/scrollable/mock_scrollable.h"
#define protected public
#define private public
#include "core/components_ng/pattern/refresh/refresh_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"

namespace OHOS::Ace::NG {
/**
 * @tc.name: SetParentNestedScroll001
 * @tc.desc: Test SetParentNestedScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, SetParentNestedScroll001, TestSize.Level1)
{
    /**
     *@Tc. steps: The first step. Initialize ScrollablePattern type pointer
     *@Tc. inspected: The nested binding relationship of the component is not empty
     */
    auto pattern = scroll_->GetPattern<PartiallyMockedScrollable>();
    ASSERT_NE(pattern, nullptr);
    auto scrollProxy = AceType::MakeRefPtr<ScrollBarProxy>();
    pattern->nestScrollBarProxy_.clear();
    pattern->AddNestScrollBarProxy(scrollProxy);
    auto scroll = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 0, AceType::MakeRefPtr<PartiallyMockedScrollable>());
    ASSERT_NE(scroll, nullptr);
    auto scrollPnTest = scroll->GetPattern<ScrollablePattern>();
    pattern->SetParentNestedScroll(scrollPnTest);
    EXPECT_EQ(pattern->nestScrollBarProxy_.size(), 1);
}

/**
 * @tc.name: UnsetParentNestedScroll001
 * @tc.desc: Test UnsetParentNestedScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, UnsetParentNestedScroll001, TestSize.Level1)
{
    /**
     *@Tc. steps: The first step. Initialize ScrollablePattern type pointer
     *@Tc. inspected: Component unbinding relationship
     */
    auto pattern = scroll_->GetPattern<PartiallyMockedScrollable>();
    ASSERT_NE(pattern, nullptr);
    auto scrollProxy = AceType::MakeRefPtr<ScrollBarProxy>();
    pattern->nestScrollBarProxy_.clear();
    pattern->AddNestScrollBarProxy(scrollProxy);
    auto scroll = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 0, AceType::MakeRefPtr<PartiallyMockedScrollable>());
    ASSERT_NE(scroll, nullptr);
    auto scrollPnTest = scroll->GetPattern<ScrollablePattern>();
    pattern->scrollBarProxy_ = scrollProxy;
    pattern->SetParentNestedScroll(scrollPnTest);
    ASSERT_NE(scrollPnTest->nestScrollBarProxy_.size(), 0);
    ASSERT_NE(scrollPnTest->scrollBarProxy_, nullptr);
    pattern->UnsetParentNestedScroll(scrollPnTest);
    ASSERT_EQ(scrollPnTest->nestScrollBarProxy_.size(), 0);
}

/**
 * @tc.name: DeleteNestScrollBarProxy001
 * @tc.desc: Test DeleteNestScrollBarProxy
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, DeleteNestScrollBarProxy001, TestSize.Level1)
{
    /**
     *@Tc. steps: The first step. Initialize ScrollablePattern type pointer
     *@Tc. inspected: After unbinding, the binding relationship is empty
     */
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    ASSERT_NE(scrollPn, nullptr);
    auto scrollProxy = AceType::MakeRefPtr<ScrollBarProxy>();
    scrollPn->nestScrollBarProxy_.clear();
    scrollPn->AddNestScrollBarProxy(scrollProxy);
    scrollPn->DeleteNestScrollBarProxy(scrollProxy);
    EXPECT_EQ(scrollPn->nestScrollBarProxy_.size(), 0);
}
} // namespace OHOS::Ace::NG