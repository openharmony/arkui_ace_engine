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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_ISOLATED_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_ISOLATED_PATTERN_H

#include "core/common/dynamic_component_renderer.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_pattern.h"

namespace OHOS::Ace::NG {
struct IsolatedInfo {
    std::string abcPath;
    std::string reourcePath;
    std::string entryPoint;
};

class IsolatedPattern : public UIExtensionPattern {
    DECLARE_ACE_TYPE(IsolatedPattern, UIExtensionPattern);

public:
    IsolatedPattern();
    ~IsolatedPattern() override;

    void InitializeDynamicComponent(const std::string& hapPath,
        const std::string& abcPath, const std::string& entryPoint, void* runtime);
    void InitializeIsolatedComponent(
        const RefPtr<OHOS::Ace::WantWrap>& wantWrap, void* runtime);
    bool OnDirtyLayoutWrapperSwap(
        const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void OnDetachFromFrameNode(FrameNode* frameNode) override;

    void OnSizeChanged(int32_t width, int32_t height)
    {
        if (onSizeChanged_) {
            onSizeChanged_(width, height);
        }
    }

    void SetOnSizeChangedCallback(std::function<void(int32_t, int32_t)>&& callback)
    {
        onSizeChanged_ = std::move(callback);
    }

    void FireOnErrorCallback(int32_t code, const std::string& name, const std::string& message) override;

protected:
    virtual void DispatchPointerEvent(
        const std::shared_ptr<MMI::PointerEvent>& pointerEvent) override;
    virtual void DispatchKeyEvent(const KeyEvent& event) override;

private:
    void InitializeRender(void* runtime);

    RefPtr<DynamicComponentRenderer> dynamicComponentRenderer_;
    std::function<void(int32_t, int32_t)> onSizeChanged_;
    IsolatedInfo curIsolatedInfo_;
    ACE_DISALLOW_COPY_AND_MOVE(IsolatedPattern);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_ISOLATED_PATTERN_H
