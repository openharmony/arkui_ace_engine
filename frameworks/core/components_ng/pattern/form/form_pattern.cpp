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

#include "core/components_ng/pattern/form/form_pattern.h"

#include "form_constants.h"
#include "form_info_base.h"
#include "locale_config.h"
#include "locale_info.h"
#include "pointer_event.h"
#include "transaction/rs_interfaces.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/osal/resource_adapter_impl_v2.h"
#include "base/geometry/dimension.h"
#include "base/i18n/localization.h"
#include "base/log/event_report.h"
#include "base/log/log_wrapper.h"
#include "base/utils/string_utils.h"
#include "core/common/form_manager.h"
#include "core/components/form/resource/form_manager_delegate.h"
#include "core/components_ng/pattern/form/form_node.h"
#include "core/components_ng/pattern/shape/rect_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"

#if OHOS_STANDARD_SYSTEM
#include "form_info.h"
#endif

#include "core/common/udmf/udmf_client.h"
#include "form_pattern.h"

static const int64_t MAX_NUMBER_OF_JS = 0x20000000000000;

namespace OHOS::Ace::NG {
namespace {
constexpr double FORM_CLICK_OPEN_LIMIT_DISTANCE = 20.0;
constexpr uint32_t DELAY_TIME_FOR_FORM_SUBCONTAINER_CACHE = 30000;
constexpr uint32_t DELAY_TIME_FOR_FORM_SNAPSHOT_3S = 3000;
constexpr uint32_t DELAY_TIME_FOR_FORM_SNAPSHOT_EXTRA = 200;
constexpr uint32_t DELAY_TIME_FOR_SET_NON_TRANSPARENT = 70;
constexpr uint32_t DELAY_TIME_FOR_DELETE_IMAGE_NODE = 500;
constexpr uint32_t DELAY_TIME_FOR_RESET_MANUALLY_CLICK_FLAG = 3000;
constexpr double ARC_RADIUS_TO_DIAMETER = 2.0;
constexpr double NON_TRANSPARENT_VAL = 1.0;
constexpr double TRANSPARENT_VAL = 0;
constexpr int32_t MAX_CLICK_DURATION = 500000000; // ns
constexpr int32_t DOUBLE = 2;
constexpr char FORM_DIMENSION_SPLITTER = '*';
constexpr int32_t FORM_SHAPE_CIRCLE = 2;
constexpr double TIME_LIMIT_FONT_SIZE_BASE = 18.0;
constexpr double TIBETAN_TIME_LIMIT_FONT_SIZE_BASE = 9.0;
constexpr double ONE_DIMENSION_TIME_LIMIT_FONT_SIZE_BASE = 14.0;
constexpr float MAX_FONT_SCALE = 1.3f;
constexpr char TIME_LIMIT_RESOURCE_NAME[] = "form_disable_time_limit";
constexpr uint32_t TOP_BG_COLOR_DARK = 0xFF444549;
constexpr uint32_t BOTTOM_BG_COLOR_DARK = 0xFF2E3033;
constexpr uint32_t TOP_BG_COLOR_LIGHT = 0xFFDEDEEB;
constexpr uint32_t BOTTOM_BG_COLOR_LIGHT = 0xFFA1A3B3;
constexpr uint32_t FONT_COLOR_DARK = 0x99FFFFFF;
constexpr uint32_t FONT_COLOR_LIGHT = 0x99000000;
constexpr double TRANSITION_PERCENT = 0.1;
constexpr double TEXT_TRANSPARENT_VAL = 0.9;
constexpr int32_t FORM_DIMENSION_MIN_HEIGHT = 1;
constexpr int32_t FORM_UNLOCK_ANIMATION_DUATION = 250;
constexpr int32_t FORM_UNLOCK_ANIMATION_DELAY = 200;
constexpr char NO_FORM_DUMP[] = "-noform";

class FormSnapshotCallback : public Rosen::SurfaceCaptureCallback {
public:
    explicit FormSnapshotCallback(const WeakPtr<FormPattern>& node) : weakFormPattern_(node) {}
    ~FormSnapshotCallback() override = default;
    void OnSurfaceCapture(std::shared_ptr<Media::PixelMap> pixelMap) override
    {
        auto formPattern_ = weakFormPattern_.Upgrade();
        CHECK_NULL_VOID(formPattern_);
        formPattern_->OnSnapshot(pixelMap);
    }

private:
    WeakPtr<FormPattern> weakFormPattern_ = nullptr;
};

void PostTask(const TaskExecutor::Task& task, TaskExecutor::TaskType type, const std::string& name)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(task, type, name, PriorityType::HIGH);
}

void PostUITask(const TaskExecutor::Task& task, const std::string& name)
{
    PostTask(task, TaskExecutor::TaskType::UI, name);
}

void PostBgTask(const TaskExecutor::Task& task, const std::string& name)
{
    PostTask(task, TaskExecutor::TaskType::BACKGROUND, name);
}
} // namespace

FormPattern::FormPattern()
{
    ACE_SCOPED_TRACE("FormCreate");
}

FormPattern::~FormPattern() = default;

void FormPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
    host->GetRenderContext()->SetClipToBounds(true);
    host->GetRenderContext()->UpdateRenderGroup(true);
    // Init the render context for RSSurfaceNode from FRS.
    externalRenderContext_ = RenderContext::Create();
    // for external RSNode, name is meaningless.
    static RenderContext::ContextParam param = { RenderContext::ContextType::EXTERNAL, std::nullopt };
    externalRenderContext_->InitContext(false, param);
    InitFormManagerDelegate();
    auto eventHub = host->GetEventHub<FormEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnCache([weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto context = host->GetContextRefPtr();
        CHECK_NULL_VOID(context);
        auto subContainer = pattern->GetSubContainer();
        CHECK_NULL_VOID(subContainer);
        auto uiTaskExecutor =
            SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        auto id = subContainer->GetRunningCardId();
        TAG_LOGI(AceLogTag::ACE_FORM, "FormPattern::OnAttachToFrameNode, cardId: %{public}" PRId64, id);
        FormManager::GetInstance().AddSubContainer(id, subContainer);
        uiTaskExecutor.PostDelayedTask(
            [id, nodeId = subContainer->GetNodeId()] {
                auto cachedSubContainer = FormManager::GetInstance().GetSubContainer(id);
                if (cachedSubContainer != nullptr && cachedSubContainer->GetNodeId() == nodeId) {
                    FormManager::GetInstance().RemoveSubContainer(id);
                }
            },
            DELAY_TIME_FOR_FORM_SUBCONTAINER_CACHE, "ArkUIFormRemoveSubContainer");
    });

    InitClickEvent();

    scopeId_ = Container::CurrentId();
}

void FormPattern::InitClickEvent()
{
    // Init click event for static form.
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureEventHub = host->GetOrCreateGestureEventHub();
    auto clickCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto formPattern = weak.Upgrade();
        TAG_LOGI(AceLogTag::ACE_FORM, "gestureEvent - clickCallback");
        CHECK_NULL_VOID(formPattern);
        formPattern->HandleStaticFormEvent(
            { static_cast<float>(info.GetLocalLocation().GetX()), static_cast<float>(info.GetLocalLocation().GetY()) });
    };
    auto clickEvent = AceType::MakeRefPtr<ClickEvent>(std::move(clickCallback));
    gestureEventHub->AddClickEvent(clickEvent);

    // check touch duration in click event
    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto formPattern = weak.Upgrade();
        CHECK_NULL_VOID(formPattern);
        auto touchType = info.GetTouches().front().GetTouchType();
        if (touchType == TouchType::DOWN) {
            formPattern->HandleTouchDownEvent(info);
            return;
        }
        if (touchType == TouchType::UP || touchType == TouchType::CANCEL) {
            formPattern->HandleTouchUpEvent(info);
            return;
        }
    };
    auto touchEvent = AceType::MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gestureEventHub->AddTouchEvent(touchEvent);
}

void FormPattern::HandleTouchDownEvent(const TouchEventInfo& event)
{
    touchDownTime_ = event.GetTimeStamp();
    shouldResponseClick_ = true;
    if (!event.GetTouches().empty()) {
        lastTouchLocation_ = event.GetTouches().front().GetScreenLocation();
    }
}

void FormPattern::HandleTouchUpEvent(const TouchEventInfo& event)
{
    auto duration = event.GetTimeStamp().time_since_epoch().count() - touchDownTime_.time_since_epoch().count();
    if (duration > MAX_CLICK_DURATION) {
        TAG_LOGI(AceLogTag::ACE_FORM, "reject click. duration is %{public}lld.", duration);
        shouldResponseClick_ = false;
        return;
    }
    if (event.GetTouches().empty()) {
        return;
    }
    auto distance = event.GetTouches().front().GetScreenLocation() - lastTouchLocation_;
    if (distance.GetDistance() > FORM_CLICK_OPEN_LIMIT_DISTANCE) {
        shouldResponseClick_ = false;
    }
}

void FormPattern::HandleUnTrustForm()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (externalRenderContext_) {
        auto renderContext = DynamicCast<NG::RosenRenderContext>(host->GetRenderContext());
        CHECK_NULL_VOID(renderContext);
        renderContext->RemoveChild(externalRenderContext_);
    }

    isUnTrust_ = true;
    isLoaded_ = true;
    if (!isJsCard_) {
        RequestFormInfo info;
        if (ShouldLoadFormSkeleton(false, info)) {
            LoadFormSkeleton(true);
        }
    }

    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    auto parent = host->GetParent();
    CHECK_NULL_VOID(parent);
    parent->MarkNeedSyncRenderTree();
    parent->RebuildRenderContextTree();
    host->GetRenderContext()->RequestNextFrame();
}

void FormPattern::UpdateBackgroundColorWhenUnTrustForm()
{
    if (!isUnTrust_) {
        return;
    }

    if (colorMode != SystemProperties::GetColorMode()) {
        colorMode = SystemProperties::GetColorMode();
        HandleUnTrustForm();
    }
}

void FormPattern::HandleSnapshot(uint32_t delayTime, const std::string& nodeIdStr)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto executor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(executor);
    snapshotTimestamp_ = GetCurrentTimestamp();
    if (isDynamic_) {
        if (formChildrenNodeMap_.find(FormChildNodeType::FORM_STATIC_IMAGE_NODE) != formChildrenNodeMap_.end()) {
            executor->RemoveTask(TaskExecutor::TaskType::UI, "ArkUIFormSetNonTransparentAfterRecover_" + nodeIdStr);
            executor->RemoveTask(TaskExecutor::TaskType::UI, "ArkUIFormDeleteImageNodeAfterRecover_" + nodeIdStr);
            RemoveFrsNode();
            ReleaseRenderer();
            UnregisterAccessibility();
            isSnapshot_ = true;
            needSnapshotAgain_ = false;
            return;
        }
    }

    executor->PostDelayedTask(
        [weak = WeakClaim(this), delayTime]() mutable {
            auto form = weak.Upgrade();
            CHECK_NULL_VOID(form);
            int64_t currentTime = GetCurrentTimestamp();
            if (currentTime - form->snapshotTimestamp_ < delayTime) {
                TAG_LOGD(AceLogTag::ACE_FORM, "another snapshot task has been posted.");
                return;
            }
            form->TakeSurfaceCaptureForUI();
        },
        TaskExecutor::TaskType::UI, delayTime, "ArkUIFormTakeSurfaceCapture");
}

void FormPattern::HandleStaticFormEvent(const PointF& touchPoint)
{
    if (formLinkInfos_.empty() || isDynamic_ || !shouldResponseClick_) {
        return;
    }
    TAG_LOGI(AceLogTag::ACE_FORM, "StaticFrom click.");
    for (const auto& info : formLinkInfos_) {
        auto linkInfo = JsonUtil::ParseJsonString(info);
        CHECK_NULL_VOID(linkInfo);
        auto action = linkInfo->GetValue("action")->GetString();
        auto rectStr = linkInfo->GetValue("formLinkRect")->GetString();
        RectF linkRect = RectF::FromString(rectStr);
        if (linkRect.IsInRegion(touchPoint)) {
            OnActionEvent(action);
            break;
        }
    }
}

void FormPattern::HandleEnableForm(const bool enable)
{
    TAG_LOGI(AceLogTag::ACE_FORM, "FormPattern::HandleEnableForm, enable = %{public}d", enable);
    auto newFormSpecialStyle = formSpecialStyle_;
    newFormSpecialStyle.SetIsForbiddenByParentControl(!enable);
    HandleFormStyleOperation(newFormSpecialStyle);
}

