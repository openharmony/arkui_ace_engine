/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_TSA_ADVANCED_FEATURE_H
#define FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_TSA_ADVANCED_FEATURE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    FEATURE_NONE               = 0,        //      0x00000000
    OPERATING_HAND_LEFT        = (1 << 0), //   0: 0x00000001
    OPERATING_HAND_RIGHT       = (1 << 1), //   1: 0x00000002
} TSA_ADVANCED_FEATURE_ENUM;

#ifdef __cplusplus
}
#endif

#endif // FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_TSA_ADVANCED_FEATURE_H