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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_CUSTOMVIEWBASE_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_CUSTOMVIEWBASE_H

#include <list>

#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::Framework {

#ifdef USE_V8_ENGINE
using V8Handle = v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>;
#endif

// JSView has two implmentation for qjs and v8
// this base is used to keep the common implementation
class JSCustomViewBase : public JSViewAbstract {
    DECLARE_ACE_TYPE(JSCustomViewBase, JSViewAbstract);

public:
    JSCustomViewBase();
    virtual ~JSCustomViewBase();

    virtual void Destroy(JSViewAbstract* parentCustomView) override;

    virtual bool IsCustomView() override
    {
        return true;
    }

    /**
     * During render function execution, the child customview with same id will
     * be recycled if they exist already in our child map. The ones which are not
     * recycled needs to be cleaned. So After render function execution, clean the
     * abandoned child customview.
     */
    void CleanUpAbandonedChild();

    /**
     * Find if the customview child with same id exist
     */
    bool FindChildById(const std::string& viewId);

#ifdef USE_V8_ENGINE
    /**
     * Retries the customview child for recycling
     * always use FindChildById to be certain before calling this method
     */
    std::pair<JSViewAbstract*, v8::Local<v8::Value>> GetChildById(const std::string& viewId);
    /**
     * New CustomView child will be added to the map.
     * and it can be reterieved for recycling in next render function
     * In next render call if this child is not recycled, it will be destroyed.
     */
    void AddChildById(const std::string& viewId, JSViewAbstract* view, v8::Local<v8::Object> obj);
#elif USE_QUICKJS_ENGINE
    /**
     * Retries the customview child for recycling
     * always use FindChildById to be certain before calling this method
     */
    std::pair<JSViewAbstract*, JSValue> GetChildById(const std::string& viewId);
    /**
     * New CustomView child will be added to the map.
     * and it can be reterieved for recycling in next render function
     * In next render call if this child is not recycled, it will be destroyed.
     */
    void AddChildById(const std::string& viewId, JSViewAbstract* view, JSValue obj);
#endif

    /**
     * This method should be called before executing view mapper function of a foreach
     * child.
     */
    void StartHandlingForEach(const std::string& key)
    {
        forEachKey_.append(key);
    }

    /**
     * This method should be called after executing view mapper function of a foreach
     * child.
     */
    void EndHandlingForEachKeys()
    {
        forEachKey_.clear();
    }
#ifdef USE_QUICKJS_ENGINE
protected:
    JSContext* ctx_;
#endif

private:
    /**
     * Takes care of the viewId wrt to foreach
     */
    std::string ProcessViewId(const std::string& viewid);
    /**
     * creates a set of valid viewids on a renderfuntion excution
     * its cleared after cleaning up the abandoned child.
     */
    void ChildAccessedById(const std::string& viewId);

    // this holds the foreach identitymapperkeys + generatedviewid
    // it will be reset on EndHandlingForEachKeys
    std::string forEachKey_;

    // hold handle to the native and javascript object to keep them alive
    // until they are abandoned
    std::unordered_map<std::string, JSViewAbstract*> customViewChildren_;
#ifdef USE_V8_ENGINE
    std::unordered_map<std::string, V8Handle> jsCustomViewChildren_;
#elif USE_QUICKJS_ENGINE
    std::unordered_map<std::string, JSValue> jsCustomViewChildren_;
#endif
    // a set of valid viewids on a renderfuntion excution
    // its cleared after cleaning up the abandoned child.
    std::unordered_set<std::string> lastAccessedViewIds_;
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_CUSTOMVIEWBASE_H
