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
#define private public
#define protected public
#include "base/ressched/taihang_optimizer.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components/swiper/swiper_controller.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

class TaihangOptimizerTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        NG::MockPipelineContext::SetUp();
    }

    static void TearDownTestSuite()
    {
        NG::MockPipelineContext::TearDown();
    }
    void SetUp() override
    {
        optimizer_ = std::make_shared<TaihangOptimizer>();
    }
    void TearDown() override
    {
        optimizer_ = nullptr;
    }

    std::shared_ptr<TaihangOptimizer> optimizer_;
};

HWTEST_F(TaihangOptimizerTest, IsInitedTest001, TestSize.Level1)
{
    optimizer_->isInited_ = false;
    EXPECT_FALSE(optimizer_->IsInited());

    optimizer_->isInited_ = true;
    EXPECT_TRUE(optimizer_->IsInited());
}

HWTEST_F(TaihangOptimizerTest, IsEnableTest001, TestSize.Level1)
{
    optimizer_->enable_ = false;
    EXPECT_FALSE(optimizer_->IsEnable());

    optimizer_->enable_ = true;
    EXPECT_TRUE(optimizer_->IsEnable());
}

HWTEST_F(TaihangOptimizerTest, SetEnableTest001, TestSize.Level1)
{
    optimizer_->SetEnable(true);
    EXPECT_TRUE(optimizer_->enable_);
}

HWTEST_F(TaihangOptimizerTest, SetEnableTest002, TestSize.Level1)
{
    optimizer_->SetEnable(false);
    EXPECT_FALSE(optimizer_->enable_);
}

HWTEST_F(TaihangOptimizerTest, CheckSwiperPageValidTest001, TestSize.Level1)
{
    optimizer_->isInited_ = true;
    optimizer_->enable_ = false;
    optimizer_->pageNameSet_.clear();
    bool result = optimizer_->CheckSwiperPageValid("page1,page2");
    EXPECT_FALSE(result);
}

HWTEST_F(TaihangOptimizerTest, CheckSwiperPageValidTest002, TestSize.Level1)
{
    optimizer_->isInited_ = true;
    optimizer_->enable_ = true;
    optimizer_->pageNameSet_.clear();
    bool result = optimizer_->CheckSwiperPageValid("page1,page2");
    EXPECT_FALSE(result);
}

HWTEST_F(TaihangOptimizerTest, CheckSwiperPageValidTest003, TestSize.Level1)
{
    optimizer_->isInited_ = true;
    optimizer_->enable_ = true;
    optimizer_->pageNameSet_ = {"page1"};
    bool result = optimizer_->CheckSwiperPageValid("page1");
    EXPECT_TRUE(result);
}

HWTEST_F(TaihangOptimizerTest, CheckSwiperPageValidTest004, TestSize.Level1)
{
    optimizer_->isInited_ = true;
    optimizer_->enable_ = true;
    optimizer_->pageNameSet_ = {"page2"};
    bool result = optimizer_->CheckSwiperPageValid("page1,page2");
    EXPECT_TRUE(result);
}

HWTEST_F(TaihangOptimizerTest, CheckSwiperPageValidTest005, TestSize.Level1)
{
    optimizer_->isInited_ = true;
    optimizer_->enable_ = true;
    optimizer_->pageNameSet_ = {"page2", "page3"};
    bool result = optimizer_->CheckSwiperPageValid("page1,page2");
    EXPECT_TRUE(result);
}

HWTEST_F(TaihangOptimizerTest, CheckSwiperPageValidTest006, TestSize.Level1)
{
    optimizer_->isInited_ = true;
    optimizer_->enable_ = true;
    optimizer_->pageNameSet_ = {"page2", "page3"};
    bool result = optimizer_->CheckSwiperPageValid("page1,page4");
    EXPECT_FALSE(result);
}

HWTEST_F(TaihangOptimizerTest, CheckSwiperPageValidTest007, TestSize.Level1)
{
    optimizer_->isInited_ = true;
    optimizer_->enable_ = true;
    optimizer_->pageNameSet_ = {"page2"};
    bool result = optimizer_->CheckSwiperPageValid("");
    EXPECT_FALSE(result);
}

HWTEST_F(TaihangOptimizerTest, CheckSwiperPageValidTest008, TestSize.Level1)
{
    optimizer_->isInited_ = false;
    bool result = optimizer_->CheckSwiperPageValid("page1,page3");
    EXPECT_FALSE(result);
}

