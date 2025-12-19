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
    setImages(images) {
        if (images.length === 0) {
            this.action = 1;
        }
        else {
            this.action = 0;
        }
        console.info(TAG, `Update the number of images from ${this.images?.length} to ${images.length}.`);
        this.images = images;
    }
    updateRelativeLayout(layout) {
        if (layout) {
            let layout = {
                image: undefined,
                url: undefined,
                rect: undefined,
                rotation: undefined,
                zIndex: 0,
                isHandwrite: false
            };
            this.layoutImage = layout;
        }
        else {
            this.layoutImage = undefined;
        }
    }
    updateUserPrompt(prompt) {
        this.userPrompt = prompt;
    }
    updateShapePath(shapePath) {
        this.shapePath = shapePath;
    }
    updateStyle(style) {
        this.style = style;
    }
    updateResolution(resolution) {
        this.resolution = resolution;
    }
    updateRatio(ratio) {
        this.ratio = ratio;
    }
    updateType(type) {
        this.type = type;
    }
    updateVersion(version) {
        this.version = version;
    }
}
AIGenerateOptions.instance = new AIGenerateOptions();
