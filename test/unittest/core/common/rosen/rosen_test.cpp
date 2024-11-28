/*
 * Copyright (c) 2023 iSoftStone Information Technology (Group) Co.,Ltd.
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
#include "gtest/gtest.h"
#define private public
#define protected public
#include "core/common/rosen/rosen_asset_manager.h"
#include "core/common/rosen/rosen_convert_helper.h"
#include "core/common/rosen/rosen_enums.h"
#include "core/common/rosen/rosen_window.h"
#undef private
#undef protected
#include "mock_rosen.h"
#include "test/mock/core/common/mock_container.h"

#include "adapter/ohos/entrance/file_asset_provider_impl.h"
#include "core/pipeline/base/render_node.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
const std::string RET_TEST = "error";
const std::string HAPPATTH = "/system/app/com.ohos.photos/Photos.hap";
const std::string ASSETBASEPATHS = "/resources/base/profile/";
uint64_t nanoTimestamp_ = 0;
uint32_t frameCount_ = 0;
AceVsyncCallback callback_;
} // namespace

class RosenTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
    void SetUp() {}
    void TearDown() {}
};

/**
 * @tc.name: CastToRosenTest001
 * @tc.desc: Test cast to rosen.
 * @tc.type: FUNC
 */
HWTEST_F(RosenTest, CastToRosenTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object RSWindow.
     */
    Platform::RSWindow object;

    /**
     * @tc.steps: step2. callback Create.
     * @tc.expected: step2. Return expected results..
     */
    auto result1 = PlatformWindow::Create(nullptr);
    EXPECT_EQ(result1, nullptr);

    /**
     * @tc.steps: step3. callback SetRootRenderNode.
     * @tc.expected: step3. SetRootRenderNode success.
     */
    object.SetRootRenderNode(nullptr);
}

/**
 * @tc.name: CastToRosenTest002
 * @tc.desc: Test cast to rosen.
 * @tc.type: FUNC
 */
HWTEST_F(RosenTest, CastToRosenTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object RSWindow.
     */
    Platform::RSWindow object;

    /**
     * @tc.steps: step2. callback RegisterVsyncCallback.
     * @tc.expected: step2. Return expected results.
     */
    auto callback = [](uint64_t deltaNanoTimestamp, uint32_t deltaFrameCount) {
        nanoTimestamp_ += deltaNanoTimestamp;
        frameCount_ += deltaFrameCount;
        if (callback_) {
            callback_(nanoTimestamp_, frameCount_);
        }
    };
    object.RegisterVsyncCallback(callback);
    EXPECT_EQ(nanoTimestamp_, 0);
}

/**
 * @tc.name: CastToRosenTest005
 * @tc.desc: Test cast to rosen.
 * @tc.type: FUNC
 */
