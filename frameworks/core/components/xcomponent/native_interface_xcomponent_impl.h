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

#ifndef _NATIVE_INTERFACE_XCOMPONENT_IMPL_
#define _NATIVE_INTERFACE_XCOMPONENT_IMPL_

#include <string>
#include <unistd.h>

#include "base/memory/ace_type.h"
#include "interfaces/native/native_interface_xcomponent.h"

namespace OHOS::Ace {
class NativeXComponentImpl : public virtual AceType {
    DECLARE_ACE_TYPE(NativeXComponentImpl, AceType);

public:
    NativeXComponentImpl() : window_(nullptr), width_(0), height_(0), callback_(nullptr) {}

    void SetXComponentId(const std::string& id)
    {
        xcomponetId_ = id;
    }

    const std::string& GetXComponentId() const
    {
        return xcomponetId_;
    }

    void SetSurfaceWidth(const int width)
    {
        width_ = width;
    }

    int GetSurfaceWidth() const
    {
        return width_;
    }

    void SetSurfaceHeight(const int height)
    {
        height_ = height;
    }

    int GetSurfaceHeight() const
    {
        return height_;
    }

    void SetSurface(void* window)
    {
        window_ = window;
    }

    void* GetSurface() const
    {
        return window_;
    }

    void SetCallback(NativeXComponentCallback* callback)
    {
        callback_ = callback;
    }

    const NativeXComponentCallback* GetCallback() const
    {
        return callback_;
    }

    void SetTouchInfo(const TouchInfo touchInfo)
    {
        touchInfo_ = touchInfo;
    }

    const TouchInfo GetTouchInfo() const
    {
        return touchInfo_;
    }

private:
    std::string xcomponetId_;
    void* window_;
    int width_;
    int height_;
    TouchInfo touchInfo_;
    NativeXComponentCallback* callback_;
};
}

struct NativeXComponent {
    NativeXComponent(OHOS::Ace::NativeXComponentImpl* xComponentImpl) : xcomponentImpl_(xComponentImpl) {}
    ~NativeXComponent() {}
    int32_t GetXComponentId(char* id, uint64_t* size);
    int32_t GetNativeWindow(void** window);
    int32_t GetSurfaceSize(const void* window, uint64_t* width, uint64_t* height);
    int32_t GetTouchInfo(const void* window, TouchInfo* touchInfo);
    int32_t RegisterCallback(NativeXComponentCallback* callback);

private:
    OHOS::Ace::NativeXComponentImpl* xcomponentImpl_ = nullptr;
};

#endif // _NATIVE_INTERFACE_XCOMPONENT_IMPL_