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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_PIPELINE_CONTEXT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_PIPELINE_CONTEXT_H

#include "gmock/gmock.h"

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
class MockPipelineContext : public PipelineContext {
    DECLARE_ACE_TYPE(MockPipelineContext, PipelineContext);

public:
    MockPipelineContext() = default;
    ~MockPipelineContext() override = default;

    static void SetUp();
    static void TearDown();
    static void SetCurrentWindowRect(Rect rect);
    static RefPtr<MockPipelineContext> GetCurrent();
    void SetRootSize(double rootWidth, double rootHeight);
    void SetInstanceId(int32_t instanceId);

    MOCK_CONST_METHOD0(GetSafeAreaWithoutProcess, SafeAreaInsets());
    MOCK_METHOD(void, FlushUITasks, (bool triggeredByImplicitAnimation), (override));
    MOCK_METHOD(float, GetFontScale, ());
    MOCK_METHOD(SafeAreaInsets, GetSafeArea, (), (const));

    bool GetIsDeclarative() const override
    {
        return isDeclarative_;
    }

    static RefPtr<MockPipelineContext> pipeline_;

protected:
    float fontScale_ = 1.0f;
    bool isDeclarative_ = false;
    double dipScale_ = 1.0;
    RefPtr<TaskExecutor> taskExecutor_;
};
} // namespace OHOS::Ace::NG

namespace OHOS::Ace {
    void SetBoolStatus(bool value);
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_PIPELINE_CONTEXT_H
