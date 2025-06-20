
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent132 } from "./manyImportFile132"
import { ManyImportComponent133 } from "./manyImportFile133"


@Component
export struct ManyImportComponent66 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent132()
            ManyImportComponent133()

        }
    }
}
