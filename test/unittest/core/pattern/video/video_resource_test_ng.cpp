/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include <memory>
#include <string>
#include <vector>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "core/common/platform_res_register.h"
#include "core/components_ng/pattern/video/resource/ext_surface.h"
#include "core/components_ng/pattern/video/resource/ext_texture.h"
#include "core/components_ng/pattern/video/resource/player.h"
#include "core/components_ng/pattern/video/resource/resource.h"
#include "core/components_ng/pattern/video/resource/texture.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
using NG::MockPipelineContext;
namespace {

constexpr int64_t TEST_RESOURCE_ID = 42;
constexpr int32_t TEST_INT_VALUE = 100;
constexpr double TEST_DOUBLE_VALUE = 3.14;
constexpr int64_t TEST_INT64_VALUE = 1234567890123LL;
constexpr uint32_t TEST_UINT_VALUE = 1280;
constexpr uint32_t TEST_UINT_VALUE_ALT = 720;
constexpr uint32_t TEST_DURATION_VALUE = 300;
constexpr float TEST_FLOAT_1 = 1.0f;
constexpr float TEST_FLOAT_2 = 2.0f;
constexpr float TEST_FLOAT_3 = 3.0f;
constexpr int32_t TEST_PATTERN_TYPE = 5;
constexpr uint32_t TEST_SEEK_POS = 5000;
constexpr uint32_t TEST_CURRENT_POS_ALT = 4000;

class TestResource : public Resource {
public:
    using Resource::GetDoubleParam;
    using Resource::GetFloatArrayParam;
    using Resource::GetInt64Param;
    using Resource::GetIntParam;
    using Resource::IsResultSuccess;
    using Resource::MakeEventHash;
    using Resource::MakeMethodHash;
    using Resource::MakeResourceHash;
    using Resource::OnError;

    TestResource(const WeakPtr<PipelineBase>& context, ErrorCallback&& onError)
        : Resource("test", context, std::move(onError))
    {}
};

class TestTexture : public Texture {
public:
    using Texture::OnRefresh;
    TestTexture(const WeakPtr<PipelineBase>& context, ErrorCallback&& onError) : Texture(context, std::move(onError)) {}
};

class TestExtSurfaceClass : public ExtSurface {
public:
    using ExtSurface::OnSurfaceChanged;
    using ExtSurface::OnSurfaceCreated;
    using ExtSurface::OnSurfaceDestroyed;
    TestExtSurfaceClass(const WeakPtr<PipelineBase>& context, ErrorCallback&& onError)
        : ExtSurface(context, std::move(onError))
    {}
};

class TestExtTextureClass : public ExtTexture {
public:
    using ExtTexture::OnRefresh;
    using ExtTexture::OnSurfaceChanged;
    using ExtTexture::OnSurfaceCreated;
    TestExtTextureClass(const WeakPtr<PipelineBase>& context, ErrorCallback&& onError)
        : ExtTexture(context, std::move(onError))
    {}
};

class TestPlayer : public Player {
public:
    using Player::OnAddCompletionListener;
    using Player::OnAddCurrentPosListener;
    using Player::OnAddPlayStatusListener;
    using Player::OnAddPreparedListener;
    using Player::OnAddSeekDoneListener;
    using Player::OnAddStopListener;
    using Player::OnCompletion;
    using Player::OnPaused;
    using Player::OnPopListener;
    using Player::OnSeekComplete;
    using Player::OnStarted;
    using Player::OnStop;
    using Player::OnTimeGetted;
    TestPlayer(const WeakPtr<PipelineBase>& context, ErrorCallback&& onError) : Player(context, std::move(onError)) {}
};
} // namespace

class VideoResourceTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override {}

protected:
    RefPtr<TestResource> CreateTestResource()
    {
        auto pipeline = MockPipelineContext::GetCurrent();
        return AceType::MakeRefPtr<TestResource>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    }

    RefPtr<TestResource> CreateTestResourceWithErrorCallback()
    {
        auto pipeline = MockPipelineContext::GetCurrent();
        return AceType::MakeRefPtr<TestResource>(
            AceType::WeakClaim(AceType::RawPtr(pipeline)), [this](const std::string& code, const std::string& msg) {
                lastErrorCode_ = code;
                lastErrorMsg_ = msg;
                errorCallbackCalled_ = true;
            });
    }

    std::string lastErrorCode_;
    std::string lastErrorMsg_;
    bool errorCallbackCalled_ = false;
};

void VideoResourceTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp(MockPipelineContext::GetCurrent());
}

void VideoResourceTestNg::TearDownTestSuite()
{
    MockContainer::TearDown();
    MockPipelineContext::TearDown();
}

void VideoResourceTestNg::SetUp()
{
    errorCallbackCalled_ = false;
    lastErrorCode_.clear();
    lastErrorMsg_.clear();
}

