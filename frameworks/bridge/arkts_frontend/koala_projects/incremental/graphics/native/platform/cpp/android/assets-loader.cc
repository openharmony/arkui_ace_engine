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

#include "assets-loader.h"
#include "logdefs.h"
#include <sstream>
#include <fstream>
#include <vector>

AssetsLoader::AssetsLoader(AAssetManager *assetManager, const char *internalDataPath)
    : am(assetManager), dataDir(internalDataPath)
{
    auto asset = AAssetManager_open(am, "assets.sha1", AASSET_MODE_BUFFER);
    if (asset) {
        auto buffer = (const char*)AAsset_getBuffer(asset);
        auto length = AAsset_getLength(asset);
        assetsFingerPrint = std::string(buffer, length);
        AAsset_close(asset);
    }
}

bool AssetsLoader::syncFiles() {
    if (assetsFingerPrint.empty()) return false;
    std::string fileMapFingerPrint;
    std::ifstream mapFPFile(dataDir.root() + "/map.sha1");
    if (mapFPFile.is_open() && std::getline(mapFPFile, fileMapFingerPrint)) {
        if (fileMapFingerPrint != assetsFingerPrint) { // partial copy, based on assets.map <-> files.map
            AssetsMap assetsMap = readAssetsMap();
            if (assetsMap.empty()) return false; // assets.map must exist

            AssetsMap fileMap = readFileMap();
            selectUpdated(assetsMap, fileMap);
            copyAssets(assetsMap);
        } else {
            LOGW_ANDROID("All assets are the same");
        }
        return true; // No need to copy
    }
    else { // map.sha1 does not exist, copy all contents
        AssetsMap assetsMap = readAssetsMap();
        if (assetsMap.empty()) return false; // assets.map must exist
        return copyAssets(assetsMap);
    }
}

AssetsMap AssetsLoader::readAssetsMap() {
    AssetsMap result;
    auto asset = AAssetManager_open(am, "assets.map", AASSET_MODE_BUFFER);
    if (asset) {
        auto data = (const char*)AAsset_getBuffer(asset);
        auto length = AAsset_getLength(asset);

        std::istringstream bufferStream(std::string(data, length));
        std::string line;
        while (std::getline(bufferStream, line)) {
            auto pos = line.find(':');
            auto path = line.substr(0, pos);
            auto fingerPrint = line.substr(pos + 1);
            result[path] = fingerPrint;
        }

        AAsset_close(asset);
    }
    return result;
}

AssetsMap AssetsLoader::readFileMap() {
    AssetsMap result;
    std::ifstream bufferStream(dataDir.root() + "/files.map");
    if (bufferStream.is_open()) {
        std::string line;
        while (std::getline(bufferStream, line)) {
            auto pos = line.find(':');
            auto path = line.substr(0, pos);
            auto fingerPrint = line.substr(pos + 1);
            result[path] = fingerPrint;
        }
    }
    return result;
}

void AssetsLoader::selectUpdated(AssetsMap &assets, const AssetsMap& files) {
    for (const auto& f : files) {
        auto af = assets.find(f.first);
        if (af != assets.end() && af->second == f.second) { // remove same instances
            assets.erase(af);
        }
    }
}

bool AssetsLoader::copyAssets(const AssetsMap& itemsToCopy) {
    for (const auto& item : itemsToCopy) {
        if (!copySingleAsset(item.first.c_str(), item.first.c_str())) return false;
    }

    return copySingleAsset("assets.sha1", "map.sha1") && copySingleAsset("assets.map", "files.map");
}

bool AssetsLoader::copySingleAsset(const char* source, const char* dest) {
    auto asset = AAssetManager_open(am, source, AASSET_MODE_BUFFER);
    if (asset) {
        // Check if directory exists
        if (dataDir.mkdirFor(dest)) {
            auto buffer = (const char*)AAsset_getBuffer(asset);
            auto length = AAsset_getLength(asset);

            auto targetFileName = dataDir.root() + "/" + dest;
            auto outFile = std::fopen(targetFileName.c_str(), "w+");
            LOGW_ANDROID("Replacing asset %s", targetFileName.c_str());
            bool retValue = true;
            if (outFile != nullptr) {
                int res = std::fwrite(buffer, 1, length, outFile);
                if (res != length) {
                    LOGE_ANDROID("Error writing asset file.");
                    retValue = false;
                }
                std::fclose(outFile);
            }
            else {
                LOGE_ANDROID("Can't create asset file: %s", std::strerror(errno));
                retValue = false;
            }
            AAsset_close(asset);
            return retValue;
        }
    } else {
        LOGE_ANDROID("assert %s not found", source);
    }
    return false;
}