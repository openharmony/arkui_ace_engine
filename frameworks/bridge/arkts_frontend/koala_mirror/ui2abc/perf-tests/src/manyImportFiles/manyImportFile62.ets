
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent124 } from "./manyImportFile124"
import { ManyImportComponent125 } from "./manyImportFile125"


@Component
export struct ManyImportComponent62 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent124()
            ManyImportComponent125()

        }
    }
}
