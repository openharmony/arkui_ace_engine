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

#include "core/interfaces/native/implementation/web_context_menu_param_peer_impl.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
class MockWebContextMenuParam : public WebContextMenuParam {
public:
    MOCK_METHOD(int32_t, GetXCoord, (), (const));
    MOCK_METHOD(int32_t, GetYCoord, (), (const));
    MOCK_METHOD(std::string, GetLinkUrl, (), (const));
    MOCK_METHOD(std::string, GetUnfilteredLinkUrl, (), (const));
    MOCK_METHOD(std::string, GetSourceUrl, (), (const));
    MOCK_METHOD(bool, HasImageContents, (), (const));
    MOCK_METHOD(bool, IsEditable, (), (const));
    MOCK_METHOD(int, GetEditStateFlags, (), (const));
    MOCK_METHOD(int, GetSourceType, (), (const));
    MOCK_METHOD(int, GetMediaType, (), (const));
    MOCK_METHOD(int, GetInputFieldType, (), (const));
    MOCK_METHOD(std::string, GetSelectionText, (), (const));
};
} // namespace

class WebContextMenuParamAccessorTest : public AccessorTestBase<GENERATED_ArkUIWebContextMenuParamAccessor,
    &GENERATED_ArkUIAccessors::getWebContextMenuParamAccessor, WebContextMenuParamPeer> {
public:
    void SetUp() override
    {
        AccessorTestBase::SetUp();
        mockHandler_ = Referenced::MakeRefPtr<MockWebContextMenuParam>();
        ASSERT_NE(mockHandler_, nullptr);
        peer_->handler = mockHandler_;
    }

    void TearDown() override
    {
        AccessorTestBase::TearDown();
        mockHandler_ = nullptr;
    }

    RefPtr<MockWebContextMenuParam> mockHandler_ = nullptr;
};

/**
 * @tc.name: xTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuParamAccessorTest, xTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->x, nullptr);

    int32_t value = 5;

    EXPECT_CALL(*mockHandler_, GetXCoord()).Times(1).WillOnce(Return(value));
    EXPECT_EQ(value, accessor_->x(peer_));
}

/**
 * @tc.name: yTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuParamAccessorTest, yTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->y, nullptr);

    int32_t value = 6;

    EXPECT_CALL(*mockHandler_, GetYCoord()).Times(1).WillOnce(Return(value));
    EXPECT_EQ(value, accessor_->y(peer_));
}

/**
 * @tc.name: DISABLED_getLinkUrlTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuParamAccessorTest, DISABLED_getLinkUrlTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getLinkUrl, nullptr);

    std::string value = "value";

    EXPECT_CALL(*mockHandler_, GetLinkUrl()).Times(1).WillOnce(Return(value));
    // should return value
    accessor_->getLinkUrl(peer_);
}

/**
 * @tc.name: DISABLED_getUnfilteredLinkUrlTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuParamAccessorTest, DISABLED_getUnfilteredLinkUrlTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getUnfilteredLinkUrl, nullptr);

    std::string value = "value";

    EXPECT_CALL(*mockHandler_, GetUnfilteredLinkUrl()).Times(1).WillOnce(Return(value));
    // should return value
    accessor_->getUnfilteredLinkUrl(peer_);
}

/**
 * @tc.name: DISABLED_getSourceUrlTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuParamAccessorTest, DISABLED_getSourceUrlTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getSourceUrl, nullptr);

    std::string value = "value";

    EXPECT_CALL(*mockHandler_, GetSourceUrl()).Times(1).WillOnce(Return(value));
    // should return value
    accessor_->getSourceUrl(peer_);
}

/**
 * @tc.name: DISABLED_getSelectionTextTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuParamAccessorTest, DISABLED_getSelectionTextTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getSelectionText, nullptr);

    std::string value = "value";

    EXPECT_CALL(*mockHandler_, GetSelectionText()).Times(1).WillOnce(Return(value));
    // should return value
    accessor_->getSelectionText(peer_);
}

/**
 * @tc.name: existsImageContentsTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuParamAccessorTest, existsImageContentsTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->existsImageContents, nullptr);

    Ark_Boolean arkTrue = Converter::ArkValue<Ark_Boolean>(true);
    Ark_Boolean arkFalse = Converter::ArkValue<Ark_Boolean>(false);

    EXPECT_CALL(*mockHandler_, HasImageContents()).Times(1).WillOnce(Return(true));
    EXPECT_EQ(arkTrue, accessor_->existsImageContents(peer_));

    EXPECT_CALL(*mockHandler_, HasImageContents()).Times(1).WillOnce(Return(false));
    EXPECT_EQ(arkFalse, accessor_->existsImageContents(peer_));
}

/**
 * @tc.name: isEditableTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuParamAccessorTest, isEditableTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->isEditable, nullptr);

    Ark_Boolean arkTrue = Converter::ArkValue<Ark_Boolean>(true);
    Ark_Boolean arkFalse = Converter::ArkValue<Ark_Boolean>(false);

    EXPECT_CALL(*mockHandler_, IsEditable()).Times(1).WillOnce(Return(true));
    EXPECT_EQ(arkTrue, accessor_->isEditable(peer_));

    EXPECT_CALL(*mockHandler_, IsEditable()).Times(1).WillOnce(Return(false));
    EXPECT_EQ(arkFalse, accessor_->isEditable(peer_));
}

/**
 * @tc.name: DISABLED_getMediaTypeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuParamAccessorTest, DISABLED_getMediaTypeTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getMediaType, nullptr);

    int value = 7;

    EXPECT_CALL(*mockHandler_, GetMediaType()).Times(1).WillOnce(Return(value));
    // should return value
    accessor_->getMediaType(peer_);
}

/**
 * @tc.name: DISABLED_getSourceTypeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuParamAccessorTest, DISABLED_getSourceTypeTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getSourceType, nullptr);

    int value = 8;

    EXPECT_CALL(*mockHandler_, GetSourceType()).Times(1).WillOnce(Return(value));
    // should return value
    accessor_->getSourceType(peer_);
}

/**
 * @tc.name: DISABLED_getInputFieldTypeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuParamAccessorTest, DISABLED_getInputFieldTypeTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getInputFieldType, nullptr);

    int value = 9;

    EXPECT_CALL(*mockHandler_, GetInputFieldType()).Times(1).WillOnce(Return(value));
    // should return value
    accessor_->getInputFieldType(peer_);
}

/**
 * @tc.name: getEditStateFlagsTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuParamAccessorTest, getEditStateFlagsTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getEditStateFlags, nullptr);

    int32_t value = 10;

    EXPECT_CALL(*mockHandler_, GetEditStateFlags()).Times(1).WillOnce(Return(value));
    EXPECT_EQ(value, accessor_->getEditStateFlags(peer_));
}

} // namespace OHOS::Ace::NG
