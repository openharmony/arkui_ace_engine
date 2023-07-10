/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include <optional>
#include <string>
#include <utility>

#include "base/geometry/dimension.h"
#include "base/geometry/size.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/common/thread_checker.h"
#include "core/components/common/layout/constants.h"
#include "core/components/xcomponent/native_interface_xcomponent_impl.h"
#include "core/components/xcomponent/xcomponent_controller.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/event/input_event.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_event_hub.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_layout_algorithm.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/render_surface.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
class XComponentExtSurfaceCallbackClient;
class XComponentPattern : public Pattern {
    DECLARE_ACE_TYPE(XComponentPattern, Pattern);

public:
    XComponentPattern() = default;
    XComponentPattern(const std::string& id, XComponentType type, const std::string& libraryname,
        const RefPtr<XComponentController>& xcomponentController);
    ~XComponentPattern() override = default;

    bool IsAtomicNode() const override
    {
        return type_ == XComponentType::SURFACE || type_ == XComponentType::TEXTURE;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<XComponentLayoutProperty>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<XComponentEventHub>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<XComponentLayoutAlgorithm>();
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::NODE, false };
    }

    std::pair<RefPtr<OHOS::Ace::NativeXComponentImpl>, std::weak_ptr<OH_NativeXComponent>> GetNativeXComponent()
    {
        if (!nativeXComponent_ || !nativeXComponentImpl_) {
            nativeXComponentImpl_ = AceType::MakeRefPtr<NativeXComponentImpl>();
            nativeXComponent_ = std::make_shared<OH_NativeXComponent>(AceType::RawPtr(nativeXComponentImpl_));
        }
        return std::make_pair(nativeXComponentImpl_, nativeXComponent_);
    }

    void NativeXComponentInit()
    {
        CHECK_RUN_ON(UI);
        CHECK_NULL_VOID(nativeXComponentImpl_);
        CHECK_NULL_VOID(nativeXComponent_);
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto width = initSize_.Width();
        auto height = initSize_.Height();
        nativeXComponentImpl_->SetXComponentWidth(static_cast<uint32_t>(width));
        nativeXComponentImpl_->SetXComponentHeight(static_cast<uint32_t>(height));
        auto* surface = const_cast<void*>(nativeXComponentImpl_->GetSurface());
        const auto* callback = nativeXComponentImpl_->GetCallback();
        if (callback && callback->OnSurfaceCreated != nullptr) {
            callback->OnSurfaceCreated(nativeXComponent_.get(), surface);
        }
    }

    void OnPaint();
    void NativeXComponentOffset(double x, double y);
    void NativeXComponentChange(float width, float height);
    void NativeXComponentDestroy();
    void NativeXComponentDispatchTouchEvent(const OH_NativeXComponent_TouchEvent& touchEvent,
        const std::vector<XComponentTouchPoint>& xComponentTouchPoints);
    void NativeXComponentDispatchMouseEvent(const OH_NativeXComponent_MouseEvent& mouseEvent);

    void InitNativeWindow(float textureWidth, float textureHeight);
    void XComponentSizeInit();
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

    const std::optional<std::string>& GetSoPath() const
    {
        return soPath_;
    }

    void SetSoPath(const std::string& soPath)
    {
        soPath_ = soPath;
    }

private:
    void OnAttachToFrameNode() override;
    void OnDetachFromFrameNode(FrameNode* frameNode) override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void OnRebuildFrame() override;
    void OnAreaChangedInner() override;

    void InitEvent();
    void InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandleTouchEvent(const TouchEventInfo& info);
    void InitMouseEvent(const RefPtr<InputEventHub>& inputHub);
    void HandleMouseEvent(const MouseInfo& info);
    void InitMouseHoverEvent(const RefPtr<InputEventHub>& inputHub);
    void HandleMouseHoverEvent(bool isHover);
    void InitFocusEvent(const RefPtr<FocusHub>& focusHub);
    void HandleFocusEvent();
    bool HandleKeyEvent(const KeyEvent& event);
    void HandleBlurEvent();
    ExternalEvent CreateExternalEvent();
    void CreateSurface();
    void SetMethodCall();
    void ConfigSurface(uint32_t surfaceWidth, uint32_t surfaceHeight);
    void SetTouchPoint(
        const std::list<TouchLocationInfo>& touchInfoList, int64_t timeStamp, const TouchType& touchType);

    std::vector<OH_NativeXComponent_HistoricalPoint> SetHistoryPoint(const std::list<TouchLocationInfo>& touchInfoList);
    std::string id_;
    XComponentType type_;
    std::string libraryname_;
    RefPtr<XComponentController> xcomponentController_;
    std::optional<std::string> soPath_;

    RefPtr<RenderSurface> renderSurface_;
    RefPtr<RenderContext> renderContextForSurface_;

    std::shared_ptr<OH_NativeXComponent> nativeXComponent_;
    RefPtr<NativeXComponentImpl> nativeXComponentImpl_;

    bool hasXComponentInit_ = false;

    RefPtr<TouchEventImpl> touchEvent_;
    OH_NativeXComponent_TouchEvent touchEventPoint_;
    RefPtr<InputEvent> mouseEvent_;
    RefPtr<InputEvent> mouseHoverEvent_;
    std::vector<XComponentTouchPoint> nativeXComponentTouchPoints_;
    RefPtr<XComponentExtSurfaceCallbackClient> extSurfaceClient_;
    WeakPtr<NG::PipelineContext> context_;
    int32_t scopeId_;
    SizeF initSize_;
#ifdef OHOS_PLATFORM
    int64_t startIncreaseTime_ = 0;
#endif
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_XCOMPONENT_PATTERN_H
