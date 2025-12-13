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
import { AIGenerateCallBack } from '../types/Declaration';
export declare class AIGenerateImpl {
    private stopTask;
    private sessionId;
    private TextModal;
    private ImageModal;
    private static instance;
    static getInstance(): AIGenerateImpl;
    setSelfTextGenerateModal(v17: imageGeneration.TextGenerationModel | undefined): void;
    setSelfImageGenerateModal(u17: imageGeneration.ImageGenerationModel | undefined): void;
    private delay;
    TextAIGenerate(p17: AIGenerateCallBack): Promise<number>;
    private mockPoolingTask;
    ImageAIGenerate(d17: AIGenerateCallBack): Promise<number>;
    cancelTextGenerateTask(c17: number): Promise<void>;
    cancelImageGenerateTask(b17: number): Promise<void>;
}
