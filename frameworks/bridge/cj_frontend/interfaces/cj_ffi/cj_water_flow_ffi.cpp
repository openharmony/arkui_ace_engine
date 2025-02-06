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

#include "cj_water_flow_ffi.h"

#include "cj_lambda.h"

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_scroll_ffi.h"
#include "core/common/container.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::Framework {
NativeWaterFlowSections::NativeWaterFlowSections() : FFIData()
{
    RefPtr<NG::WaterFlowSections> sections = AceType::MakeRefPtr<NG::WaterFlowSections>();
    SetWaterFlowSections(sections);
}
} // namespace OHOS::Ace::Framework

extern "C" {
void FfiOHOSAceFrameworkWaterFlowCreate(void (*footer)(), int32_t scrollerID, bool scrollerHasValue, int32_t sectionID,
    bool sectionsIDHasValue, int32_t direction)
{
    WaterFlowModel::GetInstance()->Create();
    WaterFlowModel::GetInstance()->SetLayoutMode(static_cast<NG::WaterFlowLayoutMode>(direction));

    if (scrollerHasValue) {
        auto scroller = FFIData::GetData<NativeNGScroller>(scrollerID);
        if (scroller == nullptr) {
            LOGE("invalid scrollerID");
            return;
        }
        auto positionController = WaterFlowModel::GetInstance()->CreateScrollController();
        scroller->SetController(positionController);

        auto proxy = AceType::DynamicCast<NG::ScrollBarProxy>(scroller->GetScrollBarProxy());
        if (!proxy) {
            proxy = AceType::MakeRefPtr<NG::ScrollBarProxy>();
            scroller->SetScrollBarProxy(proxy);
        }
        WaterFlowModel::GetInstance()->SetScroller(positionController, proxy);
    }

    if (sectionsIDHasValue) {
        auto self = FFIData::GetData<NativeWaterFlowSections>(sectionID);
        if (self == nullptr) {
            LOGE("invalid sectionID");
            return;
        }
        auto waterFlowSections = WaterFlowModel::GetInstance()->GetOrCreateWaterFlowSections();
        auto localSections = self->GetWaterFlowSections()->GetSectionInfo();
        waterFlowSections->ReplaceFrom(0, localSections);
    } else {
        WaterFlowModel::GetInstance()->ResetSections();
        auto lambda = CJLambda::Create(footer);
        auto builderFunc = [lambda]() { lambda(); };
        WaterFlowModel::GetInstance()->SetFooter(std::move(builderFunc));
    }
}

void FfiOHOSAceFrameworkWaterFlowSetColumnsTemplate(const char* content)
{
    auto string = static_cast<std::string>(content);
    WaterFlowModel::GetInstance()->SetColumnsTemplate(string);
}

void FfiOHOSAceFrameworkWaterFlowSetRowsTemplate(const char* content)
{
    auto string = static_cast<std::string>(content);
    WaterFlowModel::GetInstance()->SetRowsTemplate(string);
}

void FfiOHOSAceFrameworkWaterFlowSetItemConstraintSize(double minWidth, int32_t minWidthUnit, double maxWidth,
    int32_t maxWidthUnit, double minHeight, int32_t minHeightUnit, double maxHeight, int32_t maxHeightUnit)
{
    CalcDimension minWidthLocal = CalcDimension(minWidth, static_cast<DimensionUnit>(minWidthUnit));
    WaterFlowModel::GetInstance()->SetItemMinWidth(minWidthLocal);
    CalcDimension maxWidthLocal = CalcDimension(maxWidth, static_cast<DimensionUnit>(maxWidthUnit));
    WaterFlowModel::GetInstance()->SetItemMaxWidth(maxWidthLocal);
    CalcDimension minHeightLocal = CalcDimension(minHeight, static_cast<DimensionUnit>(minHeightUnit));
    WaterFlowModel::GetInstance()->SetItemMinHeight(minHeightLocal);
    CalcDimension maxHeightLocal = CalcDimension(maxHeight, static_cast<DimensionUnit>(maxHeightUnit));
    WaterFlowModel::GetInstance()->SetItemMaxHeight(maxHeightLocal);
}
void FfiOHOSAceFrameworkWaterFlowSetColumnsGap(double size, int32_t unit)
{
    CalcDimension value = CalcDimension(size, static_cast<DimensionUnit>(unit));
    WaterFlowModel::GetInstance()->SetColumnsGap(value);
}

void FfiOHOSAceFrameworkWaterFlowSetRowsGap(double size, int32_t unit)
{
    CalcDimension value = CalcDimension(size, static_cast<DimensionUnit>(unit));
    WaterFlowModel::GetInstance()->SetRowsGap(value);
}

void FfiOHOSAceFrameworkWaterFlowSetFriction(double value)
{
    WaterFlowModel::GetInstance()->SetFriction(value);
}

void FfiOHOSAceFrameworkWaterFlowSetLayoutDirection(int32_t value)
{
    if (value < static_cast<int32_t>(FlexDirection::ROW) ||
        value > static_cast<int32_t>(FlexDirection::COLUMN_REVERSE)) {
        WaterFlowModel::GetInstance()->SetLayoutDirection(FlexDirection::COLUMN);
    } else {
        WaterFlowModel::GetInstance()->SetLayoutDirection(static_cast<FlexDirection>(value));
    }
}

void FfiOHOSAceFrameworkWaterFlowSetCachedCount(int32_t value, bool show)
{
    WaterFlowModel::GetInstance()->SetCachedCount(value, show);
}

void FfiOHOSAceFrameworkWaterFlowSetScrollEnabled(bool value)
{
    WaterFlowModel::GetInstance()->SetScrollEnabled(value);
}

void FfiOHOSAceFrameworkWaterFlowSetNestedScroll(int32_t forward, int32_t backward)
{
    int32_t forwardLocal = forward;
    int32_t backwardLocal = backward;
    if (forwardLocal < static_cast<int32_t>(NestedScrollMode::SELF_ONLY) ||
        forwardLocal > static_cast<int32_t>(NestedScrollMode::PARALLEL)) {
        forwardLocal = 0;
    }
    if (backwardLocal < static_cast<int32_t>(NestedScrollMode::SELF_ONLY) ||
        backwardLocal > static_cast<int32_t>(NestedScrollMode::PARALLEL)) {
        backwardLocal = 0;
    }
    NestedScrollOptions nestedOpt = { .forward = static_cast<NestedScrollMode>(forwardLocal),
        .backward = static_cast<NestedScrollMode>(backwardLocal) };
    WaterFlowModel::GetInstance()->SetNestedScroll(nestedOpt);
}

void FfiOHOSAceFrameworkWaterFlowSetOnReachStartCallback(void (*callback)())
{
    auto lambda = CJLambda::Create(callback);
    auto onReachStart = [lambda]() { lambda(); };
    WaterFlowModel::GetInstance()->SetOnReachStart(std::move(onReachStart));
}

void FfiOHOSAceFrameworkWaterFlowSetOnReachEndCallback(void (*callback)())
{
    auto lambda = CJLambda::Create(callback);
    auto onReachEnd = [lambda]() { lambda(); };
    WaterFlowModel::GetInstance()->SetOnReachEnd(std::move(onReachEnd));
}

void FfiOHOSAceFrameworkWaterFlowScrollBar(int32_t value)
{
    auto displayMode = static_cast<DisplayMode>(value);
    WaterFlowModel::GetInstance()->SetScrollBarMode(displayMode);
}

void FfiOHOSAceFrameworkWaterFlowScrollBarColor(uint32_t color)
{
    WaterFlowModel::GetInstance()->SetScrollBarColor(Color(color).ColorToString());
}

void FfiOHOSAceFrameworkWaterFlowScrollBarWidth(double value, int32_t valueUnit)
{
    Dimension dimWidth(value, static_cast<DimensionUnit>(valueUnit));
    CalcDimension scrollBarWidth = CalcDimension(dimWidth);
    if (scrollBarWidth.Unit() == DimensionUnit::PERCENT) {
        return;
    }
    WaterFlowModel::GetInstance()->SetScrollBarWidth(scrollBarWidth.ToString());
}

void FfiOHOSAceFrameworkWaterFlowEdgeEffect(int32_t value, bool isEnabled)
{
    auto edgeEffect = value;
    if (edgeEffect < static_cast<int32_t>(EdgeEffect::SPRING) || edgeEffect > static_cast<int32_t>(EdgeEffect::NONE)) {
        edgeEffect = static_cast<int32_t>(EdgeEffect::NONE);
    }
    WaterFlowModel::GetInstance()->SetEdgeEffect(static_cast<EdgeEffect>(edgeEffect), isEnabled);
}

void FfiOHOSAceFrameworkWaterFlowOnScrollStart(void (*callback)())
{
    auto lambda = CJLambda::Create(callback);
    auto onScrollStart = [lambda]() {
        lambda();
    };
    WaterFlowModel::GetInstance()->SetOnScrollStart(std::move(onScrollStart));
}

void FfiOHOSAceFrameworkWaterFlowOnScrollStop(void (*callback)())
{
    auto lambda = CJLambda::Create(callback);
    auto onScrollStop = [lambda]() {
        lambda();
    };
    WaterFlowModel::GetInstance()->SetOnScrollStop(std::move(onScrollStop));
}

void FfiOHOSAceFrameworkWaterFlowSetOnScrollFrameBegin(double (*callback)(double offset, int32_t state))
{
    auto lambda = CJLambda::Create(callback);
    auto onScrollBegin = [lambda](const Dimension& offset, const ScrollState& state) -> ScrollFrameResult {
        ScrollFrameResult scrollRes { .offset = offset };
        auto result = lambda(offset.Value(), static_cast<int32_t>(state));
        scrollRes.offset = Dimension(result, DimensionUnit::VP);
        return scrollRes;
    };
    WaterFlowModel::GetInstance()->SetOnScrollFrameBegin(std::move(onScrollBegin));
}

void FfiOHOSAceFrameworkWaterFlowSetScrollIndexCallback(void (*callback)(int32_t first, int32_t last))
{
    auto lambda = CJLambda::Create(callback);
    auto onScrollIndex = [lambda](int32_t first, const int32_t last) {
        lambda(first, last);
        return;
    };
    WaterFlowModel::GetInstance()->SetOnScrollIndex(std::move(onScrollIndex));
}

int64_t FfiOHOSAceFrameworkWaterFlowSectionsCreate()
{
    auto sections = FFIData::Create<NativeWaterFlowSections>();
    if (sections == nullptr) {
        return FFI_ERROR_CODE;
    }
    return sections->GetID();
}

bool FfiOHOSAceFrameworkWaterFlowSectionsSplice(
    int64_t selfID, int32_t start, uint32_t deleteCount, CArrNativeSectionOptions sections)
{
    std::vector<NG::WaterFlowSections::Section> newSections;
    for (int32_t i = 0; i < sections.size; i++) {
        NativeSectionOptions nativeSection = sections.head[i];
        NG::WaterFlowSections::Section section;
        section.itemsCount = nativeSection.itemCount;
        section.crossCount = nativeSection.crossCount;
        if (nativeSection.columnsGapHasValue) {
            section.columnsGap =
                Dimension(nativeSection.columnsGapValue, static_cast<DimensionUnit>(nativeSection.columnsGapUnit));
        } else {
            section.columnsGap = std::nullopt;
        }
        if (nativeSection.rowsGapHasValue) {
            section.rowsGap =
                Dimension(nativeSection.rowsGapValue, static_cast<DimensionUnit>(nativeSection.rowsGapUnit));
        } else {
            section.rowsGap = std::nullopt;
        }
        section.margin->SetEdges(
            NG::CalcLength(nativeSection.margin.left, static_cast<DimensionUnit>(nativeSection.margin.leftUnit)),
            NG::CalcLength(nativeSection.margin.right, static_cast<DimensionUnit>(nativeSection.margin.rightUnit)),
            NG::CalcLength(nativeSection.margin.top, static_cast<DimensionUnit>(nativeSection.margin.topUnit)),
            NG::CalcLength(nativeSection.margin.bottom, static_cast<DimensionUnit>(nativeSection.margin.bottomUnit)));
        if (nativeSection.onGetItemMainSizeByIndexHasValue) {
            auto lambda = CJLambda::Create(nativeSection.onGetItemMainSizeByIndex);
            auto onGetItemMainSizeByIndexLocal = [lambda](int32_t index) -> float { return lambda(index); };
            section.onGetItemMainSizeByIndex = std::move(onGetItemMainSizeByIndexLocal);
        }
        newSections.emplace_back(section);
    }

    auto self = FFIData::GetData<NativeWaterFlowSections>(selfID);
    if (self) {
        auto localSections = self->GetWaterFlowSections();
        localSections->ChangeData(start, deleteCount, newSections);
        return true;
    } else {
        LOGE("invalid water flow sections id in splice");
        return false;
    }
}

bool FfiOHOSAceFrameworkWaterFlowSectionsPush(int64_t selfID, NativeSectionOptions nativeSection)
{
    return FfiOHOSAceFrameworkWaterFlowSectionsUpdate(
        selfID, FfiOHOSAceFrameworkWaterFlowSectionsLength(selfID), nativeSection);
}

bool FfiOHOSAceFrameworkWaterFlowSectionsUpdate(
    int64_t selfID, uint32_t sectionIndex, NativeSectionOptions nativeSection)
{
    NG::WaterFlowSections::Section section;
    section.itemsCount = nativeSection.itemCount;
    section.crossCount = nativeSection.crossCount;
    if (nativeSection.columnsGapHasValue) {
        section.columnsGap =
            Dimension(nativeSection.columnsGapValue, static_cast<DimensionUnit>(nativeSection.columnsGapUnit));
    } else {
        section.columnsGap = std::nullopt;
    }
    if (nativeSection.rowsGapHasValue) {
        section.rowsGap = Dimension(nativeSection.rowsGapValue, static_cast<DimensionUnit>(nativeSection.rowsGapUnit));
    } else {
        section.rowsGap = std::nullopt;
    }
    section.margin->SetEdges(
        NG::CalcLength(nativeSection.margin.left, static_cast<DimensionUnit>(nativeSection.margin.leftUnit)),
        NG::CalcLength(nativeSection.margin.right, static_cast<DimensionUnit>(nativeSection.margin.rightUnit)),
        NG::CalcLength(nativeSection.margin.top, static_cast<DimensionUnit>(nativeSection.margin.topUnit)),
        NG::CalcLength(nativeSection.margin.bottom, static_cast<DimensionUnit>(nativeSection.margin.bottomUnit)));
    if (nativeSection.onGetItemMainSizeByIndexHasValue) {
        auto lambda = CJLambda::Create(nativeSection.onGetItemMainSizeByIndex);
        auto onGetItemMainSizeByIndexLocal = [lambda](int32_t index) -> float { return lambda(index); };
        section.onGetItemMainSizeByIndex = std::move(onGetItemMainSizeByIndexLocal);
    }

    std::vector<NG::WaterFlowSections::Section> newSections;
    newSections.emplace_back(section);

    auto self = FFIData::GetData<NativeWaterFlowSections>(selfID);
    if (self) {
        auto localSections = self->GetWaterFlowSections();
        localSections->ChangeData(sectionIndex, 1, newSections);
        return true;
    } else {
        LOGE("invalid water flow sections id in update");
        return false;
    }
}

uint32_t FfiOHOSAceFrameworkWaterFlowSectionsLength(int64_t selfID)
{
    auto self = FFIData::GetData<NativeWaterFlowSections>(selfID);
    uint32_t result;
    if (self) {
        auto localSections = self->GetWaterFlowSections();
        result = localSections->GetSectionInfo().size();
        return result;
    } else {
        LOGE("invalid water flow sections id in length");
        return 0;
    }
}

void FfiOHOSAceFrameworkWaterFlowSectionsValue(int64_t selfID, CArrNativeSectionOptions sections)
{
    LOGE("tbd");
    return;
}

void FfiOHOSAceFrameworkFlowItemCreate()
{
    WaterFlowItemModel::GetInstance()->Create();
}
}
