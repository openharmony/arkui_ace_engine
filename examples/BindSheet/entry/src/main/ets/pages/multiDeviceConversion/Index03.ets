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
struct Index03 {

  @State isShow1: boolean = false;
  @State isShow2: boolean = false;
  private modalTransitionArr:ModalTransition[] = [ModalTransition.DEFAULT, ModalTransition.NONE, ModalTransition.ALPHA];
  private modalTransitionArrStr:string[] = ['ModalTransition.DEFAULT', 'ModalTransition.NONE', 'ModalTransition.ALPHA'];
  @State modalTransitionIndex:number = 0;

  private preferTypeArr:SheetType[] = [SheetType.BOTTOM, SheetType.CONTENT_COVER];
  private preferTypeArrStr:string[] = ['BOTTOM', 'CONTENT_COVER'];
  @State preferTypeIndex:number = 0;

  @State dismissState:boolean = false;

  private page1WidthArr:number[] = [400, 300];
  @State page1WidthIndex:number = 0;

  @Builder
  myBuilder2() {
    Column() {
      Button('Close Page 2')
        .fontSize(20)
        .margin({ top: 10, bottom: 10 })
        .onClick(()=>{
          this.isShow2 = false;
        })

      Text('Page1 Setting').fontSize(20).margin({ bottom: 5 })

      Button('bindSheet page style: ' + this.preferTypeArrStr[this.preferTypeIndex])
        .fontSize(20)
        .margin({ bottom: 10 })
        .onClick(() => {
          this.preferTypeIndex = ++this.preferTypeIndex % this.preferTypeArr.length;
        })
    }
    .width('100%')
    .height('100%')
  }

  @Builder
  myBuilder1() {
    Column() {
      Button('Close Page 1')
        .fontSize(20)
        .margin({ top: 10, bottom: 5 })
        .onClick(()=>{
          this.isShow1 = false;
        })

      Button('Show Page 2')
        .fontSize(20)
        .margin({ bottom: 10 })
        .onClick(() => {
          this.isShow2 = true;
        })
        .bindSheet(this.isShow2, this.myBuilder2(), {
          height: '600vp',
          width: '300vp',
          preferType: SheetType.BOTTOM,
          detents: ['600vp'],
          dragBar: true,
          title: { title: 'Page2', subtitle: 'bindSheet'},
          backgroundColor: Color.Gray
        })

      Text('Page1 Setting').fontSize(20).margin({ bottom: 5 })

      Button('bindSheet page style: ' + this.preferTypeArrStr[this.preferTypeIndex])
        .fontSize(20)
        .margin({ bottom: 5 })
        .onClick(() => {
          this.preferTypeIndex = ++this.preferTypeIndex % this.preferTypeArr.length;
        })

      Button('allow to close bindSheet: ' + (this.dismissState ? 'allow' : 'not allow'))
        .fontSize(20)
        .margin({ bottom: 5 })
        .onClick(() => {
          this.dismissState = !this.dismissState;
        })

      Button('Page1 width: ' + this.page1WidthArr[this.page1WidthIndex])
        .fontSize(20)
        .margin({ bottom: 5 })
        .onClick(() => {
          this.page1WidthIndex = ++this.page1WidthIndex % this.page1WidthArr.length;
        })
    }
    .width('100%')
    .height('100%')
  }

  build() {
    Row(){
      Column(){
        Button('Show Page 1')
          .fontSize(20)
          .onClick(() => {
            this.isShow1 = true;
          })
          .bindSheet(this.isShow1, this.myBuilder1(), {
            height: '100vp',
            width: this.page1WidthArr[this.page1WidthIndex],
            preferType: this.preferTypeArr[this.preferTypeIndex],
            detents: [SheetSize.MEDIUM, SheetSize.LARGE],
            dragBar: true,
            title: { title: 'Page1', subtitle: 'bindSheet'},
            radius: { topLeft: 0 },
            borderWidth: 10,
            borderColor: Color.Pink,
            borderStyle: BorderStyle.Solid,
            showClose: true,
            shadow: {
              radius: 100
            },
            blurStyle: BlurStyle.COMPONENT_ULTRA_THIN,
            maskColor: Color.Yellow,
            modalTransition: this.modalTransitionArr[this.modalTransitionIndex],
            shouldDismiss: (sheetDismiss: SheetDismiss) => {
              console.log('[TEST INFO] [Page1] shouldDismiss(dismiss)');
              if (this.dismissState == true) {
                console.log('[TEST INFO] [Page1] shouldDismiss(dismiss) Begin');
                sheetDismiss.dismiss();
                console.log('[TEST INFO] [Page1] shouldDismiss(dismiss) End');
              }
            },
            onWillDismiss: (dismissContentCoverAction: DismissContentCoverAction) => {
              if (dismissContentCoverAction.reason == DismissReason.PRESS_BACK) {
                console.log('[TEST INFO] [Page1] onWillDismiss PRESS_BACK');
              } else if (dismissContentCoverAction.reason == DismissReason.CLOSE_BUTTON) {
                console.log('[TEST INFO] [Page1] onWillDismiss CLOSE_BUTTON');
              } else {
                console.log('[TEST INFO] [Page1] onWillDismiss Other');
              }
              if (this.dismissState == true) {
                console.log('[TEST INFO] [Page1] onWillDismiss(dismiss) Begin');
                dismissContentCoverAction.dismiss();
                console.log('[TEST INFO] [Page1] onWillDismiss(dismiss) End');
              }
            },
            onHeightDidChange: (height: number)=>{
              console.log('[TEST INFO] [Page1] onHeightDidChange: %d', height);
            },
            onDetentsDidChange: (height: number)=>{
              console.log('[TEST INFO] [Page1] onDetentsDidChange: %d', height);
            },
            onWidthDidChange: (width: number)=>{
              console.log('[TEST INFO] [Page1] onWidthDidChange: %d', width);
            },
            onTypeDidChange: (type: SheetType)=>{
              console.log('[TEST INFO] [Page1] onTypeDidChange: %d', type);
            },
            backgroundColor: Color.Gray,
            onWillAppear: ()=>{
              console.log('[TEST INFO] [Page1] onWillAppear');
            },
            onAppear: ()=>{
              console.log('[TEST INFO] [Page1] onAppear');
            },
            onWillDisappear: ()=>{
              console.log('[TEST INFO] [Page1] onWillDisappear');
            },
            onDisappear: ()=>{
              console.log('[TEST INFO] [Page1] onDisappear');
            }
          })

        Row(){
          Button('bindSheet transition mode: ' + this.modalTransitionArrStr[this.modalTransitionIndex])
            .onClick(()=>{
              this.modalTransitionIndex = ++this.modalTransitionIndex % this.modalTransitionArr.length;
            })
        }.margin({ top: 10, bottom: 10 })
      }
      .width('100%')
    }
    .height('100%')
  }
}