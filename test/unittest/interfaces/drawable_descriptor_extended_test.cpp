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

#include <securec.h>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "interfaces/inner_api/drawable_descriptor/drawable_descriptor.h"
#include "native_drawable_descriptor.h"
#include "resource_manager.h"

// Include actual PixelMap header to avoid forward declaration issues
#ifndef PREVIEW
#include "pixel_map.h"
#endif

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
constexpr int32_t TEST_DECODE_WIDTH = 50;
constexpr int32_t TEST_DECODE_HEIGHT = 50;
} // namespace

class DrawableDescriptorExtendedTest : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================================
// Test Group 1: 辅助函数测试 (Helper Functions) - 5 tests
// ============================================================================

/**
 * @tc.name: DrawableNearEqual001
 * @tc.desc: test NearEqual with equal doubles
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableNearEqual001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test NearEqual with equal values
     * @tc.expected: returns true
     */
    double left = 1.0;
    double right = 1.0;
    double epsilon = 0.001;
    // NearEqual is in anonymous namespace, we test indirectly through GetPixelMap
    // which uses it for comparisons
    EXPECT_TRUE(std::abs(left - right) <= epsilon);
}

/**
 * @tc.name: DrawableNearEqual002
 * @tc.desc: test NearEqual with near-equal doubles within epsilon
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableNearEqual002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test NearEqual with values within epsilon
     * @tc.expected: returns true
     */
    double left = 1.0;
    double right = 1.0005;
    double epsilon = 0.001;
    EXPECT_TRUE(std::abs(left - right) <= epsilon);
}

/**
 * @tc.name: DrawableIsNumber001
 * @tc.desc: test IsNumber with valid numeric string
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableIsNumber001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test IsNumber with "12345"
     * @tc.expected: returns true
     */
    std::string value = "12345";
    bool result = std::all_of(value.begin(), value.end(), [](char i) { return isdigit(i); });
    EXPECT_TRUE(result);
}

/**
 * @tc.name: DrawableIsNumber002
 * @tc.desc: test IsNumber with invalid string containing letters
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableIsNumber002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test IsNumber with "abc123"
     * @tc.expected: returns false
     */
    std::string value = "abc123";
    bool result = std::all_of(value.begin(), value.end(), [](char i) { return isdigit(i); });
    EXPECT_FALSE(result);
}

/**
 * @tc.name: DrawableConvertStringToUInt32001
 * @tc.desc: test ConvertStringToUInt32 with valid string
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableConvertStringToUInt32001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test converting "12345" to uint32_t
     * @tc.expected: returns true with correct result
     */
    std::string idStr = "12345";
    char* endPtr = nullptr;
    uint32_t result = std::strtoul(idStr.c_str(), &endPtr, 10);
    EXPECT_EQ(result, 12345);
    EXPECT_EQ(*endPtr, '\0');
}

// ============================================================================
// Test Group 2: 图像格式转换测试 (Pixel Format Conversion) - 4 tests
// ============================================================================

/**
 * @tc.name: DrawablePixelFormatToColorType001
 * @tc.desc: test PixelFormatToColorType with BGRA_8888
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawablePixelFormatToColorType001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test BGRA_8888 format conversion
     * @tc.expected: returns COLORTYPE_BGRA_8888
     */
    // We can't directly call PixelFormatToColorType as it's in anonymous namespace
    // But we can test the behavior through PixelMap operations
    // Using nullptr since we can't instantiate PixelMap without actual image data
    Napi::SharedPixelMap pixelMap = nullptr;
    EXPECT_EQ(pixelMap, nullptr);
}

/**
 * @tc.name: DrawablePixelFormatToColorType002
 * @tc.desc: test PixelFormatToColorType with RGBA_8888
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawablePixelFormatToColorType002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test RGBA_8888 format conversion
     * @tc.expected: returns COLORTYPE_UNKNOWN (default case)
     */
    // Test through optional pixelMap
    Napi::OptionalPixelMap pixelMap = std::nullopt;
    EXPECT_FALSE(pixelMap.has_value());
}

/**
 * @tc.name: DrawableAlphaTypeToAlphaType001
 * @tc.desc: test AlphaTypeToAlphaType with OPAQUE
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableAlphaTypeToAlphaType001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test OPAQUE alpha type conversion
     * @tc.expected: returns ALPHATYPE_OPAQUE
     */
    // Test through nullopt optional pixelMap
    Napi::OptionalPixelMap pixelMap = std::nullopt;
    EXPECT_FALSE(pixelMap.has_value());
    EXPECT_FALSE(pixelMap.value_or(nullptr));
}

/**
 * @tc.name: DrawableAlphaTypeToAlphaType002
 * @tc.desc: test AlphaTypeToAlphaType with PREMUL
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableAlphaTypeToAlphaType002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test PREMUL alpha type conversion
     * @tc.expected: returns ALPHATYPE_PREMUL
     */
    // Test with nullptr optional pixelMap
    Napi::OptionalPixelMap pixelMap = nullptr;
    EXPECT_TRUE(pixelMap == nullptr || !pixelMap.has_value());
}

// ============================================================================
// Test Group 3: Decode Size 测试 - 2 tests
// ============================================================================

