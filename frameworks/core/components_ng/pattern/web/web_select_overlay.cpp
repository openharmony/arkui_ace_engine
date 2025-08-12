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

#include "core/components_ng/pattern/web/web_select_overlay.h"

#include <algorithm>
#include <optional>

#include "base/utils/utils.h"
#include "core/components_ng/manager/select_content_overlay/select_content_overlay_manager.h"
#include "core/components_ng/manager/select_overlay/select_overlay_manager.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#include "core/components_ng/pattern/web/view_data_common.h"
#include "core/components_ng/pattern/web/transitional_node_info.h"
#include "core/components/web/resource/web_delegate.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/event/event_info_convertor.h"
#include "nweb_handler.h"

namespace OHOS::Ace::NG {
constexpr Dimension SELECT_HANDLE_DEFAULT_HEIGHT = 16.0_vp;
constexpr float SELECT_MENE_HEIGHT = 140.0f;
constexpr int32_t HALF = 2;
const std::string ASK_CELIA_TAG = "askCelia";

namespace {
struct InitStrategyTools {
    RefPtr<PipelineContext> pipeline = nullptr;
    RefPtr<TextOverlayTheme> theme = nullptr;
    RefPtr<SafeAreaManager> safeAreaManager = nullptr;
    RefPtr<GeometryNode> geometryNode = nullptr;
};
}

bool WebSelectOverlay::RunQuickMenu(std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params,
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuCallback> callback)
{
    needResetHandleReverse_ = false;
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_RETURN(pattern, false);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    CHECK_NULL_RETURN(params, false);
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> insertTouchHandle =
        params->GetTouchHandleState(OHOS::NWeb::NWebTouchHandleState::TouchHandleType::INSERT_HANDLE);
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> beginTouchHandle =
        params->GetTouchHandleState(OHOS::NWeb::NWebTouchHandleState::TouchHandleType::SELECTION_BEGIN_HANDLE);
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endTouchHandle =
        params->GetTouchHandleState(OHOS::NWeb::NWebTouchHandleState::TouchHandleType::SELECTION_END_HANDLE);
    WebOverlayType overlayType = GetTouchHandleOverlayType(insertTouchHandle, beginTouchHandle, endTouchHandle);
    if (overlayType == INVALID_OVERLAY) { return false; }
    if (params->GetIsLongPressActived()) {
        TAG_LOGI(AceLogTag::ACE_WEB, "ShowMagnifier");
        pattern->ShowMagnifier(static_cast<int>(pattern->touchPointX), static_cast<int>(pattern->touchPointY));
        return false;
    }
    if (overlayType == INSERT_OVERLAY) {
        CloseOverlay(false, CloseReason::CLOSE_REASON_CLICK_OUTSIDE);
    }
    selectTemporarilyHidden_ = false;
    selectTemporarilyHiddenByScroll_ = false;
    SelectOverlayInfo selectInfo;
    selectInfo.isSingleHandle = (overlayType == INSERT_OVERLAY);
    UpdateRunQuickMenuSelectInfo(selectInfo, params, insertTouchHandle, beginTouchHandle, endTouchHandle);
    if (isQuickMenuMouseTrigger_) {
        return false;
    }
    SetMenuOptions(selectInfo, params, callback);
    SetComputeMenuOffset(selectInfo);
    RegisterSelectOverlayEvent(selectInfo);
    selectInfo.ancestorViewPort = pattern->GetViewPort();
    if (selectInfo.isNewAvoid) {
        ShowMenu();
        selectInfo.menuInfo.menuIsShow = true;
    }
    dropParams_ = params;
    selectMenuInfo_ = selectInfo.menuInfo;
    insertHandle_ = insertTouchHandle;
    startSelectionHandle_ = beginTouchHandle;
    endSelectionHandle_ = endTouchHandle;
    isShowHandle_ = true;
    webSelectInfo_ = selectInfo;
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, false);
    StartListenSelectOverlayParentScroll(host);
    ProcessOverlay({ .animation = true });
    SetTouchHandleExistState(true);
    return true;
}

