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
import observer from '@ohos.arkui.observer';
import { common } from '@kit.AbilityKit';

class NavDestinationIdHelper {
  private ids: string[] = [];
  private static instance: NavDestinationIdHelper = new NavDestinationIdHelper()

  static getInstance() {
    return NavDestinationIdHelper.instance
  }

  public addId(id: string): number {
    this.ids.push(id)
    return this.ids.length
  }

  public removeId(id: string): boolean {
    let index: number = this.ids.findIndex(element => element === id)
    if (index === -1) {
      return false
    }
    this.ids.splice(index, 1)
    return true
  }

  public getIdArray(): string[] {
    return this.ids
  }
}

@Entry
@Component
struct Index {
  stack: NavPathStack = new NavPathStack()
  private context = getContext(this) as common.UIAbilityContext;//新增

  routerPageUpdateCallback(info: RouterPageInfo) {
    if(info){
      console.log(`testTag routerPageUpdateCallback,
      index: ${info.index},
      name: ${info.name}, path: ${info.path}, state: ${info.state},
      pageId: ${info.pageId}`);
    }
  }

  observerOnRouter(){
    observer.on('routerPageUpdate', this.context, this.routerPageUpdateCallback);
  }//新增

  observerOffRouter(){
    observer.off('routerPageUpdate', this.context, this.routerPageUpdateCallback);
  }//新增

  @Builder
  pageMap(name: string) {
    if (name == 'dest') {
      Dest()
    }else if(name=='pageOne'){
      pageOneTmp()
    }else if(name=='pageTwo'){
      pageTwo()
    }
  }

  aboutToAppear(): void {
    this.stack.pushPath({name: 'dest'})
  }

  onPageShow(): void {
    if (this.stack.size() === 0) {
      this.stack.pushPath({name: 'dest'})
    }
  }

  build() {
    Navigation(this.stack) {
      Button('push destination').margin(20)
        .onClick(() => {
          this.stack.pushPath({name: 'dest'})
        })
    }
    .hideNavBar(true)
    .navDestination(this.pageMap)
  }
}

