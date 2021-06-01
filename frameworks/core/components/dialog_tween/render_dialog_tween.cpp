/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/dialog_tween/render_dialog_tween.h"

#include "base/geometry/dimension.h"
#include "base/geometry/offset.h"
#include "base/log/event_report.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components/stack/stack_element.h"
#include "core/event/ace_event_helper.h"
#include "core/event/back_end_event_manager.h"

namespace OHOS::Ace {
namespace {

// Using UX spec: Constrain max height within 4/5 of screen height.
constexpr double DIALOG_HEIGHT_RATIO = 0.8;
constexpr double DIALOG_HEIGHT_RATIO_FOR_LANDSCAPE = 0.9;
constexpr double DIALOG_DRAG_RATIO = 0.5;
constexpr int32_t POSITIVE_SUCCESS_ID = 0;
constexpr int32_t NEGATIVE_SUCCESS_ID = 1;
constexpr int32_t NEUTRAL_SUCCESS_ID = 2;

} // namespace

RenderDialogTween::RenderDialogTween()
{
    clickDetector_ = AceType::MakeRefPtr<ClickRecognizer>();
    clickDetector_->SetOnClick([weak = WeakClaim(this)](const ClickInfo& info) {
        auto dialog = weak.Upgrade();
        if (dialog) {
            dialog->HandleClick(info.GetLocalLocation());
        }
    });
    dragDetector_ = AceType::MakeRefPtr<DragRecognizer>(Axis::HORIZONTAL);
    dragDetector_->SetOnDragStart([weak = WeakClaim(this)](const DragStartInfo& startInfo) {
        auto dialog = weak.Upgrade();
        if (dialog) {
            dialog->dragStart_ = startInfo.GetLocalLocation().GetX();
        }
    });
    dragDetector_->SetOnDragEnd([weak = WeakClaim(this)](const DragEndInfo& endInfo) {
        auto dialog = weak.Upgrade();
        if (dialog) {
            double dragEnd = endInfo.GetLocalLocation().GetX();
            if (GreatOrEqual(dragEnd - dialog->dragStart_, dialog->GetLayoutSize().Width() * DIALOG_DRAG_RATIO)) {
                dialog->PopDialog();
            }
        }
    });
}

RenderDialogTween::~RenderDialogTween()
{
    auto dialogTweenComponent = weakDialogTweenComponent_.Upgrade();
    if (dialogTweenComponent) {
        RemoveBackendEvent(dialogTweenComponent);
    }
}

RefPtr<RenderNode> RenderDialogTween::Create()
{
    return AceType::MakeRefPtr<RenderDialogTween>();
}

void RenderDialogTween::Update(const RefPtr<Component>& component)
{
    const RefPtr<DialogTweenComponent> dialog = AceType::DynamicCast<DialogTweenComponent>(component);
    if (!dialog) {
        LOGE("RenderDialogTween update with nullptr");
        EventReport::SendRenderException(RenderExcepType::RENDER_COMPONENT_ERR);
        return;
    }
    weakDialogTweenComponent_ = dialog;
    autoCancel_ = dialog->GetAutoCancel();
    onSuccess_ = AceAsyncEvent<void(int32_t)>::Create(dialog->GetOnSuccessId(), context_);
    onCancel_ = AceAsyncEvent<void()>::Create(dialog->GetOnCancelId(), context_);
    onComplete_ = AceAsyncEvent<void()>::Create(dialog->GetOnCompleteId(), context_);
    animator_ = dialog->GetParentAnimator();
    composedId_ = dialog->GetComposedId();
    customDialogId_ = dialog->GetCustomDialogId();
    data_ = dialog->GetData();
    isLimit_ = dialog->GetDialogLimit();
    isSetMargin_ = dialog->IsSetMargin();
    if (isSetMargin_) {
        margin_ = dialog->GetMargin();
    }
    BackEndEventManager<void()>::GetInstance().BindBackendEvent(
        dialog->GetOnPositiveSuccessId(), [weak = WeakClaim(this)]() {
            auto dialog = weak.Upgrade();
            dialog->CallOnSuccess(POSITIVE_SUCCESS_ID);
        });

    BackEndEventManager<void()>::GetInstance().BindBackendEvent(
        dialog->GetOnNegativeSuccessId(), [weak = WeakClaim(this)]() {
            auto dialog = weak.Upgrade();
            dialog->CallOnSuccess(NEGATIVE_SUCCESS_ID);
        });

    BackEndEventManager<void()>::GetInstance().BindBackendEvent(
        dialog->GetOnNeutralSuccessId(), [weak = WeakClaim(this)]() {
            auto dialog = weak.Upgrade();
            dialog->CallOnSuccess(NEUTRAL_SUCCESS_ID);
        });
    MarkNeedLayout();
}

void RenderDialogTween::CallOnSuccess(int32_t successType)
{
    const auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    const auto& lastStack = context->GetLastStack();
    if (!lastStack) {
        return;
    }
    if (animator_) {
        animator_->AddStopListener([successType, lastStack, weak = WeakClaim(this)] {
            auto dialog = weak.Upgrade();
            if (!dialog) {
                return;
            }
            lastStack->PopDialog(true);
            if (dialog->onSuccess_) {
                dialog->onSuccess_(successType);
            }
            if (dialog->onComplete_) {
                dialog->onComplete_();
            }
        });
        animator_->Play();
    } else {
        lastStack->PopDialog(true);
        if (onSuccess_) {
            onSuccess_(successType);
        }
        if (onComplete_) {
            onComplete_();
        }
    }
    const auto& accessibilityManager = context->GetAccessibilityManager();
    if (accessibilityManager) {
        accessibilityManager->RemoveAccessibilityNodeById(composedId_);
    }
}

double RenderDialogTween::GetMaxWidthBasedOnGridType(
    const RefPtr<GridColumnInfo>& info, GridSizeType type, DeviceType deviceType)
{
    if (deviceType == DeviceType::WATCH) {
        if (type == GridSizeType::SM) {
            return info->GetWidth(3);
        } else if (type == GridSizeType::MD) {
            return info->GetWidth(4);
        } else if (type == GridSizeType::LG) {
            return info->GetWidth(5);
        } else {
            LOGI("GetMaxWidthBasedOnGridType is undefined");
            return info->GetWidth(5);
        }
    } else if (deviceType == DeviceType::PHONE) {
        if (type == GridSizeType::SM) {
            return info->GetWidth(4);
        } else if (type == GridSizeType::MD) {
            return info->GetWidth(5);
        } else if (type == GridSizeType::LG) {
            return info->GetWidth(6);
        } else {
            LOGI("GetMaxWidthBasedOnGridType is undefined");
            return info->GetWidth(6);
        }
    } else {
        if (type == GridSizeType::SM) {
            return info->GetWidth(2);
        } else if (type == GridSizeType::MD) {
            return info->GetWidth(3);
        } else if (type == GridSizeType::LG) {
            return info->GetWidth(4);
        } else {
            LOGI("GetMaxWidthBasedOnGridType is undefined");
            return info->GetWidth(4);
        }
    }
}

void RenderDialogTween::PerformLayout()
{
    LayoutParam innerLayout = GetLayoutParam();
    auto maxSize = innerLayout.GetMaxSize();
    auto theme = GetTheme<DialogTheme>();
    if (!theme) {
        return;
    }
    // Set different layout param for different devices
    auto gridSizeType = GridSystemManager::GetInstance().GetCurrentSize();
    auto columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::DIALOG);
    columnInfo->GetParent()->BuildColumnWidth();
    auto width = GetMaxWidthBasedOnGridType(columnInfo, gridSizeType, SystemProperties::GetDeviceType());
    if (!isLimit_) {
        innerLayout.SetMinSize(Size(0.0, 0.0));
        innerLayout.SetMaxSize(Size(maxSize.Width(), maxSize.Height()));
    } else if (SystemProperties::GetDeviceType() == DeviceType::WATCH) {
        innerLayout.SetMinSize(Size(width, 0.0));
        innerLayout.SetMaxSize(Size(width, maxSize.Height()));
    } else if (SystemProperties::GetDeviceType() == DeviceType::PHONE) {
        if (SystemProperties::GetDevcieOrientation() == DeviceOrientation::LANDSCAPE) {
            innerLayout.SetMinSize(Size(width, 0.0));
            innerLayout.SetMaxSize(Size(width, maxSize.Height() * DIALOG_HEIGHT_RATIO_FOR_LANDSCAPE));
        } else {
            innerLayout.SetMinSize(Size(width, 0.0));
            innerLayout.SetMaxSize(Size(width, maxSize.Height() * DIALOG_HEIGHT_RATIO));
        }
    } else {
        innerLayout.SetMinSize(Size(width, 0.0));
        innerLayout.SetMaxSize(Size(width, maxSize.Height() * DIALOG_HEIGHT_RATIO));
    }
    if (GetChildren().empty()) {
        SetLayoutSize(maxSize);
        return;
    }
    const auto& child = GetChildren().front();
    child->Layout(innerLayout);
    auto childSize = child->GetLayoutSize();
    Offset topLeftPoint;
    // Set different positions for different devices
    if (SystemProperties::GetDeviceType() == DeviceType::PHONE &&
        SystemProperties::GetDevcieOrientation() == DeviceOrientation::PORTRAIT) {
        topLeftPoint = Offset((maxSize.Width() - childSize.Width()) / 2.0,
            maxSize.Height() - childSize.Height() - (isSetMargin_ ? 0.0 : NormalizeToPx(theme->GetMarginBottom())));
    } else {
        topLeftPoint =
            Offset((maxSize.Width() - childSize.Width()) / 2.0, (maxSize.Height() - childSize.Height()) / 2.0);
    }