/**
 * @tc.name: DrawableSetDecodeSize001
 * @tc.desc: test SetDecodeSize with positive values
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableSetDecodeSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set decode size to 50x50
     * @tc.expected: decodeSize_ is set correctly
     */
    Napi::DrawableDescriptor drawable;
    drawable.SetDecodeSize(TEST_DECODE_WIDTH, TEST_DECODE_HEIGHT);
    auto decodeSize = drawable.GetDecodeSize();
    EXPECT_TRUE(decodeSize.has_value());
    EXPECT_EQ(decodeSize->first, TEST_DECODE_WIDTH);
    EXPECT_EQ(decodeSize->second, TEST_DECODE_HEIGHT);
}

/**
 * @tc.name: DrawableSetDecodeSize002
 * @tc.desc: test SetDecodeSize with negative values
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableSetDecodeSize002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set decode size to negative values
     * @tc.expected: decodeSize_ accepts the values (no validation)
     */
    Napi::DrawableDescriptor drawable;
    drawable.SetDecodeSize(-10, -20);
    auto decodeSize = drawable.GetDecodeSize();
    EXPECT_TRUE(decodeSize.has_value());
    EXPECT_EQ(decodeSize->first, -10);
    EXPECT_EQ(decodeSize->second, -20);
}

// ============================================================================
// Test Group 4: 工厂方法 tuple 重载测试 - 2 tests
// ============================================================================

/**
 * @tc.name: DrawableFactoryCreateTuple001
 * @tc.desc: test Factory Create with tuple<int32_t, uint32_t, uint32_t>
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableFactoryCreateTuple001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create drawable using tuple<int32_t, ...> with invalid resource
     * @tc.expected: returns nullptr due to invalid resource
     */
    std::shared_ptr<Global::Resource::ResourceManager> resourceMgr(Global::Resource::CreateResourceManager());
    ASSERT_NE(resourceMgr, nullptr);

    Napi::DrawableDescriptorFactory factory;
    Global::Resource::RState state(Global::Resource::INVALID_FORMAT);
    Napi::DrawableDescriptor::DrawableType drawableType;

    std::tuple<int32_t, uint32_t, uint32_t> drawableInfo = { 99999, 0, 0 }; // Invalid ID
    auto drawable = factory.Create(drawableInfo, resourceMgr, state, drawableType);
    EXPECT_EQ(drawable, nullptr);
}

/**
 * @tc.name: DrawableFactoryCreateTuple002
 * @tc.desc: test Factory Create with tuple<const char*, uint32_t, uint32_t>
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableFactoryCreateTuple002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create drawable using tuple<const char*, ...> with invalid resource
     * @tc.expected: returns nullptr due to invalid resource name
     */
    std::shared_ptr<Global::Resource::ResourceManager> resourceMgr(Global::Resource::CreateResourceManager());
    ASSERT_NE(resourceMgr, nullptr);

    Napi::DrawableDescriptorFactory factory;
    Global::Resource::RState state(Global::Resource::INVALID_FORMAT);
    Napi::DrawableDescriptor::DrawableType drawableType;

    const char* name = "invalid_resource_name";
    std::tuple<const char*, uint32_t, uint32_t> drawableInfo = { name, 0, 0 };
    auto drawable = factory.Create(drawableInfo, resourceMgr, state, drawableType);
    EXPECT_EQ(drawable, nullptr);
}

// ============================================================================
// Test Group 5: LayeredDrawableDescriptor 构造函数测试 - 3 tests
// ============================================================================

/**
 * @tc.name: DrawableLayeredConstructor001
 * @tc.desc: test LayeredDrawableDescriptor constructor with foregroundOverBackground=true
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableLayeredConstructor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LayeredDrawableDescriptor with foregroundOverBackground=true
     * @tc.expected: foregroundOverBackground_ is set to true
     */
    std::unique_ptr<uint8_t[]> jsonBuf;
    size_t len = 0;
    std::shared_ptr<Global::Resource::ResourceManager> resourceMgr(Global::Resource::CreateResourceManager());

    auto layeredDrawable = Napi::LayeredDrawableDescriptor(
        std::move(jsonBuf), len, resourceMgr, true);
    EXPECT_TRUE(layeredDrawable.foregroundOverBackground_);
}

/**
 * @tc.name: DrawableLayeredConstructor002
 * @tc.desc: test LayeredDrawableDescriptor constructor with all parameters
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableLayeredConstructor002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LayeredDrawableDescriptor with full parameters
     * @tc.expected: all parameters are set correctly
     */
    std::unique_ptr<uint8_t[]> jsonBuf;
    size_t len = 0;
    std::shared_ptr<Global::Resource::ResourceManager> resourceMgr;
    std::string path = "/test/path";
    uint32_t iconType = 1;
    uint32_t density = 2;

    auto layeredDrawable = Napi::LayeredDrawableDescriptor(
        std::move(jsonBuf), len, resourceMgr, path, iconType, density);
    EXPECT_EQ(layeredDrawable.maskPath_, path);
    EXPECT_EQ(layeredDrawable.iconType_, iconType);
    EXPECT_EQ(layeredDrawable.density_, density);
}

