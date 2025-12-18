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
import { ImageGenerateState } from '../types/Declaration'
import { AIGenerateImpl } from "../utils/AIGenerateImpl";
import { AIGenerateOptions } from '../utils/AIGenerateOptions';
import { ApplicationStateChangeCallback } from '@kit.AbilityKit';
import { systemDateTime } from '@kit.BasicServicesKit';

@ComponentV2
export struct GenerateProgress {
  @Param currentGenerateState: ImageGenerateState | undefined = undefined;
  @Event changeCurrentState: (state: ImageGenerateState) => void = (state: ImageGenerateState) => {};
  @Local imageNumber: number = 0;
  @Local progressValue: number = 0;
  @Local isGenerateSuccess: boolean = false;
  @Local isGenerateTimeout: boolean = false;
  private total: number = 100;
  private timerCnt: number = 0;
  private timerId: number = -1;
  private goToBackGroundTimeStamp: number = 0;
  private goToBackProgressValue: number = 0;
  private estimatedTime: number = 0;
  private isForeground: boolean = true;
  private canvasGenerateProgressChangeCallback: ApplicationStateChangeCallback | undefined = undefined;
  @Monitor('currentGenerateState')
  currentGenerateStateChangeMonitor(monitor: IMonitor) {
    if (this.isForeground &&
      monitor.value<ImageGenerateState>('currentGenerateState')?.now === ImageGenerateState.BEFORE_GENERATED) {
      this.progressValue = this.total;
    }
  }

  getEstimatedTime(imageNumber: number): number {
    // 0/1图30s，2图40s，3图50s，4图70s 进度100%。
    let timeCntRet: Array<number> = [30, 30, 40, 50, 70];
    if (imageNumber < timeCntRet.length) {
      return timeCntRet[imageNumber];
    }
    return 30;
  }

  getUpdateProgressValue(currentValue: number, estimatedTime: number, currentCnt: number): number {
    // 非线性进度，前70%用总时长的50%
    let retVal = currentValue;
    for (let i = 0; i < currentCnt; i++) {
      if (retVal < 70) {
        retVal += 35 / estimatedTime;
      } else if (retVal >= 70 && retVal < this.total) {
        retVal += 15 / estimatedTime;
      }
      if (retVal >= this.total - 1) {
        return this.total - 1;
      }
    }
    return retVal;
  }

  aboutToAppear(): void {
    this.imageNumber = AIGenerateOptions.getInstance().images?.length ?? 0;
    this.createApplicationListener();
    this.createTimer();
  }

  aboutToDisappear(): void {
    this.clearApplicationListener();
    this.clearTimer();
    this.cancelImageGenerateTask();
  }

  createApplicationListener(): void {
    let that = this;
    this.canvasGenerateProgressChangeCallback = {
      onApplicationForeground() {
        let currentTimeStamp = systemDateTime.getTime();
        if (that.isGenerateSuccess) {
          this.progressValue = that.total;
        } else if (that.estimatedTime > 0) {
          let timeDiff = Math.floor((currentTimeStamp - that.goToBackGroundTimeStamp) / 250);
          that.progressValue = that.getUpdateProgressValue(that.goToBackProgressValue, that.estimatedTime, timeDiff);
          that.timerCnt += timeDiff;
        }
        that.isForeground = true;
        // todo: recreate ai request to get result
      },
      onApplicationBackground() {
        that.goToBackGroundTimeStamp = systemDateTime.getTime();
        that.goToBackProgressValue = that.progressValue;
        that.isForeground = false;
      }
    };
    this.getUIContext()?.getHostContext()?.getApplicationContext()
    ?.on('applicationStateChange', this.canvasGenerateProgressChangeCallback);
  }

  clearApplicationListener(): void {
    if (this.canvasGenerateProgressChangeCallback) {
      this.getUIContext()?.getHostContext()?.getApplicationContext()
      ?.off('applicationStateChange', this.canvasGenerateProgressChangeCallback);
      this.canvasGenerateProgressChangeCallback = undefined;
    }
  }

