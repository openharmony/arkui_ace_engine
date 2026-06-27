/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/grid/bridge/grid/arkts_native_grid_bridge.h"

#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include "base/log/ace_scoring_log.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/jsview/js_scroller.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components_ng/pattern/grid/grid_constants.h"
#include "core/components_ng/pattern/grid/grid_event_hub.h"
#include "core/components_ng/pattern/grid/grid_layout_options.h"
#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"
#include "core/components_ng/pattern/scrollable/scrollable_controller.h"
#include "core/components_ng/pattern/scrollable/selectable_container_pattern.h"
#include "core/components_v2/grid/grid_event.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
constexpr int32_t CALL_ARG_0 = 0;
constexpr int32_t CALL_ARG_1 = 1;
constexpr int32_t CALL_ARG_2 = 2;
constexpr int32_t CALL_ARG_3 = 3;
constexpr int32_t DEFAULT_CACHED_COUNT = 1;
constexpr int32_t BREAKPOINT_DEFAULT = 0;
constexpr int32_t BREAKPOINT_SM2MD3LG5 = 2;
constexpr size_t GRID_ITEM_SIZE_RESULT_LENGTH = 2;
constexpr size_t GRID_ITEM_RECT_RESULT_LENGTH = 4;
constexpr size_t GRID_START_LINE_INFO_RESULT_LENGTH = 4;
const std::vector<DisplayMode> DISPLAY_MODE = { DisplayMode::OFF, DisplayMode::AUTO, DisplayMode::ON };
const std::vector<FlexDirection> LAYOUT_DIRECTION = { FlexDirection::ROW, FlexDirection::COLUMN,
    FlexDirection::ROW_REVERSE, FlexDirection::COLUMN_REVERSE };

