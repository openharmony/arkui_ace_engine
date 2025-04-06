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

#ifndef OHOS_ACE_FRAMEWORK_CJ_WATER_FLOW_H
#define OHOS_ACE_FRAMEWORK_CJ_WATER_FLOW_H

#include <cstdint>

#include "ffi_remote_data.h"

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"
#include "core/components_ng/pattern/waterflow/water_flow_model.h"
#include "core/components_ng/pattern/waterflow/water_flow_model_ng.h"
#include "core/components_ng/pattern/waterflow/water_flow_sections.h"
#include "frameworks/bridge/declarative_frontend/jsview/models/water_flow_item_model_impl.h"
#include "frameworks/core/components_ng/pattern/waterflow/water_flow_item_model_ng.h"

namespace OHOS::Ace::Framework {
class ACE_EXPORT NativeWaterFlowSections : public OHOS::FFI::FFIData {
    DECL_TYPE(NativeWaterFlowSections, OHOS::FFI::FFIData)
public:
    NativeWaterFlowSections();

    RefPtr<NG::WaterFlowSections> GetWaterFlowSections() const
    {
        return WaterFlowSections_;
    }
    void SetWaterFlowSections(const RefPtr<NG::WaterFlowSections>& sections)
    {
        WaterFlowSections_ = sections;
    }

private:
    RefPtr<NG::WaterFlowSections> WaterFlowSections_;
};
} // namespace OHOS::Ace::Framework

extern "C" {
struct NativeSectionOptions {
    int32_t itemCount;
    int32_t crossCount;
    float (*onGetItemMainSizeByIndex)(int32_t);
    bool onGetItemMainSizeByIndexHasValue;
    double columnsGapValue;
    int32_t columnsGapUnit;
    bool columnsGapHasValue;
    double rowsGapValue;
    int32_t rowsGapUnit;
    bool rowsGapHasValue;
    CJEdge margin;
    float (*onGetItemMainSizeByIndexBack)(int32_t);
};

struct CArrNativeSectionOptions {
    NativeSectionOptions* head;
    int64_t size;
};

CJ_EXPORT void FfiOHOSAceFrameworkWaterFlowCreate(void (*footer)(), int32_t scrollerID, bool scrollerHasValue,
    int32_t sectionID, bool sectionsIDHasValue, int32_t direction);
CJ_EXPORT void FfiOHOSAceFrameworkWaterFlowSetColumnsTemplate(const char* content);
CJ_EXPORT void FfiOHOSAceFrameworkWaterFlowSetRowsTemplate(const char* content);
CJ_EXPORT void FfiOHOSAceFrameworkWaterFlowScrollBar(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkWaterFlowScrollBarColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkWaterFlowScrollBarWidth(double value, int32_t valueUnit);
CJ_EXPORT void FfiOHOSAceFrameworkWaterFlowEdgeEffect(int32_t value, bool isEnabled);
CJ_EXPORT void FfiOHOSAceFrameworkWaterFlowSetItemConstraintSize(double minWidth, int32_t minWidthUnit, double maxWidth,
    int32_t maxWidthUnit, double minHeight, int32_t minHeightUnit, double maxHeight, int32_t maxHeightUnit);
CJ_EXPORT void FfiOHOSAceFrameworkWaterFlowSetColumnsGap(double size, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkWaterFlowSetRowsGap(double size, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkWaterFlowSetFriction(double value);
CJ_EXPORT void FfiOHOSAceFrameworkWaterFlowSetLayoutDirection(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkWaterFlowSetCachedCount(int32_t value, bool show);
CJ_EXPORT void FfiOHOSAceFrameworkWaterFlowSetScrollEnabled(bool value);
CJ_EXPORT void FfiOHOSAceFrameworkWaterFlowSetNestedScroll(int32_t forward, int32_t backward);
CJ_EXPORT void FfiOHOSAceFrameworkWaterFlowSetOnReachStartCallback(void (*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkWaterFlowSetOnReachEndCallback(void (*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkWaterFlowOnScrollStart(void (*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkWaterFlowOnScrollStop(void (*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkWaterFlowSetOnScrollFrameBegin(double (*callback)(double offset, int32_t state));
CJ_EXPORT void FfiOHOSAceFrameworkWaterFlowSetScrollIndexCallback(void (*callback)(int32_t first, int32_t last));

CJ_EXPORT int64_t FfiOHOSAceFrameworkWaterFlowSectionsCreate();
CJ_EXPORT bool FfiOHOSAceFrameworkWaterFlowSectionsSplice(
    int64_t selfID, int32_t start, uint32_t deleteCount, CArrNativeSectionOptions sections);
CJ_EXPORT bool FfiOHOSAceFrameworkWaterFlowSectionsPush(int64_t selfID, NativeSectionOptions nativeSection);
CJ_EXPORT bool FfiOHOSAceFrameworkWaterFlowSectionsUpdate(
    int64_t selfID, uint32_t sectionIndex, NativeSectionOptions section);
CJ_EXPORT uint32_t FfiOHOSAceFrameworkWaterFlowSectionsLength(int64_t selfID);
CJ_EXPORT void FfiOHOSAceFrameworkWaterFlowSectionsValue(int64_t selfID, CArrNativeSectionOptions sections);
CJ_EXPORT void FfiOHOSAceFrameworkFlowItemCreate();
}

#endif // OHOS_ACE_FRAMEWORK_CJ_WATER_FLOW_H