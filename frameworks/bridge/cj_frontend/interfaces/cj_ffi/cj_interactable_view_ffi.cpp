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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_interactable_view_ffi.h"

#include "cj_lambda.h"

#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_model.h"
#ifndef _NON_OHOS_
#include "foundation/multimedia/image_framework/frameworks/kits/cj/include/pixel_map_impl.h"

#include "adapter/ohos/osal/pixel_map_ohos.h"
#endif

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace {
void FFiSetDragInfo(
    const RefPtr<DragEvent>& info, const std::string& extraParams, CJPosition& cjPosition, CJDragInfo& ffiDragInfo)
{
    cjPosition.x = info->GetX();
    cjPosition.y = info->GetY();
    ffiDragInfo.extraParams = extraParams.c_str();
}

RefPtr<AceType> ParseDragNode(void (*builder)())
{
    if (builder == nullptr) {
        return nullptr;
    }
    std::function<void(void)> builderFunc = CJLambda::Create(builder);
    // use another VSP instance while executing the builder function
    ViewStackModel::GetInstance()->NewScope();
    {
        builderFunc();
    }
    return ViewStackModel::GetInstance()->Finish();
}

RefPtr<PixelMap> ParseDragPixelMap(int64_t pixelMapId)
{
#ifndef _NON_OHOS_
    if (pixelMapId == 0) {
        return nullptr;
    }
    auto pixelMapImpl = OHOS::FFI::FFIData::GetData<OHOS::Media::PixelMapImpl>(pixelMapId);
    if (pixelMapImpl == nullptr) {
        LOGE("DragStart error, Cannot get PixelMapProxy by id: %{public}" PRId64, pixelMapId);
        return nullptr;
    }
    auto pixMap = pixelMapImpl->GetRealPixelMap();
    if (pixMap == nullptr) {
        LOGE("DragStart error, Cannot get pixMap in PixelMapProxy");
        return nullptr;
    }
    auto pixMapOhos = PixelMap::CreatePixelMap(&pixMap);
    if (pixMapOhos == nullptr) {
        LOGE("DragStart error, Cannot create PixelMapOhos by pixMap");
        return nullptr;
    }
    return pixMapOhos;
#else
    return nullptr;
#endif
}

} // namespace OHOS::Ace

