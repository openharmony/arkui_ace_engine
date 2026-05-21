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

// [Start gesture_recognition]
@Entry
@ComponentV2
struct Index {
  @Local progress: number = 496000; // 初始进度，秒
  @Local total: number = 27490000; // 总时长，秒
  @Local currentWidth: string = '100%';
  @Local currentHeight: string = '100%';
  private currentPosX: number = 0;
  private currentPosY: number = 0;
  private currentFullScreenState: boolean = true;
  private normalPlayTimer: number = -1;
  private isPlaying: boolean = true;
  private fastForwardTimer: number = -1;
  private context = this.getUIContext().getHostContext()

  aboutToAppear(): void {
    // 启动一个周期性定时器每隔一秒刷新一次进度
    this.startNormalPlayTimer();
  };

  startNormalPlayTimer(): void {
    if (this.normalPlayTimer != -1) {
      this.stopNormalPlayTimer()
    };
    this.normalPlayTimer = setInterval(() => {
      this.progress = this.progress + 1000
    }, 1000);
  };

  stopNormalPlayTimer(): void {
    if (this.normalPlayTimer == -1) {
      return;
    };
    clearInterval(this.normalPlayTimer);
    this.normalPlayTimer = -1;
  };

  startFastForwardTimer(): void {
    if (this.fastForwardTimer != -1) {
      this.stopFastForwardTimer();
    };
    this.fastForwardTimer = setInterval(() => {
      this.progress = this.progress + 100000;
    }, 100);
  };

  stopFastForwardTimer(): void {
    if (this.fastForwardTimer == -1) {
      return;
    };
    clearInterval(this.fastForwardTimer);
    this.fastForwardTimer = -1;
  };

  showMessage(message: string): void {
    this.getUIContext().getPromptAction().showToast({ message: message, alignment: Alignment.Center });
  };

  resetPosInfo(): void {
    this.currentPosX = 0;
    this.currentPosY = 0;
  };

  toggleFullScreenState(): void {
    this.currentFullScreenState = !this.currentFullScreenState;
    if (this.currentFullScreenState) {
      this.currentWidth = '100%';
      this.currentHeight = '100%';
    } else {
      this.currentWidth = '100%';
      this.currentHeight = '50%';
    };
    // 请将$r('app.string.Play_full_screen')替换为实际资源文件，在本示例中该资源文件的value值为"全屏播放"
    // 请将$r('app.string.Exit_play_full_screen')替换为实际资源文件，在本示例中该资源文件的value值为"取消全屏播放"
    this.showMessage(this.currentFullScreenState
      ? this.context!.resourceManager.getStringSync($r('app.string.Play_full_screen').id)
      : this.context!.resourceManager.getStringSync($r('app.string.Exit_play_full_screen').id));
  };

  togglePlayAndPause(): void {
    this.isPlaying = !this.isPlaying;
    if (!this.isPlaying) {
      this.stopNormalPlayTimer();
    } else {
      // 重新启动
      this.startNormalPlayTimer();
    };
    // 请将$r('app.string.stop_playing')替换为实际资源文件，在本示例中该资源文件的value值为"暂停播放"
    // 请将$r('app.string.Continue_playing')替换为实际资源文件，在本示例中该资源文件的value值为"继续播放"
    this.showMessage(this.isPlaying
      ? this.context!.resourceManager.getStringSync($r('app.string.stop_playing').id)
      : this.context!.resourceManager.getStringSync($r('app.string.Continue_playing').id));
  };

  doFastForward(start: boolean): void {
    if (!start) { // 停止快进，恢复正常播放
      this.stopFastForwardTimer();
      this.startNormalPlayTimer();
      // 请将$r('app.string.Cancel_FastForwarding')替换为实际资源文件，在本示例中该资源文件的value值为"取消快进"
      this.showMessage(
        this.context!.resourceManager.getStringSync($r('app.string.Cancel_FastForwarding').id));
      return;
    };

    this.stopNormalPlayTimer();
    this.startFastForwardTimer();
    // 请将$r('app.string.Start_FastForwarding')替换为实际资源文件，在本示例中该资源文件的value值为"开始快进"
    this.showMessage(
      this.context!.resourceManager.getStringSync($r('app.string.Start_FastForwarding').id));
  };

