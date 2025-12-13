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

import { common2D } from '@kit.ArkGraphics2D';
import imageGeneration from '@ohos.arkui.intelligence.imageGeneration'

let TAG: string = '[AIGenerateOptions]'

export class AIGenerateOptions {
  public action: number = 0;
  public userPrompt: string = '';
  public images: Array<imageGeneration.ImageItem> | undefined;
  public layoutImage: imageGeneration.ImageItem | undefined;
  public shapePath: Array<common2D.Point> | undefined;
  public style: string | undefined;
  public type: number = 0;
  public resolution: string = '2K';
  public ratio: string = '1:1';
  public version: string = '1.0.0';

  private static instance: AIGenerateOptions = new AIGenerateOptions();

  static getInstance() {
    return AIGenerateOptions.instance;
  }

  public setImages(images: Array<imageGeneration.ImageItem>): void {
    if (images.length === 0) {
      this.action = 1;
    } else {
      this.action = 0;
    }
    console.info(TAG, `Update the number of images from ${this.images?.length} to ${images.length}.`);
    this.images = images;
  }

  public updateRelativeLayout(layout: boolean): void {
    if (layout) {
      let layout: imageGeneration.ImageItem = {
        image: undefined,
        url: undefined,
        rect: undefined,
        rotation: undefined,
        zIndex: 0,
        isHandwrite: false
      }
      this.layoutImage = layout;
    } else {
      this.layoutImage = undefined;
    }
  }

  public updateUserPrompt(prompt: string): void {
    this.userPrompt = prompt;
  }

  public updateShapePath(shapePath: Array<common2D.Point>): void {
    this.shapePath = shapePath;
  }

  public updateStyle(style: string): void {
    this.style = style;
  }

  public updateResolution(resolution: string): void {
    this.resolution = resolution;
  }

  public updateRatio(ratio: string): void {
    this.ratio = ratio;
  }

  public updateType(type: number): void {
    this.type = type;
  }

  public updateVersion(version: string): void {
    this.version = version;
  }
}