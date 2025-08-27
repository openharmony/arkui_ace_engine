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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ATOMIC_SERVICE_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ATOMIC_SERVICE_PATTERN_H

#include <cstddef>
#include "core/components_ng/pattern/app_bar/app_bar_theme.h"
#include "core/components_ng/pattern/app_bar/atomic_service_layout_algorithm.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/custom/custom_app_bar_node.h"

namespace OHOS::Ace::NG {
class AtomicServicePattern : public LinearLayoutPattern {
    DECLARE_ACE_TYPE(AtomicServicePattern, LinearLayoutPattern);
    ACE_DISALLOW_COPY_AND_MOVE(AtomicServicePattern);

public:
    AtomicServicePattern() : LinearLayoutPattern(true) {};
    ~AtomicServicePattern() override = default;

    void OnAttachToFrameNode() override;
    void BeforeCreateLayoutWrapper() override;
    void OnColorConfigurationUpdate() override;
    void OnLanguageConfigurationUpdate() override;
    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<AtomicServiceLayoutAlgorithm>();
    }
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>&, const DirtySwapConfig&) override;
    RefPtr<CustomAppBarNode> GetJSAppBarContainer();
    RefPtr<FrameNode> GetStageNodeWrapper();
    RefPtr<FrameNode> GetContent();
    RefPtr<FrameNode> GetMenuBarRow();
    RefPtr<FrameNode> GetMenuBar();
    RefPtr<FrameNode> GetMenuButton();
    RefPtr<FrameNode> GetDivider();
    RefPtr<FrameNode> GetCloseButton();
    RefPtr<FrameNode> GetMenuIcon();
    RefPtr<FrameNode> GetCloseIcon();
    void UpdateColor(std::optional<bool> isLight);
    void UpdateMenuBarColor(RefPtr<AppBarTheme>& theme, RefPtr<FrameNode>& menuBar, bool isLight);
    void UpdateButtonColor(RefPtr<AppBarTheme>& theme, RefPtr<FrameNode>& button, bool isLight);
    void UpdateDividerColor(RefPtr<AppBarTheme>& theme, RefPtr<FrameNode>& divider, bool isLight);
    void UpdateIconColor(RefPtr<AppBarTheme>& theme, RefPtr<FrameNode>& icon, bool isLight);
    void UpdateLayout();
    void UpdateMenuBarLayout(RefPtr<AppBarTheme>& theme, RefPtr<FrameNode>& menuBar, bool isRtl);
    void UpdateButtonLayout(RefPtr<AppBarTheme>& theme, RefPtr<FrameNode>& button, bool isLeft);
    void UpdateIconLayout(RefPtr<AppBarTheme>& theme, RefPtr<FrameNode>& icon, bool isLeft);
    void ColorConfigurationCallBack();
    void AppInfoCallBack();
    void AppScreenCallBack();
    void AppBgColorCallBack();
    std::optional<bool> settedColorMode = std::nullopt;
    ACE_FORCE_EXPORT static void RegisterBeforeCreateLayoutBuilder(
        std::function<void(RefPtr<FrameNode> host, std::optional<bool> settedColorMode)> beforeCreateLayoutBuilder);
    bool OnBackPressedCallback() override;
    void SetOnBackPressedConsumed();
    int32_t AddRectChangeListener(std::function<void(const RectF& rect)>&& listener);
    void RemoveRectChangeListener(int32_t id);
    void NotifyRectChange(const RectF& rect);
    void CallRectChange();
private:
    void UpdateLayoutMargin();
    void UpdateOverlayLayout();
    void MenuBarSafeAreaCallBack();
    void ContentSafeAreaCallBack();
    static std::function<void(RefPtr<FrameNode> host, std::optional<bool> settedColorMode)> beforeCreateLayoutBuilder_;
    std::optional<bool> onBackPressedConsumed_;
    std::optional<RectF> appBarRect_;
    std::unordered_map<int32_t, std::function<void(const RectF& rect)>> rectChangeListeners_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ATOMIC_SERVICE_PATTERN_H
