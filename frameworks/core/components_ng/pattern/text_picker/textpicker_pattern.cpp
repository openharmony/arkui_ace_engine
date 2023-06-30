/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/text_picker/textpicker_pattern.h"

#include <cstdint>
#include <securec.h>

#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/utils/utils.h"
#include "core/components/picker/picker_theme.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_column_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_event_hub.h"
#include "core/components_ng/pattern/text_picker/textpicker_layout_property.h"
#include "core/components_ng/pattern/text_picker/toss_animation_controller.h"
#include "core/components_ng/property/calc_length.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
namespace {
// TODO datepicker style modification
const Dimension PRESS_INTERVAL = 4.0_vp;
const Dimension PRESS_RADIUS = 8.0_vp;
constexpr uint32_t RATE = 2;
} // namespace

void TextPickerPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
}

bool TextPickerPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    CHECK_NULL_RETURN_NOLOG(config.frameSizeChange, false);
    CHECK_NULL_RETURN(dirty, false);
    SetButtonIdeaSize();
    return true;
}

void TextPickerPattern::SetButtonIdeaSize()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto pickerTheme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    auto children = host->GetChildren();
    auto height = pickerTheme->GetDividerSpacing();
    auto width = host->GetGeometryNode()->GetFrameSize().Width() / static_cast<float>(children.size());
    auto defaultWidth = height.ConvertToPx() * 2;
    if (width > defaultWidth) {
        width = static_cast<float>(defaultWidth);
    }
    for (const auto& child : children) {
        auto buttonNode = DynamicCast<FrameNode>(child->GetFirstChild());
        auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
        buttonLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
        buttonLayoutProperty->UpdateType(ButtonType::NORMAL);
        buttonLayoutProperty->UpdateBorderRadius(BorderRadiusProperty(PRESS_RADIUS));
        auto buttonHeight = CalculateHeight() - PRESS_INTERVAL.ConvertToPx() * RATE;
        if (resizeFlag_) {
            buttonHeight = resizePickerItemHeight_ - PRESS_INTERVAL.ConvertToPx() * RATE;
        }
        buttonLayoutProperty->
            UpdateUserDefinedIdealSize(CalcSize(CalcLength(width - PRESS_INTERVAL.ConvertToPx() * RATE),
                CalcLength(buttonHeight)));
        auto buttonConfirmRenderContext = buttonNode->GetRenderContext();
        buttonConfirmRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
        buttonConfirmRenderContext->UpdateBorderRadius({ PRESS_RADIUS, PRESS_RADIUS, PRESS_RADIUS, PRESS_RADIUS });
        buttonNode->MarkModifyDone();
        buttonNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void TextPickerPattern::OnModifyDone()
{
    OnColumnsBuilding();
    FlushOptions();
    CalculateHeight();
    if (cascadeOptions_.size() > 0) {
        SetChangeCallback([weak = WeakClaim(this)](const RefPtr<FrameNode>& tag,
            bool add, uint32_t index, bool notify) {
            auto refPtr = weak.Upgrade();
            CHECK_NULL_VOID_NOLOG(refPtr);
            refPtr->HandleColumnChange(tag, add, index, notify);
        });
    }
    SetEventCallback([weak = WeakClaim(this)](bool refresh) {
        auto refPtr = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(refPtr);
        refPtr->FireChangeEvent(refresh);
    });
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID_NOLOG(focusHub);
    InitOnKeyEvent(focusHub);
    InitDisabled();
}

void TextPickerPattern::SetEventCallback(EventCallback&& value)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto children = host->GetChildren();
    for (const auto& child : children) {
        auto stackNode = DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(stackNode);
        auto childNode = DynamicCast<FrameNode>(stackNode->GetLastChild());
        CHECK_NULL_VOID(childNode);
        auto pickerColumnPattern = childNode->GetPattern<TextPickerColumnPattern>();
        CHECK_NULL_VOID(pickerColumnPattern);
        pickerColumnPattern->SetEventCallback(std::move(value));
    }
}

