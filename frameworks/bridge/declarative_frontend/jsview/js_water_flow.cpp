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

#include "bridge/declarative_frontend/jsview/js_water_flow.h"

#include <cstdint>
#include <vector>

#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include "bridge/declarative_frontend/jsview/js_scrollable.h"
#include "bridge/declarative_frontend/jsview/js_scroller.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/js_water_flow_sections.h"
#include "bridge/declarative_frontend/jsview/models/water_flow_model_impl.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/waterflow/water_flow_model.h"
#include "core/components_ng/pattern/waterflow/water_flow_model_ng.h"
#include "core/components_ng/pattern/waterflow/water_flow_sections.h"

namespace OHOS::Ace {
std::unique_ptr<WaterFlowModel> WaterFlowModel::instance_ = nullptr;
std::mutex WaterFlowModel::mutex_;

WaterFlowModel* WaterFlowModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::WaterFlowModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::WaterFlowModelNG());
            } else {
                instance_.reset(new Framework::WaterFlowModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace
namespace OHOS::Ace::Framework {
namespace {
const std::vector<FlexDirection> LAYOUT_DIRECTION = { FlexDirection::ROW, FlexDirection::COLUMN,
    FlexDirection::ROW_REVERSE, FlexDirection::COLUMN_REVERSE };

namespace {
void ParseChanges(
    const JSCallbackInfo& args, const JSRef<JSArray>& changeArray, RefPtr<NG::WaterFlowSections>& waterFlowSections)
{
    auto length = changeArray->Length();
    for (size_t i = 0; i < length; ++i) {
        auto change = changeArray->GetValueAt(i);
        if (!change->IsObject()) {
            continue;
        }
        auto changeObject = JSRef<JSObject>::Cast(change);
        auto sectionValue = changeObject->GetProperty("sections");
        if (!sectionValue->IsArray()) {
            continue;
        }
        auto sectionArray = JSRef<JSArray>::Cast(sectionValue);
        auto sectionsCount = sectionArray->Length();
        std::vector<NG::WaterFlowSections::Section> newSections;
        for (size_t j = 0; j < sectionsCount; ++j) {
            NG::WaterFlowSections::Section section;
            auto newSection = sectionArray->GetValueAt(j);
            if (JSWaterFlowSections::ParseSectionOptions(args, newSection, section)) {
                newSections.emplace_back(section);
            }
        }
        waterFlowSections->ChangeData(changeObject->GetProperty("start")->ToNumber<int32_t>(),
            changeObject->GetProperty("deleteCount")->ToNumber<int32_t>(), newSections);
    }
}

void ParseSections(
    const JSCallbackInfo& args, const JSRef<JSArray>& sectionArray, RefPtr<NG::WaterFlowSections>& waterFlowSections)
{
    auto length = sectionArray->Length();
    std::vector<NG::WaterFlowSections::Section> newSections;
    for (size_t j = 0; j < length; ++j) {
        NG::WaterFlowSections::Section section;
        auto newSection = sectionArray->GetValueAt(j);
        if (JSWaterFlowSections::ParseSectionOptions(args, newSection, section)) {
            newSections.emplace_back(section);
        }
    }
    waterFlowSections->ChangeData(0, waterFlowSections->GetSectionInfo().size(), newSections);
}

void ParseScroller(const JSRef<JSObject>& obj)
{
    auto scroller = obj->GetProperty("scroller");
    if (scroller->IsObject()) {
        auto* jsScroller = JSRef<JSObject>::Cast(scroller)->Unwrap<JSScroller>();
        CHECK_NULL_VOID(jsScroller);
        jsScroller->SetInstanceId(Container::CurrentId());
        auto positionController = WaterFlowModel::GetInstance()->CreateScrollController();
        jsScroller->SetController(positionController);

        // Init scroll bar proxy.
        auto proxy = jsScroller->GetScrollBarProxy();
        if (!proxy) {
            proxy = WaterFlowModel::GetInstance()->CreateScrollBarProxy();
            jsScroller->SetScrollBarProxy(proxy);
        }
        WaterFlowModel::GetInstance()->SetScroller(positionController, proxy);
    }
}
} // namespace
} // namespace

void UpdateSections(
    const JSCallbackInfo& args, const JSRef<JSVal>& sections, RefPtr<NG::WaterFlowSections>& waterFlowSections)
{
    CHECK_NULL_VOID(waterFlowSections);
    auto sectionsObject = JSRef<JSObject>::Cast(sections);
    auto changes = sectionsObject->GetProperty("changeArray");
    CHECK_NULL_VOID(changes->IsArray());
    auto changeArray = JSRef<JSArray>::Cast(changes);
    ParseChanges(args, changeArray, waterFlowSections);

    auto lengthFunc = sectionsObject->GetProperty("length");
    CHECK_NULL_VOID(lengthFunc->IsFunction());
    auto sectionLength = (JSRef<JSFunc>::Cast(lengthFunc))->Call(sectionsObject);
    if (waterFlowSections->GetSectionInfo().size() != sectionLength->ToNumber<uint32_t>()) {
        auto allSections = sectionsObject->GetProperty("sectionArray");
        CHECK_NULL_VOID(allSections->IsArray());
        ParseSections(args, JSRef<JSArray>::Cast(allSections), waterFlowSections);
    }

    auto clearFunc = sectionsObject->GetProperty("clearChanges");
    CHECK_NULL_VOID(clearFunc->IsFunction());
    auto func = JSRef<JSFunc>::Cast(clearFunc);
    func->Call(sectionsObject);
}

void UpdateWaterFlowSections(const JSCallbackInfo& args, const JSRef<JSVal>& sections)
{
    auto waterFlowSections = WaterFlowModel::GetInstance()->GetOrCreateWaterFlowSections();
    CHECK_NULL_VOID(waterFlowSections);
    UpdateSections(args, sections, waterFlowSections);
}

void JSWaterFlow::UpdateWaterFlowSectionsByFrameNode(
    NG::FrameNode* frameNode, const JSCallbackInfo& args, const JSRef<JSVal>& sections)
{
    auto waterFlowSections = NG::WaterFlowModelNG::GetOrCreateWaterFlowSections(frameNode);
    CHECK_NULL_VOID(waterFlowSections);
    UpdateSections(args, sections, waterFlowSections);
}

RefPtr<NG::UINode> SetWaterFlowBuilderNode(const JSRef<JSObject>& footerJsObject)
{
    JSRef<JSVal> builderNodeParam = footerJsObject->GetProperty("builderNode_");
    if (builderNodeParam->IsObject()) {
        auto builderNodeObject = JSRef<JSObject>::Cast(builderNodeParam);
        JSRef<JSVal> nodePtr = builderNodeObject->GetProperty("nodePtr_");
        if (!nodePtr.IsEmpty()) {
            const auto* vm = nodePtr->GetEcmaVM();
            auto* node = nodePtr->GetLocalHandle()->ToNativePointer(vm)->Value();
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

void JSWaterFlow::UpdateWaterFlowFooterContent(NG::FrameNode* frameNode, const JSRef<JSVal>& args)
{
    CHECK_NULL_VOID(args->IsObject());
    JSRef<JSObject> footerJsObject = JSRef<JSObject>::Cast(args); // 4 is the index of footerContent
    if (footerJsObject->HasProperty("builderNode_")) {
        RefPtr<NG::UINode> refPtrUINode = SetWaterFlowBuilderNode(footerJsObject);
        NG::WaterFlowModelNG::SetWaterflowFooterWithFrameNode(frameNode, refPtrUINode);
    }
}

void JSWaterFlow::Create(const JSCallbackInfo& args)
{
    if (args.Length() > 1) {
        LOGW("Arg is wrong, it is supposed to have at most one argument");
        return;
    }

    WaterFlowModel::GetInstance()->Create();

    if (args.Length() == 0) {
        return;
    }

    if (!args[0]->IsObject()) {
        LOGE("The arg must be object");
        return;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);

    // set layout mode first. SetFooter is dependent to it
    using LayoutMode = NG::WaterFlowLayoutMode;
    auto mode = LayoutMode::TOP_DOWN;
    auto jsMode = obj->GetProperty("layoutMode");
    if (jsMode->IsNumber()) {
        mode = static_cast<LayoutMode>(jsMode->ToNumber<int32_t>());
        if (mode < LayoutMode::TOP_DOWN || mode > LayoutMode::SLIDING_WINDOW) {
            mode = LayoutMode::TOP_DOWN;
        }
    }
    WaterFlowModel::GetInstance()->SetLayoutMode(mode);

    ParseScroller(obj);

    auto sections = obj->GetProperty("sections");
    auto footerObject = obj->GetProperty("footer");
    if (sections->IsObject()) {
        UpdateWaterFlowSections(args, sections);
    } else {
        WaterFlowModel::GetInstance()->ResetSections();

        if (obj->HasProperty("footerContent")) {
            RefPtr<NG::UINode> refPtrUINode = nullptr;
            auto footerContentObject = obj->GetProperty("footerContent");
            if (footerContentObject->IsObject()) {
                auto footerJsObject = JSRef<JSObject>::Cast(footerContentObject);
                refPtrUINode = SetWaterFlowBuilderNode(footerJsObject);
            }
            WaterFlowModel::GetInstance()->SetFooterWithFrameNode(refPtrUINode);
            return;
        }
        if (footerObject->IsFunction()) {
            // ignore footer if sections are present
            auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(footerObject));
            auto footerAction = [builderFunc]() { builderFunc->Execute(); };
            WaterFlowModel::GetInstance()->SetFooter(footerAction);
        }
    }
}

void JSWaterFlow::JSBind(BindingTarget globalObj)
{
    JSClass<JSWaterFlow>::Declare("WaterFlow");

    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSWaterFlow>::StaticMethod("create", &JSWaterFlow::Create, opt);
    JSClass<JSWaterFlow>::StaticMethod("columnsGap", &JSWaterFlow::SetColumnsGap, opt);
    JSClass<JSWaterFlow>::StaticMethod("rowsGap", &JSWaterFlow::SetRowsGap, opt);
    JSClass<JSWaterFlow>::StaticMethod("layoutDirection", &JSWaterFlow::SetLayoutDirection, opt);
    JSClass<JSWaterFlow>::StaticMethod("columnsTemplate", &JSWaterFlow::SetColumnsTemplate, opt);
    JSClass<JSWaterFlow>::StaticMethod("itemConstraintSize", &JSWaterFlow::SetItemConstraintSize, opt);
    JSClass<JSWaterFlow>::StaticMethod("rowsTemplate", &JSWaterFlow::SetRowsTemplate, opt);
    JSClass<JSWaterFlow>::StaticMethod("nestedScroll", &JSWaterFlow::SetNestedScroll);
    JSClass<JSWaterFlow>::StaticMethod("enableScrollInteraction", &JSWaterFlow::SetScrollEnabled);
    JSClass<JSWaterFlow>::StaticMethod("onReachStart", &JSWaterFlow::ReachStartCallback);
    JSClass<JSWaterFlow>::StaticMethod("onReachEnd", &JSWaterFlow::ReachEndCallback);
    JSClass<JSWaterFlow>::StaticMethod("onScrollFrameBegin", &JSWaterFlow::ScrollFrameBeginCallback);
    JSClass<JSWaterFlow>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSWaterFlow>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSWaterFlow>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSWaterFlow>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSWaterFlow>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSWaterFlow>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSWaterFlow>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSWaterFlow>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSWaterFlow>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSWaterFlow>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);
    JSClass<JSWaterFlow>::StaticMethod("friction", &JSWaterFlow::SetFriction);
    JSClass<JSWaterFlow>::StaticMethod("clip", &JSScrollable::JsClip);
    JSClass<JSWaterFlow>::StaticMethod("cachedCount", &JSWaterFlow::SetCachedCount);
    JSClass<JSWaterFlow>::StaticMethod("edgeEffect", &JSWaterFlow::SetEdgeEffect);
    JSClass<JSWaterFlow>::StaticMethod("syncLoad", &JSWaterFlow::SetSyncLoad);

    JSClass<JSWaterFlow>::StaticMethod("onScroll", &JSWaterFlow::JsOnScroll);
    JSClass<JSWaterFlow>::StaticMethod("onScrollStart", &JSWaterFlow::JsOnScrollStart);
    JSClass<JSWaterFlow>::StaticMethod("onScrollStop", &JSWaterFlow::JsOnScrollStop);
    JSClass<JSWaterFlow>::StaticMethod("onScrollIndex", &JSWaterFlow::JsOnScrollIndex);

    JSClass<JSWaterFlow>::StaticMethod("scrollBar", &JSWaterFlow::SetScrollBar, opt);
    JSClass<JSWaterFlow>::StaticMethod("scrollBarWidth", &JSWaterFlow::SetScrollBarWidth, opt);
    JSClass<JSWaterFlow>::StaticMethod("scrollBarColor", &JSWaterFlow::SetScrollBarColor, opt);

    JSClass<JSWaterFlow>::InheritAndBind<JSScrollableBase>(globalObj);
}

void JSWaterFlow::SetColumnsGap(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CalcDimension colGap;
    if (!ParseJsDimensionVp(info[0], colGap) || colGap.Value() < 0) {
        colGap.SetValue(0.0);
    }
    WaterFlowModel::GetInstance()->SetColumnsGap(colGap);
}

void JSWaterFlow::SetRowsGap(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CalcDimension rowGap;
    if (!ParseJsDimensionVp(info[0], rowGap) || rowGap.Value() < 0) {
        rowGap.SetValue(0.0);
    }
    WaterFlowModel::GetInstance()->SetRowsGap(rowGap);
}

void JSWaterFlow::SetLayoutDirection(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto value = static_cast<int32_t>(FlexDirection::COLUMN);
    auto jsValue = info[0];
    if (!jsValue->IsUndefined()) {
        ParseJsInteger<int32_t>(jsValue, value);
    }
    if (value >= 0 && value < static_cast<int32_t>(LAYOUT_DIRECTION.size())) {
        WaterFlowModel::GetInstance()->SetLayoutDirection(LAYOUT_DIRECTION[value]);
    } else {
        WaterFlowModel::GetInstance()->SetLayoutDirection(FlexDirection::COLUMN);
    }
}

void JSWaterFlow::SetColumnsTemplate(const std::string& value)
{
    WaterFlowModel::GetInstance()->SetColumnsTemplate(value);
}

void JSWaterFlow::SetItemConstraintSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        return;
    }

    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);

    JSRef<JSVal> minWidthValue = sizeObj->GetProperty("minWidth");
    CalcDimension minWidth;
    if (ParseJsDimensionVp(minWidthValue, minWidth)) {
        WaterFlowModel::GetInstance()->SetItemMinWidth(minWidth);
    }

    JSRef<JSVal> maxWidthValue = sizeObj->GetProperty("maxWidth");
    CalcDimension maxWidth;
    if (ParseJsDimensionVp(maxWidthValue, maxWidth)) {
        WaterFlowModel::GetInstance()->SetItemMaxWidth(maxWidth);
    }

    JSRef<JSVal> minHeightValue = sizeObj->GetProperty("minHeight");
    CalcDimension minHeight;
    if (ParseJsDimensionVp(minHeightValue, minHeight)) {
        WaterFlowModel::GetInstance()->SetItemMinHeight(minHeight);
    }

    JSRef<JSVal> maxHeightValue = sizeObj->GetProperty("maxHeight");
    CalcDimension maxHeight;
    if (ParseJsDimensionVp(maxHeightValue, maxHeight)) {
        WaterFlowModel::GetInstance()->SetItemMaxHeight(maxHeight);
    }
}

void JSWaterFlow::SetRowsTemplate(const std::string& value)
{
    WaterFlowModel::GetInstance()->SetRowsTemplate(value);
}

void JSWaterFlow::SetNestedScroll(const JSCallbackInfo& args)
{
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_ONLY,
        .backward = NestedScrollMode::SELF_ONLY,
    };
    if (args.Length() < 1 || !args[0]->IsObject()) {
        WaterFlowModel::GetInstance()->SetNestedScroll(nestedOpt);
        LOGW("Invalid params");
        return;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
    int32_t froward = 0;
    JSViewAbstract::ParseJsInt32(obj->GetProperty("scrollForward"), froward);
    if (froward < static_cast<int32_t>(NestedScrollMode::SELF_ONLY) ||
        froward > static_cast<int32_t>(NestedScrollMode::PARALLEL)) {
        LOGW("ScrollFroward params invalid");
        froward = 0;
    }
    int32_t backward = 0;
    JSViewAbstract::ParseJsInt32(obj->GetProperty("scrollBackward"), backward);
    if (backward < static_cast<int32_t>(NestedScrollMode::SELF_ONLY) ||
        backward > static_cast<int32_t>(NestedScrollMode::PARALLEL)) {
        LOGW("ScrollFroward params invalid");
        backward = 0;
    }
    nestedOpt.forward = static_cast<NestedScrollMode>(froward);
    nestedOpt.backward = static_cast<NestedScrollMode>(backward);
    WaterFlowModel::GetInstance()->SetNestedScroll(nestedOpt);
    args.ReturnSelf();
}

void JSWaterFlow::SetScrollEnabled(const JSCallbackInfo& args)
{
    WaterFlowModel::GetInstance()->SetScrollEnabled(args[0]->IsBoolean() ? args[0]->ToBoolean() : true);
}

void JSWaterFlow::SetFriction(const JSCallbackInfo& info)
{
    double friction = -1.0;
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> resObj;
        if (!JSViewAbstract::ParseJsDouble(info[0], friction, resObj)) {
            friction = -1.0;
        }
        WaterFlowModel::GetInstance()->ParseResObjFriction(resObj);
    } else if (!JSViewAbstract::ParseJsDouble(info[0], friction)) {
        LOGW("Friction params invalid,can not convert to double");
        friction = -1.0;
    }
    WaterFlowModel::GetInstance()->SetFriction(friction);
}

