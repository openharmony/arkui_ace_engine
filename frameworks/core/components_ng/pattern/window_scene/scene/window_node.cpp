/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/window_scene/scene/window_node.h"

#include "core/components_ng/pattern/window_scene/scene/window_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float MOUSE_RECT_HOT_VP = 4.0f;
constexpr float TOUCH_RECT_HOT_VP = 20.0f;
constexpr double DEFAULT_HOT_DENSITY = 1.5f;
}

RefPtr<WindowNode> WindowNode::GetOrCreateWindowNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto windowNode = ElementRegister::GetInstance()->GetSpecificItemById<WindowNode>(nodeId);
    if (windowNode) {
        if (windowNode->GetTag() == tag) {
            return windowNode;
        }
        ElementRegister::GetInstance()->RemoveItemSilently(nodeId);
        auto parent = windowNode->GetParent();
        if (parent) {
            parent->RemoveChild(windowNode);
        }
    }

    auto pattern = patternCreator ? patternCreator() : AceType::MakeRefPtr<Pattern>();
    windowNode = AceType::MakeRefPtr<WindowNode>(tag, nodeId, pattern, false);
    windowNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(windowNode);
    return windowNode;
}

bool WindowNode::IsOutOfTouchTestRegion(const PointF& parentLocalPoint, int32_t sourceType)
{
    const auto& rect = GetPaintRectWithTransform();
    const auto& hotRect = ConvertHotRect(rect, sourceType);
    if (!hotRect.IsInRegion(parentLocalPoint)) {
        LOGD("Point %{public}s is out of region in %{public}s",
            parentLocalPoint.ToString().c_str(), GetTag().c_str());
        return true;
    }
    return false;
}

std::vector<RectF> WindowNode::GetResponseRegionList(const RectF& rect, int32_t sourceType)
{
    std::vector<RectF> responseRegionList;
    responseRegionList.emplace_back(ConvertHotRect(rect, sourceType));
    return responseRegionList;
}

RectF WindowNode::ConvertHotRect(const RectF& rect, int32_t sourceType)
{
    float hotOffsetVp = (sourceType == static_cast<int32_t>(Ace::SourceType::MOUSE)) ?
        MOUSE_RECT_HOT_VP : TOUCH_RECT_HOT_VP;
    auto context = PipelineContext::GetCurrentContext();
    double density = (context != nullptr) ? context->GetDensity() : DEFAULT_HOT_DENSITY;
    float hotOffset = static_cast<float>(hotOffsetVp * density);
    float hotX = rect.GetX() - hotOffset;
    float hotY = rect.GetY() - hotOffset;
    float hotWidth = rect.Width() + hotOffset * 2;
    float hotHeight = rect.Height() + hotOffset * 2;
    RectF rectHot(hotX, hotY, hotWidth, hotHeight);
    return rectHot;
}
} // namespace OHOS::Ace::NG
