/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * ========================================
 * Image CAPI 测试用例集合 (融合 Image_C 和 ImageCapiExample)
 * ========================================
 * 
 * 文件目的：
 * 本文件包含 11 个 Image 组件的 CAPI 测试用例，涵盖：
 * - 基础图片加载
 * - 九宫格切片 (resizable)
 * - Lattice 格点渲染
 * - 图片变换矩阵 (Matrix)
 * - 方向旋转 (orientation)
 * - 抗锯齿 (antialiased)
 * - 重复模式 (objectRepeat)
 * 
 * 测试用例列表：
 * - Test 1: 基础图片加载
 * - Test 2: 九宫格切片 (Slice)
 * - Test 3: Lattice 基础渲染
 * - Test 4: Lattice 自定义区域
 * - Test 5: Lattice 固定颜色
 * - Test 6: 方向 + 抗锯齿 + 重复模式
 * - Test 7: 动态切片参数
 * - Test 8: Matrix 变换 (平移 + 旋转 + 缩放)
 * - Test 9: ObjectFit 测试
 * - Test 10: Matrix + ObjectFit 组合
 * - Test 11: EXIF 方向自动识别
 * 
 * 使用方法：
 * 在 ArkTS 层调用 nativeNode.createNativeRoot() 后，
 * Native 层会调用 CreateImageListExample() 创建 UI 树
 */

#ifndef MYAPPLICATION_NORMALIMAGELISTEXAMPLE_H
#define MYAPPLICATION_NORMALIMAGELISTEXAMPLE_H

#include "ArkUIButtonNode.h"
#include "native_drawing/drawing_rect.h"

#include "ArkUIBaseNode.h"
#include "ArkUIImageNode.h"
#include "ArkUIListItemNode.h"
#include "ArkUIListNode.h"
#include <cstdint>

