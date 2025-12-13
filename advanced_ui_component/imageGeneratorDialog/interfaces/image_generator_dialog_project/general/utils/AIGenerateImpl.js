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

import imageGeneration from '@ohos.arkui.intelligence.imageGeneration';
import { AIGenerateOptions } from './AIGenerateOptions';
let TAG = '[AIGenerateImpl]';
export class AIGenerateImpl {
    constructor() {
        this.stopTask = false;
        this.sessionId = 0;
    }
    static getInstance() {
        return AIGenerateImpl.instance;
    }
    ;
    setSelfTextGenerateModal(s9) {
        this.TextModal = s9;
    }
    ;
    setSelfImageGenerateModal(r9) {
        this.ImageModal = r9;
    }
    ;
    delay() {
        return new Promise(q9 => setTimeout(q9, 1000));
    }
    async TextAIGenerate(h9) {
        this.stopTask = false;
        let i9 = this.sessionId;
        this.sessionId++;
        if (this.TextModal !== undefined) {
            console.info(TAG, `Complete the text polishing task using a user-defined model.`);
            let n9 = (p9) => {
                if (p9.partialFail !== undefined) {
                    console.error(TAG, `Error in requestTextGeneration: ${p9.partialFail}.`);
                    h9.onError();
                }
                else {
                    if (h9.onResult) {
                        h9.onResult(p9);
                    }
                }
            };
            this.TextModal.requestTextGeneration(i9, AIGenerateOptions.getInstance().userPrompt, n9);
            h9.onReady();
        }
        else {
            console.info(TAG, `Complete the text polishing task using Celia model.`);
            this.mockPoolingTask(h9);
        }
        return i9;
    }
    ;
    async mockPoolingTask(r2) {
        let s2 = ['mockThink：', 'mockResult：'];
        let t2 = {
            type: 0,
            reasoningContent: undefined,
            content: undefined,
        };
        r2.onReady();
        setTimeout(async () => {
            for (let v2 = 0; v2 < 10; v2++) {
                if (this.stopTask) {
                    return;
                }
                t2.reasoningContent = s2[0] +
                    AIGenerateOptions.getInstance().userPrompt.slice(0, Math.floor(Math.random() * AIGenerateOptions.getInstance().userPrompt.length));
                if (r2.onResult) {
                    r2.onResult(t2);
                }
                await this.delay();
            }
            t2.type = 1;
            t2.reasoningContent = undefined;
            t2.content = undefined;
            console.info(TAG, `The thinking process of the text polishing task has been completed.`);
            if (r2.onResult) {
                r2.onResult(t2);
            }
            t2.type = 0;
            for (let u2 = 0; u2 < 5; u2++) {
                if (this.stopTask) {
                    return;
                }
                t2.content = s2[1] +
                    AIGenerateOptions.getInstance().userPrompt.slice(0, Math.floor(Math.random() * AIGenerateOptions.getInstance().userPrompt.length));
                if (r2.onResult) {
                    r2.onResult(t2);
                }
                await this.delay();
            }
            t2.type = 1;
            t2.reasoningContent = undefined;
            t2.content = undefined;
            console.info(TAG, `The text polishing task generation process has been completed.`);
            if (r2.onResult) {
                r2.onResult(t2);
            }
        }, 1000);
        return;
    }
    async ImageAIGenerate(z8) {
        let a9 = this.sessionId;
        this.sessionId++;
        let b9;
        if (this.ImageModal !== undefined) {
            console.info(TAG, `Complete the image generation task using a user-defined model.`);
            let d9 = {
                images: AIGenerateOptions.getInstance().images,
                positionImage: AIGenerateOptions.getInstance().layoutImage?.image,
                selectPath: AIGenerateOptions.getInstance().shapePath,
                prompt: AIGenerateOptions.getInstance().userPrompt,
                style: AIGenerateOptions.getInstance().style,
                size: AIGenerateOptions.getInstance().resolution,
            };
            let e9 = (g9) => {
                if (g9.partialFail !== undefined) {
                    console.error(TAG, `Error in requestImageGeneration: ${g9.partialFail}.`);
                    z8.onError();
                }
                else {
                    if (g9.type === imageGeneration.PartialResultType.PARTIAL) {
                        console.info(TAG, `The image generation task returns an image.`);
                        b9.push(g9.imageData);
                    }
                    else if (g9.type === imageGeneration.PartialResultType.COMPLETED) {
                        b9.push(g9.imageData);
                        console.info(TAG, `The task of generating the image has been completed.`);
                        if (z8.onComplete) {
                            z8.onComplete(b9);
                        }
                    }
                }
            };
            this.ImageModal.requestImageGeneration(a9, d9, e9);
            z8.onReady();
        }
        else {
            console.info(TAG, `Complete the image generation task using Celia model.`);
            z8.onReady();
            AIGenerateOptions.getInstance().images?.forEach(async (c9) => {
                b9.push(c9.url.toString());
                console.info(TAG, `The image generation task returns an image.`);
                await this.delay();
            });
            setTimeout(() => {
                console.info(TAG, `The task of generating the image has been completed.`);
                if (z8.onComplete) {
                    z8.onComplete(b9);
                }
            }, 10000);
        }
        return a9;
    }
    ;
    async cancelTextGenerateTask(y8) {
        console.info(TAG, `Text task sessionId: ${y8} cancel.`);
        if (this.TextModal !== undefined) {
            this.TextModal.cancelTextGeneration(Number(y8));
        }
        else {
            this.stopTask = true;
        }
    }
    ;
    async cancelImageGenerateTask(x8) {
        console.info(TAG, `Image task sessionId: ${x8} cancel.`);
        if (this.ImageModal !== undefined) {
            this.ImageModal.cancelImageGeneration(Number(x8));
        }
        else {
        }
    }
    ;
}
AIGenerateImpl.instance = new AIGenerateImpl();
