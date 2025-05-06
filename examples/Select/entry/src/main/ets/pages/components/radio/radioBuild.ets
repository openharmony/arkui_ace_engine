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

@Builder
export function RadioBuildBuilder(name: string, param: Object) {
  RadioBuildExample()
}

class MyRadioStyle implements ContentModifier<RadioConfiguration> {
  public type: number = 0
  public selectedColor: Color = Color.Black

  constructor(numberType: number, colorType: Color) {
    this.type = numberType
    this.selectedColor = colorType
  }

  applyContent(): WrappedBuilder<[RadioConfiguration]> {
    return wrapBuilder(buildRadio)
  }
}

@Builder
function buildRadio(config: RadioConfiguration) {
  Row({ space: 30 }) {
    Circle({ width: 50, height: 50 })
      .stroke(Color.Black)
      .fill(config.checked ? (config.contentModifier as MyRadioStyle).selectedColor : Color.White)
    Button(config.checked ? 'off' : 'on')
      .width(100)
      .type(config.checked ? (config.contentModifier as MyRadioStyle).type : ButtonType.Normal)
      .backgroundColor(0xAABBCC)
      .onClick(() => {
        if (config.checked) {
          config.triggerChange(false)
        } else {
          config.triggerChange(true)
        }
      })
  }
}

@Entry
@Component
struct RadioBuildExample {
  pathStack: NavPathStack = new NavPathStack()

  build() {
    NavDestination() {
      Column({ space: 50 }) {
        Row() {
          Radio({ value: 'Radio1', group: 'radioGroup' })
            .contentModifier(new MyRadioStyle(1, Color.Red))
            .checked(false)
            .width(300)
            .height(100)
        }

        Row() {
          Radio({ value: 'Radio2', group: 'radioGroup' })
            .checked(true)
            .width(300)
            .height(60)
            .contentModifier(new MyRadioStyle(2, Color.Red))
        }
      }
    }
    .title('RadioBuild')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}

export { RadioBuildExample }