void TextPickerPattern::FireChangeEvent(bool refresh)
{
    auto frameNodes = GetColumnNodes();
    std::vector<std::string> value;
    std::vector<double> index;
    for (auto it : frameNodes) {
        CHECK_NULL_VOID(it.second);
        auto textPickerColumnPattern = it.second->GetPattern<TextPickerColumnPattern>();
        if (refresh) {
            auto currentIndex = textPickerColumnPattern->GetCurrentIndex();
            index.emplace_back(currentIndex);
            auto currentValue = textPickerColumnPattern->GetOption(currentIndex);
            value.emplace_back(currentValue);
        }
    }
    auto textPickerEventHub = GetEventHub<TextPickerEventHub>();
    CHECK_NULL_VOID(textPickerEventHub);
    textPickerEventHub->FireChangeEvent(value, index);
    textPickerEventHub->FireDialogChangeEvent(GetSelectedObject(true, 1));
}

void TextPickerPattern::InitDisabled()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto renderContext = host->GetRenderContext();
    enabled_ = eventHub->IsEnabled();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

RefPtr<FrameNode> TextPickerPattern::GetColumnNode()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);

    auto stackNode = host->GetChildAtIndex(focusKeyID_);
    CHECK_NULL_RETURN(stackNode, nullptr);

    auto columnNode = stackNode->GetLastChild();
    CHECK_NULL_RETURN(columnNode, nullptr);

    return DynamicCast<FrameNode>(columnNode);
}

std::map<uint32_t, RefPtr<FrameNode>> TextPickerPattern::GetColumnNodes()
{
    std::map<uint32_t, RefPtr<FrameNode>> allChildNode;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, allChildNode);
    auto children = host->GetChildren();
    uint32_t index = 0;
    for (auto iter = children.begin(); iter != children.end(); iter++) {
        CHECK_NULL_RETURN(*iter, allChildNode);
        auto stackNode = DynamicCast<FrameNode>(*iter);
        auto currentNode = DynamicCast<FrameNode>(stackNode->GetLastChild());
        allChildNode[index] = currentNode;
        index++;
    }
    return allChildNode;
}

