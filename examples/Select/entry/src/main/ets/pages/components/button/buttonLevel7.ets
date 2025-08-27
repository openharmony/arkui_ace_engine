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

import { ButtonModifier } from '@ohos.arkui.modifier';
import { font, ThemeControl } from '@kit.ArkUI';

@Builder
export function ButtonLevel7Builder(name: string, param: Object) {
  ButtonLevel7Example()
}

ThemeControl.setDefaultTheme(undefined);

class MyModifier extends ButtonModifier {
  public buttonStyle1: Array<obj> = [
    {
      //0
      width: 250,
      height: 80,
      minFontScale: 0,
      maxFontScale: undefined
    },
    {
      //1
      width: 300,
      height: 90,
      type: ButtonType.ROUNDED_RECTANGLE,
      stateEffect: false,
      minFontScale: 0.5,
      maxFontScale: 0.5
    },
    {
      //2
      buttonStyle: ButtonStyleMode.TEXTUAL,
      stateEffect: undefined,
      fontColor: 0xFF8C00,
      minFontScale: 1.5,
      maxFontScale: 1.5
    },
    {
      //3
      type: ButtonType.Normal,
      buttonStyle: ButtonStyleMode.EMPHASIZED,
      stateEffect: true,
      // fontColor: Color.Red,
      minFontScale: 1,
      maxFontScale: 1
    },
    {
      //4
      type: ButtonType.Circle,
      buttonStyle: undefined,
      minFontScale: $r('app.float.float_8'),
      maxFontScale: $r('app.float.integer_145')
    },
    {
      //5
      width: 90,
      type: ButtonType.Circle
    },
    {
      //6
      fontColor: $r('app.color.fontColor'),
      buttonStyle: 0,
      minFontScale: undefined,
      maxFontScale: undefined
    },
    {
      //7
      fontColor: 'color',
      buttonStyle: 1,
      minFontScale: $r('app.integer.integer_1'),
      maxFontScale: $r('app.integer.integer_2')
    },
    {
      //8
      buttonStyle: 2,
      fontColor: Color.Red,
      minFontScale: 0.9,
      maxFontScale: 1.8
    },
    {
      //9
      fontSize: '36px',
      buttonStyle: 3
    },
    {
      //10
      buttonStyle: ButtonStyleMode.NORMAL,
      fontSize: $r('app.string.minFontSize'),
      controlSize: ControlSize.SMALL,
      fontColor: $r('app.color.selectedColor')
    },
    {
      //11
      width: 300,
      height: 90,
      type: ButtonType.Capsule,
      fontSize: '10%',
      controlSize: undefined,
      minFontScale: $r('app.float.float_80'),
      maxFontScale: $r('app.float.integer_145')
    },
    {
      //12
      fontWeight: 100,
      controlSize: ControlSize.NORMAL,
      fontColor: 'rgb(255,165,0)',
      minFontScale: -2,
      maxFontScale: 4
    },
    {
      //13
      fontWeight: 400,
      controlSize: ControlSize.SMALL,
      fontColor: Color.Red,
      maxFontScale: -4
    },
    {
      //14
      fontWeight: 900,
      controlSize: ControlSize.NORMAL,
      minFontScale: 0.9,
      maxFontScale: 2.2
    },
    {
      //15
      fontFamily: 'huawen',
      role: ButtonRole.ERROR
    },
    {
      //16
      fontFamily: 'rrfds',
      role: undefined
    },
    {
      //17
      fontFamily: 'Arial',
      role: ButtonRole.NORMAL
    },
    {
      //18
      fontStyle: FontStyle.Normal,
      role: 1
    },
    {
      //19
      fontStyle: FontStyle.Italic,
      role: 0
    },
    {
      //20
      labelStyle: {
        maxLines: 2,
        minFontSize: 15,
        maxFontSize: 50,
        font: {
          size: 14,
          weight: 100
        }
      }
    },
    {
      //21
      labelStyle: {
        maxLines: 1,
        minFontSize: $r('app.string.minFontSize'),
        maxFontSize: $r('app.string.maxFontSize'),
        font: {
          size: 20,
          weight: 700
        }
      },
      fontColor: $r('app.color.fontColor'),
    }
  ]
  public num: number = 0

