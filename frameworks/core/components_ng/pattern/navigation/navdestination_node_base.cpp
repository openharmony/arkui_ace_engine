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

#include "core/components_ng/pattern/navigation/navdestination_node_base.h"

#include "base/utils/utf_helper.h"
#include "base/json/json_util.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/navigation/bar_item_node.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navigation/navdestination_content_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navigation/tool_bar_node.h"
#include "core/components_ng/pattern/navigation/tool_bar_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double HALF = 0.5;
constexpr float REMOVE_CLIP_SIZE = 100000.0f;
constexpr float CONTENT_OFFSET_PERCENT = 0.2f;
}

std::string NavDestinationNodeBase::GetBarItemsString(bool isMenu) const
{
    auto jsonValue = JsonUtil::Create(true);
    auto parentNodeOfBarItems = isMenu ? DynamicCast<FrameNode>(GetMenu()) : DynamicCast<FrameNode>(GetToolBarNode());
    CHECK_NULL_RETURN(parentNodeOfBarItems, "");
    if (parentNodeOfBarItems->GetChildren().empty()) {
        return "";
    }
    auto jsonOptions = JsonUtil::CreateArray(true);
    int32_t i = 0;
    for (auto iter = parentNodeOfBarItems->GetChildren().begin(); iter != parentNodeOfBarItems->GetChildren().end();
            ++iter, i++) {
        auto jsonToolBarItem = JsonUtil::CreateArray(true);
        auto barItemNode = DynamicCast<BarItemNode>(*iter);
        if (!barItemNode) {
            jsonToolBarItem->Put("value", "");
            jsonToolBarItem->Put("icon", "");
            continue;
        }
        auto iconNode = DynamicCast<FrameNode>(barItemNode->GetIconNode());
        if (iconNode) {
            auto imageLayoutProperty = iconNode->GetLayoutProperty<ImageLayoutProperty>();
            if (!imageLayoutProperty || !imageLayoutProperty->HasImageSourceInfo()) {
                jsonToolBarItem->Put("icon", "");
            } else {
                jsonToolBarItem->Put("icon", imageLayoutProperty->GetImageSourceInfoValue().GetSrc().c_str());
            }
        } else {
            jsonToolBarItem->Put("icon", "");
        }
        auto textNode = DynamicCast<FrameNode>(barItemNode->GetTextNode());
        if (textNode) {
            auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
            if (!textLayoutProperty) {
                jsonToolBarItem->Put("value", "");
            } else {
                jsonToolBarItem->Put("value", UtfUtils::Str16ToStr8(textLayoutProperty->GetContentValue(u"")).c_str());
            }
        } else {
            jsonToolBarItem->Put("value", "");
        }
        auto index_ = std::to_string(i);
        jsonOptions->Put(index_.c_str(), jsonToolBarItem);
    }
    jsonValue->Put("items", jsonOptions);
    return jsonValue->ToString();
}

bool NavDestinationNodeBase::IsToolBarVisible() const
{
    auto toolBarNode = AceType::DynamicCast<FrameNode>(GetToolBarNode());
    CHECK_NULL_RETURN(toolBarNode, false);
    auto layoutProperty = toolBarNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, false);
    return layoutProperty->GetVisibilityValue(VisibleType::VISIBLE) == VisibleType::VISIBLE;
}

bool NavDestinationNodeBase::CustomizeExpandSafeArea()
{
    if (isCustomExpandRunning_) {
        return false;
    }
    if (!(rotateAngle_.has_value() && viewportConfig_)) {
        return false;
    }
    isCustomExpandRunning_ = true;
    ScopePageViewportConfig scopeConfig(viewportConfig_);
    auto geometryNode = GetGeometryNode();
    RectF backupParentAdjust;
    auto angle = rotateAngle_.value();
    if (geometryNode) {
        backupParentAdjust = geometryNode->GetParentAdjust();
        if (angle == ROTATION_90 || angle == ROTATION_180 || angle == ROTATION_270) {
            RectF parentAdjust{ safeAreaInsets_.left_.end, safeAreaInsets_.top_.end, 0.0f, 0.0f };
            geometryNode->SetParentAdjust(parentAdjust);
        }
    }
    FrameNode::ExpandSafeArea();
    if (geometryNode) {
        geometryNode->SetParentAdjust(backupParentAdjust);
    }
    isCustomExpandRunning_ = false;
    return true;
}

void NavDestinationNodeBase::Measure(const std::optional<LayoutConstraintF>& parentConstraint)
{
    if (rotateAngle_.has_value() && rotateAngle_.value() != ROTATION_0 && viewportConfig_) {
        ScopePageViewportConfig scopeConfig(viewportConfig_);
        FrameNode::Measure(parentConstraint);
        return;
    }
    FrameNode::Measure(parentConstraint);
}

