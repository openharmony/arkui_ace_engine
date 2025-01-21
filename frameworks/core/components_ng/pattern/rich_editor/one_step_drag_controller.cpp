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

#include "core/components_ng/pattern/rich_editor/one_step_drag_controller.h"

namespace OHOS::Ace::NG {

/* begin OneStepDragParam */
OneStepDragParam::OneStepDragParam(const Builder& builder, const SelectMenuParam& selectMenuParam,
    TextSpanType spanType, TagFilter tagFilter) : spanType_(spanType), tagFilter_(tagFilter)
{
    menuBuilder = builder;
    onAppear = [onAppearFunc = selectMenuParam.onAppear, onMenuShowFunc = selectMenuParam.onMenuShow](
                   int32_t start, int32_t end) {
        onAppearFunc(start, end);
        onMenuShowFunc(start, end);
    };
    onDisappear = [onDisappearFunc = selectMenuParam.onDisappear, onMenuHideFunc = selectMenuParam.onMenuHide](
                      int32_t start, int32_t end) {
        onMenuHideFunc(start, end);
        onDisappearFunc();
    };
    menuParam.previewMode = MenuPreviewMode::IMAGE;
    menuParam.type = MenuType::CONTEXT_MENU;
    menuParam.previewAnimationOptions.scaleFrom = 1.0f;
    menuParam.previewBorderRadius = BorderRadiusProperty(Dimension(0));
    menuParam.backgroundBlurStyle = static_cast<int>(BlurStyle::NO_MATERIAL);
}

void OneStepDragParam::EnableDrag(const RefPtr<FrameNode>& frameNode) const
{
    frameNode->SetDraggable(true);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->InitDragDropEvent();
}

void OneStepDragParam::BindContextMenu(const RefPtr<FrameNode>& frameNode)
{
#ifndef ACE_UNITTEST
    CHECK_NULL_VOID(frameNode);
    auto resType = ResponseType::LONG_PRESS;
    auto menuParam = GetMenuParam(frameNode);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    ViewAbstractModel::GetInstance()->BindContextMenu(resType, menuBuilder, menuParam, previewBuilder);
    ViewAbstractModel::GetInstance()->BindDragWithContextMenuParams(menuParam);
    ViewStackProcessor::GetInstance()->Finish();
#endif
}

void OneStepDragParam::FillJsonValue(const std::unique_ptr<JsonValue>& jsonValue) const
{
    CHECK_NULL_VOID(jsonValue);
    auto jsonItem = JsonUtil::Create(true);
    jsonItem->Put("spanType", static_cast<int32_t>(spanType_));
    jsonItem->Put("responseType", static_cast<int32_t>(TextResponseType::LONG_PRESS));
    jsonItem->Put("menuType", static_cast<int32_t>(SelectionMenuType::PREVIEW_MENU));
    jsonValue->Put(jsonItem);
}

void OneStepDragParam::HandleDirtyNodes()
{
    while (!dirtyFrameNodes.empty()) {
        auto weakNode = dirtyFrameNodes.front();
        dirtyFrameNodes.pop();
        auto frameNode = weakNode.Upgrade();
        BindContextMenu(frameNode);
    }
}

inline void OneStepDragParam::MarkDirtyNode(const WeakPtr<FrameNode>& dirtyFrameNode)
{
    dirtyFrameNodes.push(dirtyFrameNode);
}
/* end OneStepDragParam */

/* begin ImageOneStepDragParam */
MenuParam ImageOneStepDragParam::GetMenuParam(const RefPtr<FrameNode>& frameNode) const
{
    auto imageNode = AceType::DynamicCast<ImageSpanNode>(frameNode);
    CHECK_NULL_RETURN(imageNode, menuParam);
    auto res = menuParam;
    res.onAppear = [weak = AceType::WeakClaim(AceType::RawPtr(imageNode)), onAppear = this->onAppear]() {
        CHECK_NULL_VOID(onAppear);
        auto imageNode = weak.Upgrade();
        CHECK_NULL_VOID(imageNode);
        const auto& spanItem = imageNode->GetSpanItem();
        onAppear(spanItem->rangeStart, spanItem->position);
    };
    res.onDisappear = [weak = AceType::WeakClaim(AceType::RawPtr(imageNode)), onDisappear = this->onDisappear]() {
        CHECK_NULL_VOID(onDisappear);
        auto imageNode = weak.Upgrade();
        CHECK_NULL_VOID(imageNode);
        const auto& spanItem = imageNode->GetSpanItem();
        onDisappear(spanItem->rangeStart, spanItem->position);
    };
    res.previewAnimationOptions.scaleTo = CalcImageScale(imageNode);
    return res;
}

void ImageOneStepDragParam::EnableOneStepDrag(const RefPtr<FrameNode>& frameNode)
{
    // image need to update [scaleTo] when size change, bindContextMenu when HandleDirtyNodes
    EnableDrag(frameNode);
}

float ImageOneStepDragParam::CalcImageScale(const RefPtr<ImageSpanNode>& imageNode) const
{
    float scale = 1.1f;
    auto dispSize = imageNode->GetGeometryNode()->GetMarginFrameSize();
    CHECK_NULL_RETURN(dispSize.IsPositive(), scale);
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(imageLayoutProperty, scale);
    auto imageSourceInfo = imageLayoutProperty->GetImageSourceInfoValue();
    CHECK_NULL_RETURN(imageSourceInfo.IsPixmap(), scale);
    auto pixelMap = imageSourceInfo.GetPixmap();
    CHECK_NULL_RETURN(pixelMap, scale);
    auto realWidth = pixelMap->GetWidth();
    auto realHeight = pixelMap->GetHeight();
    scale = std::max((float) realWidth / dispSize.Width(), (float) realHeight / dispSize.Height());
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "realSize=[%{public}d,%{public}d], scale=%{public}.2f",
        realWidth, realHeight, scale);
    return std::max(scale, 1.1f);
}
/* end ImageOneStepDragParam */

