
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent140 } from "./manyImportFile140"
import { ManyImportComponent141 } from "./manyImportFile141"


@Component
export struct ManyImportComponent70 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent140()
            ManyImportComponent141()

        }
    }
}
