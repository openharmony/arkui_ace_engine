/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_THEME_MOCK_THEME_DEFAULT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_THEME_MOCK_THEME_DEFAULT_H

#include "gmock/gmock.h"

#include "core/components/picker/picker_theme.h"

namespace OHOS::Ace {
class ACE_EXPORT MockThemeDefault {
public:
    MockThemeDefault() = delete;
    ~MockThemeDefault() = delete;

    static RefPtr<PickerTheme> GetPickerTheme()
    {
        auto pickerTheme = AceType::MakeRefPtr<PickerTheme>();
        pickerTheme->showOptionCount_ = 5;
        pickerTheme->focusColor_ = Color::FromString("#FFFF0000");
        pickerTheme->showOptionCount_ = 5;
        pickerTheme->showButtons_ = true;
        pickerTheme->buttonWidth_ = Dimension(10.0, DimensionUnit::PX);
        pickerTheme->buttonHeight_ = Dimension(10.0, DimensionUnit::PX);
        pickerTheme->buttonTopPadding_ = Dimension(10.0, DimensionUnit::PX);
        pickerTheme->jumpInterval_ = Dimension(10.0, DimensionUnit::PX);
        pickerTheme->columnIntervalMargin_ = Dimension(10.0, DimensionUnit::PX);
        pickerTheme->optionPadding_ = 0.0;
        pickerTheme->titleBottomPadding_ = Dimension(10.0, DimensionUnit::PX);
        pickerTheme->lunarWidth_ = Dimension(36.0, DimensionUnit::VP);
        pickerTheme->lunarHeight_ = Dimension(18.0, DimensionUnit::VP);
        pickerTheme->timeSplitter_ = 5;
        pickerTheme->rotateInterval_ = 15.0;
        pickerTheme->dividerThickness_ = Dimension(1.0, DimensionUnit::PX);
        pickerTheme->dividerSpacing_ = Dimension(10.0, DimensionUnit::PX);
        pickerTheme->dividerColor_ = Color::FromString("#FFFF0000");
        pickerTheme->gradientHeight_ = Dimension(10.0, DimensionUnit::PX);
        pickerTheme->columnFixedWidth_ = Dimension(10.0, DimensionUnit::PX);
        pickerTheme->pressColor_ = Color::FromString("#FFFF0000");
        pickerTheme->hoverColor_ = Color::FromString("#FF000000");
        pickerTheme->lunarswitchTextColor_ = Color::FromString("#FF000000");
        return pickerTheme;
    }
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_THEME_MOCK_THEME_DEFAULT_H
