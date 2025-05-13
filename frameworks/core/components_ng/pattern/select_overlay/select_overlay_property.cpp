/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"

#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
Dimension SelectHandleInfo::GetDefaultLineWidth()
{
    const Dimension defaultLineWidth = 2.0_vp;
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, defaultLineWidth);
    auto theme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_RETURN(theme, defaultLineWidth);
    return theme->GetHandleLineWidth();
}

void SelectOverlayInfo::GetCallerNodeAncestorViewPort(RectF& viewPort)
{
    if (ancestorViewPort) {
        viewPort = ancestorViewPort.value();
    } else {
        auto frameNode = callerFrameNode.Upgrade();
        if (frameNode) {
            auto viewPortOption = frameNode->GetViewPort(true);
            if (viewPortOption.has_value()) {
                viewPort = viewPortOption.value();
            }
        }
    }
}

const RectF& SelectOverlayInfo::GetFirstHandlePaintRect()
{
    return handleLevelMode == HandleLevelMode::OVERLAY ? firstHandle.paintRect : firstHandle.localPaintRect;
}

const RectF& SelectOverlayInfo::GetSecondHandlePaintRect()
{
    return handleLevelMode == HandleLevelMode::OVERLAY ? secondHandle.paintRect : secondHandle.localPaintRect;
}

TextMenuShowMode CastToTextMenuShowMode(int32_t value)
{
    if (value <= static_cast<int32_t>(TextMenuShowMode::BEGIN) || value > static_cast<int32_t>(TextMenuShowMode::END)) {
        return TextMenuShowMode::DEFAULT;
    }
    return static_cast<TextMenuShowMode>(value);
}

namespace TextSystemMenu {
bool IsDisableMenuItem(SystemServiceMenuDisableFlag flag)
{
    auto textMenuInfo = AceApplicationInfo::GetInstance().GetTextMenuInfo();
    return (textMenuInfo.disableFlags & DISABLE_ALL_FLAG) == DISABLE_ALL_FLAG ||
           (textMenuInfo.disableFlags & flag) == flag;
}
DEFINE_MENU_CHECK_METHOD_IMPL(Translate, DISABLE_TRANSLATE_FLAG)
DEFINE_MENU_CHECK_METHOD_IMPL(Search, DISABLE_SEARCH_FLAG)
DEFINE_MENU_CHECK_METHOD_IMPL(Share, DISABLE_SHARE_FLAG)
DEFINE_MENU_CHECK_METHOD_IMPL(CameraInput, DISABLE_CAMERA_INPUT_FLAG)
DEFINE_MENU_CHECK_METHOD_IMPL(AIWriter, DISABLE_AI_WRITER_FLAG)
DEFINE_MENU_CHECK_METHOD_IMPL(CollaborationService, DISABLE_COLLABORATION_SERVICE_FLAG)
} // namespace MenuController
} // namespace OHOS::Ace::NG