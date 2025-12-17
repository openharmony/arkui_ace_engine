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
    setSelfTextGenerateModal(v17) {
        this.TextModal = v17;
    }
    ;
    setSelfImageGenerateModal(u17) {
        this.ImageModal = u17;
    }
    ;
    delay() {
        return new Promise(t17 => setTimeout(t17, 1000));
    }
    async TextAIGenerate(p17) {
        this.stopTask = false;
        let q17 = this.sessionId;
        this.sessionId++;
        if (this.TextModal !== undefined) {
            console.info(TAG, `Complete the text polishing task using a user-defined model.`);
            let r17 = (s17) => {
                if (s17.partialFail !== undefined) {
                    console.error(TAG, `Error in requestTextGeneration: ${s17.partialFail}.`);
                    p17.onError();
                }
                else {
                    if (p17.onResult) {
                        p17.onResult(s17);
                    }
                }
            };
            this.TextModal.requestTextGeneration(q17, AIGenerateOptions.getInstance().userPrompt, r17);
            p17.onReady();
        }
        else {
            console.info(TAG, `Complete the text polishing task using Celia model.`);
            this.mockPoolingTask(p17);
        }
        return q17;
    }
    ;
    async mockPoolingTask(k17) {
        let l17 = ['mockThink：', 'mockResult：'];
        let m17 = {
            type: 0,
            reasoningContent: undefined,
            content: undefined,
        };
        k17.onReady();
        setTimeout(async () => {
            for (let o17 = 0; o17 < 10; o17++) {
                if (this.stopTask) {
                    return;
                }
                m17.reasoningContent = l17[0] +
                    AIGenerateOptions.getInstance().userPrompt.slice(0, Math.floor(Math.random() * AIGenerateOptions.getInstance().userPrompt.length));
                if (k17.onResult) {
                    k17.onResult(m17);
                }
                await this.delay();
            }
            m17.type = 1;
            m17.reasoningContent = undefined;
            m17.content = undefined;
            console.info(TAG, `The thinking process of the text polishing task has been completed.`);
            if (k17.onResult) {
                k17.onResult(m17);
            }
            m17.type = 0;
            for (let n17 = 0; n17 < 5; n17++) {
                if (this.stopTask) {
                    return;
                }
                m17.content = l17[1] +
                    AIGenerateOptions.getInstance().userPrompt.slice(0, Math.floor(Math.random() * AIGenerateOptions.getInstance().userPrompt.length));
                if (k17.onResult) {
                    k17.onResult(m17);
                }
                await this.delay();
            }
            m17.type = 1;
            m17.reasoningContent = undefined;
            m17.content = undefined;
            console.info(TAG, `The text polishing task generation process has been completed.`);
            if (k17.onResult) {
                k17.onResult(m17);
            }
        }, 1000);
        return;
    }
    async ImageAIGenerate(d17) {
        let e17 = this.sessionId;
        this.sessionId++;
        let f17;
        if (this.ImageModal !== undefined) {
            console.info(TAG, `Complete the image generation task using a user-defined model.`);
            let h17 = {
                images: AIGenerateOptions.getInstance().images,
                positionImage: AIGenerateOptions.getInstance().layoutImage?.image,
                selectPath: AIGenerateOptions.getInstance().shapePath,
                prompt: AIGenerateOptions.getInstance().userPrompt,
                style: AIGenerateOptions.getInstance().style,
                imageSize: AIGenerateOptions.getInstance().resolution,
            };
            let i17 = (j17) => {
                if (j17.partialFail !== undefined) {
                    console.error(TAG, `Error in requestImageGeneration: ${j17.partialFail}.`);
                    d17.onError();
                }
                else {
                    if (j17.type === imageGeneration.PartialResultType.PARTIAL) {
                        console.info(TAG, `The image generation task returns an image.`);
                        f17.push(j17.imageData);
                    }
                    else if (j17.type === imageGeneration.PartialResultType.COMPLETED) {
                        f17.push(j17.imageData);
                        console.info(TAG, `The task of generating the image has been completed.`);
                        if (d17.onComplete) {
                            d17.onComplete(f17);
                        }
                    }
                }
            };
            this.ImageModal.requestImageGeneration(e17, h17, i17);
            d17.onReady();
        }
        else {
            console.info(TAG, `Complete the image generation task using Celia model.`);
            d17.onReady();
            AIGenerateOptions.getInstance().images?.forEach(async (g17) => {
                f17.push(g17.url.toString());
                console.info(TAG, `The image generation task returns an image.`);
                await this.delay();
            });
            setTimeout(() => {
                console.info(TAG, `The task of generating the image has been completed.`);
                if (d17.onComplete) {
                    d17.onComplete(f17);
                }
            }, 10000);
        }
        return e17;
    }
    ;
    async cancelTextGenerateTask(c17) {
        console.info(TAG, `Text task sessionId: ${c17} cancel.`);
        if (this.TextModal !== undefined) {
            this.TextModal.cancelTextGeneration(Number(c17));
        }
        else {
            this.stopTask = true;
        }
    }
    ;
    async cancelImageGenerateTask(b17) {
        console.info(TAG, `Image task sessionId: ${b17} cancel.`);
        if (this.ImageModal !== undefined) {
            this.ImageModal.cancelImageGeneration(Number(b17));
        }
        else {
        }
    }
    ;
}
AIGenerateImpl.instance = new AIGenerateImpl();