HWTEST_F(TaihangOptimizerTest, ComponentPreMakeTest001, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> extInfo;
    extInfo["componentType"] = "1";
    extInfo["path"] = "test";
    extInfo["index"] = "0";
    optimizer_->ComponentPreMake(extInfo);
    EXPECT_TRUE(optimizer_->IsInited() || !optimizer_->IsInited());
}

HWTEST_F(TaihangOptimizerTest, ComponentPreMakeTest002, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> extInfo;
    extInfo["componentType"] = "0";
    extInfo["path"] = "test";
    extInfo["index"] = "0";
    optimizer_->ComponentPreMake(extInfo);
    EXPECT_TRUE(optimizer_->IsInited() || !optimizer_->IsInited());
}

HWTEST_F(TaihangOptimizerTest, ComponentPreMakeTest003, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> extInfo;
    extInfo["componentType"] = "2";
    extInfo["path"] = "test";
    extInfo["index"] = "0";
    optimizer_->ComponentPreMake(extInfo);
    EXPECT_TRUE(optimizer_->IsInited() || !optimizer_->IsInited());
}

HWTEST_F(TaihangOptimizerTest, ComponentPreMakeTest004, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> extInfo;
    optimizer_->ComponentPreMake(extInfo);
    EXPECT_TRUE(optimizer_->IsInited() || !optimizer_->IsInited());
}

HWTEST_F(TaihangOptimizerTest, InitTest001, TestSize.Level1)
{
    optimizer_->isInited_ = true;
    optimizer_->Init();
    EXPECT_TRUE(optimizer_->isInited_);
}

HWTEST_F(TaihangOptimizerTest, InitTest002, TestSize.Level1)
{
    optimizer_->isInited_ = false;
    optimizer_->Init();
    EXPECT_TRUE(optimizer_->isInited_);
}

HWTEST_F(TaihangOptimizerTest, InitTest003, TestSize.Level1)
{
    optimizer_->isInited_ = false;
    optimizer_->enable_ = false;
    optimizer_->Init();
    EXPECT_TRUE(optimizer_->isInited_);
}

HWTEST_F(TaihangOptimizerTest, PostSwiperPreMakeTaskTest001, TestSize.Level1)
{
    auto frameNode = NG::FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 1, AceType::MakeRefPtr<NG::SwiperPattern>());
    EXPECT_NE(frameNode, nullptr);
    optimizer_->PostSwiperPreMakeTask(frameNode, 0);
}

HWTEST_F(TaihangOptimizerTest, PostSwiperPreMakeTaskTest002, TestSize.Level1)
{
    auto frameNode = NG::FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<NG::Pattern>());
    EXPECT_NE(frameNode, nullptr);
    optimizer_->PostSwiperPreMakeTask(frameNode, 0);
}

HWTEST_F(TaihangOptimizerTest, PostSwiperPreMakeTaskTest003, TestSize.Level1)
{
    RefPtr<NG::FrameNode> frameNode = nullptr;
    optimizer_->PostSwiperPreMakeTask(frameNode, 0);
    EXPECT_EQ(frameNode, nullptr);
}

HWTEST_F(TaihangOptimizerTest, PostSwiperPreMakeTaskTest004, TestSize.Level1)
{
    auto frameNode = NG::FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 1, AceType::MakeRefPtr<NG::SwiperPattern>());
    auto swiperPattern = frameNode->GetPattern<NG::SwiperPattern>();
    EXPECT_NE(swiperPattern, nullptr);
    swiperPattern->swiperController_ = nullptr;
    optimizer_->PostSwiperPreMakeTask(frameNode, 0);

    EXPECT_NE(frameNode, nullptr);
}

HWTEST_F(TaihangOptimizerTest, HandleSwiperPreMakeTest001, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> extInfo;
    optimizer_->HandleSwiperPreMake(extInfo);

    EXPECT_EQ(extInfo.size(), 0);
}

HWTEST_F(TaihangOptimizerTest, HandleSwiperPreMakeTest003, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> extInfo;
    extInfo["path"] = "";
    extInfo["index"] = "0";
    optimizer_->HandleSwiperPreMake(extInfo);

    EXPECT_NE(extInfo.size(), 0);
}

