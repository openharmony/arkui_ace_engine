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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SEARCH_SEARCH_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SEARCH_SEARCH_NODE_H

#include <optional>

#include "core/components_ng/base/group_node.h"

namespace OHOS::Ace::NG {
class IconOptions {
public:
    IconOptions(CalcDimension size) : size_(size)
    {}

    IconOptions(Color color, CalcDimension size) : color_(color), size_(size)
    {}

    IconOptions(std::string src, std::string bundleName = "", std::string moduleName = "")
        : src_(src), bundleName_(bundleName), moduleName_(moduleName)
    {}

    IconOptions(CalcDimension size, std::string src, std::string bundleName, std::string moduleName)
        : size_(size), src_(src), bundleName_(bundleName), moduleName_(moduleName)
    {}

    IconOptions(Color color, CalcDimension size, std::string src, std::string bundleName, std::string moduleName)
        : color_(color), size_(size), src_(src), bundleName_(bundleName), moduleName_(moduleName)
    {}

    IconOptions() = default;
    ~IconOptions() = default;

    std::optional<Color>& GetColor()
    {
        return color_;
    }

    std::optional<Dimension>& GetSize()
    {
        return size_;
    }

    std::optional<std::string>& GetSrc()
    {
        return src_;
    }

    std::optional<std::string>& GetBundleName()
    {
        return bundleName_;
    }

    std::optional<std::string>& GetModuleName()
    {
        return moduleName_;
    }

    void UpdateSrc(std::string src, std::string bundleName, std::string moduleName)
    {
        src_ = src;
        moduleName_ = moduleName;
        bundleName_ = bundleName;
    }

    void UpdateSize(Dimension size)
    {
        size_ = size;
    }

    void UpdateColor(Color color)
    {
        color_ = color;
    }

    bool operator==(const IconOptions& info) const
    {
        return color_ == info.color_ && size_ == info.size_ && src_ == info.src_ && bundleName_ == info.bundleName_ &&
               moduleName_ == info.moduleName_;
    }

    bool operator!=(const IconOptions& info) const
    {
        return !(operator==(info));
    }

    std::string ToString() const
    {
        auto json = JsonUtil::Create(true);
        if (src_.has_value()) {
            json->Put("src", src_.value().c_str());
        }
        if (bundleName_.has_value()) {
            json->Put("bundleName", bundleName_.value().c_str());
        }
        if (moduleName_.has_value()) {
            json->Put("moduleName", moduleName_.value().c_str());
        }
        if (size_.has_value()) {
            json->Put("size", size_.value().ToString().c_str());
        }
        if (color_.has_value()) {
            json->Put("color", color_.value().ToString().c_str());
        }
        return json->ToString();
    }

private:
    std::optional<Color> color_;
    std::optional<Dimension> size_;
    std::optional<std::string> src_;
    std::optional<std::string> bundleName_;
    std::optional<std::string> moduleName_;
};

class ACE_EXPORT SearchNode : public GroupNode {
    DECLARE_ACE_TYPE(SearchNode, GroupNode);

public:
    SearchNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot = false)
        : GroupNode(tag, nodeId, pattern, isRoot)
    {}
    ~SearchNode() override = default;

    void AddChildToGroup(const RefPtr<UINode>& child, int32_t slot = DEFAULT_NODE_SLOT) override;
    bool HasTextFieldNode() const
    {
        return textFieldId_.has_value();
    }

    bool HasSearchIconNodeCreated() const
    {
        return searchIconNodeCreated_;
    }

    bool HasButtonNode() const
    {
        return buttonId_.has_value();
    }

    bool HasDividerNode() const
    {
        return dividerId_.has_value();
    }

    bool HasCancelIconNodeCreated() const
    {
        return cancelIconNodeCreated_;
    }

    bool HasCancelButtonNode() const
    {
        return cancelButtonId_.has_value();
    }

