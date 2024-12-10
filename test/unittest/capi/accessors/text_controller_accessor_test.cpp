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

#include "gmock/gmock.h"

#include "accessor_test_base.h"
#include "node_api.h"
#include "core/interfaces/native/implementation/text_controller_peer_impl.h"
#include "core/components_ng/pattern/text/span/span_string.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
class MockTextController : public TextController {
public:
    MOCK_METHOD(void, CloseSelectionMenu, ());
    MOCK_METHOD(void, SetStyledString, (const RefPtr<SpanStringBase>&));
    MOCK_METHOD(WeakPtr<NG::LayoutInfoInterface>, GetLayoutInfoInterface, ());
};
}

class TextControllerAccessorTest : public AccessorTestBase<
    GENERATED_ArkUITextControllerAccessor,
    &GENERATED_ArkUIAccessors::getTextControllerAccessor,
    TextControllerPeer> {
public:
    void SetUp() override
    {
        AccessorTestBase::SetUp();
        mockController_ = Referenced::MakeRefPtr<MockTextController>();
        ASSERT_NE(mockController_, nullptr);
        peer_->controller = mockController_;
    }

    void TearDown() override
    {
        AccessorTestBase::TearDown();
        mockController_ = nullptr;
    }

    RefPtr<MockTextController> mockController_ = nullptr;
};

/**
 * @tc.name: closeSelectionMenuTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextControllerAccessorTest, closeSelectionMenuTest, TestSize.Level1)
{
    EXPECT_CALL(*mockController_, CloseSelectionMenu()).Times(1);
    accessor_->closeSelectionMenu(peer_);
}

} // namespace OHOS::Ace::NG