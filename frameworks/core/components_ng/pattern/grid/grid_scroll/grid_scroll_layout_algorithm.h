/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_SCROLL_GRID_SCROLL_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_SCROLL_GRID_SCROLL_LAYOUT_ALGORITHM_H

#include "core/components_ng/pattern/grid/grid_item_layout_property.h"
#include "core/components_ng/pattern/grid/grid_layout_base_algorithm.h"
#include "core/components_ng/pattern/grid/grid_layout_info.h"
#include "core/components_ng/pattern/grid/grid_layout_property.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT GridScrollLayoutAlgorithm : public GridLayoutBaseAlgorithm {
    DECLARE_ACE_TYPE(GridScrollLayoutAlgorithm, GridLayoutBaseAlgorithm);

public:
    GridScrollLayoutAlgorithm(GridLayoutInfo gridLayoutInfo, uint32_t crossCount, uint32_t mainCount)
        : GridLayoutBaseAlgorithm(std::move(gridLayoutInfo)), crossCount_(crossCount), mainCount_(mainCount) {};
    ~GridScrollLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

    void SetCanOverScrollStart(bool canOverScroll)
    {
        canOverScrollStart_ = canOverScroll;
    }

    void SetCanOverScrollEnd(bool canOverScroll)
    {
        canOverScrollEnd_ = canOverScroll;
    }

    void SetScrollSource(int32_t scrollSource)
    {
        scrollSource_ = scrollSource;
    }

    /**
     * @brief Set enableSkipping_ parameter. When skip is enabled, the algorithm would skip measuring intermediate items
     * when the offset change is large (larger than the whole viewport).
     *
     * @param skip
     */
    void SetLineSkipping(bool skip)
    {
        enableSkipping_ = skip;
    }

    std::unique_ptr<GridLayoutInfo>&& MoveInfoCopy()
    {
        return std::move(infoCopy_);
    }

    template<class T>
    void DeleteItemsOutOfScope(std::map<int32_t, T>& map, int32_t startLineIndex, int32_t endLineIndex)
    {
        auto iter = map.begin();
        while (iter != map.end()) {
            if (iter->first < startLineIndex || iter->first > endLineIndex) {
                iter = map.erase(iter);
            } else {
                ++iter;
            }
        }
    }

protected:
    void SkipForwardLines(float mainSize, LayoutWrapper* layoutWrapper);
    void SkipBackwardLines(float mainSize, LayoutWrapper* layoutWrapper);
    void SkipRegularLines(bool forward);
    virtual void SkipIrregularLines(LayoutWrapper* layoutWrapper, bool forward);

