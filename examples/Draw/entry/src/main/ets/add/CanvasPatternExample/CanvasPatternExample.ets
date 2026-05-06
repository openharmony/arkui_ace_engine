/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

@Entry
@Component
struct CanvasPatternExample {
  private settings: RenderingContextSettings = new RenderingContextSettings(true);
  private context: CanvasRenderingContext2D = new CanvasRenderingContext2D(this.settings);
  private matrix: Matrix2D = new Matrix2D();
  private img: ImageBitmap = new ImageBitmap("../../../resources/rawfile/pattern.jpg");
  private pattern: CanvasPattern | null = null;

  build() {
    Column() {
      Button("Click to set transform")
        .onClick(() => {
          this.matrix.scaleY = 1
          this.matrix.scaleX = 1
          this.matrix.translateX = 50
          this.matrix.translateY = 200
          if (this.pattern) {
            this.pattern.setTransform(this.matrix)
          }
          this.context.fillRect(0, 0, 480, 720)
        })
        .width("45%")
        .margin("5px")
      Canvas(this.context)
        .width('100%')
        .height('80%')
        .backgroundColor('#FFFFFF')
        .onReady(() => {
          this.pattern = this.context.createPattern(this.img, 'no-repeat')
          this.matrix.scaleY = 0.5
          this.matrix.scaleX = 0.5
          this.matrix.translateX = 50
          this.matrix.translateY = 50
          if (this.pattern) {
            this.context.fillStyle = this.pattern
            this.pattern.setTransform(this.matrix)
          }
          this.context.fillRect(0, 0, 480, 720)
        })
    }
    .width('100%')
    .height('100%')
  }
}