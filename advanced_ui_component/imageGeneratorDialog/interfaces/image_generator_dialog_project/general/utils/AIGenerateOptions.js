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
        this.resolution = '2K';
        this.ratio = '1:1';
        this.version = '1.0.0';
    }
    static getInstance() {
        return AIGenerateOptions.instance;
    }
    setImages(c10) {
        if (c10.length === 0) {
            this.action = 1;
        }
        else {
            this.action = 0;
        }
        console.info(TAG, `Update the number of images from ${this.images?.length} to ${c10.length}.`);
        this.images = c10;
    }
    updateRelativeLayout(a10) {
        if (a10) {
            let b10 = {
                image: undefined,
                url: undefined,
                rect: undefined,
                rotation: undefined,
                zIndex: 0,
                isHandwrite: false
            };
            this.layoutImage = b10;
        }
        else {
            this.layoutImage = undefined;
        }
    }
    updateUserPrompt(z9) {
        this.userPrompt = z9;
    }
    updateShapePath(y9) {
        this.shapePath = y9;
    }
    updateStyle(x9) {
        this.style = x9;
    }
    updateResolution(w9) {
        this.resolution = w9;
    }
    updateRatio(v9) {
        this.ratio = v9;
    }
    updateType(u9) {
        this.type = u9;
    }
    updateVersion(t9) {
        this.version = t9;
    }
}
AIGenerateOptions.instance = new AIGenerateOptions();
