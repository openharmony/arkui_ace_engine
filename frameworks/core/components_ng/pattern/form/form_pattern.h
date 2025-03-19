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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_FORM_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_FORM_PATTERN_H

#include <unordered_map>

#include "transaction/rs_interfaces.h"

#include "core/common/container.h"
#include "core/common/ace_application_info.h"
#include "core/components/form/resource/form_request_data.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/form/accessibility_session_adapter_form.h"
#include "core/components_ng/pattern/form/form_event_hub.h"
#include "core/components_ng/pattern/form/form_layout_property.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/form/form_special_style.h"
#include "core/components/common/properties/color.h"
#include "form_skeleton_params.h"

namespace OHOS {
namespace MMI {
class PointerEvent;
} // namespace MMI

namespace Ace {
class SubContainer;
class FormManagerDelegate;
class DrawDelegate;
struct SerializedGesture;
struct AccessibilityParentRectInfo;

namespace NG {
enum class FormChildNodeType : int32_t {
    /**
     * Arkts card node type
    */
    FORM_SURFACE_NODE,

    /**
     * static form image node type
    */
    FORM_STATIC_IMAGE_NODE,

    /**
     * form skeleton node type
    */
    FORM_SKELETON_NODE,

    /**
     * forbidden form root node
    */
    FORM_FORBIDDEN_ROOT_NODE,

    /**
     * forbidden form text node
    */
    FORM_SPECIAL_STYLE_NODE
};

class FormPattern : public Pattern {
    DECLARE_ACE_TYPE(FormPattern, Pattern);

public:
    FormPattern();
    ~FormPattern() override;

    void OnActionEvent(const std::string& action);

    void OnLoadEvent();

    void HandleUnTrustForm();

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<FormLayoutProperty>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<FormEventHub>();
    }

    std::unique_ptr<DrawDelegate> GetDrawDelegate();

    const RefPtr<SubContainer>& GetSubContainer() const;

    void DispatchPointerEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent,
        SerializedGesture& serializedGesture);

    void OnSnapshot(std::shared_ptr<Media::PixelMap> pixelMap);

    void HandleOnSnapshot(std::shared_ptr<Media::PixelMap> pixelMap);

    RefPtr<RenderContext> GetExternalRenderContext()
    {
        return externalRenderContext_;
    }

    bool GetIsLoaded() const
    {
        return isLoaded_;
    }

    void SetFormLinkInfos(const std::vector<std::string>& infos)
    {
        formLinkInfos_.clear();
        formLinkInfos_ = infos;
    }

    void GetRectRelativeToWindow(AccessibilityParentRectInfo& parentRectInfo);

    bool IsJsCard() const
    {
        return isJsCard_;
    }

    void SetObscured(bool isObscured)
    {
        isFormObscured_ = isObscured;
    }

    RefPtr<AccessibilitySessionAdapter> GetAccessibilitySessionAdapter() override;

    void OnAccessibilityChildTreeRegister(uint32_t windowId, int32_t treeId, int64_t accessibilityId);

    void OnAccessibilityChildTreeDeregister();

    void OnAccessibilityDumpChildInfo(const std::vector<std::string>& params, std::vector<std::string>& info);

    void OnLanguageConfigurationUpdate() override;

    void GetTimeLimitResource(std::string &content);

    void UnregisterAccessibility();

    void DumpInfo() override;
    void DumpInfo(std::unique_ptr<JsonValue>& json) override;

private:
    void OnAttachToFrameNode() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void OnRebuildFrame() override;
    void OnVisibleChange(bool isVisible) override;
    void OnModifyDone() override;

    void InitFormManagerDelegate();
    void CreateCardContainer();
    void RemoveSubContainer();

    void FireOnAcquiredEvent(int64_t id) const;
    void FireOnRouterEvent(const std::unique_ptr<JsonValue>& action);
    void FireOnLoadEvent() const;
    void FireOnErrorEvent(const std::string& code, const std::string& msg) const;
    void FireOnUninstallEvent(int64_t id) const;
    void FireFormSurfaceNodeCallback(const std::shared_ptr<Rosen::RSSurfaceNode>& node, const AAFwk::Want& want);
    void FireFormSurfaceChangeCallback(float width, float height, float borderWidth = 0.0);
    void FireFormSurfaceDetachCallback();
    void UpdateBackgroundColorWhenUnTrustForm();

    bool ISAllowUpdate() const;
    void EnableDrag();
    void UpdateConfiguration();
    void HandleFormComponent(RequestFormInfo& info);
    void SetParamForWantTask(const RequestFormInfo& info);
    void AddFormComponent(const RequestFormInfo& info);
    void AddFormComponentTask(const RequestFormInfo& info, RefPtr<PipelineContext> pipeline);
    void AddFormComponentUI(bool isTransparencyEnabled, const RequestFormInfo& info);
    void UpdateFormComponent(const RequestFormInfo& info);
    void UpdateFormComponentSize(const RequestFormInfo& info);
    void UpdateSpecialStyleCfg();
    void UpdateTimeLimitFontCfg();
    void UpdateAppLockCfg();

    void HandleSnapshot(uint32_t delayTime, const std::string& nodeIdStr);
    void TakeSurfaceCaptureForUI();
    void UpdateStaticCard();
    RefPtr<FrameNode> CreateImageNode();
    void UpdateImageNode();
    void RemoveFrsNode();
    void ReleaseRenderer();
    void DelayDeleteImageNode(bool needHandleCachedClick);
    void SetNonTransparentAfterRecover();
    void DeleteImageNodeAfterRecover(bool needHandleCachedClick);
    void HandleStaticFormEvent(const PointF& touchPoint);
    void ProcDeleteImageNode(const AAFwk::Want& want);
    void AttachRSNode(const std::shared_ptr<Rosen::RSSurfaceNode>& node, const AAFwk::Want& want);
    void AttachJsRSNode(const std::shared_ptr<Rosen::RSNode> &jsNode);
    void HandleEnableForm(const bool enable);

