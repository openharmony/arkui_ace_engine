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
export function SelectLevel5Builder(name: string, param: Object) {
  SelectLevel5Example()
}

@Entry
@Component
struct SelectLevel5Example {
  pathStack: NavPathStack = new NavPathStack()
  @State font: Font = { size: 30, weight: 400, family: 'serif', style: FontStyle.Normal }
  @State fontColor: Color = 0xCCCCCC

  build() {
    NavDestination() {
      Row() {
        Column() {
          List({ space: 0, initialIndex: 0 }) {
            ListItem() {
              Select([{ value: 'aaa', icon: '/images/img.png' },
                { value: 'bbb', icon: '/images/img.png' },
                { value: 'ccc', icon: '/images/img.png' },
                { value: 'ddd', icon: '/images/img.png' }])
                .selected(2)
                .value('TTT')
                .font(this.font)
                .fontColor(this.fontColor)
                .selectedOptionFont({
                  size: 40,
                  weight: 500,
                  family: 'serif',
                  style: FontStyle.Normal
                })
                .optionFont({
                  size: 30,
                  weight: 400,
                  family: 'serif',
                  style: FontStyle.Normal
                })
                .key('selectTest1')
                .menuAlign(MenuAlignType.START)
                .onSelect((index: number) => {
                  console.info('Select:' + index)
                })
            }

            ListItem() {
              Select([{ value: 'aaa', icon: '/images/img.png' },
                { value: 'bbb', icon: '/images/img.png' },
                { value: 'ccc', icon: '/images/img.png' },
                { value: 'ddd', icon: '/images/img.png' }])
                .selected(2)
                .value('TTT')
                .font(this.font)
                .fontColor(this.fontColor)
                .selectedOptionFont({
                  size: 40,
                  weight: 500,
                  family: 'serif',
                  style: FontStyle.Normal
                })
                .optionFont({
                  size: 30,
                  weight: 400,
                  family: 'serif',
                  style: FontStyle.Normal
                })
                .key('selectTest2')
                .menuAlign(MenuAlignType.CENTER)
                .onSelect((index: number) => {
                  console.info('Select:' + index)
                })
            }

            ListItem() {
              Select([{ value: 'aaa', icon: '/images/img.png' },
                { value: 'bbb', icon: '/images/img.png' },
                { value: 'ccc', icon: '/images/img.png' },
                { value: 'ddd', icon: '/images/img.png' }])
                .selected(2)
                .value('TTT')
                .font(this.font)
                .fontColor(this.fontColor)
                .selectedOptionFont({
                  size: 40,
                  weight: 500,
                  family: 'serif',
                  style: FontStyle.Normal
                })
                .optionFont({
                  size: 30,
                  weight: 400,
                  family: 'serif',
                  style: FontStyle.Normal
                })
                .key('selectTest3')
                .menuAlign(MenuAlignType.END)
                .onSelect((index: number) => {
                  console.info('Select:' + index)
                })
            }

            ListItem() {
              Select([{ value: 'aaa', icon: '/images/img.png' },
                { value: 'bbb', icon: '/images/img.png' },
                { value: 'ccc', icon: '/images/img.png' },
                { value: 'ddd', icon: '/images/img.png' }])
                .selected(2)
                .value('TTT')
                .font(this.font)
                .fontColor(this.fontColor)
                .selectedOptionFont({
                  size: 40,
                  weight: 500,
                  family: 'serif',
                  style: FontStyle.Normal
                })
                .optionFont({
                  size: 30,
                  weight: 400,
                  family: 'serif',
                  style: FontStyle.Normal
                })
                .key('selectTest4')
                .menuAlign(MenuAlignType.START, { dx: 10, dy: 10 })
                .onSelect((index: number) => {
                  console.info('Select:' + index)
                })
            }

            ListItem() {
              Select([{ value: 'aaa', icon: '/images/img.png' },
                { value: 'bbb', icon: '/images/img.png' },
                { value: 'ccc', icon: '/images/img.png' },
                { value: 'ddd', icon: '/images/img.png' }])
                .selected(2)
                .value('TTT')
                .font(this.font)
                .fontColor(this.fontColor)
                .selectedOptionFont({
                  size: 40,
                  weight: 500,
                  family: 'serif',
                  style: FontStyle.Normal
                })
                .optionFont({
                  size: 30,
                  weight: 400,
                  family: 'serif',
                  style: FontStyle.Normal
                })
                .key('selectTest5')
                .menuAlign(MenuAlignType.CENTER, { dx: -10, dy: 0 })
                .onSelect((index: number) => {
                  console.info('Select:' + index)
                })
            }

            ListItem() {
              Select([{ value: 'aaa', icon: '/images/img.png' },
                { value: 'bbb', icon: '/images/img.png' },
                { value: 'ccc', icon: '/images/img.png' },
                { value: 'ddd', icon: '/images/img.png' }])
                .selected(2)
                .value('TTT')
                .font(this.font)
                .fontColor(this.fontColor)
                .selectedOptionFont({
                  size: 40,
                  weight: 500,
                  family: 'serif',
                  style: FontStyle.Normal
                })
                .optionFont({
                  size: 30,
                  weight: 400,
                  family: 'serif',
                  style: FontStyle.Normal
                })
                .key('selectTest6')
                .menuAlign(MenuAlignType.END, { dx: -20, dy: -50 })
                .onSelect((index: number) => {
                  console.info('Select:' + index)
                })
            }

            ListItem() {
              Select([{ value: 'aaa', icon: '/images/img.png' },
                { value: 'bbb', icon: '/images/img.png' },
                { value: 'ccc', icon: '/images/img.png' },
                { value: 'ddd', icon: '/images/img.png' }])
                .selected(2)
                .value('TTT')
                .font(this.font)
                .fontColor(this.fontColor)
                .selectedOptionFont({
                  size: 40,
                  weight: 500,
                  family: 'serif',
                  style: FontStyle.Normal
                })
                .optionFont({
                  size: 30,
                  weight: 400,
                  family: 'serif',
                  style: FontStyle.Normal
                })
                .key('selectTest7')
                .menuAlign(MenuAlignType.END, { dx: 0, dy: 0 })
                .onSelect((index: number) => {
                  console.info('Select:' + index)
                })
            }

            ListItem() {
              Select([{ value: 'aaa', icon: '/images/img.png' },
                { value: 'bbb', icon: '/images/img.png' },
                { value: 'ccc', icon: '/images/img.png' },
                { value: 'ddd', icon: '/images/img.png' }])
                .selected(2)
                .value('TTT')
                .font(this.font)
                .fontColor(this.fontColor)
                .selectedOptionFont({
                  size: 40,
                  weight: 500,
                  family: 'serif',
                  style: FontStyle.Normal
                })
                .optionFont({
                  size: 30,
                  weight: 400,
                  family: 'serif',
                  style: FontStyle.Normal
                })
                .key('selectTest8')
                .menuAlign(fakeMenuAlignType(null))
                .onSelect((index: number) => {
                  console.info('Select:' + index)
                })
            }

            ListItem() {
              Select([{ value: 'aaa', icon: '/images/img.png' },
                { value: 'bbb', icon: '/images/img.png' },
                { value: 'ccc', icon: '/images/img.png' },
                { value: 'ddd', icon: '/images/img.png' }])
                .selected(2)
                .value('TTT')
                .font(this.font)
                .fontColor(this.fontColor)
                .selectedOptionFont({
                  size: 40,
                  weight: 500,
                  family: 'serif',
                  style: FontStyle.Normal
                })
                .optionFont({
                  size: 30,
                  weight: 400,
                  family: 'serif',
                  style: FontStyle.Normal
                })
                .key('selectTest9')
                .menuAlign(fakeMenuAlignType(undefined))
                .onSelect((index: number) => {
                  console.info('Select:' + index)
                })
            }

            ListItem() {
              Select([{ value: 'aaa', icon: '/images/img.png' },
                { value: 'bbb', icon: '/images/img.png' },
                { value: 'ccc', icon: '/images/img.png' },
                { value: 'ddd', icon: '/images/img.png' }])
                .selected(2)
                .value('TTT')
                .font(this.font)
                .fontColor(this.fontColor)
                .selectedOptionFont({
                  size: 40,
                  weight: 500,
                  family: 'serif',
                  style: FontStyle.Normal
                })
                .optionFont({
                  size: 30,
                  weight: 400,
                  family: 'serif',
                  style: FontStyle.Normal
                })
                .key('selectTest10')
                .menuAlign(fakeMenuAlignType('menuAlign'))
                .onSelect((index: number) => {
                  console.info('Select:' + index)
                })
            }

            ListItem() {
              Select([{ value: 'aaa', icon: '/images/img.png' },
                { value: 'bbb', icon: '/images/img.png' },
                { value: 'ccc', icon: '/images/img.png' },
                { value: 'ddd', icon: '/images/img.png' }])
                .selected(2)
                .value('TTT')
                .font(this.font)
                .fontColor(this.fontColor)
                .selectedOptionFont({
                  size: 40,
                  weight: 500,
                  family: 'serif',
                  style: FontStyle.Normal
                })
                .optionFont({
                  size: 30,
                  weight: 400,
                  family: 'serif',
                  style: FontStyle.Normal
                })
                .key('selectTest11')
                .onSelect((index: number) => {
                  console.info('Select:' + index)
                })
            }

            ListItem() {
              Select([{ value: 'aaa', icon: '/images/img.png' },
                { value: 'bbb', icon: '/images/img.png' },
                { value: 'ccc', icon: '/images/img.png' },
                { value: 'ddd', icon: '/images/img.png' }])
                .selected(2)
                .value('TTT')
                .font(this.font)
                .fontColor(this.fontColor)
                .selectedOptionFont({
                  size: 40,
                  weight: 500,
                  family: 'serif',
                  style: FontStyle.Normal
                })
                .optionFont({
                  size: 30,
                  weight: 400,
                  family: 'serif',
                  style: FontStyle.Normal
                })
                .key('selectTest12')
                .menuAlign(MenuAlignType.CENTER)
                .menuAlign(MenuAlignType.END)
                .onSelect((index: number) => {
                  console.info('Select:' + index)
                })
            }

            ListItem() {
              Select([{ value: 'aaa', icon: '/images/img.png' },
                { value: 'bbb', icon: '/images/img.png' },
                { value: 'ccc', icon: '/images/img.png' },
                { value: 'ddd', icon: '/images/img.png' }])
                .selected(2)
                .value('TTT')
                .font(this.font)
                .fontColor(this.fontColor)
                .selectedOptionFont({
                  size: 40,
                  weight: 500,
                  family: 'serif',
                  style: FontStyle.Normal
                })
                .optionFont({
                  size: 30,
                  weight: 400,
                  family: 'serif',
                  style: FontStyle.Normal
                })
                .key('selectTest13')
                .menuAlign(MenuAlignType.CENTER)
                .menuAlign(fakeMenuAlignType(null))
                .onSelect((index: number) => {
                  console.info('Select:' + index)
                })
            }

            ListItem() {
              Select([{ value: 'aaa', icon: '/images/img.png' },
                { value: 'bbb', icon: '/images/img.png' },
                { value: 'ccc', icon: '/images/img.png' },
                { value: 'ddd', icon: '/images/img.png' }])
                .selected(2)
                .value('TTT')
                .font(this.font)
                .fontColor(this.fontColor)
                .selectedOptionFont({
                  size: 40,
                  weight: 500,
                  family: 'serif',
                  style: FontStyle.Normal
                })
                .optionFont({
                  size: 30,
                  weight: 400,
                  family: 'serif',
                  style: FontStyle.Normal
                })
                .key('selectTest14')
                .menuAlign(fakeMenuAlignType(null))
                .menuAlign(MenuAlignType.CENTER, { dx: -5, dy: -5 })
                .onSelect((index: number) => {
                  console.info('Select:' + index)
                })
            }

            ListItem() {
              Select([{ value: 'aaa', icon: '/images/img.png' },
                { value: 'bbb', icon: '/images/img.png' },
                { value: 'ccc', icon: '/images/img.png' },
                { value: 'ddd', icon: '/images/img.png' }])
                .selected(2)
                .value('TTT')
                .font(this.font)
                .fontColor(this.fontColor)
                .selectedOptionFont({
                  size: 40,
                  weight: 500,
                  family: 'serif',
                  style: FontStyle.Normal
                })
                .optionFont({
                  size: 30,
                  weight: 400,
                  family: 'serif',
                  style: FontStyle.Normal
                })
                .key('selectTest15')
                .onSelect((index: number) => {
                  console.info('Select:' + index)
                })
            }
          }
          .alignListItem(ListItemAlign.Center)
        }
        .width('100%')
      }
      .height('100%')
    }
    .title('SelectLevel5')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}

function fakeMenuAlignType(val: MenuAlignType|string|null|undefined) {
  return val as MenuAlignType
}