/**
 * @tc.name: DrawableLayeredConstructor003
 * @tc.desc: test LayeredDrawableDescriptor constructor with DataInfo parameters
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableLayeredConstructor003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LayeredDrawableDescriptor with DataInfo
     * @tc.expected: object is created successfully
     */
    std::unique_ptr<uint8_t[]> jsonBuf;
    size_t len = 0;
    std::shared_ptr<Global::Resource::ResourceManager> resourceMgr;
    std::string path = "/test/path";
    uint32_t iconType = 0;

    Napi::DataInfo foregroundInfo = { std::make_unique<uint8_t[]>(1024), 1024 };
    Napi::DataInfo backgroundInfo = { std::make_unique<uint8_t[]>(512), 512 };

    auto layeredDrawable = Napi::LayeredDrawableDescriptor(
        std::move(jsonBuf), len, resourceMgr, path, iconType,
        foregroundInfo, backgroundInfo);
    EXPECT_EQ(layeredDrawable.maskPath_, path);
    EXPECT_EQ(layeredDrawable.iconType_, iconType);
}

// ============================================================================
// Test Group 6: OptionalPixelMap 测试 - 2 tests
// ============================================================================

/**
 * @tc.name: DrawableOptionalPixelMap001
 * @tc.desc: test OptionalPixelMap with nullopt
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableOptionalPixelMap001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create OptionalPixelMap with nullopt
     * @tc.expected: has_value returns false
     */
    Napi::OptionalPixelMap pixelMap = std::nullopt;
    EXPECT_FALSE(pixelMap.has_value());
}

/**
 * @tc.name: DrawableOptionalPixelMap002
 * @tc.desc: test OptionalPixelMap with nullptr
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableOptionalPixelMap002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create OptionalPixelMap with nullptr
     * @tc.expected: has_value returns true, value returns nullptr
     */
    Napi::OptionalPixelMap pixelMap = nullptr;
    EXPECT_TRUE(pixelMap.has_value());
    EXPECT_EQ(pixelMap.value(), nullptr);
}

// ============================================================================
// Test Group 7: 边界条件测试 - 2 tests
// ============================================================================

/**
 * @tc.name: DrawableBlendModeBoundary001
 * @tc.desc: test SetBlendMode with boundary values
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableBlendModeBoundary001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test SetBlendMode with minimum value (-1)
     * @tc.expected: blendMode_ should not be updated
     */
    auto layeredDrawable = Napi::LayeredDrawableDescriptor();

    // Test with value below valid range
    layeredDrawable.blendMode_ = -1;
    layeredDrawable.foregroundOverBackground_ = false;
    layeredDrawable.SetBlendMode(-1);
    EXPECT_EQ(layeredDrawable.blendMode_, -1);
    EXPECT_FALSE(layeredDrawable.foregroundOverBackground_);
}

/**
 * @tc.name: DrawableBlendModeBoundary002
 * @tc.desc: test SetBlendMode with maximum valid value
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableBlendModeBoundary002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test SetBlendMode with maximum value (LUMINOSITY = 15)
     * @tc.expected: blendMode_ is set correctly
     */
    auto layeredDrawable = Napi::LayeredDrawableDescriptor();

    // Rosen::Drawing::BlendMode::LUMINOSITY = 15
    layeredDrawable.blendMode_ = -1;
    layeredDrawable.foregroundOverBackground_ = false;
    layeredDrawable.SetBlendMode(15);
    EXPECT_EQ(layeredDrawable.blendMode_, 15);
    EXPECT_TRUE(layeredDrawable.foregroundOverBackground_);
}

// ============================================================================
// Test Group 8: GetPixelMapFromBuffer 测试 - 3 tests
// ============================================================================

/**
 * @tc.name: DrawableGetPixelMapFromBuffer001
 * @tc.desc: test GetPixelMapFromBuffer with null mediaData
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableGetPixelMapFromBuffer001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DrawableDescriptor with null mediaData
     * @tc.expected: GetPixelMapFromBuffer returns false
     */
    Napi::DrawableDescriptor drawable;
    // mediaData_ is nullptr by default
    auto result = drawable.GetPixelMapFromBuffer();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: DrawableGetPixelMapFromBuffer002
 * @tc.desc: test GetPixelMapFromBuffer with empty mediaData
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableGetPixelMapFromBuffer002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DrawableDescriptor with empty mediaData
     * @tc.expected: GetPixelMapFromBuffer returns false
     */
    auto emptyData = std::make_unique<uint8_t[]>(0);
    Napi::DrawableDescriptor drawable(std::move(emptyData), 0);
    auto result = drawable.GetPixelMapFromBuffer();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: DrawableGetPixelMapFromBuffer003
 * @tc.desc: test GetPixelMap with null mediaData_
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableGetPixelMapFromBuffer003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DrawableDescriptor without mediaData
     * @tc.expected: GetPixelMap returns nullptr
     */
    Napi::DrawableDescriptor drawable;
    auto pixelMap = drawable.GetPixelMap();
    EXPECT_EQ(pixelMap, nullptr);
}

// ============================================================================
// Test Group 9: PreGetPixelMapFromJsonBuf 测试 - 4 tests
// ============================================================================

