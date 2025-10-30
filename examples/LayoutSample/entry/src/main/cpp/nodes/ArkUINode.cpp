/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License")
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

#include "ArkUINode.h"
#include <cassert>

namespace NativeModule {

ArkUINode::ArkUINode(ArkUI_NodeHandle handle) : ArkUIBaseNode(handle)
{
    nativeModule_ = NativeModuleInstance::GetInstance()->GetNativeNodeAPI();
    // 事件触发时需要通过函数获取对应的事件对象，这边通过设置节点自定义数据将封装类指针保持在组件上，方便后续事件分发
    nativeModule_->setUserData(handle_, this);
    // 注册节点监听事件接受器
    nativeModule_->addNodeEventReceiver(handle_, ArkUINode::NodeEventReceiver);
}

ArkUINode::~ArkUINode()
{
    if (onClick_) {
        nativeModule_->unregisterNodeEvent(handle_, NODE_ON_CLICK);
    }
    if (onTouch_) {
        nativeModule_->unregisterNodeEvent(handle_, NODE_TOUCH_EVENT);
    }
    if (onDisappear_) {
        nativeModule_->unregisterNodeEvent(handle_, NODE_EVENT_ON_DISAPPEAR);
    }
    if (onAppear_) {
        nativeModule_->unregisterNodeEvent(handle_, NODE_EVENT_ON_APPEAR);
    }
    nativeModule_->removeNodeEventReceiver(handle_, ArkUINode::NodeEventReceiver);
}

std::pair<std::string, ArkUI_IntSize> ArkUINode::layoutConstraintExample(std::shared_ptr<ArkUIBaseNode> child)
{
    assert(handle_);

    // Create constraint and set its values.
    auto layoutConstraint = OH_ArkUI_LayoutConstraint_Create();
    OH_ArkUI_LayoutConstraint_SetMinWidth(layoutConstraint, defaultMinSize);
    OH_ArkUI_LayoutConstraint_SetMaxWidth(layoutConstraint, defaultMaxSize);
    OH_ArkUI_LayoutConstraint_SetMinHeight(layoutConstraint, defaultMinSize);
    OH_ArkUI_LayoutConstraint_SetMaxHeight(layoutConstraint, defaultMaxSize);
    OH_ArkUI_LayoutConstraint_SetPercentReferenceWidth(layoutConstraint, defaultPercentReference);
    OH_ArkUI_LayoutConstraint_SetPercentReferenceHeight(layoutConstraint, defaultPercentReference);

    std::string constraint = "MinWidth: " + std::to_string(OH_ArkUI_LayoutConstraint_GetMinWidth(layoutConstraint));
    constraint += "\n";
    constraint += "MaxWidth: " + std::to_string(OH_ArkUI_LayoutConstraint_GetMaxWidth(layoutConstraint));
    constraint += "\n";
    constraint += "MinHeight: " + std::to_string(OH_ArkUI_LayoutConstraint_GetMinHeight(layoutConstraint));
    constraint += "\n";
    constraint += "MaxHeight: " + std::to_string(OH_ArkUI_LayoutConstraint_GetMaxHeight(layoutConstraint));
    constraint += "\n";
    constraint += "PercentReferenceWidth: ";
    constraint += std::to_string(OH_ArkUI_LayoutConstraint_GetPercentReferenceWidth(layoutConstraint));
    constraint += "\n";
    constraint += "PercentReferenceHeight: ";
    constraint += std::to_string(OH_ArkUI_LayoutConstraint_GetPercentReferenceHeight(layoutConstraint));

    // Create a deep copy of old constraint.
    auto layoutConstraintCopy = OH_ArkUI_LayoutConstraint_Copy(layoutConstraint);

    nativeModule_->addChild(handle_, child->GetHandle());
    nativeModule_->measureNode(handle_, layoutConstraint);
    auto size = nativeModule_->getMeasuredSize(handle_);

    constraint += "\n\n";
    constraint += "inner first width: " + std::to_string(size.width);
    constraint += "\n";
    constraint += "inner first height: " + std::to_string(size.height);
    constraint += "\n\n";

    // Check if it is a deep copy.
    OH_ArkUI_LayoutConstraint_SetMaxWidth(layoutConstraintCopy, constraintCopyMaxWidth);
    nativeModule_->measureNode(handle_, layoutConstraintCopy);
    nativeModule_->layoutNode(handle_, defaultLayoutPosition, defaultLayoutPosition);
    size = nativeModule_->getMeasuredSize(handle_);

    constraint += "inner second width: " + std::to_string(size.width);
    constraint += "\n";
    constraint += "inner second height: " + std::to_string(size.height);
    constraint += "\n";

    // Destroy constraints.
    OH_ArkUI_LayoutConstraint_Dispose(layoutConstraint);
    OH_ArkUI_LayoutConstraint_Dispose(layoutConstraintCopy);
    return std::pair<std::string, ArkUI_IntSize>(constraint, size);
}

void ArkUINode::SetWidthLayoutPolicy(int32_t policy)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .i32 = policy }};
    ArkUI_AttributeItem item = { value, 1 };
    nativeModule_->setAttribute(handle_, NODE_WIDTH_LAYOUTPOLICY, &item);
}

