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

import { LengthUnit } from '@kit.ArkUI'
import app from '@system.app'
class ProgressModifier1 implements AttributeModifier<ProgressAttribute> {
  color: LinearGradient | ResourceColor | undefined = Color.Pink

  applyNormalAttribute(instance: ProgressAttribute): void {
    instance.color(this.color)
  }
}

class ProgressModifier2 implements AttributeModifier<ProgressAttribute> {
  color: LinearGradient | ResourceColor | undefined = undefined

  applyNormalAttribute(instance: ProgressAttribute): void {
    instance.color(this.color)
  }
}

class ProgressModifier3 implements AttributeModifier<ProgressAttribute> {
  color: LinearGradient | ResourceColor | undefined =
    new LinearGradient([{ color: Color.Red, offset: 0 }, { color: Color.Green, offset: 1 }])

  applyNormalAttribute(instance: ProgressAttribute): void {
    instance.color(this.color)
  }
}

// xxx.ets
@Entry
@Component
struct ProgressExample {
  @State modifier1: ProgressModifier1 = new ProgressModifier1();
  @State modifier2: ProgressModifier2 = new ProgressModifier2();
  @State modifier3: ProgressModifier3 = new ProgressModifier3();
  public color1: LinearGradient =
    new LinearGradient([{ color: "#65EEC9A3", offset: 0 }, { color: "#FFEF629F", offset: 1 }])
  public color2: LinearGradient =
    new LinearGradient([{ color: Color.Red, offset: 0 }, { color: Color.Green, offset: 1 }])
  public color3: LinearGradient =
    new LinearGradient([{ color: "#E5B87B", offset: 0 }, { color: "#E05F2A", offset: 1 }])
  public color4: LinearGradient =
    new LinearGradient([{ color: "#A97AE5", offset: 0 }, { color: "#A74CC2", offset: 1 }])
  public color5: LinearGradient =
    new LinearGradient([{ color: "#7E7CF4", offset: 0 }, { color: "#605EBE", offset: 1 }])
  public color6: LinearGradient =
    new LinearGradient([{ color: "#87BDF9", offset: 0 }, { color: "#3662F0", offset: 1 }])
  public color7: LinearGradient =
    new LinearGradient([{ color: "#99CD78", offset: 0 }, { color: "#53BA49", offset: 1 }])
  @State typeIndex: number =0;
  @State typeArr: (ProgressType|undefined)[]=[ProgressType.Linear,ProgressType.Ring,ProgressType.Eclipse,ProgressType.ScaleRing,ProgressType.Capsule,undefined]
  @State colorIndex: number =0;
  @State colorArr: (ResourceColor|LinearGradient|undefined)[]=[Color.Pink,this.color3,undefined]
  @State index: number = 1;

