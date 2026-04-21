/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { DurationObject , TimeObject , FullscreenObject } from './VideoExample1'

@Entry
@Component
struct VideoCreateComponent2 {
  // $rawfile('video1.mp4')、$r('app.media.startIcon')需要分别替换为开发者所需的视频、图片资源文件
  @State videoSrc: Resource = $rawfile('video1.mp4');
  @State previewUri: Resource = $r('app.media.startIcon');
  @State curRate: number = 1.0;
  @State isAutoPlay: boolean = false;
  @State showControls: boolean = true;
  @State isShortcutKeyEnabled: boolean = false;
  @State showFirstFrame: boolean = false;
  controller: VideoController = new VideoController();

  build() {
    Column() {
      Video({
        src: this.videoSrc,
        previewUri: this.previewUri, // 设置预览图
        currentProgressRate: this.curRate, // 设置播放速度
        controller: this.controller,
        posterOptions: { showFirstFrame: this.showFirstFrame } // 关闭首帧送显
      })
        .width('100%')
        .height(600)
        .autoPlay(this.isAutoPlay)
        .controls(this.showControls)
        .enableShortcutKey(this.isShortcutKeyEnabled)
        .onStart(() => {
          console.info('onStart');
        })
        .onPause(() => {
          console.info('onPause');
        })
        .onFinish(() => {
          console.info('onFinish');
        })
        .onError(() => {
          console.info('onError');
        })
        .onStop(() => {
          console.info('onStop');
        })
        .onPrepared((e?: DurationObject) => {
          if (e != undefined) {
            console.info('onPrepared is ' + e.duration);
          }
        })
        .onSeeking((e?: TimeObject) => {
          if (e != undefined) {
            console.info('onSeeking is ' + e.time);
          }
        })
        .onSeeked((e?: TimeObject) => {
          if (e != undefined) {
            console.info('onSeeked is ' + e.time);
          }
        })
        .onUpdate((e?: TimeObject) => {
          if (e != undefined) {
            console.info('onUpdate is ' + e.time);
          }
        })
        .onFullscreenChange((e?: FullscreenObject) => {
          if (e != undefined) {
            console.info('onFullscreenChange is ' + e.fullscreen);
          }
        })

        Row() {
        // $rawfile('video2.mp4')、$r('app.media.background')需要分别替换为开发者所需的视频、图片资源文件
        Button('src').onClick(() => {
          this.videoSrc = $rawfile('video2.mp4'); // 切换视频源。
        }).margin(5)
        Button('previewUri').onClick(() => {
          this.previewUri = $r('app.media.background'); // 切换视频预览海报。
        }).margin(5)
        Button('controls').onClick(() => {
          this.showControls = !this.showControls; // 切换是否显示视频控制栏
        }).margin(5)
      }

      Row() {
        Button('start').onClick(() => {
          this.controller.start(); // 开始播放
        }).margin(2)
        Button('pause').onClick(() => {
          this.controller.pause(); // 暂停播放
        }).margin(2)
        Button('stop').onClick(() => {
          this.controller.stop(); // 结束播放
        }).margin(2)
        Button('reset').onClick(() => {
          this.controller.reset(); // 重置AVPlayer
        }).margin(2)
        Button('setTime').onClick(() => {
          this.controller.setCurrentTime(10, SeekMode.Accurate); // 精准跳转到视频的10s位置
        }).margin(2)
      }

      Row() {
        Button('rate 0.75').onClick(() => {
          this.curRate = 0.75; // 0.75倍速播放
        }).margin(5)
        Button('rate 1').onClick(() => {
          this.curRate = 1.0; // 原倍速播放
        }).margin(5)
        Button('rate 2').onClick(() => {
          this.curRate = 2.0; // 2倍速播放
        }).margin(5)
      }
    }
  }
}