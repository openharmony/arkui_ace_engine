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

#include "frameworks/compatible/components/canvas/canvas_modifier_compatible.h"
#ifdef PREVIEW
#include "bridge/declarative_frontend/jsview/models/preview_mock_model_impl.h"
#endif
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "interfaces/inner_api/ace_kit/include/ui/base/ace_type.h"
#include "compatible/components/canvas/offscreen_canvas_rendering_context_2d_model_impl.h"
#include "compatible/components/canvas/canvas_rendering_context_2d_model_impl.h"
#include "frameworks/compatible/components/canvas/custom_paint_component.h"
#include "frameworks/bridge/js_frontend/engine/common/base_canvas_bridge.h"
#include "compatible/components/canvas/bridge/jsi_canvas_bridge.h"
#include "compatible/components/canvas/bridge/jsi_offscreen_canvas_bridge.h"
#include "compatible/components/component_loader.h"

namespace OHOS::Ace::CanvasModifierCompatible {
static RefPtr<CustomPaintComponent> customPaintComponent_;
namespace {
#ifdef PREVIEW
constexpr Dimension DEFAULT_FONT_SIZE = 30.0_px;
constexpr double DEFAULT_OFFSET = 25;
constexpr double DEFAULT_HEIGHT = 30;
#endif

void CreateCustomPaintComponent(const std::string& content)
{
#ifdef PREVIEW
    RefPtr<CustomPaintComponent> mockComponent = AceType::MakeRefPtr<CustomPaintComponent>();

    auto& pool = mockComponent->GetTaskPool();
    Framework::PreviewMockModelImpl::CreateJSRenderingContext(true, pool);

    mockComponent->GetTaskPool()->UpdateFontSize(DEFAULT_FONT_SIZE);
    mockComponent->GetTaskPool()->FillText(
        "This component is not supported on PC preview.", Offset(0, DEFAULT_OFFSET));

    if (content == "Video") {
        mockComponent->SetInspectorTag(content + "ComponentV2");
    } else if (content == "PluginComponent" || content == "UIExtensionComponent") {
        mockComponent->SetInspectorTag(content);
    } else {
        mockComponent->SetInspectorTag(content + "Component");
    }

    OHOS::Ace::Framework::ViewStackProcessor::GetInstance()->Push(mockComponent);
    RefPtr<BoxComponent> mountBox = OHOS::Ace::Framework::ViewStackProcessor::GetInstance()->GetBoxComponent();
    mountBox->SetColor(Color::FromString("#808080"));
    mountBox->SetHeight(DEFAULT_HEIGHT);
#endif
}

void* CreateCanvasRenderingContextModel(bool isOffscreen)
{
    if (isOffscreen) {
        return new Framework::OffscreenCanvasRenderingContext2DModelImpl();
    } else {
        return new Framework::CanvasRenderingContext2DModelImpl();
    }
}

void* CreateCanvasBridge(CanvasBridgeParams& params)
{
    if (params.isOffscreen) {
        return new Framework::JsiOffscreenCanvasBridge(params.pipeline, params.width, params.height);
    } else {
        return new Framework::JsiCanvasBridge();
    }
}

}

const ArkUICanvasModifierCompatible* GetCanvasModifier()
{
    static const ArkUICanvasModifierCompatible instance = {
        .createCustomPaintComponent = CreateCustomPaintComponent,
        .createCanvasRenderingContextModel = CreateCanvasRenderingContextModel,
        .createCanvasBridge = CreateCanvasBridge,
    };
    return &instance;
}
} // OHOS::Ace::CanvasModifierCompatible