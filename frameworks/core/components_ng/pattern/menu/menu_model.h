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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_MODEL_H

#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_v2/list/list_properties.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT MenuModel {
public:
    static MenuModel* GetInstance();
    virtual ~MenuModel() = default;

    virtual void Create();
    virtual void SetFontSize(const Dimension& fontSize);
    virtual void SetFontWeight(FontWeight weight);
    virtual void SetFontStyle(Ace::FontStyle style);
    virtual void SetFontColor(const std::optional<Color>& color);
    virtual void SetFontFamily(const std::vector<std::string> &families);
    virtual void ResetFontFamily() {};
    virtual void SetWidth(const Dimension& width);
    virtual void SetBorderRadius(const Dimension& radius);
    virtual void ResetBorderRadius() {};
    virtual void SetBorderRadius(const std::optional<Dimension>& radiusTopLeft,
        const std::optional<Dimension>& radiusTopRight, const std::optional<Dimension>& radiusBottomLeft,
        const std::optional<Dimension>& radiusBottomRight);
    virtual void SetExpandingMode(const NG::SubMenuExpandingMode& expandingMode) {};
    virtual void SetItemDivider(const V2::ItemDivider& divider, const DividerMode& mode) = 0;
    virtual void SetItemGroupDivider(const V2::ItemDivider& divider, const DividerMode& mode) = 0;
private:
    static std::unique_ptr<MenuModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_MODEL_H
