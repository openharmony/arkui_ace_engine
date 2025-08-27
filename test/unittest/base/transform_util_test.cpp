/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "base/geometry/transform_util.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
const double NUM_D1 = 1.0;
const double NUM_D2 = 0.0;
const float PROGRESS = 0.5f;
} // namespace

class TransformUtilTest : public testing::Test {};

/**
 * @tc.name: TransformUtilTest001
 * @tc.desc: Test the functions of the class TranslateOperation.
 * @tc.type: FUNC
 */
HWTEST_F(TransformUtilTest, TransformUtilTest001, TestSize.Level1)
{
    Dimension dimension(NUM_D1);
    TranslateOperation to(dimension, dimension, dimension);
    TranslateOperation from(dimension, dimension, dimension);
    TranslateOperation result = TranslateOperation::Blend(to, from, PROGRESS);
    EXPECT_EQ(result, to);
}

/**
 * @tc.name: TransformUtilTest002
 * @tc.desc: Test the functions of the class ScaleOperation.
 * @tc.type: FUNC
 */
HWTEST_F(TransformUtilTest, TransformUtilTest002, TestSize.Level1)
{
    ScaleOperation to(NUM_D1, NUM_D1, NUM_D1);
    ScaleOperation from(NUM_D1, NUM_D1, NUM_D1);
    ScaleOperation result = ScaleOperation::Blend(to, from, PROGRESS);
    EXPECT_EQ(result, to);
}

/**
 * @tc.name: TransformUtilTest003
 * @tc.desc: Test the functions of the class SkewOperation.
 * @tc.type: FUNC
 */
HWTEST_F(TransformUtilTest, TransformUtilTest003, TestSize.Level1)
{
    SkewOperation to(NUM_D1, NUM_D1);
    SkewOperation from(NUM_D1, NUM_D1);
    SkewOperation result = SkewOperation::Blend(to, from, PROGRESS);
    EXPECT_EQ(result, to);
}

/**
 * @tc.name: TransformUtilTest004
 * @tc.desc: Test the functions of the class RotateOperation.
 * @tc.type: FUNC
 */
HWTEST_F(TransformUtilTest, TransformUtilTest004, TestSize.Level1)
{
    RotateOperation to(NUM_D1, NUM_D1, NUM_D1, NUM_D1);
    RotateOperation from(NUM_D1, NUM_D1, NUM_D1, NUM_D1);
    RotateOperation result = RotateOperation::Blend(to, from, PROGRESS);
    EXPECT_EQ(result, to);

    to = RotateOperation(NUM_D2, NUM_D2, NUM_D2, NUM_D1);
    from = RotateOperation(NUM_D1, NUM_D1, NUM_D1, NUM_D1);
    result = RotateOperation::Blend(to, from, PROGRESS);
    EXPECT_EQ(result, from);
}

/**
 * @tc.name: TransformUtilTest005
 * @tc.desc: Test the functions of the class PerspectiveOperation.
 * @tc.type: FUNC
 */
HWTEST_F(TransformUtilTest, TransformUtilTest005, TestSize.Level1)
{
    Dimension dimension(NUM_D1);
    PerspectiveOperation to(dimension);
    PerspectiveOperation from(dimension);
    PerspectiveOperation result = PerspectiveOperation::Blend(to, from, PROGRESS);
    EXPECT_EQ(result, to);
}

/**
 * @tc.name: TransformUtilTest006
 * @tc.desc: Test the functions of the class TransformOperation.
 * @tc.type: FUNC
 */
