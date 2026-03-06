/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under * License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See * License for * specific language governing permissions and
 * limitations under * License.
 */

@Builder
export function SelectLevel8Builder(name: string, param: Object) {
  SelectLevel8Example()
}

@Entry
@Component
struct SelectLevel8Example {
  pathStack: NavPathStack = new NavPathStack()
  @State select1: number = 0
  @State select2: number = 1
  @State select3: number = 0
  @State select4: number = 0
  @State select5: number = 0
  @State select6: number = 0
  @State value1: string = '选项1'
  @State value2: string = '苹果'
  @State value3: string = '红色'
  @State value4: string = '小号'
  @State value5: string = '男'
  @State value6: string = '中文'

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 20 }) {
          Text('Select 基础示例')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .width('100%')

          Text('默认选择器')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Select([{ value: '选项1' }, { value: '选项2' }, { value: '选项3' }])
            .selected(this.select1)
            .value($$this.value1)
            .onSelect((index: number) => {
              this.select1 = index
            })

          Text('带图标')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Select([
            { value: '苹果', icon: $r('app.media.app_icon') },
            { value: '香蕉', icon: $r('app.media.app_icon') },
            { value: '橘子', icon: $r('app.media.app_icon') }
          ])
            .selected(this.select2)
            .value($$this.value2)
            .onSelect((index: number) => {
              this.select2 = index
            })

          Text('自定义选中颜色')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Select([{ value: '红色' }, { value: '绿色' }, { value: '蓝色' }])
            .selected(this.select3)
            .value($$this.value3)
            .selectedOptionBgColor(0x317aff)
            .selectedOptionFontColor(Color.White)
            .onSelect((index: number) => {
              this.select3 = index
            })

          Text('不同尺寸')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Column({ space: 10 }) {
            Select([{ value: '小号' }, { value: '中号' }, { value: '大号' }])
              .selected(this.select4)
              .value($$this.value4)
              .width(150)
              .onSelect((index: number) => {
                this.select4 = index
              })
            Select([{ value: 'S' }, { value: 'M' }, { value: 'L' }])
              .selected(1)
              .value('M')
              .width(200)
          }

          Text('禁用状态')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Select([{ value: '选项1' }, { value: '选项2' }, { value: '选项3' }])
            .selected(0)
            .value('选项1')
            .enabled(false)

          Text('带标签')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Column({ space: 10 }) {
            Row({ space: 10 }) {
              Text('性别:')
              Select([{ value: '男' }, { value: '女' }])
                .selected(this.select5)
                .value($$this.value5)
                .width(100)
                .onSelect((index: number) => {
                  this.select5 = index
                })
            }
            Row({ space: 10 }) {
              Text('语言:')
              Select([{ value: '中文' }, { value: 'English' }, { value: '日本語' }])
                .selected(this.select6)
                .value($$this.value6)
                .width(120)
                .onSelect((index: number) => {
                  this.select6 = index
                })
            }
          }

          Text('自定义字体')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Select([{ value: '选项1' }, { value: '选项2' }, { value: '选项3' }])
            .selected(1)
            .value('选项2')
            .font({ size: 16, weight: 500 })
            .selectedOptionFont({ size: 16, weight: 400 })
            .optionFont({ size: 16, weight: 400 })

          Text('带分隔线')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Select([{ value: '选项1' }, { value: '选项2' }, { value: '选项3' }])
            .selected(0)
            .value('选项1')
            .divider({
              strokeWidth: 1,
              color: 0xcccccc,
              startMargin: 10,
              endMargin: 10
            })

          Text('自定义箭头位置')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Column({ space: 10 }) {
            Select([{ value: '选项1' }, { value: '选项2' }, { value: '选项3' }])
              .selected(0)
              .value('选项1')
              .arrowPosition(ArrowPosition.START)
            Select([{ value: '选项1' }, { value: '选项2' }, { value: '选项3' }])
              .selected(0)
              .value('选项1')
              .arrowPosition(ArrowPosition.END)
          }

          Text('菜单对齐方式')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Select([{ value: '选项1' }, { value: '选项2' }, { value: '选项3' }])
            .selected(0)
            .value('选项1')
            .menuAlign(MenuAlignType.START)

          Text('自定义选项宽高')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Select([{ value: '选项1' }, { value: '选项2' }, { value: '选项3' }])
            .selected(0)
            .value('选项1')
            .optionWidth(200)
            .optionHeight(150)

          Text('带间距')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Select([{ value: '选项1' }, { value: '选项2' }, { value: '选项3' }])
            .selected(0)
            .value('选项1')
            .space(10)

          Text('不同方向')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Column({ space: 10 }) {
            Select([{ value: '选项1' }, { value: '选项2' }, { value: '选项3' }])
              .selected(0)
              .value('选项1')
              .direction(Direction.Ltr)
            Select([{ value: '选项1' }, { value: '选项2' }, { value: '选项3' }])
              .selected(0)
              .value('选项1')
              .direction(Direction.Rtl)
          }
        }
        .padding(20)
      }
    }
    .title('SelectLevel8')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