void FormPattern::TakeSurfaceCaptureForUI()
{
    if (isFrsNodeDetached_) {
        TAG_LOGI(AceLogTag::ACE_FORM, "Frs node is detached, cancel snapshot.");
        return;
    }
    
    if (isDynamic_) {
        formLinkInfos_.clear();
    }
    TAG_LOGI(AceLogTag::ACE_FORM, "Static-form take snapshot.");
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<FormLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto renderContext = host->GetRenderContext();
    auto visible = layoutProperty->GetVisibleType().value_or(VisibleType::VISIBLE);
    auto opacity = renderContext->GetOpacityValue(NON_TRANSPARENT_VAL);
    if (visible == VisibleType::INVISIBLE || visible == VisibleType::GONE || opacity == TRANSPARENT_VAL) {
        TAG_LOGI(AceLogTag::ACE_FORM, "The form is invisible, TakeSurfaceCaptureForUI later.");
        needSnapshotAgain_ = true;
        return;
    }

    if (formChildrenNodeMap_.find(FormChildNodeType::FORM_FORBIDDEN_ROOT_NODE)
        == formChildrenNodeMap_.end()) {
        SnapshotSurfaceNode();
        return;
    }
    UpdateChildNodeOpacity(FormChildNodeType::FORM_SURFACE_NODE, NON_TRANSPARENT_VAL);
    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    uiTaskExecutor.PostDelayedTask(
        [weak = WeakClaim(this)] {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->SnapshotSurfaceNode();
        },
        DELAY_TIME_FOR_FORM_SNAPSHOT_EXTRA, "ArkUIFormDelaySnapshotSurfaceNode");
}
 
void FormPattern::SnapshotSurfaceNode()
{
    auto externalContext = DynamicCast<NG::RosenRenderContext>(GetExternalRenderContext());
    CHECK_NULL_VOID(externalContext);
    auto rsNode = externalContext->GetRSNode();
    CHECK_NULL_VOID(rsNode);
    auto& rsInterface = Rosen::RSInterfaces::GetInstance();
    rsInterface.TakeSurfaceCaptureForUI(rsNode, std::make_shared<FormSnapshotCallback>(WeakClaim(this)));
}

void FormPattern::OnSnapshot(std::shared_ptr<Media::PixelMap> pixelMap)
{
    ContainerScope scope(scopeId_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto uiTaskExecutor =
        SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    uiTaskExecutor.PostTask([weak = WeakClaim(this), pixelMap] {
        auto formPattern = weak.Upgrade();
        CHECK_NULL_VOID(formPattern);
        formPattern->HandleOnSnapshot(pixelMap);
        }, "ArkUIFormHandleOnSnapshot");
}

void FormPattern::HandleOnSnapshot(std::shared_ptr<Media::PixelMap> pixelMap)
{
    TAG_LOGI(AceLogTag::ACE_FORM, "call.");
    CHECK_NULL_VOID(pixelMap);
    pixelMap_ = PixelMap::CreatePixelMap(reinterpret_cast<void*>(&pixelMap));
    UpdateStaticCard();
    isSnapshot_ = true;
    needSnapshotAgain_ = false;
}

void FormPattern::OnAccessibilityChildTreeRegister(uint32_t windowId, int32_t treeId, int64_t accessibilityId)
{
    TAG_LOGD(AceLogTag::ACE_FORM, "call, treeId: %{public}d, id: %{public}" PRId64, treeId, accessibilityId);
    if (formManagerBridge_ == nullptr) {
        TAG_LOGE(AceLogTag::ACE_FORM, "formManagerBridge_ is null");
        return;
    }
    formManagerBridge_->OnAccessibilityChildTreeRegister(windowId, treeId, accessibilityId);
}

void FormPattern::OnAccessibilityChildTreeDeregister()
{
    TAG_LOGD(AceLogTag::ACE_FORM, "call.");
    if (formManagerBridge_ == nullptr) {
        TAG_LOGE(AceLogTag::ACE_FORM, "formManagerBridge_ is null");
        return;
    }
    formManagerBridge_->OnAccessibilityChildTreeDeregister();
}

void FormPattern::OnAccessibilityDumpChildInfo(const std::vector<std::string>& params, std::vector<std::string>& info)
{
    TAG_LOGD(AceLogTag::ACE_FORM, "call.");
    if (formManagerBridge_ == nullptr) {
        TAG_LOGE(AceLogTag::ACE_FORM, "formManagerBridge_ is null");
        return;
    }
    formManagerBridge_->OnAccessibilityDumpChildInfo(params, info);
}

RefPtr<AccessibilitySessionAdapter> FormPattern::GetAccessibilitySessionAdapter()
{
    return accessibilitySessionAdapter_;
}

void FormPattern::UpdateStaticCard()
{
    // 1. Use imageNode to display pixelMap
    UpdateImageNode();
    // 2. Remove FrsNode from formNode
    RemoveFrsNode();
    // 3. Release renderer obj
    ReleaseRenderer();
    // 4. clear form node ChildTree register flag.  can do register again
    UnregisterAccessibility();
}

void FormPattern::SetNonTransparentAfterRecover()
{
    ACE_FUNCTION_TRACE();
    // set frs node non transparent
    if (formChildrenNodeMap_.find(FormChildNodeType::FORM_FORBIDDEN_ROOT_NODE)
        == formChildrenNodeMap_.end()) {
        UpdateChildNodeOpacity(FormChildNodeType::FORM_SURFACE_NODE, NON_TRANSPARENT_VAL);
        TAG_LOGI(AceLogTag::ACE_FORM, "setOpacity:1");
    } else {
        TAG_LOGW(AceLogTag::ACE_FORM, "has forbidden node");
    }
}

void FormPattern::DeleteImageNodeAfterRecover(bool needHandleCachedClick)
{
    ACE_FUNCTION_TRACE();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    // delete image rs node and frame node
    RemoveFormChildNode(FormChildNodeType::FORM_STATIC_IMAGE_NODE);

    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    auto parent = host->GetParent();
    CHECK_NULL_VOID(parent);
    parent->MarkNeedSyncRenderTree();
    parent->RebuildRenderContextTree();
    renderContext->RequestNextFrame();

    // handle cached pointer event
    if (needHandleCachedClick && formManagerBridge_) {
        formManagerBridge_->HandleCachedClickEvents();
    }
}

RefPtr<FrameNode> FormPattern::CreateImageNode()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto formNode = DynamicCast<FormNode>(host);
    CHECK_NULL_RETURN(formNode, nullptr);
    auto imageId = formNode->GetImageId();
    RefPtr<FrameNode> imageNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, imageId,
        AceType::MakeRefPtr<ImagePattern>());
    CHECK_NULL_RETURN(imageNode, nullptr);
    AddFormChildNode(FormChildNodeType::FORM_STATIC_IMAGE_NODE, imageNode);
    auto imagePattern = imageNode->GetPattern<ImagePattern>();
    CHECK_NULL_RETURN(imagePattern, nullptr);
    imagePattern->SetSyncLoad(true);
    RefPtr<FrameNode> disableStyleRootNode = GetFormChildNode(FormChildNodeType::FORM_FORBIDDEN_ROOT_NODE);
    disableStyleRootNode == nullptr ? host->AddChild(imageNode) :
        host->AddChildBefore(imageNode, disableStyleRootNode);
    auto eventHub = imageNode->GetOrCreateGestureEventHub();
    if (eventHub != nullptr) {
        eventHub->RemoveDragEvent();
    }
    return imageNode;
}

void FormPattern::UpdateImageNode()
{
    ContainerScope scope(scopeId_);
    CHECK_NULL_VOID(pixelMap_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    RemoveFormChildNode(FormChildNodeType::FORM_STATIC_IMAGE_NODE);
    auto imageNode = CreateImageNode();
    CHECK_NULL_VOID(imageNode);
    auto pixelLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(pixelLayoutProperty);
    auto pixelSourceInfo = ImageSourceInfo(pixelMap_);

    auto width = static_cast<float>(cardInfo_.width.Value()) - cardInfo_.borderWidth * DOUBLE;
    auto height = static_cast<float>(cardInfo_.height.Value()) - cardInfo_.borderWidth * DOUBLE;
    CalcSize idealSize = { CalcLength(width), CalcLength(height) };
    MeasureProperty layoutConstraint;
    layoutConstraint.selfIdealSize = idealSize;
    layoutConstraint.maxSize = idealSize;
    imageNode->UpdateLayoutConstraint(layoutConstraint);
    pixelLayoutProperty->UpdateImageSourceInfo(pixelSourceInfo);
    auto externalContext = DynamicCast<NG::RosenRenderContext>(imageNode->GetRenderContext());
    CHECK_NULL_VOID(externalContext);
    externalContext->SetVisible(true);
    if (formChildrenNodeMap_.find(FormChildNodeType::FORM_FORBIDDEN_ROOT_NODE)
        != formChildrenNodeMap_.end()) {
        externalContext->SetOpacity(TRANSPARENT_VAL);
    }
    imageNode->MarkModifyDone();
    imageNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void FormPattern::RemoveFrsNode()
{
    ContainerScope scope(scopeId_);
    CHECK_NULL_VOID(externalRenderContext_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = DynamicCast<NG::RosenRenderContext>(host->GetRenderContext());
    CHECK_NULL_VOID(renderContext);
    renderContext->RemoveChild(externalRenderContext_);

    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    auto parent = host->GetParent();
    CHECK_NULL_VOID(parent);
    parent->MarkNeedSyncRenderTree();
    parent->RebuildRenderContextTree();
    host->GetRenderContext()->RequestNextFrame();
}

void FormPattern::ReleaseRenderer()
{
    ContainerScope scope(scopeId_);
    CHECK_NULL_VOID(formManagerBridge_);
    formManagerBridge_->ReleaseRenderer();
}

void FormPattern::OnRebuildFrame()
{
    if (isSnapshot_) {
        return;
    }

    if (isSkeletonAnimEnable_ && !isTransparencyEnable_ && !ShouldAddChildAtReuildFrame()) {
        TAG_LOGW(AceLogTag::ACE_FORM, "should not add child");
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->AddChild(externalRenderContext_, 0);
}

void FormPattern::OnVisibleChange(bool isVisible)
{
    isVisible_ = isVisible;
}

void FormPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureEventHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureEventHub);
    // FormComponent do not response to user's onClick callback.
    gestureEventHub->ClearUserOnClick();

    auto layoutProperty = host->GetLayoutProperty<FormLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto &&layoutConstraint = layoutProperty->GetCalcLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint);
    auto size = layoutConstraint->selfIdealSize;
    CHECK_NULL_VOID(size);
    auto sizeWidth = size->Width();
    auto sizeHeight = size->Height();
    CHECK_NULL_VOID(sizeWidth);
    CHECK_NULL_VOID(sizeHeight);
    auto width = sizeWidth->GetDimension();
    auto height = sizeHeight->GetDimension();
    if (width.Unit() == DimensionUnit::PERCENT || height.Unit() == DimensionUnit::PERCENT) {
        /**
         * If DimensionUnit is DimensionUnit::PERCENT, it need parentNode-size to calculate formNode-size.
         * However, the parentNode-size cannot be obtained in the current callback function,
         * so HandleFormComponent in OnDirtyLayoutWrapperSwap function.
         */
        return;
    }
    // Convert DimensionUnit to DimensionUnit::PX
    auto info = layoutProperty->GetRequestFormInfo().value_or(RequestFormInfo());
    TAG_LOGI(AceLogTag::ACE_FORM, "FormPattern::OnModifyDone, info.id: %{public}" PRId64, info.id);
    info.width = Dimension(width.ConvertToPx());
    info.height = Dimension(height.ConvertToPx());
    auto &&borderWidthProperty = layoutProperty->GetBorderWidthProperty();
    float borderWidth = 0.0f;
    if (borderWidthProperty && borderWidthProperty->topDimen) {
        borderWidth = borderWidthProperty->topDimen->ConvertToPx();
    }
    info.borderWidth = borderWidth;
    layoutProperty->UpdateRequestFormInfo(info);
    UpdateBackgroundColorWhenUnTrustForm();
    info.obscuredMode = isFormObscured_;
    info.obscuredMode |= (CheckFormBundleForbidden(info.bundleName) || IsFormBundleLocked(info.bundleName, info.id));
    auto wantWrap = info.wantWrap;
    if (wantWrap) {
        bool isEnable = wantWrap->GetWant().GetBoolParam(OHOS::AppExecFwk::Constants::FORM_ENABLE_SKELETON_KEY, false);
        TAG_LOGD(AceLogTag::ACE_FORM, "FORM_ENABLE_SKELETON_KEY %{public}d", isEnable);
    }
    HandleFormComponent(info);

    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetAccessibilityLevel(AccessibilityProperty::Level::NO_STR);
}

bool FormPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    isBeenLayout_ = true;
    auto size = dirty->GetGeometryNode()->GetFrameSize();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto layoutProperty = host->GetLayoutProperty<FormLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    auto info = layoutProperty->GetRequestFormInfo().value_or(RequestFormInfo());
    info.width = Dimension(size.Width());
    info.height = Dimension(size.Height());
    if (std::isinf(info.width.Value()) || std::isnan(info.width.Value()) || std::isinf(info.height.Value())
        || std::isnan(info.height.Value())) {
        TAG_LOGE(AceLogTag::ACE_FORM, "size invalid, width:%{public}f height:%{public}f",
            info.width.Value(), info.height.Value());
        return false;
    }
    auto &&borderWidthProperty = layoutProperty->GetBorderWidthProperty();
    float borderWidth = 0.0f;
    if (borderWidthProperty && borderWidthProperty->topDimen) {
        borderWidth = borderWidthProperty->topDimen->ConvertToPx();
    }
    info.borderWidth = borderWidth;
    layoutProperty->UpdateRequestFormInfo(info);

    UpdateBackgroundColorWhenUnTrustForm();
    info.obscuredMode = isFormObscured_;
    info.obscuredMode |= (CheckFormBundleForbidden(info.bundleName) || IsFormBundleLocked(info.bundleName, info.id));
    HandleFormComponent(info);
    return true;
}