private:
    void FillGridViewportAndMeasureChildren(float mainSize, float crossSize, LayoutWrapper* layoutWrapper);
    void ReloadToStartIndex(float mainSize, float crossSize, LayoutWrapper* layoutWrapper);
    void ReloadFromUpdateIdxToStartIndex(
        float mainSize, float crossSize, int32_t updateLineIndex, LayoutWrapper* layoutWrapper);
    float MeasureRecordedItems(float mainSize, float crossSize, LayoutWrapper* layoutWrapper);
    bool UseCurrentLines(float mainSize, float crossSize, LayoutWrapper* layoutWrapper, float& mainLength);
    virtual void SkipLargeOffset(float mainSize, LayoutWrapper* layoutWrapper);

    // fill start of viewport
    bool FillBlankAtStart(float mainSize, float crossSize, LayoutWrapper* layoutWrapper);
    float FillNewLineForward(float crossSize, float mainSize, LayoutWrapper* layoutWrapper);
    void AddForwardLines(int32_t currentIndex, float crossSize, float mainSize, LayoutWrapper* layoutWrapper);
    void UpdateMatrixForAddedItems();
    // Fill forward one line, but do not update startMainLineIndex_ and startIndex_
    virtual void FillOneLineForwardWithoutUpdatingStartIndex(
        float crossSize, float mainSize, LayoutWrapper* layoutWrapper);

    // fill end of viewport
    void FillBlankAtEnd(float mainSize, float crossSize, LayoutWrapper* layoutWrapper, float& mainLength);
    float FillNewLineBackward(float crossSize, float mainSize, LayoutWrapper* layoutWrapper, bool reverse);
    void FillCurrentLine(float mainSize, float crossSize, LayoutWrapper* layoutWrapper);

    // Measure grid item which not exist in grid matrix already, need to place it and save to grid matrix.
    int32_t MeasureNewChild(const SizeF& frameSize, int32_t itemIndex, LayoutWrapper* layoutWrapper,
        const RefPtr<LayoutWrapper>& childLayoutWrapper, bool reverse);
    // Measure grid item which exist in grid matrix already, needn't to place it again.
    int32_t MeasureChildPlaced(const SizeF& frameSize, int32_t itemIndex, int32_t crossStart,
        LayoutWrapper* layoutWrapper, const RefPtr<LayoutWrapper>& childLayoutWrapper);
    bool CheckNeedMeasure(const RefPtr<LayoutWrapper>& layoutWrapper, const LayoutConstraintF& layoutConstraint) const;
    bool CheckNeedMeasureWhenStretch(
        const RefPtr<LayoutWrapper>& layoutWrapper, const LayoutConstraintF& layoutConstraint) const;
    void MeasureChild(LayoutWrapper* layoutWrapper, const SizeF& frameSize,
        const RefPtr<LayoutWrapper>& childLayoutWrapper, int32_t crossStart, int32_t crossSpan);

    // Compote position of grid item in cross axis.
    float ComputeItemCrossPosition(int32_t crossStart) const;
    virtual void LargeItemLineHeight(const RefPtr<LayoutWrapper>& itemWrapper);
    // Find next valid cell when current is not valid.
    bool GetNextGrid(int32_t& curMain, int32_t& curCross, bool reverse) const;
    // Find a valid cell to place grid item and save to grid matrix.
    bool CheckGridPlaced(int32_t index, int32_t main, int32_t cross, int32_t mainSpan, int32_t crossSpan);
    LayoutConstraintF CreateChildConstraint(float mainSize, float crossSize,
        const RefPtr<GridLayoutProperty>& gridLayoutProperty, int32_t crossStart, int32_t crossSpan) const;
    void ModifyCurrentOffsetWhenReachEnd(float mainSize, LayoutWrapper* layoutWrapper);
    void InitialItemsCrossSize(
        const RefPtr<GridLayoutProperty>& layoutProperty, const SizeF& frameSize, int32_t childrenCount);
    bool IsIndexInMatrix(int32_t index, int32_t& startLine);
    void UpdateGridLayoutInfo(LayoutWrapper* layoutWrapper, float mainSize);
    virtual void GetTargetIndexInfoWithBenchMark(
        LayoutWrapper* layoutWrapper, bool isTargetBackward, int32_t targetIndex);

    void UpdateOffsetOnVirtualKeyboardHeightChange(LayoutWrapper* layoutWrapper, float mainSize);
    void AdaptToChildMainSize(LayoutWrapper* layoutWrapper, RefPtr<GridLayoutProperty>& gridLayoutProperty,
        float mainSize, SizeF idealSize, bool matchChildren);
    void UpdateOffsetOnHeightChangeDuringAnimation(LayoutWrapper* layoutWrapper, float mainSize);

    virtual int32_t GetStartingItem(LayoutWrapper* layoutWrapper, int32_t currentIndex);

    OffsetF CalculateLargeItemOffset(
        OffsetF currOffset, int32_t itemIndex, int32_t currLineIndex, int32_t currentCrossIndex);
    bool NeedAdjust(const RefPtr<GridItemLayoutProperty>& itemLayoutWrapper);
    virtual void AdjustRowColSpan(
        const RefPtr<LayoutWrapper>& itemLayoutWrapper, LayoutWrapper* layoutWrapper, int32_t itemIndex);
    void LargeItemNextLineHeight(int32_t currentLineIndex, LayoutWrapper* layoutWrapper);
    void LargeItemForwardLineHeight(int32_t currentLineIndex, LayoutWrapper* LayoutWrapper);
    int32_t CalculateLineIndexForLargeItem(std::map<int32_t, std::map<int32_t, int32_t>>::iterator gridMatrixIter,
        int32_t currentIndex, int32_t lineIndex, LayoutWrapper* layoutWrapper);
    void CalculateLineHeightForLargeItem(int32_t lineIndex, int32_t currentLineIndex,
        std::map<int32_t, std::map<int32_t, int32_t>>::iterator gridMatrixIter, LayoutWrapper* layoutWrapper);
    void ScrollToIndexStart(LayoutWrapper* layoutWrapper, int32_t targetIndex);
    void ScrollToIndexAuto(LayoutWrapper* layoutWrapper, float mainSize, int32_t targetIndex);
    bool IsScrollToEndLine() const;
    bool IsEndLineInScreenWithGap(int32_t targetLine, float totalViewHeight, float mainSize) const;
    void UpdateCurrentOffsetForJumpTo(float mainSize);
    void SupplyAllData2ZeroIndex(float mainSize, float crossSize, LayoutWrapper* layoutWrapper);

    void FillCacheLineAtEnd(float mainSize, float crossSize, LayoutWrapper* layoutWrapper);
    float FillNewCacheLineBackward(float crossSize, float mainSize, LayoutWrapper* layoutWrapper, int32_t currentLine);
    int32_t MeasureCachedChild(const SizeF& frameSize, int32_t itemIndex, LayoutWrapper* layoutWrapper,
        const RefPtr<LayoutWrapper>& childLayoutWrapper);

    void CreateCachedChildConstraint(LayoutWrapper* layoutWrapper, float mainSize, float crossSize);

    static bool PredictBuildItem(FrameNode& host, int32_t itemIdx, const GridPredictLayoutParam& param);
    static void SyncGeometry(RefPtr<LayoutWrapper>& wrapper);
    void CompleteItemCrossPosition(LayoutWrapper* layoutWrapper, const std::map<int32_t, int32_t>& items);
    /**
     * @brief Updates the main line during ReloadToStartIndex based on the new crossCount_.
     *
     * @param startIdx index of the first GridItem in viewport
     */
    virtual void UpdateMainLineOnReload(int32_t startIdx);

    // get [resetFromStart,resetFromUpdate]
    std::pair<bool, bool> GetResetMode(LayoutWrapper* layoutWrapper, int32_t updateIdx);

    void CheckReset(float mainSize, float crossSize, LayoutWrapper* layoutWrapper);

    bool CheckLastLineItemFullyShowed(LayoutWrapper* layoutWrapper);

    void ResetOffsetWhenHeightChanged();

    bool IsIrregularLine(int32_t lineIndex) const override;

    void MergeRemainingLines(std::map<int32_t, std::map<int32_t, int32_t>> matrix, int32_t forwardLines);

    bool SkipLargeLineHeightLines(float mainSize);

    /**
     * @brief immediately create & measure items in cache range.
     *
     * @param cacheLineCnt number of lines to preload above and below viewport.
     */
    void SyncPreload(LayoutWrapper* wrapper, int32_t cacheLineCnt, float crossSize, float mainSize);

    virtual std::pair<int32_t, int32_t> CalculateCachedCount(LayoutWrapper* layoutWrapper, int32_t cachedCount)
    {
        return std::make_pair(cachedCount * crossCount_, cachedCount * crossCount_);
    }

    std::string GetReloadReasonStr(GridReloadReason reason)
    {
        switch (reason) {
            case GridReloadReason::INIT:
                return "init";
            case GridReloadReason::CROSS_COUNT_CHANGE:
                return "cross count change";
            case GridReloadReason::DATA_RELOAD:
                return "data reload";
            case GridReloadReason::SCROLL_TO_INDEX:
                return "scroll to index";
            case GridReloadReason::SKIP_LARGE_OFFSET:
                return "skip large offset";
            default:
                return "";
        }
    }

    bool HasLayoutOptions(LayoutWrapper* layoutWrapper);

    virtual void PreloadItems(LayoutWrapper* layoutWrapper);

    void ClearUnlayoutedItems(LayoutWrapper* layoutWrapper);

    void UpdateUnlayoutedItems();

