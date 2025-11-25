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
#include "core/interfaces/native/utility/converter.h"
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
    MOCK_METHOD(std::vector<std::string>, GetMimeType, ());
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
 * @tc.name: getTitleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FileSelectorParamAccessorTest, getTitleTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getTitle, nullptr);
    std::string title = "title";

    EXPECT_CALL(*mockHandler_, GetTitle()).Times(1).WillOnce(Return("title"));
    EXPECT_EQ(Converter::Convert<std::string>(accessor_->getTitle(peer_)), title);
}

/**
 * @tc.name: getAcceptTypeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FileSelectorParamAccessorTest, getAcceptTypeTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getAcceptType, nullptr);
    std::vector<std::string> acceptType { "item1", "item2" };

    EXPECT_CALL(*mockHandler_, GetAcceptType()).Times(1).WillOnce(Return(acceptType));
    EXPECT_EQ(Converter::Convert<std::vector<std::string>>(accessor_->getAcceptType(peer_)), acceptType);
}

/**
 * @tc.name: getModeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FileSelectorParamAccessorTest, getModeTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getMode, nullptr);

    EXPECT_CALL(*mockHandler_, GetMode()).Times(1).WillOnce(Return(2));
    EXPECT_EQ(accessor_->getMode(peer_), ARK_FILE_SELECTOR_MODE_FILE_OPEN_FOLDER_MODE);
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

/**
 * @tc.name: getMimeTypesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FileSelectorParamAccessorTest, getMimeTypesTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getMimeTypes, nullptr);
    std::vector<std::string> mimeTypes { "item1", "item2" };

    EXPECT_CALL(*mockHandler_, GetMimeType()).Times(1).WillOnce(Return(mimeTypes));
    EXPECT_EQ(Converter::Convert<std::vector<std::string>>(accessor_->getMimeTypes(peer_)), mimeTypes);
}

} // namespace OHOS::Ace::NG