HWTEST_F(TransformUtilTest, TransformUtilTest006, TestSize.Level1)
{
    TransformOperation result;
    TransformOperation to = TransformOperation::Create(TransformOperationType::UNDEFINED);
    TransformOperation from = TransformOperation::Create(TransformOperationType::UNDEFINED);
    result = TransformOperation::Blend(to, from, PROGRESS);
    EXPECT_EQ(result.matrix4_, Matrix4::CreateIdentity());
    from = TransformOperation::Create(TransformOperationType::TRANSLATE);
    result = TransformOperation::Blend(to, from, PROGRESS);
    EXPECT_EQ(result.type_, TransformOperationType::TRANSLATE);
    EXPECT_EQ(result.translateOperation_, TranslateOperation());
    result = TransformOperation::Blend(from, to, PROGRESS);
    EXPECT_EQ(result.type_, TransformOperationType::TRANSLATE);
    EXPECT_EQ(result.translateOperation_, TranslateOperation());
    result = TransformOperation::Blend(from, from, PROGRESS);
    EXPECT_EQ(result.type_, TransformOperationType::TRANSLATE);
    EXPECT_EQ(result.translateOperation_, TranslateOperation());

    from = TransformOperation::Create(TransformOperationType::SCALE);
    result = TransformOperation::Blend(to, from, PROGRESS);
    EXPECT_EQ(result.type_, TransformOperationType::SCALE);
    EXPECT_EQ(result.scaleOperation_, ScaleOperation());

    from = TransformOperation::Create(TransformOperationType::SKEW);
    result = TransformOperation::Blend(to, from, PROGRESS);
    EXPECT_EQ(result.type_, TransformOperationType::SKEW);
    EXPECT_EQ(result.skewOperation_, SkewOperation());

    from = TransformOperation::Create(TransformOperationType::ROTATE);
    result = TransformOperation::Blend(to, from, PROGRESS);
    EXPECT_EQ(result.type_, TransformOperationType::ROTATE);
    EXPECT_EQ(result.rotateOperation_, RotateOperation());

    from = TransformOperation::Create(TransformOperationType::MATRIX);
    result = TransformOperation::Blend(to, from, PROGRESS);
    EXPECT_EQ(result.type_, TransformOperationType::MATRIX);
    EXPECT_EQ(result.matrix4_, Matrix4::CreateIdentity());

    from = TransformOperation::Create(TransformOperationType::PERSPECTIVE);
    result = TransformOperation::Blend(to, from, PROGRESS);
    EXPECT_EQ(result.type_, TransformOperationType::PERSPECTIVE);
    EXPECT_EQ(result.perspectiveOperation_, PerspectiveOperation());
}

/**
 * @tc.name: TransformUtilTest007
 * @tc.desc: Test the function ToString of the class DecomposedTransform.
 * @tc.type: FUNC
 */
HWTEST_F(TransformUtilTest, TransformUtilTest007, TestSize.Level1)
{
    DecomposedTransform decomposedTransform;
    std::string resStr;
    resStr.append("translate: ")
        .append(std::to_string(0.0f))
        .append(" ")
        .append(std::to_string(0.0f))
        .append(" ")
        .append(std::to_string(0.0f))
        .append("\n")
        .append("scale: ")
        .append(std::to_string(1.0f))
        .append(" ")
        .append(std::to_string(1.0f))
        .append(" ")
        .append(std::to_string(1.0f))
        .append("\n")
        .append("skew: ")
        .append(std::to_string(0.0f))
        .append(" ")
        .append(std::to_string(0.0f))
        .append(" ")
        .append(std::to_string(0.0f))
        .append("\n")
        .append("perspective: ")
        .append(std::to_string(0.0f))
        .append(" ")
        .append(std::to_string(0.0f))
        .append(" ")
        .append(std::to_string(0.0f))
        .append(" ")
        .append(std::to_string(1.0f))
        .append("\n")
        .append("quaternion: ")
        .append(std::to_string(0.0))
        .append(" ")
        .append(std::to_string(0.0))
        .append(" ")
        .append(std::to_string(0.0))
        .append(" ")
        .append(std::to_string(0.0))
        .append("\n");
    EXPECT_EQ(decomposedTransform.ToString(), resStr);
}

/**
 * @tc.name: TransformUtilTest008
 * @tc.desc: Test the functions of the class TransformOperations.
 * @tc.type: FUNC
 */
