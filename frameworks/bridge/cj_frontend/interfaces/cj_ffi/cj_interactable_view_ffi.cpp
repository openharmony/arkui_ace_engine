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

#include <cstddef>
#include <cstdint>
#include <vector>

#include "cj_common_ffi.h"
#include "cj_lambda.h"

#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_model.h"
#ifndef _NON_OHOS_
#include "pixel_map_impl.h"

#include "adapter/ohos/osal/pixel_map_ohos.h"
#endif

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace {
const std::vector<NG::TouchTestStrategy> TOUCH_TEST_STRATEGY = { NG::TouchTestStrategy::DEFAULT,
    NG::TouchTestStrategy::FORWARD_COMPETITION, NG::TouchTestStrategy::FORWARD };

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

bool CheckKeysPressed(const std::vector<KeyCode>& pressedKeyCodes, std::vector<std::string>& checkKeyCodes)
{
    auto hasKeyCode = [pressedKeyCodes](const KeyCode& keyCode) -> bool {
        auto it = std::find(pressedKeyCodes.begin(), pressedKeyCodes.end(), keyCode);
        return it != pressedKeyCodes.end();
    };
    for (auto& checkKeyCode : checkKeyCodes)
        if (checkKeyCode == "ctrl") {
            if (!hasKeyCode(KeyCode::KEY_CTRL_LEFT) && !hasKeyCode(KeyCode::KEY_CTRL_RIGHT)) {
                return false;
            }
        } else if (checkKeyCode == "shift") {
            if (!hasKeyCode(KeyCode::KEY_SHIFT_LEFT) && !hasKeyCode(KeyCode::KEY_SHIFT_RIGHT)) {
                return false;
            }
        } else if (checkKeyCode == "alt") {
            if (!hasKeyCode(KeyCode::KEY_ALT_LEFT) && !hasKeyCode(KeyCode::KEY_ALT_RIGHT)) {
                return false;
            }
        } else if (checkKeyCode == "fn") {
            if (!hasKeyCode(KeyCode::KEY_FN)) {
                return false;
            }
        } else {
            return false;
        }
    return true;
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

VectorTouchTestInfoHandle FFICJCreateVectorTouchTestInfo(int64_t size)
{
    return new std::vector<CJTouchTestInfo>(size);
}

void FFICJVectorTouchTestInfoSetElement(VectorTouchTestInfoHandle vec, int64_t index, CJTouchTestInfo touchTestInfo)
{
    auto actualVec = reinterpret_cast<std::vector<CJTouchTestInfo>*>(vec);
    (*actualVec)[index] = touchTestInfo;
}

CJTouchTestInfo FFICJVectorTouchTestInfoGetElement(VectorTouchTestInfoHandle vec, int64_t index)
{
    auto actualVec = reinterpret_cast<std::vector<CJTouchTestInfo>*>(vec);
    return (*actualVec)[index];
}

void FFICJVectorTouchTestInfoDelete(VectorTouchTestInfoHandle vec)
{
    auto actualVec = reinterpret_cast<std::vector<CJTouchTestInfo>*>(vec);
    delete actualVec;
}

int64_t FFICJVectorTouchTestInfoGetSize(VectorTouchTestInfoHandle vec)
{
    auto actualVec = reinterpret_cast<std::vector<CJTouchTestInfo>*>(vec);
    return (*actualVec).size();
}

void FfiOHOSAceFrameworkInteractableOnChildTouchTest(CJTouchResult (*callback)(VectorTouchTestInfoHandle handle))
{
    auto onChildTouchTest = [ffiCallback = CJLambda::Create(callback)](
                                const std::vector<NG::TouchTestInfo>& touchInfo) -> NG::TouchResult {
        NG::TouchResult touchRes;
        auto arr = new std::vector<CJTouchTestInfo>(touchInfo.size());
        size_t size = touchInfo.size();
        for (size_t i = 0; i < size; i++) {
            CJTouchTestInfo tmp;
            tmp.windowX = touchInfo[i].windowPoint.GetX();
            tmp.windowY = touchInfo[i].windowPoint.GetY();
            tmp.parentX = touchInfo[i].currentCmpPoint.GetX();
            tmp.parentY = touchInfo[i].currentCmpPoint.GetY();
            tmp.x = touchInfo[i].subCmpPoint.GetX();
            tmp.y = touchInfo[i].subCmpPoint.GetY();
            tmp.rect.x = static_cast<double>(touchInfo[i].subRect.GetX());
            tmp.rect.y = static_cast<double>(touchInfo[i].subRect.GetY());
            tmp.rect.width = static_cast<double>(touchInfo[i].subRect.Width());
            tmp.rect.height = static_cast<double>(touchInfo[i].subRect.Height());
            tmp.id = Utils::MallocCString(touchInfo[i].id);
            (*arr)[i] = tmp;
        }
        auto ret = ffiCallback(arr);
        touchRes.strategy = static_cast<NG::TouchTestStrategy>(ret.strategy);
        touchRes.id = ret.id.value;
        return touchRes;
    };
    ViewAbstractModel::GetInstance()->SetOnTouchTestFunc(std::move(onChildTouchTest));
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
    auto onKeyEvent = [ffiCallback = CJLambda::Create(callback)](KeyEventInfo& keyInfo) -> bool {
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
        return ret;
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

void FfiInteractableViewOnDragStart(CJDragItemInfo (*callback)(CJDragEvent event, const char* extraParams))
{
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto cjCallback = [func = CJLambda::Create(callback), node = frameNode](
                          const RefPtr<DragEvent>& info, const std::string& extraParams) -> NG::DragDropBaseInfo {
        NG::DragDropBaseInfo dragDropInfo;
        PipelineContext::SetCallBackNode(node);
        CJDragEvent cjEvent { .evtPtr = new RefPtr<DragEvent>(info),
            .useCustomDropAnimation = info->IsUseCustomAnimation(),
            .dragBehavior = static_cast<int32_t>(info->GetDragBehavior()) };
        auto ret = func(cjEvent, extraParams.c_str());
        auto retNode = ParseDragNode(ret.builder);
#if defined(PIXEL_MAP_SUPPORTED)
        dragDropInfo.pixelMap = ParseDragPixelMap(ret.pixelMapId);
#endif
        dragDropInfo.extraInfo = ret.extraInfo;
        dragDropInfo.node = retNode;
        return dragDropInfo;
    };
    ViewAbstractModel::GetInstance()->SetOnDragStart(std::move(cjCallback));
}

void FfiDragEventSetResult(void* ptr, int32_t result)
{
    auto dragEvent = *reinterpret_cast<RefPtr<DragEvent>*>(ptr);
    CHECK_NULL_VOID(dragEvent);
    auto res = static_cast<DragRet>(result);
    dragEvent->SetResult(res);
}

int32_t FfiDragEventGetResult(void* ptr)
{
    auto dragEvent = *reinterpret_cast<RefPtr<DragEvent>*>(ptr);
    CHECK_NULL_RETURN(dragEvent, -1);
    return static_cast<int32_t>(dragEvent->GetResult());
}

NativeRectangle FfiDragEventGetPreviewRect(void* ptr)
{
    auto dragEvent = *reinterpret_cast<RefPtr<DragEvent>*>(ptr);
    CHECK_NULL_RETURN(dragEvent, NativeRectangle {});
    auto rect = dragEvent->GetPreviewRect();
    NativeRectangle resRect { .x = rect.GetOffset().GetX(),
        .xUnit = static_cast<int32_t>(DimensionUnit::VP),
        .y = rect.GetOffset().GetY(),
        .yUnit = static_cast<int32_t>(DimensionUnit::VP),
        .width = rect.Width(),
        .widthUnit = static_cast<int32_t>(DimensionUnit::PERCENT),
        .height = rect.Height(),
        .heightUnit = static_cast<int32_t>(DimensionUnit::PERCENT) };
    return resRect;
}

double FfiDragEventGetVelocityX(void* ptr)
{
    auto dragEvent = *reinterpret_cast<RefPtr<DragEvent>*>(ptr);
    CHECK_NULL_RETURN(dragEvent, 0.0);
    auto velocity = dragEvent->GetVelocity();
    return PipelineBase::Px2VpWithCurrentDensity(velocity.GetVelocityX());
}

double FfiDragEventGetVelocityY(void* ptr)
{
    auto dragEvent = *reinterpret_cast<RefPtr<DragEvent>*>(ptr);
    CHECK_NULL_RETURN(dragEvent, 0.0);
    auto velocity = dragEvent->GetVelocity();
    return PipelineBase::Px2VpWithCurrentDensity(velocity.GetVelocityY());
}

double FfiDragEventGetVelocity(void* ptr)
{
    auto dragEvent = *reinterpret_cast<RefPtr<DragEvent>*>(ptr);
    CHECK_NULL_RETURN(dragEvent, 0.0);
    auto velocity = dragEvent->GetVelocity();
    return PipelineBase::Px2VpWithCurrentDensity(velocity.GetVelocityValue());
}

double FfiDragEventGetWindowX(void* ptr)
{
    auto dragEvent = *reinterpret_cast<RefPtr<DragEvent>*>(ptr);
    CHECK_NULL_RETURN(dragEvent, 0.0);
    return PipelineBase::Px2VpWithCurrentDensity(dragEvent->GetX());
}

double FfiDragEventGetWindowY(void* ptr)
{
    auto dragEvent = *reinterpret_cast<RefPtr<DragEvent>*>(ptr);
    CHECK_NULL_RETURN(dragEvent, 0.0);
    return PipelineBase::Px2VpWithCurrentDensity(dragEvent->GetY());
}

double FfiDragEventGetDisplayX(void* ptr)
{
    auto dragEvent = *reinterpret_cast<RefPtr<DragEvent>*>(ptr);
    CHECK_NULL_RETURN(dragEvent, 0.0);
    return PipelineBase::Px2VpWithCurrentDensity(dragEvent->GetScreenX());
}

double FfiDragEventGetDisplayY(void* ptr)
{
    auto dragEvent = *reinterpret_cast<RefPtr<DragEvent>*>(ptr);
    CHECK_NULL_RETURN(dragEvent, 0.0);
    return PipelineBase::Px2VpWithCurrentDensity(dragEvent->GetScreenY());
}

void FfiDragEventFree(void* ptr)
{
    RefPtr<DragEvent>* evtPtr = reinterpret_cast<RefPtr<DragEvent>*>(ptr);
    if (evtPtr != nullptr) {
        delete evtPtr;
    }
}

bool FfiDragEventGetModifierKeyState(void* ptr, VectorStringHandle keys)
{
    auto dragEvent = *reinterpret_cast<RefPtr<DragEvent>*>(ptr);
    CHECK_NULL_RETURN(dragEvent, false);
    auto keyVec = reinterpret_cast<std::vector<std::string>*>(keys);
    auto pressedKeyCodes = dragEvent->GetPressedKeyCodes();
    std::vector<std::string> checkKeyCodes;
    std::vector<std::string> validKeyCodes = { "ctrl", "shift", "alt", "fn" };
    for (size_t i = 0; i < keyVec->size(); i++) {
        auto code = (*keyVec)[0];
        std::transform(code.begin(), code.end(), code.begin(), [](char& c) { return std::tolower(c); });
        auto it = std::find(validKeyCodes.begin(), validKeyCodes.end(), code.c_str());
        if (it == validKeyCodes.end()) {
            return false;
        } else {
            checkKeyCodes.emplace_back(code);
        }
    }
    if (checkKeyCodes.empty()) {
        return false;
    }
    return CheckKeysPressed(pressedKeyCodes, checkKeyCodes);
}

void FfiInteractableViewOnDragEnter(void (*callback)(CJDragEvent event, const char* extraParams))
{
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto cjCallback = [func = CJLambda::Create(callback), node = frameNode](
                          const RefPtr<DragEvent>& info, const std::string& extraParams) {
        PipelineContext::SetCallBackNode(node);
        CJDragEvent cjEvent { .evtPtr = new RefPtr<DragEvent>(info),
            .useCustomDropAnimation = info->IsUseCustomAnimation(),
            .dragBehavior = static_cast<int32_t>(info->GetDragBehavior()) };
        func(cjEvent, extraParams.c_str());
    };
    ViewAbstractModel::GetInstance()->SetOnDragEnter(std::move(cjCallback));
}

void FfiInteractableViewOnDragMove(void (*callback)(CJDragEvent event, const char* extraParams))
{
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto cjCallback = [func = CJLambda::Create(callback), node = frameNode](
                          const RefPtr<DragEvent>& info, const std::string& extraParams) {
        PipelineContext::SetCallBackNode(node);
        CJDragEvent cjEvent { .evtPtr = new RefPtr<DragEvent>(info),
            .useCustomDropAnimation = info->IsUseCustomAnimation(),
            .dragBehavior = static_cast<int32_t>(info->GetDragBehavior()) };
        func(cjEvent, extraParams.c_str());
    };
    ViewAbstractModel::GetInstance()->SetOnDragMove(std::move(cjCallback));
}

void FfiInteractableViewOnDragLeave(void (*callback)(CJDragEvent event, const char* extraParams))
{
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto cjCallback = [func = CJLambda::Create(callback), node = frameNode](
                          const RefPtr<DragEvent>& info, const std::string& extraParams) {
        PipelineContext::SetCallBackNode(node);
        CJDragEvent cjEvent { .evtPtr = new RefPtr<DragEvent>(info),
            .useCustomDropAnimation = info->IsUseCustomAnimation(),
            .dragBehavior = static_cast<int32_t>(info->GetDragBehavior()) };
        func(cjEvent, extraParams.c_str());
    };
    ViewAbstractModel::GetInstance()->SetOnDragLeave(std::move(cjCallback));
}

void FfiInteractableViewOnDrop(void (*callback)(CJDragEvent event, const char* extraParams))
{
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto cjCallback = [func = CJLambda::Create(callback), node = frameNode](
                          const RefPtr<DragEvent>& info, const std::string& extraParams) {
        PipelineContext::SetCallBackNode(node);
        CJDragEvent cjEvent { .evtPtr = new RefPtr<DragEvent>(info),
            .useCustomDropAnimation = info->IsUseCustomAnimation(),
            .dragBehavior = static_cast<int32_t>(info->GetDragBehavior()) };
        func(cjEvent, extraParams.c_str());
    };
    ViewAbstractModel::GetInstance()->SetOnDrop(std::move(cjCallback));
}

void FfiInteractableViewOnDragEnd(void (*callback)(CJDragEvent event, const char* extraParams))
{
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto cjCallback = [func = CJLambda::Create(callback), node = frameNode](const RefPtr<DragEvent>& info) {
        PipelineContext::SetCallBackNode(node);
        CJDragEvent cjEvent { .evtPtr = new RefPtr<DragEvent>(info),
            .useCustomDropAnimation = info->IsUseCustomAnimation(),
            .dragBehavior = static_cast<int32_t>(info->GetDragBehavior()) };
        func(cjEvent, nullptr);
    };
    ViewAbstractModel::GetInstance()->SetOnDragEnd(std::move(cjCallback));
}

void FfiInteractableViewOnPreDrag(void (*callback)(int32_t status))
{
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto cjCallback = [func = CJLambda::Create(callback), node = frameNode](const PreDragStatus preDragStatus) {
        PipelineContext::SetCallBackNode(node);
        func(static_cast<int32_t>(preDragStatus));
    };
    ViewAbstractModel::GetInstance()->SetOnPreDrag(std::move(cjCallback));
}
}