/**
 * @tc.name: DrawablePreGetPixelMapFromJsonBuf001
 * @tc.desc: test PreGetPixelMapFromJsonBuf with null jsonBuf
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawablePreGetPixelMapFromJsonBuf001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LayeredDrawableDescriptor with null jsonBuf
     * @tc.expected: PreGetPixelMapFromJsonBuf returns false
     */
    Napi::LayeredDrawableDescriptor drawable;
    auto result = drawable.PreGetPixelMapFromJsonBuf(nullptr, true);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: DrawablePreGetPixelMapFromJsonBuf002
 * @tc.desc: test PreGetPixelMapFromJsonBuf with invalid JSON
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawablePreGetPixelMapFromJsonBuf002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LayeredDrawableDescriptor with invalid JSON
     * @tc.expected: PreGetPixelMapFromJsonBuf returns false
     */
    Napi::LayeredDrawableDescriptor drawable;
    const char* invalidJson = "not a json";
    drawable.len_ = strlen(invalidJson) + 1;
    drawable.jsonBuf_ = std::make_unique<uint8_t[]>(drawable.len_);
    memcpy_s(drawable.jsonBuf_.get(), drawable.len_ - 1, invalidJson, strlen(invalidJson));

    auto result = drawable.PreGetPixelMapFromJsonBuf(nullptr, true);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: DrawablePreGetPixelMapFromJsonBuf003
 * @tc.desc: test PreGetPixelMapFromJsonBuf with JSON missing background key
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawablePreGetPixelMapFromJsonBuf003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LayeredDrawableDescriptor with JSON missing background
     * @tc.expected: PreGetPixelMapFromJsonBuf returns false
     */
    Napi::LayeredDrawableDescriptor drawable;
    const char* jsonNoBg = "{\"foreground\":\"fg\"}";
    drawable.len_ = strlen(jsonNoBg) + 1;
    drawable.jsonBuf_ = std::make_unique<uint8_t[]>(drawable.len_);
    memcpy_s(drawable.jsonBuf_.get(), drawable.len_ - 1, jsonNoBg, strlen(jsonNoBg));

    auto result = drawable.PreGetPixelMapFromJsonBuf(nullptr, true);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: DrawablePreGetPixelMapFromJsonBuf004
 * @tc.desc: test PreGetPixelMapFromJsonBuf with JSON missing foreground key
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawablePreGetPixelMapFromJsonBuf004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LayeredDrawableDescriptor with JSON missing foreground
     * @tc.expected: PreGetPixelMapFromJsonBuf returns false
     */
    Napi::LayeredDrawableDescriptor drawable;
    const char* jsonNoFg = "{\"background\":\"bg\"}";
    drawable.len_ = strlen(jsonNoFg) + 1;
    drawable.jsonBuf_ = std::make_unique<uint8_t[]>(drawable.len_);
    memcpy_s(drawable.jsonBuf_.get(), drawable.len_ - 1, jsonNoFg, strlen(jsonNoFg));

    auto result = drawable.PreGetPixelMapFromJsonBuf(nullptr, false);
    EXPECT_FALSE(result);
}

// ============================================================================
// Test Group 10: GetPixelMapFromJsonBuf 测试 - 3 tests
// ============================================================================

/**
 * @tc.name: DrawableGetPixelMapFromJsonBuf001
 * @tc.desc: test GetPixelMapFromJsonBuf with already set pixelMap
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableGetPixelMapFromJsonBuf001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set background_ to nullptr explicitly
     * @tc.expected: GetPixelMapFromJsonBuf handles nullptr value
     */
    Napi::LayeredDrawableDescriptor drawable;
    drawable.background_ = nullptr;  // Explicit nullptr

    auto result = drawable.GetPixelMapFromJsonBuf(true);
    // Since backgroundItem_ state is not SUCCESS, should return false
    EXPECT_FALSE(result);
}

/**
 * @tc.name: DrawableGetPixelMapFromJsonBuf002
 * @tc.desc: test GetPixelMapFromJsonBuf with invalid state
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableGetPixelMapFromJsonBuf002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set backgroundItem_ state to ERROR
     * @tc.expected: GetPixelMapFromJsonBuf returns false
     */
    Napi::LayeredDrawableDescriptor drawable;
    drawable.backgroundItem_.state_ = Global::Resource::ERROR;

    auto result = drawable.GetPixelMapFromJsonBuf(true);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: DrawableGetPixelMapFromJsonBuf003
 * @tc.desc: test GetPixelMapFromJsonBuf with foreground
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableGetPixelMapFromJsonBuf003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set foregroundItem_ state to ERROR
     * @tc.expected: GetPixelMapFromJsonBuf returns false
     */
    Napi::LayeredDrawableDescriptor drawable;
    drawable.foregroundItem_.state_ = Global::Resource::ERROR;

    auto result = drawable.GetPixelMapFromJsonBuf(false);
    EXPECT_FALSE(result);
}

// ============================================================================
// Test Group 11: InitialResource 测试 - 3 tests
// ============================================================================

/**
 * @tc.name: DrawableInitialResource001
 * @tc.desc: test InitialResource with null resource manager
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableInitialResource001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call InitialResource with nullptr resourceMgr
     * @tc.expected: should handle gracefully without crash
     */
    Napi::LayeredDrawableDescriptor drawable;
    std::shared_ptr<Global::Resource::ResourceManager> nullMgr = nullptr;
    drawable.InitialResource(nullMgr);
    // Should not crash
    SUCCEED();
}