void WebSelectOverlay::OnTouchSelectionChanged(std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> insertHandle,
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> startSelectionHandle,
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endSelectionHandle)
{
    needResetHandleReverse_ = false;
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_VOID(pattern);
    WebOverlayType overlayType = GetTouchHandleOverlayType(insertHandle, startSelectionHandle, endSelectionHandle);
    if (overlayType == INVALID_OVERLAY) {
        pattern->CloseSelectOverlay();
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    insertHandle_ = insertHandle;
    startSelectionHandle_ = startSelectionHandle;
    endSelectionHandle_ = endSelectionHandle;
    if (selectTemporarilyHidden_ || selectTemporarilyHiddenByScroll_) {
        TAG_LOGD(AceLogTag::ACE_WEB, "select menu temporarily hidden");
        return;
    }
    if (!isShowHandle_) {
        if (overlayType == INSERT_OVERLAY) {
            CloseOverlay(false, CloseReason::CLOSE_REASON_CLICK_OUTSIDE);
            return;
        }
    } else {
        if (overlayType == INSERT_OVERLAY) {
            if (!selectOverlayDragging_) {
                UpdateTouchHandleForOverlay(true);
            }
        } else {
            UpdateSelectHandleInfo();
            if (!selectOverlayDragging_) {
                UpdateTouchHandleForOverlay(false);
            }
        }
    }
}

void WebSelectOverlay::RegisterSelectOverlayEvent(SelectOverlayInfo& selectInfo)
{
    selectInfo.onClick = [weak = AceType::WeakClaim(this)](const GestureEvent& info, bool isFirst) {
        auto overlay = weak.Upgrade();
        CHECK_NULL_VOID(overlay);
        overlay->OnOverlayClick(info, isFirst);
    };
}

void WebSelectOverlay::SetEditMenuOptions(SelectOverlayInfo& selectInfo)
{
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_VOID(pattern);
    if (pattern && !(pattern->onCreateMenuCallback_ && pattern->onMenuItemClick_)) {
        selectInfo.menuOptionItems = pattern->menuOptionParam_;
    }
    if (pattern && pattern->onCreateMenuCallback_ && pattern->onMenuItemClick_) {
        selectInfo.onCreateCallback.onCreateMenuCallback = pattern->onCreateMenuCallback_;
        selectInfo.onCreateCallback.onMenuItemClick = pattern->onMenuItemClick_;
        if (pattern->onPrepareMenuCallback_) {
            selectInfo.onCreateCallback.onPrepareMenuCallback = pattern->onPrepareMenuCallback_;
            selectInfo.menuInfo.hasOnPrepareMenuCallback = true;
        }
        auto textRange = [](int32_t& start, int32_t& end) {
            start = -1;
            end = -1;
        };
        selectInfo.onCreateCallback.textRangeCallback = textRange;
    }
}

bool WebSelectOverlay::IsSelectHandleReverse()
{
    if (startSelectionHandle_->GetTouchHandleType() ==
        OHOS::NWeb::NWebTouchHandleState::SELECTION_BEGIN_HANDLE &&
        endSelectionHandle_->GetTouchHandleType() ==
        OHOS::NWeb::NWebTouchHandleState::SELECTION_BEGIN_HANDLE) {
        return true;
    } else if (startSelectionHandle_->GetTouchHandleType() ==
        OHOS::NWeb::NWebTouchHandleState::SELECTION_END_HANDLE &&
        endSelectionHandle_->GetTouchHandleType() ==
        OHOS::NWeb::NWebTouchHandleState::SELECTION_END_HANDLE) {
        return true;
    }
    return false;
}

void WebSelectOverlay::UpdateSelectHandleInfo()
{
    bool needReverse = IsSelectHandleReverse();
    SelectHandleInfo handleInfo;
    if (!needReverse) {
        if (!isCurrentStartHandleDragging_) {
            handleInfo.paintRect = ComputeTouchHandleRect(startSelectionHandle_);
            CheckHandles(handleInfo, startSelectionHandle_);
            webSelectInfo_.firstHandle = handleInfo;
            UpdateFirstHandleOffset();
        } else {
            handleInfo.paintRect = ComputeTouchHandleRect(endSelectionHandle_);
            CheckHandles(handleInfo, endSelectionHandle_);
            webSelectInfo_.secondHandle = handleInfo;
            UpdateSecondHandleOffset();
        }
    } else {
        if (!isCurrentStartHandleDragging_) {
            handleInfo.paintRect = ComputeTouchHandleRect(endSelectionHandle_);
            CheckHandles(handleInfo, endSelectionHandle_);
            webSelectInfo_.firstHandle = handleInfo;
            UpdateFirstHandleOffset();
        } else {
            handleInfo.paintRect = ComputeTouchHandleRect(startSelectionHandle_);
            CheckHandles(handleInfo, startSelectionHandle_);
            webSelectInfo_.secondHandle = handleInfo;
            UpdateSecondHandleOffset();
        }
    }
}

void WebSelectOverlay::OnSelectHandleStart(const GestureEvent& event, bool isFirst)
{
}

RectF WebSelectOverlay::ChangeHandleHeight(const GestureEvent& event, bool isFirst)
{
    auto touchOffset = event.GetLocalLocation();
    auto handle = isFirst ? webSelectInfo_.firstHandle : webSelectInfo_.secondHandle;
    auto handleHeight = SELECT_HANDLE_DEFAULT_HEIGHT.ConvertToPx();
    handleHeight = std::min(static_cast<float>(handleHeight), handle.paintRect.Height());
    bool isTouchHandleCircle = isFirst ?
        LessNotEqual(touchOffset.GetY(), handle.paintRect.Top()) :
        GreatNotEqual(touchOffset.GetY(), handle.paintRect.Bottom());
    if (isFirst) {
        if (!isTouchHandleCircle) {
            handle.paintRect.SetTop(static_cast<float>(touchOffset.GetY()) - handleHeight / HALF);
        }
        handle.paintRect.SetHeight(handleHeight);
        webSelectInfo_.firstHandle = handle;
        webSelectInfo_.firstHandle.isCircleShow = false;
        UpdateFirstHandleOffset();
    } else {
        auto handleOffsetY = isTouchHandleCircle
                            ? handle.paintRect.Bottom() - handleHeight
                            : static_cast<float>(touchOffset.GetY()) - handleHeight / HALF;
        handle.paintRect.SetTop(handleOffsetY);
        handle.paintRect.SetHeight(handleHeight);
        webSelectInfo_.secondHandle = handle;
        webSelectInfo_.secondHandle.isCircleShow = false;
        UpdateSecondHandleOffset();
    }
    return handle.paintRect;
}

void WebSelectOverlay::OnMagnifierHandleMove(const RectF& handleRect, bool isFirst)
{
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->OnMagnifierHandleMove(handleRect, isFirst);
}

void WebSelectOverlay::UpdateTouchHandleForOverlay(bool fromOverlay)
{
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_VOID(pattern);
    WebOverlayType overlayType = GetTouchHandleOverlayType(insertHandle_, startSelectionHandle_, endSelectionHandle_);
    if (overlayType == INVALID_OVERLAY) {
        pattern->CloseSelectOverlay();
        return;
    }
    SelectHandleInfo firstHandleInfo;
    SelectHandleInfo secondHandleInfo;
    if (overlayType == INSERT_OVERLAY) {
        if (!fromOverlay) {
            HideMenu(true);
            webSelectInfo_.menuInfo.menuIsShow = false;
        }
        firstHandleInfo.paintRect = ComputeTouchHandleRect(insertHandle_);
        CheckHandles(firstHandleInfo, insertHandle_);
        firstHandleInfo.needLayout = true;
        webSelectInfo_.firstHandle = firstHandleInfo;
        if (SelectOverlayIsOn()) {
            UpdateFirstHandleOffset();
        } else {
            ProcessOverlay({ .animation = true });
            isShowHandle_ = true;
        }
    } else {
        if (selectTemporarilyHidden_ || selectTemporarilyHiddenByScroll_) {
            return;
        }
        firstHandleInfo.paintRect = ComputeTouchHandleRect(startSelectionHandle_);
        secondHandleInfo.paintRect = ComputeTouchHandleRect(endSelectionHandle_);
        CheckHandles(firstHandleInfo, startSelectionHandle_);
        CheckHandles(secondHandleInfo, endSelectionHandle_);
        webSelectInfo_.firstHandle = firstHandleInfo;
        webSelectInfo_.secondHandle = secondHandleInfo;
        if (firstHandleInfo.isShow || secondHandleInfo.isShow) {
            webSelectInfo_.isNewAvoid = false;
        }
        webSelectInfo_.handleReverse = false;
        if (SelectOverlayIsOn()) {
            UpdateIsSelectAll();
            UpdateAllHandlesOffset();
        } else {
            ProcessOverlay({ .animation = true });
            isShowHandle_ = true;
        }
    }
}

void WebSelectOverlay::HideMagnifier()
{
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->HideMagnifier();
}

void WebSelectOverlay::SetMenuOptions(SelectOverlayInfo& selectInfo,
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params,
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuCallback> callback)
{
    quickMenuCallback_ = callback;
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_VOID(pattern);
    auto delegate = pattern->delegate_;
    CHECK_NULL_VOID(delegate);
    auto copyOption = delegate->GetCopyOptionMode();
    uint32_t flags = static_cast<uint32_t>(params->GetEditStateFlags());
    if (!(flags & OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_CUT) ||
        copyOption == OHOS::NWeb::NWebPreference::CopyOptionMode::NONE) {
        selectInfo.menuInfo.showCut = false;
    } else {
        selectInfo.menuInfo.showCut = true;
    }
    if (!(flags & OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_COPY)) {
        selectInfo.menuInfo.showCopy = false;
    } else {
        selectInfo.menuInfo.showCopy = true;
    }
    if (!(flags & OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_PASTE)) {
        selectInfo.menuInfo.showPaste = false;
    } else {
        selectInfo.menuInfo.showPaste = true;
    }
    if (!(flags & OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_SELECT_ALL)) {
        selectInfo.menuInfo.showCopyAll = false;
    } else {
        selectInfo.menuInfo.showCopyAll = true;
    }
    bool detectFlag = !isSelectAll_;

    auto value = GetSelectedText();
    auto queryWord = std::regex_replace(value, std::regex("^\\s+|\\s+$"), "");
    if (!queryWord.empty()) {
        selectInfo.menuInfo.showSearch = true;
        selectInfo.menuInfo.showTranslate = true;
    } else {
        selectInfo.menuInfo.showSearch = false;
        selectInfo.menuInfo.showTranslate = false;
    }
    selectInfo.menuInfo.showAIWrite = !(!(flags & OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_CUT) ||
        (copyOption == OHOS::NWeb::NWebPreference::CopyOptionMode::NONE) || !pattern->IsShowAIWrite());
    // should be the last
    canShowAIMenu_ = (copyOption != OHOS::NWeb::NWebPreference::CopyOptionMode::NONE) &&
                     (copyOption != OHOS::NWeb::NWebPreference::CopyOptionMode::IN_APP);
    canShowAIMenu_ = canShowAIMenu_ && !(flags & OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_CUT);
    selectInfo.menuInfo.isAskCeliaEnabled = canShowAIMenu_;
    DetectSelectedText(detectFlag ? value : std::string());
}

void WebSelectOverlay::HideHandleAndQuickMenuIfNecessary(bool hide, bool isScroll)
{
    WebOverlayType overlayType = GetTouchHandleOverlayType(insertHandle_, startSelectionHandle_, endSelectionHandle_);
    TAG_LOGI(AceLogTag::ACE_WEB,
        "HideHandleAndQuickMenuIfNecessary hide:%{public}d, overlayType:%{public}d, isScroll:%{public}d",
        hide, overlayType, isScroll);
    if (overlayType != SELECTION_OVERLAY) {
        return;
    }
    SelectHandleInfo firstInfo;
    SelectHandleInfo secondInfo;
    if (!isScroll) {
        selectTemporarilyHidden_ = hide;
        if (selectTemporarilyHiddenByScroll_) {
            return;
        }
    }
    if (hide) {
        HideMenu(true);
        webSelectInfo_.menuInfo.menuIsShow = false;
        firstInfo.isShow = false;
        firstInfo.paintRect = ComputeTouchHandleRect(startSelectionHandle_);
        secondInfo.isShow = false;
        secondInfo.paintRect = ComputeTouchHandleRect(endSelectionHandle_);
        webSelectInfo_.firstHandle = firstInfo;
        webSelectInfo_.secondHandle = secondInfo;
        UpdateAllHandlesOffset();
    } else {
        firstInfo.paintRect = ComputeTouchHandleRect(startSelectionHandle_);
        secondInfo.paintRect = ComputeTouchHandleRect(endSelectionHandle_);
        CheckHandles(firstInfo, startSelectionHandle_);
        CheckHandles(secondInfo, endSelectionHandle_);
        webSelectInfo_.firstHandle = firstInfo;
        webSelectInfo_.secondHandle = secondInfo;
        if (firstInfo.isShow || secondInfo.isShow) {
            ShowMenu();
            webSelectInfo_.menuInfo.menuIsShow = true;
            webSelectInfo_.isNewAvoid = false;
        } else if (dropParams_) {
            bool isNewAvoid = false;
            auto selectArea = ComputeClippedSelectionBounds(
                dropParams_, startSelectionHandle_, endSelectionHandle_, isNewAvoid);
            webSelectInfo_.isNewAvoid = false;
            webSelectInfo_.selectArea = selectArea;
        }
        UpdateAllHandlesOffset();
    }
}

void WebSelectOverlay::OnParentScrollStartOrEndCallback(bool isEnd)
{
    if (webSelectInfo_.isSingleHandle && !isEnd)  {
        webSelectInfo_.menuInfo.menuIsShow = false;
        return;
    }
    selectTemporarilyHiddenByScroll_ = !isEnd;
    if (selectTemporarilyHidden_) {
        return;
    }
    HideHandleAndQuickMenuIfNecessary(selectTemporarilyHiddenByScroll_, true);
}

void WebSelectOverlay::StopListenSelectOverlayParentScroll(const RefPtr<FrameNode>& host)
{
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto manager = context->GetSelectOverlayManager();
    CHECK_NULL_VOID(manager);
    manager->RemoveScrollCallback(host->GetId());
}

void WebSelectOverlay::RegisterSelectOverlayParentScrollCallback(int32_t parentId, int32_t callbackId)
{
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto manager = context->GetSelectOverlayManager();
    CHECK_NULL_VOID(manager);
    auto scrollCallback = [weak = WeakClaim(this)](Axis axis, float offset, int32_t source) {
        auto client = weak.Upgrade();
        CHECK_NULL_VOID(client);
        if (source == SCROLL_FROM_START) {
            client->OnParentScrollStartOrEndCallback(false);
        } else if (source == -1) {
            client->OnParentScrollStartOrEndCallback(true);
        }
    };
    manager->RegisterScrollCallback(parentId, callbackId, scrollCallback);
}

void WebSelectOverlay::StartListenSelectOverlayParentScroll(const RefPtr<FrameNode>& host)
{
    if (!scrollableParentInfo_.hasParent) {
        TAG_LOGI(AceLogTag::ACE_WEB, "has no scrollable parent");
        return;
    }
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto hostId = host->GetId();
    if (!scrollableParentInfo_.parentIds.empty()) {
        for (const auto& scrollId : scrollableParentInfo_.parentIds) {
            RegisterSelectOverlayParentScrollCallback(scrollId, hostId);
        }
        return;
    }
    auto parent = host->GetParent();
    while (parent && parent->GetTag() != V2::PAGE_ETS_TAG) {
        auto parentNode = AceType::DynamicCast<FrameNode>(parent);
        if (parentNode) {
            auto pattern = parentNode->GetPattern<ScrollablePattern>();
            if (pattern) {
                scrollableParentInfo_.parentIds.emplace_back(parentNode->GetId());
                RegisterSelectOverlayParentScrollCallback(parentNode->GetId(), hostId);
            }
        }
        parent = parent->GetParent();
    }
    scrollableParentInfo_.hasParent = !scrollableParentInfo_.parentIds.empty();
    TAG_LOGI(AceLogTag::ACE_WEB, "find scrollable parent %{public}d", scrollableParentInfo_.hasParent);
}

void WebSelectOverlay::UpdateRunQuickMenuSelectInfo(SelectOverlayInfo& selectInfo,
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params,
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> insertTouchHandle,
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> beginTouchHandle,
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endTouchHandle)
{
    selectInfo.hitTestMode = HitTestMode::HTMDEFAULT;
    isQuickMenuMouseTrigger_ = false;
    auto pattern = GetPattern<WebPattern>();
    if (selectInfo.isSingleHandle) {
        selectInfo.firstHandle.paintRect = ComputeTouchHandleRect(insertTouchHandle);
        CheckHandles(selectInfo.firstHandle, insertTouchHandle);
        selectInfo.secondHandle.isShow = false;
        if (!selectInfo.firstHandle .isShow) {
            selectInfo.isNewAvoid = true;
        }
    } else {
        selectInfo.firstHandle.paintRect = ComputeTouchHandleRect(beginTouchHandle);
        selectInfo.secondHandle.paintRect = ComputeTouchHandleRect(endTouchHandle);
        CheckHandles(selectInfo.firstHandle, beginTouchHandle);
        CheckHandles(selectInfo.secondHandle, endTouchHandle);
        QuickMenuIsNeedNewAvoid(selectInfo, params, beginTouchHandle, endTouchHandle);
        if (pattern && !(pattern->onCreateMenuCallback_ && pattern->onMenuItemClick_)) {
            selectInfo.menuOptionItems = pattern->menuOptionParam_;
        }
    }
    selectInfo.menuInfo.menuIsShow = true;
    selectInfo.handleReverse = false;
    if (pattern && pattern->onCreateMenuCallback_ && pattern->onMenuItemClick_) {
        selectInfo.onCreateCallback.onCreateMenuCallback = pattern->onCreateMenuCallback_;
        selectInfo.onCreateCallback.onMenuItemClick = pattern->onMenuItemClick_;
        if (pattern->onPrepareMenuCallback_) {
            selectInfo.onCreateCallback.onPrepareMenuCallback = pattern->onPrepareMenuCallback_;
            selectInfo.menuInfo.hasOnPrepareMenuCallback = true;
        }
        auto textRange = [](int32_t& start, int32_t& end) {
            start = -1;
            end = -1;
        };
        selectInfo.onCreateCallback.textRangeCallback = textRange;
    }
}

void WebSelectOverlay::QuickMenuIsNeedNewAvoid(
    SelectOverlayInfo& selectInfo,
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params,
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> startHandle,
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endHandle)
{
    isQuickMenuMouseTrigger_ = false;
    if (!selectInfo.firstHandle.isShow && !selectInfo.secondHandle.isShow) {
        selectInfo.isNewAvoid = true;
        if ((startHandle->GetEdgeHeight() == 0 && startHandle->GetTouchHandleId() == -1) &&
            (endHandle->GetEdgeHeight() == 0 && endHandle->GetTouchHandleId() == -1)) {
            isQuickMenuMouseTrigger_ = true;
            selectInfo.selectArea = ComputeMouseClippedSelectionBounds(
                params->GetSelectX(), params->GetSelectY(), params->GetSelectWidth(), params->GetSelectXHeight());
        } else {
            selectInfo.selectArea =
                ComputeClippedSelectionBounds(params, startHandle, endHandle, selectInfo.isNewAvoid);
        }
    } else {
        float selectX = params->GetSelectX();
        float selectY = params->GetSelectY();
        float selectWidth = params->GetSelectWidth();
        float selectHeight = params->GetSelectXHeight();
        selectInfo.selectArea = RectF(selectX, selectY, selectWidth, selectHeight);
    }
}

RectF WebSelectOverlay::ComputeClippedSelectionBounds(
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params,
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> startHandle,
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endHandle, bool& isNewAvoid)
{
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_RETURN(pattern, RectF());
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, RectF());
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, RectF());
    float selectX = params->GetSelectX();
    float selectY = params->GetSelectY();
    float selectWidth = params->GetSelectWidth();
    float selectHeight = params->GetSelectXHeight();
    float viewPortX = static_cast<float>((startHandle->GetViewPortX() + endHandle->GetViewPortX())) / 2;
    float viewPortY = static_cast<float>((startHandle->GetViewPortY() + endHandle->GetViewPortY())) / 2;
    auto offset = pattern->GetCoordinatePoint().value_or(OffsetF());
    RectF visibleRect;
    RectF visibleInnerRect;
    RectF frameRect;
    host->GetVisibleRectWithClip(visibleRect, visibleInnerRect, frameRect);
    auto visibleTop = visibleInnerRect.Top();
    auto visibleBottom = GetBottomWithKeyboard(visibleInnerRect.Bottom());
    isNewAvoid = true;
    if (LessOrEqual(visibleBottom, selectY + viewPortY + offset.GetY()) ||
        LessOrEqual(selectY + selectHeight + offset.GetY(), visibleTop)) {
        isNewAvoid = false;
        return RectF();
    } else if (LessOrEqual(selectY + offset.GetY(), visibleTop) &&
        LessOrEqual(visibleBottom, selectY + viewPortY + selectHeight + offset.GetY())) {
        return RectF(offset.GetX(), offset.GetY(), pattern->drawSize_.Width(), pattern->drawSize_.Height());
    }
    auto theme = pipeline->GetTheme<TextOverlayTheme>();
    float radius = theme ? theme->GetHandleHotZoneRadius().ConvertToPx() : 0.0;
    if (LessOrEqual(visibleBottom, selectY + viewPortY + startHandle->GetEdgeHeight() + offset.GetY())) {
        selectX = startHandle->GetX() + offset.GetX();
        selectY = startHandle->GetY() + offset.GetY() - radius - startHandle->GetEdgeHeight() - SELECT_MENE_HEIGHT;
        selectWidth = SelectHandleInfo::GetDefaultLineWidth().ConvertToPx();
    } else if (LessOrEqual(selectY + selectHeight - endHandle->GetEdgeHeight() + offset.GetY(), visibleTop)) {
        selectX = endHandle->GetX() + offset.GetX();
        selectY = endHandle->GetY() + offset.GetY() + radius;
        selectWidth = SelectHandleInfo::GetDefaultLineWidth().ConvertToPx();
    } else {
        selectX = selectX + viewPortX + offset.GetX();
        selectY = selectY + viewPortY + offset.GetY() - SELECT_MENE_HEIGHT - radius;
        if (selectY < offset.GetY())
            selectY = offset.GetY();
    }
    return RectF(selectX, selectY, selectWidth, SELECT_MENE_HEIGHT);
}

