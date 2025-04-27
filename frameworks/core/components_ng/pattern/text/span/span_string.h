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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_SPAN_SPAN_STRING_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_SPAN_SPAN_STRING_H

#include <list>
#include <string>
#include <unordered_map>
#include <vector>

#include "base/memory/referenced.h"
#include "core/components_ng/pattern/text/span/tlv_util.h"
#include "core/components_ng/pattern/text/span/span_object.h"
#include "core/components_ng/pattern/text/text_model.h"

namespace OHOS::Ace {

class SpanStringBase;

enum class SpanStringOperation { REPLACE = 0, INSERT, REMOVE };

class ACE_EXPORT SpanString : public SpanStringBase {
    DECLARE_ACE_TYPE(SpanString, SpanStringBase);

public:
    explicit SpanString(const std::u16string& text);
    explicit SpanString(const ImageSpanOptions& options);
    explicit SpanString(RefPtr<CustomSpan>& span);
    ~SpanString() override;
    const std::string GetString() const;
    const std::u16string& GetU16string() const;
    int32_t GetLength() const;
    void SetString(const std::u16string& text);
    void SetFramNode(const WeakPtr<NG::FrameNode>& frameNode);
    void MarkDirtyFrameNode();
    void AddCustomSpan();
    void RemoveCustomSpan();
    void SetGroupId(const RefPtr<SpanBase>& span);
    void SetSpanItems(const std::list<RefPtr<NG::SpanItem>>&& spanItems);
    void SetSpanMap(std::unordered_map<SpanType, std::list<RefPtr<SpanBase>>>&& spansMap);
    const std::unordered_map<SpanType, std::list<RefPtr<SpanBase>>>& GetSpansMap() const;
    bool IsEqualToSpanString(const RefPtr<SpanString>& other) const;
    RefPtr<SpanString> GetSubSpanString(int32_t start, int32_t length, bool includeStartHalf = false,
        bool includeEndHalf = true, bool rangeNeedNotChange = true) const;
    std::vector<RefPtr<SpanBase>> GetSpans(int32_t start, int32_t length) const;
    std::vector<RefPtr<SpanBase>> GetSpans(int32_t start, int32_t length, SpanType spanType) const;
    RefPtr<SpanBase> GetSpan(int32_t start, int32_t length, SpanType spanType) const;
    bool operator==(const SpanString& other) const;
    std::list<RefPtr<NG::SpanItem>> GetSpanItems() const;
    void AddSpan(const RefPtr<SpanBase>& span);
    void RemoveSpan(int32_t start, int32_t length, SpanType key);
    bool CheckRange(int32_t start, int32_t length, bool allowLengthZero = false) const;
    void BindWithSpans(const std::vector<RefPtr<SpanBase>>& spans);
    bool EncodeTlv(std::vector<uint8_t>& buff);
    static RefPtr<SpanString> DecodeTlv(std::vector<uint8_t>& buff);
    static RefPtr<SpanString> DecodeTlv(std::vector<uint8_t>& buff,
        const std::function<RefPtr<ExtSpan>(const std::vector<uint8_t>&, int32_t, int32_t)>&& unmarshallCallback,
        int32_t instanceId = -1);
    static void DecodeTlvOldExt(std::vector<uint8_t>& buff, SpanString* spanString, int32_t& cursor);
    static void DecodeTlvExt(std::vector<uint8_t>& buff, SpanString* spanString,
        const std::function<RefPtr<ExtSpan>(const std::vector<uint8_t>&, int32_t, int32_t)>&& unmarshallCallback,
        int32_t instanceId = -1);
    static void DecodeSpanItemList(std::vector<uint8_t>& buff, int32_t& cursor, RefPtr<SpanString>& spanStr);
    static void DecodeSpanItemListExt(std::vector<uint8_t>& buff, int32_t& cursor, SpanString* spanStr);
    void ClearSpans();
    void AppendSpanItem(const RefPtr<NG::SpanItem>& spanItem);
    void UpdateSpansMap();
    RefPtr<LineHeightSpan> ToLineHeightSpan(const RefPtr<NG::SpanItem>& spanItem, int32_t start, int32_t end);
    RefPtr<BackgroundColorSpan> ToBackgroundColorSpan(const RefPtr<NG::SpanItem>& spanItem, int32_t start, int32_t end);
    RefPtr<ParagraphStyleSpan> ToParagraphStyleSpan(
        const RefPtr<NG::SpanItem>& spanItem, int32_t start, int32_t end);
    RefPtr<ImageSpan> ToImageSpan(const RefPtr<NG::SpanItem>& spanItem, int32_t start, int32_t end);
    RefPtr<TextShadowSpan> ToTextShadowSpan(const RefPtr<NG::SpanItem>& spanItem, int32_t start, int32_t end);
    RefPtr<GestureSpan> ToGestureSpan(const RefPtr<NG::SpanItem>& spanItem, int32_t start, int32_t end);
    RefPtr<LetterSpacingSpan> ToLetterSpacingSpan(
        const RefPtr<NG::SpanItem>& spanItem, int32_t start, int32_t end);
    RefPtr<BaselineOffsetSpan> ToBaselineOffsetSpan(
        const RefPtr<NG::SpanItem>& spanItem, int32_t start, int32_t end);
    RefPtr<DecorationSpan> ToDecorationSpan(const RefPtr<NG::SpanItem>& spanItem, int32_t start, int32_t end);
    RefPtr<FontSpan> ToFontSpan(const RefPtr<NG::SpanItem>& spanItem, int32_t start, int32_t end);
    RefPtr<UrlSpan> ToUrlSpan(const RefPtr<NG::SpanItem>& spanItem, int32_t start, int32_t end);
    std::string ToString();
protected:
    std::list<RefPtr<SpanBase>> GetSubSpanList(
        int32_t start, int32_t length, const std::list<RefPtr<SpanBase>>& spans) const;
    void MergeIntervals(std::list<RefPtr<SpanBase>>& spans);
    void SplitInterval(std::list<RefPtr<SpanBase>>& spans, std::pair<int32_t, int32_t> interval);
    void ApplyToSpans(const RefPtr<SpanBase>& span, std::pair<int32_t, int32_t> interval, SpanOperation operation);
    void SortSpans(std::list<RefPtr<SpanBase>>& spans);
    bool CanMerge(const RefPtr<SpanBase>& a, const RefPtr<SpanBase>& b);
    static RefPtr<NG::SpanItem> GetDefaultSpanItem(const std::u16string& text);
    static RefPtr<SpanBase> GetDefaultSpan(SpanType type);
    void AddSpecialSpan(const RefPtr<SpanBase>& span, SpanType type, int32_t start);
    int32_t GetStepsByPosition(int32_t pos);
    void UpdateSpansWithOffset(int32_t start, int32_t offset);
    void UpdateSpanMapWithOffset(int32_t start, int32_t offset);
    void UpdateSpanBaseWithOffset(RefPtr<SpanBase>& span, int32_t start, int32_t offset);
    void RemoveSpecialSpan(int32_t start, int32_t end, SpanType type);
    // For the scene after image remove
    bool CheckRange(const RefPtr<SpanBase>& spanBase) const;
    static std::u16string GetWideStringSubstr(const std::u16string& content, int32_t start);
    static std::u16string GetWideStringSubstr(const std::u16string& content, int32_t start, int32_t length);
    std::list<RefPtr<NG::SpanItem>>::iterator SplitSpansAndForward(std::list<RefPtr<NG::SpanItem>>::iterator& it);
    RefPtr<NG::ImageSpanItem> MakeImageSpanItem(const RefPtr<ImageSpan>& imageSpan);
    RefPtr<NG::CustomSpanItem> MakeCustomSpanItem(const RefPtr<CustomSpan>& customSpan);
    void GetSpecialTypesVector(std::list<int32_t>& indexList, int32_t start, int32_t length);
    void GetNormalTypesVector(std::list<std::pair<int32_t, int32_t>>& indexList, int32_t start, int32_t length);
    bool ContainSpecialNode(int32_t start, int32_t length);
    bool IsSpecialNode(RefPtr<SpanBase> span);

    std::u16string text_;
    std::unordered_map<SpanType, std::list<RefPtr<SpanBase>>> spansMap_;
    std::list<RefPtr<NG::SpanItem>> spans_;
    WeakPtr<NG::FrameNode> framNode_;
    int32_t groupId_ = 0;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_SPAN_SPAN_STRING_H