void FormPattern::HandleFormComponent(const RequestFormInfo& info)
{
    ACE_FUNCTION_TRACE();
    if (info.bundleName != cardInfo_.bundleName || info.abilityName != cardInfo_.abilityName ||
        info.moduleName != cardInfo_.moduleName || info.cardName != cardInfo_.cardName ||
        info.dimension != cardInfo_.dimension || info.renderingMode != cardInfo_.renderingMode) {
        AddFormComponent(info);
    } else {
        UpdateFormComponent(info);
    }
}

void FormPattern::AddFormComponent(const RequestFormInfo& info)
{
    ACE_FUNCTION_TRACE();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    // When cardInfo has changed, it will call AddForm in Fwk
    // If the width or height equal to zero, it will not
    if (NonPositive(info.width.Value()) || NonPositive(info.height.Value())) {
        TAG_LOGW(AceLogTag::ACE_FORM, "Invalid form size.");
        return;
    }
    TAG_LOGI(AceLogTag::ACE_FORM, "width: %{public}f   height: %{public}f  borderWidth: %{public}f",
        info.width.Value(), info.height.Value(), info.borderWidth);
    cardInfo_ = info;
    if (info.dimension == static_cast<int32_t>(OHOS::AppExecFwk::Constants::Dimension::DIMENSION_1_1)
        || info.shape == FORM_SHAPE_CIRCLE) {
        BorderRadiusProperty borderRadius;
        Dimension diameter = std::min(info.width, info.height);
        borderRadius.SetRadius(diameter / ARC_RADIUS_TO_DIAMETER);
        host->GetRenderContext()->UpdateBorderRadius(borderRadius);
    }
    isJsCard_ = true;
    RefPtr<PipelineContext> pipeline = host->GetContextRefPtr();
    PostBgTask([weak = WeakClaim(this), info, pipeline] {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->AddFormComponentTask(info, pipeline);
        }, "ArkUIAddFormComponent");
}

void FormPattern::AddFormComponentTask(const RequestFormInfo& info, RefPtr<PipelineContext> pipeline)
{
#if OHOS_STANDARD_SYSTEM
    AppExecFwk::FormInfo formInfo;
    if (FormManagerDelegate::GetFormInfo(info.bundleName, info.moduleName, info.cardName, formInfo) &&
        formInfo.uiSyntax == AppExecFwk::FormType::ETS) {
        isJsCard_ = false;
    }
#endif

    AddFormComponentUI(formInfo.transparencyEnabled, info);

    if (!formManagerBridge_) {
        TAG_LOGE(AceLogTag::ACE_FORM, "Form manager delegate is nullptr.");
        return;
    }
#if OHOS_STANDARD_SYSTEM
    formManagerBridge_->AddForm(pipeline, info, formInfo);
#else
    formManagerBridge_->AddForm(pipeline, info);
#endif

    if (formInfo.transparencyEnabled) {
        TAG_LOGI(AceLogTag::ACE_FORM, "transparencyEnabled.");
        return;
    }
    bool isFormBundleLocked = IsFormBundleLocked(info.bundleName, info.id);
    bool isFormBundleForbidden = CheckFormBundleForbidden(info.bundleName);
    if (isFormBundleLocked || isFormBundleForbidden)  {
        auto newFormSpecialStyle = formSpecialStyle_;
        newFormSpecialStyle.SetIsLockedByAppLock(isFormBundleLocked);
        newFormSpecialStyle.SetIsForbiddenByParentControl(isFormBundleForbidden);
        PostUITask([weak = WeakClaim(this), info, newFormSpecialStyle] {
            ACE_SCOPED_TRACE("ArkUILoadDisableFormStyle");
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->HandleFormStyleOperation(newFormSpecialStyle, info);
            }, "ArkUILoadDisableFormStyle");
    }
}

void FormPattern::AddFormComponentUI(bool isTransparencyEnabled, const RequestFormInfo& info)
{
    PostUITask([weak = WeakClaim(this), isTransparencyEnabled, info, isJsCard = isJsCard_] {
        ACE_SCOPED_TRACE("ArkUIAddFormComponentUI");
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        pattern->CreateCardContainer();
        if (host->IsDraggable()) {
            pattern->EnableDrag();
        }

#if OHOS_STANDARD_SYSTEM
        pattern->SetTransparencyConfig(isTransparencyEnabled, info);
        pattern->SetSkeletonEnableConfig(info);
        if (!isJsCard && !pattern->isTransparencyEnable_
            && pattern->ShouldLoadFormSkeleton(isTransparencyEnabled, info)) {
            pattern->LoadFormSkeleton();
        }
#endif
        }, "ArkUIAddFormComponentUI");
}

