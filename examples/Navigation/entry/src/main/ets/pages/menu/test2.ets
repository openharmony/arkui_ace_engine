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

import { BusinessError, Callback } from '@ohos.base';
import { JSON } from '@kit.ArkTS';
import observer from '@ohos.arkui.observer';

class DerivedNavPathStack extends NavPathStack {
  id: string = '__default__'

  setId(id: string) {
    this.id = id;
  }

  getInfo(): string {
    return 'this page used Derived NavPathStack, id: ' + this.id
  }

  pushPath(info: NavPathInfo): void
  pushPath(info: NavPathInfo, animated?: boolean): void
  pushPath(info: NavPathInfo, animated?: boolean): void {
    super.pushPath(info, animated);
  }

  pushPathByName1(name: string, param: ESObject , animated?: boolean): void {
    super.pushPathByName(name, param, animated);
  }

  pushPathByName2(name: string, param: ESObject, onPop:Callback<PopInfo>, animated?: boolean): void {
    super.pushPathByName(name, param, onPop, animated);
  }

  pushDestination(info: NavPathInfo): Promise<void>
  pushDestination(info: NavPathInfo, animated?: boolean): Promise<void>
  pushDestination(info: NavPathInfo, animated?: boolean): Promise<void> {
    return super.pushDestination(info, animated);
  }

  pushDestinationByName1(name: string, param: Object, animated?: boolean ): Promise<void> {
    return super.pushDestinationByName(name, param, animated);
  }

  pushDestinationByName2(name: string, param: Object, onPop:Callback<PopInfo>, animated?: boolean): Promise<void> {
    return super.pushDestinationByName(name, param, onPop, animated);
  }

  replacePath(info: NavPathInfo): void
  replacePath(info: NavPathInfo, animated?: boolean ): void
  replacePath(info: NavPathInfo, animated?: boolean ): void {
    super.replacePath(info, animated);
  }

  replacePathByName(name: string, param: Object, animated?: boolean): void {
    super.replacePathByName(name, param, animated);
  }

  removeByIndexes(indexes: Array<number>): number {
    return super.removeByIndexes(indexes);
  }

  removeByName(name: string): number {
    return super.removeByName(name);
  }

  pop(animated?: boolean | undefined): NavPathInfo | undefined
  pop(result: Object, animated?: boolean | undefined): NavPathInfo | undefined
  pop(result?: Object, animated?: boolean | undefined): NavPathInfo | undefined {
    return super.pop(result, animated);
  }


  popToName(name: string, animated?: boolean): number
  popToName(name: string, result: Object, animated?: boolean): number
  popToName(name: string, result?: Object, animated?: boolean): number {
    return super.popToName(name, result, animated);
  }

  popToIndex(index: number, animated?: boolean): void
  popToIndex(index: number, result: Object, animated?: boolean): void
  popToIndex(index: number, result?: Object, animated?: boolean):void {
    super.popToIndex(index, result, animated);
  }

  moveToTop(name: string, animated?: boolean): number {
    return super.moveToTop(name, animated);
  }

  moveIndexToTop(index: number, animated?: boolean): void {
    super.moveIndexToTop(index, animated);
  }

  clear(animated?: boolean): void {
    super.clear(animated);
  }

  getAllPathName(): Array<string> {
    return super.getAllPathName();
  }

  getParamByIndex(index: number): ESObject | undefined {
    return super.getParamByIndex(index);
  }

  getParamByName(name: string): Array<ESObject> {
    return super.getParamByName(name);
  }

  getIndexByName(name: string): Array<number> {
    return super.getIndexByName(name);
  }

  size(): number {
    return super.size();
  }

  disableAnimation(value: boolean): void {
    super.disableAnimation(value);
  }

  getParent(): NavPathStack | null {
    return super.getParent();
  }

  setInterception(interception: NavigationInterception): void {
    super.setInterception(interception);
  }

  pushAndPopIndex(): void {
    super.pushPathByName('pageOne', new param('ok'));
    super.pushPathByName('pageOne', new param('ok'));
    super.pushPathByName('pageOne', new param('ok'));
    super.pushPathByName('pageOne', new param('ok'));
    super.pushPathByName('pageOne', new param('ok'));
    super.popToIndex(1);
  }