    void InitClickEvent();
    void HandleTouchDownEvent(const TouchEventInfo& event);
    void HandleTouchUpEvent(const TouchEventInfo& event);

    void LoadFormSkeleton(bool isRefresh = false);
    bool ShouldLoadFormSkeleton(bool isTransparencyEnabled, const RequestFormInfo &info);
    void LoadDisableFormStyle(const RequestFormInfo& info, bool isRefresh = false);
    void RemoveDisableFormStyle(const RequestFormInfo& info);
    void RemoveFormChildNode(FormChildNodeType formChildNodeType);
    int32_t GetFormDimensionHeight(int32_t dimension);
    RefPtr<FrameNode> CreateColumnNode(FormChildNodeType formChildNodeType);
    RefPtr<FrameNode> CreateTimeLimitNode();
    RefPtr<FrameNode> CreateAppLockNode();
    RefPtr<FrameNode> CreateRectNode(const RefPtr<FrameNode>& parent, const CalcSize& idealSize,
        const MarginProperty& margin, uint32_t fillColor, double opacity);
    void CreateSkeletonView(const RefPtr<FrameNode>& parent, const std::shared_ptr<FormSkeletonParams>& params,
        int32_t dimensionHeight);
    void SetTransparencyConfig(bool isTransparencyForm, const RequestFormInfo &info);
    void SetSkeletonEnableConfig(const RequestFormInfo &info);
    void SetExternalRenderOpacity(double opacity);
    bool ShouldDoSkeletonAnimation();
    void DoSkeletonAnimation();
    void UpdateFormBaseConfig(bool isDynamic);
    void AddFormChildNode(FormChildNodeType formChildNodeType, const RefPtr<FrameNode> child);
    RefPtr<FrameNode> GetFormChildNode(FormChildNodeType formChildNodeType) const;
    double GetTimeLimitFontSize();
    bool IsMaskEnableForm(const RequestFormInfo &info);
    void UpdateChildNodeOpacity(FormChildNodeType formChildNodeType, double opacity);
    void SnapshotSurfaceNode();
    bool CheckFormBundleForbidden(const std::string &bundleName);
    void DelayResetManuallyClickFlag();
    void RemoveDelayResetManuallyClickFlagTask();

    void InitAddFormUpdateAndErrorCallback(int32_t instanceId);
    void InitAddUninstallAndSurfaceNodeCallback(int32_t instanceId);
    void InitAddFormSurfaceChangeAndDetachCallback(int32_t instanceId);
    void InitAddUnTrustAndSnapshotCallback(int32_t instanceId);
    void InitOtherCallback(int32_t instanceId);
    bool IsFormBundleExempt(int64_t formId) const;
    bool IsFormBundleProtected(const std::string &bundleName, int64_t formId) const;
    void HandleLockEvent(bool isLock);
    void HandleFormStyleOperation(const FormSpecialStyle& formSpecialStyle);
    void HandleFormStyleOperation(const FormSpecialStyle& formSpecialStyle, const RequestFormInfo& info);
    void UpdateForbiddenRootNodeStyle(const RefPtr<RenderContext> &renderContext);
    void ReAddStaticFormSnapshotTimer();
    RefPtr<FrameNode> CreateActionNode();
    // used by ArkTS Card, for RSSurfaceNode from FRS,
    void enhancesSubContainer(bool hasContainer);
    RefPtr<RenderContext> externalRenderContext_;

    RefPtr<SubContainer> subContainer_;
    RefPtr<FormManagerDelegate> formManagerBridge_;
    RefPtr<AccessibilitySessionAdapterForm> accessibilitySessionAdapter_;

    FormSpecialStyle formSpecialStyle_;
    RequestFormInfo cardInfo_;
    bool isLoaded_ = false;
    bool isVisible_ = true;
    bool isBeenLayout_ = false;
    bool isUnTrust_ = false;
    bool isDynamic_ = true;
    bool isFrsNodeDetached_ = false;
    bool needSnapshotAgain_ = false;
    bool isSnapshot_ = false;
    RefPtr<PixelMap> pixelMap_ = nullptr;
    int64_t snapshotTimestamp_ = 0;
    int32_t scopeId_;
    std::string localeTag_ = AceApplicationInfo::GetInstance().GetLocaleTag();
    std::vector<std::string> formLinkInfos_;
    TimeStamp touchDownTime_;
    bool shouldResponseClick_ = false;
    Offset lastTouchLocation_;
    ColorMode colorMode = ColorMode::LIGHT;
    int32_t instanceId_ = Container::CurrentId();

    bool isFormObscured_ = false;
    bool isJsCard_ = true;
    bool isTransparencyEnable_ = false;
    bool isSkeletonAnimEnable_ = false;
    std::unordered_map<FormChildNodeType, RefPtr<FrameNode>> formChildrenNodeMap_;
    bool isTibetanLanguage_ = false;
    bool isManuallyClick_ = false;
    bool ShouldAddChildAtReuildFrame();
    bool isStaticFormSnaping_ = false;
    int64_t updateFormComponentTimestamp_ = 0;
};
} // namespace NG
} // namespace Ace
} // namespace OHOS

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_FORM_PATTERN_H
