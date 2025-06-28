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

/**
 * Enable or disable image analysis functionality by setting the enableAnalyzer attribute of the Image
 * component to control whether the image content is parsed and processed.
 */
import image from '@ohos.multimedia.image'
import common from '@ohos.app.ability.common';


class MyDataSource implements IDataSource {
  private list: (image.PixelMap | undefined | ResourceStr)[] = []

  constructor(list: (image.PixelMap | undefined | ResourceStr)[]) {
    this.list = list
  }

  totalCount(): number {
    return this.list.length
  }

  getData(index: number): image.PixelMap | undefined | ResourceStr {
    return this.list[index]
  }

  registerDataChangeListener(listener: DataChangeListener): void {
  }

  unregisterDataChangeListener() {
  }
}

@Entry
@Component
struct Test2 {
  @State enableAnalyzerValue: boolean = true
  @State pix01: image.PixelMap | undefined = undefined
  @State srcArr: (image.PixelMap | undefined | ResourceStr)[] =
    [$r('app.media.font2'), $r('app.media.font1'), $r('app.media.font3'), $r('app.media.logo'), $r('app.media.font4')]
  @State textArr: string[] = ['PNG', 'JPG', 'BMP', 'SVG', 'GIF']
  private swiperController: SwiperController = new SwiperController()
  private data: MyDataSource = new MyDataSource([])
  @State text: string = 'PNG'
  @State srcArr2: (image.PixelMap | undefined | ResourceStr)[] =
    [$r('app.media.font2'), $r('app.media.font1'), $r('app.media.font3'), $r('app.media.logo'), $r('app.media.font4')]
  @State srcIndex: number = 0
  @State textArr2: string[] = ['PNG', 'JPG', 'BMP', 'SVG', 'GIF']

  async aboutToAppear() {
    let list: (image.PixelMap | undefined | ResourceStr)[] = []
    for (let i = 0; i < 1; i++) {
      list.push(this.srcArr[i]);
    }
    this.data = new MyDataSource(list)

    let context = getContext(this) as common.UIAbilityContext
    this.pix01 = context.resourceManager.getDrawableDescriptor($r('app.media.font1').id).getPixelMap()
  }

  build() {
    Column({ space: 20 }) {
      Text('2 enableAnalyzer属性测试-纯文本')

      Column({ space: 3 }) {
        Button('enableAnalyzer设置为true')
          .onClick(() => {
            this.enableAnalyzerValue = true
          })

        Button('enableAnalyzer设置为false')
          .onClick(() => {
            this.enableAnalyzerValue = false
          })
      }

      Scroll() {
        Column({ space: 20 }) {
          Image($r('app.media.v_mirror'))
            .width(100)
            .height(100)
            .orientation(ImageRotateOrientation.AUTO)
            .objectFit(ImageFit.Cover)
            .margin(5)
          Image($r('app.media.font2'))
            .width('70%').height(200).enableAnalyzer(this.enableAnalyzerValue)
            .overlay()
          Text(this.text)
        }.width('100%')
      }.height('80%')

    }.width('100%').height('100%')

  }
}