/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_nav_path_stack_ffi.h"

#include "cj_lambda.h"

#include "bridge/cj_frontend/runtime/cj_runtime_delegate.h"

namespace OHOS::Ace::Framework {

napi_value CJNavPathInfoNG::GetParamObj() const
{
    return nullptr;
}

void CJNavPathInfoNG::UpdateNavPathInfo(const RefPtr<NG::NavPathInfo>& info)
{
    NG::NavPathInfo::UpdateNavPathInfo(info);
    auto jsPathInfo = AceType::DynamicCast<CJNavPathInfoNG>(info);
    if (!jsPathInfo) {
        return;
    }
    param_ = jsPathInfo->GetParam();
}

bool CJNavPathStack::IsEmpty()
{
    return pathArray_.empty();
}

void CJNavPathStack::PushPath(CJNavPathInfo info, bool animated, LaunchMode launchMode)
{
    if (launchMode == LaunchMode::MOVE_TO_TOP_SINGLETON || launchMode == LaunchMode::POP_TO_SINGLETON) {
        int32_t index = -1;
        for (int i = 0; static_cast<unsigned long>(i) < pathArray_.size(); ++i) {
            if (pathArray_[i].name == info.name) {
                index = i;
                break;
            }
        }
        if (index != -1) {
            pathArray_[index].param = info.param;
            pathArray_[index].onPop = info.onPop;
            pathArray_[index].needUpdate = true;
            pathArray_[index].isEntry = info.isEntry;
            if (launchMode == LaunchMode::MOVE_TO_TOP_SINGLETON) {
                MoveIndexToTop(index, animated);
            } else {
                InnerPopToIndex(index, std::nullopt, animated, false);
            }
            return;
        }
    }
    std::optional<CJNavPathInfo> popInfo = findInPopArray(info.name);
    if (popInfo.has_value()) {
        auto data = popInfo.value();
        info.index = data.index;
        info.navDestinationId = data.navDestinationId;
    }
    pathArray_.push_back(info);
    isReplace_ = 0;
    animated_ = animated;
    OnStateChanged();
}

void CJNavPathStack::PushName(std::string name, std::string param)
{
    CJNavPathInfo info = CJNavPathInfo();
    info.name = name;
    info.param = param;
    std::optional<CJNavPathInfo> popInfo = findInPopArray(name);
    if (popInfo.has_value()) {
        auto data = popInfo.value();
        info.index = data.index;
        info.navDestinationId = data.navDestinationId;
    }
    pathArray_.push_back(info);
    isReplace_ = 0;
    OnStateChanged();
}

void CJNavPathStack::ReplacePath(CJNavPathInfo info, bool animated, LaunchMode launchMode)
{
    int32_t index = -1;
    if (launchMode == LaunchMode::MOVE_TO_TOP_SINGLETON || launchMode == LaunchMode::POP_TO_SINGLETON) {
        for (int i = 0; static_cast<unsigned long>(i) < pathArray_.size(); ++i) {
            if (pathArray_[i].name == info.name) {
                index = i;
                break;
            }
        }
        if (index != -1) {
            InnerReplacePathWithLaunchMode(index, info, launchMode);
        }
    }
    if (index == -1) {
        if (pathArray_.size() != 0) {
            pathArray_.pop_back();
        }
        info.index = -1;
        pathArray_.push_back(info);
    }
    isReplace_ = 1;
    animated_ = animated;
    OnStateChanged();
}

int32_t CJNavPathStack::RemoveByIndexes(std::vector<int32_t> indexes)
{
    if (pathArray_.size() == 0) {
        return 0;
    }
    int32_t originLength = static_cast<int32_t>(pathArray_.size());
    std::set<size_t> filterSet(indexes.begin(), indexes.end());
    std::vector<CJNavPathInfo> tmpPathArray;
    for (size_t i = 0; i < pathArray_.size(); ++i) {
        if (filterSet.find(i) == filterSet.end()) {
            tmpPathArray.push_back(pathArray_[i]);
        }
    }
    pathArray_ = tmpPathArray;
    int32_t cnt = originLength - static_cast<int32_t>(pathArray_.size());
    if (cnt > 0) {
        isReplace_ = 0;
        OnStateChanged();
    }
    return cnt;
}

void CJNavPathStack::RemoveIndex(int32_t index)
{
    if (pathArray_.size() == static_cast<unsigned long>(0) || static_cast<unsigned long>(index) >= pathArray_.size()) {
        return;
    }
    pathArray_.erase(pathArray_.begin() + index);
    isReplace_ = 0;
    OnStateChanged();
}

int32_t CJNavPathStack::RemoveByName(std::string name)
{
    if (pathArray_.size() == 0) {
        return 0;
    }
    int32_t originLength = static_cast<int32_t>(pathArray_.size());
    pathArray_.erase(
        std::remove_if(
            pathArray_.begin(),
            pathArray_.end(),
            [&](const CJNavPathInfo& cjNavPathInfo) { return name == cjNavPathInfo.name; }),
        pathArray_.end());
    int32_t cnt = originLength - static_cast<int32_t>(pathArray_.size());
    if (cnt > 0) {
        isReplace_ = 0;
        OnStateChanged();
    }
    return cnt;
}

bool CJNavPathStack::RemoveByNavDestinationId(std::string navDestinationId)
{
    int32_t index = -1;
    for (int i = 0; static_cast<unsigned long>(i) < pathArray_.size(); i++) {
        if (pathArray_[i].navDestinationId == navDestinationId) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        return false;
    }
    pathArray_.erase(pathArray_.begin() + index);
    isReplace_ = 0;
    OnStateChanged();
    return true;
}

CJNavPathInfo CJNavPathStack::Pop(std::string result, bool animated)
{
    if (pathArray_.size() == 0) {
        CJNavPathInfo ret = CJNavPathInfo();
        ret.valid = -1;
        return ret;
    }
    CJNavPathInfo pathInfo = pathArray_.back();
    pathArray_.pop_back();
    popArray_.push_back(pathInfo);
    isReplace_ = 0;
    if (!result.empty() && pathInfo.onPop) {
        auto popInfo = CJPopInfo();
        popInfo.info = pathInfo;
        popInfo.result = result;
        pathInfo.onPop(popInfo);
    }
    animated_ = animated;
    OnPopCallback(result);
    OnStateChanged();
    return pathInfo;
}

int32_t CJNavPathStack::PopToName(std::string name, std::string result, bool animated)
{
    if (pathArray_.size() == 0) {
        return -1;
    }
    auto it = std::find_if(pathArray_.begin(), pathArray_.end(),
        [&](const CJNavPathInfo& cjNavPathInfo) { return name == cjNavPathInfo.name; });
    int32_t index = -1;
    if (it != pathArray_.end()) {
        index = std::distance(pathArray_.begin(), it);
    }
    if (index == -1) {
        return -1;
    }
    CJNavPathInfo currentPathInfo = pathArray_.back();
    pathArray_.erase(it + 1, pathArray_.end());
    isReplace_ = 0;
    if (!result.empty() && currentPathInfo.onPop) {
        auto popInfo = CJPopInfo();
        popInfo.info = currentPathInfo;
        popInfo.result = result;
        currentPathInfo.onPop(popInfo);
    }
    animated_ = animated;
    OnPopCallback(result);
    OnStateChanged();
    return index;
}

void CJNavPathStack::PopToIndex(int32_t index, std::string result, bool animated)
{
    if (pathArray_.size() == static_cast<unsigned long>(0) || static_cast<unsigned long>(index) >= pathArray_.size()) {
        return;
    }
    CJNavPathInfo currentPathInfo = pathArray_.back();
    pathArray_.erase(pathArray_.begin() + index + 1, pathArray_.end());
    isReplace_ = 0;
    if (!result.empty() && currentPathInfo.onPop) {
        auto popInfo = CJPopInfo();
        popInfo.info = currentPathInfo;
        popInfo.result = result;
        currentPathInfo.onPop(popInfo);
    }
    animated_ = animated;
    OnPopCallback(result);
    OnStateChanged();
}

int32_t CJNavPathStack::MoveToTop(std::string name, bool animated)
{
    if (pathArray_.size() == 0) {
        return -1;
    }
    auto it = std::find_if(pathArray_.begin(), pathArray_.end(),
        [&](const CJNavPathInfo& cjNavPathInfo) { return name == cjNavPathInfo.name; });
    int32_t index = -1;
    if (it != pathArray_.end()) {
        index = std::distance(pathArray_.begin(), it);
    }
    if (index == -1) {
        return -1;
    }
    auto info = pathArray_[index];
    pathArray_.erase(pathArray_.begin() + index);
    pathArray_.push_back(info);
    isReplace_ = 0;
    animated_ = animated;
    OnStateChanged();
    return index;
}

void CJNavPathStack::MoveIndexToTop(int32_t index, bool animated)
{
    if (pathArray_.size() == static_cast<unsigned long>(0) || static_cast<unsigned long>(index) >= pathArray_.size()) {
        return;
    }
    auto info = pathArray_[index];
    pathArray_.erase(pathArray_.begin() + index);
    pathArray_.push_back(info);
    isReplace_ = 0;
    animated_ = animated;
    OnStateChanged();
}

void CJNavPathStack::Clear(bool animated)
{
    if (pathArray_.size() == 0) {
        return;
    }
    pathArray_.clear();
    isReplace_ = 0;
    animated_ = animated;
    OnStateChanged();
}

std::vector<std::string> CJNavPathStack::GetAllPathName()
{
    std::vector<std::string> names;
    for (const auto& path : pathArray_) {
        names.push_back(path.name);
    }
    return names;
}

std::string CJNavPathStack::GetParamByIndex(int32_t index)
{
    std::string param;
    if (static_cast<unsigned long>(index) >= pathArray_.size()) {
        return param;
    }
    param = pathArray_[index].param;
    return param;
}

std::vector<std::string> CJNavPathStack::GetParamByName(std::string name)
{
    std::vector<std::string> params;
    for (const auto& path : pathArray_) {
        if (path.name == name) {
            params.push_back(path.param);
        }
    }
    return params;
}

std::vector<int32_t> CJNavPathStack::GetAllPathIndex()
{
    std::vector<int32_t> indexs;
    for (const auto& path : pathArray_) {
        indexs.push_back(path.index);
    }
    return indexs;
}

std::vector<int32_t> CJNavPathStack::GetIndexByName(std::string name)
{
    std::vector<int32_t> indexs;
    for (int i = 0; static_cast<unsigned long>(i) < pathArray_.size(); ++i) {
        if (pathArray_[i].name == name) {
            indexs.push_back(i);
        }
    }
    return indexs;
}

int32_t CJNavPathStack::GetIndexFromIndex(int32_t index)
{
    for (int i = 0; static_cast<unsigned long>(i) < pathArray_.size(); i++) {
        if (pathArray_[i].index == index) {
            return i;
        }
    }
    return -1;
}

void CJNavPathStack::InitNavPathIndex(const std::vector<std::string>& pathNames)
{
    popArray_.clear();
    for (int i = 0;
        static_cast<unsigned long>(i) < pathArray_.size() && static_cast<unsigned long>(i) < pathNames.size();
        i++) {
        if (pathNames[i] == pathArray_[i].name && isReplace_ != 1) {
            pathArray_[i].index = i;
        }
    }
}

int32_t CJNavPathStack::GetIsReplace()
{
    return isReplace_;
}

void CJNavPathStack::SetIsReplace(int32_t isReplace)
{
    isReplace_ = isReplace;
}

bool CJNavPathStack::GetAnimated()
{
    return animated_;
}

void CJNavPathStack::SetAnimated(bool animated)
{
    animated_ = animated;
}

void CJNavPathStack::SetNavDestinationId(int32_t index, const std::string& navDestinationId)
{
    if (static_cast<unsigned long>(index) >= pathArray_.size()) {
        return;
    }
    pathArray_[index].navDestinationId = navDestinationId.c_str();
}

std::optional<CJNavPathInfo> CJNavPathStack::GetPathInfo(int32_t index)
{
    if (static_cast<unsigned long>(index) >= pathArray_.size()) {
        return std::nullopt;
    }
    return pathArray_[index];
}

void CJNavPathStack::SetNeedUpdateByIndex(int32_t index, bool needUpdate)
{
    if (static_cast<unsigned long>(index) >= pathArray_.size()) {
        return;
    }
    pathArray_[index].needUpdate = needUpdate;
}

void CJNavPathStack::SetNeedBuildNewInstanceByIndex(int32_t index, bool needBuildNewInstance)
{
    if (static_cast<unsigned long>(index) >= pathArray_.size()) {
        return;
    }
    pathArray_[index].needBuildNewInstance = needBuildNewInstance;
}

void CJNavPathStack::SetIsEntryByIndex(int32_t index, bool isEntry)
{
    if (static_cast<unsigned long>(index) >= pathArray_.size()) {
        return;
    }
    pathArray_[index].isEntry = isEntry;
}

void CJNavPathStack::SetFromRecoveryByIndex(int32_t index, bool fromRecovery)
{
    if (static_cast<unsigned long>(index) >= pathArray_.size()) {
        return;
    }
    pathArray_[index].fromRecovery = fromRecovery;
}

void CJNavPathStack::SetRecoveryFromReplaceDestinationByIndex(int32_t index, bool recoveryFromReplaceDestination)
{
    if (static_cast<unsigned long>(index) >= pathArray_.size()) {
        return;
    }
    pathArray_[index].recoveryFromReplaceDestination = recoveryFromReplaceDestination;
}

int32_t CJNavPathStack::GetSize()
{
    return pathArray_.size();
}

void CJNavPathStack::SetDisableAllAnimation(bool disableAnimation)
{
    disableAllAnimation_ = disableAnimation;
}

bool CJNavPathStack::GetDisableAllAnimation()
{
    return disableAllAnimation_;
}

void CJNavPathStack::SetParent(sptr<CJNavPathStack> parent)
{
    parentStack_ = parent;
}

sptr<CJNavPathStack> CJNavPathStack::GetParent()
{
    return parentStack_;
}

void CJNavPathStack::SetPathArray(std::vector<CJNavPathInfo> pathArray)
{
    pathArray_ = pathArray;
}

} // namespace OHOS::Ace::Framework

