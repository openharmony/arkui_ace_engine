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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WEB_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WEB_PAINT_METHOD_H

#include "core/components_ng/render/node_paint_method.h"
#include "core/components_ng/pattern/web/web_content_modifier.h"
#include "core/components_ng/render/render_surface.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT WebPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(WebPaintMethod, NodePaintMethod)
public:
    WebPaintMethod(RefPtr<NG::RenderSurface> surface): renderSuface_(surface) {}
    ~WebPaintMethod() override = default;

    CanvasDrawFunction GetForegroundDrawFunction(PaintWrapper* paintWrapper) override;

private:
    RefPtr<WebContentModifier> WebContentModifier_;
    RefPtr<NG::RenderSurface> renderSuface_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WEB_PAINT_METHOD_H