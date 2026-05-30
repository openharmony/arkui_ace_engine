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
import curves from '@ohos.curves';
import { Route, RouteGroup } from './common/Index';
import { KeyboardAvoidMode } from '@kit.ArkUI';
import router from '@ohos.router';

@Styles
function cardPressedStyle() {
  .backgroundColor('rgba(0,0,0,0.1)')
  .opacity(1)
  .animation({ curve: curves.cubicBezierCurve(0.33, 0, 0.67, 1), duration: 100 })
}

@Styles
function cardNormalStyle() {
  .backgroundColor('rgba(0,0,0,0)')
  .opacity(1)
  .animation({ curve: curves.cubicBezierCurve(0.33, 0, 0.67, 1), duration: 100 })
}

@Styles
function cardDisabledStyle() {
  .backgroundColor('rgba(0,0,0,0)')
  .opacity(0.5)
  .animation({ curve: curves.cubicBezierCurve(0.33, 0, 0.67, 1), duration: 100 })
}


@Entry
@Component
struct ComponentExtension {
  @Provide('router') router: NavPathStack = new NavPathStack();
  @State routes: RouteGroup[] = [
    {
      name: 'StateStyle',
      // 请将$r('app.string.StateStyles')替换为实际资源文件，在本示例中该资源文件的value值为"基础场景"
      label: $r('app.string.StateStyles'),
      // 请将$r('app.string.StateStylesExample')替换为实际资源文件，在本示例中该资源文件的value值为"基础场景示例"
      children: [
        { name: 'StateStylesSample', label: $r('app.string.StateStylesExample') },
      ]
    },
    {
      name: 'NormalStyle',
      // 请将$r('app.string.MyComponent')替换为实际资源文件，在本示例中该资源文件的value值为"按压态"
      label: $r('app.string.MyComponent'),
      children: [
        // 请将$r('app.string.MyComponentExample')替换为实际资源文件，在本示例中该资源文件的value值为"按压态示例"
        { name: 'MyComponent', label: $r('app.string.MyComponentExample') },
      ]
    },
    {
      name: 'FocusStyle',
      // 请将$r('app.string.CompWithInlineStateStyles')替换为实际资源文件，在本示例中该资源文件的value值为"获焦变色"
      label: $r('app.string.CompWithInlineStateStyles'),
      children: [
        // 请将$r('app.string.CompWithInlineStateStylesExample')替换为实际资源文件，在本示例中该资源文件的value值为"获焦变色示例"
        { name: 'CompWithInlineStateStyles', label: $r('app.string.CompWithInlineStateStylesExample') },
      ]
    }
  ];
  @State selection: string | null = null;

  @Builder
  ListItemGroupHeader(route: RouteGroup) {
    Row() {
      Text(route.label)
        .fontColor($r('sys.color.ohos_id_color_text_primary'))
        .fontWeight(FontWeight.Medium)

      Blank()

      Text(`${route.children.length}`)
        .fontColor($r('sys.color.ohos_id_color_text_secondary'))
        .opacity(this.selection === route.name ? 0 : 1)

      Image($r('sys.media.ohos_ic_public_arrow_right'))
        .fillColor($r('sys.color.ohos_id_color_fourth'))
        .height(24)
        .width(24)
        .rotate({ angle: this.selection === route.name ? 90 : 0 })
        .animation({ curve: curves.interpolatingSpring(0, 1, 228, 30) })
    }
    .borderRadius(20)
    .width('100%')
    .padding(8)
    .enabled(!!route.children.length)
    .stateStyles({
      pressed: cardPressedStyle,
      normal: cardNormalStyle,
      disabled: cardDisabledStyle,
    })
    .onClick(() => {
      animateTo(
        { curve: curves.interpolatingSpring(0, 1, 228, 25) },
        () => {
          if (this.selection === route.name) {
            this.selection = null;
          } else {
            this.selection = route.name;
          }
        });
    })
  }

  aboutToAppear(): void{
    this.getUIContext().setKeyboardAvoidMode(KeyboardAvoidMode.RESIZE);
  }
  build() {
    Column() {
      Text('ComponentExtension')
      List() {
        ForEach(this.routes, (routeGroup: RouteGroup) => {
          ListItemGroup({
            header: this.ListItemGroupHeader(routeGroup),
            style: ListItemGroupStyle.CARD,
          }) {
            if (routeGroup.name === this.selection) {
              ForEach(routeGroup.children, (route: Route) => {
                ListItem() {
                  Row() {
                    Text(route.label).fontSize(16)
                    Blank()
                    Image($r('sys.media.ohos_ic_public_arrow_right'))
                      .fillColor($r('sys.color.ohos_id_color_fourth'))
                      .height(24)
                      .width(24)
                  }
                  .stateStyles({
                    pressed: cardPressedStyle,
                    normal: cardNormalStyle,
                    disabled: cardDisabledStyle,
                  })
                  .borderRadius(20)
                  .padding(8)
                  .transition(
                    TransitionEffect.OPACITY.animation({
                      curve: curves.interpolatingSpring(0, 1, 228, 30)
                    })
                  )
                  .width('100%')
                  .onClick(() => {
                    const name = `pages/${routeGroup.name}/${route.name}`;
                    this.getUIContext().getRouter().pushUrl({url: name});
                  })
                }
                .width('100%')
              })
            }
          }
          .padding(2)
          .divider({ strokeWidth: 0.5 })
        })
      }.padding({bottom: 10})
    }
  }
}