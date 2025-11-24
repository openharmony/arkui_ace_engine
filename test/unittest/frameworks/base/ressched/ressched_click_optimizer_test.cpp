/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#define private public
#define protected public
#include "base/ressched/ressched_click_optimizer.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

static std::unique_ptr<ResSchedClickOptimizer> optimizer_;

class ResSchedClickOptimizerTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        optimizer_ = std::make_unique<ResSchedClickOptimizer>();
    }
    static void TearDownTestSuite()
    {
        optimizer_.reset();
    }
    void SetUp() {};
    void TearDown() {};
};

/**
 * @tc.name: GetClickExtEnabledTest001
 * @tc.desc: test GetClickExtEnabled method
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedClickOptimizerTest, GetClickExtEnabledTest001, TestSize.Level1)
{
    optimizer_->clickExtEnabled_ = false;
    EXPECT_FALSE(optimizer_->GetClickExtEnabled());

    optimizer_->clickExtEnabled_ = true;
    EXPECT_TRUE(optimizer_->GetClickExtEnabled());
}

/**
 * @tc.name: ReportClickTest001
 * @tc.desc: test ReportClick method
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedClickOptimizerTest, ReportClickTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init node.
     */
    auto node = NG::FrameNode::CreateFrameNode("myButton", 101, AceType::MakeRefPtr<NG::Pattern>());
    WeakPtr<NG::FrameNode> host = AceType::WeakClaim(AceType::RawPtr(node));
    GestureEvent info = GestureEvent();

    /**
     * @tc.steps: step2. call ReportClick and compare result.
     * @tc.steps: case1: GetClickExtEnabled is false
     * @tc.expected: step2. result equals.
     */
    optimizer_->SetClickExtEnabled(false);
    optimizer_->ReportClick(host, info);
    EXPECT_EQ(optimizer_->GetClickExtEnabled(), false);

    /**
     * @tc.steps: step2. call ReportClick and compare result.
     * @tc.steps: case2: GetClickExtEnabled is true
     * @tc.expected: step2. result equals.
     */
    optimizer_->SetClickExtEnabled(true);
    optimizer_->SetMaxDeep(20);
    optimizer_->ReportClick(host, info);
    EXPECT_EQ(optimizer_->GetClickExtEnabled(), true);
    EXPECT_EQ(optimizer_->GetMaxDeep(), 20);
}

/**
 * @tc.name: GetComponentTextAndImageSourceRecursiveTest001
 * @tc.desc: test GetComponentTextAndImageSourceRecursive method
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedClickOptimizerTest, GetComponentTextAndImageSourceRecursiveTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init node.
     */
    auto node = NG::FrameNode::CreateFrameNode("test1", 1, AceType::MakeRefPtr<NG::Pattern>());
    WeakPtr<NG::FrameNode> host = AceType::WeakClaim(AceType::RawPtr(node));
    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);

    /**
     * @tc.steps: step2. call GetComponentTextAndImageSourceRecursive and compare result.
     * @tc.steps: case1. deep lte 0
     * @tc.expected: step2. result equals.
     */
    std::string text1 = "";
    std::string imgSrc1 = "";
    ResSchedClickOptimizer::GetComponentTextAndImageSourceRecursive(host, text1, imgSrc1, 0);
    EXPECT_EQ(text1, "");
    EXPECT_EQ(imgSrc1, "");

    /**
     * @tc.steps: step2. call GetComponentTextAndImageSourceRecursive and compare result.
     * @tc.steps: case2. deep gt 0, text is empty, nodeText is empty
     * @tc.expected: step2. result equals.
     */
    std::string text2 = "";
    std::string imgSrc2 = "";
    accessibilityProperty->SetText("");
    accessibilityProperty->SetAccessibilityText("");
    ResSchedClickOptimizer::GetComponentTextAndImageSourceRecursive(host, text2, imgSrc2, 1);
    EXPECT_EQ(text2, "");
    EXPECT_EQ(imgSrc2, "");

    /**
     * @tc.steps: step2. call GetComponentTextAndImageSourceRecursive and compare result.
     * @tc.steps: case3. deep gt 0, text is not empty, nodeText is empty
     * @tc.expected: step2. result equals.
     */
    std::string text3 = "123";
    std::string imgSrc3 = "";
    ResSchedClickOptimizer::GetComponentTextAndImageSourceRecursive(host, text3, imgSrc3, 1);
    EXPECT_EQ(text3, "123");
    EXPECT_EQ(imgSrc3, "");

    /**
     * @tc.steps: step2. call GetComponentTextAndImageSourceRecursive and compare result.
     * @tc.steps: case4. deep gt 0, text is empty, nodeText is not empty
     * @tc.expected: step2. result equals.
     */
    std::string text4 = "";
    std::string imgSrc4 = "";
    accessibilityProperty->SetText("test");
    ResSchedClickOptimizer::GetComponentTextAndImageSourceRecursive(host, text4, imgSrc4, 1);
    EXPECT_EQ(text4, "test");
    EXPECT_EQ(imgSrc4, "");

    /**
     * @tc.steps: step2. call GetComponentTextAndImageSourceRecursive and compare result.
     * @tc.steps: case5. deep gt 0, text is not empty, nodeText is not empty
     * @tc.expected: step2. result equals.
     */
    std::string text5 = "123";
    std::string imgSrc5 = "";
    accessibilityProperty->SetText("test");
    ResSchedClickOptimizer::GetComponentTextAndImageSourceRecursive(host, text5, imgSrc5, 1);
    EXPECT_EQ(text5, "123,test");
    EXPECT_EQ(imgSrc5, "");
}

