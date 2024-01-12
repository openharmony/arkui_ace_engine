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

#include "form_info_base.h"
#include "pointer_event.h"
#include "transaction/rs_interfaces.h"

#include "base/geometry/dimension.h"
#include "base/log/log_wrapper.h"
#include "base/utils/utils.h"
#include "base/utils/time_util.h"
#include "core/common/form_manager.h"
#include "core/common/frontend.h"
#include "core/components/form/resource/form_manager_delegate.h"
#include "core/components/form/sub_container.h"
#include "core/components_ng/pattern/form/form_event_hub.h"
#include "core/components_ng/pattern/form/form_layout_property.h"
#include "core/components_ng/pattern/form/form_node.h"
#include "core/components_ng/pattern/form/form_theme.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/pipeline_ng/pipeline_context.h"

#include "form_constants.h"

#if OHOS_STANDARD_SYSTEM
#include "form_info.h"
#endif

#include "core/common/udmf/udmf_client.h"

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t DELAY_TIME_FOR_FORM_SUBCONTAINER_CACHE = 30000;
constexpr uint32_t DELAY_TIME_FOR_FORM_SNAPSHOT_3S = 3000;
constexpr double ARC_RADIUS_TO_DIAMETER = 2.0;
constexpr double NON_TRANSPARENT_VAL = 1.0;
constexpr double TRANSPARENT_VAL = 0;

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
        auto subContainer = pattern->GetSubContainer();
        CHECK_NULL_VOID(subContainer);
        auto uiTaskExecutor =
            SingleTaskExecutor::Make(host->GetContext()->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        auto id = subContainer->GetRunningCardId();
        FormManager::GetInstance().AddSubContainer(id, subContainer);
        uiTaskExecutor.PostDelayedTask(
            [id, nodeId = subContainer->GetNodeId()] {
                auto cachedSubContainer = FormManager::GetInstance().GetSubContainer(id);
                if (cachedSubContainer != nullptr && cachedSubContainer->GetNodeId() == nodeId) {
                    FormManager::GetInstance().RemoveSubContainer(id);
                }
            },
            DELAY_TIME_FOR_FORM_SUBCONTAINER_CACHE);
    });

    // Init click event for static form.
    auto gestureEventHub = host->GetOrCreateGestureEventHub();
    auto clickCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto formPattern = weak.Upgrade();
        CHECK_NULL_VOID(formPattern);
        formPattern->HandleStaticFormEvent(
            { static_cast<float>(info.GetLocalLocation().GetX()), static_cast<float>(info.GetLocalLocation().GetY()) });
    };
    auto clickEvent = AceType::MakeRefPtr<ClickEvent>(std::move(clickCallback));
    gestureEventHub->AddClickEvent(clickEvent);
    scopeId_ = Container::CurrentId();

    RegistVisibleAreaChangeCallback();
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
    UpdateBackgroundColorWhenUnTrustForm();
    auto layoutProperty = host->GetLayoutProperty<FormLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto visible = layoutProperty->GetVisibleType().value_or(VisibleType::VISIBLE);
    layoutProperty->UpdateVisibility(visible);
    isLoaded_ = true;

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

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto formTheme = pipelineContext->GetTheme<FormTheme>();
    CHECK_NULL_VOID(formTheme);
    Color unTrustBackgroundColor = formTheme->GetUnTrustBackgroundColor();
    host->GetRenderContext()->UpdateBackgroundColor(unTrustBackgroundColor);
}

void FormPattern::HandleSnapshot(uint32_t delayTime)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto executor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(executor);
    snapshotTimestamp_ = GetCurrentTimestamp();
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
        TaskExecutor::TaskType::UI, delayTime);
}

