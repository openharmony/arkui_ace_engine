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
'use static'
import { Entry, Text, Column, Component, Button, ClickEvent, Select, TextModifier, TextAlign, Color, Row,
  FontWeight, TextOverflow, $r, HorizontalAlign, ColumnOptions, RowOptions, ArrowPosition, MenuAlignType,
  MenuOutlineOptions, MenuOutlineOptions, Dimension, EdgeOutlineWidths, ResourceColor, EdgeColors }
  from '@ohos.arkui.component'
import { State } from '@ohos.arkui.stateManagement'
import hilog from '@ohos.hilog'

@Builder
export function SelectMenuOutlineStaticBuilder(name: string, param: Object) {
  SelectMenuOutlineStatic()
}
@Entry
@Component
struct SelectMenuOutlineStatic {
  @State text: string = 'TTTTT';
  @State index: Int = -1;
  @State arrowPosition: ArrowPosition = ArrowPosition.END;
  @State changeIndex: Int = 0;
  private changeList: (MenuOutlineOptions | undefined)[] =
    [{width: '5vp',color: Color.Blue}, undefined,{width: '10vp',color: Color.Pink}];

  build() {
    Column({ space: 10 } as ColumnOptions) {
      Text(`设置5vp,Blue:`)
        .fontSize(16)
        .width('100%')
      Select([{ value: 'aaa' },
        { value: 'bbb' },
        { value: 'ccc' },
        { value: 'ddd' }])
        .selected(this.index)
        .value(this.text)
        .font({ size: 16, weight: 500 })
        .fontColor('#182431')
        .selectedOptionFont({ size: 16, weight: 400 })
        .optionFont({ size: 16, weight: 400 })
        .arrowPosition(this.arrowPosition)
        .menuAlign(MenuAlignType.START, { dx: 0, dy: 0 })
        .optionWidth(200)
        .optionHeight(300)
        .menuOutline({
          width: '5vp',
          color: Color.Blue
        })
      Text(`设置undefined:`)
        .fontSize(16)
        .width('100%')
      Select([{ value: 'aaa' },
        { value: 'bbb' },
        { value: 'ccc' },
        { value: 'ddd' }])
        .selected(this.index)
        .value(this.text)
        .font({ size: 16, weight: 500 })
        .fontColor('#182431')
        .selectedOptionFont({ size: 16, weight: 400 })
        .optionFont({ size: 16, weight: 400 })
        .arrowPosition(this.arrowPosition)
        .menuAlign(MenuAlignType.START, { dx: 0, dy: 0 })
        .optionWidth(200)
        .optionHeight(300)
        .menuOutline(undefined)
      Text(`动态延迟更新:`)
        .fontSize(16)
        .width('100%')
      Select([{ value: 'aaa' },
        { value: 'bbb' },
        { value: 'ccc' },
        { value: 'ddd' }])
        .selected(this.index)
        .value(this.text)
        .font({ size: 16, weight: 500 })
        .fontColor('#182431')
        .selectedOptionFont({ size: 16, weight: 400 })
        .optionFont({ size: 16, weight: 400 })
        .arrowPosition(this.arrowPosition)
        .menuAlign(MenuAlignType.START, { dx: 0, dy: 0 })
        .optionWidth(200)
        .optionHeight(300)
        .menuOutline(this.changeList[this.changeIndex])
      Button('动态延迟更新:' + this.changeList[this.changeIndex])
        .onClick(()=>{
          this.changeIndex = (this.changeIndex + 1) %this.changeList.length
        })
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F0F2F5')
  }
}