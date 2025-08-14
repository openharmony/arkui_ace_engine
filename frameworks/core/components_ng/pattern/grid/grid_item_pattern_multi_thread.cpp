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

#include "core/components_ng/pattern/grid/grid_item_pattern.h"


#include "base/log/dump_log.h"
#include "base/utils/multi_thread.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
namespace OHOS::Ace::NG {
void GridItemPattern::OnAttachToFrameNodeMultiThread()
{
    // do nothing thread unsafe
}
void GridItemPattern::OnAttachToMainTreeMultiThread()
{
    if (gridItemStyle_ == GridItemStyle::PLAIN) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto pipeline = GetContext();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetTheme<GridItemTheme>();
        CHECK_NULL_VOID(theme);
        auto renderContext = host->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->UpdateBorderRadius(theme->GetGridItemBorderRadius());
    }
}
} // namespace OHOS::Ace::NG