/* begin PlaceholderOneStepDragParam */
MenuParam PlaceholderOneStepDragParam::GetMenuParam(const RefPtr<FrameNode>& frameNode) const
{
    auto placeholderNode = AceType::DynamicCast<PlaceholderSpanNode>(frameNode);
    CHECK_NULL_RETURN(placeholderNode, menuParam);
    auto res = menuParam;
    res.onAppear = [weak = AceType::WeakClaim(AceType::RawPtr(placeholderNode)), onAppear = this->onAppear]() {
        CHECK_NULL_VOID(onAppear);
        auto placeholderNode = weak.Upgrade();
        CHECK_NULL_VOID(placeholderNode);
        const auto& spanItem = placeholderNode->GetSpanItem();
        onAppear(spanItem->rangeStart, spanItem->position);
    };
    return res;
}

void PlaceholderOneStepDragParam::EnableDrag(const RefPtr<FrameNode>& frameNode) const
{
    OneStepDragParam::EnableDrag(frameNode);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto dragStart = [](const RefPtr<OHOS::Ace::DragEvent>&, const std::string&) -> DragDropInfo {
        return DragDropInfo();
    };
    eventHub->SetDefaultOnDragStart(std::move(dragStart));
}

void PlaceholderOneStepDragParam::EnableOneStepDrag(const RefPtr<FrameNode>& frameNode)
{
    EnableDrag(frameNode);
    BindContextMenu(frameNode);
}
/* end PlaceholderOneStepDragParam */

/* begin OneStepDragController */
// handle existing nodes, when bindSelectionMenu
bool OneStepDragController::SetMenuParam(TextSpanType spanType, const Builder& builder,
    const SelectMenuParam& menuParam)
{
    const auto& dragParam = CreateDragParam(spanType, builder, menuParam);
    CHECK_NULL_RETURN(dragParam, false);

    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, false);
    const auto& tagFilter = dragParam->tagFilter_;
    CHECK_NULL_RETURN(tagFilter, false);

    for (const auto& uiNode : host->GetChildren()) {
        const auto& tag = uiNode->GetTag();
        CHECK_NULL_CONTINUE(tagFilter(tag));
        auto frameNode = AceType::DynamicCast<FrameNode>(uiNode);
        CHECK_NULL_CONTINUE(frameNode);
        dragParam->EnableDrag(frameNode);
        dragParam->BindContextMenu(frameNode);
    }
    return true;
}

// handle new added node
void OneStepDragController::EnableOneStepDrag(TextSpanType spanType, const RefPtr<FrameNode>& frameNode)
{
    const auto& dragParam = GetDragParam(spanType);
    CHECK_NULL_VOID(frameNode && dragParam);
    dragParam->EnableOneStepDrag(frameNode);
    CopyDragCallback(spanType, frameNode);
}

std::string OneStepDragController::GetJsonRange(const TextSpanType spanType, const RefPtr<FrameNode>& frameNode)
{
    RefPtr<SpanItem> spanItem;
    if (spanType == TextSpanType::IMAGE) {
        auto imageNode = AceType::DynamicCast<ImageSpanNode>(frameNode);
        IF_TRUE(imageNode, spanItem = imageNode->GetSpanItem());
    } else if (spanType == TextSpanType::BUILDER) {
        auto placeholderNode = AceType::DynamicCast<PlaceholderSpanNode>(frameNode);
        IF_TRUE(placeholderNode, spanItem = placeholderNode->GetSpanItem());
    }
    CHECK_NULL_RETURN(spanItem, "");
    auto jsonRange = JsonUtil::Create(true);
    jsonRange->Put("rangeStart", spanItem->rangeStart);
    jsonRange->Put("rangeEnd", spanItem->position);
    return jsonRange->ToString();
}