void ArkUINode::SetConstraintSize(float minWidth, float maxWidth, float minHeight, float maxHeight)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .f32 = minWidth }, { .f32 = maxWidth },
                                 { .f32 = minHeight }, { .f32 = maxHeight }};
    ArkUI_AttributeItem item = { value, 4 };
    nativeModule_->setAttribute(handle_, NODE_CONSTRAINT_SIZE, &item);
}

void ArkUINode::SetHeightLayoutPolicy(int32_t policy)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .i32 = policy }};
    ArkUI_AttributeItem item = { value, 1 };
    nativeModule_->setAttribute(handle_, NODE_HEIGHT_LAYOUTPOLICY, &item);
}

void ArkUINode::SetWidth(float width)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .f32 = width }};
    ArkUI_AttributeItem item = { value, 1 };
    nativeModule_->setAttribute(handle_, NODE_WIDTH, &item);
}

float ArkUINode::GetWidth()
{
    assert(handle_);
    auto item = nativeModule_->getAttribute(handle_, NODE_WIDTH);
    return item->value->f32;
}

std::string ArkUINode::GetLayoutPositionOH()
{
    assert(handle_);
    ArkUI_IntOffset offset = {};
    std::string offsetValue = "";
    auto err = OH_ArkUI_NodeUtils_GetLayoutPosition(handle_, &offset);
    offsetValue += "LayoutPositionOH\n";
    offsetValue += "id: " + std::string(GetId()) + "\n";
    offsetValue += "err: " + std::to_string(err) + "\n";
    offsetValue += "ArkUI_IntOffset: (" + std::to_string(offset.x) + ", " + std::to_string(offset.y) + ")\n";
    return offsetValue;
}

std::string ArkUINode::GetLayoutPosition()
{
    assert(handle_);
    ArkUI_IntOffset offset = nativeModule_->getLayoutPosition(handle_);
    std::string offsetValue = "";
    offsetValue += "LayoutPosition\n";
    offsetValue += "id: " + std::string(GetId()) + "\n";
    offsetValue += "ArkUI_IntOffset: (" + std::to_string(offset.x) + ", " + std::to_string(offset.y) + ")\n";
    return offsetValue;
}

std::string ArkUINode::GetLayoutPositionInScreen()
{
    assert(handle_);
    ArkUI_IntOffset offset = {};
    std::string offsetValue = "";
    auto err = OH_ArkUI_NodeUtils_GetLayoutPositionInScreen(handle_, &offset);
    offsetValue += "LayoutPositionInScreen\n";
    offsetValue += "id: " + std::string(GetId()) + "\n";
    offsetValue += "err: " + std::to_string(err) + "\n";
    offsetValue += "ArkUI_IntOffset: (" + std::to_string(offset.x) + ", " + std::to_string(offset.y) + ")\n";
    return offsetValue;
}