protected:
    uint32_t crossCount_ = 0;
    uint32_t mainCount_ = 0;
    int32_t currentItemRowSpan_ = 0;
    int32_t currentItemColSpan_ = 0;
    int32_t currentItemRowStart_ = -1;
    int32_t currentItemColStart_ = -1;
    int32_t currentItemRowEnd_ = -1;
    int32_t currentItemColEnd_ = -1;
    float cellAveLength_ = -1.0f;
    float mainGap_ = 0;
    float crossGap_ = 0;
    std::map<int32_t, float> itemsCrossSize_; // grid item's size in cross axis.
    std::list<GridPreloadItem> predictBuildList_;
    LayoutConstraintF cachedChildConstraint_;
    std::map<int32_t, float> unLayoutedItems_;

private:
    /**
     * @brief Measure items on a line previously recorded
     *
     * @param line index of line to measure
     * updates @param mainLength by adding this line's measured height
     * updates @param endIdx with max item index in this line
     * updates @param isScrollableSpringMotionRunning spring effect is runnning
     * @return false if line isn't recorded.
     */
    bool MeasureExistingLine(
        int32_t line, float& mainLength, int32_t& endIdx, bool isScrollableSpringMotionRunning = false);

    float GetContentHeight(LayoutWrapper* layoutWrapper);

    LayoutWrapper* wrapper_;
    SizeF frameSize_;
    int32_t currentMainLineIndex_ = 0;        // it equals to row index in vertical grid
    int32_t moveToEndLineIndex_ = -1;         // place index in the last line when scroll to index after matrix
    Axis axis_ = Axis::VERTICAL;

    float crossPaddingOffset_ = 0;
    int32_t lastCross_ = 0;
    int32_t cacheEnd_ = 0;
    bool isChildrenUpdated_ = false;

    bool expandSafeArea_ = false;
    bool canOverScrollStart_ = false;
    bool canOverScrollEnd_ = false;
    bool enableSkipping_ = true;               // enables skipping lines on a large offset change.
    bool isLayouted_ = true;
    std::unique_ptr<GridLayoutInfo> infoCopy_; // legacy impl to save independent data for animation.

    // Map structure: [index, crossPosition], store cross position of each item.
    std::map<int32_t, float> itemsCrossPosition_;
    int32_t scrollSource_ = SCROLL_FROM_NONE;
    OffsetF childFrameOffset_;
    GridReloadReason reason_;

    ACE_DISALLOW_COPY_AND_MOVE(GridScrollLayoutAlgorithm);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_SCROLL_GRID_SCROLL_LAYOUT_ALGORITHM_H