HWTEST_F(RosenTest, CastToRosenTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback GetRosenBlurStyleValue.The blurStyleOption parameter is the default value.
     * @tc.expected: step1. Return expected results.
     */
    auto result = GetRosenBlurStyleValue(BlurStyleOption());
    EXPECT_EQ(result, MATERIAL_BLUR_STYLE::NO_MATERIAL);

    /**
     * @tc.steps: step2. callback GetRosenBlurStyleValue.The blurStyleOption parameter is new value.
     * @tc.expected: step2. Return expected results.
     */
    BlurStyleOption blurStyleOption;
    blurStyleOption.blurStyle = BlurStyle::THIN;
    blurStyleOption.colorMode = ThemeColorMode::DARK;
    auto retDark = GetRosenBlurStyleValue(blurStyleOption);
    EXPECT_EQ(retDark, MATERIAL_BLUR_STYLE::STYLE_CARD_THIN_DARK);

    /**
     * @tc.steps: step3. callback GetRosenBlurStyleValue.The blurStyleOption parameter is new value.
     * @tc.expected: step3. Return expected results.
     */
    blurStyleOption.blurStyle = BlurStyle::REGULAR;
    blurStyleOption.colorMode = ThemeColorMode::DARK;
    auto retDark1 = GetRosenBlurStyleValue(blurStyleOption);
    EXPECT_EQ(retDark1, MATERIAL_BLUR_STYLE::STYLE_CARD_DARK);

    /**
     * @tc.steps: step4. callback GetRosenBlurStyleValue.The blurStyleOption parameter is new value.
     * @tc.expected: step4. Return expected results.
     */
    blurStyleOption.blurStyle = BlurStyle::THICK;
    blurStyleOption.colorMode = ThemeColorMode::DARK;
    auto retDark2 = GetRosenBlurStyleValue(blurStyleOption);
    EXPECT_EQ(retDark2, MATERIAL_BLUR_STYLE::STYLE_CARD_THICK_DARK);

    /**
     * @tc.steps: step5. callback GetRosenBlurStyleValue.The blurStyleOption parameter is new value.
     * @tc.expected: step5. Return expected results.
     */
    blurStyleOption.blurStyle = BlurStyle::BACKGROUND_THIN;
    blurStyleOption.colorMode = ThemeColorMode::DARK;
    auto retDark3 = GetRosenBlurStyleValue(blurStyleOption);
    EXPECT_EQ(retDark3, MATERIAL_BLUR_STYLE::STYLE_BACKGROUND_SMALL_DARK);

    /**
     * @tc.steps: step6. callback GetRosenBlurStyleValue.The blurStyleOption parameter is new value.
     * @tc.expected: step6. Return expected results.
     */
    blurStyleOption.blurStyle = BlurStyle::BACKGROUND_REGULAR;
    blurStyleOption.colorMode = ThemeColorMode::DARK;
    auto retDark4 = GetRosenBlurStyleValue(blurStyleOption);
    EXPECT_EQ(retDark4, MATERIAL_BLUR_STYLE::STYLE_BACKGROUND_MEDIUM_DARK);

    /**
     * @tc.steps: step7. callback GetRosenBlurStyleValue.The blurStyleOption parameter is new value.
     * @tc.expected: step7. Return expected results.
     */
    blurStyleOption.blurStyle = BlurStyle::BACKGROUND_THICK;
    blurStyleOption.colorMode = ThemeColorMode::DARK;
    auto retDark5 = GetRosenBlurStyleValue(blurStyleOption);
    EXPECT_EQ(retDark5, MATERIAL_BLUR_STYLE::STYLE_BACKGROUND_LARGE_DARK);

    /**
     * @tc.steps: step8. callback GetRosenBlurStyleValue.The blurStyleOption parameter is new value.
     * @tc.expected: step8. Return expected results.
     */
    blurStyleOption.blurStyle = BlurStyle::BACKGROUND_ULTRA_THICK;
    blurStyleOption.colorMode = ThemeColorMode::DARK;
    auto retDark6 = GetRosenBlurStyleValue(blurStyleOption);
    EXPECT_EQ(retDark6, MATERIAL_BLUR_STYLE::STYLE_BACKGROUND_XLARGE_DARK);
}

/**
 * @tc.name: CastToRosenTest006
 * @tc.desc: Test cast to rosen.
 * @tc.type: FUNC
 */
