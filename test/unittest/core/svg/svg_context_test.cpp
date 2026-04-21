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
#include "frameworks/core/components_ng/svg/svg_context.h"
#include "frameworks/core/components_ng/svg/parse/svg_node.h"
#include "core/animation/animator.h"

using namespace testing;
using namespace OHOS::Ace::NG;

class SvgContextTest : public testing::Test {
public:
    void SetUp() override
    {
        svgContext_ = AceType::MakeRefPtr<SvgContext>();
    }

    void TearDown() override
    {
        svgContext_ = nullptr;
    }

protected:
    RefPtr<SvgContext> svgContext_;
};

/**
 * @tc.name: SvgContextTest001
 * @tc.desc: Test SVG context initialization and default values
 * @tc.type: FUNC
 */
HWTEST_F(SvgContextTest, SvgContextTest001, TestSize.Level1)
{
    // Test that SvgContext initializes correctly
    EXPECT_NE(svgContext_, nullptr);
    EXPECT_EQ(svgContext_->GetRootViewBox(), Rect(0, 0, 0, 0));
    EXPECT_EQ(svgContext_->GetViewPort(), Size(0, 0));
    EXPECT_EQ(svgContext_->GetContentSize(), Size(0, 0));
    EXPECT_FALSE(svgContext_->GetHasRecordedPath());
}

/**
 * @tc.name: SvgContextTest002
 * @tc.desc: Test SVG node ID mapping functionality
 * @tc.type: FUNC
 */
HWTEST_F(SvgContextTest, SvgContextTest002, TestSize.Level1)
{
    // Create a test SVG node
    auto testNode = AceType::MakeRefPtr<SvgNode>();
    testNode->SetNodeId("testNode");
    
    // Test pushing SVG node to context
    svgContext_->Push("testNode", testNode);
    
    // Test retrieving SVG node by ID
    auto retrievedNode = svgContext_->GetSvgNodeById("testNode");
    EXPECT_NE(retrievedNode, nullptr);
    EXPECT_EQ(retrievedNode->GetNodeId(), "testNode");
    
    // Test retrieving non-existent node
    auto nonExistentNode = svgContext_->GetSvgNodeById("nonExistent");
    EXPECT_EQ(nonExistentNode, nullptr);
}

/**
 * @tc.name: SvgContextTest003
 * @tc.desc: Test SVG style mapping functionality
 * @tc.type: FUNC
 */
HWTEST_F(SvgContextTest, SvgContextTest003, TestSize.Level1)
{
    // Test pushing style to context
    std::string styleName = "testStyle";
    std::pair<std::string, std::string> attrPair("color", "red");
    svgContext_->PushStyle(styleName, attrPair);
    
    // Test retrieving style attribute map
    const auto& attrMap = svgContext_->GetAttrMap(styleName);
    EXPECT_EQ(attrMap.size(), 1);
    EXPECT_EQ(attrMap.at("color"), "red");
    
    // Test retrieving non-existent style
    const auto& emptyAttrMap = svgContext_->GetAttrMap("nonExistentStyle");
    EXPECT_TRUE(emptyAttrMap.empty());
}

/**
 * @tc.name: SvgContextTest004
 * @tc.desc: Test SVG animator management
 * @tc.type: FUNC
 */
HWTEST_F(SvgContextTest, SvgContextTest004, TestSize.Level1)
{
    // Create test animator
    auto animator = AceType::MakeRefPtr<Animator>();
    int32_t animatorKey = 100;
    
    // Test adding animator
    svgContext_->AddAnimator(animatorKey, animator);
    
    // Test controlling animators
    svgContext_->ControlAnimators(true);  // Play animators
    
    // Test removing animator
    svgContext_->RemoveAnimator(animatorKey);
    // Note: Since it's a weak reference, removing should not immediately fail
}

/**
 * @tc.name: SvgContextTest005
 * @tc.desc: Test SVG context view box and viewport setting
 * @tc.type: FUNC
 */
HWTEST_F(SvgContextTest, SvgContextTest005, TestSize.Level1)
{
    // Test setting root view box
    Rect viewBox(10, 20, 200, 150);
    svgContext_->SetRootViewBox(viewBox);
    EXPECT_EQ(svgContext_->GetRootViewBox(), viewBox);
    
    // Test setting viewport
    Size viewPort(300, 250);
    svgContext_->SetViewPort(viewPort);
    EXPECT_EQ(svgContext_->GetViewPort(), viewPort);
}

/**
 * @tc.name: SvgContextTest006
 * @tc.desc: Test SVG content size management
 * @tc.type: FUNC
 */
HWTEST_F(SvgContextTest, SvgContextTest006, TestSize.Level1)
{
    // Test setting content size
    Size contentSize(400, 300);
    svgContext_->SetContentSize(contentSize);
    EXPECT_EQ(svgContext_->GetContentSize(), contentSize);
}

