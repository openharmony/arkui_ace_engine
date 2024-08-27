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

#include "core/components/flex/render_flex_item.h"

#include "base/log/dump_log.h"
#include "core/components/flex/flex_item_component.h"

namespace OHOS::Ace {

RefPtr<RenderNode> RenderFlexItem::Create()
{
    return AceType::MakeRefPtr<RenderFlexItem>();
}

void RenderFlexItem::Update(const RefPtr<Component>& component)
{
    const RefPtr<FlexItemComponent> flexItem = AceType::DynamicCast<FlexItemComponent>(component);
    if (!flexItem) {
        return;
    }
    // check the validity of properties
    SetId(flexItem->GetInspectorKey());
    SetAlignRules(flexItem->GetAlignRules());
    if (flexItem->GetFlexShrink() >= 0.0) {
        flexShrink_ = flexItem->GetFlexShrink();
    }
    if (flexItem->GetFlexBasis().Value() >= 0.0) {
        flexBasis_ = flexItem->GetFlexBasis();
    }
    if (flexItem->GetFlexGrow() >= 0.0) {
        flexGrow_ = flexItem->GetFlexGrow();
    }
    gridColumnInfo_ = flexItem->GetGridColumnInfo();
    canStretch_ = flexItem->GetStretchFlag();
    mustStretch_ = flexItem->MustStretch();
    alignSelf_ = flexItem->GetAlignSelf();
    if (minWidth_ != flexItem->GetMinWidth() || maxWidth_ != flexItem->GetMaxWidth() ||
        minHeight_ != flexItem->GetMinHeight() || maxHeight_ != flexItem->GetMaxHeight()) {
        auto parentFlex = GetParent().Upgrade();
        if (parentFlex) {
            parentFlex->MarkNeedLayout();
        }
    }
    minWidth_ = flexItem->GetMinWidth();
    minHeight_ = flexItem->GetMinHeight();
    maxWidth_ = flexItem->GetMaxWidth();
    maxHeight_ = flexItem->GetMaxHeight();
    isHidden_ = flexItem->IsHidden();
    displayType_ = flexItem->GetDisplayType();
    MarkNeedLayout();
}

void RenderFlexItem::PerformLayout()
{
    RenderProxy::PerformLayout();
    if (!gridColumnInfo_) {
        return;
    }
    auto offset = gridColumnInfo_->GetOffset();
    if (offset != UNDEFINED_DIMENSION) {
        positionParam_.type = PositionType::PTSEMI_RELATIVE;
        std::pair<AnimatableDimension, bool>& edge =
            (GetTextDirection() == TextDirection::RTL) ? positionParam_.right : positionParam_.left;
        edge.first = offset;
        edge.second = true;
    }
}

bool RenderFlexItem::MaybeRelease()
{
    auto context = GetContext().Upgrade();
    if (context && context->GetRenderFactory() &&
        context->GetRenderFactory()->GetRenderFlexItemFactory()->Recycle(this)) {
        ClearRenderObject();
        return false;
    }
    return true;
}

void RenderFlexItem::ClearRenderObject()
{
    RenderNode::ClearRenderObject();
    flexGrow_ = 0.0;
    flexShrink_ = 0.0;
    flexBasis_ = 0.0_px;
    canStretch_ = true;
    mustStretch_ = false;
    minWidth_ = Dimension();
    minHeight_ = Dimension();
    maxWidth_ = Dimension(Size::INFINITE_SIZE);
    maxHeight_ = Dimension(Size::INFINITE_SIZE);
    alignSelf_ = FlexAlign::AUTO;
    relativeLeftAligned_ = false;
    relativeRightAligned_ = false;
    relativeMiddleAligned_ = false;
    relativeTopAligned_ = false;
    relativeBottomAligned_ = false;
    relativeCenterAligned_ = false;
    relativeLeft_ = 0.0;
    relativeRight_ = 0.0;
    relativeMiddle_ = 0.0;
    relativeTop_ = 0.0;
    relativeBottom_ = 0.0;
    relativeCenter_ = 0.0;
}

void RenderFlexItem::SetAligned(const AlignDirection& alignDirection)
{
    static const std::unordered_map<AlignDirection, void (*)(RenderFlexItem&)> operators = {
        { AlignDirection::LEFT, [](RenderFlexItem& item) {
            item.relativeLeftAligned_ = true;
        }},
        { AlignDirection::RIGHT, [](RenderFlexItem& item) {
            item.relativeRightAligned_ = true;
        }},
        { AlignDirection::MIDDLE, [](RenderFlexItem& item) {
            item.relativeMiddleAligned_ = true;
        }},
        { AlignDirection::TOP, [](RenderFlexItem& item) {
            item.relativeTopAligned_ = true;
        }},
        { AlignDirection::BOTTOM, [](RenderFlexItem& item) {
            item.relativeBottomAligned_ = true;
        }},
        { AlignDirection::CENTER, [](RenderFlexItem& item) {
            item.relativeCenterAligned_ = true;
        }},
    };
    auto operatorIter = operators.find(alignDirection);
    if (operatorIter != operators.end()) {
        operatorIter->second(*this);
        return;
    }
    LOGE("Unknown Align Direction");
}

bool RenderFlexItem::GetAligned(AlignDirection& alignDirection)
{
    static const std::unordered_map<AlignDirection, bool (*)(RenderFlexItem&)> operators = {
        { AlignDirection::LEFT, [](RenderFlexItem& item) {
            return item.relativeLeftAligned_;
        }},
        { AlignDirection::RIGHT, [](RenderFlexItem& item) {
            return item.relativeRightAligned_;
        }},
        { AlignDirection::MIDDLE, [](RenderFlexItem& item) {
            return item.relativeMiddleAligned_;
        }},
        { AlignDirection::TOP, [](RenderFlexItem& item) {
            return item.relativeTopAligned_;
        }},
        { AlignDirection::BOTTOM, [](RenderFlexItem& item) {
            return item.relativeBottomAligned_;
        }},
        { AlignDirection::CENTER, [](RenderFlexItem& item) {
            return item.relativeCenterAligned_;
        }},
    };
    auto operatorIter = operators.find(alignDirection);
    if (operatorIter != operators.end()) {
        return operatorIter->second(*this);
    }
    LOGE("Unknown Align Direction");
    return false;
}

double RenderFlexItem::GetAlignValue(AlignDirection& alignDirection)
{
    static const std::unordered_map<AlignDirection, double (*)(RenderFlexItem&)> operators = {
        { AlignDirection::LEFT, [](RenderFlexItem& item) {
            return item.relativeLeft_;
        }},
        { AlignDirection::RIGHT, [](RenderFlexItem& item) {
            return item.relativeRight_;
        }},
        { AlignDirection::MIDDLE, [](RenderFlexItem& item) {
            return item.relativeMiddle_;
        }},
        { AlignDirection::TOP, [](RenderFlexItem& item) {
            return item.relativeTop_;
        }},
        { AlignDirection::BOTTOM, [](RenderFlexItem& item) {
            return item.relativeBottom_;
        }},
        { AlignDirection::CENTER, [](RenderFlexItem& item) {
            return item.relativeCenter_;
        }},
    };
    auto operatorIter = operators.find(alignDirection);
    if (operatorIter != operators.end()) {
        return operatorIter->second(*this);
    }
    LOGE("Unknown Align Direction");
    return 0.0;
}

void RenderFlexItem::SetAlignValue(AlignDirection& alignDirection, double value)
    {
    static const std::unordered_map<AlignDirection, void (*)(double, RenderFlexItem&)> operators = {
        { AlignDirection::LEFT, [](double inMapvalue, RenderFlexItem& item) {
            item.relativeLeft_ = inMapvalue;
            item.relativeLeftAligned_ = true;
        }},
        { AlignDirection::RIGHT, [](double inMapvalue, RenderFlexItem& item) {
            item.relativeRight_ = inMapvalue;
            item.relativeRightAligned_ = true;
        }},
        { AlignDirection::MIDDLE, [](double inMapvalue, RenderFlexItem& item) {
            item.relativeMiddle_ = inMapvalue;
            item.relativeMiddleAligned_ = true;
        }},
        { AlignDirection::TOP, [](double inMapvalue, RenderFlexItem& item) {
            item.relativeTop_ = inMapvalue;
            item.relativeTopAligned_ = true;
        }},
        { AlignDirection::BOTTOM, [](double inMapvalue, RenderFlexItem& item) {
            item.relativeBottom_ = inMapvalue;
            item.relativeBottomAligned_ = true;
        }},
        { AlignDirection::CENTER, [](double inMapvalue, RenderFlexItem& item) {
            item.relativeCenter_ = inMapvalue;
            item.relativeCenterAligned_ = true;
        }},
    };
    auto operatorIter = operators.find(alignDirection);
    if (operatorIter != operators.end()) {
        operatorIter->second(value, *this);
        return;
    }
    LOGE("Unknown Align Direction");
}

void RenderFlexItem::Dump()
{
    DumpLog::GetInstance().AddDesc(std::string("FlexGrow: ")
                                       .append(std::to_string(flexGrow_))
                                       .append(", FlexShrink: ")
                                       .append(std::to_string(flexShrink_))
                                       .append(", FlexBasis: ")
                                       .append(std::to_string(flexBasis_.Value())));
}

} // namespace OHOS::Ace