std::string ArkUINode::GetPositionWithTranslateInScreen()
{
    assert(handle_);
    ArkUI_IntOffset offset = {};
    std::string offsetValue = "";
    auto err = OH_ArkUI_NodeUtils_GetPositionWithTranslateInScreen(handle_, &offset);
    offsetValue += "PositionWithTranslateInScreen\n";
    offsetValue += "id: " + std::string(GetId()) + "\n";
    offsetValue += "err: " + std::to_string(err) + "\n";
    offsetValue += "ArkUI_IntOffset: (" + std::to_string(offset.x) + ", " + std::to_string(offset.y) + ")\n";
    return offsetValue;
}

void ArkUINode::GetPositionToParent()
{
    assert(handle_);
    ArkUI_IntOffset offset = {};
    auto err = OH_ArkUI_NodeUtils_GetPositionToParent(handle_, &offset);
    std::string value = "";
    value += "GetPositionToParent： (" + std::to_string(offset.x) + ", " + std::to_string(offset.y) + ")\n";
    OH_LOG_INFO(LOG_APP, "%{public}s", value.c_str());
}

std::string ArkUINode::GetLayoutPositionInWindow()
{
    assert(handle_);
    ArkUI_IntOffset offset = {};
    std::string offsetValue = "";
    auto err = OH_ArkUI_NodeUtils_GetLayoutPositionInWindow(handle_, &offset);
    offsetValue += "LayoutPositionInWindow\n";
    offsetValue += "id: " + std::string(GetId()) + "\n";
    offsetValue += "err: " + std::to_string(err) + "\n";
    offsetValue += "ArkUI_IntOffset: (" + std::to_string(offset.x) + ", " + std::to_string(offset.y) + ")\n";
    return offsetValue;
}

std::string ArkUINode::GetLayoutSize()
{
    assert(handle_);
    ArkUI_IntSize intSize = {};
    std::string intSizeValue = "";
    auto err = OH_ArkUI_NodeUtils_GetLayoutSize(handle_, &intSize);
    intSizeValue += "GetLayoutSize\n";
    intSizeValue += "id: " + std::string(GetId()) + "\n";
    intSizeValue += "err: " + std::to_string(err) + "\n";
    intSizeValue +=
        "ArkUI_IntSize: (" + std::to_string(intSize.width) + ", " + std::to_string(intSize.height) + ")\n";
    return intSizeValue;
}

void ArkUINode::SetHeight(float height)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .f32 = height }};
    ArkUI_AttributeItem item = { value, 1 };
    nativeModule_->setAttribute(handle_, NODE_HEIGHT, &item);
}

void ArkUINode::SetPercentWidth(float percent)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .f32 = percent }};
    ArkUI_AttributeItem item = { value, 1 };
    nativeModule_->setAttribute(handle_, NODE_WIDTH_PERCENT, &item);
}

void ArkUINode::SetPercentHeight(float percent)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .f32 = percent }};
    ArkUI_AttributeItem item = { value, 1 };
    nativeModule_->setAttribute(handle_, NODE_HEIGHT_PERCENT, &item);
}

void ArkUINode::SetPositionEdges(void *positionEdge)
{
    assert(handle_);
    ArkUI_AttributeItem item = { .object = positionEdge };
    nativeModule_->setAttribute(handle_, NODE_POSITION_EDGES, &item);
}

void ArkUINode::SetBackgroundColor(uint32_t color)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .u32 = color }};
    ArkUI_AttributeItem item = { value, 1 };
    nativeModule_->setAttribute(handle_, NODE_BACKGROUND_COLOR, &item);
}

