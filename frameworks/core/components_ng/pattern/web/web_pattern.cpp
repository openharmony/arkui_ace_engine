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

#include "core/components_ng/pattern/web/web_pattern.h"

#include <securec.h>

#include "display_manager.h"
#include "file_uri.h"
#include "image_source.h"
#include "parameters.h"

#include "base/geometry/ng/offset_t.h"
#include "base/image/file_uri_helper.h"
#include "base/mousestyle/mouse_style.h"
#include "base/utils/date_util.h"
#include "base/utils/linear_map.h"
#include "base/utils/utils.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components/picker/picker_data.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components/web/resource/web_delegate.h"
#include "core/components/web/web_property.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/web/web_event_hub.h"
#include "core/event/key_event.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/base/utils/system_properties.h"
#include "frameworks/core/components_ng/base/ui_node.h"

#ifdef ENABLE_DRAG_FRAMEWORK
#include "base/geometry/rect.h"
#include "base/msdp/device_status/interfaces/innerkits/interaction/include/interaction_manager.h"
#include "core/common/ace_engine_ext.h"
#include "core/common/udmf/udmf_client.h"
#include "core/common/udmf/unified_data.h"
#endif

namespace OHOS::Ace::NG {
#ifdef ENABLE_DRAG_FRAMEWORK
using namespace Msdp::DeviceStatus;
#endif // ENABLE_DRAG_FRAMEWORK
namespace {
const std::string IMAGE_POINTER_CONTEXT_MENU_PATH = "etc/webview/ohos_nweb/context-menu.svg";
const std::string IMAGE_POINTER_ALIAS_PATH = "etc/webview/ohos_nweb/alias.svg";
const LinearEnumMapNode<OHOS::NWeb::CursorType, MouseFormat> g_cursorTypeMap[] = {
    { OHOS::NWeb::CursorType::CT_CROSS, MouseFormat::CROSS },
    { OHOS::NWeb::CursorType::CT_HAND, MouseFormat::HAND_POINTING },
    { OHOS::NWeb::CursorType::CT_IBEAM, MouseFormat::TEXT_CURSOR },
    { OHOS::NWeb::CursorType::CT_WAIT, MouseFormat::LOADING },
    { OHOS::NWeb::CursorType::CT_HELP, MouseFormat::HELP },
    { OHOS::NWeb::CursorType::CT_EASTRESIZE, MouseFormat::WEST_EAST },
    { OHOS::NWeb::CursorType::CT_NORTHRESIZE, MouseFormat::NORTH_SOUTH },
    { OHOS::NWeb::CursorType::CT_NORTHEASTRESIZE, MouseFormat::NORTH_EAST_SOUTH_WEST },
    { OHOS::NWeb::CursorType::CT_NORTHWESTRESIZE, MouseFormat::NORTH_WEST_SOUTH_EAST },
    { OHOS::NWeb::CursorType::CT_SOUTHRESIZE, MouseFormat::NORTH_SOUTH },
    { OHOS::NWeb::CursorType::CT_SOUTHEASTRESIZE, MouseFormat::NORTH_WEST_SOUTH_EAST },
    { OHOS::NWeb::CursorType::CT_SOUTHWESTRESIZE, MouseFormat::NORTH_EAST_SOUTH_WEST },
    { OHOS::NWeb::CursorType::CT_WESTRESIZE, MouseFormat::WEST_EAST },
    { OHOS::NWeb::CursorType::CT_NORTHSOUTHRESIZE, MouseFormat::NORTH_SOUTH },
    { OHOS::NWeb::CursorType::CT_EASTWESTRESIZE, MouseFormat::WEST_EAST },
    { OHOS::NWeb::CursorType::CT_NORTHEASTSOUTHWESTRESIZE, MouseFormat::NORTH_EAST_SOUTH_WEST },
    { OHOS::NWeb::CursorType::CT_NORTHWESTSOUTHEASTRESIZE, MouseFormat::NORTH_WEST_SOUTH_EAST },
    { OHOS::NWeb::CursorType::CT_COLUMNRESIZE, MouseFormat::RESIZE_LEFT_RIGHT },
    { OHOS::NWeb::CursorType::CT_ROWRESIZE, MouseFormat::RESIZE_UP_DOWN },
    { OHOS::NWeb::CursorType::CT_MIDDLEPANNING, MouseFormat::MIDDLE_BTN_NORTH_SOUTH_WEST_EAST },
    { OHOS::NWeb::CursorType::CT_EASTPANNING, MouseFormat::MIDDLE_BTN_EAST },
    { OHOS::NWeb::CursorType::CT_NORTHPANNING, MouseFormat::MIDDLE_BTN_NORTH },
    { OHOS::NWeb::CursorType::CT_NORTHEASTPANNING, MouseFormat::MIDDLE_BTN_NORTH_EAST },
    { OHOS::NWeb::CursorType::CT_NORTHWESTPANNING, MouseFormat::MIDDLE_BTN_NORTH_WEST },
    { OHOS::NWeb::CursorType::CT_SOUTHPANNING, MouseFormat::MIDDLE_BTN_SOUTH },
    { OHOS::NWeb::CursorType::CT_SOUTHEASTPANNING, MouseFormat::MIDDLE_BTN_SOUTH_EAST },
    { OHOS::NWeb::CursorType::CT_SOUTHWESTPANNING, MouseFormat::MIDDLE_BTN_SOUTH_WEST },
    { OHOS::NWeb::CursorType::CT_WESTPANNING, MouseFormat::MIDDLE_BTN_WEST },
    { OHOS::NWeb::CursorType::CT_MOVE, MouseFormat::CURSOR_MOVE },
    { OHOS::NWeb::CursorType::CT_VERTICALTEXT, MouseFormat::HORIZONTAL_TEXT_CURSOR },
    { OHOS::NWeb::CursorType::CT_CELL, MouseFormat::CURSOR_CROSS },
    { OHOS::NWeb::CursorType::CT_PROGRESS, MouseFormat::RUNNING },
    { OHOS::NWeb::CursorType::CT_NODROP, MouseFormat::CURSOR_FORBID },
    { OHOS::NWeb::CursorType::CT_COPY, MouseFormat::CURSOR_COPY },
    { OHOS::NWeb::CursorType::CT_NONE, MouseFormat::CURSOR_NONE },
    { OHOS::NWeb::CursorType::CT_NOTALLOWED, MouseFormat::CURSOR_FORBID },
    { OHOS::NWeb::CursorType::CT_ZOOMIN, MouseFormat::ZOOM_IN },
    { OHOS::NWeb::CursorType::CT_ZOOMOUT, MouseFormat::ZOOM_OUT },
    { OHOS::NWeb::CursorType::CT_GRAB, MouseFormat::HAND_OPEN },
    { OHOS::NWeb::CursorType::CT_GRABBING, MouseFormat::HAND_GRABBING },
    { OHOS::NWeb::CursorType::CT_MIDDLE_PANNING_VERTICAL, MouseFormat::MIDDLE_BTN_NORTH_SOUTH },
    { OHOS::NWeb::CursorType::CT_MIDDLE_PANNING_HORIZONTAL, MouseFormat::MIDDLE_BTN_NORTH_SOUTH_WEST_EAST },
};

bool ParseDateTimeJson(const std::string& timeJson, NWeb::DateTime& result)
{
    auto sourceJson = JsonUtil::ParseJsonString(timeJson);
    if (!sourceJson || sourceJson->IsNull()) {
        return false;
    }

    auto year = sourceJson->GetValue("year");
    if (year && year->IsNumber()) {
        result.year = year->GetInt();
    }
    auto month = sourceJson->GetValue("month");
    if (month && month->IsNumber()) {
        result.month = month->GetInt();
    }
    auto day = sourceJson->GetValue("day");
    if (day && day->IsNumber()) {
        result.day = day->GetInt();
    }
    auto hour = sourceJson->GetValue("hour");
    if (hour && hour->IsNumber()) {
        result.hour = hour->GetInt();
    }
    auto minute = sourceJson->GetValue("minute");
    if (minute && minute->IsNumber()) {
        result.minute = minute->GetInt();
    }
    return true;
}

std::string ParseTextJsonValue(const std::string& textJson)
{
    auto sourceJson = JsonUtil::ParseJsonString(textJson);
    if (!sourceJson || sourceJson->IsNull()) {
        return "";
    }
    auto value = sourceJson->GetValue("value");
    if (value && value->IsString()) {
        return value->GetString();
    }
    return "";
}
} // namespace

constexpr int32_t SINGLE_CLICK_NUM = 1;
constexpr int32_t DOUBLE_CLICK_NUM = 2;
constexpr double DEFAULT_DBCLICK_INTERVAL = 0.5;
constexpr double DEFAULT_DBCLICK_OFFSET = 2.0;
constexpr double DEFAULT_AXIS_RATIO = -0.06;
constexpr double DEFAULT_WEB_WIDTH = 100.0;
constexpr double DEFAULT_WEB_HEIGHT = 80.0;
constexpr uint32_t DEFAULT_WEB_DRAW_HEIGHT = 4000;
const std::string PATTERN_TYPE_WEB = "WEBPATTERN";
constexpr int32_t SURFACE_QUEUE_SIZE = 8;
// web feature params
constexpr char VISIBLE_ACTIVE_ENABLE[] = "persist.web.visible_active_enable";
constexpr char MEMORY_LEVEL_ENABEL[] = "persist.web.memory_level_enable";
const std::vector<int32_t> DEFAULT_HEIGHT_GEAR {7998, 7999, 8001, 8002, 8003};
const std::vector<int32_t> DEFAULT_ORIGN_GEAR {0, 2000, 4000, 6000, 8000};

WebPattern::WebPattern() = default;

WebPattern::WebPattern(const std::string& webSrc,
                       const RefPtr<WebController>& webController,
                       WebType type,
                       bool incognitoMode)
    : webSrc_(std::move(webSrc)), webController_(webController), type_(type),
      incognitoMode_(incognitoMode)
{}

WebPattern::WebPattern(const std::string& webSrc,
                       const SetWebIdCallback& setWebIdCallback,
                       WebType type,
                       bool incognitoMode)
    : webSrc_(std::move(webSrc)), setWebIdCallback_(setWebIdCallback), type_(type),
      incognitoMode_(incognitoMode) {}

WebPattern::~WebPattern()
{
    if (delegate_) {
        delegate_->SetAudioMuted(true);
    }

    if (observer_) {
        observer_->NotifyDestory();
    }
    if (isActive_) {
        OnInActive();
    }
}

bool WebPattern::NeedSoftKeyboard() const
{
    if (delegate_) {
        return delegate_->NeedSoftKeyboard();
    }
    return false;
}

void WebPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
    host->GetRenderContext()->UpdateBackgroundColor(Color::WHITE);
    host->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddNodesToNotifyMemoryLevel(host->GetId());
}

void WebPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    CHECK_NULL_VOID(delegate_);
    isFocus_ = false;
    delegate_->OnBlur();
    OnQuickMenuDismissed();

    auto id = frameNode->GetId();
    auto pipeline = AceType::DynamicCast<PipelineContext>(PipelineBase::GetCurrentContext());
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveWindowStateChangedCallback(id);
    pipeline->RemoveWindowSizeChangeCallback(id);
    pipeline->RemoveNodesToNotifyMemoryLevel(id);
}

void WebPattern::InitEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(eventHub);

    auto gestureHub = eventHub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    InitTouchEvent(gestureHub);
    InitDragEvent(gestureHub);
    InitPanEvent(gestureHub);

    auto inputHub = eventHub->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);
    InitMouseEvent(inputHub);
    InitHoverEvent(inputHub);

    auto focusHub = eventHub->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    InitFocusEvent(focusHub);

    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto langTask = [weak = AceType::WeakClaim(this)]() {
        auto WebPattern = weak.Upgrade();
        CHECK_NULL_VOID(WebPattern);
        WebPattern->UpdateLocale();
    };
    context->SetConfigChangedCallback(std::move(langTask));
}

void WebPattern::InitFeatureParam()
{
    isVisibleActiveEnable_ = system::GetBoolParameter(VISIBLE_ACTIVE_ENABLE, true);
    isMemoryLevelEnable_ = system::GetBoolParameter(MEMORY_LEVEL_ENABEL, true);
}

void WebPattern::InitPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (panEvent_) {
        return;
    }
    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& event) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnScrollStartRecursive(pattern->GetParentAxis() == Axis::HORIZONTAL
                                    ? event.GetGlobalLocation().GetX()
                                    : event.GetGlobalLocation().GetY());
    };
    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& event) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleDragMove(event);
    };
    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) { return; };
    auto actionCancelTask = [weak = WeakClaim(this)]() { return; };
    PanDirection panDirection;
    panDirection.type = PanDirection::ALL;
    panEvent_ = MakeRefPtr<PanEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    gestureHub->AddPanEvent(panEvent_, panDirection, DEFAULT_PAN_FINGER, DEFAULT_PAN_DISTANCE);
}

void WebPattern::HandleDragMove(const GestureEvent& event)
{
    if (event.GetInputEventType() == InputEventType::AXIS) {
        CHECK_NULL_VOID(delegate_);
        auto localLocation = event.GetLocalLocation();
        delegate_->HandleAxisEvent(localLocation.GetX(), localLocation.GetY(),
            event.GetDelta().GetX() * DEFAULT_AXIS_RATIO, event.GetDelta().GetY() * DEFAULT_AXIS_RATIO);
    }
}

