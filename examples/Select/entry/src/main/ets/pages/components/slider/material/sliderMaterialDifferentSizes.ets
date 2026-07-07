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

import { uiMaterial } from '@kit.ArkUI';

@Builder
export function SliderMaterialDifferentSizesBuilder(name: string, param: Object) {
  SliderMaterialDifferentSizes()
}

@Entry
@Component
struct SliderMaterialDifferentSizes {
  pathStack: NavPathStack = new NavPathStack()

  @State sliderValue: number = 40;
  @State blockType: SliderBlockType = SliderBlockType.DEFAULT;
  @State blockTypeIndex: number = 0;
  @State blockSizeIndex: number = 0;
  @State materialIndex: number = 0;
  @State materialType: uiMaterial.Material | undefined = undefined;
  @State widthValue: string = '100%';
  @State widthIndex: number = 0;
  @State heightValue: string = '40vp';
  @State heightIndex: number = 0;
  @State reverseValue: boolean = false;

  blockTypeArray: Array<SelectOption> = [
    { value: 'DEFAULT' },
    { value: 'IMAGE' },
    { value: 'SHAPE' }
  ]

  materialArray: Array<SelectOption> = [
    { value: 'undefined' },
    { value: 'NONE' },
    { value: 'SEMI_TRANSPARENT' }
  ]

  blockSizeArray: Array<SelectOption> = [
    { value: '默认尺寸' },
    { value: '大尺寸 40x40' },
    { value: '小尺寸 10x10' }
  ]

  widthArray: Array<SelectOption> = [
    { value: '100%' },
    { value: '200vp' },
    { value: '150vp' },
    { value: '80%' }
  ]

  heightArray: Array<SelectOption> = [
    { value: '40vp' },
    { value: '60vp' },
    { value: '20vp' },
    { value: '80vp' }
  ]

