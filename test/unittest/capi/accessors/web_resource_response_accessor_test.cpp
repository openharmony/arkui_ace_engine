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
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"

#include "core/interfaces/native/implementation/web_resource_response_peer_impl.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class WebResourceResponseAccessorTest : public AccessorTestBase<GENERATED_ArkUIWebResourceResponseAccessor,
    &GENERATED_ArkUIAccessors::getWebResourceResponseAccessor, WebResourceResponsePeer> {
public:
    void SetUp() override
    {
        AccessorTestBase::SetUp();
        peer_->handler = Referenced::MakeRefPtr<WebResponse>();
        ASSERT_NE(peer_->handler, nullptr);
    }
};

/**
 * @tc.name: DISABLED_getResponseDataTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebResourceResponseAccessorTest, DISABLED_getResponseDataTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getResponseData, nullptr);
    accessor_->getResponseData(peer_);
}

/**
 * @tc.name: DISABLED_getResponseDataExTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebResourceResponseAccessorTest, DISABLED_getResponseDataExTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getResponseDataEx, nullptr);
    accessor_->getResponseDataEx(peer_);
}

/**
 * @tc.name: DISABLED_getResponseEncodingTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebResourceResponseAccessorTest, DISABLED_getResponseEncodingTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getResponseEncoding, nullptr);
    accessor_->getResponseEncoding(peer_);
}

/**
 * @tc.name: DISABLED_getResponseMimeTypeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebResourceResponseAccessorTest, DISABLED_getResponseMimeTypeTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getResponseMimeType, nullptr);
    accessor_->getResponseMimeType(peer_);
}

/**
 * @tc.name: DISABLED_getReasonMessageTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebResourceResponseAccessorTest, DISABLED_getReasonMessageTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getReasonMessage, nullptr);
    accessor_->getReasonMessage(peer_);
}

/**
 * @tc.name: DISABLED_getResponseHeaderTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebResourceResponseAccessorTest, DISABLED_getResponseHeaderTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getResponseHeader, nullptr);
    accessor_->getResponseHeader(peer_);
}

/**
 * @tc.name: getResponseCodeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebResourceResponseAccessorTest, getResponseCodeTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getResponseCode, nullptr);

    int32_t statusCode = 5;
    Ark_Int32 arkStatusCode = Converter::ArkValue<Ark_Int32>(statusCode);

    peer_->handler->SetStatusCode(statusCode);
    EXPECT_EQ(arkStatusCode, accessor_->getResponseCode(peer_));
}

/**
 * @tc.name: setResponseDataTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebResourceResponseAccessorTest, setResponseDataTest, TestSize.Level1)
{
    Ark_Union_String_Number_Resource_Buffer data;

    ASSERT_NE(accessor_->setResponseData, nullptr);

    std::string responseData = "responseData";
    data = Converter::ArkUnion<Ark_Union_String_Number_Resource_Buffer, Ark_String>(responseData);
    accessor_->setResponseData(peer_, &data);
    EXPECT_EQ(responseData, peer_->handler->GetData());

    int32_t fd = 7;
    data = Converter::ArkUnion<Ark_Union_String_Number_Resource_Buffer, Ark_Number>(fd);
    accessor_->setResponseData(peer_, &data);
    EXPECT_EQ(fd, peer_->handler->GetFileHandle());
}

/**
 * @tc.name: DISABLED_setResponseDataResourceTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebResourceResponseAccessorTest, DISABLED_setResponseDataResourceTest, TestSize.Level1)
{
    // test need to be implemented for Ark_Resource
}

/**
 * @tc.name: DISABLED_setResponseDataArrayBufferTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebResourceResponseAccessorTest, DISABLED_setResponseDataArrayBufferTest, TestSize.Level1)
{
    // test need to be implemented for Ark_ArrayBuffer
}

/**
 * @tc.name: setResponseEncoding
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebResourceResponseAccessorTest, setResponseEncodingTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setResponseEncoding, nullptr);

    std::string encodingData = "encodingData";
    Ark_String data = Converter::ArkValue<Ark_String>(encodingData);
    accessor_->setResponseEncoding(peer_, &data);
    EXPECT_EQ(encodingData, peer_->handler->GetEncoding());
}

/**
 * @tc.name: setResponseMimeTypeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebResourceResponseAccessorTest, setResponseMimeTypeTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setResponseMimeType, nullptr);

    std::string mimeType = "mimeType";
    Ark_String data = Converter::ArkValue<Ark_String>(mimeType);
    accessor_->setResponseMimeType(peer_, &data);
    EXPECT_EQ(mimeType, peer_->handler->GetMimeType());
}

/**
 * @tc.name: setReasonMessageTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebResourceResponseAccessorTest, setReasonMessageTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setReasonMessage, nullptr);

    std::string reason = "reason";
    Ark_String data = Converter::ArkValue<Ark_String>(reason);
    accessor_->setReasonMessage(peer_, &data);
    EXPECT_EQ(reason, peer_->handler->GetReason());
}

/**
 * @tc.name: setResponseHeaderTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebResourceResponseAccessorTest, setResponseHeaderTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setResponseHeader, nullptr);

    std::string headerKey = "headerKey";
    std::string headerValue = "headerValue";
    std::map<std::string, std::string> httpHeaders;
    httpHeaders[headerKey] = headerValue;

    Ark_Header header;
    header.headerKey = Converter::ArkValue<Ark_String>(headerKey);
    header.headerValue = Converter::ArkValue<Ark_String>(headerValue);
    std::vector<Ark_Header> vec { header };
    Converter::ArkArrayHolder<Array_Header> vecHolder(vec);
    Array_Header arrayHeader = vecHolder.ArkValue();

    accessor_->setResponseHeader(peer_, &arrayHeader);
    EXPECT_EQ(httpHeaders, peer_->handler->GetHeaders());
}

/**
 * @tc.name: setResponseCodeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebResourceResponseAccessorTest, setResponseCodeTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setResponseCode, nullptr);

    int32_t statusCode = 404;
    Ark_Number data = Converter::ArkValue<Ark_Number>(statusCode);
    accessor_->setResponseCode(peer_, &data);
    EXPECT_EQ(statusCode, peer_->handler->GetStatusCode());
}

/**
 * @tc.name: setResponseIsReadyTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebResourceResponseAccessorTest, setResponseIsReadyTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setResponseIsReady, nullptr);

    accessor_->setResponseIsReady(peer_, Converter::ArkValue<Ark_Boolean>(true));
    EXPECT_TRUE(peer_->handler->GetResponseStatus());

    accessor_->setResponseIsReady(peer_, Converter::ArkValue<Ark_Boolean>(false));
    EXPECT_FALSE(peer_->handler->GetResponseStatus());
}

/**
 * @tc.name: getResponseIsReadyTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebResourceResponseAccessorTest, getResponseIsReadyTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setResponseIsReady, nullptr);

    Ark_Boolean arkTrue = Converter::ArkValue<Ark_Boolean>(true);
    peer_->handler->SetResponseStatus(true);
    EXPECT_EQ(arkTrue, accessor_->getResponseIsReady(peer_));

    Ark_Boolean arkFalse = Converter::ArkValue<Ark_Boolean>(false);
    peer_->handler->SetResponseStatus(false);
    EXPECT_EQ(arkFalse, accessor_->getResponseIsReady(peer_));
}

} // namespace OHOS::Ace::NG
