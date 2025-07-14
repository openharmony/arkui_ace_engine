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

#include "core/interfaces/native/implementation/web_context_menu_param_peer_impl.h"
#include "test/unittest/capi/stubs/mock_web_entities.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

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
    EXPECT_EQ(value, Converter::Convert<int32_t>(accessor_->x(peer_)));
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
    EXPECT_EQ(value, Converter::Convert<int32_t>(accessor_->y(peer_)));
}

/**
 * @tc.name: getLinkUrlTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuParamAccessorTest, getLinkUrlTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getLinkUrl, nullptr);

    std::string value = "value";

    EXPECT_CALL(*mockHandler_, GetLinkUrl()).Times(1).WillOnce(Return(value));
    EXPECT_EQ(Converter::Convert<std::string>(accessor_->getLinkUrl(peer_)), value);
    EXPECT_EQ(Converter::Convert<std::string>(accessor_->getLinkUrl(nullptr)), "");
}

/**
 * @tc.name: getUnfilteredLinkUrlTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuParamAccessorTest, getUnfilteredLinkUrlTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getUnfilteredLinkUrl, nullptr);

    std::string value = "value";

    EXPECT_CALL(*mockHandler_, GetUnfilteredLinkUrl()).Times(1).WillOnce(Return(value));
    EXPECT_EQ(Converter::Convert<std::string>(accessor_->getUnfilteredLinkUrl(peer_)), value);
    EXPECT_EQ(Converter::Convert<std::string>(accessor_->getUnfilteredLinkUrl(nullptr)), "");
}

/**
 * @tc.name: getSourceUrlTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuParamAccessorTest, getSourceUrlTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getSourceUrl, nullptr);

    std::string value = "value";

    EXPECT_CALL(*mockHandler_, GetSourceUrl()).Times(1).WillOnce(Return(value));
    EXPECT_EQ(Converter::Convert<std::string>(accessor_->getSourceUrl(peer_)), value);
    EXPECT_EQ(Converter::Convert<std::string>(accessor_->getSourceUrl(nullptr)), "");
}

/**
 * @tc.name: getSelectionTextTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuParamAccessorTest, getSelectionTextTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getSelectionText, nullptr);

    std::string value = "value";

    EXPECT_CALL(*mockHandler_, GetSelectionText()).Times(1).WillOnce(Return(value));
    EXPECT_EQ(Converter::Convert<std::string>(accessor_->getSelectionText(peer_)), value);
    EXPECT_EQ(Converter::Convert<std::string>(accessor_->getSelectionText(nullptr)), "");
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
 * @tc.name: getMediaTypeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuParamAccessorTest, getMediaTypeTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getMediaType, nullptr);

    int value = 1;

    EXPECT_CALL(*mockHandler_, GetMediaType()).Times(1).WillOnce(Return(value));
    EXPECT_EQ(accessor_->getMediaType(peer_), ARK_CONTEXT_MENU_MEDIA_TYPE_IMAGE);
}

/**
 * @tc.name: getSourceTypeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuParamAccessorTest, getSourceTypeTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getSourceType, nullptr);

    int value = 2;

    EXPECT_CALL(*mockHandler_, GetSourceType()).Times(1).WillOnce(Return(value));
    EXPECT_EQ(accessor_->getSourceType(peer_), ARK_CONTEXT_MENU_SOURCE_TYPE_LONG_PRESS);
}

/**
 * @tc.name: getInputFieldTypeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuParamAccessorTest, getInputFieldTypeTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getInputFieldType, nullptr);

    int value = 5;

    EXPECT_CALL(*mockHandler_, GetInputFieldType()).Times(1).WillOnce(Return(value));
    EXPECT_EQ(accessor_->getInputFieldType(peer_), ARK_CONTEXT_MENU_INPUT_FIELD_TYPE_OTHER);
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
    EXPECT_EQ(value, Converter::Convert<int32_t>(accessor_->getEditStateFlags(peer_)));
}

/**
 * @tc.name: getPreviewWidthTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuParamAccessorTest, getPreviewWidthTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getPreviewWidth, nullptr);

    int32_t value = 11;

    mockHandler_->mockPreviewWidth = value;
    auto result = Converter::Convert<int32_t>(accessor_->getPreviewWidth(peer_));
    EXPECT_EQ(value, result);
}

/**
 * @tc.name: getPreviewHeightTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuParamAccessorTest, getPreviewHeightTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getPreviewHeight, nullptr);

    int32_t value = 12;

    mockHandler_->mockPreviewHeight = value;
    auto result = Converter::Convert<int32_t>(accessor_->getPreviewHeight(peer_));
    EXPECT_EQ(value, result);
}
} // namespace OHOS::Ace::NG