namespace NativeModule {

/**
 * 创建 Image 测试列表
 * @return 返回根节点 (ArkUIListNode)
 */
std::shared_ptr<ArkUIBaseNode> CreateImageListExample()
{
    // 创建纵向列表容器
    auto list = std::make_shared<ArkUIListNode>();
    ArkUI_NumberValue directionValue[] = {{.i32 = ARKUI_AXIS_VERTICAL}};
    ArkUI_AttributeItem directionItem = {directionValue, 1};
    NativeModuleInstance::GetInstance()->GetNativeNodeAPI()->setAttribute(
        list->GetHandle(), NODE_LIST_DIRECTION, &directionItem);
    
    // ========================================
    // Test 1: 基础图片加载
    // ========================================
    // 测试目的：验证最基本的图片加载功能
    // 涉及 API: SetSrc, SetWidth, SetHeight
    // 预期结果：正常显示 startIcon.png 图片
    auto image1 = std::make_shared<ArkUIImageNode>();
    image1->SetSrc("resources/rawfile/startIcon.png");
    image1->SetHeight(100);
    image1->SetWidth(100);
    list->AddChild(image1);

    // ========================================
    // Test 2: 九宫格切片 (Slice)
    // ========================================
    // 测试目的：测试图片九宫格切片功能，用于可拉伸图片
    // 涉及 API: SetSlice
    // 参数说明：4 个值分别表示 left, top, right, bottom 的切片边距 (px)
    // 预期结果：图片中间区域可拉伸，四角保持不变
    auto image2 = std::make_shared<ArkUIImageNode>();
    image2->SetSrc("resources/rawfile/startIcon.png");
    image2->SetHeight(200);
    image2->SetWidth(200);
    ArkUI_NumberValue values2[] = {{.f32 = 20}, {.f32 = 20}, {.f32 = 20}, {.f32 = 20}};
    image2->SetSlice(values2);
    list->AddChild(image2);

    // ========================================
    // Test 3: Lattice 基础渲染
    // ========================================
    // 测试目的：测试 Lattice 格点渲染功能
    // 涉及 API: SetLattice, OH_Drawing_LatticeCreate
    // 参数说明：
    //   - xDivs/yDivs: X/Y 方向的分割线位置
    //   - xCount/yCount: 分割线数量
    //   - bounds: 渲染边界矩形
    // 预期结果：图片按格点规则渲染
    const int xDivs[] = {2, 4};
    const int yDivs[] = {2, 4};
    uint32_t xCount = 2;
    uint32_t yCount = 2;
    OH_Drawing_Rect *bounds = OH_Drawing_RectCreate(0, 0, 100, 100);
    
    auto image3 = std::make_shared<ArkUIImageNode>();
    image3->SetSrc("resources/rawfile/startIcon.png");
    OH_Drawing_Lattice *lattice3 = nullptr;
    OH_Drawing_ErrorCode code3 = OH_Drawing_LatticeCreate(
        xDivs, yDivs, xCount, yCount, bounds, nullptr, 0, 0, 0, &lattice3);
    image3->SetLattice(lattice3);
    list->AddChild(image3);

    // ========================================
    // Test 4: Lattice 自定义区域类型
    // ========================================
    // 测试目的：测试 Lattice 自定义区域类型渲染
    // 涉及 API: OH_Drawing_LatticeCreate (带 rectTypes 参数)
    // 参数说明：rectTypes 定义每个区域的渲染类型
    // 预期结果：不同区域按指定类型渲染
    uint32_t rectTypeCount = (xCount + 1) * (yCount + 1);
    OH_Drawing_LatticeRectType *rectTypes = new OH_Drawing_LatticeRectType[rectTypeCount];
    for (uint32_t i = 0; i < rectTypeCount; ++i) {
        rectTypes[i] = OH_Drawing_LatticeRectType::DEFAULT;
    }

    auto image4 = std::make_shared<ArkUIImageNode>();
    image4->SetSrc("resources/rawfile/startIcon.png");
    OH_Drawing_Lattice *lattice4 = nullptr;
    OH_Drawing_ErrorCode code4 = OH_Drawing_LatticeCreate(
        xDivs, yDivs, xCount, yCount, nullptr, rectTypes, rectTypeCount, 0, 0, &lattice4);
    image4->SetLattice(lattice4);
    list->AddChild(image4);

    // ========================================
    // Test 5: Lattice 固定颜色填充
    // ========================================
    // 测试目的：测试 Lattice 固定颜色填充功能
    // 涉及 API: OH_Drawing_LatticeCreate (带 colors 参数)
    // 参数说明：colors 数组定义每个区域的颜色
    // 预期结果：不同区域显示不同颜色
    const uint32_t colors[] = {0xFFFF0000, 0xFF00FF00, 0xFF0000FF, 0xFFFFFF00};
    OH_Drawing_LatticeRectType *rectTypes5 = new OH_Drawing_LatticeRectType[rectTypeCount];
    for (uint32_t i = 0; i < rectTypeCount; ++i) {
        rectTypes5[i] = OH_Drawing_LatticeRectType::FIXED_COLOR;
    }
    
    auto image5 = std::make_shared<ArkUIImageNode>();
    image5->SetSrc("resources/rawfile/startIcon.png");
    OH_Drawing_Lattice *lattice5 = nullptr;
    OH_Drawing_ErrorCode code5 = OH_Drawing_LatticeCreate(
        xDivs, yDivs, xCount, yCount, bounds, rectTypes5, rectTypeCount, colors, 9, &lattice5);
    image5->SetLattice(lattice5);
    list->AddChild(image5);

    // ========================================
    // Test 6: 方向 + 抗锯齿 + 重复模式
    // ========================================
    // 测试目的：测试方向旋转、抗锯齿和重复模式组合效果
    // 涉及 API: SetOrientation, SetAntialiased, SetObjectRepeat
    // 预期结果：图片向左旋转 90 度，启用抗锯齿，不重复
    auto image6 = std::make_shared<ArkUIImageNode>();
    image6->SetSrc("resources/rawfile/startIcon.png");
    image6->SetObjectRepeat(ArkUI_ImageRepeat::ARKUI_IMAGE_REPEAT_NONE);
    image6->SetAntialiased(true);
    image6->SetOrientation(ArkUI_ImageRotateOrientation::ARKUI_ORIENTATION_LEFT);
    list->AddChild(image6);

    // ========================================
    // Test 7: 动态切片参数
    // ========================================
    // 测试目的：测试动态修改切片参数的效果
    // 涉及 API: SetSlice (动态更新)
    // 参数说明：nums 数组包含 7 组不同的切片值，点击按钮切换
    // 预期结果：点击按钮后切片参数变化，图片渲染效果随之改变
    auto image7 = std::make_shared<ArkUIImageNode>();
    image7->SetSrc("resources/rawfile/startIcon.png");
    image7->SetWidth(200);
    image7->SetHeight(200);
    static float nums[] = {-1000, -10, -0.5, 0, 0.5, 10, 1000};
    static int index = 0;
    static float temp = nums[index];
    ArkUI_NumberValue values7[] = {{.f32 = temp}, {.f32 = temp}, {.f32 = temp}, {.f32 = temp}};
    image7->SetSlice(values7);

    // 创建按钮用于切换切片参数
    auto button7 = std::make_shared<ArkUIButtonNode>();
    std::string str7 = "Test7: Change Slice";
    button7->SetText(str7);
    button7->SetOnClick([=]() {
        index = (index + 1) % 7;
        temp = nums[index];
        ArkUI_NumberValue newValues7[] = {{.f32 = temp}, {.f32 = temp}, {.f32 = temp}, {.f32 = temp}};
        image7->SetSlice(newValues7);
    });
    list->AddChild(image7);
    list->AddChild(button7);
    
    // ========================================
    // Test 8: Matrix 变换 (平移 + 旋转 + 缩放)
    // ========================================
    // 测试目的：测试 ImageMatrix 变换功能
    // 涉及 API: ImageMatrix::Translate, Rotate, Scale, SetImageMatrix
    // 参数说明：
    //   - Translate: 平移 (x=1, y=2, z=3)
    //   - Rotate: 旋转 (x=1, y=2, z=3, angle=6)
    //   - Scale: 缩放 (x=1, y=2, z=3)
    // 预期结果：图片应用复合变换效果
    const RotateOptions rotate {
        .x = 1.0,
        .y = 2.0,
        .z = 3.0,
        .centerX = 4.0,
        .centerY = 5.0,
        .angle = 6.0
    };
    const TranslateOptions translate {
        .x = 1.0,
        .y = 2.0, 
        .z = 3.0
    };
    const ScaleOptions scale {
        .x = 1.0,
        .y = 2.0,
        .z = 3.0,
        .centerX = 4.0,
        .centerY = 5.0
    };
    auto matrix = ImageMatrix::Identity();
    matrix->Translate(translate);
    matrix->Rotate(rotate);
    matrix->Scale(scale);
    
    auto image8 = std::make_shared<ArkUIImageNode>();
    image8->SetSrc("resources/rawfile/startIcon.png");
    image8->SetImageMatrix(matrix);
    list->AddChild(image8);
    
    // ========================================
    // Test 9: ObjectFit 测试
    // ========================================
    // 测试目的：测试 ObjectFit 属性
    // 涉及 API: SetObjectFit
    // 参数说明：ARKUI_OBJECT_FIT_NONE_MATRIX 表示不使用 Matrix 的 ObjectFit
    // 预期结果：图片按指定 ObjectFit 模式渲染
    auto image9 = std::make_shared<ArkUIImageNode>();
    image9->SetSrc("resources/rawfile/startIcon.png");
    image9->SetObjectFit(ArkUI_ObjectFit::ARKUI_OBJECT_FIT_NONE_MATRIX);
    list->AddChild(image9);
    
    // ========================================
    // Test 10: Matrix + ObjectFit 组合
    // ========================================
    // 测试目的：测试 Matrix 和 ObjectFit 组合效果
    // 涉及 API: SetImageMatrix, SetObjectFit
    // 预期结果：图片同时应用 Matrix 变换和 ObjectFit 模式
    auto image10 = std::make_shared<ArkUIImageNode>();
    image10->SetSrc("resources/rawfile/startIcon.png");
    image10->SetImageMatrix(matrix);
    image10->SetObjectFit(ArkUI_ObjectFit::ARKUI_OBJECT_FIT_NONE_MATRIX);
    list->AddChild(image10);
    
    // ========================================
    // Test 11: EXIF 方向自动识别
    // ========================================
    // 测试目的：测试 EXIF 方向信息自动识别
    // 涉及 API: SetOrientation(ARKUI_ORIENTATION_AUTO)
    // 预期结果：图片根据 EXIF 信息自动调整显示方向
    auto image11 = std::make_shared<ArkUIImageNode>();
    image11->SetSrc("resources/rawfile/startIcon.png");
    image11->SetOrientation(ArkUI_ImageRotateOrientation::ARKUI_ORIENTATION_AUTO);
    list->AddChild(image11);

    // 清理临时分配的内存
    delete[] rectTypes;
    delete[] rectTypes5;
    OH_Drawing_RectDestroy(bounds);
    OH_Drawing_LatticeDestroy(lattice3);
    OH_Drawing_LatticeDestroy(lattice4);
    OH_Drawing_LatticeDestroy(lattice5);

    return list;
}

} // namespace NativeModule

#endif // MYAPPLICATION_NORMALIMAGELISTEXAMPLE_H