void JSWaterFlow::ReachStartCallback(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto onReachStart = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])]() {
            func->Call(JSRef<JSObject>());
            UiSessionManager::GetInstance()->ReportComponentChangeEvent("event", "onReachStart");
            return;
        };
        WaterFlowModel::GetInstance()->SetOnReachStart(std::move(onReachStart));
    }
    args.ReturnSelf();
}

void JSWaterFlow::ReachEndCallback(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto onReachEnd = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])]() {
            func->Call(JSRef<JSObject>());
            UiSessionManager::GetInstance()->ReportComponentChangeEvent("event", "onReachEnd");
            return;
        };
        WaterFlowModel::GetInstance()->SetOnReachEnd(std::move(onReachEnd));
    }
    args.ReturnSelf();
}

void JSWaterFlow::ScrollFrameBeginCallback(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto onScrollBegin = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])](
                                 const Dimension& offset, const ScrollState& state) -> ScrollFrameResult {
            ScrollFrameResult scrollRes { .offset = offset };
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, scrollRes);
            auto params = ConvertToJSValues(offset, state);
            auto result = func->Call(JSRef<JSObject>(), params.size(), params.data());
            if (result.IsEmpty()) {
                LOGE("Error calling onScrollFrameBegin, result is empty.");
                return scrollRes;
            }

            if (!result->IsObject()) {
                LOGE("Error calling onScrollFrameBegin, result is not object.");
                return scrollRes;
            }

            auto resObj = JSRef<JSObject>::Cast(result);
            auto dxRemainValue = resObj->GetProperty("offsetRemain");
            if (dxRemainValue->IsNumber()) {
                scrollRes.offset = Dimension(dxRemainValue->ToNumber<float>(), DimensionUnit::VP);
            }
            return scrollRes;
        };
        WaterFlowModel::GetInstance()->SetOnScrollFrameBegin(std::move(onScrollBegin));
    }
}

