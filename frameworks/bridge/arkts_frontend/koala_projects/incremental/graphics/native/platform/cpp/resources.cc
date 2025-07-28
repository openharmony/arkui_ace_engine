/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "skoala-interop.h"

#include <iostream>

namespace {
SkString homeDir;
SkString resourceDir;
}

void impl_skoala_provideResourceDirs(const KStringPtr& homeDirPtr, const KStringPtr& resourceDirPtr) {
    homeDir = SkString(homeDirPtr.c_str());
    resourceDir = SkString(resourceDirPtr.c_str());
}
KOALA_INTEROP_V2(skoala_provideResourceDirs, KStringPtr, KStringPtr)

KNativePointer impl_skoala_getHomeDir() {
    return new SkString(homeDir);
}
KOALA_INTEROP_0(skoala_getHomeDir, KNativePointer)

KNativePointer impl_skoala_getResourceDir() {
    return new SkString(resourceDir);
}
KOALA_INTEROP_0(skoala_getResourceDir, KNativePointer)