namespace {

void ParseGridStartLineInfo(const EcmaVM* vm, const Local<JSValueRef>& value, GridStartLineInfo& gridStartLineInfo)
{
    if (!value->IsArray(vm)) {
        return;
    }
    auto array = Local<panda::ArrayRef>(value);
    if (array->Length(vm) != GRID_START_LINE_INFO_RESULT_LENGTH) {
        return;
    }
    auto startIndex = panda::ArrayRef::GetValueAt(vm, array, CALL_ARG_0);
    if (startIndex->IsNumber()) {
        gridStartLineInfo.startIndex = startIndex->Int32Value(vm);
    }
    auto startLine = panda::ArrayRef::GetValueAt(vm, array, CALL_ARG_1);
    if (startLine->IsNumber()) {
        gridStartLineInfo.startLine = startLine->Int32Value(vm);
    }
    auto startOffset = panda::ArrayRef::GetValueAt(vm, array, CALL_ARG_2);
    if (startOffset->IsNumber()) {
        gridStartLineInfo.startOffset = startOffset->ToNumber(vm)->Value();
    }
    auto totalOffset = panda::ArrayRef::GetValueAt(vm, array, CALL_ARG_3);
    if (totalOffset->IsNumber()) {
        gridStartLineInfo.totalOffset = totalOffset->ToNumber(vm)->Value();
    }
}

void ParseGridItemSize(const EcmaVM* vm, const Local<JSValueRef>& value, GridItemSize& gridItemSize)
{
    if (!value->IsArray(vm)) {
        return;
    }
    auto array = Local<panda::ArrayRef>(value);
    uint32_t length = ArkTSUtils::GetArrayLength(vm, array);
    if (length != GRID_ITEM_SIZE_RESULT_LENGTH) {
        return;
    }
    auto rows = panda::ArrayRef::GetValueAt(vm, array, CALL_ARG_0);
    if (!rows.IsEmpty() && rows->IsNumber()) {
        gridItemSize.rows = rows->Int32Value(vm);
    }
    auto columns = panda::ArrayRef::GetValueAt(vm, array, CALL_ARG_1);
    if (!columns.IsEmpty() && columns->IsNumber()) {
        gridItemSize.columns = columns->Int32Value(vm);
    }
}

void ParseGridItemRect(const EcmaVM* vm, const Local<JSValueRef>& value, GridItemRect& gridItemRect)
{
    if (!value->IsArray(vm)) {
        return;
    }
    auto array = Local<panda::ArrayRef>(value);
    if (array->Length(vm) != GRID_ITEM_RECT_RESULT_LENGTH) {
        return;
    }
    auto rowStart = panda::ArrayRef::GetValueAt(vm, array, GridItemRect::ROW_START);
    if (!rowStart.IsEmpty() && rowStart->IsNumber()) {
        gridItemRect.rowStart = rowStart->Int32Value(vm);
    }
    auto rowSpan = panda::ArrayRef::GetValueAt(vm, array, GridItemRect::ROW_SPAN);
    if (!rowSpan.IsEmpty() && rowSpan->IsNumber()) {
        gridItemRect.rowSpan = rowSpan->Int32Value(vm);
    }
    auto columnStart = panda::ArrayRef::GetValueAt(vm, array, GridItemRect::COLUMN_START);
    if (!columnStart.IsEmpty() && columnStart->IsNumber()) {
        gridItemRect.columnStart = columnStart->Int32Value(vm);
    }
    auto columnSpan = panda::ArrayRef::GetValueAt(vm, array, GridItemRect::COLUMN_SPAN);
    if (!columnSpan.IsEmpty() && columnSpan->IsNumber()) {
        gridItemRect.columnSpan = columnSpan->Int32Value(vm);
    }
}

void ParseGetGridItemSize(
    const EcmaVM* vm, const Local<JSValueRef>& getSizeByIndex, GridLayoutOptions& option, bool isJSView = false)
{
    if (!getSizeByIndex->IsFunction(vm)) {
        return;
    }
    Local<panda::FunctionRef> functionRef = getSizeByIndex->ToObject(vm);
    auto onGetIrregularSizeByIndex = [func = panda::CopyableGlobal(vm, functionRef), isJSView](int32_t index) {
        auto vm = func.GetEcmaVM();
        panda::LocalScope scope(vm);
        panda::TryCatch trycatch(vm);
        GridItemSize gridItemSize;
        auto itemIndex = ArkTSUtils::ToJsValueWithVM(vm, index);
        auto result = func->Call(vm, func.ToLocal(), &itemIndex, 1);
        if (isJSView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
        if (!result->IsArray(vm)) {
            return gridItemSize;
        }
        ParseGridItemSize(vm, result, gridItemSize);
        return gridItemSize;
    };
    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
}

void ParseGetGridItemRect(
    const EcmaVM* vm, const Local<JSValueRef>& getRectByIndex, GridLayoutOptions& option, bool isJSView = false)
{
    if (!getRectByIndex->IsFunction(vm)) {
        return;
    }
    Local<panda::FunctionRef> functionRef = getRectByIndex->ToObject(vm);
    auto onGetRectByIndex = [func = panda::CopyableGlobal(vm, functionRef), isJSView](int32_t index) {
        auto vm = func.GetEcmaVM();
        panda::LocalScope scope(vm);
        panda::TryCatch trycatch(vm);
        GridItemRect gridItemRect;
        auto itemIndex = ArkTSUtils::ToJsValueWithVM(vm, index);
        auto result = func->Call(vm, func.ToLocal(), &itemIndex, 1);
        if (isJSView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
        if (!result->IsArray(vm)) {
            return gridItemRect;
        }
        ParseGridItemRect(vm, result, gridItemRect);
        return gridItemRect;
    };
    option.getRectByIndex = std::move(onGetRectByIndex);
}

void ParseGetStartIndexByOffset(
    const EcmaVM* vm, const Local<JSValueRef>& getStartIndexByOffset, GridLayoutOptions& option, bool isJSView = false)
{
    if (!getStartIndexByOffset->IsFunction(vm)) {
        return;
    }
    if (getStartIndexByOffset->IsFunction(vm)) {
        Local<panda::FunctionRef> functionRef = getStartIndexByOffset->ToObject(vm);
        auto onGetStartIndexByOffset = [func = panda::CopyableGlobal(vm, functionRef), isJSView](float offset) {
            auto vm = func.GetEcmaVM();
            panda::LocalScope scope(vm);
            panda::TryCatch trycatch(vm);
            GridStartLineInfo gridStartLineInfo;
            auto offsetValue = ArkTSUtils::ToJsValueWithVM(vm, offset);
            auto result = func->Call(vm, func.ToLocal(), &offsetValue, 1);
            if (isJSView) {
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            }
            if (!result->IsArray(vm)) {
                return gridStartLineInfo;
            }
            ParseGridStartLineInfo(vm, result, gridStartLineInfo);
            return gridStartLineInfo;
        };
        option.getStartIndexByOffset = std::move(onGetStartIndexByOffset);
    }
}

void ParseGetStartIndexByIndex(
    const EcmaVM* vm, const Local<JSValueRef>& getStartIndexByIndex, GridLayoutOptions& option, bool isJSView = false)
{
    if (!getStartIndexByIndex->IsFunction(vm)) {
        return;
    }
    Local<panda::FunctionRef> functionRef = getStartIndexByIndex->ToObject(vm);
    auto onGetStartIndexByIndex = [func = panda::CopyableGlobal(vm, functionRef), isJSView](int32_t index) {
        auto vm = func.GetEcmaVM();
        panda::LocalScope scope(vm);
        panda::TryCatch trycatch(vm);
        GridStartLineInfo gridStartLineInfo;
        auto itemIndex = ArkTSUtils::ToJsValueWithVM(vm, index);
        auto result = func->Call(vm, func.ToLocal(), &itemIndex, 1);
        if (isJSView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
        if (!result->IsArray(vm)) {
            return gridStartLineInfo;
        }
        ParseGridStartLineInfo(vm, result, gridStartLineInfo);
        return gridStartLineInfo;
    };
    option.getStartIndexByIndex = std::move(onGetStartIndexByIndex);
}

void ParsePreviewBadge(const EcmaVM* vm, const Local<JSValueRef>& result, PreviewBadge& badge)
{
    if (result.IsEmpty()) {
        return;
    }
    if (result->IsNumber()) {
        int64_t number = result->IntegerValue(vm);
        if (number < 0 || number > INT_MAX) {
            badge.mode = PreviewBadgeMode::AUTO;
        } else {
            badge.mode = PreviewBadgeMode::USER_SET;
            badge.count = result->Int32Value(vm);
        }
    } else if (result->IsBoolean()) {
        badge.mode = result->ToBoolean(vm)->Value() ? PreviewBadgeMode::AUTO : PreviewBadgeMode::NO_BADGE;
    }
}

void SetJSGridLayoutOptions(const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    Local<JSValueRef> infoArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    if (runtimeCallInfo->GetArgsNumber() <= 1 || infoArg.IsEmpty() || !infoArg->IsObject(vm)) {
        return;
    }
    GridLayoutOptions option;
    Local<panda::ObjectRef> obj = infoArg->ToObject(vm);
    Local<JSValueRef> value = ArkTSUtils::GetProperty(vm, obj, "regularSize");
    ParseGridItemSize(vm, value, option.regularSize);

    // only support regularSize(1, 1)
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;

    auto indexes = ArkTSUtils::GetProperty(vm, obj, "irregularIndexes");
    if (!indexes.IsEmpty() && indexes->IsArray(vm)) {
        Local<panda::ArrayRef> array = indexes;
        uint32_t length = ArkTSUtils::GetArrayLength(vm, array);
        for (size_t i = 0; i < length; i++) {
            auto index = panda::ArrayRef::GetValueAt(vm, array, i);
            if (index.IsEmpty() || !index->IsNumber()) {
                continue;
            }
            auto indexNum = index->Int32Value(vm);
            if (indexNum >= 0) {
                option.irregularIndexes.emplace(indexNum);
            }
        }
    }

    ParseGetGridItemSize(vm, ArkTSUtils::GetProperty(vm, obj, "onGetIrregularSizeByIndex"), option, true);
    ParseGetGridItemRect(vm, ArkTSUtils::GetProperty(vm, obj, "onGetRectByIndex"), option, true);
    ParseGetStartIndexByOffset(vm, ArkTSUtils::GetProperty(vm, obj, "onGetStartIndexByOffset"), option, true);
    ParseGetStartIndexByIndex(vm, ArkTSUtils::GetProperty(vm, obj, "onGetStartIndexByIndex"), option, true);

    GetArkUINodeModifiers()->getGridModifier()->setLayoutOptions(nullptr, &option);
}

std::string ParseBarWidth(const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, RefPtr<ResourceObject>& resObj)
{
    if (runtimeCallInfo->GetArgsNumber() < 2) { // 2: param count
        return "";
    }
    Local<JSValueRef> scrollBarWidthArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);

    CalcDimension scrollBarWidth;
    if (scrollBarWidthArg.IsEmpty()) {
        return "";
    }
    bool parsed = false;
    if (scrollBarWidthArg->IsString(vm) || scrollBarWidthArg->IsNumber()) {
        parsed = ArkTSUtils::ParseJsDimensionVp(vm, scrollBarWidthArg, scrollBarWidth, resObj, false);
    } else if (scrollBarWidthArg->IsObject(vm)) {
        parsed = ArkTSUtils::ParseJsDimensionVpNG(vm, scrollBarWidthArg, scrollBarWidth, resObj);
    }

    if (scrollBarWidthArg->IsUndefined() || scrollBarWidthArg->IsNull() ||
        (scrollBarWidthArg->IsString(vm) && scrollBarWidthArg->ToString(vm)->ToString(vm).empty()) || !parsed ||
        LessNotEqual(scrollBarWidth.Value(), 0.0) || scrollBarWidth.Unit() == DimensionUnit::PERCENT) {
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, "");
        auto theme = pipelineContext->GetTheme<ScrollBarTheme>();
        CHECK_NULL_RETURN(theme, "");
        scrollBarWidth = theme->GetNormalWidth();
    }
    return scrollBarWidth.ToString();
}

EdgeEffect ParseEdgeEffect(const EcmaVM* vm, const Local<JSValueRef>& jsValue, EdgeEffect defaultValue)
{
    auto edgeEffect = static_cast<int32_t>(defaultValue);
    CHECK_EQUAL_RETURN(jsValue.IsEmpty(), true, defaultValue);
    if (jsValue->IsNull() || jsValue->IsUndefined() || !ArkTSUtils::ParseJsInt32(vm, jsValue, edgeEffect) ||
        edgeEffect < static_cast<int32_t>(EdgeEffect::SPRING) || edgeEffect > static_cast<int32_t>(EdgeEffect::NONE)) {
        edgeEffect = static_cast<int32_t>(defaultValue);
    }
    return static_cast<EdgeEffect>(edgeEffect);
}

bool ParseAlwaysEnable(const EcmaVM* vm, const Local<JSValueRef>& jsValue, bool defaultValue)
{
    auto alwaysEnabled = defaultValue;
    CHECK_EQUAL_RETURN(jsValue.IsEmpty(), true, alwaysEnabled);
    if ((!(jsValue->IsNull() || jsValue->IsUndefined())) && jsValue->IsObject(vm)) {
        auto paramObject = jsValue->ToObject(vm);
        Local<JSValueRef> alwaysEnabledParam = ArkTSUtils::GetProperty(vm, paramObject, "alwaysEnabled");
        alwaysEnabled = alwaysEnabledParam->IsBoolean() ? alwaysEnabledParam->BooleaValue(vm) : defaultValue;
    }
    return alwaysEnabled;
}

EffectEdge ParseEffectEdge(const EcmaVM* vm, const Local<JSValueRef>& jsValue)
{
    auto effectEdge = static_cast<int32_t>(EffectEdge::ALL);
    CHECK_EQUAL_RETURN(jsValue.IsEmpty(), true, EffectEdge::ALL);
    if (jsValue->IsObject(vm)) {
        auto paramObject = jsValue->ToObject(vm);
        Local<JSValueRef> effectEdgedParam = ArkTSUtils::GetProperty(vm, paramObject, "effectEdge");
        if (effectEdgedParam->IsNull() || effectEdgedParam->IsUndefined() ||
            !ArkTSUtils::ParseJsInt32(vm, effectEdgedParam, effectEdge) ||
            effectEdge < static_cast<int32_t>(EffectEdge::START) ||
            effectEdge > static_cast<int32_t>(EffectEdge::END)) {
            effectEdge = static_cast<int32_t>(EffectEdge::ALL);
        }
    }
    return static_cast<EffectEdge>(effectEdge);
}
} // namespace

ArkUINativeModuleValue GridBridge::CreateGrid(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));

    RefPtr<ScrollControllerBase> positionController;
    RefPtr<ScrollProxy> scrollBarProxy;
    Local<JSValueRef> scrollerArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);

    if (runtimeCallInfo->GetArgsNumber() > 0 && !scrollerArg.IsEmpty() && scrollerArg->IsObject(vm)) {
        Local<ObjectRef> scrollerObj = scrollerArg->ToObject(vm);
        JSScroller* jsScroller = static_cast<JSScroller*>(scrollerObj->GetNativePointerField(vm, 0));
        if (jsScroller) {
            jsScroller->SetInstanceId(Container::CurrentId());
            auto tmp = AceType::Claim(reinterpret_cast<ScrollControllerBase*>(
                GetArkUINodeModifiers()->getGridModifier()->createPositionController()));
            tmp->DecRefCount();
            positionController = tmp;
            jsScroller->SetController(positionController);

            // Init scroll bar proxy.
            scrollBarProxy = jsScroller->GetScrollBarProxy();
            if (!scrollBarProxy) {
                auto proxyTmp = AceType::Claim(
                    reinterpret_cast<ScrollProxy*>(GetArkUINodeModifiers()->getGridModifier()->createScrollBarProxy()));
                proxyTmp->DecRefCount();
                scrollBarProxy = proxyTmp;
                jsScroller->SetScrollBarProxy(scrollBarProxy);
            }
        }
    }
    GetArkUINodeModifiers()->getGridModifier()->create(positionController.GetRawPtr(), scrollBarProxy.GetRawPtr());

    SetJSGridLayoutOptions(vm, runtimeCallInfo);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::PopGrid(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    GetArkUINodeModifiers()->getGridModifier()->popGrid();
    return panda::JSValueRef::Undefined(vm);
}

