/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "compatible/components/canvas/canvas_loader.h"

#include "base/memory/ace_type.h"
#include "compatible/components/canvas/bridge/jsi_canvas_bridge.h"
#include "compatible/components/canvas/bridge/jsi_offscreen_canvas_bridge.h"
#include "compatible/components/canvas/canvas_declaration.h"
#include "compatible/components/canvas/canvas_model_impl.h"
#include "compatible/components/canvas/canvas_rendering_context_2d_model_impl.h"
#include "compatible/components/canvas/dom_canvas.h"
#include "compatible/components/canvas/offscreen_canvas_rendering_context_2d_model_impl.h"
#include "compatible/components/component_loader.h"
#include "compatible/components/js_command.h"
#include "core/components_v2/inspector/inspector_composed_element.h"

namespace OHOS::Ace {

RefPtr<Framework::DOMNode> CanvasLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMCanvas>(nodeId, nodeName);
}

void* CanvasLoader::CreateModel()
{
    return new Framework::CanvasModelImpl();
}

RefPtr<Declaration> CanvasLoader::CreateDeclaration()
{
    return AceType::MakeRefPtr<CanvasDeclaration>();
}

RefPtr<V2::InspectorComposedElement> CanvasLoader::CreateInspectorElement(const std::string& id)
{
    return AceType::MakeRefPtr<V2::InspectorComposedElement>(id);
}

void* OHOS_ACE_Compatible_GetCanvasRenderingContext(bool isOffscreen)
{
    if (isOffscreen) {
        return new Framework::OffscreenCanvasRenderingContext2DModelImpl();
    } else {
        return new Framework::CanvasRenderingContext2DModelImpl();
    }
}

void* OHOS_ACE_Compatible_CreateCanvasBridge(CanvasBridgeParams& params)
{
    if (params.isOffscreen) {
        return new Framework::JsiOffscreenCanvasBridge(params.pipeline, params.width, params.height);
    } else {
        return new Framework::JsiCanvasBridge();
    }
}

} // namespace OHOS::Ace