  aboutToAppear(): void {
    app.setImageCacheCount(-1);

  }
  build() {
    Scroll() {
      Column({ space: 15 }) {
        Text('ProgressType:'+this.typeIndex+',Color:'+this.colorIndex).fontSize(15).fontColor(0xCCCCCC).width('90%')
        Flex(){
          Button('切换ProgressType++')
            .onClick(()=>{
              this.typeIndex = (this.typeIndex+1)%this.typeArr.length
            })
          Button('切换ProgressType--')
            .onClick(()=>{
              this.typeIndex = (this.typeIndex-1) < 0 ? (this.typeArr.length -1) : (this.typeIndex-1)
            })
          Button('切换Color++')
            .onClick(()=>{
              this.colorIndex = (this.colorIndex+1)%this.colorArr.length
            })
          Button('切换Color--')
            .onClick(()=>{
              this.colorIndex = (this.colorIndex-1) < 0 ? (this.colorArr.length -1) : (this.colorIndex-1)
            })
        }
        Button('切换modifier')
          .onClick(()=>{
            if(this.index == 4) this.index = 0;
            if(this.index == 0) {
              this.modifier1.color = Color.Pink;
              this.index++;
            } else if(this.index == 1) {
              this.modifier1.color = undefined;
              this.index++;
            } else if(this.index == 2) {
              this.modifier1.color = this.color3;
              this.index++;
            }else if(this.index == 3) {
              this.modifier1.color = undefined;
              this.index++;
            }

          })
        Progress({ value: 30, type: this.typeArr[this.typeIndex] }).width(200)
          .style({strokeWidth:20}).color(this.colorArr[this.colorIndex])
        Text('Linear Progress').fontSize(15).fontColor(0xCCCCCC).width('90%')
        Progress({ value: 40, type: ProgressType.Linear }).width(200).color(Color.Pink)
          .style({ strokeWidth: 20 })
        Progress({ value: 30, type: ProgressType.Linear }).width(200)//.color(undefined)
          .style({ strokeWidth: 20 })
        Progress({ value: 20, total: 150, type: ProgressType.Linear }).color(this.color2).value(50).width(200)
          .style({ strokeWidth: 20 })
        Text('Linear Progress Modifier').fontSize(15).fontColor(0xCCCCCC).width('90%')
        Progress({ value: 40, type: ProgressType.Linear }).width(200).attributeModifier(this.modifier1)
          .style({ strokeWidth: 20 })
        Progress({ value: 30, type: ProgressType.Linear }).width(200).attributeModifier(this.modifier2)
          .style({ strokeWidth: 20 })
        Progress({ value: 20, total: 150, type: ProgressType.Linear })
          .value(50)
          .width(200)
          .style({ strokeWidth: 20 })
          .attributeModifier(this.modifier3)
        // .backgroundColor(Color.Transparent)

        Text('Capsule Progress').fontSize(15).fontColor(0xCCCCCC).width('90%')
        Column({ space: 40 }) {
          Flex() {
            Progress({ value: 20, type: ProgressType.Capsule })//.width(100).height(50)
            Progress({ value: 20, total: 150, type: ProgressType.Capsule })
              .color(this.color2)
              .value(20)
              //.width(100)
              //.height(50)
              //.style({ borderRadius: { value: 10, unit: LengthUnit.VP } })
            Progress({ value: 20, total: 150, type: ProgressType.Capsule })
              .color(this.color2)
              .value(50)
              //.width(100)
              //.height(50)
            Progress({ value: 20, total: 150, type: ProgressType.Capsule })
              .color(this.color2)
              .value(100)
              // .width(100)
              // .height(50)
            Progress({ value: 20, total: 150, type: ProgressType.Capsule })
              .color(this.color2)
              .value(130)
              // .width(100)
              // .height(50)
            Progress({ value: 20, total: 150, type: ProgressType.Capsule })
              .color(this.color2)
              .value(150)
              // .width(100)
              // .height(50)

          }
          Flex(){
            Progress({ value: 20, total: 150, type: ProgressType.Capsule })
              .color(this.color3)
              .value(20)
            //.width(100)
            //.height(50)
            //.style({ borderRadius: { value: 10, unit: LengthUnit.VP } })
            Progress({ value: 20, total: 150, type: ProgressType.Capsule })
              .color(this.color4)
              .value(50)
            //.width(100)
            //.height(50)
            Progress({ value: 20, total: 150, type: ProgressType.Capsule })
              .color(this.color5)
              .value(100)
            // .width(100)
            // .height(50)
            Progress({ value: 20, total: 150, type: ProgressType.Capsule })
              .color(this.color6)
              .value(130)
            // .width(100)
            // .height(50)
            Progress({ value: 20, total: 150, type: ProgressType.Capsule })
              .color(this.color7)
              .value(150)
            // .width(100)
            // .height(50)
          }
          Flex() {
            Progress({ value: 20, total: 150, type: ProgressType.Capsule })
              .color(this.color2)
              .value(20)
              .width(50)
              .height(100)
              // .style({ borderRadius: { value: 10, unit: LengthUnit.VP } })
            Progress({ value: 20, total: 150, type: ProgressType.Capsule })
              .color(this.color2)
              .value(50)
              .width(50)
              .height(100)
            Progress({ value: 20, total: 150, type: ProgressType.Capsule })
              .color(this.color2)
              .value(100)
              .width(50)
              .height(100)
            Progress({ value: 20, total: 150, type: ProgressType.Capsule })
              .color(this.color2)
              .value(130)
              .width(50)
              .height(100)
            Progress({ value: 20, total: 150, type: ProgressType.Capsule })
              .color(this.color2)
              .value(150)
              .width(50)
              .height(100)
          }
        }

        Text('Capsule Progress Modifer').fontSize(15).fontColor(0xCCCCCC).width('90%')
        Column({ space: 40 }) {
          Flex() {
            Progress({ value: 20, type: ProgressType.Capsule })
              // .width(100).height(50)
              .attributeModifier(this.modifier2)
            Progress({ value: 20, total: 150, type: ProgressType.Capsule })
              .attributeModifier(this.modifier1)
              .value(20)
              // .width(100)
              // .height(50)
            // .style({ borderRadius: { value: 10, unit: LengthUnit.VP } })
            Progress({ value: 20, total: 150, type: ProgressType.Capsule })
              .attributeModifier(this.modifier3)
              .value(50)
              // .width(100)
              // .height(50)
          }
        }

        Text('Eclipse Progress').fontSize(15).fontColor(0xCCCCCC).width('90%')
        Row({ space: 40 }) {
          Progress({ value: 10, type: ProgressType.Eclipse }).width(100)
          Progress({ value: 20, total: 150, type: ProgressType.Eclipse }).color(Color.Pink).value(50).width(100)
          Progress({ value: 40, total: 150, type: ProgressType.Eclipse }).color(this.color2).value(50).width(100)
        }

        Text('Eclipse Progress Modifier').fontSize(15).fontColor(0xCCCCCC).width('90%')
        Row({ space: 40 }) {
          Progress({ value: 10, type: ProgressType.Eclipse }).width(100).attributeModifier(this.modifier2)
          Progress({ value: 20, total: 150, type: ProgressType.Eclipse })
            .attributeModifier(this.modifier1)
            .value(50)
            .width(100)
          Progress({ value: 40, total: 150, type: ProgressType.Eclipse })
            .attributeModifier(this.modifier3)
            .value(50)
            .width(100)
        }

        Text('ScaleRing Progress').fontSize(15).fontColor(0xCCCCCC).width('90%')
        Row({ space: 40 }) {
          Progress({ value: 10, type: ProgressType.ScaleRing }).width(100)
          Progress({ value: 10, total:80, type: ProgressType.ScaleRing }).width(100)
            .style({strokeWidth:30,scaleCount:1,scaleWidth:5})
          Progress({ value: 20, total: 150, type: ProgressType.ScaleRing })
            .color(Color.Pink).value(50).width(100)
            .style({ strokeWidth: 15, scaleCount: 15, scaleWidth: 5 })
          Progress({ value: 40, total: 150, type: ProgressType.ScaleRing })
            .color(this.color2).value(50).width(100)
            .style({ strokeWidth: 15, scaleCount: 15, scaleWidth: 5 })
        }

        Text('ScaleRing Progress Modifier').fontSize(15).fontColor(0xCCCCCC).width('90%')
        Row({ space: 40 }) {
          Progress({ value: 10, type: ProgressType.ScaleRing }).width(100).attributeModifier(this.modifier2)
          Progress({ value: 20, total: 150, type: ProgressType.ScaleRing })
            .attributeModifier(this.modifier1).value(50).width(100)
            .style({ strokeWidth: 15, scaleCount: 15, scaleWidth: 5 })
          Progress({ value: 40, total: 150, type: ProgressType.ScaleRing })
            .attributeModifier(this.modifier3).value(50).width(100)
            .style({ strokeWidth: 15, scaleCount: 15, scaleWidth: 5 })
        }

        Text('Ring Progress').fontSize(15).fontColor(0xCCCCCC).width('90%')
        Row({ space: 40 }) {
          Progress({ value: 150, total: 150, type: ProgressType.Ring }).width(100)
          Progress({ value: 100, total: 150, type: ProgressType.Ring }).width(100).color(Color.Pink)
          Progress({ value: 160, total: 150, type: ProgressType.Ring })
            .color(this.color2).value(50).width(100)
            .style({ strokeWidth: 20 })
          // .backgroundColor(Color.Transparent)
        }

        Text('Ring Progress Modifier').fontSize(15).fontColor(0xCCCCCC).width('90%')
        Row({ space: 40 }) {
          Progress({ value: 150, total: 150, type: ProgressType.Ring }).width(100).attributeModifier(this.modifier2)
        Progress({ value: 100, total: 150, type: ProgressType.Ring }).width(100).attributeModifier(this.modifier1)
          Progress({ value: 160, total: 150, type: ProgressType.Ring })
            .value(50).width(100).attributeModifier(this.modifier3)
            .style({ strokeWidth: 20 })
          // .backgroundColor(Color.Transparent)
        }


      }
    }.width('100%').margin({ top: 30 })
  }
}
