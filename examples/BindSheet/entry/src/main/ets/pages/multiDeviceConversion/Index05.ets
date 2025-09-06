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
struct Index05 {
  @State isShow1: boolean = false;
  @State modalTransitionIndex:number = 0;

  private preferTypeArr:SheetType[] = [SheetType.BOTTOM, SheetType.CONTENT_COVER];
  private preferTypeArrStr:string[] = ['BOTTOM', 'CONTENT_COVER'];
  @State preferTypeIndex:number = 0;

  @Builder
  myBuilder1() {
    Column() {
      Button('Close Page 1')
        .fontSize(20)
        .margin({ top: 10, bottom: 5 })
        .onClick(()=>{
          this.isShow1 = false;
        })

      Text('Page1 Setting').fontSize(20).margin({ bottom: 5 })

      Button('bindSheet page style: ' + this.preferTypeArrStr[this.preferTypeIndex])
        .fontSize(20)
        .margin({ bottom: 5 })
        .onClick(() => {
          this.preferTypeIndex = ++this.preferTypeIndex % this.preferTypeArr.length;
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
            uiContext: this.getUIContext(),
            height: '100vp',
            width: '400vp',
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
            backgroundColor: Color.Gray
          })
      }
      .width('100%')
    }
    .height('100%')
  }
}