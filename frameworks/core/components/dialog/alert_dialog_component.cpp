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

#include "core/components/dialog/alert_dialog_component.h"

#include "core/components/scroll/scroll_component.h"

namespace OHOS::Ace {
namespace {

const Dimension BUTTON_SPACING = 22.0_vp;

} // namespace

void AlertDialogComponent::BuildChild(const RefPtr<ThemeManager>& themeManager)
{
    if (!themeManager) {
        return;
    }
    dialogTheme_ = AceType::DynamicCast<DialogTheme>(themeManager->GetTheme(DialogTheme::TypeId()));
    if (!dialogTheme_) {
        return;
    }
    if (!isDeviceTypeSet_) {
        deviceType_ = SystemProperties::GetDeviceType();
    }
    auto box = AceType::MakeRefPtr<BoxComponent>();
    auto backDecoration = AceType::MakeRefPtr<Decoration>();
    backDecoration->SetBackgroundColor(Color::FromString("#333333"));
    Border border;
    border.SetBorderRadius(Radius(48.0_vp, 48.0_vp));
    backDecoration->SetBorder(border);
    if (deviceType_ == DeviceType::WATCH) {
        box->SetFlex(BoxFlex::FLEX_XY);
    } else {
        box->SetFlex(BoxFlex::FLEX_X);
    }
    box->SetBackDecoration(backDecoration);
    bool isLimit = true;
    if (height_.IsValid()) {
        box->SetHeight(height_.Value(), height_.Unit());
        isLimit = false;
    }
    if (width_.IsValid()) {
        box->SetWidth(width_.Value(), width_.Unit());
        isLimit = false;
    }
    if (isSetMargin_) {
        box->SetMargin(margin_);
    }
    auto transition = BuildAnimation(box);
    BuildDialogTween(transition, isLimit, margin_);

    auto focusCollaboration = AceType::MakeRefPtr<FocusCollaborationComponent>();
    if (!HasCustomChild()) {
        std::list<RefPtr<Component>> columnChildren;
        auto column = AceType::MakeRefPtr<ColumnComponent>(FlexAlign::FLEX_START, FlexAlign::CENTER, columnChildren);
        column->SetMainAxisSize(MainAxisSize::MIN);
        BuildTitle(column);
        BuildContent(column);
        if (isMenu_) {
            BuildMenu(column);
        } else {
            BuildActions(themeManager, column);
        }
        BuildFocusChild(column, focusCollaboration);
    } else {
        // build custom child
        BuildFocusChild(customComponent_, focusCollaboration);
    }
    if (deviceType_ == DeviceType::WATCH) {
        auto scroll = AceType::MakeRefPtr<ScrollComponent>(focusCollaboration);
        box->SetChild(scroll);
    } else {
        box->SetChild(focusCollaboration);
    }
    box->SetTextDirection(GetTextDirection());
}

void AlertDialogComponent::BuildContent(const RefPtr<ColumnComponent>& column)
{
    if (!content_) {
        return;
    }
    auto contentPadding = AceType::MakeRefPtr<PaddingComponent>();
    if (contentPadding_ == Edge::NONE) {
        if (!title_) {
            contentPadding_ = actions_.empty() ? dialogTheme_->GetDefaultPadding() : dialogTheme_->GetAdjustPadding();
        } else {
            contentPadding_ =
                actions_.empty() ? dialogTheme_->GetContentDefaultPadding() : dialogTheme_->GetContentAdjustPadding();
        }
    }
    contentPadding_ = Edge(64.0_vp, 36.0_vp, 64.0_vp, 68.0_vp);
    contentPadding->SetPadding(std::move(contentPadding_));
    RefPtr<FlexItemComponent> contentFlex;
    if (deviceType_ == DeviceType::WATCH) {
        contentPadding->SetChild(content_);
        contentFlex = AceType::MakeRefPtr<FlexItemComponent>(0, 0, 0.0, contentPadding);
    } else {
        auto scroll = AceType::MakeRefPtr<ScrollComponent>(content_);
        contentPadding->SetChild(scroll);
        contentFlex = AceType::MakeRefPtr<FlexItemComponent>(0, 1, 0.0, contentPadding);
    }
    column->AppendChild(GenerateComposed("dialogContent", contentFlex, true));
}

void AlertDialogComponent::BuildActions(const RefPtr<ThemeManager>& themeManager, const RefPtr<ColumnComponent>& column)
{
    if (actions_.empty()) {
        LOGW("the action is empty");
        return;
    }

    // Bind success event between button and dialog.
    BackEndEventManager<void(int32_t)>::GetInstance().BindBackendEvent(
        onSuccessId_, [properties = properties_, context = context_](int32_t successType) {
            if (successType == 0) {
                auto func = AceAsyncEvent<void()>::Create(
                    properties.primaryId.IsEmpty() ? properties.secondaryId : properties.primaryId, context);
                if (func) {
                    func();
                }
            } else if (successType == 1) {
                auto func = AceAsyncEvent<void()>::Create(properties.secondaryId, context);
                if (func) {
                    func();
                }
            }
        });

    auto actionsPadding = AceType::MakeRefPtr<PaddingComponent>();
    actionsPadding->SetPadding(Edge(64.0_vp, 0.0_vp, 64.0_vp, 32.0_vp));
    if (actions_.size() == 1) { // the button in dialog is one.
        std::list<RefPtr<Component>> rowChildren;
        auto row = AceType::MakeRefPtr<RowComponent>(FlexAlign::SPACE_AROUND, FlexAlign::FLEX_START, rowChildren);
        row->SetStretchToParent(true);
        row->AppendChild(AceType::MakeRefPtr<FlexItemComponent>(
            1, 1, 0.0, BuildButton(actions_.front(), onPositiveSuccessId_, Edge::NONE, true)));
        actionsPadding->SetChild(row);
    } else if (actions_.size() == 2) { // the button in dialog is two.
        std::list<RefPtr<Component>> rowChildren;
        auto row = AceType::MakeRefPtr<RowComponent>(FlexAlign::SPACE_AROUND, FlexAlign::CENTER, rowChildren);
        row->SetStretchToParent(true);
        row->AppendChild(AceType::MakeRefPtr<FlexItemComponent>(
            1, 1, 0.0, BuildButton(actions_.front(), onPositiveSuccessId_, Edge::NONE)));
        auto padding = AceType::MakeRefPtr<PaddingComponent>();
        padding->SetPadding(Edge(BUTTON_SPACING, 0.0_vp, 0.0_vp, 0.0_vp));
        row->AppendChild(AceType::MakeRefPtr<FlexItemComponent>(0, 0, 0.0, padding));
        row->AppendChild(AceType::MakeRefPtr<FlexItemComponent>(
            1, 1, 0.0, BuildButton(actions_.back(), onNegativeSuccessId_, Edge::NONE, true)));
        actionsPadding->SetChild(row);
    }
    auto actionsFlex = AceType::MakeRefPtr<FlexItemComponent>(0, 0, 0.0, actionsPadding);
    column->AppendChild(actionsFlex);
}

} // namespace OHOS::Ace