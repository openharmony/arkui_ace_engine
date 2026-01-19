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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_PIXEL_ROUND_TEST_NG_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_PIXEL_ROUND_TEST_NG_H

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_rosen_render_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/flex/flex_model_ng.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

class PixelRoundTestNg : public TestNG {
public:
    void SetUp() override {}
    void TearDown() override {}
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
        MockContainer::SetUp();
        MockContainer::Current()->GetTaskExecutor() = AceType::MakeRefPtr<MockTaskExecutor>();
        MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
    }

    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
        MockContainer::TearDown();
    }

    RefPtr<FrameNode> CreateFlex(const std::function<void(FlexModelNG)>& callback)
    {
        FlexModelNG model;
        model.CreateFlexRow();
        if (callback) {
            callback(model);
        }
        RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
        ViewStackProcessor::GetInstance()->PopContainer();
        return AceType::DynamicCast<FrameNode>(element);
    }
};
} // namespace OHOS::Ace::NG
#endif