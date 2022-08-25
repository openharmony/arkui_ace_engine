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

#include "core/components_v2/inspector/inspector_composed_element.h"

namespace OHOS::Ace::V2 {
InspectorComposedElement::InspectorComposedElement(const ComposeId& id): ComposedElement(id) {}

InspectorComposedElement::~InspectorComposedElement() = default;

void InspectorComposedElement::OnInactive()
{
}

void InspectorComposedElement::OnActive()
{
    inspectorId_ = std::stoi(id_);
}

RefPtr<PopupElementV2> InspectorComposedElement::GetPopupElement() const
{
    return nullptr;
}

RefPtr<Element> InspectorComposedElement::GetElementChildBySlot(const RefPtr<Element>& element, int32_t& slot) const
{
    return nullptr;
}

RefPtr<Element> InspectorComposedElement::GetInspectorComposedElementParent(const RefPtr<Element>& element) const
{
    return nullptr;
}

std::unique_ptr<JsonValue> InspectorComposedElement::ToJsonObject() const
{
    return nullptr;
}

void InspectorComposedElement::Prepare(const WeakPtr<Element>& weakParent)
{
}

void InspectorComposedElement::Update()
{
}

bool InspectorComposedElement::CanUpdate(const RefPtr<Component>& newComponent)
{
    return false;
}

void InspectorComposedElement::AddComposedComponentId()
{
}

void InspectorComposedElement::RemoveInspectorNode(int32_t id)
{
}

RefPtr<RenderNode> InspectorComposedElement::GetInspectorNode(IdType typeId, bool isForward) const
{
    return nullptr;
}

RefPtr<AccessibilityNode> InspectorComposedElement::GetAccessibilityNode() const
{
    return nullptr;
}

RefPtr<RenderBox> InspectorComposedElement::GetRenderBox() const
{
    return nullptr;
}

std::string InspectorComposedElement::GetWidth() const
{
    return "-";
}

std::string InspectorComposedElement::GetHeight() const
{
    return "-";
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetSize() const
{
    return nullptr;
}

std::string InspectorComposedElement::GetPadding() const
{
    return "0.0";
}

std::string InspectorComposedElement::GetAllMargin() const
{
    return "0.0";
}

Dimension InspectorComposedElement::GetMargin(OHOS::Ace::AnimatableType type) const
{
    return Dimension();
}

std::string InspectorComposedElement::GetConstraintSize() const
{
    return std::string();
}

int32_t InspectorComposedElement::GetLayoutPriority() const
{
    return 0;
}

int32_t InspectorComposedElement::GetLayoutWeight() const
{
    return 0;
}

std::string InspectorComposedElement::GetAlign() const
{
    return std::string();
}

std::string InspectorComposedElement::GetDirectionStr() const
{
    return std::string();
}

TextDirection InspectorComposedElement::GetDirection() const
{
    return TextDirection::AUTO;
}

std::string InspectorComposedElement::GetBorderRadius() const
{
    return std::string();
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetUnifyBorder() const
{
    return nullptr;
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetPosition() const
{
    return nullptr;
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetMarkAnchor() const
{
    return nullptr;
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetOffset() const
{
    return nullptr;
}

std::string InspectorComposedElement::GetRect()
{
    return std::string();
}

Rect InspectorComposedElement::GetParentRect() const
{
    return Rect();
}

double InspectorComposedElement::GetAspectRatio() const
{
    return 0.0;
}

int32_t InspectorComposedElement::GetDisplayPriority() const
{
    return 1;
}

std::string InspectorComposedElement::GetFlexBasis() const
{
    return std::string();
}

double InspectorComposedElement::GetFlexGrow() const
{
    return 0.0;
}

double InspectorComposedElement::GetFlexShrink() const
{
    return 0.0;
}

std::string InspectorComposedElement::GetAlignSelf() const
{
    return std::string();
}

Border InspectorComposedElement::GetBorder() const
{
    return Border();
}

std::string InspectorComposedElement::GetBorderStyle() const
{
    return std::string();
}

std::string InspectorComposedElement::GetBorderWidth() const
{
    return std::string();
}

std::string InspectorComposedElement::GetBorderColor() const
{
    return std::string();
}

RefPtr<Decoration> InspectorComposedElement::GetBackDecoration() const
{
    return nullptr;
}

std::string InspectorComposedElement::GetBackgroundImage() const
{
    return std::string();
}

std::string InspectorComposedElement::GetBackgroundColor() const
{
    return std::string();
}

std::string InspectorComposedElement::GetBackgroundImageSize() const
{
    return std::string();
}

std::string InspectorComposedElement::GetBackgroundImagePosition() const
{
    return std::string();
}

std::string InspectorComposedElement::GetAlignmentType(double width, double height) const
{
    return std::string();
}

RefPtr<Decoration> InspectorComposedElement::GetFrontDecoration() const
{
    return nullptr;
}

double InspectorComposedElement::GetOpacity() const
{
    return 0.0;
}

std::string InspectorComposedElement::GetVisibility() const
{
    return std::string();
}

std::string InspectorComposedElement::GetClip() const
{
    return std::string();
}

bool InspectorComposedElement::GetClipFlag() const
{
    auto render = GetRenderBox();
    if (!render) {
        return false;
    }

    return render->GetBoxClipFlag();
}

bool InspectorComposedElement::GetEnabled() const
{
    return false;
}

int32_t InspectorComposedElement::GetZIndex() const
{
    return 0;
}

DimensionOffset InspectorComposedElement::GetOriginPoint() const
{
    return DimensionOffset();
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetRotate() const
{
    return nullptr;
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetScale() const
{
    return nullptr;
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetTransform() const
{
    return nullptr;
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetTranslate() const
{
    return nullptr;
}

double InspectorComposedElement::GetBlur() const
{
    return 0.0;
}

double InspectorComposedElement::GetBackDropBlur() const
{
    return 0.0;
}

double InspectorComposedElement::GetBrightness() const
{
    return 0.0;
}

double InspectorComposedElement::GetSaturate() const
{
    return 0.0;
}

double InspectorComposedElement::GetContrast() const
{
    return 0.0;
}

double InspectorComposedElement::GetInvert() const
{
    return 0.0;
}

double InspectorComposedElement::GetSepia() const
{
    return 0.0;
}

double InspectorComposedElement::GetGrayScale() const
{
    return 0.0;
}

double InspectorComposedElement::GetHueRotate() const
{
    return 0.0;
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetWindowBlur() const
{
    return nullptr;
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetShadow() const
{
    return nullptr;
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetOverlay() const
{
    return nullptr;
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetMask() const
{
    return nullptr;
}

RefPtr<GridColumnInfo> InspectorComposedElement::GetGridColumnInfo() const
{
    return nullptr;
}

int32_t InspectorComposedElement::GetGridSpan() const
{
    return 0;
}

int32_t InspectorComposedElement::GetGridOffset() const
{
    return 0;
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetUseSizeType() const
{
    return nullptr;
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetUseAlign() const
{
    return nullptr;
}

std::string InspectorComposedElement::GetBindPopup() const
{
    return std::string();
}

std::string InspectorComposedElement::GetBindContextMenu() const
{
    return std::string();
}

std::string InspectorComposedElement::GetColorBlend() const
{
    return std::string();
}

void InspectorComposedElement::UpdateEventTarget(BaseEventInfo& info) const
{
}

std::pair<Rect, Offset> InspectorComposedElement::GetCurrentRectAndOrigin() const
{
    return std::pair<Rect, Offset>();
}

void InspectorComposedElement::GetColorsAndRepeating(
    std::unique_ptr<JsonValue>& resultJson, const Gradient& gradient) const
{
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetLinearGradient() const
{
    return nullptr;
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetSweepGradient() const
{
    return nullptr;
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetRadialGradient() const
{
    return nullptr;
}

const std::string& InspectorComposedElement::GetTag() const
{
    return name_;
}

bool InspectorComposedElement::GetClickable() const
{
    return false;
}
bool InspectorComposedElement::GetCheckable() const
{
    return false;
}
bool InspectorComposedElement::GetFocusable() const
{
    return false;
}
bool InspectorComposedElement::GetScrollable() const
{
    return false;
}
bool InspectorComposedElement::GetLongClickable() const
{
    return false;
}
bool InspectorComposedElement::GetTouchable() const
{
    return false;
}
bool InspectorComposedElement::IsSelected() const
{
    return false;
}
bool InspectorComposedElement::IsPassword() const
{
    return false;
}
bool InspectorComposedElement::IsChecked() const
{
    return false;
}
bool InspectorComposedElement::IsFocused() const
{
    return false;
}

void InspectorComposedElement::TriggerVisibleAreaChangeCallback(std::list<VisibleCallbackInfo>& callbackInfoList)
{
}

double InspectorComposedElement::CalculateCurrentVisibleRatio(const Rect& visibleRect, const Rect& renderRect)
{
    return 0.0;
}

void InspectorComposedElement::ProcessAllVisibleCallback(
    std::list<VisibleCallbackInfo>& callbackInfoList, double currentVisibleRatio)
{
}

void InspectorComposedElement::OnVisibleAreaChangeCallback(
    VisibleCallbackInfo& callbackInfo, bool visibleType, double currentVisibleRatio)
{
}

std::string InspectorComposedElement::GetHitTestBehaviorStr() const
{
    return std::string();
}
} // namespace OHOS::Ace::V2