void WebPattern::InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (touchEvent_) {
        return;
    }

    auto touchTask = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (info.GetChangedTouches().empty()) {
            return;
        }

        // only handle touch event
        if (info.GetSourceDevice() != SourceType::TOUCH) {
            return;
        }

        pattern->isMouseEvent_ = false;
        const auto& changedPoint = info.GetChangedTouches().front();
        if (changedPoint.GetTouchType() == TouchType::DOWN) {
            pattern->HandleTouchDown(info, false);
            return;
        }
        if (changedPoint.GetTouchType() == TouchType::MOVE) {
            pattern->HandleTouchMove(info, false);
            return;
        }
        if (changedPoint.GetTouchType() == TouchType::UP) {
            pattern->HandleTouchUp(info, false);
            return;
        }
        if (changedPoint.GetTouchType() == TouchType::CANCEL) {
            pattern->HandleTouchCancel(info);
            return;
        }
    };
    touchEvent_ = MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    gestureHub->AddTouchEvent(touchEvent_);
}

void WebPattern::InitMouseEvent(const RefPtr<InputEventHub>& inputHub)
{
    if (mouseEvent_) {
        return;
    }

    auto mouseTask = [weak = WeakClaim(this)](MouseInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleMouseEvent(info);
    };

    mouseEvent_ = MakeRefPtr<InputEvent>(std::move(mouseTask));
    inputHub->AddOnMouseEvent(mouseEvent_);
}

void WebPattern::InitHoverEvent(const RefPtr<InputEventHub>& inputHub)
{
    if (hoverEvent_) {
        return;
    }

    auto hoverTask = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        MouseInfo info;
        info.SetAction(isHover ? MouseAction::HOVER : MouseAction::HOVER_EXIT);
        pattern->WebOnMouseEvent(info);
    };

    hoverEvent_ = MakeRefPtr<InputEvent>(std::move(hoverTask));
    inputHub->AddOnHoverEvent(hoverEvent_);
}

void WebPattern::HandleMouseEvent(MouseInfo& info)
{
    isMouseEvent_ = true;
    WebOnMouseEvent(info);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto mouseEventCallback = eventHub->GetOnMouseEvent();
    CHECK_NULL_VOID(mouseEventCallback);
    mouseEventCallback(info);
}

void WebPattern::WebOnMouseEvent(const MouseInfo& info)
{
    CHECK_NULL_VOID(delegate_);
    if (info.GetAction() == MouseAction::PRESS) {
        delegate_->OnContextMenuHide("");
    }

    if (info.GetAction() == MouseAction::RELEASE) {
        WebRequestFocus();
    }

    if (info.GetButton() == MouseButton::LEFT_BUTTON && info.GetAction() == MouseAction::RELEASE) {
        ResetDragAction();
    }

    auto localLocation = info.GetLocalLocation();
    if (!HandleDoubleClickEvent(info)) {
        delegate_->OnMouseEvent(
            localLocation.GetX(), localLocation.GetY(), info.GetButton(), info.GetAction(), SINGLE_CLICK_NUM);
    }
}

void WebPattern::ResetDragAction()
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    frameNode->SetDraggable(false);
    auto eventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto gestureHub = eventHub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->ResetDragActionForWeb();

    if (!isDragging_) {
        return;
    }

    isDragging_ = false;
    // cancel drag action to avoid web kernel can't process other input event
    CHECK_NULL_VOID(delegate_);
    delegate_->HandleDragEvent(0, 0, DragAction::DRAG_CANCEL);
    gestureHub->CancelDragForWeb();
}

Offset WebPattern::GetDragOffset() const
{
    Offset webDragOffset;
    int x = 0;
    int y = 0;
    if (delegate_ && delegate_->dragData_) {
        delegate_->dragData_->GetDragStartPosition(x, y);
    }

    webDragOffset.SetX(x);
    webDragOffset.SetY(y);

    return webDragOffset;
}

bool WebPattern::HandleDoubleClickEvent(const MouseInfo& info)
{
    if (info.GetButton() != MouseButton::LEFT_BUTTON || info.GetAction() != MouseAction::PRESS) {
        return false;
    }
    auto localLocation = info.GetLocalLocation();
    MouseClickInfo clickInfo;
    clickInfo.x = localLocation.GetX();
    clickInfo.y = localLocation.GetY();
    clickInfo.start = info.GetTimeStamp();
    if (doubleClickQueue_.empty()) {
        doubleClickQueue_.push(clickInfo);
        return false;
    }
    std::chrono::duration<float> timeout_ = clickInfo.start - doubleClickQueue_.back().start;
    double offsetX = clickInfo.x - doubleClickQueue_.back().x;
    double offsetY = clickInfo.y - doubleClickQueue_.back().y;
    double offset = sqrt(offsetX * offsetX + offsetY * offsetY);
    if (timeout_.count() < DEFAULT_DBCLICK_INTERVAL && offset < DEFAULT_DBCLICK_OFFSET) {
        SendDoubleClickEvent(clickInfo);
        std::queue<MouseClickInfo> empty;
        swap(empty, doubleClickQueue_);
        return true;
    }
    if (doubleClickQueue_.size() == 1) {
        doubleClickQueue_.push(clickInfo);
        return false;
    }
    doubleClickQueue_.pop();
    doubleClickQueue_.push(clickInfo);
    return false;
}

void WebPattern::SendDoubleClickEvent(const MouseClickInfo& info)
{
    CHECK_NULL_VOID(delegate_);
    delegate_->OnMouseEvent(info.x, info.y, MouseButton::LEFT_BUTTON, MouseAction::PRESS, DOUBLE_CLICK_NUM);
}

bool WebPattern::GenerateDragDropInfo(NG::DragDropInfo& dragDropInfo)
{
    if (delegate_) {
        dragDropInfo.pixelMap = delegate_->GetDragPixelMap();
    }

    if (dragDropInfo.pixelMap) {
        isW3cDragEvent_ = true;
        return true;
    }

    return false;
}

NG::DragDropInfo WebPattern::HandleOnDragStart(const RefPtr<OHOS::Ace::DragEvent>& info)
{
    isDragging_ = true;
    NG::DragDropInfo dragDropInfo;
    if (GenerateDragDropInfo(dragDropInfo)) {
        auto frameNode = GetHost();
        CHECK_NULL_RETURN(frameNode, dragDropInfo);
        CHECK_NULL_RETURN(delegate_, dragDropInfo);
        CHECK_NULL_RETURN(delegate_->dragData_, dragDropInfo);
        // get drag pixel map successfully, disable next drag util received web kernel drag callback
        frameNode->SetDraggable(false);
        RefPtr<UnifiedData> aceUnifiedData = UdmfClient::GetInstance()->CreateUnifiedData();
        std::string plainContent = delegate_->dragData_->GetFragmentText();
        std::string htmlContent = delegate_->dragData_->GetFragmentHtml();
        std::string linkUrl = delegate_->dragData_->GetLinkURL();
        std::string linkTitle = delegate_->dragData_->GetLinkTitle();
        if (!plainContent.empty()) {
            UdmfClient::GetInstance()->AddPlainTextRecord(aceUnifiedData, plainContent);
        }
        if (!htmlContent.empty()) {
            UdmfClient::GetInstance()->AddHtmlRecord(aceUnifiedData, htmlContent, "");
        }
        if (!linkUrl.empty()) {
            UdmfClient::GetInstance()->AddLinkRecord(aceUnifiedData, linkUrl, linkTitle);
        }
        std::string fileName = delegate_->dragData_->GetImageFileName();
        if (!fileName.empty()) {
            std::string fullName;
            if (delegate_->tempDir_.empty()) {
                fullName = "/data/storage/el2/base/haps/entry/temp/dragdrop/" + fileName;
            } else {
                fullName = delegate_->tempDir_ + "/dragdrop/" + fileName;
            }
            AppFileService::ModuleFileUri::FileUri fileUri(fullName);
            std::vector<std::string> urlVec;
            std::string udmfUri = fileUri.ToString();
            urlVec.emplace_back(udmfUri);
            UdmfClient::GetInstance()->AddFileUriRecord(aceUnifiedData, urlVec);
        } else {
            TAG_LOGW(AceLogTag::ACE_WEB, "DragDrop event start, dragdata has no image file uri, just pass");
        }
        info->SetData(aceUnifiedData);
        HandleOnDragEnter(info);
        return dragDropInfo;
    }
    return dragDropInfo;
}

void WebPattern::HandleOnDropMove(const RefPtr<OHOS::Ace::DragEvent>& info)
{
    if (!isDragging_) {
        return;
    }

    if (!isW3cDragEvent_) {
        return;
    }

    CHECK_NULL_VOID(delegate_);
    delegate_->OnContextMenuHide("");
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto viewScale = pipelineContext->GetViewScale();
    int32_t globalX = static_cast<int32_t>(info->GetX()) * viewScale;
    int32_t globalY = static_cast<int32_t>(info->GetY()) * viewScale;
    auto offset = GetCoordinatePoint();
    globalX = static_cast<int32_t>(globalX - offset.value_or(OffsetF()).GetX());
    globalY = static_cast<int32_t>(globalY - offset.value_or(OffsetF()).GetY());
    delegate_->HandleDragEvent(globalX, globalY, DragAction::DRAG_OVER);
}

void WebPattern::InitCommonDragDropEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(eventHub);

    isDisableDrag_ = false;
    // disable drag
    frameNode->SetDraggable(false);
    // init common drag drop event
    gestureHub->InitDragDropEvent();
    InitWebEventHubDragDropStart(eventHub);
    InitWebEventHubDragDropEnd(eventHub);
}

void WebPattern::InitWebEventHubDragDropStart(const RefPtr<WebEventHub>& eventHub)
{
    auto onDragStartId = [weak = WeakClaim(this)](const RefPtr<OHOS::Ace::DragEvent>& info,
                             const std::string& extraParams) -> NG::DragDropInfo {
        NG::DragDropInfo dragDropInfo;
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->dropX_ = 0;
            pattern->dropY_ = 0;
            return pattern->HandleOnDragStart(info);
        }
        return dragDropInfo;
    };

    auto onDragEnterId = [weak = WeakClaim(this)](const RefPtr<OHOS::Ace::DragEvent>& info,
                             const std::string& extraParams) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->isW3cDragEvent_ = true;
        pattern->isDragging_ = true;
        pattern->dropX_ = 0;
        pattern->dropY_ = 0;
        return pattern->HandleOnDragEnter(info);
    };

    auto onDragMoveId = [weak = WeakClaim(this)](const RefPtr<OHOS::Ace::DragEvent>& info,
                             const std::string& extraParams) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (!pattern->isDragging_) {
            return;
        }
        pattern->OnQuickMenuDismissed();

        // update drag status
        info->SetResult(pattern->GetDragAcceptableStatus());

        pattern->HandleOnDropMove(info);
    };
    // set custom OnDragStart function
    eventHub->SetOnDragStart(std::move(onDragStartId));
    eventHub->SetOnDragEnter(std::move(onDragEnterId));
    eventHub->SetOnDragMove(std::move(onDragMoveId));
}

void WebPattern::InitWebEventHubDragDropEnd(const RefPtr<WebEventHub>& eventHub)
{
    auto onDragDropId = [weak = WeakClaim(this)](const RefPtr<OHOS::Ace::DragEvent>& info,
                             const std::string& extraParams) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (!pattern->isDragging_) {
            return;
        }
        pattern->dropX_ = info->GetX();
        pattern->dropY_ = info->GetY();
        pattern->HandleOnDragDrop(info);
    };

    auto onDragLeaveId = [weak = WeakClaim(this)](const RefPtr<OHOS::Ace::DragEvent>& info,
                             const std::string& extraParams) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleOnDragLeave(info->GetX(), info->GetY());
    };

    auto onDragEndId = [weak = WeakClaim(this)](const RefPtr<OHOS::Ace::DragEvent>& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleDragEnd(pattern->dropX_, pattern->dropY_);
    };
    // set custom OnDragStart function
    eventHub->SetOnDragEnd(std::move(onDragEndId));
    eventHub->SetOnDragLeave(std::move(onDragLeaveId));
    eventHub->SetOnDrop(std::move(onDragDropId));
}

bool WebPattern::IsImageDrag()
{
    if (delegate_) {
        return delegate_->IsImageDrag();
    }
    return false;
}

DragRet WebPattern::GetDragAcceptableStatus()
{
    OHOS::NWeb::NWebDragData::DragOperation status = delegate_->GetDragAcceptableStatus();
    if (status == OHOS::NWeb::NWebDragData::DragOperation::DRAG_OPERATION_MOVE ||
        status == OHOS::NWeb::NWebDragData::DragOperation::DRAG_OPERATION_COPY ||
        status == OHOS::NWeb::NWebDragData::DragOperation::DRAG_OPERATION_LINK) {
        return DragRet::ENABLE_DROP;
    }
    return DragRet::DISABLE_DROP;
}