  pushAndReplace(): void {
    super.pushPathByName('pageOne', new param('ok'));
    super.replacePathByName('pageTwo', new param('ok'));
  }
}

class param {
  info: string = 'default_param';
  constructor(info: string) { this.info = info }
}

@Entry
@Component
struct Index11432 {
  derivedStack: DerivedNavPathStack = new DerivedNavPathStack();
  @State disableAnimationValue: boolean = true

  @State modeValue: NavigationMode[] = [ NavigationMode.Stack,  NavigationMode.Split,  NavigationMode.Auto]
  @State modeValueIndex: number = 0
  @State modeValueStr: string[] = ['NavigationMode.Stack', 'NavigationMode.Split', 'NavigationMode.Auto']

  navDesUpdateCallback(info: NavDestinationInfo) {
    console.log(`navDesUpdateCallback, info: ${JSON.stringify(info)}`);
  }

  observerOn(){
    observer.on('navDestinationUpdate', this.navDesUpdateCallback);
  }

  observerOff(){
    observer.off('navDestinationUpdate', this.navDesUpdateCallback);
  }

  @Builder
  pageMap(name: string) {
    if (name === 'pageOne') {
      PageOne()
    } else if (name === 'pageTwo') {
      PageTwo()
    } else if (name === 'pageThree') {
      PageThree()
    }
  }
  @Styles buttonStyles() {
    .margin(2)
    .padding(2)
    .height(26)
  }

  @State text : string = ''

