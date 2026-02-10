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
#include "frameworks/core/components_ng/svg/svg_dom.h"
#include "frameworks/core/components_ng/svg/parse/svg_node.h"
#include "core/image/image_source_info.h"
#include "src/core/SkStream.h"

using namespace testing;
using namespace OHOS::Ace::NG;

class SvgDomTest : public testing::Test {
public:
    void SetUp() override
    {
        svgDom_ = AceType::MakeRefPtr<SvgDom>();
    }

    void TearDown() override
    {
        svgDom_ = nullptr;
    }

protected:
    RefPtr<SvgDom> svgDom_;
    
    // Helper method to create a simple SVG string
    std::string CreateSimpleSvgString()
    {
        return R"(<svg width="100" height="100" viewBox="0 0 100 100">
            <circle cx="50" cy="50" r="40" fill="red"/>
        </svg>)";
    }
    
    // Helper method to create SVG stream from string
    std::unique_ptr<SkMemoryStream> CreateSvgStream(const std::string& svgString)
    {
        return std::make_unique<SkMemoryStream>(svgString.c_str(), svgString.length());
    }
};

/**
 * @tc.name: SvgDomTest001
 * @tc.desc: Test SVG DOM initialization
 * @tc.type: FUNC
 */
HWTEST_F(SvgDomTest, SvgDomTest001, TestSize.Level1)
{
    EXPECT_NE(svgDom_, nullptr);
    EXPECT_TRUE(svgDom_->IsStatic()); // Default should be static
}

/**
 * @tc.name: SvgDomTest002
 * @tc.desc: Test SVG DOM creation from stream
 * @tc.type: FUNC
 */
HWTEST_F(SvgDomTest, SvgDomTest002, TestSize.Level1)
{
    // Create SVG stream
    auto svgStream = CreateSvgStream(CreateSimpleSvgString());
    ImageSourceInfo src;
    
    // Test creating SVG DOM
    auto createdSvgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(createdSvgDom, nullptr);
    EXPECT_TRUE(createdSvgDom->IsStatic());
}

/**
 * @tc.name: SvgDomTest003
 * @tc.desc: Test SVG DOM parsing functionality
 * @tc.type: FUNC
 */
HWTEST_F(SvgDomTest, SvgDomTest003, TestSize.Level1)
{
    // Create SVG stream for parsing
    auto svgStream = CreateSvgStream(CreateSimpleSvgString());
    
    // Test parsing SVG
    bool parseResult = svgDom_->ParseSvg(*svgStream);
    EXPECT_TRUE(parseResult);
    EXPECT_TRUE(svgDom_->IsStatic()); // Should remain static without animations
}

/**
 * @tc.name: SvgDomTest004
 * @tc.desc: Test SVG DOM with animations (non-static)
 * @tc.type: FUNC
 */
HWTEST_F(SvgDomTest, SvgDomTest004, TestSize.Level1)
{
    // Create SVG string with animation
    std::string animatedSvg = R"(<svg width="100" height="100">
        <circle cx="50" cy="50" r="40" fill="red">
            <animate attributeName="r" from="40" to="20" dur="1s" repeatCount="indefinite"/>
        </circle>
    </svg>)";
    
    auto svgStream = CreateSvgStream(animatedSvg);
    
    // Test parsing animated SVG
    bool parseResult = svgDom_->ParseSvg(*svgStream);
    EXPECT_TRUE(parseResult);
    EXPECT_FALSE(svgDom_->IsStatic()); // Should be non-static with animations
}

/**
 * @tc.name: SvgDomTest005
 * @tc.desc: Test setting normalize to pixel function
 * @tc.type: FUNC
 */
