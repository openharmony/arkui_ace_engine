/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_list.h"
#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include "base/geometry/axis.h"
#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/engine/functions/js_drag_function.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_scrollable.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/list_model_impl.h"
#include "core/common/container.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/list/list_model.h"
#include "core/components_ng/pattern/list/list_model_ng.h"
#include "core/components_ng/pattern/list/list_position_controller.h"
#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"

namespace OHOS::Ace {

std::unique_ptr<ListModel> ListModel::instance_ = nullptr;
std::mutex ListModel::mutex_;

ListModel* ListModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::ListModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::ListModelNG());
            } else {
                instance_.reset(new Framework::ListModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

const std::vector<ScrollSnapAlign> SCROLL_SNAP_ALIGN = { ScrollSnapAlign::NONE, ScrollSnapAlign::START,
    ScrollSnapAlign::CENTER, ScrollSnapAlign::END };

namespace {
const std::regex DIMENSION_REGEX(R"(^[-+]?\d+(?:\.\d+)?(?:px|vp|fp|lpx)?$)", std::regex::icase);
constexpr ScrollAlign ALIGN_TABLE[] = {
    ScrollAlign::START,
    ScrollAlign::CENTER,
    ScrollAlign::END,
    ScrollAlign::AUTO,
};
static constexpr int ARGS_LENGTH = 2;
}

namespace {
bool ParseChange(const JSRef<JSObject>& changeObject, const float defaultSize, int32_t& start,
    int32_t& deleteCount, std::vector<float>& newChildrenSize)
{
    if (!JSViewAbstract::ParseJsInteger<int32_t>(changeObject->GetProperty("start"), start) || start < 0) {
        return false;
    }
    if (!(changeObject->HasProperty("deleteCount"))) {
        // If only input one parameter, set -1 to deleteCount for deleting elements after index 'start' in the array.
        deleteCount = -1;
    } else if (!JSViewAbstract::ParseJsInteger<int32_t>(changeObject->GetProperty("deleteCount"), deleteCount) ||
        deleteCount < 0) {
        deleteCount = 0;
    }
    auto childrenSizeValue = changeObject->GetProperty("childrenSize");
    if (childrenSizeValue->IsArray()) {
        auto childrenSize = JSRef<JSArray>::Cast(childrenSizeValue);
        auto childrenSizeCount = childrenSize->Length();
        for (size_t j = 0; j < childrenSizeCount; ++j) {
            // -1.0: represent default size.
            double childSize = -1.0;
            if (!JSViewAbstract::ParseJsDouble(childrenSize->GetValueAt(j), childSize) || Negative(childSize)) {
                // -1.0f: represent default size.
                newChildrenSize.emplace_back(-1.0f);
            } else {
                newChildrenSize.emplace_back(Dimension(childSize, DimensionUnit::VP).ConvertToPx());
            }
        }
    }
    return true;
}

void SyncChildrenSize(const JSRef<JSObject>& childrenSizeObj, RefPtr<NG::ListChildrenMainSize> childrenSize)
{
    auto sizeArray = childrenSizeObj->GetProperty("sizeArray");
    if (!sizeArray->IsArray()) {
        return;
    }
    childrenSize->ResizeChildrenSize(0);
    auto childrenSizeJSArray = JSRef<JSArray>::Cast(sizeArray);
    auto length = childrenSizeJSArray->Length();
    for (size_t i = 0; i < length; ++i) {
        // -1.0: represent default size.
        double childSize = -1.0;
        if (!JSViewAbstract::ParseJsDouble(childrenSizeJSArray->GetValueAt(i), childSize) || Negative(childSize)) {
            // -1.0f: represent default size.
            childrenSize->SyncChildrenSize(-1.0f);
        } else {
            childrenSize->SyncChildrenSize(Dimension(childSize, DimensionUnit::VP).ConvertToPx());
        }
    }
    childrenSize->SyncChildrenSizeOver();
}
} // namespace

void JSList::SetDirection(int32_t direction)
{
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_THIRTEEN) && direction != 0 &&
        direction != 1) {
        direction = 0;
    }
    ListModel::GetInstance()->SetListDirection(static_cast<Axis>(direction));
}

void JSList::SetScrollBar(const JSCallbackInfo& info)
{
    auto displayMode = JSScrollable::ParseDisplayMode(info, ListModel::GetInstance()->GetDisplayMode());
    ListModel::GetInstance()->SetScrollBar(displayMode);
}

