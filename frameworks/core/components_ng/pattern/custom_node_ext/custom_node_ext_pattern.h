/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CUSTOM_NODE_EXT_CUSTOM_NODE_EXT_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CUSTOM_NODE_EXT_CUSTOM_NODE_EXT_PATTERN_H

#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/custom_node_ext/custom_node_ext_layout_algorithm.h"
#include "core/components_ng/pattern/custom_node_ext/custom_node_ext_modifier.h"
#include "core/components_ng/pattern/custom_node_ext/custom_node_ext_paint_method.h"

namespace OHOS::Ace::NG {
enum ConfigurationType {
    COLOR_MODE_UPDATE = 0,
    LANGUAGE_UPDATE = 1,
    DIRECTION_UPDATE = 2,
    DPI_UPDATE = 3,
    FONT_UPDATE = 4,
    ICON_UPDATE = 5,
    SKIN_UPDATE = 6,
    FONT_SCALE_UPDATE = 7,
};

class CustomNodeExtPattern : public Pattern {
    DECLARE_ACE_TYPE(CustomNodeExtPattern, Pattern);
public:
    CustomNodeExtPattern() = default;
    ~CustomNodeExtPattern() override = default;

    bool IsAtomicNode() const override
    {
        return isAtomic_;
    }

    void SetIsAtomic(bool isAtomic)
    {
        isAtomic_ = isAtomic;
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<CustomNodeExtLayoutAlgorithm>(measureCallback_, layoutCallback_);
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override;
    void SetMeasureCallback(std::function<void(LayoutConstraintF constraints)>&& onMeasure);
    void SetLayoutCallback(std::function<void(RectF rect)>&& onLayout);
    void SetContentDrawCallback(DrawFunction&& onContent);
    void SetForegroundDrawCallback(DrawFunction&& onForeground);
    void SetOverlayDrawCallback(DrawFunction&& onOverlay);

    void SetOnConfigUpdateCallback(std::function<void(ConfigurationType configType)>&& onConfigUpdate)
    {
        onConfigUpdate_ =  std::move(onConfigUpdate);
    }

    void SetOnModifyDoneCallback(std::function<void()>&& onModifyDone)
    {
        onModifyDoneCallback_ = std::move(onModifyDone);
    }

    void SetOnDirtyLayoutWrapperSwap(std::function<void(const DirtySwapConfig& config)>&& onDirtySwap)
    {
        onDirtySwap_ = std::move(onDirtySwap);
    }

    void OnModifyDone() override;
    void OnMountToParentDone() override {}
    bool OnDirtyLayoutWrapperSwap(
        const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void OnLanguageConfigurationUpdate() override;
    void OnColorConfigurationUpdate() override;
    void OnDirectionConfigurationUpdate() override;
    void OnDpiConfigurationUpdate() override;
    void OnIconConfigurationUpdate() override;
    void OnFontConfigurationUpdate() override;
    void OnFontScaleConfigurationUpdate() override;

    void OnAttachToMainTree() override {}
    void OnDetachFromMainTree() override {}
protected:
    void OnDetachFromFrameNode(FrameNode* frameNode) override {}
    void OnAttachToFrameNode() override {}
private:
    std::function<void(LayoutConstraintF constraints)> measureCallback_;
    std::function<void(RectF rect)> layoutCallback_;
    RefPtr<CustomNodeExtContentModifier> contentModifier_;
    RefPtr<CustomNodeExtForegroundModifier> foregroundModifier_;
    RefPtr<CustomNodeExtOverlayModifier> overlayModifier_;
    std::function<void(ConfigurationType configType)> onConfigUpdate_;
    std::function<void()> onModifyDoneCallback_;
    std::function<void(const DirtySwapConfig& config)> onDirtySwap_;

    bool isAtomic_ = true;
};
} // OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CUSTOM_NODE_EXT_CUSTOM_NODE_EXT_PATTERN_H