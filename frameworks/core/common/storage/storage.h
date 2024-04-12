/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_STORAGE_STORAGE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_STORAGE_STORAGE_H

#include "base/memory/ace_type.h"
#include "base/thread/task_executor.h"

namespace OHOS::Ace {

class Storage : public AceType {
    DECLARE_ACE_TYPE(Storage, AceType);

public:
    enum class DataType : uint32_t {
        NONE = 0,
        STRING,
        DOUBLE,
        BOOLEAN,
    };

    using DataOnChange = std::function<void(const std::string& key)>;

    ~Storage() override = default;

    virtual void SetString(const std::string& key, const std::string& value) = 0;
    virtual std::string GetString(const std::string& key) = 0;
    virtual void SetDouble(const std::string& key, const double value) = 0;
    virtual bool GetDouble(const std::string& key, double& value) = 0;
    virtual void SetBoolean(const std::string& key, const bool value) = 0;
    virtual bool GetBoolean(const std::string& key, bool& value) = 0;

    virtual DataType GetDataType(const std::string& key)
    {
        return DataType::NONE;
    }

    virtual void Clear() = 0;
    virtual void Delete(const std::string& key) = 0;

    void SetDataOnChangeCallback(DataOnChange&& dataOnChange)
    {
        dataOnChange_ = std::move(dataOnChange);
    }

    void OnDataChange(const std::string& key)
    {
        if (dataOnChange_) {
            dataOnChange_(key);
        }
    }

protected:
    Storage() = default;
    RefPtr<TaskExecutor> taskExecutor_;
    DataOnChange dataOnChange_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_STORAGE_STORAGE_H