HWTEST_F(TransformUtilTest, TransformUtilTest008, TestSize.Level1)
{
    std::vector<TransformOperation> operations;
    operations.push_back(TransformOperation::Create(TransformOperationType::TRANSLATE));
    operations.push_back(TransformOperation::Create(TransformOperationType::SCALE));
    operations.push_back(TransformOperation::Create(TransformOperationType::SKEW));
    operations.push_back(TransformOperation::Create(TransformOperationType::ROTATE));
    operations.push_back(TransformOperation::Create(TransformOperationType::PERSPECTIVE));
    operations.push_back(TransformOperation::Create(TransformOperationType::MATRIX));
    operations.push_back(TransformOperation::Create(TransformOperationType::UNDEFINED));

    TransformOperations::ParseOperationsToMatrix(operations);
    EXPECT_EQ(operations[0].type_, TransformOperationType::TRANSLATE);
    EXPECT_EQ(operations[0].translateOperation_, TranslateOperation());
    EXPECT_EQ(operations[0].matrix4_, Matrix4::CreateTranslate(NUM_D2, NUM_D2, NUM_D2));
    EXPECT_EQ(operations[1].type_, TransformOperationType::SCALE);
    EXPECT_EQ(operations[1].scaleOperation_, ScaleOperation());
    EXPECT_EQ(operations[1].matrix4_, Matrix4::CreateScale(NUM_D1, NUM_D1, NUM_D1));
    EXPECT_EQ(operations[2].type_, TransformOperationType::SKEW);
    EXPECT_EQ(operations[2].skewOperation_, SkewOperation());
    EXPECT_EQ(operations[2].matrix4_, Matrix4::CreateSkew(NUM_D2, NUM_D2));
    EXPECT_EQ(operations[3].type_, TransformOperationType::ROTATE);
    EXPECT_EQ(operations[3].rotateOperation_, RotateOperation());
    EXPECT_EQ(operations[3].matrix4_, Matrix4::CreateRotate(NUM_D2, NUM_D2, NUM_D2, NUM_D2));
    EXPECT_EQ(operations[4].type_, TransformOperationType::PERSPECTIVE);
    EXPECT_EQ(operations[4].perspectiveOperation_, PerspectiveOperation());
    EXPECT_EQ(operations[4].matrix4_, Matrix4::CreatePerspective(NUM_D2));
    EXPECT_EQ(operations[5].type_, TransformOperationType::MATRIX);
    EXPECT_EQ(operations[5].matrix4_, Matrix4::CreateIdentity());
    EXPECT_EQ(operations[6].type_, TransformOperationType::UNDEFINED);
    EXPECT_EQ(operations[6].matrix4_, Matrix4::CreateIdentity());

    TransformOperations to(operations);
    TransformOperations from(operations);
    TransformOperations result = TransformOperations::Blend(to, from, PROGRESS);
    ASSERT_EQ(result.GetOperations().size(), operations.size());
    EXPECT_EQ(result.GetOperations()[0].translateOperation_, TranslateOperation());
    EXPECT_EQ(result.GetOperations()[1].scaleOperation_, ScaleOperation());
    EXPECT_EQ(result.GetOperations()[2].skewOperation_, SkewOperation());
    EXPECT_EQ(result.GetOperations()[3].rotateOperation_, RotateOperation());
    EXPECT_EQ(result.GetOperations()[4].perspectiveOperation_, PerspectiveOperation());
}

/**
 * @tc.name: TransformUtilTest009
 * @tc.desc: Test the functions of the class ComposeTransform.
 * @tc.type: FUNC
 */
HWTEST_F(TransformUtilTest, TransformUtilTest009, TestSize.Level1)
{
    DecomposedTransform decomposedTransform;
    decomposedTransform.skew[0] = 1.0f;
    decomposedTransform.skew[1] = 1.0f;
    decomposedTransform.skew[2] = 1.0f;
    EXPECT_EQ(TransformUtil::ComposeTransform(decomposedTransform).GetScaleX(), 1.0);
    EXPECT_EQ(TransformUtil::ComposeTransform(decomposedTransform).GetScaleY(), 1.0);
}

/**
 * @tc.name: TransformUtilTest010
 * @tc.desc: Test the functions of  BuildTranslationMatrix.
 * @tc.type: FUNC
 */