void JSList::SetScrollBarColor(const JSCallbackInfo& info)
{
    auto scrollBarColor = JSScrollable::ParseBarColor(info);
    if (!scrollBarColor.empty()) {
        ListModel::GetInstance()->SetScrollBarColor(scrollBarColor);
    }
}

void JSList::SetScrollBarWidth(const JSCallbackInfo& scrollWidth)
{
    auto scrollBarWidth = JSScrollable::ParseBarWidth(scrollWidth);
    if (!scrollBarWidth.empty()) {
        ListModel::GetInstance()->SetScrollBarWidth(scrollBarWidth);
    }
}

void JSList::SetEdgeEffect(const JSCallbackInfo& info)
{
    auto edgeEffect = EdgeEffect::SPRING;
    auto effectEdge = EffectEdge::ALL;
    if (info.Length() > 0) {
        edgeEffect = JSScrollable::ParseEdgeEffect(info[0], EdgeEffect::SPRING);
    }
    auto alwaysEnabled = false;
    if (info.Length() > 1) {
        alwaysEnabled = JSScrollable::ParseAlwaysEnable(info[1], false);
        effectEdge = JSScrollable::ParseEffectEdge(info[1]);
    }
    ListModel::GetInstance()->SetEdgeEffect(edgeEffect, alwaysEnabled, effectEdge);
}

void JSList::SetEditMode(bool editMode)
{
    ListModel::GetInstance()->SetEditMode(editMode);
}

void JSList::SetCachedCount(const JSCallbackInfo& info)
{
    int32_t cachedCount = 1;
    ParseJsInteger<int32_t>(info[0], cachedCount);
    cachedCount = cachedCount < 0 ? 1 : cachedCount;
    bool show = false;
    // 2: represent 2 params.
    if (info.Length() == 2) {
        show = info[1]->ToBoolean();
    }
    ListModel::GetInstance()->SetCachedCount(cachedCount, show);
}

void JSList::SetScroller(RefPtr<JSScroller> scroller)
{
    if (scroller) {
        RefPtr<ScrollControllerBase> listController = ListModel::GetInstance()->CreateScrollController();
        scroller->SetController(listController);

        // Init scroll bar proxy.
        auto proxy = scroller->GetScrollBarProxy();
        if (!proxy) {
            if (Container::IsCurrentUseNewPipeline()) {
                proxy = AceType::MakeRefPtr<NG::ScrollBarProxy>();
            } else {
                proxy = AceType::MakeRefPtr<ScrollBarProxy>();
            }
            scroller->SetScrollBarProxy(proxy);
        }
        ListModel::GetInstance()->SetScroller(listController, proxy);
    }
}

void JSList::Create(const JSCallbackInfo& args)
{
    ListModel::GetInstance()->Create();
    if (args.Length() < 1) {
        return;
    }
    JSRef<JSVal> arg0 = args[0];
    if (arg0->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(arg0);
        JSRef<JSVal> spaceValue = obj->GetProperty("space");
        if (!spaceValue->IsNull()) {
            CalcDimension space;
            ConvertFromJSValue(spaceValue, space);
            ListModel::GetInstance()->SetSpace(space);
        }
        int32_t initialIndex = 0;
        if (ConvertFromJSValue(obj->GetProperty("initialIndex"), initialIndex) && initialIndex >= 0) {
            ListModel::GetInstance()->SetInitialIndex(initialIndex);
        }
        JSRef<JSVal> scrollerValue = obj->GetProperty("scroller");
        if (scrollerValue->IsObject()) {
            void* scroller = JSRef<JSObject>::Cast(scrollerValue)->Unwrap<JSScroller>();
            RefPtr<JSScroller> jsScroller = Referenced::Claim(reinterpret_cast<JSScroller*>(scroller));
            jsScroller->SetInstanceId(Container::CurrentId());
            SetScroller(jsScroller);
        }
    }
}

void JSList::SetChildrenMainSize(const JSCallbackInfo& args)
{
    if (args.Length() != 1 || !(args[0]->IsObject())) {
        ListModel::GetInstance()->ResetListChildrenMainSize();
        return;
    }
    SetChildrenMainSize(JSRef<JSObject>::Cast(args[0]));
}

