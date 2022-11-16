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

#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace {
namespace {
constexpr double DISPLAY_WIDTH = 720;
constexpr double DISPLAY_HEIGHT = 1280;
}
class Window : public AceType {
    DECLARE_ACE_TYPE(Window, AceType);
};
class FontManager : public AceType {
    DECLARE_ACE_TYPE(FontManager, AceType);
};
class ManagerInterface : public AceType {
    DECLARE_ACE_TYPE(ManagerInterface, AceType);
};
class Frontend : public AceType {
    DECLARE_ACE_TYPE(Frontend, AceType);
};
class OffscreenCanvas : public AceType {
    DECLARE_ACE_TYPE(Frontend, AceType);
};
enum class FrontendType {};

void PipelineBase::OnVsyncEvent(uint64_t nanoTimestamp, uint32_t frameCount) {}

void PipelineBase::SendEventToAccessibility(const AccessibilityEvent& accessibilityEvent) {}

void PipelineBase::OnActionEvent(const std::string& action) {}

void PipelineBase::SetRootSize(double density, int32_t width, int32_t height) {}

RefPtr<PipelineBase> PipelineBase::GetCurrentContext()
{
    auto pipeline = AceType::MakeRefPtr<MockPipelineBase>();
    pipeline->SetThemeManager(AceType::MakeRefPtr<ThemeManager>());
    return pipeline;
}

double PipelineBase::NormalizeToPx(const Dimension& /*dimension*/) const
{
    return 1.0f;
}

PipelineBase::~PipelineBase() = default;

uint64_t PipelineBase::GetTimeFromExternalTimer()
{
    return 1;
}

RefPtr<AccessibilityManager> PipelineBase::GetAccessibilityManager() const
{
    return nullptr;
}

void PipelineBase::Destroy() {}

double PipelineBase::ConvertPxToVp(const Dimension& /* dimension */) const
{
    return 1.0f;
}

void PipelineBase::RequestFrame() {}

Rect PipelineBase::GetCurrentWindowRect() const
{
    return {0., 0., DISPLAY_WIDTH, DISPLAY_HEIGHT};
}
} // namespace OHOS::Ace
