/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_FRAME_NODE_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_FRAME_NODE_H

#include <functional>
#include <list>
#include <optional>
#include <string>

#include "ui/base/ace_type.h"
#include "ui/base/referenced.h"
#include "ui/properties/dirty_flag.h"
#include "ui/resource/resource_configuration.h"
#include "ui/view/layout/layout_info.h"

namespace OHOS::Ace::NG {
class LayoutProperty;
template<class T>
struct LayoutConstraintT;
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::Kit {

class Pattern;
class UIContext;
class Property;
using NodeHandle = void*;

class FrameNode : public AceType {
    DECLARE_ACE_TYPE(FrameNode, AceType);

public:
    FrameNode() = default;
    virtual ~FrameNode() = default;

    virtual void InitializePatternAndContext() = 0;
    virtual void Reset() = 0;

    virtual void Measure(const Kit::LayoutConstraintInfo& parentContraint) = 0;
    virtual void Layout() = 0;

    virtual RefPtr<NG::LayoutProperty> GetLayoutProperty() = 0;
    virtual RefPtr<Pattern> GetPattern() = 0;
    virtual RefPtr<Property> GetProperty() = 0;
    virtual NodeHandle GetHandle() = 0;

    virtual void AddChild(const RefPtr<FrameNode>& child) = 0;
    virtual std::list<RefPtr<FrameNode>> GetChildren() = 0;
    virtual void MarkDirtyNode(NG::PropertyChangeFlag flag = NG::PROPERTY_UPDATE_NORMAL) = 0;
    virtual void RemoveChild(const RefPtr<FrameNode>& child) = 0;

    virtual std::string GetTag() const = 0;
    virtual int32_t GetId() const = 0;

    virtual void MeasureChildren() = 0;
    virtual void LayoutChildren() = 0;
    virtual void SetOnNodeDestroyCallback(const std::function<void(RefPtr<FrameNode>)>& destroyCallback) = 0;
    virtual void SetConfigurationUpdateCallback(
        const std::function<void(const ConfigurationChange& configurationChange)>&& callback) = 0;
    virtual void AddExtraCustomProperty(const std::string& key, void* extraData) = 0;
    virtual void* GetExtraCustomProperty(const std::string& key) const = 0;
    virtual void SetClipEdge(bool isClip) = 0;

    virtual RefPtr<UIContext> GetUIContext() const = 0;
};
} // namespace OHOS::Ace::Kit

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_FRAME_NODE_H