void FormPattern::UpdateFormComponent(const RequestFormInfo& info)
{
    if (formManagerBridge_) {
#if OHOS_STANDARD_SYSTEM
        AppExecFwk::FormInfo formInfo;
        FormManagerDelegate::GetFormInfo(info.bundleName, info.moduleName, info.cardName, formInfo);
        std::lock_guard<std::mutex> lock(formManagerBridge_->GetRecycleMutex());
        formManagerBridge_->SetParamForWant(info, formInfo);
#endif
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<FormLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (cardInfo_.allowUpdate != info.allowUpdate) {
        cardInfo_.allowUpdate = info.allowUpdate;
        if (subContainer_) {
            subContainer_->SetAllowUpdate(cardInfo_.allowUpdate);
        }
        if (formManagerBridge_) {
            formManagerBridge_->SetAllowUpdate(cardInfo_.allowUpdate);
        }
    }
    if (cardInfo_.width != info.width || cardInfo_.height != info.height || cardInfo_.borderWidth != info.borderWidth) {
        UpdateFormComponentSize(info);
    }
    if (cardInfo_.obscuredMode != info.obscuredMode) {
        cardInfo_.obscuredMode = info.obscuredMode;
        if (formManagerBridge_) {
            formManagerBridge_->SetObscured(info.obscuredMode);
        }
    }
    if (isLoaded_) {
        auto visible = layoutProperty->GetVisibleType().value_or(VisibleType::VISIBLE);
        layoutProperty->UpdateVisibility(visible);
        if (!isDynamic_ && !isSnapshot_ && needSnapshotAgain_) {
            auto renderContext = host->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            auto opacity = renderContext->GetOpacityValue(NON_TRANSPARENT_VAL);
            std::string nodeIdStr = std::to_string(host->GetId());
            TAG_LOGI(AceLogTag::ACE_FORM,
                "Static-form, current opacity: %{public}f, visible: %{public}d, nodeId: %{public}s.",
                opacity, static_cast<int>(visible), nodeIdStr.c_str());
            if (visible == VisibleType::VISIBLE && opacity == NON_TRANSPARENT_VAL) {
                HandleSnapshot(DELAY_TIME_FOR_FORM_SNAPSHOT_3S, nodeIdStr);
            }
        }
    }
    UpdateSpecialStyleCfg();
    UpdateConfiguration();
}

void FormPattern::UpdateFormComponentSize(const RequestFormInfo& info)
{
    TAG_LOGI(AceLogTag::ACE_FORM,
        "update size, id: %{public}" PRId64 "  width: %{public}f  height: %{public}f  borderWidth: %{public}f",
        info.id, info.width.Value(), info.height.Value(), info.borderWidth);
    cardInfo_.width = info.width;
    cardInfo_.height = info.height;
    cardInfo_.borderWidth = info.borderWidth;
    auto externalRenderContext = DynamicCast<NG::RosenRenderContext>(GetExternalRenderContext());
    CHECK_NULL_VOID(externalRenderContext);

    externalRenderContext->SetBounds(round(cardInfo_.borderWidth), round(cardInfo_.borderWidth),
        round(cardInfo_.width.Value() - cardInfo_.borderWidth * DOUBLE),
        round(cardInfo_.height.Value() - cardInfo_.borderWidth * DOUBLE));

    if (formManagerBridge_) {
        formManagerBridge_->NotifySurfaceChange(info.width.Value(), info.height.Value(), info.borderWidth);
    } else {
        TAG_LOGE(AceLogTag::ACE_FORM, "form manager delagate is nullptr, card id is %{public}" PRId64 ".",
            cardInfo_.id);
    }

    auto imageNode = GetFormChildNode(FormChildNodeType::FORM_STATIC_IMAGE_NODE);
    auto disableStyleRootNode = GetFormChildNode(FormChildNodeType::FORM_FORBIDDEN_ROOT_NODE);
    if (imageNode != nullptr || disableStyleRootNode != nullptr) {
        auto width = static_cast<float>(info.width.Value()) - info.borderWidth * DOUBLE;
        auto height = static_cast<float>(info.height.Value()) - info.borderWidth * DOUBLE;
        CalcSize idealSize = { CalcLength(width), CalcLength(height) };
        MeasureProperty layoutConstraint;
        layoutConstraint.selfIdealSize = idealSize;
        layoutConstraint.maxSize = idealSize;
        if (imageNode != nullptr) {
            imageNode->UpdateLayoutConstraint(layoutConstraint);
        }
        if (disableStyleRootNode != nullptr) {
            disableStyleRootNode->UpdateLayoutConstraint(layoutConstraint);
        }
    }

    auto formSkeletonNode = GetFormChildNode(FormChildNodeType::FORM_SKELETON_NODE);
    if (formSkeletonNode) {
        LoadFormSkeleton(true);
    }

    if (info.dimension == static_cast<int32_t>(OHOS::AppExecFwk::Constants::Dimension::DIMENSION_1_1)) {
        BorderRadiusProperty borderRadius;
        Dimension diameter = std::min(info.width, info.height);
        borderRadius.SetRadius(diameter / ARC_RADIUS_TO_DIAMETER);
        GetHost()->GetRenderContext()->UpdateBorderRadius(borderRadius);
    }
    if (subContainer_) {
        subContainer_->SetFormPattern(WeakClaim(this));
        subContainer_->UpdateRootElementSize();
        subContainer_->UpdateSurfaceSizeWithAnimathion();
    }
}

void FormPattern::UpdateSpecialStyleCfg()
{
    auto columnNode = GetFormChildNode(FormChildNodeType::FORM_FORBIDDEN_ROOT_NODE);
    CHECK_NULL_VOID(columnNode);
    auto renderContext = columnNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateBackgroundColor(GetFormStyleBackGroundColor());
    auto attribution = formSpecialStyle_.GetFormStyleAttribution();
    if (attribution == FormStyleAttribution::PARENT_CONTROL) {
        UpdateTimeLimitFontCfg();
        return;
    }
    if (attribution == FormStyleAttribution::APP_LOCK) {
        UpdateAppLockCfg();
    }
}

void FormPattern::UpdateTimeLimitFontCfg()
{
    auto textNode = GetFormChildNode(FormChildNodeType::FORM_SPECIAL_STYLE_NODE);
    CHECK_NULL_VOID(textNode);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);

    Dimension fontSize(GetTimeLimitFontSize());
    if (!textLayoutProperty->GetFontSize().has_value() ||
        !NearEqual(textLayoutProperty->GetFontSize().value(), fontSize)) {
        TAG_LOGD(AceLogTag::ACE_FORM, "bundleName = %{public}s, id: %{public}" PRId64 ", UpdateFontSize:%{public}f.",
            cardInfo_.bundleName.c_str(), cardInfo_.id, fontSize.Value());
        textLayoutProperty->UpdateFontSize(fontSize);
        textNode->MarkModifyDone();
        textNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void FormPattern::UpdateAppLockCfg()
{
    auto node = GetFormChildNode(FormChildNodeType::FORM_SPECIAL_STYLE_NODE);
    CHECK_NULL_VOID(node);
    auto imageLayoutProperty = node->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    auto info = ImageSourceInfo("");
    info.SetResourceId(InternalResource::ResourceId::APP_LOCK_SVG);
    info.SetFillColor(SystemProperties::GetColorMode() == ColorMode::DARK ? Color::WHITE : Color::BLACK);
    imageLayoutProperty->UpdateImageSourceInfo(info);
    node->MarkModifyDone();
    node->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void FormPattern::LoadDisableFormStyle(const RequestFormInfo& info, bool isRefresh)
{
    if (IsMaskEnableForm(info)) {
        if (!formManagerBridge_) {
            TAG_LOGE(AceLogTag::ACE_FORM, "LoadDisableFormStyle failed, form manager deleget is null!");
            return;
        }

        formManagerBridge_->SetObscured(false);
        return;
    }

    if (!isRefresh && GetFormChildNode(FormChildNodeType::FORM_FORBIDDEN_ROOT_NODE) != nullptr &&
        GetFormChildNode(FormChildNodeType::FORM_SPECIAL_STYLE_NODE) != nullptr) {
        TAG_LOGW(AceLogTag::ACE_FORM, "Form disable style node already exist.");
        return;
    }

    TAG_LOGI(AceLogTag::ACE_FORM, "FormPattern::LoadDisableFormStyle");
    RemoveFormChildNode(FormChildNodeType::FORM_SPECIAL_STYLE_NODE);
    RemoveFormChildNode(FormChildNodeType::FORM_FORBIDDEN_ROOT_NODE);
    int32_t dimension = cardInfo_.dimension;
    int32_t dimensionHeight = GetFormDimensionHeight(dimension);
    if (dimensionHeight <= 0) {
        TAG_LOGE(AceLogTag::ACE_FORM, "LoadDisableFormStyle failed, invalid dimensionHeight!");
        return;
    }

    auto columnNode = CreateColumnNode(FormChildNodeType::FORM_FORBIDDEN_ROOT_NODE);
    CHECK_NULL_VOID(columnNode);
    auto renderContext = columnNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateBackgroundColor(GetFormStyleBackGroundColor());

    auto node = CreateActionNode();
    CHECK_NULL_VOID(node);
    node->MarkModifyDone();
    node->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    columnNode->MarkModifyDone();
    columnNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<FormLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto visible = layoutProperty->GetVisibleType().value_or(VisibleType::VISIBLE);
    layoutProperty->UpdateVisibility(visible);

    UpdateChildNodeOpacity(FormChildNodeType::FORM_SURFACE_NODE, TRANSPARENT_VAL);
    UpdateChildNodeOpacity(FormChildNodeType::FORM_STATIC_IMAGE_NODE, TRANSPARENT_VAL);
    UpdateChildNodeOpacity(FormChildNodeType::FORM_SKELETON_NODE, TRANSPARENT_VAL);
}

RefPtr<FrameNode> FormPattern::CreateActionNode()
{
    auto attribution = formSpecialStyle_.GetFormStyleAttribution();
    if (attribution == FormStyleAttribution::PARENT_CONTROL) {
        return CreateTimeLimitNode();
    }
    if (attribution == FormStyleAttribution::APP_LOCK) {
        return CreateAppLockNode();
    }
    return nullptr;
}

void FormPattern::RemoveDisableFormStyle(const RequestFormInfo& info)
{
    if (!IsMaskEnableForm(info)) {
        UpdateChildNodeOpacity(FormChildNodeType::FORM_SURFACE_NODE, NON_TRANSPARENT_VAL);
        UpdateChildNodeOpacity(FormChildNodeType::FORM_STATIC_IMAGE_NODE, NON_TRANSPARENT_VAL);
        UpdateChildNodeOpacity(FormChildNodeType::FORM_SKELETON_NODE, CONTENT_BG_OPACITY);
        RemoveFormChildNode(FormChildNodeType::FORM_SPECIAL_STYLE_NODE);
        RemoveFormChildNode(FormChildNodeType::FORM_FORBIDDEN_ROOT_NODE);
        return;
    }
    if (!formManagerBridge_) {
        TAG_LOGE(AceLogTag::ACE_FORM, "RemoveDisableFormStyle failed, form manager deleget is null!");
        return;
    }
    formManagerBridge_->SetObscured(false);
}

void FormPattern::LoadFormSkeleton(bool isRefresh)
{
    TAG_LOGI(AceLogTag::ACE_FORM, "LoadFormSkeleton");
    if (!isRefresh && GetFormChildNode(FormChildNodeType::FORM_SKELETON_NODE) != nullptr) {
        TAG_LOGW(AceLogTag::ACE_FORM, "LoadFormSkeleton failed, repeat load!");
        return;
    }

    int32_t dimension = cardInfo_.dimension;
    int32_t dimensionHeight = GetFormDimensionHeight(dimension);
    if (dimensionHeight <= 0) {
        TAG_LOGE(AceLogTag::ACE_FORM, "LoadFormSkeleton failed, invalid dimensionHeight!");
        return;
    }

    RemoveFormChildNode(FormChildNodeType::FORM_SKELETON_NODE);
    auto columnNode = CreateColumnNode(FormChildNodeType::FORM_SKELETON_NODE);
    CHECK_NULL_VOID(columnNode);
    double cardWidth = cardInfo_.width.Value();
    double cardHeight = cardInfo_.height.Value();
    auto colorMode = SystemProperties::GetColorMode();
    bool isDarkMode = colorMode == ColorMode::DARK;
    std::shared_ptr<FormSkeletonParams> params = std::make_shared<FormSkeletonParams>(cardWidth,
        cardHeight, dimension, dimensionHeight, isDarkMode);
    CreateSkeletonView(columnNode, params, dimensionHeight);

    auto renderContext = columnNode->GetRenderContext();
    if (renderContext != nullptr) {
        BlurStyleOption styleOption;
        styleOption.blurStyle = static_cast<BlurStyle>(static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK));
        renderContext->UpdateBackBlurStyle(styleOption);
        renderContext->UpdateBackgroundColor(isDarkMode ?
            Color(CONTENT_BG_COLOR_DARK) : Color(CONTENT_BG_COLOR_LIGHT));
        double opacity = formChildrenNodeMap_.find(FormChildNodeType::FORM_FORBIDDEN_ROOT_NODE)
            != formChildrenNodeMap_.end() ? TRANSPARENT_VAL : CONTENT_BG_OPACITY;
        renderContext->SetOpacity(opacity);
    }
    columnNode->MarkModifyDone();
    columnNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<FormLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto visible = layoutProperty->GetVisibleType().value_or(VisibleType::VISIBLE);
    layoutProperty->UpdateVisibility(visible);
}

bool FormPattern::ShouldLoadFormSkeleton(bool isTransparencyEnabled, const RequestFormInfo &info)
{
    auto wantWrap = info.wantWrap;
    if (isUnTrust_) {
        return true;
    }

    if (!wantWrap ||
        !wantWrap->GetWant().GetBoolParam(OHOS::AppExecFwk::Constants::FORM_ENABLE_SKELETON_KEY, false)) {
        TAG_LOGD(AceLogTag::ACE_FORM, "LoadFormSkeleton ignored, not enable.");
        return false;
    }

    if (isTransparencyEnabled && wantWrap) {
        auto color = wantWrap->GetWant().GetStringParam(OHOS::AppExecFwk::Constants::PARAM_FORM_TRANSPARENCY_KEY);
        Color bgColor;
        if (Color::ParseColorString(color, bgColor) && bgColor == Color::TRANSPARENT) {
            TAG_LOGD(AceLogTag::ACE_FORM, "LoadFormSkeleton ignored, bgColor: %{public}s", color.c_str());
            return false;
        }
    }

    if (info.renderingMode ==
        static_cast<int32_t>(OHOS::AppExecFwk::Constants::RenderingMode::SINGLE_COLOR)) {
        TAG_LOGD(AceLogTag::ACE_FORM, "LoadFormSkeleton ignored, single mode.");
        return false;
    }
    return true;
}

int32_t FormPattern::GetFormDimensionHeight(int32_t dimension)
{
    auto iter = OHOS::AppExecFwk::Constants::DIMENSION_MAP.
        find(static_cast<OHOS::AppExecFwk::Constants::Dimension>(dimension));
    if (iter == OHOS::AppExecFwk::Constants::DIMENSION_MAP.end()) {
        TAG_LOGE(AceLogTag::ACE_FORM, "GetFormDimensionHeight failed, invalid dimension: %{public}d",
            dimension);
        return 0;
    }

    std::string formDimensionStr = iter->second;
    std::stringstream streamDimension(formDimensionStr);
    std::string dimensionHeightStr;
    if (!std::getline(streamDimension, dimensionHeightStr, FORM_DIMENSION_SPLITTER)) {
        TAG_LOGE(AceLogTag::ACE_FORM, "GetFormDimensionHeight failed!");
        return 0;
    }
    return StringUtils::StringToInt(dimensionHeightStr);
}

RefPtr<FrameNode> FormPattern::CreateTimeLimitNode()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);

    std::string content;
    GetTimeLimitResource(content);
    TAG_LOGI(AceLogTag::ACE_FORM, "GetTimeLimitContent, content = %{public}s", content.c_str());

    RefPtr<FrameNode> textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textNode, nullptr);
    AddFormChildNode(FormChildNodeType::FORM_SPECIAL_STYLE_NODE, textNode);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, nullptr);

    auto width = static_cast<float>(cardInfo_.width.Value()) - cardInfo_.borderWidth * DOUBLE;
    auto height = static_cast<float>(cardInfo_.height.Value()) - cardInfo_.borderWidth * DOUBLE;
    CalcSize idealSize = { CalcLength(width), CalcLength(height) };
    MeasureProperty layoutConstraint;
    layoutConstraint.selfIdealSize = idealSize;
    layoutConstraint.maxSize = idealSize;
    textNode->UpdateLayoutConstraint(layoutConstraint);
    textLayoutProperty->UpdateContent(content);
    textLayoutProperty->UpdateFontWeight(FontWeight::BOLD);
    Dimension fontSize(GetTimeLimitFontSize());
    textLayoutProperty->UpdateFontSize(fontSize);
    textLayoutProperty->UpdateTextColor(SystemProperties::GetColorMode() == ColorMode::DARK ?
        Color(FONT_COLOR_DARK) : Color(FONT_COLOR_LIGHT));
    textLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
    auto externalContext = DynamicCast<NG::RosenRenderContext>(textNode->GetRenderContext());
    CHECK_NULL_RETURN(externalContext, nullptr);
    externalContext->SetVisible(true);
    externalContext->SetOpacity(TEXT_TRANSPARENT_VAL);
    host->AddChild(textNode);
    return textNode;
}

RefPtr<FrameNode> FormPattern::CreateAppLockNode()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    int32_t imageNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto imageNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, imageNodeId, AceType::MakeRefPtr<ImagePattern>());
    CHECK_NULL_RETURN(imageNode, nullptr);
    AddFormChildNode(FormChildNodeType::FORM_SPECIAL_STYLE_NODE, imageNode);
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(imageLayoutProperty, nullptr);
    auto info = ImageSourceInfo("");
    info.SetResourceId(InternalResource::ResourceId::APP_LOCK_SVG);
    info.SetFillColor(SystemProperties::GetColorMode() == ColorMode::DARK ? Color::BLACK:Color::WHITE);
    imageLayoutProperty->UpdateImageSourceInfo(info);
    CalcSize idealSize = { CalcLength(32, DimensionUnit::VP), CalcLength(32, DimensionUnit::VP) };
    imageLayoutProperty->UpdateUserDefinedIdealSize(idealSize);
    auto externalContext = DynamicCast<NG::RosenRenderContext>(imageNode->GetRenderContext());
    CHECK_NULL_RETURN(externalContext, nullptr);
    externalContext->SetVisible(true);
    externalContext->SetOpacity(TEXT_TRANSPARENT_VAL);
    host->AddChild(imageNode);
    return imageNode;
}

void FormPattern::CreateSkeletonView(
    const RefPtr<FrameNode>& parent, const std::shared_ptr<FormSkeletonParams>& params, int32_t dimensionHeight)
{
    float lineHeight = params->GetLineHeight();
    uint32_t fillColor = params->GetFillColor();
    float lineMarginLeft = params->GetLineMarginLeft();

    // 1. Set title line
    MarginProperty titleMargin;
    titleMargin.top = CalcLength(params->GetTitleMarginTop());
    titleMargin.left = CalcLength(lineMarginLeft);
    CalcSize titleIdealSize = { CalcLength(params->GetTitleLineWidth()), CalcLength(lineHeight) };
    auto titleLineNode = CreateRectNode(parent, titleIdealSize, titleMargin,
        fillColor, params->GetTitleOpacity());
    CHECK_NULL_VOID(titleLineNode);

    // 2. Set content lines
    for (int32_t i = 0; i < params->GetContentLineNum(); i++) {
        MarginProperty contentMargin;
        contentMargin.top = CalcLength(i == 0 ? params->GetTitleContentMargins() :
            params->GetContentMargins());
        contentMargin.left = CalcLength(lineMarginLeft);
        CalcSize contentIdealSize = { CalcLength(params->GetLineWidth()), CalcLength(lineHeight) };
        auto contentLineNode = CreateRectNode(parent, contentIdealSize, contentMargin,
            fillColor, params->GetContentOpacity());
        CHECK_NULL_VOID(contentLineNode);
    }
    
    // 3. Set ending line if form dimension height greater than 1
    if (dimensionHeight > 1) {
        MarginProperty endingMargin;
        endingMargin.top = CalcLength(params->GetEndingLineMarginTop());
        endingMargin.left = CalcLength(lineMarginLeft);
        CalcSize endingIdealSize = { CalcLength(params->GetEndingLineWidth()), CalcLength(lineHeight) };
        auto endingLineNode = CreateRectNode(parent, endingIdealSize, endingMargin,
            fillColor, params->GetContentOpacity());
        CHECK_NULL_VOID(endingLineNode);
    }
}