std::string ArkUINode::SetPositionEdgesExample(float top, float left, float bottom, float right)
{
    auto positionEdges = OH_ArkUI_PositionEdges_Create();
    if (top != -1) {
        OH_ArkUI_PositionEdges_SetTop(positionEdges, top);
    }
    if (left != -1) {
        OH_ArkUI_PositionEdges_SetLeft(positionEdges, left);
    }
    if (bottom != -1) {
        OH_ArkUI_PositionEdges_SetBottom(positionEdges, bottom);
    }
    if (right != -1) {
        OH_ArkUI_PositionEdges_SetRight(positionEdges, right);
    }
    SetPositionEdges(positionEdges);
    std::string positionEdgesValue = "";
    positionEdgesValue += "PositionEdges\n";
    float value;
    OH_ArkUI_PositionEdges_GetTop(positionEdges, &value);
    positionEdgesValue += "Top: " + std::to_string(value) + "\n";
    OH_ArkUI_PositionEdges_GetLeft(positionEdges, &value);
    positionEdgesValue += "Left: " + std::to_string(value) + "\n";
    OH_ArkUI_PositionEdges_GetBottom(positionEdges, &value);
    positionEdgesValue += "Bottom: " + std::to_string(value) + "\n";
    OH_ArkUI_PositionEdges_GetRight(positionEdges, &value);
    positionEdgesValue += "Right: " + std::to_string(value) + "\n";

    auto positionEdgesCopy = OH_ArkUI_PositionEdges_Copy(positionEdges);
    OH_ArkUI_PositionEdges_GetTop(positionEdgesCopy, &value);
    positionEdgesValue += "TopCopy: " + std::to_string(value) + "\n";
    OH_ArkUI_PositionEdges_GetLeft(positionEdgesCopy, &value);
    positionEdgesValue += "LeftCopy: " + std::to_string(value) + "\n";
    OH_ArkUI_PositionEdges_GetBottom(positionEdgesCopy, &value);
    positionEdgesValue += "BottomCopy: " + std::to_string(value) + "\n";
    OH_ArkUI_PositionEdges_GetRight(positionEdgesCopy, &value);
    positionEdgesValue += "RightCopy: " + std::to_string(value) + "\n";

    OH_ArkUI_PositionEdges_Dispose(positionEdges);
    OH_ArkUI_PositionEdges_Dispose(positionEdgesCopy);
    return positionEdgesValue;
}

void ArkUINode::SetPixelRound(void *pixelRound)
{
    assert(handle_);
    ArkUI_AttributeItem item = { .object = pixelRound };
    nativeModule_->setAttribute(handle_, NODE_PIXEL_ROUND, &item);
}

std::string ArkUINode::SetPixelRoundExample(ArkUI_PixelRoundCalcPolicy top, ArkUI_PixelRoundCalcPolicy start,
                                            ArkUI_PixelRoundCalcPolicy bottom, ArkUI_PixelRoundCalcPolicy end)
{
    assert(handle_);
    auto pixelRoundPolicy = OH_ArkUI_PixelRoundPolicy_Create();
    OH_ArkUI_PixelRoundPolicy_SetStart(pixelRoundPolicy, start);
    OH_ArkUI_PixelRoundPolicy_SetTop(pixelRoundPolicy, top);
    OH_ArkUI_PixelRoundPolicy_SetBottom(pixelRoundPolicy, bottom);
    OH_ArkUI_PixelRoundPolicy_SetEnd(pixelRoundPolicy, end);
    SetPixelRound(pixelRoundPolicy);
    std::string pixelRoundValue = "";
    auto value = std::make_shared<ArkUI_PixelRoundCalcPolicy>();
    pixelRoundValue += "PixelRoundPolicy\n";
    OH_ArkUI_PixelRoundPolicy_GetStart(pixelRoundPolicy, value.get());
    pixelRoundValue += "Start: " + std::to_string(*value) + "\n";
    OH_ArkUI_PixelRoundPolicy_GetTop(pixelRoundPolicy, value.get());
    pixelRoundValue += "Top: " + std::to_string(*value) + "\n";
    OH_ArkUI_PixelRoundPolicy_GetBottom(pixelRoundPolicy, value.get());
    pixelRoundValue += "Bottom: " + std::to_string(*value) + "\n";
    OH_ArkUI_PixelRoundPolicy_GetEnd(pixelRoundPolicy, value.get());
    pixelRoundValue += "End: " + std::to_string(*value) + "\n";

    OH_ArkUI_PixelRoundPolicy_Dispose(pixelRoundPolicy);
    return pixelRoundValue;
}