bool WebPattern::NotifyStartDragTask()
{
    if (isDisableDrag_) {
        return false;
    }
    isDragging_ = true;
    auto frameNode = GetHost();
    CHECK_NULL_RETURN(frameNode, false);
    auto eventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    auto gestureHub = eventHub->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(gestureHub, false);
    // received web kernel drag callback, enable drag
    frameNode->SetDraggable(true);
    gestureHub->SetPixelMap(delegate_->GetDragPixelMap());
    if (!isMouseEvent_) {
        // mouse drag does not need long press action
        gestureHub->StartLongPressActionForWeb();
    }
    gestureHub->StartDragTaskForWeb();
    return true;
}

void WebPattern::InitDragEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (dragEvent_) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(eventHub);

    auto userOnDragStartFunc = eventHub->GetOnDragStart();
    if (userOnDragStartFunc) {
        isDisableDrag_ = true;
        return;
    }

    InitCommonDragDropEvent(gestureHub);

    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        int32_t x = info.GetGlobalPoint().GetX();
        int32_t y = info.GetGlobalPoint().GetY();
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleDragStart(x, y);
    };

    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        return;
    };

    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        int32_t x = info.GetGlobalPoint().GetX();
        int32_t y = info.GetGlobalPoint().GetY();
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleDragEnd(x, y);
    };

    auto actionCancelTask = [weak = WeakClaim(this)]() {
    };

    dragEvent_ = MakeRefPtr<DragEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    gestureHub->SetCustomDragEvent(dragEvent_, { PanDirection::ALL }, DEFAULT_PAN_FINGER, DEFAULT_PAN_DISTANCE);
}

void WebPattern::HandleDragStart(int32_t x, int32_t y) {}

void WebPattern::HandleOnDragEnter(const RefPtr<OHOS::Ace::DragEvent>& info)
{
    if (!delegate_) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    int32_t globalX = static_cast<int32_t>(info->GetX());
    int32_t globalY = static_cast<int32_t>(info->GetY());
    auto viewScale = pipelineContext->GetViewScale();
    auto offset = GetCoordinatePoint();
    int32_t localX = static_cast<int32_t>(globalX - offset.value_or(OffsetF()).GetX()) * viewScale;
    int32_t localY = static_cast<int32_t>(globalY - offset.value_or(OffsetF()).GetY()) * viewScale;

    // fake drag data when enter
    delegate_->GetOrCreateDragData();
    // use summary to set fake data
    ClearDragData();
    delegate_->HandleDragEvent(localX, localY, DragAction::DRAG_ENTER);
}

void WebPattern::HandleOnDragDropLink(RefPtr<UnifiedData> aceData)
{
    CHECK_NULL_VOID(aceData);
    CHECK_NULL_VOID(delegate_);
    CHECK_NULL_VOID(delegate_->dragData_);
    // hyperlink
    std::string linkUrl;
    std::string linkTitle;
    UdmfClient::GetInstance()->GetLinkRecord(aceData, linkUrl, linkTitle);
    if (!linkUrl.empty()) {
        delegate_->dragData_->SetLinkURL(linkUrl);
        delegate_->dragData_->SetLinkTitle(linkTitle);
    } else {
        TAG_LOGW(AceLogTag::ACE_WEB,
            "DragDrop event WebEventHub onDragDropId, linkUrl is empty");
    }
}

void WebPattern::HandleOnDragDropFile(RefPtr<UnifiedData> aceData)
{
    CHECK_NULL_VOID(aceData);
    CHECK_NULL_VOID(delegate_);
    CHECK_NULL_VOID(delegate_->dragData_);
    // file
    std::vector<std::string> urlVec;
    UdmfClient::GetInstance()->GetFileUriRecord(aceData, urlVec);
    TAG_LOGI(AceLogTag::ACE_WEB, "DragDrop event WebEventHub onDragDropId,"
        "url array size is:%{public}d", (int)urlVec.size());
    delegate_->dragData_->ClearImageFileNames();
    for (std::string url : urlVec) {
        TAG_LOGI(AceLogTag::ACE_WEB, "DragDrop event WebEventHub onDragDropId,"
            "url get from udmf:%{public}s", url.c_str());
        AppFileService::ModuleFileUri::FileUri fileUri(url);
        TAG_LOGI(AceLogTag::ACE_WEB, "DragDrop event WebEventHub onDragDropId,"
            "fileUri ToString:%{public}s", fileUri.ToString().c_str());
        std::string uriRealPath = FileUriHelper::GetRealPath(url);
        if (!uriRealPath.empty() && access(uriRealPath.c_str(), F_OK) == 0) { // file exist
            TAG_LOGI(AceLogTag::ACE_WEB, "DragDrop event WebEventHub onDragDropId,"
            "url real path:%{public}s", uriRealPath.c_str());
            delegate_->dragData_->SetFileUri(uriRealPath);
        } else {
            TAG_LOGW(AceLogTag::ACE_WEB, "DragDrop event WebEventHub onDragDropId,"
                "url is empty or not exist, uriRealPath:%{public}s", uriRealPath.c_str());
        }
    }
}

void WebPattern::HandleOnDragDrop(const RefPtr<OHOS::Ace::DragEvent>& info)
{
    isDragging_ = false;
    isW3cDragEvent_ = false;
    CHECK_NULL_VOID(delegate_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto viewScale = pipelineContext->GetViewScale();
    auto offset = GetCoordinatePoint();
    int32_t localX = static_cast<int32_t>(info->GetX() - offset.value_or(OffsetF()).GetX()) * viewScale;
    int32_t localY = static_cast<int32_t>(info->GetY() - offset.value_or(OffsetF()).GetY()) * viewScale;

    RefPtr<UnifiedData> aceData = info->GetData();
    // get data from ace(from udmf), and send it to chromium
    if (aceData && aceData->GetSize() >= 1) {
        TAG_LOGI(AceLogTag::ACE_WEB,
            "DragDrop event WebEventHub onDragDropId, size:%{public}d", (int)aceData->GetSize());
        CHECK_NULL_VOID(delegate_->dragData_);
        // plain text
        std::string plain = UdmfClient::GetInstance()->GetSinglePlainTextRecord(aceData);
        if (!plain.empty()) {
            delegate_->dragData_->SetFragmentText(plain);
        }
        // html
        std::string htmlContent;
        std::string plainContent;
        UdmfClient::GetInstance()->GetHtmlRecord(aceData, htmlContent, plainContent);
        if (!htmlContent.empty()) {
            delegate_->dragData_->SetFragmentHtml(htmlContent);
        }
        // link
        HandleOnDragDropLink(aceData);
        // file
        HandleOnDragDropFile(aceData);
    } else {
        TAG_LOGW(AceLogTag::ACE_WEB, "DragDrop event WebEventHub onDragDropId get data failed");
    }

    delegate_->HandleDragEvent(localX, localY, DragAction::DRAG_DROP);
}

void WebPattern::HandleOnDragLeave(int32_t x, int32_t y)
{
    CHECK_NULL_VOID(delegate_);
    isDragging_ = false;
    isW3cDragEvent_ = false;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto viewScale = pipelineContext->GetViewScale();
    auto offset = GetCoordinatePoint();
    int32_t localX = static_cast<int32_t>(x - offset.value_or(OffsetF()).GetX());
    int32_t localY = static_cast<int32_t>(y - offset.value_or(OffsetF()).GetY());
    delegate_->HandleDragEvent(localX * viewScale, localY * viewScale, DragAction::DRAG_LEAVE);
}

void WebPattern::HandleDragEnd(int32_t x, int32_t y)
{
    CHECK_NULL_VOID(delegate_);

    isDragging_ = false;
    isW3cDragEvent_ = false;
    ClearDragData();

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto viewScale = pipelineContext->GetViewScale();
    auto offset = GetCoordinatePoint();
    int32_t localX = static_cast<int32_t>(x - offset.value_or(OffsetF()).GetX()) * viewScale;
    int32_t localY = static_cast<int32_t>(y - offset.value_or(OffsetF()).GetY()) * viewScale;
    if (x == 0 && y == 0) {
        delegate_->HandleDragEvent(0, 0, DragAction::DRAG_END);
    } else {
        delegate_->HandleDragEvent(localX, localY, DragAction::DRAG_END);
    }
}

void WebPattern::HandleDragCancel()
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    // disable drag
    frameNode->SetDraggable(false);
    CHECK_NULL_VOID(delegate_);
    isDragging_ = false;
    isW3cDragEvent_ = false;
    ClearDragData();
    delegate_->HandleDragEvent(0, 0, DragAction::DRAG_CANCEL);
}

void WebPattern::ClearDragData()
{
    CHECK_NULL_VOID(delegate_);
    std::string plain = "";
    std::string htmlContent = "";
    std::string linkUrl = "";
    std::string linkTitle = "";
    if (delegate_->dragData_) {
        delegate_->dragData_->SetFragmentText(plain);
        delegate_->dragData_->SetFragmentHtml(htmlContent);
        delegate_->dragData_->SetLinkURL(linkUrl);
        delegate_->dragData_->SetLinkTitle(linkTitle);
    }
}

void WebPattern::InitFocusEvent(const RefPtr<FocusHub>& focusHub)
{
    auto focusTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleFocusEvent();
    };
    focusHub->SetOnFocusInternal(focusTask);

    auto blurTask = [weak = WeakClaim(this)](const BlurReason& blurReason) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleBlurEvent(blurReason);
    };
    focusHub->SetOnBlurReasonInternal(blurTask);

    auto keyTask = [weak = WeakClaim(this)](const KeyEvent& keyEvent) -> bool {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->HandleKeyEvent(keyEvent);
    };
    focusHub->SetOnKeyEventInternal(keyTask);
}

void WebPattern::HandleFocusEvent()
{
    CHECK_NULL_VOID(delegate_);
    isFocus_ = true;
    if (needOnFocus_) {
        delegate_->OnFocus();
    } else {
        needOnFocus_ = true;
    }
}

void WebPattern::HandleBlurEvent(const BlurReason& blurReason)
{
    CHECK_NULL_VOID(delegate_);
    isFocus_ = false;
    if (!selectPopupMenuShowing_) {
        delegate_->SetBlurReason(static_cast<OHOS::NWeb::BlurReason>(blurReason));
        delegate_->OnBlur();
    }
    OnQuickMenuDismissed();
    for (auto keyCode : KeyCodeSet_) {
        delegate_->OnKeyEvent(static_cast<int32_t>(keyCode), static_cast<int32_t>(OHOS::Ace::KeyAction::UP));
    }
    KeyCodeSet_.clear();
}

bool WebPattern::HandleKeyEvent(const KeyEvent& keyEvent)
{
    bool ret = false;

    auto host = GetHost();
    CHECK_NULL_RETURN(host, ret);
    auto eventHub = host->GetEventHub<WebEventHub>();
    CHECK_NULL_RETURN(eventHub, ret);

    KeyEventInfo info(keyEvent);
    auto keyEventCallback = eventHub->GetOnKeyEvent();
    if (keyEventCallback) {
        keyEventCallback(info);
    }

    auto preKeyEventCallback = eventHub->GetOnPreKeyEvent();
    if (preKeyEventCallback) {
        ret = preKeyEventCallback(info);
        if (ret) {
            return ret;
        }
    }

    ret = WebOnKeyEvent(keyEvent);
    return ret;
}

bool WebPattern::WebOnKeyEvent(const KeyEvent& keyEvent)
{
    CHECK_NULL_RETURN(delegate_, false);
    if (keyEvent.action == OHOS::Ace::KeyAction::DOWN) {
        KeyCodeSet_.insert(keyEvent.code);
    } else if (keyEvent.action == OHOS::Ace::KeyAction::UP) {
        KeyCodeSet_.erase(keyEvent.code);
    }
    return delegate_->OnKeyEvent(static_cast<int32_t>(keyEvent.code), static_cast<int32_t>(keyEvent.action));
}

void WebPattern::WebRequestFocus()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto focusHub = eventHub->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);

    focusHub->RequestFocusImmediately();
}

void WebPattern::UpdateContentOffset(const RefPtr<LayoutWrapper>& dirty)
{
    CHECK_NULL_VOID(dirty);
    auto geometryNode = dirty->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto paddingOffset = geometryNode->GetPaddingOffset();
    auto webContentSize = geometryNode->GetContentSize();

    auto positionProperty = renderContext->GetPropertyOfPosition();
    renderContext->SetBounds(
        paddingOffset.GetX() +  positionProperty.GetX(), paddingOffset.GetY() + positionProperty.GetY(),
        webContentSize.Width(), webContentSize.Height());
}

