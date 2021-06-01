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

#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>

#include "adapter/preview/entrance/ace_ability.h"
#include "adapter/preview/entrance/ace_run_args.h"

namespace {

constexpr int32_t GET_INSPECTOR_TREE_TIMES = 12;
constexpr int32_t GET_INSPECTOR_TREE_INTERVAL = 5000;
constexpr char FILE_NAME[] = "InspectorTree.txt";
// card default width and height:
// 2*1 (150*54)
// 2*2 (150*150)
// 4*2 (320*150)
// 4*4 (320*344)
constexpr int32_t CARD_DEFAULT_WIDTH = 320;
constexpr int32_t CARD_DEFAULT_HEIGHT = 344;

} // namespace

int main()
{
    auto&& renderCallback = [](const void*, size_t bufferSize) -> bool { return true; };

#ifdef MAC_PLATFORM
    std::string assetPath = "/Volumes/SSD2T/daily-test/preview/js/default_card";
    std::string resourcesPath = "/Volumes/SSD2T/daily-test/preview/js/resources";
    constexpr double resolution = 2;
#else
    std::string assetPath = "D:\\Workspace\\preview\\js\\default_card";
    std::string resourcesPath = "D:\\Workspace\\preview\\js\\resources";
    constexpr double resolution = 1;
#endif

    OHOS::Ace::Platform::AceRunArgs args = {
        .assetPath = assetPath,
        .resourcesPath = resourcesPath,
        .deviceWidth = CARD_DEFAULT_WIDTH,
        .deviceHeight = CARD_DEFAULT_HEIGHT,
        .windowTitle = "ACE card",
        .resolution = resolution,
        .formsEnabled = true,
        .onRender = std::move(renderCallback),
    };

    auto ability = OHOS::Ace::Platform::AceAbility::CreateInstance(args);
    if (!ability) {
        std::cerr << "Could not create AceAbility!" << std::endl;
        return -1;
    }

    std::thread timer([&ability]() {
        int32_t getJSONTreeTimes = GET_INSPECTOR_TREE_TIMES;
        while (getJSONTreeTimes--) {
            std::this_thread::sleep_for(std::chrono::milliseconds(GET_INSPECTOR_TREE_INTERVAL));
            std::string jsonTreeStr = ability->GetJSONTree();
            // clear all information
            std::ofstream fileCleaner(FILE_NAME, std::ios_base::out);
            std::ofstream fileWriter(FILE_NAME, std::ofstream::app);
            fileWriter << jsonTreeStr;
            fileWriter << std::endl;
            fileWriter.close();
        }
    });
    ability->InitEnv();
    std::cout << "Ace initialize done. run loop now" << std::endl;
    ability->Start();

    return 0;
}
