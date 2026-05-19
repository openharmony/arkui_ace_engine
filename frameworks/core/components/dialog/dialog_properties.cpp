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

#include "core/components/dialog/dialog_properties.h"

namespace OHOS::Ace {

std::string DialogTypeUtils::ConvertDialogTypeToString(DialogType type)
{
    switch (type) {
        case DialogType::COMMON:
            return "DialogType.COMMON";
        case DialogType::ALERT_DIALOG:
            return "DialogType.ALERT_DIALOG";
        case DialogType::ACTION_SHEET:
            return "DialogType.ACTION_SHEET";
        case DialogType::CHECKBOX_DIALOG:
            return "DialogType.CHECKBOX_DIALOG";
        default:
            break;
    }
    return "DialogType.COMMON";
}

std::string DialogAlignmentUtils::ConvertDialogAlignmentToString(DialogAlignment dialogAlignment)
{
    std::string Alignment = "";
    switch (dialogAlignment) {
        case DialogAlignment::TOP:
            Alignment = "DialogAlignment.TOP";
            break;
        case DialogAlignment::CENTER:
            Alignment = "DialogAlignment.CENTER";
            break;
        case DialogAlignment::BOTTOM:
            Alignment = "DialogAlignment.BOTTOM";
            break;
        case DialogAlignment::TOP_START:
            Alignment = "DialogAlignment.TOP_START";
            break;
        case DialogAlignment::TOP_END:
            Alignment = "DialogAlignment.TOP_END";
            break;
        case DialogAlignment::CENTER_START:
            Alignment = "DialogAlignment.CENTER_START";
            break;
        case DialogAlignment::CENTER_END:
            Alignment = "DialogAlignment.CENTER_END";
            break;
        case DialogAlignment::BOTTOM_START:
            Alignment = "DialogAlignment.BOTTOM_START";
            break;
        case DialogAlignment::BOTTOM_END:
            Alignment = "DialogAlignment.BOTTOM_END";
            break;
        default:
            Alignment = "DialogAlignment.DEFAULT";
    }
    return Alignment;
}

std::string DialogButtonDirectionUtils::ConvertDialogButtonDirectionToString(DialogButtonDirection buttonDirection)
{
    std::string direction = "";
    switch (buttonDirection) {
        case DialogButtonDirection::HORIZONTAL:
            direction = "DialogButtonDirection.HORIZONTAL";
            break;
        case DialogButtonDirection::VERTICAL:
            direction = "DialogButtonDirection.VERTICAL";
            break;
        default:
            direction = "DialogButtonDirection.AUTO";
    }
    return direction;
}

} // namespace OHOS::Ace