void GridBridge::RegisterGridAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = {
        "create",
        "pop",
        "setColumnsTemplate",
        "resetColumnsTemplate",
        "setRowsTemplate",
        "resetRowsTemplate",
        "setColumnsGap",
        "resetColumnsGap",
        "setRowsGap",
        "resetRowsGap",
        "setScrollBar",
        "resetScrollBar",
        "setScrollBarWidth",
        "resetScrollBarWidth",
        "setScrollBarColor",
        "resetScrollBarColor",
        "setCachedCount",
        "resetCachedCount",
        "setEditMode",
        "resetEditMode",
        "setMultiSelectable",
        "resetMultiSelectable",
        "setMaxCount",
        "resetMaxCount",
        "setMinCount",
        "resetMinCount",
        "setCellLength",
        "resetCellLength",
        "setLayoutDirection",
        "resetLayoutDirection",
        "setDragAnimation",
        "setEdgeEffect",
        "setDirection",
        "setSupportAnimation",
        "resetSupportAnimation",
        "setHeight",
        "setNestedScroll",
        "resetNestedScroll",
        "setEnableScroll",
        "resetEnableScroll",
        "setFriction",
        "resetFriction",
        "setFocusWrapMode",
        "resetFocusWrapMode",
        "setAlignItems",
        "resetAlignItems",
        "setSyncLoad",
        "resetSyncLoad",
        "setEditModeOptions",
        "resetEditModeOptions",
        "setGridEnableEditMode",
        "resetGridEnableEditMode",
        "setOnEditModeChange",
        "resetOnEditModeChange",
        "setGridScroller",
        "setGridLayoutOptions",
        "setOnScrollIndex",
        "resetOnScrollIndex",
        "setOnScrollBarUpdate",
        "resetOnScrollBarUpdate",
        "setOnItemDragStart",
        "resetOnItemDragStart",
        "setOnItemDragEnter",
        "resetOnItemDragEnter",
        "setOnItemDragMove",
        "resetOnItemDragMove",
        "setOnItemDragLeave",
        "resetOnItemDragLeave",
        "setOnItemDrop",
        "resetOnItemDrop",
        "setSupportLazyLoadingEmptyBranch",
        "setOnScroll",
        "setOnReachStart",
        "setOnReachEnd",
        "setOnScrollStart",
        "setOnScrollStop",
        "setOnScrollFrameBegin",
        "willUseProxy",
        "setJSScrollBar",
        "setJSScrollBarWidth",
        "setJSEnableEditMode",
    };
    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(vm, GridBridge::CreateGrid),
        panda::FunctionRef::New(vm, GridBridge::PopGrid),
        panda::FunctionRef::New(vm, GridBridge::SetColumnsTemplate),
        panda::FunctionRef::New(vm, GridBridge::ResetColumnsTemplate),
        panda::FunctionRef::New(vm, GridBridge::SetRowsTemplate),
        panda::FunctionRef::New(vm, GridBridge::ResetRowsTemplate),
        panda::FunctionRef::New(vm, GridBridge::SetColumnsGap),
        panda::FunctionRef::New(vm, GridBridge::ResetColumnsGap),
        panda::FunctionRef::New(vm, GridBridge::SetRowsGap),
        panda::FunctionRef::New(vm, GridBridge::ResetRowsGap),
        panda::FunctionRef::New(vm, GridBridge::SetScrollBar),
        panda::FunctionRef::New(vm, GridBridge::ResetScrollBar),
        panda::FunctionRef::New(vm, GridBridge::SetScrollBarWidth),
        panda::FunctionRef::New(vm, GridBridge::ResetScrollBarWidth),
        panda::FunctionRef::New(vm, GridBridge::SetScrollBarColor),
        panda::FunctionRef::New(vm, GridBridge::ResetScrollBarColor),
        panda::FunctionRef::New(vm, GridBridge::SetCachedCount),
        panda::FunctionRef::New(vm, GridBridge::ResetCachedCount),
        panda::FunctionRef::New(vm, GridBridge::SetEditMode),
        panda::FunctionRef::New(vm, GridBridge::ResetEditMode),
        panda::FunctionRef::New(vm, GridBridge::SetMultiSelectable),
        panda::FunctionRef::New(vm, GridBridge::ResetMultiSelectable),
        panda::FunctionRef::New(vm, GridBridge::SetMaxCount),
        panda::FunctionRef::New(vm, GridBridge::ResetMaxCount),
        panda::FunctionRef::New(vm, GridBridge::SetMinCount),
        panda::FunctionRef::New(vm, GridBridge::ResetMinCount),
        panda::FunctionRef::New(vm, GridBridge::SetCellLength),
        panda::FunctionRef::New(vm, GridBridge::ResetCellLength),
        panda::FunctionRef::New(vm, GridBridge::SetLayoutDirection),
        panda::FunctionRef::New(vm, GridBridge::ResetLayoutDirection),
        panda::FunctionRef::New(vm, GridBridge::SetDragAnimation),
        panda::FunctionRef::New(vm, GridBridge::SetEdgeEffect),
        panda::FunctionRef::New(vm, GridBridge::SetDirection),
        panda::FunctionRef::New(vm, GridBridge::SetSupportAnimation),
        panda::FunctionRef::New(vm, GridBridge::ResetSupportAnimation),
        panda::FunctionRef::New(vm, GridBridge::SetHeight),
        panda::FunctionRef::New(vm, GridBridge::SetNestedScroll),
        panda::FunctionRef::New(vm, GridBridge::ResetNestedScroll),
        panda::FunctionRef::New(vm, GridBridge::SetEnableScroll),
        panda::FunctionRef::New(vm, GridBridge::ResetEnableScroll),
        panda::FunctionRef::New(vm, GridBridge::SetFriction),
        panda::FunctionRef::New(vm, GridBridge::ResetFriction),
        panda::FunctionRef::New(vm, GridBridge::SetFocusWrapMode),
        panda::FunctionRef::New(vm, GridBridge::ResetFocusWrapMode),
        panda::FunctionRef::New(vm, GridBridge::SetAlignItems),
        panda::FunctionRef::New(vm, GridBridge::ResetAlignItems),
        panda::FunctionRef::New(vm, GridBridge::SetSyncLoad),
        panda::FunctionRef::New(vm, GridBridge::ResetSyncLoad),
        panda::FunctionRef::New(vm, GridBridge::SetEditModeOptions),
        panda::FunctionRef::New(vm, GridBridge::ResetEditModeOptions),
        panda::FunctionRef::New(vm, GridBridge::SetEnableEditMode),
        panda::FunctionRef::New(vm, GridBridge::ResetEnableEditMode),
        panda::FunctionRef::New(vm, GridBridge::SetOnEditModeChange),
        panda::FunctionRef::New(vm, GridBridge::ResetOnEditModeChange),
        panda::FunctionRef::New(vm, GridBridge::SetGridScroller),
        panda::FunctionRef::New(vm, GridBridge::SetGridLayoutOptions),
        panda::FunctionRef::New(vm, GridBridge::SetOnGridScrollIndex),
        panda::FunctionRef::New(vm, GridBridge::ResetOnGridScrollIndex),
        panda::FunctionRef::New(vm, GridBridge::SetOnGridScrollBarUpdate),
        panda::FunctionRef::New(vm, GridBridge::ResetOnGridScrollBarUpdate),
        panda::FunctionRef::New(vm, GridBridge::SetOnGridItemDragStart),
        panda::FunctionRef::New(vm, GridBridge::ResetOnGridItemDragStart),
        panda::FunctionRef::New(vm, GridBridge::SetOnGridItemDragEnter),
        panda::FunctionRef::New(vm, GridBridge::ResetOnGridItemDragEnter),
        panda::FunctionRef::New(vm, GridBridge::SetOnGridItemDragMove),
        panda::FunctionRef::New(vm, GridBridge::ResetOnGridItemDragMove),
        panda::FunctionRef::New(vm, GridBridge::SetOnGridItemDragLeave),
        panda::FunctionRef::New(vm, GridBridge::ResetOnGridItemDragLeave),
        panda::FunctionRef::New(vm, GridBridge::SetOnGridItemDrop),
        panda::FunctionRef::New(vm, GridBridge::ResetOnGridItemDrop),
        panda::FunctionRef::New(vm, GridBridge::SetSupportLazyLoadingEmptyBranch),
        panda::FunctionRef::New(vm, GridBridge::SetOnScroll),
        panda::FunctionRef::New(vm, GridBridge::SetOnReachStart),
        panda::FunctionRef::New(vm, GridBridge::SetOnReachEnd),
        panda::FunctionRef::New(vm, GridBridge::SetOnScrollStart),
        panda::FunctionRef::New(vm, GridBridge::SetOnScrollStop),
        panda::FunctionRef::New(vm, GridBridge::SetOnScrollFrameBegin),
        panda::FunctionRef::New(vm, GridBridge::WillUseProxy),
        panda::FunctionRef::New(vm, GridBridge::SetJSScrollBar),
        panda::FunctionRef::New(vm, GridBridge::SetJSScrollBarWidth),
        panda::FunctionRef::New(vm, GridBridge::SetJSEnableEditMode),
    };
    auto grid = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "grid"), grid);
}