RectF WebSelectOverlay::ComputeMouseClippedSelectionBounds(int32_t x, int32_t y, int32_t w, int32_t h)
{
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_RETURN(pattern, RectF());
    auto offset = pattern->GetCoordinatePoint().value_or(OffsetF());
    float selectX = offset.GetX() + x;
    float selectY = offset.GetY();
    float selectWidth = w;
    float selectHeight = h;
    if (LessOrEqual(pattern->GetHostFrameSize().value_or(SizeF()).Height(), y)) {
        selectY += pattern->GetHostFrameSize().value_or(SizeF()).Height();
    } else if (y + h <= 0) {
        selectY -= h;
    } else {
        selectY += y;
    }
    return RectF(selectX, selectY, selectWidth, selectHeight);
}

void WebSelectOverlay::CheckHandles(SelectHandleInfo& handleInfo,
    const std::shared_ptr<OHOS::NWeb::NWebTouchHandleState>& handle)
{
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(handle);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    int y = static_cast<int32_t>(handle->GetY() / pipeline->GetDipScale());
    int edgeHeight = static_cast<int32_t>(handle->GetEdgeHeight() / pipeline->GetDipScale()) - 1;
    if (handle->GetAlpha() <= 0 || y < edgeHeight) {
        handleInfo.isShow = false;
        return;
    }
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    float viewPortY = handle->GetViewPortY();
    RectF visibleRect;
    RectF visibleInnerRect;
    RectF frameRect;
    host->GetVisibleRectWithClip(visibleRect, visibleInnerRect, frameRect);
    visibleInnerRect.SetRect(visibleInnerRect.GetX(), visibleInnerRect.GetY() + viewPortY - 1,
        visibleInnerRect.Width(), visibleInnerRect.Height() - viewPortY + 1);
    auto paintRect = handleInfo.paintRect;
    PointF bottomPoint = { paintRect.Left(), paintRect.Bottom() };
    PointF topPoint = { paintRect.Left(), paintRect.Top() };
    handleInfo.isShow = (visibleInnerRect.IsInRegion(bottomPoint) && visibleInnerRect.IsInRegion(topPoint));
}

