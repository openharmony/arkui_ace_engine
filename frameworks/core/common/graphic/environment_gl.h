/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_ENVIRONMENT_GL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_ENVIRONMENT_GL_H

#include <memory>
#include <thread>

#include "third_party/skia/include/core/SkRefCnt.h"

#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"

typedef void* EGLSurface;
typedef void* EGLContext;
typedef void* EGLDisplay;

class GrContext;

namespace OHOS::Ace {

class EnvironmentGL final : public Referenced {
public:
    static RefPtr<EnvironmentGL> MakeSharedGLContext();
    static RefPtr<EnvironmentGL> GetCurrent();

    EnvironmentGL(EGLDisplay display, EGLContext context, EGLSurface surface)
        : display_(display), context_(context), surface_(surface)
    {}
    ~EnvironmentGL();

    void MakeCurrent();
    void MakeGrContext();
    sk_sp<GrContext> GetGrContext() const;

private:
    EGLDisplay display_ = nullptr;
    EGLContext context_ = nullptr;
    EGLSurface surface_ = nullptr;
    static thread_local WeakPtr<EnvironmentGL> glEnvironment_;
    sk_sp<GrContext> grContext_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_ENVIRONMENT_GL_H