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

#include "core/components_ng/pattern/text/span/span_string.h"

#include <cstdint>

#include "base/utils/string_utils.h"
#include "base/utils/utf_helper.h"
#include "core/text/text_emoji_processor.h"
#include "core/common/ace_engine.h"

namespace OHOS::Ace {

const std::unordered_set<SpanType> specailTypes = { SpanType::Image, SpanType::CustomSpan };

std::u16string SpanString::GetWideStringSubstr(const std::u16string& content, int32_t start, int32_t length)
{
    if (start >= static_cast<int32_t>(content.length())) {
        return u"";
    }
    return content.substr(start, length);
}

std::u16string SpanString::GetWideStringSubstr(const std::u16string& content, int32_t start)
{
    if (start >= static_cast<int32_t>(content.length())) {
        return u"";
    }
    return content.substr(start);
}

SpanString::SpanString(const std::u16string& text) : text_(text)
{
    auto spanItem = MakeRefPtr<NG::SpanItem>();
    UtfUtils::HandleInvalidUTF16(reinterpret_cast<uint16_t*>(text_.data()), text_.length(), 0);
    spanItem->content = text_;
    spanItem->interval = { 0, text_.length() };
    spans_.emplace_back(spanItem);
    auto it = spans_.begin();
    SplitSpansAndForward(it);
}

SpanString::SpanString(const ImageSpanOptions& options) : text_(u" ")
{
    auto spanItem = MakeRefPtr<NG::ImageSpanItem>();
    spanItem->options = options;
    spanItem->content = u" ";
    spanItem->interval = { 0, 1 };
    spans_.emplace_back(spanItem);
    spansMap_[SpanType::Image].emplace_back(MakeRefPtr<ImageSpan>(options));
}

SpanString::SpanString(RefPtr<CustomSpan>& span) : text_(u" ")
{
    auto spanItem = MakeRefPtr<NG::CustomSpanItem>();
    spanItem->content = u" ";
    spanItem->interval = { 0, 1 };
    spanItem->onMeasure = span->GetOnMeasure();
    spanItem->onDraw = span->GetOnDraw();
    spans_.emplace_back(spanItem);
    spansMap_[SpanType::CustomSpan].emplace_back(span);
}

void SpanString::AddCustomSpan()
{
    auto spanBases = GetSpans(0, GetLength(), SpanType::CustomSpan);
    for (const auto& spanBase : spanBases) {
        if (spanBase->GetSpanType() != SpanType::CustomSpan) {
            continue;
        }
        auto customSpan = DynamicCast<CustomSpan>(spanBase);
        if (!customSpan) {
            continue;
        }
        customSpan->AddStyledString(Referenced::WeakClaim(this));
    }
}

void SpanString::RemoveCustomSpan()
{
    auto spanBases = GetSpans(0, GetLength(), SpanType::CustomSpan);
    for (const auto& spanBase : spanBases) {
        if (spanBase->GetSpanType() != SpanType::CustomSpan) {
            continue;
        }
        auto customSpan = DynamicCast<CustomSpan>(spanBase);
        if (!customSpan) {
            continue;
        }
        customSpan->RemoveStyledString(Referenced::WeakClaim(this));
    }
}
void SpanString::SetFramNode(const WeakPtr<NG::FrameNode>& frameNode)
{
    framNode_ = frameNode;
}

void SpanString::MarkDirtyFrameNode()
{
    auto frameNode = framNode_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    frameNode->MarkDirtyNode(NG::PROPERTY_UPDATE_RENDER);
}

SpanString::~SpanString()
{
    spansMap_.clear();
    spans_.clear();
}

std::list<RefPtr<NG::SpanItem>>::iterator SpanString::SplitSpansAndForward(
    std::list<RefPtr<NG::SpanItem>>::iterator& it)
{
    auto wString = (*it)->content;
    auto newlineIndex = static_cast<int32_t>(wString.find(u'\n'));
    int32_t offset = (*it)->interval.first;
    while (newlineIndex != -1 && newlineIndex != static_cast<int32_t>(wString.size()) - 1) {
        auto newSpan = (*it)->GetSameStyleSpanItem();
        newSpan->interval = { offset + newlineIndex + 1, (*it)->interval.second };
        (*it)->interval = { offset, offset + newlineIndex + 1 };
        (*it)->UpdateContent(GetWideStringSubstr(wString, 0, newlineIndex + 1));
        wString = GetWideStringSubstr(wString, newlineIndex + 1);
        newSpan->UpdateContent(wString);
        newlineIndex = static_cast<int32_t>(wString.find(u'\n'));

        offset = newSpan->interval.first;
        ++it;
        it = spans_.insert(it, newSpan);
    }

    return std::next(it);
}

void SpanString::ApplyToSpans(
    const RefPtr<SpanBase>& span, std::pair<int32_t, int32_t> interval, SpanOperation operation)
{
    SetGroupId(span);
    for (auto it = spans_.begin(); it != spans_.end(); ++it) {
        auto intersection = (*it)->GetIntersectionInterval(interval);
        if (!intersection) {
            continue;
        }
        auto oldStart = (*it)->interval.first;
        auto oldEnd = (*it)->interval.second;
        if (oldStart == intersection->first && intersection->second == oldEnd) {
            span->ApplyToSpanItem(*it, operation);
            continue;
        }
        auto wContent = (*it)->content;
        auto newSpan = (*it)->GetSameStyleSpanItem();
        auto firstStartIdx = std::clamp(intersection->first - oldStart, 0, static_cast<int32_t>(wContent.length()));
        auto secondStartIdx = std::clamp(intersection->second - oldStart, 0, static_cast<int32_t>(wContent.length()));
        if (oldStart < intersection->first && intersection->second < oldEnd) {
            (*it)->interval = { oldStart, intersection->first };
            (*it)->content = wContent.substr(0, firstStartIdx);

            newSpan->interval = { intersection->first, intersection->second };
            newSpan->content = wContent.substr(firstStartIdx,
                intersection->second - intersection->first);
            span->ApplyToSpanItem(newSpan, operation);

            auto newSpan2 = (*it)->GetSameStyleSpanItem();
            newSpan2->interval = { intersection->second, oldEnd };
            newSpan2->content = wContent.substr(secondStartIdx);
            it = spans_.insert(std::next(it), newSpan);
            it = spans_.insert(std::next(it), newSpan2);
            continue;
        }
        if (oldEnd > intersection->second) {
            (*it)->content = wContent.substr(0, secondStartIdx);
            (*it)->interval = { oldStart, intersection->second };
            span->ApplyToSpanItem(*it, operation);
            newSpan->interval = { intersection->second, oldEnd };
            newSpan->content = wContent.substr(secondStartIdx);
            it = spans_.insert(std::next(it), newSpan);
            continue;
        }
        if (intersection->first > oldStart) {
            (*it)->content = wContent.substr(0, firstStartIdx);
            (*it)->interval = { oldStart, intersection->first };
            newSpan->interval = { intersection->first, oldEnd };
            newSpan->content = wContent.substr(firstStartIdx);
            span->ApplyToSpanItem(newSpan, operation);
            it = spans_.insert(std::next(it), newSpan);
        }
    }
}

void SpanString::SplitInterval(std::list<RefPtr<SpanBase>>& spans, std::pair<int32_t, int32_t> interval)
{
    std::list<RefPtr<SpanBase>> newSpans;
    for (auto it = spans.begin(); it != spans.end();) {
        auto intersection = (*it)->GetIntersectionInterval(interval);
        if (!intersection) {
            ++it;
            continue;
        }
        auto oldStart = (*it)->GetStartIndex();
        auto oldEnd = (*it)->GetEndIndex();
        if (intersection->first == oldStart && intersection->second == oldEnd) {
            it = spans.erase(it);
            continue;
        }
        if (oldStart < intersection->first && intersection->second < oldEnd) {
            newSpans.emplace_back((*it)->GetSubSpan(oldStart, intersection->first));
            newSpans.emplace_back((*it)->GetSubSpan(intersection->second, oldEnd));
            it = spans.erase(it);
            continue;
        }
        if (oldEnd > intersection->second) {
            (*it)->UpdateStartIndex(intersection->second);
            ++it;
            continue;
        }
        if (intersection->first > oldStart) {
            (*it)->UpdateEndIndex(intersection->first);
            ++it;
        }
    }
    spans.merge(newSpans);
}

void SpanString::SortSpans(std::list<RefPtr<SpanBase>>& spans)
{
    spans.sort(
        [](const RefPtr<SpanBase>& a, const RefPtr<SpanBase>& b) { return a->GetStartIndex() < b->GetStartIndex(); });
}

bool SpanString::CanMerge(const RefPtr<SpanBase>& a, const RefPtr<SpanBase>& b)
{
    return a->GetEndIndex() >= b->GetStartIndex() && a->IsAttributesEqual(b);
}

void SpanString::MergeIntervals(std::list<RefPtr<SpanBase>>& spans)
{
    auto it = spans.begin();
    while (it != spans.end()) {
        auto spanType = (*it)->GetSpanType();
        if (spanType == SpanType::Image || spanType == SpanType::CustomSpan) {
            return;
        }
        auto current = it++;
        if (it != spans.end() && CanMerge(*current, *it)) {
            (*current)->UpdateStartIndex(std::min((*current)->GetStartIndex(), (*it)->GetStartIndex()));
            (*current)->UpdateEndIndex(std::max((*current)->GetEndIndex(), (*it)->GetEndIndex()));
            spans.erase(it++);
            if (it == spans.end()) {
                break;
            }
            it = current;
        }
    }
}

int32_t SpanString::GetStepsByPosition(int32_t pos)
{
    if (pos == 0) {
        return 0;
    }
    int32_t step = 0;
    for (auto iter = spans_.begin(); iter != spans_.end(); ++iter) {
        if ((*iter)->interval.first == pos) {
            return step;
        }
        if ((*iter)->interval.first < pos && pos < (*iter)->interval.second) {
            auto spanItem = (*iter)->GetSameStyleSpanItem();
            spanItem->interval.first = pos;
            spanItem->interval.second = (*iter)->interval.second;
            auto wStr = spanItem->content;
            auto start = (*iter)->interval.first;
            spanItem->content = wStr.substr(std::clamp(pos - start, 0, static_cast<int32_t>(wStr.length())));
            spans_.insert(std::next(iter), spanItem);
            (*iter)->interval.second = pos;
            (*iter)->content = wStr.substr(0, pos - start);
            return step;
        }
        step++;
    }
    return step;
}

void SpanString::AddSpecialSpan(const RefPtr<SpanBase>& span, SpanType type, int32_t start)
{
    start = std::clamp(start, 0, static_cast<int32_t>(GetU16string().length()));
    text_ = GetU16string().substr(0, start) + u" " + GetU16string().substr(start);
    auto iter = spans_.begin();
    auto step = GetStepsByPosition(start);
    std::advance(iter, step);
    RefPtr<NG::SpanItem> spanItem;
    if (type == SpanType::Image) {
        auto imageSpan = DynamicCast<ImageSpan>(span);
        CHECK_NULL_VOID(imageSpan);
        spanItem = MakeImageSpanItem(imageSpan);
    } else if (type == SpanType::CustomSpan) {
        auto customSpan = AceType::DynamicCast<CustomSpan>(span);
        CHECK_NULL_VOID(customSpan);
        spanItem = MakeCustomSpanItem(customSpan);
    }
    iter = spans_.insert(iter, spanItem);
    for (++iter; iter != spans_.end(); ++iter) {
        ++(*iter)->interval.first;
        ++(*iter)->interval.second;
    }

    UpdateSpanMapWithOffset(start - 1, 1);
    if (spansMap_.find(type) == spansMap_.end()) {
        spansMap_[type].emplace_back(span);
    } else {
        auto specialList = spansMap_[type];
        int32_t step = 0;
        for (const auto& specialSpan : specialList) {
            if (specialSpan->GetStartIndex() >= start) {
                break;
            }
            ++step;
        }
        auto iter = specialList.begin();
        std::advance(iter, step);
        specialList.insert(iter, span);
        spansMap_[type] = specialList;
    }
}

RefPtr<NG::ImageSpanItem> SpanString::MakeImageSpanItem(const RefPtr<ImageSpan>& imageSpan)
{
    auto spanItem = MakeRefPtr<NG::ImageSpanItem>();
    spanItem->content = u" ";
    spanItem->interval.first = imageSpan->GetStartIndex();
    spanItem->interval.second = imageSpan->GetEndIndex();
    spanItem->SetImageSpanOptions(imageSpan->GetImageSpanOptions());
    return spanItem;
}

RefPtr<NG::CustomSpanItem> SpanString::MakeCustomSpanItem(const RefPtr<CustomSpan>& customSpan)
{
    auto spanItem = MakeRefPtr<NG::CustomSpanItem>();
    spanItem->content = u" ";
    spanItem->interval.first = customSpan->GetStartIndex();
    spanItem->interval.second = customSpan->GetEndIndex();
    spanItem->onDraw = customSpan->GetOnDraw();
    spanItem->onMeasure = customSpan->GetOnMeasure();
    return spanItem;
}

bool SpanString::CheckMultiTypeDecorationSpan(const RefPtr<SpanBase>& span)
{
    if (span->GetSpanType() != SpanType::Decoration) {
        return false;
    }
    auto decorationSpan = AceType::DynamicCast<DecorationSpan>(span);
    if (!decorationSpan->GetTextDecorationOptions().has_value()) {
        return false;
    }
    auto options = decorationSpan->GetTextDecorationOptions().value();
    return options.enableMultiType.value_or(false);
}

std::vector<RefPtr<SpanBase>> SpanString::GetWholeSpans(int32_t start, int32_t end, SpanType spanType) const
{
    std::vector<RefPtr<SpanBase>> res;
    if (!CheckRange(start, end - start)) {
        return res;
    }

    auto spans = spansMap_.find(spanType)->second;
    for (const auto& span : spans) {
        int32_t tempStart = span->GetStartIndex();
        int32_t tempEnd = span->GetEndIndex();
        if ((tempStart <= start && tempEnd > start) ||
            (tempStart <= end && tempEnd > end) ||
            (tempStart >= start && tempEnd <= end)) {
            res.push_back(span);
        }
    }
    return res;
}

void SpanString::ProcessMultiDecorationSpanForIntersection(
    const RefPtr<SpanBase>& span, const RefPtr<SpanBase>& lastSpan,
    std::vector<int32_t>& spanNoIntersection, int32_t start, int32_t end)
{
    auto lastDecorationSpan = AceType::DynamicCast<DecorationSpan>(lastSpan);
    auto lastDecorations = lastDecorationSpan->GetTextDecorationTypes();

    int32_t lastSpanStart = lastSpan->GetStartIndex();
    int32_t lastSpanEnd = lastSpan->GetEndIndex();
    int32_t intersectionStart = std::max(start, lastSpanStart);
    int32_t intersectionEnd = std::min(end, lastSpanEnd);

    bool spanInRight = lastSpanStart <= start && lastSpanEnd <= end;
    bool isInclude = lastSpanStart <= start && lastSpanEnd >= end;

    int32_t newStart = 0;
    int32_t newEnd = 0;
    if (isInclude) {
        newStart = intersectionStart;
        newEnd = intersectionEnd;
    } else if (spanInRight) {
        newStart = intersectionStart;
        newEnd = lastSpanEnd;
    } else {
        newStart = lastSpanStart;
        newEnd = intersectionEnd;
    }
    auto intersectionSpan = span->GetSubSpan(newStart, newEnd);
    auto intersectionDecorationSpan = AceType::DynamicCast<DecorationSpan>(intersectionSpan);
    // apply new data to newSpan
    if (CheckMultiTypeDecorationSpan(lastSpan) && CheckMultiTypeDecorationSpan(intersectionSpan)) {
        for (TextDecoration value : lastDecorations) {
            intersectionDecorationSpan->AddTextDecorationType(value);
        }
    } else {
        TextDecorationOptions option { false };
        intersectionDecorationSpan->SetTextDecorationOptions(option);
    }
    AddSpan(intersectionSpan, false);
    for (int32_t index = newStart; index < newEnd; index++) {
        spanNoIntersection[index] = 0; //unmark
    }
}

void SpanString::ProcessMultiDecorationSpanForNoIntersection(
    const RefPtr<SpanBase>& span, std::vector<int32_t>& spanNoIntersection,
    int32_t start, int32_t end)
{
    int32_t tempStart = start;
    int32_t tempEnd = start;
    for (int32_t index = start; index < end;) {
        index++;
        if (spanNoIntersection[tempStart] != 0) {
            while (tempEnd < end && spanNoIntersection[tempEnd] != 0) {
                tempEnd++;
            }
            if (tempEnd == tempStart) {
                continue;
            }
            auto tempSpan = span->GetSubSpan(tempStart, tempEnd);
            AddSpan(tempSpan, false);
        } else {
            tempStart = index;
            tempEnd = index;
        }
    }
}

bool SpanString::ProcessMultiDecorationSpan(const RefPtr<SpanBase>& span, int32_t start, int32_t end)
{
    bool multiTypeDecoration = CheckMultiTypeDecorationSpan(span);
    if (!multiTypeDecoration) {
        return false;
    }
    auto lastSpans = GetWholeSpans(start, end, SpanType::Decoration);
    if (lastSpans.size() <= 0) {
        return false;
    }
    std::vector<int32_t> spanNoIntersection;
    for (int32_t index = 0; index <= end; index++) {
        if (index >= start) {
            spanNoIntersection.push_back(1); // mark
        } else {
            spanNoIntersection.push_back(0);
        }
    }
    for (const RefPtr<SpanBase>& lastSpan : lastSpans) {
        ProcessMultiDecorationSpanForIntersection(span, lastSpan, spanNoIntersection, start, end);
    }
    ProcessMultiDecorationSpanForNoIntersection(span, spanNoIntersection, start, end);
    return true;
}

void SpanString::AddSpan(const RefPtr<SpanBase>& span, bool processMultiDecoration,
    bool isFromHtml, bool removeOriginStyle)
{
    if (!span || !CheckRange(span)) {
        return;
    }
    auto start = span->GetStartIndex();
    auto end = span->GetEndIndex();
    if (span->GetSpanType() == SpanType::Image || span->GetSpanType() == SpanType::CustomSpan) {
        AddSpecialSpan(span, span->GetSpanType(), start);
        return;
    }
    if (spansMap_.find(span->GetSpanType()) == spansMap_.end()) {
        spansMap_[span->GetSpanType()].emplace_back(span);
        ApplyToSpans(span, { start, end }, SpanOperation::ADD);
        return;
    }
    // If the span type is Font and the span is from HTML, directly add it to the spansMap_ and apply it.
    else if (span->GetSpanType() == SpanType::Font && isFromHtml) {
        spansMap_[span->GetSpanType()].emplace_back(span);
        ApplyToSpans(span, { start, end }, SpanOperation::ADD);
        return;
    }
    if (processMultiDecoration && ProcessMultiDecorationSpan(span, start, end)) {
        return;
    }
    if (removeOriginStyle) {
        RemoveSpan(start, end - start, span->GetSpanType());
    }
    auto spans = spansMap_[span->GetSpanType()];
    ApplyToSpans(span, { start, end }, SpanOperation::ADD);
    SplitInterval(spans, { start, end });
    spans.emplace_back(span);
    SortSpans(spans);
    MergeIntervals(spans);
    spansMap_[span->GetSpanType()] = spans;
}

void SpanString::RemoveSpan(int32_t start, int32_t length, SpanType key)
{
    if (!CheckRange(start, length)) {
        return;
    }
    auto end = start + length;
    length = end - start;
    auto it = spansMap_.find(key);
    if (it == spansMap_.end()) {
        return;
    }
    auto spans = spansMap_[key];
    if (key == SpanType::Image) {
        RemoveSpecialSpan(start, end, key);
        return;
    }
    if (key == SpanType::CustomSpan) {
        RemoveSpecialSpan(start, end, key);
        return;
    }
    auto defaultSpan = GetDefaultSpan(key);
    CHECK_NULL_VOID(defaultSpan);
    defaultSpan->UpdateStartIndex(start);
    defaultSpan->UpdateEndIndex(end);
    ApplyToSpans(defaultSpan, { start, end }, SpanOperation::REMOVE);
    SplitInterval(spans, { start, end });
    SortSpans(spans);
    MergeIntervals(spans);
    if (spans.empty()) {
        spansMap_.erase(key);
    } else {
        spansMap_[key] = spans;
    }
}

RefPtr<SpanBase> SpanString::GetDefaultSpan(SpanType type)
{
    switch (type) {
        case SpanType::Font:
            return MakeRefPtr<FontSpan>();
        case SpanType::TextShadow:
            return MakeRefPtr<TextShadowSpan>();
        case SpanType::Gesture:
            return MakeRefPtr<GestureSpan>();
        case SpanType::Decoration:
            return MakeRefPtr<DecorationSpan>();
        case SpanType::BaselineOffset:
            return MakeRefPtr<BaselineOffsetSpan>();
        case SpanType::LetterSpacing:
            return MakeRefPtr<LetterSpacingSpan>();
        case SpanType::ParagraphStyle:
            return MakeRefPtr<ParagraphStyleSpan>();
        case SpanType::LineHeight:
            return MakeRefPtr<LineHeightSpan>();
        case SpanType::ExtSpan:
            return MakeRefPtr<ExtSpan>();
        case SpanType::BackgroundColor:
            return MakeRefPtr<BackgroundColorSpan>();
        case SpanType::Url:
            return MakeRefPtr<UrlSpan>();
        default:
            return nullptr;
    }
}

bool SpanString::CheckRange(const RefPtr<SpanBase>& spanBase) const
{
    auto start = spanBase->GetStartIndex();
    auto length = spanBase->GetLength();
    if (length <= 0) {
        return false;
    }
    auto spanType = spanBase->GetSpanType();
    auto len = spanType == SpanType::Image || spanType == SpanType::CustomSpan ? GetLength() + 1 : GetLength();
    auto end = start + length;

    if (start > len || end > len) {
        return false;
    }

    if (start < 0) {
        return false;
    }

    return true;
}

bool SpanString::CheckRange(int32_t start, int32_t length, bool allowLengthZero) const
{
    if (length < 0 || (length == 0 && !allowLengthZero)) {
        return false;
    }

    auto len = GetLength();
    auto end = start + length;

    if (start > len || end > len) {
        return false;
    }

    if (start < 0) {
        return false;
    }

    return true;
}

RefPtr<NG::SpanItem> SpanString::GetDefaultSpanItem(const std::u16string& text)
{
    auto spanItem = MakeRefPtr<NG::SpanItem>();
    spanItem->content = text;
    spanItem->interval = { 0, text.length() };
    return spanItem;
}

void SpanString::SetString(const std::u16string& text)
{
    text_ = text;
}

void SpanString::SetGroupId(const RefPtr<SpanBase>& span)
{
    if (span->GetSpanType() == SpanType::BackgroundColor) {
        auto backgroundColorSpan = DynamicCast<BackgroundColorSpan>(span);
        CHECK_NULL_VOID(backgroundColorSpan);
        backgroundColorSpan->SetBackgroundColorGroupId(groupId_++);
    }
}
void SpanString::SetSpanItems(const std::list<RefPtr<NG::SpanItem>>&& spanItems)
{
    spans_ = spanItems;
}

void SpanString::SetSpanMap(std::unordered_map<SpanType, std::list<RefPtr<SpanBase>>>&& spansMap)
{
    spansMap_ = spansMap;
}

const std::string SpanString::GetString() const
{
    return UtfUtils::Str16DebugToStr8(text_);
}

const std::u16string& SpanString::GetU16string() const
{
    return text_;
}

int32_t SpanString::GetLength() const
{
    return text_.length();
}

bool SpanString::IsEqualToSpanString(const RefPtr<SpanString>& other) const
{
    return *this == *other;
}

RefPtr<SpanString> SpanString::GetSubSpanString(int32_t start, int32_t length, bool includeStartHalf,
    bool includeEndHalf, bool rangeNeedNotChange) const
{
    if (!CheckRange(start, length)) {
        RefPtr<SpanString> span = AceType::MakeRefPtr<SpanString>(u"");
        return span;
    }
    int32_t end = start + length;
    if (!rangeNeedNotChange) {
        TextEmojiSubStringRange range = TextEmojiProcessor::CalSubU16stringRange(
            start, end - start, text_, includeStartHalf, includeEndHalf);
        start = range.startIndex;
        end = range.endIndex;
        length = end - start;
    }
    start = std::clamp(start, 0, static_cast<int32_t>(text_.length()));
    RefPtr<SpanString> span =
        AceType::MakeRefPtr<SpanString>(text_.substr(start, length));
    std::unordered_map<SpanType, std::list<RefPtr<SpanBase>>> subMap;
    for (const auto& map : spansMap_) {
        auto subList = GetSubSpanList(start, length, map.second);
        if (!subList.empty()) {
            subMap.insert({ map.first, subList });
        }
    }
    span->spansMap_ = subMap;

    std::list<RefPtr<NG::SpanItem>> subSpans_;
    for (const auto& spanItem : spans_) {
        auto intersection = spanItem->GetIntersectionInterval({start, start+length});
        if (intersection) {
            int32_t oldStart = spanItem->interval.first;
            int32_t oldEnd = spanItem->interval.second;
            auto spanStart = oldStart <= start ? 0 : oldStart - start;
            auto spanEnd = oldEnd < end ? oldEnd - start : end - start;
            auto newSpanItem = spanItem->GetSameStyleSpanItem();
            newSpanItem->interval = { spanStart, spanEnd };
            newSpanItem->content = spanItem->content
                    .substr(std::max(start - oldStart, 0), std::min(end, oldEnd) - std::max(start, oldStart));
            subSpans_.emplace_back(newSpanItem);
        }
    }
    span->spans_ = subSpans_;
    return span;
}

std::list<RefPtr<SpanBase>> SpanString::GetSubSpanList(
    int32_t start, int32_t length, const std::list<RefPtr<SpanBase>>& spans) const
{
    std::list<RefPtr<SpanBase>> res;
    int32_t end = start + length;
    for (auto& span : spans) {
        auto intersection = span->GetIntersectionInterval({ start, end });
        if (intersection) {
            int32_t spanStart = span->GetStartIndex();
            int32_t spanEnd = span->GetEndIndex();
            spanStart = spanStart <= start ? 0 : spanStart - start;
            spanEnd = spanEnd < end ? spanEnd - start : end - start;
            if (spanStart == spanEnd) {
                continue;
            }
            res.emplace_back(span->GetSubSpan(spanStart, spanEnd));
        }
    }
    return res;
}

const std::unordered_map<SpanType, std::list<RefPtr<SpanBase>>>& SpanString::GetSpansMap() const
{
    return spansMap_;
}

std::vector<RefPtr<SpanBase>> SpanString::GetSpans(int32_t start, int32_t length) const
{
    std::vector<RefPtr<SpanBase>> res;
    if (!CheckRange(start, length)) {
        return res;
    }

    for (const auto& map : spansMap_) {
        auto spans = GetSpans(start, length, map.first);
        res.insert(res.begin(), spans.begin(), spans.end());
    }
    return res;
}

std::vector<RefPtr<SpanBase>> SpanString::GetSpans(int32_t start, int32_t length, SpanType spanType) const
{
    std::vector<RefPtr<SpanBase>> res;
    if (!CheckRange(start, length)) {
        return res;
    }
    int32_t end = start + length;
    RefPtr<SpanBase> span;
    while ((span = GetSpan(start, length, spanType)) != nullptr) {
        res.emplace_back(span);
        start = span->GetEndIndex();
        length = end - start;
    }
    return res;
}

RefPtr<SpanBase> SpanString::GetSpan(int32_t start, int32_t length, SpanType spanType) const
{
    if (!CheckRange(start, length) || spansMap_.find(spanType) == spansMap_.end()) {
        return nullptr;
    }
    int32_t end = start + length;
    auto spanBaseList = spansMap_.find(spanType)->second;
    for (auto& spanBase : spanBaseList) {
        auto intersection = spanBase->GetIntersectionInterval({ start, end });
        if (intersection) {
            int32_t newStart = intersection->first;
            int32_t newEnd = intersection->second;
            if (newStart == newEnd) {
                continue;
            }
            return spanBase->GetSubSpan(newStart, newEnd);
        }
    }
    return nullptr;
}

bool SpanString::operator==(const SpanString& other) const
{
    if (text_ != other.text_) {
        return false;
    }
    auto size =
        !spansMap_.empty()
            ? (static_cast<int32_t>(spansMap_.size()) - (spansMap_.find(SpanType::Gesture) == spansMap_.end() ? 0 : 1))
            : 0;
    auto sizeOther = !other.spansMap_.empty()
                         ? (static_cast<int32_t>(other.spansMap_.size()) -
                               (other.spansMap_.find(SpanType::Gesture) == other.spansMap_.end() ? 0 : 1))
                         : 0;
    if (size != sizeOther) {
        return false;
    }

    for (const auto& map : spansMap_) {
        if (map.first == SpanType::Gesture) {
            continue;
        }
        auto spansOtherMap = other.spansMap_.find(map.first);
        if (spansOtherMap == other.spansMap_.end()) {
            return false;
        }
        auto spans = map.second;
        auto spansOther = spansOtherMap->second;
        if (spans.size() != spansOther.size()) {
            return false;
        }
        for (auto spansItr = spans.begin(), spansOtherItr = spansOther.begin();
             spansItr != spans.end() && spansOtherItr != spansOther.end(); ++spansItr, ++spansOtherItr) {
            if (!(*spansItr)->IsAttributesEqual(*spansOtherItr) ||
                (*spansItr)->GetEndIndex() != (*spansOtherItr)->GetEndIndex() ||
                (*spansItr)->GetStartIndex() != (*spansOtherItr)->GetStartIndex()) {
                return false;
            }
        }
    }
    return true;
}

std::list<RefPtr<NG::SpanItem>> SpanString::GetSpanItems() const
{
    return spans_;
}

void SpanString::BindWithSpans(const std::vector<RefPtr<SpanBase>>& spans)
{
    for (auto& span : spans) {
        AddSpan(span);
    }
}

void SpanString::UpdateSpansWithOffset(int32_t start, int32_t offset)
{
    for (auto& span : spans_) {
        if (span->interval.second > start && span->interval.first != start) {
            span->interval.second += offset;
        }
        if (span->interval.first > start) {
            span->interval.first += offset;
        }
    }
}

void SpanString::UpdateSpanMapWithOffset(int32_t start, int32_t offset)
{
    for (auto& iter : spansMap_) {
        if (spansMap_.find(iter.first) == spansMap_.end()) {
            continue;
        }
        auto spans = spansMap_[iter.first];
        for (auto& it : spans) {
            UpdateSpanBaseWithOffset(it, start, offset);
        }
        spansMap_[iter.first] = spans;
    }
}

void SpanString::UpdateSpanBaseWithOffset(RefPtr<SpanBase>& span, int32_t start, int32_t offset)
{
    if (span->GetEndIndex() > start && span->GetStartIndex() != start) {
        span->UpdateEndIndex(span->GetEndIndex() + offset);
    }
    if (span->GetStartIndex() > start) {
        span->UpdateStartIndex(span->GetStartIndex() + offset);
    }
}

void SpanString::RemoveSpecialSpan(int32_t start, int32_t end, SpanType type)
{
    auto spans = spansMap_[type];
    int32_t count = 0;
    for (auto iter = spans.begin(); iter != spans.end();) {
        if ((*iter)->GetStartIndex() >= start && (*iter)->GetStartIndex() < end - count) {
            text_.erase((*iter)->GetStartIndex(), 1);
            UpdateSpanMapWithOffset((*iter)->GetStartIndex(), -1);
            iter = spans.erase(iter);
            ++count;
            continue;
        }
        ++iter;
    }
    if (spans.empty()) {
        spansMap_.erase(type);
    } else {
        spansMap_[type] = spans;
    }
    count = 0;
    for (auto iter = spans_.begin(); iter != spans_.end();) {
        if ((*iter)->interval.first >= start && (*iter)->interval.first < end - count
            && ((type == SpanType::Image && (*iter)->spanItemType == SpanItemType::IMAGE)
                || (type == SpanType::CustomSpan && (*iter)->spanItemType == SpanItemType::CustomSpan))) {
            UpdateSpansWithOffset((*iter)->interval.first, -1);
            iter = spans_.erase(iter);
            ++count;
            continue;
        }
        ++iter;
    }
}

void SpanString::GetSpecialTypesVector(std::list<int32_t>& indexList, int32_t start, int32_t length)
{
    int32_t end = start + length;
    auto iter = indexList.begin();
    for (const auto& type : specailTypes) {
        auto spans = spansMap_[type];
        for (const auto& span : spans) {
            auto intersection = span->GetIntersectionInterval({ start, end });
            if (!intersection) {
                continue;
            }
            iter = indexList.insert(iter, span->GetStartIndex());
        }
    }
    indexList.sort([](const int32_t& a, const int32_t& b) { return a < b; });
}

void SpanString::GetNormalTypesVector(std::list<std::pair<int32_t, int32_t>>& indexList, int32_t start, int32_t length)
{
    std::list<int32_t> specialList;
    GetSpecialTypesVector(specialList, start, length);
    auto next = start;
    auto iter = indexList.begin();
    for (const auto& index : specialList) {
        if (index > next) {
            iter = indexList.insert(iter, { next, index - next });
        }
        next = index + 1;
    }
    if (next < start + length) {
        indexList.insert(iter, { next, start + length - next });
    }
}

bool SpanString::ContainSpecialNode(int32_t start, int32_t length)
{
    int32_t end = start + length;
    for (const auto& type : specailTypes) {
        auto spans = spansMap_[type];
        for (const auto& span : spans) {
            auto intersection = span->GetIntersectionInterval({ start, end });
            if (intersection) {
                return true;
            }
            if (span->GetStartIndex() >= end) {
                break;
            }
        }
    }
    return false;
}

bool SpanString::IsSpecialNode(RefPtr<SpanBase> span)
{
    auto type = span->GetSpanType();
    if (specailTypes.find(type) == specailTypes.end()) {
        return false;
    }
    return true;
}

void SpanString::ClearSpans()
{
    spans_.clear();
}

void SpanString::AppendSpanItem(const RefPtr<NG::SpanItem>& spanItem)
{
    spans_.emplace_back(spanItem);
}

bool SpanString::EncodeTlv(std::vector<uint8_t>& buff)
{
    TLVUtil::WriteUint8(buff, TLV_SPAN_STRING_SPANS);
    TLVUtil::WriteInt32(buff, spans_.size());
    for (auto it = spans_.begin(); it != spans_.end(); ++it) {
        auto spanItem = (*it);
        if (spanItem->spanItemType == SpanItemType::CustomSpan) {
            TLVUtil::WriteInt32(buff, static_cast<int32_t>(SpanItemType::NORMAL));
            auto placeHolderSpan = AceType::MakeRefPtr<NG::SpanItem>();
            placeHolderSpan->content = u" ";
            placeHolderSpan->interval = spanItem->interval;
            placeHolderSpan->EncodeTlv(buff);
            continue;
        }
        TLVUtil::WriteInt32(buff, static_cast<int32_t>(spanItem->spanItemType));
        spanItem->EncodeTlv(buff);
    }
    TLVUtil::WriteUint8(buff, TLV_SPAN_STRING_CONTENT);
    TLVUtil::WriteString(buff, UtfUtils::Str16DebugToStr8(text_));
    TLVUtil::WriteUint8(buff, TLV_END);
    std::vector<uint8_t> otherInfo;
    TLVUtil::WriteInt32(otherInfo, isFromStyledStringMode ? 1 : 0);
    TLVUtil::WriteUint8(buff, TLV_SPAN_STRING_MODE_FLAG);
    TLVUtil::WriteInt32(buff, static_cast<int32_t>(otherInfo.size()));
    buff.insert(buff.end(), otherInfo.begin(), otherInfo.end());
    return true;
}

RefPtr<SpanString> SpanString::DecodeTlv(std::vector<uint8_t>& buff)
{
    RefPtr<SpanString> spanStr = MakeRefPtr<SpanString>(u"");
    SpanString* spanString = Referenced::RawPtr(spanStr);
    std::function<RefPtr<ExtSpan>(const std::vector<uint8_t>&, int32_t, int32_t)> unmarshallCallback;
    DecodeTlvExt(buff, spanString, std::move(unmarshallCallback));
    return spanStr;
}

RefPtr<SpanString> SpanString::DecodeTlv(std::vector<uint8_t>& buff,
    const std::function<RefPtr<ExtSpan>(const std::vector<uint8_t>&, int32_t, int32_t)>&& unmarshallCallback,
    int32_t instanceId)
{
    RefPtr<SpanString> spanStr = MakeRefPtr<SpanString>(u"");
    SpanString* spanString = Referenced::RawPtr(spanStr);
    DecodeTlvExt(buff, spanString, std::move(unmarshallCallback), instanceId);
    return spanStr;
}

void SpanString::DecodeTlvExt(std::vector<uint8_t>& buff, SpanString* spanString,
    const std::function<RefPtr<ExtSpan>(const std::vector<uint8_t>&, int32_t, int32_t)>&& unmarshallCallback,
    int32_t instanceId)
{
    CHECK_NULL_VOID(spanString);
    int32_t cursor = 0;
    DecodeTlvOldExt(buff, spanString, cursor);
    
    for (uint8_t tag = TLVUtil::ReadUint8(buff, cursor); tag != TLV_END; tag = TLVUtil::ReadUint8(buff, cursor)) {
        auto buffLength = TLVUtil::ReadInt32(buff, cursor);
        if (buffLength == 0) {
            continue;
        }
        auto lastCursor = cursor;
        switch (tag) {
            case TLV_CUSTOM_MARSHALL_BUFFER_START: {
                CHECK_NULL_BREAK(unmarshallCallback);
                auto start = TLVUtil::ReadInt32(buff, cursor);
                auto length = TLVUtil::ReadInt32(buff, cursor);
                auto endOfUserDataArrBuff = buffLength + cursor + cursor - lastCursor;
                std::vector<uint8_t> bufferSubVec(buff.begin() + cursor, buff.begin() + endOfUserDataArrBuff);
                ContainerScope scope(instanceId);
                auto container = AceEngine::Get().GetContainer(instanceId);
                CHECK_NULL_VOID(container);
                auto taskExecutor = container->GetTaskExecutor();
                CHECK_NULL_VOID(taskExecutor);
                taskExecutor->PostSyncTask([spanString, start, length, bufferSubVec, unmarshallCallback]() mutable {
                        auto extSpan = unmarshallCallback(bufferSubVec, start, length);
                        spanString->AddSpan(extSpan);
                    }, TaskExecutor::TaskType::UI, "SpanstringDecodeTlvExt", PriorityType::IMMEDIATE);
                cursor = lastCursor + buffLength;
                break;
            }
            case TLV_SPAN_STRING_MODE_FLAG: {
                auto isFromStyledStringMode = TLVUtil::ReadInt32(buff, cursor);
                spanString->isFromStyledStringMode = isFromStyledStringMode == 1;
            }
            default:
                break;
        }
        cursor = lastCursor + buffLength;
    }
}

void SpanString::DecodeTlvOldExt(std::vector<uint8_t>& buff, SpanString* spanString, int32_t& cursor)
{
    CHECK_NULL_VOID(spanString);
    spanString->ClearSpans();
    for (uint8_t tag = TLVUtil::ReadUint8(buff, cursor); tag != TLV_END; tag = TLVUtil::ReadUint8(buff, cursor)) {
        switch (tag) {
            case TLV_SPAN_STRING_CONTENT: {
                auto str = UtfUtils::Str8DebugToStr16(TLVUtil::ReadString(buff, cursor));
                spanString->SetString(str);
                break;
            }
            case TLV_SPAN_STRING_SPANS: {
                DecodeSpanItemListExt(buff, cursor, spanString);
                break;
            }
            default:
                break;
        }
    }
}

void SpanString::DecodeSpanItemListExt(std::vector<uint8_t>& buff, int32_t& cursor, SpanString* spanStr)
{
    CHECK_NULL_VOID(spanStr);
    int32_t spanLength = TLVUtil::ReadInt32(buff, cursor);
    for (auto i = 0; i < spanLength; i++) {
        auto spanItemType = TLVUtil::ReadInt32(buff, cursor);
        if (spanItemType == static_cast<int32_t>(SpanItemType::IMAGE)) {
            auto imageSpanItem = NG::ImageSpanItem::DecodeTlv(buff, cursor);
            spanStr->AppendSpanItem(imageSpanItem);
        } else {
            auto spanItem = NG::SpanItem::DecodeTlv(buff, cursor);
            spanStr->AppendSpanItem(spanItem);
        }
    }
    spanStr->UpdateSpansMap();
}

void SpanString::DecodeSpanItemList(std::vector<uint8_t>& buff, int32_t& cursor, RefPtr<SpanString>& spanStr)
{
    CHECK_NULL_VOID(spanStr);
    DecodeSpanItemListExt(buff, cursor, Referenced::RawPtr(spanStr));
}

void SpanString::UpdateSpansMap()
{
    spansMap_.clear();
    for (auto& spanItem : spans_) {
        if (!spanItem) {
            continue;
        }
        auto start = spanItem->interval.first;
        auto end = spanItem->interval.second;
        std::list<RefPtr<SpanBase>> spanBases;
        if (spanItem->spanItemType == SpanItemType::IMAGE) {
            spanBases = { ToImageSpan(spanItem, start, end) };
        } else if (spanItem->spanItemType == SpanItemType::NORMAL)
            spanBases = { ToFontSpan(spanItem, start, end),
                ToDecorationSpan(spanItem, start, end),
                ToBaselineOffsetSpan(spanItem, start, end),
                ToLetterSpacingSpan(spanItem, start, end),
                ToGestureSpan(spanItem, start, end),
                ToParagraphStyleSpan(spanItem, start, end),
                ToLineHeightSpan(spanItem, start, end),
                ToBackgroundColorSpan(spanItem, start, end),
                ToUrlSpan(spanItem, start, end) };
        for (auto& spanBase : spanBases) {
            if (!spanBase) {
                continue;
            }
            auto it = spansMap_.find(spanBase->GetSpanType());
            if (it == spansMap_.end()) {
                spansMap_.insert({ spanBase->GetSpanType(), { spanBase } });
            } else {
                it->second.emplace_back(std::move(spanBase));
            }
        }
    }
}

std::string SpanString::ToString()
{
    std::stringstream ss;
    for (auto span: spans_) {
        ss << "Get spanItem [" << span->interval.first << ":"
            << span->interval.second << "] " << UtfUtils::Str16DebugToStr8(span->content) << std::endl;
    }
    for (auto& iter : spansMap_) {
        auto spans = spansMap_[iter.first];
        for (auto it = spans.begin(); it != spans.end(); ++it) {
            ss << (*it)->ToString() << std::endl;
        }
    }
    std::string output = ss.str();
    return output;
}

RefPtr<FontSpan> SpanString::ToFontSpan(const RefPtr<NG::SpanItem>& spanItem, int32_t start, int32_t end)
{
    CHECK_NULL_RETURN(spanItem && spanItem->fontStyle, nullptr);
    Font font;
    font.fontColor = spanItem->fontStyle->GetTextColor();
    font.fontFamiliesNG = spanItem->fontStyle->GetFontFamily();
    font.fontSize = spanItem->fontStyle->GetFontSize();
    font.fontStyle = spanItem->fontStyle->GetItalicFontStyle();
    font.fontWeight = spanItem->fontStyle->GetFontWeight();
    font.strokeWidth = spanItem->fontStyle->GetStrokeWidth();
    font.strokeColor = spanItem->fontStyle->GetStrokeColor();
    font.superscript = spanItem->fontStyle->GetSuperscript();
    return AceType::MakeRefPtr<FontSpan>(font, start, end);
}

RefPtr<DecorationSpan> SpanString::ToDecorationSpan(
    const RefPtr<NG::SpanItem>& spanItem, int32_t start, int32_t end)
{
    CHECK_NULL_RETURN(spanItem && spanItem->fontStyle, nullptr);
    std::vector<TextDecoration> types = spanItem->fontStyle->GetTextDecoration().value_or(
        std::vector<TextDecoration>({TextDecoration::NONE}));
    std::optional<Color> color = spanItem->fontStyle->GetTextDecorationColor();
    std::optional<TextDecorationStyle> style = spanItem->fontStyle->GetTextDecorationStyle();
    std::optional<float> lineThicknessScale = spanItem->fontStyle->GetLineThicknessScale();
    std::optional<TextDecorationOptions> options;
    return AceType::MakeRefPtr<DecorationSpan>(
        types, color, style, lineThicknessScale, options, start, end);
}

RefPtr<BaselineOffsetSpan> SpanString::ToBaselineOffsetSpan(
    const RefPtr<NG::SpanItem>& spanItem, int32_t start, int32_t end)
{
    CHECK_NULL_RETURN(spanItem && spanItem->textLineStyle, nullptr);
    Dimension baselineOffset;
    if (spanItem->textLineStyle->GetBaselineOffset().has_value()) {
        baselineOffset.SetValue(spanItem->textLineStyle->GetBaselineOffsetValue().ConvertToVp());
    }
    return AceType::MakeRefPtr<BaselineOffsetSpan>(baselineOffset, start, end);
}

RefPtr<LetterSpacingSpan> SpanString::ToLetterSpacingSpan(
    const RefPtr<NG::SpanItem>& spanItem, int32_t start, int32_t end)
{
    CHECK_NULL_RETURN(spanItem && spanItem->fontStyle, nullptr);
    Dimension letterSpacing;
    if (spanItem->fontStyle->GetLetterSpacing().has_value()) {
        letterSpacing.SetValue(spanItem->fontStyle->GetLetterSpacingValue().ConvertToVp());
    }
    return AceType::MakeRefPtr<LetterSpacingSpan>(letterSpacing, start, end);
}

RefPtr<GestureSpan> SpanString::ToGestureSpan(const RefPtr<NG::SpanItem>& spanItem, int32_t start, int32_t end)
{
    GestureStyle gestureInfo;
    if (spanItem->onClick) {
        gestureInfo.onClick = spanItem->onClick;
    }
    if (spanItem->onLongPress) {
        gestureInfo.onLongPress = spanItem->onLongPress;
    }
    return AceType::MakeRefPtr<GestureSpan>(gestureInfo, start, end);
}

RefPtr<TextShadowSpan> SpanString::ToTextShadowSpan(
    const RefPtr<NG::SpanItem>& spanItem, int32_t start, int32_t end)
{
    CHECK_NULL_RETURN(spanItem && spanItem->fontStyle, nullptr);
    std::vector<Shadow> textShadow = spanItem->fontStyle->GetTextShadow().value_or(std::vector<Shadow> { Shadow() });
    return AceType::MakeRefPtr<TextShadowSpan>(textShadow, start, end);
}

RefPtr<ImageSpan> SpanString::ToImageSpan(const RefPtr<NG::SpanItem>& spanItem, int32_t start, int32_t end)
{
    auto imageItem = DynamicCast<NG::ImageSpanItem>(spanItem);
    CHECK_NULL_RETURN(imageItem && start + 1 == end, nullptr);
    return AceType::MakeRefPtr<ImageSpan>(imageItem->options, start);
}

RefPtr<ParagraphStyleSpan> SpanString::ToParagraphStyleSpan(
    const RefPtr<NG::SpanItem>& spanItem, int32_t start, int32_t end)
{
    CHECK_NULL_RETURN(spanItem && spanItem->textLineStyle, nullptr);
    SpanParagraphStyle paragraphStyle;
    paragraphStyle.align = spanItem->textLineStyle->GetTextAlign();
    paragraphStyle.textVerticalAlign = spanItem->textLineStyle->GetTextVerticalAlign();
    paragraphStyle.maxLines = spanItem->textLineStyle->GetMaxLines();
    paragraphStyle.textOverflow = spanItem->textLineStyle->GetTextOverflow();
    paragraphStyle.leadingMargin = spanItem->textLineStyle->GetLeadingMargin();
    paragraphStyle.wordBreak = spanItem->textLineStyle->GetWordBreak();
    paragraphStyle.textIndent = spanItem->textLineStyle->GetTextIndent();
    paragraphStyle.paragraphSpacing = spanItem->textLineStyle->GetParagraphSpacing();
    return AceType::MakeRefPtr<ParagraphStyleSpan>(paragraphStyle, start, end);
}

RefPtr<LineHeightSpan> SpanString::ToLineHeightSpan(const RefPtr<NG::SpanItem>& spanItem, int32_t start, int32_t end)
{
    CHECK_NULL_RETURN(spanItem && spanItem->textLineStyle, nullptr);
    Dimension lineHeight;
    if (spanItem->textLineStyle->GetLineHeight().has_value()) {
        lineHeight.SetValue(spanItem->textLineStyle->GetLineHeightValue().ConvertToVp());
    }
    return AceType::MakeRefPtr<LineHeightSpan>(lineHeight, start, end);
}

RefPtr<BackgroundColorSpan> SpanString::ToBackgroundColorSpan(
    const RefPtr<NG::SpanItem>& spanItem, int32_t start, int32_t end)
{
    CHECK_NULL_RETURN(spanItem, nullptr);
    std::optional<TextBackgroundStyle> backgroundStyle;
    if (spanItem->backgroundStyle.has_value()) {
        backgroundStyle = spanItem->backgroundStyle.value();
    }
    return AceType::MakeRefPtr<BackgroundColorSpan>(backgroundStyle, start, end);
}

RefPtr<UrlSpan> SpanString::ToUrlSpan(const RefPtr<NG::SpanItem>& spanItem, int32_t start, int32_t end)
{
    CHECK_NULL_RETURN(spanItem && spanItem->urlOnRelease && !spanItem->GetUrlAddress().empty(), nullptr);
    std::string urlAddress = UtfUtils::Str16DebugToStr8(spanItem->GetUrlAddress());
    return AceType::MakeRefPtr<UrlSpan>(urlAddress, start, end);
}

} // namespace OHOS::Ace
