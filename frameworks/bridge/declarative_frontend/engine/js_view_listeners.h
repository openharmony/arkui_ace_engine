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

#ifndef FOUNDATION_ACE_FRAMEWORKS_DECLARATIVE_FRONTEND_ENGINE_VIEW_LISTENERS_H
#define FOUNDATION_ACE_FRAMEWORKS_DECLARATIVE_FRONTEND_ENGINE_VIEW_LISTENERS_H

#include <set>

#include "base/memory/ace_type.h"

namespace OHOS::Ace::Framework {

// forward
class JSViewAbstract;

class JSViewListeners : public AceType {
    DECLARE_ACE_TYPE(JSViewListeners, AceType);

protected:
    std::set<JSViewAbstract*> listeners_;

public:
    JSViewListeners() {}
    ~JSViewListeners()
    {
        listeners_.clear();
    }

    /** Add a new listening view
     * avoids duplicates
     * returns false if View already exists
     */
    bool add(JSViewAbstract* view);

    /** remove View
     * returns true of found
     */
    bool remove(JSViewAbstract* view);

    /**
     * nodify all listeners to update
     */
    void notifyAll();

    std::size_t count()
    {
        return listeners_.size();
    }
};

} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_DECLARATIVE_FRONTEND_ENGINE_VIEW_LISTENERS_H
