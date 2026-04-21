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
struct Options_TitleTest {
  @State message: string = 'Hello World';
  @State select: boolean = true;
  @State MenuOptions:MenuOptions = {title:undefined}
  // $r('app.media.xxx')需要替换为开发者所需的图像资源文件。
  private iconStr: ResourceStr = $r("app.media.app_icon");

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
  }

  build() {
    Scroll() {
      Column({space:5}) {
        Text('bindMenu设置options，title菜单标题,仅在content设置为Array<MenuElement> 时生效')
          .fontSize(20).fontColor(0x000020).fontWeight(FontWeight.Bold)
          .height('6%')
          .width('95%')
          .borderRadius(15)
          .backgroundColor('#ffa9cbd6')

        Text('设定bindMenu的options中title为空格').width('80%')
        Button('空格')
          .bindMenu([
            {
              value: 'Menu1',
              action: () => {
                console.info('handle Menu1 select');
              }
            },
            {
              value: 'Menu2',
              action: () => {
                console.info('handle Menu2 select');
              }
            },
          ], { title: "  " })

        Text('设定bindMenu的options中title为null').width('80%')
        Button('null')
          .bindMenu([
            {
              value: 'Menu1',
              action: () => {
                console.info('handle Menu1 select');
              }
            },
            {
              value: 'Menu2',
              action: () => {
                console.info('handle Menu2 select');
              }
            },
          ], { title: null })
      }
      .width('100%')
      .height('100%')
    }
  }
}