extern "C" {
std::string CJClickInfo::ToString() const
{
    std::string result = "x: " + std::to_string(x);
    result = result + ", y: " + std::to_string(y);
    result = result + ", windowX: " + std::to_string(windowX);
    result = result + ", windowY: " + std::to_string(windowY);
    result = result + ", displayX: " + std::to_string(displayX);
    result = result + ", displayY: " + std::to_string(displayY);
    result = result + ", timestamp: " + std::to_string(timestamp);
    result = result + ", target.area.width: " + std::to_string(target->area->width);
    result = result + ", target.area.height: " + std::to_string(target->area->width);
    result = result + ", target.area.position.x: " + std::to_string(target->area->position->x);
    result = result + ", target.area.position.y: " + std::to_string(target->area->position->y);
    result = result + ", target.area.globalPosition.x: " + std::to_string(target->area->globalPosition->y);
    result = result + ", target.area.globalPosition.y: " + std::to_string(target->area->globalPosition->y);
    return result;
}

std::string CJTouchEvent::ToString() const
{
    std::string result = "type: " + std::to_string(eventType);
    result = result + ", touchesSize: " + std::to_string(touchesSize);
    result = result + ", changedTouchesSize: " + std::to_string(changedTouchesSize);
    return result;
}

void FfiOHOSAceFrameworkInteractableViewOnClick(void (*callback)(CJClickInfo clickInfo))
{
    auto lambda = [ffiOnClick = CJLambda::Create(callback)](const GestureEvent& event) -> void {
        CJClickInfo cjClickInfo {};
        CJEventTarget cjEventTarget {};
        CJArea cjArea {};
        CJPosition cjPosition {};
        CJPosition cjGlobalPosition {};
        AssambleCJClickInfo(event, cjClickInfo, cjEventTarget, cjArea, cjPosition, cjGlobalPosition);
        ffiOnClick(cjClickInfo);
    };
    ViewAbstractModel::GetInstance()->SetOnClick(std::move(lambda), nullptr);
}

void FfiOHOSAceFrameworkInteractableViewOnTouch(bool (*callback)(CJTouchEvent touchInfo))
{
    auto onTouch = [ffiCallback = CJLambda::Create(callback)](TouchEventInfo& touchEventInfo) {
        CJTouchEvent ffiTouchInfo;

        auto& touches = touchEventInfo.GetTouches();
        ffiTouchInfo.touches = new CJTouchInfo[touches.size()];
        TransformNativeTouchLocationInfo(ffiTouchInfo.touches, touches);
        ffiTouchInfo.touchesSize = static_cast<int32_t>(touches.size());

        auto& changedTouches = touchEventInfo.GetChangedTouches();
        auto changeTouchArr = new CJTouchInfo[changedTouches.size()];
        TransformNativeTouchLocationInfo(changeTouchArr, touchEventInfo.GetChangedTouches());
        ffiTouchInfo.changedTouches = changeTouchArr;
        ffiTouchInfo.changedTouchesSize = static_cast<int32_t>(changedTouches.size());

        ffiTouchInfo.eventType = 0;
        if (changedTouches.size() > 0) {
            ffiTouchInfo.eventType = static_cast<uint8_t>(changedTouches.front().GetTouchType());
        }
        ffiTouchInfo.timestamp = touchEventInfo.GetTimeStamp().time_since_epoch().count();
        ffiTouchInfo.sourceType = static_cast<int32_t>(touchEventInfo.GetSourceDevice());
        CJArea cjArea {};
        CJEventTarget cjEventTarget {};
        CJPosition cjPosition {};
        CJPosition cjGlobalPosition {};
        AssambleCJEventTarget(touchEventInfo.GetTarget(), cjArea, cjPosition, cjGlobalPosition);
        cjArea.position = &cjPosition;
        cjArea.globalPosition = &cjGlobalPosition;
        cjEventTarget.area = &cjArea;

        ffiTouchInfo.target = &cjEventTarget;

        auto flag = ffiCallback(ffiTouchInfo);
        touchEventInfo.SetStopPropagation(flag);
        delete[] ffiTouchInfo.touches;
        delete[] ffiTouchInfo.changedTouches;
    };
    ViewAbstractModel::GetInstance()->SetOnTouch(std::move(onTouch));
}
void FfiOHOSAceFrameworkInteractableViewOnAppear(void (*callback)())
{
    auto onAppear = CJLambda::Create(callback);
    ViewAbstractModel::GetInstance()->SetOnAppear([onAppear]() { onAppear(); });
}

void FfiOHOSAceFrameworkInteractableViewOnDisAppear(void (*callback)())
{
    auto onDisappear = CJLambda::Create(callback);
    ViewAbstractModel::GetInstance()->SetOnDisAppear([onDisappear]() { onDisappear(); });
}

void FfiOHOSAceFrameworkInteractableViewOnHover(void (*callback)(bool))
{
    auto onHover = CJLambda::Create(callback);
    ViewAbstractModel::GetInstance()->SetOnHover([onHover](bool param, HoverInfo& info) { onHover(param); });
}

void FfiOHOSAceFrameworkInteractableViewOnAreaChanged(void (*callback)(CJArea, CJArea))
{
    auto onAreaChanged = CJLambda::Create(callback);
    ViewAbstractModel::GetInstance()->SetOnAreaChanged([onAreaChanged](const Rect& lastRect, const Offset& lastOrigin,
                                                           const Rect& rect, const Offset& origin) {
        CJArea lastCjArea {};
        lastCjArea.width = PipelineBase::Px2VpWithCurrentDensity(lastRect.Width());
        lastCjArea.height = PipelineBase::Px2VpWithCurrentDensity(lastRect.Height());
        CJPosition lastCjPosition {};
        CJPosition lastCjGlobalPosition {};
        lastCjPosition.x = PipelineBase::Px2VpWithCurrentDensity(lastRect.GetOffset().GetX());
        lastCjPosition.y = PipelineBase::Px2VpWithCurrentDensity(lastRect.GetOffset().GetY());
        lastCjGlobalPosition.x = PipelineBase::Px2VpWithCurrentDensity(lastRect.GetOffset().GetX() + lastOrigin.GetX());
        lastCjGlobalPosition.y = PipelineBase::Px2VpWithCurrentDensity(lastRect.GetOffset().GetY() + lastOrigin.GetY());
        lastCjArea.position = &lastCjPosition;
        lastCjArea.globalPosition = &lastCjGlobalPosition;

        CJArea cjArea {};
        cjArea.width = PipelineBase::Px2VpWithCurrentDensity(rect.Width());
        cjArea.height = PipelineBase::Px2VpWithCurrentDensity(rect.Height());
        CJPosition cjPosition {};
        CJPosition cjGlobalPosition {};
        cjPosition.x = PipelineBase::Px2VpWithCurrentDensity(rect.GetOffset().GetX());
        cjPosition.y = PipelineBase::Px2VpWithCurrentDensity(rect.GetOffset().GetY());
        cjGlobalPosition.x = PipelineBase::Px2VpWithCurrentDensity(rect.GetOffset().GetX() + origin.GetX());
        cjGlobalPosition.y = PipelineBase::Px2VpWithCurrentDensity(rect.GetOffset().GetY() + origin.GetY());
        cjArea.position = &cjPosition;
        cjArea.globalPosition = &cjGlobalPosition;

        onAreaChanged(lastCjArea, cjArea);
    });
}

void FfiOHOSAceFrameworkInteractableViewOnVisibleAreaChange(
    VectorFloat64Handle raitosValsHandle, void (*callback)(bool isVisible, double currentRatio))
{
    auto onVisibleChange = CJLambda::Create(callback);
    const auto& ratios = *reinterpret_cast<std::vector<double>*>(raitosValsHandle);

    ViewAbstractModel::GetInstance()->SetOnVisibleChange(
        [onVisibleChange](bool isVisible, double currentRatio) { onVisibleChange(isVisible, currentRatio); }, ratios);
}

void FfiOHOSAceFrameworkInteractableViewOnMouse(void (*callback)(CJMouseEvent))
{
    auto onMouse = [func = CJLambda::Create(callback)](MouseInfo& mouseInfo) {
        CJMouseEvent cjMouseEvent {};
        cjMouseEvent.timestamp = static_cast<int64_t>(mouseInfo.GetTimeStamp().time_since_epoch().count());
        Offset globalOffset = mouseInfo.GetGlobalLocation();
        Offset localOffset = mouseInfo.GetLocalLocation();
        cjMouseEvent.screenX = PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetX());
        cjMouseEvent.screenY = PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetY());
        cjMouseEvent.x = PipelineBase::Px2VpWithCurrentDensity(localOffset.GetX());
        cjMouseEvent.y = PipelineBase::Px2VpWithCurrentDensity(localOffset.GetY());
        cjMouseEvent.button = static_cast<int32_t>(mouseInfo.GetButton());
        cjMouseEvent.action = static_cast<int32_t>(mouseInfo.GetAction());
        func(cjMouseEvent);
    };

    ViewAbstractModel::GetInstance()->SetOnMouse(std::move(onMouse));
}

