/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/manager/select_overlay/select_overlay_proxy.h"

#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
RefPtr<SelectOverlayPattern> GetSelectOverlayPattern(int32_t selectOverlayId)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto manager = pipeline->GetSelectOverlayManager();
    CHECK_NULL_RETURN(manager, nullptr);
    auto node = manager->GetSelectOverlayNode(selectOverlayId);
    CHECK_NULL_RETURN(node, nullptr);
    return node->GetPattern<SelectOverlayPattern>();
}
} // namespace

void SelectOverlayProxy::UpdateFirstSelectHandleInfo(const SelectHandleInfo& info) const
{
    auto pattern = GetSelectOverlayPattern(selectOverlayId_);
    CHECK_NULL_VOID(pattern);
    pattern->UpdateFirstSelectHandleInfo(info);
}

void SelectOverlayProxy::UpdateSecondSelectHandleInfo(const SelectHandleInfo& info) const
{
    auto pattern = GetSelectOverlayPattern(selectOverlayId_);
    CHECK_NULL_VOID(pattern);
    pattern->UpdateSecondSelectHandleInfo(info);
}

void SelectOverlayProxy::UpdateFirstAndSecondHandleInfo(
    const SelectHandleInfo& firstInfo, const SelectHandleInfo& secondInfo) const
{
    auto pattern = GetSelectOverlayPattern(selectOverlayId_);
    CHECK_NULL_VOID(pattern);
    pattern->UpdateFirstAndSecondHandleInfo(firstInfo, secondInfo);
}

void SelectOverlayProxy::UpdateSelectMenuInfo(const SelectMenuInfo& info) const
{
    auto pattern = GetSelectOverlayPattern(selectOverlayId_);
    CHECK_NULL_VOID(pattern);
    pattern->UpdateSelectMenuInfo(info);
}

void SelectOverlayProxy::UpdateSelectMenuInfo(std::function<void(SelectMenuInfo& menuInfo)> updateAction) const
{
    auto pattern = GetSelectOverlayPattern(selectOverlayId_);
    CHECK_NULL_VOID(pattern);
    pattern->UpdateSelectMenuInfo(updateAction);
}

void SelectOverlayProxy::UpdateShowArea(const RectF& area) const
{
    auto pattern = GetSelectOverlayPattern(selectOverlayId_);
    CHECK_NULL_VOID(pattern);
    pattern->UpdateShowArea(area);
}

void SelectOverlayProxy::SetSelectRegionVisible(bool isSelectRegionVisible)
{
    auto pattern = GetSelectOverlayPattern(selectOverlayId_);
    CHECK_NULL_VOID(pattern);
    pattern->SetSelectRegionVisible(isSelectRegionVisible);
}

void SelectOverlayProxy::SetHandleReverse(bool reverse)
{
    auto pattern = GetSelectOverlayPattern(selectOverlayId_);
    CHECK_NULL_VOID(pattern);
    pattern->SetHandleReverse(reverse);
}

bool SelectOverlayProxy::IsClosed() const
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, true);
    auto manager = pipeline->GetSelectOverlayManager();
    CHECK_NULL_RETURN(manager, true);
    return !manager->HasSelectOverlay(selectOverlayId_);
}

void SelectOverlayProxy::Close(bool animation) const
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetSelectOverlayManager();
    CHECK_NULL_VOID(manager);
    manager->DestroySelectOverlay(selectOverlayId_, animation);
}

void SelectOverlayProxy::SetSelectInfo(const std::string& selectInfo) const
{
    auto pattern = GetSelectOverlayPattern(selectOverlayId_);
    CHECK_NULL_VOID(pattern);
    pattern->SetSelectInfo(selectInfo);
}

void SelectOverlayProxy::ShowOrHiddenMenu(bool isHidden, bool noAnimation)
{
    auto pattern = GetSelectOverlayPattern(selectOverlayId_);
    CHECK_NULL_VOID(pattern);
    pattern->ShowOrHiddenMenu(isHidden, noAnimation);
}

void SelectOverlayProxy::DisableMenu(bool isDisabled)
{
    auto pattern = GetSelectOverlayPattern(selectOverlayId_);
    CHECK_NULL_VOID(pattern);
    pattern->DisableMenu(isDisabled);
}

bool SelectOverlayProxy::IsMenuShow()
{
    auto pattern = GetSelectOverlayPattern(selectOverlayId_);
    CHECK_NULL_RETURN(pattern, false);
    return pattern->IsMenuShow();
}

bool SelectOverlayProxy::IsSingleHandleMenuShow()
{
    auto pattern = GetSelectOverlayPattern(selectOverlayId_);
    CHECK_NULL_RETURN(pattern, false);
    return pattern->IsSingleHandleMenuShow();
}

bool SelectOverlayProxy::IsHandleShow()
{
    auto pattern = GetSelectOverlayPattern(selectOverlayId_);
    CHECK_NULL_RETURN(pattern, false);
    return pattern->IsHandleShow();
}

bool SelectOverlayProxy::IsSingleHandle()
{
    auto pattern = GetSelectOverlayPattern(selectOverlayId_);
    CHECK_NULL_RETURN(pattern, false);
    return pattern->IsSingleHandle();
}

bool SelectOverlayProxy::IsHandleReverse()
{
    auto pattern = GetSelectOverlayPattern(selectOverlayId_);
    CHECK_NULL_RETURN(pattern, false);
    auto info = pattern->GetSelectOverlayInfo();
    return info && info->handleReverse;
}

SelectOverlayInfo SelectOverlayProxy::GetSelectOverlayMangerInfo()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, SelectOverlayInfo());
    auto manager = pipeline->GetSelectOverlayManager();
    CHECK_NULL_RETURN(manager, SelectOverlayInfo());
    return manager->GetSelectOverlayInfo();
}

void SelectOverlayProxy::UpdateSelectArea(const RectF& selectArea)
{
    auto pattern = GetSelectOverlayPattern(selectOverlayId_);
    CHECK_NULL_VOID(pattern);
    pattern->UpdateSelectArea(selectArea);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SelectOverlayProxy::SetIsNewAvoid(bool isNewAvoid)
{
    auto pattern = GetSelectOverlayPattern(selectOverlayId_);
    CHECK_NULL_VOID(pattern);
    pattern->SetIsNewAvoid(isNewAvoid);
}
} // namespace OHOS::Ace::NG
