/*
 * Copyright (c) 2023-2023 Huawei Device Co., Ltd.
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
 
const EMPTY_STRING: string = ''
const MAX_PROGRESS: number = 100
const MAX_PERCENTAGE: string = '100%'
const MIN_PERCENTAGE: string = '0%'

@Component
export struct ProgressButton {
  @Prop @Watch('getProgressContext') progress: number
  @State textProgress: string = EMPTY_STRING
  @Prop content: string = EMPTY_STRING
  @State isLoading: boolean = false
  progressButtonWidth?: Length = 44
  clickCallback: () => void = null
  @Prop enable: boolean = true

  private getButtonProgress(): number {
    if (this.progress < 0) {
      return 0
    } else if (this.progress > MAX_PROGRESS) {
      return MAX_PROGRESS
    }
    return this.progress
  }

  private getProgressContext() {
    if (this.progress < 0) {
      this.isLoading = false
      this.textProgress = MIN_PERCENTAGE
    } else if (this.progress >= MAX_PROGRESS) {
      this.isLoading = false
      this.textProgress = MAX_PERCENTAGE
    } else {
      this.isLoading = true
      this.textProgress = Math.floor(this.progress / MAX_PROGRESS * MAX_PROGRESS).toString() + "%"
    }
  }

  build() {
    Button() {
      Stack(){
        Progress({ value: this.getButtonProgress(), total: MAX_PROGRESS,
          style: ProgressStyle.Capsule })
          .height(28)
          .borderRadius(14)
          .width('100%')
          .hoverEffect(HoverEffect.None)
          .clip(false)
          .enabled(this.enable)
          .color('#330A59F7')
        Row() {
          Text(this.isLoading? this.textProgress: this.content)
            .fontSize($r('sys.float.ohos_id_text_size_button3'))
            .fontWeight(FontWeight.Medium)
            .fontColor($r('sys.color.ohos_id_color_text_primary'))
            .maxLines(1)
            .textOverflow({ overflow: TextOverflow.Ellipsis })
            .padding({left: 8, right: 8})
            .opacity(this.enable? 1.0: 0.4)
        }
        Row().backgroundColor(Color.Transparent)
          .border({ width: 1, color: '#330A59F7'})
          .height(28)
          .borderRadius(14)
          .width('100%')
      }
    }
    .borderRadius(14)
    .clip(false)
    .hoverEffect(HoverEffect.None)
    .backgroundColor($r("sys.color.ohos_id_color_foreground_contrary"))
    .constraintSize({minWidth: 44})
    .width(this.progressButtonWidth < 44? 44: this.progressButtonWidth)
    .stateEffect(this.enable)
    .onClick(() => {
      if(!this.enable){
        return
      }
      if (this.progress < MAX_PROGRESS) {
        this.isLoading = !this.isLoading
      }
      this.clickCallback && this.clickCallback()
    })
  }
}