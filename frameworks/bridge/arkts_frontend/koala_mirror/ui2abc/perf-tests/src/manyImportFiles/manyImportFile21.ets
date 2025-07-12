
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent42 } from "./manyImportFile42"
import { ManyImportComponent43 } from "./manyImportFile43"


@Component
export struct ManyImportComponent21 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent42()
            ManyImportComponent43()

        }
    }
}