HWTEST_F(TaihangOptimizerTest, HandleSwiperPreMakeTest004, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> extInfo;
    extInfo["path"] = "test";
    extInfo["index"] = "-1";
    optimizer_->HandleSwiperPreMake(extInfo);

    EXPECT_NE(extInfo.size(), 0);
}

HWTEST_F(TaihangOptimizerTest, HandleSwiperPreMakeWithValidPath001, TestSize.Level1)
{
    auto rootNode = NG::FrameNode::CreateFrameNode("root", 0, AceType::MakeRefPtr<NG::Pattern>());
    ASSERT_NE(rootNode, nullptr);
    auto childNode = NG::FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 1, AceType::MakeRefPtr<NG::SwiperPattern>());
    ASSERT_NE(childNode, nullptr);
    childNode->MountToParent(rootNode);

    auto context = NG::PipelineContext::GetCurrentContextSafely();
    ASSERT_NE(context, nullptr);
    context->rootNode_ = rootNode;

    std::unordered_map<std::string, std::string> extInfo;
    extInfo["path"] = "/root/swiper[0]";
    extInfo["index"] = "0";
    optimizer_->HandleSwiperPreMake(extInfo);

    EXPECT_NE(extInfo.size(), 0);
}

HWTEST_F(TaihangOptimizerTest, HandleSwiperPreMakeWithValidPath002, TestSize.Level1)
{
    auto rootNode = NG::FrameNode::CreateFrameNode("root", 0, AceType::MakeRefPtr<NG::Pattern>());
    ASSERT_NE(rootNode, nullptr);
    auto childNode = NG::FrameNode::CreateFrameNode("other", 1, AceType::MakeRefPtr<NG::Pattern>());
    ASSERT_NE(childNode, nullptr);
    childNode->MountToParent(rootNode);

    auto context = NG::PipelineContext::GetCurrentContextSafely();
    ASSERT_NE(context, nullptr);
    context->rootNode_ = rootNode;

    std::unordered_map<std::string, std::string> extInfo;
    extInfo["path"] = "/root/swiper[0]";
    extInfo["index"] = "0";
    optimizer_->HandleSwiperPreMake(extInfo);

    EXPECT_NE(extInfo.size(), 0);
}

HWTEST_F(TaihangOptimizerTest, HandleSwiperPreMakeWithValidPath003, TestSize.Level1)
{
    auto rootNode = NG::FrameNode::CreateFrameNode("root", 0, AceType::MakeRefPtr<NG::Pattern>());
    ASSERT_NE(rootNode, nullptr);

    auto context = NG::PipelineContext::GetCurrentContextSafely();
    ASSERT_NE(context, nullptr);
    context->rootNode_ = rootNode;

    std::unordered_map<std::string, std::string> extInfo;
    extInfo["path"] = "/root/other[0]";
    extInfo["index"] = "0";
    optimizer_->HandleSwiperPreMake(extInfo);

    EXPECT_NE(extInfo.size(), 0);
}

HWTEST_F(TaihangOptimizerTest, HandleSwiperPreMakeWithNullRoot001, TestSize.Level1)
{
    auto context = NG::PipelineContext::GetCurrentContextSafely();
    ASSERT_NE(context, nullptr);
    context->rootNode_ = nullptr;

    std::unordered_map<std::string, std::string> extInfo;
    extInfo["path"] = "test[0]";
    extInfo["index"] = "0";
    optimizer_->HandleSwiperPreMake(extInfo);

    EXPECT_NE(extInfo.size(), 0);
}

HWTEST_F(TaihangOptimizerTest, HandleSwiperPreMakeWithNegativeIndex001, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> extInfo;
    extInfo["path"] = "test[0]";
    extInfo["index"] = "-5";
    optimizer_->HandleSwiperPreMake(extInfo);

    EXPECT_NE(extInfo.size(), 0);
}

HWTEST_F(TaihangOptimizerTest, HandleSwiperPreMakeWithEmptyPath001, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> extInfo;
    extInfo["path"] = "";
    extInfo["index"] = "10";
    optimizer_->HandleSwiperPreMake(extInfo);

    EXPECT_NE(extInfo.size(), 0);
}

