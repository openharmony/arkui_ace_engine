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
interface Info {
  name: string;
  type?: number;
  callback: (stack: NavPathStack, index?: string)=>void
}
@Entry
@Component
export struct pageTwoTmp {
  pathStack: NavPathStack = new NavPathStack();
  index: string = "";

  checkArray: Array<Info> = [
    {name: 'push pageThree', callback: (stack: NavPathStack)=>{stack.pushPath({name:'pageThree'});}},
    {name: 'Pop', callback: (stack: NavPathStack)=>{stack.pop();}},
    {name: 'PopToOneByName', callback: (stack: NavPathStack) => {stack.popToName('pageOne');}},
    {name: 'popToOneByIndex', callback: (stack: NavPathStack) => {
      let index = stack.getIndexByName('pageOne')[0];
      stack.popToIndex(index);
    }},
    {name: 'replaceToPageThree', callback: (stack: NavPathStack) => {
      stack.replacePath({name: 'pageThree'});
    }},
    {name: 'replaceToPageThreeByName', callback: (stack: NavPathStack)=>{
     stack.replacePathByName('pageThree', null);
    }},
    {name: 'replaceToPageTwo', callback: (stack: NavPathStack)=>{
      stack.replacePath({name: 'pageTwo'})
    }},
    {
      name: 'replacePageOneToPageTwo', callback: (stack: NavPathStack)=>{

    }
    },
    {
      name: 'removeByNamePageTwo', callback: (stack: NavPathStack) => {
      stack.removeByName('pageTwo');
    } },
    {
      name: 'removeByNamePageOne', callback: (stack: NavPathStack) => {
      stack.removeByName('pageOne');
    }
    },
    {
      name: 'removeByIndexPageTwo',
      callback: (stack: NavPathStack, index?: string)=>{
        console.log("remove index " + index);
        stack.removeByIndexes([1])
      }
    },
    {name: 'movePageOneToTop', callback: (stack: NavPathStack)=>{
      stack.moveToTop('pageOne');
    }},
    {name: 'moveIndexToTop', callback: (stack: NavPathStack)=>{stack.moveIndexToTop(0);}}
  ];

  build() {
    NavDestination() {
      Column() {
        List() {
          ForEach(this.checkArray, (item: Info) => {
            ListItem() {
              if (item.type) {
                Row()  {
                  Text(item.name + ":")
                  TextInput({placeholder: 'please enter index'}).width('30%').onSubmit(()=>{
                    item.callback(this.pathStack, this.index);
                  }).onChange((val:string)=>{
                    this.index = val;
                  })
                }
              } else {
                Button(item.name)
                  .width('80%')
                  .height(30)
                  .margin(5).onClick(()=>{
                  item.callback(this.pathStack);
                })
              }
            }
          })
        }
      }.width('100%').height('100%')
    }.title('pageTwo').onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    }).onShown(()=>{
      console.log("===NavigationReInterception=== pageTwo onShown");
    })
  }

}