  build() {
    Column({space:5}){
      Row({space:5}){
        Button('observer.on')
          .buttonStyles()
          .fontSize(10)
          .onClick(() => {
            this.observerOn()
          })

        Button('observer.off')
          .buttonStyles()
          .fontSize(10)
          .onClick(() => {
            this.observerOff()
          })
      }

      Button('mode:' + this.modeValueStr[this.modeValueIndex] )
        .buttonStyles()
        .fontSize(10)
        .onClick(()=>{
          this.modeValueIndex ++
          if(this.modeValueIndex > this.modeValue.length -1 ){
            this.modeValueIndex = 0
          }
        })

      Flex({wrap: FlexWrap.Wrap}){
        Button('pushPath pageOne')
          .buttonStyles()
          .fontSize(10)
          .onClick(() => {
            this.derivedStack.pushPath({ name: 'pageOne', param: new param('ok') }, true)
          })

        Button('pushPathByName pageTwo')
          .buttonStyles()
          .fontSize(10)
          .onClick(() => {
            this.derivedStack.pushPathByName1('pageTwo', new param('ok'), false)
          })

        Button('pushPathByName(onPop) pageThree')
          .buttonStyles()
          .fontSize(10)
          .onClick(()=>{
            this.derivedStack.pushPathByName2('pageThree', new param('ok'), (popInfo) => {
              console.log('[pushPathByName(onPop)]last page is: ' + popInfo.info.name + ', result: ' + JSON.stringify(popInfo.result))
            })
          })

        Button('pushDestination pageOne')
          .buttonStyles()
          .fontSize(10)
          .onClick(()=>{
            this.derivedStack.pushDestination({ name: 'pageOne',param:new param('ok')  })
              .catch((error: BusinessError)=>{
                console.error(`[pushDestination]failed, error code = ${error.code}, error.message = ${error.message}.`);
              }).then(()=>{
              console.error('[pushDestination]success.');
            });
          })


        Button('pushDestinationByName pageOne')
          .buttonStyles()
          .fontSize(10)
          .onClick(()=>{
            this.derivedStack.pushDestinationByName1('pageOne',new param('ok'))
              .catch((error: BusinessError)=>{
                console.error(`[pushDestinationByName]failed, error code = ${error.code}, error.message = ${error.message}.`);
              }).then(()=>{
              console.error('[pushDestinationByName]success.');
            });
          })


        Button('pushDestinationByName(onPop) pageOne')
          .buttonStyles()
          .fontSize(10)
          .onClick(()=>{
            this.derivedStack.pushDestinationByName2('pageOne',new param('ok'), (popInfo) => {
              console.log('[pushDestinationByName(onPop)]last page is: ' + popInfo.info.name + ', result: ' + JSON.stringify(popInfo.result))
            })
              .catch((error: BusinessError)=>{
                console.error(`[pushDestinationByName(onPop)]failed, error code = ${error.code}, error.message = ${error.message}.`);
              }).then(()=>{
              console.error('[pushDestinationByName(onPop)]success.');
            });
          })

        Button('replacePath pageTwo')
          .buttonStyles()
          .fontSize(10)
          .onClick(()=>{
            this.derivedStack.replacePath({name:'pageTwo', param:new param('ok')})
          })

        Button('replacePathByName pageTwo')
          .buttonStyles()
          .fontSize(10)
          .onClick(()=>{
            this.derivedStack.replacePathByName('pageTwo',new param('ok'))
          })

        Button('removeByIndexes [1]')
          .buttonStyles()
          .fontSize(10)
          .onClick(()=>{
            let mes = this.derivedStack.removeByIndexes([1])
            console.log('removeByIndexes return :' + mes)
          })

        Button('removeByName pageOne')
          .buttonStyles()
          .fontSize(10)
          .onClick(()=>{
            let mes = this.derivedStack.removeByName('pageOne')
            console.log('removeByName return :' + mes)
          })

        Button('pop')
          .buttonStyles()
          .fontSize(10)
          .onClick(()=>{
            this.derivedStack.pop()
          })


        Button('pop(result)')
          .buttonStyles()
          .fontSize(10)
          .onClick(()=>{
            let mes = this.derivedStack.pop(new param('pop ok'), true)
            if (mes) {
              console.log('pop(result) return :' + JSON.stringify(mes))
            }
          })

        Button('popToName pageOne')
          .buttonStyles()
          .fontSize(10)
          .onClick(()=>{
            let mes = this.derivedStack.popToName('pageOne')
            console.log('popToName return :' + mes)
          })

        Button('popToName(result) pageOne')
          .buttonStyles()
          .fontSize(10)
          .onClick(()=>{
            let mes = this.derivedStack.popToName('pageOne', new param('pop ok'))
            console.log('popToName(result) return :' + mes)
          })

        Button('popToIndex 0')
          .buttonStyles()
          .fontSize(10)
          .onClick(()=>{
            this.derivedStack.popToIndex(0)
          })

        Button('popToIndex(result) 0')
          .buttonStyles()
          .fontSize(10)
          .onClick(()=>{
            this.derivedStack.popToIndex(0, new param('pop ok'))
          })

        Button('moveToTop pageOne')
          .buttonStyles()
          .fontSize(10)
          .onClick(()=>{
            let mes = this.derivedStack.moveToTop('pageOne')
            console.log('moveToTop return :' + mes)
          })

        Button('moveIndexToTop 0')
          .buttonStyles()
          .fontSize(10)
          .onClick(()=>{
            this.derivedStack.moveIndexToTop(0)
          })

        Button('clear')
          .buttonStyles()
          .fontSize(10)
          .onClick(()=>{
            this.derivedStack.clear()
          })

        Button('getAllPathName')
          .buttonStyles()
          .fontSize(10)
          .onClick(()=>{
            let mes = JSON.stringify(this.derivedStack.getAllPathName())
            console.log('getAllPathName return :' + mes)
            this.text = 'getAllPathName return :' + mes
          })



        Button('getParamByIndex 0')
          .buttonStyles()
          .fontSize(10)
          .onClick(()=>{
            let mes:ESObject = this.derivedStack.getParamByIndex(0)
            if(mes instanceof  Object) {
              console.log('getParamByIndex return :' + JSON.stringify(mes))
              this.text = 'getParamByIndex return :' +  JSON.stringify(mes)
            } else {
              console.log('getParamByIndex return :' +mes)
              this.text = 'getParamByIndex return :' +  mes
            }
          })

        Button('getParamByName pageOne')
          .buttonStyles()
          .fontSize(10)
          .onClick(()=>{
            let mes = JSON.stringify(this.derivedStack.getParamByName('pageOne'))
            console.log('getParamByName return :' + mes)
            this.text = 'getParamByName return :' + mes
          })

        Button('getIndexByName pageOne')
          .buttonStyles()
          .fontSize(10)
          .onClick(()=>{
            let mes = JSON.stringify(this.derivedStack.getIndexByName('pageOne'))
            console.log('getIndexByName return :' + mes)
            this.text = 'getIndexByName return :' + mes
          })

        Button('size')
          .buttonStyles()
          .fontSize(10)
          .width(100)
          .onClick(()=>{
            let mes = this.derivedStack.size()+ ''
            console.log('size:' + mes)
            this.text = 'size return :' + mes
          })

        Button('disableAnimation ' + this.disableAnimationValue)
          .key('disableAnimation')
          .buttonStyles()
          .fontSize(10)
          .onClick(()=>{
            this.disableAnimationValue = !this.disableAnimationValue
            this.derivedStack.disableAnimation(this.disableAnimationValue)
          })

        Button('getParent')
          .buttonStyles()
          .fontSize(10)
          .onClick(()=>{
            let stack = this.derivedStack.getParent()
            if(stack){
              stack.clear()
            } else {
              console.log('getParent return :' + this.derivedStack.getParent())
            }
          })

        Button(`jump pageTwo，willShow，to dialog，pushPath to pageThree`, { stateEffect: true, type: ButtonType.Capsule })
          .buttonStyles()
          .fontSize(10)
          .onClick(()=>{
            this.derivedStack.setInterception({
              willShow: (from: NavDestinationContext | 'navBar', to: NavDestinationContext | 'navBar', operation: NavigationOperation, animated: boolean) => {
                if (typeof to === 'string') {
                  console.log('target page is navigation home');
                  return;
                }
                let target: NavDestinationContext = to as NavDestinationContext;
                if (target.pathInfo.name === 'pageTwo') {
                  target.pathStack.pop();
                  AlertDialog.show(
                    {
                      title: 'dialog',
                      message: 'text',
                      autoCancel: true,
                      alignment: DialogAlignment.Bottom,
                      offset: { dx: 0, dy: -20 },
                      gridCount: 3,
                      confirm: {
                        value: 'confirm',
                        action: () => {
                          target.pathStack.pushPath({ name:'pageThree',param:new param('ok') })
                          console.info('Button-clicking callback')
                        }
                      },
                    }
                  )

                }
                console.log(`will show`)
              },
              didShow:(from: NavDestinationContext | 'navBar', to: NavDestinationContext | 'navBar', operation: NavigationOperation, animated: boolean) => {
                console.log(`did show`)
              },

              modeChange: (mode: NavigationMode) => {
                console.log(`current navigation mode is ${mode}`);
              }
            });
            this.derivedStack.pushPath({name:'pageTwo', param:new param('ok')})
          })


        Button(`jump pageTwo，didShow，to dialog，pushPath to pageThree`, { stateEffect: true, type: ButtonType.Capsule })
          .buttonStyles()
          .fontSize(10)
          .onClick(()=>{
            this.derivedStack.setInterception({
              willShow:(from: NavDestinationContext | 'navBar', to: NavDestinationContext | 'navBar', operation: NavigationOperation, animated: boolean) => {
                console.log(`will show`)
              },

              didShow: (from: NavDestinationContext | 'navBar', to: NavDestinationContext | 'navBar', operation: NavigationOperation, animated: boolean) => {
                if (typeof to === 'string') {
                  console.log('target page is navigation home');
                  return;
                }
                let target: NavDestinationContext = to as NavDestinationContext;
                if (target.pathInfo.name === 'pageTwo') {
                  target.pathStack.pop();
                  AlertDialog.show(
                    {
                      title: 'dialog',
                      message: 'text',
                      autoCancel: true,
                      alignment: DialogAlignment.Bottom,
                      offset: { dx: 0, dy: -20 },
                      gridCount: 3,
                      confirm: {
                        value: 'confirm',
                        action: () => {
                          target.pathStack.pushPath({ name:'pageThree',param:new param('ok') })
                          console.info('Button-clicking callback')
                        }
                      },
                    }
                  )

                }
                console.log(`will show`)
              },
              modeChange: (mode: NavigationMode) => {
                console.log(`current navigation mode is ${mode}`);
              }
            });
            this.derivedStack.pushPath({name:'pageTwo', param:new param('ok')})
          })

        Button('pushAndPopIndex')
          .buttonStyles()
          .fontSize(10)
          .onClick(()=>{
            this.derivedStack.pushAndPopIndex()
          })

        Button('pushAndReplace')
          .buttonStyles()
          .fontSize(10)
          .onClick(()=>{
            this.derivedStack.pushAndReplace()
          })
      }
      .width('100%').height('55%').borderWidth(1).borderColor('#ffe20ea6')

      Text(this.text)

      Navigation(this.derivedStack) {
      }
      .borderWidth(1)
      .height('30%')
      .title('Navigation')
      .minContentWidth(50)
      .navDestination(this.pageMap)
      .mode(this.modeValue[this.modeValueIndex])
      .navBarWidthRange(['240vp','432vp'])
    }

  }
}

