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

#ifndef _ASSET_LOADER_H
#define _ASSET_LOADER_H

#include <android/asset_manager.h>
#include <string>
#include <map>
#include "directory.h"

typedef std::map<std::string, std::string> AssetsMap;

class AssetsLoader {
public:
    AssetsLoader(AAssetManager* assetManager, const char* internalDataPath);

    bool syncFiles();

private:
    AssetsMap   readAssetsMap();
    AssetsMap   readFileMap();

    static void selectUpdated(AssetsMap &assets, const AssetsMap& files);
    bool copyAssets(const AssetsMap& itemsToCopy);
    bool copySingleAsset(const char* source, const char* dest);

    AAssetManager* am;
    Directory dataDir;

    std::string assetsFingerPrint;
};

#endif //_ASSET_LOADER_H
