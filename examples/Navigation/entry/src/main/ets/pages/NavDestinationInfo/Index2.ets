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

// import router from '@ohos.router';
//
// interface ListCategories {
//   title:string,
//   url:string
// }
//
// @Entry
// @Component
// struct MenuIndex {
//   @State message: string = 'Navigation'
//   private items : ListCategories[] = [
//     {title:'基础场景页面',url:'pages/Foundations'},
//     {title:'Navigation不存在ID场景',url:'pages/NoId'},
//   ]
//
//   build() {
//     Column() {
//       Text(this.message).fontSize(22).fontColor(0xFFFFFF).fontWeight(FontWeight.Bold).textAlign(TextAlign.Center).width('100%').height(50).backgroundColor("#FF08528A")
//       List({space:'20vp'}) {
//         ForEach(this.items,(item : ListCategories) => {
//           ListItem() {
//             Button(){
//               Row() {
//                 LoadingProgress().width(40).height(40).color(0xFFFFFF)
//                 Text(item.title).fontSize(16).fontColor(0xffffff).margin({ left: 5, right: 12 })
//               }.alignItems(VerticalAlign.Center)
//
//             }
//             .type(ButtonType.Normal)
//             .backgroundColor(0x317aff)
//             .width('100%')
//             .fontSize(15)
//             .fontColor(0x000000)
//             .labelStyle({maxLines:1, overflow: TextOverflow.MARQUEE})
//             .onClick(() => {
//               router.pushUrl({url:item.url})
//             })
//           }
//         })
//       }.expandSafeArea()
//       .alignListItem(ListItemAlign.Center)
//       // .margin({top:'10vp'})
//       .width('95%').height('90%')
//     }.width('100%').height('100%').backgroundColor('#FFDDE7F6')
//     .expandSafeArea()
//   }
// }

// Index.ets
import observer from '@ohos.arkui.observer'



@Entry
@Component
struct NavigationExample {

  build() {
    Column(){
      OtherNode()
      NavigationNode()
      NavigationNode1()
    }
  }
}

@Component
struct NavigationNode {
  @Provide('pageInfos') pageInfos: NavPathStack = new NavPathStack()
  build() {
    Navigation(this.pageInfos) {
      Column() {
        Button('pushPath PageOne', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .margin(20)
          .onClick(() => {
            this.pageInfos.pushPath({ name: 'MainPageOne', param: 'MainPageOne' }) //将name指定的NavDestination页面信息入栈
          })
        Button('pushPath PageTwo', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .margin(20)
          .onClick(() => {
            this.pageInfos.pushPath({ name: 'MainPageTwo', param: 'MainPageTwo' }) //将name指定的NavDestination页面信息入栈
          })
      }
    }.title('NavIndex')
    .mode(NavigationMode.Stack)
    .id('navigation')
    .height(500)
  }
}

@Component
struct NavigationNode1 {
  @Provide('pageInfos') pageInfos: NavPathStack = new NavPathStack()
  build() {
    Navigation(this.pageInfos) {
      Column() {
        Button('pushPath PageOne', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .margin(20)
          .onClick(() => {
            this.pageInfos.pushPath({ name: 'MainPageOne', param: 'MainPageOne' }) //将name指定的NavDestination页面信息入栈
          })
        Button('pushPath PageTwo', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .margin(20)
          .onClick(() => {
            this.pageInfos.pushPath({ name: 'MainPageTwo', param: 'MainPageTwo' }) //将name指定的NavDestination页面信息入栈
          })
      }
    }.title('NavIndex')
    .mode(NavigationMode.Stack)
    .id('navigation')
    .height(500)
  }
}



@Component
struct OtherNode {
  pathStack : NavPathStack = new NavPathStack()

  aboutToAppear() {
    // query navigation info
    console.log("==================================")
    console.log("other aboutToappear")
    let navigationInfo : observer.NavigationInfo | undefined = this.queryNavigationInfo()
    console.log("获取Navigation信息"+JSON.stringify(navigationInfo))
    if (navigationInfo !== undefined) {
      this.pathStack = navigationInfo.pathStack;
    }
  }
  build() {
    Row() {
      Button('跳转到PageOne')
        .onClick(()=>{
          this.pathStack.pushPathByName('MainPageOne', 'MainPageOne')
        })
      Button('跳转到PageTwo')
        .onClick(()=>{
          this.pathStack.pushPathByName('MainPageTwo', 'MainPageTwo')
        })
    }
  }
}