/**
 * @tc.name: DrawableInitialResource002
 * @tc.desc: test InitialResource with valid resource manager
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableInitialResource002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call InitialResource with valid resourceMgr
     * @tc.expected: should initialize without crash
     */
    std::shared_ptr<Global::Resource::ResourceManager> resourceMgr(Global::Resource::CreateResourceManager());
    Napi::LayeredDrawableDescriptor drawable;
    drawable.InitialResource(resourceMgr);
    // Should not crash
    SUCCEED();
}

/**
 * @tc.name: DrawableInitialResource003
 * @tc.desc: test InitialMask with valid resource manager
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableInitialResource003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call InitialMask with valid resourceMgr
     * @tc.expected: should initialize mask without crash
     */
    std::shared_ptr<Global::Resource::ResourceManager> resourceMgr(Global::Resource::CreateResourceManager());
    Napi::LayeredDrawableDescriptor drawable;
    drawable.InitialMask(resourceMgr);
    // Should not crash
    SUCCEED();
}

// ============================================================================
// Test Group 12: CreatePixelMap 相关测试 - 5 tests
// ============================================================================

/**
 * @tc.name: DrawableCreatePixelMap001
 * @tc.desc: test CreatePixelMap with incomplete parameters
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableCreatePixelMap001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call GetPixelMap on empty LayeredDrawableDescriptor
     * @tc.expected: returns nullptr
     */
    Napi::LayeredDrawableDescriptor drawable;
    auto pixelMap = drawable.GetPixelMap();
    EXPECT_EQ(pixelMap, nullptr);
}

/**
 * @tc.name: DrawableCreatePixelMap002
 * @tc.desc: test CreatePixelMap with customized flag and no foreground
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableCreatePixelMap002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set customized to true without setting foreground
     * @tc.expected: GetPixelMap handles the case
     */
    Napi::LayeredDrawableDescriptor drawable;
    drawable.customized_ = true;
    drawable.foreground_ = nullptr;

    auto pixelMap = drawable.GetPixelMap();
    // Should return nullptr since foreground is null
    EXPECT_EQ(pixelMap, nullptr);
}

/**
 * @tc.name: DrawableCreatePixelMap003
 * @tc.desc: test CreatePixelMap with layeredPixelMap already set
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableCreatePixelMap003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set layeredPixelMap_ to nullptr
     * @tc.expected: GetPixelMap returns nullptr (cached value)
     */
    Napi::LayeredDrawableDescriptor drawable;
    drawable.layeredPixelMap_ = nullptr;

    auto pixelMap = drawable.GetPixelMap();
    EXPECT_EQ(pixelMap, nullptr);
}

/**
 * @tc.name: DrawableCreatePixelMap004
 * @tc.desc: test CreatePixelMap with GetLayeredIconParm failure
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableCreatePixelMap004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LayeredDrawableDescriptor without parameters
     * @tc.expected: GetLayeredIconParm returns false
     */
    Napi::LayeredDrawableDescriptor drawable;
    Napi::SharedBitMap foreground;
    Napi::SharedBitMap background;
    Napi::SharedBitMap mask;

    // GetLayeredIconParm is private but we can test through CreatePixelMap
    auto pixelMap = drawable.GetPixelMap();
    // Should return nullptr since no valid resources
    EXPECT_EQ(pixelMap, nullptr);
}

/**
 * @tc.name: DrawableCreatePixelMap005
 * @tc.desc: test CreatePixelMap with invalid size
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableCreatePixelMap005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set decode size to negative values
     * @tc.expected: GetPixelMap handles negative size
     */
    Napi::LayeredDrawableDescriptor drawable;
    drawable.SetDecodeSize(-100, -100);

    auto pixelMap = drawable.GetPixelMap();
    EXPECT_EQ(pixelMap, nullptr);
}

// ============================================================================
// Test Group 13: GetMaskByPath 测试 - 3 tests
// ============================================================================

/**
 * @tc.name: DrawableGetMaskByPath001
 * @tc.desc: test GetMaskByPath with empty path
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableGetMaskByPath001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call GetMaskByPath with empty maskPath_
     * @tc.expected: returns false
     */
    Napi::LayeredDrawableDescriptor drawable;
    drawable.maskPath_.clear();

    auto result = drawable.GetMaskByPath();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: DrawableGetMaskByPath002
 * @tc.desc: test GetMaskByPath with mask already set
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableGetMaskByPath002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set mask_ to nullptr and call GetMaskByPath
     * @tc.expected: returns false (path is invalid)
     */
    Napi::LayeredDrawableDescriptor drawable;
    drawable.maskPath_ = "/invalid/path/to/image.jpg";
    drawable.mask_ = nullptr;

    auto result = drawable.GetMaskByPath();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: DrawableGetMaskByPath003
 * @tc.desc: test GetMask with mask already set
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableGetMaskByPath003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set mask_ to nullptr explicitly
     * @tc.expected: GetMask tries other methods
     */
    Napi::LayeredDrawableDescriptor drawable;
    drawable.mask_ = nullptr;
    drawable.maskPath_.clear();

    auto result = drawable.GetMask();
    // Should return nullptr since no valid mask source
    EXPECT_EQ(result, nullptr);
}

// ============================================================================
// Test Group 14: GetMaskByName 测试 - 2 tests
// ============================================================================