bool WebPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (!config.contentSizeChange || isInWindowDrag_) {
        return false;
    }
    CHECK_NULL_RETURN(delegate_, false);
    CHECK_NULL_RETURN(dirty, false);
    auto geometryNode = dirty->GetGeometryNode();
    auto drawSize = Size(geometryNode->GetContentSize().Width(), geometryNode->GetContentSize().Height());
    if (drawSize.IsInfinite() || drawSize.IsEmpty()) {
        return false;
    }

    if (GreatOrEqual(drawSize.Width(), Infinity<double>())) {
        drawSize.SetWidth(DEFAULT_WEB_WIDTH);
    }
    if (GreatOrEqual(drawSize.Height(), Infinity<double>())) {
        drawSize.SetHeight(DEFAULT_WEB_HEIGHT);
    }

    drawSize_ = drawSize;
    drawSizeCache_ = drawSize_;
    auto offset = Offset(GetCoordinatePoint()->GetX(), GetCoordinatePoint()->GetY());
    delegate_->SetBoundsOrResize(drawSize_, offset);
    if (isOfflineMode_) {
        isOfflineMode_ = false;
        OnWindowShow();
    }

    // first update size to load url.
    if (!isUrlLoaded_) {
        isUrlLoaded_ = true;
        if (webSrc_) {
            delegate_->LoadUrl();
        } else if (webData_) {
            delegate_->LoadDataWithRichText();
        }
    }

    return false;
}

void WebPattern::OnAreaChangedInner()
{
    auto offset = OffsetF(GetCoordinatePoint()->GetX(), GetCoordinatePoint()->GetY());
    if (webOffset_ == offset) {
        return;
    }
    webOffset_ = offset;
    UpdateTouchHandleForOverlay();
    if (isInWindowDrag_)
        return;
    auto resizeOffset = Offset(offset.GetX(), offset.GetY());
    delegate_->SetBoundsOrResize(drawSize_, resizeOffset);
}

void WebPattern::OnWebSrcUpdate()
{
    if (delegate_ && isUrlLoaded_) {
        delegate_->LoadUrl();
    }
}

void WebPattern::OnWebDataUpdate()
{
    if (delegate_ && isUrlLoaded_) {
        delegate_->LoadDataWithRichText();
    }
}

void WebPattern::OnJsEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateJavaScriptEnabled(value);
    }
}

void WebPattern::OnMediaPlayGestureAccessUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateMediaPlayGestureAccess(value);
    }
}

void WebPattern::OnFileAccessEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateAllowFileAccess(value);
    }
}

void WebPattern::OnOnLineImageAccessEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateBlockNetworkImage(!value);
    }
}

void WebPattern::OnDomStorageAccessEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateDomStorageEnabled(value);
    }
}

void WebPattern::OnImageAccessEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateLoadsImagesAutomatically(value);
    }
}

void WebPattern::OnMixedModeUpdate(MixedModeContent value)
{
    if (delegate_) {
        delegate_->UpdateMixedContentMode(value);
    }
}

void WebPattern::OnZoomAccessEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateSupportZoom(value);
    }
}

void WebPattern::OnGeolocationAccessEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateGeolocationEnabled(value);
    }
}

void WebPattern::OnUserAgentUpdate(const std::string& value)
{
    if (delegate_) {
        delegate_->UpdateUserAgent(value);
    }
}

void WebPattern::OnCacheModeUpdate(WebCacheMode value)
{
    if (delegate_) {
        delegate_->UpdateCacheMode(value);
    }
}

void WebPattern::OnDarkModeUpdate(WebDarkMode mode)
{
    if (delegate_) {
        delegate_->UpdateDarkMode(mode);
    }
}

void WebPattern::OnOverScrollModeUpdate(int mode)
{
    if (delegate_) {
        delegate_->UpdateOverScrollMode(mode);
    }
}

void WebPattern::OnCopyOptionModeUpdate(int32_t mode)
{
    if (delegate_) {
        delegate_->UpdateCopyOptionMode(mode);
    }
}

void WebPattern::OnForceDarkAccessUpdate(bool access)
{
    if (delegate_) {
        delegate_->UpdateForceDarkAccess(access);
    }
}

void WebPattern::OnAudioResumeIntervalUpdate(int32_t resumeInterval)
{
    if (delegate_) {
        delegate_->UpdateAudioResumeInterval(resumeInterval);
    }
}

void WebPattern::OnAudioExclusiveUpdate(bool audioExclusive)
{
    if (delegate_) {
        delegate_->UpdateAudioExclusive(audioExclusive);
    }
}

void WebPattern::OnOverviewModeAccessEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateOverviewModeEnabled(value);
    }
}

void WebPattern::OnFileFromUrlAccessEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateFileFromUrlEnabled(value);
    }
}

void WebPattern::OnDatabaseAccessEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateDatabaseEnabled(value);
    }
}

void WebPattern::OnTextZoomRatioUpdate(int32_t value)
{
    if (delegate_) {
        delegate_->UpdateTextZoomRatio(value);
    }
}

void WebPattern::OnWebDebuggingAccessEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateWebDebuggingAccess(value);
    }
}

void WebPattern::OnPinchSmoothModeEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdatePinchSmoothModeEnabled(value);
    }
}

void WebPattern::OnBackgroundColorUpdate(int32_t value)
{
    UpdateBackgroundColorRightNow(value);
    if (delegate_) {
        delegate_->UpdateBackgroundColor(value);
    }
}

void WebPattern::OnInitialScaleUpdate(float value)
{
    if (delegate_) {
        delegate_->UpdateInitialScale(value);
    }
}

void WebPattern::OnMultiWindowAccessEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateMultiWindowAccess(value);
    }
}

void WebPattern::OnAllowWindowOpenMethodUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateAllowWindowOpenMethod(value);
    }
}

void WebPattern::OnWebCursiveFontUpdate(const std::string& value)
{
    if (delegate_) {
        delegate_->UpdateWebCursiveFont(value);
    }
}

void WebPattern::OnWebFantasyFontUpdate(const std::string& value)
{
    if (delegate_) {
        delegate_->UpdateWebFantasyFont(value);
    }
}

void WebPattern::OnWebFixedFontUpdate(const std::string& value)
{
    if (delegate_) {
        delegate_->UpdateWebFixedFont(value);
    }
}

void WebPattern::OnWebSansSerifFontUpdate(const std::string& value)
{
    if (delegate_) {
        delegate_->UpdateWebSansSerifFont(value);
    }
}

void WebPattern::OnWebSerifFontUpdate(const std::string& value)
{
    if (delegate_) {
        delegate_->UpdateWebSerifFont(value);
    }
}

void WebPattern::OnWebStandardFontUpdate(const std::string& value)
{
    if (delegate_) {
        delegate_->UpdateWebStandardFont(value);
    }
}

void WebPattern::OnDefaultFixedFontSizeUpdate(int32_t value)
{
    if (delegate_) {
        delegate_->UpdateDefaultFixedFontSize(value);
    }
}

void WebPattern::OnDefaultFontSizeUpdate(int32_t value)
{
    if (delegate_) {
        delegate_->UpdateDefaultFontSize(value);
    }
}

void WebPattern::OnMinFontSizeUpdate(int32_t value)
{
    if (delegate_) {
        delegate_->UpdateMinFontSize(value);
    }
}

void WebPattern::OnMinLogicalFontSizeUpdate(int32_t value)
{
    if (delegate_) {
        delegate_->UpdateMinLogicalFontSize(value);
    }
}

void WebPattern::OnBlockNetworkUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateBlockNetwork(value);
    }
}

void WebPattern::OnHorizontalScrollBarAccessEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateHorizontalScrollBarAccess(value);
    }
}

void WebPattern::OnVerticalScrollBarAccessEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateVerticalScrollBarAccess(value);
    }
}

void WebPattern::OnScrollBarColorUpdate(const std::string& value)
{
    if (delegate_) {
        delegate_->UpdateScrollBarColor(value);
    }
}

void WebPattern::RegistVirtualKeyBoardListener()
{
    if (!needUpdateWeb_) {
        return;
    }
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->SetVirtualKeyBoardCallback(
        [weak = AceType::WeakClaim(this)](int32_t width, int32_t height, double keyboard) {
            auto webPattern = weak.Upgrade();
            CHECK_NULL_RETURN(webPattern, false);
            return webPattern->ProcessVirtualKeyBoard(width, height, keyboard);
        });
    needUpdateWeb_ = false;
}

void WebPattern::InitEnhanceSurfaceFlag()
{
    if (SystemProperties::GetExtSurfaceEnabled()) {
        isEnhanceSurface_ = true;
    } else {
        isEnhanceSurface_ = false;
    }
}

void WebPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    // called in each update function.
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    RegistVirtualKeyBoardListener();
    if (!delegate_) {
        // first create case,
        delegate_ = AceType::MakeRefPtr<WebDelegate>(PipelineContext::GetCurrentContext(), nullptr, "");
        CHECK_NULL_VOID(delegate_);
        observer_ = AceType::MakeRefPtr<WebDelegateObserver>(delegate_, PipelineContext::GetCurrentContext());
        CHECK_NULL_VOID(observer_);
        delegate_->SetObserver(observer_);
        delegate_->SetWebType(type_);
        InitEnhanceSurfaceFlag();
        delegate_->SetNGWebPattern(Claim(this));
        delegate_->SetEnhanceSurfaceFlag(isEnhanceSurface_);
        delegate_->SetPopup(isPopup_);
        delegate_->SetParentNWebId(parentNWebId_);
        accessibilityState_ = AceApplicationInfo::GetInstance().IsAccessibilityEnabled();
        delegate_->UpdateAccessibilityState(accessibilityState_);
        delegate_->SetBackgroundColor(GetBackgroundColorValue(
            static_cast<int32_t>(renderContext->GetBackgroundColor().value_or(Color::WHITE).GetValue())));
        if (isEnhanceSurface_) {
            auto drawSize = Size(1, 1);
            delegate_->SetDrawSize(drawSize);
            delegate_->InitOHOSWeb(PipelineContext::GetCurrentContext());
        } else {
            auto drawSize = Size(1, 1);
            delegate_->SetDrawSize(drawSize);
            int32_t instanceId = Container::CurrentId();
            renderSurface_->SetInstanceId(instanceId);
            renderSurface_->SetRenderContext(host->GetRenderContext());
            if (type_ == WebType::TEXTURE) {
                renderSurface_->SetIsTexture(true);
                renderSurface_->SetPatternType(PATTERN_TYPE_WEB);
                renderSurface_->SetSurfaceQueueSize(SURFACE_QUEUE_SIZE);
            } else {
                renderSurface_->SetIsTexture(false);
            }
            renderSurface_->InitSurface();
            renderSurface_->UpdateXComponentConfig();
            delegate_->InitOHOSWeb(PipelineContext::GetCurrentContext(), renderSurface_);
        }
        UpdateJavaScriptOnDocumentStart();
        UpdateJavaScriptOnDocumentEnd();
        delegate_->UpdateBackgroundColor(GetBackgroundColorValue(
            static_cast<int32_t>(renderContext->GetBackgroundColor().value_or(Color::WHITE).GetValue())));
        delegate_->UpdateJavaScriptEnabled(GetJsEnabledValue(true));
        delegate_->UpdateBlockNetworkImage(!GetOnLineImageAccessEnabledValue(true));
        delegate_->UpdateAllowFileAccess(GetFileAccessEnabledValue(true));
        delegate_->UpdateLoadsImagesAutomatically(GetImageAccessEnabledValue(true));
        delegate_->UpdateMixedContentMode(GetMixedModeValue(MixedModeContent::MIXED_CONTENT_NEVER_ALLOW));
        delegate_->UpdateSupportZoom(GetZoomAccessEnabledValue(true));
        delegate_->UpdateDomStorageEnabled(GetDomStorageAccessEnabledValue(false));
        delegate_->UpdateGeolocationEnabled(GetGeolocationAccessEnabledValue(true));
        delegate_->UpdateCacheMode(GetCacheModeValue(WebCacheMode::DEFAULT));
        if (webData_) {
            // Created a richtext component
            delegate_->SetRichtextIdentifier(webData_);
            delegate_->UpdateDarkMode(GetDarkModeValue(WebDarkMode::Auto));
            delegate_->UpdateForceDarkAccess(GetForceDarkAccessValue(true));
            delegate_->UpdateOverviewModeEnabled(GetOverviewModeAccessEnabledValue(false));
        } else {
            delegate_->UpdateDarkMode(GetDarkModeValue(WebDarkMode::Off));
            delegate_->UpdateForceDarkAccess(GetForceDarkAccessValue(false));
            delegate_->UpdateOverviewModeEnabled(GetOverviewModeAccessEnabledValue(true));
        }
        delegate_->UpdateAudioResumeInterval(GetAudioResumeIntervalValue(-1));
        delegate_->UpdateAudioExclusive(GetAudioExclusiveValue(true));
        delegate_->UpdateFileFromUrlEnabled(GetFileFromUrlAccessEnabledValue(false));
        delegate_->UpdateDatabaseEnabled(GetDatabaseAccessEnabledValue(false));
        delegate_->UpdateTextZoomRatio(GetTextZoomRatioValue(DEFAULT_TEXT_ZOOM_RATIO));
        delegate_->UpdateWebDebuggingAccess(GetWebDebuggingAccessEnabledValue(false));
        delegate_->UpdateMediaPlayGestureAccess(GetMediaPlayGestureAccessValue(true));
        delegate_->UpdatePinchSmoothModeEnabled(GetPinchSmoothModeEnabledValue(false));
        delegate_->UpdateMultiWindowAccess(GetMultiWindowAccessEnabledValue(false));
        delegate_->UpdateWebCursiveFont(GetWebCursiveFontValue(DEFAULT_CURSIVE_FONT_FAMILY));
        delegate_->UpdateWebFantasyFont(GetWebFantasyFontValue(DEFAULT_FANTASY_FONT_FAMILY));
        delegate_->UpdateWebFixedFont(GetWebFixedFontValue(DEFAULT_FIXED_fONT_FAMILY));
        delegate_->UpdateWebSansSerifFont(GetWebSansSerifFontValue(DEFAULT_SANS_SERIF_FONT_FAMILY));
        delegate_->UpdateWebSerifFont(GetWebSerifFontValue(DEFAULT_SERIF_FONT_FAMILY));
        delegate_->UpdateWebStandardFont(GetWebStandardFontValue(DEFAULT_STANDARD_FONT_FAMILY));
        delegate_->UpdateDefaultFixedFontSize(GetDefaultFixedFontSizeValue(DEFAULT_FIXED_FONT_SIZE));
        delegate_->UpdateDefaultFontSize(GetDefaultFontSizeValue(DEFAULT_FONT_SIZE));
        delegate_->UpdateMinFontSize(GetMinFontSizeValue(DEFAULT_MINIMUM_FONT_SIZE));
        delegate_->UpdateMinLogicalFontSize(GetMinLogicalFontSizeValue(DEFAULT_MINIMUM_LOGICAL_FONT_SIZE));
        delegate_->UpdateHorizontalScrollBarAccess(GetHorizontalScrollBarAccessEnabledValue(true));
        delegate_->UpdateVerticalScrollBarAccess(GetVerticalScrollBarAccessEnabledValue(true));
        delegate_->UpdateScrollBarColor(GetScrollBarColorValue(DEFAULT_SCROLLBAR_COLOR));
        delegate_->UpdateOverScrollMode(GetOverScrollModeValue(OverScrollMode::NEVER));
        delegate_->UpdateCopyOptionMode(GetCopyOptionModeValue(static_cast<int32_t>(CopyOptions::Distributed)));
        if (GetBlockNetwork()) {
            delegate_->UpdateBlockNetwork(GetBlockNetwork().value());
        }
        if (GetUserAgent()) {
            delegate_->UpdateUserAgent(GetUserAgent().value());
        }
        if (GetInitialScale()) {
            delegate_->UpdateInitialScale(GetInitialScale().value());
        }
        isAllowWindowOpenMethod_ = SystemProperties::GetAllowWindowOpenMethodEnabled();
        delegate_->UpdateAllowWindowOpenMethod(GetAllowWindowOpenMethodValue(isAllowWindowOpenMethod_));
        if (!webAccessibilityNode_) {
            webAccessibilityNode_ = AceType::MakeRefPtr<WebAccessibilityNode>(host);
        }
    }

    // Initialize events such as keyboard, focus, etc.
    InitEvent();
    // Initialize web params.
    InitFeatureParam();

    // Initialize scrollupdate listener
    if (type_ == WebType::TEXTURE) {
        auto task = [this]() {
            InitScrollUpdateListener();
        };
        PostTaskToUI(std::move(task));
    }
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->AddOnAreaChangeNode(host->GetId());

    // offline mode
    if (host->GetNodeStatus() != NodeStatus::NORMAL_NODE) {
        TAG_LOGE(AceLogTag::ACE_WEB, "Web offline mode type");
        isOfflineMode_ = true;
        OfflineMode();
    }
}