void JSWaterFlow::SetCachedCount(const JSCallbackInfo& info)
{
    int32_t cachedCount = 1;
    auto jsValue = info[0];

    if (!jsValue->IsUndefined() && jsValue->IsNumber()) {
        ParseJsInt32(jsValue, cachedCount);
        if (cachedCount < 0) {
            cachedCount = 1;
        }
    }
    bool show = false;
    if (info.Length() > 1) {
        show = info[1]->ToBoolean();
    }
    WaterFlowModel::GetInstance()->SetCachedCount(cachedCount, show);
}

void JSWaterFlow::SetEdgeEffect(const JSCallbackInfo& info)
{
    auto edgeEffect = WaterFlowModel::GetInstance()->GetEdgeEffect();
    auto effectEdge = EffectEdge::ALL;
    if (info.Length() > 0) {
        edgeEffect = JSScrollable::ParseEdgeEffect(info[0], edgeEffect);
    }
    auto alwaysEnabled = WaterFlowModel::GetInstance()->GetAlwaysEnableEdgeEffect();
    if (info.Length() > 1) {
        alwaysEnabled = JSScrollable::ParseAlwaysEnable(info[1], alwaysEnabled);
        effectEdge = JSScrollable::ParseEffectEdge(info[1]);
    }
    WaterFlowModel::GetInstance()->SetEdgeEffect(edgeEffect, alwaysEnabled, effectEdge);
}