void NavDestinationNodeBase::Layout()
{
    if (rotateAngle_.has_value() && rotateAngle_.value() != ROTATION_0 && viewportConfig_) {
        ScopePageViewportConfig scopeConfig(viewportConfig_);
        FrameNode::Layout();
        return;
    }
    FrameNode::Layout();
}

RectF NavDestinationNodeBase::CalcHalfClipRectForTransition(const SizeF& frameSize)
{
    auto angle = rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
    RectF rect;
    float width = frameSize.Width();
    float height = frameSize.Height();
    if (angle == ROTATION_90 || angle == ROTATION_270) {
        rect.SetSize({ REMOVE_CLIP_SIZE, height * HALF });
    } else {
        rect.SetSize({ width * HALF, REMOVE_CLIP_SIZE });
    }

    OffsetF offset{ 0.0f, 0.0f };
    if (AceApplicationInfo::GetInstance().IsRightToLeft()) {
        if (angle == ROTATION_90) {
            offset = OffsetF{ 0.0f, height * HALF };
        } else if (angle == ROTATION_180) {
            offset = OffsetF{ width * HALF, 0.0f };
        }
    } else {
        if (angle == ROTATION_270) {
            offset = OffsetF{ 0.0f, height * HALF };
        } else if (angle == ROTATION_0) {
            offset = OffsetF{ width * HALF, 0.0f };
        }
    }
    rect.SetOffset(offset);
    return rect;
}

RectF NavDestinationNodeBase::CalcFullClipRectForTransition(const SizeF& frameSize)
{
    auto angle = rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
    RectF rect;
    if (angle == ROTATION_90 || angle == ROTATION_270) {
        rect = RectF(0.0f, 0.0f, REMOVE_CLIP_SIZE, frameSize.Height());
    } else {
        rect = RectF(0.0f, 0.0f, frameSize.Width(), REMOVE_CLIP_SIZE);
    }
    return rect;
}

OffsetF NavDestinationNodeBase::CalcTranslateForTransitionPushStart(const SizeF& frameSize, bool transitionIn)
{
    if (!transitionIn) {
        return OffsetF{ 0.0f, 0.0f };
    }
    auto angle = rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
    float isRTL = GetLanguageDirection();
    float width = frameSize.Width();
    if (angle == ROTATION_90 || angle == ROTATION_270) {
        width = frameSize.Height();
    }
    auto translate = OffsetF{ width * HALF * isRTL, 0.0f };
    return translate;
}

OffsetF NavDestinationNodeBase::CalcTranslateForTransitionPushEnd(const SizeF& frameSize, bool transitionIn)
{
    if (transitionIn) {
        return OffsetF{ 0.0f, 0.0f };
    }
    auto angle = rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
    float isRTL = GetLanguageDirection();
    float width = frameSize.Width();
    if (angle == ROTATION_90 || angle == ROTATION_270) {
        width = frameSize.Height();
    }
    auto translate = OffsetF{ -width * CONTENT_OFFSET_PERCENT * isRTL, 0.0f };
    return translate;
}

OffsetF NavDestinationNodeBase::CalcTranslateForTransitionPopStart(const SizeF& frameSize, bool transitionIn)
{
    if (!transitionIn) {
        return OffsetF{ 0.0f, 0.0f };
    }
    auto angle = rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
    float isRTL = GetLanguageDirection();
    float width = frameSize.Width();
    if (angle == ROTATION_90 || angle == ROTATION_270) {
        width = frameSize.Height();
    }
    auto translate = OffsetF{ -width * CONTENT_OFFSET_PERCENT * isRTL, 0.0f };
    return translate;
}

OffsetF NavDestinationNodeBase::CalcTranslateForTransitionPopEnd(const SizeF& frameSize, bool transitionIn)
{
    if (transitionIn) {
        return OffsetF{ 0.0f, 0.0f };
    }
    auto angle = rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
    float isRTL = GetLanguageDirection();
    float width = frameSize.Width();
    if (angle == ROTATION_90 || angle == ROTATION_270) {
        width = frameSize.Height();
    }
    auto translate = OffsetF{ width * HALF * isRTL, 0.0f };
    return translate;
}

void NavDestinationNodeBase::RestoreRenderContext()
{
    viewportConfig_ = nullptr;
    rotateAngle_ = std::nullopt;
    auto renderContext = GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->SetBaseTranslateInXY(OffsetF(0.0f, 0.0f));
    renderContext->SetBaseRotateInZ(0.0f);
}

