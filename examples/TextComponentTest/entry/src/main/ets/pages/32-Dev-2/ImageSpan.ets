/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { drawing, common2D } from '@kit.ArkGraphics2D';

interface ImageCompleteData {
  width: number,
  height: number
}

@Entry
@Component
struct ImageSpan18 {
  @State widthArr: number = 300
  @State heightArr: number = 300
  @State src: ResourceStr | ImageContent = $r('app.media.81')
  @State srcArray: (ResourceStr | ImageContent)[] = [
    ImageContent.EMPTY, $r('app.media.22'), $r('app.media.81'), $r('app.media.bmp'), $r('app.media.gif'),
    $r('app.media.svg'), $r('app.media.webp'), $r('app.media.heif'), ''
  ]
  @State srcArrayStr: string[] = ['EMPTY', 'jpg', 'png', 'bmp', 'gif', 'svg', 'webp', 'heif', '空']
  @State srcNum: number = 1;
  @State altSrc: ResourceStr[] = [$r('app.media.startIcon'), $r('app.media.81')];
  @State altNum: number = 0
  @State show: boolean = false
  @State obscuredAdd: boolean = false
  @State paddingAdd: number = 0
  @State renderMode: ImageRenderMode = ImageRenderMode.Original
  @State objectFitIndex: number = 0
  @State objectFitStr: string[] =
    ['Cover', 'Contain', 'Auto', 'Fill', 'ScaleDown', 'None', 'TOP_START', 'TOP', 'TOP_END', 'START', 'CENTER', 'END',
      'BOTTOM_START', 'BOTTOM', 'BOTTOM_END']
  @State objectFit: ImageFit[] =
    [ImageFit.Cover, ImageFit.Contain, ImageFit.Auto, ImageFit.Fill, ImageFit.ScaleDown, ImageFit.None,
      ImageFit.TOP_START, ImageFit.TOP, ImageFit.TOP_END, ImageFit.START, ImageFit.CENTER, ImageFit.END,
      ImageFit.BOTTOM_START, ImageFit.BOTTOM, ImageFit.BOTTOM_END]
  @State objectRepeat: ImageRepeat[] = [ImageRepeat.NoRepeat, ImageRepeat.X, ImageRepeat.Y, ImageRepeat.XY]
  @State objectRepeatStr: string[] = ['NoRepeat', 'X', 'Y', 'XY']
  @State objectRepeatIndex: number = 0
  @State interpolation: ImageInterpolation[] =
    [ImageInterpolation.Low, ImageInterpolation.None, ImageInterpolation.Medium, ImageInterpolation.High]
  @State interpolationStr: string[] = ['Low', 'None', 'Medium', 'High']
  @State interpolationIndex: number = 0
  @State text: string = ''
  @State text2: string = ''
  @State text3: string = ''
  private color: common2D.Color = {
    alpha: 255,
    red: 255,
    green: 0,
    blue: 0
  };
  @State drawingColorFilterFirst: ColorFilter | undefined = undefined
  @State con: TextEditControllerEx | undefined = undefined