/**
 * @tc.name: GetComponentTextAndImageSourceRecursiveTest002
 * @tc.desc: test GetComponentTextAndImageSourceRecursive method
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedClickOptimizerTest, GetComponentTextAndImageSourceRecursiveTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init node.
     */
    auto node = NG::FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<NG::ImagePattern>());
    WeakPtr<NG::FrameNode> host = AceType::WeakClaim(AceType::RawPtr(node));

    /**
     * @tc.steps: step2. call GetComponentTextAndImageSourceRecursive function and compare result.
     * @tc.steps: case1: imgSrc is empty, property is null
     * @tc.expected: step2. result equals.
     */
    node->layoutProperty_ = nullptr;
    std::string text1 = "";
    std::string imgSrc1 = "";
    ResSchedClickOptimizer::GetComponentTextAndImageSourceRecursive(host, text1, imgSrc1, 1);
    EXPECT_EQ(text1, "");
    EXPECT_EQ(imgSrc1, "");

    /**
     * @tc.steps: step2. call GetComponentTextAndImageSourceRecursive function and compare result.
     * @tc.steps: case2: imgSrc is empty, src is empty
     * @tc.expected: step2. result equals.
     */
    std::string text2 = "";
    std::string imgSrc2 = "";
    auto imageLayoutProperty = AceType::MakeRefPtr<NG::ImageLayoutProperty>();
    imageLayoutProperty->UpdateImageSourceInfo(
        ImageSourceInfo("", Dimension(300.0), Dimension(200.0)));
    node->SetLayoutProperty(imageLayoutProperty);
    ResSchedClickOptimizer::GetComponentTextAndImageSourceRecursive(host, text2, imgSrc2, 1);
    EXPECT_EQ(text2, "");
    EXPECT_EQ(imgSrc2, "");

    /**
     * @tc.steps: step2. call GetComponentTextAndImageSourceRecursive function and compare result.
     * @tc.steps: case3: imgSrc is not empty, src is empty
     * @tc.expected: step2. result equals.
     */
    std::string text3 = "";
    std::string imgSrc3 = "123";
    ResSchedClickOptimizer::GetComponentTextAndImageSourceRecursive(host, text3, imgSrc3, 1);
    EXPECT_EQ(text3, "");
    EXPECT_EQ(imgSrc3, "123");

    /**
     * @tc.steps: step2. call GetComponentTextAndImageSourceRecursive function and compare result.
     * @tc.steps: case4: imgSrc is empty, src is not empty
     * @tc.expected: step2. result equals.
     */
    imageLayoutProperty->UpdateImageSourceInfo(
        ImageSourceInfo("file://data/data/com.example.test/res/example.svg", Dimension(300.0), Dimension(200.0)));
    std::string text4 = "";
    std::string imgSrc4 = "";
    ResSchedClickOptimizer::GetComponentTextAndImageSourceRecursive(host, text4, imgSrc4, 1);
    EXPECT_EQ(text4, "");
    EXPECT_EQ(imgSrc4, "file://data/data/com.example.test/res/example.svg");

    /**
     * @tc.steps: step2. call GetComponentTextAndImageSourceRecursive function and compare result.
     * @tc.steps: case5: imgSrc is not empty, src is not empty
     * @tc.expected: step2. result equals.
     */
    std::string text5 = "";
    std::string imgSrc5 = "123";
    ResSchedClickOptimizer::GetComponentTextAndImageSourceRecursive(host, text5, imgSrc5, 1);
    EXPECT_EQ(text5, "");
    EXPECT_EQ(imgSrc5, "123,file://data/data/com.example.test/res/example.svg");

    /**
     * @tc.steps: step2. call GetComponentTextAndImageSourceRecursive function and compare result.
     * @tc.steps: case6: imgSrc is base64
     * @tc.expected: step2. result equals.
     */
    imageLayoutProperty->UpdateImageSourceInfo(
        ImageSourceInfo("data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAUA", Dimension(300.0), Dimension(200.0)));
    std::string text6 = "";
    std::string imgSrc6 = "";
    ResSchedClickOptimizer::GetComponentTextAndImageSourceRecursive(host, text6, imgSrc6, 1);
    EXPECT_EQ(text6, "");
    EXPECT_EQ(imgSrc6, "data:image/png;base64;iVBORw0KGg");
}
} // namespace OHOS::Ace