void TextPickerPattern::OnColumnsBuildingCascade()
{
    auto frameNodes = GetColumnNodes();
    auto count = frameNodes.size();
    for (size_t index = 0; index < count; index++) {
        CHECK_NULL_VOID(frameNodes[index]);
        auto textPickerColumnPattern = frameNodes[index]->GetPattern<TextPickerColumnPattern>();
        CHECK_NULL_VOID(textPickerColumnPattern);
        if (cascadeOptions_.size() > 0) {
            selectedIndex_ = cascadeOptions_[index].rangeResult.empty() ? 0 :
                selecteds_[index] % cascadeOptions_[index].rangeResult.size();
            textPickerColumnPattern->SetCurrentIndex(selectedIndex_);
            std::vector<NG::RangeContent> rangeContents;
            for (uint32_t i = 0; i < cascadeOptions_[index].rangeResult.size(); i++) {
                NG::RangeContent rangeContent;
                rangeContent.text_ = cascadeOptions_[index].rangeResult[i];
                rangeContents.emplace_back(rangeContent);
            }
            textPickerColumnPattern->SetOptions(rangeContents);
            textPickerColumnPattern->SetColumnKind(NG::TEXT);
            optionsWithNode_[frameNodes[index]] = rangeContents;
            frameNodes[index]->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
    }
}

void TextPickerPattern::OnColumnsBuildingUnCascade()
{
    auto frameNodes = GetColumnNodes();
    for (auto it : frameNodes) {
        CHECK_NULL_VOID(it.second);
        auto textPickerColumnPattern = it.second->GetPattern<TextPickerColumnPattern>();
        CHECK_NULL_VOID(textPickerColumnPattern);
        if (cascadeOptions_.size() > 0) {
            selectedIndex_ = cascadeOptions_[it.first].rangeResult.empty() ? 0 :
                selecteds_[it.first] % cascadeOptions_[it.first].rangeResult.size();
            textPickerColumnPattern->SetCurrentIndex(selectedIndex_);
            std::vector<NG::RangeContent> rangeContents;
            for (uint32_t i = 0; i < cascadeOptions_[it.first].rangeResult.size(); i++) {
                NG::RangeContent rangeContent;
                rangeContent.text_ = cascadeOptions_[it.first].rangeResult[i];
                rangeContents.emplace_back(rangeContent);
            }
            textPickerColumnPattern->SetOptions(rangeContents);
            textPickerColumnPattern->SetColumnKind(NG::TEXT);
            optionsWithNode_[it.second] = rangeContents;
            it.second->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        } else {
            ClearOption();
            for (const auto& item : range_) {
                AppendOption(item);
            }
            selectedIndex_ = range_.empty() ? 0 : GetSelected() % range_.size();
            textPickerColumnPattern->SetCurrentIndex(selectedIndex_);
            textPickerColumnPattern->SetOptions(options_);
            textPickerColumnPattern->SetColumnKind(columnsKind_);
            it.second->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
    }
}

void TextPickerPattern::OnColumnsBuilding()
{
    if (!isCascade_) {
        OnColumnsBuildingUnCascade();
    } else {
        OnColumnsBuildingCascade();
    }
}

void TextPickerPattern::SetSelecteds(const std::vector<uint32_t>& values)
{
    selecteds_.clear();
    for (auto& value : values) {
        selecteds_.emplace_back(value);
    }
    if (isCascade_) {
        auto columnCount = cascadeOptions_.size();
        cascadeOptions_.clear();
        ProcessCascadeOptions(cascadeOriginptions_, cascadeOptions_, 0);
        if (cascadeOptions_.size() < columnCount) {
            auto differ = columnCount - cascadeOptions_.size();
            for (uint32_t i = 0; i < differ; i++) {
                NG::TextCascadePickerOptions differOption;
                memset_s(&differOption, sizeof(differOption), 0, sizeof(differOption));
                cascadeOptions_.emplace_back(differOption);
            }
        }
    }
}

void TextPickerPattern::FlushOptions()
{
    auto frameNodes = GetColumnNodes();
    for (auto it : frameNodes) {
        CHECK_NULL_VOID(it.second);
        auto columnPattern = it.second->GetPattern<TextPickerColumnPattern>();
        CHECK_NULL_VOID(columnPattern);
        columnPattern->FlushCurrentOptions();
        it.second->MarkModifyDone();
        it.second->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

double TextPickerPattern::CalculateHeight()
{
    double height = 0.0;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, height);
    auto textPickerLayoutProperty = host->GetLayoutProperty<TextPickerLayoutProperty>();
    CHECK_NULL_RETURN(textPickerLayoutProperty, height);
    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, height);
    auto pickerTheme = context->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, height);
    if (textPickerLayoutProperty->HasDefaultPickerItemHeight()) {
        auto defaultPickerItemHeightValue = textPickerLayoutProperty->GetDefaultPickerItemHeightValue();
        if (context->NormalizeToPx(defaultPickerItemHeightValue) <= 0) {
            height = pickerTheme->GetDividerSpacing().ConvertToPx();
            return height;
        }
        if (defaultPickerItemHeightValue.Unit() == DimensionUnit::PERCENT) {
            height = pickerTheme->GetGradientHeight().ConvertToPx() * defaultPickerItemHeightValue.Value();
        } else {
            height = context->NormalizeToPx(defaultPickerItemHeightValue);
        }
    } else {
        height = pickerTheme->GetDividerSpacing().ConvertToPx();
    }
    if (defaultPickerItemHeight_ != height) {
        defaultPickerItemHeight_ = height;
        PaintFocusState();
        SetButtonIdeaSize();
    }
    auto frameNodes = GetColumnNodes();
    for (auto it : frameNodes) {
        CHECK_NULL_RETURN(it.second, height);
        auto textPickerColumnPattern = it.second->GetPattern<TextPickerColumnPattern>();
        CHECK_NULL_RETURN(textPickerColumnPattern, height);
        textPickerColumnPattern->SetDefaultPickerItemHeight(height);
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    return height;
}

void TextPickerPattern::InitOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        CHECK_NULL_RETURN_NOLOG(pattern, false);
        return pattern->OnKeyEvent(event);
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));

    auto getInnerPaintRectCallback = [wp = WeakClaim(this)](RoundRect& paintRect) {
        auto pattern = wp.Upgrade();
        if (pattern) {
            pattern->GetInnerFocusPaintRect(paintRect);
        }
    };
    focusHub->SetInnerFocusPaintRectCallback(getInnerPaintRectCallback);
}

