/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2023-2024. All rights reserved.
 */

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_CACHED_IMAGE_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_CACHED_IMAGE_H

#include "frameworks/bridge/declarative_frontend/jsview/js_image.h"

namespace OHOS::Ace::Framework {

class JSCachedImage : public JSImage {
public:
    static void JSBind(BindingTarget globalObj);
    static void JSBindMediaCachedImage(BindingTarget globalObj);

private:
    static void Create(const JSCallbackInfo& info);
    static void SetSourceSize(const JSCallbackInfo& info);
    static bool IsASTCResource(const JSRef<JSVal>& jsValue, std::vector<std::string>& uriList,
        int& column);
    static void SetAlt(const JSCallbackInfo& info);
};

}  // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_CACHED_IMAGE_H