void ArkUINode::SetDisplayPriority(uint32_t priority)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .u32 = priority }};
    ArkUI_AttributeItem item = { value, 1 };
    nativeModule_->setAttribute(handle_, NODE_DISPLAY_PRIORITY, &item);
}

void ArkUINode::SetLayoutRect(int32_t positionX, int32_t positionY, int32_t width, int32_t height)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .i32 = positionX }, { .i32 = positionY }, { .i32 = width }, { .i32 = height }};
    ArkUI_AttributeItem item = { value, 4 };
    nativeModule_->setAttribute(handle_, NODE_LAYOUT_RECT, &item);
}

void ArkUINode::SetExpandSafeArea(uint32_t type, uint32_t edge)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .u32 = type }, { .u32 = edge }};
    ArkUI_AttributeItem item = { value, 2 };
    nativeModule_->setAttribute(handle_, NODE_EXPAND_SAFE_AREA, &item);
}

void ArkUINode::SetAlignSelf(int32_t align)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .i32 = align }};
    ArkUI_AttributeItem item = { value, 1 };
    nativeModule_->setAttribute(handle_, NODE_ALIGN_SELF, &item);
}

void ArkUINode::SetTextAlignment(int32_t align)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .i32 = align }};
    ArkUI_AttributeItem item = { value, 1 };
    nativeModule_->setAttribute(handle_, NODE_TEXT_ALIGN, &item);
}

void ArkUINode::SetPadding(float top, float right, float bottom, float left)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .f32 = top }, { .f32 = right }, { .f32 = bottom }, { .f32 = left }};
    ArkUI_AttributeItem item = { value, 4 };
    nativeModule_->setAttribute(handle_, NODE_PADDING, &item);
}

void ArkUINode::SetPadding(float padding)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .f32 = padding }};
    ArkUI_AttributeItem item = { value, 1 };
    nativeModule_->setAttribute(handle_, NODE_PADDING, &item);
}

void ArkUINode::SetPercentPadding(float top, float right, float bottom, float left)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .f32 = top }, { .f32 = right }, { .f32 = bottom }, { .f32 = left }};
    ArkUI_AttributeItem item = { value, 4 };
    nativeModule_->setAttribute(handle_, NODE_PADDING_PERCENT, &item);
}

void ArkUINode::SetPercentPadding(float percentPadding)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .f32 = percentPadding }};
    ArkUI_AttributeItem item = { value, 1 };
    nativeModule_->setAttribute(handle_, NODE_PADDING_PERCENT, &item);
}

void ArkUINode::SetBorderWidth(float top, float right, float bottom, float left)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .f32 = top }, { .f32 = right }, { .f32 = bottom }, { .f32 = left }};
    ArkUI_AttributeItem item = { value, 4 };
    nativeModule_->setAttribute(handle_, NODE_BORDER_WIDTH, &item);
}

void ArkUINode::SetBorderWidth(float borderWidth)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .f32 = borderWidth }};
    ArkUI_AttributeItem item = { value, 1 };
    nativeModule_->setAttribute(handle_, NODE_BORDER_WIDTH, &item);
}

