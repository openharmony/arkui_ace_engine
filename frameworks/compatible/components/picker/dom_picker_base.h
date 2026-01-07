/*
 * Copyright (c) 2021-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_PICKER_DOM_PICKER_BASE_H
#define FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_PICKER_DOM_PICKER_BASE_H

#include "compatible/components/picker/picker_date_component.h"
#include "compatible/components/picker/picker_datetime_component.h"
#include "compatible/components/picker/picker_multitext_component.h"
#include "compatible/components/picker/picker_text_component.h"
#include "compatible/components/picker/picker_time_component.h"
#include "compatible/components/picker/picker_value_component.h"

#include "core/components_ng/pattern/picker/picker_theme.h"
#include "core/components/text/text_component.h"
#include "core/components/theme/theme_manager.h"
#include "frameworks/bridge/common/dom/dom_node.h"

namespace OHOS::Ace::Framework {
extern const char DOM_PICKER_SPLIT_ITEM;
extern const char DOM_PICKER_SPLIT_ARRAY;
extern const char DOM_PICKER_CONTAIN_SECOND[];
extern const char DOM_PICKER_RANGE[];
extern const char DOM_PICKER_COLUMN_CHANGE[];
extern const char DOM_PICKER_COLUMN_COUNT[];
extern const char DOM_PICKER_HOUR24[];
extern const char DOM_PICKER_LUNAR[];
extern const char DOM_PICKER_SHOW_LUNAR[];
extern const char DOM_PICKER_TYPE_TIME[];
extern const char DOM_PICKER_TYPE_DATE[];
extern const char DOM_PICKER_TYPE_TEXT[];
extern const char DOM_PICKER_TYPE_MULTITEXT[];
extern const char DOM_PICKER_TYPE_DATETIME[];
extern const char DOM_PICKER_TEXT_COLOR[];
extern const char DOM_PICKER_SELECT_COLOR[];
extern const char DOM_PICKER_SELECT_SIZE[];
extern const char DOM_PICKER_SELECT_FAMILIES[];
extern const char DOM_PICKER_FOCUS_COLOR[];
extern const char DOM_PICKER_FOCUS_SIZE[];
extern const char DOM_PICKER_FOCUS_FAMILIES[];
extern const char DOM_PICKER_PREFIX[];
extern const char DOM_PICKER_SUFFIX[];
extern const char DOM_PICKER_DISAPPEAR_COLOR[];
extern const char DOM_PICKER_DISAPPEAR_FONT_SIZE[];
extern const char DOM_PICKER_COLUMN_HEIGHT[];
extern const char DOM_PICKER_VIBRATE[];
extern const char DOM_VALUE[];
extern const char DOM_TYPE[];
extern const char DOM_BACKGROUND_COLOR[];
extern const char DOM_ROTATION[];
extern const char DOM_SHOW[];
extern const char DOM_END[];
extern const char DOM_SELECTED[];
extern const char DOM_START[];
extern const char DOM_CANCEL[];
extern const char DOM_CHANGE[];
extern const char DOM_TEXT_COLOR[];
extern const char DOM_TEXT_FONT_FAMILY[];
extern const char DOM_TEXT_FONT_SIZE[];
extern const char DOM_TEXT_FONT_STYLE[];
extern const char DOM_TEXT_FONT_WEIGHT[];
extern const char DOM_TEXT_LETTER_SPACING[];
extern const char DOM_TEXT_LINE_HEIGHT[];
extern const char DOM_TEXT_DECORATION[];

class DOMPickerBase : public DOMNode {
    DECLARE_ACE_TYPE(DOMPickerBase, DOMNode);

public:
    DOMPickerBase(NodeId nodeId, const std::string& nodeName, bool hasValue);
    ~DOMPickerBase() override = default;

    RefPtr<Component> GetSpecializedComponent() override;

    void InitializeStyle() override;

    void ResetInitializedStyle() override;

    bool SetStart(const std::string& value);
    bool SetEnd(const std::string& value);
    bool SetSelected(const std::string& value);
    bool SetHasSecond(const std::string& value);
    bool SetRange(const std::string& value);
    bool SetColumnCount(const std::string& value);
    bool SetHour24(const std::string& value);
    bool SetLunar(const std::string& value);
    bool SetShowLunar(const std::string& value);
    bool SetPrefix(const std::string& value);
    bool SetSuffix(const std::string& value);
    bool SetVibrate(const std::string& value);

protected:
    bool SetSpecializedAttr(const std::pair<std::string, std::string>& attr) override;
    bool AddSpecializedEvent(int32_t pageId, const std::string& event) override;
    bool SetSpecializedStyle(const std::pair<std::string, std::string>& style) override;
    void CallSpecializedMethod(const std::string& method, const std::string& args) override;
    void CompositeComponents() override;
    void PrepareSpecializedComponent() override;

private:
    void HandleClickCallback() const;

    void ShowDialog() const;

    bool GetPickerDate(const std::string& strDate, PickerDate& outDate) const;
    bool GetPickerTime(const std::string& strDate, PickerTime& outTime) const;
    bool GetPickerDateTime(const std::string& strDate, PickerDateTime& outDateTime) const;

    bool CreatePicker();

    bool SetTextSelected(const std::string& value);

    bool SetDateTimeSelected(const std::string& value);

    bool SetOptionStyleOperators(const std::pair<std::string, std::string>& style);

    bool SetTextStyleOperators(const std::pair<std::string, std::string>& style);

    bool SetTextBackgroundColor(const std::pair<std::string, std::string>& style);
    bool SetColumnHeight(const std::pair<std::string, std::string>& style);

    bool hasValue_ = true;
    // used for inspector node in PC preview
    int32_t pickerId_ = -1;
    std::string type_ { DOM_PICKER_TYPE_TEXT };

    std::list<std::pair<std::string, std::string>> storeAttributes_;
    std::list<std::pair<int32_t, std::string>> storeEvents_;
    std::list<std::pair<std::string, std::string>> storeStyles_;

    RefPtr<PickerTheme> theme_;
    RefPtr<PickerBaseComponent> basePickerChild_;
    RefPtr<PickerValueComponent> valuePickerChild_;
};

} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_PICKER_DOM_PICKER_BASE_H