HWTEST_F(RosenTest, CastToRosenTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback GetRosenBlurStyleValue.The blurStyleOption parameter is new value.
     * @tc.expected: step1. Return expected results.
     */
    BlurStyleOption blurStyleOption;
    blurStyleOption.blurStyle = BlurStyle::NO_MATERIAL;
    blurStyleOption.colorMode = ThemeColorMode::LIGHT;
    auto retLight = GetRosenBlurStyleValue(blurStyleOption);
    EXPECT_EQ(retLight, MATERIAL_BLUR_STYLE::NO_MATERIAL);

    /**
     * @tc.steps: step2. callback GetRosenBlurStyleValue.The blurStyleOption parameter is new value.
     * @tc.expected: step2. Return expected results.
     */
    blurStyleOption.blurStyle = BlurStyle::THIN;
    blurStyleOption.colorMode = ThemeColorMode::LIGHT;
    auto retLight1 = GetRosenBlurStyleValue(blurStyleOption);
    EXPECT_EQ(retLight1, MATERIAL_BLUR_STYLE::STYLE_CARD_THIN_LIGHT);

    /**
     * @tc.steps: step3. callback GetRosenBlurStyleValue.The blurStyleOption parameter is new value.
     * @tc.expected: step3. Return expected results.
     */
    blurStyleOption.blurStyle = BlurStyle::REGULAR;
    blurStyleOption.colorMode = ThemeColorMode::LIGHT;
    auto retLight2 = GetRosenBlurStyleValue(blurStyleOption);
    EXPECT_EQ(retLight2, MATERIAL_BLUR_STYLE::STYLE_CARD_LIGHT);

    /**
     * @tc.steps: step4. callback GetRosenBlurStyleValue.The blurStyleOption parameter is new value.
     * @tc.expected: step4. Return expected results.
     */
    blurStyleOption.blurStyle = BlurStyle::THICK;
    blurStyleOption.colorMode = ThemeColorMode::LIGHT;
    auto retLight3 = GetRosenBlurStyleValue(blurStyleOption);
    EXPECT_EQ(retLight3, MATERIAL_BLUR_STYLE::STYLE_CARD_THICK_LIGHT);

    /**
     * @tc.steps: step5. callback GetRosenBlurStyleValue.The blurStyleOption parameter is new value.
     * @tc.expected: step5. Return expected results.
     */
    blurStyleOption.blurStyle = BlurStyle::BACKGROUND_ULTRA_THICK;
    blurStyleOption.colorMode = ThemeColorMode::LIGHT;
    auto retLight4 = GetRosenBlurStyleValue(blurStyleOption);
    EXPECT_EQ(retLight4, MATERIAL_BLUR_STYLE::STYLE_BACKGROUND_XLARGE_LIGHT);
}

/**
 * @tc.name: CastToRosenTest007
 * @tc.desc: Test cast to rosen.
 * @tc.type: FUNC
 */
HWTEST_F(RosenTest, CastToRosenTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object.
     * @tc.steps: step2. callback GetAssetPath input provider is null.
     * @tc.expected: step2. Return expected results.
     */
    RSAssetManager object;
    auto assetProvider = AceType::MakeRefPtr<Ace::FileAssetProviderImpl>();
    std::string hapPath = "/system/app/com.ohos.photos/Photos.hap";
    std::vector<std::string> assetBasePaths;
    assetBasePaths.push_back("resources/base/profile/");
    assetProvider->Initialize(hapPath, assetBasePaths);
    object.PushBack(std::move(assetProvider));
    std::string assetName = RET_TEST;
    std::string result = object.GetAssetPath(assetName, true);
    EXPECT_EQ(result, "");
}

/**
 * @tc.name: CastToRosenTest008
 * @tc.desc: Test cast to rosen.
 * @tc.type: FUNC
 */
HWTEST_F(RosenTest, CastToRosenTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object.
     * @tc.steps: step2. callback GetAssetPath input provider is null.
     * @tc.expected: step2. Return expected results..
     */
    RSAssetManager object;
    std::string assetName = RET_TEST;
    std::string ret = object.GetAssetPath(assetName, true);
    EXPECT_EQ(ret, "");

    /**
     * @tc.steps: step3. callback GetAssetPath input provider is not null.
     * @tc.expected: step3. Return expected results.
     */
    std::string hapPath = "test";
    auto assetProvider = AceType::MakeRefPtr<MockAssetProvider>();
    EXPECT_CALL(*assetProvider, IsValid()).Times(1).WillOnce(Return(true));
    EXPECT_CALL(*assetProvider, GetAssetPath(hapPath, true)).Times(1).WillOnce(Return("test"));
    object.PushBack(std::move(assetProvider));
    std::string result = object.GetAssetPath(hapPath, true);
    EXPECT_EQ(result, "test");
}

