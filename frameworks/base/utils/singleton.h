/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_SINGLETON_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_SINGLETON_H

#include "base/utils/noncopyable.h"
#include "base/utils/macros.h"

namespace OHOS::Ace {

#define DECLARE_SINGLETON(MyClass)               \
private:                                         \
    friend Singleton<MyClass>;                   \
    MyClass& operator=(const MyClass&) = delete; \
    MyClass(const MyClass&) = delete;            \
    MyClass();                                   \
    ~MyClass();

#define SINGLETON_INSTANCE_IMPL(MyClass)         \
template<>                                       \
ACE_FORCE_EXPORT                                 \
MyClass& Singleton<MyClass>::GetInstance() {     \
   static MyClass instance;                      \
   return instance;                              \
}

template<typename T>
class Singleton : public NonCopyable {
public:
    static ACE_FORCE_EXPORT T& GetInstance();
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_SINGLETON_H
