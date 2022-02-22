/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/components/web/render_web.h"

#include <iomanip>
#include <sstream>

#include "base/log/log.h"
#include "core/components/web/resource/web_resource.h"
#include "core/event/ace_event_helper.h"

namespace OHOS::Ace {

RenderWeb::RenderWeb() : RenderNode(true)
{
#ifdef OHOS_STANDARD_SYSTEM
    Initialize();
#endif
}

void RenderWeb::OnAttachContext()
{
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("OnAttachContext context null");
        return;
    }
    if (delegate_) {
        // web component is displayed in full screen by default.
        drawSize_ = Size(pipelineContext->GetRootWidth(), pipelineContext->GetRootHeight());
        position_ = Offset(0, 0);
#ifdef OHOS_STANDARD_SYSTEM
        delegate_->InitOHOSWeb(context_);
#else
        delegate_->CreatePlatformResource(drawSize_, position_, context_);
#endif
    }
}

void RenderWeb::Update(const RefPtr<Component>& component)
{
    const RefPtr<WebComponent> web = AceType::DynamicCast<WebComponent>(component);
    if (!web) {
        LOGE("WebComponent is null");
        return;
    }

    if (!component) {
        return;
    }
    MarkNeedLayout();
}

void RenderWeb::PerformLayout()
{
    if (!NeedLayout()) {
        LOGI("RenderWeb::PerformLayout No Need to Layout");
        return;
    }

    // render web do not support child.
    drawSize_ = Size(GetLayoutParam().GetMaxSize().Width(),
                     (GetLayoutParam().GetMaxSize().Height() == Size::INFINITE_SIZE) ?
                     Size::INFINITE_SIZE :
                     (GetLayoutParam().GetMaxSize().Height()));
    SetLayoutSize(drawSize_);
    SetNeedLayout(false);
    MarkNeedRender();
}

void RenderWeb::OnSizeChanged()
{
#ifdef OHOS_STANDARD_SYSTEM
    if (delegate_) {
        delegate_->Resize(drawSize_.Width(), drawSize_.Height());
        if (!isUrlLoaded_) {
            delegate_->LoadUrl();
            isUrlLoaded_ = true;
        }
    }
#endif
}

#ifdef OHOS_STANDARD_SYSTEM
void RenderWeb::Initialize()
{
    touchRecognizer_ = AceType::MakeRefPtr<RawRecognizer>();
    touchRecognizer_->SetOnTouchDown([weakItem = AceType::WeakClaim(this)](const TouchEventInfo& info) {
        auto item = weakItem.Upgrade();
        if (item) {
            item->HandleTouch(true, info);
        }
    });
    touchRecognizer_->SetOnTouchUp([weakItem = AceType::WeakClaim(this)](const TouchEventInfo& info) {
        auto item = weakItem.Upgrade();
        if (item) {
            item->HandleTouch(false, info);
        }
    });
    touchRecognizer_->SetOnTouchMove([weakItem = AceType::WeakClaim(this)](const TouchEventInfo& info) {
        auto item = weakItem.Upgrade();
        if (item) {
            item->HandleTouchMove(info);
        }
    });
    touchRecognizer_->SetOnTouchCancel([weakItem = AceType::WeakClaim(this)](const TouchEventInfo& info) {
        auto item = weakItem.Upgrade();
        if (item) {
            item->HandleTouchCancel(info);
        }
    });
}

void RenderWeb::HandleTouch(const bool& isPress, const TouchEventInfo& info)
{
    if (!delegate_) {
        LOGE("Touch delegate_ is nullprt");
        return;
    }
    TouchInfo touchInfo;
    if (!ParseTouchInfo(info, touchInfo)) {
        LOGE("Touch error");
        return;
    }
    if (isPress) {
        delegate_->HandleTouchDown(touchInfo.id, touchInfo.x, touchInfo.y);
    } else {
        delegate_->HandleTouchUp(touchInfo.id, touchInfo.x, touchInfo.y);
    }
}

void RenderWeb::HandleTouchMove(const TouchEventInfo& info)
{
    if (info.GetTouches().empty()) {
        LOGE("Touch move getTouches is empty");
        return;
    }
    if (!delegate_) {
        LOGE("Touch move delegate_ is nullprt");
        return;
    }
    TouchInfo touchInfo;
    if (!ParseTouchInfo(info, touchInfo)) {
        LOGE("Touch move error");
        return;
    }
    delegate_->HandleTouchMove(touchInfo.id, touchInfo.x, touchInfo.y);
}

void RenderWeb::HandleTouchCancel(const TouchEventInfo& info)
{
    if (info.GetTouches().empty()) {
        LOGE("Touch cancel getTouches is empty");
        return;
    }
    if (!delegate_) {
        LOGE("Touch cancel delegate_ is nullprt");
        return;
    }
    delegate_->HandleTouchCancel();
}

bool RenderWeb::ParseTouchInfo(const TouchEventInfo& touchEventInfo, TouchInfo& touchInfo)
{
    auto context = context_.Upgrade();
    if (!context) {
        return false;
    }

    constexpr int invalidFingerID = -1;
    TouchLocationInfo info{invalidFingerID};
    if (!touchEventInfo.GetTouches().empty()) {
        info = touchEventInfo.GetTouches().front();
    } else if (!touchEventInfo.GetChangedTouches().empty()) {
        info = touchEventInfo.GetChangedTouches().front();
    } else {
        return false;
    }
    auto viewScale = context->GetViewScale();
    touchInfo.id = info.GetFingerId();
    Offset location = info.GetLocalLocation();
    touchInfo.x = location.GetX() * viewScale;
    touchInfo.y = location.GetY() * viewScale;
    LOGD("touch id:%{private}d, x:%{private}lf, y:%{private}lf", touchInfo.id, touchInfo.x, touchInfo.y);
    return true;
}

void RenderWeb::OnTouchTestHit(const Offset& coordinateOffset, const TouchRestrict& touchRestrict,
    TouchTestResult& result)
{
    if (!touchRecognizer_) {
        LOGE("TouchTestHit touchRecognizer_ is nullprt");
        return;
    }
    touchRecognizer_->SetCoordinateOffset(coordinateOffset);
    result.emplace_back(touchRecognizer_);
}
#endif
} // namespace OHOS::Ace