void JSList::SetChildrenMainSize(const JSRef<JSObject>& childrenSizeObj)
{
    double defaultSize = 0.0f;
    if (!ParseJsDouble(childrenSizeObj->GetProperty("childDefaultSize"), defaultSize) || !NonNegative(defaultSize)) {
        TAG_LOGW(AceLogTag::ACE_LIST, "JSList input parameter defaultSize check failed.");
        return;
    }
    auto listChildrenMainSize = ListModel::GetInstance()->GetOrCreateListChildrenMainSize();
    CHECK_NULL_VOID(listChildrenMainSize);
    listChildrenMainSize->UpdateDefaultSize(Dimension(defaultSize, DimensionUnit::VP).ConvertToPx());

    if (listChildrenMainSize->NeedSync()) {
        SyncChildrenSize(childrenSizeObj, listChildrenMainSize);
    } else {
        auto changes = childrenSizeObj->GetProperty("changeArray");
        if (!changes->IsArray()) {
            return;
        }
        auto changeArray = JSRef<JSArray>::Cast(changes);
        auto length = changeArray->Length();
        for (size_t i = 0; i < length; ++i) {
            auto change = changeArray->GetValueAt(i);
            if (!change->IsObject()) {
                continue;
            }
            auto changeObject = JSRef<JSObject>::Cast(change);
            int32_t start = 0;
            int32_t deleteCount = 0;
            std::vector<float> newChildrenSize;
            if (!ParseChange(changeObject, defaultSize, start, deleteCount, newChildrenSize)) {
                SyncChildrenSize(childrenSizeObj, listChildrenMainSize);
                break;
            }
            listChildrenMainSize->ChangeData(start, deleteCount, newChildrenSize);
        }
    }
    auto clearFunc = childrenSizeObj->GetProperty("clearChanges");
    if (!clearFunc->IsFunction()) {
        return;
    }
    auto func = JSRef<JSFunc>::Cast(clearFunc);
    JSRef<JSVal>::Cast(func->Call(childrenSizeObj));
}

void JSList::SetChainAnimation(const JSCallbackInfo& args)
{
    ListModel::GetInstance()->SetChainAnimation(args[0]->IsBoolean() ? args[0]->ToBoolean() : false);
}

void JSList::SetChainAnimationOptions(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    if (info[0]->IsObject()) {
        RefPtr<ListTheme> listTheme = GetTheme<ListTheme>();
        CHECK_NULL_VOID(listTheme);
        ChainAnimationOptions options = {
            .minSpace = listTheme->GetChainMinSpace(),
            .maxSpace = listTheme->GetChainMaxSpace(),
            .conductivity = listTheme->GetChainConductivity(),
            .intensity = listTheme->GetChainIntensity(),
            .edgeEffect = 0,
            .stiffness = listTheme->GetChainStiffness(),
            .damping = listTheme->GetChainDamping(),
        };
        JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
        ParseJsDimensionVp(jsObj->GetProperty("minSpace"), options.minSpace);
        ParseJsDimensionVp(jsObj->GetProperty("maxSpace"), options.maxSpace);
        JSViewAbstract::ParseJsDouble(jsObj->GetProperty("conductivity"), options.conductivity);
        JSViewAbstract::ParseJsDouble(jsObj->GetProperty("intensity"), options.intensity);
        JSViewAbstract::ParseJsInt32(jsObj->GetProperty("edgeEffect"), options.edgeEffect);
        JSViewAbstract::ParseJsDouble(jsObj->GetProperty("stiffness"), options.stiffness);
        JSViewAbstract::ParseJsDouble(jsObj->GetProperty("damping"), options.damping);
        ListModel::GetInstance()->SetChainAnimationOptions(options);
    }
}

void JSList::JsWidth(const JSCallbackInfo& info)
{
    JSViewAbstract::JsWidth(info);
    ListModel::GetInstance()->SetHasWidth(true);
}

void JSList::JsHeight(const JSCallbackInfo& info)
{
    JSViewAbstract::JsHeight(info);
    ListModel::GetInstance()->SetHasHeight(true);
}

void JSList::SetListItemAlign(int32_t itemAlignment)
{
    ListModel::GetInstance()->SetListItemAlign(static_cast<V2::ListItemAlign>(itemAlignment));
}