void FormPattern::HandleStaticFormEvent(const PointF& touchPoint)
{
    if (formLinkInfos_.empty() || isDynamic_) {
        return;
    }
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
    auto externalContext = DynamicCast<NG::RosenRenderContext>(renderContext);
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
    auto uiTaskExecutor =
        SingleTaskExecutor::Make(host->GetContext()->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    uiTaskExecutor.PostTask([weak = WeakClaim(this), pixelMap] {
        auto formPattern = weak.Upgrade();
        CHECK_NULL_VOID(formPattern);
        formPattern->HandleOnSnapshot(pixelMap);
    });
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

void FormPattern::UpdateStaticCard()
{
    // 1. Use imageNode to display pixelMap
    UpdateImageNode();
    // 2. Remove FrsNode from formNode
    RemoveFrsNode();
    // 3. Release renderer obj
    ReleaseRenderer();
}

void FormPattern::DeleteImageNode()
{
    ContainerScope scope(scopeId_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto child = host->GetLastChild();
    CHECK_NULL_VOID(child);

    std::list<RefPtr<UINode>> children = host->GetChildren();
    if (children.size() > 0 && child->GetTag() == V2::IMAGE_ETS_TAG) {
        host->RemoveChildAtIndex(children.size() - 1);
    }
}

RefPtr<FrameNode> FormPattern::CreateImageNode()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto formNode = DynamicCast<FormNode>(host);
    CHECK_NULL_RETURN(formNode, nullptr);
    auto imageId = formNode->GetImageId();
    auto imageNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, imageId, AceType::MakeRefPtr<ImagePattern>());
    CHECK_NULL_RETURN(imageNode, nullptr);
    host->AddChild(imageNode);
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
    DeleteImageNode();
    auto imageNode = CreateImageNode();
    CHECK_NULL_VOID(imageNode);
    auto pixelLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(pixelLayoutProperty);
    auto pixelSourceInfo = ImageSourceInfo(pixelMap_);

    auto width = static_cast<float>(cardInfo_.width.Value());
    auto height = static_cast<float>(cardInfo_.height.Value());
    CalcSize idealSize = { CalcLength(width), CalcLength(height) };
    MeasureProperty layoutConstraint;
    layoutConstraint.selfIdealSize = idealSize;
    layoutConstraint.maxSize = idealSize;
    imageNode->UpdateLayoutConstraint(layoutConstraint);
    pixelLayoutProperty->UpdateImageSourceInfo(pixelSourceInfo);
    auto externalContext = DynamicCast<NG::RosenRenderContext>(imageNode->GetRenderContext());
    CHECK_NULL_VOID(externalContext);
    externalContext->SetVisible(true);

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
    info.width = Dimension(width.ConvertToPx());
    info.height = Dimension(height.ConvertToPx());
    layoutProperty->UpdateRequestFormInfo(info);
    UpdateBackgroundColorWhenUnTrustForm();
    HandleFormComponent(info);
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
    layoutProperty->UpdateRequestFormInfo(info);

    UpdateBackgroundColorWhenUnTrustForm();
    HandleFormComponent(info);
    return false;
}

void FormPattern::HandleFormComponent(const RequestFormInfo& info)
{
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
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    // When cardInfo has changed, it will call AddForm in Fwk
    // If the width or height equal to zero, it will not
    if (NonPositive(info.width.Value()) || NonPositive(info.height.Value())) {
        TAG_LOGW(AceLogTag::ACE_FORM, "Invalid form size.");
        return;
    }
    TAG_LOGI(AceLogTag::ACE_FORM, "width: %{public}f   height: %{public}f", info.width.Value(), info.height.Value());
    cardInfo_ = info;
    if (info.dimension == static_cast<int32_t>(OHOS::AppExecFwk::Constants::Dimension::DIMENSION_1_1)) {
        BorderRadiusProperty borderRadius;
        Dimension diameter = std::min(info.width, info.height);
        borderRadius.SetRadius(diameter / ARC_RADIUS_TO_DIAMETER);
        host->GetRenderContext()->UpdateBorderRadius(borderRadius);
    }
    isJsCard_ = true;
#if OHOS_STANDARD_SYSTEM
    AppExecFwk::FormInfo formInfo;
    if (FormManagerDelegate::GetFormInfo(info.bundleName, info.moduleName, info.cardName, formInfo) &&
        formInfo.uiSyntax == AppExecFwk::FormType::ETS) {
        isJsCard_ = false;
    }
#endif

    CreateCardContainer();
    if (host->IsDraggable()) {
        EnableDrag();
    }
    if (formManagerBridge_) {
#if OHOS_STANDARD_SYSTEM
        formManagerBridge_->AddForm(host->GetContext(), info, formInfo);
#else
        formManagerBridge_->AddForm(host->GetContext(), info);
#endif
    }
}

void FormPattern::UpdateFormComponent(const RequestFormInfo& info)
{
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

    if (cardInfo_.width != info.width || cardInfo_.height != info.height) {
        TAG_LOGI(AceLogTag::ACE_FORM, "update size, width: %{public}f   height: %{public}f",
            info.width.Value(), info.height.Value());
        cardInfo_.width = info.width;
        cardInfo_.height = info.height;
        if (formManagerBridge_) {
            formManagerBridge_->NotifySurfaceChange(info.width.Value(), info.height.Value());
        }
        if (info.dimension == static_cast<int32_t>(OHOS::AppExecFwk::Constants::Dimension::DIMENSION_1_1)) {
            BorderRadiusProperty borderRadius;
            Dimension diameter = std::min(info.width, info.height);
            borderRadius.SetRadius(diameter / ARC_RADIUS_TO_DIAMETER);
            host->GetRenderContext()->UpdateBorderRadius(borderRadius);
        }
        if (subContainer_) {
            subContainer_->SetFormPattern(WeakClaim(this));
            subContainer_->UpdateRootElementSize();
            subContainer_->UpdateSurfaceSizeWithAnimathion();
        }
    }
    if (isLoaded_) {
        auto visible = layoutProperty->GetVisibleType().value_or(VisibleType::VISIBLE);
        layoutProperty->UpdateVisibility(visible);
        if (!isDynamic_ && !isSnapshot_ && needSnapshotAgain_) {
            auto renderContext = host->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            auto opacity = renderContext->GetOpacityValue(NON_TRANSPARENT_VAL);
            TAG_LOGI(AceLogTag::ACE_FORM, "Static-form, current opacity: %{public}f, visible: %{public}d",
                opacity, static_cast<int>(visible));
            if (visible == VisibleType::VISIBLE && opacity == NON_TRANSPARENT_VAL) {
                HandleSnapshot(DELAY_TIME_FOR_FORM_SNAPSHOT_3S);
            }
        }
    }
    UpdateConfiguration();
}

void FormPattern::InitFormManagerDelegate()
{
    if (formManagerBridge_) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    formManagerBridge_ = AceType::MakeRefPtr<FormManagerDelegate>(context);
    formManagerBridge_->AddRenderDelegate();
    formManagerBridge_->RegisterRenderDelegateEvent();
    auto formUtils = FormManager::GetInstance().GetFormUtils();
    if (formUtils) {
        formManagerBridge_->SetFormUtils(formUtils);
    }
    int32_t instanceID = context->GetInstanceId();
    formManagerBridge_->AddFormAcquireCallback([weak = WeakClaim(this), instanceID](int64_t id, const std::string& path,
                                                   const std::string& module, const std::string& data,
                                                   const std::map<std::string, sptr<AppExecFwk::FormAshmem>>&
                                                       imageDataMap,
                                                   const AppExecFwk::FormJsInfo& formJsInfo,
                                                   const FrontendType& frontendType, const FrontendType& uiSyntax) {
        ContainerScope scope(instanceID);
        auto form = weak.Upgrade();
        CHECK_NULL_VOID(form);
        auto host = form->GetHost();
        CHECK_NULL_VOID(host);
        auto uiTaskExecutor =
            SingleTaskExecutor::Make(host->GetContext()->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        uiTaskExecutor.PostTask([id, path, module, data, imageDataMap, formJsInfo, weak, instanceID, frontendType,
                                    uiSyntax] {
            ContainerScope scope(instanceID);
            auto form = weak.Upgrade();
            CHECK_NULL_VOID(form);
            auto container = form->GetSubContainer();
            CHECK_NULL_VOID(container);
            container->SetWindowConfig({ formJsInfo.formWindow.designWidth, formJsInfo.formWindow.autoDesignWidth });
            container->RunCard(id, path, module, data, imageDataMap, formJsInfo.formSrc, frontendType, uiSyntax);
        });
    });

    formManagerBridge_->AddFormUpdateCallback(
        [weak = WeakClaim(this), instanceID](int64_t id, const std::string& data,
            const std::map<std::string, sptr<AppExecFwk::FormAshmem>>& imageDataMap) {
            ContainerScope scope(instanceID);
            auto form = weak.Upgrade();
            CHECK_NULL_VOID(form);
            auto host = form->GetHost();
            CHECK_NULL_VOID(host);
            auto uiTaskExecutor =
                SingleTaskExecutor::Make(host->GetContext()->GetTaskExecutor(), TaskExecutor::TaskType::UI);
            uiTaskExecutor.PostTask([id, data, imageDataMap, weak, instanceID] {
                ContainerScope scope(instanceID);
                auto form = weak.Upgrade();
                CHECK_NULL_VOID(form);
                if (form->ISAllowUpdate()) {
                    form->GetSubContainer()->UpdateCard(data, imageDataMap);
                }
            });
        });

    formManagerBridge_->AddFormErrorCallback(
        [weak = WeakClaim(this), instanceID](const std::string& code, const std::string& msg) {
            ContainerScope scope(instanceID);
            auto form = weak.Upgrade();
            CHECK_NULL_VOID(form);
            auto host = form->GetHost();
            CHECK_NULL_VOID(host);
            auto uiTaskExecutor =
                SingleTaskExecutor::Make(host->GetContext()->GetTaskExecutor(), TaskExecutor::TaskType::UI);
            uiTaskExecutor.PostTask([code, msg, weak, instanceID] {
                ContainerScope scope(instanceID);
                auto form = weak.Upgrade();
                CHECK_NULL_VOID(form);
                form->FireOnErrorEvent(code, msg);
            });
        });

    formManagerBridge_->AddFormUninstallCallback([weak = WeakClaim(this), instanceID](int64_t formId) {
        ContainerScope scope(instanceID);
        auto form = weak.Upgrade();
        CHECK_NULL_VOID(form);
        auto host = form->GetHost();
        CHECK_NULL_VOID(host);
        auto uiTaskExecutor =
            SingleTaskExecutor::Make(host->GetContext()->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        uiTaskExecutor.PostTask([formId, weak, instanceID] {
            ContainerScope scope(instanceID);
            auto form = weak.Upgrade();
            CHECK_NULL_VOID(form);
            form->FireOnUninstallEvent(formId);
        });
    });

    formManagerBridge_->AddFormSurfaceNodeCallback(
        [weak = WeakClaim(this), instanceID](const std::shared_ptr<Rosen::RSSurfaceNode>& node, bool isDynamic) {
            ContainerScope scope(instanceID);
            auto form = weak.Upgrade();
            CHECK_NULL_VOID(form);
            auto host = form->GetHost();
            CHECK_NULL_VOID(host);
            auto uiTaskExecutor =
                SingleTaskExecutor::Make(host->GetContext()->GetTaskExecutor(), TaskExecutor::TaskType::UI);
            uiTaskExecutor.PostTask([weak, instanceID, node, isDynamic] {
                ContainerScope scope(instanceID);
                auto form = weak.Upgrade();
                CHECK_NULL_VOID(form);
                form->FireFormSurfaceNodeCallback(node, isDynamic);
            });
        });

    formManagerBridge_->AddFormSurfaceChangeCallback([weak = WeakClaim(this), instanceID](float width, float height) {
        ContainerScope scope(instanceID);
        auto form = weak.Upgrade();
        CHECK_NULL_VOID(form);
        auto host = form->GetHost();
        CHECK_NULL_VOID(host);
        auto uiTaskExecutor =
            SingleTaskExecutor::Make(host->GetContext()->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        uiTaskExecutor.PostTask([weak, instanceID, width, height] {
            ContainerScope scope(instanceID);
            auto form = weak.Upgrade();
            CHECK_NULL_VOID(form);
            form->FireFormSurfaceChangeCallback(width, height);
        });
    });

    formManagerBridge_->AddFormSurfaceDetachCallback([weak = WeakClaim(this), instanceID]() {
            ContainerScope scope(instanceID);
            auto formPattern = weak.Upgrade();
            CHECK_NULL_VOID(formPattern);
            formPattern->FireFormSurfaceDetachCallback();
        });

    formManagerBridge_->AddActionEventHandle([weak = WeakClaim(this), instanceID](const std::string& action) {
        ContainerScope scope(instanceID);
        TAG_LOGI(AceLogTag::ACE_FORM, "Card receive action event, action: %{public}s", action.c_str());
        auto formPattern = weak.Upgrade();
        CHECK_NULL_VOID(formPattern);
        formPattern->OnActionEvent(action);
    });

    formManagerBridge_->AddUnTrustFormCallback([weak = WeakClaim(this), instanceID]() {
        ContainerScope scope(instanceID);
        auto formPattern = weak.Upgrade();
        CHECK_NULL_VOID(formPattern);
        auto host = formPattern->GetHost();
        CHECK_NULL_VOID(host);
        auto uiTaskExecutor =
            SingleTaskExecutor::Make(host->GetContext()->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        uiTaskExecutor.PostTask([weak, instanceID] {
            ContainerScope scope(instanceID);
            auto formPattern = weak.Upgrade();
            CHECK_NULL_VOID(formPattern);
            formPattern->HandleUnTrustForm();
        });
    });

    formManagerBridge_->AddSnapshotCallback([weak = WeakClaim(this), instanceID](const uint32_t& delayTime) {
        ContainerScope scope(instanceID);
        auto formPattern = weak.Upgrade();
        CHECK_NULL_VOID(formPattern);
        formPattern->HandleSnapshot(delayTime);
    });

    formManagerBridge_->AddFormLinkInfoUpdateCallback(
        [weak = WeakClaim(this), instanceID](const std::vector<std::string>& infos) {
            ContainerScope scope(instanceID);
            auto formPattern = weak.Upgrade();
            CHECK_NULL_VOID(formPattern);
            formPattern->SetFormLinkInfos(infos);
        });
}

void FormPattern::FireFormSurfaceNodeCallback(const std::shared_ptr<Rosen::RSSurfaceNode>& node, bool isDynamic)
{
    CHECK_NULL_VOID(node);
    node->CreateNodeInRenderThread();

    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto externalRenderContext = DynamicCast<NG::RosenRenderContext>(GetExternalRenderContext());
    CHECK_NULL_VOID(externalRenderContext);
    externalRenderContext->SetRSNode(node);
    if (isBeenLayout_) {
        auto geometryNode = host->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        auto size = geometryNode->GetFrameSize();
        externalRenderContext->SetBounds(0, 0, size.Width(), size.Height());
    } else {
        externalRenderContext->SetBounds(0, 0, cardInfo_.width.Value(), cardInfo_.height.Value());
    }

    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (isDynamic) {
        renderContext->ClearChildren();
    }
    renderContext->AddChild(externalRenderContext, 0);

    auto layoutProperty = host->GetLayoutProperty<FormLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto visible = layoutProperty->GetVisibleType().value_or(VisibleType::VISIBLE);
    TAG_LOGI(AceLogTag::ACE_FORM, "VisibleType: %{public}d", static_cast<int32_t>(visible));
    layoutProperty->UpdateVisibility(visible);

    isLoaded_ = true;
    isUnTrust_ = false;
    isFrsNodeDetached_ = false;
    isDynamic_ = isDynamic;
    DeleteImageNode();
    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    auto parent = host->GetParent();
    CHECK_NULL_VOID(parent);
    parent->MarkNeedSyncRenderTree();
    parent->RebuildRenderContextTree();
    renderContext->RequestNextFrame();
    OnLoadEvent();
}

void FormPattern::FireFormSurfaceChangeCallback(float width, float height)
{
    auto externalRenderContext = DynamicCast<NG::RosenRenderContext>(GetExternalRenderContext());
    CHECK_NULL_VOID(externalRenderContext);
    externalRenderContext->SetBounds(0, 0, width, height);
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
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
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
    CHECK_NULL_VOID(subContainer_);
    subContainer_->SetFormPattern(WeakClaim(this));
    subContainer_->Initialize();
    subContainer_->SetNodeId(host->GetId());

    subContainer_->AddFormAcquireCallback([weak = WeakClaim(this)](size_t id) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto uiTaskExecutor =
            SingleTaskExecutor::Make(host->GetContext()->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        uiTaskExecutor.PostTask([id, weak] {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->FireOnAcquiredEvent(id);
        });
    });

    subContainer_->SetFormLoadCallback([weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnLoadEvent();
    });

    subContainer_->AddFormVisiableCallback([weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto layoutProperty = host->GetLayoutProperty<FormLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        auto visible = layoutProperty->GetVisibleType().value_or(VisibleType::VISIBLE);
        layoutProperty->UpdateVisibility(visible);
        pattern->isLoaded_ = true;
    });

    if (hasContainer) {
        subContainer_->RunSameCard();
    }
}

std::unique_ptr<DrawDelegate> FormPattern::GetDrawDelegate()
{
    auto drawDelegate = std::make_unique<DrawDelegate>();
#ifdef ENABLE_ROSEN_BACKEND
    drawDelegate->SetDrawRSFrameCallback(
        [weak = WeakClaim(this)](std::shared_ptr<RSNode>& node, const Rect& /* dirty */) {
            CHECK_NULL_VOID(node);
            auto form = weak.Upgrade();
            CHECK_NULL_VOID(form);
            auto host = form->GetHost();
            CHECK_NULL_VOID(host);
            auto context = DynamicCast<NG::RosenRenderContext>(host->GetRenderContext());
            CHECK_NULL_VOID(context);
            auto rsNode = context->GetRSNode();
            CHECK_NULL_VOID(rsNode);
            rsNode->AddChild(node, -1);
            host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
        });

    drawDelegate->SetDrawRSFrameByRenderContextCallback(
        [weak = WeakClaim(this)](RefPtr<OHOS::Ace::NG::RenderContext>& renderContext) {
            auto context = DynamicCast<NG::RosenRenderContext>(renderContext);
            CHECK_NULL_VOID(context);
            auto node = context->GetRSNode();
            CHECK_NULL_VOID(node);
            auto form = weak.Upgrade();
            CHECK_NULL_VOID(form);
            auto host = form->GetHost();
            CHECK_NULL_VOID(host);
            auto formContext = DynamicCast<NG::RosenRenderContext>(host->GetRenderContext());
            CHECK_NULL_VOID(formContext);
            auto rsNode = formContext->GetRSNode();
            CHECK_NULL_VOID(rsNode);
            rsNode->AddChild(node, -1);
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
    auto json = JsonUtil::Create(true);
    json->Put("id", std::to_string(id).c_str());
    eventHub->FireOnUninstall(json->ToString());
}

void FormPattern::FireOnAcquiredEvent(int64_t id) const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<FormEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto json = JsonUtil::Create(true);
    json->Put("id", std::to_string(id).c_str());
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
    auto uiTaskExecutor = SingleTaskExecutor::Make(host->GetContext()->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    uiTaskExecutor.PostTask([weak = WeakClaim(this)] {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->FireOnLoadEvent();
    });
}

void FormPattern::OnActionEvent(const std::string& action)
{
    CHECK_NULL_VOID(formManagerBridge_);
    auto eventAction = JsonUtil::ParseJsonString(action);
    if (!eventAction->IsValid()) {
        return;
    }
    auto uri = eventAction->GetValue("uri");
    auto abilityName = eventAction->GetValue("abilityName");
    if (uri->IsValid() && !abilityName->IsValid()) {
        formManagerBridge_->OnActionEvent(action);
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

    if ("router" == type) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto uiTaskExecutor =
            SingleTaskExecutor::Make(host->GetContext()->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        if (uiTaskExecutor.IsRunOnCurrentThread()) {
            FireOnRouterEvent(eventAction);
        } else {
            uiTaskExecutor.PostTask([weak = WeakClaim(this), action] {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                auto eventAction = JsonUtil::ParseJsonString(action);
                pattern->FireOnRouterEvent(eventAction);
            });
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

    if (!isVisible_) {
        auto pointerAction = pointerEvent->GetPointerAction();
        if (pointerAction == OHOS::MMI::PointerEvent::POINTER_ACTION_UP ||
            pointerAction == OHOS::MMI::PointerEvent::POINTER_ACTION_PULL_UP ||
            pointerAction == OHOS::MMI::PointerEvent::POINTER_ACTION_PULL_OUT_WINDOW) {
            // still dispatch 'up' event to finish this pointer event
            formManagerBridge_->DispatchPointerEvent(pointerEvent, serializedGesture);
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
    if (!eventHub->HasOnDragStart()) {
        eventHub->SetOnDragStart(std::move(dragStart));
    }
}

void FormPattern::UpdateConfiguration()
{
    auto localeTag = AceApplicationInfo::GetInstance().GetLocaleTag();
    if (localeTag != localeTag_ && subContainer_) {
        localeTag_ = localeTag;
        subContainer_->UpdateConfiguration();
    }
}

void FormPattern::OnVisibleAreaChange(bool visible)
{
    if (isFrsNodeDetached_) {
        return;
    }
    
    CHECK_NULL_VOID(formManagerBridge_);
    formManagerBridge_->SetVisibleChange(visible);
}

void FormPattern::RegistVisibleAreaChangeCallback()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!isRegistedAreaCallback_) {
        isRegistedAreaCallback_ = true;
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto callback = [weak = WeakClaim(this)](bool visible, double ratio) {
            auto formPattern = weak.Upgrade();
            CHECK_NULL_VOID(formPattern);
            formPattern->OnVisibleAreaChange(visible);
        };
        pipeline->AddVisibleAreaChangeNode(host, 0.0f, callback, false);
    }
}
} // namespace OHOS::Ace::NG
