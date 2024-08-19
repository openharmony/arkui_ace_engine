/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_PREVIEW_MOCK_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_PREVIEW_MOCK_MODEL_IMPL_H

#include <functional>
#include <string>

#include "bridge/declarative_frontend/jsview/canvas/js_canvas_renderer.h"
#include "bridge/declarative_frontend/jsview/canvas/js_rendering_context.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components_ng/pattern/preview_mock/preview_mock_model.h"

namespace OHOS::Ace::Framework {
namespace {
constexpr Dimension DEFAULT_FONT_SIZE = 30.0_px;
constexpr double DEFAULT_OFFSET = 25;
constexpr double DEFAULT_HEIGHT = 30;
}

class ACE_EXPORT PreviewMockModelImpl : public PreviewMockModel {
public:
    void Create(const std::string& content) {
        RefPtr<OHOS::Ace::CustomPaintComponent> mockComponent = AceType::MakeRefPtr<OHOS::Ace::CustomPaintComponent>();
        auto jsContext = Referenced::MakeRefPtr<JSRenderingContext>();
        jsContext->SetAnti(true);
        jsContext->SetCanvasPattern(mockComponent->GetTaskPool());
        jsContext->SetAntiAlias();
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
        ViewStackProcessor::GetInstance()->Push(mockComponent);
        RefPtr<BoxComponent> mountBox = ViewStackProcessor::GetInstance()->GetBoxComponent();
        mountBox->SetColor(Color::FromString("#808080"));
        mountBox->SetHeight(DEFAULT_HEIGHT);
    }
};
} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_PREVIEW_MOCK_MODEL_IMPL_H