@Component
struct pageTwo {
  build(){
    NavDestination(){
      Text('this is pageTwo')
    }.mode(NavDestinationMode.DIALOG)
    .backgroundColor('rgba(255,242,22,6)')
  }
}
@Component
struct Dest {
  stack: NavPathStack = new NavPathStack()
  @State curId: string = 'NA'
  @State idArray: string[] = NavDestinationIdHelper.getInstance().getIdArray();
  @State editText: string = 'indicate ids to remove, split by space'
  @State text2:string = ''
  updateIdArray() {
    this.idArray = NavDestinationIdHelper.getInstance().getIdArray();
  }
  navDesUpdateCallback(info: NavDestinationInfo) {
    console.log(JSON.stringify(info))
  }
  observerOn(){
    observer.on('navDestinationUpdate', this.navDesUpdateCallback);
  }
  observerOff(){
    observer.off('navDestinationUpdate', this.navDesUpdateCallback);
  }
  build() {
    NavDestination() {
      Text('current page：dest').fontWeight(FontWeight.Bolder)
      Column() {
        Text('current id: ' + this.curId)
          .fontSize(30)
          .fontWeight(FontWeight.Bold)
          .margin(15)
        Text('all id: ' + JSON.stringify(this.idArray))
          .fontSize(18)
          .margin(20)
      }
      .backgroundColor(Color.Pink)
      Row({space:5}) {
        Button('push*5').margin(3)
          .onClick(() => {
            this.stack.pushPath({ name: 'dest' })
            this.stack.pushPath({ name: 'dest' })
            this.stack.pushPath({ name: 'dest' })
            this.stack.pushPath({ name: 'dest' })
            this.stack.pushPath({ name: 'dest' })
          })
        Button('pop').onClick(()=>this.stack.pop())
        Button('push new dest').margin(3)
          .onClick(() => {
            this.stack.pushPath({ name: 'dest' })
          })
      }
        Row({space:5}){
        Button('remove by invalid id').margin(5)
          .onClick(() => {
            let ret = this.stack.removeByNavDestinationId('__INVALID__')
            console.log('[removeById][demo] remove invalid id\'s return value: ' + ret)
            AlertDialog.show({message:'remove invalid id\'s return value: ' + ret})
          })
        Button('remove by currentId').margin(5)
          .onClick(() => {
            let ret = this.stack.removeByNavDestinationId(this.curId)
            console.log('[removeById][demo] remove curId\'s return value: ' + ret)
            AlertDialog.show({message:' remove curId\'s return value: ' + ret})
          })
      }
      Row(){
        Button('remove by top - 1 id').margin(5).fontSize(15)
          .onClick(() => {
            let ids = NavDestinationIdHelper.getInstance().getIdArray()
            if (ids.length <= 1) {
              return;
            }
            let id = ids[ids.length - 2]
            let ret = this.stack.removeByNavDestinationId(id)
            console.log('[removeById][demo] remove top - 1 id\'s return value: ' + ret)

            setTimeout(() => {
              this.updateIdArray()
            }, 200)
          })
        Button('push pageOne dest').fontSize(15)
          .onClick(()=>{
            this.stack.pushPath({name:'pageOne'})
          })
      }

      Button('removeByName currentPage dest').onClick(()=>{
        this.stack.removeByName('dest')
      })
      Row({space:3}){
        Button('removeByCurrentId+pop').onClick(()=>{
          let ret = this.stack.removeByNavDestinationId(this.curId)
          AlertDialog.show({message:' remove curId\'s return value: ' + ret})
          this.stack.pop()
        })
        Button('removeById:5 *5').onClick(()=>{
          let ret1=this.stack.removeByNavDestinationId('5')
          let ret2=this.stack.removeByNavDestinationId('5')
          let ret3=this.stack.removeByNavDestinationId('5')
          let ret4=this.stack.removeByNavDestinationId('5')
          let ret5=this.stack.removeByNavDestinationId('5')
          AlertDialog.show({message:' remove curId\'s return value: ' +
            ret1+' '+ret2+' '+ret3+' '+ret4+' '+ret5})
        })
      }
      Row({space:3}){
        Button('removeByCurrentId:0').onClick(()=>{
          this.stack.removeByNavDestinationId('0')
        })
        Button('get', { stateEffect: true, type: ButtonType.Capsule })
          .height(40)
          .margin(20)
          .onClick(() => {
            console.log('getAllPathName:', JSON.stringify(this.stack.getAllPathName()))
            console.log('getParamByIndex:', JSON.stringify(this.stack.getParamByIndex(1)))
            console.log('getParamByName:', JSON.stringify(this.stack.getParamByName('dest')))
            console.log('getIndexByName:', JSON.stringify(this.stack.getIndexByName('dest')))
            console.log('get stack size：', JSON.stringify(this.stack.size()))
          })
      }
      Row({space:5}){
        Button('observerOn')
          .onClick(() => {
            this.observerOn()
          })

        Button('observerOff')
          .onClick(() => {
            this.observerOff()
          })
      }
      TextInput({text: this.editText})
        .margin(20)
        .width('75%')
        .backgroundColor('#ccc')
        .fontWeight(200)
        .onEditChange((isEditing) => {
          this.editText = isEditing ? '' : 'indicate ids to remove, split by space'
        })
        .onSubmit((enterKey: EnterKeyType, event: SubmitEvent) => {
          let deletedIds = event.text.split(' ');
          let removeSuccessIds: string[] = []
          let removeFailedIds: string[] = []
          for (let index = 0; index < deletedIds.length; ++ index) {
            let deletedId = deletedIds[index]
            if (this.stack.removeByNavDestinationId(deletedId)) {
              removeSuccessIds.push(deletedId)
            } else {
              removeFailedIds.push(deletedId)
            }
          }
          console.log('[removeById][demo] result of remove indicated ids:')
          console.log('[removeById][demo] --> remove success: ' + removeSuccessIds)
          console.log('[removeById][demo] --> remove failed : ' + removeFailedIds)
          setTimeout(() => {
            this.updateIdArray()
          }, 200)
        })
      Text(this.text2).fontWeight(FontWeight.Bold).fontColor('#FFBB00')
      Button(`getAllPathName`, { stateEffect: true, type: ButtonType.Capsule })
        .width('80%')
        .height(40)
        .margin(10)
        .onClick(() => {
          this.text2 = JSON.stringify(this.stack.getAllPathName())
        })
    }
    .onReady((ctx) => {
      this.stack = ctx.pathStack
      this.curId = ctx.navDestinationId ? ctx.navDestinationId : '__invalid__'
      NavDestinationIdHelper.getInstance().addId(this.curId)
    })
    .onShown(() => {
      console.log('[removeById][demo][life] id ' + this.curId + ' onShown')
      this.updateIdArray()
    })
    .onWillDisappear(() => {
      console.log('[removeById][demo][life] id ' + this.curId + ' onWillDisAppear')
      NavDestinationIdHelper.getInstance().removeId(this.curId)
    })
    .onDisAppear(() => {
      console.log('[removeById][demo][life] id ' + this.curId + ' onDisAppear')
    })
    .onWillAppear(()=>{
      console.log('[removeById][demo][life] id ' + this.curId + ' onWillAppear')
    })
    .onAppear(()=>{
      console.log('[removeById][demo][life] id ' + this.curId + ' onAppear')
    })
    .onWillShow(()=>{
      console.log('[removeById][demo][life] id ' + this.curId + ' onWillShow')
    })
    .onShown(()=>{
      console.log('[removeById][demo][life] id ' + this.curId + ' onShown')
    })
    .onWillHide(()=>{
      console.log('[removeById][demo][life] id ' + this.curId + ' onWillHide')
    })
    .onHidden(()=>{
      console.log('[removeById][demo][life] id ' + this.curId + ' onHidden')
    })
    .onWillDisappear(()=>{
      console.log('[removeById][demo][life] id ' + this.curId + ' onWillDisappear')
    })
    .onDisAppear(()=>{
      console.log('[removeById][demo][life] id ' + this.curId + ' onDisAppear')
    })
  }
}

