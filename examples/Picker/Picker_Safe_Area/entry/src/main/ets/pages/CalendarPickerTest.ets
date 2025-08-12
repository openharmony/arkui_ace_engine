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

import { Callback } from '@ohos.base'
import { LengthMetrics } from '@kit.ArkUI';

class CustomModifier implements AttributeModifier<CalendarPickerAttribute> {
  public widthValue: Length | LayoutPolicy = '';
  public heightValue: Length | LayoutPolicy = '';
  public constraintSizeValue: ConstraintSizeOptions = {};
  public aspectRatioValue: number = 0;
  public ignoresLayoutValue: Array<LayoutSafeAreaEdge> = [];

  applyNormalAttribute(instance: CalendarPickerAttribute): void {
    instance.width(this.widthValue)
    instance.height(this.heightValue)
    instance.aspectRatio(this.aspectRatioValue)
    instance.constraintSize(this.constraintSizeValue)
    instance.backgroundColor('#ffdff5d2')
    instance.ignoreLayoutSafeArea([LayoutSafeAreaType.SYSTEM], this.ignoresLayoutValue)
    instance.border({width: '1px', color: Color.Orange})
  }
}

interface pickerCategories<T> {
  id?: string,
  text: string,
  value?: T
}

@Entry
@Component
struct CalendarPickerExample {
  @State myModifier: CustomModifier = new CustomModifier();
  @State currentPicker: string = '原生设置属性Picker'
  @State isModifier: boolean = false

  // Picker属性
  @State pickerWidthHeightList: (pickerCategories<Length | LayoutPolicy>)[] = [
    {
      text: 'no value',
      value: ''
    },
    {
      text: '400px',
      value: '400px'
    },
    {
      text: '100%',
      value: '100%'
    },
    {
      text: 'matchParent',
      value: LayoutPolicy.matchParent
    },
    {
      text: 'wrapContent',
      value: LayoutPolicy.wrapContent
    },
    {
      text: 'fixAtIdealSize',
      value: LayoutPolicy.fixAtIdealSize
    },
  ];
  @State widthValue: Length | LayoutPolicy = '';
  @State heightValue: Length | LayoutPolicy = '';

  @State constraintSizeList: (pickerCategories<ConstraintSizeOptions>)[] = [
    {
      text: 'max 100px',
      value: { maxWidth: '100px', maxHeight: '100px' }
    },
    {
      text: 'max 200px',
      value: { maxWidth: '200px', maxHeight: '200px' }
    },
    {
      text: '取消',
      value: {}
    },
  ];
  @State constraintSizeValue: ConstraintSizeOptions = {};

  @State aspectRatioList: (pickerCategories<number>)[] = [
    {
      text: '无值',
      value: 0
    },
    {
      text: '2',
      value: 2
    },
  ];
  @State aspectRatioValue: number = 0;

  @State backgroundStr: string = 'backgroundColor';
  @State backType: number = 2; // 0: background.ResourceColor, 1: background.CustomBuilder, 2: backgroundColor

  @State ignoresLayoutList: (pickerCategories<Array<LayoutSafeAreaEdge>>)[] = [
    {
      text: '取消',
      value: []
    },
    {
      text: 'START',
      value: [LayoutSafeAreaEdge.START]
    },
    {
      text: 'END',
      value: [LayoutSafeAreaEdge.END]
    },
    {
      text: 'VERTICAL',
      value: [LayoutSafeAreaEdge.VERTICAL]
    },
    {
      text: 'HORIZONTAL',
      value: [LayoutSafeAreaEdge.HORIZONTAL]
    },
    {
      text: 'ALL',
      value: [LayoutSafeAreaEdge.ALL]
    },
  ];
  @State ignoresLayoutValue: Array<LayoutSafeAreaEdge> = [];

  // 父组件属性
  @State parentWidthHeightList: (pickerCategories<Length | LayoutPolicy>)[] = [
    {
      text: 'no value',
      value: ''
    },
    {
      text: '100%',
      value: '100%'
    },
    {
      text: '70%',
      value: '70%'
    },
    {
      text: '200px',
      value: '200px'
    },
    {
      text: 'wrapContent',
      value: LayoutPolicy.wrapContent
    },
  ];
  @State parentWidthValue: Length | LayoutPolicy = '';
  @State parentHeightValue: Length | LayoutPolicy = '';

  @State parentPaddingList: (pickerCategories<Length>)[] = [
    {
      text: '0',
      value: '0'
    },
    {
      text: '20px',
      value: '20px'
    },
    {
      text: '200px',
      value: '200px'
    },
    {
      text: '400px',
      value: '400px'
    },
  ];
  @State parentPaddingValue: Length = 0;

  @State parentBorderList: (pickerCategories<Length>)[] = [
    {
      text: '0',
      value: '0'
    },
    {
      text: '20px',
      value: '20px'
    },
    {
      text: '200px',
      value: '200px'
    },
    {
      text: '400px',
      value: '400px'
    },
  ];
  @State parentBorderValue: Length = 0;

