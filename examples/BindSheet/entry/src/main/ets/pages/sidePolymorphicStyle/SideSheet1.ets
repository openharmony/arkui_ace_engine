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
@Entry
@Component
struct BlurExample {
  @State isShow:boolean = false
  @State isShow2:boolean = false
  @State isShow3:boolean = false

  @State blurStyle: BlurStyle = BlurStyle.Thin
  @State shadows: ShadowStyle|ShadowOptions|undefined = undefined
  @State maskColor: ResourceColor = Color.Pink

  @Builder myBuilder() {
    Column({space: 10}) {
      Button('close sheet')
        .onClick(()=>{
          this.isShow = false;
        })
      Button('COMPONENT_ULTRA_THIN')
        .onClick(()=>{
          this.blurStyle = BlurStyle.COMPONENT_ULTRA_THIN;
        })
      Button('COMPONENT_THIN')
        .onClick(()=>{
          this.blurStyle = BlurStyle.COMPONENT_THIN;
        })
      Button('COMPONENT_REGULAR')
        .onClick(()=>{
          this.blurStyle = BlurStyle.COMPONENT_REGULAR;
        })
      Button('COMPONENT_THICK')
        .onClick(()=>{
          this.blurStyle = BlurStyle.COMPONENT_THICK;
        })
      Button('COMPONENT_ULTRA_THICK')
        .onClick(()=>{
          this.blurStyle = BlurStyle.COMPONENT_ULTRA_THICK;
        })
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }

  @Builder ShadowBuilder() {
    Column({space: 5}) {
      Button('ShadowStyle-OUTER_DEFAULT_SM')
        .margin({top: 10})
        .onClick(() => {
          this.shadows = ShadowStyle.OUTER_DEFAULT_SM
        })
      Button('ShadowStyle-OUTER_DEFAULT_MD')
        .onClick(() => {
          this.shadows = ShadowStyle.OUTER_DEFAULT_MD
        })
      Button('ShadowStyle-OUTER_DEFAULT_LG')
        .onClick(() => {
          this.shadows = ShadowStyle.OUTER_DEFAULT_LG
        })

      Button('ShadowOptions-OUTER_FLOATING_SM')
        .onClick(() => {
          this.shadows = ShadowStyle.OUTER_FLOATING_SM
        })
      Button('ShadowOptions-OUTER_FLOATING_MD')
        .onClick(() => {
          this.shadows = ShadowStyle.OUTER_FLOATING_MD
        })
      Button('ShadowOptions1')
        .onClick(() => {
          this.shadows = {
            radius: 2,
            type: ShadowType.COLOR,
            color: '#ff00ff',
            offsetX: 2,
            offsetY: 4,
            fill: false
          }
        })
      Button('ShadowOptions2')
        .onClick(() => {
          this.shadows = {
            radius: $r('app.float.shadow_radius'),
            type: ShadowType.BLUR,
            color: ColoringStrategy.AVERAGE,
            offsetX: $r('app.float.shadow_offsetX'),
            offsetY: $r('app.float.shadow_offsetY'),
            fill: true
          }
        })
      Button('ShadowOptions3')
        .onClick(() => {
          this.shadows = {
            radius: 30,
            type: ShadowType.COLOR,
            color: Color.Red,
            offsetX: -20,
            offsetY: -20,
            fill: false
          }
        })
      Button('ShadowOptions4')
        .onClick(() => {
          this.shadows = {
            radius: 30,
            type: ShadowType.BLUR,
            color: 0x008000,
            offsetX: -20,
            offsetY: -20,
            fill: false
          }
        })
    }
  }

  @Builder maskColorBuilder() {
    Column({space: 5}) {
      Button('maskColor-0xffff00')
        .onClick(()=>{
          this.maskColor = 0xffff00
        })

      Button('maskColor-0x008000')
        .onClick(()=>{
          this.maskColor = 0x008000
        })

      Button('maskColor-string-rgb')
        .onClick(()=>{
          this.maskColor = 'rgb(255, 100, 255)'
        })

      Button('maskColor-string-rgba')
        .onClick(()=>{
          this.maskColor = 'rgba(255, 100, 255, 0.5)'
        })

      Button('maskColor-string-#ff00ff')
        .onClick(()=>{
          this.maskColor = '#ff00ff'
        })

      Button('maskColor-Resource-#ff00ff')
        .onClick(()=>{
          this.maskColor = $r('app.color.start_color_purple')
        })

      Button('maskColor-Resource-#ffff0000')
        .onClick(()=>{
          this.maskColor = $r('app.color.start_color_red')
        })
      Button('close sheet')
        .onClick(()=>{
          this.isShow3 = false;
        })
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }

  build() {
    Column({space: 10}) {
      Text($r('app.string.SideSheet2'))
        .fontSize(22).fontColor(0xFFFFFF).fontWeight(FontWeight.Bold).textAlign(TextAlign.Center)
        .width('100%').height(50).backgroundColor('#2ebd82')

      Button('SideSheet With Shadow')
        .onClick(() => {
          this.isShow2 = true
        })
        .bindSheet(
          $$this.isShow2,
          this.ShadowBuilder(),
          {
            title: { title: 'title', subtitle: 'subtitle' },
            preferType: SheetType.SIDE,
            shadow: this.shadows,
          })

      Button('SideSheet With BlurStyle')
        .onClick(() => {
          this.isShow = true
        })
        .bindSheet(
          $$this.isShow,
          this.myBuilder(),
          {
            title: { title: 'title', subtitle: 'subtitle' },
            preferType: SheetType.SIDE,
            blurStyle: this.blurStyle
          })

      Button('SideSheet With maskColor')
        .onClick(() => {
          this.isShow3 = true
        })
        .bindSheet(
          $$this.isShow3,
          this.maskColorBuilder(),
          {
            title: { title: 'title', subtitle: 'subtitle' },
            preferType: SheetType.SIDE,
            maskColor: this.maskColor,
          })
    }
    .justifyContent(FlexAlign.Center)
    .backgroundColor(Color.White)
    .width('100%')
    .height('100%')
  }
}