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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCREEN_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCREEN_PATTERN_H

#include "session/screen/include/screen_session.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "input_manager.h"

namespace OHOS::Ace::NG {
class ScreenPattern : public StackPattern {
    DECLARE_ACE_TYPE(ScreenPattern, StackPattern);

public:
    explicit ScreenPattern(const sptr<Rosen::ScreenSession>& screenSession);
    ~ScreenPattern() override = default;

    std::optional<RenderContext::ContextParam> GetContextParam() const override
    {
        return RenderContext::ContextParam { RenderContext::ContextType::EXTERNAL };
    }

    sptr<Rosen::ScreenSession> GetScreenSession()
    {
        return screenSession_;
    }

    void SetScreenSession(const sptr<Rosen::ScreenSession>& screenSession);
    uint32_t GetWindowPatternType() const override;

protected:
    void OnAttachToFrameNode() override;
    void OnDetachFromFrameNode(FrameNode* frameNode) override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& changeConfig) override;

private:
    void UpdateDisplayInfo();
    void UpdateRenderPivot(float pivotX, float pivotY);
    void DeduplicateDisplayInfo();
    void UpdateToInputManager(float rotation);
    void InputManagerUpdateDisplayInfo(RectF paintRect, MMI::DisplayInfo displayInfo, MMI::WindowInfo windowInfo);
    float GetDensityInCurrentResolution();

    static float screenMaxWidth_;
    static float screenMaxHeight_;

    sptr<Rosen::ScreenSession> screenSession_;

    ACE_DISALLOW_COPY_AND_MOVE(ScreenPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCREEN_PATTERN_H
