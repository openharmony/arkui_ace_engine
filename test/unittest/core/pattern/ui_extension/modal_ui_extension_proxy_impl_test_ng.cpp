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

#include "gtest/gtest.h"
#include "base/memory/ace_type.h"
#define private public
#define protected public
#include "core/components_ng/pattern/ui_extension/ui_extension_component/modal_ui_extension_proxy_impl.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_component/session_wrapper_impl.h"
#include "core/components_ng/pattern/ui_extension/session_wrapper_factory.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
    NG::SessionType sessionType = NG::SessionType::UI_EXTENSION_ABILITY;
} // namespace

class ModalUIExtensionProxyImplTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
};

void ModalUIExtensionProxyImplTestNg::SetUp() {}

void ModalUIExtensionProxyImplTestNg::TearDown() {}

/**
 * @tc.name: ModalUIExtensionProxyImplTest001
 * @tc.desc: Test ModalUIExtensionProxyImplTestNg SendData
 * @tc.type: FUNC
 */
HWTEST_F(ModalUIExtensionProxyImplTestNg, ModalUIExtensionProxyImplTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize ModalUIExtensionProxyImpl
     */
    auto hostPattern = WeakPtr<UIExtensionPattern>();
    int32_t instanceId = 1;
    bool isTransferringCaller = false;
    RefPtr<SessionWrapper> sessionWrapper = SessionWrapperFactory::CreateSessionWrapper(
        sessionType, hostPattern, instanceId, isTransferringCaller);
    ASSERT_EQ(sessionWrapper, nullptr);
    auto proxy = std::make_shared<ModalUIExtensionProxyImpl>(sessionWrapper);
    ASSERT_EQ(proxy->sessionWrapper_, nullptr);

    /**
     * @tc.steps: step2. initialize SendData
     */
    AAFwk::WantParams wantParams;
    proxy->SendData(wantParams);
}
} // namespace OHOS::Ace::NG