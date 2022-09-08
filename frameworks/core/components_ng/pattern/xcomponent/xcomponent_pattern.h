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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_XCOMPONENT_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_XCOMPONENT_PATTERN_H

#include <string>
#include <utility>

#include "base/geometry/dimension.h"
#include "base/geometry/size.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/xcomponent/resource/native_texture.h"
#include "core/components/xcomponent/xcomponent_component.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_event_hub.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_layout_algorithm.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/render_surface.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
class XComponentPattern : public Pattern {
    DECLARE_ACE_TYPE(XComponentPattern, Pattern);

public:
    XComponentPattern() = default;
    XComponentPattern(const std::string& id, const std::string& type, const std::string& libraryname,
        const RefPtr<XComponentController>& xcomponentController);
    ~XComponentPattern() override = default;

    std::optional<std::string> GetSurfaceNodeName() const override
    {
        return id_ + "Surface";
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<XComponentEventHub>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<XComponentLayoutAlgorithm>();
    }

    void NativeXComponentInit(OH_NativeXComponent* nativeXComponent, WeakPtr<NativeXComponentImpl> nativeXComponentImpl)
    {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto pipelineContext = host->GetContext();
        CHECK_NULL_VOID(pipelineContext);
        auto geometryNode = host->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        nativeXComponent_ = nativeXComponent;
        nativeXComponentImpl_ = std::move(nativeXComponentImpl);
        auto width = geometryNode->GetContentSize().Width();
        auto height = geometryNode->GetContentSize().Height();

        pipelineContext->GetTaskExecutor()->PostTask(
            [weakNXCompImpl = nativeXComponentImpl_, nXComp = nativeXComponent_, width, height] {
                auto nXCompImpl = weakNXCompImpl.Upgrade();
                if (nXComp && nXCompImpl) {
                    nXCompImpl->SetXComponentWidth(static_cast<int>(width));
                    nXCompImpl->SetXComponentHeight(static_cast<int>(height));
                    auto* surface = const_cast<void*>(nXCompImpl->GetSurface());
                    const auto* callback = nXCompImpl->GetCallback();
                    if (callback && callback->OnSurfaceCreated != nullptr) {
                        callback->OnSurfaceCreated(nXComp, surface);
                    }
                } else {
                    LOGE("Native XComponent nullptr");
                }
            },
            TaskExecutor::TaskType::JS);
    }
    void OnPaint();
    void NativeXComponentOffset(double x, double y);
    void NativeXComponentChange(float width, float height);
    void NativeXComponentDestroy();
    void NativeXComponentDispatchTouchEvent(const OH_NativeXComponent_TouchEvent& touchEvent);

    void XComponentSizeInit(float textureWidth, float textureHeight);
    void XComponentSizeChange(float textureWidth, float textureHeight);

    void* GetNativeWindow()
    {
        return renderSurface_->GetNativeWindow();
    }

    const std::string& GetId() const
    {
        return id_;
    }

    const std::string& GetLibraryName() const
    {
        return libraryname_;
    }

private:
    void OnAttachToFrameNode() override;
    void OnDetachFromFrameNode() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void InitEvent();
    void InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandleTouchEvent(const TouchEventInfo& info);
    ExternalEvent CreateExternalEvent();
    void CreateSurface();
    void SetMethodCall();
    void ConfigSurface(uint32_t surfaceWidth, uint32_t surfaceHeight);
    void SetTouchPoint(
        const std::list<TouchLocationInfo>& touchInfoList, int64_t timeStamp, const TouchType& touchType);
    static OH_NativeXComponent_TouchEventType ConvertNativeXComponentTouchEvent(const TouchType& touchType);

    std::string id_;
    std::string type_;
    std::string libraryname_;
    RefPtr<XComponentController> xcomponentController_;

    RefPtr<RenderSurface> renderSurface_ = RenderSurface::Create();

    OH_NativeXComponent* nativeXComponent_ = nullptr;
    WeakPtr<NativeXComponentImpl> nativeXComponentImpl_;

    bool hasXComponentInit_ = false;

    RefPtr<TouchEventImpl> touchEvent_;
    OH_NativeXComponent_TouchEvent touchEventPoint_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_XCOMPONENT_PATTERN_H