void ArkUINode::SetBorderRadius(float upperLeft, float upperRight, float lowerLeft, float lowerRight)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .f32 = upperLeft }, { .f32 = upperRight },
                                 { .f32 = lowerLeft }, { .f32 = lowerRight }};
    ArkUI_AttributeItem item = { value, 4 };
    nativeModule_->setAttribute(handle_, NODE_BORDER_RADIUS, &item);
}

void ArkUINode::SetStackAlignContent(int32_t align)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .i32 = align }};
    ArkUI_AttributeItem item = { value, 1 };
    nativeModule_->setAttribute(handle_, NODE_STACK_ALIGN_CONTENT, &item);
}

void ArkUINode::SetBorderRadius(float borderRadius)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .f32 = borderRadius }};
    ArkUI_AttributeItem item = { value, 1 };
    nativeModule_->setAttribute(handle_, NODE_BORDER_RADIUS, &item);
}

void ArkUINode::SetBorderColor(uint32_t upperLeft, uint32_t upperRight, uint32_t lowerLeft, uint32_t lowerRight)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .u32 = upperLeft }, { .u32 = upperRight },
                                 { .u32 = lowerLeft }, { .u32 = lowerRight }};
    ArkUI_AttributeItem item = { value, 4 };
    nativeModule_->setAttribute(handle_, NODE_BORDER_COLOR, &item);
}

void ArkUINode::SetBorderColor(uint32_t borderColor)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .u32 = borderColor }};
    ArkUI_AttributeItem item = { value, 1 };
    nativeModule_->setAttribute(handle_, NODE_BORDER_COLOR, &item);
}

void ArkUINode::SetBorderStyle(int32_t upperLeft, int32_t upperRight, int32_t lowerLeft, int32_t lowerRight)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .i32 = upperLeft },
        { .i32 = upperRight }, { .i32 = lowerLeft }, { .i32 = lowerRight }};
    ArkUI_AttributeItem item = { value, 4 };
    nativeModule_->setAttribute(handle_, NODE_BORDER_STYLE, &item);
}

void ArkUINode::SetBorderStyle(int32_t borderStyle)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .i32 = borderStyle }};
    ArkUI_AttributeItem item = { value, 1 };
    nativeModule_->setAttribute(handle_, NODE_BORDER_STYLE, &item);
}

void ArkUINode::SetMargin(float top, float right, float bottom, float left)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .f32 = top }, { .f32 = right }, { .f32 = bottom }, { .f32 = left }};
    ArkUI_AttributeItem item = { value, 4 };
    nativeModule_->setAttribute(handle_, NODE_MARGIN, &item);
}

void ArkUINode::SetMargin(float margin)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .f32 = margin }};
    ArkUI_AttributeItem item = { value, 1 };
    nativeModule_->setAttribute(handle_, NODE_MARGIN, &item);
}

void ArkUINode::SetPercentMargin(float top, float right, float bottom, float left)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .f32 = top }, { .f32 = right }, { .f32 = bottom }, { .f32 = left }};
    ArkUI_AttributeItem item = { value, 4 };
    nativeModule_->setAttribute(handle_, NODE_MARGIN_PERCENT, &item);
}

void ArkUINode::SetPercentMargin(float percentMargin)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .f32 = percentMargin }};
    ArkUI_AttributeItem item = { value, 1 };
    nativeModule_->setAttribute(handle_, NODE_MARGIN_PERCENT, &item);
}

void ArkUINode::SetFlexShrink(float shrink)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .f32 = shrink }};
    ArkUI_AttributeItem item = { value, 1 };
    nativeModule_->setAttribute(handle_, NODE_FLEX_SHRINK, &item);
}

void ArkUINode::SetFlexGrow(float grow)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .f32 = grow }};
    ArkUI_AttributeItem item = { value, 1 };
    nativeModule_->setAttribute(handle_, NODE_FLEX_GROW, &item);
}

