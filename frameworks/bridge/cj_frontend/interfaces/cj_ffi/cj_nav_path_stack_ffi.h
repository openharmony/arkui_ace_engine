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

#ifndef OHOS_ACE_FRAMEWORK_CJ_NAV_PATH_STACK_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_NAV_PATH_STACK_FFI_H

#include <functional>
#include <string>

#include "ffi_remote_data.h"

#include "base/utils/macros.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"

enum class LaunchMode {
    STANDARD = 0,
    MOVE_TO_TOP_SINGLETON,
    POP_TO_SINGLETON,
    NEW_INSTANCE,
};

struct CJPopInfo;

struct CJNavPathInfo {
    int64_t id;
    std::string name;
    std::string param;
    std::function<void(const CJPopInfo& popInfo)> onPop;
    bool onPopValid;
    int32_t index = -1;
    bool needUpdate = false;
    bool needBuildNewInstance = false;
    std::string navDestinationId;
    CJNavPathInfo* replacedDestinationInfo;
    bool recoveryFromReplaceDestination = false;
    bool isEntry;
    bool fromRecovery = false;
    int32_t mode = -1;
    int32_t valid;
};

struct CJPopInfo {
    CJNavPathInfo info;
    std::string result;
};

namespace OHOS::Ace::Framework {

class CJNavPathStack : public OHOS::FFI::FFIData {
    DECL_TYPE(CJNavPathStack, OHOS::FFI::FFIData)
public:
    CJNavPathStack() : FFIData() {};
    ~CJNavPathStack() override = default;

    void OnStateChanged()
    {
        if (onStateChangedCallback_) {
            onStateChangedCallback_();
        }
    }

    void SetOnStateChangedCallback(std::function<void()> callback)
    {
        onStateChangedCallback_ = callback;
    }

    void SetOnPopCallback(const std::function<void(const std::string)>& popCallback)
    {
        onPopCallback_ = popCallback;
    }

    void OnPopCallback(const std::string& info)
    {
        if (onPopCallback_) {
            onPopCallback_(info);
        }
    }

    bool IsEmpty();
    void PushPath(CJNavPathInfo info, bool animated, LaunchMode launchMode);
    void PushName(std::string name, std::string param);
    void ReplacePath(CJNavPathInfo info, bool animated, LaunchMode launchMode);
    int32_t RemoveByIndexes(std::vector<int32_t> indexes);
    void RemoveIndex(int32_t index);
    int32_t RemoveByName(std::string name);
    bool RemoveByNavDestinationId(std::string navDestinationId);
    CJNavPathInfo Pop(std::string result, bool animated);
    int32_t PopToName(std::string name, std::string result, bool animated);
    void PopToIndex(int32_t index, std::string result, bool animated);
    int32_t MoveToTop(std::string name, bool animated);
    void MoveIndexToTop(int32_t index, bool animated);
    void Clear(bool animated);
    std::vector<std::string> GetAllPathName();
    std::string GetParamByIndex(int32_t index);
    std::vector<std::string> GetParamByName(std::string name);
    std::vector<int32_t> GetAllPathIndex();
    std::vector<int32_t> GetIndexByName(std::string name);
    int32_t GetIndexFromIndex(int32_t index);
    void InitNavPathIndex(const std::vector<std::string>& pathNames);
    int32_t GetIsReplace();
    void SetIsReplace(int32_t isReplace);
    bool GetAnimated();
    void SetAnimated(bool animated);
    void SetNavDestinationId(int32_t index, const std::string& navDestinationId);
    std::optional<CJNavPathInfo> GetPathInfo(int32_t index);
    void SetNeedUpdateByIndex(int32_t index, bool needUpdate);
    void SetNeedBuildNewInstanceByIndex(int32_t index, bool needBuildNewInstance);
    void SetIsEntryByIndex(int32_t index, bool isEntry);
    void SetFromRecoveryByIndex(int32_t index, bool fromRecovery);
    void SetRecoveryFromReplaceDestinationByIndex(int32_t index, bool recoveryFromReplaceDestination);
    int32_t GetSize();
    void SetDisableAllAnimation(bool disableAnimation);
    bool GetDisableAllAnimation();
    void SetParent(sptr<CJNavPathStack> parent);
    sptr<CJNavPathStack> GetParent();
    void SetPathArray(std::vector<CJNavPathInfo> pathArray);

private:
    std::optional<CJNavPathInfo> findInPopArray(std::string name)
    {
        for (auto it = popArray_.begin(); it != popArray_.end(); ++it) {
            if (std::string(it->name) == name) {
                CJNavPathInfo popInfo = *it;
                popArray_.erase(it);
                return popInfo;
            }
        }
        return std::nullopt;
    }

    void InnerPopToIndex(int32_t index, std::optional<std::string> result, bool animated, bool needFireOnResult)
    {
        if (pathArray_.size() == 0 || index >= pathArray_.size()) {
            return;
        }
        CJNavPathInfo currentPathInfo = pathArray_.back();
        pathArray_.erase(pathArray_.begin() + index + 1, pathArray_.end());
        isReplace_ = 0;
        if (result.has_value() && currentPathInfo.onPop) {
            auto popInfo = CJPopInfo();
            popInfo.info = currentPathInfo;
            popInfo.result = result.value();
            currentPathInfo.onPop(popInfo);
        }
        animated_ = animated;
        if (needFireOnResult) {
            OnPopCallback(result.value());
        }
        OnStateChanged();
    }

