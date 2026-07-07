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
export function SliderMaterialThreeStylesBuilder(name: string, param: Object) {
  SliderMaterialThreeStyles()
}

@Entry
@Component
struct SliderMaterialThreeStyles {
  pathStack: NavPathStack = new NavPathStack()

  @State sliderValue: number = 40;
  @State blockType: SliderBlockType = SliderBlockType.DEFAULT;
  @State blockTypeIndex: number = 0;
  @State trackColorIndex: number = 0;
  @State selectedColorIndex: number = 0;
  @State blockSizeIndex: number = 0;
  @State materialIndex: number = 0;
  @State materialType: uiMaterial.Material | undefined = undefined;

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

  trackColorArray: Array<SelectOption> = [
    { value: '默认灰色' },
    { value: '红色' },
    { value: '蓝色' },
    { value: '绿色' }
  ]

  selectedColorArray: Array<SelectOption> = [
    { value: '默认蓝色' },
    { value: '红色' },
    { value: '橙色' },
    { value: '紫色' }
  ]

  blockSizeArray: Array<SelectOption> = [
    { value: '默认尺寸' },
    { value: '大尺寸 40x40' },
    { value: '小尺寸 10x10' }
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

  getTrackColor(index: number): ResourceColor {
    switch (index) {
      case 0:
        return '#CCCCCC';
      case 1:
        return Color.Red;
      case 2:
        return Color.Blue;
      case 3:
        return Color.Green;
      default:
        return '#CCCCCC';
    }
  }

  getSelectedColor(index: number): ResourceColor {
    switch (index) {
      case 0:
        return '#007DFF';
      case 1:
        return Color.Red;
      case 2:
        return '#FF9500';
      case 3:
        return '#AF52DE';
      default:
        return '#007DFF';
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
              Text('trackColor:')
                .fontSize(14)
                .width('40%')
              Select(this.trackColorArray)
                .value(this.trackColorArray[this.trackColorIndex].value)
                .selected(this.trackColorIndex)
                .width('60%')
                .onSelect((index: number) => {
                  this.trackColorIndex = index;
                })
            }
            .width('100%')

            Row() {
              Text('selectedColor:')
                .fontSize(14)
                .width('40%')
              Select(this.selectedColorArray)
                .value(this.selectedColorArray[this.selectedColorIndex].value)
                .selected(this.selectedColorIndex)
                .width('60%')
                .onSelect((index: number) => {
                  this.selectedColorIndex = index;
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

            Text('Slider展示区域')
              .fontSize(16)
              .fontWeight(FontWeight.Bold)

            Column({ space: 20 }) {
              Text('OutSet Slider')
                .fontSize(12)
                .fontColor(0x666666)
              Slider({
                value: this.sliderValue,
                style: SliderStyle.OutSet
              })
                .blockSize(this.getBlockSize(this.blockSizeIndex))
                .trackColor(this.getTrackColor(this.trackColorIndex))
                .selectedColor(this.getSelectedColor(this.selectedColorIndex))
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

              Text('InSet Slider')
                .fontSize(12)
                .fontColor(0x666666)
              Slider({
                value: this.sliderValue,
                style: SliderStyle.InSet
              })
                .blockSize(this.getBlockSize(this.blockSizeIndex))
                .trackColor(this.getTrackColor(this.trackColorIndex))
                .selectedColor(this.getSelectedColor(this.selectedColorIndex))
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

              Text('NONE Slider')
                .fontSize(12)
                .fontColor(0x666666)
              Slider({
                value: this.sliderValue,
                style: SliderStyle.NONE
              })
                .blockSize(this.getBlockSize(this.blockSizeIndex))
                .trackColor(this.getTrackColor(this.trackColorIndex))
                .selectedColor(this.getSelectedColor(this.selectedColorIndex))
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
    .title('Slider三种类型+新材质')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}