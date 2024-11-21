/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_list_item_ffi.h"

#include "cj_lambda.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/utils.h"
#include "core/components_ng/pattern/list/list_item_model.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace {
const std::vector<V2::StickyMode> STICKY_MODES = { V2::StickyMode::NONE, V2::StickyMode::NORMAL,
    V2::StickyMode::OPACITY };

const std::vector<V2::SwipeEdgeEffect> SWIPE_EDGE_EFFECT = { V2::SwipeEdgeEffect::Spring, V2::SwipeEdgeEffect::None };
} // namespace

extern "C" {
void FfiOHOSAceFrameworkListItemCreate()
{
    ListItemModel::GetInstance()->Create();
}

void FfiOHOSAceFrameworkListItemSetBorderRaduis(double raduis, int32_t unit)
{
    Dimension value(raduis, static_cast<DimensionUnit>(unit));

    ListItemModel::GetInstance()->SetBorderRadius(value);
}

void FfiOHOSAceFrameworkListItemSetSticky(int32_t value)
{
    if (!Utils::CheckParamsValid(value, STICKY_MODES.size())) {
        LOGE("invalid value for font style");
        return;
    }
    ListItemModel::GetInstance()->SetSticky(STICKY_MODES[value]);
}

void FfiOHOSAceFrameworkListItemSetEditable(bool flag)
{
    uint32_t value = flag ? V2::EditMode::DELETABLE : V2::EditMode::SHAM;
    ListItemModel::GetInstance()->SetEditMode(value);
}

void FfiOHOSAceFrameworkListItemSetSelectable(bool flag)
{
    ListItemModel::GetInstance()->SetSelectable(flag);
}

void FfiOHOSAceFrameworkListItemSetOnSelect(void (*callback)(bool flag))
{
    ListItemModel::GetInstance()->SetSelectCallback(CJLambda::Create(callback));
}

void FfiOHOSAceFrameworkListItemSetSwipeAction(void (*startBuilder)(), void (*endBuilder)(), int32_t edgeEffect)
{
    if (!Utils::CheckParamsValid(edgeEffect, SWIPE_EDGE_EFFECT.size())) {
        LOGE("invalid value for font swipeEdgeAction");
        return;
    }

    ListItemModel::GetInstance()->SetDeleteArea(
        CJLambda::Create(endBuilder), nullptr, nullptr, nullptr, nullptr,
        Dimension(0, DimensionUnit::VP), false, nullptr);

    ListItemModel::GetInstance()->SetDeleteArea(
        CJLambda::Create(startBuilder), nullptr, nullptr, nullptr, nullptr,
        Dimension(0, DimensionUnit::VP), true, nullptr);

    ListItemModel::GetInstance()->SetSwiperAction(
        nullptr, nullptr, nullptr, SWIPE_EDGE_EFFECT[edgeEffect]);
}
}
