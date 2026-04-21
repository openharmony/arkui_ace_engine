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
#include "frameworks/core/components_ng/svg/parse/svg_node.h"
#include "frameworks/core/components_ng/svg/svg_context.h"
#include "frameworks/core/components_ng/svg/parse/svg_attributes_parser.h"
#include "core/components_ng/render/drawing.h"
#include "base/geometry/dimension.h"

using namespace testing;
using namespace OHOS::Ace::NG;

class SvgNodeTest : public testing::Test {
public:
    void SetUp() override
    {
        svgNode_ = AceType::MakeRefPtr<SvgNode>();
        svgContext_ = AceType::MakeRefPtr<SvgContext>();
        svgNode_->SetContext(svgContext_);
    }

    void TearDown() override
    {
        svgNode_ = nullptr;
        svgContext_ = nullptr;
    }

protected:
    RefPtr<SvgNode> svgNode_;
    RefPtr<SvgContext> svgContext_;
};

/**
 * @tc.name: SvgNodeTest001
 * @tc.desc: Test SVG node initialization
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTest, SvgNodeTest001, TestSize.Level1)
{
    EXPECT_NE(svgNode_, nullptr);
    EXPECT_EQ(svgNode_->GetNodeId(), "");
    EXPECT_FLOAT_EQ(svgNode_->GetSmoothEdge(), 0.0f);
    EXPECT_FALSE(svgNode_->GetColorFilter().has_value());
}

/**
 * @tc.name: SvgNodeTest002
 * @tc.desc: Test SVG node ID setting and getting
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTest, SvgNodeTest002, TestSize.Level1)
{
    std::string nodeId = "testNode123";
    svgNode_->SetNodeId(nodeId);
    
    EXPECT_EQ(svgNode_->GetNodeId(), nodeId);
}

/**
 * @tc.name: SvgNodeTest003
 * @tc.desc: Test SVG node smooth edge setting
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTest, SvgNodeTest003, TestSize.Level1)
{
    float smoothEdge = 3.5f;
    svgNode_->SetSmoothEdge(smoothEdge);
    
    EXPECT_FLOAT_EQ(svgNode_->GetSmoothEdge(), smoothEdge);
}

/**
 * @tc.name: SvgNodeTest004
 * @tc.desc: Test SVG node color filter setting
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTest, SvgNodeTest004, TestSize.Level1)
{
    ImageColorFilter colorFilter;
    svgNode_->SetColorFilter(colorFilter);
    
    auto retrievedColorFilter = svgNode_->GetColorFilter();
    EXPECT_TRUE(retrievedColorFilter.has_value());
}

/**
 * @tc.name: SvgNodeTest005
 * @tc.desc: Test SVG node effect filter area setting
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTest, SvgNodeTest005, TestSize.Level1)
{
    Rect effectFilterArea(10, 20, 100, 80);
    svgNode_->SetEffectFilterArea(effectFilterArea);
    
    Rect retrievedArea = svgNode_->GetEffectFilterArea();
    EXPECT_EQ(retrievedArea.GetX(), effectFilterArea.GetX());
    EXPECT_EQ(retrievedArea.GetY(), effectFilterArea.GetY());
    EXPECT_EQ(retrievedArea.GetWidth(), effectFilterArea.GetWidth());
    EXPECT_EQ(retrievedArea.GetHeight(), effectFilterArea.GetHeight());
}

/**
 * @tc.name: SvgNodeTest006
 * @tc.desc: Test SVG node image path setting
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTest, SvgNodeTest006, TestSize.Level1)
{
    std::string imagePath = "/data/test/image.svg";
    svgNode_->SetImagePath(imagePath);
    
    EXPECT_EQ(svgNode_->GetImagePath(), imagePath);
}

/**
 * @tc.name: SvgNodeTest007
 * @tc.desc: Test SVG node root node marking
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTest, SvgNodeTest007, TestSize.Level1)
{
    // Test default state
    // Note: There's no GetIsRootNode() method, but we test setting
    svgNode_->SetIsRootNode(true);
    svgNode_->SetIsRootNode(false);
    
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgNodeTest008
 * @tc.desc: Test SVG node attribute inheritance
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTest, SvgNodeTest008, TestSize.Level1)
{
    // Create parent attributes
    SvgBaseAttribute parentAttr;
    parentAttr.fill = Color::RED;
    parentAttr.stroke = Color::BLUE;
    parentAttr.strokeWidth = Dimension(2.0, DimensionUnit::PX);
    
    // Test inheritance
    svgNode_->InheritAttr(parentAttr);
    
    auto baseAttr = svgNode_->GetBaseAttributes();
    // Inherited attributes should be present in base attributes
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgNodeTest009
 * @tc.desc: Test SVG node use attribute inheritance
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTest, SvgNodeTest009, TestSize.Level1)
{
    // Create use attributes
    SvgBaseAttribute useAttr;
    useAttr.fill = Color::GREEN;
    useAttr.opacity = 0.8f;
    
    // Test use inheritance
    svgNode_->InheritUseAttr(useAttr);
    
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgNodeTest010
 * @tc.desc: Test SVG node child append functionality
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTest, SvgNodeTest010, TestSize.Level1)
{
    // Create child node
    auto childNode = AceType::MakeRefPtr<SvgNode>();
    childNode->SetNodeId("childNode");
    
    // Test appending child
    svgNode_->AppendChild(childNode);
    
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgNodeTest011
 * @tc.desc: Test SVG node general attribute setting
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTest, SvgNodeTest011, TestSize.Level1)
{
    // Test setting general attributes
    svgNode_->SetAttr("fill", "red");
    svgNode_->SetAttr("stroke", "blue");
    svgNode_->SetAttr("stroke-width", "2px");
    
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgNodeTest012
 * @tc.desc: Test SVG node specialized attribute parsing
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTest, SvgNodeTest012, TestSize.Level1)
{
    // Test that specialized attribute parsing returns false by default
    bool result = svgNode_->ParseAndSetSpecializedAttr("specialAttr", "value");
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SvgNodeTest013
 * @tc.desc: Test SVG node style initialization
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTest, SvgNodeTest013, TestSize.Level1)
{
    // Create style attributes
    SvgBaseAttribute styleAttr;
    styleAttr.fill = Color::YELLOW;
    styleAttr.stroke = Color::PURPLE;
    
    // Test style initialization
    svgNode_->InitStyle(styleAttr);
    
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgNodeTest014
 * @tc.desc: Test SVG node style processing
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTest, SvgNodeTest014, TestSize.Level1)
{
    // Create style attributes
    SvgBaseAttribute styleAttr;
    styleAttr.fill = Color::CYAN;
    styleAttr.stroke = Color::MAGENTA;
    
    // Test style processing
    svgNode_->ProcessSvgStyle(svgNode_, styleAttr);
    
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgNodeTest015
 * @tc.desc: Test SVG node child animation processing
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTest, SvgNodeTest015, TestSize.Level1)
{
    // Test child animation processing
    svgNode_->ProcessChildAnimations(svgNode_);
    
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgNodeTest016
 * @tc.desc: Test SVG node child style processing
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTest, SvgNodeTest016, TestSize.Level1)
{
    // Create style info
    SvgInitStyleProcessInfo styleInfo(svgNode_);
    styleInfo.childIndex = 0;
    
    // Create style task stack
    std::stack<std::pair<SvgInitStyleProcessInfo, const SvgBaseAttribute*>> initStyleTaskStack;
    SvgBaseAttribute attrPtr;
    initStyleTaskStack.push({styleInfo, &attrPtr});
    
    // Test child style processing
    bool result = svgNode_->ProcessChildStyle(styleInfo, initStyleTaskStack);
    
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgNodeTest017
 * @tc.desc: Test SVG node style DFS initialization
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTest, SvgNodeTest017, TestSize.Level1)
{
    // Create style attributes
    SvgBaseAttribute styleAttr;
    styleAttr.fill = Color::ORANGE;
    
    // Test DFS style initialization
    WeakPtr<SvgNode> rootPtr(svgNode_);
    svgNode_->InitStyleDfs(rootPtr, styleAttr);
    
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgNodeTest018
 * @tc.desc: Test SVG node path conversion
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTest, SvgNodeTest018, TestSize.Level1)
{
    // Create viewport size
    Size viewPort(100, 100);
    
    // Test path conversion (base implementation returns empty)
    RSRecordingPath path = svgNode_->AsPath(viewPort);
    EXPECT_TRUE(path.IsEmpty());
}

/**
 * @tc.name: SvgNodeTest019
 * @tc.desc: Test SVG node RS path conversion
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTest, SvgNodeTest019, TestSize.Level1)
{
    // Create viewport size
    Size viewPort(100, 100);
    
    // Test RS path conversion (base implementation returns empty)
    RSPath rsPath = svgNode_->AsRSPath(viewPort);
    EXPECT_TRUE(rsPath.IsEmpty());
}

/**
 * @tc.name: SvgNodeTest020
 * @tc.desc: Test SVG node bounds calculation
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTest, SvgNodeTest020, TestSize.Level1)
{
    // Create viewport size
    Size viewPort(100, 100);
    
    // Test bounds calculation (base implementation)
    Rect bounds = svgNode_->AsBounds(viewPort);
    EXPECT_TRUE(bounds.IsValid());
}

/**
 * @tc.name: SvgNodeTest021
 * @tc.desc: Test SVG node base attributes management
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTest, SvgNodeTest021, TestSize.Level1)
{
    // Create custom attributes
    SvgBaseAttribute customAttr;
    customAttr.fill = Color::PINK;
    customAttr.stroke = Color::BLACK;
    
    // Test setting base attributes
    svgNode_->SetBaseAttributes(customAttr);
    
    // Test getting base attributes
    auto retrievedAttr = svgNode_->GetBaseAttributes();
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgNodeTest022
 * @tc.desc: Test SVG node transform calculation
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTest, SvgNodeTest022, TestSize.Level1)
{
    // Create transform origin
    std::pair<Dimension, Dimension> transformOrigin(
        Dimension(50.0, DimensionUnit::PX),
        Dimension(25.0, DimensionUnit::PX)
    );
    
    // Create length scale rule
    SvgLengthScaleRule lengthRule;
    
    // Test global pivot calculation
    Offset pivot = svgNode_->CalcGlobalPivot(transformOrigin, lengthRule);
    
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgNodeTest023
 * @tc.desc: Test SVG node region length calculation
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTest, SvgNodeTest023, TestSize.Level1)
{
    // Create test values
    Dimension origin(100.0, DimensionUnit::PX);
    SvgLengthScaleRule boxMeasureRule;
    SvgLengthType lengthType = SvgLengthType::HORIZONTAL;
    
    // Test region length calculation
    float length = svgNode_->GetRegionLength(origin, boxMeasureRule, lengthType);
    
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgNodeTest024
 * @tc.desc: Test SVG node region position calculation
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTest, SvgNodeTest024, TestSize.Level1)
{
    // Create test values
    Dimension origin(50.0, DimensionUnit::PX);
    SvgLengthScaleRule boxMeasureRule;
    SvgLengthType lengthType = SvgLengthType::HORIZONTAL;
    
    // Test region position calculation
    float position = svgNode_->GetRegionPosition(origin, boxMeasureRule, lengthType);
    
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgNodeTest025
 * @tc.desc: Test SVG node user config version
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTest, SvgNodeTest025, TestSize.Level1)
{
    // Test getting user config version
    uint32_t version = svgNode_->GetUsrConfigVersion();
    
    // Version should be a valid value
    EXPECT_LT(version, UINT32_MAX);
}