  @State parentSafeAreaPaddingList: (pickerCategories<number>)[] = [
    {
      text: '0',
      value: 0
    },
    {
      text: '20px',
      value: 20
    },
    {
      text: '200px',
      value: 200
    },
    {
      text: '400px',
      value: 400
    },
  ];
  @State parentSafeAreaPaddingValue: number = 0;

  @Builder
  clickComponent(id?: string, text?: string, click?: Callback<ClickEvent>) {
    Column() {
      Button(text).fontSize(12)
    }
    .id(id)
    .onClick(click)
  }

  @Builder
  renderBackGround() {
    Column()
      .backgroundColor('#ffdff5d2')
      .width('100%')
      .height('100%')
  }

  build() {
    Column({space: 5}) {
      // 设置picker组件本身属性
      Text('picker组件属性')
      Scroll() {
        Column() {
          Text('选中一个Picker:' + this.currentPicker).width('100%')
          Row({space: 5}) {
            this.clickComponent(undefined, '原生设置属性', (event: ClickEvent) => {
              this.isModifier = false;
              this.currentPicker = '原生设置属性Picker'
            })
            this.clickComponent(undefined, 'Modifier设置属性', (event: ClickEvent) => {
              this.isModifier = true;
              this.currentPicker = 'Modifier设置属性Picker'
              this.backType = 2;
            })
          }.width('100%')

          Text('width: ' + JSON.stringify(this.widthValue)).width('100%').fontSize(12)
          Flex({wrap: FlexWrap.Wrap, alignContent: FlexAlign.Center, space: {main: LengthMetrics.vp(5)}}) {
            ForEach(this.pickerWidthHeightList, (item: pickerCategories<Length | LayoutPolicy>, index: number) => {
              this.clickComponent(item.id, item.text, (event: ClickEvent) => {
                this.widthValue = item.value!;
                this.myModifier.widthValue = item.value!;
              })
            })
          }.width('100%')

          Text('height: ' + JSON.stringify(this.heightValue)).width('100%').fontSize(12)
          Flex({wrap: FlexWrap.Wrap, alignContent: FlexAlign.Center, space: {main: LengthMetrics.vp(5)}}) {
            ForEach(this.pickerWidthHeightList, (item: pickerCategories<Length | LayoutPolicy>, index: number) => {
              this.clickComponent(item.id, item.text, (event: ClickEvent) => {
                this.heightValue = item.value!;
                this.myModifier.heightValue = item.value!;
              })
            })
          }.width('100%')

          Text('constraintSize: ' + JSON.stringify(this.constraintSizeValue)).width('100%').fontSize(12)
          Flex({wrap: FlexWrap.Wrap, alignContent: FlexAlign.Center, space: {main: LengthMetrics.vp(5)}}) {
            ForEach(this.constraintSizeList, (item: pickerCategories<ConstraintSizeOptions>, index: number) => {
              this.clickComponent(item.id, item.text, (event: ClickEvent) => {
                this.constraintSizeValue = item.value!;
                this.myModifier.constraintSizeValue = item.value!;
              })
            })
          }.width('100%')

          Text('aspectRatio: ' + JSON.stringify(this.aspectRatioValue)).width('100%').fontSize(12)
          Flex({wrap: FlexWrap.Wrap, alignContent: FlexAlign.Center, space: {main: LengthMetrics.vp(5)}}) {
            ForEach(this.aspectRatioList, (item: pickerCategories<number>, index: number) => {
              this.clickComponent(item.id, item.text, (event: ClickEvent) => {
                this.aspectRatioValue = item.value!;
                this.myModifier.aspectRatioValue = item.value!;
              })
            })
          }.width('100%')

          if (this.isModifier) {
            Text('背景: ' + 'backgroundColor').width('100%').fontSize(12)
          } else {
            Text('背景: ' + this.backgroundStr).width('100%').fontSize(12)
            Row({space: 5}) {
              this.clickComponent(undefined, 'background.ResourceColor', (event: ClickEvent) => {
                this.backType = 0;
                this.backgroundStr = 'background.ResourceColor';
              })
              this.clickComponent(undefined, 'background.CustomBuilder', (event: ClickEvent) => {
                this.backType = 1;
                this.backgroundStr = 'background.CustomBuilder';
              })
            }.width('100%')
            Row({space: 5}) {
              this.clickComponent(undefined, 'backgroundColor', (event: ClickEvent) => {
                this.backType = 2;
                this.backgroundStr = 'backgroundColor';
              })
            }.width('100%')
          }

          Text('LayoutSafeAreaEdge: ' + JSON.stringify(this.ignoresLayoutValue)).width('100%').fontSize(12)
          Flex({wrap: FlexWrap.Wrap, alignContent: FlexAlign.Center, space: {main: LengthMetrics.vp(5)}}) {
            ForEach(this.ignoresLayoutList, (item: pickerCategories<Array<LayoutSafeAreaEdge>>, index: number) => {
              this.clickComponent(item.id, item.text, (event: ClickEvent) => {
                this.ignoresLayoutValue = item.value!;
                this.myModifier.ignoresLayoutValue = item.value!;
              })
            })
          }.width('100%')
        }
      }.constraintSize({maxHeight: '30%'})

      // 设置父组件属性
      Text('父组件属性')
      Scroll() {
        Column() {
          Text('width: ' + JSON.stringify(this.parentWidthValue)).width('100%').fontSize(12)
          Flex({wrap: FlexWrap.Wrap, alignContent: FlexAlign.Center, space: {main: LengthMetrics.vp(5)}}) {
            ForEach(this.parentWidthHeightList, (item: pickerCategories<Length | LayoutPolicy>, index: number) => {
              this.clickComponent(item.id, item.text, (event: ClickEvent) => {
                this.parentWidthValue = item.value!;
              })
            })
          }.width('100%')

          Text('height: ' + JSON.stringify(this.parentHeightValue)).width('100%').fontSize(12)
          Flex({wrap: FlexWrap.Wrap, alignContent: FlexAlign.Center, space: {main: LengthMetrics.vp(5)}}) {
            ForEach(this.parentWidthHeightList, (item: pickerCategories<Length | LayoutPolicy>, index: number) => {
              this.clickComponent(item.id, item.text, (event: ClickEvent) => {
                this.parentHeightValue = item.value!;
              })
            })
          }.width('100%')

          Text('padding: ' + JSON.stringify(this.parentPaddingValue)).width('100%').fontSize(12)
          Flex({wrap: FlexWrap.Wrap, alignContent: FlexAlign.Center, space: {main: LengthMetrics.vp(5)}}) {
            ForEach(this.parentPaddingList, (item: pickerCategories<Length>, index: number) => {
              this.clickComponent(item.id, item.text, (event: ClickEvent) => {
                this.parentPaddingValue = item.value!;
              })
            })
          }.width('100%')

          Text('board: ' + JSON.stringify(this.parentBorderValue)).width('100%').fontSize(12)
          Flex({wrap: FlexWrap.Wrap, alignContent: FlexAlign.Center, space: {main: LengthMetrics.vp(5)}}) {
            ForEach(this.parentBorderList, (item: pickerCategories<Length>, index: number) => {
              this.clickComponent(item.id, item.text, (event: ClickEvent) => {
                this.parentBorderValue = item.value!;
              })
            })
          }.width('100%')

          Text('safeAreaPadding: ' + JSON.stringify(this.parentSafeAreaPaddingValue)).width('100%').fontSize(12)
          Flex({wrap: FlexWrap.Wrap, alignContent: FlexAlign.Center, space: {main: LengthMetrics.vp(5)}}) {
            ForEach(this.parentSafeAreaPaddingList, (item: pickerCategories<number>, index: number) => {
              this.clickComponent(item.id, item.text, (event: ClickEvent) => {
                this.parentSafeAreaPaddingValue = item.value!;
              })
            })
          }.width('100%')
        }
      }.constraintSize({maxHeight: '20%'})

      // 测试
      Column() {
        Column() {
          if (this.isModifier) {
            CalendarPicker({})
              .attributeModifier(this.myModifier)
              .overlay('modifier')
          } else {
            if (this.backType == 0) {
              CalendarPicker({})
                .width(this.widthValue)
                .height(this.heightValue)
                .aspectRatio(this.aspectRatioValue)
                .constraintSize(this.constraintSizeValue)
                .background('#ffdff5d2')
                .border({width: '1px', color: Color.Orange})
                .overlay('原生')
            } else if (this.backType == 1) {
              CalendarPicker({})
                .width(this.widthValue)
                .height(this.heightValue)
                .aspectRatio(this.aspectRatioValue)
                .constraintSize(this.constraintSizeValue)
                .background(this.renderBackGround(),
                  {ignoresLayoutSafeAreaEdges: this.ignoresLayoutValue})
                .border({width: '1px', color: Color.Orange})
                .overlay('原生')
            } else {
              CalendarPicker({})
                .width(this.widthValue)
                .height(this.heightValue)
                .aspectRatio(this.aspectRatioValue)
                .constraintSize(this.constraintSizeValue)
                .backgroundColor('#ffdff5d2')
                .ignoreLayoutSafeArea([LayoutSafeAreaType.SYSTEM], this.ignoresLayoutValue)
                .border({width: '1px', color: Color.Orange})
                .overlay('原生')
            }
          }
        }
        .width(this.parentWidthValue)
        .height(this.parentHeightValue)
        .padding(this.parentPaddingValue)
        .border({width: this.parentBorderValue, color: '#ff54f6e3'})
        .safeAreaPadding(LengthMetrics.px(this.parentSafeAreaPaddingValue))
      }
      .width('100%')
      .height('38%')
      .border({width: '10px', color: Color.Blue})
    }.width('100%')
  }
}