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
import imageGeneration from '@ohos.arkui.intelligence.imageGeneration';
import { Constants } from '../common/CommonConstants';
import { ImageOperate } from './ImageOperate';

@ComponentV2
export struct DoodleBoardArea {
  private static DEFAULT_COUNT: number = 4;
  @Param @Require imageInfoArr: Array<imageGeneration.ImageItem>;
  @Param @Require imageMatrixArr: number[][];

  private invalidImageInfo(index: number): boolean {
    if (index < 0 || index >= DoodleBoardArea.DEFAULT_COUNT) {
      return true;
    }
    return this.imageInfoArr[index].url === Constants.NOT_SELECTED_NAME;
  }

  private getImageAspectRito(index: number): number {
    let imageItem = this.imageInfoArr[index]
    if (imageItem.rect === undefined) {

      let ImageW = (imageItem.image as PixelMap)?.getImageInfoSync().size.width
      let ImageH = (imageItem.image as PixelMap)?.getImageInfoSync().size.height
      if (ImageW !== undefined) {
        return ImageW / ImageH
      }
      return 1;
    }
    let left: number = this.imageInfoArr[index].rect?.left as number;
    let right: number = this.imageInfoArr[index].rect?.right as number;
    let top: number = this.imageInfoArr[index].rect?.top as number;
    let bottom: number = this.imageInfoArr[index].rect?.bottom as number;
    return (right - left) / (bottom - top);
  }

  private getImageWidth(index: number): number | string {
    if (this.imageInfoArr[index].rect === undefined) {
      return '100%';
    }
    let left: number = this.imageInfoArr[index].rect?.left as number;
    let right: number = this.imageInfoArr[index].rect?.right as number;
    return this.getUIContext().px2vp(right - left);
  }

  private setMatrix(index: number, imageMatrixArr: number[]) {
    this.imageMatrixArr[index] = imageMatrixArr
  }

  @Builder
  ImageBuilder(index: number) {
    if (this.imageInfoArr[index].image) {
      ImageOperate({
        pixelMap: this.imageInfoArr[index].image ?? ImageContent.EMPTY,
        imageAspectRito: this.getImageAspectRito(index),
        preTransform: this.imageMatrixArr[index],
        imageWidth: this.getImageWidth(index),
        setMatrixCallback: (imageMatrixArr: number[]) => {
          this.setMatrix(index, imageMatrixArr)
        }
      })
        .position({ x: 0, y: 0 })
        .zIndex(this.imageInfoArr[index].zIndex ?? undefined)
        .hitTestBehavior(HitTestMode.Transparent)
    }
  }

  build() {
    Stack() {
      Stack() {
        //Image($r('app.media.doodle_board_light'))
        Image('xx')
          .scale({ x: 1.36, y: 1.36 })
          .width('100%')
          .height('100%')
          .draggable(false)
          //.borderRadius($r('app.float.doodle_board_border_radius'))
          .borderRadius(24)
          .hitTestBehavior(HitTestMode.Transparent)

        Column()
          .width('100%')
          .height('100%')
          .draggable(false)
          .hitTestBehavior(HitTestMode.Transparent)
          .backgroundColor(Color.White)
          .blur(25)
          .borderRadius(24)
        //Image($r('app.media.home_background'))
        Image('xx')
          .width('100%')
          .height('100%')
          //.borderRadius($r('app.float.doodle_board_border_radius'))
          .borderRadius(24)
          .padding(1)
          .draggable(false)
          .hitTestBehavior(HitTestMode.Transparent)
      }
      .borderRadius(24)
      .width('100%')
      .height('100%')

      Column() {
        Stack() {
          if (this.invalidImageInfo(0)) {
            Stack() {
              Column() {
                //Image($r('app.media.doodble_pen'))
                Image('xx')
                  .width(160)
                  .height(160)
                  .draggable(false)
                Row() {
                  Text("添加图片或涂鸦进行创作")
                    .blendMode(BlendMode.DST_IN, BlendApplyType.OFFSCREEN)
                    .fontFamily("HarmonyHeiTi")
                    .fontSize(16)
                    .fontWeight(500)
                    .lineHeight(19)
                    .textAlign(TextAlign.Center)
                }
                .linearGradient({
                  direction: GradientDirection.Left,
                  colors: [['#64DCFF', 0.0], ['#8999FF', 1]]
                })
                .blendMode(BlendMode.SRC_OVER, BlendApplyType.OFFSCREEN)
                .margin({ top: 8 })
              }
              .justifyContent(FlexAlign.Center)
              .width('100%')
              .height('100%')
            }
            .alignContent(Alignment.Center)
            .width('100%')
            .height('100%')
          }
          ForEach(this.imageInfoArr, (item: imageGeneration.ImageItem, index: number) => {
            this.ImageBuilder(index);
          }, (item: imageGeneration.ImageItem, index: number) => '' + index + (item?.url ?? 'imageGeneration'))
        }
      }
      .width(386)
      .height(386)
      .borderRadius(24)
      .clip(true)
    }
    .width(386)
    .height(386)
    .borderRadius(24)
    .borderWidth(2)// todo: delete here
    .borderColor('#33000000')
  }
}