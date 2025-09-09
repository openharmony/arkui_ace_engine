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
import { LengthMetrics } from '@kit.ArkUI'

@Entry
@Component
struct BorderExample {
  @State isShow:boolean = false
  @State isShow2:boolean = false
  @State isShow3:boolean = false
  @State isShow4:boolean = false

  @State borderColors: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined = Color.Black
  @State borderStyles: BorderStyle | EdgeStyles | undefined = BorderStyle.Solid
  @State borderWidths: Dimension | EdgeWidths | LocalizedEdgeWidths | undefined = 0
  @State sheetRadius: LengthMetrics | BorderRadiuses | LocalizedBorderRadiuses | undefined =  LengthMetrics.vp(0)

  @Builder myBuilder4() {
    Column({space: 10}) {
      Button('BorderRadiuses，not available in mirrors')
        .onClick(()=>{
          this.sheetRadius = {
            topLeft: 20,
            topRight: 0,
            bottomLeft: 20,
            bottomRight: 0,
          };
        })
      Text('topLeft = bottomLeft = 20vp').fontSize(10).fontWeight(FontWeight.Bold)
        .margin(5)
      Text('topRight = bottomRight = 0vp').fontSize(10).fontWeight(FontWeight.Bold)
        .margin({bottom: 15})

      Button('LocalizedBorderRadiuses，available in mirrors')
        .onClick(()=>{
          this.sheetRadius = {
            topStart: LengthMetrics.vp(40),
            topEnd: LengthMetrics.vp(20),
            bottomStart: LengthMetrics.vp(40),
            bottomEnd: LengthMetrics.vp(20)
          };
        })
      Text('topStart = bottomStart = 40vp').fontSize(10).fontWeight(FontWeight.Bold)
        .margin(5)
      Text('topEnd = bottomEnd = 20vp').fontSize(10).fontWeight(FontWeight.Bold)
        .margin({bottom: 15})

      Button('sheetRadius = undefined')
        .onClick(()=>{
          this.sheetRadius = undefined;
        })
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }


  @Builder myBuilder3() {
    Column({space: 10}) {
      Button('ResourceColor-Color')
        .onClick(()=>{
          this.borderColors = Color.Pink;
        })
      Button('ResourceColor-number')
        .onClick(()=>{
          this.borderColors = 0x008000;
        })
      Button('ResourceColor-string')
        .onClick(()=>{
          this.borderColors = 'rgba(255, 100, 255, 0.5)';
        })
      Button('ResourceColor-Resource')
        .onClick(()=>{
          this.borderColors = $r('app.color.start_color_purple');
        })
      Button('EdgeColors')
        .onClick(()=>{
          this.borderColors = {
            top: 0xffff00,
            right: '#ff00ff',
            left: 'rgb(255, 100, 255)',
            bottom: $r('app.color.start_color_red'),
          };
        })
      Text('left: rgb(255, 100, 255)').fontSize(10).fontWeight(FontWeight.Bold)
        .margin(5)
      Text('right: #ff00ff').fontSize(10).fontWeight(FontWeight.Bold)
        .margin({ bottom: 15} )

      Text('LocalizedEdgeColor，available in mirrors')
        .fontSize(10).fontColor(0xFFFFFF).fontWeight(FontWeight.Bold).textAlign(TextAlign.Center)
        .width('100%').height(50).backgroundColor('#2ebd82')
      Button('LocalizedEdgeColors')
        .onClick(()=>{
          this.borderColors = {
            top: '#ffff0000',
            end: $r('app.color.start_color_purple'),
            bottom: Color.Yellow,
            start: $r('app.color.start_color_blue')
          };
        })
      Text('start: blue').fontSize(10).fontWeight(FontWeight.Bold)
      Text('end: purple').fontSize(10).fontWeight(FontWeight.Bold)

      Button('borderColors = undefined')
        .onClick(()=>{
          this.borderColors = undefined;
        })
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }

  @Builder myBuilder2() {
    Column({space: 10}) {
      Text('BorderStyle，not available in mirrors')
        .fontSize(10).fontColor(0xFFFFFF).fontWeight(FontWeight.Bold).textAlign(TextAlign.Center)
        .width('100%').height(50).backgroundColor('#2ebd82')
      Button('EdgeStyle')
        .onClick(()=>{
          this.borderStyles = {
            top: BorderStyle.Dotted,
            right: BorderStyle.Dashed,
            bottom: BorderStyle.Solid,
            left: BorderStyle.Solid
          };
        })

      Button('BorderStyle-Dotted')
        .onClick(()=>{
          this.borderStyles = BorderStyle.Dotted;
        })
      Button('BorderStyle-Dashed')
        .onClick(()=>{
          this.borderStyles = BorderStyle.Dashed;
        })
      Button('BorderStyle-Solid')
        .onClick(()=>{
          this.borderStyles = BorderStyle.Solid;
        })

      Button('borderStyles = undefined')
        .onClick(()=>{
          this.borderStyles = undefined;
        })
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }

  @Builder myBuilder() {
    Column({space: 10}) {
      Button('Dimension-PX')
        .onClick(()=>{
          this.borderWidths = '4px';
        })
      Button('Dimension-VP')
        .onClick(()=>{
          this.borderWidths = 5;
        })
      Button('Dimension-FP')
        .onClick(()=>{
          this.borderWidths = '8fp';
        })
      Button('Dimension-LPX')
        .onClick(()=>{
          this.borderWidths = '6lpx';
        })
      Button('Dimension-Percentage')
        .onClick(()=>{
          this.borderWidths = '2%';
        })
      Button('Dimension-Resource')
        .onClick(()=>{
          this.borderWidths = $r('app.float.borderWidth1');
        })
      Button('EdgeWidths1')
        .onClick(()=>{
          this.borderWidths = {
            top: '24px',
            right: '2%',
            bottom: 3,
            left: $r('app.float.borderWidth1')
          };
        })
      Text('LocalizedEdgeWidth，available in mirrors')
        .fontSize(10).fontColor(0xFFFFFF).fontWeight(FontWeight.Bold).textAlign(TextAlign.Center)
        .width('100%').height(50).backgroundColor('#2ebd82')
      Button('LocalizedEdgeWidths1')
        .onClick(()=>{
          this.borderWidths = {
            top: LengthMetrics.px(18),
            end: LengthMetrics.vp(12),
            bottom: LengthMetrics.fp(7),
            start: LengthMetrics.lpx(14),
          };
        })
      Text('start: 14vp ').fontSize(10).fontWeight(FontWeight.Bold)
        .margin(5)
      Text('end: 12vp').fontSize(10).fontWeight(FontWeight.Bold)
        .margin({bottom: 15})

      Button('LocalizedEdgeWidths2')
        .onClick(()=>{
          this.borderWidths = {
            top: LengthMetrics.px(4),
            end: LengthMetrics.vp(4),
            bottom: LengthMetrics.fp(4),
            start: LengthMetrics.percent(0.04),
          };
        })
      Text('start: 0.04 ').fontSize(10).fontWeight(FontWeight.Bold)
        .margin(5)
      Text('end: 4vp').fontSize(10).fontWeight(FontWeight.Bold)
        .margin({bottom: 15})

      Button('borderWidths = undefined')
        .onClick(()=>{
          this.borderWidths = undefined;
        })
    }
    .width('100%')
    .justifyContent(FlexAlign.Center)
  }

  build() {
    Column() {
      Text($r('app.string.SideSheet3'))
        .fontSize(22).fontColor(0xFFFFFF).fontWeight(FontWeight.Bold).textAlign(TextAlign.Center)
        .width('100%').height(50).backgroundColor('#2ebd82')
        .margin(50)

      Text('has no right border，mirroring has no left border')
        .fontSize(22).fontColor(0xFFFFFF).fontWeight(FontWeight.Bold).textAlign(TextAlign.Center)
        .width('100%').height(50).backgroundColor('#2ebd82')

      Button('borderWidth')
        .onClick(() => {
          this.isShow = true
        })
        .fontSize(20)
        .margin(10)
        .bindSheet(
          $$this.isShow,
          this.myBuilder(),
          {
            title: { title: 'SideSheet', subtitle: 'borderWidth' },
            preferType: SheetType.SIDE,
            borderWidth: this.borderWidths,
            borderColor: Color.Red
          })

      Button('borderStyle')
        .onClick(() => {
          this.isShow2 = true
        })
        .fontSize(20)
        .margin(10)
        .bindSheet(
          $$this.isShow2,
          this.myBuilder2(),
          {
            title: { title: 'SideSheet', subtitle: 'borderStyle, 6vp border' },
            preferType: SheetType.SIDE,
            borderStyle: this.borderStyles,
            borderColor: Color.Pink,
            borderWidth: 6
          })

      Button('borderColor')
        .onClick(() => {
          this.isShow3 = true
        })
        .fontSize(20)
        .margin(10)
        .bindSheet(
          $$this.isShow3,
          this.myBuilder3(),
          {
            title: { title: 'SideSheet', subtitle: 'borderColor, 6vp border' },
            preferType: SheetType.SIDE,
            borderColor: this.borderColors,
            borderWidth: 6
          })

      Text('left radius in default，mirroring is the opposite')
        .fontSize(22).fontColor(0xFFFFFF).fontWeight(FontWeight.Bold).textAlign(TextAlign.Center)
        .width('100%').height(50).backgroundColor('#2ebd82')
      Button('radius')
        .onClick(() => {
          this.isShow4 = true
        })
        .fontSize(20)
        .margin(10)
        .bindSheet(
          $$this.isShow4,
          this.myBuilder4(),
          {
            title: { title: 'SideSheet', subtitle: 'radius' },
            preferType: SheetType.SIDE,
            radius: this.sheetRadius,
          })
    }
    .justifyContent(FlexAlign.Center)
    .backgroundColor(Color.White)
    .width('100%')
    .height('100%')
  }
}