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

/*用例描述
 1、本用例通过给Scroll设置自由滚动和手势缩放
*/

@Entry
@Component
struct ScrollZoomExample {
  @State maxScale: number | undefined = 2;
  @State minScale: number | undefined = 1;
  @State enableBounces: boolean | undefined = true;
  @State currScale: number = 1;

  build() {
    Column() {
      Column() {
        Row() {
          Text('Max')

          Button('4').onClick(() => {
            this.maxScale = 4;
          })

          Button('-1').onClick(() => {
            this.maxScale = -1;
          })

          Button('0').onClick(() => {
            this.maxScale = 0;
          })

          Button('undefined').onClick(() => {
            this.maxScale = undefined;
          })

          Button('1').onClick(() => {
            this.maxScale = 1;
          })
        }

        Row() {
          Text('Min')

          Button('0.5').onClick(() => {
            this.minScale = 0.5;
          })

          Button('-1').onClick(() => {
            this.minScale = -1;
          })

          Button('0').onClick(() => {
            this.minScale = 0;
          })

          Button('undefined').onClick(() => {
            this.minScale = undefined;
          })

          Button('1').onClick(() => {
            this.minScale = 1;
          })
        }

        Row() {
          Text('Bounces')

          Button('true').onClick(() => {
            this.enableBounces = true;
          })

          Button('false').onClick(() => {
            this.enableBounces = false;
          })

          Button('undefined').onClick(() => {
            this.enableBounces = undefined;
          })
        }
      }

      Scroll() {
        Image($r('app.media.startIcon'))
      }
      .height(400)
      .scrollable(ScrollDirection.FREE)
      .minZoomScale(this.minScale)
      .maxZoomScale(this.maxScale)
      .zoomScale(this.currScale!!)
      .enableBouncesZoom(this.enableBounces)
      .onDidZoom((scale: number) => {
        console.info(`onDidZoom:${scale}`);
      })
      .onZoomStart(() => {
        console.info('onZoomStart');
      })
      .onZoomStop(() => {
        console.info('onZoomStop');
      })
    }.width('100%').height('100%')
  }
}
