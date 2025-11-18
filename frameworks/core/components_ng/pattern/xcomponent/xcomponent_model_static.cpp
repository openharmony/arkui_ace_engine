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

#include "core/components_ng/pattern/xcomponent/xcomponent_model_static.h"

#include "base/utils/utils.h"
// This marco must be undefined after include xcomponent pattern headers.
#define private protected
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern_v2.h"
#undef private
#include "core/components_ng/pattern/xcomponent/xcomponent_ext_surface_callback_client.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_accessibility_session_adapter.h"
#include "base/display_manager/display_manager.h"
#include "base/error/error_code.h"

namespace OHOS::Ace::NG {
namespace {
// Declare xcomponent static pattern for language with static typing.
class XComponentStaticPattern : public XComponentPatternV2 {
    DECLARE_ACE_TYPE(XComponentStaticPattern, XComponentPatternV2);
public:
    XComponentStaticPattern() = default;
    explicit XComponentStaticPattern(bool isTypedNode);
    ~XComponentStaticPattern() override = default;
    void InitParams();
    bool IsBindNative() override;
    void MarkBindNative();
    bool BindXComponentController(const std::shared_ptr<InnerXComponentController>& controller);
    void SetNativeHandler(const std::function<void(void*)>& handler);
    void UpdateId(const std::string &id);
    bool UpdateType(XComponentType type);
    void RegisterSurfaceInitEvent();
    void HandleSurfaceInitEvent();
private:
    // Hooked xcomponent pattern methods.
    void InitializeNativeXComponent();
    void OnAttachToFrameNode() override {}
    void OnAttachToMainTree() override;
    void BeforeSyncGeometryProperties(const DirtySwapConfig& config) override;
    void OnDetachFromMainTree() override;
    void OnDetachFromFrameNode(FrameNode* frameNode) override;
    void OnWindowHide() override;
    void OnWindowShow() override;
    void OnRebuildFrame() override;
    void OnModifyDone() override;
    void DumpInfo() override;
    std::function<void(void*)> nativeHandler_ = nullptr;
    bool isBindNative_ = false;
    bool isHostAttached_ = false;
};

#define XCOMPONENT_STATIC_PATTERN_METHOD(func, ...) \
    if (isBindNative_) {                            \
        XComponentPatternV2::func(__VA_ARGS__);     \
    }  else {                                       \
        XComponentPattern::func(__VA_ARGS__);       \
    }                                               \

} // namespace

RefPtr<FrameNode> XComponentModelStatic::CreateFrameNode(int32_t nodeId, bool isTypedNode)
{
    std::shared_ptr<InnerXComponentController> controller = nullptr;
    auto frameNode = FrameNode::CreateFrameNode(
        V2::XCOMPONENT_ETS_TAG, nodeId, AceType::MakeRefPtr<XComponentStaticPattern>(isTypedNode));
    return frameNode;
}

bool XComponentModelStatic::SetXComponentController(FrameNode* frameNode,
    const std::shared_ptr<InnerXComponentController>& controller)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto xcPattern = AceType::DynamicCast<XComponentStaticPattern>(frameNode->GetPattern());
    CHECK_NULL_RETURN(xcPattern, false);
    return xcPattern->BindXComponentController(controller);
}

void XComponentModelStatic::InitParams(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto xcPattern = AceType::DynamicCast<XComponentStaticPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(xcPattern);
    xcPattern->InitParams();
}

void XComponentModelStatic::SetNativeXComponentHandler(
    FrameNode* frameNode, const std::function<void(void*)>& handler)
{
    CHECK_NULL_VOID(frameNode);
    auto xcPattern = AceType::DynamicCast<XComponentStaticPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(xcPattern);
    xcPattern->SetNativeHandler(handler);
}

void XComponentModelStatic::SetXComponentId(FrameNode* frameNode, const std::string& id)
{
    CHECK_NULL_VOID(frameNode);
    auto xcPattern = AceType::DynamicCast<XComponentStaticPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(xcPattern);
    CHECK_EQUAL_VOID((xcPattern->IsBindNative()), true);
    xcPattern->UpdateId(id);
}

void XComponentModelStatic::MarkBindNative(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto xcPattern = AceType::DynamicCast<XComponentStaticPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(xcPattern);
    xcPattern->MarkBindNative();
}

void XComponentModelStatic::SetScreenId(FrameNode* frameNode, uint64_t screenId)
{
    CHECK_NULL_VOID(frameNode);
    auto xcPattern = AceType::DynamicCast<XComponentStaticPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(xcPattern);
    CHECK_EQUAL_VOID((xcPattern->IsBindNative()), true);
    uint64_t rsScreenId = 0u;
    TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "XComponent[%{public}s][screenId: %" PRIu64 "]", xcPattern->GetId().c_str(),
        screenId);
    if (!DisplayManager::GetInstance().ConvertScreenIdToRsScreenId(screenId, rsScreenId)) {
        TAG_LOGW(AceLogTag::ACE_XCOMPONENT, "ConvertScreenIdToRsScreenId fail");
    }
    xcPattern->SetScreenId(rsScreenId);
}

void XComponentModelStatic::SetXComponentType(FrameNode* frameNode, XComponentType type)
{
    CHECK_NULL_VOID(frameNode);
    auto xcPattern = AceType::DynamicCast<XComponentStaticPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(xcPattern);
    bool shouldUpdateType = xcPattern->UpdateType(type);
    if (shouldUpdateType) {
        auto layoutProperty = frameNode->GetLayoutProperty<XComponentLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->UpdateXComponentType(type);
    }
}

