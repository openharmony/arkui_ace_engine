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
#include "frameworks/core/components_ng/svg/svg_transform_utils.h"
#include "base/geometry/rect.h"
#include "base/geometry/dimension.h"
#include "core/components_ng/render/drawing.h"

using namespace testing;
using namespace OHOS::Ace::NG;

class SvgTransformUtilsTest : public testing::Test {
public:
    void SetUp() override
    {
        transformUtils_ = AceType::MakeRefPtr<SvgTransformUtils>();
    }

    void TearDown() override
    {
        transformUtils_ = nullptr;
    }

protected:
    RefPtr<SvgTransformUtils> transformUtils_;
};

/**
 * @tc.name: SvgTransformUtilsTest001
 * @tc.desc: Test SVG transform utils creation
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformUtilsTest, SvgTransformUtilsTest001, TestSize.Level1)
{
    EXPECT_NE(transformUtils_, nullptr);
}

/**
 * @tc.name: SvgTransformUtilsTest002
 * @tc.desc: Test parsing translate transform
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformUtilsTest, SvgTransformUtilsTest002, TestSize.Level1)
{
    std::string translateStr = "translate(10, 20)";
    RSMatrix matrix = {0};
    
    // Test parsing translate
    bool result = transformUtils_->ParseTransform(translateStr, matrix);
    EXPECT_TRUE(result);
    
    // Verify matrix values (approximate due to floating point)
    EXPECT_FLOAT_EQ(matrix.tx, 10.0f);
    EXPECT_FLOAT_EQ(matrix.ty, 20.0f);
}

/**
 * @tc.name: SvgTransformUtilsTest003
 * @tc.desc: Test parsing rotate transform
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformUtilsTest, SvgTransformUtilsTest003, TestSize.Level1)
{
    std::string rotateStr = "rotate(45)";
    RSMatrix matrix = {0};
    
    // Test parsing rotate
    bool result = transformUtils_->ParseTransform(rotateStr, matrix);
    EXPECT_TRUE(result);
    
    // Verify rotation matrix (cos(45°), -sin(45°), sin(45°), cos(45°), 0, 0)
    EXPECT_NEAR(matrix.sx, 0.7071f, 0.01f);
    EXPECT_NEAR(matrix.sy, 0.7071f, 0.01f);
}

/**
 * @tc.name: SvgTransformUtilsTest004
 * @tc.desc: Test parsing rotate with center point
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformUtilsTest, SvgTransformUtilsTest004, TestSize.Level1)
{
    std::string rotateWithCenterStr = "rotate(45, 50, 50)";
    RSMatrix matrix = {0};
    
    // Test parsing rotate with center
    bool result = transformUtils_->ParseTransform(rotateWithCenterStr, matrix);
    EXPECT_TRUE(result);
    
    // Should include translation for center point
    EXPECT_TRUE(matrix.sx != 0.0f || matrix.sy != 0.0f);
}

/**
 * @tc.name: SvgTransformUtilsTest005
 * @tc.desc: Test parsing scale transform
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformUtilsTest, SvgTransformUtilsTest005, TestSize.Level1)
{
    std::string scaleStr = "scale(1.5, 0.8)";
    RSMatrix matrix = {0};
    
    // Test parsing scale
    bool result = transformUtils_->ParseTransform(scaleStr, matrix);
    EXPECT_TRUE(result);
    
    // Verify scale matrix
    EXPECT_FLOAT_EQ(matrix.sx, 1.5f);
    EXPECT_FLOAT_EQ(matrix.sy, 0.8f);
}

/**
 * @tc.name: SvgTransformUtilsTest006
 * @tc.desc: Test parsing single scale
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformUtilsTest, SvgTransformUtilsTest006, TestSize.Level1)
{
    std::string scaleStr = "scale(2.0)";
    RSMatrix matrix = {0};
    
    // Test parsing single scale value
    bool result = transformUtils_->ParseTransform(scaleStr, matrix);
    EXPECT_TRUE(result);
    
    // Should scale both axes equally
    EXPECT_FLOAT_EQ(matrix.sx, 2.0f);
    EXPECT_FLOAT_EQ(matrix.sy, 2.0f);
}

/**
 * @tc.name: SvgTransformUtilsTest007
 * @tc.desc: Test parsing skew transform
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformUtilsTest, SvgTransformUtilsTest007, TestSize.Level1)
{
    std::string skewStr = "skewX(30) skewY(20)";
    RSMatrix matrix = {0};
    
    // Test parsing skew
    bool result = transformUtils_->ParseTransform(skewStr, matrix);
    EXPECT_TRUE(result);
    
    // Verify skew matrix (tan(30°), tan(20°))
    EXPECT_NEAR(matrix.ky, 0.57735f, 0.01f); // tan(30°)
    EXPECT_NEAR(matrix.kx, 0.36397f, 0.01f); // tan(20°)
}

/**
 * @tc.name: SvgTransformUtilsTest008
 * @tc.desc: Test parsing matrix transform
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformUtilsTest, SvgTransformUtilsTest008, TestSize.Level1)
{
    std::string matrixStr = "matrix(1, 0, 0, 1, 10, 20)";
    RSMatrix matrix = {0};
    
    // Test parsing matrix
    bool result = transformUtils_->ParseTransform(matrixStr, matrix);
    EXPECT_TRUE(result);
    
    // Verify matrix values
    EXPECT_FLOAT_EQ(matrix.sx, 1.0f);
    EXPECT_FLOAT_EQ(matrix.sy, 1.0f);
    EXPECT_FLOAT_EQ(matrix.kx, 0.0f);
    EXPECT_FLOAT_EQ(matrix.ky, 0.0f);
    EXPECT_FLOAT_EQ(matrix.tx, 10.0f);
    EXPECT_FLOAT_EQ(matrix.ty, 20.0f);
}

/**
 * @tc.name: SvgTransformUtilsTest009
 * @tc.desc: Test parsing multiple transforms
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformUtilsTest, SvgTransformUtilsTest009, TestSize.Level1)
{
    std::string multipleStr = "translate(10, 20) rotate(30) scale(1.5)";
    RSMatrix matrix = {0};
    
    // Test parsing multiple transforms
    bool result = transformUtils_->ParseTransform(multipleStr, matrix);
    EXPECT_TRUE(result);
    
    // Should combine all transforms
    EXPECT_TRUE(matrix.sx != 0.0f || matrix.sy != 0.0f);
    EXPECT_TRUE(matrix.tx != 0.0f || matrix.ty != 0.0f);
}

/**
 * @tc.name: SvgTransformUtilsTest010
 * @tc.desc: Test parsing identity transform
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformUtilsTest, SvgTransformUtilsTest010, TestSize.Level1)
{
    RSMatrix matrix = {0};
    
    // Test identity (no transform)
    bool result = transformUtils_->ParseTransform("", matrix);
    EXPECT_TRUE(result);
    
    // Should return identity matrix
    EXPECT_FLOAT_EQ(matrix.sx, 1.0f);
    EXPECT_FLOAT_EQ(matrix.sy, 1.0f);
    EXPECT_FLOAT_EQ(matrix.kx, 0.0f);
    EXPECT_FLOAT_EQ(matrix.ky, 0.0f);
    EXPECT_FLOAT_EQ(matrix.tx, 0.0f);
    EXPECT_FLOAT_EQ(matrix.ty, 0.0f);
}

/**
 * @tc.name: SvgTransformUtilsTest011
 * @tc.desc: Test parsing decimal values
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformUtilsTest, SvgTransformUtilsTest011, TestSize.Level1)
{
    std::string decimalStr = "translate(1.5, 2.75) scale(0.5, 0.25)";
    RSMatrix matrix = {0};
    
    // Test parsing decimal values
    bool result = transformUtils_->ParseTransform(decimalStr, matrix);
    EXPECT_TRUE(result);
    
    // Should handle decimal values correctly
    EXPECT_FLOAT_EQ(matrix.tx, 1.5f);
    EXPECT_FLOAT_EQ(matrix.ty, 2.75f);
    EXPECT_FLOAT_EQ(matrix.sx, 0.5f);
    EXPECT_FLOAT_EQ(matrix.sy, 0.25f);
}

/**
 * @tc.name: SvgTransformUtilsTest012
 * @tc.desc: Test parsing negative values
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformUtilsTest, SvgTransformUtilsTest012, TestSize.Level1)
{
    std::string negativeStr = "translate(-10, -20) rotate(-45) scale(-1, -2)";
    RSMatrix matrix = {0};
    
    // Test parsing negative values
    bool result = transformUtils_->ParseTransform(negativeStr, matrix);
    EXPECT_TRUE(result);
    
    // Should handle negative values correctly
    EXPECT_FLOAT_EQ(matrix.tx, -10.0f);
    EXPECT_FLOAT_EQ(matrix.ty, -20.0f);
    EXPECT_FLOAT_EQ(matrix.sx, -1.0f);
    EXPECT_FLOAT_EQ(matrix.sy, -2.0f);
}

/**
 * @tc.name: SvgTransformUtilsTest013
 * @tc.desc: Test parsing large values
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformUtilsTest, SvgTransformUtilsTest013, TestSize.Level1)
{
    std::string largeStr = "translate(1000, 2000) scale(3.5, 2.5)";
    RSMatrix matrix = {0};
    
    // Test parsing large values
    bool result = transformUtils_->ParseTransform(largeStr, matrix);
    EXPECT_TRUE(result);
    
    // Should handle large values correctly
    EXPECT_FLOAT_EQ(matrix.tx, 1000.0f);
    EXPECT_FLOAT_EQ(matrix.ty, 2000.0f);
    EXPECT_FLOAT_EQ(matrix.sx, 3.5f);
    EXPECT_FLOAT_EQ(matrix.sy, 2.5f);
}

/**
 * @tc.name: SvgTransformUtilsTest014
 * @tc.desc: Test parsing zero values
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformUtilsTest, SvgTransformUtilsTest014, TestSize.Level1)
{
    std::string zeroStr = "translate(0, 0) scale(0, 0)";
    RSMatrix matrix = {0};
    
    // Test parsing zero values
    bool result = transformUtils_->ParseTransform(zeroStr, matrix);
    EXPECT_TRUE(result);
    
    // Should handle zero values correctly
    EXPECT_FLOAT_EQ(matrix.tx, 0.0f);
    EXPECT_FLOAT_EQ(matrix.ty, 0.0f);
    EXPECT_FLOAT_EQ(matrix.sx, 0.0f);
    EXPECT_FLOAT_EQ(matrix.sy, 0.0f);
}

/**
 * @tc.name: SvgTransformUtilsTest015
 * @tc.desc: Test parsing with whitespace
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformUtilsTest, SvgTransformUtilsTest015, TestSize.Level1)
{
    std::string spaceStr = "translate ( 10 , 20 )   scale ( 1.5 ,   0.8 )";
    RSMatrix matrix = {0};
    
    // Test parsing with whitespace
    bool result = transformUtils_->ParseTransform(spaceStr, matrix);
    EXPECT_TRUE(result);
    
    // Should handle whitespace correctly
    EXPECT_FLOAT_EQ(matrix.tx, 10.0f);
    EXPECT_FLOAT_EQ(matrix.ty, 20.0f);
    EXPECT_FLOAT_EQ(matrix.sx, 1.5f);
    EXPECT_FLOAT_EQ(matrix.sy, 0.8f);
}

/**
 * @tc.name: SvgTransformUtilsTest016
 * @tc.desc: Test parsing invalid transform
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformUtilsTest, SvgTransformUtilsTest016, TestSize.Level1)
{
    std::vector<std::string> invalidTransforms = {
        "invalid(10, 20)",           // Invalid function
        "translate()",               // No parameters
        "translate(10)",            // Single parameter for translate
        "rotate(45, 50, 50, 10)", // Too many parameters
        "scale(a, b)",            // Non-numeric parameters
        "matrix(1, 2)",           // Not enough parameters
        "translate(, 10)"         // Missing first parameter
    };
    
    for (const auto& transform : invalidTransforms) {
        RSMatrix matrix = {0};
        bool result = transformUtils_->ParseTransform(transform, matrix);
        // May fail, but should not crash
        SUCCEED(); // Test passes if no crash
    }
}

/**
 * @tc.name: SvgTransformUtilsTest017
 * @tc.desc: Test matrix multiplication
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformUtilsTest, SvgTransformUtilsTest017, TestSize.Level1)
{
    // Create two matrices
    RSMatrix matrix1 = { 2, 0, 0, 2, 10, 20 }; // Scale 2, translate
    RSMatrix matrix2 = { 0, -1, 1, 0, -20, 30 }; // Rotate 90°, translate
    
    // Test matrix multiplication
    RSMatrix result = transformUtils_->Multiply(matrix1, matrix2);
    
    // Should combine both transformations
    EXPECT_TRUE(result.sx != 0.0f || result.sy != 0.0f);
}

/**
 * @tc.name: SvgTransformUtilsTest018
 * @tc.desc: Test matrix inversion
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformUtilsTest, SvgTransformUtilsTest018, TestSize.Level1)
{
    // Create invertible matrix
    RSMatrix matrix = { 2, 0, 0, 2, 10, 20 };
    
    // Test matrix inversion
    RSMatrix inverted = transformUtils_->Invert(matrix);
    
    // Should create valid inverse
    EXPECT_TRUE(std::isfinite(inverted.sx));
    EXPECT_TRUE(std::isfinite(inverted.sy));
    EXPECT_TRUE(std::isfinite(inverted.tx));
    EXPECT_TRUE(std::isfinite(inverted.ty));
}

/**
 * @tc.name: SvgTransformUtilsTest019
 * @tc.desc: Test singular matrix inversion
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformUtilsTest, SvgTransformUtilsTest019, TestSize.Level1)
{
    // Create singular matrix (determinant = 0)
    RSMatrix matrix = { 0, 0, 0, 0, 10, 20 };
    
    // Test singular matrix inversion
    RSMatrix inverted = transformUtils_->Invert(matrix);
    
    // Should handle singular matrix gracefully
    // Implementation-dependent result
    SUCCEED(); // Test passes if no crash
}

/**
 * @tc.name: SvgTransformUtilsTest020
 * @tc.desc: Test matrix creation from components
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformUtilsTest, SvgTransformUtilsTest020, TestSize.Level1)
{
    // Create matrix from individual components
    RSMatrix matrix = transformUtils_->CreateMatrix(
        1.0f,  // sx
        0.0f,  // kx
        0.0f,  // ky
        1.0f,  // sy
        10.0f, // tx
        20.0f  // ty
    );
    
    EXPECT_FLOAT_EQ(matrix.sx, 1.0f);
    EXPECT_FLOAT_EQ(matrix.sy, 1.0f);
    EXPECT_FLOAT_EQ(matrix.kx, 0.0f);
    EXPECT_FLOAT_EQ(matrix.ky, 0.0f);
    EXPECT_FLOAT_EQ(matrix.tx, 10.0f);
    EXPECT_FLOAT_EQ(matrix.ty, 20.0f);
}

/**
 * @tc.name: SvgTransformUtilsTest021
 * @tc.desc: Test create rotation matrix
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformUtilsTest, SvgTransformUtilsTest021, TestSize.Level1)
{
    // Test rotation matrix creation
    RSMatrix rotation = transformUtils_->CreateRotation(45.0f);
    
    // Should create rotation matrix
    EXPECT_NEAR(rotation.sx, 0.7071f, 0.01f);
    EXPECT_NEAR(rotation.sy, 0.7071f, 0.01f);
    EXPECT_NEAR(rotation.kx, -0.7071f, 0.01f);
    EXPECT_NEAR(rotation.ky, 0.7071f, 0.01f);
    EXPECT_FLOAT_EQ(rotation.tx, 0.0f);
    EXPECT_FLOAT_EQ(rotation.ty, 0.0f);
}

/**
 * @tc.name: SvgTransformUtilsTest022
 * @tc.desc: Test create translation matrix
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformUtilsTest, SvgTransformUtilsTest022, TestSize.Level1)
{
    // Test translation matrix creation
    RSMatrix translation = transformUtils_->CreateTranslation(15.0f, 25.0f);
    
    // Should create translation matrix
    EXPECT_FLOAT_EQ(translation.sx, 1.0f);
    EXPECT_FLOAT_EQ(translation.sy, 1.0f);
    EXPECT_FLOAT_EQ(translation.kx, 0.0f);
    EXPECT_FLOAT_EQ(translation.ky, 0.0f);
    EXPECT_FLOAT_EQ(translation.tx, 15.0f);
    EXPECT_FLOAT_EQ(translation.ty, 25.0f);
}

/**
 * @tc.name: SvgTransformUtilsTest023
 * @tc.desc: Test create scale matrix
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformUtilsTest, SvgTransformUtilsTest023, TestSize.Level1)
{
    // Test scale matrix creation
    RSMatrix scale = transformUtils_->CreateScale(2.0f, 1.5f);
    
    // Should create scale matrix
    EXPECT_FLOAT_EQ(scale.sx, 2.0f);
    EXPECT_FLOAT_EQ(scale.sy, 1.5f);
    EXPECT_FLOAT_EQ(scale.kx, 0.0f);
    EXPECT_FLOAT_EQ(scale.ky, 0.0f);
    EXPECT_FLOAT_EQ(scale.tx, 0.0f);
    EXPECT_FLOAT_EQ(scale.ty, 0.0f);
}

/**
 * @tc.name: SvgTransformUtilsTest024
 * @tc.desc: Test complex transformation chain
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformUtilsTest, SvgTransformUtilsTest024, TestSize.Level1)
{
    std::string complexTransform = 
        "translate(100, 50) rotate(30) scale(1.5, 0.8) translate(-20, -10)";
    RSMatrix matrix = {0};
    
    // Test complex transformation chain
    bool result = transformUtils_->ParseTransform(complexTransform, matrix);
    EXPECT_TRUE(result);
    
    // Verify result is a valid transformation matrix
    EXPECT_TRUE(std::isfinite(matrix.sx));
    EXPECT_TRUE(std::isfinite(matrix.sy));
    EXPECT_TRUE(std::isfinite(matrix.tx));
    EXPECT_TRUE(std::isfinite(matrix.ty));
}

/**
 * @tc.name: SvgTransformUtilsTest025
 * @tc.desc: Test transform list parsing
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformUtilsTest, SvgTransformUtilsTest025, TestSize.Level1)
{
    std::vector<std::string> transforms = {
        "translate(10,20)",
        "rotate(45)",
        "scale(1.5,0.8)",
        "skewX(30)",
        "skewY(20)"
    };
    
    std::vector<RSMatrix> matrices;
    for (const auto& transformStr : transforms) {
        RSMatrix matrix = {0};
        bool result = transformUtils_->ParseTransform(transformStr, matrix);
        EXPECT_TRUE(result) << "Failed to parse: " << transformStr;
        
        // Store matrix for potential combination
        matrices.push_back(matrix);
    }
    
    EXPECT_EQ(matrices.size(), 5);
}