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
#include "accessor_test_utils.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"

#include "core/interfaces/native/implementation/web_resource_response_peer_impl.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_theme_style.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
const auto RES_NAME_ID = NamedResourceId { "aa.bb.cc", ResourceType::STRING };
const auto RES_NAME_ID_ANY = "res_name_any";
const auto RES_NAME_ID_EMPTY = NamedResourceId { "res_name_empty", ResourceType::STRING };
const auto RES_NUMBER_ID = IntResourceId { 11111, ResourceType::STRING };
const auto RES_INVALID_ID = IntResourceId { -1, ResourceType::STRING };
const std::string RES_DATA_URL = "/super.example.com";
const std::string RES_DATA_URL_ANY = "any string not url";
const std::string RES_DATA_URL_OTHER = "example.com/";
const std::string RES_DATA_EMPTY = "";
const std::vector<std::tuple<std::string, Ark_Resource, std::string>> resourceTestPlan = {
    { RES_DATA_URL, CreateResource(RES_NAME_ID), "super.example.com" },
    { RES_DATA_URL_ANY, CreateResource(RES_NAME_ID_ANY, ResourceType::STRING), "any string not url" },
    { RES_DATA_EMPTY, CreateResource(RES_NAME_ID_EMPTY), "" },
    { RES_DATA_URL_OTHER, CreateResource(RES_NUMBER_ID), "example.com" },
    { RES_DATA_URL, CreateResource(RES_INVALID_ID), "" },
};
const std::vector<std::tuple<std::string, Ark_Buffer, std::string>> responseBufferTestPlan = {
    { RES_DATA_URL, Converter::ArkValue<Ark_Buffer>(RES_DATA_URL, nullptr), "/super.example.com" },
    { RES_DATA_URL_ANY, Converter::ArkValue<Ark_Buffer>(RES_DATA_URL_ANY, nullptr), "any string not url" },
    { RES_DATA_URL_OTHER, Converter::ArkValue<Ark_Buffer>(RES_DATA_URL_OTHER, nullptr), "example.com/" },
    { RES_DATA_EMPTY, Converter::ArkValue<Ark_Buffer>(RES_DATA_EMPTY, nullptr), "" },
};
} // namespace
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
 * @tc.name: getResponseDataTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebResourceResponseAccessorTest, getResponseDataTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getResponseData, nullptr);
    EXPECT_EQ("", Converter::Convert<std::string>(accessor_->getResponseData(peer_)));

    std::string responseData = "responseData";
    auto data = Converter::ArkUnion<Ark_Union_String_Number_Resource_Buffer, Ark_String>(responseData);
    accessor_->setResponseData(peer_, &data);

    EXPECT_EQ(responseData, Converter::Convert<std::string>(accessor_->getResponseData(peer_)));
    EXPECT_EQ("", Converter::Convert<std::string>(accessor_->getResponseData(nullptr)));
}

