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
@Builder
export function SelectShowDefaultSelectedIconBuilder(name: string, param: Object) {
  SelectShowDefaultSelectedIcon()
}
@Entry
@Component
struct SelectShowDefaultSelectedIcon {
  @State text: string = 'TTTTT';
  @State index: number = 2;
  @State arrowPosition: ArrowPosition = ArrowPosition.END;
  @State changeIndex: number = 0;
  @State changeList: ( boolean | undefined )[] = [
    false,
    true,
    undefined
  ]

  build() {
    Column({ space: 10 }) {
      Text(`设置selectedOptionBgColor选中项的背景色:`)
        .fontSize(16)
        .width('100%')
      Row({ space: 5 }){
        Select([{ value: 'aaa' },
          { value: 'bbb' },
          { value: 'ccc' },
          { value: 'ddd' }])
          .selected(this.index)
          .value('true')
          .font({ size: 16, weight: 500 })
          .fontColor('#182431')
          .selectedOptionFont({ size: 16, weight: 400 })
          .optionFont({ size: 16, weight: 400 })
          .arrowPosition(this.arrowPosition)
          .menuAlign(MenuAlignType.START, { dx: 0, dy: 0 })
          .optionWidth(200)
          .optionHeight(300)
          .selectedOptionBgColor(Color.Orange)
          .showDefaultSelectedIcon(true)
        Select([{ value: 'aaa' },
          { value: 'bbb' },
          { value: 'ccc' },
          { value: 'ddd' }])
          .selected(this.index)
          .value('false')
          .font({ size: 16, weight: 500 })
          .fontColor('#182431')
          .selectedOptionFont({ size: 16, weight: 400 })
          .optionFont({ size: 16, weight: 400 })
          .arrowPosition(this.arrowPosition)
          .menuAlign(MenuAlignType.START, { dx: 0, dy: 0 })
          .optionWidth(200)
          .optionHeight(300)
          .selectedOptionBgColor(Color.Orange)
          .showDefaultSelectedIcon(false)
        Select([{ value: 'aaa' },
          { value: 'bbb' },
          { value: 'ccc' },
          { value: 'ddd' }])
          .selected(this.index)
          .value('undefined')
          .font({ size: 16, weight: 500 })
          .fontColor('#182431')
          .selectedOptionFont({ size: 16, weight: 400 })
          .optionFont({ size: 16, weight: 400 })
          .arrowPosition(this.arrowPosition)
          .menuAlign(MenuAlignType.START, { dx: 0, dy: 0 })
          .optionWidth(200)
          .optionHeight(300)
          .selectedOptionBgColor(Color.Orange)
          .showDefaultSelectedIcon(undefined)
      }
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
        .selectedOptionBgColor(Color.Orange)
        .showDefaultSelectedIcon(this.changeList[this.changeIndex])
      Button('动态延迟更新:' + this.changeList[this.changeIndex])
        .onClick(()=>{
          setTimeout(()=>{
            this.changeIndex = (this.changeIndex + 1) %this.changeList.length
          },2000)
        })
      Text(`未通过selectedOptionBgColor设置选中项的背景色:`)
        .fontSize(16)
        .width('100%')
      Row({ space: 5 }){
        Select([{ value: 'aaa' },
          { value: 'bbb' },
          { value: 'ccc' },
          { value: 'ddd' }])
          .selected(this.index)
          .value('true')
          .font({ size: 16, weight: 500 })
          .fontColor('#182431')
          .selectedOptionFont({ size: 16, weight: 400 })
          .optionFont({ size: 16, weight: 400 })
          .arrowPosition(this.arrowPosition)
          .menuAlign(MenuAlignType.START, { dx: 0, dy: 0 })
          .optionWidth(200)
          .optionHeight(300)
          .showDefaultSelectedIcon(true)
        Select([{ value: 'aaa' },
          { value: 'bbb' },
          { value: 'ccc' },
          { value: 'ddd' }])
          .selected(this.index)
          .value('false')
          .font({ size: 16, weight: 500 })
          .fontColor('#182431')
          .selectedOptionFont({ size: 16, weight: 400 })
          .optionFont({ size: 16, weight: 400 })
          .arrowPosition(this.arrowPosition)
          .menuAlign(MenuAlignType.START, { dx: 0, dy: 0 })
          .optionWidth(200)
          .optionHeight(300)
          .showDefaultSelectedIcon(false)
        Select([{ value: 'aaa' },
          { value: 'bbb' },
          { value: 'ccc' },
          { value: 'ddd' }])
          .selected(this.index)
          .value('undefined')
          .font({ size: 16, weight: 500 })
          .fontColor('#182431')
          .selectedOptionFont({ size: 16, weight: 400 })
          .optionFont({ size: 16, weight: 400 })
          .arrowPosition(this.arrowPosition)
          .menuAlign(MenuAlignType.START, { dx: 0, dy: 0 })
          .optionWidth(200)
          .optionHeight(300)
          .showDefaultSelectedIcon(undefined)
      }
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
        .showDefaultSelectedIcon(this.changeList[this.changeIndex])
      Button('动态延迟更新:' + this.changeList[this.changeIndex])
        .onClick(()=>{
          setTimeout(()=>{
            this.changeIndex = (this.changeIndex + 1) %this.changeList.length
          },2000)
        })
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F0F2F5')
  }
}