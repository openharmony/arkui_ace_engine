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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MODEL_MODEL_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MODEL_MODEL_PROPERTY_H

namespace OHOS::Ace::NG {

#define DEFINE_NEEDS_SETUP_FLAG_PROPERTY(name, defaultVal, changeFlag)  \
public:                                                                 \
    bool Needs##name##Setup() const                                     \
    {                                                                   \
        return needs##name##Setup_;                                     \
    }                                                                   \
    void UpdateNeeds##name##Setup(const bool value)                     \
    {                                                                   \
        needs##name##Setup_ = value;                                    \
        if (value) {                                                    \
            UpdatePropertyChangeFlag(changeFlag);                       \
        }                                                               \
    }                                                                   \
    bool CloneNeeds##name##Setup() const                                \
    {                                                                   \
        return needs##name##Setup_;                                     \
    }                                                                   \
private:                                                                \
    bool needs##name##Setup_ = (defaultVal)

#define DEFINE_NEEDS_SETUP_FLAG_TRIGGER_PROPERTY(name, type, trigger, changeFlag)             \
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP_AND_USING_CALLBACK(name, type, changeFlag)         \
public:                                                                                       \
    void On##name##Update(const type& value)                                                  \
    {                                                                                         \
        do {                                                                                  \
            UpdateNeeds##trigger##Setup(true);                                                \
        } while (false);                                                                      \
    }
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MODEL_MODEL_PROPERTY_H