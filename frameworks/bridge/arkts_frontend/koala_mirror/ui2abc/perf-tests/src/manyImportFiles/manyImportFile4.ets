
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent8 } from "./manyImportFile8"
import { ManyImportComponent9 } from "./manyImportFile9"


@Component
export struct ManyImportComponent4 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent8()
            ManyImportComponent9()

        }
    }
}
