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

export class Profiler {
    totalTime = 0
    transformTime = 0
    proceedTime = 0
    restartTime = 0
    visitedNodes = 0
    createdNodes = 0

    report() {
        console.log(
            "total compiler:",
            this.totalTime,
            " proceeds:",
            this.proceedTime,
            " restarts",
            this.restartTime,
            " transforms:",
            this.transformTime,
            " visited:",
            this.visitedNodes,
            " created:",
            this.createdNodes
        )
    }
}