RefPtr<FrameNode> FormPattern::CreateColumnNode(FormChildNodeType formChildNodeType)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    RefPtr<FrameNode> columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    CHECK_NULL_RETURN(columnNode, nullptr);
    AddFormChildNode(formChildNodeType, columnNode);
    auto width = static_cast<float>(cardInfo_.width.Value());
    auto height = static_cast<float>(cardInfo_.height.Value());
    CalcSize idealSize = { CalcLength(width), CalcLength(height) };
    MeasureProperty layoutConstraint;
    layoutConstraint.selfIdealSize = idealSize;
    layoutConstraint.maxSize = idealSize;
    columnNode->UpdateLayoutConstraint(layoutConstraint);

    auto layoutProperty = columnNode->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    layoutProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_START);

    host->AddChild(columnNode);
    return columnNode;
}

RefPtr<FrameNode> FormPattern::CreateRectNode(const RefPtr<FrameNode>& parent, const CalcSize& idealSize,
    const MarginProperty& margin, uint32_t fillColor, double opacity)
{
    auto rectNode = FrameNode::CreateFrameNode(V2::RECT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<RectPattern>());
    MeasureProperty layoutConstraint;
    layoutConstraint.selfIdealSize = idealSize;
    layoutConstraint.maxSize = idealSize;
    rectNode->UpdateLayoutConstraint(layoutConstraint);

    rectNode->GetLayoutProperty()->UpdateMargin(margin);

    auto paintProperty = rectNode->GetPaintProperty<RectPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, nullptr);
    paintProperty->UpdateFill(Color(fillColor));
    paintProperty->UpdateFillOpacity(opacity);

    paintProperty->UpdateTopLeftRadius(NG::Radius(RECT_RADIUS));
    paintProperty->UpdateTopRightRadius(NG::Radius(RECT_RADIUS));
    paintProperty->UpdateBottomLeftRadius(NG::Radius(RECT_RADIUS));
    paintProperty->UpdateBottomRightRadius(NG::Radius(RECT_RADIUS));

    rectNode->MountToParent(parent);
    rectNode->MarkDirtyNode();

    return rectNode;
}

void FormPattern::InitFormManagerDelegate()
{
    if (formManagerBridge_) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    formManagerBridge_ = AceType::MakeRefPtr<FormManagerDelegate>(context);
    formManagerBridge_->AddRenderDelegate();
    formManagerBridge_->RegisterRenderDelegateEvent();
    auto formUtils = FormManager::GetInstance().GetFormUtils();
    if (formUtils) {
        formManagerBridge_->SetFormUtils(formUtils);
    }
    int32_t instanceID = context->GetInstanceId();
    accessibilitySessionAdapter_ = AceType::MakeRefPtr<AccessibilitySessionAdapterForm>(formManagerBridge_);
    formManagerBridge_->AddFormAcquireCallback([weak = WeakClaim(this), instanceID, pipeline](int64_t id,
                                                   const std::string& path,
                                                   const std::string& module, const std::string& data,
                                                   const std::map<std::string, sptr<AppExecFwk::FormAshmem>>&
                                                       imageDataMap,
                                                   const AppExecFwk::FormJsInfo& formJsInfo,
                                                   const FrontendType& frontendType, const FrontendType& uiSyntax) {
        ContainerScope scope(instanceID);
        CHECK_NULL_VOID(pipeline);
        auto uiTaskExecutor =
            SingleTaskExecutor::Make(pipeline->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        uiTaskExecutor.PostTask([id, path, module, data, imageDataMap, formJsInfo, weak, instanceID, frontendType,
                                    uiSyntax] {
            ContainerScope scope(instanceID);
            auto form = weak.Upgrade();
            CHECK_NULL_VOID(form);
            auto container = form->GetSubContainer();
            CHECK_NULL_VOID(container);
            container->SetWindowConfig({ formJsInfo.formWindow.designWidth, formJsInfo.formWindow.autoDesignWidth });
            container->RunCard(id, path, module, data, imageDataMap, formJsInfo.formSrc, frontendType, uiSyntax);
            }, "ArkUIFormRunCard");
    });

    InitAddFormUpdateAndErrorCallback(instanceID);
    InitAddUninstallAndSurfaceNodeCallback(instanceID);
    InitAddFormSurfaceChangeAndDetachCallback(instanceID);
    InitAddUnTrustAndSnapshotCallback(instanceID);
    InitOtherCallback(instanceID);
    const std::function<void(bool isRotate, const std::shared_ptr<Rosen::RSTransaction>& rsTransaction)>& callback =
        [this](bool isRotate, const std::shared_ptr<Rosen::RSTransaction>& rsTransaction) {
            FormManager::GetInstance().NotifyIsSizeChangeByRotate(isRotate, rsTransaction);
        };
    context->SetSizeChangeByRotateCallback(callback);
}

void FormPattern::GetRectRelativeToWindow(AccessibilityParentRectInfo& parentRectInfo)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto rect = host->GetTransformRectRelativeToWindow();
    VectorF finalScale = host->GetTransformScaleRelativeToWindow();
    parentRectInfo.top = static_cast<int32_t>(rect.Top());
    parentRectInfo.left = static_cast<int32_t>(rect.Left());
    parentRectInfo.scaleX = finalScale.x;
    parentRectInfo.scaleY = finalScale.y;

    auto pipeline = host->GetContext();
    if (pipeline) {
        auto windowRect = pipeline->GetDisplayWindowRectInfo();
        parentRectInfo.top += static_cast<int32_t>(windowRect.Top());
        parentRectInfo.left += static_cast<int32_t>(windowRect.Left());
    }

    TAG_LOGD(AceLogTag::ACE_ACCESSIBILITY, "elementId: %{public}" PRId64 ", top: %{public}d, left: %{public}d",
        host->GetAccessibilityId(), parentRectInfo.top, parentRectInfo.left);
}

void FormPattern::ProcDeleteImageNode(const AAFwk::Want& want)
{
    if (want.GetBoolParam(OHOS::AppExecFwk::Constants::FORM_IS_RECOVER_FORM, false)) {
        DelayDeleteImageNode(want.GetBoolParam(
            OHOS::AppExecFwk::Constants::FORM_IS_RECOVER_FORM_TO_HANDLE_CLICK_EVENT, false));
    } else {
        RemoveFormChildNode(FormChildNodeType::FORM_STATIC_IMAGE_NODE);
    }
}

void FormPattern::AttachRSNode(const std::shared_ptr<Rosen::RSSurfaceNode>& node, const AAFwk::Want& want)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto externalRenderContext = DynamicCast<NG::RosenRenderContext>(GetExternalRenderContext());
    CHECK_NULL_VOID(externalRenderContext);
    externalRenderContext->SetRSNode(node);
    float boundWidth = cardInfo_.width.Value() - cardInfo_.borderWidth * DOUBLE;
    float boundHeight = cardInfo_.height.Value() - cardInfo_.borderWidth * DOUBLE;
    if (isBeenLayout_) {
        auto geometryNode = host->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        auto size = geometryNode->GetFrameSize();
        boundWidth = size.Width() - cardInfo_.borderWidth * DOUBLE;
        boundHeight = size.Height() - cardInfo_.borderWidth * DOUBLE;
    }
    TAG_LOGI(AceLogTag::ACE_FORM,
        "attach rs node, id: %{public}" PRId64 "  width: %{public}f  height: %{public}f  borderWidth: %{public}f",
        cardInfo_.id, boundWidth, boundHeight, cardInfo_.borderWidth);
    externalRenderContext->SetBounds(round(cardInfo_.borderWidth), round(cardInfo_.borderWidth),
        round(boundWidth), round(boundHeight));

    bool isRecover = want.GetBoolParam(OHOS::AppExecFwk::Constants::FORM_IS_RECOVER_FORM, false);
    if (isRecover || (isSkeletonAnimEnable_ && !isTransparencyEnable_) ||
        formChildrenNodeMap_.find(FormChildNodeType::FORM_FORBIDDEN_ROOT_NODE) != formChildrenNodeMap_.end()) {
        TAG_LOGI(AceLogTag::ACE_FORM, "surfaceNode: %{public}s setOpacity:0,%{public}d,"
                                  "%{public}d,%{public}d",
            std::to_string(node->GetId()).c_str(),
            isRecover,
            isSkeletonAnimEnable_,
            isTransparencyEnable_);
        externalRenderContext->SetOpacity(TRANSPARENT_VAL);
    } else {
        TAG_LOGI(AceLogTag::ACE_FORM, "surfaceNode: %{public}s setOpacity:1,%{public}d,"
                                  "%{public}d,%{public}d",
            std::to_string(node->GetId()).c_str(),
            isRecover,
            isSkeletonAnimEnable_,
            isTransparencyEnable_);
        externalRenderContext->SetOpacity(NON_TRANSPARENT_VAL);
    }

    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->AddChild(externalRenderContext, 0);
}

void FormPattern::FireFormSurfaceNodeCallback(
    const std::shared_ptr<Rosen::RSSurfaceNode>& node, const AAFwk::Want& want)
{
    ACE_FUNCTION_TRACE();
    CHECK_NULL_VOID(node);
    bool isEnableSkeleton = isSkeletonAnimEnable_;
    TAG_LOGI(AceLogTag::ACE_FORM, "FireFormSurfaceNodeCallback %{public}d, %{public}d",
        isTransparencyEnable_, isEnableSkeleton);
    node->CreateNodeInRenderThread();

    // do anim only when skeleton enable and transparency
    AttachRSNode(node, want);
    if (!isEnableSkeleton) {
        RemoveFormChildNode(FormChildNodeType::FORM_SKELETON_NODE);
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    isDynamic_ = want.GetBoolParam(OHOS::AppExecFwk::Constants::FORM_IS_DYNAMIC, false);
    UpdateFormBaseConfig(isDynamic_);

    ProcDeleteImageNode(want);

    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    auto parent = host->GetParent();
    CHECK_NULL_VOID(parent);
    parent->MarkNeedSyncRenderTree();
    parent->RebuildRenderContextTree();
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->RequestNextFrame();
    OnLoadEvent();

    auto formNode = DynamicCast<FormNode>(host);
    CHECK_NULL_VOID(formNode);
    formNode->NotifyAccessibilityChildTreeRegister();

    if (isEnableSkeleton && !isTransparencyEnable_) {
        TAG_LOGI(AceLogTag::ACE_FORM, "FireFormSurfaceNodeCallback delay %{public}d,%{public}d",
            isTransparencyEnable_, isEnableSkeleton);
        auto context = host->GetContext();
        CHECK_NULL_VOID(context);
        if (!ShouldDoSkeletonAnimation()) {
            TAG_LOGE(AceLogTag::ACE_FORM, "not do skeleton animation");
            SetExternalRenderOpacity(NON_TRANSPARENT_VAL);
            return;
        }
        std::string nodeIdStr = std::to_string(host->GetId());
        auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        uiTaskExecutor.PostDelayedTask(
            [weak = WeakClaim(this)] {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                pattern->DoSkeletonAnimation();
            }, FORM_UNLOCK_ANIMATION_DELAY, "DoSkeletonAnimation_" + nodeIdStr);
    }
}

void FormPattern::DelayDeleteImageNode(bool needHandleCachedClick)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    std::string nodeIdStr = std::to_string(host->GetId());
    auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    uiTaskExecutor.PostDelayedTask(
        [weak = WeakClaim(this)] {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->SetNonTransparentAfterRecover();
        },
        DELAY_TIME_FOR_SET_NON_TRANSPARENT, "ArkUIFormSetNonTransparentAfterRecover_" + nodeIdStr);
    uiTaskExecutor.PostDelayedTask(
        [weak = WeakClaim(this), needHandleCachedClick] {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->DeleteImageNodeAfterRecover(needHandleCachedClick);
        },
        DELAY_TIME_FOR_DELETE_IMAGE_NODE, "ArkUIFormDeleteImageNodeAfterRecover_" + nodeIdStr);
}