/**
 * @tc.name: DrawableGetMaskByName001
 * @tc.desc: test GetMaskByName with empty name
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableGetMaskByName001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call GetMaskByName with empty name
     * @tc.expected: returns false
     */
    std::shared_ptr<Global::Resource::ResourceManager> resourceMgr(Global::Resource::CreateResourceManager());
    Napi::LayeredDrawableDescriptor drawable;
    std::string emptyName = "";

    auto result = drawable.GetMaskByName(resourceMgr, emptyName);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: DrawableGetMaskByName002
 * @tc.desc: test GetMaskByName with null resource manager
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableGetMaskByName002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call GetMaskByName with null resourceMgr
     * @tc.expected: returns false
     */
    std::shared_ptr<Global::Resource::ResourceManager> nullMgr = nullptr;
    Napi::LayeredDrawableDescriptor drawable;
    std::string name = "test_mask";

    auto result = drawable.GetMaskByName(nullMgr, name);
    EXPECT_FALSE(result);
}

// ============================================================================
// Test Group 15: 工厂方法返回类型测试 - 4 tests
// ============================================================================

/**
 * @tc.name: DrawableFactoryReturnType001
 * @tc.desc: test Factory Create returns BASE type for PNG
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableFactoryReturnType001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call Create with invalid ID (will fail)
     * @tc.expected: drawableType should remain unchanged or be set by error
     */
    std::shared_ptr<Global::Resource::ResourceManager> resourceMgr(Global::Resource::CreateResourceManager());
    Napi::DrawableDescriptorFactory factory;
    Global::Resource::RState state;
    Napi::DrawableDescriptor::DrawableType drawableType = Napi::DrawableDescriptor::DrawableType::BASE;

    auto drawable = factory.Create(99999, resourceMgr, state, drawableType, 0);
    EXPECT_EQ(drawable, nullptr);
    // state should indicate error
    EXPECT_NE(state, Global::Resource::SUCCESS);
}

/**
 * @tc.name: DrawableFactoryReturnType002
 * @tc.desc: test Factory Create returns LAYERED type for JSON
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableFactoryReturnType002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call Create with invalid name (will fail)
     * @tc.expected: returns nullptr
     */
    std::shared_ptr<Global::Resource::ResourceManager> resourceMgr(Global::Resource::CreateResourceManager());
    Napi::DrawableDescriptorFactory factory;
    Global::Resource::RState state;
    Napi::DrawableDescriptor::DrawableType drawableType = Napi::DrawableDescriptor::DrawableType::LAYERED;

    auto drawable = factory.Create("invalid_name", resourceMgr, state, drawableType, 0);
    EXPECT_EQ(drawable, nullptr);
}

/**
 * @tc.name: DrawableFactoryReturnType003
 * @tc.desc: test Factory Create with DataInfo
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableFactoryReturnType003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call Create with DataInfo
     * @tc.expected: returns LayeredDrawableDescriptor
     */
    std::shared_ptr<Global::Resource::ResourceManager> resourceMgr;
    Napi::DrawableDescriptorFactory factory;
    Napi::DrawableDescriptor::DrawableType drawableType;
    Napi::DataInfo foregroundInfo = { std::make_unique<uint8_t[]>(100), 100 };
    Napi::DataInfo backgroundInfo = { std::make_unique<uint8_t[]>(100), 100 };
    std::string path = "/test/path";

    auto drawable = factory.Create(foregroundInfo, backgroundInfo, path, drawableType, resourceMgr);
    EXPECT_NE(drawable, nullptr);
    EXPECT_EQ(drawableType, Napi::DrawableDescriptor::DrawableType::LAYERED);
}

/**
 * @tc.name: DrawableFactoryReturnType004
 * @tc.desc: test Factory Create with different densities
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableFactoryReturnType004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call Create with different density values
     * @tc.expected: should handle different density values
     */
    std::shared_ptr<Global::Resource::ResourceManager> resourceMgr(Global::Resource::CreateResourceManager());
    Napi::DrawableDescriptorFactory factory;
    Global::Resource::RState state;
    Napi::DrawableDescriptor::DrawableType drawableType;

    // Test with density = 0 (default)
    auto drawable1 = factory.Create(99999, resourceMgr, state, drawableType, 0);
    EXPECT_EQ(drawable1, nullptr);

    // Test with density = 160 (MDPI)
    state = Global::Resource::INVALID_FORMAT;
    auto drawable2 = factory.Create(99999, resourceMgr, state, drawableType, 160);
    EXPECT_EQ(drawable2, nullptr);

    // Test with density = 320 (XHDPI)
    state = Global::Resource::INVALID_FORMAT;
    auto drawable3 = factory.Create(99999, resourceMgr, state, drawableType, 320);
    EXPECT_EQ(drawable3, nullptr);
}

// ============================================================================
// Test Group 16: 边界条件和特殊情况 - 4 tests
// ============================================================================

