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

#include "core/components_ng/manager/avoid_info/avoid_info_manager.h"
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

class CustomNodeExtPattern : public Pattern, public IAvoidInfoListener {
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
    
    void SetOnWindowFocusedCallback(std::function<void()>&& onWindowFocusedCallback)
    {
        onWindowFocusedCallback_ = std::move(onWindowFocusedCallback);
    }
    
    void SetOnWindowUnfocusedCallback(std::function<void()>&& onWindowUnfocusedCallback)
    {
        onWindowUnfocusedCallback_ = std::move(onWindowUnfocusedCallback);
    }
    
    void SetOnAttachToMainTreeCallback(std::function<void()>&& onAttachToMainTreeCallback)
    {
        onAttachToMainTreeCallback_ = std::move(onAttachToMainTreeCallback);
    }
    
    void SetOnDetachFromMainTreeCallback(std::function<void()>&& onDetachFromMainTreeCallback)
    {
        onDetachFromMainTreeCallback_ = std::move(onDetachFromMainTreeCallback);
    }
    
    void SetOnAvoidInfoChangeCallback(std::function<void()>&& onAvoidInfoChangeCallback)
    {
        onAvoidInfoChangeCallback_ = std::move(onAvoidInfoChangeCallback);
    }
    
    void SetIsNeedRegisterAvoidInfoChangeListener(bool isNeedRegisterAvoidInfoChangeListener)
    {
        isNeedRegisterAvoidInfoChangeListener_ = isNeedRegisterAvoidInfoChangeListener;
    }

    void SetOnDirtyLayoutWrapperSwap(std::function<void(const DirtySwapConfig& config)>&& onDirtySwap)
    {
        onDirtySwap_ = std::move(onDirtySwap);
    }
    void SetBeforeCreateLayoutWrapperCallback(std::function<void()>&& beforeCreateLayoutWrapper)
    {
        beforeCreateLayoutWrapperCallback_ = std::move(beforeCreateLayoutWrapper);
    }

    void OnModifyDone() override;
    void OnWindowFocused() override;
    void OnWindowUnfocused() override;
    void OnAvoidInfoChange(const ContainerModalAvoidInfo& info) override;
    void RegisterAvoidInfoChangeListener(const RefPtr<FrameNode>& hostNode);
    void UnregisterAvoidInfoChangeListener(const RefPtr<FrameNode>& hostNode);
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

    void OnAttachToMainTree() override;
    void OnDetachFromMainTree() override;
    void BeforeCreateLayoutWrapper() override;
protected:
    void OnDetachFromFrameNode(FrameNode* frameNode) override;
    void OnAttachToFrameNode() override;
private:
    std::function<void(LayoutConstraintF constraints)> measureCallback_;
    std::function<void(RectF rect)> layoutCallback_;
    RefPtr<CustomNodeExtContentModifier> contentModifier_;
    RefPtr<CustomNodeExtForegroundModifier> foregroundModifier_;
    RefPtr<CustomNodeExtOverlayModifier> overlayModifier_;
    std::function<void(ConfigurationType configType)> onConfigUpdate_;
    std::function<void()> onModifyDoneCallback_;
    std::function<void(const DirtySwapConfig& config)> onDirtySwap_;
    std::function<void()> onWindowFocusedCallback_;
    std::function<void()> onWindowUnfocusedCallback_;
    std::function<void()> onAttachToMainTreeCallback_;
    std::function<void()> onDetachFromMainTreeCallback_;
    std::function<void()> onAvoidInfoChangeCallback_;
    std::function<void()> beforeCreateLayoutWrapperCallback_;

    bool isNeedRegisterAvoidInfoChangeListener_ = false;
    
    bool isAtomic_ = true;
};
} // OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CUSTOM_NODE_EXT_CUSTOM_NODE_EXT_PATTERN_H