@Component
struct PageOne {
  derivedStack: DerivedNavPathStack = new DerivedNavPathStack();
  curStringifyParam: string = '';
  build() {
    NavDestination() {
      Column({space:10}) {
      }
    }
    .title('pageOne')
    .backgroundColor(Color.Pink)
    .onReady((context: NavDestinationContext) => {
      console.log('pageOne onReady');
      this.derivedStack = context.pathStack as DerivedNavPathStack;
    })
    .onBackPressed(() => {
      console.log(`pageOne on backpress`)
      this.derivedStack?.pop()
      return true
    })
    .onWillAppear(()=>{
      console.log('pageOne onWillAppear')
    })
    .onAppear(()=>{
      console.log('pageOne onAppear')
    })
    .onWillShow(()=>{
      console.log('pageOne onWillShow')
    })
    .onShown(()=>{
      console.log('pageOne onShown')
    })
    .onWillHide(()=>{
      console.log('pageOne onWillHide')
    })
    .onHidden(()=>{
      console.log('pageOne onHidden')
    })
    .onWillDisappear(()=>{
      console.log('pageOne onWillDisappear')
    })
    .onDisAppear(()=>{
      console.log('pageOne onDisAppear')
    })

  }
}


@Component
struct PageTwo {
  derivedStack: DerivedNavPathStack = new DerivedNavPathStack();
  curStringifyParam: string = '';
  build() {
    NavDestination() {
      Column({space:10}) {
      }
    }
    .title('pageTwo')
    .backgroundColor(Color.Pink)
    .onReady((context: NavDestinationContext) => {
      console.log('pageTwo onReady');
      this.derivedStack = context.pathStack as DerivedNavPathStack;
    })
    .onBackPressed(() => {
      console.log(`pageTwo on backpress`)
      this.derivedStack?.pop()
      return true
    })
    .onWillAppear(()=>{
      console.log('pageTwo onWillAppear')
    })
    .onAppear(()=>{
      console.log('pageTwo onAppear')
    })
    .onWillShow(()=>{
      console.log('pageTwo onWillShow')
    })
    .onShown(()=>{
      console.log('pageTwo onShown')
    })
    .onWillHide(()=>{
      console.log('pageTwo onWillHide')
    })
    .onHidden(()=>{
      console.log('pageTwo onHidden')
    })
    .onWillDisappear(()=>{
      console.log('pageTwo onWillDisappear')
    })
    .onDisAppear(()=>{
      console.log('pageTwo onDisAppear')
    })
  }
}