HWTEST_F(TransformUtilTest, TransformUtilTest010, TestSize.Level1)
{
    DecomposedTransform decomposedTransform;
    // 0.000001 true false false
    decomposedTransform.translate[0] = 0.000001f;
    decomposedTransform.translate[1] = 1.0f;
    decomposedTransform.translate[2] = 1.0f;
    EXPECT_EQ(TransformUtil::ComposeTransform(decomposedTransform).GetScaleX(), 1.0);
    EXPECT_EQ(TransformUtil::ComposeTransform(decomposedTransform).GetScaleY(), 1.0);
    // 0.000001 true true false
    decomposedTransform.translate[0] = 0.000001f;
    decomposedTransform.translate[1] = 0.000001f;
    decomposedTransform.translate[2] = 1.0f;
    EXPECT_EQ(TransformUtil::ComposeTransform(decomposedTransform).GetScaleX(), 1.0);
    EXPECT_EQ(TransformUtil::ComposeTransform(decomposedTransform).GetScaleY(), 1.0);
    // 0.000001 true true true
    decomposedTransform.translate[0] = 0.000001f;
    decomposedTransform.translate[1] = 0.000001f;
    decomposedTransform.translate[2] = 0.000001f;
    EXPECT_EQ(TransformUtil::ComposeTransform(decomposedTransform).GetScaleX(), 1.0);
    EXPECT_EQ(TransformUtil::ComposeTransform(decomposedTransform).GetScaleY(), 1.0);
    // 0.000001 false true true
    decomposedTransform.translate[0] = 1.0f;
    decomposedTransform.translate[1] = 0.000001f;
    decomposedTransform.translate[2] = 0.000001f;
    EXPECT_EQ(TransformUtil::ComposeTransform(decomposedTransform).GetScaleX(), 1.0);
    EXPECT_EQ(TransformUtil::ComposeTransform(decomposedTransform).GetScaleY(), 1.0);
    // 0.000001 true false true
    decomposedTransform.translate[0] = 0.000001f;
    decomposedTransform.translate[1] = 1.0f;
    decomposedTransform.translate[2] = 0.000001f;
    EXPECT_EQ(TransformUtil::ComposeTransform(decomposedTransform).GetScaleX(), 1.0);
    EXPECT_EQ(TransformUtil::ComposeTransform(decomposedTransform).GetScaleY(), 1.0);
}

/**
 * @tc.name: TransformUtilTest011
 * @tc.desc: Test the functions of the BuildSkewMatrix
 * @tc.type: FUNC
 */
HWTEST_F(TransformUtilTest, TransformUtilTest011, TestSize.Level1)
{
    DecomposedTransform decomposedTransform;
    decomposedTransform.skew[0] = 0.0f;
    decomposedTransform.skew[1] = 0.0f;
    decomposedTransform.skew[2] = 0.0f;
    EXPECT_EQ(TransformUtil::ComposeTransform(decomposedTransform).GetScaleX(), 1.0);
    EXPECT_EQ(TransformUtil::ComposeTransform(decomposedTransform).GetScaleY(), 1.0);
}

/**
 * @tc.name: TransformUtilTest012
 * @tc.desc: Test the functions of the DecomposeTransform
 * @tc.type: FUNC
 */
HWTEST_F(TransformUtilTest, TransformUtilTest012, TestSize.Level1)
{
    // Normalize is false
    DecomposedTransform out;
    Matrix4 transform = Matrix4::CreateIdentity();
    transform.Set(3, 3, 0.000001f);
    TransformUtil::DecomposeTransform(out, transform);
    EXPECT_EQ(transform.Get(3, 3) == 0.000001f, true);
    // Normalize is true
    transform.Set(3, 3, 1.0f);
    // NearZero false false false
    transform.Set(3, 0, 1.0f);
    transform.Set(3, 1, 1.0f);
    transform.Set(3, 2, 1.0f);
    TransformUtil::DecomposeTransform(out, transform);
    EXPECT_EQ(out.perspective[0] == 1.0f, true);
    // NearZero true false false
    transform.Set(3, 0, 0.000001f);
    transform.Set(3, 1, 1.0f);
    transform.Set(3, 2, 1.0f);
    TransformUtil::DecomposeTransform(out, transform);
    EXPECT_EQ(out.perspective[0] == 0.000001f, true);
    // NearZero true true false
    transform.Set(3, 0, 0.000001f);
    transform.Set(3, 1, 1.0f);
    transform.Set(3, 2, 1.0f);
    TransformUtil::DecomposeTransform(out, transform);
    EXPECT_EQ(out.perspective[0] == 0.000001f, true);
    // CreateScale 0.0f
    Matrix4 transform2 = Matrix4::CreateScale(0.0f, 0.0f, 0.0f);
    TransformUtil::DecomposeTransform(out, transform2);
    EXPECT_EQ(out.scale[0] == 0.0f, true);
}