void TextPickerPattern::PaintFocusState()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    RoundRect focusRect;
    GetInnerFocusPaintRect(focusRect);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->PaintInnerFocusState(focusRect);

    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextPickerPattern::GetInnerFocusPaintRect(RoundRect& paintRect)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto childSize = host->GetChildren().size();
    if (childSize == 0) {
        return;
    }
    auto columnNode = GetColumnNode();
    CHECK_NULL_VOID(columnNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    auto frameWidth = host->GetGeometryNode()->GetFrameSize().Width();
    auto dividerSpacing = pipeline->NormalizeToPx(pickerTheme->GetDividerSpacing());
    auto pickerThemeWidth = dividerSpacing * 2;

    auto centerX = (frameWidth / childSize - pickerThemeWidth) / 2 +
                   columnNode->GetGeometryNode()->GetFrameRect().Width() * focusKeyID_ +
                   PRESS_INTERVAL.ConvertToPx() * 2;
    auto centerY =
        (host->GetGeometryNode()->GetFrameSize().Height() - dividerSpacing) / 2 + PRESS_INTERVAL.ConvertToPx();

    paintRect.SetRect(RectF(centerX, centerY, (dividerSpacing - PRESS_INTERVAL.ConvertToPx()) * 2,
        dividerSpacing - PRESS_INTERVAL.ConvertToPx() * 2));
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS, static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()),
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS, static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()),
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS, static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()),
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS, static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()),
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
}

bool TextPickerPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN) {
        return false;
    }

    if (event.code == KeyCode::KEY_SPACE || event.code == KeyCode::KEY_ENTER) {
        if (!operationOn_ && event.code == KeyCode::KEY_ENTER) {
            HandleDirectionKey(event.code);
        }
        operationOn_ = (event.code == KeyCode::KEY_SPACE) || (event.code == KeyCode::KEY_ENTER);
        return true;
    }

    if (event.code == KeyCode::KEY_TAB) {
        operationOn_ = false;
        return false;
    }

    if (event.code == KeyCode::KEY_DPAD_UP || event.code == KeyCode::KEY_DPAD_DOWN ||
        event.code == KeyCode::KEY_DPAD_LEFT || event.code == KeyCode::KEY_DPAD_RIGHT) {
        if (operationOn_) {
            HandleDirectionKey(event.code);
        }
        return true;
    }
    return false;
}

void TextPickerPattern::SetChangeCallback(ColumnChangeCallback&& value)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto children = host->GetChildren();
    for (const auto& child : children) {
        auto stackNode = DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(stackNode);
        auto childNode = DynamicCast<FrameNode>(stackNode->GetLastChild());
        CHECK_NULL_VOID(childNode);
        auto textPickerColumnPattern = childNode->GetPattern<TextPickerColumnPattern>();
        CHECK_NULL_VOID(textPickerColumnPattern);
        textPickerColumnPattern->SetChangeCallback(std::move(value));
    }
}

size_t TextPickerPattern::ProcessCascadeOptionDepth(const NG::TextCascadePickerOptions& option)
{
    size_t depth = 1;
    if (option.children.empty()) {
        return depth;
    }

    for (auto& pos : option.children) {
        size_t tmpDep = 1;
        tmpDep += ProcessCascadeOptionDepth(pos);
        if (tmpDep > depth) {
            depth = tmpDep;
        }
    }
    return depth;
}

