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

#include "gtest/gtest.h"
#define private public
#define protected public

#include "ability_context_impl.h"
#include "adapter/ohos/entrance/rs_adapter.h"
#include "base/utils/system_properties.h"
#include "command/rs_base_node_command.h"


using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class RsAdapterTest : public testing::Test {
public:
    static bool multiInstanceEnabledSaved_;

    static void SetUpTestSuite()
    {
        RsAdapterTest::multiInstanceEnabledSaved_ = SystemProperties::GetMultiInstanceEnabled();
    }
    static void TearDownTestSuite()
    {
        SystemProperties::SetMultiInstanceEnabled(RsAdapterTest::multiInstanceEnabledSaved_);
    }
    void SetUp() {};
    void TearDown() {};
};

bool RsAdapterTest::multiInstanceEnabledSaved_ = false;

/**
 * @tc.name: RsUIDirectorInit001
 * @tc.desc: Test RsAdapterTest
 * @tc.type: FUNC
 */
HWTEST_F(RsAdapterTest, RsUIDirectorInit001, TestSize.Level1)
{
#ifdef ENABLE_ROSEN_BACKEND
    std::shared_ptr<OHOS::Rosen::RSUIDirector> rsUiDirector;
    OHOS::sptr<OHOS::Rosen::WindowOption> windowOption = new OHOS::Rosen::WindowOption();
    windowOption->SetWindowType(Rosen::WindowType::WINDOW_TYPE_TRANSPARENT_VIEW);
    auto context = std::make_shared<AbilityRuntime::AbilityContextImpl>();
    sptr<OHOS::Rosen::Window> window = OHOS::Rosen::Window::Create("test", windowOption, context);

    EXPECT_NE(window, nullptr);

    SystemProperties::SetMultiInstanceEnabled(false);
    RsAdapter::RsUIDirectorInit(rsUiDirector, window, "");

    EXPECT_NE(rsUiDirector, nullptr);
    EXPECT_EQ(rsUiDirector->GetRSUIContext(), nullptr);

    EXPECT_EQ(OHOS::Rosen::WMError::WM_OK, window->Destroy());
#endif
}

/**
 * @tc.name: RsUIDirectorInit002
 * @tc.desc: Test RsAdapterTest
 * @tc.type: FUNC
 */
HWTEST_F(RsAdapterTest, RsUIDirectorInit002, TestSize.Level1)
{
#ifdef ENABLE_ROSEN_BACKEND
    std::shared_ptr<OHOS::Rosen::RSUIDirector> rsUiDirector;
    OHOS::sptr<OHOS::Rosen::WindowOption> windowOption = new OHOS::Rosen::WindowOption();
    windowOption->SetWindowType(Rosen::WindowType::WINDOW_TYPE_TRANSPARENT_VIEW);
    auto context = std::make_shared<AbilityRuntime::AbilityContextImpl>();
    sptr<OHOS::Rosen::Window> window = OHOS::Rosen::Window::Create("test", windowOption, context);

    EXPECT_NE(window, nullptr);

    SystemProperties::SetMultiInstanceEnabled(true);
    RsAdapter::RsUIDirectorInit(rsUiDirector, window, "");

    EXPECT_NE(rsUiDirector, nullptr);
    EXPECT_NE(rsUiDirector->GetRSUIContext(), nullptr);

    EXPECT_EQ(OHOS::Rosen::WMError::WM_OK, window->Destroy());
#endif
}

/**
 * @tc.name: RsFlushImplicitTransaction001
 * @tc.desc: Test RsAdapterTest
 * @tc.type: FUNC
 */
HWTEST_F(RsAdapterTest, RsFlushImplicitTransaction001, TestSize.Level1)
{
#ifdef ENABLE_ROSEN_BACKEND
    // Prerequisite 1
    auto transactionProxy = Rosen::RSTransactionProxy::GetInstance();
    std::unique_ptr<Rosen::RSCommand> command = std::make_unique<Rosen::RSBaseNodeDestroy>(0);
    if (transactionProxy != nullptr) {
        auto renderThreadClient = Rosen::RSIRenderClient::CreateRenderThreadClient();
        transactionProxy->SetRenderThreadClient(renderThreadClient);
        transactionProxy->AddCommonCommand(command);
        transactionProxy->implicitCommonTransactionData_->abilityName_ = "test_ability";
    }

    EXPECT_EQ(transactionProxy->implicitCommonTransactionData_->abilityName_, "test_ability");

    std::shared_ptr<OHOS::Rosen::RSUIDirector> rsUiDirector;
    OHOS::sptr<OHOS::Rosen::WindowOption> windowOption = new OHOS::Rosen::WindowOption();
    windowOption->SetWindowType(Rosen::WindowType::WINDOW_TYPE_TRANSPARENT_VIEW);
    sptr<OHOS::Rosen::Window> window = OHOS::Rosen::Window::Create("test", windowOption);

    EXPECT_NE(window, nullptr);

    SystemProperties::SetMultiInstanceEnabled(false);
    auto surfaceNode = window->GetSurfaceNode();
    RsAdapter::RsFlushImplicitTransaction(rsUiDirector, window, surfaceNode);

    EXPECT_NE(rsUiDirector, nullptr);
    EXPECT_EQ(rsUiDirector->GetRSUIContext(), nullptr);
    EXPECT_NE(rsUiDirector->GetRSSurfaceNode(), nullptr);
    EXPECT_EQ(transactionProxy->implicitCommonTransactionData_->abilityName_, "");

    EXPECT_EQ(OHOS::Rosen::WMError::WM_OK, window->Destroy());
#endif
}

