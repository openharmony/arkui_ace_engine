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
export function BindMenuBackgroundEffectBuilder(name: string, param: Object) {
  BindMenuBackgroundEffectExample()
}

@Entry
@Component
struct BindMenuBackgroundEffectExample {
  pathStack: NavPathStack = new NavPathStack()

  build() {
    NavDestination() {
      Stack() {
        Image($r('app.media.app_icon'))
        Column() {
          Text('click for Menu')
            .fontSize('25fp')
            .fontWeight(FontWeight.Bold)
            .bindMenu([
              {
                value: 'Menu1',
                action: () => {
                  console.info('handle Menu1 select');
                }
              },
              {
                value: 'Menu2',
                action: () => {
                  console.info('handle Menu2 select');
                }
              },
            ],
              {
                backgroundBlurStyle: BlurStyle.BACKGROUND_THIN,
                backgroundEffect: {
                  radius: 60,
                  saturation: 10,
                  brightness: 1,
                  color: '#661A1A1A',
                  adaptiveColor: AdaptiveColor.AVERAGE,
                  blurOptions: { grayscale: [20, 20] }
                }
              }
            )
        }
        .width('100%')
        .margin({ top: 5 })
      }
    }
    .title('BindMenuBackgroundEffect')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}