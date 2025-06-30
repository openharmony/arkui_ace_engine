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

import events_emitter from '@ohos.events.emitter';
import hilog from '@ohos.hilog';

@Builder
export function SelectLevel6Builder(name: string, param: Object) {
  SelectLevel6Example()
}

@Entry
@Component
struct SelectLevel6Example {
  pathStack: NavPathStack = new NavPathStack()
  @State font: Font = {
    size: 30,
    weight: 400,
    family: 'serif',
    style: FontStyle.Normal
  }
  @State fontColor: Color = 0xCCCCCC
  @State spaceValue: number = 8
  @State spaceValueString: string = '50.00vp'
  @State arrowPosition: ArrowPosition = ArrowPosition.END
  @State spaceValueResource: Resource = $r('app.string.Test_Values')
  private stateChangCallBack = (eventData: events_emitter.EventData) => {
    console.info('selectTest stateChangCallBack before:' + JSON.stringify(eventData));
    if (eventData != null) {
      this.spaceValue = eventData.data?.spaceValue;
      console.info('select page state change called after spaceValue:' + this.spaceValue);
      this.arrowPosition = eventData.data?.arrowPosition;
      console.info('select page eventData:' + this.arrowPosition);

      if (eventData.data?.spaceValueString != null) {
        this.spaceValueString = eventData.data.spaceValueString;
        console.info('select page state change called after spaceValue:' + this.spaceValueString);
      }

      if (eventData.data?.spaceValueResource != null) {
        this.spaceValueResource = eventData.data.spaceValueResource;
        console.info('select page state change called after spaceValue:' + this.spaceValueResource);
      }
    }
  }

  aboutToAppear() {
    let stateChangeEvent: events_emitter.InnerEvent = {
      eventId: 181,
      priority: events_emitter.EventPriority.LOW
    }
    events_emitter.on(stateChangeEvent, this.stateChangCallBack);
    hilog.isLoggable(0x0000, 'testTag', hilog.LogLevel.INFO);
    hilog.info(0x0000, 'testTag', '%{public}s', 'start run testcase!!!');
  }

  build() {
    NavDestination() {
      Column() {
        Select([{ value: 'aaa', icon: '/images/img.png' },
          { value: 'bbb', icon: '/images/img.png' },
          { value: 'ccc', icon: '/images/img.png' },
          { value: 'ddd', icon: '/images/img.png' }])
          .selected(2)
          .value('TTT')
          .font(this.font)
          .fontColor(this.fontColor)
          .selectedOptionFont({
            size: 40,
            weight: 500,
            family: 'serif',
            style: FontStyle.Normal
          })
          .optionFont({
            size: 30,
            weight: 400,
            family: 'serif',
            style: FontStyle.Normal
          })
          .key('selectTest')
          .onSelect((index: number) => {
            console.info('Select:' + index)
          })
          .space(this.spaceValue)
          .arrowPosition(this.arrowPosition)
          .margin({ bottom: 40 })

        Select([{ value: 'aaa', icon: '/images/img.png' },
          { value: 'bbb', icon: '/images/img.png' },
          { value: 'ccc', icon: '/images/img.png' },
          { value: 'ddd', icon: '/images/img.png' }])
          .selected(2)
          .value('TTT')
          .font(this.font)
          .fontColor(this.fontColor)
          .selectedOptionFont({
            size: 40,
            weight: 500,
            family: 'serif',
            style: FontStyle.Normal
          })
          .optionFont({
            size: 30,
            weight: 400,
            family: 'serif',
            style: FontStyle.Normal
          })
          .key('selectTest2')
          .onSelect((index: number) => {
            console.info('Select:' + index)
          })
          .space(this.spaceValueString)
          .arrowPosition(this.arrowPosition)

          .margin({ bottom: 40 })

        Select([{ value: 'aaa', icon: '/images/img.png' },
          { value: 'bbb', icon: '/images/img.png' },
          { value: 'ccc', icon: '/images/img.png' },
          { value: 'ddd', icon: '/images/img.png' }])
          .selected(2)
          .value('TTT')
          .font(this.font)
          .fontColor(this.fontColor)
          .selectedOptionFont({
            size: 40,
            weight: 500,
            family: 'serif',
            style: FontStyle.Normal
          })
          .optionFont({
            size: 30,
            weight: 400,
            family: 'serif',
            style: FontStyle.Normal
          })
          .key('selectTest3')
          .onSelect((index: number) => {
            console.info('Select:' + index)
          })
          .space(this.spaceValueResource)
          .arrowPosition(this.arrowPosition)
      }
    }
    .title('SelectLevel6')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}