@Component
struct PageThree {
  derivedStack: DerivedNavPathStack = new DerivedNavPathStack();
  curStringifyParam: string = '';
  build() {
    NavDestination() {
      Column({space:10}) {
      }
    }
    .mode(NavDestinationMode.DIALOG)
    .title('pageThree')
    .backgroundColor(Color.Pink)
    .onReady((context: NavDestinationContext) => {
      console.log('pageThree onReady');
      this.derivedStack = context.pathStack as DerivedNavPathStack;
    })
    .onBackPressed(() => {
      console.log(`pageThree on backpress`)
      this.derivedStack?.pop()
      return true
    })
    .onWillAppear(()=>{
      console.log('pageThree onWillAppear')
    })
    .onAppear(()=>{
      console.log('pageThree onAppear')
    })
    .onWillShow(()=>{
      console.log('pageThree onWillShow')
    })
    .onShown(()=>{
      console.log('pageThree onShown')
    })
    .onWillHide(()=>{
      console.log('pageThree onWillHide')
    })
    .onHidden(()=>{
      console.log('pageThree onHidden')
    })
    .onWillDisappear(()=>{
      console.log('pageThree onWillDisappear')
    })
    .onDisAppear(()=>{
      console.log('pageThree onDisAppear')
    })
  }
}