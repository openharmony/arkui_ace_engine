/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
import { AnimatedDrawableDescriptor } from '@kit.ArkUI'

@Entry
@Component
struct AnimatedDrawableDescriptorResource {
  @State drawable1: AnimatedDrawableDescriptor =
    new AnimatedDrawableDescriptor($r('app.media.flower'), { iterations: -1, duration: 2000 })
  @State drawable2: AnimatedDrawableDescriptor =
    new AnimatedDrawableDescriptor($r('app.media.img2'), { iterations: -1, duration: 2000 })
  @State drawable3: AnimatedDrawableDescriptor =
    new AnimatedDrawableDescriptor($r('app.media.cat2'), { iterations: 10, duration: 4000 })
  @State drawable4: AnimatedDrawableDescriptor =
    new AnimatedDrawableDescriptor($r('app.media.mouse'), { iterations: -1, duration: 2000 })
  @State drawable5: AnimatedDrawableDescriptor =
    new AnimatedDrawableDescriptor($r('app.media.loading'), { iterations: -1, duration: 2000 })
  @State drawable6: AnimatedDrawableDescriptor =
    new AnimatedDrawableDescriptor($r('app.media.startIcon'), { iterations: -1, duration: 2000 })

  build() {
    Column({ space: 5 }) {
      Row({ space: 5 }) {
        Image(this.drawable1).width(100).height(100)
        Image(this.drawable1).width(100).height(100)
        Image(this.drawable1).width(100).height(100)
      }

      Row({ space: 5 }) {
        Image(this.drawable1).width(100).height(100)
        Image(this.drawable1).width(100).height(100)
        Image(this.drawable1).width(100).height(100)
      }

      Row({ space: 5 }) {
        Image(this.drawable1).width(100).height(100)
        Image(this.drawable1).width(100).height(100)
        Image(this.drawable1).width(100).height(100)
      }

      Row({ space: 5 }) {
        Image(this.drawable6).width(100).height(100)
        Image(this.drawable6).width(100).height(100)
        Image(this.drawable6).width(100).height(100)
      }

      Row({ space: 5 }) {
        Image(this.drawable2).width(100).height(100)
        Image(this.drawable2).width(100).height(100)
        Image(this.drawable2).width(100).height(100)
      }

      Row({ space: 5 }) {
        Image(this.drawable3).width(100).height(100)
        Image(this.drawable3).width(100).height(100)
        Image(this.drawable3).width(100).height(100)
      }

      Row({ space: 5 }) {
        Image(this.drawable4).width(100).height(100)
        Image(this.drawable4).width(100).height(100)
        Image(this.drawable4).width(100).height(100)
      }
    }
    .height('100%')
    .width('100%')
  }
}