void ArkUINode::SetFlexBasis(float basis)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .f32 = basis }};
    ArkUI_AttributeItem item = { value, 1 };
    nativeModule_->setAttribute(handle_, NODE_FLEX_BASIS, &item);
}

void ArkUINode::SetPosition(float x, float y)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .f32 = x }, { .f32 = y }};
    ArkUI_AttributeItem item = { value, 2 };
    nativeModule_->setAttribute(handle_, NODE_POSITION, &item);
}

void ArkUINode::SetOffset(float x, float y)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .f32 = x }, { .f32 = y }};
    ArkUI_AttributeItem item = { value, 2 };
    nativeModule_->setAttribute(handle_, NODE_OFFSET, &item);
}

void ArkUINode::SetDirection(int32_t direct)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .i32 = direct }};
    ArkUI_AttributeItem item = { value, 1 };
    nativeModule_->setAttribute(handle_, NODE_DIRECTION, &item);
}

void ArkUINode::SetAspectRatio(float ratio)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .f32 = ratio }};
    ArkUI_AttributeItem item = { value, 1 };
    nativeModule_->setAttribute(handle_, NODE_ASPECT_RATIO, &item);
}

void ArkUINode::SetSize(float width, float height)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .f32 = width }, { .f32 = height }};
    ArkUI_AttributeItem item = { value, 2 };
    nativeModule_->setAttribute(handle_, NODE_SIZE, &item);
}

void ArkUINode::SetColumnJustifyContent(int32_t justifyContent)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .i32 = justifyContent }};
    ArkUI_AttributeItem item = { value, 1 };
    nativeModule_->setAttribute(handle_, NODE_COLUMN_JUSTIFY_CONTENT, &item);
}

void ArkUINode::SetColumnAlignItems(int32_t align)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .i32 = align }};
    ArkUI_AttributeItem item = { value, 1 };
    nativeModule_->setAttribute(handle_, NODE_COLUMN_ALIGN_ITEMS, &item);
}

void ArkUINode::SetAlignment(int32_t align)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .i32 = align }};
    ArkUI_AttributeItem item = { value, 1 };
    nativeModule_->setAttribute(handle_, NODE_ALIGNMENT, &item);
}

void ArkUINode::SetRowAlignItems(int32_t align)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .i32 = align }};
    ArkUI_AttributeItem item = { value, 1 };
    nativeModule_->setAttribute(handle_, NODE_ROW_ALIGN_ITEMS, &item);
}

void ArkUINode::SetId(const char *id)
{
    assert(handle_);
    ArkUI_AttributeItem item = {nullptr, 0, id };
    nativeModule_->setAttribute(handle_, NODE_ID, &item);
}

void ArkUINode::SetAlignRules(void *alignRules)
{
    assert(handle_);
    ArkUI_AttributeItem item = { .object = alignRules };
    nativeModule_->setAttribute(handle_, NODE_ALIGN_RULES, &item);
}

void ArkUINode::SetBarrier(void *barrier)
{
    assert(handle_);
    ArkUI_AttributeItem item = { .object = barrier };
    nativeModule_->setAttribute(handle_, NODE_RELATIVE_CONTAINER_BARRIER, &item);
}

void ArkUINode::SetLayoutWeight(uint32_t layoutWeight)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .u32 = layoutWeight }};
    ArkUI_AttributeItem item = { value, 1 };
    nativeModule_->setAttribute(handle_, NODE_LAYOUT_WEIGHT, &item);
}

void ArkUINode::SetScrollBar(int32_t displayMode)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .i32 = displayMode }};
    ArkUI_AttributeItem item = { value, 1 };
    nativeModule_->setAttribute(handle_, NODE_SCROLL_BAR_DISPLAY_MODE, &item);
}

void ArkUINode::SetChainMode(int32_t axi, int32_t style)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .i32 = axi }, { .i32 = style }};
    ArkUI_AttributeItem item = { value, 2 };
    nativeModule_->setAttribute(handle_, NODE_RELATIVE_LAYOUT_CHAIN_MODE, &item);
}

