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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_MENU_ITEM_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_MENU_ITEM_MODEL_IMPL_H

#include "frameworks/core/components_ng/pattern/menu/menu_item/menu_item_model.h"

namespace OHOS::Ace::Framework {
class MenuItemModelImpl : public MenuItemModel {
public:
    void Create(const RefPtr<NG::UINode>& customNode) override;
    void Create(const MenuItemProperties& props) override;
    void SetSelected(bool isSelected = false) override;
    void SetSelectIcon(bool isShow = false) override;
    void SetSelectIconSymbol(std::function<void(WeakPtr<NG::FrameNode>)> &&symbolApply) override;
    void SetSelectIconSrc(const std::string& src) override;
    void SetOnChange(std::function<void(bool)>&& onChange) override;
    void SetFontSize(const Dimension& fontSize) override;
    void SetFontWeight(FontWeight weight) override;
    void SetFontStyle(Ace::FontStyle style) override;
    void SetFontColor(const std::optional<Color>& color) override;
    void SetFontFamily(const std::vector<std::string> &families) override;
    void SetLabelFontSize(const Dimension& fontSize) override;
    void SetLabelFontWeight(FontWeight weight) override;
    void SetLabelFontStyle(Ace::FontStyle style) override;
    void SetLabelFontColor(const std::optional<Color>& color) override;
    void SetLabelFontFamily(const std::vector<std::string> &families) override;
    void SetSelectedChangeEvent(std::function<void(bool)>&& selectedChangeEvent) override;
    void CreateWithColorResourceObj(const RefPtr<ResourceObject>& resObj, MenuItemFontColorType type) override {};
    void CreateWithDimensionFpResourceObj(
        const RefPtr<ResourceObject>& resObj, MenuItemFontSizeType type) override {};
    void CreateWithFontFamilyResourceObj(const RefPtr<ResourceObject>& resObj, MenuItemFontFamilyType type) override {};
    void CreateWithStringResourceObj(const RefPtr<ResourceObject>& resObj, MenuItemStringType type) override {};
    void CreateWithMediaResourceObj(const RefPtr<ResourceObject>& resObj, const MenuItemIconType type) override {};
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_MENU_ITEM_MODEL_IMPL_H
