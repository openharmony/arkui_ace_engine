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
export function MenuTestLevel01Builder(name: string, param: Object) {
  MenuTestLevel01Example()
}

class BuilderOptions1 {
  public width?: Length = '240'
  public height?: Length = '300'
}

@Extend(Text)
function paramTextStyle1() {
  .fontSize(11)
  .width('100%')
}

@Extend(Text)
function subParamTextStyle1() {
  .fontSize(13)
  .width('100%')
  .borderWidth(1.0)
  .backgroundColor(Color.Orange)
}

@Entry
@Component
struct MenuTestLevel01Example {
  pathStack: NavPathStack = new NavPathStack()
  private scroller: Scroller = new Scroller()

  //Menu菜单：设置不同的高度、宽度
  @Builder
  MenuBuilder($$: BuilderOptions1) {
    Menu() {
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
    }
    .backgroundColor('#3300ffff')
    .borderWidth(1.0)
    .height($$.height)
    .width($$.width)
  }

  //自定义菜单：设置不同高度、宽度
  @Builder
  MenuCustomBuilder($$: BuilderOptions1) {
    Scroll(this.scroller) {
      Column()
        .backgroundColor(Color.Orange)
        .height('100%')
        .width('100%')
        .borderRadius(20)
        .borderWidth(1.0)
    }
    .margin(20)
    .height($$.height)
    .width($$.width)
  }

  build() {
    NavDestination() {
      Scroll(this.scroller) {
        Column({ space: 10 }) {
          Text('bindContextMenu的菜单绘制：')
            .paramTextStyle1()
            .margin({ top: 5 })
          Column({ space: 5 }) {
            Text('自定义菜单')
              .paramTextStyle1()
            Text('正常自定义菜单')
              .subParamTextStyle1()
              .bindContextMenu(this.MenuCustomBuilder({ width: 200, height: 300 }), ResponseType.LongPress)
            Text('高度为0的自定义菜单')//builder父容器高度为0，因为设置了外边距，显示为上下外边距+UX外边距的高度
              .subParamTextStyle1()
              .bindContextMenu(this.MenuCustomBuilder({ width: 120, height: 0 }), ResponseType.LongPress)
            Text('超短自定义菜单')//菜单的绘制位置和方式：预期避让且高度有限制
              .subParamTextStyle1()
              .bindContextMenu(this.MenuCustomBuilder({ width: 200, height: 30 }), ResponseType.LongPress)
            Text('超长自定义菜单')//菜单的绘制位置和方式：预期避让且高度有限制
              .subParamTextStyle1()
              .bindContextMenu(this.MenuCustomBuilder({ width: 200, height: 1080 }), ResponseType.LongPress)
            Text('窄自定义菜单')//菜单的绘制：预期正常宽度绘制
              .subParamTextStyle1()
              .bindContextMenu(this.MenuCustomBuilder({ width: 60, height: 300 }), ResponseType.LongPress)
            Text('宽自定义菜单')//菜单的绘制：预期有最大宽度限制，按照最大宽度绘制，超出部分剪裁
              .subParamTextStyle1()
              .bindContextMenu(this.MenuCustomBuilder({ width: 600, height: 300 }), ResponseType.LongPress)
            Text('尺寸百分比自定义菜单')//菜单的绘制：预期有最大宽度限制，按照最大宽度绘制，超出部分剪裁
              .subParamTextStyle1()
              .bindContextMenu(this.MenuCustomBuilder({ width: '100%', height: '100%' }), ResponseType.LongPress)

            Text('Menu菜单')
              .paramTextStyle1()
            Text('正常Menu菜单')
              .subParamTextStyle1()
              .bindContextMenu(this.MenuBuilder({ width: 200, height: 300 }), ResponseType.LongPress)
            Text('宽度为0的自定义菜单')//builder父容器宽度为0：预期极小宽度的一个长条
              .subParamTextStyle1()
              .bindContextMenu(this.MenuCustomBuilder({ width: 0, height: 300 }), ResponseType.LongPress)
            Text('超短Menu菜单')
              .subParamTextStyle1()
              .bindContextMenu(this.MenuBuilder({ width: 200, height: 30 }), ResponseType.LongPress)
            Text('超长Menu菜单')
              .subParamTextStyle1()
              .bindContextMenu(this.MenuBuilder({ width: 200, height: 1080 }), ResponseType.LongPress)
            Text('窄Menu菜单')
              .subParamTextStyle1()
              .bindContextMenu(this.MenuBuilder({ width: 30, height: 300 }), ResponseType.LongPress)
            Text('宽Menu菜单')
              .subParamTextStyle1()
              .bindContextMenu(this.MenuBuilder({ width: 600, height: 300 }), ResponseType.LongPress)
            Text('自定义尺寸Menu菜单')
              .subParamTextStyle1()
              .bindContextMenu(this.MenuBuilder({ width: '100%', height: '100%' }), ResponseType.LongPress)
          }
          .backgroundColor(Color.Pink)
          .width('100%')
          .padding(5)
          .borderWidth(1.0)
        }
        .width('100%')
        .padding(10)
      }
      .align(Alignment.Top)
      .height('100%')
      .width('100%')
    }
    .title('MenuTestLevel01')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}