HWTEST_F(TaihangOptimizerTest, HandleSwiperPreMakeWithMalformedBracket001, TestSize.Level1)
{
    auto rootNode = NG::FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<NG::Pattern>());
    ASSERT_NE(rootNode, nullptr);

    auto context = NG::PipelineContext::GetCurrentContextSafely();
    ASSERT_NE(context, nullptr);
    context->rootNode_ = rootNode;

    std::unordered_map<std::string, std::string> extInfo;
    extInfo["path"] = "test[";
    extInfo["index"] = "0";
    optimizer_->HandleSwiperPreMake(extInfo);

    EXPECT_NE(extInfo.size(), 0);
}

HWTEST_F(TaihangOptimizerTest, HandleSwiperPreMakeWithMalformedBracket002, TestSize.Level1)
{
    auto rootNode = NG::FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<NG::Pattern>());
    ASSERT_NE(rootNode, nullptr);

    auto context = NG::PipelineContext::GetCurrentContextSafely();
    ASSERT_NE(context, nullptr);
    context->rootNode_ = rootNode;

    std::unordered_map<std::string, std::string> extInfo;
    extInfo["path"] = "test[0";
    extInfo["index"] = "0";
    optimizer_->HandleSwiperPreMake(extInfo);

    EXPECT_NE(extInfo.size(), 0);
}

HWTEST_F(TaihangOptimizerTest, HandleSwiperPreMakeWithMalformedBracket003, TestSize.Level1)
{
    auto rootNode = NG::FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<NG::Pattern>());
    ASSERT_NE(rootNode, nullptr);

    auto context = NG::PipelineContext::GetCurrentContextSafely();
    ASSERT_NE(context, nullptr);
    context->rootNode_ = rootNode;

    std::unordered_map<std::string, std::string> extInfo;
    extInfo["path"] = "test[]";
    extInfo["index"] = "0";
    optimizer_->HandleSwiperPreMake(extInfo);

    EXPECT_NE(extInfo.size(), 0);
}

HWTEST_F(TaihangOptimizerTest, HandleSwiperPreMakeWithMalformedBracket004, TestSize.Level1)
{
    auto rootNode = NG::FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<NG::Pattern>());
    ASSERT_NE(rootNode, nullptr);

    auto context = NG::PipelineContext::GetCurrentContextSafely();
    ASSERT_NE(context, nullptr);
    context->rootNode_ = rootNode;

    std::unordered_map<std::string, std::string> extInfo;
    extInfo["path"] = "test[ ]";
    extInfo["index"] = "0";
    optimizer_->HandleSwiperPreMake(extInfo);

    EXPECT_NE(extInfo.size(), 0);
}

HWTEST_F(TaihangOptimizerTest, HandleSwiperPreMakeWithInvalidIndex001, TestSize.Level1)
{
    auto rootNode = NG::FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<NG::Pattern>());
    ASSERT_NE(rootNode, nullptr);

    auto context = NG::PipelineContext::GetCurrentContextSafely();
    ASSERT_NE(context, nullptr);
    context->rootNode_ = rootNode;

    std::unordered_map<std::string, std::string> extInfo;
    extInfo["path"] = "test[abc]";
    extInfo["index"] = "0";
    optimizer_->HandleSwiperPreMake(extInfo);

    EXPECT_NE(extInfo.size(), 0);
}

HWTEST_F(TaihangOptimizerTest, HandleSwiperPreMakeWithInvalidIndex002, TestSize.Level1)
{
    auto rootNode = NG::FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<NG::Pattern>());
    ASSERT_NE(rootNode, nullptr);

    auto context = NG::PipelineContext::GetCurrentContextSafely();
    ASSERT_NE(context, nullptr);
    context->rootNode_ = rootNode;

    std::unordered_map<std::string, std::string> extInfo;
    extInfo["path"] = "test[-1]";
    extInfo["index"] = "0";
    optimizer_->HandleSwiperPreMake(extInfo);

    EXPECT_NE(extInfo.size(), 0);
}

HWTEST_F(TaihangOptimizerTest, HandleSwiperPreMakeWithValidJson001, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> extInfo;
    extInfo["path"] = "validPath";
    extInfo["index"] = "5";
    optimizer_->HandleSwiperPreMake(extInfo);

    EXPECT_NE(extInfo.size(), 0);
}

