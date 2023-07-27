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

namespace OHOS::Ace::NG {
bool SelectOverlayProxy::IsClosed() const
{
    return false;
}

void SelectOverlayProxy::Close() const {}

void SelectOverlayProxy::UpdateFirstSelectHandleInfo(const SelectHandleInfo& info) const {}

void SelectOverlayProxy::UpdateSecondSelectHandleInfo(const SelectHandleInfo& info) const {}

void SelectOverlayProxy::UpdateFirstAndSecondHandleInfo(
    const SelectHandleInfo& firstInfo, const SelectHandleInfo& secondInfo) const
{}

void SelectOverlayProxy::SetSelectInfo(const std::string& selectInfo) const {}

void SelectOverlayProxy::UpdateSelectMenuInfo(const SelectMenuInfo& info) const {}
} // namespace OHOS::Ace::NG