namespace {

CJNavPathInfoFFi ConvertCJ2FFi(CJNavPathInfo info)
{
    CJNavPathInfoFFi ret = CJNavPathInfoFFi();
    if (info.valid == -1) {
        ret.valid = info.valid;
    } else {
        ret.id = info.id;
        ret.name = strdup(info.name.c_str());
        ret.param = strdup(info.param.c_str());
        ret.onPopValid = info.onPopValid;
        ret.index = info.index;
        ret.navDestinationId = strdup(info.navDestinationId.c_str());
        ret.isEntry = info.isEntry;
        ret.valid = info.valid;
    }
    return ret;
}

CJNavPathInfo ConvertFFi2CJ(CJNavPathInfoFFi info)
{
    CJNavPathInfo ret = CJNavPathInfo();
    ret.id = info.id;
    ret.name = info.name;
    ret.param = info.param;
    if (info.onPopValid) {
        auto onPop = [lambda = CJLambda::Create(info.onPop)](const CJPopInfo& popInfo) {
            CJPopInfoFFi cjPopInfoFFi = CJPopInfoFFi();
            cjPopInfoFFi.info = ConvertCJ2FFi(popInfo.info);
            cjPopInfoFFi.result = strdup(popInfo.result.c_str());
            lambda(cjPopInfoFFi);
        };
        ret.onPop = std::move(onPop);
    }
    ret.onPopValid = info.onPopValid;
    ret.index = info.index;
    ret.navDestinationId = info.navDestinationId;
    ret.isEntry = info.isEntry;
    ret.valid = info.valid;
    return ret;
}

}