void JSList::SetLanes(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    if (info.Length() >= 2 && !(info[1]->IsNull())) { /* 2: parameter count */
        CalcDimension laneGutter;
        RefPtr<ResourceObject> resObjLaneGutter;
        if (JSViewAbstract::ParseJsDimensionVp(info[1], laneGutter, resObjLaneGutter)) {
            if (laneGutter.IsNegative()) {
                laneGutter.Reset();
            }
        }
        if (SystemProperties::ConfigChangePerform()) {
            ListModel::GetInstance()->CreateWithResourceObjLaneGutter(resObjLaneGutter);
        }
        ListModel::GetInstance()->SetLaneGutter(laneGutter);
    }

    int32_t laneNum = 1;
    if (ParseJsInteger<int32_t>(info[0], laneNum)) {
        // when [lanes] is set, [laneConstrain_] of list component will be reset to std::nullopt
        ListModel::GetInstance()->SetLanes(laneNum);
        ListModel::GetInstance()->SetLaneConstrain(-1.0_vp, -1.0_vp);
        return;
    }
    RefPtr<ResourceObject> resObjMinLengthValue;
    RefPtr<ResourceObject> resObjMaxLengthValue;
    if (info[0]->IsObject()) {
        JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
        auto minLengthParam = jsObj->GetProperty("minLength");
        auto maxLengthParam = jsObj->GetProperty("maxLength");
        if (minLengthParam->IsNull() || maxLengthParam->IsNull()) {
            TAG_LOGW(AceLogTag::ACE_LIST, "minLength and maxLength are not both set");
            if (SystemProperties::ConfigChangePerform()) {
                ListModel::GetInstance()->CreateWithResourceObjLaneConstrain(nullptr, nullptr);
            }
            return;
        }
        CalcDimension minLengthValue;
        CalcDimension maxLengthValue;
        if (!ParseJsDimensionVp(minLengthParam, minLengthValue, resObjMinLengthValue)
            || !ParseJsDimensionVp(maxLengthParam, maxLengthValue, resObjMaxLengthValue)) {
            ListModel::GetInstance()->SetLanes(1);
            ListModel::GetInstance()->SetLaneConstrain(-1.0_vp, -1.0_vp);
            return;
        }
        ListModel::GetInstance()->SetLaneConstrain(minLengthValue, maxLengthValue);
    }
    ListModel::GetInstance()->SetLanes(1);
    ListModel::GetInstance()->CreateWithResourceObjLaneConstrain(resObjMinLengthValue, resObjMaxLengthValue);
}

void JSList::SetSticky(int32_t sticky)
{
    ListModel::GetInstance()->SetSticky(static_cast<V2::StickyStyle>(sticky));
}

void JSList::SetContentStartOffset(const JSCallbackInfo& info)
{
    double value = 0.0;
    ParseJsDouble(info[0], value);
    ListModel::GetInstance()->SetContentStartOffset(value);
}

void JSList::SetContentEndOffset(const JSCallbackInfo& info)
{
    double value = 0.0;
    ParseJsDouble(info[0], value);
    ListModel::GetInstance()->SetContentEndOffset(value);
}

void JSList::SetScrollSnapAlign(int32_t scrollSnapAlign)
{
    ScrollSnapAlign param;
    if (scrollSnapAlign < 0 || scrollSnapAlign >= static_cast<int32_t>(SCROLL_SNAP_ALIGN.size())) {
        param = ScrollSnapAlign::NONE;
    } else {
        param = ScrollSnapAlign(scrollSnapAlign);
    }
    ListModel::GetInstance()->SetScrollSnapAlign(param);
}

