
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent144 } from "./manyImportFile144"
import { ManyImportComponent145 } from "./manyImportFile145"


@Component
export struct ManyImportComponent72 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent144()
            ManyImportComponent145()

        }
    }
}
