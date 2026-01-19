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
#include "bridge/declarative_frontend/jsview/models/preview_mock_model_impl.h"

#include "bridge/declarative_frontend/jsview/canvas/js_rendering_context.h"
#include "compatible/components/canvas/canvas_modifier_compatible.h"
#include "compatible/components/canvas/custom_paint_component.h"
#include "core/common/dynamic_module_helper.h"

namespace OHOS::Ace::Framework {
void PreviewMockModelImpl::Create(const std::string& content)
{
    auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("canvas");
    CHECK_NULL_VOID(loader);
    auto* modifier = reinterpret_cast<const ArkUICanvasModifierCompatible*>(loader->GetCustomModifier());
    CHECK_NULL_VOID(modifier);
    modifier->createCustomPaintComponent(content);
}

void PreviewMockModelImpl::CreateJSRenderingContext(bool anti, const RefPtr<CanvasTaskPool>& pool)
{
    auto jsContext = Referenced::MakeRefPtr<JSRenderingContext>();
    jsContext->SetAnti(anti);
    jsContext->SetCanvasPattern(pool);
    jsContext->SetAntiAlias();
}

} // namespace OHOS::Ace::Framework