bool TextPickerPattern::ChangeCurrentOptionValue(NG::TextCascadePickerOptions& option,
    uint32_t value, uint32_t curColumn, uint32_t replaceColumn)
{
    if (curColumn >= replaceColumn) {
        selecteds_[curColumn] = value;
        values_[curColumn] = "";
    }

    for (uint32_t valueIndex = 0; valueIndex < option.children.size(); valueIndex++) {
        if (curColumn >= replaceColumn) {
            if (ChangeCurrentOptionValue(option.children[valueIndex], 0, curColumn + 1, replaceColumn)) {
                return true;
            }
        } else {
            if (ChangeCurrentOptionValue(option.children[valueIndex], value, curColumn + 1, replaceColumn)) {
                return true;
            }
        }
    }
    return false;
}

void TextPickerPattern::ProcessCascadeOptionsValues(const std::vector<std::string>& rangeResultValue,
    uint32_t index)
{
    auto valueIterator = std::find(rangeResultValue.begin(), rangeResultValue.end(), values_[index]);
    if (valueIterator != rangeResultValue.end()) {
        if (index < selecteds_.size()) {
            selecteds_[index] = std::distance(rangeResultValue.begin(), valueIterator);
        } else {
            selecteds_.emplace_back(std::distance(rangeResultValue.begin(), valueIterator));
        }
    } else {
        if (index < selecteds_.size()) {
            selecteds_[index] = 0;
        } else {
            selecteds_.emplace_back(0);
        }
    }
}

void TextPickerPattern::ProcessCascadeOptions(const std::vector<NG::TextCascadePickerOptions>& options,
    std::vector<NG::TextCascadePickerOptions>& reOptions, uint32_t index)
{
    std::vector<std::string> rangeResultValue;
    NG::TextCascadePickerOptions option;
    for (size_t i = 0; i < options.size(); i++) {
        if (!options[i].rangeResult.empty()) {
            rangeResultValue.emplace_back(options[i].rangeResult[0]);
        }
    }
    option.rangeResult = rangeResultValue;
    for (size_t i = 0; i < options.size(); i++) {
        if (index < selecteds_.size() &&
            ((selecteds_[index] != 0 && !isHasSelectAttr_) || isHasSelectAttr_)) {
            if (selecteds_[index] < 0 && selecteds_[index] > options.size()) {
                selecteds_[index] = 0;
            }
            option.children = options[selecteds_[index]].children;
            reOptions.emplace_back(option);
            return ProcessCascadeOptions(options[selecteds_[index]].children, reOptions, index + 1);
        }
        if (index < values_.size() && values_[index] != "") {
            ProcessCascadeOptionsValues(rangeResultValue, index);
            option.children = options[selecteds_[index]].children;
            reOptions.emplace_back(option);
            return ProcessCascadeOptions(options[selecteds_[index]].children, reOptions, index + 1);
        }
        if (i == options.size() - 1) {
            option.children = options[0].children;
            reOptions.emplace_back(option);
            return ProcessCascadeOptions(options[0].children, reOptions, index + 1);
        }
    }
}

void TextPickerPattern::SupplementOption(const std::vector<NG::TextCascadePickerOptions>& reOptions,
    std::vector<NG::RangeContent>& rangeContents, uint32_t patterIndex)
{
    for (uint32_t i = 0; i < reOptions[patterIndex].rangeResult.size(); i++) {
        NG::RangeContent rangeContent;
        rangeContent.text_ = reOptions[patterIndex].rangeResult[i];
        rangeContents.emplace_back(rangeContent);
    }
}