/**
 * @tc.name: RsFlushImplicitTransaction002
 * @tc.desc: Test RsAdapterTest
 * @tc.type: FUNC
 */
HWTEST_F(RsAdapterTest, RsFlushImplicitTransaction002, TestSize.Level1)
{
#ifdef ENABLE_ROSEN_BACKEND
    // Prerequisite 1
    auto transactionProxy = Rosen::RSTransactionProxy::GetInstance();
    std::unique_ptr<Rosen::RSCommand> command = std::make_unique<Rosen::RSBaseNodeDestroy>(0);
    if (transactionProxy != nullptr) {
        auto renderThreadClient = Rosen::RSIRenderClient::CreateRenderThreadClient();
        transactionProxy->SetRenderThreadClient(renderThreadClient);
        transactionProxy->AddCommonCommand(command);
        transactionProxy->implicitCommonTransactionData_->abilityName_ = "test_ability";
    }

    EXPECT_EQ(transactionProxy->implicitCommonTransactionData_->abilityName_, "test_ability");

    std::shared_ptr<OHOS::Rosen::RSUIDirector> rsUiDirector;
    OHOS::sptr<OHOS::Rosen::WindowOption> windowOption = new OHOS::Rosen::WindowOption();
    windowOption->SetWindowType(Rosen::WindowType::WINDOW_TYPE_TRANSPARENT_VIEW);
    auto context = std::make_shared<AbilityRuntime::AbilityContextImpl>();
    sptr<OHOS::Rosen::Window> window = OHOS::Rosen::Window::Create("test", windowOption, context);

    EXPECT_NE(window, nullptr);

    SystemProperties::SetMultiInstanceEnabled(true);
    std::shared_ptr<OHOS::Rosen::RSSurfaceNode> surfaceNode;
    RsAdapter::RsFlushImplicitTransaction(rsUiDirector, window, surfaceNode);

    EXPECT_NE(rsUiDirector, nullptr);
    EXPECT_NE(rsUiDirector->GetRSUIContext(), nullptr);
    EXPECT_EQ(rsUiDirector->GetRSSurfaceNode(), nullptr);
    EXPECT_EQ(transactionProxy->implicitCommonTransactionData_->abilityName_, "");

    EXPECT_EQ(OHOS::Rosen::WMError::WM_OK, window->Destroy());
#endif
}

/**
 * @tc.name: RsFlushImplicitTransactionWithRoot001
 * @tc.desc: Test RsAdapterTest
 * @tc.type: FUNC
 */
HWTEST_F(RsAdapterTest, RsFlushImplicitTransactionWithRoot001, TestSize.Level1)
{
#ifdef ENABLE_ROSEN_BACKEND
    // Prerequisite 1
    auto transactionProxy = Rosen::RSTransactionProxy::GetInstance();
    std::unique_ptr<Rosen::RSCommand> command = std::make_unique<Rosen::RSBaseNodeDestroy>(0);
    if (transactionProxy != nullptr) {
        auto renderThreadClient = Rosen::RSIRenderClient::CreateRenderThreadClient();
        transactionProxy->SetRenderThreadClient(renderThreadClient);
        transactionProxy->AddCommonCommand(command);
        transactionProxy->implicitCommonTransactionData_->abilityName_ = "test_ability";
    }

    EXPECT_EQ(transactionProxy->implicitCommonTransactionData_->abilityName_, "test_ability");

    std::shared_ptr<OHOS::Rosen::RSUIDirector> rsUiDirector;
    OHOS::sptr<OHOS::Rosen::WindowOption> windowOption = new OHOS::Rosen::WindowOption();
    windowOption->SetWindowType(Rosen::WindowType::WINDOW_TYPE_TRANSPARENT_VIEW);
    auto context = std::make_shared<AbilityRuntime::AbilityContextImpl>();
    sptr<OHOS::Rosen::Window> window = OHOS::Rosen::Window::Create("test", windowOption, context);

    EXPECT_NE(window, nullptr);

    SystemProperties::SetMultiInstanceEnabled(false);
    auto surfaceNode = window->GetSurfaceNode();
    std::shared_ptr<OHOS::Rosen::RSNode> rootNode;
    RsAdapter::RsFlushImplicitTransactionWithRoot(rsUiDirector, window, surfaceNode, rootNode);

    EXPECT_NE(rsUiDirector, nullptr);
    EXPECT_EQ(rsUiDirector->GetRSUIContext(), nullptr);
    EXPECT_NE(rsUiDirector->GetRSSurfaceNode(), nullptr);
    EXPECT_NE(rootNode, nullptr);
    EXPECT_EQ(rootNode->GetRSUIContext(), nullptr);
    EXPECT_EQ(transactionProxy->implicitCommonTransactionData_->abilityName_, "");

    EXPECT_EQ(OHOS::Rosen::WMError::WM_OK, window->Destroy());
#endif
}

