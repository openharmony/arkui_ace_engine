/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_view_measure_layout.h"

#include "jsnapi.h"

#include "base/geometry/dimension.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "frameworks/core/components_ng/base/frame_node.h"
#include "frameworks/core/components_ng/pattern/custom/custom_measure_layout_node.h"

namespace OHOS::Ace::Framework {

#ifdef USE_ARK_ENGINE

namespace {
JSRef<JSObject> GenConstraint(const std::optional<NG::LayoutConstraintF>& parentConstraint)
{
    auto minSize = parentConstraint->minSize;
    auto maxSize = parentConstraint->maxSize;
    JSRef<JSObject> constraint = JSRef<JSObject>::New();
    constraint->SetProperty<double>("minWidth", minSize.Width());
    constraint->SetProperty<double>("minHeight", minSize.Height());
    constraint->SetProperty<double>("maxWidth", maxSize.Width());
    constraint->SetProperty<double>("maxHeight", maxSize.Height());
    return constraint;
}

JSRef<JSObject> GenConstraintNG(const NG::LayoutConstraintF& parentConstraint)
{
    auto minSize = parentConstraint.minSize;
    auto maxSize = parentConstraint.maxSize;
    JSRef<JSObject> constraint = JSRef<JSObject>::New();
    auto pipeline = PipelineBase::GetCurrentContext();
    constraint->SetProperty<double>("minWidth", minSize.Width() / pipeline->GetDipScale());
    constraint->SetProperty<double>("minHeight", minSize.Height() / pipeline->GetDipScale());
    constraint->SetProperty<double>("maxWidth", maxSize.Width() / pipeline->GetDipScale());
    constraint->SetProperty<double>("maxHeight", maxSize.Height() / pipeline->GetDipScale());
    return constraint;
}

JSRef<JSObject> GenPadding(const std::unique_ptr<NG::PaddingProperty>& paddingNative)
{
    JSRef<JSObject> padding = JSRef<JSObject>::New();
    padding->SetProperty("top", paddingNative->top->GetDimension().ConvertToVp());
    padding->SetProperty("right", paddingNative->right->GetDimension().ConvertToVp());
    padding->SetProperty("bottom", paddingNative->bottom->GetDimension().ConvertToVp());
    padding->SetProperty("left", paddingNative->left->GetDimension().ConvertToVp());
    return padding;
}

JSRef<JSObject> GenMargin(const std::unique_ptr<NG::MarginProperty>& marginNative)
{
    JSRef<JSObject> margin = JSRef<JSObject>::New();
    margin->SetProperty("top", marginNative->top->GetDimension().ConvertToVp());
    margin->SetProperty("right", marginNative->right->GetDimension().ConvertToVp());
    margin->SetProperty("bottom", marginNative->bottom->GetDimension().ConvertToVp());
    margin->SetProperty("left", marginNative->left->GetDimension().ConvertToVp());
    return margin;
}

JSRef<JSObject> GenEdgeWidths(const std::unique_ptr<NG::BorderWidthProperty>& edgeWidthsNative)
{
    JSRef<JSObject> edgeWidths = JSRef<JSObject>::New();
    edgeWidths->SetProperty("top", edgeWidthsNative->topDimen->ConvertToVp());
    edgeWidths->SetProperty("right", edgeWidthsNative->rightDimen->ConvertToVp());
    edgeWidths->SetProperty("bottom", edgeWidthsNative->bottomDimen->ConvertToVp());
    edgeWidths->SetProperty("left", edgeWidthsNative->leftDimen->ConvertToVp());
    return edgeWidths;
}

JSRef<JSObject> GenBorderInfo(const RefPtr<NG::LayoutWrapper>& layoutWrapper)
{
    JSRef<JSObject> borderInfo = JSRef<JSObject>::New();
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    const std::unique_ptr<NG::PaddingProperty> defaultPadding = std::make_unique<NG::PaddingProperty>();
    const std::unique_ptr<NG::PaddingProperty> defaultMargin = std::make_unique<NG::MarginProperty>();
    const std::unique_ptr<NG::BorderWidthProperty>& defaultEdgeWidth = std::make_unique<NG::BorderWidthProperty>();
    if (!layoutProperty) {
        borderInfo->SetPropertyObject("borderWidth", GenEdgeWidths(defaultEdgeWidth));
        borderInfo->SetPropertyObject("margin", GenMargin(defaultPadding));
        borderInfo->SetPropertyObject("padding", GenPadding(defaultPadding));
        return borderInfo;
    }

    borderInfo->SetPropertyObject("borderWidth",
        GenEdgeWidths(
            layoutProperty->GetBorderWidthProperty() ? layoutProperty->GetBorderWidthProperty() : defaultEdgeWidth));

    borderInfo->SetPropertyObject("margin",
        GenMargin(layoutProperty->GetMarginProperty() ? layoutProperty->GetMarginProperty() : defaultMargin));
    borderInfo->SetPropertyObject("padding",
        GenPadding(layoutProperty->GetPaddingProperty() ? layoutProperty->GetPaddingProperty() : defaultPadding));

    return borderInfo;
}

JSRef<JSObject> GenPositionInfo(const RefPtr<NG::LayoutWrapper>& layoutWrapper)
{
    auto offset = layoutWrapper->GetGeometryNode()->GetFrameOffset();
    JSRef<JSObject> position = JSRef<JSObject>::New();
    position->SetProperty("x", offset.GetX());
    position->SetProperty("y", offset.GetY());
    return position;
}

JSRef<JSObject> GenSelfLayoutInfo(RefPtr<NG::LayoutProperty> layoutProperty)
{
    JSRef<JSObject> selfLayoutInfo = JSRef<JSObject>::New();
    const std::unique_ptr<NG::PaddingProperty> defaultPadding = std::make_unique<NG::PaddingProperty>();
    const std::unique_ptr<NG::PaddingProperty> defaultMargin = std::make_unique<NG::MarginProperty>();
    const std::unique_ptr<NG::BorderWidthProperty>& defaultEdgeWidth = std::make_unique<NG::BorderWidthProperty>();
    if (!layoutProperty) {
        selfLayoutInfo->SetPropertyObject("borderWidth", GenEdgeWidths(defaultEdgeWidth));
        selfLayoutInfo->SetPropertyObject("margin", GenMargin(defaultPadding));
        selfLayoutInfo->SetPropertyObject("padding", GenPadding(defaultPadding));
        selfLayoutInfo->SetProperty("width", 0.0f);
        selfLayoutInfo->SetProperty("height", 0.0f);
        return selfLayoutInfo;
    }
    auto parentNode = AceType::DynamicCast<NG::FrameNode>(layoutProperty->GetHost()->GetParent());
    auto pipeline = PipelineBase::GetCurrentContext();
    if (parentNode && parentNode->GetTag() == V2::COMMON_VIEW_ETS_TAG) {
        layoutProperty = parentNode->GetLayoutProperty();
    }
    auto host = layoutProperty->GetHost();
    NG::RectF originGeoRect;
    if (host) {
        originGeoRect = host->GetGeometryNode()->GetFrameRect();
    }
    auto width =
        GreatNotEqual(originGeoRect.Width(), 0.0f) ? originGeoRect.Width() / pipeline->GetDipScale()
        : layoutProperty->GetLayoutConstraint()
            ? layoutProperty->GetLayoutConstraint()->selfIdealSize.Width().value_or(0.0) / pipeline->GetDipScale()
            : 0.0f;
    auto height =
        GreatNotEqual(originGeoRect.Height(), 0.0f) ? originGeoRect.Height() / pipeline->GetDipScale()
        : layoutProperty->GetLayoutConstraint()
            ? layoutProperty->GetLayoutConstraint()->selfIdealSize.Height().value_or(0.0) / pipeline->GetDipScale()
            : 0.0f;

    selfLayoutInfo->SetPropertyObject("borderWidth",
        GenEdgeWidths(
            layoutProperty->GetBorderWidthProperty() ? layoutProperty->GetBorderWidthProperty() : defaultEdgeWidth));
    selfLayoutInfo->SetPropertyObject("margin",
        GenMargin(layoutProperty->GetMarginProperty() ? layoutProperty->GetMarginProperty() : defaultPadding));
    selfLayoutInfo->SetPropertyObject("padding",
        GenPadding(layoutProperty->GetPaddingProperty() ? layoutProperty->GetPaddingProperty() : defaultPadding));
    selfLayoutInfo->SetProperty(
        "width", NearEqual(width, 0.0f)
                     ? layoutProperty->GetLayoutConstraint()->percentReference.Width() / pipeline->GetDipScale()
                     : width);
    selfLayoutInfo->SetProperty(
        "height", NearEqual(height, 0.0f)
                      ? layoutProperty->GetLayoutConstraint()->percentReference.Height() / pipeline->GetDipScale()
                      : height);
    return selfLayoutInfo;
}

void FillSubComponentProperty(
    JSRef<JSObjTemplate>& info, const RefPtr<NG::LayoutWrapper>& layoutWrapper, const size_t& index)
{
    info->SetProperty<std::string>("name", layoutWrapper->GetHostNode()->GetTag());
    info->SetProperty<std::string>("id", std::to_string(layoutWrapper->GetHostNode()->GetId()));
    info->SetPropertyObject("constraint", GenConstraint(layoutWrapper->GetLayoutProperty()->GetLayoutConstraint()));
    info->SetPropertyObject("borderInfo", GenBorderInfo(layoutWrapper));
    info->SetPropertyObject("position", GenPositionInfo(layoutWrapper));
}

void FillPlaceSizeProperty(JSRef<JSObjTemplate>& info, const NG::SizeF& size)
{
    JSRef<JSObject> measureResult = JSRef<JSObject>::New();
    Dimension measureWidth(size.Width(), DimensionUnit::PX);
    Dimension measureHeight(size.Height(), DimensionUnit::PX);
    measureResult->SetProperty("width", measureWidth.ConvertToVp());
    measureResult->SetProperty("height", measureHeight.ConvertToVp());
    info->SetPropertyObject("measureResult", measureResult);
}
} // namespace

JSMeasureLayoutParam::JSMeasureLayoutParam(NG::LayoutWrapper* layoutWrapper) : MeasureLayoutParam(layoutWrapper)
{
    Init();
}

void JSMeasureLayoutParam::Init()
{
    int32_t count = GetTotalChildCount();
    childArray_ = JSRef<JSArray>::New(count);
    GenChildArray(0, count);
}

void JSMeasureLayoutParam::GenChildArray(int32_t start, int32_t end)
{
    JSRef<JSFunc> measureFunc = JSRef<JSFunc>::New<FunctionCallback>(ViewMeasureLayout::JSMeasure);
    JSRef<JSFunc> layoutFunc = JSRef<JSFunc>::New<FunctionCallback>(ViewMeasureLayout::JSLayout);
    for (int32_t index = start; index < end; index++) {
        JSRef<JSObjTemplate> info = JSRef<JSObjTemplate>::New();
        info->SetInternalFieldCount(1);
        FillSubComponentProperty(info, GetOrCreateChildByIndex(index), index);
        info->Wrap<NG::MeasureLayoutChild>(&Get(index));
        info->SetPropertyObject("measure", measureFunc);
        info->SetPropertyObject("layout", layoutFunc);
        childArray_->SetValueAt(index, info);
    }
}

JSRef<JSObject> JSMeasureLayoutParam::GetConstraint()
{
    auto layoutWrapper = GetLayoutWrapper();
    auto parentConstraint = layoutWrapper->GetGeometryNode()->GetParentLayoutConstraint();
    return GenConstraint(parentConstraint);
}

void JSMeasureLayoutParam::Update(NG::LayoutWrapper* layoutWrapper)
{
    NG::MeasureLayoutChild* addr = nullptr;
    int32_t count = GetTotalChildCount();
    if (count > 0) {
        addr = &Get(0);
    }
    MeasureLayoutParam::Update(layoutWrapper);
    int32_t newCount = GetTotalChildCount();
    if (count == newCount) {
        return;
    }
    childArray_->SetLength(newCount);
    if (count < newCount) {
        GenChildArray(count, newCount);
    }
    if (addr != &Get(0)) {
        for (int32_t index = 0; index < count; index++) {
            auto info = JSRef<JSObjTemplate>::Cast(childArray_->GetValueAt(index));
            info->Wrap<NG::MeasureLayoutChild>(&Get(index));
        }
    }
}

RefPtr<JSMeasureLayoutParam> JSMeasureLayoutParam::GetInstance(NG::LayoutWrapper* layoutWrapper)
{
    auto host = AceType::DynamicCast<NG::CustomMeasureLayoutNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_RETURN(host, nullptr);
    auto jsParam = AceType::DynamicCast<JSMeasureLayoutParam>(host->GetMeasureLayoutParam());
    if (!jsParam) {
        jsParam = AceType::MakeRefPtr<JSMeasureLayoutParam>(layoutWrapper);
        host->SetMeasureLayoutParam(jsParam);
    } else {
        jsParam->Update(layoutWrapper);
    }
    return jsParam;
}

JSMeasureLayoutParamNG::JSMeasureLayoutParamNG(NG::LayoutWrapper* layoutWrapper) : MeasureLayoutParam(layoutWrapper)
{
    Init();
}

void JSMeasureLayoutParamNG::Init()
{
    int32_t count = GetTotalChildCount();
    childArray_ = JSRef<JSArray>::New(count);
    GenChildArray(0, count);
}

void JSMeasureLayoutParamNG::GenChildArray(int32_t start, int32_t end)
{
    JSRef<JSObject> size = JSRef<JSObject>::New();
    size->SetProperty("width", 0);
    size->SetProperty("height", 0);
    JSRef<JSFunc> measureFunc = JSRef<JSFunc>::New<FunctionCallback>(ViewMeasureLayout::JSMeasure);
    JSRef<JSFunc> layoutFunc = JSRef<JSFunc>::New<FunctionCallback>(ViewMeasureLayout::JSPlaceChildren);
    for (int32_t index = start; index < end; index++) {
        JSRef<JSObjTemplate> info = JSRef<JSObjTemplate>::New();
        info->SetInternalFieldCount(1);
        info->SetPropertyObject("measureResult", size);
        info->Wrap<NG::MeasureLayoutChild>(&Get(index));
        info->SetPropertyObject("measure", measureFunc);
        info->SetPropertyObject("layout", layoutFunc);
        childArray_->SetValueAt(index, info);
    }
}

JSRef<JSObject> JSMeasureLayoutParamNG::GetConstraint()
{
    auto layoutWrapper = GetLayoutWrapper();
    auto layoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint().value();
    return GenConstraintNG(layoutConstraint);
}

JSRef<JSObject> JSMeasureLayoutParamNG::GetSelfLayoutInfo()
{
    auto layoutWrapper = GetLayoutWrapper();
    return GenSelfLayoutInfo(layoutWrapper->GetLayoutProperty());
}

void JSMeasureLayoutParamNG::UpdateSize(int32_t index, const NG::SizeF& size)
{
    auto info = JSRef<JSObjTemplate>::Cast(childArray_->GetValueAt(index));
    FillPlaceSizeProperty(info, size);
}

void JSMeasureLayoutParamNG::Update(NG::LayoutWrapper* layoutWrapper)
{
    NG::MeasureLayoutChild* addr = nullptr;
    int32_t count = GetTotalChildCount();
    if (count > 0) {
        addr = &Get(0);
    }
    MeasureLayoutParam::Update(layoutWrapper);
    int32_t newCount = GetTotalChildCount();
    if (count == newCount) {
        return;
    }
    childArray_->SetLength(newCount);
    if (count < newCount) {
        GenChildArray(count, newCount);
    }
    if (addr != &Get(0)) {
        for (int32_t index = 0; index < count; index++) {
            auto info = JSRef<JSObjTemplate>::Cast(childArray_->GetValueAt(index));
            info->Wrap<NG::MeasureLayoutChild>(&Get(index));
        }
    }
}

RefPtr<JSMeasureLayoutParamNG> JSMeasureLayoutParamNG::GetInstance(NG::LayoutWrapper* layoutWrapper)
{
    auto host = AceType::DynamicCast<NG::CustomMeasureLayoutNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_RETURN(host, nullptr);
    auto jsParam = AceType::DynamicCast<JSMeasureLayoutParamNG>(host->GetMeasureLayoutParam());
    if (!jsParam) {
        jsParam = AceType::MakeRefPtr<JSMeasureLayoutParamNG>(layoutWrapper);
        host->SetMeasureLayoutParam(jsParam);
    } else {
        jsParam->Update(layoutWrapper);
    }
    return jsParam;
}

panda::Local<panda::JSValueRef> ViewMeasureLayout::JSMeasure(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    ACE_SCOPED_TRACE("ViewMeasureLayout::JSMeasure");
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> thisObj = runtimeCallInfo->GetThisRef();
    auto ptr = static_cast<NG::MeasureLayoutChild*>(panda::Local<panda::ObjectRef>(thisObj)->GetNativePointerField(0));
    auto child = ptr->GetOrCreateChild();
    if (!child) {
        return panda::JSValueRef::Undefined(vm);
    }

    auto childLayoutConstraint = ptr->CreateChildConstraint();
    auto layoutProperty = child->GetLayoutProperty();
    auto info = runtimeCallInfo;
    if (info->GetArgsNumber() >= 1 && info->GetCallArgRef(0)->IsObject()) {
        auto jsObject = JsiObject(info->GetCallArgRef(0)->ToObject(vm));
        JSRef<JSObject> sizeObj = JSRef<JSObject>::Make(jsObject);
        CalcDimension minWidth;
        if (JSViewAbstract::ParseJsDimensionVp(sizeObj->GetProperty("minWidth"), minWidth)) {
            if (layoutProperty) {
                layoutProperty->UpdateCalcMinSize(NG::CalcSize(NG::CalcLength(minWidth), std::nullopt));
            } else {
                auto length = ConvertToPx(NG::CalcLength(minWidth), childLayoutConstraint.scaleProperty,
                    childLayoutConstraint.percentReference.Width());
                if (length) {
                    childLayoutConstraint.minSize.SetWidth(length.value());
                }
            }
        }

        CalcDimension maxWidth;
        if (JSViewAbstract::ParseJsDimensionVp(sizeObj->GetProperty("maxWidth"), maxWidth)) {
            if (layoutProperty) {
                layoutProperty->UpdateCalcMaxSize(NG::CalcSize(NG::CalcLength(maxWidth), std::nullopt));
            } else {
                auto length = ConvertToPx(NG::CalcLength(maxWidth), childLayoutConstraint.scaleProperty,
                    childLayoutConstraint.percentReference.Width());
                if (length) {
                    childLayoutConstraint.maxSize.SetWidth(length.value());
                }
            }
        }

        CalcDimension minHeight;
        if (JSViewAbstract::ParseJsDimensionVp(sizeObj->GetProperty("minHeight"), minHeight)) {
            if (layoutProperty) {
                layoutProperty->UpdateCalcMinSize(NG::CalcSize(std::nullopt, NG::CalcLength(minHeight)));
            } else {
                auto length = ConvertToPx(NG::CalcLength(minHeight), childLayoutConstraint.scaleProperty,
                    childLayoutConstraint.percentReference.Height());
                if (length) {
                    childLayoutConstraint.minSize.SetHeight(length.value());
                }
            }
        }

        CalcDimension maxHeight;
        if (JSViewAbstract::ParseJsDimensionVp(sizeObj->GetProperty("maxHeight"), maxHeight)) {
            if (layoutProperty) {
                layoutProperty->UpdateCalcMaxSize(NG::CalcSize(std::nullopt, NG::CalcLength(maxHeight)));
            } else {
                auto length = ConvertToPx(NG::CalcLength(maxHeight), childLayoutConstraint.scaleProperty,
                    childLayoutConstraint.percentReference.Height());
                if (length) {
                    childLayoutConstraint.maxSize.SetHeight(length.value());
                }
            }
        }
    }
    child->Measure(childLayoutConstraint);

    auto size = child->GetGeometryNode()->GetFrameSize();
    ptr->UpdateSize(size);
    Dimension measureWidth(size.Width(), DimensionUnit::PX);
    Dimension measureHeight(size.Height(), DimensionUnit::PX);
    Local<ObjectRef> measureResultObject = ObjectRef::New(vm);
    measureResultObject->Set(vm, ToJSValue("width"), ToJSValue(measureWidth.ConvertToVp()));
    measureResultObject->Set(vm, ToJSValue("height"), ToJSValue(measureHeight.ConvertToVp()));
    return measureResultObject;
}

panda::Local<panda::JSValueRef> ViewMeasureLayout::JSLayout(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    ACE_SCOPED_TRACE("ViewMeasureLayout::JSLayout");
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> thisObj = runtimeCallInfo->GetThisRef();
    auto ptr = static_cast<NG::MeasureLayoutChild*>(panda::Local<panda::ObjectRef>(thisObj)->GetNativePointerField(0));
    auto child = ptr->GetChild();
    if (!child) {
        return panda::JSValueRef::Undefined(vm);
    }

    auto info = runtimeCallInfo;
    if (info->GetArgsNumber() != 1 || !info->GetCallArgRef(0)->IsObject()) {
        LOGE("JSLayout arg is wrong");
        child->Layout();
        return panda::JSValueRef::Undefined(vm);
    }

    auto jsObject = JsiObject(info->GetCallArgRef(0)->ToObject(vm));
    JSRef<JSObject> layoutInfo = JSRef<JSObject>::Make(jsObject);
    JSRef<JSObject> sizeObj = layoutInfo->GetProperty("position");
    JSRef<JSVal> xVal = sizeObj->GetProperty("x");
    JSRef<JSVal> yVal = sizeObj->GetProperty("y");
    CalcDimension dimenX;
    CalcDimension dimenY;
    auto xResult = JSViewAbstract::ParseJsDimensionVp(xVal, dimenX);
    auto yResult = JSViewAbstract::ParseJsDimensionVp(yVal, dimenY);
    if (!(xResult || yResult)) {
        LOGE("the position prop is illegal");
    } else {
        child->GetGeometryNode()->SetMarginFrameOffset({ dimenX.ConvertToPx(), dimenY.ConvertToPx() });
    }
    child->Layout();

    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::JSValueRef> ViewMeasureLayout::JSPlaceChildren(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    ACE_SCOPED_TRACE("ViewMeasureLayout::JSPlaceChildren");
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> thisObj = runtimeCallInfo->GetThisRef();
    auto ptr = static_cast<NG::MeasureLayoutChild*>(panda::Local<panda::ObjectRef>(thisObj)->GetNativePointerField(0));
    auto child = ptr->GetChild();
    if (!child) {
        return panda::JSValueRef::Undefined(vm);
    }

    auto info = runtimeCallInfo;
    if (info->GetArgsNumber() != 1 || !info->GetCallArgRef(0)->IsObject()) {
        LOGE("JSPlaceChildren arg is wrong");
        child->Layout();
        return panda::JSValueRef::Undefined(vm);
    }

    auto jsObject = JsiObject(info->GetCallArgRef(0)->ToObject(vm));
    JSRef<JSObject> layoutInfo = JSRef<JSObject>::Make(jsObject);
    JSRef<JSVal> xVal = layoutInfo->GetProperty("x");
    JSRef<JSVal> yVal = layoutInfo->GetProperty("y");
    CalcDimension dimenX;
    CalcDimension dimenY;
    auto xResult = JSViewAbstract::ParseJsDimensionVp(xVal, dimenX);
    auto yResult = JSViewAbstract::ParseJsDimensionVp(yVal, dimenY);
    if (!(xResult || yResult)) {
        LOGE("the position prop is illegal");
    } else {
        child->GetGeometryNode()->SetMarginFrameOffset({ dimenX.ConvertToPx(), dimenY.ConvertToPx() });
    }
    child->Layout();
    return panda::JSValueRef::Undefined(vm);
}

#endif

} // namespace OHOS::Ace::Framework