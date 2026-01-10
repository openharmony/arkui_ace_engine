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
#include "core/components_ng/pattern/waterflow/bridge/waterflow/arkts_native_water_flow_bridge.h"

#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/jsview/js_scroller.h"
#include "bridge/declarative_frontend/jsview/js_water_flow_sections.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components_ng/pattern/scrollable/scrollable_controller.h"
#include "core/components_ng/pattern/waterflow/water_flow_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double FRICTION_DEFAULT = -1.0;
constexpr double DIMENSION_DEFAULT = 0.0;
constexpr int32_t DISPLAY_MODE_SIZE = 3;
constexpr int32_t NUM_0 = 0;
constexpr int32_t NUM_1 = 1;
constexpr int32_t NUM_2 = 2;
constexpr int32_t NUM_3 = 3;
constexpr int32_t NUM_4 = 4;
constexpr int32_t NUM_5 = 5;
constexpr int32_t BREAKPOINT_DEFAULT = 0;
constexpr int32_t BREAKPOINT_SM2MD3LG5 = 2;
const std::vector<FlexDirection> LAYOUT_DIRECTION = { FlexDirection::ROW, FlexDirection::COLUMN,
    FlexDirection::ROW_REVERSE, FlexDirection::COLUMN_REVERSE };
const std::vector<DisplayMode> DISPLAY_MODE = { DisplayMode::OFF, DisplayMode::AUTO, DisplayMode::ON };

bool GetNativeNode(ArkUINodeHandle& nativeNode, const Local<JSValueRef>& nodeArg, const EcmaVM* vm)
{
    CHECK_NULL_RETURN(vm, false);
    if (nodeArg->IsNativePointer(vm)) {
        nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
        return true;
    }
    if (nodeArg->IsBoolean() && nodeArg->ToBoolean(vm)->Value()) {
        nativeNode = nullptr;
        return true;
    }

    return false;
}

void SetItemConstraintSizeSendParams(CalcDimension& doubleValue, std::string& calcStrValue)
{
    if (doubleValue.Unit() == DimensionUnit::CALC) {
        calcStrValue = doubleValue.CalcValue();
        doubleValue.SetValue(DIMENSION_DEFAULT);
    }
}

bool SetMarginProperty(EcmaVM* vm, const Local<ObjectRef>& paddingObj, NG::MarginProperty& margin)
{
    std::optional<CalcDimension> left;
    std::optional<CalcDimension> right;
    std::optional<CalcDimension> top;
    std::optional<CalcDimension> bottom;
    ArkTSUtils::ParseMarginOrPaddingCorner(vm, paddingObj, top, bottom, left, right);
    bool isMarginObject = false;
    if (top.has_value()) {
        if (top.value().Unit() == DimensionUnit::CALC) {
            margin.top = NG::CalcLength(top.value().CalcValue());
        } else {
            margin.top = NG::CalcLength(top.value());
        }
        isMarginObject = true;
    }
    if (bottom.has_value()) {
        if (bottom.value().Unit() == DimensionUnit::CALC) {
            margin.bottom = NG::CalcLength(bottom.value().CalcValue());
        } else {
            margin.bottom = NG::CalcLength(bottom.value());
        }
        isMarginObject = true;
    }
    if (left.has_value()) {
        if (left.value().Unit() == DimensionUnit::CALC) {
            margin.left = NG::CalcLength(left.value().CalcValue());
        } else {
            margin.left = NG::CalcLength(left.value());
        }
        isMarginObject = true;
    }
    if (right.has_value()) {
        if (right.value().Unit() == DimensionUnit::CALC) {
            margin.right = NG::CalcLength(right.value().CalcValue());
        } else {
            margin.right = NG::CalcLength(right.value());
        }
        isMarginObject = true;
    }
    return isMarginObject;
}

void ParseMargin(EcmaVM* vm, const Local<JSValueRef>& jsValue, NG::MarginProperty& margin)
{
    CHECK_NULL_VOID(vm);
    if (jsValue->IsObject(vm)) {
        if (SetMarginProperty(vm, jsValue->ToObject(vm), margin)) {
            return;
        }
    }

    CalcDimension length;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, jsValue, length)) {
        length.Reset();
    }
    if (length.Unit() == DimensionUnit::CALC) {
        margin.SetEdges(NG::CalcLength(length.CalcValue()));
    } else {
        margin.SetEdges(NG::CalcLength(length));
    }
}

void ParseGaps(EcmaVM* vm, const Local<ObjectRef>& obj, WaterFlowSections::Section& section)
{
    CHECK_NULL_VOID(vm);
    if (ArkTSUtils::HasProperty(vm, obj, "columnsGap")) {
        auto columnsGap = ArkTSUtils::GetProperty(vm, obj, "columnsGap");
        CalcDimension colGap;
        if (!ArkTSUtils::ParseJsDimensionVp(vm, columnsGap, colGap) || colGap.Value() < 0) {
            colGap.SetValue(0.0);
        }
        section.columnsGap = colGap;
    }

    if (ArkTSUtils::HasProperty(vm, obj, "rowsGap")) {
        auto rowsGap = ArkTSUtils::GetProperty(vm, obj, "rowsGap");
        CalcDimension rowGap;
        if (!ArkTSUtils::ParseJsDimensionVp(vm, rowsGap, rowGap) || rowGap.Value() < 0) {
            rowGap.SetValue(0.0);
        }
        section.rowsGap = rowGap;
    }

    if (ArkTSUtils::HasProperty(vm, obj, "margin")) {
        auto margin = ArkTSUtils::GetProperty(vm, obj, "margin");
        NG::MarginProperty marginProperty;
        ParseMargin(vm, margin, marginProperty);
        section.margin = marginProperty;
    }
}

bool ParseSectionOptions(EcmaVM* vm, const Local<JSValueRef>& jsValue, WaterFlowSections::Section& section)
{
    CHECK_NULL_RETURN(vm, false);
    if (!jsValue->IsObject(vm)) {
        LOGW("The arg must be object");
        return false;
    }
    Local<ObjectRef> obj = jsValue->ToObject(vm);
    if (!ArkTSUtils::HasProperty(vm, obj, "itemsCount")) {
        return false;
    }
    auto itemsCount = ArkTSUtils::GetProperty(vm, obj, "itemsCount");
    ArkTSUtils::ParseJsInteger(vm, itemsCount, section.itemsCount);
    if (section.itemsCount < 0) {
        LOGW("itemsCount can not be less than 0");
        return false;
    }

    if (ArkTSUtils::HasProperty(vm, obj, "crossCount")) {
        auto crossCount = ArkTSUtils::GetProperty(vm, obj, "crossCount");
        int32_t crossCountValue = 1;
        ArkTSUtils::ParseJsInteger(vm, crossCount, crossCountValue);
        if (crossCountValue <= 0) {
            crossCountValue = 1;
        }
        section.crossCount = crossCountValue;
    }

    ParseGaps(vm, obj, section);

    if (!ArkTSUtils::HasProperty(vm, obj, "onGetItemMainSizeByIndex")) {
        return true;
    }
    auto getSizeByIndex = ArkTSUtils::GetProperty(vm, obj, "onGetItemMainSizeByIndex");
    if (!getSizeByIndex->IsFunction(vm)) {
        return true;
    }
    Local<panda::FunctionRef> getSizeByIndexFunc = getSizeByIndex->ToObject(vm);

    auto onGetItemMainSizeByIndex = [vm, func = panda::CopyableGlobal(vm, getSizeByIndexFunc)](int32_t index) {
        panda::LocalScope socpe(vm);
        panda::TryCatch trycatch(vm);
        panda::Local<panda::NumberRef> paramIndex = panda::NumberRef::New(vm, index);
        panda::Local<panda::JSValueRef> params[1] = { paramIndex };
        auto result = func->Call(vm, func.ToLocal(), params, 1);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        if (!result->IsNumber()) {
            return 0.0f;
        }
        return static_cast<float>(result->ToNumber(vm)->Value());
    };
    section.onGetItemMainSizeByIndex = std::move(onGetItemMainSizeByIndex);
    return true;
}

