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

import { inputMethod } from '@kit.IMEKit';
import { LengthMetrics } from '@kit.ArkUI';
import { MyComponent } from '../../common/MyComponent'
@Extend(Text)
function paramTextStyle() {
  .fontSize(16)
  .width("100%")
}
@Entry
@Component
struct bindContextMenu_keyBoard {
  // $r('app.media.icon')需要替换为开发者所需的图像资源文件。
  private iconStr: ResourceStr = $r("app.media.app_icon");
  @State isShown: boolean = false;
  private inputController: inputMethod.InputMethodController = inputMethod.getController();
  @State keyboardAvoidMode:	MenuKeyboardAvoidMode | undefined = undefined;
  @State minKeyboardAvoidDistance: LengthMetrics | undefined = undefined;
  @State longPress: string = 'LONG_PRESS';
  @State rightClick: string = 'RIGHT_CLICK';

  @Builder
  MyMenu() {
    Menu() {
      MenuItem({ startIcon: this.iconStr, content: "菜单选项" })
      MenuItem({ startIcon: this.iconStr, content: "菜单选项" })
      MenuItem({ startIcon: this.iconStr, content: "菜单选项" })
      MenuItem({ startIcon: this.iconStr, content: "菜单选项" })
      MenuItem({ startIcon: this.iconStr, content: "菜单选项" })
    }
  }

