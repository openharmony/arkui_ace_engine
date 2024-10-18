/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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

#ifndef OHOS_ACE_COMPONENT_TEST_MANAGER_H
#define OHOS_ACE_COMPONENT_TEST_MANAGER_H

#include "component_test/test_result_recorder.h"
#include "component_test/test_task_scheduler.h"

#include "base/memory/referenced.h"

namespace OHOS::Ace::ComponentTest {
class ComponentTestManager : public AceType {
public:
    virtual void PostUITask(std::function<void(void*)>&& task, std::function<void(void*)>&& onFinish,
        void* data = nullptr, uint32_t delay = 0) = 0;
    virtual void PostJSTask(std::function<void(void*)>&& task, std::function<void(void*)>&& onFinish,
        void* data = nullptr, uint32_t delay = 0) = 0;
    virtual void SetTestCaseAttribute(TestCaseAttribute attribute) = 0;
    virtual void Record(std::string info, std::string position, Result result) = 0;
    virtual void Finish() = 0;
    virtual void ClaimLongOperation() = 0;
    virtual void LongOperationComplete() = 0;
    virtual void RequestContinuousIdleStatusNotification(IdleNotifycallback&& notifycallback) = 0;
    virtual ~ComponentTestManager() = default;
};
} // namespace OHOS::Ace::ComponentTest

#endif // OHOS_ACE_COMPONENT_TEST_MANAGER_H