// can not trigged this event on eTS app
void FfiOHOSAceFrameworkInteractableViewOnKey(bool (*callback)(CJKeyEvent info))
{
    auto onKeyEvent = [ffiCallback = CJLambda::Create(callback)](KeyEventInfo& keyInfo) -> void {
        CJKeyEvent ffiKeyInfo {};
        ffiKeyInfo.keyText = keyInfo.GetKeyText();
        ffiKeyInfo.type = static_cast<int32_t>(keyInfo.GetKeyType());
        ffiKeyInfo.keyCode = static_cast<int32_t>(keyInfo.GetKeyCode());
        ffiKeyInfo.keySource = static_cast<int32_t>(keyInfo.GetKeySource());
        ffiKeyInfo.metaKey = keyInfo.GetMetaKey();
        ffiKeyInfo.deviceId = keyInfo.GetDeviceId();
        ffiKeyInfo.timestamp = keyInfo.GetTimeStamp().time_since_epoch().count();
        auto ret = ffiCallback(ffiKeyInfo);
        keyInfo.SetStopPropagation(ret);
    };
    ViewAbstractModel::GetInstance()->SetOnKeyEvent(onKeyEvent);
}

void FfiOHOSAceFrameworkInteractableViewOnDelete(void (*callback)())
{
    ViewAbstractModel::GetInstance()->SetOnDelete(CJLambda::Create(callback));
}

void FfiOHOSAceFrameworkInteractableViewOnFocus(void (*callback)())
{
    ViewAbstractModel::GetInstance()->SetOnFocus(CJLambda::Create(callback));
}

void FfiOHOSAceFrameworkInteractableViewOnBlur(void (*callback)())
{
    ViewAbstractModel::GetInstance()->SetOnBlur(CJLambda::Create(callback));
}