XComponentStaticPattern::XComponentStaticPattern(bool isTypedNode)
{
    isTypedNode_ = isTypedNode;
    type_ = XComponentType::UNKNOWN;
}

void XComponentStaticPattern::InitParams()
{
    InitializeNativeXComponent();
    CHECK_EQUAL_VOID(isHostAttached_, true);
    XCOMPONENT_STATIC_PATTERN_METHOD(OnAttachToFrameNode);
    isHostAttached_ = true;
    CHECK_EQUAL_VOID(isBindNative_, true);
    RegisterSurfaceInitEvent();
}

bool XComponentStaticPattern::IsBindNative()
{
    return isBindNative_;
}

void XComponentStaticPattern::MarkBindNative()
{
    CHECK_EQUAL_VOID((nativeHandler_ != nullptr), true);
    CHECK_EQUAL_VOID((xcomponentController_ != nullptr), true);
    isBindNative_ = true;
}

bool XComponentStaticPattern::BindXComponentController(const std::shared_ptr<InnerXComponentController>& controller)
{
    CHECK_NULL_RETURN(controller, false);
    CHECK_EQUAL_RETURN(isBindNative_, true, false);
    CHECK_EQUAL_RETURN((xcomponentController_ != nullptr), true, false);
    xcomponentController_ = controller;
    return true;
}

void XComponentStaticPattern::SetNativeHandler(const std::function<void(void*)>& handler)
{
    CHECK_EQUAL_VOID(isBindNative_, true);
    CHECK_EQUAL_VOID((nativeHandler_ != nullptr), true);
    nativeHandler_ = std::move(handler);
}

void XComponentStaticPattern::UpdateId(const std::string &id)
{
    CHECK_EQUAL_VOID(isBindNative_, true);
    CHECK_EQUAL_VOID((id_.has_value()), true);
    id_ = id;
}

bool XComponentStaticPattern::UpdateType(XComponentType type)
{
    CHECK_EQUAL_RETURN((type_ != XComponentType::UNKNOWN), true, false);
    type_ = type;
    return true;
}

void XComponentStaticPattern::InitializeNativeXComponent()
{
    CHECK_NULL_VOID(nativeHandler_);
    CHECK_EQUAL_VOID(isBindNative_, true);
    CHECK_EQUAL_VOID((nativeXComponentImpl_ != nullptr), true);
    isNativeXComponent_ = true;
    nativeXComponentImpl_ = AceType::MakeRefPtr<NativeXComponentImpl>();
    CHECK_NULL_VOID(nativeXComponentImpl_);
    nativeXComponentImpl_->SetXComponentId(GetId());
    nativeXComponent_ = std::make_shared<OH_NativeXComponent>(AceType::RawPtr(nativeXComponentImpl_));
    CHECK_EQUAL_VOID(isTypedNode_, false);
    InitializeAccessibility();
    SetExpectedRateRangeInit();
    OnFrameEventInit();
    UnregisterOnFrameEventInit();
    LoadNative();
}

void XComponentStaticPattern::RegisterSurfaceInitEvent()
{
    auto surfaceInitEvent = [weak = AceType::WeakClaim(this)]
        (const std::string& componentId, const uint32_t nodeId, const bool isDestroy) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleSurfaceInitEvent();
    };
    auto host = GetHost();
    auto eventHub = host->GetEventHub<XComponentEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSurfaceInitEvent(std::move(surfaceInitEvent));
}

void XComponentStaticPattern::HandleSurfaceInitEvent()
{
    CHECK_NULL_VOID(nativeHandler_);
    CHECK_NULL_VOID(nativeXComponent_);
    nativeHandler_(reinterpret_cast<void*>(nativeXComponent_.get()));
    CHECK_EQUAL_VOID(isTypedNode_, true);
    XComponentPattern::OnSurfaceCreated();
}

void XComponentStaticPattern::OnAttachToMainTree()
{
    XCOMPONENT_STATIC_PATTERN_METHOD(OnAttachToMainTree);
}

void XComponentStaticPattern::BeforeSyncGeometryProperties(const DirtySwapConfig& config)
{
    XCOMPONENT_STATIC_PATTERN_METHOD(BeforeSyncGeometryProperties, config);
}

void XComponentStaticPattern::OnDetachFromMainTree()
{
    XCOMPONENT_STATIC_PATTERN_METHOD(OnDetachFromMainTree);
}

void XComponentStaticPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    XCOMPONENT_STATIC_PATTERN_METHOD(OnDetachFromFrameNode, frameNode);
}

void XComponentStaticPattern::OnWindowHide()
{
    XCOMPONENT_STATIC_PATTERN_METHOD(OnWindowHide);
}

void XComponentStaticPattern::OnWindowShow()
{
    XCOMPONENT_STATIC_PATTERN_METHOD(OnWindowShow);
}

void XComponentStaticPattern::OnRebuildFrame()
{
    XCOMPONENT_STATIC_PATTERN_METHOD(OnRebuildFrame);
}

void XComponentStaticPattern::OnModifyDone()
{
    XCOMPONENT_STATIC_PATTERN_METHOD(OnModifyDone);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    CHECK_NULL_VOID(renderContextForSurface_);
    renderFit_ = renderContext->GetRenderFit().value_or(RenderFit::RESIZE_FILL);
    renderContextForSurface_->UpdateRenderFit(renderFit_);
}

void XComponentStaticPattern::DumpInfo()
{
    XCOMPONENT_STATIC_PATTERN_METHOD(DumpInfo);
}

} // namespace OHOS::Ace::NG
