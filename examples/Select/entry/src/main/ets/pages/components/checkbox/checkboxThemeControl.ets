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
import { Theme, ThemeControl, CustomColors, CustomTheme } from '@kit.ArkUI';

// Custom color resources
export class AppColors implements CustomColors {
  //checkbox stroke color use this resource
  public iconOnPrimary?: ResourceColor | undefined = Color.Black
  //Checkbox unselected color use this resource
  public iconFourth?: ResourceColor | undefined = Color.Orange
  //Checkbox selected color use this resource
  public compBackgroundEmphasize?: ResourceColor | undefined = Color.Green
}

// Customized theme object
export class AppTheme implements CustomTheme {
  public colors: AppColors = new AppColors();
}

// Creating a global topic instance
export let gAppTheme: CustomTheme = new AppTheme();

ThemeControl.setDefaultTheme(gAppTheme);

@Builder
export function CheckboxThemeControlBuilder(name: string, param: Object) {
  CheckboxThemeControlExample()
}

@Component
struct CheckboxThemeControlExample {
  pathStack: NavPathStack = new NavPathStack()
  @State selectedColor: ResourceColor = Color.Blue;

  // Listening topic changes
  onWillApplyTheme(theme: Theme) {
    this.selectedColor = theme.colors.interactiveSelect;
  }

  build() {
    NavDestination() {
      Column() {
        Text('期望：Checkbox默认拥有黑色的对勾，橘色的未选中边框，')
          .margin({ top: 100, bottom: 100 })

        Checkbox()
          .select(true)

      }.width('100%')
    }
    .title('CheckboxSize')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}

export { CheckboxThemeControlExample };