/**
 * @tc.name: SvgContextTest007
 * @tc.desc: Test SVG path recording flag
 * @tc.type: FUNC
 */
HWTEST_F(SvgContextTest, SvgContextTest007, TestSize.Level1)
{
    // Test initial state
    EXPECT_FALSE(svgContext_->GetHasRecordedPath());
    
    // Test setting path recording flag
    svgContext_->SetGetHasRecordedPath(true);
    EXPECT_TRUE(svgContext_->GetHasRecordedPath());
    
    svgContext_->SetGetHasRecordedPath(false);
    EXPECT_FALSE(svgContext_->GetHasRecordedPath());
}

/**
 * @tc.name: SvgContextTest008
 * @tc.desc: Test SVG fill color management
 * @tc.type: FUNC
 */
HWTEST_F(SvgContextTest, SvgContextTest008, TestSize.Level1)
{
    // Test setting fill color
    Color fillColor(Color::RED);
    svgContext_->SetFillColor(fillColor);
    
    // Test getting fill color
    auto retrievedColor = svgContext_->GetFillColor();
    EXPECT_TRUE(retrievedColor.has_value());
    EXPECT_EQ(retrievedColor->GetValue(), fillColor.GetValue());
}

/**
 * @tc.name: SvgContextTest009
 * @tc.desc: Test SVG user config version management
 * @tc.type: FUNC
 */
HWTEST_F(SvgContextTest, SvgContextTest009, TestSize.Level1)
{
    // Test setting user config version
    uint32_t version = SVG_FEATURE_SUPPORT_TWO;
    svgContext_->SetUsrConfigVersion(version);
    EXPECT_EQ(svgContext_->GetUsrConfigVersion(), version);
    
    // Test with different version
    svgContext_->SetUsrConfigVersion(SVG_FEATURE_SUPPORT_UNDEFINE);
    EXPECT_EQ(svgContext_->GetUsrConfigVersion(), SVG_FEATURE_SUPPORT_UNDEFINE);
}

/**
 * @tc.name: SvgContextTest010
 * @tc.desc: Test SVG dump info functionality
 * @tc.type: FUNC
 */
HWTEST_F(SvgContextTest, SvgContextTest010, TestSize.Level1)
{
    // Test dump info creation
    Size contentSize(500, 400);
    std::string drawTime = "100ms";
    SvgDumpInfo dumpInfo(contentSize, drawTime);
    
    // Test dump info string conversion
    std::string dumpString = dumpInfo.ToString();
    EXPECT_TRUE(dumpString.find("contentSize:") != std::string::npos);
    EXPECT_TRUE(dumpString.find(contentSize.ToString()) != std::string::npos);
    EXPECT_TRUE(dumpString.find(drawTime) != std::string::npos);
    
    // Test svg draw path info
    std::string pathInfo = "M10,20 L30,40";
    dumpInfo.SetSvgDrawPathInfoDump(pathInfo);
    dumpString = dumpInfo.ToString();
    EXPECT_TRUE(dumpString.find(pathInfo) != std::string::npos);
    
    // Test creating dump info in SVG context
    svgContext_->CreateDumpInfo(dumpInfo);
    svgContext_->SetSvgDrawPathInfoDump("TestPath");
    
    std::string contextDumpInfo = svgContext_->GetDumpInfo();
    EXPECT_TRUE(contextDumpInfo.find("TestPath") != std::string::npos);
}

/**
 * @tc.name: SvgContextTest011
 * @tc.desc: Test SVG normalize to pixel function
 * @tc.type: FUNC
 */
HWTEST_F(SvgContextTest, SvgContextTest011, TestSize.Level1)
{
    // Test setting normalize function
    bool functionCalled = false;
    FuncNormalizeToPx normalizeFunc = [&](const Dimension& dim) -> double {
        functionCalled = true;
        return 10.0; // Return a test value
    };
    
    svgContext_->SetFuncNormalizeToPx(normalizeFunc);
    
    // Test calling normalize function
    Dimension testDim(50.0, DimensionUnit::PX);
    double result = svgContext_->NormalizeToPx(testDim);
    EXPECT_TRUE(functionCalled);
    EXPECT_EQ(result, 10.0);
}

/**
 * @tc.name: SvgContextTest012
 * @tc.desc: Test SVG animation flush functionality
 * @tc.type: FUNC
 */
HWTEST_F(SvgContextTest, SvgContextTest012, TestSize.Level1)
{
    // Test setting animation flush function
    bool flushCalled = false;
    FuncAnimateFlush flushFunc = [&]() {
        flushCalled = true;
    };
    
    WeakPtr<CanvasImage> imagePtr;
    svgContext_->SetFuncAnimateFlush(std::move(flushFunc), imagePtr);
    
    // Test calling animate flush
    svgContext_->AnimateFlush();
    EXPECT_TRUE(flushCalled);
}

