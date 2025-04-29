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

#include "bridge/declarative_frontend/jsview/models/menu_model_impl.h"

namespace OHOS::Ace::Framework {
void MenuModelImpl::Create() {}
void MenuModelImpl::SetFontSize(const Dimension& fontSize) {}
void MenuModelImpl::SetFontWeight(FontWeight weight) {}
void MenuModelImpl::SetFontStyle(Ace::FontStyle style) {}
void MenuModelImpl::SetFontColor(const std::optional<Color>& color) {}
void MenuModelImpl::SetFontFamily(const std::vector<std::string> &families) {}
void MenuModelImpl::SetWidth(const Dimension& width) {}
void MenuModelImpl::SetBorderRadius(const Dimension& radius) {}
void MenuModelImpl::SetBorderRadius(const std::optional<Dimension>& radiusTopLeft,
    const std::optional<Dimension>& radiusTopRight, const std::optional<Dimension>& radiusBottomLeft,
    const std::optional<Dimension>& radiusBottomRight) {}
void MenuModelImpl::SetItemDivider(const V2::ItemDivider& divider, const DividerMode& mode) {}
void MenuModelImpl::SetItemGroupDivider(const V2::ItemDivider& divider, const DividerMode& mode) {}
} // namespace OHOS::Ace::Framework
