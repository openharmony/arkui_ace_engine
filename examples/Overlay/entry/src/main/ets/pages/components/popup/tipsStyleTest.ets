/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
export function TipsStyleBuilder(name: string, param: Object) {
  TipsStyleExample()
}

@Extend(Text) function paramTextStyle() {
  .fontSize(9)
  .width('100%')
}
@Extend(Text) function  componentTextStyle() {
  .fontSize(15)
  .backgroundColor(Color.Orange)
  .margin(3).padding(3)
  .borderWidth(1.0)
}
@Extend(Column) function columnStyle() {
  .borderWidth(1.0)
  .padding(10)
  .width('100%')
  .backgroundColor(Color.Pink)
}
@Extend(Select) function selectStyle() {
  .width('50%')
  .controlSize(ControlSize.SMALL)
  .selected(0)
  .backgroundColor(Color.Orange)
}

@Entry
@Component
struct TipsStyleExample {
  pathStack: NavPathStack = new NavPathStack()
  @State index: number[] = [0, 0, 0]
  @State bindTipsMsg: TipsMessageType = 'bindTips message'
  @State bindTipsOpt: TipsOptions = {}

  build() {
    NavDestination() {
      Column({ space: 5 }) {
        Text(`验证bindTips入参msg功能`)
          .paramTextStyle()
        Column({space: 5}){
          Text(`msg设置不同参数`)
            .paramTextStyle()
          Select([
            { value:'正常文本' },
            { value:'换行文本' },
            { value:'两行文本' },
            { value:'超长文本' },
            { value:'正常文本属性字符串' },
          ])
            .selectStyle()
            .onSelect((idx, value: string) => {
              switch (value) {
                case '正常文本':
                  this.bindTipsMsg = 'bindTips message'
                  break;
                case '换行文本':
                  this.bindTipsMsg = 'bindTips message \n'
                  break;
                case '两行文本':
                  this.bindTipsMsg = 'bindTips message '.repeat(3)
                  break;
                case '超长文本':
                  this.bindTipsMsg = 'bindTips message '.repeat(30)
                  break;
                case '正常文本属性字符串':
                  this.bindTipsMsg = new StyledString('bindTips message', [{
                    start: 0,
                    length: 9,
                    styledKey: StyledStringKey.FONT,
                    styledValue: new TextStyle({ fontColor: Color.Blue })
                  }])
                  break;
              }
            })
            .key('select_tipsMsg')

          Text(`bindTips: message`)
            .componentTextStyle()
            .bindTips(this.bindTipsMsg, {
            })
        }
        .columnStyle()

        Text(`验证bindTips入参opt的箭头相关属性`)
          .paramTextStyle()
        Column({space: 5}){
          Text(`arrow设置不同参数`)
            .paramTextStyle()
          Select([
            { value:'opt设置为{}' },
            { value:'enableArrow设置UN' },
            { value:'enableArrow设置false' },
            { value:'enableArrow设置true' },

            // 设置tips不同msg内容: tips msg/ bindTips message bindTips message
            { value:'arrowPosition设置UN' },
            { value:'arrowPosition设置Start' },
            { value:'arrowPosition设置Center' },
            { value:'arrowPosition设置End' },

            //
            { value:'arrowSize设置UN' },
            { value:'arrowSize设置w16vp/h8vp' },
            { value:'arrowSize设置w16px/h8px' },
            { value:'arrowSize设置w16lpx/h8lpx' },
            { value:'arrowSize设置w16fp/h8fp' },
            { value:'arrowSize设置w16/h8' },
            { value:'arrowSize设置w-16/h-8' },
            { value:'arrowSize设置w0/h0' },
            { value:'arrowSize设置res正常值' },
            { value:'arrowSize设置res异常值' },
            { value:'arrowSize设置w正常/h异常' },
            { value:'arrowSize设置百分比50%' },
            { value:'arrowSize设置w160vp/h8vp' },  // 所设置的气泡箭头宽度超过所在边的长度减去两倍的气泡圆角大小，则不绘制气泡箭头。
            { value:'arrowSize设置w16vp/h160vp' },  // 页面可用空间无法让气泡完全避让时，气泡会覆盖到组件上并且不显示气泡箭头。
          ])
            .selectStyle()
            .onSelect((idx, value: string) => {
              switch (value) {
                case 'opt设置为{}':
                  this.bindTipsOpt = {
                  }
                  break;
                case 'enableArrow设置UN':
                  this.bindTipsOpt = {
                    enableArrow: undefined
                  }
                  break;
                case 'enableArrow设置false':
                  this.bindTipsOpt = {
                    enableArrow: false
                  }
                  break;
                case 'enableArrow设置true':
                  this.bindTipsOpt = {
                    enableArrow: true
                  }
                  break;

                case 'arrowPosition设置UN':
                  this.bindTipsOpt = {
                    arrowPointPosition: undefined
                  }
                  break;
                case 'arrowPosition设置Start':
                  this.bindTipsOpt = {
                    arrowPointPosition: ArrowPointPosition.START
                  }
                  break;
                case 'arrowPosition设置Center':
                  this.bindTipsOpt = {
                    arrowPointPosition: ArrowPointPosition.CENTER
                  }
                  break;
                case 'arrowPosition设置End':
                  this.bindTipsOpt = {
                    arrowPointPosition: ArrowPointPosition.END
                  }
                  break;

                case 'arrowSize设置UN':
                  this.bindTipsOpt = {
                    arrowWidth: undefined,
                    arrowHeight: undefined
                  }
                  break;
                case 'arrowSize设置w16vp/h8vp':
                  this.bindTipsOpt = {
                    arrowWidth: '16vp',
                    arrowHeight: '8vp'
                  }
                  break;
                case 'arrowSize设置w16px/h8px':
                  this.bindTipsOpt = {
                    arrowWidth: '16px',
                    arrowHeight: '8px'
                  }
                  break;
                case 'arrowSize设置w16lpx/h8lpx':
                  this.bindTipsOpt = {
                    arrowWidth: '16lpx',
                    arrowHeight: '8lpx'
                  }
                  break;
                case 'arrowSize设置w16fp/h8fp':
                  this.bindTipsOpt = {
                    arrowWidth: '16fp',
                    arrowHeight: '8fp'
                  }
                  break;
                case 'arrowSize设置w16/h8':
                  this.bindTipsOpt = {
                    arrowWidth: 16,
                    arrowHeight: 8
                  }
                  break;
                case 'arrowSize设置w-16/h-8':
                  this.bindTipsOpt = {
                    arrowWidth: -16,
                    arrowHeight: -8
                  }
                  break;
                case 'arrowSize设置w0/h0':
                  this.bindTipsOpt = {
                    arrowWidth: 0,
                    arrowHeight: 0
                  }
                  break;
                case 'arrowSize设置res正常值':
                  this.bindTipsOpt = {
                    arrowWidth: $r('app.float.float_20'),
                    arrowHeight: $r('app.float.float_10')
                  }
                  break;
                case 'arrowSize设置res异常值值':
                  this.bindTipsOpt = {
                    arrowWidth: $r('app.string.EntryAbility_label'),
                    arrowHeight: $r('app.string.EntryAbility_label')
                  }
                  break;
                case 'arrowSize设置res异常值值':
                  this.bindTipsOpt = {
                    arrowWidth: $r('app.string.EntryAbility_label'),
                    arrowHeight: $r('app.string.EntryAbility_label')
                  }
                  break;
                case 'arrowSize设置w正常/h异常':
                  this.bindTipsOpt = {
                    arrowWidth: '24vp',
                    arrowHeight: $r('app.string.EntryAbility_label')
                  }
                  break;
                case 'arrowSize设置百分比50':
                  this.bindTipsOpt = {
                    arrowWidth: '50%',
                    arrowHeight: '50%'
                  }
                  break;
                case 'arrowSize设置w160vp/h8vp':
                  this.bindTipsOpt = {
                    arrowWidth: '160vp',
                    arrowHeight: '8vp'
                  }
                  break;
                case 'arrowSize设置w16vp/h160vp':
                  this.bindTipsOpt = {
                    arrowWidth: '16vp',
                    arrowHeight: '160vp'
                  }
                  break;
              }
            })
            .key('select_tipsArrow')

          Text(`bindTips: opt_arrow`)
            .componentTextStyle()
            .bindTips(this.bindTipsMsg, this.bindTipsOpt)
        }
        .columnStyle()
      }.width('100%').margin({ top: 5 })
    }
    .title('TipsStyleTest')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}