/**
 * @tc.name: SvgContextTest013
 * @tc.desc: Test SVG animation finish callback functionality
 * @tc.type: FUNC
 */
HWTEST_F(SvgContextTest, SvgContextTest013, TestSize.Level1)
{
    // Test setting finish callback
    bool callbackCalled = false;
    std::function<void()> finishCallback = [&]() {
        callbackCalled = true;
    };
    
    svgContext_->SetOnAnimationFinished(finishCallback);
    
    // Test calling animation finished
    svgContext_->OnAnimationFinished();
    EXPECT_TRUE(callbackCalled);
}

/**
 * @tc.name: SvgContextTest014
 * @tc.desc: Test SVG bounding rect calculation
 * @tc.type: FUNC
 */
HWTEST_F(SvgContextTest, SvgContextTest014, TestSize.Level1)
{
    // Create a test SVG node
    auto testNode = AceType::MakeRefPtr<SvgNode>();
    testNode->SetNodeId("testBoxNode");
    
    // Create bounding box context (mock)
    SvgLengthScaleRule boxMeasureRule;
    boxMeasureRule = SvgLengthScaleRule(); // Initialize with default values
    
    // Test getting bounding rect
    // Note: This is a basic test as the actual implementation depends on node type
    GuidelineRect boundingRect = svgContext_->GetBoundingRect(testNode, boxMeasureRule);
    // Verify that a rect is returned (specific values depend on implementation)
    EXPECT_TRUE(boundingRect.IsValid());
}

/**
 * @tc.name: SvgContextTest015
 * @tc.desc: Test SVG context destructor behavior
 * @tc.type: FUNC
 */
HWTEST_F(SvgContextTest, SvgContextTest015, TestSize.Level1)
{
    // Create SVG context with nodes
    auto tempContext = AceType::MakeRefPtr<SvgContext>();
    auto testNode = AceType::MakeRefPtr<SvgNode>();
    testNode->SetNodeId("tempTestNode");
    
    tempContext->Push("tempTestNode", testNode);
    
    // Verify node is present
    auto retrievedNode = tempContext->GetSvgNodeById("tempTestNode");
    EXPECT_NE(retrievedNode, nullptr);
    
    // Reset context (simulate destructor behavior)
    tempContext = nullptr;
    // No assertion needed - just test that destructor doesn't crash
    SUCCEED();
}

/**
 * @tc.name: SvgContextTest016
 * @tc.desc: Test multiple SVG nodes in context
 * @tc.type: FUNC
 */
HWTEST_F(SvgContextTest, SvgContextTest016, TestSize.Level1)
{
    // Create multiple SVG nodes
    std::vector<RefPtr<SvgNode>> nodes;
    for (int i = 0; i < 5; i++) {
        auto node = AceType::MakeRefPtr<SvgNode>();
        node->SetNodeId("node" + std::to_string(i));
        nodes.push_back(node);
        svgContext_->Push(node->GetNodeId(), node);
    }
    
    // Verify all nodes can be retrieved
    for (int i = 0; i < 5; i++) {
        std::string nodeId = "node" + std::to_string(i);
        auto retrievedNode = svgContext_->GetSvgNodeById(nodeId);
        EXPECT_NE(retrievedNode, nullptr);
        EXPECT_EQ(retrievedNode->GetNodeId(), nodeId);
    }
}

/**
 * @tc.name: SvgContextTest017
 * @tc.desc: Test SVG context with complex style mapping
 * @tc.type: FUNC
 */
HWTEST_F(SvgContextTest, SvgContextTest017, TestSize.Level1)
{
    // Create complex style mapping
    std::string styleName = "complexStyle";
    std::pair<std::string, std::string> attrPair1("fill", "blue");
    std::pair<std::string, std::string> attrPair2("stroke", "red");
    std::pair<std::string, std::string> attrPair3("stroke-width", "2px");
    
    svgContext_->PushStyle(styleName, attrPair1);
    svgContext_->PushStyle(styleName, attrPair2);
    svgContext_->PushStyle(styleName, attrPair3);
    
    // Verify complex style mapping
    const auto& attrMap = svgContext_->GetAttrMap(styleName);
    EXPECT_EQ(attrMap.size(), 3);
    EXPECT_EQ(attrMap.at("fill"), "blue");
    EXPECT_EQ(attrMap.at("stroke"), "red");
    EXPECT_EQ(attrMap.at("stroke-width"), "2px");
}

/**
 * @tc.name: SvgContextTest018
 * @tc.desc: Test SVG context time string functionality
 * @tc.type: FUNC
 */
HWTEST_F(SvgContextTest, SvgContextTest018, TestSize.Level1)
{
    // Test getting current time string
    std::string timeString = svgContext_->GetCurrentTimeString();
    
    // Verify time string format (basic validation)
    EXPECT_FALSE(timeString.empty());
    EXPECT_TRUE(timeString.length() > 0);
    // The exact format depends on implementation, so just check it's not empty
}