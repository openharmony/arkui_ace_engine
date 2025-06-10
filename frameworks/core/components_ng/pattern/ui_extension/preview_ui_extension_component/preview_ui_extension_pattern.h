/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_PREVIEW_UI_EXTENSION_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_PREVIEW_UI_EXTENSION_PATTERN_H

#include "core/components_ng/pattern/ui_extension/security_ui_extension_component/security_ui_extension_pattern.h"
namespace OHOS::Ace::NG {
class PreviewUIExtensionPattern : public SecurityUIExtensionPattern {
    DECLARE_ACE_TYPE(PreviewUIExtensionPattern, SecurityUIExtensionPattern);
public:
    PreviewUIExtensionPattern();
    ~PreviewUIExtensionPattern() override;
    void Initialize(const NG::UIExtensionConfig& config);
    void UpdateWant(const RefPtr<OHOS::Ace::WantWrap>& wantWrap);
    void UpdateWant(const AAFwk::Want& want);
    void OnConnect();
    void OnAttachToFrameNode() override;
    void FireOnRemoteReadyCallback() override;
    void OnAttachContext(PipelineContext *context) override;
    void RegisterVisibleAreaChange();
    void InitializeAccessibility();
private:
    void UpdateSessionInstanceId(int32_t instanceId);
    ACE_DISALLOW_COPY_AND_MOVE(PreviewUIExtensionPattern);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_PREVIEW_UI_EXTENSION_PATTERN_H