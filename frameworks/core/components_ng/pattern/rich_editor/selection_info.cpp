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

#include "base/image/pixel_map.h"
#include "core/components_ng/pattern/rich_editor/selection_info.h"

namespace OHOS::Ace {

SymbolSpanStyle::SymbolSpanStyle(const TextStyle& style)
{
    fontSize = style.GetFontSize().ConvertToVp();
    lineHeight = style.GetLineHeight().ConvertToPx();
    letterSpacing = style.GetLetterSpacing().ConvertToPx();
    lineSpacing = style.GetLineSpacing().ConvertToPx();
    for (const auto& color : style.GetSymbolColorList()) {
        symbolColor += color.ColorToString() + ",";
    }
    if (symbolColor.size() > 0) {
        symbolColor = symbolColor.substr(0, symbolColor.size() - 1);
    }
    symbolColor = symbolColor.empty() ? DEFAULT_SYMBOL_COLOR.ColorToString() : symbolColor;
    fontFeature = style.GetFontFeatures();
    fontWeight = static_cast<int32_t>(style.GetFontWeight());
    renderingStrategy = style.GetRenderStrategy();
    effectStrategy = style.GetEffectStrategy();
}

bool SymbolSpanStyle::operator==(const SymbolSpanStyle& rhs) const
{
    return fontSize == rhs.fontSize
        && lineHeight == rhs.lineHeight
        && letterSpacing == rhs.letterSpacing
        && lineSpacing == rhs.lineSpacing
        && symbolColor == rhs.symbolColor
        && fontFeature == rhs.fontFeature
        && fontWeight == rhs.fontWeight
        && renderingStrategy == rhs.renderingStrategy
        && effectStrategy == rhs.effectStrategy;
}

bool SymbolSpanStyle::operator!=(const SymbolSpanStyle& rhs) const
{
    return !operator==(rhs);
}

Selection SelectionInfo::GetSelection() const
{
    return selection_;
}

Selection& SelectionInfo::GetSelectionRef()
{
    return selection_;
}

void SelectionInfo::SetSelectionStart(int32_t start)
{
    selection_.selection[RichEditorSpanRange::RANGESTART] = start;
}

void SelectionInfo::SetSelectionEnd(int32_t end)
{
    selection_.selection[RichEditorSpanRange::RANGEEND] = end;
}

void SelectionInfo::SetResultObjectList(const std::list<ResultObject>& resultObjectList)
{
    for (auto& resultObject : resultObjectList) {
        selection_.resultObjects.emplace_back(resultObject);
    }
}

void SelectionRangeInfo::reset()
{
    start_ = -1;
    end_ = -1;
}

bool SelectionRangeInfo::operator==(const SelectionRangeInfo& rhs) const
{
    return start_ == rhs.start_ && end_ == rhs.end_;
}

} // namespace OHOS::Ace