void NavDestinationNodeBase::SetPageViewportConfig(const RefPtr<PageViewportConfig>& config)
{
    viewportConfig_ = config;
    if (config) {
        safeAreaInsets_ = config->GetSafeArea();
    } else {
        safeAreaInsets_ = SafeAreaInsets();
    }
    do {
        auto titleNode = AceType::DynamicCast<TitleBarNode>(titleBarNode_);
        CHECK_NULL_BREAK(titleNode);
        auto titleBarPattern = titleNode->GetPattern<TitleBarPattern>();
        CHECK_NULL_BREAK(titleBarPattern);
        titleBarPattern->SetPageViewportConfig(config ? config->Clone() : nullptr);
    } while (false);
    do {
        auto toolbarNode = AceType::DynamicCast<NavToolbarNode>(toolBarNode_);
        CHECK_NULL_BREAK(toolbarNode);
        auto toolBarPattern = toolbarNode->GetPattern<NavToolbarPattern>();
        CHECK_NULL_BREAK(toolBarPattern);
        toolBarPattern->SetPageViewportConfig(config ? config->Clone() : nullptr);
    } while (false);
    do {
        auto contentNode = AceType::DynamicCast<FrameNode>(contentNode_);
        CHECK_NULL_BREAK(contentNode);
        auto contentPattern = contentNode->GetPattern<NavDestinationContentPattern>();
        CHECK_NULL_BREAK(contentPattern);
        contentPattern->SetPageViewportConfig(config ? config->Clone() : nullptr);
    } while (false);
}

LayoutConstraintF NavDestinationNodeBase::AdjustLayoutConstarintIfNeeded(const LayoutConstraintF& originConstraint)
{
    if (!rotateAngle_.has_value() || !viewportConfig_) {
        return originConstraint;
    }
    auto layoutConstraint = viewportConfig_->CreateRootLayoutConstraint();
    ApplySafeArea(safeAreaInsets_, layoutConstraint);
    return layoutConstraint;
}

OffsetF NavDestinationNodeBase::GetParentGlobalOffsetWithSafeArea(bool checkBoundary, bool checkPosition) const
{
    if (rotateAngle_.has_value()) {
        return OffsetF(0.0f, 0.0f);
    }
    return LayoutWrapper::GetParentGlobalOffsetWithSafeArea(checkBoundary, checkPosition);
}

TranslateOptions NavDestinationNodeBase::CalcContentTranslateForDialog(const SizeF& frameSize)
{
    auto angle = rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
    switch (angle) {
        case ROTATION_90:
            return TranslateOptions{ frameSize.Width(), 0.0f, 0.0f };
        case ROTATION_180:
            return TranslateOptions{ 0.0f, -frameSize.Height(), 0.0f };
        case ROTATION_270:
            return TranslateOptions{ -frameSize.Width(), 0.0f, 0.0f };
        default:
            return TranslateOptions{ 0.0f, frameSize.Height(), 0.0f };
    }
}

void NavDestinationNodeBase::AdjustRenderContextIfNeeded()
{
    auto renderContext = GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto angle = rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
    if (angle == ROTATION_0 || isRotated_) {
        return;
    }

    auto geometryNode = GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameRect = geometryNode->GetFrameRect();
    auto frameRectWithSafeArea = geometryNode->GetFrameRect(true);

    FrameNode::ExpandSafeArea();
    frameRect = geometryNode->GetFrameRect();
    frameRectWithSafeArea = geometryNode->GetFrameRect(true);
    auto paintRect = renderContext->GetPaintRectWithoutTransform();
    auto curCenter = paintRect.Center();
    OffsetF targetCenter = curCenter;
    if (angle == ROTATION_90 || angle == ROTATION_270) {
        targetCenter = OffsetF(paintRect.Height() / 2.0f, paintRect.Width() / 2.0f);
    }
    auto offset = targetCenter - curCenter;
    renderContext->SetBaseTranslateInXY(offset);
    renderContext->SetBaseRotateInZ(angle);

    isRotated_ = true;
}

OffsetF NavDestinationNodeBase::CalcTranslateForSlideTransition(
    const SizeF& frameSize, bool isRight, bool isEnter, bool isEnd)
{
    if ((isEnd && isEnter) || (!isEnd && !isEnter)) {
        return OffsetF{ 0.0f, 0.0f };
    }
    auto angle = rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
    float width = frameSize.Width();
    float height = frameSize.Height();
    if (angle == ROTATION_90 || angle == ROTATION_270) {
        std::swap(width, height);
    }

    auto translate = OffsetF{ isRight ? width : 0.0f, isRight ? 0.0f : height };
    return translate;
}
} // namespace OHOS::Ace::NG
