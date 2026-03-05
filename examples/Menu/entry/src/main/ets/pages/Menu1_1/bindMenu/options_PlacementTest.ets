/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

@Entry
@Component
struct Options_PlacementTest {
  @State message: string = 'Hello World';
  @State select: boolean = true;
  @State MenuOptions:MenuOptions = {title:undefined}
  // $r('app.media.xxx')需要替换为开发者所需的图像资源文件。
  private iconStr: ResourceStr = $r("app.media.app_icon");
  private iconStr2: ResourceStr = $r("app.media.app_icon");
  PlacementNames: string[] = [
    'Left:气泡提示位于组件左侧，与组件左侧中心对齐',
    'Right:气泡提示位于组件右侧，与组件右侧中心对齐',
    'Top:气泡提示位于组件上侧，与组件上侧中心对齐',
    'Bottom:气泡提示位于组件下侧，与组件下侧中心对齐',
    'TopLeft:气泡提示位于组件上侧，从API Version 9开始，与组件左侧边缘对齐',
    'TopRight:气泡提示位于组件上侧，从API Version 9开始，与组件右侧边缘对齐',
    'BottomLeft:气泡提示位于组件下侧，从API Version 9开始，与组件左侧边缘对齐',
    'BottomRight:气泡提示位于组件下侧，从API Version 9开始，与组件右侧边缘对齐',
    'LeftTop:气泡提示位于组件左侧，与组件上侧边缘对齐',
    'LeftBottom:气泡提示位于组件左侧，与组件下侧边缘对齐',
    'RightTop:气泡提示位于组件右侧，与组件上侧边缘对齐',
    'RightBottom:气泡提示位于组件右侧，与组件下侧边缘对齐',
  ]
  @State PlacementIndex: number = 0
  @State PlacementList: (Placement| undefined)[] = [
    Placement.Left,
    Placement.Right,
    Placement.Top,
    Placement.Bottom,
    Placement.TopLeft,
    Placement.TopRight,
    Placement.BottomLeft,
    Placement.BottomRight,
    Placement.LeftTop,
    Placement.LeftBottom,
    Placement.RightTop,
    Placement.RightBottom,
    undefined
  ]
  @Builder
  SubMenu() {
    Menu() {
      MenuItem({ content: undefined, labelInfo: "Ctrl+C" })
      MenuItem({ content: "粘贴", labelInfo: "Ctrl+V" })
    }.backgroundColor("#f2f2f2")
  }

  @Builder
  MyMenu(color:ResourceColor){
    Menu() {
      MenuItemGroup(){
        MenuItem({ startIcon: $r("app.media.app_icon"), content: "菜单选项" })
        MenuItem({ startIcon: $r("app.media.app_icon"), content: "菜单选项" })
        MenuItem({
          startIcon: this.iconStr,
          content: "菜单选项"
        })
        MenuItem({
          startIcon: this.iconStr,
          content: "菜单选项",
        })
      }
    }.fontColor(color)
    .backgroundColor("#f2f2f2")
    .width('20%')
    .height(300)
  }

  build() {
    Scroll() {
      Column({space:5}) {
        Text('bindMenu设置options，Placement气泡显示的位置,默认值：Placement.BottomLeft')
          .fontSize(20).fontColor(0x000020).fontWeight(FontWeight.Bold)
          .height('6%')
          .width('95%')
          .borderRadius(15)
          .backgroundColor('#ffa9cbd6')

        Text('设定bindMenu的options中placement?: Placement显示位置设置空').width('80%')
        Button('menu Placement_null')
          .bindMenu(this.MyMenu(Color.Blue),{placement:null})
        Text('设定bindMenu的options中placement?: Placement显示位置设置undefined').width('80%')
        Button('menu Placement_undefined')
          .bindMenu(this.MyMenu(Color.Blue),{placement:undefined})
        Text('设定bindMenu的options中placement?: Placement显示位置设置LeftTop').width('80%')
        Button('menu Placement_LeftTop')
          .bindMenu(this.MyMenu(Color.Blue),{placement:Placement.LeftTop})
        Text('遍历placement').width('80%')
        Button('遍历').backgroundColor(Color.Gray)
          .onClick(() => {
            this.PlacementIndex++
            if (this.PlacementIndex > this.PlacementList.length - 1) {
              this.PlacementIndex = 0
            }
          })
        Text(`参数：placement=${this.PlacementNames[this.PlacementIndex]}`).width('80%')
        Button('menu')
          .bindMenu(this.MyMenu(Color.Blue),{placement:this.PlacementList[this.PlacementIndex]})
        Button('menu Placement_Bottom')
          .bindMenu(this.MyMenu(Color.Blue),{placement:Placement.Bottom})
        Button('menu Placement_Bottom')
          .bindMenu(this.MyMenu(Color.Blue),{placement:Placement.Bottom})
        Button('menu Placement_Bottom')
          .bindMenu(this.MyMenu(Color.Blue),{placement:Placement.Bottom})
        Button('menu Placement_Bottom')
          .bindMenu(this.MyMenu(Color.Blue),{placement:Placement.Bottom})
        Button('menu Placement_Bottom')
          .bindMenu(this.MyMenu(Color.Blue),{placement:Placement.Bottom})
        Button('menu Placement_Bottom')
          .bindMenu(this.MyMenu(Color.Blue),{placement:Placement.Bottom})
      }
      .width('100%')
      .height('100%')
    }
  }
}