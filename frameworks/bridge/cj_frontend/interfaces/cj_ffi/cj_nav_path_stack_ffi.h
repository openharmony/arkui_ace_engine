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

#include "base/utils/macros.h"
#include "ffi_remote_data.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"

struct CJNavPathInfo {
    std::string name;
    std::string param;
    int32_t index;
    std::string navDestinationId;
    bool isEntry;
    int32_t valid;
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

    bool IsEmpty()
    {
        return pathArray_.empty();
    }

    void PushPath(CJNavPathInfo info)
    {
        std::optional<CJNavPathInfo> popInfo = findInPopArray(info.name);
        if (popInfo.has_value()) {
            auto data = popInfo.value();
            info.index = data.index;
            info.navDestinationId = data.navDestinationId;
        }
        pathArray_.push_back(info);
        isReplace_ = 0;
        animated_ = true;
        OnStateChanged();
    }

    CJNavPathInfo Pop()
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
        OnStateChanged();
        return pathInfo;
    }

    std::vector<std::string> GetAllPathName()
    {
        std::vector<std::string> names;
        for (const auto& path : pathArray_) {
            names.push_back(path.name);
        }
        return names;
    }

    std::vector<int32_t> GetAllPathIndex()
    {
        std::vector<int32_t> indexs;
        for (const auto& path : pathArray_) {
            indexs.push_back(path.index);
        }
        return indexs;
    }

    void InitNavPathIndex(const std::vector<std::string>& pathNames)
    {
        popArray_.clear();
        for (int i = 0; i < pathArray_.size() && i < pathNames.size(); i++) {
            if (pathNames[i] == pathArray_[i].name) {
                pathArray_[i].index = i;
            }
        }
    }

    int32_t GetIsReplace()
    {
        return isReplace_;
    }

    void SetIsReplace(int32_t isReplace)
    {
        isReplace_ = isReplace;
    }

    bool GetAnimated()
    {
        return animated_;
    }

    void SetAnimated(bool animated)
    {
        animated_ = animated;
    }

    void SetNavDestinationId(int32_t index, const std::string& navDestinationId)
    {
        pathArray_[index].navDestinationId = navDestinationId.c_str();
    }

    CJNavPathInfo GetPathInfo(int32_t index)
    {
        return pathArray_[index];
    }

    int32_t GetSize()
    {
        return pathArray_.size();
    }

    void SetParent(sptr<CJNavPathStack> parent)
    {
        parentStack_ = parent;
    }

    sptr<CJNavPathStack> GetParent()
    {
        return parentStack_;
    }

    void SetPathArray(std::vector<CJNavPathInfo> pathArray)
    {
        pathArray_ = pathArray;
    }
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

    std::function<void()> onStateChangedCallback_;

    std::vector<CJNavPathInfo> pathArray_;
    int32_t isReplace_;
    bool animated_;
    std::vector<CJNavPathInfo> popArray_;
    sptr<CJNavPathStack> parentStack_;
};

class CJNavPathInfoNG : public NG::NavPathInfo {
    DECLARE_ACE_TYPE(CJNavPathInfoNG, NG::NavPathInfo)
public:
    CJNavPathInfoNG() = default;
    CJNavPathInfoNG(const std::string& name, const std::string& param) : NG::NavPathInfo(name), param_(param) {}
    ~CJNavPathInfoNG() = default;

    void SetParam(const std::string& param)
    {
        param_ = param;
    }

    std::string GetParam() const
    {
        return param_;
    }

    napi_value GetParamObj() const override;

    void UpdateNavPathInfo(const RefPtr<NG::NavPathInfo>& info) override;

private:
    std::string param_;
};

} // namespace OHOS::Ace::Framework

extern "C" {
struct CJNavPathInfoFFi {
    const char* name;
    const char* param;
    int32_t index;
    const char* navDestinationId;
    bool isEntry;
    int32_t valid;
};


CJ_EXPORT int64_t FfiOHOSAceFrameworkNavPathStackCreate();
CJ_EXPORT void FfiOHOSAceFrameworkNavPathStackPushPath(int64_t id, CJNavPathInfoFFi info);
CJ_EXPORT CJNavPathInfoFFi FfiOHOSAceFrameworkNavPathStackPop(int64_t id);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_NAV_PATH_STACK_FFI_H
