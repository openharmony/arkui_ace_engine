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
import router from '@ohos.router';

interface ListCategories {
  title:string,
  url:string
}

@Entry
@Component
struct NavigationTest2 {
  @State message: string = 'Navigation支持转场衔接共享元素动画'
  private items : ListCategories[] = [
    {title:'1 测试不同共享元素动画时长和组件上下树时长;\n' +
      '单个关闭系统动画接口，pageOne跳转pageTwo动画时间为1000，pageone中的navdestination组件下树时间为1000；' +
      '\npageTwo跳转pageOne动画时间为1000，pagetwo中的navdestination组件下树时间为300',url:'pages/SharingAnimation/Test1'},

    {title:'2 测试不同共享元素动画时长和组件上下树时长;\n' +
      '单个关闭系统动画接口，pageOne跳转pageTwo动画时间为500，pageone中的navdestination组件下树时间为800；\n' +
      'pageTwo跳转pageOne动画时间为1000，pagetwo中的navdestination组件下树时间为1000',url:'pages/SharingAnimation/Test2'},

    {title:'3 测试同时开启系统默认转场动画和用户自定义共享元素动画;\n' +
      '单个开启系统动画接口，pageOne跳转pageTwo动画时间为1000，pageone中的navdestination组件下树时间为1000；' +
      '\npageTwo跳转pageOne动画时间为1000，pagetwo中的navdestination组件下树时间为300',url:'pages/SharingAnimation/Test3'},

    {title:'4 测试同时开启系统默认转场动画和用户自定义共享元素动画;\n' +
      '单个开启系统动画接口，pageOne跳转pageTwo动画时间为500，pageone中的navdestination组件下树时间为800；' +
      '\npageTwo跳转pageOne动画时间为1000，pagetwo中的navdestination组件下树时间为1000',url:'pages/SharingAnimation/Test4'},

    {title:'5 Dialog页面测试不同共享元素动画时长和组件上下树时长;\n' +
      'navdestination页面为dialog类型，pageOne跳转pageTwo动画时间为1000，pageone中的navdestination组件下树时间为1000；\n' +
      'pageTwo跳转pageOne动画时间为1000，pagetwo中的navdestination组件下树时间为300',url:'pages/SharingAnimation/Test5'},

    {title:'6 Dialog页面测试不同共享元素动画时长和组件上下树时长;\n' +
      'pushPath不设置animated，默认为true，navdestination页面为dialog类型，pageOne跳转pageTwo动画时间为500，pageone中的navdestination组件下树时间为800；\n' +
      'pageTwo跳转pageOne动画时间为1000，pagetwo中的navdestination组件下树时间为1000',url:'pages/SharingAnimation/Test6'},

    {title:'7 给animateTo设置动画效果，规格应该不生效;\n' +
      '单个关闭系统动画接口，在animateTo下加入不同动画参数，pageOne跳转pageTwo动画时间为1000，pageone中的navdestination组件下树时间为1000；\n' +
      'pageTwo跳转pageOne动画时间为1000，pagetwo中的navdestination组件下树时间为300;\n' +
      'animateTo中设置动画时间为1000，curve: Curve.EaseOut,iterations: 0, playMode: PlayMode.Normal',url:'pages/SharingAnimation/Test7'},

    {title:'8 测试NavPathStack路由接口中的animated参数;\n' +
      '在animateTo下加入不同动画参数，pageOne跳转pageTwo动画时间为1000，pageone中的navdestination组件下树时间为1000；\n' +
      'pageTwo跳转pageOne动画时间为1000，pagetwo中的navdestination组件下树时间为1000' ,url:'pages/SharingAnimation/Test8'},

    {title:'9 测试不同共享元素动画时长和组件上下树时长;\n' +
      '在animateTo下加入不同动画参数，pageOne跳转pageTwo动画时间为1000，pageone中的navdestination组件下树时间为0；\n' +
      'pageTwo跳转pageOne动画时间为1000，pagetwo中的navdestination组件不设置transition' ,url:'pages/SharingAnimation/Test9'},


  ]

  build() {
    Column() {
      Text(this.message).fontSize(22).fontColor(0xFFFFFF).fontWeight(FontWeight.Bold).textAlign(TextAlign.Center).width('100%').height(50).backgroundColor("#1770b9")
      List({space:'10vp'}) {
        ForEach(this.items,(item : ListCategories) => {
          ListItem() {

            Text(item.title)
              .width('90%')
              .padding(20)
              .backgroundColor(Color.Pink)
              .onClick(() => {
                router.pushUrl({url:item.url})
              })

          }
        })
      }.alignListItem(ListItemAlign.Center).margin({top:'10vp'}).width('100%').height('90%')
    }.width('100%').height('100%').backgroundColor(0xE0FFFF)
  }
}