/**
 * @tc.name: RsFlushImplicitTransactionWithRoot002
 * @tc.desc: Test RsAdapterTest
 * @tc.type: FUNC
 */
HWTEST_F(RsAdapterTest, RsFlushImplicitTransactionWithRoot002, TestSize.Level1)
{
#ifdef ENABLE_ROSEN_BACKEND
    // Prerequisite 1
    auto transactionProxy = Rosen::RSTransactionProxy::GetInstance();
    std::unique_ptr<Rosen::RSCommand> command = std::make_unique<Rosen::RSBaseNodeDestroy>(0);
    if (transactionProxy != nullptr) {
        auto renderThreadClient = Rosen::RSIRenderClient::CreateRenderThreadClient();
        transactionProxy->SetRenderThreadClient(renderThreadClient);
        transactionProxy->AddCommonCommand(command);
        transactionProxy->implicitCommonTransactionData_->abilityName_ = "test_ability";
    }

    EXPECT_EQ(transactionProxy->implicitCommonTransactionData_->abilityName_, "test_ability");

    std::shared_ptr<OHOS::Rosen::RSUIDirector> rsUiDirector;
    OHOS::sptr<OHOS::Rosen::WindowOption> windowOption = new OHOS::Rosen::WindowOption();
    windowOption->SetWindowType(Rosen::WindowType::WINDOW_TYPE_TRANSPARENT_VIEW);
    auto context = std::make_shared<AbilityRuntime::AbilityContextImpl>();
    sptr<OHOS::Rosen::Window> window = OHOS::Rosen::Window::Create("test", windowOption, context);

    EXPECT_NE(window, nullptr);

    SystemProperties::SetMultiInstanceEnabled(true);
    auto surfaceNode = window->GetSurfaceNode();
    std::shared_ptr<OHOS::Rosen::RSNode> rootNode;
    RsAdapter::RsFlushImplicitTransactionWithRoot(rsUiDirector, window, surfaceNode, rootNode);

    EXPECT_NE(rsUiDirector, nullptr);
    EXPECT_NE(rsUiDirector->GetRSUIContext(), nullptr);
    EXPECT_NE(rsUiDirector->GetRSSurfaceNode(), nullptr);
    EXPECT_NE(rootNode, nullptr);
    EXPECT_EQ(rootNode->GetRSUIContext(), nullptr);
    EXPECT_EQ(transactionProxy->implicitCommonTransactionData_->abilityName_, "");

    EXPECT_EQ(OHOS::Rosen::WMError::WM_OK, window->Destroy());
#endif
}

/**
 * @tc.name: FlushImplicitTransaction001
 * @tc.desc: Test RsAdapterTest
 * @tc.type: FUNC
 */
HWTEST_F(RsAdapterTest, FlushImplicitTransaction001, TestSize.Level1)
{
#ifdef ENABLE_ROSEN_BACKEND
    // Prerequisite 1
    auto transactionProxy = Rosen::RSTransactionProxy::GetInstance();
    std::unique_ptr<Rosen::RSCommand> command = std::make_unique<Rosen::RSBaseNodeDestroy>(0);
    if (transactionProxy != nullptr) {
        auto renderThreadClient = Rosen::RSIRenderClient::CreateRenderThreadClient();
        transactionProxy->SetRenderThreadClient(renderThreadClient);
        transactionProxy->AddCommonCommand(command);
        transactionProxy->implicitCommonTransactionData_->abilityName_ = "test_ability";
    }

    EXPECT_EQ(transactionProxy->implicitCommonTransactionData_->abilityName_, "test_ability");

    RsAdapter::FlushImplicitTransaction();

    EXPECT_EQ(transactionProxy->implicitCommonTransactionData_->abilityName_, "");
#endif
}

} // namespace OHOS::Ace::NG