RectF WebSelectOverlay::ComputeTouchHandleRect(std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> touchHandle)
{
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_RETURN(pattern, RectF());
    CHECK_NULL_RETURN(touchHandle, RectF());
    RectF paintRect;
    auto offset = pattern->GetCoordinatePoint().value_or(OffsetF());
    auto size = pattern->GetHostFrameSize().value_or(SizeF());
    float edgeHeight = touchHandle->GetEdgeHeight();
    float x = touchHandle->GetX();
    float y = touchHandle->GetY();
    if (x > size.Width()) {
        x = offset.GetX() + size.Width();
    } else {
        x = x + offset.GetX();
    }

    if (y < 0) {
        y = offset.GetY();
    } else if (y > size.Height()) {
        y = offset.GetY() + size.Height();
    } else {
        float diff = 0;
        auto pipeline = PipelineBase::GetCurrentContext();
        if (pipeline) {
            auto dipScale = pipeline->GetDipScale();
            if (dipScale != 0) {
                diff = edgeHeight - static_cast<int32_t>(static_cast<int32_t>(edgeHeight / dipScale) * dipScale);
            }
        }
        y = y + offset.GetY() - edgeHeight + diff;
    }

    paintRect.SetOffset({ x, y });
    paintRect.SetSize({ SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(), edgeHeight });
    return paintRect;
}

WebOverlayType WebSelectOverlay::GetTouchHandleOverlayType(
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> insertHandle,
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> startSelectionHandle,
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endSelectionHandle)
{
    if (IsTouchHandleValid(insertHandle) && !IsTouchHandleValid(startSelectionHandle) &&
        !IsTouchHandleValid(endSelectionHandle)) {
        return INSERT_OVERLAY;
    }

    if (!IsTouchHandleValid(insertHandle) && IsTouchHandleValid(startSelectionHandle) &&
        IsTouchHandleValid(endSelectionHandle)) {
        return SELECTION_OVERLAY;
    }

    return INVALID_OVERLAY;
}

