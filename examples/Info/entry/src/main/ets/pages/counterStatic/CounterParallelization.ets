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
'use static'

import {
  Entry,
  FlexWrap,
  ForEach,
  FlexAlign,
  ItemAlign,
  Flex,
  Text,
  Column,
  Scroll,
  Component,
  Button,
  ClickEvent,
  Checkbox,
  Gauge,
  LinearGradient,
  FontWeight,
  TextAlign,
  Builder,
  $r,
  ContentModifier,
  GaugeConfiguration,
  WrappedBuilder,
  Color,
  Progress,
  ProgressType,
  LengthMetrics,
  ProgressOptions,
  CapsuleStyleOptions,
  Counter,
  LazyForEach,
  ForEach
} from '@ohos.arkui.component'
import { State } from '@ohos.arkui.stateManagement'
import hilog from '@ohos.hilog'
import { forEachItems20, forEachItems100 } from '../Utils/Jarvis';
import { ParallelOption, ParallelizeUI } from '@ohos.arkui.Parallelize';

@Entry
@Component
struct CounterTest {
  @State value: number = 0;

  build() {
    Scroll() {
      Flex({ wrap: FlexWrap.Wrap, justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center }) {
        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text("1" + "-" + index + ">")
            Counter() {
              Text(this.value.toString())
            }
            .enableInc(undefined)
            .enableDec(undefined)
            .onInc(() => {
              this.value++;
              console.log("test ++");
            })
            .onDec(() => {
              this.value--;
              console.log("test --");
            })
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text("2" + "-" + index + ">")
            Counter() {
              Text(this.value.toString())
            }
            .enableInc(undefined)
            .enableDec(undefined)
            .onInc(() => {
              this.value++;
              console.log("test ++");
            })
            .onDec(() => {
              this.value--;
              console.log("test --");
            })
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text("3" + "-" + index + ">")
            Counter() {
              Text(this.value.toString())
            }
            .enableInc(undefined)
            .enableDec(undefined)
            .onInc(() => {
              this.value++;
              console.log("test ++");
            })
            .onDec(() => {
              this.value--;
              console.log("test --");
            })
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text("4" + "-" + index + ">")
            Counter() {
              Text(this.value.toString())
            }
            .enableInc(undefined)
            .enableDec(undefined)
            .onInc(() => {
              this.value++;
              console.log("test ++");
            })
            .onDec(() => {
              this.value--;
              console.log("test --");
            })
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text("5" + "-" + index + ">")
            Counter() {
              Text(this.value.toString())
            }
            .enableInc(undefined)
            .enableDec(undefined)
            .onInc(() => {
              this.value++;
              console.log("test ++");
            })
            .onDec(() => {
              this.value--;
              console.log("test --");
            })
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text("6" + "-" + index + ">")
            Counter() {
              Text(this.value.toString())
            }
            .enableInc(undefined)
            .enableDec(undefined)
            .onInc(() => {
              this.value++;
              console.log("test ++");
            })
            .onDec(() => {
              this.value--;
              console.log("test --");
            })
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text("7" + "-" + index + ">")
            Counter() {
              Text(this.value.toString())
            }
            .enableInc(undefined)
            .enableDec(undefined)
            .onInc(() => {
              this.value++;
              console.log("test ++");
            })
            .onDec(() => {
              this.value--;
              console.log("test --");
            })
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text("8" + "-" + index + ">")
            Counter() {
              Text(this.value.toString())
            }
            .enableInc(undefined)
            .enableDec(undefined)
            .onInc(() => {
              this.value++;
              console.log("test ++");
            })
            .onDec(() => {
              this.value--;
              console.log("test --");
            })
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text("9" + "-" + index + ">")
            Counter() {
              Text(this.value.toString())
            }
            .enableInc(undefined)
            .enableDec(undefined)
            .onInc(() => {
              this.value++;
              console.log("test ++");
            })
            .onDec(() => {
              this.value--;
              console.log("test --");
            })
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text("10" + "-" + index + ">")
            Counter() {
              Text(this.value.toString())
            }
            .enableInc(undefined)
            .enableDec(undefined)
            .onInc(() => {
              this.value++;
              console.log("test ++");
            })
            .onDec(() => {
              this.value--;
              console.log("test --");
            })
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text("11" + "-" + index + ">")
            Counter() {
              Text(this.value.toString())
            }
            .enableInc(undefined)
            .enableDec(undefined)
            .onInc(() => {
              this.value++;
              console.log("test ++");
            })
            .onDec(() => {
              this.value--;
              console.log("test --");
            })
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text("12" + "-" + index + ">")
            Counter() {
              Text(this.value.toString())
            }
            .enableInc(undefined)
            .enableDec(undefined)
            .onInc(() => {
              this.value++;
              console.log("test ++");
            })
            .onDec(() => {
              this.value--;
              console.log("test --");
            })
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text("13" + "-" + index + ">")
            Counter() {
              Text(this.value.toString())
            }
            .enableInc(undefined)
            .enableDec(undefined)
            .onInc(() => {
              this.value++;
              console.log("test ++");
            })
            .onDec(() => {
              this.value--;
              console.log("test --");
            })
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text("14" + "-" + index + ">")
            Counter() {
              Text(this.value.toString())
            }
            .enableInc(true)
            .enableDec(true)
            .onInc(() => {
              this.value++;
              console.log("test ++");
            })
            .onDec(() => {
              this.value--;
              console.log("test --");
            })
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text("15" + "-" + index + ">")
            Counter() {
              Text(this.value.toString())
            }
            .enableInc(false)
            .enableDec(false)
            .onInc(() => {
              this.value++;
              console.log("test ++");
            })
            .onDec(() => {
              this.value--;
              console.log("test --");
            })
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text("16" + "-" + index + ">")
            Counter() {
              Text(this.value.toString())
            }
            .enableInc(undefined)
            .enableDec(undefined)
            .onInc(() => {
              this.value++;
              console.log("test ++");
            })
            .onDec(() => {
              this.value--;
              console.log("test --");
            })
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text("17" + "-" + index + ">")
            Counter() {
              Text(this.value.toString())
            }
            .enableInc(undefined)
            .enableDec(undefined)
            .onInc(() => {
              this.value++;
              console.log("test ++");
            })
            .onDec(() => {
              this.value--;
              console.log("test --");
            })
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text("18" + "-" + index + ">")
            Counter() {
              Text(this.value.toString())
            }
            .enableInc(undefined)
            .enableDec(undefined)
            .onInc(() => {
              this.value++;
              console.log("test ++");
            })
            .onDec(() => {
              this.value--;
              console.log("test --");
            })
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text("19" + "-" + index + ">")
            Counter() {
              Text(this.value.toString())
            }
            .enableInc(undefined)
            .enableDec(undefined)
            .onInc(() => {
              this.value++;
              console.log("test ++");
            })
            .onDec(() => {
              this.value--;
              console.log("test --");
            })
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text("20" + "-" + index + ">")
            Counter() {
              Text(this.value.toString())
            }
            .enableInc(undefined)
            .enableDec(undefined)
            .onInc(() => {
              this.value++;
              console.log("test ++");
            })
            .onDec(() => {
              this.value--;
              console.log("test --");
            })
          })
        }
      }
    }
  }
}
