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

#include "core/interfaces/native/implementation/file_selector_param_peer_impl.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
class MockWebFileSelectorParam : public WebFileSelectorParam {
public:
    MOCK_METHOD(std::string, GetTitle, ());
    MOCK_METHOD(int, GetMode, ());
    MOCK_METHOD(std::vector<std::string>, GetAcceptType, ());
    MOCK_METHOD(std::string, GetDefaultFileName, ());
    MOCK_METHOD(bool, IsCapture, ());
};
} // namespace

class FileSelectorParamAccessorTest : public AccessorTestBase<GENERATED_ArkUIFileSelectorParamAccessor,
    &GENERATED_ArkUIAccessors::getFileSelectorParamAccessor, FileSelectorParamPeer> {
public:
    void SetUp() override
    {
        AccessorTestBase::SetUp();
        mockHandler_ = Referenced::MakeRefPtr<MockWebFileSelectorParam>();
        ASSERT_NE(mockHandler_, nullptr);
        peer_->handler = mockHandler_;
    }

    void TearDown() override
    {
        AccessorTestBase::TearDown();
        mockHandler_ = nullptr;
    }

    RefPtr<MockWebFileSelectorParam> mockHandler_ = nullptr;
};

/**
 * @tc.name: DISABLED_getTitleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FileSelectorParamAccessorTest, DISABLED_getTitleTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getTitle, nullptr);

    EXPECT_CALL(*mockHandler_, GetTitle()).Times(1);
    accessor_->getTitle(peer_);
}

/**
 * @tc.name: DISABLED_getAcceptTypeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FileSelectorParamAccessorTest, DISABLED_getAcceptTypeTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getAcceptType, nullptr);

    EXPECT_CALL(*mockHandler_, GetAcceptType()).Times(1);
    accessor_->getAcceptType(peer_);
}

/**
 * @tc.name: DISABLED_getModeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FileSelectorParamAccessorTest, DISABLED_getModeTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getMode, nullptr);

    EXPECT_CALL(*mockHandler_, GetMode()).Times(1);
    accessor_->getMode(peer_);
}

/**
 * @tc.name: isCaptureTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FileSelectorParamAccessorTest, isCaptureTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->isCapture, nullptr);

    Ark_Boolean arkTrue = Converter::ArkValue<Ark_Boolean>(true);
    Ark_Boolean arkFalse = Converter::ArkValue<Ark_Boolean>(false);

    EXPECT_CALL(*mockHandler_, IsCapture()).Times(1).WillOnce(Return(true));
    EXPECT_EQ(arkTrue, accessor_->isCapture(peer_));

    EXPECT_CALL(*mockHandler_, IsCapture()).Times(1).WillOnce(Return(false));
    EXPECT_EQ(arkFalse, accessor_->isCapture(peer_));
}

} // namespace OHOS::Ace::NG