void WebSelectOverlay::RegisterSelectOverLayOnClose(SelectOverlayInfo& selectInfo)
{
    selectInfo.onClose = [weak = AceType::WeakClaim(this)] (bool isGlobalTouchEvent) {
        if (!isGlobalTouchEvent) {
            return;
        }
        TAG_LOGI(AceLogTag::ACE_WEB, "globalTouchEvent, close web select overLayer.");
        auto selectOverlay = weak.Upgrade();
        CHECK_NULL_VOID(selectOverlay);
        selectOverlay->CloseOverlay(false, CloseReason::CLOSE_REASON_CLICK_OUTSIDE);
        selectOverlay->SelectCancel();
    };
}

void WebSelectOverlay::SelectCancel()
{
    CHECK_NULL_VOID(quickMenuCallback_);
    quickMenuCallback_->Cancel();
    isSelectAll_ = false;
    insertHandle_ = nullptr;
    startSelectionHandle_ = nullptr;
    endSelectionHandle_ = nullptr;
    quickMenuCallback_ = nullptr;
}

void WebSelectOverlay::UpdateClippedSelectionBounds(int32_t x, int32_t y, int32_t w, int32_t h)
{
    webSelectInfo_.selectArea = ComputeMouseClippedSelectionBounds(x, y, w, h);
}

void WebSelectOverlay::ChangeVisibilityOfQuickMenu()
{
    WebOverlayType overlayType = GetTouchHandleOverlayType(insertHandle_, startSelectionHandle_, endSelectionHandle_);
    if (overlayType == SELECTION_OVERLAY && !selectTemporarilyHidden_ && !selectTemporarilyHiddenByScroll_) {
        bool isMenuShow = IsShowMenu();
        if (isMenuShow) {
            HideMenu(true);
            SetMenuIsShow(false);
            webSelectInfo_.menuInfo.menuIsShow = false;
        } else {
            ShowMenu();
            SetMenuIsShow(true);
            webSelectInfo_.menuInfo.menuIsShow = true;
        }
        TAG_LOGI(AceLogTag::ACE_WEB, "Current menu display status is %{public}d.", isMenuShow);
    }
}

bool WebSelectOverlay::PreProcessOverlay(const OverlayRequest& request)
{
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_RETURN(pattern, false);
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipeline, false);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, false);
    SetEnableHandleLevel(true);
    SetEnableSubWindowMenu(true);
    SetMenuTranslateIsSupport(true);
    SetIsSupportMenuSearch(true);
    CheckEnableContainerModal();
    pipeline->AddOnAreaChangeNode(host->GetId());
    return true;
}

bool WebSelectOverlay::CheckHandleVisible(const RectF& paintRect)
{
    return true;
}

std::optional<SelectHandleInfo> WebSelectOverlay::GetFirstHandleInfo()
{
    if (webSelectInfo_.secondHandle.paintRect.IsEmpty() && !webSelectInfo_.secondHandle.isShow) {
        webSelectInfo_.handleReverse = false;
        needResetHandleReverse_ = true;
    }
    return webSelectInfo_.firstHandle;
}

std::optional<SelectHandleInfo> WebSelectOverlay::GetSecondHandleInfo()
{
    return webSelectInfo_.secondHandle;
}

void WebSelectOverlay::OnUpdateMenuInfo(SelectMenuInfo& menuInfo, SelectOverlayDirtyFlag dirtyFlag)
{
    menuInfo = webSelectInfo_.menuInfo;
}

RectF WebSelectOverlay::GetSelectArea()
{
    return webSelectInfo_.selectArea;
}

std::string WebSelectOverlay::GetSelectedText()
{
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_RETURN(pattern, "");
    return pattern->GetSelectInfo();
}

bool WebSelectOverlay::IsTouchHandleValid(std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> handle)
{
    return (handle != nullptr) && (handle->IsEnable());
}

void WebSelectOverlay::OnMenuItemAction(OptionMenuActionId id, OptionMenuType type)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "OnMenuItemAction menu option id %{public}d", id);
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_VOID(pattern);
    if (id == OptionMenuActionId::PASTE || id == OptionMenuActionId::CUT) {
        isSelectAll_ = false;
    }
    if (!quickMenuCallback_) {
        TAG_LOGE(AceLogTag::ACE_WEB, "OnMenuItemAction failed callback is null");
        pattern->CloseSelectOverlay();
        return;
    }
    switch (id) {
        case OptionMenuActionId::COPY:
            quickMenuCallback_->Continue(
                OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_COPY, OHOS::NWeb::MenuEventFlags::EF_LEFT_MOUSE_BUTTON);
            ChangeVisibilityOfQuickMenu();
            break;
        case OptionMenuActionId::CUT:
            quickMenuCallback_->Continue(
                OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_CUT, OHOS::NWeb::MenuEventFlags::EF_LEFT_MOUSE_BUTTON);
            pattern->CloseSelectOverlay();
            break;
        case OptionMenuActionId::PASTE:
            quickMenuCallback_->Continue(
                OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_PASTE, OHOS::NWeb::MenuEventFlags::EF_LEFT_MOUSE_BUTTON);
            pattern->CloseSelectOverlay();
            break;
        case OptionMenuActionId::SELECT_ALL:
            quickMenuCallback_->Continue(OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_SELECT_ALL,
                OHOS::NWeb::MenuEventFlags::EF_LEFT_MOUSE_BUTTON);
            isSelectAll_ = true;
            break;
        case OptionMenuActionId::TRANSLATE:
            HandleOnTranslate();
            pattern->CloseSelectOverlay();
            SelectCancel();
            break;
        case OptionMenuActionId::SEARCH:
            HandleOnSearch();
            pattern->CloseSelectOverlay();
            SelectCancel();
            break;
        case OptionMenuActionId::AI_WRITE:
            pattern->GetHandleInfo(webSelectInfo_);
            pattern->HandleOnAIWrite();
            SelectCancel();
            break;
        case OptionMenuActionId::DISAPPEAR:
            pattern->CloseSelectOverlay();
            SelectCancel();
            break;
        case OptionMenuActionId::AI_MENU_OPTION:
            if (auto adapter = pattern->webDataDetectorAdapter_) {
                adapter->OnClickAISelectMenuOption(aiMenuType_, aiMenucontent_);
            }
            pattern->CloseSelectOverlay();
            SelectCancel();
            break;
        case OptionMenuActionId::ASK_CELIA:
            HandleOnAskCelia();
            break;
        default:
            break;
    }
}

void WebSelectOverlay::HandleOnAskCelia()
{
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_VOID(pattern);
    auto vectorStringFunc = pattern->textDetectResult_.menuOptionAndAction.find(ASK_CELIA_TAG);
    if (vectorStringFunc == pattern->textDetectResult_.menuOptionAndAction.end() || vectorStringFunc->second.empty()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "HandleOnAskCelia failed no askCelia option.");
    } else {
        auto funcVariant = vectorStringFunc->second.begin()->second;
        if (std::holds_alternative<std::function<void(int, std::string)>>(funcVariant)) {
            auto func = std::get<std::function<void(int, std::string)>>(funcVariant);
            if (func) {
                TAG_LOGI(AceLogTag::ACE_WEB, "HandleOnAskCelia execute.");
                func(true, GetSelectedText());
            } else {
                TAG_LOGE(AceLogTag::ACE_WEB, "HandleOnAskCelia failed option is null.");
            }
        } else {
            TAG_LOGE(AceLogTag::ACE_WEB, "HandleOnAskCelia failed option type error.");
        }
    }
    pattern->CloseSelectOverlay();
    SelectCancel();
    return;
}

void WebSelectOverlay::OnMenuItemAction(OptionMenuActionId id, OptionMenuType type, const std::string& labelInfo)
{
    OnMenuItemAction(id, type);
}

