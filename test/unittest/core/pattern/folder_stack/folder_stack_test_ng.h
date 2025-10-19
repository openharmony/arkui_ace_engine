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

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_TEST_UNITTEST_CORE_PATTERN_FOLDER_STACK_FOLDER_STACK_TEST_NG_H
#define FOUNDATION_ARKUI_ACE_ENGINE_TEST_UNITTEST_CORE_PATTERN_FOLDER_STACK_FOLDER_STACK_TEST_NG_H

#include "gtest/gtest.h"

#include "core/components/common/properties/alignment.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/blank/blank_model_ng.h"

#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/blank/blank_model_ng.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_layout_algorithm.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_layout_property.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_model_ng.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_pattern.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace {
    using namespace testing;
    using namespace testing::ext;
}
namespace OHOS::Ace::NG {

namespace {
constexpr float ZERO = 0.0f;
const OffsetF ORIGIN_POINT(ZERO, ZERO);
constexpr float STACK_HEIGHT = 120.0f;
constexpr float FULL_SCREEN_WIDTH = 2224.0f;
constexpr float FULL_SCREEN_HEIGHT = 2496.0f;
const SizeF CONTAINER_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);

constexpr float SMALL_ITEM_WIDTH = 100.0f;
constexpr float SMALL_ITEM_HEIGHT = 40.0f;
constexpr int CALLBACK_ID = 1;
const SizeF SMALL_ITEM_SIZE(SMALL_ITEM_WIDTH, SMALL_ITEM_HEIGHT);
} // namespace

class FolderStackTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockContainer::SetUp();
        MockPipelineContext::SetUp();
    }

    static void TearDownTestSuite()
    {
        MockContainer::TearDown();
        MockPipelineContext::TearDown();
    }

    RefPtr<FrameNode> CreateFolder(const std::function<void(FolderStackModelNG)>& callback)
    {
        FolderStackModelNG model;
        model.Create();
        if (callback) {
            callback(model);
        }
        RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
        ViewStackProcessor::GetInstance()->PopContainer();
        return AceType::DynamicCast<FrameNode>(element);
    }

    RefPtr<FrameNode> CreateStack(const std::function<void(StackModelNG)>& callback)
    {
        StackModelNG model;
        model.Create();
        if (callback) {
            callback(model);
        }
        RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
        ViewStackProcessor::GetInstance()->PopContainer();
        return AceType::DynamicCast<FrameNode>(element);
    }

    void FlushUITasks(const RefPtr<FrameNode>& frameNode)
    {
        frameNode->SetActive();
        frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        MockPipelineContext::GetCurrent()->FlushUITasks();
    }

protected:
    // std::pair<RefPtr<FrameNode>, RefPtr<LayoutWrapperNode>> CreateStack(const Alignment alignment);
    RefPtr<UINode> CreateWithItem(bool enableAnimation, bool autoHalfFold, Alignment align);
    PaddingProperty CreatePadding(float left, float top, float right, float bottom);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ARKUI_ACE_ENGINE_TEST_UNITTEST_CORE_PATTERN_FOLDER_STACK_FOLDER_STACK_TEST_NG_H