/**
 * @tc.name: CastToRosenTest009
 * @tc.desc: Test cast to rosen.
 * @tc.type: FUNC
 */
HWTEST_F(RosenTest, CastToRosenTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object.
     * @tc.steps: step2. callback GetAssetList input provider is not null.
     * @tc.expected: step2. Return expected results.
     */
    RSAssetManager object;
    std::string path = RET_TEST;
    std::vector<std::string> assetList;
    auto assetProvider = AceType::MakeRefPtr<MockAssetProvider>();
    EXPECT_CALL(*assetProvider, IsValid()).Times(1).WillOnce(Return(true));
    EXPECT_CALL(*assetProvider, GetAssetList(path, assetList)).WillOnce(Return());
    object.PushBack(std::move(assetProvider));
    object.GetAssetList(path, assetList);
    EXPECT_TRUE(assetList.empty());
}

/**
 * @tc.name: CastToRosenTest0010
 * @tc.desc: Test cast to rosen.
 * @tc.type: FUNC
 */
HWTEST_F(RosenTest, CastToRosenTest0010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object.
     * @tc.steps: step2. callback GetFileInfo input assetName is null.
     * @tc.expected: step2. Return results is false.
     */
    RSAssetManager object;
    std::string hapPath = "test";
    MediaFileInfo fileInfo = { .fileName = hapPath, .offset = 1, .length = 1, .lastModTime = 1, .lastModDate = 1 };
    auto assetProvider = AceType::MakeRefPtr<Ace::FileAssetProviderImpl>();
    std::vector<std::string> assetBasePaths;
    assetBasePaths.push_back("resources/base/profile/");
    assetProvider->Initialize(hapPath, assetBasePaths);
    assetProvider->GetFileInfo(hapPath, fileInfo);
    object.PushBack(std::move(assetProvider));
    bool result = object.GetFileInfo(hapPath, fileInfo);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CastToRosenTest0011
 * @tc.desc: Test cast to rosen.
 * @tc.type: FUNC
 */
HWTEST_F(RosenTest, CastToRosenTest0011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object.
     * @tc.steps: step2. callback GetAsset input assetName is null.
     * @tc.expected: step2. The expected result is null.
     */
    RSAssetManager object;
    auto result = object.GetAsset("");
    EXPECT_EQ(result, nullptr);

    /**
     * @tc.steps: step3. callback GetAsset input assetName is not null.
     * @tc.expected: step3. The expected result is null.
     */
    std::string assetName = RET_TEST;
    auto testAsset = object.GetAsset(assetName);
    EXPECT_EQ(testAsset, nullptr);
}

/**
 * @tc.name: CastToRosenTest0012
 * @tc.desc: Test cast to rosen.
 * @tc.type: FUNC
 */
HWTEST_F(RosenTest, CastToRosenTest0012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object.
     * @tc.steps: step2. callback GetAsset input provider is not null.
     * @tc.expected: step2. The expected result is null.
     */
    RSAssetManager object;
    std::string hapPath = "core/common/test/unittest/rosen/BUILD.gn";
    auto assetProvider = AceType::MakeRefPtr<MockAssetProvider>();
    EXPECT_CALL(*assetProvider, IsValid()).Times(1).WillOnce(Return(true));
    EXPECT_CALL(*assetProvider, GetAsset(hapPath)).Times(1).WillOnce(Return(nullptr));
    assetProvider->GetAsset(hapPath);
    object.PushBack(std::move(assetProvider));
    auto ret = object.GetAsset(hapPath);
    EXPECT_EQ(ret, nullptr);
}
} // namespace OHOS::Ace
