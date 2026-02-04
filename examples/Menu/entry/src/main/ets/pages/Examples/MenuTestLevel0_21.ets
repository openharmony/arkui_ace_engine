/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

/*
* 菜单蒙层效果
*
 */

import { MyComponent } from '../../common/MyComponent'
import { MenuBuilder, MenuAttrOptions } from '../../customBuilder/MenuBuilder'
import { Menu_UEC_0 } from '../../UIExtension/MenuTestLevel0_0_UEC'

@Extend(Text) function paramTextStyle() {
  .fontSize(9)
  .width('100%')
}

@Entry
@Component
struct MenuTestLevel0_21 {
  scroller: Scroller = new Scroller()

  @State targetVisible: Visibility = Visibility.Visible
  @State uecVisible: Visibility = Visibility.Visible

  build() {
    Scroll(this.scroller){
      Column({space: 5}){
        Text(`宿主窗口显示：${this.targetVisible}, UEC窗口显示: ${this.uecVisible}`)
          .paramTextStyle()
        Row({space: 3}){
          MyComponent({title: '隐藏Target窗口', func: () => {
            if (this.targetVisible == Visibility.Visible) {
              this.targetVisible = Visibility.None
            } else {
              this.targetVisible = Visibility.Visible
            }
          }})
          MyComponent({title: '隐藏UEC窗口', func: () => {
            if (this.uecVisible == Visibility.Visible) {
              this.uecVisible = Visibility.None
            } else {
              this.uecVisible = Visibility.Visible
            }
          }})
        }

        Column({space: 5}){
          //主窗中的弹窗
          Column({space: 5}){
            Text(`菜单的蒙层效果`)
              .paramTextStyle()
            Menu_UEC_0()
          }
          .visibility(this.targetVisible)
          .layoutWeight(1)

          Column({space: 5}) {
            
          }
          .visibility(this.uecVisible)
          .layoutWeight(1)
        }
      }
      .width('100%')
    }
    .padding(12)
    .scrollBar(BarState.Off)
    .align(Alignment.TopStart)
    .width('100%').height('100%')
  }

  pageTransition() {
    //进入该界面没有跳转延迟
    PageTransitionEnter({ type: RouteType.None, duration: 0 })
  }
}