  applyNormalAttribute(instance: ButtonModifier): void {
    super.applyNormalAttribute?.(instance);
  }

  public setGroup1(): void {
    this.width(this.buttonStyle1[this.num].width)
    this.height(this.buttonStyle1[this.num].height)
    this.type(this.buttonStyle1[this.num].type)
    this.stateEffect(this.buttonStyle1[this.num].stateEffect)
    this.fontFamily(this.buttonStyle1[this.num].fontFamily)
    this.buttonStyle(this.buttonStyle1[this.num].buttonStyle)
    this.controlSize(this.buttonStyle1[this.num].controlSize)
    this.role(this.buttonStyle1[this.num].role)
    this.fontSize(this.buttonStyle1[this.num].fontSize)
    this.fontColor(this.buttonStyle1[this.num].fontColor)
    this.fontWeight(this.buttonStyle1[this.num].fontWeight)
    this.fontStyle(this.buttonStyle1[this.num].fontStyle)
    this.labelStyle(this.buttonStyle1[this.num].labelStyle)
    this.minFontScale(this.buttonStyle1[this.num].minFontScale)
    this.maxFontScale(this.buttonStyle1[this.num].maxFontScale)
  }
}

interface obj {
  width ?: Length,
  height ?: Length,
  type ?: ButtonType,
  stateEffect ?: boolean,
  fontWeight ?: number | string | FontWeight,
  fontFamily ?: string | Resource,
  fontStyle ?: FontStyle,
  buttonStyle ?: ButtonStyleMode,
  controlSize ?: ControlSize,
  role ?: ButtonRole,
  fontColor ?: ResourceColor,
  fontSize ?: Length,
  labelStyle ?: LabelStyle,
  minFontScale ?: number | Resource,
  maxFontScale ?: number | Resource
}

@Entry
@Component
struct ButtonLevel7Example {
  pathStack: NavPathStack = new NavPathStack()
  @State mod1: ButtonModifier = new MyModifier()
    .width(undefined)
    .height(undefined)
    .type(undefined)
    .stateEffect(undefined)
    .fontFamily(undefined)
    .buttonStyle(undefined)
    .controlSize(undefined)
    .role(undefined)
    .fontSize(undefined)
    .fontColor(undefined)
    .fontWeight(undefined)
    .fontStyle(undefined)
    .labelStyle(undefined)
    .minFontScale(undefined)
    .maxFontScale(undefined)

  aboutToAppear() {
    (this.mod1 as MyModifier).setGroup1()
  }

