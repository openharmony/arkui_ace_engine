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

#include "directory.h"
#include <libgen.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>

bool Directory::mkdirFor(const char* filename) {
    std::string base = dirname(filename);
    if (base == ".") return true;

    auto dir = rootPath + "/" + base;
    if (notExist(dir.c_str())) {
        std::vector<std::string> parents;
        while (base != ".") {
            parents.push_back(base);
            base = dirname(base.c_str());
        }
        for (auto it = parents.rbegin(); it != parents.rend(); ++it ) {
            dir = rootPath + "/" + *it;
            if (notExist(dir.c_str())) { // otherwise: sb.st_mode & S_IFDIR
                if (mkdir(dir.c_str(), 0770) != 0) return false;
            }
        }
    }
    return true;
}

bool Directory::notExist(const char *dir) {
    static struct stat sb = {0};
    return stat(dir, &sb) != 0 && ENOENT == errno;
}