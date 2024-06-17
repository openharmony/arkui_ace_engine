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

#include "bridge/declarative_frontend/jsview/models/menu_item_model_impl.h"

namespace OHOS::Ace::Framework {
void MenuItemModelImpl::Create(const RefPtr<NG::UINode>& customNode) {}

void MenuItemModelImpl::Create(const MenuItemProperties& props) {}

void MenuItemModelImpl::SetSelected(bool isSelected) {}

void MenuItemModelImpl::SetSelectIcon(bool isShow) {}

void MenuItemModelImpl::SetSelectIconSymbol(std::function<void(WeakPtr<NG::FrameNode>)>&& symbolApply) {}

void MenuItemModelImpl::SetSelectIconSrc(const std::string& src) {}

void MenuItemModelImpl::SetOnChange(std::function<void(bool)>&& onChange) {}

void MenuItemModelImpl::SetFontSize(const Dimension& fontSize) {}

void MenuItemModelImpl::SetFontWeight(FontWeight weight) {}

void MenuItemModelImpl::SetFontStyle(Ace::FontStyle style) {}

void MenuItemModelImpl::SetFontColor(const std::optional<Color>& color) {}

void MenuItemModelImpl::SetFontFamily(const std::vector<std::string> &families) {}

void MenuItemModelImpl::SetLabelFontSize(const Dimension& fontSize) {}

void MenuItemModelImpl::SetLabelFontWeight(FontWeight weight) {}

void MenuItemModelImpl::SetLabelFontStyle(Ace::FontStyle style) {}

void MenuItemModelImpl::SetLabelFontColor(const std::optional<Color>& color) {}

void MenuItemModelImpl::SetLabelFontFamily(const std::vector<std::string> &families) {}

void MenuItemModelImpl::SetSelectedChangeEvent(std::function<void(bool)>&& selectedChangeEvent) {}
} // namespace OHOS::Ace::Framework