  getMaterialType(index: number): uiMaterial.Material | undefined {
    switch (index) {
      case 0:
        return undefined;
      case 1:
        return new uiMaterial.Material({ type: uiMaterial.MaterialType.NONE });
      case 2:
        return new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT });
      default:
        return undefined;
    }
  }

  getBlockSize(index: number): Size {
    switch (index) {
      case 0:
        return { width: 20, height: 20 };
      case 1:
        return { width: 40, height: 40 };
      case 2:
        return { width: 10, height: 10 };
      default:
        return { width: 20, height: 20 };
    }
  }

  getWidthValue(index: number): Length {
    switch (index) {
      case 0:
        return '100%';
      case 1:
        return 200;
      case 2:
        return 150;
      case 3:
        return '80%';
      default:
        return '100%';
    }
  }

  getHeightValue(index: number): Length {
    switch (index) {
      case 0:
        return 40;
      case 1:
        return 60;
      case 2:
        return 20;
      case 3:
        return 80;
      default:
        return 40;
    }
  }

  build() {
    NavDestination() {
      Column() {
        Scroll() {
          Column({ space: 12 }) {
            Text('配置面板')
              .fontSize(16)
              .fontWeight(FontWeight.Bold)
              .margin({ top: 10, bottom: 10 })

            Row() {
              Text('systemMaterial:')
                .fontSize(14)
                .width('40%')
              Select(this.materialArray)
                .value(this.materialArray[this.materialIndex].value)
                .selected(this.materialIndex)
                .width('60%')
                .onSelect((index: number) => {
                  this.materialIndex = index;
                  this.materialType = this.getMaterialType(index);
                })
            }
            .width('100%')

            Row() {
              Text('blockType:')
                .fontSize(14)
                .width('40%')
              Select(this.blockTypeArray)
                .value(this.blockTypeArray[this.blockTypeIndex].value)
                .selected(this.blockTypeIndex)
                .width('60%')
                .onSelect((index: number) => {
                  this.blockTypeIndex = index;
                  this.blockType = index === 0 ? SliderBlockType.DEFAULT :
                    index === 1 ? SliderBlockType.IMAGE : SliderBlockType.SHAPE;
                })
            }
            .width('100%')

            Row() {
              Text('blockSize:')
                .fontSize(14)
                .width('40%')
              Select(this.blockSizeArray)
                .value(this.blockSizeArray[this.blockSizeIndex].value)
                .selected(this.blockSizeIndex)
                .width('60%')
                .onSelect((index: number) => {
                  this.blockSizeIndex = index;
                })
            }
            .width('100%')

            Row() {
              Text('width:')
                .fontSize(14)
                .width('40%')
              Select(this.widthArray)
                .value(this.widthArray[this.widthIndex].value)
                .selected(this.widthIndex)
                .width('60%')
                .onSelect((index: number) => {
                  this.widthIndex = index;
                })
            }
            .width('100%')

            Row() {
              Text('height:')
                .fontSize(14)
                .width('40%')
              Select(this.heightArray)
                .value(this.heightArray[this.heightIndex].value)
                .selected(this.heightIndex)
                .width('60%')
                .onSelect((index: number) => {
                  this.heightIndex = index;
                })
            }
            .width('100%')

            Row() {
              Text('reverse:')
                .fontSize(14)
                .width('40%')
              Toggle({ type: ToggleType.Switch, isOn: this.reverseValue })
                .onChange((isOn: boolean) => {
                  this.reverseValue = isOn;
                })
            }
            .width('100%')

            Divider()
              .margin({ top: 10, bottom: 10 })

            Text('Value值控制')
              .fontSize(16)
              .fontWeight(FontWeight.Bold)
              .margin({ top: 10, bottom: 10 })

            Row() {
              Text('当前值: ' + this.sliderValue.toFixed(0))
                .fontSize(14)
                .fontWeight(FontWeight.Bold)
                .fontColor(Color.Blue)
            }
            .width('100%')

            Text('正常值测试 (min=0, max=100)')
              .fontSize(12)
              .fontColor(0x666666)
              .margin({ top: 8 })

            Row({ space: 10 }) {
              Button('设为 0')
                .fontSize(12)
                .width(80)
                .onClick(() => {
                  this.sliderValue = 0;
                })
              Button('设为 50')
                .fontSize(12)
                .width(80)
                .onClick(() => {
                  this.sliderValue = 50;
                })
              Button('设为 100')
                .fontSize(12)
                .width(80)
                .onClick(() => {
                  this.sliderValue = 100;
                })
            }
            .width('100%')

            Text('异常值测试')
              .fontSize(12)
              .fontColor(0x666666)
              .margin({ top: 8 })

            Row({ space: 10 }) {
              Button('设为 -10')
                .fontSize(12)
                .width(80)
                .backgroundColor(Color.Red)
                .onClick(() => {
                  this.sliderValue = -10;
                })
              Button('设为 150')
                .fontSize(12)
                .width(80)
                .backgroundColor(Color.Red)
                .onClick(() => {
                  this.sliderValue = 150;
                })
            }
            .width('100%')

            Divider()
              .margin({ top: 10, bottom: 10 })

            Text('横向Slider展示区域')
              .fontSize(16)
              .fontWeight(FontWeight.Bold)

            Column({ space: 20 }) {
              Text('OutSet Horizontal')
                .fontSize(12)
                .fontColor(0x666666)
              Slider({
                value: this.sliderValue,
                style: SliderStyle.OutSet,
                direction: Axis.Horizontal,
                reverse: this.reverseValue
              })
                .width(this.getWidthValue(this.widthIndex))
                .height(this.getHeightValue(this.heightIndex))
                .blockSize(this.getBlockSize(this.blockSizeIndex))
                .blockStyle({
                  type: this.blockType,
                  image: this.blockType === SliderBlockType.IMAGE ? $r('sys.media.ohos_app_icon') : undefined,
                  shape: this.blockType === SliderBlockType.SHAPE ?
                    new Path({ commands: 'M60 60 M30 30 L15 56 L45 56 Z' }) : undefined
                })
                .systemMaterial(this.materialType)
                .onChange((value: number) => {
                  this.sliderValue = value;
                })

              Text('InSet Horizontal')
                .fontSize(12)
                .fontColor(0x666666)
              Slider({
                value: this.sliderValue,
                style: SliderStyle.InSet,
                direction: Axis.Horizontal,
                reverse: this.reverseValue
              })
                .width(this.getWidthValue(this.widthIndex))
                .height(this.getHeightValue(this.heightIndex))
                .blockSize(this.getBlockSize(this.blockSizeIndex))
                .blockStyle({
                  type: this.blockType,
                  image: this.blockType === SliderBlockType.IMAGE ? $r('sys.media.ohos_app_icon') : undefined,
                  shape: this.blockType === SliderBlockType.SHAPE ?
                    new Path({ commands: 'M60 60 M30 30 L15 56 L45 56 Z' }) : undefined
                })
                .systemMaterial(this.materialType)
                .onChange((value: number) => {
                  this.sliderValue = value;
                })

              Text('NONE Horizontal')
                .fontSize(12)
                .fontColor(0x666666)
              Slider({
                value: this.sliderValue,
                style: SliderStyle.NONE,
                direction: Axis.Horizontal,
                reverse: this.reverseValue
              })
                .width(this.getWidthValue(this.widthIndex))
                .height(this.getHeightValue(this.heightIndex))
                .blockSize(this.getBlockSize(this.blockSizeIndex))
                .blockStyle({
                  type: this.blockType,
                  image: this.blockType === SliderBlockType.IMAGE ? $r('sys.media.ohos_app_icon') : undefined,
                  shape: this.blockType === SliderBlockType.SHAPE ?
                    new Path({ commands: 'M60 60 M30 30 L15 56 L45 56 Z' }) : undefined
                })
                .systemMaterial(this.materialType)
                .onChange((value: number) => {
                  this.sliderValue = value;
                })
            }
            .width('100%')
            .padding({ left: 20, right: 20, bottom: 20 })
            .backgroundColor(Color.Gray)
            .borderRadius(8)

            Divider()
              .margin({ top: 10, bottom: 10 })

            Text('竖向Slider展示区域')
              .fontSize(16)
              .fontWeight(FontWeight.Bold)

            Row({ space: 30 }) {
              Column({ space: 10 }) {
                Text('OutSet Vertical')
                  .fontSize(12)
                  .fontColor(0x666666)
                Slider({
                  value: this.sliderValue,
                  style: SliderStyle.OutSet,
                  direction: Axis.Vertical,
                  reverse: this.reverseValue
                })
                  .width(this.getHeightValue(this.heightIndex))
                  .height(this.getWidthValue(this.widthIndex))
                  .blockSize(this.getBlockSize(this.blockSizeIndex))
                  .blockStyle({
                    type: this.blockType,
                    image: this.blockType === SliderBlockType.IMAGE ? $r('sys.media.ohos_app_icon') : undefined,
                    shape: this.blockType === SliderBlockType.SHAPE ?
                      new Path({ commands: 'M60 60 M30 30 L15 56 L45 56 Z' }) : undefined
                  })
                  .systemMaterial(this.materialType)
                  .onChange((value: number) => {
                    this.sliderValue = value;
                  })
              }

              Column({ space: 10 }) {
                Text('InSet Vertical')
                  .fontSize(12)
                  .fontColor(0x666666)
                Slider({
                  value: this.sliderValue,
                  style: SliderStyle.InSet,
                  direction: Axis.Vertical,
                  reverse: this.reverseValue
                })
                  .width(this.getHeightValue(this.heightIndex))
                  .height(this.getWidthValue(this.widthIndex))
                  .blockSize(this.getBlockSize(this.blockSizeIndex))
                  .blockStyle({
                    type: this.blockType,
                    image: this.blockType === SliderBlockType.IMAGE ? $r('sys.media.ohos_app_icon') : undefined,
                    shape: this.blockType === SliderBlockType.SHAPE ?
                      new Path({ commands: 'M60 60 M30 30 L15 56 L45 56 Z' }) : undefined
                  })
                  .systemMaterial(this.materialType)
                  .onChange((value: number) => {
                    this.sliderValue = value;
                  })
              }

              Column({ space: 10 }) {
                Text('NONE Vertical')
                  .fontSize(12)
                  .fontColor(0x666666)
                Slider({
                  value: this.sliderValue,
                  style: SliderStyle.NONE,
                  direction: Axis.Vertical,
                  reverse: this.reverseValue
                })
                  .width(this.getHeightValue(this.heightIndex))
                  .height(this.getWidthValue(this.widthIndex))
                  .blockSize(this.getBlockSize(this.blockSizeIndex))
                  .blockStyle({
                    type: this.blockType,
                    image: this.blockType === SliderBlockType.IMAGE ? $r('sys.media.ohos_app_icon') : undefined,
                    shape: this.blockType === SliderBlockType.SHAPE ?
                      new Path({ commands: 'M60 60 M30 30 L15 56 L45 56 Z' }) : undefined
                  })
                  .systemMaterial(this.materialType)
                  .onChange((value: number) => {
                    this.sliderValue = value;
                  })
              }
            }
            .width('100%')
            .justifyContent(FlexAlign.Center)
            .padding({ left: 20, right: 20, bottom: 20, top: 20 })
            .backgroundColor('#999999')
            .borderRadius(8)
          }
          .width('100%')
          .padding(16)
        }
        .width('100%')
        .height('100%')
      }
      .width('100%')
      .height('100%')
    }
    .title('Slider不同尺寸新材质表现')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}