void TextPickerPattern::HandleColumnChange(const RefPtr<FrameNode>& tag, bool isAdd,
    uint32_t index, bool needNotify)
{
    if (isCascade_) {
        auto frameNodes = GetColumnNodes();
        auto columnIndex = 0;
        for (auto iter = frameNodes.begin(); iter != frameNodes.end(); iter++) {
            if (iter->second->GetId() == tag->GetId()) {
                break;
            }
            columnIndex++;
        }
        for (uint32_t valueIndex = 0; valueIndex < cascadeOriginptions_.size(); valueIndex++) {
            ChangeCurrentOptionValue(cascadeOriginptions_[valueIndex], index, 0, columnIndex);
        }

        std::vector<NG::TextCascadePickerOptions> reOptions;
        ProcessCascadeOptions(cascadeOriginptions_, reOptions, 0);
        // Next Column Update Value
        columnIndex = columnIndex + 1;
        for (uint32_t patterIndex = columnIndex; patterIndex < frameNodes.size(); patterIndex++) {
            auto patternNode = frameNodes[patterIndex];
            CHECK_NULL_VOID(patternNode);
            auto textPickerColumnPattern = patternNode->GetPattern<TextPickerColumnPattern>();
            CHECK_NULL_VOID(textPickerColumnPattern);
            if (patterIndex < reOptions.size()) {
                auto currentSelectedIndex = reOptions[patterIndex].rangeResult.empty() ? 0 :
                             selecteds_[patterIndex] % reOptions[patterIndex].rangeResult.size();
                std::vector<NG::RangeContent> rangeContents;
                SupplementOption(reOptions, rangeContents, patterIndex);
                textPickerColumnPattern->SetCurrentIndex(currentSelectedIndex);
                textPickerColumnPattern->SetOptions(rangeContents);
                textPickerColumnPattern->FlushCurrentOptions();
            } else {
                textPickerColumnPattern->ClearOptions();
                textPickerColumnPattern->SetCurrentIndex(0);
                textPickerColumnPattern->FlushCurrentOptions(false, false, true);
            }
        }
    }
}

bool TextPickerPattern::HandleDirectionKey(KeyCode code)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto childSize = host->GetChildren().size();
    auto frameNode = GetColumnNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto textPickerColumnPattern = frameNode->GetPattern<TextPickerColumnPattern>();
    CHECK_NULL_RETURN(textPickerColumnPattern, false);
    auto totalOptionCount = textPickerColumnPattern->GetOptionCount();
    if (totalOptionCount == 0) {
        return false;
    }
    bool result = true;
    switch (code) {
        case KeyCode::KEY_DPAD_UP:
            textPickerColumnPattern->InnerHandleScroll(-1, false);
            break;

        case KeyCode::KEY_DPAD_DOWN:
            textPickerColumnPattern->InnerHandleScroll(1, false);
            break;

        case KeyCode::KEY_ENTER:
            focusKeyID_ = 0;
            PaintFocusState();
            break;

        case KeyCode::KEY_DPAD_LEFT:
            focusKeyID_ -= 1;
            if (focusKeyID_ < 0) {
                focusKeyID_ = 0;
            }
            PaintFocusState();
            break;

        case KeyCode::KEY_DPAD_RIGHT:
            focusKeyID_ += 1;
            if (focusKeyID_ > static_cast<int32_t>(childSize) - 1) {
                focusKeyID_ = static_cast<int32_t>(childSize) - 1;
            }
            PaintFocusState();
            break;

        default:
            result = false;
            break;
    }

    return result;
}

std::string TextPickerPattern::GetSelectedObjectMulti(const std::vector<std::string>& values,
    const std::vector<uint32_t>& indexs, int32_t status) const
{
    std::string result = "";
    result = std::string("{\"value\":") + "[";
    for (uint32_t i = 0; i < values.size(); i++) {
        result += "\"" + values[i];
        if (i != values.size() - 1) {
            result += "\",";
        } else {
            result += "\"]";
        }
    }
    result += std::string(",\"index\":") + "[";
    for (uint32_t i = 0; i < indexs.size(); i++) {
        result += "\"" + std::to_string(indexs[i]);
        if (i != indexs.size() - 1) {
            result += "\",";
        } else {
            result += "\"]";
        }
    }
    result += ",\"status\":" + std::to_string(status) + "}";
    return result;
}

