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

#include "gmock/gmock.h"

#include "accessor_test_base.h"
#include "core/components/web/web_event.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/controller_handler_peer_impl.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
class MockWebWindowNewHandler : public WebWindowNewHandler {
public:
    MOCK_METHOD(void, SetWebController, (int32_t));
    MOCK_METHOD(bool, IsFrist, (), (const override));
    MOCK_METHOD(int32_t, GetId, (), (const override));
    MOCK_METHOD(int32_t, GetParentNWebId, (), (const override));
};
}

class ControllerHandlerAccessorTest : public AccessorTestBase<GENERATED_ArkUIControllerHandlerAccessor,
    &GENERATED_ArkUIAccessors::getControllerHandlerAccessor, ControllerHandlerPeer> {
};

/**
 * @tc.name: setWebControllerTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ControllerHandlerAccessorTest, setWebControllerTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setWebController, nullptr);

    auto webControllerPeer = accessors_->getWebviewControllerAccessor()->construct();
    ASSERT_NE(webControllerPeer, nullptr);
    EXPECT_TRUE(ControllerHandlerPeer::controllerMap.empty());
    RefPtr<MockWebWindowNewHandler> mockHandler = Referenced::MakeRefPtr<MockWebWindowNewHandler>();
    peer_->handler = mockHandler;
    ASSERT_NE(peer_->handler, nullptr);
    EXPECT_CALL(*mockHandler, GetParentNWebId()).Times(3).WillRepeatedly(Return(5));
    EXPECT_CALL(*mockHandler, GetId()).Times(1).WillOnce(Return(15));

    accessor_->setWebController(peer_, nullptr);
    EXPECT_TRUE(ControllerHandlerPeer::controllerMap.empty());

    auto webviewControllerPeer = new webview_WebviewControllerPeer();
    accessor_->setWebController(peer_, webviewControllerPeer);
    EXPECT_TRUE(ControllerHandlerPeer::controllerMap.empty());

    auto getWebIdFunc = []() -> int32_t { return 0; };
    webviewControllerPeer->getWebIdFunc = getWebIdFunc;
    auto setWebIdFunc = [](int32_t nwebId) { return; };
    webviewControllerPeer->setWebIdFunc = setWebIdFunc;
    auto setHapPathFunc = [](const std::string& hapPath) { return; };
    webviewControllerPeer->setHapPathFunc = setHapPathFunc;
    auto getNativePtrFunc = []() -> long { return 0L; };
    webviewControllerPeer->getNativePtrFunc = getNativePtrFunc;
    auto releaseRefFunc = []() { return; };
    webviewControllerPeer->releaseRefFunc = releaseRefFunc;
    accessor_->setWebController(peer_, webviewControllerPeer);
    EXPECT_FALSE(ControllerHandlerPeer::controllerMap.empty());
    EXPECT_EQ(ControllerHandlerPeer::controllerMap.size(), 1);
    delete webviewControllerPeer;

    auto it = ControllerHandlerPeer::controllerMap.find(15);
    ASSERT_NE(it, ControllerHandlerPeer::controllerMap.end());
    EXPECT_EQ(it->second.controller, webviewControllerPeer);
    EXPECT_EQ(it->second.parentWebId, 5);
    auto weakWebController = Referenced::WeakClaim(webControllerPeer);
    EXPECT_FALSE(weakWebController.Invalid());
    auto finalyzer = reinterpret_cast<void (*)(Ark_WebviewController)>(
        accessors_->getWebviewControllerAccessor()->getFinalizer());
    finalyzer(webControllerPeer);
    EXPECT_FALSE(weakWebController.Invalid());
}

} // namespace OHOS::Ace::NG
