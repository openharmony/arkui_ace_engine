
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent34 } from "./manyImportFile34"
import { ManyImportComponent35 } from "./manyImportFile35"


@Component
export struct ManyImportComponent17 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent34()
            ManyImportComponent35()

        }
    }
}