void WebSelectOverlay::OnHandleMove(const RectF& handleRect, bool isFirst)
{
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_VOID(pattern);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(manager);
    if (pattern->isDragging_ || manager->IsDragged()) {
        return;
    }
    TouchInfo touchPoint;
    touchPoint.id = 0;
    touchPoint.x = handleRect.GetX() - pattern->webOffset_.GetX();
    touchPoint.y = handleRect.GetY() - pattern->webOffset_.GetY() + handleRect.Height() / HALF;
    if (pattern->IsOverlayCreating()) {
        pattern->UpdateImageOverlayTouchInfo(touchPoint.x, touchPoint.y, TouchType::MOVE);
    } else {
        std::vector<std::shared_ptr<OHOS::NWeb::NWebTouchPointInfo>> touch_point_infos;
        std::shared_ptr<OHOS::NWeb::NWebTouchPointInfo> touch_point_info =
            std::make_shared<NWebTouchPointInfoImpl>(touchPoint.id, touchPoint.x, touchPoint.y);
        touch_point_infos.emplace_back(touch_point_info);
        pattern->delegate_->HandleTouchMove(touch_point_infos, true);
    }
    OnMagnifierHandleMove(handleRect, isFirst);
}

void WebSelectOverlay::OnHandleMoveStart(const GestureEvent& event, bool isFirst)
{
    selectOverlayDragging_ = true;
    isCurrentStartHandleDragging_ = isFirst;
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_VOID(pattern);
    auto delegate = pattern->delegate_;
    CHECK_NULL_VOID(delegate);
    RectF handleRect = ChangeHandleHeight(event, isFirst);
    TouchInfo touchPoint;
    touchPoint.id = 0;
    touchPoint.x = handleRect.GetX() - pattern->webOffset_.GetX();
    touchPoint.y = handleRect.GetY() - pattern->webOffset_.GetY() + handleRect.Height() / HALF;
    pattern->PushOverlayInfo(touchPoint.x, touchPoint.y, touchPoint.id);
    delegate->HandleTouchDown(touchPoint.id, touchPoint.x, touchPoint.y, true);
    if (pattern->IsOverlayCreating()) {
        pattern->UpdateImageOverlayTouchInfo(touchPoint.x, touchPoint.y, TouchType::DOWN);
    }
    aiMenuType_ = TextDataDetectType::INVALID;
    webSelectInfo_.menuInfo.aiMenuOptionType = aiMenuType_;
    webSelectInfo_.menuInfo.isAskCeliaEnabled = canShowAIMenu_;
    pattern->WebOverlayRequestFocus();
}

void WebSelectOverlay::OnHandleMoveDone(const RectF& rect, bool isFirst)
{
    HideMagnifier();
    isSelectAll_ = false;
    selectOverlayDragging_ = false;
    webSelectInfo_.menuInfo.showCopyAll = true;
    UpdateSelectMenuOptions();
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_VOID(pattern);
    auto delegate = pattern->delegate_;
    CHECK_NULL_VOID(delegate);
    DetectSelectedText(GetSelectedText());
    TouchInfo touchPoint;
    touchPoint.id = 0;
    touchPoint.x = rect.GetX() - pattern->webOffset_.GetX();
    touchPoint.y = rect.GetY() - pattern->webOffset_.GetY() + rect.Height() / HALF;
    pattern->DelTouchOverlayInfoByTouchId(touchPoint.id);
    if (!pattern->IsOverlayCreating()) {
        delegate->HandleTouchUp(touchPoint.id, touchPoint.x, touchPoint.y, true);
    } else if (pattern->imageAnalyzerManager_) {
        pattern->UpdateImageOverlayTouchInfo(touchPoint.x, touchPoint.y, TouchType::UP);
        pattern->SetOverlayCreating(false);
        delegate->HandleTouchCancel();
    }
    UpdateTouchHandleForOverlay(true);
    if (!IsShowMenu()) {
        ChangeVisibilityOfQuickMenu();
    }
    if (startSelectionHandle_ && endSelectionHandle_) {
        auto offset = pattern->GetCoordinatePoint().value_or(OffsetF());
        auto size = pattern->GetHostFrameSize().value_or(SizeF());
        TAG_LOGI(AceLogTag::ACE_WEB, "OnSelectHandleDone offset(%{public}f,%{public}f) size(%{public}f,%{public}f)"
            "start(%{public}d,%{public}d) end(%{public}d,%{public}d)", offset.GetX(), offset.GetY(),
            size.Width(), size.Height(), startSelectionHandle_->GetX(), startSelectionHandle_->GetY(),
            endSelectionHandle_->GetX(), endSelectionHandle_->GetY());
    }
    WebOverlayType overlayType = GetTouchHandleOverlayType(insertHandle_, startSelectionHandle_, endSelectionHandle_);
    if (overlayType == SELECTION_OVERLAY && !pattern->IsSelectInfoValid()) {
        TAG_LOGI(AceLogTag::ACE_WEB, "Close handles and menu.");
        pattern->CloseSelectOverlay();
        SelectCancel();
    }
    UpdateSingleHandleVisible(true);
}

void WebSelectOverlay::OnCloseOverlay(OptionMenuType menuType, CloseReason reason, RefPtr<OverlayInfo> info)
{
    selectOverlayDragging_ = false;
    selectTemporarilyHidden_ = false;
    selectTemporarilyHiddenByScroll_ = false;
    isShowHandle_ = false;
    if (CloseReason::CLOSE_REASON_BACK_PRESSED == reason) {
        SelectCancel();
    }
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    aiMenuType_ = TextDataDetectType::INVALID;
    webSelectInfo_.menuInfo.aiMenuOptionType = aiMenuType_;
    webSelectInfo_.menuInfo.isAskCeliaEnabled = canShowAIMenu_;
    StopListenSelectOverlayParentScroll(host);
    SetTouchHandleExistState(false);
}

void WebSelectOverlay::AfterCloseOverlay()
{
    selectOverlayDragging_ = false;
    isShowHandle_ = false;
}

void WebSelectOverlay::OnOverlayClick(const GestureEvent& event, bool isClickCaret)
{
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    auto delegate = pattern->delegate_;
    CHECK_NULL_VOID(delegate);
    if (!focusHub->IsFocusable() || event.GetSourceDevice() == SourceType::MOUSE) {
        return;
    }
    if (selectOverlayDragging_) {
        TAG_LOGI(AceLogTag::ACE_WEB, "HandleTouchClickEvent fail when handle dragging.");
        return;
    }
    if (!IsTouchHandleValid(insertHandle_)) {
        return;
    }
    auto globalLocation = event.GetGlobalLocation();
    TouchInfo touchPoint;
    touchPoint.id = 0;
    touchPoint.x = globalLocation.GetX() - pattern->webOffset_.GetX();
    touchPoint.y = globalLocation.GetY() - pattern->webOffset_.GetY();
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_VOID(theme);
    float hotZone = theme->GetHandleHotZoneRadius().ConvertToPx();
    RectF edgeRect(insertHandle_->GetX() - hotZone / HALF,
                   insertHandle_->GetY() - insertHandle_->GetEdgeHeight(),
                   hotZone,
                   insertHandle_->GetEdgeHeight());
    bool isInRegion = edgeRect.IsInRegion({touchPoint.x, touchPoint.y});
    TAG_LOGI(AceLogTag::ACE_WEB, "point.x:%{public}f. y:%{public}f, isInRegion:%{public}d",
        touchPoint.x, touchPoint.y, isInRegion);
    TAG_LOGI(AceLogTag::ACE_WEB, "edgeRect:%{public}s", edgeRect.ToString().c_str());
    delegate->HandleTouchDown(touchPoint.id, touchPoint.x, touchPoint.y, !isInRegion);
    delegate->HandleTouchUp(touchPoint.id, touchPoint.x, touchPoint.y, !isInRegion);
}

bool WebSelectOverlay::CheckTouchInHostNode(const PointF& touchPoint)
{
    return true;
}

void WebSelectOverlay::OnHandleReverse(bool isReverse)
{
    if (isReverse && needResetHandleReverse_) {
        TAG_LOGI(AceLogTag::ACE_WEB, "WebSelectOverlay should reset handleReverse.");
        auto manager = GetManager<SelectContentOverlayManager>();
        CHECK_NULL_VOID(manager);
        manager->MarkInfoChange(DIRTY_DOUBLE_HANDLE);
    } else {
        needResetHandleReverse_ = false;
    }
}

