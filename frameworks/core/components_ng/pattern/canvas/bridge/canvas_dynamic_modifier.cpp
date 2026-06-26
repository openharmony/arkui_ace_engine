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
#include "core/common/container.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components/theme/app_theme.h"
#include "core/interfaces/native/node/node_canvas_modifier.h"

#include "core/components/common/properties/paint_state.h"
#include "core/components_ng/pattern/canvas/canvas_model_ng.h"
#include "core/components_ng/pattern/canvas/canvas_pattern.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_stack_model.h"

namespace OHOS::Ace {
CanvasModel* CanvasModel::GetInstance()
{
#ifdef NG_BUILD
    static NG::CanvasModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::CanvasModelNG instance;
        return &instance;
    } else {
        static auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("canvas");
        if (loader == nullptr) {
            TAG_LOGE(AceLogTag::ACE_CANVAS_COMPONENT, "CanvasModel::GetInstance: canvas loader not found");
            return nullptr;
        }
        return reinterpret_cast<CanvasModel*>(loader->CreateModel());
    }
#endif
}

#ifndef CROSS_PLATFORM
CanvasModel* GetCanvasModelImpl()
{
    static auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("canvas");
    static CanvasModel* instance = loader ? reinterpret_cast<CanvasModel*>(loader->CreateModel()) : nullptr;
    if (instance == nullptr) {
        TAG_LOGE(AceLogTag::ACE_CANVAS_COMPONENT, "GetCanvasModelImpl: canvas loader not found");
    }
    return instance;
}
#endif
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace CanvasDynamicModifier {

void CreateModel()
{
    CanvasModel::GetInstance()->Create(); // modelng
}

void SetCanvasOnReady(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onReady = reinterpret_cast<std::function<void(bool, CanvasUnit)>*>(callback);
        CanvasModelNG::SetOnReady(frameNode, std::move(*onReady));
    } else {
        CanvasModelNG::ResetOnReady(frameNode);
    }
}

void ResetCanvasOnReady(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CanvasModelNG::ResetOnReady(frameNode);
}

void SetCanvasEnableAnalyzer(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CanvasModelNG::EnableAnalyzer(frameNode, static_cast<bool>(value));
}

void ResetCanvasEnableAnalyzer(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CanvasModelNG::EnableAnalyzer(frameNode, false);
}

void SetCanvasAntiAlias(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto canvasPattern = AceType::DynamicCast<CanvasPattern>(CanvasModelNG::GetCanvasPattern(frameNode));
    CHECK_NULL_VOID(canvasPattern);
    canvasPattern->SetAntiAlias(static_cast<bool>(value));
}

void SetCanvasImmediateRender(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CanvasModelNG::SetImmediateRender(frameNode, static_cast<bool>(value));
}

void ResetCanvasImmediateRender(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CanvasModelNG::SetImmediateRender(frameNode, false);
}

void SetCanvasUpdateUnit(ArkUINodeHandle node, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CanvasModelNG::UpdateUnit(frameNode, static_cast<CanvasUnit>(unit));
}

void ResetCanvasUpdateUnit(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CanvasModelNG::UpdateUnit(frameNode, CanvasUnit::DEFAULT);
}

ArkUINodeHandle CreateFrameNode(int32_t nodeId)
{
    auto frameNode = CanvasModelNG::CreateFrameNode(nodeId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    auto node = reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
    CHECK_NULL_RETURN(node, nullptr);
    return node;
}

void SetInvalidate(ArkUINodeHandle node)
{
    // node may be a FrameNode* (NG pipeline) or AceType*/CanvasPattern* (peer impl path).
    // Try DynamicCast first, then fallback to reinterpret_cast<FrameNode*>.
    auto* pattern = AceType::DynamicCast<CanvasPattern>(reinterpret_cast<AceType*>(node));
    if (!pattern) {
        auto* frameNode = reinterpret_cast<FrameNode*>(node);
        CHECK_NULL_VOID(frameNode);
        auto patternRef = AceType::DynamicCast<CanvasPattern>(CanvasModelNG::GetCanvasPattern(frameNode));
        pattern = AceType::RawPtr(patternRef);
    }
    CHECK_NULL_VOID(pattern);
    pattern->SetInvalidate();
}

void SetAntiAlias(ArkUINodeHandle node, ArkUI_Bool antialias)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto canvasPattern = AceType::DynamicCast<CanvasPattern>(CanvasModelNG::GetCanvasPattern(frameNode));
    CHECK_NULL_VOID(canvasPattern);
    canvasPattern->SetAntiAlias(antialias);
}

void SetRSCanvasCallback(ArkUINodeHandle node, void* callback)
{
    auto* pattern = AceType::DynamicCast<CanvasPattern>(reinterpret_cast<AceType*>(node));
    if (!pattern) {
        auto* frameNode = reinterpret_cast<FrameNode*>(node);
        CHECK_NULL_VOID(frameNode);
        auto patternRef = AceType::DynamicCast<CanvasPattern>(CanvasModelNG::GetCanvasPattern(frameNode));
        pattern = AceType::RawPtr(patternRef);
    }
    CHECK_NULL_VOID(pattern);
    auto& cb = *reinterpret_cast<std::function<void(std::shared_ptr<RSCanvas>, double, double)>*>(callback);
    pattern->SetRSCanvasCallback(cb);
}

