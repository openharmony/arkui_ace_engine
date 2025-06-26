
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent48 } from "./manyImportFile48"
import { ManyImportComponent49 } from "./manyImportFile49"


@Component
export struct ManyImportComponent24 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent48()
            ManyImportComponent49()

        }
    }
}
