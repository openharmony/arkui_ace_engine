/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import router from '@ohos.router';

interface ListCategories {
  title:string,
  utl:string
}

interface obj {
  height?: number | string,
  isSupportAvoidance?: boolean
}

@Entry
@Component
struct Index50019 {
  private items : ListCategories[] = [
    {title:'TextInput',utl:'pages/50019/TextInput2'},
    {title:'TextArea',utl:'pages/50019/TextArea2'},
    {title:'Search',utl:'pages/50019/Search2'},
    {title:'多个输入框',utl:'pages/50019/page1'},
    {title:'TextArea高度整屏',utl:'pages/50019/page2'},
    {title:'自定义弹窗search',utl:'pages/50019/page3'},
    {title:'自定义弹窗TextInput',utl:'pages/50019/page4'},
    {title:'自定义弹窗TextArea',utl:'pages/50019/page5'},
    {title:'安全区域延伸顶部TextInput',utl:'pages/50019/page6'},
    {title:'安全区域延伸顶部TextArea',utl:'pages/50019/page7'},
    {title:'安全区域延伸顶部Search',utl:'pages/50019/page8'},
    {title:'子窗口',utl:'pages/50019/page9'},
  ]
  @State height1: number | string = 0
  @State isSupportAvoidance: boolean = true
  @State obj: obj = {
    height: 0,
    isSupportAvoidance: true
  }

  build() {
    Column() {

      Text(JSON.stringify(this.obj)).margin({top:10})
      Row() {
        Button('顶部')
          .width('30%')
          .onClick(() => {
            this.height1 = 0
            this.obj = {
              height: this.height1,
              isSupportAvoidance: this.isSupportAvoidance
            }
          })

        Button('中部')
          .width('30%')
          .onClick(() => {
            this.height1 = '63%'
            this.obj = {
              height: this.height1,
              isSupportAvoidance: this.isSupportAvoidance
            }
          })

        Button('底部')
          .width('30%')
          .onClick(() => {
            this.height1 = '80%'
            this.obj = {
              height: this.height1,
              isSupportAvoidance: this.isSupportAvoidance
            }
          })

      }.margin({top:10})

      Row() {
        Button('isSupportAvoidance:' + this.isSupportAvoidance)
          .width('80%')
          .onClick((event: ClickEvent) => {
            this.isSupportAvoidance = !this.isSupportAvoidance
            this.obj = {
              height: this.height1,
              isSupportAvoidance: this.isSupportAvoidance
            }
          })
      }.margin({ top:10 })


      List({space:'10vp'}) {
        ForEach(this.items,(item : ListCategories) => {
          ListItem() {
            Text(item.title).fontSize(16).fontWeight(FontWeight.Bold).onClick(() => {
              router.pushUrl({url:item.utl , params:  this.obj })
            })
          }.width('90%').height('40vp').backgroundColor('#ff53ecd9').borderRadius(10)
        })
      }.alignListItem(ListItemAlign.Center).margin({top:'10vp'}).width('100%').height('90%')
    }.width('100%').height('100%')
  }
}