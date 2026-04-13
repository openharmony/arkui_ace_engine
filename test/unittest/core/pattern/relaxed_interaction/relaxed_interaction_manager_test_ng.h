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

#ifndef TEST_UNITTEST_CORE_PATTERN_RELAXED_INTERACTION_RELAXED_INTERACTION_MANAGER_TEST_NG_H
#define TEST_UNITTEST_CORE_PATTERN_RELAXED_INTERACTION_RELAXED_INTERACTION_MANAGER_TEST_NG_H

#include <string>

#include "gtest/gtest.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/relaxed_interaction/relaxed_interaction_manager.h"

namespace OHOS::Ace::NG {

class RelaxedInteractionManagerTestBase : public testing::Test {
public:
    static void SetUpTestCase()
    {
        mockPipelineContext_ = AceType::MakeRefPtr<MockPipelineContext>();
        ASSERT_NE(mockPipelineContext_, nullptr);
    }

    static void TearDownTestCase()
    {
        mockPipelineContext_.Reset();
        manager_.Reset();
    }

protected:
    inline static RefPtr<PipelineContext> mockPipelineContext_ = nullptr;
    inline static RefPtr<RelaxedInteractionManager> manager_ = nullptr;
};

} // namespace OHOS::Ace::NG

#endif