void JSList::SetDivider(const JSCallbackInfo& args)
{
    V2::ItemDivider divider;
    if (args.Length() >= 1 && args[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
        RefPtr<ResourceObject> resObjStrokeWidth;
        RefPtr<ResourceObject> resObjColor;
        RefPtr<ResourceObject> resObjStartMargin;
        RefPtr<ResourceObject> resObjEndMargin;
        bool needReset = obj->GetProperty("strokeWidth")->IsString() &&
                         !std::regex_match(obj->GetProperty("strokeWidth")->ToString(), DIMENSION_REGEX);
        if (needReset ||
            !ConvertFromJSValue(obj->GetProperty("strokeWidth"), divider.strokeWidth, resObjStrokeWidth)) {
            divider.strokeWidth = 0.0_vp;
        }
        bool setByUser = false;
        if (!ConvertFromJSValue(obj->GetProperty("color"), divider.color, resObjColor)) {
            // Failed to get color from param, using default color defined in theme
            RefPtr<ListTheme> listTheme = GetTheme<ListTheme>();
            if (listTheme) {
                divider.color = listTheme->GetDividerColor();
                setByUser = false;
            }
        } else {
            setByUser = true;
        }
        ListModel::GetInstance()->SetDividerColorByUser(setByUser);

        needReset = obj->GetProperty("startMargin")->IsString() &&
                    !std::regex_match(obj->GetProperty("startMargin")->ToString(), DIMENSION_REGEX);
        if (needReset ||
            !ConvertFromJSValue(obj->GetProperty("startMargin"), divider.startMargin, resObjStartMargin)) {
            divider.startMargin = 0.0_vp;
        }

        needReset = obj->GetProperty("endMargin")->IsString() &&
                    !std::regex_match(obj->GetProperty("endMargin")->ToString(), DIMENSION_REGEX);
        if (needReset || !ConvertFromJSValue(obj->GetProperty("endMargin"), divider.endMargin, resObjEndMargin)) {
            divider.endMargin = 0.0_vp;
        }

        if (SystemProperties::ConfigChangePerform()) {
            ListModel::GetInstance()->ParseResObjDividerStrokeWidth(resObjStrokeWidth);
            ListModel::GetInstance()->ParseResObjDividerColor(resObjColor);
            ListModel::GetInstance()->ParseResObjDividerStartMargin(resObjStartMargin);
            ListModel::GetInstance()->ParseResObjDividerEndMargin(resObjEndMargin);
        }
    }
    ListModel::GetInstance()->SetDivider(divider);
    args.ReturnSelf();
}

void JSList::SetNestedScroll(const JSCallbackInfo& args)
{
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_ONLY,
        .backward = NestedScrollMode::SELF_ONLY,
    };
    if (args.Length() < 1 || !args[0]->IsObject()) {
        ListModel::GetInstance()->SetNestedScroll(nestedOpt);
        return;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
    int32_t froward = 0;
    JSViewAbstract::ParseJsInt32(obj->GetProperty("scrollForward"), froward);
    if (froward < static_cast<int32_t>(NestedScrollMode::SELF_ONLY) ||
        froward > static_cast<int32_t>(NestedScrollMode::PARALLEL)) {
        froward = 0;
    }
    int32_t backward = 0;
    JSViewAbstract::ParseJsInt32(obj->GetProperty("scrollBackward"), backward);
    if (backward < static_cast<int32_t>(NestedScrollMode::SELF_ONLY) ||
        backward > static_cast<int32_t>(NestedScrollMode::PARALLEL)) {
        backward = 0;
    }
    nestedOpt.forward = static_cast<NestedScrollMode>(froward);
    nestedOpt.backward = static_cast<NestedScrollMode>(backward);
    ListModel::GetInstance()->SetNestedScroll(nestedOpt);
    args.ReturnSelf();
}

void JSList::SetScrollEnabled(const JSCallbackInfo& args)
{
    ListModel::GetInstance()->SetScrollEnabled(args[0]->IsBoolean() ? args[0]->ToBoolean() : true);
}

void JSList::ScrollCallback(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto onScroll = [func = JSRef<JSFunc>::Cast(args[0])](
                            const CalcDimension& scrollOffset, const ScrollState& scrollState) {
            auto params = ConvertToJSValues(scrollOffset, scrollState);
            func->Call(JSRef<JSObject>(), params.size(), params.data());
            return;
        };
        ListModel::GetInstance()->SetOnScroll(std::move(onScroll));
    }
    args.ReturnSelf();
}

void JSList::SetFriction(const JSCallbackInfo& info)
{
    double friction = -1.0;
    RefPtr<ResourceObject> resObj;
    if (!JSViewAbstract::ParseJsDouble(info[0], friction, resObj)) {
        friction = -1.0;
    }
    if (SystemProperties::ConfigChangePerform()) {
        ListModel::GetInstance()->CreateWithResourceObjFriction(resObj);
    }
    ListModel::GetInstance()->SetFriction(friction);
}

void JSList::SetFocusWrapMode(const JSCallbackInfo& args)
{
    if (args.Length() < 1) {
        return;
    }
    auto focusWrapMode = static_cast<int32_t>(FocusWrapMode::DEFAULT);
    if (!JSViewAbstract::ParseJsInt32(args[0], focusWrapMode) ||
        focusWrapMode < static_cast<int32_t>(FocusWrapMode::DEFAULT) ||
        focusWrapMode > static_cast<int32_t>(FocusWrapMode::WRAP_WITH_ARROW)) {
        focusWrapMode = static_cast<int32_t>(FocusWrapMode::DEFAULT);
    }
    ListModel::GetInstance()->SetFocusWrapMode(static_cast<FocusWrapMode>(focusWrapMode));
}