void FormPattern::FireFormSurfaceChangeCallback(float width, float height, float borderWidth)
{
    auto externalRenderContext = DynamicCast<NG::RosenRenderContext>(GetExternalRenderContext());
    CHECK_NULL_VOID(externalRenderContext);
    TAG_LOGI(AceLogTag::ACE_FORM,
        "FireFormSurfaceChangeCallback, "
        "id: %{public}" PRId64 "  width: %{public}f  height: %{public}f  borderWidth: %{public}f",
        cardInfo_.id, width, height, borderWidth);
    externalRenderContext->SetBounds(round(borderWidth), round(borderWidth), round(width - borderWidth * DOUBLE),
        round(height - borderWidth * DOUBLE));
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    isUnTrust_ = false;
    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    auto parent = host->GetParent();
    CHECK_NULL_VOID(parent);
    parent->MarkNeedSyncRenderTree();
    parent->RebuildRenderContextTree();
    renderContext->RequestNextFrame();
}

void FormPattern::FireFormSurfaceDetachCallback()
{
    TAG_LOGI(AceLogTag::ACE_FORM, "FireFormSurfaceDetachCallback isFrsNodeDetached:%{public}d", isFrsNodeDetached_);
    isFrsNodeDetached_ = true;
}

void FormPattern::CreateCardContainer()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto layoutProperty = host->GetLayoutProperty<FormLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto hasContainer = false;
    RemoveSubContainer();
    if (cardInfo_.id != 0 && Container::IsCurrentUseNewPipeline()) {
        auto subContainer = FormManager::GetInstance().GetSubContainer(cardInfo_.id);
        if (subContainer && context->GetInstanceId() == subContainer->GetInstanceId() &&
            subContainer->GetCardType() == FrontendType::JS_CARD) {
            subContainer_ = subContainer;
            FormManager::GetInstance().RemoveSubContainer(cardInfo_.id);
            hasContainer = true;
        }
    }
    if (!subContainer_) {
        subContainer_ = AceType::MakeRefPtr<SubContainer>(context, context->GetInstanceId());
    }
    enhancesSubContainer(hasContainer);
}

void FormPattern::AttachJsRSNode(const std::shared_ptr<Rosen::RSNode> &jsNode)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto externalRenderContext = DynamicCast<NG::RosenRenderContext>(GetExternalRenderContext());
    CHECK_NULL_VOID(externalRenderContext);
    externalRenderContext->SetRSNode(jsNode);

    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->AddChild(externalRenderContext, 0);
}

std::unique_ptr<DrawDelegate> FormPattern::GetDrawDelegate()
{
    auto drawDelegate = std::make_unique<DrawDelegate>();
#ifdef ENABLE_ROSEN_BACKEND
    auto host = GetHost();
    drawDelegate->SetDrawRSFrameCallback(
        [weak = WeakClaim(this), host](std::shared_ptr<RSNode>& node, const Rect& /* dirty */) {
            CHECK_NULL_VOID(host);
            CHECK_NULL_VOID(node);
            auto form = weak.Upgrade();
            CHECK_NULL_VOID(form);
            auto context = DynamicCast<NG::RosenRenderContext>(host->GetRenderContext());
            CHECK_NULL_VOID(context);
            auto rsNode = context->GetRSNode();
            CHECK_NULL_VOID(rsNode);
            form->AttachJsRSNode(node);
            host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
        });

    drawDelegate->SetDrawRSFrameByRenderContextCallback(
        [weak = WeakClaim(this), host](RefPtr<OHOS::Ace::NG::RenderContext>& renderContext) {
            auto context = DynamicCast<NG::RosenRenderContext>(renderContext);
            CHECK_NULL_VOID(context);
            auto node = context->GetRSNode();
            CHECK_NULL_VOID(node);
            auto form = weak.Upgrade();
            CHECK_NULL_VOID(form);
            auto formContext = DynamicCast<NG::RosenRenderContext>(host->GetRenderContext());
            CHECK_NULL_VOID(formContext);
            auto rsNode = formContext->GetRSNode();
            CHECK_NULL_VOID(rsNode);
            form->AttachJsRSNode(node);
            host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
        });
#endif
    return drawDelegate;
}

void FormPattern::FireOnErrorEvent(const std::string& code, const std::string& msg) const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<FormEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto json = JsonUtil::Create(true);
    json->Put("errcode", code.c_str());
    json->Put("msg", msg.c_str());
    eventHub->FireOnError(json->ToString());
}

void FormPattern::FireOnUninstallEvent(int64_t id) const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<FormEventHub>();
    CHECK_NULL_VOID(eventHub);
    int64_t uninstallFormId = id < MAX_NUMBER_OF_JS ? id : -1;
    auto json = JsonUtil::Create(true);
    json->Put("id", std::to_string(uninstallFormId).c_str());
    json->Put("idString", std::to_string(id).c_str());
    eventHub->FireOnUninstall(json->ToString());
}

void FormPattern::FireOnAcquiredEvent(int64_t id) const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<FormEventHub>();
    CHECK_NULL_VOID(eventHub);
    int64_t onAcquireFormId = id < MAX_NUMBER_OF_JS ? id : -1;
    auto json = JsonUtil::Create(true);
    json->Put("id", std::to_string(onAcquireFormId).c_str());
    json->Put("idString", std::to_string(id).c_str());
    eventHub->FireOnAcquired(json->ToString());
}

void FormPattern::FireOnRouterEvent(const std::unique_ptr<JsonValue>& action)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<FormEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto json = JsonUtil::Create(true);
    json->Put("action", action);
    eventHub->FireOnRouter(json->ToString());
}

void FormPattern::FireOnLoadEvent() const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<FormEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireOnLoad("");
}

void FormPattern::OnLoadEvent()
{
    ACE_FUNCTION_TRACE();
    isSnapshot_ = false;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    uiTaskExecutor.PostTask([weak = WeakClaim(this)] {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->FireOnLoadEvent();
        }, "ArkUIFormFireLoadEvent");
}

void FormPattern::OnActionEvent(const std::string& action)
{
    TAG_LOGI(AceLogTag::ACE_FORM, "formPattern receive actionEvent");  
    if (!formManagerBridge_) {
        TAG_LOGE(AceLogTag::ACE_FORM, "OnActionEvent failed, form manager deleget is null!");
        return;
    }
    auto eventAction = JsonUtil::ParseJsonString(action);
    if (!eventAction->IsValid()) {
        return;
    }

    auto actionType = eventAction->GetValue("action");
    if (!actionType->IsValid()) {
        return;
    }

    auto type = actionType->GetString();
    if (type != "router" && type != "message" && type != "call") {
        return;
    }

    RemoveDelayResetManuallyClickFlagTask();
    auto subContainer = GetSubContainer();
    CHECK_NULL_VOID(subContainer);
    if (!isManuallyClick_ && subContainer->GetUISyntaxType() == FrontendType::ETS_CARD) {
        EventReport::ReportNonManualPostCardActionInfo(cardInfo_.cardName, cardInfo_.bundleName, cardInfo_.abilityName,
            cardInfo_.moduleName, cardInfo_.dimension);
        if ("router" == type && !AceApplicationInfo::GetInstance().IsAccessibilityEnabled()) {
            TAG_LOGI(AceLogTag::ACE_FORM, "postcardaction is not manually click.");
            return;
        }
    }

    isManuallyClick_ = false;
    if ("router" == type) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto context = host->GetContext();
        CHECK_NULL_VOID(context);
        auto uiTaskExecutor =
            SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        if (uiTaskExecutor.IsRunOnCurrentThread()) {
            FireOnRouterEvent(eventAction);
        } else {
            uiTaskExecutor.PostTask([weak = WeakClaim(this), action] {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                auto eventAction = JsonUtil::ParseJsonString(action);
                TAG_LOGI(AceLogTag::ACE_FORM, "UI task execute begin.");
                pattern->FireOnRouterEvent(eventAction);
                }, "ArkUIFormFireRouterEvent");
        }
    }

    formManagerBridge_->OnActionEvent(action);
}

bool FormPattern::ISAllowUpdate() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, true);
    auto property = host->GetLayoutProperty<FormLayoutProperty>();
    CHECK_NULL_RETURN(property, true);
    auto formInfo = property->GetRequestFormInfo();
    CHECK_NULL_RETURN(property, true);
    return formInfo->allowUpdate;
}

const RefPtr<SubContainer>& FormPattern::GetSubContainer() const
{
    return subContainer_;
}

void FormPattern::DispatchPointerEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent,
    SerializedGesture& serializedGesture)
{
    CHECK_NULL_VOID(pointerEvent);
    CHECK_NULL_VOID(formManagerBridge_);

    if (OHOS::MMI::PointerEvent::POINTER_ACTION_DOWN == pointerEvent->GetPointerAction()) {
        isManuallyClick_ = true;
        DelayResetManuallyClickFlag();
    }
    if (!isVisible_) {
        auto pointerAction = pointerEvent->GetPointerAction();
        if (pointerAction == OHOS::MMI::PointerEvent::POINTER_ACTION_UP ||
            pointerAction == OHOS::MMI::PointerEvent::POINTER_ACTION_PULL_UP ||
            pointerAction == OHOS::MMI::PointerEvent::POINTER_ACTION_PULL_OUT_WINDOW ||
            pointerAction == OHOS::MMI::PointerEvent::POINTER_ACTION_CANCEL) {
            // still dispatch 'up' or 'cancel' event to finish this pointer event
            formManagerBridge_->DispatchPointerEvent(pointerEvent, serializedGesture);
        } else {
            TAG_LOGD(AceLogTag::ACE_FORM, "form invisible, not dispatch pointerEvent: %{public}d.", pointerAction);
        }
        return;
    }
    formManagerBridge_->DispatchPointerEvent(pointerEvent, serializedGesture);
}

void FormPattern::RemoveSubContainer()
{
    auto host = GetHost();
    auto eventHub = host->GetEventHub<FormEventHub>();
    if (eventHub) {
        eventHub->FireOnCache();
    }
    subContainer_.Reset();
}

void FormPattern::EnableDrag()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto dragStart = [weak = WeakClaim(this)](const RefPtr<OHOS::Ace::DragEvent>& event,
                         const std::string& /* extraParams */) -> DragDropInfo {
        DragDropInfo info;

        auto form = weak.Upgrade();
        CHECK_NULL_RETURN(form, info);
        auto subcontainer = form->GetSubContainer();
        CHECK_NULL_RETURN(subcontainer, info);

        RefPtr<UnifiedData> unifiedData = UdmfClient::GetInstance()->CreateUnifiedData();
        UdmfClient::GetInstance()->AddFormRecord(unifiedData, subcontainer->GetRunningCardId(), form->cardInfo_);
        event->SetData(unifiedData);

        info.extraInfo = "card drag";
        return info;
    };
    auto eventHub = GetHost()->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetDefaultOnDragStart(std::move(dragStart));
}

void FormPattern::UpdateConfiguration()
{
    auto localeTag = AceApplicationInfo::GetInstance().GetLocaleTag();
    if (localeTag != localeTag_ && subContainer_) {
        localeTag_ = localeTag;
        subContainer_->UpdateConfiguration();
    }
}

void FormPattern::OnLanguageConfigurationUpdate()
{
    if (formSpecialStyle_.GetFormStyleAttribution() != FormStyleAttribution::PARENT_CONTROL) {
        TAG_LOGI(AceLogTag::ACE_FORM, "OnLanguageConfigurationUpdate, not need to update!");
        return;
    }
    RefPtr<FrameNode> textNode = GetFormChildNode(FormChildNodeType::FORM_SPECIAL_STYLE_NODE);
    CHECK_NULL_VOID(textNode);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    std::string content;
    GetTimeLimitResource(content);
    textLayoutProperty->UpdateContent(content);

    Dimension fontSize(GetTimeLimitFontSize());
    if (!textLayoutProperty->GetFontSize().has_value() ||
        !NearEqual(textLayoutProperty->GetFontSize().value(), fontSize)) {
        textLayoutProperty->UpdateFontSize(fontSize);
    }
}

void FormPattern::GetTimeLimitResource(std::string &content)
{
    std::shared_ptr<Global::Resource::ResourceManager> sysResMgr(Global::Resource::CreateResourceManager());
    if (sysResMgr == nullptr) {
        TAG_LOGE(AceLogTag::ACE_FORM, "init sysMgr failed!");
        return;
    }
    std::unique_ptr<Global::Resource::ResConfig> resConfig(Global::Resource::CreateResConfig());
    if (resConfig == nullptr) {
        TAG_LOGE(AceLogTag::ACE_FORM, "init resConfig failed!");
        return;
    }

    sysResMgr->GetResConfig(*resConfig);
    UErrorCode status = U_ZERO_ERROR;
    std::string language = Global::I18n::LocaleConfig::GetSystemLanguage();
    icu::Locale locale = icu::Locale::forLanguageTag(language, status);
    if (status != U_ZERO_ERROR) {
        TAG_LOGE(AceLogTag::ACE_FORM, "forLanguageTag failed, errCode:%{public}d", status);
        return;
    }

    resConfig->SetLocaleInfo(locale.getLanguage(), locale.getScript(), locale.getCountry());
    Global::Resource::RState state = sysResMgr->UpdateResConfig(*resConfig);
    if (state != Global::Resource::RState::SUCCESS) {
        TAG_LOGE(AceLogTag::ACE_FORM, "UpdateResConfig failed! errcode:%{public}d.", state);
        return;
    }
    sysResMgr->GetStringByName(TIME_LIMIT_RESOURCE_NAME, content);
    isTibetanLanguage_ = language == "bo"? true : false;
}

