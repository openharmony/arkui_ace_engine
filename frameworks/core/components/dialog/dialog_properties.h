/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_ACE_ENGINE_FRAMEWORKS_CORE_COMPONENTS_COMMON_PROPERTIES_DIALOG_PROPERTIES_H
#define FOUNDATION_ACE_ACE_ENGINE_FRAMEWORKS_CORE_COMPONENTS_COMMON_PROPERTIES_DIALOG_PROPERTIES_H

#include <cstdint>

#include "base/geometry/dimension_offset.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/event/click_event.h"
#include "core/components_ng/property/border_property.h"
#include "core/event/ace_event_handler.h"
#include "core/gestures/gesture_info.h"
#include "core/pipeline/base/component.h"

namespace OHOS::Ace {

enum class DialogType {
    COMMON = 0,
    ALERT_DIALOG,
    ACTION_SHEET,
    CHECKBOX_DIALOG,
    PROGRESS_DIALOG,
};

enum class DialogButtonStyle {
    DEFAULT = 0,
    HIGHTLIGHT,
};

// Alignment of dialog in vertical.
enum class DialogAlignment {
    TOP = 0,
    CENTER,
    BOTTOM,
    DEFAULT,
    TOP_START,
    TOP_END,
    CENTER_START,
    CENTER_END,
    BOTTOM_START,
    BOTTOM_END,
};

// Direction of buttons in dialog
enum class DialogButtonDirection {
    AUTO = 0,
    HORIZONTAL,
    VERTICAL,
};

class DialogAlignmentUtils {
public:
    static std::string ConvertDialogAlignmentToString(DialogAlignment dialogAlignment)
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
};

class DialogButtonDirectionUtils {
public:
    static std::string ConvertDialogButtonDirectionToString(DialogButtonDirection buttonDirection)
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
};

// Information of ActionSheet
struct ActionSheetInfo {
    std::string title;             // title of ActionSheet, necessary.
    std::string icon;              // icon of ActionSheet, not necessary.
    RefPtr<Gesture> gesture;       // called when ActionSheet is clicked.
    RefPtr<NG::ClickEvent> action; // NG sheet item click action

    // Whether sheetInfo is valid, valid if title if not empty.
    bool IsValid() const
    {
        return !title.empty();
    }
};

// Information of Button.
struct ButtonInfo {
    std::string text;              // text of button.
    std::string textColor;         // style of text in button.
    bool isBgColorSetted = false;
    Color bgColor;                 // background color of button.
    RefPtr<NG::ClickEvent> action; // NG button click action
    bool enabled = true;                             // status of enabled in button.
    bool defaultFocus = false;                       // status of defaultFocus in button.
    std::optional<DialogButtonStyle> dlgButtonStyle; // DialogButtonStyle of dialog.

    // Whether button info is valid, valid if text is not empty.
    bool IsValid() const
    {
        return !text.empty();
    }
};

struct DialogProperties {
    DialogType type = DialogType::COMMON; // type of dialog, current support common dialog and alert dialog.
    std::string title;                    // title of dialog.
    std::string subtitle;                 // subtitle of dialog.
    std::string content;                  // message of dialog.
    std::string checkboxContent;          // message of checkbox.
    bool autoCancel = true;               // pop dialog when click mask if autoCancel is true.
    bool customStyle = false;             // when true, dialog doesn't paint background or constraint child size.
    bool isMenu = false;
    bool isSelect = false;                // init checkbox state
    std::vector<ButtonInfo> buttons;
    std::function<void()> onCancel;       // NG cancel callback
    std::function<void(int32_t, int32_t)> onSuccess;      // NG prompt success callback
    std::function<void(const bool)> onChange;             // onChange success callback
    DialogAlignment alignment = DialogAlignment::DEFAULT; // Alignment of dialog.
    DimensionOffset offset;                               // Offset which base on alignment of Dialog.
    int32_t gridCount = -1;
    std::optional<Color> maskColor;
    std::optional<Color> backgroundColor;
    std::optional<NG::BorderRadiusProperty> borderRadius;
    std::optional<AnimationOption> openAnimation;
    std::optional<AnimationOption> closeAnimation;
    bool isShowInSubWindow = false;
    DialogButtonDirection buttonDirection = DialogButtonDirection::AUTO;

#ifndef NG_BUILD
    std::unordered_map<std::string, EventMarker> callbacks; // <callback type(success, cancel, complete), eventId>
    // These ids is used for AlertDialog of declarative.
    EventMarker primaryId;   // first button's callback.
    EventMarker secondaryId; // second button's callback.
#endif

    // These attributes is used for CustomDialog.
    RefPtr<AceType> customComponent;         // Used for CustomDialog in declarative.
    std::function<void(bool)> onStatusChanged; // Called when dialog appear or disappear.

    // These attributes is used for ActionSheet.
    std::vector<ActionSheetInfo> sheetsInfo;

    WeakPtr<NG::UINode> windowScene;
    std::optional<DimensionRect> maskRect;
};

struct PromptDialogAttr {
    std::string title;
    std::string message;
    bool autoCancel = true;

    std::optional<DialogAlignment> alignment;
    std::optional<DimensionOffset> offset;
    std::optional<DimensionRect> maskRect;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ACE_ENGINE_FRAMEWORKS_CORE_COMPONENTS_COMMON_PROPERTIES_DIALOG_PROPERTIES_H