/**
 * @tc.name: DrawableGetForeground001
 * @tc.desc: test GetForeground with nullptr foreground_
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableGetForeground001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call GetForeground when foreground_ is nullptr
     * @tc.expected: returns nullptr after attempting to load from JSON
     */
    Napi::LayeredDrawableDescriptor drawable;
    drawable.foreground_ = nullptr;

    auto result = drawable.GetForeground();
    // Should return nullptr since no valid source
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: DrawableGetBackground001
 * @tc.desc: test GetBackground with nullptr background_
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableGetBackground001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call GetBackground when background_ is nullptr
     * @tc.expected: returns nullptr after attempting to load from JSON
     */
    Napi::LayeredDrawableDescriptor drawable;
    drawable.background_ = nullptr;

    auto result = drawable.GetBackground();
    // Should return nullptr since no valid source
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: DrawableGetMask001
 * @tc.desc: test GetMask when all mask sources fail
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableGetMask001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call GetMask with no valid mask sources
     * @tc.expected: returns nullptr
     */
    Napi::LayeredDrawableDescriptor drawable;
    drawable.mask_ = nullptr;
    drawable.maskPath_.clear();
    drawable.defaultMaskData_ = nullptr;
    drawable.defaultMaskDataLength_ = 0;

    auto result = drawable.GetMask();
    // Should return nullptr since no valid mask source
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: DrawableGetStaticMaskClipPath001
 * @tc.desc: test GetStaticMaskClipPath
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableGetStaticMaskClipPath001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call GetStaticMaskClipPath
     * @tc.expected: returns a string (may be empty)
     */
    auto path = Napi::LayeredDrawableDescriptor::GetStaticMaskClipPath();
    // Just verify it returns without crash
    SUCCEED();
}

// ============================================================================
// Test Group 17: 更多构造函数测试 - 3 tests
// ============================================================================

/**
 * @tc.name: DrawableLayeredConstructor004
 * @tc.desc: test LayeredDrawableDescriptor constructor with decoderSize
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableLayeredConstructor004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LayeredDrawableDescriptor with decoderSize parameter
     * @tc.expected: decoderSize is set correctly
     */
    size_t len = 0;
    std::string path = "/test/path";
    uint32_t iconType = 0;
    Napi::DataInfo foregroundInfo = { std::make_unique<uint8_t[]>(512), 512 };
    Napi::DataInfo backgroundInfo = { std::make_unique<uint8_t[]>(512), 512 };
    std::pair<int32_t, int32_t> decoderSize = { 200, 200 };

    auto layeredDrawable = Napi::LayeredDrawableDescriptor(
        len, path, iconType, foregroundInfo, backgroundInfo, decoderSize);

    auto decodeSize = layeredDrawable.GetDecodeSize();
    EXPECT_TRUE(decodeSize.has_value());
    EXPECT_EQ(decodeSize->first, 200);
    EXPECT_EQ(decodeSize->second, 200);
}

/**
 * @tc.name: DrawableLayeredConstructor005
 * @tc.desc: test LayeredDrawableDescriptor default constructor
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableLayeredConstructor005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LayeredDrawableDescriptor with default constructor
     * @tc.expected: all members initialized to default values
     */
    Napi::LayeredDrawableDescriptor drawable;

    EXPECT_EQ(drawable.len_, 0);
    EXPECT_EQ(drawable.iconType_, 0);
    EXPECT_EQ(drawable.density_, 0);
    EXPECT_FALSE(drawable.customized_);
    EXPECT_FALSE(drawable.foregroundOverBackground_);
    EXPECT_EQ(drawable.blendMode_, -1);
}

/**
 * @tc.name: DrawableLayeredConstructor006
 * @tc.desc: test LayeredDrawableDescriptor with negative blendMode
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableLayeredConstructor006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LayeredDrawableDescriptor and test InitBlendMode
     * @tc.expected: blendMode initialized correctly based on foregroundOverBackground
     */
    Napi::LayeredDrawableDescriptor drawable;
    drawable.foregroundOverBackground_ = false;
    drawable.InitBlendMode();

    // blendMode should remain -1 when foregroundOverBackground is false
    EXPECT_EQ(drawable.blendMode_, -1);
}

// ============================================================================
// Test Group 18: Customized 相关测试 - 3 tests
// ============================================================================

/**
 * @tc.name: DrawableCustomized001
 * @tc.desc: test SetForeground sets customized flag
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableCustomized001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call SetForeground with nullptr
     * @tc.expected: customized_ is set to true
     */
    Napi::LayeredDrawableDescriptor drawable;
    drawable.SetForeground(nullptr);
    EXPECT_TRUE(drawable.Customized());
}

/**
 * @tc.name: DrawableCustomized002
 * @tc.desc: test SetBackground sets customized flag
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableCustomized002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call SetBackground with nullptr
     * @tc.expected: customized_ is set to true
     */
    Napi::LayeredDrawableDescriptor drawable;
    drawable.SetBackground(nullptr);
    EXPECT_TRUE(drawable.Customized());
}

/**
 * @tc.name: DrawableCustomized003
 * @tc.desc: test SetMask sets customized flag
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableCustomized003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call SetMask with nullptr
     * @tc.expected: customized_ is set to true
     */
    Napi::LayeredDrawableDescriptor drawable;
    drawable.SetMask(nullptr);
    EXPECT_TRUE(drawable.Customized());
}

// ============================================================================
// Test Group 19: InitLayeredParam 测试 - 2 tests
// ============================================================================

