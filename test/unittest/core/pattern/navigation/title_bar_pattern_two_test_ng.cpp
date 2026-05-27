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

#include "gtest/gtest.h"
#include "mock_navigation_route.h"

#define protected public
#define private public

#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t TEST_LUMINANCE_LOW = 100;
constexpr uint32_t TEST_LUMINANCE_HIGH = 250;

RefPtr<TitleBarNode> CreateTitleBarNode()
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto node = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        nodeId, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    node->InitializePatternAndContext();
    return node;
}

RefPtr<FrameNode> CreateSymbolNode()
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto node = FrameNode::CreateFrameNode(V2::SYMBOL_ETS_TAG, nodeId, AceType::MakeRefPtr<Pattern>());
    node->InitializePatternAndContext();
    return node;
}

RefPtr<FrameNode> CreateImageNode(bool isSvg)
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto node = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, nodeId, AceType::MakeRefPtr<ImagePattern>());
    auto layoutProperty = node->GetLayoutProperty<ImageLayoutProperty>();
    if (layoutProperty) {
        ImageSourceInfo imageSourceInfo;
        if (isSvg) {
            imageSourceInfo.SetSrc("test.svg");
        } else {
            imageSourceInfo.SetSrc("test.png");
        }
        layoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    }
    node->InitializePatternAndContext();
    return node;
}
} // namespace

class TitleBarPatternTestTwoNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void TitleBarPatternTestTwoNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void TitleBarPatternTestTwoNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: IsSymbolOrSVGIcon001
 * @tc.desc: Test IsSymbolOrSVGIcon when iconNode is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, IsSymbolOrSVGIcon001, TestSize.Level1)
{
    bool result = TitleBarPattern::IsSymbolOrSVGIcon(nullptr);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsSymbolOrSVGIcon002
 * @tc.desc: Test IsSymbolOrSVGIcon when iconNode is Symbol node
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, IsSymbolOrSVGIcon002, TestSize.Level1)
{
    auto symbolNode = CreateSymbolNode();
    ASSERT_NE(symbolNode, nullptr);
    
    bool result = TitleBarPattern::IsSymbolOrSVGIcon(symbolNode);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: IsSymbolOrSVGIcon003
 * @tc.desc: Test IsSymbolOrSVGIcon when iconNode is Image node with SVG source
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, IsSymbolOrSVGIcon003, TestSize.Level1)
{
    auto imageNode = CreateImageNode(true);
    ASSERT_NE(imageNode, nullptr);
    
    bool result = TitleBarPattern::IsSymbolOrSVGIcon(imageNode);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: IsSymbolOrSVGIcon004
 * @tc.desc: Test IsSymbolOrSVGIcon when iconNode is Image node with PNG source
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, IsSymbolOrSVGIcon004, TestSize.Level1)
{
    auto imageNode = CreateImageNode(false);
    ASSERT_NE(imageNode, nullptr);
    
    bool result = TitleBarPattern::IsSymbolOrSVGIcon(imageNode);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: GetCurrentColorMode001
 * @tc.desc: Test GetCurrentColorMode when enableColorInvert is true and isColorPickerDark_ is true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, GetCurrentColorMode001, TestSize.Level1)
{
    auto titleBarNode = CreateTitleBarNode();
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    
    titleBarPattern->isColorPickerDark_ = true;
    
    ColorMode colorMode = titleBarPattern->GetCurrentColorMode(true);
    EXPECT_EQ(colorMode, ColorMode::DARK);
}

/**
 * @tc.name: GetCurrentColorMode002
 * @tc.desc: Test GetCurrentColorMode when enableColorInvert is true and isColorPickerDark_ is false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, GetCurrentColorMode002, TestSize.Level1)
{
    auto titleBarNode = CreateTitleBarNode();
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    
    titleBarPattern->isColorPickerDark_ = false;
    
    ColorMode colorMode = titleBarPattern->GetCurrentColorMode(true);
    EXPECT_EQ(colorMode, ColorMode::LIGHT);
}

/**
 * @tc.name: GetCurrentColorMode003
 * @tc.desc: Test GetCurrentColorMode when enableColorInvert is false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, GetCurrentColorMode003, TestSize.Level1)
{
    auto titleBarNode = CreateTitleBarNode();
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    
    titleBarPattern->isColorPickerDark_ = std::nullopt;
    titleBarPattern->isBackgroundDark_ = true;
    
    ColorMode colorMode = titleBarPattern->GetCurrentColorMode(false);
    EXPECT_NE(colorMode, ColorMode::COLOR_MODE_UNDEFINED);
}

/**
 * @tc.name: OnLuminanceUpdate001
 * @tc.desc: Test OnLuminanceUpdate when luminance is below threshold LOW
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, OnLuminanceUpdate001, TestSize.Level1)
{
    auto titleBarNode = CreateTitleBarNode();
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    
    titleBarPattern->isColorPickerDark_ = std::nullopt;
    
    titleBarPattern->OnLuminanceUpdate(TEST_LUMINANCE_LOW);
    EXPECT_TRUE(titleBarPattern->isColorPickerDark_.has_value());
    EXPECT_TRUE(titleBarPattern->isColorPickerDark_.value());
}

/**
 * @tc.name: OnLuminanceUpdate002
 * @tc.desc: Test OnLuminanceUpdate when luminance is above threshold HIGH
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, OnLuminanceUpdate002, TestSize.Level1)
{
    auto titleBarNode = CreateTitleBarNode();
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    
    titleBarPattern->isColorPickerDark_ = std::nullopt;
    
    titleBarPattern->OnLuminanceUpdate(TEST_LUMINANCE_HIGH);
    EXPECT_TRUE(titleBarPattern->isColorPickerDark_.has_value());
    EXPECT_FALSE(titleBarPattern->isColorPickerDark_.value());
}

/**
 * @tc.name: UnregisterColorPicker001
 * @tc.desc: Test UnregisterColorPicker when hasRegisterColorPicker_ is true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, UnregisterColorPicker001, TestSize.Level1)
{
    auto titleBarNode = CreateTitleBarNode();
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    
    titleBarPattern->hasRegisterColorPicker_ = true;
    titleBarPattern->isColorPickerDark_ = true;
    
    titleBarPattern->UnregisterColorPicker();
    EXPECT_FALSE(titleBarPattern->hasRegisterColorPicker_);
    EXPECT_FALSE(titleBarPattern->isColorPickerDark_.has_value());
}

/**
 * @tc.name: UnregisterColorPicker002
 * @tc.desc: Test UnregisterColorPicker when hasRegisterColorPicker_ is false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, UnregisterColorPicker002, TestSize.Level1)
{
    auto titleBarNode = CreateTitleBarNode();
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    
    titleBarPattern->hasRegisterColorPicker_ = false;
    titleBarPattern->isColorPickerDark_ = true;
    
    titleBarPattern->UnregisterColorPicker();
    EXPECT_FALSE(titleBarPattern->hasRegisterColorPicker_);
    EXPECT_TRUE(titleBarPattern->isColorPickerDark_.has_value());
}
} // namespace OHOS::Ace::NG