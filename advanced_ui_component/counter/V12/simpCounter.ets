import { Text, Column, Component, Button, ClickEvent, Entry } from "@ohos.arkui.component"
import { State } from "@ohos.arkui.stateManagement"

@Entry
@Component
struct MyStateSample {
  @State stateVar: string = "state var";
  build() {
    Column() {
      Text("Hello World").fontSize(20)
        Button("TTTTTTTTTTTT")
         .onClick((e: ClickEvent) => {
         })
    }
  }
}

export function TestABC(): void {
  
}

