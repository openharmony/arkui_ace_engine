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

import imageGeneration from '@ohos.arkui.intelligence.imageGeneration'

import { AIGenerateOptions } from './AIGenerateOptions';
import { AIGenerateCallBack } from '../types/Declaration';

let TAG: string = '[AIGenerateImpl]'

export class AIGenerateImpl {
  private stopTask: boolean = false;  // only for mock
  private sessionId: number = 0;

  private TextModal: imageGeneration.TextGenerationModel | undefined;
  private ImageModal: imageGeneration.ImageGenerationModel | undefined;

  private static instance: AIGenerateImpl = new AIGenerateImpl();

  static getInstance() {
    return AIGenerateImpl.instance;
  };

  public setSelfTextGenerateModal(modal: imageGeneration.TextGenerationModel | undefined): void {
    this.TextModal = modal;
  };

  public setSelfImageGenerateModal(modal: imageGeneration.ImageGenerationModel | undefined): void {
    this.ImageModal = modal;
  };

  private delay(): Promise<void> {
    return new Promise(resolve => setTimeout(resolve, 1000));
  }

  public async TextAIGenerate(callback: AIGenerateCallBack): Promise<number> {
    this.stopTask = false;
    let retSessionId: number = this.sessionId;
    this.sessionId++;

    if (this.TextModal !== undefined) {
      console.info(TAG, `Complete the text polishing task using a user-defined model.`);
      let userTextModalCallback: Callback<imageGeneration.GenerateTextTaskPartialResult> = (ret: imageGeneration.GenerateTextTaskPartialResult) => {
        if (ret.partialFail !== undefined) {
          console.error(TAG, `Error in requestTextGeneration: ${ret.partialFail}.`);
          callback.onError();  // TODO Add error enumeration
        } else {
          if (callback.onResult) {
            callback.onResult(ret);
          }
        }
      }

      this.TextModal.requestTextGeneration(retSessionId, AIGenerateOptions.getInstance().userPrompt, userTextModalCallback);
      callback.onReady();
    } else {
      console.info(TAG, `Complete the text polishing task using Celia model.`);
      this.mockPoolingTask(callback);
    }

    return retSessionId;
  };

  private async mockPoolingTask(callback: AIGenerateCallBack): Promise<void> {
    let mockString: string[] = ['mockThink：', 'mockResult：'];

    let mockReturn: imageGeneration.GenerateTextTaskPartialResult = {
      type: 0,
      reasoningContent: undefined,
      content: undefined,
    }

    callback.onReady();

    setTimeout(async () => {
      for (let temp = 0; temp < 10 ; temp++) {
        if (this.stopTask) {
          return;
        }
        mockReturn.reasoningContent = mockString[0] +
          AIGenerateOptions.getInstance().userPrompt.slice(0, Math.floor(Math.random() * AIGenerateOptions.getInstance().userPrompt.length));
        if (callback.onResult) {
          callback.onResult(mockReturn);
        }
        await this.delay();
      }

      mockReturn.type = 1;
      mockReturn.reasoningContent = undefined;
      mockReturn.content = undefined;
      console.info(TAG, `The thinking process of the text polishing task has been completed.`);
      if (callback.onResult) {
        callback.onResult(mockReturn);
      }
      mockReturn.type = 0;

      for (let temp = 0; temp < 5 ; temp++) {
        if (this.stopTask) {
          return;
        }
        mockReturn.content = mockString[1] +
          AIGenerateOptions.getInstance().userPrompt.slice(0, Math.floor(Math.random() * AIGenerateOptions.getInstance().userPrompt.length));
        if (callback.onResult) {
          callback.onResult(mockReturn);
        }
        await this.delay();
      }

      mockReturn.type = 1;
      mockReturn.reasoningContent = undefined;
      mockReturn.content = undefined;
      console.info(TAG, `The text polishing task generation process has been completed.`);
      if (callback.onResult) {
        callback.onResult(mockReturn);
      }
    }, 1000);

    return;
  }

  public async ImageAIGenerate(callback: AIGenerateCallBack): Promise<number> {
    let retSessionId: number = this.sessionId;
    this.sessionId++;

    let getResultFromAIGenerate: string[];

    if (this.ImageModal !== undefined) {
      console.info(TAG, `Complete the image generation task using a user-defined model.`);
      let taskParams: imageGeneration.GenerateImageTaskParams = {
        images: AIGenerateOptions.getInstance().images!,
        positionImage: AIGenerateOptions.getInstance().layoutImage?.image,
        selectPath: AIGenerateOptions.getInstance().shapePath,
        prompt: AIGenerateOptions.getInstance().userPrompt,
        style: AIGenerateOptions.getInstance().style,
        size: AIGenerateOptions.getInstance().resolution,
        // imageCount: ,
      }

      let userImageModalCallback: Callback<imageGeneration.GenerateImageTaskPartialResult> = (ret: imageGeneration.GenerateImageTaskPartialResult) => {
        if (ret.partialFail !== undefined) {
          console.error(TAG, `Error in requestImageGeneration: ${ret.partialFail}.`);
          callback.onError();  // TODO Add error enumeration
        } else {
          if (ret.type === imageGeneration.PartialResultType.PARTIAL) {
            console.info(TAG, `The image generation task returns an image.`);
            getResultFromAIGenerate.push(ret.imageData!);
          } else if (ret.type === imageGeneration.PartialResultType.COMPLETED) {
            getResultFromAIGenerate.push(ret.imageData!);
            console.info(TAG, `The task of generating the image has been completed.`);
            if (callback.onComplete) {
              callback.onComplete(getResultFromAIGenerate);
            }
          }
        }
      }

      this.ImageModal.requestImageGeneration(retSessionId, taskParams, userImageModalCallback);
      callback.onReady();
    } else {
      console.info(TAG, `Complete the image generation task using Celia model.`);
      callback.onReady();
      AIGenerateOptions.getInstance().images?.forEach(async (image: imageGeneration.ImageItem) => {
        getResultFromAIGenerate.push(image.url!.toString());
        console.info(TAG, `The image generation task returns an image.`);
        await this.delay();
      })
      setTimeout(() => {
        console.info(TAG, `The task of generating the image has been completed.`);
        if (callback.onComplete) {
          callback.onComplete(getResultFromAIGenerate);
        }
      }, 10000)
    }

    return retSessionId;
  };

  public async cancelTextGenerateTask(sessionId: number): Promise<void> {
    console.info(TAG, `Text task sessionId: ${sessionId} cancel.`);
    if (this.TextModal !== undefined) {
      this.TextModal.cancelTextGeneration(Number(sessionId));
    } else {
      // TODO
      this.stopTask = true;
    }
  };

  public async cancelImageGenerateTask(sessionId: number): Promise<void> {
    console.info(TAG, `Image task sessionId: ${sessionId} cancel.`);
    if (this.ImageModal !== undefined) {
      this.ImageModal.cancelImageGeneration(Number(sessionId));
    } else {
      // TODO
    }
  };
}