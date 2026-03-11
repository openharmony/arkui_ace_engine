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

@Entry
@Component
struct VideoErrorComponent {
  @State videoSrc: string = "video.mp4"; // 传入不存在的视频资源路径。
  @State isAutoPlay: boolean = false;
  @State showControls: boolean = true;
  @State showFirstFrame: boolean = false;
  controller: VideoController = new VideoController();
  @State errorMessage: string = "";

  build() {
    Column() {
      Video({
        src: this.videoSrc,
        controller: this.controller,
      })
        .width(200)
        .height(120)
        .margin(5)
        .autoPlay(this.isAutoPlay)
        .controls(this.showControls)
        .onError((err) => {
          // 通过onError事件获取错误码，code为错误码，message为错误信息。
          console.error(`code is ${err.code}, message is ${err.message}`);
          this.errorMessage = `code is ${err.code}, message is ${err.message}`;
        })
      // 传入不存在的视频资源路径，预期："code is 103602, message is Not a valid source"。
      Text(this.errorMessage)
    }
    .width("100%")
    .height("100%")
    .backgroundColor('rgb(213,213,213)')
  }
}