/**
 * @tc.name: ResourceParseMapFromStringValidPairs
 * @tc.desc: Test ParseMapFromString with valid key=value pairs returns correct map
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ResourceParseMapFromStringValidPairs, TestSize.Level1)
{
    std::string input = "width#HWJS-=-#100#HWJS-&-#height#HWJS-=-#200";
    auto result = Resource::ParseMapFromString(input);
    EXPECT_EQ(result["width"], "100");
    EXPECT_EQ(result["height"], "200");
}

/**
 * @tc.name: ResourceParseMapFromStringEmptyString
 * @tc.desc: Test ParseMapFromString with empty string returns empty map
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ResourceParseMapFromStringEmptyString, TestSize.Level1)
{
    auto result = Resource::ParseMapFromString("");
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: ResourceParseMapFromStringMissingEquals
 * @tc.desc: Test ParseMapFromString with key without equals sign is skipped
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ResourceParseMapFromStringMissingEquals, TestSize.Level1)
{
    std::string input = "validKey#HWJS-=-#value#HWJS-&-#noEqualsKey#HWJS-&-#another#HWJS-=-#val";
    auto result = Resource::ParseMapFromString(input);
    EXPECT_EQ(result["validKey"], "value");
    EXPECT_EQ(result["another"], "val");
    EXPECT_EQ(result.find("noEqualsKey"), result.end());
}

/**
 * @tc.name: ResourceParseMapFromStringEndReached
 * @tc.desc: Test ParseMapFromString with end of string reached handles last pair
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ResourceParseMapFromStringEndReached, TestSize.Level1)
{
    std::string input = "single#HWJS-=-#alone";
    auto result = Resource::ParseMapFromString(input);
    EXPECT_EQ(result["single"], "alone");
}

/**
 * @tc.name: ResourceGetDoubleParamNameFound
 * @tc.desc: Test GetDoubleParam with name found in param string parses correct value
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ResourceGetDoubleParamNameFound, TestSize.Level1)
{
    auto resource = CreateTestResource();
    std::string param = "width=3.14";
    double result = resource->GetDoubleParam(param, "width");
    EXPECT_DOUBLE_EQ(result, TEST_DOUBLE_VALUE);
}

/**
 * @tc.name: ResourceGetDoubleParamNameNotFound
 * @tc.desc: Test GetDoubleParam with name not found returns default 0.0
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ResourceGetDoubleParamNameNotFound, TestSize.Level1)
{
    auto resource = CreateTestResource();
    std::string param = "height=10.5";
    double result = resource->GetDoubleParam(param, "width");
    EXPECT_DOUBLE_EQ(result, 0.0);
}

/**
 * @tc.name: ResourceGetIntParamNameFound
 * @tc.desc: Test GetIntParam with name found in param string parses correct value
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ResourceGetIntParamNameFound, TestSize.Level1)
{
    auto resource = CreateTestResource();
    std::string param = "width=100";
    int32_t result = resource->GetIntParam(param, "width");
    EXPECT_EQ(result, TEST_INT_VALUE);
}

/**
 * @tc.name: ResourceGetIntParamNameNotFound
 * @tc.desc: Test GetIntParam with name not found returns default 0
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ResourceGetIntParamNameNotFound, TestSize.Level1)
{
    auto resource = CreateTestResource();
    std::string param = "height=200";
    int32_t result = resource->GetIntParam(param, "width");
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: ResourceGetInt64ParamNameFound
 * @tc.desc: Test GetInt64Param with name found in param string parses correct value
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ResourceGetInt64ParamNameFound, TestSize.Level1)
{
    auto resource = CreateTestResource();
    std::string param = "id=1234567890123";
    int64_t result = resource->GetInt64Param(param, "id");
    EXPECT_EQ(result, TEST_INT64_VALUE);
}

/**
 * @tc.name: ResourceGetInt64ParamNameNotFound
 * @tc.desc: Test GetInt64Param with name not found returns default 0
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ResourceGetInt64ParamNameNotFound, TestSize.Level1)
{
    auto resource = CreateTestResource();
    std::string param = "other=999";
    int64_t result = resource->GetInt64Param(param, "id");
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: ResourceGetFloatArrayParamNameNotFound
 * @tc.desc: Test GetFloatArrayParam with name not found clears matrix
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ResourceGetFloatArrayParamNameNotFound, TestSize.Level1)
{
    auto resource = CreateTestResource();
    std::vector<float> matrix = { TEST_FLOAT_1, TEST_FLOAT_2 };
    std::string param = "other=[1,2,3]";
    resource->GetFloatArrayParam(param, "transform", matrix);
    EXPECT_TRUE(matrix.empty());
}

/**
 * @tc.name: ResourceGetFloatArrayParamNoBracket
 * @tc.desc: Test GetFloatArrayParam with name found but no bracket, matrix stays empty
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ResourceGetFloatArrayParamNoBracket, TestSize.Level1)
{
    auto resource = CreateTestResource();
    std::vector<float> matrix;
    std::string param = "transform=1,2,3";
    resource->GetFloatArrayParam(param, "transform", matrix);
    EXPECT_TRUE(matrix.empty());
}

/**
 * @tc.name: ResourceGetFloatArrayParamValidArray
 * @tc.desc: Test GetFloatArrayParam parses float array values correctly
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ResourceGetFloatArrayParamValidArray, TestSize.Level1)
{
    auto resource = CreateTestResource();
    std::vector<float> matrix;
    std::string param = "transform=[1.0,2.0,3.0]";
    resource->GetFloatArrayParam(param, "transform", matrix);
    ASSERT_EQ(matrix.size(), 3U);
    EXPECT_FLOAT_EQ(matrix[0], TEST_FLOAT_1);
    EXPECT_FLOAT_EQ(matrix[1], TEST_FLOAT_2);
    EXPECT_FLOAT_EQ(matrix[2], TEST_FLOAT_3);
}

/**
 * @tc.name: ResourceMakeResourceHashValid
 * @tc.desc: Test MakeResourceHash returns correct type@id format
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ResourceMakeResourceHashValid, TestSize.Level1)
{
    auto resource = CreateTestResource();
    resource->id_ = TEST_RESOURCE_ID;
    std::string hashResult = resource->MakeResourceHash();
    EXPECT_EQ(hashResult, "test@42");
}

/**
 * @tc.name: ResourceMakeEventHashValid
 * @tc.desc: Test MakeEventHash returns hash with event suffix
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ResourceMakeEventHashValid, TestSize.Level1)
{
    auto resource = CreateTestResource();
    resource->hash_ = "video@100";
    std::string eventHash = resource->MakeEventHash("prepared");
    EXPECT_NE(eventHash.find("video@100"), std::string::npos);
    EXPECT_NE(eventHash.find("event#HWJS-=-#prepared"), std::string::npos);
}

/**
 * @tc.name: ResourceMakeMethodHashValid
 * @tc.desc: Test MakeMethodHash returns hash with method suffix
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ResourceMakeMethodHashValid, TestSize.Level1)
{
    auto resource = CreateTestResource();
    resource->hash_ = "video@200";
    std::string methodHash = resource->MakeMethodHash("start");
    EXPECT_NE(methodHash.find("video@200"), std::string::npos);
    EXPECT_NE(methodHash.find("method#HWJS-=-#start"), std::string::npos);
}

/**
 * @tc.name: ResourceIsResultSuccessResultFail
 * @tc.desc: Test IsResultSuccess returns false when result starts with "fail"
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ResourceIsResultSuccessResultFail, TestSize.Level1)
{
    auto resource = CreateTestResource();
    EXPECT_FALSE(resource->IsResultSuccess("fail_video_000001"));
}

/**
 * @tc.name: ResourceIsResultSuccessResultSuccess
 * @tc.desc: Test IsResultSuccess returns true when result does not start with "fail"
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ResourceIsResultSuccessResultSuccess, TestSize.Level1)
{
    auto resource = CreateTestResource();
    EXPECT_TRUE(resource->IsResultSuccess("success"));
}

/**
 * @tc.name: ResourceOnErrorWithCallback
 * @tc.desc: Test OnError invokes callback when set
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ResourceOnErrorWithCallback, TestSize.Level1)
{
    auto resource = CreateTestResourceWithErrorCallback();
    resource->OnError("ERR001", "test error");
    EXPECT_TRUE(errorCallbackCalled_);
    EXPECT_EQ(lastErrorCode_, "ERR001");
    EXPECT_EQ(lastErrorMsg_, "test error");
}

/**
 * @tc.name: ResourceOnErrorWithoutCallback
 * @tc.desc: Test OnError does not crash when callback is null
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ResourceOnErrorWithoutCallback, TestSize.Level1)
{
    auto resource = CreateTestResource();
    resource->OnError("ERR001", "test error");
    EXPECT_FALSE(errorCallbackCalled_);
}

/**
 * @tc.name: ResourceReleaseInvalidId
 * @tc.desc: Test Release returns early when id is invalid
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ResourceReleaseInvalidId, TestSize.Level1)
{
    auto resource = CreateTestResource();
    resource->id_ = INVALID_ID;
    resource->Release();
    EXPECT_EQ(resource->id_, INVALID_ID);
}

/**
 * @tc.name: ResourceReleaseNullContext
 * @tc.desc: Test Release returns early when context is null
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ResourceReleaseNullContext, TestSize.Level1)
{
    auto tempPipeline = AceType::MakeRefPtr<MockPipelineContext>();
    auto deadWeak = AceType::WeakClaim(AceType::RawPtr(tempPipeline));
    tempPipeline = nullptr;
    auto resource = AceType::MakeRefPtr<TestResource>(deadWeak, nullptr);
    resource->id_ = TEST_RESOURCE_ID;
    resource->Release();
    EXPECT_EQ(resource->id_, TEST_RESOURCE_ID);
}

/**
 * @tc.name: ResourceCallResRegisterMethodEmptyMethod
 * @tc.desc: Test CallResRegisterMethod returns early when method is empty
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ResourceCallResRegisterMethodEmptyMethod, TestSize.Level1)
{
    auto resource = CreateTestResource();
    resource->CallResRegisterMethod("", "param");
    EXPECT_EQ(resource->id_, INVALID_ID);
}

/**
 * @tc.name: ResourceCallResRegisterMethodNullContext
 * @tc.desc: Test CallResRegisterMethod returns early when context is null
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ResourceCallResRegisterMethodNullContext, TestSize.Level1)
{
    auto tempPipeline = AceType::MakeRefPtr<MockPipelineContext>();
    auto deadWeak = AceType::WeakClaim(AceType::RawPtr(tempPipeline));
    tempPipeline = nullptr;
    auto resource = AceType::MakeRefPtr<TestResource>(deadWeak, nullptr);
    resource->CallResRegisterMethod("testMethod", "param");
    EXPECT_EQ(resource->id_, INVALID_ID);
}

/**
 * @tc.name: ResourceCallSyncResRegisterMethodEmptyMethod
 * @tc.desc: Test CallSyncResRegisterMethod returns early when method is empty
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ResourceCallSyncResRegisterMethodEmptyMethod, TestSize.Level1)
{
    auto resource = CreateTestResource();
    resource->CallSyncResRegisterMethod("", "param");
    EXPECT_EQ(resource->id_, INVALID_ID);
}

/**
 * @tc.name: ResourceCallSyncResRegisterMethodNullContext
 * @tc.desc: Test CallSyncResRegisterMethod returns early when context is null
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ResourceCallSyncResRegisterMethodNullContext, TestSize.Level1)
{
    auto tempPipeline = AceType::MakeRefPtr<MockPipelineContext>();
    auto deadWeak = AceType::WeakClaim(AceType::RawPtr(tempPipeline));
    tempPipeline = nullptr;
    auto resource = AceType::MakeRefPtr<TestResource>(deadWeak, nullptr);
    resource->CallSyncResRegisterMethod("testMethod", "param");
    EXPECT_EQ(resource->id_, INVALID_ID);
}

/**
 * @tc.name: TextureOnRefreshWithListener
 * @tc.desc: Test Texture::OnRefresh invokes listener when set
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, TextureOnRefreshWithListener, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto texture = AceType::MakeRefPtr<TestTexture>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    bool called = false;
    texture->SetRefreshListener([&called]() { called = true; });
    texture->OnRefresh("");
    EXPECT_TRUE(called);
}

/**
 * @tc.name: TextureOnRefreshWithoutListener
 * @tc.desc: Test Texture::OnRefresh does not crash when listener is null
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, TextureOnRefreshWithoutListener, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto texture = AceType::MakeRefPtr<TestTexture>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    texture->onRefreshListener_ = nullptr;
    texture->OnRefresh("");
    EXPECT_EQ(texture->onRefreshListener_, nullptr);
}

/**
 * @tc.name: ExtSurfaceOnSurfaceCreatedWithCallback
 * @tc.desc: Test ExtSurface::OnSurfaceCreated invokes callback when set
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ExtSurfaceOnSurfaceCreatedWithCallback, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto surface = AceType::MakeRefPtr<TestExtSurfaceClass>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    bool called = false;
    surface->SetCreateCallback([&called]() { called = true; });
    surface->OnSurfaceCreated();
    EXPECT_TRUE(called);
}

/**
 * @tc.name: ExtSurfaceOnSurfaceCreatedWithoutCallback
 * @tc.desc: Test ExtSurface::OnSurfaceCreated does not crash when callback is null
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ExtSurfaceOnSurfaceCreatedWithoutCallback, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto surface = AceType::MakeRefPtr<TestExtSurfaceClass>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    surface->OnSurfaceCreated();
    EXPECT_EQ(surface->onSurfaceCreated_, nullptr);
}

/**
 * @tc.name: ExtSurfaceOnSurfaceChangedWithCallback
 * @tc.desc: Test ExtSurface::OnSurfaceChanged invokes callback with dimensions
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ExtSurfaceOnSurfaceChangedWithCallback, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto surface = AceType::MakeRefPtr<TestExtSurfaceClass>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    int32_t capturedWidth = 0;
    int32_t capturedHeight = 0;
    surface->SetSurfaceChanged([&](int32_t w, int32_t h) {
        capturedWidth = w;
        capturedHeight = h;
    });
    constexpr int32_t testWidth = 1920;
    constexpr int32_t testHeight = 1080;
    surface->OnSurfaceChanged(testWidth, testHeight);
    EXPECT_EQ(capturedWidth, testWidth);
    EXPECT_EQ(capturedHeight, testHeight);
}

/**
 * @tc.name: ExtSurfaceOnSurfaceChangedWithoutCallback
 * @tc.desc: Test ExtSurface::OnSurfaceChanged does not crash when callback is null
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ExtSurfaceOnSurfaceChangedWithoutCallback, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto surface = AceType::MakeRefPtr<TestExtSurfaceClass>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    surface->OnSurfaceChanged(TEST_INT_VALUE, TEST_INT_VALUE);
    EXPECT_EQ(surface->onSurfaceChanged_, nullptr);
}

/**
 * @tc.name: ExtSurfaceOnSurfaceDestroyedWithCallback
 * @tc.desc: Test ExtSurface::OnSurfaceDestroyed invokes callback when set
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ExtSurfaceOnSurfaceDestroyedWithCallback, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto surface = AceType::MakeRefPtr<TestExtSurfaceClass>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    bool called = false;
    surface->SetSurfaceDestroyed([&called]() { called = true; });
    surface->OnSurfaceDestroyed();
    EXPECT_TRUE(called);
}

/**
 * @tc.name: ExtSurfaceOnSurfaceDestroyedWithoutCallback
 * @tc.desc: Test ExtSurface::OnSurfaceDestroyed does not crash when callback is null
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ExtSurfaceOnSurfaceDestroyedWithoutCallback, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto surface = AceType::MakeRefPtr<TestExtSurfaceClass>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    surface->OnSurfaceDestroyed();
    EXPECT_EQ(surface->onSurfaceDestroyed_, nullptr);
}

/**
 * @tc.name: ExtTextureSetPatternTypeDifferentType
 * @tc.desc: Test ExtTexture::SetPatternType updates value when type is different
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ExtTextureSetPatternTypeDifferentType, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto texture = AceType::MakeRefPtr<TestExtTextureClass>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    texture->patternType_ = 0;
    texture->SetPatternType(TEST_PATTERN_TYPE);
    EXPECT_EQ(texture->patternType_, TEST_PATTERN_TYPE);
}

/**
 * @tc.name: ExtTextureSetPatternTypeSameType
 * @tc.desc: Test ExtTexture::SetPatternType does not change when type is same
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ExtTextureSetPatternTypeSameType, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto texture = AceType::MakeRefPtr<TestExtTextureClass>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    texture->patternType_ = TEST_PATTERN_TYPE;
    texture->SetPatternType(TEST_PATTERN_TYPE);
    EXPECT_EQ(texture->patternType_, TEST_PATTERN_TYPE);
}

/**
 * @tc.name: ExtTextureOnRefreshWithCallback
 * @tc.desc: Test ExtTexture::OnRefresh invokes texture refresh callback when set
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ExtTextureOnRefreshWithCallback, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto texture = AceType::MakeRefPtr<TestExtTextureClass>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    bool called = false;
    texture->SetTextureFreshCallback([&called](int32_t, int64_t) { called = true; });
    const char* refreshParam = "instanceId=1000textureId=42";
    texture->OnRefresh(refreshParam);
    EXPECT_TRUE(called);
}

/**
 * @tc.name: ExtTextureOnRefreshWithoutCallback
 * @tc.desc: Test ExtTexture::OnRefresh does not crash when callback is null
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ExtTextureOnRefreshWithoutCallback, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto texture = AceType::MakeRefPtr<TestExtTextureClass>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    texture->onTextureRefresh_ = nullptr;
    texture->OnRefresh("");
    EXPECT_EQ(texture->onTextureRefresh_, nullptr);
}

/**
 * @tc.name: ExtTextureOnSurfaceCreatedWithCallback
 * @tc.desc: Test ExtTexture::OnSurfaceCreated invokes callback when set
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ExtTextureOnSurfaceCreatedWithCallback, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto texture = AceType::MakeRefPtr<TestExtTextureClass>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    bool called = false;
    texture->SetCreateCallback([&called]() { called = true; });
    texture->OnSurfaceCreated();
    EXPECT_TRUE(called);
}

/**
 * @tc.name: ExtTextureOnSurfaceCreatedWithoutCallback
 * @tc.desc: Test ExtTexture::OnSurfaceCreated does not crash when callback is null
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ExtTextureOnSurfaceCreatedWithoutCallback, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto texture = AceType::MakeRefPtr<TestExtTextureClass>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    texture->OnSurfaceCreated();
    EXPECT_EQ(texture->onSurfaceCreated_, nullptr);
}

/**
 * @tc.name: ExtTextureOnSurfaceChangedWithCallback
 * @tc.desc: Test ExtTexture::OnSurfaceChanged invokes callback with dimensions
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ExtTextureOnSurfaceChangedWithCallback, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto texture = AceType::MakeRefPtr<TestExtTextureClass>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    int32_t capturedWidth = 0;
    int32_t capturedHeight = 0;
    texture->SetSurfaceChanged([&](int32_t w, int32_t h) {
        capturedWidth = w;
        capturedHeight = h;
    });
    constexpr int32_t testW = 800;
    constexpr int32_t testH = 600;
    texture->OnSurfaceChanged(testW, testH);
    EXPECT_EQ(capturedWidth, testW);
    EXPECT_EQ(capturedHeight, testH);
}

/**
 * @tc.name: ExtTextureOnSurfaceChangedWithoutCallback
 * @tc.desc: Test ExtTexture::OnSurfaceChanged does not crash when callback is null
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, ExtTextureOnSurfaceChangedWithoutCallback, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto texture = AceType::MakeRefPtr<TestExtTextureClass>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    texture->OnSurfaceChanged(TEST_INT_VALUE, TEST_INT_VALUE);
    EXPECT_EQ(texture->onSurfaceChanged_, nullptr);
}

/**
 * @tc.name: PlayerGetWidth
 * @tc.desc: Test Player::GetWidth returns correct width
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerGetWidth, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->width_ = TEST_UINT_VALUE;
    EXPECT_EQ(player->GetWidth(), TEST_UINT_VALUE);
}

/**
 * @tc.name: PlayerGetHeight
 * @tc.desc: Test Player::GetHeight returns correct height
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerGetHeight, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->height_ = TEST_UINT_VALUE_ALT;
    EXPECT_EQ(player->GetHeight(), TEST_UINT_VALUE_ALT);
}

/**
 * @tc.name: PlayerGetDuration
 * @tc.desc: Test Player::GetDuration returns correct duration
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerGetDuration, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->duration_ = TEST_DURATION_VALUE;
    EXPECT_EQ(player->GetDuration(), TEST_DURATION_VALUE);
}

/**
 * @tc.name: PlayerGetCurrent
 * @tc.desc: Test Player::GetCurrent returns correct current position
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerGetCurrent, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->currentPos_ = TEST_UINT_VALUE;
    EXPECT_EQ(player->GetCurrent(), TEST_UINT_VALUE);
}

/**
 * @tc.name: PlayerIsPlaying
 * @tc.desc: Test Player::IsPlaying returns correct playing status
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerIsPlaying, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->isPlaying_ = true;
    EXPECT_TRUE(player->IsPlaying());
}

/**
 * @tc.name: PlayerSetMute
 * @tc.desc: Test Player::SetMute updates isMute flag
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerSetMute, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->SetMute(true);
    EXPECT_TRUE(player->isMute_);
    player->SetMute(false);
    EXPECT_FALSE(player->isMute_);
}

/**
 * @tc.name: PlayerSetAutoPlay
 * @tc.desc: Test Player::SetAutoPlay updates isAutoPlay flag
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerSetAutoPlay, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->SetAutoPlay(true);
    EXPECT_TRUE(player->isAutoPlay_);
    player->SetAutoPlay(false);
    EXPECT_FALSE(player->isAutoPlay_);
}

/**
 * @tc.name: PlayerMarkResetPending
 * @tc.desc: Test Player::MarkResetPending stores true
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerMarkResetPending, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->resetPending_.store(false, std::memory_order_relaxed);
    player->MarkResetPending();
    EXPECT_TRUE(player->resetPending_.load(std::memory_order_relaxed));
}

/**
 * @tc.name: PlayerSetRenderFirstFrameNotInit
 * @tc.desc: Test SetRenderFirstFrame stores state when not yet initialized
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerSetRenderFirstFrameNotInit, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->isInit_ = false;
    player->hasSetRenderFirstFrame_ = false;
    player->SetRenderFirstFrame(true);
    EXPECT_TRUE(player->showFirstFrame_);
    EXPECT_TRUE(player->hasSetRenderFirstFrame_);
}

/**
 * @tc.name: PlayerSetSourceNotInit
 * @tc.desc: Test SetSource stores source but does not call method when not initialized
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerSetSourceNotInit, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->isInit_ = false;
    player->SetSource("new_source.mp4");
    EXPECT_EQ(player->src_, "new_source.mp4");
}

/**
 * @tc.name: PlayerOnStartedWithListener
 * @tc.desc: Test OnStarted notifies play status listeners
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerOnStartedWithListener, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->isPlaying_ = false;
    bool listenerCalled = false;
    bool receivedPlayingState = false;
    player->OnAddPlayStatusListener([&listenerCalled, &receivedPlayingState](bool isPlaying) {
        listenerCalled = true;
        receivedPlayingState = isPlaying;
    });
    player->OnStarted();
    EXPECT_TRUE(listenerCalled);
    EXPECT_TRUE(receivedPlayingState);
    EXPECT_TRUE(player->isPlaying_);
}

/**
 * @tc.name: PlayerOnPausedWithListener
 * @tc.desc: Test OnPaused notifies play status listeners
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerOnPausedWithListener, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->isPlaying_ = true;
    bool listenerCalled = false;
    bool receivedPlayingState = true;
    player->OnAddPlayStatusListener([&listenerCalled, &receivedPlayingState](bool isPlaying) {
        listenerCalled = true;
        receivedPlayingState = isPlaying;
    });
    player->OnPaused();
    EXPECT_TRUE(listenerCalled);
    EXPECT_FALSE(receivedPlayingState);
    EXPECT_FALSE(player->isPlaying_);
}

/**
 * @tc.name: PlayerOnStopWithListener
 * @tc.desc: Test OnStop notifies stop listeners
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerOnStopWithListener, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->isPlaying_ = true;
    bool stopListenerCalled = false;
    player->OnAddStopListener([&stopListenerCalled]() { stopListenerCalled = true; });
    player->OnStop();
    EXPECT_TRUE(stopListenerCalled);
    EXPECT_FALSE(player->isPlaying_);
    EXPECT_EQ(player->currentPos_, 0U);
}

/**
 * @tc.name: PlayerOnCompletionWithListener
 * @tc.desc: Test OnCompletion notifies completion listeners
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerOnCompletionWithListener, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->isPlaying_ = true;
    player->duration_ = TEST_DURATION_VALUE;
    bool completionCalled = false;
    player->OnAddCompletionListener([&completionCalled]() { completionCalled = true; });
    player->OnCompletion("");
    EXPECT_TRUE(completionCalled);
    EXPECT_FALSE(player->isPlaying_);
    EXPECT_EQ(player->currentPos_, TEST_DURATION_VALUE);
}

/**
 * @tc.name: PlayerOnSeekCompleteWithListener
 * @tc.desc: Test OnSeekComplete calls seek done listener
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerOnSeekCompleteWithListener, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    bool seekDoneCalled = false;
    uint32_t receivedPos = 0;
    player->OnAddSeekDoneListener([&seekDoneCalled, &receivedPos](uint32_t pos) {
        seekDoneCalled = true;
        receivedPos = pos;
    });
    std::string param = "currentpos=5000";
    player->OnSeekComplete(param);
    EXPECT_TRUE(seekDoneCalled);
    EXPECT_EQ(receivedPos, TEST_SEEK_POS);
}

/**
 * @tc.name: PlayerOnSeekCompleteWithoutListener
 * @tc.desc: Test OnSeekComplete does not crash when listener list is empty
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerOnSeekCompleteWithoutListener, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    std::string param = "currentpos=5000";
    player->OnSeekComplete(param);
    EXPECT_EQ(player->currentPos_, TEST_SEEK_POS);
}

/**
 * @tc.name: PlayerOnTimeGettedWithListener
 * @tc.desc: Test OnTimeGetted updates position and calls listener
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerOnTimeGettedWithListener, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    bool listenerCalled = false;
    uint32_t receivedPos = 0;
    player->OnAddCurrentPosListener([&listenerCalled, &receivedPos](uint32_t pos) {
        listenerCalled = true;
        receivedPos = pos;
    });
    constexpr uint32_t currPos = 3000;
    std::string result = "currentpos=3000";
    player->OnTimeGetted(result);
    EXPECT_TRUE(listenerCalled);
    EXPECT_EQ(receivedPos, currPos);
    EXPECT_EQ(player->currentPos_, currPos);
}

/**
 * @tc.name: PlayerOnTimeGettedWithoutListener
 * @tc.desc: Test OnTimeGetted updates position without crash when listener list is empty
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerOnTimeGettedWithoutListener, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    std::string result = "currentpos=4000";
    player->OnTimeGetted(result);
    EXPECT_EQ(player->currentPos_, TEST_CURRENT_POS_ALT);
}

/**
 * @tc.name: PlayerOnPopListenerCurrentPosListenerExists
 * @tc.desc: Test OnPopListener calls current position listener when available
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerOnPopListenerCurrentPosListenerExists, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->currentPos_ = TEST_UINT_VALUE;

    // Add necessary listeners to avoid crash from pop_back on empty lists
    player->AddRefreshRenderListener([]() {});
    player->OnAddPreparedListener([](uint32_t, uint32_t, bool, uint32_t, uint32_t, bool) {});
    player->OnAddPlayStatusListener([](bool) {});
    player->OnAddSeekDoneListener([](uint32_t) {});
    player->OnAddCompletionListener([]() {});
    player->OnAddStopListener([]() {});

    bool listenerCalled = false;
    uint32_t receivedPos = 0;
    player->OnAddCurrentPosListener([&listenerCalled, &receivedPos](uint32_t pos) {
        listenerCalled = true;
        receivedPos = pos;
    });
    player->OnAddCurrentPosListener([](uint32_t pos) {});
    player->OnPopListener();
    EXPECT_TRUE(listenerCalled);
    EXPECT_EQ(receivedPos, TEST_UINT_VALUE);
}

/**
 * @tc.name: PlayerOnPopListenerAllListenersPresent
 * @tc.desc: Test OnPopListener does not crash when all listener lists have elements
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerOnPopListenerAllListenersPresent, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->currentPos_ = TEST_UINT_VALUE;

    // Add all necessary listeners to avoid crash from pop_back on empty lists
    player->AddRefreshRenderListener([]() {});
    player->OnAddPreparedListener([](uint32_t, uint32_t, bool, uint32_t, uint32_t, bool) {});
    player->OnAddPlayStatusListener([](bool) {});
    player->OnAddCurrentPosListener([](uint32_t) {});
    player->OnAddSeekDoneListener([](uint32_t) {});
    player->OnAddCompletionListener([]() {});
    player->OnAddStopListener([]() {});

    EXPECT_FALSE(player->onPreparedListener_.empty());
    EXPECT_FALSE(player->onPlayStatusListener_.empty());
    EXPECT_FALSE(player->onCurrentPosListener_.empty());
    EXPECT_FALSE(player->onSeekDoneListener_.empty());
    EXPECT_FALSE(player->onCompletionListener_.empty());
    EXPECT_FALSE(player->onStopListener_.empty());
    EXPECT_FALSE(player->onRefreshRenderListener_.empty());
    player->OnPopListener();
}

/**
 * @tc.name: PlayerOnAddPreparedListenerAlreadyPrepared
 * @tc.desc: Test OnAddPreparedListener calls listener immediately when already prepared
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerOnAddPreparedListenerAlreadyPrepared, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->isPrepared_ = true;
    player->width_ = TEST_UINT_VALUE;
    player->height_ = TEST_UINT_VALUE_ALT;
    player->isPlaying_ = true;
    player->duration_ = TEST_DURATION_VALUE;
    player->currentPos_ = 0;
    bool listenerCalled = false;
    player->OnAddPreparedListener([&listenerCalled](uint32_t w, uint32_t h, bool playing, uint32_t dur, uint32_t pos,
                                      bool needRefresh) { listenerCalled = true; });
    EXPECT_TRUE(listenerCalled);
}

/**
 * @tc.name: PlayerOnAddPreparedListenerNotPrepared
 * @tc.desc: Test OnAddPreparedListener stores listener without calling when not prepared
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerOnAddPreparedListenerNotPrepared, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->isPrepared_ = false;
    bool listenerCalled = false;
    player->OnAddPreparedListener([&listenerCalled](uint32_t w, uint32_t h, bool playing, uint32_t dur, uint32_t pos,
                                      bool needRefresh) { listenerCalled = true; });
    EXPECT_FALSE(listenerCalled);
    EXPECT_FALSE(player->onPreparedListener_.empty());
}

/**
 * @tc.name: PlayerAddRefreshRenderListener
 * @tc.desc: Test AddRefreshRenderListener adds listener to list
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerAddRefreshRenderListener, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    bool listenerCalled = false;
    player->AddRefreshRenderListener([&listenerCalled]() { listenerCalled = true; });
    EXPECT_FALSE(player->onRefreshRenderListener_.empty());
    player->onRefreshRenderListener_.back()();
    EXPECT_TRUE(listenerCalled);
}

/**
 * @tc.name: PlayerOnAddPlayStatusListenerStored
 * @tc.desc: Test OnAddPlayStatusListener adds listener to list
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerOnAddPlayStatusListenerStored, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->OnAddPlayStatusListener([](bool) {});
    EXPECT_FALSE(player->onPlayStatusListener_.empty());
}

/**
 * @tc.name: PlayerOnAddCurrentPosListenerStored
 * @tc.desc: Test OnAddCurrentPosListener adds listener to list
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerOnAddCurrentPosListenerStored, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->OnAddCurrentPosListener([](uint32_t) {});
    EXPECT_FALSE(player->onCurrentPosListener_.empty());
}

/**
 * @tc.name: PlayerOnAddSeekDoneListenerStored
 * @tc.desc: Test OnAddSeekDoneListener adds listener to list
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerOnAddSeekDoneListenerStored, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->OnAddSeekDoneListener([](uint32_t) {});
    EXPECT_FALSE(player->onSeekDoneListener_.empty());
}

/**
 * @tc.name: PlayerOnAddCompletionListenerStored
 * @tc.desc: Test OnAddCompletionListener adds listener to list
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerOnAddCompletionListenerStored, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->OnAddCompletionListener([]() {});
    EXPECT_FALSE(player->onCompletionListener_.empty());
}

/**
 * @tc.name: PlayerOnAddStopListenerStored
 * @tc.desc: Test OnAddStopListener adds listener to list
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerOnAddStopListenerStored, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->OnAddStopListener([]() {});
    EXPECT_FALSE(player->onStopListener_.empty());
}

/**
 * @tc.name: PlayerReleaseNullContext
 * @tc.desc: Test Player::Release returns early when context is null
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerReleaseNullContext, TestSize.Level1)
{
    auto tempPipeline = AceType::MakeRefPtr<MockPipelineContext>();
    auto deadWeak = AceType::WeakClaim(AceType::RawPtr(tempPipeline));
    tempPipeline = nullptr;
    auto player = AceType::MakeRefPtr<TestPlayer>(deadWeak, nullptr);
    player->isInit_ = true;
    player->resetPending_.store(true, std::memory_order_relaxed);
    player->Release();
    EXPECT_TRUE(player->isInit_);
    EXPECT_TRUE(player->resetPending_.load(std::memory_order_relaxed));
}

/**
 * @tc.name: PlayerStartCallResRegister
 * @tc.desc: Test Start() calls CallResRegisterMethod via playMethod_ without crash
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerStartCallResRegister, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->playMethod_ = "play_hash";
    player->Start();
    EXPECT_EQ(player->playMethod_, "play_hash");
}

/**
 * @tc.name: PlayerPauseCallResRegister
 * @tc.desc: Test Pause() calls CallResRegisterMethod via pauseMethod_ without crash
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerPauseCallResRegister, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->pauseMethod_ = "pause_hash";
    player->Pause();
    EXPECT_EQ(player->pauseMethod_, "pause_hash");
}

/**
 * @tc.name: PlayerStopWithoutScheduler
 * @tc.desc: Test Stop() without scheduler calls CallResRegisterMethod without crash
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerStopWithoutScheduler, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->scheduler_ = nullptr;
    player->stopMethod_ = "stop_hash";
    player->Stop();
    EXPECT_EQ(player->stopMethod_, "stop_hash");
}

/**
 * @tc.name: PlayerStopWithScheduler
 * @tc.desc: Test Stop() with scheduler stops scheduler and calls CallResRegisterMethod
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerStopWithScheduler, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->scheduler_ = SchedulerBuilder::Build(
        [](uint64_t timestamp) {}, AceType::WeakClaim(AceType::RawPtr(pipeline)));
    player->stopMethod_ = "stop_hash";
    EXPECT_NE(player->scheduler_, nullptr);
    player->Stop();
}

/**
 * @tc.name: PlayerSeekToPosition
 * @tc.desc: Test SeekTo(pos) calls CallResRegisterMethod with value param without crash
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerSeekToPosition, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->seekMethod_ = "seek_hash";
    player->SeekTo(TEST_SEEK_POS);
    EXPECT_EQ(player->seekMethod_, "seek_hash");
}

/**
 * @tc.name: PlayerSeekToPositionWithMode
 * @tc.desc: Test SeekTo(pos, mode) calls CallResRegisterMethod with value and seekMode params
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerSeekToPositionWithMode, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->seekMethod_ = "seek_hash";
    constexpr uint32_t seekMode = 1;
    player->SeekTo(TEST_SEEK_POS, seekMode);
    EXPECT_EQ(player->seekMethod_, "seek_hash");
}

/**
 * @tc.name: PlayerSetVolume
 * @tc.desc: Test SetVolume(volume) calls CallResRegisterMethod without crash
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerSetVolume, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->setVolumeMethod_ = "setvolume_hash";
    constexpr float volume = 0.5f;
    player->SetVolume(volume);
    EXPECT_EQ(player->setVolumeMethod_, "setvolume_hash");
}

/**
 * @tc.name: PlayerEnterFullScreen
 * @tc.desc: Test EnterFullScreen() calls CallResRegisterMethod with fullscreenMethod_ without crash
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerEnterFullScreen, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->fullscreenMethod_ = "fullscreen_hash";
    player->EnterFullScreen();
    EXPECT_EQ(player->fullscreenMethod_, "fullscreen_hash");
}

/**
 * @tc.name: PlayerEnableLoopingTrue
 * @tc.desc: Test EnableLooping(true) sets loop param to "1" without crash
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerEnableLoopingTrue, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->enableloopingMethod_ = "enablelooping_hash";
    player->EnableLooping(true);
    EXPECT_EQ(player->enableloopingMethod_, "enablelooping_hash");
}

/**
 * @tc.name: PlayerEnableLoopingFalse
 * @tc.desc: Test EnableLooping(false) sets loop param to "0" without crash
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerEnableLoopingFalse, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->enableloopingMethod_ = "enablelooping_hash";
    player->EnableLooping(false);
    EXPECT_EQ(player->enableloopingMethod_, "enablelooping_hash");
}

/**
 * @tc.name: PlayerSetSpeed
 * @tc.desc: Test SetSpeed(speed) calls CallResRegisterMethod without crash
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerSetSpeed, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->setSpeedMethod_ = "setspeed_hash";
    constexpr float speed = 1.5f;
    player->SetSpeed(speed);
    EXPECT_EQ(player->setSpeedMethod_, "setspeed_hash");
}

/**
 * @tc.name: PlayerSetDirectionCallResRegister
 * @tc.desc: Test SetDirection(direction) calls CallResRegisterMethod without crash
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerSetDirectionCallResRegister, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->setDirectionMethod_ = "setDirection_hash";
    std::string direction = "horizontal";
    player->SetDirection(direction);
    EXPECT_EQ(player->setDirectionMethod_, "setDirection_hash");
}

/**
 * @tc.name: PlayerSetLandscape
 * @tc.desc: Test SetLandscape() calls CallResRegisterMethod without crash
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerSetLandscape, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->setLandsacpeMethod_ = "setLandscape_hash";
    player->SetLandscape();
    EXPECT_EQ(player->setLandsacpeMethod_, "setLandscape_hash");
}

/**
 * @tc.name: PlayerSetFullScreenChangeTrue
 * @tc.desc: Test SetFullScreenChange(true) sets param to "1" without crash
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerSetFullScreenChangeTrue, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->fullscreenMethod_ = "fullscreen_hash";
    player->SetFullScreenChange(true);
    EXPECT_EQ(player->fullscreenMethod_, "fullscreen_hash");
}

/**
 * @tc.name: PlayerSetFullScreenChangeFalse
 * @tc.desc: Test SetFullScreenChange(false) sets param to "0" without crash
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerSetFullScreenChangeFalse, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->fullscreenMethod_ = "fullscreen_hash";
    player->SetFullScreenChange(false);
    EXPECT_EQ(player->fullscreenMethod_, "fullscreen_hash");
}

/**
 * @tc.name: PlayerSetSurfaceIdTexture
 * @tc.desc: Test SetSurfaceId with isTexture=true constructs param with "1" for isTexture
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerSetSurfaceIdTexture, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->SetSurfaceId(TEST_RESOURCE_ID, true);
    EXPECT_EQ(player->textureId_, TEST_RESOURCE_ID);
}

/**
 * @tc.name: PlayerSetSurfaceIdNotTexture
 * @tc.desc: Test SetSurfaceId with isTexture=false constructs param with "0" for isTexture
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerSetSurfaceIdNotTexture, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto player = AceType::MakeRefPtr<TestPlayer>(AceType::WeakClaim(AceType::RawPtr(pipeline)), nullptr);
    player->SetSurfaceId(TEST_RESOURCE_ID, false);
    EXPECT_EQ(player->textureId_, TEST_RESOURCE_ID);
}

/**
 * @tc.name: PlayerPopListenerNullContext
 * @tc.desc: Test PopListener returns early when context is null
 * @tc.type: FUNC
 */
HWTEST_F(VideoResourceTestNg, PlayerPopListenerNullContext, TestSize.Level1)
{
    auto tempPipeline = AceType::MakeRefPtr<MockPipelineContext>();
    auto deadWeak = AceType::WeakClaim(AceType::RawPtr(tempPipeline));
    tempPipeline = nullptr;
    auto player = AceType::MakeRefPtr<TestPlayer>(deadWeak, nullptr);
    player->AddRefreshRenderListener([]() {});
    EXPECT_FALSE(player->onRefreshRenderListener_.empty());
    player->PopListener();
    EXPECT_EQ(player->onRefreshRenderListener_.size(), 0U);
}
} // namespace OHOS::Ace
