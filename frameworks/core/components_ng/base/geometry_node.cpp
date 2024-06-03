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

#include "core/components_ng/base/geometry_node.h"

#include <string>
#include <utility>

#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/layout/layout_wrapper.h"

namespace OHOS::Ace::NG {

void GeometryNode::Reset()
{
    frame_.Reset();
    margin_.reset();
    padding_.reset();
    content_.reset();
    parentGlobalOffset_.Reset();
    parentAbsoluteOffset_.Reset();
    parentLayoutConstraint_.reset();
}

RefPtr<GeometryNode> GeometryNode::Clone() const
{
    auto node = MakeRefPtr<GeometryNode>();
    node->frame_ = frame_;
    if (margin_) {
        node->margin_ = std::make_unique<MarginPropertyF>(*margin_);
    }
    if (padding_) {
        node->padding_ = std::make_unique<MarginPropertyF>(*padding_);
    }
    if (content_) {
        node->content_ = std::make_unique<GeometryProperty>(*content_);
    }
    node->parentGlobalOffset_ = parentGlobalOffset_;
    node->parentLayoutConstraint_ = parentLayoutConstraint_;
    node->parentAbsoluteOffset_ = parentAbsoluteOffset_;
    return node;
}

void GeometryNode::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
#if defined(PREVIEW)
    auto frameSize = frame_.rect_.GetSize();
    json->Put("width", std::to_string(frameSize.Width()).c_str());
    json->Put("height", std::to_string(frameSize.Height()).c_str());

    auto jsonSize = JsonUtil::Create(true);
    jsonSize->Put("width", std::to_string(frameSize.Width()).c_str());
    jsonSize->Put("height", std::to_string(frameSize.Height()).c_str());
    json->Put("size", jsonSize);
#endif
}

RectF GeometryNode::GetParentAdjust() const
{
    return parentAdjust_;
}

void GeometryNode::SetParentAdjust(RectF parentAdjust)
{
    parentAdjust_ = parentAdjust;
}

RectF GeometryNode::GetSelfAdjust() const
{
    return selfAdjust_;
}

void GeometryNode::SetSelfAdjust(RectF selfAdjust)
{
    selfAdjust_ = selfAdjust;
}

float GeometryNode::OnePixelValueRounding(float value)
{
    float fractials = fmod(value, 1.0f);
    if (fractials < 0.0f) {
        ++fractials;
    }
    if (NearEqual(fractials, 1.0f) || GreatOrEqual(fractials, 0.5f)) {
        return (value - fractials + 1.0f);
    } else {
        return (value - fractials);
    }
}

float GeometryNode::OnePixelValueRounding(float value, bool isRound, bool forceCeil, bool forceFloor)
{
    float fractials = fmod(value, 1.0f);
    if (fractials < 0.0f) {
        ++fractials;
    }
    if (forceCeil) {
        return (value - fractials + 1.0f);
    } else if (forceFloor) {
        return (value - fractials);
    } else if (isRound) {
        if (NearEqual(fractials, 1.0f) || GreatOrEqual(fractials, 0.5f)) {
            return (value - fractials + 1.0f);
        } else {
            return (value - fractials);
        }
    }
    return value;
}

void GeometryNode::OnePixelRounding()
{
    float relativeLeft = GetPixelGridRoundOffset().GetX();
    float relativeTop = GetPixelGridRoundOffset().GetY();
    float nodeWidth = GetFrameSize().Width();
    float nodeHeight = GetFrameSize().Height();
    float roundToPixelErrorX = 0.0f;
    float roundToPixelErrorY = 0.0f;
    float absoluteRight = relativeLeft + nodeWidth;
    float absoluteBottom = relativeTop + nodeHeight;

    float nodeLeftI = OnePixelValueRounding(relativeLeft);
    float nodeTopI = OnePixelValueRounding(relativeTop);
    roundToPixelErrorX += nodeLeftI - relativeLeft;
    roundToPixelErrorY += nodeTopI - relativeTop;
    pixelGridRoundOffset_ = OffsetF(nodeLeftI, nodeTopI);

    float nodeWidthI = OnePixelValueRounding(absoluteRight) - nodeLeftI;
    float nodeWidthTemp = OnePixelValueRounding(nodeWidth);
    roundToPixelErrorX += nodeWidthI - nodeWidth;
    if (roundToPixelErrorX > 0.5f) {
        nodeWidthI -= 1.0f;
        roundToPixelErrorX -= 1.0f;
    }
    if (roundToPixelErrorX < -0.5f) {
        nodeWidthI += 1.0f;
        roundToPixelErrorX += 1.0f;
    }
    if (nodeWidthI < nodeWidthTemp) {
        roundToPixelErrorX += nodeWidthTemp - nodeWidthI;
        nodeWidthI = nodeWidthTemp;
    }

    float nodeHeightI = OnePixelValueRounding(absoluteBottom) - nodeTopI;
    float nodeHeightTemp = OnePixelValueRounding(nodeHeight);
    roundToPixelErrorY += nodeHeightI - nodeHeight;
    if (roundToPixelErrorY > 0.5f) {
        nodeHeightI -= 1.0f;
        roundToPixelErrorY -= 1.0f;
    }
    if (roundToPixelErrorY < -0.5f) {
        nodeHeightI += 1.0f;
        roundToPixelErrorY += 1.0f;
    }
    if (nodeHeightI < nodeHeightTemp) {
        roundToPixelErrorY += nodeHeightTemp - nodeHeightI;
        nodeHeightI = nodeHeightTemp;
    }
    pixelGridRoundSize_ = SizeF(nodeWidthI, nodeHeightI);
}

