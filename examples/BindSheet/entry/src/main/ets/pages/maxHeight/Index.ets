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

import { router } from '@kit.ArkUI'

@Entry
@Component
struct Index2 {
  @State isShow: boolean = false;
  @State isShow1: boolean = false;
  @State isShow2: boolean = false;
  @State isShow3: boolean = false;
  @State isShow4: boolean = false;
  @State isShow5: boolean = false;
  @State isShow6: boolean = false;

  @Builder
  myBuilder() {
    Column(){

    }.backgroundColor(Color.Pink).width('100%').height('100%')
  }

  build() {
    Scroll(){
      Column(){
        Row(){
          Text('Center样式最大高度测试1').padding({left:20}).fontColor(Color.White).fontWeight(FontWeight.Bold)
        }.height(44).width('95%').backgroundColor(Color.Blue).borderRadius(4).clickEffect({level:ClickEffectLevel.LIGHT})
        .bindSheet($$this.isShow, this.myBuilder(), {
          height: SheetSize.LARGE,
          showClose: true,
          title: { title: "半模态HOPE测试" },
          preferType: SheetType.CENTER,
        })
        .onClick(()=>{
          this.isShow = true;

        })

        Row(){
          Text('Center样式最大高度测试2').padding({left:20}).fontColor(Color.White).fontWeight(FontWeight.Bold)
        }.height(44).width('95%').backgroundColor(Color.Blue).borderRadius(4).clickEffect({level:ClickEffectLevel.LIGHT})
        .bindSheet($$this.isShow1, this.myBuilder(), {
          height: 9999,
          showClose: true,
          title: { title: "半模态HOPE测试" },
          preferType: SheetType.CENTER,
        })
        .onClick(()=>{
          this.isShow1 = true;

        })

        Row(){
          Text('PopUp样式最大高度测试1').padding({left:20}).fontColor(Color.White).fontWeight(FontWeight.Bold)
        }.height(44).width('95%').backgroundColor(Color.Blue).borderRadius(4).clickEffect({level:ClickEffectLevel.LIGHT})
        .bindSheet($$this.isShow2, this.myBuilder(), {
          height: SheetSize.LARGE,
          showClose: true,
          title: { title: "半模态HOPE测试" },
          preferType: SheetType.POPUP,
        })
        .onClick(()=>{
          this.isShow2 = true;

        })

        Row(){
          Text('PopUp样式最大高度测试2').padding({left:20}).fontColor(Color.White).fontWeight(FontWeight.Bold)
        }.height(44).width('95%').backgroundColor(Color.Blue).borderRadius(4).clickEffect({level:ClickEffectLevel.LIGHT})
        .bindSheet($$this.isShow3, this.myBuilder(), {
          height: 9999,
          showClose: true,
          title: { title: "半模态HOPE测试" },
          preferType: SheetType.POPUP,
        })
        .onClick(()=>{
          this.isShow3 = true;

        })

        Row(){
          Text('Bottom样式最大高度测试').padding({left:20}).fontColor(Color.White).fontWeight(FontWeight.Bold)
        }.height(44).width('95%').backgroundColor(Color.Blue).borderRadius(4).clickEffect({level:ClickEffectLevel.LIGHT})
        .bindSheet($$this.isShow4, this.myBuilder(), {
          height: 9999,
          showClose: true,
          title: { title: "半模态HOPE测试" },
          preferType: SheetType.BOTTOM,
        })
        .onClick(()=>{
          this.isShow4 = true;

        })

        Row(){
          Text('SIDE样式最大高度测试').padding({left:20}).fontColor(Color.White).fontWeight(FontWeight.Bold)
        }.height(44).width('95%').backgroundColor(Color.Blue).borderRadius(4).clickEffect({level:ClickEffectLevel.LIGHT})
        .bindSheet($$this.isShow5, this.myBuilder(), {
          height: 9999,
          showClose: true,
          title: { title: "半模态HOPE测试" },
          preferType: SheetType.SIDE,
        })
        .onClick(()=>{
          this.isShow5 = true;

        })

        Row(){
          Text('CONTENT_COVER样式最大高度测试').padding({left:20}).fontColor(Color.White).fontWeight(FontWeight.Bold)
        }.height(44).width('95%').backgroundColor(Color.Blue).borderRadius(4).clickEffect({level:ClickEffectLevel.LIGHT})
        .bindSheet($$this.isShow6, this.myBuilder(), {
          height: 9999,
          showClose: true,
          title: { title: "半模态HOPE测试" },
          preferType: SheetType.CONTENT_COVER,
        })
        .onClick(()=>{
          this.isShow6 = true;

        })
      }.alignItems(HorizontalAlign.Center).width('100%')
    }
  }
}

