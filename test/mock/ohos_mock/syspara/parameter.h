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

#ifndef STARTUP_SYSPARAM_PARAMETER_API_H
#define STARTUP_SYSPARAM_PARAMETER_API_H
#include <cstdint>
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */
const char *GetDeviceType(void);
const char *GetProductModel(void);
const char *GetBrand(void);
const char *GetManufacture(void);
const char *GetMarketName(void);

int GetSdkApiVersion(void);
const char *GetOsReleaseType(void);

int GetParameter(const char *key, const char *def, char *value, uint32_t len);
typedef void (*ParameterChgPtr)(const char *key, const char *value, void *context);
int WatchParameter(const char *keyPrefix, ParameterChgPtr callback, void *context);

int RemoveParameterWatcher(const char *keyPrefix, ParameterChgPtr callback, void *context);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif // STARTUP_SYSPARAM_PARAMETER_API_H
