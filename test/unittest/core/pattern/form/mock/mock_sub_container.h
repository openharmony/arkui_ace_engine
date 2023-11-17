/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_PATTERN_FORM_MOCK_MOCK_SUB_CONTAINER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_PATTERN_FORM_MOCK_MOCK_SUB_CONTAINER_H

#include <string>

#include "gmock/gmock.h"

#include "core/components/form/sub_container.h"

namespace OHOS::Ace {
class MockSubContainer : public SubContainer {
public:
    MockSubContainer(const WeakPtr<PipelineBase>& context) : SubContainer(context) {}
    MockSubContainer(const WeakPtr<PipelineBase>& context, int32_t instanceId) : SubContainer(context, instanceId) {}
    ~MockSubContainer() override = default;

    MOCK_METHOD8(
        RunCard, void(int64_t formId, const std::string& path, const std::string& module, const std::string& data,
                     const std::map<std::string, sptr<AppExecFwk::FormAshmem>>& imageDataMap,
                     const std::string& formSrc, const FrontendType& cardType, const FrontendType& uiSyntax));
    MOCK_METHOD0(RunSameCard, void());
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_PATTERN_FORM_MOCK_MOCK_SUB_CONTAINER_H