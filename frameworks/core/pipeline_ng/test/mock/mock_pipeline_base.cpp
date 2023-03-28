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

#include "core/pipeline_ng/test/mock/mock_interface.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace {
namespace {
constexpr double DISPLAY_WIDTH = 720;
constexpr double DISPLAY_HEIGHT = 1280;
} // namespace
class Window : public AceType {
    DECLARE_ACE_TYPE(Window, AceType);
};
class Frontend : public AceType {
    DECLARE_ACE_TYPE(Frontend, AceType);
};
class OffscreenCanvas : public AceType {
    DECLARE_ACE_TYPE(Frontend, AceType);
};
enum class FrontendType {};

RefPtr<MockPipelineBase> MockPipelineBase::pipeline_;

void PipelineBase::OnVsyncEvent(uint64_t nanoTimestamp, uint32_t frameCount) {}

void PipelineBase::SendEventToAccessibility(const AccessibilityEvent& accessibilityEvent) {}

void PipelineBase::OnActionEvent(const std::string& action) {}

void PipelineBase::SetRootSize(double density, int32_t width, int32_t height) {}

RefPtr<PipelineBase> PipelineBase::GetCurrentContext()
{
    return MockPipelineBase::GetCurrent();
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

void PipelineBase::PostAsyncEvent(TaskExecutor::Task&& task, TaskExecutor::TaskType type) {}

void PipelineBase::PostAsyncEvent(const TaskExecutor::Task& task, TaskExecutor::TaskType type) {}

RefPtr<AccessibilityManager> PipelineBase::GetAccessibilityManager() const
{
    return nullptr;
}

bool PipelineBase::Animate(const AnimationOption& option, const RefPtr<Curve>& curve,
    const std::function<void()>& propertyCallback, const std::function<void()>& finishCallback)
{
    return true;
}

void PipelineBase::Destroy() {}

void PipelineBase::AddEtsCardTouchEventCallback(
    int32_t ponitId, EtsCardTouchEventCallback&& callback) {}

double PipelineBase::ConvertPxToVp(const Dimension& /* dimension */) const
{
    return 1.0f;
}

void PipelineBase::RequestFrame() {}

Rect PipelineBase::GetCurrentWindowRect() const
{
    return { 0., 0., DISPLAY_WIDTH, DISPLAY_HEIGHT };
}

void MockPipelineBase::SetUp()
{
    pipeline_ = AceType::MakeRefPtr<MockPipelineBase>();
}

void MockPipelineBase::TearDown()
{
    pipeline_ = nullptr;
}

RefPtr<MockPipelineBase> MockPipelineBase::GetCurrent()
{
    return pipeline_;
}

void PipelineBase::OpenImplicitAnimation(
    const AnimationOption& option, const RefPtr<Curve>& curve, const std::function<void()>& finishCallBack)
{}

bool PipelineBase::CloseImplicitAnimation()
{
    return true;
}

RefPtr<Frontend> PipelineBase::GetFrontend() const
{
    return nullptr;
}
} // namespace OHOS::Ace
