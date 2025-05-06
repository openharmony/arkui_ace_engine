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
import { LengthMetrics, LengthMetricsUnit } from '@kit.ArkUI';

/**
 * 验证Image的基础功能
 */
@Entry
@Component
struct ImageExample {
  @State imageSource: ResourceStr | undefined = undefined;
  @State imageFits: ImageFit[] = [];
  @State imageFitIndex: number = 0;

  aboutToAppear(): void {
    this.pushDataToImageFits();
  }

  private pushDataToImageFits() {
    this.imageFits.push(ImageFit.Auto);
    this.imageFits.push(ImageFit.Fill);
    this.imageFits.push(ImageFit.Contain);
    this.imageFits.push(ImageFit.Cover);
    this.imageFits.push(ImageFit.ScaleDown);
    this.imageFits.push(ImageFit.CENTER);
    this.imageFits.push(ImageFit.START);
    this.imageFits.push(ImageFit.TOP_START);
    this.imageFits.push(ImageFit.CENTER);
    this.imageFits.push(ImageFit.Auto);
    this.imageFits.push(ImageFit.BOTTOM_START);
    this.imageFits.push(ImageFit.BOTTOM_END);
    this.imageFits.push(ImageFit.END);
    this.imageFits.push(ImageFit.Auto);
    this.imageFits.push(ImageFit.Fill);
    this.imageFits.push(ImageFit.END);
    this.imageFits.push(ImageFit.None);
  }

  private changDataByImageFit() {
    this.imageFitIndex++;
    if (this.imageFitIndex >= this.imageFits.length) {
      this.imageFitIndex = 0;
    }
  }

  build() {
    Column() {
      Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Start }) {
        Row() {
          // 加载png格式图片
          Image($r('app.media.sky'))
            .width(120)
            .height(140)
            .margin(17)
            .overlay('png', { align: Alignment.Bottom, offset: { x: 0, y: 20 } })
            .border({
              width: 2,
              color: Color.Pink,
              radius: 8,
              dashGap: LengthMetrics.px(5)
            })
            .objectFit(this.imageFits[this.imageFitIndex])
          Button('change imageFitIndex')
            .onClick(() => {
              this.changDataByImageFit()
              console.log(`imageFitIndex: ${this.imageFitIndex}`);
            })


          // 加载base64格式图片
          Image($r('app.media.sky'))
            .width(110)
            .height(110)
            .margin(15)
            .overlay('gif', { align: Alignment.Bottom, offset: { x: 0, y: 20 } })
            .border({ width: 2, color: Color.Pink })
            .objectFit(ImageFit.BOTTOM_START)
        }
      }
    }.height(320).width(360).padding({ right: 10, top: 10 })
  }
}