ArkUINativeModuleValue GridBridge::SetColumnsTemplate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_columnsTemplate = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, node, vm), false, panda::JSValueRef::Undefined(vm));
    if (arg_columnsTemplate->IsObject(vm)) {
        auto value = BREAKPOINT_DEFAULT;
        GetArkUINodeModifiers()->getGridModifier()->resetGridColumnsTemplate(nativeNode);
        GetArkUINodeModifiers()->getGridModifier()->setItemFillPolicy(nativeNode, value);
        auto fillTypeArg = ArkTSUtils::GetProperty(vm, arg_columnsTemplate, "fillType");
        if (!fillTypeArg.IsEmpty() && !fillTypeArg->IsNull() && ArkTSUtils::ParseJsInt32(vm, fillTypeArg, value)) {
            if (InRegion(BREAKPOINT_DEFAULT, BREAKPOINT_SM2MD3LG5, value)) {
                GetArkUINodeModifiers()->getGridModifier()->setItemFillPolicy(nativeNode, value);
            }
        }
    } else if (!ArkTSUtils::IsJsView(vm, node) &&
               (arg_columnsTemplate->IsUndefined() || !arg_columnsTemplate->IsString(vm))) {
        GetArkUINodeModifiers()->getGridModifier()->resetGridColumnsTemplate(nativeNode);
    } else {
        std::string columnsTemplate = arg_columnsTemplate->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getGridModifier()->setGridColumnsTemplate(nativeNode, columnsTemplate.c_str());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetColumnsTemplate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetGridColumnsTemplate(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetRowsTemplate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_rowsTemplate = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, node, vm), false, panda::JSValueRef::Undefined(vm));
    bool isJSView = ArkTSUtils::IsJsView(vm, node);
    if (!isJSView && (arg_rowsTemplate->IsUndefined() || !arg_rowsTemplate->IsString(vm))) {
        GetArkUINodeModifiers()->getGridModifier()->resetGridRowsTemplate(nativeNode);
    } else {
        std::string rowsTemplate = arg_rowsTemplate->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getGridModifier()->setGridRowsTemplate(nativeNode, rowsTemplate.c_str());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetRowsTemplate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetGridRowsTemplate(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetColumnsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_size = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, node, vm), false, panda::JSValueRef::Undefined(vm));

    CalcDimension size;
    std::string calcStr;
    RefPtr<ResourceObject> columnGapResObj;
    struct ArkUIResourceLength columnGap = { 0.0, 0, nullptr };
    bool parseResult = ArkTSUtils::ParseJsDimensionVpNG(vm, arg_size, size, columnGapResObj, true);
    bool isJSView = ArkTSUtils::IsJsView(vm, node);
    if (!isJSView && (arg_size->IsUndefined() || !parseResult)) {
        GetArkUINodeModifiers()->getGridModifier()->resetGridColumnsGap(nativeNode);
    } else {
        auto columnGapRawPtr = AceType::RawPtr(columnGapResObj);
        if (size.Unit() == DimensionUnit::CALC) {
            columnGap.unit = static_cast<int32_t>(DimensionUnit::CALC);
            calcStr = size.CalcValue();
            columnGap.string = calcStr.c_str();
        } else {
            columnGap.value = size.Value();
            columnGap.unit = static_cast<int32_t>(size.Unit());
            columnGap.string = calcStr.c_str();
        }
        if (isJSView) {
            GetArkUINodeModifiers()->getGridModifier()->setGridColumnsGapByJs(nativeNode, &columnGap, columnGapRawPtr);
        } else {
            GetArkUINodeModifiers()->getGridModifier()->setGridColumnsGap(nativeNode, &columnGap, columnGapRawPtr);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetColumnsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetGridColumnsGap(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetRowsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_size = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, node, vm), false, panda::JSValueRef::Undefined(vm));

    CalcDimension size;
    std::string calcStr;
    RefPtr<ResourceObject> rowGapResObj;
    struct ArkUIResourceLength rowsGap = { 0.0, 0, nullptr };
    bool parseResult = ArkTSUtils::ParseJsDimensionVpNG(vm, arg_size, size, rowGapResObj, true);
    bool isJSView = ArkTSUtils::IsJsView(vm, node);
    if (!isJSView && (arg_size->IsUndefined() || !parseResult)) {
        GetArkUINodeModifiers()->getGridModifier()->resetGridRowsGap(nativeNode);
    } else {
        auto rowGapRawPtr = AceType::RawPtr(rowGapResObj);
        if (size.Unit() == DimensionUnit::CALC) {
            rowsGap.unit = static_cast<int32_t>(DimensionUnit::CALC);
            calcStr = size.CalcValue();
            rowsGap.string = calcStr.c_str();
        } else {
            rowsGap.value = size.Value();
            rowsGap.unit = static_cast<int32_t>(size.Unit());
            rowsGap.string = calcStr.c_str();
        }
        if (isJSView) {
            GetArkUINodeModifiers()->getGridModifier()->setGridRowsGapByJs(nativeNode, &rowsGap, rowGapRawPtr);
        } else {
            GetArkUINodeModifiers()->getGridModifier()->setGridRowsGap(nativeNode, &rowsGap, rowGapRawPtr);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetRowsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetGridRowsGap(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetScrollBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_scrollBar = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    if (!arg_scrollBar->IsNull() && arg_scrollBar->IsNumber()) {
        int32_t scrollBar = arg_scrollBar->Int32Value(vm);
        if (scrollBar < 0) {
            GetArkUINodeModifiers()->getGridModifier()->resetGridScrollBar(nativeNode);
        } else {
            GetArkUINodeModifiers()->getGridModifier()->setGridScrollBar(nativeNode, scrollBar);
        }
    } else {
        GetArkUINodeModifiers()->getGridModifier()->resetGridScrollBar(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetScrollBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetGridScrollBar(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetScrollBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> scrollBarArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());

    CalcDimension scrollBarWidth;
    RefPtr<ResourceObject> resObj;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, scrollBarArg, scrollBarWidth, resObj, false)) {
        GetArkUINodeModifiers()->getGridModifier()->resetGridScrollBarWidth(nativeNode);
    } else {
        if (LessNotEqual(scrollBarWidth.Value(), 0.0f)) {
            GetArkUINodeModifiers()->getGridModifier()->resetGridScrollBarWidth(nativeNode);
        } else {
            GetArkUINodeModifiers()->getGridModifier()->setGridScrollBarWidth(
                nativeNode, scrollBarWidth.Value(), static_cast<int32_t>(scrollBarWidth.Unit()));
        }
    }
    GetArkUINodeModifiers()->getGridModifier()->setGridScrollBarWidthResObj(nativeNode, resObj.GetRawPtr());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetScrollBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetGridScrollBarWidth(nativeNode);
    GetArkUINodeModifiers()->getGridModifier()->setGridScrollBarWidthResObj(nativeNode, nullptr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetScrollBarColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_color = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, node, vm), false, panda::JSValueRef::Undefined(vm));
    bool isJSView = ArkTSUtils::IsJsView(vm, node);
    if (!isJSView && (arg_color->IsNull() || arg_color->IsUndefined())) {
        GetArkUINodeModifiers()->getGridModifier()->resetGridScrollBarColor(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (!isJSView && arg_color->IsNumber()) {
        auto colorNum = arg_color->ToNumber(vm)->Value();
        if (colorNum <= 0) {
            GetArkUINodeModifiers()->getGridModifier()->resetGridScrollBarColor(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }
    }
    Color color;
    RefPtr<ResourceObject> resObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (ArkTSUtils::ParseJsColorAlpha(vm, arg_color, color, resObj, nodeInfo)) {
        GetArkUINodeModifiers()->getGridModifier()->setGridScrollBarColor(
            nativeNode, color.GetValue());
    } else {
        GetArkUINodeModifiers()->getGridModifier()->resetGridScrollBarColor(nativeNode);
    }
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getGridModifier()->createWithResourceObjScrollBarColor(
            nativeNode, reinterpret_cast<void*>(AceType::RawPtr(resObj)));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetScrollBarColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetGridScrollBarColor(nativeNode);
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getGridModifier()->createWithResourceObjScrollBarColor(nativeNode, nullptr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetCachedCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> argCachedCount = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    Local<JSValueRef> argShow = runtimeCallInfo->GetCallArgRef(CALL_ARG_2);
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, node, vm), false, panda::JSValueRef::Undefined(vm));
    auto value = DEFAULT_CACHED_COUNT;
    if (!argCachedCount->IsUndefined()) {
        ArkTSUtils::ParseJsInteger(vm, argCachedCount, value);
        if (value < 0) {
            value = DEFAULT_CACHED_COUNT;
        }
    }
    GetArkUINodeModifiers()->getGridModifier()->setGridCachedCount(nativeNode, value);

    bool show = !argShow.IsNull() && argShow->IsTrue();
    GetArkUINodeModifiers()->getGridModifier()->setShowCached(nativeNode, show);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetCachedCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetGridCachedCount(nativeNode);
    GetArkUINodeModifiers()->getGridModifier()->resetShowCached(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetEditMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_editMode = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, node, vm), false, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(vm, node) && !arg_editMode.IsEmpty() && !arg_editMode->IsUndefined() &&
        arg_editMode->IsBoolean()) {
        bool mode = arg_editMode->BooleaValue(vm);
        GetArkUINodeModifiers()->getGridModifier()->setGridEditMode(nativeNode, mode);
        return panda::JSValueRef::Undefined(vm);
    }
    bool editMode = arg_editMode->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getGridModifier()->setGridEditMode(nativeNode, editMode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetEditMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetGridEditMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetMultiSelectable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_multiSelectable = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, node, vm), false, panda::JSValueRef::Undefined(vm));
    bool multiSelectable = ArkTSUtils::IsJsView(vm, node) ? arg_multiSelectable->Uint32Value(vm)
                                                          : arg_multiSelectable->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getGridModifier()->setGridMultiSelectable(nativeNode, multiSelectable);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetMultiSelectable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetGridMultiSelectable(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetMaxCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_maxCount = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, node, vm), false, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(vm, node)) {
        int32_t maxCount = Infinity<int32_t>();
        if (!arg_maxCount.IsEmpty() && !arg_maxCount->IsUndefined() && arg_maxCount->IsNumber()) {
            ArkTSUtils::ParseJsInt32(vm, arg_maxCount, maxCount);
            if (maxCount < 1) {
                maxCount = Infinity<int32_t>();
            }
        }
        GetArkUINodeModifiers()->getGridModifier()->setGridMaxCount(nativeNode, maxCount);
        return panda::JSValueRef::Undefined(vm);
    }
    if (!arg_maxCount->IsNull() && arg_maxCount->IsNumber()) {
        int32_t maxCount = arg_maxCount->Int32Value(vm);
        if (maxCount < 1) {
            GetArkUINodeModifiers()->getGridModifier()->resetGridMaxCount(nativeNode);
        } else {
            GetArkUINodeModifiers()->getGridModifier()->setGridMaxCount(nativeNode, maxCount);
        }
    } else {
        GetArkUINodeModifiers()->getGridModifier()->resetGridMaxCount(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetMaxCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetGridMaxCount(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetMinCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_minCount = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, node, vm), false, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(vm, node)) {
        int32_t minCount = 1;
        if (!arg_minCount.IsEmpty() && !arg_minCount->IsUndefined() && arg_minCount->IsNumber()) {
            ArkTSUtils::ParseJsInt32(vm, arg_minCount, minCount);
            if (minCount < 1) {
                minCount = 1;
            }
        }
        GetArkUINodeModifiers()->getGridModifier()->setGridMinCount(nativeNode, minCount);
        return panda::JSValueRef::Undefined(vm);
    }
    if (!arg_minCount->IsNull() && arg_minCount->IsNumber()) {
        int32_t minCount = arg_minCount->Int32Value(vm);
        if (minCount < 1) {
            GetArkUINodeModifiers()->getGridModifier()->resetGridMinCount(nativeNode);
        } else {
            GetArkUINodeModifiers()->getGridModifier()->setGridMinCount(nativeNode, minCount);
        }
    } else {
        GetArkUINodeModifiers()->getGridModifier()->resetGridMinCount(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetMinCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetGridMinCount(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetCellLength(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_cellLength = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, node, vm), false, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(vm, node)) {
        int32_t cellLength = arg_cellLength->Int32Value(vm);
        GetArkUINodeModifiers()->getGridModifier()->setGridCellLength(nativeNode, cellLength);
        return panda::JSValueRef::Undefined(vm);
    }
    if (!arg_cellLength->IsNull() && arg_cellLength->IsNumber()) {
        int32_t cellLength = arg_cellLength->Int32Value(vm);
        GetArkUINodeModifiers()->getGridModifier()->setGridCellLength(nativeNode, cellLength);
    } else {
        GetArkUINodeModifiers()->getGridModifier()->resetGridCellLength(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetCellLength(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetGridCellLength(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetLayoutDirection(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_layoutDirection = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, node, vm), false, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(vm, node)) {
        int32_t layoutDirection = arg_layoutDirection->Int32Value(vm);
        if (layoutDirection < 0 || layoutDirection >= static_cast<int32_t>(LAYOUT_DIRECTION.size())) {
            return panda::JSValueRef::Undefined(vm);
        }
        GetArkUINodeModifiers()->getGridModifier()->setGridLayoutDirection(nativeNode, layoutDirection);
    }
    if (!arg_layoutDirection->IsNull() && arg_layoutDirection->IsNumber()) {
        int32_t layoutDirection = arg_layoutDirection->Int32Value(vm);
        GetArkUINodeModifiers()->getGridModifier()->setGridLayoutDirection(nativeNode, layoutDirection);
    } else {
        GetArkUINodeModifiers()->getGridModifier()->resetGridLayoutDirection(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetDragAnimation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    bool supportDragAnimation = valueArg->Uint32Value(vm);
    GetArkUINodeModifiers()->getGridModifier()->setSupportDragAnimation(nullptr, supportDragAnimation);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetEdgeEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> edgeEffectArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, node, vm), false, panda::JSValueRef::Undefined(vm));

    auto edgeEffect = EdgeEffect::NONE;
    auto effectEdge = EffectEdge::ALL;
    if (runtimeCallInfo->GetArgsNumber() > 1) {
        edgeEffect = ParseEdgeEffect(vm, edgeEffectArg, EdgeEffect::NONE);
    }
    auto alwaysEnabled = false;
    if (runtimeCallInfo->GetArgsNumber() > 2) { // 2: param count
        Local<JSValueRef> effectEdgeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_2);
        alwaysEnabled = ParseAlwaysEnable(vm, effectEdgeArg, false);
        effectEdge = ParseEffectEdge(vm, effectEdgeArg);
    }
    GetArkUINodeModifiers()->getGridModifier()->setEdgeEffect(
        nativeNode, static_cast<int32_t>(edgeEffect), alwaysEnabled, static_cast<int32_t>(effectEdge));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetDirection(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> directionArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, node, vm), false, panda::JSValueRef::Undefined(vm));
    TextDirection direction = TextDirection::AUTO;
    if (!directionArg.IsEmpty() && directionArg->IsString(vm)) {
        auto directionStr = directionArg->ToString(vm)->ToString(vm);
        if (directionStr == "Ltr") {
            direction = TextDirection::LTR;
        } else if (directionStr == "Rtl") {
            direction = TextDirection::RTL;
        }
    }
    GetArkUINodeModifiers()->getGridModifier()->setDirection(nativeNode, static_cast<int32_t>(direction));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetLayoutDirection(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetGridLayoutDirection(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetSupportAnimation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_supportAnimation = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, node, vm), false, panda::JSValueRef::Undefined(vm));
    bool supportAnimation = ArkTSUtils::IsJsView(vm, node) ? arg_supportAnimation->Uint32Value(vm)
                                                           : arg_supportAnimation->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getGridModifier()->setGridSupportAnimation(nativeNode, supportAnimation);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetSupportAnimation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetGridSupportAnimation(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    if (runtimeCallInfo->GetArgsNumber() < 2) { // 2: param count
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, node, vm), false, panda::JSValueRef::Undefined(vm));
    ArkTSUtils::SetJSHeight(valueArg);
    CalcDimension height;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, valueArg, height, false)) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (LessNotEqual(height.Value(), 0.0)) {
        height.SetValue(0.0);
    }
    GetArkUINodeModifiers()->getGridModifier()->setHeight(
        nativeNode, height.Value(), static_cast<int32_t>(height.Unit()), height.CalcValue().c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetNestedScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_forward = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    Local<JSValueRef> arg_backward = runtimeCallInfo->GetCallArgRef(CALL_ARG_2);

    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, node, vm), false, panda::JSValueRef::Undefined(vm));
    int32_t forward = static_cast<int32_t>(NestedScrollMode::SELF_ONLY);
    int32_t backward = static_cast<int32_t>(NestedScrollMode::SELF_ONLY);
    if (ArkTSUtils::IsJsView(vm, node)) {
        if (arg_forward->IsObject(vm)) {
            auto obj = arg_forward->ToObject(vm);
            ArkTSUtils::ParseJsInt32(vm, ArkTSUtils::GetProperty(vm, obj, "scrollForward"), forward);
            ArkTSUtils::ParseJsInt32(vm, ArkTSUtils::GetProperty(vm, obj, "scrollBackward"), backward);
        }
    } else {
        if (!arg_forward->IsUndefined()) {
            forward = arg_forward->Int32Value(vm);
        }
        if (!arg_backward->IsUndefined()) {
            backward = arg_backward->Int32Value(vm);
        }
    }

    if (forward < static_cast<int32_t>(NestedScrollMode::SELF_ONLY) ||
        forward > static_cast<int32_t>(NestedScrollMode::PARALLEL)) {
        forward = static_cast<int32_t>(NestedScrollMode::SELF_ONLY);
    }

    if (backward < static_cast<int32_t>(NestedScrollMode::SELF_ONLY) ||
        backward > static_cast<int32_t>(NestedScrollMode::PARALLEL)) {
        backward = static_cast<int32_t>(NestedScrollMode::SELF_ONLY);
    }

    GetArkUINodeModifiers()->getGridModifier()->setNestedScroll(nativeNode, forward, backward);

    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue GridBridge::ResetNestedScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetNestedScroll(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue GridBridge::SetEnableScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_enableScroll = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);

    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, node, vm), false, panda::JSValueRef::Undefined(vm));

    GetArkUINodeModifiers()->getGridModifier()->setEnableScroll(
        nativeNode, arg_enableScroll->IsBoolean() ? arg_enableScroll->ToBoolean(vm)->Value() : true);

    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue GridBridge::ResetEnableScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetEnableScroll(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue GridBridge::SetFriction(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_friction = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);

    double friction = -1.0;
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, node, vm), false, panda::JSValueRef::Undefined(vm));
    RefPtr<ResourceObject> resObj;
    if (!ArkTSUtils::ParseJsDouble(vm, arg_friction, friction, resObj)) {
        friction = -1.0;
    }
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getGridModifier()->createWithResourceObjFriction(
            nativeNode, reinterpret_cast<void*>(AceType::RawPtr(resObj)));
    }
    GetArkUINodeModifiers()->getGridModifier()->setFriction(nativeNode, static_cast<ArkUI_Float32>(friction));

    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue GridBridge::ResetFriction(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetFriction(nativeNode);
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getGridModifier()->createWithResourceObjFriction(nativeNode, nullptr);
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue GridBridge::SetFocusWrapMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_focusWrapMode = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, node, vm), false, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(vm, node)) {
        int32_t focusWrapMode = static_cast<int32_t>(FocusWrapMode::DEFAULT);
        if (!ArkTSUtils::ParseJsInt32(vm, arg_focusWrapMode, focusWrapMode) ||
            focusWrapMode < static_cast<int32_t>(FocusWrapMode::DEFAULT) ||
            focusWrapMode > static_cast<int32_t>(FocusWrapMode::WRAP_WITH_ARROW)) {
            focusWrapMode = static_cast<int32_t>(FocusWrapMode::DEFAULT);
        }
        GetArkUINodeModifiers()->getGridModifier()->setGridFocusWrapMode(nativeNode, focusWrapMode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (!arg_focusWrapMode->IsNull() && arg_focusWrapMode->IsNumber()) {
        int32_t focusWrapMode = arg_focusWrapMode->Int32Value(vm);
        if (focusWrapMode < 0 || focusWrapMode > 1) {
            GetArkUINodeModifiers()->getGridModifier()->resetGridFocusWrapMode(nativeNode);
        } else {
            GetArkUINodeModifiers()->getGridModifier()->setGridFocusWrapMode(nativeNode, focusWrapMode);
        }
    } else {
        GetArkUINodeModifiers()->getGridModifier()->resetGridFocusWrapMode(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue GridBridge::ResetFocusWrapMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetGridFocusWrapMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue GridBridge::SetAlignItems(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_alignItems = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);

    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, node, vm), false, panda::JSValueRef::Undefined(vm));
    int32_t itemAlignment = static_cast<int32_t>(GridItemAlignment::DEFAULT);
    if (runtimeCallInfo->GetArgsNumber() < 2) { // 2: param count
        GetArkUINodeModifiers()->getGridModifier()->setGridAlignItems(nativeNode, itemAlignment);
        return panda::JSValueRef::Undefined(vm);
    }
    if (!arg_alignItems->IsUndefined() && !arg_alignItems->IsNull()) {
        itemAlignment = arg_alignItems->Int32Value(vm);
    }

    if (itemAlignment != static_cast<int32_t>(GridItemAlignment::DEFAULT) &&
        itemAlignment != static_cast<int32_t>(GridItemAlignment::STRETCH)) {
        itemAlignment = static_cast<int32_t>(GridItemAlignment::DEFAULT);
    }
        
    GetArkUINodeModifiers()->getGridModifier()->setGridAlignItems(nativeNode, itemAlignment);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue GridBridge::ResetAlignItems(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetGridAlignItems(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetSyncLoad(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> argSyncLoad = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);

    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, node, vm), false, panda::JSValueRef::Undefined(vm));
    bool syncLoad = true;
    if (ArkTSUtils::IsJsView(vm, node) && runtimeCallInfo->GetArgsNumber() >= 2 && // 2: param count
        argSyncLoad->IsBoolean()) {
        syncLoad = argSyncLoad->BooleaValue(vm);
    } else if (!argSyncLoad->IsUndefined() && !argSyncLoad->IsNull()) {
        syncLoad = argSyncLoad->BooleaValue(vm);
    }

    GetArkUINodeModifiers()->getGridModifier()->setSyncLoad(nativeNode, syncLoad);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetSyncLoad(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetSyncLoad(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetEditModeOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, node, vm), false, panda::JSValueRef::Undefined(vm));
    bool isJSView = ArkTSUtils::IsJsView(vm, node);
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    EditModeOptions options;
    Local<JSValueRef> argOptions = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    if (argOptions->IsObject(vm)) {
        auto optionsObj = argOptions->ToObject(vm);
        auto gather = optionsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "enableGatherSelectedItemsAnimation"));
        if (gather->IsBoolean()) {
            options.enableGatherSelectedItemsAnimation = gather->ToBoolean(vm)->Value();
        }
        auto getPreviewBadge = optionsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "onGetPreviewBadge"));
        if (getPreviewBadge->IsFunction(vm)) {
            Local<panda::FunctionRef> functionRef = getPreviewBadge->ToObject(vm);
            auto onGetPreviewBadge = [func = panda::CopyableGlobal(vm, functionRef),
                                         node = AceType::WeakClaim(frameNode), isJSView]() {
                auto vm = func.GetEcmaVM();
                panda::LocalScope socpe(vm);
                panda::TryCatch trycatch(vm);
                PipelineContext::SetCallBackNode(node);
                NG::PreviewBadge badge;
                auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
                if (isJSView) {
                    ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
                }
                ParsePreviewBadge(vm, result, badge);
                return badge;
            };
            options.getPreviewBadge = std::move(onGetPreviewBadge);
        }
        auto useDefaultStyle = optionsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "useDefaultMultiSelectStyle"));
        if (useDefaultStyle->IsBoolean()) {
            options.useDefaultMultiSelectStyle = useDefaultStyle->ToBoolean(vm)->Value();
        }
        auto fingerSelect = optionsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "enableFingerMultiSelect"));
        if (fingerSelect->IsBoolean()) {
            options.enableFingerMultiSelect = fingerSelect->ToBoolean(vm)->Value();
        }
        auto twoFingerSelect = optionsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "enableTwoFingerMultiSelect"));
        if (twoFingerSelect->IsBoolean()) {
            options.enableFingerMultiSelect = twoFingerSelect->ToBoolean(vm)->Value();
        }
    }
    GetArkUINodeModifiers()->getGridModifier()->setEditModeOptions(nativeNode, &options);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetEnableEditMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_enableEditMode = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    bool enableEditMode = arg_enableEditMode->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getGridModifier()->setGridEnableEditMode(nativeNode, enableEditMode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetEnableEditMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetGridEnableEditMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetOnEditModeChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, node, vm), false, panda::JSValueRef::Undefined(vm));
    bool isJSView = ArkTSUtils::IsJsView(vm, node);
    if (!isJSView && (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm))) {
        GetArkUINodeModifiers()->getGridModifier()->resetOnGridEditModeChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    } else if (isJSView && (callbackArg.IsEmpty() || !callbackArg->IsFunction(vm))) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void(bool)> callback = [weakNode = AceType::WeakClaim(frameNode),
                                             func = panda::CopyableGlobal(vm, func), isJSView](bool enableEditMode) {
        auto vm = func.GetEcmaVM();
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        auto frameNode = weakNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        PipelineContext::SetCallBackNode(weakNode);
        panda::Local<panda::JSValueRef> params[1] = { panda::BooleanRef::New(vm, enableEditMode) };
        auto result = func->Call(vm, func.ToLocal(), params, 1);
        if (isJSView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getGridModifier()->setOnGridEditModeChangeCallBack(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetOnEditModeChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetOnGridEditModeChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetEditModeOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetEditModeOptions(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetGridScroller(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeVal = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> scrollerVal = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    bool isBindController = false;
    if (runtimeCallInfo->GetArgsNumber() > CALL_ARG_2) {
        Local<JSValueRef> bindArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_2);
        isBindController = bindArg->IsBoolean() && bindArg->ToBoolean(vm)->Value();
    }
    RefPtr<ScrollControllerBase> positionController;
    RefPtr<ScrollProxy> scrollBarProxy;
    CHECK_NULL_RETURN(nodeVal->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeVal->ToNativePointer(vm)->Value());
    if (scrollerVal->IsObject(vm)) {
        Local<ObjectRef> scrollerObj = scrollerVal->ToObject(vm);
        auto* jsScroller = static_cast<Framework::JSScroller*>(scrollerObj->GetNativePointerField(vm, 0));
        if (jsScroller) {
            jsScroller->SetInstanceId(Container::CurrentIdSafely());
            if (isBindController) {
                auto controller = GetArkUINodeModifiers()->getGridModifier()->getController(nativeNode);
                positionController = AceType::Claim(reinterpret_cast<ScrollControllerBase*>(controller));
            } else {
                positionController = AceType::MakeRefPtr<ScrollableController>();
            }
            jsScroller->SetController(positionController);
            scrollBarProxy = jsScroller->GetScrollBarProxy();
            if (!scrollBarProxy) {
                scrollBarProxy = AceType::MakeRefPtr<NG::ScrollBarProxy>();
                jsScroller->SetScrollBarProxy(scrollBarProxy);
            }
            if (isBindController) {
                auto proxyPtr = reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(scrollBarProxy));
                GetArkUINodeModifiers()->getGridModifier()->setScrollBarProxy(nativeNode, proxyPtr);
                return panda::JSValueRef::Undefined(vm);
            }
        }
    }
    GetArkUINodeModifiers()->getGridModifier()->initScroller(
        nativeNode, positionController.GetRawPtr(), scrollBarProxy.GetRawPtr());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetGridLayoutOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeVal = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> irregularIndexesVal = runtimeCallInfo->GetCallArgRef(2); // 2: parameter index
    Local<JSValueRef> indexesLengthVal = runtimeCallInfo->GetCallArgRef(3); // 3: parameter index
    CHECK_NULL_RETURN(nodeVal->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeVal->ToNativePointer(vm)->Value());
    int32_t length = 0;
    if (indexesLengthVal->IsNumber()) {
        length = indexesLengthVal->Int32Value(vm);
    }
    auto irregularIndexes = std::make_unique<int32_t[]>(length);
    bool irregularResult = ArkTSUtils::ParseArray<int32_t>(vm, irregularIndexesVal, irregularIndexes.get(), length,
        [](const EcmaVM* vm, const Local<JSValueRef>& jsValue) {
            bool isNumber = false;
            return jsValue->GetValueInt32(isNumber);
        });

    GridLayoutOptions options;
    // only support regularSize(1, 1)
    options.regularSize.rows = 1;
    options.regularSize.columns = 1;
    if (irregularResult) {
        for (int32_t i = 0; i < length; i++) {
            options.irregularIndexes.emplace(irregularIndexes[i]);
        }
    }
    irregularIndexes.reset();
    ParseGetGridItemSize(vm, runtimeCallInfo->GetCallArgRef(4), options); // 4: parameter index
    ParseGetGridItemRect(vm, runtimeCallInfo->GetCallArgRef(5), options); // 5: parameter index
    ParseGetStartIndexByOffset(vm, runtimeCallInfo->GetCallArgRef(6), options); // 6: parameter index
    ParseGetStartIndexByIndex(vm, runtimeCallInfo->GetCallArgRef(7), options); // 7: parameter index
    GetArkUINodeModifiers()->getGridModifier()->setLayoutOptions(nativeNode, &options);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetOnGridScrollIndex(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), false, panda::JSValueRef::Undefined(vm));
    bool isJSView = ArkTSUtils::IsJsView(vm, firstArg);
    if (!isJSView && (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm))) {
        GetArkUINodeModifiers()->getGridModifier()->resetOnGridScrollIndex(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    } else if (isJSView && (callbackArg.IsEmpty() || !callbackArg->IsFunction(vm))) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    if (isJSView && !Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TEN)) {
        ScrollToIndexFunc callback = [func = panda::CopyableGlobal(vm, func)](
                                         const BaseEventInfo* event) {
            auto vm = func.GetEcmaVM();
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            const auto* eventInfo = TypeInfoHelper::DynamicCast<V2::GridEventInfo>(event);
            if (!eventInfo) {
                return;
            }
            auto params = ArkTSUtils::ToJSValueWithVM(vm, eventInfo->GetScrollIndex());
            auto result = func->Call(vm, func.ToLocal(), &params, 1);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        };
        GetArkUINodeModifiers()->getGridModifier()->setOnScrollToIndex(
            nativeNode, reinterpret_cast<void*>(&callback));
        return panda::JSValueRef::Undefined(vm);
    }

    std::function<void(int32_t, int32_t)> callback = [weakNode = AceType::WeakClaim(frameNode),
                                                         func = panda::CopyableGlobal(vm, func), isJSView](
                                                         const int32_t first, const int32_t last) {
        auto vm = func.GetEcmaVM();
        CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        if (!isJSView) {
            PipelineContext::SetCallBackNode(weakNode);
        }

        panda::Local<panda::NumberRef> firstParam = panda::NumberRef::New(vm, first);
        panda::Local<panda::NumberRef> lastParam = panda::NumberRef::New(vm, last);
        // 2: Array length
        panda::Local<panda::JSValueRef> params[2] = { firstParam, lastParam };
        auto result = func->Call(vm, func.ToLocal(), params, 2); // 2: Array length
        if (isJSView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getGridModifier()->setOnGridScrollIndexCallBack(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetOnGridScrollIndex(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetOnGridScrollIndex(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetOnGridScrollBarUpdate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), false, panda::JSValueRef::Undefined(vm));
    bool isJSView = ArkTSUtils::IsJsView(vm, firstArg);
    if (!isJSView && (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm))) {
        GetArkUINodeModifiers()->getGridModifier()->resetOnGridScrollBarUpdate(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    } else if (isJSView && (callbackArg.IsEmpty() || !callbackArg->IsFunction(vm))) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<std::pair<std::optional<float>, std::optional<float>>(int32_t, Dimension)> callback =
        [weakNode = AceType::WeakClaim(frameNode), func = panda::CopyableGlobal(vm, func), isJSView](
            const int32_t index, const Dimension& offset) {
            auto vm = func.GetEcmaVM();
            std::pair<float, float> defaultResult(0, 0);
            CHECK_EQUAL_RETURN(ArkTSUtils::CheckJavaScriptScope(vm), false, defaultResult);
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(weakNode);
            panda::Local<panda::JSValueRef> params[] = { ArkTSUtils::ToJsValueWithVM(vm, index),
                ArkTSUtils::ToJsValueWithVM(vm, offset.ConvertToVp()) };
            auto result = func->Call(vm, func.ToLocal(), params, 2); // 2: Array length
            if (isJSView) {
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            }
            if (result->IsObject(vm)) {
                auto resultObj = result->ToObject(vm);
                CalcDimension totalOffset_;
                CalcDimension totalLength_;
                if (ArkTSUtils::ParseJsDimensionVp(
                        vm, ArkTSUtils::GetProperty(vm, resultObj, "totalOffset"), totalOffset_) &&
                    ArkTSUtils::ParseJsDimensionVp(
                        vm, ArkTSUtils::GetProperty(vm, resultObj, "totalLength"), totalLength_)) {
                    return std::pair<float, float>(totalOffset_.ConvertToPx(), totalLength_.ConvertToPx());
                }
            }
            return defaultResult;
        };
    GetArkUINodeModifiers()->getGridModifier()->setOnGridScrollBarUpdateCallBack(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetOnGridScrollBarUpdate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetOnGridScrollBarUpdate(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetOnGridItemDragStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> eventArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), false, panda::JSValueRef::Undefined(vm));
    bool isJSView = ArkTSUtils::IsJsView(vm, firstArg);
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));

    if (eventArg.IsEmpty() || !eventArg->IsFunction(vm)) {
        if (!isJSView) {
            GetArkUINodeModifiers()->getGridModifier()->resetOnGridItemDragStart(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }

    Local<panda::FunctionRef> onDragFunc = eventArg->ToObject(vm);
    std::function<void(const ItemDragInfo&, int32_t)> callback = [weakNode = AceType::WeakClaim(frameNode),
                                                                     func = panda::CopyableGlobal(vm, onDragFunc),
                                                                     isJSView](
                                                                     const ItemDragInfo& dragInfo, int32_t itemIndex) {
        auto vm = func.GetEcmaVM();
        CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
        ACE_SCORING_EVENT("Grid.onItemDragStart");
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        Local<JSValueRef> params[] = { ArkTSUtils::CreateItemDragInfo(vm, dragInfo),
            ArkTSUtils::ToJsValueWithVM(vm, itemIndex) };
        Local<JSValueRef> ret = func->Call(vm, func.ToLocal(), params, 2); // 2: Array length
        if (ret.IsEmpty() || !ret->IsObject(vm)) {
            return;
        }

        auto builderObj = ret->ToObject(vm);
        auto builder = ArkTSUtils::GetProperty(vm, builderObj, "builder");
        if (builder.IsEmpty() || !builder->IsFunction(vm)) {
            return;
        }

        Local<panda::FunctionRef> builderFunc = builder->ToObject(vm);
        PipelineContext::SetCallBackNode(weakNode);
        builderFunc->Call(vm, builderFunc, nullptr, 0);
    };
    GetArkUINodeModifiers()->getGridModifier()->setOnGridItemDragStart(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetOnGridItemDragStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetOnGridItemDragStart(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetOnGridItemDragEnter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> eventArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), false, panda::JSValueRef::Undefined(vm));
    bool isJSView = ArkTSUtils::IsJsView(vm, firstArg);
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));

    if (eventArg.IsEmpty() || !eventArg->IsFunction(vm)) {
        if (!isJSView) {
            GetArkUINodeModifiers()->getGridModifier()->resetOnGridItemDragEnter(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    Local<panda::FunctionRef> onDragFunc = eventArg->ToObject(vm);
    std::function<void(const ItemDragInfo&)> callback = [weakNode = AceType::WeakClaim(frameNode),
                                                            func = panda::CopyableGlobal(vm, onDragFunc), isJSView](
                                                            const ItemDragInfo& dragInfo) {
        auto vm = func.GetEcmaVM();
        CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);

        PipelineContext::SetCallBackNode(weakNode);
        Local<JSValueRef> params = ArkTSUtils::CreateItemDragInfo(vm, dragInfo);
        auto result = func->Call(vm, func.ToLocal(), &params, 1);
        if (isJSView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getGridModifier()->setOnGridItemDragEnter(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetOnGridItemDragEnter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetOnGridItemDragEnter(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetOnGridItemDragMove(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> eventArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), false, panda::JSValueRef::Undefined(vm));
    bool isJSView = ArkTSUtils::IsJsView(vm, firstArg);
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));

    if (eventArg.IsEmpty() || !eventArg->IsFunction(vm)) {
        if (!isJSView) {
            GetArkUINodeModifiers()->getGridModifier()->resetOnGridItemDragMove(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    Local<panda::FunctionRef> onDragFunc = eventArg->ToObject(vm);
    std::function<void(const ItemDragInfo&, int32_t, int32_t)> callback =
        [weakNode = AceType::WeakClaim(frameNode), func = panda::CopyableGlobal(vm, onDragFunc), isJSView](
            const ItemDragInfo& dragInfo, int32_t itemIndex, int32_t insertIndex) {
            auto vm = func.GetEcmaVM();
            CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);

            PipelineContext::SetCallBackNode(weakNode);
            Local<JSValueRef> params[] = { ArkTSUtils::CreateItemDragInfo(vm, dragInfo),
                ArkTSUtils::ToJsValueWithVM(vm, itemIndex), ArkTSUtils::ToJsValueWithVM(vm, insertIndex) };
            auto result = func->Call(vm, func.ToLocal(), params, 3); // 3: Array length
            if (isJSView) {
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            }
        };
    GetArkUINodeModifiers()->getGridModifier()->setOnGridItemDragMove(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetOnGridItemDragMove(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetOnGridItemDragMove(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetOnGridItemDragLeave(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> eventArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), false, panda::JSValueRef::Undefined(vm));
    bool isJSView = ArkTSUtils::IsJsView(vm, firstArg);
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));

    if (eventArg.IsEmpty() || !eventArg->IsFunction(vm)) {
        if (!isJSView) {
            GetArkUINodeModifiers()->getGridModifier()->resetOnGridItemDragLeave(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    Local<panda::FunctionRef> onDragFunc = eventArg->ToObject(vm);
    std::function<void(const ItemDragInfo&, int32_t)> callback = [weakNode = AceType::WeakClaim(frameNode),
                                                                     func = panda::CopyableGlobal(vm, onDragFunc),
                                                                     isJSView](
                                                                     const ItemDragInfo& dragInfo, int32_t itemIndex) {
        auto vm = func.GetEcmaVM();
        CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);

        PipelineContext::SetCallBackNode(weakNode);
        Local<JSValueRef> params[] = { ArkTSUtils::CreateItemDragInfo(vm, dragInfo),
            ArkTSUtils::ToJsValueWithVM(vm, itemIndex) };
        auto result = func->Call(vm, func.ToLocal(), params, 2); // 2: Array length
        if (isJSView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getGridModifier()->setOnGridItemDragLeave(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetOnGridItemDragLeave(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetOnGridItemDragLeave(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetOnGridItemDrop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> eventArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), false, panda::JSValueRef::Undefined(vm));
    bool isJSView = ArkTSUtils::IsJsView(vm, firstArg);
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));

    if (eventArg.IsEmpty() || !eventArg->IsFunction(vm)) {
        if (!isJSView) {
            GetArkUINodeModifiers()->getGridModifier()->resetOnGridItemDrop(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    Local<panda::FunctionRef> onDragFunc = eventArg->ToObject(vm);
    std::function<void(const ItemDragInfo&, int32_t, int32_t, bool)> callback =
        [weakNode = AceType::WeakClaim(frameNode), func = panda::CopyableGlobal(vm, onDragFunc), isJSView](
            const ItemDragInfo& dragInfo, int32_t itemIndex, int32_t insertIndex, bool isSuccess) {
            auto vm = func.GetEcmaVM();
            CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);

            PipelineContext::SetCallBackNode(weakNode);
            std::vector<Local<JSValueRef>> params = { ArkTSUtils::CreateItemDragInfo(vm, dragInfo),
                ArkTSUtils::ToJsValueWithVM(vm, itemIndex), ArkTSUtils::ToJsValueWithVM(vm, insertIndex),
                ArkTSUtils::ToJsValueWithVM(vm, isSuccess) };
            auto result = func->Call(vm, func.ToLocal(), params.data(), static_cast<int32_t>(params.size()));
            if (isJSView) {
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
                UiSessionManager::GetInstance()->ReportComponentChangeEvent(
                    "event", "Grid.onItemDrop", ComponentEventType::COMPONENT_EVENT_SCROLL);
            }
        };
    GetArkUINodeModifiers()->getGridModifier()->setOnGridItemDrop(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetOnGridItemDrop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetOnGridItemDrop(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetSupportLazyLoadingEmptyBranch(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_support = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);

    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, node, vm), false, panda::JSValueRef::Undefined(vm));

    GetArkUINodeModifiers()->getGridModifier()->setSupportLazyLoadingEmptyBranch(
        nativeNode, arg_support->IsBoolean() ? arg_support->ToBoolean(vm)->Value() : false);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetOnScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> funcArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), false, panda::JSValueRef::Undefined(vm));
    if (funcArg.IsEmpty() || !funcArg->IsFunction(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<panda::FunctionRef> funcRef = funcArg->ToObject(vm);
    OnScrollEvent onScroll = [func = panda::CopyableGlobal(vm, funcRef)](
        Dimension scrollOffset, ScrollState scrollState) {
        auto vm = func.GetEcmaVM();
        CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        auto params = ArkTSUtils::ConvertToJSValues(vm, scrollOffset, scrollState);
        auto result = func->Call(vm, func.ToLocal(), params.data(), static_cast<int32_t>(params.size()));
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
    };
    GetArkUINodeModifiers()->getGridModifier()->setOnGridScroll(nativeNode, reinterpret_cast<void*>(&onScroll));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetOnReachStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> funcArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), false, panda::JSValueRef::Undefined(vm));
    if (funcArg.IsEmpty() || !funcArg->IsFunction(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<panda::FunctionRef> funcRef = funcArg->ToObject(vm);
    OnReachEvent onReachStart = [func = panda::CopyableGlobal(vm, funcRef)]() {
        auto vm = func.GetEcmaVM();
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        UiSessionManager::GetInstance()->ReportComponentChangeEvent(
            "event", "Grid.onReachStart", ComponentEventType::COMPONENT_EVENT_SCROLL);
    };
    GetArkUINodeModifiers()->getGridModifier()->setOnGridReachStart(nativeNode, reinterpret_cast<void*>(&onReachStart));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetOnReachEnd(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> funcArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), false, panda::JSValueRef::Undefined(vm));
    if (funcArg.IsEmpty() || !funcArg->IsFunction(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<panda::FunctionRef> funcRef = funcArg->ToObject(vm);
    OnReachEvent onReachEnd = [func = panda::CopyableGlobal(vm, funcRef)]() {
        auto vm = func.GetEcmaVM();
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        UiSessionManager::GetInstance()->ReportComponentChangeEvent(
            "event", "Grid.onReachEnd", ComponentEventType::COMPONENT_EVENT_SCROLL);
    };
    GetArkUINodeModifiers()->getGridModifier()->setOnGridReachEnd(nativeNode, reinterpret_cast<void*>(&onReachEnd));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetOnScrollStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> funcArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), false, panda::JSValueRef::Undefined(vm));
    if (funcArg.IsEmpty() || !funcArg->IsFunction(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<panda::FunctionRef> funcRef = funcArg->ToObject(vm);
    OnScrollStartEvent onScrollStart = [func = panda::CopyableGlobal(vm, funcRef)]() {
        auto vm = func.GetEcmaVM();
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
    };
    GetArkUINodeModifiers()->getGridModifier()->setOnGridScrollStart(
        nativeNode, reinterpret_cast<void*>(&onScrollStart));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetOnScrollStop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> funcArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), false, panda::JSValueRef::Undefined(vm));
    if (funcArg.IsEmpty() || !funcArg->IsFunction(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<panda::FunctionRef> funcRef = funcArg->ToObject(vm);
    OnScrollStopEvent onScrollStop = [func = panda::CopyableGlobal(vm, funcRef)]() {
        auto vm = func.GetEcmaVM();
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        UiSessionManager::GetInstance()->ReportComponentChangeEvent(
            "event", "Grid.onScrollStop", ComponentEventType::COMPONENT_EVENT_SCROLL);
    };
    GetArkUINodeModifiers()->getGridModifier()->setOnGridScrollStop(nativeNode, reinterpret_cast<void*>(&onScrollStop));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetOnScrollFrameBegin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> funcArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), false, panda::JSValueRef::Undefined(vm));
    if (funcArg.IsEmpty() || !funcArg->IsFunction(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<panda::FunctionRef> funcRef = funcArg->ToObject(vm);
    OnScrollFrameBeginEvent onScrollBegin = [func = panda::CopyableGlobal(vm, funcRef)](
        Dimension offset, ScrollState state) -> ScrollFrameResult {
        ScrollFrameResult scrollRes { .offset = offset };
        auto vm = func.GetEcmaVM();
        CHECK_EQUAL_RETURN(ArkTSUtils::CheckJavaScriptScope(vm), false, scrollRes);
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        auto params = ArkTSUtils::ConvertToJSValues(vm, offset, state);
        auto result = func->Call(vm, func.ToLocal(), params.data(), static_cast<int32_t>(params.size()));
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        if (result.IsEmpty() || !result->IsObject(vm)) {
            return scrollRes;
        }
        auto resObj = result->ToObject(vm);
        auto dxRemainValue = ArkTSUtils::GetProperty(vm, resObj, "offsetRemain");
        if (!dxRemainValue.IsEmpty() && dxRemainValue->IsNumber()) {
            scrollRes.offset = Dimension(dxRemainValue->ToNumber(vm)->Value(), DimensionUnit::VP);
        }
        return scrollRes;
    };
    GetArkUINodeModifiers()->getGridModifier()->setOnGridScrollFrameBegin(
        nativeNode, reinterpret_cast<void*>(&onScrollBegin));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::WillUseProxy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
#ifdef NG_BUILD
    return ArkTSUtils::ToJSValueWithVM(vm, false);
#else
    auto parentGrid = Framework::ViewStackProcessor::GetInstance()->GetTopGrid();

    // return true if code path for GridElement and its children will rely on
    // ElementProxy. Only in this case shallow render functionality can be used
    // see also GridLayoutComponent::CreateElement() and GridItemElementProxy class
    return ArkTSUtils::ToJSValueWithVM(vm, parentGrid ? !parentGrid->UseNonProxiedCodePath() : false);
#endif
}

ArkUINativeModuleValue GridBridge::SetJSScrollBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> displayModeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, node, vm), false, panda::JSValueRef::Undefined(vm));
    DisplayMode defaultValue =
        static_cast<DisplayMode>(GetArkUINodeModifiers()->getGridModifier()->getDisplayMode(nativeNode));

    auto displayMode = static_cast<int32_t>(defaultValue);
    if (runtimeCallInfo->GetArgsNumber() >= 1) {
        if (!displayModeArg.IsEmpty() && !displayModeArg->IsUndefined() && displayModeArg->IsNumber()) {
            ArkTSUtils::ParseJsInt32(vm, displayModeArg, displayMode);
            if (displayMode < 0 || displayMode >= static_cast<int32_t>(DISPLAY_MODE.size())) {
                displayMode = static_cast<int32_t>(defaultValue);
            }
        }
    }
    GetArkUINodeModifiers()->getGridModifier()->setGridScrollBar(nativeNode, displayMode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetJSScrollBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, node, vm), false, panda::JSValueRef::Undefined(vm));

    RefPtr<ResourceObject> resObj;
    auto scrollBarWidth = ParseBarWidth(vm, runtimeCallInfo, resObj);
    if (!scrollBarWidth.empty()) {
        GetArkUINodeModifiers()->getGridModifier()->setScrollBarWidthString(nativeNode, scrollBarWidth.c_str());
    }
    GetArkUINodeModifiers()->getGridModifier()->setGridScrollBarWidthResObj(nativeNode, resObj.GetRawPtr());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetJSEnableEditMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, node, vm), false, panda::JSValueRef::Undefined(vm));

    if (runtimeCallInfo->GetArgsNumber() < 2) { // 2: param count
        return panda::JSValueRef::Undefined(vm);
    }
    bool enableEditMode = false;
    Local<JSValueRef> changeEventVal;
    auto enableVal = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    if (!enableVal.IsEmpty() && enableVal->IsObject(vm)) {
        auto obj = enableVal->ToObject(vm);
        enableVal = ArkTSUtils::GetProperty(vm, obj, "value");
        changeEventVal = ArkTSUtils::GetProperty(vm, obj, "$value");
    } else if (runtimeCallInfo->GetArgsNumber() > 2) { // 2: param count
        changeEventVal = runtimeCallInfo->GetCallArgRef(CALL_ARG_2);
    }
    if (!enableVal.IsEmpty() && enableVal->IsBoolean()) {
        enableEditMode = enableVal->BooleaValue(vm);
    }
    GetArkUINodeModifiers()->getGridModifier()->setEnableEditMode(nativeNode, enableEditMode);

    if (!changeEventVal.IsEmpty() && changeEventVal->IsFunction(vm)) {
        Local<panda::FunctionRef> jsFunc = changeEventVal->ToObject(vm);
        auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        std::function<void(bool)> changeEvent = [func = panda::CopyableGlobal(vm, jsFunc), node = targetNode](
                                                    bool param) {
            auto vm = func.GetEcmaVM();
            CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            ACE_SCORING_EVENT("Grid.EnableEditModeChangeEvent");
            auto newJSVal = ArkTSUtils::ToJsValueWithVM(vm, param);
            PipelineContext::SetCallBackNode(node);
            auto res = func->Call(vm, func.ToLocal(), &newJSVal, 1);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, res);
        };
        GetArkUINodeModifiers()->getGridModifier()->setEnableEditModeChangeEvent(nativeNode, &changeEvent);
    }
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
