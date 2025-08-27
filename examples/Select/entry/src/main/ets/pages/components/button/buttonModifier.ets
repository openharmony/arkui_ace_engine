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

export class DefaultButtonModifier implements AttributeModifier<ButtonAttribute> {
  private buttonType: ButtonType = ButtonType.Normal;
  private stateEffectValue: boolean = true;
  private fontSize: number = 16
  private height: number = 42
  private width: number | string = '100%'
  private borderRadius: number = 4

  constructor() {
  }

  applyNormalAttribute(instance: ButtonAttribute): void {
    instance.stateEffect(this.stateEffectValue);
    instance.type(this.buttonType);
    instance.width(this.width);
    instance.height(this.height);
    instance.fontSize(this.fontSize)
    instance.borderRadius(this.borderRadius)
  }

  stateEffect(enable: boolean): DefaultButtonModifier {
    this.stateEffectValue = enable;
    return this;
  }
}

@Builder
export function ButtonModifierBuilder(name: string, param: Object) {
  ButtonModifierExample()
}

@Entry
@Component
struct ButtonModifierExample {
  @State btnEnabled: boolean = false
  private defaultButtonModifier: DefaultButtonModifier = new DefaultButtonModifier()
  pathStack: NavPathStack = new NavPathStack()

  build() {
    NavDestination() {
      Column() {
        Text('观测点：点击后，按钮不可用，且圆角不发生变化')
        Button('按钮样式bug')
          .attributeModifier(this.defaultButtonModifier)
          .enabled(!this.btnEnabled).onClick(() => {
          this.btnEnabled = !this.btnEnabled
        })
      }
      .padding({ top: 100 })
    }
    .title('ButtonModifier')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}

export { ButtonModifierExample };