void JSWaterFlow::SetSyncLoad(const JSCallbackInfo& info)
{
    bool syncLoad = false;
    if (info.Length() >= 1) {
        auto value = info[0];
        if (value->IsBoolean()) {
            syncLoad = value->ToBoolean();
        }
    }
    WaterFlowModel::GetInstance()->SetSyncLoad(syncLoad);
}

void JSWaterFlow::JsOnScroll(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto onScroll = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])](
                            const CalcDimension& scrollOffset, const ScrollState& scrollState) {
            auto params = ConvertToJSValues(scrollOffset, scrollState);
            func->Call(JSRef<JSObject>(), params.size(), params.data());
            return;
        };
        WaterFlowModel::GetInstance()->SetOnScroll(std::move(onScroll));
    }
    args.ReturnSelf();
}

void JSWaterFlow::JsOnScrollStart(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto onScrollStart = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])]() {
            func->Call(JSRef<JSObject>());
            return;
        };
        WaterFlowModel::GetInstance()->SetOnScrollStart(std::move(onScrollStart));
    }
    args.ReturnSelf();
}

void JSWaterFlow::JsOnScrollStop(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto onScrollStop = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])]() {
            func->Call(JSRef<JSObject>());
            return;
        };
        WaterFlowModel::GetInstance()->SetOnScrollStop(std::move(onScrollStop));
    }
    args.ReturnSelf();
}