  build() {
    NavDestination() {
      Column({ space: 10 }) {
        Divider()
        Row({ space: 4 }) {
          Text(`${(this.mod1 as MyModifier).num}/`)
            .fontSize('18vp')
          Text(`${(this.mod1 as MyModifier).buttonStyle1.length - 1}`)
            .fontSize('18vp')
            .key('Button14')
          Text('Test++')
            .fontSize('18vp')
            .backgroundColor(0x0000ff)
            .fontColor(0xffffff)
            .onClick(() => {
              (this.mod1 as MyModifier).num++
              if ((this.mod1 as MyModifier).num > (this.mod1 as MyModifier).buttonStyle1.length - 1) {
                (this.mod1 as MyModifier).num = 0
              }
              (this.mod1 as MyModifier).setGroup1()
            })
          Text('Test--')
            .fontSize('18vp')
            .backgroundColor(0x0000ff)
            .fontColor(0xffffff)
            .onClick(() => {
              (this.mod1 as MyModifier).num--
              if ((this.mod1 as MyModifier).num < 0) {
                (this.mod1 as MyModifier).num = (this.mod1 as MyModifier).buttonStyle1.length - 1
              }
              (this.mod1 as MyModifier).setGroup1()
            })
        }

        Divider()
        Text('Botton切换属性：1-Modifier，2-原生')
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')
        Column({ space: 10 }) {
          Button('Modifier原生对比-Modifier测试换行测试换行测试换行测试换行测试换行测试换行测试换行')
            .attributeModifier(this.mod1 as MyModifier)
          Button('Modifier原生对比-原生测试换行测试换行测试换行测试换行测试换行测试换行测试换行')
            .width((this.mod1 as MyModifier).buttonStyle1[(this.mod1 as MyModifier).num].width)
            .height((this.mod1 as MyModifier).buttonStyle1[(this.mod1 as MyModifier).num].height)
            .type((this.mod1 as MyModifier).buttonStyle1[(this.mod1 as MyModifier).num].type)
            .stateEffect((this.mod1 as MyModifier).buttonStyle1[(this.mod1 as MyModifier).num].stateEffect)
            .fontFamily((this.mod1 as MyModifier).buttonStyle1[(this.mod1 as MyModifier).num].fontFamily)
            .buttonStyle((this.mod1 as MyModifier).buttonStyle1[(this.mod1 as MyModifier).num].buttonStyle)
            .controlSize((this.mod1 as MyModifier).buttonStyle1[(this.mod1 as MyModifier).num].controlSize)
            .role((this.mod1 as MyModifier).buttonStyle1[(this.mod1 as MyModifier).num].role)
            .fontSize((this.mod1 as MyModifier).buttonStyle1[(this.mod1 as MyModifier).num].fontSize)
            .fontColor((this.mod1 as MyModifier).buttonStyle1[(this.mod1 as MyModifier).num].fontColor)
            .fontWeight((this.mod1 as MyModifier).buttonStyle1[(this.mod1 as MyModifier).num].fontWeight)
            .fontStyle((this.mod1 as MyModifier).buttonStyle1[(this.mod1 as MyModifier).num].fontStyle)
            .labelStyle((this.mod1 as MyModifier).buttonStyle1[((this.mod1 as MyModifier)).num].labelStyle)
            .minFontScale((this.mod1 as MyModifier).buttonStyle1[(this.mod1 as MyModifier).num].minFontScale)
            .maxFontScale((this.mod1 as MyModifier).buttonStyle1[(this.mod1 as MyModifier).num].maxFontScale)
          Button('原生不设置最大最小倍数测试换行测试换行试换行测试换行测试换行')
            .width((this.mod1 as MyModifier).buttonStyle1[(this.mod1 as MyModifier).num].width)
            .height((this.mod1 as MyModifier).buttonStyle1[(this.mod1 as MyModifier).num].height)
            .type((this.mod1 as MyModifier).buttonStyle1[(this.mod1 as MyModifier).num].type)
            .stateEffect((this.mod1 as MyModifier).buttonStyle1[(this.mod1 as MyModifier).num].stateEffect)
            .fontFamily((this.mod1 as MyModifier).buttonStyle1[(this.mod1 as MyModifier).num].fontFamily)
            .buttonStyle((this.mod1 as MyModifier).buttonStyle1[(this.mod1 as MyModifier).num].buttonStyle)
            .controlSize((this.mod1 as MyModifier).buttonStyle1[(this.mod1 as MyModifier).num].controlSize)
            .role((this.mod1 as MyModifier).buttonStyle1[(this.mod1 as MyModifier).num].role)
            .fontSize((this.mod1 as MyModifier).buttonStyle1[(this.mod1 as MyModifier).num].fontSize)
            .fontColor((this.mod1 as MyModifier).buttonStyle1[(this.mod1 as MyModifier).num].fontColor)
            .fontWeight((this.mod1 as MyModifier).buttonStyle1[(this.mod1 as MyModifier).num].fontWeight)
            .fontStyle((this.mod1 as MyModifier).buttonStyle1[(this.mod1 as MyModifier).num].fontStyle)
            .labelStyle((this.mod1 as MyModifier).buttonStyle1[((this.mod1 as MyModifier)).num].labelStyle)
        }
        .height(100)

      }
      .width('100%')
    }
    .title('ButtonLevel7')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}