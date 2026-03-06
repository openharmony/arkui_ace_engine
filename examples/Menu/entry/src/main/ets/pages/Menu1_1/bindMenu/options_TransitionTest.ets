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
struct options_TransitionTest {
  private iconStr: ResourceStr = $r("app.media.app_icon");
  private iconStr2: ResourceStr = $r("app.media.app_icon");
  @Builder
  SubMenu() {
    Menu() {
      MenuItem({ content: "复制", labelInfo: "Ctrl+C" })
      MenuItem({ content: "粘贴", labelInfo: "Ctrl+V" })
    }.transition(TransitionEffect.SLIDE_SWITCH)
  }

  @Builder
  MyMenu1(){
    Menu() {
      MenuItem({ startIcon: $r("app.media.app_icon"), content: "菜单选项" })
      MenuItem({ startIcon: $r("app.media.app_icon"), content: "菜单选项" })
        .enabled(false)
      MenuItem({
        startIcon: this.iconStr,
        content: "菜单选项1",
        endIcon: this.iconStr2,
        builder: ():void=>this.SubMenu()
      })
      MenuItemGroup({ header: '小标题' }) {
        MenuItem({
          startIcon: this.iconStr,
          content: "菜单选项2",
          endIcon: this.iconStr2,
          builder: ():void=>this.SubMenu()
        })
        MenuItem({
          startIcon: $r("app.media.app_icon"),
          content: "菜单选项3",
          endIcon: this.iconStr2,
          builder: ():void=>this.SubMenu()
        })
      }
      MenuItem({
        startIcon: this.iconStr,
        content: "菜单选项",
      })
    }
  }
  build() {
      Scroll(){
        Column({space:5}) {
          Text('bindMenu通过配置transition，实现自定义菜单以及菜单预览时的显示和退出动效')
            .fontSize(20).fontColor(0x000020).fontWeight(FontWeight.Bold)
            .height('10%')
            .width('95%')
            .borderRadius(15)
            .backgroundColor('#ffa9cbd6')
          Text('js')
          Button('menu')
            .margin({ top: 10 })
            .bindMenu(this.MyMenu1, {
              // transition: TransitionEffect.SLIDE_SWITCH
              transition: TransitionEffect.asymmetric(TransitionEffect.OPACITY
                .animation({ duration: 3000, curve: Curve.Sharp })
                .combine(TransitionEffect.scale({ x: 1.5, y: 1.5 })
                  .animation({ duration: 3000, curve: Curve.Sharp })),
                TransitionEffect.OPACITY.animation({ duration: 100, curve: Curve.Smooth })
                  .combine(TransitionEffect.scale({ x: 0.5, y: 0.5 })
                    .animation({ duration: 100, curve: Curve.Smooth })))
            })
        }
      }
  }
}