  build() {
    Column() {

      Text(this.text + '\n' + this.text2 + '\n' + this.text3)

      if (this.show) {
        Image(this.srcArray[0])
          .copyOption(CopyOptions.InApp)
          .objectFit(ImageFit.Contain)
          .alt(this.altSrc[this.altNum])
          .interpolation(this.interpolation[this.interpolationIndex])
          .borderWidth(1)
          .objectFit(this.objectFit[this.objectFitIndex])
          .objectRepeat(this.objectRepeat[this.objectRepeatIndex])
          .renderMode(this.renderMode)
          .draggable(true)
          .colorFilter(this.drawingColorFilterFirst)
          .fillColor(Color.Pink)
          .enableAnalyzer(true)
          .padding(this.paddingAdd)
          .onClick(() => {
            this.srcNum = 0;
          })
          .onFinish(() => {
            console.info('finish')
            this.text2 = 'onFinish'
          })
          .onComplete((msg: ImageCompleteData) => {
            this.text = 'onComplete width:' + msg.width + ' height:' + msg.height
          })
          .onError(() => {
            this.text3 = 'onError'
          })
          .dynamicRangeMode(DynamicRangeMode.HIGH)
      } else if (this.show == false && this.obscuredAdd == false) {
        Image(this.srcArray[this.srcNum])
          .width(this.widthArr)
          .height(this.heightArr)
          .copyOption(CopyOptions.InApp)
          .objectFit(ImageFit.Contain)
          .alt(this.altSrc[this.altNum])
          .interpolation(this.interpolation[this.interpolationIndex])
          .borderWidth(1)
          .objectFit(this.objectFit[this.objectFitIndex])
          .objectRepeat(this.objectRepeat[this.objectRepeatIndex])
          .renderMode(this.renderMode)
          .draggable(true)
          .colorFilter(this.drawingColorFilterFirst)
          .enableAnalyzer(true)
          .fillColor(Color.Pink)
          .padding(this.paddingAdd)
          .onClick(() => {
            this.srcNum = 0;
          })
          .onFinish(() => {
            console.info('finish')
            this.text2 = 'onFinish'
          })
          .onComplete((msg: ImageCompleteData) => {
            this.text = 'onComplete width:' + msg.width + ' height:' + msg.height
          })
          .onError(() => {
            this.text3 = 'onError'
          })
          .dynamicRangeMode(DynamicRangeMode.HIGH)
      } else if (this.show == false && this.obscuredAdd == true) {
        Image(this.srcArray[this.srcNum])
          .width(this.widthArr)
          .height(this.heightArr)
          .copyOption(CopyOptions.InApp)
          .objectFit(ImageFit.Contain)
          .alt(this.altSrc[this.altNum])
          .interpolation(this.interpolation[this.interpolationIndex])
          .borderWidth(1)
          .objectFit(this.objectFit[this.objectFitIndex])
          .objectRepeat(this.objectRepeat[this.objectRepeatIndex])
          .renderMode(this.renderMode)
          .draggable(true)
          .colorFilter(this.drawingColorFilterFirst)
          .enableAnalyzer(true)
          .padding(this.paddingAdd)
          .fillColor(Color.Pink)
          .obscured([ObscuredReasons.PLACEHOLDER])
          .onClick(() => {
            this.srcNum = 0;
          })
          .onFinish(() => {
            console.info('finish')
            this.text2 = 'onFinish'
          })
          .onComplete((msg: ImageCompleteData) => {
            this.text = 'onComplete width:' + msg.width + ' height:' + msg.height
          })
          .onError(() => {
            this.text3 = 'onError'
          })
          .dynamicRangeMode(DynamicRangeMode.HIGH)
      }

      Divider()

      Scroll() {
        Column() {

          Row() {
            Button('不设置宽高')
              .onClick(() => {
                this.show = true
              }).width('50%')

            Button('设置宽高')
              .onClick(() => {
                this.show = false
              }).width('50%')
          }.width('90%')

          Row() {
            Button('Src:' + this.srcArrayStr[this.srcNum])
              .onClick(() => {
                this.srcNum = (this.srcNum + 1) % this.srcArray.length;
              }).width('50%')

            Button('AltSrc')
              .onClick(() => {
                this.altNum = (this.altNum + 1) % this.altSrc.length;
              }).width('50%')
          }.width('90%')

          Row() {
            Button('padding+,' + this.paddingAdd)
              .onClick(() => {
                this.paddingAdd += 10
              }).width('50%')

            Button('padding-,' + this.paddingAdd)
              .onClick(() => {
                this.paddingAdd -= 10
              }).width('50%')
          }.width('90%')

          Row() {
            Button('不遮罩')
              .onClick(() => {
                this.obscuredAdd = false
              }).width('50%')

            Button('遮罩')
              .onClick(() => {
                this.obscuredAdd = true
              }).width('50%')
          }.width('90%')

          Row() {
            Button('renderMode.Original')
              .onClick(() => {
                this.renderMode = ImageRenderMode.Original
              }).width('50%')

            Button('renderMode.Template')
              .onClick(() => {
                this.renderMode = ImageRenderMode.Template
              }).width('50%')
          }.width('90%')

          Row() {
            Button('objectFit: ' + this.objectFitStr[this.objectFitIndex])
              .onClick(() => {
                this.objectFitIndex = (this.objectFitIndex + 1) % this.objectFit.length;
              }).width('50%')

            Button('objectRepeat: ' + this.objectRepeatStr[this.objectRepeatIndex])
              .onClick(() => {
                this.objectRepeatIndex = (this.objectRepeatIndex + 1) % this.objectRepeat.length;
              }).width('50%')
          }.width('90%')

          Row() {
            Button('interpolation: ' + this.interpolationStr[this.interpolationIndex])
              .onClick(() => {
                this.interpolationIndex = (this.interpolationIndex + 1) % this.interpolationStr.length;
              }).width('50%')

            Button('colorFilter')
              .onClick(() => {
                this.drawingColorFilterFirst =
                  drawing.ColorFilter.createBlendModeColorFilter(this.color, drawing.BlendMode.SRC_IN);
              }).width('50%')
          }.width('90%')

        }
      }.height(350)

    }
    .width('100%')
    .height('100%')
  }
}