void FormPattern::AddFormChildNode(FormChildNodeType formChildNodeType, const RefPtr<FrameNode> child)
{
    auto iter = formChildrenNodeMap_.find(formChildNodeType);
    if (iter == formChildrenNodeMap_.end()) {
        formChildrenNodeMap_.insert(std::make_pair(formChildNodeType, child));
    } else {
        formChildrenNodeMap_[formChildNodeType] = child;
    }
}

void FormPattern::RemoveFormChildNode(FormChildNodeType formChildNodeType)
{
    RefPtr<FrameNode> childNode = GetFormChildNode(formChildNodeType);
    CHECK_NULL_VOID(childNode);

    ContainerScope scope(scopeId_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    if (renderContext == nullptr) {
        TAG_LOGE(AceLogTag::ACE_FORM, "Remove child node: %{public}d failed, null context.",
            formChildNodeType);
        return;
    }
    renderContext->RemoveChild(childNode->GetRenderContext());
    host->RemoveChild(childNode);
    TAG_LOGI(AceLogTag::ACE_FORM, "Remove child node: %{public}d sucessfully.",
        formChildNodeType);
    formChildrenNodeMap_.erase(formChildNodeType);
    host->MarkModifyDone();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

RefPtr<FrameNode> FormPattern::GetFormChildNode(FormChildNodeType formChildNodeType) const
{
    auto iter = formChildrenNodeMap_.find(formChildNodeType);
    if (iter == formChildrenNodeMap_.end()) {
        return nullptr;
    }

    return iter->second;
}

double FormPattern::GetTimeLimitFontSize()
{
    float fontScale = SystemProperties::GetFontScale();
    if (fontScale > MAX_FONT_SCALE) {
        fontScale = MAX_FONT_SCALE;
    }
    double density = PipelineBase::GetCurrentDensity();
    TAG_LOGD(AceLogTag::ACE_FORM, "Density is %{public}f, font scale is %{public}f.",
        density, fontScale);
   
    int32_t dimensionHeight = GetFormDimensionHeight(cardInfo_.dimension);
    if (dimensionHeight == FORM_DIMENSION_MIN_HEIGHT) {
        if (isTibetanLanguage_) {
            return TIBETAN_TIME_LIMIT_FONT_SIZE_BASE * density * fontScale;
        }
        return ONE_DIMENSION_TIME_LIMIT_FONT_SIZE_BASE * density * fontScale;
    } else {
        return TIME_LIMIT_FONT_SIZE_BASE * density * fontScale;
    }
}

bool FormPattern::IsMaskEnableForm(const RequestFormInfo& info)
{
    return info.shape == FORM_SHAPE_CIRCLE || info.renderingMode ==
        static_cast<int32_t>(OHOS::AppExecFwk::Constants::RenderingMode::SINGLE_COLOR) ||
        info.dimension == static_cast<int32_t>(OHOS::AppExecFwk::Constants::Dimension::DIMENSION_1_1);
}

void FormPattern::UpdateChildNodeOpacity(FormChildNodeType formChildNodeType, double opacity)
{
    TAG_LOGI(AceLogTag::ACE_FORM, "formChildNodeType: %{public}d, opacity: %{public}f.",
        static_cast<int32_t>(formChildNodeType), opacity);
    if (formChildNodeType == FormChildNodeType::FORM_SURFACE_NODE) {
        auto externalRenderContext = DynamicCast<NG::RosenRenderContext>(GetExternalRenderContext());
        CHECK_NULL_VOID(externalRenderContext);
        externalRenderContext->OnOpacityUpdate(opacity);
    } else if (formChildNodeType == FormChildNodeType::FORM_STATIC_IMAGE_NODE ||
        formChildNodeType == FormChildNodeType::FORM_SKELETON_NODE) {
        auto childNode = GetFormChildNode(formChildNodeType);
        CHECK_NULL_VOID(childNode);
        auto renderContext = DynamicCast<NG::RosenRenderContext>(childNode->GetRenderContext());
        CHECK_NULL_VOID(renderContext);
        renderContext->OnOpacityUpdate(opacity);
    }
}

void FormPattern::UnregisterAccessibility()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto formNode = DynamicCast<FormNode>(host);
    CHECK_NULL_VOID(formNode);
    formNode->ClearAccessibilityChildTreeRegisterFlag();
}

bool FormPattern::CheckFormBundleForbidden(const std::string &bundleName)
{
    CHECK_NULL_RETURN(formManagerBridge_, false);
    return formManagerBridge_->CheckFormBundleForbidden(bundleName);
}

void FormPattern::DelayResetManuallyClickFlag()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto executor = context->GetTaskExecutor();
    CHECK_NULL_VOID(executor);
    std::string nodeIdStr = std::to_string(host->GetId());
    executor->PostDelayedTask(
        [weak = WeakClaim(this)] {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->isManuallyClick_ = false;
        },
        TaskExecutor::TaskType::UI, DELAY_TIME_FOR_RESET_MANUALLY_CLICK_FLAG,
        std::string("ArkUIFormResetManuallyClickFlag").append(nodeIdStr));
}

void FormPattern::RemoveDelayResetManuallyClickFlagTask()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto executor = context->GetTaskExecutor();
    CHECK_NULL_VOID(executor);
    std::string nodeIdStr = std::to_string(host->GetId());
    executor->RemoveTask(TaskExecutor::TaskType::UI, std::string("ArkUIFormResetManuallyClickFlag").append(nodeIdStr));
}

void FormPattern::SetTransparencyConfig(bool isTransparencyForm, const RequestFormInfo& info)
{
    if (!isTransparencyForm) {
        isTransparencyEnable_ = false;
        return;
    }
    auto wantWrap = info.wantWrap;
    if (wantWrap) {
        auto color = wantWrap->GetWant().GetStringParam(OHOS::AppExecFwk::Constants::PARAM_FORM_TRANSPARENCY_KEY);
        Color bgColor;
        if (Color::ParseColorString(color, bgColor) && bgColor == Color::TRANSPARENT) {
            TAG_LOGD(AceLogTag::ACE_FORM, "Parse color, bg color: %{public}s.", color.c_str());
            isTransparencyEnable_ = true;
        }
    }
}

void FormPattern::SetSkeletonEnableConfig(const RequestFormInfo &info)
{
    auto wantWrap = info.wantWrap;
    if (wantWrap) {
        isSkeletonAnimEnable_ = wantWrap->GetWant().GetBoolParam(
            OHOS::AppExecFwk::Constants::FORM_ENABLE_SKELETON_KEY, false);
        TAG_LOGI(AceLogTag::ACE_FORM, "FORM_ENABLE_SKELETON_KEY: %{public}d.", isSkeletonAnimEnable_);
    }
}

void FormPattern::SetExternalRenderOpacity(double opacity)
{
    auto externalRenderContext = DynamicCast<NG::RosenRenderContext>(GetExternalRenderContext());
    CHECK_NULL_VOID(externalRenderContext);
    externalRenderContext->SetOpacity(opacity);
}

bool FormPattern::ShouldDoSkeletonAnimation()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    std::list<RefPtr<UINode>> children = host->GetChildren();
    if (children.size() <= 0) {
        TAG_LOGE(AceLogTag::ACE_FORM, "Cur form component's children is empty.");
        return false;
    }

    auto skeletonNode = GetFormChildNode(FormChildNodeType::FORM_SKELETON_NODE);
    if (skeletonNode == nullptr) {
         TAG_LOGE(AceLogTag::ACE_FORM, "Cur form component's has no skeleton.");
        return false;
    }
    std::string lastChildTag = skeletonNode->GetTag();
    if (lastChildTag != V2::COLUMN_ETS_TAG) {
        TAG_LOGE(AceLogTag::ACE_FORM, "Cur form component's last child is not skeleton.");
        return false;
    }
    return true;
}

void FormPattern::DoSkeletonAnimation()
{
    ACE_FUNCTION_TRACE();
    TAG_LOGD(AceLogTag::ACE_FORM, "DoSkeletonAnimation");
    ContainerScope scope(scopeId_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto skeletonNode = GetFormChildNode(FormChildNodeType::FORM_SKELETON_NODE);
    if (!ShouldDoSkeletonAnimation()) {
        TAG_LOGE(AceLogTag::ACE_FORM, "should not do skeleton anim");
        SetExternalRenderOpacity(NON_TRANSPARENT_VAL);
        return;
    }
    
    std::function<void()> finishCallback = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->RemoveFormChildNode(FormChildNodeType::FORM_SKELETON_NODE);
        TAG_LOGD(AceLogTag::ACE_FORM, "DoSkeletonAnimation finishCallBack");
    };

    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    AnimationOption option = AnimationOption();
    option.SetDuration(FORM_UNLOCK_ANIMATION_DUATION);
    option.SetCurve(Curves::FRICTION);
    AnimationOption optionAlpha = AnimationOption();
    optionAlpha.SetCurve(Curves::SHARP);

    context->OpenImplicitAnimation(option, option.GetCurve(), finishCallback);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    context->FlushUITasks();

    optionAlpha.SetDuration(FORM_UNLOCK_ANIMATION_DUATION);
    auto externalRenderContext = DynamicCast<NG::RosenRenderContext>(GetExternalRenderContext());
    CHECK_NULL_VOID(externalRenderContext);
    externalRenderContext->OpacityAnimation(optionAlpha, 0, 1);

    auto lastFrameChild = AceType::DynamicCast<FrameNode>(skeletonNode);
    CHECK_NULL_VOID(lastFrameChild);
    RefPtr<OHOS::Ace::NG::RenderContext> childRenderContext = lastFrameChild->GetRenderContext();
    CHECK_NULL_VOID(childRenderContext);
    childRenderContext->OpacityAnimation(optionAlpha, 1, 0);
    context->CloseImplicitAnimation();
}

void FormPattern::UpdateFormBaseConfig(bool isDynamic)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<FormLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto visible = layoutProperty->GetVisibleType().value_or(VisibleType::VISIBLE);
    TAG_LOGI(AceLogTag::ACE_FORM, "VisibleType: %{public}d", static_cast<int32_t>(visible));
    layoutProperty->UpdateVisibility(visible);
    isLoaded_ = true;
    isUnTrust_ = false;
    isFrsNodeDetached_ = false;
    isDynamic_ = isDynamic;
}

void FormPattern::InitAddFormUpdateAndErrorCallback(int32_t instanceID)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();

    formManagerBridge_->AddFormUpdateCallback(
        [weak = WeakClaim(this), instanceID, pipeline](int64_t id, const std::string& data,
            const std::map<std::string, sptr<AppExecFwk::FormAshmem>>& imageDataMap) {
            ContainerScope scope(instanceID);
            CHECK_NULL_VOID(pipeline);
            auto uiTaskExecutor = SingleTaskExecutor::Make(pipeline->GetTaskExecutor(), TaskExecutor::TaskType::UI);
            uiTaskExecutor.PostTask(
                [id, data, imageDataMap, weak, instanceID] {
                    ContainerScope scope(instanceID);
                    auto form = weak.Upgrade();
                    CHECK_NULL_VOID(form);
                    if (form->ISAllowUpdate()) {
                        form->GetSubContainer()->UpdateCard(data, imageDataMap);
                    }
                },
                "ArkUIFormUpdateCard");
        });

    formManagerBridge_->AddFormErrorCallback(
        [weak = WeakClaim(this), instanceID, pipeline](const std::string& code, const std::string& msg) {
            ContainerScope scope(instanceID);
            CHECK_NULL_VOID(pipeline);
            auto uiTaskExecutor = SingleTaskExecutor::Make(pipeline->GetTaskExecutor(), TaskExecutor::TaskType::UI);
            uiTaskExecutor.PostTask(
                [code, msg, weak, instanceID] {
                    ContainerScope scope(instanceID);
                    auto form = weak.Upgrade();
                    CHECK_NULL_VOID(form);
                    form->FireOnErrorEvent(code, msg);
                },
                "ArkUIFormFireErrorEvent");
        });
}