void GeometryNode::OnePixelRounding(bool isRound, uint8_t flag)
{
    float relativeLeft = GetPixelGridRoundOffset().GetX();
    float relativeTop = GetPixelGridRoundOffset().GetY();
    float nodeWidth = GetFrameSize().Width();
    float nodeHeight = GetFrameSize().Height();
    float roundToPixelErrorX = 0.0f;
    float roundToPixelErrorY = 0.0f;
    float absoluteRight = relativeLeft + nodeWidth;
    float absoluteBottom = relativeTop + nodeHeight;
    bool ceilLeft = flag & static_cast<uint8_t>(PixelRoundPolicy::FORCE_CEIL_START);
    bool floorLeft = flag & static_cast<uint8_t>(PixelRoundPolicy::FORCE_FLOOR_START);
    bool ceilTop = flag & static_cast<uint8_t>(PixelRoundPolicy::FORCE_CEIL_TOP);
    bool floorTop = flag & static_cast<uint8_t>(PixelRoundPolicy::FORCE_FLOOR_TOP);
    bool ceilRight = flag & static_cast<uint8_t>(PixelRoundPolicy::FORCE_CEIL_END);
    bool floorRight = flag & static_cast<uint8_t>(PixelRoundPolicy::FORCE_FLOOR_END);
    bool ceilBottom = flag & static_cast<uint8_t>(PixelRoundPolicy::FORCE_CEIL_BOTTOM);
    bool floorBottom = flag & static_cast<uint8_t>(PixelRoundPolicy::FORCE_FLOOR_BOTTOM);

    float nodeLeftI = OnePixelValueRounding(relativeLeft, isRound, ceilLeft, floorLeft);
    float nodeTopI = OnePixelValueRounding(relativeTop, isRound, ceilTop, floorTop);
    roundToPixelErrorX += nodeLeftI - relativeLeft;
    roundToPixelErrorY += nodeTopI - relativeTop;
    pixelGridRoundOffset_ = OffsetF(nodeLeftI, nodeTopI);

    float nodeWidthI = OnePixelValueRounding(absoluteRight, isRound, ceilRight, floorRight) - nodeLeftI;
    float nodeWidthTemp = OnePixelValueRounding(nodeWidth, isRound, ceilRight, floorRight);
    roundToPixelErrorX += nodeWidthI - nodeWidth;
    if (roundToPixelErrorX > 0.5f) {
        nodeWidthI -= 1.0f;
        roundToPixelErrorX -= 1.0f;
    }
    if (roundToPixelErrorX < -0.5f) {
        nodeWidthI += 1.0f;
        roundToPixelErrorX += 1.0f;
    }
    if (nodeWidthI < nodeWidthTemp) {
        roundToPixelErrorX += nodeWidthTemp - nodeWidthI;
        nodeWidthI = nodeWidthTemp;
    }

    float nodeHeightI = OnePixelValueRounding(absoluteBottom, isRound, ceilBottom, floorBottom) - nodeTopI;
    float nodeHeightTemp = OnePixelValueRounding(nodeHeight, isRound, ceilBottom, floorBottom);
    roundToPixelErrorY += nodeHeightI - nodeHeight;
    if (roundToPixelErrorY > 0.5f) {
        nodeHeightI -= 1.0f;
        roundToPixelErrorY -= 1.0f;
    }
    if (roundToPixelErrorY < -0.5f) {
        nodeHeightI += 1.0f;
        roundToPixelErrorY += 1.0f;
    }
    if (nodeHeightI < nodeHeightTemp) {
        roundToPixelErrorY += nodeHeightTemp - nodeHeightI;
        nodeHeightI = nodeHeightTemp;
    }
    pixelGridRoundSize_ = SizeF(nodeWidthI, nodeHeightI);
}
} // namespace OHOS::Ace::NG
