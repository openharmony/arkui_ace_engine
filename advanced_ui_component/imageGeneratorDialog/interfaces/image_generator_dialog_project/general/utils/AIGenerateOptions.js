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

let TAG = '[AIGenerateOptions]';
export class AIGenerateOptions {
    constructor() {
        this.action = 0;
        this.userPrompt = '';
        this.type = 0;
        this.resolution = { width: 100, height: 100 };
        this.ratio = '1:1';
        this.version = '1.0.0';
    }
    static getInstance() {
        return AIGenerateOptions.instance;
    }
    setImages(f18) {
        if (f18.length === 0) {
            this.action = 1;
        }
        else {
            this.action = 0;
        }
        console.info(TAG, `Update the number of images from ${this.images?.length} to ${f18.length}.`);
        this.images = f18;
    }
    updateRelativeLayout(d18) {
        if (d18) {
            let e18 = {
                image: undefined,
                url: undefined,
                rect: undefined,
                rotation: undefined,
                zIndex: 0,
                isHandwrite: false
            };
            this.layoutImage = e18;
        }
        else {
            this.layoutImage = undefined;
        }
    }
    updateUserPrompt(c18) {
        this.userPrompt = c18;
    }
    updateShapePath(b18) {
        this.shapePath = b18;
    }
    updateStyle(a18) {
        this.style = a18;
    }
    updateResolution(z17) {
        this.resolution = z17;
    }
    updateRatio(y17) {
        this.ratio = y17;
    }
    updateType(x17) {
        this.type = x17;
    }
    updateVersion(w17) {
        this.version = w17;
    }
}
AIGenerateOptions.instance = new AIGenerateOptions();