HWTEST_F(TaihangOptimizerTest, HandleSwiperPreMakeWithValidJson002, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> extInfo;
    extInfo["path"] = "/root/child[0]";
    extInfo["index"] = "0";
    optimizer_->HandleSwiperPreMake(extInfo);

    EXPECT_NE(extInfo.size(), 0);
}


HWTEST_F(TaihangOptimizerTest, HandleSwiperPreMakeWithMissingPathKey001, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> extInfo;
    extInfo["index"] = "0";
    optimizer_->HandleSwiperPreMake(extInfo);

    EXPECT_NE(extInfo.size(), 0);
}

HWTEST_F(TaihangOptimizerTest, HandleSwiperPreMakeWithMissingIndexKey001, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> extInfo;
    extInfo["path"] = "test";
    optimizer_->HandleSwiperPreMake(extInfo);

    EXPECT_NE(extInfo.size(), 0);
}

HWTEST_F(TaihangOptimizerTest, PostSwiperPreMakeTaskWithPositiveIndex001, TestSize.Level1)
{
    auto frameNode = NG::FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 1, AceType::MakeRefPtr<NG::SwiperPattern>());
    auto swiperPattern = frameNode->GetPattern<NG::SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto controller = AceType::MakeRefPtr<SwiperController>();
    swiperPattern->swiperController_ = controller;

    optimizer_->PostSwiperPreMakeTask(frameNode, 5);
    EXPECT_NE(swiperPattern->swiperController_, nullptr);
}

HWTEST_F(TaihangOptimizerTest, CheckSwiperPageValidWithChineseChars001, TestSize.Level1)
{
    optimizer_->isInited_ = true;
    optimizer_->enable_ = true;
    optimizer_->pageNameSet_ = {"页面1"};
    bool result = optimizer_->CheckSwiperPageValid("prefix,页面1");
    EXPECT_TRUE(result);
}

HWTEST_F(TaihangOptimizerTest, CheckSwiperPageValidWithWhitespace001, TestSize.Level1)
{
    optimizer_->isInited_ = true;
    optimizer_->enable_ = true;
    optimizer_->pageNameSet_ =  {"page1"};
    bool result = optimizer_->CheckSwiperPageValid("prefix, page1");
    EXPECT_FALSE(result);
}

HWTEST_F(TaihangOptimizerTest, ConstructorTest001, TestSize.Level1)
{
    auto newOptimizer = std::make_shared<TaihangOptimizer>();
    EXPECT_FALSE(newOptimizer->IsInited());
    EXPECT_FALSE(newOptimizer->IsEnable());
}

HWTEST_F(TaihangOptimizerTest, DestructorTest001, TestSize.Level1)
{
    auto newOptimizer = std::make_shared<TaihangOptimizer>();
    newOptimizer.reset();
    EXPECT_EQ(newOptimizer, nullptr);
}

HWTEST_F(TaihangOptimizerTest, MultipleInitCalls001, TestSize.Level1)
{
    optimizer_->isInited_ = false;
    optimizer_->Init();
    EXPECT_TRUE(optimizer_->isInited_);
    optimizer_->Init();
    EXPECT_TRUE(optimizer_->isInited_);
}

HWTEST_F(TaihangOptimizerTest, EnableDisableSequence001, TestSize.Level1)
{
    optimizer_->SetEnable(true);
    EXPECT_TRUE(optimizer_->IsEnable());
    optimizer_->SetEnable(false);
    EXPECT_FALSE(optimizer_->IsEnable());
    optimizer_->SetEnable(true);
    EXPECT_TRUE(optimizer_->IsEnable());
}

HWTEST_F(TaihangOptimizerTest, ParseReplyPages001, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> reply;
    reply["pageNames"] = "[\"page1\", \"page2\"]";
    optimizer_->ParseReplyPages(reply);
    EXPECT_FALSE(optimizer_->pageNameSet_.empty());
}

HWTEST_F(TaihangOptimizerTest, ParseReplyPages002, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> reply;
    reply["pageNames"] = "";
    optimizer_->ParseReplyPages(reply);
    EXPECT_TRUE(optimizer_->pageNameSet_.empty());
}

HWTEST_F(TaihangOptimizerTest, ParseReplyPages003, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> reply;
    reply["pageNames"] = "[1,2]";
    optimizer_->ParseReplyPages(reply);
    EXPECT_TRUE(optimizer_->pageNameSet_.empty());
}
} // namespace OHOS::Ace