    child->SetPosition(topLeftPoint);
    UpdateTouchRegion(topLeftPoint, maxSize, childSize);
    SetLayoutSize(maxSize);
}

void RenderDialogTween::UpdateTouchRegion(const Offset& topLeftPoint, const Size& maxSize, const Size& childSize)
{
    double left = margin_.Left().Unit() == DimensionUnit::PERCENT ? margin_.Left().Value() * maxSize.Width()
                                                                  : NormalizeToPx(margin_.Left());
    double top = margin_.Top().Unit() == DimensionUnit::PERCENT ? margin_.Top().Value() * maxSize.Height()
                                                                : NormalizeToPx(margin_.Top());
    Offset touchTopLeft = topLeftPoint + (isSetMargin_ ? Offset(left, top) : Offset(0.0, 0.0));

    double right = margin_.Right().Unit() == DimensionUnit::PERCENT ? margin_.Right().Value() * maxSize.Width()
                                                                    : NormalizeToPx(margin_.Right());
    double bottom = margin_.Bottom().Unit() == DimensionUnit::PERCENT ? margin_.Bottom().Value() * maxSize.Height()
                                                                      : NormalizeToPx(margin_.Bottom());
    Offset touchBottomRight = topLeftPoint + childSize - (isSetMargin_ ? Offset(right, bottom) : Offset(0.0, 0.0));

    maskTouchRegion_ = TouchRegion(touchTopLeft, touchBottomRight);
    LOGD("top: %{public}lf, bottom:%{public}lf, left: %{public}lf, right:%{public}lf isSetMargin:%{public}d",
        touchTopLeft.GetY(), touchBottomRight.GetY(), touchTopLeft.GetX(), touchBottomRight.GetX(), isSetMargin_);
}

