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

std::shared_ptr<ArkUIBaseNode> CreateImageListExample()
{
    auto list = std::make_shared<ArkUIListNode>();
    // 设置列表方向为纵向
    ArkUI_NumberValue directionValue[] = {{.i32 = ARKUI_AXIS_VERTICAL}};
    ArkUI_AttributeItem directionItem = {directionValue, 1};
    NativeModuleInstance::GetInstance()->GetNativeNodeAPI()->setAttribute(
        list->GetHandle(), NODE_LIST_DIRECTION, &directionItem);
    
    // test2
    auto image2 = std::make_shared<ArkUIImageNode>();
    image2->SetSrc("resources/rawfile/startIcon.png");
    image2->SetHeight(200);
    image2->SetWidth(200);
    ArkUI_NumberValue values2[] = {{.f32 = 20}, {.f32 = 20}, {.f32 = 20}, {.f32 = 20}};
    image2->SetSlice(values2);
    list->AddChild(image2);


    const int xDivs[] = {2, 4};
    const int yDivs[] = {2, 4};
    uint32_t xCount = 2;
    uint32_t yCount = 2;
    OH_Drawing_Rect *bounds = OH_Drawing_RectCreate(0, 0, 100, 100);
    uint32_t rectTypeCount = (xCount + 1) * (yCount + 1);
    OH_Drawing_LatticeRectType *rectTypes = new OH_Drawing_LatticeRectType[rectTypeCount];
    for (uint32_t i = 0; i < rectTypeCount; ++i) {
        rectTypes[i] = OH_Drawing_LatticeRectType::DEFAULT;
    }

    // test3
    auto image3 = std::make_shared<ArkUIImageNode>();
    image3->SetSrc("resources/rawfile/startIcon.png");

    OH_Drawing_Lattice *lattice3 = nullptr;
    OH_Drawing_ErrorCode code3 = OH_Drawing_LatticeCreate(
        xDivs, yDivs, xCount, yCount, bounds, nullptr, 0, 0, 0, &lattice3);
    image3->SetLattice(lattice3);
    list->AddChild(image3);

    // test4
    auto image4 = std::make_shared<ArkUIImageNode>();
    image4->SetSrc("resources/rawfile/startIcon.png");

    OH_Drawing_Lattice *lattice4 = nullptr;
    OH_Drawing_ErrorCode code4 = OH_Drawing_LatticeCreate(
        xDivs, yDivs, xCount, yCount, nullptr, rectTypes, rectTypeCount, 0, 0, &lattice4);
    image4->SetLattice(lattice4);
    list->AddChild(image4);

    // test5
    auto image5 = std::make_shared<ArkUIImageNode>();
    image5->SetSrc("resources/rawfile/startIcon.png");
    const uint32_t colors[] = {0xFFFF0000, 0xFF00FF00, 0xFF0000FF, 0xFFFFFF00};

    OH_Drawing_LatticeRectType *rectTypes5 = new OH_Drawing_LatticeRectType[rectTypeCount];
    for (uint32_t i = 0; i < rectTypeCount; ++i) {
        rectTypes[i] = OH_Drawing_LatticeRectType::FIXED_COLOR;
    }
    OH_Drawing_Lattice *lattice5 = nullptr;
    OH_Drawing_ErrorCode code5 = OH_Drawing_LatticeCreate(
        xDivs, yDivs, xCount, yCount, bounds, rectTypes5, rectTypeCount, colors, 9, &lattice5);
    image5->SetLattice(lattice5);
    list->AddChild(image5);

    // test6
    auto image6 = std::make_shared<ArkUIImageNode>();
    image6->SetSrc("resources/rawfile/startIcon.png");

    image6->SetObjectRepeat(ArkUI_ImageRepeat::ARKUI_IMAGE_REPEAT_NONE);
    image6->SetAntialiased(true);
    image6->SetOrientation(ArkUI_ImageRotateOrientation::ARKUI_ORIENTATION_LEFT);
    list->AddChild(image6);

    // test7
    auto image7 = std::make_shared<ArkUIImageNode>();
    image7->SetSrc("resources/rawfile/startIcon.png");
    image7->SetWidth(200);
    image7->SetHeight(200);
    static float nums[] = {-1000, -10, -0.5, 0, 0.5, 10, 1000};
    static int index = 0;
    static float temp = nums[index];
    ArkUI_NumberValue values7[] = {{.f32 = temp}, {.f32 = temp}, {.f32 = temp}, {.f32 = temp}};
    image7->SetSlice(values7);

    auto button7 = std::make_shared<ArkUIButtonNode>();
    std::string str7 = "test7 change";
    button7->SetOnClick([=]() {
        index = (index + 1) % 7;
        temp = nums[index];
        ArkUI_NumberValue values7[] = {{.f32 = temp}, {.f32 = temp}, {.f32 = temp}, {.f32 = temp}};
        image7->SetSlice(values7);
    });
    list->AddChild(image7);
    
    // 公共rotate、translate和scale属性
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
    
    // test8
    auto image8 = std::make_shared<ArkUIImageNode>();
    image8->SetSrc("resources/rawfile/startIcon.png");
    image8->SetImageMatrix(matrix);
    list->AddChild(image8);
    
    // test9
    auto image9 = std::make_shared<ArkUIImageNode>();
    image9->SetSrc("resources/rawfile/startIcon.png");
    image9->SetObjectFit(ArkUI_ObjectFit::ARKUI_OBJECT_FIT_NONE_MATRIX);
    list->AddChild(image9);
    
    // test10
    auto image10 = std::make_shared<ArkUIImageNode>();
    image10->SetSrc("resources/rawfile/startIcon.png");
    image10->SetImageMatrix(matrix);
    image10->SetObjectFit(ArkUI_ObjectFit::ARKUI_OBJECT_FIT_NONE_MATRIX);
    list->AddChild(image10);
    
    // test11
    auto image11 = std::make_shared<ArkUIImageNode>();
    image11->SetSrc("resources/rawfile/startIcon.png");
    image11->SetOrientation(ArkUI_ImageRotateOrientation::ARKUI_ORIENTATION_AUTO);
    list->AddChild(image11);

    return list;
}
} // namespace NativeModule

#endif // MYAPPLICATION_NORMALIMAGELISTEXAMPLE_H