  createTimer(): void {
    this.timerCnt = 0;
    this.estimatedTime = this.getEstimatedTime(this.imageNumber);
    this.timerId = setInterval(() => {
      if (this.isForeground) {
        if (this.progressValue == this.total) {
          // Success
          this.onSuccess();
        } else if (this.timerCnt >= this.estimatedTime * 8) { // 超时时间为标准时间的两倍
          // Timeout
          this.onTimeOut();
        } else if (this.progressValue < this.total - 1) {
          this.progressValue = this.getUpdateProgressValue(this.progressValue, this.estimatedTime, 1);
        }
        this.timerCnt++;
      }
    }, 250)
  }

  clearTimer(): void {
    if (this.timerId >= 0) {
      clearInterval((this.timerId));
    }
  }

  onSuccess(): void {
    this.clearTimer();
    this.clearApplicationListener();
    this.isGenerateSuccess = true;
    setTimeout(() => {
      this.changeCurrentState(ImageGenerateState.GENERATED);
    }, 400)
  }

  onTimeOut(): void {
    this.clearTimer();
    this.clearApplicationListener();
    this.isGenerateTimeout = true;
    this.progressValue = 0;
    this.cancelImageGenerateTask();
  }

  cancelImageGenerateTask(): void {
    let generateInstance = AIGenerateImpl.getInstance();
    generateInstance.cancelImageGenerateTask(generateInstance.getCurrentImageSessionId());
  }

  build() {
    Column() {
      Stack(){
        Stack() {
          Stack()
            .backgroundColor('#99FFFFFF').width(160).height(40)
          Column() {
            // progress bar
          }
          .width(Math.round(this.progressValue * 1.6)).height(40)
          .animation({
            duration: this.progressValue == this.total ? 400 : 150,
            curve: Curve.EaseOut,
            playMode: PlayMode.Normal
          })
        }.width(160).height(40)
        .blur(31)
        .borderRadius(31.11, RenderStrategy.OFFSCREEN).clip(true).alignContent(Alignment.Start)
        Row() {
          Column() {
            Text(this.isGenerateTimeout ? `生成失败`
              : `AI生成中 ${Math.round(this.progressValue)}%`)
              .fontSize(16)
              .fontFamily("HarmonyHeiTi")
              .fontColor('#E6000000')
              .maxLines(1)
              .textOverflow({ overflow: TextOverflow.MARQUEE })
              .width(this.isGenerateSuccess ? 120 : 104)
          }
          Column() {
            if (!this.isGenerateSuccess) {
              SymbolGlyph($r('sys.symbol.xmark'))
                .fontSize(20)
                .onClick(() => {
                  if (!this.isGenerateSuccess) {
                    this.cancelImageGenerateTask()
                    this.changeCurrentState(ImageGenerateState.CONFIGURATION)
                  }
                })
            }
          }
        }.justifyContent(FlexAlign.SpaceBetween).width('100%').height(22)
        .padding({
          left: 16,
          right: 17
        })
      }.height('100%')

    }.width(160).height(40)
    .transition(TransitionEffect.OPACITY.animation({ duration: 500, curve: Curve.Ease }))
  }
}

@ComponentV2
export struct MinimizeButton {
  build() {
    Button({type: ButtonType.Circle}) {
      SymbolGlyph($r('sys.symbol.smal_window_playback'))
        .fontSize(22)
        .fontWeight(400)
        .fontColor(['#E6000000'])
    }
    .backgroundColor('#99FFFFFF')
    .width(40)
    .height(40)
    .margin({left: 8})
    .onClick(() => {

    })
  }
}

@ComponentV2
export struct GeneratingArea {
  @Param currentGenerateState: ImageGenerateState | undefined = undefined;
  @Event changeGenerateState: (state: ImageGenerateState) => void = (state: ImageGenerateState) => {};
  build() {
    Column() {
      Row() {
        GenerateProgress({
          currentGenerateState: this.currentGenerateState,
          changeCurrentState: this.changeGenerateState
        })
        MinimizeButton()
      }
    }.width('100%')
  }
}