void JSList::MaintainVisibleContentPosition(const JSCallbackInfo& args)
{
    bool enabled = false;
    JSRef<JSVal> arg0 = args[0];
    if (arg0->IsBoolean()) {
        enabled = arg0->ToBoolean();
    }
    ListModel::GetInstance()->SetMaintainVisibleContentPosition(enabled);
}

void JSList::SetStackFromEnd(const JSCallbackInfo& args)
{
    bool enabled = false;
    JSRef<JSVal> arg0 = args[0];
    if (arg0->IsBoolean()) {
        enabled = arg0->ToBoolean();
    }
    ListModel::GetInstance()->SetStackFromEnd(enabled);
}

void JSList::SetSyncLoad(const JSCallbackInfo& args)
{
    bool enabled = true;
    JSRef<JSVal> arg0 = args[0];
    if (arg0->IsBoolean()) {
        enabled = arg0->ToBoolean();
    }
    ListModel::GetInstance()->SetSyncLoad(enabled);
}

void JSList::ItemDeleteCallback(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto onItemDelete = [func = JSRef<JSFunc>::Cast(args[0])](int32_t index) -> bool {
            auto params = ConvertToJSValues(index);
            func->Call(JSRef<JSObject>(), params.size(), params.data());
            return true;
        };
        ListModel::GetInstance()->SetOnItemDelete(std::move(onItemDelete));
    }
    args.ReturnSelf();
}

void JSList::SetListItemIndex(JSRef<JSObject> listItemInfo, ListItemIndex indexInfo)
{
    listItemInfo->SetProperty<int32_t>("index", indexInfo.index);
    if (indexInfo.indexInGroup != -1) {
        listItemInfo->SetProperty<int32_t>("itemIndexInGroup", indexInfo.indexInGroup);
    }
    if (indexInfo.area != -1) {
        listItemInfo->SetProperty<int32_t>("itemGroupArea", indexInfo.area);
    }
}

void JSList::SetMultiSelectable(bool multiSelectable)
{
    ListModel::GetInstance()->SetMultiSelectable(multiSelectable);
}

void JSList::ScrollBeginCallback(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto onScrollBegin = [func = JSRef<JSFunc>::Cast(args[0])](
                                 const CalcDimension& dx, const CalcDimension& dy) -> ScrollInfo {
            ScrollInfo scrollInfo { .dx = dx, .dy = dy };
            auto params = ConvertToJSValues(dx, dy);
            auto result = func->Call(JSRef<JSObject>(), params.size(), params.data());
            if (result.IsEmpty()) {
                return scrollInfo;
            }

            if (!result->IsObject()) {
                return scrollInfo;
            }

            auto resObj = JSRef<JSObject>::Cast(result);
            auto dxRemainValue = resObj->GetProperty("dxRemain");
            if (dxRemainValue->IsNumber()) {
                scrollInfo.dx = CalcDimension(dxRemainValue->ToNumber<float>(), DimensionUnit::VP);
            }
            auto dyRemainValue = resObj->GetProperty("dyRemain");
            if (dyRemainValue->IsNumber()) {
                scrollInfo.dy = CalcDimension(dyRemainValue->ToNumber<float>(), DimensionUnit::VP);
            }
            return scrollInfo;
        };
        ListModel::GetInstance()->SetOnScrollBegin(std::move(onScrollBegin));
    }
}