void ParseSections(EcmaVM* vm, const Local<panda::ArrayRef>& sectionArray, RefPtr<WaterFlowSections>& waterFlowSections)
{
    CHECK_NULL_VOID(vm);
    auto length = sectionArray->Length(vm);
    std::vector<NG::WaterFlowSections::Section> newSections;
    for (size_t j = 0; j < length; ++j) {
        NG::WaterFlowSections::Section section;
        auto newSection = panda::ArrayRef::GetValueAt(vm, sectionArray, j);
        if (ParseSectionOptions(vm, newSection, section)) {
            newSections.emplace_back(section);
        }
    }
    waterFlowSections->ChangeData(0, waterFlowSections->GetSectionInfo().size(), newSections);
}

void SetNativeWaterFlowSection(
    const EcmaVM* vm, const Local<ObjectRef>& jsSection, const Local<ObjectRef>& nativeSection)
{
    CHECK_NULL_VOID(vm);
    panda::TryCatch trycatch(vm);
    if (jsSection.IsEmpty() || jsSection->IsNull() || jsSection->IsUndefined() || nativeSection.IsEmpty() ||
        nativeSection->IsNull() || nativeSection->IsUndefined()) {
        return;
    }

    auto property = ArkTSUtils::GetProperty(vm, jsSection, "setNativeSection");
    if (!property->IsFunction(vm)) {
        return;
    }

    Local<panda::FunctionRef> setNativeSectionFunc = property->ToObject(vm);
    Local<JSValueRef> params[1] = { nativeSection };
    auto result = setNativeSectionFunc->Call(vm, jsSection, params, 1);
    ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
}

void UpdateSections(EcmaVM* vm, const Local<JSValueRef>& sections, RefPtr<WaterFlowSections>& waterFlowSections,
    NG::FrameNode* frameNode)
{
    CHECK_NULL_VOID(vm);
    CHECK_NULL_VOID(waterFlowSections);
    auto sectionsObject = sections->ToObject(vm);
    auto property = ArkTSUtils::GetProperty(vm, sectionsObject, "getNativeSection");
    CHECK_NULL_VOID(property->IsFunction(vm));
    panda::TryCatch trycatch(vm);
    Local<panda::FunctionRef> getNativeSectionFunc = property->ToObject(vm);
    auto nativeSection = getNativeSectionFunc->Call(vm, sectionsObject, nullptr, 0);
    ArkTSUtils::HandleCallbackJobs(vm, trycatch, nativeSection);
    if (nativeSection.IsEmpty() || nativeSection->IsNull() || nativeSection->IsUndefined()) {
        nativeSection = Framework::JSWaterFlowSections::NewInstance();
        SetNativeWaterFlowSection(vm, sectionsObject, nativeSection);
    }
    CHECK_NULL_VOID(nativeSection->IsObject(vm));
    auto nativeSectionObj = nativeSection->ToObject(vm);
    if (!frameNode) {
        frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    }
    CHECK_NULL_VOID(frameNode);
    Framework::JSWaterFlowSections* section =
        static_cast<Framework::JSWaterFlowSections*>(nativeSectionObj->GetNativePointerField(vm, 0));
    CHECK_NULL_VOID(section);
    if (section->IsBound(frameNode)) {
        return;
    }
    auto id = Container::CurrentId();
    auto callback = [id, weak = AceType::WeakClaim(AceType::RawPtr(waterFlowSections)),
                        weakNode = AceType::WeakClaim(frameNode)](size_t start, size_t deleteCount,
                        std::vector<NG::WaterFlowSections::Section>& newSections,
                        const std::vector<NG::WaterFlowSections::Section>& allSections) {
        ContainerScope scope(id);
        auto node = weakNode.Upgrade();
        CHECK_NULL_VOID(node);
        auto context = node->GetContext();
        CHECK_NULL_VOID(context);
        context->AddBuildFinishCallBack([start, deleteCount, change = newSections, weak, all = allSections]() {
            auto nodeSection = weak.Upgrade();
            CHECK_NULL_VOID(nodeSection);
            nodeSection->ChangeData(start, deleteCount, change);
            if (nodeSection->GetSectionInfo().size() != all.size()) {
                nodeSection->ChangeData(0, nodeSection->GetSectionInfo().size(), all);
            }
        });
        context->RequestFrame();
    };
    section->SetOnSectionChangedCallback(frameNode, callback);
    // Used for makeObserved to listen and refresh status.
    ArkTSUtils::GetProperty(vm, sectionsObject, "changeFlag");
    auto allSections = ArkTSUtils::GetProperty(vm, sectionsObject, "sectionArray");
    CHECK_NULL_VOID(allSections->IsArray(vm));
    ParseSections(vm, allSections->ToObject(vm), waterFlowSections);
}

void UpdateWaterFlowSectionsByFrameNode(
    NG::FrameNode* frameNode, EcmaVM* vm, const Local<JSValueRef>& sections, bool isJSView)
{
    auto waterFlowSections = NG::WaterFlowModelNG::GetOrCreateWaterFlowSections(frameNode);
    CHECK_NULL_VOID(waterFlowSections);
    UpdateSections(vm, sections, waterFlowSections, frameNode);
}

void SetWaterFlowSections(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> sectionsArgs = runtimeCallInfo->GetCallArgRef(NUM_2);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_VOID(GetNativeNode(nativeNode, nodeArg, vm), false);
    bool isJSView = nodeArg->IsBoolean() && nodeArg->ToBoolean(vm)->Value();
    if (!sectionsArgs->IsNull() && sectionsArgs->IsObject(vm)) {
        nativeNode = nativeNode
                         ? nativeNode
                         : reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
        UpdateWaterFlowSectionsByFrameNode(frameNode, vm, sectionsArgs, isJSView);
        GetArkUINodeModifiers()->getWaterFlowModifier()->resetWaterflowFooter(nativeNode);
    } else if (!isJSView) {
        GetArkUINodeModifiers()->getWaterFlowModifier()->resetWaterFlowSections(nativeNode);
    }
}

RefPtr<NG::UINode> SetWaterFlowBuilderNode(EcmaVM* vm, const Local<ObjectRef>& footerJsObject)
{
    CHECK_NULL_RETURN(vm, nullptr);
    auto builderNodeParam = ArkTSUtils::GetProperty(vm, footerJsObject, "builderNode_");
    if (builderNodeParam->IsObject(vm)) {
        auto builderNodeObject = builderNodeParam->ToObject(vm);
        auto nodePtr = ArkTSUtils::GetProperty(vm, builderNodeObject, "nodePtr_");
        if (!(nodePtr.IsEmpty() || nodePtr->IsNull() || nodePtr->IsUndefined())) {
            auto* node = nodePtr->ToNativePointer(vm)->Value();
            auto* myUINode = reinterpret_cast<NG::UINode*>(node);
            if (!myUINode) {
                return nullptr;
            }
            auto refPtrUINode = AceType::Claim(myUINode);
            return refPtrUINode;
        }
    }
    return nullptr;
}

void UpdateWaterFlowFooterContent(EcmaVM* vm, FrameNode* frameNode, const Local<JSValueRef>& args, bool isJsView)
{
    CHECK_NULL_VOID(vm);
    CHECK_NULL_VOID(args->IsObject(vm));
    auto footerJsObject = args->ToObject(vm);
    if (ArkTSUtils::HasProperty(vm, footerJsObject, "builderNode_")) {
        RefPtr<NG::UINode> refPtrUINode = SetWaterFlowBuilderNode(vm, footerJsObject);
        GetArkUINodeModifiers()->getWaterFlowModifier()->setWaterflowFooterWithFrameNode(
            reinterpret_cast<ArkUINodeHandle>(frameNode), AceType::RawPtr(refPtrUINode));
    } else if (isJsView) {
        GetArkUINodeModifiers()->getWaterFlowModifier()->setWaterflowFooterWithFrameNode(
            reinterpret_cast<ArkUINodeHandle>(frameNode), nullptr);
    }
}

void SetWaterFlowFooterContent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> footerContentArgs = runtimeCallInfo->GetCallArgRef(NUM_4);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_VOID(GetNativeNode(nativeNode, nodeArg, vm), false);
    FrameNode* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    bool isJSView = nodeArg->IsBoolean() && nodeArg->ToBoolean(vm)->Value();
    if (!footerContentArgs->IsNull() && footerContentArgs->IsObject(vm)) {
        UpdateWaterFlowFooterContent(vm, frameNode, footerContentArgs, isJSView);
    } else if (isJSView) {
        GetArkUINodeModifiers()->getWaterFlowModifier()->setWaterflowFooterWithFrameNode(
            reinterpret_cast<ArkUINodeHandle>(frameNode), nullptr);
    }
}

