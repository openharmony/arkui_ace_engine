/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "drag_event.h"

#include <algorithm>

#include "frameworks/core/components_ng/event/gesture_event_hub.h"


namespace OHOS::Ace {

// PasteData
void PasteData::SetPlainText(const std::string& plainText)
{
    plainText_ = plainText;
}

const std::string& PasteData::GetPlainText() const
{
    return plainText_;
}

// DragEvent
void DragEvent::SetPasteData(const RefPtr<PasteData>& pasteData)
{
    pasteData_ = pasteData;
}

RefPtr<PasteData> DragEvent::GetPasteData() const
{
    return pasteData_;
}

double DragEvent::GetScreenX() const
{
    return screenX_;
}

double DragEvent::GetScreenY() const
{
    return screenY_;
}

void DragEvent::SetScreenX(double x)
{
    screenX_ = x;
}

void DragEvent::SetScreenY(double y)
{
    screenY_ = y;
}

double DragEvent::GetX() const
{
    return x_;
}

double DragEvent::GetY() const
{
    return y_;
}

void DragEvent::SetX(double x)
{
    x_ = x;
}

void DragEvent::SetY(double y)
{
    y_ = y;
}

double DragEvent::GetDisplayX() const
{
    return displayX_;
}

double DragEvent::GetDisplayY() const
{
    return displayY_;
}

void DragEvent::SetDisplayX(double x)
{
    displayX_ = x;
}

void DragEvent::SetDisplayY(double y)
{
    displayY_ = y;
}

double DragEvent::GetGlobalDisplayX() const
{
    return globalDisplayX_;
}

double DragEvent::GetGlobalDisplayY() const
{
    return globalDisplayY_;
}

void DragEvent::SetGlobalDisplayX(double x)
{
    globalDisplayX_ = x;
}

void DragEvent::SetGlobalDisplayY(double y)
{
    globalDisplayY_ = y;
}

void DragEvent::SetDescription(const std::string& description)
{
    description_ = description;
}

const std::string& DragEvent::GetDescription() const
{
    return description_;
}

void DragEvent::SetPixmap(const RefPtr<PixelMap>& pixelMap)
{
    pixelMap_ = pixelMap;
}

RefPtr<PixelMap> DragEvent::GetPixmap() const
{
    return pixelMap_;
}

void DragEvent::SetSummary(std::map<std::string, int64_t>& summary)
{
    summary_ = summary;
}

std::map<std::string, int64_t>& DragEvent::GetSummary()
{
    return summary_;
}

void DragEvent::SetResult(DragRet dragRet)
{
    dragRet_ = dragRet;
}

DragRet DragEvent::GetResult()
{
    return dragRet_;
}

Rect DragEvent::GetPreviewRect()
{
    return previewRect_;
}

void DragEvent::SetPreviewRect(Rect previewRect)
{
    previewRect_ = previewRect;
}

void DragEvent::UseCustomAnimation(bool useCustomAnimation)
{
    useCustomAnimation_ = useCustomAnimation;
}

bool DragEvent::IsUseCustomAnimation()
{
    return useCustomAnimation_;
}

void DragEvent::SetDragAnimationType(DragAnimationType dragAnimationType)
{
    dragAnimationType_ = dragAnimationType;
}

void DragEvent::SetDragAnimationType(int32_t dragAnimationType)
{
    dragAnimationType_ = static_cast<DragAnimationType>(dragAnimationType);
}

DragAnimationType DragEvent::GetDragAnimationType() const
{
    return dragAnimationType_;
}

int32_t DragEvent::GetDragAnimationTypeValue() const
{
    return static_cast<int32_t>(dragAnimationType_);
}

void DragEvent::SetFollowHandMorphDropAnimation(std::function<void()>&& onAnimationFinished)
{
    executeFollowHandMorphDropAnimation_ = std::move(onAnimationFinished);
}

bool DragEvent::HasFollowHandMorphDropAnimation() const
{
    return (executeFollowHandMorphDropAnimation_ != nullptr);
}

void DragEvent::ExecuteFollowHandMorphDropAnimation()
{
    if (executeFollowHandMorphDropAnimation_) {
        auto executeFollowHandMorphDropAnimation = executeFollowHandMorphDropAnimation_;
        executeFollowHandMorphDropAnimation();
    }
}

void DragEvent::SetFollowHandMorphAnimationOption(const std::string& animationOption)
{
    followHandMorphAnimationOption_ = animationOption;
}

const std::string& DragEvent::GetFollowHandMorphAnimationOption() const
{
    return followHandMorphAnimationOption_;
}

void DragEvent::SetCopy(bool copy)
{
    copy_ = copy;
}

bool DragEvent::IsCopy()
{
    return copy_;
}

void DragEvent::SetDragBehavior(DragBehavior dragBehavior)
{
    dragBehavior_ = dragBehavior;
}

DragBehavior DragEvent::GetDragBehavior() const
{
    return dragBehavior_;
}

void DragEvent::SetAutoHideComponentUniqueIds(const std::vector<int32_t>& autoHideComponentUniqueIds)
{
    autoHideComponentUniqueIds_.clear();
    for (auto uniqueId : autoHideComponentUniqueIds) {
        if (std::find(autoHideComponentUniqueIds_.begin(), autoHideComponentUniqueIds_.end(), uniqueId) ==
            autoHideComponentUniqueIds_.end()) {
            autoHideComponentUniqueIds_.emplace_back(uniqueId);
        }
    }
}

const std::vector<int32_t>& DragEvent::GetAutoHideComponentUniqueIds() const
{
    return autoHideComponentUniqueIds_;
}

void DragEvent::SetUdKey(const std::string& udKey)
{
    udKey_ = udKey;
}

const std::string& DragEvent::GetUdKey()
{
    return udKey_;
}

void DragEvent::SetIsGetDataSuccess(bool isGetDataSuccess)
{
    isGetDataSuccess_ = isGetDataSuccess;
}

bool DragEvent::IsGetDataSuccess()
{
    return isGetDataSuccess_;
}

void DragEvent::SetData(const RefPtr<UnifiedData>& unifiedData)
{
    unifiedData_ = unifiedData;
}

RefPtr<UnifiedData>& DragEvent::GetData()
{
    return unifiedData_;
}

void DragEvent::SetDragInfo(const RefPtr<UnifiedData>& dragInfo)
{
    dragInfo_ = dragInfo;
}

RefPtr<UnifiedData>& DragEvent::GetDragInfo()
{
    return dragInfo_;
}

void DragEvent::SetVelocity(const Velocity& velocity)
{
    velocity_ = velocity;
}

const Velocity& DragEvent::GetVelocity() const
{
    return velocity_;
}

void DragEvent::SetSourceTool(SourceTool sourceTool)
{
    sourceTool_ = sourceTool;
}

SourceTool DragEvent::GetSourceTool() const
{
    return sourceTool_;
}

const std::vector<KeyCode>& DragEvent::GetPressedKeyCodes() const
{
    return pressedKeyCodes_;
}

void DragEvent::SetPressedKeyCodes(const std::vector<KeyCode>& pressedKeyCodes)
{
    pressedKeyCodes_ = pressedKeyCodes;
}

void DragEvent::SetCapi(bool isCapi)
{
    isCapi_ = isCapi;
}

bool DragEvent::IsCapi()
{
    return isCapi_;
}

void DragEvent::SetDropAnimation(std::function<void()>&& executeDropAnimation)
{
    executeDropAnimation_ = std::move(executeDropAnimation);
}

bool DragEvent::HasDropAnimation() const
{
    return (executeDropAnimation_ != nullptr);
}

void DragEvent::ExecuteDropAnimation()
{
    if (executeDropAnimation_) {
        auto executeDropAnimation = executeDropAnimation_;
        executeDropAnimation();
    }
}

void DragEvent::SetIsDragEndPending(bool isDragEndPending)
{
    isDragEndPending_ = isDragEndPending;
}

bool DragEvent::IsDragEndPending() const
{
    return isDragEndPending_;
}

void DragEvent::SetRequestIdentify(int32_t requestId)
{
    requestId_ = requestId;
}

int32_t DragEvent::GetRequestIdentify() const
{
    return requestId_;
}

void DragEvent::SetDisplayId(int32_t displayId)
{
    displayId_ = displayId;
}

int32_t DragEvent::GetDisplayId() const
{
    return displayId_;
}

void DragEvent::SetDragSource(const std::string& bundleName)
{
    bundleName_ = bundleName;
}

const std::string& DragEvent::GetDragSource() const
{
    return bundleName_;
}

void DragEvent::SetRemoteDev(bool isRemoteDev)
{
    isRemoteDev_ = isRemoteDev;
}

bool DragEvent::isRemoteDev() const
{
    return isRemoteDev_;
}

void DragEvent::SetNeedDoInternalDropAnimation(bool needDoInternalDropAnimation)
{
    needDoInternalDropAnimation_ = needDoInternalDropAnimation;
}

bool DragEvent::GetNeedDoInternalDropAnimation() const
{
    return needDoInternalDropAnimation_;
}

void DragEvent::SetDataLoadParams(const RefPtr<DataLoadParams>& dataLoadParams)
{
    dataLoadParams_ = dataLoadParams;
}

RefPtr<DataLoadParams> DragEvent::GetDataLoadParams() const
{
    return dataLoadParams_;
}

void DragEvent::SetUseDataLoadParams(bool useDataLoadParams)
{
    useDataLoadParams_ = useDataLoadParams;
}

bool DragEvent::IsUseDataLoadParams() const
{
    return useDataLoadParams_;
}

RefPtr<PixelMap> DragEvent::GetDragDropInfoPixelMap() const
{
    return dragDropInfoPixelMap_;
}

void* DragEvent::GetDragDropInfoCustomNode() const
{
    return dragDropInfoCustomNode_;
}

std::string DragEvent::GetDragDropInfoExtraInfo() const
{
    return dragDropInfoExtraInfo_;
}

void DragEvent::SetDragDropInfoPixelMap(RefPtr<PixelMap> pixelMap)
{
    dragDropInfoPixelMap_ = pixelMap;
}

void DragEvent::SetDragDropInfoCustomNode(void* customNode)
{
    dragDropInfoCustomNode_ = customNode;
}

void DragEvent::SetDragDropInfoExtraInfo(std::string& extraInfo)
{
    dragDropInfoExtraInfo_ = extraInfo;
}

// DragSpringLoadingContext
void DragSpringLoadingContext::SetState(DragSpringLoadingState state)
{
    state_ = state;
}

DragSpringLoadingState DragSpringLoadingContext::GetState() const
{
    return state_;
}

void DragSpringLoadingContext::SetCurrentNotifySequence(int32_t currentNotifySequence)
{
    currentNotifySequence_ = currentNotifySequence;
}

int32_t DragSpringLoadingContext::GetCurrentNotifySequence() const
{
    return currentNotifySequence_;
}

void DragSpringLoadingContext::SetExtraInfos(std::string_view extraInfos)
{
    extraInfos_ = extraInfos.data();
}

const std::string& DragSpringLoadingContext::GetExtraInfos() const
{
    return extraInfos_;
}

void DragSpringLoadingContext::SetSummary(const std::map<std::string, int64_t>& summary)
{
    summary_ = summary;
}

const std::map<std::string, int64_t>& DragSpringLoadingContext::GetSummary() const
{
    return summary_;
}

void DragSpringLoadingContext::SetSpringLoadingAborted()
{
    isSpringLoadingAborted_ = true;
}

bool DragSpringLoadingContext::IsSpringLoadingAborted() const
{
    return isSpringLoadingAborted_;
}

const RefPtr<NG::DragSpringLoadingConfiguration>& DragSpringLoadingContext::GetDragSpringLoadingConfiguration() const
{
    return DragSpringLoadingConfiguration_;
}

void DragSpringLoadingContext::SetDragSpringLoadingConfiguration(
    const RefPtr<NG::DragSpringLoadingConfiguration>& dragSpringLoadingConfiguration)
{
    DragSpringLoadingConfiguration_ = dragSpringLoadingConfiguration;
}

} // namespace OHOS::Ace
