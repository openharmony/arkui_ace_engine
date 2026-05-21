/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/scrollable/selectable_item_pattern.h"

#include "core/components_ng/event/input_event.h"
#include "core/components_ng/event/touch_event.h"
#include "core/components_ng/pattern/scrollable/selectable_utils.h"
#include "core/interfaces/native/node/node_checkbox_modifier.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension EDIT_MODE_CHECK_BOX_PADDING = 8.0_vp;
} // namespace

void SelectableItemPattern::SetEditModeEnabled(bool enabled)
{
    if (enabled && selectable_ && !editModeCheckBoxNode_) {
        CreateEditModeCheckBox();
    } else if ((!enabled || !selectable_) && editModeCheckBoxNode_) {
        RemoveEditModeCheckBox();
    }
}

void SelectableItemPattern::CreateEditModeCheckBox()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(!editModeCheckBoxNode_);

    auto checkboxModifier = NodeModifier::GetCheckboxCustomModifier();
    CHECK_NULL_VOID(checkboxModifier);

    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto checkboxHandle = checkboxModifier->createCheckboxFrameNode(nodeId);
    std::function<void(bool)>&& onChange = [weak = WeakClaim(this)](bool isChecked) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->MarkIsSelectedWithoutCheckbox(isChecked);
    };
    checkboxModifier->setCheckboxOnChange(checkboxHandle, reinterpret_cast<void*>(&onChange));
    checkboxModifier->setSelect(checkboxHandle, isSelected_);

    editModeCheckBoxNode_ = AceType::Claim(reinterpret_cast<FrameNode*>(checkboxHandle));
    auto checkboxLayoutProperty = editModeCheckBoxNode_->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(checkboxLayoutProperty);
    MarginProperty marginCheckbox;
    marginCheckbox.SetEdges(CalcLength(EDIT_MODE_CHECK_BOX_PADDING));
    checkboxLayoutProperty->UpdateMargin(marginCheckbox);
    editModeCheckBoxNode_->MarkModifyDone();
    host->AddChild(editModeCheckBoxNode_);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void SelectableItemPattern::RemoveEditModeCheckBox()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(editModeCheckBoxNode_);

    host->RemoveChild(editModeCheckBoxNode_);
    editModeCheckBoxNode_.Reset();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void SelectableItemPattern::UpdateEditModeCheckBoxPosition()
{
    CHECK_NULL_VOID(editModeCheckBoxNode_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto itemSize = geometryNode->GetFrameSize();
    auto cbGeometryNode = editModeCheckBoxNode_->GetGeometryNode();
    auto cbSize = cbGeometryNode ? cbGeometryNode->GetMarginFrameSize() : SizeF(0.0f, 0.0f);
    float offsetX = !AceApplicationInfo::GetInstance().IsRightToLeft() ? (itemSize.Width() - cbSize.Width()) : 0.0f;
    float offsetY = itemSize.Height() - cbSize.Height();
    auto renderContext = editModeCheckBoxNode_->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdatePosition(OffsetT<Dimension>(Dimension(offsetX), Dimension(offsetY)));
}

void SelectableItemPattern::SyncCheckBoxFromItem()
{
    CHECK_NULL_VOID(editModeCheckBoxNode_);
    auto checkboxModifier = NodeModifier::GetCheckboxCustomModifier();
    CHECK_NULL_VOID(checkboxModifier);
    checkboxModifier->setSelect(
        reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(editModeCheckBoxNode_)), isSelected_);
    editModeCheckBoxNode_->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SelectableItemPattern::BeforeCreateLayoutWrapper()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto useCheckbox = SelectableUtils::IsDefaultMultiSelectStyleEnabled(host);
    if (useCheckbox && selectable_ && !editModeCheckBoxNode_) {
        CreateEditModeCheckBox();
    } else if ((!useCheckbox || !selectable_) && editModeCheckBoxNode_) {
        RemoveEditModeCheckBox();
    }
}
} // namespace OHOS::Ace::NG