void RenderDialogTween::OnPaintFinish()
{
    InitAccessibilityEventListener();
}

void RenderDialogTween::HandleClick(const Offset& clickPosition)
{
    if (autoCancel_ && !maskTouchRegion_.ContainsInRegion(clickPosition.GetX(), clickPosition.GetY())) {
        PopDialog();
    }
}

void RenderDialogTween::OnTouchTestHit(
    const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result)
{
    clickDetector_->SetCoordinateOffset(coordinateOffset);
    result.emplace_back(clickDetector_);
    result.emplace_back(dragDetector_);
}

bool RenderDialogTween::PopDialog()
{
    const auto context = context_.Upgrade();
    if (!context) {
        return false;
    }
    const auto& lastStack = context->GetLastStack();
    if (!lastStack) {
        return false;
    }
    if (animator_) {
        animator_->AddStopListener([lastStack, weak = AceType::WeakClaim(this)] {
            auto dialog = weak.Upgrade();
            if (!dialog) {
                return;
            }
            lastStack->PopDialog(true);
            if (dialog->onCancel_) {
                dialog->onCancel_();
            }
            if (dialog->onComplete_) {
                dialog->onComplete_();
            }
        });
        animator_->Play();
    } else {
        lastStack->PopDialog(true);
        if (onCancel_) {
            onCancel_();
        }
        if (onComplete_) {
            onComplete_();
        }
    }
    const auto& accessibilityManager = context->GetAccessibilityManager();
    if (accessibilityManager) {
        accessibilityManager->RemoveAccessibilityNodeById(composedId_);
    }
#if defined(WINDOWS_PLATFORM) || defined(MAC_PLATFORM)
    auto node = accessibilityManager->GetAccessibilityNodeById(customDialogId_);
    accessibilityManager->ClearNodeRectInfo(node, true);
#endif
    return true;
}

void RenderDialogTween::SetAnimator(const RefPtr<Animator>& animator)
{
    animator_ = animator;
}

void RenderDialogTween::InitAccessibilityEventListener()
{
    const auto& accessibilityNode = GetAccessibilityNode().Upgrade();
    if (!accessibilityNode) {
        return;
    }
    accessibilityNode->SetFocusableState(true);
    accessibilityNode->SetText(data_);

    accessibilityNode->AddSupportAction(AceAction::CUSTOM_ACTION);
    accessibilityNode->AddSupportAction(AceAction::ACTION_CLICK);
    accessibilityNode->AddSupportAction(AceAction::ACTION_FOCUS);
    accessibilityNode->AddSupportAction(AceAction::ACTION_LONG_CLICK);
    accessibilityNode->AddSupportAction(AceAction::GLOBAL_ACTION_BACK);
    accessibilityNode->SetLongClickableState(true);

    accessibilityNode->SetActionLongClickImpl([weakPtr = WeakClaim(this)]() {
        const auto& dialogTween = weakPtr.Upgrade();
        if (dialogTween) {
            dialogTween->PopDialog();
        }
    });
}

void RenderDialogTween::RemoveBackendEvent(const RefPtr<DialogTweenComponent>& component)
{
    BackEndEventManager<void()>::GetInstance().RemoveBackEndEvent(component->GetOnPositiveSuccessId());
    BackEndEventManager<void()>::GetInstance().RemoveBackEndEvent(component->GetOnNegativeSuccessId());
    BackEndEventManager<void()>::GetInstance().RemoveBackEndEvent(component->GetOnNeutralSuccessId());
}

} // namespace OHOS::Ace