void WebSelectOverlay::OnHandleGlobalTouchEvent(SourceType sourceType, TouchType touchType, bool touchInside)
{
    if (EventInfoConvertor::MatchCompatibleCondition() && IsMouseClickDown(sourceType, touchType)) {
        return;
    }
    if (IsMouseClickDown(sourceType, touchType) || IsTouchUp(sourceType, touchType)) {
        CloseOverlay(false, CloseReason::CLOSE_REASON_CLICK_OUTSIDE);
        SelectCancel();
    }
}

void WebSelectOverlay::OnUpdateSelectOverlayInfo(SelectOverlayInfo &selectInfo, int32_t requestCode)
{
    selectInfo.isNewAvoid = webSelectInfo_.isNewAvoid;
    selectInfo.isSingleHandle = webSelectInfo_.isSingleHandle;
    selectInfo.menuOptionItems = webSelectInfo_.menuOptionItems;
    selectInfo.handleReverse = webSelectInfo_.handleReverse;
    selectInfo.hitTestMode = webSelectInfo_.hitTestMode;
    selectInfo.onCreateCallback = webSelectInfo_.onCreateCallback;
    selectInfo.onClose = webSelectInfo_.onClose;
    selectInfo.onClick = webSelectInfo_.onClick;
    selectInfo.enableHandleLevel = true;
    selectInfo.enableSubWindowMenu = true;
    selectInfo.computeMenuOffset = webSelectInfo_.computeMenuOffset;
}

void WebSelectOverlay::OnHandleMarkInfoChange(
    const std::shared_ptr<SelectOverlayInfo> info, SelectOverlayDirtyFlag flag)
{
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    if ((flag & DIRTY_HANDLE_COLOR_FLAG) == DIRTY_HANDLE_COLOR_FLAG) {
        info->handlerColor = GetHandleColor();
        manager->MarkHandleDirtyNode(PROPERTY_UPDATE_RENDER);
    }
    if ((flag & DIRTY_FIRST_HANDLE) == DIRTY_FIRST_HANDLE || (flag & DIRTY_SECOND_HANDLE) == DIRTY_SECOND_HANDLE) {
        if (info->menuInfo.showShare != (IsSupportMenuShare() && AllowShare() && IsNeedMenuShare())) {
            info->menuInfo.showShare = !info->menuInfo.showShare;
            manager->NotifyUpdateToolBar(true);
        }
        if (info->menuInfo.aiMenuOptionType != aiMenuType_) {
            TAG_LOGI(AceLogTag::ACE_WEB, "WebSelectOverlay::OnHandleMarkInfoChange aiMenuOptionType change.");
            info->menuInfo.aiMenuOptionType = aiMenuType_;
            info->menuInfo.isAskCeliaEnabled = canShowAIMenu_ && (aiMenuType_ == TextDataDetectType::INVALID);
            manager->NotifyUpdateToolBar(true);
        }
    }
    if ((flag & DIRTY_DOUBLE_HANDLE) == DIRTY_DOUBLE_HANDLE) {
        if (needResetHandleReverse_) {
            TAG_LOGI(AceLogTag::ACE_WEB, "WebSelectOverlay OnHandleMarkInfoChange reset handleReverse.");
            info->handleReverse = webSelectInfo_.handleReverse;
            manager->MarkHandleDirtyNode(PROPERTY_UPDATE_RENDER);
            needResetHandleReverse_ = false;
        }
    }
}

void WebSelectOverlay::OnAfterSelectOverlayShow(bool isCreated)
{
    if (needResetHandleReverse_) {
        OnHandleReverse(true);
        needResetHandleReverse_ = false;
    }
}

void WebSelectOverlay::UpdateSelectMenuOptions()
{
    auto value = GetSelectedText();
    auto queryWord = std::regex_replace(value, std::regex("^\\s+|\\s+$"), "");
    if (isSelectAll_) {
        isSelectAll_ = false;
    }
    if (!queryWord.empty()) {
        webSelectInfo_.menuInfo.showSearch = true;
        webSelectInfo_.menuInfo.showTranslate = true;
    } else {
        webSelectInfo_.menuInfo.showSearch = false;
        webSelectInfo_.menuInfo.showTranslate = false;
    }
    TAG_LOGI(AceLogTag::ACE_WEB, "WebSelectInfo MenuInfo ShowSearch is %{public}d", webSelectInfo_.menuInfo.showSearch);
    TAG_LOGI(AceLogTag::ACE_WEB, "WebSelectInfo MenuInfo ShowTranslate is %{public}d",
        webSelectInfo_.menuInfo.showTranslate);
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    manager->MarkInfoChange(DIRTY_ALL_MENU_ITEM);
}

void WebSelectOverlay::DetectSelectedText(const std::string& text)
{
    if (!canShowAIMenu_) {
        return;
    }
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_VOID(pattern);
    auto adapter = pattern->webDataDetectorAdapter_;
    CHECK_NULL_VOID(adapter);
    aiMenuType_ = TextDataDetectType::INVALID;
    webSelectInfo_.menuInfo.aiMenuOptionType = aiMenuType_;
    adapter->DetectSelectedText(text);
}

void WebSelectOverlay::UpdateAISelectMenu(TextDataDetectType type, const std::string& content)
{
    TAG_LOGI(
        AceLogTag::ACE_WEB, "WebDataDetectorAdapter::UpdateAISelectMenu type: %{public}d", static_cast<int32_t>(type));
    aiMenuType_ = type;
    aiMenucontent_ = content;
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    webSelectInfo_.menuInfo.aiMenuOptionType = aiMenuType_;
    webSelectInfo_.menuInfo.isAskCeliaEnabled = canShowAIMenu_ && (aiMenuType_ == TextDataDetectType::INVALID);
    manager->MarkInfoChange(DIRTY_ALL_MENU_ITEM);
}

void WebSelectOverlay::UpdateIsSelectAll()
{
    if (isSelectAll_) {
        isSelectAll_ = false;
    }
}

void WebSelectOverlay::UpdateSingleHandleVisible(bool isVisible)
{
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_VOID(pattern);
    if (IsSingleHandle()) {
        pattern->UpdateSingleHandleVisible(isVisible);
    }
}

bool WebSelectOverlay::IsSingleHandle()
{
    WebOverlayType overlayType = GetTouchHandleOverlayType(insertHandle_, startSelectionHandle_, endSelectionHandle_);
    return overlayType == INSERT_OVERLAY;
}

void WebSelectOverlay::OnHandleIsHidden()
{
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateSingleHandleVisible(false);
    SetTouchHandleExistState(false);
}

void WebSelectOverlay::SetTouchHandleExistState(bool touchHandleExist)
{
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetTouchHandleExistState(touchHandleExist);
}

double WebSelectOverlay::GetBottomWithKeyboard(double bottom)
{
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_RETURN(pattern, bottom);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, bottom);
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, bottom);
    auto safeAreaManager = pipeline->GetSafeAreaManager();
    CHECK_NULL_RETURN(safeAreaManager, bottom);
    auto keyboardInset = safeAreaManager->GetKeyboardWebInset();
    auto keyboardPosition =
        GreatNotEqual(static_cast<double>(keyboardInset.Length()), 0.0f) ? keyboardInset.start : bottom;
    return GreatNotEqual(keyboardPosition, bottom) ? bottom : keyboardPosition;
}

