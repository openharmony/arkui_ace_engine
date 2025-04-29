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
#include "bridge/cj_frontend/cppview/search_controller.h"

namespace OHOS::Ace::Framework {

void SearchController::CaretPosition(int32_t caretPosition)
{
    auto controller = controller_.Upgrade();
    if (controller) {
        controller->CaretPosition(caretPosition);
    } else {
        LOGW("CaretPosition failed, controller is null.");
    }
}

void SearchController::StopEditing()
{
    auto controller = controller_.Upgrade();
    if (controller) {
        controller->StopEditing();
    } else {
        LOGW("StopEditing failed, controller is null.");
    }
}

void SearchController::SetTextSelection(
    int32_t selectionStart, int32_t selectionEnd, const std::optional<SelectionOptions>& options)
{
    auto controller = controller_.Upgrade();
    if (controller) {
        controller->SetTextSelection(selectionStart, selectionEnd, options);
    } else {
        LOGW("SetTextSelection failed, controller is null.");
    }
}

int32_t SearchController::GetTextContentLinesNum()
{
    int32_t linesNum = -1;
    auto controller = controller_.Upgrade();
    if (controller) {
        linesNum = controller->GetTextContentLinesNum();
    }
    return linesNum;
}

CJRectResult SearchController::GetTextContentRect()
{
    CJRectResult result;
    auto controller = controller_.Upgrade();
    if (controller) {
        Rect rect = controller->GetTextContentRect();
        result.x = rect.Left();
        result.y = rect.Top();
        result.width = rect.Width();
        result.height = rect.Height();
    }
    return result;
}

CJCaretOffset SearchController::GetCaretOffset()
{
    CJCaretOffset result;
    auto controller = controller_.Upgrade();
    if (controller) {
        NG::OffsetF caretOffset = controller->GetCaretPosition();
        result.index = controller->GetCaretIndex();
        result.x = caretOffset.GetX();
        result.y = caretOffset.GetY();
    }
    return result;
}

} // namespace OHOS::Ace::Framework
