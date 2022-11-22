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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_INDEXER_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_INDEXER_THEME_H

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"

namespace OHOS::Ace {
class IndexerTheme : public virtual Theme {
    DECLARE_ACE_TYPE(IndexerTheme, Theme);

public:
    ~IndexerTheme() = default;
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;
        RefPtr<IndexerTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<IndexerTheme> theme = AceType::Claim(new IndexerTheme());
            if (!themeConstants) {
                LOGE("Build AppTheme error, themeConstants is null!");
                return theme;
            }
            theme->color_ = themeConstants->GetColor(THEME_INDEXER_COLOR);
            theme->selectedColor_ = themeConstants->GetColor(THEME_INDEXER_SELECTED_COLOR);
            theme->popupColor_ = themeConstants->GetColor(THEME_INDEXER_POPUP_COLOR);
            theme->selectedBackgroundColor_ = themeConstants->GetColor(THEME_INDEXER_SELECT_BACKGROUND_COLOR);
            theme->popupBackgroundColor_ = themeConstants->GetColor(THEME_INDEXER_POPUP_BACKGROUND_COLOR);
            theme->font_.SetFontSize(themeConstants->GetDimension(THEME_INDEXER_FONT_SIZE));
            theme->popupFont_.SetFontSize(themeConstants->GetDimension(THEME_INDEXER_POPUP_FONT_SIZE));
            theme->selectedFont_.SetFontSize(themeConstants->GetDimension(THEME_INDEXER_SELECTED_FONT_SIZE));
            return theme;
        }
    };
    const Color& GetColor() const
    {
        return color_;
    }
    const Color& GetSelectedColor() const
    {
        return selectedColor_;
    }
    const Color& GetPopupColor() const
    {
        return popupColor_;
    }
    const Color& GetPopupBackgroundColor() const
    {
        return popupBackgroundColor_;
    }
    const Color& GetSeclectedBackgroundColor() const
    {
        return selectedBackgroundColor_;
    }
    const TextStyle& GetSelectedFont() const
    {
        return selectedFont_;
    }
    const TextStyle& GetPopupFont() const
    {
        return popupFont_;
    }
    const TextStyle& GetFont() const
    {
        return font_;
    }

protected:
    IndexerTheme() = default;

    Color color_;
    Color selectedColor_;
    Color popupColor_;
    Color selectedBackgroundColor_;
    Color popupBackgroundColor_;
    TextStyle selectedFont_;
    TextStyle popupFont_;
    TextStyle font_;
};
} // namespace OHOS::Ace
#endif