  updateBrightness(start: boolean, event: BaseGestureEvent): void {
    let newY = event.fingerList[0].localY;
    if (start) {
      this.currentPosY = newY;
      // 请将$r('app.string.Start_adjusting_brightness')替换为实际资源文件，在本示例中该资源文件的value值为"开始调整 亮度"
      this.showMessage(this.context!.resourceManager
        .getStringSync($r('app.string.Start_adjusting_brightness').id));
      return;
    };
    let offsetY = newY - this.currentPosY;
    if (Math.abs(offsetY) > 10) {
      // 请将$r('app.string.Reduce_brightness')替换为实际资源文件，在本示例中该资源文件的value值为"降低亮度"
      // 请将$r('app.string.Increase_brightness')替换为实际资源文件，在本示例中该资源文件的value值为"提高亮度"
      this.showMessage((offsetY > 0)
        ? this.context!.resourceManager.getStringSync($r('app.string.Reduce_brightness').id)
        : this.context!.resourceManager.getStringSync($r('app.string.Increase_brightness').id))
      this.currentPosY = newY;
    };
  };

  updateProgress(start: boolean, event: BaseGestureEvent): void {
    let newX = event.fingerList[0].localX;
    if (start) {
      this.currentPosX = newX;
      // 请将$r('app.string.Adjust_schedule')替换为实际资源文件，在本示例中该资源文件的value值为"开始调整 进度"
      this.showMessage(this.context!.resourceManager
        .getStringSync($r('app.string.Adjust_schedule').id));
      return;
    };
    let offsetX = newX - this.currentPosX;
    this.progress = Math.floor(this.progress + offsetX * 10000);
    this.currentPosX = newX;
  };

  build() {
    Stack({ alignContent: Alignment.Center }) {
      Column() {
        Column() {
          // 请将$r('app.string.Playback_progress')替换为实际资源文件，在本示例中该资源文件的value值为"播放进度"
          Text(this.context!.resourceManager.getStringSync($r('app.string.Playback_progress').id) + this.progress)
        }
        .width('100%').height('90%')

        Flex({ alignItems: ItemAlign.Center, justifyContent: FlexAlign.SpaceBetween }) {
          Slider({
            value: this.progress,
            min: 0,
            max: this.total,
            style: SliderStyle.OutSet
          })
            .onChange((value: number, mode: SliderChangeMode) => {
              this.progress = value;
            })
            .id('progress_layer')
            .onTouchTestDone((event, allRecognizers: Array<GestureRecognizer>) => {
              for (let i = 0; i < allRecognizers.length; i++) {
                let recognizer = allRecognizers[i];
                let inspectorInfo = recognizer.getEventTargetInfo().getId();
                if (inspectorInfo !== 'progress_layer') {
                  // 用户操作到进度条区域时，禁用掉所有非progress_layer上的手势
                  recognizer.preventBegin();
                };
              };
            })
            .margin({ left: 5 })
            .trackColor(Color.Blue)
            .blockColor(Color.Gray)
            .selectedColor(Color.White)
            .trackThickness(2)
            .flexShrink(1)
            .flexGrow(1)
        }
        .flexGrow(1)
        .flexShrink(1)
        .id('id_progress_view')
      }
    }
    .id('video_layer')
    .backgroundColor('#E0E0E0')
    .gesture(
      GestureGroup(GestureMode.Exclusive,
        PanGesture({ direction: PanDirection.Vertical, distance: 10 })
          .tag('pan_for_brightness_control')
          .onActionStart((event) => {
            this.updateBrightness(true, event);
          })
          .onActionUpdate((event) => {
            this.updateBrightness(false, event);
          }),
        PanGesture({ direction: PanDirection.Horizontal, distance: 10 })
          .tag('pan_for_play_progress_control')
          .onActionStart((event) => {
            this.updateProgress(true, event);
          })
          .onActionUpdate((event) => {
            this.updateProgress(false, event);
          }),

        LongPressGesture()
          .tag('long_press_for_fast_forward_control')
          .onAction(() => {
            this.doFastForward(true); // 开始快进
          })
          .onActionEnd(() => {
            this.doFastForward(false); // 停止快进
          })
          .onActionCancel(() => {
            this.doFastForward(false);
          }),

        TapGesture({ count: 2 })
          .tag('double_tap_on_video')
          .onAction(() => {
            this.toggleFullScreenState();
          }),

        TapGesture()
          .tag('single_tap_on_video')
          .onAction(() => {
            this.togglePlayAndPause();
          })
      )
    )
    .width(this.currentWidth)
    .height(this.currentHeight)
  }
}

// [End gesture_recognition]