/**
 * @tc.name: TransformUtilTest013
 * @tc.desc: Test the functions of the DecomposeTransform
 * @tc.type: FUNC
 */
HWTEST_F(TransformUtilTest, TransformUtilTest013, TestSize.Level1)
{
    // Normalize is false
    DecomposedTransform out;
    float INDEX_0_004 = 0.004f;
    float INDEX_0_008 = 0.008f;
    float INDEX_0_7071 = 0.7071;
    Matrix4 transform(0, INDEX_0_004, 0, 0, -INDEX_0_004, -INDEX_0_004, 0, -INDEX_0_008, 0, 0, 1, 0, 0, 0, 0, 1);
    TransformUtil::DecomposeTransform(out, transform);
    EXPECT_EQ(out.skew[0], 1);
    EXPECT_EQ(out.skew[1], 0);
    EXPECT_EQ(out.skew[2], 0);
    EXPECT_EQ(out.scale[0], INDEX_0_004);
    EXPECT_EQ(out.scale[1], INDEX_0_004);
    EXPECT_EQ(out.scale[2], 1);
    EXPECT_EQ(out.quaternion.GetX(), 0);
    EXPECT_EQ(out.quaternion.GetY(), 0);
    EXPECT_TRUE(NearEqual(out.quaternion.GetZ(), -INDEX_0_7071));
    EXPECT_TRUE(NearEqual(out.quaternion.GetW(), INDEX_0_7071));
    EXPECT_EQ(out.translate[0], 0);
    EXPECT_EQ(out.translate[1], -INDEX_0_008);
    EXPECT_EQ(out.translate[2], 0);
    EXPECT_EQ(out.perspective[0], 0);
    EXPECT_EQ(out.perspective[1], 0);
    EXPECT_EQ(out.perspective[2], 0);
    EXPECT_EQ(out.perspective[3], 1);
}

/**
 * @tc.name: Invert001
 * @tc.desc: Test function: Invert
 * @tc.type: FUNC
 */
HWTEST_F(TransformUtilTest, Invert001, TestSize.Level1)
{
    float INDEX_0_004 = 0.004f;
    float INDEX_0_008 = 0.008f;
    float INDEX_250 = 250.0f;
    Matrix4 matrix =
        Matrix4::Invert({ 0, INDEX_0_004, 0, 0, -INDEX_0_004, -INDEX_0_004, 0, -INDEX_0_008, 0, 0, 1, 0, 0, 0, 0, 1 });
    EXPECT_TRUE(NearEqual(matrix.Get(0, 0), -INDEX_250));
    EXPECT_TRUE(NearEqual(matrix.Get(0, 1), -INDEX_250));
    EXPECT_EQ(matrix.Get(0, 2), 0);
    EXPECT_EQ(matrix.Get(0, 3), -2);
    EXPECT_TRUE(NearEqual(matrix.Get(1, 0), INDEX_250));
    EXPECT_EQ(matrix.Get(1, 1), 0);
    EXPECT_EQ(matrix.Get(1, 2), 0);
    EXPECT_EQ(matrix.Get(1, 3), 0);
    EXPECT_EQ(matrix.Get(2, 0), 0);
    EXPECT_EQ(matrix.Get(2, 1), 0);
    EXPECT_EQ(matrix.Get(2, 2), 1);
    EXPECT_EQ(matrix.Get(2, 3), 0);
    EXPECT_EQ(matrix.Get(3, 0), 0);
    EXPECT_EQ(matrix.Get(3, 1), 0);
    EXPECT_EQ(matrix.Get(3, 2), 0);
    EXPECT_EQ(matrix.Get(3, 3), 1);

    matrix = Matrix4::Invert({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
    EXPECT_EQ(matrix.Get(0, 0), Matrix4::CreateIdentity().Get(0, 0));
}
} // namespace OHOS::Ace