void ArkUINode::SetBorderWidthPercent(float width)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .f32 = width }};
    ArkUI_AttributeItem item = { value, 1 };
    nativeModule_->setAttribute(handle_, NODE_BORDER_WIDTH_PERCENT, &item);
}

void ArkUINode::SetBorderWidthPercent(float top, float right, float bottom, float left)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .f32 = top }, { .f32 = right }, { .f32 = bottom }, { .f32 = left }};
    ArkUI_AttributeItem item = { value, 4 };
    nativeModule_->setAttribute(handle_, NODE_BORDER_WIDTH_PERCENT, &item);
}

void ArkUINode::SetBorderRadiusPercent(float radius)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .f32 = radius }};
    ArkUI_AttributeItem item = { value, 1 };
    nativeModule_->setAttribute(handle_, NODE_BORDER_RADIUS_PERCENT, &item);
}

void ArkUINode::SetBorderRadiusPercent(float upperLeft, float upperRight, float lowerLeft, float lowerRight)
{
    assert(handle_);
    ArkUI_NumberValue value[] = {{ .f32 = upperLeft },
        { .f32 = upperRight }, { .f32 = lowerLeft }, { .f32 = lowerRight }};
    ArkUI_AttributeItem item = { value, 4 };
    nativeModule_->setAttribute(handle_, NODE_BORDER_RADIUS_PERCENT, &item);
}

const char *ArkUINode::GetId()
{
    assert(handle_);
    return nativeModule_->getAttribute(handle_, NODE_ID)->string;
}

void ArkUINode::NodeEventReceiver(ArkUI_NodeEvent *event)
{
    // 获取事件发生的UI组件对象
    auto nodeHandle = OH_ArkUI_NodeEvent_GetNodeHandle(event);
    // 获取保持在UI组件对象中的自定义数据，返回封装类指针
    auto *node = reinterpret_cast<ArkUINode *>(
        NativeModuleInstance::GetInstance()->GetNativeNodeAPI()->getUserData(nodeHandle));
    // 基于封装类实例对象处理事件
    node->ProcessNodeEvent(event);
}

void ArkUINode::ProcessNodeEvent(ArkUI_NodeEvent *event)
{
    auto eventType = OH_ArkUI_NodeEvent_GetEventType(event);
    switch (eventType) {
        case NODE_ON_CLICK: {
            if (onClick_) {
                onClick_();
            }
            break;
        }
        case NODE_TOUCH_EVENT: {
            if (onTouch_) {
                auto *uiInputEvent = OH_ArkUI_NodeEvent_GetInputEvent(event);
                float x = OH_ArkUI_PointerEvent_GetX(uiInputEvent);
                float y = OH_ArkUI_PointerEvent_GetY(uiInputEvent);
                auto type = OH_ArkUI_UIInputEvent_GetAction(uiInputEvent);
                onTouch_(type, x, y);
            }
        }
        case NODE_EVENT_ON_DISAPPEAR: {
            if (onDisappear_) {
                onDisappear_();
            }
            break;
        }
        case NODE_EVENT_ON_APPEAR: {
            if (onAppear_) {
                onAppear_();
            }
            break;
        }
        default: {
            // 组件特有事件交给子类处理
            OnNodeEvent(event);
        }
    }
}

void ArkUINode::OnAddChild(const std::shared_ptr<ArkUIBaseNode> &child)
{
    nativeModule_->addChild(handle_, child->GetHandle());
}

void ArkUINode::OnRemoveChild(const std::shared_ptr<ArkUIBaseNode> &child)
{
    nativeModule_->removeChild(handle_, child->GetHandle());
}

void ArkUINode::OnInsertChild(const std::shared_ptr<ArkUIBaseNode> &child, int32_t index)
{
    nativeModule_->insertChildAt(handle_, child->GetHandle(), index);
}

} // namespace NativeModule