    void InnerReplacePathWithLaunchMode(int32_t index, CJNavPathInfo info, LaunchMode launchMode)
    {
        pathArray_[index].param = info.param;
        pathArray_[index].onPop = info.onPop;
        pathArray_[index].index = -1;
        if (index != pathArray_.size() - 1) {
            auto targetInfo = pathArray_[index];
            pathArray_.erase(pathArray_.begin() + index);
            if (launchMode == LaunchMode::MOVE_TO_TOP_SINGLETON) {
                pathArray_.pop_back();
            } else {
                pathArray_.erase(pathArray_.begin() + index, pathArray_.end());
            }
            pathArray_.push_back(targetInfo);
        }
    }

    std::function<void()> onStateChangedCallback_;
    std::function<void(const std::string&)> onPopCallback_;

    std::vector<CJNavPathInfo> pathArray_;
    int32_t isReplace_ = 0;
    bool disableAllAnimation_ = false;
    bool animated_ = true;
    sptr<CJNavPathStack> parentStack_;
    std::vector<CJNavPathInfo> popArray_;
};

class CJNavPathInfoNG : public NG::NavPathInfo {
    DECLARE_ACE_TYPE(CJNavPathInfoNG, NG::NavPathInfo)
public:
    CJNavPathInfoNG() = default;
    CJNavPathInfoNG(const std::string& name, const std::string& param) : NG::NavPathInfo(name), param_(param) {}
    CJNavPathInfoNG(const std::string& name, const std::string& param,
        std::function<void(const CJPopInfo& popInfo)> onPop, bool isEntry = false)
        : NG::NavPathInfo(name, isEntry), param_(param), onPop_(onPop)
    {}
    ~CJNavPathInfoNG() = default;

    void SetParam(const std::string& param)
    {
        param_ = param;
    }

    std::string GetParam() const
    {
        return param_;
    }

    void SetOnPop(const std::function<void(const CJPopInfo& popInfo)>& onPop)
    {
        onPop_ = onPop;
    }

    std::function<void(const CJPopInfo& popInfo)> GetOnPop() const
    {
        return onPop_;
    }

    napi_value GetParamObj() const override;

    void UpdateNavPathInfo(const RefPtr<NG::NavPathInfo>& info) override;

private:
    std::string param_;
    std::function<void(const CJPopInfo& popInfo)> onPop_;
};

} // namespace OHOS::Ace::Framework

using VectorInt32Ptr = void*;
using VectorStringPtr = void*;

extern "C" {
struct CJPopInfoFFi;

struct CJNavPathInfoFFi {
    int64_t id;
    const char* name;
    const char* param;
    void (*onPop)(CJPopInfoFFi popInfo);
    bool onPopValid;
    int32_t index;
    const char* navDestinationId;
    bool isEntry;
    int32_t valid;
};

struct CJPopInfoFFi {
    CJNavPathInfoFFi info;
    const char* result;
};

struct CJNavigationOptionsFFi {
    int32_t launchMode;
    bool animated;
};

CJ_EXPORT int64_t FfiOHOSAceFrameworkNavPathStackCreate();
CJ_EXPORT void FfiOHOSAceFrameworkNavPathStackPushPath(
    int64_t id, CJNavPathInfoFFi info, CJNavigationOptionsFFi options);
CJ_EXPORT void FfiOHOSAceFrameworkNavPathStackReplacePath(
    int64_t id, CJNavPathInfoFFi info, CJNavigationOptionsFFi options);
CJ_EXPORT int32_t FfiOHOSAceFrameworkNavPathStackRemoveByIndexes(int64_t id, VectorInt32Ptr indexes);
CJ_EXPORT int32_t FfiOHOSAceFrameworkNavPathStackRemoveByName(int64_t id, char* name);
CJ_EXPORT bool FfiOHOSAceFrameworkNavPathStackRemoveByNavDestinationId(int64_t id, char* navDestinationId);
CJ_EXPORT int32_t FfiOHOSAceFrameworkNavPathStackPopToName(int64_t id, char* name, char* result, bool animated);
CJ_EXPORT void FfiOHOSAceFrameworkNavPathStackPopToIndex(int64_t id, int32_t index, char* result, bool animated);
CJ_EXPORT int32_t FfiOHOSAceFrameworkNavPathStackMoveToTop(int64_t id, char* name, bool animated);
CJ_EXPORT void FfiOHOSAceFrameworkNavPathStackMoveIndexToTop(int64_t id, int32_t index, bool animated);
CJ_EXPORT void FfiOHOSAceFrameworkNavPathStackClear(int64_t id, bool animated);
CJ_EXPORT VectorStringPtr FfiOHOSAceFrameworkNavPathStackGetAllPathName(int64_t id);
CJ_EXPORT char* FfiOHOSAceFrameworkNavPathStackGetParamByIndex(int64_t id, int32_t index);
CJ_EXPORT VectorStringPtr FfiOHOSAceFrameworkNavPathStackGetParamByName(int64_t id, char* name);
CJ_EXPORT VectorInt32Ptr FfiOHOSAceFrameworkNavPathStackGetIndexByName(int64_t id, char* name);
CJ_EXPORT int32_t FfiOHOSAceFrameworkNavPathStackSize(int64_t id);
CJ_EXPORT void FfiOHOSAceFrameworkNavPathStackDisableAnimation(int64_t id, bool animated);
CJ_EXPORT int64_t FfiOHOSAceFrameworkNavPathStackGetParent(int64_t id);
CJ_EXPORT CJNavPathInfoFFi FfiOHOSAceFrameworkNavPathStackPop(int64_t id, char* result, bool animated);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_NAV_PATH_STACK_FFI_H