void JSList::JSBind(BindingTarget globalObj)
{
    JSClass<JSList>::Declare("List");
    JSClass<JSList>::StaticMethod("create", &JSList::Create);
    JSClass<JSList>::StaticMethod("width", &JSList::JsWidth);
    JSClass<JSList>::StaticMethod("height", &JSList::JsHeight);
    JSClass<JSList>::StaticMethod("clip", &JSScrollable::JsClip);
    JSClass<JSList>::StaticMethod("listDirection", &JSList::SetDirection);
    JSClass<JSList>::StaticMethod("scrollBar", &JSList::SetScrollBar);
    JSClass<JSList>::StaticMethod("scrollBarWidth", &JSList::SetScrollBarWidth);
    JSClass<JSList>::StaticMethod("scrollBarColor", &JSList::SetScrollBarColor);
    JSClass<JSList>::StaticMethod("edgeEffect", &JSList::SetEdgeEffect);
    JSClass<JSList>::StaticMethod("divider", &JSList::SetDivider);
    JSClass<JSList>::StaticMethod("editMode", &JSList::SetEditMode);
    JSClass<JSList>::StaticMethod("cachedCount", &JSList::SetCachedCount);
    JSClass<JSList>::StaticMethod("chainAnimation", &JSList::SetChainAnimation);
    JSClass<JSList>::StaticMethod("chainAnimationOptions", &JSList::SetChainAnimationOptions);
    JSClass<JSList>::StaticMethod("childrenMainSize", &JSList::SetChildrenMainSize);
    JSClass<JSList>::StaticMethod("multiSelectable", &JSList::SetMultiSelectable);
    JSClass<JSList>::StaticMethod("alignListItem", &JSList::SetListItemAlign);
    JSClass<JSList>::StaticMethod("lanes", &JSList::SetLanes);
    JSClass<JSList>::StaticMethod("sticky", &JSList::SetSticky);
    JSClass<JSList>::StaticMethod("contentStartOffset", &JSList::SetContentStartOffset);
    JSClass<JSList>::StaticMethod("contentEndOffset", &JSList::SetContentEndOffset);
    JSClass<JSList>::StaticMethod("nestedScroll", &JSList::SetNestedScroll);
    JSClass<JSList>::StaticMethod("enableScrollInteraction", &JSList::SetScrollEnabled);
    JSClass<JSList>::StaticMethod("scrollSnapAlign", &JSList::SetScrollSnapAlign);
    JSClass<JSList>::StaticMethod("friction", &JSList::SetFriction);
    JSClass<JSList>::StaticMethod("focusWrapMode", &JSList::SetFocusWrapMode);
    JSClass<JSList>::StaticMethod("maintainVisibleContentPosition", &JSList::MaintainVisibleContentPosition);
    JSClass<JSList>::StaticMethod("stackFromEnd", &JSList::SetStackFromEnd);
    JSClass<JSList>::StaticMethod("syncLoad", &JSList::SetSyncLoad);
    JSClass<JSList>::StaticMethod("onScroll", &JSList::ScrollCallback);
    JSClass<JSList>::StaticMethod("onItemDelete", &JSList::ItemDeleteCallback);
    JSClass<JSList>::StaticMethod("onScrollBegin", &JSList::ScrollBeginCallback);
    JSClass<JSList>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSList>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSList>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSList>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSList>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSList>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSList>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSList>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSList>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);

    JSClass<JSList>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);

    JSClass<JSList>::InheritAndBind<JSScrollableBase>(globalObj);
}

void JSListScroller::JSBind(BindingTarget globalObj)
{
    JSClass<JSListScroller>::Declare("ListScroller");
    JSClass<JSListScroller>::CustomMethod("getItemRectInGroup", &JSListScroller::GetItemRectInGroup);
    JSClass<JSListScroller>::CustomMethod("scrollToItemInGroup", &JSListScroller::ScrollToItemInGroup);
    JSClass<JSListScroller>::CustomMethod("closeAllSwipeActions", &JSListScroller::CloseAllSwipeActions);
    JSClass<JSListScroller>::CustomMethod("getVisibleListContentInfo", &JSListScroller::GetVisibleListContentInfo);
    JSClass<JSListScroller>::InheritAndBind<JSScroller>(globalObj, JSListScroller::Constructor,
        JSListScroller::Destructor);
}

void JSListScroller::Constructor(const JSCallbackInfo& args)
{
    auto scroller = Referenced::MakeRefPtr<JSListScroller>();
    scroller->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(scroller));
}

void JSListScroller::Destructor(JSListScroller* scroller)
{
    if (scroller != nullptr) {
        scroller->DecRefCount();
    }
}

void JSListScroller::GetItemRectInGroup(const JSCallbackInfo& args)
{
    int32_t index = -1;
    int32_t indexInGroup = -1;
    // Parameter passed into function must be 2.
    if (args.Length() != 2 || !ConvertFromJSValue(args[0], index) || !ConvertFromJSValue(args[1], indexInGroup)) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
        return;
    }
    auto scrollController = GetController().Upgrade();
    if (scrollController) {
        ContainerScope scope(GetInstanceId());
        auto rectObj = CreateRectangle(scrollController->GetItemRectInGroup(index, indexInGroup));
        JSRef<JSVal> rect = JSRef<JSObject>::Cast(rectObj);
        args.SetReturnValue(rect);
    } else {
        JSException::Throw(ERROR_CODE_NAMED_ROUTE_ERROR, "%s", "Controller not bound to component.");
    }
}

