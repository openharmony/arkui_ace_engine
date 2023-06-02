/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SEARCH_ROSEN_RENDER_SEARCH_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SEARCH_ROSEN_RENDER_SEARCH_H

#ifndef USE_ROSEN_DRAWING
#include "include/core/SkCanvas.h"
#endif

#include "core/components/search/render_search.h"
#include "core/pipeline/base/rosen_render_context.h"

namespace OHOS::Ace {

class RosenRenderSearch : public RenderSearch {
    DECLARE_ACE_TYPE(RosenRenderSearch, RenderSearch);

public:
    void Paint(RenderContext& context, const Offset& offset) override;

private:
    void PaintFocus();
    void PaintOverlayForHoverAndPress(RenderContext& context, const Offset& offset);
#ifndef USE_ROSEN_DRAWING
    SkRRect MakeRRect(const Offset& offset, const Size& size, const Border& border);
    SkCanvas* GetSkCanvas(RenderContext& context);
#else
    RSRoundRect MakeRRect(const Offset& offset, const Size& size, const Border& border);
    RSCanvas* GetDrawingCanvas(RenderContext& context);
#endif
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SEARCH_ROSEN_RENDER_SEARCH_H