void JSWaterFlow::JsOnScrollIndex(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto onScrollIndex = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])](
                                 const int32_t first, const int32_t last) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto params = ConvertToJSValues(first, last);
            func->Call(JSRef<JSObject>(), params.size(), params.data());
            UiSessionManager::GetInstance()->ReportComponentChangeEvent("event", "onScrollIndex");
            return;
        };
        WaterFlowModel::GetInstance()->SetOnScrollIndex(std::move(onScrollIndex));
    }
    args.ReturnSelf();
}

void JSWaterFlow::SetScrollBar(const JSCallbackInfo& info)
{
    auto displayMode = JSScrollable::ParseDisplayMode(info, WaterFlowModel::GetDisplayMode());
    WaterFlowModel::GetInstance()->SetScrollBarMode(displayMode);
}

void JSWaterFlow::SetScrollBarColor(const JSCallbackInfo& info)
{
    auto scrollBarColor = JSScrollable::ParseBarColor(info);
    if (!scrollBarColor.empty()) {
        WaterFlowModel::GetInstance()->SetScrollBarColor(scrollBarColor);
    }
}

void JSWaterFlow::SetScrollBarWidth(const JSCallbackInfo& scrollWidth)
{
    auto scrollBarWidth = JSScrollable::ParseBarWidth(scrollWidth);
    if (!scrollBarWidth.empty()) {
        WaterFlowModel::GetInstance()->SetScrollBarWidth(scrollBarWidth);
    }
}
} // namespace OHOS::Ace::Framework