    int32_t GetTextFieldId()
    {
        if (!textFieldId_.has_value()) {
            textFieldId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return textFieldId_.value();
    }

    int32_t GetButtonId()
    {
        if (!buttonId_.has_value()) {
            buttonId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return buttonId_.value();
    }

    int32_t GetCancelButtonId()
    {
        if (!cancelButtonId_.has_value()) {
            cancelButtonId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return cancelButtonId_.value();
    }

    int32_t GetDividerId()
    {
        if (!dividerId_.has_value()) {
            dividerId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return dividerId_.value();
    }

    Dimension& GetSearchImageIconSize()
    {
        return searchImageIconOptions_.GetSize().value();
    }

    Dimension& GetCancelImageIconSize()
    {
        return cancelImageIconOptions_.GetSize().value();
    }

    const Dimension& GetSearchSymbolIconSize() const
    {
        return searchSymbolIconSize_;
    }

    const Dimension& GetCancelSymbolIconSize() const
    {
        return cancelSymbolIconSize_;
    }

    const Color& GetSearchSymbolIconColor() const
    {
        return searchSymbolIconColor_;
    }

    const Color& GetCancelSymbolIconColor() const
    {
        return cancelSymbolIconColor_;
    }

    Color& GetSearchImageIconColor()
    {
        return searchImageIconOptions_.GetColor().value();
    }

    Color& GetCancelImageIconColor()
    {
        return cancelImageIconOptions_.GetColor().value();
    }

    IconOptions& GetSearchImageIconOptions()
    {
        return searchImageIconOptions_;
    }

    IconOptions& GetCancelImageIconOptions()
    {
        return cancelImageIconOptions_;
    }

    void SetSearchImageIconSize(Dimension searchIconSize)
    {
        searchImageIconOptions_.UpdateSize(searchIconSize);
    }

    void SetCancelImageIconSize(Dimension cancelIconSize)
    {
        cancelImageIconOptions_.UpdateSize(cancelIconSize);
    }

    void SetSearchSymbolIconSize(Dimension searchIconSize)
    {
        searchSymbolIconSize_ = searchIconSize;
    }

    void SetCancelSymbolIconSize(Dimension cancelIconSize)
    {
        cancelSymbolIconSize_ = cancelIconSize;
    }

    void SetSearchSymbolIconColor(Color searchIconColor)
    {
        searchSymbolIconColor_ = searchIconColor;
    }

    void SetCancelSymbolIconColor(Color cancelIconColor)
    {
        cancelSymbolIconColor_ = cancelIconColor;
    }

    void SetSearchImageIconColor(Color searchIconColor)
    {
        searchImageIconOptions_.UpdateColor(searchIconColor);
    }

    void SetCancelImageIconColor(Color cancelIconColor)
    {
        cancelImageIconOptions_.UpdateColor(cancelIconColor);
    }

    void SetSearchImageIconOptions(IconOptions options)
    {
        searchImageIconOptions_ = options;
    }

    void SetCancelImageIconOptions(IconOptions options)
    {
        cancelImageIconOptions_ = options;
    }

    void UpdateHasSearchIconNodeCreated(bool hasNodeCreated)
    {
        searchIconNodeCreated_ = hasNodeCreated;
    }

    void UpdateHasCancelIconNodeCreated(bool hasNodeCreated)
    {
        cancelIconNodeCreated_ = hasNodeCreated;
    }

private:
    std::optional<int32_t> textFieldId_;
    std::optional<int32_t> buttonId_;
    std::optional<int32_t> cancelButtonId_;
    std::optional<int32_t> dividerId_;

    std::set<int32_t> searchChildren_;

    Dimension searchSymbolIconSize_ = 16.0_fp;
    Color searchSymbolIconColor_;
    Dimension cancelSymbolIconSize_ = 16.0_fp;
    Color cancelSymbolIconColor_;
    bool searchIconNodeCreated_ = false;
    bool cancelIconNodeCreated_ = false;

    IconOptions searchImageIconOptions_ = IconOptions(16.0_vp);
    IconOptions cancelImageIconOptions_ = IconOptions(16.0_vp);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SEARCH_SEARCH_NODE_H