@Component
struct pageOneTmp {
  stack: NavPathStack = new NavPathStack()
  @State curId: string = 'NA'
  @State idArray: string[] = NavDestinationIdHelper.getInstance().getIdArray();
  @State editText: string = 'indicate ids to remove, split by space'
  @State text2:string = ''
  updateIdArray() {
    this.idArray = NavDestinationIdHelper.getInstance().getIdArray();
  }
  navDesUpdateCallback(info: NavDestinationInfo) {
    console.log(JSON.stringify(info))
  }
  observerOn(){
    observer.on('navDestinationUpdate', this.navDesUpdateCallback);
  }

  observerOff(){
    observer.off('navDestinationUpdate', this.navDesUpdateCallback);
  }
  build() {
    NavDestination() {
      Text('current page：dest').fontWeight(FontWeight.Bolder)
      Column() {
        Text('current id: ' + this.curId)
          .fontSize(30)
          .fontWeight(FontWeight.Bold)
          .margin(15)
        Text('all id: ' + JSON.stringify(this.idArray))
          .fontSize(18)
          .margin(20)
      }
      .backgroundColor(Color.Pink)
      Row({space:5}) {
        Button('push*5').margin(3)
          .onClick(() => {
            this.stack.pushPath({ name: 'dest' })
            this.stack.pushPath({ name: 'dest' })
            this.stack.pushPath({ name: 'dest' })
            this.stack.pushPath({ name: 'dest' })
            this.stack.pushPath({ name: 'dest' })
          })
        Button('pop').onClick(()=>this.stack.pop())
        Button('push new dest').margin(3)
          .onClick(() => {
            this.stack.pushPath({ name: 'dest' })
          })
      }
      Row({space:5}){
        Button('remove by invalid id').margin(5)
          .onClick(() => {
            let ret = this.stack.removeByNavDestinationId('__INVALID__')
            console.log('[removeById][demo] remove invalid id\'s return value: ' + ret)
            AlertDialog.show({message:'remove invalid id\'s return value: ' + ret})
          })
        Button('remove by currentId').margin(5)
          .onClick(() => {
            let ret = this.stack.removeByNavDestinationId(this.curId)
            console.log('[removeById][demo] remove curId\'s return value: ' + ret)
            AlertDialog.show({message:' remove curId\'s return value: ' + ret})
          })
      }
      Row(){
        Button('remove by top - 1 id').margin(5).fontSize(15)
          .onClick(() => {
            let ids = NavDestinationIdHelper.getInstance().getIdArray()
            if (ids.length <= 1) {
              return;
            }
            let id = ids[ids.length - 2]
            let ret = this.stack.removeByNavDestinationId(id)
            console.log('[removeById][demo] remove top - 1 id\'s return value: ' + ret)

            setTimeout(() => {
              this.updateIdArray()
            }, 200)
          })
        Button('push pageOne dest').fontSize(15)
          .onClick(()=>{
            this.stack.pushPath({name:'pageOne'})
          })
      }
      Button('removeByName currentPage dest').onClick(()=>{
        this.stack.removeByName('dest')
      })
      Row({space:3}){
        Button('removeByCurrentId+pop').onClick(()=>{
          let ret = this.stack.removeByNavDestinationId(this.curId)
          AlertDialog.show({message:' remove curId\'s return value: ' + ret})
          this.stack.pop()
        })
        Button('removeById:5 *5').onClick(()=>{
          let ret1=this.stack.removeByNavDestinationId('5')
          let ret2=this.stack.removeByNavDestinationId('5')
          let ret3=this.stack.removeByNavDestinationId('5')
          let ret4=this.stack.removeByNavDestinationId('5')
          let ret5=this.stack.removeByNavDestinationId('5')
          AlertDialog.show({message:' remove curId\'s return value: ' +
            ret1+' '+ret2+' '+ret3+' '+ret4+' '+ret5})
        })
      }
      Row({space:3}){
        Button('removeByCurrentId:0').onClick(()=>{
          this.stack.removeByNavDestinationId('0')
        })
        Button('get', { stateEffect: true, type: ButtonType.Capsule })
          .height(40)
          .margin(20)
          .onClick(() => {
            console.log('getAllPathName:', JSON.stringify(this.stack.getAllPathName()))
            console.log('getParamByIndex:', JSON.stringify(this.stack.getParamByIndex(1)))
            console.log('getParamByName:', JSON.stringify(this.stack.getParamByName('dest')))
            console.log('getIndexByName:', JSON.stringify(this.stack.getIndexByName('dest')))
            console.log('get stack size:', JSON.stringify(this.stack.size()))
          })
      }
      Row({space:5}){
        Button('observerOn')
          .onClick(() => {
            this.observerOn()
          })

        Button('observerOff')
          .onClick(() => {
            this.observerOff()
          })
      }
      TextInput({text: this.editText})
        .margin(20)
        .width('75%')
        .backgroundColor('#ccc')
        .fontWeight(200)
        .onEditChange((isEditing) => {
          this.editText = isEditing ? '' : 'indicate ids to remove, split by space'
        })
        .onSubmit((enterKey: EnterKeyType, event: SubmitEvent) => {
          let deletedIds = event.text.split(' ');
          let removeSuccessIds: string[] = []
          let removeFailedIds: string[] = []
          for (let index = 0; index < deletedIds.length; ++ index) {
            let deletedId = deletedIds[index]
            if (this.stack.removeByNavDestinationId(deletedId)) {
              removeSuccessIds.push(deletedId)
            } else {
              removeFailedIds.push(deletedId)
            }
          }
          console.log('[removeById][demo] result of remove indicated ids:')
          console.log('[removeById][demo] --> remove success: ' + removeSuccessIds)
          console.log('[removeById][demo] --> remove failed : ' + removeFailedIds)

          setTimeout(() => {
            this.updateIdArray()
          }, 200)
        })
      Text(this.text2).fontWeight(FontWeight.Bold).fontColor('#FFBB00')
      Button(`getAllPathName`, { stateEffect: true, type: ButtonType.Capsule })
        .width('80%')
        .height(40)
        .margin(10)
        .onClick(() => {
          this.text2 = JSON.stringify(this.stack.getAllPathName())
        })
    }
    .onReady((ctx) => {
      this.stack = ctx.pathStack
      this.curId = ctx.navDestinationId ? ctx.navDestinationId : '__invalid__'
      NavDestinationIdHelper.getInstance().addId(this.curId)
    })
    .onShown(() => {
      console.log('[removeById][demo][life] id ' + this.curId + ' onShown')
      this.updateIdArray()
    })
    .onWillDisappear(() => {
      console.log('[removeById][demo][life] id ' + this.curId + ' onWillDisAppear')
      NavDestinationIdHelper.getInstance().removeId(this.curId)
    })
    .mode(NavDestinationMode.DIALOG)
    .onDisAppear(() => {
      console.log('[removeById][demo][life] id ' + this.curId + ' onDisAppear')
    })
    .onWillAppear(()=>{
      console.log('[removeById][demo][life] id ' + this.curId + ' onWillAppear')
    })
    .onAppear(()=>{
      console.log('[removeById][demo][life] id ' + this.curId + ' onAppear')
    })
    .onWillShow(()=>{
      console.log('[removeById][demo][life] id ' + this.curId + ' onWillShow')
    })
    .onShown(()=>{
      console.log('[removeById][demo][life] id ' + this.curId + ' onShown')
    })
    .onWillHide(()=>{
      console.log('[removeById][demo][life] id ' + this.curId + ' onWillHide')
    })
    .onHidden(()=>{
      console.log('[removeById][demo][life] id ' + this.curId + ' onHidden')
    })
    .onWillDisappear(()=>{
      console.log('[removeById][demo][life] id ' + this.curId + ' onWillDisappear')
    })
    .onDisAppear(()=>{
      console.log('[removeById][demo][life] id ' + this.curId + ' onDisAppear')
    })
  }
}