void WebPattern::OfflineMode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    int width = 0;
    int height = 0;
    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto& calcLayout = layoutProperty->GetCalcLayoutConstraint();
    if (calcLayout) {
        width = calcLayout->selfIdealSize ?
            calcLayout->selfIdealSize->Width()->GetDimension().ConvertToPx() : 0;
        height = calcLayout->selfIdealSize ?
            calcLayout->selfIdealSize->Height()->GetDimension().ConvertToPx() : 0;
    }
    bool isUnSetSize = (width == 0) && (height == 0);
    auto defaultDisplay = OHOS::Rosen::DisplayManager::GetInstance().GetDefaultDisplay();
    if (isUnSetSize && defaultDisplay) {
        width = defaultDisplay->GetWidth();
        height = defaultDisplay->GetHeight();
    }
    Size drawSize = Size(width, height);
    Offset offset = Offset(0, 0);
    delegate_->SetBoundsOrResize(drawSize, offset);
    if (webSrc_) {
        delegate_->LoadUrl();
    } else if (webData_) {
        delegate_->LoadDataWithRichText();
    }
    isUrlLoaded_ = true;
    OnWindowHide();
}

bool WebPattern::ProcessVirtualKeyBoard(int32_t width, int32_t height, double keyboard)
{
    CHECK_NULL_RETURN(delegate_, false);
    delegate_->SetVirtualKeyBoardArg(width, height, keyboard);
    if (!isFocus_ || !isVisible_) {
        if (isVirtualKeyBoardShow_ == VkState::VK_SHOW) {
            drawSize_.SetSize(drawSizeCache_);
            UpdateWebLayoutSize(width, height);
            isVirtualKeyBoardShow_ = VkState::VK_HIDE;
        }
        return false;
    }
    if (NearZero(keyboard)) {
        if (isVirtualKeyBoardShow_ != VkState::VK_SHOW) {
            return false;
        }
        drawSize_.SetSize(drawSizeCache_);
        UpdateWebLayoutSize(width, height);
        isVirtualKeyBoardShow_ = VkState::VK_HIDE;
    } else if (isVirtualKeyBoardShow_ != VkState::VK_SHOW) {
        drawSizeCache_.SetSize(drawSize_);
        if (drawSize_.Height() <= (height - keyboard - GetCoordinatePoint()->GetY())) {
            isVirtualKeyBoardShow_ = VkState::VK_SHOW;
            return true;
        }
        if (height - GetCoordinatePoint()->GetY() < keyboard) {
            return true;
        }
        drawSize_.SetHeight(height - keyboard - GetCoordinatePoint()->GetY());
        UpdateWebLayoutSize(width, height);
        isVirtualKeyBoardShow_ = VkState::VK_SHOW;
    }
    return true;
}

void WebPattern::UpdateWebLayoutSize(int32_t width, int32_t height)
{
    CHECK_NULL_VOID(delegate_);
    if (delegate_->ShouldVirtualKeyboardOverlay()) {
        TAG_LOGW(AceLogTag::ACE_WEB, "VirtualKeyboard Overlaycontent is true and does not require resizing");
        return;
    }
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto rect = frameNode->GetGeometryNode()->GetFrameRect();
    auto offset = Offset(GetCoordinatePoint()->GetX(), GetCoordinatePoint()->GetY());

    // Scroll focused node into view when keyboard show or hide, so set isKeyboard to true here.
    delegate_->SetBoundsOrResize(drawSize_, offset, true);

    rect.SetSize(SizeF(drawSize_.Width(), drawSize_.Height()));
    frameNode->GetRenderContext()->SyncGeometryProperties(rect);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->SetRootRect(width, height, 0);
}

void WebPattern::HandleTouchDown(const TouchEventInfo& info, bool fromOverlay)
{
    CHECK_NULL_VOID(delegate_);
    Offset touchOffset = Offset(0, 0);
    std::list<TouchInfo> touchInfos;
    if (!ParseTouchInfo(info, touchInfos)) {
        return;
    }
    for (auto& touchPoint : touchInfos) {
        if (fromOverlay) {
            touchPoint.x -= webOffset_.GetX();
            touchPoint.y -= webOffset_.GetY();
        }
        delegate_->HandleTouchDown(touchPoint.id, touchPoint.x, touchPoint.y, fromOverlay);
    }
    if (!touchInfos.empty()) {
        WebRequestFocus();
    }
}

void WebPattern::HandleTouchUp(const TouchEventInfo& info, bool fromOverlay)
{
    ResetDragAction();
    CHECK_NULL_VOID(delegate_);
    std::list<TouchInfo> touchInfos;
    if (!ParseTouchInfo(info, touchInfos)) {
        return;
    }
    for (auto& touchPoint : touchInfos) {
        if (fromOverlay) {
            touchPoint.x -= webOffset_.GetX();
            touchPoint.y -= webOffset_.GetY();
        }
        delegate_->HandleTouchUp(touchPoint.id, touchPoint.x, touchPoint.y, fromOverlay);
    }
}

void WebPattern::HandleTouchMove(const TouchEventInfo& info, bool fromOverlay)
{
    if (isDragging_) {
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(manager);
    if (manager->IsDragged()) {
        return;
    }
    CHECK_NULL_VOID(delegate_);
    std::list<TouchInfo> touchInfos;
    if (!ParseTouchInfo(info, touchInfos)) {
        return;
    }
    for (auto& touchPoint : touchInfos) {
        if (fromOverlay) {
            touchPoint.x -= webOffset_.GetX();
            touchPoint.y -= webOffset_.GetY();
        }
        delegate_->HandleTouchMove(touchPoint.id, touchPoint.x, touchPoint.y, fromOverlay);
    }
}

void WebPattern::HandleTouchCancel(const TouchEventInfo& /*info*/)
{
    CHECK_NULL_VOID(delegate_);
    delegate_->HandleTouchCancel();
}

bool WebPattern::ParseTouchInfo(const TouchEventInfo& info, std::list<TouchInfo>& touchInfos)
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, false);
    auto viewScale = context->GetViewScale();
    if (info.GetChangedTouches().empty()) {
        return false;
    }
    for (const auto& point : info.GetChangedTouches()) {
        TouchInfo touchInfo;
        touchInfo.id = point.GetFingerId();
        const Offset& location = point.GetLocalLocation();
        touchInfo.x = static_cast<float>(location.GetX() * viewScale);
        touchInfo.y = static_cast<float>(location.GetY() * viewScale);
        touchInfos.emplace_back(touchInfo);
    }
    return true;
}

void WebPattern::RequestFullScreen()
{
    isFullScreen_ = true;
}

void WebPattern::ExitFullScreen()
{
    isFullScreen_ = false;
}

bool WebPattern::IsTouchHandleValid(std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> handle)
{
    return (handle != nullptr) && (handle->IsEnable());
}

bool WebPattern::IsTouchHandleShow(std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> handle)
{
    CHECK_NULL_RETURN(handle, false);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    int y = static_cast<int32_t>(handle->GetY() / pipeline->GetDipScale());
    int edgeHeight = static_cast<int32_t>(handle->GetEdgeHeight() / pipeline->GetDipScale()) - 1;
    if (handle->GetAlpha() > 0 && y >= edgeHeight &&
        GreatNotEqual(GetHostFrameSize().value_or(SizeF()).Height(), handle->GetY())) {
        return true;
    }
    return false;
}

WebOverlayType WebPattern::GetTouchHandleOverlayType(std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> insertHandle,
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

std::optional<OffsetF> WebPattern::GetCoordinatePoint()
{
    auto frameNode = GetHost();
    CHECK_NULL_RETURN(frameNode, std::nullopt);
    return frameNode->GetTransformRelativeOffset();
}

RectF WebPattern::ComputeTouchHandleRect(std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> touchHandle)
{
    RectF paintRect;
    auto offset = GetCoordinatePoint().value_or(OffsetF());
    auto size = GetHostFrameSize().value_or(SizeF());
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
        y = y + offset.GetY();
        y = y - edgeHeight;
    }

    x = x - SelectHandleInfo::GetDefaultLineWidth().ConvertToPx() / 2;
    paintRect.SetOffset({ x, y });
    paintRect.SetSize({ SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(), edgeHeight });
    return paintRect;
}

void WebPattern::CloseSelectOverlay()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    if (selectOverlayProxy_) {
        selectOverlayProxy_->Close();
        pipeline->GetSelectOverlayManager()->DestroySelectOverlay(selectOverlayProxy_);
        selectOverlayProxy_ = nullptr;
    }
}

void WebPattern::RegisterSelectOverlayCallback(SelectOverlayInfo& selectInfo,
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params,
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuCallback> callback)
{
    quickMenuCallback_ = callback;
    int32_t flags = params->GetEditStateFlags();
    if (flags & OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_CUT) {
        selectInfo.menuCallback.onCut = [weak = AceType::WeakClaim(this), callback]() {
            CHECK_NULL_VOID(callback);
            callback->Continue(
                OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_CUT, OHOS::NWeb::MenuEventFlags::EF_LEFT_MOUSE_BUTTON);
        };
    } else {
        selectInfo.menuInfo.showCut = false;
    }
    if (flags & OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_COPY) {
        selectInfo.menuCallback.onCopy = [weak = AceType::WeakClaim(this), callback]() {
            CHECK_NULL_VOID(callback);
            callback->Continue(
                OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_COPY, OHOS::NWeb::MenuEventFlags::EF_LEFT_MOUSE_BUTTON);
        };
    } else {
        selectInfo.menuInfo.showCopy = false;
    }
    if (flags & OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_PASTE) {
        selectInfo.menuCallback.onPaste = [weak = AceType::WeakClaim(this), callback]() {
            CHECK_NULL_VOID(callback);
            callback->Continue(
                OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_PASTE, OHOS::NWeb::MenuEventFlags::EF_LEFT_MOUSE_BUTTON);
        };
    } else {
        selectInfo.menuInfo.showPaste = false;
    }
    if (flags & OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_SELECT_ALL) {
        selectInfo.menuCallback.onSelectAll = [weak = AceType::WeakClaim(this), callback]() {
            CHECK_NULL_VOID(callback);
            callback->Continue(OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_SELECT_ALL,
                OHOS::NWeb::MenuEventFlags::EF_LEFT_MOUSE_BUTTON);
        };
    } else {
        selectInfo.menuInfo.showCopyAll = false;
    }
}

