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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_MENU_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_MENU_MODEL_IMPL_H

#include "frameworks/core/components_ng/pattern/menu/menu_model.h"

namespace OHOS::Ace::Framework {
class MenuModelImpl : public MenuModel {
public:
    void Create() override;
    void SetFontSize(const Dimension& fontSize) override;
    void SetFontWeight(FontWeight weight) override;
    void SetFontStyle(Ace::FontStyle style) override;
    void SetFontColor(const std::optional<Color>& color) override;
    void SetWidth(const Dimension& width) override;
    void SetBorderRadius(const Dimension& radius) override;
    void SetBorderRadius(const std::optional<Dimension>& radiusTopLeft, const std::optional<Dimension>& radiusTopRight,
        const std::optional<Dimension>& radiusBottomLeft,
        const std::optional<Dimension>& radiusBottomRight) override;
    void SetFontFamily(const std::vector<std::string> &families) override;
    void SetItemDivider(const V2::ItemDivider& divider, const DividerMode& mode) override;
    void SetItemGroupDivider(const V2::ItemDivider& divider, const DividerMode& mode) override;
    void CreateWithColorResourceObj(
        const RefPtr<ResourceObject>& resObj, const MenuColorType menuColorType) override {};
    void CreateWithDimensionResourceObj(
        const RefPtr<ResourceObject>& resObj, const MenuDimensionType menuDimensionType) override {};
    void CreateWithFontFamilyResourceObj(const RefPtr<ResourceObject>& resObj, MenuFamilyType type) override {};
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_MENU_MODEL_IMPL_H