extern "C" {
int64_t FfiOHOSAceFrameworkNavPathStackCreate()
{
    auto ret_ = OHOS::FFI::FFIData::Create<OHOS::Ace::Framework::CJNavPathStack>();
    if (ret_ == nullptr) {
        return FFI_ERROR_CODE;
    }
    return ret_->GetID();
}
void FfiOHOSAceFrameworkNavPathStackPushPath(int64_t id, CJNavPathInfoFFi info, CJNavigationOptionsFFi options)
{
    LaunchMode launchMode = LaunchMode::STANDARD;
    if (options.launchMode >= static_cast<int>(LaunchMode::STANDARD) &&
        options.launchMode <= static_cast<int>(LaunchMode::NEW_INSTANCE)) {
        launchMode = static_cast<LaunchMode>(options.launchMode);
    }
    auto self_ = OHOS::FFI::FFIData::GetData<OHOS::Ace::Framework::CJNavPathStack>(id);
    if (self_ == nullptr) {
        LOGE("Failed to invoke ffi function: CJNavPathStack pushPath!");
        return;
    }
    self_->PushPath(ConvertFFi2CJ(info), options.animated, launchMode);
}

CJNavPathInfoFFi FfiOHOSAceFrameworkNavPathStackPop(int64_t id, char* result, bool animated)
{
    auto self_ = OHOS::FFI::FFIData::GetData<OHOS::Ace::Framework::CJNavPathStack>(id);
    if (self_ == nullptr) {
        LOGE("Failed to invoke ffi function: CJNavPathStack pop!");
        CJNavPathInfoFFi ret = CJNavPathInfoFFi();
        ret.valid = -1;
        return ret;
    }
    auto ret = self_->Pop(result, animated);
    return ConvertCJ2FFi(ret);
}

void FfiOHOSAceFrameworkNavPathStackReplacePath(int64_t id, CJNavPathInfoFFi info, CJNavigationOptionsFFi options)
{
    LaunchMode launchMode = LaunchMode::STANDARD;
    if (options.launchMode >= static_cast<int>(LaunchMode::STANDARD) &&
        options.launchMode <= static_cast<int>(LaunchMode::NEW_INSTANCE)) {
        launchMode = static_cast<LaunchMode>(options.launchMode);
    }
    auto self_ = OHOS::FFI::FFIData::GetData<OHOS::Ace::Framework::CJNavPathStack>(id);
    if (self_ == nullptr) {
        LOGE("Failed to invoke ffi function: CJNavPathStack replacePath!");
        return;
    }
    self_->ReplacePath(ConvertFFi2CJ(info), options.animated, launchMode);
}

int32_t FfiOHOSAceFrameworkNavPathStackRemoveByIndexes(int64_t id, VectorInt32Ptr indexes)
{
    auto self_ = OHOS::FFI::FFIData::GetData<OHOS::Ace::Framework::CJNavPathStack>(id);
    if (self_ == nullptr) {
        LOGE("Failed to invoke ffi function: CJNavPathStack removeByIndexes!");
        return 0;
    }
    const auto& indexVector = *reinterpret_cast<std::vector<int32_t>*>(indexes);
    if (indexVector.size() == 0) {
        return 0;
    }
    return self_->RemoveByIndexes(indexVector);
}

int32_t FfiOHOSAceFrameworkNavPathStackRemoveByName(int64_t id, char* name)
{
    auto self_ = OHOS::FFI::FFIData::GetData<OHOS::Ace::Framework::CJNavPathStack>(id);
    if (self_ == nullptr) {
        LOGE("Failed to invoke ffi function: CJNavPathStack removeByName!");
        return 0;
    }
    return self_->RemoveByName(name);
}

bool FfiOHOSAceFrameworkNavPathStackRemoveByNavDestinationId(int64_t id, char* navDestinationId)
{
    auto self_ = OHOS::FFI::FFIData::GetData<OHOS::Ace::Framework::CJNavPathStack>(id);
    if (self_ == nullptr) {
        LOGE("Failed to invoke ffi function: CJNavPathStack removeByNavDestinationId!");
        return false;
    }
    return self_->RemoveByNavDestinationId(navDestinationId);
}

int32_t FfiOHOSAceFrameworkNavPathStackPopToName(int64_t id, char* name, char* result, bool animated)
{
    auto self_ = OHOS::FFI::FFIData::GetData<OHOS::Ace::Framework::CJNavPathStack>(id);
    if (self_ == nullptr) {
        LOGE("Failed to invoke ffi function: CJNavPathStack popToName!");
        return -1;
    }
    return self_->PopToName(name, result, animated);
}

void FfiOHOSAceFrameworkNavPathStackPopToIndex(int64_t id, int32_t index, char* result, bool animated)
{
    auto self_ = OHOS::FFI::FFIData::GetData<OHOS::Ace::Framework::CJNavPathStack>(id);
    if (self_ == nullptr) {
        LOGE("Failed to invoke ffi function: CJNavPathStack popToIndex!");
        return;
    }
    return self_->PopToIndex(index, result, animated);
}

int32_t FfiOHOSAceFrameworkNavPathStackMoveToTop(int64_t id, char* name, bool animated)
{
    auto self_ = OHOS::FFI::FFIData::GetData<OHOS::Ace::Framework::CJNavPathStack>(id);
    if (self_ == nullptr) {
        LOGE("Failed to invoke ffi function: CJNavPathStack moveToTop!");
        return -1;
    }
    return self_->MoveToTop(name, animated);
}

void FfiOHOSAceFrameworkNavPathStackMoveIndexToTop(int64_t id, int32_t index, bool animated)
{
    auto self_ = OHOS::FFI::FFIData::GetData<OHOS::Ace::Framework::CJNavPathStack>(id);
    if (self_ == nullptr) {
        LOGE("Failed to invoke ffi function: CJNavPathStack moveIndexToTop!");
        return;
    }
    return self_->MoveIndexToTop(index, animated);
}

void FfiOHOSAceFrameworkNavPathStackClear(int64_t id, bool animated)
{
    auto self_ = OHOS::FFI::FFIData::GetData<OHOS::Ace::Framework::CJNavPathStack>(id);
    if (self_ == nullptr) {
        LOGE("Failed to invoke ffi function: CJNavPathStack clear!");
        return;
    }
    return self_->Clear(animated);
}

VectorStringPtr FfiOHOSAceFrameworkNavPathStackGetAllPathName(int64_t id)
{
    auto self_ = OHOS::FFI::FFIData::GetData<OHOS::Ace::Framework::CJNavPathStack>(id);
    if (self_ == nullptr) {
        LOGE("Failed to invoke ffi function: CJNavPathStack getAllPathName!");
        return new std::vector<std::string>();
    }

    return new std::vector<std::string>(self_->GetAllPathName());
}

char* FfiOHOSAceFrameworkNavPathStackGetParamByIndex(int64_t id, int32_t index)
{
    auto self_ = OHOS::FFI::FFIData::GetData<OHOS::Ace::Framework::CJNavPathStack>(id);
    std::string param;
    if (self_ == nullptr) {
        LOGE("Failed to invoke ffi function: CJNavPathStack getParamByIndex!");
        return strdup(param.c_str());
    }
    param = self_->GetParamByIndex(index);
    return strdup(param.c_str());
}

VectorStringPtr FfiOHOSAceFrameworkNavPathStackGetParamByName(int64_t id, char* name)
{
    auto self_ = OHOS::FFI::FFIData::GetData<OHOS::Ace::Framework::CJNavPathStack>(id);
    if (self_ == nullptr) {
        LOGE("Failed to invoke ffi function: CJNavPathStack getParamByName!");
        return new std::vector<std::string>();
    }

    return new std::vector<std::string>(self_->GetParamByName(name));
}

VectorInt32Ptr FfiOHOSAceFrameworkNavPathStackGetIndexByName(int64_t id, char* name)
{
    auto self_ = OHOS::FFI::FFIData::GetData<OHOS::Ace::Framework::CJNavPathStack>(id);
    if (self_ == nullptr) {
        LOGE("Failed to invoke ffi function: CJNavPathStack getIndexByName!");
        return new std::vector<int32_t>();
    }
    return new std::vector<int32_t>(self_->GetIndexByName(name));
}

int32_t FfiOHOSAceFrameworkNavPathStackSize(int64_t id)
{
    auto self_ = OHOS::FFI::FFIData::GetData<OHOS::Ace::Framework::CJNavPathStack>(id);
    if (self_ == nullptr) {
        LOGE("Failed to invoke ffi function: CJNavPathStack size!");
        return 0;
    }
    return self_->GetSize();
}

void FfiOHOSAceFrameworkNavPathStackDisableAnimation(int64_t id, bool animated)
{
    auto self_ = OHOS::FFI::FFIData::GetData<OHOS::Ace::Framework::CJNavPathStack>(id);
    if (self_ == nullptr) {
        LOGE("Failed to invoke ffi function: CJNavPathStack disableAnimation!");
        return;
    }
    self_->SetDisableAllAnimation(animated);
}

int64_t FfiOHOSAceFrameworkNavPathStackGetParent(int64_t id)
{
    auto self_ = OHOS::FFI::FFIData::GetData<OHOS::Ace::Framework::CJNavPathStack>(id);
    if (self_ == nullptr) {
        LOGE("Failed to invoke ffi function: CJNavPathStack getParent!");
        return -1;
    }
    return self_->GetParent()->GetID();
}
}