void WebPattern::RegisterSelectOverlayEvent(SelectOverlayInfo& selectInfo)
{
    selectInfo.onHandleMoveDone = [weak = AceType::WeakClaim(this)](const RectF& rectF, bool isFirst) {
        auto webPattern = weak.Upgrade();
        CHECK_NULL_VOID(webPattern);
        webPattern->UpdateTouchHandleForOverlay();
        webPattern->SetSelectOverlayDragging(false);
    };
    selectInfo.onTouchDown = [weak = AceType::WeakClaim(this)](const TouchEventInfo& info) {
        auto webPattern = weak.Upgrade();
        CHECK_NULL_VOID(webPattern);
        webPattern->HandleTouchDown(info, true);
    };
    selectInfo.onTouchUp = [weak = AceType::WeakClaim(this)](const TouchEventInfo& info) {
        auto webPattern = weak.Upgrade();
        CHECK_NULL_VOID(webPattern);
        webPattern->HandleTouchUp(info, true);
    };
    selectInfo.onTouchMove = [weak = AceType::WeakClaim(this)](const TouchEventInfo& info) {
        auto webPattern = weak.Upgrade();
        CHECK_NULL_VOID(webPattern);
        if (webPattern->IsSelectOverlayDragging()) {
            webPattern->HandleTouchMove(info, true);
        }
    };
    selectInfo.onHandleMoveStart = [weak = AceType::WeakClaim(this)](bool isFirst) {
        auto webPattern = weak.Upgrade();
        CHECK_NULL_VOID(webPattern);
        webPattern->SetCurrentStartHandleDragging(isFirst);
        webPattern->SetSelectOverlayDragging(true);
    };
}

bool WebPattern::RunQuickMenu(std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params,
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuCallback> callback)
{
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> insertTouchHandle =
        params->GetTouchHandleState(OHOS::NWeb::NWebTouchHandleState::TouchHandleType::INSERT_HANDLE);
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> beginTouchHandle =
        params->GetTouchHandleState(OHOS::NWeb::NWebTouchHandleState::TouchHandleType::SELECTION_BEGIN_HANDLE);
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endTouchHandle =
        params->GetTouchHandleState(OHOS::NWeb::NWebTouchHandleState::TouchHandleType::SELECTION_END_HANDLE);
    WebOverlayType overlayType = GetTouchHandleOverlayType(insertTouchHandle, beginTouchHandle, endTouchHandle);
    if (overlayType == INVALID_OVERLAY) {
        return false;
    }
    if (selectOverlayProxy_) {
        CloseSelectOverlay();
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto theme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_RETURN(theme, false);
    selectHotZone_ = theme->GetHandleHotZoneRadius().ConvertToPx();
    SelectOverlayInfo selectInfo;
    selectInfo.isSingleHandle = (overlayType == INSERT_OVERLAY);
    selectInfo.hitTestMode = HitTestMode::HTMDEFAULT;
    if (selectInfo.isSingleHandle) {
        selectInfo.firstHandle.isShow = IsTouchHandleShow(insertTouchHandle);
        selectInfo.firstHandle.paintRect = ComputeTouchHandleRect(insertTouchHandle);
        selectInfo.secondHandle.isShow = false;
    } else {
        selectInfo.firstHandle.isShow = IsTouchHandleShow(beginTouchHandle);
        selectInfo.firstHandle.paintRect = ComputeTouchHandleRect(beginTouchHandle);
        selectInfo.secondHandle.isShow = IsTouchHandleShow(endTouchHandle);
        selectInfo.secondHandle.paintRect = ComputeTouchHandleRect(endTouchHandle);
    }
    selectInfo.menuInfo.menuIsShow = true;
    RegisterSelectOverlayCallback(selectInfo, params, callback);
    RegisterSelectOverlayEvent(selectInfo);
    selectOverlayProxy_ = pipeline->GetSelectOverlayManager()->CreateAndShowSelectOverlay(selectInfo, WeakClaim(this));
    selectMenuInfo_ = selectInfo.menuInfo;
    insertHandle_ = insertTouchHandle;
    startSelectionHandle_ = beginTouchHandle;
    endSelectionHandle_ = endTouchHandle;
    return selectOverlayProxy_ ? true : false;
}

void WebPattern::OnQuickMenuDismissed()
{
    CloseSelectOverlay();
}

void WebPattern::UpdateSelectHandleInfo()
{
    bool needReverse = IsSelectHandleReverse();
    SelectHandleInfo handleInfo;
    if (!needReverse) {
        if (!isCurrentStartHandleDragging_) {
            handleInfo.isShow = IsTouchHandleShow(startSelectionHandle_);
            handleInfo.paintRect = ComputeTouchHandleRect(startSelectionHandle_);
            selectOverlayProxy_->UpdateFirstSelectHandleInfo(handleInfo);
        } else {
            handleInfo.isShow = IsTouchHandleShow(endSelectionHandle_);
            handleInfo.paintRect = ComputeTouchHandleRect(endSelectionHandle_);
            selectOverlayProxy_->UpdateSecondSelectHandleInfo(handleInfo);
        }
    } else {
        if (!isCurrentStartHandleDragging_) {
            handleInfo.isShow = IsTouchHandleShow(endSelectionHandle_);
            handleInfo.paintRect = ComputeTouchHandleRect(endSelectionHandle_);
            selectOverlayProxy_->UpdateFirstSelectHandleInfo(handleInfo);
        } else {
            handleInfo.isShow = IsTouchHandleShow(startSelectionHandle_);
            handleInfo.paintRect = ComputeTouchHandleRect(startSelectionHandle_);
            selectOverlayProxy_->UpdateSecondSelectHandleInfo(handleInfo);
        }
    }
}

bool WebPattern::IsSelectHandleReverse()
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

void WebPattern::OnTouchSelectionChanged(std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> insertHandle,
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> startSelectionHandle,
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endSelectionHandle)
{
    WebOverlayType overlayType = GetTouchHandleOverlayType(insertHandle, startSelectionHandle, endSelectionHandle);
    if (overlayType == INVALID_OVERLAY) {
        CloseSelectOverlay();
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_VOID(theme);
    selectHotZone_ = theme->GetHandleHotZoneRadius().ConvertToPx();
    insertHandle_ = insertHandle;
    startSelectionHandle_ = startSelectionHandle;
    endSelectionHandle_ = endSelectionHandle;
    if (!selectOverlayProxy_) {
        if (overlayType == INSERT_OVERLAY) {
            SelectOverlayInfo selectInfo;
            selectInfo.isSingleHandle = true;
            selectInfo.firstHandle.isShow = IsTouchHandleShow(insertHandle_);
            selectInfo.firstHandle.paintRect = ComputeTouchHandleRect(insertHandle_);
            selectInfo.secondHandle.isShow = false;
            selectInfo.menuInfo.menuDisable = true;
            selectInfo.menuInfo.menuIsShow = false;
            selectInfo.hitTestMode = HitTestMode::HTMDEFAULT;
            RegisterSelectOverlayEvent(selectInfo);
            selectOverlayProxy_ =
                pipeline->GetSelectOverlayManager()->CreateAndShowSelectOverlay(selectInfo, WeakClaim(this));
        }
    } else {
        if (overlayType == INSERT_OVERLAY) {
            UpdateTouchHandleForOverlay();
        } else {
            UpdateSelectHandleInfo();
        }
    }
}

bool WebPattern::OnCursorChange(const OHOS::NWeb::CursorType& type, const OHOS::NWeb::NWebCursorInfo& info)
{
    (void)info;
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto windowId = pipeline->GetWindowId();
    auto mouseStyle = MouseStyle::CreateMouseStyle();
    int32_t curPointerStyle = 0;
    if (mouseStyle->GetPointerStyle(windowId, curPointerStyle) == -1) {
        return false;
    }
    if ((type == OHOS::NWeb::CursorType::CT_CONTEXTMENU) || (type == OHOS::NWeb::CursorType::CT_ALIAS)) {
        UpdateLocalCursorStyle(windowId, type);
    } else {
        MouseFormat pointStyle = MouseFormat::DEFAULT;
        int64_t idx = BinarySearchFindIndex(g_cursorTypeMap, ArraySize(g_cursorTypeMap), type);
        if (idx >= 0) {
            pointStyle = g_cursorTypeMap[idx].value;
        }
        mouseStyle->SetPointerVisible(pointStyle);
        if (static_cast<int32_t>(pointStyle) != curPointerStyle) {
            mouseStyle->SetPointerStyle(windowId, pointStyle);
        }
    }
    return true;
}

void WebPattern::UpdateLocalCursorStyle(int32_t windowId, const OHOS::NWeb::CursorType& type)
{
    std::shared_ptr<Media::PixelMap> pixelMap;
    auto mouseStyle = MouseStyle::CreateMouseStyle();
    if (type == NWeb::CursorType::CT_CONTEXTMENU) {
        MouseFormat pointStyle = MouseFormat::CONTEXT_MENU;
        pixelMap = CreatePixelMapFromString(IMAGE_POINTER_CONTEXT_MENU_PATH);
        mouseStyle->SetMouseIcon(windowId, pointStyle, pixelMap);
    } else if (type == NWeb::CursorType::CT_ALIAS) {
        MouseFormat pointStyle = MouseFormat::ALIAS;
        pixelMap = CreatePixelMapFromString(IMAGE_POINTER_ALIAS_PATH);
        mouseStyle->SetMouseIcon(windowId, pointStyle, pixelMap);
    }
}

std::shared_ptr<OHOS::Media::PixelMap> WebPattern::CreatePixelMapFromString(const std::string& filePath)
{
    OHOS::Media::SourceOptions opts;
    opts.formatHint = "image/svg+xml";
    uint32_t errCode = 0;
    auto imageSource = OHOS::Media::ImageSource::CreateImageSource(filePath, opts, errCode);
    CHECK_NULL_RETURN(imageSource, nullptr);
    std::set<std::string> formats;
    errCode = imageSource->GetSupportedFormats(formats);
    Media::DecodeOptions decodeOpts;
    std::shared_ptr<OHOS::Media::PixelMap> pixelMap = imageSource->CreatePixelMap(decodeOpts, errCode);
    CHECK_NULL_RETURN(pixelMap, nullptr);

    return pixelMap;
}

void WebPattern::OnSelectPopupMenu(std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuParam> params,
    std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuCallback> callback)
{
    CHECK_NULL_VOID(params);
    CHECK_NULL_VOID(callback);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto id = host->GetId();
    std::vector<SelectParam> selectParam;
    for (auto& item : params->menuItems) {
        selectParam.push_back({
            item.label, ""
        });
    }
    auto menu = MenuView::Create(selectParam, id, host->GetTag());
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto eventHub = host->GetEventHub<WebEventHub>();
    auto destructor = [weak = WeakClaim(this), id]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto pipeline = NG::PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto overlayManager = pipeline->GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        pattern->SetSelectPopupMenuShowing(false);
        overlayManager->DeleteMenu(id);
    };
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDisappear(destructor);

    WebPattern::RegisterSelectPopupCallback(menu, callback, params);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto menuWrapperPattern = menu->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    menuWrapperPattern->RegisterMenuDisappearCallback([weak = WeakClaim(this), callback]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        callback->Cancel();
        pattern->SetSelectPopupMenuShowing(false);
    });
    auto offset = GetSelectPopupPostion(params->bounds);
    selectPopupMenuShowing_ = true;
    overlayManager->ShowMenu(id, offset, menu);
}

void WebPattern::OnDateTimeChooserPopup(const NWeb::DateTimeChooser& chooser,
    const std::vector<NWeb::DateTimeSuggestion>& suggestions,
    std::shared_ptr<NWeb::NWebDateTimeChooserCallback> callback)
{
    bool result = false;
    if (suggestions.size() != 0) {
        result = ShowDateTimeSuggestionDialog(chooser, suggestions, callback);
    } else if (chooser.type == NWeb::DTC_TIME) {
        result = ShowTimeDialog(chooser, suggestions, callback);
    } else {
        result = ShowDateTimeDialog(chooser, suggestions, callback);
    }
    if (!result) {
        callback->Continue(false, OHOS::NWeb::DateTime());
    }
}

DialogProperties WebPattern::GetDialogProperties(const RefPtr<DialogTheme>& theme)
{
    DialogProperties properties;
    if (SystemProperties::GetDeviceType() == DeviceType::PHONE) {
        properties.alignment = DialogAlignment::BOTTOM;
    } else {
        properties.alignment = DialogAlignment::CENTER;
    }
    properties.customStyle = false;
    properties.offset = DimensionOffset(Offset(0, -theme->GetMarginBottom().ConvertToPx()));
    return properties;
}