void SetWaterFlowFooter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> footer = runtimeCallInfo->GetCallArgRef(NUM_5);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_VOID(GetNativeNode(nativeNode, nodeArg, vm), false);
    FrameNode* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    bool isJSView = nodeArg->IsBoolean() && nodeArg->ToBoolean(vm)->Value();
    if (!footer->IsNull() && footer->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> builderFunc = footer->ToObject(vm);
        std::function<void()> footerAction = [vm, frameNode, func = panda::CopyableGlobal(vm, builderFunc),
                                                 isJSView]() {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
            if (isJSView) {
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            }
        };
        GetArkUINodeModifiers()->getWaterFlowModifier()->setFooterCallback(nativeNode, &footerAction);
    }
}

std::optional<PresetFillType> ParsePresetFillType(const EcmaVM* vm, const Local<JSValueRef>& jsValue)
{
    int32_t presetFillType = 0;
    if (ArkTSUtils::ParseJsInt32(vm, jsValue, presetFillType) &&
        InRegion(static_cast<int32_t>(PresetFillType::BREAKPOINT_DEFAULT),
            static_cast<int32_t>(PresetFillType::BREAKPOINT_SM2MD3LG5), presetFillType)) {
        return static_cast<PresetFillType>(presetFillType);
    } else {
        return std::nullopt;
    }
}

std::string ParseBarWidth(const EcmaVM* vm, const Local<JSValueRef>& jsValue)
{
    CalcDimension scrollBarWidth;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, jsValue, scrollBarWidth) || jsValue->IsNull() || jsValue->IsUndefined() ||
        (jsValue->IsString(vm) && jsValue->ToString(vm)->ToString(vm).empty()) ||
        LessNotEqual(scrollBarWidth.Value(), 0.0) || scrollBarWidth.Unit() == DimensionUnit::PERCENT) {
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, "");
        auto theme = pipelineContext->GetTheme<ScrollBarTheme>();
        CHECK_NULL_RETURN(theme, "");
        scrollBarWidth = theme->GetNormalWidth();
    }
    return scrollBarWidth.ToString();
}

void SetWaterFlowFooterOrSection(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, const ArkUINodeHandle& nativeNode)
{
    CHECK_NULL_VOID(vm);
    Local<JSValueRef> sectionsArgs = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> footerContentArgs = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> footerArgs = runtimeCallInfo->GetCallArgRef(NUM_5);
    if (!sectionsArgs->IsNull() && sectionsArgs->IsObject(vm)) {
        // set sections only when sections exist
        SetWaterFlowSections(runtimeCallInfo);
    } else {
        // reset sections and set footer when no sections exist
        GetArkUINodeModifiers()->getWaterFlowModifier()->resetWaterFlowSections(nativeNode);
        // check footerContent first
        if (!footerContentArgs->IsNull() && footerContentArgs->IsObject(vm)) {
            SetWaterFlowFooterContent(runtimeCallInfo);
            return;
        }
        // set footer if no footerContent
        if (!footerArgs->IsNull() && footerArgs->IsFunction(vm)) {
            SetWaterFlowFooter(runtimeCallInfo);
        }
    }
}
} // namespace

void WaterFlowBridge::RegisterWaterFlowAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = {
        "create",
        "resetColumnsTemplate",
        "setColumnsTemplate",
        "resetRowsTemplate",
        "setRowsTemplate",
        "resetEnableScrollInteraction",
        "setEnableScrollInteraction",
        "resetColumnsGap",
        "setColumnsGap",
        "resetRowsGap",
        "setRowsGap",
        "resetItemConstraintSize",
        "setItemConstraintSize",
        "resetLayoutDirection",
        "setLayoutDirection",
        "resetNestedScroll",
        "setNestedScroll",
        "resetFriction",
        "setFriction",
        "resetScrollBar",
        "setScrollBar",
        "resetScrollBarWidth",
        "setScrollBarWidth",
        "resetScrollBarColor",
        "setScrollBarColor",
        "resetCachedCount",
        "setCachedCount",
        "resetSyncLoad",
        "setSyncLoad",
        "resetWaterFlowInitialize",
        "setWaterFlowInitialize",
        "resetOnScrollIndex",
        "setOnScrollIndex",
        "setWaterFlowScroller",
        "setOnScroll",
        "setOnScrollStart",
        "setOnScrollStop",
        "setJSOnScrollIndex",
        "setOnReachStart",
        "setOnReachEnd",
        "setOnScrollFrameBegin",
        "setJSColumnsGap",
        "setJSRowsGap",
        "setJSColumnsTemplate",
        "setJSItemConstraintSize",
        "setJSScrollBar",
        "setJSScrollBarWidth",
        "setJSScrollBarColor",
    };
    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(vm, WaterFlowBridge::CreateWaterFlow),
        panda::FunctionRef::New(vm, WaterFlowBridge::ResetColumnsTemplate),
        panda::FunctionRef::New(vm, WaterFlowBridge::SetColumnsTemplate),
        panda::FunctionRef::New(vm, WaterFlowBridge::ResetRowsTemplate),
        panda::FunctionRef::New(vm, WaterFlowBridge::SetRowsTemplate),
        panda::FunctionRef::New(vm, WaterFlowBridge::ResetEnableScrollInteraction),
        panda::FunctionRef::New(vm, WaterFlowBridge::SetEnableScrollInteraction),
        panda::FunctionRef::New(vm, WaterFlowBridge::ResetColumnsGap),
        panda::FunctionRef::New(vm, WaterFlowBridge::SetColumnsGap),
        panda::FunctionRef::New(vm, WaterFlowBridge::ResetRowsGap),
        panda::FunctionRef::New(vm, WaterFlowBridge::SetRowsGap),
        panda::FunctionRef::New(vm, WaterFlowBridge::ResetItemConstraintSize),
        panda::FunctionRef::New(vm, WaterFlowBridge::SetItemConstraintSize),
        panda::FunctionRef::New(vm, WaterFlowBridge::ResetLayoutDirection),
        panda::FunctionRef::New(vm, WaterFlowBridge::SetLayoutDirection),
        panda::FunctionRef::New(vm, WaterFlowBridge::ResetNestedScroll),
        panda::FunctionRef::New(vm, WaterFlowBridge::SetNestedScroll),
        panda::FunctionRef::New(vm, WaterFlowBridge::ResetFriction),
        panda::FunctionRef::New(vm, WaterFlowBridge::SetFriction),
        panda::FunctionRef::New(vm, WaterFlowBridge::ResetScrollBar),
        panda::FunctionRef::New(vm, WaterFlowBridge::SetScrollBar),
        panda::FunctionRef::New(vm, WaterFlowBridge::ResetScrollBarWidth),
        panda::FunctionRef::New(vm, WaterFlowBridge::SetScrollBarWidth),
        panda::FunctionRef::New(vm, WaterFlowBridge::ResetScrollBarColor),
        panda::FunctionRef::New(vm, WaterFlowBridge::SetScrollBarColor),
        panda::FunctionRef::New(vm, WaterFlowBridge::ResetCachedCount),
        panda::FunctionRef::New(vm, WaterFlowBridge::SetCachedCount),
        panda::FunctionRef::New(vm, WaterFlowBridge::ResetSyncLoad),
        panda::FunctionRef::New(vm, WaterFlowBridge::SetSyncLoad),
        panda::FunctionRef::New(vm, WaterFlowBridge::ResetWaterFlowInitialize),
        panda::FunctionRef::New(vm, WaterFlowBridge::SetWaterFlowInitialize),
        panda::FunctionRef::New(vm, WaterFlowBridge::ResetOnWaterFlowScrollIndex),
        panda::FunctionRef::New(vm, WaterFlowBridge::SetOnWaterFlowScrollIndex),
        panda::FunctionRef::New(vm, WaterFlowBridge::SetWaterFlowScroller),
        panda::FunctionRef::New(vm, WaterFlowBridge::SetOnScroll),
        panda::FunctionRef::New(vm, WaterFlowBridge::SetOnScrollStart),
        panda::FunctionRef::New(vm, WaterFlowBridge::SetOnScrollStop),
        panda::FunctionRef::New(vm, WaterFlowBridge::SetOnScrollIndex),
        panda::FunctionRef::New(vm, WaterFlowBridge::SetOnReachStart),
        panda::FunctionRef::New(vm, WaterFlowBridge::SetOnReachEnd),
        panda::FunctionRef::New(vm, WaterFlowBridge::SetOnScrollFrameBegin),
        panda::FunctionRef::New(vm, WaterFlowBridge::SetJSColumnsGap),
        panda::FunctionRef::New(vm, WaterFlowBridge::SetJSRowsGap),
        panda::FunctionRef::New(vm, WaterFlowBridge::SetJSColumnsTemplate),
        panda::FunctionRef::New(vm, WaterFlowBridge::SetJSItemConstraintSize),
        panda::FunctionRef::New(vm, WaterFlowBridge::SetJSScrollBar),
        panda::FunctionRef::New(vm, WaterFlowBridge::SetJSScrollBarWidth),
        panda::FunctionRef::New(vm, WaterFlowBridge::SetJSScrollBarColor),
    };
    auto waterflow = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "waterFlow"), waterflow);
}

