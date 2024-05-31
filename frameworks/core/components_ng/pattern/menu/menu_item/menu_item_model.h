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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_MODEL_H

#include <functional>
#include <optional>

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace {
struct MenuItemProperties {
    std::string content;
    std::optional<ImageSourceInfo> startIcon;
    std::optional<ImageSourceInfo> endIcon;
    std::optional<std::string> labelInfo;
    std::optional<std::function<void()>> buildFunc;
    std::function<void(WeakPtr<NG::FrameNode>)> startApply;
    std::function<void(WeakPtr<NG::FrameNode>)> endApply;
};
class ACE_FORCE_EXPORT MenuItemModel {
public:
    static MenuItemModel* GetInstance();
    virtual ~MenuItemModel() = default;

    // createMenuItem with custom
    virtual void Create(const RefPtr<NG::UINode>& customNode);
    virtual void Create(const MenuItemProperties& props);
    virtual void SetSelected(bool isSelected = false);
    virtual void SetSelectIcon(bool isShow = false);
    virtual void SetSelectIconSymbol(std::function<void(WeakPtr<NG::FrameNode>)> &&symbolApply);
    virtual void SetSelectIconSrc(const std::string& src);
    virtual void SetOnChange(std::function<void(bool)>&& onChange);
    virtual void SetFontSize(const Dimension& fontSize);
    virtual void SetFontWeight(FontWeight weight);
    virtual void SetFontStyle(Ace::FontStyle style);
    virtual void SetFontColor(const std::optional<Color>& color);
    virtual void SetFontFamily(const std::vector<std::string>& families);
    virtual void SetLabelFontSize(const Dimension& fontSize);
    virtual void SetLabelFontWeight(FontWeight weight);
    virtual void SetLabelFontStyle(Ace::FontStyle style);
    virtual void SetLabelFontColor(const std::optional<Color>& color);
    virtual void SetLabelFontFamily(const std::vector<std::string>& families);
    virtual void SetSelectedChangeEvent(std::function<void(bool)>&& selectedChangeEvent);

private:
    static std::unique_ptr<MenuItemModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_MODEL_H
