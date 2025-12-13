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
import { ApplicationStateChangeCallback } from '@kit.AbilityKit';
import { systemDateTime } from '@kit.BasicServicesKit';

@ComponentV2
export struct GenerateProgress {
  @Param currentGenerateState: ImageGenerateState | undefined = undefined;
  @Event changeCurrentState: (state: ImageGenerateState) => void = (state: ImageGenerateState) => {};
  @Param imageNumber: number = 0;
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
    // 1图30s，2图40s，3图50s，4图70s 进度100%，每1%为300ms, 400ms, 500ms, 700ms
    let timeCntRet: Array<number> = [300, 300, 400, 500, 700];
    if (imageNumber < timeCntRet.length) {
      return timeCntRet[imageNumber];
    }
    return 300;
  }

  aboutToAppear(): void {
    this.createApplicationListener();
    this.createTimer();
  }

  aboutToDisappear(): void {
    this.clearApplicationListener();
    this.clearTimer();
  }

  createApplicationListener(): void {
    let that = this;
    this.canvasGenerateProgressChangeCallback = {
      onApplicationForeground() {
        let currentTimeStamp = systemDateTime.getTime();
        if (that.isGenerateSuccess) {
          this.progressValue = that.total;
        } else if (that.estimatedTime > 0) {
          let timeDiff = Math.floor((currentTimeStamp - that.goToBackGroundTimeStamp) / that.estimatedTime);
          let progressValue = that.goToBackProgressValue + timeDiff;
          if (progressValue >= that.total) {
            that.progressValue = that.total - 1;
          } else {
            that.progressValue = progressValue;
          }
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
        } else if (this.timerCnt >= 200) {
          // Timeout
          this.onTimeOut();
        } else if (this.progressValue < this.total - 1) {
          this.progressValue++;
        }
        this.timerCnt++;
      }
    }, this.estimatedTime)
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
    }, 300)
  }

  onTimeOut(): void {
    this.clearTimer();
    this.clearApplicationListener();
    this.isGenerateTimeout = true;
    this.progressValue = 0;
    // todo: AI generate cancel api
  }

  build() {
    Column() {
      Stack(){
        Stack() {
          Stack().backgroundColor(Color.White).width((100 - this.progressValue) * 1.5)
            .position({right: 0}).height(40).animation({
            duration: this.progressValue == this.total ? 400 : 150,
            curve: Curve.EaseOut,
            playMode: PlayMode.Normal
          })
        }.width(150).height(40).blur(20).borderRadius(20).clip(true)
        Row() {
          Column() {
            Text(this.isGenerateSuccess ? '已完成' : this.isGenerateTimeout ? `生成失败`
              : `AI生成中  ${this.progressValue} %`)
              .fontSize(14)
              .fontFamily("HarmonyHeiTi")
              .maxLines(1)
              .textOverflow({ overflow: TextOverflow.MARQUEE })
              .width(100)
          }
          Column() {
            if (!this.isGenerateSuccess) {
              Image($r('sys.media.ohos_ic_public_cancel'))
                .width(22)
                .height(22)
                .onClick(() => {
                  if (!this.isGenerateSuccess) {
                    this.changeCurrentState(ImageGenerateState.CONFIGURATION)
                  }
                })
            }
          }
        }.justifyContent(FlexAlign.SpaceBetween).width('100%').height(22)
        .padding({
          left: 12,
          right: 12
        })
      }.height('100%')

    }.width(150).height(40)
  }
}

@ComponentV2
export struct MinimizeButton {
  build() {
    Button({type: ButtonType.Circle}) {
      SymbolGlyph($r('sys.symbol.smal_window_playback'))
        .fontSize(21.62)
        .fontWeight(400)
    }
    .backgroundColor(Color.White)
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