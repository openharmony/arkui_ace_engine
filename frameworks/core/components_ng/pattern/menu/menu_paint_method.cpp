/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/menu/menu_paint_method.h"

#include "core/components/select/select_theme.h"
#include "core/components_ng/pattern/menu/menu_paint_property.h"
#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {

CanvasDrawFunction MenuPaintMethod::GetContentDrawFunction(PaintWrapper* paintWrapper)
{
    return [paintWrapper](RSCanvas& canvas) {
        CHECK_NULL_VOID(paintWrapper);
        auto props = DynamicCast<MenuPaintProperty>(paintWrapper->GetPaintProperty());
        CHECK_NULL_VOID(props);
        if (!props->GetEnableArrow().has_value() || !props->GetEnableArrow().value()) {
            return;
        }
        auto clipPath = props->GetClipPath().value_or("");
        if (clipPath == "") {
            return;
        }
        auto path = AceType::MakeRefPtr<Path>();
        path->SetValue(clipPath);
        path->SetBasicShapeType(BasicShapeType::PATH);
        auto renderContext = paintWrapper->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->UpdateClipShape(path);
    };
}
} // namespace OHOS::Ace::NG