bool WebPattern::ShowDateTimeDialog(const NWeb::DateTimeChooser& chooser,
    const std::vector<NWeb::DateTimeSuggestion>& suggestions,
    std::shared_ptr<NWeb::NWebDateTimeChooserCallback> callback)
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto pipelineContext = AccessibilityManager::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_RETURN(pipelineContext, false);
    auto executor = pipelineContext->GetTaskExecutor();
    CHECK_NULL_RETURN(executor, false);
    auto context = AccessibilityManager::DynamicCast<NG::PipelineContext>(pipelineContext);
    auto overlayManager = context ? context->GetOverlayManager() : nullptr;
    CHECK_NULL_RETURN(overlayManager, false);
    auto theme = pipelineContext->GetTheme<DialogTheme>();
    CHECK_NULL_RETURN(theme, false);
    NG::DatePickerSettingData settingData;
    settingData.isLunar = false;
    settingData.showTime = chooser.type == NWeb::DTC_DATETIME_LOCAL;
    settingData.useMilitary = true;
    DialogProperties properties = GetDialogProperties(theme);
    std::map<std::string, PickerDate> datePickerProperty;
    std::map<std::string, PickerTime> timePickerProperty;
    settingData.datePickerProperty["start"] = PickerDate(
        chooser.minimum.year, chooser.minimum.month + 1, chooser.minimum.day);
    settingData.datePickerProperty["end"] = PickerDate(
        chooser.maximum.year, chooser.maximum.month + 1, chooser.maximum.day);
    if (chooser.hasSelected) {
        int32_t day = (chooser.dialogValue.day == 0) ? 1 : chooser.dialogValue.day;
        settingData.datePickerProperty["selected"] =
            PickerDate(chooser.dialogValue.year, chooser.dialogValue.month + 1, day);
    }
    std::map<std::string, NG::DialogEvent> dialogEvent;
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    auto acceptId = [callback](const std::string& info) {
        OHOS::NWeb::DateTime result;
        bool success = ParseDateTimeJson(info, result);
        callback->Continue(success, result);
    };
    dialogEvent["acceptId"] = acceptId;
    auto cancelId = [callback](const GestureEvent&) { callback->Continue(false, OHOS::NWeb::DateTime()); };
    dialogCancelEvent["cancelId"] = cancelId;
    overlayManager->RegisterOnHideDialog([callback] { callback->Continue(false, OHOS::NWeb::DateTime()); });
    executor->PostTask(
        [properties, settingData, dialogEvent, dialogCancelEvent, weak = WeakPtr<NG::OverlayManager>(overlayManager)] {
            auto overlayManager = weak.Upgrade();
            CHECK_NULL_VOID(overlayManager);
            overlayManager->ShowDateDialog(properties, settingData, dialogEvent, dialogCancelEvent);
        },
        TaskExecutor::TaskType::UI);
    return true;
}

bool WebPattern::ShowTimeDialog(const NWeb::DateTimeChooser& chooser,
    const std::vector<NWeb::DateTimeSuggestion>& suggestions,
    std::shared_ptr<NWeb::NWebDateTimeChooserCallback> callback)
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto pipelineContext = AccessibilityManager::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_RETURN(pipelineContext, false);
    auto executor = pipelineContext->GetTaskExecutor();
    CHECK_NULL_RETURN(executor, false);
    auto theme = pipelineContext->GetTheme<DialogTheme>();
    CHECK_NULL_RETURN(theme, false);
    auto context = AccessibilityManager::DynamicCast<NG::PipelineContext>(pipelineContext);
    auto overlayManager = context ? context->GetOverlayManager() : nullptr;
    CHECK_NULL_RETURN(overlayManager, false);
    NG::TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = true;
    DialogProperties properties = GetDialogProperties(theme);
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["start"] = PickerTime(chooser.minimum.hour, chooser.minimum.minute, chooser.minimum.second);
    timePickerProperty["selected"] = PickerTime(chooser.maximum.hour, chooser.maximum.minute, chooser.maximum.second);
    if (chooser.hasSelected) {
        timePickerProperty["selected"] =
            PickerTime(chooser.dialogValue.hour, chooser.dialogValue.minute, chooser.dialogValue.second);
    }
    std::map<std::string, NG::DialogEvent> dialogEvent;
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    auto acceptId = [callback](const std::string& info) {
        OHOS::NWeb::DateTime result;
        bool success = ParseDateTimeJson(info, result);
        callback->Continue(success, result);
    };
    dialogEvent["acceptId"] = acceptId;
    auto cancelId = [callback](const GestureEvent&) { callback->Continue(false, OHOS::NWeb::DateTime()); };
    dialogCancelEvent["cancelId"] = cancelId;
    overlayManager->RegisterOnHideDialog([callback] { callback->Continue(false, OHOS::NWeb::DateTime()); });
    executor->PostTask(
        [properties, settingData, timePickerProperty, dialogEvent, dialogCancelEvent,
            weak = WeakPtr<NG::OverlayManager>(overlayManager)] {
            auto overlayManager = weak.Upgrade();
            CHECK_NULL_VOID(overlayManager);
            overlayManager->ShowTimeDialog(properties, settingData, timePickerProperty, dialogEvent, dialogCancelEvent);
        },
        TaskExecutor::TaskType::UI);
    return true;
}

bool WebPattern::ShowDateTimeSuggestionDialog(const NWeb::DateTimeChooser& chooser,
    const std::vector<NWeb::DateTimeSuggestion>& suggestions,
    std::shared_ptr<NWeb::NWebDateTimeChooserCallback> callback)
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto pipelineContext = AccessibilityManager::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_RETURN(pipelineContext, false);
    auto executor = pipelineContext->GetTaskExecutor();
    CHECK_NULL_RETURN(executor, false);
    auto theme = pipelineContext->GetTheme<DialogTheme>();
    CHECK_NULL_RETURN(theme, false);
    auto context = AccessibilityManager::DynamicCast<NG::PipelineContext>(pipelineContext);
    auto overlayManager = context ? context->GetOverlayManager() : nullptr;
    CHECK_NULL_RETURN(overlayManager, false);
    NG::TextPickerSettingData settingData;
    if (memset_s(&settingData, sizeof(NG::TextPickerSettingData), 0, sizeof(NG::TextPickerSettingData)) != EOK) {
        return false;
    }
    std::map<std::string, OHOS::NWeb::DateTime> suggestionMap;
    for (size_t i = 0; i < suggestions.size(); i++) {
        settingData.rangeVector.push_back({ "", suggestions[i].localizedValue });
        settingData.values.push_back(suggestions[i].localizedValue);
        suggestionMap.emplace(std::make_pair(suggestions[i].localizedValue, suggestions[i].value));
    }
    settingData.columnKind = NG::TEXT;
    settingData.selected = chooser.suggestionIndex;
    DialogProperties properties = GetDialogProperties(theme);
    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    auto cancelId = [callback](const GestureEvent&) { callback->Continue(false, OHOS::NWeb::DateTime()); };
    auto acceptId = [suggestionMap, callback](const std::string& info) {
        std::string value = ParseTextJsonValue(info);
        if (suggestionMap.find(value) != suggestionMap.end()) {
            callback->Continue(true, suggestionMap.at(value));
        } else {
            callback->Continue(false, OHOS::NWeb::DateTime());
        }
    };
    dialogEvent["acceptId"] = acceptId;
    dialogCancelEvent["cancelId"] = cancelId;
    overlayManager->RegisterOnHideDialog([callback] { callback->Continue(false, OHOS::NWeb::DateTime()); });
    executor->PostTask(
        [properties, settingData, dialogEvent, dialogCancelEvent, weak = WeakPtr<NG::OverlayManager>(overlayManager)] {
            auto overlayManager = weak.Upgrade();
            CHECK_NULL_VOID(overlayManager);
            overlayManager->ShowTextDialog(properties, settingData, dialogEvent, dialogCancelEvent);
        },
        TaskExecutor::TaskType::UI);
    return true;
}

void WebPattern::OnDateTimeChooserClose() {}

void WebPattern::RegisterSelectPopupCallback(RefPtr<FrameNode>& menu,
    std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuCallback> callback,
    std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuParam> params)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto menuContainer = AceType::DynamicCast<FrameNode>(menu->GetChildAtIndex(0));
    CHECK_NULL_VOID(menuContainer);
    auto menuPattern = menuContainer->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto options = menuPattern->GetOptions();
    for (auto&& option : options) {
        auto selectCallback = [callback](int32_t index) {
            std::vector<int32_t> indices { static_cast<int32_t>(index) };
            callback->Continue(indices);
        };
        auto optionNode = AceType::DynamicCast<FrameNode>(option);
        if (optionNode) {
            auto hub = optionNode->GetEventHub<OptionEventHub>();
            auto optionPattern = optionNode->GetPattern<OptionPattern>();
            if (!hub || !optionPattern) {
                continue;
            }
            hub->SetOnSelect(std::move(selectCallback));
            optionPattern->SetFontSize(Dimension(params->itemFontSize * pipeline->GetDipScale()));
            optionNode->MarkModifyDone();
        }
    }
}

OffsetF WebPattern::GetSelectPopupPostion(const OHOS::NWeb::SelectMenuBound& bounds)
{
    auto offset = GetCoordinatePoint().value_or(OffsetF());
    offset.AddX(bounds.x);
    offset.AddY(bounds.y + bounds.height);
    return offset;
}

void WebPattern::UpdateTouchHandleForOverlay()
{
    WebOverlayType overlayType = GetTouchHandleOverlayType(insertHandle_, startSelectionHandle_, endSelectionHandle_);
    CHECK_NULL_VOID(selectOverlayProxy_);
    if (overlayType == INVALID_OVERLAY) {
        CloseSelectOverlay();
        return;
    }
    SelectHandleInfo firstHandleInfo;
    SelectHandleInfo secondHandleInfo;
    SelectMenuInfo menuInfo;
    if (overlayType == INSERT_OVERLAY) {
        firstHandleInfo.isShow = IsTouchHandleShow(insertHandle_);
        firstHandleInfo.paintRect = ComputeTouchHandleRect(insertHandle_);
        menuInfo.menuDisable = true;
        menuInfo.menuIsShow = false;
        selectOverlayProxy_->UpdateFirstSelectHandleInfo(firstHandleInfo);
        selectOverlayProxy_->UpdateSelectMenuInfo(menuInfo);
    } else {
        firstHandleInfo.isShow = IsTouchHandleShow(startSelectionHandle_);
        firstHandleInfo.paintRect = ComputeTouchHandleRect(startSelectionHandle_);
        secondHandleInfo.isShow = IsTouchHandleShow(endSelectionHandle_);
        secondHandleInfo.paintRect = ComputeTouchHandleRect(endSelectionHandle_);
        selectOverlayProxy_->UpdateFirstSelectHandleInfo(firstHandleInfo);
        selectOverlayProxy_->UpdateSecondSelectHandleInfo(secondHandleInfo);
        selectOverlayProxy_->UpdateSelectMenuInfo(selectMenuInfo_);
        selectOverlayProxy_->SetHandleReverse(false);
    }
}

void WebPattern::UpdateLocale()
{
    CHECK_NULL_VOID(delegate_);
    delegate_->UpdateLocale();
}

void WebPattern::OnWindowShow()
{
    if (isWindowShow_ || !isVisible_) {
        return;
    }

    CHECK_NULL_VOID(delegate_);
    delegate_->ShowWebView();
    isWindowShow_ = true;
}

void WebPattern::OnWindowHide()
{
    if (!isWindowShow_ || !isVisible_) {
        return;
    }

    CHECK_NULL_VOID(delegate_);
    delegate_->HideWebView();
    needOnFocus_ = false;
    isWindowShow_ = false;
}

void WebPattern::OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type) {}

void WebPattern::OnCompleteSwapWithNewSize()
{
    if (!isInWindowDrag_ || !isWaiting_)
        return;

    ACE_SCOPED_TRACE("WebPattern::OnCompleteSwapWithNewSize");
    isWaiting_ = false;
}

void WebPattern::OnResizeNotWork()
{
    if (!isInWindowDrag_ || !isWaiting_)
        return;

    ACE_SCOPED_TRACE("WebPattern::OnResizeNotWork");
    isWaiting_ = false;
}

bool WebPattern::OnBackPressed() const
{
    if (!isFullScreen_) {
        return false;
    }

    CHECK_NULL_RETURN(fullScreenExitHandler_, false);
    auto webFullScreenExitHandler = fullScreenExitHandler_->GetHandler();
    CHECK_NULL_RETURN(webFullScreenExitHandler, false);
    webFullScreenExitHandler->ExitFullScreen();
    return true;
}

void WebPattern::SetFullScreenExitHandler(const std::shared_ptr<FullScreenEnterEvent>& fullScreenExitHandler)
{
    fullScreenExitHandler_ = fullScreenExitHandler;
}

void WebPattern::OnInActive()
{
    if (!isActive_) {
        return;
    }

    CHECK_NULL_VOID(delegate_);
    delegate_->OnInactive();
    isActive_ = false;
}

void WebPattern::OnActive()
{
    if (isActive_) {
        return;
    }

    CHECK_NULL_VOID(delegate_);
    delegate_->OnActive();
    isActive_ = true;
}

void WebPattern::OnVisibleChange(bool isVisible)
{
    if (isVisible_ == isVisible) {
        return;
    }

    isVisible_ = isVisible;
    if (!isVisible_) {
        CloseSelectOverlay();
        if (isVisibleActiveEnable_) {
            OnInActive();
        }
    } else {
        if (isVisibleActiveEnable_) {
            OnActive();
        }
    }
}