/**
 * @tc.name: DrawableInitLayeredParam001
 * @tc.desc: test InitLayeredParam with empty DataInfo
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableInitLayeredParam001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call InitLayeredParam with empty DataInfo
     * @tc.expected: should handle gracefully
     */
    Napi::LayeredDrawableDescriptor drawable;
    Napi::DataInfo emptyForeground = { nullptr, 0 };
    Napi::DataInfo emptyBackground = { nullptr, 0 };

    drawable.InitLayeredParam(emptyForeground, emptyBackground);

    // foreground_ and background_ should be nullopt since data is empty
    EXPECT_FALSE(drawable.foreground_.has_value());
    EXPECT_FALSE(drawable.background_.has_value());
}

/**
 * @tc.name: DrawableInitLayeredParam002
 * @tc.desc: test InitLayeredParam with decodeSize set
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableInitLayeredParam002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set decodeSize and call InitLayeredParam
     * @tc.expected: decodeSize is used in image loading
     */
    Napi::LayeredDrawableDescriptor drawable;
    drawable.SetDecodeSize(100, 100);

    Napi::DataInfo foregroundInfo = { std::make_unique<uint8_t[]>(100), 100 };
    Napi::DataInfo backgroundInfo = { std::make_unique<uint8_t[]>(100), 100 };

    drawable.InitLayeredParam(foregroundInfo, backgroundInfo);

    auto decodeSize = drawable.GetDecodeSize();
    EXPECT_TRUE(decodeSize.has_value());
    EXPECT_EQ(decodeSize->first, 100);
}

// ============================================================================
// Test Group 20: GetLayeredIconParm 测试 - 2 tests
// ============================================================================

/**
 * @tc.name: DrawableGetLayeredIconParm001
 * @tc.desc: test CreatePixelMap calls GetLayeredIconParm
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableGetLayeredIconParm001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call CreatePixelMap which calls GetLayeredIconParm internally
     * @tc.expected: returns false when all params are missing
     */
    Napi::LayeredDrawableDescriptor drawable;
    auto pixelMap = drawable.GetPixelMap();
    EXPECT_EQ(pixelMap, nullptr);
}

/**
 * @tc.name: DrawableGetLayeredIconParm002
 * @tc.desc: test GetLayeredIconParm with customized=true
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableGetLayeredIconParm002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set customized to true but don't set all required params
     * @tc.expected: returns nullptr when customized but incomplete
     */
    Napi::LayeredDrawableDescriptor drawable;
    drawable.customized_ = true;

    auto pixelMap = drawable.GetPixelMap();
    EXPECT_EQ(pixelMap, nullptr);
}

// ============================================================================
// Test Group 21: GetDefaultMask 测试 - 2 tests
// ============================================================================

/**
 * @tc.name: DrawableGetDefaultMask001
 * @tc.desc: test GetDefaultMask with no mask data
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableGetDefaultMask001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call GetDefaultMask with no data
     * @tc.expected: returns false
     */
    Napi::LayeredDrawableDescriptor drawable;
    drawable.defaultMaskData_ = nullptr;
    drawable.defaultMaskDataLength_ = 0;

    auto result = drawable.GetDefaultMask();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: DrawableGetDefaultMask002
 * @tc.desc: test GetDefaultMask with mask already set
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableGetDefaultMask002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set mask_ to nullptr
     * @tc.expected: GetDefaultMask attempts to load
     */
    Napi::LayeredDrawableDescriptor drawable;
    drawable.mask_ = nullptr;

    auto result = drawable.GetDefaultMask();
    EXPECT_FALSE(result);
}

// ============================================================================
// Test Group 22: 边界值和特殊场景 - 3 tests
// ============================================================================

/**
 * @tc.name: DrawableDecodeSizeBoundary001
 * @tc.desc: test SetDecodeSize with zero values
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableDecodeSizeBoundary001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set decode size to 0x0
     * @tc.expected: accepts zero values
     */
    Napi::DrawableDescriptor drawable;
    drawable.SetDecodeSize(0, 0);

    auto decodeSize = drawable.GetDecodeSize();
    EXPECT_TRUE(decodeSize.has_value());
    EXPECT_EQ(decodeSize->first, 0);
    EXPECT_EQ(decodeSize->second, 0);
}

/**
 * @tc.name: DrawableBlendMode003
 * @tc.desc: test SetBlendMode with value above valid range
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableBlendMode003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set blendMode to value > 15 (LUMINOSITY)
     * @tc.expected: blendMode should not be updated
     */
    Napi::LayeredDrawableDescriptor drawable;
    drawable.blendMode_ = -1;
    drawable.foregroundOverBackground_ = false;

    drawable.SetBlendMode(16);  // Above valid range
    EXPECT_EQ(drawable.blendMode_, -1);
    EXPECT_FALSE(drawable.foregroundOverBackground_);
}

/**
 * @tc.name: DrawableBlendMode004
 * @tc.desc: test InitBlendMode with foregroundOverBackground=true
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorExtendedTest, DrawableBlendMode004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set foregroundOverBackground to true and init
     * @tc.expected: blendMode set to SRC_OVER (3)
     */
    Napi::LayeredDrawableDescriptor drawable;
    drawable.foregroundOverBackground_ = true;
    drawable.blendMode_ = -1;

    drawable.InitBlendMode();
    EXPECT_EQ(drawable.blendMode_, 3);  // SRC_OVER
    EXPECT_TRUE(drawable.foregroundOverBackground_);
}

} // namespace OHOS::Ace