void SetUpdateContextCallback(ArkUINodeHandle node, void* callback)
{
    auto* pattern = AceType::DynamicCast<CanvasPattern>(reinterpret_cast<AceType*>(node));
    if (!pattern) {
        auto* frameNode = reinterpret_cast<FrameNode*>(node);
        CHECK_NULL_VOID(frameNode);
        auto patternRef = AceType::DynamicCast<CanvasPattern>(CanvasModelNG::GetCanvasPattern(frameNode));
        pattern = AceType::RawPtr(patternRef);
    }
    CHECK_NULL_VOID(pattern);
    auto& cb = *reinterpret_cast<std::function<void(CanvasUnit)>*>(callback);
    pattern->SetUpdateContextCallback(std::move(cb));
}

void SetRSCanvasForDrawingContext(ArkUINodeHandle node)
{
    auto* pattern = AceType::DynamicCast<CanvasPattern>(reinterpret_cast<AceType*>(node));
    if (!pattern) {
        auto* frameNode = reinterpret_cast<FrameNode*>(node);
        CHECK_NULL_VOID(frameNode);
        auto patternRef = AceType::DynamicCast<CanvasPattern>(CanvasModelNG::GetCanvasPattern(frameNode));
        pattern = AceType::RawPtr(patternRef);
    }
    CHECK_NULL_VOID(pattern);
    pattern->SetRSCanvasForDrawingContext();
}

#ifndef CROSS_PLATFORM
void CreateModelImpl()
{
    GetCanvasModelImpl()->Create();
}

void SetCanvasOnReadyImpl(ArkUINodeHandle node, void* callback)
{
    if (callback) {
        auto onReady = reinterpret_cast<std::function<void(bool, CanvasUnit)>*>(callback);
        GetCanvasModelImpl()->SetOnReady(std::move(*onReady));
    }
}

void ResetCanvasOnReadyImpl(ArkUINodeHandle node)
{
    // Legacy path: reset is handled by setting nullptr callback
}

void SetCanvasEnableAnalyzerImpl(ArkUINodeHandle node, ArkUI_Bool value)
{
    GetCanvasModelImpl()->EnableAnalyzer(static_cast<bool>(value));
}

void ResetCanvasEnableAnalyzerImpl(ArkUINodeHandle node)
{
    GetCanvasModelImpl()->EnableAnalyzer(false);
}
#endif

} // namespace CanvasDynamicModifier

const ArkUICanvasModifier* GetCanvasDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifndef CROSS_PLATFORM
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUICanvasModifier modifier = {
            .createModel = CanvasDynamicModifier::CreateModelImpl,
            .setCanvasOnReady = CanvasDynamicModifier::SetCanvasOnReadyImpl,
            .resetCanvasOnReady = CanvasDynamicModifier::ResetCanvasOnReadyImpl,
            .setCanvasEnableAnalyzer = CanvasDynamicModifier::SetCanvasEnableAnalyzerImpl,
            .resetCanvasEnableAnalyzer = CanvasDynamicModifier::ResetCanvasEnableAnalyzerImpl,
            .setCanvasAntiAlias = CanvasDynamicModifier::SetCanvasAntiAlias,
            .setCanvasImmediateRender = nullptr,
            .resetCanvasImmediateRender = nullptr,
            .setCanvasUpdateUnit = nullptr,
            .resetCanvasUpdateUnit = nullptr,
            .createFrameNode = nullptr,
            .setInvalidate = CanvasDynamicModifier::SetInvalidate,
            .setAntiAlias = nullptr,
            .setRSCanvasCallback = nullptr,
            .setUpdateContextCallback = nullptr,
            .setRSCanvasForDrawingContext = nullptr,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

        return &modifier;
#endif
    }
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUICanvasModifier modifier = {
        .createModel = CanvasDynamicModifier::CreateModel,
        .setCanvasOnReady = CanvasDynamicModifier::SetCanvasOnReady,
        .resetCanvasOnReady = CanvasDynamicModifier::ResetCanvasOnReady,
        .setCanvasEnableAnalyzer = CanvasDynamicModifier::SetCanvasEnableAnalyzer,
        .resetCanvasEnableAnalyzer = CanvasDynamicModifier::ResetCanvasEnableAnalyzer,
        .setCanvasAntiAlias = CanvasDynamicModifier::SetCanvasAntiAlias,
        .setCanvasImmediateRender = CanvasDynamicModifier::SetCanvasImmediateRender,
        .resetCanvasImmediateRender = CanvasDynamicModifier::ResetCanvasImmediateRender,
        .setCanvasUpdateUnit = CanvasDynamicModifier::SetCanvasUpdateUnit,
        .resetCanvasUpdateUnit = CanvasDynamicModifier::ResetCanvasUpdateUnit,
        .createFrameNode = CanvasDynamicModifier::CreateFrameNode,
        .setInvalidate = CanvasDynamicModifier::SetInvalidate,
        .setAntiAlias = CanvasDynamicModifier::SetAntiAlias,
        .setRSCanvasCallback = CanvasDynamicModifier::SetRSCanvasCallback,
        .setUpdateContextCallback = CanvasDynamicModifier::SetUpdateContextCallback,
        .setRSCanvasForDrawingContext = CanvasDynamicModifier::SetRSCanvasForDrawingContext,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

} // namespace OHOS::Ace::NG