void FfiOHOSAceFrameworkInteractableViewOnDragStart(CJDragItemInfo (*callback)(CJDragInfo info), uint32_t componentName)
{
    if (!Container::IsCurrentUseNewPipeline()) {
        LOGE("not supported");
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto ffiCallback = CJLambda::Create(callback);
    auto onDragStart = [ffiCallback, fnode = frameNode](
                           const RefPtr<DragEvent>& info, const std::string& extraParams) -> NG::DragDropBaseInfo {
        LOGD("extraParams: %{public}s", extraParams.c_str());
        PipelineContext::SetCallBackNode(fnode);
        NG::DragDropBaseInfo itemInfo;
        CJDragInfo ffiDragInfo {};
        CJPosition cjPosition {};
        FFiSetDragInfo(info, extraParams, cjPosition, ffiDragInfo);
        ffiDragInfo.position = &cjPosition;
        auto ret = ffiCallback(ffiDragInfo);
        LOGD("piexlMapId: %{public}" PRId64 ", extraInfo: %{public}s", ret.pixelMapId, ret.extraInfo);
        auto node = ParseDragNode(ret.builder);
#if defined(PIXEL_MAP_SUPPORTED)
        itemInfo.pixelMap = ParseDragPixelMap(ret.pixelMapId);
#endif
        itemInfo.extraInfo = ret.extraInfo;
        itemInfo.node = node;
        return itemInfo;
    };

    ViewAbstractModel::GetInstance()->SetOnDragStart(std::move(onDragStart));
}

void FfiOHOSAceFrameworkInteractableViewOnDragEnter(void (*callback)(CJDragInfo info), uint32_t componentName)
{
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto ffiCallback = CJLambda::Create(callback);
    auto onDragEnter = [ffiCallback, fnode = frameNode](const RefPtr<DragEvent>& info, const std::string& extraParams) {
        LOGD("extraParams: %{public}s", extraParams.c_str());
        PipelineContext::SetCallBackNode(fnode);
        NG::DragDropBaseInfo itemInfo;
        CJDragInfo ffiDragInfo {};
        CJPosition cjPosition {};
        FFiSetDragInfo(info, extraParams, cjPosition, ffiDragInfo);
        ffiDragInfo.position = &cjPosition;
        ffiCallback(ffiDragInfo);
    };

    ViewAbstractModel::GetInstance()->SetOnDragEnter(std::move(onDragEnter));
}

void FfiOHOSAceFrameworkInteractableViewOnDragMove(void (*callback)(CJDragInfo info), uint32_t componentName)
{
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto ffiCallback = CJLambda::Create(callback);
    auto onDragMove = [ffiCallback, fnode = frameNode](const RefPtr<DragEvent>& info, const std::string& extraParams) {
        LOGD("extraParams: %{public}s", extraParams.c_str());
        PipelineContext::SetCallBackNode(fnode);
        NG::DragDropBaseInfo itemInfo;
        CJDragInfo ffiDragInfo {};
        CJPosition cjPosition {};
        FFiSetDragInfo(info, extraParams, cjPosition, ffiDragInfo);
        ffiDragInfo.position = &cjPosition;
        ffiCallback(ffiDragInfo);
    };

    ViewAbstractModel::GetInstance()->SetOnDragMove(std::move(onDragMove));
}

void FfiOHOSAceFrameworkInteractableViewOnDragLeave(void (*callback)(CJDragInfo info), uint32_t componentName)
{
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto ffiCallback = CJLambda::Create(callback);
    auto onDragLeave = [ffiCallback, fnode = frameNode](const RefPtr<DragEvent>& info, const std::string& extraParams) {
        LOGD("extraParams: %{public}s", extraParams.c_str());
        PipelineContext::SetCallBackNode(fnode);
        NG::DragDropBaseInfo itemInfo;
        CJDragInfo ffiDragInfo {};
        CJPosition cjPosition {};
        FFiSetDragInfo(info, extraParams, cjPosition, ffiDragInfo);
        ffiDragInfo.position = &cjPosition;
        ffiCallback(ffiDragInfo);
    };

    ViewAbstractModel::GetInstance()->SetOnDragLeave(std::move(onDragLeave));
}

void FfiOHOSAceFrameworkInteractableViewOnDrop(void (*callback)(CJDragInfo info), uint32_t componentName)
{
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto ffiCallback = CJLambda::Create(callback);
    auto onDrop = [ffiCallback, fnode = frameNode](const RefPtr<DragEvent>& info, const std::string& extraParams) {
        LOGD("extraParams: %{public}s", extraParams.c_str());
        PipelineContext::SetCallBackNode(fnode);
        NG::DragDropBaseInfo itemInfo;
        CJDragInfo ffiDragInfo {};
        CJPosition cjPosition {};
        FFiSetDragInfo(info, extraParams, cjPosition, ffiDragInfo);
        ffiDragInfo.position = &cjPosition;
        ffiCallback(ffiDragInfo);
    };

    ViewAbstractModel::GetInstance()->SetOnDrop(std::move(onDrop));
}
}
