
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent10 } from "./manyImportFile10"
import { ManyImportComponent11 } from "./manyImportFile11"


@Component
export struct ManyImportComponent5 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent10()
            ManyImportComponent11()

        }
    }
}