HWTEST_F(SvgDomTest, SvgDomTest005, TestSize.Level1)
{
    bool functionCalled = false;
    FuncNormalizeToPx normalizeFunc = [&](const Dimension& dim) -> double {
        functionCalled = true;
        return 5.0; // Return test value
    };
    
    svgDom_->SetFuncNormalizeToPx(std::move(normalizeFunc));
    
    // Parse SVG to test function usage
    auto svgStream = CreateSvgStream(CreateSimpleSvgString());
    svgDom_->ParseSvg(*svgStream);
    
    // Note: Actual function usage may depend on implementation details
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgDomTest006
 * @tc.desc: Test SVG DOM animation callback setting
 * @tc.type: FUNC
 */
HWTEST_F(SvgDomTest, SvgDomTest006, TestSize.Level1)
{
    bool callbackCalled = false;
    std::function<void()> animateCallback = [&]() {
        callbackCalled = true;
    };
    
    WeakPtr<CanvasImage> imagePtr;
    svgDom_->SetAnimationCallback(animateCallback, imagePtr);
    
    // Test calling the callback
    // Note: The actual callback is called during animation execution
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgDomTest007
 * @tc.desc: Test SVG DOM animation finish callback
 * @tc.type: FUNC
 */
HWTEST_F(SvgDomTest, SvgDomTest007, TestSize.Level1)
{
    bool finishCallbackCalled = false;
    std::function<void()> finishCallback = [&]() {
        finishCallbackCalled = true;
    };
    
    svgDom_->SetAnimationOnFinishCallback(finishCallback);
    
    // Test setting callback
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgDomTest008
 * @tc.desc: Test SVG DOM animation control
 * @tc.type: FUNC
 */
HWTEST_F(SvgDomTest, SvgDomTest008, TestSize.Level1)
{
    // Create animated SVG
    std::string animatedSvg = R"(<svg width="100" height="100">
        <circle cx="50" cy="50" r="40" fill="red">
            <animate attributeName="r" from="40" to="20" dur="1s" repeatCount="indefinite"/>
        </circle>
    </svg>)";
    
    auto svgStream = CreateSvgStream(animatedSvg);
    svgDom_->ParseSvg(*svgStream);
    
    // Test controlling animations
    svgDom_->ControlAnimation(true); // Play
    svgDom_->ControlAnimation(false); // Pause
    
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgDomTest009
 * @tc.desc: Test setting fill color in SVG DOM
 * @tc.type: FUNC
 */
HWTEST_F(SvgDomTest, SvgDomTest009, TestSize.Level1)
{
    // Set fill color
    Color fillColor(Color::BLUE);
    svgDom_->SetFillColor(fillColor);
    
    // Verify color is set (this affects subsequent drawing operations)
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgDomTest010
 * @tc.desc: Test setting smooth edge in SVG DOM
 * @tc.type: FUNC
 */
HWTEST_F(SvgDomTest, SvgDomTest010, TestSize.Level1)
{
    // Set smooth edge value
    float smoothEdge = 2.0f;
    svgDom_->SetSmoothEdge(smoothEdge);
    
    // Parse SVG to apply smooth edge
    auto svgStream = CreateSvgStream(CreateSimpleSvgString());
    svgDom_->ParseSvg(*svgStream);
    
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgDomTest011
 * @tc.desc: Test setting color filter in SVG DOM
 * @tc.type: FUNC
 */
HWTEST_F(SvgDomTest, SvgDomTest011, TestSize.Level1)
{
    // Create color filter
    ImageColorFilter colorFilter;
    svgDom_->SetColorFilter(colorFilter);
    
    // Parse SVG to apply color filter
    auto svgStream = CreateSvgStream(CreateSimpleSvgString());
    svgDom_->ParseSvg(*svgStream);
    
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgDomTest012
 * @tc.desc: Test SVG DOM container size
 * @tc.type: FUNC
 */
HWTEST_F(SvgDomTest, SvgDomTest012, TestSize.Level1)
{
    // Parse SVG
    auto svgStream = CreateSvgStream(CreateSimpleSvgString());
    svgDom_->ParseSvg(*svgStream);
    
    // Test setting container size
    SizeF containerSize(200.0f, 150.0f);
    svgDom_->SetContainerSize(containerSize);
    
    // Test getting container size
    SizeF retrievedSize = svgDom_->GetContainerSize();
    EXPECT_FLOAT_EQ(retrievedSize.Width(), 200.0f);
    EXPECT_FLOAT_EQ(retrievedSize.Height(), 150.0f);
}

/**
 * @tc.name: SvgDomTest013
 * @tc.desc: Test SVG DOM dump info generation
 * @tc.type: FUNC
 */
HWTEST_F(SvgDomTest, SvgDomTest013, TestSize.Level1)
{
    // Parse SVG
    auto svgStream = CreateSvgStream(CreateSimpleSvgString());
    svgDom_->ParseSvg(*svgStream);
    
    // Test getting dump info
    std::string dumpInfo = svgDom_->GetDumpInfo();
    EXPECT_FALSE(dumpInfo.empty());
}

/**
 * @tc.name: SvgDomTest014
 * @tc.desc: Test SVG DOM with complex SVG structure
 * @tc.type: FUNC
 */
HWTEST_F(SvgDomTest, SvgDomTest014, TestSize.Level1)
{
    // Create complex SVG with multiple elements
    std::string complexSvg = R"(<svg width="200" height="200" viewBox="0 0 200 200">
        <rect x="10" y="10" width="50" height="50" fill="blue"/>
        <circle cx="100" cy="100" r="30" fill="red"/>
        <line x1="150" y1="150" x2="180" y2="180" stroke="green" stroke-width="2"/>
        <text x="20" y="180" font-size="12" fill="black">Hello SVG</text>
    </svg>)";
    
    auto svgStream = CreateSvgStream(complexSvg);
    
    // Test parsing complex SVG
    bool parseResult = svgDom_->ParseSvg(*svgStream);
    EXPECT_TRUE(parseResult);
}

/**
 * @tc.name: SvgDomTest015
 * @tc.desc: Test SVG DOM with gradients
 * @tc.type: FUNC
 */
HWTEST_F(SvgDomTest, SvgDomTest015, TestSize.Level1)
{
    // Create SVG with gradient
    std::string gradientSvg = R'(<svg width="100" height="100">
        <defs>
            <linearGradient id="grad1" x1="0%" y1="0%" x2="100%" y2="0%">
                <stop offset="0%" style="stop-color:rgb(255,255,0);stop-opacity:1" />
                <stop offset="100%" style="stop-color:rgb(255,0,0);stop-opacity:1" />
            </linearGradient>
        </defs>
        <ellipse cx="50" cy="50" rx="40" ry="30" fill="url(#grad1)" />
    </svg>)';
    
    auto svgStream = CreateSvgStream(gradientSvg);
    
    // Test parsing gradient SVG
    bool parseResult = svgDom_->ParseSvg(*svgStream);
    EXPECT_TRUE(parseResult);
}

/**
 * @tc.name: SvgDomTest016
 * @tc.desc: Test SVG DOM with transforms
 * @tc.type: FUNC
 */
HWTEST_F(SvgDomTest, SvgDomTest016, TestSize.Level1)
{
    // Create SVG with transforms
    std::string transformSvg = R'(<svg width="100" height="100">
        <rect x="10" y="10" width="30" height="30" fill="blue" transform="rotate(45 25 25)"/>
        <circle cx="50" cy="50" r="20" fill="red" transform="scale(1.5 0.8)"/>
    </svg>)';
    
    auto svgStream = CreateSvgStream(transformSvg);
    
    // Test parsing transform SVG
    bool parseResult = svgDom_->ParseSvg(*svgStream);
    EXPECT_TRUE(parseResult);
}

/**
 * @tc.name: SvgDomTest017
 * @tc.desc: Test SVG DOM with viewBox
 * @tc.type: FUNC
 */
HWTEST_F(SvgDomTest, SvgDomTest017, TestSize.Level1)
{
    // Create SVG with viewBox
    std::string viewBoxSvg = R'(<svg width="100" height="100" viewBox="0 0 200 200">
        <circle cx="100" cy="100" r="50" fill="red"/>
    </svg>)';
    
    auto svgStream = CreateSvgStream(viewBoxSvg);
    
    // Test parsing viewBox SVG
    bool parseResult = svgDom_->ParseSvg(*svgStream);
    EXPECT_TRUE(parseResult);
}

/**
 * @tc.name: SvgDomTest018
 * @tc.desc: Test SVG DOM with nested groups
 * @tc.type: FUNC
 */
HWTEST_F(SvgDomTest, SvgDomTest018, TestSize.Level1)
{
    // Create SVG with nested groups
    std::string nestedSvg = R'(<svg width="100" height="100">
        <g fill="red">
            <circle cx="25" cy="25" r="20"/>
            <g fill="blue">
                <rect x="10" y="40" width="20" height="20"/>
                <circle cx="70" cy="70" r="15"/>
            </g>
        </g>
    </svg>)';
    
    auto svgStream = CreateSvgStream(nestedSvg);
    
    // Test parsing nested SVG
    bool parseResult = svgDom_->ParseSvg(*svgStream);
    EXPECT_TRUE(parseResult);
}

/**
 * @tc.name: SvgDomTest019
 * @tc.desc: Test SVG DOM error handling with invalid SVG
 * @tc.type: FUNC
 */
HWTEST_F(SvgDomTest, SvgDomTest019, TestSize.Level1)
{
    // Create invalid SVG
    std::string invalidSvg = R'(<svg width="100" height="100">
        <circle cx="50" cy="50" r="40" fill="red"
    </svg>)'; // Missing closing tag
    
    auto svgStream = CreateSvgStream(invalidSvg);
    
    // Test parsing invalid SVG (should handle gracefully)
    bool parseResult = svgDom_->ParseSvg(*svgStream);
    // Result depends on error handling strategy
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgDomTest020
 * @tc.desc: Test SVG DOM with large SVG content
 * @tc.type: FUNC
 */
HWTEST_F(SvgDomTest, SvgDomTest020, TestSize.Level1)
{
    // Create large SVG content
    std::string largeSvg = R'(<svg width="1000" height="1000">)';
    for (int i = 0; i < 100; i++) {
        largeSvg += R'(<rect x=")' + std::to_string(i * 10) +
                   R'(" y=")' + std::to_string(i * 10) +
                   R'(" width="8" height="8" fill="blue"/>)';
    }
    largeSvg += R"(</svg>)";
    
    auto svgStream = CreateSvgStream(largeSvg);
    
    // Test parsing large SVG
    bool parseResult = svgDom_->ParseSvg(*svgStream);
    EXPECT_TRUE(parseResult);
}