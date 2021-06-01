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

#include "frameworks/bridge/declarative_frontend/engine/js_view_listeners.h"

#include "base/log/ace_trace.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "frameworks/bridge/js_frontend/engine/quickjs/qjs_utils.h"

namespace OHOS::Ace::Framework {

void JSViewListeners::notifyAll()
{
    for (std::set<JSViewAbstract*>::const_iterator iter = listeners_.begin(); iter != listeners_.end(); iter++) {
        (*iter)->MarkNeedUpdate();
    }
}

bool JSViewListeners::add(JSViewAbstract* view)
{
    // avoid duplicates
    if (listeners_.find(view) == listeners_.end()) {
        listeners_.emplace(view);
        return true;
    } else {
        return false;
    }
}

bool JSViewListeners::remove(JSViewAbstract* view)
{
    // this simple approach only works because we avoid duplicates when adding new View.
    std::set<JSViewAbstract*>::iterator iter = listeners_.find(view);
    if (iter != listeners_.end()) {
        listeners_.erase(iter);
        return true;
    } else {
        return false;
    }
}

} // namespace OHOS::Ace::Framework