void OneStepDragController::CopyDragCallback(TextSpanType spanType, const RefPtr<FrameNode>& frameNode)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);

    auto hostEventHub = host->GetEventHub<EventHub>();
    auto frameNodeEventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hostEventHub && frameNodeEventHub);

    // start
    auto start = hostEventHub->GetOnDragStart();
    auto oneStepDragStart = [weakNode = AceType::WeakClaim(AceType::RawPtr(frameNode)), start, spanType](
        const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& extraParams) -> DragDropInfo {
        auto frameNode = weakNode.Upgrade();
        auto jsonStr = OneStepDragController::GetJsonRange(spanType, frameNode);
        return start(event, jsonStr);
    };
    IF_TRUE(start, frameNodeEventHub->SetOnDragStart(std::move(oneStepDragStart)));

    // end
    auto end = hostEventHub->GetCustomerOnDragEndFunc();
    auto oneStepDragEnd = [end, weakPattern = pattern_, scopeId = Container::CurrentId()]
        (const RefPtr<OHOS::Ace::DragEvent>& event) {
        ContainerScope scope(scopeId);
        IF_TRUE(end, end(event));
    };
    frameNodeEventHub->SetCustomerOnDragFunc(DragFuncType::DRAG_END, std::move(oneStepDragEnd));
}

void OneStepDragController::SetEnableEventResponse(bool isEnable)
{
    CHECK_NULL_VOID(imageDragParam_ || placeholderDragParam_);
    CHECK_NULL_VOID(isEnableEventResponse_ != isEnable);
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);

    const auto& imageTagFilter = imageDragParam_ ? imageDragParam_->tagFilter_ : DEFAULT_FILTER;
    const auto& placeholderTagFilter = placeholderDragParam_ ? placeholderDragParam_->tagFilter_ : DEFAULT_FILTER;

    for (const auto& uiNode : host->GetChildren()) {
        auto& tag = uiNode->GetTag();
        CHECK_NULL_CONTINUE(imageTagFilter(tag) || placeholderTagFilter(tag));
        auto frameNode = AceType::DynamicCast<FrameNode>(uiNode);
        CHECK_NULL_CONTINUE(frameNode);
        auto hub = frameNode->GetOrCreateGestureEventHub();
        CHECK_NULL_CONTINUE(hub);
        hub->SetHitTestMode(isEnable ? HitTestMode::HTMDEFAULT : HitTestMode::HTMNONE);
    }
    isEnableEventResponse_ = isEnable;
}

void OneStepDragController::SetEnableEventResponse(const TextSelector& selector,
    std::list<WeakPtr<ImageSpanNode>>& imageNodes, std::list<WeakPtr<PlaceholderSpanNode>>& builderNodes)
{
    auto start = selector.GetTextStart();
    auto end = selector.GetTextEnd();
    IF_TRUE(imageDragParam_, SetEnableEventResponse(start, end, imageNodes));
    IF_TRUE(placeholderDragParam_, SetEnableEventResponse(start, end, builderNodes));
}

template<typename T>
void OneStepDragController::SetEnableEventResponse(int32_t start, int32_t end, std::list<WeakPtr<T>>& builderNodes)
{
    for (auto it = builderNodes.begin(); it != builderNodes.end();) {
        auto builderNode = it->Upgrade();
        if (!builderNode) {
            it = builderNodes.erase(it);
            continue;
        }
        ++it;
        auto hub = builderNode->GetOrCreateGestureEventHub();
        CHECK_NULL_CONTINUE(hub);
        auto spanItem = builderNode->GetSpanItem();
        bool enableResponse = start > spanItem->rangeStart || spanItem->position > end;
        hub->SetHitTestMode(enableResponse ? HitTestMode::HTMDEFAULT : HitTestMode::HTMNONE);
    }
}

void OneStepDragController::FillJsonValue(const std::unique_ptr<JsonValue>& jsonValue)
{
    IF_PRESENT(imageDragParam_, FillJsonValue(jsonValue));
    IF_PRESENT(placeholderDragParam_, FillJsonValue(jsonValue));
}

void OneStepDragController::MarkDirtyNode(const WeakPtr<ImageSpanNode>& dirtyFrameNode)
{
    IF_PRESENT(imageDragParam_, MarkDirtyNode(dirtyFrameNode));
}

void OneStepDragController::HandleDirtyNodes()
{
    IF_PRESENT(imageDragParam_, HandleDirtyNodes());
    IF_PRESENT(placeholderDragParam_, HandleDirtyNodes());
}

const std::unique_ptr<OneStepDragParam>& OneStepDragController::GetDragParam(TextSpanType spanType) const
{
    if (spanType == TextSpanType::IMAGE) {
        return imageDragParam_;
    }
    if (spanType == TextSpanType::BUILDER) {
        return placeholderDragParam_;
    }
    return invalidParam;
}

const std::unique_ptr<OneStepDragParam>& OneStepDragController::CreateDragParam(TextSpanType spanType,
    const Builder& builder, const SelectMenuParam& menuParam)
{
    CHECK_NULL_RETURN(builder, invalidParam);
    if (spanType == TextSpanType::IMAGE) {
        return imageDragParam_ = std::make_unique<ImageOneStepDragParam>(builder, menuParam);
    }
    if (spanType == TextSpanType::BUILDER) {
        return placeholderDragParam_ = std::make_unique<PlaceholderOneStepDragParam>(builder, menuParam);
    }
    return invalidParam;
}
/* end OneStepDragController */

} // namespace OHOS::Ace::NG