ArkUINativeModuleValue WaterFlowBridge::CreateWaterFlow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));

    GetArkUINodeModifiers()->getWaterFlowModifier()->create();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetColumnsTemplate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetColumnsTemplate(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetColumnsTemplate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> columnsTemplateArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (columnsTemplateArg->IsObject(vm)) {
        auto value = BREAKPOINT_DEFAULT;
        GetArkUINodeModifiers()->getWaterFlowModifier()->resetColumnsTemplate(nativeNode);
        GetArkUINodeModifiers()->getWaterFlowModifier()->setItemFillPolicy(nativeNode, value);
        auto stringRef = panda::StringRef::NewFromUtf8(vm, "fillType");
        auto fillTypeArg = columnsTemplateArg->ToObject(vm)->Get(vm, stringRef);
        if (!fillTypeArg->IsNull() && ArkTSUtils::ParseJsInt32(vm, fillTypeArg, value)) {
            if (InRegion(BREAKPOINT_DEFAULT, BREAKPOINT_SM2MD3LG5, value)) {
                GetArkUINodeModifiers()->getWaterFlowModifier()->setItemFillPolicy(nativeNode, value);
            }
        }
    } else if (columnsTemplateArg->IsUndefined() || !columnsTemplateArg->IsString(vm)) {
        GetArkUINodeModifiers()->getWaterFlowModifier()->resetColumnsTemplate(nativeNode);
    } else {
        std::string columnsTemplateValue = columnsTemplateArg->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getWaterFlowModifier()->resetItemFillPolicy(nativeNode);
        GetArkUINodeModifiers()->getWaterFlowModifier()->setColumnsTemplate(nativeNode, columnsTemplateValue.c_str());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetRowsTemplate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetRowsTemplate(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetRowsTemplate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> rowsTemplateArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(GetNativeNode(nativeNode, nodeArg, vm), false, panda::JSValueRef::Undefined(vm));
    std::string rowsTemplateValue = rowsTemplateArg->ToString(vm)->ToString(vm);
    GetArkUINodeModifiers()->getWaterFlowModifier()->setRowsTemplate(nativeNode, rowsTemplateValue.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetEnableScrollInteraction(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> enableScrollInteractionArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(GetNativeNode(nativeNode, nodeArg, vm), false, panda::JSValueRef::Undefined(vm));
    if (enableScrollInteractionArg->IsUndefined() || !enableScrollInteractionArg->IsBoolean()) {
        GetArkUINodeModifiers()->getWaterFlowModifier()->setWaterFlowEnableScrollInteraction(nativeNode, true);
        return panda::JSValueRef::Undefined(vm);
    }
    bool flag = enableScrollInteractionArg->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getWaterFlowModifier()->setWaterFlowEnableScrollInteraction(nativeNode, flag);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetEnableScrollInteraction(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetWaterFlowEnableScrollInteraction(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetColumnsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetColumnsGap(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetColumnsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> columnsGapArg = runtimeCallInfo->GetCallArgRef(NUM_1);

    CalcDimension columnsGap;
    std::string calcStr;
    RefPtr<ResourceObject> columnGapResObj;
    if (columnsGapArg->IsUndefined() ||
        !ArkTSUtils::ParseJsDimensionVpNG(vm, columnsGapArg, columnsGap, columnGapResObj)) {
        GetArkUINodeModifiers()->getWaterFlowModifier()->resetColumnsGap(nativeNode);
    } else {
        if (LessNotEqual(columnsGap.Value(), DIMENSION_DEFAULT)) {
            columnsGap.SetValue(DIMENSION_DEFAULT);
        }

        auto columnGapRawPtr = AceType::RawPtr(columnGapResObj);
        if (columnsGap.Unit() == DimensionUnit::CALC) {
            GetArkUINodeModifiers()->getWaterFlowModifier()->setColumnsGap(nativeNode, NUM_0,
                static_cast<int32_t>(columnsGap.Unit()), columnsGap.CalcValue().c_str(), columnGapRawPtr);
        } else {
            GetArkUINodeModifiers()->getWaterFlowModifier()->setColumnsGap(nativeNode, columnsGap.Value(),
                static_cast<int32_t>(columnsGap.Unit()), calcStr.c_str(), columnGapRawPtr);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetRowsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetRowsGap(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetRowsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> rowsGapArg = runtimeCallInfo->GetCallArgRef(NUM_1);

    CalcDimension rowGap;
    std::string calcStr;
    RefPtr<ResourceObject> rowGapResObj;
    if (rowsGapArg->IsUndefined() || !ArkTSUtils::ParseJsDimensionVpNG(vm, rowsGapArg, rowGap, rowGapResObj)) {
        GetArkUINodeModifiers()->getWaterFlowModifier()->resetRowsGap(nativeNode);
    } else {
        if (LessNotEqual(rowGap.Value(), DIMENSION_DEFAULT)) {
            rowGap.SetValue(DIMENSION_DEFAULT);
        }

        auto rowGapRawPtr = AceType::RawPtr(rowGapResObj);
        if (rowGap.Unit() == DimensionUnit::CALC) {
            GetArkUINodeModifiers()->getWaterFlowModifier()->setRowsGap(
                nativeNode, 0, static_cast<int32_t>(rowGap.Unit()), rowGap.CalcValue().c_str(), rowGapRawPtr);
        } else {
            GetArkUINodeModifiers()->getWaterFlowModifier()->setRowsGap(
                nativeNode, rowGap.Value(), static_cast<int32_t>(rowGap.Unit()), calcStr.c_str(), rowGapRawPtr);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetItemConstraintSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> minWidthValue = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> maxWidthValue = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> minHeightValue = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> maxHeightValue = runtimeCallInfo->GetCallArgRef(NUM_4);
    CalcDimension minWidth;
    CalcDimension maxWidth;
    CalcDimension minHeight;
    CalcDimension maxHeight;
    std::string calcMinWidthStr;
    std::string calcMaxWidthStr;
    std::string calcMinHeightStr;
    std::string calcMaxHeightStr;
    RefPtr<ResourceObject> itemMinWidthResObj;
    RefPtr<ResourceObject> itemMaxWidthResObj;
    RefPtr<ResourceObject> itemMinHeightResObj;
    RefPtr<ResourceObject> itemMaxHeightResObj;
    if (minWidthValue->IsUndefined() ||
        !ArkTSUtils::ParseJsDimensionVp(vm, minWidthValue, minWidth, itemMinWidthResObj, false)) {
        GetArkUINodeModifiers()->getWaterFlowModifier()->resetItemMinWidth(nativeNode);
    } else {
        auto itemMinWidthRawPtr = AceType::RawPtr(itemMinWidthResObj);
        SetItemConstraintSizeSendParams(minWidth, calcMinWidthStr);
        GetArkUINodeModifiers()->getWaterFlowModifier()->setItemMinWidth(nativeNode, minWidth.Value(),
            static_cast<int32_t>(minWidth.Unit()), calcMinWidthStr.c_str(), itemMinWidthRawPtr);
    }
    if (maxWidthValue->IsUndefined() ||
        !ArkTSUtils::ParseJsDimensionVp(vm, maxWidthValue, maxWidth, itemMaxWidthResObj, false)) {
        GetArkUINodeModifiers()->getWaterFlowModifier()->resetItemMaxWidth(nativeNode);
    } else {
        auto itemMaxWidthRawPtr = AceType::RawPtr(itemMaxWidthResObj);
        SetItemConstraintSizeSendParams(maxWidth, calcMaxWidthStr);
        GetArkUINodeModifiers()->getWaterFlowModifier()->setItemMaxWidth(nativeNode, maxWidth.Value(),
            static_cast<int32_t>(maxWidth.Unit()), calcMaxWidthStr.c_str(), itemMaxWidthRawPtr);
    }
    if (minHeightValue->IsUndefined() ||
        !ArkTSUtils::ParseJsDimensionVp(vm, minHeightValue, minHeight, itemMinHeightResObj, false)) {
        GetArkUINodeModifiers()->getWaterFlowModifier()->resetItemMinHeight(nativeNode);
    } else {
        auto itemMinHeightRawPtr = AceType::RawPtr(itemMinHeightResObj);
        SetItemConstraintSizeSendParams(minHeight, calcMinHeightStr);
        GetArkUINodeModifiers()->getWaterFlowModifier()->setItemMinHeight(nativeNode, minHeight.Value(),
            static_cast<int32_t>(minHeight.Unit()), calcMinHeightStr.c_str(), itemMinHeightRawPtr);
    }
    if (maxHeightValue->IsUndefined() ||
        !ArkTSUtils::ParseJsDimensionVp(vm, maxHeightValue, maxHeight, itemMaxHeightResObj, false)) {
        GetArkUINodeModifiers()->getWaterFlowModifier()->resetItemMaxHeight(nativeNode);
    } else {
        auto itemMaxHeightRawPtr = AceType::RawPtr(itemMaxHeightResObj);
        SetItemConstraintSizeSendParams(maxHeight, calcMaxHeightStr);
        GetArkUINodeModifiers()->getWaterFlowModifier()->setItemMaxHeight(nativeNode, maxHeight.Value(),
            static_cast<int32_t>(maxHeight.Unit()), calcMaxHeightStr.c_str(), itemMaxHeightRawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetItemConstraintSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetItemMaxHeight(nativeNode);
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetItemMaxWidth(nativeNode);
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetItemMinHeight(nativeNode);
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetItemMinWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetLayoutDirection(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> layoutDirectionArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(GetNativeNode(nativeNode, nodeArg, vm), false, panda::JSValueRef::Undefined(vm));
    auto value = static_cast<int32_t>(FlexDirection::COLUMN);
    if (!layoutDirectionArg->IsUndefined()) {
        ArkTSUtils::ParseJsInteger(vm, layoutDirectionArg, value);
    }
    if (value >= NUM_0 && value < static_cast<int32_t>(LAYOUT_DIRECTION.size())) {
        GetArkUINodeModifiers()->getWaterFlowModifier()->setLayoutDirection(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getWaterFlowModifier()->resetLayoutDirection(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetLayoutDirection(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetLayoutDirection(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetNestedScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> scrollForwardValue;
    Local<JSValueRef> scrollBackwardValue;
    ArkUINodeHandle nativeNode = nullptr;
    int32_t froward = NUM_0;
    int32_t backward = NUM_0;
    bool isJSView = nodeArg->IsBoolean() && nodeArg->ToBoolean(vm)->Value();
    if (isJSView) {
        Local<JSValueRef> obj = runtimeCallInfo->GetCallArgRef(NUM_1);
        if (!obj->IsObject(vm)) {
            GetArkUINodeModifiers()->getWaterFlowModifier()->setWaterFlowNestedScroll(nativeNode, froward, backward);
            return panda::JSValueRef::Undefined(vm);
        }
        scrollForwardValue = ArkTSUtils::GetProperty(vm, obj, "scrollForward");
        scrollBackwardValue = ArkTSUtils::GetProperty(vm, obj, "scrollBackward");
        CHECK_EQUAL_RETURN(GetNativeNode(nativeNode, nodeArg, vm), false, panda::JSValueRef::Undefined(vm));
    } else {
        scrollForwardValue = runtimeCallInfo->GetCallArgRef(NUM_1);
        scrollBackwardValue = runtimeCallInfo->GetCallArgRef(NUM_2);
        CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
        nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    }
    ArkTSUtils::ParseJsInteger(vm, scrollForwardValue, froward);
    if (froward < static_cast<int32_t>(NestedScrollMode::SELF_ONLY) ||
        froward > static_cast<int32_t>(NestedScrollMode::PARALLEL)) {
        froward = NUM_0;
    }
    ArkTSUtils::ParseJsInteger(vm, scrollBackwardValue, backward);
    if (backward < static_cast<int32_t>(NestedScrollMode::SELF_ONLY) ||
        backward > static_cast<int32_t>(NestedScrollMode::PARALLEL)) {
        backward = NUM_0;
    }
    GetArkUINodeModifiers()->getWaterFlowModifier()->setWaterFlowNestedScroll(nativeNode, froward, backward);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetNestedScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetWaterFlowNestedScroll(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetFriction(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> frictionArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(GetNativeNode(nativeNode, nodeArg, vm), false, panda::JSValueRef::Undefined(vm));
    double friction = FRICTION_DEFAULT;
    RefPtr<ResourceObject> frictionResObj;
    if (!ArkTSUtils::ParseJsDouble(vm, frictionArg, friction, frictionResObj)) {
        bool isJSView = nodeArg->IsBoolean() && nodeArg->ToBoolean(vm)->Value();
        if (isJSView) {
            GetArkUINodeModifiers()->getWaterFlowModifier()->setWaterFlowFriction(
                nativeNode, static_cast<ArkUI_Float32>(FRICTION_DEFAULT), AceType::RawPtr(frictionResObj));
        } else {
            GetArkUINodeModifiers()->getWaterFlowModifier()->resetWaterFlowFriction(nativeNode);
        }
    } else {
        auto frictionRawPtr = AceType::RawPtr(frictionResObj);
        GetArkUINodeModifiers()->getWaterFlowModifier()->setWaterFlowFriction(
            nativeNode, static_cast<ArkUI_Float32>(friction), frictionRawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetFriction(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetWaterFlowFriction(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetScrollBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    int32_t barState = 0;
    if (!ArkTSUtils::ParseJsInteger(vm, secondArg, barState) || barState < 0 || barState >= DISPLAY_MODE_SIZE) {
        GetArkUINodeModifiers()->getWaterFlowModifier()->resetWaterFlowScrollBar(nativeNode);
    } else {
        GetArkUINodeModifiers()->getWaterFlowModifier()->setWaterFlowScrollBar(nativeNode, barState);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetScrollBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> argNode = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(argNode->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(argNode->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetWaterFlowScrollBar(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetScrollBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> scrollBarArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());

    CalcDimension scrollBarWidth;
    if (!ArkTSUtils::ParseJsDimension(vm, scrollBarArg, scrollBarWidth, DimensionUnit::VP) || scrollBarArg->IsNull() ||
        scrollBarArg->IsUndefined() || (scrollBarArg->IsString(vm) && scrollBarWidth.ToString().empty()) ||
        LessNotEqual(scrollBarWidth.Value(), 0.0) || scrollBarWidth.Unit() == DimensionUnit::PERCENT) {
        GetArkUINodeModifiers()->getWaterFlowModifier()->resetWaterFlowScrollBarWidth(nativeNode);
    } else {
        GetArkUINodeModifiers()->getWaterFlowModifier()->setWaterFlowScrollBarWidth(
            nativeNode, scrollBarWidth.ToString().c_str());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetScrollBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> argNode = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(argNode->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(argNode->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetWaterFlowScrollBarWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetScrollBarColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> argNode = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> argColor = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(argNode->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(argNode->ToNativePointer(vm)->Value());
    Color color;
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> resObj;
        nativeNode = nativeNode
                         ? nativeNode
                         : reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
        if (!ArkTSUtils::ParseJsColorAlpha(vm, argColor, color, resObj, nodeInfo) || color.ColorToString().empty()) {
            GetArkUINodeModifiers()->getWaterFlowModifier()->resetWaterFlowScrollBarColor(nativeNode);
        } else {
            GetArkUINodeModifiers()->getWaterFlowModifier()->setWaterFlowScrollBarColor(
                nativeNode, color.ColorToString().c_str());
        }
        GetArkUINodeModifiers()->getWaterFlowModifier()->createWaterFlowScrollBarColorWithResourceObj(
            nativeNode, AceType::RawPtr(resObj));
        return panda::JSValueRef::Undefined(vm);
    }
    if (!ArkTSUtils::ParseJsColorAlpha(vm, argColor, color) || color.ColorToString().empty()) {
        GetArkUINodeModifiers()->getWaterFlowModifier()->resetWaterFlowScrollBarColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getWaterFlowModifier()->setWaterFlowScrollBarColor(
            nativeNode, color.ColorToString().c_str());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetScrollBarColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> argNode = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(argNode->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(argNode->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetWaterFlowScrollBarColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetCachedCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> argNode = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> argCachedCount = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> argShow = runtimeCallInfo->GetCallArgRef(NUM_2);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(GetNativeNode(nativeNode, argNode, vm), false, panda::JSValueRef::Undefined(vm));
    int32_t cachedCount = 0;
    if (!ArkTSUtils::ParseJsInteger(vm, argCachedCount, cachedCount) || cachedCount < 0) {
        GetArkUINodeModifiers()->getWaterFlowModifier()->resetCachedCount(nativeNode);
    } else {
        GetArkUINodeModifiers()->getWaterFlowModifier()->setCachedCount(nativeNode, cachedCount);
    }

    bool show = !argShow.IsNull() && argShow->IsTrue();
    GetArkUINodeModifiers()->getWaterFlowModifier()->setShowCached(nativeNode, show);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetCachedCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> argNode = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(argNode->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(argNode->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetCachedCount(nativeNode);
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetShowCached(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetSyncLoad(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> argSyncLoad = runtimeCallInfo->GetCallArgRef(NUM_1);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(GetNativeNode(nativeNode, node, vm), false, panda::JSValueRef::Undefined(vm));
    bool syncLoad = true;
    bool isJSView = node->IsBoolean() && node->ToBoolean(vm)->Value();
    if (isJSView && argSyncLoad->IsBoolean()) {
        // jsview
        syncLoad = argSyncLoad->BooleaValue(vm);
        GetArkUINodeModifiers()->getWaterFlowModifier()->setSyncLoad(nativeNode, syncLoad);
        return panda::JSValueRef::Undefined(vm);
    }
    if (!argSyncLoad->IsUndefined() && !argSyncLoad->IsNull()) {
        syncLoad = argSyncLoad->BooleaValue(vm);
    }

    GetArkUINodeModifiers()->getWaterFlowModifier()->setSyncLoad(nativeNode, syncLoad);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetSyncLoad(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetSyncLoad(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetWaterFlowScroller(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(GetNativeNode(nativeNode, nodeArg, vm), false, panda::JSValueRef::Undefined(vm));

    bool isJSView = nodeArg->IsBoolean() && nodeArg->ToBoolean(vm)->Value();
    Local<JSValueRef> scrollerArg = runtimeCallInfo->GetCallArgRef(1);
    if (!scrollerArg->IsNull() && scrollerArg->IsObject(vm)) {
        Local<ObjectRef> obj = scrollerArg->ToObject(vm);
        Framework::JSScroller* jsScroller = static_cast<Framework::JSScroller*>(obj->GetNativePointerField(vm, 0));

        if (jsScroller) {
            jsScroller->SetInstanceId(Container::CurrentId());
            auto positionController = GetArkUINodeModifiers()->getWaterFlowModifier()->getScrollController(nativeNode);
            auto nodePositionController =
                AceType::Claim(reinterpret_cast<OHOS::Ace::ScrollControllerBase*>(positionController));
            jsScroller->SetController(nodePositionController);
            // Init scroll bar proxy.
            auto proxy = jsScroller->GetScrollBarProxy();
            if (!proxy) {
                auto* tmp = reinterpret_cast<ScrollProxy*>(
                    GetArkUINodeModifiers()->getWaterFlowModifier()->createScrollBarProxy());
                proxy = AceType::Claim(tmp);
                jsScroller->SetScrollBarProxy(proxy);
            }
            auto proxyPtr = reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(proxy));
            GetArkUINodeModifiers()->getWaterFlowModifier()->setWaterFlowScroller(
                nativeNode, positionController, proxyPtr);
        }
    } else if (!isJSView) {
        auto positionController = AceType::MakeRefPtr<ScrollableController>();
        auto controller = reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(positionController));
        auto* tmp =
            reinterpret_cast<ScrollProxy*>(GetArkUINodeModifiers()->getWaterFlowModifier()->createScrollBarProxy());
        auto proxy = AceType::Claim(tmp);
        auto proxyPtr = reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(proxy));
        GetArkUINodeModifiers()->getWaterFlowModifier()->setWaterFlowScroller(nativeNode, controller, proxyPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetWaterFlowInitialize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> layoutModeArgs = runtimeCallInfo->GetCallArgRef(3); // 3 is the index of layoutMode
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(GetNativeNode(nativeNode, nodeArg, vm), false, panda::JSValueRef::Undefined(vm));

    SetWaterFlowScroller(runtimeCallInfo);

    if (layoutModeArgs->IsUndefined() || layoutModeArgs->IsNull() || !layoutModeArgs->IsNumber()) {
        GetArkUINodeModifiers()->getWaterFlowModifier()->resetWaterFlowLayoutMode(nativeNode);
        bool isJSView = nodeArg->IsBoolean() && nodeArg->ToBoolean(vm)->Value();
        if (isJSView) {
            SetWaterFlowFooterOrSection(vm, runtimeCallInfo, nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }
        SetWaterFlowFooter(runtimeCallInfo);
        SetWaterFlowFooterContent(runtimeCallInfo);
        SetWaterFlowSections(runtimeCallInfo);
    } else {
        uint32_t layoutMode = layoutModeArgs->Uint32Value(vm);
        if (layoutMode < static_cast<uint32_t>(NG::WaterFlowLayoutMode::TOP_DOWN) ||
            layoutMode > static_cast<uint32_t>(NG::WaterFlowLayoutMode::SLIDING_WINDOW)) {
            layoutMode = static_cast<uint32_t>(NG::WaterFlowLayoutMode::TOP_DOWN);
        }
        GetArkUINodeModifiers()->getWaterFlowModifier()->setWaterFlowLayoutMode(nativeNode, layoutMode);
        SetWaterFlowFooterOrSection(vm, runtimeCallInfo, nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetWaterFlowInitialize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    auto positionController = AceType::MakeRefPtr<ScrollableController>();
    auto controller = reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(positionController));
    auto* tmp = reinterpret_cast<ScrollProxy*>(GetArkUINodeModifiers()->getWaterFlowModifier()->createScrollBarProxy());
    auto proxy = AceType::Claim(tmp);
    auto proxyPtr = reinterpret_cast<ArkUINodeHandle>(OHOS::Ace::AceType::RawPtr(proxy));
    GetArkUINodeModifiers()->getWaterFlowModifier()->setWaterFlowScroller(nativeNode, controller, proxyPtr);
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetWaterFlowSections(nativeNode);
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetWaterFlowLayoutMode(nativeNode);
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetWaterflowFooter(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetOnWaterFlowScrollIndex(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWaterFlowModifier()->resetOnWaterFlowScrollIndex(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void(int32_t, int32_t)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                         const int32_t first, const int32_t last) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));

        panda::Local<panda::NumberRef> firstParam = panda::NumberRef::New(vm, first);
        panda::Local<panda::NumberRef> lastParam = panda::NumberRef::New(vm, last);
        // 2: Array length
        panda::Local<panda::JSValueRef> params[2] = { firstParam, lastParam };
        func->Call(vm, func.ToLocal(), params, 2); // 2: Array length
    };
    GetArkUINodeModifiers()->getWaterFlowModifier()->setOnWaterFlowScrollIndexCallBack(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetOnWaterFlowScrollIndex(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetOnWaterFlowScrollIndex(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetOnScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> funcArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(GetNativeNode(nativeNode, nodeArg, vm), false, panda::JSValueRef::Undefined(vm));
    if (!funcArg->IsFunction(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    bool isJSView = nodeArg->IsBoolean() && nodeArg->ToBoolean(vm)->Value();
    Local<panda::FunctionRef> funcRef = funcArg->ToObject(vm);
    std::function<void(const CalcDimension&, const ScrollState&)> onScroll =
        [vm, func = panda::CopyableGlobal(vm, funcRef), isJSView](
            const CalcDimension& scrollOffset, const ScrollState& scrollState) {
            CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            auto params = ArkTSUtils::ConvertToJSValues(vm, scrollOffset, scrollState);
            auto result = func->Call(vm, func.ToLocal(), params.data(), static_cast<int32_t>(params.size()));
            if (isJSView) {
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            }
        };
    GetArkUINodeModifiers()->getWaterFlowModifier()->setOnScroll(nativeNode, reinterpret_cast<void*>(&onScroll));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetOnScrollStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> funcArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(GetNativeNode(nativeNode, nodeArg, vm), false, panda::JSValueRef::Undefined(vm));
    if (!funcArg->IsFunction(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    bool isJSView = nodeArg->IsBoolean() && nodeArg->ToBoolean(vm)->Value();
    Local<panda::FunctionRef> funcRef = funcArg->ToObject(vm);
    std::function<void()> onScrollStart = [vm, func = panda::CopyableGlobal(vm, funcRef), isJSView]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
        if (isJSView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
        return;
    };
    GetArkUINodeModifiers()->getWaterFlowModifier()->setOnScrollStart(
        nativeNode, reinterpret_cast<void*>(&onScrollStart));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetOnScrollStop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> funcArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(GetNativeNode(nativeNode, nodeArg, vm), false, panda::JSValueRef::Undefined(vm));
    if (!funcArg->IsFunction(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    bool isJSView = nodeArg->IsBoolean() && nodeArg->ToBoolean(vm)->Value();
    Local<panda::FunctionRef> funcRef = funcArg->ToObject(vm);
    std::function<void()> onScrollStop = [vm, func = panda::CopyableGlobal(vm, funcRef), isJSView]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
        if (isJSView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
        return;
    };
    GetArkUINodeModifiers()->getWaterFlowModifier()->setOnScrollStop(
        nativeNode, reinterpret_cast<void*>(&onScrollStop));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetOnScrollIndex(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> funcArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(GetNativeNode(nativeNode, nodeArg, vm), false, panda::JSValueRef::Undefined(vm));
    if (!funcArg->IsFunction(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    bool isJSView = nodeArg->IsBoolean() && nodeArg->ToBoolean(vm)->Value();
    Local<panda::FunctionRef> funcRef = funcArg->ToObject(vm);
    std::function<void(const int32_t, const int32_t)> onScrollIndex =
        [vm, func = panda::CopyableGlobal(vm, funcRef), isJSView](const int32_t first, const int32_t last) {
            CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            auto params = ArkTSUtils::ConvertToJSValues(vm, first, last);
            auto result = func->Call(vm, func.ToLocal(), params.data(), static_cast<int32_t>(params.size()));
            if (isJSView) {
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            }
            UiSessionManager::GetInstance()->ReportComponentChangeEvent("event", "onScrollIndex");
            return;
        };
    GetArkUINodeModifiers()->getWaterFlowModifier()->setOnScrollIndex(
        nativeNode, reinterpret_cast<void*>(&onScrollIndex));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetOnReachStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> funcArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(GetNativeNode(nativeNode, nodeArg, vm), false, panda::JSValueRef::Undefined(vm));
    if (!funcArg->IsFunction(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    bool isJSView = nodeArg->IsBoolean() && nodeArg->ToBoolean(vm)->Value();
    Local<panda::FunctionRef> funcRef = funcArg->ToObject(vm);
    std::function<void()> onReachStart = [vm, func = panda::CopyableGlobal(vm, funcRef), isJSView]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
        if (isJSView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
        UiSessionManager::GetInstance()->ReportComponentChangeEvent("event", "onReachStart");
        return;
    };
    GetArkUINodeModifiers()->getWaterFlowModifier()->setOnReachStart(
        nativeNode, reinterpret_cast<void*>(&onReachStart));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetOnReachEnd(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> funcArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(GetNativeNode(nativeNode, nodeArg, vm), false, panda::JSValueRef::Undefined(vm));
    if (!funcArg->IsFunction(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    bool isJSView = nodeArg->IsBoolean() && nodeArg->ToBoolean(vm)->Value();
    Local<panda::FunctionRef> funcRef = funcArg->ToObject(vm);
    std::function<void()> onReachEnd = [vm, func = panda::CopyableGlobal(vm, funcRef), isJSView]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
        if (isJSView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
        UiSessionManager::GetInstance()->ReportComponentChangeEvent("event", "onReachEnd");
        return;
    };
    GetArkUINodeModifiers()->getWaterFlowModifier()->setOnReachEnd(nativeNode, reinterpret_cast<void*>(&onReachEnd));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetOnScrollFrameBegin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> funcArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(GetNativeNode(nativeNode, nodeArg, vm), false, panda::JSValueRef::Undefined(vm));
    if (!funcArg->IsFunction(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    bool isJSView = nodeArg->IsBoolean() && nodeArg->ToBoolean(vm)->Value();
    Local<panda::FunctionRef> funcRef = funcArg->ToObject(vm);
    std::function<ScrollFrameResult(const Dimension&, const ScrollState&)> onScrollBegin =
        [vm, func = panda::CopyableGlobal(vm, funcRef), isJSView](
            const Dimension& offset, const ScrollState& state) -> ScrollFrameResult {
        ScrollFrameResult scrollRes { .offset = offset };
        CHECK_EQUAL_RETURN(ArkTSUtils::CheckJavaScriptScope(vm), false, scrollRes);
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        auto params = ArkTSUtils::ConvertToJSValues(vm, offset, state);
        auto result = func->Call(vm, func.ToLocal(), params.data(), static_cast<int32_t>(params.size()));
        if (isJSView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
        if (result.IsEmpty() || result->IsUndefined() || result->IsNull()) {
            LOGE("Error calling onScrollFrameBegin, result is empty.");
            return scrollRes;
        }

        if (!result->IsObject(vm)) {
            LOGE("Error calling onScrollFrameBegin, result is not object.");
            return scrollRes;
        }

        auto resObj = result->ToObject(vm);
        auto dxRemainValue = ArkTSUtils::GetProperty(vm, resObj, "offsetRemain");
        if (dxRemainValue->IsNumber()) {
            scrollRes.offset = Dimension(dxRemainValue->ToNumber(vm)->Value(), DimensionUnit::VP);
        }
        return scrollRes;
    };
    GetArkUINodeModifiers()->getWaterFlowModifier()->setOnScrollFrameBegin(
        nativeNode, reinterpret_cast<void*>(&onScrollBegin));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetJSColumnsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_EQUAL_RETURN(GetNativeNode(nativeNode, nodeArg, vm), false, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> columnsGapArg = runtimeCallInfo->GetCallArgRef(NUM_1);

    CalcDimension colGap;
    std::string calcStr;
    RefPtr<ResourceObject> resObj;
    if (SystemProperties::ConfigChangePerform()) {
        if (!ArkTSUtils::ParseJsDimensionVp(vm, columnsGapArg, colGap, resObj) || colGap.Value() < 0) {
            colGap.SetValue(0.0);
        }
    } else if (!ArkTSUtils::ParseJsDimensionVp(vm, columnsGapArg, colGap) || colGap.Value() < 0) {
        colGap.SetValue(0.0);
    }
    auto columnGapRawPtr = AceType::RawPtr(resObj);
    if (colGap.Unit() == DimensionUnit::CALC) {
        GetArkUINodeModifiers()->getWaterFlowModifier()->setColumnsGap(
            nativeNode, NUM_0, static_cast<int32_t>(colGap.Unit()), colGap.CalcValue().c_str(), columnGapRawPtr);
    } else {
        GetArkUINodeModifiers()->getWaterFlowModifier()->setColumnsGap(nativeNode,
            static_cast<ArkUI_Float32>(colGap.Value()), static_cast<int32_t>(colGap.Unit()), calcStr.c_str(),
            columnGapRawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetJSRowsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_EQUAL_RETURN(GetNativeNode(nativeNode, nodeArg, vm), false, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> rowsGapArg = runtimeCallInfo->GetCallArgRef(NUM_1);

    CalcDimension rowGap;
    std::string calcStr;
    RefPtr<ResourceObject> resObj;
    if (SystemProperties::ConfigChangePerform()) {
        if (!ArkTSUtils::ParseJsDimensionVp(vm, rowsGapArg, rowGap, resObj) || rowGap.Value() < 0) {
            rowGap.SetValue(0.0);
        }
    } else if (!ArkTSUtils::ParseJsDimensionVp(vm, rowsGapArg, rowGap) || rowGap.Value() < 0) {
        rowGap.SetValue(0.0);
    }
    auto rowGapRawPtr = AceType::RawPtr(resObj);
    if (rowGap.Unit() == DimensionUnit::CALC) {
        GetArkUINodeModifiers()->getWaterFlowModifier()->setRowsGap(
            nativeNode, 0, static_cast<int32_t>(rowGap.Unit()), rowGap.CalcValue().c_str(), rowGapRawPtr);
    } else {
        GetArkUINodeModifiers()->getWaterFlowModifier()->setRowsGap(nativeNode,
            static_cast<ArkUI_Float32>(rowGap.Value()), static_cast<int32_t>(rowGap.Unit()), calcStr.c_str(),
            rowGapRawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetJSColumnsTemplate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_EQUAL_RETURN(GetNativeNode(nativeNode, nodeArg, vm), false, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> columnsTemplateArg = runtimeCallInfo->GetCallArgRef(NUM_1);

    if (columnsTemplateArg->IsObject(vm)) {
        auto columnsTemplateObj = columnsTemplateArg->ToObject(vm);
        auto fillTypeParam = ArkTSUtils::GetProperty(vm, columnsTemplateObj, "fillType");
        if (!fillTypeParam->IsNull()) {
            auto type = ParsePresetFillType(vm, fillTypeParam);
            GetArkUINodeModifiers()->getWaterFlowModifier()->setItemFillPolicy(
                nativeNode, static_cast<ArkUI_Int32>(type.value_or(PresetFillType::BREAKPOINT_DEFAULT)));
        } else {
            GetArkUINodeModifiers()->getWaterFlowModifier()->setItemFillPolicy(
                nativeNode, static_cast<ArkUI_Int32>(PresetFillType::BREAKPOINT_DEFAULT));
        }
    } else {
        auto str = columnsTemplateArg->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getWaterFlowModifier()->resetItemFillPolicy(nativeNode);
        GetArkUINodeModifiers()->getWaterFlowModifier()->setColumnsTemplate(nativeNode, str.c_str());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetJSItemConstraintSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_EQUAL_RETURN(GetNativeNode(nativeNode, nodeArg, vm), false, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> sizeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_EQUAL_RETURN(sizeArg->IsObject(vm), false, panda::JSValueRef::Undefined(vm));

    auto sizeObj = sizeArg->ToObject(vm);

    RefPtr<ResourceObject> resObjMinWidth;
    RefPtr<ResourceObject> resObjMaxWidth;
    RefPtr<ResourceObject> resObjMinHeight;
    RefPtr<ResourceObject> resObjMaxHeight;
    auto minWidthValue = ArkTSUtils::GetProperty(vm, sizeObj, "minWidth");
    CalcDimension minWidth;
    if (ArkTSUtils::ParseJsDimensionVp(vm, minWidthValue, minWidth, resObjMinWidth)) {
        std::string calcMinWidthStr = minWidth.Unit() == DimensionUnit::CALC ? minWidth.CalcValue() : "";
        GetArkUINodeModifiers()->getWaterFlowModifier()->setItemMinWidth(nativeNode,
            static_cast<ArkUI_Float32>(minWidth.Value()), static_cast<int32_t>(minWidth.Unit()),
            calcMinWidthStr.c_str(), AceType::RawPtr(resObjMinWidth));
    }

    auto maxWidthValue = ArkTSUtils::GetProperty(vm, sizeObj, "maxWidth");
    CalcDimension maxWidth;
    if (ArkTSUtils::ParseJsDimensionVp(vm, maxWidthValue, maxWidth, resObjMaxWidth)) {
        std::string calcMaxWidthStr = maxWidth.Unit() == DimensionUnit::CALC ? maxWidth.CalcValue() : "";
        GetArkUINodeModifiers()->getWaterFlowModifier()->setItemMaxWidth(nativeNode,
            static_cast<ArkUI_Float32>(maxWidth.Value()), static_cast<int32_t>(maxWidth.Unit()),
            calcMaxWidthStr.c_str(), AceType::RawPtr(resObjMaxWidth));
    }

    auto minHeightValue = ArkTSUtils::GetProperty(vm, sizeObj, "minHeight");
    CalcDimension minHeight;
    if (ArkTSUtils::ParseJsDimensionVp(vm, minHeightValue, minHeight, resObjMinHeight)) {
        std::string calcMinHeightStr = minHeight.Unit() == DimensionUnit::CALC ? minHeight.CalcValue() : "";
        GetArkUINodeModifiers()->getWaterFlowModifier()->setItemMinHeight(nativeNode,
            static_cast<ArkUI_Float32>(minHeight.Value()), static_cast<int32_t>(minHeight.Unit()),
            calcMinHeightStr.c_str(), AceType::RawPtr(resObjMinHeight));
    }

    auto maxHeightValue = ArkTSUtils::GetProperty(vm, sizeObj, "maxHeight");
    CalcDimension maxHeight;
    if (ArkTSUtils::ParseJsDimensionVp(vm, maxHeightValue, maxHeight, resObjMaxHeight)) {
        std::string calcMaxHeightStr = maxHeight.Unit() == DimensionUnit::CALC ? maxHeight.CalcValue() : "";
        GetArkUINodeModifiers()->getWaterFlowModifier()->setItemMaxHeight(nativeNode,
            static_cast<ArkUI_Float32>(maxHeight.Value()), static_cast<int32_t>(maxHeight.Unit()),
            calcMaxHeightStr.c_str(), AceType::RawPtr(resObjMaxHeight));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetJSScrollBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_EQUAL_RETURN(GetNativeNode(nativeNode, nodeArg, vm), false, panda::JSValueRef::Undefined(vm));

    Local<JSValueRef> modeArg = runtimeCallInfo->GetCallArgRef(NUM_1);

    DisplayMode defaultValue = DisplayMode::OFF;
    auto displayMode = static_cast<int32_t>(defaultValue);
    if (!modeArg->IsUndefined() && modeArg->IsNumber()) {
        ArkTSUtils::ParseJsInt32(vm, modeArg, displayMode);
        if (displayMode < 0 || displayMode >= static_cast<int32_t>(DISPLAY_MODE.size())) {
            displayMode = static_cast<int32_t>(defaultValue);
        }
    }
    GetArkUINodeModifiers()->getWaterFlowModifier()->setWaterFlowScrollBar(nativeNode, displayMode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetJSScrollBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_EQUAL_RETURN(GetNativeNode(nativeNode, nodeArg, vm), false, panda::JSValueRef::Undefined(vm));

    Local<JSValueRef> widthArg = runtimeCallInfo->GetCallArgRef(NUM_1);

    auto scrollBarWidth = ParseBarWidth(vm, widthArg);
    if (!scrollBarWidth.empty()) {
        GetArkUINodeModifiers()->getWaterFlowModifier()->setWaterFlowScrollBarWidth(nativeNode, scrollBarWidth.c_str());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetJSScrollBarColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_EQUAL_RETURN(GetNativeNode(nativeNode, nodeArg, vm), false, panda::JSValueRef::Undefined(vm));

    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    nativeNode = nativeNode ? nativeNode
                            : reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode());

    Color color;
    RefPtr<ResourceObject> resObj;
    NodeInfo nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (ArkTSUtils::ParseJsColor(vm, colorArg, color, resObj, nodeInfo)) {
        GetArkUINodeModifiers()->getWaterFlowModifier()->setWaterFlowScrollBarColor(
            nativeNode, color.ColorToString().c_str());
    } else {
        GetArkUINodeModifiers()->getWaterFlowModifier()->setScrollBarColorNull(nativeNode);
    }
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getWaterFlowModifier()->createWaterFlowScrollBarColorWithResourceObj(
            nativeNode, AceType::RawPtr(resObj));
    }
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG