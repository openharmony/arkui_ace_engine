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

#include "core/components/calendar/calendar_element.h"

#include "base/i18n/localization.h"
#include "core/common/ace_application_info.h"
#include "core/components/calendar/calendar_component.h"
#include "core/components/calendar/render_calendar.h"
#include "core/components/display/render_display.h"
#include "core/components/text/text_element.h"

namespace OHOS::Ace {

void CalendarElement::PerformBuild()
{
    RefPtr<CalendarComponent> calendar = AceType::DynamicCast<CalendarComponent>(component_);
    if (!calendar) {
        LOGE("Can not dynamicCast to CalendarComponent!");
        return;
    }

    if (!calendarController_) {
        calendarController_ = AceType::MakeRefPtr<CalendarController>(calendar->GetDataAdapterAction(), context_);
        UpdateAttr(calendar);
        calendarController_->Initialize();
    } else {
        UpdateAttr(calendar);
        return;
    }

    const auto& child = children_.empty() ? nullptr : children_.front();
    auto newComponent = calendar->Build(GetContext(), calendarController_);
    auto element = UpdateChild(child, newComponent);
    if (calendar->IsCardCalendar()) {
        BuildCardCalendar(calendar, element);
        element = element->GetChildren().back();
    }

    auto swiperElement = AceType::DynamicCast<SwiperElement>(element);

    calendarController_->SetRequestFocusImpl([weak = WeakClaim(this)]() {
        auto element = weak.Upgrade();
        if (!element) {
            return;
        }
        element->RequestFocus();
    });
    if (swiperElement) {
        renderSwiper_ = AceType::DynamicCast<RenderSwiper>(swiperElement->GetRenderNode());
        if (renderSwiper_) {
            calendarController_->SetRenderSwiper(renderSwiper_);
        }
    }

    RequestFocusImmediately();
}

void CalendarElement::BuildCardCalendar(const RefPtr<CalendarComponent>& calendar, const RefPtr<Element>& element)
{
    if (!element || !element->GetChildren().front()) {
        return;
    }
    auto children = element->GetChildren().front()->GetChildren();
    int32_t index = 0;
    RefPtr<Element> box;
    for (const auto& item : children) {
        if (index == 0) {
            SetArrowImage(item, true);
        }
        if (index == 1) {
            box = item;
        }
        if (index == 2) {
            SetArrowImage(item, false);
        }
        ++index;
    }
    auto text = AceType::DynamicCast<TextElement>(box->GetChildren().front());
    if (text) {
        auto renderText = AceType::DynamicCast<RenderText>(text->GetRenderNode());
        calendarController_->SetCardTitle(renderText);
        auto buttonCallback = [weak = WeakClaim(RawPtr(calendar)), text = WeakClaim(RawPtr(renderText)),
                                  weakController = WeakClaim(RawPtr(calendarController_))](bool pre) {
            auto calendar = weak.Upgrade();
            auto controller = weakController.Upgrade();
            if (controller) {
                auto swiper = controller->GetRenderSwiper();
                if (swiper && swiper->GetMoveStatus()) {
                    return;
                }
            }
            if (!calendar) {
                return;
            }
            pre ? calendar->GetCalendarController()->GoToPrevMonth(1)
                : calendar->GetCalendarController()->GoToNextMonth(1);
            auto renderText = text.Upgrade();
            if (renderText) {
                DateTime dateTime;
                dateTime.year = calendar->GetCalendarController()->GetCurrentMonth().year;
                dateTime.month = calendar->GetCalendarController()->GetCurrentMonth().month;
                auto date = Localization::GetInstance()->FormatDateTime(dateTime, "yyyyMMM");
                auto textComponent = AceType::MakeRefPtr<TextComponent>(date);
                auto cardTheme = renderText->GetTheme<CalendarTheme>();
                if (!cardTheme) {
                    return;
                }
                TextStyle style;
                style.SetFontSize(cardTheme->GetCardCalendarTheme().titleFontSize);
                style.SetTextColor(cardTheme->GetCardCalendarTheme().titleTextColor);
                style.SetFontWeight(FontWeight::W500);
                textComponent->SetTextStyle(style);
                renderText->Update(textComponent);
                renderText->MarkNeedLayout();
            }
        };
        BackEndEventManager<void()>::GetInstance().BindBackendEvent(calendar->GetPreClickId(), [buttonCallback]() {
            AceApplicationInfo::GetInstance().IsRightToLeft() ? buttonCallback(false) : buttonCallback(true);
        });
        BackEndEventManager<void()>::GetInstance().BindBackendEvent(calendar->GetNextClickId(), [buttonCallback]() {
            AceApplicationInfo::GetInstance().IsRightToLeft() ? buttonCallback(true) : buttonCallback(false);
        });
    }
}

void CalendarElement::UpdateAttr(const RefPtr<CalendarComponent>& calendar)
{
    auto dataAdapter = calendarController_->GetDataAdapter();
    if (!dataAdapter) {
        return;
    }
    if (calendar->IsSetToday()) {
        auto today = dataAdapter->GetToday();
        auto date = calendar->GetDate();
        if (today.day != date.day || today.month != date.month) {
            calendarController_->SetToday(date);
            calendarController_->GoTo(date.month.year, date.month.month, date.day);
            calendarController_->UpdateTitle(date);
        }
    }
    CardCalendarAttr attr;
    attr.startDayOfWeek = calendar->GetStartDayOfWeek();
    attr.showLunar = calendar->IsShowLunar();
    attr.textDirection = calendar->GetTextDirection();
    attr.cardCalendar = calendar->IsCardCalendar();
    attr.requestData = calendar->GetRequestDataEvent();
    attr.showHoliday = calendar->GetShowHoliday();
    attr.offDays = calendar->GetOffDays();
    dataAdapter->UpdateCardCalendarAttr(attr);
}

void CalendarElement::SetArrowImage(const RefPtr<Element>& element, bool isLeft)
{
    if (!element) {
        return;
    }
    auto imageElement = element->GetChildren().front();
    if (!imageElement) {
        return;
    }
    auto image = AceType::DynamicCast<RenderImage>(imageElement->GetRenderNode());
    if (image) {
        isLeft ? calendarController_->SetLeftRowImage(image) : calendarController_->SetRightRowImage(image);
    }
}

void CalendarMonthElement::Update()
{
    RenderElement::Update();
}

bool CalendarMonthElement::OnKeyEvent(const KeyEvent& keyEvent)
{
    if (keyEvent.action != KeyAction::UP) {
        return false;
    }

    auto display = AceType::DynamicCast<RenderDisplay>(renderNode_->GetParent().Upgrade());
    if (display) {
        auto swiper = AceType::DynamicCast<RenderSwiper>(display->GetParent().Upgrade());
        if (swiper) {
            if (swiper->GetMoveStatus()) {
                return true;
            }
        }
    }

    switch (keyEvent.code) {
        case KeyCode::TV_CONTROL_UP:
            return RequestNextFocus(true, true, GetRect());
        case KeyCode::TV_CONTROL_DOWN:
            return RequestNextFocus(true, false, GetRect());
        case KeyCode::TV_CONTROL_LEFT:
            return RequestNextFocus(false, true, GetRect());
        case KeyCode::TV_CONTROL_RIGHT:
            return RequestNextFocus(false, false, GetRect());
        case KeyCode::KEYBOARD_TAB:
            return RequestNextFocus(false, false, GetRect()) || RequestNextFocus(true, false, GetRect());
        default:
            return false;
    }
}

bool CalendarMonthElement::RequestNextFocus(bool vertical, bool reverse, const Rect& rect)
{
    RefPtr<FocusableGrid> focusableGrid = AceType::DynamicCast<FocusableGrid>(renderNode_);
    if (!focusableGrid) {
        LOGE("focusable grid is null.");
        return false;
    }
    bool needFocus = focusableGrid->RequestNextFocus(vertical, reverse) >= 0;
    if (needFocus) {
        auto calendar = DynamicCast<RenderCalendar>(renderNode_);
        if (!calendar) {
            LOGE("get render node failed");
            return false;
        }
        calendar->MarkNeedRender();
    }
    return needFocus;
}

void CalendarMonthElement::OnFocus()
{
    if (renderNode_) {
        renderNode_->ChangeStatus(RenderStatus::FOCUS);
    }
}

void CalendarMonthElement::OnBlur()
{
    if (renderNode_) {
        renderNode_->ChangeStatus(RenderStatus::BLUR);
    }
}

} // namespace OHOS::Ace