void JSListScroller::GetVisibleListContentInfo(const JSCallbackInfo& args)
{
    if (args.Length() != ARGS_LENGTH) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter length failed.");
        return;
    }

    Dimension xOffset;
    Dimension yOffset;
    if (!ConvertFromJSValue(args[0], xOffset) ||
        !ConvertFromJSValue(args[1], yOffset)) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
        return;
    }
    auto scrollController =  GetController().Upgrade();
    if (!scrollController) {
        JSException::Throw(ERROR_CODE_NAMED_ROUTE_ERROR, "%s", "Controller not bound to component.");
        return;
    }

    ContainerScope scope(GetInstanceId());
    auto deltaX = xOffset.Value();
    auto deltaY = yOffset.Value();
    auto container = Container::Current();
    if (container) {
        auto context = container->GetPipelineContext();
        if (context) {
            deltaX = context->NormalizeToPx(xOffset);
            deltaY = context->NormalizeToPx(yOffset);
            JSRef<JSObject> retObj = JSRef<JSObject>::New();
            auto itemGroup = scrollController->GetItemIndexInGroup(deltaX, deltaY);
            retObj->SetProperty<int32_t>("index", itemGroup.index);
            if (itemGroup.area == -1) {
                retObj->SetProperty("itemGroupArea", JSVal::Undefined());
            } else {
                retObj->SetProperty<int32_t>("itemGroupArea", itemGroup.area);
            }

            if (itemGroup.indexInGroup == -1) {
                retObj->SetProperty("itemIndexInGroup", JSVal::Undefined());
            } else {
                retObj->SetProperty<int32_t>("itemIndexInGroup", itemGroup.indexInGroup);
            }

            args.SetReturnValue(retObj);
        }
    }
    return;
}

void JSListScroller::ScrollToItemInGroup(const JSCallbackInfo& args)
{
    int32_t index = 0;
    int32_t indexInGroup = 0;
    bool smooth = false;
    ScrollAlign align = ScrollAlign::NONE;

    if (args.Length() < 1) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
        return;
    }

    auto scrollController = GetController().Upgrade();
    if (!scrollController) {
        JSException::Throw(ERROR_CODE_NAMED_ROUTE_ERROR, "%s", "Controller not bound to component.");
        return;
    }

    if (!ConvertFromJSValue(args[0], index)) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
        return;
    }
    if (index < 0) {
        return;
    }

    if (args.Length() >= 2) { // 2 is param count
        if (!ConvertFromJSValue(args[1], indexInGroup)) {
            JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
            return;
        }
        if (indexInGroup < 0) {
            return;
        }
    }

    if (args.Length() >= 3) { // 3 is param count
        if (!args[2]->IsBoolean()) { // 2 is the param index of smooth
            JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
            return;
        }
        smooth = args[2]->ToBoolean(); // 2 is the param index of smooth
    }

    if (args.Length() == 4) { // 4 is param count
        if (!ConvertFromJSValue(args[3], ALIGN_TABLE, align)) { // 3 is param count of align
            JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
            return;
        }
    }

    ContainerScope scope(GetInstanceId());
    scrollController->JumpToItemInGroup(index, indexInGroup, smooth, align, SCROLL_FROM_JUMP);
}

void JSListScroller::CloseAllSwipeActions(const JSCallbackInfo& args)
{
    if (args.Length() != 0 && args.Length() != 1) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "too many parameters.");
        return;
    }
    OnFinishFunc onFinishCallBack;
    if (args.Length() == 1) {
        if (!args[0]->IsObject()) {
            JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "options param must be object.");
            return;
        }
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
        auto onFinishProperty = obj->GetProperty("onFinish");
        if (onFinishProperty->IsFunction()) {
            auto vm = args.GetVm();
            auto jsFunc = JSRef<JSFunc>::Cast(onFinishProperty);
            auto func = jsFunc->GetLocalHandle();
            onFinishCallBack = [vm, func = panda::CopyableGlobal(vm, func)]() {
                panda::LocalScope pandaScope(vm);
                panda::TryCatch trycatch(vm);
                func->Call(vm, func.ToLocal(), nullptr, 0);
            };
        } else {
            JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "onFinish param must be function.");
            return;
        }
    }
    auto scrollController = GetController().Upgrade();
    if (!scrollController) {
        JSException::Throw(ERROR_CODE_NAMED_ROUTE_ERROR, "%s", "Controller not bound to component.");
        return;
    }
    ContainerScope scope(GetInstanceId());
    scrollController->CloseAllSwipeActions(std::move(onFinishCallBack));
}
} // namespace OHOS::Ace::Framework