/**
 * @tc.name: getResponseDataEx1Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebResourceResponseAccessorTest, getResponseDataEx1Test, TestSize.Level1)
{
    ASSERT_NE(accessor_->getResponseDataEx, nullptr);

    auto dataString = Converter::ArkUnion<Ark_Union_String_Number_Resource_Buffer, Ark_String>("text");
    auto dataNumber = Converter::ArkUnion<Ark_Union_String_Number_Resource_Buffer, Ark_Number>(5);

    accessor_->setResponseData(peer_, &dataString);
    auto data = accessor_->getResponseDataEx(peer_);
    std::string strResult = "";
    Converter::VisitUnion(data,
        [&strResult](const Ark_String& responseData) {
            strResult = Converter::Convert<std::string>(responseData);
        },
        [](const auto& value) {},
        []() {}
    );
    EXPECT_EQ(strResult, "text");

    accessor_->setResponseData(peer_, &dataNumber);
    data = accessor_->getResponseDataEx(peer_);
    int32_t intResult = 0;
    Converter::VisitUnion(data,
        [&intResult](const Ark_Number& responseData) {
            intResult = Converter::Convert<int32_t>(responseData);
        },
        [](const auto& value) {},
        []() {}
    );
    EXPECT_EQ(intResult, 5);
}

/**
 * @tc.name: getResponseDataEx2Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebResourceResponseAccessorTest, getResponseDataEx2Test, TestSize.Level1)
{
    ASSERT_NE(accessor_->getResponseDataEx, nullptr);
    Ark_Resource resource {
        .bundleName = Converter::ArkValue<Ark_String>("bundleName"),
        .moduleName = Converter::ArkValue<Ark_String>("moduleName"),
        .id = Converter::ArkValue<Ark_Number>(8)
    };

    auto testStr = std::string("buffer");
    auto dataBuffer = Converter::ArkUnion<Ark_Union_String_Number_Resource_Buffer, Ark_Buffer>(testStr);
    auto dataRes = Converter::ArkUnion<Ark_Union_String_Number_Resource_Buffer, Ark_Resource>(resource);

    accessor_->setResponseData(peer_, &dataBuffer);
    auto data = accessor_->getResponseDataEx(peer_);
    std::string bufResult = "";
    Converter::VisitUnion(data,
        [&bufResult](const Ark_Buffer& responseData) {
            bufResult = Converter::Convert<std::string>(responseData);
        },
        [](const auto& value) {},
        []() {}
    );
    EXPECT_EQ(bufResult, testStr);

    accessor_->setResponseData(peer_, &dataRes);
    data = accessor_->getResponseDataEx(peer_);
    Ark_Resource resResult;
    Converter::VisitUnion(data,
        [&resResult](const Ark_Resource& responseData) {
            resResult = responseData;
        },
        [](const auto& value) {},
        []() {}
    );
    EXPECT_EQ(Converter::Convert<std::string>(resResult.bundleName), "bundleName");
    EXPECT_EQ(Converter::Convert<std::string>(resResult.moduleName), "moduleName");
    EXPECT_EQ(Converter::Convert<int32_t>(resResult.id), 8);
}

/**
 * @tc.name: getResponseEncodingTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebResourceResponseAccessorTest, getResponseEncodingTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getResponseEncoding, nullptr);
    EXPECT_EQ("", Converter::Convert<std::string>(accessor_->getResponseEncoding(peer_)));

    std::string encodingData = "encodingData";
    Ark_String data = Converter::ArkValue<Ark_String>(encodingData);
    accessor_->setResponseEncoding(peer_, &data);

    EXPECT_EQ(encodingData, Converter::Convert<std::string>(accessor_->getResponseEncoding(peer_)));
    EXPECT_EQ("", Converter::Convert<std::string>(accessor_->getResponseEncoding(nullptr)));
}

/**
 * @tc.name: getResponseMimeTypeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebResourceResponseAccessorTest, getResponseMimeTypeTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getResponseMimeType, nullptr);
    EXPECT_EQ("", Converter::Convert<std::string>(accessor_->getResponseMimeType(peer_)));

    std::string mimeType = "mimeType";
    Ark_String data = Converter::ArkValue<Ark_String>(mimeType);
    accessor_->setResponseMimeType(peer_, &data);

    EXPECT_EQ(mimeType, Converter::Convert<std::string>(accessor_->getResponseMimeType(peer_)));
    EXPECT_EQ("", Converter::Convert<std::string>(accessor_->getResponseMimeType(nullptr)));
}

/**
 * @tc.name: getReasonMessageTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebResourceResponseAccessorTest, getReasonMessageTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getReasonMessage, nullptr);
    std::vector<Converter::Header> empty;
    EXPECT_EQ("", Converter::Convert<std::string>(accessor_->getReasonMessage(peer_)));

    std::string reason = "reason";
    Ark_String data = Converter::ArkValue<Ark_String>(reason);
    accessor_->setReasonMessage(peer_, &data);

    EXPECT_EQ(reason, Converter::Convert<std::string>(accessor_->getReasonMessage(peer_)));
    EXPECT_EQ("", Converter::Convert<std::string>(accessor_->getReasonMessage(nullptr)));
}

/**
 * @tc.name: getResponseHeaderTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebResourceResponseAccessorTest, getResponseHeaderTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getResponseHeader, nullptr);
    auto headers = accessor_->getResponseHeader(nullptr);
    std::vector<Converter::Header> headerVect = Converter::Convert<std::vector<Converter::Header>>(headers);
    std::vector<Converter::Header> empty;
    EXPECT_EQ(headerVect, empty);

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

    headers = accessor_->getResponseHeader(peer_);
    headerVect = Converter::Convert<std::vector<Converter::Header>>(headers);
    std::vector<Converter::Header> expected = Converter::Convert<std::vector<Converter::Header>>(arrayHeader);

    EXPECT_EQ(headerVect, expected);
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
    EXPECT_EQ(arkStatusCode, Converter::Convert<int32_t>(accessor_->getResponseCode(peer_)));
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
 * @tc.name: setResponseDataResourceTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebResourceResponseAccessorTest, setResponseDataResourceTest, TestSize.Level1)
{
    Ark_Union_String_Number_Resource_Buffer initvalueResponse;
    ASSERT_NE(accessor_->setResponseData, nullptr);
    // Initial setup
    AddResource(RES_NAME_ID, RES_DATA_URL);
    AddResource(RES_NAME_ID_ANY, RES_DATA_URL_ANY);
    AddResource(RES_NAME_ID_EMPTY, RES_DATA_EMPTY);
    AddResource(RES_NUMBER_ID, RES_DATA_URL_OTHER);
    AddResource(RES_INVALID_ID, RES_DATA_URL);
    auto responseData = std::get<1>(resourceTestPlan[0]);
    initvalueResponse = Converter::ArkUnion<Ark_Union_String_Number_Resource_Buffer, Ark_Resource>(responseData);
    auto checkValue = [this, &initvalueResponse](
        const std::string& input, const Ark_Resource& value, const std::string& expectedStr) {
        Ark_Union_String_Number_Resource_Buffer data = initvalueResponse;
        data = Converter::ArkUnion<Ark_Union_String_Number_Resource_Buffer, Ark_Resource>(value);
        accessor_->setResponseData(peer_, &data);
        auto result = peer_->handler->GetResourceUrl();
        EXPECT_EQ(result, expectedStr);
    };
    for (const auto& [input, value, expected] : resourceTestPlan) {
        checkValue(input, value, expected);
    }
}

/**
 * @tc.name: setResponseDataArrayBufferTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebResourceResponseAccessorTest, setResponseDataArrayBufferTest, TestSize.Level1)
{
    Ark_Union_String_Number_Resource_Buffer initvalueResponse;
    ASSERT_NE(accessor_->setResponseData, nullptr);
    // Initial setup
    auto responseData = std::get<1>(responseBufferTestPlan[0]);
    initvalueResponse = Converter::ArkUnion<Ark_Union_String_Number_Resource_Buffer, Ark_Buffer>(responseData);
    auto checkValue = [this, &initvalueResponse](
        const std::string& input, const Ark_Buffer& value, const std::string& expectedStr) {
        Ark_Union_String_Number_Resource_Buffer data = initvalueResponse;
        data = Converter::ArkUnion<Ark_Union_String_Number_Resource_Buffer, Ark_Buffer>(value);
        accessor_->setResponseData(peer_, &data);
        auto result = peer_->handler->GetData();
        EXPECT_EQ(result, expectedStr);
    };
    for (const auto& [input, value, expected] : responseBufferTestPlan) {
        checkValue(input, value, expected);
    }
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
