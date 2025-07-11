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

import { UniqueId } from "@koalaui/common"

export class GenSymGenerator {
    // Global for the whole program.
    private static callCount: number = 0;
    static instance: GenSymGenerator;

    // Set `stable` to true if you want to have more predictable values.
    // For example for tests.
    // Don't use it in production!
    private constructor(public stableForTests: boolean = false) {
        if (stableForTests) GenSymGenerator.callCount = 0;
    }

    static getInstance(stableForTests: boolean = false): GenSymGenerator {
        if (!this.instance) {
            this.instance = new GenSymGenerator(stableForTests);
        }

        return this.instance;
    }

    sha1Id(callName: string): string {
        const uniqId = new UniqueId();
        uniqId.addString("gensym uniqid");
        uniqId.addString(callName);
        uniqId.addI32(GenSymGenerator.callCount++);
        return uniqId.compute().substring(0, 7);
    }

    stringId(callName: string): string {
        return `${GenSymGenerator.callCount++}_${callName}_id`;
    }

    id(callName: string = ""): string {
        const positionId = (this.stableForTests) ?
            this.stringId(callName) :
            this.sha1Id(callName);

        const coreceToStr = parseInt(positionId, 16).toString();

        // compiler use gensym%%_ but % is illegal before after-check phase
        return `gensym___${coreceToStr}`;
    }
}