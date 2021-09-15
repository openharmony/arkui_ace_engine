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

#include "core/components/rich_text/render_rich_text.h"

#include <iomanip>
#include <sstream>

#include "base/log/log.h"
#include "core/event/ace_event_helper.h"

namespace OHOS::Ace {

void RenderRichText::Update(const RefPtr<Component>& component)
{
    if (!component || !delegate_) {
        return;
    }

    const RefPtr<RichTextComponent> richText = AceType::DynamicCast<RichTextComponent>(component);
    if (!richText) {
        LOGE("RenderRichText update dynamicCast to nullptr error");
        return;
    }

    auto& declaration = richText->GetDeclaration();
    if (declaration && declaration->HasDisplayStyle()) {
        bool visible = true;
        auto& style = static_cast<CommonVisibilityStyle&>(declaration->GetStyle(StyleTag::COMMON_VISIBILITY_STYLE));
        if (style.IsValid()) {
            visible = style.visibility == VisibilityType::VISIBLE ? true : false;
        }

        if (isVisible_ != visible) {
            isVisible_ = visible;
            if (hasCreateWeb_) {
                delegate_->ChangeRichTextVisibility(isVisible_);
            }
        }
    }
    if (!hasCreateWeb_) {
        CreateRealWeb(0, 0, isVisible_);
    }

    drawSize_.SetWidth(webContentWidth_);
    drawSize_.SetHeight(webContentHeight_);

    MarkNeedLayout(true, true);
}

void RenderRichText::CreateRealWeb(int32_t top, int32_t left, bool visible, bool reCreate)
{
    if (reCreate) {
        delegate_->ReleasePlatformResource();
        delegate_->CreatePlatformResource(context_, top, left, visible);
        return;
    }

    hasCreateWeb_ = true;
    delegate_->CreatePlatformResource(context_, top, left, visible);
}

void RenderRichText::UpdateLayoutParams(const int32_t width, const int32_t height)
{
    float scale = 1.0f;
    auto pipelineContext = context_.Upgrade();
    if (pipelineContext) {
        scale = pipelineContext->GetViewScale();
    }
    if (!NearZero(scale)) {
        webContentWidth_ = width / scale;
        webContentHeight_ = height / scale;
    } else {
        webContentWidth_ = width;
        webContentHeight_ = height;
    }
    drawSize_.SetWidth(webContentWidth_);
    drawSize_.SetHeight(webContentHeight_);

    MarkNeedLayout(false, true);
}

void RenderRichText::OnGlobalPositionChanged()
{
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext || !delegate_) {
        LOGE("update rich text position, but context or delegate is null");
        return;
    }
    Offset offset = GetGlobalOffset();
    double top = offset.GetY() * pipelineContext->GetViewScale();
    double left = offset.GetX() * pipelineContext->GetViewScale();

    if (!initPositionSet_) {
        initPositionSet_ = true;
        CreateRealWeb((int32_t)top, (int32_t)left, isVisible_, true);
    } else {
        delegate_->UpdateWebPostion((int32_t)top, (int32_t)left);
    }
}

void RenderRichText::PerformLayout()
{
    if (!NeedLayout()) {
        LOGI("Render Rich Text PerformLayout No Need to Layout");
        return;
    }
    drawSize_ = Size(webContentWidth_, webContentHeight_);
    SetLayoutSize(drawSize_);
    SetNeedLayout(false);
    MarkNeedRender();
}

void RenderRichText::MarkNeedRender(bool overlay)
{
    RenderNode::MarkNeedRender(overlay);
}

} // namespace OHOS::Ace
