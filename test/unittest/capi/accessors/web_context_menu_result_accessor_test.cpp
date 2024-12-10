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
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"

#include "core/interfaces/native/implementation/web_context_menu_result_peer_impl.h"
#include "test/unittest/capi/stubs/mock_web_entities.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class WebContextMenuResultAccessorTest : public AccessorTestBase<GENERATED_ArkUIWebContextMenuResultAccessor,
    &GENERATED_ArkUIAccessors::getWebContextMenuResultAccessor, WebContextMenuResultPeer> {
public:
    void SetUp() override
    {
        AccessorTestBase::SetUp();
        mockHandler_ = Referenced::MakeRefPtr<MockContextMenuResult>();
        ASSERT_NE(mockHandler_, nullptr);
        peer_->handler = mockHandler_;
    }

    void TearDown() override
    {
        AccessorTestBase::TearDown();
        mockHandler_ = nullptr;
    }

    RefPtr<MockContextMenuResult> mockHandler_ = nullptr;
};

/**
 * @tc.name: closeContextMenuTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuResultAccessorTest, closeContextMenuTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->closeContextMenu, nullptr);

    EXPECT_CALL(*mockHandler_, Cancel()).Times(3);
    accessor_->closeContextMenu(peer_);
    accessor_->closeContextMenu(peer_);
    accessor_->closeContextMenu(peer_);
}

/**
 * @tc.name: copyImageTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuResultAccessorTest, copyImageTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->copyImage, nullptr);

    EXPECT_CALL(*mockHandler_, CopyImage()).Times(3);
    accessor_->copyImage(peer_);
    accessor_->copyImage(peer_);
    accessor_->copyImage(peer_);
}

/**
 * @tc.name: copyTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuResultAccessorTest, copyTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->copy, nullptr);

    EXPECT_CALL(*mockHandler_, Copy()).Times(3);
    accessor_->copy(peer_);
    accessor_->copy(peer_);
    accessor_->copy(peer_);
}

/**
 * @tc.name: pasteTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuResultAccessorTest, pasteTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->paste, nullptr);

    EXPECT_CALL(*mockHandler_, Paste()).Times(3);
    accessor_->paste(peer_);
    accessor_->paste(peer_);
    accessor_->paste(peer_);
}

/**
 * @tc.name: cutTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuResultAccessorTest, cutTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->cut, nullptr);

    EXPECT_CALL(*mockHandler_, Cut()).Times(3);
    accessor_->cut(peer_);
    accessor_->cut(peer_);
    accessor_->cut(peer_);
}

/**
 * @tc.name: selectAllTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuResultAccessorTest, selectAllTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->selectAll, nullptr);

    EXPECT_CALL(*mockHandler_, SelectAll()).Times(3);
    accessor_->selectAll(peer_);
    accessor_->selectAll(peer_);
    accessor_->selectAll(peer_);
}

} // namespace OHOS::Ace::NG