void WebPattern::UpdateBackgroundColorRightNow(int32_t color)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateBackgroundColor(Color(static_cast<uint32_t>(color)));
}

void WebPattern::OnNotifyMemoryLevel(int32_t level)
{
    if (!isMemoryLevelEnable_) {
        return;
    }
    CHECK_NULL_VOID(delegate_);
    delegate_->NotifyMemoryLevel(level);
}

int WebPattern::GetWebId()
{
    if (delegate_) {
        return delegate_->GetWebId();
    }
    return -1;
}

ScrollResult WebPattern::HandleScroll(float offset, int32_t source, NestedState state)
{
    auto parent = parent_.Upgrade();
    if (parent) {
        source = isMouseEvent_ ? SCROLL_FROM_AXIS : source;
        return parent->HandleScroll(offset, source, state);
    }
    return { 0.0f, false };
}

bool WebPattern::HandleScrollVelocity(float velocity)
{
    auto parent = parent_.Upgrade();
    CHECK_NULL_RETURN(parent, false);
    if (InstanceOf<SwiperPattern>(parent)) {
        // When scrolling to the previous SwiperItem, that item needs to be visible. Update the offset slightly to make
        // it visible before calling HandleScrollVelocity.
        float tweak = (velocity > 0.0f) ? 1.0f : -1.0f;
        parent->HandleScroll(tweak, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL);
    }
    if (parent->HandleScrollVelocity(velocity)) {
        return true;
    }
    return false;
}

void WebPattern::OnScrollStartRecursive(float position)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::OnScrollStartRecursive");
    auto parent = parent_.Upgrade();
    if (parent) {
        parent->OnScrollStartRecursive(position);
    }
    isFirstFlingScrollVelocity_ = true;
}

void WebPattern::OnScrollEndRecursive()
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::OnScrollEndRecursive");
    auto parent = parent_.Upgrade();
    if (parent) {
        parent->OnScrollEndRecursive();
    }
}

void WebPattern::OnOverScrollFlingVelocity(float xVelocity, float yVelocity, bool isFling)
{
    float velocity = GetAxis() == Axis::HORIZONTAL ? xVelocity : yVelocity;
    if (!isFling) {
        if (scrollState_ && ((velocity < 0 && nestedScrollForwardMode_ == NestedScrollMode::SELF_FIRST) ||
                                (velocity > 0 && nestedScrollBackwardMode_ == NestedScrollMode::SELF_FIRST))) {
            HandleScroll(-velocity, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL);
        }
    } else {
        if (((velocity > 0 && nestedScrollForwardMode_ == NestedScrollMode::SELF_FIRST) ||
                (velocity < 0 && nestedScrollBackwardMode_ == NestedScrollMode::SELF_FIRST))) {
            if (isFirstFlingScrollVelocity_) {
                HandleScrollVelocity(velocity);
                isFirstFlingScrollVelocity_ = false;
            }
        }
    }
}

void WebPattern::OnScrollState(bool scrollState)
{
    scrollState_ = scrollState;
    if (!scrollState) {
        OnScrollEndRecursive();
    }
}

Axis WebPattern::GetParentAxis()
{
    auto parent = WebSearchParent();
    parent_ = parent;
    CHECK_NULL_RETURN(parent, Axis::HORIZONTAL);
    axis_ = parent->GetAxis();
    return axis_;
}

RefPtr<NestableScrollContainer> WebPattern::WebSearchParent()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    for (auto parent = host->GetParent(); parent != nullptr; parent = parent->GetParent()) {
        RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(parent);
        if (!frameNode) {
            continue;
        }
        auto pattern = frameNode->GetPattern<NestableScrollContainer>();
        if (!pattern) {
            continue;
        }
        return pattern;
    }
    return nullptr;
}

void WebPattern::OnRootLayerChanged(int width, int height)
{
    rootLayerWidth_ = width;
    rootLayerHeight_ = height;
    if (layoutMode_ == WebLayoutMode::FIT_CONTENT) {
        auto frameNode = GetHost();
        CHECK_NULL_VOID(frameNode);
        auto newRect = Size(width, height);
        drawSize_.SetSize(newRect);
        frameNode->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT | PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
        auto offset = Offset(GetCoordinatePoint()->GetX(), GetCoordinatePoint()->GetY());
        delegate_->SetBoundsOrResize(drawSize_, offset, false);
    }
}

void WebPattern::SetNestedScroll(const NestedScrollOptions& nestedOpt)
{
    nestedScrollForwardMode_ = nestedOpt.forward;
    nestedScrollBackwardMode_ = nestedOpt.backward;
}

bool WebPattern::FilterScrollEvent(const float x, const float y, const float xVelocity, const float yVelocity)
{
    float offset = GetAxis() == Axis::HORIZONTAL ? x : y;
    float velocity = GetAxis() == Axis::HORIZONTAL ? xVelocity : yVelocity;
    if (((offset > 0 || velocity > 0) && nestedScrollForwardMode_ == NestedScrollMode::PARENT_FIRST) ||
        ((offset < 0 || velocity < 0) && nestedScrollBackwardMode_ == NestedScrollMode::PARENT_FIRST)) {
        if (offset != 0) {
            auto result = HandleScroll(offset, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL);
            CHECK_NULL_RETURN(delegate_, false);
            GetAxis() == Axis::HORIZONTAL ? delegate_->ScrollBy(-result.remain, 0)
                                          : delegate_->ScrollBy(0, -result.remain);
            return true;
        } else {
            return HandleScrollVelocity(velocity);
        }
    } else if (((offset > 0 || velocity > 0) && nestedScrollForwardMode_ == NestedScrollMode::PARALLEL) ||
               ((offset < 0 || velocity < 0) && nestedScrollBackwardMode_ == NestedScrollMode::PARALLEL)) {
        if (offset != 0) {
            HandleScroll(offset, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL);
        } else {
            HandleScrollVelocity(velocity);
        }
    }
    return false;
}

RefPtr<ScrollPattern> WebPattern::SearchParent()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    if (isParentHasScroll_) {
        relativeOffsetOfScroll_.Reset();
    }
    relativeOffsetOfScroll_ += host->GetGeometryNode()->GetFrameOffset();
    for (auto parent = host->GetParent(); parent != nullptr; parent = parent->GetParent()) {
        RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(parent);
        if (!frameNode) {
            continue;
        }
        auto pattern = frameNode->GetPattern<ScrollPattern>();
        if (!pattern) {
            relativeOffsetOfScroll_ += frameNode->GetGeometryNode()->GetFrameOffset();
            continue;
        }
        isParentHasScroll_ = true;
        return pattern;
    }
    isParentHasScroll_ = false;
    return nullptr;
}

void WebPattern::InitScrollUpdateListener()
{
    std::shared_ptr<ScrollUpdateListener> listener = std::make_shared<ScrollUpdateListener>();
    listener->SetPatternToListener(AceType::WeakClaim(this));
    auto pattern = SearchParent();
    CHECK_NULL_VOID(pattern);
    TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern registerScrollUpdateListener");
    pattern->registerScrollUpdateListener(listener);
    axis_ = pattern->GetAxis();
}

void WebPattern::UpdateScrollOffset(SizeF frameSize)
{
    if (isParentHasScroll_) {
        SearchParent();
        switch (axis_) {
            case Axis::HORIZONTAL:
                CalculateHorizontalDrawRect(frameSize);
                break;
            case Axis::VERTICAL:
                CalculateVerticalDrawRect(frameSize);
                break;
            default :
                break;
        }
    }
}

void WebPattern::CalculateHorizontalDrawRect(SizeF frameSize) {}

void WebPattern::CalculateVerticalDrawRect(SizeF frameSize)
{
    if (relativeOffsetOfScroll_.GetY() >= 0) {
        return;
    }

    int32_t stepGear = (-relativeOffsetOfScroll_.GetY()) / DEFAULT_WEB_DRAW_HEIGHT;
    if (stepGear >= static_cast<int32_t>(DEFAULT_HEIGHT_GEAR.size())) {
        TAG_LOGE(AceLogTag::ACE_WEB, "stepGear out of DEFAULT_HEIGHT_GEAR orign");
        return;
    }
    int32_t height = DEFAULT_HEIGHT_GEAR[stepGear];
    int32_t y = DEFAULT_ORIGN_GEAR[stepGear];
    CHECK_NULL_VOID(renderSurface_);
    renderSurface_->SetWebMessage({ 0, y });

    SetDrawRect(relativeOffsetOfScroll_.GetX(), -y, frameSize.Width(), height);
}

void WebPattern::PostTaskToUI(const std::function<void()>&& task) const
{
    CHECK_NULL_VOID(task);
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto pipelineContext = AccessibilityManager::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_VOID(pipelineContext);
    auto taskExecutor = pipelineContext->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(task, TaskExecutor::TaskType::UI);
}

void WebPattern::SetDrawRect(int32_t x, int32_t y, int32_t width, int32_t height)
{
    CHECK_NULL_VOID(delegate_);
    delegate_->SetDrawRect(x, -y, width, height);
}

RefPtr<NodePaintMethod> WebPattern::CreateNodePaintMethod()
{
    auto paint = MakeRefPtr<WebPaintMethod>(renderSurface_);
    return paint;
}

void WebPattern::JavaScriptOnDocumentStart(const ScriptItems& scriptItems)
{
    onDocumentStartScriptItems_ = std::make_optional<ScriptItems>(scriptItems);
    if (delegate_) {
        UpdateJavaScriptOnDocumentStart();
        delegate_->JavaScriptOnDocumentStart();
    }
}

void WebPattern::JavaScriptOnDocumentEnd(const ScriptItems& scriptItems)
{
    onDocumentEndScriptItems_ = std::make_optional<ScriptItems>(scriptItems);
    if (delegate_) {
        UpdateJavaScriptOnDocumentEnd();
        delegate_->JavaScriptOnDocumentEnd();
    }
}

void WebPattern::UpdateJavaScriptOnDocumentStart()
{
    if (delegate_ && onDocumentStartScriptItems_.has_value()) {
        delegate_->SetJavaScriptItems(onDocumentStartScriptItems_.value(), ScriptItemType::DOCUMENT_START);
        onDocumentStartScriptItems_ = std::nullopt;
    }
}

void WebPattern::UpdateJavaScriptOnDocumentEnd()
{
    if (delegate_ && onDocumentEndScriptItems_.has_value()) {
        delegate_->SetJavaScriptItems(onDocumentEndScriptItems_.value(), ScriptItemType::DOCUMENT_END);
        onDocumentEndScriptItems_ = std::nullopt;
    }
}

RefPtr<WebAccessibilityNode> WebPattern::GetAccessibilityNodeById(int32_t accessibilityId)
{
    CHECK_NULL_RETURN(delegate_, nullptr);
    CHECK_NULL_RETURN(webAccessibilityNode_, nullptr);
    auto& info = webAccessibilityNode_->GetAccessibilityNodeInfo();
    if (!delegate_->GetAccessibilityNodeInfoById(accessibilityId, info)) {
        return nullptr;
    }
    SetSelfAsParentOfWebCoreNode(info);
    return webAccessibilityNode_;
}

RefPtr<WebAccessibilityNode> WebPattern::GetFocusedAccessibilityNode(int32_t accessibilityId, bool isAccessibilityFocus)
{
    CHECK_NULL_RETURN(delegate_, nullptr);
    CHECK_NULL_RETURN(webAccessibilityNode_, nullptr);
    auto& info = webAccessibilityNode_->GetAccessibilityNodeInfo();
    if (!delegate_->GetFocusedAccessibilityNodeInfo(accessibilityId, isAccessibilityFocus, info)) {
        return nullptr;
    }
    SetSelfAsParentOfWebCoreNode(info);
    return webAccessibilityNode_;
}

RefPtr<WebAccessibilityNode> WebPattern::GetAccessibilityNodeByFocusMove(int32_t accessibilityId, int32_t direction)
{
    CHECK_NULL_RETURN(delegate_, nullptr);
    CHECK_NULL_RETURN(webAccessibilityNode_, nullptr);
    auto& info = webAccessibilityNode_->GetAccessibilityNodeInfo();
    if (!delegate_->GetAccessibilityNodeInfoByFocusMove(accessibilityId, direction, info)) {
        return nullptr;
    }
    SetSelfAsParentOfWebCoreNode(info);
    return webAccessibilityNode_;
}


void WebPattern::ExecuteAction(int32_t nodeId, AceAction action) const
{
    CHECK_NULL_VOID(delegate_);
    delegate_->ExecuteAction(nodeId, action);
}

void WebPattern::SetAccessibilityState(bool state)
{
    CHECK_NULL_VOID(delegate_);
    if (accessibilityState_ != state) {
        accessibilityState_ = state;
        delegate_->SetAccessibilityState(state);
    }
}

void WebPattern::SetSelfAsParentOfWebCoreNode(NWeb::NWebAccessibilityNodeInfo& info) const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (info.parentId == -1) { // root node of web core
        info.parentId = host->GetAccessibilityId();
    }
}
} // namespace OHOS::Ace::NG