std::string TextPickerPattern::GetSelectedObject(bool isColumnChange, int32_t status) const
{
    std::vector<std::string> values;
    std::vector<uint32_t> indexs;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, "");
    auto children = host->GetChildren();
    for (const auto& child : children) {
        CHECK_NULL_RETURN(child, "");
        auto stackNode = DynamicCast<FrameNode>(child);
        CHECK_NULL_RETURN(stackNode, "");
        auto currentNode = DynamicCast<FrameNode>(stackNode->GetLastChild());
        CHECK_NULL_RETURN(currentNode, "");
        auto textPickerColumnPattern = currentNode->GetPattern<TextPickerColumnPattern>();
        CHECK_NULL_RETURN(textPickerColumnPattern, "");
        auto value = textPickerColumnPattern->GetOption(textPickerColumnPattern->GetSelected());
        auto index = textPickerColumnPattern->GetSelected();
        if (isColumnChange) {
            value = textPickerColumnPattern->GetCurrentText();
            index = textPickerColumnPattern->GetCurrentIndex();
        }
        values.emplace_back(value);
        indexs.emplace_back(index);
    }

    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, "");
    if (context->GetIsDeclarative()) {
        if (values.size() == 1) {
            return std::string("{\"value\":") + "\"" + values[0] + "\"" + ",\"index\":" + std::to_string(indexs[0]) +
               ",\"status\":" + std::to_string(status) + "}";
        } else {
            return GetSelectedObjectMulti(values, indexs, status);
        }
    } else {
        return std::string("{\"newValue\":") + "\"" +
                values[0] + "\"" + ",\"newSelected\":" + std::to_string(indexs[0]) +
               ",\"status\":" + std::to_string(status) + "}";
    }
}

void TextPickerPattern::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    if (!range_.empty()) {
        json->Put("range", GetRangeStr().c_str());
    } else {
        if (!cascadeOriginptions_.empty()) {
            if (!isCascade_) {
                json->Put("range", GetOptionsMultiStr().c_str());
            } else {
                json->Put("range", GetOptionsCascadeStr(cascadeOriginptions_).c_str());
            }
        }
    }
}

std::string TextPickerPattern::GetRangeStr() const
{
    if (!range_.empty()) {
        std::string result = "[";
        for (const auto& item : range_) {
            result += "\"";
            result += "icon:";
            result += item.icon_;
            result += ",";
            result += "text:";
            result += item.text_;
            result += "\"";
            result += ",";
        }
        result.pop_back();
        result += "]";
        return result;
    }
    return "";
}

std::string TextPickerPattern::GetOptionsCascadeStr(
    const std::vector<NG::TextCascadePickerOptions>& options) const
{
    std::string result = "[";
    for (uint32_t i = 0; i < options.size(); i++) {
        result += std::string("{\"text\":\"");
        result += options[i].rangeResult[0];
        result += "\"";
        if (options[i].children.size() > 0) {
            result += std::string(", \"children\":");
            result += GetOptionsCascadeStr(options[i].children);
        }
        if (i != options.size() - 1) {
            result += "},";
        } else {
            result += "}]";
        }
    }
    return result;
}

std::string TextPickerPattern::GetOptionsMultiStrInternal() const
{
    std::string result = "[";
    for (uint32_t i = 0; i < cascadeOptions_.size(); i++) {
        result += "[";
        for (uint32_t j = 0; j < cascadeOptions_[i].rangeResult.size(); j++) {
            result += "\"" + cascadeOptions_[i].rangeResult[j];
            if (j != cascadeOptions_[i].rangeResult.size() - 1) {
                result += "\",";
            } else {
                result += "\"]";
            }
        }
        if (i != cascadeOptions_.size() - 1) {
            result += ",";
        } else {
            result += "]";
        }
    }
    return result;
}

std::string TextPickerPattern::GetOptionsMultiStr() const
{
    std::string result = "";
    if (!cascadeOptions_.empty()) {
        result = GetOptionsMultiStrInternal();
    }
    return result;
}
} // namespace OHOS::Ace::NG