void WebSelectOverlay::SetComputeMenuOffset(SelectOverlayInfo &info)
{
    info.computeMenuOffset = [weak = AceType::WeakClaim(this)](LayoutWrapper *layoutWrapper,
                                 OffsetF &menuOffset,
                                 const RectF &menuRect,
                                 OffsetF &windowOffset,
                                 std::shared_ptr<SelectOverlayInfo> &info) {
        auto overlay = weak.Upgrade();
        CHECK_NULL_RETURN(overlay, false);
        return overlay->ComputeMenuOffset(layoutWrapper, menuOffset, menuRect, windowOffset, info);
    };
}

bool WebSelectOverlay::ComputeMenuOffset(LayoutWrapper *layoutWrapper, OffsetF &menuOffset, const RectF &menuRect,
    OffsetF &windowOffset, std::shared_ptr<SelectOverlayInfo> &info)
{
    CHECK_NULL_RETURN(info, false);
    CHECK_NULL_RETURN(layoutWrapper, false);
    if (info->isSingleHandle || info->isNewAvoid) {
        return false;
    }
    MenuAvoidStrategyMember member;
    member.layoutWrapper = layoutWrapper;
    member.windowOffset = windowOffset;
    member.menuHeight = menuRect.Height();
    member.menuWidth = menuRect.Width();
    member.info = info;
    bool initSuccess = InitMenuAvoidStrategyMember(member);
    if (initSuccess) {
        MenuAvoidStrategy(menuOffset, member);
        return true;
    } else {
        return false;
    }
}

bool WebSelectOverlay::InitMenuAvoidStrategyMember(MenuAvoidStrategyMember& member)
{
    InitStrategyTools tools;
    tools.pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(tools.pipeline, false);
    tools.theme = tools.pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_RETURN(tools.theme, false);
    tools.safeAreaManager = tools.pipeline->GetSafeAreaManager();
    CHECK_NULL_RETURN(tools.safeAreaManager, false);
    tools.geometryNode = member.layoutWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(tools.geometryNode, false);

    InitMenuAvoidStrategyAboutParam(member, tools);
    InitMenuAvoidStrategyAboutKeyboard(member, tools);
    InitMenuAvoidStrategyAboutTop(member, tools);
    InitMenuAvoidStrategyAboutBottom(member, tools);
    InitMenuAvoidStrategyAboutPosition(member, tools);

    return true;
}

void WebSelectOverlay::InitMenuAvoidStrategyAboutParam(MenuAvoidStrategyMember& member, InitStrategyTools& tools)
{
    auto& theme = tools.theme;

    member.defaultAvoidY = theme->GetDefaultMenuPositionY();
    member.avoidFromText = theme->GetMenuSpacingWithText().ConvertToPx() +
                                theme->GetHandleDiameter().ConvertToPx() +
                                theme->GetHandleDiameterStrokeWidth().ConvertToPx() / 2.0f;
}

void WebSelectOverlay::InitMenuAvoidStrategyAboutKeyboard(MenuAvoidStrategyMember& member, InitStrategyTools& tools)
{
    auto& safeAreaManager = tools.safeAreaManager;
    auto keyboardInset = safeAreaManager->GetKeyboardInset().Combine(safeAreaManager->GetKeyboardWebInset());

    member.keyboardInsetStart = static_cast<double>(keyboardInset.start);
    member.keyboardHeight = static_cast<double>(keyboardInset.Length());
    member.hasKeyboard = GreatNotEqual(keyboardInset.Length(), 0.0f);
}

void WebSelectOverlay::InitMenuAvoidStrategyAboutTop(MenuAvoidStrategyMember& member, InitStrategyTools& tools)
{
    auto& info = member.info;
    SelectHandleInfo upHandle = info->handleReverse ? info->secondHandle : info->firstHandle;
    auto topArea = static_cast<double>(tools.safeAreaManager->GetSystemSafeArea().top_.Length());
    auto rootTop = static_cast<double>(tools.pipeline->GetRootRect().Top());

    member.upPaint = upHandle.GetPaintRect() - tools.geometryNode->GetFrameOffset() + member.windowOffset;
    member.topArea = GreatNotEqual(rootTop, topArea) ? rootTop : topArea;
    member.selectionTop = upHandle.isShow ? member.upPaint.Top() : member.topArea;
}

void WebSelectOverlay::InitMenuAvoidStrategyAboutBottom(MenuAvoidStrategyMember& member, InitStrategyTools& tools)
{
    auto info = member.info;
    SelectHandleInfo downHandle = info->handleReverse ? info->firstHandle : info->secondHandle;
    auto downPaint = downHandle.GetPaintRect() - tools.geometryNode->GetFrameOffset() + member.windowOffset;
    auto handleBottom = static_cast<double>(downPaint.Bottom());
    bool hasKeyboard = member.hasKeyboard;
    auto frameHeight = tools.geometryNode->GetFrameRect().Height();
    auto keyboardStart = member.keyboardInsetStart;
    auto defaultY = member.defaultAvoidY;

    auto bottomArea = tools.safeAreaManager->GetSafeAreaWithoutProcess().bottom_.start;
    bottomArea = hasKeyboard ? keyboardStart - defaultY : bottomArea;
    bottomArea = GreatNotEqual(bottomArea, 0.0f) ? bottomArea : tools.pipeline->GetRootRect().Bottom();
    bottomArea = GreatNotEqual(bottomArea, frameHeight) ? frameHeight : bottomArea;

    auto handleIsShow = hasKeyboard ? (LessOrEqual(handleBottom, keyboardStart) ? true : false) : downHandle.isShow;
    auto selectionBottom = handleIsShow ? handleBottom : bottomArea;
    selectionBottom = NearEqual(selectionBottom, keyboardStart - defaultY) ? keyboardStart : selectionBottom;

    member.downPaint = downPaint;
    member.bottomArea = bottomArea;
    member.selectionBottom = selectionBottom;
}

void WebSelectOverlay::InitMenuAvoidStrategyAboutPosition(MenuAvoidStrategyMember& member, InitStrategyTools& tools)
{
    auto selectArea = member.info->selectArea + member.windowOffset;
    auto defaultAvoidY = member.defaultAvoidY;
    auto midPosition = (member.selectionTop + member.selectionBottom - member.menuHeight) / 2.0f;
    auto avoidPositionY = member.bottomArea - member.menuHeight;
    avoidPositionY = GreatNotEqual(midPosition, avoidPositionY) ? avoidPositionY : midPosition;

    member.avoidPositionX = (selectArea.Left() + selectArea.Right() - member.menuWidth) / 2.0f;
    member.avoidPositionY = GreatNotEqual(avoidPositionY, defaultAvoidY) ? avoidPositionY : defaultAvoidY;
}

void WebSelectOverlay::MenuAvoidStrategy(OffsetF& menuOffset, MenuAvoidStrategyMember& member)
{
    if (GreatNotEqual(menuOffset.GetY(), member.upPaint.Top())) {
        menuOffset.SetY(member.downPaint.Bottom() + member.avoidFromText);
    }
    double menuHeight = member.menuHeight;
    double menuTop = menuOffset.GetY();
    double menuBottom = menuTop + menuHeight;
    if (GreatNotEqual(menuBottom, member.bottomArea)) {
        menuOffset.SetY(member.avoidPositionY);
        menuTop = menuOffset.GetY();
        menuBottom = menuTop + menuHeight;
    }
    if (GreatNotEqual(member.upPaint.Top(), menuTop)) {
        double finalY = member.upPaint.Top() - member.avoidFromText - menuHeight;
        finalY = GreatNotEqual(menuTop, finalY) ? finalY : menuTop;
        menuOffset.SetY(finalY);
    } else if (GreatNotEqual(menuBottom, member.downPaint.Bottom())) {
        double finalY = member.downPaint.Bottom() + member.avoidFromText;
        finalY = GreatNotEqual(finalY, menuTop) ? finalY : menuTop;
        menuOffset.SetY(finalY);
    } else {
        menuOffset.SetY(member.avoidPositionY);
    }
    menuOffset.SetX(member.avoidPositionX);
}
} // namespace OHOS::Ace::NG
