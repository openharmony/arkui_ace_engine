/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "parameter.h"
#include "parameters.h"

// ================================= start mock parameters.h ==============================
namespace OHOS {
namespace system {
std::string GetParameter(const std::string& key, const std::string& def)
{
    return def;
}

bool GetBoolParameter(const std::string& key, bool def)
{
    return def;
}

bool SetParameter(const std::string& key, const std::string& value)
{
    return true;
}

std::string GetDeviceType(void)
{
    return "default";
}
}
}
// ================================= end mock parameters.h =================================

//================================= start mock parameter.h =================================
int GetParameter(const char *key, const char *def, char *value, uint32_t len)
{
    return 0;
}

int WatchParameter(const char *keyPrefix, ParameterChgPtr callback, void *context)
{
    return 0;
}

int RemoveParameterWatcher(const char *keyPrefix, ParameterChgPtr callback, void *context)
{
    return 0;
}

const char *GetDeviceType(void)
{
    return "default";
}

const char *GetProductModel(void)
{
    return "";
}

const char *GetBrand(void)
{
    return "";
}

const char *GetManufacture(void)
{
    return "";
}

const char *GetMarketName(void)
{
    return "";
}

int GetSdkApiVersion(void)
{
    return 0;
}

const char *GetOsReleaseType(void)
{
    return "test";
}

//================================= end mock parameter.h ===================================

bool HasSystemCapability(const char *cap)
{
    return false;
}

bool CheckApiVersionGreaterOrEqual(int majorVersion, int minorVersion, int patchVersion)
{
    return false;
}
