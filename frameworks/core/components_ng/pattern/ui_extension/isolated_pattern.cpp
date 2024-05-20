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

#include "core/components_ng/pattern/ui_extension/isolated_pattern.h"

#include <sys/stat.h>
#include <sys/statfs.h>

#include "adapter/ohos/osal/want_wrap_ohos.h"
#include "base/log/dump_log.h"
#include "core/event/key_event.h"
#include "core/event/pointer_event.h"
#include "display_manager.h"
#include "session/host/include/session.h"

namespace OHOS::Ace::NG {
namespace {
constexpr char RESOURCE_PATH[] = "resourcePath";
constexpr char ABC_PATH[] = "abcPath";
constexpr char ENTRY_POINT[] = "entryPoint";
constexpr int32_t PARAM_ERR_CODE = 10001;
constexpr char PARAM_NAME[] = "paramError";
constexpr char PARAM_MSG[] = "The param is empty";
}

int32_t IsolatedPattern::isolatedIdGenerator_ = 0;

IsolatedPattern::IsolatedPattern()
    : PlatformPattern(AceLogTag::ACE_ISOLATED_COMPONENT, ++isolatedIdGenerator_)
{
    PLATFORM_LOGI("The IsolatedPattern is created.");
}

IsolatedPattern::~IsolatedPattern()
{
    PLATFORM_LOGI("The IsolatedPattern is destroyed.");
}

void IsolatedPattern::InitializeDynamicComponent(
    const std::string& hapPath, const std::string& abcPath, const std::string& entryPoint, void* runtime)
{
    if (hapPath.empty() || abcPath.empty() || entryPoint.empty() || runtime == nullptr) {
        PLATFORM_LOGE("The param empty.");
        return;
    }

    curIsolatedInfo_.abcPath = abcPath;
    curIsolatedInfo_.reourcePath = hapPath;
    curIsolatedInfo_.entryPoint = entryPoint;
    InitializeRender(runtime);
}

void IsolatedPattern::InitializeIsolatedComponent(const RefPtr<OHOS::Ace::WantWrap>& wantWrap, void* runtime)
{
    auto want = AceType::DynamicCast<WantWrapOhos>(wantWrap)->GetWant();
    auto resourcePath = want.GetStringParam(RESOURCE_PATH);
    auto abcPath = want.GetStringParam(ABC_PATH);
    auto entryPoint = want.GetStringParam(ENTRY_POINT);
    if (resourcePath.empty() || abcPath.empty() || entryPoint.empty() || runtime == nullptr) {
        PLATFORM_LOGE("The param empty.");
        FireOnErrorCallback(PARAM_ERR_CODE, PARAM_NAME, PARAM_MSG);
        return;
    }

    curIsolatedInfo_.abcPath = abcPath;
    curIsolatedInfo_.reourcePath = resourcePath;
    curIsolatedInfo_.entryPoint = entryPoint;
    InitializeRender(runtime);
}

void IsolatedPattern::InitializeRender(void* runtime)
{
    isolatedDumpInfo_.createLimitedWorkerTime = GetCurrentTimestamp();
#if !defined(PREVIEW)
    if (!dynamicComponentRenderer_) {
        ContainerScope scope(instanceId_);
        dynamicComponentRenderer_ = DynamicComponentRenderer::Create(GetHost(),
            curIsolatedInfo_.reourcePath, curIsolatedInfo_.abcPath, curIsolatedInfo_.entryPoint, runtime);
        CHECK_NULL_VOID(dynamicComponentRenderer_);
        dynamicComponentRenderer_->CreateContent();
    }
#else
    PLATFORM_LOGE("IsolatedComponent not support preview.");
#endif
}

void IsolatedPattern::DispatchPointerEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    CHECK_NULL_VOID(pointerEvent);
    CHECK_NULL_VOID(dynamicComponentRenderer_);
    dynamicComponentRenderer_->TransferPointerEvent(pointerEvent);
}

bool IsolatedPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    CHECK_NULL_RETURN(dynamicComponentRenderer_, false);
    CHECK_NULL_RETURN(dirty, false);
    auto host = dirty->GetHostNode();
    CHECK_NULL_RETURN(host, false);
    auto offset = host->GetPaintRectGlobalOffsetWithTranslate().first;
    auto size = dirty->GetGeometryNode()->GetFrameSize();
    Ace::ViewportConfig vpConfig;
    vpConfig.SetSize(size.Width(), size.Height());
    vpConfig.SetPosition(offset.GetX(), offset.GetY());
    float density = 1.0f;
    int32_t orientation = 0;
    auto defaultDisplay = Rosen::DisplayManager::GetInstance().GetDefaultDisplay();
    if (defaultDisplay) {
        density = defaultDisplay->GetVirtualPixelRatio();
        orientation = static_cast<int32_t>(defaultDisplay->GetOrientation());
    }
    vpConfig.SetDensity(density);
    vpConfig.SetOrientation(orientation);
    dynamicComponentRenderer_->UpdateViewportConfig(vpConfig, Rosen::WindowSizeChangeReason::UNDEFINED, nullptr);
    return false;
}

void IsolatedPattern::DispatchKeyEvent(const KeyEvent& event)
{
    CHECK_NULL_VOID(event.rawKeyEvent);
    CHECK_NULL_VOID(dynamicComponentRenderer_);
    dynamicComponentRenderer_->TransferKeyEvent(event.rawKeyEvent);
}

void IsolatedPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    CHECK_NULL_VOID(dynamicComponentRenderer_);
    dynamicComponentRenderer_->DestroyContent();
    dynamicComponentRenderer_ = nullptr;
}

void IsolatedPattern::DumpInfo()
{
    DumpLog::GetInstance().AddDesc(std::string("isolatedId: ").append(std::to_string(platformId_)));
    DumpLog::GetInstance().AddDesc(std::string("abcPath: ").append(curIsolatedInfo_.abcPath));
    DumpLog::GetInstance().AddDesc(std::string("reourcePath: ").append(curIsolatedInfo_.reourcePath));
    DumpLog::GetInstance().AddDesc(std::string("entryPoint: ").append(curIsolatedInfo_.entryPoint));
    DumpLog::GetInstance().AddDesc(std::string("createLimitedWorkerTime: ")
        .append(std::to_string(isolatedDumpInfo_.createLimitedWorkerTime)));
    CHECK_NULL_VOID(dynamicComponentRenderer_);
    RendererDumpInfo rendererDumpInfo;
    dynamicComponentRenderer_->Dump(rendererDumpInfo);
    DumpLog::GetInstance().AddDesc(std::string("createUiContenTime: ")
        .append(std::to_string(rendererDumpInfo.createUiContenTime)));
    DumpLog::GetInstance().AddDesc(std::string("limitedWorkerInitTime: ")
        .append(std::to_string(rendererDumpInfo.limitedWorkerInitTime)));
    DumpLog::GetInstance().AddDesc(std::string("loadAbcTime: ")
        .append(std::to_string(rendererDumpInfo.loadAbcTime)));
}
} // namespace OHOS::Ace::NG
