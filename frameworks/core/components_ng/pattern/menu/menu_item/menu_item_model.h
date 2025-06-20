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
#include "core/components/common/properties/text_style.h"

namespace OHOS::Ace {
enum class MenuItemFontColorType {
    FONT_COLOR,
    LABEL_FONT_COLOR
};
enum class MenuItemFontSizeType {
    FONT_SIZE,
    LABEL_FONT_SIZE
};
enum class MenuItemStringType {
    SELECT_ICON,
    CONTENT,
    LABEL_INFO
};
enum class MenuItemFontFamilyType {
    FONT_FAMILY,
    LABEL_FONT_FAMILY
};
enum class MenuItemIconType {
    START_ICON,
    END_ICON
};
template<typename T>
class ResourceHolder {
public:
    virtual ~ResourceHolder() = default;
    struct ResourceUpdater {
        RefPtr<ResourceObject> resObj;
        std::function<void(const RefPtr<ResourceObject>&, T&)> updateFunc;
    };
    using ResourceMap = std::unordered_map<std::string, ResourceUpdater>;
    void AddResource(const std::string& key, const RefPtr<ResourceObject>& resObj,
        std::function<void(const RefPtr<ResourceObject>&, T&)>&& updateFunc)
    {
        if (resObj == nullptr || !updateFunc) {
            return;
        }
        resources_[key] = {resObj, std::move(updateFunc)};
    }
    const RefPtr<ResourceObject> GetResource(const std::string& key) const
    {
        auto it = resources_.find(key);
        return (it != resources_.end()) ? it->second.resObj : nullptr;
    }
    bool HasResources() const
    {
        return !resources_.empty();
    }
    void ReloadResources(T& context)
    {
        for (const auto& [key, updater] : resources_) {
            updater.updateFunc(updater.resObj, context);
        }
    }
protected:
    ResourceMap resources_;
};
struct MenuItemProperties : public ResourceHolder<MenuItemProperties> {
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
    virtual void CreateWithColorResourceObj(const RefPtr<ResourceObject>& resObj, MenuItemFontColorType type);
    virtual void CreateWithDimensionFpResourceObj(const RefPtr<ResourceObject>& resObj, MenuItemFontSizeType type);
    virtual void CreateWithFontFamilyResourceObj(const RefPtr<ResourceObject>& resObj, MenuItemFontFamilyType type);
    virtual void CreateWithStringResourceObj(const RefPtr<ResourceObject>& resObj, MenuItemStringType type);
    virtual void CreateWithMediaResourceObj(const RefPtr<ResourceObject>& resObj, const MenuItemIconType type);

private:
    static std::unique_ptr<MenuItemModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_MODEL_H
