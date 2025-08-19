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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_PATTERN_CONTENT_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_PATTERN_CONTENT_MODIFIER_H

#include <optional>
#include <vector>

#include "base/memory/ace_type.h"
#include "core/components_ng/base/modifier.h"
#ifdef USE_ROSEN_DRAWING
#include "core/components_ng/render/drawing.h"
#endif
#include "core/components_ng/render/render_surface.h"

namespace OHOS::Rosen {
class RSRecordingCanvas;
}

namespace OHOS::Ace::NG {
class Pattern;

class WebContentModifier : public ContentModifier {
    DECLARE_ACE_TYPE(WebContentModifier, ContentModifier);

public:
    WebContentModifier(RefPtr<NG::RenderSurface> renderSuface) : renderSuface_(renderSuface) {}
    ~WebContentModifier() override = default;
    void onDraw(DrawingContext& drawingContext) override;
    RefPtr<NG::RenderSurface> renderSuface_;
};
} // namespace OHOS::Ace::NG

#endif