
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent110 } from "./manyImportFile110"
import { ManyImportComponent111 } from "./manyImportFile111"


@Component
export struct ManyImportComponent55 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent110()
            ManyImportComponent111()

        }
    }
}