  @Builder
  MyPreview() {
    Column() {
      Image($r('app.media.app_icon'))
        .width(200)
        .height(200)
    }
  }
  @Builder MenuBuilder() {
    Flex({ direction: FlexDirection.Column, justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
      Text('Test menu item 1')
        .fontSize(20)
        .width(100)
        .height(50)
        .textAlign(TextAlign.Center)
      Divider().height(10)
      Text('Test menu item 2')
        .fontSize(20)
        .width(100)
        .height(50)
        .textAlign(TextAlign.Center)
    }.width(100)
  }
  @Builder
  MenuBuilderWithParam(type: ResponseType) {
    Flex({ direction: FlexDirection.Column, justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
        Menu() {
          MenuItem({ startIcon: this.iconStr, content: "菜单选项" })
          MenuItem({ startIcon: this.iconStr, content: "菜单选项" })
          MenuItem({ startIcon: this.iconStr, content: "菜单选项" })
          MenuItem({ startIcon: this.iconStr, content: "菜单选项" })
          MenuItem({ startIcon: this.iconStr, content: "菜单选项" })
        }
      Text('Current ResponseType = ' + (type === 0 ? 'RIGHT_CLICK' : 'LONG_PRESS'))
      Divider().height(10)
      if (type === ResponseType.LongPress) {
        Text('Item: ' + this.longPress)
          .fontSize(20)
          .width(200)
          .height(20)
          .textAlign(TextAlign.Center)
      }
      if (type === ResponseType.RightClick) {
        Text('Item: ' + this.rightClick)
          .fontSize(20)
          .width(200)
          .height(20)
          .textAlign(TextAlign.Center)
      }
    }
  }
  build() {
    Column({ space: 200 }) {
        Column() {
          // Text('preview-builder')
          //   .position({x:50, y:50})
          //   .width(200)
          //   .height(100)
          //   .textAlign(TextAlign.Center)
          //   .fontSize(30)
          //   .bindContextMenu(this.isShown, this.MyMenu,
          //     {
          //       keyboardAvoidMode: MenuKeyboardAvoidMode.TRANSLATE_AND_RESIZE,
          //       minKeyboardAvoidDistance: LengthMetrics.vp(20),
          //       // placement:Placement.Bottom,
          //       // preview: this.MyPreview,
          //       aboutToDisappear: ()=>{
          //         this.isShown = false;
          //       }
          //     })


          // Button('click')
          //   .onClick(()=>{
          //     this.isShown = true;
          //     setTimeout(() => {
          //       this.attachAndListener()
          //     }, 2000)
          //   })
          Text(`keyboardAvoidMode: ${this.keyboardAvoidMode}`)
            .paramTextStyle()
          Row({ space: 5 }) {
            MyComponent({
              title: 'NONE', func: () => {
                this.keyboardAvoidMode = MenuKeyboardAvoidMode.NONE
              }
            })
            MyComponent({
              title: 'RESIZE', func: () => {
                this.keyboardAvoidMode = MenuKeyboardAvoidMode.TRANSLATE_AND_RESIZE
              }
            })
            MyComponent({
              title: 'UN', func: () => {
                this.keyboardAvoidMode = undefined
              }
            })
          }
          Text(`minKeyboardAvoidDistance: ${this.minKeyboardAvoidDistance}`)
            .paramTextStyle()
          Row({ space: 5 }) {
            MyComponent({
              title: '10', func: () => {
                this.minKeyboardAvoidDistance = LengthMetrics.vp(10)
              }
            })
            MyComponent({
              title: '30', func: () => {
                this.minKeyboardAvoidDistance = LengthMetrics.vp(30)
              }
            })
            MyComponent({
              title: 'un', func: () => {
                this.minKeyboardAvoidDistance = undefined
              }
            })
          }
        }
      Column() {
        Button('preview-builder')
          .align(Alignment.Center)
          .bindContextMenu(this.MyMenu,ResponseType.LongPress,
            {
              keyboardAvoidMode: MenuKeyboardAvoidMode.TRANSLATE_AND_RESIZE,
              minKeyboardAvoidDistance: LengthMetrics.vp(20),
              // placement:Placement.Bottom,
              // preview: this.MyPreview,
              onAppear: ()=>{
                setTimeout(() => {
                  this.attachAndListener()
                }, 2000)
              }
            })
      }.width('100%')
    }.width('100%').height('100%')
  }
  async attachAndListener() {
    focusControl.requestFocus('Index')
    try {
      await this.inputController.attach(true, {
        inputAttribute: {
          textInputType: inputMethod.TextInputType.TEXT,
          enterKeyType: inputMethod.EnterKeyType.SEARCH
        }
      })
    } catch (err) {
      console.error('Fail to attach')
    }
  }
}

//bindMenu示例代码
// import { inputMethod } from '@kit.IMEKit';
// import { LengthMetrics } from '@kit.ArkUI';
//
// @Entry
// @Component
// struct Index {
//   private inputController: inputMethod.InputMethodController = inputMethod.getController();
//
//   @Builder
//   MyMenu() {
//     Menu() {
//       MenuItem({ content: 'MenuItemContent' })
//       MenuItem({ content: 'MenuItemContent' })
//       MenuItem({ content: 'MenuItemContent' })
//       MenuItem({ content: 'MenuItemContent' })
//       MenuItem({ content: 'MenuItemContent' })
//     }
//   }
//
//   build() {
//     RelativeContainer() {
//       Button('Click Show Menu')
//         .alignRules({
//           center: { anchor: '__container__', align: VerticalAlign.Center },
//           middle: { anchor: '__container__', align: HorizontalAlign.Center },
//         })
//         .bindMenu(this.MyMenu, {
//           keyboardAvoidMode: MenuKeyboardAvoidMode.TRANSLATE_AND_RESIZE,
//           minKeyboardAvoidDistance: LengthMetrics.vp(20)
//         })
//         .onClick(() => {
//           setTimeout(() => {
//             this.attachAndListener()
//           }, 2000)
//         })
//     }
//     .height('100%')
//     .width('100%')
//
//   }
//
//   async attachAndListener() {
//     focusControl.requestFocus('Index')
//     try {
//       await this.inputController.attach(true, {
//         inputAttribute: {
//           textInputType: inputMethod.TextInputType.TEXT,
//           enterKeyType: inputMethod.EnterKeyType.SEARCH
//         }
//       })
//     } catch (err) {
//       console.error('Fail to attach')
//     }
//   }
// }