void FormPattern::InitAddUninstallAndSurfaceNodeCallback(int32_t instanceID)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    formManagerBridge_->AddFormUninstallCallback([weak = WeakClaim(this), instanceID, pipeline](int64_t formId) {
        ContainerScope scope(instanceID);
        CHECK_NULL_VOID(pipeline);
        auto uiTaskExecutor = SingleTaskExecutor::Make(pipeline->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        uiTaskExecutor.PostTask(
            [formId, weak, instanceID] {
                ContainerScope scope(instanceID);
                auto form = weak.Upgrade();
                CHECK_NULL_VOID(form);
                form->FireOnUninstallEvent(formId);
            },
            "ArkUIFormFireUninstallEvent");
    });

    formManagerBridge_->AddFormSurfaceNodeCallback(
        [weak = WeakClaim(this), instanceID](
            const std::shared_ptr<Rosen::RSSurfaceNode>& node, const AAFwk::Want& want) {
            ContainerScope scope(instanceID);
            auto pipeline = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            auto executor = pipeline->GetTaskExecutor();
            CHECK_NULL_VOID(executor);
            auto uiTaskExecutor = SingleTaskExecutor::Make(executor, TaskExecutor::TaskType::UI);
            uiTaskExecutor.PostTask(
                [weak, instanceID, node, want] {
                    ContainerScope scope(instanceID);
                    auto form = weak.Upgrade();
                    CHECK_NULL_VOID(form);
                    form->FireFormSurfaceNodeCallback(node, want);
                },
                "ArkUIFormFireSurfaceNodeCallback");
        });
}

void FormPattern::InitAddFormSurfaceChangeAndDetachCallback(int32_t instanceID)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();

    formManagerBridge_->AddFormSurfaceChangeCallback(
        [weak = WeakClaim(this), instanceID, pipeline](float width, float height, float borderWidth) {
            ContainerScope scope(instanceID);
            CHECK_NULL_VOID(pipeline);
            auto uiTaskExecutor = SingleTaskExecutor::Make(pipeline->GetTaskExecutor(), TaskExecutor::TaskType::UI);
            uiTaskExecutor.PostTask(
                [weak, instanceID, width, height, borderWidth] {
                    ContainerScope scope(instanceID);
                    auto form = weak.Upgrade();
                    CHECK_NULL_VOID(form);
                    form->FireFormSurfaceChangeCallback(width, height, borderWidth);
                },
                "ArkUIFormFireSurfaceChange");
        });

    formManagerBridge_->AddFormSurfaceDetachCallback([weak = WeakClaim(this), instanceID]() {
        ContainerScope scope(instanceID);
        auto formPattern = weak.Upgrade();
        CHECK_NULL_VOID(formPattern);
        formPattern->FireFormSurfaceDetachCallback();
    });

    formManagerBridge_->AddActionEventHandle([weak = WeakClaim(this), instanceID](const std::string& action) {
        ContainerScope scope(instanceID);
        TAG_LOGI(AceLogTag::ACE_FORM, "Card receive action event, action: %{public}zu", action.length());
        auto formPattern = weak.Upgrade();
        CHECK_NULL_VOID(formPattern);
        formPattern->OnActionEvent(action);
    });
}

void FormPattern::InitAddUnTrustAndSnapshotCallback(int32_t instanceID)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    formManagerBridge_->AddUnTrustFormCallback([weak = WeakClaim(this), instanceID, pipeline]() {
        ContainerScope scope(instanceID);
        CHECK_NULL_VOID(pipeline);
        auto uiTaskExecutor = SingleTaskExecutor::Make(pipeline->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        uiTaskExecutor.PostTask(
            [weak, instanceID] {
                ContainerScope scope(instanceID);
                auto formPattern = weak.Upgrade();
                CHECK_NULL_VOID(formPattern);
                formPattern->HandleUnTrustForm();
            },
            "ArkUIFormHandleUnTrust");
    });

    formManagerBridge_->AddSnapshotCallback([weak = WeakClaim(this), instanceID](const uint32_t& delayTime) {
        ContainerScope scope(instanceID);
        auto formPattern = weak.Upgrade();
        CHECK_NULL_VOID(formPattern);
        auto host = formPattern->GetHost();
        CHECK_NULL_VOID(host);
        std::string nodeIdStr = std::to_string(host->GetId());
        formPattern->HandleSnapshot(delayTime, nodeIdStr);
    });

    formManagerBridge_->AddFormLinkInfoUpdateCallback(
        [weak = WeakClaim(this), instanceID](const std::vector<std::string>& infos) {
            ContainerScope scope(instanceID);
            auto formPattern = weak.Upgrade();
            CHECK_NULL_VOID(formPattern);
            formPattern->SetFormLinkInfos(infos);
        });
}


void FormPattern::InitOtherCallback(int32_t instanceID)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    formManagerBridge_->AddGetRectRelativeToWindowCallback(
        [weak = WeakClaim(this), instanceID](AccessibilityParentRectInfo& parentRectInfo) {
            ContainerScope scope(instanceID);
            auto context = PipelineContext::GetCurrentContextSafely();
            CHECK_NULL_VOID(context);
            auto uiTaskExecutor =
                SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
            uiTaskExecutor.PostSyncTask([weak, instanceID, &parentRectInfo] {
                ContainerScope scope(instanceID);
                auto form = weak.Upgrade();
                CHECK_NULL_VOID(form);
                form->GetRectRelativeToWindow(parentRectInfo);
                }, "ArkUIFormGetRectRelativeToWindow");
        });

    formManagerBridge_->AddEnableFormCallback([weak = WeakClaim(this), instanceID, pipeline](const bool enable) {
        ContainerScope scope(instanceID);
        CHECK_NULL_VOID(pipeline);
        auto uiTaskExecutor =
            SingleTaskExecutor::Make(pipeline->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        uiTaskExecutor.PostTask([weak, instanceID, enable] {
            ContainerScope scope(instanceID);
            auto formPattern = weak.Upgrade();
            CHECK_NULL_VOID(formPattern);
            formPattern->HandleEnableForm(enable);
            }, "ArkUIFormHandleEnableForm");
        });

    formManagerBridge_->AddLockFormCallback([weak = WeakClaim(this), instanceID, pipeline](const bool lock) {
        ContainerScope scope(instanceID);
        CHECK_NULL_VOID(pipeline);
        auto uiTaskExecutor =
            SingleTaskExecutor::Make(pipeline->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        uiTaskExecutor.PostTask([weak, instanceID, lock] {
            ContainerScope scope(instanceID);
            auto formPattern = weak.Upgrade();
            CHECK_NULL_VOID(formPattern);
            formPattern->HandleLockEvent(lock);
            }, "ArkUIFormHandleLockForm");
        });
}

void FormPattern::enhancesSubContainer(bool hasContainer)
{
    CHECK_NULL_VOID(subContainer_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto layoutProperty = host->GetLayoutProperty<FormLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    
    subContainer_->SetFormPattern(WeakClaim(this));
    subContainer_->Initialize();
    subContainer_->SetNodeId(host->GetId());

    subContainer_->AddFormAcquireCallback([weak = WeakClaim(this), pipeline](int64_t id) {
        CHECK_NULL_VOID(pipeline);
        auto uiTaskExecutor =
            SingleTaskExecutor::Make(pipeline->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        uiTaskExecutor.PostTask([id, weak] {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->FireOnAcquiredEvent(id);
            }, "ArkUIFormFireAcquiredEvent");
    });

    subContainer_->SetFormLoadCallback([weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnLoadEvent();
    });

    subContainer_->AddFormVisiableCallback([weak = WeakClaim(this), layoutProperty]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        CHECK_NULL_VOID(layoutProperty);
        auto visible = layoutProperty->GetVisibleType().value_or(VisibleType::VISIBLE);
        layoutProperty->UpdateVisibility(visible);
        pattern->isLoaded_ = true;
    });

    if (hasContainer) {
        subContainer_->RunSameCard();
    }
}

bool FormPattern::ShouldAddChildAtReuildFrame()
{
    auto externalRenderContext = DynamicCast<NG::RosenRenderContext>(GetExternalRenderContext());
    CHECK_NULL_RETURN(externalRenderContext, true);
    auto externalRsNode = externalRenderContext->GetRSNode();
    if (externalRsNode) {
        auto externalParentRsNode = externalRsNode->GetParent();
        if (externalParentRsNode) {
            uint32_t externalParentRsNodeId = externalParentRsNode->GetId();
            TAG_LOGW(AceLogTag::ACE_FORM, "external Parent RsNode Id:%{public}d", externalParentRsNodeId);
            if (externalParentRsNodeId != 0) {
                return false;
            }
        }
    } else {
        TAG_LOGW(AceLogTag::ACE_FORM, "external RsNode is null");
    }
    return true;
}

void FormPattern::DumpInfo()
{
    TAG_LOGI(AceLogTag::ACE_FORM, "dump form info in string format");
    if (formManagerBridge_ == nullptr) {
        TAG_LOGE(AceLogTag::ACE_FORM, "formManagerBridge_ is null");
        return;
    }

    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    std::vector<std::string> params = container->GetUieParams();
    // Use -noform to choose not dump form info
    if (std::find(params.begin(), params.end(), NO_FORM_DUMP) != params.end()) {
        TAG_LOGI(AceLogTag::ACE_FORM, "Not Support Dump Form Info");
    } else {
        params.push_back(std::to_string(getpid()));
        std::vector<std::string> dumpInfo;
        formManagerBridge_->NotifyFormDump(params, dumpInfo);
        for (std::string& info : dumpInfo) {
            std::string infoRes = std::regex_replace(info, std::regex(R"(\n)"), ";");
            DumpLog::GetInstance().AddDesc(std::string("Form info: ").append(infoRes));
        }
    }
}

void FormPattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    TAG_LOGI(AceLogTag::ACE_FORM, "dump form info in json format");
    if (formManagerBridge_ == nullptr) {
        TAG_LOGE(AceLogTag::ACE_FORM, "formManagerBridge_ is null");
        return;
    }

    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    std::vector<std::string> params = container->GetUieParams();
    // Use -noform to choose not dump form info
    if (std::find(params.begin(), params.end(), NO_FORM_DUMP) != params.end()) {
        TAG_LOGI(AceLogTag::ACE_FORM, "Not Support Dump Form Info");
    } else {
        params.push_back(std::to_string(getpid()));
        std::vector<std::string> dumpInfo;
        formManagerBridge_->NotifyFormDump(params, dumpInfo);
        for (std::string& info : dumpInfo) {
            std::string infoRes = std::regex_replace(info, std::regex(R"(\n)"), ";");
            json->Put("Form info: ", infoRes.c_str());
        }
    }
}

bool FormPattern::IsFormBundleLocked(const std::string& bundleName, int64_t formId)
{
    CHECK_NULL_RETURN(formManagerBridge_, false);
    return formManagerBridge_->IsFormBundleLocked(bundleName, formId);
}

void FormPattern::HandleLockEvent(bool isLock)
{
    auto newFormSpecialStyle = formSpecialStyle_;
    newFormSpecialStyle.SetIsLockedByAppLock(isLock);
    HandleFormStyleOperation(newFormSpecialStyle);
}

void FormPattern::HandleFormStyleOperation(const FormSpecialStyle& newFormSpecialStyle, const RequestFormInfo& info)
{
    auto formOperation = formSpecialStyle_.GetOperationToNewFormStyle(newFormSpecialStyle);
    TAG_LOGW(AceLogTag::ACE_FORM, "HandleFormStyleOperation formSpecialStyle_:%{public}d, new:%{public}d,",
        static_cast<int32_t>(formSpecialStyle_.GetFormStyleAttribution()),
        static_cast<int32_t>(newFormSpecialStyle.GetFormStyleAttribution()));
    formSpecialStyle_ = newFormSpecialStyle;
    switch (formOperation) {
        case FormOperation::KEEP:
            TAG_LOGI(AceLogTag::ACE_FORM, "KEEP");
            return;
        case FormOperation::UNLOAD:
            TAG_LOGI(AceLogTag::ACE_FORM, "UNLOAD");
            RemoveDisableFormStyle(info);
            break;
        case FormOperation::LOAD:
            TAG_LOGI(AceLogTag::ACE_FORM, "LOAD");
            LoadDisableFormStyle(info);
            break;
        case FormOperation::REFRESH:
            TAG_LOGI(AceLogTag::ACE_FORM, "REFRESH");
            LoadDisableFormStyle(info, true);
    }
}

void FormPattern::HandleFormStyleOperation(const FormSpecialStyle& newFormSpecialStyle)
{
  HandleFormStyleOperation(newFormSpecialStyle, cardInfo_);
}

Color FormPattern::GetFormStyleBackGroundColor()
{
  return SystemProperties::GetColorMode() == ColorMode::DARK ?
      Color::LineColorTransition(Color(TOP_BG_COLOR_DARK), Color(BOTTOM_BG_COLOR_DARK), TRANSITION_PERCENT)
      : Color::LineColorTransition(Color(TOP_BG_COLOR_LIGHT), Color(BOTTOM_BG_COLOR_LIGHT), TRANSITION_PERCENT);
}
} // namespace OHOS::Ace::NG
